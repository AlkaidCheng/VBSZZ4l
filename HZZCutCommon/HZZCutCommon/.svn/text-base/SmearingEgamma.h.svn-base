#ifndef SMEARINGEGAMMA_H
#define SMEARINGEGAMMA_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Root includes
#include "HZZCutCommon/SmearingBase.h"
#include "HZZCutCommon/ParticleVar.h"

// xAOD EDM include
#include "xAODEgamma/Electron.h"
#include "xAODEgamma/Photon.h"
#include "xAODEgamma/EgammaContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODBase/IParticleHelpers.h"

// Tool include
#include "ElectronPhotonFourMomentumCorrection/IEgammaCalibrationAndSmearingTool.h"
#include "xAODEgamma/PhotonxAODHelpers.h"

class SmearingEgamma : public SmearingBase 
{
    public:
        SmearingEgamma(EventContainer* eventcont);
        virtual ~SmearingEgamma();

        void process();

        void clearVars();
    
        void setElectronCont(const xAOD::ElectronContainer* elCont)
        {m_elCont = elCont;};
        void setPhotonCont(const xAOD::PhotonContainer* phCont)
        {m_phCont = phCont;};
    
        const xAOD::ElectronContainer* getCalElectronCont() const
        {return m_elshallowCopy.first;};
        const xAOD::PhotonContainer* getCalPhotonCont() const
        {return m_phshallowCopy.first;};
    
        void processVar(xAOD::IParticle* currPart);

        void setElParticles(const std::vector<ParticleVar*>& elList)   {m_elList = elList; };
        void setPhParticles(const std::vector<ParticleVar*>& phList)   {m_phList = phList; };

    protected:
        std::vector<ParticleVar*> m_elList;
        std::vector<ParticleVar*> m_phList;

        ToolHandle<CP::IEgammaCalibrationAndSmearingTool> m_elRescale;
    
        const xAOD::ElectronContainer* m_elCont;
        const xAOD::PhotonContainer* m_phCont;
    
        std::pair< xAOD::ElectronContainer*, xAOD::ShallowAuxContainer* > m_elshallowCopy;
        std::pair< xAOD::PhotonContainer*, xAOD::ShallowAuxContainer* > m_phshallowCopy;
    
        void processEvent(xAOD::Electron* currElectron);
        void processEvent(xAOD::Photon* currPhoton);
    
};

#endif


