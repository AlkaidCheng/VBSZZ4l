#include "H4lCutFlow/OutputTreeBkg.h"
using namespace std;

OutputTreeBkg::OutputTreeBkg(TString outName, TString sysName, TString sampleName)
:OutputTree(outName, sysName, sampleName)
{
    m_relaxIsoD0Tree = 0;
    m_emuTree = 0;
    m_ssTree = 0;
    m_threeLplusXTree = 0;
    
    
    m_isNormSys = false;
}

void OutputTreeBkg::initialize()
{
    OutputTree::initialize();
    removeVar();

    if(m_isNormSys)
    {
        output = new TFile (m_outName+"_normSys.root", "RECREATE");
    }
    else
    {
        output = new TFile (m_outName+m_sysName+".root", "RECREATE");
    }
    // Adding all the trees
    
    m_relaxIsoD0Tree    = new TTree("tree_relaxIsoD0", "all");
    m_relaxIsoD0Tree->SetAutoFlush();
    bookTree(m_relaxIsoD0Tree);
    
    
    m_emuTree    = new TTree("tree_emu", "all");
    m_emuTree->SetAutoFlush();
    bookTree(m_emuTree);
    
    m_ssTree    = new TTree("tree_ss", "all");
    m_ssTree->SetAutoFlush();
    bookTree(m_ssTree);
    
    m_threeLplusXTree    = new TTree("tree_relaxee", "all");
    m_threeLplusXTree->SetAutoFlush();
    bookTree(m_threeLplusXTree);

    initMetaData();    
}



OutputTreeBkg::~OutputTreeBkg()
{
    
    output->Close();
    delete output;

//    For some reason deleting the ttrees, create a seg fault..
//    Is there a transfer of ownership when we write a ttree?
    
//    Deleting all the trees
//    delete m_relaxElElTree;
    
}

