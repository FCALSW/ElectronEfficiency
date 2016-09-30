#include "TagProbability.hh"
#include <iostream>


int main ()
{
  
  for (int i = 0; i < 100 ;++i) {
    TagProbability tp = TagProbability("/home/sailer/Work/Libraries/ElectronEfficiency/EfficiencyFiles/OBC%i_TwoFourCut_Full_50k_4_40BX.root");

    std::cout <<    tp.GetProbability( 1201.0, 15, 123)   << std::endl;
  }
  

}
