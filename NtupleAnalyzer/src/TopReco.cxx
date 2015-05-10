#include "../include/TopReco.h"

#include "TRandom3.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/type_traits.hpp>

TopReco::TopReco(bool standalone,TFile *foutput)
{
   help = new Helper();
   
   _standalone = standalone;
   
   if( !_standalone ) _fout = foutput;
   
   _useTruthMET = 0;
   
   _v_ElectronTight = new std::vector<Electron>;
   _v_MuonTight = new std::vector<Muon>;
   _v_JetTight = new std::vector<Jet>;
   _v_BJetTight = new std::vector<Jet>;
}

TopReco::~TopReco()
{
   delete help;
   
   delete _v_ElectronTight;
   delete _v_MuonTight;
   delete _v_JetTight;
   delete _v_BJetTight;
}

void TopReco::init()
{
   rnd = new TRandom3(666);

   if( _standalone )
     {	
	std::string foutput = "hist/"+std::string(flog)+".root";
	_fout = new TFile(foutput.c_str(),"RECREATE");
     }
   
   std::string algName[4];
   algName[0] = "Mbb";
   algName[1] = "MT";
   algName[2] = "MbbMT";
   algName[3] = "Top";
   
   std::string mtype[3];
   mtype[0] = "all";
   mtype[1] = "pass";
   mtype[2] = "fail";

   std::string hname_matchAll = "h_matchAll";
   h_matchAll = new TH1F(hname_matchAll.c_str(),hname_matchAll.c_str(),4,-0.5,3.5);
   h_matchAll->Sumw2();

   std::string hname_topSol = "h_topSol";
   h_topSol = new TH1F(hname_topSol.c_str(),hname_topSol.c_str(),2,-0.5,1.5);
   h_topSol->Sumw2();
   
   for(int i=0;i<4;i++)
     {	
	std::string hname_match = "h_match_"+algName[i];
	h_match[i] = new TH1F(hname_match.c_str(),hname_match.c_str(),4,-0.5,3.5);
	h_match[i]->Sumw2();

	for(int j=0;j<3;j++)
	  {	     
	     std::string hname_H_m = "h_H_m_"+algName[i]+"_"+mtype[j];
	     h_H_m[i][j] = new TH1F(hname_H_m.c_str(),hname_H_m.c_str(),30,0.,200.);
	     h_H_m[i][j]->Sumw2();
	     
	     std::string hname_top_m = "h_top_m_"+algName[i]+"_"+mtype[j];
	     h_top_m[i][j] = new TH1F(hname_top_m.c_str(),hname_top_m.c_str(),30,50.,300.);
	     h_top_m[i][j]->Sumw2();
	     
	     std::string hname_W_m = "h_W_m_"+algName[i]+"_"+mtype[j];
	     h_W_m[i][j] = new TH1F(hname_W_m.c_str(),hname_W_m.c_str(),30,40.,120.);
	     h_W_m[i][j]->Sumw2();
	  }	
     }   
   
   std::cout << "TopReco initialisation done" << std::endl;
}

