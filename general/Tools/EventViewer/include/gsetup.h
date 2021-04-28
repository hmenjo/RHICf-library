#ifndef ROOT_GSETUP
#define   ROOT_GSETUP

#include <iostream>
#include <iomanip>
#include <TStyle.h>
using namespace std;

void gsetup() {
  //*** Setup of the presentation style ***
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(1);
  gStyle->SetLabelSize(0.05,"x");
  gStyle->SetLabelOffset(0.01,"x");
  gStyle->SetLabelSize(0.05,"y");
  gStyle->SetLabelOffset(0.005,"y");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.15);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleW(0.4);
/*   gStyle->SetTitleColor(0); */
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleSize(0.05,"x");
  gStyle->SetTitleSize(0.045,"y");
  gStyle->SetTitleOffset(1.00,"x");
  gStyle->SetTitleOffset(1.05,"y");
  gStyle->SetPadColor(0);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);

  gStyle->SetMarkerStyle(2);
  gStyle->SetStatColor(0);
  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.25);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetPalette(1);
  return ;
}

void gsetup_new(){
  //*** for root ver 4.01/02 ***
  gsetup();
  gStyle->ToggleEditor();
  gStyle->ToggleEventStatus();
}

void gsetup_special() {
  //*** Setup of the presentation style ***
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetLabelSize(0.08,"x");
  gStyle->SetLabelOffset(-0.007,"x");
  gStyle->SetLabelSize(0.06,"y");
  gStyle->SetLabelOffset(0.005,"y");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleW(0.3);
/*   gStyle->SetTitleColor(0); */
  gStyle->SetTitleSize(0.08,"x");
  gStyle->SetTitleSize(0.09,"y");
  gStyle->SetTitleOffset(0.90,"x");
  gStyle->SetTitleOffset(0.6,"y");
  gStyle->SetPadColor(3);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);
}

void gsetup12() {
  //*** Setup of the presentation style ***
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetLabelSize(0.05,"x");
  gStyle->SetLabelOffset(0.02,"x");
  gStyle->SetLabelSize(0.06,"y");
  gStyle->SetLabelOffset(0.005,"y");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleW(0.3);
/*   gStyle->SetTitleColor(0); */
  gStyle->SetTitleSize(0.06,"x");
  gStyle->SetTitleSize(0.06,"y");
  gStyle->SetTitleOffset(0.90,"x");
  gStyle->SetTitleOffset(0.95,"y");
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);
}

void gsetup13() {
  //*** Setup of the presentation style ***
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetLabelSize(0.07,"x");
  gStyle->SetLabelOffset(0.01,"x");
  gStyle->SetLabelSize(0.08 ,"y");
  gStyle->SetLabelOffset(0.005,"y");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleH(0.10);
  gStyle->SetTitleW(0.3);
/*   gStyle->SetTitleColor(0); */
  gStyle->SetTitleSize(0.06,"x");
  gStyle->SetTitleSize(0.08,"y");
  gStyle->SetTitleOffset(0.90,"x");
  gStyle->SetTitleOffset(0.75,"y");
  gStyle->SetPadTopMargin(0.12);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);
}

void gsetup14() {
  //*** Setup of the presentation style ***
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetLabelSize(0.08,"x");
  gStyle->SetLabelOffset(-0.00,"x");
  gStyle->SetLabelSize(0.08,"Y");
  gStyle->SetLabelOffset(0.005,"Y");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(1.0);
  gStyle->SetTitleH(0.10);
  gStyle->SetTitleW(0.3);
  //  gStyle->SetTitleColor(0);
  gStyle->SetTitleSize(0.08,"x");
  gStyle->SetTitleSize(0.08,"y");
  gStyle->SetTitleOffset(0.80,"x");
  gStyle->SetTitleOffset(0.65,"y");
  gStyle->SetPadTopMargin(0.12);
  gStyle->SetPadBottomMargin(0.14);
  gStyle->SetPadLeftMargin(0.12);
}

void gsetup15() {
  //*** Setup of the presentation style ***
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetLabelSize(0.09,"x");
  gStyle->SetLabelOffset(0.0,"x");
  gStyle->SetLabelSize(0.09,"y");
  gStyle->SetLabelOffset(0.005,"y");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleH(0.12);
  gStyle->SetTitleW(0.3);
/*   gStyle->SetTitleColor(0); */
  gStyle->SetTitleSize(0.10,"x");
  gStyle->SetTitleSize(0.10,"y");
  gStyle->SetTitleOffset(0.55,"x");
  gStyle->SetTitleOffset(0.55,"y");
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);
}

