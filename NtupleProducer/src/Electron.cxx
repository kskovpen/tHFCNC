#include "include/NtupleProducer.h"

ClassImp(Electron)
    
Electron::Electron()
{
}

Electron::~Electron()
{
}

void Electron::read()
{
   _ID = idx;
   
   _E   = ntP->el_E->at(idx);
   _pt  = ntP->el_pt->at(idx);
   _eta = ntP->el_eta->at(idx);
   _scleta = ntP->el_scleta->at(idx);
   _phi = ntP->el_phi->at(idx);
   _m   = ntP->el_m->at(idx);
   _dxy   = ntP->el_dxy->at(idx);
   _dz   = ntP->el_dz->at(idx);
   
   _charge   = ntP->el_charge->at(idx);
   _id   = ntP->el_id->at(idx);
   
   if(_pt > 0.) _p4.SetPtEtaPhiE(_pt,_eta,_phi,_E);
}

void Electron::init()
{
   _E        = -666;
   _pt       = -666;
   _eta      = -666;
   _phi      = -666;
   _m        = -666;
   _dxy        = -666;
   _dz        = -666;
   _iso        = -666;
   _isLoose   = 0;
   _isTight   = 0;
   
   _charge   = 0;
   _id   = 0;   

   _pass_ID_veto = 0;
   _pass_ID_loose = 0;
   _pass_ID_medium = 0;
   _pass_ID_tight = 0;
}

void Electron::sel()
{   
   bool pass_pt = (_pt > 7.);
   bool pass_eta = (fabs(_eta) < 2.5);
   bool pass_dxy = (fabs(_dxy) < 0.05);
   bool pass_dz = (fabs(_dz) < 0.1);

   bool pass_crack = !(abs(_scleta) > 1.4442 && abs(_scleta) < 1.5660);
   
   float see = ntP->el_see->at(idx);
   float dEtaIn = ntP->el_deltaEtaSuperClusterTrackAtVtx->at(idx);
   float dPhiIn = ntP->el_deltaPhiSuperClusterTrackAtVtx->at(idx);
   float hadronicOverEm = ntP->el_hadronicOverEm->at(idx);
   // Compute isolation with delta beta correction for PU, cone 0.3
   float absiso = ntP->el_pfIso_sumChargedHadronPt->at(idx)
     + std::max(0.0,ntP->el_pfIso_sumNeutralHadronEt->at(idx)+
		ntP->el_pfIso_sumPhotonEt->at(idx)-0.5*ntP->el_pfIso_sumPUPt->at(idx));
   float reliso = (_pt > 0.) ? absiso/_pt : 10E+10;
   float ooemoop = (1.0/ntP->el_ecalEnergy->at(idx)-ntP->el_eSuperClusterOverP->at(idx)/ntP->el_ecalEnergy->at(idx));
   int passConversionVeto = ntP->el_passConversionVeto->at(idx);
   int numberOfHits = ntP->el_numberOfHits->at(idx);
   
   if( fabs(_scleta) <= 1.479 )
     {
	// veto
	if( see < 0.011100 && fabs(dEtaIn) < 0.016315 &&
	    fabs(dPhiIn) < 0.252044 && hadronicOverEm < 0.345843 &&
	    reliso < 0.164369 && ooemoop < 0.248070 && fabs(_dxy) < 0.060279 &&
	    fabs(_dz) < 0.800538 && numberOfHits <= 2 &&
	    (passConversionVeto == 1)
	  )
	  _pass_ID_veto = 1;
	// loose
	if( see < 0.010557 && fabs(dEtaIn) < 0.012442 &&
	    fabs(dPhiIn) < 0.072624 && hadronicOverEm < 0.121476 &&
	    reliso < 0.120026 && ooemoop < 0.221803 && fabs(_dxy) < 0.022664 &&
	    fabs(_dz) < 0.173670 && numberOfHits <= 1 &&
	    (passConversionVeto == 1)
	  )
	  _pass_ID_loose = 1;
	// medium
	if( see < 0.010399 && fabs(dEtaIn) < 0.007641 &&
	    fabs(dPhiIn) < 0.032643 && hadronicOverEm < 0.060662 &&
	    reliso < 0.097213 && ooemoop < 0.153897 && fabs(_dxy) < 0.011811 &&
	    fabs(_dz) < 0.070775 && numberOfHits <= 1 &&
	    (passConversionVeto == 1)
	  )
	  _pass_ID_medium = 1;
	// tight
	if( see < 0.010181 && fabs(dEtaIn) < 0.006574 &&
	    fabs(dPhiIn) < 0.022868 && hadronicOverEm < 0.037553 &&
	    reliso < 0.074355 && ooemoop < 0.131191 && fabs(_dxy) < 0.009924 &&
	    fabs(_dz) < 0.015310 && numberOfHits <= 1 &&
	    (passConversionVeto == 1)
	  )
	  _pass_ID_tight = 1;
     }   
   else if( fabs(_scleta) > 1.479 && fabs(_scleta) < 2.5 )
     {
	// veto
	if( see < 0.033987 && fabs(dEtaIn) < 0.010671 &&
	    fabs(dPhiIn) < 0.245263 && hadronicOverEm < 0.134691 &&
	    reliso < 0.212604 && ooemoop < 0.157160 && fabs(_dxy) < 0.273097 &&
	    fabs(_dz) < 0.885860 && numberOfHits <= 3 &&
	    (passConversionVeto == 1)
	  )
	  _pass_ID_veto = 1;
	// loose
	if( see < 0.032602 && fabs(dEtaIn) < 0.010654 &&
	    fabs(dPhiIn) < 0.145129 && hadronicOverEm < 0.131862 &&
	    reliso < 0.162914 && ooemoop < 0.142283 && fabs(_dxy) < 0.097358 &&
	    fabs(_dz) < 0.198444 && numberOfHits <= 1 &&
	    (passConversionVeto == 1)
	  )
	  _pass_ID_loose = 1;
	// medium
	if( see < 0.029524 && fabs(dEtaIn) < 0.009285 &&
	    fabs(dPhiIn) < 0.042447 && hadronicOverEm < 0.104263 &&
	    reliso < 0.116708 && ooemoop < 0.137468 && fabs(_dxy) < 0.051682 &&
	    fabs(_dz) < 0.180720 && numberOfHits <= 1 &&
	    (passConversionVeto == 1)
	  )
	  _pass_ID_medium = 1;
	// tight
	if( see < 0.028766 && fabs(dEtaIn) < 0.005681 &&
	    fabs(dPhiIn) < 0.032046 && hadronicOverEm < 0.081902 &&
	    reliso < 0.090185 && ooemoop < 0.106055 && fabs(_dxy) < 0.027261 &&
	    fabs(_dz) < 0.147154 && numberOfHits <= 1 &&
	    (passConversionVeto == 1)
	  )
	  _pass_ID_tight = 1;
     }   

   // this is for 03
   _iso = (ntP->el_pfIso_sumChargedHadronPt->at(idx)+
	   std::max(ntP->el_pfIso_sumNeutralHadronEt->at(idx)+ntP->el_pfIso_sumPhotonEt->at(idx)-
		    0.5*ntP->el_pfIso_sumPUPt->at(idx),0.0))/_pt;
   
   for(int id=0;id<evdebug->size();id++)
     {	
	if( nt->NtEvent->at(0).id() == evdebug->at(id) )
	  {
	     std::cout << "Electron #" << _ID << std::endl;
	     std::cout << "   pt=" << _pt << " eta=" << _eta << " phi=" << _phi << std::endl;
	  }
     }
}
