#include "H4lCutFlow/CutFlow4l.h"
#include <limits>
#include <algorithm>

using namespace std;

CutFlow4l::CutFlow4l(EventContainer* eventcont, ApplyWeight4l* applyWeight)
: CutFlowBase(eventcont)
{
    m_applyWeight = applyWeight;
    
    m_limitQuadType = QuadleptonType::NA;
    m_currQuadAnalType = QuadAnalType::Nominal;
    
    m_cutQuad = new CutLepComb(m_eventCont);
    
    m_higgs = 0;
    
    m_cutFlowName = "Nominal";
    
    m_setLastCut = cutFlow::D0Sig;
    
    clearVars();
}

CutFlow4l::~CutFlow4l()
{
    m_catergoryName.clear();
    m_rawCatNumber.clear();
    m_weightCatNumber.clear();
    
    delete m_cutQuad;
}

void CutFlow4l::clearVars()
{
    CutFlowBase::clearVars();
    
    while(!m_dilepInitList.empty()) delete m_dilepInitList.back(), m_dilepInitList.pop_back();
    while(!m_quadInitList.empty()) delete m_quadInitList.back(), m_quadInitList.pop_back();
    
    m_higgs = 0;
    
    m_lepList.clear();
    
    m_dilepInitList.clear();
    m_dilepList.clear();
    
    m_quadInitList.clear();
    m_quadList.clear();
    
    
    m_lastCutPassed = cutFlow::Total;
    
}


////////////////////////////////////////////////
//
// Main function controlling the higgs selection
//
////////////////////////////////////////////////
void CutFlow4l::process()
{
    
    LOG(logDEBUG)<<"\033[35m"<<"-------------------------";
    if(m_limitQuadType == QuadleptonType::_4mu){  LOG(logDEBUG)<<"\033[35m"<<"CutFlow Channel: "<<"4mu"; }
    if(m_limitQuadType == QuadleptonType::_2e2mu){ LOG(logDEBUG)<<"\033[35m"<<"CutFlow Channel: "<<"2e2mu";}
    if(m_limitQuadType == QuadleptonType::_2mu2e){ LOG(logDEBUG)<<"\033[35m"<<"CutFlow Channel: "<<"2mu2e";}
    if(m_limitQuadType == QuadleptonType::_4e)   {LOG(logDEBUG)<<"\033[35m"<<"CutFlow Channel: "<<"4e";}
    LOG(logDEBUG)<<"\033[35m"<<"-------------------------";
    
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
    // pickQuadEvent();   
    
    std::sort (m_quadList.begin(), m_quadList.end(), sortmZ1mZ2);

    int iQuad = 0;
    for(auto quad: m_quadList)
    {
        if(iQuad == 0) quad->addMetadataInt("isNominal", 1);
        else quad->addMetadataInt("isNominal", 0);
        iQuad++;
    }

    if(m_quadList.size() == 0)
    {
        LOG(logERROR)<<"Higgs not found";
        LOG(logERROR)<<"Event number: "<<m_eventCont->eventInfo->eventNumber();
        exit(1);
    }
    
    performHiggsCuts();
    
    //// Picking one quad
    //pickQuadEvent();   
}


// For sorting the quads
bool CutFlow4l::sortmZ1mZ2 (ParticleQuadlepton* i ,ParticleQuadlepton*j)
{
    if(i->getZ1() == j->getZ1())
    {
        return (fabs(i->getZ2()->getTLV().M() - pdgZMass) < fabs(j->getZ2()->getTLV().M() - pdgZMass));
    }
    return (fabs(i->getZ1()->getTLV().M() - pdgZMass) < fabs(j->getZ1()->getTLV().M() - pdgZMass));

}


void CutFlow4l::performHiggsCuts()
{
    if(m_eventCont->isDebug)
    {
        for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
        {
            LOG(logDEBUG)<<"\033[35m"<<"--------------";
            LOG(logDEBUG)<<"Choosen Quad i: "<<i;
            
            if(m_eventCont->isDebug) m_quadList[i]->printDebug();
            LOG(logDEBUG)<<"\033[35m"<<"--------------";
        }
    }
   
    //cout<<"Event number: "<<m_eventCont->eventInfo->eventNumber()<<" m4l: "<<m_higgs->getTLV().M()<<endl;
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
    
    // Iso
    cutIsolation();
    if(m_quadList.size() == 0) return;
    m_lastCutPassed = cutFlow::Iso;
    
    // D0
    cutD0();
    if(m_quadList.size() == 0) return;
    m_lastCutPassed = cutFlow::D0Sig;
    
}

