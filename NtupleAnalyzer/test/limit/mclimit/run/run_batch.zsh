#!/bin/env zsh

#date="20130424_LIMIT_EM_OS_MIX"
date="20130610_LIMIT_MM_SS_NOMIX_EXP"
label="${date}"
dist="mlljj"
typeSig="LRSMWR" # LRSMWR, LRSMZR
mix=0 # 0,1
sfsig=1.
#sfsig=1
all=0 # all mass points or only chosen
#npearr=(1000 5000 10000 25000 50000 100000 500000 1000000 5000000 10000000 50000000 100000000)
npearr=(1000 2000 3000 4000 5000)
randarr=(666 667 668 669 670 671 672 673 674 675)

loc="/dev/shm"

chan1="mm_ss"
chan2="X"
chan3="X"
chan4="X"
chan5="X"
chan6="X"

if [[ $typeSig == "LRSMWR" ]] then
#sel1="jge1_ge_mll110_ge_mlljj400"
#sel2="jge1_ge_mll110_ge_mlljj400"
#sel3="jge1_ge_mll110_ge_st400_ge_mlljj400"
#sel4="jge1_ge_mll110_ge_st400_ge_mlljj400"

#sel1="jge1_ge_mll110_ge_mlljj400"
#sel2="jge1_ge_mll110_ge_mlljj400"
#sel3="jge1_ge_mll110_ge_mlljj400"
#sel4="jge1_ge_mll110_ge_st400_ge_mlljj400"
#sel5="jge1_ge_mll110_ge_st400_ge_mlljj400"
#sel6="jge1_ge_mll110_ge_st400_ge_mlljj400"

sel1="jge1_ge_mll110_ge_mlljj400"
sel2="X"
sel3="X"
sel4="X"
elif [[ $typeSig == "LRSMZR" ]] then
#sel1="jge2_ge_mll110_ge_mlljjjj200"
#sel2="jge2_ge_mll110_ge_mlljjjj200"
#sel3="jge2_ge_mll110_ge_st200_ge_mlljjjj200"
#sel4="jge2_ge_mll110_ge_st200_ge_mlljjjj200"

#sel1="jge2_ge_mll110_ge_mlljjjj200"
#sel2="jge2_ge_mll110_ge_mlljjjj200"
#sel3="jge2_ge_mll110_ge_mlljjjj200"
#sel4="jge2_ge_mll110_ge_st200_ge_mlljjjj200"
#sel5="jge2_ge_mll110_ge_st200_ge_mlljjjj200"
#sel6="jge2_ge_mll110_ge_st200_ge_mlljjjj200"

sel1="jge2_ge_mll110_ge_st200_ge_mlljjjj200"
sel2="X"
sel3="X"
sel4="X"
fi
sel5="X"
sel6="X"

sfsig1=1.
sfsig2=1.
sfsig3=1.
sfsig4=1.
sfsig5=1.
sfsig6=1.

# already implemented in the limit inputs
#if [[ $mix == 1 ]] then
#sfsig1=0.5
#sfsig2=0.5
#sfsig3=1.
#sfsig4=0.5
#sfsig5=0.5
#sfsig6=1.
#fi

sighLRSMWR=("WR2000NR50")

sighLRSMZR=("ZR2800NR50")

if [[ $all == 1 ]]; then
# LRSMWR
sighLRSMWR=("WR600NR50" "WR600NR150" "WR600NR300" "WR600NR450" "WR600NR500" \
"WR1000NR50" "WR1000NR250" "WR1000NR500" "WR1000NR750" "WR1000NR900" \
"WR1400NR50" "WR1400NR350" "WR1400NR700" "WR1400NR1050" "WR1400NR1300" \
"WR1700NR50" "WR1700NR425" "WR1700NR850" "WR1700NR1275" "WR1700NR1600" \
"WR2000NR50" "WR2000NR500" "WR2000NR1000" "WR2000NR1500" "WR2000NR1900" \
"WR2300NR50" "WR2300NR575" "WR2300NR1150" "WR2300NR1725" "WR2300NR2200" \
"WR2600NR50" "WR2600NR650" "WR2600NR1300" "WR2600NR1950" "WR2600NR2500" \
"WR2900NR50" "WR2900NR725" "WR2900NR1450" "WR2900NR2175" "WR2900NR2800" \
"WR3100NR50" "WR3100NR775" "WR3100NR1550" "WR3100NR2325" "WR3100NR3000" \
"WR3300NR50" "WR3300NR825" "WR3300NR1650" "WR3300NR2475" "WR3300NR3200" \
"WR3500NR50" "WR3500NR875" "WR3500NR1750" "WR3500NR2625" "WR3500NR3400" \
"WR3700NR50" "WR3700NR925" "WR3700NR1850" "WR3700NR2775" "WR3700NR3600" \
"WR3900NR50" "WR3900NR975" "WR3900NR1950" "WR3900NR2925" "WR3900NR3800" \
"WR4100NR50" "WR4100NR1025" "WR4100NR2050" "WR4100NR3075" "WR4100NR4000" \
"WR4300NR50" "WR4300NR1075" "WR4300NR2150" "WR4300NR3225" "WR4300NR4200" \
"WR4500NR50" "WR4500NR1125" "WR4500NR2250" "WR4500NR3375" "WR4500NR4400")

