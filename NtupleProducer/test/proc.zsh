#!/bin/env zsh

ver="v20150209"
outdir="/opt/sbg/data/data3/cms/kskovpen/NtupleTTH/${ver}"

cp input_1.txt input.txt
./run.zsh
cp output.root \
${outdir}/TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola_Phys14DR_PU20bx25_tsg_PHYS14_25_V1_v2.root

cp input_2.txt input.txt
./run.zsh
cp output.root \
${outdir}/TTWJets_Tune4C_13TeV-madgraph-tauola_Phys14DR_PU20bx25_PHYS14_25_V1_v1.root

cp input_3.txt input.txt
./run.zsh
cp output.root \
${outdir}/TTZJets_Tune4C_13TeV-madgraph-tauola_Phys14DR_PU20bx25_PHYS14_25_V1_v1.root

cp input_4.txt input.txt
./run.zsh
cp output.root \
${outdir}/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola_Phys14DR_PU20bx25_PHYS14_25_V1_v1.root

cp input_5.txt input.txt
./run.zsh
cp output.root \
${outdir}/DYJetsToLL_M-50_13TeV-madgraph-pythia8_Phys14DR_PU20bx25_PHYS14_25_V1_v1.root

cp input_6.txt input.txt
./run.zsh
cp output.root \
${outdir}/WZJetsTo3LNu_Tune4C_13TeV-madgraph-tauola_Phys14DR_PU20bx25_PHYS14_25_V1_v1.root