////////////////////////////////////////////////
//
// Cut Helper
//
////////////////////////////////////////////////
// Cuts on number of lepton present in the event
// Do we have enought leptons to make quadruplet
Bool_t CutFlow4l::cutNumLep()
{
    // For 4l
    if(m_limitQuadType == QuadleptonType::NA     && m_lepList.size() >= 4) return true;
    if(m_limitQuadType == QuadleptonType::_4mu   && m_muList.size() >= 4) return true;
    if(m_limitQuadType == QuadleptonType::_2e2mu && (m_muList.size() >= 2 && m_elList.size() >= 2)) return true;
    if(m_limitQuadType == QuadleptonType::_2mu2e && (m_muList.size() >= 2 && m_elList.size() >= 2)) return true;
    if(m_limitQuadType == QuadleptonType::_4e    && m_elList.size() >= 4) return true;
    
    return false;
}





////////////////////////////////////////////////
//
// General Helper
//
////////////////////////////////////////////////

// To convert the ParticleMuon/Electron to their base type
void CutFlow4l::createLepList()
{
    for(Int_t i = 0; i < (Int_t) m_muList.size(); i++)
    {
        m_lepList.push_back(m_muList[i]);
    }
    for(Int_t i = 0; i < (Int_t) m_elList.size(); i++)
    {
        m_lepList.push_back(m_elList[i]);
    }
}


// To create the dilep combination
void CutFlow4l::getDilepComb()
{
    for(Int_t i = 0; i < (Int_t) m_lepList.size(); i++)
    {
        for(Int_t j = i+1; j < (Int_t) m_lepList.size(); j++)
        {
            // Don't want to create a dilep combination with the same lepton
            if(m_lepList[i] == m_lepList[j]) continue;
            ParticleDilepton* temp;
            
            
            // for emu pairs, e is always + and mu is always -
            if(m_lepList[i]->getPartType() != m_lepList[j]->getPartType() )
            {
                if(m_lepList[i]->getPartType() == ParticleType::Electron && m_lepList[j]->getPartType() == ParticleType::Muon)
                {
                    temp = new ParticleDilepton(m_eventCont, m_lepList[i], m_lepList[j]);
                }
                else if (m_lepList[i]->getPartType() == ParticleType::Muon && m_lepList[j]->getPartType() == ParticleType::Electron)
                {
                    temp = new ParticleDilepton(m_eventCont, m_lepList[j], m_lepList[i]);
                }
            }
            // Pairing for OS dilep should be charged based
            else if(m_lepList[i]->getCharge() != m_lepList[j]->getCharge())
            {
                if(m_lepList[i]->getCharge() > 0)
                    temp = new ParticleDilepton(m_eventCont, m_lepList[i], m_lepList[j]);
                else
                    temp = new ParticleDilepton(m_eventCont, m_lepList[j], m_lepList[i]);
            }
            else // pT base the pairing for same sign
            {
                if(m_lepList[i]->getTLV().Pt() > m_lepList[j]->getTLV().Pt())
                    temp = new ParticleDilepton(m_eventCont, m_lepList[i], m_lepList[j]);
                else
                    temp = new ParticleDilepton(m_eventCont, m_lepList[j], m_lepList[i]);
            }
            
            m_dilepInitList.push_back(temp);
        }
    }
    
    
    // To limit the type of quadruplet to the correct one
    for(Int_t i = 0; i < (Int_t) m_dilepInitList.size(); i++)
    {
        if(!cutDilepCharge(m_dilepInitList[i])) continue;
        if(!cutDilepType(m_dilepInitList[i])) continue;
        
        m_dilepList.push_back(m_dilepInitList[i]);
    }
    
    
    //LOG(logDEBUG)<<"--------------";
    //LOG(logDEBUG)<<"Num dilep: "<<m_dilepList.size()<<endl;
    //for(Int_t i = 0; i < (Int_t)m_dilepList.size(); i++)
    //{
    //  LOG(logDEBUG)<<"Dilep i: "<<i;
    //  m_dilepList[i]->printDebug();
    //}
    //LOG(logDEBUG)<<"--------------";
    
    
}
// To cut on the charge of the dilep
Bool_t CutFlow4l::cutDilepCharge(ParticleDilepton* currDilep)
{
    if(currDilep->getCharge() == 0) return true;
    else return false;
}

