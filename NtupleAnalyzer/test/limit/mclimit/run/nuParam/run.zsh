#!/bin/env zsh

fitDir="/home/kskovpen/work/testarea/Limit2012/mclimit/run/nuParam"
aStyle="/home/kskovpen/work/testarea/Limit2012/mclimit/run/nuParam/atlasstyle-00-03-04"
export LD_LIBRARY_PATH=${fitDir}:${aStyle}:${LD_LIBRARY_PATH}:$ROOTSYS/lib

./nup --file ../output.root
