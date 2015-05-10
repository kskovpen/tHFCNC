#include <iostream>

void setStyle(){
  gROOT->SetStyle("Plain");
  
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

void plot(){

   gROOT->SetBatch();
   
   setStyle();

   std::string intL = "10";
   std::string ener = "13";
   std::string chan = "e+#mu";
   bool drawObs = 0;

   const int nMax = 1000;
   double co[nMax];
   
   double xsecAt1 = 55.74;
   double medAt1 = 0.0604681;
   double s2mAt1 = 0.00799945;
   double s1mAt1 = 0.020216;
   double s1pAt1 = 0.103752;
   double s2pAt1 = 0.156204;
   
   double coupMin = 0.05.;
   double coupMax = 1.;
   const int nrm = 30;

   double med[nMax],s2p[nMax],s1p[nMax],s1m[nMax],s2m[nMax],obs[nMax],
     xsec[nMax];   
   
   double step = (coupMax-coupMin)/double(nrm);
   for(int i=0;i<nrm;i++)
     {
	co[i] = coupMin+step*i;
	double fac = co[i]*co[i];
	xsec[i] = xsecAt1*fac;
	med[i] = medAt1;
	s2m[i] = s2mAt1;
	s1m[i] = s1mAt1;
	s1p[i] = s1pAt1;
	s2p[i] = s2pAt1;
	obs[i] = med[i];
     }   
   
   double *coup = &co;
   double *theory_xsec = &xsec;
   double *mel = &med;
   double *sig1_p = &s1p;
   double *sig1_n = &s1m;
   double *sig2_p = &s2p;
   double *sig2_n = &s2m;
   double *data = &obs;

   const int nel = nrm*2+1;
   double x[nel], y2_p[nel], y2_n[nel], y1_p[nel], y1_n[nel], mel2[nrm], data2[nrm];
   
   for(int i=0;i<nrm;i++)
     {	
	mel2[i] = mel[i] * xsecAt1;
	data2[i] = data[i] * xsecAt1;

	x[i] = coup[i];
	x[nrm+i] = coup[nrm-1-i];

	y2_p[i] = sig2_p[i] * xsecAt1;
	y2_p[nrm+i] = mel[nrm-1-i] * xsecAt1;

	y2_n[i] = sig2_n[i] * xsecAt1;
	y2_n[nrm+i] = mel[nrm-1-i] * xsecAt1;

	y1_p[i] = sig1_p[i] * xsecAt1;
	y1_p[nrm+i] = mel[nrm-1-i] * xsecAt1;
	
	y1_n[i] = sig1_n[i] * xsecAt1;
	y1_n[nrm+i] = mel[nrm-1-i] * xsecAt1;
     }
      
   x[int(nrm*2)] = coup[0];
   y2_p[int(nrm*2)] = sig2_p[0] * xsecAt1;
   y2_n[int(nrm*2)] = sig2_n[0] * xsecAt1;
   y1_p[int(nrm*2)] = sig1_p[0] * xsecAt1;
   y1_n[int(nrm*2)] = sig1_n[0] * xsecAt1;
   
   TCanvas *c1 = new TCanvas();

   TGraph *g_mel = new TGraph(nrm,coup,mel2);
   g_mel->SetTitle("");
   g_mel->SetLineColor(kBlack);
   g_mel->SetLineWidth(2);
   g_mel->Draw("AL");
   g_mel->SetMaximum(10000);
   g_mel->SetMinimum(0.01);

   TGraph *g_data = new TGraph(nrm,coup,data2);
   g_data->SetTitle("");
   g_data->SetLineColor(kRed);
   g_data->SetLineWidth(2);

   TGraph *g_theory = new TGraph(nrm,coup,theory_xsec);
   g_theory->SetTitle("");
   g_theory->SetLineColor(kBlack);
   g_theory->SetLineStyle(2);
   g_theory->SetLineWidth(2);
   
   TPolyLine *pl2_p = new TPolyLine(nel,x,y2_p);
   pl2_p->SetFillColor(kYellow);
   pl2_p->Draw("fSAME");

   TPolyLine *pl2_n = new TPolyLine(nel,x,y2_n);
   pl2_n->SetFillColor(kYellow);
   pl2_n->Draw("fSAME");

   TPolyLine *pl1_p = new TPolyLine(nel,x,y1_p);
   pl1_p->SetFillColor(kGreen);
   pl1_p->Draw("fSAME");

   TPolyLine *pl1_n = new TPolyLine(nel,x,y1_n);
   pl1_n->SetFillColor(kGreen);
   pl1_n->Draw("fSAME");
   
   g_mel->Draw("L");
   g_mel->GetXaxis()->SetTitle("#font[52]{#kappa_{Hut}}");
   g_mel->GetYaxis()->SetTitle("#sigma [pb]");

   if( drawObs )
     g_data->Draw("L");
   
   g_theory->Draw("L");
   
   TLegend *l1 = new TLegend(0.68,0.64,0.87,0.83);
   l1->SetLineColor(0);
   l1->AddEntry(g_mel,"Expected","l");
   l1->AddEntry(g_theory,"Theory","l");
   l1->AddEntry(pl1_p,"68%","f");
   l1->AddEntry(pl2_p,"95%","f");
   
   if( drawObs )
     l1->AddEntry(g_data,"Observed","l");
   
   l1->SetFillColor(0);
   std::string intLLab = "#intLdt = "+intL+" fb^{-1}";
   l1->SetHeader(intLLab.c_str());
   l1->Draw("SAME");

   TLatex lEner;
   lEner.SetTextSize(0.044);
   lEner.SetNDC();
   lEner.SetTextColor(kBlack);
   std::string enerLab = "#font[42]{#sqrt[]{s} = "+ener+" TeV}";
   lEner.DrawLatex(0.45,0.80,enerLab.c_str());
   
   c1->SetLogy(1);
   c1->GetFrame()->SetFillColor(kWhite);
   c1->Update();
   c1->Draw();   
   c1->Print("pics/limit.eps");
   
   gApplication->Terminate();
}
