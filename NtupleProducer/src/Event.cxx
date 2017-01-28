#include "include/NtupleProducer.h"

ClassImp(Event)
    
Event::Event()
{
}

Event::~Event()
{
}

void Event::read(float xsec,float noe,int dataStream,bool issig,bool isttbar)
{
   _id   = ntP->ev_id;
   _run  = ntP->ev_run;
   _lumi = ntP->ev_lumi;
   _rho  = ntP->ev_rho;

   _pv_chi2 = ntP->pv_chi2;
   _pv_ndof = ntP->pv_ndof;
   _pv_rho = ntP->pv_rho;
   _pv_isFake = ntP->pv_isFake;
   
   _pv_z = ntP->pv_z;

   _nvertex = ntP->nvertex;
   
   _metpt = ntP->met_pt;
   _metphi = ntP->met_phi;
   _metsumet = ntP->met_sumet;
   
   _mc_weight  = ntP->mc_weight;
   
   _genTTX_id = ntP->genTTX_id;
   
   _xsec = xsec;
   _noe = noe;
   _isData = _isdata;
   _isSignal = issig;
   _isTTBar = isttbar;
   
   _isTrigMuon = 0;
   _isTrigElec = 0;

   int nTrig = ntP->trigger_name->size();
   for(int it=0;it<nTrig;it++)
     {
	if( ntP->trigger_name->at(it).find("HLT_IsoMu22_v") != std::string::npos ||
	    ntP->trigger_name->at(it).find("HLT_IsoTkMu22_v") != std::string::npos )
//	if( ntP->trigger_name->at(it).find("HLT_IsoMu24_v") != std::string::npos ||
//	    ntP->trigger_name->at(it).find("HLT_IsoTkMu24_v") != std::string::npos )
	  {	     
	     if( (_isData && dataStream == 1) || !_isData )
	       {		  
		  if( ntP->trigger_pass->at(it) ) _isTrigMuon = 1;
	       }	     
	  }	

//	if( ntP->trigger_name->at(it).find("HLT_Ele35_WPLoose_Gsf_v") != std::string::npos ||
//	    ntP->trigger_name->at(it).find("HLT_Ele27_WPTight_Gsf_v") != std::string::npos )
	if( ntP->trigger_name->at(it).find("HLT_Ele32_eta2p1_WPTight_Gsf_v") != std::string::npos )
	  {	     
	     if( (_isData && dataStream == 0) || !_isData )
	       {		  
		  if( ntP->trigger_pass->at(it) ) _isTrigElec = 1;
	       }	     
	  }	
     }
   
   if( !_isData )
     {	
	int nPU = ntP->mc_pu_trueNumInt;
   
	_wpu = getPUWeight(nPU,"");
	_wpuUp = getPUWeight(nPU,"up");
	_wpuDown = getPUWeight(nPU,"down");
     }   
   
   _npv = ntP->nvertex;
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
   
   _pv_z = VDEF;
   
   _nvertex = 0;
   
   _xsec = VDEF;
   _noe = VDEF;   
   _isData = 0;
   _isSignal = 0;
   _isTTBar = 0;
   
   _isTrigMuon = 0;
   _isTrigElec = 0;
   
   _wpu = 1.;
   _wpuUp = 1.;
   _wpuDown = 1.;
   
   _npv = 0;
}

double Event::getPUWeight(int nPU,std::string opt)
{   
   double w = 1.;
   
   if( nPU >= 50 )
     {	
	w = _weights[50];
	if( opt == "up" ) w = _weightsUp[50];
	if( opt == "down" ) w = _weightsDown[50];
     }   
   else
     {	
	w = _weights[nPU];
	if( opt == "up" ) w = _weightsUp[nPU];
	if( opt == "down" ) w = _weightsDown[nPU];
     }      

   return w;
}
