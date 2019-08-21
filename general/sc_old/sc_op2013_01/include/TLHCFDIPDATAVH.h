#ifndef __TLHCFDIPDATAVH_H__
#define __TLHCFDIPDATAVH_H__

#include "lhcfdipdata.h"
#include <TObject.h>
#include <TNamed.h>
using namespace std;

class TLHCFDIPDATAVH : public TNamed {
 public:
  Int_t        run;
  Int_t        number;
  Int_t        time;
  LHCFDIPDATAVH data;
  
 public:
  TLHCFDIPDATAVH(){clear();}
  TLHCFDIPDATAVH(char* name, char *title) : TNamed(name,title){clear();}
  ~TLHCFDIPDATAVH(){;}
  
  LHCFDIPDATAVH* GetData(){return &data;}
  
  void       clear();
  void       DataClear();
  void       Add(TLHCFDIPDATAVH* d);
  void       Divide(double d);

  ClassDef(TLHCFDIPDATAVH, 11);
};

#endif
