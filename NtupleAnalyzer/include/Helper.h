#ifndef HELPER_H
#define HELPER_H

#include "Analyzer.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/type_traits.hpp>

class Helper
{
   
 public:
   
   Helper();
   virtual ~Helper();
   
   std::vector<Lepton> filterPt(double Pt1, double Pt2, double Pt3,
				std::vector<Electron>* ntElectron,
				std::vector<Muon>* ntMuon);
   
   float getWmassBW(TRandom3 *rnd,float mWmean,float GammaW,float nSigma);
   float BW(float mW,float mWmean,float GammaW);
   bool getNuMom(float Wmass,float px_l,float py_l,float pz_l,float E_l,
		 float px_nu,float py_nu,float &pz_nu1,float &pz_nu2);
	
 protected:

};

#endif
