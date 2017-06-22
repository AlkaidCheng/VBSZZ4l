#include "H4lCutFlow/OutputTree4l.h"
using namespace std;

OutputTree4l::OutputTree4l(TString outName, TString sysName, TString sampleName)
:OutputTree(outName, sysName, sampleName)
{
    m_inclTree = 0;
    m_isNormSys = false;
    m_isMETSys = false;
}

void OutputTree4l::initialize()
{
    OutputTree::initialize();    
    removeVar();
    
    if(m_isNormSys)
    {
        output = new TFile (m_outName+"_normSys.root", "RECREATE");
    }
    else if(m_isMETSys)
    {
        output = new TFile (m_outName+"_metSys.root", "RECREATE");
    }
    else if (m_sysName.Length() > 0)
    {
        output = new TFile (m_outName+m_sysName+".root", "RECREATE");
    }
    else
    {
        // Nominal
        output = new TFile (m_outName+"_nom.root", "RECREATE");
    }
    // Adding all the trees
    
    m_inclTree    = new TTree("tree_incl_all", "all");
    m_inclTree->SetAutoFlush();
    bookTree(m_inclTree);

    initMetaData();
}



OutputTree4l::~OutputTree4l()
{
    
    output->Close();
    delete output;

//    For some reason deleting the ttrees, create a seg fault..
//    Is there a transfer of ownership when we write a ttree?
    
//    Deleting all the trees
//    delete m_inclTree;
    
}

