#ifndef NTUPLEPRODUCER_H
#define NTUPLEPRODUCER_H

#include "Tree.h"
#include "Electron.h"
#include "Muon.h"
#include "Event.h"
#include "Jet.h"
#include "Truth.h"
#include "Ntuple.h"

#include "BTagCalibrationStandalone.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

#include "TH2F.h"
#include "TRandom3.h"

extern Tree *ntP;
extern TChain *ch;
extern Ntuple *nt;
extern std::vector<int> *evdebug;

extern BTagCalibration *calib;
extern BTagCalibrationReader *reader_iterativefit;

extern JetCorrectionUncertainty *jesTotal;
extern JME::JetResolution *jer;

extern TRandom3 *rnd;

extern double cJER[13];
extern double cJER_down[13];
extern double cJER_up[13];

extern double _weights[75];
extern double _weightsUp[75];
extern double _weightsDown[75];

extern TH2F* _hegammaID;

extern EffectiveAreas* effectiveAreas_;

#endif