void TopReco::run()
{
   float w = _v_Event->at(0).w();

   _v_ElectronTight->clear();
   _v_MuonTight->clear();
   _v_JetTight->clear();
   _v_BJetTight->clear();

   std::vector<Lepton> res;
   
   if( _standalone )
     {	
	for(int i=0;i<_v_Electron->size();i++)
	  {
	     if( 
		_v_Electron->at(i).pass_ID_medium() && 
		(_v_Electron->at(i).iso() < 0.15) &&
		(_v_Electron->at(i).pt() > 20) )
	       _v_ElectronTight->push_back(_v_Electron->at(i));
	  }       
	
	for(int i=0;i<_v_Muon->size();i++)
	  {
	     if( 
		_v_Muon->at(i).idTight() &&
		(_v_Muon->at(i).iso() < 0.15) &&
		(_v_Muon->at(i).pt() > 20) )
	       _v_MuonTight->push_back(_v_Muon->at(i));
	  }      
	
	for(int i=0;i<_v_Jet->size();i++)
	  {
	     if( 
		_v_Jet->at(i).isTight() && 
		_v_Jet->at(i).pt() > 20. &&
		fabs(_v_Jet->at(i).eta()) < 2.4 &&
		_v_Jet->at(i).idMedium() )
	       {	     
		  _v_JetTight->push_back(_v_Jet->at(i));
		  //if( _v_Jet->at(i).CSV() >= 0.898 ) _v_BJetTight->push_back(_v_Jet->at(i));
		  if( _v_Jet->at(i).CSV() >= 0.679 ) _v_BJetTight->push_back(_v_Jet->at(i));
		  //if( _v_Jet->at(i).CSV() >= 0.244 ) _v_BJetTight->push_back(_v_Jet->at(i));
		  //_v_BJetTight->push_back(_v_Jet->at(i));
	       }	
	  }      

	res = help->filterPt(20,20,20,
			     _v_ElectronTight,
			     _v_MuonTight);
	
	_v_Lepton = &res;
     }
   else
     {
	for(int i=0;i<_v_Electron->size();i++)
	  {
	     _v_ElectronTight->push_back(_v_Electron->at(i));
	  }       
	
	for(int i=0;i<_v_Muon->size();i++)
	  {
	     _v_MuonTight->push_back(_v_Muon->at(i));
	  }      
	
	for(int i=0;i<_v_Jet->size();i++)
	  {
	     _v_JetTight->push_back(_v_Jet->at(i));
	  }      	

	for(int i=0;i<_v_BJet->size();i++)
	  {
	     _v_BJetTight->push_back(_v_BJet->at(i));
	  }      	
     }   
   
   int id = _v_Event->at(0).id();
   int run = _v_Event->at(0).run();
   int lumi = _v_Event->at(0).lumi();

   float metptTruth = -1.;
   float metphiTruth = -1.;
   std::vector<int> lab = _v_Truth->at(0).mc_truth_label();
   int nTruth = lab.size();
   
   _l_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _Hb1_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _Hb2_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _topb_truth_p4.SetPtEtaPhiE(0,0,0,0);

   _Hb1_IS_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _Hb2_IS_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _topb_IS_truth_p4.SetPtEtaPhiE(0,0,0,0);
   
   for(int it=0;it<nTruth;it++)
     {
	if( lab[it] == 421 )
	  {
	     metptTruth = _v_Truth->at(0).mc_truth_p4().at(it).Pt();
	     metphiTruth = _v_Truth->at(0).mc_truth_p4().at(it).Phi();
	  }
	else if( lab[it] == 1 )
	  {
	     _H_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
				      _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
				      _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
				      _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }	     
	else if( lab[it] == 18 )
	  {
	     _Hb1_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					_v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					_v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					_v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }	     
	else if( lab[it] == 19 )
	  {
	     _Hb2_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					_v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					_v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					_v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }	     
	else if( lab[it] == 41 )
	  {
	     _topb_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					 _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					 _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					 _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }
	else if( lab[it] == 420 )
	  {
	     _l_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
				      _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
				      _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
				      _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }
	else if( lab[it] == 18666 )
	  {
	     _Hb1_IS_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					   _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					   _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					   _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }	     
	else if( lab[it] == 19666 )
	  {
	     _Hb2_IS_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					   _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					   _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					   _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }	     
	else if( lab[it] == 41666 )
	  {
	     _topb_IS_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					    _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					    _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					    _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }
     }
   
   float metpt = _v_Event->at(0).metpt();
   float metphi = _v_Event->at(0).metphi();
   float metpx = metpt*cos(metphi);
   float metpy = metpt*sin(metphi);
   float metE = sqrt(metpx*metpx+metpy*metpy);

   if( _useTruthMET )
     {	
	metpt = metptTruth;
	metphi = metphiTruth;
     }   
   
   int njets = _v_JetTight->size();
   int nbjets = _v_BJetTight->size();
   
   int nLep = _v_Lepton->size();

   bool passGenFilt = 1;
   if( _Hb1_IS_truth_p4.Pt() < 20. || 
       _Hb2_IS_truth_p4.Pt() < 20. || 
       _topb_IS_truth_p4.Pt() < 20. ) passGenFilt = 0;
   if( fabs(_Hb1_IS_truth_p4.PseudoRapidity()) > 2.4 || 
       fabs(_Hb2_IS_truth_p4.PseudoRapidity()) > 2.4 ||
       fabs(_topb_IS_truth_p4.PseudoRapidity()) > 2.4 ) passGenFilt = 0;
   
   passGenFilt = passGenFilt || !_standalone;
   
   if( nLep == 1 && nbjets >= 3 && passGenFilt )
     {
	_l_p4.SetPtEtaPhiE(_v_Lepton->at(0).p4().Pt(),
			   _v_Lepton->at(0).p4().PseudoRapidity(),
			   _v_Lepton->at(0).p4().Phi(),
			   _v_Lepton->at(0).p4().E());			    
	
	_nu_p4.SetPtEtaPhiE(metpt,
			    0,
			    metphi,
			    metE);

	truthMatch();
	bool isMatchAll = (_Hb1_match_all && _Hb2_match_all && _topb_match_all);
	h_matchAll->Fill(0.,w);
	if( _Hb1_match_all && _Hb2_match_all ) h_matchAll->Fill(1.,w);
	if( _topb_match_all ) h_matchAll->Fill(2.,w);
	if( isMatchAll ) h_matchAll->Fill(3.,w);

	if( isMatchAll || !_standalone )
	  {
	     for(int i=0;i<4;i++)
	       {
		  _topb_p4.SetPtEtaPhiE(0,0,0,0);
		  _Hb1_p4.SetPtEtaPhiE(0,0,0,0);
		  _Hb2_p4.SetPtEtaPhiE(0,0,0,0);
		  
		  if( i == 0 ) Mbb();
		  else if( i == 1 ) MT();
		  else if( i == 2 ) MbbMT();
		  else if( i == 3 ) 
		    {
		       bool hasSol = Top();
		       h_topSol->Fill(hasSol,w);
		       if( !hasSol ) MbbMT();
		    }		  
		  
		  _H_p4 = _Hb1_p4+_Hb2_p4;
		  _W_p4 = _l_p4+_nu_p4;
		  _top_p4 = _W_p4+_topb_p4;

		  // store variables for output
		  if( i == 0 )
		    {
		       _topb_Mbb_p4 = _topb_p4;
		       _Hb1_Mbb_p4 = _Hb1_p4;
		       _Hb2_Mbb_p4 = _Hb2_p4;
		       _l_Mbb_p4 = _l_p4;
		       _nu_Mbb_p4 = _nu_p4;
		       _top_Mbb_p4 = _top_p4;
		       _H_Mbb_p4 = _H_p4;
		       _W_Mbb_p4 = _W_p4;		       
		    }
		  else if( i == 1 )
		    {
		       _topb_MT_p4 = _topb_p4;
		       _Hb1_MT_p4 = _Hb1_p4;
		       _Hb2_MT_p4 = _Hb2_p4;
		       _l_MT_p4 = _l_p4;
		       _nu_MT_p4 = _nu_p4;
		       _top_MT_p4 = _top_p4;
		       _H_MT_p4 = _H_p4;
		       _W_MT_p4 = _W_p4;		       
		    }		  
		  else if( i == 2 )
		    {
		       _topb_MbbMT_p4 = _topb_p4;
		       _Hb1_MbbMT_p4 = _Hb1_p4;
		       _Hb2_MbbMT_p4 = _Hb2_p4;
		       _l_MbbMT_p4 = _l_p4;
		       _nu_MbbMT_p4 = _nu_p4;
		       _top_MbbMT_p4 = _top_p4;
		       _H_MbbMT_p4 = _H_p4;
		       _W_MbbMT_p4 = _W_p4;		       
		    }		  
		  else if( i == 3 )
		    {
		       _topb_Top_p4 = _topb_p4;
		       _Hb1_Top_p4 = _Hb1_p4;
		       _Hb2_Top_p4 = _Hb2_p4;
		       _l_Top_p4 = _l_p4;
		       _nu_Top_p4 = _nu_p4;
		       _top_Top_p4 = _top_p4;
		       _H_Top_p4 = _H_p4;
		       _W_Top_p4 = _W_p4;		       
		    }		  
		  
		  truthMatchAlg();
		  
		  bool isMatch = (_Hb1_match && _Hb2_match && _topb_match);
		  h_match[i]->Fill(0.,w);
		  if( _Hb1_match && _Hb2_match ) h_match[i]->Fill(1.,w);
		  if( _topb_match ) h_match[i]->Fill(2.,w);
		  if( isMatch ) h_match[i]->Fill(3.,w);
		  
		  fill(i,w,isMatch);
	       }	
	  }	
     }   
}

