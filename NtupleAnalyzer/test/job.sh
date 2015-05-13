#PBS -u kskovpen
#!/bin/bash

ilist=${par0}
tool=${par1}
fout=${par2}
nmax=${par3}
evc=${par4}
hdir=${par5}

cdir=${home}/../
NtupleDir=${home}/../../NtupleProducer/
export LD_LIBRARY_PATH=${cdir}:${NtupleDir}:$LD_LIBRARY_PATH

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

# tools: plot

${home}/.././Analyzer \
${ilist} \
${fout} \
${tool} \
${evc} \
${nmax} \
${hdir}

