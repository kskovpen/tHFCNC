#!/bin/env zsh

rm -rf "*.png"
rm -rf "higgsCombineTest*"
rm -rf "mlfit.root"
rm -rf "plots.root"
rm -rf "roostats*"

doCheck=0

if [[ $doCheck == 1 ]]; then

  echo "***************** Expect signal = 0"
  combine test.txt -M MaxLikelihoodFit -t -1 --expectSignal 0
#  python diffNuisances.py -a mlfit.root -g plots.root
  echo "***************** Expect signal = 1"
  combine test.txt -M MaxLikelihoodFit -t -1 --expectSignal 1
#  python diffNuisances.py -a mlfit.root -g plots.root
  
else

#  combine test.txt -M MaxLikelihoodFit \
#--saveNormalizations --saveShapes --plots --saveWithUncertainties \
#--saveNLL --stepSize=0.0001 --robustFit=1 --rMin=-0.2 --rMax=0.2

  combine test.txt -M MaxLikelihoodFit \
--saveNormalizations --saveShapes --saveWithUncertainties --minimizerStrategy=2 \
--saveNLL --stepSize=0.001 --robustFit=1 --rMin=-5 --rMax=5

  python diffNuisances.py mlfit.root --histogram plots.root -f html > ~/public_html/result.html

  python systematicsAnalyzer.py test.txt --all -f html > ~/public_html/sys.html
  
  python mlfitNormsToText.py mlfit.root

fi