void TopReco::Mbb()
{   
   float mbbDiff = 10E+10;
   
   int Hb1_idx = -1;
   int Hb2_idx = -1;
   int tb_idx = -1;
   
   int nbjets = _v_BJetTight->size();
   
   for(int ib=0;ib<nbjets;ib++)
     {
	for(int ibb=0;ibb<nbjets;ibb++)
	  {
	     if( ib == ibb ) continue;
	     float mbb = (_v_BJetTight->at(ib).p4()+_v_BJetTight->at(ibb).p4()).M();
	     if( fabs(mbb-125.) < mbbDiff ) 
	       {
		  mbbDiff = fabs(mbb-125.);
		  
		  Hb1_idx = ib;
		  Hb2_idx = ibb;
	       }		       
	  }
     }
   for(int ib=0;ib<nbjets;ib++)
     {
	if( Hb1_idx != ib && Hb2_idx != ib ) tb_idx = ib;
     }	     
   
   if( Hb1_idx >= 0 )
     {		  
	_Hb1_p4.SetPtEtaPhiE(_v_BJetTight->at(Hb1_idx).p4().Pt(),
			     _v_BJetTight->at(Hb1_idx).p4().PseudoRapidity(),
			     _v_BJetTight->at(Hb1_idx).p4().Phi(),
			     _v_BJetTight->at(Hb1_idx).p4().E());
     }	     
   if( Hb2_idx >= 0 )
     {		  
	_Hb2_p4.SetPtEtaPhiE(_v_BJetTight->at(Hb2_idx).p4().Pt(),
			     _v_BJetTight->at(Hb2_idx).p4().PseudoRapidity(),
			     _v_BJetTight->at(Hb2_idx).p4().Phi(),
			     _v_BJetTight->at(Hb2_idx).p4().E());
     }	     
   if( tb_idx >= 0 )
     {		  
	_topb_p4.SetPtEtaPhiE(_v_BJetTight->at(tb_idx).p4().Pt(),
			      _v_BJetTight->at(tb_idx).p4().PseudoRapidity(),
			      _v_BJetTight->at(tb_idx).p4().Phi(),
			      _v_BJetTight->at(tb_idx).p4().E());
     }
}

