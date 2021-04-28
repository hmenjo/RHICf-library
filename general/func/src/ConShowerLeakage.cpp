#ifndef __CONFSHOWERLEAKAGE_CPP__
#define __CONFSHOWERLEAKAGE_CPP__

#include "ConShowerLeakage.h"
//----------------------------------------------------------------------
//
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ?? ???. 08: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------

#if !defined(__CINT__)
ClassImp(ConShowerLeakage);
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <math.h>
using namespace std;

#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TStyle.h>

int ConShowerLeakage::icall = 0;
const char* ConShowerLeakage::CONFSHOWERLEAKAGE_FORMAT="CONFSHOWERLEAKAGE";
const int   ConShowerLeakage::CONFSHOWERLEAKAGE_OK;
const int   ConShowerLeakage::CONFSHOWERLEAKAGE_ERROR;

ConShowerLeakage::ConShowerLeakage(){
	Initialize();
}

ConShowerLeakage::ConShowerLeakage(char* file,char option[]){
	Initialize();
	ReadROOTFile(file,option);
}

ConShowerLeakage::~ConShowerLeakage(){
	Initialize();
}

int ConShowerLeakage::Initialize(){
	strcpy(tablefile,"");
	strcpy(format,"");
	type   = 0;
	version = 0;

	char name[256];
	sprintf(name,"conslp_aram%d",icall);
	dir = new TDirectory(name,"");
	dir->cd();
	h2fac20 = new TH2F("h2fac20","",20*4,0.,20.,20*4,0.,20.);
	h2fac40 = new TH2F("h2fac40","",40*4,0.,40.,40*4,0.,40.);
	h2fac25 = new TH2F("h2fac25","",25*4,0.,25.,25*4,0.,25.);
	h2fac32 = new TH2F("h2fac32","",32*4,0.,32.,32*4,0.,32.);
	h2fac20_leakin = new TH2F("h2fac20_leakin","",20*4,0.,20.,20*4,0.,20.);
	h2fac40_leakin = new TH2F("h2fac40_leakin","",40*4,0.,40.,40*4,0.,40.);

	for(int il=0;il<16;il++){

		h2fac20_leakinll[il] = new TH2D(Form("h2fac20_leakinll_%d", il), "", 20, 0, 20, 20, 0, 20);
		h2fac40_leakinll[il] = new TH2D(Form("h2fac40_leakinll_%d", il), "", 40, 0, 40, 40, 0, 40);
	}

	h2fac25_leakin = new TH2F("h2fac25_leakin","",25*4,0.,25.,25*4,0.,25.);
	h2fac32_leakin = new TH2F("h2fac32_leakin","",32*4,0.,32.,32*4,0.,32.);
	h2param20_leakin = new TH2F("h2param20_leakin","",20/2,0.,20.,20/2,0.,20.);
	h2param40_leakin = new TH2F("h2param40_leakin","",40/2,0.,40.,40/2,0.,40.);
	h2param25_leakin = new TH2F("h2param25_leakin","",25/2,0.,25.,25/2,0.,25.);
	h2param32_leakin = new TH2F("h2param32_leakin","",32/2,0.,32.,32/2,0.,32.);
	gROOT->cd();
	icall++;
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::ReadROOTFile(char* file,char* option){
	//cout << "ReadROOTFile" << endl;
	gROOT->cd();
	TFile *f = new TFile(file);
	if( f==0 ){
		cerr << "[ConShowerLeakage::ReadROOTFile] Cannot Open "
			<< file << endl;
		return CONFSHOWERLEAKAGE_ERROR;
	}

	dir->cd();
	if(( strstr(option,"t20")!=0 || strstr(option,"All")!=0)&&
			f->GetListOfKeys()->FindObject("h2fac20") !=0) {
		SetH2map20((TH2F*)f->Get("h2fac20"));
	}
	if( ( strstr(option,"t40")!=0 || strstr(option,"All")!=0)&&
			f->GetListOfKeys()->FindObject("h2fac40") !=0) {
		SetH2map40((TH2F*)f->Get("h2fac40"));
	} 
	if( ( strstr(option,"t25")!=0 || strstr(option,"All")!=0)&&
			f->GetListOfKeys()->FindObject("h2fac25") !=0) {
		SetH2map25((TH2F*)f->Get("h2fac25"));
	}  
	if( ( strstr(option,"t32")!=0 || strstr(option,"All")!=0)&&
			f->GetListOfKeys()->FindObject("h2fac32") !=0) {
		SetH2map32((TH2F*)f->Get("h2fac32"));
	}  

	if(( strstr(option,"tin20")!=0 || strstr(option,"All")!=0) /*&& f->GetListOfKeys()->FindObject("h2fac20_leakin") !=0*/){

		//SetH2map20Leakin((TH2F*)f->Get("h2fac20_leakin"));

		for(int ilay=0; ilay<16; ++ilay){ 
	
			if(f->GetListOfKeys()->FindObject(Form("h2map_tg0_%02d",ilay)) != 0){

				//if(ilay==0) cout << "Get TS Leakage-in" << endl;
				SetH2map20Leakinll((TH2D*)f->Get(Form("h2map_tg0_%02d",ilay)), ilay);
			}
		}
	}
	if(( strstr(option,"tin40")!=0 || strstr(option,"All")!=0) /*&& f->GetListOfKeys()->FindObject("h2fac40_leakin") !=0*/){

		//SetH2map40Leakin((TH2F*)f->Get("h2fac40_leakin"));

		for(int ilay=0; ilay<16; ++ilay){ 

			if(f->GetListOfKeys()->FindObject(Form("h2map_tg1_%02d",ilay)) != 0){

				//if(ilay==0) cout << "Get TL Leakage-in" << endl;
				SetH2map40Leakinll((TH2D*)f->Get(Form("h2map_tg1_%02d",ilay)), ilay);
			}
		}
	}
	if(( strstr(option,"tin25")!=0 || strstr(option,"All")!=0)&&
			f->GetListOfKeys()->FindObject("h2fac25_leakin") !=0) {
		SetH2map25Leakin((TH2F*)f->Get("h2fac25_leakin"));
	}
	if(( strstr(option,"tin32")!=0 || strstr(option,"All")!=0)&&
			f->GetListOfKeys()->FindObject("h2fac32_leakin") !=0) {
		SetH2map32Leakin((TH2F*)f->Get("h2fac32_leakin"));
	}

	if(( strstr(option,"inp20")!=0 || strstr(option,"All")!=0)&&
			f->GetListOfKeys()->FindObject("h2param20_leakin") !=0) {
		SetH2param20Leakin((TH2F*)f->Get("h2param20_leakin"));
	}
	if(( strstr(option,"inp40")!=0 || strstr(option,"All")!=0)&&
			f->GetListOfKeys()->FindObject("h2param40_leakin") !=0) {
		SetH2param40Leakin((TH2F*)f->Get("h2param40_leakin"));
	}
	if(( strstr(option,"inp25")!=0 || strstr(option,"All")!=0)&&
			f->GetListOfKeys()->FindObject("h2param25_leakin") !=0) {
		SetH2param25Leakin((TH2F*)f->Get("h2param25_leakin"));
	}
	if(( strstr(option,"inp32")!=0 || strstr(option,"All")!=0)&&
			f->GetListOfKeys()->FindObject("h2param32_leakin") !=0) {
		SetH2param32Leakin((TH2F*)f->Get("h2param32_leakin"));
	}

	f->Close();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::WriteROOTFile(char* file,char option[]){
	gROOT->cd();
	TFile *f = new TFile(file,"UPDATE");
	if(strstr(option,"t20")!=NULL || strstr(option,"All")!=NULL){
		h2fac20->Write("",TObject::kOverwrite);
	}
	if(strstr(option,"t40")!=NULL || strstr(option,"All")!=NULL){
		h2fac40->Write("",TObject::kOverwrite);
	}
	if(strstr(option,"t25")!=NULL || strstr(option,"All")!=NULL){
		h2fac25->Write("",TObject::kOverwrite);
	} 
	if(strstr(option,"t32")!=NULL || strstr(option,"All")!=NULL){
		h2fac32->Write("",TObject::kOverwrite);
	}

	if(strstr(option,"tin20")!=NULL || strstr(option,"All")!=NULL){
		h2fac20_leakin->Write("",TObject::kOverwrite);
	}
	if(strstr(option,"tin40")!=NULL || strstr(option,"All")!=NULL){
		h2fac40_leakin->Write("",TObject::kOverwrite);
	}
	if(strstr(option,"tin25")!=NULL || strstr(option,"All")!=NULL){
		h2fac25_leakin->Write("",TObject::kOverwrite);
	} 
	if(strstr(option,"tin32")!=NULL || strstr(option,"All")!=NULL){
		h2fac32_leakin->Write("",TObject::kOverwrite);
	}  

	if(strstr(option,"inp20")!=NULL || strstr(option,"All")!=NULL){
		h2param20_leakin->Write("",TObject::kOverwrite);
	}
	if(strstr(option,"inp40")!=NULL || strstr(option,"All")!=NULL){
		h2param40_leakin->Write("",TObject::kOverwrite);
	}
	if(strstr(option,"inp25")!=NULL || strstr(option,"All")!=NULL){
		h2param25_leakin->Write("",TObject::kOverwrite);
	} 
	if(strstr(option,"inp32")!=NULL || strstr(option,"All")!=NULL){
		h2param32_leakin->Write("",TObject::kOverwrite);
	}    


	f->Close();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2map20(TH2F* h2){
	dir->cd();
	if(h2fac20 !=NULL){delete h2fac20;}
	h2fac20 = (TH2F*)h2->Clone("h2fac20");  
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2map40(TH2F* h2){
	dir->cd();
	if(h2fac40 !=NULL){delete h2fac40;}
	h2fac40 = (TH2F*)h2->Clone("h2fac40");
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2map25(TH2F* h2){
	dir->cd();
	if(h2fac25 !=NULL){delete h2fac25;}
	h2fac25 = (TH2F*)h2->Clone("h2fac25");
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2map32(TH2F* h2){
	dir->cd();
	if(h2fac32 !=NULL){delete h2fac32;}
	h2fac32 = (TH2F*)h2->Clone("h2fac32");
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2map20Leakin(TH2F* h2){
	dir->cd();
	if(h2fac20_leakin !=NULL){delete h2fac20_leakin;}
	h2fac20_leakin = (TH2F*)h2->Clone("h2fac20_leakin");  
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2map40Leakin(TH2F* h2){
	dir->cd();
	if(h2fac40_leakin !=NULL){delete h2fac40_leakin;}
	h2fac40_leakin = (TH2F*)h2->Clone("h2fac40_leakin");  
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2map20Leakinll(TH2D* h2, int il){
        dir->cd();
        if(h2fac20_leakinll[il] !=NULL){delete h2fac20_leakinll[il];}
        h2fac20_leakinll[il] = (TH2D*)h2->Clone(Form("h2map_tg0_%02d",il));
	//printf("TS il:%d, %f\n", il, h2fac20_leakinll[il]->Interpolate(5,5));
        gROOT->cd();
        return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2map40Leakinll(TH2D* h2, int il){
        dir->cd();
        if(h2fac40_leakinll[il] !=NULL){delete h2fac40_leakinll[il];}
        h2fac40_leakinll[il] = (TH2D*)h2->Clone(Form("h2map_tg1_%02d",il));
	//printf("TL il:%d, %f\n", il, h2fac40_leakinll[il]->Interpolate(5,5));
        gROOT->cd();
        return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2map25Leakin(TH2F* h2){
	dir->cd();
	if(h2fac25_leakin !=NULL){delete h2fac25_leakin;}
	h2fac25_leakin = (TH2F*)h2->Clone("h2fac25_leakin");  
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2map32Leakin(TH2F* h2){
	dir->cd();
	if(h2fac32_leakin !=NULL){delete h2fac32_leakin;}
	h2fac32_leakin = (TH2F*)h2->Clone("h2fac32_leakin");  
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2param20Leakin(TH2F* h2){
	dir->cd();
	if(h2param20_leakin !=NULL){delete h2param20_leakin;}
	h2param20_leakin = (TH2F*)h2->Clone("h2param20_leakin");  
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2param40Leakin(TH2F* h2){
	dir->cd();
	if(h2param40_leakin !=NULL){delete h2param40_leakin;}
	h2param40_leakin = (TH2F*)h2->Clone("h2param40_leakin");  
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2param25Leakin(TH2F* h2){
	dir->cd();
	if(h2param25_leakin !=NULL){delete h2param25_leakin;}
	h2param25_leakin = (TH2F*)h2->Clone("h2param25_leakin");  
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::SetH2param32Leakin(TH2F* h2){
	dir->cd();
	if(h2param32_leakin !=NULL){delete h2param32_leakin;}
	h2param32_leakin = (TH2F*)h2->Clone("h2param32_leakin");  
	gROOT->cd();
	return CONFSHOWERLEAKAGE_OK;
}

double ConShowerLeakage::GetFactor(int id,int it,double x,double y,char option[]){
	int ix,iy;
	double tmp;
	if(strstr(option,"p")!=NULL){
		if(id==1 && it==0){
			ix = h2param20_leakin->GetXaxis()->FindBin(x);
			iy = h2param20_leakin->GetYaxis()->FindBin(y); 
			tmp = h2param20_leakin->GetBinContent(ix,iy);
			if(tmp>0.0001){return tmp;}
		}
		if(id==1 && it==1){
			ix = h2param40_leakin->GetXaxis()->FindBin(x);
			iy = h2param40_leakin->GetYaxis()->FindBin(y); 
			tmp = h2param40_leakin->GetBinContent(ix,iy);
			if(tmp>0.0001){return tmp;}
		}
		if(id==2 && it==0){
			ix = h2param25_leakin->GetXaxis()->FindBin(x);
			iy = h2param25_leakin->GetYaxis()->FindBin(y); 
			tmp = h2param25_leakin->GetBinContent(ix,iy);
			if(tmp>0.0001){return tmp;}
		}
		if(id==2 && it==1){
			ix = h2param32_leakin->GetXaxis()->FindBin(x);
			iy = h2param32_leakin->GetYaxis()->FindBin(y); 
			tmp = h2param32_leakin->GetBinContent(ix,iy);
			if(tmp>0.0001){return tmp;}
		}
		return 5.;
	}
	else if(strstr(option,"in")!=NULL){
		if(id==1 && it==0){
			ix = h2fac20_leakin->GetXaxis()->FindBin(x);
			iy = h2fac20_leakin->GetYaxis()->FindBin(y); 
			tmp = h2fac20_leakin->GetBinContent(ix,iy);
			if(tmp>0.000001){return tmp;}
		}
		if(id==1 && it==1){
			ix = h2fac40_leakin->GetXaxis()->FindBin(x);
			iy = h2fac40_leakin->GetYaxis()->FindBin(y); 
			tmp = h2fac40_leakin->GetBinContent(ix,iy);
			if(tmp>0.000001){return tmp;}
		}
		if(id==2 && it==0){
			ix = h2fac25_leakin->GetXaxis()->FindBin(x);
			iy = h2fac25_leakin->GetYaxis()->FindBin(y); 
			tmp = h2fac25_leakin->GetBinContent(ix,iy);
			if(tmp>0.000001){return tmp;}
		}
		if(id==2 && it==1){
			ix = h2fac32_leakin->GetXaxis()->FindBin(x);
			iy = h2fac32_leakin->GetYaxis()->FindBin(y); 
			tmp = h2fac32_leakin->GetBinContent(ix,iy);
			if(tmp>0.000001){return tmp;}
		}
		return 1.;
	}
	else {
		if(id==1 && it==0){
			ix = h2fac20->GetXaxis()->FindBin(x);
			iy = h2fac20->GetYaxis()->FindBin(y); 
			tmp = h2fac20->GetBinContent(ix,iy);
			if(tmp>0.0001){return tmp;}
		}
		if(id==1 && it==1){
			ix = h2fac40->GetXaxis()->FindBin(x);
			iy = h2fac40->GetYaxis()->FindBin(y); 
			tmp = h2fac40->GetBinContent(ix,iy);
			if(tmp>0.0001){return tmp;}
		}
		if(id==2 && it==0){
			ix = h2fac25->GetXaxis()->FindBin(x);
			iy = h2fac25->GetYaxis()->FindBin(y); 
			tmp = h2fac25->GetBinContent(ix,iy);
			if(tmp>0.0001){return tmp;}
		}
		if(id==2 && it==1){
			ix = h2fac32->GetXaxis()->FindBin(x);
			iy = h2fac32->GetYaxis()->FindBin(y); 
			tmp = h2fac32->GetBinContent(ix,iy);
			if(tmp>0.0001){return tmp;}
		}
		return 1.;
	} 
}

double ConShowerLeakage::GetLeakFactor(int id,int it,double x,double y){
	return GetFactor(id,it,x,y,"");
}

double ConShowerLeakage::GetLeakinFactor(int id,int it,double x,double y){
	return GetFactor(id,it,x,y,"in");
}

double ConShowerLeakage::GetLeakinFactorll(int it, int il, double x, double y){

	//cout << "GetLeakinFactorll" << endl;
	//cout << h2fac20_leakinll[5] -> Interpolate(5, 5) << endl;
	//cout << h2fac20_leakinll[5] -> Interpolate(5, 5) << endl;
	//printf("it:%d, (%0.1f, %0.1f)\n", it, x, y);

	if(it==0) return h2fac20_leakinll[il] -> Interpolate(x, y);
	if(it==1) return h2fac40_leakinll[il] -> Interpolate(x, y);
}

double ConShowerLeakage::GetLeakinParam(int id,int it,double x,double y){
	return GetFactor(id,it,x,y,"p");
}

int ConShowerLeakage::Draw(int id,int itower,char option[]){
	TH2F* h2;
	if(strstr(option,"p")!=NULL){
		if(id==1 && itower==0) { h2 = h2param20_leakin;}
		else if(id==1 && itower==1) {h2 = h2param40_leakin;}
		else if(id==2 && itower==0) {h2 = h2param25_leakin;}
		else if(id==2 && itower==1) {h2 = h2param32_leakin;} 
		else{ return CONFSHOWERLEAKAGE_ERROR;}
	}
	else if(strstr(option,"in")!=NULL){
		if(id==1 && itower==0) { h2 = h2fac20_leakin;}
		else if(id==1 && itower==1) {h2 = h2fac40_leakin;}
		else if(id==2 && itower==0) {h2 = h2fac25_leakin;}
		else if(id==2 && itower==1) {h2 = h2fac32_leakin;} 
		else{ return CONFSHOWERLEAKAGE_ERROR;}
	}
	else{
		if(id==1 && itower==0) { h2 = h2fac20;}
		else if(id==1 && itower==1) {h2 = h2fac40;}
		else if(id==2 && itower==0) {h2 = h2fac25;}
		else if(id==2 && itower==1) {h2 = h2fac32;} 
		else{ return CONFSHOWERLEAKAGE_ERROR;}
	}

	h2->SetXTitle("X [mm]");
	h2->SetYTitle("Y [mm]");  

	if(strchr(option,'Q')==NULL){
		dir->cd();
		TCanvas *c = new TCanvas("sldraw","",500,500);
		c->SetTopMargin(0.10); 
		c->SetBottomMargin(0.15);
		c->SetRightMargin(0.15);
		c->SetLeftMargin(0.15);  
		h2->Draw("COLZ");
		c->Update();
	}
	return CONFSHOWERLEAKAGE_OK;
}

int ConShowerLeakage::DrawAll(int id){
	dir->cd();
	TCanvas *c = new TCanvas("sldraw_all","ShowerLeakage Functions",800,500);
	c->Divide(3,2);
	for(int itower=0;itower<2;itower++){
		for(int type=0;type<3;type++){
			TH2F *h2; 
			if(type==0){
				if(id==1 && itower==0) { h2 = h2fac20;}
				else if(id==1 && itower==1) {h2 = h2fac40;}
				else if(id==2 && itower==0) {h2 = h2fac25;}
				else if(id==2 && itower==1) {h2 = h2fac32;} 
			}
			else if(type==1){
				if(id==1 && itower==0) { h2 = h2fac20_leakin;}
				else if(id==1 && itower==1) {h2 = h2fac40_leakin;}
				else if(id==2 && itower==0) {h2 = h2fac25_leakin;}
				else if(id==2 && itower==1) {h2 = h2fac32_leakin;} 
			}  
			else if(type==2){
				if(id==1 && itower==0) { h2 = h2param20_leakin;}
				else if(id==1 && itower==1) {h2 = h2param40_leakin;}
				else if(id==2 && itower==0) {h2 = h2param25_leakin;}
				else if(id==2 && itower==1) {h2 = h2param32_leakin;} 
			}

			if(h2==NULL) continue;

			c->cd(itower*3+type+1);
			gStyle->SetTitleX(0.5);
			gPad->SetTopMargin(0.15); 
			gPad->SetBottomMargin(0.15);
			gPad->SetRightMargin(0.15);
			gPad->SetLeftMargin(0.15);  

			if(type==0){
				h2->SetTitle(Form("%s:Leakage-out",(itower==0?"25mm":"32mm")));
			} 
			if(type==1){
				h2->SetTitle(Form("%s:Leakage-in Scale",(itower==0?"25mm":"32mm")));
			}    
			if(type==2){
				h2->SetTitle(Form("%s:Leakage-in offset",(itower==0?"25mm":"32mm")));
			}    
			h2->SetXTitle("X [mm]");
			h2->SetYTitle("Y [mm]");  
			h2->Draw("COLZ");
		}
	}
	c->Update();
	return CONFSHOWERLEAKAGE_OK;
}


int ConShowerLeakage::it2size(int it){
	if(it==0) return 20;
	if(it==1) return 40;
	if(it==2) return 25;
	if(it==3) return 32;
	return 0;
}

#endif
