#include "H4lProcessMinitree/ProcessMinitree.h"

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

// ROOT includes
#include "TH1F.h"
#include "TString.h"
#include "TCollection.h"
#include "TKey.h"
#include "TObject.h"
#include "TObjArray.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TSystem.h"

// Boost includes
#include "boost/regex.hpp"
#include "boost/algorithm/string/replace.hpp"

// ASG includes
#include "xAODRootAccess/tools/ReturnCheck.h"
#include "GoodRunsLists/GoodRunsListSelectionTool.h"

// HZZ includes
#include "HZZUtils/BkgCrossSection.h"
#include "HZZUtils/HiggsCrossSection.h"
#include "HZZUtils/H4lBrRatio.h"
#include "HZZUtils/TheoryVariation.h"

// Tools
#include "MCFM_MatrixElement/MatrixElementProvider.h"


using namespace std;

typedef std::set< std::pair<unsigned long long, int> > eventCandIndexSet;

// Constructor
ProcessMinitree::ProcessMinitree()
    :
    asg::AsgMessaging("ProcessMinitree"),
    m_blindData(false),
    m_doDebug(false),
    m_doVrtCut(false),
    m_doPtReweighting(false),
    m_doXSFix(false),
    m_doBRFix(false),
    m_doMHShift(false),
    m_doNewIsoCuts(false),
    m_applyIsoCuts(false),
    m_foundFirstEvent(false),
    m_ignoreGRL(false),
    m_ignoreTrig(false),
    m_hasTrigVar(false),
    m_hasWeightCorrForNormSyst(false),
    m_isggF(false),
    m_addMELA(false)

{
    m_fileList = "";
    m_outFolder = "";
    m_xml4GRL = "";
    m_grlTool = NULL;
    m_higgsBR = NULL;

    m_inFile = 0;
    m_outFile = 0;
    m_metaDataTree = 0;
    m_countingHist = 0;

    // Fill set with variables names that are needed:
    // Wild card is .
    m_brsToRead.insert("w_.");
    m_brsToRead.insert("weight_.");
    m_brsToRead.insert("weight");
    m_brsToRead.insert("run");
    m_brsToRead.insert("event");
    m_brsToRead.insert("lbn"); // to calculate GRL
    m_brsToRead.insert("cand_index"); // needed for duplicates checks
    m_brsToRead.insert("hasExtraLep");
    m_brsToRead.insert("sumOfEventWeights");
    m_brsToRead.insert("hasExtraLepNominal");
    m_brsToRead.insert("lepton_passD0sig.");
    m_brsToRead.insert("lepton_passIsoCut.");
    // m_brsToRead.insert("weight_novtx4lCut");
    m_brsToRead.insert("pass_vtx4lCut"); 
    m_brsToRead.insert("GRLisOK");
    m_brsToRead.insert("trigDecisionOK");
    m_brsToRead.insert("truth_event_type"); // needed to compute the BR
    m_brsToRead.insert("m4l_truth_born");   // needed for Sherpa samples (can be removed when w_sherpaLep is fixed)
    if (m_doDebug) {
        ATH_MSG_DEBUG("Add branches to be used: ");
        for ( auto br : m_brsToRead ) ATH_MSG_DEBUG(br);
    }

    // set up mini tree type names
    m_outTreeTypeNames.reserve(nMiniTreeTypes);
    m_outTreeTypeNames.push_back("singleMiniTree");
    m_outTreeTypeNames.push_back("relaxeeMiniTree");
    m_outTreeTypeNames.push_back("relaxIsoD0MiniTree");
    m_outTreeTypeNames.push_back("invIsoMiniTree");
    m_outTreeTypeNames.push_back("invD0MiniTree");
    m_outTreeTypeNames.push_back("Z2SSMiniTree");
    m_outTreeTypeNames.push_back("emuZ2mumuMiniTree");
    m_outTreeTypeNames.push_back("ZeMiniTree");
    m_outTreeTypeNames.push_back("ZmuMiniTree");

}


void ProcessMinitree::setAddMELA()
{
    m_addMELA = true;
    m_brsToRead.insert("lepton_pt");
    m_brsToRead.insert("lepton_eta");
    m_brsToRead.insert("lepton_phi");
    m_brsToRead.insert("lepton_m");
    m_brsToRead.insert("event_type");
    m_brsToRead.insert("lepton_pt_fidDres_truth");
    m_brsToRead.insert("lepton_eta_fidDres_truth");
    m_brsToRead.insert("lepton_phi_fidDres_truth");
    m_brsToRead.insert("lepton_m_fidDres_truth");
    m_brsToRead.insert("event_type_fidDres_truth");
}


// Destructor
ProcessMinitree::~ProcessMinitree()
{
    if(m_grlTool) delete m_grlTool;
}

void ProcessMinitree::setDoMHShift()
{
    m_doMHShift = true;
    m_brsToRead.insert("m4l_unconstrained");
    m_brsToRead.insert("m4l_constrained");
    m_brsToRead.insert("m4l_fsr");
    m_brsToRead.insert("m4l_constrained_HM");
}

    void
ProcessMinitree::setDoPtReweighting()
{
    m_doPtReweighting = true;
    // add in the needed variables to read
    m_brsToRead.insert("jet_pt_truth");
    m_brsToRead.insert("jet_eta_truth");
    m_brsToRead.insert("n_jets_truth_20");
    m_brsToRead.insert("n_jets_truth_25");
    // m_brsToRead.insert("truthCat_type"); // old version
    m_brsToRead.insert("HTXS_Stage0_Category"); // new version
    m_brsToRead.insert("pt4l_truth_born");
    ATH_MSG_DEBUG("setDoPtReweighting - added extra branches to be used");
}    

void ProcessMinitree::setDoIsoCuts(bool doNewIsoCuts)
{
    m_doNewIsoCuts = doNewIsoCuts;
    m_applyIsoCuts = true;
    m_brsToRead.insert("lepton_ptvarcone20.");
    m_brsToRead.insert("lepton_ptvarcone30.");
    m_brsToRead.insert("lepton_topoetcone20.");
    if (!m_doNewIsoCuts) {
        m_brsToRead.insert("lepton_id");
    }
    else {
        m_brsToRead.insert("lepton_pt");
    }
}


// Process
void ProcessMinitree::process()
{
    ATH_MSG_DEBUG("process - Out File name:           " << m_outFilePath);
    ATH_MSG_DEBUG("process - InFile:                  " << m_fileList);
    ATH_MSG_DEBUG("process - Out folder:              " << m_outFolder);
    ATH_MSG_DEBUG("process - do vertex cut:           " << m_doVrtCut);
    ATH_MSG_DEBUG("process - do Higgs pt reweighting: " << m_doPtReweighting);
    ATH_MSG_DEBUG("process - do X-section fix:        " << m_doXSFix);
    ATH_MSG_DEBUG("process - do BR fix:               " << m_doBRFix);
    ATH_MSG_DEBUG("process - do MH shift fix:         " << m_doMHShift);
    ATH_MSG_DEBUG("process - ignore GRL:              " << m_ignoreGRL);
    ATH_MSG_DEBUG("process - ignore Trig:             " << m_ignoreTrig);
    ATH_MSG_DEBUG("process - do blind data:           " << m_blindData);

    // Read the samples from the file
    readSampleList();

    // Process each sample
    for(size_t i = 0; i < m_sampleList.size(); i++)
    {
        processSample(m_sampleList[i]);
    }

}



// Helper functions
void ProcessMinitree::readSampleList()
{
    // Reading the file name to process
    ifstream file(m_fileList);
    if(!file.is_open()) {ATH_MSG_ERROR("readSampleList - Can't open file");exit(-1);}

    while(file.good()) {
        string line;
        getline(file, line);
        if(line == "") continue;
        TString currFileName(line);

        // For adding in commenting samples inside a file
        if(currFileName.Contains("#")) continue;

        // To not process
        if(!currFileName.Contains(".root")) continue;

        ATH_MSG_DEBUG("readSampleList - Pushing back samples: "<<currFileName);
        m_sampleList.push_back(currFileName);
    }

}

void ProcessMinitree::clearVars()
{
    if(m_inFile) delete m_inFile;
    if(m_outFile) delete m_outFile;

    m_inFile = 0;
    m_outFile = 0;

    m_metaDataTree = 0;
    m_countingHist = 0;

    m_inTreeNames.clear();
    m_outTreeNames.clear();
    m_outTreeTypes.clear();
    m_sampleName.clear();
    m_isNormSys                = false;
    m_isFidTree                = false;
    m_isDxAOD                  = false;
    m_hasWeight                = false;
    m_hasWeightJet             = false;
    m_hasWeightbTag            = false;
    m_hasWeightCorr            = false;
    m_hasSherpaJetWeight       = false;
    m_hasSherpaLepWeight       = false;
    m_hasCandIndex             = false;
    m_isData                   = false;
    m_foundFirstEvent          = false;
    m_hasWeightCorrForNormSyst = false;
    m_hasTrigVar               = false;
    m_isggF                    = false;
    m_isNoTau                  = false;

    m_xsFix  = 1;
    m_outputCount = 0;
    m_br4e = 1;
    m_br2e2mu = 1;

    m_currInSampleName = "";

    m_outFilePath = "";

    m_nSimEvent_raw = 0;
    m_nSimEvent = 0;

    clearTTreeVars();
}

void ProcessMinitree::clearTTreeVars()
{
    m_intArrayVar.clear();
    m_floatArrayVar.clear();
    m_ulongIntArrayVar.clear();
    m_intVar.clear();
    m_floatVar.clear();
    m_doubleVar.clear();
    m_normSysName.clear();
    m_intMetaDataVar.clear();
    m_stringMetaDataVar.clear();

}


