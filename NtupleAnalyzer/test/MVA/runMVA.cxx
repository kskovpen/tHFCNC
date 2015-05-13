#include "runMVA.h"

int main(int argc, char *argv[])
{
   TFile* outfile = TFile::Open("TMVA.root","RECREATE");
   
   double weight;
   double H_m;
//   double H_pt;
   double H_eta;
   double top_pt;
   double top_eta;
   double top_m;
//   int njet;
//   double HT;
   double Hb1_Hb2_dr;
   double W_m;
//   double W_pt;
//   double W_eta;
   double H_nu_dr;
   double H_l_dr;
   int l_charge;
   double chi2;
   
   TMVA::Factory *factory = new TMVA::Factory("TMVAClassification",outfile,
					      "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   
   factory->AddVariable("H_m",'D');
//   factory->AddVariable("H_pt",'D');
   factory->AddVariable("H_eta",'D');
   factory->AddVariable("top_m",'D');
   factory->AddVariable("top_pt",'D');
   factory->AddVariable("top_eta",'D');
//   factory->AddVariable("njet",'I');
//   factory->AddVariable("HT",'D');
   factory->AddVariable("Hb1_Hb2_dr",'D');
   factory->AddVariable("W_m",'D');
//   factory->AddVariable("W_pt",'D');
//   factory->AddVariable("W_eta",'D');
   factory->AddVariable("H_nu_dr",'D');
   factory->AddVariable("H_l_dr",'D');
   factory->AddVariable("chi2",'D');
   factory->AddVariable("l_charge",'I');

   TFile *input_sig_hut = TFile::Open("../histMERGE/TTtoTHToBB_1L_Kappa_hut.root");
   //TFile *input_sig_hut = TFile::Open("../histMERGE/tHToBB_1L_Kappa_hut.root");
   TFile *input_bkg_ttbar = TFile::Open("../histMERGE/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola.root");
   
   TTree *tr_sig_hut = (TTree*)input_sig_hut->Get("tr_m");
   TTree *tr_bkg_ttbar = (TTree*)input_bkg_ttbar->Get("tr_m");
   
   tr_sig_hut->SetBranchAddress("weight",&weight);
   tr_sig_hut->SetBranchAddress("H_m",&H_m);
//   tr_sig_hut->SetBranchAddress("H_pt",&H_pt);
   tr_sig_hut->SetBranchAddress("H_eta",&H_eta);
   tr_sig_hut->SetBranchAddress("top_m",&top_m);
   tr_sig_hut->SetBranchAddress("top_pt",&top_pt);
   tr_sig_hut->SetBranchAddress("top_eta",&top_eta);
//   tr_sig_hut->SetBranchAddress("njet",&njet);
//   tr_sig_hut->SetBranchAddress("HT",&HT);
   tr_sig_hut->SetBranchAddress("Hb1_Hb2_dr",&Hb1_Hb2_dr);
   tr_sig_hut->SetBranchAddress("W_m",&W_m);
//   tr_sig_hut->SetBranchAddress("W_pt",&W_pt);
//   tr_sig_hut->SetBranchAddress("W_eta",&W_eta);
   tr_sig_hut->SetBranchAddress("H_nu_dr",&H_nu_dr);
   tr_sig_hut->SetBranchAddress("H_l_dr",&H_l_dr);
   tr_sig_hut->SetBranchAddress("chi2",&chi2);
   tr_sig_hut->SetBranchAddress("l_charge",&l_charge);

   tr_bkg_ttbar->SetBranchAddress("weight",&weight);
   tr_bkg_ttbar->SetBranchAddress("H_m",&H_m);
//   tr_bkg_ttbar->SetBranchAddress("H_pt",&H_pt);
   tr_bkg_ttbar->SetBranchAddress("H_eta",&H_eta);
   tr_bkg_ttbar->SetBranchAddress("top_m",&top_m);
   tr_bkg_ttbar->SetBranchAddress("top_pt",&top_pt);
   tr_bkg_ttbar->SetBranchAddress("top_eta",&top_eta);
//   tr_bkg_ttbar->SetBranchAddress("njet",&njet);
//   tr_bkg_ttbar->SetBranchAddress("HT",&HT);
   tr_bkg_ttbar->SetBranchAddress("Hb1_Hb2_dr",&Hb1_Hb2_dr);
   tr_bkg_ttbar->SetBranchAddress("W_m",&W_m);
//   tr_bkg_ttbar->SetBranchAddress("W_pt",&W_pt);
//   tr_bkg_ttbar->SetBranchAddress("W_eta",&W_eta);
   tr_bkg_ttbar->SetBranchAddress("H_nu_dr",&H_nu_dr);
   tr_bkg_ttbar->SetBranchAddress("H_l_dr",&H_l_dr);
   tr_bkg_ttbar->SetBranchAddress("chi2",&chi2);
   tr_bkg_ttbar->SetBranchAddress("l_charge",&l_charge);

   std::vector<double> vars(11);

   for(int i=0;i<tr_sig_hut->GetEntries();i++) 
     {
	tr_sig_hut->GetEntry(i);
	vars[0] = H_m;
//	vars[1] = H_pt;
	vars[1] = H_eta;
	vars[2] = top_m;
	vars[3] = top_pt;
	vars[4] = top_eta;
//	vars[6] = njet;
//	vars[7] = HT;
	vars[5] = Hb1_Hb2_dr;
	vars[6] = W_m;
//	vars[8] = W_pt;
//	vars[9] = W_eta;
	vars[7] = H_nu_dr;
	vars[8] = H_l_dr;
	vars[9] = chi2;
	vars[10] = l_charge;
	if( i < tr_sig_hut->GetEntries()/2 )
	  factory->AddSignalTrainingEvent(vars,weight);
	else
	  factory->AddSignalTestEvent(vars,weight);
     }
   
   for(int i=0;i<tr_bkg_ttbar->GetEntries();i++) 
     {
	tr_bkg_ttbar->GetEntry(i);
	vars[0] = H_m;
//	vars[1] = H_pt;
	vars[1] = H_eta;
	vars[2] = top_m;
	vars[3] = top_pt;
	vars[4] = top_eta;
//	vars[6] = njet;
//	vars[7] = HT;
	vars[5] = Hb1_Hb2_dr;
	vars[6] = W_m;
//	vars[8] = W_pt;
//	vars[9] = W_eta;
	vars[7] = H_nu_dr;
	vars[8] = H_l_dr;
	vars[9] = chi2;
	vars[10] = l_charge;
	if( i < tr_bkg_ttbar->GetEntries()/2 )
	  factory->AddBackgroundTrainingEvent(vars,weight);
	else
	  factory->AddBackgroundTestEvent(vars,weight);
     }

   factory->PrepareTrainingAndTestTree("","",
				       "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );
   
   factory->BookMethod(TMVA::Types::kBDT,"BDT",
		       "!H:!V:NTrees=100:MaxDepth=3:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
   
   factory->TrainAllMethods();

   factory->TestAllMethods();
   
   factory->EvaluateAllMethods();
   
   outfile->Write();
   outfile->Close();
}
