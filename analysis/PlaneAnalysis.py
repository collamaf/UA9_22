from ROOT import TCanvas, TFile, TH1F, TH2F
import math
import myStyle
from setup import *

### Define the analysis functions you need
def anaPlanes(t,label = 'lastRun',savePlot=False):
    print("anaPlanes() reading from ",t.GetName())
    rows=4
    c1 = TCanvas('cmain','Summary',cW*len(planes),cH*rows)
    c1.Divide(len(planes),rows)
    c2 = TCanvas('c2','Additional info', cW*2,cH)
    c2.Divide(2,1)
    h_x = []
    h_y = []
    h_xy = []
    h_cx = []
    h_cy = []
    h_cxcy = []
    h_Ene = []
    h_P = []
    for i in range(0,len(planes)):
        ## Histograms
        ht_x = TH1F('h_x','pos. x',40,posR["min"],posR["max"])
        ht_y = TH1F('h_y','pos. y',40,posR["min"],posR["max"])
        ht_y.SetLineStyle(2)
        ht_xy = TH2F('h_xy','y vs x',40,posR["min"],posR["max"],40,posR["min"],posR["max"])
        ht_cx = TH1F('h_cx','cos. x',40,cosR["min"],cosR["max"])
        ht_cy = TH1F('h_cy','cos. y',40,cosR["min"],cosR["max"])
        ht_cxcy = TH2F('h_cxcy','cos(y) vs cos(x)',40,cosR["min"],cosR["max"],40,cosR["min"],cosR["max"])
        ht_Ene = TH1F('h_Ene','Energy',40,eneR["min"],eneR["max"])
        ht_P = TH1F('h_P','Momentum',40,eneR["min"],eneR["max"])
        condT="PlaneId=="+str(planes[i])
        ##
        c1.cd(i+1)
        drawT="Y:X>>h_xy"
        t.Draw(drawT,condT,"COLZ0")
        h_xy.append(ht_xy)
        ##
        c1.cd((i+1)+(1*len(planes))).SetLogy()
        drawT="X>>h_x"
        t.Draw(drawT,condT,"")
        h_x.append(ht_x)
        ##
        c1.cd((i+1)+(2*len(planes)))
        drawT="CosY:CosX>>h_cxcy"
        t.Draw(drawT,condT,"COLZ0")
        h_cxcy.append(ht_cxcy)
        ##
        c1.cd((i+1)+(3*len(planes)))
        drawT="CosX>>h_cx"
        t.Draw(drawT,condT,"")
        h_cx.append(ht_cx)
        ##
        c2.cd(1).SetLogy()
        drawT="Ene>>h_Ene"
        t.Draw(drawT,condT,"")
        h_Ene.append(ht_Ene)
        ##
        c2.cd(2).SetLogy()
        drawT="P>>h_P"
        t.Draw(drawT,condT,"")
        h_P.append(ht_P)
    c1.Update()
    c2.Update()

    if savePlot:
        c1.SaveAs("Summary_"+label+".pdf")
        c1.SaveAs("Summary_"+label+".png")
        c2.SaveAs("EneP_"+label+".pdf")
        c2.SaveAs("EneP_"+label+".png")


    input('done with anaPlanes(): should I proceed?')
    return

def treeLoop(t,label = 'lastRun',savePlot=False):
    rows = 4
    h_x = []; ht_x = TH1F('h_x','pos. x',40,posR["min"],posR["max"]); ht_x.GetXaxis().SetTitle("X [mm]")
    h_y = []; ht_y = TH1F('h_y','pos. y',40,posR["min"],posR["max"]); ht_y.GetXaxis().SetTitle("Y [mm]")
    h_xy = []; ht_xy = TH2F('h_xy','y vs x',40,posR["min"],posR["max"],40,posR["min"],posR["max"]); ht_xy.GetXaxis().SetTitle("X [mm]"); ht_xy.GetYaxis().SetTitle("Y [mm]")
    h_cx = []; ht_cx = TH1F('h_cx','cos. x',40,cosR["min"],cosR["max"]); ht_cx.GetXaxis().SetTitle("cosX [rad]")
    h_cy = []; ht_cy = TH1F('h_cy','cos. y',40,cosR["min"],cosR["max"]); ht_cy.GetXaxis().SetTitle("cosY [rad]")
    h_cxcy = []; ht_cxcy = TH2F('h_cxcy','cos.y vs cos.x',40,cosR["min"],cosR["max"],40,cosR["min"],cosR["max"]); ht_cxcy.GetXaxis().SetTitle("cosX [rad]"); ht_cxcy.GetYaxis().SetTitle("cosY [rad]")
    
    h_Ene = []; ht_Ene = TH1F('h_Ene','Energy',40,eneR["min"],eneR["max"]); ht_Ene.GetXaxis().SetTitle("Energy [GeV]")
    h_P = []; ht_P = TH1F('h_P','Momentum',40,eneR["min"],eneR["max"]); ht_P.GetXaxis().SetTitle("Momentum [GeV]")

    for i in range(0,len(planes)):
        h_x.append(ht_x.Clone())
        h_y.append(ht_y.Clone())
        h_xy.append(ht_xy.Clone())
        h_cx.append(ht_cx.Clone())
        h_cy.append(ht_cy.Clone())
        h_cxcy.append(ht_cxcy.Clone())
        h_Ene.append(ht_Ene.Clone())

    c2 = TCanvas('c2','',cW,cH)
    c3 = TCanvas('c3','',cW*2,cH*2)
    c4 = TCanvas('c4','test',cW*len(planes),cH*rows)
    h_big = TH2F('h_big','Deflection vs. incidence',400,-2.0,2.0,400,-2.,2.0)
    h_big.GetXaxis().SetTitle("Deflection [mrad]")
    h_big.GetYaxis().SetTitle("Incidence angle [mrad]")
    for event in t: 
        for ip in range(0,min(len(event.X),len(event.Y))):
            h_x[ip].Fill(event.X[ip])
            h_y[ip].Fill(event.Y[ip])
            h_xy[ip].Fill(event.X[ip],event.Y[ip])
            h_cx[ip].Fill(event.CosX[ip])
            h_cy[ip].Fill(event.CosY[ip])
            h_cxcy[ip].Fill(event.CosX[ip],event.CosY[ip])
            h_Ene[ip].Fill(event.Ene[ip])
        if len(event.CosX) > 2 :
            h_big.Fill(-1*(math.acos(event.CosX[2])-math.acos(event.CosX[1]))*10e3,(0.5*math.pi-math.acos(event.CosX[1]))*10e3)

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
        c4.cd((ip+1)+(1*len(planes))).SetLogy(); h_x[ip].Draw()
        c4.cd((ip+1)+(2*len(planes))); h_cxcy[ip].Draw("COLZ0")
        c4.cd((ip+1)+(3*len(planes))).SetLogy(); h_cx[ip].Draw()
    c4.Update()

    if savePlot:
        c4.SaveAs("Summary_"+label+".pdf")
        c4.SaveAs("Summary_"+label+".png")
        c2.SaveAs("Ene_"+label+".pdf")
        c2.SaveAs("Ene_"+label+".png")
        c3.SaveAs("Channeling_"+label+".pdf")
        c3.SaveAs("Channeling_"+label+".png")

    input('done with treeLoop(): should I proceed?')
    return
