#include "HZZUtils/BkgCrossSection.h"

using namespace std;

double CrossSections::bkgCrossSection(int RunNumber, LHCEnergy energy, bool PrintSummary)
{
/*
  if(energy != CrossSections::SevenTeV && energy != CrossSections::EightTeV) 
    {
      std::cout << "Unknown LHC Energy" << std::endl;
      return 0.;
    }
  else if(energy == CrossSections::SevenTeV)
    return CrossSections::GetBkgCrossSection7TeV(RunNumber,PrintSummary);
  else if(energy == CrossSections::EightTeV)
    return CrossSections::GetBkgCrossSection8TeV(RunNumber,PrintSummary);

  return -1; // yes, this is an error code
*/

 if(energy != CrossSections::SevenTeV && energy != CrossSections::EightTeV && energy != CrossSections::ThirteenTeV)
    {
      std::cout << "Unknown LHC Energy" << std::endl;
      return 0.;
    }
  else if(energy == CrossSections::SevenTeV)
    return CrossSections::GetBkgCrossSection7TeV(RunNumber,PrintSummary);
  else if(energy == CrossSections::EightTeV)
    return CrossSections::GetBkgCrossSection8TeV(RunNumber,PrintSummary);
  else if(energy == CrossSections::ThirteenTeV) 
    return CrossSections::GetBkgCrossSection13TeV(RunNumber,PrintSummary);
  else if(energy == CrossSections::ThirteenHalfTeV)
    return CrossSections::GetBkgCrossSection13_5TeV(RunNumber,PrintSummary);
  else if(energy == CrossSections::FourteenTeV)
    return CrossSections::GetBkgCrossSection14TeV(RunNumber,PrintSummary);


 return -1; // yes, this is an error code
  
}

double CrossSections::GetBkgCrossSection7TeV(int RunNumber,bool PrintSummary)
{
  //EVERYTHING in fb  
  double crossSection=-1.0;
  std::string name="";
  
  if (RunNumber==107650){
    name="Alpgen+Jimmy Zee + 0	partons ";
    crossSection=827375.;
  }else if (RunNumber==107651){
    name="Alpgen+Jimmy Zee + 1	partons ";
    crossSection=166625.;
  }else if (RunNumber==107652){
    name="Alpgen+Jimmy Zee + 2	partons ";
    crossSection=50375.;
  }else if (RunNumber==107653){
    name="Alpgen+Jimmy Zee + 3	partons ";
    crossSection=14000.;
  }else if (RunNumber==107654){
    name="Alpgen+Jimmy Zee + 4	partons ";
    crossSection=3375.;
  }else if (RunNumber==107655){
    name="Alpgen+Jimmy Zee + 5	partons ";
    crossSection=1000.;
  }else if (RunNumber==107660){
    name="Alpgen+Jimmy Zmumu + 0	partons ";
    crossSection=822125;
  }else if (RunNumber==107661){
    name="Alpgen+Jimmy Zmumu + 1	partons ";
    crossSection=166000.;
  }else if (RunNumber==107662){
    name="Alpgen+Jimmy Zmumu + 2	 partons ";
    crossSection=49500.;
  }else if (RunNumber==107663){
    name="Alpgen+Jimmy Zmumu + 3	partons "; 
    crossSection=13875.;
  }else if (RunNumber==107664){
    name="Alpgen+Jimmy Zmumu + 4	partons ";
    crossSection=3500.;
  }else if (RunNumber==107665){
    name="Alpgen+Jimmy Zmumu + 5	partons ";
    crossSection=1000.;
  }else if (RunNumber==107670){
    name="Alpgen+Jimmy Ztautau + 0	partons ";
    crossSection=828125.;
  }else if (RunNumber==107671){
    name="Alpgen+Jimmy Ztautau + 1	partons ";
    crossSection=167375.;
  }else if (RunNumber==107672){
    name="Alpgen+Jimmy Ztautau + 2	partons ";
    crossSection=50375.;
  }else if (RunNumber==107673){
    name="Alpgen+Jimmy Ztautau + 3	partons ";
    crossSection=13750;
  }else if (RunNumber==107674){
    name="Alpgen+Jimmy Ztautau + 4	partons ";
    crossSection=3500.;
  }else if (RunNumber==107675){
    name="Alpgen+Jimmy Ztautau + 5	partons ";
    crossSection=1000.;
  }else if (RunNumber==181420){
      name="Zbb, AlpgenPythia_Auto_P2011C_4lFilte Z->ee Np0 ";
      crossSection=6.3027e3*4.6996e-03*1.6;
  }else if (RunNumber==181421){
      name="Zbb, AlpgenPythia_Auto_P2011C_4lFilte Z->ee Np1 ";
      crossSection=2.1842e3*9.6297e-3*1.6;
  }else if (RunNumber==181422){
      name="Zbb, AlpgenPythia_Auto_P2011C_4lFilte Z->ee Np2 ";
      crossSection=6.9232e2*1.4135e-2*1.6;
  }else if (RunNumber==181425){
      name="Zbb, AlpgenPythia_Auto_P2011C_4lFilte Z->mumu Np0 ";
      crossSection=6.3027e3*4.7314e-3*1.6;
  }else if (RunNumber==181426){
      name="Zbb, AlpgenPythia_Auto_P2011C_4lFilte Z->mumu Np1 ";
      crossSection=2.1842e3*9.6874e-3*1.6;
  }else if (RunNumber==181427){
      name="Zbb, AlpgenPythia_Auto_P2011C_4lFilte Z->mumu Np2 ";
      crossSection=6.9244e2*1.4277e-2*1.6;
  }else if (RunNumber==181430){
      name="Zbb, AlpgenPythia_Auto_P2011C_3lFilter_4lVeto Z->ee Np0 ";
      crossSection=6.3013e3*1.0241e-1*1.6;
  }else if (RunNumber==181431){
      name="Zbb, AlpgenPythia_Auto_P2011C_3lFilter_4lVeto Z->ee Np1 ";
      crossSection=2.1891e3*1.5018e-1*1.6;
  }else if (RunNumber==181432){
      name="Zbb, AlpgenPythia_Auto_P2011C_3lFilter_4lVeto Z->ee Np2 ";
      crossSection=6.9257e2*1.6789e-1*1.6;
  }else if (RunNumber==181435){
      name="Zbb, AlpgenPythia_Auto_P2011C_3lFilter_4lVeto Z->mm Np0 ";
      crossSection=6.3035e3*1.0252e-1*1.6;
  }else if (RunNumber==181436){
      name="Zbb, AlpgenPythia_Auto_P2011C_3lFilter_4lVeto Z->mm Np1 ";
      crossSection=2.1850e3*1.5030e-1*1.6;
  }else if (RunNumber==181437){
      name="Zbb, AlpgenPythia_Auto_P2011C_3lFilter_4lVeto Z->mm Np2 ";
      crossSection=6.9274e2*1.6865e-1*1.6;
  }else if (RunNumber==116960){
    name="Zbb, Z->ee (ll > 30 !GeV) + 0 parton [m_4l 60/12 !GeV] ";
    crossSection=20.701*1.4;
  }else if (RunNumber==116961){
    name="Zbb, Z->ee (ll > 30 !GeV) + 1 parton [m_4l 60/12 !GeV] ";
    crossSection=18.8029*1.4;
  }else if (RunNumber==116962){
    name="Zbb, Z->ee (ll > 30 !GeV) + 2 parton [m_4l 60/12 !GeV] ";
    crossSection=10.505*1.4;
  }else if (RunNumber==116963){
    name="Zbb, Z->ee (ll > 30 !GeV) + 3 parton [m_4l 60/12 !GeV] ";
    crossSection=7.30463*1.4;
  }else if (RunNumber==116965){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 0 parton [m_4l 60/12 !GeV] ";
    crossSection=21.516*1.4;
  }else if (RunNumber==116966){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 1 parton [m_4l 60/12 !GeV] ";
    crossSection=19.6674*1.4;
  }else if (RunNumber==116967){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 2 parton [m_4l 60/12 !GeV] ";
    crossSection=10.516*1.4;
  }else if (RunNumber==116968){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 3 parton [m_4l 60/12 !GeV] ";
    crossSection=7.93834*1.4;
  }else if (RunNumber==116950){
    name="Zbb, Z->ee (ll > 30 !GeV) + 0 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=756.32*1.4;
  }else if (RunNumber==116951){
    name="Zbb, Z->ee (ll > 30 !GeV) + 1 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=432.25*1.4;
  }else if (RunNumber==116952){
    name="Zbb, Z->ee (ll > 30 !GeV) + 2 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=176*1.4;
  }else if (RunNumber==116953){ 
    name="Zbb, Z->ee (ll > 30 !GeV) + 3 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=96.75*1.4;
  }else if (RunNumber==116955){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 0 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=730.24*1.4;
  }else if (RunNumber==116956){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 1 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=432.25*1.4;
  }else if (RunNumber==116957){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 2 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=179.3*1.4;
  }else if (RunNumber==116958){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 3 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=92.3962*1.4;
  }else if (RunNumber==128130){ 
    name="AlpgenJimmyLowMassDYeebbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128131){ 
    name="AlpgenJimmyLowMassDYeebbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128132){ 
    name="AlpgenJimmyLowMassDYeebbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128133){ 
    name="AlpgenJimmyLowMassDYeebbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==128135){ 
    name="AlpgenJimmyLowMassDYmumubbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128136){ 
    name="AlpgenJimmyLowMassDYmumubbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128137){ 
    name="AlpgenJimmyLowMassDYmumubbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128138){ 
    name="AlpgenJimmyLowMassDYmumubbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==128140){ 
    name="AlpgenJimmyLowMassDYtautaubbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128141){ 
    name="AlpgenJimmyLowMassDYtautaubbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128142){ 
    name="AlpgenJimmyLowMassDYtautaubbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128143){ 
    name="AlpgenJimmyLowMassDYtautaubbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==105200){ 
    name="ttbar (at least 1lepton filter) ";
    crossSection=91550.6;
  }else if (RunNumber==109345){ 
    name="ttbar (with Mll > 60 !GeV filter) ";
    crossSection=12707.2;
  }else if (RunNumber==109346){ 
    name="ttbar (with Mll > 60 !GeV filter and Mll > 12 !GeV) ";
    crossSection=515.2;
  }else if (RunNumber==117050){
      name="ttbar PowHeg_Pythia_P2011C";
      crossSection=80.07*1.202*1.3;
  }else if (RunNumber==109292){
    name="ZZ->4l 3LepFilter ";
    crossSection=91.54;
  }else if (RunNumber==126399){ 
    name="PowHegBoxZZeemm_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126400){ 
    name="PowHegBoxZZeeee_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126401){ 
    name="PowHegBoxZmmmm_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126859){ 
    name="PowHegZZ_4e_trilep5GeV_Pythia ";
    crossSection=46.6; 
  } else if (RunNumber==126860){ 
    name="PowHegZZ_4mu_trilep5GeV_Pythia ";
    crossSection=46.6; 
  }else if (RunNumber==126861){ 
    name="PowHegZZ_2e2mu_trilep5GeV_Pythia ";
    crossSection=99.1; 
  }else if (RunNumber==126862){ 
    name="PowHegZZ_2mu2tau_trilep5GeV_Pythia ";
    crossSection=99.1*0.124/0.617; 
  }else if (RunNumber==126863){ 
    name="PowHegZZ_2e2tau_trilep5GeV_Pythia ";
    crossSection=99.1*0.124/0.617; 
  }else if (RunNumber==126864){ 
    name="PowHegZZ_4tau_trilep5GeV_Pythia ";
    crossSection=44.6*0.0126/0.705;
  }else if (RunNumber==181281){
    name="PowhegPythia6_ZZ_4e_m4l100_150_mll4_4pt3 ";
    crossSection=4.475; 
  }else if (RunNumber==181282){
    name="PowhegPythia6_ZZ_4mu_m4l100_150_mll4_4pt3 ";
    crossSection=4.651;
  }else if (RunNumber==181283){
    name="PowhegPythia6_ZZ_2e2mu_m4l100_150_mll4_4pt3 ";
    crossSection=9.154;
  }else if (RunNumber==181284){
    name="PowhegPythia6_ZZ_2mu2tau_m4l100_150_mll4_4pt3 ";
    crossSection=0.768;
  }else if (RunNumber==181285){
    name="PowhegPythia6_ZZ_2e2tau_m4l100_150_mll4_4pt3 ";
    crossSection=0.764;
  }else if (RunNumber==181286){
    name="PowhegPythia6_ZZ_4tau_m4l100_150_mll4_4pt3 ";
    crossSection=0.0176;
  }else if (RunNumber==181287){
    name="PowhegPythia6_ZZ_4e_m4l500_50000_mll4_4pt3 ";
    crossSection=0.310;
  }else if (RunNumber==181288){
    name="PowhegPythia6_ZZ_4mu_m4l500_50000_mll4_4pt3 ";
    crossSection=0.329;
  }else if (RunNumber==181289){
    name="PowhegPythia6_ZZ_2e2mu_m4l500_50000_mll4_4pt3 ";
    crossSection=0.639;
  }
  else if (RunNumber==126937){
    name="PowhegPythia8_AU2CT10_ZZ_4e_mll4_2pt5";
    crossSection=59.59;
  }
  else if (RunNumber==126938){
    name="PowhegPythia8_AU2CT10_ZZ_2e2mu_mll4_2pt5";
    crossSection=124.51;
  }
  else if (RunNumber==126939){
    name="PowhegPythia8_AU2CT10_ZZ_2e2tau_mll4_2pt5";
    crossSection=87.05;
  }
  else if (RunNumber==126940){
    name="PowhegPythia8_AU2CT10_ZZ_4mu_mll4_2pt5";
    crossSection=59.86;
  }
  else if (RunNumber==126941){
    name="PowhegPythia8_AU2CT10_ZZ_2mu2tau_mll4_2pt5";
    crossSection=88.06;
  }
  else if (RunNumber==126942){
    name="PowhegPythia8_AU2CT10_ZZ_4tau_mll4_2pt5";
    crossSection=6.77;
  }
  else if(RunNumber==167162 ) {
    name="PowhegPythia8 ZZ->4e with 100-150 mass filter";
    crossSection=4.49;
  }
  else if(RunNumber==167165 ) {
    name="PowhegPythia8 ZZ->4mu with 100-150 mass filter";
    crossSection=4.67;
  }
  else if(RunNumber==167163 ) {
    name="PowhegPythia8 ZZ->2e2mu with 100-150 mass filter";
    crossSection=9.20;
  }
  else if(RunNumber==167164 ) {
    name="PowhegPythia8 ZZ->2e2tau with 100-150 mass filter";
    crossSection=0.769;
  }
  else if(RunNumber==167166 ) {
    name="PowhegPythia8 ZZ->2mu2tau with 100-150 mass filter";
    crossSection=0.775;
  }
  else if(RunNumber==167167 ) {
    name="PowhegPythia8 ZZ->4tau with 100-150 mass filter";
    crossSection=0.019;
  }
  else if(RunNumber==169690 ) {
    name="PowhegPythia8 ZZ->4e with 500-10000 mass filter";
    crossSection=0.31; //5.5084E-03*7.7000E-05 nb
  }
  else if(RunNumber==169691 ) {
    name="PowhegPythia8 ZZ->2e2mu with 500-10000 mass filter";
    crossSection=0.64; //4.7629E-03*1.7580E-04 nb
  }
  else if(RunNumber==169692 ) {
    name="PowhegPythia8 ZZ->4mu with 500-10000 mass filter";
    crossSection=0.33; //5.8613E-03*7.6630E-05 nb
  }

  else if (RunNumber==128813){ 
    name="SherpaZZllll ";
    crossSection=-1;
  }else if (RunNumber==161988){ 
    name="Sherpa_CT10_llll_ZZ_EW6_noHiggs ";
    crossSection=0.77; // https://savannah.cern.ch/task/index.php?30125
  }else if (RunNumber==116600){ 
    name="gg2ZZ_JIMMY_ZZ4lep [2e2mu,2e2tau,2mu2tau] (gg2ZZv2.0) ";
    crossSection=-1; // don't use this sample - check 116601,116602,116603
  }else if (RunNumber==116601){ 
    name="gg2ZZ_JIMMY_ZZ4lep [4e] (gg2ZZv2.0) ";
    crossSection=0.86/2.;
  }else if (RunNumber==116602){ 
    name="gg2ZZ_JIMMY_ZZ4lep [4mu] (gg2ZZv2.0) ";
    crossSection=0.86/2.;
  }else if (RunNumber==116603){ 
    name="gg2ZZ_JIMMY_ZZ4lep [2e2mu] (gg2ZZv2.0) ";
    crossSection=0.86;
  }else if (RunNumber==128593){ 
    name="PythiaZZall_EF_15_5 ";
    crossSection=9.23e3*1.56*0.14657;
  }else if (RunNumber==109300){ 
    name="AlpgenJimmyZeebbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109301){ 
    name="AlpgenJimmyZeebbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109302){ 
    name="AlpgenJimmyZeebbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109303){ 
    name="AlpgenJimmyZeebbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==109305){ 
    name="AlpgenJimmyZmumubbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109306){ 
    name="AlpgenJimmyZmumubbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109307){ 
    name="AlpgenJimmyZmumubbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109308){ 
    name="AlpgenJimmyZmumubbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==109310){ 
    name="AlpgenJimmyZtautaubbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109311){ 
    name="AlpgenJimmyZtautaubbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109312){ 
    name="AlpgenJimmyZtautaubbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109313){ 
    name="AlpgenJimmyZtautaubbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==116250){ 
    name="ZeeNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116251){ 
    name="ZeeNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116252){ 
    name="ZeeNp2 M10to40 pt20 ";
    crossSection=41100*1.22;
  }else if (RunNumber==116253){ 
    name="ZeeNp3 M10to40 pt20 ";
    crossSection=8460*1.22;
  }else if (RunNumber==116254){ 
    name="ZeeNp4 M10to40 pt20 ";
    crossSection=1840*1.22;
  }else if (RunNumber==116255){ 
    name="ZeeNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }else if (RunNumber==116260){ 
    name="ZmumuNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116261){ 
    name="ZmumuNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116262){ 
    name="ZmumuNp2 M10to40 pt20 ";
    crossSection=40950*1.22;
  }else if (RunNumber==116263){ 
    name="ZmumuNp3 M10to40 pt20 ";
    crossSection=8410*1.22;
  }else if (RunNumber==116264){ 
    name="ZmumuNp4 M10to40 pt20 ";
    crossSection=1850*1.22;
  }else if (RunNumber==116265){ 
    name="ZmumuNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }else if (RunNumber==116270){ 
    name="ZtautauNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116271){ 
    name="ZtautauNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116272){ 
    name="ZtautauNp2 M10to40 pt20 ";
    crossSection=41100*1.22;
  }else if (RunNumber==116273){ 
    name="ZtautauNp3 M10to40 pt20 ";
    crossSection=8460*1.22;
  }else if (RunNumber==116274){ 
    name="ZtautauNp4 M10to40 pt20 ";
    crossSection=1840*1.22;
  }else if (RunNumber==116275){ 
    name="ZtautauNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }else if (RunNumber==128971){
    name="mc11_7TeV.128971.PythiaWZ_inclusive ";
    crossSection=12.006e3;
  }
  else if (RunNumber==105987){
    name="mc11_7TeV.105987.WZ_Herwig ";
    crossSection=11.485e3;
  }
   else if (RunNumber==181767){
    name="Pythia8_AU2CTEQ6L1_DPI_Z_Z_4l";
    crossSection=0.786;
  } 
  if (PrintSummary){
    if (crossSection!=-1){
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"               Cross section x Branching Ratio = "<< crossSection <<" fb^-1 "<< std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
    }else{
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"                    NO Cross section !!!  " << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    }
  }
  return crossSection;
}

