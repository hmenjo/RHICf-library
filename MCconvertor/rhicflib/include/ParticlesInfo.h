#ifndef __PARTICLESINFO_H__
#define __PARTICLESINFO_H__

#include <TNamed.h>
#include <TObjArray.h>
#include <TClonesArray.h>
#include "RHICfSimP.h"


class ParticlesInfo : public TNamed 
{

 private:           
  Int_t       kRunNumber;        // Run Number
  Int_t       kEventNumber;     // Event number
  
  Int_t       kSpin;         // Spin of Incident Particle

  TClonesArray* fIP;
  TClonesArray* fWPlate;
  TClonesArray* fZDCGhost;
  TClonesArray* fCircle;
  TClonesArray* fGhost;
  TClonesArray* fNGhost;
  TClonesArray* fP0Ghost;
  TClonesArray* fNSignal;
  TClonesArray* fP0Signal;


  static TClonesArray* fgIP;
  static TClonesArray* fgWPlate;
  static TClonesArray* fgZDCGhost;
  static TClonesArray* fgCircle;
  static TClonesArray* fgGhost;
  static TClonesArray* fgNGhost;
  static TClonesArray* fgP0Ghost;
  static TClonesArray* fgNSignal;
  static TClonesArray* fgP0Signal;

 public:
  ParticlesInfo();
  ParticlesInfo(char* name, char *title);
  ~ParticlesInfo();
  void Reset();


  void SetRunNumber(Int_t);
  void SetEventNumber(Int_t);
  void SetSpin(Int_t);
  RHICfSimP* AddToIP(Int_t);
  RHICfSimP* AddToWPlate(Int_t);
  RHICfSimP* AddToZDCGhost(Int_t);
  RHICfSimP* AddToCircle(Int_t);
  RHICfSimP* AddToGhost(Int_t);
  RHICfSimP* AddToNGhost(Int_t);
  RHICfSimP* AddToP0Ghost(Int_t);
  RHICfSimP* AddToNSignal(Int_t);
  RHICfSimP* AddToP0Signal(Int_t);
  
  Int_t GetRunNumber(){return kRunNumber;};
  Int_t GetEventNumber(){return kEventNumber;};
  Int_t GetSpin(){return kSpin;};

  void     Clear();
  
  RHICfSimP* GetPFromIP(Int_t);
  RHICfSimP* GetPFromWPlate(Int_t);
  RHICfSimP* GetPFromZDCGhost(Int_t);
  RHICfSimP* GetPFromCircle(Int_t);
  RHICfSimP* GetPFromGhost(Int_t);
  RHICfSimP* GetPFromNGhost(Int_t);
  RHICfSimP* GetPFromP0Ghost(Int_t);
  RHICfSimP* GetPFromNSignal(Int_t);
  RHICfSimP* GetPFromP0Signal(Int_t);
  
  TClonesArray* GetIP(){return fIP;};
  TClonesArray* GetWPlate(){return fWPlate;};
  TClonesArray* GetZDCGhost(){return fZDCGhost;};
  TClonesArray* GetCircle(){return fCircle;};
  TClonesArray* GetGhost(){return fGhost;};
  TClonesArray* GetNGhost(){return fNGhost;};
  TClonesArray* GetP0Ghost(){return fP0Ghost;};
  TClonesArray* GetNSignal(){return fNSignal;};
  TClonesArray* GetP0Signal(){return fP0Signal;};
  
  ClassDef(ParticlesInfo,1);
};

#endif
