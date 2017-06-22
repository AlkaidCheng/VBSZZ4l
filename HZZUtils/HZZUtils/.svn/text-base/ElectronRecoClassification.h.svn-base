#ifndef ELECTRONRECOCLASSIFICATION_H
#define ELECTRONRECOCLASSIFICATION_H

// Framework include(s):
#include "AsgTools/AsgTool.h"

//Local includes
#include "HZZUtils/IElectronRecoClassification.h"

class ElectronRecoClassification : public virtual IElectronRecoClassification,
  public asg::AsgTool
{
  ASG_TOOL_CLASS( ElectronRecoClassification , IElectronRecoClassification )

  public:
    ElectronRecoClassification(const std::string&);
    ~ElectronRecoClassification();

    virtual RecoType getRecoClassification(const xAOD::Electron& electron) const;

  private:

    RecoType getRecoClassification(double eta,double TRTHighTOutliersRatio, double f1, 
        double rphi, int nPix, int nPixDeadSensors,int nBlayerHits, 
        bool expectBlayer,int nTRT, int nTRTOutliers) const;

};


#endif//ELECTRONRECOCLASSIFICATION_H
