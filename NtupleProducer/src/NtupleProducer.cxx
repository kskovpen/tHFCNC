#include "../include/NtupleProducer.h"

#include "Riostream.h"
#include "TSystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <assert.h>

void readPU();

Tree *ntP;
TChain *ch;
Ntuple *nt;
std::vector<int> *evdebug;
int _isdata;

BTagCalibration *calib;
BTagCalibrationReader *reader_iterativefit;

JetCorrectionUncertainty *jesTotal;

JME::JetResolution *jer;

TRandom3 *rnd;

double cJER[13];
double cJER_down[13];
double cJER_up[13];

TFile* _fpuNom;
TFile* _fpuUp;
TFile* _fpuDown;

TH1D* _hpuNom;
TH1D* _hpuUp;
TH1D* _hpuDown;

TFile* _fegammaID;
TH2F* _hegammaID;

EffectiveAreas* effectiveAreas_;

unsigned int idx;

double _weights[75];
double _weightsUp[75];
double _weightsDown[75];

int main(int argc, char *argv[])
{
   if( argc < 4 )
     {
	std::cout << "NtupleProducer usage:" << std::endl;
	std::cout << "--file: input filename" << std::endl;
	std::cout << "--tree: TTree name" << std::endl;
	std::cout << "--noe : Number of events" << std::endl;
	std::cout << "--xsec: Cross-section" << std::endl;
	std::cout << "--nmax: Max number of events" << std::endl;
	std::cout << "--outfile: output file" << std::endl;
	std::cout << "--isdata: is data flag" << std::endl;
	std::cout << "--stream: data stream" << std::endl;
	std::cout << "--issig: is signal" << std::endl;
	std::cout << "--isttbar: is ttbar" << std::endl;
	exit(1);
     }
   
   const char *fname_str = "output.root";
   const char *stream_str = "FlatTree/tree";
   float noe = 1.;
   float xsec = 1.;
   int nmax = -1;
   const char *outfile_str = "666";
   _isdata = 0;
   int dataStream = -1;
   int issig = 0;
   int isttbar = 0;
   
   for(int i=0;i<argc;i++)
     {
	if( ! strcmp(argv[i],"--file") ) fname_str = argv[i+1];
	if( ! strcmp(argv[i],"--tree") ) stream_str = argv[i+1];
	if( ! strcmp(argv[i],"--noe") ) noe = atof(argv[i+1]);
	if( ! strcmp(argv[i],"--xsec") ) xsec = atof(argv[i+1]);
	if( ! strcmp(argv[i],"--nmax") ) nmax = atoi(argv[i+1]);
	if( ! strcmp(argv[i],"--outfile") ) outfile_str = argv[i+1];
	if( ! strcmp(argv[i],"--isdata") ) _isdata = atoi(argv[i+1]);
	if( ! strcmp(argv[i],"--stream") ) dataStream = atoi(argv[i+1]);
	if( ! strcmp(argv[i],"--issig") ) issig = atoi(argv[i+1]);
	if( ! strcmp(argv[i],"--isttbar") ) isttbar = atoi(argv[i+1]);
     }   

   const char *fname  = fname_str;
   const char *stream = stream_str;
   const char *outfile = outfile_str;
   
   std::cout << "--file=" << fname << std::endl;
   std::cout << "--tree=" << stream << std::endl;
   std::cout << "--noe=" << noe << std::endl;
   std::cout << "--xsec=" << xsec << std::endl;
   std::cout << "--nmax=" << nmax << std::endl;
   std::cout << "--outfile=" << outfile << std::endl;
   std::cout << "--isdata=" << _isdata << std::endl;
   std::cout << "--stream=" << dataStream << std::endl;
   std::cout << "--issig=" << issig << std::endl;
   std::cout << "--isttbar=" << isttbar << std::endl;

   std::cout << fname << std::endl;
   Tree tree(0,const_cast<char*>(fname),stream);
   ntP = &tree;
   
   ch = tree.fChain;
   Long64_t nentries = ch->GetEntries();
   ntP->registerInputBranches(ch);
   
   nt = new Ntuple();

   nt->Init(std::string(outfile));
   nt->createVar();
   nt->setBranchAddress();

   Electron el;
   Muon mu;
   Jet jet;
   Event ev;
   Truth truth;

   calib = new BTagCalibration("csvv2","/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/tHFCNC/NtupleProducer/test/CSVv2Moriond17_2017_1_26_BtoH.csv");
   reader_iterativefit = new BTagCalibrationReader(BTagEntry::OP_RESHAPING,"central",
						   {"up_jes","down_jes","up_lf","down_lf",
							"up_hf","down_hf",
							"up_hfstats1","down_hfstats1",
							"up_hfstats2","down_hfstats2",
							"up_lfstats1","down_lfstats1",
							"up_lfstats2","down_lfstats2",
							"up_cferr1","down_cferr1",
							"up_cferr2","down_cferr2"});
   reader_iterativefit->load(*calib,BTagEntry::FLAV_B,"iterativefit");
   reader_iterativefit->load(*calib,BTagEntry::FLAV_C,"iterativefit");
   reader_iterativefit->load(*calib,BTagEntry::FLAV_UDSG,"iterativefit");

   std::cout << "BTagCalibration initialized" << std::endl;

   jesTotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters("/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/tHFCNC/NtupleProducer/test/Summer16_23Sep2016V3_MC/Summer16_23Sep2016V3_MC_Uncertainty_AK4PFchs.txt")));
   
   jer = new JME::JetResolution("/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/tHFCNC/NtupleProducer/test/Spring16_25nsV6_MC_PtResolution_AK4PFchs.txt");
   
   effectiveAreas_ = new EffectiveAreas("/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/RecoEgamma/ElectronIdentification/data/Summer16/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_80X.txt");
   
   rnd = new TRandom3();

   cJER[0] = 1.122; // 0.0-0.5
   cJER[1] = 1.167; // 0.5-0.8
   cJER[2] = 1.168; // 0.8-1.1
   cJER[3] = 1.029; // 1.1-1.3
   cJER[4] = 1.115; // 1.3-1.7
   cJER[5] = 1.041; // 1.7-1.9
   cJER[6] = 1.167; // 1.9-2.1
   cJER[7] = 1.094; // 2.1-2.3
   cJER[8] = 1.168; // 2.3-2.5
   cJER[9] = 1.266; // 2.5-2.8
   cJER[10] = 1.595; // 2.8-3.0
   cJER[11] = 0.998; // 3.0-3.2
   cJER[12] = 1.226; // 3.2-5.0

   cJER_down[0] = 1.096;
   cJER_down[1] = 1.119;
   cJER_down[2] = 1.122;
   cJER_down[3] = 0.963;
   cJER_down[4] = 1.085;
   cJER_down[5] = 0.979;
   cJER_down[6] = 1.081;
   cJER_down[7] = 1.001;
   cJER_down[8] = 1.048;
   cJER_down[9] = 1.134;
   cJER_down[10] = 1.420;
   cJER_down[11] = 0.932;
   cJER_down[12] = 1.081;

   cJER_up[0] = 1.148;
   cJER_up[1] = 1.215;
   cJER_up[2] = 1.214;
   cJER_up[3] = 1.095;
   cJER_up[4] = 1.145;
   cJER_up[5] = 1.103;
   cJER_up[6] = 1.253;
   cJER_up[7] = 1.187;
   cJER_up[8] = 1.288;
   cJER_up[9] = 1.398;
   cJER_up[10] = 1.770;
   cJER_up[11] = 1.064;
   cJER_up[12] = 1.371;

   if( !_isdata )
     {	   
	std::string puNom = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/tHFCNC/NtupleProducer/test/Pileup.root";
	std::string puUp = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/tHFCNC/NtupleProducer/test/PileupUp.root";
	std::string puDown = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/tHFCNC/NtupleProducer/test/PileupDown.root";
	
	_fpuNom = TFile::Open(puNom.c_str(),"READ");
	_fpuUp = TFile::Open(puUp.c_str(),"READ");
	_fpuDown = TFile::Open(puDown.c_str(),"READ");
	
	_fpuNom->GetObject("pileup",_hpuNom);
	_fpuUp->GetObject("pileup",_hpuUp);
	_fpuDown->GetObject("pileup",_hpuDown);

	readPU();
   
	std::string egID = "/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/tHFCNC/NtupleProducer/test/egammaEffi_MediumCB_SF2D.root";
	_fegammaID = TFile::Open(egID.c_str(),"READ");
	
	_fegammaID->GetObject("EGamma_SF2D",_hegammaID);
     }   
   
   evdebug = new std::vector<int>();
   evdebug->push_back(4465955);
   
   std::cout << "Input events = " << nentries << std::endl;
   
   for(Long64_t i=0;i<nentries;i++)
     {
//	std::cout << i << std::endl;
	if( nmax >= 0 && i >= nmax ) break;
	
	ch->GetEntry(i);

	nt->clearVar();	
	
	// event
	ev.init();
	ev.read(xsec,noe,dataStream,issig,isttbar);
	
	nt->NtEvent->push_back(ev);
	
	// muons
	for(int j=0;j<ntP->mu_n;j++)
	  {
	     idx = j;
	     
	     mu.init();
	     mu.read();
	     mu.sel();
	
	     if( mu.isTight() ) nt->NtMuonTight->push_back(mu);	     
	     else if( mu.isLoose() ) nt->NtMuonLoose->push_back(mu);	     
	  }		

	// electrons
	for(int j=0;j<ntP->el_n;j++)
	  {
	     idx = j;
	     
	     el.init();
	     el.read();
	     el.sel();

	     if( el.isTight() ) nt->NtElectronTight->push_back(el);	     
	     else if( el.isLoose() ) nt->NtElectronLoose->push_back(el);
	  }

	// jets
	for(int j=0;j<ntP->jet_n;j++)
	  {
	     idx = j;
	     
	     jet.init();
	     jet.read();
	     jet.sel();

	     if( jet.isTight() ) nt->NtJetTight->push_back(jet);
	     else if( jet.isLoose() ) nt->NtJetLoose->push_back(jet);
	     
	     if( jet.isTight() && jet.isBTag() ) nt->NtBJetTight->push_back(jet);
	  }

	if( !_isdata )
	  {	     
	     // truth
	     truth.init();
	     truth.read();
	     
	     nt->NtTruth->push_back(truth);
	  }	

	int nElecLoose = nt->NtElectronLoose->size();
	int nMuonLoose = nt->NtMuonLoose->size();
	
	int nElecTight = nt->NtElectronTight->size();
	int nMuonTight = nt->NtMuonTight->size();

	int nJetLoose = nt->NtJetLoose->size();
	int nJetTight = nt->NtJetTight->size();
	int nJetBTag = nt->NtBJetTight->size();

	if(
	   ((nElecTight == 1 && nMuonLoose+nMuonTight == 0 && nElecLoose == 0) ||
	       (nMuonTight == 1 && nElecLoose+nElecTight == 0 && nMuonLoose == 0)) &&
	   (nJetLoose+nJetTight) >= 3 && nJetBTag >= 2
	  ) // main analysis
/*	if(
	   ((nElecTight == 1 && nMuonLoose+nMuonTight == 0 && nElecLoose == 0) ||
	       (nMuonTight == 1 && nElecLoose+nElecTight == 0 && nMuonLoose == 0)) &&
	   (nJetLoose+nJetTight) >= 3
	  ) // TopKinFit*/
	  {
	     nt->fill();
	  }
     }
   
   std::cout << "Output events = " << nt->m_tree->GetEntries() << std::endl;

   if( !_isdata )
     {	
	_fpuNom->Close();
	_fpuUp->Close();
	_fpuDown->Close();
	
	_fegammaID->Close();
     }   

   delete jer;
   delete jesTotal;
   delete rnd;

   delete nt;
}

