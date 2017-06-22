//--------------------------------------------------------------------------------
// Authors: R. Di Nardo   <Roberto.Di.Nardo@cern.ch>
//          E. Mountricha <Eleni.Mountricha@cern.ch>
//          S. Haider Abidi <sabidi@cern.ch>
//--------------------------------------------------------------------------------
#include <stdlib.h>
#include "H4lBDTWeights/H4lBDTWeights.h"
#include "xAODTruth/TruthParticleContainer.h"

/*-------------MadGraph ME calculation------------*/
#include "MadGraphME/CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemepem.h"
#include "MadGraphME/CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemmupmum.h"
#include "MadGraphME/CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemepem.h"
#include "MadGraphME/CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemmupmum.h"
#include "MadGraphME/CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemepem.h"
#include "MadGraphME/CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemmupmum.h"
#include "MadGraphME/ComputeMGME.h"
/*------------------------------------------------*/

#ifndef ROOTCORE
#include "PathResolver/PathResolver.h"
#endif

#include <TFile.h>
#include <TH1D.h>
#include <iostream>
#include <string>
#include "TSystem.h"


////////////////////////////////////////////////////////////////////////////////////////
//                              Constructor and Destructor
////////////////////////////////////////////////////////////////////////////////////////
H4lBDTWeights::H4lBDTWeights (const std::string& name):
	asg::AsgTool(name),
	m_bdtType(-1)
{
	declareProperty( "BDTtype", m_bdtType = v03_Moriond2017_prodV10);
}
H4lBDTWeights::~H4lBDTWeights(void)
{
	delete m_reader;
	delete m_theHptSysTool;
	delete m_S_heft_gg_4l_SF;
	delete m_S_heft_gg_4l_DF;
	delete m_S_sm_pp_4l_uu_SF;
	delete m_S_sm_pp_4l_uu_DF;
	delete m_S_sm_pp_4l_dd_SF;
	delete m_S_sm_pp_4l_dd_DF;
}

