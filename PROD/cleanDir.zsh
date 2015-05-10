#!/bin/env zsh

ntuplev="v20150427"

cleanf=1 # clean all ntuples ?
opath="/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/tHFCNCPROD/${ntuplev}/"

if [[ ${cleanf} == 1 ]]; then
/usr/bin/rfrm -rf ${opath}
/usr/bin/rfmkdir ${opath}
fi

rm -rf crab_*

#dlist=$(ls -d */ | egrep -v multicrab)
#echo $dlist | while read line
#do
#res=$(/usr/bin/rfstat ${opath}${line} 2>&1)
#res=$(echo $res | grep "No such file or directory")
#if [[ ${res} != "" ]]; then
#echo "Creating output directory ${line}"
#/usr/bin/rfmkdir ${opath}${line}
#fi
#done
