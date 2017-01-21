#!/bin/env zsh

rm -rf comb_*.txt

combineCards.py \
b2j3=input_MVAHutMAX_b2j3_hut.txt \
b2j4=input_MVAHutMAX_b2j4_hut.txt \
b3j3=input_MVAHutMAX_b3j3_hut.txt \
b3j4=input_MVAHutMAX_b3j4_hut.txt \
b4j4=input_MVAHutMAX_b4j4_hut.txt \
> comb_MVAHutMAX_hut.txt

combineCards.py \
b2j3=input_MVAHctMAX_b2j3_hct.txt \
b2j4=input_MVAHctMAX_b2j4_hct.txt \
b3j3=input_MVAHctMAX_b3j3_hct.txt \
b3j4=input_MVAHctMAX_b3j4_hct.txt \
b4j4=input_MVAHctMAX_b4j4_hct.txt \
> comb_MVAHctMAX_hct.txt