void gsetup16() {
  //*** Setup of the presentation style ***
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetLabelSize(0.09,"x");
  gStyle->SetLabelOffset(0.0,"x");
  gStyle->SetLabelSize(0.10,"y");
  gStyle->SetLabelOffset(0.005,"y");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleH(0.12);
  gStyle->SetTitleW(0.3);
/*   gStyle->SetTitleColor(0); */
  gStyle->SetTitleSize(0.10,"x");
  gStyle->SetTitleSize(0.10,"y");
  gStyle->SetTitleOffset(0.55,"x");
  gStyle->SetTitleOffset(0.45,"y");
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);
}

void gsetup22() {
  //*** Setup of the presentation style ***
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetLabelSize(0.04,"x");
  gStyle->SetLabelOffset(-0.004,"x");
  gStyle->SetLabelSize(0.04,"y");
  gStyle->SetLabelOffset(0.005,"y");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleH(0.12);
  gStyle->SetTitleW(0.3);
/*   gStyle->SetTitleColor(0); */
  gStyle->SetTitleSize(0.06,"x");
  gStyle->SetTitleSize(0.05,"y");
  gStyle->SetTitleOffset(0.8,"x");
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);
}

void gsetup33() {
  //*** Setup of the presentation style ***
  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetLabelSize(0.05,"x");
  gStyle->SetLabelOffset(-0.004,"x");
  gStyle->SetLabelSize(0.03,"y");
  gStyle->SetLabelOffset(0.005,"y");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleH(0.12);
  gStyle->SetTitleW(0.3);
/*   gStyle->SetTitleColor(0); */
  gStyle->SetTitleSize(0.06,"x");
  gStyle->SetTitleSize(0.05,"y");
  gStyle->SetTitleOffset(0.8,"x");
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);
}

#ifndef COLMAX
#define COLMAX 256
#endif
void set_fine_monochro(int colNum) {
  int pm = colNum/abs(colNum);
  colNum *= pm;

  if ( colNum>COLMAX ) {
    cout << "COLMAX = " << COLMAX << " ; colNum is set to be " << COLMAX << endl;
    colNum = COLMAX;
  }

  Double_t pred[COLMAX], pgreen[COLMAX], pblue[COLMAX], length[COLMAX];
  for ( int i=0; i<colNum; i++) {
    pred[i] = (float)i/(float)(colNum-1);
    pblue[i] = (float)i/(float)(colNum-1);
    pgreen[i] = (float)i/(float)(colNum-1);
    if ( pm<0 ) {
      pred[i] = 1 - pred[i];
      pblue[i] = 1 - pblue[i];
      pgreen[i] = 1 - pgreen[i];
    }
    length[i] = (float)i/(float)(colNum-1);
  }

  gStyle->SetNumberContours(colNum); 



  return;
}

void set_fine_spectle(int colNum) {

  int pm = colNum/abs(colNum);
  colNum *= pm;

  if ( colNum>COLMAX ) {
    cout << "COLMAX = " << COLMAX << " ; colNum is set to be " << COLMAX << endl;
    colNum = COLMAX;
  }

  Double_t pred[COLMAX], pgreen[COLMAX], pblue[COLMAX], length[COLMAX];
  int j;

  for ( int i=0; i<colNum; i++) {
    j = i;
    if ( pm<0 ) j = colNum - i -1;

    if ( i<colNum/3.0 ) {
      pred[j] = 0.0;
      pgreen[j] = sin(3.141592*i*3.0/(2.0*colNum));
      pblue[j] = 1.0;
    } else if ( i<2.0*colNum/3.0 ) {
      pred[j] = sin(3.141592*(3.0*i/(1.0*colNum)-3.0/2.0));
      pgreen[j] = 1.0;
      pblue[j] = -sin(3.141592*(3.0*i/(1.0*colNum)-3.0/2.0));
      if (pred[j]<0.0) pred[j]=0.0;
      if (pblue[j]<0.0) pblue[j]=0.0;
    } else {
      pred[j] = 1.0;
      pgreen[j] = sin(3.141592*((i-1.0*colNum/3.0)*3.0/(2.0*colNum)));
      pblue[j] = 0.0;
    }

    length[i] = (float)i/(float)(colNum-1);

  }

  gStyle->SetNumberContours(colNum); 



  return;
}

char* fcantitle(){
  char *title = new char[100];
  for(int ic=0;ic<100;ic++){
   sprintf(title,"canvas%d",ic);
   if(gROOT->FindObject(title)==0){break;}
  }
  return title;
}
#endif
