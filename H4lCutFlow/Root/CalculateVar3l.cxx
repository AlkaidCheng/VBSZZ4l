#include "H4lCutFlow/CalculateVar3l.h"
using namespace std;

CalculateVar3l::CalculateVar3l(EventContainer* eventCont)
{
    // Copying it for local use
    m_eventCont = eventCont;
    m_outTree = 0;
    
    m_fsrTool = ToolHandle<FSR::IFsrPhotonTool>("FSRTool");
    if(m_fsrTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar3l::CalculateVar3l() - cannot retrieve IFsrPhotonTool";
        exit(1);
    }
    
    m_BDTtool = ToolHandle<IH4lBDTWeights>("H4lBDTWeights");
    if(m_BDTtool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar3l::CalculateVar3l() - cannot retrieve IH4lBDTWeights";
        exit(1);
    }
    
    // For finding isolated lepton
    m_cutQuad = new CutLepComb(m_eventCont);
    
    
    m_massConstraint = ToolHandle<ZMassConstraint::IConstraintFit>("ZMassConstraint");
    if(m_BDTtool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar3l::CalculateVar3l() - cannot retrieve ZMassConstraint::IConstraintFit";
        exit(1);
    }
    
    m_energyRescaler = ToolHandle<CP::IEgammaCalibrationAndSmearingTool>("EgammaCalibrationAndSmearingTool");
    if(m_energyRescaler.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar3l::CalculateVar3l() - cannot retrieve CP::IEgammaCalibrationAndSmearingTool";
        exit(1);
    }
    
    m_electronMCClassifier = ToolHandle<IElectronMCClassification>("elMCClassifier");
    if(m_electronMCClassifier.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar3l::CalculateVar3l() - cannot retrieve IElectronMCClassification";
        exit(1);
    }
    m_recoClassification = ToolHandle<IElectronRecoClassification>("recoClassification");
    if(m_recoClassification.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar3l::CalculateVar3l() - cannot retrieve IElectronRecoClassification";
        exit(1);
    }
    m_MCTruthClassifier = ToolHandle<IMCTruthClassifier>("MCClassifier");
    if(m_MCTruthClassifier.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar3l::CalculateVar3l() - cannot retrieve MCTruthClassifier";
        exit(1);
    }
    m_grl = ToolHandle<IGoodRunsListSelectionTool>("GoodRunsListSelectionTool");
    if(m_grl.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar3l::CalculateVar3l() - cannot retrieve IGoodRunsListSelectionTool";
        exit(1);
    } 
    
    
    m_truthHelper = new TruthHelper(m_eventCont);

    clearVars();
    
}

CalculateVar3l::~CalculateVar3l()
{
    delete m_cutQuad;
    delete m_truthHelper;
}

void CalculateVar3l::process()
{
    // A local copy to limit the amount of typing
    m_outTree = m_eventCont->outTree;
    if(!m_outTree)
    {
        LOG(logERROR)<<"Error: CalculateVar3l - the output tree has not been specified";
        exit(1);
    }
    
    // General Variables
    fillGeneralVars();
    
    // Lepton related vars
    fillLeptonVars();
    
    // 3l
    fill3lVar();
    
    // Has to be before MET
    fillMassVars();
    
    //
    fillMET();
    
    fillGRLDecision();

    fillJetVars();
    
    // Jet related vars
//    fillJetVars();
//    fillFidJetVars();
    
    // Mass related vars
    
//    // Mass BDT
//    fillMassBDTVars();
    
//    fillCategory();
    
    // Angular variables
//    fillAngularVar();
    
    // Truth vars
//    fillTruthMatched();
//    fillTruth();
    
}


void CalculateVar3l::clearVars()
{
    // Clearing the variables
    if(m_outTree) m_outTree->clearVars();
    
    m_truthHelper->clearVars();
    
    m_ZplusL = 0;
    
    m_isJetFilled = false;
    
    m_leadingJet = 0;
    m_subLeadingJet = 0;
    m_jetVarFilled = false;
    
    m_phCont = 0;
    m_elCont = 0;

    m_candIndex = 0;
    
    m_elList.clear();
    m_muList.clear();
    m_jetList.clear();
    m_fidJetList.clear();
    
    while(!m_partContainer.empty()) delete m_partContainer.back(), m_partContainer.pop_back();
    
}



// Helper

// To fill in the general information
void CalculateVar3l::fillGeneralVars()
{
    // Lumi info
    m_outTree->updateLongIntVar("event", m_eventCont->eventInfo->eventNumber());
    if(m_eventCont->isMC)
    {
        m_outTree->updateIntVar("run",  m_eventCont->getDSID());
        m_outTree->updateIntVar("random_run",  m_eventCont->eventInfo->auxdecor<unsigned int>("RandomRunNumber"));
    }
    else
    {
        m_outTree->updateIntVar("run",  m_eventCont->eventInfo->runNumber());
        m_outTree->updateIntVar("random_run",  m_eventCont->eventInfo->runNumber());
    }

    m_outTree->updateIntVar("lbn",  m_eventCont->eventInfo->lumiBlock());
    // Index for candidate
    m_outTree->updateIntVar("cand_index",  m_candIndex);  
    // Pileup hash
    m_outTree->updateLongIntVar("PRWHash",  m_eventCont->eventInfo->auxdecor<unsigned long long>("PRWHash"));


    const xAOD::VertexContainer* vertexCont = 0;
    m_eventCont->getEvent()->retrieve( vertexCont, "PrimaryVertices" ).ignore();
    

    int NPV = 0;
    for ( auto vtx : *vertexCont) {
        if (vtx->nTrackParticles() >= 2)  NPV++;
    }
    m_outTree->updateIntVar("npv",  NPV);  
}

// Fill vars related to the 3l itself
void CalculateVar3l::fill3lVar()
{
    ParticleDilepton* Zcand = dynamic_cast<ParticleDilepton*> (m_ZplusL->getParticle("ZCand"));
    
    quadType::quadType partType = quadType::other;
    
    if(Zcand->getDilepType() == DileptonType::_2e)
    {
        if(m_ZplusL->getParticle("lep")->getPartType() == ParticleType::Electron) partType = quadType::_2ee;
        if(m_ZplusL->getParticle("lep")->getPartType() == ParticleType::Muon) partType = quadType::_2emu;
    }
    else if(Zcand->getDilepType() == DileptonType::_2mu)
    {
        if(m_ZplusL->getParticle("lep")->getPartType() == ParticleType::Electron) partType = quadType::_2mue;
        if(m_ZplusL->getParticle("lep")->getPartType() == ParticleType::Muon) partType = quadType::_2mumu;
    }
    m_outTree->updateIntVar("event_type", partType);
}

