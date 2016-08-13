#ifndef TRUTH_H
#define TRUTH_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "Base.h"

class Truth : public Base
{
 public:
   Truth();
   virtual ~Truth();

   int mc_truth_n()         {return _mc_truth_n;};
   std::vector<int> mc_truth_id()         {return _mc_truth_id;};
   std::vector<int> mc_truth_label()         {return _mc_truth_label;};
   std::vector<float> mc_truth_pt()         {return _mc_truth_pt;};
   std::vector<float> mc_truth_eta()         {return _mc_truth_eta;};
   std::vector<float> mc_truth_phi()         {return _mc_truth_phi;};
   std::vector<float> mc_truth_E()         {return _mc_truth_E;};
   
   void read();
   void init();
	
 protected:

   int _mc_truth_n;
   std::vector<int> _mc_truth_id;
   std::vector<int> _mc_truth_label;
   std::vector<float> _mc_truth_pt;
   std::vector<float> _mc_truth_eta;
   std::vector<float> _mc_truth_phi;
   std::vector<float> _mc_truth_E;
   
   int getUnique(int p);

   ClassDef(Truth,1)
};

#endif
