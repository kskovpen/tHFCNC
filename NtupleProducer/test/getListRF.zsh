#!/bin/env zsh

fpath="/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/FlatTree/Medusa-patch4-v20160726/"

dataStr="SingleElectron|SingleMuon"

#liDATA=($(/usr/bin/rfdir ${fpath} | egrep -e "$dataStr" | awk '{print $9}'))
liDATA=($(/usr/bin/rfdir ${fpath} | egrep -e "$dataStr" | awk '{print $9}' | grep "XXX"))
#liMC=($(/usr/bin/rfdir ${fpath} | egrep -v "$dataStr" | awk '{print $9}' | egrep -e "TT_TuneCUETP8M1_13TeV-powheg-pythia8|WJetsToLNu_TuneCUETP8M1_13TeV|TH|ST|WW_TuneCUETP8M1_13TeV-pythia8|ZZ_TuneCUETP8M1_13TeV-pythia8|WZ_TuneCUETP8M1_13TeV-pythia8|DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8|DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"))
liMC=($(/usr/bin/rfdir ${fpath} | egrep -v "$dataStr" | awk '{print $9}' | egrep -e "TH_|TT_TuneCUETP8M1_13TeV-powheg-pythia8"))
#liMC=($(/usr/bin/rfdir ${fpath} | egrep -v "$dataStr" | awk '{print $9}'))
#liMC=($(/usr/bin/rfdir ${fpath} | egrep -v "$dataStr" | awk '{print $9}' | grep "ST_TH_1L3B" | egrep -v "ST_TH_1L3B_Hct"))

fpathDATAXRD=$(echo ${fpath} | sed "s%/dpm%root://sbgse1.in2p3.fr//dpm%g")
fpathMCXRD=$(echo ${fpath} | sed "s%/dpm%root://sbgse1.in2p3.fr//dpm%g")

nFilesDATA=60 # per job
nFilesMC=10
outDir="lists/"

rm -rf ${outDir}
mkdir ${outDir}

# DATA

rm -f /tmp/tempDATA.txt
for line in $liDATA
do
  echo $line
  d1=$(echo $line)
  liDATA2=$(/usr/bin/rfdir ${fpath}${d1} | awk '{print $9}')
  d2=($(echo $liDATA2))
  for id2 in $d2
  do
    liDATA3=$(/usr/bin/rfdir ${fpath}${d1}/${id2})
    d3=$(echo $liDATA3 | awk '{print $9}')
    liDATA4=($(/usr/bin/rfdir ${fpath}${d1}/${id2}/${d3} | awk '{print $9}'))
    for d4 in $liDATA4
    do
      liDATA5=($(/usr/bin/rfdir ${fpath}${d1}/${id2}/${d3}/${d4} | awk '{print $9}'))
      for line2 in $liDATA5
      do
        f1=$(echo $line2)
        file=$(echo ${fpathDATAXRD}${d1}/${id2}/${d3}/${d4}/${f1})
        echo "${file}" >> /tmp/tempDATA.txt
      done
    done
    split -a 5 -l ${nFilesDATA} -d /tmp/tempDATA.txt /tmp/${d1}_
    lsfi=($(ls /tmp/${d1}_*))
    jid=0
    for fil in $lsfi
    do
      if [[ $#d2 != 1 ]]; then
        mv ${fil} ${outDir}${d1}_${id2}_ID${jid}.txt
      else
        mv ${fil} ${outDir}${d1}_ID${jid}.txt
      fi
      jid=$[$jid+1]
    done
    rm -f /tmp/tempDATA.txt
  done
done

# MC

rm -f /tmp/tempMC.txt
for line in $liMC
do
  echo $line
  d1=$(echo $line)
  liMC2=$(/usr/bin/rfdir ${fpath}${d1} | awk '{print $9}')
  d2=($(echo $liMC2 | egrep -e "PUSpring16_80X|kskovpen"))
  for id2 in $d2
  do
    echo $id2
    liMC3=$(/usr/bin/rfdir ${fpath}${d1}/${id2})
    d3=$(echo $liMC3 | awk '{print $9}')
    liMC4=($(/usr/bin/rfdir ${fpath}${d1}/${id2}/${d3} | awk '{print $9}'))
    for d4 in $liMC4
    do
      liMC5=($(/usr/bin/rfdir ${fpath}${d1}/${id2}/${d3}/${d4} | awk '{print $9}'))
      for line2 in $liMC5
      do
        f1=$(echo $line2)
        file=$(echo ${fpathMCXRD}${d1}/${id2}/${d3}/${d4}/${f1})
        echo "${file}" >> /tmp/tempMC.txt
      done
    done
    split -a 5 -l ${nFilesMC} -d /tmp/tempMC.txt /tmp/${d1}_
    lsfi=($(ls /tmp/${d1}_*))
    jid=0
    for fil in $lsfi
    do
      sampStrip=$(echo $id2 | sed "s%RunIIFall15MiniAODv2_.*%%g" | sed "s%RunIISpring16MiniAODv2_.*%%g" | sed "s%_MINIAODSIM_.*%%g" | sed "s%kskovpen.*%%g")
      mv ${fil} ${outDir}${d1}${sampStrip}_ID${jid}.txt
      jid=$[$jid+1]
    done
    rm -f /tmp/tempMC.txt
  done
done

