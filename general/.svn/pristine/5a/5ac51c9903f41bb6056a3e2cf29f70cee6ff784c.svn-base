#ifndef __SCIFIPOSCALCULATION_CPP__
#define __SCIFIPOSCALCULATION_CPP__

#include "SciFiPosCalculation.h"

//----------------------------------------------------------------------
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by Mizuishi
//  ?? ???. 09: Modified by someones
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//  26 Apr. 15: Mod. ver. for op2015 by Y.Makino
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(SciFiPosCalculation);
#endif

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>

#define  SH     10
#define  PSH    100
#define  Zyou   2
#define  Ma0    0.75
#define  Ma1    0.70

using namespace std;

int SciFiPosCalculation::Init()
{
  //  return Initialize();
  return Initialize_op2015(); // Use this for op2015 
} 

int SciFiPosCalculation::CalPosition(A1Cal2 *a1cal2, A1Phys *a1phys){
  //    scifi_gaincalibration(a1cal2);
    scifipos_read(a1cal2);
    scifipos_fill(a1phys);
    return OK;
}

int SciFiPosCalculation::Initialize(){
  
  int xy_sou_pos;
  ifstream fin0("config/20mm_pos.dat");
  ifstream fin1("config/40mm_pos.dat");
  ifstream fin0_1MIP("config/20mm_1MIP.dat");
  ifstream fin1_1MIP("config/40mm_1MIP.dat");
 
  for(int ixy=0; ixy<2; ++ixy){
    for(int ilay=0; ilay<4; ++ilay){
      for(int ich=0; ich<20; ++ich){
	fin0>>hosei0[ilay][ixy][ich];
	fin0_1MIP>>xy_sou_pos>>hosei_1MIP0[ilay][ixy][ich];
      }
      for(int ich=0; ich<40; ++ich){
	fin1>>hosei1[ilay][ixy][ich];
	fin1_1MIP>>xy_sou_pos>>hosei_1MIP1[ilay][ixy][ich];
      }
    }
  }

  return OK;
}

int SciFiPosCalculation::Initialize_op2015(){
  
  // Gain table based on SPS2014
  //  ReadGSObarGainTable(); -> gc is done in A1GainCalibration

  // AD-HOC Pos table.  
  ReadGSObarPosTable();

  return OK;
}

int SciFiPosCalculation::ReadGSObarPosTable(){

  // NOTE: These tables are not based on beam test. Just ad-hoc tables!
  ifstream fin20("config/20mm_pos_op2015.dat");
  ifstream fin40("config/40mm_pos_op2015.dat");
  for(int ixy=0; ixy<2; ++ixy){
    for(int ilay=0; ilay<4; ++ilay){
      for(int ich=0; ich<20; ++ich){
	fin20 >> hosei0[ilay][ixy][ich];
      }
      for(int ich=0; ich<40; ++ich){
	fin40 >> hosei1[ilay][ixy][ich];
      }
    }
  }

  return OK;
}

// int SciFiPosCalculation::ReadGSObarGainTable(){
//   // NOTE: this gain correction is just relative, not absolute.
//   ifstream fin("config/gsobar_gain_table_20141219_5.tab");
//   if(!fin) cerr<<"Table not found in SciFiPosCalculation::ReadGSObarGainTable()"<<endl;
//   char a[256];
//   int tower=0;
//   int layer=0;
//   int xy=0;
//   int ch=0;
//   double gain=0;

//   while(1){
//     fin >> a;
//     if(strcmp(a,"END")==0) break;
//     if(strcmp(a,"D")==0){
//       fin >> tower >> layer >> xy >> ch >> gain;
//       if(tower==0)      hosei_1MIP0[layer][xy][ch]=gain;
//       else if(tower==1) hosei_1MIP1[layer][xy][ch]=gain;
//     }
//   }

//   return OK;
// }

void SciFiPosCalculation::scifi_gaincalibration(A1Cal2 *a1cal2){

  for(int ixy=0; ixy<2; ixy++){
    for(int ilay=0; ilay<4; ilay++){
      for(int ich=0; ich<20; ich++){
	if(hosei_1MIP0[ilay][ixy][ich]!=0){
	  a1cal2->scifi0[ilay][ixy][ich] /= hosei_1MIP0[ilay][ixy][ich];
	}
	if(hosei_1MIP0[ilay][ilay][ich]==0){
	  a1cal2->scifi0[ilay][ixy][ich] = -100;
	}
      }
      for(int ich=0;ich<40;ich++){
	if(hosei_1MIP1[ilay][ixy][ich]!=0){
	  a1cal2->scifi1[ilay][ixy][ich] /= hosei_1MIP1[ilay][ixy][ich];
	}
	if(hosei_1MIP1[ilay][ixy][ich]==0){
	  a1cal2->scifi1[ilay][ixy][ich] = -100;
	}
      }
    }
  }
  
}


