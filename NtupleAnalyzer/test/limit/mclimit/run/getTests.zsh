#!/bin/zsh

inp="run_20130610_LIMIT_MM_SS_NOMIX_EXP"
resp="/gcf/atlas/data/Limits/${inp}/"
typ="WR2000NR50"

lf=$(ls $resp | grep ${typ} | sort -n -tR -k 2,2n -k 3,3n)

fout="tests/bayes_${inp}.txt"
rm -f $fout

echo $lf | while read line
do
log=$resp/${line}/${typ}.log
wrm=$(echo $typ | sed 's%NR.*%%g' | sed 's%NPE.*%%g' | sed 's%.*WR%%g')
nrm=$(echo $typ | sed 's%.*NR%%g' | sed 's%NPE.*%%g')
npe=$(echo $line | sed 's%.*NPE%%g' | sed 's%RAND.*%%g' | sed 's%_%%g')
rand=$(echo $line | sed 's%.*RAND%%g')

exp=$(cat $log | grep "Expected Limit at")
obs=$(cat $log | grep "Observed Limit at")
expl=$(echo $exp | sed 's\.*+2SD \\g')
obsl=$(echo $obs | sed 's\.*C.L \\g')
m2=$(echo $expl | awk '{print $1}')
m1=$(echo $expl | awk '{print $2}')
med=$(echo $expl | awk '{print $3}')
p1=$(echo $expl | awk '{print $4}')
p2=$(echo $expl | awk '{print $5}')

str="$wrm $nrm $npe $rand $med $p2 $p1 $m1 $m2 $obsl"
echo $str
echo $str >> $fout
done