// Intial decleration of the variables
void OutputTree4l::addVar()
{
    ////////
    // Event Level vars
    ////////
    m_intVar["run"]                 = -999;
    m_intVar["random_run"]          = -999;
    m_intLongVar["PRWHash"]         = -999;    
    m_intLongVar["event"]           = -999;
    m_intVar["lbn"]                 = -999;
    m_intVar["npv"]                 = -999;
    m_floatVar["ave_int_per_xing"]  = -999;
    m_intVar["event_type"]          = -999;
    m_intVar["GRLisOK"]             = -999;
    m_intVar["hasExtraLepNominal"]  = -999;
    m_intVar["bcid"]                = -999;
    m_intVar["bc_distanceFromFront"]= -999;

    ////////
    // Higgs vars
    ////////
    m_floatVar["mZ1_unconstrained"] = -999;
    m_floatVar["mZ2_unconstrained"] = -999;
    m_floatVar["m4l_unconstrained"] = -999;
    
    m_floatVar["mZ1_fsr"] = -999;
    m_floatVar["mZ2_fsr"] = -999;
    m_floatVar["m4l_fsr"] = -999;
    
    m_floatVar["mZ1_constrained"] = -999;
    m_floatVar["mZ2_constrained"] = -999;
    m_floatVar["m4l_constrained"] = -999;
    m_floatVar["m4l_constrained_HM"] = -999;
    
    m_floatVar["m4lerr_unconstrained"] = -999;
    m_floatVar["m4lerr_fsr"] = -999;
    m_floatVar["m4lerr_constrained"] = -999;

    m_floatVar["pt4l_unconstrained"]  = -999;
    m_floatVar["pt4l_constrained"]  = -999;
    m_floatVar["eta4l_unconstrained"] = -999;
    m_floatVar["phi4l_unconstrained"] = -999;
    m_floatVar["y4l_unconstrained"] = -999;

    m_floatArrayVar["lepton_pt"]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_eta"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_phi"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_m"]     = {{-999, -999, -999, -999}};

    // Vertex information
    m_floatVar["vtx4l_chi2ndf"]     = -999;
    m_intVar["pass_vtx4lCut"]       = -999;

    m_floatVar["BDT_discriminant"]  = -999;
    m_floatVar["KD_discriminant"]   = -999;
    m_floatVar["MELA"]      = -999;
    m_floatVar["HiggsME"]   = -999;

    // Agular variables
    m_floatVar["cthstr"]    = -999;
    m_floatVar["phi1"]      = -999;
    m_floatVar["cth1"]      = -999;
    m_floatVar["cth2"]      = -999;
    m_floatVar["phi"]       = -999;

    // Truth pairing 
    m_intVar["truth_pairing"]   = -999;
    m_intVar["truth_decay"]    = -999;

    m_intVar["cand_index"] = -999;


    ////////
    // Jet related vars
    ////////
    m_intVar["n_jets"]              = -999;
    m_floatVar["dijet_invmass"]     = -999;
    m_floatVar["dijet_deltaeta"]    = -999;
    m_floatVar["dijet_deltaphi"]    = -999;
    m_floatVar["dijet_pt"]          = -999;
    m_floatArrayVar["jet_pt"]       = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_eta"]      = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_phi"]      = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_m"]        = {{-999, -999, -999, -999}};
    m_intArrayVar["jet_passfJVT"]   = {{-999, -999, -999, -999}};
    m_intArrayVar["jet_btag70"]     = {{-999, -999, -999, -999}};
    m_intArrayVar["jet_btag85"]     = {{-999, -999, -999, -999}};
    m_intVar["n_jets_btag60"]       = -999;
    m_intVar["n_jets_btag70"]       = -999;
    m_intVar["n_jets_btag77"]       = -999;
    m_intVar["n_jets_btag85"]       = -999;
    m_floatVar["leading_jet_pt"]    = -999;
     
    m_intArrayVar["jet_partonTruthLabelID"] = {{-999, -999, -999, -999}};

    ////////
    // For coupling analysis
    ////////

    m_intVar["prod_type"]                       = -999;
    m_intVar["prod_type_HM"]                    = -999;
    m_intVar["HTXS_Stage0_Category"]            = -999;
    m_intVar["HTXS_Stage1_Category_pTjet25"]    = -999;
    m_intVar["HTXS_Stage1_Category_pTjet30"]    = -999;


    m_intVar["prod_type_w_fJVT"]                = -999;
    m_intVar["prod_type_HM_w_fJVT"]             = -999;

    m_floatVar["m4ljj_unconstrained"]           = -999; 

    m_floatVar["BDT_OneJet_jptetadR_discriminant"]      = -999;
    m_floatVar["BDT_TwoJet_discriminant"]               = -999;
    m_floatVar["BDT_VH_noptHjj_discriminant"]           = -999;
    m_floatVar["BDT_1Jet_pt4l_60"]                      = -999;
    m_floatVar["BDT_1Jet_pt4l_120"]                     = -999;
    m_floatVar["BDT_1Jet_pt4l_60_120"]                  = -999;
    m_floatVar["BDT_VBF_TOPO"]                          = -999;
    m_floatVar["BDT_VBF_Rest"]                          = -999;

    // For training BDT
    m_floatVar["pt4ljj_unconstrained"]          = -999;
    m_floatVar["min_dR_jZ"]                     = -999;
    m_floatVar["eta_zepp_ZZ"]                   = -999;
    m_floatVar["dR_jH"]                         = -999;

    ////////
    // For differential analysis
    ////////
    m_floatVar["pt4l_fsr"]  = -999;
    m_floatVar["y4l_fsr"]   = -999;
    m_floatVar["cthstr_fsr"]= -999;
    
    
    ////////
    // For mass analysis
    ////////
    m_floatArrayVar["lepton_pt_constrained"]      = {{-999, -999, -999, -999}};

    m_floatVar["fsr_pt"]                = -999;
    m_floatVar["fsr_pt_constrained"]    = -999;
    m_floatVar["fsr_eta"]               = -999;
    m_floatVar["fsr_phi"]               = -999;
    m_intVar["fsr_associated_lepton"]   = -999;
    m_intVar["fsr_type"]                = -999;

    
    ////////
    // For HM analysis
    ////////
    m_floatArrayVar["mu_IDpt"]            = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_IDeta"]           = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_IDphi"]           = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_MSpt"]            = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_MSeta"]           = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_MSphi"]           = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_phiInMS"]	  = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_qOverPsig"]       = {{-999, -999, -999, -999}};
    m_intArrayVar["mu_NPrecLayer"]        = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_redChi2"]	  = {{-999, -999, -999, -999}};

    m_floatVar["MCFM_dxs_ZZ"] 		  = -999;
    m_floatVar["MCFM_dxs_ggZZ"] 	  = -999;
    m_floatVar["MCFM_dxs_ggZZtot"] 	  = -999;
    m_floatVar["MCFM_dxs_ggZZint"] 	  = -999;
    m_floatVar["MCFM_dxs_HZZ"] 		  = -999;


    ////////
    // For some checks idk
    ////////
    //m_intArrayVar["mu_innerSmallHits"]            = {{-999, -999, -999, -999}};
    //m_intArrayVar["mu_innerLargeHits"]            = {{-999, -999, -999, -999}};
    //m_intArrayVar["mu_middleSmallHits"]           = {{-999, -999, -999, -999}};
    //m_intArrayVar["mu_middleLargeHits"]           = {{-999, -999, -999, -999}};
    //m_intArrayVar["mu_outerSmallHits"]            = {{-999, -999, -999, -999}};
    //m_intArrayVar["mu_outerLargeHits"]            = {{-999, -999, -999, -999}};



    ////////
    // For cross-checks
    ////////
    m_intArrayVar["lepton_id"]      = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_res"]   = {{-999, -999, -999, -999}};
    m_floatVar["leading_jet_width"]                 = -999;
    m_floatVar["subleading_jet_width"]              = -999;
    m_floatVar["leading_jet_TrackWidthPt1000"]      = -999;    
    m_floatVar["subleading_jet_TrackWidthPt1000"]   = -999;

    
    ////////
    // Weight
    ////////

    // lumi related vars
    m_doubleVar["w_xs"]      = -999;
    m_doubleVar["w_br"]      = -999;
    m_doubleVar["w_lumi"]    = -999;
    // Weight_corr
    m_doubleVar["w_lepEff"]      = -999;
    m_doubleVar["w_pileup"]      = -999;
    m_doubleVar["w_MCw"]         = -999;
    m_doubleVar["w_EW"]          = -999;
    m_doubleVar["w_triggerSF"]   = -999;
    m_doubleVar["w_sherpaJet"]   = -999; // run dependant
    m_doubleVar["w_sherpaLep"]   = -999; // run dependant    
    //m_doubleVar["w_jetJvt_SF"]   = -999; 
    m_doubleVar["w_btagEff"]     = -999;
    m_doubleVar["w_EWNLO"]       = -999;
    m_doubleVar["w_QCDNNLO"]     = -999;

    // Total weight
    m_doubleVar["weight"]                = -999;
    //m_doubleVar["weight_jet"]            = -999;
    //m_doubleVar["weight_bTag"]           = -999;
    m_doubleVar["weight_couplings"]      = -999;
    m_doubleVar["w_couplings"]           = -999;    

    m_doubleVar["weight_lumi"]           = -999;
    m_doubleVar["weight_sampleoverlap"]  = -999;
    m_doubleVar["weight_corr"]           = -999;

    ////////
    // For Jet Bin Migration
    ////////
    m_intVar["n_jets_truth_20"] = -999;
    m_intVar["n_jets_truth_25"] = -999;
    m_intVar["n_jets_truth_30"] = -999;

    m_floatArrayVar["jet_pt_truth"]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_eta_truth"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_phi_truth"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_m_truth"]     = {{-999, -999, -999, -999}};


    ////////
    // Truth
    ////////
    m_intVar["truth_event_type"]                = -999;

    // Truth matched vars
    m_floatVar["m4l_truth_matched_bare"] = -999;
    m_floatVar["mZ1_truth_matched_bare"] = -999;
    m_floatVar["mZ2_truth_matched_bare"] = -999;

    m_floatVar["pt4l_truth_matched_bare"]  = -999;
    m_floatVar["eta4l_truth_matched_bare"] = -999;

    m_floatArrayVar["lepton_pt_truth_matched_bare"]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_eta_truth_matched_bare"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_phi_truth_matched_bare"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_m_truth_matched_bare"]     = {{-999, -999, -999, -999}};

    //m_floatArrayVar["lepton_pt_truth_matched_born"]    = {{-999, -999, -999, -999}};
    //m_floatArrayVar["lepton_eta_truth_matched_born"]   = {{-999, -999, -999, -999}};
    //m_floatArrayVar["lepton_phi_truth_matched_born"]   = {{-999, -999, -999, -999}};
    //m_floatArrayVar["lepton_m_truth_matched_born"]     = {{-999, -999, -999, -999}};

    //m_floatArrayVar["lepton_pt_truth_matched_dressed"]    = {{-999, -999, -999, -999}};
 	//m_floatArrayVar["lepton_eta_truth_matched_dressed"]   = {{-999, -999, -999, -999}};
 	//m_floatArrayVar["lepton_phi_truth_matched_dressed"]   = {{-999, -999, -999, -999}};
 	//m_floatArrayVar["lepton_m_truth_matched_dressed"]     = {{-999, -999, -999, -999}};

    // Truth vars
    m_floatVar["m4l_truth_born"] = -999;
    m_floatVar["mZ1_truth_born"] = -999;
    m_floatVar["mZ2_truth_born"] = -999;

    m_floatVar["pt4l_truth_born"]  = -999;
    m_floatVar["eta4l_truth_born"] = -999;
    m_floatVar["y4l_truth_born"] = -999;
    
    m_floatArrayVar["lepton_pt_truth_born"]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_eta_truth_born"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_phi_truth_born"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_m_truth_born"]     = {{-999, -999, -999, -999}};

    ////////
    // MET
    ////////
    m_floatVar["met_et"]        = -999;
    m_floatVar["met_sum_et"]    = -999;
    m_floatVar["met_phi"]       = -999;


    m_floatVar["leading_additional_lepton_pt"]       = -999; 
    
}

