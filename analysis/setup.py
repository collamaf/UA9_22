murad = 1.E-6
planes = [0,1,2,3]

xtalX = 2.0 #mm
xtalY = 7.0 #mm
xtalZ = 1.0 #mm 

cH = 300
cW = 300

posR = {
    "min" : -2.0,
    "max" : +2.0
}

cosR = {
    "min" : -0.002,
    "max" : +0.002
}

angR = {
    "min" : -200.,
    "max" : 200.
}

eneR = {
#    "min" : 21.6,
#    "max" : 22.6
    "min" : 395,
    "max" : 400
}

pColor = {
    "proton" : 4,
    "mup" : 46,
    "mum" : 36,
    "photon" : 41
}

### Define utility functions
def hold(string,noStop):
    if not noStop:
        input(string)
    return