// Intial decleration of the variables
void OutputTreeBkg::addVar()
{
    LOG(logINFO)<<"Adding vars";

    m_intVar["run"] = -999;
    m_intVar["random_run"] = -999;
    m_intLongVar["event"]   = -999;
    //m_intLongVar["PRWHash"] = -999;
    m_intVar["lbn"] = -999;
    m_intVar["npv"] = -999;
    m_intVar["prod_type_HM"]    = -999;
    m_intVar["truth_event_type"]          = -999;
    m_floatVar["ave_int_per_xing"] = -999;

    m_intVar["cand_index"] = -999;    
    m_intVar["event_type"] = -999;
    m_intVar["prod_type"] = -999;
    m_intVar["GRLisOK"]   = -999;

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

    m_floatVar["pt4l_unconstrained"]  = -999;
    m_floatVar["eta4l_unconstrained"] = -999;
    m_floatVar["phi4l_unconstrained"] = -999;
    m_floatVar["y4l_unconstrained"] = -999;
    m_floatVar["pt4l_constrained"]  = -999;

    // For differential
    m_floatVar["pt4l_fsr"]  = -999;
    m_floatVar["y4l_fsr"]  = -999;
    m_floatVar["cthstr_fsr"]    = -999;
    
    m_floatArrayVar["lepton_pt"]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_eta"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_phi"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_m"]     = {{-999, -999, -999, -999}};
    m_intArrayVar["lepton_id"]      = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_res"]   = {{-999, -999, -999, -999}};
    
    
    // Bkg vars
    // common for all leptons
    m_intArrayVar["lepton_charge"]      = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_d0sig"]     = {{-999, -999, -999, -999}};
    
    m_floatArrayVar["lepton_ptvarcone30"]     = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_ptvarcone20"]     = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_topoetcone20"]    = {{-999, -999, -999, -999}};

    m_intArrayVar["lepton_passD0sig"]   = {{-999, -999, -999, -999}};
    m_intArrayVar["lepton_passIsoCut"]  = {{-999, -999, -999, -999}};
    
    // el specific
    //m_intArrayVar["el_recoClass"]   = {{-999, -999, -999, -999}};
    m_intArrayVar["el_MCClass"]     = {{-999, -999, -999, -999}};
    //m_floatArrayVar["el_Rphi"]      = {{-999, -999, -999, -999}};
    //m_floatArrayVar["el_Reta"]      = {{-999, -999, -999, -999}};
    //m_floatArrayVar["el_f1"]        = {{-999, -999, -999, -999}};
    //m_floatArrayVar["el_Deta1"]     = {{-999, -999, -999, -999}};
    //m_intArrayVar["el_nBL"]         = {{-999, -999, -999, -999}};
    m_intArrayVar["el_nInnerExpPix"]= {{-999, -999, -999, -999}}; // Actually used in the fit
    //m_intArrayVar["el_nPix"]        = {{-999, -999, -999, -999}};
    //m_intArrayVar["el_nSCT"]        = {{-999, -999, -999, -999}};
    m_floatArrayVar["el_rTRT"]      = {{-999, -999, -999, -999}};
    //m_floatArrayVar["el_eProbHT"]   = {{-999, -999, -999, -999}};
    //m_floatArrayVar["el_eOverP"]    = {{-999, -999, -999, -999}};
    //m_floatArrayVar["el_expInner"]          = {{-999, -999, -999, -999}};
    //m_floatArrayVar["el_expNextToInner"]    = {{-999, -999, -999, -999}};
    //m_floatArrayVar["el_nInner"]            = {{-999, -999, -999, -999}};
    //m_floatArrayVar["el_nNextToInner"]      = {{-999, -999, -999, -999}};

    
    // mu specific
    m_intArrayVar["mu_MCPartType"]  = {{-999, -999, -999, -999}};
    m_intArrayVar["mu_MCOriginType"]= {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_IDpt"]      = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_MSpt"]      = {{-999, -999, -999, -999}};
    m_floatArrayVar["mu_qOverPsig"] = {{-999, -999, -999, -999}};
    m_intArrayVar["mu_author"]      = {{-999, -999, -999, -999}};
    m_intArrayVar["mu_type"]        = {{-999, -999, -999, -999}};
    m_intArrayVar["mu_NPrecLayer"]  = {{-999, -999, -999, -999}};
    m_intArrayVar["mu_nInnerExpPix"]= {{-999, -999, -999, -999}};
    
    m_intVar["n_jets"] = -999;
    m_floatVar["dijet_invmass"]      = -999;
    m_floatVar["dijet_deltaeta"]     = -999;
    m_floatVar["dijet_deltaphi"]     = -999;
    m_floatVar["dijet_pt"]           = -999;
    m_floatArrayVar["jet_pt"]        = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_eta"]       = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_phi"]       = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_m"]         = {{-999, -999, -999, -999}};
    m_intArrayVar["jet_passfJVT"]    = {{-999, -999, -999, -999}};
    m_intArrayVar["jet_btag70"]      = {{-999, -999, -999, -999}};
    m_intArrayVar["jet_btag85"]      = {{-999, -999, -999, -999}};
    m_intVar["n_jets_btag60"] = -999;
    m_intVar["n_jets_btag70"] = -999;
    m_intVar["n_jets_btag77"] = -999;
    m_intVar["n_jets_btag85"] = -999;
   

    
    // Agular variables
    m_floatVar["cthstr"]    = -999;
    m_floatVar["phi1"]      = -999;
    m_floatVar["cth1"]      = -999;
    m_floatVar["cth2"]      = -999;
    m_floatVar["phi"]       = -999;

    // Vertex information
    m_floatVar["vtx4l_chi2ndf"] = -999;
    m_intVar["pass_vtx4lCut"] = -999;    

    // Weights
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
    
    // Total weight
    m_doubleVar["weight"]                = -999;
    //m_doubleVar["weight_jet"]            = -999;
    //m_doubleVar["weight_bTag"]           = -999;
    m_doubleVar["weight_lumi"]           = -999;
    m_doubleVar["weight_sampleoverlap"]  = -999;
    m_doubleVar["weight_corr"]           = -999;

    m_floatVar["met_et"]        = -999;
    m_floatVar["met_sum_et"]    = -999;
    m_floatVar["met_phi"]       = -999;

    m_floatVar["m4ljj_unconstrained"]        = -999;

    m_floatVar["KD_discriminant"]                       = -999;
    m_floatVar["MELA"]                                  = -999;
    m_floatVar["BDT_discriminant"]                      = -999;
    m_floatVar["BDT_OneJet_jptetadR_discriminant"]      = -999;
    m_floatVar["BDT_TwoJet_discriminant"]               = -999;
    m_floatVar["BDT_VH_noptHjj_discriminant"]           = -999;
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

    m_floatVar["pt4ljj_unconstrained"]       = -999;
    m_floatVar["min_dR_jZ"]                  = -999;
    m_floatVar["eta_zepp_ZZ"]                = -999;

    m_floatVar["leading_jet_width"]         = -999;
    m_floatVar["subleading_jet_width"]      = -999;
    m_floatVar["leading_jet_TrackWidthPt1000"]          = -999;    
    m_floatVar["subleading_jet_TrackWidthPt1000"]       = -999;

    m_floatVar["leading_additional_lepton_pt"]       = -999;

    //// Truth matched vars
    //m_floatVar["m4l_truth_matched_bare"] = -999;
    //m_floatVar["mZ1_truth_matched_bare"] = -999;
    //m_floatVar["mZ2_truth_matched_bare"] = -999;

    //m_floatVar["pt4l_truth_matched_bare"]  = -999;
    //m_floatVar["eta4l_truth_matched_bare"] = -999;

    //m_floatArrayVar["lepton_pt_truth_matched_bare"]    = {{-999, -999, -999, -999}};
    //m_floatArrayVar["lepton_eta_truth_matched_bare"]   = {{-999, -999, -999, -999}};
    //m_floatArrayVar["lepton_phi_truth_matched_bare"]   = {{-999, -999, -999, -999}};
    //m_floatArrayVar["lepton_m_truth_matched_bare"]     = {{-999, -999, -999, -999}};

    //// Truth vars
    //m_floatVar["m4l_truth_born"] = -999;
    //m_floatVar["mZ1_truth_born"] = -999;
    //m_floatVar["mZ2_truth_born"] = -999;

    //m_floatVar["pt4l_truth_born"]  = -999;
    //m_floatVar["eta4l_truth_born"] = -999;
    //m_floatVar["y4l_truth_born"] = -999;
    //
    //m_floatArrayVar["lepton_pt_truth_born"]    = {{-999, -999, -999, -999}};
    //m_floatArrayVar["lepton_eta_truth_born"]   = {{-999, -999, -999, -999}};
    //m_floatArrayVar["lepton_phi_truth_born"]   = {{-999, -999, -999, -999}};
    //m_floatArrayVar["lepton_m_truth_born"]     = {{-999, -999, -999, -999}};

    //    // For Jet bin migration
    //m_intVar["n_jets_truth_20"] = -999;
    //m_intVar["n_jets_truth_25"] = -999;
    //m_intVar["n_jets_truth_30"] = -999;

    //m_floatArrayVar["jet_pt_truth"]    = {{-999, -999, -999, -999}};
    //m_floatArrayVar["jet_eta_truth"]   = {{-999, -999, -999, -999}};
    //m_floatArrayVar["jet_phi_truth"]   = {{-999, -999, -999, -999}};
    //m_floatArrayVar["jet_m_truth"]     = {{-999, -999, -999, -999}};

    //m_intVar["truth_pairing"] = -999;

}

