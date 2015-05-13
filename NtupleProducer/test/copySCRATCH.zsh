#!/bin/env zsh

dirName=${1}

voName="vo.sbg.in2p3.fr"
#voName="cms"

njobMax=10

if [[ ${dirName} == "" ]]; then
  echo "Please specify input directory"
  exit
fi

dpath="/opt/sbg/scratch1/${voName}/kskovpen/tH/${dirName}DATA/"
opath="/opt/sbg/scratch1/cms/kskovpen/toyTEST/"
#opath="/opt/sbg/data/sbgse24/data1/cms/kskovpen/tH/toy${dirName}/"

rm -rf ${opath}
mkdir ${opath}

rm -rf logs
mkdir logs

flist=($(ls ${dpath}))

for i in $flist
do
  list=($(pgrep cp))
  njobs=${#list[@]}
  if [[ $njobs -ge ${njobMax} ]]; then
    while true
    do
      sleep 1
      list=($(pgrep cp))
      njobs=${#list[@]}
      if [[ $njobs -lt ${njobMax} ]]; then
        break
      fi
    done
  fi
  echo ${i}
  nohup ./job.sh "${dpath}${i}" "${opath}/." > logs/${i}.log 2>&1&
done
