#!/bin/env zsh

pileupCalc.py -i \
../../../FlatTree/FlatTreeProducer/test/PROD/GRL/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt \
--inputLumiJSON pileup_latest.txt --calcMode true --minBiasXsec 69200 \
--maxPileupBin 75 --numPileupBins 75 Pileup.root \

# 4.6% systematics

pileupCalc.py -i \
../../../FlatTree/FlatTreeProducer/test/PROD/GRL/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt \
--inputLumiJSON pileup_latest.txt --calcMode true --minBiasXsec 72383 \
--maxPileupBin 75 --numPileupBins 75 PileupUp.root \

pileupCalc.py -i \
../../../FlatTree/FlatTreeProducer/test/PROD/GRL/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt \
--inputLumiJSON pileup_latest.txt --calcMode true --minBiasXsec 66017 \
--maxPileupBin 75 --numPileupBins 75 PileupDown.root \
