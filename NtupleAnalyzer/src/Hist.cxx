#include "../include/Hist.h"

#include "TRandom3.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/type_traits.hpp>

Hist::Hist(std::string home)
{
   help = new Helper();
   
   _home = home;
   
//   std::string foutlog = "log/"+std::string(flog);
   std::string foutlog = "log/list.txt";
   _fevc = fopen(foutlog.c_str(),"w");
//   std::string foutlogVal = "log/"+std::string(flog)+".val";
   std::string foutlogVal = "log/list.val";
   _fevcVal.open(foutlogVal.c_str());
      
   _v_ElectronTight = new std::vector<Electron>;
   _v_ElectronLoose = new std::vector<Electron>;
   _v_MuonTight = new std::vector<Muon>;
   _v_MuonLoose = new std::vector<Muon>;
   _v_JetTight = new std::vector<Jet>;
   _v_BJetTight = new std::vector<Jet>;
   _v_NonBJetTight = new std::vector<Jet>;
}

Hist::~Hist()
{
   delete _v_ElectronTight;
   delete _v_ElectronLoose;
   delete _v_MuonTight;
   delete _v_MuonLoose;
   delete _v_JetTight;
   delete _v_BJetTight;
   delete _v_NonBJetTight;

   delete help;
   delete _trec;
   delete _mva;
}

