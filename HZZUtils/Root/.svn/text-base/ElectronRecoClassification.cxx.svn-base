#include "HZZUtils/ElectronRecoClassification.h"
#include <cmath>
#include <iostream>

ElectronRecoClassification::ElectronRecoClassification(const std::string& name) : AsgTool ( name ) {
}

ElectronRecoClassification::~ElectronRecoClassification()
{
}

ElectronRecoClassification::RecoType ElectronRecoClassification::getRecoClassification(const xAOD::Electron& electron) const
{

  bool success = true;
  //get vars from xAOD::Electron
  float eta = 0;
  float TRTHighTOutliersRatio = 0; 
  float f1 = 0; 
  float rphi = 0; 
  float e237 = 0;
  float e277 = 0;
  uint8_t nPix = 0; 
  uint8_t nPixDeadSensors = 0;
  uint8_t nBlayerHits = 0; 
  bool expectBlayer = false;
  uint8_t nTRT = 0; 
  uint8_t nTRTHigh = 0;
  uint8_t nTRTOutliers = 0;
  uint8_t nTRTHighOutliers = 0;
  uint8_t expectedBlayerHits = 0;

  const xAOD::TrackParticle * electronTrack = electron.trackParticle();
  success = success && electronTrack->summaryValue( nTRT, xAOD::numberOfTRTHits);
  success = success && electronTrack->summaryValue( nTRTHigh, xAOD::numberOfTRTHighThresholdHits);
  success = success && electronTrack->summaryValue( nTRTOutliers, xAOD::numberOfTRTOutliers);
  success = success && electronTrack->summaryValue( nTRTHighOutliers, xAOD::numberOfTRTHighThresholdOutliers);
  success = success && electronTrack->summaryValue( nPix, xAOD::numberOfPixelHits);
  success = success && electronTrack->summaryValue( nPixDeadSensors, xAOD::numberOfPixelDeadSensors);
  success = success && electronTrack->summaryValue( nBlayerHits, xAOD::numberOfBLayerHits);
  success = success && electronTrack->summaryValue( expectedBlayerHits, xAOD::expectBLayerHit);

  double nTRTTotal = nTRT + nTRTOutliers;

  if(nTRTTotal > 0)
  {
    TRTHighTOutliersRatio = (double)(nTRTHigh + nTRTHighOutliers)/nTRTTotal;
  }else{
    TRTHighTOutliersRatio = 0;
  }

  eta = electron.eta();

  success = success && electron.showerShapeValue(f1, xAOD::EgammaParameters::f1); 
  // success = success && electron.showerShapeValue(rphi, xAOD::EgammaParameters::Rphi);
  success = success && electron.showerShapeValue(e237, xAOD::EgammaParameters::e237); 
  success = success && electron.showerShapeValue(e277, xAOD::EgammaParameters::e277); 

  rphi = e237/e277;

  if ( expectedBlayerHits > 0)
  {
    expectBlayer = true;
  }


  if(success){
    //call old function
    return getRecoClassification(eta, TRTHighTOutliersRatio, f1, rphi, nPix,
        nPixDeadSensors, nBlayerHits, expectBlayer, nTRT, nTRTOutliers );
  }else{
    Error("getRecoClassification()", "Failed to retireive required summary value");
    return ElectronRecoClassification::Failed;
  }
}

ElectronRecoClassification::RecoType ElectronRecoClassification::getRecoClassification(double eta,
    double TRTHighTOutliersRatio, double f1, 
    double rphi, int nPix, int nPixDeadSensors,int nBlayerHits, 
    bool expectBlayer,int nTRT, int nTRTOutliers ) const{

  bool passf1=(f1>0.1);
  bool passrphi=(rphi>0.9);
  bool passConv=((expectBlayer && nBlayerHits<1) || (!expectBlayer && (nPix+nPixDeadSensors)<2));
  int nTRTTotal= nTRT+nTRTOutliers;
  //
  int ibin_eta_TRT = -1;
  static const double CutTR[6] = {0.09, 0.105, 0.11, 0.125, 0.145, 0.16};
  static const double CutBinEta_TRT[6] = {0.1, 0.625, 1.07, 1.304, 1.752, 2.0};  
  //Find eta bin
  for (unsigned int ibinEta=0;ibinEta<6;ibinEta++) {
    if ( ibinEta == 0 ){
      if ( fabs(eta) < CutBinEta_TRT[ibinEta] ) {
        ibin_eta_TRT = ibinEta;
      }
    } 
    else {
      if ( fabs(eta) >= CutBinEta_TRT[ibinEta-1] && fabs(eta) < CutBinEta_TRT[ibinEta] ) {
        ibin_eta_TRT = ibinEta;
      }
    }
  }
  //
  bool passTR=false;
  if (ibin_eta_TRT >= 0) {//apply the cut 
    passTR= (TRTHighTOutliersRatio > CutTR[ibin_eta_TRT]) ;
  }


  if(fabs(eta)<2.0 || nTRTTotal>=10 ){ //either less than 2.0 or nTRTTotal>=10 for the "edges" 
    if(passConv){
      return ElectronRecoClassification::Photon;
    }
    else if(passTR&&passf1){
      return ElectronRecoClassification::Electron;    
    }
    else{
      return ElectronRecoClassification::Jet;    
    }
  }
  else{ //No TRT hits or above eta 2.0
    if(passConv){
      return ElectronRecoClassification::Photon;
    }
    else if(passf1&&passrphi){
      return ElectronRecoClassification::Electron;    
    }
    else{
      return ElectronRecoClassification::Jet;
    }
  }


}


