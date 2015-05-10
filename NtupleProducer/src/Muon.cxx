#include "include/NtupleProducer.h"

ClassImp(Muon)
    
Muon::Muon()
{
}

Muon::~Muon()
{
}

void Muon::read()
{
   _ID = idx;
   
   if( CHECK(ntP->mu_E) )                _E   = ntP->mu_E->at(idx);
   if( CHECK(ntP->mu_pt) )               _pt  = ntP->mu_pt->at(idx);
   if( CHECK(ntP->mu_eta) )              _eta = ntP->mu_eta->at(idx);   
   if( CHECK(ntP->mu_phi) )              _phi = ntP->mu_phi->at(idx);   
   if( CHECK(ntP->mu_m) )                _m   = ntP->mu_m->at(idx);
   if( CHECK(ntP->mu_innerTrack_dxy) )                _dxy   = ntP->mu_innerTrack_dxy->at(idx);
   if( CHECK(ntP->mu_innerTrack_dz) )                _dz   = ntP->mu_innerTrack_dz->at(idx);
   
   if( CHECK(ntP->mu_charge) )                _charge   = ntP->mu_charge->at(idx);
   if( CHECK(ntP->mu_id) )                _id   = ntP->mu_id->at(idx);
   
   if(_pt > 0.) _p4.SetPtEtaPhiE(_pt,_eta,_phi,_E);
}

void Muon::init()
{
   _E        = -666;
   _pt       = -666;
   _eta      = -666;
   _phi      = -666;
   _m        = -666;
   _dxy        = -666;
   _dz        = -666;
   _iso        = -666;
   
   _charge        = 0;
   _id        = 0;
   
   _idLoose = 0;
   _idTight = 0;
}

void Muon::sel()
{
   _idLoose = (ntP->mu_isPFMuon->at(idx) && 
	       (ntP->mu_isGlobalMuon->at(idx) ||
		   ntP->mu_isTrackerMuon->at(idx)));
   
   _idTight = (_idLoose && ntP->mu_isTightMuon->at(idx)
	      );
   
   bool pass_pt = (_pt > 5.);
   bool pass_eta = (fabs(_eta) < 2.4);
   bool pass_dxy = (fabs(_dxy) < 0.05);
   bool pass_dz = (fabs(_dz) < 0.1);

   _iso = (ntP->mu_pfIso04_sumChargedHadronPt->at(idx) +
	   std::max(ntP->mu_pfIso04_sumNeutralHadronEt->at(idx) +
		    ntP->mu_pfIso04_sumPhotonEt->at(idx) - 0.5*ntP->mu_pfIso04_sumPUPt->at(idx),0.0))/_pt;
     
   for(int id=0;id<evdebug->size();id++)
     {	
	if( nt->NtEvent->at(0).id() == evdebug->at(id) )
	  {
	     std::cout << "Muon #" << _ID << std::endl;
	     std::cout << "   pt=" << _pt << " eta=" << _eta << " phi=" << _phi << std::endl;
	  }	
     }
}
