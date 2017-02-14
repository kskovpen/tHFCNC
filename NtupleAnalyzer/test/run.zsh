#!/bin/env zsh

cdir=$(pwd)/../
NtupleDir=$(pwd)/../../NtupleProducer/
export LD_LIBRARY_PATH=${cdir}:${NtupleDir}:${NtupleDir}/obj:../../../TopKinFit/:$LD_LIBRARY_PATH

nmax=100
#nmax=-1
#tool="topreco"
tool="plot"
#tool="jetassign"
#ilist="lists/tHFCNC13TeV_kskovpen_kskovpen_TTtoTHToBB_1L_Kappa_hut_ID0.txt"
#ilist="lists/TT_TopLeptonicDecay_TH_1L3B_Eta_Hct_ID13.txt"
#ilist="lists/TT_TuneCUETP8M1_13TeV-powheg-pythia8_ID0.txt"
ilist="list.txt"
#ilist="lists/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ID0.txt"
home=$(pwd)
evec=0

# tools: plot, topreco

./../Analyzer \
${ilist} \
output \
${tool} \
${nmax} \
${home} \
${evec}