// To fill the general lepton vars
void CalculateVar3l::fillLeptonVars()
{
    m_outTree->updateFloatVar("Z_lepplus_pt",  m_ZplusL->getLep(0)->getTLV().Pt()/1000);
    m_outTree->updateFloatVar("Z_lepminus_pt", m_ZplusL->getLep(1)->getTLV().Pt()/1000);
    m_outTree->updateFloatVar("lep_pt",  m_ZplusL->getLep(2)->getTLV().Pt()/1000);
    
    m_outTree->updateFloatVar("Z_lepplus_eta",  m_ZplusL->getLep(0)->getTLV().Eta());
    m_outTree->updateFloatVar("Z_lepminus_eta", m_ZplusL->getLep(1)->getTLV().Eta());
    m_outTree->updateFloatVar("lep_eta",  m_ZplusL->getLep(2)->getTLV().Eta());
    
    m_outTree->updateFloatVar("Z_lepplus_phi",  m_ZplusL->getLep(0)->getTLV().Phi());
    m_outTree->updateFloatVar("Z_lepminus_phi", m_ZplusL->getLep(1)->getTLV().Phi());
    m_outTree->updateFloatVar("lep_phi",  m_ZplusL->getLep(2)->getTLV().Phi());
    
    m_outTree->updateFloatVar("Z_lepplus_m",  m_ZplusL->getLep(0)->getParticle()->m()/1000);
    m_outTree->updateFloatVar("Z_lepminus_m", m_ZplusL->getLep(1)->getParticle()->m()/1000);
    m_outTree->updateFloatVar("lep_m",  m_ZplusL->getLep(2)->getParticle()->m()/1000);
    
    
    std::array<float, 3> lepton_pt    = {{-999, -999, -999}};
    std::array<float, 3> lepton_phi   = {{-999, -999, -999}};
    std::array<float, 3> lepton_eta   = {{-999, -999, -999}};
    std::array<float, 3> lepton_m     = {{-999, -999, -999}};
    std::array<float, 3> lepton_res   = {{-999, -999, -999}};
    
    for(int i = 0; i < 3; i++)
    {
        lepton_pt[i]  = m_ZplusL->getLep(i)->getTLV().Pt()/1000;
        lepton_eta[i] = m_ZplusL->getLep(i)->getTLV().Eta();
        lepton_phi[i] = m_ZplusL->getLep(i)->getTLV().Phi();
        lepton_m[i]   = m_ZplusL->getLep(i)->getParticle()->m()/1000;
        lepton_res[i] = m_ZplusL->getLep(i)->getParticle()->auxdecor<float>("resolution");
        
    }
    

    std::array<int, 3> lepton_id       = {{-999, -999, -999}};

    for(int i = 0; i < 3; i++)
    {
        lepton_id[i] = leptonIDType::unknown;
        if(m_ZplusL->getLep(i)->getPartType() == ParticleType::Muon)
        {
            // fill Iso
            const xAOD::Muon* tempLep = dynamic_cast<const xAOD::Muon*>(m_ZplusL->getLep(i)->getParticle());
            if(tempLep->muonType() == xAOD::Muon::MuonStandAlone)   lepton_id[i] = leptonIDType::mu_SA;
            if(tempLep->muonType() == xAOD::Muon::CaloTagged)       lepton_id[i] = leptonIDType::mu_CA;
            if(tempLep->muonType() == xAOD::Muon::SegmentTagged)    lepton_id[i] = leptonIDType::mu_ST;
            if(tempLep->muonType() == xAOD::Muon::SiliconAssociatedForwardMuon)    lepton_id[i] = leptonIDType::mu_SAFM;
            if(tempLep->muonType() == xAOD::Muon::Combined)         lepton_id[i] = leptonIDType::mu_CB;
        }
        else if(m_ZplusL->getLep(i)->getPartType() == ParticleType::Electron)
        {
            // fill quality
            if(m_ZplusL->getLep(i)->getParticle()->auxdecor<int>("tightID"))            lepton_id[i] = leptonIDType::el_Tight;
            else if(m_ZplusL->getLep(i)->getParticle()->auxdecor<int>("mediumID"))      lepton_id[i] = leptonIDType::el_Medium;
            else if(m_ZplusL->getLep(i)->getParticle()->auxdecor<int>("looseID"))       lepton_id[i] = leptonIDType::el_Loose;
            else if(m_ZplusL->getLep(i)->getParticle()->auxdecor<int>("looseID_noBL"))  lepton_id[i] = leptonIDType::el_Loose_noBL;
            else if(m_ZplusL->getLep(i)->getParticle()->auxdecor<int>("veryLooseID"))   lepton_id[i] = leptonIDType::el_VLoose;
            else if(m_ZplusL->getLep(i)->getParticle()->auxdecor<int>("basicID"))       lepton_id[i] = leptonIDType::el_Basic;
        }
    }

    m_outTree->updateFloat3ArrayVar("lepton_pt", lepton_pt);
    m_outTree->updateFloat3ArrayVar("lepton_phi", lepton_phi);
    m_outTree->updateFloat3ArrayVar("lepton_eta", lepton_eta);
    m_outTree->updateFloat3ArrayVar("lepton_m", lepton_m);
    m_outTree->updateFloat3ArrayVar("lepton_res", lepton_res);
    m_outTree->updateInt3ArrayVar("lepton_id", lepton_id);

    
    
    // Recompute the isolation
    m_cutQuad->cutIsolation(m_ZplusL);
    
    
    // Bkg specific
    // array variable fill
    // m_ZplusL Z leptons are ordered by charge
    // array variable lepton pairs need to be ordered by pT
    // map the index in m_ZplusL to index in array
    int lepIndex[3] = {0, 1, 2};
    
    // For all the lepton
    std::array<int, 3> lepton_charge        = {{-999, -999, -999}};
    std::array<int, 3> lepton_quality       = {{-999, -999, -999}};
    std::array<float, 3> lepton_d0sig       = {{-999, -999, -999}};
    // pass information to be used in CR generation
    std::array<int, 3> lepton_passD0sig     = {{-999, -999, -999}};
    std::array<int, 3> lepton_passIsoCut    = {{-999, -999, -999}};
    std::array<float, 3> lepton_ptvarcone30    = {{-999, -999, -999}};
    std::array<float, 3> lepton_ptvarcone20    = {{-999, -999, -999}};
    std::array<float, 3> lepton_topoetcone20   = {{-999, -999, -999}};
    
    for(int i = 0; i < 3; i++)
    {
        lepton_charge[i] = m_ZplusL->getLep(lepIndex[i])->getCharge();
        lepton_d0sig[i] = fabs(m_ZplusL->getLep(lepIndex[i])->getParticle()->auxdecor<float>("d0sig"));
        lepton_passD0sig[i] = m_ZplusL->getLep(lepIndex[i])->getParticle()->auxdecor<int>("passD0Sig");
        lepton_passIsoCut[i] = m_ZplusL->getLep(lepIndex[i])->getParticle()->auxdecor<int>("isoCut");
        
        float ptvarcone30 = -1;
        float ptvarcone20 = -1;
        float topoetcone20 = -1;
        
        if(m_ZplusL->getLep(lepIndex[i])->getPartType() == ParticleType::Muon)
        {
            // fill Iso
            const xAOD::Muon *tempLep = dynamic_cast<const xAOD::Muon*>(m_ZplusL->getLep(lepIndex[i])->getParticle());
            
            tempLep->isolation(ptvarcone30,xAOD::Iso::ptvarcone30);
            tempLep->isolation(ptvarcone20,xAOD::Iso::ptvarcone20);
            tempLep->isolation(topoetcone20,xAOD::Iso::topoetcone20);
            
            // fill quality
            lepton_quality[i] = LeptonQuality::otherMu;
        }
        else if(m_ZplusL->getLep(lepIndex[i])->getPartType() == ParticleType::Electron)
        {
            // fill Iso
            const xAOD::Electron* tempLep = dynamic_cast<const xAOD::Electron*>(m_ZplusL->getLep(lepIndex[i])->getParticle());
            
            tempLep->isolation(ptvarcone30,xAOD::Iso::ptvarcone30);
            tempLep->isolation(ptvarcone20,xAOD::Iso::ptvarcone20);
            tempLep->isolation(topoetcone20,xAOD::Iso::topoetcone20);
            
            // fill quality
            if(m_ZplusL->getLep(lepIndex[i])->getParticle()->auxdecor<int>("looseID")) lepton_quality[i] = LeptonQuality::looseID;
            else if(m_ZplusL->getLep(lepIndex[i])->getParticle()->auxdecor<int>("veryLooseID")) lepton_quality[i] = LeptonQuality::veryLooseID;
            else if(m_ZplusL->getLep(lepIndex[i])->getParticle()->auxdecor<int>("basicID")) lepton_quality[i] = LeptonQuality::basicID;
            else lepton_quality[i] = LeptonQuality::otherEl;
        }
        
        ptvarcone30 = m_ZplusL->getLep(lepIndex[i])->getParticle()->auxdecor<float>("corr_ptvarcone30");
        ptvarcone20 = m_ZplusL->getLep(lepIndex[i])->getParticle()->auxdecor<float>("corr_ptvarcone20");
        topoetcone20 = m_ZplusL->getLep(lepIndex[i])->getParticle()->auxdecor<float>("corr_topoetcone20");
        
        lepton_ptvarcone30[i] = ptvarcone30/m_ZplusL->getLep(lepIndex[i])->getParticle()->pt();
        lepton_ptvarcone20[i] = ptvarcone20/m_ZplusL->getLep(lepIndex[i])->getParticle()->pt();
        lepton_topoetcone20[i] = topoetcone20/m_ZplusL->getLep(lepIndex[i])->getParticle()->pt();
        
    }
    
    m_outTree->updateInt3ArrayVar("lepton_charge", lepton_charge);
    m_outTree->updateInt3ArrayVar("lepton_quality", lepton_quality);
    m_outTree->updateFloat3ArrayVar("lepton_d0sig", lepton_d0sig);
    
    m_outTree->updateFloat3ArrayVar("lepton_ptvarcone30", lepton_ptvarcone30);
    m_outTree->updateFloat3ArrayVar("lepton_ptvarcone20", lepton_ptvarcone20);
    m_outTree->updateFloat3ArrayVar("lepton_topoetcone20", lepton_topoetcone20);
    
    m_outTree->updateInt3ArrayVar("lepton_passD0sig", lepton_passD0sig);
    m_outTree->updateInt3ArrayVar("lepton_passIsoCut", lepton_passIsoCut);
    
    // el specific
    std::array<int, 3> el_recoClass = {{-999, -999, -999}};
    std::array<int, 3> el_MCClass = {{-999, -999, -999}};
    std::array<float, 3> el_Rphi = {{-999, -999, -999}};
    std::array<float, 3> el_Deta = {{-999, -999, -999}};
    std::array<float, 3> el_Reta = {{-999, -999, -999}};
    std::array<float, 3> el_f1 = {{-999, -999, -999}};
    std::array<int, 3> el_nBL = {{-999, -999, -999}};
    std::array<int, 3> el_nInnerExpPix = {{-999, -999, -999}};
    std::array<float, 3> el_rTRT = {{-999, -999, -999}};
    std::array<float, 3> el_eProbHT = {{-999, -999, -999}};
    std::array<float, 3> el_eOverP = {{-999, -999, -999}};
    std::array<int, 3> el_nPix = {{-999, -999, -999}};
    std::array<int, 3> el_nSCT = {{-999, -999, -999}};
    std::array<int, 3> el_expInner = {{-999, -999, -999}};
    std::array<int, 3> el_expNextToInner = {{-999, -999, -999}};
    std::array<int, 3> el_nInner = {{-999, -999, -999}};
    std::array<int, 3> el_nNextToInner = {{-999, -999, -999}};

    uint8_t sumval;
    float val;
    for(int i = 0; i < 3; i++)
    {
        if(m_ZplusL->getLep(lepIndex[i])->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron *tempEl = dynamic_cast<const xAOD::Electron*>(m_ZplusL->getLep(lepIndex[i])->getParticle());
            const xAOD::TrackParticle* tp = tempEl->trackParticle();
            el_recoClass[i] = m_recoClassification->getRecoClassification(*tempEl);
            el_MCClass[i] = m_electronMCClassifier->getMCClassification(*tempEl);
            el_Rphi[i] = tempEl->showerShapeValue(val, xAOD::EgammaParameters::Rphi) ? val : -999;
            el_Reta[i] = tempEl->showerShapeValue(val, xAOD::EgammaParameters::Reta) ? val : -999;
            el_f1[i] = tempEl->showerShapeValue(val, xAOD::EgammaParameters::f1)     ? val : -999;
            el_Deta[i] = tempEl->trackCaloMatchValue(xAOD::EgammaParameters::deltaEta1);
            int expBL       = tempEl->trackParticleSummaryValue(sumval, xAOD::expectBLayerHit)    ? sumval : -999;
            el_nBL[i]       = (1 == expBL && tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfBLayerHits))? sumval : -999;

            el_nPix[i]       = tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfPixelHits) ? sumval : -999;
            el_nSCT[i]      = tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfSCTHits) ? sumval : -999;

            int expectInPix             = tempEl->trackParticleSummaryValue(sumval, xAOD::expectInnermostPixelLayerHit) ? sumval : -999;
            int expectNextInPix         = tempEl->trackParticleSummaryValue(sumval, xAOD::expectNextToInnermostPixelLayerHit) ? sumval : -999;
            if (expectInPix == 1) {
                el_nInnerExpPix[i] = tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfInnermostPixelLayerHits) ? sumval : -999;
            }
            else if (expectNextInPix == 1) {
                el_nInnerExpPix[i] = tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfNextToInnermostPixelLayerHits) ? sumval : -999;
            }


            el_expInner[i]          =  tempEl->trackParticleSummaryValue(sumval, xAOD::expectInnermostPixelLayerHit) ? sumval : -999;
            el_expNextToInner[i]    =  tempEl->trackParticleSummaryValue(sumval, xAOD::expectNextToInnermostPixelLayerHit) ? sumval : -999;

            el_nInner[i]          =  tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfInnermostPixelLayerHits) ? sumval : -999;
            el_nNextToInner[i]    =  tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfNextToInnermostPixelLayerHits) ? sumval : -999;

            float el_nTRT = (float) tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfTRTHits) ? sumval : -999;
            float el_nHTTRT = (float) tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfTRTHighThresholdHits) ? sumval : -999;
            if(el_nTRT) el_rTRT[i] = el_nHTTRT / el_nTRT;
            else el_rTRT[i] = -999;
            
            el_eProbHT[i] = tempEl->trackParticleSummaryValue(val, xAOD::eProbabilityHT) ? val : -999;
            el_eOverP[i] = fabs(tempEl->e()*tp->qOverP());
        }
    }
    
    m_outTree->updateFloat3ArrayVar("el_Reta", el_Reta);
    m_outTree->updateFloat3ArrayVar("el_Rphi", el_Rphi);
    m_outTree->updateFloat3ArrayVar("el_f1", el_f1);
    m_outTree->updateInt3ArrayVar("el_nBL", el_nBL);
    m_outTree->updateInt3ArrayVar("el_nInnerExpPix", el_nInnerExpPix);
    m_outTree->updateFloat3ArrayVar("el_rTRT", el_rTRT);
    m_outTree->updateInt3ArrayVar("el_nPix", el_nPix);
    m_outTree->updateInt3ArrayVar("el_nSCT", el_nSCT);

    m_outTree->updateInt3ArrayVar("el_expInner", el_expInner);
    m_outTree->updateInt3ArrayVar("el_expNextToInner", el_expNextToInner);
    m_outTree->updateInt3ArrayVar("el_nInner", el_nInner);
    m_outTree->updateInt3ArrayVar("el_nNextToInner", el_nNextToInner);

    m_outTree->updateInt3ArrayVar("el_recoClass", el_recoClass);
    m_outTree->updateInt3ArrayVar("el_MCClass", el_MCClass);
    m_outTree->updateFloat3ArrayVar("el_Rphi", el_Rphi);
    m_outTree->updateFloat3ArrayVar("el_Reta", el_Reta);
    m_outTree->updateFloat3ArrayVar("el_f1", el_f1);
    m_outTree->updateFloat3ArrayVar("el_Deta1", el_Deta);    
    m_outTree->updateInt3ArrayVar("el_nBL", el_nBL);
    m_outTree->updateFloat3ArrayVar("el_rTRT", el_rTRT);
    m_outTree->updateFloat3ArrayVar("el_eProbHT", el_eProbHT);
    m_outTree->updateFloat3ArrayVar("el_eOverP", el_eOverP);
    
    // mu specific
    std::array<int, 3> mu_MCPartType = {{-999, -999, -999}};
    std::array<int, 3> mu_MCOriginType = {{-999, -999, -999}};
    std::array<float, 3> mu_IDpt = {{-999, -999, -999}};
    std::array<float, 3> mu_MSpt = {{-999, -999, -999}};
    std::array<float, 3> mu_qOverPsig = {{-999, -999, -999}};
    std::array<int, 3> mu_author = {{-999, -999, -999}};
    std::array<int, 3> mu_type = {{-999, -999, -999}};
    std::array<int, 3> mu_NPrecLayer = {{-999, -999, -999}};
    std::array<int, 3> mu_nInnerExpPix = {{-999, -999, -999}};
    
    for(int i = 0; i < 3; i++)
    {
        if(m_ZplusL->getLep(lepIndex[i])->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* tempMu = dynamic_cast<const xAOD::Muon*>(m_ZplusL->getLep(lepIndex[i])->getParticle());
            const xAOD::TrackParticle* idtp = tempMu->trackParticle(xAOD::Muon::InnerDetectorTrackParticle);
            const xAOD::TrackParticle* emstp = tempMu->trackParticle(xAOD::Muon::ExtrapolatedMuonSpectrometerTrackParticle);

           bool isIDOK = (tempMu->isAvailable< float >( "InnerDetectorPt" ) && idtp);
            bool isMSOK = (tempMu->isAvailable< float >( "MuonSpectrometerPt" ) && emstp);

            mu_IDpt[i] = isIDOK ? tempMu->auxdata< float >( "InnerDetectorPt" )/1000 : -999;
            mu_MSpt[i] = isMSOK? tempMu->auxdata< float >( "MuonSpectrometerPt" )/1000 : -999;
            
            mu_author[i] = tempMu->author();
            mu_type[i] = tempMu->muonType();
            tempMu->summaryValue(sumval,xAOD::numberOfPrecisionLayers);
            mu_NPrecLayer[i] = sumval;
            std::pair<MCTruthPartClassifier::ParticleType,MCTruthPartClassifier::ParticleOrigin>
            classification = m_MCTruthClassifier->particleTruthClassifier(tempMu);
            mu_MCPartType[i] = classification.first;
            mu_MCOriginType[i] = classification.second;


            if (isIDOK && isMSOK) {
                float qOverPsigma  = sqrt( idtp->definingParametersCovMatrix()(4,4) +
                        emstp->definingParametersCovMatrix()(4,4) );
                mu_qOverPsig[i] = fabs(emstp->qOverP() - idtp->qOverP()) / qOverPsigma;
            }

            if (isIDOK) {

                int expInPix             = idtp->summaryValue(sumval, xAOD::expectInnermostPixelLayerHit)? sumval : -999;
                int expNextInPix         = idtp->summaryValue(sumval, xAOD::expectNextToInnermostPixelLayerHit)? sumval : -999;
                if (1 == expInPix) {
                    mu_nInnerExpPix[i]   = idtp->summaryValue(sumval, xAOD::numberOfInnermostPixelLayerHits)? sumval : -999;
                }
                else if (1 == expNextInPix) {
                    mu_nInnerExpPix[i]  = idtp->summaryValue(sumval, xAOD::numberOfNextToInnermostPixelLayerHits)? sumval : -999;
                }
            }
        }
    }
    m_outTree->updateFloat3ArrayVar("mu_IDpt", mu_IDpt);
    m_outTree->updateFloat3ArrayVar("mu_MSpt", mu_MSpt);
    m_outTree->updateFloat3ArrayVar("mu_qOverPsig", mu_qOverPsig);
    m_outTree->updateInt3ArrayVar("mu_author", mu_author);
    m_outTree->updateInt3ArrayVar("mu_type", mu_type);
    m_outTree->updateInt3ArrayVar("mu_NPrecLayer", mu_NPrecLayer);
    m_outTree->updateInt3ArrayVar("mu_MCPartType", mu_MCPartType);
    m_outTree->updateInt3ArrayVar("mu_MCOriginType", mu_MCOriginType);
    m_outTree->updateInt3ArrayVar("mu_nInnerExpPix", mu_nInnerExpPix);

}

