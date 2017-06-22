
#include "TMath.h"
#include "TRandom3.h"
#include "TLorentzVector.h"
#include "MCFM_MatrixElement/TUtil.h"
#include "TCanvas.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "TProfile.h"

using namespace std;

void SetEwkCoupligParameters(){

  ewinput_.Gf_inp=1.16639E-05;
  ewinput_.aemmz_inp=7.81751E-03;
  ewinput_.wmass_inp=79.956049884402844;
  ewinput_.zmass_inp=91.1876;
  ewinput_.xw_inp=0.23116864;

}

void SetAlphaS (double Q, int mynloop, int mynflav, string mypartons){
	if(Q<=1 || mynloop<=0 || mypartons.compare("Default")==0){
		if(Q<0) cout << "Invalid QCD scale for alpha_s, setting to mH/2..." << endl;
		Q = (masses_mcfm_.hmass)*0.5;
		mynloop = 1;
	};
	if(mypartons.compare("Default")!=0 && mypartons.compare("cteq6_l")!=0 && mypartons.compare("cteq6l1")!=0&& mypartons.compare("CT14.NN")!=0){
		cout << "Only default :: cteq6l1 or cteq6_l are supported. Modify mela.cc symlinks, put the pdf table into data/Pdfdata and retry. Setting to Default..." << endl;
		mypartons = "Default";
	};

	bool nflav_is_same = (nflav_.nflav == mynflav);
	mcfmscale_.scale = Q;
	mcfmscale_.musq = Q*Q;
	nlooprun_.nlooprun = mynloop;

// From pdfwrapper_linux.f:
	if(mypartons.compare("cteq6_l")==0) couple_.amz = 0.118;
  else if(mypartons.compare("cteq6l1")==0 || mypartons.compare("Default")==0) couple_.amz = 0.130;
	else if(mypartons.compare("CT14.NN")==0) couple_.amz = 0.118;
	else couple_.amz = 0.118; // Add pdf as appropriate

// For proper pdfwrapper_linux.f execution (alpha_s computation does not use pdf but examines the pdf name to initialize amz.)
	if(!nflav_is_same){
		nflav_.nflav = mynflav;

		if(mypartons.compare("Default")!=0) sprintf(pdlabel_.pdlabel,"%s",mypartons.c_str());
		else sprintf(pdlabel_.pdlabel,"%s","cteq6l1"); // Default pdf is cteq6l1
		coupling2_();
	}
	else{
		qcdcouple_.as = alphas_(&(mcfmscale_.scale),&(couple_.amz),&(nlooprun_.nlooprun));
	};

	qcdcouple_.gsq = 4.0*TMath::Pi()*qcdcouple_.as;
	qcdcouple_.ason2pi = qcdcouple_.as/(2.0*TMath::Pi());
	qcdcouple_.ason4pi = qcdcouple_.as/(4.0*TMath::Pi());

// TEST RUNNING SCALE PER EVENT:
/*
	if(verbosity >= TVar::DEBUG){
		cout << "My pdf is: " << pdlabel_.pdlabel << endl;
		cout << "My Q: " << Q << " | My alpha_s: " << qcdcouple_.as << " at order " << nlooprun_.nlooprun << " with a(m_Z): " << couple_.amz << '\t'
			<< "Nflav: " << nflav_.nflav << endl;
*/
}

