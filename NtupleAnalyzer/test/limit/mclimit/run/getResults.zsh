#!/bin/zsh

#resp="/gcf/atlas/data/Limits/run_20130424_LIMITFULL/"
#resp="/gcf/atlas/data/Limits/run_20130424_LIMITMM/"
#resp="/gcf/atlas/data/Limits/run_20130424_LIMIT_EE_OS_NOMIX/"
resp="/gcf/atlas/data/Limits/run_20130503_LIMIT_EE_SS_NOMIX/"
typ="WR" # WR, ZR
kf=0.5
lab="eeSS"

# kf for LRSM ***
# no mixing ---
# ee/mm SS/OS 0.5
# ee/mm SS+OS 1
# ee+mm SS/OS 1
# ee+mm SS+OS 2
# with mixing ---
# ee/mm SS/OS 0.25
# ee/mm SS+OS 0.5
# ee+mm SS/OS 0.5
# ee+mm SS+OS 1
# emu+mue SS/OS 0.5
# emu+mue SS+OS 1
# all SS/OS 1
# all SS+OS 2

lf=$(ls $resp | grep ${typ} | sort -n -tR -k 2,2n -k 3,3n)

fout="results/bayes_${typ}_${lab}.txt"
rm -f $fout

echo $lf | while read line
do
log=$resp/${line}/${line}.log
wrm=$(echo $line | sed "s%.*${typ}%%g" | sed 's%NR.*%%g')
nrm=$(echo $line | sed "s%.*${typ}%%g" | sed 's%.*NR%%g')

exp=$(cat $log | grep "Expected Limit at")
obs=$(cat $log | grep "Observed Limit at")
expl=$(echo $exp | sed 's\.*+2SD \\g')
obsl=$(echo $obs | sed 's\.*C.L \\g')
m2=$(echo $expl | awk '{print $1}')
m1=$(echo $expl | awk '{print $2}')
med=$(echo $expl | awk '{print $3}')
p1=$(echo $expl | awk '{print $4}')
p2=$(echo $expl | awk '{print $5}')
pval=666
#pval=$(cat $log | grep "1-CLb (from p-value)" | sed 's\.*: \\g')

xsec=$(root -b -l get_xsec_lrsm.C\($wrm,$nrm,$kf,\"$typ\"\))
xsec=$(echo $xsec | sed 1d | sed 1d)
str="$wrm $nrm $med $p2 $p1 $m1 $m2 $obsl $xsec 0 0 $pval"
echo $str
echo $str >> $fout
done

echo "--- Median:"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"med\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- +Sigma:"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"p1\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- ++Sigma:"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"p2\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- -Sigma:"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"m1\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- --Sigma:"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"m2\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- Observed:"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"obs\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- M(${typ}):"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"wrmass\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- M(NR):"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"nrmass\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- Xsec:"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"xsec\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- Pval:"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"pval\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- Nelem:"
res=$(root -b -l read_lrsm.C\(\"$fout\",\"nelem\",$kf\))
echo $res | sed 1d | sed 1d
