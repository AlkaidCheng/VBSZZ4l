#include "H4lCutFlow/CutLepComb.h"

#include <algorithm>    // std::find
#include <set>

using namespace std;

CutLepComb::CutLepComb(EventContainer* eventcont)
{
    // Copying it for local use
    m_eventCont = eventcont;

    // Standard PT cuts
    m_pT1CutVal = 20 * 1000;
    m_pT2CutVal = 15 * 1000;
    m_pT3CutVal = 10 * 1000;

    // mZ1 cuts
    m_mZ1LwrCutVal = 50 * 1000;
    m_mZ1UprCutVal = 106 * 1000;

    // mZ2 cuts
    m_nBinMZ2Cut = 2;
    m_massMZ2Cut = new Double_t[m_nBinMZ2Cut];
    m_cutMZ2Cut = new Double_t[m_nBinMZ2Cut];

    m_massMZ2Cut[0] = 140 * 1000;
    m_massMZ2Cut[1] = 190 * 1000;

    m_cutMZ2Cut[0] = 12 * 1000;
    m_cutMZ2Cut[1] = 50 * 1000;

    m_mZ2UprCutVal = 115 * 1000;

    //////////////////////
    //// SM test values

    //// mZ1 cuts
    //m_mZ1LwrCutVal = 66 * 1000;
    //m_mZ1UprCutVal = 116 * 1000;

    //// mZ2 cuts
    //m_nBinMZ2Cut = 2;
    //m_massMZ2Cut = new Double_t[m_nBinMZ2Cut];
    //m_cutMZ2Cut = new Double_t[m_nBinMZ2Cut];

    //m_massMZ2Cut[0] = 140 * 1000;
    //m_massMZ2Cut[1] = 190 * 1000;

    //m_cutMZ2Cut[0] = 66 * 1000;
    //m_cutMZ2Cut[1] = 66 * 1000;

    //m_mZ2UprCutVal = 116 * 1000;
    //////////////////////


    // Delta R cut
    m_SFdRCut = 0.10;
    m_OFdRCut = 0.20;

    // JPsi cut
    m_JPsiVetoVal = 5 * 1000;

    // D0 significance cut
    m_muD0SigCut = 3;
    m_elD0SigCut = 5;

    // Vertex cut
    m_4mVrtCut = 6;
    m_4e_2l2l_VrtCut = 9;


    // For trigger matching
    m_isoTool = ToolHandle<CP::IIsolationSelectionTool>("isoTool");
    if(m_isoTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutLepComb::CutLepComb() - cannot retrieve IIsolationSelectionTool";
        exit(1);
    }
    m_isoSelMu = ToolHandle<CP::IIsolationCloseByCorrectionTool>("isoSelMu");
    if(m_isoSelMu.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutLepComb::CutLepComb() - cannot retrieve IIsolationCloseByCorrectionTool";
        exit(1);
    }

    m_isoSelEl = ToolHandle<CP::IIsolationCloseByCorrectionTool>("isoSelEl");
    if(m_isoSelEl.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutLepComb::CutLepComb() - cannot retrieve IIsolationCloseByCorrectionTool";
        exit(1);
    }

    m_isoCorrTool = ToolHandle<CP::IIsolationCorrectionTool>("isoCorrTool");
    if(m_isoCorrTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutLepComb::CutLepComb() - cannot retrieve IIsolationCorrectionTool";
        exit(1);
    }
    m_isotypes.push_back(xAOD::Iso::IsolationType::ptvarcone30);
    m_isotypes.push_back(xAOD::Iso::IsolationType::ptvarcone20);
    m_isotypes.push_back(xAOD::Iso::IsolationType::topoetcone20);
    m_isotypesString.push_back("corr_ptvarcone30");
    m_isotypesString.push_back("corr_ptvarcone20");
    m_isotypesString.push_back("corr_topoetcone20");

    m_trigger = 0;

    m_doTriggerMatch = false;

}

CutLepComb::~CutLepComb()
{
    delete m_massMZ2Cut;
    delete m_cutMZ2Cut;
}

