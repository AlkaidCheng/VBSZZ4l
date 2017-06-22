#include "HZZCutCommon/SmearingTau.h"
using namespace std;

SmearingTau::SmearingTau(EventContainer* eventcont) :
    SmearingBase(eventcont)
{
    //m_tauCalibTool = ToolHandle<TauAnalysisTools::ITauSmearingTool>("TauSmearingTool");
    //if(m_tauCalibTool.retrieve().isFailure())
    //{
    //    LOG(logERROR) <<"SmearingTau::SmearingTau() - cannot retrieve ITauSmearingTool";
    //    exit(1);
    //}
    
    //m_tauTruthMatchTool = ToolHandle<TauAnalysisTools::ITauTruthMatchingTool>("TauTruthMatchingTool");
    //if(m_tauTruthMatchTool.retrieve().isFailure())
    //{
    //    LOG(logERROR) <<"SmearingTau::SmearingTau() - cannot retrieve ITauTruthMatchingTool";
    //    exit(1);
    //}
}

SmearingTau::~SmearingTau()
{
    clearVars();
}

// To reset for each new event
void SmearingTau::clearVars()
{
    m_tauCont = 0;    
    SmearingBase::clearVars();
}


// Function that loops over the vector and smears it
void SmearingTau::process()
{
    if(m_tauCont == 0)
    {
        LOG(logERROR)<<"Tau Smear: Tau container not specified";
        exit(1);
    }
    
    //if(!m_tauTruthMatchTool->initializeEvent())
    //{
    //    LOG(logERROR)<<"Cannot intialize truth tau tool";
    //    exit(1);
    //}
    
    
    m_shallowCopy = xAOD::shallowCopyContainer( *m_tauCont );
    m_eventCont->store->record( m_shallowCopy.first, "tauCorr" ).ignore();
    m_eventCont->store->record( m_shallowCopy.second, "tauCorrAux" ).ignore();
    Int_t i = 0;
    for( auto tau : *( m_shallowCopy.first ) ) {
        processVar(tau);
        m_partList[i]->addAnalParticle(m_eventCont->m_analType, tau);
        m_partList[i]->addAnalTLV(TLVType::Unconstrained, tau->p4());
        i++;
    }
}

// Function to smear each individual event
void SmearingTau::processVar(xAOD::IParticle* currPart)
{
    
    if(currPart->type() != xAOD::Type::Tau)
    {
        LOG(logERROR)<<"SmearingTau::processVar particle type not supported";
        LOG(logERROR)<<"Incoming part type: "<<currPart->type();
        exit(1);
    }
    
    xAOD::TauJet* currTau = dynamic_cast<xAOD::TauJet*>(currPart);
   
    //m_tauTruthMatchTool->getTruth(*currTau);
    
    if(m_eventCont->doSmear)
    {
        //if(!m_tauCalibTool->applyCorrection(*currTau))
        //{
        //    LOG(logERROR)<<"Cannot apply Tau Calibration";
        //    exit(1);
        //}
    }
}




