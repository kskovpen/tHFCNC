#include "include/NtupleProducer.h"

ClassImp(Event)
    
Event::Event()
{
}

Event::~Event()
{
}

void Event::read(float xsec,float noe,int dataStream,bool issig)
{
   _id   = ntP->ev_id;
   _run  = ntP->ev_run;
   _lumi = ntP->ev_lumi;
   _rho  = ntP->ev_rho;

   _pv_chi2 = ntP->pv_chi2;
   _pv_ndof = ntP->pv_ndof;
   _pv_rho = ntP->pv_rho;
   _pv_isFake = ntP->pv_isFake;
   
   _metpt = ntP->met_pt;
   _metphi = ntP->met_phi;
   _metsumet = ntP->met_sumet;
   
   _mc_weight  = ntP->mc_weight;
   
   _xsec = xsec;
   _noe = noe;
   _isData = _isdata;
   _isSignal = issig;
   
   _isTrigMuon = 0;
   _isTrigElec = 0;

   int nTrig = ntP->trigger_name->size();
   for(int it=0;it<nTrig;it++)
     {
	if( ntP->trigger_name->at(it).find("HLT_IsoMu22_v") != std::string::npos ||
	    ntP->trigger_name->at(it).find("HLT_IsoTkMu22_v") != std::string::npos )
	  {	     
	     if( (_isData && dataStream == 1) || !_isData )
	       {		  
		  if( ntP->trigger_pass->at(it) ) _isTrigMuon = 1;
	       }	     
	  }	
	
	if( ntP->trigger_name->at(it).find("HLT_Ele35_WPLoose_Gsf_v") != std::string::npos ||
	    ntP->trigger_name->at(it).find("HLT_Ele27_WPTight_Gsf_v") != std::string::npos )
	  {	     
	     if( (_isData && dataStream == 0) || !_isData )
	       {		  
		  if( ntP->trigger_pass->at(it) ) _isTrigElec = 1;
	       }	     
	  }	
     }
}

void Event::init()
{
   _id        = VDEF;
   _run       = VDEF;
   _lumi      = VDEF;
   _rho       = VDEF;

   _metpt        = VDEF;
   _metphi       = VDEF;
   _metsumet      = VDEF;

   _pv_chi2 = VDEF;
   _pv_ndof = VDEF;
   _pv_rho = VDEF;
   _pv_isFake = VDEF;
   
   _xsec = VDEF;
   _noe = VDEF;   
   _isData = 0;
   _isSignal = 0;
   
   _isTrigMuon = 0;
   _isTrigElec = 0;
}
