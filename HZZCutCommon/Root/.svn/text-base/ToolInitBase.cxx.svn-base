#include "HZZCutCommon/ToolInitBase.h"

// Tool include
// Jet
#include "JetMomentTools/JetVertexTaggerTool.h"
#include "JetMomentTools/JetForwardJvtTool.h"
#include "JetCalibTools/JetCalibrationTool.h"
#include "JetUncertainties/JetUncertaintiesTool.h"
#include "JetResolution/JERTool.h"
#include "JetResolution/IJERTool.h"
#include "JetResolution/JERSmearingTool.h"

// Electrons
#include "ElectronPhotonFourMomentumCorrection/EgammaCalibrationAndSmearingTool.h"

// muons
#include "MuonMomentumCorrections/MuonCalibrationAndSmearingTool.h"

// b-jet tagging includes
#include "xAODBTaggingEfficiency/BTaggingSelectionTool.h"

// Tau
//#include "TauAnalysisTools/TauSmearingTool.h"
//#include "TauAnalysisTools/TauTruthMatchingTool.h"

// MET
#include "METUtilities/METMaker.h"
#include "METUtilities/METSystematicsTool.h"

// ASG
#include "PileupReweighting/PileupReweightingTool.h"

// HZZ
#include "HZZUtils/HiggsCrossSection.h"
#include "HZZUtils/H4lBrRatio.h"
#include "HZZUtils/TheoryVariation.h"

using namespace std;

ToolInitBase::ToolInitBase(EventContainer* eventcont)
{
    m_eventCont = eventcont;

    hasInit = false;
    m_doReducedSys = false;
    m_doFullEgammaSys = false;
}

ToolInitBase::~ToolInitBase()
{
    for(auto tool: m_asgToolVec)
    {
        delete tool;
    }

}

bool ToolInitBase::initialize()
{

    bool checkVar = true;
    checkVar &= initEgammaTools();
    checkVar &= initMuonTools();
    checkVar &= initJetTools();
    checkVar &= initBtagTools();
    checkVar &= initWeightTools();
    checkVar &= initTauTools();
    checkVar &= initMETTools();


    if (!checkVar)
    {
        LOG(logERROR)<<"ToolInitBase::initialize() - something went wrong with tool intiailization";
        LOG(logERROR)<<"See the text above";
        exit(1);
    }


    hasInit = true;

    return checkVar;

}


bool ToolInitBase::initEgammaTools()
{

    if(m_eventCont->m_analType == AnalysisType::Fiducial)
    {
        LOG(logWARNING)<<"Fiducial Analysis - Will not initialize EgammaTools.";
        return true;
    }

    // Calibration tool
    CP::EgammaCalibrationAndSmearingTool* m_elRescale = new CP::EgammaCalibrationAndSmearingTool("EgammaCalibrationAndSmearingTool");
    //RETURN_CHECK("initEgammaTools", m_elRescale->setProperty("ESModel", "es2016PRE"));
    RETURN_CHECK("initEgammaTools", m_elRescale->setProperty("ESModel", "es2016data_mc15c"));
    RETURN_CHECK("initEgammaTools", m_elRescale->setProperty("ResolutionType", "SigmaEff90"));
    
    // Reduced Sys
    if(m_doReducedSys)
    {
        RETURN_CHECK("initEgammaTools", m_elRescale->setProperty("decorrelationModel", "1NP_v1"));
    }
    else
    { 
        RETURN_CHECK("initEgammaTools", m_elRescale->setProperty("decorrelationModel", "1NPCOR_PLUS_UNCOR"));
    }

    if(m_doFullEgammaSys)
    {
        RETURN_CHECK("initEgammaTools", m_elRescale->setProperty("decorrelationModel", "FULL_v1"));        
    }


    if(m_eventCont->m_AFII) RETURN_CHECK("initEgammaTools", m_elRescale->setProperty("useAFII", 1));

    if(!m_elRescale->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize EgammaCalibrationAndSmearingTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"EgammaCalibrationAndSmearingTool initialized";
    }
    addToolToVec(m_elRescale);

    return true;
}

