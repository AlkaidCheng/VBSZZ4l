#include "H4lCutFlow/ToolInit4l.h"

// Tool include

#include "ElectronPhotonFourMomentumCorrection/IEgammaCalibrationAndSmearingTool.h"
#include "ElectronEfficiencyCorrection/AsgElectronEfficiencyCorrectionTool.h"
#include "ElectronPhotonSelectorTools/AsgElectronLikelihoodTool.h"
#include "ElectronPhotonSelectorTools/LikelihoodEnums.h"

#include "MuonMomentumCorrections/IMuonCalibrationAndSmearingTool.h"
#include "MuonEfficiencyCorrections/MuonTriggerScaleFactors.h"
#include "MuonEfficiencyCorrections/MuonEfficiencyScaleFactors.h"
#include "MuonSelectorTools/MuonSelectionTool.h"

#include "GoodRunsLists/GoodRunsListSelectionTool.h"

#include "TrigConfxAOD/xAODConfigTool.h"
#include "TrigDecisionTool/TrigDecisionTool.h"

#include "IsolationSelection/IsolationSelectionTool.h"
#include "IsolationSelection/IIsolationSelectionTool.h"
#include "IsolationSelection/IsolationCloseByCorrectionTool.h"
#include "IsolationCorrections/IsolationCorrectionTool.h"

#include "xAODBTaggingEfficiency/BTaggingEfficiencyTool.h"

#include "JetSelectorTools/JetCleaningTool.h"
#include "JetJvtEfficiency/JetJvtEfficiency.h"

#include "HZZUtils/ElectronMCClassification.h"
#include "HZZUtils/ElectronRecoClassification.h"
#include "HZZUtils/SampleShowerInfo.h"
#include "MCTruthClassifier/MCTruthClassifier.h"
#include "MCTruthClassifier/IMCTruthClassifier.h"

#include "FsrUtils/FsrPhotonTool.h"
#include "ZMassConstraint/ConstraintFit.h"
#include "H4lBDTWeights/H4lBDTWeights.h"
#include "CategoriesMVA/CategoriesMVA.h"

#include "HZZUtils/NLOreweighting.h"
#include "PMGTools/PMGSherpa22VJetsWeightTool.h"

#include "TrigBunchCrossingTool/BunchCrossingToolBase.h"
#include "MCFM_MatrixElement/MatrixElementProvider.h"


using namespace std;

ToolInit4l::ToolInit4l(EventContainer* eventcont):
    ToolInitBase(eventcont)
{


}

ToolInit4l::~ToolInit4l()
{
    // memory release is taken care by the base class for any asg tool
    // User is responsible for all the other
}


bool ToolInit4l::initialize()
{
    // Protection against data files where there are zero events
    if(m_eventCont->getEvent()->getEntries() == 0) return true;


    bool checkVar = true;

    bool checkVarBase   = ToolInitBase::initialize();
    bool checkVarPre    = initPreSelTools();
    bool checkVarTrig   = initTriggerTools();
    bool checkVarEg     = initEgTools();
    bool checkVarMu     = initMuTools();
    bool checkVarJet    = initJetTools();
    bool checkVarEff    = initEffTools();
    bool checkVarIso    = initIsoTools();
    bool checkVarOlv    = initOlvTools();
    bool checkVarCalc   = initCalcTools();
    bool checkVarLep    = initLepTools();

    checkVar = checkVarBase
        && checkVarPre
        && checkVarTrig
        && checkVarEg
        && checkVarMu
        && checkVarJet
        && checkVarEff
        && checkVarIso
        && checkVarOlv
        && checkVarCalc
        && checkVarLep;

    if (!checkVar)
    {
        LOG(logERROR)<<"ToolInit4l::initialize() - something went wrong with tool intiailization";
        LOG(logERROR)<<"checkVarBase: "<<checkVarBase;
        LOG(logERROR)<<"checkVarTrig: "<<checkVarTrig;
        LOG(logERROR)<<"checkVarEg: "<<checkVarEg;
        LOG(logERROR)<<"checkVarMu: "<<checkVarMu;
        LOG(logERROR)<<"checkVarJet: "<<checkVarJet;
        LOG(logERROR)<<"checkVarEff: "<<checkVarEff;
        LOG(logERROR)<<"checkVarIso: "<<checkVarIso;
        LOG(logERROR)<<"checkVarOlv: "<<checkVarOlv;
        LOG(logERROR)<<"checkVarCalc: "<<checkVarCalc;
        LOG(logERROR)<<"checkVarLep: "<<checkVarLep;
        exit(1);
    }


    return checkVar;

}

