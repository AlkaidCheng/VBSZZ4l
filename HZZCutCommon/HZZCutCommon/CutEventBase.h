#ifndef CUTEVENTBASE_H
#define CUTEVENTBASE_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Root includes
#include "HZZCutCommon/EventContainer.h"

class CutEventBase
{
    public:
        CutEventBase(EventContainer* eventcont);
        virtual ~CutEventBase();
    
        // Mainly to setup anything depedant on systematics
        virtual void initialize() {};

        virtual Bool_t passCut() const;
   
        virtual void clearVars() {};
        
        
    protected:
        EventContainer* m_eventCont;
        
        
};

#endif


