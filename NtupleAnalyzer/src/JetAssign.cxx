#include "../include/JetAssign.h"

#include "TRandom3.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/type_traits.hpp>

JetAssign::JetAssign(std::string home,bool standalone,TFile *foutput)
{
   _home = home;
   
   help = new Helper();
   
   _standalone = standalone;
   
   if( !_standalone ) _fout = foutput;
   
   _v_ElectronTight = new std::vector<Electron>;
   _v_MuonTight = new std::vector<Muon>;
   _v_JetTight = new std::vector<Jet>;
   _v_BJetTight = new std::vector<Jet>;
}

JetAssign::~JetAssign()
{
   delete help;
   
   delete _v_ElectronTight;
   delete _v_MuonTight;
   delete _v_JetTight;
   delete _v_BJetTight;
}

void JetAssign::init()
{
   rnd = new TRandom3(666);

   if( _standalone )
     {	
//	std::string foutput = _home+"/"+std::string(flog)+".root";
	std::string foutput = std::string(flog)+".root";
	_fout = new TFile(foutput.c_str(),"RECREATE");

	_tree = new TTree("tree","Tree");

	_tree->Branch("match",&m_match,"match/O");
	_tree->Branch("weight",&m_weight,"weight/D");
	_tree->Branch("hasSol",&m_hasSol,"hasSol/O");
	_tree->Branch("id",&m_id,"id/I");
	
	_tree->Branch("topb_pt",&m_topb_pt,"topb_pt/D");
	_tree->Branch("topb_eta",&m_topb_eta,"topb_eta/D");
	_tree->Branch("topb_phi",&m_topb_phi,"topb_phi/D");
	_tree->Branch("topb_E",&m_topb_E,"topb_E/D");
	_tree->Branch("topb_CSV",&m_topb_CSV,"topb_CSV/D");

	_tree->Branch("Hb1_pt",&m_Hb1_pt,"Hb1_pt/D");
	_tree->Branch("Hb1_eta",&m_Hb1_eta,"Hb1_eta/D");
	_tree->Branch("Hb1_phi",&m_Hb1_phi,"Hb1_phi/D");
	_tree->Branch("Hb1_E",&m_Hb1_E,"Hb1_E/D");
	_tree->Branch("Hb1_CSV",&m_Hb1_CSV,"Hb1_CSV/D");
	
	_tree->Branch("Hb2_pt",&m_Hb2_pt,"Hb2_pt/D");
	_tree->Branch("Hb2_eta",&m_Hb2_eta,"Hb2_eta/D");
	_tree->Branch("Hb2_phi",&m_Hb2_phi,"Hb2_phi/D");
	_tree->Branch("Hb2_E",&m_Hb2_E,"Hb2_E/D");
	_tree->Branch("Hb2_CSV",&m_Hb2_CSV,"Hb2_CSV/D");

	_tree->Branch("l_pt",&m_l_pt,"l_pt/D");
	_tree->Branch("l_eta",&m_l_eta,"l_eta/D");
	_tree->Branch("l_phi",&m_l_phi,"l_phi/D");
	_tree->Branch("l_E",&m_l_E,"l_E/D");
	
	_tree->Branch("W_m",&m_W_m,"W_m/D");
	_tree->Branch("H_m",&m_H_m,"H_m/D");
	_tree->Branch("H_eta",&m_H_eta,"H_eta/D");
	_tree->Branch("top_m",&m_top_m,"top_m/D");
	_tree->Branch("top_pt",&m_top_pt,"top_pt/D");
	_tree->Branch("Hb1_Hb2_Dr",&m_Hb1_Hb2_Dr,"Hb1_Hb2_Dr/D");
	_tree->Branch("tb_tW_Dr",&m_tb_tW_Dr,"tb_tW_Dr/D");
	_tree->Branch("top_H_Dr",&m_top_H_Dr,"top_H_Dr/D");
	_tree->Branch("chi2",&m_chi2,"chi2/D");

	_treeReco = new TTree("treeReco","Tree");	
	_treeReco->Branch("matchAll",&m_matchAll,"matchAll/O");
	
	_treeTTbar = new TTree("treeTTbar","Tree");

	_treeTTbar->Branch("matchTTbar",&m_matchTTbar,"matchTTbar/O");
	_treeTTbar->Branch("weightTTbar",&m_weightTTbar,"weightTTbar/D");
	_treeTTbar->Branch("hasSolTTbar",&m_hasSolTTbar,"hasSolTTbar/O");
	_treeTTbar->Branch("idTTbar",&m_idTTbar,"idTTbar/I");
	
	_treeTTbar->Branch("topbLep_pt",&m_topbLep_pt,"topbLep_pt/D");
	_treeTTbar->Branch("topbLep_eta",&m_topbLep_eta,"topbLep_eta/D");
	_treeTTbar->Branch("topbLep_phi",&m_topbLep_phi,"topbLep_phi/D");
	_treeTTbar->Branch("topbLep_E",&m_topbLep_E,"topbLep_E/D");
	_treeTTbar->Branch("topbLep_CSV",&m_topbLep_CSV,"topbLep_CSV/D");

	_treeTTbar->Branch("topbHad_pt",&m_topbHad_pt,"topbHad_pt/D");
	_treeTTbar->Branch("topbHad_eta",&m_topbHad_eta,"topbHad_eta/D");
	_treeTTbar->Branch("topbHad_phi",&m_topbHad_phi,"topbHad_phi/D");
	_treeTTbar->Branch("topbHad_E",&m_topbHad_E,"topbHad_E/D");
	_treeTTbar->Branch("topbHad_CSV",&m_topbHad_CSV,"topbHad_CSV/D");

	_treeTTbar->Branch("topWj1_pt",&m_topWj1_pt,"topWj1_pt/D");
	_treeTTbar->Branch("topWj1_eta",&m_topWj1_eta,"topWj1_eta/D");
	_treeTTbar->Branch("topWj1_phi",&m_topWj1_phi,"topWj1_phi/D");
	_treeTTbar->Branch("topWj1_E",&m_topWj1_E,"topWj1_E/D");
	_treeTTbar->Branch("topWj1_CSV",&m_topWj1_CSV,"topWj1_CSV/D");

	_treeTTbar->Branch("topWj2_pt",&m_topWj2_pt,"topWj2_pt/D");
	_treeTTbar->Branch("topWj2_eta",&m_topWj2_eta,"topWj2_eta/D");
	_treeTTbar->Branch("topWj2_phi",&m_topWj2_phi,"topWj2_phi/D");
	_treeTTbar->Branch("topWj2_E",&m_topWj2_E,"topWj2_E/D");
	_treeTTbar->Branch("topWj2_CSV",&m_topWj2_CSV,"topWj2_CSV/D");
	
	_treeTTbar->Branch("topWl_pt",&m_topWl_pt,"topWl_pt/D");
	_treeTTbar->Branch("topWl_eta",&m_topWl_eta,"topWl_eta/D");
	_treeTTbar->Branch("topWl_phi",&m_topWl_phi,"topWl_phi/D");
	_treeTTbar->Branch("topWl_E",&m_topWl_E,"topWl_E/D");
	
	_treeTTbar->Branch("WLep_m",&m_WLep_m,"WLep_m/D");
	_treeTTbar->Branch("WHad_m",&m_WHad_m,"WHad_m/D");
	_treeTTbar->Branch("topLep_m",&m_topLep_m,"topLep_m/D");
	_treeTTbar->Branch("topHad_m",&m_topHad_m,"topHad_m/D");
	_treeTTbar->Branch("topLep_eta",&m_topLep_eta,"topLep_eta/D");
	_treeTTbar->Branch("topHad_eta",&m_topHad_eta,"topHad_eta/D");
	_treeTTbar->Branch("tbLep_tWLep_Dr",&m_tbLep_tWLep_Dr,"tbLep_tWLep_Dr/D");
	_treeTTbar->Branch("tbHad_tWHad_Dr",&m_tbHad_tWHad_Dr,"tbHad_tWHad_Dr/D");
	_treeTTbar->Branch("tWj1_tWj2_Dr",&m_tWj1_tWj2_Dr,"tWj1_tWj2_Dr/D");
	_treeTTbar->Branch("chi2TTbar",&m_chi2TTbar,"chi2TTbar/D");
	
	_treeRecoTTbar = new TTree("treeRecoTTbar","Tree");	
	_treeRecoTTbar->Branch("matchAllTTbar",&m_matchAllTTbar,"matchAllTTbar/O");
     }   

   std::cout << "JetAssign initialisation done" << std::endl;
}

