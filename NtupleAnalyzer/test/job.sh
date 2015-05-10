#PBS -u kskovpen
#!/bin/bash

ilist=${1}
tool=${2}
fout=${3}
nmax=${4}
evc=${5}

cdir=$(pwd)/../
NtupleDir=$(pwd)/../../NtupleProducer/
export LD_LIBRARY_PATH=${cdir}:${NtupleDir}:$LD_LIBRARY_PATH

# tools: plot

./../Analyzer \
${ilist} \
${fout} \
${tool} \
${evc} \
${nmax}

