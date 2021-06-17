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

# set some global style options
gROOT.SetStyle('Plain')
gStyle.SetOptFit(1)
TGaxis.SetMaxDigits(3)


# ## define simple decay fit function
# def decay(x,par):
#
#     return par[0]*exp(-x[0]/par[1])
#
# ## define fit function with spin dependence
# def spinDecay(x,par):
#
#     return par[0]*exp(-x[0]/par[1])*(1 + par[2]*cos(par[3]*x[0] + par[4]) )
#
# # MIA DEFINIZIONE per funzione asimmetria
# def asymmetry_function(x,par):
#
#     return par[0]*cos(par[1]*x[0])+par[2]


# # set fit range, parameter names and start values
# myfit = TF1('myfit', decay, 0., 20.e3,2)
# myfit.SetParName(0,'A')
# myfit.SetParameter(0,10000.)
# myfit.SetParName(1,'tau')
# myfit.SetParameter(1,200.)
#
# # set fit line style
# myfit.SetLineColor(kRed)
# myfit.SetLineWidth(1)
#
# def decay_double(x,par):
#     return par[0]*exp(-x[0]/par[1])+par[2]*exp(-x[0]/par[3])+par[4]
#
# myfit2 = TF1('myfit2', decay_double, 0., 20 ,5)
# myfit2.SetParName(0,'#N_mu^+')
# myfit2.SetParameter(0,10000.)
# myfit2.SetParName(1,'#tau_mu^+')
# myfit2.FixParameter(1,2.2)
# myfit2.SetParName(2,'#N_mu^-')
# myfit2.SetParameter(2,10000)
# myfit2.SetParName(3,'#tau_mu^-')
# myfit2.SetParameter(3,0.7)
# myfit2.SetParName(4,'Bkg')
# myfit2.FixParameter(4,0)
#
# # set fit line style
# myfit2.SetLineColor(kRed)
# myfit2.SetLineWidth(1)
#
#
# # set fit range, parameter names and start values
# myspinfit = TF1('myspinfit', spinDecay, 0., 20.e3,5)
# myspinfit.SetParName(0,'A')
# myspinfit.SetParameter(0,10000.)
# myspinfit.SetParName(1,'tau')
# myspinfit.SetParameter(1,2000.)
# myspinfit.SetParName(2,'B')
# myspinfit.SetParameter(2,0.1)
# myspinfit.SetParName(3,'omega')
# myspinfit.SetParameter(3,3.)
# myspinfit.SetParName(4,'delta')
# myspinfit.SetParameter(4,0)
#
# # set fit line style
# myfit.SetLineColor(kRed)
# myfit.SetLineWidth(1)
# myspinfit.SetLineColor(kRed)
# myspinfit.SetLineWidth(1)
#
#
# myAsymmetryF = TF1('asymmetry_tf1', asymmetry_function, 0., 5, 3)
# myAsymmetryF.SetParName(0,'#xi')
# myAsymmetryF.SetParameter(0,0.32)
# myAsymmetryF.SetParName(1,'#omega')
# myAsymmetryF.FixParameter(1,1.7)
# myAsymmetryF.SetParName(2,'c')
# myAsymmetryF.SetParameter(2,0)
#
# myAsymmetryF.SetLineColor(kRed)
# myAsymmetryF.SetLineWidth(1)

"""Read root file.

Simple PyROOT macro to read a root file and plot
dacay time and decay position.
"""
def analyseDecay():
    global file, file2, c1, c2, h

    # load histograms from file
    file = TFile.Open("histoEnergy_"+argv[1]+".root")
    file.ls()
    # file2 = TFile.Open("tree_run0.root")
    # file2.ls()
    #draw histogram and fit
    c1 = TCanvas('c1','Energy Distribution',10,10,1800,1200)
    h = file.EnDis

    h1 = h.RebinX(5)
    # max = h1.FindLastBinAbove()
    h1.GetXaxis().SetRange(1,int(argv[2]))
    h1.Draw()
    # c1.SetLogy()
    c1.SaveAs("histo_"+argv[1]+"_zoom.png")
    c1.Modified()
    c1.Update()

    # c2 = TCanvas('c2','Mother Energy Distribution',10,10,1800,1200)
    #
    # a = file2.Get("Gas_Tree")
    # a.Draw("medep")
    # c2.SaveAs("histo_mother_"+argv[1]+".png")
    # c2.Modified()
    # c2.Update()



    #
    # c2 = TCanvas('c2','Decay Position',250,20,700,500)
    # file.decayPos.Draw()
    #
    # # print out results
    # print 'average Decay time =',file.decayTime.GetMean(),'us'
    # print 'fitted Decay time = (',myfit.GetParameter('tau'),'+-',myfit.GetParError(1),') us'
    # print 'average Decay position =',file.decayPos.GetMean(),'mm'
    #
    # # draw histogram and fit
    # c3 = TCanvas('c3','Decay Time Forward',30,50,700,500)
    # file.decayTimeForward.Draw()
    # myspinfit.FixParameter(0,myfit.GetParameter('A')/2.)
    # myspinfit.FixParameter(1,myfit.GetParameter('tau'))
    # file.decayTimeForward.Fit(myspinfit)
    # c3.Modified()
    # c3.Update()
    #
    # calcLande(myspinfit.GetParameter('omega'),3.5e-3)  # tesla

    # asymmetry_histo = TH1D('asymmetry', 'Asymmetry U-D/(U+D)', 200, 0, 20)
    # file.Close()
    #
    # file2.Close()



if __name__=='__main__':
    # check for run time arguments
    analyseDecay()
    # gApplication.Run()

print "\n to quit press Ctrl-D"