// For processing each sample
void ProcessMinitree::processSample(TString sample)
{

    ATH_MSG_INFO("");
    ATH_MSG_INFO("-------------------------------");
    ATH_MSG_INFO("");
    ATH_MSG_DEBUG("processSample - " << sample);

    // clear the vars
    clearVars();

    // Copy the sample name so it is avaliable for other functions
    m_currInSampleName = sample;


    // Read the input file
    m_inFile = new TFile(sample, "read");


    // Fill the metaData information
    fillTTreeInfo();
    fillMetaData();

    // if(m_isData) {
    //     ATH_MSG_INFO("processSample -  skipping data sample: " << sample);
    //     return;
    // }

    // Setup the output file
    setupOutput();

    // Setting up the counting hist
    if (!m_isData) fillCountingVar();

    // Setup up the branching ratio tool
    H4lBrRatio* h4lBrRatio = new H4lBrRatio("H4lBrRatio");
    // RETURN_CHECK("processSample", h4lBrRatio->initialize());
    // ATH_CHECK(h4lBrRatio->initialize());
    h4lBrRatio->initialize().ignore();
    m_higgsBR = ToolHandle<IH4lBrRatio>(h4lBrRatio->name());

    TheoryVariation* varTool = new TheoryVariation("varTool");
    varTool->initialize().ignore();
    m_varTool = ToolHandle<ITheoryVariation>(varTool->name());

    if (m_addMELA) {
	HSG2_MCFM::MatrixElementProvider *mep = new HSG2_MCFM::MatrixElementProvider("MEP");
	mep->setProperty("HiggsMass",125);
	mep->setProperty("Is13TeV",true);
	if (mep->initialize().isFailure()) {
		ATH_MSG_ERROR("Failed to init the MELA tool");
	}

	m_MEprovider = mep;
    }

    double output = 0;
    double mHTrue = m_doMHShift ? 125.09 : 125.;
    ATH_MSG_DEBUG("processSample - set mHTrue to " << mHTrue);
    m_higgsBR->execute(mHTrue, ColumnBR::br_4e, output).ignore();
    m_br4e = output;
    m_higgsBR->execute(mHTrue, ColumnBR::br_2e2mu, output).ignore();
    m_br2e2mu = output;
    if (std::string::npos != m_sampleName.find("noTau") || std::string::npos != m_sampleName.find("notau")) m_isNoTau = true;

    ATH_MSG_INFO("processSample - " << sample);

    // Now create the output file
    m_outFile = new TFile(m_outFilePath, "RECREATE");

    // Loop over all the TTree and process them
    int nTree = m_inTreeNames.size();

    for(int i = 0; i < nTree; i++)
    {
        // clear the vars
        clearTTreeVars();

        ATH_MSG_DEBUG("processSample - for tree " << m_inTreeNames[i] << " out tree: " << m_outTreeNames[i]);

        // Retrieve the input file and setup it to read the vars
        m_inFile->cd();
        m_currInTree = (TTree*) m_inFile->Get(m_inTreeNames[i]);

        // get the list of variables
        getVariableTree(m_currInTree);
        // connect the vars to read
        setupReadTree(m_currInTree);
        // set flags according to variables in the tree
        checkVariables(); 

        // For Higgs pt reweighting, must check that we a Nominal input file and that it is ggF
        if (m_doPtReweighting && "tree_incl_all" == m_inTreeNames[i]) {
            // check for ggF data sets
            checkFor_ggF();
        }

        checkFor_theorySys();

        // Setup the output file
        m_outFile->cd();

        // Clone the TTree
        setBranchStatus(false); // branches to skip
        m_currOutTree = m_currInTree->CloneTree(0);
        setBranchStatus(true);
        m_currOutTree->SetNameTitle(m_outTreeNames[i], m_outTreeNames[i]);

        // set enum for tree type
        m_currOutTreeType = m_outTreeTypes[i];
        ATH_MSG_DEBUG("processSample - current output tree type: " << m_outTreeTypeNames[m_currOutTreeType]);

        // For compression
        m_currOutTree->SetAutoFlush(); 


        // Process
        processTTree();

        // Write the tree out
        m_outFile->cd();
        m_currOutTree->Write();

        // Save the outputHist
        if(m_countingHist) m_countingHist->Write();
    }


    // write the metadata tree
    if(m_metaDataTree) {
        // clone meta data tree
        m_metaDataTree = (TTree*) m_inFile->Get("MetaData");
        setupReadMetaDataTree(m_metaDataTree);
        m_outFile->cd();
        m_outMetaDataTree = m_metaDataTree->CloneTree(0);
        m_outMetaDataTree->SetNameTitle(m_metaDataTree->GetName(), m_metaDataTree->GetName());
        // m_outMetaDataTree->SetAutoFlush();
        m_metaDataTree->GetEntry(0);
        m_outMetaDataTree->Fill();
        m_outMetaDataTree->Write();
    }

    // m_inFile->cd();
    // fillMetaData();
    // m_outFile->cd();

    
    delete h4lBrRatio;
    h4lBrRatio = 0;

    // Close the file for modifications
    m_outFile->Close();

}


// Process the TTree
// requires the in/out file and in/out tree to be set
void ProcessMinitree::processTTree()
{

    ATH_MSG_DEBUG("processTTree " << m_currInTree->GetName());

    // For Higgs pt reweighting, add extra branch in output for ggF files
    if (m_doPtReweighting && m_isggF) {
        // add branch for the Higgs pt weight
        m_doubleVar["w_Higgs_pt"] = -999;
        m_currOutTree->Branch("w_Higgs_pt",  &m_doubleVar.at("w_Higgs_pt"));
    }

    // If we need to, add MELA branches to the output tree
    if (m_addMELA) {
	if (m_floatVar.find("MCFM_dxs_ZZ") == m_floatVar.end()) {
		m_floatVar["MCFM_dxs_ZZ"] = -999;
		m_currOutTree->Branch("MCFM__ZZ", &m_floatVar.at("MCFM_dxs_ZZ"));
		m_floatVar["MCFM_dxs_ggZZ"] = -999;
		m_currOutTree->Branch("MCFM_dxs_ggZZ", &m_floatVar.at("MCFM_dxs_ggZZ"));
		m_floatVar["MCFM_dxs_ggZZtot"] = -999;
		m_currOutTree->Branch("MCFM_dxs_ggZZtot", &m_floatVar.at("MCFM_dxs_ggZZtot"));
		m_floatVar["MCFM_dxs_ggZZint"] = -999;
		m_currOutTree->Branch("MCFM_dxs_ggZZint", &m_floatVar.at("MCFM_dxs_ggZZint"));
		m_floatVar["MCFM_dxs_HZZ"] = -999;
		m_currOutTree->Branch("MCFM_dxs_HZZ", &m_floatVar.at("MCFM_dxs_HZZ"));
		m_floatVar["MCFM_mean_dxs_ZZ_atM4l"] = -999;
		m_currOutTree->Branch("MCFM_mean_dxs_ZZ_atM4l", &m_floatVar.at("MCFM_mean_dxs_ZZ_atM4l"));
		m_floatVar["MCFM_mean_dxs_HZZ_atM4l"] = -999;
		m_currOutTree->Branch("MCFM_mean_dxs_HZZ_atM4l", &m_floatVar.at("MCFM_mean_dxs_HZZ_atM4l"));
		m_floatVar["MCFM_mean_dxs_ggZZtot_atM4l"] = -999;
		m_currOutTree->Branch("MCFM_mean_dxs_ggZZtot_atM4l", &m_floatVar.at("MCFM_mean_dxs_ggZZtot_atM4l"));
	}
    }

    // Looping over the events
    Int_t nEntries = m_currInTree->GetEntries();

    ATH_MSG_DEBUG("processTTree - nEntries " << nEntries);

    // For normalization systematics
    getNormSysName(m_normSysName);


    // For counting
    Double_t totalWeight = 0;
    Int_t rawCount = 0;

    eventCandIndexSet readEvents;
    int nDuplicatedEvents = 0;

    for(Int_t i = 0; i < nEntries; i++)
    {

        ATH_MSG_DEBUG("processTTree - get entry " << i);
        if(i%50000 == 0)ATH_MSG_INFO("processTTree - get entry " << i <<" done: "<<i*100.0/nEntries); 
        m_currInTree->GetEntry(i);

        // if (3280571976 == m_ulong64Var.at("event")) setDoDebug();
        
        // On first event of each sample, get the x-section fix value
        if (m_doXSFix && !m_foundFirstEvent) {
            ATH_MSG_INFO("processTTree - doing x-section fix: run " << m_intVar.at("run"));
            m_xsFix = CrossSections::bkgCrossSection(m_intVar.at("run"), CrossSections::ThirteenTeV, m_doDebug);

            ATH_MSG_INFO("processTTree - doing x-section fix: sample " << m_currInSampleName);

            // Haider - please don't delete: needed for testing Jochen's ggZZ NLO samples
            //m_xsFix = 4.87659E-03 * 1000;
            //m_xsFix = m_doubleVar.at("w_xs");
            //if(m_currInSampleName.Contains("fid.3")) m_xsFix = 5.11428E-03 *1000;
            //if(m_currInSampleName.Contains("fid.4")) m_xsFix = 5.30218E-03 *1000;
            //if(m_currInSampleName.Contains("fid.5")) m_xsFix = 9.04448E-04 *1000;
            //if(m_currInSampleName.Contains("fid.6")) m_xsFix = 5.07632E-03 *1000;
            //if(m_currInSampleName.Contains("fid.7")) m_xsFix = 4.87659E-03 *1000;
            //if(m_currInSampleName.Contains("fid.8")) m_xsFix = 8.24224E-04 *1000;
            //if(m_currInSampleName.Contains("fid.9")) m_xsFix = 4.43800E-03 *1000;
            //if(m_currInSampleName.Contains("fid.10")) m_xsFix = 4.87659E-03 *1000;
            //if(m_currInSampleName.Contains("fid.11")) m_xsFix = 4.87659E-03 *1000;
            //if(m_currInSampleName.Contains("fid.12")) m_xsFix = 4.66233E-03 *1000;
            //if(m_currInSampleName.Contains("fid.14")) m_xsFix = 5.11428E-03 *1000;
            //if(m_currInSampleName.Contains("fid.16")) m_xsFix = m_doubleVar.at("w_xs") * 1.7;
            //if(m_currInSampleName.Contains("fid.17")) m_xsFix = m_doubleVar.at("w_xs") * 1.7;
            //if(m_currInSampleName.Contains("fid.18")) m_xsFix = m_doubleVar.at("w_xs") * 1.7;
            //if(m_currInSampleName.Contains("fid.19")) m_xsFix = m_doubleVar.at("w_xs") * 1.7;

            m_foundFirstEvent = true;
            ATH_MSG_INFO("processTTree - doing x-section fix: run/fix " << m_intVar.at("run") << " " << m_xsFix);
        }

        if (m_doMHShift) {
            switch (m_intVar.at("run")) {
            case 341471: m_xsFix = 48.52; break; // ggF with tau
            case 341505: m_xsFix = 48.52; break; // ggF noTau
            case 345060: m_xsFix = 48.52; break; // ggF NNOPS
            case 341488: m_xsFix = 3.779; break; // VBF with tau
            case 341518: m_xsFix = 3.779; break; // VBF noTau
            case 344235: m_xsFix = 3.779; break; // VBF NNPDF
            case 341947: m_xsFix = 0.882; break; // ZH
            case 345038: m_xsFix = 0.882; break; // ZH NNPDF
            case 341964: m_xsFix = 1.369; break; // WH
            case 345039: m_xsFix = 0.838; break; // WpH NNPDF
            case 345040: m_xsFix = 0.531; break; // WmH NNPDF
            case 342561: m_xsFix = 0.506; break; // ttH
            case 344973: m_xsFix = 0.528; break; // bbH yb2
            case 344974: m_xsFix = -0.0412; break; // bbH ytyt
            } // end sample switch
            m_xsFix *= 1000; // XS should be in fb while LHCHXSWG provides pb.

            // shift the m4l values
            m_floatVar.at("m4l_unconstrained")  += 0.09;
            m_floatVar.at("m4l_constrained")    += 0.09;
            m_floatVar.at("m4l_fsr")            += 0.09;
            m_floatVar.at("m4l_constrained_HM") += 0.09;
        }

        // for each event, find the branching ratio
        if (m_doBRFix || m_doMHShift) {
            if (!m_isNoTau) {
                if (0 == m_intVar.at("truth_event_type") || 1 == m_intVar.at("truth_event_type") ) m_brFix = 9.    * m_br4e;     // 4e or 4mu BR
                else                                                                               m_brFix = 9./2. * m_br2e2mu;  // 2e2mu and 2mu2e BR
            } //end inclusive case
            else {
                if (0 == m_intVar.at("truth_event_type") || 1 == m_intVar.at("truth_event_type") ) m_brFix = 4. * m_br4e;     // 4e or 4mu BR
                else                                                                               m_brFix = 2. * m_br2e2mu;  // 2e2mu and 2mu2e BR
            } //end tau case           

            // Override for EFT and MCFM: put BR to 1.
            if ( (343247 <= m_intVar.at("run") && m_intVar.at("run") <= 343262)
                || (344135 <= m_intVar.at("run") && m_intVar.at("run") <= 344170)
                || (345049 <= m_intVar.at("run") && m_intVar.at("run") <= 345052)
                || (344824 <= m_intVar.at("run") && m_intVar.at("run") <= 344832) ) { // MCFM
                m_brFix = 1;
            }
            ATH_MSG_DEBUG("processTTree - doing BR fix fix: run/event/fix " << m_intVar.at("run") << "/" << m_ulong64Var.at("event") << " " << m_brFix);
        }

        if (m_applyIsoCuts && singleMiniTree != m_currOutTreeType) {

            // recalculate the isolation
            // (for the moment, variables are not available for inclusive tree)
            calcIso();
        }

	if (m_addMELA) {
		ATH_MSG_DEBUG("processTTree - doing MCFM matrix element for MELA");
		calcMELA();
	}

        // Apply any event level cut
        if(!cutEvent()) continue;

        // // Check if the event is a duplicate
        // int local_cand_index = m_hasCandIndex ? m_intVar.at("cand_index") : -1; // set cand_index to -1 if the branch is not available (0 is another possibility).
        // pair<eventCandIndexSet::iterator, bool> insertResult = readEvents.insert( make_pair(m_ulong64Var.at("event"), local_cand_index) );
        // if (!insertResult.second) {
        //     ATH_MSG_INFO("processTTree - Found duplicated event in tree " << m_currInTree->GetName()
        //                  << ": run/lbn/event/cand_index = " << m_intVar.at("run") << "/" << m_intVar.at("lbn") << "/"
        //                  << m_ulong64Var.at("event") << "/" << local_cand_index);
        //     nDuplicatedEvents++;
        // }

        // calc the weights
        calcWeight();

        // If missing weight variable, just do direct sum
        if (m_isData && !m_hasWeight) totalWeight++;
        else totalWeight += (m_doubleVar.at("weight"));
        rawCount++;

        ATH_MSG_DEBUG("processTTree - fill tree ");
        // fill the output tree
        m_currOutTree->Fill();

        // if (3280571976 == m_ulong64Var.at("event")) setDoDebug(false);
        
    }      

    if (nDuplicatedEvents) ATH_MSG_INFO("processTTree - nDuplicatedEvents = " << nDuplicatedEvents);

    ATH_MSG_INFO("processTTree - " << m_currOutTree->GetName() << " Total weight: " << totalWeight
                 << " Raw count: " << rawCount);

    readEvents.clear();

}

