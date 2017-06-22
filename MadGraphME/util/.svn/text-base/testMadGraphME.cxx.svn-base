
#include "CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemepem.h"
#include "CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemmupmum.h"
#include "CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemepem.h"
#include "CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemmupmum.h"
#include "CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemepem.h"
#include "CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemmupmum.h"

#include "CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_uux_epemepemuux.h"
#include "CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ddx_epemepemuux.h"

#include "CPPProcess_P0_Sigma_heft_pp_Hjj_4l_heft_gu_epemmupmumgu.h"
#include "CPPProcess_P0_Sigma_heft_gq_Hjj_4l_heft_gu_epemmupmumgu.h"

#include "CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_uu_uuepemmupmum.h"
#include "CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_uc_ucepemmupmum.h"
#include "CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemmupmum.h"

#include "MadGraphME/ComputeMGME.h"

#include "TRandom2.h"

#include <iostream>
#include <memory>

class TestHelperBase {
public:
  virtual void testMe() = 0;

  template <typename T>
  static std::shared_ptr<TestHelperBase> build(std::string pCard);
};

template <typename T>
class TestHelper: public TestHelperBase {
public:
  TestHelper(T&& s, std::string pCard);
  void testMe();
  void setMomenta();
private:
  T m_S;
  std::string m_paramCard;

  TLorentzVector m_cms, m_cms4l;
  std::vector<TLorentzVector> m_fermions;
};

template <typename T>
TestHelper<T>::TestHelper(T&& s, std::string pCard):
  m_S(s), m_paramCard(pCard) {
    m_S.initProc(m_paramCard.c_str()); // This can throw an exception
    setMomenta();
}

template <typename T>
void TestHelper<T>::setMomenta() {

  if( (m_S.nexternal - m_S.ninitial) < 4 )
    std::cerr << "ERROR: the process is not compatible with our test!" << std::endl;
  m_fermions.clear();
  m_fermions.resize(m_S.nexternal - m_S.ninitial);
  // Input should be in GeV !!!!
  // Define MGME_USE_MEV if you need MeV!
  // ComputeMGME_cmsM4l is just a wrapper around the MadGraph ME. 
  // In particular, the ordering of m_fermions must correspond to the process:
  // e.g. in MadGraphME/inc/CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ddx_epemepemuux.h
  // which is produced after building the MadGraph MEs.

#define USE_RANDOM_VALUES
#ifdef USE_RANDOM_VALUES
  TRandom2 rnd;
  for(int i = 0 ; i < 4 ; ++i)
    m_fermions[i].SetPtEtaPhiM( rnd.Uniform(10.,200.), rnd.Uniform(-2.5,2.5), rnd.Uniform(0, 6.2831853072), 106. );
  if( (m_S.nexternal - m_S.ninitial) == 6 ) {
    for(int i = 4 ; i < 6 ; ++i)
      m_fermions[i].SetPtEtaPhiM( rnd.Uniform(30.,200), rnd.Uniform(-2.5,2.5), rnd.Uniform(0, 6.2831853072), 2.3 );
  }
#else
  m_fermions[0].SetPtEtaPhiM( 35., 1.10, 1.234, 106. );
  m_fermions[1].SetPtEtaPhiM( 38., -1.0, 1.500, 106. );
  m_fermions[2].SetPtEtaPhiM( 10., 1.10, 1.234, 106. );
  m_fermions[3].SetPtEtaPhiM( 10., -1.8, 1.234, 106. );
  if( (m_S.nexternal - m_S.ninitial) == 6 ) {
    m_fermions[4].SetPtEtaPhiM( 20., 0.9, 1.104, 2.3 );
    m_fermions[5].SetPtEtaPhiM( 20., -1.18, 1.104, 2.3 );
  }
#endif
  for(unsigned i = 0 ; i < m_fermions.size() ; ++i) {
    m_cms += m_fermions[i];
    if( i < 4 ) m_cms4l += m_fermions[i];
  }
  for(unsigned i = 0 ; i < m_fermions.size() ; ++i)
    m_fermions[i].Boost( -( m_cms.BoostVector() ) );

  std::cout << std::string(80,'-') << endl;
  std::cout << " Momenta:\t" << "Pt\tEta\tPhi\tMass" << endl;

  double (TLorentzVector::*fPtr[])() const =  { &TLorentzVector::E, &TLorentzVector::Px, &TLorentzVector::Py, &TLorentzVector::Pz };
  for(unsigned i = 0 ; i < m_fermions.size() ; ++i) {
    for(int j = 0 ; j < 4 ; ++j)
      std::cout << "\t" << (m_fermions[i].*fPtr[j])();
    std::cout << std::endl;
  }

  std::cout << std::string(80,'-') << endl;

}

