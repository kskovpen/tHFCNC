#!/bin/env zsh

anaName="tH"
runName="TEST"
voName="vo.sbg.in2p3.fr"
#voName="cms"

ldir=$(ls ../lists)
tdir=""
dirli=""
echo $ldir | while read line
do
dirnm=$(echo $line | sed 's%_ID.*%%g')
if [[ ${dirnm} != ${tdir} ]]; then
tdir=${dirnm}
dirli=${dirli}"XXX"${tdir}
fi
done

#dirli=$(echo ${dirli} | sed -r 's/^.{3}//')
dirli=$(echo ${dirli})

cp j.jdl temp.jdl

cat temp.jdl | \
sed "s%anaName%${anaName}%g" | \
sed "s%runName%${runName}%g" | \
sed "s%voName%${voName}%g" | \
sed "s%inputName%${foutStr}%g" | \
sed "s%dirli%${dirli}%g" \
> jSUBMIT.jdl

rm temp.jdl

#glite-wms-job-delegate-proxy -d kskovpen
glite-wms-job-delegate-proxy -e https://sbgwms2.in2p3.fr:7443/glite_wms_wmproxy_server -d kskovpen

rm -f jobs.txt

#outp=$(glite-wms-job-submit -a jSUBMIT.jdl 2>&1 | grep "https://sbgwms1.in2p3.fr:9000")
outp=$(glite-wms-job-submit -a -e https://sbgwms2.in2p3.fr:7443/glite_wms_wmproxy_server jSUBMIT.jdl 2>&1 | grep "https://sbgwms2.in2p3.fr:9000")
echo "$outp" >> jobs.txt
rm jSUBMIT.jdl
