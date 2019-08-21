// ***********************************************************
// ****           Parameters List for frontend3           ****  
// ****  03 Jun. 08 : Improved by H.Menjo                 ****
// ****  08 Sep. 08 : Update "N_SC_SMON" by H.Menjo       ****
// ***********************************************************
 
// version 001  
// type    001

#ifndef FE3_FEPARAM
#define FE3_FEPARAM

// *** General parameter 
#define FE3_FEPARAM_VERSION      1
#define FE3_FEPARAM_TYPE         1
#define FE3_LOGFILE             "./frontend3_log"

#define SOCKET_PORT     4410
//#define SOCKET_SERVER   "localhost"
#define SOCKET_SERVER   "lhcfdaq3.cern.ch"

#endif

#ifndef GENERAL_SC_PARAMETER_LIST
#define GENERAL_SC_PARAMETER_LIST

#define N_SC_SMON    1752       // BYTE
#define N_SC_DIPH    1784       // BYTE
#define N_SC_DIPL  136632       // BYTE
#define N_SC_DIVH     128       // BYTE

#endif
