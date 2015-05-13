#!/bin/env zsh

username=$(whoami)
jlist=($(qstat -u ${username} | awk '{print $1}'))
for i in $jlist
do
  qdel ${i}
done
