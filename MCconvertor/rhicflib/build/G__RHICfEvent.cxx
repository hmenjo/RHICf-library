// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__RHICfEvent

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/ParticlesInfo.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfBBC.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfFC.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfRoman.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfSimIncidents.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfSimP.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfZDC.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_RHICfSimP(void *p = 0);
   static void *newArray_RHICfSimP(Long_t size, void *p);
   static void delete_RHICfSimP(void *p);
   static void deleteArray_RHICfSimP(void *p);
   static void destruct_RHICfSimP(void *p);
   static void streamer_RHICfSimP(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RHICfSimP*)
   {
      ::RHICfSimP *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RHICfSimP >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RHICfSimP", ::RHICfSimP::Class_Version(), "RHICfSimP.h", 9,
                  typeid(::RHICfSimP), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RHICfSimP::Dictionary, isa_proxy, 16,
                  sizeof(::RHICfSimP) );
      instance.SetNew(&new_RHICfSimP);
      instance.SetNewArray(&newArray_RHICfSimP);
      instance.SetDelete(&delete_RHICfSimP);
      instance.SetDeleteArray(&deleteArray_RHICfSimP);
      instance.SetDestructor(&destruct_RHICfSimP);
      instance.SetStreamerFunc(&streamer_RHICfSimP);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RHICfSimP*)
   {
      return GenerateInitInstanceLocal((::RHICfSimP*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::RHICfSimP*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_ParticlesInfo(void *p = 0);
   static void *newArray_ParticlesInfo(Long_t size, void *p);
   static void delete_ParticlesInfo(void *p);
   static void deleteArray_ParticlesInfo(void *p);
   static void destruct_ParticlesInfo(void *p);
   static void streamer_ParticlesInfo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ParticlesInfo*)
   {
      ::ParticlesInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ParticlesInfo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ParticlesInfo", ::ParticlesInfo::Class_Version(), "ParticlesInfo.h", 10,
                  typeid(::ParticlesInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ParticlesInfo::Dictionary, isa_proxy, 16,
                  sizeof(::ParticlesInfo) );
      instance.SetNew(&new_ParticlesInfo);
      instance.SetNewArray(&newArray_ParticlesInfo);
      instance.SetDelete(&delete_ParticlesInfo);
      instance.SetDeleteArray(&deleteArray_ParticlesInfo);
      instance.SetDestructor(&destruct_ParticlesInfo);
      instance.SetStreamerFunc(&streamer_ParticlesInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ParticlesInfo*)
   {
      return GenerateInitInstanceLocal((::ParticlesInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ParticlesInfo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RHICfBBC(void *p = 0);
   static void *newArray_RHICfBBC(Long_t size, void *p);
   static void delete_RHICfBBC(void *p);
   static void deleteArray_RHICfBBC(void *p);
   static void destruct_RHICfBBC(void *p);
   static void streamer_RHICfBBC(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RHICfBBC*)
   {
      ::RHICfBBC *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RHICfBBC >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RHICfBBC", ::RHICfBBC::Class_Version(), "RHICfBBC.h", 6,
                  typeid(::RHICfBBC), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RHICfBBC::Dictionary, isa_proxy, 16,
                  sizeof(::RHICfBBC) );
      instance.SetNew(&new_RHICfBBC);
      instance.SetNewArray(&newArray_RHICfBBC);
      instance.SetDelete(&delete_RHICfBBC);
      instance.SetDeleteArray(&deleteArray_RHICfBBC);
      instance.SetDestructor(&destruct_RHICfBBC);
      instance.SetStreamerFunc(&streamer_RHICfBBC);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RHICfBBC*)
   {
      return GenerateInitInstanceLocal((::RHICfBBC*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::RHICfBBC*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RHICfFC(void *p = 0);
   static void *newArray_RHICfFC(Long_t size, void *p);
   static void delete_RHICfFC(void *p);
   static void deleteArray_RHICfFC(void *p);
   static void destruct_RHICfFC(void *p);
   static void streamer_RHICfFC(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RHICfFC*)
   {
      ::RHICfFC *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RHICfFC >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RHICfFC", ::RHICfFC::Class_Version(), "RHICfFC.h", 6,
                  typeid(::RHICfFC), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RHICfFC::Dictionary, isa_proxy, 16,
                  sizeof(::RHICfFC) );
      instance.SetNew(&new_RHICfFC);
      instance.SetNewArray(&newArray_RHICfFC);
      instance.SetDelete(&delete_RHICfFC);
      instance.SetDeleteArray(&deleteArray_RHICfFC);
      instance.SetDestructor(&destruct_RHICfFC);
      instance.SetStreamerFunc(&streamer_RHICfFC);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RHICfFC*)
   {
      return GenerateInitInstanceLocal((::RHICfFC*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::RHICfFC*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RHICfRoman(void *p = 0);
   static void *newArray_RHICfRoman(Long_t size, void *p);
   static void delete_RHICfRoman(void *p);
   static void deleteArray_RHICfRoman(void *p);
   static void destruct_RHICfRoman(void *p);
   static void streamer_RHICfRoman(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RHICfRoman*)
   {
      ::RHICfRoman *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RHICfRoman >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RHICfRoman", ::RHICfRoman::Class_Version(), "RHICfRoman.h", 6,
                  typeid(::RHICfRoman), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RHICfRoman::Dictionary, isa_proxy, 16,
                  sizeof(::RHICfRoman) );
      instance.SetNew(&new_RHICfRoman);
      instance.SetNewArray(&newArray_RHICfRoman);
      instance.SetDelete(&delete_RHICfRoman);
      instance.SetDeleteArray(&deleteArray_RHICfRoman);
      instance.SetDestructor(&destruct_RHICfRoman);
      instance.SetStreamerFunc(&streamer_RHICfRoman);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RHICfRoman*)
   {
      return GenerateInitInstanceLocal((::RHICfRoman*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::RHICfRoman*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RHICfSimIncidents(void *p = 0);
   static void *newArray_RHICfSimIncidents(Long_t size, void *p);
   static void delete_RHICfSimIncidents(void *p);
   static void deleteArray_RHICfSimIncidents(void *p);
   static void destruct_RHICfSimIncidents(void *p);
   static void streamer_RHICfSimIncidents(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RHICfSimIncidents*)
   {
      ::RHICfSimIncidents *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RHICfSimIncidents >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RHICfSimIncidents", ::RHICfSimIncidents::Class_Version(), "RHICfSimIncidents.h", 8,
                  typeid(::RHICfSimIncidents), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RHICfSimIncidents::Dictionary, isa_proxy, 16,
                  sizeof(::RHICfSimIncidents) );
      instance.SetNew(&new_RHICfSimIncidents);
      instance.SetNewArray(&newArray_RHICfSimIncidents);
      instance.SetDelete(&delete_RHICfSimIncidents);
      instance.SetDeleteArray(&deleteArray_RHICfSimIncidents);
      instance.SetDestructor(&destruct_RHICfSimIncidents);
      instance.SetStreamerFunc(&streamer_RHICfSimIncidents);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RHICfSimIncidents*)
   {
      return GenerateInitInstanceLocal((::RHICfSimIncidents*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::RHICfSimIncidents*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RHICfZDC(void *p = 0);
   static void *newArray_RHICfZDC(Long_t size, void *p);
   static void delete_RHICfZDC(void *p);
   static void deleteArray_RHICfZDC(void *p);
   static void destruct_RHICfZDC(void *p);
   static void streamer_RHICfZDC(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RHICfZDC*)
   {
      ::RHICfZDC *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RHICfZDC >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RHICfZDC", ::RHICfZDC::Class_Version(), "RHICfZDC.h", 6,
                  typeid(::RHICfZDC), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RHICfZDC::Dictionary, isa_proxy, 16,
                  sizeof(::RHICfZDC) );
      instance.SetNew(&new_RHICfZDC);
      instance.SetNewArray(&newArray_RHICfZDC);
      instance.SetDelete(&delete_RHICfZDC);
      instance.SetDeleteArray(&deleteArray_RHICfZDC);
      instance.SetDestructor(&destruct_RHICfZDC);
      instance.SetStreamerFunc(&streamer_RHICfZDC);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RHICfZDC*)
   {
      return GenerateInitInstanceLocal((::RHICfZDC*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::RHICfZDC*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr RHICfSimP::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RHICfSimP::Class_Name()
{
   return "RHICfSimP";
}

//______________________________________________________________________________
const char *RHICfSimP::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfSimP*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RHICfSimP::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfSimP*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RHICfSimP::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfSimP*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RHICfSimP::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfSimP*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr ParticlesInfo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ParticlesInfo::Class_Name()
{
   return "ParticlesInfo";
}

//______________________________________________________________________________
const char *ParticlesInfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ParticlesInfo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ParticlesInfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ParticlesInfo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ParticlesInfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ParticlesInfo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ParticlesInfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ParticlesInfo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RHICfBBC::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RHICfBBC::Class_Name()
{
   return "RHICfBBC";
}

//______________________________________________________________________________
const char *RHICfBBC::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfBBC*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RHICfBBC::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfBBC*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RHICfBBC::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfBBC*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RHICfBBC::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfBBC*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RHICfFC::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RHICfFC::Class_Name()
{
   return "RHICfFC";
}

//______________________________________________________________________________
const char *RHICfFC::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfFC*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RHICfFC::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfFC*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RHICfFC::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfFC*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RHICfFC::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfFC*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RHICfRoman::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RHICfRoman::Class_Name()
{
   return "RHICfRoman";
}

//______________________________________________________________________________
const char *RHICfRoman::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfRoman*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RHICfRoman::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfRoman*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RHICfRoman::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfRoman*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RHICfRoman::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfRoman*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RHICfSimIncidents::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RHICfSimIncidents::Class_Name()
{
   return "RHICfSimIncidents";
}

//______________________________________________________________________________
const char *RHICfSimIncidents::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfSimIncidents*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RHICfSimIncidents::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfSimIncidents*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RHICfSimIncidents::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfSimIncidents*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RHICfSimIncidents::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfSimIncidents*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RHICfZDC::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RHICfZDC::Class_Name()
{
   return "RHICfZDC";
}

//______________________________________________________________________________
const char *RHICfZDC::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfZDC*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RHICfZDC::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RHICfZDC*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RHICfZDC::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfZDC*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RHICfZDC::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RHICfZDC*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void RHICfSimP::Streamer(TBuffer &R__b)
{
   // Stream an object of class RHICfSimP.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> pdgcode;
      name.Streamer(R__b);
      R__b >> user;
      R__b.ReadStaticArray((double*)pos);
      R__b >> energy;
      R__b.ReadStaticArray((double*)mom);
      Name.Streamer(R__b);
      FMomentum.Streamer(R__b);
      Position.Streamer(R__b);
      OriginalPName.Streamer(R__b);
      OriginalP4Momentum.Streamer(R__b);
      OriginalPPosition.Streamer(R__b);
      R__b >> TrackID;
      R__b >> Tower;
      R__b.CheckByteCount(R__s, R__c, RHICfSimP::IsA());
   } else {
      R__c = R__b.WriteVersion(RHICfSimP::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << pdgcode;
      name.Streamer(R__b);
      R__b << user;
      R__b.WriteArray(pos, 3);
      R__b << energy;
      R__b.WriteArray(mom, 3);
      Name.Streamer(R__b);
      FMomentum.Streamer(R__b);
      Position.Streamer(R__b);
      OriginalPName.Streamer(R__b);
      OriginalP4Momentum.Streamer(R__b);
      OriginalPPosition.Streamer(R__b);
      R__b << TrackID;
      R__b << Tower;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RHICfSimP(void *p) {
      return  p ? new(p) ::RHICfSimP : new ::RHICfSimP;
   }
   static void *newArray_RHICfSimP(Long_t nElements, void *p) {
      return p ? new(p) ::RHICfSimP[nElements] : new ::RHICfSimP[nElements];
   }
   // Wrapper around operator delete
   static void delete_RHICfSimP(void *p) {
      delete ((::RHICfSimP*)p);
   }
   static void deleteArray_RHICfSimP(void *p) {
      delete [] ((::RHICfSimP*)p);
   }
   static void destruct_RHICfSimP(void *p) {
      typedef ::RHICfSimP current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RHICfSimP(TBuffer &buf, void *obj) {
      ((::RHICfSimP*)obj)->::RHICfSimP::Streamer(buf);
   }
} // end of namespace ROOT for class ::RHICfSimP

//______________________________________________________________________________
void ParticlesInfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class ParticlesInfo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> kRunNumber;
      R__b >> kEventNumber;
      R__b >> kSpin;
      fIP->Streamer(R__b);
      fWPlate->Streamer(R__b);
      fZDCGhost->Streamer(R__b);
      fCircle->Streamer(R__b);
      fGhost->Streamer(R__b);
      fNGhost->Streamer(R__b);
      fP0Ghost->Streamer(R__b);
      fNSignal->Streamer(R__b);
      fP0Signal->Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, ParticlesInfo::IsA());
   } else {
      R__c = R__b.WriteVersion(ParticlesInfo::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << kRunNumber;
      R__b << kEventNumber;
      R__b << kSpin;
      fIP->Streamer(R__b);
      fWPlate->Streamer(R__b);
      fZDCGhost->Streamer(R__b);
      fCircle->Streamer(R__b);
      fGhost->Streamer(R__b);
      fNGhost->Streamer(R__b);
      fP0Ghost->Streamer(R__b);
      fNSignal->Streamer(R__b);
      fP0Signal->Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ParticlesInfo(void *p) {
      return  p ? new(p) ::ParticlesInfo : new ::ParticlesInfo;
   }
   static void *newArray_ParticlesInfo(Long_t nElements, void *p) {
      return p ? new(p) ::ParticlesInfo[nElements] : new ::ParticlesInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_ParticlesInfo(void *p) {
      delete ((::ParticlesInfo*)p);
   }
   static void deleteArray_ParticlesInfo(void *p) {
      delete [] ((::ParticlesInfo*)p);
   }
   static void destruct_ParticlesInfo(void *p) {
      typedef ::ParticlesInfo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_ParticlesInfo(TBuffer &buf, void *obj) {
      ((::ParticlesInfo*)obj)->::ParticlesInfo::Streamer(buf);
   }
} // end of namespace ROOT for class ::ParticlesInfo

//______________________________________________________________________________
void RHICfBBC::Streamer(TBuffer &R__b)
{
   // Stream an object of class RHICfBBC.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> run;
      R__b >> number;
      R__b.ReadStaticArray((double*)dE);
      R__b.ReadStaticArray((int*)NOP);
      R__b.CheckByteCount(R__s, R__c, RHICfBBC::IsA());
   } else {
      R__c = R__b.WriteVersion(RHICfBBC::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << run;
      R__b << number;
      R__b.WriteArray((double*)dE, 72);
      R__b.WriteArray((int*)NOP, 72);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RHICfBBC(void *p) {
      return  p ? new(p) ::RHICfBBC : new ::RHICfBBC;
   }
   static void *newArray_RHICfBBC(Long_t nElements, void *p) {
      return p ? new(p) ::RHICfBBC[nElements] : new ::RHICfBBC[nElements];
   }
   // Wrapper around operator delete
   static void delete_RHICfBBC(void *p) {
      delete ((::RHICfBBC*)p);
   }
   static void deleteArray_RHICfBBC(void *p) {
      delete [] ((::RHICfBBC*)p);
   }
   static void destruct_RHICfBBC(void *p) {
      typedef ::RHICfBBC current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RHICfBBC(TBuffer &buf, void *obj) {
      ((::RHICfBBC*)obj)->::RHICfBBC::Streamer(buf);
   }
} // end of namespace ROOT for class ::RHICfBBC

//______________________________________________________________________________
void RHICfFC::Streamer(TBuffer &R__b)
{
   // Stream an object of class RHICfFC.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> run;
      R__b >> number;
      R__b.ReadStaticArray((int*)FCNOP);
      R__b.ReadStaticArray((double*)FCdE);
      R__b.CheckByteCount(R__s, R__c, RHICfFC::IsA());
   } else {
      R__c = R__b.WriteVersion(RHICfFC::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << run;
      R__b << number;
      R__b.WriteArray(FCNOP, 2);
      R__b.WriteArray(FCdE, 2);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RHICfFC(void *p) {
      return  p ? new(p) ::RHICfFC : new ::RHICfFC;
   }
   static void *newArray_RHICfFC(Long_t nElements, void *p) {
      return p ? new(p) ::RHICfFC[nElements] : new ::RHICfFC[nElements];
   }
   // Wrapper around operator delete
   static void delete_RHICfFC(void *p) {
      delete ((::RHICfFC*)p);
   }
   static void deleteArray_RHICfFC(void *p) {
      delete [] ((::RHICfFC*)p);
   }
   static void destruct_RHICfFC(void *p) {
      typedef ::RHICfFC current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RHICfFC(TBuffer &buf, void *obj) {
      ((::RHICfFC*)obj)->::RHICfFC::Streamer(buf);
   }
} // end of namespace ROOT for class ::RHICfFC

//______________________________________________________________________________
void RHICfRoman::Streamer(TBuffer &R__b)
{
   // Stream an object of class RHICfRoman.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> run;
      R__b >> number;
      R__b.ReadStaticArray((double*)dE);
      R__b.CheckByteCount(R__s, R__c, RHICfRoman::IsA());
   } else {
      R__c = R__b.WriteVersion(RHICfRoman::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << run;
      R__b << number;
      R__b.WriteArray(dE, 36);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RHICfRoman(void *p) {
      return  p ? new(p) ::RHICfRoman : new ::RHICfRoman;
   }
   static void *newArray_RHICfRoman(Long_t nElements, void *p) {
      return p ? new(p) ::RHICfRoman[nElements] : new ::RHICfRoman[nElements];
   }
   // Wrapper around operator delete
   static void delete_RHICfRoman(void *p) {
      delete ((::RHICfRoman*)p);
   }
   static void deleteArray_RHICfRoman(void *p) {
      delete [] ((::RHICfRoman*)p);
   }
   static void destruct_RHICfRoman(void *p) {
      typedef ::RHICfRoman current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RHICfRoman(TBuffer &buf, void *obj) {
      ((::RHICfRoman*)obj)->::RHICfRoman::Streamer(buf);
   }
} // end of namespace ROOT for class ::RHICfRoman

//______________________________________________________________________________
void RHICfSimIncidents::Streamer(TBuffer &R__b)
{
   // Stream an object of class RHICfSimIncidents.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> run;
      R__b >> number;
      R__b >> gnumber;
      R__b >> np;
      particles.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, RHICfSimIncidents::IsA());
   } else {
      R__c = R__b.WriteVersion(RHICfSimIncidents::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << run;
      R__b << number;
      R__b << gnumber;
      R__b << np;
      particles.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RHICfSimIncidents(void *p) {
      return  p ? new(p) ::RHICfSimIncidents : new ::RHICfSimIncidents;
   }
   static void *newArray_RHICfSimIncidents(Long_t nElements, void *p) {
      return p ? new(p) ::RHICfSimIncidents[nElements] : new ::RHICfSimIncidents[nElements];
   }
   // Wrapper around operator delete
   static void delete_RHICfSimIncidents(void *p) {
      delete ((::RHICfSimIncidents*)p);
   }
   static void deleteArray_RHICfSimIncidents(void *p) {
      delete [] ((::RHICfSimIncidents*)p);
   }
   static void destruct_RHICfSimIncidents(void *p) {
      typedef ::RHICfSimIncidents current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RHICfSimIncidents(TBuffer &buf, void *obj) {
      ((::RHICfSimIncidents*)obj)->::RHICfSimIncidents::Streamer(buf);
   }
} // end of namespace ROOT for class ::RHICfSimIncidents

//______________________________________________________________________________
void RHICfZDC::Streamer(TBuffer &R__b)
{
   // Stream an object of class RHICfZDC.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> run;
      R__b >> number;
      R__b.ReadStaticArray((int*)ZDCNOP);
      R__b.ReadStaticArray((int*)SMDHNOP);
      R__b.ReadStaticArray((int*)SMDVNOP);
      R__b.ReadStaticArray((double*)ZDCdE);
      R__b.ReadStaticArray((double*)SMDHdE);
      R__b.ReadStaticArray((double*)SMDVdE);
      R__b.CheckByteCount(R__s, R__c, RHICfZDC::IsA());
   } else {
      R__c = R__b.WriteVersion(RHICfZDC::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << run;
      R__b << number;
      R__b.WriteArray(ZDCNOP, 3);
      R__b.WriteArray(SMDHNOP, 7);
      R__b.WriteArray(SMDVNOP, 8);
      R__b.WriteArray(ZDCdE, 3);
      R__b.WriteArray(SMDHdE, 7);
      R__b.WriteArray(SMDVdE, 8);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RHICfZDC(void *p) {
      return  p ? new(p) ::RHICfZDC : new ::RHICfZDC;
   }
   static void *newArray_RHICfZDC(Long_t nElements, void *p) {
      return p ? new(p) ::RHICfZDC[nElements] : new ::RHICfZDC[nElements];
   }
   // Wrapper around operator delete
   static void delete_RHICfZDC(void *p) {
      delete ((::RHICfZDC*)p);
   }
   static void deleteArray_RHICfZDC(void *p) {
      delete [] ((::RHICfZDC*)p);
   }
   static void destruct_RHICfZDC(void *p) {
      typedef ::RHICfZDC current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RHICfZDC(TBuffer &buf, void *obj) {
      ((::RHICfZDC*)obj)->::RHICfZDC::Streamer(buf);
   }
} // end of namespace ROOT for class ::RHICfZDC

namespace {
  void TriggerDictionaryInitialization_libRHICfEvent_Impl() {
    static const char* headers[] = {
"/home/hoosiki/DataConversion/convertor/rhicflib/include/ParticlesInfo.h",
"/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfBBC.h",
"/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfFC.h",
"/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfRoman.h",
"/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfSimIncidents.h",
"/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfSimP.h",
"/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfZDC.h",
0
    };
    static const char* includePaths[] = {
"/home/hoosiki/Packages/root6/include",
"/home/hoosiki/DataConversion/convertor/rhicflib/include",
"/home/hoosiki/Cellar/root/root6.12.04/include",
"/home/hoosiki/DataConversion/convertor/rhicflib/build/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libRHICfEvent dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Data class for information of one incident particle in simulation.)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Data class for information of one incident particle in simulation.)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Data class for information of one incident particle in simulation.)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Data class for information of one incident particle in simulation.)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$RHICfSimP.h")))  __attribute__((annotate("$clingAutoload$/home/hoosiki/DataConversion/convertor/rhicflib/include/ParticlesInfo.h")))  RHICfSimP;
class __attribute__((annotate("$clingAutoload$/home/hoosiki/DataConversion/convertor/rhicflib/include/ParticlesInfo.h")))  ParticlesInfo;
class __attribute__((annotate(R"ATTRDUMP(RHICf BBC data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf BBC data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf BBC data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf BBC data)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfBBC.h")))  RHICfBBC;
class __attribute__((annotate(R"ATTRDUMP(RHICf FC data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf FC data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf FC data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf FC data)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfFC.h")))  RHICfFC;
class __attribute__((annotate(R"ATTRDUMP(RHICf Roman data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf Roman data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf Roman data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf Roman data)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfRoman.h")))  RHICfRoman;
class __attribute__((annotate("$clingAutoload$/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfSimIncidents.h")))  RHICfSimIncidents;
class __attribute__((annotate(R"ATTRDUMP(RHICf ZDC data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf ZDC data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf ZDC data)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(RHICf ZDC data)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfZDC.h")))  RHICfZDC;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libRHICfEvent dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/ParticlesInfo.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfBBC.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfFC.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfRoman.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfSimIncidents.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfSimP.h"
#include "/home/hoosiki/DataConversion/convertor/rhicflib/include/RHICfZDC.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"ParticlesInfo", payloadCode, "@",
"RHICfBBC", payloadCode, "@",
"RHICfFC", payloadCode, "@",
"RHICfRoman", payloadCode, "@",
"RHICfSimIncidents", payloadCode, "@",
"RHICfSimP", payloadCode, "@",
"RHICfZDC", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libRHICfEvent",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libRHICfEvent_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libRHICfEvent_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libRHICfEvent() {
  TriggerDictionaryInitialization_libRHICfEvent_Impl();
}
