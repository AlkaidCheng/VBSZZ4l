#include "H4lCutFlow/CutEventDataPreSel.h"
using namespace std;

CutEventDataPreSel::CutEventDataPreSel(EventContainer* eventcont):
    CutEventBase(eventcont)
{
    m_grl = ToolHandle<IGoodRunsListSelectionTool>("GoodRunsListSelectionTool");
    if(m_grl.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutEventDataPreSel::CutEventDataPreSel() - cannot retrieve IGoodRunsListSelectionTool";
        exit(1);
    }
}

CutEventDataPreSel::~CutEventDataPreSel()
{
}


Bool_t CutEventDataPreSel::passCut()  const
{

    LOG(logDEBUG)<<"In dataPreSel pass cut function";
    // if MC, this cut doesn't apply
    if(m_eventCont->isMC) return true;

    LOG(logDEBUG)<<"Passed MC cut";

    LOG(logDEBUG)<<"LARerror: "<<larError(m_eventCont->eventInfo) ;
    LOG(logDEBUG)<<"tileError: "<<tileError(m_eventCont->eventInfo) ;
    LOG(logDEBUG)<<"coreFlag: "<<coreFlag(m_eventCont->eventInfo) ;
    LOG(logDEBUG)<<"tileTrip: "<<tileTrip(m_eventCont->eventInfo) ;
    LOG(logDEBUG)<<"grlEvent: "<<grlEvent(m_eventCont->eventInfo) ;
    

    if(!larError(m_eventCont->eventInfo))   return false;
    if(!sctError(m_eventCont->eventInfo))   return false;
    if(!tileError(m_eventCont->eventInfo))  return false;
    if(!coreFlag(m_eventCont->eventInfo))   return false;
    if(!tileTrip(m_eventCont->eventInfo))   return false;
    //if(!grlEvent(m_eventCont->eventInfo))   return false;

    return true;
}

// Individual cuts
Bool_t CutEventDataPreSel::larError(const xAOD::EventInfo* ei) const
{
    if(ei->errorState(xAOD::EventInfo::LAr) == xAOD::EventInfo::Error) return false;
    return true;
}
Bool_t CutEventDataPreSel::sctError(const xAOD::EventInfo* ei) const
{
    if(ei->errorState(xAOD::EventInfo::SCT) == xAOD::EventInfo::Error) return false;
    return true;
}

Bool_t CutEventDataPreSel::tileError(const xAOD::EventInfo* ei) const
{
    if(ei->errorState(xAOD::EventInfo::Tile) == xAOD::EventInfo::Error) return false;
    return true;
}

Bool_t CutEventDataPreSel::coreFlag(const xAOD::EventInfo* ei) const
{
    if(ei->eventFlags(xAOD::EventInfo::Core) & 0x40000) return false;
    return true;
}

Bool_t CutEventDataPreSel::tileTrip(const xAOD::EventInfo*) const
{
    return true;
}

Bool_t CutEventDataPreSel::grlEvent(const xAOD::EventInfo* ei) const
{
    return m_grl->passRunLB(*ei);
}


