#ifndef __MYFUNCTION_CPP__
#define __MYFUNCTION_CPP__

#include "MyFunction.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <math.h>
#include <cstdio>
using namespace std;

#ifndef PI
#define PI 3.141592654
#endif

void PosShift(double &ix,double &iy,double sx,double sy){
  ix += sx;
  iy += sy;
}

void PosRotate(double &ix,double &iy,double theta){
  double x = ix;
  double y = iy;
  ix = x*cos(theta) - y*sin(theta);
  iy = x*sin(theta) + y*cos(theta);
}

void PosReflect(double &ix,double &iy){
  double x = ix;
  double y = iy;
  ix = y;
  iy = x;
}

int MyMax(int n,int *x){
  int  mn=0;
  int mx;
  mx = x[0];
  for(int i=1;i<n;i++){
    if(x[i] > mx){
      mn = i;
      mx = x[i];
    }
  }
  return mn; 
}

int MyMax(int n,double *x){
  int  mn=0;
  double mx;
  mx = x[0];
  for(int i=1;i<n;i++){
    if(x[i] > mx){
      mn = i;
      mx = x[i];
    }
  }
  return mn; 
}

int MyMin(int n,int *x){
  int mn=0;
  int mx;
  mx = x[0];
  for(int i=1;i<n;i++){
    if(x[i] < mx){
      mn = i;
      mx = x[i];
    }
  }
  return mn;
}

int MyMin(int n,double *x){
  int mn=0;
  double mx;
  mx = x[0];
  for(int i=1;i<n;i++){
    if(x[i] < mx){
      mn = i;
      mx = x[i];
    }
  }
  return mn;
}

double Chi2(int n,double *d1,double *d1_e,double *d2,double *d2_e){
  double chi2 = 0.;
  double sigma2_t;
  for(int i=0;i<n;i++){
    sigma2_t = d1_e[i]*d1_e[i]+d2_e[i]*d2_e[i];
    if(sigma2_t==0){sigma2_t = 1.;}
    chi2 += (d1[i]-d2[i])*(d1[i]-d2[i])/sigma2_t;
  }
  return chi2;
}

int MySum(int n,int *d){
  int sum = 0;
  for(int i=0;i<n;i++){
    sum += d[i];
  }
  return sum;
}

double MySum(int n,double *d){
  double sum = 0.;
  for(int i=0;i<n;i++){
    sum += d[i];
  }
  return sum;
}

double MyAverage(int n,int *d){
  double mean = 0.;
  for(int i=0;i<n;i++){
    mean += d[i];
  }
  return mean/n;
}

double MyAverage(int n,double *d){
  double mean = 0.;
  for(int i=0;i<n;i++){
    mean += d[i];
  }
  return mean/n;
}

double MyRMS(int n,double mean,double *d){
  double rms=0;
  for(int i=0;i<n;i++){
    rms += (d[i]-mean)*(d[i]-mean);
  }
  return sqrt(rms);
}

int MyFitFirstLinear(int n, double *X,double *Y,double &a, double &b){
  double x=0.;
  double y=0.;
  double xx=0.;
  double xy=0.;
  for(int i=0;i<n;i++){
    x += X[i];
    y += Y[i];
    xx += X[i]*X[i];
    xy += X[i]*Y[i];
  }
  x = x/n;
  y = y/n;
  xx = xx/n;
  xy = xy/n;
  
  a = (xy-x*y)/(xx-x*x);
  b = (xx*y-x*xy)/(xx-x*x);
  return n;
}

MyFilePath::MyFilePath(char *b){
  SetDirectory(b);
}

int MyFilePath::SetBase(char *b){
  if(strlen(b)>256) {
    cerr << "[MyFilePaths::SetBase] char size is over > 256." << endl;
    return -1;
  }
  strcpy(base,b);
  return 0;
}

int MyFilePath::SetDirectory(char b[]){
  int len = strlen(b);
  if(b[len-1]!='/'){strcat(b,"/");}
  return SetBase(b);
}

char* MyFilePath::GetPath(char b[]){
  sprintf(tmp,"%s%s",base,b);
  return tmp;
}

SimpleList::SimpleList(char* file){
  Open(file);
}

int  SimpleList::Open(char* file){
  ifstream fin(file);
  if(!fin){
    cout << "[SimpleList::Open] Cannnot Open " << file << endl;
    return -1;
  }
  char a[256];
  nlist = 0;
  while(fin.getline(a,256)){
    if(a[0]=='#'){continue;}
    strcpy(list[nlist],a);
    nlist++;
  }
  fin.close();
  return nlist;
}

char* SimpleList::Get(int n){
  return (char*)list[n];
}

#endif
