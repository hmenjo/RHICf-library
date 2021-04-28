#ifndef  __CONSCIFIPOSITION_H__
#define  __CONSCIFIPOSITION_H__

//-----------------------------------------------------------------
//                         ConScifiPosition  
//-----------------------------------------------------------------

#include <TObject.h>
#include "MyFunction.h"

class StructFiberPos{
 public:
  double  origin[2];           // (x,y) on the calorimeter frame
  double  width;               // 
  double  length;              //
  double  direction;           // theta[rad]
 public:
  StructFiberPos(){;}
  virtual ~StructFiberPos(){;}
  ClassDef(StructFiberPos,1); 
};

class ConScifiPosition{
public:
  char       tablefile[256];     //
  char       format[256];        //
  int        type;               //
  int        version;            //

  StructFiberPos fiber[2][4][2][40]; //

public:
  ConScifiPosition();
  ConScifiPosition(char* file); 
  virtual ~ConScifiPosition();

  int    Initialize();
  int    ReadFile(char* file);
  int    WriteFile(int t,char* file,char comment[] = "");

  double GetFiberOriginX(int it,int il,int ixy,int is);
  double GetFiberOriginY(int it,int il,int ixy,int is);
  double GetFiberWidth(int it,int il,int ixy,int is);
  double GetFiberLength(int it,int il,int ixy,int is); 
  double GetFiberDirection(int it,int il,int ixy,int is); 
  double GetCenterPosition(int it,int il,int ixy,int is, double ap=-10.);
  double CalPos2FiberPosX(double cx,double cy,int it,int il,int ixy,int is);
  double CalPos2FiberPosY(double cx,double cy,int it,int il,int ixy,int is);  
  int    CalPos2FiberPos(double cx,double cy,double &lx,double &ly,
			 int it,int il,int ixy,int is); 
  double FiberPos2CalPosX(double lx,double ly,int it,int il,int ixy,int is);
  double FiberPos2CalPosY(double lx,double ly,int it,int il,int ixy,int is);
  int    FiberPos2CalPos(double lx,double ly,double &cx,double &cy,
			 int it,int il,int ixy,int is);
  int    FindFiber(int it,int il,int ixy,double x,double y);
  int    it2size(int it);
  
  static const double pi;
  static const char* CONSCIFIPOSITION_FORMAT;
  static const int CONSCIFIPOSITION_OK = 0;
  static const int CONSCIFIPOSITION_ERROR = -1;
  
  ClassDef(ConScifiPosition,1);   // Control the parameter table for positions of each fiber 

};


#endif