// kinematic cut on the leptons in the quad
Bool_t CutLepComb::cutKinematic(const LepCombBase* currComb) const
{
    
    Int_t pT1Cut = 0;
    Int_t pT2Cut = 0;
    Int_t pT3Cut = 0;
    for(Int_t i = 0; i < currComb->getLepSize(); i++)
    {
        if(currComb->getLep(i)->getTLV().Pt() > m_pT1CutVal) pT1Cut++;
        if(currComb->getLep(i)->getTLV().Pt() > m_pT2CutVal) pT2Cut++;
        if(currComb->getLep(i)->getTLV().Pt() > m_pT3CutVal) pT3Cut++;
    }

    // For 4l quads
    if(currComb->getLepSize() == 4 && pT1Cut >= 1 && pT2Cut >= 2 && pT3Cut >= 3) return true;

    // For 2l quads
    if(currComb->getLepSize() == 2 && pT1Cut >= 1 && pT2Cut >= 2 ) return true;
    
   
    /*
    // For HM test
    double t_pT1CutVal = m_pT1CutVal;
    double t_pT2CutVal = m_pT2CutVal;
    double t_pT3CutVal = m_pT3CutVal;
    double t_pT4CutVal = 0;

    const ParticleQuadlepton* quad = dynamic_cast<const ParticleQuadlepton*>(currComb);
    if(!quad) return false;

    double m4l = quad->getTLV().M()/1000;

    if(m4l > 200)
    {
        t_pT1CutVal = (0.18125*m4l-16.25) * 1000;
        t_pT2CutVal = (0.125*m4l-25) * 1000;
        t_pT3CutVal = (0.06875*m4l-13.75) * 1000;
        t_pT4CutVal = (0.06875*m4l-13.75) * 1000;
    }
    if(m4l > 1000)
    {
        t_pT1CutVal = 165 * 1000;
        t_pT2CutVal = 100 * 1000;
        t_pT3CutVal = 55 * 1000;
        t_pT4CutVal = 55 * 1000;
    }

    Int_t pT1Cut = 0;
    Int_t pT2Cut = 0;
    Int_t pT3Cut = 0;
    Int_t pT4Cut = 0;
    for(Int_t i = 0; i < currComb->getLepSize(); i++)
    {
        if(currComb->getLep(i)->getTLV().Pt() > t_pT1CutVal) pT1Cut++;
        if(currComb->getLep(i)->getTLV().Pt() > t_pT2CutVal) pT2Cut++;
        if(currComb->getLep(i)->getTLV().Pt() > t_pT3CutVal) pT3Cut++;
        if(currComb->getLep(i)->getTLV().Pt() > t_pT4CutVal) pT4Cut++;
    }

    // For 4l quads
    if(currComb->getLepSize() == 4 && pT1Cut >= 1 && pT2Cut >= 2 && pT3Cut >= 3  && pT4Cut >= 4) return true;
    */
    
    return false;
}

// TODO trigger match the leptons in the quad
Bool_t CutLepComb::cutTrigMatch(const LepCombBase* currComb) const
{
    if(m_trigger == 0)
    {
        LOG(logERROR) <<"CutLepComb::cutTrigMatch() - CutEventTrigger not specified";
        exit(1);
    }

    if(!m_doTriggerMatch) return true;

    // Return true if any of the triggers match
    if(matchSingleMu(currComb)) return true;
    if(matchSingleEl(currComb)) return true;

    if(matchDiMu(currComb)) return true;
    //if(matchDiEl(currComb)) return true;

    //if(matchElMu(currComb)) return true;

    //if(matchTriMu(currComb)) return true;
    //if(matchTriEl(currComb)) return true;

    return false;
}


Bool_t CutLepComb::matchSingleMu(const LepCombBase* ) const
{
    if(!m_trigger->singleMuonTrigger()) return false;
    return false;
}

Bool_t CutLepComb::matchDiMu(const LepCombBase* ) const
{
    if(!m_trigger->diMuonTrigger()) return false;
    return false;
}

Bool_t CutLepComb::matchTriMu(const LepCombBase* ) const
{
    if(!m_trigger->triMuonTrigger()) return false;
    return true;
}

Bool_t CutLepComb::matchSingleEl(const LepCombBase* ) const
{
    if(!m_trigger->singleElectronTrigger()) return false;
    return false;
}
Bool_t CutLepComb::matchDiEl(const LepCombBase* ) const
{
    if(!m_trigger->diElectronTrigger()) return false;
    return true;
}
Bool_t CutLepComb::matchTriEl(const LepCombBase* ) const
{
    if(!m_trigger->triElectronTrigger()) return false;
    return true;
}

Bool_t CutLepComb::matchElMu(const LepCombBase* ) const
{
    if(!m_trigger->elMuTrigger()) return false;
    return true;
}