// To cut on the flavour of the dilep
Bool_t CutFlow4l::cutDilepType(ParticleDilepton* currDilep)
{
    if(currDilep->getDilepType() == DileptonType::_2mu) return true;
    else if(currDilep->getDilepType() == DileptonType::_2e)  return true;
    
    return false;
}

// To create the qaudlep combination
void CutFlow4l::getQuadComb()
{
    for(Int_t i = 0; i < (Int_t) m_dilepList.size(); i++)
    {
        for(Int_t j = i+1; j < (Int_t) m_dilepList.size(); j++)
        {
            // Don't want to create a dilep combination with the same lepton
            if(m_dilepList[i] == m_dilepList[j]) continue;
            if(m_dilepList[i]->isOverlap(m_dilepList[j])) continue;
            
            ParticleQuadlepton* temp = new ParticleQuadlepton(m_eventCont, m_dilepList[i], m_dilepList[j]);
            temp->setQuadAnalType(m_currQuadAnalType);
            
            m_quadInitList.push_back(temp);
        }
    }
    
    for(Int_t i = 0; i < (Int_t) m_quadInitList.size(); i++)
    {
        //if(m_quadInitList[i]->getTLV().M() > 130 * 1000 || m_quadInitList[i]->getTLV().M() < 115 * 100) continue;
        if(!cutQuadCharge(m_quadInitList[i])) continue;
        if(!cutQuadType(m_quadInitList[i])) continue;
        if(!cutMuonType(m_quadInitList[i])) continue;
        
        m_quadList.push_back(m_quadInitList[i]);
    }
    
    
    //LOG(logDEBUG)<<"--------------";
    //LOG(logDEBUG)<<"Init quadlep: "<<m_quadInitList.size();
    //for(Int_t i = 0; i < (Int_t)m_quadInitList.size(); i++)
    //{
    //  LOG(logDEBUG)<<"Quadlep i: "<<i;
    //  m_quadInitList[i]->printDebug();
    //}
    //LOG(logDEBUG)<<"--------------";
    
}

// Cut based on the charge of the quad
Bool_t CutFlow4l::cutQuadCharge(ParticleQuadlepton* currQuad)
{
    if(currQuad->getCharge() == 0) return true;
    else return false;
    
}
// Cut based on the favour of the quad
Bool_t CutFlow4l::cutQuadType(ParticleQuadlepton* currQuad)
{
    
    // Quad specific cleaning
    if(m_limitQuadType == QuadleptonType::_4mu &&
       currQuad->getQuadType() == QuadleptonType::_4mu)    return true;
    if(m_limitQuadType == QuadleptonType::_2e2mu &&
       currQuad->getQuadType() == QuadleptonType::_2e2mu)  return true;
    if(m_limitQuadType == QuadleptonType::_2mu2e &&
       currQuad->getQuadType() == QuadleptonType::_2mu2e)  return true;
    if(m_limitQuadType == QuadleptonType::_4e &&
       currQuad->getQuadType() == QuadleptonType::_4e)     return true;
    
    // If there are not limit sets
    if(m_limitQuadType == QuadleptonType::NA &&
       currQuad->getQuadType() == QuadleptonType::_4mu)    return true;
    if(m_limitQuadType == QuadleptonType::NA &&
       currQuad->getQuadType() == QuadleptonType::_2e2mu)  return true;
    if(m_limitQuadType == QuadleptonType::NA &&
       currQuad->getQuadType() == QuadleptonType::_2mu2e)  return true;
    if(m_limitQuadType == QuadleptonType::NA &&
       currQuad->getQuadType() == QuadleptonType::_4e)     return true;
    
    return false;
}
// Cut based on the number of calo and SA muons in the quad
Bool_t CutFlow4l::cutMuonType(LepCombBase* currComb)
{
    Int_t caloSAcount = 0;
    for(Int_t i = 0; i < currComb->getLepSize(); i++)
    {
        if(currComb->getLep(i)->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* temp = dynamic_cast<const xAOD::Muon*> (currComb->getLep(i)->getParticle());
            if(temp->muonType() == xAOD::Muon::MuonStandAlone) caloSAcount++;
            else if (temp->muonType() == xAOD::Muon::CaloTagged) caloSAcount++;
            else if (temp->muonType() == xAOD::Muon::SiliconAssociatedForwardMuon) caloSAcount++;
        }
    }
    
    if(caloSAcount > 1) return false;
    
    return true;
}

