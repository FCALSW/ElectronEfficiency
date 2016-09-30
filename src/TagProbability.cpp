#include "TagProbability.hh"

#include <TFile.h>
#include <TEfficiency.h>
#include <TLorentzVector.h>
#include <TRandom3.h>


#include <iostream>


double TagProbability::GetProbability(const TLorentzVector& electron) const {

  double theta = electron.Theta();
  if(theta > TMath::PiOver2()) theta = TMath::Pi()-theta;
  theta*=1000;

  //we assume that we can find all electrons above 32 mrad with more than 100~GeV
  //Assume perfect tagging above beamcal acceptance
  //  if(theta > 35 && electron.E() > 100 ) return 1.0;

  double phi = electron.Phi()*TMath::RadToDeg();

  if(phi < 0) phi+=360.0;

  //  int energy = (int(electron.E())/100)*100;

  return GetProbability(electron.E(), theta, phi);

}//GetProbability


double TagProbability::GetProbability(double gevEnergy, double mradTheta, double degreesPhi) const {

  //round the energy to the next lowest 100 value
  const int energy = (int(gevEnergy)/100)*100;

  if(degreesPhi < 0) degreesPhi+=360.0;

  std::map<int, TEfficiency*>::const_iterator it = EfficiencyHistograms.find(energy);
  if( it != EfficiencyHistograms.end() ) {
    //    std::cout << "Found Histo"  << std::endl;
    int globalbin = it->second->FindFixBin(mradTheta,degreesPhi);
    //    std::cout << "Globalbin " << globalbin  << std::endl;
    const double prob = it->second->GetEfficiency(globalbin);
    //    std::cout << "E " << energy << " Phi " << degreesPhi << " Theta " << theta << " Prob " << prob  << std::endl;
    return prob;
  }
  return 0.0;

}//GetProbability


bool TagProbability::IsTagged(const TLorentzVector& electron) const {
  const double prob = GetProbability(electron);
  if(  gRandom->Uniform() < prob ) {
    //    std::cout << "Found electron"  << std::endl;
    return true;
  }
  return false;

}//IsTagged



TagProbability::TagProbability(const TString& fileDescriptor):EfficiencyHistograms(){
  for (int i = 500; i <= 1500 ;i+=100) {

    TFile *file = TFile::Open(Form(fileDescriptor,i));
    if( not file ) {
      std::cerr << "File "  << Form(fileDescriptor,i) << " could not be opened."  << std::endl;
      exit (1);
    }

    TEfficiency* tEff = dynamic_cast<TEfficiency*>(file->Get("efficiency72d"));
    //TEfficiency* tEff = dynamic_cast<TEfficiency*>(file->Get("efficiency62d"));
    //    file->ls();
    //    std::cout << tEff  << std::endl;
    if( not tEff ) { std::cout << "Crashed"  << std::endl; exit(1); }
    EfficiencyHistograms[i] = dynamic_cast<TEfficiency*>(tEff->Clone(Form("Prob2d_%i",i)));
    delete tEff;
    file->Close();
    delete file;
  }
}//Constructor


TagProbability::~TagProbability() {
  for (std::map<int, TEfficiency*>::iterator it = EfficiencyHistograms.begin(); it != EfficiencyHistograms.end(); ++it) {
    delete (it->second);
  }
}//D'tor
