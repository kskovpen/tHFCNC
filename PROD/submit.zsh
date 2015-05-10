#!/bin/env zsh

pset="crabConfigTemplate.py"
tag="v20150427"
#ver="tHToBB-1L-Kappa-gct_AODFASTSIM"
#ver="TTtoTHToBB-1L-Kappa-hct_AODFASTSIM"
#ver="THQtoTBBQ-1L_AODFASTSIM"
ver="TZQtoTQQQ-1L_AODFASTSIM"
prodv="/store/user/kskovpen/tHFCNCPROD/${tag}/"

rm -f crabConfig.py*

cat ${pset} \
| sed "s%OUTLFN%${prodv}%g" \
| sed "s%VERSION%${ver}%g" \
> crabConfig.py
  
crab submit

rm -f crabConfig.py*
