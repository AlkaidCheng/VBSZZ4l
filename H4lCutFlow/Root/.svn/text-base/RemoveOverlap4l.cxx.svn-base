#include "H4lCutFlow/RemoveOverlap4l.h"
#include "AssociationUtils/OverlapRemovalDefs.h"
#include "FourMomUtils/xAODP4Helpers.h"

using namespace std;

RemoveOverlap4l::RemoveOverlap4l(EventContainer* eventcont)
{
    // Copying it for local use
    m_eventCont = eventcont;


    m_orTool = asg::AnaToolHandle<ORUtils::IOverlapRemovalTool>("OverlapRemovalTool");
    if(m_orTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"RemoveOverlap4l::RemoveOverlap4l() - cannot retrieve OverlapRemovalTool";
        exit(1);
    }

    m_muList = new xAOD::MuonContainer(SG::VIEW_ELEMENTS);
    m_elList = new xAOD::ElectronContainer(SG::VIEW_ELEMENTS);
    m_jetList = new xAOD::JetContainer(SG::VIEW_ELEMENTS);



}
RemoveOverlap4l::~RemoveOverlap4l()
{
    if(m_muList)    delete m_muList;
    if(m_elList)    delete m_elList;
    if(m_jetList)   delete m_jetList;

}
void RemoveOverlap4l::initialize()
{
    initCutFlow();
}

void RemoveOverlap4l::clearVars()
{
    m_mu_init.clear();
    m_el_init.clear();
    m_jet_init.clear();

    m_mu_list.clear();
    m_el_list.clear();
    m_jet_list.clear();


    m_af_elelOlp.clear();

    m_el_loose.clear();
    m_el_veryloose.clear();

    m_mu_final.clear();
    m_el_all_final.clear();
    m_el_L_final.clear();
    m_el_VL_final.clear();
    m_jet_final.clear();
    m_mu_ASGCaloEl.clear();
    m_mu_MET.clear();
    m_el_MET.clear();


    m_muList->clear();
    m_elList->clear();
    m_jetList->clear();

}

void RemoveOverlap4l::process()
{
    asgOverlap();
}

