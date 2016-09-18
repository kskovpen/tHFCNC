#include "../include/TopReco.h"

#include "TRandom3.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/type_traits.hpp>

struct sortFunc
{
   bool operator()(const std::pair<float,int> &left, const std::pair<float,int> &right)
     {
	return left.first > right.first;
     }
};

TopReco::TopReco()
{
   help = new Helper();
   
   _v_ElectronTight = new std::vector<Electron>;
   _v_MuonTight = new std::vector<Muon>;
   _v_JetTight = new std::vector<Jet>;
   _v_BJetTight = new std::vector<Jet>;
   _v_NonBJetTight = new std::vector<Jet>;
   
   kfTopTopLepHbb = new KINFIT::kfit();
   kfTopHLepbb = new KINFIT::kfit();
   kfTopTopLepHad = new KINFIT::kfit();
   
   MVAFullRecoReaderTOPTOPLEPHBB = new TMVA::Reader("!Color:!Silent");

   MVAFullRecoReaderTOPTOPLEPHBB->AddVariable("HiggsRecMCSVv2M",&MVAFullReco_HiggsRecM_TOPTOPLEPHBB);
   MVAFullRecoReaderTOPTOPLEPHBB->AddVariable("TopLepRecMCSVv2M",&MVAFullReco_TopLepRecM_TOPTOPLEPHBB);
   MVAFullRecoReaderTOPTOPLEPHBB->AddVariable("HiggsTopLepRecDrCSVv2M",&MVAFullReco_HiggsTopLepRecDr_TOPTOPLEPHBB);
   MVAFullRecoReaderTOPTOPLEPHBB->AddVariable("TopLepRecPtCSVv2M",&MVAFullReco_TopLepRecPt_TOPTOPLEPHBB);

   std::string weightsFileFullRecoTOPTOPLEPHBB = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_12/src/TopKinFit/test/Validation/TopTopLepHbb/MVA/weights/TMVAFullRecoCSVv2M_BDT.weights.xml";
   MVAFullRecoReaderTOPTOPLEPHBB->BookMVA("BDTG method",weightsFileFullRecoTOPTOPLEPHBB.c_str());
   
   MVAPartRecoReaderTOPTOPLEPHBB = new TMVA::Reader("!Color:!Silent");

   MVAPartRecoReaderTOPTOPLEPHBB->AddVariable("HiggsRecMCSVv2M",&MVAPartReco_HiggsRecM_TOPTOPLEPHBB);
   MVAPartRecoReaderTOPTOPLEPHBB->AddVariable("TopLepRecMTCSVv2M",&MVAPartReco_TopLepRecMT_TOPTOPLEPHBB);
   MVAPartRecoReaderTOPTOPLEPHBB->AddVariable("HiggsTopLepRecDphiTCSVv2M",&MVAPartReco_HiggsTopLepRecDphiT_TOPTOPLEPHBB);
   MVAPartRecoReaderTOPTOPLEPHBB->AddVariable("TopLepRecPtTCSVv2M",&MVAPartReco_TopLepRecPtT_TOPTOPLEPHBB);

   std::string weightsFilePartRecoTOPTOPLEPHBB = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_12/src/TopKinFit/test/Validation/TopTopLepHbb/MVA/weights/TMVAPartRecoCSVv2M_BDT.weights.xml";
   MVAPartRecoReaderTOPTOPLEPHBB->BookMVA("BDTG method",weightsFilePartRecoTOPTOPLEPHBB.c_str());
}

TopReco::~TopReco()
{
   delete help;
   
   delete _v_ElectronTight;
   delete _v_MuonTight;
   delete _v_JetTight;
   delete _v_BJetTight;
   delete _v_NonBJetTight;
   
   delete kfTopTopLepHbb;
   delete kfTopHLepbb;
   delete kfTopTopLepHad;
   
   delete MVAFullRecoReaderTOPTOPLEPHBB;
   delete MVAPartRecoReaderTOPTOPLEPHBB;
}

