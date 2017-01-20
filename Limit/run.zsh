#!/bin/env zsh

#combine cards/input_PassSel5_ALL_hct.txt -M MaxLikelihoodFit --rMin=-50 --rMax=50 --preFitValue 0 \
#--saveNormalizations --saveShapes --plots --saveWithUncertainties --out fit

#combine cards/input_MVAHct_hct.txt -M MaxLikelihoodFit --rMin=-50 --rMax=50 \
#--saveNormalizations --saveShapes --plots --saveWithUncertainties --out fit

combine test.txt -M MaxLikelihoodFit --rMin=-50 --rMax=50 \
--saveNormalizations --saveShapes --plots --saveWithUncertainties --out fit

#combine cards/input_PassSel5_ALL_hut.txt -M ProfileLikelihood --rMin=0. --rMax=0.

#combine -M ProfileLikelihood cards/input_MVAHut_hut.txt -t 10 --rMin 0.0001 --rMax 0.1

#combine cards/input_PassSel_ALL_hut.txt -M Asymptotic --rMax=0.001 --rMin=0.000001
#combine cards/input_MVAHut_hut.txt -M Asymptotic --rMin=0.0001 --rMax=0.1

#combine test.txt -M MarkovChainMC

#combine test.txt -M HybridNew