// Calculate the weight
// Recalculate everything locally and then compare it to the results
void ProcessMinitree::calcWeight()
{

    ATH_MSG_DEBUG("calcWeight - entering");

    // If data set everything to 1
    if(m_isData)
    {
        if (!m_hasWeight) return;

        if(m_doVrtCut)
        {
            if(singleMiniTree == m_currOutTreeType || relaxeeMiniTree == m_currOutTreeType) {
                ATH_MSG_DEBUG("calcWeight - weight/pass_vtx4lCut" << m_doubleVar.at("weight") << "/"
                        <<  m_intVar.at("pass_vtx4lCut"));
                m_doubleVar.at("weight") = m_intVar.at("pass_vtx4lCut"); 
                return;
            }
        }

        m_doubleVar.at("weight") = 1;
        if (m_hasWeightJet)  m_doubleVar.at("weight_jet") = 1;
        if (m_hasWeightbTag) m_doubleVar.at("weight_bTag") = 1;
        // m_doubleVar.at("weight_corr") = 1;
        // m_doubleVar.at("weight_lumi") = 1;

        // Handle the extra quads that are based on ME pairing 
        if (m_intVar.find("cand_index") != m_intVar.end() && (singleMiniTree == m_currOutTreeType) )
        {
            m_doubleVar.at("weight_couplings") = m_hasWeightbTag ? m_doubleVar.at("weight_bTag") : m_doubleVar.at("weight");

            // if there is an extra lep and w_couplings 
            if(m_intVar.at("cand_index") == 0 && m_intVar.at("hasExtraLepNominal") == 1)
            {
                m_doubleVar.at("weight_couplings") = 0;
            }
            else if((m_intVar.at("cand_index") == 1 && m_intVar.at("hasExtraLepNominal") == 1))
            {
                if (m_hasWeightbTag) m_doubleVar.at("weight_bTag") = 0;
                if (m_hasWeightJet)  m_doubleVar.at("weight_jet") = 0;
                m_doubleVar.at("weight") = 0;
            }
        }


        return;
    }


    //////////
    // Standard weight calc
    ////////// 

    ATH_MSG_DEBUG("calcWeight - 1");

    
    // weight_corr
    Float_t weight_corr_local= -999;
    weight_corr_local = m_doubleVar.at("w_MCw") * m_doubleVar.at("w_lepEff") * m_doubleVar.at("w_pileup") * m_doubleVar.at("w_triggerSF")*m_doubleVar.at("w_EW")*m_doubleVar.at("w_btagEff");

    ATH_MSG_DEBUG("calcWeight - 2");

    // Lumi Weight
    Double_t weight_lumi_local = 0;
    if (m_doXSFix || m_doMHShift) m_doubleVar.at("w_xs") = m_xsFix;
    if (m_doBRFix || m_doMHShift) m_doubleVar.at("w_br") = m_brFix;
    weight_lumi_local = (m_doubleVar.at("w_lumi") * m_doubleVar.at("w_xs") * m_doubleVar.at("w_br") );

    // check if the offline calculated weight_corr and weight_lumi are similar to the online ones
    if(m_hasWeightCorr && fabs(weight_corr_local - m_doubleVar.at("weight_corr")) > 0.001 && m_outputCount<100)
    {
        ATH_MSG_ERROR("calcWeight - Weight corr mismatch");
        ATH_MSG_ERROR("calcWeight - Offline: "<<weight_corr_local<<" online: "<<m_doubleVar.at("weight_corr"));
        m_outputCount++;
    }

    if(fabs(weight_lumi_local - m_doubleVar.at("weight_lumi"))/m_doubleVar.at("weight_lumi") > 0.001 && m_outputCount < 100) {
        ATH_MSG_DEBUG("calcWeight - Weight lumi mismatch");
        ATH_MSG_DEBUG("calcWeight - Offline: "<<weight_lumi_local<<" online: "<<m_doubleVar.at("weight_lumi"));
        m_outputCount++;
    }
    if(m_outputCount == 100)
    {
        ATH_MSG_INFO("calcWeight - Maximum error output count reached... stopping the ERROR messages");
    }

    // No issue, there by we can continue

    // Nominal weights first
    // no change to weight_corr
    m_doubleVar.at("weight_lumi") = weight_lumi_local/m_nSimEvent_raw;
    m_doubleVar.at("weight_corr") = weight_corr_local;

    float w_sherpaJet = m_hasSherpaJetWeight ? m_doubleVar.at("w_sherpaJet") : 1;
    float w_sherpaLep = m_hasSherpaLepWeight ? m_doubleVar.at("w_sherpaLep") : 1;

    // // Correct sherpa lep weights
    // float w_sherpaLep = 1;
    // if (m_hasSherpaLepWeight) {
    //         //      mass bins:                  < 80    80-100 100-200  200-300 300-400 400-500  > 500
    //         static float sherpa4eWeight[7]  = { 0.8181, 0.9402, 0.9579, 0.9580, 0.9607, 0.9651, 0.9699 };
    //         static float sherpa4muWeight[7] = { 1.2845, 1.0677, 1.0461, 1.0459, 1.0421, 1.0373, 1.0313 };
    //         float mh = m_floatVar.at("m4l_truth_born");
    //         int im = -1;
    //         if      (mh < 80)  im = 0;
    //         else if (mh < 100) im = 1;
    //         else if (mh < 200) im = 2;
    //         else if (mh < 300) im = 3;
    //         else if (mh < 400) im = 4;
    //         else if (mh < 500) im = 5;
    //         else im = 6;
    //         int tet = m_intVar.at("truth_event_type");
    //         if      (QuadType::_4e      == tet) w_sherpaLep = sherpa4eWeight[im];
    //         else if (QuadType::_4mu     == tet) w_sherpaLep = sherpa4muWeight[im];
    //         else if (QuadType::_2e2tau  == tet) w_sherpaLep = sherpa4eWeight[im];
    //         else if (QuadType::_2tau2e  == tet) w_sherpaLep = sherpa4eWeight[im];
    //         else if (QuadType::_2mu2tau == tet) w_sherpaLep = sherpa4muWeight[im];
    //         else if (QuadType::_2tau2mu == tet) w_sherpaLep = sherpa4muWeight[im];
    //         m_doubleVar.at("w_sherpaLep") = w_sherpaLep;
    //         ATH_MSG_DEBUG("calcWeight: w_sherpaLep " << w_sherpaLep << " (truth_event_type:" << tet << "/" << mh << "/" << im << ")");
    // }
    
    // New Sytle
    float weight_nominal_final= m_doubleVar.at("weight_corr") 
        * m_doubleVar.at("weight_lumi") 
        * m_doubleVar.at("weight_sampleoverlap")
        * w_sherpaJet
        * w_sherpaLep
        * m_nSimEvent_raw/m_nSimEvent;
    
    float higgsPtReweight = 1;


    ATH_MSG_DEBUG("calcWeight - 3");


    // For Higgs pt reweighting, apply weight for events with 0 or 1 jet with pt > 25 and eta < 4.5info
    if (m_doPtReweighting && m_isggF) {

        ATH_MSG_DEBUG("calcWeight: is ggF, njets gt 25 " << m_intVar.at("n_jets_truth_25"));

        m_doubleVar.at("w_Higgs_pt") = 1;
        if (m_intVar.at("n_jets_truth_25") < 2) {
            m_doubleVar.at("w_Higgs_pt") = ggF_01jet_hpT_weight(m_floatVar.at("pt4l_truth_born"));

            ATH_MSG_DEBUG("calcWeight: pt, w_Higgs_pt " << m_floatVar.at("pt4l_truth_born") << "/"
                    << m_doubleVar.at("w_Higgs_pt"));

        }
        else {
            // check that we have more that 1 jet within eta < 4.5
            int njets = 0;

            ATH_MSG_DEBUG("calcWeight: njet gt 20 " << m_intVar.at("n_jets_truth_20"));

            int njetMax = (m_intVar.at("n_jets_truth_20")) < 5 ? m_intVar.at("n_jets_truth_20") : 4;
            for (int ijet = 0; ijet < njetMax; ++ijet) {

                ATH_MSG_DEBUG("calcWeight: jet pt,eta " << ijet << " "
                        << m_floatArrayVar.at("jet_pt_truth").array[ijet] << "/"
                        << m_floatArrayVar.at("jet_eta_truth").array[ijet]);

                if (25 < m_floatArrayVar.at("jet_pt_truth").array[ijet] &&
                        fabs(m_floatArrayVar.at("jet_eta_truth").array[ijet]) < 4.5) njets++;
            }

            ATH_MSG_DEBUG("calcWeight: njets " << njets);

            if (njets < 2) {


                int njetMax = (m_intVar.at("n_jets_truth_20")) < 5 ? m_intVar.at("n_jets_truth_20") : 4;
                for (int ijet = 0; ijet < njetMax; ++ijet) {

                    ATH_MSG_DEBUG("calcWeight: jet pt,eta " << ijet << " "
                            << m_floatArrayVar.at("jet_pt_truth").array[ijet] << "/"
                            << m_floatArrayVar.at("jet_eta_truth").array[ijet]);
                }

                m_doubleVar.at("w_Higgs_pt") = ggF_01jet_hpT_weight(m_floatVar.at("pt4l_truth_born"));

                ATH_MSG_DEBUG("calcWeight: 2nd check pt, w_Higgs_pt " << m_floatVar.at("pt4l_truth_born") << "/"
                        << m_doubleVar.at("w_Higgs_pt"));

            }
        }

        higgsPtReweight =  m_doubleVar.at("w_Higgs_pt");
        ATH_MSG_DEBUG("calcWeight: w_higgts_pT after  " << higgsPtReweight);
    }


    ATH_MSG_DEBUG("calcWeight - 4");

    // Save weight for weight_jet and weight_bTag for RD/Antoine's production (need to take ratio
    // for correction)
    float weight_sav = m_doubleVar.at("weight");

    // Apply the pt reweighting here (vertex cut is not yet done here - must be done for all
    // analyses)
    m_doubleVar.at("weight") = weight_nominal_final * higgsPtReweight;

    // If everything is good uptil do the other weights
    if(m_hasWeightJet) {
        // For cross-check
        float weight_jet_minitree = m_doubleVar.at("weight") * (m_doubleVar.at("weight_jet") / weight_sav);

        // weight_jet_minitree *= w_sherpaJet;
        // weight_jet_minitree *= higgsPtReweight;
        // weight_jet_minitree *= m_doubleVar.at("weight_sampleoverlap");
        // weight_jet_minitree /= m_nSimEvent;

        // new computed weight 
        m_doubleVar.at("weight_jet") = m_doubleVar.at("weight") * m_doubleVar.at("w_jetJvt_SF");

        if(fabs(weight_jet_minitree - m_doubleVar.at("weight_jet")) > 0.001 && m_outputCount<100)
        {
            ATH_MSG_ERROR("calcWeight - Weight jet mismatch");

            ATH_MSG_ERROR("calcWeight - Weight jet mismatch" << w_sherpaJet << "/" << higgsPtReweight);
            
            ATH_MSG_ERROR("calcWeight - Offline: "<<weight_jet_minitree<<" online: "<<m_doubleVar.at("weight_jet"));
            m_outputCount++;
        }
    }

    ATH_MSG_DEBUG("calcWeight - 5");

    if(m_hasWeightbTag) {
        // For cross-check
        float weight_bTag_minitree = m_doubleVar.at("weight") * (m_doubleVar.at("weight_bTag") / weight_sav);

        // weight_bTag_minitree *= w_sherpaJet;
        // weight_bTag_minitree *= higgsPtReweight;
        // weight_bTag_minitree *= m_doubleVar.at("weight_sampleoverlap");
        // weight_bTag_minitree /= m_nSimEvent;

        // new computed weight 
        m_doubleVar.at("weight_bTag") = m_doubleVar.at("weight") * m_doubleVar.at("w_jetJvt_SF") * m_doubleVar.at("w_btagEff");

        if(fabs(weight_bTag_minitree - m_doubleVar.at("weight_bTag")) > 0.001 && m_outputCount<100)
        {
            ATH_MSG_ERROR("calcWeight - Weight btag mismatch");
            ATH_MSG_ERROR("calcWeight - Offline: "<<weight_bTag_minitree<<" online: "<<m_doubleVar.at("weight_bTag"));
            m_outputCount++;
        }
    }
    ATH_MSG_DEBUG("calcWeight - 5.5");


    // Handle the extra quads that are based on ME pairing 
    if (m_doubleVar.find("w_couplings") != m_doubleVar.end())
    {
        if(m_hasWeightbTag) m_doubleVar.at("weight_couplings") = m_doubleVar.at("weight_bTag");
        else if(m_hasWeightJet) m_doubleVar.at("weight_couplings") = m_doubleVar.at("weight_jet");
        else m_doubleVar.at("weight_couplings") = m_doubleVar.at("weight");

        // if there is an extra lep and w_couplings 
        if(m_doubleVar.at("w_couplings") == 1 && m_intVar.at("hasExtraLepNominal") == 1)
        {
            m_doubleVar.at("weight_couplings") = 0;
        }
        else if((m_doubleVar.at("w_couplings") == 0 && m_intVar.at("hasExtraLepNominal") == 1))
        {
            if(m_hasWeightbTag) m_doubleVar.at("weight_bTag") = 0;
            if(m_hasWeightJet) m_doubleVar.at("weight_jet") = 0;
            m_doubleVar.at("weight") = 0;
        }

    }

    ATH_MSG_DEBUG("calcWeight - 6");




    //////////
    // Norm Systematic 
    ////////// 

    // Now the systematic variations
    // This is always nominal selection, so we will apply the vertex cut
    if(m_isNormSys)
    {

        ATH_MSG_DEBUG("calcWeight - hasWeightCorrForNormSyst " << m_hasWeightCorrForNormSyst);

        for(size_t i = 0; i < m_normSysName.size(); i++) 
        {

            string weightName = ("weight"+m_normSysName[i]).Data();

            ATH_MSG_DEBUG("calcWeight - weightName " << weightName);

            if (m_hasWeightCorrForNormSyst) {
                // Haider's norm systs
                string weightCorrName = ("weight_corr"+m_normSysName[i]).Data();
                string weightLumiName = "weight_lumi";

                // New Sytle
                m_floatVar.at(weightName) = m_floatVar.at(weightCorrName) 
                    * m_floatVar.at(weightLumiName) 
                    * m_doubleVar.at("weight_sampleoverlap")
                    * w_sherpaJet
                    * m_nSimEvent_raw/m_nSimEvent;
            }
            else {
                // RD's norm systs
                m_floatVar.at(weightName) /= m_nSimEvent;
            }
        }
    }


    ATH_MSG_DEBUG("calcWeight - 7");

    //////////
    // Vertex Cut
    ////////// 

    // If the CR is not bkg or 3l+x, apply the vertex cut here
    // Plus copy over the other weight for backup
    if(m_doVrtCut)
    {
        if(singleMiniTree == m_currOutTreeType || relaxeeMiniTree == m_currOutTreeType) {
            m_doubleVar.at("weight") *= m_intVar.at("pass_vtx4lCut"); 
        }

        if(m_isNormSys) {
            for(size_t i = 0; i < m_normSysName.size(); i++) {
                string weightName = ("weight"+m_normSysName[i]).Data();
                m_floatVar.at(weightName) *= m_intVar.at("pass_vtx4lCut"); 
            }
        }
    }

    ///////////////////////////
    // Theory systematics
    ///////////////////////////
    if(m_hasTheorySys)
    {
        //get the map that relates the variation to the index in mcEventWeights
        std::map<std::string, int> weight_vars = m_varTool->execute(m_intVar.at("run"));

        for(auto varInfo: weight_vars)
        {
            std::string w_name = ("weight_var_th_"+ m_varTool->getTheorySysName(varInfo.first)).Data(); //get name of variation
            //ATH_MSG_INFO("Doing sys: "<<w_name);
            // get the sum of weights
            double sysSumWeight = m_variationHist->GetBinContent(varInfo.second + 1);

            // Scale the weight variable
            m_floatVar.at(w_name) = m_floatVar.at(w_name) * m_nSimEvent / sysSumWeight;

        }
    }



    ATH_MSG_DEBUG("calcWeight - leaving");

    
}

