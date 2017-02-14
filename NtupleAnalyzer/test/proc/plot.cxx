#include "PlotStyle.h"
#include "ratioSig.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "THStack.h"
#include "TMath.h"
#include "TFile.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"

#include <vector>
#include <iostream>

double sigScale = 1;

int sigType = 0; // all(0) singleTopHut(1) singleTopHct(2) ttbarHut(3) ttbarHct(4) singleTop(5) ttbar(6)

void addbin(TH1F*);

void totSys(TH1F*,TH1F*,TH1F*);
void combSys(TH1F*,TH1F**,TH1F**,TH1F*,TH1F*,int);
void combSysLinear(std::vector<TH1F*>,std::vector<TH1F*>,std::vector<TH1F*>,TH1F*,TH1F*,TH1F*);
TGraphAsymmErrors* makeErrorBand(TH1F*,TH1F*,TH1F*);
void removeMCNeg(TH1F*);

int main(int argc, char *argv[])
{
   if( argc < 2 )
     {
	std::cout << "Usage: ./plot [toy name]" << std::endl;
	exit(1);
     }
   
   std::string toyName = std::string(argv[1]);
   
   SetPlotStyle();

   gStyle->SetOptFit();   

   std::string fname = "hist"+toyName+".root";
   TFile *fout = new TFile(fname.c_str(),"RECREATE");
   
   std::vector<std::string> data;
   
   std::vector<std::string> ttbar;
   std::vector<std::string> stop;
   std::vector<std::string> higgs;
   std::vector<std::string> thq;
   std::vector<std::string> tzq;
   std::vector<std::string> wjets;
   std::vector<std::string> zjets;
   
   std::vector<std::string> sig_hut_stop;
   std::vector<std::string> sig_hct_stop;
   std::vector<std::string> sig_gut;
   std::vector<std::string> sig_gct;

   std::vector<std::string> sig_hut_ttbar;
   std::vector<std::string> sig_hct_ttbar;
   
   std::vector<std::string> sig_hut;
   std::vector<std::string> sig_hct;
   
   data.push_back("SingleElectron_Run2016B_23Sep2016_v3_MINIAOD");
   data.push_back("SingleElectron_Run2016C_23Sep2016_v1_MINIAOD");
   data.push_back("SingleElectron_Run2016D_23Sep2016_v1_MINIAOD");
   data.push_back("SingleElectron_Run2016E_23Sep2016_v1_MINIAOD");
   data.push_back("SingleElectron_Run2016F_23Sep2016_v1_MINIAOD");
   data.push_back("SingleElectron_Run2016G_23Sep2016_v1_MINIAOD");
   data.push_back("SingleElectron_Run2016H_PromptReco_v2_MINIAOD");
   data.push_back("SingleElectron_Run2016H_PromptReco_v3_MINIAOD");

   data.push_back("SingleMuon_Run2016B_23Sep2016_v3_MINIAOD");
   data.push_back("SingleMuon_Run2016C_23Sep2016_v1_MINIAOD");
   data.push_back("SingleMuon_Run2016D_23Sep2016_v1_MINIAOD");
   data.push_back("SingleMuon_Run2016E_23Sep2016_v1_MINIAOD");
   data.push_back("SingleMuon_Run2016F_23Sep2016_v1_MINIAOD");
   data.push_back("SingleMuon_Run2016G_23Sep2016_v1_MINIAOD");
   data.push_back("SingleMuon_Run2016H_PromptReco_v2_MINIAOD");
   data.push_back("SingleMuon_Run2016H_PromptReco_v3_MINIAOD");
   
   ttbar.push_back("TT_TuneCUETP8M2T4_13TeV-powheg-pythia8");
   
   stop.push_back("ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1");
   stop.push_back("ST_t-channel_antitop_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin");
   stop.push_back("ST_t-channel_top_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin");
   stop.push_back("ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4");
   stop.push_back("ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4");
   
//   ttv.push_back("ttWJets_13TeV_madgraphMLM");
//   ttv.push_back("ttZJets_13TeV_madgraphMLM");
   
   wjets.push_back("WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");

   zjets.push_back("DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8");
   zjets.push_back("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8");
   
   sig_hut_stop.push_back("ST_FCNC-TH_Tleptonic_HTobb_eta_hut-MadGraph5-pythia8");
   
   sig_hct_stop.push_back("ST_FCNC-TH_Tleptonic_HTobb_eta_hct-MadGraph5-pythia8");
   
   sig_hut_ttbar.push_back("TT_FCNC-TtoHJ_aTleptonic_HTobb_eta_hut-MadGraph5-pythia8");
   sig_hut_ttbar.push_back("TT_FCNC-aTtoHJ_Tleptonic_HTobb_eta_hut-MadGraph5-pythia8");
   
   sig_hct_ttbar.push_back("TT_FCNC-T2HJ_aTleptonic_HTobb_eta_hct-MadGraph5-pythia8");
   sig_hct_ttbar.push_back("TT_FCNC-aTtoHJ_Tleptonic_HTobb_eta_hct-MadGraph5-pythia8");

   for(int i=0;i<sig_hut_stop.size();i++)
     sig_hut.push_back(sig_hut_stop.at(i));
   for(int i=0;i<sig_hut_ttbar.size();i++)
     sig_hut.push_back(sig_hut_ttbar.at(i));

   for(int i=0;i<sig_hct_stop.size();i++)
     sig_hct.push_back(sig_hct_stop.at(i));
   for(int i=0;i<sig_hct_ttbar.size();i++)
     sig_hct.push_back(sig_hct_ttbar.at(i));
   
   const int data_n = data.size();
   const int ttbar_n = ttbar.size();
   const int stop_n = stop.size();
   const int zjets_n = zjets.size();
   const int wjets_n = wjets.size();
   const int sig_hut_n = sig_hut.size();
   const int sig_hut_stop_n = sig_hut_stop.size();
   const int sig_hut_ttbar_n = sig_hut_ttbar.size();
   const int sig_hct_stop_n = sig_hct_stop.size();
   const int sig_hct_ttbar_n = sig_hct_ttbar.size();

   float ksig = 1;
   
//   const int nvar = 31;
//   const int nvar = 35;
   const int nvar = 2;
   std::string var[nvar] =
     {
//	"PassSel5",
//	"MVAHutST",
//	"MVAHctST",
//	"MVAHutTT",
//	"MVAHctTT",
//	"MVAHut",
//	"MVAHct",
	"MVAHutMAX",
	"MVAHctMAX"

/*	"LepCharge",
	"LepPt",
	"LepEta",
	"LepPhi",*/
	
/*	"HiggsMass_TOPHLEPBB",
	"HiggsPt_TOPHLEPBB",
        "HiggsEta_TOPHLEPBB",
	"HiggsPhi_TOPHLEPBB",
	"TopLepMass_TOPHLEPBB",
	"TopLepPt_TOPHLEPBB",
	"TopLepEta_TOPHLEPBB",
	"TopLepPhi_TOPHLEPBB",
	"HiggsBJet1Pt_TOPHLEPBB",
	"HiggsBJet2Pt_TOPHLEPBB",
	"TopLepBJetPt_TOPHLEPBB",
	"HiggsBJet1Eta_TOPHLEPBB",
	"HiggsBJet2Eta_TOPHLEPBB",
	"TopLepBJetEta_TOPHLEPBB",
	"HiggsBJet1Phi_TOPHLEPBB",
	"HiggsBJet2Phi_TOPHLEPBB",
	"TopLepBJetPhi_TOPHLEPBB",
	"HiggsBJet1E_TOPHLEPBB",
	"HiggsBJet2E_TOPHLEPBB",
	"TopLepBJetE_TOPHLEPBB",
	"HiggsBJet1CSVv2_TOPHLEPBB",
	"HiggsBJet2CSVv2_TOPHLEPBB",
	"TopLepBJetCSVv2_TOPHLEPBB",
	"TopLepHiggsDr_TOPHLEPBB",
	"HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",
	"MVA_TOPHLEPBB"*/

/*	"HiggsMass_TOPTOPLEPHBB", // 31
	"TopLepMass_TOPTOPLEPHBB",
	"HiggsPt_TOPTOPLEPHBB",
        "HiggsEta_TOPTOPLEPHBB",
	"HiggsPhi_TOPTOPLEPHBB",
	"TopLepPt_TOPTOPLEPHBB",
	"TopLepEta_TOPTOPLEPHBB",
	"TopLepPhi_TOPTOPLEPHBB",
	"HiggsBJet1Pt_TOPTOPLEPHBB",
	"HiggsBJet2Pt_TOPTOPLEPHBB",
	"TopLepBJetPt_TOPTOPLEPHBB",
	"TopHadNonBJetPt_TOPTOPLEPHBB",
	"HiggsBJet1Eta_TOPTOPLEPHBB",
	"HiggsBJet2Eta_TOPTOPLEPHBB",
	"TopLepBJetEta_TOPTOPLEPHBB",
	"TopHadNonBJetEta_TOPTOPLEPHBB",
	"HiggsBJet1Phi_TOPTOPLEPHBB",
	"HiggsBJet2Phi_TOPTOPLEPHBB",
	"TopLepBJetPhi_TOPTOPLEPHBB",
	"TopHadNonBJetPhi_TOPTOPLEPHBB",
	"HiggsBJet1E_TOPTOPLEPHBB",
	"HiggsBJet2E_TOPTOPLEPHBB",
	"TopLepBJetE_TOPTOPLEPHBB",
	"TopHadNonBJetE_TOPTOPLEPHBB",
	"HiggsBJet1CSVv2_TOPTOPLEPHBB",
	"HiggsBJet2CSVv2_TOPTOPLEPHBB",
	"TopLepBJetCSVv2_TOPTOPLEPHBB",
	"TopHadNonBJetCSVv2_TOPTOPLEPHBB",
	"TopLepHiggsDr_TOPTOPLEPHBB",
	"HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",
	"MVA_TOPTOPLEPHBB"*/

/*	"TopHadWMass_TOPTOPLEPHAD", // 35
	"TopLepMass_TOPTOPLEPHAD",
	"TopHadMass_TOPTOPLEPHAD",
	"TopHadWPt_TOPTOPLEPHAD",
        "TopHadWEta_TOPTOPLEPHAD",
	"TopHadWPhi_TOPTOPLEPHAD",
	"TopLepPt_TOPTOPLEPHAD",
	"TopLepEta_TOPTOPLEPHAD",
	"TopLepPhi_TOPTOPLEPHAD",
	"TopHadPt_TOPTOPLEPHAD",
	"TopHadEta_TOPTOPLEPHAD",
	"TopHadPhi_TOPTOPLEPHAD",
	"TopHadWNonBJet1Pt_TOPTOPLEPHAD",
	"TopHadWNonBJet2Pt_TOPTOPLEPHAD",
	"TopLepBJetPt_TOPTOPLEPHAD",
	"TopHadBJetPt_TOPTOPLEPHAD",
	"TopHadWNonBJet1Eta_TOPTOPLEPHAD",
	"TopHadWNonBJet2Eta_TOPTOPLEPHAD",
	"TopLepBJetEta_TOPTOPLEPHAD",
	"TopHadBJetEta_TOPTOPLEPHAD",
	"TopHadWNonBJet1Phi_TOPTOPLEPHAD",
	"TopHadWNonBJet2Phi_TOPTOPLEPHAD",
	"TopLepBJetPhi_TOPTOPLEPHAD",
	"TopHadBJetPhi_TOPTOPLEPHAD",
	"TopHadWNonBJet1E_TOPTOPLEPHAD",
	"TopHadWNonBJet2E_TOPTOPLEPHAD",
	"TopLepBJetE_TOPTOPLEPHAD",
	"TopHadBJetE_TOPTOPLEPHAD",
	"TopHadWNonBJet1CSVv2_TOPTOPLEPHAD",
	"TopHadWNonBJet2CSVv2_TOPTOPLEPHAD",
	"TopLepBJetCSVv2_TOPTOPLEPHAD",
	"TopHadBJetCSVv2_TOPTOPLEPHAD",
	"TopLepTopHadDr_TOPTOPLEPHAD",
	"TopHadWNonBJet1TopHadWNonBJet2Dr_TOPTOPLEPHAD",
	"MVA_TOPTOPLEPHAD"*/
     };   

   const int nsys = 11;
   std::string sys[nsys] =
     {
	"SfIterativeFitJes",
	"SfIterativeFitLf",
	"SfIterativeFitHf",
	"SfIterativeFitHfstats1",
	"SfIterativeFitHfstats2",
	"SfIterativeFitLfstats1",
	"SfIterativeFitLfstats2",
	"SfIterativeFitCferr1",
	"SfIterativeFitCferr2",
	"Jes",
	"Jer"
     };

   bool norm[nsys] =
     {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
     };
   
   std::string xtit[nvar] =
     {
//	"",
//	"MVA Hut ST",
//	"MVA Hct ST",
//	"MVA Hut TT",
//	"MVA Hct TT",
//	"MVA Hut 2D bins",
//	"MVA Hct 2D bins",
	"MVA Hut",
	"MVA Hct"

/*	"lepton charge",
	"p_{T}_{lepton} [GeV]",
	"#eta_{lepton}",
	"#phi_{lepton}",*/
	
/*	"m_{H} [GeV]",
	"p_{T}_{H} [GeV]",
	"#eta_{H}",
	"#phi_{H}",
        "m_{TopLep} [GeV]",
	"p_{T}_{TopLep} [GeV]",
	"#eta_{TopLep}",
	"#phi_{TopLep}",
	"p_{T}_{b_{H1}} [GeV]",
	"p_{T}_{b_{H2}} [GeV]",
	"p_{T}_{b_{TopLep}} [GeV]",
	"#eta_{b_{H1}}",
	"#eta_{b_{H2}}",
	"#eta_{b_{TopLep}}",
	"#phi_{b_{H1}}",
	"#phi_{b_{H2}}",
	"#phi_{b_{TopLep}}",
	"E_{b_{H1}} [GeV]",
	"E_{b_{H2}} [GeV]",
	"E_{b_{TopLep}} [GeV]",
	"b_{H1} CSVv2",
	"b_{H2} CSVv2",
	"b_{TopLep} CSVv2",
	"#Delta R (TopLep,H)",
	"#Delta R (b_{H1},b_{H2})",
	"bMVA TopHLepbb"*/

/*	"m_{H} [GeV]",
	"m_{TopLep} [GeV]",
	"p_{T}_{H} [GeV]",
        "#eta_{H}",
	"#phi_{H}",
	"p_{T}_{TopLep} [GeV]",
	"#eta_{TopLep}",
	"#phi_{TopLep}",
	"p_{T}_{b_{H1}} [GeV]",
	"p_{T}_{b_{H2}} [GeV]",
	"p_{T}_{b_{TopLep}} [GeV]",
	"p_{T}_{j_{TopHad}} [GeV]",
	"#eta_{b_{H1}}",
	"#eta_{b_{H2}}",
	"#eta_{b_{TopLep}}",
	"#eta_{j_{TopHad}}",
	"#phi_{b_{H1}}",
	"#phi_{b_{H2}}",
	"#phi_{b_{TopLep}}",
	"#phi_{j_{TopHad}}",
	"E_{b_{H1}}",
	"E_{b_{H2}}",
	"E_{b_{TopLep}}",
	"E_{j_{TopHad}}",
	"b_{H1} CSVv2",
	"b_{H2} CSVv2",
	"b_{TopLep} CSVv2",
	"j_{TopHad} CSVv2",
	"#Delta R (TopLep,H)",
	"#Delta R (b_{H1},b_{H2})",
	"bMVA TopTopLepHbb"*/

/*	"m_{WHad} [GeV]",
	"m_{TopLep} [GeV]",
	"m_{TopHad} [GeV]",
	"p_{T}_{WHad} [GeV]",
        "#eta_{WHad}",
	"#phi_{WHad}",
	"p_{T}_{TopLep} [GeV]",
	"#eta_{TopLep}",
	"#phi_{TopLep}",
	"p_{T}_{TopHad} [GeV]",
	"#eta_{TopHad}",
	"#phi_{TopHad}",
	"p_{T}_{j_{WHad1}} [GeV]",
	"p_{T}_{j_{WHad2}} [GeV]",
	"p_{T}_{b_{TopLep}} [GeV]",
	"p_{T}_{b_{TopHad}} [GeV]",
	"#eta_{j_{WHad1}}",
	"#eta_{j_{WHad2}}",
	"#eta_{b_{TopLep}}",
	"#eta_{b_{TopHad}}",
	"#phi_{j_{WHad1}}",
	"#phi_{j_{WHad2}}",
	"#phi_{b_{TopLep}}",
	"#phi_{b_{TopHad}}",
	"E_{j_{WHad1}}",
	"E_{j_{WHad2}}",
	"E_{b_{TopLep}}",
	"E_{b_{TopHad}}",
	"j_{WHad1} CSVv2",
	"j_{WHad2} CSVv2",
	"b_{TopLep} CSVv2",
	"b_{TopHad} CSVv2",
	"#Delta R (TopLep,TopHad)",
	"#Delta R (j_{WHad1},j_{WHad2})",
	"bMVA TopTopLepHad"*/
     };   
   
   const int nchan = 1;
   std::string chan[nchan] = 
     {
	"all"
//	"e"
//	"m"
     };   

   const int nsel = 6;
   std::string sel[nsel] =
     {
//	"b0j3",
//	"b0j4",
//	"b1j3",
//	"b1j4",
	"b2j3",
	"b2j4",
	"b3j3",
	"b3j4",
	"b4j4",
	"ALL"
     };   
   
   std::string hname[100000];
   std::string hname_ttbb[100000];
   std::string hname_ttcc[100000];
   std::string hname_ttlf[100000];
   int chanid[100000];
   int varid[100000];
   int selid[100000];
   
   int idx = 0;
   for(int iv=0;iv<nvar;iv++)
     {
	for(int ic=0;ic<nchan;ic++)
	  {
/*	     if( iv == 0 )
	       {
		  hname[idx] = "h_"+var[iv]+"_"+chan[ic]+"_ALL_ALL";
		  hname_ttbb[idx] = "h_"+var[iv]+"_"+chan[ic]+"_ttbb";
		  hname_ttcc[idx] = "h_"+var[iv]+"_"+chan[ic]+"_ttcc";
		  hname_ttlf[idx] = "h_"+var[iv]+"_"+chan[ic]+"_ttlf";
		  varid[idx] = iv;
		  chanid[idx] = ic;
		  idx++;
		  continue;		  
	       }*/
	     for(int is=0;is<nsel;is++)
	       {
		  hname[idx] = "h_"+var[iv]+"_"+chan[ic]+"_"+sel[is]+"_ALL";
		  hname_ttbb[idx] = "h_"+var[iv]+"_"+chan[ic]+"_"+sel[is]+"_ttbb";
		  hname_ttcc[idx] = "h_"+var[iv]+"_"+chan[ic]+"_"+sel[is]+"_ttcc";
		  hname_ttlf[idx] = "h_"+var[iv]+"_"+chan[ic]+"_"+sel[is]+"_ttlf";
		  varid[idx] = iv;
		  chanid[idx] = ic;
		  selid[idx] = is;
		  idx++;
	       }
	  }	
     }
   const int hn = idx;

   TH1F *h_data[hn];
   TFile *f_data[data_n];
   
   TH1F *h_ttbar[hn]; TH1F *h_ttbar_up[nsys][hn]; TH1F *h_ttbar_down[nsys][hn];
   TH1F *h_ttbb[hn]; TH1F *h_ttbb_up[nsys][hn]; TH1F *h_ttbb_down[nsys][hn];
   TH1F *h_ttcc[hn]; TH1F *h_ttcc_up[nsys][hn]; TH1F *h_ttcc_down[nsys][hn];
   TH1F *h_ttlf[hn]; TH1F *h_ttlf_up[nsys][hn]; TH1F *h_ttlf_down[nsys][hn];
   TFile *f_ttbar[ttbar_n];   

   TH1F *h_stop[hn]; TH1F *h_stop_up[nsys][hn]; TH1F *h_stop_down[nsys][hn];
   TFile *f_stop[stop_n];   
   
   TH1F *h_zjets[hn]; TH1F *h_zjets_up[nsys][hn]; TH1F *h_zjets_down[nsys][hn];
   TFile *f_zjets[zjets_n]; 

   TH1F *h_wjets[hn]; TH1F *h_wjets_up[nsys][hn]; TH1F *h_wjets_down[nsys][hn];
   TFile *f_wjets[wjets_n];   
   
   TH1F *h_sig_hut[hn]; TH1F *h_sig_hut_up[nsys][hn]; TH1F *h_sig_hut_down[nsys][hn];
   TFile *f_sig_hut[sig_hut_n];

   TH1F *h_sig_hut_stop[hn]; TH1F *h_sig_hut_stop_up[nsys][hn]; TH1F *h_sig_hut_stop_down[nsys][hn];
   TFile *f_sig_hut_stop[sig_hut_stop_n];

   TH1F *h_sig_hut_ttbar[hn]; TH1F *h_sig_hut_ttbar_up[nsys][hn]; TH1F *h_sig_hut_ttbar_down[nsys][hn];
   TFile *f_sig_hut_ttbar[sig_hut_ttbar_n];
   
   TH1F *h_sig_hct_stop[hn]; TH1F *h_sig_hct_stop_up[nsys][hn]; TH1F *h_sig_hct_stop_down[nsys][hn];
   TFile *f_sig_hct_stop[sig_hct_stop_n];
   
   TH1F *h_sig_hct_ttbar[hn]; TH1F *h_sig_hct_ttbar_up[nsys][hn]; TH1F *h_sig_hct_ttbar_down[nsys][hn];
   TFile *f_sig_hct_ttbar[sig_hct_ttbar_n];

   // Read histograms

   for(int i=0;i<data_n;i++)
     {	
	std::string fname = "../hist"+toyName+"_MERGED/"+data[i]+".root";
	f_data[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {
	     std::string hname_clone = hname[ih]+"_DATA_clone";

	     TH1F *h = (TH1F*)f_data[i]->Get(hname[ih].c_str());
	     if( i == 0 )
	       {
		  fout->cd();
		  h_data[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_data[ih]->Add(h);
	       }	
	  }
     }
   
   gDirectory->cd(); for(int i=0;i<data_n;i++) f_data[i]->Close();

   for(int i=0;i<ttbar_n;i++)
     {	
	std::string fname = "../hist"+toyName+"_MERGED/"+ttbar[i]+".root";
	f_ttbar[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {	     
	     std::string hname_clone = hname[ih]+"_ttbar_clone";
	     TH1F *h = (TH1F*)f_ttbar[i]->Get(hname[ih].c_str());
	     std::string hname_ttbb_clone = hname_ttbb[ih]+"_ttbb_clone";
	     TH1F *httbb = (TH1F*)f_ttbar[i]->Get(hname_ttbb[ih].c_str());
	     std::string hname_ttcc_clone = hname_ttcc[ih]+"_ttcc_clone";
	     TH1F *httcc = (TH1F*)f_ttbar[i]->Get(hname_ttcc[ih].c_str());
	     std::string hname_ttlf_clone = hname_ttlf[ih]+"_ttlf_clone";
	     TH1F *httlf = (TH1F*)f_ttbar[i]->Get(hname_ttlf[ih].c_str());
	     
	     if( i == 0 )
	       {
		  fout->cd();
		  h_ttbar[ih] = (TH1F*)h->Clone(hname_clone.c_str());
		  h_ttbb[ih] = (TH1F*)httbb->Clone(hname_ttbb_clone.c_str());
		  h_ttcc[ih] = (TH1F*)httcc->Clone(hname_ttcc_clone.c_str());
		  h_ttlf[ih] = (TH1F*)httlf->Clone(hname_ttlf_clone.c_str());
	       }
	     else
	       {
		  h_ttbar[ih]->Add(h);
		  h_ttbb[ih]->Add(httbb);
		  h_ttcc[ih]->Add(httcc);
		  h_ttlf[ih]->Add(httlf);
	       }

	     for(int is=0;is<nsys;is++)
	       {
		  std::string hname_sys_up = hname[ih]+"_"+sys[is]+"_Up";
		  std::string hname_sys_up_clone = hname_sys_up+"_ttbar_clone";
		  TH1F *h_sys_up = (TH1F*)f_ttbar[i]->Get(hname_sys_up.c_str());
		  std::string hname_sys_down = hname[ih]+"_"+sys[is]+"_Down";
		  std::string hname_sys_down_clone = hname_sys_down+"_ttbar_clone";
		  TH1F *h_sys_down = (TH1F*)f_ttbar[i]->Get(hname_sys_down.c_str());

		  std::string hname_ttbb_sys_up = hname_ttbb[ih]+"_"+sys[is]+"_Up";
		  std::string hname_ttbb_sys_up_clone = hname_ttbb_sys_up+"_ttbb_clone";
		  TH1F *h_ttbb_sys_up = (TH1F*)f_ttbar[i]->Get(hname_ttbb_sys_up.c_str());
		  std::string hname_ttbb_sys_down = hname_ttbb[ih]+"_"+sys[is]+"_Down";
		  std::string hname_ttbb_sys_down_clone = hname_ttbb_sys_down+"_ttbb_clone";
		  TH1F *h_ttbb_sys_down = (TH1F*)f_ttbar[i]->Get(hname_ttbb_sys_down.c_str());
		  
		  std::string hname_ttcc_sys_up = hname_ttcc[ih]+"_"+sys[is]+"_Up";
		  std::string hname_ttcc_sys_up_clone = hname_ttcc_sys_up+"_ttcc_clone";
		  TH1F *h_ttcc_sys_up = (TH1F*)f_ttbar[i]->Get(hname_ttcc_sys_up.c_str());
		  std::string hname_ttcc_sys_down = hname_ttcc[ih]+"_"+sys[is]+"_Down";
		  std::string hname_ttcc_sys_down_clone = hname_ttcc_sys_down+"_ttcc_clone";
		  TH1F *h_ttcc_sys_down = (TH1F*)f_ttbar[i]->Get(hname_ttcc_sys_down.c_str());
		  
		  std::string hname_ttlf_sys_up = hname_ttlf[ih]+"_"+sys[is]+"_Up";
		  std::string hname_ttlf_sys_up_clone = hname_ttlf_sys_up+"_ttlf_clone";
		  TH1F *h_ttlf_sys_up = (TH1F*)f_ttbar[i]->Get(hname_ttlf_sys_up.c_str());
		  std::string hname_ttlf_sys_down = hname_ttlf[ih]+"_"+sys[is]+"_Down";
		  std::string hname_ttlf_sys_down_clone = hname_ttlf_sys_down+"_ttlf_clone";
		  TH1F *h_ttlf_sys_down = (TH1F*)f_ttbar[i]->Get(hname_ttlf_sys_down.c_str());
		       
		  if( i == 0 )
		    {
		       fout->cd();
		       h_ttbar_up[is][ih] = (TH1F*)h_sys_up->Clone(hname_sys_up_clone.c_str());
		       h_ttbar_down[is][ih] = (TH1F*)h_sys_down->Clone(hname_sys_down_clone.c_str());
		       h_ttbb_up[is][ih] = (TH1F*)h_ttbb_sys_up->Clone(hname_ttbb_sys_up_clone.c_str());
		       h_ttbb_down[is][ih] = (TH1F*)h_ttbb_sys_down->Clone(hname_ttbb_sys_down_clone.c_str());
		       h_ttcc_up[is][ih] = (TH1F*)h_ttcc_sys_up->Clone(hname_ttcc_sys_up_clone.c_str());
		       h_ttcc_down[is][ih] = (TH1F*)h_ttcc_sys_down->Clone(hname_ttcc_sys_down_clone.c_str());
		       h_ttlf_up[is][ih] = (TH1F*)h_ttlf_sys_up->Clone(hname_ttlf_sys_up_clone.c_str());
		       h_ttlf_down[is][ih] = (TH1F*)h_ttlf_sys_down->Clone(hname_ttlf_sys_down_clone.c_str());
		    }
		  else
		    {
		       h_ttbar_up[is][ih]->Add(h_sys_up);
		       h_ttbar_down[is][ih]->Add(h_sys_down);
		       h_ttbb_up[is][ih]->Add(h_ttbb_sys_up);
		       h_ttbb_down[is][ih]->Add(h_ttbb_sys_down);
		       h_ttcc_up[is][ih]->Add(h_ttcc_sys_up);
		       h_ttcc_down[is][ih]->Add(h_ttcc_sys_down);
		       h_ttlf_up[is][ih]->Add(h_ttlf_sys_up);
		       h_ttlf_down[is][ih]->Add(h_ttlf_sys_down);
		    }
	       }
	  }	
     }
   
   gDirectory->cd(); for(int i=0;i<ttbar_n;i++) f_ttbar[i]->Close();

   for(int i=0;i<zjets_n;i++)
     {	
	std::string fname = "../hist"+toyName+"_MERGED/"+zjets[i]+".root";
	f_zjets[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {
	     std::string hname_clone = hname[ih]+"_zjets_clone";
	     TH1F *h = (TH1F*)f_zjets[i]->Get(hname[ih].c_str());
	     
	     if( i == 0 )
	       {
		  fout->cd();
		  h_zjets[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_zjets[ih]->Add(h);
	       }

	     for(int is=0;is<nsys;is++)
	       {
		  std::string hname_sys_up = hname[ih]+"_"+sys[is]+"_Up";
		  std::string hname_sys_up_clone = hname_sys_up+"_zjets_clone";
		  TH1F *h_sys_up = (TH1F*)f_zjets[i]->Get(hname_sys_up.c_str());
		  std::string hname_sys_down = hname[ih]+"_"+sys[is]+"_Down";
		  std::string hname_sys_down_clone = hname_sys_down+"_zjets_clone";
		  TH1F *h_sys_down = (TH1F*)f_zjets[i]->Get(hname_sys_down.c_str());
		  
		  if( i == 0 )
		    {
		       fout->cd();
		       h_zjets_up[is][ih] = (TH1F*)h_sys_up->Clone(hname_sys_up_clone.c_str());
		       h_zjets_down[is][ih] = (TH1F*)h_sys_down->Clone(hname_sys_down_clone.c_str());
		    }
		  else
		    {
		       h_zjets_up[is][ih]->Add(h_sys_up);
		       h_zjets_down[is][ih]->Add(h_sys_down);
		    }
	       }
	  }	       
     }
   
   gDirectory->cd(); for(int i=0;i<zjets_n;i++) f_zjets[i]->Close();

   for(int i=0;i<wjets_n;i++)
     {	
	std::string fname = "../hist"+toyName+"_MERGED/"+wjets[i]+".root";
	f_wjets[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {	     
	     std::string hname_clone = hname[ih]+"_wjets_clone";
	     TH1F *h = (TH1F*)f_wjets[i]->Get(hname[ih].c_str());
	     
	     if( i == 0 )
	       {
		  fout->cd();
		  h_wjets[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_wjets[ih]->Add(h);
	       }

	     for(int is=0;is<nsys;is++)
	       {
		  std::string hname_sys_up = hname[ih]+"_"+sys[is]+"_Up";
		  std::string hname_sys_up_clone = hname_sys_up+"_wjets_clone";
		  TH1F *h_sys_up = (TH1F*)f_wjets[i]->Get(hname_sys_up.c_str());
		  std::string hname_sys_down = hname[ih]+"_"+sys[is]+"_Down";
		  std::string hname_sys_down_clone = hname_sys_down+"_wjets_clone";
		  TH1F *h_sys_down = (TH1F*)f_wjets[i]->Get(hname_sys_down.c_str());
		  
		  if( i == 0 )
		    {
		       fout->cd();
		       h_wjets_up[is][ih] = (TH1F*)h_sys_up->Clone(hname_sys_up_clone.c_str());
		       h_wjets_down[is][ih] = (TH1F*)h_sys_down->Clone(hname_sys_down_clone.c_str());
		    }
		  else
		    {
		       h_wjets_up[is][ih]->Add(h_sys_up);
		       h_wjets_down[is][ih]->Add(h_sys_down);
		    }
	       }
	  }
     }
   
   gDirectory->cd(); for(int i=0;i<wjets_n;i++) f_wjets[i]->Close();

   for(int i=0;i<stop_n;i++)
     {	
	std::string fname = "../hist"+toyName+"_MERGED/"+stop[i]+".root";
	f_stop[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {	     
	     std::string hname_clone = hname[ih]+"_stop_clone";
	     TH1F *h = (TH1F*)f_stop[i]->Get(hname[ih].c_str());
	     
	     if( i == 0 )
	       {
		  fout->cd();
		  h_stop[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_stop[ih]->Add(h);
	       }

	     for(int is=0;is<nsys;is++)
	       {
		  std::string hname_sys_up = hname[ih]+"_"+sys[is]+"_Up";
		  std::string hname_sys_up_clone = hname_sys_up+"_stop_clone";
		  TH1F *h_sys_up = (TH1F*)f_stop[i]->Get(hname_sys_up.c_str());
		  std::string hname_sys_down = hname[ih]+"_"+sys[is]+"_Down";
		  std::string hname_sys_down_clone = hname_sys_down+"_stop_clone";
		  TH1F *h_sys_down = (TH1F*)f_stop[i]->Get(hname_sys_down.c_str());
		  
		  if( i == 0 )
		    {
		       fout->cd();
		       h_stop_up[is][ih] = (TH1F*)h_sys_up->Clone(hname_sys_up_clone.c_str());
		       h_stop_down[is][ih] = (TH1F*)h_sys_down->Clone(hname_sys_down_clone.c_str());
		    }
		  else
		    {
		       h_stop_up[is][ih]->Add(h_sys_up);
		       h_stop_down[is][ih]->Add(h_sys_down);
		    }
	       }
	  }
     }
   
   gDirectory->cd(); for(int i=0;i<stop_n;i++) f_stop[i]->Close();

   for(int i=0;i<sig_hut_n;i++)
     {	
	std::string fname = "../hist"+toyName+"_MERGED/"+sig_hut[i]+".root";
	f_sig_hut[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {	     
	     std::string hname_clone = hname[ih]+"_sig_hut_clone";
	     TH1F *h = (TH1F*)f_sig_hut[i]->Get(hname[ih].c_str());
	     
	     if( i == 0 )
	       {
		  fout->cd();
		  h_sig_hut[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_sig_hut[ih]->Add(h);
	       }

	     for(int is=0;is<nsys;is++)
	       {
		  std::string hname_sys_up = hname[ih]+"_"+sys[is]+"_Up";
		  std::string hname_sys_up_clone = hname_sys_up+"_sig_hut_clone";
		  TH1F *h_sys_up = (TH1F*)f_sig_hut[i]->Get(hname_sys_up.c_str());
		  std::string hname_sys_down = hname[ih]+"_"+sys[is]+"_Down";
		  std::string hname_sys_down_clone = hname_sys_down+"_sig_hut_clone";
		  TH1F *h_sys_down = (TH1F*)f_sig_hut[i]->Get(hname_sys_down.c_str());
		       
		  if( i == 0 )
		    {
		       fout->cd();
		       h_sig_hut_up[is][ih] = (TH1F*)h_sys_up->Clone(hname_sys_up_clone.c_str());
		       h_sig_hut_down[is][ih] = (TH1F*)h_sys_down->Clone(hname_sys_down_clone.c_str());
		    }
		  else
		    {
		       h_sig_hut_up[is][ih]->Add(h_sys_up);
		       h_sig_hut_down[is][ih]->Add(h_sys_down);
		    }
	       }
	  }
     }
   
   gDirectory->cd(); for(int i=0;i<sig_hut_n;i++) f_sig_hut[i]->Close();

   for(int i=0;i<sig_hut_stop_n;i++)
     {	
	std::string fname = "../hist"+toyName+"_MERGED/"+sig_hut_stop[i]+".root";
	f_sig_hut_stop[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {	     
	     std::string hname_clone = hname[ih]+"_sig_hut_stop_clone";
	     TH1F *h = (TH1F*)f_sig_hut_stop[i]->Get(hname[ih].c_str());
	     
	     if( i == 0 )
	       {
		  fout->cd();
		  h_sig_hut_stop[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_sig_hut_stop[ih]->Add(h);
	       }

	     for(int is=0;is<nsys;is++)
	       {
		  std::string hname_sys_up = hname[ih]+"_"+sys[is]+"_Up";
		  std::string hname_sys_up_clone = hname_sys_up+"_sig_hut_stop_clone";
		  TH1F *h_sys_up = (TH1F*)f_sig_hut_stop[i]->Get(hname_sys_up.c_str());
		  std::string hname_sys_down = hname[ih]+"_"+sys[is]+"_Down";
		  std::string hname_sys_down_clone = hname_sys_down+"_sig_hut_stop_clone";
		  TH1F *h_sys_down = (TH1F*)f_sig_hut_stop[i]->Get(hname_sys_down.c_str());
		  
		  if( i == 0 )
		    {
		       fout->cd();
		       h_sig_hut_stop_up[is][ih] = (TH1F*)h_sys_up->Clone(hname_sys_up_clone.c_str());
		       h_sig_hut_stop_down[is][ih] = (TH1F*)h_sys_down->Clone(hname_sys_down_clone.c_str());
		    }
		  else
		    {
		       h_sig_hut_stop_up[is][ih]->Add(h_sys_up);
		       h_sig_hut_stop_down[is][ih]->Add(h_sys_down);
		    }
	       }
	  }
     }
   
   gDirectory->cd(); for(int i=0;i<sig_hut_stop_n;i++) f_sig_hut_stop[i]->Close();

   for(int i=0;i<sig_hct_stop_n;i++)
     {	
	std::string fname = "../hist"+toyName+"_MERGED/"+sig_hct_stop[i]+".root";
	f_sig_hct_stop[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {	     
	     std::string hname_clone = hname[ih]+"_sig_hct_stop_clone";
	     TH1F *h = (TH1F*)f_sig_hct_stop[i]->Get(hname[ih].c_str());
	     
	     if( i == 0 )
	       {
		  fout->cd();
		  h_sig_hct_stop[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_sig_hct_stop[ih]->Add(h);
	       }

	     for(int is=0;is<nsys;is++)
	       {
		  std::string hname_sys_up = hname[ih]+"_"+sys[is]+"_Up";
		  std::string hname_sys_up_clone = hname_sys_up+"_sig_hct_stop_clone";
		  TH1F *h_sys_up = (TH1F*)f_sig_hct_stop[i]->Get(hname_sys_up.c_str());
		  std::string hname_sys_down = hname[ih]+"_"+sys[is]+"_Down";
		  std::string hname_sys_down_clone = hname_sys_down+"_sig_hct_stop_clone";
		  TH1F *h_sys_down = (TH1F*)f_sig_hct_stop[i]->Get(hname_sys_down.c_str());
		  
		  if( i == 0 )
		    {
		       fout->cd();
		       h_sig_hct_stop_up[is][ih] = (TH1F*)h_sys_up->Clone(hname_sys_up_clone.c_str());
		       h_sig_hct_stop_down[is][ih] = (TH1F*)h_sys_down->Clone(hname_sys_down_clone.c_str());
		    }
		  else
		    {
		       h_sig_hct_stop_up[is][ih]->Add(h_sys_up);
		       h_sig_hct_stop_down[is][ih]->Add(h_sys_down);
		    }
	       }
	  }	
     }
   
   gDirectory->cd(); for(int i=0;i<sig_hct_stop_n;i++) f_sig_hct_stop[i]->Close();
   
   for(int i=0;i<sig_hut_ttbar_n;i++)
     {	
	std::string fname = "../hist"+toyName+"_MERGED/"+sig_hut_ttbar[i]+".root";
	f_sig_hut_ttbar[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {	     
	     std::string hname_clone = hname[ih]+"_sig_hut_ttbar_clone";
	     TH1F *h = (TH1F*)f_sig_hut_ttbar[i]->Get(hname[ih].c_str());
	     
	     if( i == 0 )
	       {
		  fout->cd();
		  h_sig_hut_ttbar[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_sig_hut_ttbar[ih]->Add(h);
	       }

	     for(int is=0;is<nsys;is++)
	       {
		  std::string hname_sys_up = hname[ih]+"_"+sys[is]+"_Up";
		  std::string hname_sys_up_clone = hname_sys_up+"_sig_hut_ttbar_clone";
		  TH1F *h_sys_up = (TH1F*)f_sig_hut_ttbar[i]->Get(hname_sys_up.c_str());
		  std::string hname_sys_down = hname[ih]+"_"+sys[is]+"_Down";
		  std::string hname_sys_down_clone = hname_sys_down+"_sig_hut_ttbar_clone";
		  TH1F *h_sys_down = (TH1F*)f_sig_hut_ttbar[i]->Get(hname_sys_down.c_str());
		  
		  if( i == 0 )
		    {
		       fout->cd();
		       h_sig_hut_ttbar_up[is][ih] = (TH1F*)h_sys_up->Clone(hname_sys_up_clone.c_str());
		       h_sig_hut_ttbar_down[is][ih] = (TH1F*)h_sys_down->Clone(hname_sys_down_clone.c_str());
		    }
		  else
		    {
		       h_sig_hut_ttbar_up[is][ih]->Add(h_sys_up);
		       h_sig_hut_ttbar_down[is][ih]->Add(h_sys_down);
		    }
	       }
	  }
     }
   
   gDirectory->cd(); for(int i=0;i<sig_hut_ttbar_n;i++) f_sig_hut_ttbar[i]->Close();

   for(int i=0;i<sig_hct_ttbar_n;i++)
     {	
	std::string fname = "../hist"+toyName+"_MERGED/"+sig_hct_ttbar[i]+".root";
	f_sig_hct_ttbar[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {	     
	     std::string hname_clone = hname[ih]+"_sig_hct_ttbar_clone";
	     TH1F *h = (TH1F*)f_sig_hct_ttbar[i]->Get(hname[ih].c_str());
	     
	     if( i == 0 )
	       {
		  fout->cd();
		  h_sig_hct_ttbar[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_sig_hct_ttbar[ih]->Add(h);
	       }

	     for(int is=0;is<nsys;is++)
	       {
		  std::string hname_sys_up = hname[ih]+"_"+sys[is]+"_Up";
		  std::string hname_sys_up_clone = hname_sys_up+"_sig_hct_ttbar_clone";
		  TH1F *h_sys_up = (TH1F*)f_sig_hct_ttbar[i]->Get(hname_sys_up.c_str());
		  std::string hname_sys_down = hname[ih]+"_"+sys[is]+"_Down";
		  std::string hname_sys_down_clone = hname_sys_down+"_sig_hct_ttbar_clone";
		  TH1F *h_sys_down = (TH1F*)f_sig_hct_ttbar[i]->Get(hname_sys_down.c_str());
		  
		  if( i == 0 )
		    {
		       fout->cd();
		       h_sig_hct_ttbar_up[is][ih] = (TH1F*)h_sys_up->Clone(hname_sys_up_clone.c_str());
		       h_sig_hct_ttbar_down[is][ih] = (TH1F*)h_sys_down->Clone(hname_sys_down_clone.c_str());
		    }
		  else
		    {
		       h_sig_hct_ttbar_up[is][ih]->Add(h_sys_up);
		       h_sig_hct_ttbar_down[is][ih]->Add(h_sys_down);
		    }
	       }
	  }	
     }
   
   gDirectory->cd(); for(int i=0;i<sig_hct_ttbar_n;i++) f_sig_hct_ttbar[i]->Close();

   // Process histograms

//   exit(1);
   fout->cd();

   for(int ih=0;ih<hn;ih++)
     {
	TCanvas *c1 = new TCanvas("c1","c1",0,0,600,500);
	TPad *c1_1;
	c1->Range(0,0,1,1);
	c1_1 = new TPad("c1_1","main",0.01,0.30,0.99,0.99);
	c1_1->Draw();
	c1_1->cd();

	h_sig_hut[ih]->Scale(sigScale);
	h_sig_hut_stop[ih]->Scale(sigScale);
	h_sig_hut_ttbar[ih]->Scale(sigScale);
	h_sig_hct_stop[ih]->Scale(sigScale);
	h_sig_hct_ttbar[ih]->Scale(sigScale);	
	
	for(int is=0;is<nsys;is++)
	  {
	     h_sig_hut_up[is][ih]->Scale(sigScale);
	     h_sig_hut_down[is][ih]->Scale(sigScale);
	     h_sig_hut_stop_up[is][ih]->Scale(sigScale);
	     h_sig_hut_stop_down[is][ih]->Scale(sigScale);
	     h_sig_hut_ttbar_up[is][ih]->Scale(sigScale);
	     h_sig_hut_ttbar_down[is][ih]->Scale(sigScale);
	     h_sig_hct_stop_up[is][ih]->Scale(sigScale);
	     h_sig_hct_stop_down[is][ih]->Scale(sigScale);
	     h_sig_hct_ttbar_up[is][ih]->Scale(sigScale);
	     h_sig_hct_ttbar_down[is][ih]->Scale(sigScale);
	  }
	
	addbin(h_data[ih]);
	addbin(h_ttbar[ih]); removeMCNeg(h_ttbar[ih]);
	addbin(h_ttbb[ih]); removeMCNeg(h_ttbb[ih]);
	addbin(h_ttcc[ih]); removeMCNeg(h_ttcc[ih]);
	addbin(h_ttlf[ih]); removeMCNeg(h_ttlf[ih]);
	addbin(h_stop[ih]); removeMCNeg(h_stop[ih]);
	addbin(h_zjets[ih]); removeMCNeg(h_zjets[ih]);
	addbin(h_wjets[ih]); removeMCNeg(h_wjets[ih]);
	addbin(h_sig_hut[ih]); removeMCNeg(h_sig_hut[ih]);
	addbin(h_sig_hut_stop[ih]); removeMCNeg(h_sig_hut_stop[ih]);
	addbin(h_sig_hut_ttbar[ih]); removeMCNeg(h_sig_hut_ttbar[ih]);
	addbin(h_sig_hct_stop[ih]); removeMCNeg(h_sig_hct_stop[ih]);
	addbin(h_sig_hct_ttbar[ih]); removeMCNeg(h_sig_hct_ttbar[ih]);

	for(int is=0;is<nsys;is++)
	  {
	     addbin(h_ttbar_up[is][ih]); removeMCNeg(h_ttbar_up[is][ih]);
	     addbin(h_ttbar_down[is][ih]); removeMCNeg(h_ttbar_down[is][ih]);
	     addbin(h_ttbb_up[is][ih]); removeMCNeg(h_ttbb_up[is][ih]);
	     addbin(h_ttbb_down[is][ih]); removeMCNeg(h_ttbb_down[is][ih]);
	     addbin(h_ttcc_up[is][ih]); removeMCNeg(h_ttcc_up[is][ih]);
	     addbin(h_ttcc_down[is][ih]); removeMCNeg(h_ttcc_down[is][ih]);
	     addbin(h_ttlf_up[is][ih]); removeMCNeg(h_ttlf_up[is][ih]);
	     addbin(h_ttlf_down[is][ih]); removeMCNeg(h_ttlf_down[is][ih]);
	     addbin(h_stop_up[is][ih]); removeMCNeg(h_stop_up[is][ih]);
	     addbin(h_stop_down[is][ih]); removeMCNeg(h_stop_down[is][ih]);
	     addbin(h_zjets_up[is][ih]); removeMCNeg(h_zjets_up[is][ih]);
	     addbin(h_zjets_down[is][ih]); removeMCNeg(h_zjets_down[is][ih]);
	     addbin(h_wjets_up[is][ih]); removeMCNeg(h_wjets_up[is][ih]);
	     addbin(h_wjets_down[is][ih]); removeMCNeg(h_wjets_down[is][ih]);
	     addbin(h_sig_hut_up[is][ih]); removeMCNeg(h_sig_hut_up[is][ih]);
	     addbin(h_sig_hut_down[is][ih]); removeMCNeg(h_sig_hut_down[is][ih]);
	     addbin(h_sig_hut_stop_up[is][ih]); removeMCNeg(h_sig_hut_stop_up[is][ih]);
	     addbin(h_sig_hut_stop_down[is][ih]); removeMCNeg(h_sig_hut_stop_down[is][ih]);
	     addbin(h_sig_hut_ttbar_up[is][ih]); removeMCNeg(h_sig_hut_ttbar_up[is][ih]);
	     addbin(h_sig_hut_ttbar_down[is][ih]); removeMCNeg(h_sig_hut_ttbar_down[is][ih]);
	     addbin(h_sig_hct_stop_up[is][ih]); removeMCNeg(h_sig_hct_stop_up[is][ih]);
	     addbin(h_sig_hct_stop_down[is][ih]); removeMCNeg(h_sig_hct_stop_down[is][ih]);
	     addbin(h_sig_hct_ttbar_up[is][ih]); removeMCNeg(h_sig_hct_ttbar_up[is][ih]);
	     addbin(h_sig_hct_ttbar_down[is][ih]); removeMCNeg(h_sig_hct_ttbar_down[is][ih]);
	  }
	
        h_data[ih]->SetMarkerSize(0.7);
	h_data[ih]->SetMarkerColor(1);
	h_data[ih]->SetLineColor(1);
	
        h_zjets[ih]->SetMarkerSize(0);
	h_zjets[ih]->SetMarkerColor(94);
	h_zjets[ih]->SetLineColor(94);
	h_zjets[ih]->SetFillColor(94);
	h_zjets[ih]->SetLineStyle(1);
	
	h_ttbar[ih]->SetMarkerSize(0);
	h_ttbar[ih]->SetMarkerColor(kAzure+1);
	h_ttbar[ih]->SetLineColor(kAzure+1);
	h_ttbar[ih]->SetFillColor(kAzure+1);
	h_ttbar[ih]->SetLineStyle(1);

	h_ttbb[ih]->SetMarkerSize(0);
	h_ttbb[ih]->SetMarkerColor(kAzure+3);
	h_ttbb[ih]->SetLineColor(kAzure+3);
	h_ttbb[ih]->SetFillColor(kAzure+3);
	h_ttbb[ih]->SetLineStyle(1);

	h_ttcc[ih]->SetMarkerSize(0);
	h_ttcc[ih]->SetMarkerColor(kAzure+5);
	h_ttcc[ih]->SetLineColor(kAzure+5);
	h_ttcc[ih]->SetFillColor(kAzure+5);
	h_ttcc[ih]->SetLineStyle(1);

	h_ttlf[ih]->SetMarkerSize(0);
	h_ttlf[ih]->SetMarkerColor(kAzure+7);
	h_ttlf[ih]->SetLineColor(kAzure+7);
	h_ttlf[ih]->SetFillColor(kAzure+7);
	h_ttlf[ih]->SetLineStyle(1);
	
	h_stop[ih]->SetMarkerSize(0);
	h_stop[ih]->SetMarkerColor(kGreen);
	h_stop[ih]->SetLineColor(kGreen);
	h_stop[ih]->SetFillColor(kGreen);
	h_stop[ih]->SetLineStyle(1);
	
//	h_ttv[ih]->SetMarkerSize(0);
//	h_ttv[ih]->SetMarkerColor(kOrange);
//	h_ttv[ih]->SetLineColor(kOrange);
//	h_ttv[ih]->SetFillColor(kOrange);
//	h_ttv[ih]->SetLineStyle(1);

	h_wjets[ih]->SetMarkerSize(0);
	h_wjets[ih]->SetMarkerColor(kMagenta-7);
	h_wjets[ih]->SetLineColor(kMagenta-7);
	h_wjets[ih]->SetFillColor(kMagenta-7);
	h_wjets[ih]->SetLineStyle(1);

	h_sig_hut[ih]->SetMarkerSize(0);
	h_sig_hut[ih]->SetMarkerColor(kRed);
	h_sig_hut[ih]->SetLineColor(kRed);
	h_sig_hut[ih]->SetFillColor(0);
	h_sig_hut[ih]->SetLineWidth(2);

	h_sig_hut_stop[ih]->SetMarkerSize(0);
	h_sig_hut_stop[ih]->SetMarkerColor(kRed+1);
	h_sig_hut_stop[ih]->SetLineColor(kRed+1);
	h_sig_hut_stop[ih]->SetFillColor(0);
	h_sig_hut_stop[ih]->SetLineWidth(2);

	h_sig_hut_ttbar[ih]->SetMarkerSize(0);
	h_sig_hut_ttbar[ih]->SetMarkerColor(kRed-7);
	h_sig_hut_ttbar[ih]->SetLineColor(kRed-7);
	h_sig_hut_ttbar[ih]->SetFillColor(0);
	h_sig_hut_ttbar[ih]->SetLineWidth(2);

	h_sig_hct_stop[ih]->SetMarkerSize(0);
	h_sig_hct_stop[ih]->SetMarkerColor(kYellow+1);
	h_sig_hct_stop[ih]->SetLineColor(kYellow+1);
	h_sig_hct_stop[ih]->SetFillColor(0);
	h_sig_hct_stop[ih]->SetLineWidth(2);

	h_sig_hct_ttbar[ih]->SetMarkerSize(0);
	h_sig_hct_ttbar[ih]->SetMarkerColor(kYellow-7);
	h_sig_hct_ttbar[ih]->SetLineColor(kYellow-7);
	h_sig_hct_ttbar[ih]->SetFillColor(0);
	h_sig_hct_ttbar[ih]->SetLineWidth(2);

	float data_int = h_data[ih]->Integral(0,h_data[ih]->GetXaxis()->GetNbins()+1);
	
	float ttbar_int = h_ttbar[ih]->Integral(0,h_ttbar[ih]->GetXaxis()->GetNbins()+1);
	float ttbb_int = h_ttbb[ih]->Integral(0,h_ttbb[ih]->GetXaxis()->GetNbins()+1);
	float ttcc_int = h_ttcc[ih]->Integral(0,h_ttcc[ih]->GetXaxis()->GetNbins()+1);
	float ttlf_int = h_ttlf[ih]->Integral(0,h_ttlf[ih]->GetXaxis()->GetNbins()+1);
	float stop_int = h_stop[ih]->Integral(0,h_stop[ih]->GetXaxis()->GetNbins()+1);
	float zjets_int = h_zjets[ih]->Integral(0,h_zjets[ih]->GetXaxis()->GetNbins()+1);
	float wjets_int = h_wjets[ih]->Integral(0,h_wjets[ih]->GetXaxis()->GetNbins()+1);
	
	float bg_int = ttbb_int+ttcc_int+ttlf_int+stop_int+zjets_int+wjets_int;

	fout->cd();
	
	std::string h_data_name = "data_"+hname[ih];
	TH1F * h_data_orig = (TH1F*)h_data[ih]->Clone(h_data_name.c_str());
	std::string h_data_name_norm = "data_"+hname[ih]+"_norm";
	TH1F * h_data_norm = (TH1F*)h_data[ih]->Clone(h_data_name_norm.c_str());
	if(data_int > 0) h_data_norm->Scale(1./data_int);
	
	std::string h_ttbar_name = "ttbar_"+hname[ih];
	TH1F * h_ttbar_orig = (TH1F*)h_ttbar[ih]->Clone(h_ttbar_name.c_str());
	std::string h_ttbar_name_norm = "ttbar_"+hname[ih]+"_norm";
	TH1F * h_ttbar_norm = (TH1F*)h_ttbar[ih]->Clone(h_ttbar_name_norm.c_str());
	if(bg_int > 0) h_ttbar_norm->Scale(1./bg_int);

	std::string h_ttbb_name = "ttbb_"+hname[ih];
	TH1F * h_ttbb_orig = (TH1F*)h_ttbb[ih]->Clone(h_ttbb_name.c_str());
	std::string h_ttbb_name_norm = "ttbb_"+hname[ih]+"_norm";
	TH1F * h_ttbb_norm = (TH1F*)h_ttbb[ih]->Clone(h_ttbb_name_norm.c_str());
	if(bg_int > 0) h_ttbb_norm->Scale(1./bg_int);

	std::string h_ttcc_name = "ttcc_"+hname[ih];
	TH1F * h_ttcc_orig = (TH1F*)h_ttcc[ih]->Clone(h_ttcc_name.c_str());
	std::string h_ttcc_name_norm = "ttcc_"+hname[ih]+"_norm";
	TH1F * h_ttcc_norm = (TH1F*)h_ttcc[ih]->Clone(h_ttcc_name_norm.c_str());
	if(bg_int > 0) h_ttcc_norm->Scale(1./bg_int);

	std::string h_ttlf_name = "ttlf_"+hname[ih];
	TH1F * h_ttlf_orig = (TH1F*)h_ttlf[ih]->Clone(h_ttlf_name.c_str());
	std::string h_ttlf_name_norm = "ttlf_"+hname[ih]+"_norm";
	TH1F * h_ttlf_norm = (TH1F*)h_ttlf[ih]->Clone(h_ttlf_name_norm.c_str());
	if(bg_int > 0) h_ttlf_norm->Scale(1./bg_int);
	
	std::string h_stop_name = "stop_"+hname[ih];
	TH1F * h_stop_orig = (TH1F*)h_stop[ih]->Clone(h_stop_name.c_str());
	std::string h_stop_name_norm = "stop_"+hname[ih]+"_norm";
	TH1F * h_stop_norm = (TH1F*)h_stop[ih]->Clone(h_stop_name_norm.c_str());
	if(bg_int > 0) h_stop_norm->Scale(1./bg_int);
	
	std::string h_zjets_name = "zjets_"+hname[ih];
	TH1F * h_zjets_orig = (TH1F*)h_zjets[ih]->Clone(h_zjets_name.c_str());
	std::string h_zjets_name_norm = "zjets_"+hname[ih]+"_norm";
	TH1F * h_zjets_norm = (TH1F*)h_zjets[ih]->Clone(h_zjets_name_norm.c_str());
	if(bg_int > 0) h_zjets_norm->Scale(1./bg_int);
	
	std::string h_wjets_name = "wjets_"+hname[ih];
	TH1F * h_wjets_orig = (TH1F*)h_wjets[ih]->Clone(h_wjets_name.c_str());
	std::string h_wjets_name_norm = "wjets_"+hname[ih]+"_norm";
	TH1F * h_wjets_norm = (TH1F*)h_wjets[ih]->Clone(h_wjets_name_norm.c_str());
	if(bg_int > 0) h_wjets_norm->Scale(1./bg_int);

	float sig_hut_stop_int = h_sig_hut_stop[ih]->Integral(0,h_sig_hut_stop[ih]->GetXaxis()->GetNbins()+1);
	float sig_hut_ttbar_int = h_sig_hut_ttbar[ih]->Integral(0,h_sig_hut_ttbar[ih]->GetXaxis()->GetNbins()+1);
	float sig_hct_stop_int = h_sig_hct_stop[ih]->Integral(0,h_sig_hct_stop[ih]->GetXaxis()->GetNbins()+1);
	float sig_hct_ttbar_int = h_sig_hct_ttbar[ih]->Integral(0,h_sig_hct_ttbar[ih]->GetXaxis()->GetNbins()+1);
	
	std::string h_sig_hut_stop_name = "sig_hut_stop_"+hname[ih];
	TH1F * h_sig_hut_stop_orig = (TH1F*)h_sig_hut_stop[ih]->Clone(h_sig_hut_stop_name.c_str());
	std::string h_sig_hut_stop_name_norm = "sig_hut_stop_"+hname[ih]+"_norm";
	TH1F * h_sig_hut_stop_norm = (TH1F*)h_sig_hut_stop[ih]->Clone(h_sig_hut_stop_name_norm.c_str());
	if(sig_hut_stop_int > 0) h_sig_hut_stop_norm->Scale(1./sig_hut_stop_int);

	std::string h_sig_hut_ttbar_name = "sig_hut_ttbar_"+hname[ih];
	TH1F * h_sig_hut_ttbar_orig = (TH1F*)h_sig_hut_ttbar[ih]->Clone(h_sig_hut_ttbar_name.c_str());
	std::string h_sig_hut_ttbar_name_norm = "sig_hut_ttbar_"+hname[ih]+"_norm";
	TH1F * h_sig_hut_ttbar_norm = (TH1F*)h_sig_hut_ttbar[ih]->Clone(h_sig_hut_ttbar_name_norm.c_str());
	if(sig_hut_ttbar_int > 0) h_sig_hut_ttbar_norm->Scale(1./sig_hut_ttbar_int);

	std::string h_sig_hct_stop_name = "sig_hct_stop_"+hname[ih];
	TH1F * h_sig_hct_stop_orig = (TH1F*)h_sig_hct_stop[ih]->Clone(h_sig_hct_stop_name.c_str());
	std::string h_sig_hct_stop_name_norm = "sig_hct_stop_"+hname[ih]+"_norm";
	TH1F * h_sig_hct_stop_norm = (TH1F*)h_sig_hct_stop[ih]->Clone(h_sig_hct_stop_name_norm.c_str());
	if(sig_hct_stop_int > 0) h_sig_hct_stop_norm->Scale(1./sig_hct_stop_int);

	std::string h_sig_hct_ttbar_name = "sig_hct_ttbar_"+hname[ih];
	TH1F * h_sig_hct_ttbar_orig = (TH1F*)h_sig_hct_ttbar[ih]->Clone(h_sig_hct_ttbar_name.c_str());
	std::string h_sig_hct_ttbar_name_norm = "sig_hct_ttbar_"+hname[ih]+"_norm";
	TH1F * h_sig_hct_ttbar_norm = (TH1F*)h_sig_hct_ttbar[ih]->Clone(h_sig_hct_ttbar_name_norm.c_str());
	if(sig_hct_ttbar_int > 0) h_sig_hct_ttbar_norm->Scale(1./sig_hct_ttbar_int);

	for(int is=0;is<nsys;is++)
	  {
	     float ttbar_up_int = h_ttbar_up[is][ih]->Integral();
	     if( ttbar_up_int > 0 && bg_int > 0 && norm[is] ) h_ttbar_up[is][ih]->Scale(ttbar_int/(ttbar_up_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_ttbar_up[is][ih]->Scale(1./bg_int);
	     float ttbar_down_int = h_ttbar_down[is][ih]->Integral();
	     if( ttbar_down_int > 0 && bg_int > 0 && norm[is] ) h_ttbar_down[is][ih]->Scale(ttbar_int/(ttbar_down_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_ttbar_down[is][ih]->Scale(1./bg_int);
	     
	     float ttbb_up_int = h_ttbb_up[is][ih]->Integral();
	     if( ttbb_up_int > 0 && bg_int > 0 && norm[is] ) h_ttbb_up[is][ih]->Scale(ttbb_int/(ttbb_up_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_ttbb_up[is][ih]->Scale(1./bg_int);
	     float ttbb_down_int = h_ttbb_down[is][ih]->Integral();
	     if( ttbb_down_int > 0 && bg_int > 0 && norm[is] ) h_ttbb_down[is][ih]->Scale(ttbb_int/(ttbb_down_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_ttbb_down[is][ih]->Scale(1./bg_int);
	     
	     float ttcc_up_int = h_ttcc_up[is][ih]->Integral();
	     if( ttcc_up_int > 0 && bg_int > 0 && norm[is] ) h_ttcc_up[is][ih]->Scale(ttcc_int/(ttcc_up_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_ttcc_up[is][ih]->Scale(1./bg_int);
	     float ttcc_down_int = h_ttcc_down[is][ih]->Integral();
	     if( ttcc_down_int > 0 && bg_int > 0 && norm[is] ) h_ttcc_down[is][ih]->Scale(ttcc_int/(ttcc_down_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_ttcc_down[is][ih]->Scale(1./bg_int);
		  
	     float ttlf_up_int = h_ttlf_up[is][ih]->Integral();
	     if( ttlf_up_int > 0 && bg_int > 0 && norm[is] ) h_ttlf_up[is][ih]->Scale(ttlf_int/(ttlf_up_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_ttlf_up[is][ih]->Scale(1./bg_int);
	     float ttlf_down_int = h_ttlf_down[is][ih]->Integral();
	     if( ttlf_down_int > 0 && bg_int > 0 && norm[is] ) h_ttlf_down[is][ih]->Scale(ttlf_int/(ttlf_down_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_ttlf_down[is][ih]->Scale(1./bg_int);
	     
	     float zjets_up_int = h_zjets_up[is][ih]->Integral();
	     if( zjets_up_int > 0 && bg_int > 0 && norm[is] ) h_zjets_up[is][ih]->Scale(zjets_int/(zjets_up_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_zjets_up[is][ih]->Scale(1./bg_int);
	     float zjets_down_int = h_zjets_down[is][ih]->Integral();
	     if( zjets_down_int > 0 && bg_int > 0 && norm[is] ) h_zjets_down[is][ih]->Scale(zjets_int/(zjets_down_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_zjets_down[is][ih]->Scale(1./bg_int);
	     
	     float wjets_up_int = h_wjets_up[is][ih]->Integral();
	     if( wjets_up_int > 0 && bg_int > 0 && norm[is] ) h_wjets_up[is][ih]->Scale(wjets_int/(wjets_up_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_wjets_up[is][ih]->Scale(1./bg_int);
	     float wjets_down_int = h_wjets_down[is][ih]->Integral();
	     if( wjets_down_int > 0 && bg_int > 0 && norm[is] ) h_wjets_down[is][ih]->Scale(wjets_int/(wjets_down_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_wjets_down[is][ih]->Scale(1./bg_int);
	     
	     float stop_up_int = h_stop_up[is][ih]->Integral();
	     if( stop_up_int > 0 && bg_int > 0 && norm[is] ) h_stop_up[is][ih]->Scale(stop_int/(stop_up_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_stop_up[is][ih]->Scale(1./bg_int);
	     float stop_down_int = h_stop_down[is][ih]->Integral();
	     if( stop_down_int > 0 && bg_int > 0 && norm[is] ) h_stop_down[is][ih]->Scale(stop_int/(stop_down_int*bg_int));
	     if( bg_int > 0 && !norm[is] ) h_stop_down[is][ih]->Scale(1./bg_int);
	  }
	
	fout->cd();
	
	std::string h_bg_norm_name_merged = "bg_norm_"+hname[ih]+"_merged";
	TH1F *h_bg_norm_merged = (TH1F*)h_ttbb_norm->Clone(h_bg_norm_name_merged.c_str());
	h_bg_norm_merged->Add(h_ttcc_norm);
	h_bg_norm_merged->Add(h_ttlf_norm);
	h_bg_norm_merged->Add(h_stop_norm);
	h_bg_norm_merged->Add(h_zjets_norm);
	h_bg_norm_merged->Add(h_wjets_norm);

	TH1F *h_comb = (TH1F*)h_bg_norm_merged->Clone("h_comb");
	TH1F *h_sys_down_combSum = (TH1F*)h_comb->Clone("h_sys_down_combSum");
	TH1F *h_sys_up_combSum = (TH1F*)h_comb->Clone("h_sys_up_combSum");
	
	std::vector<TH1F*> v_bg;
	v_bg.push_back(h_ttbb_norm);
	v_bg.push_back(h_ttcc_norm);
	v_bg.push_back(h_ttlf_norm);
	v_bg.push_back(h_stop_norm);
	v_bg.push_back(h_zjets_norm);
	v_bg.push_back(h_wjets_norm);
	
	std::vector<std::vector<TH1F*> > v_bg_up;
	std::vector<std::vector<TH1F*> > v_bg_down;

	for(int is=0;is<nsys;is++)
	  {
	     std::vector<TH1F*> v_down;
	     std::vector<TH1F*> v_up;

	     v_down.push_back(h_ttbb_down[is][ih]);	     
	     v_down.push_back(h_ttcc_down[is][ih]);
	     v_down.push_back(h_ttlf_down[is][ih]);
	     v_down.push_back(h_stop_down[is][ih]);
	     v_down.push_back(h_zjets_down[is][ih]);
	     v_down.push_back(h_wjets_down[is][ih]);
	     
	     v_up.push_back(h_ttbb_up[is][ih]);
	     v_up.push_back(h_ttcc_up[is][ih]);
	     v_up.push_back(h_ttlf_up[is][ih]);
	     v_up.push_back(h_stop_up[is][ih]);
	     v_up.push_back(h_zjets_up[is][ih]);
	     v_up.push_back(h_wjets_up[is][ih]);

	     v_bg_up.push_back(v_up);
	     v_bg_down.push_back(v_down);
	  }
	
	TH1F *h_sys_up_comb[nsys];
	TH1F *h_sys_down_comb[nsys];
	
	for(int is=0;is<nsys;is++)
	  {
	     std::string sysname_up = "h_comb_sys_"+sys[is]+"_up";
	     h_sys_up_comb[is] = (TH1F*)h_comb->Clone(sysname_up.c_str());
	     
	     std::string sysname_down = "h_comb_sys_"+sys[is]+"_down";
	     h_sys_down_comb[is] = (TH1F*)h_comb->Clone(sysname_down.c_str());
	  }	
	
	for(int is=0;is<nsys;is++)
	  {
	     combSysLinear(v_bg,v_bg_up[is],v_bg_down[is],h_comb,h_sys_down_comb[is],h_sys_up_comb[is]);
	     
	     totSys(h_comb,h_sys_down_comb[is],h_sys_up_comb[is]);
	  }
	
	combSys(h_comb,h_sys_down_comb,h_sys_up_comb,h_sys_down_combSum,h_sys_up_combSum,nsys);
	
	totSys(h_comb,h_sys_down_combSum,h_sys_up_combSum);
	
	THStack *h_bg_norm = new THStack();
	h_bg_norm->Add(h_ttbb_norm);
	h_bg_norm->Add(h_ttcc_norm);
	h_bg_norm->Add(h_ttlf_norm);
	h_bg_norm->Add(h_stop_norm);
	h_bg_norm->Add(h_zjets_norm);
	h_bg_norm->Add(h_wjets_norm);

	int itit = varid[ih];
	std::string xtitle = xtit[itit];
	
	// IL normalised
	h_bg_norm->Draw("hist e1");
	h_bg_norm->GetXaxis()->SetTitle(xtitle.c_str());
	h_data_norm->GetXaxis()->SetTitle(xtitle.c_str());
//	h_bg_norm->GetYaxis()->SetTitle("Number of events");
	
	h_data_norm->Draw("e1p same");
	
	if( sigType == 1 || sigType == 0 || sigType == 5 )
	  {
//	     h_sig_hut_stop[ih]->Scale(ksig);
	     h_sig_hut_stop_norm->Draw("hist e1 same");
	  }	

	if( sigType == 2 || sigType == 0 || sigType == 5 )
	  {	     
//	     h_sig_hct_stop[ih]->Scale(ksig);
	     h_sig_hct_stop_norm->Draw("hist e1 same");
	  }	
	
	if( sigType == 3 || sigType == 0 || sigType == 6 )
	  {	     
//	     h_sig_hut_ttbar[ih]->Scale(ksig);
	     h_sig_hut_ttbar_norm->Draw("hist e1 same");
	  }	

	if( sigType == 4 || sigType == 0 || sigType == 6 )
	  {
//	     h_sig_hct_ttbar[ih]->Scale(ksig);
	     h_sig_hct_ttbar_norm->Draw("hist e1 same");
	  }	

//	TLegend *leg = new TLegend(0.70,0.92,0.92,0.60);
	TLegend *leg = new TLegend(0.82,0.92,0.995,0.40);
	leg->SetFillColor(253);
	leg->SetBorderSize(0);
	leg->AddEntry(h_data_norm,"Data","lp");
//	leg->AddEntry(h_ttbar[ih],"Ttbar","f");
	leg->AddEntry(h_ttbb_norm,"tt+bb","f");
	leg->AddEntry(h_ttcc_norm,"tt+cc","f");
	leg->AddEntry(h_ttlf_norm,"tt+lf","f");
	leg->AddEntry(h_stop_norm,"Single top","f");
	leg->AddEntry(h_zjets_norm,"Z+jets","f");
//	leg->AddEntry(h_ttv[ih],"TtbarV","f");
	leg->AddEntry(h_wjets_norm,"W+jets","f");
	if( sigType == 1 || sigType == 0 || sigType == 5 ) leg->AddEntry(h_sig_hut_stop_norm,"FCNH #kappa_{Hut}","lp");
	if( sigType == 2 || sigType == 0 || sigType == 5 ) leg->AddEntry(h_sig_hct_stop_norm,"FCNH #kappa_{Hct}","lp");
	if( sigType == 3 || sigType == 0 || sigType == 6 ) leg->AddEntry(h_sig_hut_ttbar_norm,"FCNH #kappa_{Hut} (ttbar)","lp");
	if( sigType == 4 || sigType == 0 || sigType == 6 ) leg->AddEntry(h_sig_hct_ttbar_norm,"FCNH #kappa_{Hct} (ttbar)","lp");
	leg->Draw();

	float bg_max = h_bg_norm_merged->GetMaximum();
	float sig_max = h_sig_hut_ttbar_norm->GetMaximum();

	float max = std::max(bg_max,sig_max);
	
//	if( ih == 0 ) h_bg->SetMaximum(50.*max);
//	else h_bg->SetMaximum(5.*max);
//	h_bg->SetMaximum(50.*max);
	h_bg_norm->SetMaximum(1.3*max);
	
//	c1_1->SetLogy(1);
//	h_bg->SetMinimum(0.5);
	h_bg_norm->SetMinimum(0.);

//	if( hname[ih] == "h_PassSel_all" ) c1_1->SetLogy(0);
	
/*	TH1F *h_bg_merged_down = (TH1F*)h_bg_merged->Clone("h_bg_merged_down");
	TH1F *h_bg_merged_up = (TH1F*)h_bg_merged->Clone("h_bg_merged_up");
	int nBins = h_data[ih]->GetXaxis()->GetNbins();
	for(int ib=1;ib<=nBins;ib++)
	  {
	     double v = h_bg_merged_down->GetBinContent(ib);
	     double err = h_bg_merged_down->GetBinError(ib);
	     h_bg_merged_down->SetBinContent(ib,v-err);
	     h_bg_merged_up->SetBinContent(ib,v+err);
	  }*/
	
	TGraphAsymmErrors *gr_mc_merged = makeErrorBand(h_comb,h_sys_up_combSum,h_sys_down_combSum);
	
	gStyle->SetHatchesLineWidth(2);
	gr_mc_merged->SetFillStyle(3005);
	gr_mc_merged->SetFillColor(kGray+3);
	gr_mc_merged->Draw("2SAME");

	CMSLABEL();
	if( sel[selid[ih]] != "ALL" ) LABEL(sel[selid[ih]]);
	
//	ratioSig(c1,h_data[ih],h_bg_merged,h_bg_merged_down,h_bg_merged_up);
	ratioSig(c1,h_data_norm,h_comb,h_sys_down_combSum,h_sys_up_combSum);
//	delete h_bg_merged_down;
//	delete h_bg_merged_up;
	
	std::string pname = "pics/"+hname[ih]+"_norm.eps";
	c1->Print(pname.c_str());
	c1->Clear();	
	
	delete gr_mc_merged;

	delete c1;
//	delete c1_1;
	
	c1 = new TCanvas("c1","c1",0,0,600,500);
	c1->Range(0,0,1,1);
	c1_1 = new TPad("c1_1","main",0.01,0.30,0.99,0.99);
	c1_1->Draw();
	c1_1->cd();

	std::string h_bg_name_merged = "bg_"+hname[ih]+"_merged_IL";
	h_ttbb_norm->Scale(bg_int);
	h_ttcc_norm->Scale(bg_int);
	h_ttlf_norm->Scale(bg_int);
	h_stop_norm->Scale(bg_int);
	h_zjets_norm->Scale(bg_int);
	h_wjets_norm->Scale(bg_int);
	
	TH1F *h_bg_merged = (TH1F*)h_ttbb_norm->Clone(h_bg_name_merged.c_str());
	h_bg_merged->Add(h_ttcc_norm);
	h_bg_merged->Add(h_ttlf_norm);
	h_bg_merged->Add(h_stop_norm);
	h_bg_merged->Add(h_zjets_norm);
	h_bg_merged->Add(h_wjets_norm);
	
	h_bg_merged->Write();

	THStack *h_bg = new THStack();
	h_bg->Add(h_ttbb_norm);
	h_bg->Add(h_ttcc_norm);
	h_bg->Add(h_ttlf_norm);
	h_bg->Add(h_stop_norm);
	h_bg->Add(h_zjets_norm);
	h_bg->Add(h_wjets_norm);
	
	h_data_norm->Scale(data_int);
	
	// IL normalised
	h_bg->Draw("hist e1");
	h_bg->GetXaxis()->SetTitle(xtitle.c_str());
	h_bg->GetYaxis()->SetTitle("");
	h_bg->GetYaxis()->SetTitle("Number of events");

	h_data_norm->Draw("e1p same");

	if( sigType == 1 || sigType == 0 || sigType == 5 )
	  {
	     h_sig_hut_stop_norm->Scale(sig_hut_stop_int);
	     h_sig_hut_stop_norm->Draw("hist e1 same");
	  }
	if( sigType == 2 || sigType == 0 || sigType == 5 )
	  {	     	
	     h_sig_hct_stop_norm->Scale(sig_hct_stop_int);
	     h_sig_hct_stop_norm->Draw("hist e1 same");
	  }
	if( sigType == 3 || sigType == 0 || sigType == 6 )
	  {	     
	     h_sig_hut_ttbar_norm->Scale(sig_hut_ttbar_int);
	     h_sig_hut_ttbar_norm->Draw("hist e1 same");
	  }	
	if( sigType == 4 || sigType == 0 || sigType == 6 )
	  {	     	
	     h_sig_hct_ttbar_norm->Scale(sig_hct_ttbar_int);
	     h_sig_hct_ttbar_norm->Draw("hist e1 same");
	  }	

	bg_max = h_bg->GetMaximum();
	float sig_hut_stop_max = h_sig_hut_stop_norm->GetMaximum();
	float sig_hct_stop_max = h_sig_hct_stop_norm->GetMaximum();
	float sig_hut_ttbar_max = h_sig_hut_ttbar_norm->GetMaximum();
	float sig_hct_ttbar_max = h_sig_hct_ttbar_norm->GetMaximum();

	float max_sig = std::max(sig_hut_stop_max,sig_hut_ttbar_max);
	max = std::max(bg_max,max_sig);
	h_bg->SetMaximum(1.3*max);
//	h_bg->SetMaximum(50*max);

	leg->Draw();

//	c1_1->SetLogy(1);
//	h_bg->SetMinimum(0.5);
	h_bg->SetMinimum(0.);

	h_comb->Scale(bg_int);
	h_sys_up_combSum->Scale(bg_int);
	h_sys_down_combSum->Scale(bg_int);
	
	for(int is=0;is<nsys;is++)
	  {
	     h_ttbar_down[is][ih]->Scale(bg_int);
	     h_ttbb_down[is][ih]->Scale(bg_int);
	     h_ttcc_down[is][ih]->Scale(bg_int);
	     h_ttlf_down[is][ih]->Scale(bg_int);
	     h_stop_down[is][ih]->Scale(bg_int);
	     h_zjets_down[is][ih]->Scale(bg_int);
	     h_wjets_down[is][ih]->Scale(bg_int);

	     h_ttbar_up[is][ih]->Scale(bg_int);
	     h_ttbb_up[is][ih]->Scale(bg_int);
	     h_ttcc_up[is][ih]->Scale(bg_int);
	     h_ttlf_up[is][ih]->Scale(bg_int);
	     h_stop_up[is][ih]->Scale(bg_int);
	     h_zjets_up[is][ih]->Scale(bg_int);
	     h_wjets_up[is][ih]->Scale(bg_int);
	  }
	
	gr_mc_merged = makeErrorBand(h_comb,h_sys_up_combSum,h_sys_down_combSum);
	
	gr_mc_merged->SetFillStyle(3002);
	gr_mc_merged->SetFillColor(kGray+3);
	gr_mc_merged->Draw("2SAME");
	
	CMSLABEL();
	if( sel[selid[ih]] != "ALL" ) LABEL(sel[selid[ih]]);
	
	ratioSig(c1,h_data_norm,h_comb,h_sys_down_combSum,h_sys_up_combSum);

	pname = "pics/"+hname[ih]+".eps";
	c1->Print(pname.c_str());
	c1->Clear();

//	c1_1->SetLogy(0);

	delete gr_mc_merged;
	
	delete h_bg;
	delete h_bg_merged;

	delete leg;

	delete h_data_orig;
	delete h_data_norm;
	
	delete c1;
//	delete c1_1;
     }

   fout->Write();   
   fout->Close();
   
   for(int i=0;i<ttbar_n;i++) f_ttbar[i]->Close();
   for(int i=0;i<stop_n;i++) f_stop[i]->Close();
   for(int i=0;i<zjets_n;i++) f_zjets[i]->Close();
   for(int i=0;i<wjets_n;i++) f_wjets[i]->Close();
}

void addbin(TH1F *h)
{   
   // Add overflow and underflow bins
   Int_t x_nbins = h->GetXaxis()->GetNbins();
   h->SetBinContent(1,h->GetBinContent(0)+h->GetBinContent(1));
   h->SetBinError(1,TMath::Sqrt(pow(h->GetBinError(0),2)+pow(h->GetBinError(1),2)));
   h->SetBinContent(x_nbins,h->GetBinContent(x_nbins)+h->GetBinContent(x_nbins+1));
   h->SetBinError(x_nbins,TMath::Sqrt(pow(h->GetBinError(x_nbins),2)+
				      pow(h->GetBinError(x_nbins+1),2)));
   // Set overflow and underflow bins to 0
   h->SetBinContent(0,0.);
   h->SetBinError(0,0.);
   h->SetBinContent(x_nbins+1,0.);
   h->SetBinError(x_nbins+1,0.);
}

void totSys(TH1F *h_nom,TH1F *h_down,TH1F *h_up)
{   
   int nbins = h_nom->GetXaxis()->GetNbins();
   
   for(int ib=1;ib<=nbins;ib++)
     {
	double b_nom = h_nom->GetBinContent(ib);
	double b_cur_down = h_down->GetBinContent(ib);
	double b_cur_up = h_up->GetBinContent(ib);
	
	double del_down = b_cur_down - b_nom;
	double del_up = b_cur_up - b_nom;
	double del_down_res = del_down;
	double del_up_res = del_up;
	
	double del_min = (del_down < del_up) ? del_down : del_up;
	double del_max = (del_down > del_up) ? del_down : del_up;

	del_down_res = (del_min > 0.) ? 0. : del_min;
	del_up_res = (del_max < 0.) ? 0. : del_max;
	
	double sys_down = b_nom + del_down_res;
	double sys_up = b_nom + del_up_res;
	
	h_down->SetBinContent(ib,sys_down);
	h_up->SetBinContent(ib,sys_up);
     }
}

void combSys(TH1F *h_nom,TH1F** h_sys_down,TH1F** h_sys_up,TH1F *h_sys_down_comb,TH1F *h_sys_up_comb,int nSys)
{
   double sys_up[1000];
   double sys_down[1000];
   
   int nBins = h_nom->GetXaxis()->GetNbins();
   
   for(int is=1;is<=nBins;is++)
     {
	sys_up[is-1] = 0.;
	sys_down[is-1] = 0.;
     }      
   
   for(int j=0;j<nSys;j++)
     {
	for(int ib=1;ib<=nBins;ib++)
	  {
	     double nom = h_nom->GetBinContent(ib);
	     double down = h_sys_down[j]->GetBinContent(ib);
	     double up = h_sys_up[j]->GetBinContent(ib);
	     double delta_down = nom - down;
	     double delta_up = up - nom;
	     sys_up[ib-1] = sqrt(pow(sys_up[ib-1],2) + pow(delta_up,2));
	     sys_down[ib-1] = sqrt(pow(sys_down[ib-1],2) + pow(delta_down,2));
	  }
     }      
   
   for(int ib=1;ib<=nBins;ib++)
     {
	double nom = h_nom->GetBinContent(ib);
	double err = h_nom->GetBinError(ib);
	
	sys_up[ib-1] = sqrt(pow(sys_up[ib-1],2) + pow(err,2));
	sys_down[ib-1] = sqrt(pow(sys_down[ib-1],2) + pow(err,2));
     }   
   
   for(int ib=1;ib<=nBins;ib++)
     {		
	double nom = h_nom->GetBinContent(ib);
	h_sys_down_comb->SetBinContent(ib,nom-sys_down[ib-1]);
	h_sys_up_comb->SetBinContent(ib,nom+sys_up[ib-1]);
     }
}

void combSysLinear(std::vector<TH1F*> h_nom,
		   std::vector<TH1F*> h_sys_up,
		   std::vector<TH1F*> h_sys_down,
		   TH1F *h_comb,
		   TH1F *h_sys_down_comb,
		   TH1F *h_sys_up_comb)
{
   double sys_up[1000];
   double sys_down[1000];
   double stat[1000];
   
   int nBins = h_nom.at(0)->GetXaxis()->GetNbins();
   
   for(int is=1;is<=nBins;is++)
     {
	sys_up[is-1] = 0.;
	sys_down[is-1] = 0.;
	stat[is-1] = 0.;
     }

   for(int ib=1;ib<=nBins;ib++)
     {
	double delta_down = 0.;
	double delta_up = 0.;
	
	for(int i=0;i<h_nom.size();i++)
	  {
	     double nom = h_nom[i]->GetBinContent(ib);
	     double up = h_sys_up[i]->GetBinContent(ib);
	     double down = h_sys_down[i]->GetBinContent(ib);
	     double err = h_nom[i]->GetBinError(ib);
	     
	     delta_down += (nom-down);
	     delta_up += (up-nom);
	     
	     stat[ib-1] += pow(err,2);
	  }	
	
	sys_up[ib-1] = sys_up[ib-1] + delta_up;
	sys_down[ib-1] = sys_down[ib-1] + delta_down;

	stat[ib-1] = sqrt(stat[ib-1]);
     }      
   
   for(int ib=1;ib<=nBins;ib++)
     {
	double nom = 0.;
	for(int i=0;i<h_nom.size();i++)
	  {
	     nom += h_nom[i]->GetBinContent(ib);
	  }

	h_comb->SetBinContent(ib,nom);
	h_comb->SetBinError(ib,stat[ib-1]);
	h_sys_down_comb->SetBinContent(ib,nom-sys_down[ib-1]);
	h_sys_up_comb->SetBinContent(ib,nom+sys_up[ib-1]);
     }
}

TGraphAsymmErrors* makeErrorBand(TH1F* tot, TH1F* plus, TH1F* minus)
{
   int nbins = tot->GetNbinsX();
   
   double x[1000];
   double xerr[1000];
   double y[1000];
   double yp[1000];
   double ym[1000];
   
   for(int bin=1;bin<=nbins;++bin)
     {
	int index = bin-1;
	xerr[index] = tot->GetBinWidth(bin)/2.0;
	x[index] = tot->GetBinLowEdge(bin) + xerr[index];
	
	y[index] = tot->GetBinContent(bin);
	yp[index] = plus->GetBinContent(bin)-y[index];
	ym[index] = y[index]-minus->GetBinContent(bin);
	if(y[index] - ym[index] < 0) ym[index] = y[index];
     }
   
   TGraphAsymmErrors* error = new TGraphAsymmErrors(nbins, x, y, xerr, xerr, ym, yp);
   
   return error;
}

void removeMCNeg(TH1F *h1)
{
   int nb = h1->GetXaxis()->GetNbins();
   
   for(int ib=1;ib<=nb;ib++)
     {
	double vb = h1->GetBinContent(ib);
	double ve = h1->GetBinError(ib);
	
	if( vb < 0 || vb <= ve )
	  {
	     h1->SetBinContent(ib,ve);
	     h1->SetBinError(ib,ve);
	  }	
     }   
}

/*void mergeSys(TH1F* h_nom,
	      std::vector<TH1F*> h_sys_up,
	      std::vector<TH1F*> h_sys_down,
	      TH1F *h_sys_down_comb,
	      TH1F *h_sys_up_comb)
{
   int nBins = h_nom->GetXaxis()->GetNbins();
   
   for(int ib=1;ib<=nBins;ib++)
     {	
	float nom = h_nom->GetBinContent(ib);
	
	for(int i=0;i<h_sys_up.size();i++)
	  {
	     float sys_up = h_sys_up[i]->GetBinContent(ib);
	     float sys_down = h_sys_down[i]->GetBinContent(ib);
	     
	     float del_up = sys_up-nom;
	     float del_down = nom-sys_down;
	     
	     
	  }   
     }   
}*/
