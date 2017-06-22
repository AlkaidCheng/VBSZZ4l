#include "H4lCutFlow/CutFlow3l.h"
using namespace std;

    CutFlow3l::CutFlow3l(EventContainer* eventcont, ApplyWeight4l* applyWeight)
: CutFlowBase(eventcont)
{
    m_applyWeight = applyWeight;
    m_cutLepComb = new CutLepComb(m_eventCont);
    m_cutFlowName = "Z + l";

    clearVars();
}

CutFlow3l::~CutFlow3l()
{
    m_catergoryName.clear();
    m_rawCatNumber.clear();
    m_weightCatNumber.clear();

    delete m_cutLepComb;
}

void CutFlow3l::clearVars()
{
    CutFlowBase::clearVars();
    m_lastCutPassed = cutFlowZl::Total;

    m_lepList.clear();
    m_dilepList.clear();
    while(!m_dilepInitList.empty()) delete m_dilepInitList.back(), m_dilepInitList.pop_back();
    m_dilepInitList.clear();
    while(!m_3lInitList.empty()) delete m_3lInitList.back(), m_3lInitList.pop_back();
    m_3lInitList.clear();
    m_ZPart = 0;    
    m_candList.clear();

}

void CutFlow3l::initialize()
{
    CutFlowBase::initialize();

    // Modify the pT cuts based on what type of cutflow it is
    if(m_cutflowType == ZlCutFlowType::ZplusMu)
    {
        m_cutLepComb->m_pT1CutVal = 20 * 1000;
        m_cutLepComb->m_pT2CutVal = 15 * 1000;
    }
    else if(m_cutflowType == ZlCutFlowType::ZplusX)
    {
        m_cutLepComb->m_pT1CutVal = 20 * 1000;
        m_cutLepComb->m_pT2CutVal = 15 * 1000;
        //m_cutLepComb->doTrigMatching();
    }
    else
    {
        LOG(logERROR)<<"CutFlow3l::initialize() - cutflow type not supported";
        exit(1);
    }

}


////////////////////////////////////////////////
//
// Main function controlling the Z+l selection
//
//////////////////////////////////////////////// 
void CutFlow3l::process()
{
    // Modify the pT cuts based on what type of cutflow it is
    if(m_cutflowType == ZlCutFlowType::ZplusMu) processZmu();
    else if(m_cutflowType == ZlCutFlowType::ZplusX) processZel();
}

void CutFlow3l::processZmu()
{
    createLepList();
    // If not enough leptons to make the Z return
    if(m_muList.size() < 2 && m_elList.size() < 2) return;
    updateCutFlow(cutFlowZl::Lepton);
    m_lastCutPassed = cutFlowZl::Lepton;

    // Now make the dilep pairs
    getDilepComb();

    // SFOS cut
    if(m_dilepList.size() == 0) return;
    updateCutFlow(cutFlowZl::SFOS);
    m_lastCutPassed = cutFlowZl::SFOS;

    // Kinematic cut
    cutKinematic();

    if(m_dilepList.size() == 0) return;
    updateCutFlow(cutFlowZl::Kinematics);
    m_lastCutPassed = cutFlowZl::Kinematics;

    // Trigger Match cut
    cutTrigMatch();

    if(m_dilepList.size() == 0) return;
    updateCutFlow(cutFlowZl::TriggerMatch);
    m_lastCutPassed = cutFlowZl::TriggerMatch;

    // Picking one quad
    pickDilep();
    if(m_eventCont->isDebug)
    {
        LOG(logDEBUG)<<"Choosen Z";
        m_ZPart->printDebug();
    }
    // Mass Cut
    if(fabs(m_ZPart->getTLV().M()) < 76 * 1000 || fabs(m_ZPart->getTLV().M()) > 106 * 1000) return;
    updateCutFlow(cutFlowZl::ZMass);
    m_lastCutPassed = cutFlowZl::ZMass;

    // DeltaR cut
    if(!m_cutLepComb->cutDeltaR(m_ZPart)) return;
    updateCutFlow(cutFlowZl::DeltaR);
    m_lastCutPassed = cutFlowZl::DeltaR;

    // No met cut for Zmu
    updateCutFlow(cutFlowZl::MET);
    m_lastCutPassed = cutFlowZl::MET;

    m_candList = create3lCand(m_ZPart, m_muList);

    for(size_t i = 0; i < m_candList.size(); i++)
    {
        LOG(logDEBUG)<<"Before any selection";
        if(m_eventCont->isDebug) m_candList[i]->printDebug();
    }

    // DeltaR and Jpsi cut
    clean3lList(m_candList, true);

    // Iso and d0 cut on leading Z
    cutZIsoD0(m_candList);
    
    // The 3l veto for muon channels
    // If greater than 3 leptons, then we will have multiple candidates
    // so essentially reject the evnet if there are more than 1 candidate
    if(m_candList.size() > 1)
    {
        LOG(logDEBUG)<<"Rejecting event since there are > 1 Z+mu candidates avaiable";
        m_candList.clear();
    }

    for(size_t i = 0; i < m_candList.size(); i++)
    {
        updateCutFlow(cutFlowZl::DeltaR_l);
        m_lastCutPassed = cutFlowZl::DeltaR_l;

        // Trig caculations
        m_cutLepComb->cutIsolation(m_candList[i], false);
        m_cutLepComb->cutD0Sig(m_candList[i], false);
    }

}

