#ifndef __CONFSHOWERLEAKAGE__
#define __CONFSHOWERLEAKAGE__

//-----------------------------------------------------------------
//                          ConShowerLeakage 
//-----------------------------------------------------------------

#include <TObject.h>
#include <TDirectory.h>
#include <TH2F.h>
#include <TH2D.h>

class ConShowerLeakage{
	public:
		char       tablefile[256];
		char       format[256];
		int        type;
		int        version;

		TDirectory* dir;
		TH2F*       h2fac20;
		TH2F*       h2fac40;
		TH2F*       h2fac25;  
		TH2F*       h2fac32;
		TH2F*       h2fac20_leakin;
		TH2F*       h2fac40_leakin;
		TH2D*       h2fac20_leakinll[16];
		TH2D*       h2fac40_leakinll[16];
		TH2F*       h2fac25_leakin;  
		TH2F*       h2fac32_leakin;
		TH2F*       h2param20_leakin;
		TH2F*       h2param40_leakin;
		TH2F*       h2param25_leakin;
		TH2F*       h2param32_leakin;

	public:
		ConShowerLeakage();
		ConShowerLeakage(char* file,char option[]="All");
		virtual ~ConShowerLeakage();  

		int    Initialize();
		int    ReadROOTFile(char* file,char option[]="All");
		int    WriteROOTFile(char* file,char option[]="All");

		TH2F*  GetH2map20(){return h2fac20;}
		TH2F*  GetH2map40(){return h2fac40;}  
		TH2F*  GetH2map25(){return h2fac25;}
		TH2F*  GetH2map32(){return h2fac32;}
		TH2F*  GetH2map20Leakin(){return h2fac20_leakin;}
		TH2F*  GetH2map40Leakin(){return h2fac40_leakin;} 
		TH2F*  GetH2map25Leakin(){return h2fac25_leakin;} 
		TH2F*  GetH2map32Leakin(){return h2fac32_leakin;}  
		TH2F*  GetH2param20Leakin(){return h2param20_leakin;}
		TH2F*  GetH2param40Leakin(){return h2param40_leakin;}
		TH2F*  GetH2param25Leakin(){return h2param25_leakin;}
		TH2F*  GetH2param32Leakin(){return h2param32_leakin;} 
		int    SetH2map20(TH2F* h2);
		int    SetH2map40(TH2F* h2);  
		int    SetH2map25(TH2F* h2);
		int    SetH2map32(TH2F* h2); 
		int    SetH2map20Leakin(TH2F* h2);
		int    SetH2map40Leakin(TH2F* h2);
		int    SetH2map20Leakinll(TH2D* h2, int il);
		int    SetH2map40Leakinll(TH2D* h2, int il); 
		int    SetH2map25Leakin(TH2F* h2);
		int    SetH2map32Leakin(TH2F* h2);  
		int    SetH2param20Leakin(TH2F* h2);
		int    SetH2param40Leakin(TH2F* h2);  
		int    SetH2param25Leakin(TH2F* h2);
		int    SetH2param32Leakin(TH2F* h2);  
		double GetFactor(int id,int it,double x,double y,char option[]="");
		double GetLeakFactor(int id,int it,double x,double y);
		double GetLeakinFactor(int id,int it,double x,double y);
		double GetLeakinFactorll(int it, int il, double x, double y);
		double GetLeakinParam(int id,int it,double x,double y); 
		int    Draw(int id,int it,char option[]=""); 
		int    DrawAll(int id);

	public:
		static const char *CONFSHOWERLEAKAGE_FORMAT; 
		static const int   CONFSHOWERLEAKAGE_OK = 0;    
		static const int   CONFSHOWERLEAKAGE_ERROR =-1;

	protected:
		static int icall;    
		int    it2size(int it);

		ClassDef(ConShowerLeakage,1);   // Control the table for shower leakage functions.
};


#endif
