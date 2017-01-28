#!/bin/env zsh

cp /tmp/x509up_u20657 /user/kskovpen/proxy/.

jName=${1}
if [[ ${jName} == "" ]]; then
  echo "Please specify the run name"
  exit 1
fi

que="localgrid"

export HOME=$(pwd)

dout="/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/tHFCNC/NtupleProducer/test/"
dscr="/user/kskovpen/analysis/tHFCNC/CMSSW_8_0_25/src/tHFCNC/NtupleProducer/test/"

fpath="${HOME}/lists/"

runName="${dscr}toy${jName}"
logName="${dscr}log${jName}"

rm -rf ${runName}
mkdir ${runName}
rm -rf ${logName}
mkdir ${logName}

nmax=-1

fxsec="table.txt"

flist=$(ls ${fpath})

echo $flist | while read line
do
  jidx=0
  sample=$(echo $line | sed 's%.txt%%g')
  dataset=$(echo $sample | sed 's%_ID..*%%g')
  if [[ ! -d ${runName}/${dataset} ]]; then
    mkdir ${runName}/${dataset}
  fi
  linexsec=$(grep ${dataset}XXX $fxsec)
  noe=$(echo $linexsec | awk '{print $3}')
  xsec=$(echo $linexsec | awk '{print $2}')
  if [[ $noe == "" ]]; then
    noe=1
  fi
  if [[ $xsec == "" ]]; then
    xsec=1
  fi
  fl=$(echo $sample | grep "Run2016")
  datamc=""
  if [[ $fl != "" ]]; then
    isdata=1
    datamc="DATA"
    nmax=${nmax}
  else
    isdata=0
    datamc="MC"
    nmax=${nmax}
  fi

  sigfl=$(echo $sample | grep "FCNC")
  isSig=0
  if [[ $sigfl != "" ]]; then
    isSig=1
  fi

  ttbarfl=$(echo $sample | egrep -e "TT_Tune")
  isTTBar=0
  if [[ $ttbarfl != "" ]]; then
    isTTBar=1
  fi

  fout=$(echo ${runName}/${dataset}/${line}_${jidx} | sed 's%.txt%%g')
  lout=$(echo ${line}_${jidx} | sed 's%.txt%%g')

  isElectronStreamStr=$(echo ${dataset} | grep "SingleElectron")
  if [[ ${isElectronStreamStr} != "" ]]; then
    isElectronStream=1
  else
    isElectronStream=0
  fi

  isMuonStreamStr=$(echo ${dataset} | grep "SingleMuon")
  if [[ ${isMuonStreamStr} != "" ]]; then
    isMuonStream=1
  else
    isMuonStream=0
  fi

# still does not work -l host=\!node23-5.wn.iihe.ac.be

  echo "${dataset}: $noe $xsec isdata=${isdata} isElecStream=${isElectronStream} isMuonStream=${isMuonStream} isSig=${isSig} isTTBar=${isTTBar}"
  while [[ $(qsub -N TFCNH -q ${que} -o ${logName}/${sample}.log -j oe job.sh \
-l walltime=05:00:00 \
-v dout=${dout},line2=${fpath}${line},fout=${fout},noe=${noe},xsec=${xsec},isdata=${isdata},sample=${sample},nmax=${nmax},\
isElectronStream=${isElectronStream},isMuonStream=${isMuonStream},isSig=${isSig},isTTBar=${isTTBar} 2>&1 | grep "Invalid credential") != "" ]];
  do;
  done
#  exit
done