void OutputTree4l::addDataSpecificVar()
{
    m_stringVar["file_name"] = "";
    m_stringVar["sample_name"] = "";
    
    m_intArrayVar["lepton_quality"]     = {{-999, -999, -999, -999}};
    m_intArrayVar["lepton_charge"]      = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_d0sig"]     = {{-999, -999, -999, -999}};
    
    m_floatArrayVar["lepton_ptvarcone30"]     = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_ptvarcone20"]     = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_topoetcone20"]    = {{-999, -999, -999, -999}};


    ////////
    // For HM analysis
    ////////
    m_floatArrayVar["mu_IDpt"]          = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_MSpt"]          = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_qOverPsig"]     = {{-999, -999, -999, -999}};
    m_intArrayVar["mu_NPrecLayer"]      = {{-999, -999, -999, -999}};
    m_intArrayVar["mu_pass_highPt_WP"]	= {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_chi2"]		= {{-999, -999, -999, -999}};
}

void OutputTree4l::addTriggerSpecificVar()
{
    //Add for Trigger Efficiency
    //for Muon
    m_intLongVar["HLT_mu20_ivarloose_L1MU15"] = -999;
    m_intLongVar["HLT_mu20_iloose_L1MU15"] = -999;
    m_intLongVar["HLT_mu24_ivarloose_L1MU15"] = -999;
    m_intLongVar["HLT_mu24_ivarmedium"] = -999;
    m_intLongVar["HLT_mu24_imedium"] = -999;
    m_intLongVar["HLT_mu26_ivarmedium"] = -999;
    m_intLongVar["HLT_mu26_imedium"] = -999;
    m_intLongVar["HLT_mu40"] = -999;
    m_intLongVar["HLT_mu50"] = -999;
    m_intLongVar["HLT_mu60"] = -999;
    m_intLongVar["HLT_mu60_0eta105_msonly"] = -999;
    m_intLongVar["HLT_mu20_mu8noL1"] = -999;
    m_intLongVar["HLT_mu22_mu8noL1"] = -999;
    m_intLongVar["HLT_mu24_mu8noL1"] = -999;
    m_intLongVar["HLT_2mu10"] = -999;
    m_intLongVar["HLT_2mu14"] = -999;
    m_intLongVar["HLT_mu6_2mu4"] = -999;
    m_intLongVar["HLT_mu20_2mu4noL1"] = -999;
    m_intLongVar["HLT_mu22_2mu4noL1"] = -999;
    m_intLongVar["HLT_mu24_2mu4noL1"] = -999;
    m_intLongVar["HLT_3mu4"] = -999;
    m_intLongVar["HLT_3mu6"] = -999;
    m_intLongVar["HLT_3mu6_msonly"] = -999;
    m_intLongVar["L1_2MU6_3MU4"] = -999;
    //for Electron
    m_intLongVar["HLT_e5_lhtight"] = -999;
    m_intLongVar["HLT_e9_lhmedium"] = -999;
    m_intLongVar["HLT_e9_lhtight"] = -999;
    m_intLongVar["HLT_e12_lhloose"] = -999;
    m_intLongVar["HLT_e12_lhmedium"] = -999;
    m_intLongVar["HLT_e12_lhtight"] = -999;
    m_intLongVar["HLT_e15_lhloose_L1EM13VH"] = -999;
    m_intLongVar["HLT_e24_lhmedium_ivarloose"] = -999;
    m_intLongVar["HLT_e24_lhtight_ivarloose"] = -999;
    m_intLongVar["HLT_e26_lhvloose_L1EM20VH"] = -999;
    m_intLongVar["HLT_e26_lhmedium_L1EM22VHI"] = -999;
    m_intLongVar["HLT_e26_lhtight_ivarloose"] = -999;
    m_intLongVar["HLT_e60_medium"] = -999;
    m_intLongVar["HLT_e60_lhmedium"] = -999;
    m_intLongVar["HLT_e300_etcut"] = -999;
    m_intLongVar["HLT_e120_lhloose"] = -999;
    m_intLongVar["HLT_e140_lhloose"] = -999;
    m_intLongVar["HLT_2e12_lhvloose_L12EM10VH"] = -999;
    m_intLongVar["HLT_2e15_lhvloose_L12EM13VH"] = -999;
    m_intLongVar["HLT_2e17_lhvloose"] = -999;
    m_intLongVar["HLT_2e22_lhvloose"] = -999;
    m_intLongVar["HLT_e17_lhloose_2e9_lhloose"] = -999;
    m_intLongVar["HLT_e17_lhmedium_2e9_lhmedium"] = -999;
    m_intLongVar["L1_EM20VH_3EM10VH"] = -999;
    m_intLongVar["L1_2EM20VH"] = -999;
    m_intLongVar["L1_2EM22VH"] = -999;
    m_intLongVar["L1_EM22VHI"] = -999;
    m_intLongVar["L1_EM24VHI"] = -999;
    m_intLongVar["L1_EM26VHI"] = -999;
    //forTau
    m_intLongVar["HLT_tau35_medium1_tracktwo_tau25_medium1_tracktwo"] = -999;
    m_intLongVar["HLT_e17_lhmedium_nod0_ivarloose_tau25_medium1_tracktwo"] = -999;
    m_intLongVar["HLT_mu14_ivarloose_tau25_medium1_tracktwo_L1MU10_TAU12IM"] = -999;
    //for Electron (nod0)
    m_intLongVar["HLT_e24_lhmedium_nod0_ivarloose"] = -999;
    m_intLongVar["HLT_e24_lhtight_nod0_ivarloose"] = -999;
    m_intLongVar["HLT_e26_lhtight_nod0_ivarloose"] = -999;
    m_intLongVar["HLT_e28_lhtight_nod0_ivarloose"] = -999;
    m_intLongVar["HLT_e60_lhmedium_nod0"] = -999;
    m_intLongVar["HLT_e120_lhloose_nod0"] = -999;
    m_intLongVar["HLT_e140_lhloose_nod0"] = -999;
    m_intLongVar["HLT_2e12_lhvloose_nod0_L12EM10VH"] = -999;
    m_intLongVar["HLT_2e15_lhvloose_nod0_L12EM13VH"] = -999;
    m_intLongVar["HLT_2e17_lhvloose_nod0"] = -999;
    m_intLongVar["HLT_2e22_lhvloose_nod0"] = -999;
    m_intLongVar["HLT_e17_lhloose_nod0_2e9_lhloose_nod0"] = -999;
    m_intLongVar["HLT_e17_lhmedium_nod0_2e9_lhmedium_nod0"] = -999;
    //for Combined electron + muon
    m_intLongVar["HLT_e7_lhmedium_mu24"] = -999;
    m_intLongVar["HLT_e17_lhloose_mu14"] = -999;
    m_intLongVar["HLT_e24_lhmedium_L1EM20VHI_mu8noL1"] = -999;
    m_intLongVar["HLT_e26_lhmedium_L1EM22VHI_mu8noL1"] = -999;
    m_intLongVar["HLT_e12_lhloose_2mu10"] = -999;
    m_intLongVar["HLT_2e12_lhloose_mu10"] = -999;
    //for Combined electron + muon (nod0)
    m_intLongVar["HLT_e7_lhmedium_nod0_mu24"] = -999;
    m_intLongVar["HLT_e17_lhloose_nod0_mu14"] = -999;
    m_intLongVar["HLT_e24_lhmedium_nod0_L1EM20VHI_mu8noL1"] = -999;
    m_intLongVar["HLT_e26_lhmedium_nod0_L1EM22VHI_mu8noL1"] = -999;
    m_intLongVar["HLT_e12_lhloose_nod0_2mu10"] = -999;
    m_intLongVar["HLT_2e12_lhloose_nod0_mu10"] = -999;

}

