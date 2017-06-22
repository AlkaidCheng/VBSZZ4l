#ifndef NLOREWEIGHTING_H
#define NLOREWEIGHTING_H

#include "AsgTools/AsgTool.h"

#include "HZZUtils/INLOreweighting.h"

class TLorentzVector;
class TH1F;
class TGraphErrors;

/**
 *
 * contact: Jochen Meyer <Jochen.Meyer@cern.ch>
 *
 */

class NLOreweighting : public virtual INLOreweighting, public virtual CP::ISystematicsTool, public asg::AsgTool
{

  ASG_TOOL_CLASS2( NLOreweighting , INLOreweighting, CP::ISystematicsTool )

  public:
    NLOreweighting(const std::string&);
    ~NLOreweighting();

/**
 * v1 [input] Negatively charged lepton from the leading Z (Z1 l-) built from Z1_lepminus_*_truth_born mini tree variables
 * v2 [input] Positively charged lepton from the leading Z (Z1 l+) built from Z1_lepplus_*_truth_born mini tree variables
 * v3 [input] Negatively charged lepton from the trailing Z (Z2 l-) built from Z2_lepminus_*_truth_born mini tree variables
 * v4 [input] Positively charged lepton from the trailing Z (Z2 l+) built from Z2_lepplus_*_truth_born mini tree variables
 * type [input] mini tree variable truth_event_type // Enum for eventType quadType{ enum { _4mu, _4e, _2mu2e, _2e2mu }; }
 * DSID [input] dataset id to identify if weight needed
 * central_yy_weight    [output] central weight to NLO EW including yy initial state
 * weight_syst_up       [output] syst. up variation (same as central, but w/o yy initial state)
 * weight_syst_down     [output] syst. down variation (same as central, but w/o yy initial state)
 * weight_qcd_syst_up   [output] syst. up variation (for evts with high qcd activity [rho>0.3] the correction doubled for up)
 * weight_qcd_syst_down [output] syst. down variation (for evts with high qcd activity [rho>0.3] the correction halfed for down)
 * rho                  [output] rho value
 *
 * the rho parameter is defined as in http://arxiv.org/abs/1401.3964 eq. 4.4
 *
 * up to now the weights are from private communitcation with Ansgar Denner and Benedikt Biedermann
 *
 */

    virtual StatusCode GetWeightHOEW( const TLorentzVector& v1, const TLorentzVector& v2,
                                      const TLorentzVector& v3, const TLorentzVector& v4,
                                      const int& type, const int& DSID, double& central_yy_weight,
                                      double& weight_syst_up, double& weight_syst_down,
                                      double& weight_qcd_syst_up, double& weight_qcd_syst_down,
                                      double& rho );

/**
 * v1 [input] Negatively charged lepton from the leading Z (Z1 l-) built from Z1_lepminus_*_truth_born mini tree variables
 * v2 [input] Positively charged lepton from the leading Z (Z1 l+) built from Z1_lepplus_*_truth_born mini tree variables
 * v3 [input] Negatively charged lepton from the trailing Z (Z2 l-) built from Z2_lepminus_*_truth_born mini tree variables
 * v4 [input] Positively charged lepton from the trailing Z (Z2 l+) built from Z2_lepplus_*_truth_born mini tree variables
 * (CURRENTLY UNUSED) type [input] mini tree variable truth_event_type // Enum for eventType quadType{ enum { _4mu, _4e, _2mu2e, _2e2mu }; }
 * DSID [input] dataset id to identify if weight needed
 * central_weight        [output] central weight from NLO QCD to NNLO QCD (qq->ZZ only; no gg initial state considered)
 * (CURRENTLY UNUSED) weight_scale_up       [output] syst. up variation (same as central, but w/o yy initial state)
 * (CURRENTLY UNUSED) weight_scale_down     [output] syst. down variation (same as central, but w/o yy initial state)
 *
 * the weights respectively cross sections are provided by the authors of arXiv:1507.06257
 *
 */

