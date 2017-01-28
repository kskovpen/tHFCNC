#!/bin/env zsh

jlist=($(qstat -u kskovpen | grep TFCNH | awk '{print $1}' | cut -c1-7))

for i in $jlist
do
  echo $i $(qstat -f $i | grep exec_host)
done
