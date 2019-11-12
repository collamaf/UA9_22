from ROOT import TCanvas, TFile, TH1F, TH2F
import myStyle
from setup import *

### Define the analysis functions you need
def anaPlanes(t):
    print("anaPlanes() reading from ",t.GetName())
    rows=4
    c1 = TCanvas('cmain','Summary',250*len(planes),250*rows)
    h_x = []
    h_y = []
    h_xy = []
    h_cx = []
    h_cy = []
    h_cxcy = []
    c1.Divide(4,rows)
    for i in range(0,len(planes)):
        ## Histograms
        ht_x = TH1F('h_x','pos. x',40,posR["min"],posR["max"])
        ht_y = TH1F('h_y','pos. y',40,posR["min"],posR["max"])
        ht_y.SetLineStyle(2)
        ht_xy = TH2F('h_xy','y vs x',40,posR["min"],posR["max"],40,posR["min"],posR["max"])
        ht_cx = TH1F('h_cx','cos. x',40,cosR["min"],cosR["max"])
        ht_cy = TH1F('h_cy','cos. y',40,cosR["min"],cosR["max"])
        ht_cxcy = TH2F('h_cxcy','cos(y) vs cos(x)',40,cosR["min"],cosR["max"],40,cosR["min"],cosR["max"])
        condT="PlaneId=="+str(planes[i])
        ##
        c1.cd(i+1)
        drawT="Y:X>>h_xy"
        t.Draw(drawT,condT,"COLZ0")
        h_xy.append(ht_xy)
        ##
        c1.cd((i+1)+(1*len(planes)))
        drawT="X>>h_x"
        t.Draw(drawT,condT,"COLZ0")
        h_x.append(ht_x)
        ##
        c1.cd((i+1)+(2*len(planes)))
        drawT="CosY:CosX>>h_cxcy"
        t.Draw(drawT,condT,"COLZ0")
        h_cxcy.append(ht_cxcy)
        ##
        c1.cd((i+1)+(3*len(planes)))
        drawT="CosX>>h_cx"
        t.Draw(drawT,condT,"COLZ0")
        h_cx.append(ht_cx)
    c1.Update()
    input('done with anaPlanes(): should I proceed?')
    return

