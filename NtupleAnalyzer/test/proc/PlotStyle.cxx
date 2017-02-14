#include <iostream>

#include "PlotStyle.h"

#include "TROOT.h"

void SetPlotStyle ()
{
  static TStyle* plotStyle = 0;
  if ( plotStyle==0 ) plotStyle = PlotStyle();
  gROOT->SetStyle("PLOT");
  gROOT->ForceStyle();
}

TStyle* PlotStyle()
{
  TStyle *plotStyle = new TStyle("PLOT","Plot style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  plotStyle->SetFrameBorderMode(icol);
  plotStyle->SetFrameFillColor(icol);
  plotStyle->SetCanvasBorderMode(icol);
  plotStyle->SetCanvasColor(icol);
  plotStyle->SetPadBorderMode(icol);
  plotStyle->SetPadColor(icol);
  plotStyle->SetStatColor(icol);
  //plotStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  plotStyle->SetPaperSize(20,26);

  // set margin sizes
  plotStyle->SetPadTopMargin(0.05);
//  plotStyle->SetPadRightMargin(0.05);
  plotStyle->SetPadRightMargin(0.2);
  plotStyle->SetPadBottomMargin(0.16);
  plotStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
  plotStyle->SetTitleXOffset(1.4);
  plotStyle->SetTitleYOffset(1.4);

  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.05;
//  Double_t tsize=0.04;
  plotStyle->SetTextFont(font);

  plotStyle->SetTextSize(tsize);
  plotStyle->SetLabelFont(font,"x");
  plotStyle->SetTitleFont(font,"x");
  plotStyle->SetLabelFont(font,"y");
  plotStyle->SetTitleFont(font,"y");
  plotStyle->SetLabelFont(font,"z");
  plotStyle->SetTitleFont(font,"z");
  
  plotStyle->SetLabelSize(tsize,"x");
  plotStyle->SetTitleSize(tsize,"x");
  plotStyle->SetLabelSize(tsize,"y");
  plotStyle->SetTitleSize(tsize,"y");
  plotStyle->SetLabelSize(tsize,"z");
  plotStyle->SetTitleSize(tsize,"z");

  // use bold lines and markers
  plotStyle->SetMarkerStyle(20);
  plotStyle->SetMarkerSize(1.2);
  plotStyle->SetHistLineWidth(2.);
  plotStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars 
  //plotStyle->SetErrorX(0.001);
  // get rid of error bar caps
  plotStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  plotStyle->SetOptTitle(0);
  //plotStyle->SetOptStat(1111);
  plotStyle->SetOptStat(0);
  //plotStyle->SetOptFit(1111);
  plotStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  plotStyle->SetPadTickX(1);
  plotStyle->SetPadTickY(1);

  return plotStyle;

}

void CMSLABEL()
{   
   TLatex *tex = new TLatex(0.1969,0.906825,"CMS");
   tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(61);
   tex->SetTextSize(0.07475);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLatex *tex2 = new TLatex(0.1969,0.817125,"Preliminary");
   tex2->SetNDC();
   tex2->SetTextAlign(13);
   tex2->SetTextFont(52);
   tex2->SetTextSize(0.05681);
   tex2->SetLineWidth(2);
   tex2->Draw();
   
//   TLatex *text1 = new TLatex(0.95,0.958,"12.9 fb^{-1}, #sqrt{s} = 13 TeV");
   TLatex *text1 = new TLatex(0.75,0.958,"12.9 fb^{-1}, #sqrt{s} = 13 TeV");
   text1->SetNDC();
   text1->SetTextAlign(31);
   text1->SetTextFont(42);
   text1->SetTextSize(0.04875);
   text1->SetLineWidth(2);
   text1->Draw();
}

void LABEL(std::string lab)
{   
   TLatex *tex = new TLatex(0.65,0.906825,lab.c_str());
   tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(61);
   tex->SetTextSize(0.07475);
   tex->SetLineWidth(2);
   tex->Draw();
}
