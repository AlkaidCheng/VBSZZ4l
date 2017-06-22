#ifndef CUTEVENTPRESEL_H
#define CUTEVENTPRESEL_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Base class include
#include "HZZCutCommon/CutEventBase.h"

// xAOD EDM include
#include "xAODTracking/VertexContainer.h"

class CutEventPreSel : public CutEventBase 
{
    public:
        CutEventPreSel(EventContainer* eventcont);
        virtual ~CutEventPreSel();

        Bool_t passCut() const;

        Bool_t VertexCut(const xAOD::VertexContainer* vertex) const;

                
    private:
        
        
};

#endif


