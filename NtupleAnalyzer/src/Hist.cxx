#include "../include/Hist.h"

#include "TRandom3.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/type_traits.hpp>

Hist::Hist(std::string home)
{
   help = new Helper();
   
   _home = home;
   
   _recAlg = 3; // 0 - mbb, 1 - mt, 2 - mbb&mt, 3 - top
   
//   std::string foutlog = "log/"+std::string(flog);
   std::string foutlog = "log/list.txt";
   _fevc = fopen(foutlog.c_str(),"w");
//   std::string foutlogVal = "log/"+std::string(flog)+".val";
   std::string foutlogVal = "log/list.val";
   _fevcVal.open(foutlogVal.c_str());
   
   _v_ElectronTight = new std::vector<Electron>;
   _v_MuonTight = new std::vector<Muon>;
//   _v_LeptonTight = new std::vector<Lepton>;
   _v_JetTight = new std::vector<Jet>;
   _v_BJetTight = new std::vector<Jet>;
}

Hist::~Hist()
{
   delete _v_ElectronTight;
   delete _v_MuonTight;
   delete _v_JetTight;
   delete _v_BJetTight;

   delete help;
   delete _trec;
}

void Hist::init()
{
   rnd = new TRandom3(666);
   
   std::string foutput = _home+"/"+std::string(flog)+".root";
   _fout = new TFile(foutput.c_str(),"RECREATE");

   _trec = new TopReco(_home,0,_fout);
   _trec->init();
   
   _h_PassSel = new TH1D("h_PassSel","h_PassSel",10,0.,10.);

   hname.clear(); 

   histname_n = 34;
   histname[0] = "h_H_m_";
   histname[1] = "h_H_pt_";
   histname[2] = "h_H_eta_";
   histname[3] = "h_top_m_";
   histname[4] = "h_top_pt_";
   histname[5] = "h_top_eta_";
   histname[6] = "h_W_m_";
   histname[7] = "h_W_pt_";
   histname[8] = "h_W_eta_";
   histname[9] = "h_l_pt_";
   histname[10] = "h_l_eta_";
   histname[11] = "h_nu_pt_";
   histname[12] = "h_nu_eta_";
   histname[13] = "h_Hb_pt_";
   histname[14] = "h_Hb_eta_";
   histname[15] = "h_topb_pt_";
   histname[16] = "h_topb_eta_";
   histname[17] = "h_Hb1_Hb2_dr_";
   histname[18] = "h_H_top_dr_";
   histname[19] = "h_l_nu_dr_";
   histname[20] = "h_W_topb_dr_";
   histname[21] = "h_Hb1_Hb2_costheta_";
   histname[22] = "h_H_top_costheta_";
   histname[23] = "h_l_nu_costheta_";
   histname[24] = "h_W_topb_costheta_";
   histname[25] = "h_HT_";
   histname[26] = "h_MET_";
   histname[27] = "h_njet_";
   histname[28] = "h_nu_phi_";
   histname[29] = "h_MET_phi_";
   histname[30] = "h_H_nu_dr_";
   histname[31] = "h_H_l_dr_";
   histname[32] = "h_chi2_";
   histname[33] = "h_l_charge_";

   type_n = 1;
//   type[0] = "nonQCD";
//   type[1] = "QCD";
   type[0] = "ALL";

   sel_n = 1;
   sel[0] = "nosel";
//   sel[2] = "bjge2";
//   sel[0] = "bjge3";
//   sel[0] = "bjge3";
//   sel[5] = "bjge3_mH";
//   sel[6] = "bjge3_mH_jveto";

   chan_n = 2;
   chan[0] = "e";
   chan[1] = "m";
   
   jets_n = 1;
   jets[0]  = "bjge3";
   
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
     }   
   
   _s_Hist = new std::vector<std::pair<std::vector<std::string>,double*> >();
   _m1d_Hist = new std::map<std::string, TH1D*>();

   std::vector<double*> set_hist;
   set_hist.clear();

   // Ranges
   set_hist.push_back(RANGE::set_H_m);
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
   set_hist.push_back(RANGE::set_H_l_dr);
   set_hist.push_back(RANGE::set_chi2);
   set_hist.push_back(RANGE::set_l_charge);
   
   std::string titl;

   for(int j=0;j<jets_n;j++)
     {	
	for(int s=0;s<sel_n;s++)
	  {
	     for(int t=0;t<type_n;t++)
	       {
		  for(int c=0;c<chan_n;c++)
		    {
		       for(int h=0;h<histname_n;h++)
			 {
			    std::string hn = histname[h]+chan[c]+"_"+jets[j]+"_"+sel[s]+"_"+type[t];
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

   for(int j=0;j<jets_n;j++)
     {	
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
				 histNAMES[j][c][t][ss][h][s] =
				   histname[h]+chan[c]+"_"+jets[j]+"_"+sel[ss]+"_"+type[t]+sys[s];
			      }
			 }		       
		    }		  
	       }
	  }
     }

   std::cout << "Hist initialisation done" << std::endl;
}

