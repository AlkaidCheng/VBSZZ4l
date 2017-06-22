#include "H4lCutFlow/ApplyWeight4l.h"
using namespace std;

ApplyWeight4l::ApplyWeight4l(EventContainer* eventcont):ApplyWeight(eventcont)
{
    // Weights we need to apply

    m_truthHelper = new TruthHelper(m_eventCont);
    myMuons = new xAOD::MuonContainer(SG::VIEW_ELEMENTS);

    m_trigger = 0;

    // retrieve the ID/Reco SF
    m_egSFClassID = ToolHandle<IAsgElectronEfficiencyCorrectionTool>("IDSFTool");
    m_egSFClassReco = ToolHandle<IAsgElectronEfficiencyCorrectionTool>("RecoSFTool");
    m_egSFClassIso = ToolHandle<IAsgElectronEfficiencyCorrectionTool>("ElIsoSFTool");
    if(m_egSFClassID.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve IAsgElectronEfficiencyCorrectionTool ID";
        exit(1);
    }
    if(m_egSFClassReco.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve IEgammaCalibrationAndSmearingTool Reco";
        exit(1);
    }
    if(m_egSFClassIso.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve IEgammaCalibrationAndSmearingTool Iso";
        exit(1);
    }

    // retrieve the muon SF
    m_effTool = ToolHandle<CP::IMuonEfficiencyScaleFactors>("MuonSFClass");
    m_effIsoTool = ToolHandle<CP::IMuonEfficiencyScaleFactors>("MuonSFIso");
    m_effd0Tool = ToolHandle<CP::IMuonEfficiencyScaleFactors>("MuonSFd0");
    if(m_effTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve IMuonEfficiencyScaleFactors SF";
        exit(1);
    }
    if(m_effIsoTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve IMuonEfficiencyScaleFactors Iso";
        exit(1);
    }
    if(m_effd0Tool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve IMuonEfficiencyScaleFactors d0";
        exit(1);
    }
    m_NLOreweighting = ToolHandle<INLOreweighting>("NLOreweighting");
    if(m_NLOreweighting.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve INLOreweighting";
        exit(1);
    }

    m_pmgSherpaWeightTool = ToolHandle<IWeightTool>("PMGSherpa22VJetsWeightTool");
    if(m_pmgSherpaWeightTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve IPMGWeightTool";
        exit(1);
    }
    m_jetJVTEffTool = ToolHandle<CP::IJetJvtEfficiency>("JetJvtEfficiency");
    if(m_jetJVTEffTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve IJetJvtEfficiency";
        exit(1);
    }
    m_jetFJVTEffTool = ToolHandle<CP::IJetJvtEfficiency>("JetFJvtEfficiency");
    if(m_jetFJVTEffTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve forward IJetJvtEfficiency";
        exit(1);
    }

    m_btagEffTool = ToolHandle<IBTaggingEfficiencyTool>("BTagEffTool_70");
    if(m_btagEffTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight4l::ApplyWeight4l() - cannot retrieve IBTaggingEfficiencyTool";
        exit(1);
    }


    m_jetCont = new xAOD::IParticleContainer(SG::VIEW_ELEMENTS);


    double weightMax=100.0;
    m_higgsMCtool = new xAOD::HiggsWeightTool( "HiggsWeightTool" );
    m_higgsMCtool->setProperty( "OutputLevel", MSG::DEBUG ).ignore();
    m_higgsMCtool->setProperty( "RequireFinite", true ).ignore();
    m_higgsMCtool->setProperty( "WeightCutOff", weightMax ).ignore();
    if (m_eventCont->mcChannelNumber == 345060) m_higgsMCtool->setProperty("ForceNNLOPS",true).ignore();
    else if (m_eventCont->mcChannelNumber == 344235) m_higgsMCtool->setProperty("ForceVBF",true).ignore();
    else if (m_eventCont->mcChannelNumber == 345038 || m_eventCont->mcChannelNumber == 345039 || m_eventCont->mcChannelNumber == 345040) 
        m_higgsMCtool->setProperty("ForceVH",true).ignore();
    else m_higgsMCtool->setProperty("ForceNNLOPS",true).ignore();
    m_higgsMCtool->initialize().ignore();
}

ApplyWeight4l::~ApplyWeight4l()
{
    if(m_truthHelper)   delete m_truthHelper;
    if(myMuons)         delete myMuons;
}

// Below are used for cutflow weight
Double_t ApplyWeight4l::getEventWeight()
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;

    Double_t weight = 1;

    weight *= getMCWeight();
    weight *= getPileUpWeight();

    return weight;
}

