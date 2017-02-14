#!/bin/env zsh

jid=($(qstat -u kskovpen | awk '{print $1}' | cut -c1-7 | egrep -v "cream02|Req|Job|----"))

for i in ${(O)jid}
do
  echo $i
  qdel $i
done