// For kinematic cut on the leptons in the quad
void CutFlow4l::cutKinematic()
{
    //// charge and pt thresholds
    for (Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        
        keep = m_cutQuad->cutKinematic(m_quadList[i]);
        if(!keep)
        {
            LOG(logDEBUG)<<"--------------";
            LOG(logDEBUG)<<"Killing the quad at the kinematic cut";
            if(m_eventCont->isDebug) m_quadList[i]->printDebug();
            LOG(logDEBUG)<<"--------------";

            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}

// For trigger match the leptons in the quad
void CutFlow4l::cutTrigMatch()
{
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        keep = m_cutQuad->cutTrigMatch(m_quadList[i]);
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}

// To pick a quadreplut with Z1 and Z2 closest to PDG mass
void CutFlow4l::pickQuadEvent()
{
    double diffZ1 = std::numeric_limits<double>::infinity();
    double diffZ2 = std::numeric_limits<double>::infinity();
    //Double_t diffSum = std::numeric_limits<double>::infinity();

    ParticleQuadlepton* choosenHiggs = 0;
    
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        ParticleQuadlepton* temp =  m_quadList[i];
        
        // Find the closest one z mass
        Double_t tempDiff1 = fabs(temp->getZ1()->getTLV().M() - pdgZMass);
        Double_t tempDiff2 = fabs(temp->getZ2()->getTLV().M() - pdgZMass);
        //Double_t tempSumDiff = tempDiff1 + tempDiff2;
        //
        //if(tempSumDiff < diffSum)
        //{
        //    diffSum = tempSumDiff;
        //    choosenHiggs = temp;
        //}

        if(tempDiff1 < diffZ1)
        {
            diffZ1 = tempDiff1;
            diffZ2 = tempDiff2; // added June 7, 2013 to fix the issue of chosing the right quadruplet
            choosenHiggs = temp;
        }
        else if(tempDiff1 == diffZ1 && tempDiff2 < diffZ2)
        {
            diffZ2 = tempDiff2;
            choosenHiggs = temp;
        }
        

    }
    
    // Pick the quadruplet and return the a vector with just that element
    m_quadList.clear();
    if(choosenHiggs) m_quadList.push_back(choosenHiggs);
}


////////////////////////
// Helpers to get make the cut implementation easy
////////////////////////
void CutFlow4l::cutMZ1()
{
    
    if(m_setLastCut < cutFlow::Z1Mass) return;
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        // Have to write the current quad to m_higgs to ensure the correct weight calculation
        // are performed for the weighted cutflow setup
        m_higgs = m_quadList[i];
        keep = m_cutQuad->cutMZ1(m_higgs);
        if(!keep)
        {
            LOG(logDEBUG)<<"--------------";
            LOG(logDEBUG)<<"Killing the quad at mZ1";
            if(m_eventCont->isDebug) m_quadList[i]->printDebug();
            LOG(logDEBUG)<<"--------------";

            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
        else updateCutFlow(cutFlow::Z1Mass);
    }
    
    // Clear m_higgs, to make sure that we don't use it
    m_higgs = 0;
}

void CutFlow4l::cutMZ2()
{
    if(m_setLastCut < cutFlow::Z2Mass) return;

    // mZ2 cut
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        m_higgs = m_quadList[i];
        keep = m_cutQuad->cutMZ2(m_higgs);
        if(!keep)
        {
            LOG(logDEBUG)<<"--------------";
            LOG(logDEBUG)<<"Killing the quad at mZ2";
            if(m_eventCont->isDebug)  m_quadList[i]->printDebug();
            LOG(logDEBUG)<<"--------------";

            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
        else updateCutFlow(cutFlow::Z2Mass);
        
    }
}

void CutFlow4l::cutDeltaRJpsi()
{
    if(m_setLastCut < cutFlow::DeltaR) return;

    //  cut
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        m_higgs = m_quadList[i];
        keep = m_cutQuad->cutDeltaR(m_higgs) && m_cutQuad->JPsiVeto(m_higgs);
        if(!keep)
        {
            LOG(logDEBUG)<<"--------------";
            LOG(logDEBUG)<<"Killing the quad at Delta R and JPsi";
            if(m_eventCont->isDebug) m_quadList[i]->printDebug();
            LOG(logDEBUG)<<"--------------";

            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
        else updateCutFlow(cutFlow::DeltaR);
        
    }
    // Clear m_higgs, to make sure that we don't use it
    m_higgs = 0;
    
}

void CutFlow4l::cutIsolation()
{
    if(m_setLastCut < cutFlow::Iso) return;

    // Iso cut
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        m_higgs = m_quadList[i];
        keep = m_cutQuad->cutIsolation(m_higgs);
        //keep = true;
        if(!keep)
        {
            LOG(logDEBUG)<<"--------------";
            LOG(logDEBUG)<<"Killing the quad at IsoCut";
            if(m_eventCont->isDebug) m_quadList[i]->printDebug();
            LOG(logDEBUG)<<"--------------";

            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
        else updateCutFlow(cutFlow::Iso);
        
    }
    // Clear m_higgs, to make sure that we don't use it
    m_higgs = 0;
    
}

void CutFlow4l::cutD0()
{
    if(m_setLastCut < cutFlow::D0Sig) return;

    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        m_higgs = m_quadList[i];
        keep = m_cutQuad->cutD0Sig(m_higgs);
        //keep = true;
        if(!keep)
        {
            LOG(logDEBUG)<<"--------------";
            LOG(logDEBUG)<<"Killing the quad at d0";
            if(m_eventCont->isDebug) m_quadList[i]->printDebug();
            LOG(logDEBUG)<<"--------------";

            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
        else updateCutFlow(cutFlow::D0Sig);
        
    }
    // Clear m_higgs, to make sure that we don't use it
    m_higgs = 0;
    
}


// To trigger the full calculations
void CutFlow4l::calcIsoD0()
{
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        // and prevent any debug output from this call
        m_cutQuad->cutIsolation(m_quadList[i], true);
        m_cutQuad->cutD0Sig(m_quadList[i], true);
    }
}



