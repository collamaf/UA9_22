from ROOT import TCanvas, TFile, TH1F, TH2F, TExec
from ROOT import gBenchmark, gStyle, gROOT
import myStyle

tag="eyOut"
beam1="SidishBeam"; b1Label="Side Beam NoDet"
beam2="FrontBeam"; b2Label="Channeled Beam"

canvas = TCanvas("canvas","Beam Superimposition",600*3,600)

file0 = TFile.Open(beam1+"_ps_out.root")
file1 = TFile.Open(beam2+"_ps_out.root")

SideBeam = file0.Get(beam1+"_"+tag); SideBeam.SetTitle(b1Label)
FrontBeam = file1.Get(beam2+"_"+tag); FrontBeam.SetTitle(b2Label)

SideBeam.GetXaxis().SetRangeUser(-1.,1.)
FrontBeam.GetXaxis().SetRangeUser(-1.,1.)

ex0 = TExec("ex0","gStyle->SetPalette(kDeepSea);");
ex1 = TExec("ex1","gStyle->SetPalette(kSolar);");

canvas.Divide(3,1)
#
canvas.cd(1).SetGrid()
SideBeam.Draw("CONTZ")
ex0.Draw()
SideBeam.Draw("CONTZ,SAME")
#
canvas.cd(2).SetGrid()
FrontBeam.Draw("CONTZ")
ex1.Draw()
FrontBeam.Draw("CONTZ,SAME")
#
canvas.cd(3).SetGrid()
SideBeam.Draw("CONTZ")
ex0.Draw()
SideBeam.Draw("CONTZ,SAME")
ex1.Draw()
FrontBeam.Draw("CONTZ,SAME")

canvas.SaveAs("Superimposition_"+tag+".png")

input("Press any key to close...")

file0.Close()
file1.Close()

