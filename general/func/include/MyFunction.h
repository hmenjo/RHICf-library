#ifndef __MYFUNCTION_H__
#define __MYFUNCTION_H__

void PosShift(double &ix,double &iy,double sx,double sy);
void PosRotate(double &ix,double &iy,double theta);
void PosReflect(double &ix,double &iy);
int MyMax(int n,int *x);
int MyMax(int n,double *x);
int MyMin(int n,int *x);
int MyMin(int n,double *x);
double Chi2(int n,double *d1,double *d1_e,double *d2,double *d2_e);
int MySum(int n,int *d);
double MySum(int n,double *d);
double MyAverage(int n,int *d);
double MyAverage(int n,double *d);
double MyRMS(int n,double mean,double *d);
int MyFitFirstLinear(int n, double *X,double *Y,double &a, double &b);

class MyFilePath{
public:
  char base[256];
  char tmp[512];
public:
  MyFilePath(){;}
  ~MyFilePath(){;}
  MyFilePath(char *b);
  int   SetBase(char *b);
  int   SetDirectory(char *b);
  char* GetPath(char *b);
};

class SimpleList{
protected:
  int      nlist;
  char     list[200][256];
public:
  SimpleList(){;}
  SimpleList(char* file);
  int   Open(char* file);
  char* Get(int n);
  int   GetNlist(){return nlist;}
};

#endif