// For cutflow
void CutFlow4l::initCutFlow()
{
    for(Int_t i = 0; i <= cutFlow::Final; i++)
    {
        m_cutName.push_back("");
    }
    for(Int_t i = 0; i < prodTypeSimp::MaxProdTypeSimp; i++)
    {
        m_catergoryName.push_back("");
    }
    
    for (auto sysListItr:m_eventCont->m_sysList){
        m_rawCutFlow[sysListItr].reserve(m_cutName.size());
        m_weightCutFlow[sysListItr].reserve(m_cutName.size());
        
        for(Int_t i = 0; i < (Int_t) m_cutName.size(); i++)
        {
            m_rawCutFlow[sysListItr].push_back(0);
            m_weightCutFlow[sysListItr].push_back(0);
        }
    }
    for (auto sysListItr:m_eventCont->m_sysList){
        m_rawCatNumber[sysListItr].reserve(m_cutName.size());
        m_weightCatNumber[sysListItr].reserve(m_cutName.size());
        
        for(Int_t i = 0; i < (Int_t) m_catergoryName.size(); i++)
        {
            m_rawCatNumber[sysListItr].push_back(0);
            m_weightCatNumber[sysListItr].push_back(0);
        }
    }
    
    m_cutName[cutFlow::Total]             = "Total";
    m_cutName[cutFlow::DataPreselection]  = "DataPreselection";
    m_cutName[cutFlow::Preselection]      = "Preselection";
    m_cutName[cutFlow::Trigger]           = "Trigger";
    m_cutName[cutFlow::Lepton]            = "Lepton";
    m_cutName[cutFlow::SFOS]              = "SFOS";
    m_cutName[cutFlow::Kinematics]        = "Kinematics";
    m_cutName[cutFlow::TriggerMatch]      = "TriggerMatch";
    m_cutName[cutFlow::Z1Mass]            = "Z1Mass";
    m_cutName[cutFlow::Z2Mass]            = "Z2Mass";
    m_cutName[cutFlow::DeltaR]            = "DeltaR";
    m_cutName[cutFlow::Iso]               = "Iso";
    m_cutName[cutFlow::D0Sig]             = "D0Sig";
    m_cutName[cutFlow::Final]             = "Final";
    
    m_catergoryName[prodTypeSimp::njet0]    = "nJet0";
    m_catergoryName[prodTypeSimp::njet1]    = "nJet1";
    m_catergoryName[prodTypeSimp::njet2_VH] = "nJet2_VH";
    m_catergoryName[prodTypeSimp::njet2_VBF]= "nJet2_VBF";
    m_catergoryName[prodTypeSimp::leptonic] = "leptonic";
    m_catergoryName[prodTypeSimp::ttH]      = "ttH";
    
}

