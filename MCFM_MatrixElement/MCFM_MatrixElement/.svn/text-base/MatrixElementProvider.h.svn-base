#ifndef MATRIXELEMENTPROVIDER_H
#define MATRIXELEMENTPROVIDER_H
// Framework include(s):
#include "AsgTools/IAsgTool.h"
#include "MCFM_MatrixElement/IMatrixElementProvider.h"

#include <iostream>
#include "Math/LorentzVector.h"
#include "TLorentzRotation.h"
#include "Math/VectorUtil.h"
// ME related

#include "MCFM_MatrixElement/TVar.h"
#include "MCFM_MatrixElement/TEvtProb.h"

#include "RooRealVar.h"
#include "math.h"

#include "AsgTools/AsgTool.h"
//typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;

namespace HSG2_MCFM{


class MatrixElementProvider : public virtual IMatrixElementProvider, public virtual asg::AsgTool {
    ASG_TOOL_CLASS( MatrixElementProvider, IMatrixElementProvider)

    public:
      MatrixElementProvider(const std::string & name);
      virtual StatusCode initialize();
      // note: the four-momenta need to be given in GeV
      virtual MatrixElementResult getME(const TLorentzVector & z1Minus,const TLorentzVector & z1Plus,
                                        const TLorentzVector & z2Minus,const TLorentzVector & z2Plus,
                                        int pdg_1, int pdg_2, int pdg_3, int pdg_4);
      // xAOD interface 
      virtual StatusCode getME(const xAOD::IParticle & z1Minus, const xAOD::IParticle & z1Plus,
                                        const xAOD::IParticle & z2Minus,const xAOD::IParticle & z2Plus, MatrixElementResult & res);
      
      virtual ~MatrixElementProvider();

    private:
      // TODO: Add sqrt(s) as a configurable!

      TEvtProb* m_Xcal2;
      hzz4l_event_type m_hzz4l_event;
      TVar::quadType getQuadType(int pdg_1, int pdg_2, int pdg_3, int pdg_4);
      void RestSystemTransforms(TLorentzVector & z1Minus, TLorentzVector & z1Plus,
                                 TLorentzVector & z2Minus, TLorentzVector & z2Plus);
      int getPdg(const xAOD::IParticle & p);
      float m_mH;
      bool m_13TeV;
      TGraph* m_par_qq;
      TGraph* m_par_SBI;
      TGraph* m_par_ggH;

  };
}

#endif
