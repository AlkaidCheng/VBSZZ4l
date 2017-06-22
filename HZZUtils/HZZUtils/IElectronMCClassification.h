#ifndef IELECTRONMCCLASIFICATION_H
#define IELECTRONMCCLASIFICATION_H

// Framework include(s):
#include "AsgTools/IAsgTool.h"

//EDM include(s);

#include "xAODEgamma/Electron.h"

namespace ElectronDetailedTruth{
    enum MCDetailedType{
      Zboson =1,
      Wboson =2,
      OtherIsolated=3,
      ZbosonBrem=4,
      WbosonBrem=5,
      FSR=6,
      HeavyFlavor=7,
      HeavyFlavorBrem=8,
      LightMesonDecay=9,
      OtherBkgConversion=10,
      OtherBkgElectron=11,
      Hadron=12,
      Muon=13,
      UnKnown=14,
      Other=15,
      ElectronBrem=16
    };
}

namespace ElectronTruth{
    enum MCType{
      Isolated =1,
      Heavy =2,
      FSR=3,
      Photon=4,
      Hadron=5,
      Muon =6,
      Other=7
    };
}

class IElectronMCClassification : public virtual asg::IAsgTool {
  ASG_TOOL_INTERFACE( IElectronMCClassification )

  public:

    virtual StatusCode initialize() = 0;


    /**
     * @brief Function to get detailed truth information about the source of an
     * electron
     *
     * This function is used to get a more detailed breakdown of the truth
     * information which can then be simplified by getMCClassification.
     *
     * @param electron xAOD electron to retrieve information for
     *
     * @return Detailed MC information
     */
    virtual ElectronDetailedTruth::MCDetailedType getDetailedMCClassification(const xAOD::Electron& electron) const = 0 ;


    /**
     * @brief Function to get detailed truth information about the source of an
     * electron
     *
     * This function is used to get a more detailed breakdown of the truth
     * information which can then be simplified by getMCClassification.
     *
     * @param electron xAOD electron to retrieve information for
     * @param detailedType detailed type returned by reference
     *
     * @return StatusCode, failure is returned if the requiered truth
     * information is not available
     */
    virtual StatusCode getDetailedMCClassification(const xAOD::Electron& electron, ElectronDetailedTruth::MCDetailedType& detailedType) const = 0;


    /**
     * @brief Function to get truth information about a
     * reconstructed electron
     *
     * @param electron xAOD electron to retrieve information for
     *
     * @return MC information
     */
    virtual ElectronTruth::MCType getMCClassification(const xAOD::Electron& electron) const = 0 ;


    /**
     * @brief Function to get truth information about a
     * reconstructed electron
     *
     * @param electron xAOD electron to retrieve information for
     * @param mcType mc type returned by reference
     *
     * @return StatusCode, failure is returned if the requiered truth
     * information is not available
     */
    virtual StatusCode getMCClassification(const xAOD::Electron& electron, ElectronTruth::MCType& mcType) const = 0;
};


#endif//IELECTRONMCCLASIFICATION_H
