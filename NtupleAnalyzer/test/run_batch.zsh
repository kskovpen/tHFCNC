#!/bin/env zsh

cp /tmp/x509up_u20657 /user/kskovpen/proxy/.

jName=${1}
if [[ ${jName} == "" ]]; then
  echo "Please specify the run name"
  exit 1
fi

que="localgrid"

tool="plot"
nmax=-1
home=$(pwd)
evec=0

export HOME=$(pwd)

dout="/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/tHFCNC/NtupleAnalyzer/test/"

fpath="${HOME}/lists/"

runName="hist${jName}"
logName="log${jName}"

rm -rf ${runName}
mkdir ${runName}
rm -rf ${logName}
mkdir ${logName}

flist=$(ls ${fpath})

echo $flist | while read line
do
  jidx=0
  sample=$(echo $line | sed 's%.txt%%g')
  dataset=$(echo $sample | sed 's%_ID..*%%g')
  if [[ ! -d ${runName}/${dataset} ]]; then
    mkdir ${runName}/${dataset}
  fi
  fl=$(echo $sample | cut -c1-1)
  fl2=$(echo $sample | cut -c1-11)

  fout=$(echo ${runName}/${dataset}/${line}_${jidx} | sed 's%.txt%%g')
  lout=$(echo ${line}_${jidx} | sed 's%.txt%%g')

  echo "${sample}"
  while [[ $(qsub -N TFCNHANA -q ${que} -o ${logName}/${sample}.log -j oe job.sh \
-l walltime=6:00:00 \
-v dout=${dout},line2=${fpath}${line},fout=${fout},tool=${tool},nmax=${nmax},home=${home},evec=${evec} 2>&1 | grep "Invalid credential") != "" ]];
  do echo "one more try";
  done
done
