import argparse
from ROOT import TCanvas, TFile
from ROOT import gBenchmark, gStyle, gROOT
import myStyle
from setup import *


gBenchmark.Start('myBench')

### Parse inputs from command line
parser = argparse.ArgumentParser(description="mUA9 parser")
parser.add_argument('--fileName', action="store", dest="fileName", default="mUA9_N10000.root", help='input file name')
parser.add_argument('--tree', action="append", dest="trees", default=[], help='list of tree you want to process')
parser.add_argument('--noStop', action="store_true", dest="noStop", default=False, help='set to True to ignore wait')
args = parser.parse_args()
inFile = TFile(args.fileName)

### Define utility functions
def hold(string):
    if not args.noStop:
        input(string)
    return

### Define the analysis functions you need
def anaPlanes(t):
    print("anaPlanes() reading from ",t.GetName())
    c1 = TCanvas('cmain','Summary',1000,250)
    c1.Divide(4,1)
    for i in range(0,4):
        c1.cd(i+1)
        cond="PlaneId=="+str(planes[i])
        t.Draw("X:Y",cond,"COLZ0")
    c1.Update()
    hold('done with anaPlanes(): should I proceed?')
    return

### Retrieve from file the trees you need to analyze
myTrees = {}
#myTrees['Planes'] = inFile.Get("Planes")

for key in inFile.GetListOfKeys():
    if key.GetClassName() == "TTree":
        if str(key.GetName()) in args.trees:
            t = inFile.Get(str(key.GetName()))
            myTrees[str(key.GetName())] = inFile.Get(str(key.GetName()))

### Process those trees and perform the analysis you need
for key, t in myTrees.items():
    if t.GetName() == "Planes":
        anaPlanes(t)
    else:
        print("Nothing to do ATM. Bye.")

hold('type something to quit: ')