bool ToolInit4l::initCalcTools()
{
    // FSR tool
    FSR::FsrPhotonTool* m_fsrTool = new FSR::FsrPhotonTool("FSRTool");
    if(!m_fsrTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize FsrPhotonTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"FsrPhotonTool initialized";
    }
    addToolToVec(m_fsrTool);

    // BDT tool
    H4lBDTWeights* m_BDTtool = new H4lBDTWeights("H4lBDTWeights"); // Default is 2012 for now
    if(!m_BDTtool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize H4lBDTWeights";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"H4lBDTWeights initialized";
    }
    addToolToVec(m_BDTtool);


    // ZMass constraint
    if(m_eventCont->m_analType == AnalysisType::Fiducial)
    {
        LOG(logWARNING)<<"Fiducial Analysis - Will not Initialize ZMassConstraint.";
    } 
    else {
        ZMassConstraint::ConstraintFit* m_massConstraint = new ZMassConstraint::ConstraintFit("ZMassConstraint");

        RETURN_CHECK("initCalcTools", m_massConstraint->setProperty( "EgammaCalibAndSmearingTool",
                    ToolHandle<CP::IEgammaCalibrationAndSmearingTool>("EgammaCalibrationAndSmearingTool")));
        RETURN_CHECK("initCalcTools", m_massConstraint->setProperty( "MuonCalibrationAndSmearingTool",
                    ToolHandle<CP::IMuonCalibrationAndSmearingTool>("muonCalSmearTool")));

        m_massConstraint->setProperty( "OutputLevel", MSG::FATAL).ignore();
        //m_massConstraint->setProperty( "OutputLevel", MSG::DEBUG).ignore();

        if(!m_massConstraint->initialize().isSuccess())
        {
            LOG(logERROR)<<"Cannot intialize ZMassConstraint";
            exit(1);
        }
        else
        {
            LOG(logINFO)<<"ZMassConstraint initialized";
        }
        addToolToVec(m_massConstraint);
    }

    // NLO reweigh
    NLOreweighting* m_NLOreweighting = new NLOreweighting("NLOreweighting");
    //m_NLOreweighting->setProperty( "OutputLevel", MSG::DEBUG).ignore();
    
    if(!m_NLOreweighting->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize NLOreweighting";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"NLOreweighting initialized";
    }
    addToolToVec(m_NLOreweighting);


    PMGTools::PMGSherpa22VJetsWeightTool* pmgWeightTool = new PMGTools::PMGSherpa22VJetsWeightTool("PMGSherpa22VJetsWeightTool");
    RETURN_CHECK("initFirstEvent", pmgWeightTool->setProperty( "TruthJetContainer", "AntiKt4TruthJets"));

    if(!pmgWeightTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize PMGSherpa22VJetsWeightTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"NLOreweighting PMGSherpa22VJetsWeightTool";
    }
    addToolToVec(pmgWeightTool);



    // Two jet run 2 VBF MVA tool
    CategoriesMVA* VBFCatMVATool = new CategoriesMVA("VBF_ICHEP2016_30GeV_BinptHjj50");
    RETURN_CHECK("initCalcTools", VBFCatMVATool->setProperty("MVA_Type", ICategoriesMVA::VBF_Moriond2017));
    RETURN_CHECK("initCalcTools", VBFCatMVATool->initialize() );
    addToolToVec(VBFCatMVATool);

    // VH BDT
    CategoriesMVA* VHnoPtHjjCatMVATool = new CategoriesMVA("VH_ICHEP2016_30GeV_noptHjj");
    RETURN_CHECK("initCalcTools", VHnoPtHjjCatMVATool->setProperty("MVA_Type", ICategoriesMVA::VH_Moriond2017));
    RETURN_CHECK("initCalcTools", VHnoPtHjjCatMVATool->initialize() );
    addToolToVec(VHnoPtHjjCatMVATool);

    // one jet BDT
    CategoriesMVA* oneJet_jptetadR_CatMVATool = new CategoriesMVA("VBF_1j_ICHEP2016_jptetadR");
    RETURN_CHECK("initCalcTools", oneJet_jptetadR_CatMVATool->setProperty("MVA_Type", ICategoriesMVA::VBF_1j_ICHEP2016_jptetadR));
    RETURN_CHECK("initCalcTools", oneJet_jptetadR_CatMVATool->initialize() );
    addToolToVec(oneJet_jptetadR_CatMVATool);


    // New BDTs
    CategoriesMVA* CatMVATool = new CategoriesMVA("VBF_TOPO_Moriond2017");
    RETURN_CHECK("initCalcTools", CatMVATool->setProperty("MVA_Type", ICategoriesMVA::VBF_TOPO_Moriond2017));
    RETURN_CHECK("initCalcTools", CatMVATool->initialize() );
    addToolToVec(CatMVATool);

    CatMVATool = new CategoriesMVA("VBF_Rest_Moriond2017");
    RETURN_CHECK("initCalcTools", CatMVATool->setProperty("MVA_Type", ICategoriesMVA::VBF_Rest_Moriond2017));
    RETURN_CHECK("initCalcTools", CatMVATool->initialize() );
    addToolToVec(CatMVATool);

    CatMVATool = new CategoriesMVA("VBF_1j_pT4l_0_60_Moriond2017");
    RETURN_CHECK("initCalcTools", CatMVATool->setProperty("MVA_Type", ICategoriesMVA::VBF_1j_pT4l_0_60_Moriond2017));
    RETURN_CHECK("initCalcTools", CatMVATool->initialize() );
    addToolToVec(CatMVATool);

    CatMVATool = new CategoriesMVA("VBF_1j_pT4l_0_120_Moriond2017");
    RETURN_CHECK("initCalcTools", CatMVATool->setProperty("MVA_Type", ICategoriesMVA::VBF_1j_pT4l_0_120_Moriond2017));
    RETURN_CHECK("initCalcTools", CatMVATool->initialize() );
    addToolToVec(CatMVATool);

    CatMVATool = new CategoriesMVA("VBF_1j_pT4l_60_120_Moriond2017");
    RETURN_CHECK("initCalcTools", CatMVATool->setProperty("MVA_Type", ICategoriesMVA::VBF_1j_pT4l_60_120_Moriond2017));
    RETURN_CHECK("initCalcTools", CatMVATool->initialize() );
    addToolToVec(CatMVATool);



    Trig::BunchCrossingToolBase* bunchCrossingTool = new Trig::BunchCrossingToolBase("BunchCrossingTool");
    RETURN_CHECK("initCalcTools", bunchCrossingTool->initialize());
    addToolToVec(bunchCrossingTool);


   
    LOG(logINFO)<<"CategoriesMVA initialized";


    // MCFM ME Tool
    HSG2_MCFM::MatrixElementProvider* m_matrixElementProvider = new HSG2_MCFM::MatrixElementProvider("MatrixElementProvider");
    if(!m_matrixElementProvider->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize MatrixElementProvider";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"MatrixElementProvider initialized";
    }
    addToolToVec(m_matrixElementProvider);

    return true;
}


