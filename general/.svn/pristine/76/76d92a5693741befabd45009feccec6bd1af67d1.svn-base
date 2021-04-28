#ifndef __EVENTMARKER_H__
#define __EVENTMARKER_H__

#include <TMarker.h>
#include <RQ_OBJECT.h>

class EventMarker : public TMarker {
 public:
  int     ievent;
  int     gnumber;
  int     a1number;
  int     a2number;
  char    message[256];
  EventMarker **val;      //!
 public:
  EventMarker();
  virtual ~EventMarker();
  
  int   GetEventNumber(){return ievent;}
  int   GetGNumber(){return gnumber;}
  int   GetA1Number(){return a1number;}
  int   GetA2Number(){return a2number;} 
  char* GetComment(){return message;}
  void  SetMarkerColor(int );
  void  SetEventNumber(int i){ievent = i;}
  void  SetGNumber(int i){ gnumber = i;}
  void  SetA1Number(int i){a1number = i;}
  void  SetA2Number(int i){a2number = i;} 
  void  SetComment(char *s){strncpy(message,s,256);}
  void  SetVal(EventMarker **v){val = v;}
  void  DrawTag();
  
  ClassDef(EventMarker,1);
};

#endif