bool JetAssign::run()
{
   float w = _v_Event->at(0).mc_weight();

   bool isData = _v_Event->at(0).isData();
   
   float xsec = _v_Event->at(0).xsec();
   float noe = _v_Event->at(0).noe();
   float wil = 1650.*xsec/noe;
   if( !isData ) w *= wil;

   _v_ElectronTight->clear();
   _v_MuonTight->clear();
   _v_JetTight->clear();
   _v_BJetTight->clear();

   std::vector<Lepton> res;
   
   if( _standalone )
     {	
	for(int i=0;i<_v_Electron->size();i++)
	  {
	     if( fabs(_v_Electron->at(i).eta()) > 2.1 ) continue;
	     
	     if( _v_Electron->at(i).isTight() )
	       {		  
		  _v_ElectronTight->push_back(_v_Electron->at(i));
	       }	     
	  }       
	
	for(int i=0;i<_v_Muon->size();i++)
	  {
	     if( fabs(_v_Muon->at(i).eta()) > 2.1 ) continue;
	     
	     if( _v_Muon->at(i).isTight() )
	       {		  
		  _v_MuonTight->push_back(_v_Muon->at(i));
	       }      
	  }	
	
	for(int i=0;i<_v_Jet->size();i++)
	  {
	     if( fabs(_v_Jet->at(i).eta()) > 2.4 ) continue;

	     if( _v_Jet->at(i).isTight() )
	       {		  	     
		  _v_JetTight->push_back(_v_Jet->at(i));
//		  _v_BJetTight->push_back(_v_Jet->at(i));
//		  if( _v_Jet->at(i).CSVv2() >= 0.970 ) _v_BJetTight->push_back(_v_Jet->at(i));
		  if( _v_Jet->at(i).CSVv2() >= 0.890 ) _v_BJetTight->push_back(_v_Jet->at(i));
//		  if( _v_Jet->at(i).CSVv2() >= 0.605 ) _v_BJetTight->push_back(_v_Jet->at(i));
	       }      
	  }
	
	res = help->filterPt(30,30,20,
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
   
   m_id = id;
   m_idTTbar = id;
   
   float metptTruth = -1.;
   float metphiTruth = -1.;
   std::vector<int> lab = _v_Truth->at(0).mc_truth_label();
   int nTruth = lab.size();
   
   _l_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _l1_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _l2_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _Hb1_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _Hb2_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _topb_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _topb1_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _topb2_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _topWj11_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _topWj21_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _topWj12_truth_p4.SetPtEtaPhiE(0,0,0,0);
   _topWj22_truth_p4.SetPtEtaPhiE(0,0,0,0);

   _is_top1_leptonic = 0;
   _is_top2_leptonic = 0;
   _is_lepton_tau = 0;
   
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
	else if( lab[it] == 420 )
	  {
	     _l_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
				      _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
				      _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
				      _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }
	else if( lab[it] == 18666 )
	  {
	     _Hb1_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					_v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					_v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					_v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }	     
	else if( lab[it] == 19666 )
	  {
	     _Hb2_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					_v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					_v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					_v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }	     
	else if( lab[it] == 41666 )
	  {
	     _topb_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					 _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					 _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					 _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }
	else if( lab[it] == 21 )
	  {
	     _topb1_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					  _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					  _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					  _v_Truth->at(0).mc_truth_p4().at(it).E());
	  }
	else if( lab[it] == 31 )
	  {
	     _topb2_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					  _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					  _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					  _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }
	else if( lab[it] == 222 )
	  {
	     _topWj11_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					    _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					    _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					    _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }
	else if( lab[it] == 223 )
	  {
	     _topWj21_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					    _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					    _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					    _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }
	else if( lab[it] == 332 )
	  {
	     _topWj12_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					    _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					    _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					    _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }
	else if( lab[it] == 333 )
	  {
	     _topWj22_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
					    _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
					    _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
					    _v_Truth->at(0).mc_truth_p4().at(it).E());			    
	  }
	else if( lab[it] == 220 )
	  {
	     _l1_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
				       _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
				       _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
				       _v_Truth->at(0).mc_truth_p4().at(it).E());
	     _is_top1_leptonic = 1;
	     if( abs(_v_Truth->at(0).mc_truth_id().at(it)) == 15 ) _is_lepton_tau = 1;
	  }
	else if( lab[it] == 330 )
	  {
	     _l2_truth_p4.SetPtEtaPhiE(_v_Truth->at(0).mc_truth_p4().at(it).Pt(),
				       _v_Truth->at(0).mc_truth_p4().at(it).PseudoRapidity(),
				       _v_Truth->at(0).mc_truth_p4().at(it).Phi(),
				       _v_Truth->at(0).mc_truth_p4().at(it).E());
	     _is_top2_leptonic = 1;
	     if( abs(_v_Truth->at(0).mc_truth_id().at(it)) == 15 ) _is_lepton_tau = 1;
	  }
     }
   
   float metpt = _v_Event->at(0).metpt();
   float metphi = _v_Event->at(0).metphi();
   float metpx = metpt*cos(metphi);
   float metpy = metpt*sin(metphi);
   float metE = sqrt(metpx*metpx+metpy*metpy);
   
   int njets = _v_JetTight->size();
   int nbjets = _v_BJetTight->size();
   
   int nLep = _v_Lepton->size();

   bool passGenFilt_tH = 1;
   if( _Hb1_truth_p4.Pt() < 30. || 
       _Hb2_truth_p4.Pt() < 30. ||
       _topb_truth_p4.Pt() < 30. ) passGenFilt_tH = 0;
   if( fabs(_Hb1_truth_p4.PseudoRapidity()) > 2.4 || 
       fabs(_Hb2_truth_p4.PseudoRapidity()) > 2.4 ||
       fabs(_topb_truth_p4.PseudoRapidity()) > 2.4 ) passGenFilt_tH = 0;

   bool passGenFilt_ttbar = 1;
   if( _topb1_truth_p4.Pt() < 30. || 
       _topb2_truth_p4.Pt() < 30. ) passGenFilt_ttbar = 0;
   if( fabs(_topb1_truth_p4.PseudoRapidity()) > 2.4 || 
       fabs(_topb2_truth_p4.PseudoRapidity()) > 2.4 ) passGenFilt_ttbar = 0;

   // select only semi-leptonic events
   if( !_is_top1_leptonic && !_is_top2_leptonic ) passGenFilt_ttbar = 0;
   if( _is_top1_leptonic && _is_top2_leptonic ) passGenFilt_ttbar = 0;
   if( _is_lepton_tau ) passGenFilt_ttbar = 0;
   
   passGenFilt_tH = passGenFilt_tH || !_standalone;
   passGenFilt_ttbar = passGenFilt_ttbar || !_standalone;

   // tH
   if( nLep == 1 && njets >= 4 && passGenFilt_tH )
     {
	m_matchAll = 0;
	
	if( nbjets >= 3 )
	  {	     
	     _l_p4.SetPtEtaPhiE(_v_Lepton->at(0).p4().Pt(),
				_v_Lepton->at(0).p4().PseudoRapidity(),
				_v_Lepton->at(0).p4().Phi(),
				_v_Lepton->at(0).p4().E());			    
	     
	     m_l_pt = _l_p4.Pt();
	     m_l_eta = _l_p4.PseudoRapidity();
	     m_l_phi = _l_p4.Phi();
	     m_l_E = _l_p4.E();
	     
	     _nu_p4.SetPtEtaPhiE(metpt,
				 0,
				 metphi,
				 metE);
	     
	     bool isMatch = truthMatchAll();
	     
	     m_matchAll = isMatch;
	  }
	
	if( _standalone ) _treeReco->Fill();
	
	if( nbjets < 3 ) return 0;
	
	if( m_matchAll || !_standalone )
	  {
	     int nBJetPerm = nbjets;
	     
//	     std::cout << "-----" << std::endl;
	     for(int ib=0;ib<nBJetPerm;ib++)
	       {
		  for(int ib2=0;ib2<nBJetPerm;ib2++)
		    {
		       for(int ib3=0;ib3<nBJetPerm;ib3++)
			 {
			    if( ib == ib2 || ib == ib3 || ib2 == ib3 ) continue;

			    if( ib3 < ib2 ) continue;
			    
//			    std::cout << ib << " " << ib2 << " " << ib3 << std::endl;
			    
			    TLorentzVector topbRec = _v_BJetTight->at(ib).p4();
			    TLorentzVector Hb1Rec = _v_BJetTight->at(ib2).p4();
			    TLorentzVector Hb2Rec = _v_BJetTight->at(ib3).p4();
			    
			    m_match = truthMatch(topbRec,Hb1Rec,Hb2Rec);
			    
			    m_topb_pt = topbRec.Pt();
			    m_topb_eta = topbRec.PseudoRapidity();
			    m_topb_phi = topbRec.Phi();
			    m_topb_E = topbRec.E();
			    m_topb_CSV = _v_BJetTight->at(ib).CSVv2();
			    
			    m_Hb1_pt = Hb1Rec.Pt();
			    m_Hb1_eta = Hb1Rec.PseudoRapidity();
			    m_Hb1_phi = Hb1Rec.Phi();
			    m_Hb1_E = Hb1Rec.E();
			    m_Hb1_CSV = _v_BJetTight->at(ib2).CSVv2();
			    
			    m_Hb2_pt = Hb2Rec.Pt();
			    m_Hb2_eta = Hb2Rec.PseudoRapidity();
			    m_Hb2_phi = Hb2Rec.Phi();
			    m_Hb2_E = Hb2Rec.E();
			    m_Hb2_CSV = _v_BJetTight->at(ib3).CSVv2();
			    
			    m_weight = w;
			    
			    _H_p4 = Hb1Rec+Hb2Rec;
			    
			    m_H_m = _H_p4.M();
			    m_H_eta = _H_p4.PseudoRapidity();
			    m_Hb1_Hb2_Dr = Hb1Rec.DeltaR(Hb2Rec);

			    m_chi2 = 666.;

			    bool hasSol = JetAssign::topReco(topbRec);
			    
			    if( hasSol )
			      {				 
				 m_top_m = _top_p4.M();
				 m_top_pt = _top_p4.Pt();
				 m_W_m = _W_p4.M();
				 m_tb_tW_Dr = _topb_p4.DeltaR(_W_p4);
				 m_top_H_Dr = _top_p4.DeltaR(_H_p4);
				 m_chi2 = _chi2 + pow(m_H_m-125.,2)/pow(30.,2);
			      }

			    m_hasSol = hasSol;
			    if( !hasSol ) m_match = 0;
			    
			    if( _standalone ) _tree->Fill();
			 }		       
		    }
	       }
	  }	
     }   

   // ttbar
   if( nLep == 1 && njets >= 4 && passGenFilt_ttbar )
     {
	m_matchAllTTbar = 0;
	
	if( nbjets >= 3 )
	  {	     
	     _l_p4.SetPtEtaPhiE(_v_Lepton->at(0).p4().Pt(),
				_v_Lepton->at(0).p4().PseudoRapidity(),
				_v_Lepton->at(0).p4().Phi(),
				_v_Lepton->at(0).p4().E());			    
	     
	     m_topWl_pt = _l_p4.Pt();
	     m_topWl_eta = _l_p4.PseudoRapidity();
	     m_topWl_phi = _l_p4.Phi();
	     m_topWl_E = _l_p4.E();
	     
	     _nu_p4.SetPtEtaPhiE(metpt,
				 0,
				 metphi,
				 metE);
	     
	     truthMatchAllTTbar();
//	     bool isMatchAll = (_topbLep_match_all && _topbHad_match_all &&
//				_topWj1_match_all && _topWj2_match_all);
	     bool isMatchAll = (_topbLep_match_all && _topbHad_match_all);
	     
	     m_matchAllTTbar = isMatchAll;
	  }
	
	if( _standalone ) _treeRecoTTbar->Fill();
	
	if( nbjets < 3 ) return 0;
	
	if( m_matchAllTTbar || !_standalone )
	  {
	     int nBJetPerm = nbjets;
	     
//	     std::cout << "-----" << std::endl;
	     for(int ib=0;ib<nBJetPerm;ib++)
	       {
		  for(int ib2=0;ib2<nBJetPerm;ib2++)
		    {
		       if( ib == ib2 ) continue;
		       
		       TLorentzVector topbLepRec = _v_BJetTight->at(ib).p4();
		       TLorentzVector topbHadRec = _v_BJetTight->at(ib2).p4();
		       
		       float pt1 = topbLepRec.Pt();
		       float pt2 = topbHadRec.Pt();
			    
		       int idj1 = -1;
		       int idj2 = -1;
		       for(int ibb=0;ibb<njets;ibb++)
			 {
			    float ptCur = _v_JetTight->at(ibb).p4().Pt();
			    if( ptCur != pt1 && ptCur != pt2 )
			      {
				 if( idj1 < 0 ) idj1 = ibb;
				 else if( idj2 < 0 ) idj2 = ibb;
				 else break;
			      }				 
			 }			    
			    
		       TLorentzVector topWj1Rec = _v_JetTight->at(idj1).p4();
		       TLorentzVector topWj2Rec = _v_JetTight->at(idj2).p4();
			    
		       m_matchTTbar = truthMatchTTbar(topbLepRec,topbHadRec);
			    
//		       std::cout << ib << " " << ib2 << " res=" << m_matchTTbar << std::endl;
			    
		       m_topbLep_pt = topbLepRec.Pt();
		       m_topbLep_eta = topbLepRec.PseudoRapidity();
		       m_topbLep_phi = topbLepRec.Phi();
		       m_topbLep_E = topbLepRec.E();
		       m_topbLep_CSV = _v_BJetTight->at(ib).CSVv2();

		       m_topbHad_pt = topbHadRec.Pt();
		       m_topbHad_eta = topbHadRec.PseudoRapidity();
		       m_topbHad_phi = topbHadRec.Phi();
		       m_topbHad_E = topbHadRec.E();
		       m_topbHad_CSV = _v_BJetTight->at(ib2).CSVv2();
		       
		       m_topWj1_pt = topWj1Rec.Pt();
		       m_topWj1_eta = topWj1Rec.PseudoRapidity();
		       m_topWj1_phi = topWj1Rec.Phi();
		       m_topWj1_E = topWj1Rec.E();
		       m_topWj1_CSV = _v_JetTight->at(idj1).CSVv2();
		       
		       m_topWj2_pt = topWj2Rec.Pt();
		       m_topWj2_eta = topWj2Rec.PseudoRapidity();
		       m_topWj2_phi = topWj2Rec.Phi();
		       m_topWj2_E = topWj2Rec.E();
		       m_topWj2_CSV = _v_JetTight->at(idj2).CSVv2();
		       
		       m_weightTTbar = w;
		       
		       m_chi2TTbar = 666.;
		       
		       _WHad_p4 = topWj1Rec+topWj2Rec;
		       _topHad_p4 = _WHad_p4+topbHadRec;
		       
		       bool hasSolTTbar = JetAssign::topReco(topbLepRec);
		       
		       if( hasSolTTbar )
			 {		
			    m_WLep_m = _W_p4.M();
			    m_WHad_m = _WHad_p4.M();
			    m_topLep_m = _top_p4.M();
			    m_topHad_m = _topHad_p4.M();
			    m_topLep_eta = _top_p4.PseudoRapidity();
			    m_topHad_eta = _topHad_p4.PseudoRapidity();
			    m_tbLep_tWLep_Dr = topbLepRec.DeltaR(_W_p4);
			    m_tbHad_tWHad_Dr = topbHadRec.DeltaR(_WHad_p4);
			    m_tWj1_tWj2_Dr = topWj1Rec.DeltaR(topWj2Rec);
			    m_chi2TTbar = _chi2 +
			      pow(_topHad_p4.M()-173.,2)/pow(100.,2) + 
			      pow(_WHad_p4.M()-80.4,2)/pow(50.,2);
			 }

		       m_hasSolTTbar = hasSolTTbar;
		       if( !hasSolTTbar ) m_matchTTbar = 0;
		       
		       if( _standalone ) _treeTTbar->Fill();
		    }
	       }
	  }
     }
   
   return 1;
}