// To set the quad event type
void CutFlow4l::setQuadAnalysisType(Int_t quadType)
{
    m_limitQuadType = static_cast<QuadleptonType::QuadleptonType>(quadType);
    
    if(m_limitQuadType == QuadleptonType::_4mu) m_cutFlowName += " 4mu";
    else if(m_limitQuadType == QuadleptonType::_2e2mu) m_cutFlowName += " 2e2mu";
    else if(m_limitQuadType == QuadleptonType::_2mu2e) m_cutFlowName += " 2mu2e";
    else if(m_limitQuadType == QuadleptonType::_4e) m_cutFlowName += " 4e";
    
}


// For CutFlow
void CutFlow4l::updateCutFlow(Int_t cutLevel, Int_t valToAdd)
{
    if(m_rawCutFlow.find(m_eventCont->m_currVariation) == m_rawCutFlow.end())
    {
        LOG(logERROR)<<"CutFlow4l::updateCutFlow - requested variation is not in the map";
        exit(1);
    }
    m_rawCutFlow[m_eventCont->m_currVariation].at(cutLevel) += valToAdd;
    
    Double_t weight = 1;
    if(cutLevel <= cutFlow::TriggerMatch) weight = m_applyWeight->getEventWeight();
    else
    {
        //LOG(logINFO)<<m_eventCont->eventInfo->eventNumber();
        //if(m_quadList.size() > 0) LOG(logINFO)<<m_quadList[0];
        
        if(m_quadList.size() > 0) weight = m_applyWeight->getTotalWeight(m_quadList[0]);
    }
    
    m_weightCutFlow[m_eventCont->m_currVariation].at(cutLevel) += (valToAdd * weight);
}

void CutFlow4l::updateCategory(Int_t currCat, Int_t valToAdd)
{
    if(m_rawCatNumber.find(m_eventCont->m_currVariation) == m_rawCutFlow.end())
    {
        LOG(logERROR)<<"CutFlow4l::updateCategory - requested variation is not in the map";
        exit(1);
    }
    m_rawCatNumber[m_eventCont->m_currVariation].at(currCat) += valToAdd;
    
    Double_t weight = 1;
    if(m_quadList.size() > 0) weight = m_applyWeight->getTotalWeight(m_quadList[0]);
    
    m_weightCatNumber[m_eventCont->m_currVariation].at(currCat) += (valToAdd * weight);
}


// To Print Cutflow
// If other class want to specify another way of printing or a different way of counting,
// they should modify this function
void CutFlow4l::printCutFlow()
{
    cout<<"-----------------------------------------"<<endl;
    cout<<"CutFlow channel: "<<m_cutFlowName<<endl;
    cout<<endl;
    cout<<setw(17)<<"CutName"<<": "<<"Raw Cutflow - weighted Cutflow"<<endl;
    
    for(Int_t i = 0; i < (Int_t) m_cutName.size(); i++)
    {
        cout<<setw(17)<<m_cutName[i]<<": "
        <<m_rawCutFlow[m_eventCont->m_currVariation].at(i)<<" - "
        <<m_weightCutFlow[m_eventCont->m_currVariation].at(i)<<endl;
    }
    cout<<endl;
    
    cout<<setw(17)<<"Production type"<<": "<<"Raw - weighted"<<endl;
    for(Int_t i = 0; i < (Int_t) m_catergoryName.size(); i++)
    {
        cout<<setw(17)<<m_catergoryName[i]<<": "
        <<m_rawCatNumber[m_eventCont->m_currVariation].at(i)<<" - "
        <<m_weightCatNumber[m_eventCont->m_currVariation].at(i)<<endl;
    }
    cout<<endl;
    
    cout<<"-----------------------------------------"<<endl;
    
}