void RemoveOverlap4l::asgOverlap()
{
    // Start the cutflow
    updateCutFlow(m_mu_init.size(), OverlapRemoval::Initial, m_rawMuCutFlow);
    updateCutFlow(m_el_init.size(), OverlapRemoval::Initial, m_rawElCutFlow);
    updateCutFlow(m_jet_init.size(), OverlapRemoval::Initial, m_rawJetCutFlow);

    // Copy over the init vector to actually play around with
    fillVector(m_mu_init,m_mu_list);
    fillVector(m_el_init,m_el_list);
    fillVector(m_jet_init,m_jet_list);

    // Remove the overlap within the electrons
    removeElElOverlap(); // Do the overlap with the Basic electron as well
    removeMuJetOverlap(); // Remove jets that overlap with muons    
    updateCutFlow(m_mu_list.size(), OverlapRemoval::ee, m_rawMuCutFlow);
    updateCutFlow(m_el_list.size(), OverlapRemoval::ee, m_rawElCutFlow);
    updateCutFlow(m_jet_list.size(), OverlapRemoval::ee, m_rawJetCutFlow);

    // Remove: because this in the tool now
    //removesASGCaloElOverlap(); // Do the overlap with the Basic electron as well
    //updateCutFlow(m_mu_list.size(), OverlapRemoval::e_caloMuon, m_rawMuCutFlow);
    //updateCutFlow(m_el_list.size(), OverlapRemoval::e_caloMuon, m_rawElCutFlow);
    //updateCutFlow(m_jet_list.size(), OverlapRemoval::e_caloMuon, m_rawJetCutFlow);

    splitElID();

    for(Int_t i = 0; i < (Int_t) m_mu_list.size(); i++)
    {
        const xAOD::Muon *mu = dynamic_cast<const xAOD::Muon*>(m_mu_list[i]->getParticle());
        xAOD::Muon *mu_i = const_cast<xAOD::Muon*>(mu);
        mu_i->auxdata<char>("selected") = true;
        mu_i->auxdata<char>("overlaps") = 0;
        m_muList->push_back(mu_i);
    }

    for(Int_t i = 0; i < (Int_t) m_jet_init.size(); i++)
    {
        const xAOD::Jet *jet = dynamic_cast<const xAOD::Jet*>(m_jet_init[i]->getParticle());
        xAOD::Jet *jet_i = const_cast<xAOD::Jet*>(jet);
        jet_i->auxdata<char>("selected") = true;
        jet_i->auxdata<char>("overlaps") = 0;
        m_jetList->push_back(jet_i);
    }

    for(Int_t i = 0; i < (Int_t) m_el_loose.size(); i++)
    {
        const xAOD::Electron *el = dynamic_cast<const xAOD::Electron*>(m_el_loose[i]->getParticle());
        xAOD::Electron *el_i = const_cast<xAOD::Electron*>(el);
        el_i->auxdata<char>("selected") = true;
        el_i->auxdata<char>("overlaps") = 0;
        m_elList->push_back(el_i);
    }

    for(Int_t i = 0; i < (Int_t) m_el_veryloose.size(); i++)
    {
        const xAOD::Electron *el = dynamic_cast<const xAOD::Electron*>(m_el_veryloose[i]->getParticle());
        xAOD::Electron *el_i = const_cast<xAOD::Electron*>(el);
        el_i->auxdata<char>("selected") = true;
        el_i->auxdata<char>("overlaps") = 0;
        m_elList->push_back(el_i);        
    }

    fillVector(m_el_loose,m_el_MET);
    fillVector(m_mu_list,m_mu_MET);


    LOG(logDEBUG)<<"--------------- running overlap with x's --------------------------";
    m_orTool->removeOverlaps(m_elList, m_muList, m_jetList).ignore();

    fillFinalVector(m_el_loose,m_el_all_final);
    fillFinalVector(m_el_veryloose,m_el_all_final);
    fillFinalVector(m_el_loose,m_el_L_final);
    fillFinalVector(m_el_veryloose,m_el_VL_final);
    
    // Moving this to after the second call of the tool, when the X's have been turned off
    // This is to prevent the asg tool from doing calo mu - X
    //fillFinalVector(m_mu_list,m_mu_final);

    // If we have X's in the event, first turn the X 'off' and recompute the overlap again
    // This way we get a proper overlap removal of muons and jets
    for( auto electron : *( m_elList ) )
    {
        if(!electron->auxdecor<int>("looseID")) electron->auxdata<char>("selected") = false;
    }
    LOG(logDEBUG)<<"--------------- running overlap without x's --------------------------";
    m_orTool->removeOverlaps(m_elList, m_muList, m_jetList).ignore();
    fillFinalVector(m_jet_list,m_jet_final);
    fillFinalVector(m_mu_list,m_mu_final);

    updateCutFlow(m_mu_final.size(), OverlapRemoval::ASGtool, m_rawMuCutFlow);
    updateCutFlow(m_el_all_final.size(), OverlapRemoval::ASGtool, m_rawElCutFlow);
    updateCutFlow(m_jet_final.size(), OverlapRemoval::ASGtool, m_rawJetCutFlow);

}


void RemoveOverlap4l::fillFinalVector(vector<ParticleVar*>& inList, vector<ParticleVar*>& outList)
{
    // For checking the overlapping object
    static ort::objLinkAccessor_t          overlapObject("overlapObject");

    for(Int_t i = 0; i < (Int_t) inList.size(); i++)
    {
        if(inList[i]->getParticle()->auxdataConst< char >("overlaps") != 1)
            outList.push_back(inList[i]);
        else 
        {
            // If a jet overlap with a si-hit electron, keep the jet still
            if(inList[i]->getPartType() == ParticleType::Jet)
            {
                // Get the overlapping object

                const xAOD::IParticle* ip = *overlapObject(*inList[i]->getParticle());
                LOG(logDEBUG)<<"Jet overlapping with info - pT: "<<inList[i]->getParticle()->pt()
                    <<" eta: "<<inList[i]->getParticle()->eta()<<" phi: "<<inList[i]->getParticle()->phi()
                    <<" m: "<<inList[i]->getParticle()->m();

                LOG(logDEBUG)<<"Overlapping particle - pT: "<<ip->pt()
                    <<" eta: "<<ip->eta()<<" phi: "<<ip->phi()
                    <<" m: "<<ip->m();


                if(xAOD::Type::Electron == ip->type())
                {
                    // If not loose, push back the jet
                    if(!ip->auxdecor<int>("looseID")) outList.push_back(inList[i]);

                    //LOG(logDEBUG)<<"Jet info - pT: "<<inList[i]->getParticle()->pt()
                    //    <<" eta: "<<inList[i]->getParticle()->eta()<<" phi: "<<inList[i]->getParticle()->phi()
                    //    <<" m: "<<inList[i]->getParticle()->m();

                    //LOG(logDEBUG)<<"Overlapping electron - pT: "<<ip->pt()
                    //    <<" eta: "<<ip->eta()<<" phi: "<<ip->phi()
                    //    <<" m: "<<ip->m()<<" isLoose? "<<ip->auxdecor<int>("looseID");


                }

            }
        }

    }
}
void RemoveOverlap4l::fillVector(vector<ParticleVar*>& inList, vector<ParticleVar*>& outList)
{
    for(Int_t i = 0; i < (Int_t) inList.size(); i++)
    {
        outList.push_back(inList[i]);
    }
}

