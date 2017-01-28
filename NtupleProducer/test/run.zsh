#!/bin/env zsh

cdir=$(pwd)/../
export LD_LIBRARY_PATH=${cdir}:${cdir}/obj:$LD_LIBRARY_PATH

#infl="lists/TT_TuneCUETP8M1_13TeV-powheg-pythia8_ID48.txt"
#infl="lists/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ID0.txt"
#infl="lists/ST_TH_1L3B_Hct_ID1.txt"
#infl="lists/SingleElectron_Run2016D_PromptReco_v2_MINIAOD_ID7.txt"
infl="list.txt"

fxsec="table.txt"

sample=$(echo $infl | sed 's%lists/%%g' | sed 's%.txt%%g' | sed 's%_ID.*%%g')

linexsec=$(grep $sample $fxsec)
noe=$(echo $linexsec | awk '{print $3}')
xsec=$(echo $linexsec | awk '{print $2}')

echo "${infl} FlatTree/tree ${noe} ${xsec}"

time ./NtupleProducer \
--file ${infl} \
--tree FlatTree/tree \
--outfile "output" \
--noe ${noe} \
--xsec ${xsec} \
--nmax -1 \
--isdata 0 \
--stream 0 \
--issig 1
