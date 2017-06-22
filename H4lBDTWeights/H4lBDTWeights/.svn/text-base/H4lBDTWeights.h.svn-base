#ifndef H4LBDTWEIGHTS_H
#define H4LBDTWEIGHTS_H


// C++ includes
#include <TString.h>
#include <TLorentzVector.h>
#include <vector>

// Root includes
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

// Local includes
#include "H4lBDTWeights/HPtSysTool.h"
#include "H4lBDTWeights/IH4lBDTWeights.h"

// Framework includes
#include "PathResolver/PathResolver.h"
#include "AsgTools/AsgTool.h"

// xAOD include:
#include "xAODBase/IParticle.h"

// Forward declarations

class CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemepem;
class CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemmupmum;
class CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemepem;
class CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemmupmum;
class CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemepem;
class CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemmupmum;



class H4lBDTWeights : public virtual IH4lBDTWeights,
					public asg::AsgTool
{
        /// Create a proper constructor for Athena
        ASG_TOOL_CLASS( H4lBDTWeights, IH4lBDTWeights )

	public: 
		H4lBDTWeights(const std::string& name );
		~H4lBDTWeights(void);
		
		/// Initialize constraint fit
		StatusCode initialize();

		/// To get the inputs
		void setBDTInputs(const xAOD::IParticle* Z1LepPlus,
				const xAOD::IParticle* Z1LepMinus,
				const xAOD::IParticle* Z2LepPlus,
				const xAOD::IParticle* Z2LepMinus,
		        float pt4l_fsr,                
				float pt4l_truth_born, 
				bool  isggH12 = false);
		
		/// To get the outputs
		void fillBDTOutputs(float &KDOut,
				float &BDTOut,
				float &BDTGuassOut,
				float &ptSysUpFac,
				float &ptSysDownFac);

        // Requires GeV input
        void setBDTInputs(TLorentzVector Z1LepPlus,
                TLorentzVector Z1LepMinus,
                TLorentzVector Z2LepPlus,
                TLorentzVector Z2LepMinus,
                BDTQuadType quadType,
                float pt4l_fsr);

		double getSignalME();
		double getSignalME_mH125();
        double getBackgroundME();
        double getSignalKD() {return calculateKD(); };


	private:
		int   m_bdtType;

		TString m_pathToWeight;
		TString m_pathToMadGraphFiles;

		// TMVA Reader
		TMVA::Reader* m_reader;

		// Vars for the TMVA reader
		float       m_pt4l;
		float       m_pt4l_truth_born;
		float       m_eta4l_unconstrained;
		float       m_KD_discriminant;
		BDTQuadType m_quadType;
		bool        m_isggH12;

		// For ptSys
		HPtSysTool* m_theHptSysTool;

		// For gaussianization
		TFile* m_thecumul        ;
		TH1D*  m_comb_cumul_4mu  ;
		TH1D*  m_comb_cumul_4e   ;
		TH1D*  m_comb_cumul_2e2mu;
		TH1D*  m_comb_cumul_2mu2e;

		// Madgraph
		/*-------------MadGraph ME calculation------------*/
		// MadGraph ME calculation
		CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemepem*   m_S_heft_gg_4l_SF;
		CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemmupmum* m_S_heft_gg_4l_DF;

		CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemepem*   m_S_sm_pp_4l_uu_SF;
		CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemmupmum* m_S_sm_pp_4l_uu_DF;
		CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemepem*   m_S_sm_pp_4l_dd_SF;
		CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemmupmum* m_S_sm_pp_4l_dd_DF;
		/*------------------------------------------------*/

		// TVL for the leptons
		TLorentzVector m_Z1LepPlus;
		TLorentzVector m_Z1LepMinus;
		TLorentzVector m_Z2LepPlus;
		TLorentzVector m_Z2LepMinus;

		// File
		bool  checkExistance(TString file_name);


		// To get the KD
		float calculateKD();
		float calculateBDT();
		float calculateGuassBDT(float out_bdt);
		float calculatePtSysUp();
		float calculatePtSysDown();

};

#endif



