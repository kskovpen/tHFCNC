#!/bin/env zsh

cdir=$(pwd)/../
NtupleDir=$(pwd)/../../NtupleProducer/
export LD_LIBRARY_PATH=${cdir}:${NtupleDir}:$LD_LIBRARY_PATH

indir="lists/"

dlist=($(ls ${indir}))
for i in $dlist
do
  echo ${indir}/${i} > input.txt
  ./../Analyzer \
input.txt \
testfile \
plot \
1
  cp hist/output.root ${outdir}/${i}
done

