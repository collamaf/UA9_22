#!/bin/bash

# runRotate.sh -m=yourMacro.mac -n=NPrim -l=commonLabel

# angles here in urad (milliradians) - will take care later about that
#angles=(-100 -90 -80 -70 -60 -50 -40 -30 -20 -10 0 10 20 30 40 50 60 70 80 90 100)
#angles=(-100 -60 0 60 100)
angles=(0)
LABEL="na"


for i in "$@"
do
case $i in
    -m=*|--macro=*)
    MACRO="${i#*=}"
    shift # past argument=value
    ;;
    -n=*|--NPrim=*)
    NPRIM="${i#*=}"
    shift # past argument=value
    ;;
    -l=*|--label=*)
    LABEL="${i#*=}"
    shift # past argument=value
    ;;
    --default)
    DEFAULT=YES
    shift # past argument with no value
    ;;
    *)
          # unknown option
    ;;
esac
done

OPTIONS="-Label $LABEL -NPrim $NPRIM -Part -11 -Ene 50 "

for a in "${angles[@]}"
do
    tmpFolder="run_${LABEL}_a${a//-/m}"
    logFile="sim_${LABEL}_a${a//-/m}.log"
#    if [ ! -d $tmpFolder ] 
#    then
#	echo "Create folder $tmpFolder"
#	mkdir $tmpFolder 
#    fi
#    cd $tmpFolder
#    cp ../$MACRO .
    cmd="./channeling $MACRO -CrystAng ${a}E-6 $OPTIONS"
    echo "$cmd"
    ##eval $cmd >& $logFile
    hdcmd=$(cat $logFile |grep hadd |grep G4WT0)
    echo "$hdcmd"
    ##eval ${hdcmd#*>}    
#    cd ..
done

#merge output
filesToMerge=$(ls | grep ${LABEL} |grep root)
mergedFile=$( cut -d '_' -f 1 <<< $filesToMerge)"_merged.root"
mrgcmd="hadd $mergedFile $filesToMerge"
echo $mrgcmd
##eval $mrgcmd
