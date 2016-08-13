#include "../include/TopReco.h"

#include "TRandom3.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/type_traits.hpp>

TopReco::TopReco(std::string home,bool standalone,TFile *foutput)
{
   _home = home;
   
   help = new Helper();
   
   _standalone = standalone;
   
   if( !_standalone ) _fout = foutput;
   
   _useTruthMET = 0;
   
   _v_ElectronTight = new std::vector<Electron>;
   _v_MuonTight = new std::vector<Muon>;
   _v_JetTight = new std::vector<Jet>;
   _v_BJetTight = new std::vector<Jet>;
   _v_NonBJetTight = new std::vector<Jet>;
   
   kf = new KINFIT::kfit();
}

TopReco::~TopReco()
{
   delete help;
   
   delete _v_ElectronTight;
   delete _v_MuonTight;
   delete _v_JetTight;
   delete _v_BJetTight;
   delete _v_NonBJetTight;
   
//   delete kf;
}

void TopReco::init()
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
        _tree->Branch("id",&m_id,"id/I");
	
	_treeReco = new TTree("treeReco","Tree");
	_treeReco->Branch("matchAll",&m_matchAll,"matchAll/O");

	_treeTTbar = new TTree("treeTTbar","Tree");
        _treeTTbar->Branch("matchTTbar",&m_matchTTbar,"matchTTbar/O");
        _treeTTbar->Branch("weightTTbar",&m_weightTTbar,"weightTTbar/D");
        _treeTTbar->Branch("idTTbar",&m_idTTbar,"idTTbar/I");
	_treeTTbar->Branch("mTopHad",&m_mTopHad,"mTopHad/D");
	_treeTTbar->Branch("mTopLep",&m_mTopLep,"mTopLep/D");
	
	_treeRecoTTbar = new TTree("treeRecoTTbar","Tree");
	_treeRecoTTbar->Branch("matchAllTTbar",&m_matchAllTTbar,"matchAllTTbar/O");
     }
   
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

   std::string hname_matchAllTTbar = "h_matchAllTTbar";
   h_matchAllTTbar = new TH1F(hname_matchAllTTbar.c_str(),hname_matchAllTTbar.c_str(),4,-0.5,3.5);
   h_matchAllTTbar->Sumw2();

   std::string hname_topSolTTbar = "h_topSolTTbar";
   h_topSolTTbar = new TH1F(hname_topSolTTbar.c_str(),hname_topSolTTbar.c_str(),2,-0.5,1.5);
   h_topSolTTbar->Sumw2();
   
   std::string hname_match = "h_match";
   h_match = new TH1F(hname_match.c_str(),hname_match.c_str(),4,-0.5,3.5);
   h_match->Sumw2();

   for(int j=0;j<3;j++)
     {	     
	std::string hname_H_m = "h_H_m_"+mtype[j];
	h_H_m[j] = new TH1F(hname_H_m.c_str(),hname_H_m.c_str(),30,0.,200.);
	h_H_m[j]->Sumw2();
	
	std::string hname_top_m = "h_top_m_"+mtype[j];
	h_top_m[j] = new TH1F(hname_top_m.c_str(),hname_top_m.c_str(),30,50.,300.);
	h_top_m[j]->Sumw2();
	
	std::string hname_W_m = "h_W_m_"+mtype[j];
	h_W_m[j] = new TH1F(hname_W_m.c_str(),hname_W_m.c_str(),30,40.,120.);
	h_W_m[j]->Sumw2();
     }   
   
   std::string pdfFileName = "/home-pbs/kskovpen/tHFCNC2016/CMSSW_8_0_12/src/TopKinFit/test/GenAnalysis/TopTopLepHbb/pdf.root";
   kf->SetPDF("TopWMass",pdfFileName.c_str(),"TopWM_Fit");
   kf->SetPDF("TopMass",pdfFileName.c_str(),"TopM_Fit");
   kf->SetPDF("HiggsMass",pdfFileName.c_str(),"TopWHadRecM_Fit");
   kf->SetPDF("TopWHadMass",pdfFileName.c_str(),"TopWHadRecM_Fit");
   kf->SetPDF("TopHadMass",pdfFileName.c_str(),"TopHadRecM_Fit");
   kf->SetPDF("MetPx",pdfFileName.c_str(),"dMetPx_Gaus");
   kf->SetPDF("MetPy",pdfFileName.c_str(),"dMetPy_Gaus");
   kf->SetPDF("BJetPx",pdfFileName.c_str(),"dBJetPx_Fit");
   kf->SetPDF("BJetPy",pdfFileName.c_str(),"dBJetPy_Fit");
   kf->SetPDF("BJetPz",pdfFileName.c_str(),"dBJetPz_Fit");
   kf->SetPDF("BJetE",pdfFileName.c_str(),"dBJetE_Fit");
   kf->SetPDF("NonBJetPx",pdfFileName.c_str(),"dNonBJetPx_Fit");
   kf->SetPDF("NonBJetPy",pdfFileName.c_str(),"dNonBJetPy_Fit");
   kf->SetPDF("NonBJetPz",pdfFileName.c_str(),"dNonBJetPz_Fit");
   kf->SetPDF("NonBJetE",pdfFileName.c_str(),"dNonBJetE_Fit");
   kf->SetPDF("ElecPx",pdfFileName.c_str(),"dElecPx_Fit");
   kf->SetPDF("ElecPy",pdfFileName.c_str(),"dElecPy_Fit");
   kf->SetPDF("ElecPz",pdfFileName.c_str(),"dElecPz_Fit");
   kf->SetPDF("ElecE",pdfFileName.c_str(),"dElecE_Fit");
   kf->SetPDF("MuonPx",pdfFileName.c_str(),"dMuonPx_Fit");
   kf->SetPDF("MuonPy",pdfFileName.c_str(),"dMuonPy_Fit");
   kf->SetPDF("MuonPz",pdfFileName.c_str(),"dMuonPz_Fit");
   kf->SetPDF("MuonE",pdfFileName.c_str(),"dMuonE_Fit");

   kf->SetWMassBW(80.4,2.1);
   kf->SetTopMass(172.5);
   kf->SetNToy(1000);

   std::cout << "TopReco initialisation done" << std::endl;
}

