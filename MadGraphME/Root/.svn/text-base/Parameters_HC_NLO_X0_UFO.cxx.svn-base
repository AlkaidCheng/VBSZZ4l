//==========================================================================
// This file has been automatically generated for C++ by
// MadGraph5_aMC@NLO v. 2.2.1, 2014-09-25
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include <iostream> 
#include <iomanip> 
#include "Parameters_HC_NLO_X0_UFO.h"

// Initialize static instance
Parameters_HC_NLO_X0_UFO * Parameters_HC_NLO_X0_UFO::instance = 0; 

// Function to get static instance - only one instance per program
Parameters_HC_NLO_X0_UFO * Parameters_HC_NLO_X0_UFO::getInstance()
{
  if (instance == 0)
    instance = new Parameters_HC_NLO_X0_UFO(); 

  return instance; 
}

void Parameters_HC_NLO_X0_UFO::setIndependentParameters(SLHAReader& slha)
{
  // Define "zero"
  zero = 0; 
  ZERO = 0; 
  // Prepare a vector for indices
  vector<int> indices(2, 0); 
  mdl_WX0 = slha.get_block_entry("decay", 25, 4.070000e-03); 
  mdl_WW = slha.get_block_entry("decay", 24, 2.047600e+00); 
  mdl_WZ = slha.get_block_entry("decay", 23, 2.441404e+00); 
  mdl_WT = slha.get_block_entry("decay", 6, 1.491500e+00); 
  mdl_ymtau = slha.get_block_entry("yukawa", 15, 1.777000e+00); 
  mdl_ymt = slha.get_block_entry("yukawa", 6, 1.730000e+02); 
  mdl_ymb = slha.get_block_entry("yukawa", 5, 4.700000e+00); 
  aS = slha.get_block_entry("sminputs", 3, 1.180000e-01); 
  mdl_Gf = slha.get_block_entry("sminputs", 2, 1.166390e-05); 
  aEWM1 = slha.get_block_entry("sminputs", 1, 1.325070e+02); 
  mdl_MX0 = slha.get_block_entry("mass", 25, 1.250000e+02); 
  mdl_MZ = slha.get_block_entry("mass", 23, 9.118800e+01); 
  mdl_MTA = slha.get_block_entry("mass", 15, 1.777000e+00); 
  mdl_MT = slha.get_block_entry("mass", 6, 1.730000e+02); 
  mdl_MB = slha.get_block_entry("mass", 5, 4.700000e+00); 
  MU_R = slha.get_block_entry("loop", 1, 9.118800e+01); 
  mdl_kHdwI = slha.get_block_entry("frblock", 23, 1.230000e+00); 
  mdl_kHdwR = slha.get_block_entry("frblock", 22, 1.220000e+00); 
  mdl_kHdz = slha.get_block_entry("frblock", 21, 1.210000e+00); 
  mdl_kHda = slha.get_block_entry("frblock", 20, 1.200000e+00); 
  mdl_kAww = slha.get_block_entry("frblock", 19, 1.190000e+00); 
  mdl_kHww = slha.get_block_entry("frblock", 18, 1.180000e+00); 
  mdl_kAzz = slha.get_block_entry("frblock", 17, 1.170000e+00); 
  mdl_kHzz = slha.get_block_entry("frblock", 16, 1.160000e+00); 
  mdl_kAza = slha.get_block_entry("frblock", 13, 1.130000e+00); 
  mdl_kHza = slha.get_block_entry("frblock", 12, 1.120000e+00); 
  mdl_kAaa = slha.get_block_entry("frblock", 11, 1.110000e+00); 
  mdl_kHaa = slha.get_block_entry("frblock", 10, 1.100000e+00); 
  mdl_kAll = slha.get_block_entry("frblock", 9, 1.090000e+00); 
  mdl_kHll = slha.get_block_entry("frblock", 8, 1.080000e+00); 
  mdl_kAbb = slha.get_block_entry("frblock", 7, 1.070000e+00); 
  mdl_kHbb = slha.get_block_entry("frblock", 6, 1.060000e+00); 
  mdl_kAtt = slha.get_block_entry("frblock", 5, 1.050000e+00); 
  mdl_kHtt = slha.get_block_entry("frblock", 4, 1.040000e+00); 
  mdl_kSM = slha.get_block_entry("frblock", 3, 1.030000e+00); 
  mdl_cosa = slha.get_block_entry("frblock", 2, 1.020000e+00); 
  mdl_Lambda = slha.get_block_entry("frblock", 1, 1.000000e+03); 
  mdl_CKM11 = 1.; 
  mdl_conjg__CKM3x3 = 1.; 
  mdl_conjg__CKM11 = 1.; 
  mdl_lhv = 1.; 
  mdl_CKM3x3 = 1.; 
  mdl_conjg__CKM33 = 1.; 
  mdl_Ncol = 3.; 
  mdl_CA = 3.; 
  mdl_TF = 0.5; 
  mdl_CF = (4./3.); 
  mdl_complexi = std::complex<double> (0., 1.); 
  mdl_MZ__exp__2 = pow(mdl_MZ, 2.); 
  mdl_MZ__exp__4 = pow(mdl_MZ, 4.); 
  mdl_sqrt__2 = sqrt(2.); 
  mdl_MX0__exp__2 = pow(mdl_MX0, 2.); 
  mdl_cosa__exp__2 = pow(mdl_cosa, 2.); 
  mdl_sina = sqrt(1. - mdl_cosa__exp__2); 
  mdl_kHdw = mdl_complexi * mdl_kHdwI + mdl_kHdwR; 
  mdl_nb__2__exp__0_75 = pow(2., 0.75); 
  mdl_conjg__kHdw = conj(mdl_kHdw); 
  mdl_Ncol__exp__2_m_1 = pow(mdl_Ncol, 2.) - 1.; 
  mdl_MB__exp__2 = pow(mdl_MB, 2.); 
  mdl_MT__exp__2 = pow(mdl_MT, 2.); 
  mdl_Ncol__exp__2_m_1_0 = pow(mdl_Ncol, 2.) - 1.; 
  mdl_aEW = 1./aEWM1; 
  mdl_MW = sqrt(mdl_MZ__exp__2/2. + sqrt(mdl_MZ__exp__4/4. - (mdl_aEW * M_PI *
      mdl_MZ__exp__2)/(mdl_Gf * mdl_sqrt__2)));
  mdl_sqrt__aEW = sqrt(mdl_aEW); 
  mdl_ee = 2. * mdl_sqrt__aEW * sqrt(M_PI); 
  mdl_MW__exp__2 = pow(mdl_MW, 2.); 
  mdl_sw2 = 1. - mdl_MW__exp__2/mdl_MZ__exp__2; 
  mdl_cw = sqrt(1. - mdl_sw2); 
  mdl_sqrt__sw2 = sqrt(mdl_sw2); 
  mdl_sw = mdl_sqrt__sw2; 
  mdl_g1 = mdl_ee/mdl_cw; 
  mdl_gw = mdl_ee/mdl_sw; 
  mdl_vev = (2. * mdl_MW * mdl_sw)/mdl_ee; 
  mdl_vev__exp__2 = pow(mdl_vev, 2.); 
  mdl_lam = mdl_MX0__exp__2/(2. * mdl_vev__exp__2); 
  mdl_yb = (mdl_ymb * mdl_sqrt__2)/mdl_vev; 
  mdl_yt = (mdl_ymt * mdl_sqrt__2)/mdl_vev; 
  mdl_ytau = (mdl_ymtau * mdl_sqrt__2)/mdl_vev; 
  mdl_muH = sqrt(mdl_lam * mdl_vev__exp__2); 
  mdl_AxialZUp = (3./2.) * (-(mdl_ee * mdl_sw)/(6. * mdl_cw)) - (1./2.) *
      ((mdl_cw * mdl_ee)/(2. * mdl_sw));
  mdl_AxialZDown = (-1./2.) * (-(mdl_cw * mdl_ee)/(2. * mdl_sw)) + (-3./2.) *
      (-(mdl_ee * mdl_sw)/(6. * mdl_cw));
  mdl_VectorZUp = (1./2.) * ((mdl_cw * mdl_ee)/(2. * mdl_sw)) + (5./2.) *
      (-(mdl_ee * mdl_sw)/(6. * mdl_cw));
  mdl_VectorZDown = (1./2.) * (-(mdl_cw * mdl_ee)/(2. * mdl_sw)) + (-1./2.) *
      (-(mdl_ee * mdl_sw)/(6. * mdl_cw));
  mdl_VectorAUp = (2. * mdl_ee)/3.; 
  mdl_VectorADown = -(mdl_ee)/3.; 
  mdl_VectorWmDxU = (1./2.) * ((mdl_ee)/(mdl_sw * mdl_sqrt__2)); 
  mdl_AxialWmDxU = (-1./2.) * ((mdl_ee)/(mdl_sw * mdl_sqrt__2)); 
  mdl_VectorWpUxD = (1./2.) * ((mdl_ee)/(mdl_sw * mdl_sqrt__2)); 
  mdl_AxialWpUxD = -(1./2.) * ((mdl_ee)/(mdl_sw * mdl_sqrt__2)); 
  mdl_I1x33 = mdl_yb * mdl_conjg__CKM3x3; 
  mdl_I2x33 = mdl_yt * mdl_conjg__CKM3x3; 
  mdl_I3x33 = mdl_CKM3x3 * mdl_yt; 
  mdl_I4x33 = mdl_CKM3x3 * mdl_yb; 
  mdl_Vector_tbGp = mdl_I1x33 - mdl_I2x33; 
  mdl_Axial_tbGp = -mdl_I2x33 - mdl_I1x33; 
  mdl_Vector_tbGm = mdl_I3x33 - mdl_I4x33; 
  mdl_Axial_tbGm = -mdl_I4x33 - mdl_I3x33; 
  mdl_ee__exp__2 = pow(mdl_ee, 2.); 
  mdl_gAaa = mdl_ee__exp__2/(3. * pow(M_PI, 2.) * mdl_vev); 
  mdl_cw__exp__2 = pow(mdl_cw, 2.); 
  mdl_gAza = ((-5. + 8. * mdl_cw__exp__2) * sqrt(mdl_ee__exp__2 * mdl_Gf *
      mdl_MZ__exp__2))/(6. * mdl_nb__2__exp__0_75 * pow(M_PI, 2.) * mdl_vev);
  mdl_gHaa = (47. * mdl_ee__exp__2)/(72. * pow(M_PI, 2.) * mdl_vev); 
  mdl_gHza = ((-13. + 94. * mdl_cw__exp__2) * sqrt(mdl_ee__exp__2 * mdl_Gf *
      mdl_MZ__exp__2))/(36. * mdl_nb__2__exp__0_75 * pow(M_PI, 2.) * mdl_vev);
  mdl_gw__exp__2 = pow(mdl_gw, 2.); 
  mdl_sw__exp__2 = pow(mdl_sw, 2.); 
  mdl_MU_R__exp__2 = pow(MU_R, 2.); 
}
void Parameters_HC_NLO_X0_UFO::setIndependentCouplings()
{
  GC_3005a = -(mdl_complexi * mdl_sina * mdl_kAww)/mdl_Lambda; 
  GC_3005h2 = -(mdl_complexi * mdl_cosa * mdl_kHdw)/mdl_Lambda; 
  GC_3005h3 = -(mdl_complexi * mdl_cosa * mdl_kHww)/mdl_Lambda; 
  GC_3005h4 = -(mdl_complexi * mdl_cosa * mdl_conjg__kHdw)/mdl_Lambda; 
  GC_3006h1 = -((mdl_cosa * mdl_complexi * mdl_kHda)/mdl_Lambda); 
  GC_3007a = -(mdl_complexi * mdl_sina * mdl_kAzz)/mdl_Lambda; 
  GC_3007h2 = -(mdl_cosa * mdl_complexi * mdl_kHzz)/mdl_Lambda; 
  GC_3007h3 = -(mdl_cosa * mdl_complexi * mdl_kHdz)/mdl_Lambda; 
  GC_3 = -(mdl_ee * mdl_complexi); 
  GC_21 = -(mdl_cw * mdl_ee * mdl_complexi)/(2. * mdl_sw); 
  GC_22 = (mdl_cw * mdl_ee * mdl_complexi)/(2. * mdl_sw); 
  GC_23 = -(mdl_ee * mdl_complexi * mdl_sw)/(6. * mdl_cw); 
  GC_24 = (mdl_ee * mdl_complexi * mdl_sw)/(2. * mdl_cw); 
  GC_47 = (mdl_ee * mdl_complexi * mdl_conjg__CKM33)/(mdl_sw * mdl_sqrt__2); 
  GC_3005h1 = (mdl_complexi * mdl_cosa * mdl_kSM * mdl_ee__exp__2 *
      mdl_vev)/(2. * mdl_sw__exp__2);
  GC_3006a = -mdl_complexi * mdl_gAza * mdl_kAza * mdl_sina; 
  GC_3006h2 = -(mdl_cosa * mdl_complexi * mdl_gHza * mdl_kHza); 
  GC_3007h1 = mdl_cosa * mdl_ee__exp__2 * mdl_complexi * mdl_kSM * mdl_vev +
      (mdl_cosa * mdl_cw__exp__2 * mdl_ee__exp__2 * mdl_complexi * mdl_kSM *
      mdl_vev)/(2. * mdl_sw__exp__2) + (mdl_cosa * mdl_ee__exp__2 *
      mdl_complexi * mdl_kSM * mdl_sw__exp__2 * mdl_vev)/(2. * mdl_cw__exp__2);
}
void Parameters_HC_NLO_X0_UFO::setDependentParameters()
{
  mdl_sqrt__aS = sqrt(aS); 
  G = 2. * mdl_sqrt__aS * sqrt(M_PI); 
  mdl_G__exp__2 = pow(G, 2.); 
  mdl_G__exp__3 = pow(G, 3.); 
  mdl_G__exp__4 = pow(G, 4.); 
  mdl_gAgg = (mdl_G__exp__2)/(8. * mdl_vev * pow(M_PI, 2.)); 
  mdl_gHgg = -(mdl_G__exp__2)/(12. * mdl_vev * pow(M_PI, 2.)); 
}
void Parameters_HC_NLO_X0_UFO::setDependentCouplings()
{

}
void Parameters_HC_NLO_X0_UFO::set4lepMass(double m_m4l)
{
  mdl_MX0 = m_m4l;
  mdl_WX0 = setWidth(m_m4l);
  mdl_MX0__exp__2 = pow(mdl_MX0, 2.); 
  mdl_lam = mdl_MX0__exp__2/(2. * mdl_vev__exp__2); 

  mdl_muH = sqrt(mdl_lam * mdl_vev__exp__2);
}