bool JetAssign::truthMatch(TLorentzVector &topbRec,
			   TLorentzVector &Hb1Rec,
			   TLorentzVector &Hb2Rec)
{
   float drMatch = 0.4;
   
   // Hb1
   _Hb1_match = 0;
   bool match_Hb1_tHb1 = 0;
   bool match_Hb1_tHb2 = 0;
   float dr_Hb1_tHb1 = Hb1Rec.DeltaR(_Hb1_truth_p4);
   float dr_Hb1_tHb2 = Hb1Rec.DeltaR(_Hb2_truth_p4);
   if( dr_Hb1_tHb1 < drMatch ) match_Hb1_tHb1 = 1;
   if( dr_Hb1_tHb2 < drMatch ) match_Hb1_tHb2 = 1;
   
   // Hb2
   _Hb2_match = 0;
   bool match_Hb2_tHb1 = 0;
   bool match_Hb2_tHb2 = 0;
   float dr_Hb2_tHb1 = Hb2Rec.DeltaR(_Hb1_truth_p4);
   float dr_Hb2_tHb2 = Hb2Rec.DeltaR(_Hb2_truth_p4);
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
   float dr_topb_ttopb = topbRec.DeltaR(_topb_truth_p4);
   if( dr_topb_ttopb < drMatch ) _topb_match = 1;
   
   if( _topb_match && _Hb1_match && _Hb2_match ) return 1;
   else return 0;
}

