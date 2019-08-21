#ifndef __PARTICLESINFO_CPP__
#define __PARTICLESINFO_CPP__

#include "ParticlesInfo.h"



#if !defined(__CINT__)
ClassImp(ParticlesInfo);
#endif

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

TClonesArray* ParticlesInfo::fgIP = 0;
TClonesArray* ParticlesInfo::fgWPlate = 0;
TClonesArray* ParticlesInfo::fgZDCGhost = 0;
TClonesArray* ParticlesInfo::fgCircle = 0;
TClonesArray* ParticlesInfo::fgGhost = 0;
TClonesArray* ParticlesInfo::fgNGhost = 0;
TClonesArray* ParticlesInfo::fgP0Ghost = 0;
TClonesArray* ParticlesInfo::fgNSignal = 0;
TClonesArray* ParticlesInfo::fgP0Signal = 0;

ParticlesInfo::ParticlesInfo(): kRunNumber(0), kEventNumber(0), kSpin(-1)
{
    if(!fgIP)fgIP = new TClonesArray("RHICfSimP", 2000000);
    if(!fgWPlate)fgWPlate = new TClonesArray("RHICfSimP", 2000);
    if(!fgZDCGhost)fgZDCGhost = new TClonesArray("RHICfSimP", 2000);
    if(!fgCircle)fgCircle = new TClonesArray("RHICfSimP", 1000);
    if(!fgGhost)fgGhost = new TClonesArray("RHICfSimP", 600);
    if(!fgNGhost)fgNGhost = new TClonesArray("RHICfSimP", 600);
    if(!fgP0Ghost)fgP0Ghost = new TClonesArray("RHICfSimP", 600);
    if(!fgNSignal)fgNSignal = new TClonesArray("RHICfSimP", 600);
    if(!fgP0Signal)fgP0Signal = new TClonesArray("RHICfSimP", 600);
    fIP = fgIP;
    fWPlate = fgWPlate;
    fZDCGhost = fgZDCGhost;
    fCircle = fgCircle;
    fGhost = fgGhost;
    fNGhost = fgNGhost;
    fP0Ghost = fgP0Ghost;
    fNSignal = fgNSignal;
    fP0Signal = fgP0Signal;
}

ParticlesInfo::ParticlesInfo(char *name, char *title):TNamed(name,title), kRunNumber(0), kEventNumber(0), kSpin(-1)
{
    if(!fgIP)fgIP = new TClonesArray("RHICfSimP", 2000000);
    if(!fgWPlate)fgWPlate = new TClonesArray("RHICfSimP", 2000);
    if(!fgZDCGhost)fgZDCGhost = new TClonesArray("RHICfSimP", 2000);
    if(!fgCircle)fgCircle = new TClonesArray("RHICfSimP", 1000);
    if(!fgGhost)fgGhost = new TClonesArray("RHICfSimP", 600);
    if(!fgNGhost)fgNGhost = new TClonesArray("RHICfSimP", 600);
    if(!fgP0Ghost)fgP0Ghost = new TClonesArray("RHICfSimP", 600);
    if(!fgNSignal)fgNSignal = new TClonesArray("RHICfSimP", 600);
    if(!fgP0Signal)fgP0Signal = new TClonesArray("RHICfSimP", 600);
    fIP = fgIP;
    fWPlate = fgWPlate;
    fZDCGhost = fgZDCGhost;
    fCircle = fgCircle;
    fGhost = fgGhost;
    fNGhost = fgNGhost;
    fP0Ghost = fgP0Ghost;
    fNSignal = fgNSignal;
    fP0Signal = fgP0Signal;
}


ParticlesInfo::~ParticlesInfo()
{
    Clear();
    delete fIP; fgIP = 0;
    delete fWPlate; fgWPlate = 0;
    delete fZDCGhost; fgZDCGhost = 0;
    delete fCircle; fgCircle = 0;
    delete fGhost; fgGhost = 0;
    delete fNGhost; fgNGhost = 0;
    delete fP0Ghost; fgP0Ghost = 0;
    delete fNSignal; fgNSignal = 0;
    delete fP0Signal; fgP0Signal = 0;
}

void ParticlesInfo::Reset()
{
    delete fIP; fgIP = 0;
    delete fWPlate; fgWPlate = 0;
    delete fZDCGhost; fgZDCGhost = 0;
    delete fCircle; fgCircle = 0;
    delete fGhost; fgGhost = 0;
    delete fNGhost; fgNGhost = 0;
    delete fP0Ghost; fgP0Ghost = 0;
    delete fNSignal; fgNSignal = 0;
    delete fP0Signal; fgP0Signal = 0;
}

void ParticlesInfo::Clear()
{
  // Clear the array of RHICfSimP. It don't delete RHICfSimP. 
  kRunNumber = 0;
  kEventNumber = 0;
  kSpin = -1;
  
  fIP->Clear("C");
  fWPlate->Clear("C");
  fZDCGhost->Clear("C");
  fCircle->Clear("C");
  fGhost->Clear("C");
  fNGhost->Clear("C");
  fP0Ghost->Clear("C");
  fNSignal->Clear("C");
  fP0Signal->Clear("C");
  
}

