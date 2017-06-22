#ifndef CUTPARTICLEJET_H
#define CUTPARTICLEJET_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <typeinfo>

// local includes
#include "HZZCutCommon/CutParticleBase.h"
#include "H4lCutFlow/EnumDef4l.h"

// xAOD EDM include
#include "xAODJet/Jet.h"
#include "xAODJet/JetContainer.h"

// Tool include
#include "JetSelectorTools/JetCleaningTool.h"
#include "JetJvtEfficiency/IJetJvtEfficiency.h"

class CutParticleJet : public CutParticleBase
{
    public:
        CutParticleJet(EventContainer* eventcont);
        virtual ~CutParticleJet();
    
        enum JetSelType
        {
            NominalReco,
            FiducialReco,
            NominalTruth,
            FiducialTruth,
            NA
        };
    
        void initialize();

        Bool_t processParticle(const ParticleVar* currPart);

        void initCutFlow();
    
        void setJetSelType(JetSelType jetSelection) {m_jetSelection = jetSelection;};

        std::vector<const ParticleVar*> getFailJVTJets() {return m_jetFailJvt;};


        void clearVars();
    
    protected:
        ToolHandle<IJetSelector> m_jetcleaningTool;
	    ToolHandle<CP::IJetJvtEfficiency> m_jetJVTEffTool;
        JetSelType m_jetSelection;
    
        Bool_t nominalRecoSel(const ParticleVar* currPart);
        Bool_t fidRecoSel(const ParticleVar* currPart);
        Bool_t truthNomRecoSel(const ParticleVar* currPart);
        Bool_t truthFidRecoSel(const ParticleVar* currPart);
    
    
        // Helper functions
        // Nominal pT cut
        Bool_t nomPtCut(double pT);
    
        // Nominal Eta Cut
        Bool_t nomEtaCut(double eta, double pt);
    
        // JVT cut
        Bool_t pileupCut(const xAOD::Jet* jet_i);
    
        // Clean cut
        Bool_t cleanCut(const xAOD::Jet* jet_i);
    
        // Fiducial pT cut
        Bool_t fidPtCut(double pT);
    
        // Fiducial Eta Cut
        Bool_t fidEtaCut(double rapidity);


        // Jet list before JVT cut
        std::vector<const ParticleVar*> m_jetFailJvt;

};

#endif