bool ProcessMinitree::cutEvent() // Apply any event level cuts
{

    ATH_MSG_DEBUG("cutEvent ");

    ATH_MSG_DEBUG("cutEvent - isData, ignoreGRL " << m_isData << "/" << m_ignoreGRL);

    if(m_isData)
    {
        if (!m_ignoreGRL) {
            // First apply the GRL cut
            bool passGRL = (bool) (m_intVar.at("GRLisOK") >= 1 ? 1:0);
            // ATH_MSG_DEBUG("cutEvent - GRL: " << m_intVar.at("GRLisOK") << " run/lbn " << m_intVar.at("run") << " " << m_intVar.at("lbn") );
            if(m_grlTool) {
                passGRL = m_grlTool->passRunLB(m_intVar.at("run"), m_intVar.at("lbn"));
                if (!passGRL) {
                    // If run number is NOT in GRL, set GRLisOK to -999
                    m_intVar.at("GRLisOK") = 0;
                    if (!m_grlTool->getGRLCollection().HasRun(m_intVar.at("run"))) m_intVar.at("GRLisOK") = -999;
                }
                else m_intVar.at("GRLisOK") = 1;
            } 
            if (!passGRL){ 
                if(m_doDebug){
                    ATH_MSG_DEBUG("cutEvent - failed GRL: " << m_intVar.at("run") << " " << m_intVar.at("lbn") );
                }
                return false;
            }
        }

        ATH_MSG_DEBUG("cutEvent - ignoreTrig, hasTrigVar " << m_ignoreTrig << "/" << m_hasTrigVar);

        // Apply trgger decision
        if (!m_ignoreTrig && m_hasTrigVar) {
            ATH_MSG_DEBUG("cutEvent - testing trigger decision: "<< m_intVar.at("trigDecisionOK"));
            if (1 != m_intVar.at("trigDecisionOK")) {
                ATH_MSG_DEBUG("cutEvent - failed Trigger decision: "<< m_intVar.at("trigDecisionOK")
                              << " run/lbn " <<  m_intVar.at("run") << "/"
                              // << " event/run/lbn " <<  m_ulong64Var.at("event") << "/" << m_intVar.at("run") << "/"
                              << m_intVar.at("lbn"));
                return false;
            }
            else ATH_MSG_DEBUG("cutEvent - passed trigger decision");
        }


        ATH_MSG_DEBUG("cutEvent - blindDatahasTrigVar " << m_blindData);


        if (m_blindData) {
            // Blind the data - for nominal and relaxed Iso/d0
            // Allow through < 110 GeV and > 140 GeV where m4l is fixed to 200 GeV max
            //cout<<treeName<<endl;
            if (singleMiniTree == m_currOutTreeType || relaxIsoD0MiniTree == m_currOutTreeType) {
                if(m_floatVar.at("m4l_constrained") > 110 && m_floatVar.at("m4l_constrained") < 140) return false;
                // must flatten all m4l variables
                for ( auto m4l : m_m4lVars ) {
                    if(m_floatVar.at(m4l) > 200) {
                        m_floatVar.at(m4l) = 200;
                    }
                }
            }
        }
    }

    // If samples processed without isolation cuts, then apply them now
    // (for the moment, the singleMiniTree already has the isolation/d0 applied)
    if (m_applyIsoCuts && singleMiniTree != m_currOutTreeType) {
        // We always require leptons 0,1 to pass iso
        if(m_intArrayVar.at("lepton_passIsoCut").array[0] == 0 ||
           m_intArrayVar.at("lepton_passIsoCut").array[1] == 0 ||
           m_intArrayVar.at("lepton_passD0sig").array[0]  == 0 ||
           m_intArrayVar.at("lepton_passD0sig").array[1]  == 0) {
            ATH_MSG_DEBUG("cutEvent - lep 0,1 fails iso cuts ");
            return false;
        }
        if (relaxeeMiniTree == m_currOutTreeType) {
            // For relaxee - just apply to the third lepton
            if(m_intArrayVar.at("lepton_passIsoCut").array[2] == 0 ||
               m_intArrayVar.at("lepton_passD0sig").array[2]  == 0) {
                ATH_MSG_DEBUG("cutEvent - lep 2 fails iso cuts ");
                return false;
            }
        }
        // else if (singleMiniTree    == m_currOutTreeType) { 
        //     // Require leptons 2,3 to pass iso
        //     if(m_intArrayVar.at("lepton_passIsoCut").array[2] == 0 ||
        //        m_intArrayVar.at("lepton_passIsoCut").array[3] == 0 ||
        //        m_intArrayVar.at("lepton_passD0sig").array[2]  == 0 ||
        //        m_intArrayVar.at("lepton_passD0sig").array[3]  == 0) {
        //         ATH_MSG_DEBUG("cutEvent - lep 2,3 fails iso cuts ");
        //         return false;
        //     }
        // }
    }

    // Apply cuts for other CR
    if (invD0MiniTree == m_currOutTreeType) {
        return cutInvD0(); 
    }


    if (invIsoMiniTree == m_currOutTreeType) {
        return cutInvIso();
    }

    ATH_MSG_DEBUG("cutEvent - returning true");

    // Other wise, just return true
    return true;
}

