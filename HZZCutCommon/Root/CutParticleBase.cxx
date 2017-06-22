#include "HZZCutCommon/CutParticleBase.h"
using namespace std;

CutParticleBase::CutParticleBase(EventContainer* eventcont)
{
    // Copying it for local use
    m_eventCont = eventcont;
}

CutParticleBase::~CutParticleBase()
{
    m_cutName.clear();
    m_rawCutFlow.clear();
    m_weightCutFlow.clear();
}

void CutParticleBase::initialize()
{
    initCutFlow();
}

void CutParticleBase::clearVars()
{
    m_partInitList.clear();
    m_partFinalList.clear();
}

void CutParticleBase::process()
{
    LOG(logDEBUG)<<"\033[35m"<<"-------------------------";
    LOG(logDEBUG)<<"\033[35m"<<" Particle Passing Information";
    if(m_partInitList.size()> 0)
    {
        LOG(logDEBUG)<<"\033[35m"<<" Particle Type: "<< m_partInitList[0]->getName();
    }
    
    
    for(Int_t i = 0; i < (Int_t) m_partInitList.size(); i++)
    {
        Bool_t passCut = false;
        if(processParticle(m_partInitList[i]))
        {
            m_partFinalList.push_back(m_partInitList[i]);
            passCut = true;
        }
        
        LOG(logDEBUG)<<"Particle - pT: "<<m_partInitList[i]->getParticle()->pt()
        <<" eta: "<<m_partInitList[i]->getParticle()->eta()
        <<" phi: "<<m_partInitList[i]->getParticle()->phi()
        <<" charge: "<<m_partInitList[i]->getCharge()
        <<" passCut: "<<passCut;
    }
    
    LOG(logDEBUG)<<"\033[35m"<<" -------------------------";
}

// To Print Cutflow
// If other class want to specify another way of printing or a different way of counting, 
// they should modify this function
void CutParticleBase::printCutFlow()
{
    cout<<"-----------------------------------------"<<endl;
    cout<<"Cut Particle: "<<m_cutFlowName<<endl;
    cout<<endl;
    for(Int_t i = 0; i < (Int_t) m_cutName.size(); i++)
    {
        cout<<setw(13)<<m_cutName.at(i)<<": "
        <<m_rawCutFlow[m_eventCont->m_currVariation].at(i)<<endl;
    }
    cout<<endl;
    cout<<"-----------------------------------------"<<endl;
    
}


void CutParticleBase::updateCutFlow(Int_t valToAdd, Int_t cutLevel)
{
    if(m_rawCutFlow.find(m_eventCont->m_currVariation) == m_rawCutFlow.end())
    {
        LOG(logERROR)<<"CutParticleBase::updateCutFlow - requested variation is not in the map";
        exit(1);
    }
    m_rawCutFlow[m_eventCont->m_currVariation].at(cutLevel) += valToAdd;
}

std::vector<Int_t> CutParticleBase::getRawCutFlow()
{
    if(m_rawCutFlow.find(m_eventCont->m_currVariation) == m_rawCutFlow.end())
    {
        LOG(logERROR)<<"CutParticleBase::getRawCutFlow - requested variation is not in the map";
        exit(1);
    }
    
    
    return m_rawCutFlow.at(m_eventCont->m_currVariation);
}