Double_t ApplyWeight4l::getHiggsWeight(const LepCombBase* combLep)
{
    if(!m_eventCont->doSmear) return 1;
    if(!m_eventCont->isMC) return 1;

    Double_t weight = 1;
    // Tigger Eff

    // Lep Eff
    weight *= getWeightCorr(combLep);

    return weight;
}

Double_t ApplyWeight4l::getTotalWeight(const LepCombBase* combLep)
{
    return getHiggsWeight(combLep);
}

// This will fill all the weights for the event
// Will fill in the cross-section, lumi and trig eff and other things
void ApplyWeight4l::fillWeight(const LepCombBase* combLep)
{
    m_eventCont->outTree->updateVar<double>("w_xs", getCrossSection());
    m_eventCont->outTree->updateVar<double>("w_br", getBranchingRatio(combLep));
    m_eventCont->outTree->updateVar<double>("w_lumi", getLumi());
    m_eventCont->outTree->updateVar<double>("w_MCw", getMCWeight());
    m_eventCont->outTree->updateVar<double>("w_EW", getEWCorr());
    m_eventCont->outTree->updateVar<double>("w_EWNLO", getEWNLOCorr());
    m_eventCont->outTree->updateVar<double>("w_QCDNNLO", getEWQCDCorr());
    m_eventCont->outTree->updateVar<double>("w_lepEff", getLepEff(combLep));
    m_eventCont->outTree->updateVar<double>("w_pileup", getPileUpWeight());
    m_eventCont->outTree->updateVar<double>("w_jetJvt_SF", getJetJVTSF());
    m_eventCont->outTree->updateVar<double>("w_triggerSF", getTriggerSF(combLep));
    m_eventCont->outTree->updateVar<double>("w_sherpaJet", getSherpaCorr());
    m_eventCont->outTree->updateVar<double>("w_sherpaLep", getSherpaReweight());
    m_eventCont->outTree->updateVar<double>("w_btagEff", getBtagSF());

    m_eventCont->outTree->updateVar<double>("weight_sampleoverlap", getSampleOlpWeight());
    m_eventCont->outTree->updateVar<double>("weight_corr", getWeightCorr(combLep));
    m_eventCont->outTree->updateVar<double>("weight_lumi", getWeightLumi(combLep));

    // weight for no jet info
    double weight = getWeight(combLep);
    m_eventCont->outTree->updateVar<double>("weight", weight);


    // To delete
    //// Weight for jets but no btag
    //weight *= getJetJVTSF();
    //m_eventCont->outTree->updateVar<double>("weight_jet", weight);

    //// weight for jet with bTag
    //weight *= getBtagSF();
    //m_eventCont->outTree->updateVar<double>("weight_bTag", weight);



    LOG(logDEBUG)<<"Weights: event number: "<<m_eventCont->eventInfo->eventNumber();
    LOG(logDEBUG)<<"Random Run number: "<<m_eventCont->eventInfo->auxdecor<unsigned int>("RandomRunNumber");
    LOG(logDEBUG)<<"w_xs: "<<m_eventCont->outTree->getDoubleVar("w_xs");
    LOG(logDEBUG)<<"w_br: "<<m_eventCont->outTree->getDoubleVar("w_br");
    LOG(logDEBUG)<<"w_lumi: "<<m_eventCont->outTree->getDoubleVar("w_lumi");
    LOG(logDEBUG)<<"w_MCw: "<<m_eventCont->outTree->getDoubleVar("w_MCw");
    LOG(logDEBUG)<<"w_lepEff: "<<m_eventCont->outTree->getDoubleVar("w_lepEff");
    LOG(logDEBUG)<<"w_EW: "<<m_eventCont->outTree->getDoubleVar("w_EW");
    for(Int_t i = 0; i < (Int_t) combLep->getLepSize(); i++)
    {
        if(combLep->getLep(i)->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon *mu_i = dynamic_cast<const xAOD::Muon*>(combLep->getLep(i)->getParticle());
            LOG(logDEBUG)<<"w_lepEff "<<i<<" "<< mu_i->auxdecor< float >( "EfficiencyScaleFactor" );
        }
        else if(combLep->getLep(i)->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron *el_i = dynamic_cast<const xAOD::Electron*>(combLep->getLep(i)->getParticle());
            LOG(logDEBUG)<<"w_lepEff "<<i<<" "<< el_i->auxdecor< float >( "Efficiency" );

        }
    }
    LOG(logDEBUG)<<"w_pileup: "<<m_eventCont->outTree->getDoubleVar("w_pileup");
    LOG(logDEBUG)<<"w_triggerSF: "<<m_eventCont->outTree->getDoubleVar("w_triggerSF");
    LOG(logDEBUG)<<"w_sherpaJet: "<<m_eventCont->outTree->getDoubleVar("w_sherpaJet");
    LOG(logDEBUG)<<"weight_sampleoverlap: "<<m_eventCont->outTree->getDoubleVar("weight_sampleoverlap");
    LOG(logDEBUG)<<"weight_corr: "<<m_eventCont->outTree->getDoubleVar("weight_corr");
    LOG(logDEBUG)<<"weight_lumi: "<<m_eventCont->outTree->getDoubleVar("weight_lumi");

    return;
}


