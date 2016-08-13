#!/bin/env zsh

cdir=$(pwd)/../
export LD_LIBRARY_PATH=${cdir}:${cdir}/obj:$LD_LIBRARY_PATH

#infl="TT_TopLeptonicDecay_TH_1L3B_Eta_Hut_ID19.txt"
#infl="SingleMuon_Run2016B_PromptReco_v2_MINIAOD_ID0.txt"
infl="ST_TH_1L3B_Hct_ID1.txt"

fxsec="table.txt"

sample=$(echo $infl | sed 's%.txt%%g' | sed 's%_ID.*%%g')

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
--stream -1 \
--issig 1
