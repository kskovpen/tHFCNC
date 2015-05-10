#include "var_comp.h" 

void plot_comp()
{
   gROOT->SetBatch();

   gROOT->ProcessLine(".L addbin.C");
   
   gStyle->SetHistTopMargin(0);
   
   gROOT->SetStyle("Plain");
   
   gStyle->SetOptStat(0);
   
   gROOT->ProcessLine(".x common.C");
   
   TCanvas *c1 = new TCanvas("c1","c1",0,0,600,500);
   
   TFile *f[nf];
   TH1D *h[nf][nh];
   
   for(int ifi=0;ifi<nf;ifi++)
     {	
	std::string fn = "output/"+fname[ifi]+".root";
	f[ifi] = TFile::Open(fn.c_str());
	
	for(int ih=0;ih<nh;ih++)
	  {
	     h[ifi][ih] = (TH1D*)f[ifi]->Get(hname[ih].c_str());
	     addbin(h[ifi][ih]);
	     float integ = h[ifi][ih]->Integral();
	     if( integ > 0. ) h[ifi][ih]->Scale(1./integ);
	  }	
     }   
   
   for(int ih=0;ih<nh;ih++)
     {
	TLegend *leg = new TLegend(0.65,0.90,0.90,0.75);
	leg->SetFillColor(253);
	leg->SetBorderSize(0);
	
	double max = 0.;
	
	for(int ifi=0;ifi<nf;ifi++)
	  {
	     if( ifi == 0 ) 
	       {
		  h[ifi][ih]->SetMarkerSize(0.0);
		  h[ifi][ih]->Draw("hist e1");
		  leg->AddEntry(h[ifi][ih],glab[ifi].c_str(),"l");
		  h[ifi][ih]->GetXaxis()->SetTitle(xtit[ih].c_str());
	       }	     
	     else if( ifi == 1 )
	       {
		  h[ifi][ih]->Draw("hist e1p same");
		  h[ifi][ih]->SetLineColor(kRed);
		  h[ifi][ih]->SetMarkerColor(kRed);
		  h[ifi][ih]->SetMarkerStyle(24);
		  h[ifi][ih]->SetMarkerSize(0.8);
		  h[ifi][ih]->Draw("same");
		  leg->AddEntry(h[ifi][ih],glab[ifi].c_str(),"lp");
	       }	     
	     else if( ifi == 2 )
	       {
		  h[ifi][ih]->Draw("hist e1p same");
		  h[ifi][ih]->SetLineColor(kBlue);
		  h[ifi][ih]->SetMarkerColor(kBlue);
		  h[ifi][ih]->SetMarkerStyle(22);
		  h[ifi][ih]->SetMarkerSize(0.8);
		  h[ifi][ih]->Draw("same");
		  leg->AddEntry(h[ifi][ih],glab[ifi].c_str(),"lp");
	       }
	     
	     double m = h[ifi][ih]->GetMaximum();
	     if( m > max ) max = m;
	  }

	leg->Draw();
	
	h[0][ih]->SetMaximum(1.35*max);
	h[0][ih]->SetMinimum(0.);

/*	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextFont(63);
	t->SetTextSizePixels(22);
	t->DrawLatex(0.4,0.9,alab[ih].c_str());*/
	
	std::string pname = "pics_comp/"+hname[ih]+".eps";
	c1->Print(pname.c_str());
	c1->Clear();
	delete leg;
//	delete t;
     }   
   
   gApplication->Terminate();
}