void ApplyWeight4l::fillTheoryVariationWeight()
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return ;
    if(!m_eventCont->isMC) return ;

    // Check if this cross-section is avaliable in the tool
    Int_t DSID = m_eventCont->getDSID();
    // Some truth derivation are weird... they store DSID in runNumber
    // Max provided this fix
    // if (m_eventCont->m_isDAODTRUTH && DSID == 0)
    // {
    //     DSID = m_eventCont->eventInfo->runNumber();
    // }
    //get the map that relates the variation to the index in mcEventWeights
    std::map<std::string, int> weight_vars = m_varTool->execute(DSID);

    float weight_nom = getMCWeight();
    std::vector< float > weights = m_eventCont->eventInfo->mcEventWeights();
    const xAOD::TruthEventContainer* truthEvent = 0;
    if(m_eventCont->m_isAOD){
        m_eventCont->getEvent()->retrieve( truthEvent, "TruthEvents" ).isSuccess();
        xAOD::TruthEventContainer::const_iterator itTruth = truthEvent->begin();
        weights = (*itTruth)->weights();
    }

    std::map<std::string, int>::iterator mapIt;
    for ( mapIt = weight_vars.begin(); mapIt != weight_vars.end(); mapIt++ )
    {
        std::string w_name = ("weight_var_th_"+ m_varTool->getTheorySysName(mapIt->first)).Data(); //get name of variation
        float weight_ratio = weights[mapIt->second]; //get weight of variation
        if(weight_nom == 0 ) weight_ratio = 0;
        else weight_ratio = weight_ratio/weight_nom;

        //LOG(logINFO)<<"mapIt->first: "<<mapIt->first<<" "<<m_eventCont->outTree->getTheorySysName(mapIt->first)<<" ratio: "<<weight_ratio;

        float var_weight = weight_ratio;
        m_eventCont->outTree->updateVar<double>(w_name, var_weight);
    }


    // if the information is not there, just return
    if (!m_eventCont->eventInfo->isAvailable<int>("HTXS_Njets_pTjet30")) return;
    int HTXS_Njets30    = m_eventCont->eventInfo->auxdata<int>("HTXS_Njets_pTjet30");
    int HTXS_Stage1     = m_eventCont->eventInfo->auxdata<int>("HTXS_Stage1_Category_pTjet30");
    double HTXS_pTH     = m_eventCont->eventInfo->auxdata<float>("HTXS_Higgs_pt");
    // Access all Higgs weights
    xAOD::HiggsWeights hw = m_higgsMCtool->getHiggsWeights(HTXS_Njets30,HTXS_pTH,HTXS_Stage1);


    // QCD weights
    if (m_eventCont->mcChannelNumber == 345060)
    {

        if( hw.ggF_qcd_stxs.size() != 9)
        {
            LOG(logERROR)<<"ggF QCD theory sys size for ggF_qcd_stxs not equals to 8... something has changed, please check";
            exit(1);
        }

        if( hw.ggF_qcd_2017.size() != 9)
        {
            LOG(logERROR)<<"ggF QCD theory sys size for ggF_qcd_2017 not equals to 8... something has changed, please check";
            exit(1);
        }

        m_eventCont->outTree->updateVar<double>("weight_var_th_qcd_wg1_mu", hw.ggF_qcd_stxs[0]/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_qcd_wg1_res", hw.ggF_qcd_stxs[1]/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_qcd_wg1_mig01", hw.ggF_qcd_stxs[2]/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_qcd_wg1_mig12", hw.ggF_qcd_stxs[3]/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_qcd_wg1_vbf2j", hw.ggF_qcd_stxs[4]/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_qcd_wg1_vbf3j", hw.ggF_qcd_stxs[5]/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_ggF_qcd_stxs_dsig60", hw.ggF_qcd_stxs[6]/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_ggF_qcd_stxs_dsig120", hw.ggF_qcd_stxs[7]/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_ggF_qcd_stxs_dsig200", hw.ggF_qcd_stxs[8]/hw.nominal);


        m_eventCont->outTree->updateVar<double>("weight_var_th_ggF_qcd_2017_pTH60", hw.ggF_qcd_2017[6]/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_ggF_qcd_2017_pTH120", hw.ggF_qcd_2017[7]/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_qcd_wg1_qm_t", hw.ggF_qcd_2017[8]/hw.nominal);

        m_eventCont->outTree->updateVar<double>("weight_var_th_qcd_wg1_qm_b", hw.qcd_wg1_qm_b/hw.nominal);
        m_eventCont->outTree->updateVar<double>("weight_var_th_qcd_wg1_pTH", hw.qcd_wg1_pTH/hw.nominal);
    }
}

