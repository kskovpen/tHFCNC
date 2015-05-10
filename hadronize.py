import FWCore.ParameterSet.Config as cms 

source = cms.Source("LHESource", fileNames = cms.untracked.vstring(
 "file:input.lhe"))

from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.Pythia8CUEP8M1Settings_cfi import *
 
generator = cms.EDFilter("Pythia8HadronizerFilter",
                         maxEventsToPrint = cms.untracked.int32(1),
                         pythiaPylistVerbosity = cms.untracked.int32(1),
                         filterEfficiency = cms.untracked.double(1.0),
                         pythiaHepMCVerbosity = cms.untracked.bool(False),
                         comEnergy = cms.double(13000.),
                         PythiaParameters = cms.PSet(                         
            pythia8CommonSettingsBlock,
            pythia8CUEP8M1SettingsBlock,
            processParameters = cms.vstring(
                         '25:onMode = off',
                         '25:4:onMode = on',
                         '24:onMode = off',
                         '24:6:onMode = on',
                         '24:7:onMode = on',
                         '24:8:onMode = on'
            ),
            JetMatchingParameters = cms.vstring(
                   'JetMatching:setMad = on'
#                   'JetMatching:scheme = 1',
#                   'JetMatching:merge = on',
#                   'JetMatching:jetAlgorithm = 2',
#                   'JetMatching:etaJetMax = 5.',
#                   'JetMatching:coneRadius = 1.',
#                   'JetMatching:slowJetPower = 1',
#                   'JetMatching:qCut = 20.', #this is the actual merging scale
#                   'JetMatching:nQmatch = 5', #4 corresponds to 4-flavour scheme (no matching of b-quarks), 5 for 5-flavour scheme
#                   'JetMatching:nJetMax = 4', #number of partons in born matrix element for highest multiplicity
#                   'JetMatching:doShowerKt = off', #off for MLM matching, turn on for shower-kT matching
                   ),
             parameterSets = cms.vstring('pythia8CommonSettings',
                                         'pythia8CUEP8M1Settings',
                                         'JetMatchingParameters',
                                         'processParameters'
                                         )
                                  )
                            )
                         
ProductionFilterSequence = cms.Sequence(generator)