void OutputTree4l::removeVar()
{
    // If systematic job, remove variables for sysJob
    if(m_sysName != ""){ removeSysVar(); }

    if(m_isMC)
    {
        m_varToRemove.push_back("GRLisOK");

        if(!((m_runNumber >= 363103 && m_runNumber <= 363411)))
        {
            m_varToRemove.push_back("w_sherpaJet");
        }
        // Low mass ggF and VBF
        if(!((m_runNumber >= 341500 && m_runNumber <= 341510) 
                    || (m_runNumber >= 341513 && m_runNumber <= 341523)
                    || (m_runNumber == 341471) || (m_runNumber == 341488)
                    || (m_runNumber == 345060)
                    || (m_runNumber == 363490) || (m_runNumber == 345107) || (m_runNumber == 345108)
                    ))
        {
            m_varToRemove.push_back("n_jets_truth_20");
            m_varToRemove.push_back("n_jets_truth_25");
            m_varToRemove.push_back("n_jets_truth_30");
            m_varToRemove.push_back("jet_pt_truth");
            m_varToRemove.push_back("jet_eta_truth");
            m_varToRemove.push_back("jet_phi_truth");
            m_varToRemove.push_back("jet_m_truth");
        }
    }

    // if data
    if(!m_isMC)
    {
        m_varToRemove.push_back("w_sherpaJet");
        m_varToRemove.push_back("w_*");
        //m_varToRemove.push_back("weight_*");
        m_varToRemove.push_back("HTXS*");
        m_varToRemove.push_back("PRWHash");
        m_varToRemove.push_back("random_run");
        m_varToRemove.push_back("*truth*");
    }



}

