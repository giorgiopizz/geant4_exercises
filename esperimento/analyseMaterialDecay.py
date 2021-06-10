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

from ROOT import TCanvas, TF1, TFile, TGaxis, TH1D, TGraph
from ROOT import gROOT, gStyle, gApplication
from ROOT import kRed

# set some global style options
gROOT.SetStyle('Plain')
gStyle.SetOptFit(1)
TGaxis.SetMaxDigits(3)


## define simple decay fit function
def decay(x,par):

    return par[0]*exp(-x[0]/par[1])

## define fit function with spin dependence
def spinDecay(x,par):

    return par[0]*exp(-x[0]/par[1])*(1 + par[2]*cos(par[3]*x[0] + par[4]) )

# MIA DEFINIZIONE per funzione asimmetria
def asymmetry_function(x,par):

    return par[0]*cos(par[1]*x[0])+par[2]







# set fit range, parameter names and start values
myspinfit = TF1('myspinfit', spinDecay, 0., 20.e3,5)
myspinfit.SetParName(0,'A')
myspinfit.SetParameter(0,10000.)
myspinfit.SetParName(1,'tau')
myspinfit.SetParameter(1,2000.)
myspinfit.SetParName(2,'B')
myspinfit.SetParameter(2,0.1)
myspinfit.SetParName(3,'omega')
myspinfit.SetParameter(3,3.)
myspinfit.SetParName(4,'delta')
myspinfit.SetParameter(4,0)

# set fit line style
# myfit.SetLineColor(kRed)
# myfit.SetLineWidth(1)
myspinfit.SetLineColor(kRed)
myspinfit.SetLineWidth(1)


myAsymmetryF = TF1('asymmetry_tf1', asymmetry_function, 0., 10, 3)
myAsymmetryF.SetParName(0,'#xi')
myAsymmetryF.SetParameter(0,0.32)
myAsymmetryF.SetParName(1,'#omega')
myAsymmetryF.SetParameter(1,3.)
myAsymmetryF.SetParName(2,'c')
myAsymmetryF.SetParameter(2,0)

myAsymmetryF.SetLineColor(kRed)
myAsymmetryF.SetLineWidth(1)



def decay_double(x,par):
    return par[0]*exp(-x[0]/par[1])+par[2]*exp(-x[0]/par[3])+par[4]



# set fit range, parameter names and start values
myfit = TF1('myfit', decay_double, 0., 20.e3,3)
myfit.SetParName(0,'A')
myfit.SetParameter(0,10000.)
myfit.SetParName(1,'tau')
myfit.SetParameter(1,200.)



myfit2 = TF1('myfit2', decay_double, 0.2, 11e+3,5)
myfit2.SetParName(0,'#N_mu^-')
myfit2.SetParameter(0,10000.)
myfit2.SetParLimits(0,0,1000000)
myfit2.SetParName(1,'#tau_mu^-')
myfit2.SetParameter(1,0.717)
myfit2.SetParName(2,'#N_mu^+')
myfit2.SetParLimits(2,0,1000000)
myfit2.SetParameter(2,20000)
myfit2.SetParName(3,'#tau_mu^+')
myfit2.SetParameter(3,2.197)
myfit2.SetParName(4,'Bkg')
myfit2.SetParameter(4,0)

# set fit line style
myfit2.SetLineColor(kRed)
myfit2.SetLineWidth(1)

"""Read root file.

Simple PyROOT macro to read a root file and plot
dacay time and decay position.
"""
def analyseDecay(fname):
    global file, c1, c2, c3, c4

    # load histograms from file
    file = TFile.Open(fname)
    file.ls()

    # draw histogram and fit
    c1 = TCanvas('c1','Decay Time',10,10,700,500)
    file.histo_tot.Draw()


    # file.histo_tot.Fit(myfit2, "R")
    # myfit2.ReleaseParameter(1)
    #myfit2.FixParameter(0, myfit2.GetParameter(0))
    #myfit2.FixParameter(2, myfit2.GetParameter(2))
    file.histo_tot.Fit(myfit, "R")
    c1.Modified()
    c1.Update()
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
    # x = []
    # y = []
    # for i in range(100):
    #     U = file.decayTimeForward.GetBinContent(i)
    #     D = file.decayTimeBackward.GetBinContent(i)
    #     x.append(file.decayTimeForward.GetBinCenter(i))
    #     try:
    #         v = (U-D)/(U+D)
    #     except:
    #         v= 0
    #     y.append(v)
        # asymmetry_histo.SetBinContent(i, x)

    #
    # c4 = TCanvas('c4','Asymm',10,10,700,500)
    # asymmetry_graph = TGraph(100,np.array(x),np.array(y))
    # c4.cd()
    # asymmetry_graph.Draw("AC*")
    # asymmetry_graph.Fit(myAsymmetryF,"R")
    # asymmetry_histo.Draw()
    # asymmetry_histo.Fit(myAsymmetryF)
    # c4.Modified()
    # c4.Update()
#
# def calcLande(omega,bfield):
#     omega=omega*1.e6     # MHz
#     hbar=1.054e-34  # J s
#     q=1.602e-19     #  C
#     c=2.998e8 # m/s
#     m=105.658e6*q/c**2
#     magneton=q*hbar/(2.*m)  # 4.485e-26 * J/T
#
#     g=omega*hbar/(magneton*bfield)
#     g_pdg = 11659209e-10*2+2
#     print 'Lande PDG g=', g_pdg
#     print 'Lande g=',g
#     print 't = ',(g-g_pdg)/12e-10
#
#     return g


if __name__=='__main__':
    fname='run_0.root'
    # check for run time arguments
    if len(sys.argv)>1:
        fname=sys.argv[1]
    analyseDecay(fname)

    # c1.Modified()
    # c1.Update()
    # c4.Modified()
    # c4.Update()
    gApplication.Run()

# print "\n to quit press Ctrl-D"