bool JetAssign::truthMatchAll()
{
   float drMatch = 0.4;
   
   int nbjets = _v_BJetTight->size();
   
   // Hb1
   bool Hb1_match_all = 0;
   float dr_Hb1_Min = 666.;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_Hb1 = _v_BJetTight->at(ij).p4().DeltaR(_Hb1_truth_p4);
	if( dr_Hb1 < dr_Hb1_Min ) dr_Hb1_Min = dr_Hb1;
     }   
   if( dr_Hb1_Min < drMatch ) Hb1_match_all = 1;

   // Hb2
   bool Hb2_match_all = 0;
   float dr_Hb2_Min = 666.;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_Hb2 = _v_BJetTight->at(ij).p4().DeltaR(_Hb2_truth_p4);
	if( dr_Hb2 < dr_Hb2_Min ) dr_Hb2_Min = dr_Hb2;
     }   
   if( dr_Hb2_Min < drMatch ) Hb2_match_all = 1;

   // topb
   bool topb_match_all = 0;
   float dr_topb_Min = 666.;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_topb = _v_BJetTight->at(ij).p4().DeltaR(_topb_truth_p4);
	if( dr_topb < dr_topb_Min ) dr_topb_Min = dr_topb;
     }   
   if( dr_topb_Min < drMatch ) topb_match_all = 1;
   
   bool isMatch = (Hb1_match_all && Hb2_match_all && topb_match_all);
   
   return isMatch;
}

