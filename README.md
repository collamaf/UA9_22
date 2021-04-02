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
- KeepSec: keep (and propagate) secondary particles (Default is off)
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

## Backward engineering
### Process Data from UA9
- The UA9 files are in `@lxplus.cern.ch:/eos/experiment/UA9/H8/current/dat`. Currently available

|File | Size | Info|
|------------|--------|--------|
|ACP80_6534.dat | 342 Mb | angle +20 (AM)|
|ACP80_0.dat | 7.1 Gb | angle 0|
|ACP80_plus10.dat | 4.4 Gb | angle +10 (VR|
|ACP80_plus50.dat | 2.3 Gb | angle +50 (VR)|
|ACP80_plus90.dat | 2.6 Gb | angle +90 (VR)|
|ACP80_min50.dat | 2.3 Gb | angle -50 (CH)|
|ACP80_min70.dat | 2.3 Gb | angle -70 (CH)|
|ACP80_min90.dat | 5.0 Gb | angle -90 (CH)|

- Need to remove some zeroes in the `.dat` files which are appearing in the form of lines such as `0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0`. A command should do the trick (files are huge, it will take some time)
```
cat ACP80_0.dat | grep -v '0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0' >& ACP80_0.dat_nozeros
mv ACP80_0.dat_nozeros ACP80_0.dat
```
- Macro `analysis/FilterData.ipynb` is to filter large data files according to some preliminary cuts: `max_d0x = 1.5` and `max_d0y = 1.5`. This create a smaller file named `*_flt.dat`. A copy of the filtered files is being placed in `@lxplus.cern.ch:/eos/user/m/mbauce/UA9_data/`

### Run and process simulation 

*coming soon, need to re-check the instructions above*

### Compare Data to Simulation
- Macro `analysis/CompareRuns.ipynb` is analysing runs of data and eventually comparing a set of them (e.g. can be Data at different angles, Sims at different angles or Data/Sim comparison for a given angle). You need one each to run the comparison. At the beginning of the jupyter macro you can (un-)comment the files you like to analyse. Check carefully the plots and read the messages between cells. Process first DATA, then Sim (if doing all at once it will probably crash/complain).
- Macro `analysis/CompareRuns.ipynb` is writing at the very end the acceptances in the `Acceptances.txt` file (and doing other stuff). Check you understand what's happening and how these are evaluated.
- The commands below are producing the plot with acceptances as a function of the impinging angle
```
cd analysis
python plotAcceptances.py
```

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

28-11-2019: by mbauce
- The removal of crystal using 'NoCryst' now works fine

29-11-2019: by collmaf
- Add command line parameter ("KeepSec") to keep and track secondary particles. Deep perf impact (~x 100 for 50GevMu).

06-12-2019: by mbauce
- created a first setup for mUA9 TB - see mUA9_tb0.mac
- Moved to 4 Si layers with size available in macro
- Renamed the ExExChTree to ExpTree
- Added to the aforementioned tree the info from the Si detectors (hits Id,X,Y,Z)

03-03-2020: by collamaf
- Fix errore in entries of Beam root leaf: P was missing, for now I fill twice with E

04-03-2020: by collamaf
- Add default value for fSiDetSize. No more need for macros

## TODOs
- need to create a macro for digi/smearing of SiDet hits
- need to create a macro for flexible data analysis of SiDet hits 
