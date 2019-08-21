/********************************************************************\

  Name:         experim.h
  Created by:   ODBedit program

  Contents:     This file contains C structures for the "Experiment"
                tree in the ODB and the "/Analyzer/Parameters" tree.

                Additionally, it contains the "Settings" subtree for
                all items listed under "/Equipment" as well as their
                event definition.

                It can be used by the frontend and analyzer to work
                with these information.

                All C structures are accompanied with a string represen-
                tation which can be used in the db_create_record function
                to setup an ODB structure which matches the C structure.

  Created on:   Sun May  3 18:04:37 2015

\********************************************************************/

#ifndef EXCL_TRIGGER1

#define TRIGGER1_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
} TRIGGER1_COMMON;

#define TRIGGER1_COMMON_STR(_name) char *_name[] = {\
"[.]",\
"Event ID = WORD : 1",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 2",\
"Source = INT : 16777215",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : y",\
"Read on = INT : 257",\
"Period = INT : 200",\
"Event limit = DOUBLE : 0",\
"Num subevents = DWORD : 0",\
"Log history = INT : 0",\
"Frontend host = STRING : [32] lhcfds1.cern.ch",\
"Frontend name = STRING : [32] ARM1_frontend",\
"Frontend file name = STRING : [256] frontend_arm1.cpp",\
"",\
NULL }

#endif

#ifndef EXCL_SCALER1

#define SCALER1_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
} SCALER1_COMMON;

#define SCALER1_COMMON_STR(_name) char *_name[] = {\
"[.]",\
"Event ID = WORD : 2",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 17",\
"Source = INT : 0",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : y",\
"Read on = INT : 505",\
"Period = INT : 10000",\
"Event limit = DOUBLE : 0",\
"Num subevents = DWORD : 0",\
"Log history = INT : 0",\
"Frontend host = STRING : [32] lhcfds1.cern.ch",\
"Frontend name = STRING : [32] ARM1_frontend",\
"Frontend file name = STRING : [256] frontend_arm1.cpp",\
"",\
NULL }

#endif

#ifndef EXCL_TRIGGER2

#define TRIGGER2_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
} TRIGGER2_COMMON;

#define TRIGGER2_COMMON_STR(_name) char *_name[] = {\
"[.]",\
"Event ID = WORD : 3",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 2",\
"Source = INT : 16777215",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : y",\
"Read on = INT : 257",\
"Period = INT : 200",\
"Event limit = DOUBLE : 0",\
"Num subevents = DWORD : 0",\
"Log history = INT : 0",\
"Frontend host = STRING : [32] lhcfdaq15.cern.ch",\
"Frontend name = STRING : [32] ARM2_frontend",\
"Frontend file name = STRING : [256] frontend_arm2.cpp",\
"",\
NULL }

#endif

#ifndef EXCL_SCALER2

#define SCALER2_COMMON_DEFINED

typedef struct {
  WORD      event_id;
  WORD      trigger_mask;
  char      buffer[32];
  INT       type;
  INT       source;
  char      format[8];
  BOOL      enabled;
  INT       read_on;
  INT       period;
  double    event_limit;
  DWORD     num_subevents;
  INT       log_history;
  char      frontend_host[32];
  char      frontend_name[32];
  char      frontend_file_name[256];
} SCALER2_COMMON;

#define SCALER2_COMMON_STR(_name) char *_name[] = {\
"[.]",\
"Event ID = WORD : 4",\
"Trigger mask = WORD : 0",\
"Buffer = STRING : [32] SYSTEM",\
"Type = INT : 17",\
"Source = INT : 0",\
"Format = STRING : [8] MIDAS",\
"Enabled = BOOL : y",\
"Read on = INT : 505",\
"Period = INT : 10000",\
"Event limit = DOUBLE : 0",\
"Num subevents = DWORD : 0",\
"Log history = INT : 0",\
"Frontend host = STRING : [32] lhcfdaq15.cern.ch",\
"Frontend name = STRING : [32] ARM2_frontend",\
"Frontend file name = STRING : [256] frontend_arm2.cpp",\
"",\
NULL }

#endif

