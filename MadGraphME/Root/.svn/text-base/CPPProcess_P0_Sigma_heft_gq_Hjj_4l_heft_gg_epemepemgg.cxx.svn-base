//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph5_aMC@NLO v. 2.2.1, 2014-09-25
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================
// This code is adjusted to handle some features. For more info, see README.
// Contact: K. Potamianos <karolos.potamianos@cern.ch>
//==========================================================================

#include "CPPProcess_P0_Sigma_heft_gq_Hjj_4l_heft_gg_epemepemgg.h"
#include "HelAmps_heft.h"

using namespace MG5_heft; 

//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: g g > h g g WEIGHTED=4 HIG=1 HIW=1
// *   Decay: h > e+ e- e+ e- HIG=1 HIW=0
// Process: g g > h g g WEIGHTED=4 HIG=1 HIW=1
// *   Decay: h > mu+ mu- mu+ mu- HIG=1 HIW=0

//--------------------------------------------------------------------------
// Initialize process.

void CPPProcess_P0_Sigma_heft_gq_Hjj_4l_heft_gg_epemepemgg::initProc(string param_card_name) 
{
  // Instantiate the model class and set parameters that stay fixed during run
  pars = Parameters_heft::getInstance(); 
  SLHAReader slha(param_card_name); 
  pars->setIndependentParameters(slha); 
  pars->setIndependentCouplings(); 
  if(MG_PRINT_PARS) pars->printIndependentParameters(); 
  if(MG_PRINT_PARS) pars->printIndependentCouplings(); 
  // Set external particle masses for this matrix element
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  mME.push_back(pars->ZERO); 
  jamp2[0] = new double[6]; 
}

//--------------------------------------------------------------------------
// Set M4l Mass

void CPPProcess_P0_Sigma_heft_gq_Hjj_4l_heft_gg_epemepemgg::setM4l(double m_m4l){
   //Adujst Parameters_sm to include new function if you wish to use m4l as mH, following Parameters_heft
   pars->set4lepMass(m_m4l);
}

//--------------------------------------------------------------------------
// Evaluate |M|^2, part independent of incoming flavour.