void OutputTree4l::removeSysVar()
{

    ////////
    // Event Level vars
    ////////
    m_varToRemove.push_back("lbn");
    m_varToRemove.push_back("npv");
    m_varToRemove.push_back("ave_int_per_xing");
    m_varToRemove.push_back("GRLisOK");

    ////////
    // Higgs vars
    ////////
    m_varToRemove.push_back("m4lerr_fsr");
    
    m_varToRemove.push_back("mZ1_unconstrained");
    m_varToRemove.push_back("mZ2_unconstrained"); 
    m_varToRemove.push_back("m4l_unconstrained"); 

    m_varToRemove.push_back("m4lerr_constrained");
    m_varToRemove.push_back("m4lerr_unconstrained");

    m_varToRemove.push_back("pt4l_constrained");
    m_varToRemove.push_back("eta4l_unconstrained");
    m_varToRemove.push_back("y4l_unconstrained");

    m_varToRemove.push_back("phi4l_unconstrained");

    m_varToRemove.push_back("lepton_pt");
    m_varToRemove.push_back("lepton_eta");
    m_varToRemove.push_back("lepton_phi");
    m_varToRemove.push_back("lepton_m");

    // Vertex information
    m_varToRemove.push_back("vtx4l_chi2ndf");
    
    // Agular variables
    m_varToRemove.push_back("cth1");
    m_varToRemove.push_back("cth2");
    m_varToRemove.push_back("phi");
    m_varToRemove.push_back("phi1");


    // Truth pairing 
    //m_varToRemove.push_back("truth_pairing");
    
    ////////
    // Jet related vars
    ////////
    //m_varToRemove.push_back("jet_pt");
    m_varToRemove.push_back("jet_eta");
    m_varToRemove.push_back("jet_phi");
    m_varToRemove.push_back("jet_m");
    m_varToRemove.push_back("jet_passfJVT");
    m_varToRemove.push_back("jet_btag70");
    m_varToRemove.push_back("jet_btag85");
    m_varToRemove.push_back("n_jets_btag60");
    m_varToRemove.push_back("n_jets_btag77");
    m_varToRemove.push_back("n_jets_btag85");

    ////////
    // For coupling analysis
    ////////
    m_varToRemove.push_back("m4ljj_unconstrained");

    // For training BDT
    m_varToRemove.push_back("pt4ljj_unconstrained");
    m_varToRemove.push_back("min_dR_jZ");
    m_varToRemove.push_back("eta_zepp_ZZ");

    m_varToRemove.push_back("dR_jH");
    

    ////////
    // For differential analysis
    ////////
    
    
    ////////
    // For mass analysis
    ////////
    m_varToRemove.push_back("fsr_pt");
    m_varToRemove.push_back("fsr_pt_constrained");
    m_varToRemove.push_back("fsr_eta");
    m_varToRemove.push_back("fsr_phi");
    m_varToRemove.push_back("fsr_associated_lepton");
    m_varToRemove.push_back("fsr_type");
    ////////
    // For cross-checks
    ////////
    m_varToRemove.push_back("lepton_id");

    m_varToRemove.push_back("leading_jet_TrackWidthPt1000");
    m_varToRemove.push_back("subleading_jet_TrackWidthPt1000");
    m_varToRemove.push_back("leading_jet_width");
    m_varToRemove.push_back("subleading_jet_width");
    m_varToRemove.push_back("lepton_res");


    
    ////////
    // For Jet Bin Migration
    ////////
    m_varToRemove.push_back("jet_*_truth");

    ////////
    // Truth
    ////////
    m_varToRemove.push_back("lep*_*_truth_matched_bare");
    m_varToRemove.push_back("lep*_*_truth_matched_born");
    m_varToRemove.push_back("lep*_*_truth_matched_dressed");
    m_varToRemove.push_back("m*_*_truth_matched_bare");
    m_varToRemove.push_back("pt4l_truth*");
    m_varToRemove.push_back("eta4l_truth*");
    m_varToRemove.push_back("jet*_truth*");
    m_varToRemove.push_back("m4l_truth_matched_bare");
    m_varToRemove.push_back("mZ1_truth_born");
    m_varToRemove.push_back("mZ1_truth_matched_bare");
    m_varToRemove.push_back("mZ2_truth_born");
    m_varToRemove.push_back("mZ2_truth_matched_bare");
    m_varToRemove.push_back("y4l_truth_born");
    m_varToRemove.push_back("m4l_truth_born");
    m_varToRemove.push_back("lepton_*_truth_born");

    ////////
    // MET
    ////////
    m_varToRemove.push_back("met_*");


    m_varToRemove.push_back("leading_additional_lepton_pt");
}


