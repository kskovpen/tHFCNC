#ifndef TOPRECO_H
#define TOPRECO_H

#include "Analyzer.h"

#include "Helper.h"

#include "kinfit.h"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

class TopReco
{
   
 public:

   TopReco();
   virtual ~TopReco();
   
   void setElectron(std::vector<Electron> *v)                {_v_Electron = v;};
   void setMuon(std::vector<Muon> *v)                        {_v_Muon = v;};
   void setJet(std::vector<Jet> *v)                          {_v_Jet = v;};
   void setBJet(std::vector<Jet> *v)                         {_v_BJet = v;};
   void setNonBJet(std::vector<Jet> *v)                      {_v_NonBJet = v;};
   void setEvent(std::vector<Event> *v)                      {_v_Event = v;};
   void setLepton(std::vector<Lepton> *v)                    {_v_Lepton = v;};
	
   void init();
   void run();
   void close();

   // nominal
   TLorentzVector TopLepBJet_TOPTOPLEPHBB_p4()      {return _TopLepBJet_TOPTOPLEPHBB_p4;};
   TLorentzVector HiggsBJet1_TOPTOPLEPHBB_p4()      {return _HiggsBJet1_TOPTOPLEPHBB_p4;};
   TLorentzVector HiggsBJet2_TOPTOPLEPHBB_p4()      {return _HiggsBJet2_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLepWLep_TOPTOPLEPHBB_p4()      {return _TopLepWLep_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLepWNu_TOPTOPLEPHBB_p4()       {return _TopLepWNu_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLep_TOPTOPLEPHBB_p4()          {return _TopLep_TOPTOPLEPHBB_p4;};
   TLorentzVector Higgs_TOPTOPLEPHBB_p4()           {return _Higgs_TOPTOPLEPHBB_p4;};
   TLorentzVector TopLepW_TOPTOPLEPHBB_p4()         {return _TopLepW_TOPTOPLEPHBB_p4;};
   TLorentzVector TopHadNonBJet_TOPTOPLEPHBB_p4()   {return _TopHadNonBJet_TOPTOPLEPHBB_p4;};

   TLorentzVector TopLepBJet_TOPHLEPBB_p4()      {return _TopLepBJet_TOPHLEPBB_p4;};
   TLorentzVector HiggsBJet1_TOPHLEPBB_p4()      {return _HiggsBJet1_TOPHLEPBB_p4;};
   TLorentzVector HiggsBJet2_TOPHLEPBB_p4()      {return _HiggsBJet2_TOPHLEPBB_p4;};
   TLorentzVector TopLepWLep_TOPHLEPBB_p4()      {return _TopLepWLep_TOPHLEPBB_p4;};
   TLorentzVector TopLepWNu_TOPHLEPBB_p4()       {return _TopLepWNu_TOPHLEPBB_p4;};
   TLorentzVector TopLep_TOPHLEPBB_p4()          {return _TopLep_TOPHLEPBB_p4;};
   TLorentzVector Higgs_TOPHLEPBB_p4()           {return _Higgs_TOPHLEPBB_p4;};
   TLorentzVector TopLepW_TOPHLEPBB_p4()         {return _TopLepW_TOPHLEPBB_p4;};

   TLorentzVector TopLepBJet_TOPTOPLEPHAD_p4()        {return _TopLepBJet_TOPTOPLEPHAD_p4;};
   TLorentzVector TopHadWNonBJet1_TOPTOPLEPHAD_p4()   {return _TopHadWNonBJet1_TOPTOPLEPHAD_p4;};
   TLorentzVector TopHadWNonBJet2_TOPTOPLEPHAD_p4()   {return _TopHadWNonBJet2_TOPTOPLEPHAD_p4;};
   TLorentzVector TopLepWLep_TOPTOPLEPHAD_p4()        {return _TopLepWLep_TOPTOPLEPHAD_p4;};
   TLorentzVector TopLepWNu_TOPTOPLEPHAD_p4()         {return _TopLepWNu_TOPTOPLEPHAD_p4;};
   TLorentzVector TopLep_TOPTOPLEPHAD_p4()            {return _TopLep_TOPTOPLEPHAD_p4;};
   TLorentzVector TopHad_TOPTOPLEPHAD_p4()            {return _TopHad_TOPTOPLEPHAD_p4;};
   TLorentzVector TopHadW_TOPTOPLEPHAD_p4()           {return _TopHadW_TOPTOPLEPHAD_p4;};
   TLorentzVector TopLepW_TOPTOPLEPHAD_p4()           {return _TopLepW_TOPTOPLEPHAD_p4;};
   TLorentzVector TopHadBJet_TOPTOPLEPHAD_p4()        {return _TopHadBJet_TOPTOPLEPHAD_p4;};

   // JesUp
   TLorentzVector TopLepBJet_TOPTOPLEPHBB_JesUp_p4()      {return _TopLepBJet_TOPTOPLEPHBB_JesUp_p4;};
   TLorentzVector HiggsBJet1_TOPTOPLEPHBB_JesUp_p4()      {return _HiggsBJet1_TOPTOPLEPHBB_JesUp_p4;};
   TLorentzVector HiggsBJet2_TOPTOPLEPHBB_JesUp_p4()      {return _HiggsBJet2_TOPTOPLEPHBB_JesUp_p4;};
   TLorentzVector TopLep_TOPTOPLEPHBB_JesUp_p4()          {return _TopLep_TOPTOPLEPHBB_JesUp_p4;};
   TLorentzVector Higgs_TOPTOPLEPHBB_JesUp_p4()           {return _Higgs_TOPTOPLEPHBB_JesUp_p4;};
   TLorentzVector TopHadNonBJet_TOPTOPLEPHBB_JesUp_p4()   {return _TopHadNonBJet_TOPTOPLEPHBB_JesUp_p4;};

   TLorentzVector TopLepBJet_TOPHLEPBB_JesUp_p4()      {return _TopLepBJet_TOPHLEPBB_JesUp_p4;};
   TLorentzVector HiggsBJet1_TOPHLEPBB_JesUp_p4()      {return _HiggsBJet1_TOPHLEPBB_JesUp_p4;};
   TLorentzVector HiggsBJet2_TOPHLEPBB_JesUp_p4()      {return _HiggsBJet2_TOPHLEPBB_JesUp_p4;};
   TLorentzVector TopLep_TOPHLEPBB_JesUp_p4()          {return _TopLep_TOPHLEPBB_JesUp_p4;};
   TLorentzVector Higgs_TOPHLEPBB_JesUp_p4()           {return _Higgs_TOPHLEPBB_JesUp_p4;};

   TLorentzVector TopLepBJet_TOPTOPLEPHAD_JesUp_p4()        {return _TopLepBJet_TOPTOPLEPHAD_JesUp_p4;};
   TLorentzVector TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4()   {return _TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4;};
   TLorentzVector TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4()   {return _TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4;};
   TLorentzVector TopLep_TOPTOPLEPHAD_JesUp_p4()            {return _TopLep_TOPTOPLEPHAD_JesUp_p4;};
   TLorentzVector TopHad_TOPTOPLEPHAD_JesUp_p4()            {return _TopHad_TOPTOPLEPHAD_JesUp_p4;};
   TLorentzVector TopHadW_TOPTOPLEPHAD_JesUp_p4()           {return _TopHadW_TOPTOPLEPHAD_JesUp_p4;};
   TLorentzVector TopHadBJet_TOPTOPLEPHAD_JesUp_p4()        {return _TopHadBJet_TOPTOPLEPHAD_JesUp_p4;};

   // JesDown
   TLorentzVector TopLepBJet_TOPTOPLEPHBB_JesDown_p4()      {return _TopLepBJet_TOPTOPLEPHBB_JesDown_p4;};
   TLorentzVector HiggsBJet1_TOPTOPLEPHBB_JesDown_p4()      {return _HiggsBJet1_TOPTOPLEPHBB_JesDown_p4;};
   TLorentzVector HiggsBJet2_TOPTOPLEPHBB_JesDown_p4()      {return _HiggsBJet2_TOPTOPLEPHBB_JesDown_p4;};
   TLorentzVector TopLep_TOPTOPLEPHBB_JesDown_p4()          {return _TopLep_TOPTOPLEPHBB_JesDown_p4;};
   TLorentzVector Higgs_TOPTOPLEPHBB_JesDown_p4()           {return _Higgs_TOPTOPLEPHBB_JesDown_p4;};
   TLorentzVector TopHadNonBJet_TOPTOPLEPHBB_JesDown_p4()   {return _TopHadNonBJet_TOPTOPLEPHBB_JesDown_p4;};

   TLorentzVector TopLepBJet_TOPHLEPBB_JesDown_p4()      {return _TopLepBJet_TOPHLEPBB_JesDown_p4;};
   TLorentzVector HiggsBJet1_TOPHLEPBB_JesDown_p4()      {return _HiggsBJet1_TOPHLEPBB_JesDown_p4;};
   TLorentzVector HiggsBJet2_TOPHLEPBB_JesDown_p4()      {return _HiggsBJet2_TOPHLEPBB_JesDown_p4;};
   TLorentzVector TopLep_TOPHLEPBB_JesDown_p4()          {return _TopLep_TOPHLEPBB_JesDown_p4;};
   TLorentzVector Higgs_TOPHLEPBB_JesDown_p4()           {return _Higgs_TOPHLEPBB_JesDown_p4;};

   TLorentzVector TopLepBJet_TOPTOPLEPHAD_JesDown_p4()        {return _TopLepBJet_TOPTOPLEPHAD_JesDown_p4;};
   TLorentzVector TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4()   {return _TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4;};
   TLorentzVector TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4()   {return _TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4;};
   TLorentzVector TopLep_TOPTOPLEPHAD_JesDown_p4()            {return _TopLep_TOPTOPLEPHAD_JesDown_p4;};
   TLorentzVector TopHad_TOPTOPLEPHAD_JesDown_p4()            {return _TopHad_TOPTOPLEPHAD_JesDown_p4;};
   TLorentzVector TopHadW_TOPTOPLEPHAD_JesDown_p4()           {return _TopHadW_TOPTOPLEPHAD_JesDown_p4;};
   TLorentzVector TopHadBJet_TOPTOPLEPHAD_JesDown_p4()        {return _TopHadBJet_TOPTOPLEPHAD_JesDown_p4;};

   // JerUp
   TLorentzVector TopLepBJet_TOPTOPLEPHBB_JerUp_p4()      {return _TopLepBJet_TOPTOPLEPHBB_JerUp_p4;};
   TLorentzVector HiggsBJet1_TOPTOPLEPHBB_JerUp_p4()      {return _HiggsBJet1_TOPTOPLEPHBB_JerUp_p4;};
   TLorentzVector HiggsBJet2_TOPTOPLEPHBB_JerUp_p4()      {return _HiggsBJet2_TOPTOPLEPHBB_JerUp_p4;};
   TLorentzVector TopLep_TOPTOPLEPHBB_JerUp_p4()          {return _TopLep_TOPTOPLEPHBB_JerUp_p4;};
   TLorentzVector Higgs_TOPTOPLEPHBB_JerUp_p4()           {return _Higgs_TOPTOPLEPHBB_JerUp_p4;};
   TLorentzVector TopHadNonBJet_TOPTOPLEPHBB_JerUp_p4()   {return _TopHadNonBJet_TOPTOPLEPHBB_JerUp_p4;};

   TLorentzVector TopLepBJet_TOPHLEPBB_JerUp_p4()      {return _TopLepBJet_TOPHLEPBB_JerUp_p4;};
   TLorentzVector HiggsBJet1_TOPHLEPBB_JerUp_p4()      {return _HiggsBJet1_TOPHLEPBB_JerUp_p4;};
   TLorentzVector HiggsBJet2_TOPHLEPBB_JerUp_p4()      {return _HiggsBJet2_TOPHLEPBB_JerUp_p4;};
   TLorentzVector TopLep_TOPHLEPBB_JerUp_p4()          {return _TopLep_TOPHLEPBB_JerUp_p4;};
   TLorentzVector Higgs_TOPHLEPBB_JerUp_p4()           {return _Higgs_TOPHLEPBB_JerUp_p4;};

   TLorentzVector TopLepBJet_TOPTOPLEPHAD_JerUp_p4()        {return _TopLepBJet_TOPTOPLEPHAD_JerUp_p4;};
   TLorentzVector TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4()   {return _TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4;};
   TLorentzVector TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4()   {return _TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4;};
   TLorentzVector TopLep_TOPTOPLEPHAD_JerUp_p4()            {return _TopLep_TOPTOPLEPHAD_JerUp_p4;};
   TLorentzVector TopHad_TOPTOPLEPHAD_JerUp_p4()            {return _TopHad_TOPTOPLEPHAD_JerUp_p4;};
   TLorentzVector TopHadW_TOPTOPLEPHAD_JerUp_p4()           {return _TopHadW_TOPTOPLEPHAD_JerUp_p4;};
   TLorentzVector TopHadBJet_TOPTOPLEPHAD_JerUp_p4()        {return _TopHadBJet_TOPTOPLEPHAD_JerUp_p4;};

   // JerDown
   TLorentzVector TopLepBJet_TOPTOPLEPHBB_JerDown_p4()      {return _TopLepBJet_TOPTOPLEPHBB_JerDown_p4;};
   TLorentzVector HiggsBJet1_TOPTOPLEPHBB_JerDown_p4()      {return _HiggsBJet1_TOPTOPLEPHBB_JerDown_p4;};
   TLorentzVector HiggsBJet2_TOPTOPLEPHBB_JerDown_p4()      {return _HiggsBJet2_TOPTOPLEPHBB_JerDown_p4;};
   TLorentzVector TopLep_TOPTOPLEPHBB_JerDown_p4()          {return _TopLep_TOPTOPLEPHBB_JerDown_p4;};
   TLorentzVector Higgs_TOPTOPLEPHBB_JerDown_p4()           {return _Higgs_TOPTOPLEPHBB_JerDown_p4;};
   TLorentzVector TopHadNonBJet_TOPTOPLEPHBB_JerDown_p4()   {return _TopHadNonBJet_TOPTOPLEPHBB_JerDown_p4;};

   TLorentzVector TopLepBJet_TOPHLEPBB_JerDown_p4()      {return _TopLepBJet_TOPHLEPBB_JerDown_p4;};
   TLorentzVector HiggsBJet1_TOPHLEPBB_JerDown_p4()      {return _HiggsBJet1_TOPHLEPBB_JerDown_p4;};
   TLorentzVector HiggsBJet2_TOPHLEPBB_JerDown_p4()      {return _HiggsBJet2_TOPHLEPBB_JerDown_p4;};
   TLorentzVector TopLep_TOPHLEPBB_JerDown_p4()          {return _TopLep_TOPHLEPBB_JerDown_p4;};
   TLorentzVector Higgs_TOPHLEPBB_JerDown_p4()           {return _Higgs_TOPHLEPBB_JerDown_p4;};

   TLorentzVector TopLepBJet_TOPTOPLEPHAD_JerDown_p4()        {return _TopLepBJet_TOPTOPLEPHAD_JerDown_p4;};
   TLorentzVector TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4()   {return _TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4;};
   TLorentzVector TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4()   {return _TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4;};
   TLorentzVector TopLep_TOPTOPLEPHAD_JerDown_p4()            {return _TopLep_TOPTOPLEPHAD_JerDown_p4;};
   TLorentzVector TopHad_TOPTOPLEPHAD_JerDown_p4()            {return _TopHad_TOPTOPLEPHAD_JerDown_p4;};
   TLorentzVector TopHadW_TOPTOPLEPHAD_JerDown_p4()           {return _TopHadW_TOPTOPLEPHAD_JerDown_p4;};
   TLorentzVector TopHadBJet_TOPTOPLEPHAD_JerDown_p4()        {return _TopHadBJet_TOPTOPLEPHAD_JerDown_p4;};
   
   float TopLepBJet_TOPTOPLEPHBB_CSVv2()      {return _TopLepBJet_TOPTOPLEPHBB_CSVv2;};
   float HiggsBJet1_TOPTOPLEPHBB_CSVv2()      {return _HiggsBJet1_TOPTOPLEPHBB_CSVv2;};
   float HiggsBJet2_TOPTOPLEPHBB_CSVv2()      {return _HiggsBJet2_TOPTOPLEPHBB_CSVv2;};
   float TopHadNonBJet_TOPTOPLEPHBB_CSVv2()   {return _TopHadNonBJet_TOPTOPLEPHBB_CSVv2;};

   float TopLepBJet_TOPHLEPBB_CSVv2()      {return _TopLepBJet_TOPHLEPBB_CSVv2;};
   float HiggsBJet1_TOPHLEPBB_CSVv2()      {return _HiggsBJet1_TOPHLEPBB_CSVv2;};
   float HiggsBJet2_TOPHLEPBB_CSVv2()      {return _HiggsBJet2_TOPHLEPBB_CSVv2;};

   float TopLepBJet_TOPTOPLEPHAD_CSVv2()        {return _TopLepBJet_TOPTOPLEPHAD_CSVv2;};
   float TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2()   {return _TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2;};
   float TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2()   {return _TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2;};
   float TopHadBJet_TOPTOPLEPHAD_CSVv2()        {return _TopHadBJet_TOPTOPLEPHAD_CSVv2;};

   float TopLepBJet_TOPTOPLEPHBB_charge()      {return _TopLepBJet_TOPTOPLEPHBB_charge;};
   float HiggsBJet1_TOPTOPLEPHBB_charge()      {return _HiggsBJet1_TOPTOPLEPHBB_charge;};
   float HiggsBJet2_TOPTOPLEPHBB_charge()      {return _HiggsBJet2_TOPTOPLEPHBB_charge;};
   float TopHadNonBJet_TOPTOPLEPHBB_charge()   {return _TopHadNonBJet_TOPTOPLEPHBB_charge;};

   float TopLepBJet_TOPHLEPBB_charge()      {return _TopLepBJet_TOPHLEPBB_charge;};
   float HiggsBJet1_TOPHLEPBB_charge()      {return _HiggsBJet1_TOPHLEPBB_charge;};
   float HiggsBJet2_TOPHLEPBB_charge()      {return _HiggsBJet2_TOPHLEPBB_charge;};

   float TopLepBJet_TOPTOPLEPHAD_charge()        {return _TopLepBJet_TOPTOPLEPHAD_charge;};
   float TopHadWNonBJet1_TOPTOPLEPHAD_charge()   {return _TopHadWNonBJet1_TOPTOPLEPHAD_charge;};
   float TopHadWNonBJet2_TOPTOPLEPHAD_charge()   {return _TopHadWNonBJet2_TOPTOPLEPHAD_charge;};
   float TopHadBJet_TOPTOPLEPHAD_charge()        {return _TopHadBJet_TOPTOPLEPHAD_charge;};

   float TopLepBJet_TOPTOPLEPHBB_chargeVec()      {return _TopLepBJet_TOPTOPLEPHBB_chargeVec;};
   float HiggsBJet1_TOPTOPLEPHBB_chargeVec()      {return _HiggsBJet1_TOPTOPLEPHBB_chargeVec;};
   float HiggsBJet2_TOPTOPLEPHBB_chargeVec()      {return _HiggsBJet2_TOPTOPLEPHBB_chargeVec;};
   float TopHadNonBJet_TOPTOPLEPHBB_chargeVec()   {return _TopHadNonBJet_TOPTOPLEPHBB_chargeVec;};

   float TopLepBJet_TOPHLEPBB_chargeVec()      {return _TopLepBJet_TOPHLEPBB_chargeVec;};
   float HiggsBJet1_TOPHLEPBB_chargeVec()      {return _HiggsBJet1_TOPHLEPBB_chargeVec;};
   float HiggsBJet2_TOPHLEPBB_chargeVec()      {return _HiggsBJet2_TOPHLEPBB_chargeVec;};

   float TopLepBJet_TOPTOPLEPHAD_chargeVec()        {return _TopLepBJet_TOPTOPLEPHAD_chargeVec;};
   float TopHadWNonBJet1_TOPTOPLEPHAD_chargeVec()   {return _TopHadWNonBJet1_TOPTOPLEPHAD_chargeVec;};
   float TopHadWNonBJet2_TOPTOPLEPHAD_chargeVec()   {return _TopHadWNonBJet2_TOPTOPLEPHAD_chargeVec;};
   float TopHadBJet_TOPTOPLEPHAD_chargeVec()        {return _TopHadBJet_TOPTOPLEPHAD_chargeVec;};

   float TopLepBJet_TOPTOPLEPHBB_CharmCvsL()      {return _TopLepBJet_TOPTOPLEPHBB_CharmCvsL;};
   float HiggsBJet1_TOPTOPLEPHBB_CharmCvsL()      {return _HiggsBJet1_TOPTOPLEPHBB_CharmCvsL;};
   float HiggsBJet2_TOPTOPLEPHBB_CharmCvsL()      {return _HiggsBJet2_TOPTOPLEPHBB_CharmCvsL;};
   float TopHadNonBJet_TOPTOPLEPHBB_CharmCvsL()   {return _TopHadNonBJet_TOPTOPLEPHBB_CharmCvsL;};

   float TopLepBJet_TOPHLEPBB_CharmCvsL()      {return _TopLepBJet_TOPHLEPBB_CharmCvsL;};
   float HiggsBJet1_TOPHLEPBB_CharmCvsL()      {return _HiggsBJet1_TOPHLEPBB_CharmCvsL;};
   float HiggsBJet2_TOPHLEPBB_CharmCvsL()      {return _HiggsBJet2_TOPHLEPBB_CharmCvsL;};

   float TopLepBJet_TOPTOPLEPHAD_CharmCvsL()        {return _TopLepBJet_TOPTOPLEPHAD_CharmCvsL;};
   float TopHadWNonBJet1_TOPTOPLEPHAD_CharmCvsL()   {return _TopHadWNonBJet1_TOPTOPLEPHAD_CharmCvsL;};
   float TopHadWNonBJet2_TOPTOPLEPHAD_CharmCvsL()   {return _TopHadWNonBJet2_TOPTOPLEPHAD_CharmCvsL;};
   float TopHadBJet_TOPTOPLEPHAD_CharmCvsL()        {return _TopHadBJet_TOPTOPLEPHAD_CharmCvsL;};

   float TopLepBJet_TOPTOPLEPHBB_CharmCvsB()      {return _TopLepBJet_TOPTOPLEPHBB_CharmCvsB;};
   float HiggsBJet1_TOPTOPLEPHBB_CharmCvsB()      {return _HiggsBJet1_TOPTOPLEPHBB_CharmCvsB;};
   float HiggsBJet2_TOPTOPLEPHBB_CharmCvsB()      {return _HiggsBJet2_TOPTOPLEPHBB_CharmCvsB;};
   float TopHadNonBJet_TOPTOPLEPHBB_CharmCvsB()   {return _TopHadNonBJet_TOPTOPLEPHBB_CharmCvsB;};

   float TopLepBJet_TOPHLEPBB_CharmCvsB()      {return _TopLepBJet_TOPHLEPBB_CharmCvsB;};
   float HiggsBJet1_TOPHLEPBB_CharmCvsB()      {return _HiggsBJet1_TOPHLEPBB_CharmCvsB;};
   float HiggsBJet2_TOPHLEPBB_CharmCvsB()      {return _HiggsBJet2_TOPHLEPBB_CharmCvsB;};

   float TopLepBJet_TOPTOPLEPHAD_CharmCvsB()        {return _TopLepBJet_TOPTOPLEPHAD_CharmCvsB;};
   float TopHadWNonBJet1_TOPTOPLEPHAD_CharmCvsB()   {return _TopHadWNonBJet1_TOPTOPLEPHAD_CharmCvsB;};
   float TopHadWNonBJet2_TOPTOPLEPHAD_CharmCvsB()   {return _TopHadWNonBJet2_TOPTOPLEPHAD_CharmCvsB;};
   float TopHadBJet_TOPTOPLEPHAD_CharmCvsB()        {return _TopHadBJet_TOPTOPLEPHAD_CharmCvsB;};

   int HiggsBJet1_TOPTOPLEPHBB_JetIdx() {return _HiggsBJet1_TOPTOPLEPHBB_JetIdx;};
   int HiggsBJet2_TOPTOPLEPHBB_JetIdx() {return _HiggsBJet2_TOPTOPLEPHBB_JetIdx;};
   int TopLepBJet_TOPTOPLEPHBB_JetIdx() {return _TopLepBJet_TOPTOPLEPHBB_JetIdx;};
   int TopHadNonBJet_TOPTOPLEPHBB_JetIdx() {return _TopHadNonBJet_TOPTOPLEPHBB_JetIdx;};

   int HiggsBJet1_TOPHLEPBB_JetIdx() {return _HiggsBJet1_TOPHLEPBB_JetIdx;};
   int HiggsBJet2_TOPHLEPBB_JetIdx() {return _HiggsBJet2_TOPHLEPBB_JetIdx;};
   int TopLepBJet_TOPHLEPBB_JetIdx() {return _TopLepBJet_TOPHLEPBB_JetIdx;};

   int TopLepBJet_TOPTOPLEPHAD_JetIdx() {return _TopLepBJet_TOPTOPLEPHAD_JetIdx;};
   int TopHadBJet_TOPTOPLEPHAD_JetIdx() {return _TopHadBJet_TOPTOPLEPHAD_JetIdx;};
   int TopHadWNonBJet1_TOPTOPLEPHAD_JetIdx() {return _TopHadWNonBJet1_TOPTOPLEPHAD_JetIdx;};
   int TopHadWNonBJet2_TOPTOPLEPHAD_JetIdx() {return _TopHadWNonBJet2_TOPTOPLEPHAD_JetIdx;};
   
   double chi2_TOPTOPLEPHBB()       {return _chi2_TOPTOPLEPHBB;};
   double chi2_TOPHLEPBB()          {return _chi2_TOPHLEPBB;};
   double chi2_TOPTOPLEPHAD()       {return _chi2_TOPTOPLEPHAD;};

   double MVA_TOPTOPLEPHBB()               {return _MVA_TOPTOPLEPHBB;};
   double MVA_TOPTOPLEPHBB_JesUp()         {return _MVAJesUp_TOPTOPLEPHBB;};
   double MVA_TOPTOPLEPHBB_JesDown()       {return _MVAJesDown_TOPTOPLEPHBB;};
   double MVA_TOPTOPLEPHBB_JerUp()         {return _MVAJerUp_TOPTOPLEPHBB;};
   double MVA_TOPTOPLEPHBB_JerDown()       {return _MVAJerDown_TOPTOPLEPHBB;};
   
   double MVA_TOPHLEPBB()                  {return _MVA_TOPHLEPBB;};
   double MVA_TOPHLEPBB_JesUp()            {return _MVAJesUp_TOPHLEPBB;};
   double MVA_TOPHLEPBB_JesDown()          {return _MVAJesDown_TOPHLEPBB;};
   double MVA_TOPHLEPBB_JerUp()            {return _MVAJerUp_TOPHLEPBB;};
   double MVA_TOPHLEPBB_JerDown()          {return _MVAJerDown_TOPHLEPBB;};
   
   double MVA_TOPTOPLEPHAD()               {return _MVA_TOPTOPLEPHAD;};
   double MVA_TOPTOPLEPHAD_JesUp()         {return _MVAJesUp_TOPTOPLEPHAD;};
   double MVA_TOPTOPLEPHAD_JesDown()       {return _MVAJesDown_TOPTOPLEPHAD;};
   double MVA_TOPTOPLEPHAD_JerUp()         {return _MVAJerUp_TOPTOPLEPHAD;};
   double MVA_TOPTOPLEPHAD_JerDown()       {return _MVAJerDown_TOPTOPLEPHAD;};
   
 protected:

   std::vector<Lepton>             *_v_Lepton;
   
   std::vector<Electron>           *_v_Electron;
   std::vector<Muon>               *_v_Muon;
   std::vector<Electron>           *_v_ElectronTight;
   std::vector<Muon>               *_v_MuonTight;
   
   std::vector<Event>              *_v_Event;
   std::vector<Jet>                *_v_Jet;
   std::vector<Jet>                *_v_BJet;
   std::vector<Jet>                *_v_NonBJet;
   std::vector<Jet>                *_v_JetTight;
   std::vector<Jet>                *_v_BJetTight;
   std::vector<Jet>                *_v_NonBJetTight;

   Helper *help;
   
 private:

   // nominal
   TLorentzVector _TopLepBJet_TOPTOPLEPHBB_p4;
   TLorentzVector _HiggsBJet1_TOPTOPLEPHBB_p4;
   TLorentzVector _HiggsBJet2_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLepWLep_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLepWNu_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLep_TOPTOPLEPHBB_p4;
   TLorentzVector _Higgs_TOPTOPLEPHBB_p4;
   TLorentzVector _TopLepW_TOPTOPLEPHBB_p4;
   TLorentzVector _TopHadNonBJet_TOPTOPLEPHBB_p4;

   TLorentzVector _TopLepBJet_TOPHLEPBB_p4;
   TLorentzVector _HiggsBJet1_TOPHLEPBB_p4;
   TLorentzVector _HiggsBJet2_TOPHLEPBB_p4;
   TLorentzVector _TopLepWLep_TOPHLEPBB_p4;
   TLorentzVector _TopLepWNu_TOPHLEPBB_p4;
   TLorentzVector _TopLep_TOPHLEPBB_p4;
   TLorentzVector _Higgs_TOPHLEPBB_p4;
   TLorentzVector _TopLepW_TOPHLEPBB_p4;

   TLorentzVector _TopLepBJet_TOPTOPLEPHAD_p4;
   TLorentzVector _TopHadWNonBJet1_TOPTOPLEPHAD_p4;
   TLorentzVector _TopHadWNonBJet2_TOPTOPLEPHAD_p4;
   TLorentzVector _TopLepWLep_TOPTOPLEPHAD_p4;
   TLorentzVector _TopLepWNu_TOPTOPLEPHAD_p4;
   TLorentzVector _TopLep_TOPTOPLEPHAD_p4;
   TLorentzVector _TopHad_TOPTOPLEPHAD_p4;
   TLorentzVector _TopHadW_TOPTOPLEPHAD_p4;
   TLorentzVector _TopLepW_TOPTOPLEPHAD_p4;
   TLorentzVector _TopHadBJet_TOPTOPLEPHAD_p4;

   // JesUp
   TLorentzVector _TopLepBJet_TOPTOPLEPHBB_JesUp_p4;
   TLorentzVector _HiggsBJet1_TOPTOPLEPHBB_JesUp_p4;
   TLorentzVector _HiggsBJet2_TOPTOPLEPHBB_JesUp_p4;
   TLorentzVector _TopLep_TOPTOPLEPHBB_JesUp_p4;
   TLorentzVector _Higgs_TOPTOPLEPHBB_JesUp_p4;
   TLorentzVector _TopHadNonBJet_TOPTOPLEPHBB_JesUp_p4;

   TLorentzVector _TopLepBJet_TOPHLEPBB_JesUp_p4;
   TLorentzVector _HiggsBJet1_TOPHLEPBB_JesUp_p4;
   TLorentzVector _HiggsBJet2_TOPHLEPBB_JesUp_p4;
   TLorentzVector _TopLep_TOPHLEPBB_JesUp_p4;
   TLorentzVector _Higgs_TOPHLEPBB_JesUp_p4;

   TLorentzVector _TopLepBJet_TOPTOPLEPHAD_JesUp_p4;
   TLorentzVector _TopHadWNonBJet1_TOPTOPLEPHAD_JesUp_p4;
   TLorentzVector _TopHadWNonBJet2_TOPTOPLEPHAD_JesUp_p4;
   TLorentzVector _TopLep_TOPTOPLEPHAD_JesUp_p4;
   TLorentzVector _TopHad_TOPTOPLEPHAD_JesUp_p4;
   TLorentzVector _TopHadW_TOPTOPLEPHAD_JesUp_p4;
   TLorentzVector _TopHadBJet_TOPTOPLEPHAD_JesUp_p4;

   // JesDown
   TLorentzVector _TopLepBJet_TOPTOPLEPHBB_JesDown_p4;
   TLorentzVector _HiggsBJet1_TOPTOPLEPHBB_JesDown_p4;
   TLorentzVector _HiggsBJet2_TOPTOPLEPHBB_JesDown_p4;
   TLorentzVector _TopLep_TOPTOPLEPHBB_JesDown_p4;
   TLorentzVector _Higgs_TOPTOPLEPHBB_JesDown_p4;
   TLorentzVector _TopHadNonBJet_TOPTOPLEPHBB_JesDown_p4;

   TLorentzVector _TopLepBJet_TOPHLEPBB_JesDown_p4;
   TLorentzVector _HiggsBJet1_TOPHLEPBB_JesDown_p4;
   TLorentzVector _HiggsBJet2_TOPHLEPBB_JesDown_p4;
   TLorentzVector _TopLep_TOPHLEPBB_JesDown_p4;
   TLorentzVector _Higgs_TOPHLEPBB_JesDown_p4;

   TLorentzVector _TopLepBJet_TOPTOPLEPHAD_JesDown_p4;
   TLorentzVector _TopHadWNonBJet1_TOPTOPLEPHAD_JesDown_p4;
   TLorentzVector _TopHadWNonBJet2_TOPTOPLEPHAD_JesDown_p4;
   TLorentzVector _TopLep_TOPTOPLEPHAD_JesDown_p4;
   TLorentzVector _TopHad_TOPTOPLEPHAD_JesDown_p4;
   TLorentzVector _TopHadW_TOPTOPLEPHAD_JesDown_p4;
   TLorentzVector _TopHadBJet_TOPTOPLEPHAD_JesDown_p4;

   // JerUp
   TLorentzVector _TopLepBJet_TOPTOPLEPHBB_JerUp_p4;
   TLorentzVector _HiggsBJet1_TOPTOPLEPHBB_JerUp_p4;
   TLorentzVector _HiggsBJet2_TOPTOPLEPHBB_JerUp_p4;
   TLorentzVector _TopLep_TOPTOPLEPHBB_JerUp_p4;
   TLorentzVector _Higgs_TOPTOPLEPHBB_JerUp_p4;
   TLorentzVector _TopHadNonBJet_TOPTOPLEPHBB_JerUp_p4;

   TLorentzVector _TopLepBJet_TOPHLEPBB_JerUp_p4;
   TLorentzVector _HiggsBJet1_TOPHLEPBB_JerUp_p4;
   TLorentzVector _HiggsBJet2_TOPHLEPBB_JerUp_p4;
   TLorentzVector _TopLep_TOPHLEPBB_JerUp_p4;
   TLorentzVector _Higgs_TOPHLEPBB_JerUp_p4;

   TLorentzVector _TopLepBJet_TOPTOPLEPHAD_JerUp_p4;
   TLorentzVector _TopHadWNonBJet1_TOPTOPLEPHAD_JerUp_p4;
   TLorentzVector _TopHadWNonBJet2_TOPTOPLEPHAD_JerUp_p4;
   TLorentzVector _TopLep_TOPTOPLEPHAD_JerUp_p4;
   TLorentzVector _TopHad_TOPTOPLEPHAD_JerUp_p4;
   TLorentzVector _TopHadW_TOPTOPLEPHAD_JerUp_p4;
   TLorentzVector _TopHadBJet_TOPTOPLEPHAD_JerUp_p4;

   // JerDown
   TLorentzVector _TopLepBJet_TOPTOPLEPHBB_JerDown_p4;
   TLorentzVector _HiggsBJet1_TOPTOPLEPHBB_JerDown_p4;
   TLorentzVector _HiggsBJet2_TOPTOPLEPHBB_JerDown_p4;
   TLorentzVector _TopLep_TOPTOPLEPHBB_JerDown_p4;
   TLorentzVector _Higgs_TOPTOPLEPHBB_JerDown_p4;
   TLorentzVector _TopHadNonBJet_TOPTOPLEPHBB_JerDown_p4;

   TLorentzVector _TopLepBJet_TOPHLEPBB_JerDown_p4;
   TLorentzVector _HiggsBJet1_TOPHLEPBB_JerDown_p4;
   TLorentzVector _HiggsBJet2_TOPHLEPBB_JerDown_p4;
   TLorentzVector _TopLep_TOPHLEPBB_JerDown_p4;
   TLorentzVector _Higgs_TOPHLEPBB_JerDown_p4;

   TLorentzVector _TopLepBJet_TOPTOPLEPHAD_JerDown_p4;
   TLorentzVector _TopHadWNonBJet1_TOPTOPLEPHAD_JerDown_p4;
   TLorentzVector _TopHadWNonBJet2_TOPTOPLEPHAD_JerDown_p4;
   TLorentzVector _TopLep_TOPTOPLEPHAD_JerDown_p4;
   TLorentzVector _TopHad_TOPTOPLEPHAD_JerDown_p4;
   TLorentzVector _TopHadW_TOPTOPLEPHAD_JerDown_p4;
   TLorentzVector _TopHadBJet_TOPTOPLEPHAD_JerDown_p4;
   
   float _TopLepBJet_TOPTOPLEPHBB_CSVv2;
   float _HiggsBJet1_TOPTOPLEPHBB_CSVv2;
   float _HiggsBJet2_TOPTOPLEPHBB_CSVv2;
   float _TopHadNonBJet_TOPTOPLEPHBB_CSVv2;

   float _TopLepBJet_TOPHLEPBB_CSVv2;
   float _HiggsBJet1_TOPHLEPBB_CSVv2;
   float _HiggsBJet2_TOPHLEPBB_CSVv2;

   float _TopLepBJet_TOPTOPLEPHAD_CSVv2;
   float _TopHadWNonBJet1_TOPTOPLEPHAD_CSVv2;
   float _TopHadWNonBJet2_TOPTOPLEPHAD_CSVv2;
   float _TopHadBJet_TOPTOPLEPHAD_CSVv2;

   float _TopLepBJet_TOPTOPLEPHBB_charge;
   float _HiggsBJet1_TOPTOPLEPHBB_charge;
   float _HiggsBJet2_TOPTOPLEPHBB_charge;
   float _TopHadNonBJet_TOPTOPLEPHBB_charge;

   float _TopLepBJet_TOPHLEPBB_charge;
   float _HiggsBJet1_TOPHLEPBB_charge;
   float _HiggsBJet2_TOPHLEPBB_charge;

   float _TopLepBJet_TOPTOPLEPHAD_charge;
   float _TopHadWNonBJet1_TOPTOPLEPHAD_charge;
   float _TopHadWNonBJet2_TOPTOPLEPHAD_charge;
   float _TopHadBJet_TOPTOPLEPHAD_charge;

   float _TopLepBJet_TOPTOPLEPHBB_chargeVec;
   float _HiggsBJet1_TOPTOPLEPHBB_chargeVec;
   float _HiggsBJet2_TOPTOPLEPHBB_chargeVec;
   float _TopHadNonBJet_TOPTOPLEPHBB_chargeVec;

   float _TopLepBJet_TOPHLEPBB_chargeVec;
   float _HiggsBJet1_TOPHLEPBB_chargeVec;
   float _HiggsBJet2_TOPHLEPBB_chargeVec;

   float _TopLepBJet_TOPTOPLEPHAD_chargeVec;
   float _TopHadWNonBJet1_TOPTOPLEPHAD_chargeVec;
   float _TopHadWNonBJet2_TOPTOPLEPHAD_chargeVec;
   float _TopHadBJet_TOPTOPLEPHAD_chargeVec;

   float _TopLepBJet_TOPTOPLEPHBB_CharmCvsL;
   float _HiggsBJet1_TOPTOPLEPHBB_CharmCvsL;
   float _HiggsBJet2_TOPTOPLEPHBB_CharmCvsL;
   float _TopHadNonBJet_TOPTOPLEPHBB_CharmCvsL;

   float _TopLepBJet_TOPHLEPBB_CharmCvsL;
   float _HiggsBJet1_TOPHLEPBB_CharmCvsL;
   float _HiggsBJet2_TOPHLEPBB_CharmCvsL;

   float _TopLepBJet_TOPTOPLEPHAD_CharmCvsL;
   float _TopHadWNonBJet1_TOPTOPLEPHAD_CharmCvsL;
   float _TopHadWNonBJet2_TOPTOPLEPHAD_CharmCvsL;
   float _TopHadBJet_TOPTOPLEPHAD_CharmCvsL;

   float _TopLepBJet_TOPTOPLEPHBB_CharmCvsB;
   float _HiggsBJet1_TOPTOPLEPHBB_CharmCvsB;
   float _HiggsBJet2_TOPTOPLEPHBB_CharmCvsB;
   float _TopHadNonBJet_TOPTOPLEPHBB_CharmCvsB;

   float _TopLepBJet_TOPHLEPBB_CharmCvsB;
   float _HiggsBJet1_TOPHLEPBB_CharmCvsB;
   float _HiggsBJet2_TOPHLEPBB_CharmCvsB;

   float _TopLepBJet_TOPTOPLEPHAD_CharmCvsB;
   float _TopHadWNonBJet1_TOPTOPLEPHAD_CharmCvsB;
   float _TopHadWNonBJet2_TOPTOPLEPHAD_CharmCvsB;
   float _TopHadBJet_TOPTOPLEPHAD_CharmCvsB;

   int _HiggsBJet1_TOPTOPLEPHBB_JetIdx;
   int _HiggsBJet2_TOPTOPLEPHBB_JetIdx;
   int _TopLepBJet_TOPTOPLEPHBB_JetIdx;
   int _TopHadNonBJet_TOPTOPLEPHBB_JetIdx;

   int _HiggsBJet1_TOPHLEPBB_JetIdx;
   int _HiggsBJet2_TOPHLEPBB_JetIdx;
   int _TopLepBJet_TOPHLEPBB_JetIdx;

   int _TopLepBJet_TOPTOPLEPHAD_JetIdx;
   int _TopHadBJet_TOPTOPLEPHAD_JetIdx;
   int _TopHadWNonBJet1_TOPTOPLEPHAD_JetIdx;
   int _TopHadWNonBJet2_TOPTOPLEPHAD_JetIdx;
   
   double _chi2_TOPTOPLEPHBB;
   double _chi2_TOPHLEPBB;
   double _chi2_TOPTOPLEPHAD;

   double _MVA_TOPTOPLEPHBB;
   double _MVAJesUp_TOPTOPLEPHBB;
   double _MVAJesDown_TOPTOPLEPHBB;
   double _MVAJerUp_TOPTOPLEPHBB;
   double _MVAJerDown_TOPTOPLEPHBB;
   
   double _MVA_TOPHLEPBB;
   double _MVAJesUp_TOPHLEPBB;
   double _MVAJesDown_TOPHLEPBB;
   double _MVAJerUp_TOPHLEPBB;
   double _MVAJerDown_TOPHLEPBB;
   
   double _MVA_TOPTOPLEPHAD;
   double _MVAJesUp_TOPTOPLEPHAD;
   double _MVAJesDown_TOPTOPLEPHAD;
   double _MVAJerUp_TOPTOPLEPHAD;
   double _MVAJerDown_TOPTOPLEPHAD;
   
   TRandom3 *rnd;

   KINFIT::kfit *kfTopTopLepHbb;
   KINFIT::kfit *kfTopHLepbb;
   KINFIT::kfit *kfTopTopLepHad;

   TMVA::Reader* MVAFullRecoReaderTOPTOPLEPHBB;
   TMVA::Reader* MVAPartRecoReaderTOPTOPLEPHBB;

   float MVAFullReco_HiggsRecM_TOPTOPLEPHBB;
   float MVAFullReco_TopLepRecM_TOPTOPLEPHBB;
   float MVAFullReco_HiggsTopLepRecDr_TOPTOPLEPHBB;
   float MVAFullReco_TopLepRecPt_TOPTOPLEPHBB;
   
   float MVAPartReco_HiggsRecM_TOPTOPLEPHBB;
   float MVAPartReco_TopLepRecMT_TOPTOPLEPHBB;
   float MVAPartReco_HiggsTopLepRecDphiT_TOPTOPLEPHBB;
   float MVAPartReco_TopLepRecPtT_TOPTOPLEPHBB;

   TMVA::Reader* MVAFullRecoReaderTOPHLEPBB;
   TMVA::Reader* MVAPartRecoReaderTOPHLEPBB;

   float MVAFullReco_HiggsRecM_TOPHLEPBB;
   float MVAFullReco_TopLepRecM_TOPHLEPBB;
   float MVAFullReco_HiggsTopLepRecDr_TOPHLEPBB;
   float MVAFullReco_TopLepRecPt_TOPHLEPBB;
   
   float MVAPartReco_HiggsRecM_TOPHLEPBB;
   float MVAPartReco_TopLepRecMT_TOPHLEPBB;
   float MVAPartReco_HiggsTopLepRecDphiT_TOPHLEPBB;
   float MVAPartReco_TopLepRecPtT_TOPHLEPBB;

   TMVA::Reader* MVAFullRecoReaderTOPTOPLEPHAD;
   TMVA::Reader* MVAPartRecoReaderTOPTOPLEPHAD;

   float MVAFullReco_TopHadRecM_TOPTOPLEPHAD;
   float MVAFullReco_TopLepRecM_TOPTOPLEPHAD;
   float MVAFullReco_TopLepTopHadRecDr_TOPTOPLEPHAD;
   float MVAFullReco_TopLepRecPt_TOPTOPLEPHAD;
   
   float MVAPartReco_TopHadRecM_TOPTOPLEPHAD;
   float MVAPartReco_TopLepRecMT_TOPTOPLEPHAD;
   float MVAPartReco_TopLepTopHadRecDphiT_TOPTOPLEPHAD;
   float MVAPartReco_TopLepRecPtT_TOPTOPLEPHAD;
};

#endif
