#!/bin/env zsh

cdir=$(pwd)

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${cdir}

./toy
