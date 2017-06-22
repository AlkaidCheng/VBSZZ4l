#include "H4lCutFlow/CutEventPreSel.h"
using namespace std;

CutEventPreSel::CutEventPreSel(EventContainer* eventcont):
    CutEventBase(eventcont)
{

}

CutEventPreSel::~CutEventPreSel()
{

}


Bool_t CutEventPreSel::passCut() const
{
    const xAOD::VertexContainer* vertexCont = 0;
    
    RETURN_CHECK("CutEventPreSel::passCut", m_eventCont->getEvent()->retrieve( vertexCont, "PrimaryVertices" ); );
    
    return VertexCut(vertexCont);
}


Bool_t CutEventPreSel::VertexCut(const xAOD::VertexContainer* vertexCont) const
{
    for (Int_t i = 0; i < (Int_t) vertexCont->size() ;++i){
        const xAOD::Vertex* vx = vertexCont->at(i);

        //if(vx->nTrackParticles() >= 3) return true;
        if(vx->vertexType() == xAOD::VxType::PriVtx) return true;
    }

    return false;
}


