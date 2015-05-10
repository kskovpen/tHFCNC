#!/bin/sh

echo "running on $HOSTNAME"

doutput="run_${label}"
dout="/gcf/atlas/data/Limits/${doutput}/"
wdpath="/home/kskovpen/work/testarea/Limit2012/mclimit"
PBS_O_WORKDIR="${wdpath}/run"

#dpath="/home/kskovpen/work/testarea/Limit2012/mclimit/run/limitInput"
dpath="/home/kskovpen/work/testarea/Limit2012/mclimit/run/webPlot/"
if [[ $mix == 0 ]]; then
finput="limitInput${typeSig}.root"
else
finput="limitInput${typeSig}Mix.root"
fi

loc=("/dev/shm" "/atlas/data")

for i in "${loc[@]}"
do
scratch=${i}/batchLimit
if [ ! -d ${scratch} ]; then
    mkdir ${scratch}
fi
scratch=${i}/batchLimit/${doutput}
if [ ! -d ${scratch} ]; then
mkdir ${scratch}
fi
scratch=${i}/batchLimit/${doutput}/${name}
if [ ! -d ${scratch} ]; then
mkdir ${scratch}
fi
scratch=${i}/batchLimit/${doutput}/${name}_${jid}_${label}
if [ ! -d ${scratch} ]; then
mkdir ${scratch}
fi
done

scratch=${loc[0]}/batchLimit/${doutput}/${name}_${jid}_${label}

gpath="/atlas/data/Limits/"
output=${gpath}/${doutput}
[ ! -d ${output} ] && mkdir ${output}
[ ! -d ${output}/${name}_NPE${npe}_RAND${rand} ] && mkdir ${output}/${name}_NPE${npe}_RAND${rand}
#[ ! -d ${output}/${name} ] && mkdir ${output}/${name}

echo "----- Setting up things:"

cd ~/

export ATLAS_LOCAL_ROOT_BASE=/local_atlas/software/tier3/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'

setupATLAS

localSetupROOT --rootVersion="5.34.03-x86_64-slc5-gcc4.3"

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/kskovpen/work/testarea/Limit2012/mclimit:$ROOTSYS/lib

cd ${scratch}

#cp -f ${wdpath}/libMCL.so .
cp -f ${wdpath}/run/toy .

curdir=$(pwd)

echo "${curdir}"

export LD_LIBRARY_PATH=${curdir}:${LD_LIBRARY_PATH}:$ROOTSYS/lib

echo "----- Files used:"
ls .

f1="${dpath}/${finput}"
f2="${dpath}/${finput}"

if [[ $chan2 != "X" ]]; then
f1=$f1"@${dpath}/${finput}"
f2=$f2"@${dpath}/${finput}"
fi
if [[ $chan3 != "X" ]]; then
f1=$f1"@${dpath}/${finput}"
f2=$f2"@${dpath}/${finput}"
fi
if [[ $chan4 != "X" ]]; then
f1=$f1"@${dpath}/${finput}"
f2=$f2"@${dpath}/${finput}"
fi
if [[ $chan5 != "X" ]]; then
f1=$f1"@${dpath}/${finput}"
f2=$f2"@${dpath}/${finput}"
fi
if [[ $chan6 != "X" ]]; then
f1=$f1"@${dpath}/${finput}"
f2=$f2"@${dpath}/${finput}"
fi

./toy \
$f1 \
$f2 \
0 2 ${npe} 0.0001 0 1 0 ${sfsig} 0 1 1 ${rand} ${name} ${chan1} ${chan2} ${chan3} ${chan4} ${chan5} ${chan6} \
${sfsig1} ${sfsig2} ${sfsig3} ${sfsig4} ${sfsig5} ${sfsig6} \
${sel1} ${sel2} ${sel3} ${sel4} ${sel5} ${sel6} ${dist} \
>& ${scratch}/${name}.log

# 0 2 2000 0.0001 0 1 0 1. 0 1 1 667

#mv ${scratch}/${name}.log ${dout}/${name}/.
#mv ${scratch}/output.root ${dout}/${name}/.
mv ${scratch}/${name}.log ${dout}/${name}_NPE${npe}_RAND${rand}/.
mv ${scratch}/output.root ${dout}/${name}_NPE${npe}_RAND${rand}/.

rm -rf ${scratch}/*
