#!/bin/env zsh

fpath="lists/"

# wms2 vo.sbg.in2p3.fr
# wms1 cms
#voName="cms"
voName="vo.sbg.in2p3.fr"

jname=$1

nmax=-1

fxsec="xsec.txt"
fstat="stat.txt"
fid="wmsid_${jname}.txt"
fre="wmsid_${jname}_RESUBMIT.txt"
treeName="FlatTree/tree"

doRe=0
if [[ -f ${fre} ]]; then
doRe=1
fi

rm -f ${fid}
rm -f logRF/*
wdir=SUBMITWMS
rm -rf ${wdir}
mkdir ${wdir}

#userareaSRM="srm://sbgse1.in2p3.fr:8446/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/bTag/HISTO_${jname}"
#userareaRF="/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/bTag/HISTO_${jname}"
#userareaRFLOG="/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/bTag/LOG_${jname}"

userareaRF="/opt/sbg/scratch1/${voName}/kskovpen/tH/${jname}DATA"
userareaRFLOG="/opt/sbg/scratch1/${voName}/kskovpen/tH/${jname}LOG"

#if [[ ${doRe} == 0 ]]; then
#/usr/bin/rfrm -rf ${userareaRF}
#/usr/bin/rfmkdir ${userareaRF}

#/usr/bin/rfrm -rf ${userareaRFLOG}
#/usr/bin/rfmkdir ${userareaRFLOG}

#rm -rf ${userareaRF}
#mkdir ${userareaRF}

#rm -rf ${userareaRFLOG}
#mkdir ${userareaRFLOG}
#fi

#echo "prepare LIBs"
#./prepareLib.zsh

glite-wms-job-delegate-proxy -e https://sbgwms2.in2p3.fr:7443/glite_wms_wmproxy_server -d kskovpen
#glite-wms-job-delegate-proxy -e https://sbgwms1.in2p3.fr:7443/glite_wms_wmproxy_server -d kskovpen
#glite-wms-job-delegate-proxy -d kskovpen

flist=$(ls ${fpath})
farr=("${(@f)$(echo $flist)}")
fint=2
ffirst=1
echo $flist | while read line
do

sample=$(echo $line | sed 's%.txt%%g' | sed 's%_ID.*%%g')
sampleID=$(echo $line | sed 's%.txt%%g')
fnext=$(echo ${farr[${fint}]} | sed 's%.txt%%g' | sed 's%_ID.*%%g')
linexsec=$(grep $sample $fxsec)
linestat=$(grep $sample $fstat)
noe=$(echo $linestat | awk '{print $2}')
xsec=$(echo $linexsec | awk '{print $2}')

if [[ $noe == "" ]]; then
noe=1
fi
if [[ $xsec == "" ]]; then
xsec=1
fi

fl=$(echo $sample | cut -c1-1)
fl2=$(echo $sample | cut -c1-10)
datamc=""
#if [[ $fl == "B" || $fl == "M" || $fl == "D" ]]; then
#isdata=1
#datamc="DATA"
#else
isdata=0
datamc="MC"
#fi

if [[ ${ffirst} == 1 ]]; then
mkdir ${wdir}/${sample}

#dire=$(rfdir ${userareaRF}/${sample} 2>&1)
dire=$(ls ${userareaRF}/${sample} 2>&1)
direFAIL=$(echo $dire | grep "No such")
#if [[ ${direFAIL} != "" && ${doRe} == 0 ]]; then
#/usr/bin/rfmkdir ${userareaRF}/${sample}
####mkdir ${userareaRF}/${sample}
#fi
jidx=0
ffirst=0
else
jidx=$[$jidx+1]
fi
fout=$(echo ${sampleID})
lout=$(echo ${sampleID})
cp j.jdl ${wdir}/${sample}/temp.jdl

cat ${wdir}/${sample}/temp.jdl | \
sed "s%line2%${line}%g" | \
sed "s%fout%${fout}%g" | \
sed "s%isdata%${isdata}%g" | \
sed "s%noe%${noe}%g" | \
sed "s%xsec%${xsec}%g" | \
sed "s%nmax%${nmax}%g" | \
sed "s%lout%${lout}%g" | \
sed "s%treeName%${treeName}%g" | \
sed "s%sample%${sample}%g" | \
sed "s%jname%${jname}%g" | \
sed "s%voName%${voName}%g" | \
sed "s%INPUTFILELIST%${fpath}${line}%g" \
> ${wdir}/${sample}/j_${jidx}.jdl

rm ${wdir}/${sample}/temp.jdl

if [[ ${fnext} != ${sample} ]]; then
rr=""
if [[ ${doRe} == 1 ]]; then
rr=$(grep ${sample} ${fre})
fi
if [[ ${rr} != "" || ${doRe} == 0 ]]; then
echo "$sample"
#glite-wms-job-submit -e https://sbgwms2.in2p3.fr:7443/glite_wms_wmproxy_server -a --collection ${wdir}/${sample}
#outp=$(glite-wms-job-submit -e https://sbgwms2.in2p3.fr:7443/glite_wms_wmproxy_server -a --collection ${wdir}/${sample} 2>&1 | grep "https://sbgwms2.in2p3.fr:9000")
#if [[ $sp2011 == 1 ]]; then
#echo "This is a special 2011 sample"
#fi
echo "xsec=$xsec noe=$noe"
#outp=$(glite-wms-job-submit -a --collection ${wdir}/${sample} 2>&1 | grep "https://sbgwms1.in2p3.fr:9000")
outp=$(glite-wms-job-submit -e https://sbgwms2.in2p3.fr:7443/glite_wms_wmproxy_server -a --collection ${wdir}/${sample} 2>&1 | grep "https://sbgwms2.in2p3.fr:9000")
#glite-wms-job-submit -a --collection ${wdir}/${sample}

#if [[ $outp == "" ]]; then
#echo "Input sandbox oversized"
#exit 1
#fi
echo "$sample   $outp" >> ${fid}
fi #rrdoRe
ffirst=1
fi

fint=$[$fint+1]

done