StatusCode H4lBDTWeights::initialize()
{
	if(m_bdtType == -1)
	{
		ATH_MSG_ERROR("BDTtype not set");
		return StatusCode::FAILURE;
	}

	// Intializing the TMVA reader
	ATH_MSG_INFO("Initializing the TMVA reader");
	m_reader = new TMVA::Reader( "silent" );

	// Adding the vars
    m_reader->AddVariable( "pt4l_fsr"                , &m_pt4l   );        
    m_reader->AddVariable( "eta4l_unconstrained"     , &m_eta4l_unconstrained  );
    m_reader->AddVariable( "KD_discriminant"         , &m_KD_discriminant      );
    


    m_pathToWeight = PathResolver::find_directory ("H4lBDTWeights", "CALIBPATH") + "/";
    m_pathToMadGraphFiles = PathResolver::find_directory ("MadGraphME", "CALIBPATH") + "/";

	TString folderName = "";

    // Run 1
		 if (m_bdtType == final2012) folderName = "Run1/minitreeV01_1_withoutTau";
	else if (m_bdtType == final2011) folderName = "Run1/minitreeV02_2011";
    TString _4lFile = "H4lBDTWeights/" + folderName + "/weights_4e_4mu/TMVA_training_BDTG.weights.xml";
    TString _2l2lFile = "H4lBDTWeights/" + folderName + "/weights_2e2mu_2mu2e/TMVA_training_BDTG.weights.xml";

    // Run 2
    if(m_bdtType == v04_Moriond2017_prodV12)
    {
        folderName = "Run2/v04_prodV12/";
        _4lFile = "H4lBDTWeights/" + folderName + "/TMVAClassification_BDTG_4.weights.xml";
        _2l2lFile = "H4lBDTWeights/" + folderName + "/TMVAClassification_BDTG_2.weights.xml";
    }
    else if(m_bdtType == v03_Moriond2017_prodV10)
    {
        folderName = "Run2/v03_prodV11/";
        _4lFile = "H4lBDTWeights/" + folderName + "/TMVAClassification_BDTG_4.weights.xml";
        _2l2lFile = "H4lBDTWeights/" + folderName + "/TMVAClassification_BDTG_2.weights.xml";
    }
    else if(m_bdtType == v02_ICHEP16_prodV4)
    {
        folderName = "Run2/v02_prodV04/";
        _4lFile = "H4lBDTWeights/" + folderName + "/TMVAClassification_BDTG_4.weights.xml";
        _2l2lFile = "H4lBDTWeights/" + folderName + "/TMVAClassification_BDTG_2.weights.xml";
    }
    else if(m_bdtType == v01_2015)
    {
        folderName = "Run2/v01";
        _4lFile = "H4lBDTWeights/" + folderName + "/TMVAClassification_BDTG_4.weights.xml";
        _2l2lFile = "H4lBDTWeights/" + folderName + "/TMVAClassification_BDTG_2.weights.xml";
    }


    TString file4l = PathResolver::find_file (_4lFile.Data(), "CALIBPATH");
    TString file2l2l = PathResolver::find_file (_2l2lFile.Data(), "CALIBPATH");
	ATH_MSG_INFO("BDT Looking for 4l file:"+_4lFile);
	ATH_MSG_INFO("BDT Looking for 2l2l file:"+_2l2lFile);


	ATH_MSG_INFO("BDT 4l file:"+file4l);
	ATH_MSG_INFO("BDT 2l2l file:"+file2l2l);
    
	m_reader->BookMVA( "BDTG_4e_4mu"         ,  file4l   );
	m_reader->BookMVA( "BDTG_2e2mu_2mu2e"    ,  file2l2l  );

	ATH_MSG_DEBUG("Initializing tool for pt Sys");
	// For pt Systematics
    TString fileHPtSysTool = PathResolver::find_file ("H4lBDTWeights/Run1/HPtSysTool/ScaleHist.root", "CALIBPATH");
	m_theHptSysTool = new HPtSysTool(fileHPtSysTool);

	ATH_MSG_DEBUG("Initializing tool for gaussianization");

	//For the gaussianization , read cumulative distributions
    TString filegauss = PathResolver::find_file ("H4lBDTWeights/Run1/gaussFile/cumul.root", "CALIBPATH");
	ATH_MSG_DEBUG("Gauss file:"+filegauss);

	m_thecumul         = new TFile(filegauss, "READ");
	m_comb_cumul_4mu   = (TH1D*) m_thecumul->Get("comb_cumul_4mu");
	m_comb_cumul_4e    = (TH1D*) m_thecumul->Get("comb_cumul_4e");
	m_comb_cumul_2e2mu = (TH1D*) m_thecumul->Get("comb_cumul_2e2mu");
	m_comb_cumul_2mu2e = (TH1D*) m_thecumul->Get("comb_cumul_2mu2e");


	m_S_heft_gg_4l_SF  = new CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemepem;   
	m_S_heft_gg_4l_DF  = new CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemmupmum; 
	m_S_sm_pp_4l_uu_SF = new CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemepem;           
	m_S_sm_pp_4l_uu_DF = new CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemmupmum;         
	m_S_sm_pp_4l_dd_SF = new CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemepem;           
	m_S_sm_pp_4l_dd_DF = new CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemmupmum;         


	ATH_MSG_DEBUG("Initializing tool for Madgraph ME");
    TString t_cardZZ = PathResolver::find_file ("MadGraphME/param_card_PROC_SA_CPP_heft_pp_H_ZZ_4l.dat", "CALIBPATH");
	//TString t_cardZZ = m_pathToMadGraphFiles + "/param_card_PROC_SA_CPP_heft_pp_H_ZZ_4l.dat";
	string cardZZ = t_cardZZ.Data();
	m_S_heft_gg_4l_SF->initProc(cardZZ);
	m_S_heft_gg_4l_DF->initProc(cardZZ);

	//TString t_card4l = m_pathToMadGraphFiles + "/param_card_PROC_SA_CPP_sm_pp_4l.dat";
    TString t_card4l = PathResolver::find_file ("MadGraphME/param_card_PROC_SA_CPP_sm_pp_4l.dat", "CALIBPATH");
    string card4l    = t_card4l.Data();

	m_S_sm_pp_4l_uu_SF->initProc(card4l);
	m_S_sm_pp_4l_uu_DF->initProc(card4l);
	m_S_sm_pp_4l_dd_SF->initProc(card4l);
	m_S_sm_pp_4l_dd_DF->initProc(card4l);

	ATH_MSG_INFO("Tool ready");
	

	return StatusCode::SUCCESS;

}


