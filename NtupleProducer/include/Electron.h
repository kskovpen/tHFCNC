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
   bool isLoose()         {return _isLoose;};
   bool isTight()         {return _isTight;};
   
   int charge()         {return _charge;};
   int id()         {return _id;};
   
   bool isLooseCBId()     {return _isLooseCBId;};
   bool isMediumCBId()     {return _isMediumCBId;};
   bool isTightCBId()     {return _isTightCBId;};
   
   float relIso()     {return _relIso;};
   
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
   bool _isLoose;
   bool _isTight;
   
   int _charge;
   int _id;
   
   bool _isLooseCBId;
   bool _isMediumCBId;
   bool _isTightCBId;
   
   float _relIso;
   
   ClassDef(Electron,1)
};

#endif
