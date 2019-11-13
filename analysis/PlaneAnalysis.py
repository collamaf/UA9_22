from ROOT import TCanvas, TFile, TH1F, TH2F
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