////////////////////////////
// To get input from the user
////////////////////////////
// all inputs in MeV
void H4lBDTWeights::setBDTInputs(const xAOD::IParticle* Z1LepPlus,
		const xAOD::IParticle* Z1LepMinus,
		const xAOD::IParticle* Z2LepPlus,
		const xAOD::IParticle* Z2LepMinus,
		float pt4l_fsr,
		float pt4l_truth_born,             
		bool isggH12)
{    

	m_Z1LepPlus            = (*Z1LepPlus).p4();
	m_Z1LepMinus           = (*Z1LepMinus).p4();
	m_Z2LepPlus            = (*Z2LepPlus).p4();
	m_Z2LepMinus           = (*Z2LepMinus).p4();
	m_pt4l_truth_born      = pt4l_truth_born/1000;
	m_isggH12              = isggH12;

	// setting the TLV to GeV
	m_Z1LepPlus.SetPtEtaPhiE (m_Z1LepPlus.Pt()*0.001,  m_Z1LepPlus.Eta(),  m_Z1LepPlus.Phi(),  m_Z1LepPlus.E()*0.001);
	m_Z1LepMinus.SetPtEtaPhiE(m_Z1LepMinus.Pt()*0.001, m_Z1LepMinus.Eta(), m_Z1LepMinus.Phi(), m_Z1LepMinus.E()*0.001);

	m_Z2LepPlus.SetPtEtaPhiE (m_Z2LepPlus.Pt()*0.001,  m_Z2LepPlus.Eta(),  m_Z2LepPlus.Phi(),  m_Z2LepPlus.E()*0.001);
	m_Z2LepMinus.SetPtEtaPhiE(m_Z2LepMinus.Pt()*0.001, m_Z2LepMinus.Eta(), m_Z2LepMinus.Phi(), m_Z2LepMinus.E()*0.001);

	// Getting the quad flavour
	
	// Sanity check
	if((Z1LepPlus->type() != Z1LepMinus->type())
			|| (Z2LepPlus->type() != Z2LepMinus->type()))
	{
		ATH_MSG_ERROR("The particle type for dilepton pairs do not match");
		exit(-1);
	}

	// getting the flavour 
	if(Z1LepPlus->type() == xAOD::Type::Muon)
	{
		if(Z2LepPlus->type() == xAOD::Type::Muon){m_quadType = _4mu;}
		else {m_quadType = _2mu2e;}
	}
	else if(Z1LepPlus->type() == xAOD::Type::Electron)
	{
		if(Z2LepPlus->type() == xAOD::Type::Muon){m_quadType = _2e2mu;}
		else {m_quadType = _4e;}
	}
    else if(Z1LepPlus->type() == xAOD::Type::TruthParticle)
	{
        const xAOD::TruthParticle* Z1LepPlusTruth = dynamic_cast<const xAOD::TruthParticle*>(Z1LepPlus);
        const xAOD::TruthParticle* Z2LepPlusTruth = dynamic_cast<const xAOD::TruthParticle*>(Z2LepPlus);

		if(Z1LepPlusTruth->pdgId() == Z2LepPlusTruth->pdgId())
        {
            if(abs(Z1LepPlusTruth->pdgId()) == 11) m_quadType = _4e;
            else m_quadType = _4mu;
        }
		else 
        {
            if(abs(Z1LepPlusTruth->pdgId()) == 11) m_quadType = _2e2mu;
            else m_quadType = _2mu2e;
        }
    }
	else
	{
		ATH_MSG_ERROR("Particle type not recognized");
		exit(-1);
	}

	// getting the unconstrained pT and eta
	TLorentzVector combined4l = m_Z1LepPlus + m_Z1LepMinus + m_Z2LepPlus + m_Z2LepMinus;    
    float pt4l_unconstrained = combined4l.Pt();
	m_eta4l_unconstrained = combined4l.Eta();    

    if(m_bdtType >= v03_Moriond2017_prodV10) m_pt4l = pt4l_fsr;
    else m_pt4l = pt4l_unconstrained;

}

