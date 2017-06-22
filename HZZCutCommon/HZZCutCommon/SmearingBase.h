#ifndef SMEARINGBASE_H
#define SMEARINGBASE_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Root includes
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/ParticleVar.h"

// xAOD EDM include
#include "xAODBase/IParticle.h"

class SmearingBase 
{
    public:
        SmearingBase(EventContainer* eventcont);
        virtual ~SmearingBase();
    
        // Mainly to setup anything depedant on systematics
        virtual void initialize() {};

        virtual void process() = 0;
        virtual void processVar(xAOD::IParticle* currPart) = 0;

        virtual void clearVars();
        
        void setParticles(const std::vector<ParticleVar*>& partList)   {m_partList = partList; };


    protected:
        std::vector<ParticleVar*> m_partList;
        EventContainer* m_eventCont;
};

#endif