void Hist::init()
{
   rnd = new TRandom3(666);
   
//   std::string foutput = _home+"/"+std::string(flog)+".root";
   std::string foutput = std::string(flog)+".root";
   _fout = new TFile(foutput.c_str(),"RECREATE");

   _trec = new TopReco();
   _trec->init();

   _fout->cd();
   
//   _mva = new ApplyMVA(_home);
//   _mva->init();
   
   _h_PassSel_all = new TH1D("h_PassSel_all","h_PassSel_all",6,0.,6.);
   _h_PassSel_e = new TH1D("h_PassSel_e","h_PassSel_e",6,0.,6.);
   _h_PassSel_m = new TH1D("h_PassSel_m","h_PassSel_m",6,0.,6.);

   hname.clear(); 

   histname_n = 2;
   histname[0] = "h_chi2_TOPTOPLEPHBB_";
   histname[1] = "h_HiggsMass_TOPTOPLEPHBB_";

   type_n = 1;
//   type[0] = "nonQCD";
//   type[1] = "QCD";
   type[0] = "ALL";

   sel_n = 1;
   sel[0] = "TopTopLepHbb";
//   sel[2] = "bjge2";
//   sel[0] = "bjge3";
//   sel[0] = "bjge3";
//   sel[5] = "bjge3_mH";
//   sel[6] = "bjge3_mH_jveto";

   chan_n = 3;
   chan[0] = "all";
   chan[1] = "e";
   chan[2] = "m";
   
   sys_low_n = 1;
   sys_low[0]   = "";
//   sys_low[1]   = "_pu_low";

   sys_up_n = sys_low_n-1;
//   sys_up[0]   = "_pu_up";

   sys_n = sys_low_n + sys_up_n;
   
   for(int is1=0;is1<sys_low_n;is1++)
     {
	sys[is1] = sys_low[is1];
     }   
   for(int is2=0;is2<sys_up_n;is2++)
     {
	sys[sys_low_n+is2] = sys_up[is2];
     }   
/*
   for(int ic=0;ic<chan_n;ic++)
     {
	std::string trName = "tr_"+chan[ic];
	_trout[ic] = new TTree(trName.c_str(),trName.c_str());

	_trout[ic]->Branch("weight",&m_weight,"weight/D");
	_trout[ic]->Branch("H_m",&m_H_m,"H_m/D");
	_trout[ic]->Branch("H_pt",&m_H_pt,"H_pt/D");
	_trout[ic]->Branch("top_m",&m_top_m,"top_m/D");
	_trout[ic]->Branch("H_eta",&m_H_eta,"H_eta/D");
	_trout[ic]->Branch("top_pt",&m_top_pt,"top_pt/D");
	_trout[ic]->Branch("top_eta",&m_top_eta,"top_eta/D");
	_trout[ic]->Branch("HT",&m_HT,"HT/D");
	_trout[ic]->Branch("njet",&m_njet,"njet/I");
	_trout[ic]->Branch("Hb1_Hb2_dr",&m_Hb1_Hb2_dr,"Hb1_Hb2_dr/D");
	_trout[ic]->Branch("H_nu_dr",&m_H_nu_dr,"H_nu_dr/D");
	_trout[ic]->Branch("H_l_dr",&m_H_l_dr,"H_l_dr/D");
	_trout[ic]->Branch("W_m",&m_W_m,"W_m/D");
	_trout[ic]->Branch("W_pt",&m_W_pt,"W_pt/D");
	_trout[ic]->Branch("W_eta",&m_W_eta,"W_eta/D");
	_trout[ic]->Branch("chi2",&m_chi2,"chi2/D");
	_trout[ic]->Branch("l_charge",&m_l_charge,"l_charge/I");
	
	_trout[ic]->Branch("TTbar_topLep_m",&m_TTbar_topLep_m,"TTbar_topLep_m/D");
	_trout[ic]->Branch("TTbar_topHad_m",&m_TTbar_topHad_m,"TTbar_topHad_m/D");
	_trout[ic]->Branch("TTbar_topLep_pt",&m_TTbar_topLep_pt,"TTbar_topLep_pt/D");
	_trout[ic]->Branch("TTbar_topHad_pt",&m_TTbar_topHad_pt,"TTbar_topHad_pt/D");
	_trout[ic]->Branch("TTbar_topLep_eta",&m_TTbar_topLep_eta,"TTbar_topLep_eta/D");
	_trout[ic]->Branch("TTbar_topHad_eta",&m_TTbar_topHad_eta,"TTbar_topHad_eta/D");
	_trout[ic]->Branch("TTbar_WLep_m",&m_TTbar_WLep_m,"TTbar_WLep_m/D");
	_trout[ic]->Branch("TTbar_WHad_m",&m_TTbar_WHad_m,"TTbar_WHad_m/D");
	_trout[ic]->Branch("TTbar_WLep_pt",&m_TTbar_WLep_pt,"TTbar_WLep_pt/D");
	_trout[ic]->Branch("TTbar_WHad_pt",&m_TTbar_WHad_pt,"TTbar_WHad_pt/D");
	_trout[ic]->Branch("TTbar_WLep_eta",&m_TTbar_WLep_eta,"TTbar_WLep_eta/D");
	_trout[ic]->Branch("TTbar_WHad_eta",&m_TTbar_WHad_eta,"TTbar_WHad_eta/D");
	_trout[ic]->Branch("TTbar_tbLep_tWLep_Dr",&m_TTbar_tbLep_tWLep_Dr,"TTbar_tbLep_tWLep_Dr/D");
	_trout[ic]->Branch("TTbar_tbHad_tWHad_Dr",&m_TTbar_tbHad_tWHad_Dr,"TTbar_tbHad_tWHad_Dr/D");
	_trout[ic]->Branch("TTbar_tWj1_tWj2_Dr",&m_TTbar_tWj1_tWj2_Dr,"TTbar_tWj1_tWj2_Dr/D");
	_trout[ic]->Branch("TTbar_chi2",&m_TTbar_chi2,"TTbar_chi2/D");
     }   
*/   
   _s_Hist = new std::vector<std::pair<std::vector<std::string>,double*> >();
   _m1d_Hist = new std::map<std::string, TH1D*>();

   std::vector<double*> set_hist;
   set_hist.clear();

   // Ranges
/*   set_hist.push_back(RANGE::set_H_m);
   set_hist.push_back(RANGE::set_H_pt);
   set_hist.push_back(RANGE::set_H_eta);
   set_hist.push_back(RANGE::set_top_m);
   set_hist.push_back(RANGE::set_top_pt);
   set_hist.push_back(RANGE::set_top_eta);
   set_hist.push_back(RANGE::set_W_m);
   set_hist.push_back(RANGE::set_W_pt);
   set_hist.push_back(RANGE::set_W_eta);
   set_hist.push_back(RANGE::set_l_pt);
   set_hist.push_back(RANGE::set_l_eta);
   set_hist.push_back(RANGE::set_nu_pt);
   set_hist.push_back(RANGE::set_nu_eta);
   set_hist.push_back(RANGE::set_Hb_pt);
   set_hist.push_back(RANGE::set_Hb_eta);
   set_hist.push_back(RANGE::set_topb_pt);
   set_hist.push_back(RANGE::set_topb_eta);
   set_hist.push_back(RANGE::set_Hb1_Hb2_dr);
   set_hist.push_back(RANGE::set_H_top_dr);
   set_hist.push_back(RANGE::set_l_nu_dr);
   set_hist.push_back(RANGE::set_W_topb_dr);
   set_hist.push_back(RANGE::set_Hb1_Hb2_costheta);
   set_hist.push_back(RANGE::set_H_top_costheta);
   set_hist.push_back(RANGE::set_l_nu_costheta);
   set_hist.push_back(RANGE::set_W_topb_costheta);
   set_hist.push_back(RANGE::set_HT);
   set_hist.push_back(RANGE::set_MET);
   set_hist.push_back(RANGE::set_njet);
   set_hist.push_back(RANGE::set_phi);
   set_hist.push_back(RANGE::set_phi);
   set_hist.push_back(RANGE::set_H_nu_dr);
   set_hist.push_back(RANGE::set_H_l_dr);*/
   set_hist.push_back(RANGE::set_chi2);
   set_hist.push_back(RANGE::set_H_m);
//   set_hist.push_back(RANGE::set_l_charge);
   
/*   set_hist.push_back(RANGE::set_top_m);
   set_hist.push_back(RANGE::set_top_m);
   set_hist.push_back(RANGE::set_top_pt);
   set_hist.push_back(RANGE::set_top_pt);
   set_hist.push_back(RANGE::set_top_eta);
   set_hist.push_back(RANGE::set_top_eta);
   set_hist.push_back(RANGE::set_W_m);
   set_hist.push_back(RANGE::set_W_m);
   set_hist.push_back(RANGE::set_W_pt);
   set_hist.push_back(RANGE::set_W_pt);
   set_hist.push_back(RANGE::set_W_eta);
   set_hist.push_back(RANGE::set_W_eta);
   set_hist.push_back(RANGE::set_W_topb_dr);
   set_hist.push_back(RANGE::set_W_topb_dr);
   set_hist.push_back(RANGE::set_W_topb_dr);
   set_hist.push_back(RANGE::set_chi2);
   set_hist.push_back(RANGE::set_MVA);*/
   
   std::string titl;

   for(int s=0;s<sel_n;s++)
     {
	for(int t=0;t<type_n;t++)
	  {
	     for(int c=0;c<chan_n;c++)
	       {
		  for(int h=0;h<histname_n;h++)
		    {
		       std::string hn = histname[h]+chan[c]+"_"+sel[s]+"_"+type[t];
		       hname.push_back(hn);
				 
		       for(int s=0;s<sys_n;s++)
			 {
			    titl = hn+sys[s];
			    std::vector<std::string> names;
			    names.clear();
			    names.push_back(titl);
			    names.push_back(sys[s]);
			    
			    _s_Hist->push_back(std::make_pair(names,set_hist.at(h)));
			 }
		    }		  
	       }
	  }
     }   
   
   for(int i=0;i<_s_Hist->size();i++)
     {
	TH1D *_h1d = new TH1D(_s_Hist->at(i).first.at(0).c_str(),
			      _s_Hist->at(i).first.at(0).c_str(),
			      _s_Hist->at(i).second[0],
			      _s_Hist->at(i).second[1],
			      _s_Hist->at(i).second[2]);
	
	_h1d->Sumw2();
	
	_m1d_Hist->insert(std::pair<std::string,TH1D*>(_s_Hist->at(i).first.at(0),_h1d));
     }

   for(int ss=0;ss<sel_n;ss++)
     {
	for(int t=0;t<type_n;t++)
	  {
	     for(int c=0;c<chan_n;c++)
	       {
		  for(int s=0;s<sys_n;s++)
		    {
		       for(int h=0;h<histname_n;h++)
			 {
			    histNAMES[c][t][ss][h][s] =
			      histname[h]+chan[c]+"_"+sel[ss]+"_"+type[t]+sys[s];
			 }		       
		    }		  
	       }
	  }
     }

   std::cout << "Hist initialisation done" << std::endl;
}