double CrossSections::GetBkgCrossSection8TeV(int RunNumber,bool PrintSummary)
{

  //EVERYTHING in fb  
  double crossSection=-1.0;
  std::string name="";
  
  if (RunNumber==105200){
    name="McAtNloJimmy_CT10_ttbar_LeptonFilter";
    crossSection=238.06e3*0.648;
  }
  else if (RunNumber==110001){
    name="McAtNloJimmy_CT10_ttbar_dilepton";
    crossSection=238.06e3*0.1045;
  }
  else if (RunNumber==181087){
    name="PowhegPythia_P2011C_ttbar_dilepton";
    crossSection=252.89*0.105*1.e3;
  }
   else if (RunNumber==146369){
    name="ttbar_4LepMass_Mll50GeV12GeV";
    crossSection=238.06e3*0.1045*0.0306;
  }
  else if (RunNumber==126937){
    name="PowhegPythia8_AU2CT10_ZZ_4e_mll4_2pt5";
    crossSection=69.78;
  }
  else if (RunNumber==126938){
    name="PowhegPythia8_AU2CT10_ZZ_2e2mu_mll4_2pt5";
    crossSection=145.39;
  }
  else if (RunNumber==126939){
    name="PowhegPythia8_AU2CT10_ZZ_2e2tau_mll4_2pt5";
    crossSection=102.13;
  }
  else if (RunNumber==126940){
    name="PowhegPythia8_AU2CT10_ZZ_4mu_mll4_2pt5";
    crossSection=70.07;
  }
  else if (RunNumber==126941){
    name="PowhegPythia8_AU2CT10_ZZ_2mu2tau_mll4_2pt5";
    crossSection=103.25;
  }
  else if (RunNumber==126942){
    name="PowhegPythia8_AU2CT10_ZZ_4tau_mll4_2pt5";
    crossSection=8.09;
  }
  else if (RunNumber==116601){
    name="gg2ZZJimmy_AUET2CT10_ZZ4e";
    crossSection=1.345/2.; // From N. Kauer
  }
  else if (RunNumber==116602){
    name="gg2ZZJimmy_AUET2CT10_ZZ4mu";
    crossSection=1.345/2.; // From N. Kauer
  }
  else if (RunNumber==116603){
    name="gg2ZZJimmy_AUET2CT10_ZZ2e2mu";
    crossSection=1.345; // From N. Kauer
  }else if (RunNumber==161988){ 
    name="Sherpa_CT10_llll_ZZ_EW6_noHiggs ";
    crossSection=1.05; // https://savannah.cern.ch/task/index.php?30125
  }
  else if (RunNumber==117650){
    name="AlpgenPythia_P2011C_ZeeNp0";
    crossSection=718890*1.18;
  }
  else if (RunNumber==117651){
    name="AlpgenPythia_P2011C_ZeeNp1";
    crossSection=175600.*1.18;
  }
  else if (RunNumber==117652){
    name="AlpgenPythia_P2011C_ZeeNp2";
    crossSection=58849.*1.18;
  }
  else if (RunNumber==117653){
    name="AlpgenPythia_P2011C_ZeeNp3";
    crossSection=15560.*1.18;
  }
  else if (RunNumber==117654){
    name="AlpgenPythia_P2011C_ZeeNp4";
    crossSection=3932.*1.18;
  }
  else if (RunNumber==117655){
    name="AlpgenPythia_P2011C_ZeeNp5";
    crossSection=1199.*1.18;
  }
  else if (RunNumber==117660){
    name="AlpgenPythia_P2011C_ZmumuNp0";
    crossSection=718910.*1.18;
  }
  else if (RunNumber==117661){
    name="AlpgenPythia_P2011C_ZmumuNp1";
    crossSection=175810.*1.18;
  }
  else if (RunNumber==117662){
    name="AlpgenPythia_P2011C_ZmumuNp2";
    crossSection=58805.*1.18;
  }
  else if (RunNumber==117663){
    name="AlpgenPythia_P2011C_ZmumuNp3";
    crossSection=15589.*1.18;
  }
  else if (RunNumber==117664){
    name="AlpgenPythia_P2011C_ZmumuNp4";
    crossSection=3907.*1.18;
  }
  else if (RunNumber==117665){
    name="AlpgenPythia_P2011C_ZmumuNp5";
    crossSection=1193.*1.18;
  }
  else if (RunNumber==117670){
    name="AlpgenPythia_P2011C_ZtautauNp0";
    crossSection=718850.*1.18;
  }
  else if (RunNumber==117671){
    name="AlpgenPythia_P2011C_ZtautauNp1";
    crossSection=175830.*1.18;
  }
  else if (RunNumber==117672){
    name="AlpgenPythia_P2011C_ZtautauNp2";
    crossSection=58630.*1.18;
  }
  else if (RunNumber==117673){
    name="AlpgenPythia_P2011C_ZtautauNp3";
    crossSection=15508.*1.18;
  }
  else if (RunNumber==117674){
    name="AlpgenPythia_P2011C_ZtautauNp4";
    crossSection=3953.*1.18;
  }
  else if (RunNumber==117675){
    name="AlpgenPythia_P2011C_ZtautauNp5";
    crossSection=1181.*1.18;
  }
  else if (RunNumber==147105){
    name="AlpgenPythia_Auto_P2011C_ZeeNp0";
    crossSection=718890*1.18;
  }
  else if (RunNumber==147106){
    name="AlpgenPythia_Auto_P2011C_ZeeNp1";
    crossSection=175600.*1.18;
  }
  else if (RunNumber==147107){
    name="AlpgenPythia_Auto_P2011C_ZeeNp2";
    crossSection=58849.*1.18;
  }
  else if (RunNumber==147108){
    name="AlpgenPythia_Auto_P2011C_ZeeNp3";
    crossSection=15560.*1.18;
  }
  else if (RunNumber==147109){
    name="AlpgenPythia_Auto_P2011C_ZeeNp4";
    crossSection=3932.*1.18;
  }
  else if (RunNumber==147110){
    name="AlpgenPythia_Auto_P2011C_ZeeNp5incl";
    crossSection=1199.*1.18;
  }
  else if (RunNumber==147113){
    name="AlpgenPythia_Auto_P2011C_ZmumuNp0";
    crossSection=718910.*1.18;
  }
  else if (RunNumber==147114){
    name="AlpgenPythia_Auto_P2011C_ZmumuNp1";
    crossSection=175810.*1.18;
  }
  else if (RunNumber==147115){
    name="AlpgenPythia_Auto_P2011C_ZmumuNp2";
    crossSection=58805.*1.18;
  }
  else if (RunNumber==147116){
    name="AlpgenPythia_Auto_P2011C_ZmumuNp3";
    crossSection=15589.*1.18;
  }
  else if (RunNumber==147117){
    name="AlpgenPythia_Auto_P2011C_ZmumuNp4";
    crossSection=3907.*1.18;
  }
  else if (RunNumber==147118){
    name="AlpgenPythia_Auto_P2011C_ZmumuNp5incl";
    crossSection=1193.*1.18;
  }
  else if (RunNumber==147121){
    name="AlpgenPythia_Auto_P2011C_ZtautauNp0";
    crossSection=718850.*1.18;
  }
  else if (RunNumber==147122){
    name="AlpgenPythia_Auto_P2011C_ZtautauNp1";
    crossSection=175830.*1.18;
  }
  else if (RunNumber==147123){
    name="AlpgenPythia_Auto_P2011C_ZtautauNp2";
    crossSection=58630.*1.18;
  }
  else if (RunNumber==147124){
    name="AlpgenPythia_Auto_P2011C_ZtautauNp3";
    crossSection=15508.*1.18;
  }
  else if (RunNumber==147125){
    name="AlpgenPythia_Auto_P2011C_ZtautauNp4";
    crossSection=3953.*1.18;
  }
  else if (RunNumber==147126){
    name="AlpgenPythia_Auto_P2011C_ZtautauNp5incl";
    crossSection=1181.*1.18;
  }
  else if (RunNumber==178354){
    name="AlpgenPythia_P2011C_ZeeNp0Excl_Mll10to40_2LeptonFilter5";
    crossSection=3.4103e6*0.174*1.18;
  }
  else if (RunNumber==178369){
    name="AlpgenPythia_P2011C_ZeeNp0Excl_Mll40to60_2LeptonFilter5";
    crossSection=6.6401e4*0.46394*1.18;
  }
  else if (RunNumber==178355){
    name="AlpgenPythia_P2011C_ZeeNp1Excl_Mll10to40_2LeptonFilter5";
    crossSection=1.1207e5*0.38652*1.18;
  }
  else if (RunNumber==178370){
    name="AlpgenPythia_P2011C_ZeeNp1Excl_Mll40to60_2LeptonFilter5";
    crossSection=9.3068e3*0.57860*1.18;
  }
 else if (RunNumber==178356){
    name="AlpgenPythia_P2011C_ZeeNp2Excl_Mll10to40_2LeptonFilter5";
    crossSection=6.4854e4*0.32589*1.18;
  }
  else if (RunNumber==178371){
    name="AlpgenPythia_P2011C_ZeeNp2Excl_Mll40to60_2LeptonFilter5";
    crossSection=3.2293e3*0.58860*1.18;
  }
  else if (RunNumber==178357){
    name="AlpgenPythia_P2011C_ZeeNp3Excl_Mll10to40_2LeptonFilter5";
    crossSection=1.2998e4*0.37537*1.18;
  }
  else if (RunNumber==178372){
    name="AlpgenPythia_P2011C_ZeeNp3Excl_Mll40to60_2LeptonFilter5";
    crossSection=7.7993e2*0.61887*1.18;
  }
  else if (RunNumber==178358){
    name="AlpgenPythia_P2011C_ZeeNp4Incl_Mll10to40_2LeptonFilter5";
    crossSection=3.7755e3*0.41180*1.18;
  }
  else if (RunNumber==178373){
    name="AlpgenPythia_P2011C_ZeeNp4Incl_Mll40to60_2LeptonFilter5";
    crossSection=2.5091e2*0.63944*1.18;
  }
  else if (RunNumber==178359){
    name="AlpgenPythia_P2011C_ZmumuNp0Excl_Mll10to40_2LeptonFilter5";
    crossSection=3.4103e6*0.18052*1.18;
  }
  else if (RunNumber==178374){
    name="AlpgenPythia_P2011C_ZmumuNp0Excl_Mll40to60_2LeptonFilter5";
    crossSection=6.6401e4*0.46394*1.18;
  }
  else if (RunNumber==178360){
    name="AlpgenPythia_P2011C_ZmumuNp1Excl_Mll10to40_2LeptonFilter5";
    crossSection=1.1209e5*0.39347*1.18;
  }
  else if (RunNumber==178375){
    name="AlpgenPythia_P2011C_ZmumuNp1Excl_Mll40to60_2LeptonFilter5";
    crossSection=9.3122e3*0.58296*1.18;
  }
 else if (RunNumber==178361){
    name="AlpgenPythia_P2011C_ZmumuNp2Excl_Mll10to40_2LeptonFilter5";
    crossSection=6.4821e4*0.33265*1.18;
  }
  else if (RunNumber==178376){
    name="AlpgenPythia_P2011C_ZmumuNp2Excl_Mll40to60_2LeptonFilter5";
    crossSection=3.2217e3*0.59344*1.18;
  }
  else if (RunNumber==178362){
    name="AlpgenPythia_P2011C_ZmumuNp3Excl_Mll10to40_2LeptonFilter5";
    crossSection=1.2983e4*0.38074*1.18;
  }
  else if (RunNumber==178377){
    name="AlpgenPythia_P2011C_ZmumuNp3Excl_Mll40to60_2LeptonFilter5";
    crossSection=7.8029e2*0.62303*1.18;
  }
  else if (RunNumber==178363){
    name="AlpgenPythia_P2011C_ZmumuNp4Incl_Mll10to40_2LeptonFilter5";
    crossSection=3.7596e3*0.41915*1.18;
  }
  else if (RunNumber==178378){
    name="AlpgenPythia_P2011C_ZmumuNp4Incl_Mll40to60_2LeptonFilter5";
    crossSection=2.5067e2*0.64492*1.18;
  }
 else if (RunNumber==178364){
    name="AlpgenPythia_P2011C_ZtautauNp0Excl_Mll10to40_2LeptonFilter5";
    crossSection=3.4104e6*0.0049028*1.18;
  }
  else if (RunNumber==178379){
    name="AlpgenPythia_P2011C_ZtautauNp0Excl_Mll40to60_2LeptonFilter5";
    crossSection=6.6407e4*0.18580*1.18;
  }
  else if (RunNumber==178365){
    name="AlpgenPythia_P2011C_ZtautauNp1Excl_Mll10to40_2LeptonFilter5";
    crossSection=1.1207e5*0.063976*1.18;
  }
  else if (RunNumber==178380){
    name="AlpgenPythia_P2011C_ZtautauNp1Excl_Mll40to60_2LeptonFilter5";
    crossSection=9.3100e3*0.23694*1.18;
  }
 else if (RunNumber==178366){
    name="AlpgenPythia_P2011C_ZtautauNp2Excl_Mll10to40_2LeptonFilter5";
    crossSection=6.4842e4*0.052245*1.18;
  }
  else if (RunNumber==178381){
    name="AlpgenPythia_P2011C_ZtautauNp2Excl_Mll40to60_2LeptonFilter5";
    crossSection=3.2270e3*0.25995*1.18;
  }
  else if (RunNumber==178367){
    name="AlpgenPythia_P2011C_ZtautauNp3Excl_Mll10to40_2LeptonFilter5";
    crossSection=1.3004e4*0.0864553*1.18;
  }
  else if (RunNumber==178382){
    name="AlpgenPythia_P2011C_ZtautauNp3Excl_Mll40to60_2LeptonFilter5";
    crossSection=7.8144e2*0.29547*1.18;
  }
  else if (RunNumber==178368){
    name="AlpgenPythia_P2011C_ZtautauNp4Incl_Mll10to40_2LeptonFilter5";
    crossSection=3.6706e3*0.12186*1.18;
  }
  else if (RunNumber==178383){
    name="AlpgenPythia_P2011C_ZtautauNp4Incl_Mll40to60_2LeptonFilter5";
    crossSection=2.4895e2*0.328736*1.18;
  }
  else if (RunNumber==107650){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp0";
    crossSection=712000.*1.23;
  }
  else if (RunNumber==107651){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp1";
    crossSection=155000.*1.23;
  }
  else if (RunNumber==107652){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp2";
    crossSection=48800.*1.23;
  }
  else if (RunNumber==107653){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp3";
    crossSection=14200.*1.23;
  }
  else if (RunNumber==107654){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp4";
    crossSection=3770.*1.23;
  }
  else if (RunNumber==107655){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp5";
    crossSection=1120.*1.23;
  }
  else if (RunNumber==107660){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp0";
    crossSection=712000.*1.23;
  }
  else if (RunNumber==107661){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp1";
    crossSection=155000.*1.23;
  }
  else if (RunNumber==107662){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp2";
    crossSection=48800.*1.23;
  }
  else if (RunNumber==107663){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp3";
    crossSection=14200.*1.23;
  }
  else if (RunNumber==107664){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp4";
    crossSection=3770.*1.23;
  }
  else if (RunNumber==107665){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp5";
    crossSection=1120.*1.23;
  }
  else if (RunNumber==107670){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp0";
    crossSection=712000.*1.23;
  }
  else if (RunNumber==107671){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp1";
    crossSection=155000.*1.23;
  }
  else if (RunNumber==107672){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp2";
    crossSection=48800.*1.23;
  }
  else if (RunNumber==107673){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp3";
    crossSection=14200.*1.23;
  }
  else if (RunNumber==107674){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp4";
    crossSection=3770.*1.23;
  }
  else if (RunNumber==107675){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp5";
    crossSection=1120.*1.23;
  }
  else if (RunNumber==147808){
    name="PowhegPythia8_AU2CT10_Ztautau";
    crossSection=1.109e6*1.04;
  }
  else if (RunNumber==147807){
    name="PowhegPythia8_AU2CT10_Zmumu";
    crossSection=1.109e6*1.04;
  }
  else if (RunNumber==147806){
    name="PowhegPythia8_AU2CT10_Zee";
    crossSection=1.109e6*1.04;
  }
  else if (RunNumber==129680){
    name="PowhegPythia8_AU2CT10_Zee";
    crossSection=1.109e6*1.04;
  }
  else if(RunNumber==146830){
    name="";
    crossSection=3.48e6*1.19;
  }
  else if(RunNumber==146831){
    name="";
    crossSection=0.11e6*1.19;
  }
  else if(RunNumber==146832){
    name="";
    crossSection=0.0523e6*1.19;
  }
  else if(RunNumber==146833){
    name="";
    crossSection=0.0113e6*1.19;
  }
  else if(RunNumber==146834){
    name="";
    crossSection=2.59e3*1.19;
  }
  else if(RunNumber==146835){
    name="";
    crossSection=6.93e2*1.19;
  }
  else if(RunNumber==146840){
    name="";
    crossSection=3.48e6*1.19;
  }
  else if(RunNumber==146841){
    name="";
    crossSection=0.11e6*1.19;
  }
  else if(RunNumber==146842){
    name="";
    crossSection=0.0523e6*1.19;
  }
  else if(RunNumber==146843){
    name="";
    crossSection=0.0113e6*1.19;
  }
  else if(RunNumber==146844){
    name="";
    crossSection=2.59e3*1.19;
  }
  else if(RunNumber==146845){
    name="";
    crossSection=6.93e2*1.19;
  }
  else if(RunNumber==146850){
    name="";
    crossSection=3.48e6*1.19;
  }
  else if(RunNumber==146851){
    name="";
    crossSection=0.11e6*1.19;
  }
  else if(RunNumber==146852){
    name="";
    crossSection=0.0523e6*1.19;
  }
  else if(RunNumber==146853){
    name="";
    crossSection=0.0113e6*1.19;
  }
  else if(RunNumber==146854){
    name="";
    crossSection=2.59e3*1.19;
  }
  else if(RunNumber==181420){
    name="Zbb, Z->ee + 0 partons (4 Leptons Mass)";
    crossSection=1.6*8032*4.7492E-03;
  }
  else if(RunNumber==181421){
    name="Zbb, Z->ee + 1 partons (4 Leptons Mass)";
    crossSection=1.6*2859*9.7603E-03;
  }
  else if(RunNumber==181422){
    name="Zbb, Z->ee + 2 partons (4 Leptons Mass)";
    crossSection=1.6*930*1.4538E-02;
  }
  else if(RunNumber==181425){
    name="Zbb, Z->mumu + 0 partons (4 Leptons Mass)";
    crossSection=1.6*8032*4.7974E-03;
  }
  else if(RunNumber==181426){
    name="Zbb, Z->mumu + 1 partons (4 Leptons Mass)";
    crossSection=1.6*2859*9.8221E-03;
  }
  else if(RunNumber==181427){
    name="Zbb, Z->mumu + 2 partons (4 Leptons Mass)";
    crossSection=1.6*930*1.4615E-02;
  }
  else if(RunNumber==181430){
    name="Zbb, Z->ee + 0 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*8035*1.0392E-01;
  }
  else if(RunNumber==181431){
    name="Zbb, Z->ee + 1 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*2858*1.5277E-01;
  }
  else if(RunNumber==181432){
    name="Zbb, Z->ee + 2 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*929*1.7110E-01;
  }
  else if(RunNumber==181435){
    name="Zbb, Z->mumu + 0 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*8029*1.0436E-01;
  }
  else if(RunNumber==181436){
    name="Zbb, Z->mumu + 1 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*2860*1.5332E-01;
  }
  else if(RunNumber==181437){
    name="Zbb, Z->mumu + 2 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*929*1.7199E-01;
  }
  else if(RunNumber==146980){
    name="Zbb, Z->ee + 0 partons (4 Leptons Mass)";
    crossSection=1.6*30.2473;
  }
  else if(RunNumber==146981){
    name="Zbb, Z->ee + 1 partons (4 Leptons Mass)";
    crossSection=1.6*25.9125;
  }
  else if(RunNumber==146982){
    name="Zbb, Z->ee + 2 partons (4 Leptons Mass)";
    crossSection=1.6*15.0649;
  }
  else if(RunNumber==146985){
    name="Zbb, Z->mumu + 0 partons (4 Leptons Mass)";
    crossSection=1.6*30.4634;
  }
  else if(RunNumber==146986){
    name="Zbb, Z->mumu + 1 partons (4 Leptons Mass)";
    crossSection=1.6*26.0188;
  }
  else if(RunNumber==146987){
    name="Zbb, Z->mumu + 2 partons (4 Leptons Mass)";
    crossSection=1.6*14.9299;
  }
  else if(RunNumber==146990){
    name="Zbb, Z->ee + 0 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*749.9056;
  }
  else if(RunNumber==146991){
    name="Zbb, Z->ee + 1 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*449.5598;
  }
  else if(RunNumber==146992){
    name="Zbb, Z->ee + 2 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*192.7407;
  }
  else if(RunNumber==146995){
    name="Zbb, Z->mumu + 0 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*752.9395;
  }
  else if(RunNumber==146996){
    name="Zbb, Z->mumu + 1 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*449.7719;
  }
  else if(RunNumber==146997){
    name="Zbb, Z->mumu + 2 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*192.7161;
  }
  else if(RunNumber==167162 ) {
    name="Powheg ZZ->4e with 100-150 mass filter";
    crossSection=5.28;
  }
  else if(RunNumber==167165 ) {
    name="Powheg ZZ->4mu with 100-150 mass filter";
    crossSection=5.47;
  }
  else if(RunNumber==167163 ) {
    name="Powheg ZZ->2e2mu with 100-150 mass filter";
    crossSection=10.79;
  }
  else if(RunNumber==167164 ) {
    name="Powheg ZZ->2e2tau with 100-150 mass filter";
    crossSection=0.926;
  }
  else if(RunNumber==167166 ) {
    name="Powheg ZZ->2mu2tau with 100-150 mass filter";
    crossSection=0.9324;
  }
  else if(RunNumber==167167 ) {
    name="Powheg ZZ->4tau with 100-150 mass filter";
    crossSection=0.0237;
  }
  else if(RunNumber==169690 ) {
    name="Powheg ZZ->4e with 500-10000 mass filter";
    crossSection=0.42; //5.5084E-03*7.7000E-05 nb
  }
  else if(RunNumber==169691 ) {
    name="Powheg ZZ->2e2mu with 500-10000 mass filter";
    crossSection=0.84; //4.7629E-03*1.7580E-04 nb
  }
  else if(RunNumber==169692 ) {
    name="Powheg ZZ->4mu with 500-10000 mass filter";
    crossSection=0.45; //5.8613E-03*7.6630E-05 nb
  }
  else if(RunNumber==161961 ) {
    name="mc12_8TeV.161961.Sherpa_CT10_lllnu_WZ";
    crossSection=2.5126e3;
  }
  else if(RunNumber == 126893 ) {
    name="mc12_8TeV.126893.Sherpa_CT10_lllnu_WZ";
    crossSection = 9.757*1.06e3; // 1.06 = k-factor
  }
  else if(RunNumber == 147194 ) {
    name="mc12_8TeV.147194.Sherpa_CT10_lllnjj_WZjj_EW6";
    crossSection = 0.07296e3;
  }
  else if(RunNumber == 147197 ) {
    name="mc12_8TeV.147197.Sherpa_CT10_lllnu_WZ_l10";
    crossSection = 9.757*1.06*0.274e3; // 1.06 = k-factor, 0.274 filter
  }
  else if(RunNumber==126894){
    name="Sherpa_CT10_llll_ZZ ";
    crossSection=8.7403e3;
  } 
  // samples for Z->4l analysis
  else if(RunNumber==147565 ) {
    name="PowhegPythia8_AU2CT10_ZZ_4mu_mll1_4lpt3_m4l40";
    crossSection=47.30; 
  }
  else if(RunNumber==147564) {
    name="PowhegPythia8_AU2CT10_ZZ_2e2mu_mll1_4lpt3_m4l40";
    crossSection=90.87; 
  }
  else if(RunNumber==147563 ) {
    name="PowhegPythia8_AU2CT10_ZZ_4e_mll1_4lpt3_m4l40";
    crossSection=45.87;
  }
  /**
  else if(RunNumber==146833){
    name="";
    crossSection=0.0113e6*1.19;
  }
  else if(RunNumber==146834){
    name="";
    crossSection=2.59e3*1.19;
  }
  else if(RunNumber==146835){
    name="";
    crossSection=6.93e2*1.19;
  }
  **/
  //////////
  //MCFM Interferometry sample
  //////////
  else if(RunNumber==189591 ) {
    name="MCFMPythia8_AU2CT10_gg_ZZ_bkg_4e_m4l100_4pt3";
    crossSection=0.9889443509/2;
  }
  else if(RunNumber==189592 ) {
    name="MCFMPythia8_AU2CT10_gg_ZZ_bkg_2e2mu_m4l100_4pt3";
    crossSection=0.9889443509;
  }
  else if(RunNumber==189593 ) {
    name="MCFMPythia8_AU2CT10_gg_ZZ_bkg_4mu_m4l100_4pt3";
    crossSection=0.9889443509/2;
  }
  else if(RunNumber==189594 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_ZZ_4e_m4l100_4pt3";
    crossSection=0.3088467730/2;
  }
  else if(RunNumber==189595 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_ZZ_2e2mu_m4l100_4pt3";
    crossSection=0.3088467730;
  }
  else if(RunNumber==189596 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_ZZ_4mu_m4l100_4pt3";
    crossSection=0.3088467730/2;
  }
  else if(RunNumber==189597 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_gg_ZZ_4e_m4l100_4pt3";
    crossSection=1.2325681692/2;
  }
  else if(RunNumber==189598 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_gg_ZZ_2e2mu_m4l100_4pt3";
    crossSection=1.2325681692;
  }
  else if(RunNumber==189599 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_gg_ZZ_4mu_m4l100_4pt3";
    crossSection=1.2325681692/2;
  }
  else if(RunNumber==189600 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_25SMW_gg_ZZ_4e_m4l100_4pt3";
    crossSection=1.7505629185/2;
  }
  else if(RunNumber==189601 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_25SMW_gg_ZZ_2e2mu_m4l100_4pt3";
    crossSection=1.7505629185;
  }
  else if(RunNumber==189602 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_25SMW_gg_ZZ_4mu_m4l100_4pt3";
    crossSection=1.7505629185/2;
  }
  else if(RunNumber==189603 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_50SMW_gg_ZZ_4e_m4l100_4pt3";
    crossSection=2.4253481850/2;
  }
  else if(RunNumber==189604 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_50SMW_gg_ZZ_2e2mu_m4l100_4pt3";
    crossSection=2.4253481850;
  }
  else if(RunNumber==189605 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_50SMW_gg_ZZ_4mu_m4l100_4pt3";
    crossSection=2.4253481850/2;
  }
  else if(RunNumber==189710 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_10SMW_gg_ZZ_4e_m4l100_4pt3";
    crossSection=1.3778877728/2;
  }
	else if(RunNumber==189711 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_10SMW_gg_ZZ_2e2mu_m4l100_4pt3";
    crossSection=1.3778877728;
  }
  else if(RunNumber==189712 ) {
    name="MCFMPythia8_AU2CT10_ggH125p5_10SMW_gg_ZZ_4mu_m4l100_4pt3";
    crossSection=1.3778877728/2;
  }
  
	else if(RunNumber==189834 ) {
    name="MadGraphPythia_AUET2BCTEQ6L1_VBFH125p5_ZZ_4l";
    crossSection=0.22038;
  }
 else if(RunNumber==189835 ) {
    name="MadGraphPythia_AUET2BCTEQ6L1_VBFH125p5_bkg_4l";
    crossSection=0.2844;
  }
 else if(RunNumber==189836 ) {
    name="MadGraphPythia_AUET2BCTEQ6L1_VBFH125p5_sbi_4l";
    crossSection=0.4601;
  }
 else if(RunNumber==189897 ) {
    name="MadGraphPythia_AUET2BCTEQ6L1_VBFH125p5_10SMW_sbi_4l";
    crossSection=0.5474;
  }

  //////////
  //gg2VV Interferometry sample
  //////////
  else if(RunNumber==189612  ) {
    name="gg2VVPythia8_AU2CT10_gg_ZZ_bkg_4e_m4l100_4pt3";
    crossSection=0.937/2;
  }
  else if(RunNumber==189613  ) {
    name="gg2VVPythia8_AU2CT10_gg_ZZ_bkg_2e2mu_m4l100_4pt3";
    crossSection=0.937;
  }
  else if(RunNumber==189614  ) {
    name="gg2VVPythia8_AU2CT10_gg_ZZ_bkg_4mu_m4l100_4pt3";
    crossSection=0.937/2;
  }
  else if(RunNumber==189615  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_ZZ_4e_m4l100_4pt3";
    crossSection=0.314/2;
  }
  else if(RunNumber==189616  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_ZZ_2e2mu_m4l100_4pt3";
    crossSection=0.314;
  }
  else if(RunNumber==189617  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_ZZ_4mu_m4l100_4pt3";
    crossSection=0.314/2;
  }
  else if(RunNumber==189618  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_gg_ZZ_4e_m4l100_4pt3";
    crossSection=1.18/2;
  }
  else if(RunNumber==189619  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_gg_ZZ_2e2mu_m4l100_4pt3";
    crossSection=1.18;
  }
  else if(RunNumber==189620  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_gg_ZZ_4mu_m4l100_4pt3";
    crossSection=1.18/2;
  }
  else if(RunNumber==189621  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_25SMW_gg_ZZ_4e_m4l100_4pt3";
    crossSection=1.696/2;
  }
  else if(RunNumber==189622  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_25SMW_gg_ZZ_2e2mu_m4l100_4pt3";
    crossSection=1.696;
  }
  else if(RunNumber==189623  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_25SMW_gg_ZZ_4mu_m4l100_4pt3";
    crossSection=1.696/2;
  }
  else if(RunNumber==189624  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_50SMW_gg_ZZ_4e_m4l100_4pt3";
    crossSection=2.379/2;
  }
  else if(RunNumber==189625  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_50SMW_gg_ZZ_2e2mu_m4l100_4pt3";
    crossSection=2.379;
  }
  else if(RunNumber==189626  ) {
    name="gg2VVPythia8_AU2CT10_ggH125p5_50SMW_gg_ZZ_4mu_m4l100_4pt3";
    crossSection=2.379/2;
  }
  else if(RunNumber==181767  ) {
    name="Pythia8_AU2CTEQ6L1_DPI_Z_Z_4l";
    crossSection=0.958;
  } else if(RunNumber==147285  ) {
    name="Pythia8_AU2CTEQ6L1_DPI_Z_Z_2l";
    crossSection=5.088;
  }
	// Sherpa Int
	else if(RunNumber==206305  ) {
		name="Sherpa_CT10_ggllll";
		crossSection=6.32;
	}
	else if(RunNumber==206306  ) {
		name="Sherpa_CT10_ggllllNoHiggs";
		crossSection=4.20;
	} 
	else if(RunNumber==206307  ) {
		name="Sherpa_CT10_ggllllOnlyHiggs";
		crossSection=3.00;
	}
	else if(RunNumber==206308  ) {
		name="Sherpa_CT10_ggllllOnlyHiggsM440";
		crossSection=2.00;
	}

 if (PrintSummary){
    if (crossSection!=-1){
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"               Cross section x Branching Ratio = "<< crossSection <<" fb^-1 "<< std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
    }else{
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"                    NO Cross section !!!  " << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    }
  }
  return crossSection;
 }


//} 