void My_choose(TVar::Process process, const TVar::LeptonInterference& leptonInterf, bool hasZZ4fInterf){

  //ZZ_4l
  if(process==TVar::QQbZZ_4l){ 

    //81 '  f(p1)+f(p2) --> Z^0(-->mu^-(p3)+mu^+(p4)) + Z^0(-->e^-(p5)+e^+(p6))'
    //86 '  f(p1)+f(p2) --> Z^0(-->e^-(p5)+e^+(p6))+Z^0(-->mu^-(p3)+mu^+(p4)) (NO GAMMA*)'
    //90 '  f(p1)+f(p2) --> Z^0(-->e^-(p3)+e^+(p4)) + Z^0(-->e^-(p5)+e^+(p6))' 'L'
    //    nproc_.nproc=81;  
    //    chooser_();

    // these settings are identical to use the chooser_() function
    npart_.npart=4;
    nqcdjets_.nqcdjets=0;

    if(hasZZ4fInterf && (leptonInterf==TVar::QQbInterfOnly || leptonInterf==TVar::InterfBoth) ) {
      //90 '  f(p1)+f(p2) --> Z^0(-->e^-(p3)+e^+(p4)) + Z^0(-->e^-(p5)+e^+(p6))' 'L'
      vsymfact_.vsymfact=0.25;
      interference_.interference=true;
    } else {
      vsymfact_.vsymfact=1.0;
      interference_.interference=false;
    }

    nwz_.nwz=0;
    bveg1_mcfm_.ndim=10;
    //masses_mcfm_.mb=0;
    //if ( process == TVar::GGZZ_4l ) 
    //  masses_mcfm_.mb=4.75;
    breit_.n2=1;
    breit_.n3=1;

    breit_.mass2=masses_mcfm_.zmass;
    breit_.width2=masses_mcfm_.zwidth;
    breit_.mass3=masses_mcfm_.zmass;
    breit_.width3=masses_mcfm_.zwidth;

    zcouple_.q1=-1.0;
    zcouple_.l1=zcouple_.le;
    zcouple_.r1=zcouple_.re;

    zcouple_.q2=-1.0;
    zcouple_.l2=zcouple_.le;
    zcouple_.r2=zcouple_.re;

  }  else if ( process == TVar::HZZ_4l || process == TVar::GGZZTOT_4l || process == TVar::GGZZINT_4l || process == TVar::GGZZ_4l)
  {

    /*
    c--- 128 '  f(p1)+f(p2) --> H(--> Z^0(e^-(p3)+e^+(p4)) + Z^0(mu^-(p5)+mu^+(p6)) [top, bottom loops, exact]' 'L'
    c--- 129 '  f(p1)+f(p2) --> H(--> Z^0(e^-(p3)+e^+(p4)) + Z^0(mu^-(p5)+mu^+(p6)) [only H, gg->ZZ intf.]' 'L' -> NOT IMPLEMENTED
    c--- 130 '  f(p1)+f(p2) --> H(--> Z^0(e^-(p3)+e^+(p4)) + Z^0(mu^-(p5)+mu^+(p6)) [H squared and H, gg->ZZ intf.]' 'L'
    c--- 131 '  f(p1)+f(p2) --> Z^0(e^-(p3)+e^+(p4)) + Z^0(mu^-(p5)+mu^+(p6) [gg only, (H + gg->ZZ) squared]' 'L'
    c--- 132 '  f(p1)+f(p2) --> Z^0(e^-(p3)+e^+(p4)) + Z^0(mu^-(p5)+mu^+(p6) [(gg->ZZ) squared]' 'L'
    */
    // nproc_.nproc=114;
    // chooser_();

    npart_.npart=4;
    nqcdjets_.nqcdjets=0;

    if(hasZZ4fInterf && (leptonInterf==TVar::GGInterfOnly || leptonInterf==TVar::InterfBoth) ) {
      vsymfact_.vsymfact=0.25;
      interference_.interference=true;
    } else {
      vsymfact_.vsymfact=1.0;
      interference_.interference=false;
    }

    bveg1_mcfm_.ndim=10;
    //masses_mcfm_.mb=4.75; // necessary for the ggZZ and HZZ interference 
    //masses_mcfm_.mb = 0; 
    breit_.n2=1;
    breit_.n3=1;

    breit_.mass2 =masses_mcfm_.zmass;
    breit_.width2=masses_mcfm_.zwidth;
    breit_.mass3 =masses_mcfm_.zmass;
    breit_.width3=masses_mcfm_.zwidth;

    zcouple_.q1=-1.0;
    zcouple_.l1=zcouple_.le;
    zcouple_.r1=zcouple_.re;

    zcouple_.q2=-1.0;
    zcouple_.l2=zcouple_.le;
    zcouple_.r2=zcouple_.re;

  } 
  else{
    std::cerr <<"[My_choose]: Can't identify Process: " << process <<endl;
  } 
}