void CPPProcess_P0_Sigma_heft_gq_Hjj_4l_heft_gg_epemepemgg::sigmaKin() 
{
  // Set the parameters which change event by event
  pars->setDependentParameters(); 
  pars->setDependentCouplings(); 
  static bool firsttime = true; 
  if (firsttime)
  {
    pars->printDependentParameters(); 
    pars->printDependentCouplings(); 
    firsttime = false; 
  }

  // Reset color flows
  for(int i = 0; i < 6; i++ )
    jamp2[0][i] = 0.; 

  // Local variables and constants
  const int ncomb = 256; 
  static bool goodhel[ncomb] = {ncomb * false}; 
  static int ntry = 0, sum_hel = 0, ngood = 0; 
  static int igood[ncomb]; 
  static int jhel; 
  std::complex<double> * * wfs; 
  double t[nprocesses]; 
  // Helicities for the process
  static const int helicities[ncomb][nexternal] = {{-1, -1, -1, -1, -1, -1, -1,
      -1}, {-1, -1, -1, -1, -1, -1, -1, 1}, {-1, -1, -1, -1, -1, -1, 1, -1},
      {-1, -1, -1, -1, -1, -1, 1, 1}, {-1, -1, -1, -1, -1, 1, -1, -1}, {-1, -1,
      -1, -1, -1, 1, -1, 1}, {-1, -1, -1, -1, -1, 1, 1, -1}, {-1, -1, -1, -1,
      -1, 1, 1, 1}, {-1, -1, -1, -1, 1, -1, -1, -1}, {-1, -1, -1, -1, 1, -1,
      -1, 1}, {-1, -1, -1, -1, 1, -1, 1, -1}, {-1, -1, -1, -1, 1, -1, 1, 1},
      {-1, -1, -1, -1, 1, 1, -1, -1}, {-1, -1, -1, -1, 1, 1, -1, 1}, {-1, -1,
      -1, -1, 1, 1, 1, -1}, {-1, -1, -1, -1, 1, 1, 1, 1}, {-1, -1, -1, 1, -1,
      -1, -1, -1}, {-1, -1, -1, 1, -1, -1, -1, 1}, {-1, -1, -1, 1, -1, -1, 1,
      -1}, {-1, -1, -1, 1, -1, -1, 1, 1}, {-1, -1, -1, 1, -1, 1, -1, -1}, {-1,
      -1, -1, 1, -1, 1, -1, 1}, {-1, -1, -1, 1, -1, 1, 1, -1}, {-1, -1, -1, 1,
      -1, 1, 1, 1}, {-1, -1, -1, 1, 1, -1, -1, -1}, {-1, -1, -1, 1, 1, -1, -1,
      1}, {-1, -1, -1, 1, 1, -1, 1, -1}, {-1, -1, -1, 1, 1, -1, 1, 1}, {-1, -1,
      -1, 1, 1, 1, -1, -1}, {-1, -1, -1, 1, 1, 1, -1, 1}, {-1, -1, -1, 1, 1, 1,
      1, -1}, {-1, -1, -1, 1, 1, 1, 1, 1}, {-1, -1, 1, -1, -1, -1, -1, -1},
      {-1, -1, 1, -1, -1, -1, -1, 1}, {-1, -1, 1, -1, -1, -1, 1, -1}, {-1, -1,
      1, -1, -1, -1, 1, 1}, {-1, -1, 1, -1, -1, 1, -1, -1}, {-1, -1, 1, -1, -1,
      1, -1, 1}, {-1, -1, 1, -1, -1, 1, 1, -1}, {-1, -1, 1, -1, -1, 1, 1, 1},
      {-1, -1, 1, -1, 1, -1, -1, -1}, {-1, -1, 1, -1, 1, -1, -1, 1}, {-1, -1,
      1, -1, 1, -1, 1, -1}, {-1, -1, 1, -1, 1, -1, 1, 1}, {-1, -1, 1, -1, 1, 1,
      -1, -1}, {-1, -1, 1, -1, 1, 1, -1, 1}, {-1, -1, 1, -1, 1, 1, 1, -1}, {-1,
      -1, 1, -1, 1, 1, 1, 1}, {-1, -1, 1, 1, -1, -1, -1, -1}, {-1, -1, 1, 1,
      -1, -1, -1, 1}, {-1, -1, 1, 1, -1, -1, 1, -1}, {-1, -1, 1, 1, -1, -1, 1,
      1}, {-1, -1, 1, 1, -1, 1, -1, -1}, {-1, -1, 1, 1, -1, 1, -1, 1}, {-1, -1,
      1, 1, -1, 1, 1, -1}, {-1, -1, 1, 1, -1, 1, 1, 1}, {-1, -1, 1, 1, 1, -1,
      -1, -1}, {-1, -1, 1, 1, 1, -1, -1, 1}, {-1, -1, 1, 1, 1, -1, 1, -1}, {-1,
      -1, 1, 1, 1, -1, 1, 1}, {-1, -1, 1, 1, 1, 1, -1, -1}, {-1, -1, 1, 1, 1,
      1, -1, 1}, {-1, -1, 1, 1, 1, 1, 1, -1}, {-1, -1, 1, 1, 1, 1, 1, 1}, {-1,
      1, -1, -1, -1, -1, -1, -1}, {-1, 1, -1, -1, -1, -1, -1, 1}, {-1, 1, -1,
      -1, -1, -1, 1, -1}, {-1, 1, -1, -1, -1, -1, 1, 1}, {-1, 1, -1, -1, -1, 1,
      -1, -1}, {-1, 1, -1, -1, -1, 1, -1, 1}, {-1, 1, -1, -1, -1, 1, 1, -1},
      {-1, 1, -1, -1, -1, 1, 1, 1}, {-1, 1, -1, -1, 1, -1, -1, -1}, {-1, 1, -1,
      -1, 1, -1, -1, 1}, {-1, 1, -1, -1, 1, -1, 1, -1}, {-1, 1, -1, -1, 1, -1,
      1, 1}, {-1, 1, -1, -1, 1, 1, -1, -1}, {-1, 1, -1, -1, 1, 1, -1, 1}, {-1,
      1, -1, -1, 1, 1, 1, -1}, {-1, 1, -1, -1, 1, 1, 1, 1}, {-1, 1, -1, 1, -1,
      -1, -1, -1}, {-1, 1, -1, 1, -1, -1, -1, 1}, {-1, 1, -1, 1, -1, -1, 1,
      -1}, {-1, 1, -1, 1, -1, -1, 1, 1}, {-1, 1, -1, 1, -1, 1, -1, -1}, {-1, 1,
      -1, 1, -1, 1, -1, 1}, {-1, 1, -1, 1, -1, 1, 1, -1}, {-1, 1, -1, 1, -1, 1,
      1, 1}, {-1, 1, -1, 1, 1, -1, -1, -1}, {-1, 1, -1, 1, 1, -1, -1, 1}, {-1,
      1, -1, 1, 1, -1, 1, -1}, {-1, 1, -1, 1, 1, -1, 1, 1}, {-1, 1, -1, 1, 1,
      1, -1, -1}, {-1, 1, -1, 1, 1, 1, -1, 1}, {-1, 1, -1, 1, 1, 1, 1, -1},
      {-1, 1, -1, 1, 1, 1, 1, 1}, {-1, 1, 1, -1, -1, -1, -1, -1}, {-1, 1, 1,
      -1, -1, -1, -1, 1}, {-1, 1, 1, -1, -1, -1, 1, -1}, {-1, 1, 1, -1, -1, -1,
      1, 1}, {-1, 1, 1, -1, -1, 1, -1, -1}, {-1, 1, 1, -1, -1, 1, -1, 1}, {-1,
      1, 1, -1, -1, 1, 1, -1}, {-1, 1, 1, -1, -1, 1, 1, 1}, {-1, 1, 1, -1, 1,
      -1, -1, -1}, {-1, 1, 1, -1, 1, -1, -1, 1}, {-1, 1, 1, -1, 1, -1, 1, -1},
      {-1, 1, 1, -1, 1, -1, 1, 1}, {-1, 1, 1, -1, 1, 1, -1, -1}, {-1, 1, 1, -1,
      1, 1, -1, 1}, {-1, 1, 1, -1, 1, 1, 1, -1}, {-1, 1, 1, -1, 1, 1, 1, 1},
      {-1, 1, 1, 1, -1, -1, -1, -1}, {-1, 1, 1, 1, -1, -1, -1, 1}, {-1, 1, 1,
      1, -1, -1, 1, -1}, {-1, 1, 1, 1, -1, -1, 1, 1}, {-1, 1, 1, 1, -1, 1, -1,
      -1}, {-1, 1, 1, 1, -1, 1, -1, 1}, {-1, 1, 1, 1, -1, 1, 1, -1}, {-1, 1, 1,
      1, -1, 1, 1, 1}, {-1, 1, 1, 1, 1, -1, -1, -1}, {-1, 1, 1, 1, 1, -1, -1,
      1}, {-1, 1, 1, 1, 1, -1, 1, -1}, {-1, 1, 1, 1, 1, -1, 1, 1}, {-1, 1, 1,
      1, 1, 1, -1, -1}, {-1, 1, 1, 1, 1, 1, -1, 1}, {-1, 1, 1, 1, 1, 1, 1, -1},
      {-1, 1, 1, 1, 1, 1, 1, 1}, {1, -1, -1, -1, -1, -1, -1, -1}, {1, -1, -1,
      -1, -1, -1, -1, 1}, {1, -1, -1, -1, -1, -1, 1, -1}, {1, -1, -1, -1, -1,
      -1, 1, 1}, {1, -1, -1, -1, -1, 1, -1, -1}, {1, -1, -1, -1, -1, 1, -1, 1},
      {1, -1, -1, -1, -1, 1, 1, -1}, {1, -1, -1, -1, -1, 1, 1, 1}, {1, -1, -1,
      -1, 1, -1, -1, -1}, {1, -1, -1, -1, 1, -1, -1, 1}, {1, -1, -1, -1, 1, -1,
      1, -1}, {1, -1, -1, -1, 1, -1, 1, 1}, {1, -1, -1, -1, 1, 1, -1, -1}, {1,
      -1, -1, -1, 1, 1, -1, 1}, {1, -1, -1, -1, 1, 1, 1, -1}, {1, -1, -1, -1,
      1, 1, 1, 1}, {1, -1, -1, 1, -1, -1, -1, -1}, {1, -1, -1, 1, -1, -1, -1,
      1}, {1, -1, -1, 1, -1, -1, 1, -1}, {1, -1, -1, 1, -1, -1, 1, 1}, {1, -1,
      -1, 1, -1, 1, -1, -1}, {1, -1, -1, 1, -1, 1, -1, 1}, {1, -1, -1, 1, -1,
      1, 1, -1}, {1, -1, -1, 1, -1, 1, 1, 1}, {1, -1, -1, 1, 1, -1, -1, -1},
      {1, -1, -1, 1, 1, -1, -1, 1}, {1, -1, -1, 1, 1, -1, 1, -1}, {1, -1, -1,
      1, 1, -1, 1, 1}, {1, -1, -1, 1, 1, 1, -1, -1}, {1, -1, -1, 1, 1, 1, -1,
      1}, {1, -1, -1, 1, 1, 1, 1, -1}, {1, -1, -1, 1, 1, 1, 1, 1}, {1, -1, 1,
      -1, -1, -1, -1, -1}, {1, -1, 1, -1, -1, -1, -1, 1}, {1, -1, 1, -1, -1,
      -1, 1, -1}, {1, -1, 1, -1, -1, -1, 1, 1}, {1, -1, 1, -1, -1, 1, -1, -1},
      {1, -1, 1, -1, -1, 1, -1, 1}, {1, -1, 1, -1, -1, 1, 1, -1}, {1, -1, 1,
      -1, -1, 1, 1, 1}, {1, -1, 1, -1, 1, -1, -1, -1}, {1, -1, 1, -1, 1, -1,
      -1, 1}, {1, -1, 1, -1, 1, -1, 1, -1}, {1, -1, 1, -1, 1, -1, 1, 1}, {1,
      -1, 1, -1, 1, 1, -1, -1}, {1, -1, 1, -1, 1, 1, -1, 1}, {1, -1, 1, -1, 1,
      1, 1, -1}, {1, -1, 1, -1, 1, 1, 1, 1}, {1, -1, 1, 1, -1, -1, -1, -1}, {1,
      -1, 1, 1, -1, -1, -1, 1}, {1, -1, 1, 1, -1, -1, 1, -1}, {1, -1, 1, 1, -1,
      -1, 1, 1}, {1, -1, 1, 1, -1, 1, -1, -1}, {1, -1, 1, 1, -1, 1, -1, 1}, {1,
      -1, 1, 1, -1, 1, 1, -1}, {1, -1, 1, 1, -1, 1, 1, 1}, {1, -1, 1, 1, 1, -1,
      -1, -1}, {1, -1, 1, 1, 1, -1, -1, 1}, {1, -1, 1, 1, 1, -1, 1, -1}, {1,
      -1, 1, 1, 1, -1, 1, 1}, {1, -1, 1, 1, 1, 1, -1, -1}, {1, -1, 1, 1, 1, 1,
      -1, 1}, {1, -1, 1, 1, 1, 1, 1, -1}, {1, -1, 1, 1, 1, 1, 1, 1}, {1, 1, -1,
      -1, -1, -1, -1, -1}, {1, 1, -1, -1, -1, -1, -1, 1}, {1, 1, -1, -1, -1,
      -1, 1, -1}, {1, 1, -1, -1, -1, -1, 1, 1}, {1, 1, -1, -1, -1, 1, -1, -1},
      {1, 1, -1, -1, -1, 1, -1, 1}, {1, 1, -1, -1, -1, 1, 1, -1}, {1, 1, -1,
      -1, -1, 1, 1, 1}, {1, 1, -1, -1, 1, -1, -1, -1}, {1, 1, -1, -1, 1, -1,
      -1, 1}, {1, 1, -1, -1, 1, -1, 1, -1}, {1, 1, -1, -1, 1, -1, 1, 1}, {1, 1,
      -1, -1, 1, 1, -1, -1}, {1, 1, -1, -1, 1, 1, -1, 1}, {1, 1, -1, -1, 1, 1,
      1, -1}, {1, 1, -1, -1, 1, 1, 1, 1}, {1, 1, -1, 1, -1, -1, -1, -1}, {1, 1,
      -1, 1, -1, -1, -1, 1}, {1, 1, -1, 1, -1, -1, 1, -1}, {1, 1, -1, 1, -1,
      -1, 1, 1}, {1, 1, -1, 1, -1, 1, -1, -1}, {1, 1, -1, 1, -1, 1, -1, 1}, {1,
      1, -1, 1, -1, 1, 1, -1}, {1, 1, -1, 1, -1, 1, 1, 1}, {1, 1, -1, 1, 1, -1,
      -1, -1}, {1, 1, -1, 1, 1, -1, -1, 1}, {1, 1, -1, 1, 1, -1, 1, -1}, {1, 1,
      -1, 1, 1, -1, 1, 1}, {1, 1, -1, 1, 1, 1, -1, -1}, {1, 1, -1, 1, 1, 1, -1,
      1}, {1, 1, -1, 1, 1, 1, 1, -1}, {1, 1, -1, 1, 1, 1, 1, 1}, {1, 1, 1, -1,
      -1, -1, -1, -1}, {1, 1, 1, -1, -1, -1, -1, 1}, {1, 1, 1, -1, -1, -1, 1,
      -1}, {1, 1, 1, -1, -1, -1, 1, 1}, {1, 1, 1, -1, -1, 1, -1, -1}, {1, 1, 1,
      -1, -1, 1, -1, 1}, {1, 1, 1, -1, -1, 1, 1, -1}, {1, 1, 1, -1, -1, 1, 1,
      1}, {1, 1, 1, -1, 1, -1, -1, -1}, {1, 1, 1, -1, 1, -1, -1, 1}, {1, 1, 1,
      -1, 1, -1, 1, -1}, {1, 1, 1, -1, 1, -1, 1, 1}, {1, 1, 1, -1, 1, 1, -1,
      -1}, {1, 1, 1, -1, 1, 1, -1, 1}, {1, 1, 1, -1, 1, 1, 1, -1}, {1, 1, 1,
      -1, 1, 1, 1, 1}, {1, 1, 1, 1, -1, -1, -1, -1}, {1, 1, 1, 1, -1, -1, -1,
      1}, {1, 1, 1, 1, -1, -1, 1, -1}, {1, 1, 1, 1, -1, -1, 1, 1}, {1, 1, 1, 1,
      -1, 1, -1, -1}, {1, 1, 1, 1, -1, 1, -1, 1}, {1, 1, 1, 1, -1, 1, 1, -1},
      {1, 1, 1, 1, -1, 1, 1, 1}, {1, 1, 1, 1, 1, -1, -1, -1}, {1, 1, 1, 1, 1,
      -1, -1, 1}, {1, 1, 1, 1, 1, -1, 1, -1}, {1, 1, 1, 1, 1, -1, 1, 1}, {1, 1,
      1, 1, 1, 1, -1, -1}, {1, 1, 1, 1, 1, 1, -1, 1}, {1, 1, 1, 1, 1, 1, 1,
      -1}, {1, 1, 1, 1, 1, 1, 1, 1}};
  // Denominators: spins, colors and identical particles
  const int denominators[nprocesses] = {2048}; 

  ntry = ntry + 1; 

  // Reset the matrix elements
  for(int i = 0; i < nprocesses; i++ )
  {
    matrix_element[i] = 0.; 
  }
  // Define permutation
  int perm[nexternal]; 
  for(int i = 0; i < nexternal; i++ )
  {
    perm[i] = i; 
  }

  if (sum_hel == 0 || ntry < 10)
  {
    // Calculate the matrix element for all helicities
    for(int ihel = 0; ihel < ncomb; ihel++ )
    {
      if (goodhel[ihel] || ntry < 2)
      {
        calculate_wavefunctions(perm, helicities[ihel]); 
        t[0] = matrix_gg_hgg_h_epemepem(); 

        double tsum = 0; 
        for(int iproc = 0; iproc < nprocesses; iproc++ )
        {
          matrix_element[iproc] += t[iproc]; 
          tsum += t[iproc]; 
        }
        // Store which helicities give non-zero result
        if (tsum != 0. && !goodhel[ihel])
        {
          goodhel[ihel] = true; 
          ngood++; 
          igood[ngood] = ihel; 
        }
      }
    }
    jhel = 0; 
    sum_hel = min(sum_hel, ngood); 
  }
  else
  {
    // Only use the "good" helicities
    for(int j = 0; j < sum_hel; j++ )
    {
      jhel++; 
      if (jhel >= ngood)
        jhel = 0; 
      double hwgt = double(ngood)/double(sum_hel); 
      int ihel = igood[jhel]; 
      calculate_wavefunctions(perm, helicities[ihel]); 
      t[0] = matrix_gg_hgg_h_epemepem(); 

      for(int iproc = 0; iproc < nprocesses; iproc++ )
      {
        matrix_element[iproc] += t[iproc] * hwgt; 
      }
    }
  }

  for (int i = 0; i < nprocesses; i++ )
    matrix_element[i] /= denominators[i]; 



}