double CrossSections::GetBkgCrossSection(int RunNumber,bool PrintSummary){
  //EVERYTHING in fb  
   double crossSection=-1.0;
   std::string name="";

 if (RunNumber==107650){
    name="Alpgen+Jimmy Zee + 0  partons ";
    crossSection=827375.;
  }else if (RunNumber==107651){
    name="Alpgen+Jimmy Zee + 1  partons ";
    crossSection=166625.;
  }else if (RunNumber==107652){
    name="Alpgen+Jimmy Zee + 2  partons ";
    crossSection=50375.;
  }else if (RunNumber==107653){
    name="Alpgen+Jimmy Zee + 3  partons ";
    crossSection=14000.;
  }else if (RunNumber==107654){
    name="Alpgen+Jimmy Zee + 4  partons ";
    crossSection=3375.;
  }else if (RunNumber==107655){
    name="Alpgen+Jimmy Zee + 5  partons ";
    crossSection=1000.;
  }else if (RunNumber==107660){
    name="Alpgen+Jimmy Zmumu + 0        partons ";
    crossSection=822125;
  }else if (RunNumber==107661){
    name="Alpgen+Jimmy Zmumu + 1        partons ";
    crossSection=166000.;
  }else if (RunNumber==107662){
    name="Alpgen+Jimmy Zmumu + 2         partons ";
    crossSection=49500.;
  }else if (RunNumber==107663){
    name="Alpgen+Jimmy Zmumu + 3        partons ";
    crossSection=13875.;
  }else if (RunNumber==107664){
    name="Alpgen+Jimmy Zmumu + 4        partons ";
    crossSection=3500.;
  }else if (RunNumber==107665){
    name="Alpgen+Jimmy Zmumu + 5        partons ";
    crossSection=1000.;
  }else if (RunNumber==107670){
    name="Alpgen+Jimmy Ztautau + 0      partons ";
    crossSection=828125.;
  }else if (RunNumber==107671){
    name="Alpgen+Jimmy Ztautau + 1      partons ";
    crossSection=167375.;
  }else if (RunNumber==107672){
    name="Alpgen+Jimmy Ztautau + 2      partons ";
    crossSection=50375.;
  }else if (RunNumber==107673){
    name="Alpgen+Jimmy Ztautau + 3      partons ";
    crossSection=13750;
  }else if (RunNumber==107674){
    name="Alpgen+Jimmy Ztautau + 4      partons ";
    crossSection=3500.;
  }else if (RunNumber==107675){
    name="Alpgen+Jimmy Ztautau + 5      partons ";
    crossSection=1000.;
  }else if (RunNumber==116960){
    name="Zbb, Z->ee (ll > 30 !GeV) + 0 parton [m_4l 60/12 !GeV] ";
    crossSection=20.701*1.4;
  }else if (RunNumber==116961){
    name="Zbb, Z->ee (ll > 30 !GeV) + 1 parton [m_4l 60/12 !GeV] ";
    crossSection=18.8029*1.4;
  }else if (RunNumber==116962){
    name="Zbb, Z->ee (ll > 30 !GeV) + 2 parton [m_4l 60/12 !GeV] ";
    crossSection=10.505*1.4;
  }else if (RunNumber==116963){
    name="Zbb, Z->ee (ll > 30 !GeV) + 3 parton [m_4l 60/12 !GeV] ";
    crossSection=7.30463*1.4;
  }else if (RunNumber==116965){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 0 parton [m_4l 60/12 !GeV] ";
    crossSection=21.516*1.4;
  }else if (RunNumber==116966){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 1 parton [m_4l 60/12 !GeV] ";
    crossSection=19.6674*1.4;
  }else if (RunNumber==116967){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 2 parton [m_4l 60/12 !GeV] ";
    crossSection=10.516*1.4;
  }else if (RunNumber==116968){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 3 parton [m_4l 60/12 !GeV] ";
    crossSection=7.93834*1.4;
  }else if (RunNumber==116950){
    name="Zbb, Z->ee (ll > 30 !GeV) + 0 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=756.32*1.4;
  }else if (RunNumber==116951){
    name="Zbb, Z->ee (ll > 30 !GeV) + 1 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=432.25*1.4;
  }else if (RunNumber==116952){
    name="Zbb, Z->ee (ll > 30 !GeV) + 2 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=176*1.4;
  }else if (RunNumber==116953){
    name="Zbb, Z->ee (ll > 30 !GeV) + 3 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=96.75*1.4;
  }else if (RunNumber==116955){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 0 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=730.24*1.4;
  }else if (RunNumber==116956){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 1 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=432.25*1.4;
  }else if (RunNumber==116957){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 2 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=179.3*1.4;
  }else if (RunNumber==116958){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 3 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=92.3962*1.4;
  }else if (RunNumber==128130){
    name="AlpgenJimmyLowMassDYeebbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128131){
    name="AlpgenJimmyLowMassDYeebbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128132){
    name="AlpgenJimmyLowMassDYeebbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128133){
    name="AlpgenJimmyLowMassDYeebbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==128135){
    name="AlpgenJimmyLowMassDYmumubbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128136){
    name="AlpgenJimmyLowMassDYmumubbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128137){
    name="AlpgenJimmyLowMassDYmumubbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128138){
    name="AlpgenJimmyLowMassDYmumubbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==128140){
    name="AlpgenJimmyLowMassDYtautaubbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128141){
    name="AlpgenJimmyLowMassDYtautaubbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128142){
    name="AlpgenJimmyLowMassDYtautaubbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128143){
    name="AlpgenJimmyLowMassDYtautaubbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==105200){
    name="ttbar (at least 1lepton filter) ";
    crossSection=91550.6;
  }else if (RunNumber==109345){
    name="ttbar (with Mll > 60 !GeV filter) ";
    crossSection=12707.2;
  }else if (RunNumber==109346){
    name="ttbar (with Mll > 60 !GeV filter and Mll > 12 !GeV) ";
    crossSection=515.2;
  }else if (RunNumber==109292){
    name="ZZ->4l 3LepFilter ";
    crossSection=91.54;
  }else if (RunNumber==126399){
    name="PowHegBoxZZeemm_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126400){
    name="PowHegBoxZZeeee_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
}else if (RunNumber==126401){
    name="PowHegBoxZmmmm_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126859){
    name="PowHegZZ_4e_trilep5GeV_Pythia ";
    crossSection=46.6;
  } else if (RunNumber==126860){
    name="PowHegZZ_4mu_trilep5GeV_Pythia ";
    crossSection=46.6;
  }else if (RunNumber==126861){
    name="PowHegZZ_2e2mu_trilep5GeV_Pythia ";
    crossSection=99.1;
  }else if (RunNumber==126862){
    name="PowHegZZ_2mu2tau_trilep5GeV_Pythia ";
    crossSection=99.1;
  }else if (RunNumber==126863){
    name="PowHegZZ_2e2tau_trilep5GeV_Pythia ";
    crossSection=99.1;
  }else if (RunNumber==126864){
    name="PowHegZZ_4tau_trilep5GeV_Pythia ";
    crossSection=44.6;
  }else if (RunNumber==128813){
    name="SherpaZZllll ";
    crossSection=-1;
  }else if (RunNumber==116600){
    name="gg2ZZ_JIMMY_ZZ4lep [2e2mu,2e2tau,2mu2tau] (gg2ZZv2.0) ";
    crossSection=-1; // don't use this sample - check 116601,116602,116603
  }else if (RunNumber==116601){
    name="gg2ZZ_JIMMY_ZZ4lep [4e] (gg2ZZv2.0) ";
    crossSection=0.86/2.;
  }else if (RunNumber==116602){
    name="gg2ZZ_JIMMY_ZZ4lep [4mu] (gg2ZZv2.0) ";
    crossSection=0.86/2.;
  }else if (RunNumber==116603){
    name="gg2ZZ_JIMMY_ZZ4lep [2e2mu] (gg2ZZv2.0) ";
    crossSection=0.86;
  }else if (RunNumber==128593){
    name="PythiaZZall_EF_15_5 ";
    crossSection=-1;
  }else if (RunNumber==109300){
    name="AlpgenJimmyZeebbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109301){
    name="AlpgenJimmyZeebbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109302){
    name="AlpgenJimmyZeebbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109303){
    name="AlpgenJimmyZeebbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==109305){
    name="AlpgenJimmyZmumubbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109306){
    name="AlpgenJimmyZmumubbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109307){
    name="AlpgenJimmyZmumubbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109308){
    name="AlpgenJimmyZmumubbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==109310){
    name="AlpgenJimmyZtautaubbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109311){
    name="AlpgenJimmyZtautaubbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109312){
    name="AlpgenJimmyZtautaubbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109313){
    name="AlpgenJimmyZtautaubbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==116250){
    name="ZeeNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;                                                                                       
}else if (RunNumber==116251){
    name="ZeeNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116252){
    name="ZeeNp2 M10to40 pt20 ";
    crossSection=41100*1.22;
  }else if (RunNumber==116253){
    name="ZeeNp3 M10to40 pt20 ";
    crossSection=8460*1.22;
  }else if (RunNumber==116254){
    name="ZeeNp4 M10to40 pt20 ";
    crossSection=1840*1.22;
  }else if (RunNumber==116255){
    name="ZeeNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }else if (RunNumber==116260){
    name="ZmumuNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116261){
    name="ZmumuNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116262){
    name="ZmumuNp2 M10to40 pt20 ";
    crossSection=40950*1.22;
  }else if (RunNumber==116263){
    name="ZmumuNp3 M10to40 pt20 ";
    crossSection=8410*1.22;
  }else if (RunNumber==116264){
    name="ZmumuNp4 M10to40 pt20 ";
    crossSection=1850*1.22;
  }else if (RunNumber==116265){
    name="ZmumuNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }else if (RunNumber==116270){
    name="ZtautauNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116271){
    name="ZtautauNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116272){
    name="ZtautauNp2 M10to40 pt20 ";
    crossSection=41100*1.22;
  }else if (RunNumber==116273){
    name="ZtautauNp3 M10to40 pt20 ";
    crossSection=8460*1.22;
  }else if (RunNumber==116274){
    name="ZtautauNp4 M10to40 pt20 ";
    crossSection=1840*1.22;
  }else if (RunNumber==116275){
    name="ZtautauNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }

  if (PrintSummary){
 if (crossSection!=-1){
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"               Cross section x Branching Ratio = "<< crossSection <<" fb^-1 "<< std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
    }else{
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"                    NO Cross section !!!  " << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    }
  }
  return crossSection;

}



double CrossSections::GetBkgCrossSection13TeV(int RunNumber,bool PrintSummary)
{

  //EVERYTHING in fb  
  double crossSection=-1.0;
  std::string name="";
  double k_Wlnu_sherpa = 0.9083;
  double k_Zll_sherpa = 0.9013;
  double k_Znunu_sherpa = 0.9374;
  double k_Wplus_powheg = 1.01724;
  double k_Wminus_powheg = 1.035786;
  double k_Zll_powheg = 1.026;
  // double k_Wlnu_MG = 1.20185;
  double k_Zll_MG = 1.232;
  double k_Znunu_MG = 1.2283;  
  double k_ZllHT_MG = 1.141; //Updated 4 November 2016 to match PMG twiki
  double k_ttZ = 1.35;
  double k_tt = 1.1949;
  // Added Feb 25, to scale madgraph EFT samples to LHC XS WG - Haider
  //double k_madGraphVBF = 1.311; 
  double k_madGraphVBF = 1;  // set to 1 2 February 2017 at request of Katharina et al. - Hannah
  // For the Sherpa 2.2 samples; values from the TWiki pages (XsecSummaryZjetsSherpa22Light) - Hannah
  double k_Zll_Sherpa22 = 0.9751;
  double k_Znunu_Sherpa22 = 0.9728;

  double k_ZZ_sherpa = 0.91;

  if (RunNumber == 187150 ){
    name = "PowhegPythia8_AU2CT10_WpWm_ee";
    crossSection = 1179.2 * 1.0 ; // 1179.2 fb 
}
else if (RunNumber == 187151 ){
    name = "PowhegPythia8_AU2CT10_WpWm_mue";
    crossSection = 1179.0 * 1.0 ; // 1179.0 fb 
}
else if (RunNumber == 187152 ){
    name = "PowhegPythia8_AU2CT10_WpWm_taue";
    crossSection = 1179.0 * 1.0 ; // 1179.0 fb 
}
else if (RunNumber == 187153 ){
    name = "PowhegPythia8_AU2CT10_WpWm_emu";
    crossSection = 1179.0 * 1.0 ; // 1179.0 fb 
}
else if (RunNumber == 187154 ){
    name = "PowhegPythia8_AU2CT10_WpWm_mumu";
    crossSection = 1179.2 ; // fb 
}
else if (RunNumber == 187155 ){
    name = "PowhegPythia8_AU2CT10_WpWm_taumu";
    crossSection = 1179.0 * 1.0 ; // 1179.0 fb 
}
else if (RunNumber == 187156 ){
    name = "PowhegPythia8_AU2CT10_WpWm_etau";
    crossSection = 1179.0 * 1.0 ; // 1179.0 fb 
}
else if (RunNumber == 187157 ){
    name = "PowhegPythia8_AU2CT10_WpWm_mutau";
    crossSection = 1179.0 * 1.0 ; // 1179.0 fb 
}
else if (RunNumber == 187158 ){
    name = "PowhegPythia8_AU2CT10_WpWm_tautau";
    crossSection = 1179.2 * 1.0 ; // 1179.2 fb 
}
else if (RunNumber == 187160 ){
    name = "PowhegPythia8_AU2CT10_WmZ_3e_mll0p25_DiLeptonFilter";
    crossSection = 1688.0 * 0.28537 ; // 481.70456 fb 
}
else if (RunNumber == 187161 ){
    name = "PowhegPythia8_AU2CT10_WmZ_e2mu_mll0p4614_DiLeptonFilter";
    crossSection = 1168.0 * 0.34095 ; // 398.2296 fb 
}
else if (RunNumber == 187162 ){
    name = "PowhegPythia8_AU2CT10_WmZ_e2tau_mll3p804_DiLeptonFilter";
    crossSection = 214.1 * 0.16291 ; // 34.879031 fb 
}
else if (RunNumber == 187163 ){
    name = "PowhegPythia8_AU2CT10_WmZ_mu2e_mll0p25_DiLeptonFilter";
    crossSection = 1769.0 * 0.28649 ; // 506.80081 fb 
}
else if (RunNumber == 187164 ){
    name = "PowhegPythia8_AU2CT10_WmZ_3mu_mll0p4614_DiLeptonFilter";
    crossSection = 1151.0 * 0.34169 ; // 393.28519 fb 
}
else if (RunNumber == 187165 ){
    name = "PowhegPythia8_AU2CT10_WmZ_mu2tau_mll3p804_DiLeptonFilter";
    crossSection = 214.1 * 0.16358 ; // 35.022478 fb 
}
else if (RunNumber == 187166 ){
    name = "PowhegPythia8_AU2CT10_WmZ_tau2e_mll0p25_DiLeptonFilter";
    crossSection = 1769.0 * 0.14671 ; // 259.52999 fb 
}
else if (RunNumber == 187167 ){
    name = "PowhegPythia8_AU2CT10_WmZ_tau2mu_mll0p4614_DiLeptonFilter";
    crossSection = 1168.0 * 0.18525 ; // 216.372 fb 
}
else if (RunNumber == 187168 ){
    name = "PowhegPythia8_AU2CT10_WmZ_3tau_mll3p804_DiLeptonFilter";
    crossSection = 210.4 * 0.059701 ; // 12.5610904 fb 
}
else if (RunNumber == 187170 ){
    name = "PowhegPythia8_AU2CT10_WpZ_3e_mll0p25_DiLeptonFilter";
    crossSection = 2354.0 * 0.27156 ; //  fb 
}
else if (RunNumber == 187171 ){
    name = "PowhegPythia8_AU2CT10_WpZ_e2mu_mll0p4614_DiLeptonFilter";
    crossSection = 1559.0 * 0.32575 ; // 507.84425 fb 
}
else if (RunNumber == 187172 ){
    name = "PowhegPythia8_AU2CT10_WpZ_e2tau_mll3p804_DiLeptonFilter";
    crossSection = 312.9 * 0.16384 ; // 51.265536 fb 
}
else if (RunNumber == 187173 ){
    name = "PowhegPythia8_AU2CT10_WpZ_mu2e_mll0p25_DiLeptonFilter";
    crossSection = 2371.0 * 0.2722 ; // 645.3862 fb 
}
else if (RunNumber == 187174 ){
    name = "PowhegPythia8_AU2CT10_WpZ_3mu_mll0p4614_DiLeptonFilter";
    crossSection = 1591.0 * 0.32682 ; //  
}
else if (RunNumber == 187175 ){
    name = "PowhegPythia8_AU2CT10_WpZ_mu2tau_mll3p804_DiLeptonFilter";
    crossSection = 312.9 * 0.1633 ; //  fb 
}
else if (RunNumber == 187176 ){
    name = "PowhegPythia8_AU2CT10_WpZ_tau2e_mll0p25_DiLeptonFilter";
    crossSection = 2371.0 * 0.13784 ; // 326.81864 fb 
}
else if (RunNumber == 187177 ){
    name = "PowhegPythia8_AU2CT10_WpZ_tau2mu_mll0p4614_DiLeptonFilter";
    crossSection = 1559.0 * 0.17402 ; // 271.29718 fb 
}
else if (RunNumber == 187178 ){
    name = "PowhegPythia8_AU2CT10_WpZ_3tau_mll3p804_DiLeptonFilter";
    crossSection = 308.1 *  0.060375; //  fb 
}
else if (RunNumber == 187180 ){
    name = "PowhegPythia8_AU2CT10_ZZ_4e_mll4_DiLeptonFilter";
    crossSection = 132.4 * 0.91935 ; // 121.72194 fb 
}
else if (RunNumber == 187181 ){
    name = "PowhegPythia8_AU2CT10_ZZ_2e2mu_mll4_DiLeptonFilter";
    crossSection = 296.1 * 0.849 ; //  fb 
}
else if (RunNumber == 187182 ){
    name = "PowhegPythia8_AU2CT10_ZZ_2e2tau_mll4_DiLeptonFilter";
    crossSection = 296.1 * 0.60915 ; // 180.369315 fb 
}
else if (RunNumber == 187183 ){
    name = "PowhegPythia8_AU2CT10_ZZ_4mu_mll4_DiLeptonFilter";
    crossSection = 132.4 * 0.92286 ; // 122.186664 fb 
}
else if (RunNumber == 187184 ){
    name = "PowhegPythia8_AU2CT10_ZZ_2mu2tau_mll4_DiLeptonFilter";
    crossSection = 296.1 * 0.61565 ; // 182.293965 fb 
}
else if (RunNumber == 187185 ){
    name = "PowhegPythia8_AU2CT10_ZZ_4tau_mll4_DiLeptonFilter";
    crossSection = 132.4 * 0.11319 ; // 14.986356 fb 
}
else if (RunNumber == 187186 ){
    name = "PowhegPythia8_AU2CT10_ZZ_2e2nu_mll4";
    crossSection = 103.23 * 1.0 * 3.; // 103.23 fb 
}
else if (RunNumber == 187187 ){
    name = "PowhegPythia8_AU2CT10_ZZ_2mu2nu_mll4";
    crossSection = 103.23 * 1.0 * 3.; // 103.23 fb 
}
else if (RunNumber == 187188 ){
    name = "PowhegPythia8_AU2CT10_ZZ_2tau2nu_mll4";
    crossSection = 103.23 * 1.0 * 3.; // 103.23 fb 
}
else if (RunNumber == 206618 ){
    name = "PowhegPythia8_AU2CT10_ZZ_4e_m4l500_50000_mll4_4pt3";
    crossSection = 131.71 * 0.0083725 ; // 1.102741975 fb 
}
else if (RunNumber == 206619 ){
    name = "PowhegPythia8_AU2CT10_ZZ_2e2mu_m4l500_50000_mll4_4pt3";
    crossSection = 295.05 * 0.0075451 ; // 2.226181755 fb 
}
else if (RunNumber == 206620 ){
    name = "PowhegPythia8_AU2CT10_ZZ_4mu_m4l500_50000_mll4_4pt3";
    crossSection = 131.71 * 0.0088051 ; // 1.159719721 fb 
}
else if (RunNumber == 301000){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_120M180";
  crossSection = 17478.0 * 1; // 17478.0 fb
}
else if (RunNumber == 301001){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_180M250";
  crossSection = 2921.2 * 1; // 2921.2 fb
}
else if (RunNumber == 301002){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_250M400";
  crossSection = 1082.0 * 1; // 1082.0 fb
}
else if (RunNumber == 301003){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_400M600";
  crossSection = 195.5 * 1; // 195.5 fb
}
else if (RunNumber == 301004){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_600M800";
  crossSection = 37.401 * 1; // 37.401 fb
}
else if (RunNumber == 301005){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_800M1000";
  crossSection = 10.607 * 1; // 10.607 fb
}
else if (RunNumber == 301006){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_1000M1250";
  crossSection = 4.2582 * 1; // 4.2582 fb
}
else if (RunNumber == 301007){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_1250M1500";
  crossSection = 1.4219 * 1; // 1.4219 fb
}
else if (RunNumber == 301008){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_1500M1750";
  crossSection = 0.54521 * 1; // 0.54521 fb
}
else if (RunNumber == 301009){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_1750M2000";
  crossSection = 0.22991 * 1; // 0.22991 fb
}
else if (RunNumber == 301010){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_2000M2250";
  crossSection = 0.10387 * 1; // 0.10387 fb
}
else if (RunNumber == 301011){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_2250M2500";
  crossSection = 0.0494 * 1; // 0.0494 fb
}
else if (RunNumber == 301012){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_2500M2750";
  crossSection = 0.024452 * 1; // 0.024452 fb
}
else if (RunNumber == 301013){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_2750M3000";
  crossSection = 0.012487 * 1; // 0.012487 fb
}
else if (RunNumber == 301014){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_3000M3500";
  crossSection = 0.010029 * 1; // 0.010029 fb
}
else if (RunNumber == 301015){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_3500M4000";
  crossSection = 0.0029342 * 1; // 0.0029342 fb
}
else if (RunNumber == 301016){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_4000M4500";
  crossSection = 0.00089764 * 1; // 0.00089764 fb
}
else if (RunNumber == 301017){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_4500M5000";
  crossSection = 0.00028071 * 1; // 0.00028071 fb
}
else if (RunNumber == 301018){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYee_5000M";
  crossSection = 0.00012649 * 1; // 0.00012649 fb
}
else if (RunNumber == 301020){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_120M180";
  crossSection = 17478.0 * 1; // 17478.0 fb
}
else if (RunNumber == 301021){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_180M250";
  crossSection = 2921.2 * 1; // 2921.2 fb
}
else if (RunNumber == 301022){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_250M400";
  crossSection = 1082.0 * 1; // 1082.0 fb
}
else if (RunNumber == 301023){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_400M600";
  crossSection = 195.5 * 1; // 195.5 fb
}
else if (RunNumber == 301024){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_600M800";
  crossSection = 37.399 * 1; // 37.399 fb
}
else if (RunNumber == 301025){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_800M1000";
  crossSection = 10.607 * 1; // 10.607 fb
}else if (RunNumber == 301026){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_1000M1250";
  crossSection = 4.2582 * 1; // 4.2582 fb
}
else if (RunNumber == 301027){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_1250M1500";
  crossSection = 1.4219 * 1; // 1.4219 fb
}
else if (RunNumber == 301028){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_1500M1750";
  crossSection = 0.54521 * 1; // 0.54521 fb
}
else if (RunNumber == 301029){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_1750M2000";
  crossSection = 0.22991 * 1; // 0.22991 fb
}
else if (RunNumber == 301030){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_2000M2250";
  crossSection = 0.10387 * 1; // 0.10387 fb
}
else if (RunNumber == 301031){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_2250M2500";
  crossSection = 0.0494 * 1; // 0.0494 fb
}
else if (RunNumber == 301032){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_2500M2750";
  crossSection = 0.024452 * 1; // 0.024452 fb
}
else if (RunNumber == 301033){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_2750M3000";
  crossSection = 0.012487 * 1; // 0.012487 fb
}
else if (RunNumber == 301034){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_3000M3500";
  crossSection = 0.010029 * 1; // 0.010029 fb
}
else if (RunNumber == 301035){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_3500M4000";
  crossSection = 0.0029342 * 1; // 0.0029342 fb
}
else if (RunNumber == 301036){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_4000M4500";
  crossSection = 0.00089764 * 1; // 0.00089764 fb
}
else if (RunNumber == 301037){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_4500M5000";
  crossSection = 0.00028071 * 1; // 0.00028071 fb
}
else if (RunNumber == 301038){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYmumu_5000M";
  crossSection = 0.00012649 * 1; // 0.00012649 fb
}
else if (RunNumber == 301040){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_120M180";
  crossSection = 17480.0 * 1; // 17480.0 fb
}
else if (RunNumber == 301041){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_180M250";
  crossSection = 2920.9 * 1; // 2920.9 fb
}
else if (RunNumber == 301042){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_250M400";
  crossSection = 1082.0 * 1; // 1082.0 fb
}
else if (RunNumber == 301043){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_400M600";
  crossSection = 195.5 * 1; // 195.5 fb
}
else if (RunNumber == 301044){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_600M800";
  crossSection = 37.401 * 1; // 37.401 fb
}
else if (RunNumber == 301045){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_800M1000";
  crossSection = 10.607 * 1; // 10.607 fb
}
else if (RunNumber == 301046){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_1000M1250";
  crossSection = 4.2584 * 1; // 4.2584 fb
}
else if (RunNumber == 301047){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_1250M1500";
  crossSection = 1.422 * 1; // 1.422 fb
}
else if (RunNumber == 301048){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_1500M1750";
  crossSection = 0.54521 * 1; // 0.54521 fb
}
else if (RunNumber == 301049){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_1750M2000";
  crossSection = 0.22991 * 1; // 0.22991 fb
}
else if (RunNumber == 301050){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_2000M2250";
  crossSection = 0.10387 * 1; // 0.10387 fb
}
else if (RunNumber == 301051){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_2250M2500";
  crossSection = 0.0494 * 1; // 0.0494 fb
}else if (RunNumber == 301052){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_2500M2750";
  crossSection = 0.024452 * 1; // 0.024452 fb
}
else if (RunNumber == 301053){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_2750M3000";
  crossSection = 0.012487 * 1; // 0.012487 fb
}
else if (RunNumber == 301054){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_3000M3500";
  crossSection = 0.010029 * 1; // 0.010029 fb
}
else if (RunNumber == 301055){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_3500M4000";
  crossSection = 0.0029342 * 1; // 0.0029342 fb
}
else if (RunNumber == 301056){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_4000M4500";
  crossSection = 0.00089764 * 1; // 0.00089764 fb
}
else if (RunNumber == 301057){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_4500M5000";
  crossSection = 0.00028071 * 1; // 0.00028071 fb
}
else if (RunNumber == 301058){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_DYtautau_5000M";
  crossSection = 0.00012649 * 1; // 0.00012649 fb
}
else if (RunNumber == 301060){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_120M180";
  crossSection = 32053.0 * 1; // 32053.0 fb
}
else if (RunNumber == 301061){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_180M250";
  crossSection = 5002.9 * 1; // 5002.9 fb
}
else if (RunNumber == 301062){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_250M400";
  crossSection = 1754.3 * 1; // 1754.3 fb
}
else if (RunNumber == 301063){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_400M600";
  crossSection = 312.35 * 1; // 312.35 fb
}
else if (RunNumber == 301064){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_600M800";
  crossSection = 60.793 * 1; // 60.793 fb
}
else if (RunNumber == 301065){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_800M1000";  
  crossSection = 17.668 * 1; // 17.668 fb
}
else if (RunNumber == 301066){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_1000M1250";
  crossSection = 7.2895 * 1; // 7.2895 fb
}
else if (RunNumber == 301067){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_1250M1500";
  crossSection = 2.5071 * 1; // 2.5071 fb
}
else if (RunNumber == 301068){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_1500M1750";
  crossSection = 0.98628 * 1; // 0.98628 fb
}
else if (RunNumber == 301069){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_1750M2000";
  crossSection = 0.4245 * 1; // 0.4245 fb
}
else if (RunNumber == 301070){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_2000M2250";
  crossSection = 0.19463 * 1; // 0.19463 fb
}
else if (RunNumber == 301071){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_2250M2500";
  crossSection = 0.093349 * 1; // 0.093349 fb
}
else if (RunNumber == 301072){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_2500M2750";
  crossSection = 0.046259 * 1; // 0.046259 fb
}
else if (RunNumber == 301073){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_2750M3000";
  crossSection = 0.023476 * 1; // 0.023476 fb
}
else if (RunNumber == 301074){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_3000M3500";
  crossSection = 0.01845 * 1; // 0.01845 fb
}
else if (RunNumber == 301075){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_3500M4000";
  crossSection = 0.0050968 * 1; // 0.0050968 fb
}
else if (RunNumber == 301076){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_4000M4500";
  crossSection = 0.0014307 * 1; // 0.0014307 fb
}
else if (RunNumber == 301077){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_4500M5000";
  crossSection = 0.00040127 * 1; // 0.00040127 fb
}else if (RunNumber == 301078){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu_5000M";
  crossSection = 0.00015346 * 1; // 0.00015346 fb
}
else if (RunNumber == 301080){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_120M180";
  crossSection = 22198.0 * 1; // 22198.0 fb
}
else if (RunNumber == 301081){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_180M250";
  crossSection = 3285.2 * 1; // 3285.2 fb
}
else if (RunNumber == 301082){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_250M400";
  crossSection = 1083.2 * 1; // 1083.2 fb
}
else if (RunNumber == 301083){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_400M600";
  crossSection = 175.41 * 1; // 175.41 fb
}
else if (RunNumber == 301084){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_600M800";
  crossSection = 30.98 * 1; // 30.98 fb
}
else if (RunNumber == 301085){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_800M1000";
  crossSection = 8.2865 * 1; // 8.2865 fb
}
else if (RunNumber == 301086){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_1000M1250";
  crossSection = 3.1594 * 1; // 3.1594 fb
}
else if (RunNumber == 301087){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_1250M1500";
  crossSection = 1.0029 * 1; // 1.0029 fb
}
else if (RunNumber == 301088){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_1500M1750";
  crossSection = 0.36812 * 1; // 0.36812 fb
}
else if (RunNumber == 301089){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_1750M2000";
  crossSection = 0.14945 * 1; // 0.14945 fb
}
else if (RunNumber == 301090){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_2000M2250";
  crossSection = 0.065311 * 1; // 0.065311 fb
}
else if (RunNumber == 301091){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_2250M2500";  
  crossSection = 0.030167 * 1; // 0.030167 fb
}
else if (RunNumber == 301092){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_2500M2750";
  crossSection = 0.014549 * 1; // 0.014549 fb
}
else if (RunNumber == 301093){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_2750M3000";
  crossSection = 0.0072592 * 1; // 0.0072592 fb
}
else if (RunNumber == 301094){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_3000M3500";
  crossSection = 0.0056692 * 1; // 0.0056692 fb
}
else if (RunNumber == 301095){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_3500M4000";
  crossSection = 0.0015975 * 1; // 0.0015975 fb
}
else if (RunNumber == 301096){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_4000M4500";
  crossSection = 0.0004721 * 1; // 0.0004721 fb
}
else if (RunNumber == 301097){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_4500M5000";
  crossSection = 0.00014279 * 1; // 0.00014279 fb
}
else if (RunNumber == 301098){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminenu_5000M";
  crossSection = 6.1624e-05 * 1; // 6.1624e-05 fb
}
else if (RunNumber == 301100){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_120M180";
  crossSection = 32053.0 * 1; // 32053.0 fb
}
else if (RunNumber == 301101){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_180M250";
  crossSection = 5002.9 * 1; // 5002.9 fb
}
else if (RunNumber == 301102){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_250M400";
  crossSection = 1754.3 * 1; // 1754.3 fb
}
else if (RunNumber == 301103){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_400M600";
  crossSection = 312.35 * 1; // 312.35 fb
}
else if (RunNumber == 301104){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_600M800";
  crossSection = 60.793 * 1; // 60.793 fb
}else if (RunNumber == 301105){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_800M1000";
  crossSection = 17.668 * 1; // 17.668 fb
}
else if (RunNumber == 301106){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_1000M1250";
  crossSection = 7.2895 * 1; // 7.2895 fb
}
else if (RunNumber == 301107){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_1250M1500";
  crossSection = 2.5071 * 1; // 2.5071 fb
}
else if (RunNumber == 301108){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_1500M1750";
  crossSection = 0.98628 * 1; // 0.98628 fb
}
else if (RunNumber == 301109){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_1750M2000";
  crossSection = 0.42457 * 1; // 0.42457 fb
}
else if (RunNumber == 301110){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_2000M2250";
  crossSection = 0.19463 * 1; // 0.19463 fb
}
else if (RunNumber == 301111){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_2250M2500";
  crossSection = 0.093349 * 1; // 0.093349 fb
}
else if (RunNumber == 301112){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_2500M2750";
  crossSection = 0.046259 * 1; // 0.046259 fb
}
else if (RunNumber == 301113){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_2750M3000";
  crossSection = 0.023476 * 1; // 0.023476 fb
}
else if (RunNumber == 301114){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_3000M3500";
  crossSection = 0.01845 * 1; // 0.01845 fb
}
else if (RunNumber == 301115){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_3500M4000";
  crossSection = 0.0050968 * 1; // 0.0050968 fb
}
else if (RunNumber == 301116){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_4000M4500";
  crossSection = 0.0014307 * 1; // 0.0014307 fb
}
else if (RunNumber == 301117){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_4500M5000";  
  crossSection = 0.00040127 * 1; // 0.00040127 fb
}
else if (RunNumber == 301118){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu_5000M";
  crossSection = 0.00015346 * 1; // 0.00015346 fb
}
else if (RunNumber == 301120){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_120M180";
  crossSection = 22198.0 * 1; // 22198.0 fb
}
else if (RunNumber == 301121){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_180M250";
  crossSection = 3285.3 * 1; // 3285.3 fb
}
else if (RunNumber == 301122){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_250M400";
  crossSection = 1083.2 * 1; // 1083.2 fb
}
else if (RunNumber == 301123){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_400M600";
  crossSection = 175.41 * 1; // 175.41 fb
}
else if (RunNumber == 301124){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_600M800";
  crossSection = 30.98 * 1; // 30.98 fb
}
else if (RunNumber == 301125){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_800M1000";
  crossSection = 8.2865 * 1; // 8.2865 fb
}
else if (RunNumber == 301126){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_1000M1250";
  crossSection = 3.1594 * 1; // 3.1594 fb
}
else if (RunNumber == 301127){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_1250M1500";
  crossSection = 1.0029 * 1; // 1.0029 fb
}
else if (RunNumber == 301128){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_1500M1750";
  crossSection = 0.36812 * 1; // 0.36812 fb
}
else if (RunNumber == 301129){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_1750M2000";
  crossSection = 0.14945 * 1; // 0.14945 fb
}
else if (RunNumber == 301130){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_2000M2250";
  crossSection = 0.065311 * 1; // 0.065311 fb
}else if (RunNumber == 301131){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_2250M2500";
  crossSection = 0.030167 * 1; // 0.030167 fb
}
else if (RunNumber == 301132){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_2500M2750";
  crossSection = 0.014549 * 1; // 0.014549 fb
}
else if (RunNumber == 301133){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_2750M3000";
  crossSection = 0.0072592 * 1; // 0.0072592 fb
}
else if (RunNumber == 301134){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_3000M3500";
  crossSection = 0.0056692 * 1; // 0.0056692 fb
}
else if (RunNumber == 301135){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_3500M4000";
  crossSection = 0.0015975 * 1; // 0.0015975 fb
}
else if (RunNumber == 301136){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_4000M4500";
  crossSection = 0.0004721 * 1; // 0.0004721 fb
}
else if (RunNumber == 301137){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_4500M5000";
  crossSection = 0.00014279 * 1; // 0.00014279 fb
}
else if (RunNumber == 301138){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminmunu_5000M";
  crossSection = 6.1624e-05 * 1; // 6.1624e-05 fb
}
else if (RunNumber == 301140){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_120M180";
  crossSection = 32053.0 * 1; // 32053.0 fb
}
else if (RunNumber == 301141){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_180M250";
  crossSection = 5002.9 * 1; // 5002.9 fb
}
else if (RunNumber == 301142){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_250M400";
  crossSection = 1754.3 * 1; // 1754.3 fb
}
else if (RunNumber == 301143){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_400M600";
  crossSection = 312.35 * 1; // 312.35 fb
}
else if (RunNumber == 301144){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_600M800";  
  crossSection = 60.793 * 1; // 60.793 fb
}
else if (RunNumber == 301145){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_800M1000";
  crossSection = 17.668 * 1; // 17.668 fb
}
else if (RunNumber == 301146){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_1000M1250";
  crossSection = 7.2895 * 1; // 7.2895 fb
}
else if (RunNumber == 301147){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_1250M1500";
  crossSection = 2.5071 * 1; // 2.5071 fb
}
else if (RunNumber == 301148){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_1500M1750";
  crossSection = 0.98628 * 1; // 0.98628 fb
}
else if (RunNumber == 301149){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_1750M2000";
  crossSection = 0.42457 * 1; // 0.42457 fb
}
else if (RunNumber == 301150){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_2000M2250";
  crossSection = 0.19463 * 1; // 0.19463 fb
}
else if (RunNumber == 301151){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_2250M2500";
  crossSection = 0.093349 * 1; // 0.093349 fb
}
else if (RunNumber == 301152){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_2500M2750";
  crossSection = 0.046259 * 1; // 0.046259 fb
}
else if (RunNumber == 301153){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_2750M3000";
  crossSection = 0.023476 * 1; // 0.023476 fb
}
else if (RunNumber == 301154){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_3000M3500";
  crossSection = 0.01845 * 1; // 0.01845 fb
}
else if (RunNumber == 301155){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_3500M4000";
  crossSection = 0.0050968 * 1; // 0.0050968 fb
}
else if (RunNumber == 301156){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_4000M4500";
  crossSection = 0.0014307 * 1; // 0.0014307 fb
}else if (RunNumber == 301157){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_4500M5000";
  crossSection = 0.00040127 * 1; // 0.00040127 fb
}
else if (RunNumber == 301158){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu_5000M";
  crossSection = 0.00015346 * 1; // 0.00015346 fb
}
else if (RunNumber == 301160){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_120M180";
  crossSection = 22198.0 * 1; // 22198.0 fb
}
else if (RunNumber == 301161){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_180M250";
  crossSection = 3285.2 * 1; // 3285.2 fb
}
else if (RunNumber == 301162){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_250M400";
  crossSection = 1083.2 * 1; // 1083.2 fb
}
else if (RunNumber == 301163){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_400M600";
  crossSection = 175.41 * 1; // 175.41 fb
}
else if (RunNumber == 301164){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_600M800";
  crossSection = 30.98 * 1; // 30.98 fb
}
else if (RunNumber == 301165){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_800M1000";
  crossSection = 8.2865 * 1; // 8.2865 fb
}
else if (RunNumber == 301166){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_1000M1250";
  crossSection = 3.1594 * 1; // 3.1594 fb
}
else if (RunNumber == 301167){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_1250M1500";
  crossSection = 1.0029 * 1; // 1.0029 fb
}
else if (RunNumber == 301168){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_1500M1750";
  crossSection = 0.36812 * 1; // 0.36812 fb
}
else if (RunNumber == 301169){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_1750M2000";
  crossSection = 0.14945 * 1; // 0.14945 fb
}
else if (RunNumber == 301170){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_2000M2250";  
  crossSection = 0.065311 * 1; // 0.065311 fb
}
else if (RunNumber == 301171){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_2250M2500";
  crossSection = 0.030167 * 1; // 0.030167 fb
}
else if (RunNumber == 301172){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_2500M2750";
  crossSection = 0.014549 * 1; // 0.014549 fb
}
else if (RunNumber == 301173){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_2750M3000";
  crossSection = 0.0072592 * 1; // 0.0072592 fb
}
else if (RunNumber == 301174){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_3000M3500";
  crossSection = 0.0056692 * 1; // 0.0056692 fb
}
else if (RunNumber == 301175){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_3500M4000";
  crossSection = 0.0015975 * 1; // 0.0015975 fb
}
else if (RunNumber == 301176){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_4000M4500";
  crossSection = 0.0004721 * 1; // 0.0004721 fb
}
else if (RunNumber == 301177){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_4500M5000";
  crossSection = 0.00014279 * 1; // 0.00014279 fb
}
else if (RunNumber == 301178){
  name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wmintaunu_5000M";
  crossSection = 6.1624e-05 * 1; // 6.1624e-05 fb
}
else if (RunNumber == 301535 ){
    name = "Sherpa_CT10_eegammaPt10_35";
    crossSection = 52706 * 1 ; // 1 fb 
}
else if (RunNumber == 301536 ){
    name = "Sherpa_CT10_mumugammaPt10_35";
    crossSection = 52708 * 1 ; // 1 fb 
}
else if (RunNumber == 301899 ){
    name = "Sherpa_CT10_eegammaPt35_70";
    crossSection = 5242 * 1 ; // 1 fb 
}
else if (RunNumber == 301900 ){
    name = "Sherpa_CT10_eegammaPt70_140";
    crossSection = 384.55 * 1 ; // 1 fb 
}
else if (RunNumber == 301901 ){
    name = "Sherpa_CT10_eegammaPt140";
    crossSection = 47.209 * 1 ; // 1 fb 
}
else if (RunNumber == 301902 ){
    name = "Sherpa_CT10_mumugammaPt35_70";
    crossSection = 5245.5 * 1 ; // 1 fb 
}
else if (RunNumber == 301903 ){
    name = "Sherpa_CT10_mumugammaPt70_140";
    crossSection = 385.48 * 1 ; // 1 fb 
}
else if (RunNumber == 301904 ){
    name = "Sherpa_CT10_mumugammaPt140";
    crossSection = 47.240 * 1 ; // 1 fb 
}
else if (RunNumber==305612){
 name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llvv_c10_m0700";
 crossSection = 12.76*1.0; // fb 
 }
else if (RunNumber==305613){
 name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llvv_c10_m0750";
 crossSection = 8.568*1.0; // fb 
 }
else if (RunNumber==305614){
 name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llvv_c10_m0900";
 crossSection = 3.012*1.0; // fb 
 }
else if (RunNumber == 341103 ){
   name = "Sherpa_CT10_Zee_4lMassFilter40GeV8GeV";
   crossSection = 2226300.0 * 0.00054683 * k_Zll_sherpa; // 1217.407629 fb
}
else if (RunNumber == 341104 ){
    name = "Sherpa_CT10_Zmumu_4lMassFilter40GeV8GeV";
    crossSection = 2226300. * 5.5139e-4 * k_Zll_sherpa ; // fb 
}
else if (RunNumber == 341105){
  name = "Sherpa_CT10_Zee_3lPtFilter4GeV_4lMassVeto40GeV8GeV";
  crossSection = 31423.7859 * k_Zll_sherpa; // 31423.7859 fb
}
else if (RunNumber == 341106 ){
    name = "Sherpa_CT10_Zmumu_3lPtFilter4GeV_4lMassVeto40GeV8GeV";
    crossSection = 2226300. * 1.4181e-2 * k_Zll_sherpa ; // fb 
}
else if (RunNumber == 344152 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHv2p5kAvm5";
    //crossSection = 0.54263 * 1.0 * k_madGraphVBF ; // 0.54263 fb 
    crossSection = 0.54263 * 1.0; // 0.54263 fb 
}
else if (RunNumber == 344153 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHv5kAv5";
    //crossSection = 0.9572 * 1.0 * k_madGraphVBF; // 0.9572 fb 
    crossSection = 0.9572 * 1.0 ; // 0.9572 fb 
}
else if (RunNumber == 344154 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHv5kAv6";
    //crossSection = 1.1259 * 1.0 * k_madGraphVBF; // 1.1259 fb 
    crossSection = 1.1259 * 1.0 ; // 1.1259 fb 
}
else if (RunNumber == 344155 ){
    name = "MGPy8EG_A14NNPDF23LO_vbfhzz4l_0pphmkHvm2p5kAvm5";
    //crossSection = 0.49501 * 1.0 * k_madGraphVBF; // 0.49501 fb 
    crossSection = 0.49501 * 1.0 ; // 0.49501 fb 
}
else if (RunNumber == 344156 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHvm5kAv5";
    //crossSection = 0.68577 * 1.0 * k_madGraphVBF; // 0.68577 fb 
    crossSection = 0.68577 * 1.0 ; // 0.68577 fb 
}
else if (RunNumber == 344157 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHvm5kAvm6";
    //crossSection = 0.78352 * 1.0 * k_madGraphVBF; // 0.78352 fb 
    crossSection = 0.78352 * 1.0 ; // 0.78352 fb 
}
else if (RunNumber == 344158 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_ppx0_FxFx_Np012_SM";
    crossSection = 4.1138 * 1.0 ; // 4.1138 fb 
}
else if (RunNumber == 344159 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kHvv1_cosa1p0";
    crossSection = 0.0052706 * 1.0 ; // 0.0052706 fb 
}
else if (RunNumber == 344160 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kHvv6_cosa1p0";
    crossSection = 5.8117 * 1.0 ; // 5.8117 fb 
}
else if (RunNumber == 344161 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kHvvn6_cosa1p0";
    crossSection = 2.8045 * 1.0 ; // 2.8045 fb 
}
else if (RunNumber == 344162 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAvv1_cosa0p707";
    crossSection = 0.00054022 * 1.0 ; // 0.00054022 fb 
}
else if (RunNumber == 344163 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAvv6_cosa0p707";
    crossSection = 1.0505 * 1.0 ; // 1.0505 fb 
}
else if (RunNumber == 344164 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAvvn6_cosa0p707";
    crossSection = 1.0484 * 1.0 ; // 1.0484 fb 
}
else if (RunNumber == 344165 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAHvv6_cosa0p707";
    crossSection = 1.4705 * 1.0 ; // 1.4705 fb 
}
else if (RunNumber == 344166 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAHvvn6_cosa0p707";
    crossSection = 0.7242 * 1.0 ; // 0.7242 fb 
}
else if (RunNumber == 344167 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAgg0p5_cosa0p707";
    crossSection = 1.6097 * 1.0 ; // 1.6097 fb 
}
else if (RunNumber == 344168 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAggn0p5_cosa0p707";
    crossSection = 1.6257 * 1.0 ; // 1.6257 fb 
}
else if (RunNumber == 344169 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAgg1p41_cosa0p707";
    crossSection = 13.38 * 1.0 ; // 13.38 fb 
}
else if (RunNumber == 344170 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAgg1_cosa0p707";
    crossSection = 2.3182 * 1.0 ; // 2.3182 fb 
}
else if (RunNumber == 344171 ){
    name = "PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_4lMFilt_40_8";
    crossSection = 696230.0 * 0.10536 * 0.049160257 ; // XS * "generator level" filter efficiency * "afterburn level" filter efficiency
}
else if (RunNumber==344172){
 name = "PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH750NW_ZZllvv";
 crossSection = 446.36*0.44517; // fb 
 }
else if (RunNumber == 344173 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH750NW_ZZllvv";
    crossSection = 182.36 * 0.44554 ; // 81.2486744 fb 
}
else if (RunNumber==344174){
 name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_HZZllvv750w5";
 crossSection = 29.457*1; // fb 
 }
else if (RunNumber==344175){
 name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_HZZllvv750w10";
 crossSection = 14.261*1; // fb 
 }
else if (RunNumber==344176){
 name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_HZZllvv750w15";
 crossSection = 9.1685*1; // fb 
 }
else if (RunNumber==344135){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0p";
 crossSection = 0.0674*1.0; // fb 
 }
else if (RunNumber==344136){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphkHv5";
 crossSection = 0.449*1.0; // fb 
 }
else if (RunNumber==344137){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphkHvm5";
 crossSection = 0.675*1.0; // fb 
 }
else if (RunNumber==344138){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphkHv2p5";
 crossSection = 0.0704*1.0; // fb 
 }
else if (RunNumber==344139){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphkHvm2p5";
 crossSection = 0.305*1.0; // fb 
 }
else if (RunNumber==344140){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0phkHv10";
 crossSection = 0.291*1.0; // fb 
 }
else if (RunNumber==344141){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkAv5";
 crossSection = 0.106*1.0; // fb 
 }
else if (RunNumber==344142){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkAvm5";
 crossSection = 0.106*1.0; // fb 
 }
else if (RunNumber==344143){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkAv2p5";
 crossSection = 0.0389*1.0; // fb 
 }
else if (RunNumber==344144){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkAvm2p5";
 crossSection = 0.039*1.0; // fb 
 }
else if (RunNumber==344145){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0mkAv15";
 crossSection = 0.0939*1.0; // fb 
 }
else if (RunNumber==344146){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHv2p5kAvm5";
 crossSection = 0.121*1.0; // fb 
 }
else if (RunNumber==344147){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHvm2p5kAvm5";
 crossSection = 0.154*1.0; // fb 
 }
else if (RunNumber==344148){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHvm5kAv5";
 crossSection = 0.237*1.0; // fb 
 }
else if (RunNumber==344149){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHvm5kAvm6";
 crossSection = 0.268*1.0; // fb 
 }
else if (RunNumber==344150){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHv5kAv6";
 crossSection = 0.285*1.0; // fb 
 }
else if (RunNumber==344151){
 name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHv5kAv5";
 crossSection = 0.232*1.0; // fb 
 }
else if (RunNumber == 344229 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_10SMW_2e2mu_m4l130";
    crossSection = 2801.6 * 1.7 /1000; // 2801.6 fb 
}
else if (RunNumber == 344230 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_10SMW_4e_m4l130";
    crossSection = 1395.9 * 1.7 /1000; // 1395.9 fb 
}
else if (RunNumber == 344231 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_10SMW_4mu_m4l130";
    crossSection = 1395.9 * 1.7 /1000; // 1395.9 fb 
}
else if (RunNumber == 344232 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_2e2mu_m4l100to130";
    crossSection = 726.87 * 1.7 /1000; // 726.87 fb 
}
else if (RunNumber == 344233 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_2e2mu_m4l130";
    crossSection = 2288.4 * 1.7 /1000; // 2288.4 fb 
}
else if (RunNumber == 344234 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_4e_m4l100to130";
    crossSection = 388.94 * 1.7 /1000; // 388.94 fb 
}
else if (RunNumber == 344821 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_4e_m4l130";
    crossSection = 1139.0 * 1.7 /1000; // 1139.0 fb 
}
else if (RunNumber == 344822 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_4mu_m4l100to130";
    crossSection = 388.94 * 1.7 /1000; // 388.94 fb 
}
else if (RunNumber == 344823 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_4mu_m4l130";
    crossSection = 1139.0 * 1.7 /1000; // 1139.0 fb 
}
else if (RunNumber == 344824 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_5SMW_2e2mu_m4l130";
    crossSection = 2.4572 * 1.7 ; // 2457.2 fb
}
else if (RunNumber == 344825 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_5SMW_4e_m4l130";
    crossSection = 1223.7 * 1.7 /1000; // 1223.7 fb 
}
else if (RunNumber == 344826 ){
    name = "MCFMPythia8EvtGen_ggH_gg_ZZ_5SMW_4mu_m4l130";
    crossSection = 1223.7 * 1.7 /1000; // 1223.7 fb 
}
else if (RunNumber == 344827 ){
    name = "MCFMPythia8EvtGen_ggH_ZZ_2e2mu_m4l100to130";
    crossSection = 594.4 * 1.7 /1000; // 594.4 fb 
}
else if (RunNumber == 344828 ){
    name = "MCFMPythia8EvtGen_ggH_ZZ_2e2mu_m4l130";
    crossSection = 107.81 * 1.7 /1000; // 107.81 fb 
}
else if (RunNumber == 344829 ){
    name = "MCFMPythia8EvtGen_ggH_ZZ_4e_m4l100to130";
    crossSection = 325.04 * 1.7 /1000; // 325.04 fb 
}
else if (RunNumber == 344830 ){
    name = "MCFMPythia8EvtGen_ggH_ZZ_4e_m4l130";
    crossSection = 53.89 * 1.7 /1000; // 53.89 fb 
}
else if (RunNumber == 344831 ){
    name = "MCFMPythia8EvtGen_ggH_ZZ_4mu_m4l100to130";
    crossSection = 325.04 * 1.7 /1000; // 325.04 fb 
}
else if (RunNumber == 344832 ){
    name = "MCFMPythia8EvtGen_ggH_ZZ_4mu_m4l130";
    crossSection = 53.884 * 1.7 /1000; // 53.884 fb 
}
else if (RunNumber == 344833 ){
    name = "MCFMPythia8EvtGen_gg_ZZ_2e2mu_m4l100";
    crossSection = 2523.8 * 1.7 /1000; // 2523.8 fb 
}
else if (RunNumber == 344834 ){
    name = "MCFMPythia8EvtGen_gg_ZZ_4e_m4l100";
    crossSection = 1254.2 * 1.7 /1000; // 1254.2 fb 
}
else if (RunNumber == 344835 ){
    name = "MCFMPythia8EvtGen_gg_ZZ_4mu_m4l100";
    crossSection = 1254.2 * 1.7 /1000; // 1254.2 fb 
}
else if (RunNumber == 344295 ){
    name = "Sherpa_NNPDF30NNLO_Zee_4lMassFilter40GeV8GeV";
    crossSection = 2071300.0 * 0.00060102 * k_Zll_Sherpa22; // 1244.892726 fb 
}
else if (RunNumber == 344296 ){
    name = "Sherpa_NNPDF30NNLO_Zmumu_4lMassFilter40GeV8GeV";
    crossSection = 2061600.0 * 0.00060991 * k_Zll_Sherpa22; // 1257.390456 fb 
}

else if (RunNumber == 344297 ){
    name = "Sherpa_NNPDF30NNLO_Zee_3lPtFilter4GeV_4lMassVeto40GeV8GeV";
    crossSection = 2071300.0 * 0.013261 * k_Zll_Sherpa22; // 27467.5093 fb 
}

else if (RunNumber == 344298 ){
    name = "Sherpa_NNPDF30NNLO_Zmumu_3lPtFilter4GeV_4lMassVeto40GeV8GeV";
    crossSection = 2071500.0 * 0.013319 * k_Zll_Sherpa22; // 27590.3085 fb 
}
else if (RunNumber == 342556 ){
    name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_100_150";
    crossSection = 1279.1 * 0.032522 ; // 41.5988902 fb
} 
else if (RunNumber == 343212 ){
    name = "Powheggg2vvPythia8EvtGen_gg_ZZ_bkg_2e2mu_13TeV";
    crossSection = 2.749987*1.7 ; // from Jochen; 1.7 - kFactor for NLO
} 
else if (RunNumber == 343213 ){
    name = "Powheggg2vvPythia8EvtGen_gg_ZZ_bkg_4l_noTau_13TeV";
    crossSection = 2.701975*1.7 ; // from Jochen; 1.7 - kFactor for NLO
} 
else if (RunNumber == 343233 ){
    name = "Powheggg2vvPythia8EvtGen_ggH125p5_gg_ZZ_2l2v_13TeV";
    //crossSection = 34.583571 * 0.66248; // from Jochen
    crossSection = 34.583571 * 0.66248 * 1.5; // *1.5 added to account for 3 v flavours (modelled with only 2 neutrino flavours originally) 
} 
else if (RunNumber == 361020 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ0W";
    crossSection = 7.842e+13 * 4.468e-4 ; //  fb 
}
else if (RunNumber == 361021 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ1W";
    crossSection = 7.842e+13 * 2.0252e-5; //  fb 
}
else if (RunNumber == 361022 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ2W";
    crossSection = 2.4332e+12 * 0.00033264 ; // 809379648.0 fb 
}
else if (RunNumber == 361023 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ3W";
    crossSection = 26454000000.0 * 0.00031953 ; // 8452846.62 fb 
}
else if (RunNumber == 361024 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ4W";
    crossSection = 254630000.0 * 0.00053009 ; // 134976.8167 fb 
}
else if (RunNumber == 361025 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ5W";
    crossSection = 4553500.0 * 0.00092325 ; // 4204.018875 fb 
}
else if (RunNumber == 361026 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ6W";
    crossSection = 257530.0 * 0.00094016 ; // 242.1194048 fb 
}
else if (RunNumber == 361027 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ7W";
    crossSection = 16215.0 * 0.00039282 ; // 6.3695763 fb 
}
else if (RunNumber == 361028 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ8W";
    crossSection = 625.02 * 0.010162 ; // 6.35145324 fb 
}
else if (RunNumber == 361029 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ9W";
    crossSection = 19.639 * 0.012054 ; // 0.236728506 fb 
}
else if (RunNumber == 361030 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ10W";
    crossSection = 1.1962 * 0.0058935 ; // 0.0070498047 fb 
}
else if (RunNumber == 361031 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ11W";
    crossSection = 0.042258 * 0.0027015 ; // 0.000114159987 fb 
}
else if (RunNumber == 361032 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ12W";
    crossSection = 0.0010367 * 0.00042502 ; // 4.40618234e-07 fb 
}
else if (RunNumber == 361063 ){
    name = "Sherpa_CT10_llll";
    crossSection = 12849.0 * 1.0 * k_ZZ_sherpa ; // fb 
}
else if (RunNumber == 361064 ){
    name = "Sherpa_CT10_lllvSFMinus";
    crossSection = 1844.6 * 1.0 ; // 1844.6 fb 
}
else if (RunNumber == 361065 ){
    name = "Sherpa_CT10_lllvOFMinus";
    crossSection = 3623.5 * 1.0 ; // 3623.5 fb 
}
else if (RunNumber == 361066 ){
    name = "Sherpa_CT10_lllvSFPlus";
    crossSection = 2565.6 * 1.0 ; // 2565.6 fb 
}
else if (RunNumber == 361067 ){
    name = "Sherpa_CT10_lllvOFPlus";
    crossSection = 5016.9 * 1.0 ; // 5016.9 fb 
}
else if (RunNumber == 361068 ){
    name = "Sherpa_CT10_llvv";
    crossSection = 14022.0 * 1.0 ; // 14022.0 fb 
}
else if (RunNumber == 361069 ){
    name = "Sherpa_CT10_llvvjj_ss_EW4";
    crossSection = 25.765 * 1.0 ; // 25.765 fb 
}
else if (RunNumber == 361070 ){
    name = "Sherpa_CT10_llvvjj_ss_EW6";
    crossSection = 43.375 * 1 ; //  fb 
}
else if (RunNumber == 361071 ){
    name = "Sherpa_CT10_lllvjj_EW6";
    crossSection = 42.017 * 1.0 ; // 42.017 fb 
}
else if (RunNumber == 361072 ){
    name = "Sherpa_CT10_lllljj_EW6";
    crossSection = 31.496 * 1.0 ; // 31.496 fb 
}
else if (RunNumber == 361073 ){
    name = "Sherpa_CT10_ggllll";
    //crossSection = 20.931 * 1.7 * 0.91 ; // 20.931 * 1.7 * 0.91  k-factor fb 
    crossSection = 20.743 * 1.7 * 0.91 ; // Corrected following advice of PMG: 20.743 * 1.7 * 0.91  k-factor fb 
}
else if (RunNumber == 361074 ){
   name = "Sherpa_CT10_ggllll_M4l100";
   crossSection = 16.161 *  0.91 * 1.7  ; // 16.161 fb * 0.91 * 1.7 k-factor (added 13 December 2016)
}
else if (RunNumber==361075){
 name = "Sherpa_CT10_ggllllNoHiggs";
 //crossSection = 11.826*1.7 * 0.91 ; // fb 
 crossSection = 11.1*1.7 * 0.91 ; // fb -- updated to match PMG (HH 05/16/2017) 
 }
else if (RunNumber==361076){
 name = "Sherpa_CT10_ggllllOnlyHiggs";
 crossSection = 6.272*1.7 * 0.91 ; // fb 
 }
else if (RunNumber == 361077 ){
    name = "Sherpa_CT10_ggllvv";
    crossSection = 854.92 * 1.0 ; // 854.92 fb 
}
else if (RunNumber == 361081 ){
    name = "Sherpa_CT10_WplvWmqq";
    crossSection = 25995.0 * 1.0 ; // 25995.0 fb 
}
else if (RunNumber == 361082 ){
    name = "Sherpa_CT10_WpqqWmlv";
    crossSection = 25974.0 * 1.0169 ; // 26412.9606 fb 
}
else if (RunNumber == 361083 ){
    name = "Sherpa_CT10_WlvZqq";
    crossSection = 12543.0 * 1.0 ; // 12543.0 fb 
}
else if (RunNumber == 361084 ){
    name = "Sherpa_CT10_WqqZll";
    crossSection = 3758.3 * 1.0 ; // 3758.3 fb 
}
else if (RunNumber == 361085 ){
    name = "Sherpa_CT10_WqqZvv";
    crossSection = 7415.1 * 1.0 ; // 7415.1 fb 
}
else if (RunNumber == 361086 ){
    name = "Sherpa_CT10_ZqqZll";
    crossSection = 16590.0 * 0.14253 ; // 2364.5727 fb 
}
else if (RunNumber == 361087 ){
    name = "Sherpa_CT10_ZqqZvv";
    crossSection = 16492.0 * 0.28096 ; //  fb 
}
else if (RunNumber == 361090 ){
    name = "Sherpa_CT10_llll_M4l100";
    crossSection = 1594.8 * 1.0004 * k_ZZ_sherpa ; // 1595.43792 fb 
}
else if (RunNumber == 361100 ){
    name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusenu";
    //crossSection = 11306000.0 * 1.0236 * k_Wplus_powheg; // 11572821.6 fb -- 4 November 2016: set filter efficiency to 1 based on Twiki; was 1.0236 
    crossSection = 11306000.0 * 1 * k_Wplus_powheg; // 11572821.6 fb -- 4 November 2016: set filter efficiency to 1 based on Twiki; was 1.0236 
}
else if (RunNumber == 361101 ){
    name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplusmunu";
    crossSection = 11306000.0 * 1.0 * k_Wplus_powheg; // 11306000.0 fb 
}
else if (RunNumber == 361102 ){
    name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wplustaunu";
    crossSection = 11306000.0 * 1.0 * k_Wplus_powheg; // 11306000.0 fb 
}
else if (RunNumber == 361103 ){
    name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusenu";
    crossSection = 8282600 * 1.0 * k_Wminus_powheg; //  fb 
}
else if (RunNumber == 361104 ){
    name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminusmunu";
    crossSection = 8282600.0 * 1.0 * k_Wminus_powheg; // 8282600.0 fb 
}
else if (RunNumber == 361105 ){
    name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Wminustaunu";
    crossSection = 8282600.0 * 1.0 * k_Wminus_powheg; // 8282600.0 fb 
}
else if (RunNumber == 361106 ){
    name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee";
    crossSection = 1901200.0 * 1.0 * k_Zll_powheg; // 1901200.0 fb 
}
else if (RunNumber == 361107 ){
    name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu";
    crossSection = 1901200.0 * 1.0 * k_Zll_powheg; // 1901200.0 fb 
}
else if (RunNumber == 361108 ){
    name = "PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau";
    crossSection = 1901200.0 * 1.0 * k_Zll_powheg; // 1901200.0 fb 
}
else if (RunNumber ==  361300  ){
    name = " Sherpa_CT10_Wenu_Pt0_70_CVetoBVeto ";
    crossSection =  21380000.0  *  0.8915  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361301  ){
    name = " Sherpa_CT10_Wenu_Pt0_70_CFilterBVeto ";
    crossSection =  21380000.0  *  0.04846  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361302  ){
    name = " Sherpa_CT10_Wenu_Pt0_70_BFilter ";
    crossSection =  21380000.0  *  0.05973  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361303  ){
    name = " Sherpa_CT10_Wenu_Pt70_140_CVetoBVeto ";
    crossSection =  631100.0  *  0.7278  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361304  ){
    name = " Sherpa_CT10_Wenu_Pt70_140_CFilterBVeto ";
    crossSection =  631100.0  *  0.1760  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361305  ){
    name = " Sherpa_CT10_Wenu_Pt70_140_BFilter ";
    crossSection =  631100.0  *  0.09637  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361306  ){
    name = " Sherpa_CT10_Wenu_Pt140_280_CVetoBVeto ";
    crossSection =  90070.0  *  0.6832  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361307  ){
    name = " Sherpa_CT10_Wenu_Pt140_280_CFilterBVeto ";
    crossSection =  90070.0  *  0.2048  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361308  ){
    name = " Sherpa_CT10_Wenu_Pt140_280_BFilter ";
    crossSection =  90070.0  *  0.1126  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361309  ){
    name = " Sherpa_CT10_Wenu_Pt280_500_CVetoBVeto ";
    crossSection =  6520.0  *  0.6513  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361310  ){
    name = " Sherpa_CT10_Wenu_Pt280_500_CFilterBVeto ";
    crossSection =  6520.0  *  0.2210  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361311  ){
    name = " Sherpa_CT10_Wenu_Pt280_500_BFilter ";
    crossSection =  6520.0  *  0.1314  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361312  ){
    name = " Sherpa_CT10_Wenu_Pt500_700_CVetoBVeto ";
    crossSection =  415.4  *  0.6306  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361313  ){
    name = " Sherpa_CT10_Wenu_Pt500_700_CFilterBVeto ";
    crossSection =  415.4  *  0.2380  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361314  ){
    name = " Sherpa_CT10_Wenu_Pt500_700_BFilter ";
    crossSection =  415.4  *  0.1594  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361315  ){
    name = " Sherpa_CT10_Wenu_Pt700_1000_CVetoBVeto ";
    crossSection =  79.31  *  0.6232  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361316  ){
    name = " Sherpa_CT10_Wenu_Pt700_1000_CFilterBVeto ";
    crossSection =  79.31  *  0.2168  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361317  ){
    name = " Sherpa_CT10_Wenu_Pt700_1000_BFilter ";
    crossSection =  79.31  *  0.1615  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361318  ){
    name = " Sherpa_CT10_Wenu_Pt1000_2000_CVetoBVeto ";
    crossSection =  10.3  *  0.6114  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361319  ){
    name = " Sherpa_CT10_Wenu_Pt1000_2000_CFilterBVeto ";
    crossSection =  10.3  *  0.2375  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361320  ){
    name = " Sherpa_CT10_Wenu_Pt1000_2000_BFilter ";
    crossSection =  10.3  *  0.1696  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361321  ){
    name = " Sherpa_CT10_Wenu_Pt2000_E_CMS_CVetoBVeto ";
    crossSection =  0.0428  *  0.6006  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361322  ){
    name = " Sherpa_CT10_Wenu_Pt2000_E_CMS_CFilterBVeto ";
    crossSection =  0.0428  *  0.2610  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361323  ){
    name = " Sherpa_CT10_Wenu_Pt2000_E_CMS_BFilter ";
    crossSection =  0.0428  *  0.1847  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361324  ){
    name = " Sherpa_CT10_Wmunu_Pt0_70_CVetoBVeto ";
    crossSection =  21380000.0  *  0.8915  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361325  ){
    name = " Sherpa_CT10_Wmunu_Pt0_70_CFilterBVeto ";
    crossSection =  21380000.0  *  0.04846  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361326  ){
    name = " Sherpa_CT10_Wmunu_Pt0_70_BFilter ";
    crossSection =  21380000.0  *  0.05973  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361327  ){
    name = " Sherpa_CT10_Wmunu_Pt70_140_CVetoBVeto ";
    crossSection =  631100.0  *  0.7278  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361328  ){
    name = " Sherpa_CT10_Wmunu_Pt70_140_CFilterBVeto ";
    crossSection =  631100.0  *  0.1760  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361329  ){
    name = " Sherpa_CT10_Wmunu_Pt70_140_BFilter ";
    crossSection =  631100.0  *  0.09637  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361330  ){
    name = " Sherpa_CT10_Wmunu_Pt140_280_CVetoBVeto ";
    crossSection =  90070.0  *  0.6832  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361331  ){
    name = " Sherpa_CT10_Wmunu_Pt140_280_CFilterBVeto ";
    crossSection =  90070.0  *  0.2048  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361332  ){
    name = " Sherpa_CT10_Wmunu_Pt140_280_BFilter ";
    crossSection =  90070.0  *  0.1126  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361333  ){
    name = " Sherpa_CT10_Wmunu_Pt280_500_CVetoBVeto ";
    crossSection =  6520.0  *  0.6513  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361334  ){
    name = " Sherpa_CT10_Wmunu_Pt280_500_CFilterBVeto ";
    crossSection =  6520.0  *  0.2210  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361335  ){
    name = " Sherpa_CT10_Wmunu_Pt280_500_BFilter ";
    crossSection =  6520.0  *  0.1314  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361336  ){
    name = " Sherpa_CT10_Wmunu_Pt500_700_CVetoBVeto ";
    crossSection =  415.4  *  0.6306  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361337  ){
    name = " Sherpa_CT10_Wmunu_Pt500_700_CFilterBVeto ";
    crossSection =  415.4  *  0.2380  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361338  ){
    name = " Sherpa_CT10_Wmunu_Pt500_700_BFilter ";
    crossSection =  415.4  *  0.1594  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361339  ){
    name = " Sherpa_CT10_Wmunu_Pt700_1000_CVetoBVeto ";
    crossSection =  79.31  *  0.6232  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361340  ){
    name = " Sherpa_CT10_Wmunu_Pt700_1000_CFilterBVeto ";
    crossSection =  79.31  *  0.2168  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361341  ){
    name = " Sherpa_CT10_Wmunu_Pt700_1000_BFilter ";
    crossSection =  79.31  *  0.1615  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361342  ){
    name = " Sherpa_CT10_Wmunu_Pt1000_2000_CVetoBVeto ";
    crossSection =  10.3  *  0.6114  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361343  ){
    name = " Sherpa_CT10_Wmunu_Pt1000_2000_CFilterBVeto ";
    crossSection =  10.3  *  0.2375  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361344  ){
    name = " Sherpa_CT10_Wmunu_Pt1000_2000_BFilter ";
    crossSection =  10.3  *  0.1696  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361345  ){
    name = " Sherpa_CT10_Wmunu_Pt2000_E_CMS_CVetoBVeto ";
    crossSection =  0.0428  *  0.6006  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361346  ){
    name = " Sherpa_CT10_Wmunu_Pt2000_E_CMS_CFilterBVeto ";
    crossSection =  0.0428  *  0.2610  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361347  ){
    name = " Sherpa_CT10_Wmunu_Pt2000_E_CMS_BFilter ";
    crossSection =  0.0428  *  0.1847  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361348  ){
    name = " Sherpa_CT10_Wtaunu_Pt0_70_CVetoBVeto.evgen.EVNT.e3733/ ";
    crossSection =  21380000.0  *  0.8915  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361349  ){
    name = " Sherpa_CT10_Wtaunu_Pt0_70_CFilterBVeto.evgen.EVNT.e3733/ ";
    crossSection =  21380000.0  *  0.04846  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361350  ){
    name = " Sherpa_CT10_Wtaunu_Pt0_70_BFilter.evgen.EVNT.e3733/ ";
    crossSection =  21380000.0  *  0.05973  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361351  ){
    name = " Sherpa_CT10_Wtaunu_Pt70_140_CVetoBVeto.evgen.EVNT.e3733/ ";
    crossSection =  631100.0  *  0.7278  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361352  ){
    name = " Sherpa_CT10_Wtaunu_Pt70_140_CFilterBVeto.evgen.EVNT.e3733/ ";
    crossSection =  631100.0  *  0.1760  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361353  ){
    name = " Sherpa_CT10_Wtaunu_Pt70_140_BFilter.evgen.EVNT.e3733/ ";
    crossSection =  631100.0  *  0.09637  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361354  ){
    name = " Sherpa_CT10_Wtaunu_Pt140_280_CVetoBVeto.evgen.EVNT.e3733/ ";
    crossSection =  90070.0  *  0.6832  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361355  ){
    name = " Sherpa_CT10_Wtaunu_Pt140_280_CFilterBVeto.evgen.EVNT.e3733/ ";
    crossSection =  90070.0  *  0.2048  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361356  ){
    name = " Sherpa_CT10_Wtaunu_Pt140_280_BFilter.evgen.EVNT.e3733/ ";
    crossSection =  90070.0  *  0.1126  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361357  ){
    name = " Sherpa_CT10_Wtaunu_Pt280_500_CVetoBVeto ";
    crossSection =  6520.0  *  0.6513  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361358  ){
    name = " Sherpa_CT10_Wtaunu_Pt280_500_CFilterBVeto ";
    crossSection =  6520.0  *  0.2210  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361359  ){
    name = " Sherpa_CT10_Wtaunu_Pt280_500_BFilter ";
    crossSection =  6520.0  *  0.1314  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361360  ){
    name = " Sherpa_CT10_Wtaunu_Pt500_700_CVetoBVeto ";
    crossSection =  415.4  *  0.6306  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361361  ){
    name = " Sherpa_CT10_Wtaunu_Pt500_700_CFilterBVeto ";
    crossSection =  415.4  *  0.2380  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361362  ){
    name = " Sherpa_CT10_Wtaunu_Pt500_700_BFilter ";
    crossSection =  415.4  *  0.1594  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361363  ){
    name = " Sherpa_CT10_Wtaunu_Pt700_1000_CVetoBVeto.evgen.EVNT.e3973/ ";
    crossSection =  79.31  *  0.6232  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361364  ){
    name = " Sherpa_CT10_Wtaunu_Pt700_1000_CFilterBVeto.evgen.EVNT.e3973/ ";
    crossSection =  79.31  *  0.2168  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361365  ){
    name = " Sherpa_CT10_Wtaunu_Pt700_1000_BFilter.evgen.EVNT.e3973/ ";
    crossSection =  79.31  *  0.1615  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361366  ){
    name = " Sherpa_CT10_Wtaunu_Pt1000_2000_CVetoBVeto ";
    crossSection =  10.3  *  0.6114  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361367  ){
    name = " Sherpa_CT10_Wtaunu_Pt1000_2000_CFilterBVeto ";
    crossSection =  10.3  *  0.2375  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361368  ){
    name = " Sherpa_CT10_Wtaunu_Pt1000_2000_BFilter ";
    crossSection =  10.3  *  0.1696  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361369  ){
    name = " Sherpa_CT10_Wtaunu_Pt2000_E_CMS_CVetoBVeto ";
    crossSection =  0.0428  *  0.6006  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361370  ){
    name = " Sherpa_CT10_Wtaunu_Pt2000_E_CMS_CFilterBVeto ";
    crossSection =  0.0428  *  0.2610  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361371  ){
    name = " Sherpa_CT10_Wtaunu_Pt2000_E_CMS_BFilter ";
    crossSection =  0.0428  *  0.1847  *  k_Wlnu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361372  ){
    name = " Sherpa_CT10_Zee_Pt0_70_CVetoBVeto ";
    crossSection =  2204000.0  *  0.7785  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361373  ){
    name = " Sherpa_CT10_Zee_Pt0_70_CFilterBVeto ";
    crossSection =  2204000.0  *  0.1422  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361374  ){
    name = " Sherpa_CT10_Zee_Pt0_70_BFilter ";
    crossSection =  2204000.0  *  0.0795  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361375  ){
    name = " Sherpa_CT10_Zee_Pt70_140_CVetoBVeto ";
    crossSection =  76140.0  *  0.6480  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361376  ){
    name = " Sherpa_CT10_Zee_Pt70_140_CFilterBVeto ";
    crossSection =  76140.0  *  0.2198  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361377  ){
    name = " Sherpa_CT10_Zee_Pt70_140_BFilter ";
    crossSection =  76140.0  *  0.1309  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361378  ){
    name = " Sherpa_CT10_Zee_Pt140_280_CVetoBVeto ";
    crossSection =  11630.0  *  0.6139  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361379  ){
    name = " Sherpa_CT10_Zee_Pt140_280_CFilterBVeto ";
    crossSection =  11630.0  *  0.2426  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361380  ){
    name = " Sherpa_CT10_Zee_Pt140_280_BFilter ";
    crossSection =  11630.0  *  0.1468  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361381  ){
    name = " Sherpa_CT10_Zee_Pt280_500_CVetoBVeto ";
    crossSection =  861.5  *  0.5836  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361382  ){
    name = " Sherpa_CT10_Zee_Pt280_500_CFilterBVeto ";
    crossSection =  861.5  *  0.2632  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361383  ){
    name = " Sherpa_CT10_Zee_Pt280_500_BFilter ";
    crossSection =  861.5  *  0.1594  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361384  ){
    name = " Sherpa_CT10_Zee_Pt500_700_CVetoBVeto ";
    crossSection =  55.11  *  0.5692  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361385  ){
    name = " Sherpa_CT10_Zee_Pt500_700_CFilterBVeto ";
    crossSection =  55.11  *  0.2692  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361386  ){
    name = " Sherpa_CT10_Zee_Pt500_700_BFilter ";
    crossSection =  55.11  *  0.1718  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361387  ){
    name = " Sherpa_CT10_Zee_Pt700_1000_CVetoBVeto ";
    crossSection =  10.05  *  0.5625  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361388  ){
    name = " Sherpa_CT10_Zee_Pt700_1000_CFilterBVeto ";
    crossSection =  10.05  *  0.2958  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361389  ){
    name = " Sherpa_CT10_Zee_Pt700_1000_BFilter ";
    crossSection =  10.05  *  0.1806  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361390  ){
    name = " Sherpa_CT10_Zee_Pt1000_2000_CVetoBVeto ";
    crossSection =  1.363  *  0.5499  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361391  ){
    name = " Sherpa_CT10_Zee_Pt1000_2000_CFilterBVeto ";
    crossSection =  1.363  *  0.3135  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361392  ){
    name = " Sherpa_CT10_Zee_Pt1000_2000_BFilter ";
    crossSection =  1.363  *  0.1861  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361393  ){
    name = " Sherpa_CT10_Zee_Pt2000_E_CMS_CVetoBVeto ";
    crossSection =  0.008637  *  0.4874  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361394  ){
    name = " Sherpa_CT10_Zee_Pt2000_E_CMS_CFilterBVeto ";
    crossSection =  0.008637  *  0.3078  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361395  ){
    name = " Sherpa_CT10_Zee_Pt2000_E_CMS_BFilter ";
    crossSection =  0.008637  *  0.2048  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361396  ){
    name = " Sherpa_CT10_Zmumu_Pt0_70_CVetoBVeto/ ";
    crossSection =  2204000.0  *  0.7785  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361397  ){
    name = " Sherpa_CT10_Zmumu_Pt0_70_CFilterBVeto ";
    crossSection =  2204000.0  *  0.1422  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361398  ){
    name = " Sherpa_CT10_Zmumu_Pt0_70_BFilter ";
    crossSection =  2204000.0  *  0.0795  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361399  ){
    name = " Sherpa_CT10_Zmumu_Pt70_140_CVetoBVeto ";
    crossSection =  76140.0  *  0.6480  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361400  ){
    name = " Sherpa_CT10_Zmumu_Pt70_140_CFilterBVeto ";
    crossSection =  76140.0  *  0.2198  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361401  ){
    name = " Sherpa_CT10_Zmumu_Pt70_140_BFilter ";
    crossSection =  76140.0  *  0.1309  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361402  ){
    name = " Sherpa_CT10_Zmumu_Pt140_280_CVetoBVeto ";
    crossSection =  11630.0  *  0.6139  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361403  ){
    name = " Sherpa_CT10_Zmumu_Pt140_280_CFilterBVeto ";
    crossSection =  11630.0  *  0.2426  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361404  ){
    name = " Sherpa_CT10_Zmumu_Pt140_280_BFilter ";
    crossSection =  11630.0  *  0.1468  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361405  ){
    name = " Sherpa_CT10_Zmumu_Pt280_500_CVetoBVeto ";
    crossSection =  861.5  *  0.5836  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361406  ){
    name = " Sherpa_CT10_Zmumu_Pt280_500_CFilterBVeto ";
    crossSection =  861.5  *  0.2632  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361407  ){
    name = " Sherpa_CT10_Zmumu_Pt280_500_BFilter ";
    crossSection =  861.5  *  0.1594  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361408  ){
    name = " Sherpa_CT10_Zmumu_Pt500_700_CVetoBVeto ";
    crossSection =  55.11  *  0.5692  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361409  ){
    name = " Sherpa_CT10_Zmumu_Pt500_700_CFilterBVeto ";
    crossSection =  55.11  *  0.2692  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361410  ){
    name = " Sherpa_CT10_Zmumu_Pt500_700_BFilter ";
    crossSection =  55.11  *  0.1718  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361411  ){
    name = " Sherpa_CT10_Zmumu_Pt700_1000_CVetoBVeto ";
    crossSection =  10.05  *  0.5625  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361412  ){
    name = " Sherpa_CT10_Zmumu_Pt700_1000_CFilterBVeto ";
    crossSection =  10.05  *  0.2958  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361413  ){
    name = " Sherpa_CT10_Zmumu_Pt700_1000_BFilter ";
    crossSection =  10.05  *  0.1806  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361414  ){
    name = " Sherpa_CT10_Zmumu_Pt1000_2000_CVetoBVeto ";
    crossSection =  1.363  *  0.5499  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361415  ){
    name = " Sherpa_CT10_Zmumu_Pt1000_2000_CFilterBVeto ";
    crossSection =  1.363  *  0.3135  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361416  ){
    name = " Sherpa_CT10_Zmumu_Pt1000_2000_BFilter ";
    crossSection =  1.363  *  0.1861  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361417  ){
    name = " Sherpa_CT10_Zmumu_Pt2000_E_CMS_CVetoBVeto ";
    crossSection =  0.008637  *  0.4874  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361418  ){
    name = " Sherpa_CT10_Zmumu_Pt2000_E_CMS_CFilterBVeto ";
    crossSection =  0.008637  *  0.3078  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361419  ){
    name = " Sherpa_CT10_Zmumu_Pt2000_E_CMS_BFilter ";
    crossSection =  0.008637  *  0.2048  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361420  ){
    name = " Sherpa_CT10_Ztautau_Pt0_70_CVetoBVeto ";
    crossSection =  2204000.0  *  0.7785  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361421  ){
    name = " Sherpa_CT10_Ztautau_Pt0_70_CFilterBVeto ";
    crossSection =  2204000.0  *  0.1422  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361422  ){
    name = " Sherpa_CT10_Ztautau_Pt0_70_BFilter ";
    crossSection =  2204000.0  *  0.0795  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361423  ){
    name = " Sherpa_CT10_Ztautau_Pt70_140_CVetoBVeto ";
    crossSection =  76140.0  *  0.6480  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361424  ){
    name = " Sherpa_CT10_Ztautau_Pt70_140_CFilterBVeto ";
    crossSection =  76140.0  *  0.2198  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361425  ){
    name = " Sherpa_CT10_Ztautau_Pt70_140_BFilter ";
    crossSection =  76140.0  *  0.1309  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361426  ){
    name = " Sherpa_CT10_Ztautau_Pt140_280_CVetoBVeto ";
    crossSection =  11630.0  *  0.6139  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361427  ){
    name = " Sherpa_CT10_Ztautau_Pt140_280_CFilterBVeto ";
    crossSection =  11630.0  *  0.2426  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361428  ){
    name = " Sherpa_CT10_Ztautau_Pt140_280_BFilter ";
    crossSection =  11630.0  *  0.1468  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361429  ){
    name = " Sherpa_CT10_Ztautau_Pt280_500_CVetoBVeto ";
    crossSection =  861.5  *  0.5836  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361430  ){
    name = " Sherpa_CT10_Ztautau_Pt280_500_CFilterBVeto ";
    crossSection =  861.5  *  0.5836  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361431  ){
    name = " Sherpa_CT10_Ztautau_Pt280_500_BFilter ";
    crossSection =  861.5  *  0.1594  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361432  ){
    name = " Sherpa_CT10_Ztautau_Pt500_700_CVetoBVeto ";
    crossSection =  55.11  *  0.5692  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361433  ){
    name = " Sherpa_CT10_Ztautau_Pt500_700_CFilterBVeto ";
    crossSection =  55.11  *  0.2692  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361434  ){
    name = " Sherpa_CT10_Ztautau_Pt500_700_BFilter ";
    crossSection =  55.11  *  0.1718  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361435  ){
    name = " Sherpa_CT10_Ztautau_Pt700_1000_CVetoBVeto ";
    crossSection =  10.05  *  0.5625  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361436  ){
    name = " Sherpa_CT10_Ztautau_Pt700_1000_CFilterBVeto ";
    crossSection =  10.05  *  0.2958  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361437  ){
    name = " Sherpa_CT10_Ztautau_Pt700_1000_BFilter ";
    crossSection =  10.05  *  0.1806  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361438  ){
    name = " Sherpa_CT10_Ztautau_Pt1000_2000_CVetoBVeto ";
    crossSection =  1.363  *  0.5499  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361439  ){
    name = " Sherpa_CT10_Ztautau_Pt1000_2000_CFilterBVeto ";
    crossSection =  1.363  *  0.3135  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361440  ){
    name = " Sherpa_CT10_Ztautau_Pt1000_2000_BFilter ";
    crossSection =  1.363  *  0.1861  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361441  ){
    name = " Sherpa_CT10_Ztautau_Pt2000_E_CMS_CVetoBVeto ";
    crossSection =  0.008637  *  0.4874  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361442  ){
    name = " Sherpa_CT10_Ztautau_Pt2000_E_CMS_CFilterBVeto ";
    crossSection =  0.008637  *  0.3078  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361443  ){
    name = " Sherpa_CT10_Ztautau_Pt2000_E_CMS_BFilter ";
    crossSection =  0.008637  *  0.2048  *  k_Zll_sherpa ; // changed from pmg
}
else if (RunNumber ==  361444  ){
    name = " Sherpa_CT10_Znunu_Pt0_70_CVetoBVeto ";
    crossSection =  11940000.0  *  0.7785  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361445  ){
    name = " Sherpa_CT10_Znunu_Pt0_70_CFilterBVeto ";
    crossSection =  11940000.0  *  0.1401  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361446  ){
    name = " Sherpa_CT10_Znunu_Pt0_70_BFilter ";
    crossSection =  11940000.0  *  0.0800  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361447  ){
    name = " Sherpa_CT10_Znunu_Pt70_140_CVetoBVeto ";
    crossSection =  428400.0  *  0.6496  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361448  ){
    name = " Sherpa_CT10_Znunu_Pt70_140_CFilterBVeto ";
    crossSection =  428400.0  *  0.2184  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361449  ){
    name = " Sherpa_CT10_Znunu_Pt70_140_BFilter ";
    crossSection =  428400.0  *  0.1328  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361450  ){
    name = " Sherpa_CT10_Znunu_Pt140_280_CVetoBVeto ";
    crossSection =  65790.0  *  0.6138  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361451  ){
    name = " Sherpa_CT10_Znunu_Pt140_280_CFilterBVeto ";
    crossSection =  65790.0  *  0.2390  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361452  ){
    name = " Sherpa_CT10_Znunu_Pt140_280_BFilter ";
    crossSection =  65790.0  *  0.1477  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361453  ){
    name = " Sherpa_CT10_Znunu_Pt280_500_CVetoBVeto ";
    crossSection =  4847.0  *  0.5857  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361454  ){
    name = " Sherpa_CT10_Znunu_Pt280_500_CFilterBVeto ";
    crossSection =  4847.0  *  0.2606  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361455  ){
    name = " Sherpa_CT10_Znunu_Pt280_500_BFilter ";
    crossSection =  4847.0  *  0.1617  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361456  ){
    name = " Sherpa_CT10_Znunu_Pt500_700_CVetoBVeto ";
    crossSection =  300.6  *  0.5550  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361457  ){
    name = " Sherpa_CT10_Znunu_Pt500_700_CFilterBVeto ";
    crossSection =  300.6  *  0.2749  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361458  ){
    name = " Sherpa_CT10_Znunu_Pt500_700_BFilter ";
    crossSection =  300.6  *  0.1649  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361459  ){
    name = " Sherpa_CT10_Znunu_Pt700_1000_CVetoBVeto ";
    crossSection =  54.93  *  0.5577  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361460  ){
    name = " Sherpa_CT10_Znunu_Pt700_1000_CFilterBVeto ";
    crossSection =  54.93  *  0.3039  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361461  ){
    name = " Sherpa_CT10_Znunu_Pt700_1000_BFilter ";
    crossSection =  54.93  *  0.1631  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361462  ){
    name = " Sherpa_CT10_Znunu_Pt1000_2000_CVetoBVeto ";
    crossSection =  7.663  *  0.5347  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361463  ){
    name = " Sherpa_CT10_Znunu_Pt1000_2000_CFilterBVeto ";
    crossSection =  7.663  *  0.3122  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361464  ){
    name = " Sherpa_CT10_Znunu_Pt1000_2000_BFilter ";
    crossSection =  7.663  *  0.1972  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361465  ){
    name = " Sherpa_CT10_Znunu_Pt2000_E_CMS_CVetoBVeto ";
    crossSection =  0.03402  *  0.5436  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361466  ){
    name = " Sherpa_CT10_Znunu_Pt2000_E_CMS_CFilterBVeto ";
    crossSection =  0.03402  *  0.3456  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber ==  361467  ){
    name = " Sherpa_CT10_Znunu_Pt2000_E_CMS_BFilter ";
    crossSection =  0.03402  *  0.2157  *  k_Znunu_sherpa ; // changed from pmg
}
else if (RunNumber == 361500 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Zee_Np0";
    crossSection = 1401.6e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361501 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Zee_Np1";
    crossSection = 211.99e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361502 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Zee_Np2";
    crossSection = 67.305e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361503 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Zee_Np3";
    crossSection = 18679 * 1 * k_Zll_MG; //  fb 4 November 2016: filter efficiency updated to 1 (was 0.99696) to match PMG twiki 
}
else if (RunNumber == 361504 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Zee_Np4";
    crossSection = 7.291e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361505 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Zmumu_Np0";
    crossSection = 1402.e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361506 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Zmumu_Np1";
    crossSection = 211.95e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361507 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Zmumu_Np2";
    crossSection = 67.353e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361508 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Zmumu_Np3";
    crossSection = 18.633e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361509 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Zmumu_Np4";
    crossSection = 7.3013e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361510 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_Np0";
    crossSection = 1397.8e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361511 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_Np1";
    crossSection = 211.4e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361512 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_Np2";
    crossSection = 67.176e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361513 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_Np3";
    crossSection = 18.609e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361514 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Ztautau_Np4";
    crossSection = 7.2749e3 * 1 * k_Zll_MG; //  fb 
}
else if (RunNumber == 361515 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Znunu_Np0";
    crossSection = 7518.4e3 * 1 * k_Znunu_MG; //  fb 
}
else if (RunNumber == 361516 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Znunu_Np1";
    crossSection = 1200.1e3 * 1 * k_Znunu_MG; //  fb 
}
else if (RunNumber == 361517 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Znunu_Np2";
    crossSection = 387.16e3 * 1 * k_Znunu_MG; //  fb 
}
else if (RunNumber == 361518 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Znunu_Np3";
    crossSection = 110.08e3 * 1 * k_Znunu_MG; //  fb 
}
else if (RunNumber == 361519 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_Znunu_Np4";
    crossSection = 43.389e3 * 1 * k_Znunu_MG; //  fb 
}
else if (RunNumber == 361600){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_WWlvlv";
  crossSection = 10631.0 * 1; // 10631.0 fb
}else if (RunNumber == 361601){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvll_mll4";
  crossSection = 4502.3 * 1; // 4462.5 fb
}
else if (RunNumber == 361602){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvvv_mll4";
  crossSection = 2777.8 * 1; // 2777.8 fb
}
else if (RunNumber == 361603){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4";
  crossSection = 1267.3 * 1; // 1256.8 fb
}
else if (RunNumber == 361604){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZvvll_mll4";
  crossSection = 917.95 * 1; // 924.98 fb
}
else if (RunNumber == 361605){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZvvvv_mll4";
  crossSection = 549.01 * 1; // 549.01 fb
}
else if (RunNumber == 361606){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_WWlvqq";
  crossSection = 44180. * 1; // 44176.0 fb
}
else if (RunNumber == 361607){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_WZqqll_mll20";
  crossSection = 3277.7 * 1; // 3284.9 fb
}
else if (RunNumber ==361609){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvqq_mqq20";
  crossSection = 10086.0 * 1; // 10099.0 fb
}
else if (RunNumber == 361610){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZqqll_mqq20mll20";
  crossSection = 2269.9 * 1; // 2273.9 fb
}
else if (RunNumber == 361611){
  name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZvvqq_mqq20";
  crossSection = 3942.2 * 1; // 3944.8 fb
}
else if (RunNumber == 361625 ){
    name = "Sherpa_CT10_ZZZ_6l0v";
    crossSection = 0.017059 * 1.0 ; // 0.017059 fb
}
else if (RunNumber == 361626 ){
    name = "Sherpa_CT10_ZZZ_4l2v";
    crossSection = 0.44125 * 0.22542 ; // 0.099466575 fb
}
else if (RunNumber == 361621 ){
    name = "Sherpa_CT10_WWZ_4l2v";
    crossSection = 1.734 * 1.0 ; // 1.734 fb
}
else if (RunNumber == 361623 ){
    name = "Sherpa_CT10_WZZ_5l1v";
    crossSection = 0.21783 * 1.0 ; // 0.21783 fb
}

//::: Sherpa 2.2 Samples: XsecSummaryZjetsSherpa22Light, c, and b
else if (RunNumber==363102){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt70_140_CVetoBVeto/";
 crossSection = 71687.0*0.66882*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363103){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt70_140_CFilterBVeto/";
 crossSection = 71653.0*0.20076*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363104){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt70_140_BFilter/";
 crossSection = 71679.0*0.12637*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363105){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt140_280_CVetoBVeto/";
 crossSection = 11031.0*0.62603*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363106){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt140_280_CFilterBVeto/";
 crossSection = 11069.0*0.22357*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363107){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt140_280_BFilter/";
 crossSection = 11078.0*0.14399*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363108){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt280_500_CVetoBVeto/";
 crossSection = 835.15*0.59782*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363109){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt280_500_CFilterBVeto/";
 crossSection = 829.16*0.24345*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363110){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt280_500_BFilter/";
 crossSection = 834.58*0.15277*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363111){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt500_700_CVetoBVeto/";
 crossSection = 53.095*0.58109*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363112){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt500_700_CFilterBVeto/";
 crossSection = 53.205*0.25463*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363113){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt500_700_BFilter/";
 crossSection = 52.708*0.15883*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363114){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt700_1000_CVetoBVeto/";
 crossSection = 9.7332*0.56759*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363115){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt700_1000_CFilterBVeto/";
 crossSection = 9.5498*0.25722*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363116){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt700_1000_BFilter/";
 crossSection = 9.5039*0.15905*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363117){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt1000_2000_CVetoBVeto/";
 crossSection = 1.2574*0.56725*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363118){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt1000_2000_CFilterBVeto/";
 crossSection = 1.2388*0.26301*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363119){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt1000_2000_BFilter/";
 crossSection = 1.2661*0.11731*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363120){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt2000_E_CMS_CVetoBVeto/";
 crossSection = 0.00475*0.52119*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363121){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt2000_E_CMS_CFilterBVeto/";
 crossSection = 0.00454*0.29017*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber == 363122 ){

    name = "Sherpa_NNPDF30NNLO_Ztautau_Pt2000_E_CMS_BFilter";

    crossSection = 0.0045616 * 0.188 ; // -0.0045616 fb - filter eff not in AMI; found here: https://twiki.cern.ch/twiki/bin/view/AtlasProtected/MC15ZjetsSherpa22BSamplesPMG#Sherpa_22_NNPDF30NNLO_Ztauta_AN6 

}
else if (RunNumber == 363123 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht0_70_CVetoBVeto";
    crossSection = 1714500. * 0.83157 * k_ZllHT_MG; //  fb 
}
else if (RunNumber == 363124 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht0_70_CFilterBVeto";
    crossSection = 1715500. * 0.10835 * k_ZllHT_MG; // fb 
}
else if (RunNumber == 363125 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht0_70_BFilter";
    crossSection = 1715700. * 0.059162 * k_ZllHT_MG; // fb 
}
else if (RunNumber == 363126 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht70_140_CVetoBVeto";
    //crossSection = 84539.0 * 0.71802 * k_ZllHT_MG; //  fb 
    crossSection = 84570.00 * 0.71809 * k_ZllHT_MG; // updated 4 November 2016 to match PMG twiki
}
else if (RunNumber == 363127 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht70_140_CFilterBVeto";
    //crossSection = 84511.0 * 0.17357 * k_ZllHT_MG; // fb 
    crossSection = 84588.0 * 0.17404 * k_ZllHT_MG; // fb Updated 4 November 2016 to match PMG Twiki 
}
else if (RunNumber == 363128 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht70_140_BFilter";
    //crossSection = 84807.0 * 0.10768 * k_ZllHT_MG; // fb 
    crossSection = 84752.0 * 0.10804 * k_ZllHT_MG; // fb Updated 4 November 2016 to match PMG Twiki 
}
else if (RunNumber == 363129 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht140_280_CVetoBVeto";
    //crossSection = 35731.0 * 0.67636 * k_ZllHT_MG; //  fb 
    crossSection = 35883.0 * 0.67472 * k_ZllHT_MG; //  fb Updated 4 November 2016 to match PMG Twiki
}
else if (RunNumber == 363130 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht140_280_CFilterBVeto";
    //crossSection = 35907.0 * 0.20006 * k_ZllHT_MG; //  fb 
    crossSection = 35908.0 * 0.19951 * k_ZllHT_MG; //  fb Updated 4 November 2016 to match PMG Twiki
}
else if (RunNumber == 363131 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht140_280_BFilter";
    crossSection = 35798.0 * 0.12654 * k_ZllHT_MG; // 4524.27409 fb 
}
else if (RunNumber == 363132 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht280_500_CVetoBVeto";
    //crossSection = 8173.1 * 0.62684 * k_ZllHT_MG; // 5141.662542 fb 
    crossSection = 8187.1 * 0.62802 * k_ZllHT_MG; // 5141.662542 fb Updated 4 November 2016 to match PMG Twiki
}
else if (RunNumber == 363133 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht280_500_CFilterBVeto";
    //crossSection = 8205.9 * 0.22641 * k_ZllHT_MG; // 1866.7901 fb 
    crossSection = 8180.50 * 0.2282 * k_ZllHT_MG; // 1866.7901 fb Updated 4 November 2016 to match PMG Twiki
}
else if (RunNumber == 363134 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht280_500_BFilter";
    crossSection = 8173.9 * 0.14276 * k_ZllHT_MG; // 1165.358415 fb 
}
else if (RunNumber == 363135 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht500_700_CVetoBVeto";
    //crossSection = 1252.6 * 0.59567 * k_ZllHT_MG; // 759.06662 fb 
    crossSection = 1271.00 * 0.59722 * k_ZllHT_MG; // 759.06662 fb Updated 4 November 2016 to match PMG Twiki 
}
else if (RunNumber == 363136 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht500_700_CFilterBVeto";
    //crossSection = 1262.3 * 0.25547 * k_ZllHT_MG; // 316.191744 fb 
    crossSection = 1267.2 * 0.24952 * k_ZllHT_MG; // 316.191744 fb Updated 4 November 2016 to match PMG Twiki
}
else if (RunNumber == 363137 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht500_700_BFilter";
    crossSection = 1276.0 * 0.15225 * k_ZllHT_MG; // 194.193108 fb 
}
else if (RunNumber == 363138 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht700_1000_CVetoBVeto";
    crossSection = 436.01 * 0.57118 * k_ZllHT_MG; // 249.0401918 fb 
}
else if (RunNumber == 363139 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht700_1000_CFilterBVeto";
    crossSection = 446.23 * 0.25948 * k_ZllHT_MG; // 115.7877604 fb 
}
else if (RunNumber == 363140 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht700_1000_BFilter";
    crossSection = 445.67 * 0.15965 * k_ZllHT_MG; // 71.1512155 fb 
}
else if (RunNumber == 363141 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht1000_2000_CVetoBVeto";
    crossSection = 148.99 * 0.54908 * k_ZllHT_MG; // 81.8074292 fb 
}
else if (RunNumber == 363142 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht1000_2000_CFilterBVeto";
    crossSection = 146.25 * 0.27164 * k_ZllHT_MG; // 39.72735 fb 
}
else if (RunNumber == 363143 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht1000_2000_BFilter";
    crossSection = 147.05 * 0.17299 * k_ZllHT_MG; // 25.4381795 fb 
}
else if (RunNumber == 363144 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht2000_E_CMS_CVetoBVeto";
    crossSection = 5.538 * 0.56337 * k_ZllHT_MG; // 3.11994306 fb 
}
else if (RunNumber == 363145 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht2000_E_CMS_CFilterBVeto";
    crossSection = 5.5466 * 0.29294 * k_ZllHT_MG; // 1.624821004 fb 
}
else if (RunNumber == 363146 ){
    name = "MGPy8EG_N30NLO_Zmumu_Ht2000_E_CMS_BFilter";
    crossSection = 5.6422 * 0.16307 * k_ZllHT_MG; // 0.920073554 fb 
}
else if (RunNumber==363361){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt0_70_CVetoBVeto/";
 crossSection = 2076500.0*0.81186*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363362){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt0_70_CFilterBVeto/";
 crossSection = 2076700.0*0.119*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363363){
 name = "Sherpa_NNPDF30NNLO_Ztautau_Pt0_70_BFilter/";
 crossSection = 2078800.0*0.069319*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363364){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt0_70_CVetoBVeto/";
 crossSection = 2077000.0*0.81102*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363365){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt0_70_CFilterBVeto/";
 crossSection = 2075900.0*0.11858*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363366){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt0_70_BFilter/";
 crossSection = 2077600.0*0.070383*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363367){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt70_140_CVetoBVeto/";
 crossSection = 71720.0*0.6669*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363368){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt70_140_CFilterBVeto/";
 crossSection = 71743.0*0.20026*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363369){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt70_140_BFilter/";
 crossSection = 71574.0*0.12759*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363370){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt140_280_CVetoBVeto/";
 crossSection = 11105.0*0.62584*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363371){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt140_280_CFilterBVeto/";
 crossSection = 11099.0*0.22245*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363372){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt140_280_BFilter/";
 crossSection = 11078.0*0.14423*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363373){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt280_500_CVetoBVeto/";
 crossSection = 833.96*0.59232*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363374){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt280_500_CFilterBVeto/";
 crossSection = 831.55*0.24084*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363375){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt280_500_BFilter/";
 crossSection = 832.16*0.15228*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363376){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt500_700_CVetoBVeto/";
 crossSection = 53.138*0.58356*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363377){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt500_700_CFilterBVeto/";
 crossSection = 52.965*0.25111*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363378){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt500_700_BFilter/";
 crossSection = 53.414*0.14697*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363379){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt700_1000_CVetoBVeto/";
 crossSection = 9.5435*0.57641*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363380){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt700_1000_CFilterBVeto/";
 crossSection = 9.5439*0.25478*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363381){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt700_1000_BFilter/";
 crossSection = 9.5915*0.15988*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363382){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt1000_2000_CVetoBVeto/";
 crossSection = 1.2698*0.55785*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363383){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt1000_2000_CFilterBVeto/";
 crossSection = 1.2528*0.26111*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363384){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt1000_2000_BFilter/";
 crossSection = 1.2306*0.15391*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363385){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt2000_E_CMS_CVetoBVeto/";
 crossSection = 0.00448*0.56059*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363386){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt2000_E_CMS_CFilterBVeto/";
 crossSection = 0.0052*0.27202*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363387){
 name = "Sherpa_NNPDF30NNLO_Zmumu_Pt2000_E_CMS_BFilter/";
 crossSection = 0.00472*0.14554*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363388){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt0_70_CVetoBVeto/";
 crossSection = 2076400.0*0.81072*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363389){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt0_70_CFilterBVeto/";
 crossSection = 2078500.0*0.11914*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363390){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt0_70_BFilter/";
 crossSection = 2074000.0*0.069482*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363391){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt70_140_CVetoBVeto/";
 crossSection = 71681.0*0.66943*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363392){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt70_140_CFilterBVeto/";
 crossSection = 71341.0*0.20196*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363393){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt70_140_BFilter/";
 crossSection = 71744.0*0.12667*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363394){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt140_280_CVetoBVeto/";
 crossSection = 11095.0*0.6276*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363395){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt140_280_CFilterBVeto/";
 crossSection = 11051.0*0.22519*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363396){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt140_280_BFilter/";
 crossSection = 10952.0*0.14604*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363397){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt280_500_CVetoBVeto/";
 crossSection = 834.77*0.59849*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363398){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt280_500_CFilterBVeto/";
 crossSection = 829.1*0.2453*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363399){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt280_500_BFilter/";
 crossSection = 832.51*0.15152*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363400){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt500_700_CVetoBVeto/";
 crossSection = 53.181*0.55451*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363401){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt500_700_CFilterBVeto/";
 crossSection = 52.912*0.25074*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363402){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt500_700_BFilter/";
 crossSection = 52.964*0.1543*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363403){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt700_1000_CVetoBVeto/";
 crossSection = 9.6374*0.57617*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363404){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt700_1000_CFilterBVeto/";
 crossSection = 9.431*0.26107*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363405){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt700_1000_BFilter/";
 crossSection = 9.6257*0.15925*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363406){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt1000_2000_CVetoBVeto/";
 crossSection = 1.2529*0.57115*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363407){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt1000_2000_CFilterBVeto/";
 crossSection = 1.2711*0.26849*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363408){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt1000_2000_BFilter/";
 crossSection = 1.2502*0.15536*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363409){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt2000_E_CMS_CVetoBVeto/";
 crossSection = 0.00492*0.52636*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363410){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt2000_E_CMS_CFilterBVeto/";
 crossSection = 0.00474*0.26346*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363411){
 name = "Sherpa_NNPDF30NNLO_Zee_Pt2000_E_CMS_BFilter/";
 crossSection = 0.0046*0.15562*k_Zll_Sherpa22; // fb 
 }
else if (RunNumber==363412){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt0_70_CVetoBVeto/";
 crossSection = 11220000.0*0.81079*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363413){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt0_70_CFilterBVeto/";
 crossSection = 11230000.0*0.1155*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363414){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt0_70_BFilter/";
 crossSection = 11215000.0*0.071258*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363415){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt70_140_CVetoBVeto/";
 crossSection = 403310.0*0.66795*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363416){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt70_140_CFilterBVeto/";
 crossSection = 403280.0*0.20046*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363417){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt70_140_BFilter/";
 crossSection = 404510.0*0.12454*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363418){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt140_280_CVetoBVeto/";
 crossSection = 62127.0*0.6267*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363419){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt140_280_CFilterBVeto/";
 crossSection = 62100.0*0.24137*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363420){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt140_280_BFilter/";
 crossSection = 62295.0*0.14478*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363421){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt280_500_CVetoBVeto/";
 crossSection = 4631.1*0.59846*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363422){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt280_500_CFilterBVeto/";
 crossSection = 4596.7*0.23872*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363423){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt280_500_BFilter/";
 crossSection = 4617.6*0.15655*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363424){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt500_700_CVetoBVeto/";
 crossSection = 294.95*0.58473*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363425){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt500_700_CFilterBVeto/";
 crossSection = 282.53*0.25609*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363426){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt500_700_BFilter/";
 crossSection = 287.77*0.15848*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363427){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt700_1000_CVetoBVeto/";
 crossSection = 49.185*0.57913*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363428){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt700_1000_CFilterBVeto/";
 crossSection = 50.976*0.26143*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363429){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt700_1000_BFilter/";
 crossSection = 51.549*0.15659*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363430){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt1000_2000_CVetoBVeto/";
 crossSection = 6.6326*0.56159*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363431){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt1000_2000_CFilterBVeto/";
 crossSection = 6.6936*0.26278*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363432){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt1000_2000_BFilter/";
 crossSection = 6.3178*0.16869*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363433){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt2000_E_CMS_CVetoBVeto/";
 crossSection = 0.0222*0.48367*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363434){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt2000_E_CMS_CFilterBVeto/";
 crossSection = 0.0239*0.28446*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber==363435){
 name = "Sherpa_NNPDF30NNLO_Znunu_Pt2000_E_CMS_BFilter/";
 crossSection = 0.0252*0.16939*k_Znunu_Sherpa22; // fb 
 }
else if (RunNumber == 363490 ){
    name = "Sherpa_221_NNPDF30NNLO_llll";
    crossSection = 1255.7 * 1.0 ; // 1255.7 fb 
}
else if (RunNumber == 363491 ){
    name = "Sherpa_221_NNPDF30NNLO_lllv";
    crossSection = 4583.3 * 1.0 ; // 4583.3 fb 
}
else if (RunNumber == 363492 ){
    name = "Sherpa_221_NNPDF30NNLO_llvv";
    crossSection = 12465.0 * 1.0 ; // 12465.0 fb 
}
else if (RunNumber == 363493 ){
    name = "Sherpa_221_NNPDF30NNLO_lvvv";
    crossSection = 3235.4 * 1.0 ; // 3235.4 fb 
}
else if (RunNumber == 363494 ){
    name = "Sherpa_221_NNPDF30NNLO_vvvv";
    crossSection = 600.49 * 1.0 ; // 600.49 fb 
}
else if (RunNumber == 364100 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CVetoBVeto";
    crossSection = 1983000.0 * 0.8221 * k_Zll_Sherpa22; // 1630224.3 fb 
}
else if (RunNumber == 364101 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CFilterBVeto";
    crossSection = 1978400.0 * 0.11308 * k_Zll_Sherpa22; // 223717.472 fb 
}
else if (RunNumber == 364102 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_BFilter";
    crossSection = 1982200.0 * 0.064161 * k_Zll_Sherpa22; // 127179.9342 fb 
}
else if (RunNumber == 364103 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_CVetoBVeto";
    crossSection = 108920.0 * 0.68873 * k_Zll_Sherpa22; // 75016.4716 fb 
}
else if (RunNumber == 364104 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_CFilterBVeto";
    crossSection = 109420.0 * 0.18596 * k_Zll_Sherpa22; // 20347.7432 fb 
}
else if (RunNumber == 364105 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_BFilter";
    crossSection = 108910.0 * 0.11375 * k_Zll_Sherpa22; // 12388.5125 fb 
}
else if (RunNumber == 364106 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CVetoBVeto";
    crossSection = 39878.0 * 0.60899 * k_Zll_Sherpa22; // 24285.30322 fb 
}
else if (RunNumber == 364107 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CFilterBVeto";
    crossSection = 39795.0 * 0.23308 * k_Zll_Sherpa22; // 9275.4186 fb 
}
else if (RunNumber == 364108 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_BFilter";
    crossSection = 39908.0 * 0.14618  * k_Zll_Sherpa22; //  fb 
}
else if (RunNumber == 364109 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_CVetoBVeto";
    crossSection = 8537.5 * 0.55906 * k_Zll_Sherpa22; // 4772.97475 fb 
}
else if (RunNumber == 364110 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_CFilterBVeto";
    crossSection = 8540.3 * 0.26528 * k_Zll_Sherpa22; // 2265.570784 fb 
}
else if (RunNumber == 364111 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_BFilter";
    crossSection = 8493.2 * 0.17559 * k_Zll_Sherpa22; // 1491.320988 fb 
}
else if (RunNumber == 364112 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV500_1000";
    crossSection = 1788.1 * 1.0 * k_Zll_Sherpa22; // 1788.1 fb 
}
else if (RunNumber == 364113 ){
    name = "Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV1000_E_CMS";
    crossSection = 147.69 * 1.0 * k_Zll_Sherpa22; // 147.69 fb 
}
else if (RunNumber == 364114 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_CVetoBVeto";
    crossSection = 1981800.0 * 0.82106 * k_Zll_Sherpa22; // 1627176.708 fb 
}
else if (RunNumber == 364115 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_CFilterBVeto";
    crossSection = 1980800.0 * 0.11295 * k_Zll_Sherpa22; // 223731.36 fb 
}
else if (RunNumber == 364116 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_BFilter";
    crossSection = 1981700.0 * 0.063809 * k_Zll_Sherpa22; // 126450.2953 fb 
}
else if (RunNumber == 364117 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_CVetoBVeto";
    crossSection = 110500.0 * 0.69043 * k_Zll_Sherpa22; // 76292.515 fb 
}
else if (RunNumber == 364118 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_CFilterBVeto";
    crossSection = 110630.0 * 0.18382 * k_Zll_Sherpa22; // 20336.0066 fb 
}
else if (RunNumber == 364119 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_BFilter";
    crossSection = 110310.0 * 0.11443 * k_Zll_Sherpa22; // 12622.7733 fb 
}
else if (RunNumber == 364120 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_CVetoBVeto";
    crossSection = 40731.0 * 0.61452 * k_Zll_Sherpa22; // 25030.01412 fb 
}
else if (RunNumber == 364121 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_CFilterBVeto";
    crossSection = 40670.0 * 0.23044 * k_Zll_Sherpa22; // 9371.9948 fb 
}
else if (RunNumber == 364122 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_BFilter";
    crossSection = 40643.0 * 0.14966 * k_Zll_Sherpa22; // 6082.63138 fb 
}
else if (RunNumber == 364123 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_CVetoBVeto";
    crossSection = 8674.3 * 0.56134 * k_Zll_Sherpa22; // 4869.231562 fb 
}
else if (RunNumber == 364124 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_CFilterBVeto";
    crossSection = 8671.1 * 0.26294 * k_Zll_Sherpa22; // 2279.979034 fb 
}
else if (RunNumber == 364125 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_BFilter";
    crossSection = 8676.6 * 0.17223 * k_Zll_Sherpa22; // 1494.370818 fb 
}
else if (RunNumber == 364126 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV500_1000";
    crossSection = 1808.1 * 1.0 * k_Zll_Sherpa22 ; // 1808.1 fb 
}
else if (RunNumber == 364127 ){
    name = "Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV1000_E_CMS";
    crossSection = 148.57 * 1.0 * k_Zll_Sherpa22; // 148.57 fb 
}
else if (RunNumber == 364128 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_CVetoBVeto";
    crossSection = 1981600.0 * 0.82142 * k_Zll_Sherpa22; // 1627725.872 fb 
}
else if (RunNumber == 364129 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_CFilterBVeto";
    crossSection = 1978800.0 * 0.11314 * k_Zll_Sherpa22; // 223881.432 fb 
}
else if (RunNumber == 364130 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_BFilter";
    crossSection = 1981800.0 * 0.064453 * k_Zll_Sherpa22; // 127732.9554 fb 
}
else if (RunNumber == 364131 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_CVetoBVeto";
    crossSection = 110370.0 * 0.68883 * k_Zll_Sherpa22; // 76026.1671 fb 
}
else if (RunNumber == 364132 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_CFilterBVeto";
    crossSection = 110510.0 * 0.1829 * k_Zll_Sherpa22; // 20212.279 fb 
}
else if (RunNumber == 364133 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_BFilter";
    crossSection = 110870.0 * 0.110886 * k_Zll_Sherpa22 ; // -110870.0 fb -- NO GENERATOR EFF IN AMI; value taken from TWiki https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/XsecSummaryZjetsSherpa221B 
}
else if (RunNumber == 364134 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_CVetoBVeto";
    crossSection = 40781.0 * 0.60821 * k_Zll_Sherpa22; // 24803.41201 fb 
}
else if (RunNumber == 364135 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_CFilterBVeto";
    crossSection = 40740.0 * 0.22897 * k_Zll_Sherpa22; // 9328.2378 fb 
}
else if (RunNumber == 364136 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_BFilter";
    crossSection = 40761.0 * 0.13442 * k_Zll_Sherpa22; // 5479.09362 fb 
}
else if (RunNumber == 364137 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_CVetoBVeto";
    crossSection = 8550.2 * 0.56036 * k_Zll_Sherpa22; // 4791.190072 fb 
}
else if (RunNumber == 364138 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_CFilterBVeto";
    crossSection = 8670.7 * 0.26245 * k_Zll_Sherpa22; // 2275.625215 fb 
}
else if (RunNumber == 364139 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_BFilter";
    crossSection = 8680.4 * 0.17313 * k_Zll_Sherpa22; // 1502.837652 fb 
}
else if (RunNumber == 364140 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV500_1000";
    crossSection = 1809.6 * 1.0 * k_Zll_Sherpa22; // 1809.6 fb 
}
else if (RunNumber == 364141 ){
    name = "Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV1000_E_CMS";
    crossSection = 148.34 * 1.0 * k_Zll_Sherpa22; // 148.34 fb 
}
else if (RunNumber == 364142 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV0_70_CVetoBVeto";
    crossSection = 10700000.0 * 0.8216 * k_Znunu_Sherpa22; // 8791120.0 fb 
}
else if (RunNumber == 364143 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV0_70_CFilterBVeto";
    crossSection = 10702000.0 * 0.11123 * k_Znunu_Sherpa22; // 1190383.46 fb 
}
else if (RunNumber == 364144 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV0_70_BFilter";
    crossSection = 10709000.0 * 0.066175 * k_Znunu_Sherpa22; // 708668.075 fb 
}
else if (RunNumber == 364145 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV70_140_CVetoBVeto";
    crossSection = 603230.0 * 0.68924 * k_Znunu_Sherpa22; // 415770.2452 fb 
}
else if (RunNumber == 364146 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV70_140_CFilterBVeto";
    crossSection = 608150.0 * 0.18243 * k_Znunu_Sherpa22; // 110944.8045 fb 
}
else if (RunNumber == 364147 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV70_140_BFilter";
    crossSection = 603320.0 * 0.11955 * k_Znunu_Sherpa22; // -386245.464 fb -- 4 Nov 2016: corrected filter efficiency based on Twiki https://twiki.cern.ch/twiki/bin/view/AtlasProtected/XsecSummaryZjetsSherpa221
}
else if (RunNumber == 364148 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV140_280_CVetoBVeto";
    crossSection = 222280.0 * 0.60735 * k_Znunu_Sherpa22; // 135001.758 fb 
}
else if (RunNumber == 364149 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV140_280_CFilterBVeto";
    crossSection = 221880.0 * 0.22527 * k_Znunu_Sherpa22; // 49982.9076 fb 
}
else if (RunNumber == 364150 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV140_280_BFilter";
    crossSection = 222470.0 * 0.15185 * k_Znunu_Sherpa22; // 33782.0695 fb 
}
else if (RunNumber == 364151 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV280_500_CVetoBVeto";
    crossSection = 47375.0 * 0.55887 * k_Znunu_Sherpa22; // 26476.46625 fb 
}
else if (RunNumber == 364152 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV280_500_CFilterBVeto";
    crossSection = 47397.0 * 0.26201 * k_Znunu_Sherpa22; // 12418.48797 fb 
}
else if (RunNumber == 364153 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV280_500_BFilter";
    crossSection = 47476.0 * 0.17514 * k_Znunu_Sherpa22; // 8314.94664 fb 
}
else if (RunNumber == 364154 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV500_1000";
    crossSection = 9909.9 * 1.0 * k_Znunu_Sherpa22; // 9909.9 fb 
}
else if (RunNumber == 364155 ){
    name = "Sherpa_221_NNPDF30NNLO_Znunu_MAXHTPTV1000_E_CMS";
    crossSection = 818.09 * 1.0 * k_Znunu_Sherpa22; // 818.09 fb 
}
else if (RunNumber==429056){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CVetoBVeto/";
 crossSection = 1978900.0*0.81885; // fb 
 }
else if (RunNumber==429057){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CFilterBVeto/";
 crossSection = 1983500.0*0.11338; // fb 
 }
else if (RunNumber==429058){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_BFilter/";
 crossSection = 1982600.0*0.064868; // fb 
 }
else if (RunNumber==429059){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_CVetoBVeto/";
 crossSection = 109750.0*0.69186; // fb 
 }
else if (RunNumber==429060){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_CFilterBVeto/";
 crossSection = 108590.0*0.19036; // fb 
 }
else if (RunNumber==429061){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_BFilter/";
 crossSection = 109450.0*0.11331; // fb 
 }
else if (RunNumber==429062){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CVetoBVeto/";
 crossSection = 39668.0*0.6145; // fb 
 }
else if (RunNumber==429063){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CFilterBVeto/";
 crossSection = 39903.0*0.23181; // fb 
 }
else if (RunNumber==429064){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_BFilter/";
 crossSection = 40019.0*0.15093; // fb 
 }
else if (RunNumber==429065){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_CVetoBVeto/";
 crossSection = 8538.4*0.55746; // fb 
 }
else if (RunNumber==429066){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_CFilterBVeto/";
 crossSection = 8533.9*0.26462; // fb 
 }
else if (RunNumber==429067){
 name = "Sherpa_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_BFilter/";
 crossSection = 8551.3*0.17467; // fb 
 }


//

else if (RunNumber == 410000 ){
    name = "PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad";
    //crossSection = 695950 * 0.543 * k_tt  ; //  fb 
    crossSection = 696110 * 0.543 * k_tt  ; //  fb Updated 4 November 2016 to match PMG Twiki 
}
else if (RunNumber == 410001 ){
    name = "PowhegPythiaEvtGen_P2012radHi_ttbar_hdamp345_down_nonallhad";
    crossSection = 783730 * 0.543 * 1.0613; // fb
}
else if (RunNumber == 410002 ){
    name = "PowhegPythiaEvtGen_P2012radLo_ttbar_hdamp172_up_nonallhad";
    crossSection = 611.1 * 0.543 * 1.3611 ; // fb 
}
else if (RunNumber == 410004 ){
    name = "PowhegHerwigppEvtGen_UEEE5_ttbar_hdamp172p5_nonallhad";
    crossSection = 696320.0 * 0.54386 ; // 378700.5952 fb 
}
else if (RunNumber == 410009 ){
    name = "PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_dil";
    //crossSection = 696120.0 * 0.10534 * k_tt; //  fb 
    crossSection = 696110.0 * 0.10534 * k_tt; //  fb Updated 4 November 2016 to match PMG Twiki  
}
else if (RunNumber == 410011 ){
    name = "PowhegPythiaEvtGen_P2012_singletop_tchan_lept_top";
    //crossSection = 43739.0 * 1.0 ; // 43739.0 fb 
    crossSection = 43739.0 * 1.0 * 1.0094 ; // 43739.0 fb Updated 4 November 2016 to match PMG Twiki  
}
else if (RunNumber == 410012 ){
    name = "PowhegPythiaEvtGen_P2012_singletop_tchan_lept_antitop";
    //crossSection = 25778.0 * 1.0 ; // 25778.0 fb 
    crossSection = 25778.0 * 1.0 * 1.0193 ; // 25778.0 fb Updated 4 November 2016 to match PMG Twiki  
}
else if (RunNumber == 410013 ){
    name = "PowhegPythiaEvtGen_P2012_Wt_inclusive_top";
    crossSection = 34009.0 * 1.0 ; // 34009.0 fb 
}
else if (RunNumber == 410014 ){
    name = "PowhegPythiaEvtGen_P2012_Wt_inclusive_antitop";
    crossSection = 33989.0 * 1.0 ; // 33989.0 fb 
}
else if (RunNumber == 410015 ){
    name = "PowhegPythiaEvtGen_P2012_Wt_dilepton_top";
    //crossSection = 3583.5 * 1.0 ; // 3583.5 fb 
    crossSection = 3583.5 * 1.0 * 1.054 ; // 3583.5 fb Updated 4 November 2016 to match PMG Twiki  
}
else if (RunNumber == 410016 ){
    name = "PowhegPythiaEvtGen_P2012_Wt_dilepton_antitop";
    //crossSection = 3581.4 * 1.0 ; // 3581.4 fb 
    crossSection = 3581.4 * 1.0 * 1.054; // 3581.4 fb Updated 4 November 2016 to match PMG Twiki  
}
else if (RunNumber == 410049 ){
    name = "MadGraphPythiaEvtGen_P2012_tZ_4fl_tchan_trilepton";
    crossSection = 9.0636 * 1.0 ; // 9.0636 fb 
}
else if (RunNumber == 410069 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_ttZllonshell_Np0";
    //crossSection = 18.103 * 1.0 * k_ttZ ; // 18.103 fb
    crossSection = 18.103 * 1.0 * 1.2; // Updated 14 November 2016 to match PMG twiki 
}
else if (RunNumber == 410070 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_ttZllonshell_Np1";
    //crossSection = 30.629 * 1.0 * k_ttZ; // 30.629 fb
    crossSection = 30.629 * 1.0 * 1.2; // Updated 14 November 2016 to match PMG twiki
}
// added for tests

else if (RunNumber == 410021 ){
    name = "Sherpa_CT10_ttbar_DiLepton_MEPS_NLO";
    crossSection = 78730. * 1. ; // fb 
}
else if (RunNumber == 410003 ){
    name = "aMcAtNloHerwigppEvtGen_ttbar_nonallhad";
    crossSection = 694860. * 5.4396e-1 ; // fb 
}
else if (RunNumber == 410004 ){
    name = "PowhegHerwigppEvtGen_UEEE5_ttbar_hdamp172p5_nonallhad";
    crossSection = 696320. * 5.4386e-1 ; // fb 
}
else if (RunNumber == 410006 ){
    name = "PowhegPythia8EvtGen_A14_ttbar_hdamp172p5_nonallhad";
    crossSection = 696350. * 5.4386e-1 ; // fb 
}

// MonoHiggs

else if (RunNumber == 410142 ){
    name = "Sherpa_NNPDF30NNLO_ttll_mll5";
    crossSection = 113.09 * 1.0 * 1.09; // 113.09 fb -- 1.09 is the kfactor from https://twiki.cern.ch/twiki/bin/view/AtlasProtected/CrossSectionNLOttV#NEW_Updated_ttW_and_ttZ_k_factor
}
else if (RunNumber == 410144 ){
    name = "Sherpa_NNPDF30NNLO_ttW";
    crossSection = 577.29 * 1 * 1.04 ; // XS and kFactor from https://twiki.cern.ch/twiki/bin/view/AtlasProtected/CrossSectionNLOttV#NEW_Updated_ttW_and_ttZ_k_factor 
}
else if (RunNumber == 410155 ){
    name = "aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW";
    crossSection = 548.3 * 1.0 * 1.10 ; // 548.3 fb -- 1.10 is the kfactor from https://twiki.cern.ch/twiki/bin/view/AtlasProtected/CrossSectionNLOttV#NEW_Updated_ttW_and_ttZ_k_factor
}
else if (RunNumber == 410218 ){
    name = "aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee";
    //crossSection = 36.888 * 1.0 ; // 36.888 fb 
    crossSection = 36.888 * 1.0 * 1.2; // Updated 14 November 2016 to match PMG twiki https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/XsecSummaryTTbarX
}
else if (RunNumber == 410219 ){
    name = "aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu";
 //   crossSection = 36.895 * 1.0 ; // 36.895 fb 
    crossSection = 36.895 * 1.0 * 1.2; // Updated 14 November 2016 to match PMG twiki https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/XsecSummaryTTbarX
}

else if (RunNumber == 341449 ){
        name = "PowhegPythia8EvtGen_CT10_AZNLO_ZH125J_MINLO_eeWWlvlv_VpT";
            crossSection = 6.668 ; // 24.531 fb
}
else if (RunNumber == 341451 ){
        name = "PowhegPythia8EvtGen_CT10_AZNLO_ZH125J_MINLO_mumuWWlvlv_VpT";
            crossSection = 6.668 ; // 24.536 fb
}
else if (RunNumber == 341454 ){
        name = "PowhegPythia8EvtGen_CT10_AZNLO_ZH125J_MINLO_tautauWWlvqq_VpT";
            crossSection = 6.668 ; // 10.77741313 fb
}
else if (RunNumber == 341974 ){
        name = "Pythia8EvtGen_A14NNPDF23LO_ZH125_ZZllvv";
            crossSection = 15.771 * 0.041082 ; // 0.647904222 fb
}
else if (RunNumber == 341744 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zphxx_ZZ4l_mzp10_mx1";
            crossSection = 2381.8 * 0.64992 ; // 1547.979456 fb
}
else if (RunNumber == 341748 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zphxx_ZZ4l_mzp200_mx1";
            crossSection = 2348.1 * 0.69858 ; // 1640.335698 fb
}
else if (RunNumber == 341749 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zphxx_ZZ4l_mzp300_mx1";
            crossSection = 2037.7 * 0.72072 ; // 1468.611144 fb
}
else if (RunNumber == 341752 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zphxx_ZZ4l_mzp2000_mx1";
            crossSection = 8.919 * 0.86926 ; // 7.75292994 fb
}
else if (RunNumber == 341753 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zphxx_ZZ4l_mzp5000_mx1";
            crossSection = 0.013817 * 0.9069 ; // 0.0125306373 fb
}
else if (RunNumber == 341759 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zphxx_ZZ4l_mzp10_mx150";
            crossSection = 0.004774 * 0.78981 ; // 0.00377055294 fb
}
else if (RunNumber == 341760 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zphxx_ZZ4l_mzp200_mx150";
            crossSection = 4.8431 * 0.78504 ; // 3.802027224 fb
}
else if (RunNumber == 341761 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zphxx_ZZ4l_mzp295_mx150";
            crossSection = 155.88 * 0.76686 ; // 119.5381368 fb
}
else if (RunNumber == 341766 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zphxx_ZZ4l_mzp1000_mx1000";
            crossSection = 0.00073722 * 0.88971 ; // 0.0006559120062 fb
}
else if (RunNumber == 341767 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zphxx_ZZ4l_mzp1995_mx1000";
            crossSection = 0.43484 * 0.87111 ; // 0.3787934724 fb
}
else if (RunNumber == 341779 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_shxx_ZZ4l_ms10_mx1";
            crossSection = 3268.9 * 0.83141 ; // 2717.796149 fb
}
else if (RunNumber == 341783 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_shxx_ZZ4l_ms200_mx1";
            crossSection = 2692.0 * 0.8517 ; // 2292.7764 fb
}
else if (RunNumber == 341784 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_shxx_ZZ4l_ms300_mx1";
            crossSection = 7655.1 * 0.79801 ; // 6108.846351 fb
}
else if (RunNumber == 341787 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_shxx_ZZ4l_ms2000_mx1";
            crossSection = 3703.1 * 0.84478 ; // 3128.304818 fb
}
else if (RunNumber == 341788 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_shxx_ZZ4l_ms5000_mx1";
            crossSection = 2892.2 * 0.84591 ; // 2446.540902 fb
}
else if (RunNumber == 341794 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_shxx_ZZ4l_ms10_mx150";
            crossSection = 0.0026184 * 0.84087 ; // 0.002201734008 fb
}
else if (RunNumber == 341795 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_shxx_ZZ4l_ms200_mx150";
            crossSection = 0.0040808 * 0.83242 ; // 0.003396939536 fb
}
else if (RunNumber == 341796 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_shxx_ZZ4l_ms295_mx150";
            crossSection = 0.023102 * 0.82423 ; // 0.01904136146 fb
}
else if (RunNumber == 341801 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_shxx_ZZ4l_ms1000_mx1000";
            crossSection = 9.821e-08 * 0.88865 ; // 8.72743165e-08 fb
}
else if (RunNumber == 341802 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_shxx_ZZ4l_ms1995_mx1000";
            crossSection = 6.9372e-06 * 0.90246 ; // 6.260545512e-06 fb
}
else if (RunNumber == 341814 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp600_mA300";
            crossSection = 0.18926 * 0.89046 ; // 0.1685284596 fb
}
else if (RunNumber == 341815 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp800_mA300";
            crossSection = 0.18926 * 0.88782 ; // 0.1680288132 fb
}
else if (RunNumber == 341818 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp1400_mA300";
            crossSection = 0.18926 * 0.88985 ; // 0.168413011 fb
}
else if (RunNumber == 341819 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp600_mA400";
            crossSection = 0.2269 * 0.88246 ; // 0.200230174 fb
}
else if (RunNumber == 341820 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp800_mA400";
            crossSection = 0.2269 * 0.88366 ; // 0.200502454 fb
}
else if (RunNumber == 341823 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp1400_mA400";
            crossSection = 0.2269 * 0.8825 ; // 0.20023925 fb
}
else if (RunNumber == 341824 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp800_mA500";
            crossSection = 0.20763 * 0.8752 ; // 0.181717776 fb
}
else if (RunNumber == 341827 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp1400_mA500";
            crossSection = 0.20763 * 0.87448 ; // 0.1815682824 fb
}
else if (RunNumber == 341828 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp800_mA600";
            crossSection = 0.15048 * 0.86457 ; // 0.1301004936 fb
}
else if (RunNumber == 341831 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp1400_mA600";
            crossSection = 0.15048 * 0.86501 ; // 0.1301667048 fb
}
else if (RunNumber == 341834 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp1400_mA700";
            crossSection = 0.079516 * 0.84907 ; // 0.06751465012 fb
}
else if (RunNumber == 341837 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_zp2hdm_ZZ4l_mzp1400_mA800";
            crossSection = 0.021232 * 0.83079 ; // 0.01763933328 fb
}
else if (RunNumber == 341935 ){
        name = "PowhegPythia8EvtGen_CT10_AZNLO_ZllH125J_MINLO_VpT";
            crossSection = 2.073 * 0.44128 ; // 11.17806368 fb
}
// qq2ZZ
else if (RunNumber == 343232 ){
    name = "PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_500_13000";
    crossSection = 1265.5 * 0.0036815 ; // 4.65893825 fb
}

// ZZd 
else if (RunNumber == 343234 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_HAHMggfZZd4l_mZd15";
    crossSection = 3.081e-07 * 1.0 ; // 3.081e-07 fb 
}
else if (RunNumber == 343235 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_HAHMggfZZd4l_mZd20";
    crossSection = 5.7627e-07 * 1.0 ; // 5.7627e-07 fb 
}
else if (RunNumber == 343236 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_HAHMggfZZd4l_mZd25";
    crossSection = 9.0183e-07 * 1.0 ; // 9.0183e-07 fb 
}
else if (RunNumber == 343237 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_HAHMggfZZd4l_mZd30";
    crossSection = 1.0863e-06 * 1.0 ; // 1.0863e-06 fb 
}
else if (RunNumber == 343238 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_HAHMggfZZd4l_mZd35";
    crossSection = 4.0872e-07 * 1.0 ; // 4.0872e-07 fb 
}
else if (RunNumber == 343239 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_HAHMggfZZd4l_mZd40";
    crossSection = 2.1457e-07 * 1.0 ; // 2.1457e-07 fb 
}
else if (RunNumber == 343240 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_HAHMggfZZd4l_mZd45";
    crossSection = 1.6602e-07 * 1.0 ; // 1.6602e-07 fb 
}
else if (RunNumber == 343241 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_HAHMggfZZd4l_mZd50";
    crossSection = 1.3315e-07 * 1.0 ; // 1.3315e-07 fb 
}
else if (RunNumber == 343242 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_HAHMggfZZd4l_mZd55";
    crossSection = 1.0107e-07 * 1.0 ; // 1.0107e-07 fb 
}


// EFT Madgraph files
else if (RunNumber == 343247 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0p";
            //crossSection = 0.54996 * 1.0 * k_madGraphVBF; // 0.54996 fb
            crossSection = 0.54996 * 1.0 ; // 0.54996 fb
}
else if (RunNumber == 343248 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0phkHdz10";
            crossSection = 45.83 * 1.0  * k_madGraphVBF; // 45.83 fb
}
else if (RunNumber == 343249 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0phkHv10";
            //crossSection = 0.82807 * 1.0 * k_madGraphVBF ; // 0.82807 fb
            crossSection = 0.82807 * 1.0  ; // 0.82807 fb
}
else if (RunNumber == 343250 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHv5kAv10";
            crossSection = 2.1514 * 1.0 * k_madGraphVBF ; // 2.1514 fb
}
else if (RunNumber == 343251 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHvm10kAv10";
            crossSection = 1.7782 * 1.0 * k_madGraphVBF ; // 1.7782 fb
}
else if (RunNumber == 343252 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0mkAv15";
            //crossSection = 1.1961 * 1.0 * k_madGraphVBF ; // 1.1961 fb
            crossSection = 1.1961 * 1.0  ; // 1.1961 fb
}
else if (RunNumber == 343253 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkAv5";
            //crossSection = 0.42213 * 1.0 * k_madGraphVBF ; // 0.42213 fb
            crossSection = 0.42213 * 1.0  ; // 0.42213 fb
}
else if (RunNumber == 343254 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkAv2p5";
            //crossSection = 0.20794 * 1.0 * k_madGraphVBF ; // 0.20794 fb
            crossSection = 0.20794 * 1.0  ; // 0.20794 fb
}
else if (RunNumber == 343255 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkAvm5";
            //crossSection = 0.42339 * 1.0 * k_madGraphVBF ; // 0.42339 fb
            crossSection = 0.42339 * 1.0  ; // 0.42339 fb
}
else if (RunNumber == 343256 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkAvm2p5";
            crossSection = 0.20793 * 1.0 * k_madGraphVBF ; // 0.20793 fb
}
else if (RunNumber == 343257 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHdz5";
            crossSection = 22.157 * 1.0 * k_madGraphVBF ; // 22.157 fb
}
else if (RunNumber == 343258 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHdzm10";
            crossSection = 2.7515 * 1.0 * k_madGraphVBF ; // 2.7515 fb
}
else if (RunNumber == 343259 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHv5";
            //crossSection = 2.3102 * 1.0 * k_madGraphVBF ; // 2.3102 fb
            crossSection = 2.3102 * 1.0  ; // 2.3102 fb
}
else if (RunNumber == 343260 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHv2p5";
            //crossSection = 0.85455 * 1.0 * k_madGraphVBF ; // 0.85455 fb
            crossSection = 0.85455 * 1.0  ; // 0.85455 fb
}
else if (RunNumber == 343261 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHvm5";
            //crossSection = 1.8872 * 1.0 * k_madGraphVBF ; // 1.8872 fb
            crossSection = 1.8872 * 1.0  ; // 1.8872 fb
}
else if (RunNumber == 343262 ){
        name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHvm2p5";
            crossSection = 0.99943 * 1.0 * k_madGraphVBF ; // 0.99943 fb
}
else if (RunNumber == 341975 ){
    name = "Pythia8EvtGen_A14NNPDF23LO_ZllH125_ZZ4l";
    crossSection = 0.01109 * 1.0 ; // fb from LHCHXS 
}
else if (RunNumber == 341561 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_ZH125J_MINLO_ll_ZZinv";
    crossSection = 29.82  ; // fb from LHCHXS for ZH, Z->ll, H incl since RB->inv assumed 100% 
}
// Adding based on Artem Basalaev's list on 25 October 2016
else if (RunNumber == 303511 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM10";
    crossSection = 11550.00 * 0.11699 * 1 ; // 1 fb 
}
else if (RunNumber == 361620 ){
    name = "Sherpa_CT10_WWW_3l3v";
    crossSection = 8.343 * 1.0 * 1.0 ; // 8.343 fb 
}
else if (RunNumber == 361622 ){
    name = "Sherpa_CT10_WWZ_2l4v";
    crossSection = 3.4299 * 1.0 * 1.0 ; // 3.4299 fb 
}
else if (RunNumber == 361624 ){
    name = "Sherpa_CT10_WZZ_3l3v";
    crossSection = 1.9248 * 0.44444 * 1.0; // 0.855458112 fb 
}
else if (RunNumber == 361627 ){
    name = "Sherpa_CT10_ZZZ_2l4v";
    crossSection = 0.4453 * 0.44815 * 1.0 ; // 0.199561195 fb 
}
else if (RunNumber == 363147 ){
    name = "MGPy8EG_N30NLO_Zee_Ht0_70_CVetoBVeto";
    crossSection = 1719700.0 * 0.83292 * k_ZllHT_MG ; // 1432372.524 fb Updated 4 November 2016 to add KFactor 
}
else if (RunNumber == 363148 ){
    name = "MGPy8EG_N30NLO_Zee_Ht0_70_CFilterBVeto";
    crossSection = 1719400.0 * 0.10775 * k_ZllHT_MG; // 185265.35 fb 
}
else if (RunNumber == 363149 ){
    name = "MGPy8EG_N30NLO_Zee_Ht0_70_BFilter";
    crossSection = 1719400.0 * 0.059156 * k_ZllHT_MG; // 101712.8264 fb 
}
else if (RunNumber == 363150 ){
    name = "MGPy8EG_N30NLO_Zee_Ht70_140_CVetoBVeto";
    crossSection = 85105.0 * 0.71754 * k_ZllHT_MG; // 61066.2417 fb 
}
else if (RunNumber == 363151 ){
    name = "MGPy8EG_N30NLO_Zee_Ht70_140_CFilterBVeto";
    crossSection = 85041.0 * 0.17377 * k_ZllHT_MG; // 14777.57457 fb 
}
else if (RunNumber == 363152 ){
    name = "MGPy8EG_N30NLO_Zee_Ht70_140_BFilter";
    crossSection = 85175.0 * 0.10763 * k_ZllHT_MG; // 9167.38525 fb 
}
else if (RunNumber == 363153 ){
    name = "MGPy8EG_N30NLO_Zee_Ht140_280_CVetoBVeto";
    crossSection = 36005.0 * 0.67279 * k_ZllHT_MG; // 24223.80395 fb 
}
else if (RunNumber == 363154 ){
    name = "MGPy8EG_N30NLO_Zee_Ht140_280_CFilterBVeto";
    crossSection = 36028.0 * 0.19996 * k_ZllHT_MG; // 7204.15888 fb 
}
else if (RunNumber == 363155 ){
    name = "MGPy8EG_N30NLO_Zee_Ht140_280_BFilter";
    crossSection = 36060.0 * 0.12486 * k_ZllHT_MG; // 4502.4516 fb 
}
else if (RunNumber == 363156 ){
    name = "MGPy8EG_N30NLO_Zee_Ht280_500_CVetoBVeto";
    crossSection = 8205.4 * 0.62846 * k_ZllHT_MG; // 5156.765684 fb 
}
else if (RunNumber == 363157 ){
    name = "MGPy8EG_N30NLO_Zee_Ht280_500_CFilterBVeto";
    crossSection = 8212.6 * 0.22726 * k_ZllHT_MG; // 1866.395476 fb 
}
else if (RunNumber == 363158 ){
    name = "MGPy8EG_N30NLO_Zee_Ht280_500_BFilter";
    crossSection = 8247.4 * 0.14193 * k_ZllHT_MG; // 1170.553482 fb 
}
else if (RunNumber == 363159 ){
    name = "MGPy8EG_N30NLO_Zee_Ht500_700_CVetoBVeto";
    crossSection = 1273.3 * 0.5966 * k_ZllHT_MG; // 759.65078 fb 
}
else if (RunNumber == 363160 ){
    name = "MGPy8EG_N30NLO_Zee_Ht500_700_CFilterBVeto";
    crossSection = 1273.0 * 0.24847 * k_ZllHT_MG; // 316.30231 fb 
}
else if (RunNumber == 363161 ){
    name = "MGPy8EG_N30NLO_Zee_Ht500_700_BFilter";
    crossSection = 1272.2 * 0.15256 * k_ZllHT_MG; // 194.086832 fb 
}
else if (RunNumber == 363162 ){
    name = "MGPy8EG_N30NLO_Zee_Ht700_1000_CVetoBVeto";
    crossSection = 445.46 * 0.57676 * k_ZllHT_MG; // 256.9235096 fb 
}
else if (RunNumber == 363163 ){
    name = "MGPy8EG_N30NLO_Zee_Ht700_1000_CFilterBVeto";
    crossSection = 446.11 * 0.26137 * k_ZllHT_MG; // 116.5997707 fb 
}
else if (RunNumber == 363164 ){
    name = "MGPy8EG_N30NLO_Zee_Ht700_1000_BFilter";
    crossSection = 446.03 * 0.16181 * k_ZllHT_MG; // 72.1721143 fb 
}
else if (RunNumber == 363165 ){
    name = "MGPy8EG_N30NLO_Zee_Ht1000_2000_CVetoBVeto";
    crossSection = 152.08 * 0.55543 * k_ZllHT_MG; // 84.4697944 fb 
}
else if (RunNumber == 363166 ){
    name = "MGPy8EG_N30NLO_Zee_Ht1000_2000_CFilterBVeto";
    crossSection = 152.48 * 0.27476 * k_ZllHT_MG; // 41.8954048 fb 
}
else if (RunNumber == 363167 ){
    name = "MGPy8EG_N30NLO_Zee_Ht1000_2000_BFilter";
    crossSection = 153.27 * 0.16618 * k_ZllHT_MG; // 25.4704086 fb 
}
else if (RunNumber == 363168 ){
    name = "MGPy8EG_N30NLO_Zee_Ht2000_E_CMS_CVetoBVeto";
    crossSection = 5.6989 * 0.53136 * k_ZllHT_MG; // 3.028167504 fb 
}
else if (RunNumber == 363169 ){
    name = "MGPy8EG_N30NLO_Zee_Ht2000_E_CMS_CFilterBVeto";
    crossSection = 5.7408 * 0.2923 * k_ZllHT_MG; // 1.67803584 fb 
}
else if (RunNumber == 363170 ){
    name = "MGPy8EG_N30NLO_Zee_Ht2000_E_CMS_BFilter";
    crossSection = 5.7164 * 0.17489 * k_ZllHT_MG; // 0.999741196 fb 
}
else if (RunNumber == 410025 ){
    name = "PowhegPythiaEvtGen_P2012_SingleTopSchan_noAllHad_top";
    crossSection = 2051.7 * 1.0 * 1.0046 ; // 2051.7 fb 
}
else if (RunNumber == 410026 ){
    name = "PowhegPythiaEvtGen_P2012_SingleTopSchan_noAllHad_antitop";
    crossSection = 1261.5 * 1.0 * 1.0215; // 1261.5 fb 
}
else if (RunNumber == 410066 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np0";
    //crossSection = 181.99 * 1.0 ; // 181.99 fb AMI
    crossSection = 176.56 * 1.0 * 1.32 ; // 181.99 fb 
}
else if (RunNumber == 410067 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np1";
    crossSection = 140.62 * 1.0 * 1.32 ; // 140.62 fb 
}
else if (RunNumber == 410068 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np2";
    crossSection = 136.8 * 1.0 * 1.32 ; // 136.8 fb 
}
else if (RunNumber == 410081 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23_ttbarWW";
    crossSection = 8.0975 * 1.0 * 1.2231; // 8.0975 fb 
}

//EFT samples, added 23 February 2017
else if (RunNumber == 345049 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l0pphmkHv10kAvm10";
    crossSection = 4.7149 * 1.0 ; // 4.7149 fb 
}
else if (RunNumber == 345050 ){
    name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHv5kAv10";
    crossSection = 0.6046 * 1.0 ; // 0.6046 fb 
}
else if (RunNumber == 345051 ){
    name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHvm10kAv10";
    crossSection = 0.62264 * 1.0 ; // 0.62264 fb 
}
else if (RunNumber == 345052 ){
    name = "MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHv10kAvm10";
    crossSection = 1.4005 * 1.0 ; // 1.4005 fb 
}

// MCFM offshell samples
else if (RunNumber == 345130 ){
    name = "MCFMPy8EG_A14_NNPDF23LO_BKG_ggZZbx_4mu_m4l700plus";
    crossSection = 0.0097966 * 1.0 ; // 0.0097966 fb 
}
else if (RunNumber == 345131 ){
    name = "MCFMPy8EG_A14_NNPDF23LO_BKG_ggZZbx_4e_m4l700plus";
    crossSection = 0.0097954 * 1.0 ; // 0.0097954 fb 
}
else if (RunNumber == 345132 ){
    name = "MCFMPy8EG_A14_NNPDF23LO_BKG_ggZZbx_2e2mu_m4l700plus";
    crossSection = 0.019585 * 1.0 ; // 0.019585 fb 
}
// MCFM samples for High mass SBI
else if (RunNumber == 345133 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_200_w15_4mu";
            crossSection = 3.9898 * 1.0 ; // 3.9898 fb 
}
else if (RunNumber == 345134 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_200_w15_4e";
            crossSection = 3.9914 * 1.0 ; // 3.9914 fb 
}
else if (RunNumber == 345135 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_200_w15_2e2mu";
            crossSection = 8.0031 * 1.0 ; // 8.0031 fb 
}
else if (RunNumber == 345136 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_300_w15_4mu";
            crossSection = 2.6194 * 1.0 ; // 2.6194 fb 
}
else if (RunNumber == 345137 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_300_w15_4e";
            crossSection = 2.6204 * 1.0 ; // 2.6204 fb 
}
else if (RunNumber == 345138 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_300_w15_2e2mu";
            crossSection = 5.2521 * 1.0 ; // 5.2521 fb 
}
else if (RunNumber == 345139 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_400_w15_4mu";
            crossSection = 2.0749 * 1.0 ; // 2.0749 fb 
}
else if (RunNumber == 345140 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_400_w15_4e";
            crossSection = 2.075 * 1.0 ; // 2.075 fb 
}
else if (RunNumber == 345141 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_400_w15_2e2mu";
            crossSection = 4.1608 * 1.0 ; // 4.1608 fb 
}
else if (RunNumber == 345142 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_500_w15_4mu";
            crossSection = 0.54761 * 1.0 ; // 0.54761 fb 
}
else if (RunNumber == 345143 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_500_w15_4e";
            crossSection = 0.54777 * 1.0 ; // 0.54777 fb 
}
else if (RunNumber == 345144 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_500_w15_2e2mu";
            crossSection = 1.0958 * 1.0 ; // 1.0958 fb 
}
else if (RunNumber == 345145 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_600_w15_4mu";
            crossSection = 0.2771 * 1.0 ; // 0.2771 fb 
}
else if (RunNumber == 345146 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_600_w15_4e";
            crossSection = 0.27709 * 1.0 ; // 0.27709 fb 
}
else if (RunNumber == 345147 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_600_w15_2e2mu";
            crossSection = 0.55441 * 1.0 ; // 0.55441 fb 
}
else if (RunNumber == 345148 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_800_w15_4mu";
            crossSection = 0.080065 * 1.0 ; // 0.080065 fb 
}
else if (RunNumber == 345149 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_800_w15_4e";
            crossSection = 0.080043 * 1.0 ; // 0.080043 fb 
}
else if (RunNumber == 345150 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_800_w15_2e2mu";
            crossSection = 0.16015 * 1.0 ; // 0.16015 fb 
}
else if (RunNumber == 345151 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_1000_w15_4mu";
            crossSection = 0.026971 * 1.0 ; // 0.026971 fb 
}
else if (RunNumber == 345152 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_1000_w15_4e";
            crossSection = 0.026966 * 1.0 ; // 0.026966 fb 
}
else if (RunNumber == 345153 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_1000_w15_2e2mu";
            crossSection = 0.053946 * 1.0 ; // 0.053946 fb 
}
else if (RunNumber == 345154 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_1200_w15_4mu";
            crossSection = 0.014853 * 1.0 ; // 0.014853 fb 
}
else if (RunNumber == 345155 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_1200_w15_4e";
            crossSection = 0.014858 * 1.0 ; // 0.014858 fb 
}
else if (RunNumber == 345156 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_1200_w15_2e2mu";
            crossSection = 0.029703 * 1.0 ; // 0.029703 fb 
}
else if (RunNumber == 345157 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_1400_w15_4mu";
            crossSection = 0.0085123 * 1.0 ; // 0.0085123 fb 
}
else if (RunNumber == 345158 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_1400_w15_4e";
            crossSection = 0.0085128 * 1.0 ; // 0.0085128 fb 
}
else if (RunNumber == 345159 ){
        name = "MCFMPy8EG_A14_NNPDF23LO_SBI_ggZZ4l_1400_w15_2e2mu";
            crossSection = 0.017026 * 1.0 ; // 0.017026 fb 
}

/////////////////////////////////////////////
// bbH samples
// there are two samples per mass point
// yb2 -> 'actual' bbH 
// ybyt -> interference term between bbH and ggH, this XS is always negative
// the sample was generated with just bbH process and H decays in PS
// so the ami XS is just the prodution XS. This number is scaled such that the total XS matches the YR4
// Secondly, the numbers here just contain the XS, for proper normalization, multiple with BR
/////////////////////////////////////////////
else if (RunNumber == 344967 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH120_yb2_ZZ4lep_noTau";
    crossSection = 479.9 * 553.4/(479.9 -39.069);
}
else if (RunNumber == 344968 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH120_ybyt_ZZ4lep_noTau";
    crossSection = -39.069 * 553.4/(479.9 -39.069);
}
else if (RunNumber == 344969 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH122_yb2_ZZ4lep_noTau";
    crossSection = 460.12 * 526.8/(460.12 -36.83);
}
else if (RunNumber == 344970 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH122_ybyt_ZZ4lep_noTau";
    crossSection = -36.83 * 526.8/(460.12 -36.83);
}
else if (RunNumber == 344971 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH124_yb2_ZZ4lep_noTau";
    crossSection = 436.71 * 499.9/(436.71 -34.169);
}
else if (RunNumber == 344972 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH124_ybyt_ZZ4lep_noTau";
    crossSection = -34.169 * 499.9/(436.71 -34.169);
}
else if (RunNumber == 344973 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_yb2_ZZ4lep_noTau";
    crossSection = 424.09 * 488/(424.09 -33.064);
}
else if (RunNumber == 344974 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_ybyt_ZZ4lep_noTau";
    crossSection = -33.064 * 488/(424.09 -33.064);
}
else if (RunNumber == 344975 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH126_yb2_ZZ4lep_noTau";
    crossSection = 414.32 * 476/(414.32 -32.54);
}
else if (RunNumber == 344976 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH126_ybyt_ZZ4lep_noTau";
    crossSection = -32.54 * 476/(414.32 -32.54);
}
else if (RunNumber == 344977 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH128_yb2_ZZ4lep_noTau";
    crossSection = 393.37 * 451.3/(393.37 -30.408);
}
else if (RunNumber == 344978 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH128_ybyt_ZZ4lep_noTau";
    crossSection = -30.408 * 451.3/(393.37 -30.408);
}
else if (RunNumber == 344979 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH130_yb2_ZZ4lep_noTau";
    crossSection = 377.56 * 430.4/(377.56 -28.388);
}
else if (RunNumber == 344980 ){
    name = "aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH130_ybyt_ZZ4lep_noTau";
    crossSection = -28.388 * 430.4/(377.56 -28.388);
}

//4l graviton samples, VBF, axial mono-Z, gg2VV llvv SBI 

else if (RunNumber == 303327 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llll_c10_m0600";
    crossSection = 7.875 * 1.0 ; // 7.875 fb 
}
else if (RunNumber == 303328 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llll_c10_m0800";
    crossSection = 1.484 * 1.0 ; // 1.484 fb 
}
else if (RunNumber == 303329 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llll_c10_m1000";
    crossSection = 0.4122 * 1.0 ; // 0.4122 fb 
}
else if (RunNumber == 303329 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llll_c10_m1000";
    crossSection = 0.4122 * 1.0 ; // 0.4122 fb 
}
else if (RunNumber == 303330 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llll_c10_m1200";
    crossSection = 0.1424 * 1.0 ; // 0.1424 fb 
}
else if (RunNumber == 303331 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llll_c10_m1400";
    crossSection = 0.05643 * 1.0 ; // 0.05643 fb 
}
else if (RunNumber == 303332 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llll_c10_m1600";
    crossSection = 0.02465 * 1.0 ; // 0.02465 fb 
}
else if (RunNumber == 303333 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llll_c10_m1800";
    crossSection = 0.01156 * 1.0 ; // 0.01156 fb 
}
else if (RunNumber == 303334 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llll_c10_m2000";
    crossSection = 0.005721 * 1.0 ; // 0.005721 fb 
}
else if (RunNumber == 303334 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF23LO_RS_G_ZZ_llll_c10_m2000";
    crossSection = 0.005721 * 1.0 ; // 0.005721 fb 
}
else if (RunNumber == 307190 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM5_MM1";
    crossSection = 3146.9 * 0.67229 ; // 2115.629401 fb 
}
else if (RunNumber == 303512 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM100";
    crossSection = 468.2 * 0.65181 ; // 305.177442 fb 
}
else if (RunNumber == 303513 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM300";
    crossSection = 63.965 * 0.82645 ; // 52.86387425 fb 
}
else if (RunNumber == 303514 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM2000";
    crossSection = 0.1636 * 0.93449 ; // 0.152882564 fb 
}
else if (RunNumber == 303515 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM10_MM10";
    crossSection = 120.5 * 0.36811 ; // 44.357255 fb 
}
else if (RunNumber == 303516 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM10_MM100";
    crossSection = 469.95 * 0.65394 ; // 307.319103 fb 
}
else if (RunNumber == 303517 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM10_MM10000";
    crossSection = 1.929e-05 * 0.91058 ; // 1.75650882e-05 fb 
}
else if (RunNumber == 303518 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM50_MM10";
    crossSection = 7.07 * 0.75443 ; // 5.3338201 fb 
}
else if (RunNumber == 303519 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM50_MM95";
    crossSection = 39.748 * 0.69382 ; // 27.57795736 fb 
}
else if (RunNumber == 303519 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM50_MM95";
    crossSection = 39.748 * 0.69382 ; // 27.57795736 fb 
}
else if (RunNumber == 303520 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM50_MM300";
    crossSection = 63.685 * 0.83043 ; // 52.88593455 fb 
}
else if (RunNumber == 303521 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM150_MM10";
    crossSection = 0.68335 * 0.87055 ; // 0.5948903425 fb 
}
else if (RunNumber == 303522 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM150_MM295";
    crossSection = 9.4495 * 0.83907 ; // 7.928791965 fb 
}
else if (RunNumber == 303523 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM150_MM1000";
    crossSection = 2.4735 * 0.911 ; // 2.2533585 fb 
}
else if (RunNumber == 303524 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM500_MM10";
    crossSection = 0.01657 * 0.92567 ; // 0.0153383519 fb 
}
else if (RunNumber == 303525 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM500_MM995";
    crossSection = 0.52043 * 0.91516 ; // 0.4762767188 fb 
}
else if (RunNumber == 303525 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM500_MM995";
    crossSection = 0.52043 * 0.91516 ; // 0.4762767188 fb 
}
else if (RunNumber == 303526 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM500_MM2000";
    crossSection = 0.15395 * 0.9358 ; // 0.14406641 fb 
}
else if (RunNumber == 303527 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM500_MM10000";
    crossSection = 1.0995e-05 * 0.93941 ; // 1.032881295e-05 fb 
}
else if (RunNumber == 303528 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1000_MM10";
    crossSection = 0.00064485 * 0.94215 ; // 0.0006075454275 fb 
}
else if (RunNumber == 303529 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1000_MM1000";
    crossSection = 0.00094805 * 0.93967 ; // 0.0008908541435 fb 
}
else if (RunNumber == 303530 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1000_MM1995";
    crossSection = 0.03306 * 0.93958 ; // 0.0310625148 fb 
}
else if (RunNumber == 303551 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM50_MM95";
    crossSection = 9.185 * 0.74985 ; // 6.88737225 fb 
}
else if (RunNumber == 303552 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM500_MM995";
    crossSection = 0.042475 * 0.92276 ; // 0.039194231 fb 
}
else if (RunNumber == 305710 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM500";
    crossSection = 18.275 * 0.87827 ; // 16.05038425 fb 
}
else if (RunNumber == 305711 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM700";
    crossSection = 7.416 * 0.89534 ; // 6.63984144 fb 
}
else if (RunNumber == 305712 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM10_MM300";
    crossSection = 63.99 * 0.83222 ; // 53.2537578 fb 
}
else if (RunNumber == 305713 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM10_MM500";
    crossSection = 18.295 * 0.87291 ; // 15.96988845 fb 
}
else if (RunNumber == 305714 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM30_MM10";
    crossSection = 17.62 * 0.66671 ; // 11.7474302 fb 
}
else if (RunNumber == 305715 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM30_MM100";
    crossSection = 451.1 * 0.65794 ; // 296.796734 fb 
}
else if (RunNumber == 305716 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM30_MM300";
    crossSection = 63.92 * 0.82926 ; // 53.0062992 fb 
}
else if (RunNumber == 305717 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM30_MM500";
    crossSection = 18.275 * 0.87184 ; // 15.932876 fb 
}
else if (RunNumber == 305718 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM30_MM700";
    crossSection = 7.4195 * 0.89334 ; // 6.62813613 fb 
}
else if (RunNumber == 305719 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM50_MM500";
    crossSection = 18.28 * 0.87184 ; // 15.9372352 fb 
}
else if (RunNumber == 305720 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM50_MM700";
    crossSection = 7.3995 * 0.89646 ; // 6.63335577 fb 
}
else if (RunNumber == 305721 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM100_MM100";
    crossSection = 2.277 * 0.8316 ; // 1.8935532 fb 
}
else if (RunNumber == 305722 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM100_MM300";
    crossSection = 60.09 * 0.83015 ; // 49.8837135 fb 
}
else if (RunNumber == 305723 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM100_MM500";
    crossSection = 18.115 * 0.8752 ; // 15.854248 fb 
}
else if (RunNumber == 305724 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM100_MM700";
    crossSection = 7.384 * 0.89437 ; // 6.60402808 fb 
}
else if (RunNumber == 306080 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM50";
    crossSection = 1403.5 * 0.45496 ; // 638.53636 fb 
}
else if (RunNumber == 306081 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM30_MM50";
    crossSection = 42.3 * 0.61155 ; // 25.868565 fb 
}
else if (RunNumber == 306082 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM55_MM100";
    crossSection = 22.91 * 0.72406 ; // 16.5882146 fb 
}
else if (RunNumber == 306083 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM25_MM150";
    crossSection = 237.8 * 0.73427 ; // 174.609406 fb 
}
else if (RunNumber == 306084 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM80_MM150";
    crossSection = 14.955 * 0.78137 ; // 11.68538835 fb 
}
else if (RunNumber == 306085 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM200";
    crossSection = 142.4 * 0.78542 ; // 111.843808 fb 
}
else if (RunNumber == 306086 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM50_MM200";
    crossSection = 139.8 * 0.78321 ; // 109.492758 fb 
}
else if (RunNumber == 306087 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM105_MM200";
    crossSection = 10.615 * 0.80913 ; // 8.58891495 fb 
}
else if (RunNumber == 306088 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM150_MM200";
    crossSection = 1.192 * 0.86044 ; // 1.02564448 fb 
}
else if (RunNumber == 306089 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM130_MM250";
    crossSection = 7.872 * 0.82891 ; // 6.52517952 fb 
}
else if (RunNumber == 306090 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM155_MM300";
    crossSection = 6.0065 * 0.84631 ; // 5.083361015 fb 
}
else if (RunNumber == 306091 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM200_MM300";
    crossSection = 0.7254 * 0.88269 ; // 0.640303326 fb 
}
else if (RunNumber == 306092 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM180_MM350";
    crossSection = 4.6775 * 0.8566 ; // 4.0067465 fb 
}
else if (RunNumber == 306093 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM400";
    crossSection = 31.865 * 0.85903 ; // 27.37299095 fb 
}
else if (RunNumber == 306094 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM50_MM400";
    crossSection = 31.765 * 0.85881 ; // 27.28009965 fb 
}
else if (RunNumber == 306095 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM100_MM400";
    crossSection = 31.145 * 0.85844 ; // 26.7361138 fb 
}
else if (RunNumber == 306096 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM150_MM400";
    crossSection = 28.34 * 0.85778 ; // 24.3094852 fb 
}
else if (RunNumber == 306097 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM205_MM400";
    crossSection = 3.68 * 0.86821 ; // 3.1950128 fb 
}
else if (RunNumber == 306098 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM250_MM400";
    crossSection = 0.47385 * 0.88849 ; // 0.4210109865 fb 
}
else if (RunNumber == 306099 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM230_MM450";
    crossSection = 2.943 * 0.87704 ; // 2.58112872 fb 
}
else if (RunNumber == 306100 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM200_MM500";
    crossSection = 15.465 * 0.87804 ; // 13.5788886 fb 
}
else if (RunNumber == 306101 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM255_MM500";
    crossSection = 2.384 * 0.88731 ; // 2.11534704 fb 
}
else if (RunNumber == 306102 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM280_MM550";
    crossSection = 1.9505 * 0.88818 ; // 1.73239509 fb 
}
else if (RunNumber == 306103 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM600";
    crossSection = 11.36 * 0.88253 ; // 10.0255408 fb 
}
else if (RunNumber == 306104 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM50_MM600";
    crossSection = 11.37 * 0.88763 ; // 10.0923531 fb 
}
else if (RunNumber == 306105 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM100_MM600";
    crossSection = 11.28 * 0.88511 ; // 9.9840408 fb 
}
else if (RunNumber == 306106 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM200_MM600";
    crossSection = 10.555 * 0.89031 ; // 9.39722205 fb 
}
else if (RunNumber == 306107 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM200_MM700";
    crossSection = 7.1035 * 0.89742 ; // 6.37482297 fb 
}
else if (RunNumber == 306108 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM300_MM700";
    crossSection = 5.7085 * 0.89598 ; // 5.11470183 fb 
}
else if (RunNumber == 306109 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM1_MM800";
    crossSection = 5.016 * 0.90147 ; // 4.52177352 fb 
}
else if (RunNumber == 306110 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM100_MM800";
    crossSection = 5.0025 * 0.90179 ; // 4.511204475 fb 
}
else if (RunNumber == 306111 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM200_MM800";
    crossSection = 4.879 * 0.90041 ; // 4.39310039 fb 
}
else if (RunNumber == 306112 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmV_Zll_MET40_DM300_MM800";
    crossSection = 4.387 * 0.90318 ; // 3.96225066 fb 
}
else if (RunNumber == 307191 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM10";
    crossSection = 11959.0 * 0.11444 ; // 1368.58796 fb 
}
else if (RunNumber == 307192 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM10_MM10";
    crossSection = 63.943 * 0.45019 ; // 28.78649917 fb 
}
else if (RunNumber == 307193 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM50_MM10";
    crossSection = 5.6363 * 0.84306 ; // 4.751739078 fb 
}
else if (RunNumber == 307194 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM5_MM30";
    crossSection = 2740.6 * 0.30942 ; // 847.996452 fb 
}
else if (RunNumber == 307195 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM50";
    crossSection = 1409.7 * 0.45773 ; // 645.261981 fb 
}
else if (RunNumber == 307196 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM30_MM50";
    crossSection = 15.618 * 0.67095 ; // 10.4788971 fb 
}
else if (RunNumber == 307197 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM25_MM80";
    crossSection = 442.36 * 0.59884 ; // 264.9028624 fb 
}
else if (RunNumber == 307198 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM100";
    crossSection = 470.17 * 0.65189 ; // 306.4991213 fb 
}
else if (RunNumber == 307199 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM55_MM100";
    crossSection = 6.4966 * 0.76104 ; // 4.944172464 fb 
}
else if (RunNumber == 307200 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM100_MM100";
    crossSection = 0.96525 * 0.8462 ; // 0.81679455 fb 
}
else if (RunNumber == 307201 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM50_MM130";
    crossSection = 131.68 * 0.71263 ; // 93.8391184 fb 
}
else if (RunNumber == 307202 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM150";
    crossSection = 238.65 * 0.73333 ; // 175.0092045 fb 
}
else if (RunNumber == 307203 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM25_MM150";
    crossSection = 217.9 * 0.73793 ; // 160.794947 fb 
}
else if (RunNumber == 307204 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM80_MM150";
    crossSection = 3.5204 * 0.80752 ; // 2.842793408 fb 
}
else if (RunNumber == 307205 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM75_MM180";
    crossSection = 53.361 * 0.76879 ; // 41.02340319 fb 
}
else if (RunNumber == 307206 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM200";
    crossSection = 142.51 * 0.77651 ; // 110.6604401 fb 
}
else if (RunNumber == 307207 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM50_MM200";
    crossSection = 112.77 * 0.78301 ; // 88.3000377 fb 
}
else if (RunNumber == 307208 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM105_MM200";
    crossSection = 2.156 * 0.83242 ; // 1.79469752 fb 
}
else if (RunNumber == 307209 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM150_MM200";
    crossSection = 0.43058 * 0.87343 ; // 0.3760814894 fb 
}
else if (RunNumber == 307210 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM100_MM230";
    crossSection = 25.667 * 0.80355 ; // 20.62471785 fb 
}
else if (RunNumber == 307211 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM250";
    crossSection = 92.89 * 0.81145 ; // 75.3755905 fb 
}
else if (RunNumber == 307212 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM75_MM250";
    crossSection = 63.449 * 0.81191 ; // 51.51487759 fb 
}
else if (RunNumber == 307213 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM130_MM250";
    crossSection = 1.4199 * 0.85035 ; // 1.207411965 fb 
}
else if (RunNumber == 307214 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM125_MM280";
    crossSection = 13.838 * 0.82718 ; // 11.44651684 fb 
}
else if (RunNumber == 307215 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM300";
    crossSection = 64.031 * 0.83004 ; // 53.14829124 fb 
}
else if (RunNumber == 307216 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM100_MM300";
    crossSection = 38.03 * 0.83035 ; // 31.5782105 fb 
}
else if (RunNumber == 307217 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM155_MM300";
    crossSection = 0.98358 * 0.86211 ; // 0.8479541538 fb 
}
else if (RunNumber == 307218 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM200_MM300";
    crossSection = 0.22889 * 0.88728 ; // 0.2030895192 fb 
}
else if (RunNumber == 307219 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM150_MM330";
    crossSection = 8.0786 * 0.84595 ; // 6.83409167 fb 
}
else if (RunNumber == 307220 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM350";
    crossSection = 45.975 * 0.84554 ; // 38.8737015 fb 
}
else if (RunNumber == 307221 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM125_MM350";
    crossSection = 23.891 * 0.84627 ; // 20.21823657 fb 
}
else if (RunNumber == 307222 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM180_MM350";
    crossSection = 0.70584 * 0.87097 ; // 0.6147654648 fb 
}
else if (RunNumber == 307223 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM175_MM380";
    crossSection = 4.9538 * 0.85917 ; // 4.256156346 fb 
}
else if (RunNumber == 307224 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM400";
    crossSection = 33.629 * 0.85773 ; // 28.84460217 fb 
}
else if (RunNumber == 307225 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM100_MM400";
    crossSection = 26.408 * 0.85868 ; // 22.67602144 fb 
}
else if (RunNumber == 307226 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM150_MM400";
    crossSection = 15.314 * 0.85911 ; // 13.15641054 fb 
}
else if (RunNumber == 307227 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM205_MM400";
    crossSection = 0.52028 * 0.8807 ; // 0.458210596 fb 
}
else if (RunNumber == 307228 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM250_MM400";
    crossSection = 0.13426 * 0.90095 ; // 0.120961547 fb 
}
else if (RunNumber == 307229 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM200_MM430";
    crossSection = 3.1494 * 0.86772 ; // 2.732797368 fb 
}
else if (RunNumber == 307230 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM450";
    crossSection = 25.155 * 0.86537 ; // 21.76838235 fb 
}
else if (RunNumber == 307231 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM175_MM450";
    crossSection = 10.103 * 0.86796 ; // 8.76899988 fb 
}
else if (RunNumber == 307232 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM230_MM450";
    crossSection = 0.39204 * 0.88834 ; // 0.3482648136 fb 
}
else if (RunNumber == 307233 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM225_MM480";
    crossSection = 2.0868 * 0.87594 ; // 1.827911592 fb 
}
else if (RunNumber == 307234 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM500";
    crossSection = 19.208 * 0.87511 ; // 16.80911288 fb 
}
else if (RunNumber == 307235 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM100_MM500";
    crossSection = 16.572 * 0.87512 ; // 14.50248864 fb 
}
else if (RunNumber == 307236 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM200_MM500";
    crossSection = 6.8612 * 0.87618 ; // 6.011646216 fb 
}
else if (RunNumber == 307237 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM255_MM500";
    crossSection = 0.30067 * 0.89354 ; // 0.2686606718 fb 
}
else if (RunNumber == 307238 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM250_MM530";
    crossSection = 1.4326 * 0.88334 ; // 1.265472884 fb 
}
else if (RunNumber == 307239 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM550";
    crossSection = 14.952 * 0.88211 ; // 13.18930872 fb 
}
else if (RunNumber == 307240 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM225_MM550";
    crossSection = 4.7804 * 0.88197 ; // 4.216169388 fb 
}
else if (RunNumber == 307241 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM280_MM550";
    crossSection = 0.23418 * 0.89722 ; // 0.2101109796 fb 
}
else if (RunNumber == 307242 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM600";
    crossSection = 11.809 * 0.8876 ; // 10.4816684 fb 
}
else if (RunNumber == 307243 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM100_MM600";
    crossSection = 10.658 * 0.88898 ; // 9.47474884 fb 
}
else if (RunNumber == 307244 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM250_MM600";
    crossSection = 3.4051 * 0.88872 ; // 3.026180472 fb 
}
else if (RunNumber == 307245 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM650";
    crossSection = 9.4444 * 0.89084 ; // 8.413449296 fb 
}
else if (RunNumber == 307246 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM700";
    crossSection = 7.6488 * 0.8957 ; // 6.85103016 fb 
}
else if (RunNumber == 307247 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM100_MM700";
    crossSection = 7.0815 * 0.89455 ; // 6.334755825 fb 
}
else if (RunNumber == 307248 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM750";
    crossSection = 6.2423 * 0.89813 ; // 5.606396899 fb 
}
else if (RunNumber == 307249 ){
    name = "MadGraphPythia8EvtGen_A14NNPDF30_dmA_Zll_MET40_DM1_MM800";
    crossSection = 5.1448 * 0.90203 ; // 4.640763944 fb 
}
else if (RunNumber == 344235 ){
    name = "PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau";
    crossSection = 3736.3 * 1.0 ; // 3736.3 fb 
}
else if (RunNumber == 344783 ){
    name = "gg2vvPy8EG_gg_ZZ_bkg_2l2v";
    crossSection = 31.72 * 1.0 ; // 31.72 fb 
}
else if (RunNumber == 344783 ){
    name = "gg2vvPy8EG_gg_ZZ_bkg_2l2v";
    crossSection = 31.72 * 1.0 ; // 31.72 fb 
}
else if (RunNumber == 344784 ){
    name = "gg2vvPy8EG_ggH125_1SMW_ZZ_2l2v";
    crossSection = 6.599 * 1.0 ; // 6.599 fb 
}
else if (RunNumber == 344784 ){
    name = "gg2vvPy8EG_ggH125_1SMW_ZZ_2l2v";
    crossSection = 6.599 * 1.0 ; // 6.599 fb 
}
else if (RunNumber == 344785 ){
    name = "gg2vvPy8EG_ggH125_1SMW_gg_ZZ_2l2v";
    crossSection = 35.33 * 1.0 ; // 35.33 fb 
}
else if (RunNumber == 344785 ){
    name = "gg2vvPy8EG_ggH125_1SMW_gg_ZZ_2l2v";
    crossSection = 35.33 * 1.0 ; // 35.33 fb 
}
else if (RunNumber == 344786 ){
    name = "gg2vvPy8EG_ggH125_5SMW_SC_gg_ZZ_2l2v";
    crossSection = 37.49 * 1.0 ; // 37.49 fb 
}
else if (RunNumber == 344786 ){
    name = "gg2vvPy8EG_ggH125_5SMW_SC_gg_ZZ_2l2v";
    crossSection = 37.49 * 1.0 ; // 37.49 fb 
}
else if (RunNumber == 344787 ){
    name = "gg2vvPy8EG_ggH125_10SMW_SC_gg_ZZ_2l2v";
    crossSection = 42.02 * 1.0 ; // 42.02 fb 
}
else if (RunNumber == 344787 ){
    name = "gg2vvPy8EG_ggH125_10SMW_SC_gg_ZZ_2l2v";
    crossSection = 42.02 * 1.0 ; // 42.02 fb 
}
else if (RunNumber == 345108 ){
        name = "Sherpa_221_NNPDF30NNLO_llll_m4l300";
            crossSection = 61.486 * 1.0 ; // 61.486 fb 
}
else if (RunNumber == 345107 ){
        name = "Sherpa_221_NNPDF30NNLO_llll_m4l100_300_filt100_150";
            crossSection = 352.99 * 0.12489 ; // 44.0849211 fb 
}
else if (RunNumber == 345363 ){
    name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pmkAv2p5";
    crossSection = 0.13793 * 1.0 ; // 0.13793 fb 
}
else if (RunNumber == 345382 ){
    name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pmkAvm5";
    crossSection = 0.66535 * 1.0 ; // 0.66535 fb 
}
else if (RunNumber == 345387 ){
    name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphmkHvm2p5kAvm5";
    crossSection = 0.94023 * 1.0 ; // 0.94023 fb 
}
else if (RunNumber == 345400 ){
    name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0phkHv10";
    crossSection = 0.75631 * 1.0 ; // 0.75631 fb 
}

// new EFT XS
else if (RunNumber == 345355 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0p";
            crossSection = 0.45261 * 1.0 ; // 0.45261 fb 
}
else if (RunNumber == 345356 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphkHv5";
            crossSection = 1.5186 * 1.0 ; // 1.5186 fb 
}
else if (RunNumber == 345357 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphkHvm5";
            crossSection = 0.62691 * 1.0 ; // 0.62691 fb 
}
else if (RunNumber == 345358 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphkHv2p5";
            crossSection = 0.76196 * 1.0 ; // 0.76196 fb 
}
else if (RunNumber == 345359 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphkHvm2p5";
            crossSection = 0.44424 * 1.0 ; // 0.44424 fb 
}
else if (RunNumber == 345360 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0phkHv10";
            crossSection = 0.27959 * 1.0 ; // 0.27959 fb 
}
else if (RunNumber == 345361 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pmkAv5";
            crossSection = 0.22887 * 1.0 ; // 0.22887 fb 
}
else if (RunNumber == 345362 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pmkAvm5";
            crossSection = 0.23076 * 1.0 ; // 0.23076 fb 
}
else if (RunNumber == 345364 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pmkAvm2p5";
            crossSection = 0.14136 * 1.0 ; // 0.14136 fb 
}
else if (RunNumber == 345365 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0mkAv15";
            crossSection = 0.12264 * 1.0 ; // 0.12264 fb 
}
else if (RunNumber == 345366 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphmkHv2p5kAvm5";
            crossSection = 0.32521 * 1.0 ; // 0.32521 fb 
}
else if (RunNumber == 345367 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphmkHvm2p5kAvm5";
            crossSection = 0.21181 * 1.0 ; // 0.21181 fb 
}
else if (RunNumber == 345368 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphmkHvm5kAv5";
            crossSection = 0.24512 * 1.0 ; // 0.24512 fb 
}
else if (RunNumber == 345369 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphmkHvm5kAvm6";
            crossSection = 0.28213 * 1.0 ; // 0.28213 fb 
}
else if (RunNumber == 345370 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphmkHv5kAv6";
            crossSection = 0.61354 * 1.0 ; // 0.61354 fb 
}
else if (RunNumber == 345371 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphmkHv5kAv5";
            crossSection = 0.53677 * 1.0 ; // 0.53677 fb 
}
else if (RunNumber == 345372 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphmkHv5kAv10";
            crossSection = 1.0192 * 1.0 ; // 1.0192 fb 
}
else if (RunNumber == 345373 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphmkHvm10kAv10";
            crossSection = 0.61143 * 1.0 ; // 0.61143 fb 
}
else if (RunNumber == 345374 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_vbf125_4l_0pphmkHv10kAvm10";
            crossSection = 2.1397 * 1.0 ; // 2.1397 fb 
}
else if (RunNumber == 345375 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0p";
            crossSection = 0.38035 * 1.0 ; // 0.38035 fb 
}
else if (RunNumber == 345376 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphkHv5";
            crossSection = 2.8035 * 1.0 ; // 2.8035 fb 
}
else if (RunNumber == 345377 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphkHvm5";
            crossSection = 4.0256 * 1.0 ; // 4.0256 fb 
}
else if (RunNumber == 345378 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphkHv2p5";
            crossSection = 0.44392 * 1.0 ; // 0.44392 fb 
}
else if (RunNumber == 345379 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphkHvm2p5";
            crossSection = 1.7924 * 1.0 ; // 1.7924 fb 
}
else if (RunNumber == 345380 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0phkHv10";
            crossSection = 1.8031 * 1.0 ; // 1.8031 fb 
}
else if (RunNumber == 345381 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pmkAv5";
            crossSection = 0.66541 * 1.0 ; // 0.66541 fb 
}
else if (RunNumber == 345383 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pmkAv2p5";
            crossSection = 0.23565 * 1.0 ; // 0.23565 fb 
}
else if (RunNumber == 345384 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pmkAvm2p5";
            crossSection = 0.23563 * 1.0 ; // 0.23563 fb 
}
else if (RunNumber == 345385 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0mkAv15";
            crossSection = 0.61385 * 1.0 ; // 0.61385 fb 
}
else if (RunNumber == 345386 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphmkHv2p5kAvm5";
            crossSection = 0.76889 * 1.0 ; // 0.76889 fb 
}
else if (RunNumber == 345388 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphmkHvm5kAv5";
            crossSection = 1.4415 * 1.0 ; // 1.4415 fb 
}
else if (RunNumber == 345389 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphmkHvm5kAvm6";
            crossSection = 1.6394 * 1.0 ; // 1.6394 fb 
}
else if (RunNumber == 345390 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphmkHv5kAv6";
            crossSection = 1.8017 * 1.0 ; // 1.8017 fb 
}
else if (RunNumber == 345391 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphmkHv5kAv5";
            crossSection = 1.4652 * 1.0 ; // 1.4652 fb 
}
else if (RunNumber == 345392 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphmkHv5kAv10";
            crossSection = 3.836 * 1.0 ; // 3.836 fb 
}
else if (RunNumber == 345393 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphmkHvm10kAv10";
            crossSection = 3.8208 * 1.0 ; // 3.8208 fb 
}
else if (RunNumber == 345394 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_wh125_4l_0pphmkHv10kAvm10";
            crossSection = 8.7931 * 1.0 ; // 8.7931 fb 
}
else if (RunNumber == 345395 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0p";
            crossSection = 0.20126 * 1.0 ; // 0.20126 fb 
}
else if (RunNumber == 345396 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphkHv5";
            crossSection = 1.0678 * 1.0 ; // 1.0678 fb 
}
else if (RunNumber == 345397 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphkHvm5";
            crossSection = 1.7971 * 1.0 ; // 1.7971 fb 
}
else if (RunNumber == 345398 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphkHv2p5";
            crossSection = 0.16399 * 1.0 ; // 0.16399 fb 
}
else if (RunNumber == 345399 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphkHvm2p5";
            crossSection = 0.83647 * 1.0 ; // 0.83647 fb 
}
else if (RunNumber == 345401 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pmkAv5";
            crossSection = 0.2715 * 1.0 ; // 0.2715 fb 
}
else if (RunNumber == 345402 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pmkAvm5";
            crossSection = 0.27146 * 1.0 ; // 0.27146 fb 
}
else if (RunNumber == 345403 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pmkAv2p5";
            crossSection = 0.10488 * 1.0 ; // 0.10488 fb 
}
else if (RunNumber == 345404 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pmkAvm2p5";
            crossSection = 0.10488 * 1.0 ; // 0.10488 fb 
}
else if (RunNumber == 345405 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0mkAv15";
            crossSection = 0.23888 * 1.0 ; // 0.23888 fb 
}
else if (RunNumber == 345406 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphmkHv2p5kAvm5";
            crossSection = 0.29692 * 1.0 ; // 0.29692 fb 
}
else if (RunNumber == 345407 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphmkHvm2p5kAvm5";
            crossSection = 0.40215 * 1.0 ; // 0.40215 fb 
}
else if (RunNumber == 345408 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphmkHvm5kAv5";
            crossSection = 0.62104 * 1.0 ; // 0.62104 fb 
}
else if (RunNumber == 345409 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphmkHvm5kAvm6";
            crossSection = 0.69815 * 1.0 ; // 0.69815 fb 
}
else if (RunNumber == 345410 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphmkHv5kAv6";
            crossSection = 0.69557 * 1.0 ; // 0.69557 fb 
}
else if (RunNumber == 345411 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphmkHv5kAv5";
            crossSection = 0.562 * 1.0 ; // 0.562 fb 
}
else if (RunNumber == 345412 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphmkHv5kAv10";
            crossSection = 1.4888 * 1.0 ; // 1.4888 fb 
}
else if (RunNumber == 345413 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphmkHvm10kAv10";
            crossSection = 1.5981 * 1.0 ; // 1.5981 fb 
}
else if (RunNumber == 345414 ){
        name = "aMcAtNloPy8EG_A14NNPDF23LO_zh125_4l_0pphmkHv10kAvm10";
            crossSection = 3.467 * 1.0 ; // 3.467 fb 
}

// Sherpa 2.2.2 samples
else if (RunNumber == 364250 ){
        name = "Sherpa_222_NNPDF30NNLO_llll";
            crossSection = 1252.2 * 1.0 ; // 1252.2 fb 
}
else if (RunNumber == 364251 ){
        name = "Sherpa_222_NNPDF30NNLO_llll_m4l100_300_filt100_150";
            crossSection = 352.75 * 0.12457 ; // 43.9421 fb 
}
else if (RunNumber == 364252 ){
        name = "Sherpa_222_NNPDF30NNLO_llll_m4l300";
            crossSection = 61.677 * 1.0 ; // 61.677 fb 
}


// XS and BR from LHCXSWD
else if (RunNumber == 342001 ){
        name = "aMcAtNloHppEG_UEEE5_CTEQ6L1_CT10ME_tWH125_lep_yt_plus1";
            crossSection = 15.17 * 0.30261 ; // fb 
}
else if (RunNumber == 343273 ){
        name = "MadGraphPythia8EvtGen_A14_CT10ME_tHjb125_lep";
            crossSection = 77.129 * 0.30261; // fb 
}

// HWW sample - XS computed using YR4 by Aaron, added by Haider
else if (RunNumber ==  341421){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_WmH125J_MINLO_eveWWlvlv";
    crossSection = 1.342; // fb 
}
else if (RunNumber == 341423 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_WmH125J_MINLO_muvmuWWlvlv";
    crossSection = 1.342; // fb 
}
else if (RunNumber == 341429 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_WpH125J_MINLO_eveWWlvlv";
    crossSection = 2.115; // fb 
}
else if (RunNumber == 341431 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_WpH125J_MINLO_muvmuWWlvlv";
    crossSection = 2.115; // fb 
}
else if (RunNumber == 343275 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_WmH125J_MINLO_eveWWlvlv";
    crossSection = 1.342; // fb 
}
else if (RunNumber == 343276 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_WmH125J_MINLO_muvmuWWlvlv";
    crossSection = 1.342; // fb 
}
else if (RunNumber == 343277 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_WpH125J_MINLO_eveWWlvlv";
    crossSection = 2.115; // fb 
}
else if (RunNumber == 343278 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_WpH125J_MINLO_muvmuWWlvlv";
    crossSection = 2.115; // fb 
}
else if (RunNumber == 344376 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_ggZH125_eeWWlvlv";
    crossSection = 0.093; // fb 
}
else if (RunNumber == 344378 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_ggZH125_mumuWWlvlv";
    crossSection = 0.093; // fb 
}
else if (RunNumber == 344380 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_ggZH125_tautauWWlvlv";
    crossSection = 0.093; // fb 
}
else if (RunNumber == 341449 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_ZH125J_MINLO_eeWWlvlv_VpT";
    crossSection = 0.576; // fb 
}
else if (RunNumber == 341451 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_ZH125J_MINLO_mumuWWlvlv_VpT";
    crossSection = 0.576; // fb 
}
else if (RunNumber == 341453 ){
    name = "PowhegPythia8EvtGen_CT10_AZNLO_ZH125J_MINLO_tautauWWlvlv_VpT";
    crossSection = 0.576; // fb 
}

// Test for Jochen
else if (RunNumber == 123456)
{
    name = "testSample";
    crossSection = 1.0;
}
// Test for Roberto
else if (RunNumber >= 890000 && RunNumber <= 890440)
{
    name = "testSample";
    crossSection = 1.0;
}
else if (RunNumber >= 990000 && RunNumber <= 990440)
{
    name = "testSample";
    crossSection = 1.0;
}

 if (PrintSummary){
    if (crossSection!=-1){
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"               Cross section x Branching Ratio = "<< crossSection <<" fb^-1 "<< std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
    }else{
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"                    NO Cross section !!!  " << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    }
  }
  return crossSection;


} //end of CrossSections::GetBkgCrossSection13TeV


double CrossSections::GetBkgCrossSection13_5TeV(int /*RunNumber*/, bool /*PrintSummary*/)
{
   std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; 
   std::cout << " The GetBkgCrossSection for the 13.5TeV has lack of contents! " << std::endl;
   std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
 
   return 0;
}

double CrossSections::GetBkgCrossSection14TeV(int /*RunNumber*/, bool /*PrintSummary*/)
{
   std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; 
   std::cout << " The GetBkgCrossSection for the 14TeV has lack of contents! " << std::endl;
   std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

   return 0;
}


