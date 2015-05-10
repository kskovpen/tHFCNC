#!/bin/env zsh

cdir=$(pwd)/../
NtupleDir=$(pwd)/../../NtupleProducer/
export LD_LIBRARY_PATH=${cdir}:${NtupleDir}:$LD_LIBRARY_PATH

nmax=10000
evc=0
#tool="topreco"
tool="plot"
#ilist="lists/tHToBB_1L_Kappa_hut_ID0.txt"
ilist="lists/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola_ID9.txt"

# tools: plot, topreco

./../Analyzer \
${ilist} \
output \
${tool} \
${evc} \
${nmax}

