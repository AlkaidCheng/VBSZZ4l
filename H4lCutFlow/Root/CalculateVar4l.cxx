#include "H4lCutFlow/CalculateVar4l.h"
#include "FourMomUtils/xAODP4Helpers.h"
#include "HZZUtils/KDToMELA.h"
#include "TRandom3.h"

#include "ZMassConstraint/ConstraintFit.h"
#include "MCFM_MatrixElement/IMatrixElementProvider.h"
using namespace std;

CalculateVar4l::CalculateVar4l(EventContainer* eventCont)
{
    // Copying it for local use
    m_eventCont = eventCont;
    m_outTree = 0;

    m_fsrTool = ToolHandle<FSR::IFsrPhotonTool>("FSRTool");
    if(m_fsrTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve IFsrPhotonTool";
        exit(1);
    }

    m_BDTtool = ToolHandle<IH4lBDTWeights>("H4lBDTWeights");
    if(m_BDTtool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve IH4lBDTWeights";
        exit(1);
    }

    m_massConstraint = ToolHandle<ZMassConstraint::IConstraintFit>("ZMassConstraint");
    if(m_BDTtool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ZMassConstraint::IConstraintFit";
        exit(1);
    }

    // For finding isolated lepton
    m_cutQuad = new CutLepComb(m_eventCont);


    // BDT tools
    m_VBFCatMVATool = ToolHandle<ICategoriesMVA>("VBF_ICHEP2016_30GeV_BinptHjj50");
    if(m_VBFCatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_VBFCatMVATool";
        exit(1);
    }
    m_VHnoPtHjjCatMVATool = ToolHandle<ICategoriesMVA>("VH_ICHEP2016_30GeV_noptHjj");
    if(m_VHnoPtHjjCatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_VHnoPtHjjCatMVATool";
        exit(1);
    }
    m_oneJet_jptetadR_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_1j_ICHEP2016_jptetadR");
    if(m_oneJet_jptetadR_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA oneJet_jptetadR_CatMVATool";
        exit(1);
    }

    m_VBF_TOPO_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_TOPO_Moriond2017");
    if(m_VBF_TOPO_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_VBF_TOPO_CatMVATool";
        exit(1);
    }
    m_VBF_Rest_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_Rest_Moriond2017");
    if(m_VBF_Rest_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_VBF_Rest_CatMVATool";
        exit(1);
    }
    m_1J_pt4l_60_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_1j_pT4l_0_60_Moriond2017");
    if(m_1J_pt4l_60_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_1J_pt4l_60_CatMVATool";
        exit(1);
    }
    m_1J_pt4l_120_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_1j_pT4l_0_120_Moriond2017");
    if(m_1J_pt4l_120_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_1J_pt4l_120_CatMVATool";
        exit(1);
    }
    m_1J_pt4l_60_120_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_1j_pT4l_60_120_Moriond2017");
    if(m_1J_pt4l_60_120_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_1J_pt4l_60_120_CatMVATool";
        exit(1);
    }



    m_energyRescaler = ToolHandle<CP::IEgammaCalibrationAndSmearingTool>("EgammaCalibrationAndSmearingTool");
    if(m_energyRescaler.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve CP::IEgammaCalibrationAndSmearingTool";
        exit(1);
    }

    m_electronMCClassifier = ToolHandle<IElectronMCClassification>("elMCClassifier");
    if(m_electronMCClassifier.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve IElectronMCClassification";
        exit(1);
    }
    m_recoClassification = ToolHandle<IElectronRecoClassification>("recoClassification");
    if(m_recoClassification.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve IElectronRecoClassification";
        exit(1);
    }

    m_MCTruthClassifier = ToolHandle<IMCTruthClassifier>("MCClassifier");
    if(m_MCTruthClassifier.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve MCTruthClassifier";
        exit(1);
    }
    m_grl = ToolHandle<IGoodRunsListSelectionTool>("GoodRunsListSelectionTool");
    if(m_grl.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve IGoodRunsListSelectionTool";
        exit(1);
    } 

    // Retrive the pileup tool for later usage
    m_pileupTool = ToolHandle<CP::IPileupReweightingTool>("PileupTool");
    if(m_pileupTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve IPileupReweightingTool";
        exit(1);
    }

    m_bunchCrossingTool = ToolHandle<Trig::IBunchCrossingTool>("BunchCrossingTool");
    if(m_bunchCrossingTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve IBunchCrossingTool";
        exit(1);
    }

    m_truthHelper = new TruthHelper(m_eventCont);



    m_matrixElementProvider = ToolHandle<HSG2_MCFM::IMatrixElementProvider>("MatrixElementProvider");
    if(m_matrixElementProvider->initialize().isFailure())
    {
        LOG(logERROR)<<"Cannot intialize MatrixElementProvider";
        exit(1);
    }


    m_metCalc.reset();

    // Not going to remove, since we might need it for BSM ME
    //// Initialize the ME code
    ////BSM

    //// SM ggF
    //m_heft_pp_H_ZZ_4l_heft_gg_epemepem      = new CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemepem();
    //m_heft_pp_H_ZZ_4l_heft_gg_epemmupmum    = new CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemmupmum();

    //// SM VBF
    //m_sm_hVBF_ZZ_4l_sm_ddx_epemepemuux      = new CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ddx_epemepemuux();
    //m_sm_hVBF_ZZ_4l_sm_ddx_epemmupmumuux    = new CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ddx_epemmupmumuux();
    //m_sm_hVBF_ZZ_4l_sm_ud_epemepemud        = new CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ud_epemepemud();
    //m_sm_hVBF_ZZ_4l_sm_ud_epemmupmumud      = new CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ud_epemmupmumud();
    ////m_sm_hVBF_ZZ_4l_sm_uux_epemepemuux      = new CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_uux_epemepemuux();


    //string cardVBF      = PathResolver::find_file ("MadGraphME/param_card_PROC_SA_CPP_sm_hVBF_ZZ_4l.dat", "CALIBPATH");
    //string cardHeft_ggF = PathResolver::find_file ("MadGraphME/param_card_PROC_SA_CPP_heft_pp_H_ZZ_4l.dat", "CALIBPATH");

    //// Proc Card
    ////BSM
    //// SM ggF
    //m_heft_pp_H_ZZ_4l_heft_gg_epemepem->initProc(cardHeft_ggF);
    //m_heft_pp_H_ZZ_4l_heft_gg_epemmupmum->initProc(cardHeft_ggF);

    //// SM VBF
    //m_sm_hVBF_ZZ_4l_sm_ddx_epemepemuux->initProc(cardVBF);
    //m_sm_hVBF_ZZ_4l_sm_ddx_epemmupmumuux->initProc(cardVBF);
    //m_sm_hVBF_ZZ_4l_sm_ud_epemepemud->initProc(cardVBF);
    //m_sm_hVBF_ZZ_4l_sm_ud_epemmupmumud->initProc(cardVBF);
    ////m_sm_hVBF_ZZ_4l_sm_uux_epemepemuux->initProc(cardVBF);

    //LHAPDF::setVerbosity(LHAPDF::LOWKEY);
    //LHAPDF::setPDFPath("/cvmfs/sft.cern.ch/lcg/external/lhapdfsets/current/");

    //m_ct10PDF = LHAPDF::mkPDF("CT10nlo",0);


    clearVars();

}

CalculateVar4l::~CalculateVar4l()
{
    delete m_cutQuad;
    delete m_truthHelper;
}

void CalculateVar4l::process()
{
    // A local copy to limit the amount of typing
    m_outTree = m_eventCont->outTree;
    if(!m_outTree)
    {
        LOG(logERROR)<<"Error: CalculateVar4l - the output tree has not been specified";
        exit(1);
    }

    // General Variables
    fillGeneralVars();

    // Lepton related vars
    fillLeptonVars();
    fillBkgLeptonVars();

    // Jet related vars
    fillJetVars();
    //fillFidJetVars();

    // Mass related vars
    fillMassVars();

    // Mass BDT
    fillMassBDTVars();

    fillCategory();
    fillCategoryfJVT();

    // Angular variables
    fillAngularVar();

    // Truth vars
    fillTruthMatched();
    fillTruth();
    fillTruthPairing();

    fillMET();

    fillSimpleXS();

    fillFileInfo();

    fillVertexInfo();

    // EFT part
    fillCatBDT();
    fillME();

    fillGRLDecision();


    // For jet bin migration
    fillTruthJets();
}


void CalculateVar4l::clearVars()
{
    // Clearing the variables
    if(m_outTree) m_outTree->clearVars();

    m_truthHelper->clearVars();

    m_higgs = 0;

    m_isJetFilled = false;
    m_isFSRFilled = false;

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

    m_isExtraLep = false;

    while(!m_partContainer.empty()) delete m_partContainer.back(), m_partContainer.pop_back();

}

// Helper

