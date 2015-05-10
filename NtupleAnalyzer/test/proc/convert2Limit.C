void convert2Limit()
{
   gROOT->SetBatch(1);

   TFile *f = TFile::Open("hist.root");
   TH1F *hget_e_signal = (TH1F*)f->Get("sig_h_count_e_jge0_bjge3_mH_ALL_merged");
   TH1F *hget_e_bg = (TH1F*)f->Get("bg_h_count_e_jge0_bjge3_mH_ALL_merged");
   TH1F *hget_m_signal = (TH1F*)f->Get("sig_h_count_m_jge0_bjge3_mH_ALL_merged");
   TH1F *hget_m_bg = (TH1F*)f->Get("bg_h_count_m_jge0_bjge3_mH_ALL_merged");

   TFile *fout = new TFile("input.root","RECREATE");
   
   TH1F *h_e_signal = (TH1F*)hget_e_signal->Clone("h_e_signal");
   TH1F *h_e_bg = (TH1F*)hget_e_bg->Clone("h_e_bg");
   TH1F *h_e_data = (TH1F*)hget_e_bg->Clone("h_e_data");

   TH1F *h_m_signal = (TH1F*)hget_m_signal->Clone("h_m_signal");
   TH1F *h_m_bg = (TH1F*)hget_m_bg->Clone("h_m_bg");
   TH1F *h_m_data = (TH1F*)hget_m_bg->Clone("h_m_data");
   
   fout->Write();
   fout->Close();
   
   gApplication->Terminate();
}
