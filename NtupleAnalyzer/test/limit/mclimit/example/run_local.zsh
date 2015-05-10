#!/bin/env zsh

cdir="/home/kskovpen/work/testarea/Limit2012/mclimit/example/"

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${cdir}:$ROOTSYS/lib

./toy \
${cdir}/LRSMLimitInput.root@${cdir}/LRSMLimitInput.root@${cdir}/LRSMLimitInput.root@${cdir}/LRSMLimitInput.root \
${cdir}/LRSMLimitInput.root@${cdir}/LRSMLimitInput.root@${cdir}/LRSMLimitInput.root@${cdir}/LRSMLimitInput.root \
0 1 20 0.0001
