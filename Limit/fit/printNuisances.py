#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser
from HiggsAnalysis.CombinedLimit.DatacardParser import *

import ROOT
ROOT.gSystem.Load("libHiggsAnalysisCombinedLimit")

parser = OptionParser(usage="usage: %prog input.root \nrun with --help to get list of options")
(options, args) = parser.parse_args()
if len(args) == 0:
    parser.print_usage()
    exit(1)

file = ROOT.TFile(args[0])
if file == None: raise RuntimeError, "Cannot open file %s" % args[0]
fit_b  = file.Get("fit_b")
fit_s  = file.Get("fit_s")
fpf_b = fit_b.floatParsFinal()
fpf_s = fit_s.floatParsFinal()
prefit = file.Get("nuisances_prefit")
if fit_b == None or fit_b.ClassName()   != "RooFitResult": raise RuntimeError, "File %s does not contain the output of the background fit 'fit_b'" % args[0]
if fit_s == None or fit_s.ClassName()   != "RooFitResult": raise RuntimeError, "File %s does not contain the output of the background fit 'fit_b'" % args[0]
if prefit == None or prefit.ClassName() != "RooArgSet":    raise RuntimeError, "File %s does not contain the prefit nuisances 'nuisances_prefit'"  % args[0]

for i in range(fpf_b.getSize()):
    nuis_b = fpf_b.at(i)
    name   = nuis_b.GetName();
    nuis_s = fpf_s.find(name)
    nuis_p = prefit.find(name)
    print name, nuis_b.getVal(), nuis_b.getError()
