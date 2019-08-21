#ifndef __RHICFSIMINCIDENTS_H__
#define __RHICFSIMINCIDENTS_H__

#include <TNamed.h>
#include <TObjArray.h>
#include "RHICfSimP.h"

class RHICfSimIncidents : public TNamed {
 public:           
  int       run;        // Run Number
  int       number;     // Event number
  int       gnumber;    // Grobal event number
  
  int       np;         // Number of Incident Particle
  TObjArray particles;  // Array of RHICfSimP                
  
  int       ref[10];    //! temporal reference to RHICfSimP

 public:
  RHICfSimIncidents(){clear();}
  RHICfSimIncidents(char* name, char *title) : TNamed(name,title){clear();}
  ~RHICfSimIncidents(){Delete();}

  int     clear();
  int     copy(RHICfSimIncidents* );      // not yet
  int     copydata(RHICfSimIncidents* );  // not yet
  
  virtual void    Delete(Option_t *option=""){particles.Delete();}
  
  int     GetN(){return np;}
  void    Add(RHICfSimP* d);
  RHICfSimP* Get(int i){return (RHICfSimP*)(particles.At(i));}
  
  int     GetNHit(int id, int it, 
		  double ke_threshold=0.0,double edgecut=0.0,
		  double offsetx=RHICfSimP::GetOffset(0), 
		  double offsety=RHICfSimP::GetOffset(1));
          // Number of selected RHICfSimP are filled in ref[10];   
  RHICfSimP* GetHit(int id, int it, int ik=0,double edgecut=0.0,
		 double offsetx=RHICfSimP::GetOffset(0),
		 double offsety=RHICfSimP::GetOffset(0));
  int     GetRefNumber(int i){return ref[i];}
  RHICfSimP*   GetRef(int i){return Get(ref[i]);}
          // Can get particle from ref list after execution of GetNHit();   

  void    Show(int id=0,int it=0,
	       double ke_threshold=0.0,double edgecut=0.0,
	       double offsetx=RHICfSimP::GetOffset(0), 
	       double offsety=RHICfSimP::GetOffset(1));
  
  // -------- For Analysis ------------------------------ 
  static  double CalPi0Mass(RHICfSimP* p1, RHICfSimP* p2);
  static  double CalPi0Distance(RHICfSimP* p1, RHICfSimP* p2);
  static  double CalPi0Energy(RHICfSimP* p1, RHICfSimP* p2);
  static  double CalPi0Momentum(RHICfSimP* p1, RHICfSimP* p2,
				int dir,double offsetx=0.,double offsety=0.);
                  // [GeV/c] dir: 0=x,1=y,3=z
  static  double CalPi0Pt(RHICfSimP* p1, RHICfSimP* p2,
			  double offsetx=0.,double offsety=0.);
  ClassDef(RHICfSimIncidents,1);
};

#endif