void H4lBDTWeights::setBDTInputs(TLorentzVector Z1LepPlus,
        TLorentzVector Z1LepMinus,
        TLorentzVector Z2LepPlus,
        TLorentzVector Z2LepMinus,
        BDTQuadType quadType,
        float pt4l_fsr)
{

    m_Z1LepPlus            = Z1LepPlus;
	m_Z1LepMinus           = Z1LepMinus;
	m_Z2LepPlus            = Z2LepPlus;
	m_Z2LepMinus           = Z2LepMinus;
	m_pt4l_truth_born      = 10;
	m_isggH12              = false;

    m_quadType = quadType;

	// getting the unconstrained pT and eta
	TLorentzVector combined4l = m_Z1LepPlus + m_Z1LepMinus + m_Z2LepPlus + m_Z2LepMinus;    
    float pt4l_unconstrained = combined4l.Pt();
	m_eta4l_unconstrained = combined4l.Eta();    

    if(m_bdtType >= v03_Moriond2017_prodV10) m_pt4l = pt4l_fsr;
    else m_pt4l = pt4l_unconstrained;

}


// What calls the other function to compute the relevant values and returns them to the user
//
void H4lBDTWeights::fillBDTOutputs(float &KDOut, 
		float &BDTOut,
		float &BDTGuassOut,
		float &ptSysUpFac,
		float &ptSysDownFac)
{

	m_KD_discriminant = calculateKD();
	
	// For the output
	KDOut = m_KD_discriminant;
	//std::cout<<"KDOut: "<<KDOut<<std::endl;   

	BDTOut = calculateBDT();
	//std::cout<<"BDTOut: "<<BDTOut<<std::endl;

	BDTGuassOut = calculateGuassBDT(BDTOut);
	//std::cout<<"BDTGuassOut: "<<BDTGuassOut<<std::endl;

	ptSysUpFac   = calculatePtSysUp();
	ptSysDownFac = calculatePtSysDown();

	//std::cout<<"ptSysUpFac: "<<ptSysUpFac<<std::endl;
	//std::cout<<"ptSysDownFac: "<<ptSysDownFac<<std::endl;




}

