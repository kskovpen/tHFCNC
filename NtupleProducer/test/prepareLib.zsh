#!/bin/env zsh

fpath="../../../lib/slc6_amd64_gcc491"
libf=($(ls ${fpath} | grep ".so"))

mkdir TEMPLIB

for i in ${libf}
do
cp ${fpath}/${i} TEMPLIB/
done

tar -cvf LIB.tar TEMPLIB/
gzip -f LIB.tar

rm -r TEMPLIB
