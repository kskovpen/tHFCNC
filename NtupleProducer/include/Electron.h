#ifndef ELECTRON_H
#define ELECTRON_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "Base.h"

class Electron : public Base
{
 public:
   Electron();
   virtual ~Electron();

   static bool sortPtPredicate(Electron lhs, Electron rhs)
     {return (lhs.pt() > rhs.pt());};
   
   int ID()    {return _ID;};
   
   void sel();
   
   // kinematics
   float E()         {return _E;};
   float pt()        {return _pt;};
   float eta()       {return _eta;};
   float scleta()       {return _scleta;};
   float phi()       {return _phi;};
   float m()         {return _m;};

   TLorentzVector p4()  {return _p4;};
   
   float dxy()         {return _dxy;};
   float dz()         {return _dz;};
   float iso()         {return _iso;};
   bool isLoose()         {return _isLoose;};
   bool isTight()         {return _isTight;};
   
   int charge()         {return _charge;};
   int id()         {return _id;};

   bool pass_ID_veto() {return _pass_ID_veto;};
   bool pass_ID_loose() {return _pass_ID_loose;};
   bool pass_ID_medium() {return _pass_ID_medium;};
   bool pass_ID_tight() {return _pass_ID_tight;};
   
   void read();
   void init();
	
 protected:

   int _ID;
   
   float _E;
   float _pt;
   float _eta;
   float _scleta;
   float _phi;
   float _m;

   TLorentzVector _p4;
   
   float _dxy;
   float _dz;
   float _iso;
   bool _isLoose;
   bool _isTight;
   
   int _charge;
   int _id;

   bool _pass_ID_veto;
   bool _pass_ID_loose;
   bool _pass_ID_medium;
   bool _pass_ID_tight;
   
   ClassDef(Electron,1)
};

#endif