void TopReco::MT()
{   
   float mtDiff = 10E+10;
   
   int nbjets = _v_BJetTight->size();
	     
   int Hb1_idx = -1;
   int Hb2_idx = -1;
   int tb_idx = -1;
   
   float ET_nu = _l_p4.Et();
   float ET_l = _nu_p4.Et();
   
   for(int ib=0;ib<nbjets;ib++)
     {
	float px_b = _v_BJetTight->at(ib).p4().Px();
	float py_b = _v_BJetTight->at(ib).p4().Py();
	float px_nu = _nu_p4.Px();
	float py_nu = _nu_p4.Py();
	float px_l = _l_p4.Px();
	float py_l = _l_p4.Py();
	float m_b = _v_BJetTight->at(ib).p4().M();
	float ET_b = sqrt(px_b*px_b+py_b*py_b+m_b*m_b);
	float mt = pow(ET_nu+ET_l+ET_b,2)-
	  pow(px_b+px_nu+px_l,2)-
	  pow(py_b+py_nu+py_l,2);
	mt = sqrt(mt);
		  
	if( fabs(mt-173.) < mtDiff )
	  {
	     mtDiff = fabs(mt-173.);	     
	     tb_idx = ib;
	  }
     }
   for(int ib=0;ib<nbjets;ib++)
     {
	if( tb_idx != ib )
	  {				 
	     if( Hb1_idx < 0 ) Hb1_idx = ib;
	     else if( Hb2_idx < 0 ) Hb2_idx = ib;
	  }			    
     }
   
   if( tb_idx >= 0 )
     {		  
	_topb_p4.SetPtEtaPhiE(_v_BJetTight->at(tb_idx).p4().Pt(),
			      _v_BJetTight->at(tb_idx).p4().PseudoRapidity(),
			      _v_BJetTight->at(tb_idx).p4().Phi(),
			      _v_BJetTight->at(tb_idx).p4().E());
     }   
   if( Hb1_idx >= 0 )
     {		  
	_Hb1_p4.SetPtEtaPhiE(_v_BJetTight->at(Hb1_idx).p4().Pt(),
			     _v_BJetTight->at(Hb1_idx).p4().PseudoRapidity(),
			     _v_BJetTight->at(Hb1_idx).p4().Phi(),
			     _v_BJetTight->at(Hb1_idx).p4().E());
     }   
   if( Hb2_idx >= 0 )
     {		     
	_Hb2_p4.SetPtEtaPhiE(_v_BJetTight->at(Hb2_idx).p4().Pt(),
			     _v_BJetTight->at(Hb2_idx).p4().PseudoRapidity(),
			     _v_BJetTight->at(Hb2_idx).p4().Phi(),
			     _v_BJetTight->at(Hb2_idx).p4().E());
     }
}

