#ifndef IH4LBDTWEIGHTS_H
#define IH4LBDTWEIGHTS_H

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

// Framework includes
#include "PathResolver/PathResolver.h"
#include "AsgTools/IAsgTool.h"

// xAOD include:
#include "xAODBase/IParticle.h"

class IH4lBDTWeights : public virtual asg::IAsgTool 
{
	ASG_TOOL_INTERFACE( H4lBDTWeights )
	public: 
		enum BDTQuadType {
			_4mu,
			_2mu2e,
			_2e2mu,
			_4e,
			UNKNOWN
		};

		
		enum BDTType {
			final2011,
			final2012,
			v01_2015,
            v02_ICHEP16_prodV4,
            v03_Moriond2017_prodV10,
            v04_Moriond2017_prodV12,
		};

		/// To get the inputs
		virtual void setBDTInputs(const xAOD::IParticle* Z1LepPlus,
				const xAOD::IParticle* Z1LepMinus,
				const xAOD::IParticle* Z2LepPlus,
				const xAOD::IParticle* Z2LepMinus,
		        float pt4l_fsr,                
				float pt4l_truth_born, 
				bool  isggH12 = false) = 0;


        
        // Requires GeV input
        virtual void setBDTInputs(TLorentzVector Z1LepPlus,
                TLorentzVector Z1LepMinus,
                TLorentzVector Z2LepPlus,
                TLorentzVector Z2LepMinus,
                BDTQuadType quadType,
                float pt4l_fsr) = 0;

		/// To get the outputs
		virtual void fillBDTOutputs(float &KDOut,
				float &BDTOut,
				float &BDTGuassOut,
				float &ptSysUpFac,
				float &ptSysDownFac) = 0;

        virtual double getSignalME() = 0;
        virtual double getSignalME_mH125() = 0;
        virtual double getBackgroundME() = 0;
        virtual double getSignalKD() = 0;
};

#endif



