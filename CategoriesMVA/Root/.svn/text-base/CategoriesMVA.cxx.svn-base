#include "CategoriesMVA/CategoriesMVA.h"

#include "TMVA/Reader.h"
#include "LHAPDF/LHAPDF.h"
#include "PathResolver/PathResolver.h"

#include "xAODRootAccess/tools/ReturnCheck.h"
#include "xAODBase/IParticle.h"
#include "FourMomUtils/xAODP4Helpers.h"

#include "TRandom3.h"

/*-------------MadGraph ME calculation------------*/
#include "MadGraphME/CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_uux_epemepemuux.h"
#include "MadGraphME/ComputeMGME.h"
/*------------------------------------------------*/

//---------------------------------------------------------------------------
// toolConstructor
//---------------------------------------------------------------------------
CategoriesMVA::CategoriesMVA(const std::string& name) 
    :
        asg::AsgTool(name),
        m_isInitialized(false),    
        m_sm_hVBF_ZZ_4l_sm_uux_epemepemuux(0),
        m_dijet_invmass(0),
        m_dijet_deltaeta(0),
        m_leading_jet_pt(0),
        m_leading_jet_eta(0),
        m_subleading_jet_pt(0),
        m_pt4ljj_unconstrained(0),
        m_min_dR_jZ(0),
        m_eta_zepp_ZZ(0),
        m_dphi_4ljj(0),
        m_VBF_uux_ME(0),
        m_dRHj(0)
{
    declareProperty("MVA_Type",    m_mvaType = VBF_ICHEP2016_30GeV_BinptHjj50, "Type of MVA");
    // default values for weights is given in initialize
    declareProperty("WeightsFile", m_weightsFileName, "Weights file for MVA"); 
    declareProperty("CutValue",    m_cutValue = -999, "Cut value for MVA");

    // Fill names for MVA types
    m_mvaTypeNames.reserve(nMVA_Types);
    m_mvaTypeNames.push_back("VBF_final2011");
    m_mvaTypeNames.push_back("VH_final2011");
    m_mvaTypeNames.push_back("VBF_final2012");
    m_mvaTypeNames.push_back("VH_final2012");
    m_mvaTypeNames.push_back("VBF_ICHEP2016_30GeV_BinptHjj50");
    m_mvaTypeNames.push_back("VBF_ICHEP2016_30GeV_noptHjj");
    m_mvaTypeNames.push_back("VH_ICHEP2016_30GeV_BinptHjj50");
    m_mvaTypeNames.push_back("VH_ICHEP2016_30GeV_noptHjj");
    m_mvaTypeNames.push_back("VBF_1j_ICHEP2016");
    m_mvaTypeNames.push_back("VBF_1j_ICHEP2016_jptetadR");
    m_mvaTypeNames.push_back("VBF_TOPO_Moriond2017");
    m_mvaTypeNames.push_back("VBF_Rest_Moriond2017");
    m_mvaTypeNames.push_back("VBF_Moriond2017");
    m_mvaTypeNames.push_back("VH_Moriond2017");
    m_mvaTypeNames.push_back("VBF_1j_pT4l_0_60_Moriond2017");
    m_mvaTypeNames.push_back("VBF_1j_pT4l_0_120_Moriond2017");
    m_mvaTypeNames.push_back("VBF_1j_pT4l_60_120_Moriond2017");

}

CategoriesMVA::~CategoriesMVA()
{
    delete m_MVAreader;
}


