#ifndef HIST_H
#define HIST_H

#include "Analyzer.h"

#include "TopReco.h"
#include "ApplyMVA.h"
#include "Helper.h"

//#include "FakeWeight.h"

class Hist
{
   
 public:
   
   Hist(std::string home,bool evec);
   virtual ~Hist();
   
   void setElectronTight(std::vector<Electron> *v)                  {_v_ElectronTight = v;};
   void setElectronLoose(std::vector<Electron> *v)                  {_v_ElectronLoose = v;};
   void setMuonTight(std::vector<Muon> *v)                      {_v_MuonTight = v;};
   void setMuonLoose(std::vector<Muon> *v)                      {_v_MuonLoose = v;};
   void setJet(std::vector<Jet> *v)                      {_v_Jet = v;};
   void setEvent(std::vector<Event> *v)                      {_v_Event = v;};
   void setTruth(std::vector<Truth> *v)                      {_v_Truth = v;};

//   void setFakeWeight(SKYPLOT::FakeWeight fakeWeight)      {_fakeWeight = fakeWeight;}; 
	
   void init();
   void fill();
   void close();

   void printout(bool doPrint,
		 int run,int lumi,int id,
		 int lepId,float lepPt,float lepEta,float lepPhi,
		 float metpt,float metphi,
		 int njets,int nbjets,float jetPt,float jetEta,float jetPhi);
   
   void fillTree(int ic,int is);

   std::vector<Lepton> filterPt(double Pt1, double Pt2, double Pt3,
				std::vector<Electron>* ntElectron,
				std::vector<Muon>* ntMuon);
   
   unsigned int passSel_all;
   unsigned int passSel_e;
   unsigned int passSel_m;
   unsigned int passSel_ev;
   
   void fillHisto1D(TH1D *h,float sfj0,float sfj,std::string sys,int ilep,std::string varName,bool isData,int isel,int idxSR);
   
   bool checkJet(int ijet,int isel);
   
   int findMVABin(float mvaST,float mvaTT);
   
//   float getVar(std::string sys,int ijet,std::string varName,int ibin);
//   std::vector<float> getVarVec(std::string sys,int ijet,std::string varName,int ibin);
//   std::pair<float,float> getVar2d(std::string sys,int ijet,std::string varName,int ibin);
//   std::vector<float> getVar3d(std::string sys,int ijet,std::string varName,int ibin);
//   float getPt(std::string sys);
//   double DeltaR(double eta1,double phi1,double eta2,double phi2);

//   double getSF(std::vector<std::pair<double,double> > vBin,
//		std::vector<std::pair<double,double> > vSf,
//		double var);
//   double get2DSF(std::vector<std::pair<double,double> > vBinX,
//		  std::vector<std::pair<double,double> > vBinY,
//		  std::vector<std::pair<double,double> > vSf,
//		  double varX,
//		  double varY);
	
   std::string chan[100];
//   std::string char[100];                                                                                           
   std::string sys[100];                                                                                               
   std::string sys_low[100];                                                                                           
   std::string sys_up[100];                                                                                            
   std::string histname[100];
   std::string type[100];                                                                                              
   std::string sel[100];                                                                                               
   
   std::vector<std::string> hname;
	
   // var / ptbin / bins / x1,x2
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rwBin;
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rwSf;
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rwBin_btag;
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rwSf_btag;
   
   // var[0] / ptbin / bins / v1,v2
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rw3DBinX;
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rw3DBinY;
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rw3DBinZ;
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rw3DSf;
   
   // var[0] / ptbin / bins / v1,v2
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rw2DBinX;
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rw2DBinY;
//   std::vector<std::vector<std::vector<std::pair<double,double> > > > rw2DSf;

   int sel_n;
   int chan_n;
   int histname_n;
   int type_n;
   int sys_n;                                                                                                          
   int sys_low_n;
   int sys_up_n;
   int n_jets;
	
