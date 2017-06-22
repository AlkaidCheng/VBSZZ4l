#ifndef INLOREWEIGHTING_H
#define INLOREWEIGHTING_H

#include "AsgTools/IAsgTool.h"


// Local include(s):
#include "PATInterfaces/CorrectionCode.h"
#include "PATInterfaces/ISystematicsTool.h"
#include "PATInterfaces/SystematicCode.h"
#include "PATInterfaces/SystematicRegistry.h"
#include "PATInterfaces/SystematicSet.h"
#include "PATInterfaces/SystematicVariation.h"

class INLOreweighting : public virtual asg::IAsgTool, virtual public CP::ISystematicsTool
{

  ASG_TOOL_INTERFACE( INLOreweighting )

  public:

    virtual StatusCode initialize() = 0;

    //::: method for next-to-leading order EW weights on qq->ZZ (lepton input)
    virtual StatusCode GetWeightHOEW( const TLorentzVector& v1, const TLorentzVector& v2,
                                      const TLorentzVector& v3, const TLorentzVector& v4,
                                      const int& type, const int& DSID, double& central_yy_weight,
                                      double& weight_syst_up, double& weight_syst_down,
                                      double& weight_qcd_syst_up, double& weight_qcd_syst_down,
                                      double& rho ) = 0;

    //::: method for next-next-to-leading order QCD weights on qq->ZZ (lepton input)
    virtual StatusCode GetWeightHOQCD( const TLorentzVector& v1, const TLorentzVector& v2,
                                       const TLorentzVector& v3, const TLorentzVector& v4,
                                       const int& type, const int& DSID, double& central_weight,
                                       double& weight_scale_up, double& weight_scale_down ) = 0;

    //::: method for next-next-to-leading order QCD weights on qq->ZZ (Z input)
    virtual StatusCode GetWeightHOQCD( const TLorentzVector& Z1, const TLorentzVector& Z2,
                                       const int& type, const int& DSID, double& central_weight,
                                       double& weight_scale_up, double& weight_scale_down ) = 0;
    
    
    //::: Is the tool affected by a specific systematic?
    virtual bool isAffectedBySystematic( const CP::SystematicVariation& systematic ) const = 0;
    //::: Which systematics have an effect on the tool's behaviour?
    virtual CP::SystematicSet affectingSystematics() const = 0;
    //::: Systematics to be used for physics analysis
    virtual CP::SystematicSet recommendedSystematics() const = 0;
    //::: Use specific systematic
    virtual CP::SystematicCode applySystematicVariation ( const CP::SystematicSet& systConfig ) = 0;

    //::: Hijacking this for systematic implementation
    virtual StatusCode fillWeightHOEW( const TLorentzVector& v1, const TLorentzVector& v2,
                                       const TLorentzVector& v3, const TLorentzVector& v4,
                                       const int& type, const int& DSID, double& weight ) = 0;

    virtual StatusCode fillWeightHOQCD( const TLorentzVector& v1, const TLorentzVector& v2,
                                        const TLorentzVector& v3, const TLorentzVector& v4,
                                        const int& type, const int& DSID, double& weight ) = 0;

    virtual StatusCode fillWeightHOQCD( const TLorentzVector& Z1, const TLorentzVector& Z2,
                                        const int& type, const int& DSID, double& weight ) = 0;

};

#endif // INLOREWEIGHTING_H


