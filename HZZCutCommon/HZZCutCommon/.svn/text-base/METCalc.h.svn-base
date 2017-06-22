#ifndef METCALC_H
#define METCALC_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Root includes
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/ParticleVar.h"

// xAOD EDM include
#include "xAODMissingET/MissingETContainer.h"
#include "xAODMissingET/MissingETAuxContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODBase/IParticleHelpers.h"

// Tool includes
#include "METInterface/IMETMaker.h"
#include "METInterface/IMETSystematicsTool.h"
#include "METUtilities/CutsMETMaker.h"
#include "METUtilities/METSystematicsTool.h"

class METCalc
{
    public:
        METCalc(EventContainer* eventcont);
        virtual ~METCalc();
    
        // Mainly to setup anything depedant on systematics
        virtual void initialize(){};
        virtual void process() ;
    
        virtual void clearVars();
    
    
        // Setting for METCalc
        void doElCut() {m_doMETElCut = true;}
        void doMuCut() {m_doMETMuCut = true;}
        void doPhCut() {m_doMETPhCut = true;}
    
        bool isElFilled() {return m_filledEl;};
        bool isMuFilled() {return m_filledMu;};
        bool isPhFilled() {return m_filledPh;};
        bool isJetFilled() {return m_filledJet;};
    
    
        void setElParticles(const std::vector<ParticleVar*> partList) {m_elVecList = partList; m_filledEl = true;};
        void setPhParticles(const std::vector<ParticleVar*> partList) {m_phVecList = partList; m_filledPh = true;};
        void setMuParticles(const std::vector<ParticleVar*> partList) {m_muVecList = partList;  m_filledMu = true;};
        void setJetParticles(const std::vector<ParticleVar*> partList){m_jetVecList = partList; m_filledJet = true;};
        void setFSRParticles(const std::vector<ParticleVar*> partList);

        xAOD::MissingET* getTrackMET() {return (*m_newMetContainer)["FinalTrk"];};

    protected:
        std::vector<ParticleVar*> m_elVecList;
        std::vector<ParticleVar*> m_muVecList;
        std::vector<ParticleVar*> m_jetVecList;
        std::vector<ParticleVar*> m_phVecList;
    
        Bool_t m_doMETElCut;
        Bool_t m_doMETMuCut;
        Bool_t m_doMETPhCut;
    
        Bool_t m_filledEl;
        Bool_t m_filledMu;
        Bool_t m_filledJet;
        Bool_t m_filledPh;
    
    
        EventContainer* m_eventCont;
    
        ToolHandle<IMETMaker>   m_metMaker;
        ToolHandle<IMETSystematicsTool>   m_metSysTool;
        met::METSystematicsTool*    m_metSysToolR;

        // Helper vars
        const xAOD::MissingETContainer* m_coreMet;
        const xAOD::MissingETAssociationMap* m_metMap;

        xAOD::MissingETContainer*    m_newMetContainer;
        xAOD::MissingETAuxContainer* m_newMetAuxContainer ;
        xAOD::MuonContainer* m_muList;
        xAOD::ElectronContainer* m_elList;
        xAOD::PhotonContainer* m_phList;
        xAOD::JetContainer* m_jetList;
    
        bool fillEl();
        bool fillPh();
        bool fillMu();
        bool fillJet();
    
        bool isOvlEl(ParticleVar* part);
    
        int n_nameItr;

};

#endif


