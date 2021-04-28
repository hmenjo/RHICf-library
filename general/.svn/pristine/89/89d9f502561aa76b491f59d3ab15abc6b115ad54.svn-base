#ifndef __SCIFIPOSTABLE_CPP__
#define __SCIFIPOSTABLE_CPP__

#include "ScifiPosTable.h"

//----------------------------------------------------------------------
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(ScifiPosTable);
#endif

#include "feparam_arm1.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
using namespace std;

const int   ScifiPosTable::SCIFIPOSTABLE_NCH;
const int   ScifiPosTable::SCIFIPOSTABLE_TOWER;
const int   ScifiPosTable::SCIFIPOSTABLE_LAYER;
const int   ScifiPosTable::SCIFIPOSTABLE_XY;
const int   ScifiPosTable::SCIFIPOSTABLE_POS;
const int   ScifiPosTable::SCIFIPOSTABLE_PMTCH;
const int   ScifiPosTable::SCIFIPOSTABLE_OK;
const int   ScifiPosTable::SCIFIPOSTABLE_ERROR;
const char* ScifiPosTable::SCIFIPOSTABLE_FORMATNAME = "SCIFI_POS_TABLE";

ScifiPosTable::ScifiPosTable(){
  Initialize();
}

ScifiPosTable::ScifiPosTable(char *file){
  Initialize();
  ReadPositionTable(file);
}

int ScifiPosTable::Initialize(){
  //  strcpy(tablefile,"../tables/scifi_pos_table.dat");
  strcpy(tablefile,"../tables/GSObar_map9.tab");
  tableversion = -1;
  tabletype = -1;
  for(int i=0;i<SCIFIPOSTABLE_NCH;i++){
    tower[i]=-1;
    layer[i]=-1;
    xy[i]=-1;
    pos[i]=-1;
    mapmt[i]=-1;
  }
  for(int it=0;it<SCIFIPOSTABLE_TOWER;it++){
    for(int il=0;il<SCIFIPOSTABLE_LAYER;il++){
      for(int ixy=0;ixy<SCIFIPOSTABLE_XY;ixy++){
	for(int ip=0;ip<SCIFIPOSTABLE_POS;ip++){
	  ch[it][il][ixy][ip] = -1;
// 	  cout << it << " " << il << " " << ixy << " " <<ip <<endl; 
	}
      }
    }
  }
  return SCIFIPOSTABLE_OK;
}

int ScifiPosTable::ReadPositionTable(char *file){
  ifstream fin;
  fin.open(file);
  if(!fin){
    cerr << "[ScifiPosTable::ReadPositionTable] Cannot Open " << file 
	 << endl;
    return SCIFIPOSTABLE_ERROR ;
  }
  
  // Initialization of values 
  Initialize();

  char a[200];
  bool check_param=false;
  while(1){
    fin >> a;
    if(fin.eof()){
      cerr << "[ScifiPosTable::ReadPositionTable] " << file 
	   << " is not Scifi Position Table." << endl;
      return SCIFIPOSTABLE_ERROR ;
    }
    if(strcmp(a,"PARAM_START")==0){check_param=true;}
    if(strcmp(a,"PARAM_END")==0){check_param=false;break;}
    if(check_param!=true){continue;}
    
    if(strcmp(a,"FORMAT:")==0){ fin >> tableformat; }
    if(strcmp(a,"VERSION:")==0){ fin >> tableversion;}
    if(strcmp(a,"TYPE:")==0){ fin >> tabletype;} 
  }
  
  if(strcmp(tableformat,SCIFIPOSTABLE_FORMATNAME)!=0){
    cerr << "[ScifiPosTable::ReadPositionTable] " << file 
	 << " is not Scifi Position Table." << endl;
    return SCIFIPOSTABLE_ERROR ;
  }
  fin.close();
  strcpy(tablefile,file);
  
  if(tabletype==1){ 
    ReadFileType1();
  }
  else if(tabletype==2){
    ReadFileType2();
  }
  else{
    cerr << "[ScifiPosTable::ReadPositionTable] Unkown Format Type."
	 << endl;
    return SCIFIPOSTABLE_ERROR ;
  }
  
  return SCIFIPOSTABLE_OK;
}

int ScifiPosTable::ReadFileType1(){
  ifstream fin(tablefile);
  char a[256];
  bool check_data=false;
  int  tch,tt,tl,txy,tp;
  while(1){
    fin.getline(a,256);
    if(fin.eof()){break;}
    if(strstr(a,"DATA_START")!=NULL){check_data=true;}
    if(strstr(a,"DATA_END")!=NULL){break;}
    
    if(check_data!=true || strstr(a,"DATA_START")!=NULL){continue;}
    sscanf(a,"%d %d %d %d %d",&tch,&tt,&tl,&txy,&tp);
    if(tch<0 || tt<0 || tl<0 || txy <0 || tp<0 ||
       tch>=SCIFIPOSTABLE_NCH || tt>=SCIFIPOSTABLE_TOWER || 
       tl>=SCIFIPOSTABLE_LAYER || txy>=SCIFIPOSTABLE_XY || tp>=SCIFIPOSTABLE_POS){
      continue;
    }

    if(tt==0)      {tp = 19 - tp;}
    else if(tt==1) {tp = 39 -tp;}

    if(ch[tt][tl][txy][tp]!=-1){
      cout << "t=" << tt << " l=" << tl 
	   << " xy=" << txy << " pos=" << tp << endl; 
    }
    
    ch[tt][tl][txy][tp] = tch;
    tower[tch] = tt;
    layer[tch] = tl;
    xy[tch] = txy;
    pos[tch] = tp;

  }
  fin.close();

  return SCIFIPOSTABLE_OK;  
}


