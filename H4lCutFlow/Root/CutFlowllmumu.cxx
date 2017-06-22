#include "H4lCutFlow/CutFlowllmumu.h"
using namespace std;

CutFlowllmumu::CutFlowllmumu(EventContainer* eventcont, ApplyWeight4l* applyWeight)
: CutFlow4l(eventcont, applyWeight)
{
    m_cutflowType = llmumuCutFlow::NA;
}

CutFlowllmumu::~CutFlowllmumu()
{
    
}



// To set the cutFlow type
void CutFlowllmumu::cutFlowType(Int_t cutflowType)
{
    m_cutflowType = static_cast<llmumuCutFlow::llmumuCutFlow>(cutflowType);
    
    if(m_cutflowType == llmumuCutFlow::d0_Iso_relax)
    {
        m_cutFlowName += " relax d0/Iso";
        m_currQuadAnalType = QuadAnalType::d0IsoRelax;
    }
    else if(m_cutflowType == llmumuCutFlow::emu)
    {
        m_cutFlowName += " emu";
        m_currQuadAnalType = QuadAnalType::emu;
    }
    
    else if(m_cutflowType == llmumuCutFlow::sameSign)
    {
        m_cutFlowName += " SS";
        m_currQuadAnalType = QuadAnalType::sameSign;
    }
    
    
    
    if(m_cutflowType == llmumuCutFlow::NA)
    {
        LOG(logERROR)<<"CutFlowllmumu - cutflow type not set";
        exit(1);
    }
    
    
}


void CutFlowllmumu::setQuadAnalysisType(Int_t quadType)
{
    m_limitQuadType = static_cast<QuadleptonType::QuadleptonType>(quadType);
    
    if(m_limitQuadType == QuadleptonType::_4mu) m_cutFlowName += " 4mu";
    else if(m_limitQuadType == QuadleptonType::_2e2mu) m_cutFlowName += " 2e2mu";
    else
    {
        LOG(logERROR)<<"quadType not supported";
        LOG(logERROR)<<"quadType requested: "<<quadType;
        exit(1);
    }
    
}
////////////////////////////////////////////////
//
// Main function controlling the higgs selection
//
////////////////////////////////////////////////
void CutFlowllmumu::process()
{
    createLepList();
    
    // Lepton Cut
    if(!cutNumLep()) return;
    updateCutFlow(cutFlow::Lepton);
    m_lastCutPassed = cutFlow::Lepton;
    
    // Getting the dilep combination
    getDilepComb();
    
    // Getting the quadLepton combination
    getQuadComb();
    
    // SFOS cut
    if(m_quadList.size() == 0) return;
    updateCutFlow(cutFlow::SFOS);
    m_lastCutPassed = cutFlow::SFOS;
    
    // Kinematic cut
    cutKinematic();
    
    if(m_quadList.size() == 0) return;
    updateCutFlow(cutFlow::Kinematics);
    m_lastCutPassed = cutFlow::Kinematics;
    
    // Trigger Match cut
    cutTrigMatch();
    
    if(m_quadList.size() == 0) return;
    updateCutFlow(cutFlow::TriggerMatch);
    m_lastCutPassed = cutFlow::TriggerMatch;
    
    // Picking one quad
    pickQuadEvent();
    
    if(m_eventCont->isDebug)
    {
        for(size_t i = 0; i < m_quadList.size(); i++)
        {
            LOG(logDEBUG)<<m_cutFlowName<<" all combinations: "<<i;
            m_quadList[i]->printDebug();
        }
        cout<<endl<<endl<<endl;;
        
    }
    
    if(m_eventCont->isDebug)
    {
        LOG(logDEBUG)<<m_cutFlowName<<" chosen quad";
        for(size_t i = 0; i < m_quadList.size(); i++)
        {
            m_quadList[i]->printDebug();
        }
    }
    
    if(m_quadList.size() == 0)
    {
        LOG(logERROR)<<"Higgs not found";
        exit(1);
    }
    
    performHiggsCuts();
    
    // cutLeadingIsoD0 after DeltaR
    if(m_lastCutPassed == cutFlow::DeltaR) cutLeadingIsoD0();
    
}


