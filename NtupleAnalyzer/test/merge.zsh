#!/bin/env zsh

ilist="/opt/sbg/data/safe1/cms/kskovpen/tHFCNC/CMSSW_7_2_3/src/NtupleProducer/test/stat.txt"

rm -rf histMERGE
mkdir histMERGE

flist=($(cat ${ilist} | awk '{print $1}'))
for i in $flist
do
  mlist=($(ls hist | grep ${i}))
  if [[ ${mlist} == "" ]]; then
    continue
  fi
  farr=()
  idx=1
  echo "Merge ${i}"
  for j in $mlist
  do
    farr[${idx}]="hist/"${j}
    idx=$[$idx+1]
  done
  hadd -f histMERGE/${i}.root ${farr[*]}
done
