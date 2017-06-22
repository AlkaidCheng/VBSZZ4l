// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIafsdIcerndOchdIworkdImdImmittaldIprivatedIMyAnalysisCodedIRootCoreBindIobjdIx86_64mIslc6mIgcc49mIoptdIHZZUtilsdIobjdIHZZUtils_Reflex

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
#include "/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/HZZUtils/HZZUtils/HZZUtilsDict.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *IHiggsCrossSection_Dictionary();
   static void IHiggsCrossSection_TClassManip(TClass*);
   static void delete_IHiggsCrossSection(void *p);
   static void deleteArray_IHiggsCrossSection(void *p);
   static void destruct_IHiggsCrossSection(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::IHiggsCrossSection*)
   {
      ::IHiggsCrossSection *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::IHiggsCrossSection));
      static ::ROOT::TGenericClassInfo 
         instance("IHiggsCrossSection", "HZZUtils/IHiggsCrossSection.h", 9,
                  typeid(::IHiggsCrossSection), DefineBehavior(ptr, ptr),
                  &IHiggsCrossSection_Dictionary, isa_proxy, 0,
                  sizeof(::IHiggsCrossSection) );
      instance.SetDelete(&delete_IHiggsCrossSection);
      instance.SetDeleteArray(&deleteArray_IHiggsCrossSection);
      instance.SetDestructor(&destruct_IHiggsCrossSection);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::IHiggsCrossSection*)
   {
      return GenerateInitInstanceLocal((::IHiggsCrossSection*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::IHiggsCrossSection*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *IHiggsCrossSection_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::IHiggsCrossSection*)0x0)->GetClass();
      IHiggsCrossSection_TClassManip(theClass);
   return theClass;
   }

   static void IHiggsCrossSection_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *HiggsCrossSection_Dictionary();
   static void HiggsCrossSection_TClassManip(TClass*);
   static void delete_HiggsCrossSection(void *p);
   static void deleteArray_HiggsCrossSection(void *p);
   static void destruct_HiggsCrossSection(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HiggsCrossSection*)
   {
      ::HiggsCrossSection *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::HiggsCrossSection));
      static ::ROOT::TGenericClassInfo 
         instance("HiggsCrossSection", "HZZUtils/HiggsCrossSection.h", 8,
                  typeid(::HiggsCrossSection), DefineBehavior(ptr, ptr),
                  &HiggsCrossSection_Dictionary, isa_proxy, 0,
                  sizeof(::HiggsCrossSection) );
      instance.SetDelete(&delete_HiggsCrossSection);
      instance.SetDeleteArray(&deleteArray_HiggsCrossSection);
      instance.SetDestructor(&destruct_HiggsCrossSection);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HiggsCrossSection*)
   {
      return GenerateInitInstanceLocal((::HiggsCrossSection*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HiggsCrossSection*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *HiggsCrossSection_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::HiggsCrossSection*)0x0)->GetClass();
      HiggsCrossSection_TClassManip(theClass);
   return theClass;
   }

   static void HiggsCrossSection_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *IH4lBrRatio_Dictionary();
   static void IH4lBrRatio_TClassManip(TClass*);
   static void delete_IH4lBrRatio(void *p);
   static void deleteArray_IH4lBrRatio(void *p);
   static void destruct_IH4lBrRatio(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::IH4lBrRatio*)
   {
      ::IH4lBrRatio *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::IH4lBrRatio));
      static ::ROOT::TGenericClassInfo 
         instance("IH4lBrRatio", "HZZUtils/IH4lBrRatio.h", 9,
                  typeid(::IH4lBrRatio), DefineBehavior(ptr, ptr),
                  &IH4lBrRatio_Dictionary, isa_proxy, 0,
                  sizeof(::IH4lBrRatio) );
      instance.SetDelete(&delete_IH4lBrRatio);
      instance.SetDeleteArray(&deleteArray_IH4lBrRatio);
      instance.SetDestructor(&destruct_IH4lBrRatio);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::IH4lBrRatio*)
   {
      return GenerateInitInstanceLocal((::IH4lBrRatio*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::IH4lBrRatio*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *IH4lBrRatio_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::IH4lBrRatio*)0x0)->GetClass();
      IH4lBrRatio_TClassManip(theClass);
   return theClass;
   }

   static void IH4lBrRatio_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *H4lBrRatio_Dictionary();
   static void H4lBrRatio_TClassManip(TClass*);
   static void delete_H4lBrRatio(void *p);
   static void deleteArray_H4lBrRatio(void *p);
   static void destruct_H4lBrRatio(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::H4lBrRatio*)
   {
      ::H4lBrRatio *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::H4lBrRatio));
      static ::ROOT::TGenericClassInfo 
         instance("H4lBrRatio", "HZZUtils/H4lBrRatio.h", 8,
                  typeid(::H4lBrRatio), DefineBehavior(ptr, ptr),
                  &H4lBrRatio_Dictionary, isa_proxy, 0,
                  sizeof(::H4lBrRatio) );
      instance.SetDelete(&delete_H4lBrRatio);
      instance.SetDeleteArray(&deleteArray_H4lBrRatio);
      instance.SetDestructor(&destruct_H4lBrRatio);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::H4lBrRatio*)
   {
      return GenerateInitInstanceLocal((::H4lBrRatio*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::H4lBrRatio*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *H4lBrRatio_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::H4lBrRatio*)0x0)->GetClass();
      H4lBrRatio_TClassManip(theClass);
   return theClass;
   }

   static void H4lBrRatio_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_IHiggsCrossSection(void *p) {
      delete ((::IHiggsCrossSection*)p);
   }
   static void deleteArray_IHiggsCrossSection(void *p) {
      delete [] ((::IHiggsCrossSection*)p);
   }
   static void destruct_IHiggsCrossSection(void *p) {
      typedef ::IHiggsCrossSection current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::IHiggsCrossSection

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HiggsCrossSection(void *p) {
      delete ((::HiggsCrossSection*)p);
   }
   static void deleteArray_HiggsCrossSection(void *p) {
      delete [] ((::HiggsCrossSection*)p);
   }
   static void destruct_HiggsCrossSection(void *p) {
      typedef ::HiggsCrossSection current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HiggsCrossSection

namespace ROOT {
   // Wrapper around operator delete
   static void delete_IH4lBrRatio(void *p) {
      delete ((::IH4lBrRatio*)p);
   }
   static void deleteArray_IH4lBrRatio(void *p) {
      delete [] ((::IH4lBrRatio*)p);
   }
   static void destruct_IH4lBrRatio(void *p) {
      typedef ::IH4lBrRatio current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::IH4lBrRatio

namespace ROOT {
   // Wrapper around operator delete
   static void delete_H4lBrRatio(void *p) {
      delete ((::H4lBrRatio*)p);
   }
   static void deleteArray_H4lBrRatio(void *p) {
      delete [] ((::H4lBrRatio*)p);
   }
   static void destruct_H4lBrRatio(void *p) {
      typedef ::H4lBrRatio current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::H4lBrRatio

namespace {
  void TriggerDictionaryInitialization_HZZUtils_Reflex_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/HZZUtils/Root",
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/HZZUtils",
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.16-x86_64-slc6-gcc49-opt/include",
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/RootCoreBin/include",
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.16-x86_64-slc6-gcc49-opt/include",
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.16-x86_64-slc6-gcc49-opt/include",
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/HZZUtils/cmt/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$HZZUtils/IHiggsCrossSection.h")))  IHiggsCrossSection;
class __attribute__((annotate("$clingAutoload$HZZUtils/HiggsCrossSection.h")))  HiggsCrossSection;
class __attribute__((annotate("$clingAutoload$HZZUtils/IH4lBrRatio.h")))  IH4lBrRatio;
class __attribute__((annotate("$clingAutoload$HZZUtils/H4lBrRatio.h")))  H4lBrRatio;
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
  #define ROOTCORE_PACKAGE "HZZUtils"
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#ifndef HZZUTILS_HZZUTILS_H
#define HZZUTILS_HZZUTILS_H

#include "HZZUtils/IHiggsCrossSection.h"
#include "HZZUtils/HiggsCrossSection.h"
#include "HZZUtils/CrossSection.h"
#include "HZZUtils/IH4lBrRatio.h"
#include "HZZUtils/H4lBrRatio.h"
#include "HZZUtils/BrRatio.h"

#endif


#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"CentreOfMass::is", payloadCode, "@",
"ColumnBR::col", payloadCode, "@",
"ColumnXS::col", payloadCode, "@",
"H4lBrRatio", payloadCode, "@",
"HiggsCrossSection", payloadCode, "@",
"IH4lBrRatio", payloadCode, "@",
"IHiggsCrossSection", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HZZUtils_Reflex",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HZZUtils_Reflex_Impl, {{"namespace DataVector_detail { template <typename B1, typename B2, typename B3> class VirtBases; }", 1},{"template <typename T, typename BASE> class DataVector;", 1}}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HZZUtils_Reflex_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HZZUtils_Reflex() {
  TriggerDictionaryInitialization_HZZUtils_Reflex_Impl();
}