   bool fillThis;

   // Tree variables
   double m_weight;

   // nominal
   double m_HiggsMass_TOPTOPLEPHBB;
   double m_HiggsMass_TOPHLEPBB;
   double m_TopHadMass_TOPTOPLEPHAD;
   double m_chi2_TOPTOPLEPHBB;
   double m_chi2_TOPHLEPBB;
   double m_chi2_TOPTOPLEPHAD;
   double m_MVA_TOPTOPLEPHBB;
   double m_MVA_TOPHLEPBB;
   double m_MVA_TOPTOPLEPHAD;
   int m_LepCharge;
   double m_HiggsEta_TOPTOPLEPHBB;
   double m_HiggsEta_TOPHLEPBB;
   double m_TopLepMass_TOPTOPLEPHBB;
   double m_TopLepMass_TOPHLEPBB;
   double m_TopLepMass_TOPTOPLEPHAD;
   double m_TopLepPt_TOPTOPLEPHBB;
   double m_TopLepPt_TOPHLEPBB;
   double m_TopLepPt_TOPTOPLEPHAD;
   double m_TopLepEta_TOPTOPLEPHBB;
   double m_TopLepEta_TOPHLEPBB;
   double m_TopLepEta_TOPTOPLEPHAD;
   double m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
   double m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
   double m_TopLepHiggsDr_TOPTOPLEPHBB;
   double m_TopLepHiggsDr_TOPHLEPBB;
   double m_TopLepTopHadDr_TOPTOPLEPHAD;
   double m_HiggsBJet1CSVv2_TOPTOPLEPHBB;
   double m_HiggsBJet2CSVv2_TOPTOPLEPHBB;
   double m_TopLepBJetCSVv2_TOPTOPLEPHBB;
   double m_TopHadNonBJetCSVv2_TOPTOPLEPHBB;
   double m_HiggsBJet1CSVv2_TOPHLEPBB;
   double m_HiggsBJet2CSVv2_TOPHLEPBB;
   double m_TopLepBJetCSVv2_TOPHLEPBB;
   double m_TopLepBJetCSVv2_TOPTOPLEPHAD;
   double m_TopHadBJetCSVv2_TOPTOPLEPHAD;
   double m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD;
   double m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD;

   // JesUp
   double m_HiggsMass_TOPTOPLEPHBB_JesUp;
   double m_HiggsMass_TOPHLEPBB_JesUp;
   double m_TopHadMass_TOPTOPLEPHAD_JesUp;
   double m_chi2_TOPTOPLEPHBB_JesUp;
   double m_chi2_TOPHLEPBB_JesUp;
   double m_chi2_TOPTOPLEPHAD_JesUp;
   double m_MVA_TOPTOPLEPHBB_JesUp;
   double m_MVA_TOPHLEPBB_JesUp;
   double m_MVA_TOPTOPLEPHAD_JesUp;
   int m_LepCharge_JesUp;
   double m_HiggsEta_TOPTOPLEPHBB_JesUp;
   double m_HiggsEta_TOPHLEPBB_JesUp;
   double m_TopLepMass_TOPTOPLEPHBB_JesUp;
   double m_TopLepMass_TOPHLEPBB_JesUp;
   double m_TopLepMass_TOPTOPLEPHAD_JesUp;
   double m_TopLepPt_TOPTOPLEPHBB_JesUp;
   double m_TopLepPt_TOPHLEPBB_JesUp;
   double m_TopLepPt_TOPTOPLEPHAD_JesUp;
   double m_TopLepEta_TOPTOPLEPHBB_JesUp;
   double m_TopLepEta_TOPHLEPBB_JesUp;
   double m_TopLepEta_TOPTOPLEPHAD_JesUp;
   double m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JesUp;
   double m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JesUp;
   double m_TopLepHiggsDr_TOPTOPLEPHBB_JesUp;
   double m_TopLepHiggsDr_TOPHLEPBB_JesUp;
   double m_TopLepTopHadDr_TOPTOPLEPHAD_JesUp;
   double m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JesUp;
   double m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JesUp;
   double m_TopLepBJetCSVv2_TOPTOPLEPHBB_JesUp;
   double m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JesUp;
   double m_HiggsBJet1CSVv2_TOPHLEPBB_JesUp;
   double m_HiggsBJet2CSVv2_TOPHLEPBB_JesUp;
   double m_TopLepBJetCSVv2_TOPHLEPBB_JesUp;
   double m_TopLepBJetCSVv2_TOPTOPLEPHAD_JesUp;
   double m_TopHadBJetCSVv2_TOPTOPLEPHAD_JesUp;
   double m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JesUp;
   double m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JesUp;

