#ifndef IELECTRONRECOCLASSIFICATION_H
#define IELECTRONRECOCLASSIFICATION_H

// Framework include(s):
#include "AsgTools/IAsgTool.h"

//EDM include(s);
#include "xAODEgamma/Electron.h"

class IElectronRecoClassification : public virtual asg::IAsgTool
{

  ASG_TOOL_INTERFACE( IElectronRecoClassification )

  public:

    enum RecoType{
      Electron = 1,
      Photon   = 2,
      Jet      = 3,
      Failed   = -1
    };

    /**
     * @brief Get an aproximate clasification for a reconstructed electron
     *
     * @param electron xAOD electron to classify
     *
     * @return clasification
     */
    virtual RecoType getRecoClassification(const xAOD::Electron& electron) const = 0;
};


#endif//IELECTRONRECOCLASSIFICATION_H

