#include "PlotStyle.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"
#include "TMath.h"
#include "TFile.h"
#include "TLegend.h"

#include <vector>
#include <iostream>

int main()
{
   SetPlotStyle();

   std::string coup = "Hut";
   std::string cat[5] = {"b2j3","b2j4","b3j3","b3j4","b4j4"};

   TFile *f = TFile::Open("histTEST.root","READ");
   
   for(int icat=0;icat<5;icat++)
     {	   
	//std::string hname = "bg_h_MVA"+coup+"_all_"+cat[icat]+"_ALL_merged_IL";
	std::string hname = "sig_hut_stop_h_MVA"+coup+"_all_"+cat[icat]+"_ALL";
	std::string hname2 = "sig_hut_ttbar_h_MVA"+coup+"_all_"+cat[icat]+"_ALL";
	TH1F *h = (TH1F*)f->Get(hname.c_str());
	TH1F *h_2 = (TH1F*)f->Get(hname2.c_str());
	h->Add(h_2);
	
	TCanvas *c1 = new TCanvas("c1","c1",0,0,600,500);

	float xbins[7] = {-0.8,-0.4,-0.2,0,0.2,0.4,0.8};
	
	TH2D *h2 = new TH2D("h2","h2",6,xbins,6,xbins);

	for(int i=0;i<6;i++)
	  {
	     h2->SetBinContent(1,6-i,h->GetBinContent(1+i*6));
	     h2->SetBinContent(2,6-i,h->GetBinContent(2+i*6));
	     h2->SetBinContent(3,6-i,h->GetBinContent(3+i*6));
	     h2->SetBinContent(4,6-i,h->GetBinContent(4+i*6));
	     h2->SetBinContent(5,6-i,h->GetBinContent(5+i*6));
	     h2->SetBinContent(6,6-i,h->GetBinContent(6+i*6));
	  }   
	
	h2->Draw("COLZ");
	
	std::string xaxisTit = "MVA"+coup+"ST";
	std::string yaxisTit = "MVA"+coup+"TT";
	
	h2->GetXaxis()->SetTitle(xaxisTit.c_str());
	h2->GetYaxis()->SetTitle(yaxisTit.c_str());
	
	std::cout << h2->GetCorrelationFactor() << std::endl;

	std::string pname = "pics/h_MVA"+coup+"2D_all_"+cat[icat]+"_ALL.eps";
	c1->Print(pname.c_str());
	c1->Clear();
	delete c1;
	delete h2;
     }   
}   