void SciFiPosCalculation::scifipos_read(A1Cal2 *a1cal2){
  
  //initizlize
  for(int ixy=0;ixy<2;ixy++){
    for(int ilay=0;ilay<4;ilay++){

      sumscifi0[ilay][ixy]=0;
      sumscifi1[ilay][ixy]=0;
      max0[ilay][ixy]=0;
      max1[ilay][ixy]=0;
      saidai0[ilay][ixy]=0;
      saidai1[ilay][ixy]=0;
      goukei0[ilay][ixy]=0;
      goukei1[ilay][ixy]=0;
      goukei0_1[ilay][ixy]=0;
      goukei1_1[ilay][ixy]=0;
      zyuusinn0[ilay][ixy]=0;
      zyuusinn1[ilay][ixy]=0;
      
      for(int ich=0;ich<20;ich++)  scifikai0[ilay][ixy][ich]=0;
      for(int ich=0;ich<40;ich++)  scifikai1[ilay][ixy][ich]=0;

    }
  }
  
  //fill_a1cal2 to scifikai
  for(int ixy=0; ixy<2; ++ixy){
    for(int ilay=0; ilay<4; ++ilay){
      for(int ich=0; ich<20; ++ich){
	if(hosei_1MIP0[ilay][ixy][ich]!=0){
	  scifikai0[ilay][ixy][ich]=a1cal2->scifi0[ilay][ixy][ich];
	}
	if(hosei_1MIP0[ilay][ixy][ich]==0 && ich!=0 && ich!=19){
	  scifikai0[ilay][ixy][ich]=(a1cal2->scifi0[ilay][ixy][ich-1]+a1cal2->scifi0[ilay][ixy][ich+1])/2;
	}
	if(hosei_1MIP0[ilay][ixy][ich]==0 && ich==0){
	  scifikai0[ilay][ixy][ich]=a1cal2->scifi0[ilay][ixy][ich+1]/2;
	}
	if(hosei_1MIP0[ilay][ixy][ich]==0 && ich==19){
	  scifikai0[ilay][ixy][ich]=a1cal2->scifi0[ilay][ixy][ich-1]/2;
	}
      }
      
      for(int ich=0; ich<40; ++ich){
	if(hosei_1MIP1[ilay][ixy][ich]!=0){
	  scifikai1[ilay][ixy][ich]=a1cal2->scifi1[ilay][ixy][ich];
	}
	if(hosei_1MIP1[ilay][ixy][ich]==0 && ich!=0 && ich!=39){
	  scifikai1[ilay][ixy][ich]=(a1cal2->scifi1[ilay][ixy][ich-1]+a1cal2->scifi1[ilay][ixy][ich+1])/2;
	}
	if(hosei_1MIP1[ilay][ixy][ich]==0 && ich==0){
	  scifikai1[ilay][ixy][ich]=a1cal2->scifi1[ilay][ixy][ich+1]/2;
	}
	if(hosei_1MIP1[ilay][ixy][ich]==0 && ich==39){
	  scifikai1[ilay][ixy][ich]=a1cal2->scifi1[ilay][ixy][ich-1]/2;
	}
      }
    }
  }

  //read_max and sum
  for(int ixy=0; ixy<2; ++ixy){
    for(int ilay=0; ilay<4; ++ilay){
      for(int ich=0; ich<20; ++ich){
	sumscifi0[ilay][ixy]=sumscifi0[ilay][ixy]+scifikai0[ilay][ixy][ich];
	if(max0[ilay][ixy]<scifikai0[ilay][ixy][ich]){
	  max0[ilay][ixy]=scifikai0[ilay][ixy][ich];
	  saidai0[ilay][ixy]=ich;
	}
      }
      for(int ich=0; ich<40; ++ich){
	sumscifi1[ilay][ixy]=sumscifi1[ilay][ixy]+scifikai1[ilay][ixy][ich];
	if(max1[ilay][ixy]<scifikai1[ilay][ixy][ich]){
	  max1[ilay][ixy]=scifikai1[ilay][ixy][ich];
	  saidai1[ilay][ixy]=ich;
	}
      }
    }
  }
  
  //read_zyuusinn
  for(int ixy=0; ixy<2; ++ixy){
    for(int ilay=0; ilay<4; ++ilay){
      //20mmtower
      if(saidai0[ilay][ixy]>1 && saidai0[ilay][ixy]<18){
	if(max0[ilay][ixy]>SH){
	  for(int ich=saidai0[ilay][ixy]-2; ich<saidai0[ilay][ixy]+3; ++ich){
	    goukei0[ilay][ixy] = goukei0[ilay][ixy]+pow(scifikai0[ilay][ixy][ich],Zyou);
	    goukei0_1[ilay][ixy] = goukei0_1[ilay][ixy]+pow(scifikai0[ilay][ixy][ich],Zyou)*hosei0[ilay][ixy][ich];
	  }
	}
	if(max0[ilay][ixy]<=SH){
	  zyuusinn0[ilay][ixy]=0;
	}	
	if(goukei0[ilay][ixy]>PSH && goukei0[ilay][ixy]/sumscifi0[ilay][ixy]>Ma0){
	    zyuusinn0[ilay][ixy]=goukei0_1[ilay][ixy]/goukei0[ilay][ixy];
	}
	if(goukei0[ilay][ixy]<=PSH){
	    zyuusinn0[ilay][ixy]=0;
	}
	
      }
      
      if(saidai0[ilay][ixy]==1 || saidai0[ilay][ixy]==18){
	if(max0[ilay][ixy]>SH){
	  for(int ich=saidai0[ilay][ixy]-1; ich<saidai0[ilay][ixy]+2; ++ich){
	    goukei0[ilay][ixy] = goukei0[ilay][ixy]+pow(scifikai0[ilay][ixy][ich],Zyou);
	    goukei0_1[ilay][ixy] = goukei0_1[ilay][ixy]+pow(scifikai0[ilay][ixy][ich],Zyou)*hosei0[ilay][ixy][ich];
	  }
	}
	if(max0[ilay][ixy]<=SH){
	  zyuusinn0[ilay][ixy]=0;
	}
	      
	if(goukei0[ilay][ixy]>PSH/2 && goukei0[ilay][ixy]/sumscifi0[ilay][ixy]>Ma0/2){
	  zyuusinn0[ilay][ixy]=goukei0_1[ilay][ixy]/goukei0[ilay][ixy];
	}
	if(goukei0[ilay][ixy]<=PSH){
	  zyuusinn0[ilay][ixy]=0;
	}
      }
      if(saidai0[ilay][ixy]==0 || saidai0[ilay][ixy]==19){
	if(max0[ilay][ixy]>SH){
	  zyuusinn0[ilay][ixy]=saidai0[ilay][ixy]+0.5;
	}
	if(max0[ilay][ixy]<=SH){
	  zyuusinn0[ilay][ixy]=0;
	}
      }
      //20mmtower
      
      //40mmtower
      if(saidai1[ilay][ixy]>1 && saidai1[ilay][ixy]<38){
	if(max1[ilay][ixy]>SH){
	  for(int ich=saidai1[ilay][ixy]-2;ich<saidai1[ilay][ixy]+3;++ich){
	    goukei1[ilay][ixy] = goukei1[ilay][ixy]+pow(scifikai1[ilay][ixy][ich],Zyou);
	    goukei1_1[ilay][ixy] = goukei1_1[ilay][ixy]+pow(scifikai1[ilay][ixy][ich],Zyou)*hosei1[ilay][ixy][ich];
	  }
	}
	if(max1[ilay][ixy]<=SH){
	  zyuusinn1[ilay][ixy]=0;
	}
	
	if(goukei1[ilay][ixy]>PSH && goukei1[ilay][ixy]/sumscifi1[ilay][ixy]>Ma1){
	  zyuusinn1[ilay][ixy]=goukei1_1[ilay][ixy]/goukei1[ilay][ixy];
	}
	if(goukei1[ilay][ixy]<=PSH){
	  zyuusinn1[ilay][ixy]=0;
	}
	
      }
      if(saidai1[ilay][ixy]==1 || saidai1[ilay][ixy]==38){
	if(max1[ilay][ixy]>SH){
	  for(int ich=saidai1[ilay][ixy]-1; ich<saidai1[ilay][ixy]+2; ++ich){
	    goukei1[ilay][ixy] = goukei1[ilay][ixy]+pow(scifikai1[ilay][ixy][ich],Zyou);
	    goukei1_1[ilay][ixy] = goukei1_1[ilay][ixy]+pow(scifikai1[ilay][ixy][ich],Zyou)*hosei1[ilay][ixy][ich];
	  }
	}
	if(max1[ilay][ixy]<=SH){
	  zyuusinn1[ilay][ixy]=0;
	}
	      
	if(goukei1[ilay][ixy]>PSH/2 && goukei1[ilay][ixy]/sumscifi1[ilay][ixy]>Ma1/2){
	  zyuusinn1[ilay][ixy]=goukei1_1[ilay][ixy]/goukei1[ilay][ixy];         
	}
	if(goukei1[ilay][ixy]<=PSH){
	  zyuusinn1[ilay][ixy]=0;
	}
      }
      if(saidai1[ilay][ixy]==0 || saidai1[ilay][ixy]==39){
	if(max1[ilay][ixy]>SH){
	  zyuusinn1[ilay][ixy]=saidai1[ilay][ixy]+0.5;
	}
	if(max1[ilay][ixy]<=SH){
	  zyuusinn1[ilay][ixy]=0;
	}
      }
      //40mmtower
    }
  }

}

