//--------------------------------------------------------------------------------
// Author: K. Potamianos <karolos.potamianos@cern.ch
// Date: 2013-VI-10
// Descrption: Template function to compute ME from MG standalone_cpp code
// Updates:
//--------------------------------------------------------------------------------

#include <TLorentzVector.h>

#include <iostream>
#include <iomanip>
#include <vector>

//#define VERBOSE

// Inputs should be in GeV: MG uses GeV internally and a scale factor is applied
// To use MeV, please define MGME_USE_MEV 

// The code assumes that the lepton 4-vectors are in the centre-of-mass system.
// Please see the example code or README for more information

template <typename CPPProcessT>
std::vector<float> ComputeMGME(CPPProcessT &S_sm, const std::vector<TLorentzVector>& fermions, const TLorentzVector& cms);

// Will use the cms mass as a value for MH
// You need to edit your CPPProcess class and include a setM4l(double) function for this to compile
template <typename CPPProcessT>
std::vector<float> ComputeMGME_cmsM4l(CPPProcessT &S_sm, const std::vector<TLorentzVector>& fermions, const TLorentzVector& cms, const TLorentzVector& cms4l) {
#ifdef MGME_USE_MEV
	const double scale = 1E-3;
#else
	const double scale = 1.;
#endif
	S_sm.setM4l(cms4l.M()*scale);
	return ComputeMGME(S_sm, fermions, cms);
}

template <typename CPPProcessT>
std::vector<float> ComputeMGME(CPPProcessT &S_sm, const std::vector<TLorentzVector>& fermions, const TLorentzVector& cms) {
  
  // Input to be provided: p[NEXTERNAL][4]
  std::vector<double*> p;
  
#ifdef MGME_USE_MEV
  const double scale = 1E-3;
#else
  const double scale = 1.;
#endif
  
  p.push_back(new double[4]);
  p[0][0] = cms.M()/2;
  p[0][1] = 0.;
  p[0][2] = 0.;
  p[0][3] = cms.M()/2;

  p.push_back(new double[4]);
  p[1][0] = cms.M()/2;
  p[1][1] = 0.;
  p[1][2] = 0.;
  p[1][3] = -cms.M()/2;
  
  double (TLorentzVector::*fPtr[])() const =  { &TLorentzVector::E, &TLorentzVector::Px, &TLorentzVector::Py, &TLorentzVector::Pz };
  
  
  for(int j = 0 ; j < 4 ; ++j) {
    p[0][j] *= scale;
    p[1][j] *= scale;
  }  

  for(unsigned int i = 0 ; i < fermions.size() ; ++i) {
    p.push_back(new double[4]);
    for(int j = 0 ; j < 4 ; ++j)
      p[i+2][j] = (fermions[i].*fPtr[j])()*scale;
  }

  S_sm.setMomenta(p);
  // Evaluate matrix element
  S_sm.sigmaKin();
  const double* theMEs = S_sm.getMatrixElements();
  
#ifdef VERBOSE
  for(int i=0;i < S_sm.nexternal; i++)
    cout << setw(4) << i+1
	 << setiosflags(ios::scientific) << setw(20) << "\t" << p[i][0]
	 << setiosflags(ios::scientific) << setw(20) << "\t" << p[i][1]
	 << setiosflags(ios::scientific) << setw(20) << "\t" << p[i][2]
	 << setiosflags(ios::scientific) << setw(20) << "\t" << p[i][3] << endl;
  cout << " -----------------------------------------------------------------------------" << endl;
  for(int i = 0 ; i < S_sm.nprocesses ; ++i) {
    std::cout << " Matrix element = "
	      << std::setiosflags(std::ios::fixed) << std::setprecision(17)
	      << theMEs[i]
	      << " GeV^" << -(2*S_sm.nexternal-8) << endl;
  }
#endif
  
  for(std::vector<double*>::iterator it = p.begin() ; it != p.end() ; ++it)
    delete[] *it;
  
  std::vector<float> outValue;
  for(int i = 0 ; i < S_sm.nprocesses ; ++i)
    outValue.push_back(theMEs[i]);
  //copy(outValue.begin(), outValue.end(), ostream_iterator<float>(cout, "\t")); cout << endl;
  return outValue; // Most decent compilers should optimize the copy of the vector
}