bool My_masscuts(double s[][mxpart],TVar::Process process){

  double minZmassSqr=10*10;

  if(process==TVar::QQbZZ_4l || process==TVar::GGZZ_4l){
    if(s[2][3]< minZmassSqr) return true;
    if(s[4][5]< minZmassSqr) return true;
  }
  return false;	 

}


bool My_smalls(double s[][mxpart],int npart){

  // Reject event if any s(i,j) is too small
  // cutoff is defined in technical.Dat

  if ( 
      npart == 3 &&
      (
       (-s[5-1][1-1]< cutoff_.cutoff)  //gamma p1
       || (-s[5-1][2-1]< cutoff_.cutoff)  //gamma p2
       || (-s[4-1][1-1]< cutoff_.cutoff)  //e+    p1
       || (-s[4-1][2-1]< cutoff_.cutoff)  //e-    p2
       || (-s[3-1][1-1]< cutoff_.cutoff)  //nu    p1
       || (-s[3-1][2-1]< cutoff_.cutoff)  //nu    p2
       || (+s[5-1][4-1]< cutoff_.cutoff)  //gamma e+
       || (+s[5-1][3-1]< cutoff_.cutoff)  //gamma nu
       || (+s[4-1][3-1]< cutoff_.cutoff)  //e+    nu
      )	 
     ) 
    return true;

  else if (
      npart == 4 &&     
      (
       (-s[5-1][1-1]< cutoff_.cutoff)  //e-    p1
       || (-s[5-1][2-1]< cutoff_.cutoff)  //e-    p2
       || (-s[6-1][1-1]< cutoff_.cutoff)  //nb    p1
       || (-s[6-1][2-1]< cutoff_.cutoff)  //nb    p2
       || (+s[6-1][5-1]< cutoff_.cutoff)  //e-    nb
      )

      )

    return true;

  return false;
}




