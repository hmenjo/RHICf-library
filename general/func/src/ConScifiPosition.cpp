#ifndef  __CONSCIFIPOSITION_CPP__
#define  __CONSCIFIPOSITION_CPP__

#include "ConScifiPosition.h"

//----------------------------------------------------------------------
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(StructFiberPos);
ClassImp(ConScifiPosition);
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <math.h>
#include <string.h>
using namespace std;

#include <TMath.h>

const double ConScifiPosition::pi = TMath::Pi();;
const char* ConScifiPosition::CONSCIFIPOSITION_FORMAT = "CONSCIFIPOSITION";
const int ConScifiPosition::CONSCIFIPOSITION_OK;
const int ConScifiPosition::CONSCIFIPOSITION_ERROR;

ConScifiPosition::ConScifiPosition(){
  Initialize();
}

ConScifiPosition::ConScifiPosition(char* file){
  Initialize();
  ReadFile(file);
}

ConScifiPosition::~ConScifiPosition(){;}

int ConScifiPosition::Initialize(){
  strcpy(tablefile,"");
  strcpy(format,"");
  type   = 0;
  version = 0;

  for(int it=0;it<2;it++){
    for(int il=0;il<4;il++){
      for(int ixy=0;ixy<2;ixy++){
	for(int is=0;is<40;is++){
	  if(ixy==0){
	    fiber[it][il][ixy][is].origin[0] = (double)is;
	    fiber[it][il][ixy][is].origin[1] = 0.;
	    fiber[it][il][ixy][is].direction = 0.;
	  }
	  else if(ixy==1){
	    fiber[it][il][ixy][is].origin[0] = 0.;
	    fiber[it][il][ixy][is].origin[1] = (double)is+1.0;
	    fiber[it][il][ixy][is].direction = -1.*pi/2.;
	  }
	  
	  fiber[it][il][ixy][is].width = 1.;
	  if(it==0){fiber[it][il][ixy][is].length = 20.;}
	  if(it==1){fiber[it][il][ixy][is].length = 40.;} 
	}
      }
    }
  }
  return CONSCIFIPOSITION_OK;
}

int ConScifiPosition::ReadFile(char* file){
  ifstream fin(file);
  if(!fin){
    cerr << "[ConScifiPosition::ReadFile] Cannot Open "
         << file << endl;
    return CONSCIFIPOSITION_ERROR;
  }
  strcpy(tablefile,file);
  
  char a[256];
  bool check_param=false;
  bool check_data=false;
  while(1){
    fin >> a;
    if(fin.eof()){break;}
    if(strcmp(a,"PARAM_END")==0){break;}
    if(strcmp(a,"PARAM_START")==0){check_param=true;}
    if(check_param==true){
      if(strcmp(a,"FORMAT:")==0){ fin >> format; }
      if(strcmp(a,"TYPE:")==0){fin >> type;}
      if(strcmp(a,"VERSION:")==0){fin >> version;}
    }
  }
  if(strcmp(format,CONSCIFIPOSITION_FORMAT)!=0){
    cerr << "[ConScifiPosition::ReadFile] this is not "
         << CONSCIFIPOSITION_FORMAT
         << endl;
    return CONSCIFIPOSITION_ERROR;
  }
  
  int it,il,ixy,is;
  double ox,oy,w,l,d;
  if(type==1){  
    while(1){
      fin >> a;
      if(fin.eof()){break;}
      if(strcmp(a,"DATA_END")==0){break;}
      if(strcmp(a,"DATA_START")==0){check_data=true;}
      
      if(strcmp(a,"FIBER")==0){
	fin >> it >> il >> ixy >> is >> ox >> oy >> w >> l >> d;
	fiber[it][il][ixy][is].origin[0] = ox;
	fiber[it][il][ixy][is].origin[1] = oy;
	fiber[it][il][ixy][is].width = w;
	fiber[it][il][ixy][is].length = l;	
	fiber[it][il][ixy][is].direction = d/180.*pi;
      }
    }
    fin.close();
    return CONSCIFIPOSITION_OK;
  }
  else {
    fin.close();
    return CONSCIFIPOSITION_ERROR;
  }
}

