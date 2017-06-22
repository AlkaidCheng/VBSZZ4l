#ifndef CUTPARTICLEELECTRON4l_H
#define CUTPARTICLEELECTRON4l_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// local includes
#include "HZZCutCommon/CutParticleBase.h"
#include "H4lCutFlow/EnumDef4l.h"

// xAOD EDM include
#include "xAODEgamma/Electron.h"
#include "xAODTracking/VertexContainer.h"

// Tool include
#include "ElectronPhotonSelectorTools/IAsgElectronLikelihoodTool.h"


class CutParticleElectron : public CutParticleBase
{
    public:
        CutParticleElectron(EventContainer* eventcont);
        virtual ~CutParticleElectron();
    
        void initCutFlow();
    
        Bool_t processParticle(const ParticleVar* currPart);
    
        void fillIDCut(const xAOD::Electron* el);
    
        // Set to do very loose ID cut
        void doVeryLooseID() {m_doVeryLooseID = true; m_cutFlowName+= " Loose ID";};
        void doBasicID() {m_doBasicID = true; m_cutFlowName+= " Basic ID";};

    protected:
        ToolHandle<IAsgElectronLikelihoodTool> m_likelihoodCut;
        ToolHandle<IAsgElectronLikelihoodTool> m_likelihoodCutVL;
        ToolHandle<IAsgElectronLikelihoodTool> m_likelihoodCutM;
        ToolHandle<IAsgElectronLikelihoodTool> m_likelihoodCutT;
    
        Bool_t m_doVeryLooseID;
        Bool_t m_doBasicID;
};

#endif


