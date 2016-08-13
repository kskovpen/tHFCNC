#ifndef TOPRECO_H
#define TOPRECO_H

#include "Analyzer.h"

#include "Helper.h"

#include "kinfit.h"

class TopReco
{
   
 public:

   TopReco(std::string home,bool standalone,TFile *foutput);
   virtual ~TopReco();
   
   void setElectron(std::vector<Electron> *v)                {_v_Electron = v;};
   void setMuon(std::vector<Muon> *v)                        {_v_Muon = v;};
   void setJet(std::vector<Jet> *v)                          {_v_Jet = v;};
   void setBJet(std::vector<Jet> *v)                         {_v_BJet = v;};
   void setNonBJet(std::vector<Jet> *v)                      {_v_NonBJet = v;};
   void setEvent(std::vector<Event> *v)                      {_v_Event = v;};
   void setTruth(std::vector<Truth> *v)                      {_v_Truth = v;};
   void setLepton(std::vector<Lepton> *v)                    {_v_Lepton = v;};
	
   void init();
   bool run();
   void fill(float w,bool isMatch);
   void truthMatch();
   void truthMatchTTbar();
   void truthMatchAlg();
   void truthMatchAlgTTbar();
   void close();

   // methods for jet assignment
   
   int _useTruthMET;

   // results of reconstruction

   TLorentzVector topb_Top_p4()   {return _topb_Top_p4;};
   TLorentzVector Hb1_Top_p4()    {return _Hb1_Top_p4;};
   TLorentzVector Hb2_Top_p4()    {return _Hb2_Top_p4;};
   TLorentzVector l_Top_p4()      {return _l_Top_p4;};
   TLorentzVector nu_Top_p4()     {return _nu_Top_p4;};
   TLorentzVector top_Top_p4()    {return _top_Top_p4;};
   TLorentzVector H_Top_p4()      {return _H_Top_p4;};
   TLorentzVector W_Top_p4()      {return _W_Top_p4;};

   TLorentzVector topLep_TTbar_p4()     {return _topLep_TTbar_p4;};
   TLorentzVector topHad_TTbar_p4()     {return _topHad_TTbar_p4;};
   TLorentzVector topbLep_TTbar_p4()    {return _topbLep_TTbar_p4;};
   TLorentzVector topbHad_TTbar_p4()    {return _topbHad_TTbar_p4;};
   TLorentzVector l_TTbar_p4()          {return _l_TTbar_p4;};
   TLorentzVector nu_TTbar_p4()         {return _nu_TTbar_p4;};
   TLorentzVector WLep_TTbar_p4()       {return _WLep_TTbar_p4;};
   TLorentzVector WHad_TTbar_p4()       {return _WHad_TTbar_p4;};
   TLorentzVector topWj1_TTbar_p4()     {return _topWj1_TTbar_p4;};
   TLorentzVector topWj2_TTbar_p4()     {return _topWj2_TTbar_p4;};
   
   double chi2()       {return _chi2;};
   double chi2TTbar()  {return _chi2TTbar;};
   
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
   
   std::vector<Truth>              *_v_Truth;

   Helper *help;
   
 private:
   
   TLorentzVector _topb_p4;
   TLorentzVector _Hb1_p4;
   TLorentzVector _Hb2_p4;
   TLorentzVector _l_p4;
   TLorentzVector _nu_p4;
   TLorentzVector _top_p4;
   TLorentzVector _H_p4;
   TLorentzVector _W_p4;

   TLorentzVector _topbLep_p4;
   TLorentzVector _topbHad_p4;
   TLorentzVector _WLep_p4;
   TLorentzVector _WHad_p4;
   TLorentzVector _topLep_p4;
   TLorentzVector _topHad_p4;
   TLorentzVector _topWj1_p4;
   TLorentzVector _topWj2_p4;

   TLorentzVector _topb_Top_p4;
   TLorentzVector _Hb1_Top_p4;
   TLorentzVector _Hb2_Top_p4;
   TLorentzVector _l_Top_p4;
   TLorentzVector _nu_Top_p4;
   TLorentzVector _top_Top_p4;
   TLorentzVector _H_Top_p4;
   TLorentzVector _W_Top_p4;

   TLorentzVector _topLep_TTbar_p4;
   TLorentzVector _topHad_TTbar_p4;
   TLorentzVector _topbLep_TTbar_p4;
   TLorentzVector _topbHad_TTbar_p4;
   TLorentzVector _l_TTbar_p4;
   TLorentzVector _nu_TTbar_p4;
   TLorentzVector _WLep_TTbar_p4;
   TLorentzVector _WHad_TTbar_p4;
   TLorentzVector _topWj1_TTbar_p4;
   TLorentzVector _topWj2_TTbar_p4;
   
   // truth particles
   TLorentzVector _topb_truth_p4;
   TLorentzVector _topb1_truth_p4;
   TLorentzVector _topb2_truth_p4;
   TLorentzVector _topWj11_truth_p4;
   TLorentzVector _topWj21_truth_p4;
   TLorentzVector _topWj12_truth_p4;
   TLorentzVector _topWj22_truth_p4;
   TLorentzVector _Hb1_truth_p4;
   TLorentzVector _Hb2_truth_p4;
   TLorentzVector _l_truth_p4;
   TLorentzVector _l1_truth_p4;
   TLorentzVector _l2_truth_p4;
   TLorentzVector _nu_truth_p4;
   TLorentzVector _top_truth_p4;
   TLorentzVector _H_truth_p4;
   TLorentzVector _W_truth_p4;
   
   bool _is_top1_leptonic;
   bool _is_top2_leptonic;
   bool _is_lepton_tau;
   
   // reconstructed objects matched to truth
   TLorentzVector _topbLep_truthReco_p4;
   TLorentzVector _topbHad_truthReco_p4;
   TLorentzVector _topWl_truthReco_p4;
   TLorentzVector _topWj1_truthReco_p4;
   TLorentzVector _topWj2_truthReco_p4;
   
   double _chi2;
   double _chi2TTbar;
   
   bool _Hb1_match;
   bool _Hb2_match;
   bool _topb_match;

   bool _topbLep_match;
   bool _topbHad_match;
   
   bool _Hb1_match_all;
   bool _Hb2_match_all;
   bool _topb_match_all;

   bool _topbLep_match_all;
   bool _topbHad_match_all;
   bool _topWl_match_all;
   bool _topWj1_match_all;
   bool _topWj2_match_all;
   
   bool m_match;
   double m_weight;
   int m_id;   
   bool m_matchAll;

   bool m_matchTTbar;
   double m_weightTTbar;
   int m_idTTbar;   
   bool m_matchAllTTbar;
   
   double m_mTopHad;
   double m_mTopLep;
   
   TRandom3 *rnd;

   bool _standalone;
   std::string _home;
   
   TFile *_fout;

   TTree *_tree;
   TTree *_treeReco;

   TTree *_treeTTbar;
   TTree *_treeRecoTTbar;
   
   // histograms
   
   TH1F *h_matchAll;
   TH1F *h_topSol;
   TH1F *h_match;
   TH1F *h_H_m[3];
   TH1F *h_top_m[3];
   TH1F *h_W_m[3];
   
   TH1F *h_matchAllTTbar;
   TH1F *h_topSolTTbar;
   
   KINFIT::kfit *kf;
};

#endif