int ScifiPosTable::ReadFileType2(){
  ifstream fin(tablefile);
  char a[256];
  bool check_data=false;
  int  tch,tt,tl,txy,tp,tmapmt;
  while(1){
    fin.getline(a,256);
    if(fin.eof()){break;}
    if(strstr(a,"DATA_START")!=NULL){check_data=true;}
    if(strstr(a,"DATA_END")!=NULL){break;}
    
    if(check_data!=true || strstr(a,"DATA_START")!=NULL){continue;}
    sscanf(a,"%d %d %d %d %d %d",&tch,&tt,&tl,&txy,&tp,&tmapmt);
    if(tch<0 || tt<0 || tl<0 || txy <0 || tp<0 ||
       tch>=SCIFIPOSTABLE_NCH || tt>=SCIFIPOSTABLE_TOWER || 
       tl>=SCIFIPOSTABLE_LAYER || txy>=SCIFIPOSTABLE_XY || tp>=SCIFIPOSTABLE_POS){
      continue;
    }

    if(tt==0)      {tp = 19 - tp;}
    else if(tt==1) {tp = 39 -tp;}

    if(ch[tt][tl][txy][tp]!=-1){
      cout << "t=" << tt << " l=" << tl 
	   << " xy=" << txy << " pos=" << tp << endl; 
    }
    
    ch[tt][tl][txy][tp] = tch;
    tower[tch] = tt;
    layer[tch] = tl;
    xy[tch] = txy;
    pos[tch] = tp;
    mapmt[tch] = tmapmt;
  }
  fin.close();

  return SCIFIPOSTABLE_OK;  
}

int ScifiPosTable::ReadCheck(){
  int check_nodata=0;
  for(int it=0;it<SCIFIPOSTABLE_TOWER;it++){
    for(int il=0;il<SCIFIPOSTABLE_LAYER;il++){
      for(int ixy=0;ixy<SCIFIPOSTABLE_XY;ixy++){
	for(int ip=0;ip<SCIFIPOSTABLE_POS;ip++){
	  if(it==0 && ip>=20){continue;}
	  if(ch[it][il][ixy][ip] == -1){
	    cout << "[ScifiPosTable::ReadCheck] No Data:"
		 << " t=" << it 
		 << " l=" << il
		 << " xy=" << ixy
		 << " pos=" << ip
		 << endl;
	    check_nodata++;
	  }
	}
      }
    }
  }
  if(check_nodata!=0){return SCIFIPOSTABLE_ERROR;}
  return SCIFIPOSTABLE_OK;
}

int ScifiPosTable::GetChannel(int tt,int tl,int txy,int tp){
  if(tt<0 || tl<0 || txy <0 || tp<0 ||
     tt>=SCIFIPOSTABLE_TOWER || tl>=SCIFIPOSTABLE_LAYER || 
     txy>=SCIFIPOSTABLE_XY || tp>=SCIFIPOSTABLE_POS){
    return SCIFIPOSTABLE_ERROR;
  }
  return ch[tt][tl][txy][tp];
}

int ScifiPosTable::GetTower(int c){
  if(c<0 || c>SCIFIPOSTABLE_NCH){return SCIFIPOSTABLE_ERROR;}
  return tower[c];
}

int ScifiPosTable::GetLayer(int c){
  if(c<0 || c>SCIFIPOSTABLE_NCH){return SCIFIPOSTABLE_ERROR;}
  return layer[c];
}

int ScifiPosTable::GetXY(int c){
  if(c<0 || c>SCIFIPOSTABLE_NCH){return SCIFIPOSTABLE_ERROR;}
  return xy[c];
}

int ScifiPosTable::GetPos(int c){
  if(c<0 || c>SCIFIPOSTABLE_NCH){return SCIFIPOSTABLE_ERROR;}
  return pos[c];
}

int ScifiPosTable::GetIPMT(int c){
  if(c<0 || c>SCIFIPOSTABLE_NCH){return SCIFIPOSTABLE_ERROR;}
  return mapmt[c]/SCIFIPOSTABLE_PMTCH;
}

int ScifiPosTable::GetPosOnPMT(int c){
  if(c<0 || c>SCIFIPOSTABLE_NCH){return SCIFIPOSTABLE_ERROR;}
  return mapmt[c]%SCIFIPOSTABLE_PMTCH;
}

int ScifiPosTable::PrintStatus(){
  cout << "FOTMAT: " << tableformat << endl
       << " TABLEFILE: " << tablefile << endl;
  return SCIFIPOSTABLE_OK;
}

#endif


/*  void test(){ */

/*    ScifiPosTable spos; */
/*    spos.Initialize(); */
/*    spos.ReadPositionTable("../tables/scifi_pos_table.dat"); */
/*    spos.ReadCheck(); */

/*    cout << spos.GetChannel(0,0,0,3) << endl; */
  
/*  } */
