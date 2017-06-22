#include "H4lCutFlow/OutputTree3l.h"
using namespace std;

OutputTree3l::OutputTree3l(TString outName, TString sysName, TString sampleName)
:OutputTree(outName, sysName, sampleName)
{
    m_ZplusMuTree = 0;
    m_ZplusElTree = 0;
    
    m_isNormSys = false;
}

void OutputTree3l::initialize()
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
    
    m_ZplusMuTree    = new TTree("tree_ZplusMu", "all");
    m_ZplusMuTree->SetAutoFlush();
    bookTree(m_ZplusMuTree);
    
    m_ZplusElTree    = new TTree("tree_ZplusEl", "all");
    m_ZplusElTree->SetAutoFlush();
    bookTree(m_ZplusElTree);

    initMetaData();    
}



OutputTree3l::~OutputTree3l()
{
    output->Close();
    delete output;

//    For some reason deleting the ttrees, create a seg fault..
//    Is there a transfer of ownership when we write a ttree?
    
//    Deleting all the trees
//    delete m_relaxElElTree;
    
}

// Intial decleration of the variables
void OutputTree3l::addVar()
{
    m_intVar["run"] = -999;
    //m_intVar["random_run"] = -999;
    m_intLongVar["event"]   = -999;
    //m_intLongVar["PRWHash"] = -999;    
    m_intVar["lbn"] = -999;
    m_intVar["npv"] = -999;
        // Index 
    m_intVar["cand_index"] = -999;
   
    m_intVar["event_type"] = -999;
    //m_intVar["prod_type"] = -999;
    m_intVar["GRLisOK"] = -999;
    
    m_float3ArrayVar["lepton_pt"]    = {{-999, -999, -999}};
    m_float3ArrayVar["lepton_eta"]   = {{-999, -999, -999}};
    m_float3ArrayVar["lepton_phi"]   = {{-999, -999, -999}};
    m_float3ArrayVar["lepton_m"]     = {{-999, -999, -999}};
    m_int3ArrayVar["lepton_id"]      = {{-999, -999, -999}};
    m_float3ArrayVar["lepton_res"]   = {{-999, -999, -999}};
    
    m_floatVar["mZ_unconstrained"]      = -999;
    m_floatVar["mZ_constrained"]        = -999;
    //m_floatVar["m3l_unconstrained"]     = -999;
    //m_floatVar["pt3l_unconstrained"]    = -999;
    //m_floatVar["eta3l_unconstrained"]   = -999;
    //m_floatVar["y3l_unconstrained"]     = -999;
    

    // Bkg vars
    // common for all leptons
    //m_int3ArrayVar["lepton_quality"]     = {{-999, -999, -999}};
    m_int3ArrayVar["lepton_charge"]      = {{-999, -999, -999}};
    m_float3ArrayVar["lepton_d0sig"]     = {{-999, -999, -999}};
    m_int3ArrayVar["lepton_passD0sig"]   = {{-999, -999, -999}};
    m_int3ArrayVar["lepton_passIsoCut"]  = {{-999, -999, -999}};
    m_float3ArrayVar["lepton_ptvarcone30"]     = {{-999, -999, -999}};
    m_float3ArrayVar["lepton_ptvarcone20"]     = {{-999, -999, -999}};
    m_float3ArrayVar["lepton_topoetcone20"]    = {{-999, -999, -999}};
    
    
    // el specific
    //m_int3ArrayVar["el_recoClass"]   = {{-999, -999, -999}};
    m_int3ArrayVar["el_MCClass"]     = {{-999, -999, -999}};
    //m_float3ArrayVar["el_Rphi"]      = {{-999, -999, -999}};
    //m_float3ArrayVar["el_Reta"]      = {{-999, -999, -999}};
    //m_float3ArrayVar["el_f1"]        = {{-999, -999, -999}};
    m_float3ArrayVar["el_Deta1"]     = {{-999, -999, -999}};
    m_int3ArrayVar["el_nInnerExpPix"]= {{-999, -999, -999}}; // Actually used in the fit
    //m_int3ArrayVar["el_nBL"]         = {{-999, -999, -999}};
    //m_int3ArrayVar["el_nPix"]        = {{-999, -999, -999}};
    //m_int3ArrayVar["el_nSCT"]        = {{-999, -999, -999}};
    //m_float3ArrayVar["el_rTRT"]      = {{-999, -999, -999}};
    m_float3ArrayVar["el_eProbHT"]   = {{-999, -999, -999}};
    //m_float3ArrayVar["el_eOverP"]    = {{-999, -999, -999}};
    //m_float3ArrayVar["el_expInner"]          = {{-999, -999, -999}};
    //m_float3ArrayVar["el_expNextToInner"]    = {{-999, -999, -999}};
    //m_float3ArrayVar["el_nInner"]            = {{-999, -999, -999}};
    //m_float3ArrayVar["el_nNextToInner"]      = {{-999, -999, -999}};
 
    // mu specific
    m_int3ArrayVar["mu_MCPartType"]     = {{-999, -999, -999}};
    m_int3ArrayVar["mu_MCOriginType"]   = {{-999, -999, -999}};
    m_float3ArrayVar["mu_IDpt"]      = {{-999, -999, -999}};
    m_float3ArrayVar["mu_MSpt"]      = {{-999, -999, -999}};
    m_float3ArrayVar["mu_qOverPsig"]      = {{-999, -999, -999}};
    //m_int3ArrayVar["mu_author"]      = {{-999, -999, -999}};
    m_int3ArrayVar["mu_type"]        = {{-999, -999, -999}};
    m_int3ArrayVar["mu_nInnerExpPix"]        = {{-999, -999, -999}};
    //m_int3ArrayVar["mu_NPrecLayer"]  = {{-999, -999, -999}};
   
    // MET var
    //m_floatVar["met_et"]      = -999;
    //m_floatVar["met_sum_et"]      = -999;
    //m_floatVar["met_phi"]      = -999;
    
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
    
    m_intVar["n_jets"] = -999;
    m_floatVar["dijet_invmass"]     = -999;
    m_floatVar["dijet_deltaeta"]    = -999;
    m_floatArrayVar["jet_pt"]       = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_eta"]      = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_phi"]      = {{-999, -999, -999, -999}};
    m_floatArrayVar["jet_m"]        = {{-999, -999, -999, -999}};
    m_intVar["n_jets_btag60"] = -999;
    m_intVar["n_jets_btag70"] = -999;
    m_intVar["n_jets_btag77"] = -999;
    m_intVar["n_jets_btag85"] = -999;
}

