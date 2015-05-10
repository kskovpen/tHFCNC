#!/bin/sh

export LFC_HOST=sbglfc1.in2p3.fr

echo "=====  Begin  =====" 
date
echo "The program is running on $HOSTNAME"
date
echo "=====  End  ====="

lsb_release -a

WDIR=$(pwd)

anaName=${1}
runName=${2}
voName=${3}
dirli=${4}

echo "Running WMS output directory initialisation for: ${anaName} ${runName} ${voName}"

odir="/opt/sbg/scratch1/${voName}/kskovpen/${anaName}"

# comment these two lines if don't want to clean dirs
rm -rf ${odir}
mkdir ${odir}

if [[ ! -d ${odir} ]]; then
  mkdir ${odir}
fi

odirDATA="/opt/sbg/scratch1/${voName}/kskovpen/${anaName}/${runName}DATA"
rm -rf ${odirDATA}
mkdir ${odirDATA}

for i in $(echo $dirli | tr "XXX" "\n")
do
  if [[ ! -d ${odirDATA}/${i} ]]; then
    mkdir ${odirDATA}/${i}
  fi
done

odirLOG="/opt/sbg/scratch1/${voName}/kskovpen/${anaName}/${runName}LOG"
rm -rf ${odirLOG}
mkdir ${odirLOG}
