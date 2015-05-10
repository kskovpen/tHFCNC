{
   gROOT->SetBatch(1);
   
   TCanvas *c1 = new TCanvas();
   
   // hut
   TF1 *h_hut = new TF1("h_hut","74.12*0.000001*x*x",0,10);   
   h_hut->Draw();
   h_hut->GetXaxis()->SetTitle("#kappa_{Hut}/#Lambda [TeV^{-1}]");
   h_hut->GetYaxis()->SetTitle("Cross-section [pb]");   
   c1->Print("hut.eps");
   c1->Clear();

   // hct
   TF1 *h_hct = new TF1("h_hct","9.179*0.000001*x*x",0,10);   
   h_hct->Draw();
   h_hct->GetXaxis()->SetTitle("#kappa_{Hct}/#Lambda [TeV^{-1}]");
   h_hct->GetYaxis()->SetTitle("Cross-section [pb]");   
   c1->Print("hct.eps");
   c1->Clear();

   // gut
   TF1 *h_gut = new TF1("h_gut","48.84*x*x",0,10);
   h_gut->Draw();
   h_gut->GetXaxis()->SetTitle("#kappa_{gut}/#Lambda [TeV^{-1}]");
   h_gut->GetYaxis()->SetTitle("Cross-section [pb]");   
   c1->Print("gut.eps");
   c1->Clear();

   // gct
   TF1 *h_gct = new TF1("h_gct","6.404*x*x",0,10);
   h_gct->Draw();
   h_gct->GetXaxis()->SetTitle("#kappa_{gct}/#Lambda [TeV^{-1}]");
   h_gct->GetYaxis()->SetTitle("Cross-section [pb]");   
   c1->Print("gct.eps");
   c1->Clear();
   
   gApplication->Terminate();
}
