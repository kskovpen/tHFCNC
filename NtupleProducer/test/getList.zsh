#!/bin/env zsh

fpath="/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/FlatTree/MantaRay-v20150429_MERGED/"

liDATA=($(/usr/bin/rfdir ${fpath} | grep "Data" | awk '{print $9}'))
liMC=($(/usr/bin/rfdir ${fpath} | awk '{print $9}'))

fpathXRD=$(echo ${fpath} | sed "s%/dpm%root://sbgse1.in2p3.fr//dpm%g")

#nFilesDATA=1 # per job
#nFilesMC=10000
nFilesMC=1
#outDir="listsSTAT/"
outDir="lists/"

rm -f ${outDir}*

rm -f /tmp/tempDATA.txt
for line in $liDATA
do
d1=$(echo $line)
liDATA2=$(/usr/bin/rfdir ${fpath}${d1})
echo $liDATA2 | while read line2
do
f1=$(echo $line2 | awk '{print $9}')
file=$(echo ${fpathXRD}${d1}/${f1})
echo "${file}" >> /tmp/tempDATA.txt
done
split -a 5 -l ${nFilesDATA} -d /tmp/tempDATA.txt /tmp/${d1}_
lsfi=$(ls /tmp/${d1}_*)
jid=0
echo $lsfi | while read fil
do
mv ${fil} ${outDir}${d1}_ID${jid}.txt
jid=$[$jid+1]
done
rm -f /tmp/tempDATA.txt
done

rm -f /tmp/tempMC.txt
for line in $liMC
do
d1=$(echo $line)
liMC2=$(/usr/bin/rfdir ${fpath}${d1})
echo $liMC2 | while read line2
do
f1=$(echo $line2 | awk '{print $9}')
file=$(echo ${fpathXRD}${d1}/${f1})
echo "${file}" >> /tmp/tempMC.txt
done
split -a 5 -l ${nFilesMC} -d /tmp/tempMC.txt /tmp/${d1}_
lsfi=$(ls /tmp/${d1}_*)
jid=0
echo $lsfi | while read fil
do
mv ${fil} ${outDir}${d1}_ID${jid}.txt
jid=$[$jid+1]
done
rm -f /tmp/tempMC.txt
done

