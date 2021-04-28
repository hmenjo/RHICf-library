#ifndef __TLHCFDIPDATAH_H__
#define __TLHCFDIPDATAH_H__

#include "lhcfdipdata.h"
#include <TObject.h>
#include <TNamed.h>
using namespace std;

class TLHCFDIPDATAH : public TNamed {
 public:
  Int_t        run;
  Int_t        number;
  Int_t        time;
  LHCFDIPDATAH data;
  
 public:
  TLHCFDIPDATAH(){clear();}
  TLHCFDIPDATAH(char* name, char *title) : TNamed(name,title){clear();}
  ~TLHCFDIPDATAH(){;}
  
  LHCFDIPDATAH* GetData(){return &data;}
  
  void       clear();
  void       DataClear();
  void       Add(TLHCFDIPDATAH* d);
  void       Divide(double d);

  ClassDef(TLHCFDIPDATAH, 6);
};

#endif
