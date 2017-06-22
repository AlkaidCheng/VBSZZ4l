#ifndef EvtProb_VAR
#define EvtProb_VAR

#include <TLorentzVector.h>

#define EBEAM 6500.00
#define fbGeV2 0.389379E12
#define smallnumber 1e-15
#define sixteen_2Pi_to_8 3.88650230418250561e+07
#define   eight_2Pi_to_5 7.83410393050320417e+04
#define    four_2Pi_to_2 39.478417604357432
class TVar{
  public:
    enum VerbosityLevel {
      ERROR = 0,
      INFO = 1,
      DEBUG = 2
    };
    enum MatrixElement{
      MCFM = 0,
   };
    enum Production{
      GG = 0,
      QQB = 1,
      INDEPENDENT=2
    };
    
    enum quadType{
      Flavor_4mu = 0,
      Flavor_4e = 1,
      Flavor_2mu2e = 2,
      Flavor_2e2mu = 3,
    };
    enum LeptonInterference{
      NoLeptonInterf,
      QQbInterfOnly,
      GGInterfOnly,
      InterfBoth
    };

    enum Process{
      QQbZZ_4l  = 1, // eemm
      HZZ_4l   = 2, 
      GGZZ_4l =  3,
      GGZZTOT_4l = 4,
      GGZZINT_4l = 5,
      Null
    };

    //---------------------------------
    // Function
    //---------------------------------
    static TString ProcessName(int temp){ 
      if(temp==TVar::QQbZZ_4l   ) 
        return TString("ZZ_4l");
      if(temp==TVar::GGZZ_4l   ) 
        return TString("GGZZ_4l");
      else if(temp==TVar::HZZ_4l   ) 
        return TString("HZZ_4l");
      else if(temp==TVar::GGZZTOT_4l   ) 
        return TString("GGZZ_total_4l");
      else if(temp==TVar::GGZZINT_4l   ) 
        return TString("GGZZ_interference_4l");
      else 
        return TString("UnKnown");
    };
    ClassDef(TVar,0)
};

struct branch_particle {
  int   PdgCode   ;
  int   Charge    ;
  double Px       ;
  double Py       ;
  double Pz       ;
  double E        ;
  double Eta      ;
  double Phi      ;

};
static const TString branch_format_particle =
"PdgCode/I:"
"Charge/I:"
"Px/D:"
"Py/D:"
"Pz/D:"
"E/D:"
"Eta/D:"
"Phi/D";

struct hzz4l_event_type{
  int PdgCode[4];
  TLorentzVector p[4];
  double Xsec   [10];
  double XsecErr[10];  
};

struct mcfm_event_type{
  int PdgCode[6];
  TLorentzVector p[6];
  double pswt;
};
struct event_type{
  TLorentzVector p1,p2,ep,em,nu,nb;
  double PSWeight;
};
struct anomcoup{
  double delg1_z, delg1_g, lambda_g, lambda_z, delk_g, delk_z_,tevscale;
};

#endif
