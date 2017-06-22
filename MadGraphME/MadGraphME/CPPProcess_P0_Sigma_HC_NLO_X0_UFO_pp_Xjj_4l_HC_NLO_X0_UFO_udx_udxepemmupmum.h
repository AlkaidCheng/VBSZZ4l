//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph5_aMC@NLO v. 2.2.1, 2014-09-25
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================
// This code is adjusted to handle some features. For more info, see README.
// Contact: K. Potamianos <karolos.potamianos@cern.ch>
//==========================================================================

#ifndef MG5_Sigma_HC_NLO_X0_UFO_udx_udxepemmupmum_H
#define MG5_Sigma_HC_NLO_X0_UFO_udx_udxepemmupmum_H

#include <complex> 
#include <vector> 

#include "Parameters_HC_NLO_X0_UFO.h"

using namespace std; 

//==========================================================================
// A class for calculating the matrix elements for
// Process: u d~ > u d~ x0 WEIGHTED=6 QNP=1 $$ w+ w- z / a
// *   Decay: x0 > z > e+ e- mu+ mu- WEIGHTED=6 QNP=1
// Process: u s~ > u s~ x0 WEIGHTED=6 QNP=1 $$ w+ w- z / a
// *   Decay: x0 > z > e+ e- mu+ mu- WEIGHTED=6 QNP=1
// Process: c d~ > c d~ x0 WEIGHTED=6 QNP=1 $$ w+ w- z / a
// *   Decay: x0 > z > e+ e- mu+ mu- WEIGHTED=6 QNP=1
// Process: c s~ > c s~ x0 WEIGHTED=6 QNP=1 $$ w+ w- z / a
// *   Decay: x0 > z > e+ e- mu+ mu- WEIGHTED=6 QNP=1
//--------------------------------------------------------------------------

class CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_udx_udxepemmupmum
{
  public:

    // Constructor.
    CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_udx_udxepemmupmum() {}

    // Destructor.
    virtual ~CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_udx_udxepemmupmum() {}

    // Initialize process.
    virtual void initProc(string param_card_name); 

    // Set M4l Mass
    void setM4l(double m_m4l);

    // Calculate flavour-independent parts of cross section.
    virtual void sigmaKin(); 

    // Evaluate sigmaHat(sHat).
    virtual double sigmaHat(); 

    // Info on the subprocess.
    virtual string name() const {return "u d~ > u d~ e+ e- mu+ mu- (HC_NLO_X0_UFO)";}

    virtual int code() const {return 0;}

    const vector<double> & getMasses() const {return mME;}

    // Get and set momenta for matrix element evaluation
    vector < double * > getMomenta(){return p;}
    void setMomenta(vector < double * > & momenta){p = momenta;}
    void setInitial(int inid1, int inid2){id1 = inid1; id2 = inid2;}

    // Get matrix element vector
    const double * getMatrixElements() const {return matrix_element;}

    // Constants for array limits
    static const int ninitial = 2; 
    static const int nexternal = 8; 
    static const int nprocesses = 2; 

  private:

    // Private functions to calculate the matrix element for all subprocesses
    // Calculate wavefunctions
    void calculate_wavefunctions(const int perm[], const int hel[]); 
    static const int nwavefuncs = 17; 
    std::complex<double> w[nwavefuncs][18]; 
    static const int namplitudes = 3; 
    std::complex<double> amp[namplitudes]; 
    double matrix_udx_udxxno_a_xz_epemmupmum(); 

    // Store the matrix element value from sigmaKin
    double matrix_element[nprocesses]; 

    // Color flows, used when selecting color
    double * jamp2[nprocesses]; 

    // Pointer to the model parameters
    Parameters_HC_NLO_X0_UFO * pars; 

    // vector with external particle masses
    vector<double> mME; 

    // vector with momenta (to be changed each event)
    vector < double * > p; 
    // Initial particle ids
    int id1, id2; 

}; 


#endif  // MG5_Sigma_HC_NLO_X0_UFO_udx_udxepemmupmum_H
