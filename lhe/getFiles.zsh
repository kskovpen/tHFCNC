#!/bin/env zsh

fpath="/dpm/in2p3.fr/home/cms/phedex/store/user/kskovpen/tHFCNCPROD/"
opath="input/"

/usr/bin/rfcp ${fpath}/tHToBB-1L-Kappa-hut_CMS/events_426633948.lhe ${opath}tHToBB-1L-Kappa-hut_CMS.lhe
/usr/bin/rfcp ${fpath}/tHToBB-1L-Kappa-hct_CMS/events_426664967.lhe ${opath}tHToBB-1L-Kappa-hct_CMS.lhe
/usr/bin/rfcp ${fpath}/tHToBB-1L-Kappa-gut_CMS/events_426670433.lhe ${opath}tHToBB-1L-Kappa-gut_CMS.lhe
/usr/bin/rfcp ${fpath}/tHToBB-1L-Kappa-gct_CMS/events_426675083.lhe ${opath}tHToBB-1L-Kappa-gct_CMS.lhe
/usr/bin/rfcp ${fpath}/TTtoHToBB-1L-Kappa-hut_CMS/events_430155385.lhe ${opath}TTtoHToBB-1L-Kappa-hut_CMS.lhe
/usr/bin/rfcp ${fpath}/TTtoHToBB-1L-Kappa-hct_CMS/events_430155731.lhe ${opath}TTtoHToBB-1L-Kappa-hct_CMS.lhe