   // JesDown
   double m_HiggsMass_TOPTOPLEPHBB_JesDown;
   double m_HiggsMass_TOPHLEPBB_JesDown;
   double m_TopHadMass_TOPTOPLEPHAD_JesDown;
   double m_chi2_TOPTOPLEPHBB_JesDown;
   double m_chi2_TOPHLEPBB_JesDown;
   double m_chi2_TOPTOPLEPHAD_JesDown;
   double m_MVA_TOPTOPLEPHBB_JesDown;
   double m_MVA_TOPHLEPBB_JesDown;
   double m_MVA_TOPTOPLEPHAD_JesDown;
   int m_LepCharge_JesDown;
   double m_HiggsEta_TOPTOPLEPHBB_JesDown;
   double m_HiggsEta_TOPHLEPBB_JesDown;
   double m_TopLepMass_TOPTOPLEPHBB_JesDown;
   double m_TopLepMass_TOPHLEPBB_JesDown;
   double m_TopLepMass_TOPTOPLEPHAD_JesDown;
   double m_TopLepPt_TOPTOPLEPHBB_JesDown;
   double m_TopLepPt_TOPHLEPBB_JesDown;
   double m_TopLepPt_TOPTOPLEPHAD_JesDown;
   double m_TopLepEta_TOPTOPLEPHBB_JesDown;
   double m_TopLepEta_TOPHLEPBB_JesDown;
   double m_TopLepEta_TOPTOPLEPHAD_JesDown;
   double m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JesDown;
   double m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JesDown;
   double m_TopLepHiggsDr_TOPTOPLEPHBB_JesDown;
   double m_TopLepHiggsDr_TOPHLEPBB_JesDown;
   double m_TopLepTopHadDr_TOPTOPLEPHAD_JesDown;
   double m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JesDown;
   double m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JesDown;
   double m_TopLepBJetCSVv2_TOPTOPLEPHBB_JesDown;
   double m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JesDown;
   double m_HiggsBJet1CSVv2_TOPHLEPBB_JesDown;
   double m_HiggsBJet2CSVv2_TOPHLEPBB_JesDown;
   double m_TopLepBJetCSVv2_TOPHLEPBB_JesDown;
   double m_TopLepBJetCSVv2_TOPTOPLEPHAD_JesDown;
   double m_TopHadBJetCSVv2_TOPTOPLEPHAD_JesDown;
   double m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JesDown;
   double m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JesDown;

