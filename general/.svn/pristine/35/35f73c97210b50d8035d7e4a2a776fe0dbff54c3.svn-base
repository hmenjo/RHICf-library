#ifndef _INC_A1CROSSTALK_CPP_
#define _INC_A1CROSSTALK_CPP_

#include "../include/A1CrossTalk.h"

//-------------------------------------------------------------------------
//  A1CrossTalk for operation 2015
// -Required table: 20141215_XtalkMatrixTemplate.root (8 60x60 matrix)
// -Proc.
// ReadFile("path/20141215_XtalkMatrixTemplate.root");
// CalibCrossTalk_wM(some formats);
//
//-------------------------------------------------------------------------
// A1CrossTalk                                
// This class is for crosstalk offset of SciFi detectors.
// It's better to use "A1LHCCrossTalk" class if you deal with A1Cal2 class.
//
// First, you must call "ReadFile" function to select following table files.
// 
// table/CROSSTALK_offset_X.dat : table for X direction.
// table/CROSSTALK_offset_Y.dat : table for Y direction.
// table/CROSSTALK_offset_X_invert.dat : invert table for X direction.
// table/CROSSTALK_offset_Y_invert.dat : invert table for Y direction.
//
// "invert" means invert matrix. When you use this tables, you can add the effect of crosstalk to SciFi data. (MC data etc.)
// After calling "ReadFile", you can use "CalibCrossTalk" function to calibrate crosstalk effect.
//=========================================================================
// 27.Aug.2009   M.NAKAI 
// 31.Jan.2010   Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
// 26.Apr.2015   Y.Makino for op2015
//-------------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(A1CrossTalk);
#endif

using namespace std;

A1CrossTalk::A1CrossTalk(){

  for(int i=0;i<4;i++){
    for(int j=0;j<60;j++){
      for(int k=0;k<20;k++){
	calib_cross_20x[i][k][j]=0;
	calib_cross_20y[i][k][j]=0;
      }
      for(int k=0;k<40;k++){
	calib_cross_40x[i][k][j]=0;
	calib_cross_40y[i][k][j]=0;
      }
    }
  }

  return;
}

A1CrossTalk::~A1CrossTalk(){  
  return;
}

int A1CrossTalk::ReadFile(char *filename_x, char *filename_y){
  // Reading tabls files selected in arguments for crosstalk offset.
  fin_x.open(filename_x);
  fin_y.open(filename_y);

  if(!fin_x || !fin_y){
    cout << "CrossTalk::ReadFile input file error" << endl;
    return 1;
  }

  fin_x >> listname >> listname >> listname >> listname;
  fin_y >> listname >> listname >> listname >> listname;

  while(!fin_x.eof()){
    fin_x >> layer >> pos >> cross_pos >> value;
    if(pos>=20){
      calib_cross_40x[layer][pos-20][cross_pos]=value;
    }else{
      calib_cross_20x[layer][pos][cross_pos]=value;
    }
  }
  while(!fin_y.eof()){
    fin_y >> layer >> pos >> cross_pos >> value;
    if(pos>=20){
      calib_cross_40y[layer][pos-20][cross_pos]=value;
    }else{
      calib_cross_20y[layer][pos][cross_pos]=value;
    }
  }

  fin_x.close();
  fin_y.close();
  fin_x.clear();  // added by H.MENJO 20 Feb 2010
  fin_y.clear();  // added by H.MENJO 20 Feb 2010
  return 0;
}

int A1CrossTalk::ReadFile(char *filename){

  // Reading a root file of Inv.Matrixies  
  // Implemented by Y.Makino

  TFile* f_mat = new TFile(filename,"read");

  char name[256];

  //Matrix for correction
  for(int imap=0; imap<8; ++imap){
      sprintf(name,"Matrix_MAPMT%d", imap);
      M[imap] = (TMatrixD*)f_mat->Get(name);
  }
  //Original matrix (before invert, for debug)
  for(int imap=0; imap<8; ++imap){
      sprintf(name,"Before_Matrix_MAPMT%d", imap);
      bM[imap] = (TMatrixD*)f_mat->Get(name);
  }

  return 0;
}

