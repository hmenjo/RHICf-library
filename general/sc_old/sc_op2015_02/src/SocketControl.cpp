#ifndef __SOCKETCONTROL_CPP__
#define __SOCKETCONTROL_CPP__

#include "SocketControl.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include </usr/include/pthread.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
using namespace std;

const int SocketControl::SOCKETCONTROL_OK;
const int SocketControl::SOCKETCONTROL_ERROR;
const char* SocketControl::DEFULT_SERVERHOST = "localhost";
const int SocketControl::PORT;
const int SocketControl::MAXDATA;

const int SocketControl::MASK_ON;
const int SocketControl::MASK_ERROR;
const int SocketControl::MASK_WARNIUNG;

pthread_mutex_t socketcontrol_mutex;

//////////////////////////////////////////////////////////
// Rapper Function for socket (2017/04/28 Menjo)
// In c++11, socket does not work. 
int SocketControl::SocketOpen(){
  sock = -1;
#if __cplusplus < 201103L 
  sock = socket (PF_INET, SOCK_STREAM, 0);
  if (sock < 0){
	 char err[256];
	 sprintf(err,"Command socket returned %d", sock);
	 perror(err);
    return SOCKETCONTROL_ERROR;
  }
#else
  perror("SOCKET DOES NOT WORK WITH C++11");
  return SOCKETCONTROL_ERROR;
#endif
  return SOCKETCONTROL_OK;
}

int SocketControl::SocketConnect(char serverhostname[]){

#if __cplusplus < 201103L 
  struct sockaddr_in servername;
  struct hostent *hostinfo;
  
  servername.sin_family = AF_INET;
  servername.sin_port = htons (PORT);
  hostinfo = gethostbyname ( serverhostname );
  if (hostinfo == NULL){
    cerr << "Unknown host " << serverhostname << endl;
    return SOCKETCONTROL_ERROR;
  }
  servername.sin_addr.s_addr=*(unsigned int *)(*(hostinfo->h_addr_list));
  
  if (connect(sock,(struct sockaddr *)&servername,sizeof(servername))<0) {
    perror("Connection Error");
    return SOCKETCONTROL_ERROR;
  }
#else
  return SOCKETCONTROL_ERROR;
#endif
  return SOCKETCONTROL_OK;
}

void SocketControl::SocketClose(){
#if __cplusplus < 201103L 
  close (sock);
#endif 
  return ;
}

int SocketControl::SocketWrite(char* val, int n){
  int nbytes = 0;
#if __cplusplus < 201103L 
  nbytes = write (sock, val, n);
#endif 
  return nbytes;
}

int SocketControl::SocketRead(char* val, int n){
  int nbytes = 0;
#if __cplusplus < 201103L 
  nbytes = read (sock, val, n);
#endif
  return nbytes;
}

int SocketControl::SocketRecv(char* val, int n, int m){
  int nbytes = 0;
#if __cplusplus < 201103L 
  nbytes = SocketRecv(val, n, m);
#endif
  return nbytes;
}

////////////////////////////////////////////////////////

SocketControl::SocketControl(const char* hostname){
  Initialize();
  SetServer(hostname);
  Connect();
}

int SocketControl::Initialize(){
  connection = false;
  strcpy(serverhost,DEFULT_SERVERHOST);
  pthread_mutex_init(&socketcontrol_mutex, NULL);
  lock = 0;
  return SOCKETCONTROL_OK;
}

int SocketControl::SetServer(const char *name){
  if(strcmp(name,"")==0){
    strcpy(serverhost,DEFULT_SERVERHOST);
    return SOCKETCONTROL_OK;
  }
  strcpy(serverhost,name);
  return SOCKETCONTROL_OK;
}

int SocketControl::Connect(){

  if(SocketOpen() != SOCKETCONTROL_OK){
	 return SOCKETCONTROL_ERROR;
  }

  if(SocketConnect(serverhost) == SOCKETCONTROL_OK){
	 connection = true;
	 cout << "Connected "<< serverhost  << endl;
	 return SOCKETCONTROL_OK;
  }
  else{
	 return SOCKETCONTROL_ERROR;
  }
}

int SocketControl::DisConnect(){
  if(connection==false){return SOCKETCONTROL_OK;}

  char command[] = "quit";
  char answer[256];
  SendCommand(command,answer,256,false);
  SocketClose();
  connection = false;
  cout << "Disconnected " << serverhost << endl;
  
  return SOCKETCONTROL_OK;
}

int SocketControl::ConnectionRefused(){
  SocketClose();
  connection = false;
  lock = 0;
  cerr << "Connection refused " << endl;
  return SOCKETCONTROL_OK;
}

