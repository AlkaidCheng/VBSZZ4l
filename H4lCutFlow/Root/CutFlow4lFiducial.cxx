#include "H4lCutFlow/CutFlow4lFiducial.h"
using namespace std;

CutFlow4lFiducial::CutFlow4lFiducial(EventContainer* eventcont, ApplyWeight4l* applyWeight)
: CutFlowBase(eventcont)
{
    m_applyWeight = applyWeight;

    m_limitQuadType = QuadleptonType::NA;

    m_cutQuad = new CutLepComb(m_eventCont);

    m_higgs = 0;
    m_doMassWindowCut = true;
    
    m_cutFlowName = "Nominal";

    clearVars();
}

CutFlow4lFiducial::~CutFlow4lFiducial()
{
    m_catergoryName.clear();
    m_rawCatNumber.clear();
    m_weightCatNumber.clear();
    
    delete m_cutQuad;
}

void CutFlow4lFiducial::clearVars()
{
    CutFlowBase::clearVars();

    while(!m_dilepInitList.empty()) delete m_dilepInitList.back(), m_dilepInitList.pop_back();
    while(!m_quadInitList.empty()) delete m_quadInitList.back(), m_quadInitList.pop_back();

    m_higgs = 0;
    m_doMassWindowCut = true;
    
    m_lepList.clear();

    m_dilepInitList.clear();
    m_dilepList.clear();

    m_quadInitList.clear();
    m_quadList.clear();
    m_quadList_kinCut.clear();
    m_quadList_trigCut.clear();

    m_lastCutPassed = cutFlow::Total;

}


////////////////////////////////////////////////
//
// Main function controlling the higgs selection
//
//////////////////////////////////////////////// 
void CutFlow4lFiducial::process()
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

    //if(m_limitQuadType == QuadleptonType::_4mu){   cout<<"CutFlow Channel: "<<"4mu"; }
    //if(m_limitQuadType == QuadleptonType::_2e2mu){ cout<<"CutFlow Channel: "<<"2e2mu";}
    //if(m_limitQuadType == QuadleptonType::_2mu2e){ cout<<"CutFlow Channel: "<<"2mu2e";}
    //if(m_limitQuadType == QuadleptonType::_4e)   { cout<<"CutFlow Channel: "<<"4e";}
    //  cout<<" Event#: "<<m_eventCont->eventInfo->eventNumber()<<endl;

    // Kinematic cut
    cutKinematic();
    
    if(m_quadList_kinCut.size() == 0) return;
    updateCutFlow(cutFlow::Kinematics);
    m_lastCutPassed = cutFlow::Kinematics;

    // Trigger Match cut
    cutTrigMatch();
    
    if(m_quadList_trigCut.size() == 0) return;
    updateCutFlow(cutFlow::TriggerMatch);
    m_lastCutPassed = cutFlow::TriggerMatch;

    // Picking one quad
    pickQuadEvent();

    if(!m_higgs)
    {
        LOG(logERROR)<<"Higgs not found";
        exit(-1);
    }
    
    performHiggsCuts();
    

}

void CutFlow4lFiducial::performHiggsCuts()
{
    LOG(logDEBUG)<<"\033[35m"<<"--------------";
    LOG(logDEBUG)<<"Choosen Quad";
    
    if(m_eventCont->isDebug) m_higgs->printDebug();
    LOG(logDEBUG)<<"\033[35m"<<"--------------";
    
    
    // mZ1 cut
    if(!m_cutQuad->cutMZ1(m_higgs)) return;
    updateCutFlow(cutFlow::Z1Mass);
    m_lastCutPassed = cutFlow::Z1Mass;
    
    // mZ2 cut
    // disable sliding cut by keeping cut at 12 for the purpose of cutflow comparison
    //m_cutQuad->m_cutMZ2Cut[1] = 12 * 1000;
    if(!m_cutQuad->cutMZ2(m_higgs)) return;
    updateCutFlow(cutFlow::Z2Mass);
    m_lastCutPassed = cutFlow::Z2Mass;

    // Mass Window cut
    if(m_doMassWindowCut) {
        if(!((m_higgs->getTLV().M() > 115000.0) && (m_higgs->getTLV().M() < 130000.0))) return;
        updateCutFlow(cutFlow::MassWindow);
        m_lastCutPassed = cutFlow::MassWindow;
    }
    // DeltaR and Jpsi cut
    //m_cutQuad->m_cutMZ2Cut[1] = 12 * 1000;
    //

    if(!m_cutQuad->cutDeltaR(m_higgs)) return;
    updateCutFlow(cutFlow::DeltaR);
    m_lastCutPassed = cutFlow::DeltaR;

    if(!m_cutQuad->JPsiVeto(m_higgs)) return;
    updateCutFlow(cutFlow::JPsiVeto);
    m_lastCutPassed = cutFlow::JPsiVeto;
    
    
    // Mass Window cut
    //if(!((m_higgs->getTLV().M() > 120000.0) && (m_higgs->getTLV().M() < 130000.0))) return;
    //updateCutFlow(cutFlow::MassWindow);
    //m_lastCutPassed = cutFlow::MassWindow;
}