///////////////
// elel overlap
///////////////
// To seperate the electrons into two seperate vector as
// we don't want to do the overlap removal with very loose electrons
void RemoveOverlap4l::splitElID()
{
    for(Int_t i = 0; i < (Int_t) m_el_list.size(); i++)
    {
        if(m_el_init[i]->getPartType() != ParticleType::Electron)
        {
            LOG(logERROR)<<"RemoveOverlap4l::splitElID - Particle Type not supported";
            LOG(logERROR)<<"Particle Type: "<<m_el_list[i]->getPartType();
            exit(1);
        }

        if(m_el_list[i]->getParticle()->auxdecor<int>("looseID")) 
        {
            LOG(logDEBUG)<<"Putting electorn into loose list";
            LOG(logDEBUG)<<"el pt: "<<m_el_list[i]->getParticle()->pt()<<" ID: "<<m_el_list[i]->getParticle()->auxdecor<int>("looseID");
            m_el_loose.push_back(m_el_list[i]);
        }
        else if(m_el_list[i]->getParticle()->auxdecor<int>("veryLooseID"))
        {
            LOG(logDEBUG)<<"Putting electorn into veryloose list";
            LOG(logDEBUG)<<"el pt: "<<m_el_list[i]->getParticle()->pt()<<" ID: "<<m_el_list[i]->getParticle()->auxdecor<int>("veryLooseID");
            m_el_veryloose.push_back(m_el_list[i]);
        }
        else if(m_el_list[i]->getParticle()->auxdecor<int>("basicID"))
        {
            LOG(logDEBUG)<<"Putting electorn into veryloose list";
            LOG(logDEBUG)<<"el pt: "<<m_el_list[i]->getParticle()->pt()<<" ID: "<<m_el_list[i]->getParticle()->auxdecor<int>("basicID");
            m_el_veryloose.push_back(m_el_list[i]);
        }
    }
}


void RemoveOverlap4l::removeElElOverlap()
{
    for(Int_t i = 0; i < (Int_t) m_el_list.size(); i++)
    {
        if(m_el_list[i]->getPartType() != ParticleType::Electron)
        {
            LOG(logERROR)<<"RemoveOverlap4l::removeElElOverlap - Particle Type not supported";
            LOG(logERROR)<<"Particle Type: "<<m_el_list[i]->getPartType();
            exit(1);
        }

        bool reject = checkEETrOlp(m_el_list[i], m_el_init);
        reject = reject || checkEEClOlp(m_el_list[i], m_el_init);

        if(reject)
        {
            //LOG(logDEBUG)<<"rejecting an electron since it overlaps";
            //LOG(logDEBUG)<<"rejected electron info - pT: "<<m_el_list[i]->getParticle()->pt()
            //    <<" eta: "<<m_el_list[i]->getParticle()->eta()<<" phi: "<<m_el_list[i]->getParticle()->phi()
            //    <<" m: "<<m_el_list[i]->getParticle()->m();


            m_el_list.erase(m_el_list.begin() + i);
            i--;
        }
    }
}


