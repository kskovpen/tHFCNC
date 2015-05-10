#!/bin/env zsh

echo "Hut"
python analyze_tH.py input/tHToBB-1L-Kappa-hut_CMS.lhe output/tHToBB-1L-Kappa-hut_CMS.root
echo "Hct"
python analyze_tH.py input/tHToBB-1L-Kappa-hct_CMS.lhe output/tHToBB-1L-Kappa-hct_CMS.root
echo "gut"
python analyze_tH.py input/tHToBB-1L-Kappa-gut_CMS.lhe output/tHToBB-1L-Kappa-gut_CMS.root
echo "gct"
python analyze_tH.py input/tHToBB-1L-Kappa-gct_CMS.lhe output/tHToBB-1L-Kappa-gct_CMS.root
echo "Hut ttbar"
python analyze_tH_ttbar.py input/TTtoHToBB-1L-Kappa-hut_CMS.lhe output/TTtoHToBB-1L-Kappa-hut_CMS.root
echo "Hct ttbar"
python analyze_tH_ttbar.py input/TTtoHToBB-1L-Kappa-hct_CMS.lhe output/TTtoHToBB-1L-Kappa-hct_CMS.root