bool TopReco::run()
{
   float w = _v_Event->at(0).mc_weight();

   bool isData = _v_Event->at(0).isData();
   
   float xsec = _v_Event->at(0).xsec();
   float noe = _v_Event->at(0).noe();
   float wil = 19200.*xsec/noe;
   if( !isData ) w *= wil;

   _v_ElectronTight->clear();
   _v_MuonTight->clear();
   _v_JetTight->clear();
   _v_BJetTight->clear();
   _v_NonBJetTight->clear();

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
//		  if( _v_Jet->at(i).CSVv2() >= 0.605 ) _v_BJetTight->push_back(_v_Jet->at(i));
//		  if( _v_Jet->at(i).CSVv2() >= 0.970 ) _v_BJetTight->push_back(_v_Jet->at(i));
		  if( _v_Jet->at(i).CSVv2() >= 0.800 ) _v_BJetTight->push_back(_v_Jet->at(i));
		  else _v_NonBJetTight->push_back(_v_Jet->at(i));
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
	     if( _v_Jet->at(i).isBTag() ) _v_BJetTight->push_back(_v_Jet->at(i));
	     else _v_NonBJetTight->push_back(_v_Jet->at(i));
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

   if( _useTruthMET )
     {	
	metpt = metptTruth;
	metphi = metphiTruth;
     }   
   
   int njets = _v_JetTight->size();
   int nbjets = _v_BJetTight->size();
   int nnonbjets = _v_NonBJetTight->size();
   
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
   if( nLep == 1 && nbjets >= 3 && nnonbjets >= 1 && passGenFilt_tH )
     {		
	m_matchAll = 0;

	if( nbjets >= 3 )
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

	     m_matchAll = isMatchAll;
	  }	
   
	if( _standalone ) _treeReco->Fill();

	if( nbjets < 3 ) return 0;

	if( m_matchAll || !_standalone )
	  {
	     _topb_p4.SetPtEtaPhiE(0,0,0,0);
	     _Hb1_p4.SetPtEtaPhiE(0,0,0,0);
	     _Hb2_p4.SetPtEtaPhiE(0,0,0,0);
	     _top_p4.SetPtEtaPhiE(0,0,0,0);
	     _H_p4.SetPtEtaPhiE(0,0,0,0);
	     _W_p4.SetPtEtaPhiE(0,0,0,0);

	     kf->Init(TOPHLEPBB);

	     std::vector<float> BJetPt;
	     std::vector<float> BJetEta;
	     std::vector<float> BJetPhi;
	     std::vector<float> BJetE;
	     
	     std::vector<float> NonBJetPt;
	     std::vector<float> NonBJetEta;
	     std::vector<float> NonBJetPhi;
	     std::vector<float> NonBJetE;
	     
	     std::vector<float> ElectronPt;
	     std::vector<float> ElectronEta;
	     std::vector<float> ElectronPhi;
	     std::vector<float> ElectronE;
	     
	     std::vector<float> MuonPt;
	     std::vector<float> MuonEta;
	     std::vector<float> MuonPhi;
	     std::vector<float> MuonE;
	     
	     for(int i=0;i<_v_ElectronTight->size();i++)
	       {
		  ElectronPt.push_back(_v_ElectronTight->at(i).pt());
		  ElectronEta.push_back(_v_ElectronTight->at(i).eta());
		  ElectronPhi.push_back(_v_ElectronTight->at(i).phi());
		  ElectronE.push_back(_v_ElectronTight->at(i).E());
	       }   
	     
	     for(int i=0;i<_v_MuonTight->size();i++)
	       {
		  MuonPt.push_back(_v_MuonTight->at(i).pt());
		  MuonEta.push_back(_v_MuonTight->at(i).eta());
		  MuonPhi.push_back(_v_MuonTight->at(i).phi());
		  MuonE.push_back(_v_MuonTight->at(i).E());
	       }   
	     
	     for(int i=0;i<_v_BJetTight->size();i++)
	       {
		  BJetPt.push_back(_v_BJetTight->at(i).pt());
		  BJetEta.push_back(_v_BJetTight->at(i).eta());
		  BJetPhi.push_back(_v_BJetTight->at(i).phi());
		  BJetE.push_back(_v_BJetTight->at(i).E());
	       }   
	     
	     for(int i=0;i<_v_NonBJetTight->size();i++)
	       {
		  NonBJetPt.push_back(_v_NonBJetTight->at(i).pt());
		  NonBJetEta.push_back(_v_NonBJetTight->at(i).eta());
		  NonBJetPhi.push_back(_v_NonBJetTight->at(i).phi());
		  NonBJetE.push_back(_v_NonBJetTight->at(i).E());
	       }   
	     
	     kf->SetBJet(BJetPt,BJetEta,BJetPhi,BJetE);
	     kf->SetNonBJet(NonBJetPt,NonBJetEta,NonBJetPhi,NonBJetE);
	     kf->SetElectron(ElectronPt,ElectronEta,ElectronPhi,ElectronE);
	     kf->SetMuon(MuonPt,MuonEta,MuonPhi,MuonE);
	     kf->SetMet(metpx,metpy);

	     kf->Run();
	     
	     _chi2 = kf->GetDisc();
	     std::cout << "nPerm=" << kf->GetNPerm() << " chi2=" << _chi2 << " nbj=" << BJetPt.size() << std::endl;

	     int idx_BJETLEP_TOPHLEPBB = kf->GetIndex(BJETLEP_TOPHLEPBB,0);
	     int idx_BJET1_TOPHLEPBB = kf->GetIndex(BJET1_TOPHLEPBB,0);
	     int idx_BJET2_TOPHLEPBB = kf->GetIndex(BJET2_TOPHLEPBB,0);
	     int idx_ELECTRON_TOPHLEPBB = kf->GetIndex(ELECTRON_TOPHLEPBB,0);
	     int idx_MUON_TOPHLEPBB = kf->GetIndex(MUON_TOPHLEPBB,0);

	     _Hb1_p4.SetPtEtaPhiE(BJetPt[idx_BJET1_TOPHLEPBB],
				  BJetEta[idx_BJET1_TOPHLEPBB],
				  BJetPhi[idx_BJET1_TOPHLEPBB],
				  BJetE[idx_BJET1_TOPHLEPBB]);

	     _Hb2_p4.SetPtEtaPhiE(BJetPt[idx_BJET2_TOPHLEPBB],
				  BJetEta[idx_BJET2_TOPHLEPBB],
				  BJetPhi[idx_BJET2_TOPHLEPBB],
				  BJetE[idx_BJET2_TOPHLEPBB]);

	     _topb_p4.SetPtEtaPhiE(BJetPt[idx_BJETLEP_TOPHLEPBB],
				   BJetEta[idx_BJETLEP_TOPHLEPBB],
				   BJetPhi[idx_BJETLEP_TOPHLEPBB],
				   BJetE[idx_BJETLEP_TOPHLEPBB]);

	     if( idx_ELECTRON_TOPHLEPBB >= 0 )
	       _l_p4.SetPtEtaPhiE(ElectronPt[idx_ELECTRON_TOPHLEPBB],
				  ElectronEta[idx_ELECTRON_TOPHLEPBB],
				  ElectronPhi[idx_ELECTRON_TOPHLEPBB],
				  ElectronE[idx_ELECTRON_TOPHLEPBB]);
	     else
	       _l_p4.SetPtEtaPhiE(MuonPt[idx_MUON_TOPHLEPBB],
				  MuonEta[idx_MUON_TOPHLEPBB],
				  MuonPhi[idx_MUON_TOPHLEPBB],
				  MuonE[idx_MUON_TOPHLEPBB]);

	     float nupx = kf->GetNuPx(0,0);
	     float nupy = kf->GetNuPy(0,0);
	     float nupz = kf->GetNuPz(0,0);
	     float nue = sqrt(nupx*nupx+nupy*nupy+nupz*nupz);
	     
	     _nu_p4.SetPxPyPzE(nupx,nupy,nupz,nue);
	     
	     _H_p4 = _Hb1_p4+_Hb2_p4;
	     _W_p4 = _l_p4+_nu_p4;
	     _top_p4 = _W_p4+_topb_p4;
	     
	     // store variables for output
	     _topb_Top_p4 = _topb_p4;
	     _Hb1_Top_p4 = _Hb1_p4;
	     _Hb2_Top_p4 = _Hb2_p4;
	     _l_Top_p4 = _l_p4;
	     _nu_Top_p4 = _nu_p4;
	     _top_Top_p4 = _top_p4;
	     _H_Top_p4 = _H_p4;
	     _W_Top_p4 = _W_p4;		       
	     
	     truthMatchAlg();

	     bool isMatch = (_Hb1_match && _Hb2_match && _topb_match);
	     h_match->Fill(0.,w);
	     if( _Hb1_match && _Hb2_match ) h_match->Fill(1.,w);
	     if( _topb_match ) h_match->Fill(2.,w);
	     if( isMatch ) h_match->Fill(3.,w);
	     
	     fill(w,isMatch);
	     
	     m_weight = w;
	     m_match = isMatch;
	     m_id = id;
	     
	     if( _standalone )
	       _tree->Fill();
	  }
     }   

   // ttbar
   if( nLep == 1 && nbjets >= 3 && nnonbjets >= 1 && passGenFilt_ttbar )
     {
	m_matchAllTTbar = 0;
	
	if( nbjets >= 3 )
	  {
	     _l_p4.SetPtEtaPhiE(_v_Lepton->at(0).p4().Pt(),
				_v_Lepton->at(0).p4().PseudoRapidity(),
				_v_Lepton->at(0).p4().Phi(),
				_v_Lepton->at(0).p4().E());			    
	     
	     _nu_p4.SetPtEtaPhiE(metpt,
				 0,
				 metphi,
				 metE);
	     
	     truthMatchTTbar();
//	     bool isMatchAll = (_topbLep_match_all && _topbHad_match_all &&
//				_topWj1_match_all && _topWj2_match_all);
	     bool isMatchAll = (_topbLep_match_all && _topbHad_match_all);
	     h_matchAllTTbar->Fill(0.,w);
	     if( _topbLep_match_all ) h_matchAllTTbar->Fill(1.,w);
	     if( _topbHad_match_all ) h_matchAllTTbar->Fill(2.,w);
	     if( isMatchAll ) h_matchAllTTbar->Fill(3.,w);

	     m_matchAllTTbar = isMatchAll;
	  }
   
	if( _standalone ) _treeRecoTTbar->Fill();
	
	if( nbjets < 3 ) return 0;

	if( m_matchAllTTbar || !_standalone )
	  {
	     _topbLep_p4.SetPtEtaPhiE(0,0,0,0);
	     _topbHad_p4.SetPtEtaPhiE(0,0,0,0);
	     _topWj1_p4.SetPtEtaPhiE(0,0,0,0);
	     _topWj2_p4.SetPtEtaPhiE(0,0,0,0);
	     _topLep_p4.SetPtEtaPhiE(0,0,0,0);
	     _topHad_p4.SetPtEtaPhiE(0,0,0,0);
	     _WLep_p4.SetPtEtaPhiE(0,0,0,0);
	     _WHad_p4.SetPtEtaPhiE(0,0,0,0);

	     kf->Init(TOPTOPLEPHAD);

	     std::vector<float> BJetPt;
	     std::vector<float> BJetEta;
	     std::vector<float> BJetPhi;
	     std::vector<float> BJetE;
	     
	     std::vector<float> NonBJetPt;
	     std::vector<float> NonBJetEta;
	     std::vector<float> NonBJetPhi;
	     std::vector<float> NonBJetE;
	     
	     std::vector<float> ElectronPt;
	     std::vector<float> ElectronEta;
	     std::vector<float> ElectronPhi;
	     std::vector<float> ElectronE;
	     
	     std::vector<float> MuonPt;
	     std::vector<float> MuonEta;
	     std::vector<float> MuonPhi;
	     std::vector<float> MuonE;
	     
	     for(int i=0;i<_v_ElectronTight->size();i++)
	       {
		  ElectronPt.push_back(_v_ElectronTight->at(i).pt());
		  ElectronEta.push_back(_v_ElectronTight->at(i).eta());
		  ElectronPhi.push_back(_v_ElectronTight->at(i).phi());
		  ElectronE.push_back(_v_ElectronTight->at(i).E());
	       }   
	     
	     for(int i=0;i<_v_MuonTight->size();i++)
	       {
		  MuonPt.push_back(_v_MuonTight->at(i).pt());
		  MuonEta.push_back(_v_MuonTight->at(i).eta());
		  MuonPhi.push_back(_v_MuonTight->at(i).phi());
		  MuonE.push_back(_v_MuonTight->at(i).E());
	       }   
	     
	     int idx_nonBJet = -1;
	     float minCSV = 10E+10;
	     for(int i=0;i<_v_BJetTight->size();i++)
	       {
		  if( _v_BJetTight->at(i).CSVv2() < minCSV )
		    {		       
		       minCSV = _v_BJetTight->at(i).CSVv2();
		       idx_nonBJet = i;
		    }		  
	       }	  
	     
	     for(int i=0;i<_v_BJetTight->size();i++)
	       {
		  if( i == idx_nonBJet && _v_NonBJetTight->size() <= 1 ) continue;

		  BJetPt.push_back(_v_BJetTight->at(i).pt());
		  BJetEta.push_back(_v_BJetTight->at(i).eta());
		  BJetPhi.push_back(_v_BJetTight->at(i).phi());
		  BJetE.push_back(_v_BJetTight->at(i).E());
	       }   
	     
	     for(int i=0;i<_v_NonBJetTight->size();i++)
	       {
		  NonBJetPt.push_back(_v_NonBJetTight->at(i).pt());
		  NonBJetEta.push_back(_v_NonBJetTight->at(i).eta());
		  NonBJetPhi.push_back(_v_NonBJetTight->at(i).phi());
		  NonBJetE.push_back(_v_NonBJetTight->at(i).E());
	       }   
	     
	     if( _v_NonBJetTight->size() <= 1 )
	       {		  
		  for(int i=0;i<_v_BJetTight->size();i++)
		    {
		       if( i != idx_nonBJet ) continue;
		       
		       NonBJetPt.push_back(_v_BJetTight->at(i).pt());
		       NonBJetEta.push_back(_v_BJetTight->at(i).eta());
		       NonBJetPhi.push_back(_v_BJetTight->at(i).phi());
		       NonBJetE.push_back(_v_BJetTight->at(i).E());
		    }   
	       }	     
	     
	     kf->SetBJet(BJetPt,BJetEta,BJetPhi,BJetE);
	     kf->SetNonBJet(NonBJetPt,NonBJetEta,NonBJetPhi,NonBJetE);
	     kf->SetElectron(ElectronPt,ElectronEta,ElectronPhi,ElectronE);
	     kf->SetMuon(MuonPt,MuonEta,MuonPhi,MuonE);
	     kf->SetMet(metpx,metpy);
	     
	     kf->Run();	     
	     
	     _chi2TTbar = kf->GetDisc();
	     
	     int idx_BJETLEP_TOPTOPLEPHAD = kf->GetIndex(BJETLEP_TOPTOPLEPHAD,0);
	     int idx_BJETHAD_TOPTOPLEPHAD = kf->GetIndex(BJETHAD_TOPTOPLEPHAD,0);
	     int idx_NONBJET1_TOPTOPLEPHAD = kf->GetIndex(NONBJET1_TOPTOPLEPHAD,0);
	     int idx_NONBJET2_TOPTOPLEPHAD = kf->GetIndex(NONBJET2_TOPTOPLEPHAD,0);
	     int idx_ELECTRON_TOPTOPLEPHAD = kf->GetIndex(ELECTRON_TOPTOPLEPHAD,0);
	     int idx_MUON_TOPTOPLEPHAD = kf->GetIndex(MUON_TOPTOPLEPHAD,0);

	     _topbLep_p4.SetPtEtaPhiE(BJetPt[idx_BJETLEP_TOPTOPLEPHAD],
				      BJetEta[idx_BJETLEP_TOPTOPLEPHAD],
				      BJetPhi[idx_BJETLEP_TOPTOPLEPHAD],
				      BJetE[idx_BJETLEP_TOPTOPLEPHAD]);

	     _topbHad_p4.SetPtEtaPhiE(BJetPt[idx_BJETHAD_TOPTOPLEPHAD],
				      BJetEta[idx_BJETHAD_TOPTOPLEPHAD],
				      BJetPhi[idx_BJETHAD_TOPTOPLEPHAD],
				      BJetE[idx_BJETHAD_TOPTOPLEPHAD]);

	     _topWj1_p4.SetPtEtaPhiE(NonBJetPt[idx_NONBJET1_TOPTOPLEPHAD],
				     NonBJetEta[idx_NONBJET1_TOPTOPLEPHAD],
				     NonBJetPhi[idx_NONBJET1_TOPTOPLEPHAD],
				     NonBJetE[idx_NONBJET1_TOPTOPLEPHAD]);

	     _topWj2_p4.SetPtEtaPhiE(NonBJetPt[idx_NONBJET2_TOPTOPLEPHAD],
				     NonBJetEta[idx_NONBJET2_TOPTOPLEPHAD],
				     NonBJetPhi[idx_NONBJET2_TOPTOPLEPHAD],
				     NonBJetE[idx_NONBJET2_TOPTOPLEPHAD]);

	     if( idx_ELECTRON_TOPTOPLEPHAD >= 0 )
	       _l_p4.SetPtEtaPhiE(ElectronPt[idx_ELECTRON_TOPTOPLEPHAD],
				  ElectronEta[idx_ELECTRON_TOPTOPLEPHAD],
				  ElectronPhi[idx_ELECTRON_TOPTOPLEPHAD],
				  ElectronE[idx_ELECTRON_TOPTOPLEPHAD]);
	     else
	       _l_p4.SetPtEtaPhiE(MuonPt[idx_MUON_TOPTOPLEPHAD],
				  MuonEta[idx_MUON_TOPTOPLEPHAD],
				  MuonPhi[idx_MUON_TOPTOPLEPHAD],
				  MuonE[idx_MUON_TOPTOPLEPHAD]);

	     float nupx = kf->GetNuPx(0,0);
	     float nupy = kf->GetNuPy(0,0);
	     float nupz = kf->GetNuPz(0,0);
	     float nue = sqrt(nupx*nupx+nupy*nupy+nupz*nupz);
	     
	     _nu_p4.SetPxPyPzE(nupx,nupy,nupz,nue);

	     _WLep_p4 = _l_p4+_nu_p4;
	     _WHad_p4 = _topWj1_p4+_topWj2_p4;
	     _topLep_p4 = _WLep_p4+_topbLep_p4;
	     _topHad_p4 = _WHad_p4+_topbHad_p4;

	     // store variables for output
	     _topbLep_TTbar_p4 = _topbLep_p4;
	     _topbHad_TTbar_p4 = _topbHad_p4;
	     _topLep_TTbar_p4 = _topLep_p4;
	     _topHad_TTbar_p4 = _topHad_p4;
	     _topWj1_TTbar_p4 = _topWj1_p4;
	     _topWj2_TTbar_p4 = _topWj2_p4;
	     _l_TTbar_p4 = _l_p4;
	     _nu_TTbar_p4 = _nu_p4;
	     _WLep_TTbar_p4 = _WLep_p4;
	     _WHad_TTbar_p4 = _WHad_p4;
		  
	     truthMatchAlgTTbar();
	     
	     bool isMatch = (_topbLep_match && _topbHad_match);

	     m_weightTTbar = w;
	     m_matchTTbar = isMatch;
	     m_idTTbar = id;
	     
	     if( _standalone )
	       _treeTTbar->Fill();
	  }	
     }
   
   return 1;
}

