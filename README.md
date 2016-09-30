# ElectronEfficiency

## BuildStatus
[![Build Status](https://travis-ci.org/FCALSW/ElectronEfficiency.svg?branch=master)](https://travis-ci.org/FCALSW/ElectronEfficiency)

## HowTo

Requires `$ROOTSYS` is set, and cmake in the `$PATH`
Then:
```
mkdir build
cd build
cmake ..
make install
```
Producing libTagProbability.so. The folder EfficiencyFiles contains the efficiencies in root 2d efficiency histograms

To use it
Create an object (once per analysis, not once per event...
```
TagProbability myTP("Path/To/EfficienyFiles/OBC%i_TwoFourCut_Full_50k_4_40BX.root"); //The %i is important
```
Then you can call
```
   double GetProbability(const TLorentzVector& electron) const;
   double GetProbability(double gevEnergy, double mradTheta, double degreesPhi) const;
   bool IsTagged(const TLorentzVector& electron) const;
```
to query for the efficiency, or isTagged which will say true/false based 
on random number generator
