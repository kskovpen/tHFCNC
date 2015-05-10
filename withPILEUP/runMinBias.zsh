#!/bin/env zsh

cmsDriver.py MinBias_13TeV_pythia8_TuneCUETP8M1_cfi -n 1000 \
--conditions auto:run2_mc --beamspot NominalCollision2015 --magField 38T_PostLS1 \
-s GEN,SIM,RECO --fast \
--eventcontent FASTPU  \
--customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 \
--fileout minbias.root
