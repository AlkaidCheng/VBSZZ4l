//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph5_aMC@NLO v. 2.2.1, 2014-09-25
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================
// This code is adjusted to handle some features. For more info, see README.
// Contact: K. Potamianos <karolos.potamianos@cern.ch>
//==========================================================================

#ifndef MG5_Sigma_heft_uxcx_epemmupmumuxcx_H
#define MG5_Sigma_heft_uxcx_epemmupmumuxcx_H

#include <complex> 
#include <vector> 

#include "Parameters_heft.h"

using namespace std; 

//==========================================================================
// A class for calculating the matrix elements for
// Process: u~ c~ > h u~ c~ WEIGHTED=4 HIG=1 HIW=1
// *   Decay: h > e+ e- mu+ mu- WEIGHTED=6 HIW=1 HIG=1
// Process: u~ d~ > h u~ d~ WEIGHTED=4 HIG=1 HIW=1
// *   Decay: h > e+ e- mu+ mu- WEIGHTED=6 HIW=1 HIG=1
// Process: u~ s~ > h u~ s~ WEIGHTED=4 HIG=1 HIW=1
// *   Decay: h > e+ e- mu+ mu- WEIGHTED=6 HIW=1 HIG=1
// Process: c~ d~ > h c~ d~ WEIGHTED=4 HIG=1 HIW=1
// *   Decay: h > e+ e- mu+ mu- WEIGHTED=6 HIW=1 HIG=1
// Process: c~ s~ > h c~ s~ WEIGHTED=4 HIG=1 HIW=1
// *   Decay: h > e+ e- mu+ mu- WEIGHTED=6 HIW=1 HIG=1
// Process: d~ s~ > h d~ s~ WEIGHTED=4 HIG=1 HIW=1
// *   Decay: h > e+ e- mu+ mu- WEIGHTED=6 HIW=1 HIG=1
//--------------------------------------------------------------------------

class CPPProcess_P0_Sigma_heft_pp_Hjj_4l_heft_uxcx_epemmupmumuxcx
{
  public:

    // Constructor.
    CPPProcess_P0_Sigma_heft_pp_Hjj_4l_heft_uxcx_epemmupmumuxcx() {}

    // Destructor.
    virtual ~CPPProcess_P0_Sigma_heft_pp_Hjj_4l_heft_uxcx_epemmupmumuxcx() {}

    // Initialize process.
    virtual void initProc(string param_card_name); 

    // Set M4l Mass
    void setM4l(double m_m4l);

    // Calculate flavour-independent parts of cross section.
    virtual void sigmaKin(); 

    // Evaluate sigmaHat(sHat).
    virtual double sigmaHat(); 

    // Info on the subprocess.
    virtual string name() const {return "u~ c~ > e+ e- mu+ mu- u~ c~ (heft)";}

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
    static const int nwavefuncs = 16; 
    std::complex<double> w[nwavefuncs][18]; 
    static const int namplitudes = 2; 
    std::complex<double> amp[namplitudes]; 
    double matrix_uxcx_huxcx_h_epemmupmum(); 

    // Store the matrix element value from sigmaKin
    double matrix_element[nprocesses]; 

    // Color flows, used when selecting color
    double * jamp2[nprocesses]; 

    // Pointer to the model parameters
    Parameters_heft * pars; 

    // vector with external particle masses
    vector<double> mME; 

    // vector with momenta (to be changed each event)
    vector < double * > p; 
    // Initial particle ids
    int id1, id2; 

}; 


#endif  // MG5_Sigma_heft_uxcx_epemmupmumuxcx_H
