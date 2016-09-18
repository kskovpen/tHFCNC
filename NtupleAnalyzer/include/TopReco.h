#ifndef TOPRECO_H
#define TOPRECO_H

#include "Analyzer.h"

#include "Helper.h"

#include "kinfit.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

class TopReco
{
   
 public:

   TopReco();
   virtual ~TopReco();
   
   void setElectron(std::vector<Electron> *v)                {_v_Electron = v;};
   void setMuon(std::vector<Muon> *v)                        {_v_Muon = v;};
   void setJet(std::vector<Jet> *v)                          {_v_Jet = v;};
   void setBJet(std::vector<Jet> *v)                         {_v_BJet = v;};
   void setNonBJet(std::vector<Jet> *v)                      {_v_NonBJet = v;};
   void setEvent(std::vector<Event> *v)                      {_v_Event = v;};
   void setLepton(std::vector<Lepton> *v)                    {_v_Lepton = v;};
	
   void init();
   void run();
   void close();

   TLorentzVector TopLepBJet_TOPTOPLEPHBB_p4()      {return _TopLepBJet_TOPTOPLEPHBB_p4;};
   TLorentzVector HiggsBJet1_TOPTOPLEPHBB_p4()      {return _HiggsBJet1_TOPTOPLEPHBB_p4;};
   TLorentzVector HiggsBJet2_TOPTOPLEPHBB_p4()      {return _HiggsBJet2_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLepWLep_TOPTOPLEPHBB_p4()      {return _TopLepWLep_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLepWNu_TOPTOPLEPHBB_p4()       {return _TopLepWNu_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLep_TOPTOPLEPHBB_p4()          {return _TopLep_TOPTOPLEPHBB_p4;};
   TLorentzVector Higgs_TOPTOPLEPHBB_p4()           {return _Higgs_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLepW_TOPTOPLEPHBB_p4()         {return _TopLepW_TOPTOPLEPHBB_p4;};
   TLorentzVector TopHadNonBJet_TOPTOPLEPHBB_p4()   {return _TopHadNonBJet_TOPTOPLEPHBB_p4;};

   TLorentzVector TopLepBJetT_TOPTOPLEPHBB_p4()      {return _TopLepBJetT_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLepWLepT_TOPTOPLEPHBB_p4()      {return _TopLepWLepT_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLepWNuT_TOPTOPLEPHBB_p4()       {return _TopLepWNuT_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLepT_TOPTOPLEPHBB_p4()   {return _TopLepT_TOPTOPLEPHBB_p4;};
   TLorentzVector HiggsT_TOPTOPLEPHBB_p4()   {return _HiggsT_TOPTOPLEPHBB_p4;};
   
   double chi2()       {return _chi2;};
   
 protected:

   std::vector<Lepton>             *_v_Lepton;
   
   std::vector<Electron>           *_v_Electron;
   std::vector<Muon>               *_v_Muon;
   std::vector<Electron>           *_v_ElectronTight;
   std::vector<Muon>               *_v_MuonTight;
   
   std::vector<Event>              *_v_Event;
   std::vector<Jet>                *_v_Jet;
   std::vector<Jet>                *_v_BJet;
   std::vector<Jet>                *_v_NonBJet;
   std::vector<Jet>                *_v_JetTight;
   std::vector<Jet>                *_v_BJetTight;
   std::vector<Jet>                *_v_NonBJetTight;

   Helper *help;
   
 private:

   TLorentzVector _TopLepBJet_TOPTOPLEPHBB_p4;
   TLorentzVector _HiggsBJet1_TOPTOPLEPHBB_p4;
   TLorentzVector _HiggsBJet2_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLepWLep_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLepWNu_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLep_TOPTOPLEPHBB_p4;
   TLorentzVector _Higgs_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLepW_TOPTOPLEPHBB_p4;
   TLorentzVector _TopHadNonBJet_TOPTOPLEPHBB_p4;
   
   TLorentzVector _TopLepBJetT_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLepWLepT_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLepWNuT_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLepT_TOPTOPLEPHBB_p4;
   TLorentzVector _HiggsT_TOPTOPLEPHBB_p4;
   
   double _chi2;
   
   TRandom3 *rnd;

   KINFIT::kfit *kfTopTopLepHbb;
   KINFIT::kfit *kfTopHLepbb;
   KINFIT::kfit *kfTopTopLepHad;

   TMVA::Reader* MVAFullRecoReaderTOPTOPLEPHBB;
   TMVA::Reader* MVAPartRecoReaderTOPTOPLEPHBB;

   float MVAFullReco_HiggsRecM_TOPTOPLEPHBB;
   float MVAFullReco_TopLepRecM_TOPTOPLEPHBB;
   float MVAFullReco_HiggsTopLepRecDr_TOPTOPLEPHBB;
   float MVAFullReco_TopLepRecPt_TOPTOPLEPHBB;
   
   float MVAPartReco_HiggsRecM_TOPTOPLEPHBB;
   float MVAPartReco_TopLepRecMT_TOPTOPLEPHBB;
   float MVAPartReco_HiggsTopLepRecDphiT_TOPTOPLEPHBB;
   float MVAPartReco_TopLepRecPtT_TOPTOPLEPHBB;
};

#endif