bool ProcessMinitree::cutInvIso()
{
    ATH_MSG_DEBUG("cutInvIso ");

    // d0Sig and isolation on leading dilepton
    if(m_intArrayVar.at("lepton_passD0sig").array[0] == 0 || m_intArrayVar.at("lepton_passD0sig").array[1] == 0) return false;
    if(m_intArrayVar.at("lepton_passIsoCut").array[0] == 0 ||m_intArrayVar.at("lepton_passIsoCut").array[1] == 0) return false;
    // std d0Sig cut on subleading
    if(m_intArrayVar.at("lepton_passD0sig").array[2] == 0 || m_intArrayVar.at("lepton_passD0sig").array[3] == 0) return false;
    // iso cut inverted for at least one lepton in subleading
    if(m_intArrayVar.at("lepton_passIsoCut").array[2] == 1 && m_intArrayVar.at("lepton_passIsoCut").array[3] == 1) return false;
    return true;
}

bool ProcessMinitree::cutInvD0()
{
    ATH_MSG_DEBUG("cutInvD0 ");

    // d0Sig and isolation on leading dilepton

    if(m_intArrayVar.at("lepton_passD0sig").array[0] == 0 || m_intArrayVar.at("lepton_passD0sig").array[1] == 0) return false;
    if(m_intArrayVar.at("lepton_passIsoCut").array[0] == 0 ||m_intArrayVar.at("lepton_passIsoCut").array[1] == 0) return false;
    // d0Sig inverted for at least one lepton in subleading
    // iso not applied
    if(m_intArrayVar.at("lepton_passD0sig").array[2] == 1 && m_intArrayVar.at("lepton_passD0sig").array[3] == 1) return false;
    return true;
}

void ProcessMinitree::calcIso()
{
    // recalculate the isolation selection

    ATH_MSG_DEBUG("calcIso: entering - doNewIsoCuts " << m_doNewIsoCuts );

    for (unsigned int i = 0; i < 4; ++i) {
        bool isoIsOK = true;
        if (m_doNewIsoCuts) {
            // Apply "optimized cuts" - std cut above 25 GeV, constant below
            float ptcone     = m_floatArrayVar.at("lepton_ptvarcone20").array[i];
            float topocone20 = m_floatArrayVar.at("lepton_topoetcone20").array[i];
            isoIsOK = ptcone < 0.15 && topocone20 < 0.30; 
            // Apply "optimized cuts" - std cut above 25 GeV, constant below
            // float pt         = m_floatArrayVar.at("lepton_pt").array[i];
            // float ptcone20   = m_floatArrayVar.at("lepton_ptvarcone20").array[i];
            // float topocone20 = m_floatArrayVar.at("lepton_topoetcone20").array[i];
            // if (25 < pt) isoIsOK = (ptcone20    < 0.15 && topocone20    < 0.20);
            // else         isoIsOK = (ptcone20*pt < 3.75 && topocone20*pt < 5.0);
        }
        else {
            // Apply the standard cuts
            bool isMuon      = m_intArrayVar.at("lepton_id").array[i] < 5;
            float ptcone     = (isMuon) ? m_floatArrayVar.at("lepton_ptvarcone30").array[i] :
                m_floatArrayVar.at("lepton_ptvarcone20").array[i];
            float topocone20 = m_floatArrayVar.at("lepton_topoetcone20").array[i];
            isoIsOK = (isMuon) ? (ptcone < 0.15 && topocone20 < 0.30) : (ptcone < 0.15 && topocone20 < 0.20);
        }
        m_intArrayVar.at("lepton_passIsoCut").array[i] = isoIsOK;
    }

    ATH_MSG_DEBUG("calcIso: end ");
}


