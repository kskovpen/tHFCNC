#!/bin/env zsh

rm -rf comb_*.txt

combineCards.py \
b2j3=input_MVAHutComb_b2j3_hut.txt \
b2j4=input_MVAHutComb_b2j4_hut.txt \
b3j3=input_MVAHutComb_b3j3_hut.txt \
b3j4=input_MVAHutComb_b3j4_hut.txt \
> comb_MVAHutComb_hut.txt

combineCards.py \
b2j3=input_MVAHctComb_b2j3_hct.txt \
b2j4=input_MVAHctComb_b2j4_hct.txt \
b3j3=input_MVAHctComb_b3j3_hct.txt \
b3j4=input_MVAHctComb_b3j4_hct.txt \
b4j4=input_MVAHctComb_b4j4_hct.txt \
> comb_MVAHctComb_hct.txt

combineCards.py \
Hbb13=comb_MVAHutComb_hut.txt \
Hbb8ML=../../8TeV/FCNHCards/multilepton_datacards/20140825_160540_combine_final_thu.txt \
Hbb8GG=../../8TeV/FCNHCards/hgg_datacards/datacard_shape_comb_v8_uh_2_7.092.txt \
Hbb8BB=../../8TeV/FCNHCards/hbb_datacards/hbb_uh/hbbcard.txt \
> comb_MVAHutComb_hut_COMB.txt

combineCards.py \
Hbb13=comb_MVAHctComb_hct.txt \
Hbb8ML=../../8TeV/FCNHCards/multilepton_datacards/20140825_160540_combine_final.txt \
Hbb8GG=../../8TeV/FCNHCards/hgg_datacards/datacard_shape_comb_v8_2_6.264.txt \
Hbb8BB=../../8TeV/FCNHCards/hbb_datacards/hbb_ch/hbbcard.txt \
> comb_MVAHctComb_hct_COMB.txt