   // JerUp
   double m_HiggsMass_TOPTOPLEPHBB_JerUp;
   double m_HiggsMass_TOPHLEPBB_JerUp;
   double m_TopHadMass_TOPTOPLEPHAD_JerUp;
   double m_chi2_TOPTOPLEPHBB_JerUp;
   double m_chi2_TOPHLEPBB_JerUp;
   double m_chi2_TOPTOPLEPHAD_JerUp;
   double m_MVA_TOPTOPLEPHBB_JerUp;
   double m_MVA_TOPHLEPBB_JerUp;
   double m_MVA_TOPTOPLEPHAD_JerUp;
   int m_LepCharge_JerUp;
   double m_HiggsEta_TOPTOPLEPHBB_JerUp;
   double m_HiggsEta_TOPHLEPBB_JerUp;
   double m_TopLepMass_TOPTOPLEPHBB_JerUp;
   double m_TopLepMass_TOPHLEPBB_JerUp;
   double m_TopLepMass_TOPTOPLEPHAD_JerUp;
   double m_TopLepPt_TOPTOPLEPHBB_JerUp;
   double m_TopLepPt_TOPHLEPBB_JerUp;
   double m_TopLepPt_TOPTOPLEPHAD_JerUp;
   double m_TopLepEta_TOPTOPLEPHBB_JerUp;
   double m_TopLepEta_TOPHLEPBB_JerUp;
   double m_TopLepEta_TOPTOPLEPHAD_JerUp;
   double m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JerUp;
   double m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JerUp;
   double m_TopLepHiggsDr_TOPTOPLEPHBB_JerUp;
   double m_TopLepHiggsDr_TOPHLEPBB_JerUp;
   double m_TopLepTopHadDr_TOPTOPLEPHAD_JerUp;
   double m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JerUp;
   double m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JerUp;
   double m_TopLepBJetCSVv2_TOPTOPLEPHBB_JerUp;
   double m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JerUp;
   double m_HiggsBJet1CSVv2_TOPHLEPBB_JerUp;
   double m_HiggsBJet2CSVv2_TOPHLEPBB_JerUp;
   double m_TopLepBJetCSVv2_TOPHLEPBB_JerUp;
   double m_TopLepBJetCSVv2_TOPTOPLEPHAD_JerUp;
   double m_TopHadBJetCSVv2_TOPTOPLEPHAD_JerUp;
   double m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JerUp;
   double m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JerUp;

   // JerDown
   double m_HiggsMass_TOPTOPLEPHBB_JerDown;
   double m_HiggsMass_TOPHLEPBB_JerDown;
   double m_TopHadMass_TOPTOPLEPHAD_JerDown;
   double m_chi2_TOPTOPLEPHBB_JerDown;
   double m_chi2_TOPHLEPBB_JerDown;
   double m_chi2_TOPTOPLEPHAD_JerDown;
   double m_MVA_TOPTOPLEPHBB_JerDown;
   double m_MVA_TOPHLEPBB_JerDown;
   double m_MVA_TOPTOPLEPHAD_JerDown;
   int m_LepCharge_JerDown;
   double m_HiggsEta_TOPTOPLEPHBB_JerDown;
   double m_HiggsEta_TOPHLEPBB_JerDown;
   double m_TopLepMass_TOPTOPLEPHBB_JerDown;
   double m_TopLepMass_TOPHLEPBB_JerDown;
   double m_TopLepMass_TOPTOPLEPHAD_JerDown;
   double m_TopLepPt_TOPTOPLEPHBB_JerDown;
   double m_TopLepPt_TOPHLEPBB_JerDown;
   double m_TopLepPt_TOPTOPLEPHAD_JerDown;
   double m_TopLepEta_TOPTOPLEPHBB_JerDown;
   double m_TopLepEta_TOPHLEPBB_JerDown;
   double m_TopLepEta_TOPTOPLEPHAD_JerDown;
   double m_HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB_JerDown;
   double m_HiggsBJet1HiggsBJet2Dr_TOPHLEPBB_JerDown;
   double m_TopLepHiggsDr_TOPTOPLEPHBB_JerDown;
   double m_TopLepHiggsDr_TOPHLEPBB_JerDown;
   double m_TopLepTopHadDr_TOPTOPLEPHAD_JerDown;
   double m_HiggsBJet1CSVv2_TOPTOPLEPHBB_JerDown;
   double m_HiggsBJet2CSVv2_TOPTOPLEPHBB_JerDown;
   double m_TopLepBJetCSVv2_TOPTOPLEPHBB_JerDown;
   double m_TopHadNonBJetCSVv2_TOPTOPLEPHBB_JerDown;
   double m_HiggsBJet1CSVv2_TOPHLEPBB_JerDown;
   double m_HiggsBJet2CSVv2_TOPHLEPBB_JerDown;
   double m_TopLepBJetCSVv2_TOPHLEPBB_JerDown;
   double m_TopLepBJetCSVv2_TOPTOPLEPHAD_JerDown;
   double m_TopHadBJetCSVv2_TOPTOPLEPHAD_JerDown;
   double m_TopHadWNonBJet1CSVv2_TOPTOPLEPHAD_JerDown;
   double m_TopHadWNonBJet2CSVv2_TOPTOPLEPHAD_JerDown;
   
