#include "TROOT.h"
#include "TFile.h"
#include "TH2.h"
#include "Riostream.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TRandom.h"
#include "TParameter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <math.h>

#include "mclimit_csm.h"

int main()
{  
   const int nf = 2;

   gRandom->SetSeed(666);

   TFile *f_input = new TFile("limitInput.root");

   TH1 *h_channel1_data = (TH1*)f_input->Get("h_channel1_data");
   TH1 *h_channel1_signal = (TH1*)f_input->Get("h_channel1_signal");
   TH1 *h_channel1_signal_sys_jesUp = (TH1*)f_input->Get("h_channel1_signal_sys_jesUp");
   TH1 *h_channel1_signal_sys_jesDown = (TH1*)f_input->Get("h_channel1_signal_sys_jesDown");
   TH1 *h_channel1_background = (TH1*)f_input->Get("h_channel1_background");
   TH1 *h_channel1_background_sys_jesUp = (TH1*)f_input->Get("h_channel1_background_sys_jesUp");
   TH1 *h_channel1_background_sys_jesDown = (TH1*)f_input->Get("h_channel1_background_sys_jesDown");
   TH1 *h_channel1_background2 = (TH1*)f_input->Get("h_channel2_background");
   TH1 *h_channel1_background2_sys_jesUp = (TH1*)f_input->Get("h_channel2_background_sys_jesUp");
   TH1 *h_channel1_background2_sys_jesDown = (TH1*)f_input->Get("h_channel2_background_sys_jesDown");

   TH1 *h_channel2_data = (TH1*)f_input->Get("h_channel2_data");
   TH1 *h_channel2_signal = (TH1*)f_input->Get("h_channel2_signal");
   TH1 *h_channel2_signal_sys_jesUp = (TH1*)f_input->Get("h_channel2_signal_sys_jesUp");
   TH1 *h_channel2_signal_sys_jesDown = (TH1*)f_input->Get("h_channel2_signal_sys_jesDown");
   TH1 *h_channel2_background = (TH1*)f_input->Get("h_channel2_background");
   TH1 *h_channel2_background_sys_jesUp = (TH1*)f_input->Get("h_channel2_background_sys_jesUp");
   TH1 *h_channel2_background_sys_jesDown = (TH1*)f_input->Get("h_channel2_background_sys_jesDown");
   TH1 *h_channel2_background2 = (TH1*)f_input->Get("h_channel2_background2");
   TH1 *h_channel2_background2_sys_jesUp = (TH1*)f_input->Get("h_channel2_background2_sys_jesUp");
   TH1 *h_channel2_background2_sys_jesDown = (TH1*)f_input->Get("h_channel2_background2_sys_jesDown");

   const int nsys = 1;
   char *sysname[nsys];
   sysname[0] = "JES";

   TH1 *h_data[nf];
   TH1 *h_signal[nf];
   TH1 *h_signal_sys_jesUp[nf];
   TH1 *h_signal_sys_jesDown[nf];
   TH1 *h_background[nf];
   TH1 *h_background_sys_jesUp[nf];
   TH1 *h_background_sys_jesDown[nf];
   TH1 *h_background2[nf];
   TH1 *h_background2_sys_jesUp[nf];
   TH1 *h_background2_sys_jesDown[nf];
   TH1 *h_signal_sys_up[nf][nsys];
   TH1 *h_signal_sys_down[nf][nsys];
   TH1 *h_background_sys_up[nf][nsys];
   TH1 *h_background_sys_down[nf][nsys];
   TH1 *h_background2_sys_up[nf][nsys];
   TH1 *h_background2_sys_down[nf][nsys];
   
   h_data[0] = h_channel1_data;
   h_data[1] = h_channel2_data;

   h_signal[0] = h_channel1_signal;
   h_signal[1] = h_channel2_signal;
   h_signal_sys_jesUp[0] = h_channel1_signal_sys_jesUp;
   h_signal_sys_jesUp[1] = h_channel2_signal_sys_jesUp;
   h_signal_sys_jesDown[0] = h_channel1_signal_sys_jesDown;
   h_signal_sys_jesDown[1] = h_channel2_signal_sys_jesDown;

   h_background[0] = h_channel1_background;
   h_background[1] = h_channel2_background;
   h_background_sys_jesUp[0] = h_channel1_background_sys_jesUp;
   h_background_sys_jesUp[1] = h_channel2_background_sys_jesUp;
   h_background_sys_jesDown[0] = h_channel1_background_sys_jesDown;
   h_background_sys_jesDown[1] = h_channel2_background_sys_jesDown;

   h_background2[0] = h_channel1_background2;
   h_background2[1] = h_channel2_background2;
   h_background2_sys_jesUp[0] = h_channel1_background2_sys_jesUp;
   h_background2_sys_jesUp[1] = h_channel2_background2_sys_jesUp;
   h_background2_sys_jesDown[0] = h_channel1_background2_sys_jesDown;
   h_background2_sys_jesDown[1] = h_channel2_background2_sys_jesDown;
   
   for(int i=0;i<nf;i++)
     {
	h_signal_sys_up[i][0] = h_signal_sys_jesUp[i];
	h_signal_sys_down[i][0] = h_signal_sys_jesDown[i];
	h_background_sys_up[i][0] = h_background_sys_jesUp[i];
	h_background_sys_down[i][0] = h_background_sys_jesDown[i];
	h_background2_sys_up[i][0] = h_background2_sys_jesUp[i];
	h_background2_sys_down[i][0] = h_background2_sys_jesDown[i];
     }   
   
   double sys_sf_n[nsys];
   double sys_sf_p[nsys];

   double sys_sf_n_nsigma[nsys];
   double sys_sf_p_nsigma[nsys];
   
   TH1 *h_sys[nsys];
   
   for(int is=0;is<nsys;is++)
     {
	sys_sf_n[is] = 0;
	sys_sf_p[is] = 0;

	sys_sf_n_nsigma[is] = -1;
	sys_sf_p_nsigma[is] = 1;
     }   
   
   csm_channel_model* nullhyp[nf];
   csm_channel_model* testhyp[nf];
   
   for(int i=0;i<nf;i++)
     {	
	nullhyp[i] = new csm_channel_model();
	testhyp[i] = new csm_channel_model();
     }
  

   double sf = 1.;
   
   for(int i=0;i<nf;i++)
     {	
	nullhyp[i]->add_template((TH1*)h_background[i],
				 sf,
				 0,
				 sysname,
				 (double*)sys_sf_n,
				 (double*)sys_sf_p,
				 (TH1**)h_background_sys_down[i],
				 (double*)sys_sf_n_nsigma,
				 (TH1**)h_background_sys_up[i],
				 (double*)sys_sf_p_nsigma,
				 0,0);

	testhyp[i]->add_template((TH1*)h_background[i],
				 sf,
				 0,
				 sysname,
				 (double*)sys_sf_n,
				 (double*)sys_sf_p,
				 (TH1**)h_background_sys_down[i],
				 (double*)sys_sf_n_nsigma,
				 (TH1**)h_background_sys_up[i],
				 (double*)sys_sf_p_nsigma,
				 0,0);

	nullhyp[i]->add_template((TH1*)h_background2[i],
				 sf,
				 0,
				 sysname,
				 (double*)sys_sf_n,
				 (double*)sys_sf_p,
				 (TH1**)h_background2_sys_down[i],
				 (double*)sys_sf_n_nsigma,
				 (TH1**)h_background2_sys_up[i],
				 (double*)sys_sf_p_nsigma,
				 0,0);

	testhyp[i]->add_template((TH1*)h_background2[i],
				 sf,
				 0,
				 sysname,
				 (double*)sys_sf_n,
				 (double*)sys_sf_p,
				 (TH1**)h_background2_sys_down[i],
				 (double*)sys_sf_n_nsigma,
				 (TH1**)h_background2_sys_up[i],
				 (double*)sys_sf_p_nsigma,
				 0,0);
	
	testhyp[i]->add_template((TH1*)h_signal[i],
				 1.,
				 0,
				 sysname,
				 (double*)sys_sf_n,
				 (double*)sys_sf_p,
				 (TH1**)h_signal_sys_down[i],
				 (double*)sys_sf_n_nsigma,
				 (TH1**)h_signal_sys_up[i],
				 (double*)sys_sf_p_nsigma,
				 0,1);
     }
   
   csm_channel_model *nullhyp_pe[100];
   csm_channel_model *testhyp_pe[100];
   
   for(int i=0;i<nf;i++)
     {	
	nullhyp_pe[i] = new csm_channel_model();
	testhyp_pe[i] = new csm_channel_model();
     }   
   
   for(int i=0;i<nf;i++)
     {
	nullhyp_pe[i]->add_template((TH1*)h_background[i],
				    sf,
				    nsys,
				    sysname,
				    (double*)sys_sf_n,
				    (double*)sys_sf_p,
				    (TH1**)h_background_sys_down[i],
				    (double*)sys_sf_n_nsigma,
				    (TH1**)h_background_sys_up[i],
				    (double*)sys_sf_p_nsigma,
				    2,0);

	testhyp_pe[i]->add_template((TH1*)h_background[i],
				    sf,
				    nsys,
				    sysname,
				    (double*)sys_sf_n,
				    (double*)sys_sf_p,
				    (TH1**)h_background_sys_down[i],
				    (double*)sys_sf_n_nsigma,
				    (TH1**)h_background_sys_up[i],
				    (double*)sys_sf_p_nsigma,
				    2,0);

	nullhyp_pe[i]->add_template((TH1*)h_background2[i],
				    sf,
				    nsys,
				    sysname,
				    (double*)sys_sf_n,
				    (double*)sys_sf_p,
				    (TH1**)h_background2_sys_down[i],
				    (double*)sys_sf_n_nsigma,
				    (TH1**)h_background2_sys_up[i],
				    (double*)sys_sf_p_nsigma,
				    2,0);

	testhyp_pe[i]->add_template((TH1*)h_background2[i],
				    sf,
				    nsys,
				    sysname,
				    (double*)sys_sf_n,
				    (double*)sys_sf_p,
				    (TH1**)h_background2_sys_down[i],
				    (double*)sys_sf_n_nsigma,
				    (TH1**)h_background2_sys_up[i],
				    (double*)sys_sf_p_nsigma,
				    2,0);
	
	testhyp_pe[i]->add_template((TH1*)h_signal[i],
				    1.,
				    nsys,
				    sysname,
				    (double*)sys_sf_n,
				    (double*)sys_sf_p,
				    (TH1**)h_signal_sys_down[i],
				    (double*)sys_sf_n_nsigma,
				    (TH1**)h_signal_sys_up[i],
				    (double*)sys_sf_p_nsigma,
				    2,1);
     }

   for(int i=0;i<nf;i++)
     {
	nullhyp[i]->set_interpolation_style(CSM_INTERP_VERTICAL_EXTRAP);
	nullhyp_pe[i]->set_interpolation_style(CSM_INTERP_VERTICAL_EXTRAP);
	testhyp[i]->set_interpolation_style(CSM_INTERP_VERTICAL_EXTRAP);
	testhyp_pe[i]->set_interpolation_style(CSM_INTERP_VERTICAL_EXTRAP);
     }
  
   mclimit_csm* mymclimit = new mclimit_csm();
   
   csm_model* nullhyp_pe_combined = new csm_model();
   csm_model* testhyp_pe_combined = new csm_model();
   csm_model* nullhyp_combined = new csm_model();
   csm_model* testhyp_combined = new csm_model();
   
   for(int i=0;i<nf;i++)
     {
	std::string chn = "Channel " + std::string(Form("%d",i+1));
	nullhyp_pe_combined->add_chanmodel((csm_channel_model*)nullhyp_pe[i],const_cast<char*>(chn.c_str()));
	testhyp_pe_combined->add_chanmodel((csm_channel_model*)testhyp_pe[i],const_cast<char*>(chn.c_str()));
	nullhyp_combined->add_chanmodel((csm_channel_model*)nullhyp[i],const_cast<char*>(chn.c_str()));
	testhyp_combined->add_chanmodel((csm_channel_model*)testhyp[i],const_cast<char*>(chn.c_str()));
     }   

   for(int i=0;i<nf;i++)
     {	
	nullhyp_pe_combined->setpriorfunc(CSM_PRIORFUNC_EXPONENTIAL);
	testhyp_pe_combined->setpriorfunc(CSM_PRIORFUNC_EXPONENTIAL);
	nullhyp_combined->setpriorfunc(CSM_PRIORFUNC_EXPONENTIAL);
	testhyp_combined->setpriorfunc(CSM_PRIORFUNC_EXPONENTIAL);
     }
   
   for(int i=0;i<nf;i++)
     {
	std::string chn = "Channel " + std::string(Form("%d",i+1));
	mymclimit->set_datahist((TH1*)h_data[i],const_cast<char*>(chn.c_str()));
     }   
  
   mymclimit->set_null_hypothesis(nullhyp_combined);
   mymclimit->set_test_hypothesis(testhyp_combined);
   mymclimit->set_null_hypothesis_pe(nullhyp_pe_combined);
   mymclimit->set_test_hypothesis_pe(testhyp_pe_combined);

   nullhyp_pe_combined->print();
   testhyp_pe_combined->print();

   int npe = 100;
//   int npe = 1000;
   
   mymclimit->setminuitstepsize(0.001);
   mymclimit->setminuitmaxcalls(10000);
   mymclimit->setminosflag(1);
   mymclimit->setminosmaxcalls(10000);
   mymclimit->setprintflag(0);
   mymclimit->setpxprintflag(0);
   mymclimit->set_npe(npe);

   Double_t tsobs = mymclimit->ts();

   PRIOR prior=flat;

   double bh=0.95;
   double sflimit;
   double unc;
   double sm2,sm1,smed,sp1,sp2;

   int bayf = 1; // 1 - Heinrich, 2 - Markov chains
   
   double b_in_b = 0.;
   double b_in_e = 1.;
   double b_in_s = 0.001;
   
   mymclimit->bayes_interval_begin = b_in_b;                                                                         
   mymclimit->bayes_interval_end = b_in_e;                                                                           
   mymclimit->bayes_interval_step = b_in_s;
   
   if( bayf == 1 )
     {	     
	mymclimit->bayes_heinrich_withexpect(bh,&sflimit,&unc,npe,&sm2,&sm1,&smed,&sp1,&sp2);
	     
	std::cout << "Expected Limit at: " << bh <<" % C.L "<< smed << " Full band: -2SD -1SD MED +1SD +2SD " << sm2 << " " << sm1 << " " << smed << " " << sp1 << " " << sp2 << std::endl;
	std::cout << "Observed Limit at: " << bh <<" % C.L "<< sflimit << std::endl;
     }	
   
   if( bayf == 2 )
     {	     
	sflimit = mymclimit->bayeslimit_mcmc1(bh,prior,"posterior.root");
	
	mymclimit->bayeslimit_mcmc1_expect(bh, prior, npe,
					   &sm2, &sm1, &smed,
					   &sp1, &sp2);
	

	std::cout << "Expected Limit at: " << bh <<" % C.L "<< smed << " Full band: -2SD -1SD MED +1SD +2SD " << sm2 << " " << sm1 << " " << smed << " " << sp1 << " " << sp2 << std::endl;
	std::cout << "Observed Limit at: " << bh <<" % C.L "<< sflimit << std::endl;
     }		
	   
   delete mymclimit;
}