void Hist::fill()
{
   float w = _v_Event->at(0).mc_weight();
   
   bool isTrigElec = _v_Event->at(0).isTrigElec();
   bool isTrigMuon = _v_Event->at(0).isTrigMuon();
   bool isSignal = _v_Event->at(0).isSignal();
   
   bool isData = _v_Event->at(0).isData();                                                                              

   float xsec = _v_Event->at(0).xsec();
   float noe = _v_Event->at(0).noe();

   float wil = 12900.*xsec/noe;
   if( !isData ) w *= wil;

/*   if( !isSignal )
     {	
	if( !isTrigElec && !isTrigMuon ) return;
     }*/

   bool passTrig = 0;
   if( isData )
     {
	if( !isTrigElec && isTrigMuon ) passTrig = 1;
	else if( isTrigElec && !isTrigMuon ) passTrig = 1;
     }   
   else passTrig = 1;
   
   m_weight = w;

   _v_ElectronTight->clear();
   _v_ElectronLoose->clear();
   _v_MuonTight->clear();
   _v_MuonLoose->clear();
   _v_JetTight->clear();
   _v_BJetTight->clear();
   _v_NonBJetTight->clear();
   
   for(int i=0;i<_v_Electron->size();i++)
     {
	if( fabs(_v_Electron->at(i).eta()) > 2.4 ) continue;

	if( _v_Electron->at(i).isTight() )
	  {		 		 
	     _v_ElectronTight->push_back(_v_Electron->at(i));
	  }	
	else
	  {
	     _v_ElectronLoose->push_back(_v_Electron->at(i));
	  }	
     }       

   for(int i=0;i<_v_Muon->size();i++)
     {
	if( fabs(_v_Muon->at(i).eta()) > 2.4 ) continue;

	if( _v_Muon->at(i).isTight() )
	  {	     
	     _v_MuonTight->push_back(_v_Muon->at(i));
	  }	
	else
	  {
	     _v_MuonLoose->push_back(_v_Muon->at(i));
	  }	
     }      

//   std::sort(_v_Jet->begin(),_v_Jet->end(),Jet::sortBTagPredicate);
   
   for(int i=0;i<_v_Jet->size();i++)
     {
	if( fabs(_v_Jet->at(i).eta()) > 2.4 ) continue;

	if( _v_Jet->at(i).isTight() )
	  {	     
	     _v_JetTight->push_back(_v_Jet->at(i));
	     
	     //	if( _v_Jet->at(i).CSVv2() >= 0.605 ) _v_BJetTight->push_back(_v_Jet->at(i));
	     //	if( i < 2 && _v_Jet->at(i).CSVv2() >= 0.890 ) _v_BJetTight->push_back(_v_Jet->at(i));
	     if( _v_Jet->at(i).CSVv2() >= 0.800 ) _v_BJetTight->push_back(_v_Jet->at(i));
	     else _v_NonBJetTight->push_back(_v_Jet->at(i));
	     //	if( _v_Jet->at(i).CSVv2() >= 0.970 ) _v_BJetTight->push_back(_v_Jet->at(i));
	  }	
     }      
   
   int id = _v_Event->at(0).id();
   int run = _v_Event->at(0).run();
   int lumi = _v_Event->at(0).lumi();
   
   float metpt = _v_Event->at(0).metpt();
   float metphi = _v_Event->at(0).metphi();
   
   int njets = _v_JetTight->size();
   int nbjets = _v_BJetTight->size();
   
   int nElecLoose = _v_ElectronLoose->size();
   int nMuonLoose = _v_MuonLoose->size();

   int nElecTight = _v_ElectronTight->size();
   int nMuonTight = _v_MuonTight->size();
   
   bool is1L = (nElecTight+nMuonTight == 1);
   bool is1L_looseVETO = (is1L && nElecLoose == 0 && nMuonLoose == 0);
   bool is1E = (nElecTight == 1 && is1L_looseVETO);
   bool is1M = (nMuonTight == 1 && is1L_looseVETO);
   
   passSel_all = 0x0;
   passSel_all |= (is1L_looseVETO && njets >= 3 && nbjets == 2)   << 0;
   passSel_all |= (is1L_looseVETO && njets == 3 && nbjets == 3)   << 1;
   passSel_all |= (is1L_looseVETO && njets >= 4 && nbjets == 3)   << 2;

   passSel_e = 0x0;
   passSel_m = 0x0;
   for(int i=0;i<=3;i++)
     {	
	passSel_e |= (CHECK_BIT(passSel_all,i) && is1E) << i;
	passSel_m |= (CHECK_BIT(passSel_all,i) && is1M) << i;
     }   
   
   bool chan_pass[chan_n];
   for(int c=0;c<chan_n;c++)
     {	
	chan_pass[c] = 0;
	if( (chan[c] == "all") ||
	    (chan[c] == "e" && is1E) ||
	    (chan[c] == "m" && is1M)
	  )
	  chan_pass[c] = 1;
     }   
   
   // Selection crtieria for plots
   bool pass = CHECK_BIT(passSel_all,2);
   
   if( pass )
     {
	_trec->setElectron(_v_ElectronTight);
	_trec->setMuon(_v_MuonTight);
	_trec->setJet(_v_JetTight);
	_trec->setBJet(_v_BJetTight);
	_trec->setNonBJet(_v_NonBJetTight);
	_trec->setEvent(_v_Event);
	_trec->setLepton(_v_Lepton);

	// top reconstruction
	_trec->run();	
	
/*	  {	     
	     _mva->setVariable_H_m(_H_p4.M());
	     _mva->setVariable_H_eta(_H_p4.PseudoRapidity());
	     _mva->setVariable_top_m(_top_p4.M());
	     _mva->setVariable_top_pt(_top_p4.Pt());
	     _mva->setVariable_top_eta(_top_p4.PseudoRapidity());
	     _mva->setVariable_Hb1_Hb2_dr(_Hb1_p4.DeltaR(_Hb2_p4));
	     _mva->setVariable_W_m(_W_p4.M());
	     _mva->setVariable_H_nu_dr(_H_p4.DeltaR(_nu_p4));
	     _mva->setVariable_H_l_dr(_H_p4.DeltaR(_l_p4));
	     _mva->setVariable_chi2(_trec->chi2());
	     _mva->setVariable_l_charge(_v_Lepton->at(0).charge());
	     _mva->setVariable_TTbar_chi2(_trec->chi2TTbar());
	     _mva->setVariable_TTbar_topLep_m(_topLep_TTbar_p4.M());
	     _mva->setVariable_TTbar_tbLep_tWLep_Dr(_topbLep_TTbar_p4.DeltaR(_WLep_TTbar_p4));
	     _mva->setVariable_TTbar_tbHad_tWHad_Dr(_topbHad_TTbar_p4.DeltaR(_WHad_TTbar_p4));
	
	     // Evaluate MVA discriminator
	     _mva->run();
	  }*/
	
	bool sel_pass[sel_n];
	for(int c=0;c<sel_n;c++)
	  {	
//	     sel_pass[c] = 0;
//	     if( sel[c] == "TopTopLepHbb" && )
	       sel_pass[c] = 1;
	  }   
	     
	for(int isys=0;isys<sys_n;isys++)
	  {	
	     double sfj = w;
	     
	     // 1d
	     std::vector<std::string> histNAMESSEL;
	     std::vector<int> histSYS;
	     std::vector<int> histVAR;
	     
	     for(int ih=0;ih<histname_n;ih++)
	       {
		  for(int ic=0;ic<chan_n;ic++)
		    {
		       if( !chan_pass[ic] ) continue;
		       
		       for(int is=0;is<sel_n;is++)
			 {
			    if( !sel_pass[is] ) continue;

			    if( ih == 0 && is == 0 && isys == 0 )
			      {
				 fillTree(ic);
			      }				 
				 
			    // [CHAN][TYPE][SEL][VAR][2*(NSYS-1)+1]
			    histNAMESSEL.push_back(histNAMES[ic][0][is][ih][isys]);
			    histSYS.push_back(isys);
			    histVAR.push_back(ih);
			 }		       
		    }		       
	       }

	     int nHISTSEL = histNAMESSEL.size();
	     for(int ih=0;ih<nHISTSEL;ih++)
	       {		       
		  TH1D *h = _m1d_Hist->find(histNAMESSEL.at(ih))->second;
		  
		  int hidx = ih;
		  std::string varName = histname[histVAR[hidx]];
		  fillHisto1D(h,sfj,sys[histSYS[hidx]],0,varName);
	       }
	  }
     }
   
   fillPassSel(_h_PassSel_all,_h_PassSel_e,_h_PassSel_m,w);
}

