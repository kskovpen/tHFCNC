void get()
{
   gROOT->SetBatch();

   TFile *f = new TFile("webPlot/limitInput.root");

   std::string sel = "mlljj_ee_ss_jge1_ge_mll110_ge_mlljj400";

   std::string sig = "WR2000NR50";
   std::string bkg = "ZJETS";
   
   std::string ch1_data = "h_DATA_"+sel;
   TH1F * h_ch1_data = (TH1F*)f->Get(ch1_data.c_str());

   std::string ch1_sig = "h_"+sig+"_"+sel;
   TH1F * h_ch1_sig = (TH1F*)f->Get(ch1_sig.c_str());
   std::string ch1_sig_sysUp = "h_"+sig+"_"+sel+"_jesUp";
   TH1F * h_ch1_sig_sys_jesUp = (TH1F*)f->Get(ch1_sig_sysUp.c_str());
   std::string ch1_sig_sysDown = "h_"+sig+"_"+sel+"_jesDown";
   TH1F * h_ch1_sig_sys_jesDown = (TH1F*)f->Get(ch1_sig_sysDown.c_str());

   std::string ch1_bkg = "h_"+bkg+"_"+sel;
   TH1F * h_ch1_bkg = (TH1F*)f->Get(ch1_bkg.c_str());
   std::string ch1_bkg_sysUp = "h_"+bkg+"_"+sel+"_jesUp";
   TH1F * h_ch1_bkg_sys_jesUp = (TH1F*)f->Get(ch1_bkg_sysUp.c_str());
   std::string ch1_bkg_sysDown = "h_"+bkg+"_"+sel+"_jesDown";
   TH1F * h_ch1_bkg_sys_jesDown = (TH1F*)f->Get(ch1_bkg_sysDown.c_str());
/*
   TH1F * h_ch2_data = (TH1F*)f->Get("h_DATA_mlljj_mm_os_jge1_ge_mll110_ge_st400_ge_mlljj400");
   
   TH1F * h_ch2_sig = (TH1F*)f->Get("h_WR2300NR1725_mlljj_mm_os_jge1_ge_mll110_ge_st400_ge_mlljj400");
   TH1F * h_ch2_sig_sys_jesUp = (TH1F*)f->Get("h_WR2300NR1725_mlljj_mm_os_jge1_ge_mll110_ge_st400_ge_mlljj400_jesUp");
   TH1F * h_ch2_sig_sys_jesDown = (TH1F*)f->Get("h_WR2300NR1725_mlljj_mm_os_jge1_ge_mll110_ge_st400_ge_mlljj400_jesDown");

   TH1F * h_ch2_bkg = (TH1F*)f->Get("h_ZJETS_mlljj_mm_os_jge1_ge_mll110_ge_st400_ge_mlljj400");
   TH1F * h_ch2_bkg_sys_jesUp = (TH1F*)f->Get("h_ZJETS_mlljj_mm_os_jge1_ge_mll110_ge_st400_ge_mlljj400_jesUp");
   TH1F * h_ch2_bkg_sys_jesDown = (TH1F*)f->Get("h_ZJETS_mlljj_mm_os_jge1_ge_mll110_ge_st400_ge_mlljj400_jesDown");
*/
   TFile *f_copy = new TFile("example/limitInput.root","RECREATE");

   TH1F *h_ch1_data_copy = h_ch1_data->Clone("h_channel1_data");
   
   TH1F *h_ch1_sig_copy = h_ch1_sig->Clone("h_channel1_signal");
   TH1F *h_ch1_sig_sys_jesUp_copy = h_ch1_sig_sys_jesUp->Clone("h_channel1_signal_sys_jesUp");
   TH1F *h_ch1_sig_sys_jesDown_copy = h_ch1_sig_sys_jesDown->Clone("h_channel1_signal_sys_jesDown");

   TH1F *h_ch1_bkg_copy = h_ch1_bkg->Clone("h_channel1_background");
   TH1F *h_ch1_bkg_sys_jesUp_copy = h_ch1_bkg_sys_jesUp->Clone("h_channel1_background_sys_jesUp");
   TH1F *h_ch1_bkg_sys_jesDown_copy = h_ch1_bkg_sys_jesDown->Clone("h_channel1_background_sys_jesDown");

/*   TH1F *h_ch2_data_copy = h_ch2_data->Clone("h_channel2_data");
   
   TH1F *h_ch2_sig_copy = h_ch2_sig->Clone("h_channel2_signal");
   TH1F *h_ch2_sig_sys_jesUp_copy = h_ch2_sig_sys_jesUp->Clone("h_channel2_signal_sys_jesUp");
   TH1F *h_ch2_sig_sys_jesDown_copy = h_ch2_sig_sys_jesDown->Clone("h_channel2_signal_sys_jesDown");

   TH1F *h_ch2_bkg_copy = h_ch2_bkg->Clone("h_channel2_background");
   TH1F *h_ch2_bkg_sys_jesUp_copy = h_ch2_bkg_sys_jesUp->Clone("h_channel2_background_sys_jesUp");
   TH1F *h_ch2_bkg_sys_jesDown_copy = h_ch2_bkg_sys_jesDown->Clone("h_channel2_background_sys_jesDown");
*/   
   f_copy->Write();
   f_copy->Close();
   
   gApplication->Terminate();
}
