# tHFCNC

Code for tH (H->bb) FCNC analysis

To be compiled within CMSSW_8_0_12, although only ROOT libraries are
used (to be fully decoupled from CMSSW in the future)

```
git clone https://github.com/kskovpen/tHFCNC
```

## NtupleProducer

Produce user class based ntuples from [FlatTrees](https://github.com/kskovpen/FlatTree), define object quality
and selection criteria, apply initial event selection

```c++
cd tHFCNC/NtupleProducer/;make;export LD_LIBRARY_PATH=${PWD}:${PWD}/obj:$LD_LIBRARY_PATH;cd test/

./NtupleProducer
--file list.txt // txt file with the list of input FlatTree files to read
--tree FlatTree/tree // name of FlatTree TTree directory
--outfile "output" // name of the output ROOT file
--noe 666 // initial number of events for considered dataset to be used for normalization
--xsec 6.66 // cross section for considered dataset to be used for normalization
--nmax -1 // max number of events to process (-1: no limit)
--isdata 0 // run on data or MC
--stream -1 // 0: SingleElectron, 1: SingleMuon (only for data)
--issig 0 // flag to mark signal events (1: signal)
```

## NtupleAnalyzer

Run various analysis routines, produce histograms and plots

```c++
git clone https:\/\/github.com/kskovpen/TopKinFit
cd TopKinFit/;make;cd -

cd tHFCNC/NtupleAnalyzer/;make
export LD_LIBRARY_PATH=${PWD}:${PWD}/../NtupleProducer:${PWD}/../NtupleProducer/obj:../../TopKinFit/:$LD_LIBRARY_PATH
cd test/

./Analyzer \
list.txt \ // txt file with the list of input Ntuple files to read 
output \ // name of the output ROOT file
plot \ // name of the tool to run (plot: apply selection and produce histograms)
0 \ // outdated option, to be removed
-1 \ // maximum number of events to process
$(PWD) // path to current directory
```
