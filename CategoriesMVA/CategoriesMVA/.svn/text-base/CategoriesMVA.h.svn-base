// ::: \\ ::: // ::: \\ ::: // ::: \\ ::: // ::: \\ ::: // ::: \\ ::: // ::: \\ ::: // ::: \\ ::: //
// :::                                                                                        ::: // 
// :::      Categories MVA                                                                    ::: //
// :::                                                                                        ::: //
// :::      Tool for evaluating discriminants for the                                         ::: //
// :::      different categories of the H -> ZZ -> 4l                                         ::: //
// :::                                                                                        ::: //
// :::      Authors:  RD Schaffer     <R.D.Schaffer@cern.ch>                                  ::: //
// :::                Giacomo Artoni  <giacomo.artoni@cern.ch>                                ::: //
// :::                Stefano Zambito <stefano.zambito@cern.ch>                               ::: //
// :::                                                                                        ::: //
// :::                                                                                        ::: //
// ::: \\ ::: // ::: \\ ::: // ::: \\ ::: // ::: \\ ::: // ::: \\ ::: // ::: \\ ::: // ::: \\ ::: //

#ifndef __CATEGORIESMVA_H__
#define __CATEGORIESMVA_H__

#include "CategoriesMVA/ICategoriesMVA.h"
#include "AsgTools/AsgTool.h"


// Forward declarations

class TLorentzVector;
class CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_uux_epemepemuux;
namespace TMVA { class Reader; }
namespace LHAPDF { class PDF; }

class CategoriesMVA : public ICategoriesMVA,
                      public asg::AsgTool        
{

public:
    
    CategoriesMVA(const std::string& name);

    ~CategoriesMVA(); 

    virtual StatusCode applyMVA(const std::vector<const xAOD::IParticle*>& leptons,
                                const std::vector<const xAOD::IParticle*>& jets,
                                float& resultBDT,
                                float& resultME,
                                bool&  passesCut) const override;

    virtual StatusCode getVBF_ME(const std::vector<const xAOD::IParticle*>& leptons,
                                 const std::vector<const xAOD::IParticle*>& jets,
                                 float& resultME) const override;


    virtual std::string typeName() const override;

    /// Initialize the tool
    virtual StatusCode initialize() override;

private:

    float                 computeMinDeltaR(const std::vector<const xAOD::IParticle*>& leptons,
                                           const std::vector<const xAOD::IParticle*>& jets) const;
    float                 getMEFromVec(const std::vector<float>& ME) const;
    const TLorentzVector& toGeV(const TLorentzVector& tlv) const;

    MVA_Type                 m_mvaType;
    std::vector<std::string> m_mvaTypeNames;
    bool                     m_isInitialized;
    TMVA::Reader*            m_MVAreader;
    std::string              m_weightsFileName;
    std::string              m_madgraphVBFCardFileName;
    float                    m_cutValue;
    mutable LHAPDF::PDF*     m_ct10PDF;
    mutable CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_uux_epemepemuux* m_sm_hVBF_ZZ_4l_sm_uux_epemepemuux;

    /// variables for BDT evaluation 
    mutable float            m_dijet_invmass;
    mutable float            m_dijet_deltaeta;
    mutable float            m_leading_jet_pt;
    mutable float            m_leading_jet_eta;
    mutable float            m_subleading_jet_pt;
    mutable float            m_pt4ljj_unconstrained;
    mutable float            m_min_dR_jZ;
    mutable float            m_eta_zepp_ZZ;
    mutable float            m_dphi_4ljj;
    mutable float            m_VBF_uux_ME;
    mutable float            m_dRHj;
};

#endif
