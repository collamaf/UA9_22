import argparse

parser = argparse.ArgumentParser(description="mUA9 parser")
parser.add_argument('--fileName', action="store", dest="fileName", default="build/mUA9COVID_Part_Ene180_CrystAng0_N1000.root", help='input file name')
parser.add_argument('--tree', action="store", dest="tree", default="ExpTree", help='list of tree you want to process')
parser.add_argument('--out', action="store", dest="out", help='output file name')
args = parser.parse_args()

from ROOT import TFile
import random

inFile = TFile(args.fileName)
tree = inFile.Get(args.tree)
if args.out:
    outName=args.out
else:
    outName=args.fileName.replace(".root",".dat")

outFile = open(outName,"w")

#smearing 10.6 microradians
smearSigmaX = 10.15
smearSigmaX = 9.0
smearSigmaX = 0.0
# Loop over events
nEntries=tree.GetEntriesFast()
#print("Start looping over",nEntries,"events. Please wait...")
for i, e in enumerate(tree): 
    #if ((i/nEntries*100)%10) == 0 : print(i/nEntries*100,"% done")
    if len(e.angXin)!=0:
        #thetaXin=(e.sdHitX[1]-e.sdHitX[0])/(e.sdHitZ[1]-e.sdHitZ[0])/murad
        #cols=[gonio_angle,d0_x,d0_y,thetaIn_x,thetaOut_x,thetaIn_y,thetaOut_y,unknown1,unknown2]
        #units= urad, mm, mm, urad, urad, urad, urad
        smearX = random.gauss(0.0,smearSigmaX)
        #print(smearX)
        outFile.write("{:f},{:.16f},{:.16f},{:.15e},{:.15e},{:.15e},{:.15e},{:.1f},{:.1f}\n".format(e.crystAngX[0],e.posXin[0],e.posYin[0],
                                                                    e.angXin[0]*1E-6,(e.angXout[0]+smearX)*1E-6,e.angYin[0]*1E-6,e.angYout[0]*1E-6,0.0,0.0))
outFile.close()
