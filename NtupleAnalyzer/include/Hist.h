#ifndef HIST_H
#define HIST_H

#include "Analyzer.h"

#include "TopReco.h"
#include "Helper.h"

//#include "FakeWeight.h"

class Hist
{
   
 public:
   
   Hist();
   virtual ~Hist();
   
   void setElectron(std::vector<Electron> *v)                  {_v_Electron = v;};
   void setMuon(std::vector<Muon> *v)                      {_v_Muon = v;};
   void setJet(std::vector<Jet> *v)                      {_v_Jet = v;};
   void setEvent(std::vector<Event> *v)                      {_v_Event = v;};
   void setTruth(std::vector<Truth> *v)                      {_v_Truth = v;};

//   void setFakeWeight(SKYPLOT::FakeWeight fakeWeight)      {_fakeWeight = fakeWeight;}; 
	
   void init();
   void fill();
   void close();
   bool printout(bool doPrint);

   std::vector<Lepton> filterPt(double Pt1, double Pt2, double Pt3,
				std::vector<Electron>* ntElectron,
				std::vector<Muon>* ntMuon);
   
   unsigned int passSel;
   
   std::vector<TLorentzVector> lep_tlv(std::string sys,int llc,bool isTIGHT);
   std::vector<TLorentzVector> jet_tlv(std::string sys); 
   
   void fillHisto1D(TH1D *h,float sfj,std::string sys,int ilep,std::string varName);

   void fillPassSel(TH1D *h,float sfj);
     
   float getWmassBW(float mWmean,float GammaW);
   float BW(float mW,float mWmean,float GammaW);
   bool getNuMom(float Wmass,float px_l,float py_l,float pz_l,float E_l,
		 float px_nu,float py_nu,float &pz_nu1,float &pz_nu2);
   
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
   std::string jets[100];                                                                                              
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

   int jets_n;
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
   int m_channel;
   int m_sel;
   
   float m_wmassGen;
   int m_foundNuMom;
   int m_truthMatch;
   
/*   int m_l1_type;
   int m_l1_charge;
   double m_l1_pt;
   double m_l1_eta;
   double m_l1_phi;
   double m_l1_m;*/
   
 protected:

   std::vector<Lepton>             *_v_Lepton;
   
   std::vector<Electron>             *_v_Electron;
   std::vector<Muon>             *_v_Muon;
   std::vector<Electron>             *_v_ElectronTight;
   std::vector<Muon>             *_v_MuonTight;
   
   std::vector<Event>             *_v_Event;
   std::vector<Jet>             *_v_Jet;
   std::vector<Jet>             *_v_JetTight;
   std::vector<Jet>             *_v_BJetTight;
   
   std::vector<Truth>             *_v_Truth;
   
//   SKYPLOT::FakeWeight           _fakeWeight;
  
   std::map<std::string, TH1D*> *_m1d_Hist;
   
   TH1D *_h_PassSel;

   std::vector<std::pair<std::vector<std::string>,double*> > *_s_Hist;
	
 private:

   // [JETS][CHAN][TYPE][SEL][VAR][2*(NSYS-1)+1]
   std::string histNAMES[5][5][5][5][100][2];
   
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

   int _recAlg;
   
   TLorentzVector _topb_p4;
   TLorentzVector _Hb1_p4;
   TLorentzVector _Hb2_p4;
   TLorentzVector _l_p4;
   TLorentzVector _nu_p4;
   TLorentzVector _top_p4;
   TLorentzVector _H_p4;
   TLorentzVector _W_p4;
   
   FILE *_fevc;
   std::ofstream _fevcVal;
	
   TRandom3 *rnd;
   
   TFile *_fout;
   TTree *_trout;
   
   TopReco *_trec;
   
   Helper *help;
};

#endif