bool ToolInit4l::initPreSelTools()
{
    // GRL tool
    GoodRunsListSelectionTool* m_grl = new GoodRunsListSelectionTool("GoodRunsListSelectionTool"); 
    std::vector<std::string> grlList;

    // Final 2015 GRL
    const char* GRLFile1 = "GoodRunsLists/data15_13TeV/20160622/data15_13TeV.periodAllYear_DetStatus-v79-repro20-02_DQDefects-00-02-02_PHYS_StandardGRL_All_Good_25ns.xml";
    grlList.push_back(GRLFile1);

    // 2016 GRL
    const char* GRLFile2 = "GoodRunsLists/data16_13TeV/20170215/data16_13TeV.periodAllYear_DetStatus-v88-pro20-21_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml";
    grlList.push_back(GRLFile2);

    RETURN_CHECK("initCalcTools", m_grl->setProperty("GoodRunsListVec", grlList)); 
    if(!m_grl->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize GoodRunsListSelectionTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"GoodRunsListSelectionTool intialized";
    }
    addToolToVec(m_grl);

    return true;
}

bool ToolInit4l::initTriggerTools()
{
    if(m_eventCont->m_analType == AnalysisType::Fiducial)
    {
        LOG(logWARNING)<<"Fiducial Analysis - Will not initialize TrigConf::xAODConfigTool.";
        return true;
    }

    TrigConf::xAODConfigTool* configTool = new TrigConf::xAODConfigTool( "xAODConfigTool" );
    if(!configTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize TrigConf::xAODConfigTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"TrigConf::xAODConfigTool initialized";
    }

    Trig::TrigDecisionTool* tdt = new Trig::TrigDecisionTool( "TrigDecisionTool" );
    RETURN_CHECK("initTriggerTools", tdt->setProperty( "ConfigTool",
                ToolHandle<TrigConf::ITrigConfigTool>(configTool)));
    RETURN_CHECK("initTriggerTools", tdt->setProperty( "TrigDecisionKey", "xTrigDecision" ));

    if(!tdt->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize Trig::TrigDecisionTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"Trig::TrigDecisionTool initialized";
    }

    addToolToVec(tdt);

    return true;
}

