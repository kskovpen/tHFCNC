#include "TROOT.h"
#include "TH1F.h"
#include "TFile.h"

#include <iostream>
#include <fstream>

//void adjustHist(TH1F *h,int &iBins,double *xBins);
void checkEmptyBins(TH1F *h);

bool mergeZjetsWjetStop = 1;
bool mergeAll = 0;

int main()
{   
   const int nc = 6;
   std::string cat[nc] = {"b2j3","b2j4","b3j3","b3j4","b4j4","ALL"};
   const int nd = 2;
   std::string dist[nd] = {"MVAHutMAX","MVAHctMAX"};
   std::string coup[nd] = {"hut","hct"};
 
   TFile *f = TFile::Open("histTEST.root");
   
   for(int ic=0;ic<nc;ic++)
     {	
	for(int id=0;id<nd;id++)
	  {	  
	     // data

	     std::string hname_data = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_DATA_clone";
	     TH1F *hget_data = (TH1F*)f->Get(hname_data.c_str());
   
	     // signal
   
	     std::string hname_sig_stop = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop = (TH1F*)f->Get(hname_sig_stop.c_str());
   
	     std::string hname_sig_ttbar = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar = (TH1F*)f->Get(hname_sig_ttbar.c_str());

	     std::string hname_sig_stop_SfIterativeFitHfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats1_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitHfstats1_up = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitHfstats1_up.c_str());
	     std::string hname_sig_stop_SfIterativeFitHfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats1_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitHfstats1_down = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitHfstats1_down.c_str());
	     
	     std::string hname_sig_stop_SfIterativeFitHfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats2_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitHfstats2_up = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitHfstats2_up.c_str());
	     std::string hname_sig_stop_SfIterativeFitHfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats2_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitHfstats2_down = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitHfstats2_down.c_str());

	     std::string hname_sig_stop_SfIterativeFitLfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats1_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitLfstats1_up = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitLfstats1_up.c_str());
	     std::string hname_sig_stop_SfIterativeFitLfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats1_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitLfstats1_down = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitLfstats1_down.c_str());

	     std::string hname_sig_stop_SfIterativeFitLfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats2_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitLfstats2_up = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitLfstats2_up.c_str());
	     std::string hname_sig_stop_SfIterativeFitLfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats2_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitLfstats2_down = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitLfstats2_down.c_str());
   
	     std::string hname_sig_stop_SfIterativeFitJes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitJes_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitJes_up = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitJes_up.c_str());
	     std::string hname_sig_stop_SfIterativeFitJes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitJes_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitJes_down = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitJes_down.c_str());

	     std::string hname_sig_stop_SfIterativeFitLf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLf_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitLf_up = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitLf_up.c_str());
	     std::string hname_sig_stop_SfIterativeFitLf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLf_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitLf_down = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitLf_down.c_str());
	     
	     std::string hname_sig_stop_SfIterativeFitHf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHf_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitHf_up = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitHf_up.c_str());
	     std::string hname_sig_stop_SfIterativeFitHf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHf_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitHf_down = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitHf_down.c_str());

	     std::string hname_sig_stop_SfIterativeFitCferr1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr1_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitCferr1_up = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitCferr1_up.c_str());
	     std::string hname_sig_stop_SfIterativeFitCferr1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr1_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitCferr1_down = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitCferr1_down.c_str());
	     
	     std::string hname_sig_stop_SfIterativeFitCferr2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr2_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitCferr2_up = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitCferr2_up.c_str());
	     std::string hname_sig_stop_SfIterativeFitCferr2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr2_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_SfIterativeFitCferr2_down = (TH1F*)f->Get(hname_sig_stop_SfIterativeFitCferr2_down.c_str());

	     std::string hname_sig_stop_Jes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jes_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_Jes_up = (TH1F*)f->Get(hname_sig_stop_Jes_up.c_str());
	     std::string hname_sig_stop_Jes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jes_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_Jes_down = (TH1F*)f->Get(hname_sig_stop_Jes_down.c_str());

	     std::string hname_sig_stop_Jer_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jer_Up_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_Jer_up = (TH1F*)f->Get(hname_sig_stop_Jer_up.c_str());
	     std::string hname_sig_stop_Jer_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jer_Down_sig_"+coup[id]+"_stop_clone";
	     TH1F *hget_sig_stop_Jer_down = (TH1F*)f->Get(hname_sig_stop_Jer_down.c_str());
	     
	     std::string hname_sig_ttbar_SfIterativeFitHfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats1_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitHfstats1_up = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitHfstats1_up.c_str());
	     std::string hname_sig_ttbar_SfIterativeFitHfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats1_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitHfstats1_down = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitHfstats1_down.c_str());
	     
	     std::string hname_sig_ttbar_SfIterativeFitHfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats2_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitHfstats2_up = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitHfstats2_up.c_str());
	     std::string hname_sig_ttbar_SfIterativeFitHfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats2_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitHfstats2_down = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitHfstats2_down.c_str());
	     
	     std::string hname_sig_ttbar_SfIterativeFitLfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats1_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitLfstats1_up = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitLfstats1_up.c_str());
	     std::string hname_sig_ttbar_SfIterativeFitLfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats1_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitLfstats1_down = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitLfstats1_down.c_str());
	     
	     std::string hname_sig_ttbar_SfIterativeFitLfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats2_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitLfstats2_up = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitLfstats2_up.c_str());
	     std::string hname_sig_ttbar_SfIterativeFitLfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats2_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitLfstats2_down = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitLfstats2_down.c_str());
   
	     std::string hname_sig_ttbar_SfIterativeFitJes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitJes_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitJes_up = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitJes_up.c_str());
	     std::string hname_sig_ttbar_SfIterativeFitJes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitJes_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitJes_down = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitJes_down.c_str());
	     
	     std::string hname_sig_ttbar_SfIterativeFitLf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLf_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitLf_up = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitLf_up.c_str());
	     std::string hname_sig_ttbar_SfIterativeFitLf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLf_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitLf_down = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitLf_down.c_str());
	     
	     std::string hname_sig_ttbar_SfIterativeFitHf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHf_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitHf_up = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitHf_up.c_str());
	     std::string hname_sig_ttbar_SfIterativeFitHf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHf_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitHf_down = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitHf_down.c_str());
	     
	     std::string hname_sig_ttbar_SfIterativeFitCferr1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr1_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitCferr1_up = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitCferr1_up.c_str());
	     std::string hname_sig_ttbar_SfIterativeFitCferr1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr1_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitCferr1_down = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitCferr1_down.c_str());
	     
	     std::string hname_sig_ttbar_SfIterativeFitCferr2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr2_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitCferr2_up = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitCferr2_up.c_str());
	     std::string hname_sig_ttbar_SfIterativeFitCferr2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr2_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_SfIterativeFitCferr2_down = (TH1F*)f->Get(hname_sig_ttbar_SfIterativeFitCferr2_down.c_str());

	     std::string hname_sig_ttbar_Jes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jes_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_Jes_up = (TH1F*)f->Get(hname_sig_ttbar_Jes_up.c_str());
	     std::string hname_sig_ttbar_Jes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jes_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_Jes_down = (TH1F*)f->Get(hname_sig_ttbar_Jes_down.c_str());

	     std::string hname_sig_ttbar_Jer_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jer_Up_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_Jer_up = (TH1F*)f->Get(hname_sig_ttbar_Jer_up.c_str());
	     std::string hname_sig_ttbar_Jer_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jer_Down_sig_"+coup[id]+"_ttbar_clone";
	     TH1F *hget_sig_ttbar_Jer_down = (TH1F*)f->Get(hname_sig_ttbar_Jer_down.c_str());
	     
	     // ttbb

	     std::string hname_ttbb = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_ttbb_clone";
	     TH1F *hget_ttbb = (TH1F*)f->Get(hname_ttbb.c_str());

	     std::string hname_ttbb_SfIterativeFitHfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitHfstats1_Up_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitHfstats1_up = (TH1F*)f->Get(hname_ttbb_SfIterativeFitHfstats1_up.c_str());
	     std::string hname_ttbb_SfIterativeFitHfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitHfstats1_Down_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitHfstats1_down = (TH1F*)f->Get(hname_ttbb_SfIterativeFitHfstats1_down.c_str());
	     
	     std::string hname_ttbb_SfIterativeFitHfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitHfstats2_Up_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitHfstats2_up = (TH1F*)f->Get(hname_ttbb_SfIterativeFitHfstats2_up.c_str());
	     std::string hname_ttbb_SfIterativeFitHfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitHfstats2_Down_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitHfstats2_down = (TH1F*)f->Get(hname_ttbb_SfIterativeFitHfstats2_down.c_str());
	     
	     std::string hname_ttbb_SfIterativeFitLfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitLfstats1_Up_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitLfstats1_up = (TH1F*)f->Get(hname_ttbb_SfIterativeFitLfstats1_up.c_str());
	     std::string hname_ttbb_SfIterativeFitLfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitLfstats1_Down_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitLfstats1_down = (TH1F*)f->Get(hname_ttbb_SfIterativeFitLfstats1_down.c_str());
	     
	     std::string hname_ttbb_SfIterativeFitLfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitLfstats2_Up_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitLfstats2_up = (TH1F*)f->Get(hname_ttbb_SfIterativeFitLfstats2_up.c_str());
	     std::string hname_ttbb_SfIterativeFitLfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitLfstats2_Down_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitLfstats2_down = (TH1F*)f->Get(hname_ttbb_SfIterativeFitLfstats2_down.c_str());
	     
	     std::string hname_ttbb_SfIterativeFitJes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitJes_Up_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitJes_up = (TH1F*)f->Get(hname_ttbb_SfIterativeFitJes_up.c_str());
	     std::string hname_ttbb_SfIterativeFitJes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitJes_Down_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitJes_down = (TH1F*)f->Get(hname_ttbb_SfIterativeFitJes_down.c_str());
	     
	     std::string hname_ttbb_SfIterativeFitLf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitLf_Up_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitLf_up = (TH1F*)f->Get(hname_ttbb_SfIterativeFitLf_up.c_str());
	     std::string hname_ttbb_SfIterativeFitLf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitLf_Down_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitLf_down = (TH1F*)f->Get(hname_ttbb_SfIterativeFitLf_down.c_str());
	     
	     std::string hname_ttbb_SfIterativeFitHf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitHf_Up_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitHf_up = (TH1F*)f->Get(hname_ttbb_SfIterativeFitHf_up.c_str());
	     std::string hname_ttbb_SfIterativeFitHf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitHf_Down_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitHf_down = (TH1F*)f->Get(hname_ttbb_SfIterativeFitHf_down.c_str());
	     
	     std::string hname_ttbb_SfIterativeFitCferr1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitCferr1_Up_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitCferr1_up = (TH1F*)f->Get(hname_ttbb_SfIterativeFitCferr1_up.c_str());
	     std::string hname_ttbb_SfIterativeFitCferr1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitCferr1_Down_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitCferr1_down = (TH1F*)f->Get(hname_ttbb_SfIterativeFitCferr1_down.c_str());
	     
	     std::string hname_ttbb_SfIterativeFitCferr2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitCferr2_Up_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitCferr2_up = (TH1F*)f->Get(hname_ttbb_SfIterativeFitCferr2_up.c_str());
	     std::string hname_ttbb_SfIterativeFitCferr2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_SfIterativeFitCferr2_Down_ttbb_clone";
	     TH1F *hget_ttbb_SfIterativeFitCferr2_down = (TH1F*)f->Get(hname_ttbb_SfIterativeFitCferr2_down.c_str());

	     std::string hname_ttbb_Jes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_Jes_Up_ttbb_clone";
	     TH1F *hget_ttbb_Jes_up = (TH1F*)f->Get(hname_ttbb_Jes_up.c_str());
	     std::string hname_ttbb_Jes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_Jes_Down_ttbb_clone";
	     TH1F *hget_ttbb_Jes_down = (TH1F*)f->Get(hname_ttbb_Jes_down.c_str());

	     std::string hname_ttbb_Jer_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_Jer_Up_ttbb_clone";
	     TH1F *hget_ttbb_Jer_up = (TH1F*)f->Get(hname_ttbb_Jer_up.c_str());
	     std::string hname_ttbb_Jer_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttbb_Jer_Down_ttbb_clone";
	     TH1F *hget_ttbb_Jer_down = (TH1F*)f->Get(hname_ttbb_Jer_down.c_str());
	     
	     // ttcc
   	     
	     std::string hname_ttcc = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_ttcc_clone";
	     TH1F *hget_ttcc = (TH1F*)f->Get(hname_ttcc.c_str());
	     
	     std::string hname_ttcc_SfIterativeFitHfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitHfstats1_Up_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitHfstats1_up = (TH1F*)f->Get(hname_ttcc_SfIterativeFitHfstats1_up.c_str());
	     std::string hname_ttcc_SfIterativeFitHfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitHfstats1_Down_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitHfstats1_down = (TH1F*)f->Get(hname_ttcc_SfIterativeFitHfstats1_down.c_str());
	     
	     std::string hname_ttcc_SfIterativeFitHfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitHfstats2_Up_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitHfstats2_up = (TH1F*)f->Get(hname_ttcc_SfIterativeFitHfstats2_up.c_str());
	     std::string hname_ttcc_SfIterativeFitHfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitHfstats2_Down_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitHfstats2_down = (TH1F*)f->Get(hname_ttcc_SfIterativeFitHfstats2_down.c_str());
	     
	     std::string hname_ttcc_SfIterativeFitLfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitLfstats1_Up_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitLfstats1_up = (TH1F*)f->Get(hname_ttcc_SfIterativeFitLfstats1_up.c_str());
	     std::string hname_ttcc_SfIterativeFitLfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitLfstats1_Down_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitLfstats1_down = (TH1F*)f->Get(hname_ttcc_SfIterativeFitLfstats1_down.c_str());
	     
	     std::string hname_ttcc_SfIterativeFitLfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitLfstats2_Up_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitLfstats2_up = (TH1F*)f->Get(hname_ttcc_SfIterativeFitLfstats2_up.c_str());
	     std::string hname_ttcc_SfIterativeFitLfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitLfstats2_Down_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitLfstats2_down = (TH1F*)f->Get(hname_ttcc_SfIterativeFitLfstats2_down.c_str());
	     
	     std::string hname_ttcc_SfIterativeFitJes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitJes_Up_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitJes_up = (TH1F*)f->Get(hname_ttcc_SfIterativeFitJes_up.c_str());
	     std::string hname_ttcc_SfIterativeFitJes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitJes_Down_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitJes_down = (TH1F*)f->Get(hname_ttcc_SfIterativeFitJes_down.c_str());
	     
	     std::string hname_ttcc_SfIterativeFitLf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitLf_Up_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitLf_up = (TH1F*)f->Get(hname_ttcc_SfIterativeFitLf_up.c_str());
	     std::string hname_ttcc_SfIterativeFitLf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitLf_Down_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitLf_down = (TH1F*)f->Get(hname_ttcc_SfIterativeFitLf_down.c_str());
	     
	     std::string hname_ttcc_SfIterativeFitHf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitHf_Up_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitHf_up = (TH1F*)f->Get(hname_ttcc_SfIterativeFitHf_up.c_str());
	     std::string hname_ttcc_SfIterativeFitHf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitHf_Down_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitHf_down = (TH1F*)f->Get(hname_ttcc_SfIterativeFitHf_down.c_str());
	     
	     std::string hname_ttcc_SfIterativeFitCferr1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitCferr1_Up_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitCferr1_up = (TH1F*)f->Get(hname_ttcc_SfIterativeFitCferr1_up.c_str());
	     std::string hname_ttcc_SfIterativeFitCferr1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitCferr1_Down_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitCferr1_down = (TH1F*)f->Get(hname_ttcc_SfIterativeFitCferr1_down.c_str());
	     
	     std::string hname_ttcc_SfIterativeFitCferr2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitCferr2_Up_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitCferr2_up = (TH1F*)f->Get(hname_ttcc_SfIterativeFitCferr2_up.c_str());
	     std::string hname_ttcc_SfIterativeFitCferr2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_SfIterativeFitCferr2_Down_ttcc_clone";
	     TH1F *hget_ttcc_SfIterativeFitCferr2_down = (TH1F*)f->Get(hname_ttcc_SfIterativeFitCferr2_down.c_str());

	     std::string hname_ttcc_Jes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_Jes_Up_ttcc_clone";
	     TH1F *hget_ttcc_Jes_up = (TH1F*)f->Get(hname_ttcc_Jes_up.c_str());
	     std::string hname_ttcc_Jes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_Jes_Down_ttcc_clone";
	     TH1F *hget_ttcc_Jes_down = (TH1F*)f->Get(hname_ttcc_Jes_down.c_str());

	     std::string hname_ttcc_Jer_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_Jer_Up_ttcc_clone";
	     TH1F *hget_ttcc_Jer_up = (TH1F*)f->Get(hname_ttcc_Jer_up.c_str());
	     std::string hname_ttcc_Jer_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttcc_Jer_Down_ttcc_clone";
	     TH1F *hget_ttcc_Jer_down = (TH1F*)f->Get(hname_ttcc_Jer_down.c_str());
	     
	     // ttlf
   
	     std::string hname_ttlf = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_ttlf_clone";
	     TH1F *hget_ttlf = (TH1F*)f->Get(hname_ttlf.c_str());
	     
	     std::string hname_ttlf_SfIterativeFitHfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitHfstats1_Up_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitHfstats1_up = (TH1F*)f->Get(hname_ttlf_SfIterativeFitHfstats1_up.c_str());
	     std::string hname_ttlf_SfIterativeFitHfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitHfstats1_Down_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitHfstats1_down = (TH1F*)f->Get(hname_ttlf_SfIterativeFitHfstats1_down.c_str());
	     
	     std::string hname_ttlf_SfIterativeFitHfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitHfstats2_Up_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitHfstats2_up = (TH1F*)f->Get(hname_ttlf_SfIterativeFitHfstats2_up.c_str());
	     std::string hname_ttlf_SfIterativeFitHfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitHfstats2_Down_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitHfstats2_down = (TH1F*)f->Get(hname_ttlf_SfIterativeFitHfstats2_down.c_str());
	     
	     std::string hname_ttlf_SfIterativeFitLfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitLfstats1_Up_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitLfstats1_up = (TH1F*)f->Get(hname_ttlf_SfIterativeFitLfstats1_up.c_str());
	     std::string hname_ttlf_SfIterativeFitLfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitLfstats1_Down_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitLfstats1_down = (TH1F*)f->Get(hname_ttlf_SfIterativeFitLfstats1_down.c_str());
	     
	     std::string hname_ttlf_SfIterativeFitLfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitLfstats2_Up_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitLfstats2_up = (TH1F*)f->Get(hname_ttlf_SfIterativeFitLfstats2_up.c_str());
	     std::string hname_ttlf_SfIterativeFitLfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitLfstats2_Down_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitLfstats2_down = (TH1F*)f->Get(hname_ttlf_SfIterativeFitLfstats2_down.c_str());
	     
	     std::string hname_ttlf_SfIterativeFitJes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitJes_Up_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitJes_up = (TH1F*)f->Get(hname_ttlf_SfIterativeFitJes_up.c_str());
	     std::string hname_ttlf_SfIterativeFitJes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitJes_Down_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitJes_down = (TH1F*)f->Get(hname_ttlf_SfIterativeFitJes_down.c_str());
	     
	     std::string hname_ttlf_SfIterativeFitLf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitLf_Up_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitLf_up = (TH1F*)f->Get(hname_ttlf_SfIterativeFitLf_up.c_str());
	     std::string hname_ttlf_SfIterativeFitLf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitLf_Down_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitLf_down = (TH1F*)f->Get(hname_ttlf_SfIterativeFitLf_down.c_str());
	     
	     std::string hname_ttlf_SfIterativeFitHf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitHf_Up_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitHf_up = (TH1F*)f->Get(hname_ttlf_SfIterativeFitHf_up.c_str());
	     std::string hname_ttlf_SfIterativeFitHf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitHf_Down_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitHf_down = (TH1F*)f->Get(hname_ttlf_SfIterativeFitHf_down.c_str());
	     
	     std::string hname_ttlf_SfIterativeFitCferr1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitCferr1_Up_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitCferr1_up = (TH1F*)f->Get(hname_ttlf_SfIterativeFitCferr1_up.c_str());
	     std::string hname_ttlf_SfIterativeFitCferr1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitCferr1_Down_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitCferr1_down = (TH1F*)f->Get(hname_ttlf_SfIterativeFitCferr1_down.c_str());

	     std::string hname_ttlf_SfIterativeFitCferr2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitCferr2_Up_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitCferr2_up = (TH1F*)f->Get(hname_ttlf_SfIterativeFitCferr2_up.c_str());
	     std::string hname_ttlf_SfIterativeFitCferr2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_SfIterativeFitCferr2_Down_ttlf_clone";
	     TH1F *hget_ttlf_SfIterativeFitCferr2_down = (TH1F*)f->Get(hname_ttlf_SfIterativeFitCferr2_down.c_str());

	     std::string hname_ttlf_Jes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_Jes_Up_ttlf_clone";
	     TH1F *hget_ttlf_Jes_up = (TH1F*)f->Get(hname_ttlf_Jes_up.c_str());
	     std::string hname_ttlf_Jes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_Jes_Down_ttlf_clone";
	     TH1F *hget_ttlf_Jes_down = (TH1F*)f->Get(hname_ttlf_Jes_down.c_str());

	     std::string hname_ttlf_Jer_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_Jer_Up_ttlf_clone";
	     TH1F *hget_ttlf_Jer_up = (TH1F*)f->Get(hname_ttlf_Jer_up.c_str());
	     std::string hname_ttlf_Jer_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ttlf_Jer_Down_ttlf_clone";
	     TH1F *hget_ttlf_Jer_down = (TH1F*)f->Get(hname_ttlf_Jer_down.c_str());
	     
	     // stop
   	     
	     std::string hname_stop = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_stop_clone";
	     TH1F *hget_stop = (TH1F*)f->Get(hname_stop.c_str());
	     
	     std::string hname_stop_SfIterativeFitHfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats1_Up_stop_clone";
	     TH1F *hget_stop_SfIterativeFitHfstats1_up = (TH1F*)f->Get(hname_stop_SfIterativeFitHfstats1_up.c_str());
	     std::string hname_stop_SfIterativeFitHfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats1_Down_stop_clone";
	     TH1F *hget_stop_SfIterativeFitHfstats1_down = (TH1F*)f->Get(hname_stop_SfIterativeFitHfstats1_down.c_str());
	     
	     std::string hname_stop_SfIterativeFitHfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats2_Up_stop_clone";
	     TH1F *hget_stop_SfIterativeFitHfstats2_up = (TH1F*)f->Get(hname_stop_SfIterativeFitHfstats2_up.c_str());
	     std::string hname_stop_SfIterativeFitHfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats2_Down_stop_clone";
	     TH1F *hget_stop_SfIterativeFitHfstats2_down = (TH1F*)f->Get(hname_stop_SfIterativeFitHfstats2_down.c_str());
	     
	     std::string hname_stop_SfIterativeFitLfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats1_Up_stop_clone";
	     TH1F *hget_stop_SfIterativeFitLfstats1_up = (TH1F*)f->Get(hname_stop_SfIterativeFitLfstats1_up.c_str());
	     std::string hname_stop_SfIterativeFitLfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats1_Down_stop_clone";
	     TH1F *hget_stop_SfIterativeFitLfstats1_down = (TH1F*)f->Get(hname_stop_SfIterativeFitLfstats1_down.c_str());
	     
	     std::string hname_stop_SfIterativeFitLfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats2_Up_stop_clone";
	     TH1F *hget_stop_SfIterativeFitLfstats2_up = (TH1F*)f->Get(hname_stop_SfIterativeFitLfstats2_up.c_str());
	     std::string hname_stop_SfIterativeFitLfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats2_Down_stop_clone";
	     TH1F *hget_stop_SfIterativeFitLfstats2_down = (TH1F*)f->Get(hname_stop_SfIterativeFitLfstats2_down.c_str());
	     
	     std::string hname_stop_SfIterativeFitJes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitJes_Up_stop_clone";
	     TH1F *hget_stop_SfIterativeFitJes_up = (TH1F*)f->Get(hname_stop_SfIterativeFitJes_up.c_str());
	     std::string hname_stop_SfIterativeFitJes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitJes_Down_stop_clone";
	     TH1F *hget_stop_SfIterativeFitJes_down = (TH1F*)f->Get(hname_stop_SfIterativeFitJes_down.c_str());
	     
	     std::string hname_stop_SfIterativeFitLf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLf_Up_stop_clone";
	     TH1F *hget_stop_SfIterativeFitLf_up = (TH1F*)f->Get(hname_stop_SfIterativeFitLf_up.c_str());
	     std::string hname_stop_SfIterativeFitLf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLf_Down_stop_clone";
	     TH1F *hget_stop_SfIterativeFitLf_down = (TH1F*)f->Get(hname_stop_SfIterativeFitLf_down.c_str());
	     
	     std::string hname_stop_SfIterativeFitHf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHf_Up_stop_clone";
	     TH1F *hget_stop_SfIterativeFitHf_up = (TH1F*)f->Get(hname_stop_SfIterativeFitHf_up.c_str());
	     std::string hname_stop_SfIterativeFitHf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHf_Down_stop_clone";
	     TH1F *hget_stop_SfIterativeFitHf_down = (TH1F*)f->Get(hname_stop_SfIterativeFitHf_down.c_str());
	     
	     std::string hname_stop_SfIterativeFitCferr1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr1_Up_stop_clone";
	     TH1F *hget_stop_SfIterativeFitCferr1_up = (TH1F*)f->Get(hname_stop_SfIterativeFitCferr1_up.c_str());
	     std::string hname_stop_SfIterativeFitCferr1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr1_Down_stop_clone";
	     TH1F *hget_stop_SfIterativeFitCferr1_down = (TH1F*)f->Get(hname_stop_SfIterativeFitCferr1_down.c_str());
	     
	     std::string hname_stop_SfIterativeFitCferr2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr2_Up_stop_clone";
	     TH1F *hget_stop_SfIterativeFitCferr2_up = (TH1F*)f->Get(hname_stop_SfIterativeFitCferr2_up.c_str());
	     std::string hname_stop_SfIterativeFitCferr2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr2_Down_stop_clone";
	     TH1F *hget_stop_SfIterativeFitCferr2_down = (TH1F*)f->Get(hname_stop_SfIterativeFitCferr2_down.c_str());

	     std::string hname_stop_Jes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jes_Up_stop_clone";
	     TH1F *hget_stop_Jes_up = (TH1F*)f->Get(hname_stop_Jes_up.c_str());
	     std::string hname_stop_Jes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jes_Down_stop_clone";
	     TH1F *hget_stop_Jes_down = (TH1F*)f->Get(hname_stop_Jes_down.c_str());

	     std::string hname_stop_Jer_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jer_Up_stop_clone";
	     TH1F *hget_stop_Jer_up = (TH1F*)f->Get(hname_stop_Jer_up.c_str());
	     std::string hname_stop_Jer_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jer_Down_stop_clone";
	     TH1F *hget_stop_Jer_down = (TH1F*)f->Get(hname_stop_Jer_down.c_str());
	     
	     // zjets
   
	     std::string hname_zjets = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_zjets_clone";
	     TH1F *hget_zjets = (TH1F*)f->Get(hname_zjets.c_str());
	     
	     std::string hname_zjets_SfIterativeFitHfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats1_Up_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitHfstats1_up = (TH1F*)f->Get(hname_zjets_SfIterativeFitHfstats1_up.c_str());
	     std::string hname_zjets_SfIterativeFitHfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats1_Down_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitHfstats1_down = (TH1F*)f->Get(hname_zjets_SfIterativeFitHfstats1_down.c_str());
	     
	     std::string hname_zjets_SfIterativeFitHfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats2_Up_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitHfstats2_up = (TH1F*)f->Get(hname_zjets_SfIterativeFitHfstats2_up.c_str());
	     std::string hname_zjets_SfIterativeFitHfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats2_Down_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitHfstats2_down = (TH1F*)f->Get(hname_zjets_SfIterativeFitHfstats2_down.c_str());
	     
	     std::string hname_zjets_SfIterativeFitLfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats1_Up_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitLfstats1_up = (TH1F*)f->Get(hname_zjets_SfIterativeFitLfstats1_up.c_str());
	     std::string hname_zjets_SfIterativeFitLfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats1_Down_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitLfstats1_down = (TH1F*)f->Get(hname_zjets_SfIterativeFitLfstats1_down.c_str());

	     std::string hname_zjets_SfIterativeFitLfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats2_Up_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitLfstats2_up = (TH1F*)f->Get(hname_zjets_SfIterativeFitLfstats2_up.c_str());
	     std::string hname_zjets_SfIterativeFitLfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats2_Down_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitLfstats2_down = (TH1F*)f->Get(hname_zjets_SfIterativeFitLfstats2_down.c_str());
	     
	     std::string hname_zjets_SfIterativeFitJes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitJes_Up_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitJes_up = (TH1F*)f->Get(hname_zjets_SfIterativeFitJes_up.c_str());
	     std::string hname_zjets_SfIterativeFitJes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitJes_Down_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitJes_down = (TH1F*)f->Get(hname_zjets_SfIterativeFitJes_down.c_str());
	     
	     std::string hname_zjets_SfIterativeFitLf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLf_Up_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitLf_up = (TH1F*)f->Get(hname_zjets_SfIterativeFitLf_up.c_str());
	     std::string hname_zjets_SfIterativeFitLf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLf_Down_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitLf_down = (TH1F*)f->Get(hname_zjets_SfIterativeFitLf_down.c_str());
	     
	     std::string hname_zjets_SfIterativeFitHf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHf_Up_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitHf_up = (TH1F*)f->Get(hname_zjets_SfIterativeFitHf_up.c_str());
	     std::string hname_zjets_SfIterativeFitHf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHf_Down_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitHf_down = (TH1F*)f->Get(hname_zjets_SfIterativeFitHf_down.c_str());

	     std::string hname_zjets_SfIterativeFitCferr1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr1_Up_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitCferr1_up = (TH1F*)f->Get(hname_zjets_SfIterativeFitCferr1_up.c_str());
	     std::string hname_zjets_SfIterativeFitCferr1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr1_Down_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitCferr1_down = (TH1F*)f->Get(hname_zjets_SfIterativeFitCferr1_down.c_str());
	     
	     std::string hname_zjets_SfIterativeFitCferr2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr2_Up_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitCferr2_up = (TH1F*)f->Get(hname_zjets_SfIterativeFitCferr2_up.c_str());
	     std::string hname_zjets_SfIterativeFitCferr2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr2_Down_zjets_clone";
	     TH1F *hget_zjets_SfIterativeFitCferr2_down = (TH1F*)f->Get(hname_zjets_SfIterativeFitCferr2_down.c_str());

	     std::string hname_zjets_Jes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jes_Up_zjets_clone";
	     TH1F *hget_zjets_Jes_up = (TH1F*)f->Get(hname_zjets_Jes_up.c_str());
	     std::string hname_zjets_Jes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jes_Down_zjets_clone";
	     TH1F *hget_zjets_Jes_down = (TH1F*)f->Get(hname_zjets_Jes_down.c_str());

	     std::string hname_zjets_Jer_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jer_Up_zjets_clone";
	     TH1F *hget_zjets_Jer_up = (TH1F*)f->Get(hname_zjets_Jer_up.c_str());
	     std::string hname_zjets_Jer_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jer_Down_zjets_clone";
	     TH1F *hget_zjets_Jer_down = (TH1F*)f->Get(hname_zjets_Jer_down.c_str());
	     
	     // wjets
   
	     std::string hname_wjets = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_wjets_clone";
	     TH1F *hget_wjets = (TH1F*)f->Get(hname_wjets.c_str());
	     
	     std::string hname_wjets_SfIterativeFitHfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats1_Up_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitHfstats1_up = (TH1F*)f->Get(hname_wjets_SfIterativeFitHfstats1_up.c_str());
	     std::string hname_wjets_SfIterativeFitHfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats1_Down_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitHfstats1_down = (TH1F*)f->Get(hname_wjets_SfIterativeFitHfstats1_down.c_str());
	     
	     std::string hname_wjets_SfIterativeFitHfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats2_Up_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitHfstats2_up = (TH1F*)f->Get(hname_wjets_SfIterativeFitHfstats2_up.c_str());
	     std::string hname_wjets_SfIterativeFitHfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHfstats2_Down_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitHfstats2_down = (TH1F*)f->Get(hname_wjets_SfIterativeFitHfstats2_down.c_str());
	     
	     std::string hname_wjets_SfIterativeFitLfstats1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats1_Up_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitLfstats1_up = (TH1F*)f->Get(hname_wjets_SfIterativeFitLfstats1_up.c_str());
	     std::string hname_wjets_SfIterativeFitLfstats1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats1_Down_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitLfstats1_down = (TH1F*)f->Get(hname_wjets_SfIterativeFitLfstats1_down.c_str());
	     
	     std::string hname_wjets_SfIterativeFitLfstats2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats2_Up_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitLfstats2_up = (TH1F*)f->Get(hname_wjets_SfIterativeFitLfstats2_up.c_str());
	     std::string hname_wjets_SfIterativeFitLfstats2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLfstats2_Down_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitLfstats2_down = (TH1F*)f->Get(hname_wjets_SfIterativeFitLfstats2_down.c_str());
	     
	     std::string hname_wjets_SfIterativeFitJes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitJes_Up_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitJes_up = (TH1F*)f->Get(hname_wjets_SfIterativeFitJes_up.c_str());
	     std::string hname_wjets_SfIterativeFitJes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitJes_Down_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitJes_down = (TH1F*)f->Get(hname_wjets_SfIterativeFitJes_down.c_str());
	     
	     std::string hname_wjets_SfIterativeFitLf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLf_Up_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitLf_up = (TH1F*)f->Get(hname_wjets_SfIterativeFitLf_up.c_str());
	     std::string hname_wjets_SfIterativeFitLf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitLf_Down_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitLf_down = (TH1F*)f->Get(hname_wjets_SfIterativeFitLf_down.c_str());
	     
	     std::string hname_wjets_SfIterativeFitHf_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHf_Up_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitHf_up = (TH1F*)f->Get(hname_wjets_SfIterativeFitHf_up.c_str());
	     std::string hname_wjets_SfIterativeFitHf_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitHf_Down_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitHf_down = (TH1F*)f->Get(hname_wjets_SfIterativeFitHf_down.c_str());

	     std::string hname_wjets_SfIterativeFitCferr1_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr1_Up_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitCferr1_up = (TH1F*)f->Get(hname_wjets_SfIterativeFitCferr1_up.c_str());
	     std::string hname_wjets_SfIterativeFitCferr1_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr1_Down_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitCferr1_down = (TH1F*)f->Get(hname_wjets_SfIterativeFitCferr1_down.c_str());
	     
	     std::string hname_wjets_SfIterativeFitCferr2_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr2_Up_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitCferr2_up = (TH1F*)f->Get(hname_wjets_SfIterativeFitCferr2_up.c_str());
	     std::string hname_wjets_SfIterativeFitCferr2_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_SfIterativeFitCferr2_Down_wjets_clone";
	     TH1F *hget_wjets_SfIterativeFitCferr2_down = (TH1F*)f->Get(hname_wjets_SfIterativeFitCferr2_down.c_str());

	     std::string hname_wjets_Jes_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jes_Up_wjets_clone";
	     TH1F *hget_wjets_Jes_up = (TH1F*)f->Get(hname_wjets_Jes_up.c_str());
	     std::string hname_wjets_Jes_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jes_Down_wjets_clone";
	     TH1F *hget_wjets_Jes_down = (TH1F*)f->Get(hname_wjets_Jes_down.c_str());

	     std::string hname_wjets_Jer_up = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jer_Up_wjets_clone";
	     TH1F *hget_wjets_Jer_up = (TH1F*)f->Get(hname_wjets_Jer_up.c_str());
	     std::string hname_wjets_Jer_down = "h_"+dist[id]+"_all_"+cat[ic]+"_ALL_Jer_Down_wjets_clone";
	     TH1F *hget_wjets_Jer_down = (TH1F*)f->Get(hname_wjets_Jer_down.c_str());

	     // Output
	     std::string fname = "input/input_"+dist[id]+"_"+cat[ic]+"_"+coup[id]+".root";
	     TFile *fout = new TFile(fname.c_str(),"RECREATE");
	     std::cout << fname << std::endl;
  
	     TH1F *hclone_data = (TH1F*)hget_data->Clone("h_data_obs");
	     std::string tname = "stats/input_"+dist[id]+"_"+cat[ic]+"_"+coup[id]+".txt";
   
	     TH1F *hclone_sig_stop = (TH1F*)hget_sig_stop->Clone("h_sig_stop"); 
	     checkEmptyBins(hclone_sig_stop);
	     TH1F *hclone_sig_ttbar = (TH1F*)hget_sig_ttbar->Clone("h_sig_ttbar");
	     checkEmptyBins(hclone_sig_ttbar);
	     TH1F *hclone_sig = (TH1F*)hget_sig_stop->Clone("h_sig");
	     hclone_sig->Add(hclone_sig_ttbar);

	     TH1F *hclone_sig_stop_SfIterativeFitHfstats1_up = (TH1F*)hget_sig_stop_SfIterativeFitHfstats1_up->Clone("h_sig_stop_SfIterativeFitHfstats1Up");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitHfstats1_up);
	     TH1F *hclone_sig_ttbar_SfIterativeFitHfstats1_up = (TH1F*)hget_sig_ttbar_SfIterativeFitHfstats1_up->Clone("h_sig_ttbar_SfIterativeFitHfstats1Up");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitHfstats1_up);
	     TH1F *hclone_sig_SfIterativeFitHfstats1_up = (TH1F*)hget_sig_stop_SfIterativeFitHfstats1_up->Clone("h_sig_SfIterativeFitHfstats1Up");
	     hclone_sig_SfIterativeFitHfstats1_up->Add(hclone_sig_ttbar_SfIterativeFitHfstats1_up);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitHfstats1_down = (TH1F*)hget_sig_stop_SfIterativeFitHfstats1_down->Clone("h_sig_stop_SfIterativeFitHfstats1Down");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitHfstats1_down);
	     TH1F *hclone_sig_ttbar_SfIterativeFitHfstats1_down = (TH1F*)hget_sig_ttbar_SfIterativeFitHfstats1_down->Clone("h_sig_ttbar_SfIterativeFitHfstats1Down");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitHfstats1_down);
	     TH1F *hclone_sig_SfIterativeFitHfstats1_down = (TH1F*)hget_sig_stop_SfIterativeFitHfstats1_down->Clone("h_sig_SfIterativeFitHfstats1Down");
	     hclone_sig_SfIterativeFitHfstats1_down->Add(hclone_sig_ttbar_SfIterativeFitHfstats1_down);

	     TH1F *hclone_sig_stop_SfIterativeFitHfstats2_up = (TH1F*)hget_sig_stop_SfIterativeFitHfstats2_up->Clone("h_sig_stop_SfIterativeFitHfstats2Up");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitHfstats2_up);
	     TH1F *hclone_sig_ttbar_SfIterativeFitHfstats2_up = (TH1F*)hget_sig_ttbar_SfIterativeFitHfstats2_up->Clone("h_sig_ttbar_SfIterativeFitHfstats2Up");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitHfstats2_up);
	     TH1F *hclone_sig_SfIterativeFitHfstats2_up = (TH1F*)hget_sig_stop_SfIterativeFitHfstats2_up->Clone("h_sig_SfIterativeFitHfstats2Up");
	     hclone_sig_SfIterativeFitHfstats2_up->Add(hclone_sig_ttbar_SfIterativeFitHfstats2_up);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitHfstats2_down = (TH1F*)hget_sig_stop_SfIterativeFitHfstats2_down->Clone("h_sig_stop_SfIterativeFitHfstats2Down");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitHfstats2_down);
	     TH1F *hclone_sig_ttbar_SfIterativeFitHfstats2_down = (TH1F*)hget_sig_ttbar_SfIterativeFitHfstats2_down->Clone("h_sig_ttbar_SfIterativeFitHfstats2Down");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitHfstats2_down);
	     TH1F *hclone_sig_SfIterativeFitHfstats2_down = (TH1F*)hget_sig_stop_SfIterativeFitHfstats2_down->Clone("h_sig_SfIterativeFitHfstats2Down");
	     hclone_sig_SfIterativeFitHfstats2_down->Add(hclone_sig_ttbar_SfIterativeFitHfstats2_down);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitLfstats1_up = (TH1F*)hget_sig_stop_SfIterativeFitLfstats1_up->Clone("h_sig_stop_SfIterativeFitLfstats1Up");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitLfstats1_up);
	     TH1F *hclone_sig_ttbar_SfIterativeFitLfstats1_up = (TH1F*)hget_sig_ttbar_SfIterativeFitLfstats1_up->Clone("h_sig_ttbar_SfIterativeFitLfstats1Up");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitLfstats1_up);
	     TH1F *hclone_sig_SfIterativeFitLfstats1_up = (TH1F*)hget_sig_stop_SfIterativeFitLfstats1_up->Clone("h_sig_SfIterativeFitLfstats1Up");
	     hclone_sig_SfIterativeFitLfstats1_up->Add(hclone_sig_ttbar_SfIterativeFitLfstats1_up);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitLfstats1_down = (TH1F*)hget_sig_stop_SfIterativeFitLfstats1_down->Clone("h_sig_stop_SfIterativeFitLfstats1Down");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitLfstats1_down);
	     TH1F *hclone_sig_ttbar_SfIterativeFitLfstats1_down = (TH1F*)hget_sig_ttbar_SfIterativeFitLfstats1_down->Clone("h_sig_ttbar_SfIterativeFitLfstats1Down");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitLfstats1_down);
	     TH1F *hclone_sig_SfIterativeFitLfstats1_down = (TH1F*)hget_sig_stop_SfIterativeFitLfstats1_down->Clone("h_sig_SfIterativeFitLfstats1Down");
	     hclone_sig_SfIterativeFitLfstats1_down->Add(hclone_sig_ttbar_SfIterativeFitLfstats1_down);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitLfstats2_up = (TH1F*)hget_sig_stop_SfIterativeFitLfstats2_up->Clone("h_sig_stop_SfIterativeFitLfstats2Up");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitLfstats2_up);
	     TH1F *hclone_sig_ttbar_SfIterativeFitLfstats2_up = (TH1F*)hget_sig_ttbar_SfIterativeFitLfstats2_up->Clone("h_sig_ttbar_SfIterativeFitLfstats2Up");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitLfstats2_up);
	     TH1F *hclone_sig_SfIterativeFitLfstats2_up = (TH1F*)hget_sig_stop_SfIterativeFitLfstats2_up->Clone("h_sig_SfIterativeFitLfstats2Up");
	     hclone_sig_SfIterativeFitLfstats2_up->Add(hclone_sig_ttbar_SfIterativeFitLfstats2_up);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitLfstats2_down = (TH1F*)hget_sig_stop_SfIterativeFitLfstats2_down->Clone("h_sig_stop_SfIterativeFitLfstats2Down");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitLfstats2_down);
	     TH1F *hclone_sig_ttbar_SfIterativeFitLfstats2_down = (TH1F*)hget_sig_ttbar_SfIterativeFitLfstats2_down->Clone("h_sig_ttbar_SfIterativeFitLfstats2Down");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitLfstats2_down);
	     TH1F *hclone_sig_SfIterativeFitLfstats2_down = (TH1F*)hget_sig_stop_SfIterativeFitLfstats2_down->Clone("h_sig_SfIterativeFitLfstats2Down");
	     hclone_sig_SfIterativeFitLfstats2_down->Add(hclone_sig_ttbar_SfIterativeFitLfstats2_down);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitJes_up = (TH1F*)hget_sig_stop_SfIterativeFitJes_up->Clone("h_sig_stop_SfIterativeFitJesUp");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitJes_up);
	     TH1F *hclone_sig_ttbar_SfIterativeFitJes_up = (TH1F*)hget_sig_ttbar_SfIterativeFitJes_up->Clone("h_sig_ttbar_SfIterativeFitJesUp");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitJes_up);
	     TH1F *hclone_sig_SfIterativeFitJes_up = (TH1F*)hget_sig_stop_SfIterativeFitJes_up->Clone("h_sig_SfIterativeFitJesUp");
	     hclone_sig_SfIterativeFitJes_up->Add(hclone_sig_ttbar_SfIterativeFitJes_up);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitJes_down = (TH1F*)hget_sig_stop_SfIterativeFitJes_down->Clone("h_sig_stop_SfIterativeFitJesDown");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitJes_down);
	     TH1F *hclone_sig_ttbar_SfIterativeFitJes_down = (TH1F*)hget_sig_ttbar_SfIterativeFitJes_down->Clone("h_sig_ttbar_SfIterativeFitJesDown");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitJes_down);
	     TH1F *hclone_sig_SfIterativeFitJes_down = (TH1F*)hget_sig_stop_SfIterativeFitJes_down->Clone("h_sig_SfIterativeFitJesDown");
	     hclone_sig_SfIterativeFitJes_down->Add(hclone_sig_ttbar_SfIterativeFitJes_down);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitLf_up = (TH1F*)hget_sig_stop_SfIterativeFitLf_up->Clone("h_sig_stop_SfIterativeFitLfUp");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitLf_up);
	     TH1F *hclone_sig_ttbar_SfIterativeFitLf_up = (TH1F*)hget_sig_ttbar_SfIterativeFitLf_up->Clone("h_sig_ttbar_SfIterativeFitLfUp");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitLf_up);
	     TH1F *hclone_sig_SfIterativeFitLf_up = (TH1F*)hget_sig_stop_SfIterativeFitLf_up->Clone("h_sig_SfIterativeFitLfUp");
	     hclone_sig_SfIterativeFitLf_up->Add(hclone_sig_ttbar_SfIterativeFitLf_up);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitLf_down = (TH1F*)hget_sig_stop_SfIterativeFitLf_down->Clone("h_sig_stop_SfIterativeFitLfDown");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitLf_down);
	     TH1F *hclone_sig_ttbar_SfIterativeFitLf_down = (TH1F*)hget_sig_ttbar_SfIterativeFitLf_down->Clone("h_sig_ttbar_SfIterativeFitLfDown");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitLf_down);
	     TH1F *hclone_sig_SfIterativeFitLf_down = (TH1F*)hget_sig_stop_SfIterativeFitLf_down->Clone("h_sig_SfIterativeFitLfDown");
	     hclone_sig_SfIterativeFitLf_down->Add(hclone_sig_ttbar_SfIterativeFitLf_down);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitHf_up = (TH1F*)hget_sig_stop_SfIterativeFitHf_up->Clone("h_sig_stop_SfIterativeFitHfUp");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitHf_up);
	     TH1F *hclone_sig_ttbar_SfIterativeFitHf_up = (TH1F*)hget_sig_ttbar_SfIterativeFitHf_up->Clone("h_sig_ttbar_SfIterativeFitHfUp");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitHf_up);
	     TH1F *hclone_sig_SfIterativeFitHf_up = (TH1F*)hget_sig_stop_SfIterativeFitHf_up->Clone("h_sig_SfIterativeFitHfUp");
	     hclone_sig_SfIterativeFitHf_up->Add(hclone_sig_ttbar_SfIterativeFitHf_up);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitHf_down = (TH1F*)hget_sig_stop_SfIterativeFitHf_down->Clone("h_sig_stop_SfIterativeFitHfDown");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitHf_down);
	     TH1F *hclone_sig_ttbar_SfIterativeFitHf_down = (TH1F*)hget_sig_ttbar_SfIterativeFitHf_down->Clone("h_sig_ttbar_SfIterativeFitHfDown");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitHf_down);
	     TH1F *hclone_sig_SfIterativeFitHf_down = (TH1F*)hget_sig_stop_SfIterativeFitHf_down->Clone("h_sig_SfIterativeFitHfDown");
	     hclone_sig_SfIterativeFitHf_down->Add(hclone_sig_ttbar_SfIterativeFitHf_down);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitCferr1_up = (TH1F*)hget_sig_stop_SfIterativeFitCferr1_up->Clone("h_sig_stop_SfIterativeFitCferr1Up");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitCferr1_up);
	     TH1F *hclone_sig_ttbar_SfIterativeFitCferr1_up = (TH1F*)hget_sig_ttbar_SfIterativeFitCferr1_up->Clone("h_sig_ttbar_SfIterativeFitCferr1Up");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitCferr1_up);
	     TH1F *hclone_sig_SfIterativeFitCferr1_up = (TH1F*)hget_sig_stop_SfIterativeFitCferr1_up->Clone("h_sig_SfIterativeFitCferr1Up");
	     hclone_sig_SfIterativeFitCferr1_up->Add(hclone_sig_ttbar_SfIterativeFitCferr1_up);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitCferr1_down = (TH1F*)hget_sig_stop_SfIterativeFitCferr1_down->Clone("h_sig_stop_SfIterativeFitCferr1Down");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitCferr1_down);
	     TH1F *hclone_sig_ttbar_SfIterativeFitCferr1_down = (TH1F*)hget_sig_ttbar_SfIterativeFitCferr1_down->Clone("h_sig_ttbar_SfIterativeFitCferr1Down");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitCferr1_down);
	     TH1F *hclone_sig_SfIterativeFitCferr1_down = (TH1F*)hget_sig_stop_SfIterativeFitCferr1_down->Clone("h_sig_SfIterativeFitCferr1Down");
	     hclone_sig_SfIterativeFitCferr1_down->Add(hclone_sig_ttbar_SfIterativeFitCferr1_down);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitCferr2_up = (TH1F*)hget_sig_stop_SfIterativeFitCferr2_up->Clone("h_sig_stop_SfIterativeFitCferr2Up");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitCferr2_up);
	     TH1F *hclone_sig_ttbar_SfIterativeFitCferr2_up = (TH1F*)hget_sig_ttbar_SfIterativeFitCferr2_up->Clone("h_sig_ttbar_SfIterativeFitCferr2Up");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitCferr2_up);
	     TH1F *hclone_sig_SfIterativeFitCferr2_up = (TH1F*)hget_sig_stop_SfIterativeFitCferr2_up->Clone("h_sig_SfIterativeFitCferr2Up");
	     hclone_sig_SfIterativeFitCferr2_up->Add(hclone_sig_ttbar_SfIterativeFitCferr2_up);
	     
	     TH1F *hclone_sig_stop_SfIterativeFitCferr2_down = (TH1F*)hget_sig_stop_SfIterativeFitCferr2_down->Clone("h_sig_stop_SfIterativeFitCferr2Down");
	     checkEmptyBins(hclone_sig_stop_SfIterativeFitCferr2_down);
	     TH1F *hclone_sig_ttbar_SfIterativeFitCferr2_down = (TH1F*)hget_sig_ttbar_SfIterativeFitCferr2_down->Clone("h_sig_ttbar_SfIterativeFitCferr2Down");
	     checkEmptyBins(hclone_sig_ttbar_SfIterativeFitCferr2_down);
	     TH1F *hclone_sig_SfIterativeFitCferr2_down = (TH1F*)hget_sig_stop_SfIterativeFitCferr2_down->Clone("h_sig_SfIterativeFitCferr2Down");
	     hclone_sig_SfIterativeFitCferr2_down->Add(hclone_sig_ttbar_SfIterativeFitCferr2_down);

	     TH1F *hclone_sig_stop_Jes_up = (TH1F*)hget_sig_stop_Jes_up->Clone("h_sig_stop_JesUp");
	     checkEmptyBins(hclone_sig_stop_Jes_up);
	     TH1F *hclone_sig_ttbar_Jes_up = (TH1F*)hget_sig_ttbar_Jes_up->Clone("h_sig_ttbar_JesUp");
	     checkEmptyBins(hclone_sig_ttbar_Jes_up);
	     TH1F *hclone_sig_Jes_up = (TH1F*)hget_sig_stop_Jes_up->Clone("h_sig_JesUp");
	     hclone_sig_Jes_up->Add(hclone_sig_ttbar_Jes_up);
	     
	     TH1F *hclone_sig_stop_Jes_down = (TH1F*)hget_sig_stop_Jes_down->Clone("h_sig_stop_JesDown");
	     checkEmptyBins(hclone_sig_stop_Jes_down);
	     TH1F *hclone_sig_ttbar_Jes_down = (TH1F*)hget_sig_ttbar_Jes_down->Clone("h_sig_ttbar_JesDown");
	     checkEmptyBins(hclone_sig_ttbar_Jes_down);
	     TH1F *hclone_sig_Jes_down = (TH1F*)hget_sig_stop_Jes_down->Clone("h_sig_JesDown");
	     hclone_sig_Jes_down->Add(hclone_sig_ttbar_Jes_down);

	     TH1F *hclone_sig_stop_Jer_up = (TH1F*)hget_sig_stop_Jer_up->Clone("h_sig_stop_JerUp");
	     checkEmptyBins(hclone_sig_stop_Jer_up);
	     TH1F *hclone_sig_ttbar_Jer_up = (TH1F*)hget_sig_ttbar_Jer_up->Clone("h_sig_ttbar_JerUp");
	     checkEmptyBins(hclone_sig_ttbar_Jer_up);
	     TH1F *hclone_sig_Jer_up = (TH1F*)hget_sig_stop_Jer_up->Clone("h_sig_JerUp");
	     hclone_sig_Jer_up->Add(hclone_sig_ttbar_Jer_up);
	     
	     TH1F *hclone_sig_stop_Jer_down = (TH1F*)hget_sig_stop_Jer_down->Clone("h_sig_stop_JerDown");
	     checkEmptyBins(hclone_sig_stop_Jer_down);
	     TH1F *hclone_sig_ttbar_Jer_down = (TH1F*)hget_sig_ttbar_Jer_down->Clone("h_sig_ttbar_JerDown");
	     checkEmptyBins(hclone_sig_ttbar_Jer_down);
	     TH1F *hclone_sig_Jer_down = (TH1F*)hget_sig_stop_Jer_down->Clone("h_sig_JerDown");
	     hclone_sig_Jer_down->Add(hclone_sig_ttbar_Jer_down);
	     
	     // ttbb
   
	     TH1F *hclone_ttbb = (TH1F*)hget_ttbb->Clone("h_ttbb");
	     checkEmptyBins(hclone_ttbb);
	     TH1F *hclone_ttbb_SfIterativeFitHfstats1_up = (TH1F*)hget_ttbb_SfIterativeFitHfstats1_up->Clone("h_ttbb_SfIterativeFitHfstats1Up");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitHfstats1_up);
	     TH1F *hclone_ttbb_SfIterativeFitHfstats1_down = (TH1F*)hget_ttbb_SfIterativeFitHfstats1_down->Clone("h_ttbb_SfIterativeFitHfstats1Down");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitHfstats1_down);
	     TH1F *hclone_ttbb_SfIterativeFitHfstats2_up = (TH1F*)hget_ttbb_SfIterativeFitHfstats2_up->Clone("h_ttbb_SfIterativeFitHfstats2Up");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitHfstats2_up);
	     TH1F *hclone_ttbb_SfIterativeFitHfstats2_down = (TH1F*)hget_ttbb_SfIterativeFitHfstats2_down->Clone("h_ttbb_SfIterativeFitHfstats2Down");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitHfstats2_down);
	     TH1F *hclone_ttbb_SfIterativeFitLfstats1_up = (TH1F*)hget_ttbb_SfIterativeFitLfstats1_up->Clone("h_ttbb_SfIterativeFitLfstats1Up");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitLfstats1_up);
	     TH1F *hclone_ttbb_SfIterativeFitLfstats1_down = (TH1F*)hget_ttbb_SfIterativeFitLfstats1_down->Clone("h_ttbb_SfIterativeFitLfstats1Down");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitLfstats1_down);
	     TH1F *hclone_ttbb_SfIterativeFitLfstats2_up = (TH1F*)hget_ttbb_SfIterativeFitLfstats2_up->Clone("h_ttbb_SfIterativeFitLfstats2Up");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitLfstats2_up);
	     TH1F *hclone_ttbb_SfIterativeFitLfstats2_down = (TH1F*)hget_ttbb_SfIterativeFitLfstats2_down->Clone("h_ttbb_SfIterativeFitLfstats2Down");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitLfstats2_down);
	     TH1F *hclone_ttbb_SfIterativeFitJes_up = (TH1F*)hget_ttbb_SfIterativeFitJes_up->Clone("h_ttbb_SfIterativeFitJesUp");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitJes_up);
	     TH1F *hclone_ttbb_SfIterativeFitJes_down = (TH1F*)hget_ttbb_SfIterativeFitJes_down->Clone("h_ttbb_SfIterativeFitJesDown");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitJes_down);
	     TH1F *hclone_ttbb_SfIterativeFitLf_up = (TH1F*)hget_ttbb_SfIterativeFitLf_up->Clone("h_ttbb_SfIterativeFitLfUp");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitLf_up);
	     TH1F *hclone_ttbb_SfIterativeFitLf_down = (TH1F*)hget_ttbb_SfIterativeFitLf_down->Clone("h_ttbb_SfIterativeFitLfDown");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitLf_down);
	     TH1F *hclone_ttbb_SfIterativeFitHf_up = (TH1F*)hget_ttbb_SfIterativeFitHf_up->Clone("h_ttbb_SfIterativeFitHfUp");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitHf_up);
	     TH1F *hclone_ttbb_SfIterativeFitHf_down = (TH1F*)hget_ttbb_SfIterativeFitHf_down->Clone("h_ttbb_SfIterativeFitHfDown");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitHf_down);
	     TH1F *hclone_ttbb_SfIterativeFitCferr1_up = (TH1F*)hget_ttbb_SfIterativeFitCferr1_up->Clone("h_ttbb_SfIterativeFitCferr1Up");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitCferr1_up);
	     TH1F *hclone_ttbb_SfIterativeFitCferr1_down = (TH1F*)hget_ttbb_SfIterativeFitCferr1_down->Clone("h_ttbb_SfIterativeFitCferr1Down");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitCferr1_down);
	     TH1F *hclone_ttbb_SfIterativeFitCferr2_up = (TH1F*)hget_ttbb_SfIterativeFitCferr2_up->Clone("h_ttbb_SfIterativeFitCferr2Up");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitCferr2_up);
	     TH1F *hclone_ttbb_SfIterativeFitCferr2_down = (TH1F*)hget_ttbb_SfIterativeFitCferr2_down->Clone("h_ttbb_SfIterativeFitCferr2Down");
	     checkEmptyBins(hclone_ttbb_SfIterativeFitCferr2_down);
	     TH1F *hclone_ttbb_Jes_up = (TH1F*)hget_ttbb_Jes_up->Clone("h_ttbb_JesUp");
	     checkEmptyBins(hclone_ttbb_Jes_up);
	     TH1F *hclone_ttbb_Jes_down = (TH1F*)hget_ttbb_Jes_down->Clone("h_ttbb_JesDown");
	     checkEmptyBins(hclone_ttbb_Jes_down);
	     TH1F *hclone_ttbb_Jer_up = (TH1F*)hget_ttbb_Jer_up->Clone("h_ttbb_JerUp");
	     checkEmptyBins(hclone_ttbb_Jer_up);
	     TH1F *hclone_ttbb_Jer_down = (TH1F*)hget_ttbb_Jer_down->Clone("h_ttbb_JerDown");
	     checkEmptyBins(hclone_ttbb_Jer_down);
	     
	     // ttcc
   
	     TH1F *hclone_ttcc = (TH1F*)hget_ttcc->Clone("h_ttcc");
	     checkEmptyBins(hclone_ttcc);
	     TH1F *hclone_ttcc_SfIterativeFitHfstats1_up = (TH1F*)hget_ttcc_SfIterativeFitHfstats1_up->Clone("h_ttcc_SfIterativeFitHfstats1Up");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitHfstats1_up);
	     TH1F *hclone_ttcc_SfIterativeFitHfstats1_down = (TH1F*)hget_ttcc_SfIterativeFitHfstats1_down->Clone("h_ttcc_SfIterativeFitHfstats1Down");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitHfstats1_down);
	     TH1F *hclone_ttcc_SfIterativeFitHfstats2_up = (TH1F*)hget_ttcc_SfIterativeFitHfstats2_up->Clone("h_ttcc_SfIterativeFitHfstats2Up");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitHfstats2_up);
	     TH1F *hclone_ttcc_SfIterativeFitHfstats2_down = (TH1F*)hget_ttcc_SfIterativeFitHfstats2_down->Clone("h_ttcc_SfIterativeFitHfstats2Down");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitHfstats2_down);
	     TH1F *hclone_ttcc_SfIterativeFitLfstats1_up = (TH1F*)hget_ttcc_SfIterativeFitLfstats1_up->Clone("h_ttcc_SfIterativeFitLfstats1Up");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitLfstats1_up);
	     TH1F *hclone_ttcc_SfIterativeFitLfstats1_down = (TH1F*)hget_ttcc_SfIterativeFitLfstats1_down->Clone("h_ttcc_SfIterativeFitLfstats1Down");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitLfstats1_down);
	     TH1F *hclone_ttcc_SfIterativeFitLfstats2_up = (TH1F*)hget_ttcc_SfIterativeFitLfstats2_up->Clone("h_ttcc_SfIterativeFitLfstats2Up");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitLfstats2_up);
	     TH1F *hclone_ttcc_SfIterativeFitLfstats2_down = (TH1F*)hget_ttcc_SfIterativeFitLfstats2_down->Clone("h_ttcc_SfIterativeFitLfstats2Down");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitLfstats2_down);
	     TH1F *hclone_ttcc_SfIterativeFitJes_up = (TH1F*)hget_ttcc_SfIterativeFitJes_up->Clone("h_ttcc_SfIterativeFitJesUp");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitJes_up);
	     TH1F *hclone_ttcc_SfIterativeFitJes_down = (TH1F*)hget_ttcc_SfIterativeFitJes_down->Clone("h_ttcc_SfIterativeFitJesDown");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitJes_down);
	     TH1F *hclone_ttcc_SfIterativeFitLf_up = (TH1F*)hget_ttcc_SfIterativeFitLf_up->Clone("h_ttcc_SfIterativeFitLfUp");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitLf_up);
	     TH1F *hclone_ttcc_SfIterativeFitLf_down = (TH1F*)hget_ttcc_SfIterativeFitLf_down->Clone("h_ttcc_SfIterativeFitLfDown");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitLf_down);
	     TH1F *hclone_ttcc_SfIterativeFitHf_up = (TH1F*)hget_ttcc_SfIterativeFitHf_up->Clone("h_ttcc_SfIterativeFitHfUp");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitHf_up);
	     TH1F *hclone_ttcc_SfIterativeFitHf_down = (TH1F*)hget_ttcc_SfIterativeFitHf_down->Clone("h_ttcc_SfIterativeFitHfDown");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitHf_down);
	     TH1F *hclone_ttcc_SfIterativeFitCferr1_up = (TH1F*)hget_ttcc_SfIterativeFitCferr1_up->Clone("h_ttcc_SfIterativeFitCferr1Up");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitCferr1_up);
	     TH1F *hclone_ttcc_SfIterativeFitCferr1_down = (TH1F*)hget_ttcc_SfIterativeFitCferr1_down->Clone("h_ttcc_SfIterativeFitCferr1Down");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitCferr1_down);
	     TH1F *hclone_ttcc_SfIterativeFitCferr2_up = (TH1F*)hget_ttcc_SfIterativeFitCferr2_up->Clone("h_ttcc_SfIterativeFitCferr2Up");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitCferr2_up);
	     TH1F *hclone_ttcc_SfIterativeFitCferr2_down = (TH1F*)hget_ttcc_SfIterativeFitCferr2_down->Clone("h_ttcc_SfIterativeFitCferr2Down");
	     checkEmptyBins(hclone_ttcc_SfIterativeFitCferr2_down);
	     TH1F *hclone_ttcc_Jes_up = (TH1F*)hget_ttcc_Jes_up->Clone("h_ttcc_JesUp");
	     checkEmptyBins(hclone_ttcc_Jes_up);
	     TH1F *hclone_ttcc_Jes_down = (TH1F*)hget_ttcc_Jes_down->Clone("h_ttcc_JesDown");
	     checkEmptyBins(hclone_ttcc_Jes_down);
	     TH1F *hclone_ttcc_Jer_up = (TH1F*)hget_ttcc_Jer_up->Clone("h_ttcc_JerUp");
	     checkEmptyBins(hclone_ttcc_Jer_up);
	     TH1F *hclone_ttcc_Jer_down = (TH1F*)hget_ttcc_Jer_down->Clone("h_ttcc_JerDown");
	     checkEmptyBins(hclone_ttcc_Jer_down);

	     // ttlf
   
	     TH1F *hclone_ttlf = (TH1F*)hget_ttlf->Clone("h_ttlf");
	     checkEmptyBins(hclone_ttlf);
	     TH1F *hclone_ttlf_SfIterativeFitHfstats1_up = (TH1F*)hget_ttlf_SfIterativeFitHfstats1_up->Clone("h_ttlf_SfIterativeFitHfstats1Up");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitHfstats1_up);
	     TH1F *hclone_ttlf_SfIterativeFitHfstats1_down = (TH1F*)hget_ttlf_SfIterativeFitHfstats1_down->Clone("h_ttlf_SfIterativeFitHfstats1Down");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitHfstats1_down);
	     TH1F *hclone_ttlf_SfIterativeFitHfstats2_up = (TH1F*)hget_ttlf_SfIterativeFitHfstats2_up->Clone("h_ttlf_SfIterativeFitHfstats2Up");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitHfstats2_up);
	     TH1F *hclone_ttlf_SfIterativeFitHfstats2_down = (TH1F*)hget_ttlf_SfIterativeFitHfstats2_down->Clone("h_ttlf_SfIterativeFitHfstats2Down");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitHfstats2_down);
	     TH1F *hclone_ttlf_SfIterativeFitLfstats1_up = (TH1F*)hget_ttlf_SfIterativeFitLfstats1_up->Clone("h_ttlf_SfIterativeFitLfstats1Up");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitLfstats1_up);
	     TH1F *hclone_ttlf_SfIterativeFitLfstats1_down = (TH1F*)hget_ttlf_SfIterativeFitLfstats1_down->Clone("h_ttlf_SfIterativeFitLfstats1Down");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitLfstats1_down);
	     TH1F *hclone_ttlf_SfIterativeFitLfstats2_up = (TH1F*)hget_ttlf_SfIterativeFitLfstats2_up->Clone("h_ttlf_SfIterativeFitLfstats2Up");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitLfstats2_up);
	     TH1F *hclone_ttlf_SfIterativeFitLfstats2_down = (TH1F*)hget_ttlf_SfIterativeFitLfstats2_down->Clone("h_ttlf_SfIterativeFitLfstats2Down");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitLfstats2_down);
	     TH1F *hclone_ttlf_SfIterativeFitJes_up = (TH1F*)hget_ttlf_SfIterativeFitJes_up->Clone("h_ttlf_SfIterativeFitJesUp");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitJes_up);
	     TH1F *hclone_ttlf_SfIterativeFitJes_down = (TH1F*)hget_ttlf_SfIterativeFitJes_down->Clone("h_ttlf_SfIterativeFitJesDown");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitJes_down);
	     TH1F *hclone_ttlf_SfIterativeFitLf_up = (TH1F*)hget_ttlf_SfIterativeFitLf_up->Clone("h_ttlf_SfIterativeFitLfUp");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitLf_up);
	     TH1F *hclone_ttlf_SfIterativeFitLf_down = (TH1F*)hget_ttlf_SfIterativeFitLf_down->Clone("h_ttlf_SfIterativeFitLfDown");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitLf_down);
	     TH1F *hclone_ttlf_SfIterativeFitHf_up = (TH1F*)hget_ttlf_SfIterativeFitHf_up->Clone("h_ttlf_SfIterativeFitHfUp");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitHf_up);
	     TH1F *hclone_ttlf_SfIterativeFitHf_down = (TH1F*)hget_ttlf_SfIterativeFitHf_down->Clone("h_ttlf_SfIterativeFitHfDown");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitHf_down);
	     TH1F *hclone_ttlf_SfIterativeFitCferr1_up = (TH1F*)hget_ttlf_SfIterativeFitCferr1_up->Clone("h_ttlf_SfIterativeFitCferr1Up");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitCferr1_up);
	     TH1F *hclone_ttlf_SfIterativeFitCferr1_down = (TH1F*)hget_ttlf_SfIterativeFitCferr1_down->Clone("h_ttlf_SfIterativeFitCferr1Down");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitCferr1_down);
	     TH1F *hclone_ttlf_SfIterativeFitCferr2_up = (TH1F*)hget_ttlf_SfIterativeFitCferr2_up->Clone("h_ttlf_SfIterativeFitCferr2Up");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitCferr2_up);
	     TH1F *hclone_ttlf_SfIterativeFitCferr2_down = (TH1F*)hget_ttlf_SfIterativeFitCferr2_down->Clone("h_ttlf_SfIterativeFitCferr2Down");
	     checkEmptyBins(hclone_ttlf_SfIterativeFitCferr2_down);
	     TH1F *hclone_ttlf_Jes_up = (TH1F*)hget_ttlf_Jes_up->Clone("h_ttlf_JesUp");
	     checkEmptyBins(hclone_ttlf_Jes_up);
	     TH1F *hclone_ttlf_Jes_down = (TH1F*)hget_ttlf_Jes_down->Clone("h_ttlf_JesDown");
	     checkEmptyBins(hclone_ttlf_Jes_down);
	     TH1F *hclone_ttlf_Jer_up = (TH1F*)hget_ttlf_Jer_up->Clone("h_ttlf_JerUp");
	     checkEmptyBins(hclone_ttlf_Jer_up);
	     TH1F *hclone_ttlf_Jer_down = (TH1F*)hget_ttlf_Jer_down->Clone("h_ttlf_JerDown");
	     checkEmptyBins(hclone_ttlf_Jer_down);

	     // stop
   
	     TH1F *hclone_stop = (TH1F*)hget_stop->Clone("h_stop");
	     checkEmptyBins(hclone_stop);
	     TH1F *hclone_stop_SfIterativeFitHfstats1_up = (TH1F*)hget_stop_SfIterativeFitHfstats1_up->Clone("h_stop_SfIterativeFitHfstats1Up");
	     checkEmptyBins(hclone_stop_SfIterativeFitHfstats1_up);
	     TH1F *hclone_stop_SfIterativeFitHfstats1_down = (TH1F*)hget_stop_SfIterativeFitHfstats1_down->Clone("h_stop_SfIterativeFitHfstats1Down");
	     checkEmptyBins(hclone_stop_SfIterativeFitHfstats1_down);
	     TH1F *hclone_stop_SfIterativeFitHfstats2_up = (TH1F*)hget_stop_SfIterativeFitHfstats2_up->Clone("h_stop_SfIterativeFitHfstats2Up");
	     checkEmptyBins(hclone_stop_SfIterativeFitHfstats2_up);
	     TH1F *hclone_stop_SfIterativeFitHfstats2_down = (TH1F*)hget_stop_SfIterativeFitHfstats2_down->Clone("h_stop_SfIterativeFitHfstats2Down");
	     checkEmptyBins(hclone_stop_SfIterativeFitHfstats2_down);
	     TH1F *hclone_stop_SfIterativeFitLfstats1_up = (TH1F*)hget_stop_SfIterativeFitLfstats1_up->Clone("h_stop_SfIterativeFitLfstats1Up");
	     checkEmptyBins(hclone_stop_SfIterativeFitLfstats1_up);
	     TH1F *hclone_stop_SfIterativeFitLfstats1_down = (TH1F*)hget_stop_SfIterativeFitLfstats1_down->Clone("h_stop_SfIterativeFitLfstats1Down");
	     checkEmptyBins(hclone_stop_SfIterativeFitLfstats1_down);
	     TH1F *hclone_stop_SfIterativeFitLfstats2_up = (TH1F*)hget_stop_SfIterativeFitLfstats2_up->Clone("h_stop_SfIterativeFitLfstats2Up");
	     checkEmptyBins(hclone_stop_SfIterativeFitLfstats2_up);
	     TH1F *hclone_stop_SfIterativeFitLfstats2_down = (TH1F*)hget_stop_SfIterativeFitLfstats2_down->Clone("h_stop_SfIterativeFitLfstats2Down");
	     checkEmptyBins(hclone_stop_SfIterativeFitLfstats2_down);
	     TH1F *hclone_stop_SfIterativeFitJes_up = (TH1F*)hget_stop_SfIterativeFitJes_up->Clone("h_stop_SfIterativeFitJesUp");
	     checkEmptyBins(hclone_stop_SfIterativeFitJes_up);
	     TH1F *hclone_stop_SfIterativeFitJes_down = (TH1F*)hget_stop_SfIterativeFitJes_down->Clone("h_stop_SfIterativeFitJesDown");
	     checkEmptyBins(hclone_stop_SfIterativeFitJes_down);
	     TH1F *hclone_stop_SfIterativeFitLf_up = (TH1F*)hget_stop_SfIterativeFitLf_up->Clone("h_stop_SfIterativeFitLfUp");
	     checkEmptyBins(hclone_stop_SfIterativeFitLf_up);
	     TH1F *hclone_stop_SfIterativeFitLf_down = (TH1F*)hget_stop_SfIterativeFitLf_down->Clone("h_stop_SfIterativeFitLfDown");
	     checkEmptyBins(hclone_stop_SfIterativeFitLf_down);
	     TH1F *hclone_stop_SfIterativeFitHf_up = (TH1F*)hget_stop_SfIterativeFitHf_up->Clone("h_stop_SfIterativeFitHfUp");
	     checkEmptyBins(hclone_stop_SfIterativeFitHf_up);
	     TH1F *hclone_stop_SfIterativeFitHf_down = (TH1F*)hget_stop_SfIterativeFitHf_down->Clone("h_stop_SfIterativeFitHfDown");
	     checkEmptyBins(hclone_stop_SfIterativeFitHf_down);
	     TH1F *hclone_stop_SfIterativeFitCferr1_up = (TH1F*)hget_stop_SfIterativeFitCferr1_up->Clone("h_stop_SfIterativeFitCferr1Up");
	     checkEmptyBins(hclone_stop_SfIterativeFitCferr1_up);
	     TH1F *hclone_stop_SfIterativeFitCferr1_down = (TH1F*)hget_stop_SfIterativeFitCferr1_down->Clone("h_stop_SfIterativeFitCferr1Down");
	     checkEmptyBins(hclone_stop_SfIterativeFitCferr1_down);
	     TH1F *hclone_stop_SfIterativeFitCferr2_up = (TH1F*)hget_stop_SfIterativeFitCferr2_up->Clone("h_stop_SfIterativeFitCferr2Up");
	     checkEmptyBins(hclone_stop_SfIterativeFitCferr2_up);
	     TH1F *hclone_stop_SfIterativeFitCferr2_down = (TH1F*)hget_stop_SfIterativeFitCferr2_down->Clone("h_stop_SfIterativeFitCferr2Down");
	     checkEmptyBins(hclone_stop_SfIterativeFitCferr2_down);
	     TH1F *hclone_stop_Jes_up = (TH1F*)hget_stop_Jes_up->Clone("h_stop_JesUp");
	     checkEmptyBins(hclone_stop_Jes_up);
	     TH1F *hclone_stop_Jes_down = (TH1F*)hget_stop_Jes_down->Clone("h_stop_JesDown");
	     checkEmptyBins(hclone_stop_Jes_down);
	     TH1F *hclone_stop_Jer_up = (TH1F*)hget_stop_Jer_up->Clone("h_stop_JerUp");
	     checkEmptyBins(hclone_stop_Jer_up);
	     TH1F *hclone_stop_Jer_down = (TH1F*)hget_stop_Jer_down->Clone("h_stop_JerDown");
	     checkEmptyBins(hclone_stop_Jer_down);

	     // zjets
   
	     TH1F *hclone_zjets = (TH1F*)hget_zjets->Clone("h_zjets");
	     checkEmptyBins(hclone_zjets);
	     TH1F *hclone_zjets_SfIterativeFitHfstats1_up = (TH1F*)hget_zjets_SfIterativeFitHfstats1_up->Clone("h_zjets_SfIterativeFitHfstats1Up");
	     checkEmptyBins(hclone_zjets_SfIterativeFitHfstats1_up);
	     TH1F *hclone_zjets_SfIterativeFitHfstats1_down = (TH1F*)hget_zjets_SfIterativeFitHfstats1_down->Clone("h_zjets_SfIterativeFitHfstats1Down");
	     checkEmptyBins(hclone_zjets_SfIterativeFitHfstats1_down);
	     TH1F *hclone_zjets_SfIterativeFitHfstats2_up = (TH1F*)hget_zjets_SfIterativeFitHfstats2_up->Clone("h_zjets_SfIterativeFitHfstats2Up");
	     checkEmptyBins(hclone_zjets_SfIterativeFitHfstats2_up);
	     TH1F *hclone_zjets_SfIterativeFitHfstats2_down = (TH1F*)hget_zjets_SfIterativeFitHfstats2_down->Clone("h_zjets_SfIterativeFitHfstats2Down");
	     checkEmptyBins(hclone_zjets_SfIterativeFitHfstats2_down);
	     TH1F *hclone_zjets_SfIterativeFitLfstats1_up = (TH1F*)hget_zjets_SfIterativeFitLfstats1_up->Clone("h_zjets_SfIterativeFitLfstats1Up");
	     checkEmptyBins(hclone_zjets_SfIterativeFitLfstats1_up);
	     TH1F *hclone_zjets_SfIterativeFitLfstats1_down = (TH1F*)hget_zjets_SfIterativeFitLfstats1_down->Clone("h_zjets_SfIterativeFitLfstats1Down");
	     checkEmptyBins(hclone_zjets_SfIterativeFitLfstats1_down);
	     TH1F *hclone_zjets_SfIterativeFitLfstats2_up = (TH1F*)hget_zjets_SfIterativeFitLfstats2_up->Clone("h_zjets_SfIterativeFitLfstats2Up");
	     checkEmptyBins(hclone_zjets_SfIterativeFitLfstats2_up);
	     TH1F *hclone_zjets_SfIterativeFitLfstats2_down = (TH1F*)hget_zjets_SfIterativeFitLfstats2_down->Clone("h_zjets_SfIterativeFitLfstats2Down");
	     checkEmptyBins(hclone_zjets_SfIterativeFitLfstats2_down);
	     TH1F *hclone_zjets_SfIterativeFitJes_up = (TH1F*)hget_zjets_SfIterativeFitJes_up->Clone("h_zjets_SfIterativeFitJesUp");
	     checkEmptyBins(hclone_zjets_SfIterativeFitJes_up);
	     TH1F *hclone_zjets_SfIterativeFitJes_down = (TH1F*)hget_zjets_SfIterativeFitJes_down->Clone("h_zjets_SfIterativeFitJesDown");
	     checkEmptyBins(hclone_zjets_SfIterativeFitJes_down);
	     TH1F *hclone_zjets_SfIterativeFitLf_up = (TH1F*)hget_zjets_SfIterativeFitLf_up->Clone("h_zjets_SfIterativeFitLfUp");
	     checkEmptyBins(hclone_zjets_SfIterativeFitLf_up);
	     TH1F *hclone_zjets_SfIterativeFitLf_down = (TH1F*)hget_zjets_SfIterativeFitLf_down->Clone("h_zjets_SfIterativeFitLfDown");
	     checkEmptyBins(hclone_zjets_SfIterativeFitLf_down);
	     TH1F *hclone_zjets_SfIterativeFitHf_up = (TH1F*)hget_zjets_SfIterativeFitHf_up->Clone("h_zjets_SfIterativeFitHfUp");
	     checkEmptyBins(hclone_zjets_SfIterativeFitHf_up);
	     TH1F *hclone_zjets_SfIterativeFitHf_down = (TH1F*)hget_zjets_SfIterativeFitHf_down->Clone("h_zjets_SfIterativeFitHfDown");
	     checkEmptyBins(hclone_zjets_SfIterativeFitHf_down);
	     TH1F *hclone_zjets_SfIterativeFitCferr1_up = (TH1F*)hget_zjets_SfIterativeFitCferr1_up->Clone("h_zjets_SfIterativeFitCferr1Up");
	     checkEmptyBins(hclone_zjets_SfIterativeFitCferr1_up);
	     TH1F *hclone_zjets_SfIterativeFitCferr1_down = (TH1F*)hget_zjets_SfIterativeFitCferr1_down->Clone("h_zjets_SfIterativeFitCferr1Down");
	     checkEmptyBins(hclone_zjets_SfIterativeFitCferr1_down);
	     TH1F *hclone_zjets_SfIterativeFitCferr2_up = (TH1F*)hget_zjets_SfIterativeFitCferr2_up->Clone("h_zjets_SfIterativeFitCferr2Up");
	     checkEmptyBins(hclone_zjets_SfIterativeFitCferr2_up);
	     TH1F *hclone_zjets_SfIterativeFitCferr2_down = (TH1F*)hget_zjets_SfIterativeFitCferr2_down->Clone("h_zjets_SfIterativeFitCferr2Down");
	     checkEmptyBins(hclone_zjets_SfIterativeFitCferr2_down);
	     TH1F *hclone_zjets_Jes_up = (TH1F*)hget_zjets_Jes_up->Clone("h_zjets_JesUp");
	     checkEmptyBins(hclone_zjets_Jes_up);
	     TH1F *hclone_zjets_Jes_down = (TH1F*)hget_zjets_Jes_down->Clone("h_zjets_JesDown");
	     checkEmptyBins(hclone_zjets_Jes_down);
	     TH1F *hclone_zjets_Jer_up = (TH1F*)hget_zjets_Jer_up->Clone("h_zjets_JerUp");
	     checkEmptyBins(hclone_zjets_Jer_up);
	     TH1F *hclone_zjets_Jer_down = (TH1F*)hget_zjets_Jer_down->Clone("h_zjets_JerDown");
	     checkEmptyBins(hclone_zjets_Jer_down);

	     // wjets
   
	     TH1F *hclone_wjets = (TH1F*)hget_wjets->Clone("h_wjets");
	     checkEmptyBins(hclone_wjets);
	     TH1F *hclone_wjets_SfIterativeFitHfstats1_up = (TH1F*)hget_wjets_SfIterativeFitHfstats1_up->Clone("h_wjets_SfIterativeFitHfstats1Up");
	     checkEmptyBins(hclone_wjets_SfIterativeFitHfstats1_up);
	     TH1F *hclone_wjets_SfIterativeFitHfstats1_down = (TH1F*)hget_wjets_SfIterativeFitHfstats1_down->Clone("h_wjets_SfIterativeFitHfstats1Down");
	     checkEmptyBins(hclone_wjets_SfIterativeFitHfstats1_down);
	     TH1F *hclone_wjets_SfIterativeFitHfstats2_up = (TH1F*)hget_wjets_SfIterativeFitHfstats2_up->Clone("h_wjets_SfIterativeFitHfstats2Up");
	     checkEmptyBins(hclone_wjets_SfIterativeFitHfstats2_up);
	     TH1F *hclone_wjets_SfIterativeFitHfstats2_down = (TH1F*)hget_wjets_SfIterativeFitHfstats2_down->Clone("h_wjets_SfIterativeFitHfstats2Down");
	     checkEmptyBins(hclone_wjets_SfIterativeFitHfstats2_down);
	     TH1F *hclone_wjets_SfIterativeFitLfstats1_up = (TH1F*)hget_wjets_SfIterativeFitLfstats1_up->Clone("h_wjets_SfIterativeFitLfstats1Up");
	     checkEmptyBins(hclone_wjets_SfIterativeFitLfstats1_up);
	     TH1F *hclone_wjets_SfIterativeFitLfstats1_down = (TH1F*)hget_wjets_SfIterativeFitLfstats1_down->Clone("h_wjets_SfIterativeFitLfstats1Down");
	     checkEmptyBins(hclone_wjets_SfIterativeFitLfstats1_down);
	     TH1F *hclone_wjets_SfIterativeFitLfstats2_up = (TH1F*)hget_wjets_SfIterativeFitLfstats2_up->Clone("h_wjets_SfIterativeFitLfstats2Up");
	     checkEmptyBins(hclone_wjets_SfIterativeFitLfstats2_up);
	     TH1F *hclone_wjets_SfIterativeFitLfstats2_down = (TH1F*)hget_wjets_SfIterativeFitLfstats2_down->Clone("h_wjets_SfIterativeFitLfstats2Down");
	     checkEmptyBins(hclone_wjets_SfIterativeFitLfstats2_down);
	     TH1F *hclone_wjets_SfIterativeFitJes_up = (TH1F*)hget_wjets_SfIterativeFitJes_up->Clone("h_wjets_SfIterativeFitJesUp");
	     checkEmptyBins(hclone_wjets_SfIterativeFitJes_up);
	     TH1F *hclone_wjets_SfIterativeFitJes_down = (TH1F*)hget_wjets_SfIterativeFitJes_down->Clone("h_wjets_SfIterativeFitJesDown");
	     checkEmptyBins(hclone_wjets_SfIterativeFitJes_down);
	     TH1F *hclone_wjets_SfIterativeFitLf_up = (TH1F*)hget_wjets_SfIterativeFitLf_up->Clone("h_wjets_SfIterativeFitLfUp");
	     checkEmptyBins(hclone_wjets_SfIterativeFitLf_up);
	     TH1F *hclone_wjets_SfIterativeFitLf_down = (TH1F*)hget_wjets_SfIterativeFitLf_down->Clone("h_wjets_SfIterativeFitLfDown");
	     checkEmptyBins(hclone_wjets_SfIterativeFitLf_down);
	     TH1F *hclone_wjets_SfIterativeFitHf_up = (TH1F*)hget_wjets_SfIterativeFitHf_up->Clone("h_wjets_SfIterativeFitHfUp");
	     checkEmptyBins(hclone_wjets_SfIterativeFitHf_up);
	     TH1F *hclone_wjets_SfIterativeFitHf_down = (TH1F*)hget_wjets_SfIterativeFitHf_down->Clone("h_wjets_SfIterativeFitHfDown");
	     checkEmptyBins(hclone_wjets_SfIterativeFitHf_down);
	     TH1F *hclone_wjets_SfIterativeFitCferr1_up = (TH1F*)hget_wjets_SfIterativeFitCferr1_up->Clone("h_wjets_SfIterativeFitCferr1Up");
	     checkEmptyBins(hclone_wjets_SfIterativeFitCferr1_up);
	     TH1F *hclone_wjets_SfIterativeFitCferr1_down = (TH1F*)hget_wjets_SfIterativeFitCferr1_down->Clone("h_wjets_SfIterativeFitCferr1Down");
	     checkEmptyBins(hclone_wjets_SfIterativeFitCferr1_down);
	     TH1F *hclone_wjets_SfIterativeFitCferr2_up = (TH1F*)hget_wjets_SfIterativeFitCferr2_up->Clone("h_wjets_SfIterativeFitCferr2Up");
	     checkEmptyBins(hclone_wjets_SfIterativeFitCferr2_up);
	     TH1F *hclone_wjets_SfIterativeFitCferr2_down = (TH1F*)hget_wjets_SfIterativeFitCferr2_down->Clone("h_wjets_SfIterativeFitCferr2Down");
	     checkEmptyBins(hclone_wjets_SfIterativeFitCferr2_down);
	     TH1F *hclone_wjets_Jes_up = (TH1F*)hget_wjets_Jes_up->Clone("h_wjets_JesUp");
	     checkEmptyBins(hclone_wjets_Jes_up);
	     TH1F *hclone_wjets_Jes_down = (TH1F*)hget_wjets_Jes_down->Clone("h_wjets_JesDown");
	     checkEmptyBins(hclone_wjets_Jes_down);
	     TH1F *hclone_wjets_Jer_up = (TH1F*)hget_wjets_Jer_up->Clone("h_wjets_JerUp");
	     checkEmptyBins(hclone_wjets_Jer_up);
	     TH1F *hclone_wjets_Jer_down = (TH1F*)hget_wjets_Jer_down->Clone("h_wjets_JerDown");
	     checkEmptyBins(hclone_wjets_Jer_down);
	     
	     // other
   
	     TH1F *hclone_other = (TH1F*)hclone_zjets->Clone("h_other");
	     hclone_other->Add(hclone_wjets);
	     if( mergeZjetsWjetStop ) hclone_other->Add(hclone_stop);
	     if( mergeAll ) hclone_other->Add(hclone_ttbb);
	     if( mergeAll ) hclone_other->Add(hclone_ttcc);
	     if( mergeAll ) hclone_other->Add(hclone_ttlf);
	     
	     TH1F *hclone_other_SfIterativeFitHfstats1_up = (TH1F*)hclone_zjets_SfIterativeFitHfstats1_up->Clone("h_other_SfIterativeFitHfstats1Up");
	     hclone_other_SfIterativeFitHfstats1_up->Add(hclone_wjets_SfIterativeFitHfstats1_up);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitHfstats1_up->Add(hclone_stop_SfIterativeFitHfstats1_up);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats1_up->Add(hclone_ttbb_SfIterativeFitHfstats1_up);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats1_up->Add(hclone_ttcc_SfIterativeFitHfstats1_up);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats1_up->Add(hclone_ttlf_SfIterativeFitHfstats1_up);
	     TH1F *hclone_other_SfIterativeFitHfstats1_down = (TH1F*)hclone_zjets_SfIterativeFitHfstats1_down->Clone("h_other_SfIterativeFitHfstats1Down");
	     hclone_other_SfIterativeFitHfstats1_down->Add(hclone_wjets_SfIterativeFitHfstats1_down);   
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitHfstats1_down->Add(hclone_stop_SfIterativeFitHfstats1_down);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats1_down->Add(hclone_ttbb_SfIterativeFitHfstats1_down);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats1_down->Add(hclone_ttcc_SfIterativeFitHfstats1_down);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats1_down->Add(hclone_ttlf_SfIterativeFitHfstats1_down);
	     
	     TH1F *hclone_other_SfIterativeFitHfstats2_up = (TH1F*)hclone_zjets_SfIterativeFitHfstats2_up->Clone("h_other_SfIterativeFitHfstats2Up");
	     hclone_other_SfIterativeFitHfstats2_up->Add(hclone_wjets_SfIterativeFitHfstats2_up);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitHfstats2_up->Add(hclone_stop_SfIterativeFitHfstats2_up);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats2_up->Add(hclone_ttbb_SfIterativeFitHfstats2_up);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats2_up->Add(hclone_ttcc_SfIterativeFitHfstats2_up);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats2_up->Add(hclone_ttlf_SfIterativeFitHfstats2_up);
	     TH1F *hclone_other_SfIterativeFitHfstats2_down = (TH1F*)hclone_zjets_SfIterativeFitHfstats2_down->Clone("h_other_SfIterativeFitHfstats2Down");
	     hclone_other_SfIterativeFitHfstats2_down->Add(hclone_wjets_SfIterativeFitHfstats2_down);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitHfstats2_down->Add(hclone_stop_SfIterativeFitHfstats2_down);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats2_down->Add(hclone_ttbb_SfIterativeFitHfstats2_down);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats2_down->Add(hclone_ttcc_SfIterativeFitHfstats2_down);
	     if( mergeAll ) hclone_other_SfIterativeFitHfstats2_down->Add(hclone_ttlf_SfIterativeFitHfstats2_down);
	     
	     TH1F *hclone_other_SfIterativeFitLfstats1_up = (TH1F*)hclone_zjets_SfIterativeFitLfstats1_up->Clone("h_other_SfIterativeFitLfstats1Up");
	     hclone_other_SfIterativeFitLfstats1_up->Add(hclone_wjets_SfIterativeFitLfstats1_up);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitLfstats1_up->Add(hclone_stop_SfIterativeFitLfstats1_up);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats1_up->Add(hclone_ttbb_SfIterativeFitLfstats1_up);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats1_up->Add(hclone_ttcc_SfIterativeFitLfstats1_up);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats1_up->Add(hclone_ttlf_SfIterativeFitLfstats1_up);
	     TH1F *hclone_other_SfIterativeFitLfstats1_down = (TH1F*)hclone_zjets_SfIterativeFitLfstats1_down->Clone("h_other_SfIterativeFitLfstats1Down");
	     hclone_other_SfIterativeFitLfstats1_down->Add(hclone_wjets_SfIterativeFitLfstats1_down);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitLfstats1_down->Add(hclone_stop_SfIterativeFitLfstats1_down);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats1_down->Add(hclone_ttbb_SfIterativeFitLfstats1_down);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats1_down->Add(hclone_ttcc_SfIterativeFitLfstats1_down);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats1_down->Add(hclone_ttlf_SfIterativeFitLfstats1_down);
	     
	     TH1F *hclone_other_SfIterativeFitLfstats2_up = (TH1F*)hclone_zjets_SfIterativeFitLfstats2_up->Clone("h_other_SfIterativeFitLfstats2Up");
	     hclone_other_SfIterativeFitLfstats2_up->Add(hclone_wjets_SfIterativeFitLfstats2_up);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitLfstats2_up->Add(hclone_stop_SfIterativeFitLfstats2_up);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats2_up->Add(hclone_ttbb_SfIterativeFitLfstats2_up);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats2_up->Add(hclone_ttcc_SfIterativeFitLfstats2_up);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats2_up->Add(hclone_ttlf_SfIterativeFitLfstats2_up);
	     TH1F *hclone_other_SfIterativeFitLfstats2_down = (TH1F*)hclone_zjets_SfIterativeFitLfstats2_down->Clone("h_other_SfIterativeFitLfstats2Down");
	     hclone_other_SfIterativeFitLfstats2_down->Add(hclone_wjets_SfIterativeFitLfstats2_down);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitLfstats2_down->Add(hclone_stop_SfIterativeFitLfstats2_down);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats2_down->Add(hclone_ttbb_SfIterativeFitLfstats2_down);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats2_down->Add(hclone_ttcc_SfIterativeFitLfstats2_down);
	     if( mergeAll ) hclone_other_SfIterativeFitLfstats2_down->Add(hclone_ttlf_SfIterativeFitLfstats2_down);
	     
	     TH1F *hclone_other_SfIterativeFitJes_up = (TH1F*)hclone_zjets_SfIterativeFitJes_up->Clone("h_other_SfIterativeFitJesUp");
	     hclone_other_SfIterativeFitJes_up->Add(hclone_wjets_SfIterativeFitJes_up);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitJes_up->Add(hclone_stop_SfIterativeFitJes_up);
	     if( mergeAll ) hclone_other_SfIterativeFitJes_up->Add(hclone_ttbb_SfIterativeFitJes_up);
	     if( mergeAll ) hclone_other_SfIterativeFitJes_up->Add(hclone_ttcc_SfIterativeFitJes_up);
	     if( mergeAll ) hclone_other_SfIterativeFitJes_up->Add(hclone_ttlf_SfIterativeFitJes_up);
	     TH1F *hclone_other_SfIterativeFitJes_down = (TH1F*)hclone_zjets_SfIterativeFitJes_down->Clone("h_other_SfIterativeFitJesDown");
	     hclone_other_SfIterativeFitJes_down->Add(hclone_wjets_SfIterativeFitJes_down);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitJes_down->Add(hclone_stop_SfIterativeFitJes_down);
	     if( mergeAll ) hclone_other_SfIterativeFitJes_down->Add(hclone_ttbb_SfIterativeFitJes_down);
	     if( mergeAll ) hclone_other_SfIterativeFitJes_down->Add(hclone_ttcc_SfIterativeFitJes_down);
	     if( mergeAll ) hclone_other_SfIterativeFitJes_down->Add(hclone_ttlf_SfIterativeFitJes_down);
	     
	     TH1F *hclone_other_SfIterativeFitLf_up = (TH1F*)hclone_zjets_SfIterativeFitLf_up->Clone("h_other_SfIterativeFitLfUp");
	     hclone_other_SfIterativeFitLf_up->Add(hclone_wjets_SfIterativeFitLf_up);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitLf_up->Add(hclone_stop_SfIterativeFitLf_up);
	     if( mergeAll ) hclone_other_SfIterativeFitLf_up->Add(hclone_ttbb_SfIterativeFitLf_up);
	     if( mergeAll ) hclone_other_SfIterativeFitLf_up->Add(hclone_ttcc_SfIterativeFitLf_up);
	     if( mergeAll ) hclone_other_SfIterativeFitLf_up->Add(hclone_ttlf_SfIterativeFitLf_up);
	     TH1F *hclone_other_SfIterativeFitLf_down = (TH1F*)hclone_zjets_SfIterativeFitLf_down->Clone("h_other_SfIterativeFitLfDown");
	     hclone_other_SfIterativeFitLf_down->Add(hclone_wjets_SfIterativeFitLf_down);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitLf_down->Add(hclone_stop_SfIterativeFitLf_down);
	     if( mergeAll ) hclone_other_SfIterativeFitLf_down->Add(hclone_ttbb_SfIterativeFitLf_down);
	     if( mergeAll ) hclone_other_SfIterativeFitLf_down->Add(hclone_ttcc_SfIterativeFitLf_down);
	     if( mergeAll ) hclone_other_SfIterativeFitLf_down->Add(hclone_ttlf_SfIterativeFitLf_down);
	     
	     TH1F *hclone_other_SfIterativeFitHf_up = (TH1F*)hclone_zjets_SfIterativeFitHf_up->Clone("h_other_SfIterativeFitHfUp");
	     hclone_other_SfIterativeFitHf_up->Add(hclone_wjets_SfIterativeFitHf_up);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitHf_up->Add(hclone_stop_SfIterativeFitHf_up);
	     if( mergeAll ) hclone_other_SfIterativeFitHf_up->Add(hclone_ttbb_SfIterativeFitHf_up);
	     if( mergeAll ) hclone_other_SfIterativeFitHf_up->Add(hclone_ttcc_SfIterativeFitHf_up);
	     if( mergeAll ) hclone_other_SfIterativeFitHf_up->Add(hclone_ttlf_SfIterativeFitHf_up);
	     TH1F *hclone_other_SfIterativeFitHf_down = (TH1F*)hclone_zjets_SfIterativeFitHf_down->Clone("h_other_SfIterativeFitHfDown");
	     hclone_other_SfIterativeFitHf_down->Add(hclone_wjets_SfIterativeFitHf_down);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitHf_down->Add(hclone_stop_SfIterativeFitHf_down);
	     if( mergeAll ) hclone_other_SfIterativeFitHf_down->Add(hclone_ttbb_SfIterativeFitHf_down);
	     if( mergeAll ) hclone_other_SfIterativeFitHf_down->Add(hclone_ttcc_SfIterativeFitHf_down);
	     if( mergeAll ) hclone_other_SfIterativeFitHf_down->Add(hclone_ttlf_SfIterativeFitHf_down);
	     
	     TH1F *hclone_other_SfIterativeFitCferr1_up = (TH1F*)hclone_zjets_SfIterativeFitCferr1_up->Clone("h_other_SfIterativeFitCferr1Up");
	     hclone_other_SfIterativeFitCferr1_up->Add(hclone_wjets_SfIterativeFitCferr1_up);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitCferr1_up->Add(hclone_stop_SfIterativeFitCferr1_up);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr1_up->Add(hclone_ttbb_SfIterativeFitCferr1_up);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr1_up->Add(hclone_ttcc_SfIterativeFitCferr1_up);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr1_up->Add(hclone_ttlf_SfIterativeFitCferr1_up);
	     TH1F *hclone_other_SfIterativeFitCferr1_down = (TH1F*)hclone_zjets_SfIterativeFitCferr1_down->Clone("h_other_SfIterativeFitCferr1Down");
	     hclone_other_SfIterativeFitCferr1_down->Add(hclone_wjets_SfIterativeFitCferr1_down);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitCferr1_down->Add(hclone_stop_SfIterativeFitCferr1_down);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr1_down->Add(hclone_ttbb_SfIterativeFitCferr1_down);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr1_down->Add(hclone_ttcc_SfIterativeFitCferr1_down);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr1_down->Add(hclone_ttlf_SfIterativeFitCferr1_down);
	     
	     TH1F *hclone_other_SfIterativeFitCferr2_up = (TH1F*)hclone_zjets_SfIterativeFitCferr2_up->Clone("h_other_SfIterativeFitCferr2Up");
	     hclone_other_SfIterativeFitCferr2_up->Add(hclone_wjets_SfIterativeFitCferr2_up);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitCferr2_up->Add(hclone_stop_SfIterativeFitCferr2_up);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr2_up->Add(hclone_ttbb_SfIterativeFitCferr2_up);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr2_up->Add(hclone_ttcc_SfIterativeFitCferr2_up);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr2_up->Add(hclone_ttlf_SfIterativeFitCferr2_up);
	     TH1F *hclone_other_SfIterativeFitCferr2_down = (TH1F*)hclone_zjets_SfIterativeFitCferr2_down->Clone("h_other_SfIterativeFitCferr2Down");
	     hclone_other_SfIterativeFitCferr2_down->Add(hclone_wjets_SfIterativeFitCferr2_down);
	     if( mergeZjetsWjetStop ) hclone_other_SfIterativeFitCferr2_down->Add(hclone_stop_SfIterativeFitCferr2_down);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr2_down->Add(hclone_ttbb_SfIterativeFitCferr2_down);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr2_down->Add(hclone_ttcc_SfIterativeFitCferr2_down);
	     if( mergeAll ) hclone_other_SfIterativeFitCferr2_down->Add(hclone_ttlf_SfIterativeFitCferr2_down);

	     TH1F *hclone_other_Jes_up = (TH1F*)hclone_zjets_Jes_up->Clone("h_other_JesUp");
	     hclone_other_Jes_up->Add(hclone_wjets_Jes_up);
	     if( mergeZjetsWjetStop ) hclone_other_Jes_up->Add(hclone_stop_Jes_up);
	     if( mergeAll ) hclone_other_Jes_up->Add(hclone_ttbb_Jes_up);
	     if( mergeAll ) hclone_other_Jes_up->Add(hclone_ttcc_Jes_up);
	     if( mergeAll ) hclone_other_Jes_up->Add(hclone_ttlf_Jes_up);	     
	     TH1F *hclone_other_Jes_down = (TH1F*)hclone_zjets_Jes_down->Clone("h_other_JesDown");
	     hclone_other_Jes_down->Add(hclone_wjets_Jes_down);
	     if( mergeZjetsWjetStop ) hclone_other_Jes_down->Add(hclone_stop_Jes_down);
	     if( mergeAll ) hclone_other_Jes_down->Add(hclone_ttbb_Jes_down);
	     if( mergeAll ) hclone_other_Jes_down->Add(hclone_ttcc_Jes_down);
	     if( mergeAll ) hclone_other_Jes_down->Add(hclone_ttlf_Jes_down);

	     TH1F *hclone_other_Jer_up = (TH1F*)hclone_zjets_Jer_up->Clone("h_other_JerUp");
	     hclone_other_Jer_up->Add(hclone_wjets_Jer_up);
	     if( mergeZjetsWjetStop ) hclone_other_Jer_up->Add(hclone_stop_Jer_up);
	     if( mergeAll ) hclone_other_Jer_up->Add(hclone_ttbb_Jer_up);
	     if( mergeAll ) hclone_other_Jer_up->Add(hclone_ttcc_Jer_up);
	     if( mergeAll ) hclone_other_Jer_up->Add(hclone_ttlf_Jer_up);
	     TH1F *hclone_other_Jer_down = (TH1F*)hclone_zjets_Jer_down->Clone("h_other_JerDown");
	     hclone_other_Jer_down->Add(hclone_wjets_Jer_down);
	     if( mergeZjetsWjetStop ) hclone_other_Jer_down->Add(hclone_stop_Jer_down);
	     if( mergeAll ) hclone_other_Jer_down->Add(hclone_ttbb_Jer_down);
	     if( mergeAll ) hclone_other_Jer_down->Add(hclone_ttcc_Jer_down);
	     if( mergeAll ) hclone_other_Jer_down->Add(hclone_ttlf_Jer_down);

