#ifndef PARTICLEQUADLEPTON_H
#define PARTICLEQUADLEPTON_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Local includes
#include "HZZCutCommon/ParticleBase.h"
#include "HZZCutCommon/ParticleDilepton.h"
#include "HZZCutCommon/LepCombBase.h"

// xAOD includes
#include "xAODEgamma/ElectronxAODHelpers.h"


class ParticleQuadlepton : public ParticleBase, public LepCombBase 
{
    public:
        ParticleQuadlepton(EventContainer* t_eventcont, ParticleDilepton* Z1, ParticleDilepton* Z2, bool domZ1mZ2Pair = true);
        virtual ~ParticleQuadlepton();

        // Getters
        // Flavour of the quad
        QuadleptonType::QuadleptonType getQuadType() const {return m_quadType;};

        // Quad setup (such as 3l+x and so on)
        QuadAnalType::QuadAnalType getQuadAnalType() const {return m_quadAnalType;};
        void setQuadAnalType(QuadAnalType::QuadAnalType analType) {m_quadAnalType = analType;};
        
        TString getQuadName () const;

        ParticleDilepton* getZ1() const {return m_Z1;};
        ParticleDilepton* getZ2() const {return m_Z2;};

        Int_t getLepSize() const {return 4;};
        ParticleVar* getLep(Int_t i) const ;
        TString getName() const {return "Quadlep";};
        
        // Does lep overlap with any leptons in this quad
        Bool_t isOverlap(const ParticleVar* lep) const;
    
        // Is truth Quadlepton
        Bool_t isTruth() const {return m_isTruth;};

        // Setter for FSR
        void setFSR(ParticleVar *fsr, Int_t whichZ);
        // Clear FSR variables
        void clearFSR();

        void setTLVType(TLVType::TLVType tlvType);
        void setAnalysisType(AnalysisType::AnalysisType analType);
        

        // To print debug information
        void printDebug() const;

    private:
        ParticleDilepton* m_Z1;
        ParticleDilepton* m_Z2;

        Bool_t m_hasFSR;

        QuadleptonType::QuadleptonType m_quadType;
        QuadAnalType::QuadAnalType m_quadAnalType;

        Bool_t m_isTruth;

        // to initialize the maps
        void initMap();
        
};

#endif


