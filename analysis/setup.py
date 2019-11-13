planes = [0,1,2,3]

cH = 300
cW = 300

posR = {
    "min" : -10.0,
    "max" : +10.0
}

cosR = {
    "min" : -0.0002,
    "max" : +0.0002
}

eneR = {
    "min" : 21.6,
    "max" : 22.6
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
