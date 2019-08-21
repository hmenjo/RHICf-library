#ifndef __SOCKETCONTROL_H__
#define __SOCKETCONTROL_H__

#include <iostream>
#include <iomanip>
#include <string>
#include "lhcfsdata.h"
#include "lhcfdipdata.h"

class SocketControl{
 protected:
  bool   connection;
  int    sock;
  char   serverhost[100];
  
  int    lock;                   // 1:lock 0:unlock
     
 public:
  SocketControl(){Initialize();}
  SocketControl(const char* hostname);
  virtual ~SocketControl(){DisConnect();}
  
  virtual int   Initialize();
  virtual int   SetServer(const char *name="");
  virtual char* GetServer(){return serverhost;}
  virtual int   GetSocketID(){return sock;}
  virtual int   Connect();
  virtual int   DisConnect();
  virtual int   ConnectionRefused();
  virtual bool  IsConnection(){return connection;}
  virtual int   CheckConnection();
  virtual int   GetBinaryData(LHCFSDATA* d);
  virtual int   GetBinaryDataDipH(LHCFDIPDATAH* d);
  virtual int   GetBinaryDataDipL(LHCFDIPDATAL* d);
  virtual int   GetBinaryDataDipVH(LHCFDIPDATAVH* d);
  virtual int   SendCommand(char* command, char* answer, int size=0,
			   bool ret_answer=true, bool send_command=true);
  virtual int   SendProcedure(const char* com, char* answer);
  
  virtual bool IsConnect(){ return connection; }

  int    Lock();
  int    UnLock();
  int    IsLock(){return lock;}
  
 public:
  static const int   SOCKETCONTROL_OK     =  0;
  static const int   SOCKETCONTROL_ERROR  = -1;
  static const char* DEFULT_SERVERHOST;
  static const int   PORT = 4410;
  static const int   MAXDATA = 200000;  // 20kB

  static const int   MASK_ON       = 0x000F;
  static const int   MASK_ERROR    = 0x00F0;
  static const int   MASK_WARNIUNG = 0x0F00;
};




#endif 
