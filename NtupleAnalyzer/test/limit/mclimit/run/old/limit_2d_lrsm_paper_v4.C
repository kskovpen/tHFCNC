#include "TGraph2D.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TPad.h"
#include "TCanvas.h"
#include <iostream>
#include "TStyle.h"
#include "TH2.h"

#include "TList.h"
#include "TObjArray.h"
#include "TROOT.h"
#include <vector>

#include "AtlasLabels.C"

void setStyle(){
   gROOT->SetStyle("Plain");
   
   gStyle->SetTitleSize(0.05593);
//   gStyle->SetTitleSize(0.05,"xyz");
   gStyle->SetTitleSize(0.0,"xyz");
   gStyle->SetLabelSize(0.0,"xyz");
//   gStyle->SetLabelSize(0.047,"xyz");
   gStyle->SetTitleFont(132,"xyz");
   gStyle->SetTitleFont(132,"t");
   gStyle->SetLabelFont(132,"xyz");
   gStyle->SetTitleYOffset(1.0);
   gStyle->SetTitleXOffset(1.2);
   
   gStyle->SetHistLineWidth(1);
   
   gStyle->SetTitleBorderSize(0);
   gStyle->SetNdivisions(505,"xyz");
   gStyle->SetOptStat(0000);
   gStyle->SetPadBottomMargin(0.14);
   gStyle->SetPadLeftMargin(0.14);
   gStyle->SetPalette(7);
  
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

void limit_2d_lrsm_paper_v4()
{
   gROOT->SetBatch();
   setStyle();
   gStyle->SetHatchesSpacing(1.5);

   TString type;
   bool dirac = 0;
   bool draw_med = 1;
   bool draw_obs = 0;
   
   if( dirac )
     type = "#font[62]{N_{Dirac}}";
   else
     type = "#font[62]{N_{Majorana}}";
   
   const int nelem = 52;
   //const int nelem = 53;

   float med_eemm[nelem] =
     {
	// OS
	// SS+OS
	0.000819328,0.000649672,0.000742449,0.00401439,0.00224206,0.00148536,0.00136945,0.00533726,0.00383208,0.00314101,0.00404648,0.0141437,0.010823,0.00842032,0.00668243,0.00829887,0.0396769,0.036807,0.0255003,0.0157218,0.0230323,0.15242,0.116609,0.0820697,0.0496305,0.0725894,0.294326,0.353562,0.271081,0.133487,0.223326,1.03435,0.774086,0.564586,0.269238,0.496553,1.65181,1.55897,1.11284,0.527479,0.93598,3.45918,3.20864,1.6,0.951694,1.63103,4.59518,6.43198,4.16691,1.62625,2.67903,5.58512
     };
/*   float med_eemmem[nelem] =
     {
	// OS
//	0.0398098,0.0202276,0.0237914,0.126628,0.0401254,0.0287473,0.0265507,0.0440797,0.0733505,0.0516109,0.0400868,0.0481741,0.18525,0.121568,0.0978719,0.0722222,0.0914953,0.44065,0.248116,0.204214,0.132078,0.193277,1.3003,0.53559,0.493554,0.335923,0.521128,2.13821,1.31948,1.11859,0.833028,1.33322,7.13459,2.50773,2.40022,1.6865,2.99603,17.5904,4.47302,4.32918,2.99268,5.76481,34.9752,10.9924,9.56102,5.14185,9.56734,60.3013,28.4654,25.7778,10.1767,17.5702,100.767
	// SS+OS
	0.00504468,0.00313803,0.00310193,0.017404,0.00928492,0.00647457,0.00572304,0.00933068,0.0194793,0.0141989,0.0117,0.0141515,0.0498239,0.0336722,0.0290493,0.0208107,0.0278396,0.130258,0.0883407,0.0724446,0.0502247,0.0702661,0.473897,0.225176,0.187231,0.128293,0.204413,0.79529,0.594643,0.501671,0.339161,0.536379,2.89497,1.13379,1.01412,0.702257,1.19714,6.79051,2.0284,1.90387,1.29623,2.47484,14.9229,5.26499,4.40469,2.42687,4.39134,27.152,12.6903,11.3882,4.75675,8.25179,48.723
     };
  */ 
   float obs_eemm[nelem] =
     {
	// OS
	// SS+OS
	0.00577665,0.00480185,0.0259007,0.00698897,0.00806127,0.00844951,0.0119848,0.0143516,0.0155205,0.0115046,0.0121321,0.0489734,0.0264984,0.0226823,0.0143012,0.0159819,0.086011,0.0586638,0.0549652,0.038177,0.0582438,0.408248,0.161483,0.150819,0.127707,0.18113,0.676485,0.509383,0.410031,0.24186,0.43726,1.94474,0.904023,0.825974,0.410449,0.86975,4.94274,1.71071,1.55798,1.04559,1.76523,11.3531,4.74034,4.43448,1.73052,3.68545,21.5667,11.3471,10.7982,3.70685,6.86747,43.3251
     };
/*   float obs_eemmem[nelem] =
     {
	// OS
//	0.0588018,0.0395029,0.0368863,0.248689,0.0612096,0.046354,0.0251912,0.0606221,0.0742361,0.0473378,0.0329764,0.0480907,0.138517,0.106376,0.0649021,0.045604,0.0475371,0.270213,0.218887,0.182523,0.116077,0.168453,1.03782,0.387065,0.356499,0.28768,0.65024,2.24525,0.97135,0.73485,0.549369,0.95,4.68203,1.76989,1.67338,0.991651,1.94795,10.4088,3.55048,3.25754,1.87546,3.72065,22.7458,8.88493,7.75519,3.70863,6.94611,41.2335,27.4931,20.2538,8.40652,13.938,77.4801
	// SS+OS
	0.0135054,0.00762144,0.00789349,0.0468519,0.0192452,0.0131665,0.0131246,0.0212703,0.0215295,0.0233107,0.0164087,0.0243261,0.112867,0.0385254,0.02236,0.0161968,0.022311,0.11751,0.0911746,0.0910315,0.0647071,0.077328,0.531142,0.193505,0.14093,0.114187,0.224834,0.887636,0.449456,0.454521,0.190154,0.377584,2.49575,0.806721,0.784338,0.549362,0.805191,5.08981,1.78982,1.2941,0.84948,1.65354,10.6962,4.14491,3.76601,1.93405,3.68999,21.2173,12.1141,10.9635,4.2517,6.91063,37.6143
     };   
*/
   // MWr
   float mass1[nelem] = 
     {
	600,600,600,600,800,800,800,1000,1000,1000,1000,1000,1200,1200,1200,1200,1200,1500,1500,1500,1500,1500,1800,1800,1800,1800,1800,2100,2100,2100,2100,2100,2300,2300,2300,2300,2300,2500,2500,2500,2500,2500,2700,2700,2700,2700,2700,2900,2900,2900,2900,2900
     };
   
   // MN
   float mass2[nelem] = 
     {
	50,100,300,500,50,100,300,50,100,200,500,800,50,100,200,600,1000,50,100,300,800,1300,50,100,500,1000,1500,50,100,600,1200,1800,50,100,700,1400,2000,50,100,800,1600,2200,50,100,800,1700,2500,50,100,900,1800,2700
     };
   
   if( dirac )
     {	
	for (int i=0;i<nelem;i++)
	  {	
	     med_eemm[i]     = med_eemm[i] / 2.;
//	     med_eemmem[i]   = med_eemmem[i] / 2.;
	     obs_eemm[i]     = obs_eemm[i] / 2.;
//	     obs_eemmem[i]   = obs_eemmem[i] / 2.;
	  }
     }   

   TGraph2D *tgc_med_eemm = new TGraph2D(nelem,mass1,mass2,med_eemm);
   tgc_med_eemm->SetNpx(35);
   tgc_med_eemm->SetNpy(40);
   tgc_med_eemm->SetName("tgc_med_eemm");
//   TGraph2D *tgc_med_eemmem = new TGraph2D(nelem,mass1,mass2,med_eemmem);
//   tgc_med_eemmem->SetNpx(29);
//   tgc_med_eemmem->SetNpy(40);
//   tgc_med_eemmem->SetName("tgc_med_eemmem");
   TGraph2D *tgc_obs_eemm = new TGraph2D(nelem,mass1,mass2,obs_eemm);
   tgc_obs_eemm->SetNpx(35);
   tgc_obs_eemm->SetNpy(40);
   tgc_obs_eemm->SetName("tgc_obs_eemm");
//   TGraph2D *tgc_obs_eemmem = new TGraph2D(nelem,mass1,mass2,obs_eemmem);
//   tgc_obs_eemmem->SetNpx(29);
//   tgc_obs_eemmem->SetNpy(40);
//   tgc_obs_eemmem->SetName("tgc_obs_eemmem");
      
   TCanvas *tc = new TCanvas("tc","",1000,800);

   std::vector< TGraph* > cont_med_eemm = getContour(tgc_med_eemm,tc,0);
//   std::vector< TGraph* > cont_med_eemmem = getContour(tgc_med_eemmem,tc,0);
   std::vector< TGraph* > cont_obs_eemm = getContour(tgc_obs_eemm,tc,0);
//   std::vector< TGraph* > cont_obs_eemmem = getContour(tgc_obs_eemmem,tc,0);

   double m1_c[1] = {0};
   double m2_c[1] = {0};
   double xs_c[1] = {0};
   
   TGraph2D *tgx_canv = new TGraph2D(1,m1_c,m2_c,xs_c);

   tgx_canv->SetTitle("");
   tgx_canv->GetYaxis()->SetTitle("#font[52]{m_{N}} #font[42]{[TeV]}");
   tgx_canv->GetXaxis()->SetTitle("#font[52]{m_{W_{R}}} #font[42]{[TeV]}");
   
   tgx_canv->Draw("");

   TH2F *hr = new TH2F("hr","",10,600.,2900.,10,0.,2700.);
   hr->GetYaxis()->SetTitle("#font[52]{m_{N}} #font[42]{[TeV]}");
   hr->GetXaxis()->SetTitle("#font[52]{m_{W_{R}}} #font[42]{[TeV]}");
   hr->SetNdivisions(505,"x");
   hr->SetNdivisions(505,"y");
   hr->Draw("");
   hr->GetYaxis()->SetRangeUser(0,2700);
   
   for (int j=0;j<cont_med_eemm.size();j++)
     {
	cont_med_eemm[j]->SetLineStyle(8);
	cont_med_eemm[j]->SetLineWidth(4);
	cont_med_eemm[j]->SetLineColor(kRed-6);
	if( draw_med && !draw_obs )
	  cont_med_eemm[j]->SetLineColor(kRed);
	int nel_eemm = cont_med_eemm[j]->GetN();
	int nel1_eemm = nel_eemm+1;	     
	double *x_poi_eemm = new double[nel1_eemm];
	double *y_poi_eemm = new double[nel1_eemm];
	if( j == 0 )
	  {		  
	     for(int ip=0;ip<nel_eemm;ip++)
	       cont_med_eemm[j]->GetPoint(ip,x_poi_eemm[ip],y_poi_eemm[ip]);
	     cont_med_eemm[j]->SetPoint(0,600.,50.);
	     for(int ip=0;ip<nel_eemm;ip++)
	       cont_med_eemm[j]->SetPoint(ip+1,x_poi_eemm[ip],y_poi_eemm[ip]);
	     
	     interp(cont_med_eemm[j],nel_eemm,1250.);
	  }
	if( draw_med )
	  cont_med_eemm[j]->Draw("L");
	delete x_poi_eemm;
	delete y_poi_eemm;
     }      
/*
   for (int j=0;j<cont_med_eemmem.size();j++)
     {
	cont_med_eemmem[j]->SetLineStyle(6);
	cont_med_eemmem[j]->SetLineWidth(4);
	cont_med_eemmem[j]->SetLineColor(kBlue-6);
	if( draw_med && !draw_obs )
	  cont_med_eemmem[j]->SetLineColor(kBlue);
	int nel_eemmem = cont_med_eemmem[j]->GetN();
	int nel1_eemmem = nel_eemmem+1;	     
	double *x_poi_eemmem = new double[nel1_eemmem];
	double *y_poi_eemmem = new double[nel1_eemmem];
	if( j == 0 )
	  {		  
	     for(int ip=0;ip<nel_eemmem;ip++)
	       cont_med_eemmem[j]->GetPoint(ip,x_poi_eemmem[ip],y_poi_eemmem[ip]);
	     cont_med_eemmem[j]->SetPoint(0,600.,50.);
	     for(int ip=0;ip<nel_eemmem;ip++)
	       cont_med_eemmem[j]->SetPoint(ip+1,x_poi_eemmem[ip],y_poi_eemmem[ip]);
	     
	     interp(cont_med_eemmem[j],nel_eemmem,900.);
	  }
	if( draw_med )
	  cont_med_eemmem[j]->Draw("L");
	delete x_poi_eemmem;
	delete y_poi_eemmem;
     }      
*/
   // observed limit
   
   for (int j=0;j<cont_obs_eemm.size();j++)
     {
	cont_obs_eemm[j]->SetLineWidth(4);
	cont_obs_eemm[j]->SetLineColor(kRed);
	cont_obs_eemm[j]->SetLineStyle(1);
	int nel_eemm = cont_obs_eemm[j]->GetN();
	int nel1_eemm = nel_eemm+1;	     
	double *x_poi_eemm = new double[nel1_eemm];
	double *y_poi_eemm = new double[nel1_eemm];
	if( j == 0 )
	  {		  
	     for(int ip=0;ip<nel_eemm;ip++)
	       cont_obs_eemm[j]->GetPoint(ip,x_poi_eemm[ip],y_poi_eemm[ip]);
	     cont_obs_eemm[j]->SetPoint(0,600.,50.);
	     for(int ip=0;ip<nel_eemm;ip++)
	       cont_obs_eemm[j]->SetPoint(ip+1,x_poi_eemm[ip],y_poi_eemm[ip]);
	     
	     interp(cont_obs_eemm[j],nel_eemm,900.);
	  }
	if( draw_obs )
	  cont_obs_eemm[j]->Draw("L");
	delete x_poi_eemm;
	delete y_poi_eemm;
     }      
/*   if( dirac )
     {	
	double x[2];
	double y[2];
	cont_obs_eemm[0]->GetPoint(cont_obs_eemm[0]->GetN()-1,x[0],y[0]);
	cont_obs_eemm[1]->GetPoint(0,x[1],y[1]);
	TGraph *grn = new TGraph(2,x,y);
	grn->SetLineWidth(2);
	grn->SetLineStyle(1);
	grn->SetLineColor(kRed);
	grn->Draw("L");
     }*/
/*
   for (int j=0;j<cont_obs_eemmem.size();j++)
     {
	cont_obs_eemmem[j]->SetLineWidth(4);
	cont_obs_eemmem[j]->SetLineColor(kBlue);
	cont_obs_eemmem[j]->SetLineStyle(7);
	int nel_eemmem = cont_obs_eemmem[j]->GetN();
	int nel1_eemmem = nel_eemmem+1;	     
	double *x_poi_eemmem = new double[nel1_eemmem];
	double *y_poi_eemmem = new double[nel1_eemmem];
	if( j == 0 )
	  {		  
	     for(int ip=0;ip<nel_eemmem;ip++)
	       cont_obs_eemmem[j]->GetPoint(ip,x_poi_eemmem[ip],y_poi_eemmem[ip]);
	     cont_obs_eemmem[j]->SetPoint(0,600.,50.);
	     for(int ip=0;ip<nel_eemmem;ip++)
	       cont_obs_eemmem[j]->SetPoint(ip+1,x_poi_eemmem[ip],y_poi_eemmem[ip]);
	     
	     interp(cont_obs_eemmem[j],nel_eemmem,900.);
	  }
	if( draw_obs )
	  cont_obs_eemmem[j]->Draw("L");
	delete x_poi_eemmem;
	delete y_poi_eemmem;
     }*/
/*   if( dirac )
     {	
	double x[2];
	double y[2];
	cont_obs_eemmem[0]->GetPoint(cont_obs_eemmem[0]->GetN()-1,x[0],y[0]);
	cont_obs_eemmem[1]->GetPoint(0,x[1],y[1]);
	TGraph *grn = new TGraph(2,x,y);
	grn->SetLineWidth(2);
	grn->SetLineStyle(1);
	grn->SetLineColor(kRed);
	grn->Draw("L");
     }   
  */ 

   TGaxis *yaxis = new TGaxis(gPad->GetUxmin(), gPad->GetUymin()-50.,
			      gPad->GetUxmin(), gPad->GetUymax(),0.,2.7,505);
   yaxis->ImportAxisAttributes(tgx_canv->GetYaxis());
   yaxis->SetLabelSize(0.047);
   yaxis->SetTitleSize(0.05);
   yaxis->Draw();

   TGaxis *xaxis = new TGaxis(gPad->GetUxmin(), gPad->GetUymin()-50.,
			      gPad->GetUxmax(), gPad->GetUymin()-50.,0.6,2.9,505);
   xaxis->ImportAxisAttributes(tgx_canv->GetXaxis());
   xaxis->SetLabelSize(0.047);
   xaxis->SetTitleSize(0.05);
   xaxis->Draw();
   
   TF1 *f1 = new TF1("f1","[0]*x",600.,2900);
   f1->SetParameter(0,1.);
   f1->SetLineStyle(2);
   f1->SetLineWidth(1);
   f1->Draw("same");

   TLegend *l1 = new TLegend(0.68,0.68,0.68,0.68);
   l1->SetLineColor(0);
   l1->SetFillColor(0);
   l1->SetTextSize(0.040);
   l1->SetHeader("#intLdt = 4.7 fb^{-1}");
   l1->Draw();

   TLegend *l2;
   if( draw_med )
     l2 = new TLegend(0.16,0.88,0.40,0.69);
   else
     l2 = new TLegend(0.16,0.81,0.40,0.71);
   l2->SetLineColor(0);
   l2->SetFillColor(0);
   l2->SetTextSize(0.040);
   if( draw_med )
     {	
//	l2->AddEntry(cont_med_eemmem[0],"#font[42]{With mixing, ee+#mu#mu+e#mu, Expected}","l");
     }
   if( draw_obs )
     {
//	l2->AddEntry(cont_obs_eemmem[0],"#font[42]{With mixing, ee+#mu#mu+e#mu, Observed}","l");
     }   
   if( draw_med )
     {	
	l2->AddEntry(cont_med_eemm[0],"#font[42]{No mixing, ee+#mu#mu, Expected}","l");
     }   
   if( draw_obs )
     {
	l2->AddEntry(cont_obs_eemm[0],"#font[42]{No mixing, ee+#mu#mu, Observed}","l");
     }   
   l2->Draw();

   TLegend *l3;
   if( draw_med )
     l3 = new TLegend(0.18,0.60,0.18,0.55);
   else
     l3 = new TLegend(0.18,0.69,0.18,0.65);
   l3->SetLineColor(0);
   l3->SetFillColor(0);
   l3->SetTextSize(0.058);
   if( !dirac )
     l3->SetHeader("SS+OS");
   else
     l3->SetHeader("OS");
   l3->Draw();

   TLegend *l5 = new TLegend(0.20,0.25,0.20,0.20);
   l5->SetLineColor(0);
   l5->SetFillColor(0);
   l5->SetTextSize(0.055);
   l5->SetHeader(type);
   l5->Draw();
   
   TLatex l7;
   l7.SetTextSize(0.044);
   l7.SetNDC();
   l7.SetTextColor(kBlack);
   l7.DrawLatex(0.71,0.59,"#font[42]{#sqrt[]{s} = 7 TeV}");
   
   TLatex l;
   l.SetTextSize(0.037);
   l.SetNDC();
   l.SetTextColor(kBlack);
   l.SetTextAngle(33);
   l.DrawLatex(0.16,0.35,"#font[52]{m_{N}} #font[42]{#geq} #font[52]{m_{W_{R}}} #font[42]{suppressed}");
   
//   myText2(0.17,0.48,kBlack,"M(N) > M(W_{R})");
//   myText2(0.17,0.45,kBlack,"m_{N} > m_{W_{R}}");
   
   ATLASLabel(0.20,0.630,"Internal",kBlack);
//   ATLASLabel(0.16,0.625,"for Approval",kBlack);
   
   tc->Print("pics/limit_2d_lrsm_paper.eps");

   gApplication->Terminate();
}

std::vector< TGraph* > getContour(TGraph2D *tgc,TCanvas *tc,const int level)
{
   TGraph *gr[1000];
   int np[1000];
   std::vector< TGraph* > res;

   TH2D *cont = tgc->GetHistogram();

   for (int ix=0;ix<cont->GetNbinsX()+1;ix++)
     for (int iy=0;iy<cont->GetNbinsY()+1;iy++)
       if (cont->GetBinContent(ix,iy)<1e-10)
	 {
	    cont->SetBinContent(ix,iy,100.0);
	 }

   cont->SetContour(1);
   cont->SetLineWidth(2);
   cont->SetContourLevel(0,1.0);
   cont->Draw("CONT Z LIST");

   tc->Update();

   TObjArray *conts = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
   TList *contLevel = NULL;
   TGraph *curv = NULL;
   TGraph *gv = NULL;
   int nGraphs = 0;
   int TotalConts = conts->GetSize();

   if( TotalConts != 1 ) std::cout << "Many contour levels found !" << std::endl;
   
   for (int i=0;i<conts->GetSize(); i++)
     {
	contLevel = (TList*)conts->At(i);
	
	np[i] = 0;
	
	for (int j=0;j<contLevel->GetSize();j++)
	  {	     
	     curv = (TGraph*)contLevel->At(j);
	     curv->SetLineWidth(4);
	     gr[j]=(TGraph*)curv->Clone(Form("gr_%d",j));
	     np[i]++;
	  }
     }

   tc->Clear();

   for(int i=0;i<np[level];i++)
     res.push_back( gr[i] );

   return res;
}

void interp(TGraph* gr,int nel,double cut)
{   
   bool found = false;
   double x_cut;
   double y_cut;
   int i_cut;
   double x_fin;
   double k_fin;
   double b_fin;
   for(int ip=0;ip<nel+1;ip++)
     {
	double x_cur;
	double y_cur;
	gr->GetPoint(ip,x_cur,y_cur);
	if( x_cur < cut && y_cur > 200. )
	  {
	     if( !found )
	       {
		  x_cut = x_cur;
		  y_cut = y_cur;
		  i_cut = ip;
		  double xt1, xt2, yt1, yt2;
		  gr->GetPoint(ip,xt1,yt1);
		  gr->GetPoint(ip-1,xt2,yt2);
		  k_fin = (yt1-yt2)/(xt1-xt2);
		  b_fin = (yt2-k_fin*xt2+yt1-k_fin*xt1)/2.;
		  x_fin = 600.;
		  found = true;
	       }
	     else
	       {					    
		  gr->SetPoint(ip,x_cur,k_fin*x_cur+b_fin);
	       }		       
	  }		  
     }	     
   gr->SetPoint(nel+1,600.,k_fin*600.+b_fin);
}