void CutFlow3l::processZel()
{
    createLepList();
    // If not enough leptons to make the Z return
    LOG(logDEBUG)<<"mu list: "<<m_muList.size();
    LOG(logDEBUG)<<"mu list: "<<(m_muList.size() < 2);
    LOG(logDEBUG)<<"!cutZeeElCut(): "<<(!cutZeeElCut());
    if(m_muList.size() < 2 && !cutZeeElCut()) return;
    updateCutFlow(cutFlowZl::Lepton);
    m_lastCutPassed = cutFlowZl::Lepton;


    // Now make the dilep pairs
    getDilepComb();

    // SFOS cut
    if(m_dilepList.size() == 0) return;
    updateCutFlow(cutFlowZl::SFOS, m_dilepList.size());
    m_lastCutPassed = cutFlowZl::SFOS;

    // Kinematic cut
    cutKinematic();

    if(m_dilepList.size() == 0) return;
    updateCutFlow(cutFlowZl::Kinematics, m_dilepList.size());
    m_lastCutPassed = cutFlowZl::Kinematics;

    // Trigger Match cut
    cutTrigMatch();

    if(m_dilepList.size() == 0) return;
    updateCutFlow(cutFlowZl::TriggerMatch, m_dilepList.size());
    m_lastCutPassed = cutFlowZl::TriggerMatch;

    if(m_eventCont->isDebug)
    {
        LOG(logDEBUG)<<"Z candidates";
        for(auto part:m_dilepList)
        {
            part->printDebug();
        }
    }

    // Picking one quad
    pickDilep();
    if(m_eventCont->isDebug)
    {
        LOG(logDEBUG)<<"Choosen Z";
        m_ZPart->printDebug();
    }

    // Mass Cut
    if(fabs(m_ZPart->getTLV().M()) < 76 * 1000 || fabs(m_ZPart->getTLV().M()) > 106 * 1000) return;
    updateCutFlow(cutFlowZl::ZMass);
    m_lastCutPassed = cutFlowZl::ZMass;

    // DeltaR cut
    if(!m_cutLepComb->cutDeltaR(m_ZPart)) return;
    updateCutFlow(cutFlowZl::DeltaR);
    m_lastCutPassed = cutFlowZl::DeltaR;

    // MET
    processMET();
    // remove MET CUT for now
    //LOG(logDEBUG)<<"MET: "<<m_metCalc->getTrackMET()->met();
    //if(m_metCalc->getTrackMET()->met() > 50 * 1000) return;

    // No met cut for Zmu
    updateCutFlow(cutFlowZl::MET);
    m_lastCutPassed = cutFlowZl::MET;

    m_candList = create3lCand(m_ZPart, m_elList);
    
    
    for(size_t i = 0; i < m_candList.size(); i++)
    {
        LOG(logDEBUG)<<"Before any selection";
        if(m_eventCont->isDebug) m_candList[i]->printDebug();
    }

    // DeltaR and Jpsi cut
    clean3lList(m_candList, true);
    // Iso and d0 cut on leading Z
    cutZIsoD0(m_candList);

    for(size_t i = 0; i < m_candList.size(); i++)
    {
        updateCutFlow(cutFlowZl::DeltaR_l);
        m_lastCutPassed = cutFlowZl::DeltaR_l;
        LOG(logDEBUG)<<"Final any selection";        
        if(m_eventCont->isDebug) m_candList[i]->printDebug();


        // Trig caculations
        m_cutLepComb->cutIsolation(m_candList[i], false);
        m_cutLepComb->cutD0Sig(m_candList[i], false);
    }


    for(size_t i = 0; i < m_candList.size(); i++)
    {
        LOG(logDEBUG)<<"After selection";
        if(m_eventCont->isDebug) m_candList[i]->printDebug();
    }


}


