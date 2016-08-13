#ifndef APPLYMVA_H
#define APPLYMVA_H

#include "Analyzer.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

class ApplyMVA
{
   
 public:

   ApplyMVA(std::string home);
   virtual ~ApplyMVA();
   
   void setVariable_H_m(double v)       {_H_m = v;};
   void setVariable_H_eta(double v)       {_H_eta = v;};
   void setVariable_top_m(double v)       {_top_m = v;};
   void setVariable_top_pt(double v)       {_top_pt = v;};
   void setVariable_top_eta(double v)       {_top_eta = v;};
   void setVariable_Hb1_Hb2_dr(double v)       {_Hb1_Hb2_dr = v;};
   void setVariable_W_m(double v)       {_W_m = v;};
   void setVariable_H_nu_dr(double v)       {_H_nu_dr = v;};
   void setVariable_H_l_dr(double v)       {_H_l_dr = v;};
   void setVariable_chi2(double v)       {_chi2 = v;};
   void setVariable_l_charge(double v)       {_l_charge = v;};
   void setVariable_TTbar_chi2(double v)       {_TTbar_chi2 = v;};
   void setVariable_TTbar_topLep_m(double v)       {_TTbar_topLep_m = v;};
   void setVariable_TTbar_tbLep_tWLep_Dr(double v)       {_TTbar_tbLep_tWLep_Dr = v;};
   void setVariable_TTbar_tbHad_tWHad_Dr(double v)       {_TTbar_tbHad_tWHad_Dr = v;};

   double disc() {return _disc;};
   
   void init();
   void run();
   void close();

 protected:

   TMVA::Reader* reader;
   
   std::string _home;

   double _disc;
   
   double _H_m; float _in_H_m;
   double _H_eta; float _in_H_eta;
   double _top_m; float _in_top_m;
   double _top_pt; float _in_top_pt;
   double _top_eta; float _in_top_eta;
   double _Hb1_Hb2_dr; float _in_Hb1_Hb2_dr;
   double _W_m; float _in_W_m;
   double _H_nu_dr; float _in_H_nu_dr;
   double _H_l_dr; float _in_H_l_dr;
   double _chi2; float _in_chi2;
   double _l_charge; float _in_l_charge;
   double _TTbar_chi2; float _in_TTbar_chi2;
   double _TTbar_topLep_m; float _in_TTbar_topLep_m;
   double _TTbar_tbLep_tWLep_Dr; float _in_TTbar_tbLep_tWLep_Dr;
   double _TTbar_tbHad_tWHad_Dr; float _in_TTbar_tbHad_tWHad_Dr;
   
 private:

};

#endif
