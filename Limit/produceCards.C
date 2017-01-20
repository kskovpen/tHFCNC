void produceCards()
{
   gROOT->SetBatch(1);

   const int nc = 6;
   std::string cat[nc] = {"b2j3","b2j4","b3j3","b3j4","b4j4","ALL"};
   const int nd = 8;
   std::string dist[nd] = {"MVAHut","MVAHct","MVAHutST","MVAHutTT","MVAHctST","MVAHctTT","PassSel5","PassSel5"};
   std::string coup[nd] = {"hut","hct","hut","hut","hct","hct","hut","hct"};
   
   for(int id=0;id<nd;id++)
     {	
	for(int ic=0;ic<nc;ic++)
	  {	
	     std::string fname = "input_"+dist[id]+"_"+cat[ic]+"_"+coup[id];
	     std::string fhist = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_12/src/tHFCNC/NtupleAnalyzer/test/proc/input/"+fname+".root";
	     std::string fcard = "cards/"+fname+".txt";
	     std::ofstream fc(fcard.c_str());
	     
	     TFile *f = TFile::Open(fhist.c_str(),"READ");
	     TH1F* h_data = (TH1F*)f->Get("h_data_obs");
	     int stats = h_data->Integral();
	     TH1F* h_sig = (TH1F*)f->Get("h_sig");
	     float statsSig = h_sig->Integral();
	     TH1F* h_ttbb = (TH1F*)f->Get("h_ttbb");
	     float statsTtbb = h_ttbb->Integral();
	     TH1F* h_ttcc = (TH1F*)f->Get("h_ttcc");
	     float statsTtcc = h_ttcc->Integral();
	     TH1F* h_ttlf = (TH1F*)f->Get("h_ttlf");
	     float statsTtlf = h_ttlf->Integral();
	     TH1F* h_other = (TH1F*)f->Get("h_other");
	     float statsOther = h_other->Integral();
	     f->Close();
   
	     fc << "imax * # number of channels" << std::endl;
	     fc << "jmax * # number of backgrounds" << std::endl;
	     fc << "kmax * # number of nuisance parameters" << std::endl;
	     fc << "---------------" << std::endl;
	     fc << "bin " << cat[ic] << std::endl;
	     fc << "observation " << stats << std::endl;
	     fc << "---------------" << std::endl;
	     fc << "shapes * * " << fhist << " h_$PROCESS h_$PROCESS_$SYSTEMATIC" << std::endl;
	     fc << "---------------" << std::endl;
	     fc << "bin " << cat[ic] << " " << cat[ic] << " " << cat[ic] << " " << cat[ic] << " " << cat[ic] << std::endl;
	     fc << "process sig ttbb ttcc ttlf other" << std::endl;
	     fc << "process 0 1 2 3 4" << std::endl;
	     fc << "rate "<< statsSig << " " << statsTtbb << " " << statsTtcc << " " << statsTtlf << " " << statsOther << std::endl;
/*	     fc << "bin " << cat[ic] << " " << cat[ic] << std::endl;
	     fc << "process sig other" << std::endl;
	     fc << "process 0 1" << std::endl;
	     fc << "rate "<< statsSig << " " << statsOther << std::endl;*/
	     fc << "---------------" << std::endl;
	     fc << "SfIterativeFitHfstats1 shape 1 1 1 1 1" << std::endl;
	     fc << "SfIterativeFitHfstats2 shape 1 1 1 1 1" << std::endl;
	     fc << "SfIterativeFitLfstats1 shape 1 1 1 1 1" << std::endl;
	     fc << "SfIterativeFitLfstats2 shape 1 1 1 1 1" << std::endl;
	     fc << "SfIterativeFitJes shape 1 1 1 1 1" << std::endl;
	     fc << "SfIterativeFitLf shape 1 1 1 1 1" << std::endl;
	     fc << "SfIterativeFitHf shape 1 1 1 1 1" << std::endl;
	     fc << "SfIterativeFitCferr1 shape 1 1 1 1 1" << std::endl;
	     fc << "SfIterativeFitCferr2 shape 1 1 1 1 1" << std::endl;
	     fc << "Jes shape 1 1 1 1 1" << std::endl;
	     fc << "Jer shape 1 1 1 1 1" << std::endl;
/*	     fc << "SfIterativeFitHfstats1 shape 1 1" << std::endl;
	     fc << "SfIterativeFitHfstats2 shape 1 1" << std::endl;
	     fc << "SfIterativeFitLfstats1 shape 1 1" << std::endl;
	     fc << "SfIterativeFitLfstats2 shape 1 1" << std::endl;
	     fc << "SfIterativeFitJes shape 1 1" << std::endl;
	     fc << "SfIterativeFitLf shape 1 1" << std::endl;
	     fc << "SfIterativeFitHf shape 1 1" << std::endl;
	     fc << "SfIterativeFitCferr1 shape 1 1" << std::endl;
	     fc << "SfIterativeFitCferr2 shape 1 1" << std::endl;
	     fc << "Jes shape 1 1" << std::endl;
	     fc << "Jer shape 1 1" << std::endl;*/
	     fc << "---------------" << std::endl;
	     
	     fc.close();
	  }
     }
   
   gApplication->Terminate();
}
