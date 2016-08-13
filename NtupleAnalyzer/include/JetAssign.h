#ifndef JETASSIGN_H
#define JETASSIGN_H

#include "Analyzer.h"

#include "Helper.h"

class JetAssign
{
   
 public:

   JetAssign(std::string home,bool standalone,TFile *foutput);
   virtual ~JetAssign();
   
   void setElectron(std::vector<Electron> *v)                {_v_Electron = v;};
   void setMuon(std::vector<Muon> *v)                        {_v_Muon = v;};
   void setJet(std::vector<Jet> *v)                          {_v_Jet = v;};
   void setBJet(std::vector<Jet> *v)                         {_v_BJet = v;};
   void setEvent(std::vector<Event> *v)                      {_v_Event = v;};
   void setTruth(std::vector<Truth> *v)                      {_v_Truth = v;};
   void setLepton(std::vector<Lepton> *v)                    {_v_Lepton = v;};
	
   void init();
   bool run();
   bool truthMatch(TLorentzVector &topbRec,
		   TLorentzVector &Hb1Rec,
		   TLorentzVector &Hb2Rec);
   bool truthMatchTTbar(TLorentzVector &topbLepRec,
			TLorentzVector &topbHadRec);
   bool truthMatchAll();
   void truthMatchAllTTbar();
   bool topReco(TLorentzVector &topbRec);
   void close();
   
 protected:

   std::vector<Lepton>             *_v_Lepton;
   
   std::vector<Electron>           *_v_Electron;
   std::vector<Muon>               *_v_Muon;
   std::vector<Electron>           *_v_ElectronTight;
   std::vector<Muon>               *_v_MuonTight;
   
   std::vector<Event>              *_v_Event;
   std::vector<Jet>                *_v_Jet;
   std::vector<Jet>                *_v_BJet;
   std::vector<Jet>                *_v_JetTight;
   std::vector<Jet>                *_v_BJetTight;
   
   std::vector<Truth>              *_v_Truth;

   Helper *help;
   
 private:
   
   TLorentzVector _l_p4;
   TLorentzVector _nu_p4;
   
   TLorentzVector _top_p4;
   TLorentzVector _topb_p4;
   TLorentzVector _W_p4;
   TLorentzVector _H_p4;

   TLorentzVector _topbLep_p4;
   TLorentzVector _topbHad_p4;
   TLorentzVector _WHad_p4;
   TLorentzVector _topHad_p4;
   TLorentzVector _topbMisId_p4;
   TLorentzVector _topj_p4;
   
   TLorentzVector _topb_truth_p4;
   TLorentzVector _Hb1_truth_p4;
   TLorentzVector _Hb2_truth_p4;
   TLorentzVector _l_truth_p4;
   TLorentzVector _nu_truth_p4;
   TLorentzVector _top_truth_p4;
   TLorentzVector _H_truth_p4;
   TLorentzVector _W_truth_p4;
   TLorentzVector _topb1_truth_p4;
   TLorentzVector _topb2_truth_p4;
   TLorentzVector _topWj11_truth_p4;
   TLorentzVector _topWj21_truth_p4;
   TLorentzVector _topWj12_truth_p4;
   TLorentzVector _topWj22_truth_p4;
   TLorentzVector _l1_truth_p4;
   TLorentzVector _l2_truth_p4;
   
   bool _Hb1_match;
   bool _Hb2_match;
   bool _topb_match;

   bool _topbLep_match;
   bool _topbHad_match;
   
   bool _is_top1_leptonic;
   bool _is_top2_leptonic;
   bool _is_lepton_tau;
   
   TRandom3 *rnd;

   bool _standalone;
   std::string _home;
   
   TFile *_fout;
   
   TTree *_tree;
   TTree *_treeReco;

   TTree *_treeTTbar;
   TTree *_treeRecoTTbar;
   
   double _chi2;
   
   bool m_match;   
   bool m_matchAll;
   bool m_hasSol;
   double m_chi2;   
   int m_id;   
   double m_weight;

   bool m_matchTTbar;
   bool m_matchAllTTbar;
   bool m_hasSolTTbar;
   double m_chi2TTbar;   
   int m_idTTbar;   
   double m_weightTTbar;
   
   bool _topbLep_match_all;
   bool _topbHad_match_all;
   bool _topWl_match_all;
   bool _topWj1_match_all;
   bool _topWj2_match_all;

   // tH
   double m_l_pt;
   double m_l_eta;
   double m_l_phi;
   double m_l_E;
   
   double m_topb_pt;
   double m_topb_eta;
   double m_topb_phi;
   double m_topb_E;
   double m_topb_CSV;

   double m_Hb1_pt;
   double m_Hb1_eta;
   double m_Hb1_phi;
   double m_Hb1_E;
   double m_Hb1_CSV;

   double m_Hb2_pt;
   double m_Hb2_eta;
   double m_Hb2_phi;
   double m_Hb2_E;
   double m_Hb2_CSV;
   
   double m_W_m;
   double m_H_m;
   double m_H_eta;
   double m_top_m;
   double m_top_pt;
   double m_Hb1_Hb2_Dr;
   double m_tb_tW_Dr;
   double m_top_H_Dr;
   
   // ttbar
   double m_topWl_pt;
   double m_topWl_eta;
   double m_topWl_phi;
   double m_topWl_E;

   double m_topbLep_pt;
   double m_topbLep_eta;
   double m_topbLep_phi;
   double m_topbLep_E;
   double m_topbLep_CSV;

   double m_topbHad_pt;
   double m_topbHad_eta;
   double m_topbHad_phi;
   double m_topbHad_E;
   double m_topbHad_CSV;
   
   double m_topWj1_pt;
   double m_topWj1_eta;
   double m_topWj1_phi;
   double m_topWj1_E;
   double m_topWj1_CSV;   

   double m_topWj2_pt;
   double m_topWj2_eta;
   double m_topWj2_phi;
   double m_topWj2_E;
   double m_topWj2_CSV;   

   double m_WLep_m;
   double m_WHad_m;
   double m_topLep_m;
   double m_topHad_m;
   double m_topLep_eta;
   double m_topHad_eta;
   double m_tbLep_tWLep_Dr;
   double m_tbHad_tWHad_Dr;
   double m_tWj1_tWj2_Dr;
};

#endif