void TopReco::init()
{
   rnd = new TRandom3(666);

   kfTopTopLepHbb->Init(TOPTOPLEPHBB);
   
   std::string pdfFileNameTopTopLepHbb = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_12/src/TopKinFit/test/GenAnalysis/TopTopLepHbb/pdf.root";
   
   kfTopTopLepHbb->SetPDF("TopWMass",pdfFileNameTopTopLepHbb.c_str(),"TopLepWM_Fit");
   kfTopTopLepHbb->SetPDF("TopMass",pdfFileNameTopTopLepHbb.c_str(),"TopLepRecM_Fit");
   kfTopTopLepHbb->SetPDF("HiggsMass",pdfFileNameTopTopLepHbb.c_str(),"HiggsRecM_Fit");
   kfTopTopLepHbb->SetPDF("TopHadMass",pdfFileNameTopTopLepHbb.c_str(),"TopHadRecM_Fit");
   kfTopTopLepHbb->SetPDF("MetPx",pdfFileNameTopTopLepHbb.c_str(),"dMetPx_Gaus");
   kfTopTopLepHbb->SetPDF("MetPy",pdfFileNameTopTopLepHbb.c_str(),"dMetPy_Gaus");
   kfTopTopLepHbb->SetPDF("BJetPx",pdfFileNameTopTopLepHbb.c_str(),"dBJetPx_Fit");
   kfTopTopLepHbb->SetPDF("BJetPy",pdfFileNameTopTopLepHbb.c_str(),"dBJetPy_Fit");
   kfTopTopLepHbb->SetPDF("BJetPz",pdfFileNameTopTopLepHbb.c_str(),"dBJetPz_Fit");
   kfTopTopLepHbb->SetPDF("BJetE",pdfFileNameTopTopLepHbb.c_str(),"dBJetE_Fit");
   kfTopTopLepHbb->SetPDF("NonBJetPx",pdfFileNameTopTopLepHbb.c_str(),"dNonBJetPx_Fit");
   kfTopTopLepHbb->SetPDF("NonBJetPy",pdfFileNameTopTopLepHbb.c_str(),"dNonBJetPy_Fit");
   kfTopTopLepHbb->SetPDF("NonBJetPz",pdfFileNameTopTopLepHbb.c_str(),"dNonBJetPz_Fit");
   kfTopTopLepHbb->SetPDF("NonBJetE",pdfFileNameTopTopLepHbb.c_str(),"dNonBJetE_Fit");
   kfTopTopLepHbb->SetPDF("ElecPx",pdfFileNameTopTopLepHbb.c_str(),"dElecPx_Fit");
   kfTopTopLepHbb->SetPDF("ElecPy",pdfFileNameTopTopLepHbb.c_str(),"dElecPy_Fit");
   kfTopTopLepHbb->SetPDF("ElecPz",pdfFileNameTopTopLepHbb.c_str(),"dElecPz_Fit");
   kfTopTopLepHbb->SetPDF("ElecE",pdfFileNameTopTopLepHbb.c_str(),"dElecE_Fit");
   kfTopTopLepHbb->SetPDF("MuonPx",pdfFileNameTopTopLepHbb.c_str(),"dMuonPx_Fit");
   kfTopTopLepHbb->SetPDF("MuonPy",pdfFileNameTopTopLepHbb.c_str(),"dMuonPy_Fit");
   kfTopTopLepHbb->SetPDF("MuonPz",pdfFileNameTopTopLepHbb.c_str(),"dMuonPz_Fit");
   kfTopTopLepHbb->SetPDF("MuonE",pdfFileNameTopTopLepHbb.c_str(),"dMuonE_Fit");

   kfTopTopLepHbb->SetNToy(20);

   std::cout << "TopReco initialisation done" << std::endl;
}

