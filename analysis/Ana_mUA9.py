import argparse
from ROOT import TCanvas, TFile
from ROOT import gBenchmark, gStyle, gROOT
import myStyle


c1 = TCanvas('cmain','Summary',1000,250)

gBenchmark.Start('myBench')


parser = argparse.ArgumentParser(description="mUA9 parser")
parser.add_argument('--fileName', action="store_true", dest="fileName", default="mUA9_N10000.root", help='input file name')
parser.add_argument('--tree', action="append", dest="trees", default=[], help='list of tree you want to process')
args = parser.parse_args()

inFile = TFile(args.fileName)
#inFile.ls()

myTrees = {}
#myTrees['Planes'] = inFile.Get("Planes")

for key in inFile.GetListOfKeys():
    if key.GetClassName() == "TTree":
        if str(key.GetName()) in args.trees:
            t = inFile.Get(str(key.GetName()))
            myTrees[str(key.GetName())] = inFile.Get(str(key.GetName()))

print(myTrees)

for key, t in myTrees.items():
#    t.Print()
    c1.Divide(4,1)
    for i in range(0,4):
        c1.cd(i+1)
        cond="PlaneId=="+str(i)
        t.Draw("X:Y",cond,"COLZ0")


c1.Update()


input('type something to quit: ')
