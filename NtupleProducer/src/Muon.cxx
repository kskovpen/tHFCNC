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
   if( CHECK(ntP->mu_innerTrack_PV_dxy) )   _dxy   = ntP->mu_innerTrack_PV_dxy->at(idx);
   if( CHECK(ntP->mu_innerTrack_PV_dz) )    _dz   = ntP->mu_innerTrack_PV_dz->at(idx);
   
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
   _relIso    = -666;
   
   _charge        = 0;
   _id        = 0;
   
   _isLoose = 0;
   _isTight = 0;
   
   _isTightID = 0;
}

void Muon::sel()
{
   _isLooseID = ntP->mu_isLooseMuon->at(idx);
   _isTightID = ntP->mu_isTightMuon->at(idx);
   
   bool passPtLoose = (_pt > 10.);
   bool passPtTight = (_pt > 30.);
   bool passEta = (fabs(_eta) < 2.4);
   bool passDxy = (fabs(_dxy) < 0.05);
   bool passDz = (fabs(_dz) < 0.1);

   // https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2#Muon_Isolation
   // http://www.sciencedirect.com/science/article/pii/S0370269312005564#
   _relIso = (ntP->mu_pfIso03_sumChargedHadronPt->at(idx) +
	      std::max(ntP->mu_pfIso03_sumNeutralHadronEt->at(idx) +
		       ntP->mu_pfIso03_sumPhotonEt->at(idx) - 0.5*ntP->mu_pfIso03_sumPUPt->at(idx),0.0))/_pt;
   
   bool passRelIsoLoose = (_relIso < 0.25);
   bool passRelIsoTight = (_relIso < 0.15);
     
   _isLoose = (
	       passPtLoose &&
	       passEta &&
	       passDxy &&
	       passDz &&
	       passRelIsoLoose &&
	       _isLooseID
	      );

   _isTight = (
	       _isLoose &&
	       passPtTight &&
	       _isTightID &&
	       passRelIsoTight
	      );
   
   for(int id=0;id<evdebug->size();id++)
     {	
	if( nt->NtEvent->at(0).id() == evdebug->at(id) )
	  {
	     std::cout << "Muon #" << _ID << std::endl;
	     std::cout << "   pt=" << _pt << " eta=" << _eta << " phi=" << _phi << std::endl;
	  }	
     }
}
