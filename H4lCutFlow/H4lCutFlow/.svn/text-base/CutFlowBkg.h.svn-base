#ifndef CUTFLOWBKG_H
#define CUTFLOWBKG_H

// Local includes
#include "H4lCutFlow/CutLepComb.h"
#include "H4lCutFlow/ApplyWeight4l.h"
#include "H4lCutFlow/CutFlow4l.h"

// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODEgamma/Electron.h"

// Enum to control the cutflow
namespace bkgCutFlow
{
    enum bkgCutFlow
    {
        d0_Iso_relax,
        sameSign,
        NA,
    };
    
}

class CutFlowBkg : public CutFlow4l
{
public:
    CutFlowBkg(EventContainer* eventcont, ApplyWeight4l* applyWeight);
    ~CutFlowBkg();
    
    /// Override the functionality from the CutFlow4l as at the moment we don't want to limit the quads based on flavour
    void setQuadAnalysisType(Int_t quadType);
    
    /// To set what type of llmumu cutflow to do
    void cutFlowType(Int_t cutflowType);
    
    // Main event selection happens here
    void process();
    
    void initCutFlow();
    
protected:
    bkgCutFlow::bkgCutFlow m_cutflowType;
    
    Bool_t cutDilepCharge(ParticleDilepton* currDilep);
    Bool_t cutDilepType(ParticleDilepton* currDilep);
    
    Bool_t cutQuadCharge(ParticleQuadlepton* currQuad);
    Bool_t cutQuadType(ParticleQuadlepton* currQuad);
    
    Bool_t cutLeadingIsoD0Helper(ParticleQuadlepton* currQuad);
    void cutLeadingIsoD0();
    void performHiggsCuts();
    
    
};

#endif


