#!/bin/env zsh

#dpath="/home/kskovpen/work/testarea/Limit2012/mclimit/run/limitInput/"
dpath="/home/kskovpen/work/testarea/Limit2012/mclimit/run/webPlot/"
#fname="limitInputLRSMWR.root"
fname="limitInput.root"
dist="mlljj"
#sig="ZR400NR50"
sig="WR2000NR50"

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/kskovpen/work/testarea/Limit2012/mclimit:$ROOTSYS/lib

rand=666
step=0.001
doProf=0

#./toy \
#${dpath}${fname}@${dpath}${fname}@${dpath}${fname}@${dpath}${fname} \
#${dpath}${fname}@${dpath}${fname}@${dpath}${fname}@${dpath}${fname} \
#0 1 10 0.0001 0 1 0 1. 0 1 1 666 "${sig}" "ee_ss" "mm_ss" "ee_os" "mm_os" "X" "X" 1. 1. 1. 1. 1. 1. \
#"jge2_ge_mll110_ge_mlljjjj200" "jge2_ge_mll110_ge_mlljjjj200" \
#"jge2_ge_mll110_ge_st200_ge_mlljjjj200" "jge2_ge_mll110_ge_st200_ge_mlljjjj200" \
#"X" "X" "${dist}"
#| grep -v "V" | grep -v "====" | grep -v "NEW MINIMUM" | grep -v "MUST BE" | grep -v "^$"

#./toy \
#${dpath}${fname}@${dpath}${fname}@${dpath}${fname}@${dpath}${fname} \
#${dpath}${fname}@${dpath}${fname}@${dpath}${fname}@${dpath}${fname} \
#0 1 50 0.0001 0 1 0 1. 0 1 1 666 "${sig}" "ee_ss" "mm_ss" "ee_os" "mm_os" "X" "X" 1. 1. 1. 1. 1. 1. \
#"jge1_ge_mll110_ge_mlljj400" \
#"jge1_ge_mll110_ge_mlljj400" \
#"jge1_ge_mll110_ge_st400_ge_mlljj400" \
#"jge1_ge_mll110_ge_st400_ge_mlljj400" \
#"X" "X" "${dist}"

./toy \
${dpath}${fname} \
${dpath}${fname} \
0 2 1000 ${step} ${doProf} 1 0 1. 0 1 1 ${rand} "${sig}" "mm_ss" "X" "X" "X" "X" "X" 1. 1. 1. 1. 1. 1. \
"jge1_ge_mll110_ge_mlljj400" \
"X" \
"X" \
"X" \
"X" "X" "${dist}"
