#ifndef __SCIFIPOSTABLE__
#define __SCIFIPOSTABLE__

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#define SCIFIPOSTABLE_FORMATNAME "SCIFI_POS_TABLE"

#define SCIFIPOSTABLE_NCH     512
#define SCIFIPOSTABLE_TOWER     2
#define SCIFIPOSTABLE_LAYER     4
#define SCIFIPOSTABLE_XY        2
#define SCIFIPOSTABLE_POS      40
#define SCIFIPOSTABLE_PMTCH    64

#define SCIFIPOSTABLE_OK        0
#define SCIFIPOSTABLE_ERROR    -1

class ScifiPosTable{
protected:
  char   tablefile[256];
  char   tableformat[256];
  int    tableversion;
  int    tabletype;

  int    tower[SCIFIPOSTABLE_NCH];
  int    layer[SCIFIPOSTABLE_NCH];
  int    xy[SCIFIPOSTABLE_NCH];
  int    pos[SCIFIPOSTABLE_NCH];
  int    mapmt[SCIFIPOSTABLE_NCH];
  int    ch[SCIFIPOSTABLE_TOWER][SCIFIPOSTABLE_LAYER][SCIFIPOSTABLE_XY][SCIFIPOSTABLE_POS];
public:
  ScifiPosTable();
  ScifiPosTable(char *file);
  
  int    Initialize();
  int    ReadPositionTable(char *file);
  int    ReadFileType1();
  int    ReadFileType2();
  int    ReadCheck();

  int    GetChannel(int t,int l,int x,int p);
  int    GetTower(int c);
  int    GetLayer(int c);
  int    GetXY(int c);
  int    GetPos(int c);
  int    GetIPMT(int c);
  int    GetPosOnPMT(int c);
  int    PrintStatus();
};

ScifiPosTable::ScifiPosTable(){
  Initialize();
}

ScifiPosTable::ScifiPosTable(char *file){
  Initialize();
  ReadPositionTable(file);
}

int ScifiPosTable::Initialize(){
  strcpy(tablefile,"../tables/scifi_pos_table.dat");
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
