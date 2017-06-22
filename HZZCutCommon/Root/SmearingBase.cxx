#include "HZZCutCommon/SmearingBase.h"
using namespace std;

SmearingBase::SmearingBase(EventContainer* eventcont)
{
    // Copying it for local use
    m_eventCont = eventcont;

}

SmearingBase::~SmearingBase()
{

}

void SmearingBase::clearVars()
{
    m_partList.clear();
}