//Make sure
// 1. tot Energy Sum < 2EBEAM
// 2. PartonEnergy Fraction minimum<x0,x1<1
// 3. number of final state particle is defined
//
double SumMatrixElementPDF(TVar::Process process, mcfm_event_type* mcfm_event,double flavor_msq[nmsq][nmsq],double* flux, bool fixedScale){

  int NPart=npart_.npart+2;
  double p4[4][mxpart];
  double msq[nmsq][nmsq];

  //Parton Density Function is always evalualted at pT=0 frame
  //Make sure parton Level Energy fraction is [0,1]
  //phase space function already makes sure the parton energy fraction between [min,1]
  //  x0 EBeam =>   <= -x1 EBeam

  double sysPz=mcfm_event->p[0].Pz()    +mcfm_event->p[1].Pz();
  double sysE =mcfm_event->p[0].Energy()+mcfm_event->p[1].Energy();

  //Ignore the Pt doesn't make significant effect
  //double sysPt_sqr=sysPx*sysPx+sysPy*sysPy;
  //if(sysPt_sqr>=1.0E-10)  sysE=TMath::Sqrt(sysE*sysE-sysPt_sqr);

  double xx[2]={(sysE+sysPz)/EBEAM/2,(sysE-sysPz)/EBEAM/2};
  if(xx[0] > 1.0 || xx[0]<=xmin_.xmin) return 0.0;
  if(xx[1] > 1.0 || xx[1]<=xmin_.xmin) return 0.0;

  //Convert TLorentzVector into 4x12 Matrix
  //reverse sign of incident partons back
  for(int ipar=0;ipar<2;ipar++){    
    if(mcfm_event->p[ipar].Energy()>0){
      p4[0][ipar] = -mcfm_event->p[ipar].Px();
      p4[1][ipar] = -mcfm_event->p[ipar].Py();
      p4[2][ipar] = -mcfm_event->p[ipar].Pz();
      p4[3][ipar] = -mcfm_event->p[ipar].Energy();
    }
  }

  // double invariantP[5] = {0};
  double m4l = (mcfm_event->p[2]+mcfm_event->p[3]+mcfm_event->p[4]+mcfm_event->p[5]).M();
  // //initialize decayed particles
  for(int ipar=2;ipar<NPart;ipar++){

    p4[0][ipar] = mcfm_event->p[ipar].Px();
    p4[1][ipar] = mcfm_event->p[ipar].Py();
    p4[2][ipar] = mcfm_event->p[ipar].Pz();
    p4[3][ipar] = mcfm_event->p[ipar].Energy();

  //   invariantP[1] += p4[3][ipar];
  //   invariantP[2] += p4[0][ipar];
  //   invariantP[3] += p4[1][ipar];
  //   invariantP[4] += p4[2][ipar];

  }

  // invariantP[0] = pow(invariantP[1],2.0);
  // for(int iq=2;iq<5;iq++) invariantP[0] -= pow(invariantP[iq],2.0);
  // invariantP[0] = sqrt(fabs(invariantP[0]));

  double defaultScale = mcfmscale_.scale;
  int defaultNloop = nlooprun_.nlooprun;
  int defaultNflav = nflav_.nflav;
  string defaultPdflabel = pdlabel_.pdlabel;

  if(!fixedScale)
    SetAlphaS( m4l , 1 , 5 , "cteq6_l"); // Set AlphaS(|Q|/2, mynloop, mynflav, mypartonPDF) for MCFM ME-related calculations  

  double newScale = mcfmscale_.scale;
  int newNloop = nlooprun_.nlooprun;
  int newNflav = nflav_.nflav;
  string newPdflabel = pdlabel_.pdlabel;

  //calculate invariant masses between partons/final state particles
  double s[mxpart][mxpart];
  for(int jdx=0;jdx< NPart ;jdx++){
    s[jdx][jdx]=0;
    for(int kdx=jdx+1;kdx<NPart;kdx++){
      s[jdx][kdx]=2*(p4[3][jdx]*p4[3][kdx]-p4[2][jdx]*p4[2][kdx]-p4[1][jdx]*p4[1][kdx]-p4[0][jdx]*p4[0][kdx]);
      s[kdx][jdx]=s[jdx][kdx];
    }
  }


  //remove events has small invariant masses
  // if(My_masscuts(s,process)) return 0.0;
  if(My_smalls(s,npart_.npart)) return 0.0;

  double msqjk=0;
  double msqgg=0;

  if( process==TVar::QQbZZ_4l )      qqb_zz_(p4[0],msq[0]);
  if( process==TVar::HZZ_4l )     gg_hzz_tb_(p4[0],msq[0]);
  // the one commented below would use infinite quark masses. Useful when comparing to MadGraph HEFT
  // if( process==TVar::HZZ_4l )     qqb_hzz_(p4[0],msq[0]);
  if( process==TVar::GGZZ_4l)    gg_zz_  (p4[0],msq[0]);                     
  if( process==TVar::GGZZTOT_4l) gg_zz_all_ (p4[0], msq[0]);                     
  if( process==TVar::GGZZINT_4l) gg_zz_int_ (p4[0], msq[0]);                     

  // by default assume only gg productions 
  // FOTRAN convention -5    -4   -3  -2    -1  0 1 2 3 4 5 
  //     parton flavor bbar cbar sbar ubar dbar g d u s c b
  // C++ convention     0     1   2    3    4   5 6 7 8 9 10


  // MAX: These lines allow to test the dxs distro with PDF
  // double sumPDF = SumMEPDF(mcfm_event->p[0],mcfm_event->p[1], &msq[0], TVar::ERROR);
  // SetAlphaS( defaultScale , defaultNloop , defaultNflav , defaultPdflabel); // Protection for other probabilities
  // return sumPDF;


  msqjk=msq[5][5];
  msqgg = msq[5][5];
  if( process==TVar::QQbZZ_4l ) msqjk=msq[3][7]+msq[7][3];
  // if (process == TVar::HZZ_4l && fabs(m4l - 125) < 2){
    // std::cout << "======================================"<<std::endl;
    // // std::cout << "mH = "<<_hmass<<", sigma = "<<_hwidth<<std::endl;
    // std::cout << "mass "<<m4l<<", scale = "<< mcfmscale_.scale<<std::endl;
    // std::cout << "mH in masses_mcfm_ = "<<masses_mcfm_.hmass<<", sigma = "<<masses_mcfm_.hwidth<<std::endl;
    // std::cout << "QCD g2 = "<<qcdcouple_.gsq<<", alpha_s = "<<qcdcouple_.as<<std::endl;
    // std::cout << "EW Gf = "<<ewcouple_.Gf<<", gw = "<<ewcouple_.gw<<", esq "<<ewcouple_.esq<<std::endl;;
    // std::cout << "msqgg = "<<msqgg<<std::endl;

  // }
  // special for the GGZZ 
  if( process==TVar::GGZZ_4l || process == TVar::HZZ_4l) msqjk=msqgg;      

  (*flux)=fbGeV2/(8*xx[0]*xx[1]*EBEAM*EBEAM);
  // std::cout << "Scale: "<< mcfmscale_.scale<<std::endl;
  if(msqjk != msqjk || flux!=flux ){
    cout << "SumMatrixPDF: "<< TVar::ProcessName(process) << " msqjk="  << msqjk << " flux="<< flux <<endl;
    msqjk=0;
    flux=0;
  }



  SetAlphaS( defaultScale , defaultNloop , defaultNflav , defaultPdflabel); // Protection for other probabilities
  return msqjk;

}

