
#include "MCFM_MatrixElement/MatrixElementProvider.h"
#include "xAODTruth/TruthParticle.h"
#include "PathResolver/PathResolver.h"

namespace HSG2_MCFM{

  // forward declare this guy
  bool OrganiseMCFMStuff();

  MatrixElementProvider::MatrixElementProvider(const std::string& name)
  : AsgTool (name),
    m_Xcal2(0){
    declareProperty("HiggsMass",m_mH = 125);
    declareProperty("Is13TeV",m_13TeV = true);
  }

  MatrixElementProvider::~MatrixElementProvider(){
    if (m_Xcal2 != 0){
      delete m_Xcal2;
      m_Xcal2=0;
    }
    // clean up the mean dxs if we have it
    if (m_par_qq) delete m_par_qq;
    if (m_par_SBI) delete m_par_SBI;
    if (m_par_ggH) delete m_par_ggH;
  }

  StatusCode MatrixElementProvider::initialize(){

    ATH_MSG_DEBUG("MatrixElementProvider::initialize ");

    if (!OrganiseMCFMStuff()){
      ATH_MSG_ERROR("Unable to link the MCFM input files to the current dir!");
      return StatusCode::FAILURE;
    }
    std::string infile = "input.DAT";
    if (m_13TeV) infile = "input13TeV.DAT";
    std::cout << "init with "<<infile<<std::endl;
    m_Xcal2 = new TEvtProb(infile);
    m_Xcal2->SetHiggsMass(m_mH,false);
  m_Xcal2->SetMatrixElement(TVar::MCFM);

    // read the mean dxs
    std::string inFileForAverageDxs = PathResolver::find_file ("MCFM_MatrixElement/MassTemplates.root", "CALIBPATH");
    TFile* fin = TFile::Open(inFileForAverageDxs.c_str(), "READ");
    if (!fin){
      ATH_MSG_ERROR( "Unable to read the Mass template file, assumed to be at "<<inFileForAverageDxs);
      return StatusCode::FAILURE;
    }
    TH1D* h_dxs_qq = dynamic_cast<TH1D*>(fin->Get("h_dxs_m_qq"));
    TH1D* h_dxs_SBI = dynamic_cast<TH1D*>(fin->Get("h_dxs_m_SBI"));
    TH1D* h_dxs_ggH = dynamic_cast<TH1D*>(fin->Get("h_dxs_m_ggH"));

    if (!h_dxs_qq || !h_dxs_SBI || !h_dxs_ggH){
      ATH_MSG_ERROR( "Unable to read histograms from the Mass template file at "<<inFileForAverageDxs);
      return StatusCode::FAILURE;
    }
    m_par_qq = new TGraph(h_dxs_qq);
    m_par_SBI = new TGraph(h_dxs_SBI);
    m_par_ggH = new TGraph(h_dxs_ggH);

    return StatusCode::SUCCESS;
  }

  void MatrixElementProvider::RestSystemTransforms(TLorentzVector & z1Minus, TLorentzVector & z1Plus,
                               TLorentzVector & z2Minus, TLorentzVector & z2Plus){

    TLorentzVector fourlsystem = z1Minus + z1Plus + z2Minus + z2Plus;
    TVector3 boost = fourlsystem.BoostVector();
    z1Minus.Boost(-boost);
    z1Plus.Boost(-boost);
    z2Minus.Boost(-boost);
    z2Plus.Boost(-boost);

  }

