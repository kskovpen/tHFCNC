#!/bin/env zsh

#export LD_PRELOAD=/usr/lib64/libglobus_gssapi_gsi.so.4

nmax=-1

cdir=$(pwd)/../
NtupleDir=$(pwd)/../../NtupleProducer/
export LD_LIBRARY_PATH=${cdir}:${NtupleDir}:$LD_LIBRARY_PATH

fpath="lists/"

rm -rf hist
mkdir hist
rm -rf logs
mkdir logs

tool="plot"
#tool="topreco"
njobMax=15
evc="0"

#flist=$(ls ${fpath} | grep Kappa)
flist=$(ls ${fpath})
echo $flist | while read line
do
jidx=0
sample=$(echo $line | sed 's%.txt%%g')
dataset=$(echo $sample | sed 's%_ID.*%%g')

#./../Analyzer \
#${fpath}${line} \
#testfile \
#${tool} \
#1

list=($(pgrep Analyzer))
njobs=${#list[@]}
if [[ $njobs -ge ${njobMax} ]]; then
while true
do
sleep 1
list=($(pgrep Analyzer))
njobs=${#list[@]}
if [[ $njobs -lt ${njobMax} ]]; then
break
fi
done
fi
echo ${line}
nohup ./job.sh ${fpath}${line} ${tool} ${sample} ${nmax} ${evc} > logs/${sample}.log 2>&1&
done
