#!/bin/env zsh

cmsDriver.py step2 -n 10 \
--conditions auto:run2_mc \
-s PAT --fast --mc \
--eventcontent MINIAODSIM \
--customise \
SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 \
--filein file:step1.root --fileout miniaod.root \
--runUnscheduled \
--no_exec -n 2