// Below code sums over all production parton flavors according to PDF 
double SumMEPDF(const TLorentzVector p0, const TLorentzVector p1, double msq[nmsq][nmsq],  TVar::VerbosityLevel verbosity)
{
  //Calculate Pdf
  //Parton Density Function is always evalualted at pT=0 frame
  //Make sure parton Level Energy fraction is [0,1]
  //phase space function already makes sure the parton energy fraction between [min,1]
  //  x0 EBeam =>   <= -x1 EBeam
  double sysPz=p0.Pz()    + p1.Pz();
  double sysE =p0.Energy()+ p1.Energy();

  //Ignore the Pt doesn't make significant effect
  //double sysPt_sqr=sysPx*sysPx+sysPy*sysPy;
  //if(sysPt_sqr>=1.0E-10)  sysE=TMath::Sqrt(sysE*sysE-sysPt_sqr);
  double xx[2]={(sysE+sysPz)/EBEAM/2,(sysE-sysPz)/EBEAM/2};
  if ( verbosity >= TVar::DEBUG ) {
    std::cout << "xx[0]: " << xx[0] << "\t xx[1] = " << xx[1] << "\n";
  }

  if(xx[0] > 1.0 || xx[0]<=xmin_.xmin) return 0.0;
  if(xx[1] > 1.0 || xx[1]<=xmin_.xmin) return 0.0;
  double fx1[nmsq];
  double fx2[nmsq];

  //Always pass address through fortran function
  fdist_ (&density_.ih1, &xx[0], &mcfmscale_.scale, fx1); 
  fdist_ (&density_.ih2, &xx[1], &mcfmscale_.scale, fx2); 
  if ( verbosity >= TVar::DEBUG ) {
    for ( int i = 0; i < nmsq; i++ ) {
      std::cout << "fx1[" << i << "]: " <<  fx1[i] << "\t"
        "fx2[" << i << "]: " <<  fx2[i] << "\n";
    }
  }

  double msqjk(0.);
  double flavor_msq[nmsq][nmsq];

  for(int ii=0;ii<nmsq;ii++){
    for(int jj=0;jj<nmsq;jj++){
      flavor_msq[jj][ii] = 0.;
      //2-D matrix is reversed in fortran
      // msq[ parton2 ] [ parton1 ]
      flavor_msq[jj][ii] = fx1[ii]*fx2[jj]*msq[jj][ii];
      msqjk+=flavor_msq[jj][ii];
    }//ii
  }//jj

  return msqjk;

}