int A1CrossTalk::CalibCrossTalk(double scifi20x[][20], double scifi20y[][20], double scifi40x[][40], double scifi40y[][40]){
  // Calibrate crosstalk effects in the SciFi data arrays of arguments.
  for(int l=0;l<4;l++){
    for(int k=0;k<40;k++){
      temp_40x[l][k]=scifi40x[l][k];
      temp_40y[l][k]=scifi40y[l][k];
    }
    for(int k=0;k<20;k++){
      temp_20x[l][k]=scifi20x[l][k];
      temp_20y[l][k]=scifi20y[l][k];
    }
  }
  
  for(int l=0;l<4;l++){
    //for 40mm CROSSTALK
    for(int k=0;k<40;k++){
      for(int m=0;m<60;m++){
	if(m>=20)
	  { 
	    if(m!=k+20)
	      {
		scifi40x[l][k] += temp_40x[l][m-20]*calib_cross_40x[l][k][m];
		scifi40y[l][k] += temp_40y[l][m-20]*calib_cross_40y[l][k][m];
	      }
	  }
	if(m<20)
	  {
	    scifi40x[l][k] += temp_20x[l][m]*calib_cross_40x[l][k][m];
	    scifi40y[l][k] += temp_20y[l][m]*calib_cross_40y[l][k][m];
	  }
      }
    }
    //for 20mm CROSSTALK
    for(int k=0;k<20;k++){
      for(int m=0;m<60;m++){
	if(m>=20)
	  { 
	    scifi20x[l][k] += temp_40x[l][m-20]*calib_cross_20x[l][k][m];
	    scifi20y[l][k] += temp_40y[l][m-20]*calib_cross_20y[l][k][m];
	  }
	if(m<20)
	  {
	    if(m!=k)
	      {
		scifi20x[l][k] += temp_20x[l][m]*calib_cross_20x[l][k][m];
		scifi20y[l][k] += temp_20y[l][m]*calib_cross_20y[l][k][m];
	      }
	  }
      }
    }
  } 

  for(int l=0;l<4;l++){
    for(int k=0;k<40;k++){
      if(scifi40x[l][k]<0){ scifi40x[l][k] = 0; }
      if(scifi40y[l][k]<0){ scifi40y[l][k] = 0; }
    }
    for(int k=0;k<20;k++){
      if(scifi20x[l][k]<0){ scifi20x[l][k] = 0; }
      if(scifi20y[l][k]<0){ scifi20y[l][k] = 0; }
    }
  }
 
  return 0;
}

int A1CrossTalk::CalibCrossTalk_wM(A1Cal1* data){
  // calibration using TMatrix class

  //fill a1cal1 data to TVectorD 
  for(int ilay=0; ilay<4; ++ilay){

    for(int m=0; m<60; ++m){
      if(m<20){
	a4Vx[ilay][m] = data->scifi0[ilay][0][m];
	a4Vy[ilay][m] = data->scifi0[ilay][1][m];
      }else{
	a4Vx[ilay][m] = data->scifi1[ilay][0][m-20];
	a4Vy[ilay][m] = data->scifi1[ilay][1][m-20];
      }
    }//m60
    Vx = new TVectorD(60,a4Vx[ilay]);
    Vy = new TVectorD(60,a4Vy[ilay]);

    (*Vy) *= (*M[2*ilay]);
    (*Vx) *= (*M[2*ilay+1]);

    for(int m=0; m<60; ++m){
      if(m<20){
	data->scifi0[ilay][0][m] = (*Vx)(m);
	data->scifi0[ilay][1][m] = (*Vy)(m);
      }else{
	data->scifi1[ilay][0][m-20] = (*Vx)(m);	
	data->scifi1[ilay][1][m-20] = (*Vy)(m);	
      }      
    }//m60
    delete Vx;
    delete Vy;
  }

//   //do not allow minus value
//   for(int ilay=0;ilay<4;ilay++){
//     for(int ipos=0;ipos<40;ipos++){
//       if(data->scifi1[ilay][0][ipos]<0){ data->scifi1[ilay][0][ipos] = 0; }
//       if(data->scifi1[ilay][1][ipos]<0){ data->scifi1[ilay][1][ipos] = 0; }
//     }
//     for(int ipos=0;ipos<20;ipos++){
//       if(data->scifi0[ilay][0][ipos]<0){ data->scifi0[ilay][0][ipos] = 0; }
//       if(data->scifi0[ilay][1][ipos]<0){ data->scifi0[ilay][1][ipos] = 0; }
//     }
//   } 
 
  return 0;
}

