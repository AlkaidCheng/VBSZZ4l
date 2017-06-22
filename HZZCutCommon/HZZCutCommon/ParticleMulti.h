#ifndef PARTICLEMULTI_H
#define PARTICLEMULTI_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <unordered_map>

// Local includes
#include "HZZCutCommon/ParticleBase.h"
#include "HZZCutCommon/ParticleVar.h"
#include "HZZCutCommon/LepCombBase.h"


class ParticleMulti : public ParticleBase, public LepCombBase
{
    public:
        ParticleMulti(EventContainer* t_eventcont);
        virtual ~ParticleMulti();

        // Gives the number of particles in this container
        Int_t getSize() const {return m_particleList.size();};
    
        /// Adds a particle to the map
        void addParticle(std::string name, ParticleBase* particle, Bool_t overWrite = false);
    
        // Get the particle with the name
        ParticleBase* getParticle(std::string name) const;
    
        /// Adds a particleVar to the map
        /// To allow resuing of some code
        void addParticleVar(ParticleVar* particle, Bool_t overWrite = false);
    
        /// Return number of leptons stored internally
        Int_t getLepSize() const {return m_particleVarList.size();};
    
        /// Return specific lepton denote by i
        ParticleVar* getLep(Int_t i) const {return m_particleVarList[i];};
    
        std::vector<ParticleVar*> getLepList() const {return m_particleVarList;};
    
        // String Identifier
        TString getName() const {return "Multi";};
        
        // Does particle overlap with any particle in this container
        Bool_t isOverlap(const ParticleBase* part) const;
    
        void setTLVType(TLVType::TLVType tlvType);
        void setAnalysisType(AnalysisType::AnalysisType analType);

        // To print debug information
        void printDebug() const;

    private:
        std::vector<ParticleBase*> m_particleList;
        std::vector<ParticleVar*> m_particleVarList;
        std::unordered_map<std::string,ParticleBase*> m_particleMap;
    
        // to initialize the maps
        void initMap();
        
};

#endif


