# UA9Mu

Geant4 simulation for Channeling in view of UA9 mu experiments
Last edit: 07-11-2019

CAVEAT - For now the sim correctly works only if Geant is compiled with MT. Then you can use only 1 thread by using in the macro:
```
/run/numberOfThreads 1
```

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
./channeling -{arg} VALUE etc etc
./channeling -Vis 1 -CrystX 1000 -CrystY 1000 -CrystZ 2000 
```

#### Available Command Line Arguments:
- Ene: beam energy [GeV]
- Part: beam particle [PDG code]
- NPrim: number of primaries to simulate
- SigmaX/Y: beam divergence [rad]
- BR: crystal bending radius [m]
- CrystX/Y/Z: crystal dimensions [mm]
- CrystAng: crystal horizontal rotation angle [rad]
- Mag: magnetic field [T]
- NoDet: remove detector material
- Vis: 1 for visualization


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
- CosX, CosY, CosZ
- Ene [GeV]
- Part

Planes: contains info at dummy planes crossing
- X, Y, Z [mm]
- CosX, CosY, CosZ
- P, [GeV], Ene [GeV]
- Time [ns]
- Part
- PlaneId: 0, 1, 2, 3

## How to analyze simulation results
Once you ran the simulation and have an output file such as `mUA9_N1000.root` you can run the following command
```
python(3) Ana_mUA9.py --fileName mUA9_N1000.root --tree Planes
```
and as a result you'll get a canvas with plots for every plane (_vertical rows_) showing (from top to bottom): y vs. x, x, CosY vs. cosX, cosX.

### CHANGE LOG
07-09-2019:
- First Commit

11-11-2019: by collamaf
- Deep reorganisation of main: now loads a default macro with some settings, that you can change via command line
- Command line parameters arrive via map to all routines
- Add hadd command print at the end of (each) run to merge root files and delete temporary ones
- Add magnetic field after target. Default is off.

12-11-2019: by mbauce
- Added analysis and plotting macro
- Changed naming convention (PX->CosX and added P) 

13-11-2019: by collamaf
- Add timing information
- Fix primary particle name in outputfile
- Add flag to remove detector materials

13-11-2019: by mbauce
- Added plot for deflection vs. incident angle
- Removed part of G4 log
- macro modified (added event loop)

26-11-2019: by mbauce
- Added emittance plot and emittance calculation (TBC)
- Added '--ana BlaBla' to analysis macro to choose
- other minor optimizations

27-11-2019: by mbauce
- Modified default parameters in 'ua9_ref0.mac'
- Crystal rotation is now incremental (wrt original rotation)
- The above should fix also the "0" case

## TODOs
- [] Sistemare readme
- [] elegantizzare particella primaria da linea di comando
