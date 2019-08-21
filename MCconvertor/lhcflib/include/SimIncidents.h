#ifndef __SIMINCIDENTS_H__
#define __SIMINCIDENTS_H__

#include <TNamed.h>
#include <TObjArray.h>
#include "globaldef.h"
#include "SimP.h"

class SimIncidents : public TNamed {
 public:           
  int       run;        // Run Number
  int       number;     // Event number
  int       gnumber;    // Grobal event number
  
  int       np;         // Number of Incident Particle
  TObjArray particles;  // Array of SimP                
  
  int       ref[10];    //! temporal reference to SimP

 public:
  SimIncidents(){clear();}
  SimIncidents(char* name, char *title) : TNamed(name,title){clear();}
  ~SimIncidents(){Delete();}

  int     clear();
  int     copy(SimIncidents* );      // not yet
  int     copydata(SimIncidents* );  // not yet
  
  void    Delete(){particles.Delete();}
  
  int     GetN(){return np;}
  void    Add(SimP* d);
  SimP*   Get(int i){return (SimP*)(particles.At(i));}
  
  int     GetNHit(int id, int it, 
		  double ke_threshold=0.0,double edgecut=0.0,
		  double offsetx=SimP::GetOffset(0), 
		  double offsety=SimP::GetOffset(1));
          // Number of selected SimP are filled in ref[10];   
  SimP*   GetHit(int id, int it, int ik=0,double edgecut=0.0,
		 double offsetx=SimP::GetOffset(0),
		 double offsety=SimP::GetOffset(0));
  int     GetRefNumber(int i){return ref[i];}
  SimP*   GetRef(int i){return Get(ref[i]);}
          // Can get particle from ref list after execution of GetNHit();   

  void    Show(int id=0,int it=0,
	       double ke_threshold=0.0,double edgecut=0.0,
	       double offsetx=SimP::GetOffset(0), 
	       double offsety=SimP::GetOffset(1));
  
  // -------- For Analysis ------------------------------ 
  static  double CalPi0Mass(SimP* p1, SimP* p2);
  static  double CalPi0Distance(SimP* p1, SimP* p2);
  static  double CalPi0Energy(SimP* p1, SimP* p2);
  static  double CalPi0Momentum(SimP* p1, SimP* p2,
				int dir,double offsetx=0.,double offsety=0.);
                  // [GeV/c] dir: 0=x,1=y,3=z
  static  double CalPi0Pt(SimP* p1, SimP* p2,
			  double offsetx=0.,double offsety=0.);
  ClassDef(SimIncidents,1);
};

#endif