bool ToolInitBase::initMuonTools()
{
    if(m_eventCont->m_analType == AnalysisType::Fiducial)
    {
        LOG(logWARNING)<<"Fiducial Analysis - Will not initialize MuonTools.";
        return true;
    }
    // Intialize the calibration tool
    CP::MuonCalibrationAndSmearingTool* m_muonCalSmearTool = new CP::MuonCalibrationAndSmearingTool("muonCalSmearTool");
    RETURN_CHECK("initMuonTools", m_muonCalSmearTool->setProperty("StatComb", true));
    RETURN_CHECK("initMuonTools", m_muonCalSmearTool->setProperty("SagittaCorr", true));

    // For debugging
    //m_muonCalSmearTool->msg().setLevel( MSG::DEBUG);

    if(!m_muonCalSmearTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize MuonCalibrationAndSmearingTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"MuonCalibrationAndSmearingTool initialized";
    }
    addToolToVec(m_muonCalSmearTool);

    return true;
}

bool ToolInitBase::initJetTools()
{
    // CP tool
    TString jetAlgo = "AntiKt4EMTopo";
    TString config = "JES_data2016_data2015_Recommendation_Dec2016.config";
    TString calibSeq = "JetArea_Residual_Origin_EtaJES_GSC";

    if(m_eventCont->m_AFII) config = "JES_MC15Prerecommendation_AFII_June2015.config";
    if(m_eventCont->m_AFII) calibSeq = "JetArea_Residual_Origin_EtaJES_GSC";
    if(!m_eventCont->isMC) calibSeq = "JetArea_Residual_Origin_EtaJES_GSC_Insitu";

    
    JetCalibrationTool* m_jetCalibTool = new JetCalibrationTool("JetCalibTool");
    RETURN_CHECK("initJetTools", m_jetCalibTool->setProperty("JetCollection",jetAlgo.Data()));
    RETURN_CHECK("initJetTools", m_jetCalibTool->setProperty("ConfigFile", config.Data()));
    RETURN_CHECK("initJetTools", m_jetCalibTool->setProperty("CalibSequence",calibSeq.Data()));
    RETURN_CHECK("initJetTools", m_jetCalibTool->setProperty("IsData",!m_eventCont->isMC));

    if(!m_jetCalibTool->initializeTool("JetCalibTool").isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize ApplyJetCalibration";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"ApplyJetCalibration initialized";
    }

    JetUncertaintiesTool* m_jes = new JetUncertaintiesTool("JESTool");
    RETURN_CHECK("initJetTools", m_jes->setProperty("JetDefinition","AntiKt4EMTopo"));
    RETURN_CHECK("initJetTools", m_jes->setProperty("MCType","MC15"));

    // Reduced Sys
    if(m_doReducedSys)
    {
        RETURN_CHECK("initJetTools", m_jes->setProperty("ConfigFile","JES_2016/Moriond2017/JES2016_SR_Scenario1.config"));
    }
    else
    { 
        RETURN_CHECK("initJetTools", m_jes->setProperty("ConfigFile","JES_2016/Moriond2017/JES2016_21NP.config"));
    }


    if(!m_jes->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize JetUncertaintiesTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"ApplyJetCalibration initialized";
    }
    addToolToVec(m_jetCalibTool);
    addToolToVec(m_jes);

    JERTool* m_jerTool = new JERTool("JERTool");
    JERSmearingTool* m_smearTool = new JERSmearingTool("JERSmearingTool");

    // Configure the JERTool.
    //jerTool.msg().setLevel(MSG::DEBUG);
    RETURN_CHECK("initJetTools", m_jerTool->setProperty("PlotFileName", "JetResolution/Prerec2015_xCalib_2012JER_ReducedTo9NP_Plots_v2.root") );
    RETURN_CHECK("initJetTools", m_jerTool->setProperty("CollectionName", "AntiKt4EMTopoJets") );

    // Configure the JERSmearingTool
    ToolHandle<IJERTool> jerHandle(m_jerTool->name());
    RETURN_CHECK("initJetTools", m_smearTool->setProperty("JERTool", jerHandle) );
    //RETURN_CHECK("initJetTools", m_smearTool->setProperty("ApplyNominalSmearing", false) );
    RETURN_CHECK("initJetTools", m_smearTool->setProperty("isMC", m_eventCont->isMC) );
    RETURN_CHECK("initJetTools", m_smearTool->setProperty("SystematicMode", "Simple") );

    // Initialize the tools
    RETURN_CHECK("initJetTools", m_jerTool->initialize() );
    RETURN_CHECK("initJetTools", m_smearTool->initialize() );

    addToolToVec(m_jerTool);
    addToolToVec(m_smearTool);

    // jvt stuff
    JetVertexTaggerTool* m_pjvtag = new JetVertexTaggerTool("jvtag");
    //m_pjvtag->msg().setLevel( MSG::DEBUG);
    RETURN_CHECK("initJetTools", m_pjvtag->setProperty("JVTFileName","JetMomentTools/JVTlikelihood_20140805.root"));
    RETURN_CHECK("initJetTools", m_pjvtag->initialize() );
    
    addToolToVec(m_pjvtag);

    // fJVT
    JetForwardJvtTool* fJVT  = new JetForwardJvtTool("fJVTTool");
    //RETURN_CHECK("initJetTools", fJVT->setProperty("CentralMaxPt", 60e3) );
    //fJVT->msg().setLevel( MSG::VERBOSE);
    
    RETURN_CHECK("initJetTools", fJVT->initialize() );
    addToolToVec(fJVT);


    return true;
}

