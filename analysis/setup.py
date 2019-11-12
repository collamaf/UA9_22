planes = [0,1,2,3]

posR = {
    "min" : -1.0,
    "max" : +1.0
}

cosR = {
    "min" : -0.0001,
    "max" : +0.0001
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