void OutputTree4l::removeFullEgammaSysVar()
{
    m_varToRemove.push_back("*BDT*");    
    m_varToRemove.push_back("jet*");    
    m_varToRemove.push_back("dijet*");    
    m_varToRemove.push_back("lepton*");  
    m_varToRemove.push_back("pt4l*");  
    m_varToRemove.push_back("eta*");  
    m_varToRemove.push_back("phi*");  
    m_varToRemove.push_back("y4l*");  
    m_varToRemove.push_back("KD*");  
    m_varToRemove.push_back("HiggsME");  
    m_varToRemove.push_back("cth*");  
    m_varToRemove.push_back("phi*");  
    m_varToRemove.push_back("n_*");  
    m_varToRemove.push_back("fsr*");  
    m_varToRemove.push_back("*lead*");  
    m_varToRemove.push_back("*truth*");  
  
}

void OutputTree4l::fillTree(OutputTreeType::OutputTreeType)
{
    // Fill the inclusive tree
    m_inclTree->Fill();
}

void OutputTree4l::writeTree()
{
    output->cd();
    m_inclTree->Write();
    m_metaDataTree->Write();

    output->mkdir("Variation-" + m_sysName);
    output->mkdir(m_sampleName);

    
    output->cd();
    output->mkdir("Hist");
    output->cd("Hist");

    for (auto it = m_THistVar.begin(); it != m_THistVar.end(); ++it)
    {
        it->second->Write();
    }

}