// To Caclulate the mass
void CalculateVar3l::fillMassVars()
{
    m_outTree->updateFloatVar("mZ_unconstrained", m_ZplusL->getParticle("ZCand")->getTLV().M()/1000);
    m_outTree->updateFloatVar("m3l_unconstrained", m_ZplusL->getTLV().M()/1000);
    
    m_outTree->updateFloatVar("pt3l_unconstrained", m_ZplusL->getTLV().Pt()/1000);
    m_outTree->updateFloatVar("eta3l_unconstrained", m_ZplusL->getTLV().Eta());
    m_outTree->updateFloatVar("y3l_unconstrained", m_ZplusL->getTLV().Rapidity());

    fillFSRVars();
    fillZMCVars();

    LOG(logDEBUG)<<"mZ_unconstrained: "<<m_ZplusL->getParticle("ZCand")->getTLV().M()/1000;
    LOG(logDEBUG)<<"mZ_FSR: "<<m_ZplusL->getParticle("ZCand")->getAnalTLV(TLVType::FSR).M()/1000;
    LOG(logDEBUG)<<"mZ_constrained: "<<m_ZplusL->getParticle("ZCand")->getAnalTLV(TLVType::Constrained).M()/1000;
}

void CalculateVar3l::fillMET()
{
    
    if(!m_metCalc) return;
    
    // check if the el muons and jets were filled from outside
    if(!(m_metCalc->isElFilled() && m_metCalc->isMuFilled() && m_metCalc->isJetFilled()))
    {
        LOG(logERROR)<<"CalculateVar4l - Input MET class not filled with information";
        LOG(logERROR)<<"m_metCalc->isElFilled(): "<<m_metCalc->isElFilled();
        LOG(logERROR)<<"m_metCalc->isMuFilled(): "<<m_metCalc->isMuFilled();
        LOG(logERROR)<<"m_metCalc->isJetFilled(): "<<m_metCalc->isJetFilled();
        exit(1);
    }
    
    // Give the photon
    vector<ParticleVar*> phList;
    
    ParticleDilepton* Zcand = dynamic_cast<ParticleDilepton*> (m_ZplusL->getParticle("ZCand"));
    LOG(logDEBUG)<<"Checking if there is a FSR";
    if(Zcand->hasFSR())
    {
        LOG(logDEBUG)<<"Add FSR";
        phList.push_back(Zcand->getFSR());
    }
    
    m_metCalc->setFSRParticles(phList);
    m_metCalc->process();
    
    const xAOD::MissingET* met = m_metCalc->getTrackMET();
    
    m_outTree->updateFloatVar("met_et", met->met()/1000.);
    m_outTree->updateFloatVar("met_sum_et", met->sumet()/1000.);
    m_outTree->updateFloatVar("met_phi", met->phi());

    
}