void Hist::close()
{
   _fout->Write();
   _fout->Close();
//   _fevc.close();
   _fevcVal.close();
   
//   delete rnd;
}

void Hist::fillTree(int ic)
{
/*   m_H_m = _H_p4.M();
   m_H_pt = (_resTop) ? _H_p4.Pt() : -666.;
   m_top_pt = (_resTop) ? _top_p4.Pt() : -666.;
   m_H_eta = (_resTop) ? _H_p4.PseudoRapidity() : -666.;
   m_top_eta = (_resTop) ? _top_p4.PseudoRapidity() : -666.;
   m_top_m = (_resTop) ? _top_p4.M() : -666.;
   
   float HT = 0.;
   int njets = _v_JetTight->size();
   for(int ij=0;ij<njets;ij++) 
     HT += _v_JetTight->at(ij).p4().Pt();
   
   m_HT = HT;
   m_njet = njets;
   m_Hb1_Hb2_dr = (_resTop) ? _Hb1_p4.DeltaR(_Hb2_p4) : -666.;
   m_H_nu_dr = (_resTop) ? _H_p4.DeltaR(_nu_p4) : -666.;
   m_H_l_dr = (_resTop) ? _H_p4.DeltaR(_l_p4) : -666.;
   m_W_m = (_resTop) ? _W_p4.M() : -666.;
   m_W_pt = (_resTop) ? _W_p4.Pt() : -666.;
   m_W_eta = (_resTop) ? _W_p4.PseudoRapidity() : -666.;
   m_chi2 = (_resTop) ? _trec->chi2() : -666.;
   m_l_charge = _v_Lepton->at(0).charge();

   m_TTbar_topLep_m = (_resTop) ? _topLep_TTbar_p4.M() : -666.;
   m_TTbar_topHad_m = (_resTop) ? _topHad_TTbar_p4.M() : -666.;
   m_TTbar_topLep_pt = (_resTop) ? _topLep_TTbar_p4.Pt() : -666.;
   m_TTbar_topHad_pt = (_resTop) ? _topHad_TTbar_p4.Pt() : -666.;
   m_TTbar_topLep_eta = (_resTop) ? _topLep_TTbar_p4.PseudoRapidity() : -666.;
   m_TTbar_topHad_eta = (_resTop) ? _topHad_TTbar_p4.PseudoRapidity() : -666.;
   m_TTbar_WLep_m = (_resTop) ? _WLep_TTbar_p4.M() : -666.;
   m_TTbar_WHad_m = (_resTop) ? _WHad_TTbar_p4.M() : -666.;
   m_TTbar_WLep_pt = (_resTop) ? _WLep_TTbar_p4.Pt() : -666.;
   m_TTbar_WHad_pt = (_resTop) ? _WHad_TTbar_p4.Pt() : -666.;
   m_TTbar_WLep_eta = (_resTop) ? _WLep_TTbar_p4.PseudoRapidity() : -666.;
   m_TTbar_WHad_eta = (_resTop) ? _WHad_TTbar_p4.PseudoRapidity() : -666.;
   m_TTbar_tbLep_tWLep_Dr = (_resTop) ? _WLep_TTbar_p4.DeltaR(_topbLep_TTbar_p4) : -666.;
   m_TTbar_tbHad_tWHad_Dr = (_resTop) ? _WHad_TTbar_p4.DeltaR(_topbHad_TTbar_p4) : -666.;
   m_TTbar_tWj1_tWj2_Dr = (_resTop) ? _topWj1_TTbar_p4.DeltaR(_topWj2_TTbar_p4) : -666.;
   m_TTbar_chi2 = (_resTop) ? _trec->chi2TTbar() : -666.;
   
   _trout[ic]->Fill();*/
}