void TopReco::truthMatchAlg()
{
   float drMatch = 0.4;
   
   // Hb1
   _Hb1_match = 0;
   bool match_Hb1_tHb1 = 0;
   bool match_Hb1_tHb2 = 0;
   float dr_Hb1_tHb1 = _Hb1_p4.DeltaR(_Hb1_truth_p4);
   float dr_Hb1_tHb2 = _Hb1_p4.DeltaR(_Hb2_truth_p4);
   if( dr_Hb1_tHb1 < drMatch ) match_Hb1_tHb1 = 1;
   if( dr_Hb1_tHb2 < drMatch ) match_Hb1_tHb2 = 1;
   
   // Hb2
   _Hb2_match = 0;
   bool match_Hb2_tHb1 = 0;
   bool match_Hb2_tHb2 = 0;
   float dr_Hb2_tHb1 = _Hb2_p4.DeltaR(_Hb1_truth_p4);
   float dr_Hb2_tHb2 = _Hb2_p4.DeltaR(_Hb2_truth_p4);
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
   float dr_topb_ttopb = _topb_p4.DeltaR(_topb_truth_p4);
   if( dr_topb_ttopb < drMatch ) _topb_match = 1;
}

void TopReco::truthMatchAlgTTbar()
{
   float drMatch = 0.4;
   
   // topbLep
   _topbLep_match = 0;
   float dr_topbLep = 10E+10;
   if( _is_top1_leptonic ) dr_topbLep = _topbLep_p4.DeltaR(_topb1_truth_p4);
   else dr_topbLep = _topbLep_p4.DeltaR(_topb2_truth_p4);
   if( dr_topbLep < drMatch ) _topbLep_match = 1;
   
   // topbHad
   _topbHad_match = 0;
   float dr_topbHad = 10E+10;
   if( _is_top1_leptonic ) dr_topbHad = _topbHad_p4.DeltaR(_topb2_truth_p4);
   else dr_topbHad = _topbHad_p4.DeltaR(_topb1_truth_p4);
   if( dr_topbHad < drMatch ) _topbHad_match = 1;
}

