
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

void plot_single(){

   gROOT->SetBatch();
   
   setStyle();   
   
   float nr_mass[11] = {150,250,350,425,500,575,650,725,775,925,975};
   float theory_xsec[11] = {16.39,1.70,0.314,0.1004,0.0338,0.0118,0.00424,0.00156,0.000813,0.0001359,0.0000805};
   
   float mel[11] = {0.00188144,0.00784338,0.0280885,0.0686625,0.177413,0.387879,1.04078,3.19776,9.3576,81.769,120.604};
   float sig1_p[11] = {0.00279415,0.0109298,0.0413433,0.102599,0.252596,0.544603,1.41799,4.11737,12.9578,110.404,162.959};
   float sig1_n[11] = {0.0014633,0.0057316,0.0205155,0.0547692,0.130658,0.304011,0.856257,2.52275,7.25047,58.5176,89.7426};
   float sig2_p[11] = {0.00492235,0.0187739,0.0624268,0.159858,0.356062,0.74379,2.06871,5.51644,17.043,150.633,209.703};
   float sig2_n[11] = {0.000969426,0.00415203,0.0180576,0.0413966,0.108793,0.262633,0.751429,2.24278,6.31532,47.3164,67.7214};
   
   float data[11] = {0.0011156,0.00433053,0.0248151,0.0761417,0.139379,0.537727,2.20551,3.70125,16.2044,82.9496,158.923};

   float x[9], y2_p[9], y2_n[9], y1_p[9], y1_n[9], mel2[11], data2[11];
   
   mel2[0] = mel[0] * theory_xsec[0];
   mel2[1] = mel[1] * theory_xsec[1];
   mel2[2] = mel[2] * theory_xsec[2];
   mel2[3] = mel[3] * theory_xsec[3];
   mel2[4] = mel[4] * theory_xsec[4];
   mel2[5] = mel[5] * theory_xsec[5];
   mel2[6] = mel[6] * theory_xsec[6];
   mel2[7] = mel[7] * theory_xsec[7];
   mel2[8] = mel[8] * theory_xsec[8];
   mel2[9] = mel[9] * theory_xsec[9];
   mel2[10] = mel[10] * theory_xsec[10];
   mel2[11] = mel[11] * theory_xsec[11];

   data2[0] = data[0] * theory_xsec[0];
   data2[1] = data[1] * theory_xsec[1];
   data2[2] = data[2] * theory_xsec[2];
   data2[3] = data[3] * theory_xsec[3];
   data2[4] = data[4] * theory_xsec[4];
   data2[5] = data[5] * theory_xsec[5];
   data2[6] = data[6] * theory_xsec[6];
   data2[7] = data[7] * theory_xsec[7];
   data2[8] = data[8] * theory_xsec[8];
   data2[9] = data[9] * theory_xsec[9];
   data2[10] = data[10] * theory_xsec[10];
   data2[11] = data[11] * theory_xsec[11];
   
   for(int i=0;i<nrm;i++)
     {	
   x[0] = nr_mass[0];
   x[1] = nr_mass[1];
   x[2] = nr_mass[2];
   x[3] = nr_mass[3];
   x[4] = nr_mass[3];
   x[5] = nr_mass[2];
   x[6] = nr_mass[1];
   x[7] = nr_mass[0];
   x[8] = nr_mass[0];
   
   y2_p[0] = sig2_p[0] * theory_xsec[0];
   y2_p[1] = sig2_p[1] * theory_xsec[1];
   y2_p[2] = sig2_p[2] * theory_xsec[2];
   y2_p[3] = sig2_p[3] * theory_xsec[3];
   y2_p[4] = mel2[3];
   y2_p[5] = mel2[2];
   y2_p[6] = mel2[1];
   y2_p[7] = mel2[0];
   y2_p[8] = sig2_p[0] * theory_xsec[0];

   y2_n[0] = sig2_n[0] * theory_xsec[0];
   y2_n[1] = sig2_n[1] * theory_xsec[1];
   y2_n[2] = sig2_n[2] * theory_xsec[2];
   y2_n[3] = sig2_n[3] * theory_xsec[3];
   y2_n[4] = mel2[3];
   y2_n[5] = mel2[2];
   y2_n[6] = mel2[1];
   y2_n[7] = mel2[0];
   y2_n[8] = sig2_n[0] * theory_xsec[0];

   y1_p[0] = sig1_p[0] * theory_xsec[0];
   y1_p[1] = sig1_p[1] * theory_xsec[1];
   y1_p[2] = sig1_p[2] * theory_xsec[2];
   y1_p[3] = sig1_p[3] * theory_xsec[3];
   y1_p[4] = mel2[3];
   y1_p[5] = mel2[2];
   y1_p[6] = mel2[1];
   y1_p[7] = mel2[0];
   y1_p[8] = sig1_p[0] * theory_xsec[0];

   y1_n[0] = sig1_n[0] * theory_xsec[0];
   y1_n[1] = sig1_n[1] * theory_xsec[1];
   y1_n[2] = sig1_n[2] * theory_xsec[2];
   y1_n[3] = sig1_n[3] * theory_xsec[3];
   y1_n[4] = mel2[3];
   y1_n[5] = mel2[2];
   y1_n[6] = mel2[1];
   y1_n[7] = mel2[0];
   y1_n[8] = sig1_n[0] * theory_xsec[0];
   
   TCanvas *c1 = new TCanvas();

   TGraph *g_mel = new TGraph(4,nr_mass,mel2);
   g_mel->SetTitle("");
   g_mel->SetLineColor(kBlack);
   g_mel->SetLineWidth(2);
   g_mel->Draw("AL");
   g_mel->SetMaximum(20);
   g_mel->SetMinimum(0.05);

   TGraph *g_data = new TGraph(4,nr_mass,data2);
   g_data->SetTitle("");
   g_data->SetLineColor(kRed);
   g_data->SetLineWidth(2);

   TGraph *g_theory = new TGraph(4,nr_mass,theory_xsec);
   g_theory->SetTitle("");
   g_theory->SetLineColor(kBlack);
   g_theory->SetLineStyle(2);
   g_theory->SetLineWidth(2);
   
   TPolyLine *pl2_p = new TPolyLine(9,x,y2_p);
   pl2_p->SetFillColor(kYellow);
   pl2_p->Draw("fSAME");

   TPolyLine *pl2_n = new TPolyLine(9,x,y2_n);
   pl2_n->SetFillColor(kYellow);
   pl2_n->Draw("fSAME");

   TPolyLine *pl1_p = new TPolyLine(9,x,y1_p);
   pl1_p->SetFillColor(kGreen);
   pl1_p->Draw("fSAME");

   TPolyLine *pl1_n = new TPolyLine(9,x,y1_n);
   pl1_n->SetFillColor(kGreen);
   pl1_n->Draw("fSAME");
   
   g_mel->Draw("L");
   g_mel->GetXaxis()->SetTitle("N [GeV]");
   g_mel->GetYaxis()->SetTitle("#sigma [pb]");
   
   g_data->Draw("L");
   g_theory->Draw("L");
   
   TLegend *l1 = new TLegend(0.6,0.64,0.87,0.87);
   l1->SetLineColor(0);
   l1->AddEntry(g_mel,"Median","l");
   l1->AddEntry(g_theory,"Theory","l");
   l1->AddEntry(pl1_p,"68%","f");
   l1->AddEntry(pl2_p,"95%","f");
   l1->AddEntry(g_data,"Data","l");
   l1->SetFillColor(0);
   l1->SetHeader("#intLdt = 35.2 pb^{-1}");
   l1->Draw("SAME");

   c1->SetLogy(1);
   c1->GetFrame()->SetFillColor(kWhite);
   c1->Update();
   c1->Draw();   
   c1->Print("pics/plot_single.eps");
   
   gApplication->Terminate();
}