// mZ1 cut for quad leptons
Bool_t CutLepComb::cutMZ1(const ParticleQuadlepton* currQuad) const
{
    Double_t currZ1M = currQuad->getZ1()->getTLV().M();

    if(currZ1M > m_mZ1LwrCutVal && currZ1M < m_mZ1UprCutVal) return true;

    return false;
}

// mZ2 cut for quad leptons
Bool_t CutLepComb::cutMZ2(const ParticleQuadlepton* currQuad) const
{

    Double_t currM4l = currQuad->getTLV().M();
    Double_t currMZ2 = currQuad->getZ2()->getTLV().M();

    Double_t z2CutVal = 0;
    Int_t index = -1;

    for(Int_t i = 0; i < m_nBinMZ2Cut; i++)
    {
        if(currM4l > m_massMZ2Cut[i]) index = i;
    }

    if(index == -1) z2CutVal = m_cutMZ2Cut[0];
    else if (index == (m_nBinMZ2Cut - 1)) z2CutVal = m_cutMZ2Cut[(m_nBinMZ2Cut - 1)];
    else z2CutVal = m_cutMZ2Cut[index] + (currM4l - m_massMZ2Cut[index]) * (m_cutMZ2Cut[index+1] - m_cutMZ2Cut[index])/(m_massMZ2Cut[index+1] - m_massMZ2Cut[index]);


    if(currMZ2 > z2CutVal && currMZ2 < m_mZ2UprCutVal) return true;


    return false;
}


// Delta R cut
// Just a simple interface
Bool_t CutLepComb::cutDeltaR(const LepCombBase* currComb) const
{
    vector<ParticleVar*> vecLep;
    for(Int_t i = 0; i < currComb->getLepSize(); i++)
    {
        vecLep.push_back(currComb->getLep(i));
    }

    Bool_t passCut = cutDeltaR(vecLep);

    vecLep.clear();

    return passCut;
}

// Delta R cut
Bool_t CutLepComb::cutDeltaR(const vector<ParticleVar*>& vecLep) const
{
    for(Int_t i = 0; i < (Int_t) vecLep.size(); i++)
    {
        for(Int_t j = i+1; j < (Int_t) vecLep.size(); j++)
        {
            if(i == j) continue;

            Double_t cutVal = -1;

            if((vecLep[i]->getPartType() == ParticleType::Truth) && (vecLep[j]->getPartType() == ParticleType::Truth)) {
                if(abs(vecLep[i]->getTruthPID()) == abs(vecLep[j]->getTruthPID())) cutVal = m_SFdRCut;
                else cutVal = m_OFdRCut;
            }
            else {
                if(vecLep[i]->getPartType() == vecLep[j]->getPartType()) cutVal = m_SFdRCut;
                else cutVal = m_OFdRCut;
            }

            Double_t currDeltaR = vecLep[i]->getTLV().DeltaR(vecLep[j]->getTLV());


            //LOG(logDEBUG)<<"DeltaR Cut - Lep i pT: "<<vecLep[i]->getParticle()->pt()
            //<<" Lep j pT: "<<vecLep[j]->getParticle()->pt()
            //<<" deltaR cut val: "<<cutVal
            //<<" computed DeltaR: "<<currDeltaR
            //<<" reject? "<<(currDeltaR < cutVal);

            if(currDeltaR < cutVal) return false;
        }
    }

    return true;
}


// Delta R cut
Bool_t CutLepComb::JPsiVeto(const ParticleQuadlepton* currQuad) const
{
    vector<ParticleVar*> vecLep;
    for(Int_t i = 0; i < currQuad->getLepSize(); i++)
    {
        vecLep.push_back(currQuad->getLep(i));
    }

    Bool_t passCut = JPsiVeto(vecLep);

    vecLep.clear();

    return passCut;
}

Bool_t CutLepComb::JPsiVeto(const std::vector<ParticleVar*>& vecLep) const
{
    for(size_t i = 0; i < vecLep.size(); i++)
    {
        for (size_t j = i+1; j < vecLep.size(); j++)
        {
            if(vecLep[i] == vecLep[j]) continue;
            // Want the same flavour
            if(vecLep[i]->getPartType() == ParticleType::Truth && vecLep[j]->getPartType() == ParticleType::Truth) {
                if(abs(vecLep[i]->getTruthPID()) != abs(vecLep[j]->getTruthPID())) continue;
            }
            else if(vecLep[i]->getPartType() != vecLep[j]->getPartType()) continue;
            // want opposite charge
            if((vecLep[i]->getCharge() + vecLep[j]->getCharge()) != 0) continue;

            // Now calculate the mass
            TLorentzVector tlv = vecLep[i]->getTLV() + vecLep[j]->getTLV();

            //LOG(logDEBUG)<<"Jpsi Cut - Lep i pT: "<<vecLep[i]->getParticle()->pt()
            //<<" Lep j pT: "<<vecLep[j]->getParticle()->pt()
            //<<" computed Mass: "<<tlv.M()
            //<<" reject? "<<(tlv.M() < m_JPsiVetoVal);
            if(tlv.M() < m_JPsiVetoVal) return false;
        }
    }

    return true;
}


