#include "../include/Helper.h"

Helper::Helper()
{
}

Helper::~Helper()
{
}

std::vector<Lepton> Helper::filterPt(double Pt1, double Pt2, double Pt3,
				     std::vector<Electron>* ntElectron,
				     std::vector<Muon>* ntMuon)
{
   std::vector<std::pair<int,double> > el_pt;
   std::vector<std::pair<int,double> > mu_pt;
   std::vector<std::pair<int,double> > ll_pt;
   
   // descending
   std::sort(ntElectron->begin(),ntElectron->end(),Electron::sortPtPredicate);
   std::sort(ntMuon->begin(),ntMuon->end(),Muon::sortPtPredicate);
   
   for(int i=0;i<ntElectron->size();i++)
     {	
	el_pt.push_back(std::make_pair(i,ntElectron->at(i).pt()));
     }   
   for(int i=0;i<ntMuon->size();i++)
     {
	mu_pt.push_back(std::make_pair(i+1000,ntMuon->at(i).pt()));
     }
   
   ll_pt.reserve( el_pt.size() + mu_pt.size() );
   ll_pt.insert( ll_pt.end(), el_pt.begin(), el_pt.end() );
   ll_pt.insert( ll_pt.end(), mu_pt.begin(), mu_pt.end() );

   // descending
   std::sort( ll_pt.begin(), ll_pt.end(),
	      boost::bind(&std::pair<int, double>::second, _1) >
	      boost::bind(&std::pair<int, double>::second, _2));

   bool found_pt1 = false;
   bool found_pt2 = false;

   std::vector<int> id_remove;

   for(int i=0;i<ll_pt.size();i++)
     {
	if( found_pt1 && found_pt2 )
	  {
	     if( ll_pt.at(i).second < Pt3 )
	       id_remove.push_back(i);
	  }	

	if( ! found_pt2 )
	  {	     
	     if( ll_pt.at(i).second > Pt1 )
	       found_pt1 = true;

	     if( (found_pt1 && ll_pt.at(i).second < Pt2) || !found_pt1 )
	       id_remove.push_back(i);
	     else
	       found_pt2 = true;
	  }	
     }   

   for(int j=id_remove.size()-1;j>=0;j--)
     {
	int index = ll_pt.at(id_remove.at(j)).first;
	
	bool is_electron = true;
	     
	if( index >= 1000 ) 
	  {
	     index = index - 1000;
	     is_electron = false;
	  }	     	

	ll_pt.erase(ll_pt.begin() + id_remove.at(j));
	
	if( is_electron )
	  ntElectron->erase(ntElectron->begin() + index);
	else
	  ntMuon->erase(ntMuon->begin() + index);
     }   

   // descending
   std::sort( ll_pt.begin(), ll_pt.end(),
	      boost::bind(&std::pair<int, double>::second, _1) >
	      boost::bind(&std::pair<int, double>::second, _2));

   std::vector<Lepton> res;
   res.clear();
   
   for(int il=0;il<ll_pt.size();il++)
     {
	int isElectron = -1;
	
	int lidx = ll_pt.at(il).first;
	
	if( lidx < 1000 ) isElectron = 1;
	if( lidx >= 1000 ) isElectron = 0;

	int idx = (lidx < 1000) ? lidx : lidx - 1000;
	
	Lepton l;
	if( isElectron ) l.setLepton(&ntElectron->at(idx),idx,1);
	else l.setLepton(&ntMuon->at(idx),idx,0);
	res.push_back(l);
     }

   return res;
}

float Helper::getWmassBW(TRandom3 *rnd,float mWmean,float GammaW,float nSigma)
{
   float mW = 0.;
   
   float max = BW(mWmean,mWmean,GammaW);
   
   while(1)
     {
	float r1 = rnd->Rndm();
	float r2 = rnd->Rndm();

	mW = mWmean - nSigma*GammaW + 2*nSigma*GammaW*r1;
	if( BW(mW,mWmean,GammaW) > max*r2 ) break;
     }
   
   return mW;      
}

float Helper::BW(float mW,float mWmean,float GammaW)
{
   float f = mW*mW/sqrt(pow(mW*mW-mWmean*mWmean,2)+mW*mW*GammaW*GammaW);
   
   return f;
}

bool Helper::getNuMom(float Wmass,float px_l,float py_l,float pz_l,float E_l,
		      float px_nu,float py_nu,float &pz_nu1,float &pz_nu2)
{
   bool hasSolution = 0.;
   
   float a = sqrt(px_l*px_l+py_l*py_l);
   float b = pz_l;
   float d = sqrt(px_nu*px_nu+py_nu*py_nu);
   float f = E_l;
   
   float c = Wmass*Wmass/2+px_l*px_nu+py_l*py_nu;
   
   float racine = c*c*b*b-a*a*(d*d*f*f-c*c);
   
   if(racine >= 0) 
     {
	hasSolution = 1;
	pz_nu1 = (c*b+sqrt(racine))/a/a;
	pz_nu2 = (c*b-sqrt(racine))/a/a;
     }   
   
   return hasSolution;
}