void OutputTree3l::removeVar()
{
    // If systematic job, remove variables for sysJob
    if(m_sysName != ""){ removeSysVar(); }

    if(m_isMC)
    {
        if(!((m_runNumber >= 363103 && m_runNumber <= 363411)))
        {
            m_varToRemove.push_back("w_sherpaJet");
        }
        m_varToRemove.push_back("GRLisOK");
    }

    // if data
    if(!m_isMC)
    {
        m_varToRemove.push_back("w_sherpaJet");
        m_varToRemove.push_back("w_sherpaLep");
        m_varToRemove.push_back("*truth*");
        m_varToRemove.push_back("w_*");
        m_varToRemove.push_back("PRWHash");
        m_varToRemove.push_back("weight_*");
        m_varToRemove.push_back("random_run");
    }

}
void OutputTree3l::addDataSpecificVar()
{
    m_stringVar["file_name"] = "";
    m_stringVar["sample_name"] = "";
}



void OutputTree3l::removeSysVar()
{
    m_varToRemove.push_back("Z*_lep*_*_truth_born");
    m_varToRemove.push_back("m*_truth_born");
    m_varToRemove.push_back("Z*_lep*_*_truth_matched_bare");
    m_varToRemove.push_back("m*_*_truth_matched_bare");
    m_varToRemove.push_back("pt4l_truth*");
    m_varToRemove.push_back("eta4l_truth*");
    m_varToRemove.push_back("Z*_lep*_*");
    m_varToRemove.push_back("BDT*");
    m_varToRemove.push_back("*discriminant");
    m_varToRemove.push_back("*jet*");
}


void OutputTree3l::fillTree(OutputTreeType::OutputTreeType type)
{
    if (type == OutputTreeType::ZplusMu) m_ZplusMuTree->Fill();
    else if (type == OutputTreeType::ZplusEl) m_ZplusElTree->Fill();
    else
    {
        LOG(logERROR)<<"OutputTree3l::fillTree - input tree type not supported";
        LOG(logERROR)<<"Type: "<<type;
    }
    
}

void OutputTree3l::writeTree()
{

    output->cd();
    m_ZplusMuTree->Write();
    m_ZplusElTree->Write();

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

void OutputTree3l::setupVarsNormSys(std::vector<CP::SystematicSet> normSysList)
{
    if(m_ZplusMuTree !=0)
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


void OutputTree3l::addHistrogram()
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



