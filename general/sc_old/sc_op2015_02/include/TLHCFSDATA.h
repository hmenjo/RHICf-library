#ifndef __TLHCFSDATA_H__
#define __TLHCFSDATA_H__

#include "lhcfsdata.h"
#include <TObject.h>
#include <TNamed.h>
using namespace std;

class TLHCFSDATA : public TNamed {
 public:
  Int_t        run;
  Int_t        number;
  Int_t        time;
  LHCFSDATA    data;
  
 public:
  TLHCFSDATA(){clear();}
  TLHCFSDATA(char* name, char *title) : TNamed(name,title){clear();}
  ~TLHCFSDATA(){;}
  
  LHCFSDATA* GetData(){return &data;}
  
  void       clear();
  void       DataClear();
  void       Add(TLHCFSDATA* d);
  void       Divide(double d);

  ClassDef(TLHCFSDATA, 1);
};

#endif