bool ToolInit4l::initEgTools()
{
    // Initializing the tool for the likelihood cut
    AsgElectronLikelihoodTool* m_likelihoodCut = new AsgElectronLikelihoodTool("likelihoodCut");

    std::string m_ElectronLHconfFile = "";

    // New likelihood with 
    m_ElectronLHconfFile = "ElectronPhotonSelectorTools/offline/mc15_20160512/ElectronLikelihoodLooseOfflineConfig2016_CutBL_Smooth.conf";
    RETURN_CHECK("initEgTools", m_likelihoodCut->setProperty("ConfigFile",m_ElectronLHconfFile));
    if(!m_likelihoodCut->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize AsgElectronLikelihoodTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"AsgElectronLikelihoodTool initialized";
    }

    // Initializing the tool for the likelihood cut
    AsgElectronLikelihoodTool* m_likelihoodCutVL = new AsgElectronLikelihoodTool("likelihoodCutVL");
    std::string m_ElectronLHconfFileVL = "dev/ElectronPhotonSelectorTools/offline/mc15_20160512/ElectronLikelihoodVeryLooseOfflineConfig2016_CutBL_Smooth.conf";
    std::string inputPDFFile = "ElectronPhotonSelectorTools/offline/mc15_20160512/May11_2016_MCPDFs_for_20pt7_LH_TrkQProbes.root";

    RETURN_CHECK("initEgTools", m_likelihoodCutVL->setProperty("ConfigFile",m_ElectronLHconfFileVL));
    RETURN_CHECK("initFirstEvent", m_likelihoodCutVL->setProperty("inputPDFFileName", inputPDFFile));
    if(!m_likelihoodCutVL->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize AsgElectronLikelihoodTool Very Loose";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"AsgElectronLikelihoodTool Very Loose initialized";
    }

    // Initializing the tool for the likelihood cut
    AsgElectronLikelihoodTool* m_likelihoodCutM = new AsgElectronLikelihoodTool("likelihoodCutM");
    std::string m_ElectronLHconfFileM = "ElectronPhotonSelectorTools/offline/mc15_20160512/ElectronLikelihoodMediumOfflineConfig2016_Smooth.conf";
    RETURN_CHECK("initEgTools", m_likelihoodCutM->setProperty("ConfigFile",m_ElectronLHconfFileM));
    if(!m_likelihoodCutM->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize AsgElectronLikelihoodTool Medium";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"AsgElectronLikelihoodTool Medium initialized";
    }

    // Initializing the tool for the likelihood cut
    AsgElectronLikelihoodTool* m_likelihoodCutT = new AsgElectronLikelihoodTool("likelihoodCutT");
    std::string m_ElectronLHconfFileT = "ElectronPhotonSelectorTools/offline/mc15_20160512/ElectronLikelihoodTightOfflineConfig2016_Smooth.conf ";
    RETURN_CHECK("initEgTools", m_likelihoodCutT->setProperty("ConfigFile",m_ElectronLHconfFileT));
    if(!m_likelihoodCutT->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize AsgElectronLikelihoodTool Tight";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"AsgElectronLikelihoodTool Tight initialized";
    }

    addToolToVec(m_likelihoodCut);
    addToolToVec(m_likelihoodCutVL);
    addToolToVec(m_likelihoodCutM);
    addToolToVec(m_likelihoodCutT);

    return true;
}

