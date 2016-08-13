#!/bin/sh

export X509_USER_PROXY=/home-pbs/kskovpen/proxy/x509up_u7989

export LD_PRELOAD=/usr/lib64/libglobus_gssapi_gsi.so.4

WDIR=$(pwd)

line2=${line2}
fout=${fout}
isdata=${isdata}
noe=${noe}
xsec=${xsec}
dout=${dout}
sample=${sample}
isElectronStream=${isElectronStream}
isMuonStream=${isMuonStream}
isSig=${isSig}

export ROOTSYS=/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.06.00-ikhhed4
ls $ROOTSYS/bin/thisroot.sh
source $ROOTSYS/bin/thisroot.sh
rootV=$(root-config --version)
echo "ROOT v${rootV} has been set up"

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${dout}/../:${dout}/../obj

export LD_LIBRARY_PATH=\
/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gcc/5.3.0/lib64:\
/usr/lib64:\
/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gcc/5.3.0/lib:\
/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_12/external/slc6_amd64_gcc530/lib/:\
/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_12/lib/slc6_amd64_gcc530/:\
$LD_LIBRARY_PATH

export PATH=/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/gcc/5.3.0/bin:$PATH

stream=-1
if [[ ${isElectronStream} == 1 ]]; then
  stream=0
fi
if [[ ${isMuonStream} == 1 ]]; then
  stream=1
fi

echo "Executing .././NtupleProducer --file ${line2} --outfile ${fout} --isdata ${isdata} --noe ${noe} --xsec ${xsec} --nmax ${nmax} --stream ${stream} --issig ${isSig}"
time ${dout}/./NtupleProducer --file ${line2} --outfile ${fout} --isdata ${isdata} --noe ${noe} --xsec ${xsec} --nmax ${nmax} --stream ${stream} --issig ${isSig}