void CalculateVar3l::fillFSRVars()
{
    vector< FSR::FsrCandidate> candidateVec;
    
    fsrType::fsrType fsrTypeVar = fsrType::noFSR;
    // Backup the FSR vars
    m_ZplusL->addAnalTLV(TLVType::FSR, m_ZplusL->getTLV(), true);
    
    ParticleDilepton* Zcand = dynamic_cast<ParticleDilepton*> (m_ZplusL->getParticle("ZCand"));
    Zcand->clearFSR();
    Zcand->addAnalTLV(TLVType::FSR, Zcand->getTLV(), true);
    
    if((m_phCont == 0) || (m_elCont == 0))
    {
        LOG(logERROR)<<"Calibrated el and ph container not set for FSR";
        exit(1);
    }
    
    // Getting the FSR Photon
    for (Int_t i = 0; i < (Int_t) Zcand->getLepSize(); i++)
    {
        FSR::FsrCandidate cand;
        candidateVec.push_back(cand);
        
        if(Zcand->getLep(i)->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* temp = dynamic_cast<const xAOD::Muon*> (Zcand->getLep(i)->getParticle());
            if(temp->muonType() == xAOD::Muon::MuonStandAlone) continue;
            else if (temp->muonType() == xAOD::Muon::CaloTagged) continue;
            
            if(m_fsrTool->getFsrPhoton(Zcand->getLep(i)->getParticle(), cand, m_phCont, m_elCont))
            {
                LOG(logDEBUG) <<"Found FSR candidate for muon "<<i;
                LOG(logDEBUG) <<"Candidate Et: "<<cand.Et<<" eta: "<<cand.eta<< " deltaR: "<<cand.deltaR<<" type: "<<cand.type;
            }
        }
        else if(Zcand->getLep(i)->getPartType() == ParticleType::Electron)
        {
            if(m_fsrTool->getFsrPhoton(Zcand->getLep(i)->getParticle(), cand, m_phCont, m_elCont))
            {
                LOG(logDEBUG) <<"Found FSR candidate for electron "<< i;
                LOG(logDEBUG) <<"Candidate Et: "<<cand.Et<<" eta: "<<cand.eta<< " deltaR: "<<cand.deltaR<<" type: "<<cand.type;                
            }
        }
        if(cand.particle) cand.particle->auxdecor<int>("associated_lep_fsr") = (int) i;
        candidateVec[i] = cand;
    }
    
    Bool_t passFSRCollinear = false;
    Bool_t passFSRFar = false;
    
    
    // Collinear only happens for 2mu
    if(Zcand->getDilepType() == DileptonType::_2mu)
    {
        Double_t higestEt = -99999;
        FSR::FsrCandidate candidate;
        Bool_t isFSR = false;
        
        // Look at just the first two FSR and find the highest cluster Et fsr
        for(Int_t i = 0; i < 2; i++)
        {
            FSR::FsrCandidate tempCandidate = candidateVec[i];
            
            // Find the higest Et collinear photon on the cluster
            if(tempCandidate.Et != -1 && tempCandidate.Et > higestEt && tempCandidate.deltaR <= 0.15)
            {
                higestEt = tempCandidate.Et;
                candidate = tempCandidate;
                isFSR = true;
            }
        }
        
        LOG(logDEBUG) <<"FSR colinear candidate Passed the deltaR cut";
        LOG(logDEBUG) <<"Et: "<<higestEt;
        
        // if FSR found, then do the checks associated with Z1 for the collinear FSR
        if(isFSR)
        {
            if((Zcand->getTLV().M() < 89*1000) && (Zcand->getTLV().M() > 66*1000))
            {
                LOG(logDEBUG) << "FSR collinear candidate passed the Z mass cut";
                
                TLorentzVector momFSR;
                momFSR.SetPtEtaPhiM(candidate.Et,candidate.eta,candidate.phi, 0.0);
                
                Double_t combMass = (Zcand->getTLV() + momFSR).M();
                if(combMass < 100*1000)
                {
                    LOG(logDEBUG)<<"FSR collinear candidate passed the combined mass cut";
                    passFSRCollinear = true;
                    addFSRCandidate(candidate);
                    fsrTypeVar = fsrType::collFSRZ1mumu;
                }
            }
        }
    }
    // If no collinear FSR has been found
    if(!passFSRCollinear)
    {
        Double_t higestEt = -99999;
        FSR::FsrCandidate candidate;
        Bool_t isFSR = false;
        // Loop over all the candidates and find the highest Et cluster far FSR
        for(Int_t i = 0; i < (Int_t) candidateVec.size(); i++)
        {
            FSR::FsrCandidate tempCandidate = candidateVec[i];
            TLorentzVector momFSRTemp;
            momFSRTemp.SetPtEtaPhiM(tempCandidate.Et,tempCandidate.eta,tempCandidate.phi, 0.0);

            Bool_t passFSROvlp = false;
            // Do the overlap first
            for(Int_t i = 0; i < (Int_t) Zcand->getLepSize(); i++)
            {
                if(momFSRTemp.DeltaR(Zcand->getLep(i)->getTLV()) < 0.15) passFSROvlp = true;
            }

            if(passFSROvlp) continue; 
            // Find the higest Et far photon on the cluster
            if(tempCandidate.Et != -1 && tempCandidate.Et > higestEt && tempCandidate.deltaR > 0.15)
            {
                higestEt = tempCandidate.Et;
                candidate = tempCandidate;
                isFSR = true;
            }
        }
        
        // If there is such a FSR candidate
        if(isFSR)
        {
            LOG(logDEBUG)<<"FSR far candidate exists";
            
            //cout<<"There is a candidate Far FSR"<<endl;
            TLorentzVector momFSR;
            momFSR.SetPtEtaPhiM(candidate.Et,candidate.eta,candidate.phi, 0.0);
            
            // Delta R cut: Ensure that deltaR > 0.15 for all the leptons in the quadruplet
            // Sortof the opposite logic here
            Bool_t deltaRCut = false;
            for(Int_t i = 0; i < (Int_t) m_ZplusL->getLepSize(); i++)
            {
                if(momFSR.DeltaR(m_ZplusL->getLep(i)->getTLV()) < 0.15) 
                {
                    deltaRCut = true;
                    LOG(logDEBUG)<<"FSR overlapping";
                    LOG(logDEBUG)<<"Candidate Et: "<<candidate.Et<<" eta: "<<candidate.eta<< " deltaR: "<<candidate.deltaR<<" type: "<<candidate.type;                
                    LOG(logDEBUG)<<"Overlapping particle pt: "
                        <<m_ZplusL->getLep(i)->getTLV().Pt()
                        <<" eta: "<<m_ZplusL->getLep(i)->getTLV().Eta()
                        <<" phi: "<<m_ZplusL->getLep(i)->getTLV().Phi();
                    

                }
                
            }
            // If deltaR cut has been pases
            if(!deltaRCut)
            {
                
                LOG(logDEBUG)<<"FSR far candidate passed Delta R cut";
                
                //cout<<"Passed Delta R cut"<<endl;
                Double_t deltaZMass = 999999;
                // if the dilepton mass is less than 81 GeV, find how much the FSR move the mass close to
                // Z pole mass... 100 GeV limit there as well
                if(Zcand->getTLV().M() < 81*1000)
                {
                    TLorentzVector combined = Zcand->getTLV() + momFSR;
                    if(combined.M() < 100 * 1000) deltaZMass = fabs(combined.M() - pdgZMass);
                }
                
                // Figuring out which dilepton to associate the far FSR photon with
                if(deltaZMass != 999999)
                {
                    addFSRCandidate(candidate);
                    passFSRFar = true;
                    fsrTypeVar = fsrType::farFSRZ1;
                    LOG(logDEBUG)<<"Far FSR Attached to Z";
                }
            }
        }
    }
    
    if(passFSRCollinear){ LOG(logDEBUG)<<"Colinear FSR event"; }
    if(passFSRFar){ LOG(logDEBUG)<<"Far FSR event"; }
    
    /*
    Double_t m4lFSR = m_ZplusL->getAnalTLV(TLVType::FSR).M()/1000;
    Double_t mZ1FSR = m_ZplusL->getZ1()->getAnalTLV(TLVType::FSR).M()/1000;
    Double_t mZ2FSR = m_ZplusL->getZ2()->getAnalTLV(TLVType::FSR).M()/1000;
    
    m_outTree->updateFloatVar("mZ1_fsr", mZ1FSR);
    m_outTree->updateFloatVar("mZ2_fsr", mZ2FSR);
    m_outTree->updateFloatVar("m4l_fsr", m4lFSR);
    m_outTree->updateIntVar("fsr_type", (int) fsrTypeVar);
    if(m_ZplusL->getZ1()->hasFSR())
    {
        m_outTree->updateFloatVar("fsr_pt", m_ZplusL->getZ1()->getFSR()->getAnalTLV(TLVType::Unconstrained).Pt()/1000);
        m_outTree->updateFloatVar("fsr_eta", m_ZplusL->getZ1()->getFSR()->getAnalTLV(TLVType::Unconstrained).Eta());
        m_outTree->updateFloatVar("fsr_phi", m_ZplusL->getZ1()->getFSR()->getAnalTLV(TLVType::Unconstrained).Phi());
        m_outTree->updateIntVar("fsr_associated_lepton", m_ZplusL->getZ1()->getFSR()->getParticle()->auxdecor<int>("associated_lep_fsr"));
    }
    else if(m_ZplusL->getZ2()->hasFSR())
    {
        m_outTree->updateFloatVar("fsr_pt", m_ZplusL->getZ2()->getFSR()->getAnalTLV(TLVType::Unconstrained).Pt()/1000);
        m_outTree->updateFloatVar("fsr_eta", m_ZplusL->getZ2()->getFSR()->getAnalTLV(TLVType::Unconstrained).Eta());
        m_outTree->updateFloatVar("fsr_phi", m_ZplusL->getZ2()->getFSR()->getAnalTLV(TLVType::Unconstrained).Phi());
        m_outTree->updateIntVar("fsr_associated_lepton", m_ZplusL->getZ2()->getFSR()->getParticle()->auxdecor<int>("associated_lep_fsr"));
    }
     */
}

