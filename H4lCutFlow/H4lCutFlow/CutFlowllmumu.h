#ifndef CUTFLOWLLMUMU_H
#define CUTFLOWLLMUMU_H

// Local includes
#include "H4lCutFlow/CutLepComb.h"
#include "H4lCutFlow/ApplyWeight4l.h"
#include "H4lCutFlow/CutFlow4l.h"

// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODEgamma/Electron.h"

// Enum to control the cutflow
namespace llmumuCutFlow
{
    enum llmumuCutFlow
    {
        d0_Iso_relax,
        emu,
        sameSign,
        NA,
    };
    
}

class CutFlowllmumu : public CutFlow4l
{
public:
    CutFlowllmumu(EventContainer* eventcont, ApplyWeight4l* applyWeight);
    ~CutFlowllmumu();
    
    /// Override the functionality from the CutFlow4l as at the moment we don't want to limit the quads based on flavour
    void setQuadAnalysisType(Int_t quadType);
    
    /// To set what type of llmumu cutflow to do
    void cutFlowType(Int_t cutflowType);
    
    // Main event selection happens here
    void process();

    void initCutFlow();
    

protected:
    llmumuCutFlow::llmumuCutFlow m_cutflowType;
    
    Bool_t cutDilepCharge(ParticleDilepton* currDilep);
    Bool_t cutDilepType(ParticleDilepton* currDilep);
    
    Bool_t cutQuadCharge(ParticleQuadlepton* currQuad);
    Bool_t cutQuadType(ParticleQuadlepton* currQuad);
    
    Bool_t cutLeadingIsoD0Helper(ParticleQuadlepton* currQuad);
    void cutLeadingIsoD0();
    
    // 25 AUG: adjust performHiggsCut and added other helpers to ease comparison with Denys
    void performHiggsCuts();
    void performCRSpecificIsoD0SigCuts();
    Bool_t cutInvD0(ParticleQuadlepton* currQuad);
    Bool_t cutInvIso(ParticleQuadlepton* currQuad);
    
    
};

#endif