//   int nBins = 0;
//   double xBins[1000];
//   h_e_signal_default->Print("all");
//   std::cout << h_e_signal_default->GetXaxis()->GetNbins() << std::endl;
//   adjustHist(h_e_signal_default,nBins,xBins);
//   h = (TH1F*)h->Rebin(i-1,"",xBins);
//   std::cout << h_e_signal_default->GetXaxis()->GetNbins() << std::endl;
//   h_e_signal_default->Print("all");
   
	     fout->Write();
	     fout->Close();
	  }
     }
}

void checkEmptyBins(TH1F *h)
{
   int nBins = h->GetXaxis()->GetNbins();
   
   for(int ib=1;ib<=nBins;ib++)
     {
	float v = h->GetBinContent(ib);
	if( v < 10E-10 )
	  {
	     h->SetBinContent(ib,v);
	     h->SetBinError(ib,v);
	  }	
     }   
}

/*void adjustHist(TH1F *h,int &iBins,double *xBins)
{
   int nBins = h->GetXaxis()->GetNbins();
   int x1 = 1;
   int x2 = nBins;
     
   for(int ib=1;ib<=nBins;ib++)
     {
	float v = h->GetBinContent(ib);
	if( v == 0 ) x1 = ib;
	else break;
     }   
   for(int ib=x1;ib<=nBins;ib++)
     {
	float v = h->GetBinContent(ib);
	if( v == 0 )
	  {
	     x2 = ib;
	     break;
	  }	
     }
   
   xBins[0] = h->GetBinLowEdge(1);
   int i = 1;
   for(int ib=x1;ib<=x2;ib++)
     {
	float edge = h->GetBinLowEdge(ib);
	if( x1 != 1 )
	  {	     
	     xBins[i] = edge;
	     i++;
	  }	
     }   

   iBins = i-1;
}*/