//---------------------------------------------------------------------------
// Initialize the tool
//---------------------------------------------------------------------------
StatusCode CategoriesMVA::initialize()
{
    ATH_MSG_INFO("initialize");

    if (!m_weightsFileName.size()) {
        // Must fill weights file according to the type

        // Moriond 2017
        if (VBF_TOPO_Moriond2017 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v08/VBFTopoEnriched_Prodv08_13TeV_PtHjjBin50GeV_JetPt30GeV_BDTG.weights.xml";
        }          
        else if (VBF_Rest_Moriond2017 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v08/VBFEnriched_Prodv08_13TeV_PtHjjBin50GeV_JetPt30GeV_BDTG.weights.xml";
        }
        else if (VBF_Moriond2017 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v10/Prodv10_13TeV_PtHjjBin50GeV_JetPt30GeV_LowPt_BDTG.weights.xml";
        }         
        else if (VH_Moriond2017 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v10/VH_Had_ProdV10_BDTG.weights.xml";
        } 
        else if (VBF_1j_pT4l_0_60_Moriond2017 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v10/1jet_pt4l_smaller_60GeV.xml";
        }          
        else if (VBF_1j_pT4l_0_120_Moriond2017 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v08/1jet_pt4l_smaller_120GeV.xml";
        }  
        else if (VBF_1j_pT4l_60_120_Moriond2017 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v10/1jet_pt4l_smaller_120GeV_larger_60GeV.xml";
        }  

        // ICHEP 2016
        else if (VBF_ICHEP2016_30GeV_BinptHjj50 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v04_2016/VBFBDT_Prodv04_13TeV_PtHjjBin50GeV_JetPt30GeV_BDTG.minitree.weights.xml";
        }       
        else if (VBF_ICHEP2016_30GeV_noptHjj == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v04_2016/VBFBDT_Prodv04_13TeV_NoPtHjj_JetPt30GeV_BDTG.minitree.weights.xml";
        }
        else if (VH_ICHEP2016_30GeV_BinptHjj50 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v04_2016/VHHAD_withPtHjj_prodV04_BDTG.weights.xml";
        }       
        else if (VH_ICHEP2016_30GeV_noptHjj == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run2/Prod_v04_2016/VHHAD_prodV04_BDTG.weights.xml";
        }
        else if (VBF_1j_ICHEP2016 == m_mvaType) {
            m_weightsFileName            = "CategoriesMVA/weights_run2/v01/OneJet_Discriminant_05_05_2016.xml";
        }
        else if (VBF_1j_ICHEP2016_jptetadR == m_mvaType) {
            m_weightsFileName            = "CategoriesMVA/weights_run2/Prod_v04_2016/OneJet_Discriminant_jptetadR_2016.xml";
        }


        // Run 1
        else if (VBF_final2012 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run1/VBF_Discriminant.weights.xml";
        }
        else if (VH_final2012 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run1/HadVH_Discriminant.weights.xml";
            m_cutValue = -0.393;
        }
        else if (VBF_final2011 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run1/VBF_Discriminant_7TeV.weights.xml";
        }
        else if (VH_final2011 == m_mvaType) {
            m_weightsFileName = "CategoriesMVA/weights_run1/HadVH_Discriminant_7TeV.weights.xml";
            m_cutValue = -0.432;
        }
    }

    // Find the full path to the file
    std::string weightsFileName = PathResolver::find_calib_file (m_weightsFileName);
    if (weightsFileName == "") {
        ATH_MSG_ERROR("initialize - Unable to find weights file name for file " << m_weightsFileName);
        return StatusCode::FAILURE;
    }

    ATH_MSG_INFO("initialize - found weights file " << weightsFileName);

    // Create the MVA reader
    m_MVAreader = new TMVA::Reader( "Silent" );

    // add variables for the corresponding MVA

    if ((   (VBF_1j_pT4l_0_60_Moriond2017 == m_mvaType) || 
            (VBF_1j_pT4l_60_120_Moriond2017 == m_mvaType) 
       )) {
        m_MVAreader->AddVariable( "jet_pt[0]",         &m_leading_jet_pt );
        m_MVAreader->AddVariable( "jet_eta[0]",        &m_leading_jet_eta );
        m_MVAreader->AddVariable( "dR_jH",  &m_dRHj );

        ATH_MSG_INFO("initialize - using variables: "
                << "jet_pt[0], "
                << "jet_eta[0], "
                << "dR_jH");

    }
    else if ((VBF_1j_ICHEP2016_jptetadR == m_mvaType) || (VBF_1j_pT4l_0_120_Moriond2017 == m_mvaType)) {
        m_MVAreader->AddVariable( "leading_jet_pt",         &m_leading_jet_pt );
        m_MVAreader->AddVariable( "leading_jet_eta",        &m_leading_jet_eta );
        m_MVAreader->AddVariable( "dRHj",  &m_dRHj );

        ATH_MSG_INFO("initialize - using variables: "
                << "leading_jet_pt, "
                << "leading_jet_eta, "
                << "dRHj");

    }

    else if (VBF_ICHEP2016_30GeV_BinptHjj50 == m_mvaType) {
        m_MVAreader->AddVariable( "dijet_invmass",          &m_dijet_invmass );
        m_MVAreader->AddVariable( "dijet_deltaeta",         &m_dijet_deltaeta );
        m_MVAreader->AddVariable( "pt4ljj_unconstrained_bin_50",  &m_pt4ljj_unconstrained );
        m_MVAreader->AddVariable( "leading_jet_pt",         &m_leading_jet_pt );
        m_MVAreader->AddVariable( "subleading_jet_pt",      &m_subleading_jet_pt );
        m_MVAreader->AddVariable( "eta_zepp_ZZ",            &m_eta_zepp_ZZ );
        m_MVAreader->AddVariable( "min_dR_jZ",              &m_min_dR_jZ );

        ATH_MSG_INFO("initialize - using variables: "
                << "dijet_invmass, "     
                << "dijet_deltaeta, "    
                << "pt4ljj_unconstrained_bin_50, "    
                << "leading_jet_pt, "    
                << "subleading_jet_pt, " 
                << "eta_zepp_ZZ, "
                << "min_dR_jZ");

    }
    else if ((VBF_TOPO_Moriond2017 == m_mvaType) || (VBF_Rest_Moriond2017 == m_mvaType) || (VBF_Moriond2017 == m_mvaType)) {
        m_MVAreader->AddVariable( "dijet_invmass",          &m_dijet_invmass );
        m_MVAreader->AddVariable( "dijet_deltaeta",         &m_dijet_deltaeta );
        m_MVAreader->AddVariable( "leading_jet_pt",         &m_leading_jet_pt );
        m_MVAreader->AddVariable( "subleading_jet_pt",      &m_subleading_jet_pt );
        m_MVAreader->AddVariable( "pt4ljj_unconstrained_bin_50",  &m_pt4ljj_unconstrained );
        m_MVAreader->AddVariable( "eta_zepp_ZZ",            &m_eta_zepp_ZZ );
        m_MVAreader->AddVariable( "min_dR_jZ",              &m_min_dR_jZ );

        ATH_MSG_INFO("initialize - using variables: "
                << "dijet_invmass, "     
                << "dijet_deltaeta, "    
                << "pt4ljj_unconstrained_bin_50, "    
                << "leading_jet_pt, "    
                << "subleading_jet_pt, " 
                << "eta_zepp_ZZ, "
                << "min_dR_jZ");

    }

    else if (VBF_ICHEP2016_30GeV_noptHjj == m_mvaType) {
        m_MVAreader->AddVariable( "dijet_invmass",          &m_dijet_invmass );
        m_MVAreader->AddVariable( "dijet_deltaeta",         &m_dijet_deltaeta );
        m_MVAreader->AddVariable( "leading_jet_pt",         &m_leading_jet_pt );
        m_MVAreader->AddVariable( "subleading_jet_pt",      &m_subleading_jet_pt );
        m_MVAreader->AddVariable( "eta_zepp_ZZ",            &m_eta_zepp_ZZ );
        m_MVAreader->AddVariable( "min_dR_jZ",              &m_min_dR_jZ );

        ATH_MSG_INFO("initialize - using variables: "
                << "dijet_invmass, "     
                << "dijet_deltaeta, "    
                << "leading_jet_pt, "    
                << "subleading_jet_pt, " 
                << "eta_zepp_ZZ, "
                << "min_dR_jZ");

    }
    else if (VH_Moriond2017 == m_mvaType) {
        m_MVAreader->AddVariable( "dijet_invmass",          &m_dijet_invmass );
        m_MVAreader->AddVariable( "dijet_deltaeta",         &m_dijet_deltaeta );
        m_MVAreader->AddVariable( "jet_pt[0]",              &m_leading_jet_pt );
        m_MVAreader->AddVariable( "jet_pt[1]",              &m_subleading_jet_pt );
        m_MVAreader->AddVariable( "jet_eta[0]",             &m_leading_jet_eta );
        m_MVAreader->AddVariable( "min_dR_jZ",              &m_min_dR_jZ );
        m_MVAreader->AddVariable( "eta_zepp_ZZ",            &m_eta_zepp_ZZ );

        ATH_MSG_INFO("initialize - using variables: "
                << "dijet_invmass, "     
                << "dijet_deltaeta, "    
                << "leading_jet_pt, "    
                << "subleading_jet_pt, " 
                << "leading_jet_eta, "    
                << "min_dR_jZ, "
                << "eta_zepp_ZZ");
    }

    else if (VH_ICHEP2016_30GeV_BinptHjj50 == m_mvaType) {
        m_MVAreader->AddVariable( "dijet_invmass",          &m_dijet_invmass );
        m_MVAreader->AddVariable( "dijet_deltaeta",         &m_dijet_deltaeta );
        m_MVAreader->AddVariable( "leading_jet_pt",         &m_leading_jet_pt );
        m_MVAreader->AddVariable( "subleading_jet_pt",      &m_subleading_jet_pt );
        m_MVAreader->AddVariable( "leading_jet_eta",        &m_leading_jet_eta );
        m_MVAreader->AddVariable( "pt4ljj_unconstrained",   &m_pt4ljj_unconstrained );
        m_MVAreader->AddVariable( "min_dR_jZ",              &m_min_dR_jZ );
        m_MVAreader->AddVariable( "eta_zepp_ZZ",            &m_eta_zepp_ZZ );

        ATH_MSG_INFO("initialize - using variables: "
                << "dijet_invmass, "     
                << "dijet_deltaeta, "    
                << "leading_jet_pt, "    
                << "subleading_jet_pt, " 
                << "higgs_dijet_pt_bin_50, "    
                << "pt4ljj_unconstrained, "    
                << "min_dR_jZ, "
                << "eta_zepp_ZZ");

    }
    else if (VH_ICHEP2016_30GeV_noptHjj == m_mvaType) {
        m_MVAreader->AddVariable( "dijet_invmass",          &m_dijet_invmass );
        m_MVAreader->AddVariable( "dijet_deltaeta",         &m_dijet_deltaeta );
        m_MVAreader->AddVariable( "leading_jet_pt",         &m_leading_jet_pt );
        m_MVAreader->AddVariable( "subleading_jet_pt",      &m_subleading_jet_pt );
        m_MVAreader->AddVariable( "leading_jet_eta",        &m_leading_jet_eta );
        m_MVAreader->AddVariable( "min_dR_jZ",              &m_min_dR_jZ );
        m_MVAreader->AddVariable( "eta_zepp_ZZ",            &m_eta_zepp_ZZ );

        ATH_MSG_INFO("initialize - using variables: "
                << "dijet_invmass, "     
                << "dijet_deltaeta, "    
                << "leading_jet_pt, "    
                << "subleading_jet_pt, " 
                << "higgs_dijet_pt_bin_50, "    
                << "min_dR_jZ, "
                << "eta_zepp_ZZ");

    }
    else if (VBF_1j_ICHEP2016 == m_mvaType) {

        // Initialize MadGraph for ME calculation
        m_MVAreader->AddVariable( "leading_jet_eta"    , &m_leading_jet_eta);        
        m_MVAreader->AddVariable( "leading_jet_pt"     , &m_leading_jet_pt);
        m_MVAreader->AddVariable( "VBF_uux_ME"         , &m_VBF_uux_ME);

        ATH_MSG_INFO("initialize - using variables: "
                << "leading_jet_pt, "    
                << "leading_jet_eta, "    
                << "VBF_uux_ME");
    }
    else if (VBF_final2012 == m_mvaType || VH_final2012 == m_mvaType || VBF_final2011 == m_mvaType ||
            VH_final2011 == m_mvaType) {
        // run 1 - all use the same variables
        m_MVAreader->AddVariable( "dijet_invmass",     &m_dijet_invmass );
        m_MVAreader->AddVariable( "dijet_deltaeta",    &m_dijet_deltaeta );
        m_MVAreader->AddVariable( "leading_jet_pt",    &m_leading_jet_pt );
        m_MVAreader->AddVariable( "subleading_jet_pt", &m_subleading_jet_pt );
        m_MVAreader->AddVariable( "leading_jet_eta",   &m_leading_jet_eta );

        ATH_MSG_INFO("initialize - using variables: "
                << "dijet_invmass, "     
                << "dijet_deltaeta, "    
                << "leading_jet_pt, "    
                << "subleading_jet_pt, " 
                << "leading_jet_eta");

    }

    // book the MVA
    m_MVAreader->BookMVA( m_mvaTypeNames[m_mvaType], weightsFileName );

    ATH_MSG_INFO("initialize - booked MVA for " << m_mvaTypeNames[m_mvaType]);

    m_isInitialized = true;

    return StatusCode::SUCCESS;
}


