from ROOT import TCanvas, TFile, TH1F, TH2F
from array import array
import math
import myStyle
from setup import *

# Define useful functions
def Hist1D(name,title,bX=10,Xmin=0.,Xmax=10.,Xlab="X",color=1):
    ht= TH1F(name,title,bX,Xmin,Xmax); 
    ht.GetXaxis().SetTitle(Xlab); ht.SetLineColor(color)
    return ht

def Hist2D(name,title,bX=10,Xmin=0.,Xmax=10.,bY=10,Ymin=0.,Ymax=10.,Xlab="X",Ylab="Y",color=1):
    ht= TH2F(name,title,bX,Xmin,Xmax,bY,Ymin,Ymax); 
    ht.GetXaxis().SetTitle(Xlab); ht.GetYaxis().SetTitle(Ylab); ht.SetLineColor(color)
    return ht

def Hist1DVec(size=1,name="h",title="h",bX=10,Xmin=0.,Xmax=10.,Xlab="X",color=1):
    htv = []; ht = Hist1D(name,title,bX,Xmin,Xmax,Xlab,color)
    for i in range(0,size):
        htv.append(ht.Clone())
    return htv

def Hist2DVec(size=1,name="h",title="h",bX=10,Xmin=0.,Xmax=10.,bY=10,Ymin=0.,Ymax=10.,Xlab="X",Ylab="Y",color=1):
    htv = []; ht = Hist2D(name,title,bX,Xmin,Xmax,bY,Ymin,Ymax,Xlab,Ylab,color)
    for i in range(0,size):
        htv.append(ht.Clone())
    return htv

## Emittance calculation
def EmittanceRMS(histo):
    # sqrt(<x^2><x'2>-<xx'>^2)
    emRMS = 0.0
    stats = array('d', [0.] * 10)
    histo.GetStats(stats)
    print(stats[0],stats[3],stats[5],stats[6])
    emRMS=math.sqrt((stats[3]*stats[5])-(stats[6]*stats[6]))/stats[0]
    return emRMS

