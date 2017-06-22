#ifndef TOOLINIT4L_H
#define TOOLINIT4L_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Base class include
#include "HZZCutCommon/ToolInitBase.h"

#include "AssociationUtils/OverlapRemovalTool.h"
#include "AssociationUtils/IOverlapRemovalTool.h"
#include "AssociationUtils/OverlapRemovalInit.h"


class ToolInit4l : public ToolInitBase
{
    public:
        ToolInit4l(EventContainer* eventcont);
        virtual ~ToolInit4l();

        bool initialize();
    
    private:
        ORUtils::ToolBox toolBox;

        bool initCalcTools();
        bool initPreSelTools();
    
        bool initTriggerTools();
    
        bool initEgTools();
        bool initMuTools();
        bool initJetTools();
        bool initEffTools();

        bool initIsoTools();
        bool initOlvTools();
        bool initLepTools();


    
};

#endif


