# UA9_22

Geant4 simulation for Channeling in view of UA9 mu experiments **New 2022 Version**
Last edit: 25-02-2022

- [Checkout the code](#checkout-the-code)
- [Compile the code](#compile-the-code)
- [Run simulations](#run-simulations)
  - [Available Command Line Arguments](#available-command-line-arguments)
  - [Geometry](#geometry)
  - [Primary particle](#primary-particle)
  - [Physics](#physics)
  - [Output](#output)
- [Analyze simulations](#analyze-simulations)
- [Process Data from UA9](#process-data-from-ua9)
- [Compare Data to Simulations](#compare-data-to-simulations)
- [Plot acceptances](#plot-acceptances)
- [CHANGELOG](#changelog)
- [TODOs](#todos)

## Checkout the code

to clone this repository
```
git clone https://github.com/collamaf/UA9Mu.git
```
and then insert your username and password.

## Compile the code

```
cd build
cmake -DGeant4_DIR=$G4INSTALL ../
make -j4
```
CAVEAT - For now the sim correctly works only if Geant is compiled with MT. Then you can use only 1 thread by using in the macro:
```
/run/numberOfThreads 1
```

## Run simulations
Once compiled the code you can run simulation going into the `build` folder and launching the macro
```
cd build
./channeling -{arg} VALUE etc etc
./channeling -Vis 1 -CrystX 1000 -CrystY 1000 -CrystZ 2000 
```
There is a script to quickly launch a simulation (after compiling the code), which should work in the general case
```
source runRotate.sh -m=ua9_ref0.mac -n=10000 -l=SimSq
``` 
where in `runRotate.sh` you need to define at the top the angles you like to generate. This script is simply setting up the environment and sending the `./channeling` macro on different angles.
The macro `ua90_ref0.mac` is the reference macro for the UA9 setup, `10000` are the generated primaries. The output goes in `mUA9SimSq_Part_Ene180_CrystAng*_N10000.root` and the log of the simulation in `sim_SimSq_a*.log`.

#### Available Command Line Arguments
- Ene: beam energy [GeV]
- Part: beam particle [PDG code]
- NPrim: number of primaries to simulate
- SigmaX/Y: beam divergence [rad]
- BR: crystal bending radius [m]
- CrystX/Y/Z: crystal dimensions [mm]
- CrystAng: crystal horizontal rotation angle [rad]
- Mag: magnetic field [T]
- NoDet: remove detector material
- Plane?Z: Z position of dummy planes [m]
- Det?Z: Z position of detectors [m]
- KeepSec: keep (and propagate) secondary particles (Default is off)
- Vis: 1 for visualization
- Setup: 1 is setup 1 of 2022 UA9 measurements, 3 for triangle beam recombination (adds othre 2 Xs and 4 scoring planes)
- Telescope: places only two Si detectors after X3 and moves Planes 3 and 7 to their end
- NoCryst2: removes (the material of) X2, needed to study triangle configuration
- NoCh: turns off channeling in crystals (useful to study for example MS in Si)


#### Geometry
Note: this is expressed in increasing z coordinates
- Channeling crystal placed at origin.
- 4 Si detectors:
- 4 dummy (empty planes) for scoring purposes: along z at: [default] -10.5m, -Cristal, +Cristal, +10.5m

#### Primary particle
The primary events are 400 GeV/c protons launched at -10.5 m from the crystal with 13.36 microrad x 11.25 microrad divergence.
Modifiable via macro commands (GPS)



#### Physics
In the example the physics of channeling and volume reflection has been added to the standard Geant4 physics. The description of the used model can be found in the paper ‘A model for the  interaction of high-energy particles in straight and bent crystals implemented in Geant4’ by E. Bagli et al., available online at http://arxiv.org/abs/1403.5819


#### Output
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

## Analyze simulations
### Classic analysis python program
Once you ran the simulation and have an output file such as `mUA9_N1000.root` you can run the following command
```
python(3) Ana_mUA9.py --fileName mUA9_N1000.root --tree Planes
```
and as a result you'll get a canvas with plots for every plane (_vertical rows_) showing (from top to bottom): y vs. x, x, CosY vs. cosX, cosX.

To dump the content of the simulated ROOT file to a `.dat` file for subsequent analysis (see next) a useful, yet simple, script `dumpRootToCSV.py` is available and can be run as
```
python dumpRootToCSV.py --fileName build/mUA9SimSq_Part_Ene180_CrystAngXXXX_N10000.root
```
where `XXX` is the angle in the file name you like to process. Move the produced `.dat` files to the `BigDataFiles` for subsequent processing.

**Note:** The `dumpRootToCSV.py` script currently implements also the possibility to smear the angular resolution (x-coordinate) with a random gaussian smearing tuned by the parameter `smearSigmaX` inside the script itself. It's set to 0 by default but can be changed manually when needed.

**Note:** In the simulated files the name contains the angle with the wrong sign so when producing the `.dat` file change that in the name (+50 should be named `min50`, -30 should be named `plus30`).

### Triangle Analysis
#### *AnaTriangle.C*
Simple root macro that reads a root file and creates histograms of interest. Deprecated in favor of a looping macro, that instead allows also to ask for example if a given track has been channeled by X1 etc
#### *AnaTriangleEvent.C/h*
Root macro based on `MakeClass` that loops on each entry, allowing to create histos of interest following the track along each crystal.
```
root -l mUA9_Conf3_SigmaX1Y0Z0_N10000.root
L ../analysis/AnaTriangleEvent.C
c=new AnaTriangleEvent(Planes,"SigmaNoDet10k")
c->Loop()
```
#### *Task1.C*
- Simple root macro that reads 2 root files and analyzes the triangle beam recombination configuration, i.e. comparing runs w/ and w/o X2
- File names are hardocoded, but can be choosen thanks to 2 flags: `caso=3,7`, chooses the plane to study (3 is after X3, 7 is at +10m), and `flagDet` chooses if consider the case w/ or w/o detectors.

## Backward engineering (April '21 - a year later)
## Process Data from UA9
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
- Macro `analysis/FilterData.ipynb` is to filter large data files according to some preliminary cuts: `max_d0x = 1.5` and `max_d0y = 1.5`. This create a smaller file named `*_flt.dat`. A copy of the filtered files is being placed in `@lxplus.cern.ch:/afs/cern.ch/user/m/mbauce/work/public/UA9_data/`, together with simulated runs.

## Compare Data to Simulations
The macro `analysis/CompareRuns.ipynb` is analysing runs of data and eventually comparing a set of them (e.g. can be Data at different angles, Sims at different angles or Data/Sim comparison for a given angle). You need one or more `.dat` files to analyse. 
At the beginning of the jupyter macro you can define the files you want to analyse: setting `whichFiles` to `Sim`, `Data`, `All` is enabling a set of simulated samples, data samples, or both. This is checking whether files exist in the local Data folder (typically `BigDataFiles`) and ignoring the missing ones. You can set `whichFiles` to `Comp` if you want to compare specific Data/Simulated samples, side-by-side: in the corresponding part of the code you can set the desired datasets. 

NOTE: In the list of dataset, the macro is looking for a reference dataset (angle 0, aligned to perfect channelling): if this is missing you may encounter several complaints.

NOTE: Check carefully the plots and read the messages between cells: make sure you always understand what is happening!


The macro `analysis/CompareRuns.ipynb` is writing at the very end (last cell) the acceptances in the `Acceptances.txt` file. Check the code and make sure you understand what's happening and how these are evaluated. These are the fraction of initial events entering a given window alighned with the outgoing channeled beam, with a N-sigma width given by the fit on the outgoing angle distribution of the dataset corresponding to *perfect channelling alignement*.

## Plot acceptances

The commands below are producing the plot with acceptances as a function of the impinging angle
```
cd analysis
python plotAcceptances.py
```
This is reading the "Acceptances.txt" file so you need to check what is in there, unless you just generated one with the `analysis/CompareRuns.ipynb` macro.

## CHANGELOG
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

06-04-2021: by mbauce
- Cleaned a bit the code, macros, improved the `README` and tested the flow.

25-02-2022: by collamaf
- Fix indentation
- Little cleaning of geo
- Add possibility to pass from command lines also Z position of detectors (-Det?Z) and dummyPlanes (-Plane?Z), both in m. 

31-03-2022: by collamaf
- Add possibility to pass from command line also the experimental setup: 1 loads `mua922_conf1.mac` 
- ~~Automatic merge of multiple root files after run~~

19-04-2022: by collamaf
- Add possibility to disable from command line also channeling in first crystal (`NoCh`)
- Add trigger logic: save events having hit all 3 crystals

06-05-2022: by collamaf
- Add possibility to remove from command line the presence of X2 (`NoCryst2`)
- Add possibility to create a detector telescope after X3 (`Telescope`)


## TODOs
- need to create a macro for digi/smearing of SiDet hits
- need to create a macro for flexible data analysis of SiDet hits 
