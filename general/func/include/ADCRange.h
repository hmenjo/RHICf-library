#ifndef  __ADCRANGE_H__
#define  __ADCRANGE_H__

//-----------------------------------------------------------------
//                         ADCRange  
//-----------------------------------------------------------------

#include <TObject.h>

class ADCRange{
public:
  static const char*  ADCRANGE_FORMAT;
  static const int    ADCRANGE_NADC = 4;
  static const int    ADCRANGE_NPARAM = 2;
  static const int    ADCRANGE_OK = 0;
  static const int    ADCRANGE_ERROR = 1;
  static const double DEFAULT_THRESHOLD;
  
  char   tablefile[256];
  char   format[256];
  int    type;
  int    version;

  // 4 adc+16 ch+2 parameters
  double param[ADCRANGE_NADC][16][ADCRANGE_NPARAM]; 
  double threshold;

public:
  ADCRange();
  ADCRange(char* file);
  virtual ~ADCRange(){;}
  
  int    Initialize();
  int    ReadFile(char* file);
  int    WriteFile(int t,char* file,char comment[] = "");

  int    SetThresold(double th){threshold = th;return ADCRANGE_OK;}
  double GetThresold(){return threshold;}
  int    SetParameters(int iadc,int ich, double p[]);
  int    SetParameter(int iadc,int ich, int ip, double p);
  double GetParameter(int iadc,int ich, int ip);
  double Get(int iadc,int ich, double adcr, double adch);

  ClassDef(ADCRange,1);   // Conbine the dual range of ADC CAEN V965.
};

#endif
