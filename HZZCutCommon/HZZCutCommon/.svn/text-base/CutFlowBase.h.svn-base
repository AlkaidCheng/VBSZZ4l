#ifndef CUTFLOWBASE_H
#define CUTFLOWBASE_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <iomanip>

// Local includes
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/EnumDefCommon.h"

#include "HZZCutCommon/ParticleBase.h"
#include "HZZCutCommon/ParticleDilepton.h"
#include "HZZCutCommon/ParticleQuadlepton.h"
#include "HZZCutCommon/ParticleVar.h"

// Root Includes
#include "TH1F.h"


class CutFlowBase
{
    public:
        CutFlowBase(EventContainer* eventcont);
        virtual ~CutFlowBase();
    
        // Mainly to setup anything depedant on systematics
        virtual void initialize();

        virtual void process() = 0;
        virtual void clearVars();

        TString getCutFlowName() {return m_cutFlowName;};

        // to initialize the cutflow, every class inheriting should implement with it own version
        virtual void initCutFlow() = 0;

        // to actually print the cutflow
        virtual void printCutFlow();

        void setMuons (const std::vector<ParticleVar*>& muList)    {m_muList = muList;};
        void setElectrons(const std::vector<ParticleVar*>& elList) {m_elList = elList;};

        virtual void updateCutFlow(Int_t cutLevel, Int_t valToAdd = 1) = 0;
    
        std::vector<Int_t> getRawCutFlow()
            {return m_rawCutFlow[m_eventCont->m_currVariation]; };

        std::vector<Float_t> getWeightedCutFlow()
            {return m_weightCutFlow[m_eventCont->m_currVariation]; };

    protected:
        EventContainer* m_eventCont;

        // For CutFlow
        TString m_cutFlowName;
        std::vector<TString> m_cutName;
        std::map<CP::SystematicSet, std::vector<Int_t>> m_rawCutFlow;
        std::map<CP::SystematicSet, std::vector<Float_t>> m_weightCutFlow;

        // lepton
        std::vector<ParticleVar*> m_muList;
        std::vector<ParticleVar*> m_elList;
               

        
};

#endif


