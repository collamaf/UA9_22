from ROOT import TCanvas, TFile, TH1F, TH2F
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

# Main function
def treeLoop(t,label = 'lastRun',savePlot=False):
    print("treeLoop() reading from ",t.GetName())
    rows = 4

    # Define the histograms you need
    h_x = Hist1DVec(len(planes),"h_x","pos. x",40,posR["min"],posR["max"],"X [mm]",1)
    h_y = Hist1DVec(len(planes),"h_y","pos. y",40,posR["min"],posR["max"],"Y [mm]",2)
    h_xy = Hist2DVec(len(planes),"h_xy","y vs x",40,posR["min"],posR["max"],40,posR["min"],posR["max"],"X [mm]","Y [mm]",1)
    h_cx = Hist1DVec(len(planes),"h_cx","cos. x",40,cosR["min"],cosR["max"],"cosX [rad]",1)
    h_cy = Hist1DVec(len(planes),"h_cy","cos. y",40,cosR["min"],cosR["max"],"cosY [rad]",2)
    h_cxcy = Hist2DVec(len(planes),"h_cxcy","cos. y vs cos. x",40,cosR["min"],cosR["max"],40,cosR["min"],cosR["max"],"cosY [rad]","cosY [rad]",1)
    h_Ene = Hist1DVec(len(planes),"h_Ene","Energy",40,eneR["min"],eneR["max"],"Energy [GeV]",1)
    h_P = Hist1DVec(len(planes),"h_P","Momentum",40,eneR["min"],eneR["max"],"Momentum [GeV]",1)
    h_big = Hist2D("h_big","Deflection vs. incidence",400,-200.0,200.0,400,-200.,200.0,"Deflection [#mu rad]","Incidence angle [#mu rad]",1)


    # Define che canvas you need
    c2 = TCanvas('c2','',cW,cH)
    c3 = TCanvas('c3','',cW*2,cH*2)
    c4 = TCanvas('c4','test',cW*len(planes),cH*rows)

    # Loop over events
    nEntries=t.GetEntriesFast()
    print("Start looping over",nEntries,"events. Please wait...")
    for i, event in enumerate(t): 
        if ((i/nEntries*100)%10) == 0 : print(i/nEntries*100,"% done")
#        print("Event: ",i)
        # Loop over planes and fill corresponding histo
        for ip in range(0,min(len(event.X),len(event.Y))):
            h_x[ip].Fill(event.X[ip])
            h_y[ip].Fill(event.Y[ip])
            h_xy[ip].Fill(event.X[ip],event.Y[ip])
            h_cx[ip].Fill(event.CosX[ip])
            h_cy[ip].Fill(event.CosY[ip])
            h_cxcy[ip].Fill(event.CosX[ip],event.CosY[ip])
            h_Ene[ip].Fill(event.Ene[ip])
        # Fill what is not plane-dependent
        if len(event.CosX) > 2 :
            h_big.Fill(-1*(math.acos(event.CosX[2])-math.acos(event.CosX[1]))*1.E6,(0.5*math.pi-math.acos(event.CosX[1]))*1.E6)
    print("End of loop over events.")

    # Draw what you need
    c2.cd().SetLogy()
    h_Ene[0].Draw()
    h_Ene[1].Draw("SAME")
    h_Ene[2].Draw("SAME")
    h_Ene[3].Draw()
    c2.Update()

    c3.cd()
    h_big.Draw("COLZ0")
    c3.Update()
    c4.cd()
    c4.Divide(len(planes),rows)

    for ip in range(0,len(planes)):
        c4.cd((ip+1)+(0*len(planes))); h_xy[ip].Draw("COLZ0")
        c4.cd((ip+1)+(1*len(planes))).SetLogy(); h_x[ip].Draw(); h_y[ip].Draw("SAME")
        c4.cd((ip+1)+(2*len(planes))); h_cxcy[ip].Draw("COLZ0")
        c4.cd((ip+1)+(3*len(planes))).SetLogy(); h_cx[ip].Draw(); h_cy[ip].Draw("SAME")
    c4.Update()

    # Save what you need later
    if savePlot:
        c4.SaveAs("Summary_"+label+".pdf")
        c4.SaveAs("Summary_"+label+".png")
        c2.SaveAs("Ene_"+label+".pdf")
        c2.SaveAs("Ene_"+label+".png")
        c3.SaveAs("Channeling_"+label+".pdf")
        c3.SaveAs("Channeling_"+label+".png")


    # Wait for people to look at the plots
    input('done with treeLoop(): should I proceed?')
    return
