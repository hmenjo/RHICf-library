#ifndef __SCIFIPOSTABLE_H__
#define __SCIFIPOSTABLE_H__

//-----------------------------------------------------------------
//                         ScifiPosTable    
//-----------------------------------------------------------------

#include <TObject.h>

class ScifiPosTable{
 public:
  static const int SCIFIPOSTABLE_NCH   = 512;
  static const int SCIFIPOSTABLE_TOWER = 2;
  static const int SCIFIPOSTABLE_LAYER = 4;
  static const int SCIFIPOSTABLE_XY    = 2;
  static const int SCIFIPOSTABLE_POS   = 40;
  static const int SCIFIPOSTABLE_PMTCH = 64;

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
  virtual ~ScifiPosTable(){;}
 
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
  
  // define 
 
  static const char* SCIFIPOSTABLE_FORMATNAME;
  static const int   SCIFIPOSTABLE_OK = 0;
  static const int   SCIFIPOSTABLE_ERROR = -1;

  ClassDef(ScifiPosTable,1);   //  Control the parameters of SciFi raw format.
};


#endif