# Main function
def treeLoop(t,label = 'lastRun',savePlot=False):
    print("treeLoop() reading from ",t.GetName())
    rows = 2
    cols = 3
    # Define the histograms you need
    h_xIn = Hist1D("h_xIn","Incident pos. x",40,posR["min"],posR["max"],"X [mm]",1)
    h_yIn = Hist1D("h_yIn","Incident pos. y",40,posR["min"],posR["max"],"Y [mm]",2)
    h_xyIn = Hist2D("h_xyIn","Incident y vs x",40,posR["min"],posR["max"],40,posR["min"],posR["max"],"X [mm]","Y [mm]",1)
    h_angXIn = Hist1D("h_angXIn","Incident X angle",40,angR["min"],angR["max"],"#theta_{X}^{in} [#mu rad]",1)
    h_angYIn = Hist1D("h_angYIn","Incident Y angle",40,angR["min"],angR["max"],"#theta_{Y}^{in} [#mu rad]",2)
    h_angXYIn = Hist2D("h_angXYIn","Incident X vs Y angle",40,angR["min"],angR["max"],40,angR["min"],angR["max"],"#theta_{X}^{in} [#mu rad]","#theta_{Y}^{in} [#mu rad]",1)
    h_angXOut = Hist1D("h_angXOut","Outgoing X angle",40,angR["min"],angR["max"],"#theta_{X}^{out} [#mu rad]",1)
    h_angYOut = Hist1D("h_angYOut","Outgoing Y angle",40,angR["min"],angR["max"],"#theta_{Y}^{out} [#mu rad]",2)
    h_angXYOut = Hist2D("h_angXYOut","Outgoing X vs Y angle",40,angR["min"],angR["max"],40,angR["min"],angR["max"],"#theta_{X}^{out} [#mu rad]","#theta_{Y}^{out} [#mu rad]",1)
    h_big = Hist2D("h_big","Deflection vs. incidence",200,angR["min"],angR["max"],200,angR["min"],angR["max"],"Deflection [#mu rad]","Incidence angle [#mu rad]",1)
    h_exIn = Hist2D("h_exIn","x' vs. x",80,posR["min"],posR["max"],200,angR["min"],angR["max"],"x_{In} [mm]","x'_{In} [#mu rad]",1)
    h_exOut = Hist2D("h_exOut","x' vs. x",80,posR["min"],posR["max"],200,angR["min"],angR["max"],"x_{Out} [mm]","x'_{Out} [#mu rad]",1)
    h_eyIn = Hist2D("h_eyIn","y' vs. y",80,posR["min"],posR["max"],200,angR["min"],angR["max"],"y_{In} [mm]","y'_{In} [#mu rad]",1)
    h_eyOut = Hist2D("h_eyOut","y' vs. y",80,posR["min"],posR["max"],200,angR["min"],angR["max"],"y_{Out} [mm]","y'_{Out} [#mu rad]",1)


    # Define che canvas you need
    c2 = TCanvas('c2','',cW*2,cH*2)
    c4 = TCanvas('c4','test',cW*len(planes),cH*rows)
    c3 = TCanvas('c3','',cW*2,cH*2)

    # Loop over events
    nEntries=t.GetEntriesFast()
    print("Start looping over",nEntries,"events. Please wait...")
    for i, event in enumerate(t): 
        if ((i/nEntries*100)%10) == 0 : print(i/nEntries*100,"% done")

        h_xIn.Fill(event.posXin[0])
        h_yIn.Fill(event.posYin[0])
        h_xyIn.Fill(event.posXin[0],event.posYin[0])
        h_angXIn.Fill(event.angXin[0])
        h_angYIn.Fill(event.angYin[0])
        h_angXYIn.Fill(event.angXin[0],event.angYin[0])
        h_angXOut.Fill(event.angXout[0])
        h_angYOut.Fill(event.angYout[0])
        h_angXYOut.Fill(event.angXout[0],event.angYout[0])
        h_big.Fill(event.angXout[0]-event.angXin[0],event.angXin[0]+event.crystAngX[0])
        #h_big.Fill(event.angXout-event.angXin,event.angXin)
        h_exIn.Fill(event.posXin[0],event.angXin[0])
        h_exOut.Fill(event.posXin[0],event.angXout[0])
        h_eyIn.Fill(event.posYin[0],event.angYin[0])
        h_eyOut.Fill(event.posYin[0],event.angYout[0])

    print("End of loop over events.")

    # Draw what you need
    c4.cd()
    c4.Divide(cols,rows)

    
    c4.cd(1).SetLogy(); h_xIn.Draw(); h_yIn.Draw("SAME")
    c4.cd(1+cols); h_xyIn.Draw("COLZ0")
    c4.cd(2).SetLogy(); h_angXIn.Draw(); h_angYIn.Draw("SAME")
    c4.cd(2+cols); h_angXYIn.Draw("COLZ0")
    c4.cd(3).SetLogy(); h_angXOut.Draw(); h_angYOut.Draw("SAME")
    c4.cd(3+cols); h_angXYOut.Draw("COLZ0")

    c4.Update()

    c2.cd()
    c2.Divide(2,2)

    c2.cd(1); h_exIn.Draw("COLZ0");  print("Emittance-x(pre): % 10.3E [mm-urad]"%EmittanceRMS(h_exIn))
    c2.cd(2); h_exOut.Draw("COLZ0"); print("Emittance-x(post): % 10.3E [mm-urad]"%EmittanceRMS(h_exOut))
    c2.cd(3); h_eyIn.Draw("COLZ0");  print("Emittance-y(pre): % 10.3E [mm-urad]"%EmittanceRMS(h_eyIn))
    c2.cd(4); h_eyOut.Draw("COLZ0"); print("Emittance-y(post): % 10.3E [mm-urad]"%EmittanceRMS(h_eyOut))
    c2.Update()

    c3.cd()
    h_big.Draw("COLZ0")
    c3.Update()


    # Save what you need later
    if savePlot:
        c3.SaveAs("CrysDeflection_"+label+".pdf")
        c3.SaveAs("CrysDeflection_"+label+".png")
        c4.SaveAs("Crystal_"+label+".pdf")
        c4.SaveAs("Crystal_"+label+".png")

    # Wait for people to look at the plots
    input('done with treeLoop(): should I proceed?')
    return