void TopReco::run()
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

   for(int i=0;i<_v_Electron->size();i++)
     {
	if( _v_Electron->at(i).isTight() ) _v_ElectronTight->push_back(_v_Electron->at(i));
     }       
   
   for(int i=0;i<_v_Muon->size();i++)
     {
	if( _v_Muon->at(i).isTight() ) _v_MuonTight->push_back(_v_Muon->at(i));
     }      
   
   for(int i=0;i<_v_Jet->size();i++)
     {
	if( _v_Jet->at(i).isTight() )
	  {	     
	     _v_JetTight->push_back(_v_Jet->at(i));
	     if( _v_Jet->at(i).isBTag() ) _v_BJetTight->push_back(_v_Jet->at(i));
	     else _v_NonBJetTight->push_back(_v_Jet->at(i));
	  }	
     }

   int id = _v_Event->at(0).id();
   int run = _v_Event->at(0).run();
   int lumi = _v_Event->at(0).lumi();

   float metpt = _v_Event->at(0).metpt();
   float metphi = _v_Event->at(0).metphi();
   float metpx = metpt*cos(metphi);
   float metpy = metpt*sin(metphi);
   float metE = sqrt(metpx*metpx+metpy*metpy);
   
   int njets = _v_JetTight->size();
   int nbjets = _v_BJetTight->size();
   int nnonbjets = _v_NonBJetTight->size();
   
   int nLep = _v_ElectronTight->size()+_v_MuonTight->size();

   _chi2_TOPTOPLEPHBB = 10E+10;
   _chi2_TOPHLEPBB = 10E+10;
   _chi2_TOPTOPLEPHAD = 10E+10;
   
   // tH ttbar
   if( nLep == 1 && nbjets >= 3 && nnonbjets >= 1 )
     {		
	_TopLepBJet_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
	_HiggsBJet1_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
	_HiggsBJet2_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
	_TopLepWLep_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
        _TopLepWNu_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
	_TopLep_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
	_Higgs_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
	_TopLepW_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
	_TopHadNonBJet_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
	
	kfTopTopLepHbb->Init(TOPTOPLEPHBB);
	
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
	
	kfTopTopLepHbb->SetBJet(BJetPt,BJetEta,BJetPhi,BJetE);
	kfTopTopLepHbb->SetNonBJet(NonBJetPt,NonBJetEta,NonBJetPhi,NonBJetE);
	kfTopTopLepHbb->SetElectron(ElectronPt,ElectronEta,ElectronPhi,ElectronE);
	kfTopTopLepHbb->SetMuon(MuonPt,MuonEta,MuonPhi,MuonE);
	kfTopTopLepHbb->SetMet(metpx,metpy);
	
	kfTopTopLepHbb->Run();

	std::vector<std::pair<float,int> > MVADisc;
	
	int nPerm = kfTopTopLepHbb->GetNPerm();
	
	for(int ip=0;ip<nPerm;ip++)
	  {
	     float disc = kfTopTopLepHbb->GetDisc(ip);

	     int idx_ELECTRON_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(ELECTRON_TOPTOPLEPHBB,ip);
	     int idx_MUON_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(MUON_TOPTOPLEPHBB,ip);
	     int idx_BJETLEP_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(BJETLEP_TOPTOPLEPHBB,ip);
	     int idx_NONBJETHAD_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(NONBJETHAD_TOPTOPLEPHBB,ip);
	     int idx_BJET1_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(BJET1_TOPTOPLEPHBB,ip);
	     int idx_BJET2_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(BJET2_TOPTOPLEPHBB,ip);

	     float NuPx = kfTopTopLepHbb->GetNuPx(ip,0);
	     float NuPy = kfTopTopLepHbb->GetNuPy(ip,0);
	     float NuPz = kfTopTopLepHbb->GetNuPz(ip,0);
	     float NuE = sqrt(NuPx*NuPx+NuPy*NuPy+NuPz*NuPz);

	     _TopLepWNu_TOPTOPLEPHBB_p4.SetPxPyPzE(NuPx,NuPy,NuPz,NuE);
	     
	     _HiggsBJet1_TOPTOPLEPHBB_p4.SetPtEtaPhiE(BJetPt[idx_BJET1_TOPTOPLEPHBB],
						      BJetEta[idx_BJET1_TOPTOPLEPHBB],
						      BJetPhi[idx_BJET1_TOPTOPLEPHBB],
						      BJetE[idx_BJET1_TOPTOPLEPHBB]);
	     
	     _HiggsBJet2_TOPTOPLEPHBB_p4.SetPtEtaPhiE(BJetPt[idx_BJET2_TOPTOPLEPHBB],
						      BJetEta[idx_BJET2_TOPTOPLEPHBB],
						      BJetPhi[idx_BJET2_TOPTOPLEPHBB],
						      BJetE[idx_BJET2_TOPTOPLEPHBB]);
	     
	     _TopLepBJet_TOPTOPLEPHBB_p4.SetPtEtaPhiE(BJetPt[idx_BJETLEP_TOPTOPLEPHBB],
						      BJetEta[idx_BJETLEP_TOPTOPLEPHBB],
						      BJetPhi[idx_BJETLEP_TOPTOPLEPHBB],
						      BJetE[idx_BJETLEP_TOPTOPLEPHBB]);
	     
	     _TopHadNonBJet_TOPTOPLEPHBB_p4.SetPtEtaPhiE(NonBJetPt[idx_NONBJETHAD_TOPTOPLEPHBB],
							 NonBJetEta[idx_NONBJETHAD_TOPTOPLEPHBB],
							 NonBJetPhi[idx_NONBJETHAD_TOPTOPLEPHBB],
							 NonBJetE[idx_NONBJETHAD_TOPTOPLEPHBB]);
	     
	     if( idx_ELECTRON_TOPTOPLEPHBB >= 0 )
	       _TopLepWLep_TOPTOPLEPHBB_p4.SetPtEtaPhiE(ElectronPt[idx_ELECTRON_TOPTOPLEPHBB],
							ElectronEta[idx_ELECTRON_TOPTOPLEPHBB],
							ElectronPhi[idx_ELECTRON_TOPTOPLEPHBB],
							ElectronE[idx_ELECTRON_TOPTOPLEPHBB]);
	     else
	       _TopLepWLep_TOPTOPLEPHBB_p4.SetPtEtaPhiE(MuonPt[idx_MUON_TOPTOPLEPHBB],
							MuonEta[idx_MUON_TOPTOPLEPHBB],
							MuonPhi[idx_MUON_TOPTOPLEPHBB],
							MuonE[idx_MUON_TOPTOPLEPHBB]);
	     
	     _Higgs_TOPTOPLEPHBB_p4 = _HiggsBJet1_TOPTOPLEPHBB_p4+_HiggsBJet2_TOPTOPLEPHBB_p4;
	     _TopLepW_TOPTOPLEPHBB_p4 = _TopLepWLep_TOPTOPLEPHBB_p4+_TopLepWNu_TOPTOPLEPHBB_p4;
	     _TopLep_TOPTOPLEPHBB_p4 = _TopLepW_TOPTOPLEPHBB_p4+_TopLepBJet_TOPTOPLEPHBB_p4;

	     float VarHiggsRecM = _Higgs_TOPTOPLEPHBB_p4.M();
	     float VarTopLepRecM = _TopLep_TOPTOPLEPHBB_p4.M();
	     float VarHiggsTopLepRecDr = _Higgs_TOPTOPLEPHBB_p4.DeltaR(_TopLep_TOPTOPLEPHBB_p4);
	     float VarTopLepRecPt = _TopLep_TOPTOPLEPHBB_p4.Pt();
	     
	     _HiggsT_TOPTOPLEPHBB_p4.SetPxPyPzE(_Higgs_TOPTOPLEPHBB_p4.Px(),_Higgs_TOPTOPLEPHBB_p4.Py(),0.,_Higgs_TOPTOPLEPHBB_p4.Et());
	     
	     _TopLepWLepT_TOPTOPLEPHBB_p4.SetPxPyPzE(_TopLepWLep_TOPTOPLEPHBB_p4.Px(),_TopLepWLep_TOPTOPLEPHBB_p4.Py(),0.,_TopLepWLep_TOPTOPLEPHBB_p4.Et());
	     
	     _TopLepWNuT_TOPTOPLEPHBB_p4.SetPxPyPzE(_TopLepWNu_TOPTOPLEPHBB_p4.Px(),_TopLepWNu_TOPTOPLEPHBB_p4.Py(),0.,_TopLepWNu_TOPTOPLEPHBB_p4.Et());
	     
	     _TopLepBJetT_TOPTOPLEPHBB_p4.SetPxPyPzE(_TopLepBJet_TOPTOPLEPHBB_p4.Px(),_TopLepBJet_TOPTOPLEPHBB_p4.Py(),0.,_TopLepBJet_TOPTOPLEPHBB_p4.Et());
	     
	     _TopLepT_TOPTOPLEPHBB_p4 = _TopLepWLepT_TOPTOPLEPHBB_p4+_TopLepWNuT_TOPTOPLEPHBB_p4+_TopLepBJetT_TOPTOPLEPHBB_p4;
	     
	     float VarTopLepRecMT = _TopLepT_TOPTOPLEPHBB_p4.M();
	     float VarHiggsTopLepRecDphiT = _HiggsT_TOPTOPLEPHBB_p4.DeltaPhi(_TopLepT_TOPTOPLEPHBB_p4);
	     float VarTopLepRecPtT = _TopLepT_TOPTOPLEPHBB_p4.Pt();
	     
	     if( disc < 10E+8 )
	       {
		  MVAFullReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecM;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHBB = VarTopLepRecM;
		  MVAFullReco_HiggsTopLepRecDr_TOPTOPLEPHBB = VarHiggsTopLepRecDr;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHBB = VarTopLepRecPt;
		  
		  MVADisc.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));
	       }	
	     else
	       {
		  MVAPartReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecM;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHBB = VarTopLepRecMT;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPTOPLEPHBB = VarHiggsTopLepRecDphiT;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHBB = VarTopLepRecPtT;
		  
		  MVADisc.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));
	       }	     
	  }
	
	std::sort(MVADisc.begin(),MVADisc.end(),sortFunc());
	int IdxPerm = MVADisc.at(0).second;
	
	_chi2_TOPTOPLEPHBB = kfTopTopLepHbb->GetDisc(IdxPerm);
     }
}
