#ifndef ELECTRONMCCLASSIFICATION_H
#define ELECTRONMCCLASSIFICATION_H

// Framework include(s):
#include "AsgTools/AsgTool.h"
#include "xAODTruth/TruthParticle.h"

//local includes
#include "HZZUtils/IElectronMCClassification.h"

#include "MCTruthClassifier/MCTruthClassifier.h"

#include "AsgTools/ToolHandle.h"
#include "MCTruthClassifier/IMCTruthClassifier.h" 

class ElectronMCClassification : public virtual IElectronMCClassification,
                                 public asg::AsgTool
{
  ASG_TOOL_CLASS( ElectronMCClassification, IElectronMCClassification)

  public:

    ElectronMCClassification(const std::string&);
    ~ElectronMCClassification();
    virtual StatusCode initialize();

    virtual ElectronDetailedTruth::MCDetailedType getDetailedMCClassification(const xAOD::Electron& electron) const;

    virtual StatusCode getDetailedMCClassification(const xAOD::Electron& electron, ElectronDetailedTruth::MCDetailedType& detailedType) const;

    virtual ElectronTruth::MCType getMCClassification(const xAOD::Electron& electron) const;

    virtual StatusCode getMCClassification(const xAOD::Electron& electron, ElectronTruth::MCType& mcType) const;

    // ElectronDetailedTruth::MCDetailedType getDetailedMCClassification(int type,
    //     int origin,
    //     int typebkg,
    //     int originbkg ) const;
    //
    // ElectronTruth::MCType getMCClassification(int type,
    //     int origin,
    //     int typebkg,
    //     int originbkg ) const;

    ElectronTruth::MCType getMCClassification(ElectronDetailedTruth::MCDetailedType detailedtype) const;

  private:


    StatusCode getMotherPhoton(const xAOD::TruthParticle* truthel, ElectronDetailedTruth::MCDetailedType& detailedType) const;

    int getAbsPdgId(const xAOD::TruthParticle* truthel) const;

    bool m_useMcClassifier;

    //ToolHandle<MCTruthClassifier>  m_mcClassifierTool;
    mutable ToolHandle<IMCTruthClassifier>  m_mcClassifierTool; 
   
};

#endif//ELECTRONMCCLASSIFICATION_H
