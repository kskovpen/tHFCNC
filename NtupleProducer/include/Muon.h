#ifndef MUON_H
#define MUON_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "Base.h"

class Muon : public Base
{
 public:
   Muon();
   virtual ~Muon();

   static bool sortPtPredicate(Muon lhs, Muon rhs)
     {return (lhs.pt() > rhs.pt());};
   
   int ID()    {return _ID;};
   
   void sel();
   
   // kinematics
   float E()         {return _E;};
   float pt()        {return _pt;};
   float eta()       {return _eta;};
   float phi()       {return _phi;};
   float m()         {return _m;};
   float dxy()         {return _dxy;};
   float dz()         {return _dz;};

   TLorentzVector p4()  {return _p4;};
   
   float iso()         {return _iso;};
   
   int charge()         {return _charge;};
   int id()         {return _id;};

   bool idLoose() {return _idLoose;};
   bool idTight() {return _idTight;};
   
   void read();
   void init();
	
 protected:

   int _ID;
   
   float _E;
   float _pt;
   float _eta;
   float _phi;
   float _m;
   float _dxy;
   float _dz;
   float _iso;

   TLorentzVector _p4;
   
   int _charge;
   int _id;
   
   bool _idLoose;
   bool _idTight;
     
   ClassDef(Muon,1)
};

#endif
