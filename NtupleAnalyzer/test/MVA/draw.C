#include <algorithm>

void setStyle()
{
   gROOT->SetStyle("Plain");
  
   gStyle->SetOptTitle(0);
   
   gStyle->SetTitleSize(0.05593);
   gStyle->SetTitleSize(0.05,"xyz");
   gStyle->SetLabelSize(0.047,"xyz");
   gStyle->SetTitleFont(132,"xyz");
   gStyle->SetTitleFont(132,"t");
   gStyle->SetLabelFont(132,"xyz");
   gStyle->SetTitleYOffset(1.2);

   gStyle->SetHistLineWidth(1);
   
   gStyle->SetTitleBorderSize(0);
   gStyle->SetNdivisions(505,"xyz");
   gStyle->SetOptStat(0000);
   gStyle->SetPadBottomMargin(0.14);
   gStyle->SetPadLeftMargin(0.14);
   gStyle->SetPalette(1);
   
   gStyle->SetLineColor(0);
   
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerSize(0.5);
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetErrorX(0.000001);
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerSize(1.1);
   gStyle->SetHistLineWidth(2.);
   gROOT->ForceStyle();   
}


void draw()
{
   gROOT->SetBatch(1);

   setStyle();
   
   gROOT->ProcessLine(".L /home/kskovpen/plugins/atlasstyle-00-03-04/AtlasStyle.C");
   
   SetAtlasStyle();
   
   TFile f("TMVA.root");

   TH1D *h_sig_train = (TH1D*)f.Get("Method_BDT/BDT/MVA_BDT_Train_S");
   TH1D *h_bkg_train = (TH1D*)f.Get("Method_BDT/BDT/MVA_BDT_Train_B");

   TH1D *h_sig_test = (TH1D*)f.Get("Method_BDT/BDT/MVA_BDT_S");
   TH1D *h_bkg_test = (TH1D*)f.Get("Method_BDT/BDT/MVA_BDT_B");
   
   TCanvas *c1 = new TCanvas();
   
   h_sig_train->SetLineColor(kRed-4);
   h_sig_train->SetMarkerSize(0.7);
   h_sig_train->SetMarkerStyle(20);
   h_sig_train->SetMarkerColor(kRed-4);
   h_sig_test->SetLineColor(kRed-4);
   h_sig_test->SetMarkerSize(0.0);
//   h_sig_test->SetFillColor(kRed-4);
//   h_sig_test->SetFillStyle(3354);

   h_bkg_train->SetLineColor(kBlue-6);
   h_bkg_train->SetMarkerSize(0.7);
   h_bkg_train->SetMarkerStyle(22);
   h_bkg_train->SetMarkerColor(kBlue-6);
   h_bkg_test->SetLineColor(kBlue-6);
   h_bkg_test->SetMarkerSize(0.0);
   h_bkg_test->SetFillColor(kBlue-10);

   gStyle->SetHatchesSpacing(2.0);
   
   h_bkg_test->Draw("hist e1");
   h_sig_test->Draw("hist e1 same");
   
   h_sig_train->Draw("e1 same");
   h_bkg_train->Draw("e1 same");

   double max_sig_test = h_sig_test->GetMaximum();
   double max_bkg_test = h_bkg_test->GetMaximum();
   double max_sig_train = h_sig_train->GetMaximum();
   double max_bkg_train = h_bkg_train->GetMaximum();
   
   double max_test = std::max(max_sig_test,max_bkg_test);
   double max_train = std::max(max_sig_train,max_bkg_train);
   double max = std::max(max_test,max_train);
   
   h_bkg_test->SetMaximum(1.2*max);
   
   h_bkg_test->GetXaxis()->SetTitle("MVA output");
   h_bkg_test->GetYaxis()->SetTitle("(1/N) dN/dx");

   TLegend *leg0 = new TLegend(0.20,0.92,0.42,0.70);
   leg0->SetFillColor(253);
   leg0->SetBorderSize(0);
   leg0->AddEntry(h_sig_train,"Signal (train)","l");
   leg0->AddEntry(h_bkg_train,"Background (train)","l");
   leg0->AddEntry(h_sig_test,"Signal (test)","f");
   leg0->AddEntry(h_bkg_test,"Background (test)","f");
   leg0->Draw();
   
   c1->Print("pics/disc.eps");
   c1->Clear();   
   
   TH1D *h_S = (TH1D*)h_bkg_test->Clone("h_S");
   h_S->Clear();
   float maxSign = -1.;
   int nBins = h_S->GetXaxis()->GetNbins();
   for(int i=1;i<=nBins;i++)
     {
	float errSig;
	float errBkg;
	float intSig = h_sig_test->IntegralAndError(i,nBins,errSig);
	float intBkg = h_bkg_test->IntegralAndError(i,nBins,errBkg);
	float sign = intSig/sqrt(intBkg+intSig);
	h_S->SetBinContent(i,sign);
	h_S->SetBinError(i,0.);
	if( sign > maxSign ) maxSign = sign;
     }
   
   h_S->GetYaxis()->SetTitle("S/#sqrt{S+B}");
   h_S->Draw("hist e1");
   h_S->SetMaximum(maxSign*1.2);
   h_S->SetMinimum(0.0);
//   h_S->SetMaximum(3.9);
//   h_S->SetMinimum(3.8);
//   h_S->SetMaximum(3.7);
//   h_S->SetMinimum(3.6);
   c1->Print("pics/sign.eps");
   c1->Clear();

   f.Close();
   
   gApplication->Terminate();
}
