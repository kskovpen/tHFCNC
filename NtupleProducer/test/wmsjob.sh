#!/bin/sh

export LFC_HOST=sbglfc1.in2p3.fr

echo "=====  Begin  =====" 
date
echo "The program is running on $HOSTNAME"
date
echo "=====  End  ====="

lsb_release -a

WDIR=$(pwd)

lfile="NtupleProducer.log"

#echo "list files in my user directory"
#srmls srm://sbgse1.in2p3.fr:8446/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen

line2=${1}
fout=${2}
jname=${3}
#isdata=${3}
xsec=${4}
noe=${5}
#nmax=${6}
#lout=${7}
#sample=${8}
voName=${6}
treeName=${7}

export ROOTSYS=/cvmfs/cms.cern.ch/slc6_amd64_gcc481/lcg/root/5.34.18-cms12
ls $ROOTSYS/bin/thisroot.sh
source $ROOTSYS/bin/thisroot.sh
rootV=$(root-config --version)
echo "ROOT v${rootV} has been set up"

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${WDIR}

export LD_LIBRARY_PATH=\
/cvmfs/cms.cern.ch/slc6_amd64_gcc481/external/gcc/4.8.1/lib64:\
/cvmfs/cms.cern.ch/slc6_amd64_gcc481/external/gcc/4.8.1/lib:\
/cvmfs/cms.cern.ch/slc6_amd64_gcc481/cms/cmssw/CMSSW_7_2_3/external/slc6_amd64_gcc481/lib/:\
/cvmfs/cms.cern.ch/slc6_amd64_gcc481/cms/cmssw/CMSSW_7_2_3/lib/slc6_amd64_gcc481/:\
$LD_LIBRARY_PATH

export PATH=/cvmfs/cms.cern.ch/slc6_amd64_gcc481/external/gcc/4.8.1/bin:$PATH

# this allows RFIO access on sl6 (DON'T USE FOR XROOTD)
#export LD_PRELOAD=/usr/lib64/libglobus_gssapi_gsi.so.4

chmod a+x NtupleProducer

#srmcp -retry_num 4 -retry_timeout 30000 srm://sbgse1.in2p3.fr:8446${finname} file:///${WDIR}/test.root

#tar -zxvf LIB.tar.gz
#mv TEMPLIB/* .
#rm -rf TEMPLIB

#echo "Executing ../NtupleProducer --file ${line2} --tree ${treeName} ${fout} ${xsec} ${noe}"
#./NtupleProducer --file ${line2} --tree ${treeName} ${fout} ${xsec} ${noe} 2>&1 | tee ${lfile}
echo "Executing ../NtupleProducer --file ${line2} --tree ${treeName} --noe ${noe} --xsec ${xsec}"
./NtupleProducer --file "${line2}" --tree "${treeName}" --noe "${noe}" --xsec "${xsec}" 2>&1 | tee ${lfile}

ls

sample=$(echo $fout | sed 's%_ID.*%%g')

cp ${WDIR}/output.root /opt/sbg/scratch1/${voName}/kskovpen/tH/${jname}DATA/${sample}/${fout}.root
cp ${WDIR}/${lfile} /opt/sbg/scratch1/${voName}/kskovpen/tH/${jname}LOG/${fout}.log

#srmcp -retry_num 4 -retry_timeout 30000 file:///${WDIR}/hist.root srm://sbgse1.in2p3.fr:8446/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/bTag/HISTO_${jname}/${sample}/$lout.root
#srmcp -retry_num 4 -retry_timeout 30000 file:///${WDIR}/${lfile} srm://sbgse1.in2p3.fr:8446/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/bTag/LOG_${jname}/${lout}.log

rm -f ${lfile}
rm -f output.root
rm NtupleProducer
rm $line2
rm *.so

