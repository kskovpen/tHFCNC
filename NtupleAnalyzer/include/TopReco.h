#ifndef TOPRECO_H
#define TOPRECO_H

#include "Analyzer.h"

#include "Helper.h"

class TopReco
{
   
 public:

   TopReco(std::string home,bool standalone,TFile *foutput);
   virtual ~TopReco();
   
   void setElectron(std::vector<Electron> *v)                {_v_Electron = v;};
   void setMuon(std::vector<Muon> *v)                        {_v_Muon = v;};
   void setJet(std::vector<Jet> *v)                          {_v_Jet = v;};
   void setBJet(std::vector<Jet> *v)                         {_v_BJet = v;};
   void setEvent(std::vector<Event> *v)                      {_v_Event = v;};
   void setTruth(std::vector<Truth> *v)                      {_v_Truth = v;};
   void setLepton(std::vector<Lepton> *v)                    {_v_Lepton = v;};
	
   void init();
   void run();
   void fill(int ialg,float w,bool isMatch);
   void truthMatch();
   void truthMatchAlg();
   void close();

   // methods for jet assignment
   void Mbb();
   void MT();
   void MbbMT();
   bool Top();
   
   int _useTruthMET;

   // results of reconstruction
   
   TLorentzVector topb_Mbb_p4()   {return _topb_Mbb_p4;};
   TLorentzVector Hb1_Mbb_p4()    {return _Hb1_Mbb_p4;};
   TLorentzVector Hb2_Mbb_p4()    {return _Hb2_Mbb_p4;};
   TLorentzVector l_Mbb_p4()      {return _l_Mbb_p4;};
   TLorentzVector nu_Mbb_p4()     {return _nu_Mbb_p4;};
   TLorentzVector top_Mbb_p4()    {return _top_Mbb_p4;};
   TLorentzVector H_Mbb_p4()      {return _H_Mbb_p4;};
   TLorentzVector W_Mbb_p4()      {return _W_Mbb_p4;};

   TLorentzVector topb_MT_p4()   {return _topb_MT_p4;};
   TLorentzVector Hb1_MT_p4()    {return _Hb1_MT_p4;};
   TLorentzVector Hb2_MT_p4()    {return _Hb2_MT_p4;};
   TLorentzVector l_MT_p4()      {return _l_MT_p4;};
   TLorentzVector nu_MT_p4()     {return _nu_MT_p4;};
   TLorentzVector top_MT_p4()    {return _top_MT_p4;};
   TLorentzVector H_MT_p4()      {return _H_MT_p4;};
   TLorentzVector W_MT_p4()      {return _W_MT_p4;};

   TLorentzVector topb_MbbMT_p4()   {return _topb_MbbMT_p4;};
   TLorentzVector Hb1_MbbMT_p4()    {return _Hb1_MbbMT_p4;};
   TLorentzVector Hb2_MbbMT_p4()    {return _Hb2_MbbMT_p4;};
   TLorentzVector l_MbbMT_p4()      {return _l_MbbMT_p4;};
   TLorentzVector nu_MbbMT_p4()     {return _nu_MbbMT_p4;};
   TLorentzVector top_MbbMT_p4()    {return _top_MbbMT_p4;};
   TLorentzVector H_MbbMT_p4()      {return _H_MbbMT_p4;};
   TLorentzVector W_MbbMT_p4()      {return _W_MbbMT_p4;};

   TLorentzVector topb_Top_p4()   {return _topb_Top_p4;};
   TLorentzVector Hb1_Top_p4()    {return _Hb1_Top_p4;};
   TLorentzVector Hb2_Top_p4()    {return _Hb2_Top_p4;};
   TLorentzVector l_Top_p4()      {return _l_Top_p4;};
   TLorentzVector nu_Top_p4()     {return _nu_Top_p4;};
   TLorentzVector top_Top_p4()    {return _top_Top_p4;};
   TLorentzVector H_Top_p4()      {return _H_Top_p4;};
   TLorentzVector W_Top_p4()      {return _W_Top_p4;};
   
   double chi2()     {return _chi2;};
   
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
   
   TLorentzVector _topb_p4;
   TLorentzVector _Hb1_p4;
   TLorentzVector _Hb2_p4;
   TLorentzVector _l_p4;
   TLorentzVector _nu_p4;
   TLorentzVector _top_p4;
   TLorentzVector _H_p4;
   TLorentzVector _W_p4;

   TLorentzVector _topb_Mbb_p4;
   TLorentzVector _Hb1_Mbb_p4;
   TLorentzVector _Hb2_Mbb_p4;
   TLorentzVector _l_Mbb_p4;
   TLorentzVector _nu_Mbb_p4;
   TLorentzVector _top_Mbb_p4;
   TLorentzVector _H_Mbb_p4;
   TLorentzVector _W_Mbb_p4;

   TLorentzVector _topb_MT_p4;
   TLorentzVector _Hb1_MT_p4;
   TLorentzVector _Hb2_MT_p4;
   TLorentzVector _l_MT_p4;
   TLorentzVector _nu_MT_p4;
   TLorentzVector _top_MT_p4;
   TLorentzVector _H_MT_p4;
   TLorentzVector _W_MT_p4;

   TLorentzVector _topb_MbbMT_p4;
   TLorentzVector _Hb1_MbbMT_p4;
   TLorentzVector _Hb2_MbbMT_p4;
   TLorentzVector _l_MbbMT_p4;
   TLorentzVector _nu_MbbMT_p4;
   TLorentzVector _top_MbbMT_p4;
   TLorentzVector _H_MbbMT_p4;
   TLorentzVector _W_MbbMT_p4;

   TLorentzVector _topb_Top_p4;
   TLorentzVector _Hb1_Top_p4;
   TLorentzVector _Hb2_Top_p4;
   TLorentzVector _l_Top_p4;
   TLorentzVector _nu_Top_p4;
   TLorentzVector _top_Top_p4;
   TLorentzVector _H_Top_p4;
   TLorentzVector _W_Top_p4;
   
   TLorentzVector _topb_truth_p4;
   TLorentzVector _Hb1_truth_p4;
   TLorentzVector _Hb2_truth_p4;
   TLorentzVector _l_truth_p4;
   TLorentzVector _nu_truth_p4;
   TLorentzVector _top_truth_p4;
   TLorentzVector _H_truth_p4;
   TLorentzVector _W_truth_p4;

   TLorentzVector _topb_IS_truth_p4;
   TLorentzVector _Hb1_IS_truth_p4;
   TLorentzVector _Hb2_IS_truth_p4;
   
   double _chi2;
   
   bool _Hb1_match;
   bool _Hb2_match;
   bool _topb_match;

   bool _Hb1_match_all;
   bool _Hb2_match_all;
   bool _topb_match_all;
   
   TRandom3 *rnd;

   bool _standalone;
   std::string _home;
   
   TFile *_fout;
   
   // histograms
   
   TH1F *h_matchAll;
   TH1F *h_topSol;
   TH1F *h_match[4];
   TH1F *h_H_m[4][3];
   TH1F *h_top_m[4][3];
   TH1F *h_W_m[4][3];
};

#endif
