#!/bin/env zsh

cp /tmp/x509up_u7989 /home-pbs/kskovpen/proxy/.

jName=${1}
if [[ ${jName} == "" ]]; then
  echo "Please specify the run name"
  exit 1
fi

#que="cms_local_short"
que="cms_local_mdm"
#que="cms_local"
#que="dteam"

export HOME=$(pwd)

dout="/home-pbs/kskovpen/tHFCNC2016/CMSSW_8_0_12/src/NtupleProducer/test/"
#dscr="/opt/sbg/scratch1/cms/kskovpen/tHFCNC/"
dscr="/home-pbs/kskovpen/tHFCNC2016/CMSSW_8_0_12/src/NtupleProducer/test/"

fpath="${HOME}/lists/"

runName="${dscr}toy${jName}"
logName="${dscr}log${jName}"

rm -rf ${runName}
mkdir ${runName}
rm -rf ${logName}
mkdir ${logName}

nmax=-1

fxsec="table.txt"

#flist=$(ls ${fpath} | egrep -e "tH|TT")
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

  sigfl=$(echo $sample | grep "TH")
  isSig=0
  if [[ $sigfl != "" ]]; then
    isSig=1
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

  echo "${dataset}: $noe $xsec isdata=${isdata} isElecStream=${isElectronStream} isMuonStream=${isMuonStream} isSig=${isSig}"
  qsub -N TFCNH -q ${que} -o ${logName}/${sample}.log -j oe job.sh \
-v dout=${dout},line2=${fpath}${line},fout=${fout},noe=${noe},xsec=${xsec},isdata=${isdata},sample=${sample},nmax=${nmax},\
isElectronStream=${isElectronStream},isMuonStream=${isMuonStream},isSig=${isSig}
#  exit
done