void ApplyWeight4l::fillVariationHist()
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return ;
    if(!m_eventCont->isMC) return ;

    // Check if this cross-section is avaliable in the tool
    Int_t DSID = m_eventCont->getDSID();
    // // Some truth derivation are weird... they store DSID in runNumber
    // // Max provided this fix
    // if (m_eventCont->m_isDAODTRUTH && DSID == 0)
    // {
    //     DSID = m_eventCont->eventInfo->runNumber();
    // }
    //get the map that relates the variation to the index in mcEventWeights
    std::map<std::string, int> weight_vars = m_varTool->execute(DSID);

    std::vector< float > weights = m_eventCont->eventInfo->mcEventWeights();
    const xAOD::TruthEventContainer* truthEvent = 0;
    if(m_eventCont->m_isAOD){
        m_eventCont->getEvent()->retrieve( truthEvent, "TruthEvents" ).isSuccess();
        xAOD::TruthEventContainer::const_iterator itTruth = truthEvent->begin();
        weights = (*itTruth)->weights();
    }

    std::map<std::string, int>::iterator mapIt;
    for ( mapIt = weight_vars.begin(); mapIt != weight_vars.end(); mapIt++ )
    {
        int w_index = mapIt->second;; //get index of variation
        float w_var = weights[w_index]; //get weight of variation
        if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("VariationHist", w_index, w_var);
    }
}


// Branching ratio
Double_t ApplyWeight4l::getBranchingRatio(const LepCombBase* combLep) const
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial) ) return 1;
    if(!m_eventCont->isMC) return 1;
    if(m_eventCont->isEFT) return 1; 

    Double_t BR_4l  = 1;
    Double_t BR_2l2l  = 1;

    // If not a signal sample, return 1
    if(m_eventCont->sampleType == SampleType::Background) return 1;

    // No Tau sample
    if(m_eventCont->isNoTau)
    {
        BR_4l = m_brTool->execute(m_eventCont->mHTrue, ColumnBR::br_4e) * 4.;
        BR_2l2l = m_brTool->execute(m_eventCont->mHTrue, ColumnBR::br_2e2mu) * 4. / 2.;
    }
    else
    {
        BR_4l = m_brTool->execute(m_eventCont->mHTrue, ColumnBR::br_4e) * 9.;
        BR_2l2l = m_brTool->execute(m_eventCont->mHTrue, ColumnBR::br_2e2mu) * 9. / 2.;
    }

    QuadleptonType::QuadleptonType quad = m_truthHelper->getTruthHiggsType();


    // If truth isn't found, return the reco type XS
    if(quad == QuadleptonType::NA) 
    {
        if(combLep->getLepSize() == 4)
        {
            const ParticleQuadlepton* quadLepton = dynamic_cast<const ParticleQuadlepton*>(combLep);
            if(quadLepton) quad = quadLepton->getQuadType();
        }

    }

    if(quad == QuadleptonType::_4mu || quad == QuadleptonType::_4e || quad == QuadleptonType::_4tau) return BR_4l;
    else if(quad != QuadleptonType::NA) return BR_2l2l;

    // Worst case senario - the quad is not recognized
    return BR_4l;
}


Double_t ApplyWeight4l::getTriggerSF(const LepCombBase* combLep)
{
    if(!m_eventCont->doSmear) return 1;
    if(!m_eventCont->isMC) return 1;

    // For now return just 1, till we figure out this trigger SF business
    Double_t eff = 1;
    return eff;
}

Double_t ApplyWeight4l::getSampleOlpWeight() const
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial) ) return 1;
    if(!m_eventCont->isMC) return 1;

    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();

    // Check if this cross-section is avaliable in the tool
    Int_t DSID = m_eventCont->getDSID();
    // // Some truth derivation are weird... they store DSID in runNumber
    // // Max provided this fix
    // if (m_eventCont->m_isDAODTRUTH && DSID == 0)
    // {
    //     DSID = m_eventCont->eventInfo->runNumber();
    // }


    return killEvent(DSID, truthCont, true, true);
}


