#ifndef __LHCFEVENT_CPP__
#define __LHCFEVENT_CPP__

#include "LHCfEvent.h"

#if !defined(__CINT__)
ClassImp(LHCfEvent);
#endif

#include <iostream>
#include <iomanip>
using namespace std;

//______________________________________________________________________________
void LHCfEvent::Initialize(){
  // Initalization of this class.  
  // Clear all data.

  Clear();
}

void LHCfEvent::Delete(){
  ObjDelete();
}

void LHCfEvent::HeaderClear(){
  this->SetName("");
  this->SetTitle("");
  run = 0;
  gnumber = 0;
  a1number = 0;
  a2number = 0;
  a1flag[0] = 0;
  a1flag[1] = 0;
  a2flag[0] = 0;
  a2flag[1] = 0; 
  ifile = 0;
  tnumber = 0;
  tag = 0;
  tmp = 0;

  return ;
}

void  LHCfEvent::HeaderCopy(LHCfEvent* d){ 
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  this->run = d->run;
  this->gnumber = d->gnumber;
  this->a1number = d->a1number;
  this->a2number = d->a2number; 
  this->a1flag[0] = d->a1flag[0];
  this->a1flag[1] = d->a1flag[1];
  this->a2flag[0] = d->a2flag[0];
  this->a2flag[1] = d->a2flag[1]; 
  this->ifile = d->ifile;
  this->tnumber = d->tnumber;
  this->tag = d->tnumber;
  this->tmp = d->tmp;
  return ;
}

int LHCfEvent::EventTime(){
  if(Check("a1scl")) {return (int)(((A1Scl*)Get("a1scl"))->time[0]);}
  if(Check("a2scl")) {return (int)(((A2Scl*)Get("a2scl"))->time[0]);}
  if(Check("a1raw")) {return (int)(((A1Raw*)Get("a1raw"))->time[0]);}
  if(Check("a2raw")) {return (int)(((A2Raw*)Get("a2raw"))->time[0]);}
  if(Check("a1cal1")){return (int)(((A1Cal1*)Get("a1cal1"))->time[0]);}
  if(Check("a2cal1")){return (int)(((A2Cal1*)Get("a2cal1"))->time[0]);}
  if(Check("a1cal2")){return (int)(((A1Cal2*)Get("a1cal2"))->time[0]);}
  if(Check("a2cal2")){return (int)(((A2Cal2*)Get("a2cal2"))->time[0]);}
  if(Check("a1phys")){return (int)(((A1Phys*)Get("a1phys"))->time[0]);}
  if(Check("a2phys")){return (int)(((A2Phys*)Get("a2phys"))->time[0]);}
  return -1;
}

void LHCfEvent::Show(){
  cout << " ==========================  LHCfEvent "
       << "===============================" << endl;
  cout << " NAME: " << setw(10) <<  GetName() << "     "
       << "TITLE: " <<  GetTitle() << endl
       << " RUN: " << setw(5) << run << "  "
       << "GEVENT: " << setw(8) << gnumber << "   "
       << "A1NUMBER: " << setw(8) << a1number << "  "
       << "A2NUMBER: " << setw(8) << a2number << endl
       << " A1FLAGS:  "  
       << "0x" << setw(8) << hex << setfill('0') << a1flag[0] << "  "
       << "0x" << setw(8) << hex << setfill('0') << a1flag[1] << "     "
       << "A2FLAGS:  "
       << "0x" << setw(8) << hex << setfill('0') << a2flag[0] << "  "
       << "0x" << setw(8) << hex << setfill('0') << a2flag[1] << endl
       << dec << setfill(' ')
       << " IFILE: " << setw(6) << ifile << "   "
       << "TNUMBER: " <<  setw(8) << tnumber << "   "
       << "TAG: " << "0x" << setw(8) << hex << setfill('0') << tag << "       "
       << "TMP: " << dec << setfill(' ') << tmp << endl;
  
  TObject *obj;
  obj = (TObject*)objarray.First();
  cout << left ;
  cout << "   OBJs ---CLASS----  ---NAME---    ---------TITLE---------------" 
       << endl;
  for(int i=0;i<100;i++){ 
    if(obj==0){break;}
    cout << "    " << setw(2) << i << "  " 
	 << setw(12) << obj->ClassName() << "  " 
	 << setw(10) << obj->GetName() << "    "
	 << obj->GetTitle() << endl;
    obj = (TObject*)objarray.After(obj); 
  }  
  cout << right ;
}

#endif
