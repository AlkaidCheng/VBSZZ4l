// March 28 2011
// S. Jindariani (sergo@fnal.gov)
// Y. Gao (Yanyan.Gao@cern.ch)
// K. Burkett (burkett@fnal.gov)


#ifndef ZZ_COMMON
#define ZZ_COMMON
#include <TLorentzVector.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <vector>
#include <TFile.h>
#include <TF1.h>
#include "MCFM_MatrixElement/TVar.h"
#include "MCFM_MatrixElement/TMCFM.h"
using namespace std;
TString DbnEventLepSelName(int i);
void My_choose(TVar::Process process, const TVar::LeptonInterference& leptonInterf, bool hasZZ4fInterf=false);
void SetEwkCoupligParameters();
void SetAlphaS(double Q, int mynloop, int mynflav, string mypartons);
bool My_smalls(double s[][mxpart], int npart);
double SumMatrixElementPDF(TVar::Process procees, mcfm_event_type* mcfm_event,double flavor_msq[][11],double* flux, bool fixedScale=true);
double SumMEPDF(const TLorentzVector p0, const TLorentzVector p1, double flavor_msq[nmsq][nmsq],  TVar::VerbosityLevel verbosity);

#endif
