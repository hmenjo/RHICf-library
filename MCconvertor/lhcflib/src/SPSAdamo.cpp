#ifndef __SPSADAMO_CPP__
#define __SPSADAMO_CPP__

#include "SPSAdamo.h"

//----------------------------------------------------------------
//
//  Data structure for ADAMO at SPS beam test in 2007
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  13 Mar. 10: First edited by H.MENJO
//  04 Oct. 10: Modified for the beam test in 2010
//              Added SR[NSR], eventcounter
//---------------------------------------------------------------- 

#if !defined(__CINT__)
ClassImp(SPSAdamo);
#endif

const int SPSAdamo::NSR;
const int SPSAdamo::NLAYER;
const int SPSAdamo::NXY;
const int SPSAdamo::NSTRIP;

int SPSAdamo::clear(){
  run     = 0;
  number  = 0;
  gnumber = 0;

  valid   = true;
  
  for(int isr=0;isr<NSR;isr++){
    SR[isr] = 0;
  }
  
  for(int il=0;il<NLAYER;il++){
    for(int ixy=0;ixy<NXY;ixy++){
      for(int istrip=0;istrip<NSTRIP;istrip++){
	strip[il][ixy][istrip] = 0.;
      }
    }
  }
  
  eventcounter = 0;
  
  return OK;
}

int SPSAdamo::copy(SPSAdamo* d){
  // Copy data, name and title of "d" to "this"
  
  this->SetName(d->GetName());
  this->SetTitle(d->GetTitle());
  return copydata(d);
}

int SPSAdamo::copydata(SPSAdamo* d){
  // Copy only data of "d" to "this"

  this->run      = d->run;
  this->number   = d->number;
  this->gnumber  = d->gnumber; 
  
  this->valid    = d->valid; 

  for(int isr=0;isr<NSR;isr++){
    SR[isr] = d->SR[isr];
  }
  
  for(int il=0;il<NLAYER;il++){
    for(int ixy=0;ixy<NXY;ixy++){
      for(int istrip=0;istrip<NSTRIP;istrip++){
	this->strip[il][ixy][istrip] = d->strip[il][ixy][istrip];
      }
    }
  }

  eventcounter = d->eventcounter;

  return OK;
}

int SPSAdamo::add(SPSAdamo* d){
  // Add data of "d" from this

  //   this->run      = d->run;
  //   this->number   = d->number;
  //   this->gnumber  = d->gnumber; 
  
  //for(int isr=0;isr<NSR;isr++){
  //  SR[isr] += d->SR[isr];
  //}
   
  for(int il=0;il<NLAYER;il++){
    for(int ixy=0;ixy<NXY;ixy++){
      for(int istrip=0;istrip<NSTRIP;istrip++){
	this->strip[il][ixy][istrip] += d->strip[il][ixy][istrip];
      }
    }
  }
  
  //eventcounter += d->eventcounter;
  
  return OK;  
}

int SPSAdamo::subtract(SPSAdamo* d){
  // Subtract data of "d" from this

  //   this->run      = d->run;
  //   this->number   = d->number;
  //   this->gnumber  = d->gnumber; 

  //for(int isr=0;isr<NSR;isr++){
  //  SR[isr] -= d->SR[isr];
  //}
  
  for(int il=0;il<NLAYER;il++){
    for(int ixy=0;ixy<NXY;ixy++){
      for(int istrip=0;istrip<NSTRIP;istrip++){
	this->strip[il][ixy][istrip] -= d->strip[il][ixy][istrip];
      }
    }
  }

  //eventcounter -= d->eventcounter;

  return OK;
}

int SPSAdamo::multiply(double d){
  // Multiply data by the given factor of "d"

  //   this->run      = d->run;
  //   this->number   = d->number;
  //   this->gnumber  = d->gnumber; 
  
  for(int il=0;il<NLAYER;il++){
    for(int ixy=0;ixy<NXY;ixy++){
      for(int istrip=0;istrip<NSTRIP;istrip++){
	this->strip[il][ixy][istrip] *= d;
      }
    }
  }
  
  return OK;
}

int SPSAdamo::divide(double d){
  // divide by "d" (just alias multiply(1./d))
  return multiply(1./d);

}

bool SPSAdamo::IsValidStrip(int il,int ixy,int is){
  // Valid channel. if it is valid, return true.
  // This is a static function.
  if(IsDeadStrip(il,ixy,is)==false && 
     IsIwataStrip(il,ixy,is)==false &&
     IsBadStrip(il,ixy,is)==false){
    return true;
  }
  else{
    return false;
  }
}

