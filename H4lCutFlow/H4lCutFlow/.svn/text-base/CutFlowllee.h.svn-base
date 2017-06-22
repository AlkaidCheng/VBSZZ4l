#ifndef CUTFLOWLLEE_H
#define CUTFLOWLLEE_H

// Local includes
#include "H4lCutFlow/CutLepComb.h"
#include "H4lCutFlow/ApplyWeight4l.h"
#include "H4lCutFlow/CutFlow4l.h"
#include "H4lCutFlow/RemoveOverlap4l.h"

// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODEgamma/Electron.h"

// Enum to control the cutflow
namespace lleeCutFlow
{
    enum lleeCutFlow
    {
        NA,
        relax,
        threeLplusX,
        ZplusXX,
    };
    
}

class CutFlowllee : public CutFlow4l
{
    public:
        CutFlowllee(EventContainer* eventcont, ApplyWeight4l* applyWeight);
        ~CutFlowllee();
    
        /// To limit the falvour of quads
        void setQuadAnalysisType(Int_t);
    
        /// Get to list of higgs passing the event as mulitple quads can pass the selection
        std::vector<ParticleQuadlepton*> getHiggsVec(){return m_quadList;};
    
        /// To set what type of llee cutflow to do
        void cutFlowType(Int_t cutflowType);
    
        // Main event selection happens here
        void process();
        
        void initCutFlow();

    protected:
        lleeCutFlow::lleeCutFlow m_cutflowType;
    
        Bool_t cutDilepCharge(ParticleDilepton* currDilep);
        Bool_t cutDilepType(ParticleDilepton* currDilep);
    
        Bool_t cutQuadCharge(ParticleQuadlepton* currQuad);
        Bool_t cutQuadType(ParticleQuadlepton* currQuad);
    
        Bool_t cutLeadingIsoD0(ParticleQuadlepton* currQuad);
    
        void cutMuonType();
        void cutQuadFlavour();
    
        void cutKinematic();
        void cutCharge();
    
        void cutTrigMatch();
    
        void cutZ1ID();
        void cutZ2ID();
    
        void pickQuadEvent();

        void performHiggsCuts();
        void cutLeadingZ();

        void cut3lx();

    
};

#endif


