#include "TROOT.h"
#include "TFile.h"
#include "TLine.h"
#include "TLegend.h"
#include "TH2.h"
#include "Riostream.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TRandom.h"
#include "TParameter.h"

#include "atlasstyle-00-03-04/AtlasStyle.h"
#include "atlasstyle-00-03-04/AtlasUtils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <math.h>

int main(int argc, char *argv[])
{
   if( argc < 2 )
     {
	std::cout << "Usage : nup" << std::endl;
	std::cout << "--file: input filename" << std::endl;
	exit(1);
     }   
   
   char *fname_str = "test.root";

   std::string proc = "ZJETS";
   std::string dist = "mlljj";
   std::string chan = "ee_ss";
   std::string nj = "jge1";
   std::string sel = "ge_mll110_ge_mlljj400";
   std::string hnameNOM = "h_"+proc+"_"+dist+"_"+chan+"_"+nj+"_"+sel;
   std::cout << hnameNOM << std::endl;
   std::string hnameJESUP = hnameNOM + "_jesUp";
   std::string hnameJESDOWN = hnameNOM + "_jesDown";
   std::string hnameJESUP3S = "sample_1_sys_jes_p_extrap_s_30";
   std::string hnameJESDOWN3S = "sample_1_sys_jes_n_extrap_s_30";
   
   for(int i=0;i<argc;i++)
     {
	if( ! strcmp(argv[i],"--file") ) fname_str = argv[i+1];
     }
   
   const char *fname  = fname_str;
   
   std::cout << "--file=" << fname << std::endl;

   gROOT->ProcessLine(".L atlasstyle-00-03-04/AtlasStyle.C");
   gROOT->ProcessLine(".L atlasstyle-00-03-04/AtlasUtils.C");
   gROOT->ProcessLine(".L atlasstyle-00-03-04/AtlasLabels.C");

   SetAtlasStyle();
   
   TFile *f = new TFile(fname);
   TH1D *hNOM = (TH1D*)f->Get(hnameNOM.c_str());
   TH1D *hJESUP = (TH1D*)f->Get(hnameJESUP.c_str());
   TH1D *hJESDOWN = (TH1D*)f->Get(hnameJESDOWN.c_str());
   TH1D *hJESUP3S = (TH1D*)f->Get(hnameJESUP3S.c_str());
   TH1D *hJESDOWN3S = (TH1D*)f->Get(hnameJESDOWN3S.c_str());

   TH1D *hNOMCLEAN = (TH1D*)hNOM->Clone("hNOMCLEAN");
   hNOMCLEAN->Reset();
   TGraphAsymmErrors *hJESUPEX;
   TGraphAsymmErrors *hJESDOWNEX;
   TGraphAsymmErrors *hJESUPEX3S;
   TGraphAsymmErrors *hJESDOWNEX3S;
   
   const int nb = hNOM->GetXaxis()->GetNbins();
   double vNOM[nb];
   double vJESUP[nb];
   double vJESDOWN[nb];
   double vJESUP3S[nb];
   double vJESDOWN3S[nb];

   double vJESUPerr[nb];
   double vJESDOWNerr[nb];
   
   double vX[nb];
   double vXerr[nb];
   
   TCanvas *c1 = new TCanvas();
   hNOMCLEAN->Draw();
   hNOMCLEAN->GetYaxis()->SetRangeUser(0.1,100.);
   hNOMCLEAN->GetXaxis()->SetTitle("Variable");
   hNOMCLEAN->GetYaxis()->SetTitle("#pmN#sigma/A");
   c1->SetLogy(1);
   
   for(int i=1;i<=nb;i++)
     {
	vX[i-1] = hNOM->GetBinCenter(i);
	vXerr[i-1] = 10E-10;
	
	vNOM[i-1] = hNOM->GetBinContent(i);
	vJESUP[i-1] = hJESUP->GetBinContent(i);
	vJESDOWN[i-1] = hJESDOWN->GetBinContent(i);
	vJESUP[i-1] = (vNOM[i-1] > 0.) ? vJESUP[i-1]/vNOM[i-1] : 0.;
	vJESDOWN[i-1] = (vNOM[i-1] > 0.) ? vJESDOWN[i-1]/vNOM[i-1] : 0.;
	vJESUP3S[i-1] = hJESUP3S->GetBinContent(i);
	vJESDOWN3S[i-1] = hJESDOWN3S->GetBinContent(i);
	vJESUP3S[i-1] = (vNOM[i-1] > 0.) ? vJESUP3S[i-1]/vNOM[i-1] : 0.;
	vJESDOWN3S[i-1] = (vNOM[i-1] > 0.) ? vJESDOWN3S[i-1]/vNOM[i-1] : 0.;
	
	vJESUPerr[i-1] = 10E-10;
	vJESDOWNerr[i-1] = 10E-10;
     }   
   
   hJESUPEX = new TGraphAsymmErrors(nb,vX,vJESUP,vXerr,vJESUPerr);
   hJESDOWNEX = new TGraphAsymmErrors(nb,vX,vJESDOWN,vXerr,vJESDOWNerr);
   hJESUPEX3S = new TGraphAsymmErrors(nb,vX,vJESUP3S,vXerr,vJESUPerr);
   hJESDOWNEX3S = new TGraphAsymmErrors(nb,vX,vJESDOWN3S,vXerr,vJESDOWNerr);

   TLine *lone = new TLine(hNOM->GetXaxis()->GetBinLowEdge(1),1.,hNOM->GetXaxis()->GetBinUpEdge(nb),1.);
   lone->SetLineWidth(2);
   lone->SetLineStyle(2);

   TLegend *leg = new TLegend(0.75,0.7,0.9,0.9);
   leg->SetFillStyle(253);
   
   // JES
     {	
	hJESUPEX->Draw("PLS");
	hJESDOWNEX->Draw("PLS");
	hJESUPEX->SetMarkerStyle(20);
	hJESDOWNEX->SetMarkerStyle(20);
	hJESDOWNEX->SetMarkerColor(kBlue);
	hJESDOWNEX->SetLineColor(kBlue);

	hJESUPEX3S->Draw("PLS");
	hJESDOWNEX3S->Draw("PLS");
	hJESUPEX3S->SetLineStyle(2);
	hJESDOWNEX3S->SetLineStyle(2);
	hJESUPEX3S->SetMarkerStyle(21);
	hJESDOWNEX3S->SetMarkerStyle(21);
	hJESDOWNEX3S->SetMarkerColor(kBlue);
	hJESDOWNEX3S->SetLineColor(kBlue);
	
	lone->Draw("same");
	leg->AddEntry(hJESUPEX3S,"+3#sigma","lp");
	leg->AddEntry(hJESUPEX,"+#sigma","lp");
	leg->AddEntry(hJESDOWNEX,"-#sigma","lp");
	leg->AddEntry(hJESDOWNEX3S,"-3#sigma","lp");
	leg->Draw("same");
	std::string fsave = "pics/"+hnameNOM+"_JES.eps";
	c1->Print(fsave.c_str());
     }   
	
   f->Close();
}