float H4lBDTWeights::calculateKD()
{
	/*-------------MadGraph ME calculation------------*/
	TLorentzVector cms;
	std::vector<TLorentzVector> leptonsOrdered; // the 4 leptons: l+l- l+l-
	std::vector<TLorentzVector> leptonsXpaired; // x-pairs ME calculation

	leptonsOrdered.resize(4);
	leptonsXpaired.resize(4);
	leptonsOrdered[0] = m_Z1LepPlus;
	leptonsOrdered[1] = m_Z1LepMinus;
	leptonsOrdered[2] = m_Z2LepPlus;
	leptonsOrdered[3] = m_Z2LepMinus;
	leptonsXpaired[0] = m_Z2LepPlus;
	leptonsXpaired[1] = m_Z1LepMinus;
	leptonsXpaired[2] = m_Z1LepPlus;
	leptonsXpaired[3] = m_Z2LepMinus;

	for(unsigned l = 0 ; l < leptonsOrdered.size() ; ++l) {
		cms += leptonsOrdered[l];
	}

	// 4-vector in the centre-of-mass frame
	leptonsOrdered[0].Boost(-(cms.BoostVector()));
	leptonsOrdered[1].Boost(-(cms.BoostVector()));
	leptonsOrdered[2].Boost(-(cms.BoostVector()));
	leptonsOrdered[3].Boost(-(cms.BoostVector()));
	leptonsXpaired[0].Boost(-(cms.BoostVector()));
	leptonsXpaired[1].Boost(-(cms.BoostVector()));
	leptonsXpaired[2].Boost(-(cms.BoostVector()));
	leptonsXpaired[3].Boost(-(cms.BoostVector()));

	// Will use the event's CMS as MH value
	std::vector<float> MEHZZ_tmp; // signal ME H->ZZ->4l
	std::vector<float> MEZZ_uu_tmp; // SM ZZ ME, uu contribution
	std::vector<float> MEZZ_dd_tmp; // SM ZZ ME, dd contribution
	std::vector<float> MEHZZXpaired_tmp; // x-pairs signal ME H->ZZ->4l

	if (fabs(m_Z1LepPlus.M() - m_Z2LepPlus.M()) < 10.e-6) { 
		MEHZZ_tmp        = ComputeMGME_cmsM4l(*m_S_heft_gg_4l_SF, leptonsOrdered, cms, cms);
		MEHZZXpaired_tmp = ComputeMGME_cmsM4l(*m_S_heft_gg_4l_SF, leptonsXpaired, cms, cms);
		MEZZ_uu_tmp      = ComputeMGME(*m_S_sm_pp_4l_uu_SF, leptonsOrdered, cms);
		MEZZ_dd_tmp      = ComputeMGME(*m_S_sm_pp_4l_dd_SF, leptonsOrdered, cms);
	}
	else {
		MEHZZ_tmp        = ComputeMGME_cmsM4l(*m_S_heft_gg_4l_DF, leptonsOrdered, cms, cms);
		MEHZZXpaired_tmp = ComputeMGME_cmsM4l(*m_S_heft_gg_4l_DF, leptonsXpaired, cms, cms);
		MEZZ_uu_tmp      = ComputeMGME(*m_S_sm_pp_4l_uu_DF, leptonsOrdered, cms);
		MEZZ_dd_tmp      = ComputeMGME(*m_S_sm_pp_4l_dd_DF, leptonsOrdered, cms);
	}


	float MEHZZ;
	float MEZZ;
	float KD;

	//std::cout << "MEHZZ[0]" << MEHZZ_tmp[0] << std::endl;
	MEHZZ = MEHZZ_tmp[0];// + MEHZZXpaired_tmp[0]; //if x-pairs wanted
	MEZZ = MEZZ_uu_tmp[0] + MEZZ_uu_tmp[1];// + MEZZ_dd_tmp[0] + MEZZ_dd_tmp[1];

	KD = log(MEHZZ/MEZZ);

	return KD;

}

double H4lBDTWeights::getSignalME()
{
    /*-------------MadGraph ME calculation------------*/
    TLorentzVector cms;
    std::vector<TLorentzVector> leptonsOrdered; // the 4 leptons: l+l- l+l-
    
    leptonsOrdered.resize(4);
    leptonsOrdered[0] = m_Z1LepPlus;
    leptonsOrdered[1] = m_Z1LepMinus;
    leptonsOrdered[2] = m_Z2LepPlus;
    leptonsOrdered[3] = m_Z2LepMinus;
    
    for(unsigned l = 0 ; l < leptonsOrdered.size() ; ++l) {
        cms += leptonsOrdered[l];
    }
    
    // 4-vector in the centre-of-mass frame
    leptonsOrdered[0].Boost(-(cms.BoostVector()));
    leptonsOrdered[1].Boost(-(cms.BoostVector()));
    leptonsOrdered[2].Boost(-(cms.BoostVector()));
    leptonsOrdered[3].Boost(-(cms.BoostVector()));    
    
    // Will use the event's CMS as MH value
    std::vector<float> MEHZZ_tmp; // signal ME H->ZZ->4l

    if (fabs(m_Z1LepPlus.M() - m_Z2LepPlus.M()) < 10.e-6)
    {
        MEHZZ_tmp        = ComputeMGME_cmsM4l(*m_S_heft_gg_4l_SF, leptonsOrdered, cms, cms);
    }
    else
    {
        MEHZZ_tmp        = ComputeMGME_cmsM4l(*m_S_heft_gg_4l_DF, leptonsOrdered, cms, cms);
    }
    
    float MEHZZ;
    
    //std::cout << "MEHZZ[0]" << MEHZZ_tmp[0] << std::endl;
    MEHZZ = MEHZZ_tmp[0];// + MEHZZXpaired_tmp[0]; //if x-pairs wanted
    return MEHZZ;
}

