#!/bin/env zsh

jname="jobs.txt"

fid="${jname}"

cat ${fid} | while read line
do
jid=$(echo $line | awk '{print $1}')
res=$(glite-wms-job-status \
${jid} 2>&1)
wai=$(echo ${res} | grep Waiting)
sub=$(echo ${res} | grep Submitted)
sch=$(echo ${res} | grep Scheduled)
run=$(echo ${res} | grep Running)
can=$(echo ${res} | grep Cancelled)
abo=$(echo ${res} | grep Aborted)
if [[ ${abo} != "" ]]; then
jstatus="\e[0;31mABORTED\e[0m"
elif [[ ${wai} == "" && ${sub} == "" && ${sch} == "" && ${run} == "" && ${can} == "" ]]; then
jstatus="\e[1;32mDONE\e[0m"
elif [[ ${can} != "" && ${run} == "" ]]; then
jstatus="\e[0;35mCANCELLED\e[0m"
elif [[ ${wai} != "" ]]; then
jstatus="\e[1;33mWAITING\e[0m"
elif [[ ${run} != "" ]]; then
jstatus="\e[0;31mRUNNING\e[0m"
fi
echo "${jstatus}"
done

