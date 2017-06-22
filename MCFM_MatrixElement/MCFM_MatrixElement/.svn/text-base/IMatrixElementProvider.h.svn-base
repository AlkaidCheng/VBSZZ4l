#ifndef IMATRIXELEMENTPROVIDER_H
#define IMATRIXELEMENTPROVIDER_H
// Framework include(s):
#include "AsgTools/IAsgTool.h"
#include "AsgTools/StatusCode.h"
#include "xAODBase/IParticle.h"

class TLorentzVector;

namespace HSG2_MCFM{


  // simple packaging for the MCFM output
  struct MatrixElementResult{
    public:
      double dxs_ZZ;
      double dxs_ggZZ;
      double dxs_ggZZtot;
      double dxs_ggZZint;
      double dxs_HZZ;
      double MELA_ggZZ;
      double MELA_ggZZ_mHm4l;
      double MELA_KD;
      double MELA_CMS_ggZZ;
      double dxs_HZZ_mHm4l;
      double MELA_KD_mHm4l;
      double mean_dxs_HZZ_atM4l;
      double mean_dxs_ggZZtot_atM4l;
      double mean_dxs_ZZ_atM4l;
      double MELA_ggZZ_deco;
  };

class IMatrixElementProvider : public virtual asg::IAsgTool {
    ASG_TOOL_INTERFACE( IMatrixElementProvider )

    public:

      virtual StatusCode initialize() = 0;
      // historical interface for ntuple analyses.
      // When using this, please provide GeV units for the input 4-momenta!
      virtual MatrixElementResult getME(const TLorentzVector & z1Minus,const TLorentzVector & z1Plus,
                                        const TLorentzVector & z2Minus,const TLorentzVector & z2Plus,
                                        int pdg_1, int pdg_2, int pdg_3, int pdg_4) = 0;
      // xAOD interface. Will internally take care of unit conversions and determining flavours
      virtual StatusCode getME(const xAOD::IParticle & z1Minus, const xAOD::IParticle & z1Plus,
                                        const xAOD::IParticle & z2Minus,const xAOD::IParticle & z2Plus, MatrixElementResult & res) = 0;\
  };
}

#endif