// Isolation cut
Bool_t CutLepComb::cutIsolation(const LepCombBase* currComb, bool preventDebug) const
{
    vector<ParticleVar*> vecLep;
    for(Int_t i = 0; i < currComb->getLepSize(); i++)
    {
        vecLep.push_back(currComb->getLep(i));
    }

    Bool_t passCut = cutIsolation(vecLep, preventDebug);

    vecLep.clear();

    return passCut;
}

Bool_t CutLepComb::cutIsolation(const std::vector<ParticleVar*>& vecLep, bool preventDebug) const
{

    decorateCorrectIso(vecLep);

    vector<const xAOD::IParticle*> iParticleVec;
    for(size_t i = 0; i < vecLep.size(); i++)
    {
        iParticleVec.push_back(vecLep[i]->getParticle());
    }

    Bool_t passCut = true;
    for(size_t i = 0; i < vecLep.size(); i++)
    {
        Bool_t passCutCurr = true;
        if(vecLep[i]->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron *currEl = dynamic_cast<const xAOD::Electron*>(vecLep[i]->getParticle());
            const xAOD::IParticle *currPar = dynamic_cast<const xAOD::IParticle*>(vecLep[i]->getParticle());

            CP::IIsolationCloseByCorrectionTool* isoSelEl = const_cast<CP::IIsolationCloseByCorrectionTool*>(&(*(m_isoSelEl)));
            //passCutCurr = m_isoTool->accept(*currEl);
            passCutCurr = m_isoSelEl->acceptCorrected(*currEl, iParticleVec);
            currEl->auxdecor< int >( "isoCut" ) = passCutCurr;

            float ptvarcone = -1;
            float topoetcone = -1;

            currEl->isolation(ptvarcone,xAOD::Iso::ptvarcone20);
            currEl->isolation(topoetcone,xAOD::Iso::topoetcone20);

            if(!preventDebug) LOG(logDEBUG)<<"Particle El i: "<<i<<" track Iso: "<<ptvarcone/currEl->pt()<<" calo Iso: "<<topoetcone/currEl->pt()<<" pass: "<<passCutCurr;
        }
        else if(vecLep[i]->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon *currMuon = dynamic_cast<const xAOD::Muon*>(vecLep[i]->getParticle());
            const xAOD::IParticle *currPar = dynamic_cast<const xAOD::IParticle*>(vecLep[i]->getParticle());

            CP::IIsolationCloseByCorrectionTool* isoSelMu = const_cast<CP::IIsolationCloseByCorrectionTool*>(&(*(m_isoSelMu)));
            //passCutCurr = m_isoTool->accept(*currMuon);            
            passCutCurr = m_isoSelMu->acceptCorrected(*currMuon, iParticleVec);

            currMuon->auxdecor< int >( "isoCut" ) = passCutCurr;

            float ptvarcone = -1;
            float topoetcone = -1;

            currMuon->isolation(ptvarcone,xAOD::Iso::ptvarcone30);
            currMuon->isolation(topoetcone,xAOD::Iso::topoetcone20);

            if(!preventDebug) LOG(logDEBUG)<<"Particle Mu i: "<<i<<" track Iso: "<<ptvarcone/currMuon->pt()<<" calo Iso: "<<topoetcone/currMuon->pt()<<" pass: "<<passCutCurr;

        }
        passCut = passCut && passCutCurr;
    }
    iParticleVec.clear();

    return passCut;
}
void CutLepComb::decorateCorrectIso(const std::vector<ParticleVar*>& vecLep) const
{
    vector<const xAOD::IParticle*> iParticleVec;
    for(size_t i = 0; i < vecLep.size(); i++)
    {
        iParticleVec.push_back(vecLep[i]->getParticle());
    }

    // Isolation leakge correction
    for(size_t i = 0; i < vecLep.size(); i++)
    {
        if(vecLep[i]->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron *currEl = dynamic_cast<const xAOD::Electron*>(vecLep[i]->getParticle());
            const xAOD::Egamma *currEgam = dynamic_cast<const xAOD::Egamma*>(vecLep[i]->getParticle());
            xAOD::Electron *el = const_cast<xAOD::Electron*>(currEl);
            xAOD::Egamma *egam = const_cast<xAOD::Egamma*>(currEgam);

            //m_isoCorrTool = ToolHandle<CP::IIsolationCorrectionTool>("isoCorrTool");

            CP::IIsolationCorrectionTool* isoCorrTool = const_cast<CP::IIsolationCorrectionTool*>(&(*(m_isoCorrTool)));
            // Apply leakage correction 
            if(!isoCorrTool->applyCorrection(*egam))
            {
                LOG(logERROR)<<"Cannot apply isolation leakage correction";
                exit(1);
            }
        }
    }



    float orgIso [3];
    orgIso[0] = -999;
    orgIso[1] = -999;
    orgIso[2] = -999;

    for(size_t i = 0; i < vecLep.size(); i++)
    {
        if(vecLep[i]->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron *currEl = dynamic_cast<const xAOD::Electron*>(vecLep[i]->getParticle());
            vector<Float_t> removals = {0, 0, 0};

            m_isoSelEl->getCloseByCorrection(removals, *currEl, m_isotypes, iParticleVec).ignore();

            for(size_t j = 0; j < m_isotypes.size(); j++)
            {
                currEl->isolation(orgIso[j], m_isotypes[j]);
                currEl->auxdecor< float >(m_isotypesString[j]) = orgIso[j] - removals[j];
            }
        }
        else if(vecLep[i]->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon *currMuon = dynamic_cast<const xAOD::Muon*>(vecLep[i]->getParticle());
            vector<Float_t> removals = {0, 0, 0};
            m_isoSelMu->getCloseByCorrection(removals, *currMuon, m_isotypes, iParticleVec).ignore();

            for(size_t j = 0; j < m_isotypes.size(); j++)
            {
                currMuon->isolation(orgIso[j], m_isotypes[j]);
                currMuon->auxdecor< float >(m_isotypesString[j]) = orgIso[j] - removals[j];
            }


        }
    }

    iParticleVec.clear();
}

