#include "HZZCutCommon/CutEventBase.h"
using namespace std;

CutEventBase::CutEventBase(EventContainer* eventcont)
{
    // Copying it for local use
    m_eventCont = eventcont;

}

CutEventBase::~CutEventBase()
{

}


Bool_t CutEventBase::passCut() const
{
    return true;
}