// Add FSR to photon
void CalculateVar3l::addFSRCandidate(FSR::FsrCandidate candidate)
{
    
    LOG(logDEBUG)<< "cand et,eta,phi,dR,etCorr,type,index "
    << candidate.Et << "/" << candidate.eta << "/" << candidate.phi
    << "/" << candidate.deltaR << "/"
    << (400./cosh(candidate.eta)) << "/"
    //<< candidate.topoEtcone40 << "/"
    << candidate.type;
    
    ParticleVar* partFSR = new ParticleVar(m_eventCont, candidate.particle, -1);
    m_partContainer.push_back(partFSR);
    partFSR->addAnalParticle(m_eventCont->m_analType, candidate.particle);
    
    // Recreate the TLV
    TLorentzVector fsrTLV;
    fsrTLV.SetPtEtaPhiM(candidate.Et, candidate.eta, candidate.phi, 0);
    
    partFSR->addAnalTLV(TLVType::Unconstrained, fsrTLV, true);
    partFSR->setAnalysisType(m_eventCont->m_analType);
    ParticleDilepton* Zcand = dynamic_cast<ParticleDilepton*> (m_ZplusL->getParticle("ZCand"));
    Zcand->setFSR(partFSR);
}


void CalculateVar3l::fillGRLDecision()
{
    int m_GRLisOK = -999;

    // GRL: Select good LumiBlocks for each run
    if (m_eventCont->isMC) m_GRLisOK = 1;
    else 
    {
        m_GRLisOK = m_grl->passRunLB(*(m_eventCont->eventInfo)); // all good for default

        if (!m_GRLisOK)
        {
            // If run number is NOT in GRL, set GRLisOK to -999
            if (!m_grl->getGRLCollection().HasRun((m_eventCont->eventInfo->runNumber()))) m_GRLisOK = -999;
        }
    }
    m_outTree->updateIntVar("GRLisOK", m_GRLisOK);
    
}

void CalculateVar3l::fillJetVars()
{
    if(!m_isJetFilled)
    {
        LOG(logERROR)<<"CalculateVar3l: Jet vector not filled";
        exit(1);
    }

    // Caching the results
    if(m_jetVarFilled) return;
    m_jetVarFilled = true;

    std::sort (m_jetList.begin(), m_jetList.end(), sortParticleVarPt); 
    

    m_outTree->updateIntVar("n_jets", m_jetList.size());


    std::array<float, 4> jet_pt = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_eta = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_phi = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_m = {{-999, -999, -999, -999}};
    std::array<int, 4> jet_btag70 = {{-999, -999, -999, -999}};
    std::array<int, 4> jet_btag85 = {{-999, -999, -999, -999}};
    

    int nJets = 4;
    if(m_jetList.size() < 4) nJets = m_jetList.size();

    for(int i = 0; i < nJets; i++)
    {
        const xAOD::Jet* jet = dynamic_cast<const xAOD::Jet*>(m_jetList[i]->getParticle());
        jet_pt[i] = jet->pt()/1000;
        jet_eta[i] = jet->eta();
        jet_phi[i] = jet->phi();
        jet_m[i] = jet->m()/1000;

        if(i == 0)
        {
            m_outTree->updateFloatVar("leading_jet_pt", jet->pt()/1000);
            m_outTree->updateFloatVar("leading_jet_width", jet->getAttribute<float>("Width"));
            std::vector<float> widths;
            jet->getAttribute<std::vector<float>>(xAOD::JetAttribute::TrackWidthPt1000, widths);
            if (widths.size()) m_outTree->updateFloatVar("leading_jet_TrackWidthPt1000", widths[0]);
        }
        else if(i == 1)
        {
            m_outTree->updateFloatVar("subleading_jet_pt", jet->pt()/1000);
            m_outTree->updateFloatVar("subleading_jet_width", jet->getAttribute<float>("Width"));
            std::vector<float> widths;
            jet->getAttribute<std::vector<float>>(xAOD::JetAttribute::TrackWidthPt1000, widths);
            if (widths.size()) m_outTree->updateFloatVar("subleading_jet_TrackWidthPt1000", widths[0]);

        }

        LOG(logDEBUG)<<"jet i: "<<i<<" pt: "<<jet->pt()/1000
        <<" eta: "<<jet->eta()
        <<" Phi: "<<jet->phi()
        <<" m: "<<jet->m()/1000
        <<" isBjet70: "<<jet->auxdecor<int>("isBjet70")
        <<" isBjet85: "<<jet->auxdecor<int>("isBjet85");
            
        // jet_width[i] = jet->getAttribute<float>("Width")
        // std::vector<float> widths;
        // jet->getAttribute<std::vector<float>>(xAOD::JetAttribute::TrackWidthPt1000, widths);
        // if (widths.size()) jet_TrackWidthPt1000[i] = widths[0];
        //
        
        // Btagging jets
        if(jet->auxdecor<int>("isBjet70")) jet_btag70[i] = 1;
        else jet_btag70[i] = 0;

        if(jet->auxdecor<int>("isBjet85")) jet_btag85[i] = 1;
        else jet_btag85[i] = 0;

    }
    m_outTree->updateFloatArrayVar("jet_pt", jet_pt);
    m_outTree->updateFloatArrayVar("jet_eta", jet_eta);
    m_outTree->updateFloatArrayVar("jet_phi", jet_phi);
    m_outTree->updateFloatArrayVar("jet_m", jet_m);
    m_outTree->updateIntArrayVar("jet_btag70", jet_btag70);
    m_outTree->updateIntArrayVar("jet_btag85", jet_btag85);
    
    // for rest of the code 
    if(m_jetList.size() > 0)
    {
        m_leadingJet = m_jetList[0];
    }
    if(m_jetList.size() > 1)
    {
        m_subLeadingJet = m_jetList[1];
    }

    // couting bJets
    int n_jets_btag60 = 0;
    int n_jets_btag70 = 0;
    int n_jets_btag77 = 0;
    int n_jets_btag85 = 0;
    for(const auto jetVar: m_jetList)
    {
        if(jetVar->getParticle()->auxdecor<int>("isBjet60")) n_jets_btag60++;
        if(jetVar->getParticle()->auxdecor<int>("isBjet70")) n_jets_btag70++;
        if(jetVar->getParticle()->auxdecor<int>("isBjet77")) n_jets_btag77++;
        if(jetVar->getParticle()->auxdecor<int>("isBjet85")) n_jets_btag85++;
    }
    m_outTree->updateIntVar("n_jets_btag60", n_jets_btag60 );
    m_outTree->updateIntVar("n_jets_btag70", n_jets_btag70 );
    m_outTree->updateIntVar("n_jets_btag77", n_jets_btag77 );
    m_outTree->updateIntVar("n_jets_btag85", n_jets_btag85 );

    /*
    if (iLeadingJet != -1)
    {
        const xAOD::Jet* jet = dynamic_cast<const xAOD::Jet*>(m_jetList[iLeadingJet]->getParticle());
        //m_outTree->updateFloatVar("leading_jet_pt", m_jetList[iLeadingJet]->getTLV().Pt()/1000);
        //m_outTree->updateFloatVar("leading_jet_eta", m_jetList[iLeadingJet]->getTLV().Eta());
        //m_outTree->updateFloatVar("leading_jet_phi", m_jetList[iLeadingJet]->getTLV().Phi());

        m_outTree->updateFloatVar("leading_jet_pt", jet->pt()/1000);
        m_outTree->updateFloatVar("leading_jet_eta", jet->eta());
        m_outTree->updateFloatVar("leading_jet_phi", jet->phi());
        m_outTree->updateFloatVar("leading_jet_m", jet->m()/1000);
        m_outTree->updateFloatVar("leading_jet_width", jet->getAttribute<float>("Width"));
        std::vector<float> widths;
        jet->getAttribute<std::vector<float>>(xAOD::JetAttribute::TrackWidthPt1000, widths);
        if (widths.size())m_outTree->updateFloatVar("leading_jet_TrackWidthPt1000", widths[0]);
        
        LOG(logDEBUG)<<"leading_jet_pt: "<<jet->pt()/1000;
        LOG(logDEBUG)<<"leading_jet_eta: "<<jet->eta();
        LOG(logDEBUG)<<"leading_jet_Phi: "<<jet->phi();
        LOG(logDEBUG)<<"leading_jet_m: "<<jet->m()/1000;
    }

    if (iSubleadingJet != -1)
    {
        const xAOD::Jet* jet = dynamic_cast<const xAOD::Jet*>(m_jetList[iSubleadingJet]->getParticle());
        m_outTree->updateFloatVar("subleading_jet_pt", m_jetList[iSubleadingJet]->getTLV().Pt()/1000);
        m_outTree->updateFloatVar("subleading_jet_eta", m_jetList[iSubleadingJet]->getTLV().Eta());
        m_outTree->updateFloatVar("subleading_jet_phi", m_jetList[iSubleadingJet]->getTLV().Phi());
        m_outTree->updateFloatVar("subleading_jet_m", jet->m()/1000);

        m_outTree->updateFloatVar("subleading_jet_width", jet->getAttribute<float>("Width"));

        std::vector<float> widths;
        jet->getAttribute<std::vector<float>>(xAOD::JetAttribute::TrackWidthPt1000, widths);
        if (widths.size())m_outTree->updateFloatVar("subleading_jet_TrackWidthPt1000", widths[0]);



        LOG(logDEBUG)<<"subleading_jet_pt: "<<jet->pt()/1000;
        LOG(logDEBUG)<<"subleading_jet_eta: "<<jet->eta();
        LOG(logDEBUG)<<"subleading_jet_Phi: "<<jet->phi();
        LOG(logDEBUG)<<"subleading_jet_m: "<<jet->m()/1000;

        m_subLeadingJet = m_jetList[iSubleadingJet];

    }
    */
    // If both leading and subleading jets are found
    if (m_jetList.size() >=2 ) {
        Int_t iLeadingJet = 0;
        Int_t iSubleadingJet = 1;
        TLorentzVector combined = m_jetList[iLeadingJet]->getTLV() + m_jetList[iSubleadingJet]->getTLV();

        m_outTree->updateFloatVar("dijet_invmass", combined.M()/1000);
        m_outTree->updateFloatVar("dijet_deltaeta", fabs(m_jetList[iLeadingJet]->getTLV().Eta() - m_jetList[iSubleadingJet]->getTLV().Eta()));
        // m_outTree->updateFloatVar("pt4ljj_unconstrained", (m_higgs->getTLV()+combined).Pt()/1000);
        // m_outTree->updateFloatVar("eta_zepp_ZZ", fabs(m_higgs->getTLV().Eta() - (m_jetList[iLeadingJet]->getTLV().Eta() + m_jetList[iSubleadingJet]->getTLV().Eta())/2));

        vector<const xAOD::IParticle*> jets;
        vector<const xAOD::IParticle*> leptons;

        // Get the jets
        jets.push_back(m_jetList[iLeadingJet]->getParticle());
        jets.push_back(m_jetList[iSubleadingJet]->getParticle());


        // // Get the leptons
        // for(int i = 0; i < 4; i++)
        // {
        //     leptons.push_back(m_higgs->getLep(i)->getParticle());
        // }

        // m_outTree->updateFloatVar("min_dR_jZ", computeMinDeltaR(leptons, jets));
        

    }


    LOG(logDEBUG)<<"dijet_invmass: "<<m_outTree->getFloatVar("dijet_invmass");
    LOG(logDEBUG)<<"dijet_deltaeta: "<<m_outTree->getFloatVar("dijet_deltaeta");

}


