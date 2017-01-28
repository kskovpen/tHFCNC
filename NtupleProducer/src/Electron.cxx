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
   _scleta = ntP->el_superCluster_eta->at(idx);
   _phi = ntP->el_phi->at(idx);
   _m   = ntP->el_m->at(idx);
   _dxy   = ntP->el_gsfTrack_PV_dxy->at(idx);
   _dz   = ntP->el_gsfTrack_PV_dz->at(idx);
   
   _charge   = ntP->el_charge->at(idx);
   _id   = ntP->el_id->at(idx);
   
   _isLooseCBId   = ntP->el_looseCBId->at(idx);
   _isMediumCBId   = ntP->el_mediumCBId->at(idx);
   _isTightCBId   = ntP->el_tightCBId->at(idx);
   
   if(_pt > 0.) _p4.SetPtEtaPhiE(_pt,_eta,_phi,_E);
}

void Electron::init()
{
   _E        = VDEF;
   _pt       = VDEF;
   _eta      = VDEF;
   _phi      = VDEF;
   _m        = VDEF;
   _dxy        = VDEF;
   _dz        = VDEF;
   
   _isLoose   = 0;
   _isTight   = 0;
      
   _charge   = 0;
   _id   = 0;
   
   _isLooseCBId = 0;
   _isMediumCBId = 0;
   _isTightCBId = 0;
   
   _relIso = 0;
   
   _wid = 1.;
   _widUp = 1.;
   _widDown = 1.;
}

void Electron::sel()
{   
   bool passPtLoose = (_pt > 10.);
   bool passPtTight = (_pt > 35.);
   bool passEtaLoose = (fabs(_eta) < 2.5);
   bool passEtaTight = (fabs(_eta) < 2.1);
//   bool passDxy = (fabs(_dxy) < 0.05);   
//   bool passDz = (fabs(_dz) < 0.1);   
   bool passCrack = !(abs(_scleta) > 1.4442 && abs(_scleta) < 1.5660);   
   bool passConversionVeto = ntP->el_passConversionVeto->at(idx);

   // https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPFBasedIsolationRun2#Pile_up_corrections
   
   float rho = ntP->ev_rho;
   float eA = effectiveAreas_->getEffectiveArea(fabs(_scleta));
   
   _relIso = (ntP->el_pfIso_sumChargedHadronPt->at(idx)+
	      std::max(ntP->el_pfIso_sumNeutralHadronEt->at(idx)+ntP->el_pfIso_sumPhotonEt->at(idx)-
		       eA*ntP->ev_rho,0.0f))/_pt;
   
   bool passRelIsoLoose = (_relIso < 0.25);
   bool passRelIsoTight = (_relIso < 0.15);
   
   if( !_isdata )
     {	
	std::pair<float,float> sf = getSF(_eta,_pt);
	_wid = sf.first;
	_widUp = sf.first+sf.second;
	_widDown = std::max(float(0.),float(sf.first-sf.second));
     }   
   
   _isLoose = (
	       passPtLoose &&
	       passEtaLoose &&
//	       passDxy &&
//	       passDz &&
//	       passCrack &&
//	       passConversionVeto &&
//	       passRelIsoLoose &&
	       _isLooseCBId
	      );

   _isTight = (
	       _isLoose &&
	       passEtaTight &&
	       passPtTight &&
	       _isMediumCBId
//	       passRelIsoTight
	      );
   
   for(int id=0;id<evdebug->size();id++)
     {	
	if( nt->NtEvent->at(0).id() == evdebug->at(id) )
	  {
	     std::cout << "Electron #" << _ID << std::endl;
	     std::cout << "   pt=" << _pt << " eta=" << _eta << " phi=" << _phi << std::endl;
	  }
     }
}

std::pair<float,float> Electron::getSF(float eta,float pt)
{
   std::pair<float,float> w;
   
   float v = 1.;
   float err = 0.;
   
   if( fabs(eta) > 2.5 ) return std::make_pair(v,err);
   
   int nbinsX = _hegammaID->GetXaxis()->GetNbins();
   int nbinsY = _hegammaID->GetYaxis()->GetNbins();

   int ibinX = _hegammaID->GetXaxis()->FindBin(eta);
   
   if( pt < 200 )
     {	
	int ibinY = _hegammaID->GetYaxis()->FindBin(pt);
	
	v = _hegammaID->GetBinContent(ibinX,ibinY);
	err = _hegammaID->GetBinError(ibinX,ibinY);
     }
   else
     {
	v = _hegammaID->GetBinContent(ibinX,nbinsY);
	err = _hegammaID->GetBinError(ibinX,nbinsY);
     }  
   
   w = std::make_pair(v,err);
   
   return w;
}
