#!/bin/env zsh

plist=($(pgrep Analyzer))
if [[ ${#plist[@]} == 0 ]]; then
  echo "Done"
else
  echo "Jobs (${#plist[@]}) running"
fi