// To cut on the charge of the dilep
Bool_t CutFlowllmumu::cutDilepCharge(ParticleDilepton* currDilep)
{
    
    // If emu or ss, don't cut on the charge here, but rather cut in the quad
    // Since we want the Z1 to have zero charge and Z2 to consider both
    if(m_cutflowType == llmumuCutFlow::emu || m_cutflowType == llmumuCutFlow::sameSign)
    {
        return true;
    }
    
    if(currDilep->getCharge() == 0) return true;
    else return false;
}

// To cut on the flavour of the dilep
Bool_t CutFlowllmumu::cutDilepType(ParticleDilepton* currDilep)
{
    if(currDilep->getDilepType() == DileptonType::_2mu) return true;
    else if(currDilep->getDilepType() == DileptonType::_2e)  return true;
    else if(m_cutflowType == llmumuCutFlow::emu && currDilep->getDilepType() == DileptonType::emu)  return true;
    
    return false;
}


// Helper functions
// Cut based on the charge of the quad
Bool_t CutFlowllmumu::cutQuadCharge(ParticleQuadlepton* currQuad)
{
    // 26 AUG: modified to separate different types of cutflow,
    // and remove bug where all sameSign quads are cut away at last if statement
    if(m_cutflowType == llmumuCutFlow::emu)
    {
        if(currQuad->getZ1()->getCharge() != 0) return false;
    }
    else if(m_cutflowType == llmumuCutFlow::sameSign)
    {
        if(currQuad->getZ1()->getCharge() != 0 || currQuad->getZ2()->getCharge() == 0) return false;
    }
    else if(currQuad->getCharge() != 0) return false;
    
    return true;
    
}
// Cut based on the favour of the quad
Bool_t CutFlowllmumu::cutQuadType(ParticleQuadlepton* currQuad)
{
    
    if(currQuad->getZ2()->getDilepType() != DileptonType::_2mu) return false;
    
    // If emu cutflow, limit the Z1 to emu type
    if(m_cutflowType == llmumuCutFlow::emu)
    {
        if(currQuad->getZ1()->getDilepType() != DileptonType::emu) return false;
    }
    else if(m_cutflowType == llmumuCutFlow::sameSign || m_cutflowType == llmumuCutFlow::d0_Iso_relax)
    {
        if(m_limitQuadType == QuadleptonType::_4mu && currQuad->getQuadType() != QuadleptonType::_4mu) return false;
        else if(m_limitQuadType == QuadleptonType::_2e2mu && currQuad->getQuadType() != QuadleptonType::_2e2mu) return false;
        else if(m_limitQuadType != QuadleptonType::_4mu && m_limitQuadType != QuadleptonType::_2e2mu)
        {
            LOG(logERROR)<<"cutflowllmumu::cutQuadType - limitQuadType not properly set for ss CR";
            LOG(logERROR)<<"limitQuadType is " << m_limitQuadType;
            exit(1);
        }
    }
    return true;
}

// Cut on the leading Z Isolation and d0
Bool_t CutFlowllmumu::cutLeadingIsoD0Helper(ParticleQuadlepton* currQuad)
{
    // Iso
    m_cutQuad->cutIsolation(currQuad);
    // D0 cut
    m_cutQuad->cutD0Sig(currQuad);
    
    if(m_setLastCut >= cutFlow::Iso)
    {
        if(!currQuad->getZ1()->getLepOne()->getParticle()->auxdecor<int>("isoCut")
           || !currQuad->getZ1()->getLepTwo()->getParticle()->auxdecor<int>("isoCut")) return false;
        updateCutFlow(cutFlow::Iso);
        m_lastCutPassed = cutFlow::Iso;
    }
    if(m_setLastCut >= cutFlow::D0Sig)
    {
        if(!currQuad->getZ1()->getLepOne()->getParticle()->auxdecor<int>("passD0Sig")
           || !currQuad->getZ1()->getLepTwo()->getParticle()->auxdecor<int>("passD0Sig")) return false;
        updateCutFlow(cutFlow::D0Sig);
        m_lastCutPassed = cutFlow::D0Sig;
    }
    return true;
}

