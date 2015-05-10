#!/bin/env zsh

resp="tests/"
#npe=" 100000000 "
npe=" 2000 "

lf=$(ls $resp)

echo $lf | while read line
do

cat $resp$line | grep $npe > $resp${line}.mod
nl=$(cat $resp${line}.mod | wc -l)
if [[ $nl -ge 1 ]]; then
root -l -b plotTest.C\(\""${resp}${line}.mod"\"\)
fi
rm -f ${resp}${line}.mod

done