void TopReco::truthMatch()
{
   float drMatch = 0.4;
   
   int nbjets = _v_BJetTight->size();
   
   // Hb1
   _Hb1_match_all = 0;
   float dr_Hb1_Min = 666.;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_Hb1 = _v_BJetTight->at(ij).p4().DeltaR(_Hb1_truth_p4);
	if( dr_Hb1 < dr_Hb1_Min ) dr_Hb1_Min = dr_Hb1;
     }   
   if( dr_Hb1_Min < drMatch ) _Hb1_match_all = 1;

   // Hb2
   _Hb2_match_all = 0;
   float dr_Hb2_Min = 666.;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_Hb2 = _v_BJetTight->at(ij).p4().DeltaR(_Hb2_truth_p4);
	if( dr_Hb2 < dr_Hb2_Min ) dr_Hb2_Min = dr_Hb2;
     }   
   if( dr_Hb2_Min < drMatch ) _Hb2_match_all = 1;

   // topb
   _topb_match_all = 0;
   float dr_topb_Min = 666.;
   for(int ij=0;ij<nbjets;ij++)
     {	
	float dr_topb = _v_BJetTight->at(ij).p4().DeltaR(_topb_truth_p4);
	if( dr_topb < dr_topb_Min ) dr_topb_Min = dr_topb;
     }   
   if( dr_topb_Min < drMatch ) _topb_match_all = 1;
}

