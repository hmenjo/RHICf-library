#ifndef __EVENTMARKER_CPP__
#define __EVENTMARKER_CPP__

#include "EventMarker.h"

#if !defined(__CINT__)
  ClassImp(EventMarker);
#endif

#include <iostream>
#include <iomanip>
using namespace std;

EventMarker::EventMarker(){
  ievent = 0;
  gnumber = 0;
  a1number = 0;
  a2number = 0;
  return ;
}

EventMarker::~EventMarker(){
  //   cerr << "Call delete" << endl;
  //   cout << *val << endl;
  *val = NULL;
  return ;
}

void EventMarker::SetMarkerColor(int c){
  TMarker::SetMarkerColor(c);
}

void EventMarker::DrawTag(){
  SetX((double)ievent);
  SetY(0.1);
  SetMarkerStyle(21);
  Draw();
}

#endif