void TopReco::MbbMT()
{   
   float mDiff = 10E+10;
   
   int Hb1_idx = -1;
   int Hb2_idx = -1;
   int tb_idx = -1;
   
   int nbjets = _v_BJetTight->size();
	     
   float ET_nu = _l_p4.Et();
   float ET_l = _nu_p4.Et();
	     
   for(int ib=0;ib<nbjets;ib++)
     {
	float px_b = _v_BJetTight->at(ib).p4().Px();
	float py_b = _v_BJetTight->at(ib).p4().Py();
	float px_nu = _nu_p4.Px();
	float py_nu = _nu_p4.Py();
	float px_l = _l_p4.Px();
	float py_l = _l_p4.Py();
	float m_b = _v_BJetTight->at(ib).p4().M();
	float ET_b = sqrt(px_b*px_b+py_b*py_b+m_b*m_b);
	float mt = pow(ET_nu+ET_l+ET_b,2)-
	  pow(px_b+px_nu+px_l,2)-
	  pow(py_b+py_nu+py_l,2);
	mt = sqrt(mt);
	
	for(int ibb=0;ibb<nbjets;ibb++)
	  {
	     for(int ibbb=0;ibbb<nbjets;ibbb++)
	       {
		  if( ib == ibb || ib == ibbb || ibb == ibbb ) continue;
		  
		  float mbb = (_v_BJetTight->at(ibb).p4()+_v_BJetTight->at(ibbb).p4()).M();

		  float totDiff = pow(mbb-125.,2)/pow(30.,2)+pow(mt-173.,2)/pow(40.,2);
		  
		  if( totDiff < mDiff )
		    {
		       mDiff = totDiff;
		       
		       Hb1_idx = ibb;
		       Hb2_idx = ibbb;
		       tb_idx = ib;
		    }			    
	       }		       
	  }
     }

   if( tb_idx >= 0 )
     {		  
	_topb_p4.SetPtEtaPhiE(_v_BJetTight->at(tb_idx).p4().Pt(),
			      _v_BJetTight->at(tb_idx).p4().PseudoRapidity(),
			      _v_BJetTight->at(tb_idx).p4().Phi(),
			      _v_BJetTight->at(tb_idx).p4().E());
     }   
   if( Hb1_idx >= 0 )
     {		  
	_Hb1_p4.SetPtEtaPhiE(_v_BJetTight->at(Hb1_idx).p4().Pt(),
			     _v_BJetTight->at(Hb1_idx).p4().PseudoRapidity(),
			     _v_BJetTight->at(Hb1_idx).p4().Phi(),
			     _v_BJetTight->at(Hb1_idx).p4().E());
     }   
   if( Hb2_idx >= 0 )
     {		     
	_Hb2_p4.SetPtEtaPhiE(_v_BJetTight->at(Hb2_idx).p4().Pt(),
			     _v_BJetTight->at(Hb2_idx).p4().PseudoRapidity(),
			     _v_BJetTight->at(Hb2_idx).p4().Phi(),
			     _v_BJetTight->at(Hb2_idx).p4().E());
     }
}

