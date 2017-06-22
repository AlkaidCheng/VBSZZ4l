#ifndef ICATEGORIESMVA_H
#define ICATEGORIESMVA_H

// Framework includes
#include "AsgTools/IAsgTool.h"
#include <vector>

// Forward declarations
namespace xAOD 
{
    class IParticle;
}


class ICategoriesMVA : public virtual asg::IAsgTool 
{
    ASG_TOOL_INTERFACE( ICategoriesMVA )
    public: 
    enum MVA_Type {
        VBF_final2011,
        VH_final2011,
        VBF_final2012,
        VH_final2012,
        VBF_ICHEP2016_30GeV_BinptHjj50,
        VBF_ICHEP2016_30GeV_noptHjj,
        VH_ICHEP2016_30GeV_BinptHjj50,
        VH_ICHEP2016_30GeV_noptHjj,
        VBF_1j_ICHEP2016,
        VBF_1j_ICHEP2016_jptetadR,

        // Moriond
        VBF_TOPO_Moriond2017,
        VBF_Rest_Moriond2017,
        VBF_Moriond2017,
        VH_Moriond2017,

        VBF_1j_pT4l_0_60_Moriond2017,
        VBF_1j_pT4l_0_120_Moriond2017,
        VBF_1j_pT4l_60_120_Moriond2017,

        nMVA_Types
    };

    virtual StatusCode applyMVA(const std::vector<const xAOD::IParticle*>& leptons,
                                const std::vector<const xAOD::IParticle*>& jets,
                                float& resultBDT,
                                float& resultME,
                                bool&  passesCut) const = 0 ;


    virtual StatusCode getVBF_ME(const std::vector<const xAOD::IParticle*>& leptons,
                                 const std::vector<const xAOD::IParticle*>& jets,
                                 float& resultME) const = 0 ;

    virtual std::string typeName() const = 0;
};

#endif // ICATEGORIESMVA_H



