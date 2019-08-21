#include <iostream>
#include <iomanip>
using namespace std;

#include "lhcfdipdata.h"
#include "lhcfsdata.h"
#include "feparam_fe3.h"

int main(){
  
  cout << "LHCFSDATA     : " << setw(6) << sizeof(LHCFSDATA) 
       <<  " <-> " << setw(6) << N_SC_SMON << endl
       << "LHCFDIPDATAH  : " << setw(6)<< sizeof(LHCFDIPDATAH) 
       <<  " <-> " << setw(6) << N_SC_DIPH << endl
       << "LHCFDIPDATAL  : " << setw(6)<< sizeof(LHCFDIPDATAL) 
       <<  " <-> " << setw(6) << N_SC_DIPL << endl
       << "LHCFDIPDATAVH : " << setw(6) << sizeof(LHCFDIPDATAVH)  
       <<  " <-> " << setw(6) << N_SC_DIVH << endl;

  return 0;
}