int A1CrossTalk::CalibCrossTalk_wM(double scifi0[][2][20], double scifi1[][2][40]){

  //fill a1cal1 data to TVectorD 
  for(int ilay=0; ilay<4; ++ilay){

    for(int m=0; m<60; ++m){
      if(m<20){
	a4Vx[ilay][m] = scifi0[ilay][0][m];
	a4Vy[ilay][m] = scifi0[ilay][1][m];
      }else{
	a4Vx[ilay][m] = scifi1[ilay][0][m-20];
	a4Vy[ilay][m] = scifi1[ilay][1][m-20];
      }
    }//m60
    Vx = new TVectorD(60,a4Vx[ilay]);
    Vy = new TVectorD(60,a4Vy[ilay]);

    (*Vy) *= (*M[2*ilay]);
    (*Vx) *= (*M[2*ilay+1]);

    for(int m=0; m<60; ++m){
      if(m<20){
	scifi0[ilay][0][m] = (*Vx)(m);
	scifi0[ilay][1][m] = (*Vy)(m);
      }else{
	scifi1[ilay][0][m-20] = (*Vx)(m);	
	scifi1[ilay][1][m-20] = (*Vy)(m);	
      }      
    }//m60
    delete Vx;
    delete Vy;
  }

//   //do not allow minus value
//   for(int ilay=0;ilay<4;ilay++){
//     for(int ipos=0;ipos<40;ipos++){
//       if(scifi1[ilay][0][ipos]<0){ scifi1[ilay][0][ipos] = 0; }
//       if(scifi1[ilay][1][ipos]<0){ scifi1[ilay][1][ipos] = 0; }
//     }
//     for(int ipos=0;ipos<20;ipos++){
//       if(scifi0[ilay][0][ipos]<0){ scifi0[ilay][0][ipos] = 0; }
//       if(scifi0[ilay][1][ipos]<0){ scifi0[ilay][1][ipos] = 0; }
//     }
//   } 
 
  return 0;
}

//for A1Cal2 : makino calibration using TMatrix class---------------------
int A1CrossTalk::CalibCrossTalk_wM(A1Cal2* data){

  //fill a1cal1 data to TVectorD 
  for(int ilay=0; ilay<4; ++ilay){

    for(int m=0; m<60; ++m){
      if(m<20){
	a4Vx[ilay][m] = data->scifi0[ilay][0][m];
	a4Vy[ilay][m] = data->scifi0[ilay][1][m];
      }else{
	a4Vx[ilay][m] = data->scifi1[ilay][0][m-20];
	a4Vy[ilay][m] = data->scifi1[ilay][1][m-20];
      }
    }//m60
    Vx = new TVectorD(60,a4Vx[ilay]);
    Vy = new TVectorD(60,a4Vy[ilay]);

    (*Vy) *= (*M[2*ilay]);
    (*Vx) *= (*M[2*ilay+1]);

    for(int m=0; m<60; ++m){
      if(m<20){
	data->scifi0[ilay][0][m] = (*Vx)(m);
	data->scifi0[ilay][1][m] = (*Vy)(m);
      }else{
	data->scifi1[ilay][0][m-20] = (*Vx)(m);	
	data->scifi1[ilay][1][m-20] = (*Vy)(m);	
      }      
    }//m60

    delete Vx;
    delete Vy;
  }

//   //do not allow minus value
//   for(int ilay=0;ilay<4;ilay++){
//     for(int ipos=0;ipos<40;ipos++){
//       if(data->scifi1[ilay][0][ipos]<0){ data->scifi1[ilay][0][ipos] = 0; }
//       if(data->scifi1[ilay][1][ipos]<0){ data->scifi1[ilay][1][ipos] = 0; }
//     }
//     for(int ipos=0;ipos<20;ipos++){
//       if(data->scifi0[ilay][0][ipos]<0){ data->scifi0[ilay][0][ipos] = 0; }
//       if(data->scifi0[ilay][1][ipos]<0){ data->scifi0[ilay][1][ipos] = 0; }
//     }
//   } 
 
  return 0;
}

