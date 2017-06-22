//--------------------------------------------------------------------------------
// Authors: R. Di Nardo      <Roberto.Di.Nardo@cern.ch>
//          K. Nikolopoulos  <Konstantinos.Nikolopoulos@cern.ch>
//--------------------------------------------------------------------------------
#ifndef HPTSYSTOOL_H
#define HPTSYSTOOL_H

#include "TFile.h"
#include "TH1F.h"
#include "TString.h"
#include <iostream>

class HPtSysTool
{

 public:
  HPtSysTool(TString source="ScaleHist.root");
  ~HPtSysTool();

//  float GetSysPDF_up     ( float ptWGen ); // Higgs pt in GeV
//  float GetSysPDF_down   ( float ptWGen ); // Higgs pt in GeV
  float GetSysScale_up   ( float ptWGen ); // Higgs pt in GeV
  float GetSysScale_down ( float ptWGen ); // Higgs pt in GeV
//  float GetSysAll_up   ( float ptWGen ); // Higgs pt in GeV
//  float GetSysAll_down ( float ptWGen ); // Higgs pt in GeV



 private:

  TFile* m_weightsSyst;

  TH1F* m_h_weightsScale_up;
  TH1F* m_h_weightsScale_down;


};




#endif // HPTSYSTOOL_H
