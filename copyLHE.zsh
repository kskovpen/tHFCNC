#!/bin/env zsh

#idir="/dpm/in2p3.fr/home/cms/kskovpen/tHFCNC/Gridpacks/"
#odir="/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/tHFCNCPROD/"

#proc="tHToBB-Kappa"
#proc="TTtoTH-Kappa"
#proc="tHq"
proc="TTtoHToBB-1L-Kappa-hct_CMS"

idir="/dpm/in2p3.fr/home/cms/kskovpen/tHFCNC/Gridpacks/"
#idir="/dpm/in2p3.fr/home/cms/FCNC_13TeV/Gridpacks/"
odir="/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/tHFCNCPROD/"

rm -rf /tmp/kskovpen/*

ldir=($(/usr/bin/rfdir ${idir} | awk '{print $9}' | grep ${proc}))
for i in $ldir
do
  echo $i
  outdi=$(echo $i)
#  outdi=$(echo $i | sed "s%ToBB%%g")
  /usr/bin/rfrm -rf ${odir}${outdi}
  /usr/bin/rfmkdir ${odir}${outdi}
  fl=($(/usr/bin/rfdir ${idir}${i} | awk '{print $9}' | grep "lhe.gz"))
  ilhe=1
  for j in ${fl}
  do
#    if [[ ${ilhe} == 11 ]]; then
#      break
#    fi
    fname=${idir}${i}/${j}
    /usr/bin/rfcp ${fname} /tmp/kskovpen/.
    gzip -d /tmp/kskovpen/${j}
    fnameMod=$(echo ${j} | sed "s%.gz%%g")
    /usr/bin/rfcp /tmp/kskovpen/${fnameMod} ${odir}${outdi}/${fnameMod}
    rm -rf /tmp/kskovpen/*
    ilhe=$[$ilhe+1]
  done  
done