////////////////////////////////////////////////
//
// Cut Helper
//
////////////////////////////////////////////////

bool CutFlow3l::cutZeeElCut()
{
    int count = 0;
    for(Int_t i = 0; i < (Int_t) m_elList.size(); i++)
    {
        if(m_elList[i]->getParticle()->auxdecor< int >( "looseID" )) count++;
    }

    if(count < 2) return false;
    return true;
}


// To convert the ParticleMuon/Electron to their base type
void CutFlow3l::createLepList()
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
void CutFlow3l::getDilepComb()
{
    for(Int_t i = 0; i < (Int_t) m_lepList.size(); i++)
    {
        if(m_lepList[i]->getTLV().Pt() > 1e+7) continue; // workaround for some issue in pT smearing
        for(Int_t j = i+1; j < (Int_t) m_lepList.size(); j++)
        {
            if(m_lepList[j]->getTLV().Pt() > 1e+7) continue; // workaround for some issue in pT smearing

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
        if(!cutDilepType(m_dilepInitList[i]))   continue;
        if(!cutDilepID(m_dilepInitList[i]))     continue;
        if(!cutMuonType(m_dilepInitList[i]))    continue;

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
Bool_t CutFlow3l::cutDilepCharge(ParticleDilepton* currDilep)
{
    if(currDilep->getCharge() == 0) return true;
    else return false;
}

// To cut on the flavour of the dilep
Bool_t CutFlow3l::cutDilepType(ParticleDilepton* currDilep)
{
    if(currDilep->getDilepType() == DileptonType::_2mu) return true;
    else if(currDilep->getDilepType() == DileptonType::_2e)  return true;

    return false;
}

Bool_t CutFlow3l::cutDilepID(ParticleDilepton* currDilep)
{
    // muons don't have a looser ID cut
    if(currDilep->getDilepType() == DileptonType::_2mu) return true;

    // El can have looser ID cut, just make sure that electrons are alteast loose
    Bool_t keep = true;
    keep = currDilep->getLepOne()->getParticle()->auxdecor< int >( "looseID" ) && currDilep->getLepTwo()->getParticle()->auxdecor< int >( "looseID" );

    return keep;
}

// Cut based on the number of calo and SA muons in the quad
Bool_t CutFlow3l::cutMuonType(LepCombBase* currComb)
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
// Remove all the quads that fail the kinematic cuts
void CutFlow3l::cutKinematic()
{
    //// charge and pt thresholds
    for (Int_t i = 0; i < (Int_t) m_dilepList.size() && i >= 0; i++)
    {
        Bool_t keep = true;

        keep = m_cutLepComb->cutKinematic(m_dilepList[i]);
        if(!keep)
        {
            m_dilepList.erase(m_dilepList.begin() + i);
            i--;
        }
    }
}

// For trigger match the leptons in the quad
void CutFlow3l::cutTrigMatch()
{
    return;
    for(Int_t i = 0; i < (Int_t) m_dilepList.size() && i >= 0; i++)
    {
        Bool_t keep = true;
        keep = m_cutLepComb->cutTrigMatch(m_dilepList[i]);
        if(!keep)
        {
            m_dilepList.erase(m_dilepList.begin() + i);
            i--;
        }
    }
}


// To pick a quadreplut with Z1 and Z2 closest to PDG mass
void CutFlow3l::pickDilep()
{
    Double_t diffZ = 9999 * 1000;

    for(Int_t i = 0; i < (Int_t) m_dilepList.size(); i++)
    {
        ParticleDilepton* temp =  m_dilepList[i];

        // Find the closest one z mass
        Double_t tempDiff= fabs(temp->getTLV().M() - pdgZMass);
        if(tempDiff < diffZ)
        {
            diffZ = tempDiff;
            m_ZPart = temp;
        }
    }

    if(!m_ZPart)
    {
        LOG(logERROR)<<m_cutFlowName<<" m_quadList_trigCut size: "<<m_dilepList.size();
        LOG(logERROR)<<"Z not found";
        LOG(logERROR)<<"Event number: "<<m_eventCont->eventInfo->eventNumber();
        exit(1);
    }
}


vector<ParticleMulti*> CutFlow3l::create3lCand(ParticleDilepton* ZPart, vector<ParticleVar*>& partList)
{
    vector<ParticleMulti*> candList;

    for(size_t i = 0; i < partList.size(); i++)
    {
        if(ZPart->isOverlap(partList[i])) continue;

        ParticleMulti* temp = new ParticleMulti(m_eventCont);
        temp->setAnalysisType(m_eventCont->m_analType);

        temp->addParticle("ZCand", ZPart);
        temp->addParticleVar(ZPart->getLepOne());
        temp->addParticleVar(ZPart->getLepTwo());

        temp->addParticle("lep", partList[i]);
        temp->addParticleVar(partList[i]);

        // For clean up 
        m_3lInitList.push_back(temp);

        // Add the 
        if(!cutMuonType(temp)) continue;
        candList.push_back(temp);
    }

    return candList;
}

void CutFlow3l::clean3lList(std::vector<ParticleMulti*>& t_3lInitList, Bool_t doJpsiCut)
{
    for(Int_t i = 0; i < (Int_t) t_3lInitList.size() && i >= 0; i++)
    {
        Bool_t keep = true;
        keep = m_cutLepComb->cutDeltaR(t_3lInitList[i]);
        if(doJpsiCut) keep &= m_cutLepComb->JPsiVeto(t_3lInitList[i]->getLepList());
        if(!keep)
        {
            t_3lInitList.erase(t_3lInitList.begin() + i);
            i--;
        }
    }
}

void CutFlow3l::cutZIsoD0(vector<ParticleMulti*>& m_3lList)
{
    for(Int_t i = 0; i < (Int_t) m_3lList.size() && i >= 0; i++)
    {
        // Iso
        m_cutLepComb->cutIsolation(m_3lList[i], true);
        // D0 cut
        m_cutLepComb->cutD0Sig(m_3lList[i], true);

        Bool_t keepCan = true;

        // Apply the is0 cut on the leading Z
        if(!m_3lList[i]->getLep(0)->getParticle()->auxdecor<int>("isoCut")
                || !m_3lList[i]->getLep(1)->getParticle()->auxdecor<int>("isoCut"))
        {
            keepCan = false;
        }
        if(keepCan) updateCutFlow(cutFlow::Iso);

        if(!m_3lList[i]->getLep(0)->getParticle()->auxdecor<int>("passD0Sig")
                || !m_3lList[i]->getLep(1)->getParticle()->auxdecor<int>("passD0Sig"))
        {
            keepCan = false;
        }
        if(keepCan) updateCutFlow(cutFlow::D0Sig);


        if(!keepCan)
        {
            m_3lList.erase(m_3lList.begin() + i);
            i--;
        }
    }
}

//// Helper
void CutFlow3l::cutFlowType(Int_t cutflowType)
{
    m_cutflowType = static_cast<ZlCutFlowType::ZlCutFlowType>(cutflowType);

    if(m_cutflowType == ZlCutFlowType::ZplusMu) m_cutFlowName = "Z + mu";
    if(m_cutflowType == ZlCutFlowType::ZplusX) m_cutFlowName = "Z + X";
    if(m_cutflowType == ZlCutFlowType::NA)
    {
        LOG(logERROR)<<"CutFlow3l - cutflow type not set";
        exit(1);
    }


}

void CutFlow3l::processMET()
{
    if(!m_metCalc)
    {
        LOG(logERROR)<<"CutFlow3l - Input MET class not given";
        exit(1);
    }


    // check if the el muons and jets were filled from outside
    if(!(m_metCalc->isElFilled() && m_metCalc->isMuFilled() && m_metCalc->isJetFilled()))
    {
        LOG(logERROR)<<"CutFlow3l - Input MET class not filled with information";
        LOG(logERROR)<<"m_metCalc->isElFilled(): "<<m_metCalc->isElFilled();
        LOG(logERROR)<<"m_metCalc->isMuFilled(): "<<m_metCalc->isMuFilled();
        LOG(logERROR)<<"m_metCalc->isJetFilled(): "<<m_metCalc->isJetFilled();
        exit(1);
    }
    m_metCalc->process();
}

// For cutflow
void CutFlow3l::initCutFlow()
{
    for(Int_t i = 0; i <= cutFlowZl::Final; i++)
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

    m_cutName[cutFlowZl::Total]             = "Total";
    m_cutName[cutFlowZl::DataPreselection]  = "DataPreselection";
    m_cutName[cutFlowZl::Preselection]      = "Preselection";
    m_cutName[cutFlowZl::Trigger]           = "Trigger";
    m_cutName[cutFlowZl::Lepton]            = "Lepton";
    m_cutName[cutFlowZl::SFOS]              = "SFOS";
    m_cutName[cutFlowZl::Kinematics]        = "Kinematics";
    m_cutName[cutFlowZl::TriggerMatch]      = "TriggerMatch";
    m_cutName[cutFlowZl::ZMass]             = "ZMass";
    m_cutName[cutFlowZl::DeltaR]            = "DeltaR";
    m_cutName[cutFlowZl::Iso]               = "LeadIso";
    m_cutName[cutFlowZl::D0Sig]             = "LeadD0Sig";
    m_cutName[cutFlowZl::MET]               = "MET";
    m_cutName[cutFlowZl::DeltaR_l]          = "DeltaR_l";
    m_cutName[cutFlowZl::Final]             = "Final";

    m_catergoryName[prodTypeSimp::njet0]    = "nJet0";
    m_catergoryName[prodTypeSimp::njet1]    = "nJet1";
    m_catergoryName[prodTypeSimp::njet2_VH] = "nJet2_VH";
    m_catergoryName[prodTypeSimp::njet2_VBF]= "nJet2_VBF";
    m_catergoryName[prodTypeSimp::leptonic] = "leptonic";
    m_catergoryName[prodTypeSimp::ttH]      = "ttH";

}


// For CutFlow
void CutFlow3l::updateCutFlow(Int_t cutLevel, Int_t valToAdd)
{
    if(m_rawCutFlow.find(m_eventCont->m_currVariation) == m_rawCutFlow.end())
    {
        LOG(logERROR)<<"CutFlow3l::updateCutFlow - requested variation is not in the map";
        LOG(logERROR)<<"Variation requested: "<<cutLevel;
        exit(1);
    }
    m_rawCutFlow[m_eventCont->m_currVariation].at(cutLevel) += valToAdd;


    // Remove the weighted cutflow for now
    //Double_t weight = 1;
    //if(cutLevel <= cutFlow::TriggerMatch) weight = m_applyWeight->getEventWeight();
    //else  weight = m_applyWeight->getTotalWeight(m_higgs);

    //m_weightCutFlow[m_eventCont->m_currVariation].at(cutLevel) += (valToAdd * weight);

}

void CutFlow3l::updateCategory(Int_t currCat, Int_t valToAdd)
{
    if(m_rawCatNumber.find(m_eventCont->m_currVariation) == m_rawCutFlow.end())
    {
        LOG(logERROR)<<"CutFlow3l::updateCategory - requested variation is not in the map";
        exit(1);
    }
    m_rawCatNumber[m_eventCont->m_currVariation].at(currCat) += valToAdd;

    // Remove the weighted cutflow for now
    //    Double_t weight = 1;
    //    weight = m_applyWeight->getTotalWeight(m_higgs);
    //    
    //    m_weightCatNumber[m_eventCont->m_currVariation].at(currCat) += (valToAdd * weight);
}


// To Print Cutflow
void CutFlow3l::printCutFlow()
{
    cout<<"-----------------------------------------"<<endl;
    cout<<"CutFlow channel: "<<m_cutFlowName<<endl;
    cout<<endl;
    cout<<setw(17)<<"CutName"<<": "<<"Raw Cutflow"<<endl;

    for(Int_t i = 0; i < (Int_t) m_cutName.size(); i++)
    {
        cout<<setw(17)<<m_cutName[i]<<": "
            <<m_rawCutFlow[m_eventCont->m_currVariation].at(i)<<endl;
        //        <<m_rawCutFlow[m_eventCont->m_currVariation].at(i)<<" - "
        //        <<m_weightCutFlow[m_eventCont->m_currVariation].at(i)<<endl;
    }
    cout<<endl;

    cout<<setw(17)<<"Production type"<<": "<<"Raw"<<endl;
    for(Int_t i = 0; i < (Int_t) m_catergoryName.size(); i++)
    {
        cout<<setw(17)<<m_catergoryName[i]<<": "
            <<m_rawCatNumber[m_eventCont->m_currVariation].at(i)<<endl;
        //        <<m_rawCatNumber[m_eventCont->m_currVariation].at(i)<<" - "
        //        <<m_weightCatNumber[m_eventCont->m_currVariation].at(i)<<endl;
    }
    cout<<endl;

    cout<<"-----------------------------------------"<<endl;

}

