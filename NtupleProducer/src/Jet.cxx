#include "include/NtupleProducer.h"

ClassImp(Jet)
    
Jet::Jet()
{
}

Jet::~Jet()
{
}

void Jet::read()
{
   _ID = idx;
   
   if( CHECK(ntP->jet_E) )                _E   = ntP->jet_E->at(idx);
   if( CHECK(ntP->jet_pt) )               _pt  = ntP->jet_pt->at(idx);
   if( CHECK(ntP->jet_eta) )              _eta = ntP->jet_eta->at(idx);   
   if( CHECK(ntP->jet_phi) )              _phi = ntP->jet_phi->at(idx);   
   if( CHECK(ntP->jet_m) )                _m   = ntP->jet_m->at(idx);

   if( CHECK(ntP->jet_gen_E) )                _gen_E   = ntP->jet_gen_E->at(idx);
   if( CHECK(ntP->jet_gen_pt) )               _gen_pt  = ntP->jet_gen_pt->at(idx);
   if( CHECK(ntP->jet_gen_eta) )              _gen_eta = ntP->jet_gen_eta->at(idx);   
   if( CHECK(ntP->jet_gen_phi) )              _gen_phi = ntP->jet_gen_phi->at(idx);   
   if( CHECK(ntP->jet_gen_m) )                _gen_m   = ntP->jet_gen_m->at(idx);
   if( CHECK(ntP->jet_gen_status) )                _gen_status   = ntP->jet_gen_status->at(idx);
   if( CHECK(ntP->jet_gen_id) )                _gen_id   = ntP->jet_gen_id->at(idx);
   
   if( CHECK(ntP->jet_ntrk) )             _ntrk   = ntP->jet_ntrk->at(idx);
   
   if( CHECK(ntP->jet_CSV) )                _CSV   = ntP->jet_CSV->at(idx);
   if( CHECK(ntP->jet_CSVv2) )                _CSVv2   = ntP->jet_CSVv2->at(idx);
   
   if(_pt > 0.) _p4.SetPtEtaPhiE(_pt,_eta,_phi,_E);
}

void Jet::init()
{
   _E        = -666;
   _pt       = -666;
   _eta      = -666;
   _phi      = -666;
   _m        = -666;

   _gen_E        = -666;
   _gen_pt       = -666;
   _gen_eta      = -666;
   _gen_phi      = -666;
   _gen_m        = -666;
   _gen_status        = -666;
   _gen_id        = -666;
   
   _ntrk        = -666;
   
   _CSV        = -666.;
   _CSVv2        = -666.;

   _isTight   = 0;
   
   _pass_ID_loose   = 0;
   _pass_ID_medium   = 0;
   _pass_ID_tight   = 0;
   
   _pass_pujetId = 0;
}

void Jet::sel()
{   
   bool pass_pt = (_pt > 20.);
   bool pass_eta = (fabs(_eta) < 5.2);

   TLorentzVector vjet;
   vjet.SetPtEtaPhiE(_pt,_eta,_phi,_E);
   
   float energy = (vjet*ntP->jet_jecFactorUncorrected->at(idx)).E();
   int numberOfConstituents = ntP->jet_chargedMultiplicity->at(idx) + ntP->jet_neutralMultiplicity->at(idx);
   float phf = ntP->jet_neutralEmEnergy->at(idx)/energy;
   float nhf = ntP->jet_neutralHadronEnergy->at(idx)/energy;
   float chf = ntP->jet_chargedHadronEnergy->at(idx)/energy;
   float muf = ntP->jet_muonEnergy->at(idx)/energy;
   float elf = ntP->jet_chargedEmEnergy->at(idx)/energy;
   float chm = ntP->jet_chargedHadronMultiplicity->at(idx);
   
   _pass_ID_loose = (nhf < 0.99 && phf < 0.99 && numberOfConstituents > 1 &&
		     muf < 0.8 && elf < 0.99);
   if( fabs(_eta) < 2.4 ) 
     _pass_ID_loose = _pass_ID_loose && (chf > 0 && chm > 0);
   
   _pass_ID_medium = (nhf < 0.95 && phf < 0.95 && numberOfConstituents > 1 &&
		      muf < 0.8 && elf < 0.99);
   if( fabs(_eta) < 2.4 ) 
     _pass_ID_medium = _pass_ID_medium && (chf > 0 && chm > 0);
   
   _pass_ID_tight = (nhf < 0.90 && phf < 0.90 && numberOfConstituents > 1 &&
		     muf < 0.8 && elf < 0.99);
   if( fabs(_eta) < 2.4 ) 
     _pass_ID_tight = _pass_ID_tight && (chf > 0 && chm > 0);
   
   bool pass_pujetId = 0;
   
   float pileupJetId = ntP->jet_pileupJetId->at(idx);
   
   if( fabs(_eta) >= 0 && fabs(_eta) < 2.5 )
     if( pileupJetId > -0.63 ) pass_pujetId = 1;
   else if( fabs(_eta) >= 2.5 && fabs(_eta) < 2.75 )
     if( pileupJetId > -0.60 ) pass_pujetId = 1;
   else if( fabs(_eta) >= 2.75 && fabs(_eta) < 3.0 )
     if( pileupJetId > -0.55 ) pass_pujetId = 1;
   else if( fabs(_eta) >= 3.0 && fabs(_eta) < 5.2 )
     if( pileupJetId > -0.45 ) pass_pujetId = 1;
   
   _pass_pujetId = pass_pujetId;
   
   bool pass_muOverlap = 1;
   int nMuon = nt->NtMuon->size();
   for(int im=0;im<nMuon;im++)
     {
	float dr = GetDeltaR(_eta,_phi,nt->NtMuon->at(im).eta(),nt->NtMuon->at(im).phi());
	if( dr < 0.4 && nt->NtMuon->at(im).pt() > 10. ) pass_muOverlap = 0;
     }  

   bool pass_elOverlap = 1;
   int nElectron = nt->NtElectron->size();
   for(int ie=0;ie<nElectron;ie++)
     {
	float dr = GetDeltaR(_eta,_phi,nt->NtElectron->at(ie).eta(),nt->NtElectron->at(ie).phi());
	if( dr < 0.4 && nt->NtElectron->at(ie).pt() > 10. ) pass_elOverlap = 0;
     }  
   
   _isTight = (
//	       pass_pt &&
//	       pass_eta &&
////	       pass_pujetId &&
	       pass_muOverlap &&
	       pass_elOverlap
	      );

   for(int id=0;id<evdebug->size();id++)
     {	
	if( nt->NtEvent->at(0).id() == evdebug->at(id) )
	  {
	     if( _isTight && _pt > 10. &&
		 fabs(_eta) < 5.2 )
	       {		  
		  std::cout << "Jet #" << _ID << std::endl;
		  std::cout << "   pt=" << _pt << " eta=" << _eta << " phi=" << _phi << std::endl;
		  std::cout << "   pileupJetId=" << pileupJetId << std::endl;
		  std::cout << "   isTight=" << _isTight << std::endl;
		  std::cout << "   pass_pujetId=" << pass_pujetId << std::endl;
		  std::cout << "   pass_elOverlap=" << pass_elOverlap << std::endl;
		  std::cout << "   pass_muOverlap=" << pass_muOverlap << std::endl;
	       }	     
	  }	
     }
}