void OutputTreeBkg::removeVar()
{
    // If systematic job, remove variables for sysJob
    if(m_sysName != ""){ removeSysVar(); }

    if(m_isMC)
    {
        if(!((m_runNumber >= 363103 && m_runNumber <= 363411)))
        {
            m_varToRemove.push_back("w_sherpaJet");
        }
         // Low mass ggF and VBF
        if(!((m_runNumber >= 341500 && m_runNumber <= 341510) 
                    || (m_runNumber >= 341513 && m_runNumber <= 341523)
                    || (m_runNumber == 341471) || (m_runNumber == 341488)
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
        m_varToRemove.push_back("*truth*");
    }

}

void OutputTreeBkg::addDataSpecificVar()
{
    m_stringVar["file_name"] = "";
    m_stringVar["sample_name"] = "";
}


void OutputTreeBkg::removeSysVar()
{
}


void OutputTreeBkg::fillTree(OutputTreeType::OutputTreeType type)
{
    if (type == OutputTreeType::d0IsoRelax)         m_relaxIsoD0Tree->Fill();
    else if (type == OutputTreeType::emu)           m_emuTree->Fill();
    else if (type == OutputTreeType::sameSign)      m_ssTree->Fill();
    else if (type == OutputTreeType::threeLplusX)   m_threeLplusXTree->Fill();
    else
    {
        LOG(logERROR)<<"OutputTreeBkg::fillTree - input tree type not supported";
        LOG(logERROR)<<"Type: "<<type;
    }
    
}

void OutputTreeBkg::writeTree()
{

    output->cd();
    m_relaxIsoD0Tree->Write();
    m_emuTree->Write();
    m_ssTree->Write();
    m_threeLplusXTree->Write();

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

void OutputTreeBkg::setupVarsNormSys(std::vector<CP::SystematicSet> normSysList)
{
    if(m_relaxIsoD0Tree !=0)
    {
        // This means that trees have been book... we need to call this function before this intialize function has been called
        LOG(logERROR)<<"setupVarsNormSys function called after the intialize function";
        LOG(logERROR)<<"This ordering of func call is incorrect. setupVarsNormSys must be called before initialize";
    }
    
    // first remove the systematic variables
    removeSysVar();
    m_isNormSys = true;

    // now add the extra weight variable
    
    for (auto sys: normSysList)
    {
        m_doubleVar["weight_corr_"+sys.name()] = -999;
        m_doubleVar["weight_lumi_"+sys.name()] = -999;
    }
}


void OutputTreeBkg::addHistrogram()
{
    OutputTree::addHistrogram();
    
    m_THistVar["truthQuadType"] = new TH1F("truthQuadType" + m_sysName, "truthQuadType", 20, 0, 20);
    
    m_THistVar["pileUpHist"] = new TH1F("pileUpHist" + m_sysName, "pileUpHist", 100, 0, 100);
    m_THistVar["pileUpWeightHist"] = new TH1F("pileUpWeightHist" + m_sysName, "pileUpWeightHist", 100, 0, 100);
    
    m_THistVar["mucutFlowHist"] = new TH1F("mucutFlowHist" + m_sysName, "mucutFlowHist", 20, 0, 20);
    m_THistVar["elcutFlowHist"] = new TH1F("elcutFlowHist" + m_sysName, "elcutFlowHist", 20, 0, 20);
    m_THistVar["elLoosecutFlowHist"] = new TH1F("elLoosecutFlowHist" + m_sysName, "elLoosecutFlowHist", 20, 0, 20);
    m_THistVar["jetcutFlowHist"] = new TH1F("jetcutFlowHist" + m_sysName, "jetcutFlowHist", 20, 0, 20);
    
    m_THistVar["4mucutFlowHist"] = new TH1F("4mucutFlowHist" + m_sysName, "4mucutFlowHist", 20, 0, 20);
    m_THistVar["2e2mucutFlowHist"] = new TH1F("2e2mucutFlowHist" + m_sysName, "2e2mucutFlowHist", 20, 0, 20);
    m_THistVar["2mu2ecutFlowHist"] = new TH1F("2mu2ecutFlowHist" + m_sysName, "2mu2ecutFlowHist", 20, 0, 20);
    m_THistVar["4ecutFlowHist"] = new TH1F("4ecutFlowHist" + m_sysName, "4ecutFlowHist", 20, 0, 20);
    m_THistVar["4lcutFlowHist"] = new TH1F("4lcutFlowHist" + m_sysName, "4lcutFlowHist", 20, 0, 20);
    
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



