void convert2Limit()
{
   gROOT->SetBatch(1);

   TFile *f = TFile::Open("hist.root");
   TH1F *hget_e_signal = (TH1F*)f->Get("sig_h_H_m_e_bjge3_nosel_ALL_merged");
   TH1F *hget_e_bg = (TH1F*)f->Get("bg_h_H_m_e_bjge3_nosel_ALL_merged");
   TH1F *hget_m_signal = (TH1F*)f->Get("sig_h_H_m_m_bjge3_nosel_ALL_merged");
   TH1F *hget_m_bg = (TH1F*)f->Get("bg_h_H_m_m_bjge3_nosel_ALL_merged");

   TFile *fout = new TFile("input.root","RECREATE");
   
   TH1F *h_e_signal_oneBin = new TH1F("h_e_signal_oneBin","h_e_signal_oneBin",1,0.,1.);
   TH1F *h_m_signal_oneBin = new TH1F("h_m_signal_oneBin","h_m_signal_oneBin",1,0.,1.);
//   h_e_signal_oneBin->Sumw2();
//   h_m_signal_oneBin->Sumw2();
   
   TH1F *h_e_bg_oneBin = new TH1F("h_e_bg_oneBin","h_e_bg_oneBin",1,0.,1.);
   TH1F *h_m_bg_oneBin = new TH1F("h_m_bg_oneBin","h_m_bg_oneBin",1,0.,1.);
//   h_e_bg_oneBin->Sumw2();
//   h_m_bg_oneBin->Sumw2();

   TH1F *h_e_data_oneBin = new TH1F("h_e_data_oneBin","h_e_data_oneBin",1,0.,1.);
   TH1F *h_m_data_oneBin = new TH1F("h_m_data_oneBin","h_m_data_oneBin",1,0.,1.);
//   h_e_data_oneBin->Sumw2();
//   h_m_data_oneBin->Sumw2();
   
   TH1F *h_e_signal = (TH1F*)hget_e_signal->Clone("h_e_signal");
   TH1F *h_e_bg = (TH1F*)hget_e_bg->Clone("h_e_bg");
   TH1F *h_e_data = (TH1F*)hget_e_bg->Clone("h_e_data");

   TH1F *h_m_signal = (TH1F*)hget_m_signal->Clone("h_m_signal");
   TH1F *h_m_bg = (TH1F*)hget_m_bg->Clone("h_m_bg");
   TH1F *h_m_data = (TH1F*)hget_m_bg->Clone("h_m_data");
   
   double e_signal_err;
   double e_signal = h_e_signal->IntegralAndError(0,h_e_signal->GetXaxis()->GetNbins()+1,e_signal_err);
   double m_signal_err;
   double m_signal = h_m_signal->IntegralAndError(0,h_m_signal->GetXaxis()->GetNbins()+1,m_signal_err);

   double e_bg_err;
   double e_bg = h_e_bg->IntegralAndError(0,h_e_bg->GetXaxis()->GetNbins()+1,e_bg_err);
   double m_bg_err;
   double m_bg = h_m_bg->IntegralAndError(0,h_m_bg->GetXaxis()->GetNbins()+1,m_bg_err);
   
   h_e_signal_oneBin->SetBinContent(1,e_signal);
   h_e_signal_oneBin->SetBinError(1,e_signal_err);

   h_m_signal_oneBin->SetBinContent(1,m_signal);
   h_m_signal_oneBin->SetBinError(1,m_signal_err);

   h_e_bg_oneBin->SetBinContent(1,e_bg);
   h_e_bg_oneBin->SetBinError(1,e_bg_err);

   h_m_bg_oneBin->SetBinContent(1,m_bg);
   h_m_bg_oneBin->SetBinError(1,m_bg_err);
   
   fout->Write();
   fout->Close();
   
   gApplication->Terminate();
}