bool ToolInit4l::initMuTools()
{
    CP::MuonSelectionTool* m_muonSelector = new CP::MuonSelectionTool("MuonSelectionTool");
    // Specific eta cuts futher inside the code
    //RETURN_CHECK("initMuTools", m_muonSelector->setProperty( "OutputLevel", MSG::VERBOSE));
    RETURN_CHECK("initMuTools", m_muonSelector->setProperty("MaxEta", 2.7));
    RETURN_CHECK("initMuTools", m_muonSelector->setProperty("MuQuality", (int)xAOD::Muon::Loose));
    RETURN_CHECK("initMuTools", m_muonSelector->setProperty("TrtCutOff", true));

    if(!m_muonSelector->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize MuonSelectionTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"MuonSelectionTool initialized";

    }
    addToolToVec(m_muonSelector);


    //CP::MuonTriggerScaleFactors* m_trig_sf = new CP::MuonTriggerScaleFactors("muTrigSF");
    //RETURN_CHECK("initMuTools", m_trig_sf->setProperty("MuonQuality","Loose"));

    //if(!m_trig_sf->initialize().isSuccess())
    //{
    //    LOG(logERROR)<<"Cannot intialize MuonTriggerScaleFactors";
    //    exit(1);
    //}
    //else
    //{
    //    LOG(logINFO)<<"MuonTriggerScaleFactors initialized";

    //}
    //addToolToVec(m_trig_sf);

    return true;
}

bool ToolInit4l::initJetTools()
{    
    JetCleaningTool* m_jetCleaningTool = new JetCleaningTool("JetCleaningTool");
    RETURN_CHECK("initJetTools",m_jetCleaningTool->setProperty("CutLevel", "LooseBad")); // also "TightBad"
    RETURN_CHECK("initJetTools",m_jetCleaningTool->setProperty("DoUgly", false));

    if(!m_jetCleaningTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize JetCleaningTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"JetCleaningTool initialized";
    }
    addToolToVec(m_jetCleaningTool);

    CP::JetJvtEfficiency* jetJVTEffTool = new CP::JetJvtEfficiency("JetJvtEfficiency");
    RETURN_CHECK("initFirstEvent", jetJVTEffTool->setProperty("SFFile","JetJvtEfficiency/Moriond2017/JvtSFFile_EM.root"));
    if(!jetJVTEffTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize jetJVTEffTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"jetJVTEffTool initialized";
    }
    addToolToVec(jetJVTEffTool);

    CP::JetJvtEfficiency* jetfJVTEffTool = new CP::JetJvtEfficiency("JetFJvtEfficiency");
    RETURN_CHECK("initJetTools", jetfJVTEffTool->setProperty("SFFile","JetJvtEfficiency/Moriond2016_v2/fJvtSFFile.root"));

    if(!jetfJVTEffTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize JetFJvtEfficiency";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"JetFJvtEfficiency initialized";
    }
    addToolToVec(jetfJVTEffTool);


    return true;
}


