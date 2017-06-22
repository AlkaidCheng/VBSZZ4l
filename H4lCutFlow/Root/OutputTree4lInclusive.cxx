#include "H4lCutFlow/OutputTree4lInclusive.h"
using namespace std;

OutputTree4lInclusive::OutputTree4lInclusive(TString outName, TString sysName, TString sampleName)
:OutputTree(outName, sysName, sampleName)
{
    m_inclTree = 0;
    m_isNormSys = false;
    m_leptonType = "";
    
}

void OutputTree4lInclusive::initialize()
{
    OutputTree::initialize();
    //removeVar();
    
    if(m_isNormSys)
    {
        output = new TFile (m_outName+"_normSys.root", "RECREATE");
    }
    else
    {
        output = new TFile (m_outName+m_sysName+"_fid.root", "RECREATE");
    }
    
    m_inclTree    = new TTree("tree_incl_all", "all");
    m_inclTree->SetAutoFlush(); 
    bookTree(m_inclTree);

    initMetaData();    
}



OutputTree4lInclusive::~OutputTree4lInclusive()
{
    
    output->Close();
    delete output;


//    For some reason deleting the ttrees, create a seg fault..
//    Is there a transfer of ownership when we write a ttree?
    
//    Deleting all the trees
//    delete m_4muTree;
//    delete m_2e2muTree;
//    delete m_2mu2eTree;
//    delete m_4eTree;
//
//    delete m_inclTree;
    
}

