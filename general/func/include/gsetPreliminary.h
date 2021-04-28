#ifndef __GSETPRELIMINARY_H__
#define __GSETPRELIMINARY_H__

//--------------------------------------------------------------
//                   For Preliminary plot   
//
//  Example:  
//      TCanvas *c = new TCanvas();     
//      preliminary()                <----
//      ..
//      h->Draw();
//      set_preliminary();           <----
//      
//--------------------------------------------------------------


TPad* preliminary(double x=0.3,double y=0.1,double angle=+45){
  static int icall=0;
 
  TPad* g = (TPad*)gPad;
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFillStyle(0);
  TLatex* text = new TLatex(x,y,"Preliminary");
  text->SetTextColor(kMagenta-10);
  text->SetTextSize(0.2);
  text->SetTextAngle(angle);
  text->Draw();
  char name[50];
  sprintf(name,"_pad_preliminary_%d",icall);
  TPad *pad_p = new TPad(name,"",0.0,0.0,1.0,1.0);
  pad_p->SetFillStyle(0);
  pad_p->SetFrameFillStyle(0);
  pad_p->Draw();
  pad_p->cd();
  
  return (TPad*)gPad;
}

void set_preliminary(){
  gPad->SetFrameFillStyle(0);
  gPad->SetFillStyle(0);
  gPad->Update();
  if(gPad->FindObject("title") ){
    ((TPaveText*)(gPad->FindObject("title")))->SetFillStyle(0);
  }
}

#endif
