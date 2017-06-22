#ifndef CUTEVENTDATAPRESEL_H
#define CUTEVENTDATAPRESEL_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Base class include
#include "HZZCutCommon/CutEventBase.h"

// xAOD EDM include
#include "xAODEventInfo/EventInfo.h"

// Tool include
#include "AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h"

class CutEventDataPreSel : public CutEventBase 
{
    public:
        CutEventDataPreSel(EventContainer* eventcont);
        virtual ~CutEventDataPreSel();

        Bool_t passCut() const;

        Bool_t larError (const xAOD::EventInfo* ei) const;
        Bool_t sctError (const xAOD::EventInfo* ei) const;
        Bool_t tileError(const xAOD::EventInfo* ei) const;
        Bool_t coreFlag (const xAOD::EventInfo* ei) const;
        Bool_t tileTrip (const xAOD::EventInfo* ei) const;
        Bool_t grlEvent (const xAOD::EventInfo* ei) const;
        
    private:

        ToolHandle<IGoodRunsListSelectionTool> m_grl;
        
        
};

#endif