Bool_t CutLepComb::cutD0Sig(const LepCombBase* currComb, bool preventDebug) const
{
    vector<ParticleVar*> vecLep;
    for(Int_t i = 0; i < currComb->getLepSize(); i++)
    {
        vecLep.push_back(currComb->getLep(i));
    }

    Bool_t passCut = cutD0Sig(vecLep, preventDebug);

    vecLep.clear();

    return passCut;
}


// D0 Significance
Bool_t CutLepComb::cutD0Sig(const std::vector<ParticleVar*>& vecLep, bool preventDebug) const
{
    Bool_t passCut = true;

    // Actual Cuts
    for(Int_t i = 0; i < (Int_t) vecLep.size(); i++)
    {
        vecLep[i]->getParticle()->auxdecor< int >( "passD0Sig" ) = 0;
        if(vecLep[i]->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron *currEl = dynamic_cast<const xAOD::Electron*>(vecLep[i]->getParticle());

            Double_t currSig = xAOD::TrackingHelpers::d0significance( currEl->trackParticle(), 
                    m_eventCont->eventInfo->beamPosSigmaX(), 
                    m_eventCont->eventInfo->beamPosSigmaY(),
                    m_eventCont->eventInfo->beamPosSigmaXY() );

            vecLep[i]->getParticle()->auxdecor< float >("d0sig") = currSig;

            if(fabs(currSig) > m_elD0SigCut){ passCut =  passCut & false;}
            else { vecLep[i]->getParticle()->auxdecor< int >( "passD0Sig" ) = 1;}
            //if(!preventDebug) LOG(logDEBUG)<<"Particle El i: "<<i
            //<<" d0 Sig: "<<vecLep[i]->getParticle()->auxdecor< float >("d0sig")
            //<<" decision: "<<vecLep[i]->getParticle()->auxdecor< int >( "passD0Sig" );

        }
        else if(vecLep[i]->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon *currMuon = dynamic_cast<const xAOD::Muon*>(vecLep[i]->getParticle());

            Double_t currSig = xAOD::TrackingHelpers::d0significance( currMuon->primaryTrackParticle(), 
                    m_eventCont->eventInfo->beamPosSigmaX(), 
                    m_eventCont->eventInfo->beamPosSigmaY(), 
                    m_eventCont->eventInfo->beamPosSigmaXY() );

            vecLep[i]->getParticle()->auxdecor< float >("d0sig") = currSig;

            if(fabs(currSig) > m_muD0SigCut){ passCut =  passCut & false;}
            else { vecLep[i]->getParticle()->auxdecor< int >( "passD0Sig" ) = 1;}
            //if(!preventDebug) LOG(logDEBUG)<<"Particle Mu i: "<<i
            //<<" d0 Sig: "<<vecLep[i]->getParticle()->auxdecor< float >("d0sig")
            //<<" decision: "<<vecLep[i]->getParticle()->auxdecor< int >( "passD0Sig" );

        }
    }

    return passCut;
}