// To get the lepton efficiency
Double_t ApplyWeight4l::getLepEff(const LepCombBase* combLep)
{
    if(!m_eventCont->doSmear) return 1;
    if(!m_eventCont->isMC) return 1;

    fillLepEff(combLep);

    Double_t eff = 1;
    for(Int_t i = 0; i < (Int_t) combLep->getLepSize(); i++)
    {
        if(combLep->getLep(i)->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon *mu_i = dynamic_cast<const xAOD::Muon*>(combLep->getLep(i)->getParticle());
            eff *= mu_i->auxdecor< float >( "EfficiencyScaleFactor" );
        }
        else if(combLep->getLep(i)->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron *el_i = dynamic_cast<const xAOD::Electron*>(combLep->getLep(i)->getParticle());
            eff *= el_i->auxdecor< float >( "Efficiency" );
        }
    }
    return eff;
}


void ApplyWeight4l::fillLepEff(const LepCombBase* combLep)
{
    // Actually calculate the efficiency
    for(Int_t i = 0; i < (Int_t) combLep->getLepSize(); i++)
    {
        if(combLep->getLep(i)->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon *currMuon = dynamic_cast<const xAOD::Muon*>(combLep->getLep(i)->getParticle());

            CP::CorrectionCode errCodeEff = m_effTool->applyEfficiencyScaleFactor(*currMuon);
            CP::CorrectionCode errCodeIso = m_effIsoTool->applyEfficiencyScaleFactor(*currMuon);
            CP::CorrectionCode errCoded0  = m_effd0Tool->applyEfficiencyScaleFactor(*currMuon);

            if(errCodeEff == CP::CorrectionCode::OutOfValidityRange)
            {
                //LOG(logERROR)<<"OutOfValidityRange EfficiencyScaleFactor";                
                currMuon->auxdecor< float >( "EfficiencyScaleFactor" ) = 1;
            }
            else if(errCodeEff != CP::CorrectionCode::Ok)
            {
                LOG(logERROR)<<"Cannot apply scale factors Eff";
                exit(1);
            }

            if(errCodeIso == CP::CorrectionCode::OutOfValidityRange)
            {
                //LOG(logERROR)<<"OutOfValidityRange IsoEfficiencyScaleFactor";                
                currMuon->auxdecor< float >( "IsoEfficiencyScaleFactor" ) = 1;
            }
            else if(errCodeIso != CP::CorrectionCode::Ok)
            {
                LOG(logERROR)<<"Cannot apply scale factors Iso";
                exit(1);
            }
            if(errCoded0 == CP::CorrectionCode::OutOfValidityRange)
            {
                //LOG(logERROR)<<"OutOfValidityRange IPEfficiencyScaleFactor";                
                currMuon->auxdecor< float >( "IPEfficiencyScaleFactor" ) = 1;
            }
            else if(errCoded0 != CP::CorrectionCode::Ok)
            {
                LOG(logERROR)<<"Cannot apply scale factors d0";
                exit(1);
            }

            LOG(logDEBUG)<<"mu Pt: "<<currMuon->pt()
                <<" eta: "<<currMuon->eta()
                <<" phi: "<<currMuon->phi()
                <<" m: "<<currMuon->m()
                <<" SF: "<<currMuon->auxdecor< float >( "EfficiencyScaleFactor" ) 
                <<" ID SF: "<<currMuon->auxdecor< float >( "IsoEfficiencyScaleFactor" ) 
                <<" IP Sf: "<<currMuon->auxdecor< float >( "IPEfficiencyScaleFactor" )
                ;

            currMuon->auxdecor< float >( "EfficiencyScaleFactor" ) = currMuon->auxdecor< float >( "EfficiencyScaleFactor" ) * 
                currMuon->auxdecor< float >( "IsoEfficiencyScaleFactor" ) * 
                currMuon->auxdecor< float >( "IPEfficiencyScaleFactor" );

        }
        else if(combLep->getLep(i)->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron *currElectron = dynamic_cast<const xAOD::Electron*>(combLep->getLep(i)->getParticle());
            if(m_eventCont->doSmear)
            {
                float elEff = 1;
                float cl_eta = currElectron->caloCluster()->etaBE(2);
                float cl_Et = currElectron->pt();

                // To aviod the error messages
                if(fabs(cl_eta) <= 2.47 && cl_Et > 7 * 1000)
                {
                    Double_t IDeff = 1;
                    Double_t recoEff = 1;
                    Double_t isoEff = 1;

                    if(!m_egSFClassID->getEfficiencyScaleFactor(*currElectron, IDeff))
                    {
                        LOG(logERROR)<<"Cannot apply electron SF ID";
                        exit(1);
                    }
                    if(!m_egSFClassReco->getEfficiencyScaleFactor(*currElectron, recoEff))
                    {
                        LOG(logERROR)<<"Cannot apply electron SF Reco";
                        exit(1);
                    }
                    if(!m_egSFClassIso->getEfficiencyScaleFactor(*currElectron, isoEff))
                    {
                        LOG(logERROR)<<"Cannot apply electron SF Iso";
                        exit(1);
                    }

                    elEff = IDeff * recoEff * isoEff;

                    //LOG(logDEBUG)<<"el Pt: "<<currElectron->pt()<<" Reco SF: "<<recoEff<<" ID SF: "<<IDeff<<" Iso Sf: "<<isoEff;
                }
                currElectron->auxdecor<float>("Efficiency") = elEff;

                // Don't apply SF electrons that don't pass LooseID
                if(!currElectron->auxdecor<int>("looseID"))
                {
                    currElectron->auxdecor< float >( "Efficiency" ) = 1;
                }
            }
        }
    }
}