StatusCode
CategoriesMVA::applyMVA(const std::vector<const xAOD::IParticle*>& leptons,
        const std::vector<const xAOD::IParticle*>& jets,
        float& resultBDT,
        float& resultME,
        bool&  passesCut) const
{
    if (!m_isInitialized) {
        ATH_MSG_ERROR("applyMVA - tool is NOT initialized ");
        return StatusCode::FAILURE;
    }

    // Set default values:
    resultBDT = -999;
    resultME  = -999;
    passesCut = true;

    // Set up values and evaluate the ME and BDT

    if (VBF_ICHEP2016_30GeV_BinptHjj50 == m_mvaType || VBF_ICHEP2016_30GeV_noptHjj == m_mvaType
            || (VBF_TOPO_Moriond2017 == m_mvaType) || (VBF_Rest_Moriond2017 == m_mvaType)
            || (VBF_Moriond2017 == m_mvaType)
            ) {
        if (leptons.size() != 4) {
            ATH_MSG_ERROR("applyMVA - must provide four leptons for " << m_mvaTypeNames[m_mvaType] <<
                    ". Found:  " << leptons.size());
            return StatusCode::FAILURE;
        }
        if (jets.size() < 2) {
            ATH_MSG_ERROR("applyMVA - must provide at least two jets for " << m_mvaTypeNames[m_mvaType]
                    << ". Found:  " << jets.size());
            return StatusCode::FAILURE;
        }
        TLorentzVector dijet   = jets[0]->p4() + jets[1]->p4();
        TLorentzVector higgs   = leptons[0]->p4() + leptons[1]->p4() + leptons[2]->p4() + leptons[3]->p4();
        m_dijet_invmass        = dijet.M()*0.001;
        m_dijet_deltaeta       = fabs(jets[0]->eta() - jets[1]->eta());
        m_leading_jet_pt       = jets[0]->pt()*0.001;
        m_subleading_jet_pt    = jets[1]->pt()*0.001;
        m_pt4ljj_unconstrained = (higgs + dijet).Pt()*0.001;
        // Binned at 50 GeV
        if(m_pt4ljj_unconstrained < 50) m_pt4ljj_unconstrained = 50;
        m_min_dR_jZ            = computeMinDeltaR(leptons, jets);
        m_eta_zepp_ZZ          = fabs(higgs.Eta() - ((jets[0]->eta() + jets[1]->eta())/2));

        if (m_leading_jet_pt < m_subleading_jet_pt) {
            ATH_MSG_WARNING("applyMVA: leading jet pt is LT subleading jet pt: leading_jet_pt "
                    << m_leading_jet_pt << " subleading_jet_pt " << m_subleading_jet_pt);
            ATH_MSG_WARNING("applyMVA: Please order jets in decreasing pt ");
        }

        ATH_MSG_DEBUG("applyMVA: dijet_invmass " << m_dijet_invmass << " dijet_deltaeta " << m_dijet_deltaeta
                << " leading_jet_pt " << m_leading_jet_pt << " subleading_jet_pt " << m_subleading_jet_pt
                << " pt4ljj_unconstrained " << m_pt4ljj_unconstrained << " min_dR_jZ " << m_min_dR_jZ
                << " eta_zepp_ZZ " << m_eta_zepp_ZZ);

        resultBDT = m_MVAreader->EvaluateMVA( m_mvaTypeNames[m_mvaType] );
    }
    else if (VH_ICHEP2016_30GeV_BinptHjj50 == m_mvaType || VH_ICHEP2016_30GeV_noptHjj == m_mvaType || VH_Moriond2017 == m_mvaType ) {
        if (leptons.size() != 4) {
            ATH_MSG_ERROR("applyMVA - must provide four leptons for " << m_mvaTypeNames[m_mvaType] <<
                    ". Found:  " << leptons.size());
            return StatusCode::FAILURE;
        }
        if (jets.size() < 2) {
            ATH_MSG_ERROR("applyMVA - must provide at least two jets for " << m_mvaTypeNames[m_mvaType]
                    << ". Found:  " << jets.size());
            return StatusCode::FAILURE;
        }
        TLorentzVector dijet   = jets[0]->p4() + jets[1]->p4();
        TLorentzVector higgs   = leptons[0]->p4() + leptons[1]->p4() + leptons[2]->p4() + leptons[3]->p4();
        m_dijet_invmass        = dijet.M()*0.001;
        m_dijet_deltaeta       = fabs(jets[0]->eta() - jets[1]->eta());
        m_leading_jet_pt       = jets[0]->pt()*0.001;
        m_leading_jet_eta        = jets[0]->eta();
        m_subleading_jet_pt    = jets[1]->pt()*0.001;
        m_pt4ljj_unconstrained = (higgs + dijet).Pt()*0.001;
        // Binned at 50 GeV
        if(m_pt4ljj_unconstrained < 50) m_pt4ljj_unconstrained = 50;
        m_min_dR_jZ            = computeMinDeltaR(leptons, jets);
        m_eta_zepp_ZZ          = fabs(higgs.Eta() - ((jets[0]->eta() + jets[1]->eta())/2));

        if (m_leading_jet_pt < m_subleading_jet_pt) {
            ATH_MSG_WARNING("applyMVA: leading jet pt is LT subleading jet pt: leading_jet_pt "
                    << m_leading_jet_pt << " subleading_jet_pt " << m_subleading_jet_pt);
            ATH_MSG_WARNING("applyMVA: Please order jets in decreasing pt ");
        }

        ATH_MSG_DEBUG("applyMVA: dijet_invmass " << m_dijet_invmass << " dijet_deltaeta " << m_dijet_deltaeta
                << " leading_jet_pt " << m_leading_jet_pt << " subleading_jet_pt " << m_subleading_jet_pt
                << " leading_jet_eta " << m_leading_jet_eta 
                << " pt4ljj_unconstrained " << m_pt4ljj_unconstrained << " min_dR_jZ " << m_min_dR_jZ
                << " eta_zepp_ZZ " << m_eta_zepp_ZZ);

        resultBDT = m_MVAreader->EvaluateMVA( m_mvaTypeNames[m_mvaType] );
    }

    else if ((VBF_1j_ICHEP2016_jptetadR == m_mvaType) ||
            (VBF_1j_pT4l_0_60_Moriond2017 == m_mvaType) || 
            (VBF_1j_pT4l_0_120_Moriond2017 == m_mvaType) || 
            (VBF_1j_pT4l_60_120_Moriond2017 == m_mvaType) 
            )
    {
        if (leptons.size() != 4) {
            ATH_MSG_ERROR("applyMVA - must provide four leptons for " << m_mvaTypeNames[m_mvaType] <<
                    ". Found:  " << leptons.size());
            return StatusCode::FAILURE;
        }
        if (jets.size() < 1) {
            ATH_MSG_ERROR("applyMVA - must provide at least one jet for " << m_mvaTypeNames[m_mvaType]
                    << ". Found:  " << jets.size());
            return StatusCode::FAILURE;
        }
        TLorentzVector jet   = jets[0]->p4();
        TLorentzVector higgs   = leptons[0]->p4() + leptons[1]->p4() + leptons[2]->p4() + leptons[3]->p4();
        float dphiHj = jet.Phi()-higgs.Phi();
        float detaHj = jet.Eta()-higgs.Eta();
        // TODO: buggy definition used in the old file - fix it when the new one is here
        if(VBF_1j_ICHEP2016_jptetadR == m_mvaType)m_dRHj = sqrt(dphiHj*dphiHj+detaHj*detaHj);
        else  m_dRHj = higgs.DeltaR(jet);

        m_leading_jet_pt    = jets[0]->pt()*0.001;
        m_leading_jet_eta    = jets[0]->eta();
        if (m_leading_jet_pt < 0) {
            ATH_MSG_WARNING("applyMVA: jet pt less than zero");
        }

        ATH_MSG_DEBUG("applyMVA: leading_jet_pt " << m_leading_jet_pt << " leading_jet_eta " << m_leading_jet_eta
                << " dRHj " << m_dRHj);

        resultBDT = m_MVAreader->EvaluateMVA( m_mvaTypeNames[m_mvaType] );
    }

    else if (VBF_1j_ICHEP2016 == m_mvaType) {
        if (leptons.size() != 4) {
            ATH_MSG_ERROR("applyMVA - must provide four leptons for " << m_mvaTypeNames[m_mvaType] <<
                    ". Found:  " << leptons.size());
            return StatusCode::FAILURE;
        }
        if (jets.size() != 1) {
            ATH_MSG_ERROR("applyMVA - must provide ONLY ONE jet for " << m_mvaTypeNames[m_mvaType]
                    << ". Found:  " << jets.size());
            return StatusCode::FAILURE;
        }

        RETURN_CHECK( "applyMVA", getVBF_ME(leptons, jets, m_VBF_uux_ME));

        // save for BDT
        m_leading_jet_pt     = jets[0]->pt()*0.001;
        m_leading_jet_eta    = jets[0]->eta();


        ATH_MSG_DEBUG("applyMVA - leading jet pt, eta, vec, cms4ljj, cms4l "
                << m_leading_jet_pt << "/" << m_leading_jet_eta);

        ATH_MSG_DEBUG("applyMVA: leading_jet_pt " << m_leading_jet_pt << " leading_jet_eta " << m_leading_jet_eta
                << " VBF_uux_ME " << m_VBF_uux_ME);

        resultBDT = m_MVAreader->EvaluateMVA( m_mvaTypeNames[m_mvaType] );
        resultME  = m_VBF_uux_ME;

        ATH_MSG_DEBUG("applyMVA: leading_jet_pt " << m_leading_jet_pt << " leading_jet_eta " << m_leading_jet_eta
                << " VBF_uux_ME " << m_VBF_uux_ME << " BDT out " << resultBDT);
    }
    else if (VBF_final2012 == m_mvaType || VH_final2012 == m_mvaType || VBF_final2011 == m_mvaType ||
            VH_final2011 == m_mvaType) {
        if (jets.size() < 2) {
            ATH_MSG_ERROR("applyMVA - must provide at least two jets for " << m_mvaTypeNames[m_mvaType]
                    << ". Found:  " << jets.size());
            return StatusCode::FAILURE;
        }
        // run 1 - all use the same variables
        TLorentzVector dijet = jets[0]->p4() + jets[1]->p4();
        m_dijet_invmass      = dijet.M();
        m_dijet_deltaeta     = fabs(jets[0]->eta() - jets[1]->eta());
        m_leading_jet_pt     = jets[0]->pt();
        m_subleading_jet_pt  = jets[1]->pt();
        m_leading_jet_eta    = jets[0]->eta();

        ATH_MSG_DEBUG("applyMVA: dijet_invmass " << m_dijet_invmass << " dijet_deltaeta " << m_dijet_deltaeta
                << " leading_jet_pt " << m_leading_jet_pt << " subleading_jet_pt " << m_subleading_jet_pt
                << " leading_jet_eta " << m_leading_jet_eta);

        resultBDT = m_MVAreader->EvaluateMVA( m_mvaTypeNames[m_mvaType] );
        if (VH_final2012 == m_mvaType || VH_final2011 == m_mvaType) passesCut =  resultBDT > m_cutValue;
    }
    else
    {
        ATH_MSG_ERROR("applyMVA - Type not recognized: "+m_mvaTypeNames[m_mvaType] );
        return StatusCode::FAILURE;
    }

    ATH_MSG_DEBUG("applyMVA: resultBDT, resultME, passesCut " << resultBDT << "/" << resultME << "/" << passesCut);
    return StatusCode::SUCCESS;
}