bool SPSAdamo::IsIwataStrip(int il,int ixy,int is){
  //Dead channel: if the pedestal RMS is smaller than 5.0 and it has no signal bigger than 40[ADC]
  //Bad channel: if the pedestal RMS is bigger than the criteria
  //       if(il==0 && ixy==0) {criteria = 10.;}
  //       if(il==1 && ixy==0) {criteria =  7.5;}
  //       if(il==2 && ixy==0) {criteria = 10.;}   
  //       if(il==3 && ixy==0) {criteria = 11.;}
  //       if(il==4 && ixy==0) {criteria = 10.;}
  //       if(il==0 && ixy==1) {criteria = 10.;}
  //       if(il==1 && ixy==1) {criteria = 13.;}
  //       if(il==2 && ixy==1) {criteria = 10.;}   
  //       if(il==3 && ixy==1) {criteria = 14.;}
  //       if(il==4 && ixy==1) {criteria = 14.;}
  //Dead ch
  if(il==4){
    if(ixy==0){
      if(is==1005){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    if(ixy==1){
      if(is==15){return true;}
      if(is==27){return true;}
      if(is==61){return true;}
      if(is==62){return true;}
      if(is==109){return true;}
      if(is==110){return true;}
      if(is==111){return true;}
      if(is==112){return true;}
      if(is==113){return true;}
      if(is==114){return true;}
      if(is==158){return true;}
      if(is==159){return true;}
      if(is==211){return true;}
      if(is==212){return true;}
      if(is==251){return true;}
      if(is==159){return true;}
      if(is==384){return true;}
      if(is==406){return true;}
      if(is==418){return true;}
      if(is==469){return true;}
      if(is==522){return true;}
      if(is==549){return true;}
      if(is==550){return true;}
      if(is==553){return true;}
      if(is==633){return true;}
      if(is==657){return true;}
      if(is==759){return true;}
      if(is==964){return true;}
    }
  }
  //Bad ch
  if(il==0){
    if(ixy==0){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==15){return true;}
      if(is==16){return true;}
      if(is==17){return true;}
      if(is==18){return true;}
      if(is==19){return true;}
      if(is==20){return true;}
      if(is==21){return true;}
      if(is==206){return true;}
      if(is==207){return true;}
      if(is==208){return true;}
      if(is==211){return true;}
      if(is==212){return true;}
      if(is==258){return true;}
      if(is==500){return true;}
      if(is==501){return true;}
      if(is==560){return true;}
      if(is==561){return true;}
      if(is==562){return true;}
      if(is==563){return true;}
      if(is==564){return true;}
      if(is==565){return true;}
      if(is==566){return true;}
      if(is==567){return true;}
      if(is==568){return true;}
      if(is==569){return true;}
      if(is==570){return true;}
      if(is==571){return true;}
      if(is==572){return true;}
      if(is==573){return true;}
      if(is==574){return true;}
      if(is==575){return true;}
      if(is==576){return true;}
      if(is==577){return true;}
      if(is==578){return true;}
      if(is==579){return true;}
      if(is==580){return true;}
      if(is==581){return true;}
      if(is==582){return true;}
      if(is==583){return true;}
      if(is==584){return true;}
      if(is==585){return true;}
      if(is==586){return true;}
      if(is==587){return true;}
      if(is==588){return true;}
      if(is==601){return true;}
      if(is==602){return true;}
      if(is==603){return true;}
      if(is==604){return true;}
      if(is==605){return true;}
      if(is==606){return true;}
      if(is==634){return true;}
      if(is==635){return true;}
      if(is==636){return true;}
      if(is==641){return true;}
      if(is==642){return true;}
      if(is==643){return true;}
      if(is==729){return true;}
      if(is==730){return true;}
      if(is==731){return true;}
      if(is==732){return true;}
      if(is==733){return true;}
      if(is==734){return true;}
      if(is==735){return true;}
      if(is==736){return true;}
      if(is==737){return true;}
      if(is==738){return true;}
      if(is==739){return true;}
      if(is==740){return true;}
      if(is==741){return true;}
      if(is==760){return true;}
      if(is==761){return true;}
      if(is==826){return true;}
      if(is==827){return true;}
      if(is==836){return true;}
      if(is==837){return true;}
      if(is==838){return true;}
      if(is==839){return true;}
      if(is==840){return true;}
      if(is==841){return true;}
      if(is==842){return true;}
      if(is==843){return true;}
      if(is==844){return true;}
      if(is==845){return true;}
      if(is==846){return true;}
      if(is==847){return true;}
      if(is==848){return true;}
      if(is==849){return true;}
      if(is==850){return true;}
      if(is==862){return true;}
      if(is==958){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    if(ixy==1){
      if(is==25){return true;}
      if(is==26){return true;}
      if(is==27){return true;}
      if(is==28){return true;}
      if(is==44){return true;}
      if(is==45){return true;}
      if(is==130){return true;}
      if(is==131){return true;}
      if(is==173){return true;}
      if(is==222){return true;}
      if(is==223){return true;}
      if(is==224){return true;}
      if(is==235){return true;}
      if(is==255){return true;}
      if(is==257){return true;}
      if(is==275){return true;}
      if(is==276){return true;}
      if(is==291){return true;}
      if(is==292){return true;}
      if(is==342){return true;}
      if(is==343){return true;}
      if(is==378){return true;}
      if(is==379){return true;}
      if(is==380){return true;}
      if(is==381){return true;}
      if(is==397){return true;}
      if(is==398){return true;}
      if(is==399){return true;}
      if(is==400){return true;}
      if(is==401){return true;}
      if(is==402){return true;}
      if(is==419){return true;}
      if(is==420){return true;}
      if(is==466){return true;}
      if(is==467){return true;}
      if(is==470){return true;}
      if(is==488){return true;}
      if(is==496){return true;}
      if(is==497){return true;}
      if(is==511){return true;}
      if(is==523){return true;}
      if(is==524){return true;}
      if(is==525){return true;}
      if(is==533){return true;}
      if(is==534){return true;}
      if(is==562){return true;}
      if(is==586){return true;}
      if(is==587){return true;}
      if(is==697){return true;}
      if(is==699){return true;}
      if(is==701){return true;}
      if(is==703){return true;}
      if(is==705){return true;}
      if(is==707){return true;}
      if(is==732){return true;}
      if(is==733){return true;}
      if(is==785){return true;}
      if(is==839){return true;}
      if(is==841){return true;}
      if(is==867){return true;}
      if(is==869){return true;}
      if(is==906){return true;}
      if(is==928){return true;}
      if(is==963){return true;}
      if(is==964){return true;}
      if(is==975){return true;}
      if(is==976){return true;}
      if(is==983){return true;}
      if(is==985){return true;}
      if(is==993){return true;}
      if(is==994){return true;}
      if(is==1001){return true;}
      if(is==1003){return true;}
      if(is==1005){return true;}
      if(is==1007){return true;}
      if(is==1008){return true;}
      if(is==1009){return true;}
    }
  }
  if(il==1){
    if(ixy==0){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==3){return true;}
      if(is==39){return true;}
      if(is==40){return true;}
      if(is==42){return true;}
      if(is==45){return true;}
      if(is==64){return true;}
      if(is==65){return true;}
      if(is==66){return true;}
      if(is==67){return true;}
      if(is==68){return true;}
      if(is==69){return true;}
      if(is==70){return true;}
      if(is==109){return true;}
      if(is==270){return true;}
      if(is==271){return true;}
      if(is==274){return true;}
      if(is==275){return true;}
      if(is==276){return true;}
      if(is==277){return true;}
      if(is==279){return true;}
      if(is==280){return true;}
      if(is==283){return true;}
      if(is==284){return true;}
      if(is==285){return true;}
      if(is==286){return true;}
      if(is==287){return true;}
      if(is==288){return true;}
      if(is==289){return true;}
      if(is==290){return true;}
      if(is==291){return true;}
      if(is==292){return true;}
      if(is==293){return true;}
      if(is==297){return true;}
      if(is==298){return true;}
      if(is==299){return true;}
      if(is==300){return true;}
      if(is==301){return true;}
      if(is==302){return true;}
      if(is==303){return true;}
      if(is==304){return true;}
      if(is==305){return true;}
      if(is==306){return true;}
      if(is==307){return true;}
      if(is==308){return true;}
      if(is==309){return true;}
      if(is==310){return true;}
      if(is==337){return true;}
      if(is==338){return true;}
      if(is==344){return true;}
      if(is==346){return true;}
      if(is==347){return true;}
      if(is==348){return true;}
      if(is==349){return true;}
      if(is==350){return true;}
      if(is==351){return true;}
      if(is==352){return true;}
      if(is==353){return true;}
      if(is==354){return true;}
      if(is==355){return true;}
      if(is==356){return true;}
      if(is==357){return true;}
      if(is==358){return true;}
      if(is==359){return true;}
      if(is==360){return true;}
      if(is==361){return true;}
      if(is==362){return true;}
      if(is==363){return true;}
      if(is==364){return true;}
      if(is==365){return true;}
      if(is==366){return true;}
      if(is==367){return true;}
      if(is==368){return true;}
      if(is==369){return true;}
      if(is==370){return true;}
      if(is==371){return true;}
      if(is==372){return true;}
      if(is==373){return true;}
      if(is==374){return true;}
      if(is==375){return true;}
      if(is==376){return true;}
      if(is==377){return true;}
      if(is==383){return true;}
      if(is==384){return true;}
      if(is==385){return true;}
      if(is==386){return true;}
      if(is==387){return true;}
      if(is==396){return true;}
      if(is==422){return true;}
      if(is==423){return true;}
      if(is==502){return true;}
      if(is==503){return true;}
      if(is==504){return true;}
      if(is==511){return true;}
      if(is==512){return true;}
      if(is==554){return true;}
      if(is==555){return true;}
      if(is==600){return true;}
      if(is==601){return true;}
      if(is==602){return true;}
      if(is==603){return true;}
      if(is==604){return true;}
      if(is==605){return true;}
      if(is==606){return true;}
      if(is==607){return true;}
      if(is==608){return true;}
      if(is==609){return true;}
      if(is==610){return true;}
      if(is==611){return true;}
      if(is==612){return true;}
      if(is==613){return true;}
      if(is==619){return true;}
      if(is==620){return true;}
      if(is==621){return true;}
      if(is==622){return true;}
      if(is==623){return true;}
      if(is==640){return true;}
      if(is==641){return true;}
      if(is==642){return true;}
      if(is==643){return true;}
      if(is==644){return true;}
      if(is==666){return true;}
      if(is==667){return true;}
      if(is==668){return true;}
      if(is==735){return true;}
      if(is==736){return true;}
      if(is==743){return true;}
      if(is==744){return true;}
      if(is==781){return true;}
      if(is==782){return true;}
      if(is==783){return true;}
      if(is==845){return true;}
      if(is==846){return true;}
      if(is==853){return true;}
      if(is==905){return true;}
      if(is==980){return true;}
      if(is==1002){return true;}
      if(is==1020){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    if(ixy==1){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==44){return true;}
      if(is==45){return true;}
      if(is==80){return true;}
      if(is==81){return true;}
      if(is==193){return true;}
      if(is==195){return true;}
      if(is==196){return true;}
      if(is==248){return true;}
      if(is==256){return true;}
      if(is==257){return true;}
      if(is==258){return true;}
      if(is==275){return true;}
      if(is==276){return true;}
      if(is==333){return true;}
      if(is==334){return true;}
      if(is==451){return true;}
      if(is==452){return true;}
      if(is==460){return true;}
      if(is==461){return true;}
      if(is==462){return true;}
      if(is==465){return true;}
      if(is==542){return true;}
      if(is==555){return true;}
      if(is==556){return true;}
      if(is==587){return true;}
      if(is==588){return true;}
      if(is==599){return true;}
      if(is==606){return true;}
      if(is==607){return true;}
      if(is==652){return true;}
      if(is==659){return true;}
      if(is==664){return true;}
      if(is==665){return true;}
      if(is==666){return true;}
      if(is==678){return true;}
      if(is==679){return true;}
      if(is==728){return true;}
      if(is==729){return true;}
      if(is==782){return true;}
      if(is==959){return true;}
      if(is==961){return true;}
      if(is==962){return true;}
      if(is==963){return true;}
      if(is==970){return true;}
      if(is==985){return true;}
    }
  }
  if(il==2){
    if(ixy==0){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==10){return true;}
      if(is==579){return true;}
      if(is==862){return true;}
      if(is==895){return true;}
      if(is==896){return true;}
      if(is==947){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    if(ixy==1){
      if(is==47){return true;}
      if(is==82){return true;}
      if(is==166){return true;}
      if(is==198){return true;}
      if(is==463){return true;}
      if(is==464){return true;}
      if(is==550){return true;}
      if(is==551){return true;}
      if(is==618){return true;}
      if(is==635){return true;}
      if(is==636){return true;}
      if(is==653){return true;}
      if(is==654){return true;}
      if(is==655){return true;}
      if(is==851){return true;}
      if(is==852){return true;}
      if(is==853){return true;}
      if(is==900){return true;}
      if(is==901){return true;}
      if(is==968){return true;}
      if(is==1017){return true;}
      if(is==1020){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
  }
  if(il==3){
    if(ixy==0){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==4){return true;}
      if(is==5){return true;}
      if(is==6){return true;}
      if(is==131){return true;}
      if(is==148){return true;}
      if(is==234){return true;}
      if(is==261){return true;}
      if(is==262){return true;}
      if(is==263){return true;}
      if(is==267){return true;}
      if(is==270){return true;}
      if(is==271){return true;}
      if(is==272){return true;}
      if(is==273){return true;}
      if(is==274){return true;}
      if(is==290){return true;}
      if(is==291){return true;}
      if(is==292){return true;}
      if(is==293){return true;}
      if(is==294){return true;}
      if(is==295){return true;}
      if(is==296){return true;}
      if(is==297){return true;}
      if(is==298){return true;}
      if(is==299){return true;}
      if(is==300){return true;}
      if(is==301){return true;}
      if(is==304){return true;}
      if(is==305){return true;}
      if(is==306){return true;}
      if(is==307){return true;}
      if(is==308){return true;}
      if(is==309){return true;}
      if(is==310){return true;}
      if(is==311){return true;}
      if(is==312){return true;}
      if(is==313){return true;}
      if(is==314){return true;}
      if(is==315){return true;}
      if(is==316){return true;}
      if(is==317){return true;}
      if(is==318){return true;}
      if(is==319){return true;}
      if(is==320){return true;}
      if(is==321){return true;}
      if(is==322){return true;}
      if(is==323){return true;}
      if(is==324){return true;}
      if(is==325){return true;}
      if(is==339){return true;}
      if(is==340){return true;}
      if(is==341){return true;}
      if(is==342){return true;}
      if(is==343){return true;}
      if(is==366){return true;}
      if(is==367){return true;}
      if(is==368){return true;}
      if(is==369){return true;}
      if(is==370){return true;}
      if(is==371){return true;}
      if(is==372){return true;}
      if(is==373){return true;}
      if(is==374){return true;}
      if(is==375){return true;}
      if(is==376){return true;}
      if(is==377){return true;}
      if(is==378){return true;}
      if(is==379){return true;}
      if(is==380){return true;}
      if(is==381){return true;}
      if(is==382){return true;}
      if(is==383){return true;}
      if(is==384){return true;}
      if(is==385){return true;}
      if(is==386){return true;}
      if(is==387){return true;}
      if(is==388){return true;}
      if(is==389){return true;}
      if(is==390){return true;}
      if(is==391){return true;}
      if(is==392){return true;}
      if(is==393){return true;}
      if(is==394){return true;}
      if(is==395){return true;}
      if(is==396){return true;}
      if(is==397){return true;}
      if(is==398){return true;}
      if(is==399){return true;}
      if(is==400){return true;}
      if(is==401){return true;}
      if(is==402){return true;}
      if(is==403){return true;}
      if(is==404){return true;}
      if(is==405){return true;}
      if(is==406){return true;}
      if(is==407){return true;}
      if(is==408){return true;}
      if(is==409){return true;}
      if(is==410){return true;}
      if(is==411){return true;}
      if(is==412){return true;}
      if(is==413){return true;}
      if(is==414){return true;}
      if(is==415){return true;}
      if(is==416){return true;}
      if(is==417){return true;}
      if(is==448){return true;}
      if(is==449){return true;}
      if(is==669){return true;}
      if(is==670){return true;}
      if(is==683){return true;}
      if(is==684){return true;}
      if(is==685){return true;}
      if(is==709){return true;}
      if(is==710){return true;}
      if(is==724){return true;}
      if(is==725){return true;}
      if(is==762){return true;}
      if(is==822){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    if(ixy==1){
      if(is==11){return true;}
      if(is==12){return true;}
      if(is==13){return true;}
      if(is==14){return true;}
      if(is==15){return true;}
      if(is==16){return true;}
      if(is==25){return true;}
      if(is==26){return true;}
      if(is==355){return true;}
      if(is==430){return true;}
      if(is==431){return true;}
      if(is==449){return true;}
      if(is==450){return true;}
      if(is==459){return true;}
      if(is==460){return true;}
      if(is==467){return true;}
      if(is==468){return true;}
      if(is==491){return true;}
      if(is==493){return true;}
      if(is==496){return true;}
      if(is==497){return true;}
      if(is==507){return true;}
      if(is==522){return true;}
      if(is==573){return true;}
      if(is==609){return true;}
      if(is==626){return true;}
      if(is==653){return true;}
      if(is==654){return true;}
      if(is==662){return true;}
      if(is==679){return true;}
      if(is==765){return true;}
      if(is==776){return true;}
      if(is==818){return true;}
      if(is==819){return true;}
      if(is==843){return true;}
    }
  }
  if(il==4){
    if(ixy==0){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==145){return true;}
      if(is==146){return true;}
      if(is==147){return true;}
      if(is==148){return true;}
      if(is==164){return true;}
      if(is==165){return true;}
      if(is==218){return true;}
      if(is==219){return true;}
      if(is==220){return true;}
      if(is==221){return true;}
      if(is==222){return true;}
      if(is==223){return true;}
      if(is==228){return true;}
      if(is==229){return true;}
      if(is==236){return true;}
      if(is==237){return true;}
      if(is==248){return true;}
      if(is==249){return true;}
      if(is==250){return true;}
      if(is==251){return true;}
      if(is==253){return true;}
      if(is==254){return true;}
      if(is==272){return true;}
      if(is==273){return true;}
      if(is==288){return true;}
      if(is==289){return true;}
      if(is==290){return true;}
      if(is==291){return true;}
      if(is==292){return true;}
      if(is==293){return true;}
      if(is==294){return true;}
      if(is==295){return true;}
      if(is==296){return true;}
      if(is==297){return true;}
      if(is==298){return true;}
      if(is==299){return true;}
      if(is==303){return true;}
      if(is==304){return true;}
      if(is==305){return true;}
      if(is==307){return true;}
      if(is==319){return true;}
      if(is==320){return true;}
      if(is==349){return true;}
      if(is==350){return true;}
      if(is==351){return true;}
      if(is==352){return true;}
      if(is==353){return true;}
      if(is==354){return true;}
      if(is==413){return true;}
      if(is==414){return true;}
      if(is==425){return true;}
      if(is==426){return true;}
      if(is==497){return true;}
      if(is==498){return true;}
      if(is==700){return true;}
      if(is==1005){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    if(ixy==1){
      if(is==15){return true;}
      if(is==27){return true;}
      if(is==61){return true;}
      if(is==62){return true;}
      if(is==109){return true;}
      if(is==110){return true;}
      if(is==111){return true;}
      if(is==112){return true;}
      if(is==113){return true;}
      if(is==114){return true;}
      if(is==158){return true;}
      if(is==159){return true;}
      if(is==211){return true;}
      if(is==212){return true;}
      if(is==251){return true;}
      if(is==384){return true;}
      if(is==406){return true;}
      if(is==418){return true;}
      if(is==469){return true;}
      if(is==522){return true;}
      if(is==549){return true;}
      if(is==550){return true;}
      if(is==553){return true;}
      if(is==633){return true;}
      if(is==657){return true;}
      if(is==759){return true;}
      if(is==964){return true;}
    }
  }
  return false;
}




bool SPSAdamo::IsDeadStrip(int il,int ixy,int is){
  // Dead channel. if it is dead channel, return true.
  // This is a static function.
  // Total number of the dead channles is 442. 
  // These dead channels are identified by using pedestal rms.
  // The criteria are 
  //       if(il==0 && ixy==0) {criteria = 10.;}
  //       if(il==1 && ixy==0) {criteria =  7.5;}
  //       if(il==2 && ixy==0) {criteria = 10.;}   
  //       if(il==3 && ixy==0) {criteria = 11.;}
  //       if(il==4 && ixy==0) {criteria = 10.;}
  //       if(il==0 && ixy==1) {criteria = 10.;}
  //       if(il==1 && ixy==1) {criteria = 13.;}
  //       if(il==2 && ixy==1) {criteria = 10.;}   
  //       if(il==3 && ixy==1) {criteria = 14.;}
  //       if(il==4 && ixy==1) {criteria = 14.;}
  
   if(ixy==0){
    if(il==0){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==353){return true;}
      if(is==1005){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    else if(il==1){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==4){return true;}
      if(is==5){return true;}
      if(is==131){return true;}
      if(is==234){return true;}
      if(is==508){return true;}
      if(is==706){return true;}
      if(is==707){return true;}
      if(is==762){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    else if(il==2){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==861){return true;}
      if(is==894){return true;}
      if(is==896){return true;}
      if(is==947){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    else if(il==3){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==67){return true;}
      if(is==128){return true;}
      if(is==129){return true;}
      if(is==130){return true;}
      if(is==131){return true;}
      if(is==132){return true;}
      if(is==133){return true;}
      if(is==134){return true;}
      if(is==135){return true;}
      if(is==136){return true;}
      if(is==137){return true;}
      if(is==138){return true;}
      if(is==139){return true;}
      if(is==140){return true;}
      if(is==141){return true;}
      if(is==142){return true;}
      if(is==143){return true;}
      if(is==144){return true;}
      if(is==145){return true;}
      if(is==146){return true;}
      if(is==147){return true;}
      if(is==148){return true;}
      if(is==149){return true;}
      if(is==150){return true;}
      if(is==151){return true;}
      if(is==152){return true;}
      if(is==153){return true;}
      if(is==154){return true;}
      if(is==155){return true;}
      if(is==156){return true;}
      if(is==157){return true;}
      if(is==158){return true;}
      if(is==159){return true;}
      if(is==160){return true;}
      if(is==161){return true;}
      if(is==162){return true;}
      if(is==163){return true;}
      if(is==164){return true;}
      if(is==165){return true;}
      if(is==166){return true;}
      if(is==167){return true;}
      if(is==168){return true;}
      if(is==169){return true;}
      if(is==170){return true;}
      if(is==171){return true;}
      if(is==172){return true;}
      if(is==173){return true;}
      if(is==174){return true;}
      if(is==175){return true;}
      if(is==176){return true;}
      if(is==177){return true;}
      if(is==178){return true;}
      if(is==179){return true;}
      if(is==180){return true;}
      if(is==181){return true;}
      if(is==182){return true;}
      if(is==183){return true;}
      if(is==184){return true;}
      if(is==185){return true;}
      if(is==186){return true;}
      if(is==187){return true;}
      if(is==188){return true;}
      if(is==189){return true;}
      if(is==190){return true;}
      if(is==191){return true;}
      if(is==192){return true;}
      if(is==193){return true;}
      if(is==194){return true;}
      if(is==195){return true;}
      if(is==196){return true;}
      if(is==197){return true;}
      if(is==198){return true;}
      if(is==199){return true;}
      if(is==200){return true;}
      if(is==201){return true;}
      if(is==202){return true;}
      if(is==203){return true;}
      if(is==204){return true;}
      if(is==205){return true;}
      if(is==206){return true;}
      if(is==207){return true;}
      if(is==208){return true;}
      if(is==209){return true;}
      if(is==210){return true;}
      if(is==211){return true;}
      if(is==212){return true;}
      if(is==213){return true;}
      if(is==214){return true;}
      if(is==215){return true;}
      if(is==216){return true;}
      if(is==217){return true;}
      if(is==218){return true;}
      if(is==219){return true;}
      if(is==220){return true;}
      if(is==221){return true;}
      if(is==222){return true;}
      if(is==223){return true;}
      if(is==224){return true;}
      if(is==225){return true;}
      if(is==226){return true;}
      if(is==227){return true;}
      if(is==228){return true;}
      if(is==229){return true;}
      if(is==230){return true;}
      if(is==231){return true;}
      if(is==232){return true;}
      if(is==233){return true;}
      if(is==234){return true;}
      if(is==235){return true;}
      if(is==236){return true;}
      if(is==237){return true;}
      if(is==238){return true;}
      if(is==239){return true;}
      if(is==240){return true;}
      if(is==241){return true;}
      if(is==242){return true;}
      if(is==243){return true;}
      if(is==244){return true;}
      if(is==245){return true;}
      if(is==246){return true;}
      if(is==247){return true;}
      if(is==248){return true;}
      if(is==249){return true;}
      if(is==250){return true;}
      if(is==251){return true;}
      if(is==252){return true;}
      if(is==253){return true;}
      if(is==254){return true;}
      if(is==255){return true;}
      if(is==782){return true;}
      if(is==853){return true;}
      if(is==958){return true;}
      if(is==980){return true;}
      if(is==981){return true;}
      if(is==1002){return true;}
      if(is==1020){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    else if(il==4){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==207){return true;}
      if(is==209){return true;}
      if(is==210){return true;}
      if(is==862){return true;}
      if(is==983){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
  }
  else if(ixy==1){
    if(il==0){
      if(is==45){return true;}
      if(is==222){return true;}
      if(is==223){return true;}
      if(is==235){return true;}
      if(is==257){return true;}
      if(is==275){return true;}
      if(is==276){return true;}
      if(is==343){return true;}
      if(is==379){return true;}
      if(is==399){return true;}
      if(is==400){return true;}
      if(is==401){return true;}
      if(is==419){return true;}
      if(is==420){return true;}
      if(is==467){return true;}
      if(is==470){return true;}
      if(is==488){return true;}
      if(is==521){return true;}
      if(is==522){return true;}
      if(is==523){return true;}
      if(is==525){return true;}
      if(is==561){return true;}
      if(is==571){return true;}
      if(is==586){return true;}
      if(is==697){return true;}
      if(is==699){return true;}
      if(is==733){return true;}
      if(is==785){return true;}
      if(is==906){return true;}
      if(is==928){return true;}
      if(is==975){return true;}
      if(is==982){return true;}
      if(is==983){return true;}
      if(is==993){return true;}
      if(is==1001){return true;}
      if(is==1003){return true;}
    }
    else if(il==1){
      if(is==4){return true;}
      if(is==45){return true;}
      if(is==78){return true;}
      if(is==81){return true;}
      if(is==107){return true;}
      if(is==195){return true;}
      if(is==196){return true;}
      if(is==222){return true;}
      if(is==235){return true;}
      if(is==248){return true;}
      if(is==256){return true;}
      if(is==257){return true;}
      if(is==297){return true;}
      if(is==333){return true;}
      if(is==446){return true;}
      if(is==451){return true;}
      if(is==460){return true;}
      if(is==483){return true;}
      if(is==542){return true;}
      if(is==561){return true;}
      if(is==651){return true;}
      if(is==658){return true;}
      if(is==671){return true;}
      if(is==677){return true;}
      if(is==728){return true;}
      if(is==742){return true;}
      if(is==748){return true;}
      if(is==781){return true;}
      if(is==838){return true;}
      if(is==970){return true;}
      if(is==985){return true;}
    }
    else if(il==2){
      if(is==82){return true;}
      if(is==198){return true;}
      if(is==463){return true;}
      if(is==550){return true;}
      if(is==618){return true;}
      if(is==635){return true;}
      if(is==654){return true;}
      if(is==729){return true;}
      if(is==852){return true;}
      if(is==1020){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    else if(il==3){
      if(is==224){return true;}
      if(is==356){return true;}
      if(is==448){return true;}
      if(is==458){return true;}
      if(is==492){return true;}
      if(is==494){return true;}
      if(is==506){return true;}
      if(is==508){return true;}
      if(is==521){return true;}
      if(is==574){return true;}
      if(is==575){return true;}
      if(is==576){return true;}
      if(is==577){return true;}
      if(is==597){return true;}
      if(is==609){return true;}
      if(is==625){return true;}
      if(is==663){return true;}
      if(is==678){return true;}
      if(is==680){return true;}
      if(is==764){return true;}
      if(is==777){return true;}
      if(is==791){return true;}
      if(is==835){return true;}
      if(is==844){return true;}
      if(is==857){return true;}
      if(is==875){return true;}
      if(is==940){return true;}
      if(is==970){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    else if(il==4){
      if(is==13){return true;}
      if(is==14){return true;}
      if(is==26){return true;}
      if(is==60){return true;}
      if(is==250){return true;}
      if(is==256){return true;}
      if(is==257){return true;}
      if(is==258){return true;}
      if(is==259){return true;}
      if(is==260){return true;}
      if(is==261){return true;}
      if(is==262){return true;}
      if(is==263){return true;}
      if(is==264){return true;}
      if(is==265){return true;}
      if(is==266){return true;}
      if(is==267){return true;}
      if(is==268){return true;}
      if(is==269){return true;}
      if(is==270){return true;}
      if(is==271){return true;}
      if(is==272){return true;}
      if(is==273){return true;}
      if(is==274){return true;}
      if(is==275){return true;}
      if(is==276){return true;}
      if(is==277){return true;}
      if(is==278){return true;}
      if(is==279){return true;}
      if(is==280){return true;}
      if(is==281){return true;}
      if(is==282){return true;}
      if(is==283){return true;}
      if(is==284){return true;}
      if(is==285){return true;}
      if(is==286){return true;}
      if(is==287){return true;}
      if(is==288){return true;}
      if(is==289){return true;}
      if(is==290){return true;}
      if(is==291){return true;}
      if(is==292){return true;}
      if(is==293){return true;}
      if(is==294){return true;}
      if(is==295){return true;}
      if(is==296){return true;}
      if(is==297){return true;}
      if(is==298){return true;}
      if(is==299){return true;}
      if(is==300){return true;}
      if(is==301){return true;}
      if(is==302){return true;}
      if(is==303){return true;}
      if(is==304){return true;}
      if(is==305){return true;}
      if(is==306){return true;}
      if(is==307){return true;}
      if(is==308){return true;}
      if(is==309){return true;}
      if(is==310){return true;}
      if(is==311){return true;}
      if(is==312){return true;}
      if(is==313){return true;}
      if(is==314){return true;}
      if(is==315){return true;}
      if(is==316){return true;}
      if(is==317){return true;}
      if(is==318){return true;}
      if(is==319){return true;}
      if(is==320){return true;}
      if(is==321){return true;}
      if(is==322){return true;}
      if(is==323){return true;}
      if(is==324){return true;}
      if(is==325){return true;}
      if(is==326){return true;}
      if(is==327){return true;}
      if(is==328){return true;}
      if(is==329){return true;}
      if(is==330){return true;}
      if(is==331){return true;}
      if(is==332){return true;}
      if(is==333){return true;}
      if(is==334){return true;}
      if(is==335){return true;}
      if(is==336){return true;}
      if(is==337){return true;}
      if(is==338){return true;}
      if(is==339){return true;}
      if(is==340){return true;}
      if(is==341){return true;}
      if(is==342){return true;}
      if(is==343){return true;}
      if(is==344){return true;}
      if(is==345){return true;}
      if(is==346){return true;}
      if(is==347){return true;}
      if(is==348){return true;}
      if(is==349){return true;}
      if(is==350){return true;}
      if(is==351){return true;}
      if(is==352){return true;}
      if(is==353){return true;}
      if(is==354){return true;}
      if(is==355){return true;}
      if(is==356){return true;}
      if(is==357){return true;}
      if(is==358){return true;}
      if(is==359){return true;}
      if(is==360){return true;}
      if(is==361){return true;}
      if(is==362){return true;}
      if(is==363){return true;}
      if(is==364){return true;}
      if(is==365){return true;}
      if(is==366){return true;}
      if(is==367){return true;}
      if(is==368){return true;}
      if(is==369){return true;}
      if(is==370){return true;}
      if(is==371){return true;}
      if(is==372){return true;}
      if(is==373){return true;}
      if(is==374){return true;}
      if(is==375){return true;}
      if(is==376){return true;}
      if(is==377){return true;}
      if(is==378){return true;}
      if(is==379){return true;}
      if(is==380){return true;}
      if(is==381){return true;}
      if(is==382){return true;}
      if(is==383){return true;}
      if(is==384){return true;}
      if(is==407){return true;}
      if(is==468){return true;}
      if(is==499){return true;}
      if(is==523){return true;}
      if(is==550){return true;}
      if(is==554){return true;}
      if(is==634){return true;}
      if(is==656){return true;}
      if(is==658){return true;}
      if(is==757){return true;}
      if(is==933){return true;}
      if(is==963){return true;}
      if(is==965){return true;}
    }
  }

  return false;
}

bool SPSAdamo::IsBadStrip(int il,int ixy,int is){
  // Dead channel. if it is dead channel, return true.
  // This is a static function.
  if(ixy==0){
    if(il==0){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==145){return true;}
      if(is==146){return true;}
      if(is==147){return true;}
      if(is==148){return true;}
      if(is==164){return true;}
      if(is==165){return true;}
      if(is==218){return true;}
      if(is==219){return true;}
      if(is==220){return true;}
      if(is==221){return true;}
      if(is==222){return true;}
      if(is==228){return true;}
      if(is==229){return true;}
      if(is==272){return true;}
      if(is==273){return true;}
      if(is==288){return true;}
      if(is==289){return true;}
      if(is==290){return true;}
      if(is==291){return true;}
      if(is==319){return true;}
      if(is==320){return true;}
      if(is==349){return true;}
      if(is==350){return true;}
      if(is==351){return true;}
      if(is==352){return true;}
      if(is==354){return true;}
      if(is==413){return true;}
      if(is==414){return true;}
      if(is==425){return true;}
      if(is==426){return true;}
      if(is==511){return true;}
      if(is==512){return true;}
      if(is==700){return true;}
      if(is==1003){return true;}
      if(is==1004){return true;}
      if(is==1005){return true;}
      if(is==1006){return true;}
      if(is==1007){return true;}
      if(is==1020){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    else if(il==1){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==3){return true;}
      if(is==4){return true;}
      if(is==5){return true;}
      if(is==6){return true;}
      if(is==97){return true;}
      if(is==131){return true;}
      if(is==144){return true;}
      if(is==146){return true;}
      if(is==148){return true;}
      if(is==149){return true;}
      if(is==150){return true;}
      if(is==234){return true;}
      if(is==261){return true;}
      if(is==262){return true;}
      if(is==263){return true;}
      if(is==270){return true;}
      if(is==271){return true;}
      if(is==272){return true;}
      if(is==273){return true;}
      if(is==274){return true;}
      if(is==291){return true;}
      if(is==292){return true;}
      if(is==293){return true;}
      if(is==294){return true;}
      if(is==295){return true;}
      if(is==296){return true;}
      if(is==297){return true;}
      if(is==299){return true;}
      if(is==300){return true;}
      if(is==309){return true;}
      if(is==310){return true;}
      if(is==311){return true;}
      if(is==312){return true;}
      if(is==313){return true;}
      if(is==314){return true;}
      if(is==315){return true;}
      if(is==317){return true;}
      if(is==318){return true;}
      if(is==319){return true;}
      if(is==320){return true;}
      if(is==321){return true;}
      if(is==322){return true;}
      if(is==323){return true;}
      if(is==324){return true;}
      if(is==339){return true;}
      if(is==340){return true;}
      if(is==341){return true;}
      if(is==342){return true;}
      if(is==367){return true;}
      if(is==368){return true;}
      if(is==369){return true;}
      if(is==370){return true;}
      if(is==371){return true;}
      if(is==372){return true;}
      if(is==373){return true;}
      if(is==374){return true;}
      if(is==375){return true;}
      if(is==376){return true;}
      if(is==377){return true;}
      if(is==378){return true;}
      if(is==379){return true;}
      if(is==380){return true;}
      if(is==381){return true;}
      if(is==382){return true;}
      if(is==383){return true;}
      if(is==384){return true;}
      if(is==385){return true;}
      if(is==386){return true;}
      if(is==387){return true;}
      if(is==388){return true;}
      if(is==389){return true;}
      if(is==390){return true;}
      if(is==391){return true;}
      if(is==392){return true;}
      if(is==393){return true;}
      if(is==394){return true;}
      if(is==395){return true;}
      if(is==396){return true;}
      if(is==397){return true;}
      if(is==398){return true;}
      if(is==399){return true;}
      if(is==400){return true;}
      if(is==401){return true;}
      if(is==402){return true;}
      if(is==403){return true;}
      if(is==404){return true;}
      if(is==405){return true;}
      if(is==406){return true;}
      if(is==407){return true;}
      if(is==408){return true;}
      if(is==409){return true;}
      if(is==410){return true;}
      if(is==411){return true;}
      if(is==413){return true;}
      if(is==414){return true;}
      if(is==415){return true;}
      if(is==416){return true;}
      if(is==417){return true;}
      if(is==448){return true;}
      if(is==449){return true;}
      if(is==501){return true;}
      if(is==507){return true;}
      if(is==508){return true;}
      if(is==509){return true;}
      if(is==512){return true;}
      if(is==669){return true;}
      if(is==670){return true;}
      if(is==671){return true;}
      if(is==683){return true;}
      if(is==684){return true;}
      if(is==685){return true;}
      if(is==709){return true;}
      if(is==710){return true;}
      if(is==724){return true;}
      if(is==725){return true;}
      if(is==762){return true;}
      if(is==822){return true;}
      if(is==900){return true;}
      if(is==901){return true;}
      if(is==953){return true;}
      if(is==973){return true;}
      if(is==1010){return true;}
      if(is==1011){return true;}
      if(is==1013){return true;}
      if(is==1020){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    else if(il==2){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==10){return true;}
      if(is==11){return true;}
      if(is==37){return true;}
      if(is==38){return true;}
      if(is==579){return true;}
      if(is==862){return true;}
      if(is==895){return true;}
      if(is==947){return true;}
      if(is==993){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    else if(il==3){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==11){return true;}
      if(is==65){return true;}
      if(is==66){return true;}
      if(is==67){return true;}
      if(is==68){return true;}
      if(is==69){return true;}
      if(is==276){return true;}
      if(is==277){return true;}
      if(is==287){return true;}
      if(is==288){return true;}
      if(is==289){return true;}
      if(is==290){return true;}
      if(is==291){return true;}
      if(is==292){return true;}
      if(is==297){return true;}
      if(is==298){return true;}
      if(is==299){return true;}
      if(is==300){return true;}
      if(is==301){return true;}
      if(is==302){return true;}
      if(is==303){return true;}
      if(is==304){return true;}
      if(is==305){return true;}
      if(is==306){return true;}
      if(is==307){return true;}
      if(is==308){return true;}
      if(is==309){return true;}
      if(is==310){return true;}
      if(is==337){return true;}
      if(is==338){return true;}
      if(is==347){return true;}
      if(is==348){return true;}
      if(is==349){return true;}
      if(is==350){return true;}
      if(is==351){return true;}
      if(is==352){return true;}
      if(is==353){return true;}
      if(is==354){return true;}
      if(is==355){return true;}
      if(is==356){return true;}
      if(is==357){return true;}
      if(is==358){return true;}
      if(is==359){return true;}
      if(is==360){return true;}
      if(is==361){return true;}
      if(is==362){return true;}
      if(is==363){return true;}
      if(is==364){return true;}
      if(is==365){return true;}
      if(is==366){return true;}
      if(is==367){return true;}
      if(is==368){return true;}
      if(is==369){return true;}
      if(is==370){return true;}
      if(is==371){return true;}
      if(is==372){return true;}
      if(is==373){return true;}
      if(is==374){return true;}
      if(is==375){return true;}
      if(is==376){return true;}
      if(is==377){return true;}
      if(is==386){return true;}
      if(is==387){return true;}
      if(is==503){return true;}
      if(is==504){return true;}
      if(is==511){return true;}
      if(is==512){return true;}
      if(is==554){return true;}
      if(is==555){return true;}
      if(is==600){return true;}
      if(is==601){return true;}
      if(is==606){return true;}
      if(is==607){return true;}
      if(is==608){return true;}
      if(is==609){return true;}
      if(is==610){return true;}
      if(is==611){return true;}
      if(is==612){return true;}
      if(is==613){return true;}
      if(is==621){return true;}
      if(is==622){return true;}
      if(is==743){return true;}
      if(is==744){return true;}
      if(is==782){return true;}
      if(is==845){return true;}
      if(is==846){return true;}
      if(is==853){return true;}
      if(is==980){return true;}
      if(is==1002){return true;}
      if(is==1017){return true;}
      if(is==1018){return true;}
      if(is==1019){return true;}
      if(is==1020){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
    else if(il==4){
      if(is==0){return true;}
      if(is==1){return true;}
      if(is==2){return true;}
      if(is==3){return true;}
      if(is==11){return true;}
      if(is==12){return true;}
      if(is==13){return true;}
      if(is==15){return true;}
      if(is==16){return true;}
      if(is==17){return true;}
      if(is==18){return true;}
      if(is==19){return true;}
      if(is==20){return true;}
      if(is==21){return true;}
      if(is==44){return true;}
      if(is==45){return true;}
      if(is==63){return true;}
      if(is==89){return true;}
      if(is==90){return true;}
      if(is==205){return true;}
      if(is==206){return true;}
      if(is==207){return true;}
      if(is==208){return true;}
      if(is==209){return true;}
      if(is==210){return true;}
      if(is==211){return true;}
      if(is==212){return true;}
      if(is==213){return true;}
      if(is==214){return true;}
      if(is==258){return true;}
      if(is==277){return true;}
      if(is==278){return true;}
      if(is==279){return true;}
      if(is==280){return true;}
      if(is==281){return true;}
      if(is==305){return true;}
      if(is==306){return true;}
      if(is==307){return true;}
      if(is==308){return true;}
      if(is==394){return true;}
      if(is==395){return true;}
      if(is==396){return true;}
      if(is==433){return true;}
      if(is==434){return true;}
      if(is==435){return true;}
      if(is==440){return true;}
      if(is==441){return true;}
      if(is==500){return true;}
      if(is==501){return true;}
      if(is==505){return true;}
      if(is==506){return true;}
      if(is==517){return true;}
      if(is==560){return true;}
      if(is==561){return true;}
      if(is==562){return true;}
      if(is==563){return true;}
      if(is==564){return true;}
      if(is==565){return true;}
      if(is==566){return true;}
      if(is==567){return true;}
      if(is==568){return true;}
      if(is==569){return true;}
      if(is==570){return true;}
      if(is==571){return true;}
      if(is==572){return true;}
      if(is==573){return true;}
      if(is==574){return true;}
      if(is==575){return true;}
      if(is==576){return true;}
      if(is==577){return true;}
      if(is==578){return true;}
      if(is==579){return true;}
      if(is==580){return true;}
      if(is==581){return true;}
      if(is==582){return true;}
      if(is==583){return true;}
      if(is==584){return true;}
      if(is==585){return true;}
      if(is==586){return true;}
      if(is==587){return true;}
      if(is==588){return true;}
      if(is==601){return true;}
      if(is==602){return true;}
      if(is==603){return true;}
      if(is==604){return true;}
      if(is==605){return true;}
      if(is==606){return true;}
      if(is==613){return true;}
      if(is==614){return true;}
      if(is==634){return true;}
      if(is==635){return true;}
      if(is==636){return true;}
      if(is==642){return true;}
      if(is==643){return true;}
      if(is==729){return true;}
      if(is==730){return true;}
      if(is==731){return true;}
      if(is==732){return true;}
      if(is==733){return true;}
      if(is==734){return true;}
      if(is==735){return true;}
      if(is==736){return true;}
      if(is==737){return true;}
      if(is==738){return true;}
      if(is==739){return true;}
      if(is==740){return true;}
      if(is==741){return true;}
      if(is==760){return true;}
      if(is==761){return true;}
      if(is==826){return true;}
      if(is==827){return true;}
      if(is==836){return true;}
      if(is==837){return true;}
      if(is==838){return true;}
      if(is==839){return true;}
      if(is==840){return true;}
      if(is==841){return true;}
      if(is==842){return true;}
      if(is==843){return true;}
      if(is==844){return true;}
      if(is==845){return true;}
      if(is==846){return true;}
      if(is==847){return true;}
      if(is==848){return true;}
      if(is==849){return true;}
      if(is==850){return true;}
      if(is==862){return true;}
      if(is==931){return true;}
      if(is==958){return true;}
      if(is==1020){return true;}
      if(is==1021){return true;}
      if(is==1022){return true;}
      if(is==1023){return true;}
    }
  }
  else if(ixy==1){
    if(il==0){
      if(is==44){return true;}
      if(is==131){return true;}
      if(is==172){return true;}
      if(is==173){return true;}
      if(is==174){return true;}
      if(is==175){return true;}
      if(is==224){return true;}
      if(is==255){return true;}
      if(is==291){return true;}
      if(is==292){return true;}
      if(is==342){return true;}
      if(is==378){return true;}
      if(is==381){return true;}
      if(is==402){return true;}
      if(is==489){return true;}
      if(is==496){return true;}
      if(is==497){return true;}
      if(is==524){return true;}
      if(is==534){return true;}
      if(is==562){return true;}
      if(is==587){return true;}
      if(is==701){return true;}
      if(is==703){return true;}
      if(is==705){return true;}
      if(is==732){return true;}
      if(is==839){return true;}
      if(is==841){return true;}
      if(is==867){return true;}
      if(is==869){return true;}
      if(is==964){return true;}
      if(is==976){return true;}
      if(is==985){return true;}
      if(is==994){return true;}
      if(is==1007){return true;}
      if(is==1009){return true;}
    }
    else if(il==1){
      if(is==0){return true;}
      if(is==44){return true;}
      if(is==80){return true;}
      if(is==181){return true;}
      if(is==193){return true;}
      if(is==258){return true;}
      if(is==276){return true;}
      if(is==334){return true;}
      if(is==452){return true;}
      if(is==461){return true;}
      if(is==462){return true;}
      if(is==466){return true;}
      if(is==467){return true;}
      if(is==484){return true;}
      if(is==506){return true;}
      if(is==508){return true;}
      if(is==509){return true;}
      if(is==510){return true;}
      if(is==511){return true;}
      if(is==512){return true;}
      if(is==542){return true;}
      if(is==580){return true;}
      if(is==587){return true;}
      if(is==588){return true;}
      if(is==598){return true;}
      if(is==599){return true;}
      if(is==600){return true;}
      if(is==606){return true;}
      if(is==607){return true;}
      if(is==652){return true;}
      if(is==659){return true;}
      if(is==664){return true;}
      if(is==665){return true;}
      if(is==666){return true;}
      if(is==678){return true;}
      if(is==679){return true;}
      if(is==727){return true;}
      if(is==729){return true;}
      if(is==741){return true;}
      if(is==761){return true;}
      if(is==782){return true;}
      if(is==837){return true;}
      if(is==852){return true;}
      if(is==871){return true;}
      if(is==877){return true;}
      if(is==895){return true;}
      if(is==958){return true;}
      if(is==959){return true;}
      if(is==960){return true;}
      if(is==961){return true;}
      if(is==962){return true;}
      if(is==963){return true;}
      if(is==964){return true;}
      if(is==965){return true;}
      if(is==966){return true;}
      if(is==967){return true;}
      if(is==968){return true;}
      if(is==969){return true;}
      if(is==971){return true;}
      if(is==984){return true;}
      if(is==986){return true;}
      if(is==989){return true;}
      if(is==997){return true;}
      if(is==998){return true;}
      if(is==1003){return true;}
      if(is==1013){return true;}
      if(is==1018){return true;}
      if(is==1023){return true;}
    }
    else if(il==2){
      if(is==464){return true;}
      if(is==655){return true;}
    }
    else if(il==3){
      if(is==12){return true;}
      if(is==13){return true;}
      if(is==14){return true;}
      if(is==15){return true;}
      if(is==16){return true;}
      if(is==17){return true;}
      if(is==25){return true;}
      if(is==26){return true;}
      if(is==355){return true;}
      if(is==430){return true;}
      if(is==431){return true;}
      if(is==449){return true;}
      if(is==450){return true;}
      if(is==459){return true;}
      if(is==460){return true;}
      if(is==466){return true;}
      if(is==467){return true;}
      if(is==468){return true;}
      if(is==491){return true;}
      if(is==493){return true;}
      if(is==496){return true;}
      if(is==497){return true;}
      if(is==507){return true;}
      if(is==509){return true;}
      if(is==511){return true;}
      if(is==522){return true;}
      if(is==573){return true;}
      if(is==626){return true;}
      if(is==653){return true;}
      if(is==654){return true;}
      if(is==662){return true;}
      if(is==679){return true;}
      if(is==765){return true;}
      if(is==776){return true;}
      if(is==813){return true;}
      if(is==814){return true;}
      if(is==815){return true;}
      if(is==816){return true;}
      if(is==817){return true;}
      if(is==818){return true;}
      if(is==819){return true;}
      if(is==820){return true;}
      if(is==821){return true;}
      if(is==822){return true;}
      if(is==823){return true;}
      if(is==824){return true;}
      if(is==843){return true;}
    }
    else if(il==4){
      if(is==15){return true;}
      if(is==27){return true;}
      if(is==61){return true;}
      if(is==62){return true;}
      if(is==108){return true;}
      if(is==109){return true;}
      if(is==110){return true;}
      if(is==111){return true;}
      if(is==112){return true;}
      if(is==113){return true;}
      if(is==114){return true;}
      if(is==115){return true;}
      if(is==142){return true;}
      if(is==158){return true;}
      if(is==159){return true;}
      if(is==211){return true;}
      if(is==212){return true;}
      if(is==246){return true;}
      if(is==251){return true;}
      if(is==406){return true;}
      if(is==469){return true;}
      if(is==509){return true;}
      if(is==510){return true;}
      if(is==511){return true;}
      if(is==512){return true;}
      if(is==549){return true;}
      if(is==553){return true;}
      if(is==633){return true;}
      if(is==657){return true;}
      if(is==759){return true;}
      if(is==897){return true;}
      if(is==898){return true;}
      if(is==899){return true;}
      if(is==900){return true;}
      if(is==964){return true;}
    }
  }

  return false;
}

#endif