long double Parameters_HC_NLO_X0_UFO::setWidth(double m_m4l)
{
  
  long double Higgs_width_Poly_Fit_Zone1_coeff0=-1.450308902710193E+03;
  long double Higgs_width_Poly_Fit_Zone1_coeff1=1.129291251156317E+02;
  long double Higgs_width_Poly_Fit_Zone1_coeff2=-3.893063071316150E+00;
  long double Higgs_width_Poly_Fit_Zone1_coeff3=7.798666884832531E-02;
  long double Higgs_width_Poly_Fit_Zone1_coeff4=-1.000455877406390E-03;
  long double Higgs_width_Poly_Fit_Zone1_coeff5=8.523735379647125E-06;
  long double Higgs_width_Poly_Fit_Zone1_coeff6=-4.823164754652171E-08;
  long double Higgs_width_Poly_Fit_Zone1_coeff7=1.747954506786346E-10;
  long double Higgs_width_Poly_Fit_Zone1_coeff8=-3.681723572169337E-13;
  long double Higgs_width_Poly_Fit_Zone1_coeff9=3.434207075968898E-16;
  
  long double Higgs_width_Poly_Fit_Zone2_coeff0=2.563291882845993E+02;
  long double Higgs_width_Poly_Fit_Zone2_coeff1=-1.037082025855304E+01;
  long double Higgs_width_Poly_Fit_Zone2_coeff2=1.780260502696301E-01;
  long double Higgs_width_Poly_Fit_Zone2_coeff3=-1.720311784419889E-03;
  long double Higgs_width_Poly_Fit_Zone2_coeff4=1.038418605369741E-05;
  long double Higgs_width_Poly_Fit_Zone2_coeff5=-4.092496883922424E-08;
  long double Higgs_width_Poly_Fit_Zone2_coeff6=1.067667966800388E-10;
  long double Higgs_width_Poly_Fit_Zone2_coeff7=-1.823343280081685E-13;
  long double Higgs_width_Poly_Fit_Zone2_coeff8=1.955637395597351E-16;
  long double Higgs_width_Poly_Fit_Zone2_coeff9=-1.193287048560413E-19;
  long double Higgs_width_Poly_Fit_Zone2_coeff10=3.156196649452213E-23;
	
  long double Higgs_width_Poly_Fit_Zone12_coeff0=-5.255605465437446E+02;
  long double Higgs_width_Poly_Fit_Zone12_coeff1=1.036972988796150E+01;
  long double Higgs_width_Poly_Fit_Zone12_coeff2=-6.817022987365029E-02;
  long double Higgs_width_Poly_Fit_Zone12_coeff3=1.493275723660056E-04;
  
  long double m_m4l__2 = m_m4l*m_m4l;
  long double m_m4l__3 = m_m4l__2*m_m4l;

  if( m_m4l < 156.5 ) return ( Higgs_width_Poly_Fit_Zone1_coeff0
			      + Higgs_width_Poly_Fit_Zone1_coeff1*m_m4l
			      + Higgs_width_Poly_Fit_Zone1_coeff2*m_m4l__2
			      + Higgs_width_Poly_Fit_Zone1_coeff3*m_m4l__3
			      + Higgs_width_Poly_Fit_Zone1_coeff4*m_m4l__2*m_m4l__2
			      + Higgs_width_Poly_Fit_Zone1_coeff5*m_m4l__2*m_m4l__3
			      + Higgs_width_Poly_Fit_Zone1_coeff6*m_m4l__2*m_m4l__2*m_m4l__2
			      + Higgs_width_Poly_Fit_Zone1_coeff7*m_m4l__2*m_m4l__2*m_m4l__3
			      + Higgs_width_Poly_Fit_Zone1_coeff8*m_m4l__2*m_m4l__2*m_m4l__2*m_m4l__2
			      + Higgs_width_Poly_Fit_Zone1_coeff9*m_m4l__2*m_m4l__2*m_m4l__2*m_m4l__3 );
  if( m_m4l >= 156.5 && m_m4l <= 162 ) return ( Higgs_width_Poly_Fit_Zone12_coeff0
					      + Higgs_width_Poly_Fit_Zone12_coeff1*m_m4l
					      + Higgs_width_Poly_Fit_Zone12_coeff2*m_m4l__2
					      + Higgs_width_Poly_Fit_Zone12_coeff3*m_m4l__3 );
  else return ( Higgs_width_Poly_Fit_Zone2_coeff0
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
  
}

// Routines for printing out parameters
void Parameters_HC_NLO_X0_UFO::printIndependentParameters()
{
  cout <<  "HC_NLO_X0_UFO model parameters independent of event kinematics:" <<
      endl;
  cout << setw(20) <<  "mdl_WX0 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_WX0 << endl;
  cout << setw(20) <<  "mdl_WW " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_WW << endl;
  cout << setw(20) <<  "mdl_WZ " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_WZ << endl;
  cout << setw(20) <<  "mdl_WT " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_WT << endl;
  cout << setw(20) <<  "mdl_ymtau " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_ymtau << endl;
  cout << setw(20) <<  "mdl_ymt " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_ymt << endl;
  cout << setw(20) <<  "mdl_ymb " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_ymb << endl;
  cout << setw(20) <<  "aS " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << aS << endl;
  cout << setw(20) <<  "mdl_Gf " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_Gf << endl;
  cout << setw(20) <<  "aEWM1 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << aEWM1 << endl;
  cout << setw(20) <<  "mdl_MX0 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MX0 << endl;
  cout << setw(20) <<  "mdl_MZ " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MZ << endl;
  cout << setw(20) <<  "mdl_MTA " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MTA << endl;
  cout << setw(20) <<  "mdl_MT " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MT << endl;
  cout << setw(20) <<  "mdl_MB " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MB << endl;
  cout << setw(20) <<  "MU_R " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << MU_R << endl;
  cout << setw(20) <<  "mdl_kHdwI " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHdwI << endl;
  cout << setw(20) <<  "mdl_kHdwR " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHdwR << endl;
  cout << setw(20) <<  "mdl_kHdz " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHdz << endl;
  cout << setw(20) <<  "mdl_kHda " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHda << endl;
  cout << setw(20) <<  "mdl_kAww " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kAww << endl;
  cout << setw(20) <<  "mdl_kHww " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHww << endl;
  cout << setw(20) <<  "mdl_kAzz " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kAzz << endl;
  cout << setw(20) <<  "mdl_kHzz " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHzz << endl;
  cout << setw(20) <<  "mdl_kAza " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kAza << endl;
  cout << setw(20) <<  "mdl_kHza " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHza << endl;
  cout << setw(20) <<  "mdl_kAaa " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kAaa << endl;
  cout << setw(20) <<  "mdl_kHaa " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHaa << endl;
  cout << setw(20) <<  "mdl_kAll " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kAll << endl;
  cout << setw(20) <<  "mdl_kHll " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHll << endl;
  cout << setw(20) <<  "mdl_kAbb " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kAbb << endl;
  cout << setw(20) <<  "mdl_kHbb " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHbb << endl;
  cout << setw(20) <<  "mdl_kAtt " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kAtt << endl;
  cout << setw(20) <<  "mdl_kHtt " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHtt << endl;
  cout << setw(20) <<  "mdl_kSM " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kSM << endl;
  cout << setw(20) <<  "mdl_cosa " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_cosa << endl;
  cout << setw(20) <<  "mdl_Lambda " <<  "= " << setiosflags(ios::fixed)
      << setw(10) << mdl_Lambda << endl;
  cout << setw(20) <<  "mdl_CKM11 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_CKM11 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM3x3 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_conjg__CKM3x3 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM11 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_conjg__CKM11 << endl;
  cout << setw(20) <<  "mdl_lhv " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_lhv << endl;
  cout << setw(20) <<  "mdl_CKM3x3 " <<  "= " << setiosflags(ios::fixed)
      << setw(10) << mdl_CKM3x3 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM33 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_conjg__CKM33 << endl;
  cout << setw(20) <<  "mdl_Ncol " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_Ncol << endl;
  cout << setw(20) <<  "mdl_CA " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_CA << endl;
  cout << setw(20) <<  "mdl_TF " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_TF << endl;
  cout << setw(20) <<  "mdl_CF " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_CF << endl;
  cout << setw(20) <<  "mdl_complexi " <<  "= " << setiosflags(ios::fixed)
      << setw(10) << mdl_complexi << endl;
  cout << setw(20) <<  "mdl_MZ__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MZ__exp__2 << endl;
  cout << setw(20) <<  "mdl_MZ__exp__4 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MZ__exp__4 << endl;
  cout << setw(20) <<  "mdl_sqrt__2 " <<  "= " << setiosflags(ios::fixed)
      << setw(10) << mdl_sqrt__2 << endl;
  cout << setw(20) <<  "mdl_MX0__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MX0__exp__2 << endl;
  cout << setw(20) <<  "mdl_cosa__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_cosa__exp__2 << endl;
  cout << setw(20) <<  "mdl_sina " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_sina << endl;
  cout << setw(20) <<  "mdl_kHdw " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_kHdw << endl;
  cout << setw(20) <<  "mdl_nb__2__exp__0_75 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_nb__2__exp__0_75 << endl;
  cout << setw(20) <<  "mdl_conjg__kHdw " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_conjg__kHdw << endl;
  cout << setw(20) <<  "mdl_Ncol__exp__2_m_1 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_Ncol__exp__2_m_1 << endl;
  cout << setw(20) <<  "mdl_MB__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MB__exp__2 << endl;
  cout << setw(20) <<  "mdl_MT__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MT__exp__2 << endl;
  cout << setw(20) <<  "mdl_Ncol__exp__2_m_1_0 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_Ncol__exp__2_m_1_0 <<
      endl;
  cout << setw(20) <<  "mdl_aEW " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_aEW << endl;
  cout << setw(20) <<  "mdl_MW " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MW << endl;
  cout << setw(20) <<  "mdl_sqrt__aEW " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_sqrt__aEW << endl;
  cout << setw(20) <<  "mdl_ee " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_ee << endl;
  cout << setw(20) <<  "mdl_MW__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MW__exp__2 << endl;
  cout << setw(20) <<  "mdl_sw2 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_sw2 << endl;
  cout << setw(20) <<  "mdl_cw " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_cw << endl;
  cout << setw(20) <<  "mdl_sqrt__sw2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_sqrt__sw2 << endl;
  cout << setw(20) <<  "mdl_sw " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_sw << endl;
  cout << setw(20) <<  "mdl_g1 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_g1 << endl;
  cout << setw(20) <<  "mdl_gw " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_gw << endl;
  cout << setw(20) <<  "mdl_vev " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_vev << endl;
  cout << setw(20) <<  "mdl_vev__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_vev__exp__2 << endl;
  cout << setw(20) <<  "mdl_lam " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_lam << endl;
  cout << setw(20) <<  "mdl_yb " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_yb << endl;
  cout << setw(20) <<  "mdl_yt " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_yt << endl;
  cout << setw(20) <<  "mdl_ytau " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_ytau << endl;
  cout << setw(20) <<  "mdl_muH " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_muH << endl;
  cout << setw(20) <<  "mdl_AxialZUp " <<  "= " << setiosflags(ios::fixed)
      << setw(10) << mdl_AxialZUp << endl;
  cout << setw(20) <<  "mdl_AxialZDown " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_AxialZDown << endl;
  cout << setw(20) <<  "mdl_VectorZUp " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_VectorZUp << endl;
  cout << setw(20) <<  "mdl_VectorZDown " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_VectorZDown << endl;
  cout << setw(20) <<  "mdl_VectorAUp " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_VectorAUp << endl;
  cout << setw(20) <<  "mdl_VectorADown " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_VectorADown << endl;
  cout << setw(20) <<  "mdl_VectorWmDxU " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_VectorWmDxU << endl;
  cout << setw(20) <<  "mdl_AxialWmDxU " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_AxialWmDxU << endl;
  cout << setw(20) <<  "mdl_VectorWpUxD " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_VectorWpUxD << endl;
  cout << setw(20) <<  "mdl_AxialWpUxD " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_AxialWpUxD << endl;
  cout << setw(20) <<  "mdl_I1x33 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_I1x33 << endl;
  cout << setw(20) <<  "mdl_I2x33 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_I2x33 << endl;
  cout << setw(20) <<  "mdl_I3x33 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_I3x33 << endl;
  cout << setw(20) <<  "mdl_I4x33 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_I4x33 << endl;
  cout << setw(20) <<  "mdl_Vector_tbGp " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_Vector_tbGp << endl;
  cout << setw(20) <<  "mdl_Axial_tbGp " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_Axial_tbGp << endl;
  cout << setw(20) <<  "mdl_Vector_tbGm " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_Vector_tbGm << endl;
  cout << setw(20) <<  "mdl_Axial_tbGm " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_Axial_tbGm << endl;
  cout << setw(20) <<  "mdl_ee__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_ee__exp__2 << endl;
  cout << setw(20) <<  "mdl_gAaa " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_gAaa << endl;
  cout << setw(20) <<  "mdl_cw__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_cw__exp__2 << endl;
  cout << setw(20) <<  "mdl_gAza " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_gAza << endl;
  cout << setw(20) <<  "mdl_gHaa " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_gHaa << endl;
  cout << setw(20) <<  "mdl_gHza " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_gHza << endl;
  cout << setw(20) <<  "mdl_gw__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_gw__exp__2 << endl;
  cout << setw(20) <<  "mdl_sw__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_sw__exp__2 << endl;
  cout << setw(20) <<  "mdl_MU_R__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MU_R__exp__2 << endl;
}
void Parameters_HC_NLO_X0_UFO::printIndependentCouplings()
{
  cout <<  "HC_NLO_X0_UFO model couplings independent of event kinematics:" <<
      endl;
  cout << setw(20) <<  "GC_3005a " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3005a << endl;
  cout << setw(20) <<  "GC_3005h2 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3005h2 << endl;
  cout << setw(20) <<  "GC_3005h3 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3005h3 << endl;
  cout << setw(20) <<  "GC_3005h4 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3005h4 << endl;
  cout << setw(20) <<  "GC_3006h1 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3006h1 << endl;
  cout << setw(20) <<  "GC_3007a " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3007a << endl;
  cout << setw(20) <<  "GC_3007h2 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3007h2 << endl;
  cout << setw(20) <<  "GC_3007h3 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3007h3 << endl;
  cout << setw(20) <<  "GC_3 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3 << endl;
  cout << setw(20) <<  "GC_21 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_21 << endl;
  cout << setw(20) <<  "GC_22 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_22 << endl;
  cout << setw(20) <<  "GC_23 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_23 << endl;
  cout << setw(20) <<  "GC_24 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_24 << endl;
  cout << setw(20) <<  "GC_47 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_47 << endl;
  cout << setw(20) <<  "GC_3005h1 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3005h1 << endl;
  cout << setw(20) <<  "GC_3006a " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3006a << endl;
  cout << setw(20) <<  "GC_3006h2 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3006h2 << endl;
  cout << setw(20) <<  "GC_3007h1 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_3007h1 << endl;
}
void Parameters_HC_NLO_X0_UFO::printDependentParameters()
{
  cout <<  "HC_NLO_X0_UFO model parameters dependent on event kinematics:" <<
      endl;
  cout << setw(20) <<  "mdl_sqrt__aS " <<  "= " << setiosflags(ios::fixed)
      << setw(10) << mdl_sqrt__aS << endl;
  cout << setw(20) <<  "G " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << G << endl;
  cout << setw(20) <<  "mdl_G__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_G__exp__2 << endl;
  cout << setw(20) <<  "mdl_G__exp__3 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_G__exp__3 << endl;
  cout << setw(20) <<  "mdl_G__exp__4 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_G__exp__4 << endl;
  cout << setw(20) <<  "mdl_gAgg " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_gAgg << endl;
  cout << setw(20) <<  "mdl_gHgg " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_gHgg << endl;
}
void Parameters_HC_NLO_X0_UFO::printDependentCouplings()
{
  cout <<  "HC_NLO_X0_UFO model couplings dependent on event kinematics:" <<
      endl;

}