bool Hist::printout(bool doPrint)
{
//	if( CHECK_BIT(passSel,1)
//	  )
//	  {	     
/*	     fprintf(_fevc,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %+2d  %6.2f %+4.2f %+4.2f    %6.1f  %+4.2f    %d \n",
		     run, lumi, id,
		     l1id, l1pt, l1eta, l1phi,
		     l2id, l2pt, l2eta, l2phi,
		     metpt, metphi,
		     njets);*/
	     
//	     _trout->Fill();
//	  }
//     }   
   
   return 1;
}

void Hist::fillHisto1D(TH1D *h,float sfj,std::string sys,int ilep,std::string varName)
{
/*   if( strcmp(varName.c_str(),"h_H_m_") == 0 )
     {	
	float H_m = (_resTop) ? _H_p4.M() : -666.;
	h->Fill(H_m,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_H_pt_") == 0 )
     {	
	float H_pt = (_resTop) ? _H_p4.Pt() : -666.;
	h->Fill(H_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_H_eta_") == 0 )
     {	
	float H_eta = (_resTop) ? _H_p4.PseudoRapidity() : -666.;
	h->Fill(H_eta,sfj);
     }
   else if( strcmp(varName.c_str(),"h_top_m_") == 0 )
     {	
	float top_m = (_resTop) ? _top_p4.M() : -666.;
	h->Fill(top_m,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_top_pt_") == 0 )
     {	
	float top_pt = (_resTop) ? _top_p4.Pt() : -666.;
	h->Fill(top_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_top_eta_") == 0 )
     {	
	float top_eta = (_resTop) ? _top_p4.PseudoRapidity() : -666.;
	h->Fill(top_eta,sfj);
     }
   else if( strcmp(varName.c_str(),"h_W_m_") == 0 )
     {	
	float W_m = (_resTop) ? _W_p4.M() : -666.;
	h->Fill(W_m,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_W_pt_") == 0 )
     {	
	float W_pt = (_resTop) ? _W_p4.Pt() : -666.;
	h->Fill(W_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_W_eta_") == 0 )
     {	
	float W_eta = (_resTop) ? _W_p4.PseudoRapidity() : -666.;
	h->Fill(W_eta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_l_pt_") == 0 )
     {	
	float l_pt = (_resTop) ? _l_p4.Pt() : -666.;
	h->Fill(l_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_l_eta_") == 0 )
     {	
	float l_eta = (_resTop) ? _l_p4.PseudoRapidity() : -666.;
	h->Fill(l_eta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_nu_pt_") == 0 )
     {	
	float nu_pt = (_resTop) ? _nu_p4.Pt() : -666.;
	h->Fill(nu_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_nu_eta_") == 0 )
     {	
	float nu_eta = (_resTop) ? _nu_p4.PseudoRapidity() : -666.;
	h->Fill(nu_eta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_Hb_pt_") == 0 )
     {	
	float Hb1_pt = (_resTop) ? _Hb1_p4.Pt() : -666.;
	h->Fill(Hb1_pt,sfj);
	float Hb2_pt = (_resTop) ? _Hb2_p4.Pt() : -666.;
	h->Fill(Hb2_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_Hb_eta_") == 0 )
     {	
	float Hb1_eta = (_resTop) ? _Hb1_p4.PseudoRapidity() : -666.;
	h->Fill(Hb1_eta,sfj);
	float Hb2_eta = (_resTop) ? _Hb2_p4.PseudoRapidity() : -666.;
	h->Fill(Hb2_eta,sfj);
     }
   else if( strcmp(varName.c_str(),"h_topb_pt_") == 0 )
     {	
	float topb_pt = (_resTop) ? _topb_p4.Pt() : -666.;
	h->Fill(topb_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_topb_eta_") == 0 )
     {	
	float topb_eta = (_resTop) ? _topb_p4.PseudoRapidity() : -666.;
	h->Fill(topb_eta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_Hb1_Hb2_dr_") == 0 )
     {	
	float Hb1_Hb2_dr = (_resTop) ? _Hb1_p4.DeltaR(_Hb2_p4) : -666.;
	h->Fill(Hb1_Hb2_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_H_top_dr_") == 0 )
     {	
	float H_top_dr = (_resTop) ? _H_p4.DeltaR(_top_p4) : -666.;
	h->Fill(H_top_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_l_nu_dr_") == 0 )
     {	
	float l_nu_dr = (_resTop) ? _l_p4.DeltaR(_nu_p4) : -666.;
	h->Fill(l_nu_dr,sfj);
     }
   else if( strcmp(varName.c_str(),"h_W_topb_dr_") == 0 )
     {	
	float W_topb_dr = (_resTop) ? _W_p4.DeltaR(_topb_p4) : -666.;
	h->Fill(W_topb_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_Hb1_Hb2_costheta_") == 0 )
     {	
	float Hb1_Hb2_costheta = (_resTop) ? cos(_Hb1_p4.Angle(_Hb2_p4.Vect())) : -666.;
	h->Fill(Hb1_Hb2_costheta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_H_top_costheta_") == 0 )
     {	
	float H_top_costheta = (_resTop) ? cos(_H_p4.Angle(_top_p4.Vect())) : -666.;
	h->Fill(H_top_costheta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_l_nu_costheta_") == 0 )
     {	
	float l_nu_costheta = (_resTop) ? cos(_l_p4.Angle(_nu_p4.Vect())) : -666.;
	h->Fill(l_nu_costheta,sfj);
     }
   else if( strcmp(varName.c_str(),"h_W_topb_costheta_") == 0 )
     {	
	float W_topb_costheta = (_resTop) ? cos(_W_p4.Angle(_topb_p4.Vect())) : -666.;
	h->Fill(W_topb_costheta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_HT_") == 0 )
     {
	float HT = 0.;
	int njets = _v_JetTight->size();
	for(int ij=0;ij<njets;ij++) 
	  HT += _v_JetTight->at(ij).p4().Pt();
	h->Fill(HT,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_MET_") == 0 )
     {
	float metpt = _v_Event->at(0).metpt();
	h->Fill(metpt,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_njet_") == 0 )
     {
	int njets = _v_JetTight->size();
	h->Fill(njets,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_nu_phi_") == 0 )
     {	
	float nu_phi = (_resTop) ? _nu_p4.Phi() : -666.;
	h->Fill(nu_phi,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_MET_phi_") == 0 )
     {
	float metphi = _v_Event->at(0).metphi();
	h->Fill(metphi,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_H_nu_dr_") == 0 )
     {	
	float H_nu_dr = (_resTop) ? _H_p4.DeltaR(_nu_p4) : -666.;
	h->Fill(H_nu_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_H_l_dr_") == 0 )
     {	
	float H_l_dr = (_resTop) ? _H_p4.DeltaR(_l_p4) : -666.;
	h->Fill(H_l_dr,sfj);
     }*/
   if( strcmp(varName.c_str(),"h_chi2_TOPTOPLEPHBB_") == 0 )
     {	
	h->Fill(_trec->chi2_TOPTOPLEPHBB(),sfj);
     }
   else if( strcmp(varName.c_str(),"h_HiggsMass_TOPTOPLEPHBB_") == 0 )
     {	
	h->Fill(_trec->Higgs_TOPTOPLEPHBB_p4().M(),sfj);
     }	     
/*   else if( strcmp(varName.c_str(),"h_l_charge_") == 0 )
     {	
	h->Fill(_v_Lepton->at(0).charge(),sfj);
     }

   else if( strcmp(varName.c_str(),"h_TTbar_topLep_m_") == 0 )
     {	
	float TTbar_top_m = (_resTop) ? _topLep_TTbar_p4.M() : -666.;
	h->Fill(TTbar_top_m,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_TTbar_topHad_m_") == 0 )
     {	
	float TTbar_top_m = (_resTop) ? _topLep_TTbar_p4.M() : -666.;
	h->Fill(TTbar_top_m,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_TTbar_topLep_pt_") == 0 )
     {	
	float TTbar_top_pt = (_resTop) ? _topLep_TTbar_p4.Pt() : -666.;
	h->Fill(TTbar_top_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_TTbar_topHad_pt_") == 0 )
     {	
	float TTbar_top_pt = (_resTop) ? _topLep_TTbar_p4.Pt() : -666.;
	h->Fill(TTbar_top_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_TTbar_topLep_eta_") == 0 )
     {	
	float TTbar_top_eta = (_resTop) ? _topLep_TTbar_p4.PseudoRapidity() : -666.;
	h->Fill(TTbar_top_eta,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_TTbar_topHad_eta_") == 0 )
     {	
	float TTbar_top_eta = (_resTop) ? _topLep_TTbar_p4.PseudoRapidity() : -666.;
	h->Fill(TTbar_top_eta,sfj);
     }	     

   else if( strcmp(varName.c_str(),"h_TTbar_WLep_m_") == 0 )
     {	
	float TTbar_W_m = (_resTop) ? _WLep_TTbar_p4.M() : -666.;
	h->Fill(TTbar_W_m,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_TTbar_WHad_m_") == 0 )
     {	
	float TTbar_W_m = (_resTop) ? _WLep_TTbar_p4.M() : -666.;
	h->Fill(TTbar_W_m,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_TTbar_WLep_pt_") == 0 )
     {	
	float TTbar_W_pt = (_resTop) ? _WLep_TTbar_p4.Pt() : -666.;
	h->Fill(TTbar_W_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_TTbar_WHad_pt_") == 0 )
     {	
	float TTbar_W_pt = (_resTop) ? _WLep_TTbar_p4.Pt() : -666.;
	h->Fill(TTbar_W_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_TTbar_WLep_eta_") == 0 )
     {	
	float TTbar_W_eta = (_resTop) ? _WLep_TTbar_p4.PseudoRapidity() : -666.;
	h->Fill(TTbar_W_eta,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_TTbar_WHad_eta_") == 0 )
     {	
	float TTbar_W_eta = (_resTop) ? _WLep_TTbar_p4.PseudoRapidity() : -666.;
	h->Fill(TTbar_W_eta,sfj);
     }	     

   else if( strcmp(varName.c_str(),"h_TTbar_tbLep_tWLep_Dr_") == 0 )
     {	
	float W_topb_dr = (_resTop) ? _WLep_TTbar_p4.DeltaR(_topbLep_TTbar_p4) : -666.;
	h->Fill(W_topb_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_TTbar_tbHad_tWHad_Dr_") == 0 )
     {	
	float W_topb_dr = (_resTop) ? _WHad_TTbar_p4.DeltaR(_topbHad_TTbar_p4) : -666.;
	h->Fill(W_topb_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_TTbar_tWj1_tWj2_Dr_") == 0 )
     {	
	float topWj1_topWj2_dr = (_resTop) ? _topWj1_TTbar_p4.DeltaR(_topWj2_TTbar_p4) : -666.;
	h->Fill(topWj1_topWj2_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_TTbar_chi2_") == 0 )
     {	
	h->Fill(_trec->chi2TTbar(),sfj);
     }
   else if( strcmp(varName.c_str(),"h_MVA_") == 0 )
     {	
	float mvaDisc = (_resTop) ? _mva->disc() : -666.;
	h->Fill(mvaDisc,sfj);
     }*/
}

void Hist::fillPassSel(TH1D *h,TH1D *he,TH1D *hm,float w)
{
   int nSel = h->GetXaxis()->GetNbins();
   for(int i=0;i<nSel;i++)
     {	
	bool pass = CHECK_BIT(passSel_all,i);
	if( pass ) h->Fill(i,w);

	bool pass_e = CHECK_BIT(passSel_e,i);
	if( pass_e ) he->Fill(i,w);

	bool pass_m = CHECK_BIT(passSel_m,i);
	if( pass_m ) hm->Fill(i,w);
     }   
}
