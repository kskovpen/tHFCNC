#ifndef EVENT_H
#define EVENT_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "Base.h"

class Event : public Base
{
 public:
   Event();
   virtual ~Event();
   
   int id()         {return _id;};
   int run()         {return _run;};
   int lumi()         {return _lumi;};

   float rho()         {return _rho;};
   
   float metpt()         {return _metpt;};
   float metphi()         {return _metphi;};
   float metsumet()         {return _metsumet;};
   
   float mc_weight()         {return _mc_weight;};

   float xsec() {return _xsec;};
   float noe() {return _noe;};
   
   bool isData() {return _isData;};
   bool isSignal() {return _isSignal;};
   
   bool isTrigMuon() {return _isTrigMuon;};
   bool isTrigElec() {return _isTrigElec;};
   
   void read(float xsec,float noe,int dataStream,bool issig);
   void init();
	
 protected:

   int _id;
   int _run;
   int _lumi;
   
   float _rho;

   float _metpt;
   float _metphi;
   float _metsumet;

   float _mc_weight;

   float _xsec;
   float _noe;
   
   bool _isData;
   bool _isSignal;
   
   bool _isTrigMuon;
   bool _isTrigElec;

   float _pv_chi2;
   int _pv_ndof;
   float _pv_rho;
   int _pv_isFake;
   
   ClassDef(Event,1)
};

#endif