 protected:

   std::vector<Lepton> *_v_Lepton;
   
   std::vector<Electron>             *_v_ElectronTight;
   std::vector<Electron>             *_v_ElectronLoose;
   std::vector<Muon>             *_v_MuonTight;
   std::vector<Muon>             *_v_MuonLoose;
   
   std::vector<Event>             *_v_Event;
   std::vector<Jet>             *_v_Jet;
   std::vector<Jet>             *_v_JetTight;
   std::vector<Jet>             *_v_BJetTight;
   std::vector<Jet>             *_v_NonBJetTight;
   
   std::vector<Truth>             *_v_Truth;
   
//   SKYPLOT::FakeWeight           _fakeWeight;
  
   std::map<std::string, TH1D*> *_m1d_Hist;
   
/*   TH1D *_h_PassSel_all;
   TH1D *_h_PassSel_e;
   TH1D *_h_PassSel_m;

   TH1D *_h_PassSel_all_ttbb;
   TH1D *_h_PassSel_e_ttbb;
   TH1D *_h_PassSel_m_ttbb;

   TH1D *_h_PassSel_all_ttcc;
   TH1D *_h_PassSel_e_ttcc;
   TH1D *_h_PassSel_m_ttcc;

   TH1D *_h_PassSel_all_ttlf;
   TH1D *_h_PassSel_e_ttlf;
   TH1D *_h_PassSel_m_ttlf;*/
   
   std::vector<std::pair<std::vector<std::string>,double*> > *_s_Hist;
	
 private:

   // [CHAN][TYPE][SEL][VAR][2*(NSYS-1)+1]
   std::string histNAMES[5][5][7][40][40];
   
//   JetCorrectionUncertainty *jesTotal;
   
   double cJER[5];
   double cJER_down[5];
   double cJER_up[5];
	
//	TLorentzVector *v_jet;
//	TLorentzVector *v_jet_sys_jesTotalUp;
//	TLorentzVector *v_jet_sys_jesTotalLow;
//	TLorentzVector *v_jet_sys_jerTotalUp;
//	TLorentzVector *v_jet_sys_jerTotalLow;
//	TLorentzVector *v_mu;
   
   FILE *_fevc;
   std::ofstream _fevcVal;
   
   std::string _home;
   bool _evec;
   
   TRandom3 *rnd;
   
   TFile *_fout;
   TTree *_trout[10][10];

   TopReco *_trec;
   
   ApplyMVA *_mva;
   ApplyMVA *_mvaJesUp;
   ApplyMVA *_mvaJesDown;
   ApplyMVA *_mvaJerUp;
   ApplyMVA *_mvaJerDown;
   
   Helper *help;

   // nominal
   double _mvab0j3HutST;
   double _mvab0j3HctST;
   double _mvab0j3HutTT;
   double _mvab0j3HctTT;

   double _mvab0j4HutST;
   double _mvab0j4HctST;
   double _mvab0j4HutTT;
   double _mvab0j4HctTT;

   double _mvab1j3HutST;
   double _mvab1j3HctST;
   double _mvab1j3HutTT;
   double _mvab1j3HctTT;

