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
   std::string weightsFileFullRecoTOPTOPLEPHBB = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/TopKinFit/test/Validation/TopTopLepHbb/MVA/weights/TMVAFullRecoCSVv2M_BDT.weights.xml";
   MVAFullRecoReaderTOPTOPLEPHBB->BookMVA("BDTG method",weightsFileFullRecoTOPTOPLEPHBB.c_str());
   
   MVAPartRecoReaderTOPTOPLEPHBB = new TMVA::Reader("!Color:!Silent");
   MVAPartRecoReaderTOPTOPLEPHBB->AddVariable("HiggsRecMCSVv2M",&MVAPartReco_HiggsRecM_TOPTOPLEPHBB);
   MVAPartRecoReaderTOPTOPLEPHBB->AddVariable("TopLepRecMTCSVv2M",&MVAPartReco_TopLepRecMT_TOPTOPLEPHBB);
   MVAPartRecoReaderTOPTOPLEPHBB->AddVariable("HiggsTopLepRecDphiTCSVv2M",&MVAPartReco_HiggsTopLepRecDphiT_TOPTOPLEPHBB);
   MVAPartRecoReaderTOPTOPLEPHBB->AddVariable("TopLepRecPtTCSVv2M",&MVAPartReco_TopLepRecPtT_TOPTOPLEPHBB);
   std::string weightsFilePartRecoTOPTOPLEPHBB = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/TopKinFit/test/Validation/TopTopLepHbb/MVA/weights/TMVAPartRecoCSVv2M_BDT.weights.xml";
   MVAPartRecoReaderTOPTOPLEPHBB->BookMVA("BDTG method",weightsFilePartRecoTOPTOPLEPHBB.c_str());

   MVAFullRecoReaderTOPHLEPBB = new TMVA::Reader("!Color:!Silent");
   MVAFullRecoReaderTOPHLEPBB->AddVariable("HiggsRecMCSVv2M",&MVAFullReco_HiggsRecM_TOPHLEPBB);
   MVAFullRecoReaderTOPHLEPBB->AddVariable("TopLepRecMCSVv2M",&MVAFullReco_TopLepRecM_TOPHLEPBB);
   MVAFullRecoReaderTOPHLEPBB->AddVariable("HiggsTopLepRecDrCSVv2M",&MVAFullReco_HiggsTopLepRecDr_TOPHLEPBB);
   MVAFullRecoReaderTOPHLEPBB->AddVariable("TopLepRecPtCSVv2M",&MVAFullReco_TopLepRecPt_TOPHLEPBB);
   std::string weightsFileFullRecoTOPHLEPBB = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/TopKinFit/test/Validation/TopHLepbb/MVA/weights/TMVAFullRecoHutCSVv2M_BDT.weights.xml";
   MVAFullRecoReaderTOPHLEPBB->BookMVA("BDTG method",weightsFileFullRecoTOPHLEPBB.c_str());
   
   MVAPartRecoReaderTOPHLEPBB = new TMVA::Reader("!Color:!Silent");
   MVAPartRecoReaderTOPHLEPBB->AddVariable("HiggsRecMCSVv2M",&MVAPartReco_HiggsRecM_TOPHLEPBB);
   MVAPartRecoReaderTOPHLEPBB->AddVariable("TopLepRecMTCSVv2M",&MVAPartReco_TopLepRecMT_TOPHLEPBB);
   MVAPartRecoReaderTOPHLEPBB->AddVariable("HiggsTopLepRecDphiTCSVv2M",&MVAPartReco_HiggsTopLepRecDphiT_TOPHLEPBB);
   MVAPartRecoReaderTOPHLEPBB->AddVariable("TopLepRecPtTCSVv2M",&MVAPartReco_TopLepRecPtT_TOPHLEPBB);
   std::string weightsFilePartRecoTOPHLEPBB = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/TopKinFit/test/Validation/TopHLepbb/MVA/weights/TMVAPartRecoHutCSVv2M_BDT.weights.xml";
   MVAPartRecoReaderTOPHLEPBB->BookMVA("BDTG method",weightsFilePartRecoTOPHLEPBB.c_str());

   MVAFullRecoReaderTOPTOPLEPHAD = new TMVA::Reader("!Color:!Silent");
   MVAFullRecoReaderTOPTOPLEPHAD->AddVariable("TopHadRecMCSVv2M",&MVAFullReco_TopHadRecM_TOPTOPLEPHAD);
   MVAFullRecoReaderTOPTOPLEPHAD->AddVariable("TopLepRecMCSVv2M",&MVAFullReco_TopLepRecM_TOPTOPLEPHAD);
   MVAFullRecoReaderTOPTOPLEPHAD->AddVariable("TopLepTopHadRecDrCSVv2M",&MVAFullReco_TopLepTopHadRecDr_TOPTOPLEPHAD);
   MVAFullRecoReaderTOPTOPLEPHAD->AddVariable("TopLepRecPtCSVv2M",&MVAFullReco_TopLepRecPt_TOPTOPLEPHAD);
   std::string weightsFileFullRecoTOPTOPLEPHAD = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/TopKinFit/test/Validation/TopTopLepHad/MVA/weights/TMVAFullRecoCSVv2M_BDT.weights.xml";
   MVAFullRecoReaderTOPTOPLEPHAD->BookMVA("BDTG method",weightsFileFullRecoTOPTOPLEPHAD.c_str());
   
   MVAPartRecoReaderTOPTOPLEPHAD = new TMVA::Reader("!Color:!Silent");
   MVAPartRecoReaderTOPTOPLEPHAD->AddVariable("TopHadRecMCSVv2M",&MVAPartReco_TopHadRecM_TOPTOPLEPHAD);
   MVAPartRecoReaderTOPTOPLEPHAD->AddVariable("TopLepRecMTCSVv2M",&MVAPartReco_TopLepRecMT_TOPTOPLEPHAD);
   MVAPartRecoReaderTOPTOPLEPHAD->AddVariable("TopLepTopHadRecDphiTCSVv2M",&MVAPartReco_TopLepTopHadRecDphiT_TOPTOPLEPHAD);
   MVAPartRecoReaderTOPTOPLEPHAD->AddVariable("TopLepRecPtTCSVv2M",&MVAPartReco_TopLepRecPtT_TOPTOPLEPHAD);
   std::string weightsFilePartRecoTOPTOPLEPHAD = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/TopKinFit/test/Validation/TopTopLepHad/MVA/weights/TMVAPartRecoCSVv2M_BDT.weights.xml";
   MVAPartRecoReaderTOPTOPLEPHAD->BookMVA("BDTG method",weightsFilePartRecoTOPTOPLEPHAD.c_str());
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

   delete MVAFullRecoReaderTOPHLEPBB;
   delete MVAPartRecoReaderTOPHLEPBB;

   delete MVAFullRecoReaderTOPTOPLEPHAD;
   delete MVAPartRecoReaderTOPTOPLEPHAD;
}

void TopReco::init()
{
   kfTopTopLepHbb->Init(TOPTOPLEPHBB);
   
   std::string pdfFileNameTopTopLepHbb = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/TopKinFit/test/GenAnalysis/TopTopLepHbb/pdf.root";
   
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

   kfTopHLepbb->Init(TOPHLEPBB);
   
   std::string pdfFileNameTopHLepbb = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/TopKinFit/test/GenAnalysis/TopHLepbb/pdf.root";
   
   kfTopHLepbb->SetPDF("TopWMass",pdfFileNameTopHLepbb.c_str(),"TopLepWM_Fit");
   kfTopHLepbb->SetPDF("TopMass",pdfFileNameTopHLepbb.c_str(),"TopLepRecM_Fit");
   kfTopHLepbb->SetPDF("HiggsMass",pdfFileNameTopHLepbb.c_str(),"HiggsRecM_Fit");
   kfTopHLepbb->SetPDF("MetPx",pdfFileNameTopHLepbb.c_str(),"dMetPx_Gaus");
   kfTopHLepbb->SetPDF("MetPy",pdfFileNameTopHLepbb.c_str(),"dMetPy_Gaus");
   kfTopHLepbb->SetPDF("BJetPx",pdfFileNameTopHLepbb.c_str(),"dBJetPx_Fit");
   kfTopHLepbb->SetPDF("BJetPy",pdfFileNameTopHLepbb.c_str(),"dBJetPy_Fit");
   kfTopHLepbb->SetPDF("BJetPz",pdfFileNameTopHLepbb.c_str(),"dBJetPz_Fit");
   kfTopHLepbb->SetPDF("BJetE",pdfFileNameTopHLepbb.c_str(),"dBJetE_Fit");
   kfTopHLepbb->SetPDF("ElecPx",pdfFileNameTopHLepbb.c_str(),"dElecPx_Fit");
   kfTopHLepbb->SetPDF("ElecPy",pdfFileNameTopHLepbb.c_str(),"dElecPy_Fit");
   kfTopHLepbb->SetPDF("ElecPz",pdfFileNameTopHLepbb.c_str(),"dElecPz_Fit");
   kfTopHLepbb->SetPDF("ElecE",pdfFileNameTopHLepbb.c_str(),"dElecE_Fit");
   kfTopHLepbb->SetPDF("MuonPx",pdfFileNameTopHLepbb.c_str(),"dMuonPx_Fit");
   kfTopHLepbb->SetPDF("MuonPy",pdfFileNameTopHLepbb.c_str(),"dMuonPy_Fit");
   kfTopHLepbb->SetPDF("MuonPz",pdfFileNameTopHLepbb.c_str(),"dMuonPz_Fit");
   kfTopHLepbb->SetPDF("MuonE",pdfFileNameTopHLepbb.c_str(),"dMuonE_Fit");

   kfTopHLepbb->SetNToy(20);

   kfTopTopLepHad->Init(TOPTOPLEPHAD);
   
   std::string pdfFileNameTopTopLepHad = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/TopKinFit/test/GenAnalysis/TopTopLepHad/pdf.root";
   
   kfTopTopLepHad->SetPDF("TopWMass",pdfFileNameTopTopLepHad.c_str(),"TopLepWM_Fit");
   kfTopTopLepHad->SetPDF("TopMass",pdfFileNameTopTopLepHad.c_str(),"TopLepRecM_Fit");
   kfTopTopLepHad->SetPDF("TopWHadMass",pdfFileNameTopTopLepHad.c_str(),"TopHadWRecM_Fit");
   kfTopTopLepHad->SetPDF("TopHadMass",pdfFileNameTopTopLepHad.c_str(),"TopHadRecM_Fit");
   kfTopTopLepHad->SetPDF("MetPx",pdfFileNameTopTopLepHad.c_str(),"dMetPx_Gaus");
   kfTopTopLepHad->SetPDF("MetPy",pdfFileNameTopTopLepHad.c_str(),"dMetPy_Gaus");
   kfTopTopLepHad->SetPDF("BJetPx",pdfFileNameTopTopLepHad.c_str(),"dBJetPx_Fit");
   kfTopTopLepHad->SetPDF("BJetPy",pdfFileNameTopTopLepHad.c_str(),"dBJetPy_Fit");
   kfTopTopLepHad->SetPDF("BJetPz",pdfFileNameTopTopLepHad.c_str(),"dBJetPz_Fit");
   kfTopTopLepHad->SetPDF("BJetE",pdfFileNameTopTopLepHad.c_str(),"dBJetE_Fit");
   kfTopTopLepHad->SetPDF("NonBJetPx",pdfFileNameTopTopLepHad.c_str(),"dNonBJetPx_Fit");
   kfTopTopLepHad->SetPDF("NonBJetPy",pdfFileNameTopTopLepHad.c_str(),"dNonBJetPy_Fit");
   kfTopTopLepHad->SetPDF("NonBJetPz",pdfFileNameTopTopLepHad.c_str(),"dNonBJetPz_Fit");
   kfTopTopLepHad->SetPDF("NonBJetE",pdfFileNameTopTopLepHad.c_str(),"dNonBJetE_Fit");
   kfTopTopLepHad->SetPDF("ElecPx",pdfFileNameTopTopLepHad.c_str(),"dElecPx_Fit");
   kfTopTopLepHad->SetPDF("ElecPy",pdfFileNameTopTopLepHad.c_str(),"dElecPy_Fit");
   kfTopTopLepHad->SetPDF("ElecPz",pdfFileNameTopTopLepHad.c_str(),"dElecPz_Fit");
   kfTopTopLepHad->SetPDF("ElecE",pdfFileNameTopTopLepHad.c_str(),"dElecE_Fit");
   kfTopTopLepHad->SetPDF("MuonPx",pdfFileNameTopTopLepHad.c_str(),"dMuonPx_Fit");
   kfTopTopLepHad->SetPDF("MuonPy",pdfFileNameTopTopLepHad.c_str(),"dMuonPy_Fit");
   kfTopTopLepHad->SetPDF("MuonPz",pdfFileNameTopTopLepHad.c_str(),"dMuonPz_Fit");
   kfTopTopLepHad->SetPDF("MuonE",pdfFileNameTopTopLepHad.c_str(),"dMuonE_Fit");

   kfTopTopLepHad->SetNToy(20);
   
   std::cout << "TopReco initialisation done" << std::endl;
}