void ProcessMinitree::calcMELA(){
    TLorentzVector tlv1;
    TLorentzVector tlv2;
    TLorentzVector tlv3;
    TLorentzVector tlv4;
    int type = -99;
    int pdg1=-99;
    int pdg2=-99;
    int pdg3=-99;
    int pdg4=-99;

    if (m_intMetaDataVar["type"] == MiniTreeFileType::Fiducial){
        ATH_MSG_DEBUG("calcMELA - setting up for a fid minitree");

        tlv1.SetPtEtaPhiM(m_floatArrayVar.at("lepton_pt_fidDres_truth").array[0],m_floatArrayVar.at("lepton_eta_fidDres_truth").array[0], m_floatArrayVar.at("lepton_phi_fidDres_truth").array[0], m_floatArrayVar.at("lepton_m_fidDres_truth").array[0]) ;
        tlv2.SetPtEtaPhiM(m_floatArrayVar.at("lepton_pt_fidDres_truth").array[1],m_floatArrayVar.at("lepton_eta_fidDres_truth").array[1], m_floatArrayVar.at("lepton_phi_fidDres_truth").array[1], m_floatArrayVar.at("lepton_m_fidDres_truth").array[1]) ;
        tlv3.SetPtEtaPhiM(m_floatArrayVar.at("lepton_pt_fidDres_truth").array[2],m_floatArrayVar.at("lepton_eta_fidDres_truth").array[2], m_floatArrayVar.at("lepton_phi_fidDres_truth").array[2], m_floatArrayVar.at("lepton_m_fidDres_truth").array[2]) ;
        tlv4.SetPtEtaPhiM(m_floatArrayVar.at("lepton_pt_fidDres_truth").array[3],m_floatArrayVar.at("lepton_eta_fidDres_truth").array[3], m_floatArrayVar.at("lepton_phi_fidDres_truth").array[3], m_floatArrayVar.at("lepton_m_fidDres_truth").array[3]) ;
        type = m_intVar.at("event_type_fidDres_truth");
    }
    else {
        ATH_MSG_DEBUG("calcMELA - setting up for a reco minitree");
        tlv1.SetPtEtaPhiM(m_floatArrayVar.at("lepton_pt").array[0],m_floatArrayVar.at("lepton_eta").array[0], m_floatArrayVar.at("lepton_phi").array[0], m_floatArrayVar.at("lepton_m").array[0]) ;
        tlv2.SetPtEtaPhiM(m_floatArrayVar.at("lepton_pt").array[1],m_floatArrayVar.at("lepton_eta").array[1], m_floatArrayVar.at("lepton_phi").array[1], m_floatArrayVar.at("lepton_m").array[1]) ;
        tlv3.SetPtEtaPhiM(m_floatArrayVar.at("lepton_pt").array[2],m_floatArrayVar.at("lepton_eta").array[2], m_floatArrayVar.at("lepton_phi").array[2], m_floatArrayVar.at("lepton_m").array[2]) ;
        tlv4.SetPtEtaPhiM(m_floatArrayVar.at("lepton_pt").array[3],m_floatArrayVar.at("lepton_eta").array[3], m_floatArrayVar.at("lepton_phi").array[3], m_floatArrayVar.at("lepton_m").array[3]) ;
        type = m_intVar.at("event_type");
    }
    switch(type){
        case (0):
            pdg1 = 13;
            pdg2 = -13;
            pdg3 = 13;
            pdg4 = -13;
            break;
        case (1):
            pdg1 = 11;
            pdg2 = -11;
            pdg3 = 11;
            pdg4 = -11;
            break;
        case (2):
            pdg1 = 13;
            pdg2 = -13;
            pdg3 = 11;
            pdg4 = -11;
            break;
        case (3):
            pdg1 = 11;
            pdg2 = -11;
            pdg3 = 13;
            pdg4 = -13;
            break;
        default:
            ATH_MSG_DEBUG("Skipping an unsupported ME for event type "<<type);
    }

    if (pdg1 < -50){
        ATH_MSG_DEBUG("calcMELA - skipping an invalid event");
        m_floatVar["MCFM_dxs_ZZ"] = -99;
        m_floatVar["MCFM_dxs_ggZZ"] = -99;
        m_floatVar["MCFM_dxs_ggZZtot"] = -99;
        m_floatVar["MCFM_dxs_ggZZint"] = -99;
        m_floatVar["MCFM_dxs_HZZ"] = -99;
        m_floatVar["MCFM_mean_dxs_HZZ_atM4l"] = -99;
        m_floatVar["MCFM_mean_dxs_ggZZtot_atM4l"] = -99;
        m_floatVar["MCFM_mean_dxs_ZZ_atM4l"] = -99;
    }
    else{
        ATH_MSG_DEBUG("calcMELA - getting the ME");
        HSG2_MCFM::MatrixElementResult res = m_MEprovider->getME(tlv1, tlv2, tlv3, tlv4, pdg1, pdg2, pdg3, pdg4);
        m_floatVar["MCFM_dxs_ZZ"] = res.dxs_ZZ;
        m_floatVar["MCFM_dxs_ggZZ"] = res.dxs_ggZZ;
        m_floatVar["MCFM_dxs_ggZZtot"] = res.dxs_ggZZtot;
        m_floatVar["MCFM_dxs_ggZZint"] = res.dxs_ggZZint;
        m_floatVar["MCFM_dxs_HZZ"] = res.dxs_HZZ;
        m_floatVar["MCFM_mean_dxs_HZZ_atM4l"] = res.mean_dxs_HZZ_atM4l;
        m_floatVar["MCFM_mean_dxs_ggZZtot_atM4l"] = res.mean_dxs_ggZZtot_atM4l;
        m_floatVar["MCFM_mean_dxs_ZZ_atM4l"] = res.mean_dxs_ZZ_atM4l;
    }
}


// Which trees to process
void ProcessMinitree::fillTTreeInfo()
{
    
    if(m_inFile->Get("tree_relaxee") != NULL)
    {
        m_inTreeNames.push_back("tree_relaxee"); 
        m_outTreeNames.push_back("tree_relaxee");
        m_outTreeTypes.push_back(relaxeeMiniTree);
    }
    if(m_inFile->Get("tree_relaxIsoD0") != NULL)
    {
        m_inTreeNames.push_back("tree_relaxIsoD0"); 
        m_outTreeNames.push_back("tree_invD0");
        m_outTreeTypes.push_back(invD0MiniTree);
    }
    if(m_inFile->Get("tree_relaxIsoD0") != NULL)
    {
        m_inTreeNames.push_back("tree_relaxIsoD0"); 
        m_outTreeNames.push_back("tree_invIso");
        m_outTreeTypes.push_back(invIsoMiniTree);
    }
    if(m_inFile->Get("tree_relaxIsoD0") != NULL)
    {
        m_inTreeNames.push_back("tree_relaxIsoD0");
        m_outTreeNames.push_back("tree_relaxIsoD0");
        m_outTreeTypes.push_back(relaxIsoD0MiniTree);
    }
    if(m_inFile->Get("tree_ss") != NULL)
    {
        m_inTreeNames.push_back("tree_ss"); 
        m_outTreeNames.push_back("tree_ss");
        m_outTreeTypes.push_back(Z2SSMiniTree);
    }
    if(m_inFile->Get("tree_emu") != NULL)
    {
        m_inTreeNames.push_back("tree_emu"); 
        m_outTreeNames.push_back("tree_emu");
        m_outTreeTypes.push_back(emuZ2mumuMiniTree);
    }
    if(m_inFile->Get("tree_ZplusMu") != NULL)
    {
        m_inTreeNames.push_back("tree_ZplusMu"); 
        m_outTreeNames.push_back("tree_ZplusMu");
        m_outTreeTypes.push_back(ZmuMiniTree);
    }
    if(m_inFile->Get("tree_ZplusEl") != NULL)
    {
        m_inTreeNames.push_back("tree_ZplusEl"); 
        m_outTreeNames.push_back("tree_ZplusEl");
        m_outTreeTypes.push_back(ZeMiniTree);
    }
    if(m_inFile->Get("tree_incl_all") != NULL)
    {
        m_inTreeNames.push_back("tree_incl_all"); 
        m_outTreeNames.push_back("tree_incl_all");
        m_outTreeTypes.push_back(singleMiniTree);
    }
}

// Fill meta data infor
// Will help will other processing
void ProcessMinitree::fillMetaData()
{

    // Check if the MetaData tree is avaliable
    if(m_inFile->GetListOfKeys()->Contains("MetaData") ) 
    {
        ATH_MSG_INFO("fillMetaData - using MetaData tree");

        // retrieve the metaData file
        m_metaDataTree = (TTree*) m_inFile->Get("MetaData");

        setupReadMetaDataTree(m_metaDataTree);

        m_metaDataTree->GetEntry(0);
        ATH_MSG_INFO("fillMetaData - get event");


        // read the info
        TString sampleName    = *m_stringMetaDataVar["sampleName"];

        // Cleaning the output a bit
        // Splitting the file path
        TObjArray *parts = sampleName.Tokenize(".");
        vector<TString> partName;
        if(parts->GetEntriesFast()) {
            TIter iString(parts);
            TObjString* os=0;
            while ((os=(TObjString*)iString())) {
                partName.push_back(os->GetString());
            }
        }

        if(partName.size() > 3)
        {
            sampleName = partName[0];
            for (size_t i = 1; i < partName.size() - 3; i++)
            {
                sampleName += ("." + partName[i]);
            }
        }

        m_sampleName = sampleName.Data();


        m_currVariation = *m_stringMetaDataVar["systematicVariation"];

        // Get the systematic infomation
        if(m_intMetaDataVar["type"] == MiniTreeFileType::NormSystematic) m_isNormSys = true;

        if(m_intMetaDataVar["type"] == MiniTreeFileType::Fiducial)      m_isFidTree = true;
        

        // DAOD
        TString DAODStr = *m_stringMetaDataVar["dataType"];
        if(DAODStr.Contains("DAOD")) m_isDxAOD = true;

        // is MC
        if(!m_intMetaDataVar["isMC"]) m_isData = true;
        else m_isData = false;

        ATH_MSG_DEBUG("fillMetaData - isMC:         " << m_intMetaDataVar["isMC"]);
        ATH_MSG_DEBUG("fillMetaData - type:         " << m_intMetaDataVar["type"]);
        

        ATH_MSG_INFO("fillMetaData - MetaDataTree sampleName:         " << m_sampleName);
        ATH_MSG_INFO("fillMetaData - MetaDataTree currVariation:      " << m_currVariation);
        ATH_MSG_INFO("fillMetaData - MetaDataTree isNormSys:          " << m_isNormSys);
        ATH_MSG_INFO("fillMetaData - MetaDataTree isFidTree:          " << m_isFidTree);
        ATH_MSG_INFO("fillMetaData - MetaDataTree isDxAOD:            " << m_isDxAOD);
        ATH_MSG_INFO("fillMetaData - MetaDataTree isData:             " << m_isData);

        return;
    }
    else {

        getSampleName(m_inFile, m_sampleName);
        getVariationName(m_inFile, m_currVariation);
        m_isNormSys     = isNormFile();
        m_isDxAOD       = isDxAOD(m_inFile);
        if(m_currInSampleName.Contains("data")) m_isData = true;

        ATH_MSG_INFO("fillMetaData - sampleName:         " << m_sampleName);
        ATH_MSG_INFO("fillMetaData - currVariation:      " << m_currVariation);
        ATH_MSG_INFO("fillMetaData - isNormSys:          " << m_isNormSys);
        ATH_MSG_INFO("fillMetaData - isDxAOD:            " << m_isDxAOD);
        ATH_MSG_INFO("fillMetaData - isData:             " << m_isData);
    }

}

