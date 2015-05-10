#!/bin/env zsh

#cmsDriver.py Configuration/GenProduction/python/GEN.py --filein mg/MG5_aMC_v2_2_1/thj0_WToLV_HToBB/Events/run_01/unweighted_events.lhe \
#--mc --eventcontent AODSIM --datatier \
#--beamspot Realistic8TeVCollision \
#RECOSIM --conditions AUTO --pileup \
#2012_Summer_50ns_PoissonOOTPU --step \
#GEN,SIM,DIGI,L1,DIGI2RAW,RAW2DIGI,L1Reco,RECO \
#--python_filename prod_LHEtoRECO.py --no_exec -n 2

# RECOSIM --conditions START53_V29::All --pileup \
# GEN,SIM,DIGI,L1,DIGI2RAW,HLT:7E33v2,RAW2DIGI,L1Reco,RECO \

#cmsDriver.py FastSimulation/Configuration/python/GEN.py --filein mg/MG5_aMC_v2_2_1/thj0_WToLV_HToBB/Events/run_01/unweighted_events.lhe \
#--mc --eventcontent AODSIM --datatier \
#--beamspot Realistic8TeVCollision \
#RECOSIM --conditions auto:startup_GRun \
#--step GEN,SIM,RECO,HLT \
#--fast \
#--python_filename prod_LHEtoRECO.py --no_exec -n 2

cmsDriver.py FastSimulation/Configuration/python/GEN.py --filein mg/MG5_aMC_v2_2_1/thj0_WToLV_HToBB/Events/run_01/unweighted_events.lhe \
--mc --eventcontent AODSIM --datatier \
--beamspot NominalCollision2015 \
RECOSIM --conditions auto:run2_mc \
--magField 38T_PostLS1 \
--pileup CSA14_inTimeOnly \
--pileup_input file:minbias.root \
--step GEN,SIM,RECO,EI,HLT:@relval \
--fast \
--customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 \
--python_filename prod_LHEtoRECO.py --no_exec -n 2

# --pileup_input file:minbias.root \
