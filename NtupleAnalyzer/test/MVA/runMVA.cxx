#include "runMVA.h"

int main(int argc, char *argv[])
{
   int imva = atoi(argv[1]);
   
   //////////
   // b3j4 //
   //////////
   
   // b3j4 tH Hut vs ttbar
   if( imva == 0 )
     {
	TFile* outfile = TFile::Open("TMVA_HutST_b3j4.root","RECREATE");
	
	double weight;
	
	double HiggsMass_TOPHLEPBB;
	double TopHadMass_TOPTOPLEPHAD;
	double MVA_TOPHLEPBB;
	double MVA_TOPTOPLEPHAD;
	int LepCharge;
	double HiggsEta_TOPHLEPBB;
	double TopLepMass_TOPHLEPBB;
	double TopLepMass_TOPTOPLEPHAD;
	double TopLepPt_TOPHLEPBB;
	double TopLepEta_TOPHLEPBB;
	double HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	double TopLepHiggsDr_TOPHLEPBB;
	double TopLepTopHadDr_TOPTOPLEPHAD;

	TMVA::Factory *factory = new TMVA::Factory("TMVA_HutST_b3j4",outfile,
						   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D:AnalysisType=Classification" );
   
	factory->AddVariable("HiggsMass_TOPHLEPBB",'D');
	factory->AddVariable("TopHadMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("MVA_TOPHLEPBB",'D');
	factory->AddVariable("MVA_TOPTOPLEPHAD",'D');
	factory->AddVariable("LepCharge",'I');
	factory->AddVariable("HiggsEta_TOPHLEPBB",'D');
	factory->AddVariable("TopLepMass_TOPHLEPBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("TopLepPt_TOPHLEPBB",'D');
	factory->AddVariable("TopLepEta_TOPHLEPBB",'D');
	factory->AddVariable("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",'D');
	factory->AddVariable("TopLepHiggsDr_TOPHLEPBB",'D');
	factory->AddVariable("TopLepTopHadDr_TOPTOPLEPHAD",'D');

	TChain tr_sig("tr_all_b3j4");
	tr_sig.Add("../histTEST_MERGED/ST_TH_1L3B.root");

	TChain tr_bkg("tr_all_b3j4");
	tr_bkg.Add("../histTEST_MERGED/TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
   
	tr_sig.SetBranchAddress("weight",&weight);
	tr_sig.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("LepCharge",&LepCharge);
	tr_sig.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	tr_bkg.SetBranchAddress("weight",&weight);
	tr_bkg.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("LepCharge",&LepCharge);
	tr_bkg.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	TRandom3 *r = new TRandom3(666);
	
	std::vector<double> vars(13);

	for(int i=0;i<tr_sig.GetEntries();i++)
	  {
	     tr_sig.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPHLEPBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = LepCharge;
	     vars[5] = HiggsEta_TOPHLEPBB;
	     vars[6] = TopLepMass_TOPHLEPBB;
	     vars[7] = TopLepMass_TOPTOPLEPHAD;
	     vars[8] = TopLepPt_TOPHLEPBB;
	     vars[9] = TopLepEta_TOPHLEPBB;
	     vars[10] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[11] = TopLepHiggsDr_TOPHLEPBB;
	     vars[12] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddSignalTrainingEvent(vars,weight);
	     else
	       factory->AddSignalTestEvent(vars,weight);
	  }
	
	for(int i=0;i<tr_bkg.GetEntries();i++)
	  {
	     tr_bkg.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPHLEPBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = LepCharge;
	     vars[5] = HiggsEta_TOPHLEPBB;
	     vars[6] = TopLepMass_TOPHLEPBB;
	     vars[7] = TopLepMass_TOPTOPLEPHAD;
	     vars[8] = TopLepPt_TOPHLEPBB;
	     vars[9] = TopLepEta_TOPHLEPBB;
	     vars[10] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[11] = TopLepHiggsDr_TOPHLEPBB;
	     vars[12] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddBackgroundTrainingEvent(vars,weight);
	     else
	       factory->AddBackgroundTestEvent(vars,weight);
	  }

	factory->PrepareTrainingAndTestTree("","",
					    "SplitMode=Random:NormMode=NumEvents:!V" );
	
	factory->BookMethod(TMVA::Types::kBDT,"BDT",
			    "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
	
	factory->TrainAllMethods();
	
	factory->TestAllMethods();
	
	factory->EvaluateAllMethods();

	outfile->Write();
	outfile->Close();
     }

   // b3j4 tH Hct vs ttbar
   else if( imva == 1 )
     {
	TFile* outfile = TFile::Open("TMVA_HctST_b3j4.root","RECREATE");
	
	double weight;
	
	double HiggsMass_TOPHLEPBB;
	double TopHadMass_TOPTOPLEPHAD;
	double MVA_TOPHLEPBB;
	double MVA_TOPTOPLEPHAD;
	double HiggsEta_TOPHLEPBB;
	double TopLepMass_TOPHLEPBB;
	double TopLepMass_TOPTOPLEPHAD;
	double TopLepPt_TOPHLEPBB;
	double TopLepEta_TOPHLEPBB;
	double HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	double TopLepHiggsDr_TOPHLEPBB;
	double TopLepTopHadDr_TOPTOPLEPHAD;

	TMVA::Factory *factory = new TMVA::Factory("TMVA_HctST_b3j4",outfile,
						   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D:AnalysisType=Classification" );
   
	factory->AddVariable("HiggsMass_TOPHLEPBB",'D');
	factory->AddVariable("TopHadMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("MVA_TOPHLEPBB",'D');
	factory->AddVariable("MVA_TOPTOPLEPHAD",'D');
	factory->AddVariable("HiggsEta_TOPHLEPBB",'D');
	factory->AddVariable("TopLepMass_TOPHLEPBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("TopLepPt_TOPHLEPBB",'D');
	factory->AddVariable("TopLepEta_TOPHLEPBB",'D');
	factory->AddVariable("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",'D');
	factory->AddVariable("TopLepHiggsDr_TOPHLEPBB",'D');
	factory->AddVariable("TopLepTopHadDr_TOPTOPLEPHAD",'D');

	TChain tr_sig("tr_all_b3j4");
	tr_sig.Add("../histTEST_MERGED/ST_TH_1L3B_Hct.root");

	TChain tr_bkg("tr_all_b3j4");
	tr_bkg.Add("../histTEST_MERGED/TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
   
	tr_sig.SetBranchAddress("weight",&weight);
	tr_sig.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	tr_bkg.SetBranchAddress("weight",&weight);
	tr_bkg.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	TRandom3 *r = new TRandom3(666);
	
	std::vector<double> vars(12);

	for(int i=0;i<tr_sig.GetEntries();i++)
	  {
	     tr_sig.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPHLEPBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPHLEPBB;
	     vars[5] = TopLepMass_TOPHLEPBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPHLEPBB;
	     vars[8] = TopLepEta_TOPHLEPBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[10] = TopLepHiggsDr_TOPHLEPBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddSignalTrainingEvent(vars,weight);
	     else
	       factory->AddSignalTestEvent(vars,weight);
	  }
	
	for(int i=0;i<tr_bkg.GetEntries();i++)
	  {
	     tr_bkg.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPHLEPBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPHLEPBB;
	     vars[5] = TopLepMass_TOPHLEPBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPHLEPBB;
	     vars[8] = TopLepEta_TOPHLEPBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[10] = TopLepHiggsDr_TOPHLEPBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddBackgroundTrainingEvent(vars,weight);
	     else
	       factory->AddBackgroundTestEvent(vars,weight);
	  }

	factory->PrepareTrainingAndTestTree("","",
					    "SplitMode=Random:NormMode=NumEvents:!V" );
	
	factory->BookMethod(TMVA::Types::kBDT,"BDT",
			    "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
	
	factory->TrainAllMethods();
	
	factory->TestAllMethods();
	
	factory->EvaluateAllMethods();

	outfile->Write();
	outfile->Close();
     }

   // b3j4 ttbar Hut vs ttbar
   else if( imva == 2 )
     {
	TFile* outfile = TFile::Open("TMVA_HutTT_b3j4.root","RECREATE");
	
	double weight;
	
	double HiggsMass_TOPTOPLEPHBB;
	double TopHadMass_TOPTOPLEPHAD;
	double MVA_TOPTOPLEPHBB;
	double MVA_TOPTOPLEPHAD;
	double HiggsEta_TOPTOPLEPHBB;
	double TopLepMass_TOPTOPLEPHBB;
	double TopLepMass_TOPTOPLEPHAD;
	double TopLepPt_TOPTOPLEPHBB;
	double TopLepEta_TOPTOPLEPHBB;
	double HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	double TopLepHiggsDr_TOPTOPLEPHBB;
	double TopLepTopHadDr_TOPTOPLEPHAD;

	TMVA::Factory *factory = new TMVA::Factory("TMVA_HutTT_b3j4",outfile,
						   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D:AnalysisType=Classification" );
   
	factory->AddVariable("HiggsMass_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopHadMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("MVA_TOPTOPLEPHBB",'D');
	factory->AddVariable("MVA_TOPTOPLEPHAD",'D');
	factory->AddVariable("HiggsEta_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("TopLepPt_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepEta_TOPTOPLEPHBB",'D');
	factory->AddVariable("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepHiggsDr_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepTopHadDr_TOPTOPLEPHAD",'D');

	TChain tr_sig("tr_all_b3j4");
	tr_sig.Add("../histTEST_MERGED/TT_TopLeptonicDecay_TH_1L3B_Eta_Hut.root");
	tr_sig.Add("../histTEST_MERGED/TT_AntitopLeptonicDecay_TH_1L3B_Eta_Hut.root");

	TChain tr_bkg("tr_all_b3j4");
	tr_bkg.Add("../histTEST_MERGED/TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
   
	tr_sig.SetBranchAddress("weight",&weight);
	tr_sig.SetBranchAddress("HiggsMass_TOPTOPLEPHBB",&HiggsMass_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHBB",&MVA_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("HiggsEta_TOPTOPLEPHBB",&HiggsEta_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHBB",&TopLepMass_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("TopLepPt_TOPTOPLEPHBB",&TopLepPt_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepEta_TOPTOPLEPHBB",&TopLepEta_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",&HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepHiggsDr_TOPTOPLEPHBB",&TopLepHiggsDr_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	tr_bkg.SetBranchAddress("weight",&weight);
	tr_bkg.SetBranchAddress("HiggsMass_TOPTOPLEPHBB",&HiggsMass_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHBB",&MVA_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("HiggsEta_TOPTOPLEPHBB",&HiggsEta_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHBB",&TopLepMass_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("TopLepPt_TOPTOPLEPHBB",&TopLepPt_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepEta_TOPTOPLEPHBB",&TopLepEta_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",&HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepHiggsDr_TOPTOPLEPHBB",&TopLepHiggsDr_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	TRandom3 *r = new TRandom3(666);
	
	std::vector<double> vars(12);

	for(int i=0;i<tr_sig.GetEntries();i++)
	  {
	     tr_sig.GetEntry(i);

	     if( HiggsMass_TOPTOPLEPHBB > 500. ) HiggsMass_TOPTOPLEPHBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPTOPLEPHBB > 500. ) TopLepMass_TOPTOPLEPHBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPTOPLEPHBB > 1000. ) TopLepPt_TOPTOPLEPHBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPTOPLEPHBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPTOPLEPHBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPTOPLEPHBB;
	     vars[5] = TopLepMass_TOPTOPLEPHBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPTOPLEPHBB;
	     vars[8] = TopLepEta_TOPTOPLEPHBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	     vars[10] = TopLepHiggsDr_TOPTOPLEPHBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddSignalTrainingEvent(vars,weight);
	     else
	       factory->AddSignalTestEvent(vars,weight);
	  }
	
	for(int i=0;i<tr_bkg.GetEntries();i++)
	  {
	     tr_bkg.GetEntry(i);

	     if( HiggsMass_TOPTOPLEPHBB > 500. ) HiggsMass_TOPTOPLEPHBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPTOPLEPHBB > 500. ) TopLepMass_TOPTOPLEPHBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPTOPLEPHBB > 1000. ) TopLepPt_TOPTOPLEPHBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPTOPLEPHBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPTOPLEPHBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPTOPLEPHBB;
	     vars[5] = TopLepMass_TOPTOPLEPHBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPTOPLEPHBB;
	     vars[8] = TopLepEta_TOPTOPLEPHBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	     vars[10] = TopLepHiggsDr_TOPTOPLEPHBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddBackgroundTrainingEvent(vars,weight);
	     else
	       factory->AddBackgroundTestEvent(vars,weight);
	  }

	factory->PrepareTrainingAndTestTree("","",
					    "SplitMode=Random:NormMode=NumEvents:!V" );
	
	factory->BookMethod(TMVA::Types::kBDT,"BDT",
			    "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
	
	factory->TrainAllMethods();
	
	factory->TestAllMethods();
	
	factory->EvaluateAllMethods();

	outfile->Write();
	outfile->Close();
     }

   // b3j4 ttbar Hct vs ttbar
   else if( imva == 3 )
     {
	TFile* outfile = TFile::Open("TMVA_HctTT_b3j4.root","RECREATE");
	
	double weight;
	
	double HiggsMass_TOPTOPLEPHBB;
	double TopHadMass_TOPTOPLEPHAD;
	double MVA_TOPTOPLEPHBB;
	double MVA_TOPTOPLEPHAD;
	double HiggsEta_TOPTOPLEPHBB;
	double TopLepMass_TOPTOPLEPHBB;
	double TopLepMass_TOPTOPLEPHAD;
	double TopLepPt_TOPTOPLEPHBB;
	double TopLepEta_TOPTOPLEPHBB;
	double HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	double TopLepHiggsDr_TOPTOPLEPHBB;
	double TopLepTopHadDr_TOPTOPLEPHAD;

	TMVA::Factory *factory = new TMVA::Factory("TMVA_HctTT_b3j4",outfile,
						   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D:AnalysisType=Classification" );
   
	factory->AddVariable("HiggsMass_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopHadMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("MVA_TOPTOPLEPHBB",'D');
	factory->AddVariable("MVA_TOPTOPLEPHAD",'D');
	factory->AddVariable("HiggsEta_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("TopLepPt_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepEta_TOPTOPLEPHBB",'D');
	factory->AddVariable("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepHiggsDr_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepTopHadDr_TOPTOPLEPHAD",'D');

	TChain tr_sig("tr_all_b3j4");
	tr_sig.Add("../histTEST_MERGED/TT_TopLeptonicDecay_TH_1L3B_Eta_Hct.root");
	tr_sig.Add("../histTEST_MERGED/TT_AntitopLeptonicDecay_TH_1L3B_Eta_Hct.root");

	TChain tr_bkg("tr_all_b3j4");
	tr_bkg.Add("../histTEST_MERGED/TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
   
	tr_sig.SetBranchAddress("weight",&weight);
	tr_sig.SetBranchAddress("HiggsMass_TOPTOPLEPHBB",&HiggsMass_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHBB",&MVA_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("HiggsEta_TOPTOPLEPHBB",&HiggsEta_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHBB",&TopLepMass_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("TopLepPt_TOPTOPLEPHBB",&TopLepPt_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepEta_TOPTOPLEPHBB",&TopLepEta_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",&HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepHiggsDr_TOPTOPLEPHBB",&TopLepHiggsDr_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	tr_bkg.SetBranchAddress("weight",&weight);
	tr_bkg.SetBranchAddress("HiggsMass_TOPTOPLEPHBB",&HiggsMass_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHBB",&MVA_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("HiggsEta_TOPTOPLEPHBB",&HiggsEta_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHBB",&TopLepMass_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("TopLepPt_TOPTOPLEPHBB",&TopLepPt_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepEta_TOPTOPLEPHBB",&TopLepEta_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",&HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepHiggsDr_TOPTOPLEPHBB",&TopLepHiggsDr_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	TRandom3 *r = new TRandom3(666);
	
	std::vector<double> vars(12);

	for(int i=0;i<tr_sig.GetEntries();i++)
	  {
	     tr_sig.GetEntry(i);

	     if( HiggsMass_TOPTOPLEPHBB > 500. ) HiggsMass_TOPTOPLEPHBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPTOPLEPHBB > 500. ) TopLepMass_TOPTOPLEPHBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPTOPLEPHBB > 1000. ) TopLepPt_TOPTOPLEPHBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPTOPLEPHBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPTOPLEPHBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPTOPLEPHBB;
	     vars[5] = TopLepMass_TOPTOPLEPHBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPTOPLEPHBB;
	     vars[8] = TopLepEta_TOPTOPLEPHBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	     vars[10] = TopLepHiggsDr_TOPTOPLEPHBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddSignalTrainingEvent(vars,weight);
	     else
	       factory->AddSignalTestEvent(vars,weight);
	  }
	
	for(int i=0;i<tr_bkg.GetEntries();i++)
	  {
	     tr_bkg.GetEntry(i);

	     if( HiggsMass_TOPTOPLEPHBB > 500. ) HiggsMass_TOPTOPLEPHBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPTOPLEPHBB > 500. ) TopLepMass_TOPTOPLEPHBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPTOPLEPHBB > 1000. ) TopLepPt_TOPTOPLEPHBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPTOPLEPHBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPTOPLEPHBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPTOPLEPHBB;
	     vars[5] = TopLepMass_TOPTOPLEPHBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPTOPLEPHBB;
	     vars[8] = TopLepEta_TOPTOPLEPHBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	     vars[10] = TopLepHiggsDr_TOPTOPLEPHBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddBackgroundTrainingEvent(vars,weight);
	     else
	       factory->AddBackgroundTestEvent(vars,weight);
	  }

	factory->PrepareTrainingAndTestTree("","",
					    "SplitMode=Random:NormMode=NumEvents:!V" );
	
	factory->BookMethod(TMVA::Types::kBDT,"BDT",
			    "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
	
	factory->TrainAllMethods();
	
	factory->TestAllMethods();
	
	factory->EvaluateAllMethods();

	outfile->Write();
	outfile->Close();
     }

   //////////
   // b3j3 //
   //////////
   
   // b3j3 tH Hut vs ttbar
   else if( imva == 4 )
     {
	TFile* outfile = TFile::Open("TMVA_HutST_b3j3.root","RECREATE");
	
	double weight;
	
	double HiggsMass_TOPHLEPBB;
	double MVA_TOPHLEPBB;
	int LepCharge;
	double HiggsEta_TOPHLEPBB;
	double TopLepMass_TOPHLEPBB;
	double TopLepPt_TOPHLEPBB;
	double TopLepEta_TOPHLEPBB;
	double HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	double TopLepHiggsDr_TOPHLEPBB;

	TMVA::Factory *factory = new TMVA::Factory("TMVA_HutST_b3j3",outfile,
						   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D:AnalysisType=Classification" );
   
	factory->AddVariable("HiggsMass_TOPHLEPBB",'D');
	factory->AddVariable("MVA_TOPHLEPBB",'D');
	factory->AddVariable("LepCharge",'I');
	factory->AddVariable("HiggsEta_TOPHLEPBB",'D');
	factory->AddVariable("TopLepMass_TOPHLEPBB",'D');
	factory->AddVariable("TopLepPt_TOPHLEPBB",'D');
	factory->AddVariable("TopLepEta_TOPHLEPBB",'D');
	factory->AddVariable("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",'D');
	factory->AddVariable("TopLepHiggsDr_TOPHLEPBB",'D');

	TChain tr_sig("tr_all_b3j3");
	tr_sig.Add("../histTEST_MERGED/ST_TH_1L3B.root");

	TChain tr_bkg("tr_all_b3j3");
	tr_bkg.Add("../histTEST_MERGED/TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
   
	tr_sig.SetBranchAddress("weight",&weight);
	tr_sig.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_sig.SetBranchAddress("LepCharge",&LepCharge);
	tr_sig.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);

	tr_bkg.SetBranchAddress("weight",&weight);
	tr_bkg.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_bkg.SetBranchAddress("LepCharge",&LepCharge);
	tr_bkg.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);

	TRandom3 *r = new TRandom3(666);
	
	std::vector<double> vars(9);

	for(int i=0;i<tr_sig.GetEntries();i++)
	  {
	     tr_sig.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = MVA_TOPHLEPBB;
	     vars[2] = LepCharge;
	     vars[3] = HiggsEta_TOPHLEPBB;
	     vars[4] = TopLepMass_TOPHLEPBB;
	     vars[5] = TopLepPt_TOPHLEPBB;
	     vars[6] = TopLepEta_TOPHLEPBB;
	     vars[7] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[8] = TopLepHiggsDr_TOPHLEPBB;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddSignalTrainingEvent(vars,weight);
	     else
	       factory->AddSignalTestEvent(vars,weight);
	  }
	
	for(int i=0;i<tr_bkg.GetEntries();i++)
	  {
	     tr_bkg.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = MVA_TOPHLEPBB;
	     vars[2] = LepCharge;
	     vars[3] = HiggsEta_TOPHLEPBB;
	     vars[4] = TopLepMass_TOPHLEPBB;
	     vars[5] = TopLepPt_TOPHLEPBB;
	     vars[6] = TopLepEta_TOPHLEPBB;
	     vars[7] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[8] = TopLepHiggsDr_TOPHLEPBB;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddBackgroundTrainingEvent(vars,weight);
	     else
	       factory->AddBackgroundTestEvent(vars,weight);
	  }

	factory->PrepareTrainingAndTestTree("","",
					    "SplitMode=Random:NormMode=NumEvents:!V" );
	
	factory->BookMethod(TMVA::Types::kBDT,"BDT",
			    "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
	
	factory->TrainAllMethods();
	
	factory->TestAllMethods();
	
	factory->EvaluateAllMethods();

	outfile->Write();
	outfile->Close();
     }

   // b3j3 tH Hct vs ttbar
   else if( imva == 5 )
     {
	TFile* outfile = TFile::Open("TMVA_HctST_b3j3.root","RECREATE");
	
	double weight;
	
	double HiggsMass_TOPHLEPBB;
	double MVA_TOPHLEPBB;
	double HiggsEta_TOPHLEPBB;
	double TopLepMass_TOPHLEPBB;
	double TopLepPt_TOPHLEPBB;
	double TopLepEta_TOPHLEPBB;
	double HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	double TopLepHiggsDr_TOPHLEPBB;

	TMVA::Factory *factory = new TMVA::Factory("TMVA_HctST_b3j3",outfile,
						   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D:AnalysisType=Classification" );
   
	factory->AddVariable("HiggsMass_TOPHLEPBB",'D');
	factory->AddVariable("MVA_TOPHLEPBB",'D');
	factory->AddVariable("HiggsEta_TOPHLEPBB",'D');
	factory->AddVariable("TopLepMass_TOPHLEPBB",'D');
	factory->AddVariable("TopLepPt_TOPHLEPBB",'D');
	factory->AddVariable("TopLepEta_TOPHLEPBB",'D');
	factory->AddVariable("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",'D');
	factory->AddVariable("TopLepHiggsDr_TOPHLEPBB",'D');

	TChain tr_sig("tr_all_b3j3");
	tr_sig.Add("../histTEST_MERGED/ST_TH_1L3B_Hct.root");

	TChain tr_bkg("tr_all_b3j3");
	tr_bkg.Add("../histTEST_MERGED/TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
   
	tr_sig.SetBranchAddress("weight",&weight);
	tr_sig.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_sig.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);

	tr_bkg.SetBranchAddress("weight",&weight);
	tr_bkg.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_bkg.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);

	TRandom3 *r = new TRandom3(666);
	
	std::vector<double> vars(8);

	for(int i=0;i<tr_sig.GetEntries();i++)
	  {
	     tr_sig.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = MVA_TOPHLEPBB;
	     vars[2] = HiggsEta_TOPHLEPBB;
	     vars[3] = TopLepMass_TOPHLEPBB;
	     vars[4] = TopLepPt_TOPHLEPBB;
	     vars[5] = TopLepEta_TOPHLEPBB;
	     vars[6] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[7] = TopLepHiggsDr_TOPHLEPBB;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddSignalTrainingEvent(vars,weight);
	     else
	       factory->AddSignalTestEvent(vars,weight);
	  }
	
	for(int i=0;i<tr_bkg.GetEntries();i++)
	  {
	     tr_bkg.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = MVA_TOPHLEPBB;
	     vars[2] = HiggsEta_TOPHLEPBB;
	     vars[3] = TopLepMass_TOPHLEPBB;
	     vars[4] = TopLepPt_TOPHLEPBB;
	     vars[5] = TopLepEta_TOPHLEPBB;
	     vars[6] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[7] = TopLepHiggsDr_TOPHLEPBB;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddBackgroundTrainingEvent(vars,weight);
	     else
	       factory->AddBackgroundTestEvent(vars,weight);
	  }

	factory->PrepareTrainingAndTestTree("","",
					    "SplitMode=Random:NormMode=NumEvents:!V" );
	
	factory->BookMethod(TMVA::Types::kBDT,"BDT",
			    "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
	
	factory->TrainAllMethods();
	
	factory->TestAllMethods();
	
	factory->EvaluateAllMethods();

	outfile->Write();
	outfile->Close();
     }

   //////////
   // b2j4 //
   //////////
   
   // b2j4 tH Hut vs ttbar
   else if( imva == 6 )
     {
	TFile* outfile = TFile::Open("TMVA_HutST_b2j4.root","RECREATE");
	
	double weight;
	
	double HiggsMass_TOPHLEPBB;
	double TopHadMass_TOPTOPLEPHAD;
	double MVA_TOPHLEPBB;
	double MVA_TOPTOPLEPHAD;
	int LepCharge;
	double HiggsEta_TOPHLEPBB;
	double TopLepMass_TOPHLEPBB;
	double TopLepMass_TOPTOPLEPHAD;
	double TopLepPt_TOPHLEPBB;
	double TopLepEta_TOPHLEPBB;
	double HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	double TopLepHiggsDr_TOPHLEPBB;
	double TopLepTopHadDr_TOPTOPLEPHAD;

	TMVA::Factory *factory = new TMVA::Factory("TMVA_HutST_b2j4",outfile,
						   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D:AnalysisType=Classification" );
   
	factory->AddVariable("HiggsMass_TOPHLEPBB",'D');
	factory->AddVariable("TopHadMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("MVA_TOPHLEPBB",'D');
	factory->AddVariable("MVA_TOPTOPLEPHAD",'D');
	factory->AddVariable("LepCharge",'I');
	factory->AddVariable("HiggsEta_TOPHLEPBB",'D');
	factory->AddVariable("TopLepMass_TOPHLEPBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("TopLepPt_TOPHLEPBB",'D');
	factory->AddVariable("TopLepEta_TOPHLEPBB",'D');
	factory->AddVariable("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",'D');
	factory->AddVariable("TopLepHiggsDr_TOPHLEPBB",'D');
	factory->AddVariable("TopLepTopHadDr_TOPTOPLEPHAD",'D');

	TChain tr_sig("tr_all_b2j4");
	tr_sig.Add("../histTEST_MERGED/ST_TH_1L3B.root");

	TChain tr_bkg("tr_all_b2j4");
	tr_bkg.Add("../histTEST_MERGED/TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
   
	tr_sig.SetBranchAddress("weight",&weight);
	tr_sig.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("LepCharge",&LepCharge);
	tr_sig.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	tr_bkg.SetBranchAddress("weight",&weight);
	tr_bkg.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("LepCharge",&LepCharge);
	tr_bkg.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	TRandom3 *r = new TRandom3(666);
	
	std::vector<double> vars(13);

	for(int i=0;i<tr_sig.GetEntries();i++)
	  {
	     tr_sig.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPHLEPBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = LepCharge;
	     vars[5] = HiggsEta_TOPHLEPBB;
	     vars[6] = TopLepMass_TOPHLEPBB;
	     vars[7] = TopLepMass_TOPTOPLEPHAD;
	     vars[8] = TopLepPt_TOPHLEPBB;
	     vars[9] = TopLepEta_TOPHLEPBB;
	     vars[10] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[11] = TopLepHiggsDr_TOPHLEPBB;
	     vars[12] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddSignalTrainingEvent(vars,weight);
	     else
	       factory->AddSignalTestEvent(vars,weight);
	  }
	
	for(int i=0;i<tr_bkg.GetEntries();i++)
	  {
	     tr_bkg.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPHLEPBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = LepCharge;
	     vars[5] = HiggsEta_TOPHLEPBB;
	     vars[6] = TopLepMass_TOPHLEPBB;
	     vars[7] = TopLepMass_TOPTOPLEPHAD;
	     vars[8] = TopLepPt_TOPHLEPBB;
	     vars[9] = TopLepEta_TOPHLEPBB;
	     vars[10] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[11] = TopLepHiggsDr_TOPHLEPBB;
	     vars[12] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddBackgroundTrainingEvent(vars,weight);
	     else
	       factory->AddBackgroundTestEvent(vars,weight);
	  }

	factory->PrepareTrainingAndTestTree("","",
					    "SplitMode=Random:NormMode=NumEvents:!V" );
	
	factory->BookMethod(TMVA::Types::kBDT,"BDT",
			    "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
	
	factory->TrainAllMethods();
	
	factory->TestAllMethods();
	
	factory->EvaluateAllMethods();

	outfile->Write();
	outfile->Close();
     }

   // b2j4 tH Hct vs ttbar
   else if( imva == 7 )
     {
	TFile* outfile = TFile::Open("TMVA_HctST_b2j4.root","RECREATE");
	
	double weight;
	
	double HiggsMass_TOPHLEPBB;
	double TopHadMass_TOPTOPLEPHAD;
	double MVA_TOPHLEPBB;
	double MVA_TOPTOPLEPHAD;
	double HiggsEta_TOPHLEPBB;
	double TopLepMass_TOPHLEPBB;
	double TopLepMass_TOPTOPLEPHAD;
	double TopLepPt_TOPHLEPBB;
	double TopLepEta_TOPHLEPBB;
	double HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	double TopLepHiggsDr_TOPHLEPBB;
	double TopLepTopHadDr_TOPTOPLEPHAD;

	TMVA::Factory *factory = new TMVA::Factory("TMVA_HctST_b2j4",outfile,
						   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D:AnalysisType=Classification" );
   
	factory->AddVariable("HiggsMass_TOPHLEPBB",'D');
	factory->AddVariable("TopHadMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("MVA_TOPHLEPBB",'D');
	factory->AddVariable("MVA_TOPTOPLEPHAD",'D');
	factory->AddVariable("HiggsEta_TOPHLEPBB",'D');
	factory->AddVariable("TopLepMass_TOPHLEPBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("TopLepPt_TOPHLEPBB",'D');
	factory->AddVariable("TopLepEta_TOPHLEPBB",'D');
	factory->AddVariable("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",'D');
	factory->AddVariable("TopLepHiggsDr_TOPHLEPBB",'D');
	factory->AddVariable("TopLepTopHadDr_TOPTOPLEPHAD",'D');

	TChain tr_sig("tr_all_b2j4");
	tr_sig.Add("../histTEST_MERGED/ST_TH_1L3B_Hct.root");

	TChain tr_bkg("tr_all_b2j4");
	tr_bkg.Add("../histTEST_MERGED/TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
   
	tr_sig.SetBranchAddress("weight",&weight);
	tr_sig.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_sig.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);
	tr_sig.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	tr_bkg.SetBranchAddress("weight",&weight);
	tr_bkg.SetBranchAddress("HiggsMass_TOPHLEPBB",&HiggsMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("MVA_TOPHLEPBB",&MVA_TOPHLEPBB);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("HiggsEta_TOPHLEPBB",&HiggsEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPHLEPBB",&TopLepMass_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("TopLepPt_TOPHLEPBB",&TopLepPt_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepEta_TOPHLEPBB",&TopLepEta_TOPHLEPBB);
	tr_bkg.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPHLEPBB",&HiggsBJet1HiggsBJet2Dr_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepHiggsDr_TOPHLEPBB",&TopLepHiggsDr_TOPHLEPBB);
	tr_bkg.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	TRandom3 *r = new TRandom3(666);
	
	std::vector<double> vars(12);

	for(int i=0;i<tr_sig.GetEntries();i++)
	  {
	     tr_sig.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPHLEPBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPHLEPBB;
	     vars[5] = TopLepMass_TOPHLEPBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPHLEPBB;
	     vars[8] = TopLepEta_TOPHLEPBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[10] = TopLepHiggsDr_TOPHLEPBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddSignalTrainingEvent(vars,weight);
	     else
	       factory->AddSignalTestEvent(vars,weight);
	  }
	
	for(int i=0;i<tr_bkg.GetEntries();i++)
	  {
	     tr_bkg.GetEntry(i);

	     if( HiggsMass_TOPHLEPBB > 500. ) HiggsMass_TOPHLEPBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPHLEPBB > 500. ) TopLepMass_TOPHLEPBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPHLEPBB > 1000. ) TopLepPt_TOPHLEPBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPHLEPBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPHLEPBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPHLEPBB;
	     vars[5] = TopLepMass_TOPHLEPBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPHLEPBB;
	     vars[8] = TopLepEta_TOPHLEPBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPHLEPBB;
	     vars[10] = TopLepHiggsDr_TOPHLEPBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddBackgroundTrainingEvent(vars,weight);
	     else
	       factory->AddBackgroundTestEvent(vars,weight);
	  }

	factory->PrepareTrainingAndTestTree("","",
					    "SplitMode=Random:NormMode=NumEvents:!V" );
	
	factory->BookMethod(TMVA::Types::kBDT,"BDT",
			    "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
	
	factory->TrainAllMethods();
	
	factory->TestAllMethods();
	
	factory->EvaluateAllMethods();

	outfile->Write();
	outfile->Close();
     }

   // b2j4 ttbar Hut vs ttbar
   else if( imva == 8 )
     {
	TFile* outfile = TFile::Open("TMVA_HutTT_b2j4.root","RECREATE");
	
	double weight;
	
	double HiggsMass_TOPTOPLEPHBB;
	double TopHadMass_TOPTOPLEPHAD;
	double MVA_TOPTOPLEPHBB;
	double MVA_TOPTOPLEPHAD;
	double HiggsEta_TOPTOPLEPHBB;
	double TopLepMass_TOPTOPLEPHBB;
	double TopLepMass_TOPTOPLEPHAD;
	double TopLepPt_TOPTOPLEPHBB;
	double TopLepEta_TOPTOPLEPHBB;
	double HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	double TopLepHiggsDr_TOPTOPLEPHBB;
	double TopLepTopHadDr_TOPTOPLEPHAD;

	TMVA::Factory *factory = new TMVA::Factory("TMVA_HutTT_b2j4",outfile,
						   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D:AnalysisType=Classification" );
   
	factory->AddVariable("HiggsMass_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopHadMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("MVA_TOPTOPLEPHBB",'D');
	factory->AddVariable("MVA_TOPTOPLEPHAD",'D');
	factory->AddVariable("HiggsEta_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("TopLepPt_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepEta_TOPTOPLEPHBB",'D');
	factory->AddVariable("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepHiggsDr_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepTopHadDr_TOPTOPLEPHAD",'D');

	TChain tr_sig("tr_all_b2j4");
	tr_sig.Add("../histTEST_MERGED/TT_TopLeptonicDecay_TH_1L3B_Eta_Hut.root");
	tr_sig.Add("../histTEST_MERGED/TT_AntitopLeptonicDecay_TH_1L3B_Eta_Hut.root");

	TChain tr_bkg("tr_all_b2j4");
	tr_bkg.Add("../histTEST_MERGED/TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
   
	tr_sig.SetBranchAddress("weight",&weight);
	tr_sig.SetBranchAddress("HiggsMass_TOPTOPLEPHBB",&HiggsMass_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHBB",&MVA_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("HiggsEta_TOPTOPLEPHBB",&HiggsEta_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHBB",&TopLepMass_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("TopLepPt_TOPTOPLEPHBB",&TopLepPt_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepEta_TOPTOPLEPHBB",&TopLepEta_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",&HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepHiggsDr_TOPTOPLEPHBB",&TopLepHiggsDr_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	tr_bkg.SetBranchAddress("weight",&weight);
	tr_bkg.SetBranchAddress("HiggsMass_TOPTOPLEPHBB",&HiggsMass_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHBB",&MVA_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("HiggsEta_TOPTOPLEPHBB",&HiggsEta_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHBB",&TopLepMass_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("TopLepPt_TOPTOPLEPHBB",&TopLepPt_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepEta_TOPTOPLEPHBB",&TopLepEta_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",&HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepHiggsDr_TOPTOPLEPHBB",&TopLepHiggsDr_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	TRandom3 *r = new TRandom3(666);
	
	std::vector<double> vars(12);

	for(int i=0;i<tr_sig.GetEntries();i++)
	  {
	     tr_sig.GetEntry(i);

	     if( HiggsMass_TOPTOPLEPHBB > 500. ) HiggsMass_TOPTOPLEPHBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPTOPLEPHBB > 500. ) TopLepMass_TOPTOPLEPHBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPTOPLEPHBB > 1000. ) TopLepPt_TOPTOPLEPHBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPTOPLEPHBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPTOPLEPHBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPTOPLEPHBB;
	     vars[5] = TopLepMass_TOPTOPLEPHBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPTOPLEPHBB;
	     vars[8] = TopLepEta_TOPTOPLEPHBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	     vars[10] = TopLepHiggsDr_TOPTOPLEPHBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddSignalTrainingEvent(vars,weight);
	     else
	       factory->AddSignalTestEvent(vars,weight);
	  }
	
	for(int i=0;i<tr_bkg.GetEntries();i++)
	  {
	     tr_bkg.GetEntry(i);

	     if( HiggsMass_TOPTOPLEPHBB > 500. ) HiggsMass_TOPTOPLEPHBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPTOPLEPHBB > 500. ) TopLepMass_TOPTOPLEPHBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPTOPLEPHBB > 1000. ) TopLepPt_TOPTOPLEPHBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPTOPLEPHBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPTOPLEPHBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPTOPLEPHBB;
	     vars[5] = TopLepMass_TOPTOPLEPHBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPTOPLEPHBB;
	     vars[8] = TopLepEta_TOPTOPLEPHBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	     vars[10] = TopLepHiggsDr_TOPTOPLEPHBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddBackgroundTrainingEvent(vars,weight);
	     else
	       factory->AddBackgroundTestEvent(vars,weight);
	  }

	factory->PrepareTrainingAndTestTree("","",
					    "SplitMode=Random:NormMode=NumEvents:!V" );
	
	factory->BookMethod(TMVA::Types::kBDT,"BDT",
			    "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
	
	factory->TrainAllMethods();
	
	factory->TestAllMethods();
	
	factory->EvaluateAllMethods();

	outfile->Write();
	outfile->Close();
     }

   // b2j4 ttbar Hct vs ttbar
   else if( imva == 9 )
     {
	TFile* outfile = TFile::Open("TMVA_HctTT_b2j4.root","RECREATE");
	
	double weight;
	
	double HiggsMass_TOPTOPLEPHBB;
	double TopHadMass_TOPTOPLEPHAD;
	double MVA_TOPTOPLEPHBB;
	double MVA_TOPTOPLEPHAD;
	double HiggsEta_TOPTOPLEPHBB;
	double TopLepMass_TOPTOPLEPHBB;
	double TopLepMass_TOPTOPLEPHAD;
	double TopLepPt_TOPTOPLEPHBB;
	double TopLepEta_TOPTOPLEPHBB;
	double HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	double TopLepHiggsDr_TOPTOPLEPHBB;
	double TopLepTopHadDr_TOPTOPLEPHAD;

	TMVA::Factory *factory = new TMVA::Factory("TMVA_HctTT_b2j4",outfile,
						   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D:AnalysisType=Classification" );
   
	factory->AddVariable("HiggsMass_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopHadMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("MVA_TOPTOPLEPHBB",'D');
	factory->AddVariable("MVA_TOPTOPLEPHAD",'D');
	factory->AddVariable("HiggsEta_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepMass_TOPTOPLEPHAD",'D');
	factory->AddVariable("TopLepPt_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepEta_TOPTOPLEPHBB",'D');
	factory->AddVariable("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepHiggsDr_TOPTOPLEPHBB",'D');
	factory->AddVariable("TopLepTopHadDr_TOPTOPLEPHAD",'D');

	TChain tr_sig("tr_all_b2j4");
	tr_sig.Add("../histTEST_MERGED/TT_TopLeptonicDecay_TH_1L3B_Eta_Hct.root");
	tr_sig.Add("../histTEST_MERGED/TT_AntitopLeptonicDecay_TH_1L3B_Eta_Hct.root");

	TChain tr_bkg("tr_all_b2j4");
	tr_bkg.Add("../histTEST_MERGED/TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
   
	tr_sig.SetBranchAddress("weight",&weight);
	tr_sig.SetBranchAddress("HiggsMass_TOPTOPLEPHBB",&HiggsMass_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHBB",&MVA_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("HiggsEta_TOPTOPLEPHBB",&HiggsEta_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHBB",&TopLepMass_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_sig.SetBranchAddress("TopLepPt_TOPTOPLEPHBB",&TopLepPt_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepEta_TOPTOPLEPHBB",&TopLepEta_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",&HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepHiggsDr_TOPTOPLEPHBB",&TopLepHiggsDr_TOPTOPLEPHBB);
	tr_sig.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	tr_bkg.SetBranchAddress("weight",&weight);
	tr_bkg.SetBranchAddress("HiggsMass_TOPTOPLEPHBB",&HiggsMass_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopHadMass_TOPTOPLEPHAD",&TopHadMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHBB",&MVA_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("MVA_TOPTOPLEPHAD",&MVA_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("HiggsEta_TOPTOPLEPHBB",&HiggsEta_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHBB",&TopLepMass_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepMass_TOPTOPLEPHAD",&TopLepMass_TOPTOPLEPHAD);
	tr_bkg.SetBranchAddress("TopLepPt_TOPTOPLEPHBB",&TopLepPt_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepEta_TOPTOPLEPHBB",&TopLepEta_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB",&HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepHiggsDr_TOPTOPLEPHBB",&TopLepHiggsDr_TOPTOPLEPHBB);
	tr_bkg.SetBranchAddress("TopLepTopHadDr_TOPTOPLEPHAD",&TopLepTopHadDr_TOPTOPLEPHAD);

	TRandom3 *r = new TRandom3(666);
	
	std::vector<double> vars(12);

	for(int i=0;i<tr_sig.GetEntries();i++)
	  {
	     tr_sig.GetEntry(i);

	     if( HiggsMass_TOPTOPLEPHBB > 500. ) HiggsMass_TOPTOPLEPHBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPTOPLEPHBB > 500. ) TopLepMass_TOPTOPLEPHBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPTOPLEPHBB > 1000. ) TopLepPt_TOPTOPLEPHBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPTOPLEPHBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPTOPLEPHBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPTOPLEPHBB;
	     vars[5] = TopLepMass_TOPTOPLEPHBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPTOPLEPHBB;
	     vars[8] = TopLepEta_TOPTOPLEPHBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	     vars[10] = TopLepHiggsDr_TOPTOPLEPHBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddSignalTrainingEvent(vars,weight);
	     else
	       factory->AddSignalTestEvent(vars,weight);
	  }
	
	for(int i=0;i<tr_bkg.GetEntries();i++)
	  {
	     tr_bkg.GetEntry(i);

	     if( HiggsMass_TOPTOPLEPHBB > 500. ) HiggsMass_TOPTOPLEPHBB = 500.;
	     if( TopHadMass_TOPTOPLEPHAD > 1000. ) TopHadMass_TOPTOPLEPHAD = 1000.;
	     if( TopLepMass_TOPTOPLEPHBB > 500. ) TopLepMass_TOPTOPLEPHBB = 500.;
	     if( TopLepMass_TOPTOPLEPHAD > 500. ) TopLepMass_TOPTOPLEPHAD = 500.;
	     if( TopLepPt_TOPTOPLEPHBB > 1000. ) TopLepPt_TOPTOPLEPHBB = 1000.;
	     
	     vars[0] = HiggsMass_TOPTOPLEPHBB;
	     vars[1] = TopHadMass_TOPTOPLEPHAD;
	     vars[2] = MVA_TOPTOPLEPHBB;
	     vars[3] = MVA_TOPTOPLEPHAD;
	     vars[4] = HiggsEta_TOPTOPLEPHBB;
	     vars[5] = TopLepMass_TOPTOPLEPHBB;
	     vars[6] = TopLepMass_TOPTOPLEPHAD;
	     vars[7] = TopLepPt_TOPTOPLEPHBB;
	     vars[8] = TopLepEta_TOPTOPLEPHBB;
	     vars[9] = HiggsBJet1HiggsBJet2Dr_TOPTOPLEPHBB;
	     vars[10] = TopLepHiggsDr_TOPTOPLEPHBB;
	     vars[11] = TopLepTopHadDr_TOPTOPLEPHAD;
	     
	     float rnd = r->Rndm();
	     if( rnd < 0.5 )
	       factory->AddBackgroundTrainingEvent(vars,weight);
	     else
	       factory->AddBackgroundTestEvent(vars,weight);
	  }

	factory->PrepareTrainingAndTestTree("","",
					    "SplitMode=Random:NormMode=NumEvents:!V" );
	
	factory->BookMethod(TMVA::Types::kBDT,"BDT",
			    "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
	
	factory->TrainAllMethods();
	
	factory->TestAllMethods();
	
	factory->EvaluateAllMethods();

	outfile->Write();
	outfile->Close();
     }
}
