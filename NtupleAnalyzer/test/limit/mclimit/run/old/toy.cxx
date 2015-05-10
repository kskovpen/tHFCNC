#include "TROOT.h"
#include "TFile.h"
#include "TH2.h"
#include "Riostream.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TRandom.h"
#include "TParameter.h"
#include "TStopwatch.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <math.h>

#include "mclimit_csm.h"

double getruntime(TStopwatch*);

int main(int argc, char *argv[])
{
   if( argc < 34 )
     {
	std::cout << "Please specify the input parameters (all have to be specified):" << std::endl;
	std::cout << "./toy [bkg_file] [sig_file] [value] [bayes] [npe] [step] \
[doProf] [input] [expcls] [sfsig] [pval] [interp] [nsigma] [seed] [corr] [symm]" << std::endl;
	std::cout << "bkg_file - file with background and data histograms" << std::endl;
	std::cout << "sig_file - file with signal histograms" << std::endl;
	std::cout << "value    - 666(all) 0(med) 1(+sig) 2(+2sig) -1(-sig) -2(-2sig) -3(obs) -4(sf)" << std::endl;
	std::cout << "bayes    - 0(use CLs) 1(use Bayesian) 2(Markov chains)" << std::endl;
	std::cout << "npe      - number of pseudo-experiments to generate (ex. 20000)" << std::endl;
	std::cout << "step     - MINUIT step size (ex. 0.01)" << std::endl;
	std::cout << "doProf   - do profiling ? (0 - do not, 1 - do it!)" << std::endl;
	std::cout << "input    - 0(Winter) 1(Summer)" << std::endl;
	std::cout << "expcls   - 0(switch off) 1(switch on)" << std::endl;
	std::cout << "sfsig    - SF on signal" << std::endl;
	std::cout << "pval     - p-value (H0) (0 - do not, 1 - do it!)" << std::endl;
	std::cout << "interp   - interpolation (0 - vertical, 1 - vertical with extrapolation)" << std::endl;
	std::cout << "nsigma   - systematic shape variation" << std::endl;
	std::cout << "seed     - seed" << std::endl;
	std::cout << "sigh     - signal histogram name" << std::endl;
	std::cout << "chan1    - channel1 name" << std::endl;
	std::cout << "chan2    - channel2 name" << std::endl;
	std::cout << "chan3    - channel3 name" << std::endl;
	std::cout << "chan4    - channel4 name" << std::endl;
	std::cout << "chan5    - channel5 name" << std::endl;
	std::cout << "chan6    - channel6 name" << std::endl;
	std::cout << "sfsig1   - channel1 signal SF" << std::endl;
	std::cout << "sfsig2   - channel2 signal SF" << std::endl;
	std::cout << "sfsig3   - channel3 signal SF" << std::endl;
	std::cout << "sfsig4   - channel4 signal SF" << std::endl;
	std::cout << "sfsig5   - channel5 signal SF" << std::endl;
	std::cout << "sfsig6   - channel6 signal SF" << std::endl;
	std::cout << "sel1    - channel1 selection" << std::endl;
	std::cout << "sel2    - channel2 selection" << std::endl;
	std::cout << "sel3    - channel3 selection" << std::endl;
	std::cout << "sel4    - channel4 selection" << std::endl;
	std::cout << "sel5    - channel5 selection" << std::endl;
	std::cout << "sel6    - channel6 selection" << std::endl;
	std::cout << "dist    - shape distribution" << std::endl;
	exit(1);
     }   

   std::string fname = argv[1];
   std::string fname_sig = argv[2];
   int sigm = atoi(argv[3]);
   int bayf = atoi(argv[4]);
   int npec = atoi(argv[5]);
   double step = atof(argv[6]);
   int doprof = atoi(argv[7]);
   int inputType = atoi(argv[8]);
   int doExp = atoi(argv[9]);
   double sfsig = atof(argv[10]);
   int pval = atoi(argv[11]);
   int interp = atoi(argv[12]);
   double nsigma = atof(argv[13]);
   int seed = atoi(argv[14]);
   std::string sigh = argv[15];
   std::string chan1 = argv[16];
   std::string chan2 = argv[17];
   std::string chan3 = argv[18];
   std::string chan4 = argv[19];
   std::string chan5 = argv[20];
   std::string chan6 = argv[21];
   double sfsig1 = atof(argv[22]);
   double sfsig2 = atof(argv[23]);
   double sfsig3 = atof(argv[24]);
   double sfsig4 = atof(argv[25]);
   double sfsig5 = atof(argv[26]);
   double sfsig6 = atof(argv[27]);
   std::string sel1 = argv[28];
   std::string sel2 = argv[29];
   std::string sel3 = argv[30];
   std::string sel4 = argv[31];
   std::string sel5 = argv[32];
   std::string sel6 = argv[33];
   std::string dist = argv[34];

   std::string fname_arr[100];
   std::string fname_sig_arr[100];
   
   std::stringstream fnamev(fname);
   std::stringstream fname_sigv(fname_sig);
   
   std::string ifile;
   int c1 = 0;
   while( getline(fnamev, ifile, '@') )
     {
	fname_arr[c1] = ifile;
	c1++;
     }   
   int c2 = 0;
   while( getline(fname_sigv, ifile, '@') )
     {
	fname_sig_arr[c2] = ifile;
	c2++;
     } 
   
   if( c1 != c2 )
     {
	std::cout << "Number of signal and background input files must be the same" << std::endl;
	exit(1);
     }   
   
   int nf = c1;
        
   std::cout << "Requested input parameters: " 
     " value=" << sigm << 
     " bayes=" << bayf << 
     " Npe=" << npec << 
     " step=" << step << 
     " doProf=" << doprof <<
     " doExp=" << doExp <<
     " sfsig=" << sfsig <<
     " pval=" << pval <<
     " interp=" << interp <<
     " nsigma=" << nsigma <<
     " seed=" << seed <<
     " sigh=" << sigh <<
     " chan1=" << chan1 <<
     " chan2=" << chan2 <<
     " chan3=" << chan3 <<
     " chan4=" << chan4 <<
     " chan5=" << chan5 <<
     " chan6=" << chan6 <<
     " sfsig1=" << sfsig1 <<
     " sfsig2=" << sfsig2 <<
     " sfsig3=" << sfsig3 <<
     " sfsig4=" << sfsig4 <<
     " sfsig5=" << sfsig5 <<
     " sfsig6=" << sfsig6 <<
     " sel1=" << sel1 <<
     " sel2=" << sel2 <<
     " sel3=" << sel3 <<
     " sel4=" << sel4 <<
     " sel5=" << sel5 <<
     " sel6=" << sel6 <<
     " dist=" << dist <<
     std::endl;

   gRandom->SetSeed(seed);

   std::cout << "Number of channels to be generated = " << nf << std::endl;
   for(int i=0;i<nf;i++)
     {
	std::cout << "Channel #" << i+1 << ": BKG " << fname_arr[i] << std::endl;
	std::cout << "Channel #" << i+1 << ": SIG " << fname_sig_arr[i] << std::endl;
     }   
   
   TStopwatch* timer_pe = new TStopwatch();
   TStopwatch* timer_bayesian = new TStopwatch();
   TStopwatch* timer_cls = new TStopwatch();

   TFile *f[50];
   TH1 *h_sample_1[50];
   TH1 *h_sample_2[50];
   TH1 *h_sample_3[50];
   TH1 *h_sample_4[50];
   TH1 *h_data[50];

   TFile *f_sig[50];
   TH1 *h_signal[50];

   std::string data = "DATA";
   std::string samp1 = "ZJETS";
   std::string samp2 = "DBX";
   std::string samp3 = "TOP";
   std::string samp4 = "QCD";
   
   std::string chan = "";
   std::string sel = "";
   double sfsigg = 1.;
   
   for(int i=0;i<nf;i++)
     {	
	if( i == 0 ) chan = chan1;
	if( i == 1 ) chan = chan2;
	if( i == 2 ) chan = chan3;
	if( i == 3 ) chan = chan4;
	if( i == 4 ) chan = chan5;
	if( i == 5 ) chan = chan6;

	if( i == 0 ) sel = sel1;
	if( i == 1 ) sel = sel2;
	if( i == 2 ) sel = sel3;
	if( i == 3 ) sel = sel4;
	if( i == 4 ) sel = sel5;
	if( i == 5 ) sel = sel6;
	
	if( i == 0 ) sfsigg = sfsig1;
	if( i == 1 ) sfsigg = sfsig2;
	if( i == 2 ) sfsigg = sfsig3;
	if( i == 3 ) sfsigg = sfsig4;
	if( i == 4 ) sfsigg = sfsig5;
	if( i == 5 ) sfsigg = sfsig6;
	
	f[i] = TFile::Open(fname_arr[i].c_str());
	std::string str_sample_1 = "h_"+samp1+"_"+dist+"_"+chan+"_"+sel;
	std::string str_sample_2 = "h_"+samp2+"_"+dist+"_"+chan+"_"+sel;
	std::string str_sample_3 = "h_"+samp3+"_"+dist+"_"+chan+"_"+sel;
	std::string str_sample_4 = "h_"+samp4+"_"+dist+"_"+chan+"_"+sel;
	h_sample_1[i] = (TH1F*)f[i]->Get(str_sample_1.c_str());
	h_sample_2[i] = (TH1F*)f[i]->Get(str_sample_2.c_str());
	h_sample_3[i] = (TH1F*)f[i]->Get(str_sample_3.c_str());
	h_sample_4[i] = (TH1F*)f[i]->Get(str_sample_4.c_str());

	std::string str_data = "h_"+data+"_"+dist+"_"+chan+"_"+sel;
//	h_data[i] = (TH1F*)f[i]->Get("data");
	h_data[i] = (TH1F*)f[i]->Get(str_data.c_str());
	
	f_sig[i] = TFile::Open(fname_sig_arr[i].c_str());
	std::string str_signal = "h_"+sigh+"_"+dist+"_"+chan+"_"+sel;
	h_signal[i] = (TH1F*)f_sig[i]->Get(str_signal.c_str());

	h_signal[i]->Scale(sfsigg);
     }   

   std::cout << "Successfully read all files" << std::endl;
   
   int sample_1_nsys = 2;
   int sample_2_nsys = 2;
   int sample_3_nsys = 2;
   int sample_4_nsys = 1;
   int signal_nsys = 2;

   int nmax = 20;

   char *sample_1_sysname[5000];
   char *sample_2_sysname[5000];
   char *sample_3_sysname[5000];
   char *sample_4_sysname[5000];   
   char *signal_sysname[5000];

   char *sample_1_sysname_tf[sample_1_nsys];
   char *sample_2_sysname_tf[sample_2_nsys];
   char *sample_3_sysname_tf[sample_3_nsys];
   char *sample_4_sysname_tf[sample_4_nsys];
   char *signal_sysname_tf[signal_nsys];

   for(int i=0;i<nf;i++)
     {		  	     
	sample_1_sysname[nmax*i] = Form("JES_sample_1_%d",i);
	sample_1_sysname[nmax*i+1] = Form("JER_sample_1_%d",i);
	
	sample_2_sysname[nmax*i] = Form("JES_sample_2_%d",i);
	sample_2_sysname[nmax*i+1] = Form("JER_sample_2_%d",i);
	
	sample_3_sysname[nmax*i] = Form("JES_sample_3_%d",i);
	sample_3_sysname[nmax*i+1] = Form("JER_sample_3_%d",i);

	sample_4_sysname[nmax*i] = Form("FLAT_sample_4_%d",i);
	
//	sample_4_sysname[nmax*i] = Form("JES_sample_4_%d",i);
//	sample_4_sysname[nmax*i+1] = Form("JER_sample_4_%d",i);

	signal_sysname[nmax*i] = Form("JES_signal_%d",i);
	signal_sysname[nmax*i+1] = Form("JER_signal_%d",i);
	
	sample_1_sysname_tf[0] = "jes";
	sample_1_sysname_tf[1] = "jer";
	
	sample_2_sysname_tf[0] = "jes";
	sample_2_sysname_tf[1] = "jer";
	
	sample_3_sysname_tf[0] = "jes";
	sample_3_sysname_tf[1] = "jer";
	
	sample_4_sysname_tf[0] = "flat";
	
//	sample_4_sysname_tf[0] = "jes";
//	sample_4_sysname_tf[1] = "jer";

	signal_sysname_tf[0] = "jes";
	signal_sysname_tf[1] = "jer";
     }  

   TH1 *h_sample_1_sys_p[50][sample_1_nsys];
   TH1 *h_sample_1_sys_n[50][sample_1_nsys];
   TH1 *h_sample_2_sys_p[50][sample_2_nsys];
   TH1 *h_sample_2_sys_n[50][sample_2_nsys];
   TH1 *h_sample_3_sys_p[50][sample_3_nsys];
   TH1 *h_sample_3_sys_n[50][sample_3_nsys];
   TH1 *h_sample_4_sys_p[50][sample_4_nsys];
   TH1 *h_sample_4_sys_n[50][sample_4_nsys];
   TH1 *h_signal_sys_p[50][signal_nsys];
   TH1 *h_signal_sys_n[50][signal_nsys];
   
   std::cout << "Retreive histograms" << std::endl;

   for(int j=0;j<nf;j++)
     {
	if( j == 0 ) chan = chan1;
	if( j == 1 ) chan = chan2;
	if( j == 2 ) chan = chan3;
	if( j == 0 ) sel = sel1;
	if( j == 1 ) sel = sel2;
	if( j == 2 ) sel = sel3;
	for(int i=0;i<sample_1_nsys;i++)
	  {
	     std::string hnameUp = "h_"+samp1+"_"+dist+"_"+chan+"_"+sel+"_"+std::string(sample_1_sysname_tf[i])+"Up";
	     std::string hnameDown = "h_"+samp1+"_"+dist+"_"+chan+"_"+sel+"_"+std::string(sample_1_sysname_tf[i])+"Down";
	     
	     if( sample_1_sysname_tf[i] == "jer" )
	       hnameDown = "h_"+samp1+"_"+dist+"_"+chan+"_"+sel;
	     
	     h_sample_1_sys_p[j][i] =  (TH1*)f[j]->Get(hnameUp.c_str());
	     h_sample_1_sys_n[j][i] =  (TH1*)f[j]->Get(hnameDown.c_str());
	  }   

	for(int i=0;i<sample_2_nsys;i++)
	  {
	     std::string hnameUp = "h_"+samp2+"_"+dist+"_"+chan+"_"+sel+"_"+std::string(sample_2_sysname_tf[i])+"Up";
	     std::string hnameDown = "h_"+samp2+"_"+dist+"_"+chan+"_"+sel+"_"+std::string(sample_2_sysname_tf[i])+"Down";
	     
	     if( sample_2_sysname_tf[i] == "jer" )
	       hnameDown = "h_"+samp2+"_"+dist+"_"+chan+"_"+sel;
	     
	     h_sample_2_sys_p[j][i] =  (TH1*)f[j]->Get(hnameUp.c_str());
	     h_sample_2_sys_n[j][i] =  (TH1*)f[j]->Get(hnameDown.c_str());
	  }   

	for(int i=0;i<sample_3_nsys;i++)
	  {
	     std::string hnameUp = "h_"+samp3+"_"+dist+"_"+chan+"_"+sel+"_"+std::string(sample_3_sysname_tf[i])+"Up";
	     std::string hnameDown = "h_"+samp3+"_"+dist+"_"+chan+"_"+sel+"_"+std::string(sample_3_sysname_tf[i])+"Down";
	     
	     if( sample_3_sysname_tf[i] == "jer" )
	       hnameDown = "h_"+samp3+"_"+dist+"_"+chan+"_"+sel;
	     
	     h_sample_3_sys_p[j][i] =  (TH1*)f[j]->Get(hnameUp.c_str());
	     h_sample_3_sys_n[j][i] =  (TH1*)f[j]->Get(hnameDown.c_str());
	  }   

	for(int i=0;i<sample_4_nsys;i++)
	  {
	     std::string hnameUp = "h_"+samp4+"_"+dist+"_"+chan+"_"+sel+"_"+std::string(sample_4_sysname_tf[i])+"Up";
	     std::string hnameDown = "h_"+samp4+"_"+dist+"_"+chan+"_"+sel+"_"+std::string(sample_4_sysname_tf[i])+"Down";
	     
	     if( sample_4_sysname_tf[i] == "jer" )
	       hnameDown = "h_"+samp4+"_"+dist+"_"+chan+"_"+sel;
	     
	     h_sample_4_sys_p[j][i] =  (TH1*)f[j]->Get(hnameUp.c_str());
	     h_sample_4_sys_n[j][i] =  (TH1*)f[j]->Get(hnameDown.c_str());
	  }   

	for(int i=0;i<signal_nsys;i++)
	  {
	     std::string hnameUp = "h_"+sigh+"_"+dist+"_"+chan+"_"+sel+"_"+std::string(signal_sysname_tf[i])+"Up";
	     std::string hnameDown = "h_"+sigh+"_"+dist+"_"+chan+"_"+sel+"_"+std::string(signal_sysname_tf[i])+"Down";
	     
	     if( signal_sysname_tf[i] == "jer" )
	       hnameDown = "h_"+sigh+"_"+dist+"_"+chan+"_"+sel;

	     h_signal_sys_p[j][i] =  (TH1*)f_sig[j]->Get(hnameUp.c_str());
	     h_signal_sys_n[j][i] =  (TH1*)f_sig[j]->Get(hnameDown.c_str());
	     h_signal_sys_p[j][i]->Scale(sfsigg);
	     h_signal_sys_n[j][i]->Scale(sfsigg);
	  }	
     }     

   std::cout << "Systematic variation set" << std::endl;
   
   double h_sample_1_sys_sigma_p[100][sample_1_nsys];
   double h_sample_1_sys_sigma_n[100][sample_1_nsys];
   double h_sample_2_sys_sigma_p[100][sample_2_nsys];
   double h_sample_2_sys_sigma_n[100][sample_2_nsys];
   double h_sample_3_sys_sigma_p[100][sample_3_nsys];
   double h_sample_3_sys_sigma_n[100][sample_3_nsys];
   double h_sample_4_sys_sigma_p[100][sample_4_nsys];
   double h_sample_4_sys_sigma_n[100][sample_4_nsys];
   double h_sample_1_sys_sf_p[100][sample_1_nsys];
   double h_sample_1_sys_sf_n[100][sample_1_nsys];
   double h_sample_2_sys_sf_p[100][sample_2_nsys];
   double h_sample_2_sys_sf_n[100][sample_2_nsys];
   double h_sample_3_sys_sf_p[100][sample_3_nsys];
   double h_sample_3_sys_sf_n[100][sample_3_nsys];
   double h_sample_4_sys_sf_p[100][sample_4_nsys];
   double h_sample_4_sys_sf_n[100][sample_4_nsys];

   double h_signal_sys_sigma_p[100][signal_nsys];
   double h_signal_sys_sigma_n[100][signal_nsys];
   double h_signal_sys_sf_p[100][signal_nsys];
   double h_signal_sys_sf_n[100][signal_nsys];

   for(int j=0;j<nf;j++)
     {	
	for(int i=0;i<sample_1_nsys;i++)
	  {
	     h_sample_1_sys_sigma_p[j][i] = nsigma;
	     h_sample_1_sys_sigma_n[j][i] = -nsigma;
	     h_sample_1_sys_sf_p[j][i] = 0.;
	     h_sample_1_sys_sf_n[j][i] = 0.;
	  }	

	for(int i=0;i<sample_2_nsys;i++)
	  {
	     h_sample_2_sys_sigma_p[j][i] = nsigma;
	     h_sample_2_sys_sigma_n[j][i] = -nsigma;
	     h_sample_2_sys_sf_p[j][i] = 0.;
	     h_sample_2_sys_sf_n[j][i] = 0.;
	  }	

	for(int i=0;i<sample_3_nsys;i++)
	  {
	     h_sample_3_sys_sigma_p[j][i] = nsigma;
	     h_sample_3_sys_sigma_n[j][i] = -nsigma;
	     h_sample_3_sys_sf_p[j][i] = 0.;
	     h_sample_3_sys_sf_n[j][i] = 0.;
	  }	

	for(int i=0;i<sample_4_nsys;i++)
	  {
	     h_sample_4_sys_sigma_p[j][i] = nsigma;
	     h_sample_4_sys_sigma_n[j][i] = -nsigma;
	     h_sample_4_sys_sf_p[j][i] = 0.;
	     h_sample_4_sys_sf_n[j][i] = 0.;
	  }	
	
	for(int i=0;i<signal_nsys;i++)
	  {
	     h_signal_sys_sigma_p[j][i] = nsigma;
	     h_signal_sys_sigma_n[j][i] = -nsigma;
	     h_signal_sys_sf_p[j][i] = 0.;
	     h_signal_sys_sf_n[j][i] = 0.;
	  }	
     }   

   std::cout << "Ready to construct models" << std::endl;
   
   csm_channel_model* nullhyp[100];
   csm_channel_model* testhyp[100];
   
   for(int i=0;i<nf;i++)
     {
	nullhyp[i] = new csm_channel_model();
	testhyp[i] = new csm_channel_model();
     }   

   double sf=(1./1.);
   
   std::cout << "Prepare fit phase" << std::endl;

   for(int i=0;i<nf;i++)
     {
	int nsys_samp_1 = sample_1_nsys;
	int nsys_samp_2 = sample_2_nsys;
	int nsys_samp_3 = sample_3_nsys;
	int nsys_samp_4 = sample_4_nsys;
	int nsys_signal = signal_nsys;
	
	if( ! doprof )
	  {
	     nsys_samp_1 = 0;
	     nsys_samp_2 = 0;
	     nsys_samp_3 = 0;
	     nsys_samp_4 = 0;
	     nsys_signal = 0;
	  }

	char *sample_1_sysname_opt[sample_1_nsys];
	for(int h=0;h<sample_1_nsys;h++)
	  sample_1_sysname_opt[h] = sample_1_sysname[i*nmax+h];

	char *sample_2_sysname_opt[sample_2_nsys];
	for(int h=0;h<sample_2_nsys;h++)
	  sample_2_sysname_opt[h] = sample_2_sysname[i*nmax+h];

	char *sample_3_sysname_opt[sample_3_nsys];
	for(int h=0;h<sample_3_nsys;h++)
	  sample_3_sysname_opt[h] = sample_3_sysname[i*nmax+h];

	char *sample_4_sysname_opt[sample_4_nsys];
	for(int h=0;h<sample_4_nsys;h++)
	  sample_4_sysname_opt[h] = sample_4_sysname[i*nmax+h];
	
	char *signal_sysname_opt[signal_nsys];
	for(int h=0;h<signal_nsys;h++)
	  signal_sysname_opt[h] = signal_sysname[i*nmax+h];
	
	nullhyp[i]->add_template((TH1*)h_sample_1[i],
				 sf,
				 nsys_samp_1,
				 sample_1_sysname_opt,
				 (double*)h_sample_1_sys_sf_n[i],
				 (double*)h_sample_1_sys_sf_p[i],
				 (TH1**)h_sample_1_sys_n[i],
				 (double*)h_sample_1_sys_sigma_n[i],
				 (TH1**)h_sample_1_sys_p[i],
				 (double*)h_sample_1_sys_sigma_p[i],
				 0,0);
	
	testhyp[i]->add_template((TH1*)h_sample_1[i],
				 sf,
				 nsys_samp_1,
				 sample_1_sysname_opt,
				 (double*)h_sample_1_sys_sf_n[i],
				 (double*)h_sample_1_sys_sf_p[i],
				 (TH1**)h_sample_1_sys_n[i],
				 (double*)h_sample_1_sys_sigma_n[i],
				 (TH1**)h_sample_1_sys_p[i],
				 (double*)h_sample_1_sys_sigma_p[i],
				 0,0);

	nullhyp[i]->add_template((TH1*)h_sample_2[i],
				 sf,
				 nsys_samp_2,
				 sample_2_sysname_opt,
				 (double*)h_sample_2_sys_sf_n[i],
				 (double*)h_sample_2_sys_sf_p[i],
				 (TH1**)h_sample_2_sys_n[i],
				 (double*)h_sample_2_sys_sigma_n[i],
				 (TH1**)h_sample_2_sys_p[i],
				 (double*)h_sample_2_sys_sigma_p[i],
				 0,0);
	
	testhyp[i]->add_template((TH1*)h_sample_2[i],
				 sf,
				 nsys_samp_2,
				 sample_2_sysname_opt,
				 (double*)h_sample_2_sys_sf_n[i],
				 (double*)h_sample_2_sys_sf_p[i],
				 (TH1**)h_sample_2_sys_n[i],
				 (double*)h_sample_2_sys_sigma_n[i],
				 (TH1**)h_sample_2_sys_p[i],
				 (double*)h_sample_2_sys_sigma_p[i],
				 0,0);

	nullhyp[i]->add_template((TH1*)h_sample_3[i],
				 sf,
				 nsys_samp_3,
				 sample_3_sysname_opt,
				 (double*)h_sample_3_sys_sf_n[i],
				 (double*)h_sample_3_sys_sf_p[i],
				 (TH1**)h_sample_3_sys_n[i],
				 (double*)h_sample_3_sys_sigma_n[i],
				 (TH1**)h_sample_3_sys_p[i],
				 (double*)h_sample_3_sys_sigma_p[i],
				 0,0);
	
	testhyp[i]->add_template((TH1*)h_sample_3[i],
				 sf,
				 nsys_samp_3,
				 sample_3_sysname_opt,
				 (double*)h_sample_3_sys_sf_n[i],
				 (double*)h_sample_3_sys_sf_p[i],
				 (TH1**)h_sample_3_sys_n[i],
				 (double*)h_sample_3_sys_sigma_n[i],
				 (TH1**)h_sample_3_sys_p[i],
				 (double*)h_sample_3_sys_sigma_p[i],
				 0,0);

	nullhyp[i]->add_template((TH1*)h_sample_4[i],
				 sf,
				 nsys_samp_4,
				 sample_4_sysname_opt,
				 (double*)h_sample_4_sys_sf_n[i],
				 (double*)h_sample_4_sys_sf_p[i],
				 (TH1**)h_sample_4_sys_n[i],
				 (double*)h_sample_4_sys_sigma_n[i],
				 (TH1**)h_sample_4_sys_p[i],
				 (double*)h_sample_4_sys_sigma_p[i],
				 0,0);
	
	testhyp[i]->add_template((TH1*)h_sample_4[i],
				 sf,
				 nsys_samp_4,
				 sample_4_sysname_opt,
				 (double*)h_sample_4_sys_sf_n[i],
				 (double*)h_sample_4_sys_sf_p[i],
				 (TH1**)h_sample_4_sys_n[i],
				 (double*)h_sample_4_sys_sigma_n[i],
				 (TH1**)h_sample_4_sys_p[i],
				 (double*)h_sample_4_sys_sigma_p[i],
				 0,0);
	
	if( ! pval )
	  {	     
	     testhyp[i]->add_template((TH1*)h_signal[i],
				      sfsig,
				      nsys_signal,
				      signal_sysname_opt,
				      (double*)h_signal_sys_sf_n[i],
				      (double*)h_signal_sys_sf_p[i],
				      (TH1**)h_signal_sys_n[i],
				      (double*)h_signal_sys_sigma_n[i],
				      (TH1**)h_signal_sys_p[i],
				      (double*)h_signal_sys_sigma_p[i],
				      0,1);
	  }
     }   

   csm_channel_model *nullhyp_pe[100];
   csm_channel_model *testhyp_pe[100];

   std::cout << "Prepare PE phase" << std::endl;
   
   for(int i=0;i<nf;i++)
     {
	if( doprof )
	  {	
	     nullhyp_pe[i] = (csm_channel_model*)(nullhyp[i]->Clone());
	     testhyp_pe[i] = (csm_channel_model*)(testhyp[i]->Clone());
	  }   
	else
	  {	
	     nullhyp_pe[i] = new csm_channel_model();
	     testhyp_pe[i] = new csm_channel_model();

	     char *sample_1_sysname_opt[sample_1_nsys];
	     for(int h=0;h<sample_1_nsys;h++)
	       sample_1_sysname_opt[h] = sample_1_sysname[i*nmax+h];

	     char *sample_2_sysname_opt[sample_2_nsys];
	     for(int h=0;h<sample_2_nsys;h++)
	       sample_2_sysname_opt[h] = sample_2_sysname[i*nmax+h];

	     char *sample_3_sysname_opt[sample_3_nsys];
	     for(int h=0;h<sample_3_nsys;h++)
	       sample_3_sysname_opt[h] = sample_3_sysname[i*nmax+h];

	     char *sample_4_sysname_opt[sample_4_nsys];
	     for(int h=0;h<sample_4_nsys;h++)
	       sample_4_sysname_opt[h] = sample_4_sysname[i*nmax+h];
	     
	     char *signal_sysname_opt[signal_nsys];
	     for(int h=0;h<signal_nsys;h++)
	       signal_sysname_opt[h] = signal_sysname[i*nmax+h];

	     nullhyp_pe[i]->add_template((TH1*)h_sample_1[i],
					 sf,
					 sample_1_nsys,
					 sample_1_sysname_opt,
					 (double*)h_sample_1_sys_sf_n[i],
					 (double*)h_sample_1_sys_sf_p[i],
					 (TH1**)h_sample_1_sys_n[i],
					 (double*)h_sample_1_sys_sigma_n[i],
					 (TH1**)h_sample_1_sys_p[i],
					 (double*)h_sample_1_sys_sigma_p[i],
					 2,0);
	     
	     testhyp_pe[i]->add_template((TH1*)h_sample_1[i],
					 sf,
					 sample_1_nsys,
					 sample_1_sysname_opt,
					 (double*)h_sample_1_sys_sf_n[i],
					 (double*)h_sample_1_sys_sf_p[i],
					 (TH1**)h_sample_1_sys_n[i],
					 (double*)h_sample_1_sys_sigma_n[i],
					 (TH1**)h_sample_1_sys_p[i],
					 (double*)h_sample_1_sys_sigma_p[i],
					 2,0);
	     
	     nullhyp_pe[i]->add_template((TH1*)h_sample_2[i],
					 sf,
					 sample_2_nsys,
					 sample_2_sysname_opt,
					 (double*)h_sample_2_sys_sf_n[i],
					 (double*)h_sample_2_sys_sf_p[i],
					 (TH1**)h_sample_2_sys_n[i],
					 (double*)h_sample_2_sys_sigma_n[i],
					 (TH1**)h_sample_2_sys_p[i],
					 (double*)h_sample_2_sys_sigma_p[i],
					 2,0);
	     
	     testhyp_pe[i]->add_template((TH1*)h_sample_2[i],
					 sf,
					 sample_2_nsys,
					 sample_2_sysname_opt,
					 (double*)h_sample_2_sys_sf_n[i],
					 (double*)h_sample_2_sys_sf_p[i],
					 (TH1**)h_sample_2_sys_n[i],
					 (double*)h_sample_2_sys_sigma_n[i],
					 (TH1**)h_sample_2_sys_p[i],
					 (double*)h_sample_2_sys_sigma_p[i],
					 2,0);
	     
	     nullhyp_pe[i]->add_template((TH1*)h_sample_3[i],
					 sf,
					 sample_3_nsys,
					 sample_3_sysname_opt,
					 (double*)h_sample_3_sys_sf_n[i],
					 (double*)h_sample_3_sys_sf_p[i],
					 (TH1**)h_sample_3_sys_n[i],
					 (double*)h_sample_3_sys_sigma_n[i],
					 (TH1**)h_sample_3_sys_p[i],
					 (double*)h_sample_3_sys_sigma_p[i],
					 2,0);
	     
	     testhyp_pe[i]->add_template((TH1*)h_sample_3[i],
					 sf,
					 sample_3_nsys,
					 sample_3_sysname_opt,
					 (double*)h_sample_3_sys_sf_n[i],
					 (double*)h_sample_3_sys_sf_p[i],
					 (TH1**)h_sample_3_sys_n[i],
					 (double*)h_sample_3_sys_sigma_n[i],
					 (TH1**)h_sample_3_sys_p[i],
					 (double*)h_sample_3_sys_sigma_p[i],
					 2,0);
	     
	     nullhyp_pe[i]->add_template((TH1*)h_sample_4[i],
					 sf,
					 sample_4_nsys,
					 sample_4_sysname_opt,
					 (double*)h_sample_4_sys_sf_n[i],
					 (double*)h_sample_4_sys_sf_p[i],
					 (TH1**)h_sample_4_sys_n[i],
					 (double*)h_sample_4_sys_sigma_n[i],
					 (TH1**)h_sample_4_sys_p[i],
					 (double*)h_sample_4_sys_sigma_p[i],
					 2,0);
	     
	     testhyp_pe[i]->add_template((TH1*)h_sample_4[i],
					 sf,
					 sample_4_nsys,
					 sample_4_sysname_opt,
					 (double*)h_sample_4_sys_sf_n[i],
					 (double*)h_sample_4_sys_sf_p[i],
					 (TH1**)h_sample_4_sys_n[i],
					 (double*)h_sample_4_sys_sigma_n[i],
					 (TH1**)h_sample_4_sys_p[i],
					 (double*)h_sample_4_sys_sigma_p[i],
					 2,0);
	     
	     if( ! pval )
	       {	
		  testhyp_pe[i]->add_template((TH1*)h_signal[i],
					      sfsig,
					      signal_nsys,
					      signal_sysname_opt,
					      (double*)h_signal_sys_sf_n[i],
					      (double*)h_signal_sys_sf_p[i],
					      (TH1**)h_signal_sys_n[i],
					      (double*)h_signal_sys_sigma_n[i],
					      (TH1**)h_signal_sys_p[i],
					      (double*)h_signal_sys_sigma_p[i],
					      2,1);
	       }
	  }
     }

   if( interp )
     {	
	for(int i=0;i<nf;i++)
	  {
	     nullhyp[i]->set_interpolation_style(CSM_INTERP_VERTICAL_EXTRAP);
	     nullhyp_pe[i]->set_interpolation_style(CSM_INTERP_VERTICAL_EXTRAP);
	     testhyp[i]->set_interpolation_style(CSM_INTERP_VERTICAL_EXTRAP);
	     testhyp_pe[i]->set_interpolation_style(CSM_INTERP_VERTICAL_EXTRAP);
	  }
     }   
   else
     {	
	for(int i=0;i<nf;i++)
	  {
	     nullhyp[i]->set_interpolation_style(CSM_INTERP_VERTICAL);
	     nullhyp_pe[i]->set_interpolation_style(CSM_INTERP_VERTICAL);
	     testhyp[i]->set_interpolation_style(CSM_INTERP_VERTICAL);
	     testhyp_pe[i]->set_interpolation_style(CSM_INTERP_VERTICAL);
	  }
     }   
   
   mclimit_csm* mymclimit = new mclimit_csm();

   std::cout << "Combine channels" << std::endl;
   
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
   
   std::cout << "Set data input" << std::endl;
   
   for(int i=0;i<nf;i++)
     {
	std::string chn = "Channel " + std::string(Form("%d",i+1));
	mymclimit->set_datahist((TH1*)h_data[i],const_cast<char*>(chn.c_str()));
     }   
   
   std::cout << "Channels successfully combined" << std::endl;
   
   mymclimit->set_null_hypothesis(nullhyp_combined);
   mymclimit->set_test_hypothesis(testhyp_combined);
   mymclimit->set_null_hypothesis_pe(nullhyp_pe_combined);
   mymclimit->set_test_hypothesis_pe(testhyp_pe_combined);

   nullhyp_pe_combined->print();
   testhyp_pe_combined->print();

   int npe = npec;
   
   mymclimit->setminuitstepsize(step);
   mymclimit->setminuitmaxcalls(10000);
   mymclimit->setminosflag(1);
   mymclimit->setminosmaxcalls(10000);
   mymclimit->setprintflag(0);
   mymclimit->setpxprintflag(0);
   mymclimit->set_npe(npe);

   cout << "Seed is set to: " << gRandom->GetSeed() << endl;
   
   cout << "Run Pseudo Experiments" << endl;
   
   timer_pe->Start();

   if( ! bayf )
     mymclimit->run_pseudoexperiments();
   
   cout << "=================================================================" << endl;
   cout << "Getting results" << endl;
   cout << "=================================================================" << endl;

   Double_t tsobs = mymclimit->ts();
   
   if( ! bayf )
     {	
	cout << "--------------------------Test Statistic for data --------------------" << endl; 
	cout << "ts: " << tsobs << endl;
	cout << "--------------------------Test Statistic: H0 Hypo ---------------------------------" << endl; 
	cout << "tsbm2: " << mymclimit->tsbm2() << endl;
	cout << "tsbm1: " << mymclimit->tsbm1() << endl;
	cout << "tsbmed: " << mymclimit->tsbmed() << endl;
	cout << "tsbp1: " << mymclimit->tsbp1() << endl;
	cout << "tsbp2: " << mymclimit->tsbp2() << endl;
	cout << "------------------------- Test Statistic: H1 Hypo ----------------------------------" << endl;
	cout << "tssm2: " << mymclimit->tssm2() << endl;
	cout << "tssm1: " << mymclimit->tssm1() << endl;
	cout << "tssmed: " << mymclimit->tssmed() << endl;
	cout << "tssp1: " << mymclimit->tssp1() << endl;
	cout << "tssp2: " << mymclimit->tssp2() << endl;
	cout << "--------------------------CL for data --------------------------------------" << endl;  
	cout << "CLb    (H0)            : " << mymclimit->clb() << endl;
	cout << "1-CLb (from p-value)  : " << mymclimit->omclb() << endl;
	cout << "1-CLsb (exclusion H1)  : " << 1-mymclimit->clsb() << endl;
	cout << "CLs~CLsb/CLs (LEP like): " << mymclimit->cls() << endl;
     }   

   if( ! bayf )
     {
	if( sigm == 0 || sigm == 666 )
	  cout << "CLs median  (bkg): " << mymclimit->clsexpbmed() << endl;
	if( sigm == -1 || sigm == 666 )
	  cout << "CLs median  (bkg): " << mymclimit->clsexpbp1() << endl;
	if( sigm == -2 || sigm == 666 )
	  cout << "CLs median  (bkg): " << mymclimit->clsexpbp2() << endl;
	if( sigm == 1 || sigm == 666 )
	  cout << "CLs median  (bkg): " << mymclimit->clsexpbm1() << endl;
	if( sigm == 2 || sigm == 666 )
	  cout << "CLs median  (bkg): " << mymclimit->clsexpbm2() << endl;

	cout << "-------------------------expected CLb in H0  (data point excluded) ---------------------------" << endl;
	
	cout << "1-CLb median  (bkg): " << 1.-mymclimit->clbexpbmed() << endl;
	cout << "1-CLb -2sigma (bkg): " << 1.-mymclimit->clbexpbm2() << endl;
	cout << "1-CLb -1sigma (bkg): " << 1.-mymclimit->clbexpbm1() << endl;
	cout << "1-CLb +1sigma (bkg): " << 1.-mymclimit->clbexpbp1() << endl;
	cout << "1-CLb +2sigma (bkg): " << 1.-mymclimit->clbexpbp2() << endl;
	
	cout << "-------------------------expected CLb in H0  (p-value)---------------------------" << endl;
	
	cout << "1-CLb median  (bkg): " << mymclimit->omclbexpbmed() << endl;
	cout << "1-CLb -2sigma (bkg): " << mymclimit->omclbexpbm2() << endl;
	cout << "1-CLb -1sigma (bkg): " << mymclimit->omclbexpbm1() << endl;
	cout << "1-CLb +1sigma (bkg): " << mymclimit->omclbexpbp1() << endl;
	cout << "1-CLb +2sigma (bkg): " << mymclimit->omclbexpbp2() << endl;
	   
	cout << "-------------------------expected CLb in H1  (data point excluded) ---------------------------" << endl;
	
	cout << "1-CLb median  (sig): " << 1.-mymclimit->clbexpsmed() << endl;
	cout << "1-CLb -2sigma (sig): " << 1.-mymclimit->clbexpsm2() << endl;
	cout << "1-CLb -1sigma (sig): " << 1.-mymclimit->clbexpsm1() << endl;
	cout << "1-CLb +1sigma (sig): " << 1.-mymclimit->clbexpsp1() << endl;
	cout << "1-CLb +2sigma (sig): " << 1.-mymclimit->clbexpsp2() << endl;
	
	cout << "-------------------------expected CLb in H1  (p-value)---------------------------" << endl;
	
	cout << "1-CLb median  (sig): " << mymclimit->omclbexpsmed() << endl;
	cout << "1-CLb -2sigma (sig): " << mymclimit->omclbexpsm2() << endl;
	cout << "1-CLb -1sigma (sig): " << mymclimit->omclbexpsm1() << endl;
	cout << "1-CLb +1sigma (sig): " << mymclimit->omclbexpsp1() << endl;
	cout << "1-CLb +2sigma (sig): " << mymclimit->omclbexpsp2() << endl;
     }
   
   timer_pe->Stop();

   TString f_out_name = "output.root";
   TFile f_out(f_out_name.Data(),"RECREATE");

   double b_in_b = 0.;
   double b_in_e = 1.;
   double b_in_s = 0.01;
   
   if( bayf )
     {	
	cout << "-------------------------Bayesian---------------------------" << endl;
   
//	PRIOR prior=flat; // corr or flat
	PRIOR prior; // corr or flat
	
	mymclimit->bayes_interval_begin = b_in_b;
	mymclimit->bayes_interval_end = b_in_e;
	mymclimit->bayes_interval_step = b_in_s;

	double bh=0.95;
	double sflimit;
	double unc;
	double sm2,sm1,smed,sp1,sp2;
	
	timer_bayesian->Start();

	if( bayf == 1 )
	  {	     
	     mymclimit->bayes_heinrich_withexpect(bh,&sflimit,&unc,npe,&sm2,&sm1,&smed,&sp1,&sp2);
	     
	     std::cout << "Expected Limit at: " << bh <<" % C.L "<< smed << " Full band: -2SD -1SD MED +1SD +2SD " << sm2 << " " << sm1 << " " << smed << " " << sp1 << " " << sp2 << std::endl;
	     std::cout << "Observed Limit at: " << bh <<" % C.L "<< sflimit << std::endl;
	  }	

	if( bayf == 2 )
	  {	     
	     // npe = number of Markov chains > 500 !
	     sflimit = mymclimit->bayeslimit_mcmc1(bh);

	     mymclimit->bayeslimit_mcmc1_expect(bh, prior, npe,
						&sm2, &sm1, &smed,
						&sp1, &sp2);


	     std::cout << "Expected Limit at: " << bh <<" % C.L "<< smed << " Full band: -2SD -1SD MED +1SD +2SD " << sm2 << " " << sm1 << " " << smed << " " << sp1 << " " << sp2 << std::endl;
	     std::cout << "Observed Limit at: " << bh <<" % C.L "<< sflimit << std::endl;
	  }		
	
	std::vector<Double_t> v_bayes_posterior = mymclimit->bayes_posterior;
	std::vector<Double_t> v_bayes_posterior_points = mymclimit->bayes_posterior_points;

	std::vector<Double_t>::const_iterator v_bayes_posterior_b = v_bayes_posterior.begin();
	std::vector<Double_t>::const_iterator v_bayes_posterior_e = v_bayes_posterior.end();
	
	double post_max = -666;
	for(;v_bayes_posterior_b!=v_bayes_posterior_e;++v_bayes_posterior_b)
	  {
	     if( (*v_bayes_posterior_b) > post_max )
	       post_max = (*v_bayes_posterior_b);
	  }	
	
	post_max += 0.3*post_max;
	
	TH2F *h_bayes_posterior = new TH2F("h_bayes_posterior","h_bayes_posterior",30,b_in_b,b_in_e,30,0.,post_max);
	
	for(int iv=0;iv<v_bayes_posterior.size();iv++)
	  {
	     h_bayes_posterior->Fill(v_bayes_posterior_points.at(iv), v_bayes_posterior.at(iv));
	  }	

	double xarr[100000];
	double yarr[100000];
	for(int iv=0;iv<v_bayes_posterior.size();iv++)
	  {
	     xarr[iv] = v_bayes_posterior_points.at(iv);
	     yarr[iv] = v_bayes_posterior.at(iv);
	  }	
	
	TGraph *gr_bayes_posterior = new TGraph(v_bayes_posterior.size(),xarr,yarr);
	gr_bayes_posterior->SetName("gr_bayes_posterior");
	gr_bayes_posterior->Write();
	
	mymclimit->run_pseudoexperiments();
	Double_t tsobs = mymclimit->ts();
	
	cout << "--------------------------Test Statistic for data --------------------" << endl; 
	cout << "ts: " << tsobs << endl;
	cout << "--------------------------Test Statistic: H0 Hypo ---------------------------------" << endl; 
	cout << "tsbm2: " << mymclimit->tsbm2() << endl;
	cout << "tsbm1: " << mymclimit->tsbm1() << endl;
	cout << "tsbmed: " << mymclimit->tsbmed() << endl;
	cout << "tsbp1: " << mymclimit->tsbp1() << endl;
	cout << "tsbp2: " << mymclimit->tsbp2() << endl;
	cout << "------------------------- Test Statistic: H1 Hypo ----------------------------------" << endl;
	cout << "tssm2: " << mymclimit->tssm2() << endl;
	cout << "tssm1: " << mymclimit->tssm1() << endl;
	cout << "tssmed: " << mymclimit->tssmed() << endl;
	cout << "tssp1: " << mymclimit->tssp1() << endl;
	cout << "tssp2: " << mymclimit->tssp2() << endl;
	cout << "--------------------------CL for data --------------------------------------" << endl;  
	cout << "CLb    (H0)            : " << mymclimit->clb() << endl;
	cout << "1-CLb (from p-value)  : " << mymclimit->omclb() << endl;
	cout << "1-CLsb (exclusion H1)  : " << 1-mymclimit->clsb() << endl;
	cout << "CLs~CLsb/CLs (LEP like): " << mymclimit->cls() << endl;

	timer_bayesian->Stop();
     }
   else if( ! doExp )
     {   	
	timer_cls->Start();
	
	cout << "----------------------------------  CLs @ 95% for  Limits  ----------------------------------" << endl;
	
	if( sigm == -3 || sigm == 666 ) cout << "s95 (Scale Factor on signal for exclusion at 95% CL exactly): " << mymclimit->s95() << endl;
	if( sigm == -4 || sigm == 666 ) cout << "lumi95 - Lumi needed for median exp to exclude at 95% CL (Multiplicative factor): " << mymclimit->lumi95() << endl;
	if( sigm == 0 || sigm == 666 ) cout << "s95med          : " << mymclimit->s95med() << endl;
	if( sigm == 2 || sigm == 666 ) cout << "s95p2 (+2sigma) : " << mymclimit->s95m2() << endl;
	if( sigm == 1 || sigm == 666 ) cout << "s95p1 (+1sigma) : " << mymclimit->s95m1() << endl;
	if( sigm == -1 || sigm == 666 ) cout << "s95m1 (-1sigma) : " << mymclimit->s95p1() << endl;
	if( sigm == -2 || sigm == 666 ) cout << "s95m2 (-2sigma) : " << mymclimit->s95p2() << endl;
	
	timer_cls->Stop();   
     }	
	
   std::cout << "Run time for pseudo-experiments: " << getruntime(timer_pe) << " sec" << std::endl;
   if( bayf ) std::cout << "Run time for Bayesian: " << getruntime(timer_bayesian) << " sec" << std::endl;
   std::cout << "Run time for CLs: " << getruntime(timer_cls) << " sec" << std::endl;
   
   delete mymclimit;
}

double getruntime(TStopwatch* timer)
{
   double realTime = timer->RealTime();
   
   int hours = int(realTime / 3600);
   realTime -= hours * 3600;
   int min   = int(realTime / 60);
   realTime -= min * 60;
   int sec   = int(realTime);
   float totTime = hours*60*60+min*60+sec;
   
   return totTime;   
}