// Vertex cut helper
double CutLepComb::getVertexQuality(const ParticleQuadlepton* currQuad) const
{
    vector<const xAOD::TrackParticle*> trackParticles;

    // Save the track particles for easier looping
    for(int i = 0; i < 4; i++)
    {
        const xAOD::TrackParticle* tp=0;

        if(currQuad->getLep(i)->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron *currEl = dynamic_cast<const xAOD::Electron*>(currQuad->getLep(i)->getParticle());
            tp = currEl->trackParticle();
        }
        else if(currQuad->getLep(i)->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon *currMuon = dynamic_cast<const xAOD::Muon*>(currQuad->getLep(i)->getParticle());
            tp = currMuon->trackParticle(xAOD::Muon::InnerDetectorTrackParticle);
        }
        if(tp) trackParticles.push_back(tp);
    }

    // retrieve the container
    const xAOD::VertexContainer* fourLVertexCont = 0;
    if (m_eventCont->getEvent()->contains<xAOD::VertexContainer>("FourLeptonVertices")) {
        m_eventCont->getEvent()->retrieve(fourLVertexCont,"FourLeptonVertices").ignore();
    }

    if(!fourLVertexCont)
    {
        // if AOD, return nicely
        if(m_eventCont->m_isAOD)
        {
            return 0;
        }
                

        LOG(logERROR)<<"CutLepComb::getVertexQuality - no vertex information";
        exit(1);
    }
    
    int nTracks = trackParticles.size();
    const xAOD::Vertex* vert = 0;


    //LOG(logDEBUG)<<"Vertex Cut";
    //for(int i = 0; i <trackParticles.size(); i++)
    //{
    //    LOG(logDEBUG)<<"track i: "<<i<<" pT: "<<trackParticles[i]->pt()<<" eta: "<<trackParticles[i]->eta();
    //}
    //int count = 0;
    //// Look at each vertex to get the right one
    //for(const auto v: *fourLVertexCont)
    //{
    //    LOG(logDEBUG)<<"Cand vert "<<count<<" chi2ndf: "<<v->chiSquared()/v->numberDoF();
    //    for(int i = 0; i < nTracks; i++)
    //    {
    //        LOG(logDEBUG)<<"Candidate track i: "<<i<<" pT: "<<v->trackParticle(i)->pt()<<" eta: "<<v->trackParticle(i)->eta();
    //    }
    //    count++;
    //}



    // Look at each vertex to get the right one
    for(const auto v: *fourLVertexCont)
    {
        int nMatch = 0;        
        if(!v) continue;

        // if the vertex doesn't have the same tracks as quadlepton, continue;
        if(v->nTrackParticles() != nTracks) continue;

        // Create a set of vertex tracks
        set<const xAOD::TrackParticle*> vtxTrks;
        for (unsigned int i = 0; i < v->nTrackParticles(); ++i) {
            vtxTrks.insert(v->trackParticle(i));
        }


        for(int i = 0; i < trackParticles.size(); i++)
        { 
            if(vtxTrks.find(trackParticles[i]) != vtxTrks.end())
            {
                nMatch++;
            }
        }
        //cout<<"nMatch : "<<nMatch<<" "<<nTracks<<endl;

        // match found
        if(nMatch == nTracks)
        {
            vert = v;
            break;
        }
    }
    
    if(vert)
    {
        LOG(logDEBUG)<<"chi2ndf = "<<vert->chiSquared()/vert->numberDoF();
        return vert->chiSquared()/vert->numberDoF();
    }
    return -999;
}


Bool_t CutLepComb::cutVertex(const ParticleQuadlepton* currQuad) const
{
    double vrtQual = getVertexQuality(currQuad);

    if(currQuad->getQuadType() == QuadleptonType::_4mu) return (vrtQual < m_4mVrtCut);
    else return (vrtQual < m_4e_2l2l_VrtCut);    

}

