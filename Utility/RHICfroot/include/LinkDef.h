#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ function RHICfEvents_Show(TTree* , int );
#pragma link C++ function RHICfEvents_Show(TFile* , int );
#pragma link C++ function RHICfEvents_Show(int );
#pragma link C++ function RHICfEvents_Get(TTree*, const int, const TString);
#pragma link C++ function RHICfEvents_Get(const int, const TString);
#pragma link C++ function RHICfEvents_GetRaw(const int );
#pragma link C++ function RHICfEvents_GetCal1(const int );
#pragma link C++ function RHICfEvents_GetCal2(const int );
#pragma link C++ function RHICfEvents_GetPhys(const int );
#pragma link C++ function RHICfEvents_GetRec(const int );
#pragma link C++ function RHICfEvents_GetSimin(const int );

#pragma link C++ function RHICfEvents_GetRec_Show(const int );

#endif
