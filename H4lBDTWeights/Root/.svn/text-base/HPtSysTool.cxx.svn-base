//--------------------------------------------------------------------------------
// Authors: R. Di Nardo      <Roberto.Di.Nardo@cern.ch>
//          K. Nikolopoulos  <Konstantinos.Nikolopoulos@cern.ch>
//--------------------------------------------------------------------------------
#include "H4lBDTWeights/HPtSysTool.h"

#include "TFile.h"
#include "TH1F.h"
#include "TString.h"
#include <iostream>


HPtSysTool::HPtSysTool(TString source)
{

  m_weightsSyst = TFile::Open(source);

  if ( !m_weightsSyst ) {
    std::cout << "ERROR: could not open file with weights: "<<source << std::endl;
  }

//  m_h_weightsPDF  = (TH1F*) m_weightsFile->Get("weightsPDF"); 

    m_h_weightsScale_up    = (TH1F*) m_weightsSyst->Get("varUp");
    m_h_weightsScale_down  = (TH1F*) m_weightsSyst->Get("varDown");


  if ( !m_h_weightsScale_up )
    std::cout << "ERROR: could not get ScaleUp weights " << std::endl;

  if ( !m_h_weightsScale_down )
    std::cout << "ERROR: could not get ScaleDown  weights " << std::endl;

}

HPtSysTool::~HPtSysTool(){
}




float HPtSysTool::GetSysScale_up ( float ptHGen )
{
  int bin = m_h_weightsScale_up->FindBin( ptHGen ); // weight histo is in GeV
  float weight = -1;
  if (bin < m_h_weightsScale_up->GetNbinsX()) {
	weight = m_h_weightsScale_up->GetBinContent(bin);
  } else {
        weight = m_h_weightsScale_up->GetBinContent(m_h_weightsScale_up->GetNbinsX());     
  }
  return weight;
}


float HPtSysTool::GetSysScale_down ( float ptHGen )
{
  int bin = m_h_weightsScale_down->FindBin( ptHGen ); // weight histo is in GeV
  float weight = -1;
  if (bin < m_h_weightsScale_down->GetNbinsX()) {
        weight = m_h_weightsScale_down->GetBinContent(bin);
  } else {
        weight = m_h_weightsScale_down->GetBinContent(m_h_weightsScale_down->GetNbinsX());
  }

  return weight;
}