double H4lBDTWeights::getSignalME_mH125()
{
    /*-------------MadGraph ME calculation------------*/
    TLorentzVector cms;
    std::vector<TLorentzVector> leptonsOrdered; // the 4 leptons: l+l- l+l-
    
    leptonsOrdered.resize(4);
    leptonsOrdered[0] = m_Z1LepPlus;
    leptonsOrdered[1] = m_Z1LepMinus;
    leptonsOrdered[2] = m_Z2LepPlus;
    leptonsOrdered[3] = m_Z2LepMinus;
    
    for(unsigned l = 0 ; l < leptonsOrdered.size() ; ++l) {
        cms += leptonsOrdered[l];
    }
    
    // 4-vector in the centre-of-mass frame
    leptonsOrdered[0].Boost(-(cms.BoostVector()));
    leptonsOrdered[1].Boost(-(cms.BoostVector()));
    leptonsOrdered[2].Boost(-(cms.BoostVector()));
    leptonsOrdered[3].Boost(-(cms.BoostVector()));    
    
	// Will use the event's CMS as MH value
    std::vector<float> MEHZZ_tmp; // signal ME H->ZZ->4l
    TLorentzVector cms_m4l; 
    cms_m4l.SetPtEtaPhiM(cms.Pt(),cms.Eta(),cms.Phi(),125.);
    if (fabs(m_Z1LepPlus.M() - m_Z2LepPlus.M()) < 10.e-6)
    {
        MEHZZ_tmp        = ComputeMGME_cmsM4l(*m_S_heft_gg_4l_SF, leptonsOrdered, cms, cms_m4l);
    }
    else
    {
        MEHZZ_tmp        = ComputeMGME_cmsM4l(*m_S_heft_gg_4l_DF, leptonsOrdered, cms, cms_m4l);
    }
    
    float MEHZZ;
    
    //std::cout << "MEHZZ[0]" << MEHZZ_tmp[0] << std::endl;
    MEHZZ = MEHZZ_tmp[0];// + MEHZZXpaired_tmp[0]; //if x-pairs wanted
    return MEHZZ;
}