bool TopReco::Top()
{
   int nbjets = _v_BJetTight->size();

   int tb_idx = -1;
   int Hb1_idx = -1;
   int Hb2_idx = -1;
   
   int itry = 0;
   int nTryMax = 100;
   std::vector<float> v_pz_nu1;
   std::vector<float> v_pz_nu2;

   float px_nu = _nu_p4.Px();
   float py_nu = _nu_p4.Py();
   float px_l = _l_p4.Px();
   float py_l = _l_p4.Py();
   float pz_l = _l_p4.Pz();
   float E_l = _l_p4.E();

   bool hasSolution = 0;
   while( v_pz_nu1.size() < 100 )
     {	    
	if( itry > nTryMax ) break;
	float wmassGen = help->getWmassBW(rnd,80.4,2.1,50);
	float pz_nu1 = -1;
	float pz_nu2 = -1;
	bool foundNuMom = help->getNuMom(wmassGen,
					 px_l,py_l,pz_l,E_l,
					 px_nu,py_nu,pz_nu1,pz_nu2);
	if( foundNuMom ) 
	  {
	     v_pz_nu1.push_back(pz_nu1);
	     v_pz_nu2.push_back(pz_nu2);
	     hasSolution = 1;
	  }	     
	itry++;	     
     }
   
   const int nSol = v_pz_nu1.size();
	
   if( nSol > 0 )
     {
	float E_nu[nSol][2];
	float pz_nu[nSol][2];
	
	for(int in=0;in<nSol;in++)
	  {
	     pz_nu[in][0] = v_pz_nu1[in];
	     pz_nu[in][1] = v_pz_nu2[in];
	     
	     E_nu[in][0] = sqrt(px_nu*px_nu+py_nu*py_nu+v_pz_nu1[in]*v_pz_nu1[in]);
	     E_nu[in][1] = sqrt(px_nu*px_nu+py_nu*py_nu+v_pz_nu2[in]*v_pz_nu2[in]);
	  }	     

	float pt_bjet[100];
	float E_bjet[100];
	float eta_bjet[100];
	float phi_bjet[100];
	float px_bjet[100];
	float py_bjet[100];
	float pz_bjet[100];
	
	int nu_idx = -1;
	int nu12_idx = -1;
		  
	float mtopDiff = 10E+10;
		  
	for(int ib=0;ib<nbjets;ib++)
	  {
	     pt_bjet[ib] = _v_BJetTight->at(ib).pt();
	     E_bjet[ib] = _v_BJetTight->at(ib).E();
	     eta_bjet[ib] = _v_BJetTight->at(ib).eta();
	     phi_bjet[ib] = _v_BJetTight->at(ib).phi();
	     px_bjet[ib] = pt_bjet[ib]*cos(phi_bjet[ib]);
	     py_bjet[ib] = pt_bjet[ib]*sin(phi_bjet[ib]);
	     pz_bjet[ib] = pt_bjet[ib]*sinh(eta_bjet[ib]);
		       
	     for(int in=0;in<nSol;in++)
	       {
		  float totPz1 = pz_bjet[ib]+pz_nu[in][0]+pz_l;
		  float totPz2 = pz_bjet[ib]+pz_nu[in][1]+pz_l;
		  float totPzMin = totPz1;
		  int idMin = 0;
		  if( totPz2 < totPzMin )
		    {
		       idMin = 1;
		       totPzMin = totPz2;
		    }
			    
		  float totE = E_bjet[ib]+E_nu[in][idMin]+E_l;
		  float totPx = px_bjet[ib]+px_nu+px_l;
		  float totPy = py_bjet[ib]+py_nu+py_l;
		  float totPz = totPzMin;
		  float mW = pow(E_nu[in][idMin]+E_l,2)-pow(px_nu+px_l,2)-pow(py_nu+py_l,2)-pow(pz_nu[in][idMin]+pz_l,2);
		  float mtop = totE*totE-totPx*totPx-totPy*totPy-totPz*totPz;

		  if( mtop >= 0 )
		    {
		       mtop = sqrt(mtop);
		       mW = sqrt(mW);
		       
		       int Hb1i = -1;
		       int Hb2i = -1;
		       
		       for(int ibb=0;ibb<nbjets;ibb++)
			 {
			    if( ib != ibb )
			      {				 
				 if( Hb1i < 0 ) Hb1i = ibb;
				 else if( Hb2i < 0 ) Hb2i = ibb;
			      }
			 }

		       TLorentzVector hb1;
		       hb1.SetPtEtaPhiE(_v_BJetTight->at(Hb1i).p4().Pt(),
					_v_BJetTight->at(Hb1i).p4().PseudoRapidity(),
					_v_BJetTight->at(Hb1i).p4().Phi(),
					_v_BJetTight->at(Hb1i).p4().E());

		       TLorentzVector hb2;
		       hb2.SetPtEtaPhiE(_v_BJetTight->at(Hb2i).p4().Pt(),
					_v_BJetTight->at(Hb2i).p4().PseudoRapidity(),
					_v_BJetTight->at(Hb2i).p4().Phi(),
					_v_BJetTight->at(Hb2i).p4().E());
		       
		       float mH = (hb1+hb2).M();
		       
		       float chi2 = pow(mtop-173.,2)/pow(40.,2) +
			 pow(mW-80.4,2)/pow(15.,2) +
			 pow(mH-125.,2)/pow(30.,2);

//		       if( chi2 < mtopDiff && mH > 60. && mH < 140. )
		       if( chi2 < mtopDiff )
			 {
			    mtopDiff = chi2;
			    tb_idx = ib;
			    Hb1_idx = Hb1i;
			    Hb2_idx = Hb2i;
			    nu_idx = in;
			    nu12_idx = idMin;
			 }
		    }		  
	       }
	  }
	
	_nu_p4.SetPxPyPzE(px_nu,py_nu,pz_nu[nu_idx][nu12_idx],E_nu[nu_idx][nu12_idx]);
     }

   bool found_tb = 0;
   bool found_Hb1 = 0;
   bool found_Hb2 = 0;
   
   if( tb_idx >= 0 )
     {		  
	_topb_p4.SetPtEtaPhiE(_v_BJetTight->at(tb_idx).p4().Pt(),
			      _v_BJetTight->at(tb_idx).p4().PseudoRapidity(),
			      _v_BJetTight->at(tb_idx).p4().Phi(),
			      _v_BJetTight->at(tb_idx).p4().E());
	found_tb = 1;
     }   
   if( Hb1_idx >= 0 )
     {		  
	_Hb1_p4.SetPtEtaPhiE(_v_BJetTight->at(Hb1_idx).p4().Pt(),
			     _v_BJetTight->at(Hb1_idx).p4().PseudoRapidity(),
			     _v_BJetTight->at(Hb1_idx).p4().Phi(),
			     _v_BJetTight->at(Hb1_idx).p4().E());
	found_Hb1 = 1;
     }   
   if( Hb2_idx >= 0 )
     {		     
	_Hb2_p4.SetPtEtaPhiE(_v_BJetTight->at(Hb2_idx).p4().Pt(),
			     _v_BJetTight->at(Hb2_idx).p4().PseudoRapidity(),
			     _v_BJetTight->at(Hb2_idx).p4().Phi(),
			     _v_BJetTight->at(Hb2_idx).p4().E());
	found_Hb2 = 1;
     }
   
   hasSolution = hasSolution && found_tb && found_Hb1 && found_Hb2;
   
   return hasSolution;
}