// Gets the base name of the sample
void ProcessMinitree::getSampleName(TFile *file, std::string& sampleName)
{
    TString dirName = "DirNotSpecified";

    TIter nextkey(file->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)nextkey())) {
        TObject *Obj = key->ReadObj();
        if(Obj->IsA()->InheritsFrom("TDirectory"))
        {
            TString temp = Obj->GetName(); 
            if (temp.Contains("TeV"))
            {
                ATH_MSG_INFO("getSampleName - Name: " << Obj->GetName());
                dirName = Obj->GetName();
            }
        }
    }

    // Cleaning the output a bit
    // Splitting the file path
    TObjArray *parts = dirName.Tokenize(".");
    vector<TString> partName;
    if(parts->GetEntriesFast()) {
        TIter iString(parts);
        TObjString* os=0;
        while ((os=(TObjString*)iString())) {
            partName.push_back(os->GetString());
        }
    }

    if(partName.size() > 3)
    {
        dirName = partName[0];
        for (size_t i = 1; i < partName.size() - 3; i++)
        {
            dirName = dirName + "." + partName[i];
        }
    }

    sampleName = dirName;

}

// Gets the sytematic variation name
    void
ProcessMinitree::getVariationName(TFile* file, TString& variationName)
{

    ATH_MSG_DEBUG("getVariationName");


    TString varName = "";
    TString outName = "";

    TIter nextkey(file->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)nextkey())) {
        TObject *Obj = key->ReadObj();
        if(Obj->IsA()->InheritsFrom("TDirectory"))
        {
            TString temp = Obj->GetName();
            if (temp.Contains("Variation"))
            {
                ATH_MSG_DEBUG(Obj->GetName());
                varName = Obj->GetName();
            }
        }
    }

    // Cleaning the output a bit
    // Splitting the file path
    TObjArray *parts = varName.Tokenize("-");
    vector<TString> partName;
    if(parts->GetEntriesFast()) {
        TIter iString(parts);
        TObjString* os=0;
        while ((os=(TObjString*)iString())) {
            partName.push_back(os->GetString());
        }
    }

    if(partName.size() > 1)
    {
        outName = partName[1];
    }
    // If first character is a underscore, replace it
    if(outName[0] == '_')
    {
        outName.Replace(0,1,"");
    }
    variationName = outName;
}

// Gets if the sample is a normalization systematics
Bool_t ProcessMinitree::isNormFile()
{
    if(m_currInSampleName.Contains("_normSys")) return true;   
    return false;
}

// checks if the current file is a DxAOD
bool ProcessMinitree::isDxAOD(TFile *file)
{
    TString dirName = "DirNotSpecified";

    TIter nextkey(file->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)nextkey())) {
        TObject *Obj = key->ReadObj();
        if(Obj->IsA()->InheritsFrom("TDirectory"))
        {
            TString temp = Obj->GetName();
            if (temp.Contains("TeV"))
            {
                dirName = Obj->GetName();
            }
        }
    }
    return dirName.Contains("DAOD");
}

// gets the list of normalization systematics
void ProcessMinitree::getNormSysName(std::vector<TString>& normSysName)
{
    normSysName.clear();

    // If the file is a norm systematic file, find the systematic variation
    for (auto it = m_floatVar.begin(); it != m_floatVar.end(); ++it)
    {
        TString varName = it->first;     
        if(varName.Contains("weight_"))
        {
            if(varName.EqualTo("weight_lumi")) continue;
            if(varName.EqualTo("weight_corr")) continue;
            if(varName.EqualTo("weight_sampleoverlap")) continue;
            if(varName.Contains("weight_lumi_")) continue;
            if(varName.Contains("weight_var_")) continue;
            if(varName.Contains("weight_bTag")) continue;
            if(varName.Contains("weight_jet")) continue;
            if(varName.Contains("weight_coupling")) continue;
            if(varName.Contains("weight_var_th_")) continue;
            if(varName.Contains("weight_corr_")) {
                // differentiate the norm systematics coming from Haider or RD
                m_hasWeightCorrForNormSyst = true;
                continue;
            }
            if(varName.Contains("weight_no")) continue;

            //ATH_MSG_DEBUG(varName);
            TString temp = varName.Replace(0,6,"");
            normSysName.push_back(temp);

            ATH_MSG_INFO("Norm Sys var: " << temp);
        }
    }
}
// checks for variables in tree
void ProcessMinitree::checkVariables()
{
    if (m_doubleVar.find("weight")        != m_doubleVar.end()) m_hasWeight = true;
    if (m_doubleVar.find("w_sherpaJet")   != m_doubleVar.end()) m_hasSherpaJetWeight = true;
    if (m_doubleVar.find("w_sherpaLep")   != m_doubleVar.end()) m_hasSherpaLepWeight = true;
    if (m_doubleVar.find("weight_jet")    != m_doubleVar.end()) m_hasWeightJet = true;
    if (m_doubleVar.find("weight_bTag")   != m_doubleVar.end()) m_hasWeightbTag = true;
    if (m_doubleVar.find("hasWeightCorr") != m_doubleVar.end()) m_hasWeightCorr = true;
    if (m_intVar.find("cand_index")       != m_intVar.end())    m_hasCandIndex = true;
    ATH_MSG_DEBUG("checkVariables - hasWeight:          " << m_hasWeight);
    ATH_MSG_DEBUG("checkVariables - hasSherpaJetWeight: " << m_hasSherpaJetWeight);
    ATH_MSG_DEBUG("checkVariables - hasSherpaLepWeight: " << m_hasSherpaLepWeight);
    ATH_MSG_DEBUG("checkVariables - hasWeightJet:       " << m_hasWeightJet);
    ATH_MSG_DEBUG("checkVariables - hasWeightbTag:      " << m_hasWeightbTag);
    ATH_MSG_DEBUG("checkVariables - hasWeightCorr:      " << m_hasWeightCorr);
    ATH_MSG_DEBUG("checkVariables - hasCandIndex:       " << m_hasCandIndex);
}


/// Output stuff
void ProcessMinitree::setupOutput()
{
    // Start building the sample output name

    // start with the base sample name
    m_outFilePath = m_sampleName;

    std::string bkgDir;
    if(m_currInSampleName.Contains("Zplusl") || m_currInSampleName.Contains("Zpl")) {
        m_outFilePath += "_bkgCRZpl.root";
        bkgDir = "BkgCRZpl";
    }
    else if(m_inFile->Get("tree_incl_all") != NULL) m_outFilePath += ".root";
    else {
        m_outFilePath += "_bkgCR.root";
        bkgDir = "BkgCR";
    }

    // At this point we have the sample name
    // Now look at the output folder

    /// If this is a variation file
    // create a folder in which samples are saved
    // This is to make sure that the systematic variations of a single samples are in one folder
    if(m_currVariation.Length() > 0) {
        gSystem->MakeDirectory(m_outFolder + "/" + m_currVariation);
        m_outFilePath = m_outFolder + "/" + m_currVariation + "/" + m_outFilePath;
    }
    else if (m_isNormSys) {
        // Is normalization systematic, save in a corresponding systmatic folder
        gSystem->MakeDirectory(m_outFolder + "/NormSystematic");
        m_outFilePath = m_outFolder + "/NormSystematic/" + m_outFilePath;
    }
    else if (bkgDir.size()) {
        // Bkg dir
        gSystem->MakeDirectory(m_outFolder + "/" + bkgDir);
        m_outFilePath = m_outFolder + "/" + bkgDir + "/" + m_outFilePath;
    }
    else {
        // Nominal
        gSystem->MakeDirectory(m_outFolder + "/Nominal");
        m_outFilePath = m_outFolder + "/Nominal/" + m_outFilePath;
    }


    ATH_MSG_INFO("setupOutput - Out File name: " << m_outFilePath);

}


// For reading the TTree
// To get all the variables that are in each branch
void ProcessMinitree::getVariableTree(TTree *tree)
{
    TObjArray* listLf = tree->GetListOfLeaves();

    for (Int_t i = 0; i < listLf->GetEntries(); i++)
    {
        TLeaf* lf = (TLeaf*) listLf->At(i);

        TString typeName   = lf->GetTypeName();
        std::string brName = lf->GetTitle();
        TString titleName  = lf->GetTitle();

        if (matchPattern(brName)) {
            ATH_MSG_DEBUG("getVariableTree: Keeping branch "  << brName);
        }
        else {
            ATH_MSG_VERBOSE("getVariableTree: skipping branch "  << brName);
            continue;
        }

        if(typeName.Contains("Int_t") && (titleName.Contains("[4]") || titleName.Contains("[3]")))
        {
            m_intArrayVar[lf->GetName()] = {{-999, -999, -999, -999}};
        }
        else if(typeName.Contains("Float_t") && (titleName.Contains("[4]") || titleName.Contains("[3]")))
        {
            m_floatArrayVar[lf->GetName()] = {{-999, -999, -999, -999}};
        }
        else if(typeName.Contains("ULong64_t"))
        {
            m_ulong64Var[lf->GetName()] = -999;
        }
        else if(typeName.Contains("Int_t") && !typeName.Contains("UInt_t"))
        {
            m_intVar[lf->GetName()] = -999;
            if ("trigDecisionOK" == brName) m_hasTrigVar = true; // not all miniTrees have trigDecisionOK
        }
        else if(typeName.Contains("UInt_t"))
        {
            continue;
        }

        else if(typeName.Contains("Float_t"))
        {
            m_floatVar[lf->GetName()] = -999;
        }
        else if(typeName.Contains("Double_t"))
        {
            m_doubleVar[lf->GetName()] = -999;
        }
        else if(typeName.Contains("ULong64_t"))
        {
            m_ulongIntArrayVar[lf->GetName()] = (ULong64_t) -999;
        }
        else if(typeName.Contains("string"))
        {
            // Do nothing for string right now
        }
    }    
}

