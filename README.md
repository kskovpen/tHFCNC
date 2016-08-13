# tHFCNC

Code for tH (H->bb) FCNC analysis

## NtupleProducer

Produce user class based ntuples from [FlatTrees](https://github.com/kskovpen/FlatTree), define object quality
and selection criteria, apply initial event selection

``
cd NtupleProducer/;make;cd test/;export LD_LIBRARY_PATH=${PWD}:${PWD}/obj:$LD_LIBRARY_PATH

./NtupleProducer
--file ${infl} # txt file with the list of input FlatTree files to read
--tree FlatTree/tree # name of FlatTree TTree directory
--outfile "output" # name of the output ROOT file
--noe 666 # initial number of events for considered dataset to be used for normalization
--xsec 6.66 # cross section for considered dataset to be used for normalization
--nmax -1 # max number of events to process (-1: no limit)
--isdata 0 # run on data or MC
--stream -1 # 0: SingleElectron, 1: SingleMuon (only for data)
--issig 0 # flag to mark signal events (1: signal)
``

## NtupleAnalyzer

Run various analysis routines, produce histograms and plots