void RemoveOverlap4l::removeMuJetOverlap()
{
    //LOG(logDEBUG)<<"Begin jet-mu overlap removal";
    //LOG(logDEBUG)<<"Num jets currently: "<<m_jet_list.size();

    for(Int_t i = 0; i < (Int_t) m_mu_list.size(); i++)
    {
        const xAOD::Muon *currMu = dynamic_cast<const xAOD::Muon*>(m_mu_list[i]->getParticle());

        for(Int_t j = m_jet_list.size() - 1; j >= 0; j--)
        {
            const xAOD::Jet *currJet = dynamic_cast<const xAOD::Jet*>(m_jet_list[j]->getParticle());
            float dR = xAOD::P4Helpers::deltaR(*currMu, *currJet);
            if (dR < 0.1)
            {
                LOG(logDEBUG)<<"Jet overlapping with mu, deltaR = "<<dR;
                LOG(logDEBUG)<<"Jet pt: "<<currJet->pt()<<" eta: "<<currJet->eta()<<" rapidity: "<<currJet->rapidity()<<" phi: "<<currJet->phi();
                LOG(logDEBUG)<<"muons pt: "<<currMu->pt()<<" eta: "<<currMu->eta()<<" rapidity: "<<currMu->rapidity()<<" phi: "<<currMu->phi();
                m_jet_list.erase(m_jet_list.begin() + j);
            }
        }
    }

    //LOG(logDEBUG)<<"End of jet-mu overlap removal";
    //LOG(logDEBUG)<<"Num jets after removal: "<<m_jet_list.size();
    for (auto jet : m_jet_list)
    {
        for (auto mu : m_mu_list)
        {
            const xAOD::Muon *currMu = dynamic_cast<const xAOD::Muon*>(mu->getParticle());
            const xAOD::Jet *currJet = dynamic_cast<const xAOD::Jet*>(jet->getParticle());
            float dR = xAOD::P4Helpers::deltaR(*currMu, *currJet);
            //LOG(logDEBUG)<<"deltaR = "<<dR;
        }
    }
}



Bool_t RemoveOverlap4l::checkEETrOlp(ParticleVar* currElectron, vector<ParticleVar*>& inList)
{
    for(Int_t i = 0; i < (Int_t) inList.size(); i++)
    {
        // Don't want to compare the same thing
        if(currElectron == inList[i]) continue;

        if(elTrackOlp(currElectron, inList[i]))
        {
            LOG(logDEBUG)<<"Track overlap for el pT: "<<currElectron->getParticle()->pt()<<" with electron pT: "<<inList[i]->getParticle()->pt();
            return true;
        }
    }

    return false;
}

Bool_t RemoveOverlap4l::checkEEClOlp(ParticleVar* currElectron, vector<ParticleVar*>& inList)
{
    for(Int_t i = 0; i < (Int_t) inList.size(); i++)
    {
        // Don't want to compare the same thing
        if(currElectron == inList[i]) continue;

        if(elClusOlp(currElectron, inList[i])) 
        {
            LOG(logDEBUG)<<"Cluster overlap for el pT: "<<currElectron->getParticle()->pt()<<" with electron pT: "<<inList[i]->getParticle()->pt();
            return true;
        }

    }

    return false;
}

// Electron track overlap
Bool_t RemoveOverlap4l::elTrackOlp(ParticleVar* el1, ParticleVar* el2)
{
    // Getting the Current Variables
    Double_t Et_curr    = -1;

    const xAOD::Electron *currEl = dynamic_cast<const xAOD::Electron*>(el1->getParticle());
    const xAOD::TrackParticle* currElTrack = xAOD::EgammaHelpers::getOriginalTrackParticleFromGSF(currEl->trackParticle());

    Et_curr     = currEl->pt();


    const xAOD::Electron *el_i = dynamic_cast<const xAOD::Electron*>(el2->getParticle());
    const xAOD::TrackParticle* el_iTrack = xAOD::EgammaHelpers::getOriginalTrackParticleFromGSF(el_i->trackParticle());
    /// For the electron to compare
    Double_t Et_j = -1;

    Et_j     = el_i->pt();

    // Comparing they share the same ID and if the curr has lower ET, reject it
    if( currElTrack == el_iTrack &&
            Et_curr < Et_j
      ) return true;


    return false;
}