Bool_t ProcessMinitree::matchPattern(const string brName)
{
    // First check direct match
    if (m_brsToRead.find(brName) != m_brsToRead.end()) return true;

    // Now allow for regexp matching
    for(auto st: m_brsToRead)
    {
        string sysPat(st);

        const boost::regex ex(boost::replace_all_copy(sysPat, ".", "\\S+"));
        string::const_iterator start, end;
        start = brName.begin();
        end = brName.end();
        boost::match_results<string::const_iterator> what;
        boost::match_flag_type flags = boost::match_default;

        if(boost::regex_search(start, end, what, ex, flags)) return true;
    }

    return false;
}


// To setup the tree read
void ProcessMinitree::setupReadTree(TTree *tree)
{      
    for (auto it = m_intVar.begin(); it != m_intVar.end(); ++it)
    {
        TString varName = it->first;
        tree->SetBranchAddress(varName, &it->second);
    }
    for (auto it = m_ulong64Var.begin(); it != m_ulong64Var.end(); ++it)
    {
        TString varName = it->first;
        tree->SetBranchAddress(varName, &it->second);
    }
    for (auto it = m_floatVar.begin(); it != m_floatVar.end(); ++it)
    {
        TString varName = it->first;
        tree->SetBranchAddress(varName, &it->second);
    }
    for (auto it = m_doubleVar.begin(); it != m_doubleVar.end(); ++it)
    {
        TString varName = it->first;
        tree->SetBranchAddress(varName, &it->second);
    }

    for (auto it = m_intArrayVar.begin(); it != m_intArrayVar.end(); ++it)
    {
        TString varName = it->first;
        tree->SetBranchAddress(varName, (it->second).array);
    }
    for (auto it = m_floatArrayVar.begin(); it != m_floatArrayVar.end(); ++it)
    {
        TString varName = it->first;
        tree->SetBranchAddress(varName, (it->second).array);
    }
    for (auto it = m_ulongIntArrayVar.begin(); it != m_ulongIntArrayVar.end(); ++it)
    {
        TString varName = it->first;
        tree->SetBranchAddress(varName, &it->second);
    }
}

// To setup the tree read
void ProcessMinitree::setupReadMetaDataTree(TTree *tree)
{      
    TObjArray* listLf = tree->GetListOfLeaves();

    for (Int_t i = 0; i < listLf->GetEntries(); i++)
    {
        TLeaf* lf = (TLeaf*) listLf->At(i);

        TString typeName   = lf->GetTypeName();
        std::string brName = lf->GetTitle();
        TString titleName  = lf->GetTitle();

        if(typeName.Contains("Int_t"))
        {
            m_intMetaDataVar[lf->GetName()] = -999;
        }
        else if(typeName.Contains("string"))
        {
            m_stringMetaDataVar[lf->GetName()] = 0;
        }
    }    

    for (auto it = m_intMetaDataVar.begin(); it != m_intMetaDataVar.end(); ++it)
    {
        TString varName = it->first;
        tree->SetBranchAddress(varName, &it->second);
    }
    for (auto it = m_stringMetaDataVar.begin(); it != m_stringMetaDataVar.end(); ++it)
    {
        TString varName = it->first;
        tree->SetBranchAddress(varName, &it->second);
    }
}



void ProcessMinitree::fillCountingVar()
{
    TH1F* countHist = 0;
    if(m_currVariation.Length() > 0) 
    {
        countHist = (TH1F*) m_inFile->Get("Hist/CountingHist_"+m_currVariation);
        if (!countHist) countHist = (TH1F*) m_inFile->Get("Hist/CountingHist");
    }
    else  countHist = (TH1F*) m_inFile->Get("Hist/CountingHist");

    if (!countHist) 
    {
        ATH_MSG_ERROR("fillCountingVar - Could NOT find counting histogram! ");
        exit(1);
    }

    m_nSimEvent_raw = countHist->GetBinContent(4);
    m_nSimEvent = countHist->GetBinContent(6);

    m_countingHist = countHist;
    ATH_MSG_INFO("fillCountingVar - Raw Event: " << m_nSimEvent_raw << " weighted events: " << m_nSimEvent);
}

    void
ProcessMinitree::setBlindData(bool doBlinding)
{
    m_blindData = doBlinding;
    ATH_MSG_INFO("setBlindData - blind data: " << m_blindData);
    m_m4lVars.clear();
    if (m_blindData) {
        m_m4lVars.push_back("m4l_constrained");
        m_m4lVars.push_back("m4l_constrained_HM");
        m_m4lVars.push_back("m4l_fsr");
        m_m4lVars.push_back("m4l_unconstrained");
        m_brsToRead.insert("m4l_constrained");
        m_brsToRead.insert("m4l_constrained_HM");
        m_brsToRead.insert("m4l_fsr");
        m_brsToRead.insert("m4l_unconstrained");
    }
}

    bool 
ProcessMinitree::setXML4GRL(const TString& xml)
{
    ATH_MSG_INFO("setXML4GRL - input " << xml );

    // Allow comma-separated list
    // Splitting the file path
    std::vector<std::string> myvals;
    std::string str_in(xml);
    tokenizeString(str_in, ",", myvals);

    for ( auto xmlFile : myvals ) {
        ifstream file(xmlFile);
        if(!file.is_open()) {
            ATH_MSG_ERROR("Cannot open xml file for GRL: " << xmlFile);
            return false;
        } else {
            file.close();
        }
        ATH_MSG_INFO("setXML4GRL - reading xml file " << xmlFile );
    }

    m_grlTool = new GoodRunsListSelectionTool("H4lGRLTool");
    RETURN_CHECK( "ProcessMinitree", m_grlTool->setProperty( "GoodRunsListVec", myvals) );
    RETURN_CHECK( "ProcessMinitree", m_grlTool->setProperty("PassThrough", false) );
    if (m_doDebug) RETURN_CHECK( "ProcessMinitree", m_grlTool->setProperty("OutputLevel", MSG::DEBUG) );
    RETURN_CHECK( "ProcessMinitree", m_grlTool->initialize() );
    ATH_MSG_INFO("setXML4GRL - GRL tool initialized... " );
    return true;
}

    void
ProcessMinitree::checkFor_ggF()
{
    /// For Higgs pt reweighting, must check that we a Nominal input file and that it is ggF

    m_isggF = false;

    if (m_currInTree->GetEntries()) {
        m_currInTree->GetEntry(0);
        // int truthCatType = m_intVar.at("truthCat_type");
        // if (0 <= truthCatType && 0 == (truthCatType/1000)) m_isggF = true;
        // ATH_MSG_INFO("checkFor_ggF - truthCatType " << std::hex << truthCatType << std::dec);

        // exclude the new ggF (345060) for now.
        if (345060 == m_intVar.at("run")) return;

        int categHTXS0 = m_intVar.at("HTXS_Stage0_Category");
        if (10 <= categHTXS0 && categHTXS0 < 20) m_isggF = true;
        ATH_MSG_INFO("checkFor_ggF - categHTXS0 " << categHTXS0);
    }

    ATH_MSG_INFO("checkFor_ggF - is ggF " << m_isggF);

}

// only for ggF events with 0 or 1 jets with pT>25 GeV
// input: Higgs boson pT in GeV !
double
ProcessMinitree::ggF_01jet_hpT_weight(double hpT) const
{
    if (hpT <  20) return 1.11;
    if (hpT <  45) return 1.11 - (hpT - 20) / 25 * 0.2; // -> 0.91
    if (hpT < 135) return 0.91 - (hpT - 45) / 90 * 0.36; // -> 0.55
    return 0.55;
}

void ProcessMinitree::checkFor_theorySys()
{
    m_hasTheorySys = false;
    m_variationHist = 0;

    
    for(auto var:m_floatVar)
    {
        TString varName(var.first);
        if(varName.Contains("weight_var_th_"))
        {
            m_hasTheorySys = true;
            m_variationHist = (TH1F*) m_inFile->Get("Hist/VariationHist");
            break;
        }
    }

    ATH_MSG_INFO("checkFor_theorySys - m_hasTheorySys " << m_hasTheorySys);
}



void ProcessMinitree::setBranchStatus(bool status)
{
    ATH_MSG_DEBUG("setBranchStatus - enter ");

    if(m_isNormSys && m_hasWeightCorr) m_currInTree->SetBranchStatus("weight_corr_*", status);

    // remove the w_* for all systematics... keep w_lumi for now
    if(m_isNormSys || (m_currVariation != ""))
    {
        m_currInTree->SetBranchStatus("w_EW", status);
        m_currInTree->SetBranchStatus("w_MCw", status);
        m_currInTree->SetBranchStatus("w_br", status);
        m_currInTree->SetBranchStatus("w_btagEff", status);
        if (m_hasWeightJet) m_currInTree->SetBranchStatus("w_jetJvt_SF", status);
        m_currInTree->SetBranchStatus("w_lepEff", status);
        m_currInTree->SetBranchStatus("w_pileup", status);
        m_currInTree->SetBranchStatus("w_triggerSF", status);
        m_currInTree->SetBranchStatus("w_xs", status);
        m_currInTree->SetBranchStatus("weight_sampleoverlap", status);
        if (m_hasWeightCorr) m_currInTree->SetBranchStatus("weight_corr", status);
        m_currInTree->SetBranchStatus("weight_lumi", status);
    }
}


void
ProcessMinitree::tokenizeString(const std::string& str_in,
        const std::string& delimiters,
        std::vector<std::string>& strs_out) const
{  
    strs_out.clear();
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str_in.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos = str_in.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos) {
        // Found a token, add it to the vector.
        strs_out.push_back(str_in.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str_in.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str_in.find_first_of(delimiters, lastPos);
    }
}

