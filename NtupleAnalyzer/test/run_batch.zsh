#!/bin/env zsh

#https://wikis.nyu.edu/display/NYUHPC/Running+jobs

export HOME=$(pwd)

#cd $HOME
qsub -d ${HOME} -qdteam job_simple.sh
#cd -

exit 1

nmax=-1

cdir=$(pwd)/../
NtupleDir=$(pwd)/../../NtupleProducer/
export LD_LIBRARY_PATH=${cdir}:${NtupleDir}:$LD_LIBRARY_PATH

fpath="lists/"

rm -rf hist
mkdir hist
rm -rf logs
mkdir logs

tool="plot"
evc="0"

flist=$(ls ${fpath})
echo $flist | while read line
do
  jidx=0
  sample=$(echo $line | sed 's%.txt%%g')
  dataset=$(echo $sample | sed 's%_ID.*%%g')

  echo ${line}
  qsub -qdteam job.sh
#  qsub -qdteam job.sh ${fpath}${line} ${tool} ${sample} ${nmax} ${evc}
done