bool ToolInit4l::initEffTools()
{
    // ID tool
    AsgElectronEfficiencyCorrectionTool* m_egSFClassID = new AsgElectronEfficiencyCorrectionTool("IDSFTool");

    std::vector< std::string > corrFileNameListID;

    corrFileNameListID.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/offline/efficiencySF.offline.LooseAndBLayerLLH_d0z0_v11.root");
    RETURN_CHECK("initEffTools", m_egSFClassID->setProperty("CorrectionFileNameList",corrFileNameListID));
    RETURN_CHECK("initEffTools", m_egSFClassID->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Full));
    // Reduced Sys
    if(m_doReducedSys)
    {
        RETURN_CHECK("initEffTools", m_egSFClassID->setProperty("CorrelationModel", "TOTAL"));
    }
    else
    { 
        RETURN_CHECK("initEffTools", m_egSFClassID->setProperty("CorrelationModel", "SIMPLIFIED"));
    }
    if(!m_egSFClassID->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize Electron ID SF tool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"Electron ID SF tool initialized";
    }
    addToolToVec(m_egSFClassID);



    // Reco tool
    AsgElectronEfficiencyCorrectionTool* m_egSFClassReco = new AsgElectronEfficiencyCorrectionTool("RecoSFTool");

    std::vector< std::string > corrFileNameListReco;
    corrFileNameListReco.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/offline/efficiencySF.offline.RecoTrk.root");
    RETURN_CHECK("initEffTools", m_egSFClassReco->setProperty("CorrectionFileNameList",corrFileNameListReco));
    RETURN_CHECK("initEffTools", m_egSFClassReco->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Full));
    RETURN_CHECK("initEffTools", m_egSFClassReco->setProperty("CorrelationModel", "TOTAL"));
    if(!m_egSFClassReco->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize Electron ID Reco tool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"Electron ID Reco tool initialized";
    }
    addToolToVec(m_egSFClassReco);


    AsgElectronEfficiencyCorrectionTool* m_egSFClassIso = new AsgElectronEfficiencyCorrectionTool("ElIsoSFTool");

    std::vector< std::string > corrFileNameListIso;
    corrFileNameListIso.push_back("ElectronEfficiencyCorrection/2015_2016/rel20.7/Moriond_February2017_v1/isolation/efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v11_isolFixedCutLoose.root");
    RETURN_CHECK("initEffTools", m_egSFClassIso->setProperty("CorrectionFileNameList",corrFileNameListIso));
    RETURN_CHECK("initEffTools", m_egSFClassIso->setProperty("ForceDataType",(int) PATCore::ParticleDataType::Full));
    RETURN_CHECK("initEffTools", m_egSFClassIso->setProperty("CorrelationModel", "TOTAL"));

    if(!m_egSFClassIso->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize Electron Iso SF tool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"Electron Iso SF tool initialized";
    }
    addToolToVec(m_egSFClassIso);


    CP::MuonEfficiencyScaleFactors* m_effTool = new CP::MuonEfficiencyScaleFactors("MuonSFClass");
    // Current default settings
    RETURN_CHECK("initEffTools", m_effTool->setProperty("WorkingPoint", "Loose"));
    RETURN_CHECK("initEffTools", m_effTool->setProperty("CalibrationRelease", "170303_Moriond_noTRT"));
    //RETURN_CHECK("initEffTools", m_effTool->setProperty("PileupReweightingTool",ToolHandle<CP::IPileupReweightingTool>("PileupTool")));

    if(!m_effTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize MuonEfficiencyScaleFactors";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"MuonEfficiencyScaleFactors initialized";
    }
    addToolToVec(m_effTool);

    CP::MuonEfficiencyScaleFactors* m_effIsoTool = new CP::MuonEfficiencyScaleFactors("MuonSFIso");
    // Current default settings
    RETURN_CHECK("initEffTools", m_effIsoTool->setProperty("WorkingPoint", "FixedCutLooseIso"));
    RETURN_CHECK("initEffTools", m_effIsoTool->setProperty("ScaleFactorDecorationName", "IsoEfficiencyScaleFactor"));
    RETURN_CHECK("initEffTools", m_effIsoTool->setProperty("CalibrationRelease", "170303_Moriond_noTRT"));
    //RETURN_CHECK("initEffTools", m_effIsoTool->setProperty("PileupReweightingTool",ToolHandle<CP::IPileupReweightingTool>("PileupTool")));
    if(!m_effIsoTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize MuonEfficiencyScaleFactors for Iso SF";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"MuonEfficiencyScaleFactors for Iso SF initialized";
    }
    addToolToVec(m_effIsoTool);


    CP::MuonEfficiencyScaleFactors* m_effd0Tool = new CP::MuonEfficiencyScaleFactors("MuonSFd0");
    // Current default settings
    RETURN_CHECK("initEffTools", m_effd0Tool->setProperty("WorkingPoint", "TTVA"));
    RETURN_CHECK("initEffTools", m_effd0Tool->setProperty("ScaleFactorDecorationName", "IPEfficiencyScaleFactor"));
    //RETURN_CHECK("initEffTools", m_effd0Tool->setProperty("CalibrationRelease", "170303_Moriond_noTRT"));
    RETURN_CHECK("initEffTools", m_effd0Tool->setProperty("CalibrationRelease", "170303_Moriond_noTRT"));
    //RETURN_CHECK("initEffTools", m_effd0Tool->setProperty("CustomInputFolder", "/afs/cern.ch/user/n/nkoehler/public/MCP/ScaleFactorFiles/170303_Moriond_noTRT"));
    //RETURN_CHECK("initEffTools", m_effd0Tool->setProperty("PileupReweightingTool",ToolHandle<CP::IPileupReweightingTool>("PileupTool")));
    m_effd0Tool->setProperty( "OutputLevel", MSG::VERBOSE).ignore();
    if(!m_effd0Tool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize MuonEfficiencyScaleFactors for do SF";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"MuonEfficiencyScaleFactors for d0 SF initialized";
    }
    addToolToVec(m_effd0Tool);


    // Btagging
    // Initialize b-jet tagging efficiency tool
    BTaggingEfficiencyTool* m_btagEffTool = new BTaggingEfficiencyTool("BTagEffTool_70");

    // Configure BTaggingEfficiencyTool properties
    RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("TaggerName", "MV2c10"));
    RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("OperatingPoint", "FixedCutBEff_70"));
    RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("JetAuthor", "AntiKt4EMTopoJets"));
    RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("ScaleFactorFileName", "xAODBTaggingEfficiency/13TeV/2016-20_7-13TeV-MC15-CDI-2017-01-31_v1.root"));

    std::string effMap = "";
    SampleShowerInfo::fillEffMapForBTag(effMap);
    LOG(logINFO)<<"Shower MC info for bTagging sf tool: "<<effMap;

    RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("EfficiencyBCalibrations",     effMap));
    RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("EfficiencyCCalibrations",     effMap));
    RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("EfficiencyTCalibrations",     effMap));
    RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("EfficiencyLightCalibrations", effMap));


    // Reduced Sys
    if(m_doReducedSys)
    {
        RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("SystematicsStrategy", "Envelope"));
    }
    else
    { 
        RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("EigenvectorReductionB", "Medium"));
        RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("EigenvectorReductionC", "Medium"));
        RETURN_CHECK("initBtagTools", m_btagEffTool->setProperty("EigenvectorReductionLight", "Medium"));
    }

    if (!m_btagEffTool->initialize().isSuccess()) {
        LOG(logERROR)<<"Cannot intialize BTaggingEfficiencyTool_70";
        exit(1);
    }
    else {
        LOG(logINFO)<<"BTaggingEfficiencyTool_70 initialized";
    }
    addToolToVec(m_btagEffTool);

    // Set the correct index for bTagging shower
    int index = 0;
    std::string showerMCName = "";    
    SampleShowerInfo::fillSampleShowerInfo(m_eventCont->fileName.Data(), showerMCName);
    SampleShowerInfo::fillIndexForBTag(m_eventCont->fileName.Data(), index);
    LOG(logINFO)<<"Setting Shower MC index to : "<<index<<" shower MC name: "<<showerMCName;


    m_btagEffTool->setMapIndex("B",     index);
    m_btagEffTool->setMapIndex("C",     index);
    m_btagEffTool->setMapIndex("T",     index);
    m_btagEffTool->setMapIndex("Light", index);




    return true;
}