// Electron cluster overlap
Bool_t RemoveOverlap4l::elClusOlp(ParticleVar* el1, ParticleVar* el2)
{
    Double_t phi_curr = -1;
    Double_t eta_curr = -1;
    Double_t eta_track_curr = -1;
    Double_t Et_curr = -1;

    Double_t cutPhi = -1;
    Double_t cutEta = -1;

    // 2012 cutValue
    cutPhi = 5*0.025;
    cutEta = 3*0.025;

    const xAOD::Electron *currEl = dynamic_cast<const xAOD::Electron*>(el1->getParticle());

    phi_curr        = currEl->caloCluster()->phi();
    eta_curr        = currEl->caloCluster()->eta();
    eta_track_curr  = currEl->trackParticle()->eta();
    Et_curr         = currEl->pt();

    const xAOD::Electron *el_i = dynamic_cast<const xAOD::Electron*>(el2->getParticle());

    /// For the electron to compare
    Double_t phi_j          = el_i->caloCluster()->phi();
    Double_t eta_j          = el_i->caloCluster()->eta();
    Double_t Et_j           = el_i->pt();

    Double_t deltaEta = fabs(eta_curr - eta_j);
    Double_t deltaPhi = fabs(phi_curr - phi_j);
    deltaPhi = (deltaPhi > TMath::Pi()) ? 2*TMath::Pi()-deltaPhi : deltaPhi;

    //LOG(logDEBUG)<<"curr EL: "<<currEl->pt()<<" eta_curr: "<<eta_curr<<" phi_curr: "<<phi_curr;
    //LOG(logDEBUG)<<"curr EL: "<<el_i->pt()<<" eta_j: "<<eta_j<<" phi_j: "<<phi_j;
    //LOG(logDEBUG)<<"curr EL: "<<currEl->pt()<<" checkEl: "<<el_i->pt()<<" deltaEta: "<<deltaEta<<" deltaPhi: "<<deltaPhi;
    // Comparing they share the same ID and if the curr has lower ET, reject it
    if( deltaEta < cutEta &&
            deltaPhi < cutPhi &&
            Et_curr < Et_j
      ) return true;

    return false;
}


///////////////
// el-mu overlap
///////////////
void RemoveOverlap4l::removesASGCaloElOverlap()
{
    // Calo muon electron overlap
    for(Int_t i = 0; i < (Int_t) m_mu_list.size(); i++)
    {
        const xAOD::Muon *mu = dynamic_cast<const xAOD::Muon*>(m_mu_list[i]->getParticle());

        if(mu->muonType() == xAOD::Muon::CaloTagged)
        {
            LOG(logDEBUG)<<"Checking mu: "<<m_mu_list[i]->getParticle()->pt()<<" el_list size: "<<m_el_list.size();            
            if(checkCaloMuElOlpASG(m_mu_list[i], m_el_list))
            {
                LOG(logDEBUG)<<"Found muon overlap with electron";
                LOG(logDEBUG)<<"Rejecting mu: "<<m_mu_list[i]->getParticle()->pt();
                // Remove from the list if it is rejected
                m_mu_list.erase(m_mu_list.begin() + i);
                i--;
            }
        }
    }
}

Bool_t RemoveOverlap4l::checkCaloMuElOlpASG(ParticleVar* currMuon, vector<ParticleVar*>& inList)
{

    const xAOD::Muon *currMu = dynamic_cast<const xAOD::Muon*>(currMuon->getParticle());

    const xAOD::TrackParticle* checkMuTrk =
        currMu->trackParticle(xAOD::Muon::InnerDetectorTrackParticle);

    Double_t mu_eta = -TMath::Log(TMath::Tan(checkMuTrk->theta()*0.5));
    Double_t mu_phi = checkMuTrk->phi();

    // Looping over to find it there is an overlap electron
    for(Int_t i = 0; i < (Int_t) inList.size(); i++)
    {
        Double_t el_eta = -1;
        Double_t el_phi = -1;

        const xAOD::Electron *el_i = dynamic_cast<const xAOD::Electron*>(inList[i]->getParticle());
        const xAOD::TrackParticle* elGSFTrack = xAOD::EgammaHelpers::getOriginalTrackParticleFromGSF(el_i->trackParticle());
        el_phi  = elGSFTrack->phi();
        el_eta  = elGSFTrack->eta();

        LOG(logDEBUG)<<"Mu eta: "<<mu_eta<<" phi: "<<mu_phi<<" el eta: "<<el_eta<<" phi: "<<el_phi<<" mu track: "<<checkMuTrk<<" el track: "<<elGSFTrack;

        // If the electron is just basic ID, then don't reject the calo muon
        if(!el_i->auxdecor<int>("looseID")) continue;


        //if(DeltaR(mu_eta, mu_phi, el_eta, el_phi) < 0.02) {return true;}
        if(checkMuTrk == elGSFTrack) return true;
    }

    return false;
}