// Intial decleration of the variables
void OutputTree4lInclusive::addVar()
{
    std::string str_truth = m_leptonType+"_truth";
    std::string str_4lsel = m_leptonType+"_4lsel";

    m_intVar["run"] = -999;
    m_intLongVar["event"]   = -999;
    m_intVar["lbn"] = -999;
    
    m_intVar["event_type_fid"+m_leptonType+"_truth"] = -999;
    m_intVar["event_type_fid"+m_leptonType+"_4lsel"] = -999;
    m_intVar["truth_event_type"]          = -999;
    m_intVar["truth_decay"]    = -999;
    
    m_floatVar["leading_lepton_pt_fid"+str_truth] = -999;
    m_floatVar["subleading_lepton_pt_fid"+str_truth] = -999;
    m_floatVar["leading_lepton_pt_fid"+str_4lsel] = -999;
    m_floatVar["subleading_lepton_pt_fid"+str_4lsel] = -999;

    m_floatArrayVar["lepton_pt_fid"+str_truth]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_eta_fid"+str_truth]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_phi_fid"+str_truth]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_m_fid"+str_truth]    = {{-999, -999, -999, -999}};
    m_intArrayVar["lepton_pdgid_fid"+str_truth]    = {{-999, -999, -999, -999}};
    
    m_floatArrayVar["lepton_pt_fid"+str_4lsel]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_eta_fid"+str_4lsel]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_phi_fid"+str_4lsel]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_m_fid"+str_4lsel]    = {{-999, -999, -999, -999}};
    
    m_intVar["n_jets_fid"+str_truth] = -999;
    m_intVar["n_bjets_fid"+str_truth] = -999;
    m_floatVar["leading_jet_pt_fid"+str_truth]    = -999;
    m_floatVar["subleading_jet_pt_fid"+str_truth]  = -999;
    m_floatVar["dijet_m_fid"+str_truth]     = -999;
    m_floatVar["dijet_deltaeta_fid"+str_truth]     = -999;
    m_floatVar["dijet_deltaphi_fid"+str_truth]     = -999;

    m_intVar["n_jets_fid"+str_4lsel] = -999;
    m_intVar["n_bjets_fid"+str_4lsel] = -999;
    m_floatVar["leading_jet_pt_fid"+str_4lsel]    = -999;
    m_floatVar["subleading_jet_pt_fid"+str_4lsel]  = -999;
    m_floatVar["dijet_m_fid"+str_4lsel]     = -999;
    m_floatVar["dijet_deltaeta_fid"+str_4lsel]     = -999;
    m_floatVar["dijet_deltaphi_fid"+str_4lsel]     = -999;

    m_floatArrayVar["jet_pt_fid"+str_truth]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_eta_fid"+str_truth]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_phi_fid"+str_truth]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_m_fid"+str_truth]    = {{-999, -999, -999, -999}};
    
    m_floatArrayVar["jet_pt_fid"+str_4lsel]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_eta_fid"+str_4lsel]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_phi_fid"+str_4lsel]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_m_fid"+str_4lsel]    = {{-999, -999, -999, -999}};

   
    m_floatArrayVar["lepton_pt_fR"]     = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_eta_fR"]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_phi_fR"]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["lepton_m_fR"]      = {{-999, -999, -999, -999}};
    m_intArrayVar["lepton_PDGID_fR"]    = {{-999, -999, -999, -999}};
    m_intArrayVar["lepton_status_fR"]    = {{-999, -999, -999, -999}};

    // Agular variables
    m_floatVar["cthstr_fid"+str_truth]    = -999;
    m_floatVar["phi1_fid"+str_truth]      = -999;
    m_floatVar["cth1_fid"+str_truth]      = -999;
    m_floatVar["cth2_fid"+str_truth]      = -999;
    m_floatVar["phi_fid"+str_truth]       = -999;
    m_floatVar["cthstr_fid"+str_4lsel]    = -999;
    m_floatVar["phi1_fid"+str_4lsel]      = -999;
    m_floatVar["cth1_fid"+str_4lsel]      = -999;
    m_floatVar["cth2_fid"+str_4lsel]      = -999;
    m_floatVar["phi_fid"+str_4lsel]       = -999;

    // Weights
    // lumi related vars
    m_doubleVar["w_xs"]      = -999;
    m_doubleVar["w_br"]      = -999;
    m_doubleVar["w_lumi"]    = -999;
    // Weight_corr
    m_doubleVar["w_lepEff"]      = -999;
    m_doubleVar["w_btagEff"]     = -999;
    m_doubleVar["w_pileup"]      = -999;
    m_doubleVar["w_MCw"]         = -999;
    m_doubleVar["w_EW"]          = -999;
    m_doubleVar["w_triggerSF"]   = -999;
    m_doubleVar["w_sherpaJet"]   = -999; // run dependant
    m_doubleVar["w_sherpaLep"]   = -999; // run dependant
    //m_doubleVar["w_jetJvt_SF"]   = -999;
    m_doubleVar["w_EWNLO"]       = -999;
    m_doubleVar["w_QCDNNLO"]     = -999;
    
    // Overlap
    m_doubleVar["w_ZZoverlap"]   = -999;
    m_doubleVar["w_Higgs_pt"]   = -999;

    // Total weight
    m_doubleVar["weight"]                = -999;
    m_doubleVar["weight_lumi"]           = -999;
    m_doubleVar["weight_sampleoverlap"]  = -999;
    m_doubleVar["weight_corr"]           = -999;

    // Fiducial vars
    std::string str_pass = m_leptonType+"_cut";
    m_intVar["pass_fid"+str_pass] = -999;

    m_floatVar["higgs_m_fid"+str_truth] = -999;
    m_floatVar["Z1_m_fid"+str_truth] = -999;
    m_floatVar["Z2_m_fid"+str_truth] = -999;

    m_floatVar["higgs_pt_fid"+str_truth]  = -999;
    m_floatVar["Z1_pt_fid"+str_truth] = -999;
    m_floatVar["Z2_pt_fid"+str_truth] = -999;
    
    m_floatVar["higgs_eta_fid"+str_truth] = -999;
    m_floatVar["Z1_eta_fid"+str_truth] = -999;
    m_floatVar["Z2_eta_fid"+str_truth] = -999;
  
    m_floatVar["Z1_phi_fid"+str_truth] = -999;
    m_floatVar["Z2_phi_fid"+str_truth] = -999;

    m_floatVar["higgs_y_fid"+str_truth] = -999;

    m_floatVar["higgs_m_fid"+str_4lsel] = -999;
    m_floatVar["Z1_m_fid"+str_4lsel] = -999;
    m_floatVar["Z2_m_fid"+str_4lsel] = -999;

    m_floatVar["higgs_pt_fid"+str_4lsel]  = -999;
    m_floatVar["Z1_pt_fid"+str_4lsel] = -999;
    m_floatVar["Z2_pt_fid"+str_4lsel] = -999;

    m_floatVar["higgs_eta_fid"+str_4lsel] = -999;
    m_floatVar["Z1_eta_fid"+str_4lsel] = -999;
    m_floatVar["Z2_eta_fid"+str_4lsel] = -999; 
    
    m_floatVar["Z1_phi_fid"+str_4lsel] = -999;
    m_floatVar["Z2_phi_fid"+str_4lsel] = -999; 

    
    m_floatVar["higgs_y_fid"+str_4lsel] = -999;
    

   //for jet bin migration
    m_intVar["n_jets_truth_20"] = -999;
    m_intVar["n_jets_truth_25"] = -999;
    m_intVar["n_jets_truth_30"] = -999;

    m_intVar["n_jets_btag60"] = -999;
    m_intVar["n_jets_btag70"] = -999;
    m_intVar["n_jets_btag77"] = -999;
    m_intVar["n_jets_btag85"] = -999;

    m_floatVar["pt4l_truth_born"]  = -999;
    m_floatArrayVar["jet_pt_truth"]    = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_eta_truth"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_phi_truth"]   = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_m_truth"]     = {{-999, -999, -999, -999}};

    ////////
    // For coupling analysis
    ////////

    m_intVar["prod_type"]                       = -999;
    m_intVar["prod_type_HM"]                    = -999;
    m_intVar["HTXS_Stage0_Category"]            = -999;
    m_intVar["HTXS_Stage1_Category_pTjet25"]    = -999;
    m_intVar["HTXS_Stage1_Category_pTjet30"]    = -999;


    //m_intVar["prod_type_w_fJVT"]                = -999;
    //m_intVar["prod_type_HM_w_fJVT"]             = -999;
    //m_floatVar["m4ljj_unconstrained"]           = -999;

    m_floatVar["BDT_OneJet_jptetadR_discriminant_fid"+str_4lsel]      = -999;
    m_floatVar["BDT_TwoJet_discriminant_fid"+str_4lsel]               = -999;
    m_floatVar["BDT_VH_noptHjj_discriminant_fid"+str_4lsel]           = -999;
    m_floatVar["BDT_1Jet_pt4l_60_fid"+str_4lsel]                      = -999;
    m_floatVar["BDT_1Jet_pt4l_120_fid"+str_4lsel]                     = -999;
    m_floatVar["BDT_1Jet_pt4l_60_120_fid"+str_4lsel]                  = -999;
    m_floatVar["BDT_VBF_TOPO_fid"+str_4lsel]                          = -999;
    m_floatVar["BDT_VBF_Rest_fid"+str_4lsel]                          = -999;
    m_floatVar["BDT_discriminant_fid"+str_4lsel]                      = -999;
    m_floatVar["KD_discriminant_fid"+str_4lsel]                       = -999;
    m_floatVar["HiggsME_fid"+str_4lsel]                               = -999;

    m_floatVar["BDT_OneJet_jptetadR_discriminant_fid"+str_truth]      = -999;
    m_floatVar["BDT_TwoJet_discriminant_fid"+str_truth]               = -999;
    m_floatVar["BDT_VH_noptHjj_discriminant_fid"+str_truth]           = -999;
    m_floatVar["BDT_1Jet_pt4l_60_fid"+str_truth]                      = -999;
    m_floatVar["BDT_1Jet_pt4l_120_fid"+str_truth]                     = -999;
    m_floatVar["BDT_1Jet_pt4l_60_120_fid"+str_truth]                  = -999;
    m_floatVar["BDT_VBF_TOPO_fid"+str_truth]                          = -999;
    m_floatVar["BDT_VBF_Rest_fid"+str_truth]                          = -999;
    m_floatVar["BDT_discriminant_fid"+str_truth]                      = -999;
    m_floatVar["KD_discriminant_fid"+str_truth]                       = -999;
    m_floatVar["HiggsME_fid"+str_truth]                               = -999;


}

