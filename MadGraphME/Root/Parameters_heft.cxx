//==========================================================================
// This file has been automatically generated for C++ by
// MadGraph5_aMC@NLO v. 2.2.1, 2014-09-25
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include <iostream> 
#include <iomanip> 
#include "Parameters_heft.h"

// Initialize static instance
Parameters_heft * Parameters_heft::instance = 0; 

// Function to get static instance - only one instance per program
Parameters_heft * Parameters_heft::getInstance()
{
  if (instance == 0)
    instance = new Parameters_heft(); 

  return instance; 
}

void Parameters_heft::setIndependentParameters(SLHAReader& slha)
{
  // Define "zero"
  zero = 0; 
  ZERO = 0; 
  // Prepare a vector for indices
  vector<int> indices(2, 0); 
  mdl_WH1 = slha.get_block_entry("decay", 9000006, 6.382339e-03); 
  mdl_WH = slha.get_block_entry("decay", 25, 6.382339e-03); 
  mdl_WW = slha.get_block_entry("decay", 24, 2.047600e+00); 
  mdl_WZ = slha.get_block_entry("decay", 23, 2.441404e+00); 
  mdl_WT = slha.get_block_entry("decay", 6, 1.491500e+00); 
  mdl_ymtau = slha.get_block_entry("yukawa", 15, 1.777000e+00); 
  mdl_ymt = slha.get_block_entry("yukawa", 6, 1.645000e+02); 
  mdl_ymb = slha.get_block_entry("yukawa", 5, 4.200000e+00); 
  aS = slha.get_block_entry("sminputs", 3, 1.180000e-01); 
  mdl_Gf = slha.get_block_entry("sminputs", 2, 1.166390e-05); 
  aEWM1 = slha.get_block_entry("sminputs", 1, 1.325070e+02); 
  mdl_MH = slha.get_block_entry("mass", 25, 1.250000e+02); 
  mdl_MZ = slha.get_block_entry("mass", 23, 9.118800e+01); 
  mdl_MTA = slha.get_block_entry("mass", 15, 1.777000e+00); 
  mdl_MT = slha.get_block_entry("mass", 6, 1.730000e+02); 
  mdl_MB = slha.get_block_entry("mass", 5, 4.700000e+00); 
  mdl_MP = 1. * mdl_MH; 
  mdl_conjg__CKM3x3 = 1.; 
  mdl_CKM3x3 = 1.; 
  mdl_complexi = std::complex<double> (0., 1.); 
  mdl_MZ__exp__2 = pow(mdl_MZ, 2.); 
  mdl_MZ__exp__4 = pow(mdl_MZ, 4.); 
  mdl_sqrt__2 = sqrt(2.); 
  mdl_MH__exp__4 = pow(mdl_MH, 4.); 
  mdl_MT__exp__4 = pow(mdl_MT, 4.); 
  mdl_MH__exp__2 = pow(mdl_MH, 2.); 
  mdl_MT__exp__2 = pow(mdl_MT, 2.); 
  mdl_MH__exp__12 = pow(mdl_MH, 12.); 
  mdl_MH__exp__10 = pow(mdl_MH, 10.); 
  mdl_MH__exp__8 = pow(mdl_MH, 8.); 
  mdl_MH__exp__6 = pow(mdl_MH, 6.); 
  mdl_MT__exp__6 = pow(mdl_MT, 6.); 
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
  mdl_v = (2. * mdl_MW * mdl_sw)/mdl_ee; 
  mdl_ee__exp__2 = pow(mdl_ee, 2.); 
  mdl_MW__exp__12 = pow(mdl_MW, 12.); 
  mdl_MW__exp__10 = pow(mdl_MW, 10.); 
  mdl_MW__exp__8 = pow(mdl_MW, 8.); 
  mdl_MW__exp__6 = pow(mdl_MW, 6.); 
  mdl_MW__exp__4 = pow(mdl_MW, 4.); 
  mdl_AH = (47. * mdl_ee__exp__2 * (1. - (2. * mdl_MH__exp__4)/(987. *
      mdl_MT__exp__4) - (14. * mdl_MH__exp__2)/(705. * mdl_MT__exp__2) + (213.
      * mdl_MH__exp__12)/(2.634632e7 * mdl_MW__exp__12) + (5. *
      mdl_MH__exp__10)/(119756. * mdl_MW__exp__10) + (41. *
      mdl_MH__exp__8)/(180950. * mdl_MW__exp__8) + (87. *
      mdl_MH__exp__6)/(65800. * mdl_MW__exp__6) + (57. * mdl_MH__exp__4)/(6580.
      * mdl_MW__exp__4) + (33. * mdl_MH__exp__2)/(470. * mdl_MW__exp__2)))/(72.
      * pow(M_PI, 2.) * mdl_v);
  mdl_v__exp__2 = pow(mdl_v, 2.); 
  mdl_lam = mdl_MH__exp__2/(2. * mdl_v__exp__2); 
  mdl_yb = (mdl_ymb * mdl_sqrt__2)/mdl_v; 
  mdl_yt = (mdl_ymt * mdl_sqrt__2)/mdl_v; 
  mdl_ytau = (mdl_ymtau * mdl_sqrt__2)/mdl_v; 
  mdl_muH = sqrt(mdl_lam * mdl_v__exp__2); 
  mdl_gw__exp__2 = pow(mdl_gw, 2.); 
  mdl_cw__exp__2 = pow(mdl_cw, 2.); 
  mdl_sw__exp__2 = pow(mdl_sw, 2.); 
}
void Parameters_heft::setIndependentCouplings()
{
  GC_1 = -(mdl_AH * mdl_complexi); 
  GC_4 = -(mdl_ee * mdl_complexi); 
  GC_40 = -(mdl_cw * mdl_ee * mdl_complexi)/(2. * mdl_sw); 
  GC_54 = (mdl_ee * mdl_complexi * mdl_sw)/(2. * mdl_cw); 
  GC_73 = mdl_ee__exp__2 * mdl_complexi * mdl_v + (mdl_cw__exp__2 *
      mdl_ee__exp__2 * mdl_complexi * mdl_v)/(2. * mdl_sw__exp__2) +
      (mdl_ee__exp__2 * mdl_complexi * mdl_sw__exp__2 * mdl_v)/(2. *
      mdl_cw__exp__2);
}
void Parameters_heft::setDependentParameters()
{
  mdl_sqrt__aS = sqrt(aS); 
  G = 2. * mdl_sqrt__aS * sqrt(M_PI); 
  mdl_G__exp__2 = pow(G, 2.); 
  mdl_GH = -(mdl_G__exp__2 * (1. + (13. * mdl_MH__exp__6)/(16800. *
      mdl_MT__exp__6) + mdl_MH__exp__4/(168. * mdl_MT__exp__4) + (7. *
      mdl_MH__exp__2)/(120. * mdl_MT__exp__2)))/(12. * pow(M_PI, 2.) * mdl_v);
  mdl_Gphi = -(mdl_G__exp__2 * (1. + mdl_MH__exp__6/(560. * mdl_MT__exp__6) +
      mdl_MH__exp__4/(90. * mdl_MT__exp__4) + mdl_MH__exp__2/(12. *
      mdl_MT__exp__2)))/(8. * pow(M_PI, 2.) * mdl_v);
}
void Parameters_heft::setDependentCouplings()
{
  GC_15 = mdl_complexi * mdl_G__exp__2 * mdl_GH; 
  GC_14 = -(G * mdl_GH); 
  GC_13 = -(mdl_complexi * mdl_GH); 
  GC_12 = mdl_complexi * mdl_G__exp__2; 
  GC_11 = mdl_complexi * G; 
  GC_10 = -G; 
}
void Parameters_heft::set4lepMass(double m_m4l)
{
  mdl_MH = m_m4l;
  mdl_WH = setWidth(m_m4l);
  mdl_WH1 = 1. * mdl_WH;
  mdl_MP = 1. * mdl_MH;
  mdl_MH__exp__4 = pow(mdl_MH, 4.);
  mdl_MH__exp__2 = pow(mdl_MH, 2.);
  mdl_MH__exp__12 = pow(mdl_MH, 12.);
  mdl_MH__exp__10 = pow(mdl_MH, 10.);
  mdl_MH__exp__8 = pow(mdl_MH, 8.);
  mdl_MH__exp__6 = pow(mdl_MH, 6.);
  mdl_MT__exp__6 = pow(mdl_MT, 6.);
  mdl_AH = (47. * mdl_ee__exp__2 * (1. - (2. * mdl_MH__exp__4)/(987. * mdl_MT__exp__4) - (14. *
      mdl_MH__exp__2)/(705. * mdl_MT__exp__2) + (213. * mdl_MH__exp__12)/(2.634632e7 *
      mdl_MW__exp__12) + (5. * mdl_MH__exp__10)/(119756. * mdl_MW__exp__10) + (41. *
      mdl_MH__exp__8)/(180950. * mdl_MW__exp__8) + (87. * mdl_MH__exp__6)/(65800. *
      mdl_MW__exp__6) + (57. * mdl_MH__exp__4)/(6580. * mdl_MW__exp__4) + (33. *
      mdl_MH__exp__2)/(470. * mdl_MW__exp__2)))/(72. * pow(M_PI, 2.) * mdl_v);
  mdl_lam = mdl_MH__exp__2/(2. * mdl_v__exp__2);
  mdl_muH = sqrt(mdl_lam * mdl_v__exp__2);
}