  int MatrixElementProvider::getPdg(const xAOD::IParticle & p){
    xAOD::Type::ObjectType type = p.type();
    if (type == xAOD::Type::Electron) return 11;
    else if (type == xAOD::Type::Muon) return 13;
    else if (type == xAOD::Type::TruthParticle) {
      const xAOD::TruthParticle* tp = dynamic_cast<const xAOD::TruthParticle*>(&p);
      if (!tp){
        std::cerr << "MatrixElementProvider: cast to truth particle failed! "<<std::endl;
        return 0;
      }
      return abs(tp->pdgId());

    }
    else{ 
      std::cerr << " MatrixElementProvider: Could not make sense of the input particle"<<std::endl;
      return 0;
    }
  }
  StatusCode MatrixElementProvider::getME(const xAOD::IParticle & z1Minus, const xAOD::IParticle & z1Plus,
                                        const xAOD::IParticle & z2Minus,const xAOD::IParticle & z2Plus, MatrixElementResult & res){

    ATH_MSG_DEBUG("MatrixElementProvider::getME with IParticle ");

    // we need to identify the flavours 
    int pdg_1 = 1 * getPdg(z1Minus);
    int pdg_2 = -1 * getPdg(z1Plus);
    int pdg_3 = 1 * getPdg(z2Minus);
    int pdg_4 = -1 * getPdg(z2Plus);

    ATH_MSG_DEBUG("getME: pdg 1,2,3,4 " << pdg_1 << "/" << pdg_2 << "/" << pdg_3 << "/" << pdg_4);

    
    if (pdg_1 == 0 || pdg_2 == 0 || pdg_3 == 0 || pdg_4 == 0){
      ATH_MSG_WARNING("MatrixElementProvider could not identify the final state flavour configuration");
      return StatusCode::FAILURE;
    }

    const double MeV_GeV = 1./1000.;
    TLorentzVector Z1minus_GeV = z1Minus.p4() * MeV_GeV;
    TLorentzVector Z1plus_GeV = z1Plus.p4() * MeV_GeV;
    TLorentzVector Z2minus_GeV = z2Minus.p4() * MeV_GeV;
    TLorentzVector Z2plus_GeV = z2Plus.p4() * MeV_GeV;

    // Z1minus_GeV.Print();
    // Z1plus_GeV.Print();
    // Z2minus_GeV.Print();
    // Z2plus_GeV.Print();

    MatrixElementResult res_tmp = getME(Z1minus_GeV, Z1plus_GeV,Z2minus_GeV,Z2plus_GeV,pdg_1,pdg_2,pdg_3,pdg_4);

    if (res_tmp.dxs_ZZ != res_tmp.dxs_ZZ ||
        res_tmp.dxs_ggZZ != res_tmp.dxs_ggZZ || 
        res_tmp.dxs_ggZZint != res_tmp.dxs_ggZZint || 
        res_tmp.dxs_ggZZtot != res_tmp.dxs_ggZZtot || 
        res_tmp.dxs_HZZ != res_tmp.dxs_HZZ || 
        res_tmp.dxs_HZZ_mHm4l != res_tmp.dxs_HZZ_mHm4l ||
        res_tmp.MELA_ggZZ != res_tmp.MELA_ggZZ ||  
        res_tmp.MELA_CMS_ggZZ != res_tmp.MELA_CMS_ggZZ ||  
        res_tmp.MELA_KD != res_tmp.MELA_KD ||  
        res_tmp.MELA_KD_mHm4l != res_tmp.MELA_KD_mHm4l){
      ATH_MSG_WARNING(" MatrixElementProvider: NaN result! ");
      return StatusCode::FAILURE;
    }
    res = res_tmp;
    return StatusCode::SUCCESS;
  }
  MatrixElementResult MatrixElementProvider::getME(
      const TLorentzVector& z1Minus,const TLorentzVector& z1Plus,
      const TLorentzVector& z2Minus,const TLorentzVector& z2Plus,
      int pdg_1, int pdg_2, int pdg_3, int pdg_4) {

    ATH_MSG_DEBUG("MatrixElementProvider::getME with TLV ");
    // populate the hzz4l_event
    m_hzz4l_event.p[0].SetXYZM(z1Minus.Px(), z1Minus.Py(), z1Minus.Pz(), 0.);
    m_hzz4l_event.p[1].SetXYZM(z1Plus.Px(), z1Plus.Py(), z1Plus.Pz(), 0.);
    m_hzz4l_event.p[2].SetXYZM(z2Minus.Px(), z2Minus.Py(), z2Minus.Pz(), 0.);
    m_hzz4l_event.p[3].SetXYZM(z2Plus.Px(), z2Plus.Py(), z2Plus.Pz(), 0.);


    ATH_MSG_DEBUG("p0: pt "<<m_hzz4l_event.p[0].Pt()<<", eta "<<m_hzz4l_event.p[0].Eta()<<", phi "<< m_hzz4l_event.p[0].Phi());
    ATH_MSG_DEBUG("p1: pt "<<m_hzz4l_event.p[1].Pt()<<", eta "<<m_hzz4l_event.p[1].Eta()<<", phi "<< m_hzz4l_event.p[1].Phi());
    ATH_MSG_DEBUG("p2: pt "<<m_hzz4l_event.p[2].Pt()<<", eta "<<m_hzz4l_event.p[2].Eta()<<", phi "<< m_hzz4l_event.p[2].Phi());
    ATH_MSG_DEBUG("p3: pt "<<m_hzz4l_event.p[3].Pt()<<", eta "<<m_hzz4l_event.p[3].Eta()<<", phi "<< m_hzz4l_event.p[3].Phi());


    ATH_MSG_DEBUG("MatrixElementProvider::getME with TLV 1");
    
    RestSystemTransforms(m_hzz4l_event.p[0],m_hzz4l_event.p[1],m_hzz4l_event.p[2],m_hzz4l_event.p[3]);

    ATH_MSG_DEBUG("MatrixElementProvider::getME with TLV 2");

    getQuadType(pdg_1,pdg_2,pdg_3,pdg_4);

    ATH_MSG_DEBUG("pdgs: "<<pdg_1<<" "<<pdg_2<<" "<<pdg_3<<" "<<pdg_4);

    ATH_MSG_DEBUG("MatrixElementProvider::getME with TLV 3");

    MatrixElementResult result;

    // MCFM based calculations
    m_Xcal2->SetHiggsMass(m_mH,false);
    ATH_MSG_DEBUG("MatrixElementProvider::getME with TLV 3 1");
    result.dxs_HZZ = m_Xcal2->XsecCalc(TVar::HZZ_4l, TVar::QQB, m_hzz4l_event,TVar::ERROR);
    ATH_MSG_DEBUG("MatrixElementProvider::getME with TLV 3 2");
    result.dxs_ZZ = m_Xcal2->XsecCalc(TVar::QQbZZ_4l, TVar::QQB, m_hzz4l_event,TVar::ERROR);
    ATH_MSG_DEBUG("MatrixElementProvider::getME with TLV 3 3");
    result.dxs_ggZZ = m_Xcal2->XsecCalc(TVar::GGZZ_4l, TVar::GG, m_hzz4l_event,TVar::ERROR);
    ATH_MSG_DEBUG("MatrixElementProvider::getME with TLV 3 4");
    result.dxs_ggZZtot = m_Xcal2->XsecCalc(TVar::GGZZTOT_4l, TVar::GG, m_hzz4l_event,TVar::ERROR);
    ATH_MSG_DEBUG("MatrixElementProvider::getME with TLV 3 5");
    result.dxs_ggZZint = m_Xcal2->XsecCalc(TVar::GGZZINT_4l, TVar::GG, m_hzz4l_event,TVar::ERROR);

    ATH_MSG_DEBUG("MatrixElementProvider::getME with TLV 4");

    // the SetHiggsMass method expects GeV inputs, so we can directly ude our 4-momenta, which also have GeV!
    double localM4l = (m_hzz4l_event.p[0]+m_hzz4l_event.p[1]+m_hzz4l_event.p[2]+m_hzz4l_event.p[3]).M();
    m_Xcal2->SetHiggsMass(localM4l,false);
    // redo the HZZ calculation assuming m_H = m_4l
    result.dxs_HZZ_mHm4l = m_Xcal2->XsecCalc(TVar::HZZ_4l, TVar::QQB, m_hzz4l_event,TVar::ERROR);

    // construct based MELA
    float width_ratio = 1;
    float cME = 0.1;
    float m_dXsec_GGZZTOT_MCFM = result.dxs_HZZ * width_ratio + result.dxs_ggZZint * sqrt(width_ratio)+ result.dxs_ggZZ;
    result.MELA_ggZZ = log10( result.dxs_HZZ / ( m_dXsec_GGZZTOT_MCFM + cME * result.dxs_ZZ ));
    result.MELA_ggZZ_mHm4l = log10( result.dxs_HZZ_mHm4l / ( m_dXsec_GGZZTOT_MCFM + cME * result.dxs_ZZ ));
    result.MELA_CMS_ggZZ = m_dXsec_GGZZTOT_MCFM / ( m_dXsec_GGZZTOT_MCFM + cME * result.dxs_ZZ  );
    result.MELA_KD = log(result.dxs_HZZ / result.dxs_ZZ );
    result.MELA_KD_mHm4l = log(result.dxs_HZZ_mHm4l / result.dxs_ZZ );

    // get the additional terms for the average dxs
    
    if (localM4l < m_par_qq->GetX()[0]){
      result.mean_dxs_ZZ_atM4l = m_par_qq->GetY()[0];
      result.mean_dxs_ggZZtot_atM4l = m_par_SBI->GetY()[0];
      result.mean_dxs_HZZ_atM4l = m_par_ggH->GetY()[0];
    }
    else if (localM4l > m_par_qq->GetX()[m_par_qq->GetN()-1]){
      result.mean_dxs_ZZ_atM4l = m_par_qq->GetY()[m_par_qq->GetN()-1];
      result.mean_dxs_ggZZtot_atM4l = m_par_SBI->GetY()[m_par_qq->GetN()-1];
      result.mean_dxs_HZZ_atM4l = m_par_ggH->GetY()[m_par_qq->GetN()-1];
    }
    else {
      result.mean_dxs_ZZ_atM4l = m_par_qq->Eval(localM4l);
      result.mean_dxs_ggZZtot_atM4l = m_par_SBI->Eval(localM4l);
      result.mean_dxs_HZZ_atM4l = m_par_ggH->Eval(localM4l);
    }

    // and the decorrelated MELA 
    if (result.mean_dxs_HZZ_atM4l != 0 && result.mean_dxs_ggZZtot_atM4l != 0 && result.mean_dxs_ZZ_atM4l != 0){
      result.MELA_ggZZ_deco = log10( (result.dxs_HZZ / result.mean_dxs_HZZ_atM4l) / ( (result.dxs_ggZZtot / result.mean_dxs_ggZZtot_atM4l) + cME * (result.dxs_ZZ / result.mean_dxs_ZZ_atM4l) ));
    }
    else {
        ATH_MSG_WARNING("Encountered a zero value for one of the tabulated <dxs> mean values! ");
        result.MELA_ggZZ_deco = -10000;
    }
    return result;


  }
  TVar::quadType MatrixElementProvider::getQuadType(int pdg_1, int pdg_2, int pdg_3, int pdg_4){

    // default

    // See lepton ID definitions here, search for "leptonIDType"
    // https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/HiggsZZllllSummer2013#Common_Nomenclature_for_the_Higg
    // 4e events

    m_hzz4l_event.PdgCode[0] = pdg_1;
    m_hzz4l_event.PdgCode[1] = pdg_2;
    m_hzz4l_event.PdgCode[2] = pdg_3;
    m_hzz4l_event.PdgCode[3] = pdg_4;

    if ((pdg_1 != -pdg_2) || (pdg_3 != -pdg_4)){
      ATH_MSG_ERROR("This is not a 2xSFOS quad! ");
    }

    if (abs(pdg_1)== 11){
      if (abs(pdg_3) == 11){
        return  TVar::Flavor_4e;
      }
      else if (abs(pdg_3) == 13){
        return  TVar::Flavor_2e2mu;
      }
    }
    else if (abs(pdg_1)== 13){
      if (abs(pdg_3) == 11){
        return  TVar::Flavor_2mu2e;
      }
      else if (abs(pdg_3) == 13){
        return  TVar::Flavor_4mu;
      }
    }
    std::cerr << "MatrixElementProvider: Could not identify the quad type!"<<std::endl;
    // this is never used...
    return TVar::Flavor_4mu;
  }
}
