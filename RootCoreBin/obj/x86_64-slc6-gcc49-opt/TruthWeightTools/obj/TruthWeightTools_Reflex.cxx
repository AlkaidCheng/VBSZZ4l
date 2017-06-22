// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIafsdIcerndOchdIworkdImdImmittaldIprivatedIMyAnalysisCodedIRootCoreBindIobjdIx86_64mIslc6mIgcc49mIoptdITruthWeightToolsdIobjdITruthWeightTools_Reflex

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
#include "/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/TruthWeightTools/TruthWeightTools/TruthWeightToolsDict.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *IIndexRetriever_Dictionary();
   static void IIndexRetriever_TClassManip(TClass*);
   static void delete_IIndexRetriever(void *p);
   static void deleteArray_IIndexRetriever(void *p);
   static void destruct_IIndexRetriever(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::IIndexRetriever*)
   {
      ::IIndexRetriever *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::IIndexRetriever));
      static ::ROOT::TGenericClassInfo 
         instance("IIndexRetriever", "TruthWeightTools/IndexRetriever.h", 7,
                  typeid(::IIndexRetriever), DefineBehavior(ptr, ptr),
                  &IIndexRetriever_Dictionary, isa_proxy, 0,
                  sizeof(::IIndexRetriever) );
      instance.SetDelete(&delete_IIndexRetriever);
      instance.SetDeleteArray(&deleteArray_IIndexRetriever);
      instance.SetDestructor(&destruct_IIndexRetriever);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::IIndexRetriever*)
   {
      return GenerateInitInstanceLocal((::IIndexRetriever*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::IIndexRetriever*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *IIndexRetriever_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::IIndexRetriever*)0x0)->GetClass();
      IIndexRetriever_TClassManip(theClass);
   return theClass;
   }

   static void IIndexRetriever_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *IndexRetriever_Dictionary();
   static void IndexRetriever_TClassManip(TClass*);
   static void delete_IndexRetriever(void *p);
   static void deleteArray_IndexRetriever(void *p);
   static void destruct_IndexRetriever(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::IndexRetriever*)
   {
      ::IndexRetriever *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::IndexRetriever));
      static ::ROOT::TGenericClassInfo 
         instance("IndexRetriever", "TruthWeightTools/IndexRetriever.h", 26,
                  typeid(::IndexRetriever), DefineBehavior(ptr, ptr),
                  &IndexRetriever_Dictionary, isa_proxy, 0,
                  sizeof(::IndexRetriever) );
      instance.SetDelete(&delete_IndexRetriever);
      instance.SetDeleteArray(&deleteArray_IndexRetriever);
      instance.SetDestructor(&destruct_IndexRetriever);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::IndexRetriever*)
   {
      return GenerateInitInstanceLocal((::IndexRetriever*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::IndexRetriever*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *IndexRetriever_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::IndexRetriever*)0x0)->GetClass();
      IndexRetriever_TClassManip(theClass);
   return theClass;
   }

   static void IndexRetriever_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *xAODcLcLITruthWeightTool_Dictionary();
   static void xAODcLcLITruthWeightTool_TClassManip(TClass*);
   static void delete_xAODcLcLITruthWeightTool(void *p);
   static void deleteArray_xAODcLcLITruthWeightTool(void *p);
   static void destruct_xAODcLcLITruthWeightTool(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::xAOD::ITruthWeightTool*)
   {
      ::xAOD::ITruthWeightTool *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::xAOD::ITruthWeightTool));
      static ::ROOT::TGenericClassInfo 
         instance("xAOD::ITruthWeightTool", "TruthWeightTools/ITruthWeightTool.h", 24,
                  typeid(::xAOD::ITruthWeightTool), DefineBehavior(ptr, ptr),
                  &xAODcLcLITruthWeightTool_Dictionary, isa_proxy, 0,
                  sizeof(::xAOD::ITruthWeightTool) );
      instance.SetDelete(&delete_xAODcLcLITruthWeightTool);
      instance.SetDeleteArray(&deleteArray_xAODcLcLITruthWeightTool);
      instance.SetDestructor(&destruct_xAODcLcLITruthWeightTool);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::xAOD::ITruthWeightTool*)
   {
      return GenerateInitInstanceLocal((::xAOD::ITruthWeightTool*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::xAOD::ITruthWeightTool*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *xAODcLcLITruthWeightTool_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::xAOD::ITruthWeightTool*)0x0)->GetClass();
      xAODcLcLITruthWeightTool_TClassManip(theClass);
   return theClass;
   }

   static void xAODcLcLITruthWeightTool_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *xAODcLcLTruthWeightTool_Dictionary();
   static void xAODcLcLTruthWeightTool_TClassManip(TClass*);
   static void *new_xAODcLcLTruthWeightTool(void *p = 0);
   static void *newArray_xAODcLcLTruthWeightTool(Long_t size, void *p);
   static void delete_xAODcLcLTruthWeightTool(void *p);
   static void deleteArray_xAODcLcLTruthWeightTool(void *p);
   static void destruct_xAODcLcLTruthWeightTool(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::xAOD::TruthWeightTool*)
   {
      ::xAOD::TruthWeightTool *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::xAOD::TruthWeightTool));
      static ::ROOT::TGenericClassInfo 
         instance("xAOD::TruthWeightTool", "TruthWeightTools/TruthWeightTool.h", 30,
                  typeid(::xAOD::TruthWeightTool), DefineBehavior(ptr, ptr),
                  &xAODcLcLTruthWeightTool_Dictionary, isa_proxy, 0,
                  sizeof(::xAOD::TruthWeightTool) );
      instance.SetNew(&new_xAODcLcLTruthWeightTool);
      instance.SetNewArray(&newArray_xAODcLcLTruthWeightTool);
      instance.SetDelete(&delete_xAODcLcLTruthWeightTool);
      instance.SetDeleteArray(&deleteArray_xAODcLcLTruthWeightTool);
      instance.SetDestructor(&destruct_xAODcLcLTruthWeightTool);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::xAOD::TruthWeightTool*)
   {
      return GenerateInitInstanceLocal((::xAOD::TruthWeightTool*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::xAOD::TruthWeightTool*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *xAODcLcLTruthWeightTool_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::xAOD::TruthWeightTool*)0x0)->GetClass();
      xAODcLcLTruthWeightTool_TClassManip(theClass);
   return theClass;
   }

   static void xAODcLcLTruthWeightTool_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_IIndexRetriever(void *p) {
      delete ((::IIndexRetriever*)p);
   }
   static void deleteArray_IIndexRetriever(void *p) {
      delete [] ((::IIndexRetriever*)p);
   }
   static void destruct_IIndexRetriever(void *p) {
      typedef ::IIndexRetriever current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::IIndexRetriever

namespace ROOT {
   // Wrapper around operator delete
   static void delete_IndexRetriever(void *p) {
      delete ((::IndexRetriever*)p);
   }
   static void deleteArray_IndexRetriever(void *p) {
      delete [] ((::IndexRetriever*)p);
   }
   static void destruct_IndexRetriever(void *p) {
      typedef ::IndexRetriever current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::IndexRetriever

namespace ROOT {
   // Wrapper around operator delete
   static void delete_xAODcLcLITruthWeightTool(void *p) {
      delete ((::xAOD::ITruthWeightTool*)p);
   }
   static void deleteArray_xAODcLcLITruthWeightTool(void *p) {
      delete [] ((::xAOD::ITruthWeightTool*)p);
   }
   static void destruct_xAODcLcLITruthWeightTool(void *p) {
      typedef ::xAOD::ITruthWeightTool current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::xAOD::ITruthWeightTool

namespace ROOT {
   // Wrappers around operator new
   static void *new_xAODcLcLTruthWeightTool(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::xAOD::TruthWeightTool : new ::xAOD::TruthWeightTool;
   }
   static void *newArray_xAODcLcLTruthWeightTool(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::xAOD::TruthWeightTool[nElements] : new ::xAOD::TruthWeightTool[nElements];
   }
   // Wrapper around operator delete
   static void delete_xAODcLcLTruthWeightTool(void *p) {
      delete ((::xAOD::TruthWeightTool*)p);
   }
   static void deleteArray_xAODcLcLTruthWeightTool(void *p) {
      delete [] ((::xAOD::TruthWeightTool*)p);
   }
   static void destruct_xAODcLcLTruthWeightTool(void *p) {
      typedef ::xAOD::TruthWeightTool current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::xAOD::TruthWeightTool

namespace {
  void TriggerDictionaryInitialization_TruthWeightTools_Reflex_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/TruthWeightTools/Root",
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/TruthWeightTools",
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.16-x86_64-slc6-gcc49-opt/include",
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/RootCoreBin/include",
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.16-x86_64-slc6-gcc49-opt/include",
"/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.16-x86_64-slc6-gcc49-opt/include",
"/afs/cern.ch/work/m/mmittal/private/MyAnalysisCode/TruthWeightTools/cmt/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TruthWeightTools/TruthWeightTool.h")))  IIndexRetriever;
class __attribute__((annotate("$clingAutoload$TruthWeightTools/TruthWeightTool.h")))  IndexRetriever;
namespace xAOD{class __attribute__((annotate("$clingAutoload$TruthWeightTools/TruthWeightTool.h")))  ITruthWeightTool;}
namespace xAOD{class __attribute__((annotate("$clingAutoload$TruthWeightTools/TruthWeightTool.h")))  TruthWeightTool;}
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
  #define ROOTCORE_PACKAGE "TruthWeightTools"
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// $Id: TruthWeightToolsDict.h 796969 2017-02-14 02:57:09Z dgillber $
#ifndef TRUTHWEIGHTTOOLS_TRUTHTOOLSDICT_H
#define TRUTHWEIGHTTOOLS_TRUTHTOOLSDICT_H

// Local include(s):
#include "TruthWeightTools/TruthWeightTool.h"

#endif // TRUTHTOOLS_TRUTHTOOLSDICT_H


#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"IIndexRetriever", payloadCode, "@",
"IndexRetriever", payloadCode, "@",
"xAOD::ITruthWeightTool", payloadCode, "@",
"xAOD::TruthWeightTool", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TruthWeightTools_Reflex",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TruthWeightTools_Reflex_Impl, {{"namespace DataVector_detail { template <typename B1, typename B2, typename B3> class VirtBases; }", 1},{"template <typename T> class DataVectorBase;", 1},{"template <typename T, typename BASE> class DataVector;", 1},{"namespace DataVector_detail { template <typename T> class DVLEltBaseInit; }", 1}}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TruthWeightTools_Reflex_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TruthWeightTools_Reflex() {
  TriggerDictionaryInitialization_TruthWeightTools_Reflex_Impl();
}