void TopReco::truthMatchAlg()
{
   float drMatch = 0.5;
   
   // Hb1
   _Hb1_match = 0;
   bool match_Hb1_tHb1 = 0;
   bool match_Hb1_tHb2 = 0;
   float dr_Hb1_tHb1 = _Hb1_p4.DeltaR(_Hb1_IS_truth_p4);
   float dr_Hb1_tHb2 = _Hb1_p4.DeltaR(_Hb2_IS_truth_p4);
   if( dr_Hb1_tHb1 < drMatch ) match_Hb1_tHb1 = 1;
   if( dr_Hb1_tHb2 < drMatch ) match_Hb1_tHb2 = 1;
   
   // Hb2
   _Hb2_match = 0;
   bool match_Hb2_tHb1 = 0;
   bool match_Hb2_tHb2 = 0;
   float dr_Hb2_tHb1 = _Hb2_p4.DeltaR(_Hb1_IS_truth_p4);
   float dr_Hb2_tHb2 = _Hb2_p4.DeltaR(_Hb2_IS_truth_p4);
   if( dr_Hb2_tHb1 < drMatch ) match_Hb2_tHb1 = 1;
   if( dr_Hb2_tHb2 < drMatch ) match_Hb2_tHb2 = 1;
   
   if( match_Hb1_tHb1 )
     {
	_Hb1_match = 1;
	if( match_Hb2_tHb2 ) _Hb2_match = 1;
     }   
   else if( match_Hb1_tHb2 )
     {
	_Hb1_match = 1;
	if( match_Hb2_tHb1 ) _Hb2_match = 1;
     }   

   // topb
   _topb_match = 0;
   float dr_topb_ttopb = _topb_p4.DeltaR(_topb_IS_truth_p4);
   if( dr_topb_ttopb < drMatch ) _topb_match = 1;
}

