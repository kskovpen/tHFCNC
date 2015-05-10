#!/bin/env zsh

#proc="tH-Kappa-gct"
proc="tHq-tchan"
hdir=$(pwd)
flist="LHEFiles/${proc}.txt"
tdir="/opt/sbg/data/sbgse24/data1/cms/kskovpen/mergeLHE"

rm -rf ${tdir}
mkdir ${tdir}

farr=()
ftxt="merge.txt"
rm -f ${ftxt}

idx=1
cat $flist | while read line
do
  farr[${idx}]=$line
  fstrip=$(echo $line | sed "s%.*events%events%g")
  echo $fstrip >> ${ftxt}
  idx=$[${idx}+1]
done

mv ${ftxt} ${tdir}/

for i in $farr
do
  xrdcp $i ${tdir}/
done

cd ${tdir}
cp ${hdir}/mergeLheFiles .
./mergeLheFiles ${ftxt}
outf="root://sbgse1.in2p3.fr//store/user/kskovpen/tHFCNCPROD/${proc}_merged.lhe"
/usr/bin/rfrm /dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/tHFCNCPROD/${proc}_merged.lhe
xrdcp out.lhe ${outf}
cd ${hdir}
rm -rf ${tdir}