void ParticlesInfo::SetRunNumber(Int_t run)
{
    kRunNumber = run;
}
void ParticlesInfo::SetEventNumber(Int_t event)
{
    kEventNumber = event;
}

void ParticlesInfo::SetSpin(Int_t num)
{
    kSpin = num;
}

RHICfSimP* ParticlesInfo::AddToIP(Int_t inum)
{
    //Junsang****new(fIP[inum]) RHICfSimP(*rhs);
    RHICfSimP *tmpsimp = (RHICfSimP*)fIP->ConstructedAt(inum);
    //Junsang****tmpsimp = new RHICfSimP(*rhs);
    return tmpsimp;
}

RHICfSimP* ParticlesInfo::AddToWPlate(Int_t inum)
{
    //Junsang****new(fIP[inum]) RHICfSimP(*rhs);
    RHICfSimP *tmpsimp = (RHICfSimP*)fWPlate->ConstructedAt(inum);
    //Junsang****tmpsimp = new RHICfSimP(*rhs);
    return tmpsimp;
}

RHICfSimP* ParticlesInfo::AddToZDCGhost(Int_t inum)
{
    //Junsang****new(fZDCGhost[inum]) RHICfSimP(*rhs);
    RHICfSimP *tmpsimp = (RHICfSimP*)fZDCGhost->ConstructedAt(inum);
    //Junsang****tmpsimp = new RHICfSimP(*rhs);
    return tmpsimp;
}

RHICfSimP* ParticlesInfo::AddToCircle(Int_t inum)
{
    //Junsang****new(fCircle[inum]) RHICfSimP(*rhs);
    RHICfSimP *tmpsimp = (RHICfSimP*)fCircle->ConstructedAt(inum);
    //Junsang****tmpsimp = new RHICfSimP(*rhs);
    return tmpsimp;
}

RHICfSimP* ParticlesInfo::AddToGhost(Int_t inum)
{
    //Junsang****new(fNGhost[inum]) RHICfSimP(*rhs);
    RHICfSimP *tmpsimp = (RHICfSimP*)fGhost->ConstructedAt(inum);
    //Junsang****tmpsimp = new RHICfSimP(*rhs);
    return tmpsimp;
}

RHICfSimP* ParticlesInfo::AddToNGhost(Int_t inum)
{
    //Junsang****new(fNGhost[inum]) RHICfSimP(*rhs);
    RHICfSimP *tmpsimp = (RHICfSimP*)fNGhost->ConstructedAt(inum);
    //Junsang****tmpsimp = new RHICfSimP(*rhs);
    return tmpsimp;
}

RHICfSimP* ParticlesInfo::AddToP0Ghost(Int_t inum)
{
    //Junsang****new(fP0Ghost[inum]) RHICfSimP(*rhs);
    RHICfSimP *tmpsimp = (RHICfSimP*)fP0Ghost->ConstructedAt(inum);
    //Junsang****tmpsimp = new RHICfSimP(*rhs);
    return tmpsimp;
}

RHICfSimP* ParticlesInfo::AddToNSignal(Int_t inum)
{
    //Junsang****new(fNSignal[inum]) RHICfSimP(*rhs);
    RHICfSimP *tmpsimp = (RHICfSimP*)fNSignal->ConstructedAt(inum);
    //Junsang****tmpsimp = new RHICfSimP(*rhs);
    return tmpsimp;
}

RHICfSimP* ParticlesInfo::AddToP0Signal(Int_t inum)
{
    //Junsang****new(fP0Signal[inum]) RHICfSimP(*rhs);
    RHICfSimP *tmpsimp = (RHICfSimP*)fP0Signal->ConstructedAt(inum);
    //Junsang****tmpsimp = new RHICfSimP(*rhs);
    return tmpsimp;
}

RHICfSimP* ParticlesInfo::GetPFromIP(Int_t inum)
{
    return (RHICfSimP*)fIP->At(inum);
}
RHICfSimP* ParticlesInfo::GetPFromWPlate(Int_t inum)
{
    return (RHICfSimP*)fWPlate->At(inum);
}
RHICfSimP* ParticlesInfo::GetPFromZDCGhost(Int_t inum)
{
    return (RHICfSimP*)fZDCGhost->At(inum);
}
RHICfSimP* ParticlesInfo::GetPFromCircle(Int_t inum)
{
    return (RHICfSimP*)fCircle->At(inum);
}
RHICfSimP* ParticlesInfo::GetPFromGhost(Int_t inum)
{
    return (RHICfSimP*)fGhost->At(inum);
}
RHICfSimP* ParticlesInfo::GetPFromNGhost(Int_t inum)
{
    return (RHICfSimP*)fNGhost->At(inum);
}
RHICfSimP* ParticlesInfo::GetPFromP0Ghost(Int_t inum)
{
    return (RHICfSimP*)fP0Ghost->At(inum);
}
RHICfSimP* ParticlesInfo::GetPFromNSignal(Int_t inum)
{
    return (RHICfSimP*)fNSignal->At(inum);
}
RHICfSimP* ParticlesInfo::GetPFromP0Signal(Int_t inum)
{
    return (RHICfSimP*)fP0Signal->At(inum);
}



#endif