void SciFiPosCalculation::scifipos_fill(A1Phys *a1phys){

  for(int itow=0; itow<2; ++itow){

    a1phys->hits[itow]=0;      

    if(itow==0){
      
      if( zyuusinn0[1][0]!=0 &&  zyuusinn0[1][1]!=0 ){
	// --- for EM ---
	a1phys->pos[itow][0]=zyuusinn0[1][0];
	a1phys->pos[itow][1]=zyuusinn0[1][1];
	a1phys->hits[itow]=1;
      }else if(zyuusinn0[3][0]!=0 && zyuusinn0[3][1]!=0){
	// --- for Hadron ---
	cout<<"SFPC check: "<<zyuusinn0[3][0]<<"  "<< zyuusinn0[3][0] <<endl;
	a1phys->pos[itow][0]=zyuusinn0[3][0];
	a1phys->pos[itow][1]=zyuusinn0[3][1];
	a1phys->hits[itow]=1;
      }else{
	a1phys->pos[itow][0]=-10;
	a1phys->pos[itow][1]=-10;
	a1phys->hits[itow]=0;
      }
      
    }else if(itow==1){
      
      if( zyuusinn1[1][0]!=0 && zyuusinn1[1][1]!=0 ){
	// --- for EM --- 
	a1phys->pos[itow][0]=zyuusinn1[1][0];
	a1phys->pos[itow][1]=zyuusinn1[1][1];
	a1phys->hits[itow]=1;
      }else if( zyuusinn1[3][0]!=0 && zyuusinn1[3][1]!=0){ 
	// --- for hadron ---
	a1phys->pos[itow][0]=zyuusinn1[3][0];
	a1phys->pos[itow][1]=zyuusinn1[3][1];
	a1phys->hits[itow]=1;
      }else{
	a1phys->pos[itow][0]=-10;
	a1phys->pos[itow][1]=-10;
	a1phys->hits[itow]=0;
      }
      
    }       

  }

}