int ConScifiPosition::WriteFile(int t,char* file,char comment[]){
  strcpy(tablefile,file);
  ofstream fout(file);

  if(t!=1){
    cerr << "[ConScifiPosition::WriteFile] "
         << t << " is wrong type" << endl;
    return CONSCIFIPOSITION_ERROR;
  }
  
  strcpy(format,CONSCIFIPOSITION_FORMAT);
  type = t;
  time_t nowtime;
  struct tm *lt;
  char timestamp[10];
  time(&nowtime);
  lt = localtime(&nowtime);

  sprintf(timestamp,"%02d%02d%02d",lt->tm_year%100,lt->tm_mon+1,lt->tm_mday);
  fout << "PARAM_START" << endl
       << "FORMAT:  " << format << endl
       << "TYPE:    " << t << endl
       << "VERSION: " << version << endl
       << "DATE:    " << timestamp << endl
       << "COMMENT: " << comment <<  endl
       << "PARAM_END" << endl << endl;

  if(t==1){
    fout << "DATA_START" << endl;
    fout.setf(ios::fixed);
    for(int it=0;it<2;it++){
      for(int il=0;il<4;il++){
	for(int ixy=0;ixy<2;ixy++){
	  for(int is=0;is<it2size(it);is++){
	    fout << "FIBER " 
		 << setw(2) << it << " "
		 << setw(2) << il << " "
		 << setw(2) << ixy << " "
		 << setw(3) << is << "  "
		 << setw(7) << setprecision(3) << fiber[it][il][ixy][is].origin[0] << " "
		 << setw(7) << setprecision(3) << fiber[it][il][ixy][is].origin[1] << " "
		 << setw(7) << setprecision(3) << fiber[it][il][ixy][is].width << " "
		 << setw(7) << setprecision(3) << fiber[it][il][ixy][is].length << " "
		 << setw(9) << setprecision(4) << fiber[it][il][ixy][is].direction/pi*180. << " "
		 << endl;
	  }
	}
      }
    }
    fout << "DATA_END" <<endl;
    fout.close();
    return CONSCIFIPOSITION_OK;
  }
  return CONSCIFIPOSITION_ERROR; 
}

double ConScifiPosition::GetFiberOriginX(int it,int il,int ixy,int is){
  return fiber[it][il][ixy][is].origin[0];
}

double ConScifiPosition::GetFiberOriginY(int it,int il,int ixy,int is){
  return fiber[it][il][ixy][is].origin[1];
}

double ConScifiPosition::GetFiberWidth(int it,int il,int ixy,int is){
  return fiber[it][il][ixy][is].width;
}

double ConScifiPosition::GetFiberLength(int it,int il,int ixy,int is){
  return fiber[it][il][ixy][is].length;
}

double ConScifiPosition::GetFiberDirection(int it,int il,int ixy,int is){
  return fiber[it][il][ixy][is].direction;
}

double ConScifiPosition::CalPos2FiberPosX(double cx,double cy,
					  int it,int il,int ixy,int is){
  double x,y;
  CalPos2FiberPos(cx,cy,x,y,it,il,ixy,is);
  return x;
}

double ConScifiPosition::CalPos2FiberPosY(double cx,double cy,
					  int it,int il,int ixy,int is){
  double x,y;
  CalPos2FiberPos(cx,cy,x,y,it,il,ixy,is);
  return y;
}

int ConScifiPosition::CalPos2FiberPos(double cx,double cy,double &lx,double &ly,
				      int it,int il,int ixy,int is){
  double x,y;
  x = cx;
  y = cy;
  PosShift(x,y,-1.*fiber[it][il][ixy][is].origin[0],-1.*fiber[it][il][ixy][is].origin[1]);
//   cout << x << " " << y << endl;
  PosRotate(x,y,-1.*fiber[it][il][ixy][is].direction);
//   cout << x << " " << y << endl;
  lx = x;
  ly = y;
  
  if(x>-0.000000001 && x<fiber[it][il][ixy][is].width &&
     y>-0.00000001 && y<fiber[it][il][ixy][is].length) {return 1;}
  else {return -1;}
}

double ConScifiPosition::FiberPos2CalPosX(double lx,double ly,
					  int it,int il,int ixy,int is){
  double x,y;
  CalPos2FiberPos(lx,ly,x,y,it,il,ixy,is);
  return x;
}

double ConScifiPosition::FiberPos2CalPosY(double lx,double ly,
					  int it,int il,int ixy,int is){
  double x,y;
  CalPos2FiberPos(lx,ly,x,y,it,il,ixy,is);
  return y;
}

int ConScifiPosition::FiberPos2CalPos(double lx,double ly,double &cx,double &cy,
				      int it,int il,int ixy,int is){
  double x,y;
  x = lx;
  y = ly;
  PosRotate(x,y,fiber[it][il][ixy][is].direction);
  PosShift(x,y,fiber[it][il][ixy][is].origin[0],fiber[it][il][ixy][is].origin[1]);
  cx = x;
  cy = y; 
  return 1;
}

double ConScifiPosition::GetCenterPosition(int it,int il,int ixy,int is, double ap){
  if(ap<-5.){ ap = (double)it2size(it)/2.;}

  double cx,cy;
  if(ixy==0){
    FiberPos2CalPos(0.5,0.,cx,cy,it,il,ixy,is);
    return tan(fiber[it][il][ixy][is].direction)*(cy-ap)+cx;
  }
  else if(ixy==1){
    FiberPos2CalPos(0.5,0.,cx,cy,it,il,ixy,is);
    return tan(fiber[it][il][ixy][is].direction+pi/2.)*(ap-cx)+cy;
  }
  return 0;
  
}

int ConScifiPosition::FindFiber(int it,int il,int ixy,double x,double y){
  int is;
  double lx,ly;
  for(is=0;is<it2size(it);is++){
    if(CalPos2FiberPos(x,y,lx,ly,it,il,ixy,is)==1){
      break;
    }
  }
  if(is==20){return -1;}
  return is;
}

int ConScifiPosition::it2size(int it){
  if(it==0) return 20;
  if(it==1) return 40;
  return 0;
}

#endif
