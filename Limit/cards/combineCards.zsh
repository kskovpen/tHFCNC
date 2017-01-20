#!/bin/env zsh

rm -rf comb_*.txt

combineCards.py \
b2j3=input_MVAHut_b2j3_hut.txt \
b2j4=input_MVAHut_b2j4_hut.txt \
b3j3=input_MVAHut_b3j3_hut.txt \
b3j4=input_MVAHut_b3j4_hut.txt \
b4j4=input_MVAHut_b4j4_hut.txt \
> comb_MVAHut_hut.txt

combineCards.py \
b2j3=input_MVAHct_b2j3_hct.txt \
b2j4=input_MVAHct_b2j4_hct.txt \
b3j3=input_MVAHct_b3j3_hct.txt \
b3j4=input_MVAHct_b3j4_hct.txt \
b4j4=input_MVAHct_b4j4_hct.txt \
> comb_MVAHct_hct.txt
