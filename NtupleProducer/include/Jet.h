#ifndef JET_H
#define JET_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "Base.h"

class Jet : public Base
{
 public:
   Jet();
   virtual ~Jet();

   static bool sortPtPredicate(Jet lhs, Jet rhs)
     {return (lhs.pt() > rhs.pt());};
   
   int ID()    {return _ID;};
   
   void sel();
   
   // kinematics
   float E()         {return _E;};
   float pt()        {return _pt;};
   float eta()       {return _eta;};
   float phi()       {return _phi;};
   float m()         {return _m;};

   float gen_E()         {return _gen_E;};
   float gen_pt()        {return _gen_pt;};
   float gen_eta()       {return _gen_eta;};
   float gen_phi()       {return _gen_phi;};
   float gen_m()         {return _gen_m;};
   int gen_status()      {return _gen_status;};
   int gen_id()          {return _gen_id;};
   
   TLorentzVector p4()  {return _p4;};
   
   int ntrk()         {return _ntrk;};
   
   float CSV()         {return _CSV;};
   float CSVv2()         {return _CSVv2;};
   
   bool isTight()         {return _isTight;};
   
   bool idLoose()         {return _pass_ID_loose;};
   bool idMedium()         {return _pass_ID_medium;};
   bool idTight()         {return _pass_ID_tight;};
   
   bool passPUID()         {return _pass_pujetId;};
   
   void read();
   void init();
	
 protected:

   int _ID;
	
   float _E;
   float _pt;
   float _eta;
   float _phi;
   float _m;

   float _gen_E;
   float _gen_pt;
   float _gen_eta;
   float _gen_phi;
   float _gen_m;
   int _gen_status;
   int _gen_id;
   
   TLorentzVector _p4;
   
   int _ntrk;
   
   float _CSV;
   float _CSVv2;

   bool _isTight;
   
   bool _pass_ID_loose;
   bool _pass_ID_medium;
   bool _pass_ID_tight;

   bool _pass_pujetId;
   
   ClassDef(Jet,1)
};

#endif
