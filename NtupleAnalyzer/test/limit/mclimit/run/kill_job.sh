#!/bin/env zsh

li=$(qstat | grep -v "prior" | grep -v "\-\-\-\-\-" | awk '{print $1}')
echo $li | while read i
do
qdel $i
done