double ApplyWeight4l::getEWCorr()
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;

    ParticleQuadlepton* truthQuad = m_truthHelper->getBornQuadlepton();

    if(!truthQuad) return 1;

    quadType::quadType currQuadType = quadType::other;

    if(truthQuad->getQuadType() == QuadleptonType::_4mu) currQuadType = quadType::_4mu;
    else if(truthQuad->getQuadType() == QuadleptonType::_2mu2e) currQuadType = quadType::_2mu2e;
    else if(truthQuad->getQuadType() == QuadleptonType::_2e2mu) currQuadType = quadType::_2e2mu;
    else if(truthQuad->getQuadType() == QuadleptonType::_4e) currQuadType = quadType::_4e;
    else return 1;


    double weight = 1;;  
    double weightEW = getEWNLOCorr();  
    double weightQCD = getEWQCDCorr();  

    weight = weightQCD * weightEW;

    LOG(logDEBUG) << "quad entering into fillWeightHOQCD";
    LOG(logDEBUG) << "weightQCD: " << weightQCD;
    LOG(logDEBUG) << "weightEW: " << weightEW;

    return weight;
}


double ApplyWeight4l::getEWNLOCorr()
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;

    ParticleQuadlepton* truthQuad = m_truthHelper->getBornQuadlepton();

    if(!truthQuad) return 1;

    quadType::quadType currQuadType = quadType::other;

    if(truthQuad->getQuadType() == QuadleptonType::_4mu) currQuadType = quadType::_4mu;
    else if(truthQuad->getQuadType() == QuadleptonType::_2mu2e) currQuadType = quadType::_2mu2e;
    else if(truthQuad->getQuadType() == QuadleptonType::_2e2mu) currQuadType = quadType::_2e2mu;
    else if(truthQuad->getQuadType() == QuadleptonType::_4e) currQuadType = quadType::_4e;
    else return 1;

    double weightEW = 1;  

    m_NLOreweighting->fillWeightHOEW(truthQuad->getLep(1)->getTLV(),
                                truthQuad->getLep(0)->getTLV(),
                                truthQuad->getLep(3)->getTLV(),
                                truthQuad->getLep(2)->getTLV(),
                                currQuadType,
                                m_eventCont->getDSID(),
                                weightEW).isSuccess();
    //LOG(logDEBUG) << "----------------------------------------------------------";
    //LOG(logDEBUG) << "quad entering into fillWeightHOEW";
    //truthQuad->printDebug();
    return weightEW;
}
double ApplyWeight4l::getEWQCDCorr()
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;

    ParticleQuadlepton* truthQuad = m_truthHelper->getBornQuadlepton();
    if(!truthQuad) return 1;

    quadType::quadType currQuadType = quadType::other;

    if(truthQuad->getQuadType() == QuadleptonType::_4mu) currQuadType = quadType::_4mu;
    else if(truthQuad->getQuadType() == QuadleptonType::_2mu2e) currQuadType = quadType::_2mu2e;
    else if(truthQuad->getQuadType() == QuadleptonType::_2e2mu) currQuadType = quadType::_2e2mu;
    else if(truthQuad->getQuadType() == QuadleptonType::_4e) currQuadType = quadType::_4e;
    else return 1;

    double weightQCD = 1;  
    m_NLOreweighting->fillWeightHOQCD(truthQuad->getLep(1)->getTLV(),
            truthQuad->getLep(0)->getTLV(),
            truthQuad->getLep(3)->getTLV(),
            truthQuad->getLep(2)->getTLV(),
            currQuadType,
            m_eventCont->getDSID(),
            weightQCD).isSuccess();

    return weightQCD;
}