int SocketControl::CheckConnection(){
  if(connection){
    char com[256] = "testconn";
    char res[256] = "";
    int check;
    int i;
    //cerr << "SocketControl::CheckConnection" << endl;
    for(i=0;i<5;i++){
      check = SendCommand(com,res,256,true);
      if(check==SOCKETCONTROL_OK && strlen(res)>0){break;}
    }
    if(i>=4){
      ConnectionRefused();
      return SOCKETCONTROL_ERROR;  
    }
    else{
      return SOCKETCONTROL_OK;
    }
  }
  else{
    return SOCKETCONTROL_ERROR;
  }
}

int SocketControl::SendCommand(char* com, char* answer, int size,
			       bool ret_answer, bool send_command){

//   pthread_mutex_lock(&socketcontrol_mutex);

  int  i=0;
  int  numbytes=0;
  int  nbytes=0;
  char command[256];
  static char resp[MAXDATA];
  
  strcpy(command,com);

  if(size==0){size = MAXDATA;}
  
  ostringstream sout;
  sout.str("");
  
  if(connection==false){
    strcpy(answer," !! Not Connect yet !! \n");
    return SOCKETCONTROL_ERROR;
  }

  if(send_command==true){ 
    while(command[i]==' ') i++;
    numbytes=strlen(command);
    command[numbytes]='\0';

    nbytes = SocketWrite( command+i, numbytes+1-i);
    if (nbytes < 0) {
      strcpy(answer," !! Error in write() of socket !!\n");
      return SOCKETCONTROL_ERROR;
    }
  }
  
  if(ret_answer==true){
    
    nbytes = SocketRead(resp, MAXDATA);

    if(nbytes<0){
      strcpy(answer," !! Error in read() of socket !!\n");
      return SOCKETCONTROL_ERROR;
    }
    
    if(nbytes > size){
      sprintf(answer," !! Data size is over %d bytes !!",size);
      return SOCKETCONTROL_ERROR;
    }
    
    for(int j=0;j<nbytes;j++){
      answer[j] = resp[j];
    } 
  }
  
//   mutex.UnLock();
//   pthread_mutex_unlock(&socketcontrol_mutex);

  return SOCKETCONTROL_OK;
}


int SocketControl::SendProcedure(const char* com, char* answer){
  int i=0;
  char command[256];
  char resp[MAXDATA];
  int  nbytes=0,numbytes;
  ostringstream sout;

  // send command +++++++++++++++++++++++++++++++++++++
  strcpy(command,com);
  i=0;
  while(command[i]==' ') i++;
  numbytes=strlen(command);
  command[numbytes]='\0';
  
  nbytes = SocketWrite( command+i, numbytes+1-i);
  if (nbytes < 0) {
    strcpy(answer," !! Error in write() of socket !!\n");
    return SOCKETCONTROL_ERROR;
  }
  
  // recieve number of commands ++++++++++++++++++++++
  nbytes = SocketRead(resp, MAXDATA);
  if(nbytes<0){
    strcpy(answer," !! Error in read() of socket !!\n");
    return SOCKETCONTROL_ERROR;
  }

  // recieve results +++++++++++++++++++++++++++++++++
  int  nproccmd=0;
  char tmpchar[20];
  if(strncmp(resp,"nproccmd",8)==0){  
    sscanf(resp,"%s %d",tmpchar,&nproccmd);
    sout << "Number of commands in procedure: "<<nproccmd<<endl;

    for(i=0;i<2*nproccmd;i++){
      strcpy(resp,"\0"); 
      nbytes = SocketRead(resp, MAXDATA); 
      if ((i%2)==0) {
	resp[strlen(resp)-1]='\0';
	sout << "  "<<i/2+1<<") ";
      }
      else sout<<"     ";
      if (strncmp(resp,"ERROR",5)==0){       //Break in case of errors.
	sout <<resp<<endl;
	break;
      }
      else{
	sout <<resp<<endl;
      }
    }
  }
  else{
    if(strncmp(resp,"ERROR",5)==0) sout << resp <<endl;
    else cout << resp <<endl;
  }

  strcpy(answer,sout.str().c_str());
  if(strstr(answer,"successfully executed")!=NULL){
    return SOCKETCONTROL_OK;
  }
  else{
    return SOCKETCONTROL_ERROR;
  }
}

