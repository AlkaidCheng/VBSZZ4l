#ifndef PARTICLEVAR_H
#define PARTICLEVAR_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Root includes
#include "HZZCutCommon/ParticleBase.h"

// xAOD EDM include
#include "xAODBase/IParticle.h"
#include "xAODTruth/TruthParticle.h"

// To remove
#include "xAODMuon/Muon.h"

class ParticleVar : public ParticleBase 
{
    public:
        ParticleVar(EventContainer* t_eventcont, const xAOD::IParticle* t_particle, Int_t t_index);
        virtual ~ParticleVar();

        TString getName() const {return m_partName;};
    
        /// Adds the xAODobject to local map
        void addAnalParticle(AnalysisType::AnalysisType tlvType, const xAOD::IParticle* t_particle, Bool_t overWrite = false);
       
        /// Get the current xAODObject
        const xAOD::IParticle* getParticle() const;
        /// Get a specific xAODObject from the map
        const xAOD::IParticle* getAnalParticle(AnalysisType::AnalysisType analType) const;

        /// Sets the current Analysis type of this particle and makes any associated change
        void setAnalysisType(AnalysisType::AnalysisType analType);
    
        /// Return the truth PDG
        Int_t getTruthPID() const {return m_truthPDG;};
    
        // To print debug information
        void printDebug() const;

    private:
        const xAOD::IParticle* m_currParticle;

        // maps that contain xAOD particle
        std::map<AnalysisType::AnalysisType, const xAOD::IParticle*> m_particleCont;
    
        TString m_partName;
    
        Int_t m_truthPDG;
    
        
};

#endif