double ApplyWeight4l::getSherpaCorr()
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;

    int runNumber = m_eventCont->getDSID();
    // if (m_eventCont->m_isDAODTRUTH && DSID == 0)
    // {
    //     DSID = m_eventCont->eventInfo->runNumber();
    // }

    // If not the sherpa weight, return 
    if(!((runNumber >= 363103 && runNumber <= 363411)))
    {
        return 1;
    }

    return m_pmgSherpaWeightTool->getWeight();
}


double ApplyWeight4l::getSherpaReweight()
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;
    if (!(m_eventCont->m_currGenerator == Generator::Sherpa)) return 1;

    int runNumber = m_eventCont->getDSID();
    if((runNumber == 345107) || (runNumber == 345108) || (runNumber == 361063) || (runNumber == 361090) || (runNumber == 363042) || (runNumber == 363043) || (runNumber == 363044) || (runNumber == 363045) || (runNumber == 363046) || (runNumber == 363047) || (runNumber == 363484) || (runNumber == 363485) || (runNumber == 363490) || (runNumber == 363495) || (runNumber == 363716))
    {
        ParticleQuadlepton* truthQuad = m_truthHelper->getBornQuadlepton(); 

        static float sherpa4eWeight[7]  = { 0.8181, 0.9402, 0.9579, 0.9580, 0.9607, 0.9651, 0.9699 };
        static float sherpa4muWeight[7] = { 1.2845, 1.0677, 1.0461, 1.0459, 1.0421, 1.0373, 1.0313 };
        float mh = (truthQuad->getTLV()).M()/1000.;
        int im = -1;
        if      (mh < 80)  im = 0;
        else if (mh < 100) im = 1;
        else if (mh < 200) im = 2;
        else if (mh < 300) im = 3;
        else if (mh < 400) im = 4;
        else if (mh < 500) im = 5;
        else im = 6;

        if (truthQuad->getQuadType() == QuadleptonType::_4e) return sherpa4eWeight[im];
        else if (truthQuad->getQuadType() == QuadleptonType::_4mu) return sherpa4muWeight[im];
        else if (truthQuad->getQuadType() == QuadleptonType::_2e2tau) return sherpa4eWeight[im];
        else if (truthQuad->getQuadType() == QuadleptonType::_2tau2e) return sherpa4eWeight[im];
        else if (truthQuad->getQuadType() == QuadleptonType::_2mu2tau) return sherpa4muWeight[im];
        else if (truthQuad->getQuadType() == QuadleptonType::_2tau2mu) return sherpa4muWeight[im];

        /*    	    if(!truthQuad) return 1;

                    if(truthQuad->getQuadType() == QuadleptonType::_4mu) return 1.089180e+00;
                    else if(truthQuad->getQuadType() == QuadleptonType::_2mu2tau || truthQuad->getQuadType() == QuadleptonType::_2tau2mu) return 1.099618e+00;
                    else if(truthQuad->getQuadType() == QuadleptonType::_2e2tau  || truthQuad->getQuadType() == QuadleptonType::_2tau2e) return 9.168630e-01;
                    else if(truthQuad->getQuadType() == QuadleptonType::_4e) return 9.241068e-01;
                    */	}

        return 1;
}


/// Calculate weight_corr
Double_t ApplyWeight4l::getWeightCorr(const LepCombBase* combLep)
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;

    Double_t weight = 1;

    weight *= getMCWeight();
    weight *= getPileUpWeight();
    weight *= getLepEff(combLep);
    weight *= getTriggerSF(combLep);
    weight *= getEWCorr(); 
    weight *= getJetJVTSF();
    weight *= getBtagSF();

    return weight;
}

/// Calculate weight_lumi
Double_t ApplyWeight4l::getWeightLumi(const LepCombBase* combLep)
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;

    Double_t weight = 1;

    weight *= getCrossSection();
    weight *= getBranchingRatio(combLep);
    weight *= getLumi();

    return weight;
}

Double_t ApplyWeight4l::getWeight(const LepCombBase* combLep)
{
    return getWeightCorr(combLep) * getWeightLumi(combLep);
}

