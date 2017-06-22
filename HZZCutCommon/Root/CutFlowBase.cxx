#include "HZZCutCommon/CutFlowBase.h"
using namespace std;

CutFlowBase::CutFlowBase(EventContainer* eventcont)
{
    // Copying it for local use
    m_eventCont = eventcont;

    m_cutFlowName = "Base";

    clearVars();

}

CutFlowBase::~CutFlowBase()
{
    m_cutName.clear();
    m_rawCutFlow.clear();
    m_weightCutFlow.clear();

    clearVars();
}

void CutFlowBase::initialize()
{
    initCutFlow();
}

void CutFlowBase::clearVars()
{
    m_muList.clear();
    m_elList.clear();
}

// To Print Cutflow
// If other class want to specify another way of printing or a different way of counting, 
// they should modify this function
void CutFlowBase::printCutFlow()
{
    cout<<"-----------------------------------------"<<endl;
    cout<<"CutFlow channel: "<<m_cutFlowName<<endl;
    cout<<endl;
    cout<<setw(17)<<"CutName"<<": "<<"Raw Cutflow - weighted Cutflow"<<endl;
    
    for(Int_t i = 0; i < (Int_t) m_cutName.size(); i++)
    {
        cout<<setw(17)<<m_cutName[i]<<": "
        <<m_rawCutFlow[m_eventCont->m_currVariation][i]<<" - "
        <<m_weightCutFlow[m_eventCont->m_currVariation][i]<<endl;
    }
    cout<<endl;
    cout<<"-----------------------------------------"<<endl;
    
}



