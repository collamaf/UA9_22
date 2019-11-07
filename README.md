# UA9Mu

Geant4 simulation for Channeling in view of UA9 mu experiments
Last edit: 07-11-2019

## How to checkout

to clone the repository:
```
git clone https://github.com/collamaf/UA9Mu.git
```
and then insert your username and password



## How to Run:
```
cd build
cmake -DGeant4_DIR=$G4INSTALL ../
make -j4

```

#### Available Command Line Arguments:
- 

#### GEOMETRY (in increasing z coord.)
- Channeling crystal placed at origin. Current size hardcoded in DetConst: 1x70x1.94 mm
- 3 Si detectors: -9.998 m, -0.320 m and 10.756 m
- 4 dummy (empty planes) for scoring purposes: along z at: -10.5m, -Cristal, +Cristal, +10.5m

### PRIMARY PARTICLE
The primary events are 400 GeV/c protons launched at -10.5 m from the crystal with 13.36 microrad x 11.25 microrad divergence.
Modifiable via macro commands



#### PHYSICS
In the example the physics of channeling and volume reflection has been added to the standard Geant4 physics. The description of the used model can be found in the paper ‘A model for the  interaction of high-energy particles in straight and bent crystals implemented in Geant4’ by E. Bagli et al., available online at http://arxiv.org/abs/1403.5819


#### OUTPUT:
The simulation produces 1 .root file, with 3 ntuples:
ExExChTree:
- angXin : incoming particle X angle at the crystal
- angYin : incoming particle Y angle at the crystal
- posXin : hitting X position of the particle at the crystal
- posYin : hitting Y position of the particle at the crystal
- angXout: outgoing particle X angle out of the the crystal
- angYout: outgoing particle Y angle out of the the crystal

Beam: contains info on primary beam
- X, Y, Z [mm]
- PX, PY, PZ
- Ene [GeV]
- Part

Planes: contains info at dummy planes crossing
- X, Y, Z [mm]
- PX, PY, PZ
- Ene [GeV]
- Part
- PlaneId: 0, 1, 2, 3



### CHANGE LOG
07-09-2019:
- First Commit



## TODOs
- Gestione piu intelligente dei parametri (bending, fascio..): linea di comando?
