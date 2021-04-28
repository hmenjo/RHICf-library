#ifndef __CONDISCRILEVEL_H__
#define __CONDISCRILEVEL_H__

class ConDiscriLevel {
  
 public:
  static const int NBOARD = 5;
  static const int NCH    = 16;

  int    version;
  int    type;
  
  double discrilevel[NBOARD][NCH];  // actual threshold parameter
  double offset[NBOARD][NCH];       // offset [mV]
  int    armtoboard[2][2];

 public:
  ConDiscriLevel();
  ~ConDiscriLevel(); 
  
  double GetDiscriLevel(int ib,int ich);                 // Board, Ch
  double GetDiscriLevel(int iarm,int itower,int ich);   // Arm, Tower,Ch
  int    SetDiscriLevel(int ib, int ich, double value);
  int    SetDiscriLevel(int iarm,int itower,int ich, double value);
  
  int    Read(char *file, char* option="");  
  
};


#endif
