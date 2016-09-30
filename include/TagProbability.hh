#ifndef TAGPROBABILITY_HH
#define TAGPROBABILITY_HH 1

#include <TString.h>

#include <map>

class TLorentzVector;
class TEfficiency;

class TagProbability{
public:
  double GetProbability(const TLorentzVector& electron) const;
  double GetProbability(double gevEnergy, double mradTheta, double degreesPhi) const;
  bool IsTagged(const TLorentzVector& electron) const;

  TagProbability(const TString & fileDescriptor="/Storage/sailer/Analysis/ElectronEfficiency/EfficiencyFiles/OBC%i_TwoFourCut_Full_50k_4_40BX.root");
  ~TagProbability();

private:
  std::map<int, TEfficiency*> EfficiencyHistograms;


};


#endif // TAGPROBABILITY_HH 1