void TopReco::truthMatch()
{
   float drMatch = 0.5;
   
   int nbjets = _v_BJetTight->size();
   
   // Hb1
   _Hb1_match_all = 0;
   float dr_Hb1_Min = 666.;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_Hb1 = _v_BJetTight->at(ij).p4().DeltaR(_Hb1_IS_truth_p4);
	if( dr_Hb1 < dr_Hb1_Min ) dr_Hb1_Min = dr_Hb1;
     }   
   if( dr_Hb1_Min < drMatch ) _Hb1_match_all = 1;

   // Hb2
   _Hb2_match_all = 0;
   float dr_Hb2_Min = 666.;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_Hb2 = _v_BJetTight->at(ij).p4().DeltaR(_Hb2_IS_truth_p4);
	if( dr_Hb2 < dr_Hb2_Min ) dr_Hb2_Min = dr_Hb2;
     }   
   if( dr_Hb2_Min < drMatch ) _Hb2_match_all = 1;

   // topb
   _topb_match_all = 0;
   float dr_topb_Min = 666.;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_topb = _v_BJetTight->at(ij).p4().DeltaR(_topb_IS_truth_p4);
	if( dr_topb < dr_topb_Min ) dr_topb_Min = dr_topb;
     }   
   if( dr_topb_Min < drMatch ) _topb_match_all = 1;
}

void TopReco::fill(int i,float w,bool isMatch)
{
   float H_m = _H_p4.M();
   h_H_m[i][0]->Fill(H_m,w);
   if( isMatch ) h_H_m[i][1]->Fill(H_m,w);
   else h_H_m[i][2]->Fill(H_m,w);
   
   float top_m = _top_p4.M();
   h_top_m[i][0]->Fill(top_m,w);
   if( isMatch ) h_top_m[i][1]->Fill(top_m,w);
   else h_top_m[i][2]->Fill(top_m,w);
   
   float W_m = _W_p4.M();
   h_W_m[i][0]->Fill(W_m,w);
   if( isMatch ) h_W_m[i][1]->Fill(W_m,w);
   else h_W_m[i][2]->Fill(W_m,w);
}

void TopReco::close()
{
   if( _standalone )
     {	
	_fout->Write();
	_fout->Close();
     }   
}