void OutputTree4l::setupVarsNormSys(std::vector<CP::SystematicSet> normSysList)
{
    if(m_inclTree !=0)
    {
        // This means that trees have been booked... we need to call this function before this intialize function has been called
        LOG(logERROR)<<"setupVarsNormSys function called after the intialize function";
        LOG(logERROR)<<"This ordering of func call is incorrect. setupVarsNormSys must be called before initialize";
    }
    
    // first remove the systematic variables
    removeSysVar();
    m_isNormSys = true;

    // now add the extra weight variable
    
    for (auto sys: normSysList)
    {
        //m_floatVar["weight_corr_"+sys.name()] = -999;
        //m_floatVar["weight_"+sys.name()] = -999;
        m_doubleVar["weight_var_"+sys.name()] = -999;
    }
}

void OutputTree4l::setupVarMETSys(std::vector<CP::SystematicSet> metSysList)
{
    if(m_inclTree !=0)
    {
        // This means that trees have been book... we need to call this function before this intialize function has been called
        LOG(logERROR)<<"setupVarMETSys function called after the intialize function";
        LOG(logERROR)<<"This ordering of func call is incorrect. setupVarMETSys must be called before initialize";
    }
    
    // first remove the systematic variables
    removeSysVar();
    m_isMETSys = true;
    
    // now add the extra weight variable
    
    for (auto sys: metSysList)
    {
        m_floatVar["met_et_"+sys.name()] = -999;
        m_floatVar["met_sum_et_"+sys.name()] = -999;
        m_floatVar["met_phi_"+sys.name()] = -999;
    }
}