void TopReco::run()
{
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

   _MVA_TOPTOPLEPHBB = 10E+10;
   _MVAJesUp_TOPTOPLEPHBB = 10E+10;
   _MVAJesDown_TOPTOPLEPHBB = 10E+10;
   _MVAJerUp_TOPTOPLEPHBB = 10E+10;
   _MVAJerDown_TOPTOPLEPHBB = 10E+10;
   
   _MVA_TOPHLEPBB = 10E+10;
   _MVAJesUp_TOPHLEPBB = 10E+10;
   _MVAJesDown_TOPHLEPBB = 10E+10;
   _MVAJerUp_TOPHLEPBB = 10E+10;
   _MVAJerDown_TOPHLEPBB = 10E+10;
   
   _MVA_TOPTOPLEPHAD = 10E+10;
   _MVAJesUp_TOPTOPLEPHAD = 10E+10;
   _MVAJesDown_TOPTOPLEPHAD = 10E+10;
   _MVAJerUp_TOPTOPLEPHAD = 10E+10;
   _MVAJerDown_TOPTOPLEPHAD = 10E+10;

   // nominal
   _TopLepBJet_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet1_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet2_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLepWLep_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLepWNu_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
   _Higgs_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLepW_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadNonBJet_TOPTOPLEPHBB_p4.SetPtEtaPhiE(0,0,0,0);

   _TopLepBJet_TOPHLEPBB_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet1_TOPHLEPBB_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet2_TOPHLEPBB_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLepWLep_TOPHLEPBB_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLepWNu_TOPHLEPBB_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPHLEPBB_p4.SetPtEtaPhiE(0,0,0,0);
   _Higgs_TOPHLEPBB_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLepW_TOPHLEPBB_p4.SetPtEtaPhiE(0,0,0,0);

   _TopLepBJet_TOPTOPLEPHAD_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadWNonBJet1_TOPTOPLEPHAD_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadWNonBJet2_TOPTOPLEPHAD_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLepWLep_TOPTOPLEPHAD_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLepWNu_TOPTOPLEPHAD_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPTOPLEPHAD_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHad_TOPTOPLEPHAD_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadW_TOPTOPLEPHAD_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLepW_TOPTOPLEPHAD_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadBJet_TOPTOPLEPHAD_p4.SetPtEtaPhiE(0,0,0,0);

   // JesUp
   _TopLepBJet_TOPTOPLEPHBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet1_TOPTOPLEPHBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet2_TOPTOPLEPHBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPTOPLEPHBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _Higgs_TOPTOPLEPHBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadNonBJet_TOPTOPLEPHBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);

   _TopLepBJet_TOPHLEPBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet1_TOPHLEPBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet2_TOPHLEPBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPHLEPBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _Higgs_TOPHLEPBB_JesUp_p4.SetPtEtaPhiE(0,0,0,0);

   _TopLepBJet_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHad_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadW_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadBJet_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(0,0,0,0);

   // JesDown
   _TopLepBJet_TOPTOPLEPHBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet1_TOPTOPLEPHBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet2_TOPTOPLEPHBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPTOPLEPHBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _Higgs_TOPTOPLEPHBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadNonBJet_TOPTOPLEPHBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);

   _TopLepBJet_TOPHLEPBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet1_TOPHLEPBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet2_TOPHLEPBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPHLEPBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _Higgs_TOPHLEPBB_JesDown_p4.SetPtEtaPhiE(0,0,0,0);

   _TopLepBJet_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHad_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadW_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadBJet_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(0,0,0,0);

   // JerUp
   _TopLepBJet_TOPTOPLEPHBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet1_TOPTOPLEPHBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet2_TOPTOPLEPHBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPTOPLEPHBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _Higgs_TOPTOPLEPHBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadNonBJet_TOPTOPLEPHBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);

   _TopLepBJet_TOPHLEPBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet1_TOPHLEPBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet2_TOPHLEPBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPHLEPBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _Higgs_TOPHLEPBB_JerUp_p4.SetPtEtaPhiE(0,0,0,0);

   _TopLepBJet_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHad_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadW_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadBJet_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(0,0,0,0);

   // JerDown
   _TopLepBJet_TOPTOPLEPHBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet1_TOPTOPLEPHBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet2_TOPTOPLEPHBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPTOPLEPHBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _Higgs_TOPTOPLEPHBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadNonBJet_TOPTOPLEPHBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);

   _TopLepBJet_TOPHLEPBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet1_TOPHLEPBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _HiggsBJet2_TOPHLEPBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPHLEPBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _Higgs_TOPHLEPBB_JerDown_p4.SetPtEtaPhiE(0,0,0,0);

   _TopLepBJet_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopLep_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHad_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadW_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   _TopHadBJet_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(0,0,0,0);
   
   _TopLepBJet_TOPTOPLEPHBB_CSVv2 = 10E+10;
   _HiggsBJet1_TOPTOPLEPHBB_CSVv2 = 10E+10;
   _HiggsBJet2_TOPTOPLEPHBB_CSVv2 = 10E+10;
   _TopHadNonBJet_TOPTOPLEPHBB_CSVv2 = 10E+10;

   _TopLepBJet_TOPHLEPBB_CSVv2 = 10E+10;
   _HiggsBJet1_TOPHLEPBB_CSVv2 = 10E+10;
   _HiggsBJet2_TOPHLEPBB_CSVv2 = 10E+10;

   _TopLepBJet_TOPTOPLEPHAD_CSVv2 = 10E+10;
   _TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2 = 10E+10;
   _TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2 = 10E+10;
   _TopHadBJet_TOPTOPLEPHAD_CSVv2 = 10E+10;

   _TopLepBJet_TOPTOPLEPHBB_charge = 10E+10;
   _HiggsBJet1_TOPTOPLEPHBB_charge = 10E+10;
   _HiggsBJet2_TOPTOPLEPHBB_charge = 10E+10;
   _TopHadNonBJet_TOPTOPLEPHBB_charge = 10E+10;

   _TopLepBJet_TOPHLEPBB_charge = 10E+10;
   _HiggsBJet1_TOPHLEPBB_charge = 10E+10;
   _HiggsBJet2_TOPHLEPBB_charge = 10E+10;

   _TopLepBJet_TOPTOPLEPHAD_charge = 10E+10;
   _TopHadWNonBJet1_TOPTOPLEPHAD_charge = 10E+10;
   _TopHadWNonBJet2_TOPTOPLEPHAD_charge = 10E+10;
   _TopHadBJet_TOPTOPLEPHAD_charge = 10E+10;

   _TopLepBJet_TOPTOPLEPHBB_chargeVec = 10E+10;
   _HiggsBJet1_TOPTOPLEPHBB_chargeVec = 10E+10;
   _HiggsBJet2_TOPTOPLEPHBB_chargeVec = 10E+10;
   _TopHadNonBJet_TOPTOPLEPHBB_chargeVec = 10E+10;

   _TopLepBJet_TOPHLEPBB_chargeVec = 10E+10;
   _HiggsBJet1_TOPHLEPBB_chargeVec = 10E+10;
   _HiggsBJet2_TOPHLEPBB_chargeVec = 10E+10;

   _TopLepBJet_TOPTOPLEPHAD_chargeVec = 10E+10;
   _TopHadWNonBJet1_TOPTOPLEPHAD_chargeVec = 10E+10;
   _TopHadWNonBJet2_TOPTOPLEPHAD_chargeVec = 10E+10;
   _TopHadBJet_TOPTOPLEPHAD_chargeVec = 10E+10;

   _TopLepBJet_TOPTOPLEPHBB_CharmCvsL = 10E+10;
   _HiggsBJet1_TOPTOPLEPHBB_CharmCvsL = 10E+10;
   _HiggsBJet2_TOPTOPLEPHBB_CharmCvsL = 10E+10;
   _TopHadNonBJet_TOPTOPLEPHBB_CharmCvsL = 10E+10;

   _TopLepBJet_TOPHLEPBB_CharmCvsL = 10E+10;
   _HiggsBJet1_TOPHLEPBB_CharmCvsL = 10E+10;
   _HiggsBJet2_TOPHLEPBB_CharmCvsL = 10E+10;

   _TopLepBJet_TOPTOPLEPHAD_CharmCvsL = 10E+10;
   _TopHadWNonBJet1_TOPTOPLEPHAD_CharmCvsL = 10E+10;
   _TopHadWNonBJet2_TOPTOPLEPHAD_CharmCvsL = 10E+10;
   _TopHadBJet_TOPTOPLEPHAD_CharmCvsL = 10E+10;

   _TopLepBJet_TOPTOPLEPHBB_CharmCvsB = 10E+10;
   _HiggsBJet1_TOPTOPLEPHBB_CharmCvsB = 10E+10;
   _HiggsBJet2_TOPTOPLEPHBB_CharmCvsB = 10E+10;
   _TopHadNonBJet_TOPTOPLEPHBB_CharmCvsB = 10E+10;

   _TopLepBJet_TOPHLEPBB_CharmCvsB = 10E+10;
   _HiggsBJet1_TOPHLEPBB_CharmCvsB = 10E+10;
   _HiggsBJet2_TOPHLEPBB_CharmCvsB = 10E+10;

   _TopLepBJet_TOPTOPLEPHAD_CharmCvsB = 10E+10;
   _TopHadWNonBJet1_TOPTOPLEPHAD_CharmCvsB = 10E+10;
   _TopHadWNonBJet2_TOPTOPLEPHAD_CharmCvsB = 10E+10;
   _TopHadBJet_TOPTOPLEPHAD_CharmCvsB = 10E+10;

   _HiggsBJet1_TOPTOPLEPHBB_JetIdx = -1;
   _HiggsBJet2_TOPTOPLEPHBB_JetIdx = -1;
   _TopLepBJet_TOPTOPLEPHBB_JetIdx = -1;
   _TopHadNonBJet_TOPTOPLEPHBB_JetIdx = -1;

   _HiggsBJet1_TOPHLEPBB_JetIdx = -1;
   _HiggsBJet2_TOPHLEPBB_JetIdx = -1;
   _TopLepBJet_TOPHLEPBB_JetIdx = -1;

   _TopLepBJet_TOPTOPLEPHAD_JetIdx = -1;
   _TopHadBJet_TOPTOPLEPHAD_JetIdx = -1;
   _TopHadWNonBJet1_TOPTOPLEPHAD_JetIdx = -1;
   _TopHadWNonBJet2_TOPTOPLEPHAD_JetIdx = -1;
   
   // tH ttbar
   if( nLep == 1 && ((nbjets == 0 && nnonbjets >= 4) ||
		     (nbjets == 1 && nnonbjets >= 3) ||
		     (nbjets == 2 && nnonbjets >= 2) ||
		     (nbjets == 3 && nnonbjets >= 1) ||
		     (nbjets >= 4 && nnonbjets >= 0)) )
     {		
	kfTopTopLepHbb->Init(TOPTOPLEPHBB);
	
	std::vector<float> BJetPt;
	std::vector<float> BJetEta;
	std::vector<float> BJetPhi;
	std::vector<float> BJetE;
	std::vector<float> BJetCSVv2;
	std::vector<float> BJetCharge;
	std::vector<float> BJetChargeVec;
	std::vector<float> BJetCharmCvsL;
	std::vector<float> BJetCharmCvsB;
	std::vector<float> BJetPtJesUp;
	std::vector<float> BJetEtaJesUp;
	std::vector<float> BJetPhiJesUp;
	std::vector<float> BJetEJesUp;
	std::vector<float> BJetPtJesDown;
	std::vector<float> BJetEtaJesDown;
	std::vector<float> BJetPhiJesDown;
	std::vector<float> BJetEJesDown;
	std::vector<float> BJetPtJerUp;
	std::vector<float> BJetEtaJerUp;
	std::vector<float> BJetPhiJerUp;
	std::vector<float> BJetEJerUp;
	std::vector<float> BJetPtJerDown;
	std::vector<float> BJetEtaJerDown;
	std::vector<float> BJetPhiJerDown;
	std::vector<float> BJetEJerDown;
	
	std::vector<float> NonBJetPt;
	std::vector<float> NonBJetEta;
	std::vector<float> NonBJetPhi;
	std::vector<float> NonBJetE;
	std::vector<float> NonBJetCSVv2;
	std::vector<float> NonBJetCharge;
	std::vector<float> NonBJetChargeVec;
	std::vector<float> NonBJetCharmCvsL;
	std::vector<float> NonBJetCharmCvsB;
	std::vector<float> NonBJetPtJesUp;
	std::vector<float> NonBJetEtaJesUp;
	std::vector<float> NonBJetPhiJesUp;
	std::vector<float> NonBJetEJesUp;
	std::vector<float> NonBJetPtJesDown;
	std::vector<float> NonBJetEtaJesDown;
	std::vector<float> NonBJetPhiJesDown;
	std::vector<float> NonBJetEJesDown;
	std::vector<float> NonBJetPtJerUp;
	std::vector<float> NonBJetEtaJerUp;
	std::vector<float> NonBJetPhiJerUp;
	std::vector<float> NonBJetEJerUp;
	std::vector<float> NonBJetPtJerDown;
	std::vector<float> NonBJetEtaJerDown;
	std::vector<float> NonBJetPhiJerDown;
	std::vector<float> NonBJetEJerDown;
	
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
	     float pt = _v_BJetTight->at(i).pt();
	     float eta = _v_BJetTight->at(i).eta();
	     float phi = _v_BJetTight->at(i).phi();
	     float E = _v_BJetTight->at(i).E();
	     float CSVv2 = _v_BJetTight->at(i).CSVv2();
	     float charge = _v_BJetTight->at(i).charge();
	     float chargeVec = _v_BJetTight->at(i).chargeVec();
	     float CharmCvsL = _v_BJetTight->at(i).CharmCvsL();
	     float CharmCvsB = _v_BJetTight->at(i).CharmCvsB();
	     float ptJesUp = _v_BJetTight->at(i).p4_jesTotalUp().Pt();
	     float etaJesUp = _v_BJetTight->at(i).p4_jesTotalUp().PseudoRapidity();
	     float phiJesUp = _v_BJetTight->at(i).p4_jesTotalUp().Phi();
	     float EJesUp = _v_BJetTight->at(i).p4_jesTotalUp().E();
	     float ptJesDown = _v_BJetTight->at(i).p4_jesTotalDown().Pt();
	     float etaJesDown = _v_BJetTight->at(i).p4_jesTotalDown().PseudoRapidity();
	     float phiJesDown = _v_BJetTight->at(i).p4_jesTotalDown().Phi();
	     float EJesDown = _v_BJetTight->at(i).p4_jesTotalDown().E();
	     float ptJerUp = _v_BJetTight->at(i).p4_jerTotalUp().Pt();
	     float etaJerUp = _v_BJetTight->at(i).p4_jerTotalUp().PseudoRapidity();
	     float phiJerUp = _v_BJetTight->at(i).p4_jerTotalUp().Phi();
	     float EJerUp = _v_BJetTight->at(i).p4_jerTotalUp().E();
	     float ptJerDown = _v_BJetTight->at(i).p4_jerTotalDown().Pt();
	     float etaJerDown = _v_BJetTight->at(i).p4_jerTotalDown().PseudoRapidity();
	     float phiJerDown = _v_BJetTight->at(i).p4_jerTotalDown().Phi();
	     float EJerDown = _v_BJetTight->at(i).p4_jerTotalDown().E();
	     
	     if( (nbjets <= 3) ||
		 (nbjets >= 4 && nnonbjets >= 1) || 
		 (nbjets >= 4 && nnonbjets == 0 && i < 3) )
	       {		  		  
		  BJetPt.push_back(pt);
		  BJetEta.push_back(eta);
		  BJetPhi.push_back(phi);
		  BJetE.push_back(E);
		  BJetCSVv2.push_back(CSVv2);
		  BJetCharge.push_back(charge);
		  BJetChargeVec.push_back(chargeVec);
		  BJetCharmCvsL.push_back(CharmCvsL);
		  BJetCharmCvsB.push_back(CharmCvsB);
		  BJetPtJesUp.push_back(ptJesUp);
		  BJetEtaJesUp.push_back(etaJesUp);
		  BJetPhiJesUp.push_back(phiJesUp);
		  BJetEJesUp.push_back(EJesUp);
		  BJetPtJesDown.push_back(ptJesDown);
		  BJetEtaJesDown.push_back(etaJesDown);
		  BJetPhiJesDown.push_back(phiJesDown);
		  BJetEJesDown.push_back(EJesDown);
		  BJetPtJerUp.push_back(ptJerUp);
		  BJetEtaJerUp.push_back(etaJerUp);
		  BJetPhiJerUp.push_back(phiJerUp);
		  BJetEJerUp.push_back(EJerUp);
		  BJetPtJerDown.push_back(ptJerDown);
		  BJetEtaJerDown.push_back(etaJerDown);
		  BJetPhiJerDown.push_back(phiJerDown);
		  BJetEJerDown.push_back(EJerDown);
	       }
	     else
	       {
		  NonBJetPt.push_back(pt);
		  NonBJetEta.push_back(eta);
		  NonBJetPhi.push_back(phi);
		  NonBJetE.push_back(E);
		  NonBJetCSVv2.push_back(CSVv2);
		  NonBJetCharge.push_back(charge);
		  NonBJetChargeVec.push_back(chargeVec);
		  NonBJetCharmCvsL.push_back(CharmCvsL);
		  NonBJetCharmCvsB.push_back(CharmCvsB);
		  NonBJetPtJesUp.push_back(ptJesUp);
		  NonBJetEtaJesUp.push_back(etaJesUp);
		  NonBJetPhiJesUp.push_back(phiJesUp);
		  NonBJetEJesUp.push_back(EJesUp);
		  NonBJetPtJesDown.push_back(ptJesDown);
		  NonBJetEtaJesDown.push_back(etaJesDown);
		  NonBJetPhiJesDown.push_back(phiJesDown);
		  NonBJetEJesDown.push_back(EJesDown);
		  NonBJetPtJerUp.push_back(ptJerUp);
		  NonBJetEtaJerUp.push_back(etaJerUp);
		  NonBJetPhiJerUp.push_back(phiJerUp);
		  NonBJetEJerUp.push_back(EJerUp);
		  NonBJetPtJerDown.push_back(ptJerDown);
		  NonBJetEtaJerDown.push_back(etaJerDown);
		  NonBJetPhiJerDown.push_back(phiJerDown);
		  NonBJetEJerDown.push_back(EJerDown);
	       }	     
	  }   
	     
	for(int i=0;i<_v_NonBJetTight->size();i++)
	  {
	     float pt = _v_NonBJetTight->at(i).pt();
	     float eta = _v_NonBJetTight->at(i).eta();
	     float phi = _v_NonBJetTight->at(i).phi();
	     float E = _v_NonBJetTight->at(i).E();
	     float CSVv2 = _v_NonBJetTight->at(i).CSVv2();
	     float charge = _v_NonBJetTight->at(i).charge();
	     float chargeVec = _v_NonBJetTight->at(i).chargeVec();
	     float CharmCvsL = _v_NonBJetTight->at(i).CharmCvsL();
	     float CharmCvsB = _v_NonBJetTight->at(i).CharmCvsB();
	     float ptJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().Pt();
	     float etaJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().PseudoRapidity();
	     float phiJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().Phi();
	     float EJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().E();
	     float ptJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().Pt();
	     float etaJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().PseudoRapidity();
	     float phiJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().Phi();
	     float EJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().E();
	     float ptJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().Pt();
	     float etaJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().PseudoRapidity();
	     float phiJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().Phi();
	     float EJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().E();
	     float ptJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().Pt();
	     float etaJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().PseudoRapidity();
	     float phiJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().Phi();
	     float EJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().E();
	     
	     if( (nbjets == 0 && i < 3) ||
		 (nbjets == 1 && i < 2) ||
		 (nbjets == 2 && i < 1) )
	       {
		  BJetPt.push_back(pt);
		  BJetEta.push_back(eta);
		  BJetPhi.push_back(phi);
		  BJetE.push_back(E);
		  BJetCSVv2.push_back(CSVv2);
		  BJetCharge.push_back(charge);
		  BJetChargeVec.push_back(chargeVec);
		  BJetCharmCvsL.push_back(CharmCvsL);
		  BJetCharmCvsB.push_back(CharmCvsB);
		  BJetPtJesUp.push_back(ptJesUp);
		  BJetEtaJesUp.push_back(etaJesUp);
		  BJetPhiJesUp.push_back(phiJesUp);
		  BJetEJesUp.push_back(EJesUp);
		  BJetPtJesDown.push_back(ptJesDown);
		  BJetEtaJesDown.push_back(etaJesDown);
		  BJetPhiJesDown.push_back(phiJesDown);
		  BJetEJesDown.push_back(EJesDown);
		  BJetPtJerUp.push_back(ptJerUp);
		  BJetEtaJerUp.push_back(etaJerUp);
		  BJetPhiJerUp.push_back(phiJerUp);
		  BJetEJerUp.push_back(EJerUp);
		  BJetPtJerDown.push_back(ptJerDown);
		  BJetEtaJerDown.push_back(etaJerDown);
		  BJetPhiJerDown.push_back(phiJerDown);
		  BJetEJerDown.push_back(EJerDown);
	       }
	     else
	       {
		  NonBJetPt.push_back(pt);
		  NonBJetEta.push_back(eta);
		  NonBJetPhi.push_back(phi);
		  NonBJetE.push_back(E);
		  NonBJetCSVv2.push_back(CSVv2);
		  NonBJetCharge.push_back(charge);
		  NonBJetChargeVec.push_back(chargeVec);
		  NonBJetCharmCvsL.push_back(CharmCvsL);
		  NonBJetCharmCvsB.push_back(CharmCvsB);
		  NonBJetPtJesUp.push_back(ptJesUp);
		  NonBJetEtaJesUp.push_back(etaJesUp);
		  NonBJetPhiJesUp.push_back(phiJesUp);
		  NonBJetEJesUp.push_back(EJesUp);
		  NonBJetPtJesDown.push_back(ptJesDown);
		  NonBJetEtaJesDown.push_back(etaJesDown);
		  NonBJetPhiJesDown.push_back(phiJesDown);
		  NonBJetEJesDown.push_back(EJesDown);
		  NonBJetPtJerUp.push_back(ptJerUp);
		  NonBJetEtaJerUp.push_back(etaJerUp);
		  NonBJetPhiJerUp.push_back(phiJerUp);
		  NonBJetEJerUp.push_back(EJerUp);
		  NonBJetPtJerDown.push_back(ptJerDown);
		  NonBJetEtaJerDown.push_back(etaJerDown);
		  NonBJetPhiJerDown.push_back(phiJerDown);
		  NonBJetEJerDown.push_back(EJerDown);
	       }	     
	  }   
	
	kfTopTopLepHbb->SetBJet(BJetPt,BJetEta,BJetPhi,BJetE);
	kfTopTopLepHbb->SetNonBJet(NonBJetPt,NonBJetEta,NonBJetPhi,NonBJetE);
	kfTopTopLepHbb->SetElectron(ElectronPt,ElectronEta,ElectronPhi,ElectronE);
	kfTopTopLepHbb->SetMuon(MuonPt,MuonEta,MuonPhi,MuonE);
	kfTopTopLepHbb->SetMet(metpx,metpy);
	
	kfTopTopLepHbb->Run();

	std::vector<std::pair<float,int> > MVADisc;
	std::vector<std::pair<float,int> > MVADiscJesUp;
	std::vector<std::pair<float,int> > MVADiscJesDown;
	std::vector<std::pair<float,int> > MVADiscJerUp;
	std::vector<std::pair<float,int> > MVADiscJerDown;
	
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

	     TLorentzVector *TopLepWNu_p4 = new TLorentzVector();
	     TopLepWNu_p4->SetPxPyPzE(NuPx,NuPy,NuPz,NuE);
	     
	     TLorentzVector *HiggsBJet1_p4 = new TLorentzVector();
	     HiggsBJet1_p4->SetPtEtaPhiE(BJetPt[idx_BJET1_TOPTOPLEPHBB],
					 BJetEta[idx_BJET1_TOPTOPLEPHBB],
					 BJetPhi[idx_BJET1_TOPTOPLEPHBB],
					 BJetE[idx_BJET1_TOPTOPLEPHBB]);
	     TLorentzVector *HiggsBJet1JesUp_p4 = new TLorentzVector();
	     HiggsBJet1JesUp_p4->SetPtEtaPhiE(BJetPtJesUp[idx_BJET1_TOPTOPLEPHBB],
					      BJetEtaJesUp[idx_BJET1_TOPTOPLEPHBB],
					      BJetPhiJesUp[idx_BJET1_TOPTOPLEPHBB],
					      BJetEJesUp[idx_BJET1_TOPTOPLEPHBB]);
	     TLorentzVector *HiggsBJet1JesDown_p4 = new TLorentzVector();
	     HiggsBJet1JesDown_p4->SetPtEtaPhiE(BJetPtJesDown[idx_BJET1_TOPTOPLEPHBB],
						BJetEtaJesDown[idx_BJET1_TOPTOPLEPHBB],
						BJetPhiJesDown[idx_BJET1_TOPTOPLEPHBB],
						BJetEJesDown[idx_BJET1_TOPTOPLEPHBB]);
	     TLorentzVector *HiggsBJet1JerUp_p4 = new TLorentzVector();
	     HiggsBJet1JerUp_p4->SetPtEtaPhiE(BJetPtJerUp[idx_BJET1_TOPTOPLEPHBB],
					      BJetEtaJerUp[idx_BJET1_TOPTOPLEPHBB],
					      BJetPhiJerUp[idx_BJET1_TOPTOPLEPHBB],
					      BJetEJerUp[idx_BJET1_TOPTOPLEPHBB]);
	     TLorentzVector *HiggsBJet1JerDown_p4 = new TLorentzVector();
	     HiggsBJet1JerDown_p4->SetPtEtaPhiE(BJetPtJerDown[idx_BJET1_TOPTOPLEPHBB],
						BJetEtaJerDown[idx_BJET1_TOPTOPLEPHBB],
						BJetPhiJerDown[idx_BJET1_TOPTOPLEPHBB],
						BJetEJerDown[idx_BJET1_TOPTOPLEPHBB]);
	     
	     TLorentzVector *HiggsBJet2_p4 = new TLorentzVector();
	     HiggsBJet2_p4->SetPtEtaPhiE(BJetPt[idx_BJET2_TOPTOPLEPHBB],
					BJetEta[idx_BJET2_TOPTOPLEPHBB],
					BJetPhi[idx_BJET2_TOPTOPLEPHBB],
					BJetE[idx_BJET2_TOPTOPLEPHBB]);
	     TLorentzVector *HiggsBJet2JesUp_p4 = new TLorentzVector();
	     HiggsBJet2JesUp_p4->SetPtEtaPhiE(BJetPtJesUp[idx_BJET2_TOPTOPLEPHBB],
					      BJetEtaJesUp[idx_BJET2_TOPTOPLEPHBB],
					      BJetPhiJesUp[idx_BJET2_TOPTOPLEPHBB],
					      BJetEJesUp[idx_BJET2_TOPTOPLEPHBB]);
	     TLorentzVector *HiggsBJet2JesDown_p4 = new TLorentzVector();
	     HiggsBJet2JesDown_p4->SetPtEtaPhiE(BJetPtJesDown[idx_BJET2_TOPTOPLEPHBB],
						BJetEtaJesDown[idx_BJET2_TOPTOPLEPHBB],
						BJetPhiJesDown[idx_BJET2_TOPTOPLEPHBB],
						BJetEJesDown[idx_BJET2_TOPTOPLEPHBB]);
	     TLorentzVector *HiggsBJet2JerUp_p4 = new TLorentzVector();
	     HiggsBJet2JerUp_p4->SetPtEtaPhiE(BJetPtJerUp[idx_BJET2_TOPTOPLEPHBB],
					      BJetEtaJerUp[idx_BJET2_TOPTOPLEPHBB],
					      BJetPhiJerUp[idx_BJET2_TOPTOPLEPHBB],
					      BJetEJerUp[idx_BJET2_TOPTOPLEPHBB]);
	     TLorentzVector *HiggsBJet2JerDown_p4 = new TLorentzVector();
	     HiggsBJet2JerDown_p4->SetPtEtaPhiE(BJetPtJerDown[idx_BJET2_TOPTOPLEPHBB],
						BJetEtaJerDown[idx_BJET2_TOPTOPLEPHBB],
						BJetPhiJerDown[idx_BJET2_TOPTOPLEPHBB],
						BJetEJerDown[idx_BJET2_TOPTOPLEPHBB]);
	     
	     TLorentzVector *TopLepBJet_p4 = new TLorentzVector();
	     TopLepBJet_p4->SetPtEtaPhiE(BJetPt[idx_BJETLEP_TOPTOPLEPHBB],
					 BJetEta[idx_BJETLEP_TOPTOPLEPHBB],
					 BJetPhi[idx_BJETLEP_TOPTOPLEPHBB],
					 BJetE[idx_BJETLEP_TOPTOPLEPHBB]);
	     TLorentzVector *TopLepBJetJesUp_p4 = new TLorentzVector();
	     TopLepBJetJesUp_p4->SetPtEtaPhiE(BJetPtJesUp[idx_BJETLEP_TOPTOPLEPHBB],
					      BJetEtaJesUp[idx_BJETLEP_TOPTOPLEPHBB],
					      BJetPhiJesUp[idx_BJETLEP_TOPTOPLEPHBB],
					      BJetEJesUp[idx_BJETLEP_TOPTOPLEPHBB]);
	     TLorentzVector *TopLepBJetJesDown_p4 = new TLorentzVector();
	     TopLepBJetJesDown_p4->SetPtEtaPhiE(BJetPtJesDown[idx_BJETLEP_TOPTOPLEPHBB],
						BJetEtaJesDown[idx_BJETLEP_TOPTOPLEPHBB],
						BJetPhiJesDown[idx_BJETLEP_TOPTOPLEPHBB],
						BJetEJesDown[idx_BJETLEP_TOPTOPLEPHBB]);
	     TLorentzVector *TopLepBJetJerUp_p4 = new TLorentzVector();
	     TopLepBJetJerUp_p4->SetPtEtaPhiE(BJetPtJerUp[idx_BJETLEP_TOPTOPLEPHBB],
					      BJetEtaJerUp[idx_BJETLEP_TOPTOPLEPHBB],
					      BJetPhiJerUp[idx_BJETLEP_TOPTOPLEPHBB],
					      BJetEJerUp[idx_BJETLEP_TOPTOPLEPHBB]);
	     TLorentzVector *TopLepBJetJerDown_p4 = new TLorentzVector();
	     TopLepBJetJerDown_p4->SetPtEtaPhiE(BJetPtJerDown[idx_BJETLEP_TOPTOPLEPHBB],
						BJetEtaJerDown[idx_BJETLEP_TOPTOPLEPHBB],
						BJetPhiJerDown[idx_BJETLEP_TOPTOPLEPHBB],
						BJetEJerDown[idx_BJETLEP_TOPTOPLEPHBB]);
	     
	     TLorentzVector *TopHadNonBJet_p4 = new TLorentzVector();
	     TopHadNonBJet_p4->SetPtEtaPhiE(NonBJetPt[idx_NONBJETHAD_TOPTOPLEPHBB],
					    NonBJetEta[idx_NONBJETHAD_TOPTOPLEPHBB],
					    NonBJetPhi[idx_NONBJETHAD_TOPTOPLEPHBB],
					    NonBJetE[idx_NONBJETHAD_TOPTOPLEPHBB]);
	     TLorentzVector *TopHadNonBJetJesUp_p4 = new TLorentzVector();
	     TopHadNonBJetJesUp_p4->SetPtEtaPhiE(NonBJetPtJesUp[idx_NONBJETHAD_TOPTOPLEPHBB],
						 NonBJetEtaJesUp[idx_NONBJETHAD_TOPTOPLEPHBB],
						 NonBJetPhiJesUp[idx_NONBJETHAD_TOPTOPLEPHBB],
						 NonBJetEJesUp[idx_NONBJETHAD_TOPTOPLEPHBB]);
	     TLorentzVector *TopHadNonBJetJesDown_p4 = new TLorentzVector();
	     TopHadNonBJetJesDown_p4->SetPtEtaPhiE(NonBJetPtJesDown[idx_NONBJETHAD_TOPTOPLEPHBB],
						   NonBJetEtaJesDown[idx_NONBJETHAD_TOPTOPLEPHBB],
						   NonBJetPhiJesDown[idx_NONBJETHAD_TOPTOPLEPHBB],
						   NonBJetEJesDown[idx_NONBJETHAD_TOPTOPLEPHBB]);
	     TLorentzVector *TopHadNonBJetJerUp_p4 = new TLorentzVector();
	     TopHadNonBJetJerUp_p4->SetPtEtaPhiE(NonBJetPtJerUp[idx_NONBJETHAD_TOPTOPLEPHBB],
						 NonBJetEtaJerUp[idx_NONBJETHAD_TOPTOPLEPHBB],
						 NonBJetPhiJerUp[idx_NONBJETHAD_TOPTOPLEPHBB],
						 NonBJetEJerUp[idx_NONBJETHAD_TOPTOPLEPHBB]);
	     TLorentzVector *TopHadNonBJetJerDown_p4 = new TLorentzVector();
	     TopHadNonBJetJerDown_p4->SetPtEtaPhiE(NonBJetPtJerDown[idx_NONBJETHAD_TOPTOPLEPHBB],
						   NonBJetEtaJerDown[idx_NONBJETHAD_TOPTOPLEPHBB],
						   NonBJetPhiJerDown[idx_NONBJETHAD_TOPTOPLEPHBB],
						   NonBJetEJerDown[idx_NONBJETHAD_TOPTOPLEPHBB]);
	     
	     TLorentzVector *TopLepWLep_p4 = new TLorentzVector();
	     if( idx_ELECTRON_TOPTOPLEPHBB >= 0 )
	       TopLepWLep_p4->SetPtEtaPhiE(ElectronPt[idx_ELECTRON_TOPTOPLEPHBB],
					   ElectronEta[idx_ELECTRON_TOPTOPLEPHBB],
					   ElectronPhi[idx_ELECTRON_TOPTOPLEPHBB],
					   ElectronE[idx_ELECTRON_TOPTOPLEPHBB]);
	     else
	       TopLepWLep_p4->SetPtEtaPhiE(MuonPt[idx_MUON_TOPTOPLEPHBB],
					   MuonEta[idx_MUON_TOPTOPLEPHBB],
					   MuonPhi[idx_MUON_TOPTOPLEPHBB],
					   MuonE[idx_MUON_TOPTOPLEPHBB]);
	     
	     TLorentzVector Higgs_p4 = *HiggsBJet1_p4+*HiggsBJet2_p4;
	     TLorentzVector HiggsJesUp_p4 = *HiggsBJet1JesUp_p4+*HiggsBJet2JesUp_p4;
	     TLorentzVector HiggsJesDown_p4 = *HiggsBJet1JesDown_p4+*HiggsBJet2JesDown_p4;
	     TLorentzVector HiggsJerUp_p4 = *HiggsBJet1JerUp_p4+*HiggsBJet2JerUp_p4;
	     TLorentzVector HiggsJerDown_p4 = *HiggsBJet1JerDown_p4+*HiggsBJet2JerDown_p4;
	     
	     TLorentzVector TopLepW_p4 = *TopLepWLep_p4+*TopLepWNu_p4;
	     
	     TLorentzVector TopLep_p4 = TopLepW_p4+*TopLepBJet_p4;
	     TLorentzVector TopLepJesUp_p4 = TopLepW_p4+*TopLepBJetJesUp_p4;
	     TLorentzVector TopLepJesDown_p4 = TopLepW_p4+*TopLepBJetJesDown_p4;
	     TLorentzVector TopLepJerUp_p4 = TopLepW_p4+*TopLepBJetJerUp_p4;
	     TLorentzVector TopLepJerDown_p4 = TopLepW_p4+*TopLepBJetJerDown_p4;

	     float VarHiggsRecM = Higgs_p4.M();
	     float VarHiggsRecMJesUp = HiggsJesUp_p4.M();
	     float VarHiggsRecMJesDown = HiggsJesDown_p4.M();
	     float VarHiggsRecMJerUp = HiggsJerUp_p4.M();
	     float VarHiggsRecMJerDown = HiggsJerDown_p4.M();
	     
	     float VarTopLepRecM = TopLep_p4.M();
	     float VarTopLepRecMJesUp = TopLepJesUp_p4.M();
	     float VarTopLepRecMJesDown = TopLepJesDown_p4.M();
	     float VarTopLepRecMJerUp = TopLepJerUp_p4.M();
	     float VarTopLepRecMJerDown = TopLepJerDown_p4.M();

	     float VarHiggsTopLepRecDr = Higgs_p4.DeltaR(TopLep_p4);
	     float VarHiggsTopLepRecDrJesUp = HiggsJesUp_p4.DeltaR(TopLepJesUp_p4);
	     float VarHiggsTopLepRecDrJesDown = HiggsJesDown_p4.DeltaR(TopLepJesDown_p4);
	     float VarHiggsTopLepRecDrJerUp = HiggsJerUp_p4.DeltaR(TopLepJerUp_p4);
	     float VarHiggsTopLepRecDrJerDown = HiggsJerDown_p4.DeltaR(TopLepJerDown_p4);
	     
	     float VarTopLepRecPt = TopLep_p4.Pt();
	     float VarTopLepRecPtJesUp = TopLepJesUp_p4.Pt();
	     float VarTopLepRecPtJesDown = TopLepJesDown_p4.Pt();
	     float VarTopLepRecPtJerUp = TopLepJerUp_p4.Pt();
	     float VarTopLepRecPtJerDown = TopLepJerDown_p4.Pt();
	     
	     TLorentzVector *HiggsT_p4 = new TLorentzVector();
	     HiggsT_p4->SetPxPyPzE(Higgs_p4.Px(),Higgs_p4.Py(),0.,Higgs_p4.Et());
	     TLorentzVector *HiggsTJesUp_p4 = new TLorentzVector();
	     HiggsTJesUp_p4->SetPxPyPzE(HiggsJesUp_p4.Px(),HiggsJesUp_p4.Py(),0.,HiggsJesUp_p4.Et());
	     TLorentzVector *HiggsTJesDown_p4 = new TLorentzVector();
	     HiggsTJesDown_p4->SetPxPyPzE(HiggsJesDown_p4.Px(),HiggsJesDown_p4.Py(),0.,HiggsJesDown_p4.Et());
	     TLorentzVector *HiggsTJerUp_p4 = new TLorentzVector();
	     HiggsTJerUp_p4->SetPxPyPzE(HiggsJerUp_p4.Px(),HiggsJerUp_p4.Py(),0.,HiggsJerUp_p4.Et());
	     TLorentzVector *HiggsTJerDown_p4 = new TLorentzVector();
	     HiggsTJerDown_p4->SetPxPyPzE(HiggsJerDown_p4.Px(),HiggsJerDown_p4.Py(),0.,HiggsJerDown_p4.Et());
	     
	     TLorentzVector *TopLepWLepT_p4 = new TLorentzVector();
	     TopLepWLepT_p4->SetPxPyPzE(TopLepWLep_p4->Px(),TopLepWLep_p4->Py(),0.,TopLepWLep_p4->Et());
	     
	     TLorentzVector *TopLepWNuT_p4 = new TLorentzVector();
	     TopLepWNuT_p4->SetPxPyPzE(TopLepWNu_p4->Px(),TopLepWNu_p4->Py(),0.,TopLepWNu_p4->Et());
	     
	     TLorentzVector *TopLepBJetT_p4 = new TLorentzVector();
	     TopLepBJetT_p4->SetPxPyPzE(TopLepBJet_p4->Px(),TopLepBJet_p4->Py(),0.,TopLepBJet_p4->Et());
	     TLorentzVector *TopLepBJetTJesUp_p4 = new TLorentzVector();
	     TopLepBJetTJesUp_p4->SetPxPyPzE(TopLepBJetJesUp_p4->Px(),TopLepBJetJesUp_p4->Py(),0.,TopLepBJetJesUp_p4->Et());
	     TLorentzVector *TopLepBJetTJesDown_p4 = new TLorentzVector();
	     TopLepBJetTJesDown_p4->SetPxPyPzE(TopLepBJetJesDown_p4->Px(),TopLepBJetJesDown_p4->Py(),0.,TopLepBJetJesDown_p4->Et());
	     TLorentzVector *TopLepBJetTJerUp_p4 = new TLorentzVector();
	     TopLepBJetTJerUp_p4->SetPxPyPzE(TopLepBJetJerUp_p4->Px(),TopLepBJetJerUp_p4->Py(),0.,TopLepBJetJerUp_p4->Et());
	     TLorentzVector *TopLepBJetTJerDown_p4 = new TLorentzVector();
	     TopLepBJetTJerDown_p4->SetPxPyPzE(TopLepBJetJerDown_p4->Px(),TopLepBJetJerDown_p4->Py(),0.,TopLepBJetJerDown_p4->Et());
	     
	     TLorentzVector TopLepT_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetT_p4;
	     TLorentzVector TopLepTJesUp_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJesUp_p4;
	     TLorentzVector TopLepTJesDown_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJesDown_p4;
	     TLorentzVector TopLepTJerUp_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJerUp_p4;
	     TLorentzVector TopLepTJerDown_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJerDown_p4;
	     
	     float VarTopLepRecMT = TopLepT_p4.M();
	     float VarTopLepRecMTJesUp = TopLepTJesUp_p4.M();
	     float VarTopLepRecMTJesDown = TopLepTJesDown_p4.M();
	     float VarTopLepRecMTJerUp = TopLepTJerUp_p4.M();
	     float VarTopLepRecMTJerDown = TopLepTJerDown_p4.M();
	     
	     float VarHiggsTopLepRecDphiT = HiggsT_p4->DeltaPhi(TopLepT_p4);
	     float VarHiggsTopLepRecDphiTJesUp = HiggsTJesUp_p4->DeltaPhi(TopLepTJesUp_p4);
	     float VarHiggsTopLepRecDphiTJesDown = HiggsTJesDown_p4->DeltaPhi(TopLepTJesDown_p4);
	     float VarHiggsTopLepRecDphiTJerUp = HiggsTJerUp_p4->DeltaPhi(TopLepTJerUp_p4);
	     float VarHiggsTopLepRecDphiTJerDown = HiggsTJerDown_p4->DeltaPhi(TopLepTJerDown_p4);
	     
	     float VarTopLepRecPtT = TopLepT_p4.Pt();
	     float VarTopLepRecPtTJesUp = TopLepTJesUp_p4.Pt();
	     float VarTopLepRecPtTJesDown = TopLepTJesDown_p4.Pt();
	     float VarTopLepRecPtTJerUp = TopLepTJerUp_p4.Pt();
	     float VarTopLepRecPtTJerDown = TopLepTJerDown_p4.Pt();
	     
	     if( disc < 10E+8 )
	       {
		  MVAFullReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecMJesUp;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHBB = VarTopLepRecMJesUp;
		  MVAFullReco_HiggsTopLepRecDr_TOPTOPLEPHBB = VarHiggsTopLepRecDrJesUp;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHBB = VarTopLepRecPtJesUp;
		  
		  MVADiscJesUp.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));

		  MVAFullReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecMJesDown;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHBB = VarTopLepRecMJesDown;
		  MVAFullReco_HiggsTopLepRecDr_TOPTOPLEPHBB = VarHiggsTopLepRecDrJesDown;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHBB = VarTopLepRecPtJesDown;
		  
		  MVADiscJesDown.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));

		  MVAFullReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecMJerUp;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHBB = VarTopLepRecMJerUp;
		  MVAFullReco_HiggsTopLepRecDr_TOPTOPLEPHBB = VarHiggsTopLepRecDrJerUp;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHBB = VarTopLepRecPtJerUp;
		  
		  MVADiscJerUp.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));

		  MVAFullReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecMJerDown;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHBB = VarTopLepRecMJerDown;
		  MVAFullReco_HiggsTopLepRecDr_TOPTOPLEPHBB = VarHiggsTopLepRecDrJerDown;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHBB = VarTopLepRecPtJerDown;
		  
		  MVADiscJerDown.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));
		  
		  MVAFullReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecM;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHBB = VarTopLepRecM;
		  MVAFullReco_HiggsTopLepRecDr_TOPTOPLEPHBB = VarHiggsTopLepRecDr;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHBB = VarTopLepRecPt;
		  
		  MVADisc.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));
	       }	
	     else
	       {
		  MVAPartReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecMJesUp;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHBB = VarTopLepRecMTJesUp;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPTOPLEPHBB = VarHiggsTopLepRecDphiTJesUp;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHBB = VarTopLepRecPtTJesUp;
		  
		  MVADiscJesUp.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));

		  MVAPartReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecMJesDown;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHBB = VarTopLepRecMTJesDown;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPTOPLEPHBB = VarHiggsTopLepRecDphiTJesDown;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHBB = VarTopLepRecPtTJesDown;
		  
		  MVADiscJesDown.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));

		  MVAPartReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecMJerUp;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHBB = VarTopLepRecMTJerUp;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPTOPLEPHBB = VarHiggsTopLepRecDphiTJerUp;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHBB = VarTopLepRecPtTJerUp;
		  
		  MVADiscJerUp.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));

		  MVAPartReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecMJerDown;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHBB = VarTopLepRecMTJerDown;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPTOPLEPHBB = VarHiggsTopLepRecDphiTJerDown;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHBB = VarTopLepRecPtTJerDown;
		  
		  MVADiscJerDown.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));
		  
		  MVAPartReco_HiggsRecM_TOPTOPLEPHBB = VarHiggsRecM;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHBB = VarTopLepRecMT;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPTOPLEPHBB = VarHiggsTopLepRecDphiT;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHBB = VarTopLepRecPtT;
		  
		  MVADisc.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHBB->EvaluateMVA("BDTG method"),ip));
	       }	     

	     delete TopLepWNu_p4;
	     delete HiggsBJet1_p4;
	     delete HiggsBJet1JesUp_p4;
	     delete HiggsBJet1JesDown_p4;
	     delete HiggsBJet1JerUp_p4;
	     delete HiggsBJet1JerDown_p4;
	     delete HiggsBJet2_p4;
	     delete HiggsBJet2JesUp_p4;
	     delete HiggsBJet2JesDown_p4;
	     delete HiggsBJet2JerUp_p4;
	     delete HiggsBJet2JerDown_p4;
	     delete TopLepBJet_p4;
	     delete TopLepBJetJesUp_p4;
	     delete TopLepBJetJesDown_p4;
	     delete TopLepBJetJerUp_p4;
	     delete TopLepBJetJerDown_p4;
	     delete TopHadNonBJet_p4;
	     delete TopHadNonBJetJesUp_p4;
	     delete TopHadNonBJetJesDown_p4;
	     delete TopHadNonBJetJerUp_p4;
	     delete TopHadNonBJetJerDown_p4;
	     delete TopLepWLep_p4;
	     delete HiggsT_p4;
	     delete HiggsTJesUp_p4;
	     delete HiggsTJesDown_p4;
	     delete HiggsTJerUp_p4;
	     delete HiggsTJerDown_p4;
	     delete TopLepWLepT_p4;
	     delete TopLepWNuT_p4;
	     delete TopLepBJetT_p4;
	     delete TopLepBJetTJesUp_p4;
	     delete TopLepBJetTJesDown_p4;
	     delete TopLepBJetTJerUp_p4;
	     delete TopLepBJetTJerDown_p4;
	  }
	
	std::sort(MVADisc.begin(),MVADisc.end(),sortFunc());
	int IdxPerm = MVADisc.at(0).second;
	
	_chi2_TOPTOPLEPHBB = kfTopTopLepHbb->GetDisc(IdxPerm);
	_MVA_TOPTOPLEPHBB = MVADisc.at(0).first;
	_MVAJesUp_TOPTOPLEPHBB = MVADiscJesUp.at(IdxPerm).first;
	_MVAJesDown_TOPTOPLEPHBB = MVADiscJesDown.at(IdxPerm).first;
	_MVAJerUp_TOPTOPLEPHBB = MVADiscJerUp.at(IdxPerm).first;
	_MVAJerDown_TOPTOPLEPHBB = MVADiscJerDown.at(IdxPerm).first;

	int idx_ELECTRON_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(ELECTRON_TOPTOPLEPHBB,IdxPerm);
	int idx_MUON_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(MUON_TOPTOPLEPHBB,IdxPerm);
	int idx_BJETLEP_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(BJETLEP_TOPTOPLEPHBB,IdxPerm);
	int idx_NONBJETHAD_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(NONBJETHAD_TOPTOPLEPHBB,IdxPerm);
	int idx_BJET1_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(BJET1_TOPTOPLEPHBB,IdxPerm);
	int idx_BJET2_TOPTOPLEPHBB = kfTopTopLepHbb->GetIndex(BJET2_TOPTOPLEPHBB,IdxPerm);

	float NuPx = kfTopTopLepHbb->GetNuPx(IdxPerm,0);
	float NuPy = kfTopTopLepHbb->GetNuPy(IdxPerm,0);
	float NuPz = kfTopTopLepHbb->GetNuPz(IdxPerm,0);
	float NuE = sqrt(NuPx*NuPx+NuPy*NuPy+NuPz*NuPz);

	_TopLepWNu_TOPTOPLEPHBB_p4.SetPxPyPzE(NuPx,NuPy,NuPz,NuE);
	
	_HiggsBJet1_TOPTOPLEPHBB_p4.SetPtEtaPhiE(BJetPt[idx_BJET1_TOPTOPLEPHBB],
						 BJetEta[idx_BJET1_TOPTOPLEPHBB],
						 BJetPhi[idx_BJET1_TOPTOPLEPHBB],
						 BJetE[idx_BJET1_TOPTOPLEPHBB]);
	_HiggsBJet1_TOPTOPLEPHBB_JesUp_p4.SetPtEtaPhiE(BJetPtJesUp[idx_BJET1_TOPTOPLEPHBB],
						       BJetEtaJesUp[idx_BJET1_TOPTOPLEPHBB],
						       BJetPhiJesUp[idx_BJET1_TOPTOPLEPHBB],
						       BJetEJesUp[idx_BJET1_TOPTOPLEPHBB]);
	_HiggsBJet1_TOPTOPLEPHBB_JesDown_p4.SetPtEtaPhiE(BJetPtJesDown[idx_BJET1_TOPTOPLEPHBB],
							 BJetEtaJesDown[idx_BJET1_TOPTOPLEPHBB],
							 BJetPhiJesDown[idx_BJET1_TOPTOPLEPHBB],
							 BJetEJesDown[idx_BJET1_TOPTOPLEPHBB]);
	_HiggsBJet1_TOPTOPLEPHBB_JerUp_p4.SetPtEtaPhiE(BJetPtJerUp[idx_BJET1_TOPTOPLEPHBB],
						       BJetEtaJerUp[idx_BJET1_TOPTOPLEPHBB],
						       BJetPhiJerUp[idx_BJET1_TOPTOPLEPHBB],
						       BJetEJerUp[idx_BJET1_TOPTOPLEPHBB]);
	_HiggsBJet1_TOPTOPLEPHBB_JerDown_p4.SetPtEtaPhiE(BJetPtJerDown[idx_BJET1_TOPTOPLEPHBB],
							 BJetEtaJerDown[idx_BJET1_TOPTOPLEPHBB],
							 BJetPhiJerDown[idx_BJET1_TOPTOPLEPHBB],
							 BJetEJerDown[idx_BJET1_TOPTOPLEPHBB]);
	
	_HiggsBJet2_TOPTOPLEPHBB_p4.SetPtEtaPhiE(BJetPt[idx_BJET2_TOPTOPLEPHBB],
						 BJetEta[idx_BJET2_TOPTOPLEPHBB],
						 BJetPhi[idx_BJET2_TOPTOPLEPHBB],
						 BJetE[idx_BJET2_TOPTOPLEPHBB]);
	_HiggsBJet2_TOPTOPLEPHBB_JesUp_p4.SetPtEtaPhiE(BJetPtJesUp[idx_BJET2_TOPTOPLEPHBB],
						       BJetEtaJesUp[idx_BJET2_TOPTOPLEPHBB],
						       BJetPhiJesUp[idx_BJET2_TOPTOPLEPHBB],
						       BJetEJesUp[idx_BJET2_TOPTOPLEPHBB]);
	_HiggsBJet2_TOPTOPLEPHBB_JesDown_p4.SetPtEtaPhiE(BJetPtJesDown[idx_BJET2_TOPTOPLEPHBB],
							 BJetEtaJesDown[idx_BJET2_TOPTOPLEPHBB],
							 BJetPhiJesDown[idx_BJET2_TOPTOPLEPHBB],
							 BJetEJesDown[idx_BJET2_TOPTOPLEPHBB]);
	_HiggsBJet2_TOPTOPLEPHBB_JerUp_p4.SetPtEtaPhiE(BJetPtJerUp[idx_BJET2_TOPTOPLEPHBB],
						       BJetEtaJerUp[idx_BJET2_TOPTOPLEPHBB],
						       BJetPhiJerUp[idx_BJET2_TOPTOPLEPHBB],
						       BJetEJerUp[idx_BJET2_TOPTOPLEPHBB]);
	_HiggsBJet2_TOPTOPLEPHBB_JerDown_p4.SetPtEtaPhiE(BJetPtJerDown[idx_BJET2_TOPTOPLEPHBB],
							 BJetEtaJerDown[idx_BJET2_TOPTOPLEPHBB],
							 BJetPhiJerDown[idx_BJET2_TOPTOPLEPHBB],
							 BJetEJerDown[idx_BJET2_TOPTOPLEPHBB]);
	
	_TopLepBJet_TOPTOPLEPHBB_p4.SetPtEtaPhiE(BJetPt[idx_BJETLEP_TOPTOPLEPHBB],
						 BJetEta[idx_BJETLEP_TOPTOPLEPHBB],
						 BJetPhi[idx_BJETLEP_TOPTOPLEPHBB],
						 BJetE[idx_BJETLEP_TOPTOPLEPHBB]);
	_TopLepBJet_TOPTOPLEPHBB_JesUp_p4.SetPtEtaPhiE(BJetPtJesUp[idx_BJETLEP_TOPTOPLEPHBB],
						       BJetEtaJesUp[idx_BJETLEP_TOPTOPLEPHBB],
						       BJetPhiJesUp[idx_BJETLEP_TOPTOPLEPHBB],
						       BJetEJesUp[idx_BJETLEP_TOPTOPLEPHBB]);
	_TopLepBJet_TOPTOPLEPHBB_JesDown_p4.SetPtEtaPhiE(BJetPtJesDown[idx_BJETLEP_TOPTOPLEPHBB],
							 BJetEtaJesDown[idx_BJETLEP_TOPTOPLEPHBB],
							 BJetPhiJesDown[idx_BJETLEP_TOPTOPLEPHBB],
							 BJetEJesDown[idx_BJETLEP_TOPTOPLEPHBB]);
	_TopLepBJet_TOPTOPLEPHBB_JerUp_p4.SetPtEtaPhiE(BJetPtJerUp[idx_BJETLEP_TOPTOPLEPHBB],
						       BJetEtaJerUp[idx_BJETLEP_TOPTOPLEPHBB],
						       BJetPhiJerUp[idx_BJETLEP_TOPTOPLEPHBB],
						       BJetEJerUp[idx_BJETLEP_TOPTOPLEPHBB]);
	_TopLepBJet_TOPTOPLEPHBB_JerDown_p4.SetPtEtaPhiE(BJetPtJerDown[idx_BJETLEP_TOPTOPLEPHBB],
							 BJetEtaJerDown[idx_BJETLEP_TOPTOPLEPHBB],
							 BJetPhiJerDown[idx_BJETLEP_TOPTOPLEPHBB],
							 BJetEJerDown[idx_BJETLEP_TOPTOPLEPHBB]);
	
	_TopHadNonBJet_TOPTOPLEPHBB_p4.SetPtEtaPhiE(NonBJetPt[idx_NONBJETHAD_TOPTOPLEPHBB],
						    NonBJetEta[idx_NONBJETHAD_TOPTOPLEPHBB],
						    NonBJetPhi[idx_NONBJETHAD_TOPTOPLEPHBB],
						    NonBJetE[idx_NONBJETHAD_TOPTOPLEPHBB]);
	_TopHadNonBJet_TOPTOPLEPHBB_JesUp_p4.SetPtEtaPhiE(NonBJetPtJesUp[idx_NONBJETHAD_TOPTOPLEPHBB],
							  NonBJetEtaJesUp[idx_NONBJETHAD_TOPTOPLEPHBB],
							  NonBJetPhiJesUp[idx_NONBJETHAD_TOPTOPLEPHBB],
							  NonBJetEJesUp[idx_NONBJETHAD_TOPTOPLEPHBB]);
	_TopHadNonBJet_TOPTOPLEPHBB_JesDown_p4.SetPtEtaPhiE(NonBJetPtJesDown[idx_NONBJETHAD_TOPTOPLEPHBB],
							    NonBJetEtaJesDown[idx_NONBJETHAD_TOPTOPLEPHBB],
							    NonBJetPhiJesDown[idx_NONBJETHAD_TOPTOPLEPHBB],
							    NonBJetEJesDown[idx_NONBJETHAD_TOPTOPLEPHBB]);
	_TopHadNonBJet_TOPTOPLEPHBB_JerUp_p4.SetPtEtaPhiE(NonBJetPtJerUp[idx_NONBJETHAD_TOPTOPLEPHBB],
							  NonBJetEtaJerUp[idx_NONBJETHAD_TOPTOPLEPHBB],
							  NonBJetPhiJerUp[idx_NONBJETHAD_TOPTOPLEPHBB],
							  NonBJetEJerUp[idx_NONBJETHAD_TOPTOPLEPHBB]);
	_TopHadNonBJet_TOPTOPLEPHBB_JerDown_p4.SetPtEtaPhiE(NonBJetPtJerDown[idx_NONBJETHAD_TOPTOPLEPHBB],
							    NonBJetEtaJerDown[idx_NONBJETHAD_TOPTOPLEPHBB],
							    NonBJetPhiJerDown[idx_NONBJETHAD_TOPTOPLEPHBB],
							    NonBJetEJerDown[idx_NONBJETHAD_TOPTOPLEPHBB]);
	
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
	_Higgs_TOPTOPLEPHBB_JesUp_p4 = _HiggsBJet1_TOPTOPLEPHBB_JesUp_p4+_HiggsBJet2_TOPTOPLEPHBB_JesUp_p4;
	_Higgs_TOPTOPLEPHBB_JesDown_p4 = _HiggsBJet1_TOPTOPLEPHBB_JesDown_p4+_HiggsBJet2_TOPTOPLEPHBB_JesDown_p4;
	_Higgs_TOPTOPLEPHBB_JerUp_p4 = _HiggsBJet1_TOPTOPLEPHBB_JerUp_p4+_HiggsBJet2_TOPTOPLEPHBB_JerUp_p4;
	_Higgs_TOPTOPLEPHBB_JerDown_p4 = _HiggsBJet1_TOPTOPLEPHBB_JerDown_p4+_HiggsBJet2_TOPTOPLEPHBB_JerDown_p4;
	
	_TopLepW_TOPTOPLEPHBB_p4 = _TopLepWLep_TOPTOPLEPHBB_p4+_TopLepWNu_TOPTOPLEPHBB_p4;
	
	_TopLep_TOPTOPLEPHBB_p4 = _TopLepW_TOPTOPLEPHBB_p4+_TopLepBJet_TOPTOPLEPHBB_p4;
	_TopLep_TOPTOPLEPHBB_JesUp_p4 = _TopLepW_TOPTOPLEPHBB_p4+_TopLepBJet_TOPTOPLEPHBB_JesUp_p4;
	_TopLep_TOPTOPLEPHBB_JesDown_p4 = _TopLepW_TOPTOPLEPHBB_p4+_TopLepBJet_TOPTOPLEPHBB_JerDown_p4;
	_TopLep_TOPTOPLEPHBB_JerUp_p4 = _TopLepW_TOPTOPLEPHBB_p4+_TopLepBJet_TOPTOPLEPHBB_JerUp_p4;
	_TopLep_TOPTOPLEPHBB_JerDown_p4 = _TopLepW_TOPTOPLEPHBB_p4+_TopLepBJet_TOPTOPLEPHBB_JerDown_p4;

	_HiggsBJet1_TOPTOPLEPHBB_CSVv2 = BJetCSVv2[idx_BJET1_TOPTOPLEPHBB];	
	_HiggsBJet2_TOPTOPLEPHBB_CSVv2 = BJetCSVv2[idx_BJET2_TOPTOPLEPHBB];
	_TopLepBJet_TOPTOPLEPHBB_CSVv2 = BJetCSVv2[idx_BJETLEP_TOPTOPLEPHBB];
	_TopHadNonBJet_TOPTOPLEPHBB_CSVv2 = NonBJetCSVv2[idx_NONBJETHAD_TOPTOPLEPHBB];

	_HiggsBJet1_TOPTOPLEPHBB_charge = BJetCharge[idx_BJET1_TOPTOPLEPHBB];
	_HiggsBJet2_TOPTOPLEPHBB_charge = BJetCharge[idx_BJET2_TOPTOPLEPHBB];
	_TopLepBJet_TOPTOPLEPHBB_charge = BJetCharge[idx_BJETLEP_TOPTOPLEPHBB];
	_TopHadNonBJet_TOPTOPLEPHBB_charge = NonBJetCharge[idx_NONBJETHAD_TOPTOPLEPHBB];

	_HiggsBJet1_TOPTOPLEPHBB_chargeVec = BJetChargeVec[idx_BJET1_TOPTOPLEPHBB];
	_HiggsBJet2_TOPTOPLEPHBB_chargeVec = BJetChargeVec[idx_BJET2_TOPTOPLEPHBB];
	_TopLepBJet_TOPTOPLEPHBB_chargeVec = BJetChargeVec[idx_BJETLEP_TOPTOPLEPHBB];
	_TopHadNonBJet_TOPTOPLEPHBB_chargeVec = NonBJetChargeVec[idx_NONBJETHAD_TOPTOPLEPHBB];

	_HiggsBJet1_TOPTOPLEPHBB_CharmCvsL = BJetCharmCvsL[idx_BJET1_TOPTOPLEPHBB];
	_HiggsBJet2_TOPTOPLEPHBB_CharmCvsL = BJetCharmCvsL[idx_BJET2_TOPTOPLEPHBB];
	_TopLepBJet_TOPTOPLEPHBB_CharmCvsL = BJetCharmCvsL[idx_BJETLEP_TOPTOPLEPHBB];
	_TopHadNonBJet_TOPTOPLEPHBB_CharmCvsL = NonBJetCharmCvsL[idx_NONBJETHAD_TOPTOPLEPHBB];

	_HiggsBJet1_TOPTOPLEPHBB_CharmCvsB = BJetCharmCvsB[idx_BJET1_TOPTOPLEPHBB];
	_HiggsBJet2_TOPTOPLEPHBB_CharmCvsB = BJetCharmCvsB[idx_BJET2_TOPTOPLEPHBB];
	_TopLepBJet_TOPTOPLEPHBB_CharmCvsB = BJetCharmCvsB[idx_BJETLEP_TOPTOPLEPHBB];
	_TopHadNonBJet_TOPTOPLEPHBB_CharmCvsB = NonBJetCharmCvsB[idx_NONBJETHAD_TOPTOPLEPHBB];
	
	for(int i=0;i<_v_JetTight->size();i++)
	  {
	     float pt = _v_JetTight->at(i).pt();
	     float eta = _v_JetTight->at(i).eta();
	     float phi = _v_JetTight->at(i).phi();

	     if( fabs(_HiggsBJet1_TOPTOPLEPHBB_p4.Pt()-pt) < 10E-5 &&
		 fabs(_HiggsBJet1_TOPTOPLEPHBB_p4.Eta()-eta) < 10E-5 &&
		 fabs(_HiggsBJet1_TOPTOPLEPHBB_p4.Phi()-phi) < 10E-5 )
	       _HiggsBJet1_TOPTOPLEPHBB_JetIdx = i;

	     if( fabs(_HiggsBJet2_TOPTOPLEPHBB_p4.Pt()-pt) < 10E-5 &&
		 fabs(_HiggsBJet2_TOPTOPLEPHBB_p4.Eta()-eta) < 10E-5 &&
		 fabs(_HiggsBJet2_TOPTOPLEPHBB_p4.Phi()-phi) < 10E-5 )
	       _HiggsBJet2_TOPTOPLEPHBB_JetIdx = i;

	     if( fabs(_TopLepBJet_TOPTOPLEPHBB_p4.Pt()-pt) < 10E-5 &&
		 fabs(_TopLepBJet_TOPTOPLEPHBB_p4.Eta()-eta) < 10E-5 &&
		 fabs(_TopLepBJet_TOPTOPLEPHBB_p4.Phi()-phi) < 10E-5 )
	       _TopLepBJet_TOPTOPLEPHBB_JetIdx = i;

	     if( fabs(_TopHadNonBJet_TOPTOPLEPHBB_p4.Pt()-pt) < 10E-5 &&
		 fabs(_TopHadNonBJet_TOPTOPLEPHBB_p4.Eta()-eta) < 10E-5 &&
		 fabs(_TopHadNonBJet_TOPTOPLEPHBB_p4.Phi()-phi) < 10E-5 )
	       _TopHadNonBJet_TOPTOPLEPHBB_JetIdx = i;
	  }	
     }

   // tH single top
   if( nLep == 1 && ((nbjets == 0 && nnonbjets >= 3) ||
		     (nbjets == 1 && nnonbjets >= 2) ||
		     (nbjets == 2 && nnonbjets >= 1) ||
		     (nbjets >= 3 && nnonbjets >= 0)) )
     {		
	kfTopHLepbb->Init(TOPHLEPBB);

	std::vector<float> BJetPt;
	std::vector<float> BJetEta;
	std::vector<float> BJetPhi;
	std::vector<float> BJetE;
	std::vector<float> BJetCSVv2;
	std::vector<float> BJetCharge;
	std::vector<float> BJetChargeVec;
	std::vector<float> BJetCharmCvsL;
	std::vector<float> BJetCharmCvsB;
	std::vector<float> BJetPtJesUp;
	std::vector<float> BJetEtaJesUp;
	std::vector<float> BJetPhiJesUp;
	std::vector<float> BJetEJesUp;
	std::vector<float> BJetPtJesDown;
	std::vector<float> BJetEtaJesDown;
	std::vector<float> BJetPhiJesDown;
	std::vector<float> BJetEJesDown;
	std::vector<float> BJetPtJerUp;
	std::vector<float> BJetEtaJerUp;
	std::vector<float> BJetPhiJerUp;
	std::vector<float> BJetEJerUp;
	std::vector<float> BJetPtJerDown;
	std::vector<float> BJetEtaJerDown;
	std::vector<float> BJetPhiJerDown;
	std::vector<float> BJetEJerDown;
	
	std::vector<float> NonBJetPt;
	std::vector<float> NonBJetEta;
	std::vector<float> NonBJetPhi;
	std::vector<float> NonBJetE;
	std::vector<float> NonBJetCSVv2;
	std::vector<float> NonBJetCharge;
	std::vector<float> NonBJetChargeVec;
	std::vector<float> NonBJetCharmCvsL;
	std::vector<float> NonBJetCharmCvsB;
	std::vector<float> NonBJetPtJesUp;
	std::vector<float> NonBJetEtaJesUp;
	std::vector<float> NonBJetPhiJesUp;
	std::vector<float> NonBJetEJesUp;
	std::vector<float> NonBJetPtJesDown;
	std::vector<float> NonBJetEtaJesDown;
	std::vector<float> NonBJetPhiJesDown;
	std::vector<float> NonBJetEJesDown;
	std::vector<float> NonBJetPtJerUp;
	std::vector<float> NonBJetEtaJerUp;
	std::vector<float> NonBJetPhiJerUp;
	std::vector<float> NonBJetEJerUp;
	std::vector<float> NonBJetPtJerDown;
	std::vector<float> NonBJetEtaJerDown;
	std::vector<float> NonBJetPhiJerDown;
	std::vector<float> NonBJetEJerDown;
	
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
	     float pt = _v_BJetTight->at(i).pt();
	     float eta = _v_BJetTight->at(i).eta();
	     float phi = _v_BJetTight->at(i).phi();
	     float E = _v_BJetTight->at(i).E();
	     float CSVv2 = _v_BJetTight->at(i).CSVv2();
	     float charge = _v_BJetTight->at(i).charge();
	     float chargeVec = _v_BJetTight->at(i).chargeVec();
	     float CharmCvsL = _v_BJetTight->at(i).CharmCvsL();
	     float CharmCvsB = _v_BJetTight->at(i).CharmCvsB();
	     float ptJesUp = _v_BJetTight->at(i).p4_jesTotalUp().Pt();
	     float etaJesUp = _v_BJetTight->at(i).p4_jesTotalUp().PseudoRapidity();
	     float phiJesUp = _v_BJetTight->at(i).p4_jesTotalUp().Phi();
	     float EJesUp = _v_BJetTight->at(i).p4_jesTotalUp().E();
	     float ptJesDown = _v_BJetTight->at(i).p4_jesTotalDown().Pt();
	     float etaJesDown = _v_BJetTight->at(i).p4_jesTotalDown().PseudoRapidity();
	     float phiJesDown = _v_BJetTight->at(i).p4_jesTotalDown().Phi();
	     float EJesDown = _v_BJetTight->at(i).p4_jesTotalDown().E();
	     float ptJerUp = _v_BJetTight->at(i).p4_jerTotalUp().Pt();
	     float etaJerUp = _v_BJetTight->at(i).p4_jerTotalUp().PseudoRapidity();
	     float phiJerUp = _v_BJetTight->at(i).p4_jerTotalUp().Phi();
	     float EJerUp = _v_BJetTight->at(i).p4_jerTotalUp().E();
	     float ptJerDown = _v_BJetTight->at(i).p4_jerTotalDown().Pt();
	     float etaJerDown = _v_BJetTight->at(i).p4_jerTotalDown().PseudoRapidity();
	     float phiJerDown = _v_BJetTight->at(i).p4_jerTotalDown().Phi();
	     float EJerDown = _v_BJetTight->at(i).p4_jerTotalDown().E();
	     
	     BJetPt.push_back(pt);
	     BJetEta.push_back(eta);
	     BJetPhi.push_back(phi);
	     BJetE.push_back(E);
	     BJetCSVv2.push_back(CSVv2);
	     BJetCharge.push_back(charge);
	     BJetChargeVec.push_back(chargeVec);
	     BJetCharmCvsL.push_back(CharmCvsL);
	     BJetCharmCvsB.push_back(CharmCvsB);
	     BJetPtJesUp.push_back(ptJesUp);
	     BJetEtaJesUp.push_back(etaJesUp);
	     BJetPhiJesUp.push_back(phiJesUp);
	     BJetEJesUp.push_back(EJesUp);
	     BJetPtJesDown.push_back(ptJesDown);
	     BJetEtaJesDown.push_back(etaJesDown);
	     BJetPhiJesDown.push_back(phiJesDown);
	     BJetEJesDown.push_back(EJesDown);
	     BJetPtJerUp.push_back(ptJerUp);
	     BJetEtaJerUp.push_back(etaJerUp);
	     BJetPhiJerUp.push_back(phiJerUp);
	     BJetEJerUp.push_back(EJerUp);
	     BJetPtJerDown.push_back(ptJerDown);
	     BJetEtaJerDown.push_back(etaJerDown);
	     BJetPhiJerDown.push_back(phiJerDown);
	     BJetEJerDown.push_back(EJerDown);
	  }   
	     
	for(int i=0;i<_v_NonBJetTight->size();i++)
	  {
	     float pt = _v_NonBJetTight->at(i).pt();
	     float eta = _v_NonBJetTight->at(i).eta();
	     float phi = _v_NonBJetTight->at(i).phi();
	     float E = _v_NonBJetTight->at(i).E();
	     float CSVv2 = _v_NonBJetTight->at(i).CSVv2();
	     float charge = _v_NonBJetTight->at(i).charge();
	     float chargeVec = _v_NonBJetTight->at(i).chargeVec();
	     float CharmCvsL = _v_NonBJetTight->at(i).CharmCvsL();
	     float CharmCvsB = _v_NonBJetTight->at(i).CharmCvsB();
	     float ptJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().Pt();
	     float etaJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().PseudoRapidity();
	     float phiJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().Phi();
	     float EJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().E();
	     float ptJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().Pt();
	     float etaJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().PseudoRapidity();
	     float phiJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().Phi();
	     float EJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().E();
	     float ptJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().Pt();
	     float etaJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().PseudoRapidity();
	     float phiJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().Phi();
	     float EJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().E();
	     float ptJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().Pt();
	     float etaJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().PseudoRapidity();
	     float phiJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().Phi();
	     float EJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().E();
	     
	     if( (nbjets == 0 && i < 3) ||
		 (nbjets == 1 && i < 2) ||
		 (nbjets == 2 && i < 1) )
	       {		  
		  BJetPt.push_back(pt);
		  BJetEta.push_back(eta);
		  BJetPhi.push_back(phi);
		  BJetE.push_back(E);
		  BJetCSVv2.push_back(CSVv2);
		  BJetCharge.push_back(charge);
		  BJetChargeVec.push_back(chargeVec);
		  BJetCharmCvsL.push_back(CharmCvsL);
		  BJetCharmCvsB.push_back(CharmCvsB);
		  BJetPtJesUp.push_back(ptJesUp);
		  BJetEtaJesUp.push_back(etaJesUp);
		  BJetPhiJesUp.push_back(phiJesUp);
		  BJetEJesUp.push_back(EJesUp);
		  BJetPtJesDown.push_back(ptJesDown);
		  BJetEtaJesDown.push_back(etaJesDown);
		  BJetPhiJesDown.push_back(phiJesDown);
		  BJetEJesDown.push_back(EJesDown);
		  BJetPtJerUp.push_back(ptJerUp);
		  BJetEtaJerUp.push_back(etaJerUp);
		  BJetPhiJerUp.push_back(phiJerUp);
		  BJetEJerUp.push_back(EJerUp);
		  BJetPtJerDown.push_back(ptJerDown);
		  BJetEtaJerDown.push_back(etaJerDown);
		  BJetPhiJerDown.push_back(phiJerDown);
		  BJetEJerDown.push_back(EJerDown);
	       }
	     else
	       {
		  NonBJetPt.push_back(pt);
		  NonBJetEta.push_back(eta);
		  NonBJetPhi.push_back(phi);
		  NonBJetE.push_back(E);
		  NonBJetCSVv2.push_back(CSVv2);
		  NonBJetCharge.push_back(charge);
		  NonBJetChargeVec.push_back(chargeVec);
		  NonBJetCharmCvsL.push_back(CharmCvsL);
		  NonBJetCharmCvsB.push_back(CharmCvsB);
		  NonBJetPtJesUp.push_back(ptJesUp);
		  NonBJetEtaJesUp.push_back(etaJesUp);
		  NonBJetPhiJesUp.push_back(phiJesUp);
		  NonBJetEJesUp.push_back(EJesUp);
		  NonBJetPtJesDown.push_back(ptJesDown);
		  NonBJetEtaJesDown.push_back(etaJesDown);
		  NonBJetPhiJesDown.push_back(phiJesDown);
		  NonBJetEJesDown.push_back(EJesDown);
		  NonBJetPtJerUp.push_back(ptJerUp);
		  NonBJetEtaJerUp.push_back(etaJerUp);
		  NonBJetPhiJerUp.push_back(phiJerUp);
		  NonBJetEJerUp.push_back(EJerUp);
		  NonBJetPtJerDown.push_back(ptJerDown);
		  NonBJetEtaJerDown.push_back(etaJerDown);
		  NonBJetPhiJerDown.push_back(phiJerDown);
		  NonBJetEJerDown.push_back(EJerDown);
	       }	     
	  }   
	
	kfTopHLepbb->SetBJet(BJetPt,BJetEta,BJetPhi,BJetE);
	kfTopHLepbb->SetNonBJet(NonBJetPt,NonBJetEta,NonBJetPhi,NonBJetE);
	kfTopHLepbb->SetElectron(ElectronPt,ElectronEta,ElectronPhi,ElectronE);
	kfTopHLepbb->SetMuon(MuonPt,MuonEta,MuonPhi,MuonE);
	kfTopHLepbb->SetMet(metpx,metpy);
	
	kfTopHLepbb->Run();

	std::vector<std::pair<float,int> > MVADisc;
	std::vector<std::pair<float,int> > MVADiscJesUp;
	std::vector<std::pair<float,int> > MVADiscJesDown;
	std::vector<std::pair<float,int> > MVADiscJerUp;
	std::vector<std::pair<float,int> > MVADiscJerDown;
	
	int nPerm = kfTopHLepbb->GetNPerm();
	
	for(int ip=0;ip<nPerm;ip++)
	  {
	     float disc = kfTopHLepbb->GetDisc(ip);

	     int idx_ELECTRON_TOPHLEPBB = kfTopHLepbb->GetIndex(ELECTRON_TOPHLEPBB,ip);
	     int idx_MUON_TOPHLEPBB = kfTopHLepbb->GetIndex(MUON_TOPHLEPBB,ip);
	     int idx_BJETLEP_TOPHLEPBB = kfTopHLepbb->GetIndex(BJETLEP_TOPHLEPBB,ip);
	     int idx_BJET1_TOPHLEPBB = kfTopHLepbb->GetIndex(BJET1_TOPHLEPBB,ip);
	     int idx_BJET2_TOPHLEPBB = kfTopHLepbb->GetIndex(BJET2_TOPHLEPBB,ip);

	     float NuPx = kfTopHLepbb->GetNuPx(ip,0);
	     float NuPy = kfTopHLepbb->GetNuPy(ip,0);
	     float NuPz = kfTopHLepbb->GetNuPz(ip,0);
	     float NuE = sqrt(NuPx*NuPx+NuPy*NuPy+NuPz*NuPz);

	     TLorentzVector *TopLepWNu_p4 = new TLorentzVector();
	     TopLepWNu_p4->SetPxPyPzE(NuPx,NuPy,NuPz,NuE);
	     
	     TLorentzVector *HiggsBJet1_p4 = new TLorentzVector();
	     HiggsBJet1_p4->SetPtEtaPhiE(BJetPt[idx_BJET1_TOPHLEPBB],
					 BJetEta[idx_BJET1_TOPHLEPBB],
					 BJetPhi[idx_BJET1_TOPHLEPBB],
					 BJetE[idx_BJET1_TOPHLEPBB]);
	     TLorentzVector *HiggsBJet1JesUp_p4 = new TLorentzVector();
	     HiggsBJet1JesUp_p4->SetPtEtaPhiE(BJetPtJesUp[idx_BJET1_TOPHLEPBB],
					      BJetEtaJesUp[idx_BJET1_TOPHLEPBB],
					      BJetPhiJesUp[idx_BJET1_TOPHLEPBB],
					      BJetEJesUp[idx_BJET1_TOPHLEPBB]);
	     TLorentzVector *HiggsBJet1JesDown_p4 = new TLorentzVector();
	     HiggsBJet1JesDown_p4->SetPtEtaPhiE(BJetPtJesDown[idx_BJET1_TOPHLEPBB],
						BJetEtaJesDown[idx_BJET1_TOPHLEPBB],
						BJetPhiJesDown[idx_BJET1_TOPHLEPBB],
						BJetEJesDown[idx_BJET1_TOPHLEPBB]);
	     TLorentzVector *HiggsBJet1JerUp_p4 = new TLorentzVector();
	     HiggsBJet1JerUp_p4->SetPtEtaPhiE(BJetPtJerUp[idx_BJET1_TOPHLEPBB],
					      BJetEtaJerUp[idx_BJET1_TOPHLEPBB],
					      BJetPhiJerUp[idx_BJET1_TOPHLEPBB],
					      BJetEJerUp[idx_BJET1_TOPHLEPBB]);
	     TLorentzVector *HiggsBJet1JerDown_p4 = new TLorentzVector();
	     HiggsBJet1JerDown_p4->SetPtEtaPhiE(BJetPtJerDown[idx_BJET1_TOPHLEPBB],
						BJetEtaJerDown[idx_BJET1_TOPHLEPBB],
						BJetPhiJerDown[idx_BJET1_TOPHLEPBB],
						BJetEJerDown[idx_BJET1_TOPHLEPBB]);
	     
	     TLorentzVector *HiggsBJet2_p4 = new TLorentzVector();
	     HiggsBJet2_p4->SetPtEtaPhiE(BJetPt[idx_BJET2_TOPHLEPBB],
					BJetEta[idx_BJET2_TOPHLEPBB],
					BJetPhi[idx_BJET2_TOPHLEPBB],
					BJetE[idx_BJET2_TOPHLEPBB]);
	     TLorentzVector *HiggsBJet2JesUp_p4 = new TLorentzVector();
	     HiggsBJet2JesUp_p4->SetPtEtaPhiE(BJetPtJesUp[idx_BJET2_TOPHLEPBB],
					      BJetEtaJesUp[idx_BJET2_TOPHLEPBB],
					      BJetPhiJesUp[idx_BJET2_TOPHLEPBB],
					      BJetEJesUp[idx_BJET2_TOPHLEPBB]);
	     TLorentzVector *HiggsBJet2JesDown_p4 = new TLorentzVector();
	     HiggsBJet2JesDown_p4->SetPtEtaPhiE(BJetPtJesDown[idx_BJET2_TOPHLEPBB],
						BJetEtaJesDown[idx_BJET2_TOPHLEPBB],
						BJetPhiJesDown[idx_BJET2_TOPHLEPBB],
						BJetEJesDown[idx_BJET2_TOPHLEPBB]);
	     TLorentzVector *HiggsBJet2JerUp_p4 = new TLorentzVector();
	     HiggsBJet2JerUp_p4->SetPtEtaPhiE(BJetPtJerUp[idx_BJET2_TOPHLEPBB],
					      BJetEtaJerUp[idx_BJET2_TOPHLEPBB],
					      BJetPhiJerUp[idx_BJET2_TOPHLEPBB],
					      BJetEJerUp[idx_BJET2_TOPHLEPBB]);
	     TLorentzVector *HiggsBJet2JerDown_p4 = new TLorentzVector();
	     HiggsBJet2JerDown_p4->SetPtEtaPhiE(BJetPtJerDown[idx_BJET2_TOPHLEPBB],
						BJetEtaJerDown[idx_BJET2_TOPHLEPBB],
						BJetPhiJerDown[idx_BJET2_TOPHLEPBB],
						BJetEJerDown[idx_BJET2_TOPHLEPBB]);
	     
	     TLorentzVector *TopLepBJet_p4 = new TLorentzVector();
	     TopLepBJet_p4->SetPtEtaPhiE(BJetPt[idx_BJETLEP_TOPHLEPBB],
					 BJetEta[idx_BJETLEP_TOPHLEPBB],
					 BJetPhi[idx_BJETLEP_TOPHLEPBB],
					 BJetE[idx_BJETLEP_TOPHLEPBB]);
	     TLorentzVector *TopLepBJetJesUp_p4 = new TLorentzVector();
	     TopLepBJetJesUp_p4->SetPtEtaPhiE(BJetPtJesUp[idx_BJETLEP_TOPHLEPBB],
					      BJetEtaJesUp[idx_BJETLEP_TOPHLEPBB],
					      BJetPhiJesUp[idx_BJETLEP_TOPHLEPBB],
					      BJetEJesUp[idx_BJETLEP_TOPHLEPBB]);
	     TLorentzVector *TopLepBJetJesDown_p4 = new TLorentzVector();
	     TopLepBJetJesDown_p4->SetPtEtaPhiE(BJetPtJesDown[idx_BJETLEP_TOPHLEPBB],
						BJetEtaJesDown[idx_BJETLEP_TOPHLEPBB],
						BJetPhiJesDown[idx_BJETLEP_TOPHLEPBB],
						BJetEJesDown[idx_BJETLEP_TOPHLEPBB]);
	     TLorentzVector *TopLepBJetJerUp_p4 = new TLorentzVector();
	     TopLepBJetJerUp_p4->SetPtEtaPhiE(BJetPtJerUp[idx_BJETLEP_TOPHLEPBB],
					      BJetEtaJerUp[idx_BJETLEP_TOPHLEPBB],
					      BJetPhiJerUp[idx_BJETLEP_TOPHLEPBB],
					      BJetEJerUp[idx_BJETLEP_TOPHLEPBB]);
	     TLorentzVector *TopLepBJetJerDown_p4 = new TLorentzVector();
	     TopLepBJetJerDown_p4->SetPtEtaPhiE(BJetPtJerDown[idx_BJETLEP_TOPHLEPBB],
						BJetEtaJerDown[idx_BJETLEP_TOPHLEPBB],
						BJetPhiJerDown[idx_BJETLEP_TOPHLEPBB],
						BJetEJerDown[idx_BJETLEP_TOPHLEPBB]);
	     
	     TLorentzVector *TopLepWLep_p4 = new TLorentzVector();
	     if( idx_ELECTRON_TOPHLEPBB >= 0 )
	       TopLepWLep_p4->SetPtEtaPhiE(ElectronPt[idx_ELECTRON_TOPHLEPBB],
					   ElectronEta[idx_ELECTRON_TOPHLEPBB],
					   ElectronPhi[idx_ELECTRON_TOPHLEPBB],
					   ElectronE[idx_ELECTRON_TOPHLEPBB]);
	     else
	       TopLepWLep_p4->SetPtEtaPhiE(MuonPt[idx_MUON_TOPHLEPBB],
					   MuonEta[idx_MUON_TOPHLEPBB],
					   MuonPhi[idx_MUON_TOPHLEPBB],
					   MuonE[idx_MUON_TOPHLEPBB]);
	     
	     TLorentzVector Higgs_p4 = *HiggsBJet1_p4+*HiggsBJet2_p4;
	     TLorentzVector HiggsJesUp_p4 = *HiggsBJet1JesUp_p4+*HiggsBJet2JesUp_p4;
	     TLorentzVector HiggsJesDown_p4 = *HiggsBJet1JesDown_p4+*HiggsBJet2JesDown_p4;
	     TLorentzVector HiggsJerUp_p4 = *HiggsBJet1JerUp_p4+*HiggsBJet2JerUp_p4;
	     TLorentzVector HiggsJerDown_p4 = *HiggsBJet1JerDown_p4+*HiggsBJet2JerDown_p4;
	     
	     TLorentzVector TopLepW_p4 = *TopLepWLep_p4+*TopLepWNu_p4;
	     
	     TLorentzVector TopLep_p4 = TopLepW_p4+*TopLepBJet_p4;
	     TLorentzVector TopLepJesUp_p4 = TopLepW_p4+*TopLepBJetJesUp_p4;
	     TLorentzVector TopLepJesDown_p4 = TopLepW_p4+*TopLepBJetJesDown_p4;
	     TLorentzVector TopLepJerUp_p4 = TopLepW_p4+*TopLepBJetJerUp_p4;
	     TLorentzVector TopLepJerDown_p4 = TopLepW_p4+*TopLepBJetJerDown_p4;

	     float VarHiggsRecM = Higgs_p4.M();
	     float VarHiggsRecMJesUp = HiggsJesUp_p4.M();
	     float VarHiggsRecMJesDown = HiggsJesDown_p4.M();
	     float VarHiggsRecMJerUp = HiggsJerUp_p4.M();
	     float VarHiggsRecMJerDown = HiggsJerDown_p4.M();
	     
	     float VarTopLepRecM = TopLep_p4.M();
	     float VarTopLepRecMJesUp = TopLepJesUp_p4.M();
	     float VarTopLepRecMJesDown = TopLepJesDown_p4.M();
	     float VarTopLepRecMJerUp = TopLepJerUp_p4.M();
	     float VarTopLepRecMJerDown = TopLepJerDown_p4.M();
	     
	     float VarHiggsTopLepRecDr = Higgs_p4.DeltaR(TopLep_p4);
	     float VarHiggsTopLepRecDrJesUp = HiggsJesUp_p4.DeltaR(TopLepJesUp_p4);
	     float VarHiggsTopLepRecDrJesDown = HiggsJesDown_p4.DeltaR(TopLepJesDown_p4);
	     float VarHiggsTopLepRecDrJerUp = HiggsJerUp_p4.DeltaR(TopLepJerUp_p4);
	     float VarHiggsTopLepRecDrJerDown = HiggsJerDown_p4.DeltaR(TopLepJerDown_p4);
	     
	     float VarTopLepRecPt = TopLep_p4.Pt();
	     float VarTopLepRecPtJesUp = TopLepJesUp_p4.Pt();
	     float VarTopLepRecPtJesDown = TopLepJesDown_p4.Pt();
	     float VarTopLepRecPtJerUp = TopLepJerUp_p4.Pt();
	     float VarTopLepRecPtJerDown = TopLepJerDown_p4.Pt();
	     
	     TLorentzVector *HiggsT_p4 = new TLorentzVector();
	     HiggsT_p4->SetPxPyPzE(Higgs_p4.Px(),Higgs_p4.Py(),0.,Higgs_p4.Et());
	     TLorentzVector *HiggsTJesUp_p4 = new TLorentzVector();
	     HiggsTJesUp_p4->SetPxPyPzE(HiggsJesUp_p4.Px(),HiggsJesUp_p4.Py(),0.,HiggsJesUp_p4.Et());
	     TLorentzVector *HiggsTJesDown_p4 = new TLorentzVector();
	     HiggsTJesDown_p4->SetPxPyPzE(HiggsJesDown_p4.Px(),HiggsJesDown_p4.Py(),0.,HiggsJesDown_p4.Et());
	     TLorentzVector *HiggsTJerUp_p4 = new TLorentzVector();
	     HiggsTJerUp_p4->SetPxPyPzE(HiggsJerUp_p4.Px(),HiggsJerUp_p4.Py(),0.,HiggsJerUp_p4.Et());
	     TLorentzVector *HiggsTJerDown_p4 = new TLorentzVector();
	     HiggsTJerDown_p4->SetPxPyPzE(HiggsJerDown_p4.Px(),HiggsJerDown_p4.Py(),0.,HiggsJerDown_p4.Et());
	     
	     TLorentzVector *TopLepWLepT_p4 = new TLorentzVector();
	     TopLepWLepT_p4->SetPxPyPzE(TopLepWLep_p4->Px(),TopLepWLep_p4->Py(),0.,TopLepWLep_p4->Et());
	     
	     TLorentzVector *TopLepWNuT_p4 = new TLorentzVector();
	     TopLepWNuT_p4->SetPxPyPzE(TopLepWNu_p4->Px(),TopLepWNu_p4->Py(),0.,TopLepWNu_p4->Et());
	     
	     TLorentzVector *TopLepBJetT_p4 = new TLorentzVector();
	     TopLepBJetT_p4->SetPxPyPzE(TopLepBJet_p4->Px(),TopLepBJet_p4->Py(),0.,TopLepBJet_p4->Et());
	     TLorentzVector *TopLepBJetTJesUp_p4 = new TLorentzVector();
	     TopLepBJetTJesUp_p4->SetPxPyPzE(TopLepBJetJesUp_p4->Px(),TopLepBJetJesUp_p4->Py(),0.,TopLepBJetJesUp_p4->Et());
	     TLorentzVector *TopLepBJetTJesDown_p4 = new TLorentzVector();
	     TopLepBJetTJesDown_p4->SetPxPyPzE(TopLepBJetJesDown_p4->Px(),TopLepBJetJesDown_p4->Py(),0.,TopLepBJetJesDown_p4->Et());
	     TLorentzVector *TopLepBJetTJerUp_p4 = new TLorentzVector();
	     TopLepBJetTJerUp_p4->SetPxPyPzE(TopLepBJetJerUp_p4->Px(),TopLepBJetJerUp_p4->Py(),0.,TopLepBJetJerUp_p4->Et());
	     TLorentzVector *TopLepBJetTJerDown_p4 = new TLorentzVector();
	     TopLepBJetTJerDown_p4->SetPxPyPzE(TopLepBJetJerDown_p4->Px(),TopLepBJetJerDown_p4->Py(),0.,TopLepBJetJerDown_p4->Et());
	     
	     TLorentzVector TopLepT_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetT_p4;
	     TLorentzVector TopLepTJesUp_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJesUp_p4;
	     TLorentzVector TopLepTJesDown_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJesDown_p4;
	     TLorentzVector TopLepTJerUp_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJerUp_p4;
	     TLorentzVector TopLepTJerDown_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJerDown_p4;
	     
	     float VarTopLepRecMT = TopLepT_p4.M();
	     float VarTopLepRecMTJesUp = TopLepTJesUp_p4.M();
	     float VarTopLepRecMTJesDown = TopLepTJesDown_p4.M();
	     float VarTopLepRecMTJerUp = TopLepTJerUp_p4.M();
	     float VarTopLepRecMTJerDown = TopLepTJerDown_p4.M();
	     
	     float VarHiggsTopLepRecDphiT = HiggsT_p4->DeltaPhi(TopLepT_p4);
	     float VarHiggsTopLepRecDphiTJesUp = HiggsTJesUp_p4->DeltaPhi(TopLepTJesUp_p4);
	     float VarHiggsTopLepRecDphiTJesDown = HiggsTJesDown_p4->DeltaPhi(TopLepTJesDown_p4);
	     float VarHiggsTopLepRecDphiTJerUp = HiggsTJerUp_p4->DeltaPhi(TopLepTJerUp_p4);
	     float VarHiggsTopLepRecDphiTJerDown = HiggsTJerDown_p4->DeltaPhi(TopLepTJerDown_p4);
	     
	     float VarTopLepRecPtT = TopLepT_p4.Pt();
	     float VarTopLepRecPtTJesUp = TopLepTJesUp_p4.Pt();
	     float VarTopLepRecPtTJesDown = TopLepTJesDown_p4.Pt();
	     float VarTopLepRecPtTJerUp = TopLepTJerUp_p4.Pt();
	     float VarTopLepRecPtTJerDown = TopLepTJerDown_p4.Pt();
	     
	     if( disc < 10E+8 )
	       {
		  MVAFullReco_HiggsRecM_TOPHLEPBB = VarHiggsRecMJesUp;
		  MVAFullReco_TopLepRecM_TOPHLEPBB = VarTopLepRecMJesUp;
		  MVAFullReco_HiggsTopLepRecDr_TOPHLEPBB = VarHiggsTopLepRecDrJesUp;
		  MVAFullReco_TopLepRecPt_TOPHLEPBB = VarTopLepRecPtJesUp;
		  
		  MVADiscJesUp.push_back(std::make_pair(MVAFullRecoReaderTOPHLEPBB->EvaluateMVA("BDTG method"),ip));

		  MVAFullReco_HiggsRecM_TOPHLEPBB = VarHiggsRecMJesDown;
		  MVAFullReco_TopLepRecM_TOPHLEPBB = VarTopLepRecMJesDown;
		  MVAFullReco_HiggsTopLepRecDr_TOPHLEPBB = VarHiggsTopLepRecDrJesDown;
		  MVAFullReco_TopLepRecPt_TOPHLEPBB = VarTopLepRecPtJesDown;
		  
		  MVADiscJesDown.push_back(std::make_pair(MVAFullRecoReaderTOPHLEPBB->EvaluateMVA("BDTG method"),ip));

		  MVAFullReco_HiggsRecM_TOPHLEPBB = VarHiggsRecMJerUp;
		  MVAFullReco_TopLepRecM_TOPHLEPBB = VarTopLepRecMJerUp;
		  MVAFullReco_HiggsTopLepRecDr_TOPHLEPBB = VarHiggsTopLepRecDrJerUp;
		  MVAFullReco_TopLepRecPt_TOPHLEPBB = VarTopLepRecPtJerUp;
		  
		  MVADiscJerUp.push_back(std::make_pair(MVAFullRecoReaderTOPHLEPBB->EvaluateMVA("BDTG method"),ip));

		  MVAFullReco_HiggsRecM_TOPHLEPBB = VarHiggsRecMJerDown;
		  MVAFullReco_TopLepRecM_TOPHLEPBB = VarTopLepRecMJerDown;
		  MVAFullReco_HiggsTopLepRecDr_TOPHLEPBB = VarHiggsTopLepRecDrJerDown;
		  MVAFullReco_TopLepRecPt_TOPHLEPBB = VarTopLepRecPtJerDown;
		  
		  MVADiscJerDown.push_back(std::make_pair(MVAFullRecoReaderTOPHLEPBB->EvaluateMVA("BDTG method"),ip));
		  
		  MVAFullReco_HiggsRecM_TOPHLEPBB = VarHiggsRecM;
		  MVAFullReco_TopLepRecM_TOPHLEPBB = VarTopLepRecM;
		  MVAFullReco_HiggsTopLepRecDr_TOPHLEPBB = VarHiggsTopLepRecDr;
		  MVAFullReco_TopLepRecPt_TOPHLEPBB = VarTopLepRecPt;
		  
		  MVADisc.push_back(std::make_pair(MVAFullRecoReaderTOPHLEPBB->EvaluateMVA("BDTG method"),ip));
	       }	
	     else
	       {
		  MVAPartReco_HiggsRecM_TOPHLEPBB = VarHiggsRecMJesUp;
		  MVAPartReco_TopLepRecMT_TOPHLEPBB = VarTopLepRecMTJesUp;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPHLEPBB = VarHiggsTopLepRecDphiTJesUp;
		  MVAPartReco_TopLepRecPtT_TOPHLEPBB = VarTopLepRecPtTJesUp;
		  
		  MVADiscJesUp.push_back(std::make_pair(MVAPartRecoReaderTOPHLEPBB->EvaluateMVA("BDTG method"),ip));

		  MVAPartReco_HiggsRecM_TOPHLEPBB = VarHiggsRecMJesDown;
		  MVAPartReco_TopLepRecMT_TOPHLEPBB = VarTopLepRecMTJesDown;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPHLEPBB = VarHiggsTopLepRecDphiTJesDown;
		  MVAPartReco_TopLepRecPtT_TOPHLEPBB = VarTopLepRecPtTJesDown;
		  
		  MVADiscJesDown.push_back(std::make_pair(MVAPartRecoReaderTOPHLEPBB->EvaluateMVA("BDTG method"),ip));

		  MVAPartReco_HiggsRecM_TOPHLEPBB = VarHiggsRecMJerUp;
		  MVAPartReco_TopLepRecMT_TOPHLEPBB = VarTopLepRecMTJerUp;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPHLEPBB = VarHiggsTopLepRecDphiTJerUp;
		  MVAPartReco_TopLepRecPtT_TOPHLEPBB = VarTopLepRecPtTJerUp;
		  
		  MVADiscJerUp.push_back(std::make_pair(MVAPartRecoReaderTOPHLEPBB->EvaluateMVA("BDTG method"),ip));

		  MVAPartReco_HiggsRecM_TOPHLEPBB = VarHiggsRecMJerDown;
		  MVAPartReco_TopLepRecMT_TOPHLEPBB = VarTopLepRecMTJerDown;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPHLEPBB = VarHiggsTopLepRecDphiTJerDown;
		  MVAPartReco_TopLepRecPtT_TOPHLEPBB = VarTopLepRecPtTJerDown;
		  
		  MVADiscJerDown.push_back(std::make_pair(MVAPartRecoReaderTOPHLEPBB->EvaluateMVA("BDTG method"),ip));
		  
		  MVAPartReco_HiggsRecM_TOPHLEPBB = VarHiggsRecM;
		  MVAPartReco_TopLepRecMT_TOPHLEPBB = VarTopLepRecMT;
		  MVAPartReco_HiggsTopLepRecDphiT_TOPHLEPBB = VarHiggsTopLepRecDphiT;
		  MVAPartReco_TopLepRecPtT_TOPHLEPBB = VarTopLepRecPtT;
		  
		  MVADisc.push_back(std::make_pair(MVAPartRecoReaderTOPHLEPBB->EvaluateMVA("BDTG method"),ip));
	       }	     

	     delete TopLepWNu_p4;
	     delete HiggsBJet1_p4;
	     delete HiggsBJet1JesUp_p4;
	     delete HiggsBJet1JesDown_p4;
	     delete HiggsBJet1JerUp_p4;
	     delete HiggsBJet1JerDown_p4;
	     delete HiggsBJet2_p4;
	     delete HiggsBJet2JesUp_p4;
	     delete HiggsBJet2JesDown_p4;
	     delete HiggsBJet2JerUp_p4;
	     delete HiggsBJet2JerDown_p4;
	     delete TopLepBJet_p4;
	     delete TopLepBJetJesUp_p4;
	     delete TopLepBJetJesDown_p4;
	     delete TopLepBJetJerUp_p4;
	     delete TopLepBJetJerDown_p4;
	     delete TopLepWLep_p4;
	     delete HiggsT_p4;
	     delete HiggsTJesUp_p4;
	     delete HiggsTJesDown_p4;
	     delete HiggsTJerUp_p4;
	     delete HiggsTJerDown_p4;
	     delete TopLepWLepT_p4;
	     delete TopLepWNuT_p4;
	     delete TopLepBJetT_p4;
	     delete TopLepBJetTJesUp_p4;
	     delete TopLepBJetTJesDown_p4;
	     delete TopLepBJetTJerUp_p4;
	     delete TopLepBJetTJerDown_p4;
	  }
	
	std::sort(MVADisc.begin(),MVADisc.end(),sortFunc());
	int IdxPerm = MVADisc.at(0).second;

	_chi2_TOPHLEPBB = kfTopHLepbb->GetDisc(IdxPerm);
	_MVA_TOPHLEPBB = MVADisc.at(0).first;
	_MVAJesUp_TOPHLEPBB = MVADiscJesUp.at(IdxPerm).first;
	_MVAJesDown_TOPHLEPBB = MVADiscJesDown.at(IdxPerm).first;
	_MVAJerUp_TOPHLEPBB = MVADiscJerUp.at(IdxPerm).first;
	_MVAJerDown_TOPHLEPBB = MVADiscJerDown.at(IdxPerm).first;
	
	int idx_ELECTRON_TOPHLEPBB = kfTopHLepbb->GetIndex(ELECTRON_TOPHLEPBB,IdxPerm);
	int idx_MUON_TOPHLEPBB = kfTopHLepbb->GetIndex(MUON_TOPHLEPBB,IdxPerm);
	int idx_BJETLEP_TOPHLEPBB = kfTopHLepbb->GetIndex(BJETLEP_TOPHLEPBB,IdxPerm);
	int idx_BJET1_TOPHLEPBB = kfTopHLepbb->GetIndex(BJET1_TOPHLEPBB,IdxPerm);
	int idx_BJET2_TOPHLEPBB = kfTopHLepbb->GetIndex(BJET2_TOPHLEPBB,IdxPerm);

	float NuPx = kfTopHLepbb->GetNuPx(IdxPerm,0);
	float NuPy = kfTopHLepbb->GetNuPy(IdxPerm,0);
	float NuPz = kfTopHLepbb->GetNuPz(IdxPerm,0);
	float NuE = sqrt(NuPx*NuPx+NuPy*NuPy+NuPz*NuPz);

	_TopLepWNu_TOPHLEPBB_p4.SetPxPyPzE(NuPx,NuPy,NuPz,NuE);
	
	_HiggsBJet1_TOPHLEPBB_p4.SetPtEtaPhiE(BJetPt[idx_BJET1_TOPHLEPBB],
					      BJetEta[idx_BJET1_TOPHLEPBB],
					      BJetPhi[idx_BJET1_TOPHLEPBB],
					      BJetE[idx_BJET1_TOPHLEPBB]);
	_HiggsBJet1_TOPHLEPBB_JesUp_p4.SetPtEtaPhiE(BJetPtJesUp[idx_BJET1_TOPHLEPBB],
						    BJetEtaJesUp[idx_BJET1_TOPHLEPBB],
						    BJetPhiJesUp[idx_BJET1_TOPHLEPBB],
						    BJetEJesUp[idx_BJET1_TOPHLEPBB]);
	_HiggsBJet1_TOPHLEPBB_JesDown_p4.SetPtEtaPhiE(BJetPtJesDown[idx_BJET1_TOPHLEPBB],
						      BJetEtaJesDown[idx_BJET1_TOPHLEPBB],
						      BJetPhiJesDown[idx_BJET1_TOPHLEPBB],
						      BJetEJesDown[idx_BJET1_TOPHLEPBB]);
	_HiggsBJet1_TOPHLEPBB_JerUp_p4.SetPtEtaPhiE(BJetPtJerUp[idx_BJET1_TOPHLEPBB],
						    BJetEtaJerUp[idx_BJET1_TOPHLEPBB],
						    BJetPhiJerUp[idx_BJET1_TOPHLEPBB],
						    BJetEJerUp[idx_BJET1_TOPHLEPBB]);
	_HiggsBJet1_TOPHLEPBB_JerDown_p4.SetPtEtaPhiE(BJetPtJerDown[idx_BJET1_TOPHLEPBB],
						      BJetEtaJerDown[idx_BJET1_TOPHLEPBB],
						      BJetPhiJerDown[idx_BJET1_TOPHLEPBB],
						      BJetEJerDown[idx_BJET1_TOPHLEPBB]);
	
	_HiggsBJet2_TOPHLEPBB_p4.SetPtEtaPhiE(BJetPt[idx_BJET2_TOPHLEPBB],
					      BJetEta[idx_BJET2_TOPHLEPBB],
					      BJetPhi[idx_BJET2_TOPHLEPBB],
					      BJetE[idx_BJET2_TOPHLEPBB]);
	_HiggsBJet2_TOPHLEPBB_JesUp_p4.SetPtEtaPhiE(BJetPtJesUp[idx_BJET2_TOPHLEPBB],
						    BJetEtaJesUp[idx_BJET2_TOPHLEPBB],
						    BJetPhiJesUp[idx_BJET2_TOPHLEPBB],
						    BJetEJesUp[idx_BJET2_TOPHLEPBB]);
	_HiggsBJet2_TOPHLEPBB_JesDown_p4.SetPtEtaPhiE(BJetPtJesDown[idx_BJET2_TOPHLEPBB],
						      BJetEtaJesDown[idx_BJET2_TOPHLEPBB],
						      BJetPhiJesDown[idx_BJET2_TOPHLEPBB],
						      BJetEJesDown[idx_BJET2_TOPHLEPBB]);
	_HiggsBJet2_TOPHLEPBB_JerUp_p4.SetPtEtaPhiE(BJetPtJerUp[idx_BJET2_TOPHLEPBB],
						    BJetEtaJerUp[idx_BJET2_TOPHLEPBB],
						    BJetPhiJerUp[idx_BJET2_TOPHLEPBB],
						    BJetEJerUp[idx_BJET2_TOPHLEPBB]);
	_HiggsBJet2_TOPHLEPBB_JerDown_p4.SetPtEtaPhiE(BJetPtJerDown[idx_BJET2_TOPHLEPBB],
						      BJetEtaJerDown[idx_BJET2_TOPHLEPBB],
						      BJetPhiJerDown[idx_BJET2_TOPHLEPBB],
						      BJetEJerDown[idx_BJET2_TOPHLEPBB]);
	
	_TopLepBJet_TOPHLEPBB_p4.SetPtEtaPhiE(BJetPt[idx_BJETLEP_TOPHLEPBB],
					      BJetEta[idx_BJETLEP_TOPHLEPBB],
					      BJetPhi[idx_BJETLEP_TOPHLEPBB],
					      BJetE[idx_BJETLEP_TOPHLEPBB]);
	_TopLepBJet_TOPHLEPBB_JesUp_p4.SetPtEtaPhiE(BJetPtJesUp[idx_BJETLEP_TOPHLEPBB],
						    BJetEtaJesUp[idx_BJETLEP_TOPHLEPBB],
						    BJetPhiJesUp[idx_BJETLEP_TOPHLEPBB],
						    BJetEJesUp[idx_BJETLEP_TOPHLEPBB]);
	_TopLepBJet_TOPHLEPBB_JesDown_p4.SetPtEtaPhiE(BJetPtJesDown[idx_BJETLEP_TOPHLEPBB],
						      BJetEtaJesDown[idx_BJETLEP_TOPHLEPBB],
						      BJetPhiJesDown[idx_BJETLEP_TOPHLEPBB],
						      BJetEJesDown[idx_BJETLEP_TOPHLEPBB]);
	_TopLepBJet_TOPHLEPBB_JerUp_p4.SetPtEtaPhiE(BJetPtJerUp[idx_BJETLEP_TOPHLEPBB],
						    BJetEtaJerUp[idx_BJETLEP_TOPHLEPBB],
						    BJetPhiJerUp[idx_BJETLEP_TOPHLEPBB],
						    BJetEJerUp[idx_BJETLEP_TOPHLEPBB]);
	_TopLepBJet_TOPHLEPBB_JerDown_p4.SetPtEtaPhiE(BJetPtJerDown[idx_BJETLEP_TOPHLEPBB],
						      BJetEtaJerDown[idx_BJETLEP_TOPHLEPBB],
						      BJetPhiJerDown[idx_BJETLEP_TOPHLEPBB],
						      BJetEJerDown[idx_BJETLEP_TOPHLEPBB]);
	
	if( idx_ELECTRON_TOPHLEPBB >= 0 )
	  _TopLepWLep_TOPHLEPBB_p4.SetPtEtaPhiE(ElectronPt[idx_ELECTRON_TOPHLEPBB],
						ElectronEta[idx_ELECTRON_TOPHLEPBB],
						ElectronPhi[idx_ELECTRON_TOPHLEPBB],
						ElectronE[idx_ELECTRON_TOPHLEPBB]);
	else
	  _TopLepWLep_TOPHLEPBB_p4.SetPtEtaPhiE(MuonPt[idx_MUON_TOPHLEPBB],
						MuonEta[idx_MUON_TOPHLEPBB],
						MuonPhi[idx_MUON_TOPHLEPBB],
						MuonE[idx_MUON_TOPHLEPBB]);
		
	_Higgs_TOPHLEPBB_p4 = _HiggsBJet1_TOPHLEPBB_p4+_HiggsBJet2_TOPHLEPBB_p4;
	_Higgs_TOPHLEPBB_JesUp_p4 = _HiggsBJet1_TOPHLEPBB_JesUp_p4+_HiggsBJet2_TOPHLEPBB_JesUp_p4;
	_Higgs_TOPHLEPBB_JesDown_p4 = _HiggsBJet1_TOPHLEPBB_JesDown_p4+_HiggsBJet2_TOPHLEPBB_JesDown_p4;
	_Higgs_TOPHLEPBB_JerUp_p4 = _HiggsBJet1_TOPHLEPBB_JerUp_p4+_HiggsBJet2_TOPHLEPBB_JerUp_p4;
	_Higgs_TOPHLEPBB_JerDown_p4 = _HiggsBJet1_TOPHLEPBB_JerDown_p4+_HiggsBJet2_TOPHLEPBB_JerDown_p4;
	
	_TopLepW_TOPHLEPBB_p4 = _TopLepWLep_TOPHLEPBB_p4+_TopLepWNu_TOPHLEPBB_p4;
	
	_TopLep_TOPHLEPBB_p4 = _TopLepW_TOPHLEPBB_p4+_TopLepBJet_TOPHLEPBB_p4;
	_TopLep_TOPHLEPBB_JesUp_p4 = _TopLepW_TOPHLEPBB_p4+_TopLepBJet_TOPHLEPBB_JesUp_p4;
	_TopLep_TOPHLEPBB_JesDown_p4 = _TopLepW_TOPHLEPBB_p4+_TopLepBJet_TOPHLEPBB_JesDown_p4;
	_TopLep_TOPHLEPBB_JerUp_p4 = _TopLepW_TOPHLEPBB_p4+_TopLepBJet_TOPHLEPBB_JerUp_p4;
	_TopLep_TOPHLEPBB_JerDown_p4 = _TopLepW_TOPHLEPBB_p4+_TopLepBJet_TOPHLEPBB_JerDown_p4;

	_HiggsBJet1_TOPHLEPBB_CSVv2 = BJetCSVv2[idx_BJET1_TOPHLEPBB];
	_HiggsBJet2_TOPHLEPBB_CSVv2 = BJetCSVv2[idx_BJET2_TOPHLEPBB];
	_TopLepBJet_TOPHLEPBB_CSVv2 = BJetCSVv2[idx_BJETLEP_TOPHLEPBB];

	_HiggsBJet1_TOPHLEPBB_charge = BJetCharge[idx_BJET1_TOPHLEPBB];
	_HiggsBJet2_TOPHLEPBB_charge = BJetCharge[idx_BJET2_TOPHLEPBB];
	_TopLepBJet_TOPHLEPBB_charge = BJetCharge[idx_BJETLEP_TOPHLEPBB];

	_HiggsBJet1_TOPHLEPBB_chargeVec = BJetChargeVec[idx_BJET1_TOPHLEPBB];
	_HiggsBJet2_TOPHLEPBB_chargeVec = BJetChargeVec[idx_BJET2_TOPHLEPBB];
	_TopLepBJet_TOPHLEPBB_chargeVec = BJetChargeVec[idx_BJETLEP_TOPHLEPBB];

	_HiggsBJet1_TOPHLEPBB_CharmCvsL = BJetCharmCvsL[idx_BJET1_TOPHLEPBB];
	_HiggsBJet2_TOPHLEPBB_CharmCvsL = BJetCharmCvsL[idx_BJET2_TOPHLEPBB];
	_TopLepBJet_TOPHLEPBB_CharmCvsL = BJetCharmCvsL[idx_BJETLEP_TOPHLEPBB];

	_HiggsBJet1_TOPHLEPBB_CharmCvsB = BJetCharmCvsB[idx_BJET1_TOPHLEPBB];
	_HiggsBJet2_TOPHLEPBB_CharmCvsB = BJetCharmCvsB[idx_BJET2_TOPHLEPBB];
	_TopLepBJet_TOPHLEPBB_CharmCvsB = BJetCharmCvsB[idx_BJETLEP_TOPHLEPBB];

	for(int i=0;i<_v_JetTight->size();i++)
	  {
	     float pt = _v_JetTight->at(i).pt();
	     float eta = _v_JetTight->at(i).eta();
	     float phi = _v_JetTight->at(i).phi();
	     
	     if( fabs(_HiggsBJet1_TOPHLEPBB_p4.Pt()-pt) < 10E-5 &&
		 fabs(_HiggsBJet1_TOPHLEPBB_p4.Eta()-eta) < 10E-5 &&
		 fabs(_HiggsBJet1_TOPHLEPBB_p4.Phi()-phi) < 10E-5 )
	       _HiggsBJet1_TOPHLEPBB_JetIdx = i;

	     if( fabs(_HiggsBJet2_TOPHLEPBB_p4.Pt()-pt) < 10E-5 &&
		 fabs(_HiggsBJet2_TOPHLEPBB_p4.Eta()-eta) < 10E-5 &&
		 fabs(_HiggsBJet2_TOPHLEPBB_p4.Phi()-phi) < 10E-5 )
	       _HiggsBJet2_TOPHLEPBB_JetIdx = i;

	     if( fabs(_TopLepBJet_TOPHLEPBB_p4.Pt()-pt) < 10E-5 &&
		 fabs(_TopLepBJet_TOPHLEPBB_p4.Eta()-eta) < 10E-5 &&
		 fabs(_TopLepBJet_TOPHLEPBB_p4.Phi()-phi) < 10E-5 )
	       _TopLepBJet_TOPHLEPBB_JetIdx = i;
	  }	
     }

   // ttbar
   if( nLep == 1 && ((nbjets == 0 && nnonbjets >= 4) ||
		     (nbjets == 1 && nnonbjets >= 3) ||
		     (nbjets == 2 && nnonbjets >= 2) ||
		     (nbjets == 3 && nnonbjets >= 1) ||
		     (nbjets >= 4 && nnonbjets >= 0)) )
     {		
	kfTopTopLepHad->Init(TOPTOPLEPHAD);
	
	std::vector<float> BJetPt;
	std::vector<float> BJetEta;
	std::vector<float> BJetPhi;
	std::vector<float> BJetE;
	std::vector<float> BJetCSVv2;
	std::vector<float> BJetCharge;
	std::vector<float> BJetChargeVec;
	std::vector<float> BJetCharmCvsL;
	std::vector<float> BJetCharmCvsB;
	std::vector<float> BJetPtJesUp;
	std::vector<float> BJetEtaJesUp;
	std::vector<float> BJetPhiJesUp;
	std::vector<float> BJetEJesUp;
	std::vector<float> BJetPtJesDown;
	std::vector<float> BJetEtaJesDown;
	std::vector<float> BJetPhiJesDown;
	std::vector<float> BJetEJesDown;
	std::vector<float> BJetPtJerUp;
	std::vector<float> BJetEtaJerUp;
	std::vector<float> BJetPhiJerUp;
	std::vector<float> BJetEJerUp;
	std::vector<float> BJetPtJerDown;
	std::vector<float> BJetEtaJerDown;
	std::vector<float> BJetPhiJerDown;
	std::vector<float> BJetEJerDown;
	
	std::vector<float> NonBJetPt;
	std::vector<float> NonBJetEta;
	std::vector<float> NonBJetPhi;
	std::vector<float> NonBJetE;
	std::vector<float> NonBJetCSVv2;
	std::vector<float> NonBJetCharge;
	std::vector<float> NonBJetChargeVec;
	std::vector<float> NonBJetCharmCvsL;
	std::vector<float> NonBJetCharmCvsB;
	std::vector<float> NonBJetPtJesUp;
	std::vector<float> NonBJetEtaJesUp;
	std::vector<float> NonBJetPhiJesUp;
	std::vector<float> NonBJetEJesUp;
	std::vector<float> NonBJetPtJesDown;
	std::vector<float> NonBJetEtaJesDown;
	std::vector<float> NonBJetPhiJesDown;
	std::vector<float> NonBJetEJesDown;
	std::vector<float> NonBJetPtJerUp;
	std::vector<float> NonBJetEtaJerUp;
	std::vector<float> NonBJetPhiJerUp;
	std::vector<float> NonBJetEJerUp;
	std::vector<float> NonBJetPtJerDown;
	std::vector<float> NonBJetEtaJerDown;
	std::vector<float> NonBJetPhiJerDown;
	std::vector<float> NonBJetEJerDown;
	
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
	     float pt = _v_BJetTight->at(i).pt();
	     float eta = _v_BJetTight->at(i).eta();
	     float phi = _v_BJetTight->at(i).phi();
	     float E = _v_BJetTight->at(i).E();
	     float CSVv2 = _v_BJetTight->at(i).CSVv2();
	     float charge = _v_BJetTight->at(i).charge();
	     float chargeVec = _v_BJetTight->at(i).chargeVec();
	     float CharmCvsL = _v_BJetTight->at(i).CharmCvsL();
	     float CharmCvsB = _v_BJetTight->at(i).CharmCvsB();
	     float ptJesUp = _v_BJetTight->at(i).p4_jesTotalUp().Pt();
	     float etaJesUp = _v_BJetTight->at(i).p4_jesTotalUp().PseudoRapidity();
	     float phiJesUp = _v_BJetTight->at(i).p4_jesTotalUp().Phi();
	     float EJesUp = _v_BJetTight->at(i).p4_jesTotalUp().E();
	     float ptJesDown = _v_BJetTight->at(i).p4_jesTotalDown().Pt();
	     float etaJesDown = _v_BJetTight->at(i).p4_jesTotalDown().PseudoRapidity();
	     float phiJesDown = _v_BJetTight->at(i).p4_jesTotalDown().Phi();
	     float EJesDown = _v_BJetTight->at(i).p4_jesTotalDown().E();
	     float ptJerUp = _v_BJetTight->at(i).p4_jerTotalUp().Pt();
	     float etaJerUp = _v_BJetTight->at(i).p4_jerTotalUp().PseudoRapidity();
	     float phiJerUp = _v_BJetTight->at(i).p4_jerTotalUp().Phi();
	     float EJerUp = _v_BJetTight->at(i).p4_jerTotalUp().E();
	     float ptJerDown = _v_BJetTight->at(i).p4_jerTotalDown().Pt();
	     float etaJerDown = _v_BJetTight->at(i).p4_jerTotalDown().PseudoRapidity();
	     float phiJerDown = _v_BJetTight->at(i).p4_jerTotalDown().Phi();
	     float EJerDown = _v_BJetTight->at(i).p4_jerTotalDown().E();

	     if( (nbjets <= 2) ||
		 (nbjets >= 3 && nnonbjets == 1 && i < 2) ||
		 (nbjets >= 3 && nnonbjets >= 2 ) ||
		 (nbjets >= 4 && nnonbjets == 0 && i < 2) ||
		 (nbjets >= 4 && nnonbjets >= 1 && i < 3) ||
		 (nbjets >= 4 && nnonbjets >= 2 ) )
	       {		  
		  BJetPt.push_back(pt);
		  BJetEta.push_back(eta);
		  BJetPhi.push_back(phi);
		  BJetE.push_back(E);
		  BJetCSVv2.push_back(CSVv2);
		  BJetCharge.push_back(charge);
		  BJetChargeVec.push_back(chargeVec);
		  BJetCharmCvsL.push_back(CharmCvsL);
		  BJetCharmCvsB.push_back(CharmCvsB);
		  BJetPtJesUp.push_back(ptJesUp);
		  BJetEtaJesUp.push_back(etaJesUp);
		  BJetPhiJesUp.push_back(phiJesUp);
		  BJetEJesUp.push_back(EJesUp);
		  BJetPtJesDown.push_back(ptJesDown);
		  BJetEtaJesDown.push_back(etaJesDown);
		  BJetPhiJesDown.push_back(phiJesDown);
		  BJetEJesDown.push_back(EJesDown);
		  BJetPtJerUp.push_back(ptJerUp);
		  BJetEtaJerUp.push_back(etaJerUp);
		  BJetPhiJerUp.push_back(phiJerUp);
		  BJetEJerUp.push_back(EJerUp);
		  BJetPtJerDown.push_back(ptJerDown);
		  BJetEtaJerDown.push_back(etaJerDown);
		  BJetPhiJerDown.push_back(phiJerDown);
		  BJetEJerDown.push_back(EJerDown);
	       }
	     else
	       {
		  NonBJetPt.push_back(pt);
		  NonBJetEta.push_back(eta);
		  NonBJetPhi.push_back(phi);
		  NonBJetE.push_back(E);
		  NonBJetCSVv2.push_back(CSVv2);
		  NonBJetCharge.push_back(charge);
		  NonBJetChargeVec.push_back(chargeVec);
		  NonBJetCharmCvsL.push_back(CharmCvsL);
		  NonBJetCharmCvsB.push_back(CharmCvsB);
		  NonBJetPtJesUp.push_back(ptJesUp);
		  NonBJetEtaJesUp.push_back(etaJesUp);
		  NonBJetPhiJesUp.push_back(phiJesUp);
		  NonBJetEJesUp.push_back(EJesUp);
		  NonBJetPtJesDown.push_back(ptJesDown);
		  NonBJetEtaJesDown.push_back(etaJesDown);
		  NonBJetPhiJesDown.push_back(phiJesDown);
		  NonBJetEJesDown.push_back(EJesDown);
		  NonBJetPtJerUp.push_back(ptJerUp);
		  NonBJetEtaJerUp.push_back(etaJerUp);
		  NonBJetPhiJerUp.push_back(phiJerUp);
		  NonBJetEJerUp.push_back(EJerUp);
		  NonBJetPtJerDown.push_back(ptJerDown);
		  NonBJetEtaJerDown.push_back(etaJerDown);
		  NonBJetPhiJerDown.push_back(phiJerDown);
		  NonBJetEJerDown.push_back(EJerDown);
	       }	     
	  }   
	     
	for(int i=0;i<_v_NonBJetTight->size();i++)
	  {
	     float pt = _v_NonBJetTight->at(i).pt();
	     float eta = _v_NonBJetTight->at(i).eta();
	     float phi = _v_NonBJetTight->at(i).phi();
	     float E = _v_NonBJetTight->at(i).E();
	     float CSVv2 = _v_NonBJetTight->at(i).CSVv2();
	     float charge = _v_NonBJetTight->at(i).charge();
	     float chargeVec = _v_NonBJetTight->at(i).chargeVec();
	     float CharmCvsL = _v_NonBJetTight->at(i).CharmCvsL();
	     float CharmCvsB = _v_NonBJetTight->at(i).CharmCvsB();
	     float ptJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().Pt();
	     float etaJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().PseudoRapidity();
	     float phiJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().Phi();
	     float EJesUp = _v_NonBJetTight->at(i).p4_jesTotalUp().E();
	     float ptJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().Pt();
	     float etaJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().PseudoRapidity();
	     float phiJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().Phi();
	     float EJesDown = _v_NonBJetTight->at(i).p4_jesTotalDown().E();
	     float ptJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().Pt();
	     float etaJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().PseudoRapidity();
	     float phiJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().Phi();
	     float EJerUp = _v_NonBJetTight->at(i).p4_jerTotalUp().E();
	     float ptJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().Pt();
	     float etaJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().PseudoRapidity();
	     float phiJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().Phi();
	     float EJerDown = _v_NonBJetTight->at(i).p4_jerTotalDown().E();

	     if( (nbjets == 0 && i < 2) ||
		 (nbjets == 1 && i < 1) )
	       {		  
		  BJetPt.push_back(pt);
		  BJetEta.push_back(eta);
		  BJetPhi.push_back(phi);
		  BJetE.push_back(E);
		  BJetCSVv2.push_back(CSVv2);
		  BJetCharge.push_back(charge);
		  BJetChargeVec.push_back(chargeVec);
		  BJetCharmCvsL.push_back(CharmCvsL);
		  BJetCharmCvsB.push_back(CharmCvsB);
		  BJetPtJesUp.push_back(ptJesUp);
		  BJetEtaJesUp.push_back(etaJesUp);
		  BJetPhiJesUp.push_back(phiJesUp);
		  BJetEJesUp.push_back(EJesUp);
		  BJetPtJesDown.push_back(ptJesDown);
		  BJetEtaJesDown.push_back(etaJesDown);
		  BJetPhiJesDown.push_back(phiJesDown);
		  BJetEJesDown.push_back(EJesDown);
		  BJetPtJerUp.push_back(ptJerUp);
		  BJetEtaJerUp.push_back(etaJerUp);
		  BJetPhiJerUp.push_back(phiJerUp);
		  BJetEJerUp.push_back(EJerUp);
		  BJetPtJerDown.push_back(ptJerDown);
		  BJetEtaJerDown.push_back(etaJerDown);
		  BJetPhiJerDown.push_back(phiJerDown);
		  BJetEJerDown.push_back(EJerDown);
	       }
	     else
	       {		  
		  NonBJetPt.push_back(pt);
		  NonBJetEta.push_back(eta);
		  NonBJetPhi.push_back(phi);
		  NonBJetE.push_back(E);
		  NonBJetCSVv2.push_back(CSVv2);
		  NonBJetCharge.push_back(charge);
		  NonBJetChargeVec.push_back(chargeVec);
		  NonBJetCharmCvsL.push_back(CharmCvsL);
		  NonBJetCharmCvsB.push_back(CharmCvsB);
		  NonBJetPtJesUp.push_back(ptJesUp);
		  NonBJetEtaJesUp.push_back(etaJesUp);
		  NonBJetPhiJesUp.push_back(phiJesUp);
		  NonBJetEJesUp.push_back(EJesUp);
		  NonBJetPtJesDown.push_back(ptJesDown);
		  NonBJetEtaJesDown.push_back(etaJesDown);
		  NonBJetPhiJesDown.push_back(phiJesDown);
		  NonBJetEJesDown.push_back(EJesDown);
		  NonBJetPtJerUp.push_back(ptJerUp);
		  NonBJetEtaJerUp.push_back(etaJerUp);
		  NonBJetPhiJerUp.push_back(phiJerUp);
		  NonBJetEJerUp.push_back(EJerUp);
		  NonBJetPtJerDown.push_back(ptJerDown);
		  NonBJetEtaJerDown.push_back(etaJerDown);
		  NonBJetPhiJerDown.push_back(phiJerDown);
		  NonBJetEJerDown.push_back(EJerDown);
	       }	     
	  }   
	
	kfTopTopLepHad->SetBJet(BJetPt,BJetEta,BJetPhi,BJetE);
	kfTopTopLepHad->SetNonBJet(NonBJetPt,NonBJetEta,NonBJetPhi,NonBJetE);
	kfTopTopLepHad->SetElectron(ElectronPt,ElectronEta,ElectronPhi,ElectronE);
	kfTopTopLepHad->SetMuon(MuonPt,MuonEta,MuonPhi,MuonE);
	kfTopTopLepHad->SetMet(metpx,metpy);
	
	kfTopTopLepHad->Run();

	std::vector<std::pair<float,int> > MVADisc;
	std::vector<std::pair<float,int> > MVADiscJesUp;
	std::vector<std::pair<float,int> > MVADiscJesDown;
	std::vector<std::pair<float,int> > MVADiscJerUp;
	std::vector<std::pair<float,int> > MVADiscJerDown;
	
	int nPerm = kfTopTopLepHad->GetNPerm();
	
	for(int ip=0;ip<nPerm;ip++)
	  {
	     float disc = kfTopTopLepHad->GetDisc(ip);

	     int idx_ELECTRON_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(ELECTRON_TOPTOPLEPHAD,ip);
	     int idx_MUON_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(MUON_TOPTOPLEPHAD,ip);
	     int idx_BJETLEP_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(BJETLEP_TOPTOPLEPHAD,ip);
	     int idx_BJETHAD_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(BJETHAD_TOPTOPLEPHAD,ip);
	     int idx_NONBJET1_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(NONBJET1_TOPTOPLEPHAD,ip);
	     int idx_NONBJET2_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(NONBJET2_TOPTOPLEPHAD,ip);

	     float NuPx = kfTopTopLepHad->GetNuPx(ip,0);
	     float NuPy = kfTopTopLepHad->GetNuPy(ip,0);
	     float NuPz = kfTopTopLepHad->GetNuPz(ip,0);
	     float NuE = sqrt(NuPx*NuPx+NuPy*NuPy+NuPz*NuPz);

	     TLorentzVector *TopLepWNu_p4 = new TLorentzVector();
	     TopLepWNu_p4->SetPxPyPzE(NuPx,NuPy,NuPz,NuE);
	     
	     TLorentzVector *TopHadWNonBJet1_p4 = new TLorentzVector();
	     TopHadWNonBJet1_p4->SetPtEtaPhiE(NonBJetPt[idx_NONBJET1_TOPTOPLEPHAD],
					      NonBJetEta[idx_NONBJET1_TOPTOPLEPHAD],
					      NonBJetPhi[idx_NONBJET1_TOPTOPLEPHAD],
					      NonBJetE[idx_NONBJET1_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadWNonBJet1JesUp_p4 = new TLorentzVector();
	     TopHadWNonBJet1JesUp_p4->SetPtEtaPhiE(NonBJetPtJesUp[idx_NONBJET1_TOPTOPLEPHAD],
						   NonBJetEtaJesUp[idx_NONBJET1_TOPTOPLEPHAD],
						   NonBJetPhiJesUp[idx_NONBJET1_TOPTOPLEPHAD],
						   NonBJetEJesUp[idx_NONBJET1_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadWNonBJet1JesDown_p4 = new TLorentzVector();
	     TopHadWNonBJet1JesDown_p4->SetPtEtaPhiE(NonBJetPtJesDown[idx_NONBJET1_TOPTOPLEPHAD],
						     NonBJetEtaJesDown[idx_NONBJET1_TOPTOPLEPHAD],
						     NonBJetPhiJesDown[idx_NONBJET1_TOPTOPLEPHAD],
						     NonBJetEJesDown[idx_NONBJET1_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadWNonBJet1JerUp_p4 = new TLorentzVector();
	     TopHadWNonBJet1JerUp_p4->SetPtEtaPhiE(NonBJetPtJerUp[idx_NONBJET1_TOPTOPLEPHAD],
						   NonBJetEtaJerUp[idx_NONBJET1_TOPTOPLEPHAD],
						   NonBJetPhiJerUp[idx_NONBJET1_TOPTOPLEPHAD],
						   NonBJetEJerUp[idx_NONBJET1_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadWNonBJet1JerDown_p4 = new TLorentzVector();
	     TopHadWNonBJet1JerDown_p4->SetPtEtaPhiE(NonBJetPtJerDown[idx_NONBJET1_TOPTOPLEPHAD],
						     NonBJetEtaJerDown[idx_NONBJET1_TOPTOPLEPHAD],
						     NonBJetPhiJerDown[idx_NONBJET1_TOPTOPLEPHAD],
						     NonBJetEJerDown[idx_NONBJET1_TOPTOPLEPHAD]);
	     
	     TLorentzVector *TopHadWNonBJet2_p4 = new TLorentzVector();
	     TopHadWNonBJet2_p4->SetPtEtaPhiE(NonBJetPt[idx_NONBJET2_TOPTOPLEPHAD],
					      NonBJetEta[idx_NONBJET2_TOPTOPLEPHAD],
					      NonBJetPhi[idx_NONBJET2_TOPTOPLEPHAD],
					      NonBJetE[idx_NONBJET2_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadWNonBJet2JesUp_p4 = new TLorentzVector();
	     TopHadWNonBJet2JesUp_p4->SetPtEtaPhiE(NonBJetPtJesUp[idx_NONBJET2_TOPTOPLEPHAD],
						   NonBJetEtaJesUp[idx_NONBJET2_TOPTOPLEPHAD],
						   NonBJetPhiJesUp[idx_NONBJET2_TOPTOPLEPHAD],
						   NonBJetEJesUp[idx_NONBJET2_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadWNonBJet2JesDown_p4 = new TLorentzVector();
	     TopHadWNonBJet2JesDown_p4->SetPtEtaPhiE(NonBJetPtJesDown[idx_NONBJET2_TOPTOPLEPHAD],
						     NonBJetEtaJesDown[idx_NONBJET2_TOPTOPLEPHAD],
						     NonBJetPhiJesDown[idx_NONBJET2_TOPTOPLEPHAD],
						     NonBJetEJesDown[idx_NONBJET2_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadWNonBJet2JerUp_p4 = new TLorentzVector();
	     TopHadWNonBJet2JerUp_p4->SetPtEtaPhiE(NonBJetPtJerUp[idx_NONBJET2_TOPTOPLEPHAD],
						   NonBJetEtaJerUp[idx_NONBJET2_TOPTOPLEPHAD],
						   NonBJetPhiJerUp[idx_NONBJET2_TOPTOPLEPHAD],
						   NonBJetEJerUp[idx_NONBJET2_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadWNonBJet2JerDown_p4 = new TLorentzVector();
	     TopHadWNonBJet2JerDown_p4->SetPtEtaPhiE(NonBJetPtJerDown[idx_NONBJET2_TOPTOPLEPHAD],
						     NonBJetEtaJerDown[idx_NONBJET2_TOPTOPLEPHAD],
						     NonBJetPhiJerDown[idx_NONBJET2_TOPTOPLEPHAD],
						     NonBJetEJerDown[idx_NONBJET2_TOPTOPLEPHAD]);
	     
	     TLorentzVector *TopLepBJet_p4 = new TLorentzVector();
	     TopLepBJet_p4->SetPtEtaPhiE(BJetPt[idx_BJETLEP_TOPTOPLEPHAD],
					 BJetEta[idx_BJETLEP_TOPTOPLEPHAD],
					 BJetPhi[idx_BJETLEP_TOPTOPLEPHAD],
					 BJetE[idx_BJETLEP_TOPTOPLEPHAD]);
	     TLorentzVector *TopLepBJetJesUp_p4 = new TLorentzVector();
	     TopLepBJetJesUp_p4->SetPtEtaPhiE(BJetPtJesUp[idx_BJETLEP_TOPTOPLEPHAD],
					      BJetEtaJesUp[idx_BJETLEP_TOPTOPLEPHAD],
					      BJetPhiJesUp[idx_BJETLEP_TOPTOPLEPHAD],
					      BJetEJesUp[idx_BJETLEP_TOPTOPLEPHAD]);
	     TLorentzVector *TopLepBJetJesDown_p4 = new TLorentzVector();
	     TopLepBJetJesDown_p4->SetPtEtaPhiE(BJetPtJesDown[idx_BJETLEP_TOPTOPLEPHAD],
						BJetEtaJesDown[idx_BJETLEP_TOPTOPLEPHAD],
						BJetPhiJesDown[idx_BJETLEP_TOPTOPLEPHAD],
						BJetEJesDown[idx_BJETLEP_TOPTOPLEPHAD]);
	     TLorentzVector *TopLepBJetJerUp_p4 = new TLorentzVector();
	     TopLepBJetJerUp_p4->SetPtEtaPhiE(BJetPtJerUp[idx_BJETLEP_TOPTOPLEPHAD],
					      BJetEtaJerUp[idx_BJETLEP_TOPTOPLEPHAD],
					      BJetPhiJerUp[idx_BJETLEP_TOPTOPLEPHAD],
					      BJetEJerUp[idx_BJETLEP_TOPTOPLEPHAD]);
	     TLorentzVector *TopLepBJetJerDown_p4 = new TLorentzVector();
	     TopLepBJetJerDown_p4->SetPtEtaPhiE(BJetPtJerDown[idx_BJETLEP_TOPTOPLEPHAD],
						BJetEtaJerDown[idx_BJETLEP_TOPTOPLEPHAD],
						BJetPhiJerDown[idx_BJETLEP_TOPTOPLEPHAD],
						BJetEJerDown[idx_BJETLEP_TOPTOPLEPHAD]);
	     
	     TLorentzVector *TopHadBJet_p4 = new TLorentzVector();
	     TopHadBJet_p4->SetPtEtaPhiE(BJetPt[idx_BJETHAD_TOPTOPLEPHAD],
					 BJetEta[idx_BJETHAD_TOPTOPLEPHAD],
					 BJetPhi[idx_BJETHAD_TOPTOPLEPHAD],
					 BJetE[idx_BJETHAD_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadBJetJesUp_p4 = new TLorentzVector();
	     TopHadBJetJesUp_p4->SetPtEtaPhiE(BJetPtJesUp[idx_BJETHAD_TOPTOPLEPHAD],
					      BJetEtaJesUp[idx_BJETHAD_TOPTOPLEPHAD],
					      BJetPhiJesUp[idx_BJETHAD_TOPTOPLEPHAD],
					      BJetEJesUp[idx_BJETHAD_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadBJetJesDown_p4 = new TLorentzVector();
	     TopHadBJetJesDown_p4->SetPtEtaPhiE(BJetPtJesDown[idx_BJETHAD_TOPTOPLEPHAD],
						BJetEtaJesDown[idx_BJETHAD_TOPTOPLEPHAD],
						BJetPhiJesDown[idx_BJETHAD_TOPTOPLEPHAD],
						BJetEJesDown[idx_BJETHAD_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadBJetJerUp_p4 = new TLorentzVector();
	     TopHadBJetJerUp_p4->SetPtEtaPhiE(BJetPtJerUp[idx_BJETHAD_TOPTOPLEPHAD],
					      BJetEtaJerUp[idx_BJETHAD_TOPTOPLEPHAD],
					      BJetPhiJerUp[idx_BJETHAD_TOPTOPLEPHAD],
					      BJetEJerUp[idx_BJETHAD_TOPTOPLEPHAD]);
	     TLorentzVector *TopHadBJetJerDown_p4 = new TLorentzVector();
	     TopHadBJetJerDown_p4->SetPtEtaPhiE(BJetPtJerDown[idx_BJETHAD_TOPTOPLEPHAD],
						BJetEtaJerDown[idx_BJETHAD_TOPTOPLEPHAD],
						BJetPhiJerDown[idx_BJETHAD_TOPTOPLEPHAD],
						BJetEJerDown[idx_BJETHAD_TOPTOPLEPHAD]);
	     
	     TLorentzVector *TopLepWLep_p4 = new TLorentzVector();
	     if( idx_ELECTRON_TOPTOPLEPHAD >= 0 )
	       TopLepWLep_p4->SetPtEtaPhiE(ElectronPt[idx_ELECTRON_TOPTOPLEPHAD],
					   ElectronEta[idx_ELECTRON_TOPTOPLEPHAD],
					   ElectronPhi[idx_ELECTRON_TOPTOPLEPHAD],
					   ElectronE[idx_ELECTRON_TOPTOPLEPHAD]);
	     else
	       TopLepWLep_p4->SetPtEtaPhiE(MuonPt[idx_MUON_TOPTOPLEPHAD],
					   MuonEta[idx_MUON_TOPTOPLEPHAD],
					   MuonPhi[idx_MUON_TOPTOPLEPHAD],
					   MuonE[idx_MUON_TOPTOPLEPHAD]);
	     
	     TLorentzVector TopHadW_p4 = *TopHadWNonBJet1_p4+*TopHadWNonBJet2_p4;
	     TLorentzVector TopHadWJesUp_p4 = *TopHadWNonBJet1JesUp_p4+*TopHadWNonBJet2JesUp_p4;
	     TLorentzVector TopHadWJesDown_p4 = *TopHadWNonBJet1JesDown_p4+*TopHadWNonBJet2JesDown_p4;
	     TLorentzVector TopHadWJerUp_p4 = *TopHadWNonBJet1JerUp_p4+*TopHadWNonBJet2JerUp_p4;
	     TLorentzVector TopHadWJerDown_p4 = *TopHadWNonBJet1JerDown_p4+*TopHadWNonBJet2JerDown_p4;
	     
	     TLorentzVector TopLepW_p4 = *TopLepWLep_p4+*TopLepWNu_p4;
	     
	     TLorentzVector TopLep_p4 = TopLepW_p4+*TopLepBJet_p4;
	     TLorentzVector TopLepJesUp_p4 = TopLepW_p4+*TopLepBJetJesUp_p4;
	     TLorentzVector TopLepJesDown_p4 = TopLepW_p4+*TopLepBJetJesDown_p4;
	     TLorentzVector TopLepJerUp_p4 = TopLepW_p4+*TopLepBJetJerUp_p4;
	     TLorentzVector TopLepJerDown_p4 = TopLepW_p4+*TopLepBJetJerDown_p4;
	     
	     TLorentzVector TopHad_p4 = TopHadW_p4+*TopHadBJet_p4;
	     TLorentzVector TopHadJesUp_p4 = TopHadWJesUp_p4+*TopHadBJetJesUp_p4;
	     TLorentzVector TopHadJesDown_p4 = TopHadWJesDown_p4+*TopHadBJetJesDown_p4;
	     TLorentzVector TopHadJerUp_p4 = TopHadWJerUp_p4+*TopHadBJetJerUp_p4;
	     TLorentzVector TopHadJerDown_p4 = TopHadWJerDown_p4+*TopHadBJetJerDown_p4;

	     float VarTopHadRecM = TopHad_p4.M();
	     float VarTopHadRecMJesUp = TopHadJesUp_p4.M();
	     float VarTopHadRecMJesDown = TopHadJesDown_p4.M();
	     float VarTopHadRecMJerUp = TopHadJerUp_p4.M();
	     float VarTopHadRecMJerDown = TopHadJerDown_p4.M();
	     
	     float VarTopLepRecM = TopLep_p4.M();
	     float VarTopLepRecMJesUp = TopLepJesUp_p4.M();
	     float VarTopLepRecMJesDown = TopLepJesDown_p4.M();
	     float VarTopLepRecMJerUp = TopLepJerUp_p4.M();
	     float VarTopLepRecMJerDown = TopLepJerDown_p4.M();
	     
	     float VarTopLepTopHadRecDr = TopLep_p4.DeltaR(TopHad_p4);
	     float VarTopLepTopHadRecDrJesUp = TopLepJesUp_p4.DeltaR(TopHadJesUp_p4);
	     float VarTopLepTopHadRecDrJesDown = TopLepJesDown_p4.DeltaR(TopHadJesDown_p4);
	     float VarTopLepTopHadRecDrJerUp = TopLepJerUp_p4.DeltaR(TopHadJerUp_p4);
	     float VarTopLepTopHadRecDrJerDown = TopLepJerDown_p4.DeltaR(TopHadJerDown_p4);
	     
	     float VarTopLepRecPt = TopLep_p4.Pt();
	     float VarTopLepRecPtJesUp = TopLepJesUp_p4.Pt();
	     float VarTopLepRecPtJesDown = TopLepJesDown_p4.Pt();
	     float VarTopLepRecPtJerUp = TopLepJerUp_p4.Pt();
	     float VarTopLepRecPtJerDown = TopLepJerDown_p4.Pt();
	     
	     TLorentzVector *TopHadT_p4 = new TLorentzVector();
	     TopHadT_p4->SetPxPyPzE(TopHad_p4.Px(),TopHad_p4.Py(),0.,TopHad_p4.Et());
	     TLorentzVector *TopHadTJesUp_p4 = new TLorentzVector();
	     TopHadTJesUp_p4->SetPxPyPzE(TopHadJesUp_p4.Px(),TopHadJesUp_p4.Py(),0.,TopHadJesUp_p4.Et());
	     TLorentzVector *TopHadTJesDown_p4 = new TLorentzVector();
	     TopHadTJesDown_p4->SetPxPyPzE(TopHadJesDown_p4.Px(),TopHadJesDown_p4.Py(),0.,TopHadJesDown_p4.Et());
	     TLorentzVector *TopHadTJerUp_p4 = new TLorentzVector();
	     TopHadTJerUp_p4->SetPxPyPzE(TopHadJerUp_p4.Px(),TopHadJerUp_p4.Py(),0.,TopHadJerUp_p4.Et());
	     TLorentzVector *TopHadTJerDown_p4 = new TLorentzVector();
	     TopHadTJerDown_p4->SetPxPyPzE(TopHadJerDown_p4.Px(),TopHadJerDown_p4.Py(),0.,TopHadJerDown_p4.Et());
	     
	     TLorentzVector *TopLepWLepT_p4 = new TLorentzVector();
	     TopLepWLepT_p4->SetPxPyPzE(TopLepWLep_p4->Px(),TopLepWLep_p4->Py(),0.,TopLepWLep_p4->Et());
	     
	     TLorentzVector *TopLepWNuT_p4 = new TLorentzVector();
	     TopLepWNuT_p4->SetPxPyPzE(TopLepWNu_p4->Px(),TopLepWNu_p4->Py(),0.,TopLepWNu_p4->Et());
	     
	     TLorentzVector *TopLepBJetT_p4 = new TLorentzVector();
	     TopLepBJetT_p4->SetPxPyPzE(TopLepBJet_p4->Px(),TopLepBJet_p4->Py(),0.,TopLepBJet_p4->Et());
	     TLorentzVector *TopLepBJetTJesUp_p4 = new TLorentzVector();
	     TopLepBJetTJesUp_p4->SetPxPyPzE(TopLepBJetJesUp_p4->Px(),TopLepBJetJesUp_p4->Py(),0.,TopLepBJetJesUp_p4->Et());
	     TLorentzVector *TopLepBJetTJesDown_p4 = new TLorentzVector();
	     TopLepBJetTJesDown_p4->SetPxPyPzE(TopLepBJetJesDown_p4->Px(),TopLepBJetJesDown_p4->Py(),0.,TopLepBJetJesDown_p4->Et());
	     TLorentzVector *TopLepBJetTJerUp_p4 = new TLorentzVector();
	     TopLepBJetTJerUp_p4->SetPxPyPzE(TopLepBJetJerUp_p4->Px(),TopLepBJetJerUp_p4->Py(),0.,TopLepBJetJerUp_p4->Et());
	     TLorentzVector *TopLepBJetTJerDown_p4 = new TLorentzVector();
	     TopLepBJetTJerDown_p4->SetPxPyPzE(TopLepBJetJerDown_p4->Px(),TopLepBJetJerDown_p4->Py(),0.,TopLepBJetJerDown_p4->Et());
	     
	     TLorentzVector TopLepT_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetT_p4;
	     TLorentzVector TopLepTJesUp_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJesUp_p4;
	     TLorentzVector TopLepTJesDown_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJesDown_p4;
	     TLorentzVector TopLepTJerUp_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJerUp_p4;
	     TLorentzVector TopLepTJerDown_p4 = *TopLepWLepT_p4+*TopLepWNuT_p4+*TopLepBJetTJerDown_p4;
	     
	     float VarTopLepRecMT = TopLepT_p4.M();
	     float VarTopLepRecMTJesUp = TopLepTJesUp_p4.M();
	     float VarTopLepRecMTJesDown = TopLepTJesDown_p4.M();
	     float VarTopLepRecMTJerUp = TopLepTJerUp_p4.M();
	     float VarTopLepRecMTJerDown = TopLepTJerDown_p4.M();
	     
	     float VarTopLepTopHadRecDphiT = TopLepT_p4.DeltaPhi(*TopHadT_p4);
	     float VarTopLepTopHadRecDphiTJesUp = TopLepTJesUp_p4.DeltaPhi(*TopHadTJesUp_p4);
	     float VarTopLepTopHadRecDphiTJesDown = TopLepTJesDown_p4.DeltaPhi(*TopHadTJesDown_p4);
	     float VarTopLepTopHadRecDphiTJerUp = TopLepTJerUp_p4.DeltaPhi(*TopHadTJerUp_p4);
	     float VarTopLepTopHadRecDphiTJerDown = TopLepTJerDown_p4.DeltaPhi(*TopHadTJerDown_p4);
	     
	     float VarTopLepRecPtT = TopLepT_p4.Pt();
	     float VarTopLepRecPtTJesUp = TopLepTJesUp_p4.Pt();
	     float VarTopLepRecPtTJesDown = TopLepTJesDown_p4.Pt();
	     float VarTopLepRecPtTJerUp = TopLepTJerUp_p4.Pt();
	     float VarTopLepRecPtTJerDown = TopLepTJerDown_p4.Pt();
	     
	     if( disc < 10E+8 )
	       {
		  MVAFullReco_TopHadRecM_TOPTOPLEPHAD = VarTopHadRecMJesUp;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHAD = VarTopLepRecMJesUp;
		  MVAFullReco_TopLepTopHadRecDr_TOPTOPLEPHAD = VarTopLepTopHadRecDrJesUp;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHAD = VarTopLepRecPtJesUp;
		  
		  MVADiscJesUp.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHAD->EvaluateMVA("BDTG method"),ip));

		  MVAFullReco_TopHadRecM_TOPTOPLEPHAD = VarTopHadRecMJesDown;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHAD = VarTopLepRecMJesDown;
		  MVAFullReco_TopLepTopHadRecDr_TOPTOPLEPHAD = VarTopLepTopHadRecDrJesDown;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHAD = VarTopLepRecPtJesDown;
		  
		  MVADiscJesDown.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHAD->EvaluateMVA("BDTG method"),ip));

		  MVAFullReco_TopHadRecM_TOPTOPLEPHAD = VarTopHadRecMJerUp;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHAD = VarTopLepRecMJerUp;
		  MVAFullReco_TopLepTopHadRecDr_TOPTOPLEPHAD = VarTopLepTopHadRecDrJerUp;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHAD = VarTopLepRecPtJerUp;
		  
		  MVADiscJerUp.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHAD->EvaluateMVA("BDTG method"),ip));

		  MVAFullReco_TopHadRecM_TOPTOPLEPHAD = VarTopHadRecMJerDown;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHAD = VarTopLepRecMJerDown;
		  MVAFullReco_TopLepTopHadRecDr_TOPTOPLEPHAD = VarTopLepTopHadRecDrJerDown;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHAD = VarTopLepRecPtJerDown;
		  
		  MVADiscJerDown.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHAD->EvaluateMVA("BDTG method"),ip));
		  
		  MVAFullReco_TopHadRecM_TOPTOPLEPHAD = VarTopHadRecM;
		  MVAFullReco_TopLepRecM_TOPTOPLEPHAD = VarTopLepRecM;
		  MVAFullReco_TopLepTopHadRecDr_TOPTOPLEPHAD = VarTopLepTopHadRecDr;
		  MVAFullReco_TopLepRecPt_TOPTOPLEPHAD = VarTopLepRecPt;
		  
		  MVADisc.push_back(std::make_pair(MVAFullRecoReaderTOPTOPLEPHAD->EvaluateMVA("BDTG method"),ip));
	       }	
	     else
	       {
		  MVAPartReco_TopHadRecM_TOPTOPLEPHAD = VarTopHadRecMJesUp;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHAD = VarTopLepRecMTJesUp;
		  MVAPartReco_TopLepTopHadRecDphiT_TOPTOPLEPHAD = VarTopLepTopHadRecDphiTJesUp;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHAD = VarTopLepRecPtTJesUp;
		  
		  MVADiscJesUp.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHAD->EvaluateMVA("BDTG method"),ip));

		  MVAPartReco_TopHadRecM_TOPTOPLEPHAD = VarTopHadRecMJesDown;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHAD = VarTopLepRecMTJesDown;
		  MVAPartReco_TopLepTopHadRecDphiT_TOPTOPLEPHAD = VarTopLepTopHadRecDphiTJesDown;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHAD = VarTopLepRecPtTJesDown;
		  
		  MVADiscJesDown.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHAD->EvaluateMVA("BDTG method"),ip));

		  MVAPartReco_TopHadRecM_TOPTOPLEPHAD = VarTopHadRecMJerUp;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHAD = VarTopLepRecMTJerUp;
		  MVAPartReco_TopLepTopHadRecDphiT_TOPTOPLEPHAD = VarTopLepTopHadRecDphiTJerUp;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHAD = VarTopLepRecPtTJerUp;
		  
		  MVADiscJerUp.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHAD->EvaluateMVA("BDTG method"),ip));

		  MVAPartReco_TopHadRecM_TOPTOPLEPHAD = VarTopHadRecMJerDown;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHAD = VarTopLepRecMTJerDown;
		  MVAPartReco_TopLepTopHadRecDphiT_TOPTOPLEPHAD = VarTopLepTopHadRecDphiTJerDown;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHAD = VarTopLepRecPtTJerDown;
		  
		  MVADiscJerDown.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHAD->EvaluateMVA("BDTG method"),ip));
		  
		  MVAPartReco_TopHadRecM_TOPTOPLEPHAD = VarTopHadRecM;
		  MVAPartReco_TopLepRecMT_TOPTOPLEPHAD = VarTopLepRecMT;
		  MVAPartReco_TopLepTopHadRecDphiT_TOPTOPLEPHAD = VarTopLepTopHadRecDphiT;
		  MVAPartReco_TopLepRecPtT_TOPTOPLEPHAD = VarTopLepRecPtT;
		  
		  MVADisc.push_back(std::make_pair(MVAPartRecoReaderTOPTOPLEPHAD->EvaluateMVA("BDTG method"),ip));
	       }	     

	     delete TopLepWNu_p4;
	     delete TopHadWNonBJet1_p4;
	     delete TopHadWNonBJet1JesUp_p4;
	     delete TopHadWNonBJet1JesDown_p4;
	     delete TopHadWNonBJet1JerUp_p4;
	     delete TopHadWNonBJet1JerDown_p4;	     
	     delete TopHadWNonBJet2_p4;
	     delete TopHadWNonBJet2JesUp_p4;
	     delete TopHadWNonBJet2JesDown_p4;
	     delete TopHadWNonBJet2JerUp_p4;
	     delete TopHadWNonBJet2JerDown_p4;
	     delete TopLepBJet_p4;
	     delete TopLepBJetJesUp_p4;
	     delete TopLepBJetJesDown_p4;
	     delete TopLepBJetJerUp_p4;
	     delete TopLepBJetJerDown_p4;
	     delete TopHadBJet_p4;
	     delete TopHadBJetJesUp_p4;
	     delete TopHadBJetJesDown_p4;
	     delete TopHadBJetJerUp_p4;
	     delete TopHadBJetJerDown_p4;
	     delete TopLepWLep_p4;
	     delete TopHadT_p4;
	     delete TopHadTJesUp_p4;
	     delete TopHadTJesDown_p4;
	     delete TopHadTJerUp_p4;
	     delete TopHadTJerDown_p4;
	     delete TopLepWLepT_p4;
	     delete TopLepWNuT_p4;
	     delete TopLepBJetT_p4;
	     delete TopLepBJetTJesUp_p4;
	     delete TopLepBJetTJesDown_p4;
	     delete TopLepBJetTJerUp_p4;
	     delete TopLepBJetTJerDown_p4;
	  }
	
	std::sort(MVADisc.begin(),MVADisc.end(),sortFunc());
	int IdxPerm = MVADisc.at(0).second;
	
	_chi2_TOPTOPLEPHAD = kfTopTopLepHad->GetDisc(IdxPerm);
	_MVA_TOPTOPLEPHAD = MVADisc.at(0).first;
	_MVAJesUp_TOPTOPLEPHAD = MVADiscJesUp.at(IdxPerm).first;
	_MVAJesDown_TOPTOPLEPHAD = MVADiscJesDown.at(IdxPerm).first;
	_MVAJerUp_TOPTOPLEPHAD = MVADiscJerUp.at(IdxPerm).first;
	_MVAJerDown_TOPTOPLEPHAD = MVADiscJerDown.at(IdxPerm).first;

	int idx_ELECTRON_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(ELECTRON_TOPTOPLEPHAD,IdxPerm);
	int idx_MUON_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(MUON_TOPTOPLEPHAD,IdxPerm);
	int idx_BJETLEP_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(BJETLEP_TOPTOPLEPHAD,IdxPerm);
	int idx_BJETHAD_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(BJETHAD_TOPTOPLEPHAD,IdxPerm);
	int idx_NONBJET1_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(NONBJET1_TOPTOPLEPHAD,IdxPerm);
	int idx_NONBJET2_TOPTOPLEPHAD = kfTopTopLepHad->GetIndex(NONBJET2_TOPTOPLEPHAD,IdxPerm);

	float NuPx = kfTopTopLepHad->GetNuPx(IdxPerm,0);
	float NuPy = kfTopTopLepHad->GetNuPy(IdxPerm,0);
	float NuPz = kfTopTopLepHad->GetNuPz(IdxPerm,0);
	float NuE = sqrt(NuPx*NuPx+NuPy*NuPy+NuPz*NuPz);

	_TopLepWNu_TOPTOPLEPHAD_p4.SetPxPyPzE(NuPx,NuPy,NuPz,NuE);

	_TopHadWNonBJet1_TOPTOPLEPHAD_p4.SetPtEtaPhiE(NonBJetPt[idx_NONBJET1_TOPTOPLEPHAD],
						      NonBJetEta[idx_NONBJET1_TOPTOPLEPHAD],
						      NonBJetPhi[idx_NONBJET1_TOPTOPLEPHAD],
						      NonBJetE[idx_NONBJET1_TOPTOPLEPHAD]);
	_TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(NonBJetPtJesUp[idx_NONBJET1_TOPTOPLEPHAD],
							    NonBJetEtaJesUp[idx_NONBJET1_TOPTOPLEPHAD],
							    NonBJetPhiJesUp[idx_NONBJET1_TOPTOPLEPHAD],
							    NonBJetEJesUp[idx_NONBJET1_TOPTOPLEPHAD]);
	_TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(NonBJetPtJesDown[idx_NONBJET1_TOPTOPLEPHAD],
							      NonBJetEtaJesDown[idx_NONBJET1_TOPTOPLEPHAD],
							      NonBJetPhiJesDown[idx_NONBJET1_TOPTOPLEPHAD],
							      NonBJetEJesDown[idx_NONBJET1_TOPTOPLEPHAD]);
	_TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(NonBJetPtJerUp[idx_NONBJET1_TOPTOPLEPHAD],
							    NonBJetEtaJerUp[idx_NONBJET1_TOPTOPLEPHAD],
							    NonBJetPhiJerUp[idx_NONBJET1_TOPTOPLEPHAD],
							    NonBJetEJerUp[idx_NONBJET1_TOPTOPLEPHAD]);
	_TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(NonBJetPtJerDown[idx_NONBJET1_TOPTOPLEPHAD],
							      NonBJetEtaJerDown[idx_NONBJET1_TOPTOPLEPHAD],
							      NonBJetPhiJerDown[idx_NONBJET1_TOPTOPLEPHAD],
							      NonBJetEJerDown[idx_NONBJET1_TOPTOPLEPHAD]);
	
	_TopHadWNonBJet2_TOPTOPLEPHAD_p4.SetPtEtaPhiE(NonBJetPt[idx_NONBJET2_TOPTOPLEPHAD],
						      NonBJetEta[idx_NONBJET2_TOPTOPLEPHAD],
						      NonBJetPhi[idx_NONBJET2_TOPTOPLEPHAD],
						      NonBJetE[idx_NONBJET2_TOPTOPLEPHAD]);
	_TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(NonBJetPtJesUp[idx_NONBJET2_TOPTOPLEPHAD],
							    NonBJetEtaJesUp[idx_NONBJET2_TOPTOPLEPHAD],
							    NonBJetPhiJesUp[idx_NONBJET2_TOPTOPLEPHAD],
							    NonBJetEJesUp[idx_NONBJET2_TOPTOPLEPHAD]);
	_TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(NonBJetPtJesDown[idx_NONBJET2_TOPTOPLEPHAD],
							      NonBJetEtaJesDown[idx_NONBJET2_TOPTOPLEPHAD],
							      NonBJetPhiJesDown[idx_NONBJET2_TOPTOPLEPHAD],
							      NonBJetEJesDown[idx_NONBJET2_TOPTOPLEPHAD]);
	_TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(NonBJetPtJerUp[idx_NONBJET2_TOPTOPLEPHAD],
							    NonBJetEtaJerUp[idx_NONBJET2_TOPTOPLEPHAD],
							    NonBJetPhiJerUp[idx_NONBJET2_TOPTOPLEPHAD],
							    NonBJetEJerUp[idx_NONBJET2_TOPTOPLEPHAD]);
	_TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(NonBJetPtJerDown[idx_NONBJET2_TOPTOPLEPHAD],
							      NonBJetEtaJerDown[idx_NONBJET2_TOPTOPLEPHAD],
							      NonBJetPhiJerDown[idx_NONBJET2_TOPTOPLEPHAD],
							      NonBJetEJerDown[idx_NONBJET2_TOPTOPLEPHAD]);
	
	_TopLepBJet_TOPTOPLEPHAD_p4.SetPtEtaPhiE(BJetPt[idx_BJETLEP_TOPTOPLEPHAD],
						 BJetEta[idx_BJETLEP_TOPTOPLEPHAD],
						 BJetPhi[idx_BJETLEP_TOPTOPLEPHAD],
						 BJetE[idx_BJETLEP_TOPTOPLEPHAD]);
	_TopLepBJet_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(BJetPtJesUp[idx_BJETLEP_TOPTOPLEPHAD],
						       BJetEtaJesUp[idx_BJETLEP_TOPTOPLEPHAD],
						       BJetPhiJesUp[idx_BJETLEP_TOPTOPLEPHAD],
						       BJetEJesUp[idx_BJETLEP_TOPTOPLEPHAD]);
	_TopLepBJet_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(BJetPtJesDown[idx_BJETLEP_TOPTOPLEPHAD],
							 BJetEtaJesDown[idx_BJETLEP_TOPTOPLEPHAD],
							 BJetPhiJesDown[idx_BJETLEP_TOPTOPLEPHAD],
							 BJetEJesDown[idx_BJETLEP_TOPTOPLEPHAD]);
	_TopLepBJet_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(BJetPtJerUp[idx_BJETLEP_TOPTOPLEPHAD],
						       BJetEtaJerUp[idx_BJETLEP_TOPTOPLEPHAD],
						       BJetPhiJerUp[idx_BJETLEP_TOPTOPLEPHAD],
						       BJetEJerUp[idx_BJETLEP_TOPTOPLEPHAD]);
	_TopLepBJet_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(BJetPtJerDown[idx_BJETLEP_TOPTOPLEPHAD],
							 BJetEtaJerDown[idx_BJETLEP_TOPTOPLEPHAD],
							 BJetPhiJerDown[idx_BJETLEP_TOPTOPLEPHAD],
							 BJetEJerDown[idx_BJETLEP_TOPTOPLEPHAD]);
	
	_TopHadBJet_TOPTOPLEPHAD_p4.SetPtEtaPhiE(BJetPt[idx_BJETHAD_TOPTOPLEPHAD],
						 BJetEta[idx_BJETHAD_TOPTOPLEPHAD],
						 BJetPhi[idx_BJETHAD_TOPTOPLEPHAD],
						 BJetE[idx_BJETHAD_TOPTOPLEPHAD]);
	_TopHadBJet_TOPTOPLEPHAD_JesUp_p4.SetPtEtaPhiE(BJetPtJesUp[idx_BJETHAD_TOPTOPLEPHAD],
						       BJetEtaJesUp[idx_BJETHAD_TOPTOPLEPHAD],
						       BJetPhiJesUp[idx_BJETHAD_TOPTOPLEPHAD],
						       BJetEJesUp[idx_BJETHAD_TOPTOPLEPHAD]);
	_TopHadBJet_TOPTOPLEPHAD_JesDown_p4.SetPtEtaPhiE(BJetPtJesDown[idx_BJETHAD_TOPTOPLEPHAD],
							 BJetEtaJesDown[idx_BJETHAD_TOPTOPLEPHAD],
							 BJetPhiJesDown[idx_BJETHAD_TOPTOPLEPHAD],
							 BJetEJesDown[idx_BJETHAD_TOPTOPLEPHAD]);
	_TopHadBJet_TOPTOPLEPHAD_JerUp_p4.SetPtEtaPhiE(BJetPtJerUp[idx_BJETHAD_TOPTOPLEPHAD],
						       BJetEtaJerUp[idx_BJETHAD_TOPTOPLEPHAD],
						       BJetPhiJerUp[idx_BJETHAD_TOPTOPLEPHAD],
						       BJetEJerUp[idx_BJETHAD_TOPTOPLEPHAD]);
	_TopHadBJet_TOPTOPLEPHAD_JerDown_p4.SetPtEtaPhiE(BJetPtJerDown[idx_BJETHAD_TOPTOPLEPHAD],
							 BJetEtaJerDown[idx_BJETHAD_TOPTOPLEPHAD],
							 BJetPhiJerDown[idx_BJETHAD_TOPTOPLEPHAD],
							 BJetEJerDown[idx_BJETHAD_TOPTOPLEPHAD]);
	
	if( idx_ELECTRON_TOPTOPLEPHAD >= 0 )
	  _TopLepWLep_TOPTOPLEPHAD_p4.SetPtEtaPhiE(ElectronPt[idx_ELECTRON_TOPTOPLEPHAD],
						   ElectronEta[idx_ELECTRON_TOPTOPLEPHAD],
						   ElectronPhi[idx_ELECTRON_TOPTOPLEPHAD],
						   ElectronE[idx_ELECTRON_TOPTOPLEPHAD]);
	else
	  _TopLepWLep_TOPTOPLEPHAD_p4.SetPtEtaPhiE(MuonPt[idx_MUON_TOPTOPLEPHAD],
						   MuonEta[idx_MUON_TOPTOPLEPHAD],
						   MuonPhi[idx_MUON_TOPTOPLEPHAD],
						   MuonE[idx_MUON_TOPTOPLEPHAD]);
		
	_TopHadW_TOPTOPLEPHAD_p4 = _TopHadWNonBJet1_TOPTOPLEPHAD_p4+_TopHadWNonBJet2_TOPTOPLEPHAD_p4;
	_TopHadW_TOPTOPLEPHAD_JesUp_p4 = _TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4+_TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4;
	_TopHadW_TOPTOPLEPHAD_JesDown_p4 = _TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4+_TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4;
	_TopHadW_TOPTOPLEPHAD_JerUp_p4 = _TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4+_TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4;
	_TopHadW_TOPTOPLEPHAD_JerDown_p4 = _TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4+_TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4;
	
	_TopLepW_TOPTOPLEPHAD_p4 = _TopLepWLep_TOPTOPLEPHAD_p4+_TopLepWNu_TOPTOPLEPHAD_p4;
	
	_TopLep_TOPTOPLEPHAD_p4 = _TopLepW_TOPTOPLEPHAD_p4+_TopLepBJet_TOPTOPLEPHAD_p4;
	_TopLep_TOPTOPLEPHAD_JesUp_p4 = _TopLepW_TOPTOPLEPHAD_p4+_TopLepBJet_TOPTOPLEPHAD_JesUp_p4;
	_TopLep_TOPTOPLEPHAD_JesDown_p4 = _TopLepW_TOPTOPLEPHAD_p4+_TopLepBJet_TOPTOPLEPHAD_JesDown_p4;
	_TopLep_TOPTOPLEPHAD_JerUp_p4 = _TopLepW_TOPTOPLEPHAD_p4+_TopLepBJet_TOPTOPLEPHAD_JerUp_p4;
	_TopLep_TOPTOPLEPHAD_JerDown_p4 = _TopLepW_TOPTOPLEPHAD_p4+_TopLepBJet_TOPTOPLEPHAD_JerDown_p4;
	
	_TopHad_TOPTOPLEPHAD_p4 = _TopHadW_TOPTOPLEPHAD_p4+_TopHadBJet_TOPTOPLEPHAD_p4;
	_TopHad_TOPTOPLEPHAD_JesUp_p4 = _TopHadW_TOPTOPLEPHAD_JesUp_p4+_TopHadBJet_TOPTOPLEPHAD_JesUp_p4;
	_TopHad_TOPTOPLEPHAD_JesDown_p4 = _TopHadW_TOPTOPLEPHAD_JesDown_p4+_TopHadBJet_TOPTOPLEPHAD_JesDown_p4;
	_TopHad_TOPTOPLEPHAD_JerUp_p4 = _TopHadW_TOPTOPLEPHAD_JerUp_p4+_TopHadBJet_TOPTOPLEPHAD_JerUp_p4;
	_TopHad_TOPTOPLEPHAD_JerDown_p4 = _TopHadW_TOPTOPLEPHAD_JerDown_p4+_TopHadBJet_TOPTOPLEPHAD_JerDown_p4;

	_TopLepBJet_TOPTOPLEPHAD_CSVv2 = BJetCSVv2[idx_BJETLEP_TOPTOPLEPHAD];
	_TopHadBJet_TOPTOPLEPHAD_CSVv2 = BJetCSVv2[idx_BJETHAD_TOPTOPLEPHAD];
	_TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2 = NonBJetCSVv2[idx_NONBJET1_TOPTOPLEPHAD];
	_TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2 = NonBJetCSVv2[idx_NONBJET2_TOPTOPLEPHAD];

	_TopLepBJet_TOPTOPLEPHAD_charge = BJetCharge[idx_BJETLEP_TOPTOPLEPHAD];
	_TopHadBJet_TOPTOPLEPHAD_charge = BJetCharge[idx_BJETHAD_TOPTOPLEPHAD];
	_TopHadWNonBJet1_TOPTOPLEPHAD_charge = NonBJetCharge[idx_NONBJET1_TOPTOPLEPHAD];
	_TopHadWNonBJet2_TOPTOPLEPHAD_charge = NonBJetCharge[idx_NONBJET2_TOPTOPLEPHAD];

	_TopLepBJet_TOPTOPLEPHAD_chargeVec = BJetChargeVec[idx_BJETLEP_TOPTOPLEPHAD];
	_TopHadBJet_TOPTOPLEPHAD_chargeVec = BJetChargeVec[idx_BJETHAD_TOPTOPLEPHAD];
	_TopHadWNonBJet1_TOPTOPLEPHAD_chargeVec = NonBJetChargeVec[idx_NONBJET1_TOPTOPLEPHAD];
	_TopHadWNonBJet2_TOPTOPLEPHAD_chargeVec = NonBJetChargeVec[idx_NONBJET2_TOPTOPLEPHAD];

	_TopLepBJet_TOPTOPLEPHAD_CharmCvsL = BJetCharmCvsL[idx_BJETLEP_TOPTOPLEPHAD];
	_TopHadBJet_TOPTOPLEPHAD_CharmCvsL = BJetCharmCvsL[idx_BJETHAD_TOPTOPLEPHAD];
	_TopHadWNonBJet1_TOPTOPLEPHAD_CharmCvsL = NonBJetCharmCvsL[idx_NONBJET1_TOPTOPLEPHAD];
	_TopHadWNonBJet2_TOPTOPLEPHAD_CharmCvsL = NonBJetCharmCvsL[idx_NONBJET2_TOPTOPLEPHAD];

	_TopLepBJet_TOPTOPLEPHAD_CharmCvsB = BJetCharmCvsB[idx_BJETLEP_TOPTOPLEPHAD];
	_TopHadBJet_TOPTOPLEPHAD_CharmCvsB = BJetCharmCvsB[idx_BJETHAD_TOPTOPLEPHAD];
	_TopHadWNonBJet1_TOPTOPLEPHAD_CharmCvsB = NonBJetCharmCvsB[idx_NONBJET1_TOPTOPLEPHAD];
	_TopHadWNonBJet2_TOPTOPLEPHAD_CharmCvsB = NonBJetCharmCvsB[idx_NONBJET2_TOPTOPLEPHAD];

	for(int i=0;i<_v_JetTight->size();i++)
	  {
	     float pt = _v_JetTight->at(i).pt();
	     float eta = _v_JetTight->at(i).eta();
	     float phi = _v_JetTight->at(i).phi();
	     
	     if( fabs(_TopLepBJet_TOPTOPLEPHAD_p4.Pt()-pt) < 10E-5 &&
		 fabs(_TopLepBJet_TOPTOPLEPHAD_p4.Eta()-eta) < 10E-5 &&
		 fabs(_TopLepBJet_TOPTOPLEPHAD_p4.Phi()-phi) < 10E-5 )
	       _TopLepBJet_TOPTOPLEPHAD_JetIdx = i;

	     if( fabs(_TopHadBJet_TOPTOPLEPHAD_p4.Pt()-pt) < 10E-5 &&
		 fabs(_TopHadBJet_TOPTOPLEPHAD_p4.Eta()-eta) < 10E-5 &&
		 fabs(_TopHadBJet_TOPTOPLEPHAD_p4.Phi()-phi) < 10E-5 )
	       _TopHadBJet_TOPTOPLEPHAD_JetIdx = i;

	     if( fabs(_TopHadWNonBJet1_TOPTOPLEPHAD_p4.Pt()-pt) < 10E-5 &&
		 fabs(_TopHadWNonBJet1_TOPTOPLEPHAD_p4.Eta()-eta) < 10E-5 &&
		 fabs(_TopHadWNonBJet1_TOPTOPLEPHAD_p4.Phi()-phi) < 10E-5 )
	       _TopHadWNonBJet1_TOPTOPLEPHAD_JetIdx = i;

	     if( fabs(_TopHadWNonBJet2_TOPTOPLEPHAD_p4.Pt()-pt) < 10E-5 &&
		 fabs(_TopHadWNonBJet2_TOPTOPLEPHAD_p4.Eta()-eta) < 10E-5 &&
		 fabs(_TopHadWNonBJet2_TOPTOPLEPHAD_p4.Phi()-phi) < 10E-5 )
	       _TopHadWNonBJet2_TOPTOPLEPHAD_JetIdx = i;
	  }	
     }
}