// To fill in the general information
void CalculateVar4l::fillGeneralVars()
{
    // Lumi info
    m_outTree->updateLongIntVar("event", m_eventCont->eventInfo->eventNumber());
    if(m_eventCont->isMC)
    {
        Int_t DSID = m_eventCont->getDSID();
        // Some truth derivation are weird... they store DSID in runNumber
        // Max provided this fix
        // if (m_eventCont->m_isDAODTRUTH && DSID == 0) DSID = m_eventCont->eventInfo->runNumber(); 
        
        m_outTree->updateIntVar("run",  DSID);
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

    //m_outTree->updateFloatVar("ave_int_per_xing", m_eventCont->eventInfo->averageInteractionsPerCrossing());
    m_outTree->updateFloatVar("ave_int_per_xing",m_pileupTool->getCorrectedAverageInteractionsPerCrossing(*m_eventCont->eventInfo, true));


    m_outTree->updateIntVar("bcid",  m_eventCont->eventInfo->bcid());  
    //m_outTree->updateIntVar("bc_distanceFromFront",  m_bunchCrossingTool->distanceFromFront(m_eventCont->eventInfo->bcid()));  


}

// To fill the general lepton vars
void CalculateVar4l::fillLeptonVars()
{
    std::array<int, 4> lepton_quality       = {{-999, -999, -999, -999}};


    int lepIndex[4] = {0, 1, 2, 3};

    for(int i = 0; i < 4; i++)
    {
        lepton_quality[i] = leptonIDType::unknown;
        if(m_higgs->getLep(i)->getPartType() == ParticleType::Muon)
        {
            // fill Iso
            const xAOD::Muon* tempLep = dynamic_cast<const xAOD::Muon*>(m_higgs->getLep(i)->getParticle());
            if(tempLep->muonType() == xAOD::Muon::MuonStandAlone)                   lepton_quality[i] = leptonIDType::mu_SA;
            if(tempLep->muonType() == xAOD::Muon::CaloTagged)                       lepton_quality[i] = leptonIDType::mu_CA;
            if(tempLep->muonType() == xAOD::Muon::SegmentTagged)                    lepton_quality[i] = leptonIDType::mu_ST;
            if(tempLep->muonType() == xAOD::Muon::SiliconAssociatedForwardMuon)     lepton_quality[i] = leptonIDType::mu_SAFM;            
            if(tempLep->muonType() == xAOD::Muon::Combined)                         lepton_quality[i] = leptonIDType::mu_CB;
        }
        else if(m_higgs->getLep(i)->getPartType() == ParticleType::Electron)
        {
            // fill quality
            if(m_higgs->getLep(i)->getParticle()->auxdecor<int>("tightID")) lepton_quality[i] = leptonIDType::el_Tight;
            else if(m_higgs->getLep(i)->getParticle()->auxdecor<int>("mediumID")) lepton_quality[i] = leptonIDType::el_Medium;
            else if(m_higgs->getLep(i)->getParticle()->auxdecor<int>("looseID")) lepton_quality[i] = leptonIDType::el_Loose;
            else if(m_higgs->getLep(i)->getParticle()->auxdecor<int>("looseID_noBL")) lepton_quality[i] = leptonIDType::el_Loose_noBL;
            else if(m_higgs->getLep(i)->getParticle()->auxdecor<int>("veryLooseID")) lepton_quality[i] = leptonIDType::el_VLoose;
            else if(m_higgs->getLep(i)->getParticle()->auxdecor<int>("basicID")) lepton_quality[i] = leptonIDType::el_Basic;
        }
    }

    std::array<float, 4> lepton_pt    = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_phi   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_eta   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_m     = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_res   = {{-999, -999, -999, -999}};
    std::vector<float> lepton_pt_test;

    for(int i = 0; i < 4; i++)
    {
        lepton_pt[i]  = m_higgs->getLep(i)->getTLV().Pt()/1000;
        lepton_eta[i] = m_higgs->getLep(i)->getTLV().Eta();
        lepton_phi[i] = m_higgs->getLep(i)->getTLV().Phi();
        lepton_m[i]   = m_higgs->getLep(i)->getTLV().M()/1000l;
        lepton_res[i] = m_higgs->getLep(i)->getParticle()->auxdecor<float>("resolution");
        lepton_pt_test.push_back( m_higgs->getLep(i)->getTLV().Pt()/1000);

    }

    m_outTree->updateFloatArrayVar("lepton_pt", lepton_pt);
    m_outTree->updateFloatArrayVar("lepton_phi", lepton_phi);
    m_outTree->updateFloatArrayVar("lepton_eta", lepton_eta);
    m_outTree->updateFloatArrayVar("lepton_m", lepton_m);
    m_outTree->updateFloatArrayVar("lepton_res", lepton_res);
    m_outTree->updateIntArrayVar("lepton_id", lepton_quality);

    // Vars for MCFM
    float MCFM_dxs_ZZ = -999;
    float MCFM_dxs_ggZZ = -999;
    float MCFM_dxs_ggZZtot = -999;
    float MCFM_dxs_ggZZint = -999;
    float MCFM_dxs_HZZ = -999;

    LOG(logDEBUG)<<"Calling MCFM ME ";
    HSG2_MCFM::MatrixElementResult meResult;
    if ((m_matrixElementProvider->getME(*m_higgs->getLep(1)->getParticle(), *m_higgs->getLep(0)->getParticle(), *m_higgs->getLep(3)->getParticle(), *m_higgs->getLep(2)->getParticle(), meResult)).isSuccess())
    {
	MCFM_dxs_ZZ = meResult.dxs_ZZ;
	MCFM_dxs_ggZZ = meResult.dxs_ggZZ;
	MCFM_dxs_ggZZint = meResult.dxs_ggZZint;
	MCFM_dxs_ggZZtot = meResult.dxs_ggZZtot;
	MCFM_dxs_HZZ = meResult.dxs_HZZ;
    }
    m_outTree->updateFloatVar("MCFM_dxs_ZZ", MCFM_dxs_ZZ);
    m_outTree->updateFloatVar("MCFM_dxs_ggZZ", MCFM_dxs_ggZZ);
    m_outTree->updateFloatVar("MCFM_dxs_ggZZtot", MCFM_dxs_ggZZtot);
    m_outTree->updateFloatVar("MCFM_dxs_ggZZint", MCFM_dxs_ggZZint);
    m_outTree->updateFloatVar("MCFM_dxs_HZZ", MCFM_dxs_HZZ);

    // example for vector output
    //m_outTree->updateVar<vector<float>>("test_vector", lepton_pt_test);

    // Mu specific vars
    uint8_t sumval;
    std::array<float, 4> mu_IDpt            = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_IDphi           = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_IDeta           = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_EMSpt           = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_EMSphi          = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_phiInMS	    = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_EMSeta          = {{-999, -999, -999, -999}};
    std::array<int, 4> mu_NPrecLayer        = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_qOverPsig       = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_redChi2         = {{-999, -999, -999, -999}};

    for(int i = 0; i < 4; i++)
    {
        if(m_higgs->getLep(lepIndex[i])->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* tempMu = dynamic_cast<const xAOD::Muon*>(m_higgs->getLep(lepIndex[i])->getParticle());
            const xAOD::TrackParticle* idtp = tempMu->trackParticle(xAOD::Muon::InnerDetectorTrackParticle);
            const xAOD::TrackParticle* emstp = tempMu->trackParticle(xAOD::Muon::ExtrapolatedMuonSpectrometerTrackParticle); 
	    const xAOD::TrackParticle* mstp = tempMu->trackParticle(xAOD::Muon::MuonSpectrometerTrackParticle);

            bool isIDOK = (tempMu->isAvailable< float >( "InnerDetectorPt" ) && idtp);
            bool isMSOK = (tempMu->isAvailable< float >( "MuonSpectrometerPt" ) && emstp);
            bool pt_ms_isMSOK = (tempMu->isAvailable< float >( "MuonSpectrometerPt" ) && mstp);

            mu_IDpt[i] = isIDOK ? tempMu->auxdata< float >( "InnerDetectorPt" )/1000 : -999;
            mu_EMSpt[i] = isMSOK ? tempMu->auxdata< float >( "MuonSpectrometerPt" )/1000 : -999;

	    mu_IDphi[i] = isIDOK ? idtp->phi() : -999;
	    mu_IDeta[i] = isIDOK ? idtp->eta() : -999;
	    mu_EMSphi[i] = isMSOK ? emstp->phi() : -999;
	    mu_EMSeta[i] = isMSOK ? emstp->eta() : -999;
	    mu_phiInMS[i] = pt_ms_isMSOK ? mstp->phi() : -999;

            tempMu->summaryValue(sumval,xAOD::numberOfPrecisionLayers);
            mu_NPrecLayer[i] = sumval;

            if (isIDOK && isMSOK) {
                float qOverPsigma  = sqrt( idtp->definingParametersCovMatrix()(4,4) +
                        emstp->definingParametersCovMatrix()(4,4) );
                mu_qOverPsig[i] = fabs(emstp->qOverP() - idtp->qOverP()) / qOverPsigma;
            }

	    mu_redChi2[i] = tempMu->primaryTrackParticle()->chiSquared()/tempMu->primaryTrackParticle()->numberDoF();
        }
    }
    m_outTree->updateFloatArrayVar("mu_IDpt", mu_IDpt);
    m_outTree->updateFloatArrayVar("mu_IDphi", mu_IDphi);
    m_outTree->updateFloatArrayVar("mu_IDeta", mu_IDeta);
    m_outTree->updateFloatArrayVar("mu_MSpt", mu_EMSpt);
    m_outTree->updateFloatArrayVar("mu_MSphi", mu_EMSphi);
    m_outTree->updateFloatArrayVar("mu_phiInMS", mu_phiInMS);
    m_outTree->updateFloatArrayVar("mu_MSeta", mu_EMSeta);
    m_outTree->updateFloatArrayVar("mu_qOverPsig", mu_qOverPsig);
    m_outTree->updateIntArrayVar("mu_NPrecLayer", mu_NPrecLayer);
    m_outTree->updateFloatArrayVar("mu_redChi2", mu_redChi2);
}

void CalculateVar4l::fillBkgLeptonVars()
{
    // Bkg specific
    // array variable fill
    // m_higgs leptons pairs are ordered by charge
    // array variable lepton pairs need to be ordered by pT
    // map the index in m_higgs to index in array
    int lepIndex[4] = {0, 1, 2, 3};
    //if( m_higgs->getLep(1)->getTLV().Pt() >  m_higgs->getLep(0)->getTLV().Pt()) {lepIndex[0] = 1; lepIndex[1] = 0;}
    //if( m_higgs->getLep(3)->getTLV().Pt() >  m_higgs->getLep(2)->getTLV().Pt()) {lepIndex[2] = 3; lepIndex[3] = 2;}


    // For all the lepton
    std::array<int, 4> lepton_charge        = {{-999, -999, -999, -999}};
    std::array<int, 4> lepton_quality       = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_d0sig       = {{-999, -999, -999, -999}};
    // pass information to be used in CR generation
    std::array<int, 4> lepton_passD0sig     = {{-999, -999, -999, -999}};
    std::array<int, 4> lepton_passIsoCut    = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_ptvarcone30    = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_ptvarcone20    = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_topoetcone20   = {{-999, -999, -999, -999}};

    // Recompute the isolation
    m_cutQuad->cutIsolation(m_higgs);

    for(int i = 0; i < 4; i++)
    {
        lepton_charge[i] = m_higgs->getLep(lepIndex[i])->getCharge();
        lepton_d0sig[i] = fabs(m_higgs->getLep(lepIndex[i])->getParticle()->auxdecor<float>("d0sig"));
        lepton_passD0sig[i] = m_higgs->getLep(lepIndex[i])->getParticle()->auxdecor<int>("passD0Sig");
        lepton_passIsoCut[i] = m_higgs->getLep(lepIndex[i])->getParticle()->auxdecor<int>("isoCut");
        float ptvarcone30 = -1;
        float ptvarcone20 = -1;
        float topoetcone20 = -1;

        if(m_higgs->getLep(lepIndex[i])->getPartType() == ParticleType::Muon)
        {
            // fill Iso
            const xAOD::Muon *tempLep = dynamic_cast<const xAOD::Muon*>(m_higgs->getLep(lepIndex[i])->getParticle());
            tempLep->isolation(ptvarcone30,xAOD::Iso::ptvarcone30);
            tempLep->isolation(ptvarcone20,xAOD::Iso::ptvarcone20);
            tempLep->isolation(topoetcone20,xAOD::Iso::topoetcone20);

            // fill quality
            lepton_quality[i] = LeptonQuality::otherMu;
        }
        else if(m_higgs->getLep(lepIndex[i])->getPartType() == ParticleType::Electron)
        {
            // fill Iso
            const xAOD::Electron* tempLep = dynamic_cast<const xAOD::Electron*>(m_higgs->getLep(lepIndex[i])->getParticle());
            tempLep->isolation(ptvarcone30,xAOD::Iso::ptvarcone30);
            tempLep->isolation(ptvarcone20,xAOD::Iso::ptvarcone20);
            tempLep->isolation(topoetcone20,xAOD::Iso::topoetcone20);

            // fill quality
            if(m_higgs->getLep(lepIndex[i])->getParticle()->auxdecor<int>("looseID")) lepton_quality[i] = LeptonQuality::looseID;
            else if(m_higgs->getLep(lepIndex[i])->getParticle()->auxdecor<int>("veryLooseID")) lepton_quality[i] = LeptonQuality::veryLooseID;
            else if(m_higgs->getLep(lepIndex[i])->getParticle()->auxdecor<int>("basicID")) lepton_quality[i] = LeptonQuality::basicID;
            else lepton_quality[i] = LeptonQuality::otherEl;
        }


        ptvarcone30 = m_higgs->getLep(lepIndex[i])->getParticle()->auxdecor<float>("corr_ptvarcone30");
        ptvarcone20 = m_higgs->getLep(lepIndex[i])->getParticle()->auxdecor<float>("corr_ptvarcone20");
        topoetcone20 = m_higgs->getLep(lepIndex[i])->getParticle()->auxdecor<float>("corr_topoetcone20");

        lepton_ptvarcone30[i] = ptvarcone30/m_higgs->getLep(lepIndex[i])->getParticle()->pt();
        lepton_ptvarcone20[i] = ptvarcone20/m_higgs->getLep(lepIndex[i])->getParticle()->pt();
        lepton_topoetcone20[i] = topoetcone20/m_higgs->getLep(lepIndex[i])->getParticle()->pt();

    }

    m_outTree->updateIntArrayVar("lepton_charge", lepton_charge);
    m_outTree->updateFloatArrayVar("lepton_d0sig", lepton_d0sig);

    m_outTree->updateFloatArrayVar("lepton_ptvarcone30", lepton_ptvarcone30);
    m_outTree->updateFloatArrayVar("lepton_ptvarcone20", lepton_ptvarcone20);
    m_outTree->updateFloatArrayVar("lepton_topoetcone20", lepton_topoetcone20);

    m_outTree->updateIntArrayVar("lepton_passD0sig", lepton_passD0sig);
    m_outTree->updateIntArrayVar("lepton_passIsoCut", lepton_passIsoCut);
    m_outTree->updateIntArrayVar("lepton_quality", lepton_quality);



    // el specific
    std::array<int, 4> el_recoClass = {{-999, -999, -999, -999}};
    std::array<int, 4> el_MCClass = {{-999, -999, -999, -999}};
    std::array<float, 4> el_Rphi = {{-999, -999, -999, -999}};
    std::array<float, 4> el_Deta = {{-999, -999, -999, -999}};
    std::array<float, 4> el_Reta = {{-999, -999, -999, -999}};
    std::array<float, 4> el_f1 = {{-999, -999, -999, -999}};

    std::array<int, 4> el_nBL = {{-999, -999, -999, -999}};
    std::array<int, 4> el_nInnerExpPix = {{-999, -999, -999, -999}};

    std::array<int, 4> el_expInner = {{-999, -999, -999, -999}};
    std::array<int, 4> el_expNextToInner = {{-999, -999, -999, -999}};
    std::array<int, 4> el_nInner = {{-999, -999, -999, -999}};
    std::array<int, 4> el_nNextToInner = {{-999, -999, -999, -999}};

    std::array<float, 4> el_rTRT = {{-999, -999, -999, -999}};
    std::array<float, 4> el_eProbHT = {{-999, -999, -999, -999}};
    std::array<float, 4> el_eOverP = {{-999, -999, -999, -999}};
    std::array<int, 4> el_nPix = {{-999, -999, -999, -999}};
    std::array<int, 4> el_nSCT = {{-999, -999, -999, -999}};

    uint8_t sumval;
    float val;
    for(int i = 0; i < 4; i++)
    {
        if(m_higgs->getLep(lepIndex[i])->getPartType() == ParticleType::Electron)
        {
            const xAOD::Electron *tempEl = dynamic_cast<const xAOD::Electron*>(m_higgs->getLep(lepIndex[i])->getParticle());
            const xAOD::TrackParticle* tp = tempEl->trackParticle();
            if(m_outTree->isIntArrayVar("el_recoClass"))
                el_recoClass[i] = m_recoClassification->getRecoClassification(*tempEl);
            if(m_outTree->isIntArrayVar("el_MCClass"))
                el_MCClass[i] = m_electronMCClassifier->getMCClassification(*tempEl);

            el_nPix[i]      = tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfPixelHits) ? sumval : -999;
            el_nSCT[i]      = tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfSCTHits) ? sumval : -999;

            el_Rphi[i]      = tempEl->showerShapeValue(val, xAOD::EgammaParameters::Rphi) ? val : -999;
            el_Reta[i]      = tempEl->showerShapeValue(val, xAOD::EgammaParameters::Reta) ? val : -999;
            el_f1[i]        = tempEl->showerShapeValue(val, xAOD::EgammaParameters::f1)     ? val : -999;
            el_Deta[i]      = tempEl->trackCaloMatchValue(xAOD::EgammaParameters::deltaEta1);

            int expBL       = tempEl->trackParticleSummaryValue(sumval, xAOD::expectBLayerHit)    ? sumval : -999;
            el_nBL[i]       = (1 == expBL && tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfBLayerHits))? sumval : -999;

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


            float el_nTRT   = (float) tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfTRTHits) ? sumval : -999;
            float el_nHTTRT = (float) tempEl->trackParticleSummaryValue(sumval, xAOD::numberOfTRTHighThresholdHits) ? sumval : -999;
            if(el_nTRT) el_rTRT[i] = el_nHTTRT / el_nTRT;
            else el_rTRT[i] = -999;

            el_eProbHT[i] = tempEl->trackParticleSummaryValue(val, xAOD::eProbabilityHT) ? val : -999;
            el_eOverP[i] = fabs(tempEl->e()*tp->qOverP());
        }
    }

    m_outTree->updateFloatArrayVar("el_Reta", el_Reta);
    m_outTree->updateFloatArrayVar("el_Rphi", el_Rphi);
    m_outTree->updateFloatArrayVar("el_f1", el_f1);
    m_outTree->updateIntArrayVar("el_nBL", el_nBL);
    m_outTree->updateIntArrayVar("el_nInnerExpPix", el_nInnerExpPix);
    m_outTree->updateIntArrayVar("el_nPix", el_nPix);
    m_outTree->updateIntArrayVar("el_nSCT", el_nSCT);

    m_outTree->updateIntArrayVar("el_expInner", el_expInner);
    m_outTree->updateIntArrayVar("el_expNextToInner", el_expNextToInner);
    m_outTree->updateIntArrayVar("el_nInner", el_nInner);
    m_outTree->updateIntArrayVar("el_nNextToInner", el_nNextToInner);

    m_outTree->updateFloatArrayVar("el_rTRT", el_rTRT);

    m_outTree->updateIntArrayVar("el_recoClass", el_recoClass);
    m_outTree->updateIntArrayVar("el_MCClass", el_MCClass);
    m_outTree->updateFloatArrayVar("el_Rphi", el_Rphi);
    m_outTree->updateFloatArrayVar("el_Reta", el_Reta);
    m_outTree->updateFloatArrayVar("el_f1", el_f1);
    m_outTree->updateFloatArrayVar("el_Deta1", el_Deta);
    m_outTree->updateIntArrayVar("el_nBL", el_nBL);
    m_outTree->updateFloatArrayVar("el_rTRT", el_rTRT);
    m_outTree->updateFloatArrayVar("el_eProbHT", el_eProbHT);
    m_outTree->updateFloatArrayVar("el_eOverP", el_eOverP);

    // mu specific
    std::array<int, 4> mu_MCPartType    = {{-999, -999, -999, -999}};
    std::array<int, 4> mu_MCOriginType  = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_IDpt        = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_EMSpt       = {{-999, -999, -999, -999}};
    std::array<int, 4> mu_author        = {{-999, -999, -999, -999}};
    std::array<int, 4> mu_type          = {{-999, -999, -999, -999}};
    std::array<int, 4> mu_NPrecLayer    = {{-999, -999, -999, -999}};
    std::array<float, 4> mu_qOverPsig   = {{-999, -999, -999, -999}};
    std::array<int, 4> mu_nInnerExpPix  = {{-999, -999, -999, -999}};

    for(int i = 0; i < 4; i++)
    {
        if(m_higgs->getLep(lepIndex[i])->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* tempMu = dynamic_cast<const xAOD::Muon*>(m_higgs->getLep(lepIndex[i])->getParticle());
            const xAOD::TrackParticle* idtp = tempMu->trackParticle(xAOD::Muon::InnerDetectorTrackParticle);
            const xAOD::TrackParticle* emstp = tempMu->trackParticle(xAOD::Muon::ExtrapolatedMuonSpectrometerTrackParticle);

            bool isIDOK = (tempMu->isAvailable< float >( "InnerDetectorPt" ) && idtp);
            bool isMSOK = (tempMu->isAvailable< float >( "MuonSpectrometerPt" ) && emstp);

            mu_IDpt[i] = isIDOK ? tempMu->auxdata< float >( "InnerDetectorPt" )/1000 : -999;
            mu_EMSpt[i] = isMSOK? tempMu->auxdata< float >( "MuonSpectrometerPt" )/1000 : -999;

            mu_author[i] = tempMu->author();
            mu_type[i] = tempMu->muonType();
            tempMu->summaryValue(sumval,xAOD::numberOfPrecisionLayers);
            mu_NPrecLayer[i] = sumval;

            if(m_outTree->isIntArrayVar("mu_MCPartType") || m_outTree->isIntArrayVar("mu_MCOriginType"))
            {
                std::pair<MCTruthPartClassifier::ParticleType,MCTruthPartClassifier::ParticleOrigin>
                    classification = m_MCTruthClassifier->particleTruthClassifier(tempMu);
                mu_MCPartType[i] = classification.first;
                mu_MCOriginType[i] = classification.second;
            }

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
    m_outTree->updateFloatArrayVar("mu_IDpt", mu_IDpt);
    m_outTree->updateFloatArrayVar("mu_MSpt", mu_EMSpt);
    m_outTree->updateFloatArrayVar("mu_qOverPsig", mu_qOverPsig);
    m_outTree->updateIntArrayVar("mu_author", mu_author);
    m_outTree->updateIntArrayVar("mu_type", mu_type);
    m_outTree->updateIntArrayVar("mu_MCPartType", mu_MCPartType);
    m_outTree->updateIntArrayVar("mu_MCOriginType", mu_MCOriginType);
    m_outTree->updateIntArrayVar("mu_NPrecLayer", mu_NPrecLayer);
    m_outTree->updateIntArrayVar("mu_nInnerExpPix", mu_nInnerExpPix);
}

void CalculateVar4l::fillJetVars()
{
    if(!m_isJetFilled)
    {
        LOG(logERROR)<<"CalculateVar4l: Jet vector not filled";
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
    std::array<int, 4> jet_pass_fJVT = {{-999, -999, -999, -999}};
    std::array<int, 4> jet_partonTruthLabelID = {{-999, -999, -999, -999}};

    int nJets = 4;
    if(m_jetList.size() < 4) nJets = m_jetList.size();

    for(int i = 0; i < nJets; i++)
    {
        const xAOD::Jet* jet = dynamic_cast<const xAOD::Jet*>(m_jetList[i]->getParticle());
        jet_pt[i] = jet->pt()/1000;
        jet_eta[i] = jet->eta();
        jet_phi[i] = jet->phi();
        jet_m[i] = jet->m()/1000;
	std::vector<int> partonLabels;

	int partonLabel;
	jet->getAttribute<int>("PartonTruthLabelID", partonLabel);
	jet_partonTruthLabelID[i] = partonLabel;

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

        jet_pass_fJVT[i] = int(jet->auxdata<char>("passFJVT"));

    }
    m_outTree->updateFloatArrayVar("jet_pt", jet_pt);
    m_outTree->updateFloatArrayVar("jet_eta", jet_eta);
    m_outTree->updateFloatArrayVar("jet_phi", jet_phi);
    m_outTree->updateFloatArrayVar("jet_m", jet_m);
    m_outTree->updateIntArrayVar("jet_btag70", jet_btag70);
    m_outTree->updateIntArrayVar("jet_btag85", jet_btag85);
    m_outTree->updateIntArrayVar("jet_passfJVT", jet_pass_fJVT);
    m_outTree->updateIntArrayVar("jet_partonTruthLabelID", jet_partonTruthLabelID);

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

    // If both leading and subleading jets are found
    if (m_jetList.size() >=2 ) {
        Int_t iLeadingJet = 0;
        Int_t iSubleadingJet = 1;
        TLorentzVector combined = m_jetList[iLeadingJet]->getTLV() + m_jetList[iSubleadingJet]->getTLV();

        m_outTree->updateFloatVar("dijet_invmass", combined.M()/1000);
        m_outTree->updateFloatVar("dijet_pt", combined.Pt()/1000);
        m_outTree->updateFloatVar("dijet_deltaeta", fabs(m_jetList[iLeadingJet]->getTLV().Eta() - m_jetList[iSubleadingJet]->getTLV().Eta()));
        m_outTree->updateFloatVar("pt4ljj_unconstrained", (m_higgs->getTLV()+combined).Pt()/1000);
        m_outTree->updateFloatVar("m4ljj_unconstrained", (m_higgs->getTLV()+combined).M()/1000);
        m_outTree->updateFloatVar("eta_zepp_ZZ", fabs(m_higgs->getTLV().Eta() - (m_jetList[iLeadingJet]->getTLV().Eta() + m_jetList[iSubleadingJet]->getTLV().Eta())/2));

        vector<const xAOD::IParticle*> jets;
        vector<const xAOD::IParticle*> leptons;

        // Get the jets
        jets.push_back(m_jetList[iLeadingJet]->getParticle());
        jets.push_back(m_jetList[iSubleadingJet]->getParticle());

        float dijet_phi = -999;
        float jet_eta[2];
        jet_eta[0] = m_jetList[iLeadingJet]->getTLV().Eta();
        jet_eta[1] = m_jetList[iSubleadingJet]->getTLV().Eta();
        float jet_phi[2];
        jet_phi[0] = m_jetList[iLeadingJet]->getTLV().Phi();
        jet_phi[1] = m_jetList[iSubleadingJet]->getTLV().Phi();
        if(jet_eta[0]>jet_eta[1]) dijet_phi= jet_phi[0]-jet_phi[1];
        if(jet_eta[0]<jet_eta[1]) dijet_phi= jet_phi[1]-jet_phi[0];

        if(dijet_phi<0) dijet_phi = dijet_phi + 2*TMath::Pi();

        m_outTree->updateFloatVar("dijet_deltaphi", dijet_phi);
        // Get the leptons
        for(int i = 0; i < 4; i++)
        {
            leptons.push_back(m_higgs->getLep(i)->getParticle());
        }

        m_outTree->updateFloatVar("min_dR_jZ", computeMinDeltaR(leptons, jets));
    }

    if(m_jetList.size() >=1)
    {
        Int_t iLeadingJet = 0;
        m_outTree->updateFloatVar("dR_jH", m_higgs->getTLV().DeltaR(m_jetList[iLeadingJet]->getTLV()));
    }


    LOG(logDEBUG)<<"dijet_invmass: "<<m_outTree->getFloatVar("dijet_invmass");
    LOG(logDEBUG)<<"dijet_deltaeta: "<<m_outTree->getFloatVar("dijet_deltaeta");

}
float CalculateVar4l::computeMinDeltaR(const std::vector<const xAOD::IParticle*>& leptons,
        const std::vector<const xAOD::IParticle*>& jets) const
{
    // double deltaR( const xAOD::IParticle& p4, double rapidity, double phi, bool useRapidity=true )

    TLorentzVector Z1 = leptons[0]->p4() + leptons[1]->p4();
    TLorentzVector Z2 = leptons[2]->p4() + leptons[3]->p4();

    float delR_j1Z1(fabs(xAOD::P4Helpers::deltaR(*jets[0], Z1.Eta(), Z1.Phi(), false)));
    float delR_j1Z2(fabs(xAOD::P4Helpers::deltaR(*jets[0], Z2.Eta(), Z2.Phi(), false)));
    float delR_j2Z1(fabs(xAOD::P4Helpers::deltaR(*jets[1], Z1.Eta(), Z1.Phi(), false)));
    float delR_j2Z2(fabs(xAOD::P4Helpers::deltaR(*jets[1], Z2.Eta(), Z2.Phi(), false)));

    float min_j1 = (delR_j1Z1 < delR_j1Z2) ? delR_j1Z1 : delR_j1Z2;
    float min_j2 = (delR_j2Z1 < delR_j2Z2) ? delR_j2Z1 : delR_j2Z2;


    return (min_j1 < min_j2) ?  min_j1 : min_j2;

}

void CalculateVar4l::fillFidJetVars()
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


// BDT
void CalculateVar4l::fillMassBDTVars()
{
    QuadleptonType::QuadleptonType quadType =m_higgs->getQuadType();
    if(quadType != QuadleptonType::_4mu &&
            quadType != QuadleptonType::_2e2mu &&
            quadType != QuadleptonType::_2mu2e &&
            quadType != QuadleptonType::_4e ) return;
    vector<const xAOD::IParticle*> particleList;

    // Getting the FSR Photon
    for (Int_t i = 0; i < (Int_t) m_higgs->getLepSize(); i++)
    {
        particleList.push_back(m_higgs->getLep(i)->getParticle());
    }

    // Set input
    m_BDTtool->setBDTInputs(particleList[0],
            particleList[1],
            particleList[2],
            particleList[3],
            m_higgs->getAnalTLV(TLVType::FSR).Pt()/1000,
            -999,
            false);

    // Set output
    float KD_discriminant       = -999;
    float BDT_discriminant      = -999;
    float BDTGuass_discriminant = -999;
    float ptSysupFac            = -999;
    float ptSysdownFac          = -999;

    m_BDTtool->fillBDTOutputs(KD_discriminant,
            BDT_discriminant,
            BDTGuass_discriminant,
            ptSysupFac,
            ptSysdownFac);

    m_outTree->updateFloatVar("BDT_discriminant", BDT_discriminant);
    m_outTree->updateFloatVar("KD_discriminant", KD_discriminant);
    m_outTree->updateFloatVar("HiggsME", m_BDTtool->getSignalME());
    
    float mela = -999;
    HZZUtils::kd2mela(KD_discriminant, m_outTree->getFloatVar("m4l_unconstrained"), quadType, mela);
    m_outTree->updateFloatVar("MELA", mela);

    LOG(logDEBUG)<<"BDT_discriminant: "<<BDT_discriminant;

}


// To Caclulate the mass
void CalculateVar4l::fillMassVars()
{
    m_outTree->updateFloatVar("mZ1_unconstrained", m_higgs->getZ1()->getTLV().M()/1000);
    m_outTree->updateFloatVar("mZ2_unconstrained", m_higgs->getZ2()->getTLV().M()/1000);
    m_outTree->updateFloatVar("m4l_unconstrained", m_higgs->getTLV().M()/1000);

    m_outTree->updateFloatVar("pt4l_unconstrained", m_higgs->getTLV().Pt()/1000);
    m_outTree->updateFloatVar("eta4l_unconstrained", m_higgs->getTLV().Eta());
    m_outTree->updateFloatVar("phi4l_unconstrained", m_higgs->getTLV().Phi());
    m_outTree->updateFloatVar("y4l_unconstrained", m_higgs->getTLV().Rapidity());


    m_higgs->clearFSR();
    fillFSRVars();
    fillZMCVars();


    LOG(logDEBUG)<<"m4l_unconstrained: "<<m_outTree->getFloatVar("m4l_unconstrained");
    LOG(logDEBUG)<<"m4l_fsr: "<<m_outTree->getFloatVar("m4l_fsr");
    LOG(logDEBUG)<<"m4l_constrained: "<<m_outTree->getFloatVar("m4l_constrained");


    LOG(logDEBUG)<<"mZ1_unconstrained: "<<m_outTree->getFloatVar("mZ1_unconstrained");
    LOG(logDEBUG)<<"mZ1_fsr: "<<m_outTree->getFloatVar("mZ1_fsr");
    LOG(logDEBUG)<<"mZ1_constrained: "<<m_outTree->getFloatVar("mZ1_constrained");

    LOG(logDEBUG)<<"mZ2_unconstrained: "<<m_outTree->getFloatVar("mZ2_unconstrained");
    LOG(logDEBUG)<<"mZ2_fsr: "<<m_outTree->getFloatVar("mZ2_fsr");
    LOG(logDEBUG)<<"mZ2_constrained: "<<m_outTree->getFloatVar("mZ2_constrained");

    LOG(logDEBUG)<<"m4lerr_unconstrained: "<<m_outTree->getFloatVar("m4lerr_unconstrained");
    LOG(logDEBUG)<<"m4lerr_fsr: "<<m_outTree->getFloatVar("m4lerr_fsr");
    LOG(logDEBUG)<<"m4lerr_constrained: "<<m_outTree->getFloatVar("m4lerr_constrained");

}

void CalculateVar4l::fillFSRVars()
{
    // Caching the results
    if(m_isFSRFilled) return;
    m_isFSRFilled = true;


    vector< FSR::FsrCandidate> candidateVec;

    //fsrType::fsrType fsrTypeVar = fsrType::noFSR;
    FSR::FsrCandidate::FsrType fsrTypeVar = FSR::FsrCandidate::FsrUnknown;
    // Backup the FSR vars
    m_higgs->addAnalTLV(TLVType::FSR, m_higgs->getTLV(), true);
    m_higgs->getZ1()->addAnalTLV(TLVType::FSR, m_higgs->getZ1()->getTLV(), true);
    m_higgs->getZ2()->addAnalTLV(TLVType::FSR, m_higgs->getZ2()->getTLV(), true);

    if((m_phCont == 0) || (m_elCont == 0))
    {
        LOG(logERROR)<<"Calibrated el and ph container not set for FSR";
        exit(1);
    }


    // Getting the FSR Photon
    for (Int_t i = 0; i < (Int_t) m_higgs->getLepSize(); i++)
    {
        FSR::FsrCandidate cand;
        candidateVec.push_back(cand);

        if(m_higgs->getLep(i)->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* temp = dynamic_cast<const xAOD::Muon*> (m_higgs->getLep(i)->getParticle());
            if(temp->muonType() == xAOD::Muon::MuonStandAlone) continue;
            else if (temp->muonType() == xAOD::Muon::CaloTagged) continue;

            if(m_fsrTool->getFsrPhoton(m_higgs->getLep(i)->getParticle(), cand, m_phCont, m_elCont))
            {
                LOG(logDEBUG) <<"Found FSR candidate for muon "<<i;
                LOG(logDEBUG) <<"Candidate Et: "<<cand.Et<<" eta: "<<cand.eta<< " deltaR: "<<cand.deltaR<<" type: "<<cand.type;
            }
        }
        else if(m_higgs->getLep(i)->getPartType() == ParticleType::Electron)
        {
            if(m_fsrTool->getFsrPhoton(m_higgs->getLep(i)->getParticle(), cand, m_phCont, m_elCont))
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


    // Collinear only happens for 4mu or 2mu2el
    if(m_higgs->getQuadType() == QuadleptonType::_4mu || m_higgs->getQuadType() == QuadleptonType::_2mu2e)
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
            if((m_higgs->getZ1()->getTLV().M() < 89*1000) && (m_higgs->getZ1()->getTLV().M() > 66*1000))
            {
                LOG(logDEBUG) << "FSR collinear candidate passed the Z1 mass cut";

                TLorentzVector momFSR;
                momFSR.SetPtEtaPhiM(candidate.Et,candidate.eta,candidate.phi, 0.0);

                Double_t combMass = (m_higgs->getZ1()->getLepOne()->getTLV()
                        + m_higgs->getZ1()->getLepTwo()->getTLV()
                        + momFSR).M();
                if(combMass < 100*1000)
                {
                    LOG(logDEBUG)<<"FSR collinear candidate passed the combined mass cut";

                    // See which lepton to attach it do
                    int index = -1;
                    if(momFSR.DeltaR(m_higgs->getLep(0)->getTLV()) < momFSR.DeltaR(m_higgs->getLep(1)->getTLV())) index = 0;
                    else index = 1;
                    if(candidate.particle) candidate.particle->auxdecor<int>("associated_lep_fsr") = (int) index;

                    passFSRCollinear = true;
                    addFSRCandidate(candidate, 1);
                    fsrTypeVar = candidate.type;

                }
            }
        }
    }
    // If no collinear FSR has been found
    bool doFarFSR = m_higgs->getQuadType() == QuadleptonType::_4mu || m_higgs->getQuadType() == QuadleptonType::_2mu2e || m_higgs->getQuadType() == QuadleptonType::_4e || m_higgs->getQuadType() == QuadleptonType::_2e2mu;

    if(!passFSRCollinear && doFarFSR)
    {
        Double_t higestEt = -99999;
        Double_t minDeltaR = 10000;
        int index = -1;
        FSR::FsrCandidate candidate;
        Bool_t isFSR = false;
        
        int nCand = candidateVec.size();
        if(m_higgs->getTLV().M() < 190*1000) nCand = 2;

        // Loop over all the candidates and find the highest Et cluster far FSR
        for(Int_t i = 0; i < (Int_t) nCand; i++)
        {
            FSR::FsrCandidate tempCandidate = candidateVec[i];
            TLorentzVector momFSRTemp;
            momFSRTemp.SetPtEtaPhiM(tempCandidate.Et,tempCandidate.eta,tempCandidate.phi, 0.0);

            Bool_t passFSROvlp = false;
            // Do the overlap first
            for(Int_t i = 0; i < (Int_t) m_higgs->getLepSize(); i++)
            {
                if(momFSRTemp.DeltaR(m_higgs->getLep(i)->getTLV()) < 0.15) passFSROvlp = true;
            }

            if(passFSROvlp) continue;

            if(tempCandidate.deltaR < 0.15) continue;

            // Find the higest Et far photon on the cluster
            if(tempCandidate.Et != -1 && tempCandidate.Et > higestEt)
            {
                higestEt = tempCandidate.Et;
                minDeltaR = tempCandidate.deltaR;
                candidate = tempCandidate;
                index = i;
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
            for(Int_t i = 0; i < (Int_t) m_higgs->getLepSize(); i++)
            {
                if(momFSR.DeltaR(m_higgs->getLep(i)->getTLV()) < 0.15) deltaRCut = true;
                else
                {
                    LOG(logDEBUG)<<"FSR overlap with lepton";
                    LOG(logDEBUG)<<"Lepton Overlap";
                }
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
                if(m_higgs->getZ1()->getTLV().M() < 81*1000)
                {
                    TLorentzVector combined = m_higgs->getZ1()->getTLV() + momFSR;
                    if(combined.M() < 100 * 1000) deltaZ1Mass = fabs(combined.M() - pdgZMass);
                }
                if(m_higgs->getZ2()->getTLV().M() < 81*1000)
                {
                    TLorentzVector combined = m_higgs->getZ2()->getTLV() + momFSR;
                    if(combined.M() < 100 * 1000) deltaZ2Mass = fabs(combined.M() - pdgZMass);
                    if(m_higgs->getTLV().M() < 190*1000) deltaZ2Mass = 999999;
                }
                LOG(logDEBUG)<<"deltaZ1Mass: "<<deltaZ1Mass<<" deltaZ2Mass: "<<deltaZ2Mass;

                // Figuring out which dilepton to associate the far FSR photon with
                if(deltaZ1Mass < deltaZ2Mass && deltaZ1Mass != 999999)
                {
                    addFSRCandidate(candidate, 1);
                    passFSRFar = true;
                    fsrTypeVar = candidate.type;

                    // See which lepton to attach it do
                    int index = -1;
                    if(momFSR.DeltaR(m_higgs->getLep(0)->getTLV()) < momFSR.DeltaR(m_higgs->getLep(1)->getTLV())) index = 0;
                    else index = 1;
                    if(candidate.particle) candidate.particle->auxdecor<int>("associated_lep_fsr") = (int) index;


                    LOG(logDEBUG)<<"Far FSR Attached to Z1";
                    LOG(logDEBUG)<<"fsr_associated_lepton: "<<candidate.particle->auxdecor<int>("associated_lep_fsr");
                }
                else if (deltaZ2Mass < deltaZ1Mass && deltaZ2Mass != 999999)
                {
                    addFSRCandidate(candidate, 2);
                    passFSRFar = true;
                    fsrTypeVar = candidate.type;

                    // See which lepton to attach it do
                    int index = -1;
                    if(momFSR.DeltaR(m_higgs->getLep(2)->getTLV()) < momFSR.DeltaR(m_higgs->getLep(3)->getTLV())) index = 2;
                    else index = 3;
                    if(candidate.particle) candidate.particle->auxdecor<int>("associated_lep_fsr") = (int) index;

                    LOG(logDEBUG)<<"Far FSR attached to Z2";
                    LOG(logDEBUG)<<"fsr_associated_lepton: "<<candidate.particle->auxdecor<int>("associated_lep_fsr");
                }
            }
        }
    }

    if(passFSRCollinear){ LOG(logDEBUG)<<"Colinear FSR event"; }
    if(passFSRFar){ LOG(logDEBUG)<<"Far FSR event"; }

    Double_t m4lFSR = m_higgs->getAnalTLV(TLVType::FSR).M()/1000;
    Double_t mZ1FSR = m_higgs->getZ1()->getAnalTLV(TLVType::FSR).M()/1000;
    Double_t mZ2FSR = m_higgs->getZ2()->getAnalTLV(TLVType::FSR).M()/1000;

    m_outTree->updateFloatVar("mZ1_fsr", mZ1FSR);
    m_outTree->updateFloatVar("mZ2_fsr", mZ2FSR);
    m_outTree->updateFloatVar("m4l_fsr", m4lFSR);
    m_outTree->updateFloatVar("pt4l_fsr", m_higgs->getAnalTLV(TLVType::FSR).Pt()/1000);
    m_outTree->updateFloatVar("y4l_fsr", m_higgs->getAnalTLV(TLVType::FSR).Rapidity());
    m_outTree->updateIntVar("fsr_type", (int) fsrTypeVar);

    if(m_higgs->getZ1()->hasFSR())
    {
        m_outTree->updateFloatVar("fsr_pt", m_higgs->getZ1()->getFSR()->getAnalTLV(TLVType::Unconstrained).Pt()/1000);
        m_outTree->updateFloatVar("fsr_eta", m_higgs->getZ1()->getFSR()->getAnalTLV(TLVType::Unconstrained).Eta());
        m_outTree->updateFloatVar("fsr_phi", m_higgs->getZ1()->getFSR()->getAnalTLV(TLVType::Unconstrained).Phi());
        m_outTree->updateIntVar("fsr_associated_lepton", m_higgs->getZ1()->getFSR()->getParticle()->auxdecor<int>("associated_lep_fsr"));
    }
    else if(m_higgs->getZ2()->hasFSR())
    {
        m_outTree->updateFloatVar("fsr_pt", m_higgs->getZ2()->getFSR()->getAnalTLV(TLVType::Unconstrained).Pt()/1000);
        m_outTree->updateFloatVar("fsr_eta", m_higgs->getZ2()->getFSR()->getAnalTLV(TLVType::Unconstrained).Eta());
        m_outTree->updateFloatVar("fsr_phi", m_higgs->getZ2()->getFSR()->getAnalTLV(TLVType::Unconstrained).Phi());
        m_outTree->updateIntVar("fsr_associated_lepton", m_higgs->getZ2()->getFSR()->getParticle()->auxdecor<int>("associated_lep_fsr"));
    }
}

// Add FSR to photon
void CalculateVar4l::addFSRCandidate(FSR::FsrCandidate candidate, Int_t whichZ)
{

    LOG(logDEBUG)<< "cand et,eta,phi,dR,etCorr,type,index "
        << candidate.Et << "/" << candidate.eta << "/" << candidate.phi
        << "/" << candidate.deltaR << "/"
        << (400./cosh(candidate.eta)) << "/"
        /*<< candidate.topoEtcone40*/ << "/" << candidate.type;

    ParticleVar* partFSR = new ParticleVar(m_eventCont, candidate.particle, -1);
    m_partContainer.push_back(partFSR);
    partFSR->addAnalParticle(m_eventCont->m_analType, candidate.particle);

    // Recreate the TLV
    TLorentzVector fsrTLV;
    fsrTLV.SetPtEtaPhiM(candidate.Et, candidate.eta, candidate.phi, 0);


    partFSR->addAnalTLV(TLVType::Unconstrained, fsrTLV, true);
    partFSR->setAnalysisType(m_eventCont->m_analType);
    m_higgs->setFSR(partFSR, whichZ);
}

void CalculateVar4l::fillZMCVars()
{

    //ZMassConstraint::IConstraintFit* Izmc = const_cast<ZMassConstraint::IConstraintFit*>(&(*(m_massConstraint)));
    //ZMassConstraint::ConstraintFit* zmc = dynamic_cast<ZMassConstraint::ConstraintFit*>(Izmc);
    //
    //if(m_eventCont->eventInfo->eventNumber() == 1139339) 
    //{
    //    zmc->setProperty( "OutputLevel", MSG::VERBOSE).ignore();
    //    LOG::ReportingLevel() = LOG::FromString("DEBUG");
    //    
    //}
    //else 
    //{
    //    zmc->setProperty( "OutputLevel", MSG::FATAL).ignore();
    //    LOG::ReportingLevel() = LOG::FromString("INFO");  
    //}


    // Get the inputs
    ZMassConstraint::ConstraintFitOutput resultZ1;
    ZMassConstraint::ConstraintFitInput inputZ1 = getZMCInput(m_higgs->getZ1());

    ZMassConstraint::ConstraintFitInput inputZ2 = getZMCInput(m_higgs->getZ2());


    // ZMC on the Z1
    if (m_massConstraint->doMassFit(inputZ1, resultZ1).isFailure()) {
        LOG(logERROR) << "doMassConstraint: Unable to do mass contrained fit for Z1";
        exit(1);
    }
    m_higgs->getZ1()->getLepOne()->addAnalTLV(TLVType::Constrained, resultZ1.getConstituentFourVector(0), true);
    m_higgs->getZ1()->getLepTwo()->addAnalTLV(TLVType::Constrained, resultZ1.getConstituentFourVector(1), true);
    if(m_higgs->getZ1()->hasFSR())
    {
        m_higgs->getZ1()->getFSR()->addAnalTLV(TLVType::Constrained, resultZ1.getConstituentFourVector(2), true);
    }
    TLorentzVector z1TLV;
    resultZ1.getCompositeFourVector(z1TLV);
    m_higgs->getZ1()->addAnalTLV(TLVType::Constrained, z1TLV, true);

    // No Z2 ZMC
    m_higgs->getZ2()->getLepOne()->addAnalTLV(TLVType::Constrained, m_higgs->getZ2()->getLepOne()->getTLV(), true);
    m_higgs->getZ2()->getLepTwo()->addAnalTLV(TLVType::Constrained, m_higgs->getZ2()->getLepTwo()->getTLV(), true);
    if(m_higgs->getZ2()->hasFSR())
    {
        m_higgs->getZ2()->getFSR()->addAnalTLV(TLVType::Constrained, m_higgs->getZ2()->getFSR()->getTLV(), true);
    }
    m_higgs->getZ2()->addAnalTLV(TLVType::Constrained, m_higgs->getZ2()->getAnalTLV(TLVType::FSR),  true);


    m_higgs->addAnalTLV(TLVType::Constrained, m_higgs->getZ1()->getAnalTLV(TLVType::Constrained) + m_higgs->getZ2()->getAnalTLV(TLVType::Constrained), true);



    // Output
    m_outTree->updateFloatVar("mZ1_constrained", m_higgs->getZ1()->getAnalTLV(TLVType::Constrained).M()/1000);
    m_outTree->updateFloatVar("mZ2_constrained", m_higgs->getZ2()->getAnalTLV(TLVType::Constrained).M()/1000);
    m_outTree->updateFloatVar("m4l_constrained", m_higgs->getAnalTLV(TLVType::Constrained).M()/1000);
    m_outTree->updateFloatVar("pt4l_constrained", m_higgs->getAnalTLV(TLVType::Constrained).Pt()/1000);

    Double_t constrainedErr = m_massConstraint->getMassError(resultZ1, inputZ2);

    m_outTree->updateFloatVar("m4lerr_constrained", constrainedErr/1000.);

    // Fill in the other m4lerr as well
    m_outTree->updateFloatVar("m4lerr_fsr", m_massConstraint->getMassError(inputZ1, inputZ2)/1000);

    m_outTree->updateFloatVar("m4lerr_unconstrained", m_massConstraint->getMassError(getZMCInput(m_higgs->getZ1(), true), getZMCInput(m_higgs->getZ2(), true))/1000);

    std::array<float, 4> lepton_pt_constrained     = {{-999, -999, -999, -999}};
    for(int i = 0; i < 4; i++)
    {
        lepton_pt_constrained[i] =  m_higgs->getLep(i)->getAnalTLV(TLVType::Constrained).Pt()/1000;
    }
    m_outTree->updateFloatArrayVar("lepton_pt_constrained", lepton_pt_constrained);


    if(m_higgs->getZ1()->hasFSR())
    {
        m_outTree->updateFloatVar("fsr_pt_constrained", m_higgs->getZ1()->getFSR()->getAnalTLV(TLVType::Constrained).Pt()/1000);
    }
    else if(m_higgs->getZ2()->hasFSR())
    {
        m_outTree->updateFloatVar("fsr_pt_constrained", m_higgs->getZ2()->getFSR()->getAnalTLV(TLVType::Constrained).Pt()/1000);
    }



    // For High mass perform the ZMC is mass > 200
    ZMassConstraint::ConstraintFitOutput resultZ2;
    TLorentzVector combinedZ2;
    if(m_higgs->getTLV().M() > 00*1000)
    {
        if (m_massConstraint->doMassFit(inputZ2, resultZ2).isFailure()) {
            LOG(logERROR) << "doMassConstraint: Unable to do mass contrained fit for Z2";
            exit(1);
        }
        resultZ2.getCompositeFourVector(combinedZ2);
    }
    else
    {
        combinedZ2 = m_higgs->getZ2()->getTLV();
    }

    m_outTree->updateFloatVar("m4l_constrained_HM",(m_higgs->getZ1()->getAnalTLV(TLVType::Constrained)+combinedZ2).M()/1000);

    LOG(logDEBUG)<<"m4l_unconstrained: "<<m_outTree->getFloatVar("m4l_unconstrained");
    LOG(logDEBUG)<<"m4l_fsr: "<<m_outTree->getFloatVar("m4l_fsr");
    LOG(logDEBUG)<<"m4l_constrained: "<<m_outTree->getFloatVar("m4l_constrained");


    LOG(logDEBUG)<<"mZ1_unconstrained: "<<m_outTree->getFloatVar("mZ1_unconstrained");
    LOG(logDEBUG)<<"mZ1_fsr: "<<m_outTree->getFloatVar("mZ1_fsr");
    LOG(logDEBUG)<<"mZ1_constrained: "<<m_outTree->getFloatVar("mZ1_constrained");

    LOG(logDEBUG)<<"mZ2_unconstrained: "<<m_outTree->getFloatVar("mZ2_unconstrained");
    LOG(logDEBUG)<<"mZ2_fsr: "<<m_outTree->getFloatVar("mZ2_fsr");
    LOG(logDEBUG)<<"mZ2_constrained: "<<m_outTree->getFloatVar("mZ2_constrained");

    LOG(logDEBUG)<<"m4lerr_unconstrained: "<<m_outTree->getFloatVar("m4lerr_unconstrained");
    LOG(logDEBUG)<<"m4lerr_fsr: "<<m_outTree->getFloatVar("m4lerr_fsr");
    LOG(logDEBUG)<<"m4lerr_constrained: "<<m_outTree->getFloatVar("m4lerr_constrained");



    //zmc->setProperty( "OutputLevel", MSG::FATAL).ignore();
    //LOG::ReportingLevel() = LOG::FromString("INFO");  


}

ZMassConstraint::ConstraintFitInput CalculateVar4l::getZMCInput(ParticleDilepton* diLep, Bool_t skipFSR)
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

// Categorization
void CalculateVar4l::fillCategory()
{
    // Fill the jet var before
    fillJetVars();

    // New category
    Bool_t nJets2 = false;
    Bool_t nJets1 = false;
    Bool_t Mjj120 = false;
    Bool_t isolatedLep = false;

    Bool_t MjjEtaHM = false;

    if(m_jetList.size() >= 2)
    {
        nJets2 = true;
        const xAOD::Jet* leadingJet = dynamic_cast<const xAOD::Jet*>(m_leadingJet->getParticle());
        const xAOD::Jet* subleadingJet = dynamic_cast<const xAOD::Jet*>(m_subLeadingJet->getParticle());
        TLorentzVector sumJet = leadingJet->p4() + subleadingJet->p4();

        double deltaEta = fabs(leadingJet->eta() - subleadingJet->eta());
        if(sumJet.M() > 120*1000) Mjj120 = true;

        if(sumJet.M() > 400*1000 && deltaEta > 3.3)MjjEtaHM = true;
    }
    if(m_jetList.size() >= 1) nJets1 = true;

    // Extra Lepton
    vector<ParticleVar*> lepList = m_elList;
    lepList.insert(lepList.end(), m_muList.begin(), m_muList.end());
    // sort the vector
    std::sort (lepList.begin(), lepList.end(), sortParticleVarPt); 

    for (auto* lep: lepList)
    {
        if(isGoodExtraLepton(lep))
        {
            m_isExtraLep = true;
            isolatedLep = true;
            m_outTree->updateFloatVar("leading_additional_lepton_pt", lep->getTLV().Pt()/1000);
            break;
        }
    }

    //bJets info
    int n_jets_btag70 = 0;
    for(const auto jetVar: m_jetList)
    {
        if(jetVar->getParticle()->auxdecor<int>("isBjet70")) n_jets_btag70++;
    }


    prodTypeSimp::prodTypeSimp          currProductionType = prodTypeSimp::njet0;

    if((n_jets_btag70 > 0) && (m_jetList.size() > 3))   currProductionType = prodTypeSimp::ttH;
    else if((n_jets_btag70 > 0) && ((m_jetList.size() > 1) && isolatedLep))   currProductionType = prodTypeSimp::ttH;
    else if(isolatedLep)                currProductionType = prodTypeSimp::leptonic;
    else if(nJets2 && Mjj120)           currProductionType = prodTypeSimp::njet2_VBF;
    else if(nJets2 && !Mjj120)          currProductionType = prodTypeSimp::njet2_VH;
    else if(nJets1)                     currProductionType = prodTypeSimp::njet1;


    m_outTree->updateIntVar("prod_type", currProductionType);
    m_outTree->updateIntVar("isExtraLep", m_isExtraLep);


    // HM
    prodTypeHighMass::prodTypeHighMass  currProductionTypeHM = prodTypeHighMass::ggF_HM;
    if(MjjEtaHM)                        currProductionTypeHM = prodTypeHighMass::VBF_HM;

    m_outTree->updateIntVar("prod_type_HM", currProductionTypeHM);

    quadType::quadType currQuadType = quadType::other;

    if(m_higgs->getQuadType() == QuadleptonType::_4mu) currQuadType = quadType::_4mu;
    else if(m_higgs->getQuadType() == QuadleptonType::_2mu2e) currQuadType = quadType::_2mu2e;
    else if(m_higgs->getQuadType() == QuadleptonType::_2e2mu) currQuadType = quadType::_2e2mu;
    else if(m_higgs->getQuadType() == QuadleptonType::_4e) currQuadType = quadType::_4e;
    else if(m_higgs->getQuadType() == QuadleptonType::_emu2mu) currQuadType = quadType::_emu2mu;
    else currQuadType = quadType::other;

    m_outTree->updateIntVar("event_type", currQuadType);
}

// Categorization
void CalculateVar4l::fillCategoryfJVT()
{

    int nJets = m_jetList.size();
    const xAOD::Jet* leadingJet = 0;
    const xAOD::Jet* subleadingJet = 0;

    int countNJets = 0;
    for(int i = 0; i < nJets; i++)
    {
        LOG(logDEBUG)<<"fillCategoryfJVT: jetPt: "<<m_jetList[i]->getTLV().Pt()<<" fJVT: "<<int(m_jetList[i]->getParticle()->auxdata<char>("passFJVT"));
        if(m_jetList[i]->getParticle()->auxdata<char>("passFJVT") == 0) continue;
        countNJets++;

        if(!leadingJet) 
        { 
            leadingJet = dynamic_cast<const xAOD::Jet*>(m_jetList[i]->getParticle());
            continue;
        }
        if(!subleadingJet)
        { 
            subleadingJet = dynamic_cast<const xAOD::Jet*>(m_jetList[i]->getParticle());
            continue;
        }

    }

    // New category
    Bool_t nJets2 = false;
    Bool_t nJets1 = false;
    Bool_t Mjj120 = false;
    Bool_t isolatedLep = false;

    Bool_t MjjEtaHM = false;

    if(countNJets >= 2)
    {
        nJets2 = true;
        TLorentzVector sumJet = leadingJet->p4() + subleadingJet->p4();
        double deltaEta = fabs(leadingJet->eta() - subleadingJet->eta());

        LOG(logDEBUG)<<"fillCategoryfJVT: leading pt: "<<leadingJet->pt()/1000;
        LOG(logDEBUG)<<"fillCategoryfJVT: subleading pt: "<<subleadingJet->pt()/1000;
        LOG(logDEBUG)<<"fillCategoryfJVT: mJJ: "<<sumJet.M()/1000;

        if(sumJet.M() > 120*1000) Mjj120 = true;
        if(sumJet.M() > 400*1000 && deltaEta > 3.3)MjjEtaHM = true;
    }
    if(countNJets >= 1) nJets1 = true;

    // Extra Lepton
    vector<ParticleVar*> lepList = m_elList;
    lepList.insert(lepList.end(), m_muList.begin(), m_muList.end());
    // sort the vector
    std::sort (lepList.begin(), lepList.end(), sortParticleVarPt); 

    for (auto* lep: lepList)
    {
        if(isGoodExtraLepton(lep))
        {
            isolatedLep = true;
            break;
        }
    }

    //bJets info
    int n_jets_btag70 = 0;
    for(const auto jetVar: m_jetList)
    {
        if(jetVar->getParticle()->auxdata<char>("passFJVT") == 0) continue;        
        if(jetVar->getParticle()->auxdecor<int>("isBjet70")) n_jets_btag70++;
    }


    prodTypeSimp::prodTypeSimp          currProductionType = prodTypeSimp::njet0;

    if((n_jets_btag70 > 0) && (countNJets > 3))   currProductionType = prodTypeSimp::ttH;
    else if((n_jets_btag70 > 0) && ((countNJets > 1) && isolatedLep))   currProductionType = prodTypeSimp::ttH;
    else if(isolatedLep)                currProductionType = prodTypeSimp::leptonic;
    else if(nJets2 && Mjj120)           currProductionType = prodTypeSimp::njet2_VBF;
    else if(nJets2 && !Mjj120)          currProductionType = prodTypeSimp::njet2_VH;
    else if(nJets1)                     currProductionType = prodTypeSimp::njet1;


    m_outTree->updateIntVar("prod_type_w_fJVT", currProductionType);


    // HM
    prodTypeHighMass::prodTypeHighMass  currProductionTypeHM = prodTypeHighMass::ggF_HM;
    if(MjjEtaHM)                        currProductionTypeHM = prodTypeHighMass::VBF_HM;

    m_outTree->updateIntVar("prod_type_HM_w_fJVT", currProductionTypeHM);

    quadType::quadType currQuadType = quadType::other;
}

Bool_t CalculateVar4l::isGoodExtraLepton(ParticleVar* lep)
{
    LOG(logDEBUG)<<"isGoodExtraLepton - checking lepton: "<<lep->getTLV().Pt();
    if(m_higgs->isOverlap(lep)) return false;
    LOG(logDEBUG)<<"isGoodExtraLepton - Pass overlap cut";

    if(!(lep->getTLV().Pt() > 12*1000)) return false;
    LOG(logDEBUG)<<"isGoodExtraLepton - Extra Lep passed pt Cut";
    vector<ParticleVar*> vecLep;
    for(Int_t i = 0; i < m_higgs->getLepSize(); i++)
    {
        vecLep.push_back(m_higgs->getLep(i));
    }
    vecLep.push_back(lep);

    // deltaR Cut
    if(!m_cutQuad->cutDeltaR(vecLep)) return false;
    LOG(logDEBUG)<<"isGoodExtraLepton - Extra Lep passed DeltaR";
    // Iso Cut
    m_cutQuad->cutIsolation(vecLep);
    if(!lep->getParticle()->auxdecor< int >("isoCut")) return false;
    LOG(logDEBUG)<<"isGoodExtraLepton - Extra Lep passed Iso";

    // D0Sig
    m_cutQuad->cutD0Sig(vecLep);
    if(!lep->getParticle()->auxdecor< int >("passD0Sig")) return false;
    LOG(logDEBUG)<<"isGoodExtraLepton - Extra Lep passed D0";


    // In AnalysisBkg, the input electron might be very loose.
    // So we need to protect against that, just in case
    if(lep->getPartType() == ParticleType::Electron)
    {
        if(!lep->getParticle()->auxdecor< int >("looseID")) return false;
    }
    LOG(logDEBUG)<<"isGoodExtraLepton - Extra Lep passed LooseID";



    // Calo SA muon
    Int_t caloSACount = 0;
    for(Int_t i = 0; i < (Int_t) vecLep.size(); i++)
    {
        if(vecLep[i]->getPartType() == ParticleType::Muon)
        {
            const xAOD::Muon* temp = dynamic_cast<const xAOD::Muon*> (vecLep[i]->getParticle());
            if(temp->muonType() == xAOD::Muon::MuonStandAlone) caloSACount++;
            else if (temp->muonType() == xAOD::Muon::CaloTagged) caloSACount++;
            else if (temp->muonType() == xAOD::Muon::SiliconAssociatedForwardMuon) caloSACount++;
        }
    }

    if(caloSACount > 1) return false;
    LOG(logDEBUG)<<"isGoodExtraLepton - Extra Lep passed Muon Count";

    vecLep.clear();
    return true;
}

void CalculateVar4l::fillTruthMatched() {

    if(!m_eventCont->isMC) return;

    vector<const xAOD::TruthParticle*> tps = m_truthHelper->getRecoMatchTruth(m_higgs);
    vector<ParticleVar*> bornLeptons = m_truthHelper->getBornLeptonsFromBareLeptons(tps);
    vector<ParticleVar*> dressedLeptons = m_truthHelper->getDressedLeptonsFromBareLeptons(tps);


    TString VarBaseName[4] = {"Z1_lepplus", "Z1_lepminus", "Z2_lepplus", "Z2_lepminus"};

    std::array<float, 4> lepton_pt_truth_matched_bare    = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_phi_truth_matched_bare   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_eta_truth_matched_bare   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_m_truth_matched_bare     = {{-999, -999, -999, -999}};

    std::array<float, 4> lepton_pt_truth_matched_born    = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_phi_truth_matched_born   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_eta_truth_matched_born   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_m_truth_matched_born     = {{-999, -999, -999, -999}};

    std::array<float, 4> lepton_pt_truth_matched_dressed    = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_phi_truth_matched_dressed   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_eta_truth_matched_dressed   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_m_truth_matched_dressed     = {{-999, -999, -999, -999}};

    for(Int_t i = 0; i < (Int_t) tps.size(); i++)
    {
        if(tps[i])
        {
            TLorentzVector l = tps[i]->p4();

            lepton_pt_truth_matched_bare[i]     = l.Pt() / 1000.;
            lepton_phi_truth_matched_bare[i]    = l.Phi();
            lepton_eta_truth_matched_bare[i]    = l.Eta();
            lepton_m_truth_matched_bare[i]      = l.M()  / 1000.;

            TLorentzVector b = bornLeptons[i]->getTLV();

            lepton_pt_truth_matched_born[i]     = b.Pt() / 1000.;
            lepton_phi_truth_matched_born[i]    = b.Phi();
            lepton_eta_truth_matched_born[i]    = b.Eta();
            lepton_m_truth_matched_born[i]      = b.M()  / 1000.;

            TLorentzVector d = dressedLeptons[i]->getTLV();

            lepton_pt_truth_matched_dressed[i]     = d.Pt() / 1000.;
            lepton_phi_truth_matched_dressed[i]    = d.Phi();
            lepton_eta_truth_matched_dressed[i]    = d.Eta();
            lepton_m_truth_matched_dressed[i]      = d.M()  / 1000.;
            //if(m_eventCont->isDebug)
            //{
            //    LOG(logDEBUG)<<"Truth matched Bare Higgs";
            //    LOG(logDEBUG)<<"matched lep: "<<i<<" pt: "<<l.Pt()/1000<<" eta: "<<l.Eta()<<" phi: "<<l.Phi()<<" m: "<<l.M()/1000;
            //}
        }

    }

    m_outTree->updateFloatArrayVar("lepton_pt_truth_matched_bare", lepton_pt_truth_matched_bare);
    m_outTree->updateFloatArrayVar("lepton_phi_truth_matched_bare", lepton_phi_truth_matched_bare);
    m_outTree->updateFloatArrayVar("lepton_eta_truth_matched_bare", lepton_eta_truth_matched_bare);
    m_outTree->updateFloatArrayVar("lepton_m_truth_matched_bare", lepton_m_truth_matched_bare);

    m_outTree->updateFloatArrayVar("lepton_pt_truth_matched_born", lepton_pt_truth_matched_born);
    m_outTree->updateFloatArrayVar("lepton_phi_truth_matched_born", lepton_phi_truth_matched_born);
    m_outTree->updateFloatArrayVar("lepton_eta_truth_matched_born", lepton_eta_truth_matched_born);
    m_outTree->updateFloatArrayVar("lepton_m_truth_matched_born", lepton_m_truth_matched_born);

    m_outTree->updateFloatArrayVar("lepton_pt_truth_matched_dressed", lepton_pt_truth_matched_dressed);
    m_outTree->updateFloatArrayVar("lepton_phi_truth_matched_dressed", lepton_phi_truth_matched_dressed);
    m_outTree->updateFloatArrayVar("lepton_eta_truth_matched_dressed", lepton_eta_truth_matched_dressed);
    m_outTree->updateFloatArrayVar("lepton_m_truth_matched_dressed", lepton_m_truth_matched_dressed);

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

void CalculateVar4l::fillTruth()
{
    if(!m_eventCont->isMC) return;

    m_outTree->updateIntVar("truth_decay", m_truthHelper->getHiggsDecayTag());
    

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

    TLorentzVector z1, z2, q;
    q = truthBornHiggs->getTLV();
    z1 = truthBornHiggs->getZ1()->getTLV();
    z2 = truthBornHiggs->getZ2()->getTLV();

    m_outTree->updateFloatVar("m4l_truth_born", q.M() / 1000.);
    m_outTree->updateFloatVar("mZ1_truth_born", z1.M() / 1000.);
    m_outTree->updateFloatVar("mZ2_truth_born", z2.M() / 1000.);

    m_outTree->updateFloatVar("pt4l_truth_born", q.Pt() / 1000.);
    m_outTree->updateFloatVar("eta4l_truth_born", q.Eta());
    m_outTree->updateFloatVar("y4l_truth_born", q.Rapidity());

    std::array<float, 4> lepton_pt_truth_born    = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_phi_truth_born   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_eta_truth_born   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_m_truth_born     = {{-999, -999, -999, -999}};


    for(Int_t i = 0; i < 4; i++)
    {
        lepton_pt_truth_born[i]     = truthBornHiggs->getLep(i)->getTLV().Pt() / 1000.;
        lepton_phi_truth_born[i]    = truthBornHiggs->getLep(i)->getTLV().Phi();
        lepton_eta_truth_born[i]    = truthBornHiggs->getLep(i)->getTLV().Eta();
        lepton_m_truth_born[i]      = truthBornHiggs->getLep(i)->getTLV().M()  / 1000.;
    }

    m_outTree->updateFloatArrayVar("lepton_pt_truth_born", lepton_pt_truth_born);
    m_outTree->updateFloatArrayVar("lepton_phi_truth_born", lepton_phi_truth_born);
    m_outTree->updateFloatArrayVar("lepton_eta_truth_born", lepton_eta_truth_born);
    m_outTree->updateFloatArrayVar("lepton_m_truth_born", lepton_m_truth_born);
    m_outTree->updateIntVar("truth_event_type", m_truthHelper->getTruthHiggsType());
    
}

void CalculateVar4l::fillTruthPairing()
{
    if(!m_eventCont->isMC) return;

    vector<const xAOD::TruthParticle*> tps = m_truthHelper->getRecoMatchTruth(m_higgs);
    vector<ParticleVar*> bornLeptonsMatched = m_truthHelper->getBornLeptonsFromBareLeptons(tps);

    ParticleQuadlepton* truthBareHiggs = m_truthHelper->getBareQuadlepton();
    ParticleQuadlepton* truthBornHiggs = m_truthHelper->getBornQuadlepton(truthBareHiggs);

    // Sherpa - making the world more complicated for you! (TM) ... sigh
    if (m_eventCont->m_currGenerator == Generator::Sherpa){
        LOG(logDEBUG)<<"Sherpa Generator - matching bare";
        truthBornHiggs = truthBareHiggs;

        bornLeptonsMatched = m_truthHelper->getParticleVar(tps);
    }


    LOG(logDEBUG)<<"Truth Pairing";
    LOG(logDEBUG)<<"bornLeptonsMatched.size(): "<<bornLeptonsMatched.size();
    for(int i = 0; i < bornLeptonsMatched.size(); i++)
    {
        if(!bornLeptonsMatched[i]) continue;
        const xAOD::IParticle* tps = bornLeptonsMatched[i]->getParticle();
        //LOG(logDEBUG)<<"Born Matched: "<<tps;
        LOG(logDEBUG)<<"Born Matched: "<<i<<" pT: "<<tps->pt()/1000<<" eta: "<<tps->eta()<<" phi: "<<tps->phi()<<" m: "<<tps->m()/1000;
    }

    if(truthBornHiggs)
    {
        for(int i = 0; i < 4; i++)
        {
            if(truthBornHiggs->getLep(i)->getParticle()) 
            {
                const xAOD::IParticle* tps = truthBornHiggs->getLep(i)->getParticle();
                //LOG(logDEBUG)<<"Born truth: "<<tps;
                LOG(logDEBUG)<<"Born truth: "<<i<<" pT: "<<tps->pt()/1000<<" eta: "<<tps->eta()<<" phi: "<<tps->phi()<<" m: "<<tps->m()/1000;
            }
        }
    }


    PairingInfo::PairingInfo pairInfo = PairingInfo::unknown;

    if(truthBornHiggs && bornLeptonsMatched.size() == 4)
    {
        vector<const xAOD::TruthParticle*> tps_bornLeptonsMatched;
        vector<const xAOD::TruthParticle*> tps_bornLeptonsTruth;

        for(int i = 0; i < 4; i++)
        {
            const xAOD::TruthParticle* bornMatch = 0;
            const xAOD::TruthParticle* bornTruth = 0;
            if(bornLeptonsMatched[i]) 
                bornMatch = dynamic_cast<const xAOD::TruthParticle*>(bornLeptonsMatched[i]->getParticle());

            if(truthBornHiggs->getLep(i)->getParticle()) 
                bornTruth = dynamic_cast<const xAOD::TruthParticle*>(truthBornHiggs->getLep(i)->getParticle());

            tps_bornLeptonsMatched.push_back(bornMatch);
            //LOG(logDEBUG)<<"born Matched: "<<bornMatch;
            //LOG(logDEBUG)<<"Born Matched: "<<bornMatch<<" pT: "<<bornMatch->pt()/1000<<" eta: "<<bornMatch->eta()<<" phi: "<<bornMatch->phi()<<" m: "<<bornMatch->m()/1000;
            tps_bornLeptonsTruth.push_back(bornTruth);
            //LOG(logDEBUG)<<"born Truth: "<<bornTruth;
            //LOG(logDEBUG)<<"Born Matched: "<<bornTruth<<" pT: "<<bornTruth->pt()/1000<<" eta: "<<bornTruth->eta()<<" phi: "<<bornTruth->phi()<<" m: "<<bornTruth->m()/1000;
        }


        // if the pairing is correct
        bool correctPair4l = true;
        for(int i = 0; i < 4; i++)
        {
            //if (!deltaRMatch(tps_bornLeptonsMatched[i], tps_bornLeptonsTruth[i]))            
            if(tps_bornLeptonsMatched[i] != tps_bornLeptonsTruth[i]) 
            {
                correctPair4l = false;
                break;
            }
        }

        // check if there is incorrect lepton
        bool incorrectLep = false;
        bool incorrectLepZ1 = false;
        bool incorrectLepZ2 = false;

        // Check for incorrect lep
        for(int i = 0; i < 4; i++)
        {
            // if a turth born lepton is not in the born reco match, we have an incorrect lepton
            if(std::find(tps_bornLeptonsMatched.begin(), tps_bornLeptonsMatched.end(), tps_bornLeptonsTruth[i])==tps_bornLeptonsMatched.end())
            {
                incorrectLep = true;

                if(i < 2) incorrectLepZ1 = true;
                if(i >= 2) incorrectLepZ2 = true;
            }
        }

        bool notMatched = false;
        for(int i = 0; i < 4; i++)
        {
            if(!bornLeptonsMatched[i]) notMatched = true;
        }


        if(correctPair4l)                           pairInfo = PairingInfo::correct;
        else if(incorrectLepZ1 && incorrectLepZ2)   pairInfo = PairingInfo::wronglep;
        else if(incorrectLepZ1)                     pairInfo = PairingInfo::wronglep;
        else if(incorrectLepZ2)                     pairInfo = PairingInfo::wronglep;
        else                                        pairInfo = PairingInfo::misorder;

        LOG(logDEBUG)<<"Truth pair correctPair4l: "<<correctPair4l;
        LOG(logDEBUG)<<"Truth pair incorrectLep: "<<incorrectLep;
        LOG(logDEBUG)<<"Truth pair incorrectLepZ1: "<<incorrectLepZ1;
        LOG(logDEBUG)<<"Truth pair incorrectLepZ2: "<<incorrectLepZ2;
        LOG(logDEBUG)<<"Truth pair pairInfo: "<<pairInfo;
    }

    m_outTree->updateIntVar("truth_pairing", pairInfo);

}


Bool_t CalculateVar4l::deltaRMatch(const xAOD::TruthParticle* tp1, const xAOD::TruthParticle* tp2)
{
    if (m_eventCont->m_currGenerator == Generator::Sherpa){
        if (xAOD::P4Helpers::deltaR(*tp1, *tp2) == 0) {return true;}
    }
    else {
        if (tp1 == tp2) {return true; }
    }

    return false;
}


void CalculateVar4l::fillAngularVar()
{
    Float_t cthstr = -999;
    Float_t phi1 = -999;
    Float_t cth1 = -999;
    Float_t cth2 = -999;
    Float_t phi = -999;


    // This function requires z1 lep neg, z1 lep plus, z2 lep neg, z2 lep plus
    // weird ordering... sigh
    HZZUtils::helicityAngles(m_higgs->getLep(1)->getTLV(),
            m_higgs->getLep(0)->getTLV(),
            m_higgs->getLep(3)->getTLV(),
            m_higgs->getLep(2)->getTLV(),
            cthstr, phi1, cth1, cth2, phi);

    m_outTree->updateFloatVar("cthstr", cthstr);
    m_outTree->updateFloatVar("phi1", phi1);
    m_outTree->updateFloatVar("cth1", cth1);
    m_outTree->updateFloatVar("cth2", cth2);
    m_outTree->updateFloatVar("phi", phi);


    //FSR version of these, as requested by Andrea
    TLorentzVector Z1LepP = m_higgs->getLep(0)->getTLV();
    TLorentzVector Z1LepN = m_higgs->getLep(1)->getTLV();
    TLorentzVector Z2LepP = m_higgs->getLep(2)->getTLV();
    TLorentzVector Z2LepN = m_higgs->getLep(3)->getTLV();



    if(m_higgs->getZ1()->hasFSR())
    {
        if(m_higgs->getZ1()->getFSR()->getParticle()->auxdecor<int>("associated_lep_fsr") == 0)
        {
            Z1LepP += m_higgs->getZ1()->getFSR()->getTLV();
        }
        else
        {
            Z1LepN += m_higgs->getZ1()->getFSR()->getTLV();
        }
    }
    else if(m_higgs->getZ2()->hasFSR())
    {
        if(m_higgs->getZ2()->getFSR()->getParticle()->auxdecor<int>("associated_lep_fsr") == 2)
        {
            Z2LepP += m_higgs->getZ2()->getFSR()->getTLV();
        }
        else
        {
            Z2LepN += m_higgs->getZ2()->getFSR()->getTLV();
        }
    }

    // This function requires z1 lep neg, z1 lep plus, z2 lep neg, z2 lep plus
    // weird ordering... sigh
    HZZUtils::helicityAngles(Z1LepN,
            Z1LepP,
            Z2LepN,
            Z2LepP,
            cthstr, phi1, cth1, cth2, phi);

    m_outTree->updateFloatVar("cthstr_fsr", cthstr);
    m_outTree->updateFloatVar("phi1_fsr", phi1);
    m_outTree->updateFloatVar("cth1_fsr", cth1);
    m_outTree->updateFloatVar("cth2_fsr", cth2);
    m_outTree->updateFloatVar("phi_fsr", phi);



}

void CalculateVar4l::fillMET(TString sysName)
{
    if(!m_metCalc) return;

    // Fill FSR
    fillFSRVars();


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
    if(m_higgs->getZ1()->hasFSR()) phList.push_back(m_higgs->getZ1()->getFSR());
    if(m_higgs->getZ2()->hasFSR()) phList.push_back(m_higgs->getZ2()->getFSR());


    m_metCalc->setFSRParticles(phList);
    m_metCalc->process();

    const xAOD::MissingET* met = m_metCalc->getTrackMET();


    if(sysName.Length() > 1) sysName = "_"+sysName;

    m_outTree->updateFloatVar(("met_et"+sysName).Data(), met->met()/1000.);
    m_outTree->updateFloatVar(("met_sum_et"+sysName).Data(), met->sumet()/1000.);
    m_outTree->updateFloatVar(("met_phi"+sysName).Data(), met->phi());
}

void CalculateVar4l::fillFileInfo()
{
    if(m_eventCont->isMC) return;

    m_outTree->updateStringVar("file_name",m_eventCont->getChain()->GetFile()->GetPath());
    m_outTree->updateStringVar("sample_name",m_eventCont->fileName.Data());


}

void CalculateVar4l::fillVertexInfo()
{
    m_outTree->updateFloatVar("vtx4l_chi2ndf", m_cutQuad->getVertexQuality(m_higgs));
    m_outTree->updateIntVar("pass_vtx4lCut", m_cutQuad->cutVertex(m_higgs));
    LOG(logDEBUG)<<"Vertex value: "<<m_cutQuad->getVertexQuality(m_higgs)<<" pass_vtx4lCut: "<<m_cutQuad->cutVertex(m_higgs); 
}

void CalculateVar4l::fillSimpleXS()
{
    if(!m_eventCont->isMC) return;

    if(m_eventCont->eventInfo->isAvailable< int >( "HTXS_Stage0_Category" ))
    {
        m_outTree->updateIntVar("HTXS_Stage0_Category", m_eventCont->eventInfo->auxdata< int >( "HTXS_Stage0_Category" ));
        m_outTree->updateIntVar("HTXS_Stage1_Category_pTjet25", m_eventCont->eventInfo->auxdata< int >( "HTXS_Stage1_Category_pTjet25" ));
        m_outTree->updateIntVar("HTXS_Stage1_Category_pTjet30", m_eventCont->eventInfo->auxdata< int >( "HTXS_Stage1_Category_pTjet30" ));
    }
}

void CalculateVar4l::fillCatBDT()
{
    // Set input
    const xAOD::IParticle* m_leadingJetPart = 0;
    const xAOD::IParticle* m_subleadingJetPart = 0;

    if(m_leadingJet) m_leadingJetPart = m_leadingJet->getParticle();
    if(m_subLeadingJet) m_subleadingJetPart = m_subLeadingJet->getParticle();


    vector<const xAOD::IParticle*> jets;
    vector<const xAOD::IParticle*> leptons;

    // Get the jets
    if(m_leadingJetPart) jets.push_back(m_leadingJetPart);
    if(m_subleadingJetPart) jets.push_back(m_subleadingJetPart);


    // Get the leptons
    for(int i = 0; i < 4; i++)
    {
        leptons.push_back(m_higgs->getLep(i)->getParticle());
    }
    // To retrieve the results
    float resultME;
    float resultME_temp;
    bool  passesCut;
    float BDTScore;

    // One Jet BDT
    if(jets.size() == 1)
    {
        if(m_oneJet_jptetadR_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"One jet BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_OneJet_jptetadR_discriminant", BDTScore);
        LOG(logDEBUG)<<"BDT_OneJet_jptetadR_discriminant: "<<BDTScore;

        if(m_1J_pt4l_60_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_1J_pt4l_60_CatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_1Jet_pt4l_60", BDTScore);

        if(m_1J_pt4l_120_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_1J_pt4l_120_CatMVATool Calc failed";
        }
        m_outTree->updateFloatVar("BDT_1Jet_pt4l_120", BDTScore);

        if(m_1J_pt4l_60_120_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_1J_pt4l_60_120_CatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_1Jet_pt4l_60_120", BDTScore);

    }
    else if(jets.size() >= 1)
    {
        if(m_VBFCatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_VBFCatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_TwoJet_discriminant", BDTScore);

        if(m_VHnoPtHjjCatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_VHnoPtHjjCatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_VH_noptHjj_discriminant", BDTScore);

        if(m_VBF_TOPO_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_VBF_TOPO_CatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_VBF_TOPO", BDTScore);

        if(m_VBF_Rest_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_VBF_Rest_CatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_VBF_Rest", BDTScore);
    }
}


void CalculateVar4l::fillME()
{
    fillJetVars();
    if(!m_leadingJet) return;
    if(!m_subLeadingJet) return;

    // Set input
    const xAOD::IParticle* m_leadingJetPart = 0;
    const xAOD::IParticle* m_subleadingJetPart = 0;

    if(m_leadingJet) m_leadingJetPart = m_leadingJet->getParticle();
    if(m_subLeadingJet) m_subleadingJetPart = m_subLeadingJet->getParticle();


    vector<const xAOD::IParticle*> jets;
    vector<const xAOD::IParticle*> leptons;

    // Get the jets
    if(m_leadingJetPart) jets.push_back(m_leadingJetPart);
    if(m_subleadingJetPart) jets.push_back(m_subleadingJetPart);


    // Get the leptons
    for(int i = 0; i < 4; i++)
    {
        leptons.push_back(m_higgs->getLep(i)->getParticle());
    }
    // To retrieve the results
    float VBF_uux_ME = -999;


    //// Get the ME as well
    //if(m_oneJetCatMVATool->getVBF_ME(leptons, jets,
    //            VBF_uux_ME
    //            ).isFailure())
    //{
    //    LOG(logERROR)<<"VBF_uux_ME Calc failed";
    //}

    m_outTree->updateFloatVar("VBF_uux_ME", VBF_uux_ME );

}

float CalculateVar4l::fillMEVec(std::vector<float> ME)
{
    float sum_tmp = 0.;
    for (unsigned int i = 0; i < ME.size(); ++i){
        sum_tmp += ME.at(i);
    }
    sum_tmp = log(sum_tmp);
    return sum_tmp;
}


void CalculateVar4l::fillGRLDecision()
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

void CalculateVar4l::fillTruthJets()
{
    if(!m_eventCont->isMC) return;

    // Retrieve the jets
    const xAOD::JetContainer* truthJetCont = 0;
    m_eventCont->getEvent()->retrieve( truthJetCont, "AntiKt4TruthJets" ).isSuccess();

    // Get the truth born higgs
    ParticleQuadlepton* truthBareHiggs = m_truthHelper->getBareQuadlepton();
    ParticleQuadlepton* truthBornHiggs = m_truthHelper->getBornQuadlepton(truthBareHiggs);

    if(!truthBornHiggs) return; 

    int countJets_20 = 0;
    int countJets_25 = 0;
    int countJets_30 = 0;

    vector<const xAOD::Jet*> jetList;

    for( auto truthJet : *( truthJetCont ) )
    {
        bool overlap = false;

        for(int i = 0; i < 4; i++)
        {
            float deltaR = fabs(xAOD::P4Helpers::deltaR(*truthJet, 
                        *truthBornHiggs->getLep(i)->getParticle()));
            if(deltaR < 0.4)
            {
                overlap = true;
                break;
            }
        }
        // For David
        if(!overlap && (truthJet->pt() > 30 * 1000) ) countJets_30++;
        if(!overlap && (truthJet->pt() > 25 * 1000) ) countJets_25++;

        // For Higgs Pt Reweighing
        if(!overlap && (truthJet->pt() > 20 * 1000) )
        {
            countJets_20++;
            jetList.push_back(truthJet);
        }
    }

    // For David, jet bin migration
    m_outTree->updateIntVar("n_jets_truth_20", countJets_20);
    m_outTree->updateIntVar("n_jets_truth_25", countJets_25);
    m_outTree->updateIntVar("n_jets_truth_30", countJets_30);

    std::array<float, 4> jet_pt_truth    = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_phi_truth   = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_eta_truth   = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_m_truth     = {{-999, -999, -999, -999}};

    for(Int_t i = 0; i < (Int_t) jetList.size(); i++)
    {
        // Can only store 4 jets at the momemtn
        if(i > 3) break;

        TLorentzVector l = jetList[i]->p4();

        jet_pt_truth[i]     = l.Pt() / 1000.;
        jet_phi_truth[i]    = l.Phi();
        jet_eta_truth[i]    = l.Eta();
        jet_m_truth[i]      = jetList[i]->m()  / 1000.;

    }

    m_outTree->updateFloatArrayVar("jet_pt_truth", jet_pt_truth);
    m_outTree->updateFloatArrayVar("jet_phi_truth", jet_phi_truth);
    m_outTree->updateFloatArrayVar("jet_eta_truth", jet_eta_truth);
    m_outTree->updateFloatArrayVar("jet_m_truth", jet_m_truth);



}

void CalculateVar4l::fillTriggerVars()
{

    //for Muon
    m_outTree->updateLongIntVar("HLT_mu20_ivarloose_L1MU15", m_singleTrigger->singleTrigger("HLT_mu20_ivarloose_L1MU15"));
    m_outTree->updateLongIntVar("HLT_mu20_iloose_L1MU15", m_singleTrigger->singleTrigger("HLT_mu20_iloose_L1MU15"));
    m_outTree->updateLongIntVar("HLT_mu24_ivarloose_L1MU15", m_singleTrigger->singleTrigger("HLT_mu24_ivarloose_L1MU15"));
    m_outTree->updateLongIntVar("HLT_mu24_imedium", m_singleTrigger->singleTrigger("HLT_mu24_imedium"));
    m_outTree->updateLongIntVar("HLT_mu24_ivarmedium", m_singleTrigger->singleTrigger("HLT_mu24_ivarmedium"));
    m_outTree->updateLongIntVar("HLT_mu26_imedium", m_singleTrigger->singleTrigger("HLT_mu26_imedium"));
    m_outTree->updateLongIntVar("HLT_mu26_ivarmedium", m_singleTrigger->singleTrigger("HLT_mu26_ivarmedium"));
    m_outTree->updateLongIntVar("HLT_mu40", m_singleTrigger->singleTrigger("HLT_mu40"));
    m_outTree->updateLongIntVar("HLT_mu50", m_singleTrigger->singleTrigger("HLT_mu50"));
    m_outTree->updateLongIntVar("HLT_mu60", m_singleTrigger->singleTrigger("HLT_mu60"));
    m_outTree->updateLongIntVar("HLT_mu60_0eta105_msonly", m_singleTrigger->singleTrigger("HLT_mu60_0eta105_msonly"));
    m_outTree->updateLongIntVar("HLT_mu20_mu8noL1", m_singleTrigger->singleTrigger("HLT_mu20_mu8noL1"));
    m_outTree->updateLongIntVar("HLT_mu22_mu8noL1", m_singleTrigger->singleTrigger("HLT_mu22_mu8noL1"));
    m_outTree->updateLongIntVar("HLT_mu24_mu8noL1", m_singleTrigger->singleTrigger("HLT_mu24_mu8noL1"));
    m_outTree->updateLongIntVar("HLT_2mu10", m_singleTrigger->singleTrigger("HLT_2mu10"));
    m_outTree->updateLongIntVar("HLT_2mu14", m_singleTrigger->singleTrigger("HLT_2mu14"));
    m_outTree->updateLongIntVar("HLT_mu6_2mu4", m_singleTrigger->singleTrigger("HLT_mu6_2mu4"));
    m_outTree->updateLongIntVar("HLT_mu20_2mu4noL1", m_singleTrigger->singleTrigger("HLT_mu20_2mu4noL1"));
    m_outTree->updateLongIntVar("HLT_mu22_2mu4noL1", m_singleTrigger->singleTrigger("HLT_mu22_2mu4noL1"));
    m_outTree->updateLongIntVar("HLT_mu24_2mu4noL1", m_singleTrigger->singleTrigger("HLT_mu24_2mu4noL1"));
    m_outTree->updateLongIntVar("HLT_3mu4", m_singleTrigger->singleTrigger("HLT_3mu4"));
    m_outTree->updateLongIntVar("HLT_3mu6", m_singleTrigger->singleTrigger("HLT_3mu6"));
    m_outTree->updateLongIntVar("HLT_3mu6_msonly", m_singleTrigger->singleTrigger("HLT_3mu6_msonly"));
    m_outTree->updateLongIntVar("L1_2MU6_3MU4", m_singleTrigger->singleTrigger("L1_2MU6_3MU4"));
    //for Electron
    m_outTree->updateLongIntVar("HLT_e5_lhtight", m_singleTrigger->singleTrigger("HLT_e5_lhtight"));
    m_outTree->updateLongIntVar("HLT_e9_lhmedium", m_singleTrigger->singleTrigger("HLT_e9_lhmedium"));
    m_outTree->updateLongIntVar("HLT_e9_lhtight", m_singleTrigger->singleTrigger("HLT_e9_lhtight"));
    m_outTree->updateLongIntVar("HLT_e12_lhloose", m_singleTrigger->singleTrigger("HLT_e12_lhloose"));
    m_outTree->updateLongIntVar("HLT_e12_lhmedium", m_singleTrigger->singleTrigger("HLT_e12_lhmedium"));
    m_outTree->updateLongIntVar("HLT_e12_lhtight", m_singleTrigger->singleTrigger("HLT_e12_lhtight"));
    m_outTree->updateLongIntVar("HLT_e15_lhloose_L1EM13VH", m_singleTrigger->singleTrigger("HLT_e15_lhloose_L1EM13VH"));
    m_outTree->updateLongIntVar("HLT_e24_lhmedium_ivarloose", m_singleTrigger->singleTrigger("HLT_e24_lhmedium_ivarloose"));
    m_outTree->updateLongIntVar("HLT_e24_lhtight_ivarloose", m_singleTrigger->singleTrigger("HLT_e24_lhtight_ivarloose"));
    m_outTree->updateLongIntVar("HLT_e26_lhtight_ivarloose", m_singleTrigger->singleTrigger("HLT_e26_lhtight_ivarloose"));
    m_outTree->updateLongIntVar("HLT_e26_lhvloose_L1EM20VH", m_singleTrigger->singleTrigger("HLT_e26_lhvloose_L1EM20VH"));
    m_outTree->updateLongIntVar("HLT_e26_lhmedium_L1EM22VHI", m_singleTrigger->singleTrigger("HLT_e26_lhmedium_L1EM22VHI"));
    m_outTree->updateLongIntVar("HLT_e60_medium", m_singleTrigger->singleTrigger("HLT_e60_medium"));
    m_outTree->updateLongIntVar("HLT_e60_lhmedium", m_singleTrigger->singleTrigger("HLT_e60_lhmedium"));
    m_outTree->updateLongIntVar("HLT_e300_etcut", m_singleTrigger->singleTrigger("HLT_e300_etcut"));
    m_outTree->updateLongIntVar("HLT_e120_lhloose", m_singleTrigger->singleTrigger("HLT_e120_lhloose"));
    m_outTree->updateLongIntVar("HLT_e140_lhloose", m_singleTrigger->singleTrigger("HLT_e140_lhloose"));
    m_outTree->updateLongIntVar("HLT_2e12_lhvloose_L12EM10VH", m_singleTrigger->singleTrigger("HLT_2e12_lhvloose_L12EM10VH"));
    m_outTree->updateLongIntVar("HLT_2e15_lhvloose_L12EM13VH", m_singleTrigger->singleTrigger("HLT_2e15_lhvloose_L12EM13VH"));
    m_outTree->updateLongIntVar("HLT_2e17_lhvloose", m_singleTrigger->singleTrigger("HLT_2e17_lhvloose"));
    m_outTree->updateLongIntVar("HLT_2e22_lhvloose", m_singleTrigger->singleTrigger("HLT_2e22_lhvloose"));
    m_outTree->updateLongIntVar("HLT_e17_lhloose_2e9_lhloose", m_singleTrigger->singleTrigger("HLT_e17_lhloose_2e9_lhloose"));
    m_outTree->updateLongIntVar("HLT_e17_lhmedium_2e9_lhmedium", m_singleTrigger->singleTrigger("HLT_e17_lhmedium_2e9_lhmedium"));
    m_outTree->updateLongIntVar("L1_EM20VH_3EM10VH", m_singleTrigger->singleTrigger("L1_EM20VH_3EM10VH"));
    m_outTree->updateLongIntVar("L1_2EM20VH", m_singleTrigger->singleTrigger("L1_2EM20VH"));
    m_outTree->updateLongIntVar("L1_2EM22VH", m_singleTrigger->singleTrigger("L1_2EM22VH"));
    m_outTree->updateLongIntVar("L1_EM22VHI", m_singleTrigger->singleTrigger("L1_EM22VHI"));
    m_outTree->updateLongIntVar("L1_EM24VHI", m_singleTrigger->singleTrigger("L1_EM24VHI"));
    m_outTree->updateLongIntVar("L1_EM26VHI", m_singleTrigger->singleTrigger("L1_EM26VHI"));
    //for Tau
    m_outTree->updateLongIntVar("HLT_tau35_medium1_tracktwo_tau25_medium1_tracktwo", m_singleTrigger->singleTrigger("HLT_tau35_medium1_tracktwo_tau25_medium1_tracktwo"));
    m_outTree->updateLongIntVar("HLT_e17_lhmedium_nod0_ivarloose_tau25_medium1_tracktwo", m_singleTrigger->singleTrigger("HLT_e17_lhmedium_nod0_ivarloose_tau25_medium1_tracktwo"));
    m_outTree->updateLongIntVar("HLT_mu14_ivarloose_tau25_medium1_tracktwo_L1MU10_TAU12IM", m_singleTrigger->singleTrigger("HLT_mu14_ivarloose_tau25_medium1_tracktwo_L1MU10_TAU12IM"));
    //for Electron (nod0)
    m_outTree->updateLongIntVar("HLT_e24_lhmedium_nod0_ivarloose", m_singleTrigger->singleTrigger("HLT_e24_lhmedium_nod0_ivarloose"));
    m_outTree->updateLongIntVar("HLT_e24_lhtight_nod0_ivarloose", m_singleTrigger->singleTrigger("HLT_e24_lhtight_nod0_ivarloose"));
    m_outTree->updateLongIntVar("HLT_e26_lhtight_nod0_ivarloose", m_singleTrigger->singleTrigger("HLT_e26_lhtight_nod0_ivarloose"));
    m_outTree->updateLongIntVar("HLT_e28_lhtight_nod0_ivarloose", m_singleTrigger->singleTrigger("HLT_e28_lhtight_nod0_ivarloose"));
    m_outTree->updateLongIntVar("HLT_e60_lhmedium_nod0", m_singleTrigger->singleTrigger("HLT_e60_lhmedium_nod0"));
    m_outTree->updateLongIntVar("HLT_e120_lhloose_nod0", m_singleTrigger->singleTrigger("HLT_e120_lhloose_nod0"));
    m_outTree->updateLongIntVar("HLT_e140_lhloose_nod0", m_singleTrigger->singleTrigger("HLT_e140_lhloose_nod0"));
    m_outTree->updateLongIntVar("HLT_2e12_lhvloose_nod0_L12EM10VH", m_singleTrigger->singleTrigger("HLT_2e12_lhvloose_nod0_L12EM10VH"));
    m_outTree->updateLongIntVar("HLT_2e15_lhvloose_nod0_L12EM13VH", m_singleTrigger->singleTrigger("HLT_2e15_lhvloose_nod0_L12EM13VH"));
    m_outTree->updateLongIntVar("HLT_2e17_lhvloose_nod0", m_singleTrigger->singleTrigger("HLT_2e17_lhvloose_nod0"));
    m_outTree->updateLongIntVar("HLT_2e22_lhvloose_nod0", m_singleTrigger->singleTrigger("HLT_2e22_lhvloose_nod0"));
    m_outTree->updateLongIntVar("HLT_e17_lhloose_nod0_2e9_lhloose_nod0", m_singleTrigger->singleTrigger("HLT_e17_lhloose_nod0_2e9_lhloose_nod0"));
    m_outTree->updateLongIntVar("HLT_e17_lhmedium_nod0_2e9_lhmedium_nod0", m_singleTrigger->singleTrigger("HLT_e17_lhmedium_nod0_2e9_lhmedium_nod0"));
    //for Combined electron + muon
    m_outTree->updateLongIntVar("HLT_e7_lhmedium_mu24", m_singleTrigger->singleTrigger("HLT_e7_lhmedium_mu24"));
    m_outTree->updateLongIntVar("HLT_e17_lhloose_mu14", m_singleTrigger->singleTrigger("HLT_e17_lhloose_mu14"));
    m_outTree->updateLongIntVar("HLT_e24_medium_L1EM20VHI_mu8noL1", m_singleTrigger->singleTrigger("HLT_e24_medium_L1EM20VHI_mu8noL1"));
    m_outTree->updateLongIntVar("HLT_e24_lhmedium_L1EM20VHI_mu8noL1", m_singleTrigger->singleTrigger("HLT_e24_lhmedium_L1EM20VHI_mu8noL1"));
    m_outTree->updateLongIntVar("HLT_e26_lhmedium_L1EM22VHI_mu8noL1", m_singleTrigger->singleTrigger("HLT_e26_lhmedium_L1EM22VHI_mu8noL1"));
    m_outTree->updateLongIntVar("HLT_e12_lhloose_2mu10", m_singleTrigger->singleTrigger("HLT_e12_lhloose_2mu10"));
    m_outTree->updateLongIntVar("HLT_2e12_lhloose_mu10", m_singleTrigger->singleTrigger("HLT_2e12_lhloose_mu10"));
    //for Combined electron + muon (nod0)
    m_outTree->updateLongIntVar("HLT_e7_lhmedium_nod0_mu24", m_singleTrigger->singleTrigger("HLT_e7_lhmedium_nod0_mu24"));
    m_outTree->updateLongIntVar("HLT_e17_lhloose_nod0_mu14", m_singleTrigger->singleTrigger("HLT_e17_lhloose_nod0_mu14"));
    m_outTree->updateLongIntVar("HLT_e24_lhmedium_nod0_L1EM20VHI_mu8noL1", m_singleTrigger->singleTrigger("HLT_e24_lhmedium_nod0_L1EM20VHI_mu8noL1"));
    m_outTree->updateLongIntVar("HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1", m_singleTrigger->singleTrigger("HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1"));
    m_outTree->updateLongIntVar("HLT_e12_lhloose_nod0_2mu10", m_singleTrigger->singleTrigger("HLT_e12_lhloose_nod0_2mu10"));
    m_outTree->updateLongIntVar("HLT_2e12_lhloose_nod0_mu10", m_singleTrigger->singleTrigger("HLT_2e12_lhloose_nod0_mu10"));


}

bool CalculateVar4l::sortParticleVarPt (ParticleVar* i ,ParticleVar*j)
{
    return i->getTLV().Pt() > j->getTLV().Pt();
}

