// ***********************************************************
// ****           Parameters List for frontend3           ****  
// ****  03 Jun. 08 : Improved by H.Menjo                 ****
// ****  08 Sep. 08 : Update "N_SC_SMON" by H.Menjo       ****
// ****  13 Jan. 13 : Update for p-Pb operaton by Menjo   ****
// ****               N_SC_DIPH    6664 ->  41176         ****
// ****               N_SC_DIPL  174856 -> 621512         ****
// ****               FE3_FEPARAM_VERSION 1 -> 2          **** 
// ***********************************************************
 
// version 001  
// type    001

#ifndef FE3_FEPARAM
#define FE3_FEPARAM

// *** General parameter 
#define FE3_FEPARAM_VERSION      2
#define FE3_FEPARAM_TYPE         1
#define FE3_LOGFILE             "./frontend3_log"

#define SOCKET_PORT     4410
//#define SOCKET_SERVER   "localhost"
#define SOCKET_SERVER   "lhcfdaq9.cern.ch"

#endif

#ifndef GENERAL_SC_PARAMETER_LIST
#define GENERAL_SC_PARAMETER_LIST

#define N_SC_SMON    1752       // BYTE
#define N_SC_DIPH   41176       // BYTE
#define N_SC_DIPL  621512       // BYTE
#define N_SC_DIVH     128       // BYTE

#endif