void OutputTree4l::addHistrogram()
{
    OutputTree::addHistrogram();    

    m_THistVar["truthQuadType"] = new TH1F("truthQuadType" + m_sysName, "truthQuadType", 20, 0, 20);
    
    m_THistVar["pileUpHist"] = new TH1F("pileUpHist" + m_sysName, "pileUpHist", 100, 0, 100);
    m_THistVar["pileUpWeightHist"] = new TH1F("pileUpWeightHist" + m_sysName, "pileUpWeightHist", 100, 0, 100);
    
    m_THistVar["mucutFlowHist"] = new TH1F("mucutFlowHist" + m_sysName, "mucutFlowHist", 20, 0, 20);
    m_THistVar["elcutFlowHist"] = new TH1F("elcutFlowHist" + m_sysName, "elcutFlowHist", 20, 0, 20);
    m_THistVar["jetcutFlowHist"] = new TH1F("jetcutFlowHist" + m_sysName, "jetcutFlowHist", 20, 0, 20);
    
    m_THistVar["4mucutFlowHist"] = new TH1F("4mucutFlowHist" + m_sysName, "4mucutFlowHist", 20, 0, 20);
    m_THistVar["2e2mucutFlowHist"] = new TH1F("2e2mucutFlowHist" + m_sysName, "2e2mucutFlowHist", 20, 0, 20);
    m_THistVar["2mu2ecutFlowHist"] = new TH1F("2mu2ecutFlowHist" + m_sysName, "2mu2ecutFlowHist", 20, 0, 20);
    m_THistVar["4ecutFlowHist"] = new TH1F("4ecutFlowHist" + m_sysName, "4ecutFlowHist", 20, 0, 20);
    m_THistVar["4lcutFlowHist"] = new TH1F("4lcutFlowHist" + m_sysName, "4lcutFlowHist", 20, 0, 20);


    m_THistVar["4mucutFlowWHist"] = new TH1F("4mucutFlowWHist" + m_sysName, "4mucutFlowWHist", 20, 0, 20);
    m_THistVar["2e2mucutFlowWHist"] = new TH1F("2e2mucutFlowWHist" + m_sysName, "2e2mucutFlowWHist", 20, 0, 20);
    m_THistVar["2mu2ecutFlowWHist"] = new TH1F("2mu2ecutFlowWHist" + m_sysName, "2mu2ecutFlowWHist", 20, 0, 20);
    m_THistVar["4ecutFlowWHist"] = new TH1F("4ecutFlowWHist" + m_sysName, "4ecutFlowWHist", 20, 0, 20);
    m_THistVar["4lcutFlowWHist"] = new TH1F("4lcutFlowWHist" + m_sysName, "4lcutFlowWHist", 20, 0, 20);

    
    m_THistVar["nPassMuHist"] = new TH1F("nPassMuHist" + m_sysName, "nPassMuHist", 20, 0, 20);
    m_THistVar["nPassElHist"] = new TH1F("nPassElHist" + m_sysName, "nPassElHist", 20, 0, 20);
    m_THistVar["nPassJetHist"] = new TH1F("nPassJetHist" + m_sysName, "nPassJetHist", 20, 0, 20);
    m_THistVar["nPassPhotonHist"] = new TH1F("nPassPhotonHist" + m_sysName, "nPassPhotonHist", 20, 0, 20);
    // Muons cuts
    m_THistVar["muStacoPTHist"]         = new TH1F("muStacopTHist" + m_sysName, "pTHist;pT[Mev];Event",         100, 0, 250*1000);
    m_THistVar["muStacoEtaHist"]        = new TH1F("muStacoetaHist" + m_sysName, "etaHist;eta;Event",       50, -4, 4);
    m_THistVar["muCaloPTHist"]      = new TH1F("muCalopTHist" + m_sysName, "pTHist;pT[Mev];Event",      100, 0, 250*1000);
    m_THistVar["muCaloEtaHist"]     = new TH1F("muCaloetaHist" + m_sysName, "etaHist;eta;Event",        50, -4, 4);
    m_THistVar["muSAPTHist"]        = new TH1F("muSApTHist" + m_sysName, "pTHist;pT[Mev];Event",        100, 0, 250*1000);
    m_THistVar["muSAEtaHist"]       = new TH1F("muSAetaHist" + m_sysName, "etaHist;eta;Event",      50, -4, 4);
    m_THistVar["muStacoPTHistAfterSel"]         = new TH1F("muStacopTHistAfterSel" + m_sysName, "pTHist;pT[Mev];Event",         100, 0, 250*1000);
    m_THistVar["muStacoEtaHistAfterSel"]        = new TH1F("muStacoetaHistAfterSel" + m_sysName, "etaHist;eta;Event",       50, -4, 4);
    m_THistVar["muCaloPTHistAfterSel"]      = new TH1F("muCalopTHistAfterSel" + m_sysName, "pTHist;pT[Mev];Event",      100, 0, 250*1000);
    m_THistVar["muCaloEtaHistAfterSel"]     = new TH1F("muCaloetaHistAfterSel" + m_sysName, "etaHist;eta;Event",        50, -4, 4);
    m_THistVar["muSAPTHistAfterSel"]        = new TH1F("muSApTHistAfterSel" + m_sysName, "pTHist;pT[Mev];Event",        100, 0, 250*1000);
    m_THistVar["muSAEtaHistAfterSel"]       = new TH1F("muSAetaHistAfterSel" + m_sysName, "etaHist;eta;Event",      50, -4, 4);
    
    // Electron
    m_THistVar["elETHist"]      = new TH1F("elETHist" + m_sysName, "ETHist;ET[Mev];Event",          100, 0, 250*1000);
    m_THistVar["elEtaHist"]     = new TH1F("eletaHist" + m_sysName, "etaHist;eta;Event",            50, -4, 4);
    m_THistVar["elETHistAfterSel"]      = new TH1F("elETHistAfterSel" + m_sysName, "ETHist;ET[Mev];Event",          100, 0, 250*1000);
    m_THistVar["elEtaHistAfterSel"]     = new TH1F("eletaHistAfterSel" + m_sysName, "etaHist;eta;Event",            50, -4, 4);

    // Jet
    m_THistVar["jetPTHist"]     = new TH1F("jetpTHist" + m_sysName, "pTHist;pT[Mev];Event",         100, 0, 250*1000);
    m_THistVar["jetEtaHist"]    = new TH1F("jetetaHist" + m_sysName, "etaHist;eta;Event",           50, -4, 4);
    
    m_THistVar["jetPTHistAfterSel"]     = new TH1F("jetpTHistAfterSel" + m_sysName, "pTHist;pT[Mev];Event",         100, 0, 250*1000);
    m_THistVar["jetEtaHistAfterSel"]    = new TH1F("jetetaHistAfterSel" + m_sysName, "etaHist;eta;Event",           50, -4, 4);
}



