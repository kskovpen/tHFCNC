#include <iostream>

#include "ratioSig.h"

#include "TGraphAsymmErrors.h"

void ratioSig(TCanvas *c1, TH1F* h1, TH1F* h2, TH1F *h2_low, TH1F *h2_up)
{
   TH1F* h2e = (TH1F*)h2->Clone("h2e");

   TH1F* h1c = (TH1F*)h1->Clone("h1c");
   
   TH1F* h2e_low = (TH1F*)h2_low->Clone("h2e_low");
   TH1F* h2e_up = (TH1F*)h2_up->Clone("h2e_up");
   
   const int s = 1000;
   
   double x[s];
   double xerr[s];
   double y[s];
   double yp[s];
   double ym[s];
   
   std::string hName = h1->GetName();
   
   int nbins = h1->GetXaxis()->GetNbins();
   
   for(int ib=1;ib<=nbins;ib++)
     {
	int index = ib-1;
	
	double dat = h1c->GetBinContent(ib);
	double datErr = h1c->GetBinError(ib);
	double nom = h2e->GetBinContent(ib);
	double delp = h2e_up->GetBinContent(ib)-nom;
	double delm = nom-h2e_low->GetBinContent(ib);
	
	double sig = 0.;
	
	if( dat >= nom )
	  sig += pow(delp,2.);
	else
	  sig += pow(delm,2.);
	
	sig += pow(datErr,2.);
	sig = sqrt(sig);
	
	double signif = (sig != 0.) ? (dat-nom)/sig : 0.;

	xerr[index] = h2e->GetBinWidth(ib)/2.0;
	x[index] = h2e->GetBinLowEdge(ib) + xerr[index];
	
	if( signif > 0. )
	  {	     
	     y[index] = 0.;
	     yp[index] = signif;
	     ym[index] = 0.;
	  }
	else
	  {
	     if( signif <= -5. ) signif = -5.;
	     y[index] = signif;
	     yp[index] = -signif;
	     ym[index] = 0.;
	  }
     }
   
   c1->cd();
   TPad *c1_2 = new TPad("c1_2", "ratio",0.01,0.01,0.99,0.37);
   c1_2->Draw();
   c1_2->cd();  
   c1_2->SetBottomMargin(0.37);
   c1_2->SetGrid(0,1);
   
   h1c->SetMarkerSize(0);
   h1c->SetLineWidth(0);
   h1c->GetYaxis()->SetNdivisions(5);
   h1c->GetYaxis()->SetTitle("#frac{Data-MC}{#sqrt{#sigma_{Data}^{2}+#sigma_{MC}^{2}}}");
   
   h1c->GetYaxis()->SetTitleSize((h1c->GetYaxis()->GetTitleSize())*2);
   h1c->GetYaxis()->SetTitleOffset(h1c->GetYaxis()->GetTitleOffset()/2);
   h1c->GetXaxis()->SetTitleSize((h1c->GetXaxis()->GetTitleSize())*2);
   h1c->GetXaxis()->SetTitleOffset(h1c->GetXaxis()->GetTitleOffset()+0.2);

   h1c->GetYaxis()->SetLabelSize((h1c->GetYaxis()->GetLabelSize())*2);
   h1c->GetXaxis()->SetLabelSize((h1c->GetXaxis()->GetLabelSize())*2);

   h1c->GetXaxis()->SetTitle(h1c->GetXaxis()->GetTitle());

   if( hName == "data_h_PassSel9_all_ALL_ALL_norm" ||
       hName == "data_h_PassSel9_e_ALL_ALL_norm" ||
       hName == "data_h_PassSel9_m_ALL_ALL_norm" )
     {
	h1c->GetXaxis()->SetBinLabel(1,"(nj=3,nb=0)");
	h1c->GetXaxis()->SetBinLabel(2,"(nj>3,nb=0)");
	h1c->GetXaxis()->SetBinLabel(3,"(nj=3,nb=1)");
	h1c->GetXaxis()->SetBinLabel(4,"(nj>3,nb=1)");
	h1c->GetXaxis()->SetBinLabel(5,"(nj=3,nb=2)");
	h1c->GetXaxis()->SetBinLabel(6,"(nj>3,nb=2)");
	h1c->GetXaxis()->SetBinLabel(7,"(nj=3,nb=3)");
	h1c->GetXaxis()->SetBinLabel(8,"(nj>3,nb=3)");
	h1c->GetXaxis()->SetBinLabel(9,"(nj>3,nb=4)");
     }

   if( hName == "data_h_PassSel5_all_ALL_ALL_norm" ||
       hName == "data_h_PassSel5_e_ALL_ALL_norm" ||
       hName == "data_h_PassSel5_m_ALL_ALL_norm" )
     {
	h1c->GetXaxis()->SetBinLabel(1,"(nj=3,nb=2)");
	h1c->GetXaxis()->SetBinLabel(2,"(nj>3,nb=2)");
	h1c->GetXaxis()->SetBinLabel(3,"(nj=3,nb=3)");
	h1c->GetXaxis()->SetBinLabel(4,"(nj>3,nb=3)");
	h1c->GetXaxis()->SetBinLabel(5,"(nj>3,nb=4)");
     }
   
   TGraphAsymmErrors* gr_signif = new TGraphAsymmErrors(nbins, x, y, xerr, xerr, ym, yp);
   gr_signif->SetFillColor(29);

   h1c->Reset();
   h1c->Draw("e1");
   
   gr_signif->Draw("2SAME");

   gPad->RedrawAxis("g");
   
   h1c->GetYaxis()->SetRangeUser(-5.0,5.0);

   c1_2->Update();
}