long double Parameters_heft::setWidth(double m_m4l){
  
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
void Parameters_heft::printIndependentParameters()
{
  cout <<  "heft model parameters independent of event kinematics:" << endl; 
  cout << setw(20) <<  "mdl_WH1 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_WH1 << endl;
  cout << setw(20) <<  "mdl_WH " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_WH << endl;
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
  cout << setw(20) <<  "mdl_MH " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MH << endl;
  cout << setw(20) <<  "mdl_MZ " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MZ << endl;
  cout << setw(20) <<  "mdl_MTA " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MTA << endl;
  cout << setw(20) <<  "mdl_MT " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MT << endl;
  cout << setw(20) <<  "mdl_MB " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MB << endl;
  cout << setw(20) <<  "mdl_MP " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_MP << endl;
  cout << setw(20) <<  "mdl_conjg__CKM3x3 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_conjg__CKM3x3 << endl;
  cout << setw(20) <<  "mdl_CKM3x3 " <<  "= " << setiosflags(ios::fixed)
      << setw(10) << mdl_CKM3x3 << endl;
  cout << setw(20) <<  "mdl_complexi " <<  "= " << setiosflags(ios::fixed)
      << setw(10) << mdl_complexi << endl;
  cout << setw(20) <<  "mdl_MZ__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MZ__exp__2 << endl;
  cout << setw(20) <<  "mdl_MZ__exp__4 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MZ__exp__4 << endl;
  cout << setw(20) <<  "mdl_sqrt__2 " <<  "= " << setiosflags(ios::fixed)
      << setw(10) << mdl_sqrt__2 << endl;
  cout << setw(20) <<  "mdl_MH__exp__4 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MH__exp__4 << endl;
  cout << setw(20) <<  "mdl_MT__exp__4 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MT__exp__4 << endl;
  cout << setw(20) <<  "mdl_MH__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MH__exp__2 << endl;
  cout << setw(20) <<  "mdl_MT__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MT__exp__2 << endl;
  cout << setw(20) <<  "mdl_MH__exp__12 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MH__exp__12 << endl;
  cout << setw(20) <<  "mdl_MH__exp__10 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MH__exp__10 << endl;
  cout << setw(20) <<  "mdl_MH__exp__8 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MH__exp__8 << endl;
  cout << setw(20) <<  "mdl_MH__exp__6 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MH__exp__6 << endl;
  cout << setw(20) <<  "mdl_MT__exp__6 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MT__exp__6 << endl;
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
  cout << setw(20) <<  "mdl_v " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_v << endl;
  cout << setw(20) <<  "mdl_ee__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_ee__exp__2 << endl;
  cout << setw(20) <<  "mdl_MW__exp__12 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MW__exp__12 << endl;
  cout << setw(20) <<  "mdl_MW__exp__10 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MW__exp__10 << endl;
  cout << setw(20) <<  "mdl_MW__exp__8 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MW__exp__8 << endl;
  cout << setw(20) <<  "mdl_MW__exp__6 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MW__exp__6 << endl;
  cout << setw(20) <<  "mdl_MW__exp__4 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_MW__exp__4 << endl;
  cout << setw(20) <<  "mdl_AH " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_AH << endl;
  cout << setw(20) <<  "mdl_v__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_v__exp__2 << endl;
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
  cout << setw(20) <<  "mdl_gw__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_gw__exp__2 << endl;
  cout << setw(20) <<  "mdl_cw__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_cw__exp__2 << endl;
  cout << setw(20) <<  "mdl_sw__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_sw__exp__2 << endl;
}
void Parameters_heft::printIndependentCouplings()
{
  cout <<  "heft model couplings independent of event kinematics:" << endl; 
  cout << setw(20) <<  "GC_1 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_1 << endl;
  cout << setw(20) <<  "GC_4 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_4 << endl;
  cout << setw(20) <<  "GC_40 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_40 << endl;
  cout << setw(20) <<  "GC_54 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_54 << endl;
  cout << setw(20) <<  "GC_73 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_73 << endl;
}
void Parameters_heft::printDependentParameters()
{
  cout <<  "heft model parameters dependent on event kinematics:" << endl; 
  cout << setw(20) <<  "mdl_sqrt__aS " <<  "= " << setiosflags(ios::fixed)
      << setw(10) << mdl_sqrt__aS << endl;
  cout << setw(20) <<  "G " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << G << endl;
  cout << setw(20) <<  "mdl_G__exp__2 " <<  "= " <<
      setiosflags(ios::fixed) << setw(10) << mdl_G__exp__2 << endl;
  cout << setw(20) <<  "mdl_GH " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_GH << endl;
  cout << setw(20) <<  "mdl_Gphi " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << mdl_Gphi << endl;
}
void Parameters_heft::printDependentCouplings()
{
  cout <<  "heft model couplings dependent on event kinematics:" << endl; 
  cout << setw(20) <<  "GC_15 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_15 << endl;
  cout << setw(20) <<  "GC_14 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_14 << endl;
  cout << setw(20) <<  "GC_13 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_13 << endl;
  cout << setw(20) <<  "GC_12 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_12 << endl;
  cout << setw(20) <<  "GC_11 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_11 << endl;
  cout << setw(20) <<  "GC_10 " <<  "= " << setiosflags(ios::fixed) <<
      setw(10) << GC_10 << endl;
}


