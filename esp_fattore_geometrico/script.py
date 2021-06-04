#!/usr/bin/python -i
#  $Id:$

##@file analyseSpinDecay.py
# Analyse spin decays.
#
# PyROOT script for displaying decay time distribution and
# doing some simple fits.

import sys
from sys import argv,platform
import numpy as np
if platform == 'darwin':
    rootPath = '/Applications/root_v6.25.01/lib/'
else:
    rootPath = '/usr/local/bin/root/lib'
sys.path.append(rootPath)

from math import *  #sqrt, exp, cos, pi

from ROOT import TCanvas, TF1, TFile, TGaxis, TH1D, TGraph, TGraphErrors
from ROOT import gROOT, gStyle, gApplication
from ROOT import kRed


# histos = [] # l'insieme dei tre istogrammi tot, up, down
files_p = []
files = ['run_first.root', 'run_second.root','run_third.root', 'run_fourth.root', 'run_fifth.root', 'run_6.root', 'run_7.root','run_8.root']
for file in files:
    files_p.append(TFile(file,"read"))
finale = TFile("tot_21Gauss.root","recreate")
names = ['decayTime', 'decayTimeForward', 'decayTimeBackward']
for name in names:
    h = files_p[0].Get(name)
    for i in range(1,len(files)):
        h.Add(files_p[i].Get(name))
    h.Write()

finale.Close()