void CalculateVar3l::fillZMCVars()
{
    
    ParticleDilepton* Zcand = dynamic_cast<ParticleDilepton*> (m_ZplusL->getParticle("ZCand"));

    // Get the inputs
    ZMassConstraint::ConstraintFitOutput resultZ;
    ZMassConstraint::ConstraintFitInput inputZ = getZMCInput(Zcand);
    
    
    // ZMC on the Z1
    if (m_massConstraint->doMassFit(inputZ, resultZ).isFailure()) {
        LOG(logERROR) << "doMassConstraint: Unable to do mass contrained fit for Z1";
        exit(1);
    }
    
    Zcand->getLepOne()->addAnalTLV(TLVType::Constrained, resultZ.getConstituentFourVector(0), true);
    Zcand->getLepTwo()->addAnalTLV(TLVType::Constrained, resultZ.getConstituentFourVector(1), true);
    if(Zcand->hasFSR())
    {
        Zcand->getFSR()->addAnalTLV(TLVType::Constrained, resultZ.getConstituentFourVector(2), true);
    }
    TLorentzVector zTLV;
    resultZ.getCompositeFourVector(zTLV);
    Zcand->addAnalTLV(TLVType::Constrained, zTLV, true);
    
    m_outTree->updateFloatVar("mZ_constrained", Zcand->getAnalTLV(TLVType::Constrained).M()/1000);
    
    if(Zcand->hasFSR())
    {
        m_outTree->updateFloatVar("fsr_pt_constrained", Zcand->getFSR()->getAnalTLV(TLVType::Constrained).Pt()/1000);
    }
    
}

ZMassConstraint::ConstraintFitInput CalculateVar3l::getZMCInput(ParticleDilepton* diLep, Bool_t skipFSR)
{
    ZMassConstraint::ConstraintFitInput input;
    
    // Add the particles
    for(Int_t i = 0; i < diLep->getLepSize(); i++)
    {
        ParticleVar* temp = diLep->getLep(i);
        
        if(temp->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* mu = dynamic_cast<const xAOD::Muon*>(temp->getParticle());
            ZMassConstraint::MassConstraintMuonType muType = ZMassConstraint::isCombMCMT;
            m_massConstraint->addParticle(*mu, input, muType);
        }
        else if(temp->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron* el = dynamic_cast<const xAOD::Electron*>(temp->getParticle());
            double el_E_resol = m_energyRescaler->getResolution(*el) * el->e();
            
            //LOG(logDEBUG)<<"Particle i: "<<i<<" Electron Resolution: "<<el_E_resol<<" calo E: "<<el->e()<<" calo eta: "<<el->caloCluster()->eta();
            
            m_massConstraint->addParticle(*el, el_E_resol, input);
        }
        else
        {
            LOG(logERROR)<<"Particle Type ("<<temp->getPartType()<<") not supported for ZMC";
            exit(1);
        }
    }
    
    // If there is a FSR particle
    if(diLep->hasFSR() && !skipFSR)
    {
        ParticleVar* fsr = diLep->getFSR();
        LOG(logDEBUG)<<"Adding FSR";
        // FSR TLV is created from the candidate information, and not the IParticle
        m_massConstraint->addFSRParticle(*fsr->getParticle(), fsr->getAnalTLV(TLVType::Unconstrained), input);
    }
    
    return input;
}



