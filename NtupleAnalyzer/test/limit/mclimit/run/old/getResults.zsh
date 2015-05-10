#!/bin/zsh

resp="/gcf/atlas/data/Limits/run_2012_05_10_LIMIT/"
typ="LRSM"
kf=2

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

lf=$(ls $resp | grep ${typ} | sort -t"_" --key=2,2n --key=3,3n -n)

fout="results/bayes.txt"
rm -f $fout

echo $lf | while read line
do
if [[ $line == "LRSM_800_500" ]]; then
continue
fi
log=$resp/${line}/${line}.log
wrm=$(echo $line | sed "s%.*${typ}_%%g" | sed 's%_.*%%g')
nrm=$(echo $line | sed "s%.*${typ}_%%g" | sed 's%.*_%%g')

exp=$(cat $log | grep "Expected Limit at")                                                                             
obs=$(cat $log | grep "Observed Limit at")                                                                             
expl=$(echo $exp | sed 's\.*+2SD \\g')                                                                                        
obsl=$(echo $obs | sed 's\.*C.L \\g')                                                                                         
m2=$(echo $expl | awk '{print $1}')                                                                                           
m1=$(echo $expl | awk '{print $2}')                                                                                           
med=$(echo $expl | awk '{print $3}')                                                                                          
p1=$(echo $expl | awk '{print $4}')                                                                                           
p2=$(echo $expl | awk '{print $5}')                                                                                           
pval=$(cat $log | grep "1-CLb (from p-value)" | sed 's\.*: \\g')

xsec=$(root -b -l get_xsec_lrsm.C\($wrm,$nrm,$kf\))                                                                           
xsec=$(echo $xsec | sed 1d | sed 1d)                                                                                          
str="$wrm $nrm $med $p2 $p1 $m1 $m2 $obsl $xsec 0 0 $pval"
echo $str
echo $str >> $fout
done

filer="bayes.txt"

echo "--- Median:"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"med\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- +Sigma:"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"p1\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- ++Sigma:"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"p2\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- -Sigma:"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"m1\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- --Sigma:"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"m2\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- Observed:"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"obs\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- M(WR):"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"wrmass\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- M(NR):"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"nrmass\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- Xsec:"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"xsec\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- Pval:"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"pval\",$kf\))
echo $res | sed 1d | sed 1d
echo "--- Nelem:"
res=$(root -b -l read_lrsm.C\(\"$filer\",\"nelem\",$kf\))
echo $res | sed 1d | sed 1d
