import argparse
from ROOT import TCanvas, TFile, TH1F, TH2F
from ROOT import gBenchmark, gStyle, gROOT
import myStyle
from setup import *
import PlaneAnalysis as pA
import CrystalAnalysis as cA

gBenchmark.Start('myBench')

### Parse inputs from command line
parser = argparse.ArgumentParser(description="mUA9 parser")
parser.add_argument('--fileName', action="store", dest="fileName", default="mUA9_N10000.root", help='input file name')
parser.add_argument('--tree', action="append", dest="trees", default=[], help='list of tree you want to process')
parser.add_argument('--ana', action="append", dest="analyses", default=[], help='list of analyses you want to perform')
parser.add_argument('--rotX', action="store", dest="rotX", default=0, help='Crystal rotation angle X [in mu-rad]')
parser.add_argument('--noStop', action="store_true", dest="noStop", default=False, help='set to True to ignore wait')
parser.add_argument('--savePdf', action="store_true", dest="savePdf", default=False, help='set to True to save canvas')
parser.add_argument('--label', action="store", dest="label", default="lastRun", help='label for outpu files')
args = parser.parse_args()
inFile = TFile(args.fileName)


### Retrieve from file the trees you need to analyze
myTrees = {}
#myTrees['Planes'] = inFile.Get("Planes")

for key in inFile.GetListOfKeys():
    if key.GetClassName() == "TTree":
        if str(key.GetName()) in args.trees:
            myTrees[str(key.GetName())] = inFile.Get(str(key.GetName()))

for iAna in args.analyses:
    if iAna == "Planes" and iAna not in myTrees:
        myTrees[iAna] = inFile.Get("Planes")
    elif iAna == "Crystal" and iAna not in myTrees:
        myTrees[iAna] = inFile.Get("ExExChTree")

### Process those trees and perform the analysis you need
for key, t in myTrees.items():
    if t.GetName() == "Planes":
#        pA.anaPlanes(t,args.label,args.savePdf)
        pA.treeLoop(t,args.label,args.savePdf)
    elif t.GetName() == "ExExChTree":
        cA.treeLoop(t,args.label,args.savePdf)
    else:
        print("Nothing to do ATM. Bye.")

hold('type something to quit: ',args.noStop)
