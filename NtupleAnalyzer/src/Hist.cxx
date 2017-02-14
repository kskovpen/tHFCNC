#include "../include/Hist.h"

#include "TRandom3.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/type_traits.hpp>

Hist::Hist(std::string home,bool evec)
{
   help = new Helper();
   
   _home = home;
   _evec = evec;
   
//   std::string foutlog = "log/"+std::string(flog);
   std::string foutlog = "log/list.txt";
   if( _evec ) _fevc = fopen(foutlog.c_str(),"w");
//   std::string foutlogVal = "log/"+std::string(flog)+".val";
   std::string foutlogVal = "log/list.val";
   if( _evec ) _fevcVal.open(foutlogVal.c_str());
      
   _v_ElectronTight = new std::vector<Electron>;
   _v_ElectronLoose = new std::vector<Electron>;
   _v_MuonTight = new std::vector<Muon>;
   _v_MuonLoose = new std::vector<Muon>;
   _v_JetTight = new std::vector<Jet>;
   _v_BJetTight = new std::vector<Jet>;
   _v_NonBJetTight = new std::vector<Jet>;
   
   _v_Lepton = new std::vector<Lepton>;
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
   
   delete _v_Lepton;

   delete help;
   
   delete _trec;
   
   delete _mva;
   delete _mvaJesUp;
   delete _mvaJesDown;
   delete _mvaJerUp;
   delete _mvaJerDown;
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
   
   _mva = new ApplyMVA(_home);
   _mva->init();

   _mvaJesUp = new ApplyMVA(_home);
   _mvaJesUp->init();

   _mvaJesDown = new ApplyMVA(_home);
   _mvaJesDown->init();

   _mvaJerUp = new ApplyMVA(_home);
   _mvaJerUp->init();

   _mvaJerDown = new ApplyMVA(_home);
   _mvaJerDown->init();
   
   hname.clear(); 

   // TOPHLEPBB
/*   histname_n = 30;
   histname[0] = "h_LepCharge_";
   histname[1] = "h_LepPt_";
   histname[2] = "h_LepEta_";
   histname[3] = "h_LepPhi_";
   
   histname[4] = "h_HiggsMass_TOPHLEPBB_";
   histname[5] = "h_TopLepMass_TOPHLEPBB_";
   histname[6] = "h_HiggsPt_TOPHLEPBB_";
   histname[7] = "h_HiggsEta_TOPHLEPBB_";
   histname[8] = "h_HiggsPhi_TOPHLEPBB_";
   histname[9] = "h_TopLepPt_TOPHLEPBB_";
   histname[10] = "h_TopLepEta_TOPHLEPBB_";
   histname[11] = "h_TopLepPhi_TOPHLEPBB_";
   histname[12] = "h_HiggsBJet1Pt_TOPHLEPBB_";
   histname[13] = "h_HiggsBJet2Pt_TOPHLEPBB_";
   histname[14] = "h_TopLepBJetPt_TOPHLEPBB_";
   histname[15] = "h_HiggsBJet1Eta_TOPHLEPBB_";
   histname[16] = "h_HiggsBJet2Eta_TOPHLEPBB_";
   histname[17] = "h_TopLepBJetEta_TOPHLEPBB_";
   histname[18] = "h_HiggsBJet1Phi_TOPHLEPBB_";
   histname[19] = "h_HiggsBJet2Phi_TOPHLEPBB_";
   histname[20] = "h_TopLepBJetPhi_TOPHLEPBB_";
   histname[21] = "h_HiggsBJet1E_TOPHLEPBB_";
   histname[22] = "h_HiggsBJet2E_TOPHLEPBB_";
   histname[23] = "h_TopLepBJetE_TOPHLEPBB_";
   histname[24] = "h_HiggsBJet1CSVv2_TOPHLEPBB_";
   histname[25] = "h_HiggsBJet2CSVv2_TOPHLEPBB_";
   histname[26] = "h_TopLepBJetCSVv2_TOPHLEPBB_";
   histname[27] = "h_TopLepHiggsDr_TOPHLEPBB_";
   histname[28] = "h_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_";
   histname[29] = "h_MVA_TOPHLEPBB_";*/

   // TOPTOPLEPHBB
/*   histname_n = 31;
   histname[0] = "h_HiggsMass_TOPTOPLEPHBB_";
   histname[1] = "h_TopLepMass_TOPTOPLEPHBB_";
   histname[2] = "h_HiggsPt_TOPTOPLEPHBB_";
   histname[3] = "h_HiggsEta_TOPTOPLEPHBB_";
   histname[4] = "h_HiggsPhi_TOPTOPLEPHBB_";
   histname[5] = "h_TopLepPt_TOPTOPLEPHBB_";
   histname[6] = "h_TopLepEta_TOPTOPLEPHBB_";
   histname[7] = "h_TopLepPhi_TOPTOPLEPHBB_";
   histname[8] = "h_HiggsBJet1Pt_TOPTOPLEPHBB_";
   histname[9] = "h_HiggsBJet2Pt_TOPTOPLEPHBB_";
   histname[10] = "h_TopLepBJetPt_TOPTOPLEPHBB_";
   histname[11] = "h_TopHadNonBJetPt_TOPTOPLEPHBB_";
   histname[12] = "h_HiggsBJet1Eta_TOPTOPLEPHBB_";
   histname[13] = "h_HiggsBJet2Eta_TOPTOPLEPHBB_";
   histname[14] = "h_TopLepBJetEta_TOPTOPLEPHBB_";
   histname[15] = "h_TopHadNonBJetEta_TOPTOPLEPHBB_";
   histname[16] = "h_HiggsBJet1Phi_TOPTOPLEPHBB_";
   histname[17] = "h_HiggsBJet2Phi_TOPTOPLEPHBB_";
   histname[18] = "h_TopLepBJetPhi_TOPTOPLEPHBB_";
   histname[19] = "h_TopHadNonBJetPhi_TOPTOPLEPHBB_";
   histname[20] = "h_HiggsBJet1E_TOPTOPLEPHBB_";
   histname[21] = "h_HiggsBJet2E_TOPTOPLEPHBB_";
   histname[22] = "h_TopLepBJetE_TOPTOPLEPHBB_";
   histname[23] = "h_TopHadNonBJetE_TOPTOPLEPHBB_";
   histname[24] = "h_HiggsBJet1CSVv2_TOPTOPLEPHBB_";
   histname[25] = "h_HiggsBJet2CSVv2_TOPTOPLEPHBB_";
   histname[26] = "h_TopLepBJetCSVv2_TOPTOPLEPHBB_";
   histname[27] = "h_TopHadNonBJetCSVv2_TOPTOPLEPHBB_";
   histname[28] = "h_TopLepHiggsDr_TOPTOPLEPHBB_";
   histname[29] = "h_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_";
   histname[30] = "h_MVA_TOPTOPLEPHBB_";*/

   // TOPTOPLEPHAD
/*   histname_n = 35;
   histname[0] = "h_TopHadWMass_TOPTOPLEPHAD_";
   histname[1] = "h_TopLepMass_TOPTOPLEPHAD_";
   histname[2] = "h_TopHadMass_TOPTOPLEPHAD_";
   histname[3] = "h_TopHadWPt_TOPTOPLEPHAD_";
   histname[4] = "h_TopHadWEta_TOPTOPLEPHAD_";
   histname[5] = "h_TopHadWPhi_TOPTOPLEPHAD_";
   histname[6] = "h_TopHadPt_TOPTOPLEPHAD_";
   histname[7] = "h_TopHadEta_TOPTOPLEPHAD_";
   histname[8] = "h_TopHadPhi_TOPTOPLEPHAD_";
   histname[9] = "h_TopLepPt_TOPTOPLEPHAD_";
   histname[10] = "h_TopLepEta_TOPTOPLEPHAD_";
   histname[11] = "h_TopLepPhi_TOPTOPLEPHAD_";
   histname[12] = "h_TopHadWNonBJet1Pt_TOPTOPLEPHAD_";
   histname[13] = "h_TopHadWNonBJet2Pt_TOPTOPLEPHAD_";
   histname[14] = "h_TopLepBJetPt_TOPTOPLEPHAD_";   
   histname[15] = "h_TopHadBJetPt_TOPTOPLEPHAD_";
   histname[16] = "h_TopHadWNonBJet1Eta_TOPTOPLEPHAD_";
   histname[17] = "h_TopHadWNonBJet2Eta_TOPTOPLEPHAD_";
   histname[18] = "h_TopLepBJetEta_TOPTOPLEPHAD_";
   histname[19] = "h_TopHadBJetEta_TOPTOPLEPHAD_";
   histname[20] = "h_TopHadWNonBJet1Phi_TOPTOPLEPHAD_";
   histname[21] = "h_TopHadWNonBJet2Phi_TOPTOPLEPHAD_";
   histname[22] = "h_TopLepBJetPhi_TOPTOPLEPHAD_";
   histname[23] = "h_TopHadBJetPhi_TOPTOPLEPHAD_";
   histname[24] = "h_TopHadWNonBJet1E_TOPTOPLEPHAD_";
   histname[25] = "h_TopHadWNonBJet2E_TOPTOPLEPHAD_";
   histname[26] = "h_TopLepBJetE_TOPTOPLEPHAD_";
   histname[27] = "h_TopHadBJetE_TOPTOPLEPHAD_";
   histname[28] = "h_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_";
   histname[29] = "h_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_";
   histname[30] = "h_TopLepBJetCSVv2_TOPTOPLEPHAD_";
   histname[31] = "h_TopHadBJetCSVv2_TOPTOPLEPHAD_";
   histname[32] = "h_TopLepTopHadDr_TOPTOPLEPHAD_";
   histname[33] = "h_TopHadWNonBJet1TopHadWNonBJet2Dr_TOPTOPLEPHAD_";
   histname[34] = "h_MVA_TOPTOPLEPHAD_";*/

   histname_n = 2;
/*   histname[0] = "h_MVAHutST_";
   histname[1] = "h_MVAHctST_";
   histname[2] = "h_MVAHutTT_";
   histname[3] = "h_MVAHctTT_";
   histname[4] = "h_PassSel5_";
   histname[5] = "h_MVAHut_";
   histname[6] = "h_MVAHct_";*/
   histname[0] = "h_MVAHutMAX_";
   histname[1] = "h_MVAHctMAX_";

   type_n = 4;
//   type[0] = "nonQCD";
//   type[1] = "QCD";
   type[0] = "ALL";
   type[1] = "ttbb";
   type[2] = "ttcc";
   type[3] = "ttlf";

   sel_n = 6;
//   sel[0] = "b0j3";
//   sel[1] = "b0j4";
//   sel[2] = "b1j3";
//   sel[3] = "b1j4";
   sel[0] = "b2j3";
   sel[1] = "b2j4";
   sel[2] = "b3j3";
   sel[3] = "b3j4";
   sel[4] = "b4j4";
   sel[5] = "ALL";

   chan_n = 3;
   chan[0] = "all";
   chan[1] = "e";
   chan[2] = "m";
   
   sys_low_n = 12;
   sys_low[0]   = "";
   sys_low[1]   = "_SfIterativeFitJes_Down";
   sys_low[2]   = "_SfIterativeFitLf_Down";
   sys_low[3]   = "_SfIterativeFitHf_Down";
   sys_low[4]   = "_SfIterativeFitHfstats1_Down";
   sys_low[5]   = "_SfIterativeFitHfstats2_Down";
   sys_low[6]   = "_SfIterativeFitCferr1_Down";
   sys_low[7]   = "_SfIterativeFitCferr2_Down";
   sys_low[8]   = "_SfIterativeFitLfstats1_Down";
   sys_low[9]   = "_SfIterativeFitLfstats2_Down";
   sys_low[10]   = "_Jes_Down";
   sys_low[11]   = "_Jer_Down";

   sys_up_n = sys_low_n-1;
   sys_up[0]   = "_SfIterativeFitJes_Up";
   sys_up[1]   = "_SfIterativeFitLf_Up";
   sys_up[2]   = "_SfIterativeFitHf_Up";
   sys_up[3]   = "_SfIterativeFitHfstats1_Up";
   sys_up[4]   = "_SfIterativeFitHfstats2_Up";
   sys_up[5]   = "_SfIterativeFitCferr1_Up";
   sys_up[6]   = "_SfIterativeFitCferr2_Up";
   sys_up[7]   = "_SfIterativeFitLfstats1_Up";
   sys_up[8]   = "_SfIterativeFitLfstats2_Up";
   sys_up[9]   = "_Jes_Up";
   sys_up[10]   = "_Jer_Up";

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
	for(int is=0;is<sel_n;is++)
	  {
	     std::string trName = "tr_"+chan[ic]+"_"+sel[is];
	     _trout[ic][is] = new TTree(trName.c_str(),trName.c_str());
	     
	     _trout[ic][is]->Branch("weight",&m_weight,"weight/D");
	     _trout[ic][is]->Branch("HiggsMass_TOPTOPLEPHBB",&m_HiggsMass_TOPTOPLEPHBB,"HiggsMass_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("HiggsMass_TOPHLEPBB",&m_HiggsMass_TOPHLEPBB,"HiggsMass_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("TopHadMass_TOPTOPLEPHAD",&m_TopHadMass_TOPTOPLEPHAD,"TopHadMass_TOPTOPLEPHAD/D");
	     _trout[ic][is]->Branch("chi2_TOPTOPLEPHBB",&m_chi2_TOPTOPLEPHBB,"chi2_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("chi2_TOPHLEPBB",&m_chi2_TOPHLEPBB,"chi2_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("chi2_TOPTOPLEPHAD",&m_chi2_TOPTOPLEPHAD,"chi2_TOPTOPLEPHAD/D");
	     _trout[ic][is]->Branch("MVA_TOPTOPLEPHBB",&m_MVA_TOPTOPLEPHBB,"MVA_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("MVA_TOPHLEPBB",&m_MVA_TOPHLEPBB,"MVA_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("MVA_TOPTOPLEPHAD",&m_MVA_TOPTOPLEPHAD,"MVA_TOPTOPLEPHAD/D");
	     _trout[ic][is]->Branch("LepCharge",&m_LepCharge,"LepCharge/I");
	     _trout[ic][is]->Branch("HiggsEta_TOPTOPLEPHBB",&m_HiggsEta_TOPTOPLEPHBB,"HiggsEta_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("HiggsEta_TOPHLEPBB",&m_HiggsEta_TOPHLEPBB,"HiggsEta_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("TopLepMass_TOPTOPLEPHBB",&m_TopLepMass_TOPTOPLEPHBB,"TopLepMass_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("TopLepMass_TOPHLEPBB",&m_TopLepMass_TOPHLEPBB,"TopLepMass_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("TopLepMass_TOPTOPLEPHAD",&m_TopLepMass_TOPTOPLEPHAD,"TopLepMass_TOPTOPLEPHAD/D");
	     _trout[ic][is]->Branch("TopLepPt_TOPTOPLEPHBB",&m_TopLepPt_TOPTOPLEPHBB,"TopLepPt_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("TopLepPt_TOPHLEPBB",&m_TopLepPt_TOPHLEPBB,"TopLepPt_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("TopLepPt_TOPTOPLEPHAD",&m_TopLepPt_TOPTOPLEPHAD,"TopLepPt_TOPTOPLEPHAD/D");
	     _trout[ic][is]->Branch("TopLepEta_TOPTOPLEPHBB",&m_TopLepEta_TOPTOPLEPHBB,"TopLepEta_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("TopLepEta_TOPHLEPBB",&m_TopLepEta_TOPHLEPBB,"TopLepEta_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("TopLepEta_TOPTOPLEPHAD",&m_TopLepEta_TOPTOPLEPHAD,"TopLepEta_TOPTOPLEPHAD/D");
	     _trout[ic][is]->Branch("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",&m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB,"HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB,"HiggsBJet1HiggsBJet2Dr_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("TopLepHiggsDr_TOPTOPLEPHBB",&m_TopLepHiggsDr_TOPTOPLEPHBB,"TopLepHiggsDr_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("TopLepHiggsDr_TOPHLEPBB",&m_TopLepHiggsDr_TOPHLEPBB,"TopLepHiggsDr_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("TopLepTopHadDr_TOPTOPLEPHAD",&m_TopLepTopHadDr_TOPTOPLEPHAD,"TopLepTopHadDr_TOPTOPLEPHAD/D");
	     _trout[ic][is]->Branch("HiggsBJet1CSVv2_TOPTOPLEPHBB",&m_HiggsBJet1CSVv2_TOPTOPLEPHBB,"HiggsBJet1CSVv2_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("HiggsBJet2CSVv2_TOPTOPLEPHBB",&m_HiggsBJet2CSVv2_TOPTOPLEPHBB,"HiggsBJet2CSVv2_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("TopLepBJetCSVv2_TOPTOPLEPHBB",&m_TopLepBJetCSVv2_TOPTOPLEPHBB,"TopLepBJetCSVv2_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("TopHadNonBJetCSVv2_TOPTOPLEPHBB",&m_TopHadNonBJetCSVv2_TOPTOPLEPHBB,"TopHadNonBJetCSVv2_TOPTOPLEPHBB/D");
	     _trout[ic][is]->Branch("HiggsBJet1CSVv2_TOPHLEPBB",&m_HiggsBJet1CSVv2_TOPHLEPBB,"HiggsBJet1CSVv2_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("HiggsBJet2CSVv2_TOPHLEPBB",&m_HiggsBJet2CSVv2_TOPHLEPBB,"HiggsBJet2CSVv2_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("TopLepBJetCSVv2_TOPHLEPBB",&m_TopLepBJetCSVv2_TOPHLEPBB,"TopLepBJetCSVv2_TOPHLEPBB/D");
	     _trout[ic][is]->Branch("TopLepBJetCSVv2_TOPTOPLEPHAD",&m_TopLepBJetCSVv2_TOPTOPLEPHAD,"TopLepBJetCSVv2_TOPTOPLEPHAD/D");
	     _trout[ic][is]->Branch("TopHadBJetCSVv2_TOPTOPLEPHAD",&m_TopHadBJetCSVv2_TOPTOPLEPHAD,"TopHadBJetCSVv2_TOPTOPLEPHAD/D");
	     _trout[ic][is]->Branch("TopHadWNonBJet1CSVv2_TOPTOPLEPHAD",&m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD,"TopHadWNonBJet1CSVv2_TOPTOPLEPHAD/D");
	     _trout[ic][is]->Branch("TopHadWNonBJet2CSVv2_TOPTOPLEPHAD",&m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD,"TopHadWNonBJet2CSVv2_TOPTOPLEPHAD/D");
	  }
     }

   _s_Hist = new std::vector<std::pair<std::vector<std::string>,double*> >();
   _m1d_Hist = new std::map<std::string, TH1D*>();

   std::vector<double*> set_hist;
   set_hist.clear();

   // Ranges
/*   set_hist.push_back(RANGE::set_l_charge);
   set_hist.push_back(RANGE::set_l_pt);
   set_hist.push_back(RANGE::set_l_eta);
   set_hist.push_back(RANGE::set_l_phi);*/
   // TOPHLEPBB
/*   set_hist.push_back(RANGE::set_H_m);
   set_hist.push_back(RANGE::set_top_m);
   set_hist.push_back(RANGE::set_H_pt);
   set_hist.push_back(RANGE::set_H_eta);
   set_hist.push_back(RANGE::set_H_phi);
   set_hist.push_back(RANGE::set_top_pt);
   set_hist.push_back(RANGE::set_top_eta);
   set_hist.push_back(RANGE::set_top_phi);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_Hb1_Hb2_dr);
   set_hist.push_back(RANGE::set_Hb1_Hb2_dr);
   set_hist.push_back(RANGE::set_bMVA);*/

   // TOPTOPLEPHBB
/*   set_hist.push_back(RANGE::set_H_m);
   set_hist.push_back(RANGE::set_top_m);
   set_hist.push_back(RANGE::set_H_pt);
   set_hist.push_back(RANGE::set_H_eta);
   set_hist.push_back(RANGE::set_H_phi);
   set_hist.push_back(RANGE::set_top_pt);
   set_hist.push_back(RANGE::set_top_eta);
   set_hist.push_back(RANGE::set_top_phi);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_Hb1_Hb2_dr);
   set_hist.push_back(RANGE::set_Hb1_Hb2_dr);
   set_hist.push_back(RANGE::set_bMVA);*/

   // TOPTOPLEPHAD
/*   set_hist.push_back(RANGE::set_W_m);
   set_hist.push_back(RANGE::set_top_m);
   set_hist.push_back(RANGE::set_top_m);
   set_hist.push_back(RANGE::set_W_pt);
   set_hist.push_back(RANGE::set_W_eta);
   set_hist.push_back(RANGE::set_W_phi);
   set_hist.push_back(RANGE::set_top_pt);
   set_hist.push_back(RANGE::set_top_eta);
   set_hist.push_back(RANGE::set_top_phi);
   set_hist.push_back(RANGE::set_top_pt);
   set_hist.push_back(RANGE::set_top_eta);
   set_hist.push_back(RANGE::set_top_phi);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetPt);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetEta);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetPhi);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_JetE);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_CSVv2);
   set_hist.push_back(RANGE::set_Hb1_Hb2_dr);
   set_hist.push_back(RANGE::set_Hb1_Hb2_dr);
   set_hist.push_back(RANGE::set_bMVA);*/
   
/*   set_hist.push_back(RANGE::set_MVA);
   set_hist.push_back(RANGE::set_MVA);
   set_hist.push_back(RANGE::set_MVA);
   set_hist.push_back(RANGE::set_MVA);
   set_hist.push_back(RANGE::set_PassSel5);   
   set_hist.push_back(RANGE::set_MVA36);
   set_hist.push_back(RANGE::set_MVA36);*/
   set_hist.push_back(RANGE::set_MVA);
   set_hist.push_back(RANGE::set_MVA);
   
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
   bool isTTBar = _v_Event->at(0).isTTBar();
   int genTTX = _v_Event->at(0).genTTX_id();
   
   bool isData = _v_Event->at(0).isData();                                                                              

   float xsec = _v_Event->at(0).xsec();
   float noe = _v_Event->at(0).noe();

   float wil = 36800.*xsec/noe;
   if( !isData ) w *= wil;
   
   bool passTrig = 0;
   if( isData )
     {
	if( !isTrigElec && isTrigMuon ) passTrig = 1;
	else if( isTrigElec && !isTrigMuon ) passTrig = 1;
     }   
   else passTrig = (isTrigElec || isTrigMuon);
   
   if( !passTrig ) return;
   
   _v_JetTight->clear();
   _v_BJetTight->clear();
   _v_NonBJetTight->clear();

/*   for(int i=0;i<_v_Electron->size();i++)
     {
	if( _v_Electron->at(i).isTight() )
	  {
	     _v_ElectronTight->push_back(_v_Electron->at(i));
	  }	
        else if( _v_Electron->at(i).isLoose() )
	  {
	     _v_ElectronLoose->push_back(_v_Electron->at(i));
	  }	
     }

   for(int i=0;i<_v_Muon->size();i++)
     {
	if( _v_Muon->at(i).isTight() )
	  {	     
	     _v_MuonTight->push_back(_v_Muon->at(i));
	  }	
	else if( _v_Muon->at(i).isLoose() )
	  {
	     _v_MuonLoose->push_back(_v_Muon->at(i));
	  }	
     }*/

   std::sort(_v_Jet->begin(),_v_Jet->end(),Jet::sortCSVv2Predicate);
   
   for(int i=0;i<_v_Jet->size();i++)
     {
	if( fabs(_v_Jet->at(i).eta()) > 2.4 ) continue;

	if( _v_Jet->at(i).isTight() )
	  {	     
	     _v_JetTight->push_back(_v_Jet->at(i));
	     
	     //	if( _v_Jet->at(i).CSVv2() >= 0.605 ) _v_BJetTight->push_back(_v_Jet->at(i));
	     //	if( i < 2 && _v_Jet->at(i).CSVv2() >= 0.890 ) _v_BJetTight->push_back(_v_Jet->at(i));
	     if( _v_Jet->at(i).CSVv2() >= 0.8484 ) _v_BJetTight->push_back(_v_Jet->at(i));
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
   
   bool hasPV = (!(_v_Event->at(0).pvIsFake()) && _v_Event->at(0).pvNDOF() > 4 && fabs(_v_Event->at(0).pvZ()) < 24 && _v_Event->at(0).pvRho() < 2 && _v_Event->at(0).nvertex() > 0);

//   bool passElec = (hasPV && isTrigElec && nElecTight == 1 && nMuonLoose+nMuonTight == 0 && nElecLoose == 0 && is1E);
//   bool passMuon = (hasPV && isTrigMuon && nMuonTight == 1 && nElecLoose+nElecTight == 0 && nMuonLoose == 0 && is1M);
   bool passElec = (is1L && nElecTight == 1 && nMuonLoose+nMuonTight == 0 && nElecLoose == 0);
   bool passMuon = (is1L && nMuonTight == 1 && nElecLoose+nElecTight == 0 && nMuonLoose == 0);
   bool passLep = (passElec || passMuon);
   
   passSel_all = 0x0;
//   passSel_all |= (passLep && njets == 3 && nbjets == 0)   << 0;
//   passSel_all |= (passLep && njets >= 4 && nbjets == 0)   << 1;
//   passSel_all |= (passLep && njets == 3 && nbjets == 1)   << 2;
//   passSel_all |= (passLep && njets >= 4 && nbjets == 1)   << 3;
   passSel_all |= (passLep && njets == 3 && nbjets == 2)   << 0;
   passSel_all |= (passLep && njets >= 4 && nbjets == 2)   << 1;
   passSel_all |= (passLep && njets == 3 && nbjets == 3)   << 2;
   passSel_all |= (passLep && njets >= 4 && nbjets == 3)   << 3;
   passSel_all |= (passLep && njets >= 4 && nbjets >= 4)   << 4;
   passSel_all |= (1)   << 5;

   passSel_e = 0x0;
   passSel_m = 0x0;
   for(int i=0;i<sel_n;i++)
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

   bool isttbb = (genTTX == 051 || genTTX == 151 || genTTX == 251 ||
		  genTTX == 052 || genTTX == 152 || genTTX == 252 ||
		  genTTX == 053 || genTTX == 153 || genTTX == 253 ||
		  genTTX == 054 || genTTX == 154 || genTTX == 254 ||
		  genTTX == 055 || genTTX == 155 || genTTX == 255);
   
   bool isttcc = (genTTX == 041 || genTTX == 141 || genTTX == 241 ||
		  genTTX == 042 || genTTX == 142 || genTTX == 242 ||
		  genTTX == 043 || genTTX == 143 || genTTX == 243 ||
		  genTTX == 044 || genTTX == 144 || genTTX == 244 ||
		  genTTX == 045 || genTTX == 145 || genTTX == 245);
   
   bool isttlf = (!isttbb && !isttcc);
   
   bool type_pass[type_n];
   for(int it=0;it<type_n;it++)
     {	
	type_pass[it] = 0;
	if( (type[it] == "ALL") ||
	    (type[it] == "ttbb" && isttbb && isTTBar) ||
	    (type[it] == "ttcc" && isttcc && isTTBar) ||
	    (type[it] == "ttlf" && isttlf && isTTBar)
	  )
	  type_pass[it] = 1;
     }   

   passSel_ev = 0x0;
   passSel_ev |= (hasPV) << 0;
   passSel_ev |= (hasPV && isTrigElec) << 1;
   passSel_ev |= (hasPV && isTrigMuon) << 2;
//   passSel_ev |= (hasPV && isTrigMuon && nMuonTight == 1) << 3;
//   passSel_ev |= (hasPV && isTrigMuon && nMuonTight == 1 && nElecLoose+nElecTight == 0) << 4;
//   passSel_ev |= (hasPV && isTrigMuon && nMuonTight == 1 && nElecLoose+nElecTight == 0 && nMuonLoose == 0) << 5;
//   passSel_ev |= (hasPV && isTrigMuon && nMuonTight == 1 && nElecLoose+nElecTight == 0 && nMuonLoose == 0 && njets >= 3) << 6;

   passSel_ev |= (hasPV && isTrigElec && nElecTight == 1) << 3;
   passSel_ev |= (hasPV && isTrigElec && nElecTight == 1 && nMuonLoose+nMuonTight == 0) << 4;
   passSel_ev |= (hasPV && isTrigElec && nElecTight == 1 && nMuonLoose+nMuonTight == 0 && nElecLoose == 0 ) << 5;
   passSel_ev |= (hasPV && isTrigElec && nElecTight == 1 && nMuonLoose+nMuonTight == 0 && nElecLoose == 0 && njets >= 3) << 6;
  
   if( _evec )
     {	
	if( is1E || is1M )
	  {	
	     /*	int lepId = (is1E) ? _v_ElectronTight->at(0).id() : _v_MuonTight->at(0).id();
	      float lepPt = (is1E) ? _v_ElectronTight->at(0).pt() : _v_MuonTight->at(0).pt();
	      float lepEta = (is1E) ? _v_ElectronTight->at(0).eta() : _v_MuonTight->at(0).eta();
	      float lepPhi = (is1E) ? _v_ElectronTight->at(0).phi() : _v_MuonTight->at(0).phi();
	      * 
	      float jetPt = (njets > 0) ? _v_JetTight->at(0).pt() : -1;
	      float jetEta = (njets > 0) ? _v_JetTight->at(0).eta() : -1;
	      float jetPhi = (njets > 0) ? _v_JetTight->at(0).phi() : -1;
	      */	
	     	printout(1,run,lumi,id,0,0,0,0,0,0,0,0,0,0,0);
	     //	printout(1,run,lumi,id,lepId,lepPt,lepEta,lepPhi,metpt,metphi,njets,nbjets,jetPt,jetEta,jetPhi);
	  }
     }   
   
   int idxSR = -1;
   
   // Selection crtieria for plots
   bool pass = (
//		CHECK_BIT(passSel_all,0) ||
//		CHECK_BIT(passSel_all,1) ||
//		CHECK_BIT(passSel_all,2) ||
//		CHECK_BIT(passSel_all,3) ||
		CHECK_BIT(passSel_all,0) ||
		CHECK_BIT(passSel_all,1) ||
		CHECK_BIT(passSel_all,2) ||
		CHECK_BIT(passSel_all,3) ||
		CHECK_BIT(passSel_all,4)
	       );
   
   if( pass )
     {
	_v_Lepton->clear();

	for(int ie=0;ie<_v_ElectronTight->size();ie++) 
	  {
	     Lepton lep;
	     lep.setLepton(&_v_ElectronTight->at(ie),ie,1);
	     _v_Lepton->push_back(lep);
	  }	
	for(int im=0;im<_v_MuonTight->size();im++)
	  {
	     Lepton lep;
	     lep.setLepton(&_v_MuonTight->at(im),im,0);
	     _v_Lepton->push_back(lep);
	  }
	
	_trec->setElectron(_v_ElectronTight);
	_trec->setMuon(_v_MuonTight);
	_trec->setJet(_v_JetTight);
	_trec->setBJet(_v_BJetTight);
	_trec->setNonBJet(_v_NonBJetTight);
	_trec->setEvent(_v_Event);

	if( _evec ) return;
	
	// top reconstruction
	_trec->run();

	// nominal
	m_HiggsMass_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_p4().M();
	m_HiggsMass_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_p4().M();
	m_TopHadMass_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_p4().M();
	m_chi2_TOPTOPLEPHBB = _trec->chi2_TOPTOPLEPHBB();
	m_chi2_TOPHLEPBB = _trec->chi2_TOPHLEPBB();
	m_chi2_TOPTOPLEPHAD = _trec->chi2_TOPTOPLEPHAD();
	m_MVA_TOPTOPLEPHBB = _trec->MVA_TOPTOPLEPHBB();
	m_MVA_TOPHLEPBB = _trec->MVA_TOPHLEPBB();
	m_MVA_TOPTOPLEPHAD = _trec->MVA_TOPTOPLEPHAD();   
	m_LepCharge = _v_Lepton->at(0).charge();
	m_HiggsEta_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_p4().PseudoRapidity();
	m_HiggsEta_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_p4().PseudoRapidity();
	m_TopLepMass_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_p4().M();
	m_TopLepMass_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_p4().M();
	m_TopLepMass_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_p4().M();
	m_TopLepPt_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_p4().Pt();
	m_TopLepPt_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_p4().Pt();
	m_TopLepPt_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_p4().Pt();
	m_TopLepEta_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_p4().PseudoRapidity();
	m_TopLepEta_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_p4().PseudoRapidity();
	m_TopLepEta_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_p4().PseudoRapidity();
	m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_p4().DeltaR(_trec->HiggsBJet2_TOPTOPLEPHBB_p4());
	m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_p4().DeltaR(_trec->HiggsBJet2_TOPHLEPBB_p4());
	m_TopLepHiggsDr_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_p4().DeltaR(_trec->Higgs_TOPTOPLEPHBB_p4());
	m_TopLepHiggsDr_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_p4().DeltaR(_trec->Higgs_TOPHLEPBB_p4());
	m_TopLepTopHadDr_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_p4().DeltaR(_trec->TopHad_TOPTOPLEPHAD_p4());
	
	m_HiggsBJet1CSVv2_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_CSVv2();
	m_HiggsBJet2CSVv2_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_CSVv2();
	m_TopLepBJetCSVv2_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_CSVv2();
	m_TopHadNonBJetCSVv2_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_CSVv2();
	m_HiggsBJet1CSVv2_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_CSVv2();
	m_HiggsBJet2CSVv2_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_CSVv2();
	m_TopLepBJetCSVv2_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_CSVv2();
	m_TopLepBJetCSVv2_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_CSVv2();
	m_TopHadBJetCSVv2_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_CSVv2();
	m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2();
	m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2();

	if( !isData ) 
	  {	     
	     // JesUp
	     m_HiggsMass_TOPTOPLEPHBB_JesUp = _trec->Higgs_TOPTOPLEPHBB_JesUp_p4().M();
	     m_HiggsMass_TOPHLEPBB_JesUp = _trec->Higgs_TOPHLEPBB_JesUp_p4().M();
	     m_TopHadMass_TOPTOPLEPHAD_JesUp = _trec->TopHad_TOPTOPLEPHAD_JesUp_p4().M();
	     m_chi2_TOPTOPLEPHBB_JesUp = _trec->chi2_TOPTOPLEPHBB();
	     m_chi2_TOPHLEPBB_JesUp = _trec->chi2_TOPHLEPBB();
	     m_chi2_TOPTOPLEPHAD_JesUp = _trec->chi2_TOPTOPLEPHAD();
	     m_MVA_TOPTOPLEPHBB_JesUp = _trec->MVA_TOPTOPLEPHBB_JesUp();
	     m_MVA_TOPHLEPBB_JesUp = _trec->MVA_TOPHLEPBB_JesUp();
	     m_MVA_TOPTOPLEPHAD_JesUp = _trec->MVA_TOPTOPLEPHAD_JesUp();
	     m_LepCharge_JesUp = _v_Lepton->at(0).charge();
	     m_HiggsEta_TOPTOPLEPHBB_JesUp = _trec->Higgs_TOPTOPLEPHBB_JesUp_p4().PseudoRapidity();
	     m_HiggsEta_TOPHLEPBB_JesUp = _trec->Higgs_TOPHLEPBB_JesUp_p4().PseudoRapidity();
	     m_TopLepMass_TOPTOPLEPHBB_JesUp = _trec->TopLep_TOPTOPLEPHBB_JesUp_p4().M();
	     m_TopLepMass_TOPHLEPBB_JesUp = _trec->TopLep_TOPHLEPBB_JesUp_p4().M();
	     m_TopLepMass_TOPTOPLEPHAD_JesUp = _trec->TopLep_TOPTOPLEPHAD_JesUp_p4().M();
	     m_TopLepPt_TOPTOPLEPHBB_JesUp = _trec->TopLep_TOPTOPLEPHBB_JesUp_p4().Pt();
	     m_TopLepPt_TOPHLEPBB_JesUp = _trec->TopLep_TOPHLEPBB_JesUp_p4().Pt();
	     m_TopLepPt_TOPTOPLEPHAD_JesUp = _trec->TopLep_TOPTOPLEPHAD_JesUp_p4().Pt();
	     m_TopLepEta_TOPTOPLEPHBB_JesUp = _trec->TopLep_TOPTOPLEPHBB_JesUp_p4().PseudoRapidity();
	     m_TopLepEta_TOPHLEPBB_JesUp = _trec->TopLep_TOPHLEPBB_JesUp_p4().PseudoRapidity();
	     m_TopLepEta_TOPTOPLEPHAD_JesUp = _trec->TopLep_TOPTOPLEPHAD_JesUp_p4().PseudoRapidity();
	     m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JesUp = _trec->HiggsBJet1_TOPTOPLEPHBB_JesUp_p4().DeltaR(_trec->HiggsBJet2_TOPTOPLEPHBB_JesUp_p4());
	     m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JesUp = _trec->HiggsBJet1_TOPHLEPBB_JesUp_p4().DeltaR(_trec->HiggsBJet2_TOPHLEPBB_JesUp_p4());
	     m_TopLepHiggsDr_TOPTOPLEPHBB_JesUp = _trec->TopLep_TOPTOPLEPHBB_JesUp_p4().DeltaR(_trec->Higgs_TOPTOPLEPHBB_JesUp_p4());
	     m_TopLepHiggsDr_TOPHLEPBB_JesUp = _trec->TopLep_TOPHLEPBB_JesUp_p4().DeltaR(_trec->Higgs_TOPHLEPBB_JesUp_p4());
	     m_TopLepTopHadDr_TOPTOPLEPHAD_JesUp = _trec->TopLep_TOPTOPLEPHAD_JesUp_p4().DeltaR(_trec->TopHad_TOPTOPLEPHAD_JesUp_p4());
	
	     m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JesUp = _trec->HiggsBJet1_TOPTOPLEPHBB_CSVv2();
	     m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JesUp = _trec->HiggsBJet2_TOPTOPLEPHBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPTOPLEPHBB_JesUp = _trec->TopLepBJet_TOPTOPLEPHBB_CSVv2();
	     m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JesUp = _trec->TopHadNonBJet_TOPTOPLEPHBB_CSVv2();
	     m_HiggsBJet1CSVv2_TOPHLEPBB_JesUp = _trec->HiggsBJet1_TOPHLEPBB_CSVv2();
	     m_HiggsBJet2CSVv2_TOPHLEPBB_JesUp = _trec->HiggsBJet2_TOPHLEPBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPHLEPBB_JesUp = _trec->TopLepBJet_TOPHLEPBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPTOPLEPHAD_JesUp = _trec->TopLepBJet_TOPTOPLEPHAD_CSVv2();
	     m_TopHadBJetCSVv2_TOPTOPLEPHAD_JesUp = _trec->TopHadBJet_TOPTOPLEPHAD_CSVv2();
	     m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JesUp = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2();
	     m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JesUp = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2();

	     // JesDown
	     m_HiggsMass_TOPTOPLEPHBB_JesDown = _trec->Higgs_TOPTOPLEPHBB_JesDown_p4().M();
	     m_HiggsMass_TOPHLEPBB_JesDown = _trec->Higgs_TOPHLEPBB_JesDown_p4().M();
	     m_TopHadMass_TOPTOPLEPHAD_JesDown = _trec->TopHad_TOPTOPLEPHAD_JesDown_p4().M();
	     m_chi2_TOPTOPLEPHBB_JesDown = _trec->chi2_TOPTOPLEPHBB();
	     m_chi2_TOPHLEPBB_JesDown = _trec->chi2_TOPHLEPBB();
	     m_chi2_TOPTOPLEPHAD_JesDown = _trec->chi2_TOPTOPLEPHAD();
	     m_MVA_TOPTOPLEPHBB_JesDown = _trec->MVA_TOPTOPLEPHBB_JesDown();
	     m_MVA_TOPHLEPBB_JesDown = _trec->MVA_TOPHLEPBB_JesDown();
	     m_MVA_TOPTOPLEPHAD_JesDown = _trec->MVA_TOPTOPLEPHAD_JesDown();
	     m_LepCharge_JesDown = _v_Lepton->at(0).charge();
	     m_HiggsEta_TOPTOPLEPHBB_JesDown = _trec->Higgs_TOPTOPLEPHBB_JesDown_p4().PseudoRapidity();
	     m_HiggsEta_TOPHLEPBB_JesDown = _trec->Higgs_TOPHLEPBB_JesDown_p4().PseudoRapidity();
	     m_TopLepMass_TOPTOPLEPHBB_JesDown = _trec->TopLep_TOPTOPLEPHBB_JesDown_p4().M();
	     m_TopLepMass_TOPHLEPBB_JesDown = _trec->TopLep_TOPHLEPBB_JesDown_p4().M();
	     m_TopLepMass_TOPTOPLEPHAD_JesDown = _trec->TopLep_TOPTOPLEPHAD_JesDown_p4().M();
	     m_TopLepPt_TOPTOPLEPHBB_JesDown = _trec->TopLep_TOPTOPLEPHBB_JesDown_p4().Pt();
	     m_TopLepPt_TOPHLEPBB_JesDown = _trec->TopLep_TOPHLEPBB_JesDown_p4().Pt();
	     m_TopLepPt_TOPTOPLEPHAD_JesDown = _trec->TopLep_TOPTOPLEPHAD_JesDown_p4().Pt();
	     m_TopLepEta_TOPTOPLEPHBB_JesDown = _trec->TopLep_TOPTOPLEPHBB_JesDown_p4().PseudoRapidity();
	     m_TopLepEta_TOPHLEPBB_JesDown = _trec->TopLep_TOPHLEPBB_JesDown_p4().PseudoRapidity();
	     m_TopLepEta_TOPTOPLEPHAD_JesDown = _trec->TopLep_TOPTOPLEPHAD_JesDown_p4().PseudoRapidity();
	     m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JesDown = _trec->HiggsBJet1_TOPTOPLEPHBB_JesDown_p4().DeltaR(_trec->HiggsBJet2_TOPTOPLEPHBB_JesDown_p4());
	     m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JesDown = _trec->HiggsBJet1_TOPHLEPBB_JesDown_p4().DeltaR(_trec->HiggsBJet2_TOPHLEPBB_JesDown_p4());
	     m_TopLepHiggsDr_TOPTOPLEPHBB_JesDown = _trec->TopLep_TOPTOPLEPHBB_JesDown_p4().DeltaR(_trec->Higgs_TOPTOPLEPHBB_JesDown_p4());
	     m_TopLepHiggsDr_TOPHLEPBB_JesDown = _trec->TopLep_TOPHLEPBB_JesDown_p4().DeltaR(_trec->Higgs_TOPHLEPBB_JesDown_p4());
	     m_TopLepTopHadDr_TOPTOPLEPHAD_JesDown = _trec->TopLep_TOPTOPLEPHAD_JesDown_p4().DeltaR(_trec->TopHad_TOPTOPLEPHAD_JesDown_p4());
	     
	     m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JesDown = _trec->HiggsBJet1_TOPTOPLEPHBB_CSVv2();
	     m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JesDown = _trec->HiggsBJet2_TOPTOPLEPHBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPTOPLEPHBB_JesDown = _trec->TopLepBJet_TOPTOPLEPHBB_CSVv2();
	     m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JesDown = _trec->TopHadNonBJet_TOPTOPLEPHBB_CSVv2();
	     m_HiggsBJet1CSVv2_TOPHLEPBB_JesDown = _trec->HiggsBJet1_TOPHLEPBB_CSVv2();
	     m_HiggsBJet2CSVv2_TOPHLEPBB_JesDown = _trec->HiggsBJet2_TOPHLEPBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPHLEPBB_JesDown = _trec->TopLepBJet_TOPHLEPBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPTOPLEPHAD_JesDown = _trec->TopLepBJet_TOPTOPLEPHAD_CSVv2();
	     m_TopHadBJetCSVv2_TOPTOPLEPHAD_JesDown = _trec->TopHadBJet_TOPTOPLEPHAD_CSVv2();
	     m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JesDown = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2();
	     m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JesDown = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2();
	     
	     // JerUp
	     m_HiggsMass_TOPTOPLEPHBB_JerUp = _trec->Higgs_TOPTOPLEPHBB_JerUp_p4().M();
	     m_HiggsMass_TOPHLEPBB_JerUp = _trec->Higgs_TOPHLEPBB_JerUp_p4().M();
	     m_TopHadMass_TOPTOPLEPHAD_JerUp = _trec->TopHad_TOPTOPLEPHAD_JerUp_p4().M();
	     m_chi2_TOPTOPLEPHBB_JerUp = _trec->chi2_TOPTOPLEPHBB();
	     m_chi2_TOPHLEPBB_JerUp = _trec->chi2_TOPHLEPBB();
	     m_chi2_TOPTOPLEPHAD_JerUp = _trec->chi2_TOPTOPLEPHAD();
	     m_MVA_TOPTOPLEPHBB_JerUp = _trec->MVA_TOPTOPLEPHBB_JerUp();
	     m_MVA_TOPHLEPBB_JerUp = _trec->MVA_TOPHLEPBB_JerUp();
	     m_MVA_TOPTOPLEPHAD_JerUp = _trec->MVA_TOPTOPLEPHAD_JerUp();
	     m_LepCharge_JerUp = _v_Lepton->at(0).charge();
	     m_HiggsEta_TOPTOPLEPHBB_JerUp = _trec->Higgs_TOPTOPLEPHBB_JerUp_p4().PseudoRapidity();
	     m_HiggsEta_TOPHLEPBB_JerUp = _trec->Higgs_TOPHLEPBB_JerUp_p4().PseudoRapidity();
	     m_TopLepMass_TOPTOPLEPHBB_JerUp = _trec->TopLep_TOPTOPLEPHBB_JerUp_p4().M();
	     m_TopLepMass_TOPHLEPBB_JerUp = _trec->TopLep_TOPHLEPBB_JerUp_p4().M();
	     m_TopLepMass_TOPTOPLEPHAD_JerUp = _trec->TopLep_TOPTOPLEPHAD_JerUp_p4().M();
	     m_TopLepPt_TOPTOPLEPHBB_JerUp = _trec->TopLep_TOPTOPLEPHBB_JerUp_p4().Pt();
	     m_TopLepPt_TOPHLEPBB_JerUp = _trec->TopLep_TOPHLEPBB_JerUp_p4().Pt();
	     m_TopLepPt_TOPTOPLEPHAD_JerUp = _trec->TopLep_TOPTOPLEPHAD_JerUp_p4().Pt();
	     m_TopLepEta_TOPTOPLEPHBB_JerUp = _trec->TopLep_TOPTOPLEPHBB_JerUp_p4().PseudoRapidity();
	     m_TopLepEta_TOPHLEPBB_JerUp = _trec->TopLep_TOPHLEPBB_JerUp_p4().PseudoRapidity();
	     m_TopLepEta_TOPTOPLEPHAD_JerUp = _trec->TopLep_TOPTOPLEPHAD_JerUp_p4().PseudoRapidity();
	     m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JerUp = _trec->HiggsBJet1_TOPTOPLEPHBB_JerUp_p4().DeltaR(_trec->HiggsBJet2_TOPTOPLEPHBB_JerUp_p4());
	     m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JerUp = _trec->HiggsBJet1_TOPHLEPBB_JerUp_p4().DeltaR(_trec->HiggsBJet2_TOPHLEPBB_JerUp_p4());
	     m_TopLepHiggsDr_TOPTOPLEPHBB_JerUp = _trec->TopLep_TOPTOPLEPHBB_JerUp_p4().DeltaR(_trec->Higgs_TOPTOPLEPHBB_JerUp_p4());
	     m_TopLepHiggsDr_TOPHLEPBB_JerUp = _trec->TopLep_TOPHLEPBB_JerUp_p4().DeltaR(_trec->Higgs_TOPHLEPBB_JerUp_p4());
	     m_TopLepTopHadDr_TOPTOPLEPHAD_JerUp = _trec->TopLep_TOPTOPLEPHAD_JerUp_p4().DeltaR(_trec->TopHad_TOPTOPLEPHAD_JerUp_p4());
	     
	     m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JerUp = _trec->HiggsBJet1_TOPTOPLEPHBB_CSVv2();
	     m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JerUp = _trec->HiggsBJet2_TOPTOPLEPHBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPTOPLEPHBB_JerUp = _trec->TopLepBJet_TOPTOPLEPHBB_CSVv2();
	     m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JerUp = _trec->TopHadNonBJet_TOPTOPLEPHBB_CSVv2();
	     m_HiggsBJet1CSVv2_TOPHLEPBB_JerUp = _trec->HiggsBJet1_TOPHLEPBB_CSVv2();
	     m_HiggsBJet2CSVv2_TOPHLEPBB_JerUp = _trec->HiggsBJet2_TOPHLEPBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPHLEPBB_JerUp = _trec->TopLepBJet_TOPHLEPBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPTOPLEPHAD_JerUp = _trec->TopLepBJet_TOPTOPLEPHAD_CSVv2();
	     m_TopHadBJetCSVv2_TOPTOPLEPHAD_JerUp = _trec->TopHadBJet_TOPTOPLEPHAD_CSVv2();
	     m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JerUp = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2();
	     m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JerUp = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2();

	     // JerDown
	     m_HiggsMass_TOPTOPLEPHBB_JerDown = _trec->Higgs_TOPTOPLEPHBB_JerDown_p4().M();
	     m_HiggsMass_TOPHLEPBB_JerDown = _trec->Higgs_TOPHLEPBB_JerDown_p4().M();
	     m_TopHadMass_TOPTOPLEPHAD_JerDown = _trec->TopHad_TOPTOPLEPHAD_JerDown_p4().M();
	     m_chi2_TOPTOPLEPHBB_JerDown = _trec->chi2_TOPTOPLEPHBB();
	     m_chi2_TOPHLEPBB_JerDown = _trec->chi2_TOPHLEPBB();
	     m_chi2_TOPTOPLEPHAD_JerDown = _trec->chi2_TOPTOPLEPHAD();
	     m_MVA_TOPTOPLEPHBB_JerDown = _trec->MVA_TOPTOPLEPHBB_JerDown();
	     m_MVA_TOPHLEPBB_JerDown = _trec->MVA_TOPHLEPBB_JerDown();
	     m_MVA_TOPTOPLEPHAD_JerDown = _trec->MVA_TOPTOPLEPHAD_JerDown();
	     m_LepCharge_JerDown = _v_Lepton->at(0).charge();
	     m_HiggsEta_TOPTOPLEPHBB_JerDown = _trec->Higgs_TOPTOPLEPHBB_JerDown_p4().PseudoRapidity();
	     m_HiggsEta_TOPHLEPBB_JerDown = _trec->Higgs_TOPHLEPBB_JerDown_p4().PseudoRapidity();
	     m_TopLepMass_TOPTOPLEPHBB_JerDown = _trec->TopLep_TOPTOPLEPHBB_JerDown_p4().M();
	     m_TopLepMass_TOPHLEPBB_JerDown = _trec->TopLep_TOPHLEPBB_JerDown_p4().M();
	     m_TopLepMass_TOPTOPLEPHAD_JerDown = _trec->TopLep_TOPTOPLEPHAD_JerDown_p4().M();
	     m_TopLepPt_TOPTOPLEPHBB_JerDown = _trec->TopLep_TOPTOPLEPHBB_JerDown_p4().Pt();
	     m_TopLepPt_TOPHLEPBB_JerDown = _trec->TopLep_TOPHLEPBB_JerDown_p4().Pt();
	     m_TopLepPt_TOPTOPLEPHAD_JerDown = _trec->TopLep_TOPTOPLEPHAD_JerDown_p4().Pt();
	     m_TopLepEta_TOPTOPLEPHBB_JerDown = _trec->TopLep_TOPTOPLEPHBB_JerDown_p4().PseudoRapidity();
	     m_TopLepEta_TOPHLEPBB_JerDown = _trec->TopLep_TOPHLEPBB_JerDown_p4().PseudoRapidity();
	     m_TopLepEta_TOPTOPLEPHAD_JerDown = _trec->TopLep_TOPTOPLEPHAD_JerDown_p4().PseudoRapidity();
	     m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JerDown = _trec->HiggsBJet1_TOPTOPLEPHBB_JerDown_p4().DeltaR(_trec->HiggsBJet2_TOPTOPLEPHBB_JerDown_p4());
	     m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JerDown = _trec->HiggsBJet1_TOPHLEPBB_JerDown_p4().DeltaR(_trec->HiggsBJet2_TOPHLEPBB_JerDown_p4());
	     m_TopLepHiggsDr_TOPTOPLEPHBB_JerDown = _trec->TopLep_TOPTOPLEPHBB_JerDown_p4().DeltaR(_trec->Higgs_TOPTOPLEPHBB_JerDown_p4());
	     m_TopLepHiggsDr_TOPHLEPBB_JerDown = _trec->TopLep_TOPHLEPBB_JerDown_p4().DeltaR(_trec->Higgs_TOPHLEPBB_JerDown_p4());
	     m_TopLepTopHadDr_TOPTOPLEPHAD_JerDown = _trec->TopLep_TOPTOPLEPHAD_JerDown_p4().DeltaR(_trec->TopHad_TOPTOPLEPHAD_JerDown_p4());
	     
	     m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JerDown = _trec->HiggsBJet1_TOPTOPLEPHBB_CSVv2();
	     m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JerDown = _trec->HiggsBJet2_TOPTOPLEPHBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPTOPLEPHBB_JerDown = _trec->TopLepBJet_TOPTOPLEPHBB_CSVv2();
	     m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JerDown = _trec->TopHadNonBJet_TOPTOPLEPHBB_CSVv2();
	     m_HiggsBJet1CSVv2_TOPHLEPBB_JerDown = _trec->HiggsBJet1_TOPHLEPBB_CSVv2();
	     m_HiggsBJet2CSVv2_TOPHLEPBB_JerDown = _trec->HiggsBJet2_TOPHLEPBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPHLEPBB_JerDown = _trec->TopLepBJet_TOPHLEPBB_CSVv2();
	     m_TopLepBJetCSVv2_TOPTOPLEPHAD_JerDown = _trec->TopLepBJet_TOPTOPLEPHAD_CSVv2();
	     m_TopHadBJetCSVv2_TOPTOPLEPHAD_JerDown = _trec->TopHadBJet_TOPTOPLEPHAD_CSVv2();
	     m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JerDown = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2();
	     m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JerDown = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2();
	  }

	// nominal
	_mva->setVariable_HiggsMass_TOPHLEPBB(m_HiggsMass_TOPHLEPBB);
	_mva->setVariable_TopHadMass_TOPTOPLEPHAD(m_TopHadMass_TOPTOPLEPHAD);
	_mva->setVariable_MVA_TOPHLEPBB(m_MVA_TOPHLEPBB);
	_mva->setVariable_MVA_TOPTOPLEPHAD(m_MVA_TOPTOPLEPHAD);
	_mva->setVariable_LepCharge(m_LepCharge);
	_mva->setVariable_HiggsEta_TOPHLEPBB(m_HiggsEta_TOPHLEPBB);
	_mva->setVariable_TopLepMass_TOPHLEPBB(m_TopLepMass_TOPHLEPBB);
	_mva->setVariable_TopLepMass_TOPTOPLEPHAD(m_TopLepMass_TOPTOPLEPHAD);
	_mva->setVariable_TopLepPt_TOPHLEPBB(m_TopLepPt_TOPHLEPBB);
	_mva->setVariable_TopLepEta_TOPHLEPBB(m_TopLepEta_TOPHLEPBB);
	_mva->setVariable_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB(m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	_mva->setVariable_TopLepHiggsDr_TOPHLEPBB(m_TopLepHiggsDr_TOPHLEPBB);
	_mva->setVariable_TopLepTopHadDr_TOPTOPLEPHAD(m_TopLepTopHadDr_TOPTOPLEPHAD);	
	_mva->setVariable_HiggsMass_TOPTOPLEPHBB(m_HiggsMass_TOPTOPLEPHBB);
	_mva->setVariable_MVA_TOPTOPLEPHBB(m_MVA_TOPTOPLEPHBB);
	_mva->setVariable_HiggsEta_TOPTOPLEPHBB(m_HiggsEta_TOPTOPLEPHBB);
	_mva->setVariable_TopLepMass_TOPTOPLEPHBB(m_TopLepMass_TOPTOPLEPHBB);
	_mva->setVariable_TopLepPt_TOPTOPLEPHBB(m_TopLepPt_TOPTOPLEPHBB);
	_mva->setVariable_TopLepEta_TOPTOPLEPHBB(m_TopLepEta_TOPTOPLEPHBB);
	_mva->setVariable_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB(m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB);
	_mva->setVariable_TopLepHiggsDr_TOPTOPLEPHBB(m_TopLepHiggsDr_TOPTOPLEPHBB);
	_mva->setVariable_HiggsBJet1CSVv2_TOPHLEPBB(m_HiggsBJet1CSVv2_TOPHLEPBB);
	_mva->setVariable_HiggsBJet2CSVv2_TOPHLEPBB(m_HiggsBJet2CSVv2_TOPHLEPBB);
	_mva->setVariable_TopLepBJetCSVv2_TOPHLEPBB(m_TopLepBJetCSVv2_TOPHLEPBB);
	_mva->setVariable_HiggsBJet1CSVv2_TOPTOPLEPHBB(m_HiggsBJet1CSVv2_TOPTOPLEPHBB);
	_mva->setVariable_HiggsBJet2CSVv2_TOPTOPLEPHBB(m_HiggsBJet2CSVv2_TOPTOPLEPHBB);
	_mva->setVariable_TopLepBJetCSVv2_TOPTOPLEPHBB(m_TopLepBJetCSVv2_TOPTOPLEPHBB);
	_mva->setVariable_TopHadNonBJetCSVv2_TOPTOPLEPHBB(m_TopHadNonBJetCSVv2_TOPTOPLEPHBB);
	_mva->setVariable_TopLepBJetCSVv2_TOPTOPLEPHAD(m_TopLepBJetCSVv2_TOPTOPLEPHAD);
	_mva->setVariable_TopHadBJetCSVv2_TOPTOPLEPHAD(m_TopHadBJetCSVv2_TOPTOPLEPHAD);
	_mva->setVariable_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD(m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD);
	_mva->setVariable_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD(m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD);

	if( !isData ) 
	  {	     
	     // JesUp
	     _mvaJesUp->setVariable_HiggsMass_TOPHLEPBB(m_HiggsMass_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_TopHadMass_TOPTOPLEPHAD(m_TopHadMass_TOPTOPLEPHAD_JesUp);
	     _mvaJesUp->setVariable_MVA_TOPHLEPBB(m_MVA_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_MVA_TOPTOPLEPHAD(m_MVA_TOPTOPLEPHAD_JesUp);
	     _mvaJesUp->setVariable_LepCharge(m_LepCharge_JesUp);
	     _mvaJesUp->setVariable_HiggsEta_TOPHLEPBB(m_HiggsEta_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_TopLepMass_TOPHLEPBB(m_TopLepMass_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_TopLepMass_TOPTOPLEPHAD(m_TopLepMass_TOPTOPLEPHAD_JesUp);
	     _mvaJesUp->setVariable_TopLepPt_TOPHLEPBB(m_TopLepPt_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_TopLepEta_TOPHLEPBB(m_TopLepEta_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB(m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_TopLepHiggsDr_TOPHLEPBB(m_TopLepHiggsDr_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_TopLepTopHadDr_TOPTOPLEPHAD(m_TopLepTopHadDr_TOPTOPLEPHAD_JesUp);	
	     _mvaJesUp->setVariable_HiggsMass_TOPTOPLEPHBB(m_HiggsMass_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_MVA_TOPTOPLEPHBB(m_MVA_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_HiggsEta_TOPTOPLEPHBB(m_HiggsEta_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_TopLepMass_TOPTOPLEPHBB(m_TopLepMass_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_TopLepPt_TOPTOPLEPHBB(m_TopLepPt_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_TopLepEta_TOPTOPLEPHBB(m_TopLepEta_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB(m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_TopLepHiggsDr_TOPTOPLEPHBB(m_TopLepHiggsDr_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_HiggsBJet1CSVv2_TOPHLEPBB(m_HiggsBJet1CSVv2_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_HiggsBJet2CSVv2_TOPHLEPBB(m_HiggsBJet2CSVv2_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_TopLepBJetCSVv2_TOPHLEPBB(m_TopLepBJetCSVv2_TOPHLEPBB_JesUp);
	     _mvaJesUp->setVariable_HiggsBJet1CSVv2_TOPTOPLEPHBB(m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_HiggsBJet2CSVv2_TOPTOPLEPHBB(m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_TopLepBJetCSVv2_TOPTOPLEPHBB(m_TopLepBJetCSVv2_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_TopHadNonBJetCSVv2_TOPTOPLEPHBB(m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JesUp);
	     _mvaJesUp->setVariable_TopLepBJetCSVv2_TOPTOPLEPHAD(m_TopLepBJetCSVv2_TOPTOPLEPHAD_JesUp);
	     _mvaJesUp->setVariable_TopHadBJetCSVv2_TOPTOPLEPHAD(m_TopHadBJetCSVv2_TOPTOPLEPHAD_JesUp);
	     _mvaJesUp->setVariable_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD(m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JesUp);
	     _mvaJesUp->setVariable_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD(m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JesUp);
	     
	     // JesDown
	     _mvaJesDown->setVariable_HiggsMass_TOPHLEPBB(m_HiggsMass_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_TopHadMass_TOPTOPLEPHAD(m_TopHadMass_TOPTOPLEPHAD_JesDown);
	     _mvaJesDown->setVariable_MVA_TOPHLEPBB(m_MVA_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_MVA_TOPTOPLEPHAD(m_MVA_TOPTOPLEPHAD_JesDown);
	     _mvaJesDown->setVariable_LepCharge(m_LepCharge_JesDown);
	     _mvaJesDown->setVariable_HiggsEta_TOPHLEPBB(m_HiggsEta_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_TopLepMass_TOPHLEPBB(m_TopLepMass_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_TopLepMass_TOPTOPLEPHAD(m_TopLepMass_TOPTOPLEPHAD_JesDown);
	     _mvaJesDown->setVariable_TopLepPt_TOPHLEPBB(m_TopLepPt_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_TopLepEta_TOPHLEPBB(m_TopLepEta_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB(m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_TopLepHiggsDr_TOPHLEPBB(m_TopLepHiggsDr_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_TopLepTopHadDr_TOPTOPLEPHAD(m_TopLepTopHadDr_TOPTOPLEPHAD_JesDown);
	     _mvaJesDown->setVariable_HiggsMass_TOPTOPLEPHBB(m_HiggsMass_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_MVA_TOPTOPLEPHBB(m_MVA_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_HiggsEta_TOPTOPLEPHBB(m_HiggsEta_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_TopLepMass_TOPTOPLEPHBB(m_TopLepMass_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_TopLepPt_TOPTOPLEPHBB(m_TopLepPt_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_TopLepEta_TOPTOPLEPHBB(m_TopLepEta_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB(m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_TopLepHiggsDr_TOPTOPLEPHBB(m_TopLepHiggsDr_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_HiggsBJet1CSVv2_TOPHLEPBB(m_HiggsBJet1CSVv2_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_HiggsBJet2CSVv2_TOPHLEPBB(m_HiggsBJet2CSVv2_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_TopLepBJetCSVv2_TOPHLEPBB(m_TopLepBJetCSVv2_TOPHLEPBB_JesDown);
	     _mvaJesDown->setVariable_HiggsBJet1CSVv2_TOPTOPLEPHBB(m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_HiggsBJet2CSVv2_TOPTOPLEPHBB(m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_TopLepBJetCSVv2_TOPTOPLEPHBB(m_TopLepBJetCSVv2_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_TopHadNonBJetCSVv2_TOPTOPLEPHBB(m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JesDown);
	     _mvaJesDown->setVariable_TopLepBJetCSVv2_TOPTOPLEPHAD(m_TopLepBJetCSVv2_TOPTOPLEPHAD_JesDown);
	     _mvaJesDown->setVariable_TopHadBJetCSVv2_TOPTOPLEPHAD(m_TopHadBJetCSVv2_TOPTOPLEPHAD_JesDown);
	     _mvaJesDown->setVariable_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD(m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JesDown);
	     _mvaJesDown->setVariable_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD(m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JesDown);

	     // JerUp
	     _mvaJerUp->setVariable_HiggsMass_TOPHLEPBB(m_HiggsMass_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_TopHadMass_TOPTOPLEPHAD(m_TopHadMass_TOPTOPLEPHAD_JerUp);
	     _mvaJerUp->setVariable_MVA_TOPHLEPBB(m_MVA_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_MVA_TOPTOPLEPHAD(m_MVA_TOPTOPLEPHAD_JerUp);
	     _mvaJerUp->setVariable_LepCharge(m_LepCharge_JerUp);
	     _mvaJerUp->setVariable_HiggsEta_TOPHLEPBB(m_HiggsEta_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_TopLepMass_TOPHLEPBB(m_TopLepMass_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_TopLepMass_TOPTOPLEPHAD(m_TopLepMass_TOPTOPLEPHAD_JerUp);
	     _mvaJerUp->setVariable_TopLepPt_TOPHLEPBB(m_TopLepPt_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_TopLepEta_TOPHLEPBB(m_TopLepEta_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB(m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_TopLepHiggsDr_TOPHLEPBB(m_TopLepHiggsDr_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_TopLepTopHadDr_TOPTOPLEPHAD(m_TopLepTopHadDr_TOPTOPLEPHAD_JerUp);	
	     _mvaJerUp->setVariable_HiggsMass_TOPTOPLEPHBB(m_HiggsMass_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_MVA_TOPTOPLEPHBB(m_MVA_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_HiggsEta_TOPTOPLEPHBB(m_HiggsEta_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_TopLepMass_TOPTOPLEPHBB(m_TopLepMass_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_TopLepPt_TOPTOPLEPHBB(m_TopLepPt_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_TopLepEta_TOPTOPLEPHBB(m_TopLepEta_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB(m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_TopLepHiggsDr_TOPTOPLEPHBB(m_TopLepHiggsDr_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_HiggsBJet1CSVv2_TOPHLEPBB(m_HiggsBJet1CSVv2_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_HiggsBJet2CSVv2_TOPHLEPBB(m_HiggsBJet2CSVv2_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_TopLepBJetCSVv2_TOPHLEPBB(m_TopLepBJetCSVv2_TOPHLEPBB_JerUp);
	     _mvaJerUp->setVariable_HiggsBJet1CSVv2_TOPTOPLEPHBB(m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_HiggsBJet2CSVv2_TOPTOPLEPHBB(m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_TopLepBJetCSVv2_TOPTOPLEPHBB(m_TopLepBJetCSVv2_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_TopHadNonBJetCSVv2_TOPTOPLEPHBB(m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JerUp);
	     _mvaJerUp->setVariable_TopLepBJetCSVv2_TOPTOPLEPHAD(m_TopLepBJetCSVv2_TOPTOPLEPHAD_JerUp);
	     _mvaJerUp->setVariable_TopHadBJetCSVv2_TOPTOPLEPHAD(m_TopHadBJetCSVv2_TOPTOPLEPHAD_JerUp);
	     _mvaJerUp->setVariable_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD(m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JerUp);
	     _mvaJerUp->setVariable_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD(m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JerUp);

	     // JerDown
	     _mvaJerDown->setVariable_HiggsMass_TOPHLEPBB(m_HiggsMass_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_TopHadMass_TOPTOPLEPHAD(m_TopHadMass_TOPTOPLEPHAD_JerDown);
	     _mvaJerDown->setVariable_MVA_TOPHLEPBB(m_MVA_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_MVA_TOPTOPLEPHAD(m_MVA_TOPTOPLEPHAD_JerDown);
	     _mvaJerDown->setVariable_LepCharge(m_LepCharge_JerDown);
	     _mvaJerDown->setVariable_HiggsEta_TOPHLEPBB(m_HiggsEta_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_TopLepMass_TOPHLEPBB(m_TopLepMass_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_TopLepMass_TOPTOPLEPHAD(m_TopLepMass_TOPTOPLEPHAD_JerDown);
	     _mvaJerDown->setVariable_TopLepPt_TOPHLEPBB(m_TopLepPt_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_TopLepEta_TOPHLEPBB(m_TopLepEta_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB(m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_TopLepHiggsDr_TOPHLEPBB(m_TopLepHiggsDr_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_TopLepTopHadDr_TOPTOPLEPHAD(m_TopLepTopHadDr_TOPTOPLEPHAD_JerDown);
	     _mvaJerDown->setVariable_HiggsMass_TOPTOPLEPHBB(m_HiggsMass_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_MVA_TOPTOPLEPHBB(m_MVA_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_HiggsEta_TOPTOPLEPHBB(m_HiggsEta_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_TopLepMass_TOPTOPLEPHBB(m_TopLepMass_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_TopLepPt_TOPTOPLEPHBB(m_TopLepPt_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_TopLepEta_TOPTOPLEPHBB(m_TopLepEta_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB(m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_TopLepHiggsDr_TOPTOPLEPHBB(m_TopLepHiggsDr_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_HiggsBJet1CSVv2_TOPHLEPBB(m_HiggsBJet1CSVv2_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_HiggsBJet2CSVv2_TOPHLEPBB(m_HiggsBJet2CSVv2_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_TopLepBJetCSVv2_TOPHLEPBB(m_TopLepBJetCSVv2_TOPHLEPBB_JerDown);
	     _mvaJerDown->setVariable_HiggsBJet1CSVv2_TOPTOPLEPHBB(m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_HiggsBJet2CSVv2_TOPTOPLEPHBB(m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_TopLepBJetCSVv2_TOPTOPLEPHBB(m_TopLepBJetCSVv2_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_TopHadNonBJetCSVv2_TOPTOPLEPHBB(m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JerDown);
	     _mvaJerDown->setVariable_TopLepBJetCSVv2_TOPTOPLEPHAD(m_TopLepBJetCSVv2_TOPTOPLEPHAD_JerDown);
	     _mvaJerDown->setVariable_TopHadBJetCSVv2_TOPTOPLEPHAD(m_TopHadBJetCSVv2_TOPTOPLEPHAD_JerDown);
	     _mvaJerDown->setVariable_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD(m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JerDown);
	     _mvaJerDown->setVariable_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD(m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JerDown);
	  }	
	
	// Evaluate MVA discriminator
	
	// nominal
	_mvab0j3HutST = _mva->run("b0j3HutST");
	_mvab0j3HctST = _mva->run("b0j3HctST");
	_mvab0j3HutTT = _mva->run("b0j3HutTT");
	_mvab0j3HctTT = _mva->run("b0j3HctTT");

	_mvab0j4HutST = _mva->run("b0j4HutST");
	_mvab0j4HctST = _mva->run("b0j4HctST");
	_mvab0j4HutTT = _mva->run("b0j4HutTT");
	_mvab0j4HctTT = _mva->run("b0j4HctTT");

	_mvab1j3HutST = _mva->run("b1j3HutST");
	_mvab1j3HctST = _mva->run("b1j3HctST");
	_mvab1j3HutTT = _mva->run("b1j3HutTT");
	_mvab1j3HctTT = _mva->run("b1j3HctTT");

	_mvab1j4HutST = _mva->run("b1j4HutST");
	_mvab1j4HctST = _mva->run("b1j4HctST");
	_mvab1j4HutTT = _mva->run("b1j4HutTT");
	_mvab1j4HctTT = _mva->run("b1j4HctTT");

	_mvab2j3HutST = _mva->run("b2j3HutST");
	_mvab2j3HctST = _mva->run("b2j3HctST");
	_mvab2j3HutTT = _mva->run("b2j3HutTT");
	_mvab2j3HctTT = _mva->run("b2j3HctTT");

	_mvab2j4HutST = _mva->run("b2j4HutST");
	_mvab2j4HctST = _mva->run("b2j4HctST");
	_mvab2j4HutTT = _mva->run("b2j4HutTT");
	_mvab2j4HctTT = _mva->run("b2j4HctTT");

	_mvab3j3HutST = _mva->run("b3j3HutST");
	_mvab3j3HctST = _mva->run("b3j3HctST");
	_mvab3j3HutTT = _mva->run("b3j3HutTT");
	_mvab3j3HctTT = _mva->run("b3j3HctTT");

	_mvab3j4HutST = _mva->run("b3j4HutST");
	_mvab3j4HctST = _mva->run("b3j4HctST");
	_mvab3j4HutTT = _mva->run("b3j4HutTT");
	_mvab3j4HctTT = _mva->run("b3j4HctTT");

	_mvab4j4HutST = _mva->run("b4j4HutST");
	_mvab4j4HctST = _mva->run("b4j4HctST");
	_mvab4j4HutTT = _mva->run("b4j4HutTT");
	_mvab4j4HctTT = _mva->run("b4j4HctTT");

	if( !isData ) 
	  {	     
	     // JesUp
	     _mvab0j3HutSTJesUp = _mvaJesUp->run("b0j3HutST");
	     _mvab0j3HctSTJesUp = _mvaJesUp->run("b0j3HctST");
	     _mvab0j3HutTTJesUp = _mvaJesUp->run("b0j3HutTT");
	     _mvab0j3HctTTJesUp = _mvaJesUp->run("b0j3HctTT");
	     
	     _mvab0j4HutSTJesUp = _mvaJesUp->run("b0j4HutST");
	     _mvab0j4HctSTJesUp = _mvaJesUp->run("b0j4HctST");
	     _mvab0j4HutTTJesUp = _mvaJesUp->run("b0j4HutTT");
	     _mvab0j4HctTTJesUp = _mvaJesUp->run("b0j4HctTT");
	     
	     _mvab1j3HutSTJesUp = _mvaJesUp->run("b1j3HutST");
	     _mvab1j3HctSTJesUp = _mvaJesUp->run("b1j3HctST");
	     _mvab1j3HutTTJesUp = _mvaJesUp->run("b1j3HutTT");
	     _mvab1j3HctTTJesUp = _mvaJesUp->run("b1j3HctTT");
	     
	     _mvab1j4HutSTJesUp = _mvaJesUp->run("b1j4HutST");
	     _mvab1j4HctSTJesUp = _mvaJesUp->run("b1j4HctST");
	     _mvab1j4HutTTJesUp = _mvaJesUp->run("b1j4HutTT");
	     _mvab1j4HctTTJesUp = _mvaJesUp->run("b1j4HctTT");
	     
	     _mvab2j3HutSTJesUp = _mvaJesUp->run("b2j3HutST");
	     _mvab2j3HctSTJesUp = _mvaJesUp->run("b2j3HctST");
	     _mvab2j3HutTTJesUp = _mvaJesUp->run("b2j3HutTT");
	     _mvab2j3HctTTJesUp = _mvaJesUp->run("b2j3HctTT");
	     
	     _mvab2j4HutSTJesUp = _mvaJesUp->run("b2j4HutST");
	     _mvab2j4HctSTJesUp = _mvaJesUp->run("b2j4HctST");
	     _mvab2j4HutTTJesUp = _mvaJesUp->run("b2j4HutTT");
	     _mvab2j4HctTTJesUp = _mvaJesUp->run("b2j4HctTT");
	     
	     _mvab3j3HutSTJesUp = _mvaJesUp->run("b3j3HutST");
	     _mvab3j3HctSTJesUp = _mvaJesUp->run("b3j3HctST");
	     _mvab3j3HutTTJesUp = _mvaJesUp->run("b3j3HutTT");
	     _mvab3j3HctTTJesUp = _mvaJesUp->run("b3j3HctTT");

	     _mvab3j4HutSTJesUp = _mvaJesUp->run("b3j4HutST");
	     _mvab3j4HctSTJesUp = _mvaJesUp->run("b3j4HctST");
	     _mvab3j4HutTTJesUp = _mvaJesUp->run("b3j4HutTT");
	     _mvab3j4HctTTJesUp = _mvaJesUp->run("b3j4HctTT");
	     
	     _mvab4j4HutSTJesUp = _mvaJesUp->run("b4j4HutST");
	     _mvab4j4HctSTJesUp = _mvaJesUp->run("b4j4HctST");
	     _mvab4j4HutTTJesUp = _mvaJesUp->run("b4j4HutTT");
	     _mvab4j4HctTTJesUp = _mvaJesUp->run("b4j4HctTT");

	     // JesDown
	     _mvab0j3HutSTJesDown = _mvaJesDown->run("b0j3HutST");
	     _mvab0j3HctSTJesDown = _mvaJesDown->run("b0j3HctST");
	     _mvab0j3HutTTJesDown = _mvaJesDown->run("b0j3HutTT");
	     _mvab0j3HctTTJesDown = _mvaJesDown->run("b0j3HctTT");

	     _mvab0j4HutSTJesDown = _mvaJesDown->run("b0j4HutST");
	     _mvab0j4HctSTJesDown = _mvaJesDown->run("b0j4HctST");
	     _mvab0j4HutTTJesDown = _mvaJesDown->run("b0j4HutTT");
	     _mvab0j4HctTTJesDown = _mvaJesDown->run("b0j4HctTT");
	     
	     _mvab1j3HutSTJesDown = _mvaJesDown->run("b1j3HutST");
	     _mvab1j3HctSTJesDown = _mvaJesDown->run("b1j3HctST");
	     _mvab1j3HutTTJesDown = _mvaJesDown->run("b1j3HutTT");
	     _mvab1j3HctTTJesDown = _mvaJesDown->run("b1j3HctTT");
	     
	     _mvab1j4HutSTJesDown = _mvaJesDown->run("b1j4HutST");
	     _mvab1j4HctSTJesDown = _mvaJesDown->run("b1j4HctST");
	     _mvab1j4HutTTJesDown = _mvaJesDown->run("b1j4HutTT");
	     _mvab1j4HctTTJesDown = _mvaJesDown->run("b1j4HctTT");
	     
	     _mvab2j3HutSTJesDown = _mvaJesDown->run("b2j3HutST");
	     _mvab2j3HctSTJesDown = _mvaJesDown->run("b2j3HctST");
	     _mvab2j3HutTTJesDown = _mvaJesDown->run("b2j3HutTT");
	     _mvab2j3HctTTJesDown = _mvaJesDown->run("b2j3HctTT");
	     
	     _mvab2j4HutSTJesDown = _mvaJesDown->run("b2j4HutST");
	     _mvab2j4HctSTJesDown = _mvaJesDown->run("b2j4HctST");
	     _mvab2j4HutTTJesDown = _mvaJesDown->run("b2j4HutTT");
	     _mvab2j4HctTTJesDown = _mvaJesDown->run("b2j4HctTT");
	     
	     _mvab3j3HutSTJesDown = _mvaJesDown->run("b3j3HutST");
	     _mvab3j3HctSTJesDown = _mvaJesDown->run("b3j3HctST");
	     _mvab3j3HutTTJesDown = _mvaJesDown->run("b3j3HutTT");
	     _mvab3j3HctTTJesDown = _mvaJesDown->run("b3j3HctTT");
	     
	     _mvab3j4HutSTJesDown = _mvaJesDown->run("b3j4HutST");
	     _mvab3j4HctSTJesDown = _mvaJesDown->run("b3j4HctST");
	     _mvab3j4HutTTJesDown = _mvaJesDown->run("b3j4HutTT");
	     _mvab3j4HctTTJesDown = _mvaJesDown->run("b3j4HctTT");
	     
	     _mvab4j4HutSTJesDown = _mvaJesDown->run("b4j4HutST");
	     _mvab4j4HctSTJesDown = _mvaJesDown->run("b4j4HctST");
	     _mvab4j4HutTTJesDown = _mvaJesDown->run("b4j4HutTT");
	     _mvab4j4HctTTJesDown = _mvaJesDown->run("b4j4HctTT");

	     // JerUp
	     _mvab0j3HutSTJerUp = _mvaJerUp->run("b0j3HutST");
	     _mvab0j3HctSTJerUp = _mvaJerUp->run("b0j3HctST");
	     _mvab0j3HutTTJerUp = _mvaJerUp->run("b0j3HutTT");
	     _mvab0j3HctTTJerUp = _mvaJerUp->run("b0j3HctTT");

	     _mvab0j4HutSTJerUp = _mvaJerUp->run("b0j4HutST");
	     _mvab0j4HctSTJerUp = _mvaJerUp->run("b0j4HctST");
	     _mvab0j4HutTTJerUp = _mvaJerUp->run("b0j4HutTT");
	     _mvab0j4HctTTJerUp = _mvaJerUp->run("b0j4HctTT");
	     
	     _mvab1j3HutSTJerUp = _mvaJerUp->run("b1j3HutST");
	     _mvab1j3HctSTJerUp = _mvaJerUp->run("b1j3HctST");
	     _mvab1j3HutTTJerUp = _mvaJerUp->run("b1j3HutTT");
	     _mvab1j3HctTTJerUp = _mvaJerUp->run("b1j3HctTT");
	     
	     _mvab1j4HutSTJerUp = _mvaJerUp->run("b1j4HutST");
	     _mvab1j4HctSTJerUp = _mvaJerUp->run("b1j4HctST");
	     _mvab1j4HutTTJerUp = _mvaJerUp->run("b1j4HutTT");
	     _mvab1j4HctTTJerUp = _mvaJerUp->run("b1j4HctTT");
	     
	     _mvab2j3HutSTJerUp = _mvaJerUp->run("b2j3HutST");
	     _mvab2j3HctSTJerUp = _mvaJerUp->run("b2j3HctST");
	     _mvab2j3HutTTJerUp = _mvaJerUp->run("b2j3HutTT");
	     _mvab2j3HctTTJerUp = _mvaJerUp->run("b2j3HctTT");
	     
	     _mvab2j4HutSTJerUp = _mvaJerUp->run("b2j4HutST");
	     _mvab2j4HctSTJerUp = _mvaJerUp->run("b2j4HctST");
	     _mvab2j4HutTTJerUp = _mvaJerUp->run("b2j4HutTT");
	     _mvab2j4HctTTJerUp = _mvaJerUp->run("b2j4HctTT");
	     
	     _mvab3j3HutSTJerUp = _mvaJerUp->run("b3j3HutST");
	     _mvab3j3HctSTJerUp = _mvaJerUp->run("b3j3HctST");
	     _mvab3j3HutTTJerUp = _mvaJerUp->run("b3j3HutTT");
	     _mvab3j3HctTTJerUp = _mvaJerUp->run("b3j3HctTT");
	     
	     _mvab3j4HutSTJerUp = _mvaJerUp->run("b3j4HutST");
	     _mvab3j4HctSTJerUp = _mvaJerUp->run("b3j4HctST");
	     _mvab3j4HutTTJerUp = _mvaJerUp->run("b3j4HutTT");
	     _mvab3j4HctTTJerUp = _mvaJerUp->run("b3j4HctTT");
	     
	     _mvab4j4HutSTJerUp = _mvaJerUp->run("b4j4HutST");
	     _mvab4j4HctSTJerUp = _mvaJerUp->run("b4j4HctST");
	     _mvab4j4HutTTJerUp = _mvaJerUp->run("b4j4HutTT");
	     _mvab4j4HctTTJerUp = _mvaJerUp->run("b4j4HctTT");

	     // JerDown
	     _mvab0j3HutSTJerDown = _mvaJerDown->run("b0j3HutST");
	     _mvab0j3HctSTJerDown = _mvaJerDown->run("b0j3HctST");
	     _mvab0j3HutTTJerDown = _mvaJerDown->run("b0j3HutTT");
	     _mvab0j3HctTTJerDown = _mvaJerDown->run("b0j3HctTT");
	     
	     _mvab0j4HutSTJerDown = _mvaJerDown->run("b0j4HutST");
	     _mvab0j4HctSTJerDown = _mvaJerDown->run("b0j4HctST");
	     _mvab0j4HutTTJerDown = _mvaJerDown->run("b0j4HutTT");
	     _mvab0j4HctTTJerDown = _mvaJerDown->run("b0j4HctTT");

	     _mvab1j3HutSTJerDown = _mvaJerDown->run("b1j3HutST");
	     _mvab1j3HctSTJerDown = _mvaJerDown->run("b1j3HctST");
	     _mvab1j3HutTTJerDown = _mvaJerDown->run("b1j3HutTT");
	     _mvab1j3HctTTJerDown = _mvaJerDown->run("b1j3HctTT");
	     
	     _mvab1j4HutSTJerDown = _mvaJerDown->run("b1j4HutST");
	     _mvab1j4HctSTJerDown = _mvaJerDown->run("b1j4HctST");
	     _mvab1j4HutTTJerDown = _mvaJerDown->run("b1j4HutTT");
	     _mvab1j4HctTTJerDown = _mvaJerDown->run("b1j4HctTT");
	     
	     _mvab2j3HutSTJerDown = _mvaJerDown->run("b2j3HutST");
	     _mvab2j3HctSTJerDown = _mvaJerDown->run("b2j3HctST");
	     _mvab2j3HutTTJerDown = _mvaJerDown->run("b2j3HutTT");
	     _mvab2j3HctTTJerDown = _mvaJerDown->run("b2j3HctTT");
	     
	     _mvab2j4HutSTJerDown = _mvaJerDown->run("b2j4HutST");
	     _mvab2j4HctSTJerDown = _mvaJerDown->run("b2j4HctST");
	     _mvab2j4HutTTJerDown = _mvaJerDown->run("b2j4HutTT");
	     _mvab2j4HctTTJerDown = _mvaJerDown->run("b2j4HctTT");
	     
	     _mvab3j3HutSTJerDown = _mvaJerDown->run("b3j3HutST");
	     _mvab3j3HctSTJerDown = _mvaJerDown->run("b3j3HctST");
	     _mvab3j3HutTTJerDown = _mvaJerDown->run("b3j3HutTT");
	     _mvab3j3HctTTJerDown = _mvaJerDown->run("b3j3HctTT");
	     
	     _mvab3j4HutSTJerDown = _mvaJerDown->run("b3j4HutST");
	     _mvab3j4HctSTJerDown = _mvaJerDown->run("b3j4HctST");
	     _mvab3j4HutTTJerDown = _mvaJerDown->run("b3j4HutTT");
	     _mvab3j4HctTTJerDown = _mvaJerDown->run("b3j4HctTT");
	     
	     _mvab4j4HutSTJerDown = _mvaJerDown->run("b4j4HutST");
	     _mvab4j4HctSTJerDown = _mvaJerDown->run("b4j4HctST");
	     _mvab4j4HutTTJerDown = _mvaJerDown->run("b4j4HutTT");
	     _mvab4j4HctTTJerDown = _mvaJerDown->run("b4j4HctTT");
	  }
	
	bool sel_pass[sel_n];
	for(int c=0;c<sel_n;c++)
	  {	
	     sel_pass[c] = 0;
	     
//	     bool isSR1 = (sel[c] == "b0j3" && nbjets == 0 && njets == 3);
//	     bool isSR2 = (sel[c] == "b0j4" && nbjets == 0 && njets >= 4);
//	     bool isSR3 = (sel[c] == "b1j3" && nbjets == 1 && njets == 3);
//	     bool isSR4 = (sel[c] == "b1j4" && nbjets == 1 && njets >= 4);
	     bool isSR5 = (sel[c] == "b2j3" && nbjets == 2 && njets == 3);
	     bool isSR6 = (sel[c] == "b2j4" && nbjets == 2 && njets >= 4);
	     bool isSR7 = (sel[c] == "b3j3" && nbjets == 3 && njets == 3);
	     bool isSR8 = (sel[c] == "b3j4" && nbjets == 3 && njets >= 4);
	     bool isSR9 = (sel[c] == "b4j4" && nbjets >= 4 && njets >= 4);
	     bool isANY = (sel[c] == "ALL");
	     
//	     if( isSR1 ) idxSR = 0;
//	     else if( isSR2 ) idxSR = 1;
//	     else if( isSR3 ) idxSR = 2;
//	     else if( isSR4 ) idxSR = 3;
	     if( isSR5 ) idxSR = 0;
	     else if( isSR6 ) idxSR = 1;
	     else if( isSR7 ) idxSR = 2;
	     else if( isSR8 ) idxSR = 3;
	     else if( isSR9 ) idxSR = 4;
	     
//	     if( isSR1 || isSR2 || isSR3 || isSR4 || isSR5 || isSR6 || isSR7 || isSR8 || isSR9 || isANY )
	     if( isSR5 || isSR6 || isSR7 || isSR8 || isSR9 || isANY )
	       sel_pass[c] = 1;
	  }   
	
	float w0 = w;
	
	if( !isData )
	  {	
	     float SfIterativeFit = 1.;
	     
	     int nJet = _v_JetTight->size();
	     
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitCentral();
	       }
	     
	     w *= SfIterativeFit;	
	  }
	
	m_weight = w;
	
	for(int isys=0;isys<sys_n;isys++)
	  {	
	     double sfj0 = w0;
	     double sfj = w;
	     
	     // 1d
	     std::vector<std::string> histNAMESSEL;
	     std::vector<int> histSYS;
	     std::vector<int> histVAR;
	     std::vector<int> histSEL;
	     
	     for(int ih=0;ih<histname_n;ih++)
	       {
		  for(int ic=0;ic<chan_n;ic++)
		    {
		       if( !chan_pass[ic] ) continue;
		       
		       for(int is=0;is<sel_n;is++)
			 {
			    if( !sel_pass[is] ) continue;

			    for(int it=0;it<type_n;it++)
			      {
				 if( !type_pass[it] ) continue;
				 
				 if( ih == 0 && isys == 0 )
				   {
				      fillTree(ic,is);
				   }
				 
				 // [CHAN][TYPE][SEL][VAR][2*(NSYS-1)+1]
//				 histNAMESSEL.push_back(histNAMES[ic][0][is][ih][isys]);
				 histNAMESSEL.push_back(histNAMES[ic][it][is][ih][isys]);
				 histSYS.push_back(isys);
				 histVAR.push_back(ih);
				 histSEL.push_back(is);
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
		  fillHisto1D(h,sfj0,sfj,sys[histSYS[hidx]],0,varName,isData,histSEL[hidx],idxSR);
	       }
	  }
     }
}

void Hist::close()
{
   _fout->Write();
   _fout->Close();
   if( _evec ) fclose(_fevc);
   if( _evec ) _fevcVal.close();
   
//   delete rnd;
}

void Hist::fillTree(int ic,int is)
{
   _trout[ic][is]->Fill();
}

void Hist::printout(bool doPrint,
		    int run,int lumi,int id,
		    int lepId,float lepPt,float lepEta,float lepPhi,
		    float metpt,float metphi,
		    int njets,int nbjets,
		    float jetPt,float jetEta,float jetPhi)
{
   if( CHECK_BIT(passSel_ev,6) )
     {
	fprintf(_fevc,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %6.1f  %+4.2f    %d %d  %6.2f %+4.2f %+4.2f \n",
		run, lumi, id,
		lepId, lepPt, lepEta, lepPhi,
		metpt, metphi,
		njets, nbjets, jetPt, jetEta, jetPhi);
/*	fprintf(_fevc,"%6d %6d %10d  %+2d  %6.2f %+4.2f %+4.2f   %6.1f  %+4.2f    %d %d \n",
		run, lumi, id,
		lepId, lepPt, lepEta, lepPhi,
		metpt, metphi,
		njets, nbjets);*/
//	fprintf(_fevc,"%6d %6d %10d\n",
//		id, run, lumi);
     }
}

void Hist::fillHisto1D(TH1D *h,float sfj0,float sfj,std::string sys,int ilep,std::string varName,bool isData,int isel,int idxSR)
{
   float w = sfj;

   if( !isData )
     {	
	float SfIterativeFit = 1.;
	
	int nJet = _v_JetTight->size();

	if( strcmp(sys.c_str(),"") == 0 )
	  {
	  }	
	else if( strcmp(sys.c_str(),"_SfIterativeFitJes_Down") == 0 )
	  {  
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitJesDown();
	       }
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitJes_Up") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitJesUp();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitLf_Down") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitLfDown();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitLf_Up") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitLfUp();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitHf_Down") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitHfDown();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitHf_Up") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitHfUp();
	       }
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitHfstats1_Down") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitHfstats1Down();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitHfstats1_Up") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitHfstats1Up();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitHfstats2_Down") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;

		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitHfstats2Down();
	       }
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitHfstats2_Up") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitHfstats2Up();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitCferr1_Down") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;

		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitCferr1Down();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitCferr1_Up") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitCferr1Up();
	       }
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitCferr2_Down") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;

		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitCferr2Down();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitCferr2_Up") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitCferr2Up();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitLfstats1_Down") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;

		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitLfstats1Down();
	       }
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitLfstats1_Up") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitLfstats1Up();
	       }
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitLfstats2_Down") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;

		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitLfstats2Down();
	       }   
	     
	     w = sfj0*SfIterativeFit;
	  }   
	else if( strcmp(sys.c_str(),"_SfIterativeFitLfstats2_Up") == 0 )
	  {
	     for(int ij=0;ij<nJet;ij++)
	       {
		  if( !checkJet(ij,idxSR) ) continue;
		  
		  SfIterativeFit *= _v_JetTight->at(ij).SfIterativeFitLfstats2Up();
	       }
	     
	     w = sfj0*SfIterativeFit;
	  }   
     }
   
   float chi2_TOPTOPLEPHBB = _trec->chi2_TOPTOPLEPHBB();
   float chi2_TOPHLEPBB = _trec->chi2_TOPHLEPBB();
   float chi2_TOPTOPLEPHAD = _trec->chi2_TOPTOPLEPHAD();
   float MVA_TOPTOPLEPHBB = _trec->MVA_TOPTOPLEPHBB();
   float MVA_TOPHLEPBB = _trec->MVA_TOPHLEPBB();
   float MVA_TOPTOPLEPHAD = _trec->MVA_TOPTOPLEPHAD();
   float HiggsMass_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_p4().M();
   float HiggsMass_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_p4().M();
   float TopHadMass_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_p4().M();
   float TopHadWMass_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_p4().M();
   int LepCharge = _v_Lepton->at(0).charge();
   float LepPt = _v_Lepton->at(0).pt();
   float LepEta = _v_Lepton->at(0).eta();
   float LepPhi = _v_Lepton->at(0).phi();
   float HiggsPt_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_p4().Pt();
   float HiggsPt_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_p4().Pt();
   float HiggsEta_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_p4().PseudoRapidity();
   float HiggsEta_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_p4().PseudoRapidity();
   float HiggsPhi_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_p4().Phi();
   float HiggsPhi_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_p4().Phi();
   float TopLepMass_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_p4().M();
   float TopLepMass_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_p4().M();
   float TopLepMass_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_p4().M();
   float TopLepPt_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_p4().Pt();
   float TopLepPt_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_p4().Pt();
   float TopLepPt_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_p4().Pt();
   float TopHadPt_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_p4().Pt();
   float TopHadWPt_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_p4().Pt();
   float TopLepEta_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_p4().PseudoRapidity();
   float TopLepEta_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_p4().PseudoRapidity();
   float TopLepEta_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_p4().PseudoRapidity();
   float TopHadEta_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_p4().PseudoRapidity();
   float TopHadWEta_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_p4().PseudoRapidity();
   float TopLepPhi_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_p4().Phi();
   float TopLepPhi_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_p4().Phi();
   float TopLepPhi_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_p4().Phi();
   float TopHadPhi_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_p4().Phi();
   float TopHadWPhi_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_p4().Phi();
   float HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_p4().DeltaR(_trec->HiggsBJet2_TOPTOPLEPHBB_p4());
   float HiggsBJet1HiggsBJet2Dr_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_p4().DeltaR(_trec->HiggsBJet2_TOPHLEPBB_p4());
   float TopHadWNonBJet1TopHadWNonBJet2Dr_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_p4().DeltaR(_trec->TopHadWNonBJet2_TOPTOPLEPHAD_p4());
   float TopLepHiggsDr_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_p4().DeltaR(_trec->Higgs_TOPTOPLEPHBB_p4());
   float TopLepHiggsDr_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_p4().DeltaR(_trec->Higgs_TOPHLEPBB_p4());
   float TopLepTopHadDr_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_p4().DeltaR(_trec->TopHad_TOPTOPLEPHAD_p4());
   float HiggsBJet1CSVv2_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_CSVv2();
   float HiggsBJet2CSVv2_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_CSVv2();
   float TopLepBJetCSVv2_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_CSVv2();
   float TopHadNonBJetCSVv2_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_CSVv2();
   float HiggsBJet1CSVv2_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_CSVv2();
   float HiggsBJet2CSVv2_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_CSVv2();
   float TopLepBJetCSVv2_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_CSVv2();
   float TopLepBJetCSVv2_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_CSVv2();
   float TopHadBJetCSVv2_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_CSVv2();
   float TopHadWNonBJet1CSVv2_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2();
   float TopHadWNonBJet2CSVv2_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2();
   float HiggsBJet1Pt_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_p4().Pt();
   float HiggsBJet2Pt_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_p4().Pt();
   float TopLepBJetPt_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_p4().Pt();
   float HiggsBJet1Eta_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_p4().PseudoRapidity();
   float HiggsBJet2Eta_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_p4().PseudoRapidity();
   float TopLepBJetEta_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_p4().PseudoRapidity();
   float HiggsBJet1Phi_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_p4().Phi();
   float HiggsBJet2Phi_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_p4().Phi();
   float TopLepBJetPhi_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_p4().Phi();
   float HiggsBJet1E_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_p4().E();
   float HiggsBJet2E_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_p4().E();
   float TopLepBJetE_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_p4().E();

   float HiggsBJet1Pt_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_p4().Pt();
   float HiggsBJet2Pt_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_p4().Pt();
   float TopLepBJetPt_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_p4().Pt();
   float TopHadNonBJetPt_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_p4().Pt();
   float HiggsBJet1Eta_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_p4().PseudoRapidity();
   float HiggsBJet2Eta_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_p4().PseudoRapidity();
   float TopLepBJetEta_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_p4().PseudoRapidity();
   float TopHadNonBJetEta_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_p4().PseudoRapidity();
   float HiggsBJet1Phi_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_p4().Phi();
   float HiggsBJet2Phi_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_p4().Phi();
   float TopLepBJetPhi_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_p4().Phi();
   float TopHadNonBJetPhi_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_p4().Phi();
   float HiggsBJet1E_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_p4().E();
   float HiggsBJet2E_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_p4().E();
   float TopLepBJetE_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_p4().E();
   float TopHadNonBJetE_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_p4().E();

   float TopHadWNonBJet1Pt_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_p4().Pt();
   float TopHadWNonBJet2Pt_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_p4().Pt();
   float TopLepBJetPt_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_p4().Pt();
   float TopHadBJetPt_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_p4().Pt();
   float TopHadWNonBJet1Eta_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_p4().PseudoRapidity();
   float TopHadWNonBJet2Eta_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_p4().PseudoRapidity();
   float TopLepBJetEta_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_p4().PseudoRapidity();
   float TopHadBJetEta_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_p4().PseudoRapidity();
   float TopHadWNonBJet1Phi_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_p4().Phi();
   float TopHadWNonBJet2Phi_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_p4().Phi();
   float TopLepBJetPhi_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_p4().Phi();
   float TopHadBJetPhi_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_p4().Phi();
   float TopHadWNonBJet1E_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_p4().E();
   float TopHadWNonBJet2E_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_p4().E();
   float TopLepBJetE_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_p4().E();
   float TopHadBJetE_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_p4().E();
   
   if( strcmp(varName.c_str(),"h_chi2_TOPTOPLEPHBB_") == 0 )
     {
	h->Fill(chi2_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_chi2_TOPHLEPBB_") == 0 )
     {
	h->Fill(chi2_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_chi2_TOPTOPLEPHAD_") == 0 )
     {
	h->Fill(chi2_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_MVA_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) MVA_TOPTOPLEPHBB = _trec->MVA_TOPTOPLEPHBB_JesUp();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) MVA_TOPTOPLEPHBB = _trec->MVA_TOPTOPLEPHBB_JesDown();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) MVA_TOPTOPLEPHBB = _trec->MVA_TOPTOPLEPHBB_JerUp();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) MVA_TOPTOPLEPHBB = _trec->MVA_TOPTOPLEPHBB_JerDown();
	  }	
	
	h->Fill(MVA_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_MVA_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) MVA_TOPHLEPBB = _trec->MVA_TOPHLEPBB_JesUp();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) MVA_TOPHLEPBB = _trec->MVA_TOPHLEPBB_JesDown();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) MVA_TOPHLEPBB = _trec->MVA_TOPHLEPBB_JerUp();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) MVA_TOPHLEPBB = _trec->MVA_TOPHLEPBB_JerDown();
	  }	
	
	h->Fill(MVA_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_MVA_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) MVA_TOPTOPLEPHAD = _trec->MVA_TOPTOPLEPHAD_JesUp();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) MVA_TOPTOPLEPHAD = _trec->MVA_TOPTOPLEPHAD_JesDown();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) MVA_TOPTOPLEPHAD = _trec->MVA_TOPTOPLEPHAD_JerUp();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) MVA_TOPTOPLEPHAD = _trec->MVA_TOPTOPLEPHAD_JerDown();
	  }	
	
	h->Fill(MVA_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsMass_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsMass_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JesUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsMass_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JesDown_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsMass_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JerUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsMass_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JerDown_p4().M();
	  }	
	
	h->Fill(HiggsMass_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsMass_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsMass_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JesUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsMass_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JesDown_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsMass_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JerUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsMass_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JerDown_p4().M();
	  }	
	
	h->Fill(HiggsMass_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadMass_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadMass_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JesUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadMass_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JesDown_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadMass_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JerUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadMass_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JerDown_p4().M();
	  }	
	
	h->Fill(TopHadMass_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWMass_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWMass_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JesUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWMass_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JesDown_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWMass_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JerUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWMass_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JerDown_p4().M();
	  }	
	
	h->Fill(TopHadWMass_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_LepCharge_") == 0 )
     {
	h->Fill(LepCharge,w);
     }
   else if( strcmp(varName.c_str(),"h_LepPt_") == 0 )
     {
	h->Fill(LepPt,w);
     }
   else if( strcmp(varName.c_str(),"h_LepEta_") == 0 )
     {
	h->Fill(LepEta,w);
     }
   else if( strcmp(varName.c_str(),"h_LepPhi_") == 0 )
     {
	h->Fill(LepPhi,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsPt_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsPt_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsPt_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsPt_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsPt_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(HiggsPt_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsPt_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsPt_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsPt_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsPt_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsPt_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(HiggsPt_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsEta_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsEta_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsEta_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsEta_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsEta_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(HiggsEta_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsEta_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsEta_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsEta_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsEta_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsEta_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(HiggsEta_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsPhi_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsPhi_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsPhi_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsPhi_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsPhi_TOPTOPLEPHBB = _trec->Higgs_TOPTOPLEPHBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(HiggsPhi_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsPhi_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsPhi_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsPhi_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsPhi_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsPhi_TOPHLEPBB = _trec->Higgs_TOPHLEPBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(HiggsPhi_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepMass_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepMass_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JesUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepMass_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JesDown_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepMass_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JerUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepMass_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JerDown_p4().M();
	  }	
	
	h->Fill(TopLepMass_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepMass_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepMass_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JesUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepMass_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JesDown_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepMass_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JerUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepMass_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JerDown_p4().M();
	  }	
	
	h->Fill(TopLepMass_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepMass_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepMass_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JesUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepMass_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JesDown_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepMass_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JerUp_p4().M();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepMass_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JerDown_p4().M();
	  }	
	
	h->Fill(TopLepMass_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepPt_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepPt_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepPt_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepPt_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepPt_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopLepPt_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepPt_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepPt_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepPt_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepPt_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepPt_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopLepPt_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepPt_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepPt_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepPt_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepPt_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepPt_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopLepPt_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadPt_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadPt_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadPt_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadPt_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadPt_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopHadPt_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWPt_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWPt_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWPt_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWPt_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWPt_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopHadWPt_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepEta_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepEta_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepEta_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepEta_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepEta_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(TopLepEta_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepEta_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepEta_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepEta_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepEta_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepEta_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(TopLepEta_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepEta_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepEta_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepEta_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepEta_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepEta_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JerDown_p4().PseudoRapidity();
	  }
	
	h->Fill(TopLepEta_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadEta_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadEta_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadEta_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadEta_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadEta_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JerDown_p4().PseudoRapidity();
	  }
	
	h->Fill(TopHadEta_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWEta_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWEta_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWEta_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWEta_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWEta_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JerDown_p4().PseudoRapidity();
	  }
	
	h->Fill(TopHadWEta_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepPhi_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepPhi_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepPhi_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepPhi_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepPhi_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(TopLepPhi_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepPhi_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepPhi_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepPhi_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepPhi_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepPhi_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(TopLepPhi_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepPhi_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepPhi_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepPhi_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepPhi_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepPhi_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JerDown_p4().Phi();
	  }
	
	h->Fill(TopLepPhi_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadPhi_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadPhi_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadPhi_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadPhi_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadPhi_TOPTOPLEPHAD = _trec->TopHad_TOPTOPLEPHAD_JerDown_p4().Phi();
	  }
	
	h->Fill(TopHadPhi_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWPhi_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWPhi_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWPhi_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWPhi_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWPhi_TOPTOPLEPHAD = _trec->TopHadW_TOPTOPLEPHAD_JerDown_p4().Phi();
	  }
	
	h->Fill(TopHadWPhi_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JesUp_p4().DeltaR(_trec->HiggsBJet2_TOPTOPLEPHBB_JesUp_p4());
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JesDown_p4().DeltaR(_trec->HiggsBJet2_TOPTOPLEPHBB_JesDown_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JerUp_p4().DeltaR(_trec->HiggsBJet2_TOPTOPLEPHBB_JerUp_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JerDown_p4().DeltaR(_trec->HiggsBJet2_TOPTOPLEPHBB_JerDown_p4());
	  }	
	
	h->Fill(HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet1TopHadWNonBJet2Dr_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWNonBJet1TopHadWNonBJet2Dr_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4().DeltaR(_trec->TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4());
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWNonBJet1TopHadWNonBJet2Dr_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4().DeltaR(_trec->TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWNonBJet1TopHadWNonBJet2Dr_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4().DeltaR(_trec->TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWNonBJet1TopHadWNonBJet2Dr_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4().DeltaR(_trec->TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4());
	  }	
	
	h->Fill(TopHadWNonBJet1TopHadWNonBJet2Dr_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet1HiggsBJet2Dr_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JesUp_p4().DeltaR(_trec->HiggsBJet2_TOPHLEPBB_JesUp_p4());
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet1HiggsBJet2Dr_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JesDown_p4().DeltaR(_trec->HiggsBJet2_TOPHLEPBB_JesDown_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet1HiggsBJet2Dr_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JerUp_p4().DeltaR(_trec->HiggsBJet2_TOPHLEPBB_JerUp_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet1HiggsBJet2Dr_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JerDown_p4().DeltaR(_trec->HiggsBJet2_TOPHLEPBB_JerDown_p4());
	  }	
	
	h->Fill(HiggsBJet1HiggsBJet2Dr_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepHiggsDr_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepHiggsDr_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JesUp_p4().DeltaR(_trec->Higgs_TOPTOPLEPHBB_JesUp_p4());
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepHiggsDr_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JesDown_p4().DeltaR(_trec->Higgs_TOPTOPLEPHBB_JesDown_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepHiggsDr_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JerUp_p4().DeltaR(_trec->Higgs_TOPTOPLEPHBB_JerUp_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepHiggsDr_TOPTOPLEPHBB = _trec->TopLep_TOPTOPLEPHBB_JerDown_p4().DeltaR(_trec->Higgs_TOPTOPLEPHBB_JerDown_p4());
	  }	
	
	h->Fill(TopLepHiggsDr_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepHiggsDr_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepHiggsDr_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JesUp_p4().DeltaR(_trec->Higgs_TOPHLEPBB_JesUp_p4());
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepHiggsDr_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JesDown_p4().DeltaR(_trec->Higgs_TOPHLEPBB_JesDown_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepHiggsDr_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JerUp_p4().DeltaR(_trec->Higgs_TOPHLEPBB_JerUp_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepHiggsDr_TOPHLEPBB = _trec->TopLep_TOPHLEPBB_JerDown_p4().DeltaR(_trec->Higgs_TOPHLEPBB_JerDown_p4());
	  }	
	
	h->Fill(TopLepHiggsDr_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepTopHadDr_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepTopHadDr_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JesUp_p4().DeltaR(_trec->TopHad_TOPTOPLEPHAD_JesUp_p4());
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepTopHadDr_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JesDown_p4().DeltaR(_trec->TopHad_TOPTOPLEPHAD_JesDown_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepTopHadDr_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JerUp_p4().DeltaR(_trec->TopHad_TOPTOPLEPHAD_JerUp_p4());
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepTopHadDr_TOPTOPLEPHAD = _trec->TopLep_TOPTOPLEPHAD_JerDown_p4().DeltaR(_trec->TopHad_TOPTOPLEPHAD_JerDown_p4());
	  }	
	
	h->Fill(TopLepTopHadDr_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet1CSVv2_TOPTOPLEPHBB_") == 0 )
     {
	h->Fill(HiggsBJet1CSVv2_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet2CSVv2_TOPTOPLEPHBB_") == 0 )
     {
	h->Fill(HiggsBJet2CSVv2_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetCSVv2_TOPTOPLEPHBB_") == 0 )
     {
	h->Fill(TopLepBJetCSVv2_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadNonBJetCSVv2_TOPTOPLEPHBB_") == 0 )
     {
	h->Fill(TopHadNonBJetCSVv2_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet1CSVv2_TOPHLEPBB_") == 0 )
     {
	h->Fill(HiggsBJet1CSVv2_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet2CSVv2_TOPHLEPBB_") == 0 )
     {
	h->Fill(HiggsBJet2CSVv2_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetCSVv2_TOPHLEPBB_") == 0 )
     {
	h->Fill(TopLepBJetCSVv2_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetCSVv2_TOPTOPLEPHAD_") == 0 )
     {
	h->Fill(TopLepBJetCSVv2_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadBJetCSVv2_TOPTOPLEPHAD_") == 0 )
     {
	h->Fill(TopHadBJetCSVv2_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_") == 0 )
     {
	h->Fill(TopHadWNonBJet1CSVv2_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_") == 0 )
     {
	h->Fill(TopHadWNonBJet2CSVv2_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet1Pt_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet1Pt_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet1Pt_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet1Pt_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet1Pt_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(HiggsBJet1Pt_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet2Pt_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet2Pt_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet2Pt_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet2Pt_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet2Pt_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(HiggsBJet2Pt_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetPt_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetPt_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetPt_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetPt_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetPt_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopLepBJetPt_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet1Eta_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet1Eta_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet1Eta_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet1Eta_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet1Eta_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(HiggsBJet1Eta_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet2Eta_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet2Eta_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet2Eta_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet2Eta_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet2Eta_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(HiggsBJet2Eta_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetEta_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetEta_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetEta_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetEta_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetEta_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(TopLepBJetEta_TOPHLEPBB,w);
     } 
   else if( strcmp(varName.c_str(),"h_HiggsBJet1Phi_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet1Phi_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet1Phi_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet1Phi_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet1Phi_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(HiggsBJet1Phi_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet2Phi_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet2Phi_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet2Phi_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet2Phi_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet2Phi_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(HiggsBJet2Phi_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetPhi_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetPhi_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetPhi_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetPhi_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetPhi_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(TopLepBJetPhi_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet1E_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet1E_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet1E_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet1E_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet1E_TOPHLEPBB = _trec->HiggsBJet1_TOPHLEPBB_JerDown_p4().E();
	  }	
	
	h->Fill(HiggsBJet1E_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet2E_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet2E_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet2E_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet2E_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet2E_TOPHLEPBB = _trec->HiggsBJet2_TOPHLEPBB_JerDown_p4().E();
	  }	
	
	h->Fill(HiggsBJet2E_TOPHLEPBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetE_TOPHLEPBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetE_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetE_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetE_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetE_TOPHLEPBB = _trec->TopLepBJet_TOPHLEPBB_JerDown_p4().E();
	  }	
	
	h->Fill(TopLepBJetE_TOPHLEPBB,w);
     }

   else if( strcmp(varName.c_str(),"h_HiggsBJet1Pt_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet1Pt_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet1Pt_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet1Pt_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet1Pt_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(HiggsBJet1Pt_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet2Pt_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet2Pt_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet2Pt_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet2Pt_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet2Pt_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(HiggsBJet2Pt_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetPt_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetPt_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetPt_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetPt_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetPt_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopLepBJetPt_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadNonBJetPt_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadNonBJetPt_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadNonBJetPt_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadNonBJetPt_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadNonBJetPt_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopHadNonBJetPt_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadBJetPt_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadBJetPt_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadBJetPt_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadBJetPt_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadBJetPt_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopHadBJetPt_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetPt_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetPt_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetPt_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetPt_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetPt_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopLepBJetPt_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet1Pt_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWNonBJet1Pt_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWNonBJet1Pt_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWNonBJet1Pt_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWNonBJet1Pt_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopHadWNonBJet1Pt_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet2Pt_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWNonBJet2Pt_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWNonBJet2Pt_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWNonBJet2Pt_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4().Pt();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWNonBJet2Pt_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4().Pt();
	  }	
	
	h->Fill(TopHadWNonBJet2Pt_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet1Eta_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet1Eta_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet1Eta_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet1Eta_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet1Eta_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(HiggsBJet1Eta_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet2Eta_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet2Eta_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet2Eta_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet2Eta_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet2Eta_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(HiggsBJet2Eta_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetEta_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetEta_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetEta_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetEta_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetEta_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(TopLepBJetEta_TOPTOPLEPHBB,w);
     } 
   else if( strcmp(varName.c_str(),"h_TopHadNonBJetEta_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadNonBJetEta_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadNonBJetEta_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadNonBJetEta_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadNonBJetEta_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(TopHadNonBJetEta_TOPTOPLEPHBB,w);
     } 
   else if( strcmp(varName.c_str(),"h_TopHadBJetEta_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadBJetEta_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadBJetEta_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadBJetEta_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadBJetEta_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(TopHadBJetEta_TOPTOPLEPHAD,w);
     } 
   else if( strcmp(varName.c_str(),"h_TopLepBJetEta_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetEta_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetEta_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetEta_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetEta_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(TopLepBJetEta_TOPTOPLEPHAD,w);
     } 
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet1Eta_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWNonBJet1Eta_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWNonBJet1Eta_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWNonBJet1Eta_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWNonBJet1Eta_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(TopHadWNonBJet1Eta_TOPTOPLEPHAD,w);
     } 
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet2Eta_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWNonBJet2Eta_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWNonBJet2Eta_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWNonBJet2Eta_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4().PseudoRapidity();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWNonBJet2Eta_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4().PseudoRapidity();
	  }	
	
	h->Fill(TopHadWNonBJet2Eta_TOPTOPLEPHAD,w);
     } 
   else if( strcmp(varName.c_str(),"h_HiggsBJet1Phi_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet1Phi_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet1Phi_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet1Phi_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet1Phi_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(HiggsBJet1Phi_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet2Phi_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet2Phi_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet2Phi_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet2Phi_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet2Phi_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(HiggsBJet2Phi_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetPhi_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetPhi_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetPhi_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetPhi_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetPhi_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(TopLepBJetPhi_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadNonBJetPhi_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadNonBJetPhi_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadNonBJetPhi_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadNonBJetPhi_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadNonBJetPhi_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JerDown_p4().Phi();
	  }	
	
	h->Fill(TopHadNonBJetPhi_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadBJetPhi_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadBJetPhi_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadBJetPhi_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadBJetPhi_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadBJetPhi_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JerDown_p4().Phi();
	  }	
	
	h->Fill(TopHadBJetPhi_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetPhi_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetPhi_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetPhi_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetPhi_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetPhi_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JerDown_p4().Phi();
	  }	
	
	h->Fill(TopLepBJetPhi_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet1Phi_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWNonBJet1Phi_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWNonBJet1Phi_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWNonBJet1Phi_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWNonBJet1Phi_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4().Phi();
	  }	
	
	h->Fill(TopHadWNonBJet1Phi_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet2Phi_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWNonBJet2Phi_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWNonBJet2Phi_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWNonBJet2Phi_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4().Phi();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWNonBJet2Phi_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4().Phi();
	  }	
	
	h->Fill(TopHadWNonBJet2Phi_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet1E_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {		     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet1E_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet1E_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet1E_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet1E_TOPTOPLEPHBB = _trec->HiggsBJet1_TOPTOPLEPHBB_JerDown_p4().E();
	  }	
	
	h->Fill(HiggsBJet1E_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_HiggsBJet2E_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) HiggsBJet2E_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) HiggsBJet2E_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) HiggsBJet2E_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) HiggsBJet2E_TOPTOPLEPHBB = _trec->HiggsBJet2_TOPTOPLEPHBB_JerDown_p4().E();
	  }	
	
	h->Fill(HiggsBJet2E_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetE_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetE_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetE_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetE_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetE_TOPTOPLEPHBB = _trec->TopLepBJet_TOPTOPLEPHBB_JerDown_p4().E();
	  }	
	
	h->Fill(TopLepBJetE_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadNonBJetE_TOPTOPLEPHBB_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadNonBJetE_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadNonBJetE_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadNonBJetE_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadNonBJetE_TOPTOPLEPHBB = _trec->TopHadNonBJet_TOPTOPLEPHBB_JerDown_p4().E();
	  }	
	
	h->Fill(TopHadNonBJetE_TOPTOPLEPHBB,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadBJetE_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadBJetE_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadBJetE_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadBJetE_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadBJetE_TOPTOPLEPHAD = _trec->TopHadBJet_TOPTOPLEPHAD_JerDown_p4().E();
	  }	
	
	h->Fill(TopHadBJetE_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopLepBJetE_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopLepBJetE_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopLepBJetE_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopLepBJetE_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopLepBJetE_TOPTOPLEPHAD = _trec->TopLepBJet_TOPTOPLEPHAD_JerDown_p4().E();
	  }	
	
	h->Fill(TopLepBJetE_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet1E_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWNonBJet1E_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWNonBJet1E_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWNonBJet1E_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWNonBJet1E_TOPTOPLEPHAD = _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4().E();
	  }	
	
	h->Fill(TopHadWNonBJet1E_TOPTOPLEPHAD,w);
     }
   else if( strcmp(varName.c_str(),"h_TopHadWNonBJet2E_TOPTOPLEPHAD_") == 0 )
     {
	if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 ) TopHadWNonBJet2E_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 ) TopHadWNonBJet2E_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 ) TopHadWNonBJet2E_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4().E();
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 ) TopHadWNonBJet2E_TOPTOPLEPHAD = _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4().E();
	  }	
	
	h->Fill(TopHadWNonBJet2E_TOPTOPLEPHAD,w);
     }
   
   else if( strcmp(varName.c_str(),"h_PassSel9_") == 0 && isel == 5 )
     {
	for(int is=0;is<sel_n-1;is++)
	  {	     
	     bool pass = CHECK_BIT(passSel_all,is);
	     if( pass ) h->Fill(is,w);
	  }	
     }

   else if( strcmp(varName.c_str(),"h_PassSel5_") == 0 && isel == 5 )
     {
//	for(int is=4;is<sel_n-1;is++)
	for(int is=0;is<sel_n-1;is++)
	  {
	     bool pass = CHECK_BIT(passSel_all,is);
//	     if( pass ) h->Fill(is-4,w);
	     if( pass ) h->Fill(is,w);
	  }	
     }

   else if( strcmp(varName.c_str(),"h_MVAHutST_") == 0 )
     {
	if( isData || (
		       !(strcmp(sys.c_str(),"_Jes_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jes_Down") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Down") == 0)
		      )
	  )
	  {	     
//	     if( isel == 0 ) h->Fill(_mvab0j3HutST,w);
//	     else if( isel == 1 ) h->Fill(_mvab0j4HutST,w);
//	     else if( isel == 2 ) h->Fill(_mvab1j3HutST,w);
//	     else if( isel == 3 ) h->Fill(_mvab1j4HutST,w);
	     if( isel == 0 ) h->Fill(_mvab2j3HutST,w);
	     else if( isel == 1 ) h->Fill(_mvab2j4HutST,w);
	     else if( isel == 2 ) h->Fill(_mvab3j3HutST,w);
	     else if( isel == 3 ) h->Fill(_mvab3j4HutST,w);
	     else if( isel == 4 ) h->Fill(_mvab4j4HutST,w);
	  }
	else if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HutSTJesUp,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HutSTJesUp,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HutSTJesUp,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HutSTJesUp,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HutSTJesUp,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HutSTJesUp,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HutSTJesUp,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HutSTJesUp,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HutSTJesUp,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HutSTJesDown,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HutSTJesDown,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HutSTJesDown,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HutSTJesDown,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HutSTJesDown,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HutSTJesDown,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HutSTJesDown,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HutSTJesDown,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HutSTJesDown,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HutSTJerUp,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HutSTJerUp,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HutSTJerUp,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HutSTJerUp,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HutSTJerUp,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HutSTJerUp,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HutSTJerUp,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HutSTJerUp,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HutSTJerUp,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HutSTJerDown,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HutSTJerDown,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HutSTJerDown,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HutSTJerDown,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HutSTJerDown,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HutSTJerDown,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HutSTJerDown,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HutSTJerDown,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HutSTJerDown,w);
	       }	
	  }   
     }   
   else if( strcmp(varName.c_str(),"h_MVAHctST_") == 0 )
     {
	if( isData || (
		       !(strcmp(sys.c_str(),"_Jes_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jes_Down") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Down") == 0)
		      )
	  )
	  {	     
//	     if( isel == 0 ) h->Fill(_mvab0j3HctST,w);
//	     else if( isel == 1 ) h->Fill(_mvab0j4HctST,w);
//	     else if( isel == 2 ) h->Fill(_mvab1j3HctST,w);
//	     else if( isel == 3 ) h->Fill(_mvab1j4HctST,w);
	     if( isel == 0 ) h->Fill(_mvab2j3HctST,w);
	     else if( isel == 1 ) h->Fill(_mvab2j4HctST,w);
	     else if( isel == 2 ) h->Fill(_mvab3j3HctST,w);
	     else if( isel == 3 ) h->Fill(_mvab3j4HctST,w);
	     else if( isel == 4 ) h->Fill(_mvab4j4HctST,w);
	  }
	else if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HctSTJesUp,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HctSTJesUp,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HctSTJesUp,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HctSTJesUp,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HctSTJesUp,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HctSTJesUp,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HctSTJesUp,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HctSTJesUp,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HctSTJesUp,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HctSTJesDown,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HctSTJesDown,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HctSTJesDown,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HctSTJesDown,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HctSTJesDown,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HctSTJesDown,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HctSTJesDown,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HctSTJesDown,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HctSTJesDown,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HctSTJerUp,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HctSTJerUp,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HctSTJerUp,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HctSTJerUp,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HctSTJerUp,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HctSTJerUp,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HctSTJerUp,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HctSTJerUp,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HctSTJerUp,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HctSTJerDown,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HctSTJerDown,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HctSTJerDown,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HctSTJerDown,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HctSTJerDown,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HctSTJerDown,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HctSTJerDown,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HctSTJerDown,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HctSTJerDown,w);
	       }	     
	  }	
     }   
   else if( strcmp(varName.c_str(),"h_MVAHutTT_") == 0 )
     {
	if( isData || (
		       !(strcmp(sys.c_str(),"_Jes_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jes_Down") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Down") == 0)
		      )
	  )
	  {	     
//	     if( isel == 0 ) h->Fill(_mvab0j3HutTT,w);
//	     else if( isel == 1 ) h->Fill(_mvab0j4HutTT,w);
//	     else if( isel == 2 ) h->Fill(_mvab1j3HutTT,w);
//	     else if( isel == 3 ) h->Fill(_mvab1j4HutTT,w);
	     if( isel == 0 ) h->Fill(_mvab2j3HutTT,w);
	     else if( isel == 1 ) h->Fill(_mvab2j4HutTT,w);
	     else if( isel == 2 ) h->Fill(_mvab3j3HutTT,w);
	     else if( isel == 3 ) h->Fill(_mvab3j4HutTT,w);
	     else if( isel == 4 ) h->Fill(_mvab4j4HutTT,w);
	  }
	else if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HutTTJesUp,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HutTTJesUp,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HutTTJesUp,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HutTTJesUp,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HutTTJesUp,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HutTTJesUp,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HutTTJesUp,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HutTTJesUp,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HutTTJesUp,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HutTTJesDown,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HutTTJesDown,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HutTTJesDown,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HutTTJesDown,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HutTTJesDown,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HutTTJesDown,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HutTTJesDown,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HutTTJesDown,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HutTTJesDown,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HutTTJerUp,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HutTTJerUp,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HutTTJerUp,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HutTTJerUp,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HutTTJerUp,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HutTTJerUp,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HutTTJerUp,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HutTTJerUp,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HutTTJerUp,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HutTTJerDown,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HutTTJerDown,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HutTTJerDown,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HutTTJerDown,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HutTTJerDown,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HutTTJerDown,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HutTTJerDown,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HutTTJerDown,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HutTTJerDown,w);
	       }	
	  }	
     }   
   else if( strcmp(varName.c_str(),"h_MVAHctTT_") == 0 )
     {
	if( isData || (
		       !(strcmp(sys.c_str(),"_Jes_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jes_Down") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Down") == 0)
		      )
	  )
	  {	     
//	     if( isel == 0 ) h->Fill(_mvab0j3HctTT,w);
//	     else if( isel == 1 ) h->Fill(_mvab0j4HctTT,w);
//	     else if( isel == 2 ) h->Fill(_mvab1j3HctTT,w);
//	     else if( isel == 3 ) h->Fill(_mvab1j4HctTT,w);
	     if( isel == 0 ) h->Fill(_mvab2j3HctTT,w);
	     else if( isel == 1 ) h->Fill(_mvab2j4HctTT,w);
	     else if( isel == 2 ) h->Fill(_mvab3j3HctTT,w);
	     else if( isel == 3 ) h->Fill(_mvab3j4HctTT,w);
	     else if( isel == 4 ) h->Fill(_mvab4j4HctTT,w);
	  }
	else if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HctTTJesUp,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HctTTJesUp,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HctTTJesUp,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HctTTJesUp,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HctTTJesUp,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HctTTJesUp,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HctTTJesUp,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HctTTJesUp,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HctTTJesUp,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HctTTJesDown,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HctTTJesDown,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HctTTJesDown,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HctTTJesDown,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HctTTJesDown,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HctTTJesDown,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HctTTJesDown,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HctTTJesDown,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HctTTJesDown,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HctTTJerUp,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HctTTJerUp,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HctTTJerUp,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HctTTJerUp,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HctTTJerUp,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HctTTJerUp,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HctTTJerUp,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HctTTJerUp,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HctTTJerUp,w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 )
	       {
//		  if( isel == 0 ) h->Fill(_mvab0j3HctTTJerDown,w);
//		  else if( isel == 1 ) h->Fill(_mvab0j4HctTTJerDown,w);
//		  else if( isel == 2 ) h->Fill(_mvab1j3HctTTJerDown,w);
//		  else if( isel == 3 ) h->Fill(_mvab1j4HctTTJerDown,w);
		  if( isel == 0 ) h->Fill(_mvab2j3HctTTJerDown,w);
		  else if( isel == 1 ) h->Fill(_mvab2j4HctTTJerDown,w);
		  else if( isel == 2 ) h->Fill(_mvab3j3HctTTJerDown,w);
		  else if( isel == 3 ) h->Fill(_mvab3j4HctTTJerDown,w);
		  else if( isel == 4 ) h->Fill(_mvab4j4HctTTJerDown,w);
	       }	
	  }	
     }  
   else if( strcmp(varName.c_str(),"h_MVAHut_") == 0 )
     {
	int ibin = -1;

	if( isData || (
		       !(strcmp(sys.c_str(),"_Jes_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jes_Down") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Down") == 0)
		      )
	  )
	  {	     
//	     if( isel == 0 ) ibin = findMVABin(_mvab0j3HutST,_mvab0j3HutTT);
//	     else if( isel == 1 ) ibin = findMVABin(_mvab0j4HutST,_mvab0j4HutTT);
//	     else if( isel == 2 ) ibin = findMVABin(_mvab1j3HutST,_mvab1j3HutTT);
//	     else if( isel == 3 ) ibin = findMVABin(_mvab1j4HutST,_mvab1j4HutTT);
	     if( isel == 0 ) ibin = findMVABin(_mvab2j3HutST,_mvab2j3HutTT);
	     else if( isel == 1 ) ibin = findMVABin(_mvab2j4HutST,_mvab2j4HutTT);
	     else if( isel == 2 ) ibin = findMVABin(_mvab3j3HutST,_mvab3j3HutTT);
	     else if( isel == 3 ) ibin = findMVABin(_mvab3j4HutST,_mvab3j4HutTT);
	     else if( isel == 4 ) ibin = findMVABin(_mvab4j4HutST,_mvab4j4HutTT);
	  }
	else if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 )
	       {
//		  if( isel == 0 ) ibin = findMVABin(_mvab0j3HutSTJesUp,_mvab0j3HutTTJesUp);
//		  else if( isel == 1 ) ibin = findMVABin(_mvab0j4HutSTJesUp,_mvab0j4HutTTJesUp);
//		  else if( isel == 2 ) ibin = findMVABin(_mvab1j3HutSTJesUp,_mvab1j3HutTTJesUp);
//		  else if( isel == 3 ) ibin = findMVABin(_mvab1j4HutSTJesUp,_mvab1j4HutTTJesUp);
		  if( isel == 0 ) ibin = findMVABin(_mvab2j3HutSTJesUp,_mvab2j3HutTTJesUp);
		  else if( isel == 1 ) ibin = findMVABin(_mvab2j4HutSTJesUp,_mvab2j4HutTTJesUp);
		  else if( isel == 2 ) ibin = findMVABin(_mvab3j3HutSTJesUp,_mvab3j3HutTTJesUp);
		  else if( isel == 3 ) ibin = findMVABin(_mvab3j4HutSTJesUp,_mvab3j4HutTTJesUp);
		  else if( isel == 4 ) ibin = findMVABin(_mvab4j4HutSTJesUp,_mvab4j4HutTTJesUp);
	       }
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 )
	       {
//		  if( isel == 0 ) ibin = findMVABin(_mvab0j3HutSTJesDown,_mvab0j3HutTTJesDown);
//		  else if( isel == 1 ) ibin = findMVABin(_mvab0j4HutSTJesDown,_mvab0j4HutTTJesDown);
//		  else if( isel == 2 ) ibin = findMVABin(_mvab1j3HutSTJesDown,_mvab1j3HutTTJesDown);
//		  else if( isel == 3 ) ibin = findMVABin(_mvab1j4HutSTJesDown,_mvab1j4HutTTJesDown);
		  if( isel == 0 ) ibin = findMVABin(_mvab2j3HutSTJesDown,_mvab2j3HutTTJesDown);
		  else if( isel == 1 ) ibin = findMVABin(_mvab2j4HutSTJesDown,_mvab2j4HutTTJesDown);
		  else if( isel == 2 ) ibin = findMVABin(_mvab3j3HutSTJesDown,_mvab3j3HutTTJesDown);
		  else if( isel == 3 ) ibin = findMVABin(_mvab3j4HutSTJesDown,_mvab3j4HutTTJesDown);
		  else if( isel == 4 ) ibin = findMVABin(_mvab4j4HutSTJesDown,_mvab4j4HutTTJesDown);
	       }
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 )
	       {
//		  if( isel == 0 ) ibin = findMVABin(_mvab0j3HutSTJerUp,_mvab0j3HutTTJerUp);
//		  else if( isel == 1 ) ibin = findMVABin(_mvab0j4HutSTJerUp,_mvab0j4HutTTJerUp);
//		  else if( isel == 2 ) ibin = findMVABin(_mvab1j3HutSTJerUp,_mvab1j3HutTTJerUp);
//		  else if( isel == 3 ) ibin = findMVABin(_mvab1j4HutSTJerUp,_mvab1j4HutTTJerUp);
		  if( isel == 0 ) ibin = findMVABin(_mvab2j3HutSTJerUp,_mvab2j3HutTTJerUp);
		  else if( isel == 1 ) ibin = findMVABin(_mvab2j4HutSTJerUp,_mvab2j4HutTTJerUp);
		  else if( isel == 2 ) ibin = findMVABin(_mvab3j3HutSTJerUp,_mvab3j3HutTTJerUp);
		  else if( isel == 3 ) ibin = findMVABin(_mvab3j4HutSTJerUp,_mvab3j4HutTTJerUp);
		  else if( isel == 4 ) ibin = findMVABin(_mvab4j4HutSTJerUp,_mvab4j4HutTTJerUp);
	       }
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 )
	       {
//		  if( isel == 0 ) ibin = findMVABin(_mvab0j3HutSTJerDown,_mvab0j3HutTTJerDown);
//		  else if( isel == 1 ) ibin = findMVABin(_mvab0j4HutSTJerDown,_mvab0j4HutTTJerDown);
//		  else if( isel == 2 ) ibin = findMVABin(_mvab1j3HutSTJerDown,_mvab1j3HutTTJerDown);
//		  else if( isel == 3 ) ibin = findMVABin(_mvab1j4HutSTJerDown,_mvab1j4HutTTJerDown);
		  if( isel == 0 ) ibin = findMVABin(_mvab2j3HutSTJerDown,_mvab2j3HutTTJerDown);
		  else if( isel == 1 ) ibin = findMVABin(_mvab2j4HutSTJerDown,_mvab2j4HutTTJerDown);
		  else if( isel == 2 ) ibin = findMVABin(_mvab3j3HutSTJerDown,_mvab3j3HutTTJerDown);
		  else if( isel == 3 ) ibin = findMVABin(_mvab3j4HutSTJerDown,_mvab3j4HutTTJerDown);
		  else if( isel == 4 ) ibin = findMVABin(_mvab4j4HutSTJerDown,_mvab4j4HutTTJerDown);
	       }
	  }	
	
	h->Fill(ibin,w);
     }   
   else if( strcmp(varName.c_str(),"h_MVAHct_") == 0 )
     {
	int ibin = -1;
	
	if( isData || (
		       !(strcmp(sys.c_str(),"_Jes_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jes_Down") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Down") == 0)
		      )
	  )
	  {	     
//	     if( isel == 0 ) ibin = findMVABin(_mvab0j3HctST,_mvab0j3HctTT);
//	     else if( isel == 1 ) ibin = findMVABin(_mvab0j4HctST,_mvab0j4HctTT);
//	     else if( isel == 2 ) ibin = findMVABin(_mvab1j3HctST,_mvab1j3HctTT);
//	     else if( isel == 3 ) ibin = findMVABin(_mvab1j4HctST,_mvab1j4HctTT);
	     if( isel == 0 ) ibin = findMVABin(_mvab2j3HctST,_mvab2j3HctTT);
	     else if( isel == 1 ) ibin = findMVABin(_mvab2j4HctST,_mvab2j4HctTT);
	     else if( isel == 2 ) ibin = findMVABin(_mvab3j3HctST,_mvab3j3HctTT);
	     else if( isel == 3 ) ibin = findMVABin(_mvab3j4HctST,_mvab3j4HctTT);
	     else if( isel == 4 ) ibin = findMVABin(_mvab4j4HctST,_mvab4j4HctTT);
	  }
	else if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 )
	       {
//		  if( isel == 0 ) ibin = findMVABin(_mvab0j3HctSTJesUp,_mvab0j3HctTTJesUp);
//		  else if( isel == 1 ) ibin = findMVABin(_mvab0j4HctSTJesUp,_mvab0j4HctTTJesUp);
//		  else if( isel == 2 ) ibin = findMVABin(_mvab1j3HctSTJesUp,_mvab1j3HctTTJesUp);
//		  else if( isel == 3 ) ibin = findMVABin(_mvab1j4HctSTJesUp,_mvab1j4HctTTJesUp);
		  if( isel == 0 ) ibin = findMVABin(_mvab2j3HctSTJesUp,_mvab2j3HctTTJesUp);
		  else if( isel == 1 ) ibin = findMVABin(_mvab2j4HctSTJesUp,_mvab2j4HctTTJesUp);
		  else if( isel == 2 ) ibin = findMVABin(_mvab3j3HctSTJesUp,_mvab3j3HctTTJesUp);
		  else if( isel == 3 ) ibin = findMVABin(_mvab3j4HctSTJesUp,_mvab3j4HctTTJesUp);
		  else if( isel == 4 ) ibin = findMVABin(_mvab4j4HctSTJesUp,_mvab4j4HctTTJesUp);
	       }
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 )
	       {
//		  if( isel == 0 ) ibin = findMVABin(_mvab0j3HctSTJesDown,_mvab0j3HctTTJesDown);
//		  else if( isel == 1 ) ibin = findMVABin(_mvab0j4HctSTJesDown,_mvab0j4HctTTJesDown);
//		  else if( isel == 2 ) ibin = findMVABin(_mvab1j3HctSTJesDown,_mvab1j3HctTTJesDown);
//		  else if( isel == 3 ) ibin = findMVABin(_mvab1j4HctSTJesDown,_mvab1j4HctTTJesDown);
		  if( isel == 0 ) ibin = findMVABin(_mvab2j3HctSTJesDown,_mvab2j3HctTTJesDown);
		  else if( isel == 1 ) ibin = findMVABin(_mvab2j4HctSTJesDown,_mvab2j4HctTTJesDown);
		  else if( isel == 2 ) ibin = findMVABin(_mvab3j3HctSTJesDown,_mvab3j3HctTTJesDown);
		  else if( isel == 3 ) ibin = findMVABin(_mvab3j4HctSTJesDown,_mvab3j4HctTTJesDown);
		  else if( isel == 4 ) ibin = findMVABin(_mvab4j4HctSTJesDown,_mvab4j4HctTTJesDown);
	       }
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 )
	       {
//		  if( isel == 0 ) ibin = findMVABin(_mvab0j3HctSTJerUp,_mvab0j3HctTTJerUp);
//		  else if( isel == 1 ) ibin = findMVABin(_mvab0j4HctSTJerUp,_mvab0j4HctTTJerUp);
//		  else if( isel == 2 ) ibin = findMVABin(_mvab1j3HctSTJerUp,_mvab1j3HctTTJerUp);
//		  else if( isel == 3 ) ibin = findMVABin(_mvab1j4HctSTJerUp,_mvab1j4HctTTJerUp);
		  if( isel == 0 ) ibin = findMVABin(_mvab2j3HctSTJerUp,_mvab2j3HctTTJerUp);
		  else if( isel == 1 ) ibin = findMVABin(_mvab2j4HctSTJerUp,_mvab2j4HctTTJerUp);
		  else if( isel == 2 ) ibin = findMVABin(_mvab3j3HctSTJerUp,_mvab3j3HctTTJerUp);
		  else if( isel == 3 ) ibin = findMVABin(_mvab3j4HctSTJerUp,_mvab3j4HctTTJerUp);
		  else if( isel == 4 ) ibin = findMVABin(_mvab4j4HctSTJerUp,_mvab4j4HctTTJerUp);
	       }
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 )
	       {
//		  if( isel == 0 ) ibin = findMVABin(_mvab0j3HctSTJerDown,_mvab0j3HctTTJerDown);
//		  else if( isel == 1 ) ibin = findMVABin(_mvab0j4HctSTJerDown,_mvab0j4HctTTJerDown);
//		  else if( isel == 2 ) ibin = findMVABin(_mvab1j3HctSTJerDown,_mvab1j3HctTTJerDown);
//		  else if( isel == 3 ) ibin = findMVABin(_mvab1j4HctSTJerDown,_mvab1j4HctTTJerDown);
		  if( isel == 0 ) ibin = findMVABin(_mvab2j3HctSTJerDown,_mvab2j3HctTTJerDown);
		  else if( isel == 1 ) ibin = findMVABin(_mvab2j4HctSTJerDown,_mvab2j4HctTTJerDown);
		  else if( isel == 2 ) ibin = findMVABin(_mvab3j3HctSTJerDown,_mvab3j3HctTTJerDown);
		  else if( isel == 3 ) ibin = findMVABin(_mvab3j4HctSTJerDown,_mvab3j4HctTTJerDown);
		  else if( isel == 4 ) ibin = findMVABin(_mvab4j4HctSTJerDown,_mvab4j4HctTTJerDown);
	       }
	  }	
	
	h->Fill(ibin,w);
     }   
   else if( strcmp(varName.c_str(),"h_MVAHutMAX_") == 0 )
     {
	if( isData || (
		       !(strcmp(sys.c_str(),"_Jes_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jes_Down") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Down") == 0)
		      )
	  )
	  {	     
	     if( isel == 0 ) h->Fill(std::max(_mvab2j3HutST,_mvab2j3HutTT),w);
	     else if( isel == 1 ) h->Fill(std::max(_mvab2j4HutST,_mvab2j4HutTT),w);
	     else if( isel == 2 ) h->Fill(std::max(_mvab3j3HutST,_mvab3j3HutTT),w);
	     else if( isel == 3 ) h->Fill(std::max(_mvab3j4HutST,_mvab3j4HutTT),w);
	     else if( isel == 4 ) h->Fill(std::max(_mvab4j4HutST,_mvab4j4HutTT),w);
	  }
	else if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 )
	       {
		  if( isel == 0 ) h->Fill(std::max(_mvab2j3HutSTJesUp,_mvab2j3HutTTJesUp),w);
		  else if( isel == 1 ) h->Fill(std::max(_mvab2j4HutSTJesUp,_mvab2j4HutTTJesUp),w);
		  else if( isel == 2 ) h->Fill(std::max(_mvab3j3HutSTJesUp,_mvab3j3HutTTJesUp),w);
		  else if( isel == 3 ) h->Fill(std::max(_mvab3j4HutSTJesUp,_mvab3j4HutTTJesUp),w);
		  else if( isel == 4 ) h->Fill(std::max(_mvab4j4HutSTJesUp,_mvab4j4HutTTJesUp),w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 )
	       {
		  if( isel == 0 ) h->Fill(std::max(_mvab2j3HutSTJesDown,_mvab2j3HutTTJesDown),w);
		  else if( isel == 1 ) h->Fill(std::max(_mvab2j4HutSTJesDown,_mvab2j4HutTTJesDown),w);
		  else if( isel == 2 ) h->Fill(std::max(_mvab3j3HutSTJesDown,_mvab3j3HutTTJesDown),w);
		  else if( isel == 3 ) h->Fill(std::max(_mvab3j4HutSTJesDown,_mvab3j4HutTTJesDown),w);
		  else if( isel == 4 ) h->Fill(std::max(_mvab4j4HutSTJesDown,_mvab4j4HutTTJesDown),w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 )
	       {
		  if( isel == 0 ) h->Fill(std::max(_mvab2j3HutSTJerUp,_mvab2j3HutTTJerUp),w);
		  else if( isel == 1 ) h->Fill(std::max(_mvab2j4HutSTJerUp,_mvab2j4HutTTJerUp),w);
		  else if( isel == 2 ) h->Fill(std::max(_mvab3j3HutSTJerUp,_mvab3j3HutTTJerUp),w);
		  else if( isel == 3 ) h->Fill(std::max(_mvab3j4HutSTJerUp,_mvab3j4HutTTJerUp),w);
		  else if( isel == 4 ) h->Fill(std::max(_mvab4j4HutSTJerUp,_mvab4j4HutTTJerUp),w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 )
	       {
		  if( isel == 0 ) h->Fill(std::max(_mvab2j3HutSTJerDown,_mvab2j3HutTTJerDown),w);
		  else if( isel == 1 ) h->Fill(std::max(_mvab2j4HutSTJerDown,_mvab2j4HutTTJerDown),w);
		  else if( isel == 2 ) h->Fill(std::max(_mvab3j3HutSTJerDown,_mvab3j3HutTTJerDown),w);
		  else if( isel == 3 ) h->Fill(std::max(_mvab3j4HutSTJerDown,_mvab3j4HutTTJerDown),w);
		  else if( isel == 4 ) h->Fill(std::max(_mvab4j4HutSTJerDown,_mvab4j4HutTTJerDown),w);
	       }	
	  }   
     }   
   else if( strcmp(varName.c_str(),"h_MVAHctMAX_") == 0 )
     {
	if( isData || (
		       !(strcmp(sys.c_str(),"_Jes_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jes_Down") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Up") == 0) &&
		       !(strcmp(sys.c_str(),"_Jer_Down") == 0)
		      )
	  )
	  {	     
	     if( isel == 0 ) h->Fill(std::max(_mvab2j3HctST,_mvab2j3HctTT),w);
	     else if( isel == 1 ) h->Fill(std::max(_mvab2j4HctST,_mvab2j4HctTT),w);
	     else if( isel == 2 ) h->Fill(std::max(_mvab3j3HctST,_mvab3j3HctTT),w);
	     else if( isel == 3 ) h->Fill(std::max(_mvab3j4HctST,_mvab3j4HctTT),w);
	     else if( isel == 4 ) h->Fill(std::max(_mvab4j4HctST,_mvab4j4HctTT),w);
	  }
	else if( !isData )
	  {	     
	     if( strcmp(sys.c_str(),"_Jes_Up") == 0 )
	       {
		  if( isel == 0 ) h->Fill(std::max(_mvab2j3HctSTJesUp,_mvab2j3HctTTJesUp),w);
		  else if( isel == 1 ) h->Fill(std::max(_mvab2j4HctSTJesUp,_mvab2j4HctTTJesUp),w);
		  else if( isel == 2 ) h->Fill(std::max(_mvab3j3HctSTJesUp,_mvab3j3HctTTJesUp),w);
		  else if( isel == 3 ) h->Fill(std::max(_mvab3j4HctSTJesUp,_mvab3j4HctTTJesUp),w);
		  else if( isel == 4 ) h->Fill(std::max(_mvab4j4HctSTJesUp,_mvab4j4HctTTJesUp),w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jes_Down") == 0 )
	       {
		  if( isel == 0 ) h->Fill(std::max(_mvab2j3HctSTJesDown,_mvab2j3HctTTJesDown),w);
		  else if( isel == 1 ) h->Fill(std::max(_mvab2j4HctSTJesDown,_mvab2j4HctTTJesDown),w);
		  else if( isel == 2 ) h->Fill(std::max(_mvab3j3HctSTJesDown,_mvab3j3HctTTJesDown),w);
		  else if( isel == 3 ) h->Fill(std::max(_mvab3j4HctSTJesDown,_mvab3j4HctTTJesDown),w);
		  else if( isel == 4 ) h->Fill(std::max(_mvab4j4HctSTJesDown,_mvab4j4HctTTJesDown),w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Up") == 0 )
	       {
		  if( isel == 0 ) h->Fill(std::max(_mvab2j3HctSTJerUp,_mvab2j3HctTTJerUp),w);
		  else if( isel == 1 ) h->Fill(std::max(_mvab2j4HctSTJerUp,_mvab2j4HctTTJerUp),w);
		  else if( isel == 2 ) h->Fill(std::max(_mvab3j3HctSTJerUp,_mvab3j3HctTTJerUp),w);
		  else if( isel == 3 ) h->Fill(std::max(_mvab3j4HctSTJerUp,_mvab3j4HctTTJerUp),w);
		  else if( isel == 4 ) h->Fill(std::max(_mvab4j4HctSTJerUp,_mvab4j4HctTTJerUp),w);
	       }	
	     else if( strcmp(sys.c_str(),"_Jer_Down") == 0 )
	       {
		  if( isel == 0 ) h->Fill(std::max(_mvab2j3HctSTJerDown,_mvab2j3HctTTJerDown),w);
		  else if( isel == 1 ) h->Fill(std::max(_mvab2j4HctSTJerDown,_mvab2j4HctTTJerDown),w);
		  else if( isel == 2 ) h->Fill(std::max(_mvab3j3HctSTJerDown,_mvab3j3HctTTJerDown),w);
		  else if( isel == 3 ) h->Fill(std::max(_mvab3j4HctSTJerDown,_mvab3j4HctTTJerDown),w);
		  else if( isel == 4 ) h->Fill(std::max(_mvab4j4HctSTJerDown,_mvab4j4HctTTJerDown),w);
	       }	     
	  }	
     }   
}

bool Hist::checkJet(int ijet,int isel)
{
   bool res = false;
   
/*   if( (isel == 0 || isel == 2 || isel == 4 || isel == 6) && (
		     ijet == _trec->HiggsBJet1_TOPHLEPBB_JetIdx() ||
		     ijet == _trec->HiggsBJet2_TOPHLEPBB_JetIdx() ||
		     ijet == _trec->TopLepBJet_TOPHLEPBB_JetIdx()
		    ) ) res = true;
   else if( (isel == 1 || isel == 3 || isel == 5 || isel == 7 || isel == 8) && (
			  ijet == _trec->HiggsBJet1_TOPHLEPBB_JetIdx() ||
			  ijet == _trec->HiggsBJet2_TOPHLEPBB_JetIdx() ||
			  ijet == _trec->TopLepBJet_TOPHLEPBB_JetIdx() ||
			  ijet == _trec->HiggsBJet1_TOPTOPLEPHBB_JetIdx() ||
			  ijet == _trec->HiggsBJet2_TOPTOPLEPHBB_JetIdx() ||
			  ijet == _trec->TopLepBJet_TOPTOPLEPHBB_JetIdx() ||
			  ijet == _trec->TopHadNonBJet_TOPTOPLEPHBB_JetIdx() ||
			  ijet == _trec->TopLepBJet_TOPTOPLEPHAD_JetIdx() ||
			  ijet == _trec->TopHadBJet_TOPTOPLEPHAD_JetIdx() ||
			  ijet == _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JetIdx() ||
			  ijet == _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JetIdx()
			 ) ) res = true;*/

   if( (isel == 0 || isel == 2) && (
		     ijet == _trec->HiggsBJet1_TOPHLEPBB_JetIdx() ||
		     ijet == _trec->HiggsBJet2_TOPHLEPBB_JetIdx() ||
		     ijet == _trec->TopLepBJet_TOPHLEPBB_JetIdx()
		    ) ) res = true;
   else if( (isel == 1 || isel == 3 || isel == 4) && (
			  ijet == _trec->HiggsBJet1_TOPHLEPBB_JetIdx() ||
			  ijet == _trec->HiggsBJet2_TOPHLEPBB_JetIdx() ||
			  ijet == _trec->TopLepBJet_TOPHLEPBB_JetIdx() ||
			  ijet == _trec->HiggsBJet1_TOPTOPLEPHBB_JetIdx() ||
			  ijet == _trec->HiggsBJet2_TOPTOPLEPHBB_JetIdx() ||
			  ijet == _trec->TopLepBJet_TOPTOPLEPHBB_JetIdx() ||
			  ijet == _trec->TopHadNonBJet_TOPTOPLEPHBB_JetIdx() ||
			  ijet == _trec->TopLepBJet_TOPTOPLEPHAD_JetIdx() ||
			  ijet == _trec->TopHadBJet_TOPTOPLEPHAD_JetIdx() ||
			  ijet == _trec->TopHadWNonBJet1_TOPTOPLEPHAD_JetIdx() ||
			  ijet == _trec->TopHadWNonBJet2_TOPTOPLEPHAD_JetIdx()
			 ) ) res = true;
   
   return res;
}

int Hist::findMVABin(float mvaST,float mvaTT)
{
   int res = -1;
   
   if( mvaTT >= 0.4 )
     {
	if( mvaST < -0.4 ) res = 0;
	else if( mvaST >= -0.4 && mvaST < -0.2 ) res = 1;
	else if( mvaST >= -0.2 && mvaST < 0. ) res = 2;
	else if( mvaST >= 0. && mvaST < 0.2 ) res = 3;
	else if( mvaST >= 0.2 && mvaST < 0.4 ) res = 4;
	else if( mvaST >= 0.4 ) res = 5;
     }   
   else if( mvaTT >= 0.2 && mvaTT < 0.4 )
     {
	if( mvaST < -0.4 ) res = 6;
	else if( mvaST >= -0.4 && mvaST < -0.2 ) res = 7;
	else if( mvaST >= -0.2 && mvaST < 0. ) res = 8;
	else if( mvaST >= 0. && mvaST < 0.2 ) res = 9;
	else if( mvaST >= 0.2 && mvaST < 0.4 ) res = 10;
	else if( mvaST >= 0.4 ) res = 11;
     }   
   else if( mvaTT >= 0. && mvaTT < 0.2 )
     {
	if( mvaST < -0.4 ) res = 12;
	else if( mvaST >= -0.4 && mvaST < -0.2 ) res = 13;
	else if( mvaST >= -0.2 && mvaST < 0. ) res = 14;
	else if( mvaST >= 0. && mvaST < 0.2 ) res = 15;
	else if( mvaST >= 0.2 && mvaST < 0.4 ) res = 16;
	else if( mvaST >= 0.4 ) res = 17;
     }   
   else if( mvaTT >= -0.2 && mvaTT < 0. )
     {
	if( mvaST < -0.4 ) res = 18;
	else if( mvaST >= -0.4 && mvaST < -0.2 ) res = 19;
	else if( mvaST >= -0.2 && mvaST < 0. ) res = 20;
	else if( mvaST >= 0. && mvaST < 0.2 ) res = 21;
	else if( mvaST >= 0.2 && mvaST < 0.4 ) res = 22;
	else if( mvaST >= 0.4 ) res = 23;
     }   
   else if( mvaTT >= -0.4 && mvaTT < -0.2 )
     {
	if( mvaST < -0.4 ) res = 24;
	else if( mvaST >= -0.4 && mvaST < -0.2 ) res = 25;
	else if( mvaST >= -0.2 && mvaST < 0. ) res = 26;
	else if( mvaST >= 0. && mvaST < 0.2 ) res = 27;
	else if( mvaST >= 0.2 && mvaST < 0.4 ) res = 28;
	else if( mvaST >= 0.4 ) res = 29;
     }   
   else if( mvaTT < -0.4 )
     {
	if( mvaST < -0.4 ) res = 30;
	else if( mvaST >= -0.4 && mvaST < -0.2 ) res = 31;
	else if( mvaST >= -0.2 && mvaST < 0. ) res = 32;
	else if( mvaST >= 0. && mvaST < 0.2 ) res = 33;
	else if( mvaST >= 0.2 && mvaST < 0.4 ) res = 34;
	else if( mvaST >= 0.4 ) res = 35;
     }   
   
   return res;
}