// To compute Delta R - static function, can be used anywhere
Double_t RemoveOverlap4l::DeltaR (Double_t eta_1, Double_t phi_1, Double_t eta_2, Double_t phi_2)
{
    Double_t dR=0;
    Double_t eta2 = (eta_1-eta_2)*(eta_1-eta_2);
    Double_t tmp_dphi = (fabs(phi_1-phi_2) > TMath::Pi()) ? 2*TMath::Pi()-fabs(phi_1-phi_2) : fabs(phi_1-phi_2);
    Double_t phi2 = tmp_dphi*tmp_dphi;
    dR = sqrt( eta2 + phi2 );
    return dR;
}


// To compute the xJet overlap
vector<ParticleVar*> RemoveOverlap4l::xJetOverlap(LepCombBase* combLep, const vector<ParticleVar*>& jetVect)
{
    vector<ParticleVar*> overlapRemovedJet;

    for(auto part: jetVect)
    {
        bool isOverlapped = false;
        for(Int_t i = 0; i < (Int_t) combLep->getLepSize(); i++)
        {
            if(combLep->getLep(i)->getPartType() == ParticleType::Electron)
            {
                if(!combLep->getLep(i)->getParticle()->auxdecor<int>("looseID"))
                {
                    float dR = xAOD::P4Helpers::deltaR(*part->getParticle(), *combLep->getLep(i)->getParticle());
                    if(dR < 0.2) {
                        LOG(logDEBUG)<<"------------------------------------------------------------------------------------------";
                        LOG(logDEBUG)<<"FOUND OVERLAPPING JET";
                        LOG(logDEBUG)<<"curr El: "<<combLep->getLep(i)->getParticle()->pt()<<" curr Jet: "<<part->getParticle()->pt()<<" dR: "<<dR;
                        isOverlapped = true; }
                }
            }
            if(isOverlapped) break;
        }

        if(!isOverlapped) overlapRemovedJet.push_back(part);
    }

    return overlapRemovedJet;
}




// For cutflow counting
void RemoveOverlap4l::initCutFlow()
{
    cout<<"RemoveOverlap4l init cutflow"<<endl;

    for(Int_t i = 0; i <= OverlapRemoval::ASGtool; i++)
    {
        m_cutName.push_back("");
    }

    for (auto sysListItr:m_eventCont->m_sysList)
    {
        m_rawMuCutFlow[sysListItr].reserve(m_cutName.size());
        m_rawElCutFlow[sysListItr].reserve(m_cutName.size());
        m_rawJetCutFlow[sysListItr].reserve(m_cutName.size());

        for(Int_t i = 0; i < (Int_t) m_cutName.size(); i++)
        {
            m_rawMuCutFlow[sysListItr].push_back(0);
            m_rawElCutFlow[sysListItr].push_back(0);
            m_rawJetCutFlow[sysListItr].push_back(0);
        }
    }

    m_cutName[OverlapRemoval::Initial]      = "Total";
    m_cutName[OverlapRemoval::ee]           = "ee";
    m_cutName[OverlapRemoval::e_caloMuon]   = "e_caloMuon";
    m_cutName[OverlapRemoval::ASGtool]      = "ASGtool";


}

void RemoveOverlap4l::updateCutFlow(Int_t valToAdd, Int_t cutLevel, map<CP::SystematicSet, vector<Int_t>>& m_rawCutFlow)
{
    if(m_rawCutFlow.find(m_eventCont->m_currVariation) == m_rawCutFlow.end())
    {
        LOG(logERROR)<<"RemoveOverlap4l::updateCutFlow - requested variation is not in the map";
        exit(1);
    }
    m_rawCutFlow[m_eventCont->m_currVariation].at(cutLevel) += valToAdd;
}

void RemoveOverlap4l::printCutFlow()
{
    cout<<"-----------------------------------------"<<endl;
    cout<<"Overlap Removal"<<endl;
    cout<<"CutName: \t Muons \t Electrons \t Jets"<<endl;
    cout<<endl;
    for(Int_t i = 0; i < (Int_t) m_cutName.size(); i++)
    {
        cout<<setw(11)<<m_cutName.at(i)<<": "
            <<"\t"<<m_rawMuCutFlow[m_eventCont->m_currVariation].at(i)
            <<"\t"<<m_rawElCutFlow[m_eventCont->m_currVariation].at(i)
            <<"\t"<<m_rawJetCutFlow[m_eventCont->m_currVariation].at(i)<<endl;
    }
    cout<<endl;
    cout<<"-----------------------------------------"<<endl;

}