   double _mvab1j4HutST;
   double _mvab1j4HctST;
   double _mvab1j4HutTT;
   double _mvab1j4HctTT;

   double _mvab2j3HutST;
   double _mvab2j3HctST;
   double _mvab2j3HutTT;
   double _mvab2j3HctTT;

   double _mvab2j4HutST;
   double _mvab2j4HctST;
   double _mvab2j4HutTT;
   double _mvab2j4HctTT;

   double _mvab3j3HutST;
   double _mvab3j3HctST;
   double _mvab3j3HutTT;
   double _mvab3j3HctTT;

   double _mvab3j4HutST;
   double _mvab3j4HctST;
   double _mvab3j4HutTT;
   double _mvab3j4HctTT;

   double _mvab4j4HutST;
   double _mvab4j4HctST;
   double _mvab4j4HutTT;
   double _mvab4j4HctTT;

   // JesUp
   double _mvab0j3HutSTJesUp;
   double _mvab0j3HctSTJesUp;
   double _mvab0j3HutTTJesUp;
   double _mvab0j3HctTTJesUp;

   double _mvab0j4HutSTJesUp;
   double _mvab0j4HctSTJesUp;
   double _mvab0j4HutTTJesUp;
   double _mvab0j4HctTTJesUp;

   double _mvab1j3HutSTJesUp;
   double _mvab1j3HctSTJesUp;
   double _mvab1j3HutTTJesUp;
   double _mvab1j3HctTTJesUp;

   double _mvab1j4HutSTJesUp;
   double _mvab1j4HctSTJesUp;
   double _mvab1j4HutTTJesUp;
   double _mvab1j4HctTTJesUp;

   double _mvab2j3HutSTJesUp;
   double _mvab2j3HctSTJesUp;
   double _mvab2j3HutTTJesUp;
   double _mvab2j3HctTTJesUp;

   double _mvab2j4HutSTJesUp;
   double _mvab2j4HctSTJesUp;
   double _mvab2j4HutTTJesUp;
   double _mvab2j4HctTTJesUp;

   double _mvab3j3HutSTJesUp;
   double _mvab3j3HctSTJesUp;
   double _mvab3j3HutTTJesUp;
   double _mvab3j3HctTTJesUp;

   double _mvab3j4HutSTJesUp;
   double _mvab3j4HctSTJesUp;
   double _mvab3j4HutTTJesUp;
   double _mvab3j4HctTTJesUp;

   double _mvab4j4HutSTJesUp;
   double _mvab4j4HctSTJesUp;
   double _mvab4j4HutTTJesUp;
   double _mvab4j4HctTTJesUp;

   // JesDown
   double _mvab0j3HutSTJesDown;
   double _mvab0j3HctSTJesDown;
   double _mvab0j3HutTTJesDown;
   double _mvab0j3HctTTJesDown;

   double _mvab0j4HutSTJesDown;
   double _mvab0j4HctSTJesDown;
   double _mvab0j4HutTTJesDown;
   double _mvab0j4HctTTJesDown;

   double _mvab1j3HutSTJesDown;
   double _mvab1j3HctSTJesDown;
   double _mvab1j3HutTTJesDown;
   double _mvab1j3HctTTJesDown;

   double _mvab1j4HutSTJesDown;
   double _mvab1j4HctSTJesDown;
   double _mvab1j4HutTTJesDown;
   double _mvab1j4HctTTJesDown;

   double _mvab2j3HutSTJesDown;
   double _mvab2j3HctSTJesDown;
   double _mvab2j3HutTTJesDown;
   double _mvab2j3HctTTJesDown;

   double _mvab2j4HutSTJesDown;
   double _mvab2j4HctSTJesDown;
   double _mvab2j4HutTTJesDown;
   double _mvab2j4HctTTJesDown;

   double _mvab3j3HutSTJesDown;
   double _mvab3j3HctSTJesDown;
   double _mvab3j3HutTTJesDown;
   double _mvab3j3HctTTJesDown;