bool ToolInitBase::initBtagTools()
{ 

    // 60% WP 
    // Initialize b-jet tagging selection tool
    BTaggingSelectionTool* m_btagSelTool = new BTaggingSelectionTool("BTagSelTool_60");

    // Configure BTaggingSelectionTool properties
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("TaggerName", "MV2c10"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("OperatingPoint", "FixedCutBEff_60"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("JetAuthor", "AntiKt4EMTopoJets"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2016-20_7-13TeV-MC15-CDI-2017-01-31_v1.root"));
    //RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("OutputLevel", MSG::VERBOSE));

    if (!m_btagSelTool->initialize().isSuccess()) {
        LOG(logERROR)<<"Cannot intialize BTaggingSelectionTool_60";
        exit(1);
    }
    else {
        LOG(logINFO)<<"BTaggingSelectionTool_60 initialized";
    }
    addToolToVec(m_btagSelTool);


    // 70% WP 
    // Initialize b-jet tagging selection tool
    m_btagSelTool = new BTaggingSelectionTool("BTagSelTool_70");

    // Configure BTaggingSelectionTool properties
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("TaggerName", "MV2c10"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("OperatingPoint", "FixedCutBEff_70"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("JetAuthor", "AntiKt4EMTopoJets"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2016-20_7-13TeV-MC15-CDI-2017-01-31_v1.root"));
    //RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("OutputLevel", MSG::VERBOSE));

    if (!m_btagSelTool->initialize().isSuccess()) {
        LOG(logERROR)<<"Cannot intialize BTaggingSelectionTool_70";
        exit(1);
    }
    else {
        LOG(logINFO)<<"BTaggingSelectionTool_70 initialized";
    }
    addToolToVec(m_btagSelTool);

    // 77% WP 
    m_btagSelTool = new BTaggingSelectionTool("BTagSelTool_77");

    // Configure BTaggingSelectionTool properties
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("TaggerName", "MV2c10"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("OperatingPoint", "FixedCutBEff_77"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("JetAuthor", "AntiKt4EMTopoJets"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2016-20_7-13TeV-MC15-CDI-2017-01-31_v1.root"));
    //RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("OutputLevel", MSG::VERBOSE));

    if (!m_btagSelTool->initialize().isSuccess()) {
        LOG(logERROR)<<"Cannot intialize BTaggingSelectionTool_77";
        exit(1);
    }
    else {
        LOG(logINFO)<<"BTaggingSelectionTool_77 initialized";
    }
    addToolToVec(m_btagSelTool);


    // 85% WP
    m_btagSelTool = new BTaggingSelectionTool("BTagSelTool_85");

    // Configure BTaggingSelectionTool properties
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("TaggerName", "MV2c10"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("OperatingPoint", "FixedCutBEff_85"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("JetAuthor", "AntiKt4EMTopoJets"));
    RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("FlvTagCutDefinitionsFileName", "xAODBTaggingEfficiency/13TeV/2016-20_7-13TeV-MC15-CDI-2017-01-31_v1.root"));
    //RETURN_CHECK("initBtagTools", m_btagSelTool->setProperty("OutputLevel", MSG::VERBOSE));

    if (!m_btagSelTool->initialize().isSuccess()) {
        LOG(logERROR)<<"Cannot intialize BTaggingSelectionTool_85";
        exit(1);
    }
    else {
        LOG(logINFO)<<"BTaggingSelectionTool_85 initialized";
    }
    addToolToVec(m_btagSelTool);

    return true;

}


bool ToolInitBase::initWeightTools()
{
    // Initializing the pileUp tool
    CP::PileupReweightingTool* m_pileupTool = new CP::PileupReweightingTool("PileupTool");    
    std::vector<std::string> prwFiles;
    // TO REMOVE: 

    //if(m_eventCont->eventInfo->runNumber() == 284500)   prwFiles.push_back("HZZUtils/Pileup/mc15/mc15c.prw.root"); // mc15c
    //else if(m_eventCont->eventInfo->runNumber() == 222526)   prwFiles.push_back("HZZUtils/Pileup/mc15/mc15b.prw.root"); // mc15b
    //else if(m_eventCont->fileName.Contains("r6264")) prwFiles.push_back("HZZUtils/Pileup/mc15/mc15a.prw.root"); // 50ns mc15a
    //else prwFiles.push_back("HZZUtils/Pileup/mc15/mc15a.341488.25ns.prw.root"); // mc15a


    prwFiles.push_back("dev/PileupReweighting/mc15c_v2_defaults.NotRecommended.prw.root");
    std::vector<std::string> lumicalcFiles;

    // Final 2015
    lumicalcFiles.push_back("GoodRunsLists/data15_13TeV/20160720/physics_25ns_20.7.lumicalc.OflLumi-13TeV-005.root");

    // 2016
    lumicalcFiles.push_back("GoodRunsLists/data16_13TeV/20170215/physics_25ns_20.7.lumicalc.OflLumi-13TeV-008.root");
    
    RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("ConfigFiles",prwFiles));
    RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("LumiCalcFiles",lumicalcFiles));
    // To improve pile overlap
    RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("DataScaleFactor", 1.0/1.09));

    // Systematics
    RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("DataScaleFactorUP", 1/1.0));
    RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("DataScaleFactorDOWN", 1.0/1.18 ));


/*    

    LOG(logINFO)<<"pileUp tool runNumber:"<<m_eventCont->eventInfo->runNumber(); 

    // MC15C
    if(m_eventCont->eventInfo->runNumber() == 284500)
    {
        //RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("DefaultChannel", 343472 ));

        // overwrite it for ttbar sample
        if(m_eventCont->isMC)
        {
            if(m_eventCont->eventInfo->mcChannelNumber() == 410000)
            {
                //RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("DefaultChannel", 410000 ));
            }
        }
    }


    // OutDated
    // but here for backwards incompatibility

    // MC15a
    if(m_eventCont->eventInfo->runNumber() == 222510)
        RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("DefaultChannel", 341488 ));
    if(m_eventCont->eventInfo->runNumber() == 222525 )
        RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("DefaultChannel", 341488 ));

    // MC15B
    if(m_eventCont->eventInfo->runNumber() == 222526 )
        RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("DefaultChannel", 361373 ));

    // 50ns overide
    if(m_eventCont->eventInfo->runNumber() == 222525 && m_eventCont->fileName.Contains("r6264"))
        RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("DefaultChannel", 341889 ));
    if(m_eventCont->eventInfo->runNumber() == 222510 && m_eventCont->fileName.Contains("r6264"))
        RETURN_CHECK("initWeightTools", m_pileupTool->setProperty("DefaultChannel", 341471 ));
*/
    if(!m_pileupTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize PileupReweightingTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"PileupReweightingTool initialized";
    }

    TheoryVariation* m_varTool = new TheoryVariation("varTool");
    if(!m_varTool->initialize().isSuccess())
    {
        LOG(logERROR)<<"Cannot intialize TheoryVariationTool";
        exit(1);
    }
    else
    {
        LOG(logINFO)<<"TheoryVariationTool initialized";
    }

    // XS and BR tool
    HiggsCrossSection* m_xsTool = new HiggsCrossSection("xsTool");
    H4lBrRatio* m_brTool = new H4lBrRatio("brTool");

    addToolToVec(m_pileupTool);
    addToolToVec(m_varTool);
    addToolToVec(m_xsTool);
    addToolToVec(m_brTool);

    return true;
}

bool ToolInitBase::initTauTools()
{
    //m_tauSmeTool = new TauAnalysisTools::TauSmearingTool("TauSmearingTool");
    //
    //
    //if(!m_tauSmeTool->initialize().isSuccess())
    //{
    //    LOG(logERROR)<<"Cannot intialize TauSmearingTool";
    //    exit(1);
    //}
    //else
    //{
    //    LOG(logINFO)<<"TauSmearingTool initialized";
    //}
    //
    //m_tauTruthMatchTool = new TauAnalysisTools::TauTruthMatchingTool("TauTruthMatchingTool");
    //
    //
    //if(!m_tauTruthMatchTool->initialize().isSuccess())
    //{
    //    LOG(logERROR)<<"Cannot intialize TauTruthMatchingTool";
    //    exit(1);
    //}
    //else
    //{
    //    LOG(logINFO)<<"TauSmearingTool initialized";
    //}
    //
    //
    //addToolToVec(m_tauTruthMatchTool);

    return true;
}

bool ToolInitBase::initMETTools()
{
    met::METMaker* m_metMaker = new met::METMaker("METMaker");
    RETURN_CHECK("initMETTools", m_metMaker->initialize() );
    //RETURN_CHECK("initMETTools", m_metMaker->setProperty("JetRejectionDec","passFJVT") );
    //m_metMaker->msg().setLevel( MSG::DEBUG);

    addToolToVec(m_metMaker);

    std::string jetType = "AntiKt4EMTopoJets";

    met::METSystematicsTool* m_metSystTool = new met::METSystematicsTool("METSystematicsTool");
    RETURN_CHECK("initMETTools", m_metSystTool->setProperty("ConfigJetTrkFile","JetTrackSyst.config" ));//this is needed to do jet track systematics
    //RETURN_CHECK("initMETTools", m_metSystTool->setProperty("JetColl",jetType));//this should be the same type as
    RETURN_CHECK("initMETTools", m_metSystTool->initialize() );
    addToolToVec(m_metSystTool);


    return true;
}
void ToolInitBase::updateToolVariation()
{
    for(auto tool:m_sysToolVec)
    {
        if(tool->applySystematicVariation(m_eventCont->m_currVariation) != CP::SystematicCode::Ok ) {
            LOG(logERROR) <<"ToolInitBase::updateToolVariation() - cannot apply this variation to "<<tool->name();
            exit(1);
        }
    }
}

void ToolInitBase::addToolToVec(asg::IAsgTool* tool)
{
    m_asgToolVec.push_back(tool);
    if(dynamic_cast<CP::ISystematicsTool*>(tool))
    {
        m_sysToolVec.push_back(dynamic_cast<CP::ISystematicsTool*>(tool));
    }
}

