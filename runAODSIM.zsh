#!/bin/env zsh

cp hadronize.py Configuration/Generator/python/.

cmsDriver.py hadronize \
--mc --eventcontent AODSIM \
--beamspot NominalCollision2015 \
--conditions auto:run2_mc \
--magField 38T_PostLS1 \
--step GEN,SIM,RECO,EI,HLT:@relval \
--fast \
--customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 \
--python_filename prod_LHEtoRECO.py --no_exec -n 2 \
--fileout step1.root
