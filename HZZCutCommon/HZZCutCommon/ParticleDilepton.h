#ifndef PARTICLEDILEPTON_H
#define PARTICLEDILEPTON_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Root includes
#include "HZZCutCommon/ParticleBase.h"
#include "HZZCutCommon/ParticleVar.h"
#include "HZZCutCommon/LepCombBase.h"

class ParticleDilepton : public ParticleBase, public LepCombBase 
{
    public:
        ParticleDilepton(EventContainer* t_eventcont, ParticleVar* lepOne, ParticleVar* lepTwo);
        virtual ~ParticleDilepton();

        /// Get the Type of dilepton combination
        DileptonType::DileptonType getDilepType() const{return m_dilepType;};

        /// get Lep one
        ParticleVar* getLepOne() const {return m_lepOne;};
        /// get Lep two
        ParticleVar* getLepTwo() const {return m_lepTwo;};
        /// get FSR if it exits, otherwise returns 0
        ParticleVar* getFSR()    const {return m_fsr;};
    
        /// To get if there is a FSR
        Bool_t hasFSR() const {return m_hasFSR;};
        
        // For interation
        Int_t getLepSize() const {return 2;};
        ParticleVar* getLep(Int_t i) const;
        TString getName() const {return "Dilep";};
    
        // Is truth Quadlepton
        Bool_t isTruth() const {return m_isTruth;};

        // Setter for FSR
        void setFSR(ParticleVar *fsr);
        // Clear FSR variables
        void clearFSR();
    
        void setTLVType(TLVType::TLVType tlvType);
        void setAnalysisType(AnalysisType::AnalysisType analType);

        // To print debug information
        void printDebug() const;

        // To check overlap with another dilep
        Bool_t isOverlap(const ParticleDilepton* temp) const;
        // With another particleVar
        Bool_t isOverlap(const ParticleVar* temp) const;


    private:
        // Implict assumption that lepOne is positive
        // and lepTwo is negative for zero sign lepton
        ParticleVar* m_lepOne;
        ParticleVar* m_lepTwo;

        ParticleVar* m_fsr;
        Bool_t m_hasFSR;

        DileptonType::DileptonType m_dilepType;
    
        Bool_t m_isTruth;

        // to initialize the maps
        void initMap();
        
};

#endif


