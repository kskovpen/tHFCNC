#include "../include/Hist.h"
#include "../include/ApplyMVA.h"

char *fin;
char *flog;
//char *runmode;
char *tool;
std::string home;
int nmax;
bool evec;
//int lept;
//int lepm;
//int imfake;
TTree *tr;

int main(int argc, char *argv[])
{
   if( argc < 7 )
     {
	std::cout << "Usage: ./Analyzer [input file] [log file] [tool] [nmax] [home] [evec]" << std::endl;
	exit(1);
     }   
   
   fin = argv[1];
   flog = argv[2];
   tool = argv[3];
   nmax = atoi(argv[4]);
   home = std::string(argv[5]);
   evec = atoi(argv[6]);
   
   TChain f("Nt");
   
//	std::stringstream fnamev(fin);

   std::ifstream infile;
   infile.open(fin);
   
   std::string ifile = "";
   while( getline(infile, ifile) )
     //	while( getline(fnamev, ifile, '@') )
     {
	std::cout << ifile.c_str() << std::endl;
	f.Add(ifile.c_str());
     }	
   
   infile.close();

   std::vector<Electron>             *v_ElectronTight             = new std::vector<Electron>();
   std::vector<Electron>             *v_ElectronLoose             = new std::vector<Electron>();
   std::vector<Muon>                 *v_MuonTight                 = new std::vector<Muon>();
   std::vector<Muon>                 *v_MuonLoose                 = new std::vector<Muon>();
   std::vector<Event>                 *v_Event                 = new std::vector<Event>();
   std::vector<Jet>                 *v_Jet                 = new std::vector<Jet>();
   std::vector<Truth>                 *v_Truth                 = new std::vector<Truth>();
   
   f.SetBranchAddress("ElectronTight", &v_ElectronTight);
   f.SetBranchAddress("ElectronLoose", &v_ElectronLoose);
   f.SetBranchAddress("MuonTight", &v_MuonTight);
   f.SetBranchAddress("MuonLoose", &v_MuonLoose);
   f.SetBranchAddress("Jet", &v_Jet);
   f.SetBranchAddress("Event", &v_Event);
   f.SetBranchAddress("Truth", &v_Truth);

   int nent = f.GetEntries();
   std::cout << nent << std::endl;
   
/*   SKYPLOT::FakeWeight fakeWeight;
   if( strcmp(tool,"realeff") != 0 &&
       strcmp(tool,"fakerate") != 0 )
     {		
	std::cout << "Read real efficiencies" << std::endl;
	fakeWeight.readRealEff();
	std::cout << "Read fake rate" << std::endl;
	fakeWeight.readFakeRate();
     }   
  */ 
   std::cout << "Analyzer initialisation done" << std::endl;
   
   if( strcmp(tool,"plot") == 0 )
     {		
	Hist hist(home,evec);
	
	hist.setElectronTight(v_ElectronTight);
	hist.setElectronLoose(v_ElectronLoose);
	hist.setMuonTight(v_MuonTight);
	hist.setMuonLoose(v_MuonLoose);
	hist.setEvent(v_Event);
	hist.setJet(v_Jet);
	hist.setTruth(v_Truth);
//	hist.setFakeWeight(fakeWeight);
	hist.init();

	for(int i=0;i<nent;i++)
	  {
	     if( nmax >= 0 && i > nmax ) break;
	     
	     f.GetEntry(i);
	     
	     std::string fcur = f.GetCurrentFile()->GetName();

	     hist.fill();
	  }   
	
	hist.close();
     }
/*   else if( strcmp(tool,"misid") == 0 )
     {		
	SKYPLOT::ChargeMisid misid;
	
	misid.init();
	misid.setEvent(v_Event);
	misid.setElectron(v_Electron);
	misid.setMuon(v_Muon);
//	misid.setTau(v_Tau);
	misid.setJet(v_Jet);
	
	for(int i=0;i<nent;i++)
	  {	
	     f.GetEntry(i);
	     
	     misid.run();
	  }   
	
	misid.close();
     }   
   else if( strcmp(tool,"realeff") == 0 )
     {		
	SKYPLOT::RealEff realeff;
	
	realeff.init();
	realeff.setEvent(v_Event);
	realeff.setElectron(v_Electron);
	realeff.setMuon(v_Muon);
	realeff.setJet(v_Jet);
	
	for(int i=0;i<nent;i++)
	  {	
	     f.GetEntry(i);
	     
	     realeff.run();
	  }   
	
	realeff.close();
     }   
   else if( strcmp(tool,"fakerate") == 0 )
     {		
	SKYPLOT::FakeRate fakerate;
	
	fakerate.init();
	fakerate.setEvent(v_Event);
	fakerate.setElectron(v_Electron);
	fakerate.setMuon(v_Muon);
//	fakerate.setTau(v_Tau);
	fakerate.setJet(v_Jet);
	fakerate.setMet(v_Met);
	
	for(int i=0;i<nent;i++)
	  {	
	     f.GetEntry(i);
	     
	     fakerate.run();
	  }   
	
	fakerate.close();
     }   
   else if( strcmp(tool,"fakepred") == 0 )
     {		
	SKYPLOT::FakePred fakepred;
	
	fakepred.init();
	fakepred.setEvent(v_Event);
	fakepred.setElectron(v_Electron);
	fakepred.setMuon(v_Muon);
//	fakepred.setTau(v_Tau);
	fakepred.setJet(v_Jet);
	
	for(int i=0;i<nent;i++)
	  {	
	     f.GetEntry(i);
	     
	     fakepred.run();
	  }   
	
	fakepred.close();
     }   
   else if( strcmp(tool,"fakecr") == 0 )
     {		
	SKYPLOT::FakeCR fakecr;
	
	fakecr.init();
	fakecr.setEvent(v_Event);
	fakecr.setElectron(v_Electron);
	fakecr.setMuon(v_Muon);
	fakecr.setJet(v_Jet);
	fakecr.setMet(v_Met);
	
	for(int i=0;i<nent;i++)
	  {	
	     f.GetEntry(i);
	     
	     fakecr.fill();
	  }   
	
	fakecr.close();
     }*/
   else
     {
	std::cout << "Select a proper tool" << std::endl;
	exit(1);
     }   

}
