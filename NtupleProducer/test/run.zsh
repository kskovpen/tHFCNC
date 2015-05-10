#!/bin/env zsh

# remove when using xrd
#export LD_PRELOAD=/usr/lib64/libglobus_gssapi_gsi.so.4

cdir=$(pwd)/../
export LD_LIBRARY_PATH=${cdir}:$LD_LIBRARY_PATH

infl="tHToBB_1L_Kappa_hut_ID0.txt"

fxsec="xsec.txt"
fstat="stat.txt"

sample=$(echo $infl | sed 's%.txt%%g' | sed 's%_ID.*%%g')

linexsec=$(grep $sample $fxsec)
linestat=$(grep $sample $fstat)
noe=$(echo $linestat | awk '{print $2}')
xsec=$(echo $linexsec | awk '{print $2}')

echo "lists/${infl} FlatTree/tree ${noe} ${xsec}"

./NtupleProducer \
--file lists/${infl} \
--tree FlatTree/tree \
--noe ${noe} \
--xsec ${xsec}