void JetAssign::close()
{
   if( _standalone )
     {	
	_fout->Write();
	_fout->Close();
     }   
}

bool JetAssign::topReco(TLorentzVector &topbRec)
{   
   int itry = 0;
   const int nTryMax = 100;
   std::vector<float> v_pz_nu1;
   std::vector<float> v_pz_nu2;

   float px_nu = _nu_p4.Px();
   float py_nu = _nu_p4.Py();
   float px_l = _l_p4.Px();
   float py_l = _l_p4.Py();
   float pz_l = _l_p4.Pz();
   float E_l = _l_p4.E();

   bool hasSolution = 0;
   while( v_pz_nu1.size() < nTryMax )
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
	float E_nu[nTryMax][2];
	float pz_nu[nTryMax][2];
	
	float pt_topb = topbRec.Pt();
	float E_topb = topbRec.E();
	float eta_topb = topbRec.PseudoRapidity();
	float phi_topb = topbRec.Phi();
	float px_topb = pt_topb*cos(phi_topb);
	float py_topb = pt_topb*sin(phi_topb);
	float pz_topb = pt_topb*sinh(eta_topb);
	
	for(int in=0;in<nSol;in++)
	  {
	     pz_nu[in][0] = v_pz_nu1[in];
	     pz_nu[in][1] = v_pz_nu2[in];
	     
	     E_nu[in][0] = sqrt(px_nu*px_nu+py_nu*py_nu+v_pz_nu1[in]*v_pz_nu1[in]);
	     E_nu[in][1] = sqrt(px_nu*px_nu+py_nu*py_nu+v_pz_nu2[in]*v_pz_nu2[in]);
	  }	     

	int nu_idx = -1;
	int nu12_idx = -1;

	float mtopDiff = 10E+10;
		       
	for(int in=0;in<nSol;in++)
	  {
	     for(int in2=0;in2<2;in2++)
	       {		       
		  float totE = E_topb+E_nu[in][in2]+E_l;
		  float totPx = px_topb+px_nu+px_l;
		  float totPy = py_topb+py_nu+py_l;
		  float totPz = pz_topb+pz_nu[in][in2]+pz_l;
		  float mW = pow(E_nu[in][in2]+E_l,2)-pow(px_nu+px_l,2)-pow(py_nu+py_l,2)-pow(pz_nu[in][in2]+pz_l,2);
		  float mtop = totE*totE-totPx*totPx-totPy*totPy-totPz*totPz;

		  if( mtop >= 0 )
		    {
		       mtop = sqrt(mtop);
		       mW = sqrt(mW);

		       float chi2 = pow(mtop-173.,2)/pow(40.,2) +
			 pow(mW-80.4,2)/pow(15.,2);
		       
		       if( chi2 < mtopDiff )
			 {
			    _chi2 = chi2;
			    mtopDiff = chi2;
			    nu_idx = in;
			    nu12_idx = in2;
			    hasSolution = 1;
			 }
		    }		  
	       }
	  }
	
	_nu_p4.SetPxPyPzE(px_nu,py_nu,pz_nu[nu_idx][nu12_idx],E_nu[nu_idx][nu12_idx]);
	_topb_p4 = topbRec;
	
	_W_p4 = (_nu_p4 + _l_p4);
	_top_p4 = (_W_p4 + _topb_p4);
     }
   
   return hasSolution;
}

