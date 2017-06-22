#ifndef SMEARINGMUON_H
#define SMEARINGMUON_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// local includes
#include "HZZCutCommon/SmearingBase.h"

// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODBase/IParticleHelpers.h"

// CP Tools
#include "MuonMomentumCorrections/IMuonCalibrationAndSmearingTool.h"
#include "MuonMomentumCorrections/MuonCalibrationAndSmearingTool.h"

class SmearingMuon : public SmearingBase 
{
    public:
        SmearingMuon(EventContainer* eventcont);
        virtual ~SmearingMuon();

        void process();
    
        void setMuonCont(const xAOD::MuonContainer* muonCont)
        {m_muonCont = muonCont;};
    
        const xAOD::MuonContainer* getCalMuonCont() const
        {return m_shallowCopy.first;};
    
        void clearVars();
    
        void processVar(xAOD::IParticle* currPart);

    protected:
        const xAOD::MuonContainer* m_muonCont;

        std::pair< xAOD::MuonContainer*, xAOD::ShallowAuxContainer* >        m_shallowCopy;

        ToolHandle<CP::IMuonCalibrationAndSmearingTool> m_muonCalSmearTool;

        // for resolution
        CP::MuonCalibrationAndSmearingTool* m_muonTool;
};

#endif


