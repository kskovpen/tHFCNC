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

   int genTTX_id()         {return _genTTX_id;};
   
   float rho()         {return _rho;};
   
   float metpt()         {return _metpt;};
   float metphi()         {return _metphi;};
   float metsumet()         {return _metsumet;};
   
   int nvertex()         {return _nvertex;};
   
   float mc_weight()         {return _mc_weight;};

   float xsec() {return _xsec;};
   float noe() {return _noe;};
   
   bool isData() {return _isData;};
   bool isSignal() {return _isSignal;};
   bool isTTBar() {return _isTTBar;};
   
   bool isTrigMuon() {return _isTrigMuon;};
   bool isTrigElec() {return _isTrigElec;};
   
   float wpu() {return _wpu;};
   float wpuUp() {return _wpuUp;};
   float wpuDown() {return _wpuDown;};
   
   int npv() {return _npv;};
   
   int pvIsFake() {return _pv_isFake;};
   float pvNDOF() {return _pv_ndof;};
   float pvZ() {return _pv_z;};
   float pvRho() {return _pv_rho;};
   
   void read(float xsec,float noe,int dataStream,bool issig,bool isttbar);
   void init();
	
 protected:

   double getPUWeight(int nPU,std::string opt);
   
   int _id;
   int _run;
   int _lumi;

   int _genTTX_id;
   
   float _rho;

   float _metpt;
   float _metphi;
   float _metsumet;
   
   int _nvertex;

   float _mc_weight;

   float _xsec;
   float _noe;
   
   bool _isData;
   bool _isSignal;
   bool _isTTBar;
   
   bool _isTrigMuon;
   bool _isTrigElec;

   float _pv_chi2;
   float _pv_ndof;
   int _pv_isFake;
   
   float _pv_z;
   float _pv_rho;
   
   float _wpu;
   float _wpuUp;
   float _wpuDown;
   
   int _npv;
   
   ClassDef(Event,1)
};

#endif
