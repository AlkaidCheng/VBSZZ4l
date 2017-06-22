#ifndef CUTPARTICLEBASE_H
#define CUTPARTICLEBASE_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <iomanip>

// Root includes
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/EnumDefCommon.h"
#include "HZZCutCommon/ParticleVar.h"

// xAOD EDM include
#include "xAODBase/IParticle.h"

// Root includes
#include "TH1F.h"

class CutParticleBase
{
    public:
        CutParticleBase(EventContainer* eventcont);
        virtual ~CutParticleBase();
    
        /// To setup anything depedant on systematics
        virtual void initialize();

        /// Loop that process all the particles in the given vector
        virtual void process();
    
        /// Process for each individual particles
        virtual Bool_t processParticle(const ParticleVar* currPart) = 0;
    
        /// Clears event specific vars
        virtual void clearVars();
    
        /// to initialize the cutflow, every class inheriting should implement with it own version
        virtual void initCutFlow() = 0;

        // print the cutflow for this class
        virtual void printCutFlow();

        void updateCutFlow(Int_t valToAdd, Int_t cutLevel);

        std::vector<Int_t> getRawCutFlow();
    
        std::vector<ParticleVar*> getParticles() {return m_partFinalList;};
    
        void setParticles(const std::vector<ParticleVar*>& partList) {m_partInitList = partList; };

    protected:
        EventContainer* m_eventCont;
    
        std::vector<ParticleVar*> m_partInitList;
        std::vector<ParticleVar*> m_partFinalList;


        // For CutFlow
        TString m_cutFlowName;
        std::vector<TString> m_cutName;
        std::map<CP::SystematicSet, std::vector<Int_t>> m_rawCutFlow;
        std::map<CP::SystematicSet, std::vector<Float_t>> m_weightCutFlow;

        
};

#endif


