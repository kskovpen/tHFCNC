#include "PlotStyle.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "THStack.h"
#include "TMath.h"
#include "TFile.h"
#include "TLegend.h"

#include <vector>
#include <iostream>

void addbin(TH1F*);
double errfMC(double,double,double,double);

int main()
{
   gROOT->SetBatch(1);
   
   SetPlotStyle();

   gStyle->SetOptFit();

   TFile *fout = new TFile("hist.root","RECREATE");
   
   std::vector<std::string> sig_hut_stop;
   std::vector<std::string> sig_hct_stop;
   std::vector<std::string> sig_gut;
   std::vector<std::string> sig_gct;

   std::vector<std::string> sig_hut_ttbar;
   std::vector<std::string> sig_hct_ttbar;
   
   std::vector<std::string> sig_hut;
   std::vector<std::string> sig_hct;
   
   sig_hut_stop.push_back("tHToBB_1L_Kappa_hut");
   sig_hct_stop.push_back("tHToBB_1L_Kappa_hct");
   
   sig_gut.push_back("tHToBB_1L_Kappa_gut");
   sig_gct.push_back("tHToBB_1L_Kappa_gct");
   
   sig_hut_ttbar.push_back("TTtoTHToBB_1L_Kappa_hut");
   sig_hct_ttbar.push_back("TTtoTHToBB_1L_Kappa_hct");

   sig_hut.push_back("tHToBB_1L_Kappa_hut");
   sig_hut.push_back("TTtoTHToBB_1L_Kappa_hut");
   
   sig_hct.push_back("tHToBB_1L_Kappa_hct");
   sig_hct.push_back("TTtoTHToBB_1L_Kappa_hct");   
   
   const int sig_hut_n = sig_hut.size();
   const int sig_hut_stop_n = sig_hut_stop.size();
   const int sig_hut_ttbar_n = sig_hut_ttbar.size();

   const int nmtype = 3;
   std::string mtype[nmtype] =
     {
	"all",
	"pass",
	"fail"
     };
   
   const int nvar = 4;
   std::string var[nvar] =
     {
	"match",
	"H_m",
	"top_m",
	"W_m"	
     };

   const int nalg = 4;
   std::string alg[nalg] =
     {
	"Mbb",
	"MT",
	"MbbMT",
	"Top"
     };

   std::string xtit[nvar] =
     {
	"",
	"m(H) [GeV]",
	"m(top) [GeV]",
	"m(W) [GeV]"
     };
   
   std::string hname[1000];
   int varid[1000];
   
   int idx = 0;
   for(int iv=0;iv<nvar;iv++)
     {
	for(int is=0;is<nalg;is++)
	  {
	     if( iv == 0 ) 
	       {
		  hname[idx] = "h_"+var[iv]+"_"+alg[is];
		  varid[idx] = iv;
		  idx++;
	       }
	     else
	       {	     		  		  
		  for(int it=0;it<nmtype;it++)
		    {
		       hname[idx] = "h_"+var[iv]+"_"+alg[is]+"_"+mtype[it];
		       varid[idx] = iv;
		       idx++;
		    }	     
	       }	     
	  }
     }
   const int hn = idx;
      
   TH1F *h_sig_hut[hn];
   TFile *f_sig_hut[sig_hut_n];

   TH1F *h_sig_hut_stop[hn];
   TFile *f_sig_hut_stop[sig_hut_stop_n];

   TH1F *h_sig_hut_ttbar[hn];
   TFile *f_sig_hut_ttbar[sig_hut_ttbar_n];

   const int nh1 = 2;
   std::string hname1[nh1] = 
     {
	"matchAll",
	"topSol"
     };   
   TH1F *h1_sig_hut[nh1];
   TH1F *h1_sig_hut_stop[nh1];
   TH1F *h1_sig_hut_ttbar[nh1];
   
   for(int i=0;i<sig_hut_n;i++)
     {	
	std::string fname = "../histMERGE/"+sig_hut[i]+".root";
	f_sig_hut[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {
	     std::string hname_clone = hname[ih]+"_clone";
	     TH1F *h = (TH1F*)f_sig_hut[i]->Get(hname[ih].c_str());
	     if( i == 0 )
	       {
		  h_sig_hut[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_sig_hut[ih]->Add(h);
	       }	
	  }	

	for(int ih=0;ih<nh1;ih++)
	  {
	     std::string hn1 = "h_"+hname1[ih];
	     std::string hname_clone = "h_"+hn1+"_clone";
	     TH1F *h = (TH1F*)f_sig_hut[i]->Get(hn1.c_str());
	     if( i == 0 )
	       {
		  h1_sig_hut[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h1_sig_hut[ih]->Add(h);
	       }		
	  }	
     }

   for(int i=0;i<sig_hut_stop_n;i++)
     {	
	std::string fname = "../histMERGE/"+sig_hut_stop[i]+".root";
	f_sig_hut_stop[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {
	     std::string hname_clone = hname[ih]+"_clone";
	     TH1F *h = (TH1F*)f_sig_hut_stop[i]->Get(hname[ih].c_str());
	     if( i == 0 )
	       {
		  h_sig_hut_stop[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_sig_hut_stop[ih]->Add(h);
	       }	
	  }	

	for(int ih=0;ih<nh1;ih++)
	  {
	     std::string hn1 = "h_"+hname1[ih];
	     std::string hname_clone = "h_"+hn1+"_clone";
	     TH1F *h = (TH1F*)f_sig_hut_stop[i]->Get(hn1.c_str());
	     if( i == 0 )
	       {
		  h1_sig_hut_stop[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h1_sig_hut_stop[ih]->Add(h);
	       }		
	  }	
     }

   for(int i=0;i<sig_hut_ttbar_n;i++)
     {	
	std::string fname = "../histMERGE/"+sig_hut_ttbar[i]+".root";
	f_sig_hut_ttbar[i] = TFile::Open(fname.c_str());
	for(int ih=0;ih<hn;ih++)
	  {
	     std::string hname_clone = hname[ih]+"_clone";
	     TH1F *h = (TH1F*)f_sig_hut_ttbar[i]->Get(hname[ih].c_str());
	     if( i == 0 )
	       {
		  h_sig_hut_ttbar[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h_sig_hut_ttbar[ih]->Add(h);
	       }	
	  }	

	for(int ih=0;ih<nh1;ih++)
	  {
	     std::string hn1 = "h_"+hname1[ih];
	     std::string hname_clone = "h_"+hn1+"_clone";
	     TH1F *h = (TH1F*)f_sig_hut_ttbar[i]->Get(hn1.c_str());
	     if( i == 0 )
	       {
		  h1_sig_hut_ttbar[ih] = (TH1F*)h->Clone(hname_clone.c_str());
	       }
	     else
	       {
		  h1_sig_hut_ttbar[ih]->Add(h);
	       }		
	  }	
     }

   fout->cd();
   
   for(int ih=0;ih<nh1;ih++)
     {	   
	TCanvas *c0 = new TCanvas();
	
	addbin(h1_sig_hut[ih]);
	addbin(h1_sig_hut_stop[ih]);
	addbin(h1_sig_hut_ttbar[ih]);

	h1_sig_hut[ih]->SetMarkerSize(0);
	h1_sig_hut[ih]->SetMarkerColor(kRed);
	h1_sig_hut[ih]->SetLineColor(kRed);
	h1_sig_hut[ih]->SetFillColor(0);
	h1_sig_hut[ih]->SetLineWidth(2);

	h1_sig_hut_stop[ih]->SetMarkerSize(0);
	h1_sig_hut_stop[ih]->SetMarkerColor(kRed+1);
	h1_sig_hut_stop[ih]->SetLineColor(kRed+1);
	h1_sig_hut_stop[ih]->SetFillColor(0);
	h1_sig_hut_stop[ih]->SetLineWidth(2);
	
	h1_sig_hut_ttbar[ih]->SetMarkerSize(0);
	h1_sig_hut_ttbar[ih]->SetMarkerColor(kRed-7);
	h1_sig_hut_ttbar[ih]->SetLineColor(kRed-7);
	h1_sig_hut_ttbar[ih]->SetFillColor(0);
	h1_sig_hut_ttbar[ih]->SetLineWidth(2);

	if( ih == 0 )
	  {	     
	     int nBins = h1_sig_hut[ih]->GetXaxis()->GetNbins();
	     float v0_hut_stop = h1_sig_hut_stop[ih]->GetBinContent(1);
	     float v0_hut_ttbar = h1_sig_hut_ttbar[ih]->GetBinContent(1);
	     float err0_hut_stop = h1_sig_hut_stop[ih]->GetBinError(1);
	     float err0_hut_ttbar = h1_sig_hut_ttbar[ih]->GetBinError(1);
	     for(int ib=2;ib<=nBins;ib++)
	       {
		  float v_hut_stop = h1_sig_hut_stop[ih]->GetBinContent(ib);
		  float v_hut_ttbar = h1_sig_hut_ttbar[ih]->GetBinContent(ib);
		  float err_hut_stop = h1_sig_hut_stop[ih]->GetBinError(ib);
		  float err_hut_ttbar = h1_sig_hut_ttbar[ih]->GetBinError(ib);
		  float eff_hut_stop = (v0_hut_stop > 0.) ? v_hut_stop/v0_hut_stop : 0.;
		  float eff_hut_ttbar = (v0_hut_ttbar > 0.) ? v_hut_ttbar/v0_hut_ttbar : 0.;
		  float efferr_hut_stop = (v0_hut_stop > 0.) ? errfMC(v_hut_stop,err_hut_stop,v0_hut_stop,err0_hut_stop) : 0.;
		  float efferr_hut_ttbar = (v0_hut_ttbar > 0.) ? errfMC(v_hut_ttbar,err_hut_ttbar,v0_hut_ttbar,err0_hut_ttbar) : 0.;
		  h1_sig_hut_stop[ih]->SetBinContent(ib,eff_hut_stop);
		  h1_sig_hut_ttbar[ih]->SetBinContent(ib,eff_hut_ttbar);
		  h1_sig_hut_stop[ih]->SetBinError(ib,efferr_hut_stop);
		  h1_sig_hut_ttbar[ih]->SetBinError(ib,efferr_hut_ttbar);
	       }	
	     h1_sig_hut_stop[ih]->GetXaxis()->SetRangeUser(h1_sig_hut_stop[ih]->GetXaxis()->GetBinLowEdge(2),
							   h1_sig_hut_stop[ih]->GetXaxis()->GetBinUpEdge(nBins));
	     h1_sig_hut_ttbar[ih]->GetXaxis()->SetRangeUser(h1_sig_hut_ttbar[ih]->GetXaxis()->GetBinLowEdge(2),
							    h1_sig_hut_ttbar[ih]->GetXaxis()->GetBinUpEdge(nBins));
	     
	     h1_sig_hut_stop[ih]->SetMaximum(1.05);
	     h1_sig_hut_ttbar[ih]->SetMaximum(1.05);
	     h1_sig_hut_stop[ih]->SetMinimum(0.0);
	     h1_sig_hut_ttbar[ih]->SetMinimum(0.0);
	     
	     h1_sig_hut_stop[ih]->GetYaxis()->SetTitle("Efficiency");
	     h1_sig_hut_stop[ih]->GetXaxis()->SetBinLabel(2,"Hb1+Hb2");
	     h1_sig_hut_stop[ih]->GetXaxis()->SetBinLabel(3,"tb");
	     h1_sig_hut_stop[ih]->GetXaxis()->SetBinLabel(4,"Hb1+Hb2+tb");
	  }
	else
	  {
	     h1_sig_hut_stop[ih]->Scale(1./h1_sig_hut_stop[ih]->Integral());
	     h1_sig_hut_ttbar[ih]->Scale(1./h1_sig_hut_ttbar[ih]->Integral());
	  }	
	
	h1_sig_hut_stop[ih]->Draw("hist e1");
	
	h1_sig_hut_ttbar[ih]->Draw("hist e1 same");
   
	TLegend *leg0 = new TLegend(0.20,0.92,0.42,0.70);
	leg0->SetFillColor(253);
	leg0->SetBorderSize(0);
	leg0->AddEntry(h1_sig_hut_stop[ih],"FCNC #kappa_{Hut}","lp");
	leg0->AddEntry(h1_sig_hut_ttbar[ih],"FCNC #kappa_{Hut} (ttbar)","lp");
	leg0->Draw();
	
	std::string pname = "pics/"+hname1[ih]+".eps";
	c0->Print(pname.c_str());
	c0->Clear();
   
	delete leg0;
	delete c0;
     }
   
   for(int ih=0;ih<hn;ih++)
     {
	TCanvas *c1 = new TCanvas();
	
	addbin(h_sig_hut[ih]);
	addbin(h_sig_hut_stop[ih]);
	addbin(h_sig_hut_ttbar[ih]);
	
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

	int itit = varid[ih];
	std::string xtitle = xtit[itit];

	if( varid[ih] == 0 )
	  {	     
	     int nBins = h_sig_hut[ih]->GetXaxis()->GetNbins();
	     float v0_hut_stop = h_sig_hut_stop[ih]->GetBinContent(1);
	     float v0_hut_ttbar = h_sig_hut_ttbar[ih]->GetBinContent(1);
	     float err0_hut_stop = h_sig_hut_stop[ih]->GetBinError(1);
	     float err0_hut_ttbar = h_sig_hut_ttbar[ih]->GetBinError(1);
	     for(int ib=2;ib<=nBins;ib++)
	       {
		  float v_hut_stop = h_sig_hut_stop[ih]->GetBinContent(ib);
		  float v_hut_ttbar = h_sig_hut_ttbar[ih]->GetBinContent(ib);
		  float err_hut_stop = h_sig_hut_stop[ih]->GetBinError(ib);
		  float err_hut_ttbar = h_sig_hut_ttbar[ih]->GetBinError(ib);
		  float eff_hut_stop = (v0_hut_stop > 0.) ? v_hut_stop/v0_hut_stop : 0.;
		  float eff_hut_ttbar = (v0_hut_ttbar > 0.) ? v_hut_ttbar/v0_hut_ttbar : 0.;
		  float efferr_hut_stop = (v0_hut_stop > 0.) ? errfMC(v_hut_stop,err_hut_stop,v0_hut_stop,err0_hut_stop) : 0.;
		  float efferr_hut_ttbar = (v0_hut_ttbar > 0.) ? errfMC(v_hut_ttbar,err_hut_ttbar,v0_hut_ttbar,err0_hut_ttbar) : 0.;
		  h_sig_hut_stop[ih]->SetBinContent(ib,eff_hut_stop);
		  h_sig_hut_ttbar[ih]->SetBinContent(ib,eff_hut_ttbar);
		  h_sig_hut_stop[ih]->SetBinError(ib,efferr_hut_stop);
		  h_sig_hut_ttbar[ih]->SetBinError(ib,efferr_hut_ttbar);
	       }	
	     h_sig_hut_stop[ih]->GetXaxis()->SetRangeUser(h_sig_hut_stop[ih]->GetXaxis()->GetBinLowEdge(2),
							  h_sig_hut_stop[ih]->GetXaxis()->GetBinUpEdge(nBins));
	     h_sig_hut_ttbar[ih]->GetXaxis()->SetRangeUser(h_sig_hut_ttbar[ih]->GetXaxis()->GetBinLowEdge(2),
							   h_sig_hut_ttbar[ih]->GetXaxis()->GetBinUpEdge(nBins));
	     
	     h_sig_hut_stop[ih]->SetMaximum(1.05);
	     h_sig_hut_ttbar[ih]->SetMaximum(1.05);
	     h_sig_hut_stop[ih]->SetMinimum(0.0);
	     h_sig_hut_ttbar[ih]->SetMinimum(0.0);
	     
	     h_sig_hut_stop[ih]->GetYaxis()->SetTitle("Truth efficiency");
	     h_sig_hut_stop[ih]->GetXaxis()->SetBinLabel(2,"Hb1+Hb2");
	     h_sig_hut_stop[ih]->GetXaxis()->SetBinLabel(3,"tb");
	     h_sig_hut_stop[ih]->GetXaxis()->SetBinLabel(4,"Hb1+Hb2+tb");
	  }
	else
	  {
	     float int_hut_stop = h_sig_hut_stop[ih]->Integral();
	     h_sig_hut_stop[ih]->Scale(1./int_hut_stop);
	     float int_hut_ttbar = h_sig_hut_ttbar[ih]->Integral();
	     h_sig_hut_ttbar[ih]->Scale(1./int_hut_ttbar);
	     float max = std::max(h_sig_hut_stop[ih]->GetMaximum(),h_sig_hut_ttbar[ih]->GetMaximum());
	     h_sig_hut_stop[ih]->SetMaximum(1.2*max);
	  }	

	h_sig_hut_stop[ih]->GetXaxis()->SetTitle(xtitle.c_str());
	
	h_sig_hut_stop[ih]->Draw("hist e1");

	h_sig_hut_ttbar[ih]->Draw("hist e1 same");
	
	TLegend *leg = new TLegend(0.20,0.92,0.42,0.70);
	leg->SetFillColor(253);
	leg->SetBorderSize(0);
	leg->AddEntry(h_sig_hut_stop[ih],"FCNC #kappa_{Hut}","lp");
	leg->AddEntry(h_sig_hut_ttbar[ih],"FCNC #kappa_{Hut} (ttbar)","lp");
	leg->Draw();
	
	std::string pname = "pics/"+hname[ih]+".eps";
	c1->Print(pname.c_str());
	c1->Clear();

	delete leg;
	delete c1;
     }

   fout->Write();   
   fout->Close();
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

double errfMC(double v1,double ve1,double v2,double ve2)
{
   if( v2 == 0 ) return -666;

   double err = pow(v2-v1,2)*ve1*ve1/pow(v2,4) +
     v1*v1*(ve2*ve2-ve1*ve1)/pow(v2,4);

   err = sqrt(err);

   return err;
}