//--------------------------------------------------------------------------
// Evaluate |M|^2, including incoming flavour dependence.

double CPPProcess_P0_Sigma_heft_gq_Hjj_4l_heft_gg_epemepemgg::sigmaHat() 
{
  // Select between the different processes
  if(id1 == 21 && id2 == 21)
  {
    // Add matrix elements for processes with beams (21, 21)
    return matrix_element[0] * 2; 
  }
  else
  {
    // Return 0 if not correct initial state assignment
    return 0.; 
  }
}

//==========================================================================
// Private class member functions

//--------------------------------------------------------------------------
// Evaluate |M|^2 for each subprocess

void CPPProcess_P0_Sigma_heft_gq_Hjj_4l_heft_gg_epemepemgg::calculate_wavefunctions(const int perm[], const int hel[])
{
  // Calculate wavefunctions for all processes
  int i, j; 

  // Calculate all wavefunctions
  vxxxxx(p[perm[0]], mME[0], hel[0], -1, w[0]); 
  vxxxxx(p[perm[1]], mME[1], hel[1], -1, w[1]); 
  ixxxxx(p[perm[2]], mME[2], hel[2], -1, w[2]); 
  oxxxxx(p[perm[3]], mME[3], hel[3], +1, w[3]); 
  ixxxxx(p[perm[4]], mME[4], hel[4], -1, w[4]); 
  oxxxxx(p[perm[5]], mME[5], hel[5], +1, w[5]); 
  FFV2_4_3(w[2], w[3], pars->GC_40, pars->GC_54, pars->mdl_MZ, pars->mdl_WZ,
      w[6]);
  FFV2_4_3(w[4], w[5], pars->GC_40, pars->GC_54, pars->mdl_MZ, pars->mdl_WZ,
      w[7]);
  VVS2_3(w[6], w[7], pars->GC_73, pars->mdl_MH, pars->mdl_WH, w[8]); 
  vxxxxx(p[perm[6]], mME[6], hel[6], +1, w[9]); 
  vxxxxx(p[perm[7]], mME[7], hel[7], +1, w[10]); 
  FFV2_4_3(w[2], w[5], pars->GC_40, pars->GC_54, pars->mdl_MZ, pars->mdl_WZ,
      w[11]);
  FFV2_4_3(w[4], w[3], pars->GC_40, pars->GC_54, pars->mdl_MZ, pars->mdl_WZ,
      w[12]);
  VVS2_3(w[11], w[12], pars->GC_73, pars->mdl_MH, pars->mdl_WH, w[13]); 
  VVV1P0_1(w[0], w[1], pars->GC_10, pars->ZERO, pars->ZERO, w[14]); 
  VVS3P0_1(w[9], w[8], pars->GC_13, pars->ZERO, pars->ZERO, w[15]); 
  VVS3P0_1(w[9], w[13], pars->GC_13, pars->ZERO, pars->ZERO, w[16]); 
  VVS3P0_1(w[10], w[8], pars->GC_13, pars->ZERO, pars->ZERO, w[17]); 
  VVS3P0_1(w[10], w[13], pars->GC_13, pars->ZERO, pars->ZERO, w[18]); 
  VVV1P0_1(w[9], w[10], pars->GC_10, pars->ZERO, pars->ZERO, w[19]); 
  VVS3P0_1(w[0], w[8], pars->GC_13, pars->ZERO, pars->ZERO, w[20]); 
  VVV1P0_1(w[1], w[9], pars->GC_10, pars->ZERO, pars->ZERO, w[21]); 
  VVS3P0_1(w[0], w[13], pars->GC_13, pars->ZERO, pars->ZERO, w[22]); 
  VVV1P0_1(w[1], w[10], pars->GC_10, pars->ZERO, pars->ZERO, w[23]); 
  VVV1P0_1(w[0], w[9], pars->GC_10, pars->ZERO, pars->ZERO, w[24]); 
  VVS3P0_1(w[1], w[8], pars->GC_13, pars->ZERO, pars->ZERO, w[25]); 
  VVS3P0_1(w[1], w[13], pars->GC_13, pars->ZERO, pars->ZERO, w[26]); 
  VVV1P0_1(w[0], w[10], pars->GC_10, pars->ZERO, pars->ZERO, w[27]); 
  VVVS2P0_1(w[0], w[1], w[8], pars->GC_14, pars->ZERO, pars->ZERO, w[28]); 
  VVVS2P0_1(w[0], w[1], w[13], pars->GC_14, pars->ZERO, pars->ZERO, w[29]); 
  VVVV1P0_1(w[0], w[1], w[9], pars->GC_12, pars->ZERO, pars->ZERO, w[30]); 
  VVVV3P0_1(w[0], w[1], w[9], pars->GC_12, pars->ZERO, pars->ZERO, w[31]); 
  VVVV4P0_1(w[0], w[1], w[9], pars->GC_12, pars->ZERO, pars->ZERO, w[32]); 
  VVVV1P0_1(w[0], w[1], w[10], pars->GC_12, pars->ZERO, pars->ZERO, w[33]); 
  VVVV3P0_1(w[0], w[1], w[10], pars->GC_12, pars->ZERO, pars->ZERO, w[34]); 
  VVVV4P0_1(w[0], w[1], w[10], pars->GC_12, pars->ZERO, pars->ZERO, w[35]); 
  VVVS2P0_1(w[0], w[9], w[8], pars->GC_14, pars->ZERO, pars->ZERO, w[36]); 
  VVVS2P0_1(w[0], w[9], w[13], pars->GC_14, pars->ZERO, pars->ZERO, w[37]); 
  VVVS2P0_1(w[0], w[10], w[8], pars->GC_14, pars->ZERO, pars->ZERO, w[38]); 
  VVVS2P0_1(w[0], w[10], w[13], pars->GC_14, pars->ZERO, pars->ZERO, w[39]); 
  VVVV1P0_1(w[0], w[9], w[10], pars->GC_12, pars->ZERO, pars->ZERO, w[40]); 
  VVVV3P0_1(w[0], w[9], w[10], pars->GC_12, pars->ZERO, pars->ZERO, w[41]); 
  VVVV4P0_1(w[0], w[9], w[10], pars->GC_12, pars->ZERO, pars->ZERO, w[42]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  VVVVS1_0(w[0], w[1], w[9], w[10], w[8], pars->GC_15, amp[0]); 
  VVVVS2_0(w[0], w[1], w[9], w[10], w[8], pars->GC_15, amp[1]); 
  VVVVS3_0(w[0], w[1], w[9], w[10], w[8], pars->GC_15, amp[2]); 
  VVVVS1_0(w[0], w[1], w[9], w[10], w[13], pars->GC_15, amp[3]); 
  VVVVS2_0(w[0], w[1], w[9], w[10], w[13], pars->GC_15, amp[4]); 
  VVVVS3_0(w[0], w[1], w[9], w[10], w[13], pars->GC_15, amp[5]); 
  VVV1_0(w[14], w[15], w[10], pars->GC_10, amp[6]); 
  VVV1_0(w[14], w[16], w[10], pars->GC_10, amp[7]); 
  VVV1_0(w[14], w[17], w[9], pars->GC_10, amp[8]); 
  VVV1_0(w[14], w[18], w[9], pars->GC_10, amp[9]); 
  VVS3_0(w[14], w[19], w[8], pars->GC_13, amp[10]); 
  VVS3_0(w[14], w[19], w[13], pars->GC_13, amp[11]); 
  VVVS2_0(w[9], w[10], w[14], w[8], pars->GC_14, amp[12]); 
  VVVS2_0(w[9], w[10], w[14], w[13], pars->GC_14, amp[13]); 
  VVV1_0(w[20], w[21], w[10], pars->GC_10, amp[14]); 
  VVV1_0(w[22], w[21], w[10], pars->GC_10, amp[15]); 
  VVV1_0(w[20], w[23], w[9], pars->GC_10, amp[16]); 
  VVV1_0(w[22], w[23], w[9], pars->GC_10, amp[17]); 
  VVV1_0(w[20], w[1], w[19], pars->GC_10, amp[18]); 
  VVV1_0(w[22], w[1], w[19], pars->GC_10, amp[19]); 
  VVVV1_0(w[1], w[9], w[10], w[20], pars->GC_12, amp[20]); 
  VVVV3_0(w[1], w[9], w[10], w[20], pars->GC_12, amp[21]); 
  VVVV4_0(w[1], w[9], w[10], w[20], pars->GC_12, amp[22]); 
  VVVV1_0(w[1], w[9], w[10], w[22], pars->GC_12, amp[23]); 
  VVVV3_0(w[1], w[9], w[10], w[22], pars->GC_12, amp[24]); 
  VVVV4_0(w[1], w[9], w[10], w[22], pars->GC_12, amp[25]); 
  VVV1_0(w[24], w[25], w[10], pars->GC_10, amp[26]); 
  VVV1_0(w[24], w[26], w[10], pars->GC_10, amp[27]); 
  VVS3_0(w[24], w[23], w[8], pars->GC_13, amp[28]); 
  VVS3_0(w[24], w[23], w[13], pars->GC_13, amp[29]); 
  VVV1_0(w[24], w[1], w[17], pars->GC_10, amp[30]); 
  VVV1_0(w[24], w[1], w[18], pars->GC_10, amp[31]); 
  VVVS2_0(w[1], w[10], w[24], w[8], pars->GC_14, amp[32]); 
  VVVS2_0(w[1], w[10], w[24], w[13], pars->GC_14, amp[33]); 
  VVV1_0(w[27], w[25], w[9], pars->GC_10, amp[34]); 
  VVV1_0(w[27], w[26], w[9], pars->GC_10, amp[35]); 
  VVS3_0(w[27], w[21], w[8], pars->GC_13, amp[36]); 
  VVS3_0(w[27], w[21], w[13], pars->GC_13, amp[37]); 
  VVV1_0(w[27], w[1], w[15], pars->GC_10, amp[38]); 
  VVV1_0(w[27], w[1], w[16], pars->GC_10, amp[39]); 
  VVVS2_0(w[1], w[9], w[27], w[8], pars->GC_14, amp[40]); 
  VVVS2_0(w[1], w[9], w[27], w[13], pars->GC_14, amp[41]); 
  VVV1_0(w[0], w[25], w[19], pars->GC_10, amp[42]); 
  VVV1_0(w[0], w[26], w[19], pars->GC_10, amp[43]); 
  VVV1_0(w[0], w[21], w[17], pars->GC_10, amp[44]); 
  VVV1_0(w[0], w[21], w[18], pars->GC_10, amp[45]); 
  VVV1_0(w[0], w[23], w[15], pars->GC_10, amp[46]); 
  VVV1_0(w[0], w[23], w[16], pars->GC_10, amp[47]); 
  VVV1_0(w[9], w[10], w[28], pars->GC_10, amp[48]); 
  VVV1_0(w[9], w[10], w[29], pars->GC_10, amp[49]); 
  VVS3_0(w[10], w[30], w[8], pars->GC_13, amp[50]); 
  VVS3_0(w[10], w[31], w[8], pars->GC_13, amp[51]); 
  VVS3_0(w[10], w[32], w[8], pars->GC_13, amp[52]); 
  VVS3_0(w[10], w[30], w[13], pars->GC_13, amp[53]); 
  VVS3_0(w[10], w[31], w[13], pars->GC_13, amp[54]); 
  VVS3_0(w[10], w[32], w[13], pars->GC_13, amp[55]); 
  VVS3_0(w[9], w[33], w[8], pars->GC_13, amp[56]); 
  VVS3_0(w[9], w[34], w[8], pars->GC_13, amp[57]); 
  VVS3_0(w[9], w[35], w[8], pars->GC_13, amp[58]); 
  VVS3_0(w[9], w[33], w[13], pars->GC_13, amp[59]); 
  VVS3_0(w[9], w[34], w[13], pars->GC_13, amp[60]); 
  VVS3_0(w[9], w[35], w[13], pars->GC_13, amp[61]); 
  VVV1_0(w[1], w[10], w[36], pars->GC_10, amp[62]); 
  VVV1_0(w[1], w[10], w[37], pars->GC_10, amp[63]); 
  VVV1_0(w[1], w[9], w[38], pars->GC_10, amp[64]); 
  VVV1_0(w[1], w[9], w[39], pars->GC_10, amp[65]); 
  VVS3_0(w[1], w[40], w[8], pars->GC_13, amp[66]); 
  VVS3_0(w[1], w[41], w[8], pars->GC_13, amp[67]); 
  VVS3_0(w[1], w[42], w[8], pars->GC_13, amp[68]); 
  VVS3_0(w[1], w[40], w[13], pars->GC_13, amp[69]); 
  VVS3_0(w[1], w[41], w[13], pars->GC_13, amp[70]); 
  VVS3_0(w[1], w[42], w[13], pars->GC_13, amp[71]); 

}
double CPPProcess_P0_Sigma_heft_gq_Hjj_4l_heft_gg_epemepemgg::matrix_gg_hgg_h_epemepem() 
{
  int i, j; 
  // Local variables
  const int ngraphs = 72; 
  const int ncolor = 6; 
  std::complex<double> ztemp; 
  std::complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {6, 6, 6, 6, 6, 6}; 
  static const double cf[ncolor][ncolor] = {{19, -2, -2, -2, -2, 4}, {-2, 19,
      -2, 4, -2, -2}, {-2, -2, 19, -2, 4, -2}, {-2, 4, -2, 19, -2, -2}, {-2,
      -2, 4, -2, 19, -2}, {4, -2, -2, -2, -2, 19}};

  // Calculate color flows
  jamp[0] = +2. * (+amp[2] - amp[0] - amp[5] + amp[3] - amp[6] + amp[7] +
      amp[8] - amp[9] - amp[10] + amp[11] - amp[12] + amp[13] - amp[14] +
      amp[15] - amp[18] + amp[19] + amp[22] - amp[20] - amp[25] + amp[23] +
      amp[34] - amp[35] + amp[36] - amp[37] + amp[38] - amp[39] + amp[40] -
      amp[41] - amp[42] + amp[43] - amp[44] + amp[45] - amp[48] + amp[49] +
      amp[52] - amp[50] - amp[55] + amp[53] - amp[58] - amp[57] + amp[61] +
      amp[60] + amp[64] - amp[65] + amp[66] + amp[67] - amp[69] - amp[70]);
  jamp[1] = +2. * (+amp[1] + amp[0] - amp[4] - amp[3] + amp[6] - amp[7] -
      amp[8] + amp[9] + amp[10] - amp[11] + amp[12] - amp[13] - amp[16] +
      amp[17] + amp[18] - amp[19] - amp[22] - amp[21] + amp[25] + amp[24] +
      amp[26] - amp[27] + amp[28] - amp[29] + amp[30] - amp[31] + amp[32] -
      amp[33] + amp[42] - amp[43] - amp[46] + amp[47] + amp[48] - amp[49] -
      amp[52] - amp[51] + amp[55] + amp[54] + amp[58] - amp[56] - amp[61] +
      amp[59] + amp[62] - amp[63] + amp[68] - amp[66] - amp[71] + amp[69]);
  jamp[2] = +2. * (-amp[2] - amp[1] + amp[5] + amp[4] + amp[14] - amp[15] +
      amp[16] - amp[17] + amp[21] + amp[20] - amp[24] - amp[23] - amp[26] +
      amp[27] - amp[28] + amp[29] - amp[30] + amp[31] - amp[32] + amp[33] -
      amp[34] + amp[35] - amp[36] + amp[37] - amp[38] + amp[39] - amp[40] +
      amp[41] + amp[44] - amp[45] + amp[46] - amp[47] + amp[50] + amp[51] -
      amp[53] - amp[54] + amp[56] + amp[57] - amp[59] - amp[60] - amp[62] +
      amp[63] - amp[64] + amp[65] - amp[68] - amp[67] + amp[71] + amp[70]);
  jamp[3] = +2. * (+amp[1] + amp[0] - amp[4] - amp[3] + amp[6] - amp[7] -
      amp[8] + amp[9] + amp[10] - amp[11] + amp[12] - amp[13] - amp[16] +
      amp[17] + amp[18] - amp[19] - amp[22] - amp[21] + amp[25] + amp[24] +
      amp[26] - amp[27] + amp[28] - amp[29] + amp[30] - amp[31] + amp[32] -
      amp[33] + amp[42] - amp[43] - amp[46] + amp[47] + amp[48] - amp[49] -
      amp[52] - amp[51] + amp[55] + amp[54] + amp[58] - amp[56] - amp[61] +
      amp[59] + amp[62] - amp[63] + amp[68] - amp[66] - amp[71] + amp[69]);
  jamp[4] = +2. * (-amp[2] - amp[1] + amp[5] + amp[4] + amp[14] - amp[15] +
      amp[16] - amp[17] + amp[21] + amp[20] - amp[24] - amp[23] - amp[26] +
      amp[27] - amp[28] + amp[29] - amp[30] + amp[31] - amp[32] + amp[33] -
      amp[34] + amp[35] - amp[36] + amp[37] - amp[38] + amp[39] - amp[40] +
      amp[41] + amp[44] - amp[45] + amp[46] - amp[47] + amp[50] + amp[51] -
      amp[53] - amp[54] + amp[56] + amp[57] - amp[59] - amp[60] - amp[62] +
      amp[63] - amp[64] + amp[65] - amp[68] - amp[67] + amp[71] + amp[70]);
  jamp[5] = +2. * (+amp[2] - amp[0] - amp[5] + amp[3] - amp[6] + amp[7] +
      amp[8] - amp[9] - amp[10] + amp[11] - amp[12] + amp[13] - amp[14] +
      amp[15] - amp[18] + amp[19] + amp[22] - amp[20] - amp[25] + amp[23] +
      amp[34] - amp[35] + amp[36] - amp[37] + amp[38] - amp[39] + amp[40] -
      amp[41] - amp[42] + amp[43] - amp[44] + amp[45] - amp[48] + amp[49] +
      amp[52] - amp[50] - amp[55] + amp[53] - amp[58] - amp[57] + amp[61] +
      amp[60] + amp[64] - amp[65] + amp[66] + amp[67] - amp[69] - amp[70]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[0][i] += real(jamp[i] * conj(jamp[i])); 

  return matrix; 
}