////////////////////////////////////////////////
//
// Cut Helper
//
//////////////////////////////////////////////// 
// Cuts on number of lepton present in the event
// Do we have enought leptons to make quadruplet
Bool_t CutFlow4lFiducial::cutNumLep()
{
    //// Debug information
    //LOG(logDEBUG)<<"--------------";
    //LOG(logDEBUG)<<"EventNumber: "<<m_eventcont->eventInfo->eventNumber();
    //LOG(logDEBUG)<<"RunNumber: "<<m_eventcont->eventInfo->runNumber();
    //LOG(logDEBUG)<<"Num mu: "<<m_muList.size();
    //LOG(logDEBUG)<<"Num el: "<<m_elList.size();
    //LOG(logDEBUG)<<"--------------";



    // For 4l
    if(m_limitQuadType == QuadleptonType::NA     && (m_muList.size() >= 4 || m_elList.size() >= 4 || (m_muList.size() >= 2 && m_elList.size() >= 2))) return true;
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
void CutFlow4lFiducial::createLepList()
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
void CutFlow4lFiducial::getDilepComb()
{
    for(Int_t i = 0; i < (Int_t) m_lepList.size(); i++)
    {
        for(Int_t j = i+1; j < (Int_t) m_lepList.size(); j++)
        {
            // Don't want to create a dilep combination with the same lepton
            if(m_lepList[i] == m_lepList[j]) continue;
            ParticleDilepton* temp;

            if(m_lepList[i]->getCharge() > 0) 
                temp = new ParticleDilepton(m_eventCont, m_lepList[i], m_lepList[j]);
            else
                temp = new ParticleDilepton(m_eventCont, m_lepList[j], m_lepList[i]);

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
Bool_t CutFlow4lFiducial::cutDilepCharge(ParticleDilepton* currDilep)
{
    if(currDilep->getCharge() == 0) return true;
    else return false;
}

// To cut on the flavour of the dilep
Bool_t CutFlow4lFiducial::cutDilepType(ParticleDilepton* currDilep)
{
         if(currDilep->getDilepType() == DileptonType::_2mu) return true;
    else if(currDilep->getDilepType() == DileptonType::_2e)  return true;
         
    return false;
}

// To create the qaudlep combination
void CutFlow4lFiducial::getQuadComb()
{
    for(Int_t i = 0; i < (Int_t) m_dilepList.size(); i++)
    {
        for(Int_t j = i+1; j < (Int_t) m_dilepList.size(); j++)
        {
            // Don't want to create a dilep combination with the same lepton
            if(m_dilepList[i] == m_dilepList[j]) continue;
            if(m_dilepList[i]->isOverlap(m_dilepList[j])) continue;

            ParticleQuadlepton* temp = new ParticleQuadlepton(m_eventCont, m_dilepList[i], m_dilepList[j]);

            m_quadInitList.push_back(temp);
        }
    }

    for(Int_t i = 0; i < (Int_t) m_quadInitList.size(); i++)
    {
        if(!cutQuadCharge(m_quadInitList[i])) continue;
        if(!cutQuadType(m_quadInitList[i])) continue;
        //if(!cutQuadMuonType(m_quadInitList[i])) continue;
        
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
Bool_t CutFlow4lFiducial::cutQuadCharge(ParticleQuadlepton* currQuad)
{
    if(currQuad->getCharge() == 0) return true;
    else return false;

}
// Cut based on the favour of the quad
Bool_t CutFlow4lFiducial::cutQuadType(ParticleQuadlepton* currQuad)
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
Bool_t CutFlow4lFiducial::cutQuadMuonType(ParticleQuadlepton* currQuad)
{
    Int_t caloSAcount = 0;
    for(Int_t i = 0; i < currQuad->getLepSize(); i++)
    {
        if(currQuad->getLep(i)->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* temp = dynamic_cast<const xAOD::Muon*> (currQuad->getLep(i)->getParticle());
            if(temp->muonType() == xAOD::Muon::MuonStandAlone) caloSAcount++;
            else if (temp->muonType() == xAOD::Muon::CaloTagged) caloSAcount++;
            else if (temp->muonType() == xAOD::Muon::SiliconAssociatedForwardMuon) caloSAcount++;
        }
    }

    if(caloSAcount > 1) return false;

    return true;
}

// For kinematic cut on the leptons in the quad
void CutFlow4lFiducial::cutKinematic()
{
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        if(!m_cutQuad->cutKinematic(m_quadList[i])) continue;
        m_quadList_kinCut.push_back(m_quadList[i]);
    }
}

// For trigger match the leptons in the quad
void CutFlow4lFiducial::cutTrigMatch()
{
    for(Int_t i = 0; i < (Int_t) m_quadList_kinCut.size(); i++)
    {
        //if(!m_cutQuad->cutTrigMatch(m_quadList_kinCut[i])) continue;
        m_quadList_trigCut.push_back(m_quadList_kinCut[i]);
    }

}

// To pick a quadreplut with Z1 and Z2 closest to PDG mass
void CutFlow4lFiducial::pickQuadEvent()
{
    Double_t diffZ1 = 9999 * 1000;
    Double_t diffZ2 = 9999 * 1000;

    for(Int_t i = 0; i < (Int_t) m_quadList_trigCut.size(); i++)
    {
        ParticleQuadlepton* temp =  m_quadList_trigCut[i];

        // Find the closest one z mass
        Double_t tempDiff1 = fabs(temp->getZ1()->getTLV().M() - pdgZMass);
        Double_t tempDiff2 = fabs(temp->getZ2()->getTLV().M() - pdgZMass);

        if(tempDiff1 < diffZ1)
        {
            diffZ1 = tempDiff1;
            diffZ2 = tempDiff2; // added June 7, 2013 to fix the issue of chosing the right quadruplet
            m_higgs = temp;
        }
        else if(tempDiff1 == diffZ1 && tempDiff2 < diffZ2)
        {
            diffZ2 = tempDiff2;
            m_higgs = temp;
        }
    }
}


// For cutflow
void CutFlow4lFiducial::initCutFlow() 
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
    m_cutName[cutFlow::JPsiVeto]            = "JsiVeto";
    //m_cutName[cutFlow::TrackIso]          = "TrackIso";
    //m_cutName[cutFlow::CaloIso]           = "CaloIso";
    //m_cutName[cutFlow::D0Sig]             = "D0Sig";
    m_cutName[cutFlow::MassWindow]        = "M4lMassWindow";
    m_cutName[cutFlow::Final]             = "Final";
    
    m_catergoryName[prodTypeSimp::njet0]    = "nJet0";
    m_catergoryName[prodTypeSimp::njet1]    = "nJet1";
    m_catergoryName[prodTypeSimp::njet2_VH] = "nJet2_VH";
    m_catergoryName[prodTypeSimp::njet2_VBF]= "nJet2_VBF";
    m_catergoryName[prodTypeSimp::leptonic] = "leptonic";
    m_catergoryName[prodTypeSimp::ttH]      = "ttH";

}

// To set the quad event type
void CutFlow4lFiducial::setQuadAnalysisType(Int_t quadType)
{
    m_limitQuadType = static_cast<QuadleptonType::QuadleptonType>(quadType);

         if(m_limitQuadType == QuadleptonType::_4mu) m_cutFlowName += " 4mu";
    else if(m_limitQuadType == QuadleptonType::_2e2mu) m_cutFlowName += " 2e2mu";
    else if(m_limitQuadType == QuadleptonType::_2mu2e) m_cutFlowName += " 2mu2e";
    else if(m_limitQuadType == QuadleptonType::_4e) m_cutFlowName += " 4e";

}


// For CutFlow
void CutFlow4lFiducial::updateCutFlow(Int_t cutLevel, Int_t valToAdd) 
{
    if(m_rawCutFlow.find(m_eventCont->m_currVariation) == m_rawCutFlow.end())
    {
        LOG(logERROR)<<"CutFlow4lFiducial::updateCutFlow - requested variation is not in the map";
        exit(-1);
    }
    m_rawCutFlow[m_eventCont->m_currVariation].at(cutLevel) += valToAdd;

    Double_t weight = 1;
    if(cutLevel <= cutFlow::TriggerMatch) weight = m_applyWeight->getEventWeight();
    else  weight = m_applyWeight->getTotalWeight(m_higgs);

    m_weightCutFlow[m_eventCont->m_currVariation].at(cutLevel) += (valToAdd * weight);

}

void CutFlow4lFiducial::updateCategory(Int_t currCat, Int_t valToAdd)
{
    if(m_rawCatNumber.find(m_eventCont->m_currVariation) == m_rawCutFlow.end())
    {
        LOG(logERROR)<<"CutFlow4lFiducial::updateCategory - requested variation is not in the map";
        exit(-1);
    }
    m_rawCatNumber[m_eventCont->m_currVariation].at(currCat) += valToAdd;
    
    Double_t weight = 1;
    weight = m_applyWeight->getTotalWeight(m_higgs);
    
    m_weightCatNumber[m_eventCont->m_currVariation].at(currCat) += (valToAdd * weight);
}


// To Print Cutflow
// If other class want to specify another way of printing or a different way of counting,
// they should modify this function
void CutFlow4lFiducial::printCutFlow()
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