void TopReco::truthMatchTTbar()
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
	_topbLep_truthReco_p4 = _v_BJetTight->at(idxLep_Min).p4();
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
	_topbHad_truthReco_p4 = _v_BJetTight->at(idxHad_Min).p4();
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
	_topWl_truthReco_p4 = _v_Lepton->at(idxWl_Min).p4();
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
	_topWj1_truthReco_p4 = _v_JetTight->at(idxWj1_Min).p4();
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
	_topWj2_truthReco_p4 = _v_JetTight->at(idxWj2_Min).p4();
     }
   
   if( _topbHad_match_all && _topWj1_match_all && _topWj2_match_all )
     m_mTopHad = (_topbHad_truthReco_p4 + _topWj1_truthReco_p4 + _topWj2_truthReco_p4).M();
   else
     m_mTopHad = 0.;
}
   
void TopReco::fill(float w,bool isMatch)
{
   float H_m = _H_p4.M();
   h_H_m[0]->Fill(H_m,w);
   if( isMatch ) h_H_m[1]->Fill(H_m,w);
   else h_H_m[2]->Fill(H_m,w);
   
   float top_m = _top_p4.M();
   h_top_m[0]->Fill(top_m,w);
   if( isMatch ) h_top_m[1]->Fill(top_m,w);
   else h_top_m[2]->Fill(top_m,w);
   
   float W_m = _W_p4.M();
   h_W_m[0]->Fill(W_m,w);
   if( isMatch ) h_W_m[1]->Fill(W_m,w);
   else h_W_m[2]->Fill(W_m,w);
}

void TopReco::close()
{
   if( _standalone )
     {	
	_fout->Write();
	_fout->Close();
     }   
}