int SocketControl::GetBinaryData(LHCFSDATA* d){
  int  nbytes=0,tmpnbytes;
  int  numbytes=0;
  char command[] = "bread";
  char answer[MAXDATA];
  
  if(connection==false){
    return SOCKETCONTROL_ERROR;
  }

  numbytes=strlen(command);
  command[numbytes]='\0';

  if(Lock()!=SOCKETCONTROL_OK){
    return SOCKETCONTROL_ERROR;
  }
  
  nbytes = SocketWrite( command,numbytes+1);
  if (nbytes < 0) {
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  // Reciave binary data from S.C. server
  nbytes = 0;
  while(1){

    tmpnbytes = SocketRecv(&(answer[nbytes]),MAXDATA-nbytes,0);
    if (tmpnbytes < 0){
      UnLock();
      return SOCKETCONTROL_ERROR;
    }
    else if(tmpnbytes==0){
      break;
    }
    nbytes += tmpnbytes;

    if(nbytes>=LHCFSDATA::GetClassSize()){break;}
  }

  // Check format of  binary data;
  LHCFSDATA* stmp = (LHCFSDATA*) answer;
  if(stmp->GetVersion()!=LHCFSDATA::GetClassVersion()){
    cerr << "[SocketControl::GetBinaryData] " 
	 << "Reciaved data have invalit vertion number: " 
	 << stmp->GetVersion() << ".  "
	 << "Should be " << LHCFSDATA::GetClassVersion()
	 << endl;
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  if(stmp->GetSize()!=LHCFSDATA::GetClassSize()){
    cerr << "[SocketControl::GetBinaryData] " 
	 << "Reciaved data have invalit size: " 
	 << stmp->GetSize() << ".  "
	 << "Should be " << LHCFSDATA::GetClassSize()
	 << endl;
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  // Copy data.
  memcpy((char*)d, answer, LHCFSDATA::GetClassSize()); 
  
#ifdef FDEBUG
  cout << "[SocketControl::GetBinaryData] Reciaved data: " 
       << "VERSION=" << d->GetVersion() << "  " 
       << "ADC.cal[9]=" << d->adc.cal[9] << endl;
#endif 
  
  UnLock();
  
  return SOCKETCONTROL_OK;
}

int SocketControl::GetBinaryDataDipH(LHCFDIPDATAH* d){
  int  nbytes=0,tmpnbytes;
  int  numbytes=0;
  char command[] = "breaddiph";
  char answer[MAXDATA];
  
  if(connection==false){
    return SOCKETCONTROL_ERROR;
  }

  numbytes=strlen(command);
  command[numbytes]='\0';

  if(Lock()!=SOCKETCONTROL_OK){
    return SOCKETCONTROL_ERROR;
  }
  
  nbytes = SocketWrite( command,numbytes+1);
  if (nbytes < 0) {
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  // Reciave binary data from S.C. server
  nbytes = 0;
  while(1){

    tmpnbytes = SocketRecv(&(answer[nbytes]),MAXDATA-nbytes,0);
    if (tmpnbytes < 0){
      UnLock();
      return SOCKETCONTROL_ERROR;
    }
    else if(tmpnbytes==0){
      break;
    }
    nbytes += tmpnbytes;

    if(nbytes>=LHCFDIPDATAH::GetClassSize()){break;}
  }

  // Check format of  binary data;
  LHCFDIPDATAH* stmp = (LHCFDIPDATAH*) answer;
  if(stmp->GetVersion()!=LHCFDIPDATAH::GetClassVersion()){
    cerr << "[SocketControl::GetBinaryDataDipH] " 
	 << "Reciaved data have invalit vertion number: " 
	 << stmp->GetVersion() << ".  "
	 << "Should be " << LHCFDIPDATAH::GetClassVersion()
	 << endl;
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  if(stmp->GetSize()!=LHCFDIPDATAH::GetClassSize()){
    cerr << "[SocketControl::GetBinaryData] " 
	 << "Reciaved data have invalit size: " 
	 << stmp->GetSize() << ".  "
	 << "Should be " << LHCFDIPDATAH::GetClassSize()
	 << endl; 
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  // Copy data.
  memcpy((char*)d, answer, LHCFDIPDATAH::GetClassSize()); 
  
#ifdef FDEBUG
  cout << "[SocketControl::GetBinaryDataDipH] Reciaved data: " 
       << "VERSION=" << d->GetVersion() << endl;
#endif 
  
  UnLock();
  
  return SOCKETCONTROL_OK;
}

int SocketControl::GetBinaryDataDipL(LHCFDIPDATAL* d){
  int  nbytes=0,tmpnbytes;
  int  numbytes=0;
  char command[] = "breaddipl";
  char answer[MAXDATA];
  
  if(connection==false){
    return SOCKETCONTROL_ERROR;
  }

  numbytes=strlen(command);
  command[numbytes]='\0';

  if(Lock()!=SOCKETCONTROL_OK){
    return SOCKETCONTROL_ERROR;
  }
  
  nbytes = SocketWrite( command,numbytes+1);
  if (nbytes < 0) {
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  // Reciave binary data from S.C. server
  nbytes = 0;
  while(1){

    tmpnbytes = SocketRecv(&(answer[nbytes]),MAXDATA-nbytes,0);
    if (tmpnbytes < 0){
       UnLock();
       return SOCKETCONTROL_ERROR;
    }
    else if(tmpnbytes==0){
      break;
    }
    nbytes += tmpnbytes;

    if(nbytes>=LHCFDIPDATAL::GetClassSize()){break;}
  }

  // Check format of  binary data;
  LHCFDIPDATAL* stmp = (LHCFDIPDATAL*) answer;
  if(stmp->GetVersion()!=LHCFDIPDATAL::GetClassVersion()){
    cerr << "[SocketControl::GetBinaryDataDipL] " 
	 << "Reciaved data have invalit vertion number: " 
	 << stmp->GetVersion() << ".  "
	 << "Should be " << LHCFDIPDATAL::GetClassVersion()
	 << endl;
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  if(stmp->GetSize()!=LHCFDIPDATAL::GetClassSize()){
    cerr << "[SocketControl::GetBinaryData] " 
	 << "Reciaved data have invalit size: " 
	 << stmp->GetSize() << ".  "
	 << "Should be " << LHCFDIPDATAL::GetClassSize()
	 << endl;
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  // Copy data.
  memcpy((char*)d, answer, LHCFDIPDATAL::GetClassSize()); 
  
#ifdef FDEBUG
  cout << "[SocketControl::GetBinaryDataDipL] Reciaved data: " 
       << "VERSION=" << d->GetVersion() << endl;
#endif 
  
  UnLock();
  
  return SOCKETCONTROL_OK;
}

int SocketControl::GetBinaryDataDipVH(LHCFDIPDATAVH* d){
  int  nbytes=0,tmpnbytes;
  int  numbytes=0;
  char command[] = "breaddipvh";
  char answer[MAXDATA];
  
  if(connection==false){
    return SOCKETCONTROL_ERROR;
  }

  numbytes=strlen(command);
  command[numbytes]='\0';

  if(Lock()!=SOCKETCONTROL_OK){
    return SOCKETCONTROL_ERROR;
  }
  
  nbytes = SocketWrite(command,numbytes+1);
  if (nbytes < 0) {
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  // Reciave binary data from S.C. server
  nbytes = 0;
  while(1){

    tmpnbytes = SocketRecv(&(answer[nbytes]),MAXDATA-nbytes,0);
    if (tmpnbytes < 0){ 
      UnLock();
      return SOCKETCONTROL_ERROR;
    }
    else if(tmpnbytes==0){
      break;
    }
    nbytes += tmpnbytes;

    if(nbytes>=LHCFDIPDATAVH::GetClassSize()){break;}
  }

  // Check format of  binary data;
  LHCFDIPDATAVH* stmp = (LHCFDIPDATAVH*) answer;
  if(stmp->GetVersion()!=LHCFDIPDATAVH::GetClassVersion()){
    cerr << "[SocketControl::GetBinaryDataDipVH] " 
	 << "Reciaved data have invalit vertion number: " 
	 << stmp->GetVersion() << ".  "
	 << "Should be " << LHCFDIPDATAVH::GetClassVersion()
	 << endl;
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  if(stmp->GetSize()!=LHCFDIPDATAVH::GetClassSize()){
    cerr << "[SocketControl::GetBinaryData] " 
	 << "Reciaved data have invalit size: " 
	 << stmp->GetSize() << ".  "
	 << "Should be " << LHCFDIPDATAVH::GetClassSize()
	 << endl;
    UnLock();
    return SOCKETCONTROL_ERROR;
  }
  
  // Copy data.
  memcpy((char*)d, answer, LHCFDIPDATAVH::GetClassSize()); 
  
#ifdef FDEBUG
  cout << "[SocketControl::GetBinaryDataDipVH] Reciaved data: " 
       << "VERSION=" << d->GetVersion() << "  " << endl;
#endif 
  
  UnLock();
  
  return SOCKETCONTROL_OK;
}

int SocketControl::Lock(){
  if(lock==0){
    lock = 1;
    return SOCKETCONTROL_OK;
  }
  else{
    cerr << "Already Locked." << endl;
    return SOCKETCONTROL_ERROR;
  }
}

int SocketControl::UnLock(){
  if(lock==1){
    lock = 0;
    return SOCKETCONTROL_OK;
  }
  else{   
    cerr << "Already UnLocked." << endl;
    return SOCKETCONTROL_ERROR;
  }
}

#endif 
