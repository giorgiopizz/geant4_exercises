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

# set some global style options
gROOT.SetStyle('Plain')
gStyle.SetOptFit(1)
TGaxis.SetMaxDigits(3)


file = TFile.Open("asymmetry_magnetico.root", "read")
file.ls()


file2 = TFile.Open("asymmetry_magnetico_spento.root", "read")
file2.ls()

c4 = TCanvas('c4','Asymm',10,10,700,500)

file.Graph.Draw("ALP")
file2.Graph.SetLineColor(3)
file2.Graph.Draw("same")

file.Graph.SetName("acceso")
file.Graph.SetTitle("acceso")
file2.Graph.SetName("spento")
file2.Graph.SetTitle("spento")

file3 = TFile("asymmetry_confronto.root", "recreate")
file.Graph.Write()
file2.Graph.Write()
file3.Close()

c4.Modified()
c4.Update()


gApplication.Run()
