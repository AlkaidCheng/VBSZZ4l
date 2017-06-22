#ifndef CUTPARTICLEMUON_H
#define CUTPARTICLEMUON_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// local includes
#include "HZZCutCommon/CutParticleBase.h"
#include "H4lCutFlow/EnumDef4l.h"

// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODTracking/TrackingPrimitives.h"
#include "xAODTracking/VertexContainer.h"

// Tool include
#include "MuonSelectorTools/IMuonSelectionTool.h"

class CutParticleMuon : public CutParticleBase
{
    public:
        CutParticleMuon(EventContainer* eventcont);
        virtual ~CutParticleMuon();
    
        Bool_t processParticle(const ParticleVar* currPart);

        void initCutFlow();

    protected:
        Bool_t processCombinedMuon(const xAOD::Muon* currMuon);
        Bool_t processStandAloneMuon(const xAOD::Muon* currMuon);
        Bool_t processCaloMuon(const xAOD::Muon* currMuon);
    
        ToolHandle<CP::IMuonSelectionTool> m_muonSelector;
};

#endif