// Cut on the leading Z Isolation and d0
void CutFlowllmumu::cutLeadingIsoD0()
{
    // Iso cut
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        m_higgs = m_quadList[i];
        keep = cutLeadingIsoD0Helper(m_higgs);
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }        
    }
}


void CutFlowllmumu::performCRSpecificIsoD0SigCuts()
{
    // for all CR, std iso and d0sig cut on Z1
    // for emu and ss, this is the end of cutflow
    if(!cutLeadingIsoD0Helper(m_higgs)) return;
    //updateCutFlow(cutFlow::Z1_Iso_D0Sig);
    
    // for relax_iso_d0, either InvD0 or InvIso
    if(m_cutflowType != llmumuCutFlow::emu && m_cutflowType != llmumuCutFlow::sameSign)
    {
        if(cutInvD0(m_higgs))
        {
            //updateCutFlow(cutFlow::InvD0);
        }
        if(cutInvIso(m_higgs))
        {
            //updateCutFlow(cutFlow::InvIso);
        }
    }
    return;
}

// iso and d0 cut on Z2 for InvD0 CR:
// d0 inverted for at least one lep, no iso cut
Bool_t CutFlowllmumu::cutInvD0(ParticleQuadlepton* currQuad)
{
    // D0 cut
    m_cutQuad->cutD0Sig(currQuad);
    
    if(currQuad->getZ2()->getLepOne()->getParticle()->auxdecor<int>("passD0Sig") && currQuad->getZ2()->getLepTwo()->getParticle()->auxdecor<int>("passD0Sig")) return false;
    
    return true;
}

// iso and d0 cut on Z2 for InvIso CR:
// Iso inverted for at least one lep, std d0sig cut
Bool_t CutFlowllmumu::cutInvIso(ParticleQuadlepton* currQuad)
{
    // Iso
    m_cutQuad->cutIsolation(currQuad);
    // D0 cut
    m_cutQuad->cutD0Sig(currQuad);
    
    if(!currQuad->getZ2()->getLepOne()->getParticle()->auxdecor<int>("passD0Sig") || !currQuad->getZ2()->getLepTwo()->getParticle()->auxdecor<int>("passD0Sig")) return false;
    
    if(currQuad->getZ2()->getLepOne()->getParticle()->auxdecor<int>("isoCut") && currQuad->getZ2()->getLepTwo()->getParticle()->auxdecor<int>("isoCut")) return false;
    
    return true;
}


// 25 AUG: override performHiggsCuts to remove std iso and d0sig cuts
// CR specific iso and d0sig cuts are done in the main function after
// performHiggsCuts()
void CutFlowllmumu::performHiggsCuts()
{
    // mZ1 cut
    cutMZ1();
    if(m_quadList.size() == 0) return;
    m_lastCutPassed = cutFlow::Z1Mass;
    
    // mZ2 cut
    cutMZ2();
    if(m_quadList.size() == 0) return;
    m_lastCutPassed = cutFlow::Z2Mass;
    
    // DeltaR and Jpsi cut
    cutDeltaRJpsi();
    if(m_quadList.size() == 0) return;
    m_lastCutPassed = cutFlow::DeltaR;
    
    // Trigger calculations
    calcIsoD0();
}


// For cutflow
void CutFlowllmumu::initCutFlow()
{
    // Call the original and overwrite some names
    CutFlow4l::initCutFlow();
  
    m_cutName[cutFlow::Iso]    = "LeadIso";
    m_cutName[cutFlow::D0Sig]  = "LeadD0Sig";
    
}

