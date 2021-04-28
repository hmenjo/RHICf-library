#ifndef __TLHCFDIPDATAL_H__
#define __TLHCFDIPDATAL_H__

#include "lhcfdipdata.h"
#include <TObject.h>
#include <TNamed.h>
using namespace std;

class TLHCFDIPDATAL : public TNamed {
 public:
  Int_t        run;
  Int_t        number;
  Int_t        time;
  LHCFDIPDATAL data;
  
 public:
  TLHCFDIPDATAL(){clear();}
  TLHCFDIPDATAL(char* name, char *title) : TNamed(name,title){clear();}
  ~TLHCFDIPDATAL(){;}
  
  LHCFDIPDATAL* GetData(){return &data;}
  
  void       clear();
  void       DataClear();
  void       Add(TLHCFDIPDATAL* d);
  void       Divide(double d);

  ClassDef(TLHCFDIPDATAL, 11);
};

#endif
