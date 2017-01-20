#!/bin/env zsh

PostFitShapes -d test.txt -o test.root \
-f mlfit.root:fit_b --postfit --sampling --print
