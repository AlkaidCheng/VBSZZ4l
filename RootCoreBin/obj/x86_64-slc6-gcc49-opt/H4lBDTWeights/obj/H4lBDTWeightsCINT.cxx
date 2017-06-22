#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#ifdef __llvm__
#pragma GCC diagnostic ignored "-Wunused-private-field"
#endif
// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIafsdIcerndOchdIworkdImdImmittaldIprivatedIMyAnalysisCodedIRootCoreBindIobjdIx86_64mIslc6mIgcc49mIoptdIH4lBDTWeightsdIobjdIH4lBDTWeightsCINT

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "H4lBDTWeights/H4lBDTWeights.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *H4lBDTWeights_Dictionary();
   static void H4lBDTWeights_TClassManip(TClass*);
   static void delete_H4lBDTWeights(void *p);
   static void deleteArray_H4lBDTWeights(void *p);
   static void destruct_H4lBDTWeights(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::H4lBDTWeights*)
   {
      ::H4lBDTWeights *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::H4lBDTWeights));
      static ::ROOT::TGenericClassInfo 
         instance("H4lBDTWeights", "H4lBDTWeights/H4lBDTWeights.h", 37,
                  typeid(::H4lBDTWeights), DefineBehavior(ptr, ptr),
                  &H4lBDTWeights_Dictionary, isa_proxy, 4,
                  sizeof(::H4lBDTWeights) );
      instance.SetDelete(&delete_H4lBDTWeights);
      instance.SetDeleteArray(&deleteArray_H4lBDTWeights);
      instance.SetDestructor(&destruct_H4lBDTWeights);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::H4lBDTWeights*)
   {
      return GenerateInitInstanceLocal((::H4lBDTWeights*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::H4lBDTWeights*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *H4lBDTWeights_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::H4lBDTWeights*)0x0)->GetClass();
      H4lBDTWeights_TClassManip(theClass);
   return theClass;
   }

   static void H4lBDTWeights_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_H4lBDTWeights(void *p) {
      delete ((::H4lBDTWeights*)p);
   }
   static void deleteArray_H4lBDTWeights(void *p) {
      delete [] ((::H4lBDTWeights*)p);
   }
   static void destruct_H4lBDTWeights(void *p) {
      typedef ::H4lBDTWeights current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::H4lBDTWeights

namespace {
  void TriggerDictionaryInitialization_H4lBDTWeightsCINT_Impl() {
    static const char* headers[] = {
"H4lBDTWeights/H4lBDTWeights.h",
0
    };
    static const char* includePaths[] = {
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/H4lBDTWeights/Root",
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/H4lBDTWeights",
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.16-x86_64-slc6-gcc49-opt/include",
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/RootCoreBin/include",
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.16-x86_64-slc6-gcc49-opt/include",
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.16-x86_64-slc6-gcc49-opt/include",
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/H4lBDTWeights/cmt/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/H4lBDTWeights/Root/LinkDef.h")))  H4lBDTWeights;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef ROOTCORE
  #define ROOTCORE 1
#endif
#ifndef ROOTCORE_RELEASE_SERIES
  #define ROOTCORE_RELEASE_SERIES 24
#endif
#ifndef ROOTCORE_TEST_FILE
  #define ROOTCORE_TEST_FILE "/afs/cern.ch/user/a/asgbase/patspace/xAODs/r7725/mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2608_s2183_r7725_r7676/AOD.07915862._000100.pool.root.1"
#endif
#ifndef ROOTCORE_TEST_DATA
  #define ROOTCORE_TEST_DATA "/afs/cern.ch/user/a/asgbase/patspace/xAODs/r7725"
#endif
#ifndef ASG_TEST_FILE_DATA
  #define ASG_TEST_FILE_DATA "/afs/cern.ch/user/a/asgbase/patspace/xAODs/r7562/data15_13TeV.00284154.physics_Main.merge.AOD.r7562_p2521/AOD.07687819._000382.pool.root.1"
#endif
#ifndef ASG_TEST_FILE_MC
  #define ASG_TEST_FILE_MC "/afs/cern.ch/user/a/asgbase/patspace/xAODs/r7725/mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2608_s2183_r7725_r7676/AOD.07915862._000100.pool.root.1"
#endif
#ifndef ASG_TEST_FILE_MCAFII
  #define ASG_TEST_FILE_MCAFII ""
#endif
#ifndef XAOD_STANDALONE
  #define XAOD_STANDALONE 1
#endif
#ifndef XAOD_ANALYSIS
  #define XAOD_ANALYSIS 1
#endif
#ifndef ASGTOOL_STANDALONE
  #define ASGTOOL_STANDALONE 1
#endif
#ifndef ROOTCORE_PACKAGE
  #define ROOTCORE_PACKAGE "H4lBDTWeights"
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "H4lBDTWeights/H4lBDTWeights.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"H4lBDTWeights", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("H4lBDTWeightsCINT",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_H4lBDTWeightsCINT_Impl, {{"namespace DataVector_detail { template <typename B1, typename B2, typename B3> class VirtBases; }", 1},{"template <typename T, typename BASE> class DataVector;", 1}}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_H4lBDTWeightsCINT_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_H4lBDTWeightsCINT() {
  TriggerDictionaryInitialization_H4lBDTWeightsCINT_Impl();
}