// void SciFiPosCalculation::scifipos_fill(A1Phys *a1phys){

//   for(int itow=0; itow<2; ++itow){
//     a1phys->hits[itow]=0;
      
//     for(int ixy=0; ixy<2; ++ixy){
//       a1phys->pos[itow][ixy] = 0;
//       switch(itow)
// 	{
// 	case 0:
// 	  if(zyuusinn0[1][ixy]!=0)
// 	    {
// 	      a1phys->pos[itow][ixy]=zyuusinn0[1][ixy];
// 	      a1phys->hits[itow]=1;
// 	      //if(xy==0)cout<<"SciFipos 20mm_x  "<<a1phys->pos[tower][xy]<<endl;
// 	      //if(xy==1)cout<<"SciFipos 20mm_y  "<<a1phys->pos[tower][xy]<<endl;
// 	    }
// 	  if(zyuusinn0[1][ixy]==0)
// 	    {
// 	      a1phys->pos[itow][ixy]=-10;
// 	      //if(xy==0)cout<<"SciFipos 20mm_x  "<<a1phys->pos[tower][xy]<<endl;
// 	      //if(xy==1)cout<<"SciFipos 20mm_y  "<<a1phys->pos[tower][xy]<<endl;
// 	    }
// 	  break;
	  
// 	case 1:
// 	  if(zyuusinn1[1][ixy]!=0)
// 	    {
// 	      a1phys->pos[itow][ixy]=zyuusinn1[1][ixy];
// 	      a1phys->hits[itow]=1;
// 	      //if(xy==0)cout<<"SciFipos 40mm_x  "<<a1phys->pos[tower][xy]<<endl;
// 	      //if(xy==1)cout<<"SciFipos 40mm_y  "<<a1phys->pos[tower][xy]<<endl;
// 	    }
// 	  if(zyuusinn1[1][ixy]==0)
// 	    {
// 	      a1phys->pos[itow][ixy]=-10;
// 	      //if(xy==0)cout<<"SciFipos 40mm_x  "<<a1phys->pos[tower][xy]<<endl;
// 	      //if(xy==1)cout<<"SciFipos 40mm_y  "<<a1phys->pos[tower][xy]<<endl;
// 	    }
// 	  break;
// 	}
//     }
//   }

// }

#endif