void readPU()
{
   // https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_X/SimGeneral/MixingModule/python/mix_2016_25ns_Moriond17MC_PoissonOOTPU_cfi.py

   double npuSummer16_25ns[75] =
     {
	1.78653e-05,
	2.56602e-05,
	5.27857e-05,
	8.88954e-05,
	0.000109362,
	0.000140973,
	0.000240998,
	0.00071209,
	0.00130121,
	0.00245255,
	0.00502589,
	0.00919534,
	0.0146697,
	0.0204126,
	0.0267586,
	0.0337697,
	0.0401478,
	0.0450159,
	0.0490577,
	0.0524855,
	0.0548159,
	0.0559937,
	0.0554468,
	0.0537687,
	0.0512055,
	0.0476713,
	0.0435312,
	0.0393107,
	0.0349812,
	0.0307413,
	0.0272425,
	0.0237115,
	0.0208329,
	0.0182459,
	0.0160712,
	0.0142498,
	0.012804,
	0.011571,
	0.010547,
	0.00959489,
	0.00891718,
	0.00829292,
	0.0076195,
	0.0069806,
	0.0062025,
	0.00546581,
	0.00484127,
	0.00407168,
	0.00337681,
	0.00269893,
	0.00212473,
	0.00160208,
	0.00117884,
	0.000859662,
	0.000569085,
	0.000365431,
	0.000243565,
	0.00015688,
	9.88128e-05,
	6.53783e-05,
	3.73924e-05,
	2.61382e-05,
	2.0307e-05,
	1.73032e-05,
	1.435e-05,
	1.36486e-05,
	1.35555e-05,
	1.37491e-05,
	1.34255e-05,
	1.33987e-05,
	1.34061e-05,
	1.34211e-05,
	1.34177e-05,
	1.32959e-05,
	1.33287e-05
     };

   double tot = 0;
   double totUp = 0;
   double totDown = 0;
   for(unsigned int npu=0;npu<75;++npu)
     {	
	const double npuEst = _hpuNom->GetBinContent(_hpuNom->GetXaxis()->FindBin(npu));
	_weights[npu] = (npuSummer16_25ns[npu]) ? npuEst / npuSummer16_25ns[npu] : 0.;
	tot += npuEst;

	const double npuEstUp = _hpuUp->GetBinContent(_hpuUp->GetXaxis()->FindBin(npu));
	_weightsUp[npu] = (npuSummer16_25ns[npu]) ? npuEstUp / npuSummer16_25ns[npu] : 0.;
	totUp += npuEstUp;

	const double npuEstDown = _hpuDown->GetBinContent(_hpuDown->GetXaxis()->FindBin(npu));
	_weightsDown[npu] = (npuSummer16_25ns[npu]) ? npuEstDown / npuSummer16_25ns[npu] : 0.;
	totDown += npuEstDown;
     }

   for(unsigned int npu=0;npu<75;++npu)
     {
	_weights[npu] /= tot;
	_weightsUp[npu] /= totUp;
	_weightsDown[npu] /= totDown;
     }
}