template <typename T>
void TestHelper<T>::testMe() {

  std::cout << "Param card: " << m_paramCard << std::endl;
  std::cout << std::string(80,'-') << endl;

  // Will use the event's CMS as MH value
  std::vector<float> mtxElem = ComputeMGME_cmsM4l(m_S, m_fermions, m_cms, m_cms4l);

  // Display matrix elements
  for(int i=0; i<m_S.nprocesses;i++) {
    std::cout << " Matrix element = "
      << setiosflags(ios::fixed) << setprecision(17)
      << mtxElem[i]
      << " GeV^" << -(2*m_S.nexternal-8) << endl;
    std::cout << " Log = " << log( mtxElem[0] ) << std::endl;
  }

  std::cout << std::string(80,'-') << endl;

}


template <typename T>
std::shared_ptr<TestHelperBase> TestHelperBase::build(std::string pCard) {
    std::shared_ptr<TestHelperBase> sharedPtr = std::make_shared<TestHelper<T>>(T(), pCard);
    return sharedPtr;
}

int main (int argc, const char** argv) {
  argc = argc;
  argv = argv;

  std::vector<std::shared_ptr<TestHelperBase>> testHelpers;

  // Loading proper parameter card
  const char* param_card = "Cards/param_card_PROC_SA_CPP_heft_pp_H_ZZ_4l.dat";

  try {
    param_card = "Cards/param_card_PROC_SA_CPP_heft_pp_H_ZZ_4l.dat";
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemepem>(param_card) );
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemmupmum>(param_card) );

    param_card = "Cards/param_card_PROC_SA_CPP_sm_pp_4l.dat";
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemepem>(param_card) );
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_sm_pp_4l_sm_ddx_epemmupmum>(param_card) );
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemepem>(param_card) );
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_sm_pp_4l_sm_uux_epemmupmum>(param_card) );


    // Adding test for VBF processes
    param_card = "Cards/param_card_PROC_SA_CPP_sm_hVBF_ZZ_4l.dat";
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_uux_epemepemuux>(param_card) );
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ddx_epemepemuux>(param_card) );

    param_card = "Cards/param_card_PROC_SA_CPP_heft_pp_Hjj_4l.dat";
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_heft_pp_Hjj_4l_heft_gu_epemmupmumgu>(param_card) );

    param_card = "Cards/param_card_PROC_SA_CPP_heft_gq_Hjj_4l.dat";
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_heft_gq_Hjj_4l_heft_gu_epemmupmumgu>(param_card) );

    param_card = "Cards/param_card_PROC_SA_CPP_HC_NLO_X0_UFO_kAvv_1.dat";
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_uu_uuepemmupmum>(param_card) );
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_uc_ucepemmupmum>(param_card) );
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemmupmum>(param_card) );

    param_card = "Cards/param_card_PROC_SA_CPP_HC_NLO_X0_UFO_kHvv_1.dat";
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_uu_uuepemmupmum>(param_card) );
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_uc_ucepemmupmum>(param_card) );
    testHelpers.push_back( TestHelperBase::build<CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemmupmum>(param_card) );


  } catch (const char* e) {
    std::cout << "Exception: " << e << ". Parameter card: " << param_card << std::endl; 
    return 1;
  }
  for(auto tH : testHelpers) {
    tH->testMe();
  }

#if 0
  std::vector<float> mtxElem_pp_4l_SF = ComputeMGME(S_sm_pp_4l_uu_SF, fermions, cms);

  // Display matrix elements
  for(int i=0; i<S_sm_pp_4l_uu_SF.nprocesses;i++)
    std::cout << " Matrix element = "
      << setiosflags(ios::fixed) << setprecision(17)
      << mtxElem_pp_4l_SF[i]
      << " GeV^" << -(2*S_sm_pp_4l_uu_SF.nexternal-8) << endl;

  std::cout << std::string(80,'-') << endl;

  float KD = log(mtxElem_hVBF_uu4l_SF[0]/(mtxElem_pp_4l_SF[0]+mtxElem_pp_4l_SF[1]));
  std::cout << "KD=" << KD << std::endl;
#endif
  return 0;
}