bool ToolInit4l::initIsoTools()
{
    CP::IsolationSelectionTool* m_isoTool = new CP::IsolationSelectionTool("isoTool");
    RETURN_CHECK("initIsoTools", m_isoTool->setProperty("MuonWP","FixedCutLoose"));
    if(!m_isoTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize IsolationSelectionTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"IsolationSelectionTool initialized";
    }
    addToolToVec(m_isoTool);

    ToolHandle<CP::IIsolationSelectionTool> m_iIsoSelTool = m_isoTool;

    CP::IsolationSelectionTool* m_isoToolEl = new CP::IsolationSelectionTool("isoToolEl");
    RETURN_CHECK("initIsoTools", m_isoToolEl->setProperty("ElectronWP","FixedCutLoose"));
    if(!m_isoToolEl->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize IsolationSelectionTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"IsolationSelectionTool initialized";
    }
    addToolToVec(m_isoToolEl);

    ToolHandle<CP::IIsolationSelectionTool> m_iIsoSelToolEl = m_isoToolEl;


    CP::IsolationCloseByCorrectionTool* m_isoSelMu = new CP::IsolationCloseByCorrectionTool("isoSelMu");
    //RETURN_CHECK("initFirstEvent", m_isoSelMu->setProperty("OutputLevel", MSG::ERROR));
    RETURN_CHECK("initFirstEvent", m_isoSelMu->setProperty("IsolationSelectionTool", m_iIsoSelTool));
    if(!m_isoSelMu->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize isoSelMu";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"isoSelMu initialized";
    }
    addToolToVec(m_isoSelMu);



    CP::IsolationCloseByCorrectionTool* m_isoSelEl = new CP::IsolationCloseByCorrectionTool("isoSelEl");
    //RETURN_CHECK("initFirstEvent", m_isoSelEl->setProperty("OutputLevel", MSG::ERROR));
    RETURN_CHECK("initFirstEvent", m_isoSelEl->setProperty("IsolationSelectionTool", m_iIsoSelToolEl));
    if(!m_isoSelEl->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize m_isoSelEl";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"m_isoSelEl initialized";
    }
    addToolToVec(m_isoSelEl);



    // Isolation correction
    CP::IsolationCorrectionTool* isoCorrTool = new CP::IsolationCorrectionTool("isoCorrTool");
    RETURN_CHECK("initIsoTools", isoCorrTool->setProperty( "IsMC", m_eventCont->isMC));
    if(!isoCorrTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize IsolationCorrectionTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"IsolationCorrectionTool initialized";
    }
    addToolToVec(isoCorrTool);


    return true;
}


