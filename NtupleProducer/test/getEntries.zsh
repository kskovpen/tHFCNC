#!/bin/env zsh

doCheck=0

datapath="listsSTAT/"

tmpPath="/tmp/kskovpen/Entries"

rm -rf ${tmpPath}
mkdir ${tmpPath}

li=$(ls ${datapath} | grep "Kappa")
fout="stat.txt"
rm -rf bad.txt

rm -f ${fout}

echo $li | while read line
do

  isdata=$(echo $line | egrep -e "Data")
  if [[ ${isdata} != "" ]]; then
    fname=$(echo $line | sed 's%.txt%%g')
    echo "${fname}       666" >> ${fout}
    continue
  else
  
    fin=$(echo ${datapath}${line})
    fl=${fin}
  
    fname=$(echo $line | sed 's%.txt%%g' | sed 's%_ID.*%%g')
    echo ${fname}
  
    fpath=$(head -1 ${fl} | sed 's%output_1.*%%g' | sed "s%root://sbgse1.in2p3.fr/%%g")
  
    li=($(/usr/bin/rfdir ${fpath} | awk '{print $9}'))

    fst=()
    idx=1
    for i in $li
    do
      fil="root://sbgse1.in2p3.fr/"${fpath}${i}
      stat=$(root -b -l getEntriesRoot.C\(\""${fil}"\"\) | grep -v "Warning" | \
grep -v "Processing" | sed '/^$/d')
      fst[${idx}]=${stat}
      idx=$[${idx}+1]    
    done
    sum=$((${(j[+])fst}))

    echo "${fname}       ${sum}" | sed 's%Processing.*%%g' >> ${fout}

  fi
  
done