void JetAssign::truthMatchAllTTbar()
{
   float drMatch = 0.4;
   
   int nleptons = _v_Lepton->size();
   int njets = _v_JetTight->size();
   int nbjets = _v_BJetTight->size();
   
   // topbLep
   _topbLep_match_all = 0;
   float dr_topbLep_Min = 10E+10;
   int idxLep_Min = -1;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_topbLep = 666.;
	if( _is_top1_leptonic ) dr_topbLep = _v_BJetTight->at(ij).p4().DeltaR(_topb1_truth_p4);
	else dr_topbLep = _v_BJetTight->at(ij).p4().DeltaR(_topb2_truth_p4);
	if( dr_topbLep < dr_topbLep_Min ) 
	  {
	     dr_topbLep_Min = dr_topbLep;
	     idxLep_Min = ij;
	  }	
     }   
   if( dr_topbLep_Min < drMatch ) 
     {
	_topbLep_match_all = 1;
     }   

   // topbHad
   _topbHad_match_all = 0;
   float dr_topbHad_Min = 10E+10;
   int idxHad_Min = -1;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_topbHad = 666.;
	if( _is_top1_leptonic ) dr_topbHad = _v_BJetTight->at(ij).p4().DeltaR(_topb2_truth_p4);
	else dr_topbHad = _v_BJetTight->at(ij).p4().DeltaR(_topb1_truth_p4);
	if( dr_topbHad < dr_topbHad_Min ) 
	  {
	     dr_topbHad_Min = dr_topbHad;
	     idxHad_Min = ij;
	  }
       
     }   
   if( dr_topbHad_Min < drMatch )
     {
	_topbHad_match_all = 1;
     }

   // topWl
   _topWl_match_all = 0;
   float dr_topWl_Min = 10E+10;
   int idxWl_Min = -1;
   for(int ij=0;ij<nleptons;ij++)
     {	
	float dr_topWl = 666.;
	if( _is_top1_leptonic ) dr_topWl = _v_Lepton->at(ij).p4().DeltaR(_l1_truth_p4);
	else dr_topWl = _v_Lepton->at(ij).p4().DeltaR(_l2_truth_p4);
	if( dr_topWl < dr_topWl_Min ) 
	  {
	     dr_topWl_Min = dr_topWl;
	     idxWl_Min = ij;
	  }	
     }   
   if( dr_topWl_Min < 0.15 )
     {
	_topWl_match_all = 1;
     }
   
   // topWj1
   _topWj1_match_all = 0;
   float dr_topWj1_Min = 10E+10;
   int idxWj1_Min = -1;
   for(int ij=0;ij<njets;ij++)
     {	
	float dr_topWj1 = 666.;
	if( _is_top1_leptonic ) 
	  {
	     dr_topWj1 = _v_JetTight->at(ij).p4().DeltaR(_topWj12_truth_p4);
	  }	
	else 
	  {
	     dr_topWj1 = _v_JetTight->at(ij).p4().DeltaR(_topWj11_truth_p4);
	  }	
	if( dr_topWj1 < dr_topWj1_Min )
	  {
	     dr_topWj1_Min = dr_topWj1;
	     idxWj1_Min = ij;
	  }	
     }   
   if( dr_topWj1_Min < drMatch ) 
     {
	_topWj1_match_all = 1;
     }   

   // topWj2
   _topWj2_match_all = 0;
   float dr_topWj2_Min = 10E+10;
   int idxWj2_Min = -1;
   for(int ij=0;ij<njets;ij++)
     {	
	float dr_topWj2 = 666.;
	if( _is_top1_leptonic ) 
	  {
	     dr_topWj2 = _v_JetTight->at(ij).p4().DeltaR(_topWj22_truth_p4);
	  }	
	else 
	  {
	     dr_topWj2 = _v_JetTight->at(ij).p4().DeltaR(_topWj21_truth_p4);
	  }	
	if( dr_topWj2 < dr_topWj2_Min )
	  {
	     dr_topWj2_Min = dr_topWj2;
	     idxWj2_Min = ij;
	  }	
     }   
   if( dr_topWj2_Min < drMatch )
     {
	_topWj2_match_all = 1;
     }
}

bool JetAssign::truthMatchTTbar(TLorentzVector &topbLepRec,
				TLorentzVector &topbHadRec)
{
   float drMatch = 0.4;
   
   // topbLep
   _topbLep_match = 0;
   float dr_topbLep = 10E+10;
   if( _is_top1_leptonic ) dr_topbLep = topbLepRec.DeltaR(_topb1_truth_p4);
   else dr_topbLep = topbLepRec.DeltaR(_topb2_truth_p4);
   if( dr_topbLep < drMatch ) _topbLep_match = 1;
   
   // topbHad
   _topbHad_match = 0;
   float dr_topbHad = 10E+10;
   if( _is_top1_leptonic ) dr_topbHad = topbHadRec.DeltaR(_topb2_truth_p4);
   else dr_topbHad = topbHadRec.DeltaR(_topb1_truth_p4);
   if( dr_topbHad < drMatch ) _topbHad_match = 1;
   
   bool isMatch = (_topbLep_match && _topbHad_match);
   
   return isMatch;
}
