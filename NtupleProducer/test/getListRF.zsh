#!/bin/env zsh

fpath="/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/FlatTree/MantaRay-patch8-v20151025/"

liDATA=$(/usr/bin/rfdir ${fpath} | grep "BTagMu")
liMC=$(/usr/bin/rfdir ${fpath} | grep "QCD" | grep "MuEnriched")

fpathDATAXRD=$(echo ${fpath} | sed "s%/dpm%root://sbgse1.in2p3.fr//dpm%g")
fpathMCXRD=$(echo ${fpath} | sed "s%/dpm%root://sbgse1.in2p3.fr//dpm%g")

#nFilesDATA=10 # per job
#nFilesMC=10
nFilesDATA=100000 # per job
nFilesMC=100000
outDir="lists/"

rm -rf ${outDir}
mkdir ${outDir}

# DATA

rm -f /tmp/tempDATA.txt
echo $liDATA | while read line
do
d1=$(echo $line | awk '{print $9}')
liDATA2=$(/usr/bin/rfdir ${fpath}${d1})
d2=$(echo $liDATA2 | awk '{print $9}')
liDATA3=$(/usr/bin/rfdir ${fpath}${d1}/${d2})
d3=$(echo $liDATA3 | awk '{print $9}')
liDATA4=$(/usr/bin/rfdir ${fpath}${d1}/${d2}/${d3})
d4=$(echo $liDATA4 | awk '{print $9}')
liDATA5=$(/usr/bin/rfdir ${fpath}${d1}/${d2}/${d3}/${d4})
echo $liDATA5 | while read line2
do
f1=$(echo $line2 | awk '{print $9}')
file=$(echo ${fpathDATAXRD}${d1}/${d2}/${d3}/${d4}/${f1})
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

# MC

rm -f /tmp/tempMC.txt
echo $liMC | while read line
do
d1=$(echo $line | awk '{print $9}')
liMC2=$(/usr/bin/rfdir ${fpath}${d1})
d2=$(echo $liMC2 | awk '{print $9}')
liMC3=$(/usr/bin/rfdir ${fpath}${d1}/${d2})
d3=$(echo $liMC3 | awk '{print $9}')
liMC4=$(/usr/bin/rfdir ${fpath}${d1}/${d2}/${d3})
d4=$(echo $liMC4 | awk '{print $9}')
liMC5=$(/usr/bin/rfdir ${fpath}${d1}/${d2}/${d3}/${d4})
echo $liMC5 | while read line2
do
f1=$(echo $line2 | awk '{print $9}')
file=$(echo ${fpathMCXRD}${d1}/${d2}/${d3}/${d4}/${f1})
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