int A1CrossTalk::CalibCrossTalk_wOrgM(A1Cal1* data){
  //XTalk corrected --> XTalk non-corrected)

  //fill a1cal1 data to TVectorD 
  for(int ilay=0; ilay<4; ++ilay){

    for(int m=0; m<60; ++m){
      if(m<20){
	a4Vx[ilay][m] = data->scifi0[ilay][0][m];
	a4Vy[ilay][m] = data->scifi0[ilay][1][m];
      }else{
	a4Vx[ilay][m] = data->scifi1[ilay][0][m-20];
	a4Vy[ilay][m] = data->scifi1[ilay][1][m-20];
      }
    }//m60
    Vx = new TVectorD(60,a4Vx[ilay]);
    Vy = new TVectorD(60,a4Vy[ilay]);

    (*Vy) *= (*bM[2*ilay]);
    (*Vx) *= (*bM[2*ilay+1]);

    for(int m=0; m<60; ++m){
      if(m<20){
	data->scifi0[ilay][0][m] = (*Vx)(m);
	data->scifi0[ilay][1][m] = (*Vy)(m);
      }else{
	data->scifi1[ilay][0][m-20] = (*Vx)(m);	
	data->scifi1[ilay][1][m-20] = (*Vy)(m);	
      }      
    }//m60

  }

//   //do not allow minus value
//   for(int ilay=0;ilay<4;ilay++){
//     for(int ipos=0;ipos<40;ipos++){
//       if(data->scifi1[ilay][0][ipos]<0){ data->scifi1[ilay][0][ipos] = 0; }
//       if(data->scifi1[ilay][1][ipos]<0){ data->scifi1[ilay][1][ipos] = 0; }
//     }
//     for(int ipos=0;ipos<20;ipos++){
//       if(data->scifi0[ilay][0][ipos]<0){ data->scifi0[ilay][0][ipos] = 0; }
//       if(data->scifi0[ilay][1][ipos]<0){ data->scifi0[ilay][1][ipos] = 0; }
//     }
//   } 
 
  return 0;
}


int A1CrossTalk::CalibCrossTalk_wOrgM(A1Cal2* data){
  //(XTalk corrected --> XTalk non-corrected)

  //fill a1cal2 data to TVectorD 
  for(int ilay=0; ilay<4; ++ilay){

    for(int m=0; m<60; ++m){
      if(m<20){
	a4Vx[ilay][m] = data->scifi0[ilay][0][m];
	a4Vy[ilay][m] = data->scifi0[ilay][1][m];
      }else{
	a4Vx[ilay][m] = data->scifi1[ilay][0][m-20];
	a4Vy[ilay][m] = data->scifi1[ilay][1][m-20];
      }
    }//m60
    Vx = new TVectorD(60,a4Vx[ilay]);
    Vy = new TVectorD(60,a4Vy[ilay]);

    (*Vy) *= (*bM[2*ilay]);
    (*Vx) *= (*bM[2*ilay+1]);

    for(int m=0; m<60; ++m){
      if(m<20){
	data->scifi0[ilay][0][m] = (*Vx)(m);
	data->scifi0[ilay][1][m] = (*Vy)(m);
      }else{
	data->scifi1[ilay][0][m-20] = (*Vx)(m);	
	data->scifi1[ilay][1][m-20] = (*Vy)(m);	
      }      
    }//m60

  }

 
  return 0;
}

int A1CrossTalk::CalibCrossTalk_wOrgM(double scifi0[][2][20], double scifi1[][2][40]){

  //fill a1cal1 data to TVectorD 
  for(int ilay=0; ilay<4; ++ilay){

    for(int m=0; m<60; ++m){
      if(m<20){
	a4Vx[ilay][m] = scifi0[ilay][0][m];
	a4Vy[ilay][m] = scifi0[ilay][1][m];
      }else{
	a4Vx[ilay][m] = scifi1[ilay][0][m-20];
	a4Vy[ilay][m] = scifi1[ilay][1][m-20];
      }
    }//m60
    Vx = new TVectorD(60,a4Vx[ilay]);
    Vy = new TVectorD(60,a4Vy[ilay]);

    (*Vy) *= (*bM[2*ilay]);
    (*Vx) *= (*bM[2*ilay+1]);

    for(int m=0; m<60; ++m){
      if(m<20){
	scifi0[ilay][0][m] = (*Vx)(m);
	scifi0[ilay][1][m] = (*Vy)(m);
      }else{
	scifi1[ilay][0][m-20] = (*Vx)(m);	
	scifi1[ilay][1][m-20] = (*Vy)(m);	
      }      
    }//m60

  }

//   //do not allow minus value
//   for(int ilay=0;ilay<4;ilay++){
//     for(int ipos=0;ipos<40;ipos++){
//       if(scifi1[ilay][0][ipos]<0){ scifi1[ilay][0][ipos] = 0; }
//       if(scifi1[ilay][1][ipos]<0){ scifi1[ilay][1][ipos] = 0; }
//     }
//     for(int ipos=0;ipos<20;ipos++){
//       if(scifi0[ilay][0][ipos]<0){ scifi0[ilay][0][ipos] = 0; }
//       if(scifi0[ilay][1][ipos]<0){ scifi0[ilay][1][ipos] = 0; }
//     }
//   } 
 
  return 0;
}

#endif