    virtual StatusCode GetWeightHOQCD( const TLorentzVector& v1, const TLorentzVector& v2,
                                       const TLorentzVector& v3, const TLorentzVector& v4,
                                       const int& type, const int& DSID, double& central_weight,
                                       double& weight_scale_up, double& weight_scale_down );


/**
 * v1 [input] Negatively charged lepton from the leading Z (Z1) built from  mini tree variables
 * v2 [input] Positively charged lepton from the tailing Z (Z2) built from  mini tree variables
 * (CURRENTLY UNUSED) type [input] mini tree variable truth_event_type // Enum for eventType quadType{ enum { _4mu, _4e, _2mu2e, _2e2mu }; }
 * DSID [input] dataset id to identify if weight needed
 * central_weight        [output] central weight from NLO QCD to NNLO QCD (qq->ZZ only; no gg initial state considered)
 * (CURRENTLY UNUSED) weight_scale_up       [output] syst. up variation (same as central, but w/o yy initial state)
 * (CURRENTLY UNUSED) weight_scale_down     [output] syst. down variation (same as central, but w/o yy initial state)
 *
 * the weights respectively cross sections are provided by the authors of arXiv:1507.06257
 *
 */

    virtual StatusCode GetWeightHOQCD( const TLorentzVector& Z1, const TLorentzVector& Z2,
                                       const int& type, const int& DSID, double& central_weight,
                                       double& weight_scale_up, double& weight_scale_down );

    //::: Is the tool affected by a specific systematic?
    virtual bool isAffectedBySystematic( const CP::SystematicVariation& systematic ) const;
    //::: Which systematics have an effect on the tool's behaviour?
    virtual CP::SystematicSet affectingSystematics() const;
    //::: Systematics to be used for physics analysis
    virtual CP::SystematicSet recommendedSystematics() const;
    //::: Use specific systematic
    virtual CP::SystematicCode applySystematicVariation ( const CP::SystematicSet& systConfig );
    
    //::: Hijacking this for systematic implementation
    virtual StatusCode fillWeightHOEW( const TLorentzVector& v1, const TLorentzVector& v2,
                                       const TLorentzVector& v3, const TLorentzVector& v4,
                                       const int& type, const int& DSID, double& weight );

    virtual StatusCode fillWeightHOQCD( const TLorentzVector& v1, const TLorentzVector& v2,
                                        const TLorentzVector& v3, const TLorentzVector& v4,
                                        const int& type, const int& DSID, double& weight );

    virtual StatusCode fillWeightHOQCD( const TLorentzVector& Z1, const TLorentzVector& Z2,
                                        const int& type, const int& DSID, double& weight );

    virtual StatusCode initialize();

  private:

    // first 4 indices are for central weights, second 4 indices are for syst weights (w/o yy initial state)
    TH1F* m_HOEW_factors[8];
    // first index is for central weights, following 2 indices are for syst weights (scale up/down)
    TGraphErrors* m_HOQCD_factors[3];
    TGraphErrors* m_HOQCD_Sherpa_factors[4];
    
    bool m_isInitialized;
    std::string m_HOEW_inputFileName;
    std::string m_HOQCD_inputFileName;
    std::string m_HOQCD_Sherpa_inputFileName;
    TFile* m_HOEW_f;
    TFile* m_HOQCD_f;
    TFile* m_HOQCD_Sherpa_f;

    enum NLOSystematic
    {
        Nominal,
        EW_Syst_up,
        EW_Syst_down,
        EW_Syst_QCD_up,
        EW_Syst_QCD_down,
        QCD_Syst_scale_up,
        QCD_Syst_scale_down
    };

    NLOSystematic m_currSys;



    // For sherpa
    virtual StatusCode GetWeightHOQCDSherpa( const TLorentzVector& v1, const TLorentzVector& v2,
                                           const TLorentzVector& v3, const TLorentzVector& v4,
                                           const int& /*type*/, const int& DSID, double& central_weight,
                                           double& weight_scale_up, double& weight_scale_down  ) ;

};



#endif // NLOREWEIGHTING_H