void OutputTree4lInclusive::removeVar()
{
    // If systematic job, remove variables for sysJob
    if(m_sysName != ""){ removeSysVar(); }

}

void OutputTree4lInclusive::removeSysVar()
{
    m_varToRemove.push_back("Z*_lep*_*_truth_born");
    m_varToRemove.push_back("m*_truth_born");
    m_varToRemove.push_back("Z*_lep*_*_truth_matched_bare");
    m_varToRemove.push_back("m*_*_truth_matched_bare");
    m_varToRemove.push_back("pt4l_truth*");
    m_varToRemove.push_back("eta4l_truth*");
    m_varToRemove.push_back("Z*_lep*_*");
    //m_varToRemove.push_back("BDT*");
    m_varToRemove.push_back("*discriminant");
    m_varToRemove.push_back("*jet*");
}

void OutputTree4lInclusive::fillTree(OutputTreeType::OutputTreeType t_type)
{
//    if(t_type == OutputTreeType::_4mu)  m_4muTree->Fill();
//    if(t_type == OutputTreeType::_2e2mu)    m_2e2muTree->Fill();
//    if(t_type == OutputTreeType::_2mu2e)    m_2mu2eTree->Fill();
//    if(t_type == OutputTreeType::_4e)   m_4eTree->Fill();

    // Fill the inclusive tree
    m_inclTree->Fill();
}

void OutputTree4lInclusive::writeTree()
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

void OutputTree4lInclusive::setupVarsNormSys(std::vector<CP::SystematicSet> normSysList)
{
    if(m_inclTree !=0)
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


void OutputTree4lInclusive::addHistrogram()
{
        OutputTree::addHistrogram();
    m_THistVar["truthQuadType"] = new TH1F("truthQuadType" + m_sysName, "truthQuadType", 20, 0, 20);

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

}

void OutputTree4lInclusive::setLeptonType(std::string leptonType) {m_leptonType = leptonType;}
std::string OutputTree4lInclusive::getLeptonType() {return m_leptonType;}