# LRSMZR
sighLRSMZR=("ZR400NR50" "ZR400NR100" "ZR400NR150" \
"ZR600NR50" "ZR600NR75" "ZR600NR150" "ZR600NR225" "ZR600NR250" \
"ZR800NR50" "ZR800NR100" "ZR800NR200" "ZR800NR300" "ZR800NR350" \
"ZR1000NR50" "ZR1000NR125" "ZR1000NR250" "ZR1000NR375" "ZR1000NR450" \
"ZR1200NR50" "ZR1200NR150" "ZR1200NR300" "ZR1200NR450" "ZR1200NR550" \
"ZR1400NR50" "ZR1400NR175" "ZR1400NR350" "ZR1400NR525" "ZR1400NR650" \
"ZR1600NR50" "ZR1600NR200" "ZR1600NR400" "ZR1600NR600" "ZR1600NR750" \
"ZR1800NR50" "ZR1800NR225" "ZR1800NR450" "ZR1800NR675" "ZR1800NR850" \
"ZR2000NR50" "ZR2000NR250" "ZR2000NR500" "ZR2000NR750" "ZR2000NR950" \
"ZR2200NR50" "ZR2200NR275" "ZR2200NR550" "ZR2200NR825" "ZR2200NR1050" \
"ZR2400NR50" "ZR2400NR300" "ZR2400NR600" "ZR2400NR900" "ZR2400NR1150" \
"ZR2600NR50" "ZR2600NR325" "ZR2600NR650" "ZR2600NR975" "ZR2600NR1250" \
"ZR2800NR50" "ZR2800NR350" "ZR2800NR700" "ZR2800NR1050" "ZR2800NR1350" \
"ZR3000NR50" "ZR3000NR375" "ZR3000NR750" "ZR3000NR1125" "ZR3000NR1450" \
"ZR3200NR50" "ZR3200NR400" "ZR3200NR800" "ZR3200NR1200" "ZR3200NR1550" \
"ZR3400NR50" "ZR3400NR425" "ZR3400NR850" "ZR3400NR1275" "ZR3400NR1650" \
"ZR3600NR50" "ZR3600NR450" "ZR3600NR900" "ZR3600NR1350" "ZR3600NR1750")
fi

if [[ $typeSig == "LRSMWR" ]] then
sigh=($sighLRSMWR)
elif [[ $typeSig == "LRSMZR" ]] then
sigh=($sighLRSMZR)
fi

WORKAREA=/home/kskovpen/work/testarea/Limit2012/mclimit/run

#rm -rf ${loc}/batch/*

rm -rf ${WORKAREA}/batchlogs

[ ! -d ${WORKAREA}/batchlogs ] && mkdir ${WORKAREA}/batchlogs

jid=0
for sn in $sigh
do
for npe in $npearr
do
for rand in $randarr
do
qsub -b y -j y -v label=${label},chan1=${chan1},chan2=${chan2},chan3=${chan3},\
chan4=${chan4},chan5=${chan5},chan6=${chan6},npe=${npe},rand=${rand},\
jid=${jid},name=${sn},sfsig1=${sfsig1},sfsig2=${sfsig2},sfsig3=${sfsig3},\
sfsig4=${sfsig4},sfsig5=${sfsig5},sfsig6=${sfsig6},\
sel1=${sel1},sel2=${sel2},sel3=${sel3},sel4=${sel4},sel5=${sel5},sel6=${sel6},\
dist=${dist},typeSig=${typeSig},sfsig=${sfsig},mix=${mix} \
-N "${sn}_${jid}_${label}_${npe}_${rand}" -o ${WORKAREA}/batchlogs ${WORKAREA}/job.sh
jid=$[$jid+1]
done
done
done
