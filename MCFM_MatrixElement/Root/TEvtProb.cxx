//-----------------------------------------------------------------------------
//
// Class EventProb Module
//
//   EventProb Module
//
// March 21 2011
// S. Jindariani (sergo@fnal.gov)
// Y. Gao (Yanyan.Gao@cern.ch)
// K. Burkett (burkett@fnal.gov)
//-----------------------------------------------------------------------------

#include "MCFM_MatrixElement/TEvtProb.h"
#include "MCFM_MatrixElement/TVar.h"
#include <fstream>

// ClassImp(TEvtProb)
  using namespace std;

  //-----------------------------------------------------------------------------
  // Constructors and Destructor
  //-----------------------------------------------------------------------------
  TEvtProb::TEvtProb(std::string infile, std::string) {
    mcfm_init_(const_cast<char*>(infile.c_str()), "./");
    SetEwkCoupligParameters();
    SetLeptonInterf(TVar::NoLeptonInterf);
    coupling_();
  }


TEvtProb::~TEvtProb() {
}

//
// Directly calculate the ZZ->4l differential cross-section 
// WARNING: in development
// 
double TEvtProb::XsecCalc(TVar::Process proc, TVar::Production production, const hzz4l_event_type &hzz4l_event,
    TVar::VerbosityLevel verbosity){


  //Initialize Process

  SetProduction(production);

  TString meName = "MCFM";
  
  bool hasZZ4fInterf= ( abs(hzz4l_event.PdgCode[0])==abs(hzz4l_event.PdgCode[2]) && abs(hzz4l_event.PdgCode[1])==abs(hzz4l_event.PdgCode[3]) );
  if ( _matrixElement == TVar::MCFM) 
    My_choose(proc, _leptonInterf, hasZZ4fInterf);

  //constants
  double sqrts = 2.*EBEAM;
  double W=sqrts*sqrts;

  //Weight calculation
  double flux=1.;
  double dXsec=0.;

  mcfm_event_type mcfm_event; 
  // assign the right initial momentum
  // assumes the events are boosted to have 0 transverse momenta
  double sysPz= ( hzz4l_event.p[0] + hzz4l_event.p[1] + hzz4l_event.p[2] + hzz4l_event.p[3] ).Pz();
  double sysE = ( hzz4l_event.p[0] + hzz4l_event.p[1] + hzz4l_event.p[2] + hzz4l_event.p[3] ).Energy();
  double pz0 = (sysE+sysPz)/2.; 
  double pz1 = -(sysE-sysPz)/2.;
  mcfm_event.p[0].SetPxPyPzE   (0., 0., pz0, TMath::Abs(pz0));
  mcfm_event.p[1].SetPxPyPzE   (0., 0., pz1, TMath::Abs(pz1));
  mcfm_event.p[2].SetPxPyPzE   (hzz4l_event.p[0].Px(), hzz4l_event.p[0].Py(), hzz4l_event.p[0].Pz(), hzz4l_event.p[0].Energy());
  mcfm_event.p[3].SetPxPyPzE   (hzz4l_event.p[1].Px(), hzz4l_event.p[1].Py(), hzz4l_event.p[1].Pz(), hzz4l_event.p[1].Energy());
  mcfm_event.p[4].SetPxPyPzE   (hzz4l_event.p[2].Px(), hzz4l_event.p[2].Py(), hzz4l_event.p[2].Pz(), hzz4l_event.p[2].Energy());
  mcfm_event.p[5].SetPxPyPzE   (hzz4l_event.p[3].Px(), hzz4l_event.p[3].Py(), hzz4l_event.p[3].Pz(), hzz4l_event.p[3].Energy());

  mcfm_event.PdgCode[0] = 21;
  mcfm_event.PdgCode[1] = 21;
  mcfm_event.PdgCode[2] = hzz4l_event.PdgCode[0];
  mcfm_event.PdgCode[3] = hzz4l_event.PdgCode[1];
  mcfm_event.PdgCode[4] = hzz4l_event.PdgCode[2];
  mcfm_event.PdgCode[5] = hzz4l_event.PdgCode[3];

  // Matrix Element evaluation in qX=qY=0 frame
  //Evaluate f(x1)f(x2)|M(q)|/x1/x2 
  // 
  double qX=mcfm_event.p[0].Px()+mcfm_event.p[1].Px();
  double qY=mcfm_event.p[0].Py()+mcfm_event.p[1].Py();

  if((qX*qX+qY*qY)>0){
    double qE = mcfm_event.p[0].Energy()+mcfm_event.p[1].Energy();
    TVector3 boostV(qX/qE,qY/qE,0);
    for(int ipt=0;ipt<6;ipt++) mcfm_event.p[ipt].Boost(-boostV);
  }
  //event selections in Lab Frame
  double flavor_msq[nmsq][nmsq];
  double msqjk=0; 
  if ( _matrixElement == TVar::MCFM ) 
    msqjk = SumMatrixElementPDF(proc, &mcfm_event, flavor_msq, &flux, _fixedScale);
    if(msqjk<=0){ mcfm_event.pswt=0; }

  flux=fbGeV2/(mcfm_event.p[0].Energy()*mcfm_event.p[1].Energy())	/(4*W);
  //    dXsec=msqjk*flux;
  dXsec=msqjk;

  if (verbosity >= TVar::INFO)
  {
    cout <<"Process " << TVar::ProcessName(proc) << 
      " TEvtProb::XsecCalc(), using Method " << meName << ":  dXsec=" << dXsec
      <<" Msq="<<msqjk 
      <<endl;
  }

  return dXsec;

}
// this appears to be some kind of 
// way of setting MCFM parameters through
// an interface defined in TMCFM.hh
void TEvtProb::SetHiggsMass(double mass, bool fixedScale){
  masses_mcfm_.hmass=mass;
  // std::cout << "m_H = "<<mass<<std::endl;
  masses_mcfm_.hwidth=0.004; // use narrow width for 125
  _hmass = mass;
  _hwidth = 0.004;
  _fixedScale = fixedScale;

  // 'borrowed' from MG...
  // 

  const long double Higgs_width_Poly_Fit_Zone1_coeff0=-1.450308902710193E+03;
  const long double Higgs_width_Poly_Fit_Zone1_coeff1=1.129291251156317E+02;
  const long double Higgs_width_Poly_Fit_Zone1_coeff2=-3.893063071316150E+00;
  const long double Higgs_width_Poly_Fit_Zone1_coeff3=7.798666884832531E-02;
  const long double Higgs_width_Poly_Fit_Zone1_coeff4=-1.000455877406390E-03;
  const long double Higgs_width_Poly_Fit_Zone1_coeff5=8.523735379647125E-06;
  const long double Higgs_width_Poly_Fit_Zone1_coeff6=-4.823164754652171E-08;
  const long double Higgs_width_Poly_Fit_Zone1_coeff7=1.747954506786346E-10;
  const long double Higgs_width_Poly_Fit_Zone1_coeff8=-3.681723572169337E-13;
  const long double Higgs_width_Poly_Fit_Zone1_coeff9=3.434207075968898E-16;
  
  const long double Higgs_width_Poly_Fit_Zone2_coeff0=2.563291882845993E+02;
  const long double Higgs_width_Poly_Fit_Zone2_coeff1=-1.037082025855304E+01;
  const long double Higgs_width_Poly_Fit_Zone2_coeff2=1.780260502696301E-01;
  const long double Higgs_width_Poly_Fit_Zone2_coeff3=-1.720311784419889E-03;
  const long double Higgs_width_Poly_Fit_Zone2_coeff4=1.038418605369741E-05;
  const long double Higgs_width_Poly_Fit_Zone2_coeff5=-4.092496883922424E-08;
  const long double Higgs_width_Poly_Fit_Zone2_coeff6=1.067667966800388E-10;
  const long double Higgs_width_Poly_Fit_Zone2_coeff7=-1.823343280081685E-13;
  const long double Higgs_width_Poly_Fit_Zone2_coeff8=1.955637395597351E-16;
  const long double Higgs_width_Poly_Fit_Zone2_coeff9=-1.193287048560413E-19;
  const long double Higgs_width_Poly_Fit_Zone2_coeff10=3.156196649452213E-23;
  
  const long double Higgs_width_Poly_Fit_Zone12_coeff0=-5.255605465437446E+02;
  const long double Higgs_width_Poly_Fit_Zone12_coeff1=1.036972988796150E+01;
  const long double Higgs_width_Poly_Fit_Zone12_coeff2=-6.817022987365029E-02;
  const long double Higgs_width_Poly_Fit_Zone12_coeff3=1.493275723660056E-04;
  
  long double m_m4l = mass;
  long double m_m4l__2 = mass*mass;
  long double m_m4l__3 = m_m4l__2*mass;

  if( m_m4l < 156.5 ) _hwidth = ( Higgs_width_Poly_Fit_Zone1_coeff0
            + Higgs_width_Poly_Fit_Zone1_coeff1*m_m4l
            + Higgs_width_Poly_Fit_Zone1_coeff2*m_m4l__2
            + Higgs_width_Poly_Fit_Zone1_coeff3*m_m4l__3
            + Higgs_width_Poly_Fit_Zone1_coeff4*m_m4l__2*m_m4l__2
            + Higgs_width_Poly_Fit_Zone1_coeff5*m_m4l__2*m_m4l__3
            + Higgs_width_Poly_Fit_Zone1_coeff6*m_m4l__2*m_m4l__2*m_m4l__2
            + Higgs_width_Poly_Fit_Zone1_coeff7*m_m4l__2*m_m4l__2*m_m4l__3
            + Higgs_width_Poly_Fit_Zone1_coeff8*m_m4l__2*m_m4l__2*m_m4l__2*m_m4l__2
            + Higgs_width_Poly_Fit_Zone1_coeff9*m_m4l__2*m_m4l__2*m_m4l__2*m_m4l__3 );
  else if( m_m4l >= 156.5 && m_m4l <= 162 ) _hwidth =  ( Higgs_width_Poly_Fit_Zone12_coeff0
                + Higgs_width_Poly_Fit_Zone12_coeff1*m_m4l
                + Higgs_width_Poly_Fit_Zone12_coeff2*m_m4l__2
                + Higgs_width_Poly_Fit_Zone12_coeff3*m_m4l__3 );
  else _hwidth =  ( Higgs_width_Poly_Fit_Zone2_coeff0
    + Higgs_width_Poly_Fit_Zone2_coeff1*m_m4l
    + Higgs_width_Poly_Fit_Zone2_coeff2*m_m4l__2
    + Higgs_width_Poly_Fit_Zone2_coeff3*m_m4l__3
    + Higgs_width_Poly_Fit_Zone2_coeff4*m_m4l__2*m_m4l__2
    + Higgs_width_Poly_Fit_Zone2_coeff5*m_m4l__2*m_m4l__3
    + Higgs_width_Poly_Fit_Zone2_coeff6*m_m4l__2*m_m4l__2*m_m4l__2
    + Higgs_width_Poly_Fit_Zone2_coeff7*m_m4l__2*m_m4l__2*m_m4l__3
    + Higgs_width_Poly_Fit_Zone2_coeff8*m_m4l__2*m_m4l__2*m_m4l__2*m_m4l__2
    + Higgs_width_Poly_Fit_Zone2_coeff9*m_m4l__2*m_m4l__2*m_m4l__2*m_m4l__3
    + Higgs_width_Poly_Fit_Zone2_coeff10*m_m4l__2*m_m4l__2*m_m4l__2*m_m4l__2*m_m4l__2 );
  

  masses_mcfm_.hwidth=_hwidth;

}
