#ifndef TOOLINITBASE_H
#define TOOLINITBASE_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Local includes
#include "HZZCutCommon/log.h"
#include "HZZCutCommon/EventContainer.h"


// Generic tool includes
#include "AsgTools/IAsgTool.h"
#include "PATInterfaces/ISystematicsTool.h"

class ToolInitBase
{
    public:
        ToolInitBase(EventContainer* eventcont);
        virtual ~ToolInitBase();
    
        // Mainly to setup anything depedant on systematics
        virtual bool initialize();
    
        // Use tool handle for all ASG tools
        Bool_t hasInit;
    
        virtual void updateToolVariation();

        void setDoReducedSys(bool reducedSys = true){m_doReducedSys = reducedSys;};
        void setDoFullEgammaSys(bool fullEgamma = true){m_doFullEgammaSys = fullEgamma;};

    protected:
        EventContainer* m_eventCont;
        bool initEgammaTools();
        bool initMuonTools();
        bool initJetTools();
        bool initBtagTools();
        bool initTauTools();
        bool initMETTools();
        bool initWeightTools();
    
        bool m_doReducedSys;
        bool m_doFullEgammaSys;

        std::vector<asg::IAsgTool*> m_asgToolVec;
        std::vector<CP::ISystematicsTool*> m_sysToolVec;
    
        void addToolToVec(asg::IAsgTool* tool);

};

#endif


