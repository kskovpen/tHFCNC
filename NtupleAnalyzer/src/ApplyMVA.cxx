#include "../include/ApplyMVA.h"

ApplyMVA::ApplyMVA(std::string home)
{
   _home = home;
}

ApplyMVA::~ApplyMVA()
{
}

void ApplyMVA::init()
{
   reader = new TMVA::Reader("!Color:!Silent");

   reader->AddVariable("H_m",&_in_H_m);
   reader->AddVariable("H_eta",&_in_H_eta);
   reader->AddVariable("top_m",&_in_top_m);
   reader->AddVariable("top_pt",&_in_top_pt);
   reader->AddVariable("top_eta",&_in_top_eta);
   reader->AddVariable("Hb1_Hb2_dr",&_in_Hb1_Hb2_dr);
   reader->AddVariable("W_m",&_in_W_m);
   reader->AddVariable("H_nu_dr",&_in_H_nu_dr);
   reader->AddVariable("H_l_dr",&_in_H_l_dr);
   reader->AddVariable("chi2",&_in_chi2);
   reader->AddVariable("l_charge",&_in_l_charge);
   reader->AddVariable("TTbar_chi2",&_in_TTbar_chi2);
   reader->AddVariable("TTbar_topLep_m",&_in_TTbar_topLep_m);
   reader->AddVariable("TTbar_tbLep_tWLep_Dr",&_in_TTbar_tbLep_tWLep_Dr);
   reader->AddVariable("TTbar_tbHad_tWHad_Dr",&_in_TTbar_tbHad_tWHad_Dr);

   std::string weightsFile = _home+"/MVA/weights/TMVAClassification_BDT.weights.xml";
   reader->BookMVA("BDTG method",weightsFile.c_str());
   
   std::cout << "ApplyMVA initialisation done" << std::endl;
}

void ApplyMVA::run()
{
   _in_H_m = _H_m;
   _in_H_eta = _H_eta;
   _in_top_m = _top_m;
   _in_top_pt = _top_pt;
   _in_top_eta = _top_eta;
   _in_Hb1_Hb2_dr = _Hb1_Hb2_dr;
   _in_W_m = _W_m;
   _in_H_nu_dr = _H_nu_dr;
   _in_H_l_dr = _H_l_dr;
   _in_chi2 = _chi2;
   _in_l_charge = _l_charge;
   _in_TTbar_chi2 = _TTbar_chi2;
   _in_TTbar_topLep_m = _TTbar_topLep_m;
   _in_TTbar_tbLep_tWLep_Dr = _TTbar_tbLep_tWLep_Dr;
   _in_TTbar_tbHad_tWHad_Dr = _TTbar_tbHad_tWHad_Dr;
   
   _disc = reader->EvaluateMVA("BDTG method");
}

void ApplyMVA::close()
{
}