void ApplyWeight4l::fillWeightSys(const LepCombBase* combLep, CP::SystematicSet sys)
{
    // Do the sanity check first
    // First start with the full weight weight
    if(m_eventCont->outTree->isDoubleVar("weight"))
    {
        if(m_eventCont->outTree->getDoubleVar("weight") == -999)
        {
            LOG(logERROR)<<"ApplyWeight4l::fillWeightSys - Need to fill the nomial weight first";
            exit(1);
        }
    }


    // Legacy - To Delete
    m_eventCont->outTree->updateVar<double>("weight_corr_"+sys.name(), getWeightCorr(combLep));
    m_eventCont->outTree->updateVar<double>("weight_"+sys.name(), getWeight(combLep));

    // To get the variations
    // weight for no jet info
    double weight = getWeight(combLep);
    double variation = -999;
    /* TO Delete
    // First start with the full weight weight
    if(m_eventCont->outTree->isDoubleVar("weight_bTag"))
    {
    weight *= getJetJVTSF();
    weight *= getBtagSF();
    variation = weight/m_eventCont->outTree->getDoubleVar("weight_bTag");
    if(m_eventCont->outTree->getDoubleVar("weight_bTag") == 0) variation = 0;
    }
    else if(m_eventCont->outTree->isDoubleVar("weight_jet"))
    {
    weight *= getJetJVTSF();
    variation = weight/m_eventCont->outTree->getDoubleVar("weight_jet");
    if(m_eventCont->outTree->getDoubleVar("weight_jet") == 0) variation = 0;

    }
    */
    if(m_eventCont->outTree->isDoubleVar("weight"))
    {
        variation = weight/m_eventCont->outTree->getDoubleVar("weight");
        if(m_eventCont->outTree->getDoubleVar("weight") == 0) variation = 0;        
    }
    else
    {
        LOG(logERROR)<<"ApplyWeight4l::fillWeightSys - Need atleast a weight variable inside to make norm sys work...";
        exit(1);
    }

    // save the variation
    m_eventCont->outTree->updateVar<double>("weight_var_"+sys.name(), variation);

}

void ApplyWeight4l::clearVars()
{
    ApplyWeight::clearVars();

    m_truthHelper->clearVars();

    m_isJetFilled = false;
    m_jetList.clear();    
    m_jetListFailJVT.clear();    
    m_jetCont->clear();
}


double ApplyWeight4l::getJetJVTSF()
{
    if(!m_isJetFilled)
    {
        // Relax the constraint here - if vector is not provided return 1
        // This is for the fiducial analysis
        return 1;
    }

    // doing random dropping rather than JVT SF
    return 1;

    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;

    float SF = 1;

    m_jetCont->clear();

    for(const auto jetVar: m_jetList)
    {
        xAOD::IParticle *jet_i = const_cast<xAOD::IParticle*>(jetVar->getParticle());
        m_jetCont->push_back(jet_i); 
    }
    for(const auto jetVar: m_jetListFailJVT)
    {
        xAOD::IParticle *jet_i = const_cast<xAOD::IParticle*>(jetVar->getParticle());
        m_jetCont->push_back(jet_i); 
    }

    if(!m_jetJVTEffTool->applyAllEfficiencyScaleFactor(m_jetCont, SF ))
    {
        LOG(logERROR)<<"Cannot apply jet JVT SF";
        exit(1);
    }

    // fJVT is experimental skip for now
    //if(!m_jetFJVTEffTool->getEfficiencyScaleFactor(*jet, jetSF ))
    //{
    //    LOG(logERROR)<<"Cannot apply jet fJVT SF";
    //    exit(1);
    //}
    //SF *= jetSF;


    return SF;
}


// btag SF
double ApplyWeight4l::getBtagSF()
{
    if(!m_isJetFilled)
    {
        // Relax the constraint here - if vector is not provided return 1
        // This is for the fiducial analysis
        return 1;
    }

    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;

    double SF = 1;

    for(const auto jetVar: m_jetList)
    {
        float currSF = 1;
        const xAOD::Jet* jet = dynamic_cast<const xAOD::Jet*>(jetVar->getParticle());
        bool inBTagKinRange = (jet->pt() > 20 * 1000) && (std::fabs(jet->eta()) < 2.5);

        if(inBTagKinRange)
        {
            if(jetVar->getParticle()->auxdecor<int>("isBjet70")) 
            {
                if(!m_btagEffTool->getScaleFactor(*jet, currSF))
                {
                    LOG(logERROR)<<"Cannot apply jet btag SF";
                    exit(1);
                }
            }
            else
            {
                if(!m_btagEffTool->getInefficiencyScaleFactor(*jet, currSF))
                {
                    LOG(logERROR)<<"Cannot apply jet btag ineff SF";
                    exit(1);
                }
            }
        }

        LOG(logDEBUG)<<"btag - jet Pt: "<<jet->pt()/1000<<" eta: "<<jet->eta()<<" in Kinematic range: "<<inBTagKinRange<<" SF: "<<currSF
            <<" isBjet: "<<jetVar->getParticle()->auxdecor<int>("isBjet70");

        SF *= currSF;
    }

    return SF;
}