void Hist::fill()
{
   float w = _v_Event->at(0).w();

   _v_ElectronTight->clear();
   _v_MuonTight->clear();
   _v_JetTight->clear();
   _v_BJetTight->clear();
   
   for(int i=0;i<_v_Electron->size();i++)
     {
	if( _v_Electron->at(i).pass_ID_medium() && 
	    (_v_Electron->at(i).iso() < 0.15) &&
	    (_v_Electron->at(i).pt() > 20) )
	  _v_ElectronTight->push_back(_v_Electron->at(i));
     }       

   for(int i=0;i<_v_Muon->size();i++)
     {
	if( _v_Muon->at(i).idTight() &&
	    (_v_Muon->at(i).iso() < 0.15) &&
	    (_v_Muon->at(i).pt() > 20) )
	  _v_MuonTight->push_back(_v_Muon->at(i));
     }      

   for(int i=0;i<_v_Jet->size();i++)
     {
	if( _v_Jet->at(i).isTight() && _v_Jet->at(i).pt() > 20. &&
	    fabs(_v_Jet->at(i).eta()) < 2.4 &&
	    _v_Jet->at(i).idMedium() )
	  {	     
	     _v_JetTight->push_back(_v_Jet->at(i));
//	     if( _v_Jet->at(i).CSV() >= 0.898 ) _v_BJetTight->push_back(_v_Jet->at(i));
	     if( _v_Jet->at(i).CSV() >= 0.679 ) _v_BJetTight->push_back(_v_Jet->at(i));
//	     if( _v_Jet->at(i).CSV() >= 0.244 ) _v_BJetTight->push_back(_v_Jet->at(i));
	  }	
     }      
   
   std::vector<Lepton> res = help->filterPt(20,20,20,
					    _v_ElectronTight,
					    _v_MuonTight);

   _v_Lepton = &res;
   
   _trec->setElectron(_v_ElectronTight);
   _trec->setMuon(_v_MuonTight);
   _trec->setJet(_v_JetTight);
   _trec->setBJet(_v_BJetTight);
   _trec->setEvent(_v_Event);
   _trec->setTruth(_v_Truth);
   _trec->setLepton(_v_Lepton);

   // top reconstruction
   _trec->run();
   
   int id = _v_Event->at(0).id();
   int run = _v_Event->at(0).run();
   int lumi = _v_Event->at(0).lumi();
   
   float metpt = _v_Event->at(0).metpt();
   float metphi = _v_Event->at(0).metphi();
	
   m_weight = _v_Event->at(0).w();
   
   int njets = _v_JetTight->size();
   int nbjets = _v_BJetTight->size();
   
   int nLep = _v_Lepton->size();
   // 1L
   bool is1L = (nLep == 1);
   bool is1E = (is1L && _v_Lepton->at(0).isElectron());
   bool is1M = (is1L && !_v_Lepton->at(0).isElectron());
   // 2L
   bool is2L = (nLep == 2);
   bool is2LM = (nLep >= 2);
   
   bool pass_met = (metpt > 25);
   
   passSel = 0x0;
   passSel |= 1   << 0;
   passSel |= is1L   << 1;
   passSel |= (is1L && nbjets >= 3)   << 2;

   bool chan_pass[chan_n];
   for(int c=0;c<chan_n;c++)
     {	
	chan_pass[c] = 0;
	if(( chan[c] == "e" && is1E ) ||
	   ( chan[c] == "m" && is1M ))
	  chan_pass[c] = 1;
     }   

   bool jets_pass[jets_n];
   for(int c=0;c<jets_n;c++)
     {	
	jets_pass[c] = 0;
	if(( jets[c] == "bjge3" && nbjets >= 3 ))
	  jets_pass[c] = 1;
     }   
   
   bool pass = CHECK_BIT(passSel,1);

   if( pass )
     {
	if( _recAlg == 0 )
	  {	     
	     _Hb1_p4 = _trec->Hb1_Mbb_p4();
	     _Hb2_p4 = _trec->Hb2_Mbb_p4();
	     _topb_p4 = _trec->topb_Mbb_p4();
	     _l_p4 = _trec->l_Mbb_p4();
	     _nu_p4 = _trec->nu_Mbb_p4();
	     _top_p4 = _trec->top_Mbb_p4();
	     _H_p4 = _trec->H_Mbb_p4();
	     _W_p4 = _trec->W_Mbb_p4();
	  }
	else if( _recAlg == 1 )
	  {	     
	     _Hb1_p4 = _trec->Hb1_MT_p4();
	     _Hb2_p4 = _trec->Hb2_MT_p4();
	     _topb_p4 = _trec->topb_MT_p4();
	     _l_p4 = _trec->l_MT_p4();
	     _nu_p4 = _trec->nu_MT_p4();
	     _top_p4 = _trec->top_MT_p4();
	     _H_p4 = _trec->H_MT_p4();
	     _W_p4 = _trec->W_MT_p4();
	  }
	else if( _recAlg == 2 )
	  {	     
	     _Hb1_p4 = _trec->Hb1_MbbMT_p4();
	     _Hb2_p4 = _trec->Hb2_MbbMT_p4();
	     _topb_p4 = _trec->topb_MbbMT_p4();
	     _l_p4 = _trec->l_MbbMT_p4();
	     _nu_p4 = _trec->nu_MbbMT_p4();
	     _top_p4 = _trec->top_MbbMT_p4();
	     _H_p4 = _trec->H_MbbMT_p4();
	     _W_p4 = _trec->W_MbbMT_p4();
	  }
	else if( _recAlg == 3 )
	  {	     
	     _Hb1_p4 = _trec->Hb1_Top_p4();
	     _Hb2_p4 = _trec->Hb2_Top_p4();
	     _topb_p4 = _trec->topb_Top_p4();
	     _l_p4 = _trec->l_Top_p4();
	     _nu_p4 = _trec->nu_Top_p4();
	     _top_p4 = _trec->top_Top_p4();
	     _H_p4 = _trec->H_Top_p4();
	     _W_p4 = _trec->W_Top_p4();
	  }	

	bool sel_pass[sel_n];
	for(int c=0;c<sel_n;c++)
	  {	
	     sel_pass[c] = 0;
	     if(
		(sel[c] == "nosel")
	       )
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
			    
			    for(int ij=0;ij<jets_n;ij++)
			      {
				 if( !jets_pass[ij] ) continue;

				 if( ih == 0 && is == 0 && ij == 0 && isys == 0 )
				   {
				      fillTree(ic);
				   }				 
				 
				 // [JETS][CHAN][TYPE][SEL][VAR][2*(NSYS-1)+1]
				 histNAMESSEL.push_back(histNAMES[ij][ic][0][is][ih][isys]);
				 histSYS.push_back(isys);
				 histVAR.push_back(ih);
			      }
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
   
   fillPassSel(_h_PassSel,w);
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
   m_H_m = _H_p4.M();
   m_H_pt = _H_p4.Pt();
   m_top_pt = _top_p4.Pt();
   m_H_eta = _H_p4.PseudoRapidity();
   m_top_eta = _top_p4.PseudoRapidity();
   m_top_m = _top_p4.M();
   
   float HT = 0.;
   int njets = _v_JetTight->size();
   for(int ij=0;ij<njets;ij++) 
     HT += _v_JetTight->at(ij).p4().Pt();
   
   m_HT = HT;
   m_njet = njets;
   m_Hb1_Hb2_dr = _Hb1_p4.DeltaR(_Hb2_p4);   
   m_H_nu_dr = _H_p4.DeltaR(_nu_p4);
   m_H_l_dr = _H_p4.DeltaR(_l_p4);
   m_W_m = _W_p4.M();
   m_W_pt = _W_p4.Pt();
   m_W_eta = _W_p4.PseudoRapidity();
   m_chi2 = _trec->chi2();
   m_l_charge = _v_Lepton->at(0).charge();
   
   _trout[ic]->Fill();
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
   if( strcmp(varName.c_str(),"h_H_m_") == 0 )
     {	
	float H_m = _H_p4.M();
	h->Fill(H_m,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_H_pt_") == 0 )
     {	
	float H_pt = _H_p4.Pt();
	h->Fill(H_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_H_eta_") == 0 )
     {	
	float H_eta = _H_p4.PseudoRapidity();
	h->Fill(H_eta,sfj);
     }
   else if( strcmp(varName.c_str(),"h_top_m_") == 0 )
     {	
	float top_m = _top_p4.M();
	h->Fill(top_m,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_top_pt_") == 0 )
     {	
	float top_pt = _top_p4.Pt();
	h->Fill(top_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_top_eta_") == 0 )
     {	
	float top_eta = _top_p4.PseudoRapidity();
	h->Fill(top_eta,sfj);
     }
   else if( strcmp(varName.c_str(),"h_W_m_") == 0 )
     {	
	float W_m = _W_p4.M();
	h->Fill(W_m,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_W_pt_") == 0 )
     {	
	float W_pt = _W_p4.Pt();
	h->Fill(W_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_W_eta_") == 0 )
     {	
	float W_eta = _W_p4.PseudoRapidity();
	h->Fill(W_eta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_l_pt_") == 0 )
     {	
	float l_pt = _l_p4.Pt();
	h->Fill(l_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_l_eta_") == 0 )
     {	
	float l_eta = _l_p4.PseudoRapidity();
	h->Fill(l_eta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_nu_pt_") == 0 )
     {	
	float nu_pt = _nu_p4.Pt();
	h->Fill(nu_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_nu_eta_") == 0 )
     {	
	float nu_eta = _nu_p4.PseudoRapidity();
	h->Fill(nu_eta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_Hb_pt_") == 0 )
     {	
	float Hb1_pt = _Hb1_p4.Pt();
	h->Fill(Hb1_pt,sfj);
	float Hb2_pt = _Hb2_p4.Pt();
	h->Fill(Hb2_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_Hb_eta_") == 0 )
     {	
	float Hb1_eta = _Hb1_p4.PseudoRapidity();
	h->Fill(Hb1_eta,sfj);
	float Hb2_eta = _Hb2_p4.PseudoRapidity();
	h->Fill(Hb2_eta,sfj);
     }
   else if( strcmp(varName.c_str(),"h_topb_pt_") == 0 )
     {	
	float topb_pt = _topb_p4.Pt();
	h->Fill(topb_pt,sfj);
     }	     
   else if( strcmp(varName.c_str(),"h_topb_eta_") == 0 )
     {	
	float topb_eta = _topb_p4.PseudoRapidity();
	h->Fill(topb_eta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_Hb1_Hb2_dr_") == 0 )
     {	
	float Hb1_Hb2_dr = _Hb1_p4.DeltaR(_Hb2_p4);
	h->Fill(Hb1_Hb2_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_H_top_dr_") == 0 )
     {	
	float H_top_dr = _H_p4.DeltaR(_top_p4);
	h->Fill(H_top_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_l_nu_dr_") == 0 )
     {	
	float l_nu_dr = _l_p4.DeltaR(_nu_p4);
	h->Fill(l_nu_dr,sfj);
     }
   else if( strcmp(varName.c_str(),"h_W_topb_dr_") == 0 )
     {	
	float W_topb_dr = _W_p4.DeltaR(_topb_p4);
	h->Fill(W_topb_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_Hb1_Hb2_costheta_") == 0 )
     {	
	float Hb1_Hb2_costheta = cos(_Hb1_p4.Angle(_Hb2_p4.Vect()));
	h->Fill(Hb1_Hb2_costheta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_H_top_costheta_") == 0 )
     {	
	float H_top_costheta = cos(_H_p4.Angle(_top_p4.Vect()));
	h->Fill(H_top_costheta,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_l_nu_costheta_") == 0 )
     {	
	float l_nu_costheta = cos(_l_p4.Angle(_nu_p4.Vect()));
	h->Fill(l_nu_costheta,sfj);
     }
   else if( strcmp(varName.c_str(),"h_W_topb_costheta_") == 0 )
     {	
	float W_topb_costheta = cos(_W_p4.Angle(_topb_p4.Vect()));
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
	float nu_phi = _nu_p4.Phi();
	h->Fill(nu_phi,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_MET_phi_") == 0 )
     {
	float metphi = _v_Event->at(0).metphi();
	h->Fill(metphi,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_H_nu_dr_") == 0 )
     {	
	float H_nu_dr = _H_p4.DeltaR(_nu_p4);
	h->Fill(H_nu_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_H_l_dr_") == 0 )
     {	
	float H_l_dr = _H_p4.DeltaR(_l_p4);
	h->Fill(H_l_dr,sfj);
     }   
   else if( strcmp(varName.c_str(),"h_chi2_") == 0 )
     {	
	h->Fill(_trec->chi2(),sfj);
     }
   else if( strcmp(varName.c_str(),"h_l_charge_") == 0 )
     {	
	h->Fill(_v_Lepton->at(0).charge(),sfj);
     }
}

float Hist::getWmassBW(float mWmean,float GammaW)
{
   float mW = 0.;
   
   float max = BW(mWmean,mWmean,GammaW);
   
   while(1)
     {
	float r1 = rnd->Rndm();
	float r2 = rnd->Rndm();

	mW = mWmean - 3*GammaW + 6*GammaW*r1;
	if( BW(mW,mWmean,GammaW) > max*r2 ) break;
     }
   
   return mW;      
}

float Hist::BW(float mW,float mWmean,float GammaW)
{
   float f = mW*mW/sqrt(pow(mW*mW-mWmean*mWmean,2)+mW*mW*GammaW*GammaW);
   
   return f;
}

bool Hist::getNuMom(float Wmass,float px_l,float py_l,float pz_l,float E_l,
		    float px_nu,float py_nu,float &pz_nu1,float &pz_nu2)
{
   bool hasSolution = 0.;
   
   float a = sqrt(px_l*px_l+py_l*py_l);
   float b = pz_l;
   float d = sqrt(px_nu*px_nu+py_nu*py_nu);
   float f = E_l;
   
   float c = Wmass*Wmass/2+px_l*px_nu+py_l*py_nu;
   
   float racine = c*c*b*b-a*a*(d*d*f*f-c*c);
   
   if(racine >= 0) 
     {
	hasSolution = 1;
	pz_nu1 = (c*b+sqrt(racine))/a/a;
	pz_nu2 = (c*b-sqrt(racine))/a/a;
//	std::cout << "pz1=" << pz_nu1 << " pz2=" << pz_nu2 << std::endl;
     }   
   
   return hasSolution;
}

void Hist::fillPassSel(TH1D *h,float w)
{
   int nSel = h->GetXaxis()->GetNbins();
   for(int i=0;i<nSel;i++)
     {	
	bool pass = CHECK_BIT(passSel,i);
	if( pass ) h->Fill(i+1,w);
     }   
}
