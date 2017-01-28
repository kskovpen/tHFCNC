#!/bin/env zsh

fpath="srm://maite.iihe.ac.be:8443/pnfs/iihe/cms/store/user/kskovpen/FlatTree/Sailfish-patch3-v20170128/"
fpathR=$(echo ${fpath} | sed 's%8443/pnfs%8443//pnfs%g')

dataStr="SingleElectron|SingleMuon"

liDATA=($(gfal-ls ${fpath} | egrep -e "${dataStr}"))
liMC=($(gfal-ls ${fpath} | egrep -v "${dataStr}"))

nFilesDATA=20 # per job
nFilesMC=3
outDir="lists/"

rm -rf ${outDir}
mkdir ${outDir}

# DATA

rm -f /tmp/tempDATA.txt
for line in $liDATA
do
  echo $line
  d1=$(echo $line)
  liDATA2=$(gfal-ls ${fpath}${d1})
  d2=($(echo $liDATA2))
  for id2 in $d2
  do
    liDATA3=$(gfal-ls ${fpath}${d1}/${id2})
    d3=$(echo $liDATA3)
    liDATA4=($(gfal-ls ${fpath}${d1}/${id2}/${d3}))
    for d4 in $liDATA4
    do
      liDATA5=($(gfal-ls ${fpath}${d1}/${id2}/${d3}/${d4}))
      for line2 in $liDATA5
      do
        f1=$(echo $line2)
        file=$(echo ${fpathR}${d1}/${id2}/${d3}/${d4}/${f1})
	isFailed=$(echo $file | grep failed)
	if [[ ${isFailed} == "" ]]; then
          echo "${file}" >> /tmp/tempDATA.txt
	fi
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
  liMC2=$(gfal-ls ${fpath}${d1})
  d2=($(echo $liMC2))
  for id2 in $d2
  do
    echo $id2
    liMC3=$(gfal-ls ${fpath}${d1}/${id2})
    d3=$(echo $liMC3)
    liMC4=($(gfal-ls ${fpath}${d1}/${id2}/${d3}))
    for d4 in $liMC4
    do
      liMC5=($(gfal-ls ${fpath}${d1}/${id2}/${d3}/${d4}))
      for line2 in $liMC5
      do
        f1=$(echo $line2)
        file=$(echo ${fpathR}${d1}/${id2}/${d3}/${d4}/${f1})
	isFailed=$(echo $file | grep failed)
	if [[ ${isFailed} == "" ]]; then
          echo "${file}" >> /tmp/tempMC.txt
	fi
      done
    done
    split -a 5 -l ${nFilesMC} -d /tmp/tempMC.txt /tmp/${d1}_
    lsfi=($(ls /tmp/${d1}_*))
    jid=0
    for fil in $lsfi
    do
      sampStrip=$(echo $id2 | sed "s%RunIISummer16MiniAODv2_.*%%g" | sed "s%_MINIAODSIM_.*%%g" | sed "s%kskovpen.*%%g")
      mv ${fil} ${outDir}${d1}${sampStrip}_ID${jid}.txt
      jid=$[$jid+1]
    done
    rm -f /tmp/tempMC.txt
  done
done