StatusCode
CategoriesMVA::getVBF_ME(const std::vector<const xAOD::IParticle*>& leptons,
        const std::vector<const xAOD::IParticle*>& jets,
        float& resultME) const
{

    // Set default values:
    resultME  = -999;

    if (leptons.size() != 4) {
        ATH_MSG_ERROR("getVBF_ME - must provide four leptons " <<
                ". Found:  " << leptons.size());
        return StatusCode::FAILURE;
    }
    if (jets.size() != 1 && jets.size() != 2) {
        ATH_MSG_ERROR("getVBF_ME - must provide ONLY ONE or TWO jet "
                << ". Found:  " << jets.size());
        return StatusCode::FAILURE;
    }

    // For MadGraph, save vector of all six particles - 4l,jj and four-vector of 4l (cms4l) and
    //   4ljj (cms4ljj) - all must be in GeV
    std::vector<TLorentzVector> fourVecs4ljj;
    TLorentzVector cms4ljj;
    TLorentzVector cms4l;
    fourVecs4ljj.reserve(6);
    for ( auto part : leptons ) {
        fourVecs4ljj.push_back(toGeV(part->p4()));
        cms4l += part->p4();
    }

    TLorentzVector second_jet;

    // If one jet, create the other one
    if(jets.size() == 1)
    {
        // Fabricate a virtual second jet with pt = 23 GeV and opposite in eta/phi from the leading jet
        // if no other jet is found
        // Generate a random phi for the virtual jet
        TRandom3 f1;
        // Seed for allowing a comparisions
        f1.SetSeed(std::abs(jets[0]->p4().Phi()) * 1E6 + std::abs(jets[0]->p4().Eta()) * 1E3);
        float rnd = f1.Uniform(1);
        float newPhi = -TMath::Pi() + (float)rnd*2.*TMath::Pi();
        if ( newPhi > M_PI ) newPhi = newPhi - 2 * M_PI;

        // Eta is set to +- 3.3
        float newEta = (jets[0]->p4().Eta() > 0) ? -3.3 : 3.3;
        float newpT = 23;
        // Calculate the energy based on angles
        float newE = newpT*TMath::CosH(newEta);
        second_jet.SetPtEtaPhiE(newpT, newEta, newPhi, newE); // virt_jet is already in GeV
        ATH_MSG_DEBUG("getVBF_ME - newpT, newEta, newPhi " << newpT << "/" << newEta << "/" << newPhi);

    }
    else
    {
        second_jet = toGeV(jets[1]->p4());
    }



    fourVecs4ljj.push_back(toGeV(jets[0]->p4()));
    fourVecs4ljj.push_back( second_jet );

    cms4ljj = cms4l + jets[0]->p4();
    cms4l   = toGeV(cms4l);   // go to GeV
    cms4ljj = toGeV(cms4ljj); // go to GeV
    cms4ljj += second_jet;


    if (!m_sm_hVBF_ZZ_4l_sm_uux_epemepemuux) {
        // Get MadGraph card file
        std::string madGraphCardFile;
        madGraphCardFile = PathResolver::find_calib_file ("MadGraphME/param_card_PROC_SA_CPP_sm_hVBF_ZZ_4l.dat");
        if (madGraphCardFile == "") {
            ATH_MSG_ERROR("initialize - Unable to find MadGraph file name for file " << m_madgraphVBFCardFileName);
            return StatusCode::FAILURE;
        }
        ATH_MSG_INFO("getVBF_ME: Initializing tool for Madgraph ME");
        m_sm_hVBF_ZZ_4l_sm_uux_epemepemuux = new CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_uux_epemepemuux();
        m_sm_hVBF_ZZ_4l_sm_uux_epemepemuux->initProc(madGraphCardFile);

        // LHA PDF
        LHAPDF::setVerbosity(LHAPDF::LOWKEY);
        LHAPDF::setPDFPath("/cvmfs/sft.cern.ch/lcg/external/lhapdfsets/current/");

        m_ct10PDF = LHAPDF::mkPDF("CT10nlo",0);
    }

    // ATH_MSG_INFO("getVBF_ME: after Madgraph init");

    // Calculate the ME
    resultME = getMEFromVec(ComputeMGME_cmsM4l(*m_sm_hVBF_ZZ_4l_sm_uux_epemepemuux,
                fourVecs4ljj, cms4ljj, cms4l)); 


    // To calculate the PDF weight
    double x1   = -999;
    double x2   = -999;
    double qsqr = -999;

    // Assume that the intial parton energy is half of the CMS and equally divided between the two.
    // X = half of CMS E [already in GeV] / Beam energy
    x1 = (cms4ljj.E()) / (2 * 6.5*1000);
    x2 = (cms4ljj.E()) / (2 * 6.5*1000);

    // Assuming that parton have opposite momementum
    qsqr = cms4ljj.M() * cms4ljj.M();

    if(x1 > 1 || x2 > 1)
    {
        resultME  = -999;
        ATH_MSG_WARNING("getVBF_ME - x > 1 for this event - x1 : "<<x1<<" x2: "<<x2);
        return StatusCode::FAILURE;
    }

    double u_pdf = m_ct10PDF->xfxQ2(1, x1, qsqr) * m_ct10PDF->xfxQ2(1, x2, qsqr);

    // Add the 
    resultME += log(u_pdf);

    ATH_MSG_DEBUG("getVBF_ME: resultME " << "/" << resultME );
    return StatusCode::SUCCESS;
}

float
CategoriesMVA::computeMinDeltaR(const std::vector<const xAOD::IParticle*>& leptons,
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

float
CategoriesMVA::getMEFromVec(const std::vector<float>& ME) const
{
    float sum = 0.;
    for ( auto me : ME ) sum += me;
    sum = log(sum);
    return sum;
}

const TLorentzVector&
CategoriesMVA::toGeV(const TLorentzVector& tlv) const
{
    static TLorentzVector out;
    out.SetPtEtaPhiE(tlv.Pt()*0.001, tlv.Eta(), tlv.Phi(), tlv.E()*0.001);
    return out;
}

std::string
CategoriesMVA::typeName() const
{
    return m_mvaTypeNames[m_mvaType];
}
