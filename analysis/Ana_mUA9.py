import argparse
from ROOT import TCanvas, TFile, TH1F, TH2F
from ROOT import gBenchmark, gStyle, gROOT
import myStyle
from setup import *
import PlaneAnalysis as pA

gBenchmark.Start('myBench')

### Parse inputs from command line
parser = argparse.ArgumentParser(description="mUA9 parser")
parser.add_argument('--fileName', action="store", dest="fileName", default="mUA9_N10000.root", help='input file name')
parser.add_argument('--tree', action="append", dest="trees", default=[], help='list of tree you want to process')
parser.add_argument('--noStop', action="store_true", dest="noStop", default=False, help='set to True to ignore wait')
args = parser.parse_args()
inFile = TFile(args.fileName)


### Retrieve from file the trees you need to analyze
myTrees = {}
#myTrees['Planes'] = inFile.Get("Planes")

for key in inFile.GetListOfKeys():
    if key.GetClassName() == "TTree":
        if str(key.GetName()) in args.trees:
            myTrees[str(key.GetName())] = inFile.Get(str(key.GetName()))

### Process those trees and perform the analysis you need
for key, t in myTrees.items():
    if t.GetName() == "Planes":
        pA.anaPlanes(t)
    else:
        print("Nothing to do ATM. Bye.")

hold('type something to quit: ')