bool ToolInit4l::initOlvTools()
{

    /*
    // Initialize the harmonization reccommendation tools
    RETURN_CHECK("initOlvTools", ORUtils::harmonizedTools(toolBox, "OverlapRemovalTool", "selected", "overlaps", false, false, false) );

    // Override property that rejects leptons in favour of jets 
    RETURN_CHECK("initOlvTools", toolBox.getTool("EleJetORT")->setProperty("OuterDR", 0) );
    RETURN_CHECK("initOlvTools", toolBox.getTool("MuJetORT")->setProperty("OuterDR", 0) );

    // Override property to activate mu-jet sliding-DR OR
    //CHECK( toolBox.getTool("MuJetORT")->setProperty("UseSlidingDR", true) );

    // For control regions, we set links to electrons to be able to ignore overlap for certain
    // electrons, e.g. not LooseLH
    RETURN_CHECK("initOlvTools", toolBox.getTool("EleJetORT")->setProperty("LinkOverlapObjects", true) );
    RETURN_CHECK("initOlvTools", toolBox.getTool("MuJetORT")->setProperty("LinkOverlapObjects", true) );
    // Set message level for all tools
    toolBox.setMsgLevel(MSG::DEBUG);

    // Initialize all tools
    //RETURN_CHECK("initOlvTools", toolBox.initialize() );
    if(!toolBox.initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize OverlapRemovalTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"OverlapRemovalTool initialized";
    }
    ToolHandle<ORUtils::IOverlapRemovalTool> orTool = toolBox.getMasterHandle();

    */

    ORUtils::ORFlags orFlags("OverlapRemovalTool", "selected", "overlaps");
    orFlags.doTaus    = false;
    orFlags.doPhotons = false;
    RETURN_CHECK("initOlvTools",  ORUtils::recommendedTools(orFlags, toolBox) );
    RETURN_CHECK("initOlvTools",  toolBox.eleJetORT.setProperty("OuterDR", 0.) );
    RETURN_CHECK("initOlvTools",  toolBox.muJetORT.setProperty("OuterDR", 0.) );
    //RETURN_CHECK("initOlvTools", toolBox.setGlobalProperty("OutputLevel", MSG::DEBUG) );

    RETURN_CHECK("initOlvTools", toolBox.eleJetORT.setProperty("LinkOverlapObjects", true) );
    RETURN_CHECK("initOlvTools", toolBox.muJetORT.setProperty("LinkOverlapObjects",  true) );
    RETURN_CHECK("initOlvTools", toolBox.eleMuORT.setProperty("LinkOverlapObjects",  true) );
    RETURN_CHECK("initOlvTools", toolBox.initialize() );

    return true;
}


bool ToolInit4l::initLepTools()
{
    // electron reco and MC classifier tool
    MCTruthClassifier* m_MCClassifier = new MCTruthClassifier("MCClassifier");

    RETURN_CHECK("initLepTools", m_MCClassifier->setProperty("xAODTruthParticleContainerName", "TruthParticles"));
    if(!m_MCClassifier->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize MCClassification";
        exit(1);
    }
    else LOG(logINFO)<<"MC Classification initialized";
    addToolToVec(m_MCClassifier);


    ElectronMCClassification* m_electronMCClassifier = new ElectronMCClassification("elMCClassifier");
    RETURN_CHECK("initLepTools", m_electronMCClassifier->setProperty("MCTruthClassifierTool", ToolHandle<IMCTruthClassifier>("MCClassifier")));
    if(!m_electronMCClassifier->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize ElectronMCClassification";
        exit(1);
    }
    else LOG(logINFO)<<"ElectronMCClassification initialized";
    addToolToVec(m_electronMCClassifier);

    ElectronRecoClassification* m_recoClassification = new ElectronRecoClassification("recoClassification");
    LOG(logINFO)<<"ElectronRecoClassification initialized";
    addToolToVec(m_recoClassification);


    return true;
}