   double _mvab3j4HutSTJesDown;
   double _mvab3j4HctSTJesDown;
   double _mvab3j4HutTTJesDown;
   double _mvab3j4HctTTJesDown;

   double _mvab4j4HutSTJesDown;
   double _mvab4j4HctSTJesDown;
   double _mvab4j4HutTTJesDown;
   double _mvab4j4HctTTJesDown;

   // JerUp
   double _mvab0j3HutSTJerUp;
   double _mvab0j3HctSTJerUp;
   double _mvab0j3HutTTJerUp;
   double _mvab0j3HctTTJerUp;

   double _mvab0j4HutSTJerUp;
   double _mvab0j4HctSTJerUp;
   double _mvab0j4HutTTJerUp;
   double _mvab0j4HctTTJerUp;

   double _mvab1j3HutSTJerUp;
   double _mvab1j3HctSTJerUp;
   double _mvab1j3HutTTJerUp;
   double _mvab1j3HctTTJerUp;

   double _mvab1j4HutSTJerUp;
   double _mvab1j4HctSTJerUp;
   double _mvab1j4HutTTJerUp;
   double _mvab1j4HctTTJerUp;

   double _mvab2j3HutSTJerUp;
   double _mvab2j3HctSTJerUp;
   double _mvab2j3HutTTJerUp;
   double _mvab2j3HctTTJerUp;

   double _mvab2j4HutSTJerUp;
   double _mvab2j4HctSTJerUp;
   double _mvab2j4HutTTJerUp;
   double _mvab2j4HctTTJerUp;

   double _mvab3j3HutSTJerUp;
   double _mvab3j3HctSTJerUp;
   double _mvab3j3HutTTJerUp;
   double _mvab3j3HctTTJerUp;

   double _mvab3j4HutSTJerUp;
   double _mvab3j4HctSTJerUp;
   double _mvab3j4HutTTJerUp;
   double _mvab3j4HctTTJerUp;

   double _mvab4j4HutSTJerUp;
   double _mvab4j4HctSTJerUp;
   double _mvab4j4HutTTJerUp;
   double _mvab4j4HctTTJerUp;

   // JerDown
   double _mvab0j3HutSTJerDown;
   double _mvab0j3HctSTJerDown;
   double _mvab0j3HutTTJerDown;
   double _mvab0j3HctTTJerDown;

   double _mvab0j4HutSTJerDown;
   double _mvab0j4HctSTJerDown;
   double _mvab0j4HutTTJerDown;
   double _mvab0j4HctTTJerDown;

   double _mvab1j3HutSTJerDown;
   double _mvab1j3HctSTJerDown;
   double _mvab1j3HutTTJerDown;
   double _mvab1j3HctTTJerDown;

   double _mvab1j4HutSTJerDown;
   double _mvab1j4HctSTJerDown;
   double _mvab1j4HutTTJerDown;
   double _mvab1j4HctTTJerDown;

   double _mvab2j3HutSTJerDown;
   double _mvab2j3HctSTJerDown;
   double _mvab2j3HutTTJerDown;
   double _mvab2j3HctTTJerDown;

   double _mvab2j4HutSTJerDown;
   double _mvab2j4HctSTJerDown;
   double _mvab2j4HutTTJerDown;
   double _mvab2j4HctTTJerDown;

   double _mvab3j3HutSTJerDown;
   double _mvab3j3HctSTJerDown;
   double _mvab3j3HutTTJerDown;
   double _mvab3j3HctTTJerDown;

   double _mvab3j4HutSTJerDown;
   double _mvab3j4HctSTJerDown;
   double _mvab3j4HutTTJerDown;
   double _mvab3j4HctTTJerDown;

   double _mvab4j4HutSTJerDown;
   double _mvab4j4HctSTJerDown;
   double _mvab4j4HutTTJerDown;
   double _mvab4j4HctTTJerDown;
};

#endif