double H4lBDTWeights::getBackgroundME()
{
    /*-------------MadGraph ME calculation------------*/
    TLorentzVector cms;
    std::vector<TLorentzVector> leptonsOrdered; // the 4 leptons: l+l- l+l-
    
    leptonsOrdered.resize(4);
    leptonsOrdered[0] = m_Z1LepPlus;
    leptonsOrdered[1] = m_Z1LepMinus;
    leptonsOrdered[2] = m_Z2LepPlus;
    leptonsOrdered[3] = m_Z2LepMinus;
    
    for(unsigned l = 0 ; l < leptonsOrdered.size() ; ++l) {
        cms += leptonsOrdered[l];
    }
    
    // 4-vector in the centre-of-mass frame
    leptonsOrdered[0].Boost(-(cms.BoostVector()));
    leptonsOrdered[1].Boost(-(cms.BoostVector()));
    leptonsOrdered[2].Boost(-(cms.BoostVector()));
    leptonsOrdered[3].Boost(-(cms.BoostVector()));
    
    // Will use the event's CMS as MH value
    std::vector<float> MEZZ_uu_tmp; // SM ZZ ME, uu contribution
    
    if (fabs(m_Z1LepPlus.M() - m_Z2LepPlus.M()) < 10.e-6) {
        MEZZ_uu_tmp      = ComputeMGME(*m_S_sm_pp_4l_uu_SF, leptonsOrdered, cms);
    }
    else {
        MEZZ_uu_tmp      = ComputeMGME(*m_S_sm_pp_4l_uu_DF, leptonsOrdered, cms);
    }
    
    
    float MEZZ;
    
    //std::cout << "MEHZZ[0]" << MEHZZ_tmp[0] << std::endl;
    MEZZ = MEZZ_uu_tmp[0] + MEZZ_uu_tmp[1];// + MEZZ_dd_tmp[0] + MEZZ_dd_tmp[1];
    return MEZZ;
}

// Get the output from the BDT Var
float H4lBDTWeights::calculateBDT()
{
	float out_bdt = -999;
	if (m_quadType == _4mu)               out_bdt = m_reader->EvaluateMVA("BDTG_4e_4mu");
	else if (m_quadType == _4e)           out_bdt = m_reader->EvaluateMVA("BDTG_4e_4mu");
	else if (m_quadType == _2e2mu)        out_bdt = m_reader->EvaluateMVA("BDTG_2e2mu_2mu2e");
	else if (m_quadType == _2mu2e)        out_bdt = m_reader->EvaluateMVA("BDTG_2e2mu_2mu2e");

	//if (quadType == BDTQuadType::_4mu)        std::cout<<"4mu"<<std::endl;            
	//if (quadType == BDTQuadType::_4e) std::cout<<"4e"<<std::endl;             
	//if (quadType == BDTQuadType::_2e2mu)std::cout<<"2e2mu"<<std::endl;                
	//if (quadType == BDTQuadType::_2mu2e)std::cout<<"2mu2e"<<std::endl;         


	return out_bdt;

}

// Guass ver of BDT
float H4lBDTWeights::calculateGuassBDT(float out_bdt)
{
	double rarity  =-1;

	if (m_quadType == _4e)         rarity  =  m_comb_cumul_4e->GetBinContent( m_comb_cumul_4e->FindBin( out_bdt ) ) ;
	else if (m_quadType == _4mu)   rarity  =  m_comb_cumul_4mu->GetBinContent( m_comb_cumul_4mu->FindBin( out_bdt ) ) ;
	else if (m_quadType == _2e2mu) rarity  =  m_comb_cumul_2e2mu->GetBinContent( m_comb_cumul_2e2mu->FindBin( out_bdt ) ) ;
	else if (m_quadType == _2mu2e) rarity  =  m_comb_cumul_2mu2e->GetBinContent( m_comb_cumul_2mu2e->FindBin( out_bdt ) ) ;

	float outBDT_gauss          =   TMath::Sqrt(2)*TMath::ErfInverse( 1.99999*( rarity - 0.5) ) ;

	return outBDT_gauss;

}

// pT sys
float H4lBDTWeights::calculatePtSysUp()
{
	float ptSysUp = 1;
	if(m_isggH12 && m_pt4l_truth_born > 0) ptSysUp = m_theHptSysTool->GetSysScale_up(m_pt4l_truth_born);

	return ptSysUp;
}

float H4lBDTWeights::calculatePtSysDown()
{
	float ptSysDown = 1;
	if(m_isggH12) ptSysDown = m_theHptSysTool->GetSysScale_down(m_pt4l_truth_born);

	return ptSysDown;

}

// To check is the file exits or not
// Copied from CategoriesMVA tool
bool H4lBDTWeights::checkExistance( TString file_name ) {
	ifstream file( file_name );
	if( file.is_open() ) {
		file.close();
		return kTRUE;
	}
	else return kFALSE;
}



