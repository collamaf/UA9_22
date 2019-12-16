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

def passSelections(event):
    #define event selections here
    return True

# Main function
def treeLoop(t,label = 'lastRun',shiftAngX=0.0,savePlot=False):
    print("treeLoop() reading from ",t.GetName())
    rows = 2
    nlayers = 4
    cols = nlayers

    # Define the histograms you need
    h_xySiDet = Hist2DVec(4,"h_xySiDet","Position on SiDet layers",100,posR["min"],posR["max"],100,posR["min"],posR["max"],"X [mm]","Y [mm]",1)
    h_xSiDet = Hist1DVec(4,"h_xSiDet","Position on SiDet layers",100,posR["min"],posR["max"],"X/Y [mm]",1)
    h_ySiDet = Hist1DVec(4,"h_ySiDet","Position on SiDet layers",100,posR["min"],posR["max"],"X/Y [mm]",2)
    h_angSiDet = Hist2DVec(4,"h_angSiDet","Angles on SiDet layers",100,angR["min"],angR["max"],100,angR["min"],angR["max"],"#theta_{X} [#mu rad]","#theta_{Y} [#mu rad]",1)
    h_angXSiDet = Hist1DVec(4,"h_angXSiDet","Angles on SiDet layers",100,angR["min"],angR["max"],"#theta_{X/Y} [#mu rad]",1)
    h_angYSiDet = Hist1DVec(4,"h_angYSiDet","Angles on SiDet layers",100,angR["min"],angR["max"],"#theta_{X/Y} [#mu rad]",2)
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
    c1 = TCanvas('c1','',cW*cols,cH*2)
    c2 = TCanvas('c2','',cW*cols,cH*2)
    #c4 = TCanvas('c4','test',cW*len(planes),cH*rows)
    c3 = TCanvas('c3','',cW*2,cH*2)
    c4 = TCanvas('c4','',cW*2,cH*2)

    # Loop over events
    nEntries=t.GetEntriesFast()
    print("Start looping over",nEntries,"events. Please wait...")
    for i, e in enumerate(t): 
        if ((i/nEntries*100)%10) == 0 : print(i/nEntries*100,"% done")
        
        # Evaluate xtal in/out parameters
        thetaXin=(e.sdHitX[1]-e.sdHitX[0])/(e.sdHitZ[1]-e.sdHitZ[0])/murad
        thetaYin=(e.sdHitY[1]-e.sdHitY[0])/(e.sdHitZ[1]-e.sdHitZ[0])/murad
        Xin=e.sdHitX[1]-(e.sdHitZ[1]+0.5*xtalZ)*thetaXin*murad
        Yin=e.sdHitY[1]-(e.sdHitZ[1]+0.5*xtalZ)*thetaYin*murad
        #
        thetaXout=(e.sdHitX[3]-e.sdHitX[2])/(e.sdHitZ[3]-e.sdHitZ[2])/murad
        thetaYout=(e.sdHitY[3]-e.sdHitY[2])/(e.sdHitZ[3]-e.sdHitZ[2])/murad
        Xout=e.sdHitX[2]-(e.sdHitZ[2]-0.5*xtalZ)*thetaXout*murad
        Yout=e.sdHitY[2]-(e.sdHitZ[2]-0.5*xtalZ)*thetaYout*murad
        
        #Apply filters here through a function
        if not passSelections(e):
            continue
        # ... or manually
        if thetaXout<500. :
            continue
        if math.fabs(Xin)>0.5*xtalX :
            continue

        for ih in range(0,len(e.sdHitId)):
            h_xSiDet[int(e.sdHitId[ih])].Fill(e.sdHitX[ih])
            h_ySiDet[int(e.sdHitId[ih])].Fill(e.sdHitY[ih])
            h_xySiDet[int(e.sdHitId[ih])].Fill(e.sdHitX[ih],e.sdHitY[ih])
            h_angXSiDet[int(e.sdHitId[ih])].Fill(e.sdAngX[ih]/murad)
            h_angYSiDet[int(e.sdHitId[ih])].Fill(e.sdAngY[ih]/murad)
            h_angSiDet[int(e.sdHitId[ih])].Fill(e.sdAngX[ih]/murad,e.sdAngY[ih]/murad)

        h_xIn.Fill(Xin)
        h_yIn.Fill(Yin)
        h_xyIn.Fill(Xin,Yin)
        h_angXIn.Fill(thetaXin)
        h_angYIn.Fill(thetaYin)
        h_angXYIn.Fill(thetaXin,thetaYin)
        h_angXOut.Fill(Xout)
        h_angYOut.Fill(Yout)
        h_angXYOut.Fill(thetaXout,thetaYout)
        h_big.Fill(thetaXout-thetaXin,thetaXin+e.crystAngX[0])
        h_exIn.Fill(Xin,thetaXin-float(shiftAngX))
        h_exOut.Fill(Xout,thetaXout-float(shiftAngX))
        h_eyIn.Fill(Yin,thetaYin)
        h_eyOut.Fill(Yout,thetaYout)

    print("End of loop over events.")

    # Draw what you need
    c1.cd(); c1.Divide(cols,2)
    for ih in range(0,nlayers):
        c1.cd(ih+1); h_xySiDet[ih].Draw("CONTZ")
        c1.cd(ih+1+cols).SetLogy(); h_ySiDet[ih].Draw(); h_xSiDet[ih].Draw("SAME"); 
    c1.Update()

    c2.cd(); c2.Divide(cols,2)
    for ih in range(0,nlayers):
        c2.cd(ih+1); h_angSiDet[ih].Draw("CONTZ")
        c2.cd(ih+1+cols).SetLogy(); h_angYSiDet[ih].Draw(); h_angXSiDet[ih].Draw("SAME"); 
    c2.Update()
    
#    c4.cd(1).SetLogy(); h_xIn.Draw(); h_yIn.Draw("SAME")
#    c4.cd(1+cols); h_xyIn.Draw("COLZ0")
#    c4.cd(2).SetLogy(); h_angXIn.Draw(); h_angYIn.Draw("SAME")
#    c4.cd(2+cols); h_angXYIn.Draw("COLZ0")
#    c4.cd(3).SetLogy(); h_angXOut.Draw(); h_angYOut.Draw("SAME")
#    c4.cd(3+cols); h_angXYOut.Draw("COLZ0")
#
#    c4.Update()
#
    c3.cd(); c3.Divide(2,2)

    c3.cd(1); h_exIn.Draw("CONTZ");  print("Emittance-x(pre): % 10.3E [mm-urad]"%EmittanceRMS(h_exIn))
    c3.cd(2); h_exOut.Draw("CONTZ"); print("Emittance-x(post): % 10.3E [mm-urad]"%EmittanceRMS(h_exOut))
    c3.cd(3); h_eyIn.Draw("CONTZ");  print("Emittance-y(pre): % 10.3E [mm-urad]"%EmittanceRMS(h_eyIn))
    c3.cd(4); h_eyOut.Draw("CONTZ"); print("Emittance-y(post): % 10.3E [mm-urad]"%EmittanceRMS(h_eyOut))
    c3.Update()

    c4.cd()
    h_big.Draw("CONTZ")
    c4.Update()


    # Save what you need later
    if savePlot:
        c3.SaveAs("CrysDeflection_"+label+".pdf")
        c3.SaveAs("CrysDeflection_"+label+".png")
        c4.SaveAs("Crystal_"+label+".pdf")
        c4.SaveAs("Crystal_"+label+".png")

    # Wait for people to look at the plots
    input('done with treeLoop(): should I proceed?')
    return