/*
void CalculateVar3l::fillFidJetVars()
{
    if(!m_isJetFidFilled)
    {
        // Just return gracefully, not all analysis need fiducial jets
        return;
    }
    

    m_outTree->updateIntVar("n_jets_fid", m_fidJetList.size());
    
    Int_t iLeadingJet = -1;
    Float_t leadingJetPt = -9999;
    
    // Get the leading Jet
    for(Int_t i = 0; i < (Int_t) m_fidJetList.size(); i++)
    {
        if(m_fidJetList[i]->getTLV().Pt() > leadingJetPt)
        {
            leadingJetPt = m_fidJetList[i]->getTLV().Pt();
            iLeadingJet = i;
        }
    }
    
    if (iLeadingJet != -1)
    {
        m_outTree->updateFloatVar("leading_jet_pt_fid", m_fidJetList[iLeadingJet]->getTLV().Pt()/1000);
    }
}





void CalculateVar3l::fillFSRVars()
{
    vector< FSR::FsrCandidate> candidateVec;
    
    fsrType::fsrType fsrTypeVar = fsrType::noFSR;
    
    // Backup the FSR vars
    m_ZplusL->addAnalTLV(TLVType::FSR, m_ZplusL->getTLV(), true);
    m_ZplusL->getZ1()->addAnalTLV(TLVType::FSR, m_ZplusL->getZ1()->getTLV(), true);
    m_ZplusL->getZ2()->addAnalTLV(TLVType::FSR, m_ZplusL->getZ2()->getTLV(), true);
    
    if((m_phCont == 0) || (m_elCont == 0))
    {
        LOG(logERROR)<<"Calibrated el and ph container not set for FSR";
        exit(1);
    }
    
    
    // Getting the FSR Photon
    for (Int_t i = 0; i < (Int_t) m_ZplusL->getLepSize(); i++)
    {
        FSR::FsrCandidate cand;
        candidateVec.push_back(cand);
        
        if(m_ZplusL->getLep(i)->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* temp = dynamic_cast<const xAOD::Muon*> (m_ZplusL->getLep(i)->getParticle());
            if(temp->muonType() == xAOD::Muon::MuonStandAlone) continue;
            else if (temp->muonType() == xAOD::Muon::CaloTagged) continue;
            
            if(m_fsrTool->getFsrPhoton(m_ZplusL->getLep(i)->getParticle(), cand, m_phCont, m_elCont))
            {
                LOG(logDEBUG) <<"Found FSR candidate for muon "<<i;
                LOG(logDEBUG) <<"Candidate Et: "<<cand.Et<<" eta: "<<cand.eta<< " deltaR: "<<cand.deltaR<<" type: "<<cand.type;
            }
        }
        else if(m_ZplusL->getLep(i)->getPartType() == ParticleType::Electron)
        {
            if(m_fsrTool->getFsrPhoton(m_ZplusL->getLep(i)->getParticle(), cand, m_phCont, m_elCont))
            {
                LOG(logDEBUG) <<"Found FSR candidate for electron "<< i;
            }
        }
        if(cand.particle) cand.particle->auxdecor<int>("associated_lep_fsr") = (int) i;
        candidateVec[i] = cand;
    }
    
    Bool_t passFSRCollinear = false;
    Bool_t passFSRFar = false;
    
    
    // Collinear only happens for 4mu or 2mu2el
    if(m_ZplusL->getQuadType() == QuadleptonType::_4mu || m_ZplusL->getQuadType() == QuadleptonType::_2mu2e)
    {
        Double_t higestEt = -99999;
        FSR::FsrCandidate candidate;
        Bool_t isFSR = false;
        
        // Look at just the first two FSR and find the highest cluster Et fsr
        for(Int_t i = 0; i < 2; i++)
        {
            FSR::FsrCandidate tempCandidate = candidateVec[i];
            
            // Find the higest Et collinear photon on the cluster
            if(tempCandidate.Et != -1 && tempCandidate.Et > higestEt && tempCandidate.deltaR <= 0.15)
            {
                higestEt = tempCandidate.Et;
                candidate = tempCandidate;
                isFSR = true;
            }
        }
        
        LOG(logDEBUG) <<"FSR colinear candidate Passed the deltaR cut";
        LOG(logDEBUG) <<"Et: "<<higestEt;
        
        // if FSR found, then do the checks associated with Z1 for the collinear FSR
        if(isFSR)
        {
            if((m_ZplusL->getZ1()->getTLV().M() < 89*1000) && (m_ZplusL->getZ1()->getTLV().M() > 66*1000))
            {
                LOG(logDEBUG) << "FSR collinear candidate passed the Z1 mass cut";
                
                TLorentzVector momFSR;
                momFSR.SetPtEtaPhiM(candidate.Et,candidate.eta,candidate.phi, 0.0);
                
                Double_t combMass = (m_ZplusL->getZ1()->getLepOne()->getTLV()
                                     + m_ZplusL->getZ1()->getLepTwo()->getTLV()
                                     + momFSR).M();
                if(combMass < 100*1000)
                {
                    LOG(logDEBUG)<<"FSR collinear candidate passed the combined mass cut";
                    passFSRCollinear = true;
                    addFSRCandidate(candidate, 1);
                    fsrTypeVar = fsrType::collFSRZ1mumu;
                    
                }
            }
        }
    }
    // If no collinear FSR has been found
    if(!passFSRCollinear)
    {
        Double_t higestEt = -99999;
        FSR::FsrCandidate candidate;
        Bool_t isFSR = false;
        // Loop over all the candidates and find the highest Et cluster far FSR
        for(Int_t i = 0; i < (Int_t) candidateVec.size(); i++)
        {
            FSR::FsrCandidate tempCandidate = candidateVec[i];
            
            // Find the higest Et far photon on the cluster
            if(tempCandidate.Et != -1 && tempCandidate.Et > higestEt && tempCandidate.deltaR > 0.15)
            {
                higestEt = tempCandidate.Et;
                candidate = tempCandidate;
                isFSR = true;
            }
        }
        
        // If there is such a FSR candidate
        if(isFSR)
        {
            LOG(logDEBUG)<<"FSR far candidate exists";
            
            //cout<<"There is a candidate Far FSR"<<endl;
            TLorentzVector momFSR;
            momFSR.SetPtEtaPhiM(candidate.Et,candidate.eta,candidate.phi, 0.0);
            
            // Delta R cut: Ensure that deltaR > 0.15 for all the leptons in the quadruplet
            // Sortof the opposite logic here
            Bool_t deltaRCut = false;
            for(Int_t i = 0; i < (Int_t) m_ZplusL->getLepSize(); i++)
            {
                if(momFSR.DeltaR(m_ZplusL->getLep(i)->getTLV()) < 0.15) deltaRCut = true;
            }
            // If deltaR cut has been pases
            if(!deltaRCut)
            {
                
                LOG(logDEBUG)<<"FSR far candidate passed Delta R cut";
                
                //cout<<"Passed Delta R cut"<<endl;
                Double_t deltaZ1Mass = 999999;
                Double_t deltaZ2Mass = 999999;
                // if the dilepton mass is less than 81 GeV, find how much the FSR move the mass close to
                // Z pole mass... 100 GeV limit there as well
                if(m_ZplusL->getZ1()->getTLV().M() < 81*1000)
                {
                    TLorentzVector combined = m_ZplusL->getZ1()->getTLV() + momFSR;
                    if(combined.M() < 100 * 1000) deltaZ1Mass = fabs(combined.M() - pdgZMass);
                }
                if(m_ZplusL->getZ2()->getTLV().M() < 81*1000)
                {
                    TLorentzVector combined = m_ZplusL->getZ2()->getTLV() + momFSR;
                    if(combined.M() < 100 * 1000) deltaZ2Mass = fabs(combined.M() - pdgZMass);
                    if(m_ZplusL->getTLV().M() < 190*1000) deltaZ2Mass = 999999;
                }
                LOG(logDEBUG)<<"deltaZ1Mass: "<<deltaZ1Mass<<" deltaZ2Mass: "<<deltaZ2Mass;
                
                // Figuring out which dilepton to associate the far FSR photon with
                if(deltaZ1Mass < deltaZ2Mass && deltaZ1Mass != 999999)
                {
                    addFSRCandidate(candidate, 1);
                    passFSRFar = true;
                    fsrTypeVar = fsrType::farFSRZ1;
                    LOG(logDEBUG)<<"Far FSR Attached to Z1";
                }
                else if (deltaZ2Mass < deltaZ1Mass && deltaZ2Mass != 999999)
                {
                    addFSRCandidate(candidate, 2);
                    passFSRFar = true;
                    fsrTypeVar = fsrType::farFSRZ2;
                    LOG(logDEBUG)<<"Far FSR attached to Z2";
                }
            }
        }
    }
    
    if(passFSRCollinear){ LOG(logDEBUG)<<"Colinear FSR event"; }
    if(passFSRFar){ LOG(logDEBUG)<<"Far FSR event"; }
    
    Double_t m4lFSR = m_ZplusL->getAnalTLV(TLVType::FSR).M()/1000;
    Double_t mZ1FSR = m_ZplusL->getZ1()->getAnalTLV(TLVType::FSR).M()/1000;
    Double_t mZ2FSR = m_ZplusL->getZ2()->getAnalTLV(TLVType::FSR).M()/1000;
    
    m_outTree->updateFloatVar("mZ1_fsr", mZ1FSR);
    m_outTree->updateFloatVar("mZ2_fsr", mZ2FSR);
    m_outTree->updateFloatVar("m4l_fsr", m4lFSR);
    m_outTree->updateIntVar("fsr_type", (int) fsrTypeVar);
    if(m_ZplusL->getZ1()->hasFSR())
    {
        m_outTree->updateFloatVar("fsr_pt", m_ZplusL->getZ1()->getFSR()->getAnalTLV(TLVType::Unconstrained).Pt()/1000);
        m_outTree->updateFloatVar("fsr_eta", m_ZplusL->getZ1()->getFSR()->getAnalTLV(TLVType::Unconstrained).Eta());
        m_outTree->updateFloatVar("fsr_phi", m_ZplusL->getZ1()->getFSR()->getAnalTLV(TLVType::Unconstrained).Phi());
        m_outTree->updateIntVar("fsr_associated_lepton", m_ZplusL->getZ1()->getFSR()->getParticle()->auxdecor<int>("associated_lep_fsr"));
    }
    else if(m_ZplusL->getZ2()->hasFSR())
    {
        m_outTree->updateFloatVar("fsr_pt", m_ZplusL->getZ2()->getFSR()->getAnalTLV(TLVType::Unconstrained).Pt()/1000);
        m_outTree->updateFloatVar("fsr_eta", m_ZplusL->getZ2()->getFSR()->getAnalTLV(TLVType::Unconstrained).Eta());
        m_outTree->updateFloatVar("fsr_phi", m_ZplusL->getZ2()->getFSR()->getAnalTLV(TLVType::Unconstrained).Phi());
        m_outTree->updateIntVar("fsr_associated_lepton", m_ZplusL->getZ2()->getFSR()->getParticle()->auxdecor<int>("associated_lep_fsr"));
    }
}



// Categorization
void CalculateVar3l::fillCategory()
{
    // Fill the jet var before
    fillJetVars();
    
    if (m_jetList.size() >= 2 && !(m_leadingJet || m_subLeadingJet))
    {
        LOG(logERROR)<<"FillCategory: nJet >= 2 but no leading or subleading jet";
        exit(1);
    }
    
    Bool_t nJets2 = false;
    Bool_t Mjj40_130 = false;
    Bool_t Mjj130 = false;
    Bool_t isolatedLep = false;
    Bool_t hadBDTCut = false;
    
    if(m_jetList.size() >= 2)
    {
        nJets2 = true;
        const xAOD::Jet* leadingJet = dynamic_cast<const xAOD::Jet*>(m_leadingJet->getParticle());
        const xAOD::Jet* subleadingJet = dynamic_cast<const xAOD::Jet*>(m_subLeadingJet->getParticle());
        
        TLorentzVector sumJet = leadingJet->p4() + subleadingJet->p4();
        
        if(sumJet.M() > 130*1000) Mjj130 = true;
        if(sumJet.M() > 40*1000 && sumJet.M() < 130*1000) Mjj40_130 = true;
        //LOG(logDEBUG)<<"Category: diJet mass: "<<sumJet.M();
        m_catDisTool->setInputs(leadingJet, subleadingJet);
        
        m_outTree->updateFloatVar("BDT_discriminant_VBF", m_catDisTool->Get_VBFDiscriminant_Output());
        m_outTree->updateFloatVar("BDT_discriminant_HadVH", m_catDisTool->Get_HadVHDiscriminant_Output());
        
        hadBDTCut = m_catDisTool->Pass_HadVHDiscriminant();
    }
    
    // Extra Lepton
    for (auto* lep: m_elList)
    {
        if(isGoodExtraLepton(lep)) isolatedLep = true;
    }
    for (auto* lep: m_muList)
    {
        if(isGoodExtraLepton(lep)) isolatedLep = true;
    }
    
    prodType::prodType currProductionType = prodType::ggF;
    
    
    //LOG(logDEBUG)<<"Category: nJets: "<<nJets2<<" Mjj130: "<<Mjj130;

    // Final
    if(nJets2 && Mjj130) currProductionType = prodType::VBF;
    else if(nJets2 && Mjj40_130 && hadBDTCut) currProductionType = prodType::VHHad;
    else if(isolatedLep) currProductionType = prodType::VHLep;
    else currProductionType = prodType::ggF;
    
    
    m_outTree->updateIntVar("prod_type", currProductionType);
    
    quadType::quadType currQuadType = quadType::other;
    
    if(m_ZplusL->getQuadType() == QuadleptonType::_4mu) currQuadType = quadType::_4mu;
    else if(m_ZplusL->getQuadType() == QuadleptonType::_2mu2e) currQuadType = quadType::_2mu2e;
    else if(m_ZplusL->getQuadType() == QuadleptonType::_2e2mu) currQuadType = quadType::_2e2mu;
    else if(m_ZplusL->getQuadType() == QuadleptonType::_4e) currQuadType = quadType::_4e;
    else currQuadType = quadType::other;
    
    m_outTree->updateIntVar("event_type", currQuadType);
}

Bool_t CalculateVar3l::isGoodExtraLepton(ParticleVar* lep)
{
    if(m_ZplusL->isOverlap(lep)) return false;
    
    if(!(lep->getTLV().Pt() > 8*1000)) return false;
    
    vector<ParticleVar*> vecLep;
    for(Int_t i = 0; i < m_ZplusL->getLepSize(); i++)
    {
        vecLep.push_back(m_ZplusL->getLep(i));
    }
    vecLep.push_back(lep);
    
    // deltaR Cut
    if(!m_cutQuad->cutDeltaR(vecLep)) return false;
    
    // Iso Cut
    m_cutQuad->cutIsolation(vecLep);
    if(!lep->getParticle()->auxdecor< int >("isoCut")) return false;
    
    // D0Sig
    m_cutQuad->cutD0Sig(vecLep);
    if(!lep->getParticle()->auxdecor< int >("passD0Sig")) return false;
    
    
    // In AnalysisBkg, the input electron might be very loose.
    // So we need to protect against that, just in case
    if(lep->getPartType() == ParticleType::Electron)
    {
        if(!lep->getParticle()->auxdecor< int >("looseID")) return false;
    }
    
    
    
    // Calo SA muon
    Int_t caloSACount = 0;
    for(Int_t i = 0; i < (Int_t) vecLep.size(); i++)
    {
        if(vecLep[i]->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* temp = dynamic_cast<const xAOD::Muon*> (vecLep[i]->getParticle());
            if(temp->muonType() == xAOD::Muon::MuonStandAlone) caloSACount++;
            else if (temp->muonType() == xAOD::Muon::CaloTagged) caloSACount++;
        }
    }
    
    if(caloSACount > 1) return false;
    
    vecLep.clear();
    return true;
}

void CalculateVar3l::fillTruthMatched() {
    
    if(!m_eventCont->isMC) return;
    
    vector<const xAOD::TruthParticle*> tps = m_truthHelper->getRecoMatchTruth(m_ZplusL);
    
    TString VarBaseName[4] = {"Z1_lepplus", "Z1_lepminus", "Z2_lepplus", "Z2_lepminus"};
    
    for(Int_t i = 0; i < (Int_t) tps.size(); i++)
    {
        if(tps[i])
        {
            TLorentzVector l = tps[i]->p4();
            m_outTree->updateFloatVar((VarBaseName[i]+"_pt_truth_matched_bare").Data() , l.Pt() / 1000.);
            m_outTree->updateFloatVar((VarBaseName[i]+"_eta_truth_matched_bare").Data(), l.Eta());
            m_outTree->updateFloatVar((VarBaseName[i]+"_phi_truth_matched_bare").Data(), l.Phi());
            m_outTree->updateFloatVar((VarBaseName[i]+"_m_truth_matched_bare").Data(), l.M() / 1000.);
            
            //LOG(logDEBUG)<<"Particle i: "<<i<<" match pT: "<<l.Pt()/1000<<" eta: "<<l.Eta()<<" phi: "<<l.Phi();
        }
        else
        {
            LOG(logDEBUG)<<"No reco match";
        }
    }
    if (tps[0] && tps[1])
    {
        TLorentzVector z1 = tps[0]->p4() + tps[1]->p4();
        m_outTree->updateFloatVar("mZ1_truth_matched_bare", z1.M() / 1000.);
    }
    if (tps[2] && tps[3])
    {
        TLorentzVector z2 = tps[2]->p4() + tps[3]->p4();
        m_outTree->updateFloatVar("mZ2_truth_matched_bare", z2.M() / 1000.);
    }
    if (tps[0] && tps[1] && tps[2] && tps[3])
    {
        TLorentzVector q = tps[0]->p4() + tps[1]->p4() + tps[2]->p4() + tps[3]->p4();
        m_outTree->updateFloatVar("m4l_truth_matched_bare", q.M() / 1000.);
        m_outTree->updateFloatVar("pt4l_truth_matched_bare", q.Pt() / 1000.);
        m_outTree->updateFloatVar("eta4l_truth_matched_bare", q.Eta());
    }
}

void CalculateVar3l::fillTruth()
{
    if(!m_eventCont->isMC) return;
    
    ParticleQuadlepton* truthBareHiggs = m_truthHelper->getBareQuadlepton();
    ParticleQuadlepton* truthBornHiggs = m_truthHelper->getBornQuadlepton(truthBareHiggs);
    
    if(!truthBornHiggs) return;
    
    if(m_eventCont->isDebug)
    {
        LOG(logDEBUG)<<"Truth Bare Higgs";
        truthBareHiggs->printDebug();
        LOG(logDEBUG)<<"Truth Born Higgs";
        truthBornHiggs->printDebug();
    }
    
    TLorentzVector tlv1, tlv2, tlv3, tlv4, z1, z2, q;
    q = truthBornHiggs->getTLV();
    z1 = truthBornHiggs->getZ1()->getTLV();
    z2 = truthBornHiggs->getZ2()->getTLV();
    tlv1 = truthBornHiggs->getLep(0)->getTLV();
    tlv2 = truthBornHiggs->getLep(1)->getTLV();
    tlv3 = truthBornHiggs->getLep(2)->getTLV();
    tlv4 = truthBornHiggs->getLep(3)->getTLV();
    
    m_outTree->updateFloatVar("m4l_truth_born", q.M() / 1000.);
    m_outTree->updateFloatVar("mZ1_truth_born", z1.M() / 1000.);
    m_outTree->updateFloatVar("mZ2_truth_born", z2.M() / 1000.);
    
    m_outTree->updateFloatVar("pt4l_truth_born", q.Pt() / 1000.);
    m_outTree->updateFloatVar("eta4l_truth_born", q.Eta());
    
    m_outTree->updateFloatVar("Z1_lepplus_pt_truth_born", tlv1.Pt() / 1000.);
    m_outTree->updateFloatVar("Z1_lepminus_pt_truth_born", tlv2.Pt() / 1000.);
    m_outTree->updateFloatVar("Z2_lepplus_pt_truth_born", tlv3.Pt() / 1000.);
    m_outTree->updateFloatVar("Z2_lepminus_pt_truth_born", tlv4.Pt() / 1000.);
    
    m_outTree->updateFloatVar("Z1_lepplus_eta_truth_born", tlv1.Eta());
    m_outTree->updateFloatVar("Z1_lepminus_eta_truth_born", tlv2.Eta());
    m_outTree->updateFloatVar("Z2_lepplus_eta_truth_born", tlv3.Eta());
    m_outTree->updateFloatVar("Z2_lepminus_eta_truth_born", tlv4.Eta());
    
    m_outTree->updateFloatVar("Z1_lepplus_phi_truth_born", tlv1.Phi());
    m_outTree->updateFloatVar("Z1_lepminus_phi_truth_born", tlv2.Phi());
    m_outTree->updateFloatVar("Z2_lepplus_phi_truth_born", tlv3.Phi());
    m_outTree->updateFloatVar("Z2_lepminus_phi_truth_born", tlv4.Phi());
    
    m_outTree->updateFloatVar("Z1_lepplus_m_truth_born", tlv1.M() / 1000.);
    m_outTree->updateFloatVar("Z1_lepminus_m_truth_born", tlv2.M() / 1000.);
    m_outTree->updateFloatVar("Z2_lepplus_m_truth_born", tlv3.M() / 1000.);
    m_outTree->updateFloatVar("Z2_lepminus_m_truth_born", tlv4.M() / 1000.);
    
    m_outTree->updateIntVar("truth_event_type", m_truthHelper->getTruthHiggsType());
}


void CalculateVar3l::fillAngularVar()
{
    Float_t cthstr = -999;
    Float_t phi1 = -999;
    Float_t cth1 = -999;
    Float_t cth2 = -999;
    Float_t phi = -999;
    
    
    // This function requires z1 lep neg, z1 lep plus, z2 lep neg, z2 lep plus
    // weird ordering... sigh
    HZZUtils::helicityAngles(m_ZplusL->getLep(1)->getTLV(),
                             m_ZplusL->getLep(0)->getTLV(),
                             m_ZplusL->getLep(3)->getTLV(),
                             m_ZplusL->getLep(2)->getTLV(),
                             cthstr, phi1, cth1, cth2, phi);
    
    m_outTree->updateFloatVar("cthstr", cthstr);
    m_outTree->updateFloatVar("phi1", phi1);
    m_outTree->updateFloatVar("cth1", cth1);
    m_outTree->updateFloatVar("cth2", cth2);
    m_outTree->updateFloatVar("phi", phi);
    
    
    
}
*/

bool CalculateVar3l::sortParticleVarPt (ParticleVar* i ,ParticleVar*j)
{
    return i->getTLV().Pt() > j->getTLV().Pt();
}
