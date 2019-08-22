#ifndef __LHCFEVENT_H__
#define __LHCFEVENT_H__

#include "globaldef.h"
#include <TNamed.h>
#include <TObjArray.h>
#include "A1Raw.h"
#include "A1Cal1.h"
#include "A1Cal2.h"
#include "A1Phys.h"
#include "A1Info.h"
#include "A1Scl.h"
#include "A2Raw.h"
#include "A2Cal1.h"
#include "A2Cal2.h"
#include "A2Cal2M.h"
#include "A2Phys.h"
#include "A2Info.h"
#include "A2Scl.h"
#include "RawL1T.h"
#include "SclL1T.h"
#include "GParam.h"
#include "GParamD64.h"
#include "SPSAdamo.h"
//#include "RHICfCollection.h"
//#include "TLHCFSDATA.h"
#include "A1Raw_pp2015.h"
#include "A2Raw_pp2015.h"
#include "A1Scl_pp2015.h"
#include "A2Scl_pp2015.h"
#include "A2Raw_pPb2013.h"
#include "A2Raw_pPb2016.h"
#include "RHICfRaw_Op2017.h"

//______________________________________________________________________________
// Hello !!

class LHCfEvent : public TNamed {
	public:
		int            run;         //  Run Number
		int            gnumber;     //  Global Event Number 
		int            a1number;    //  Arm#1  Event Number
		int            a2number;    //  Arm#2  Event Number
		unsigned int   a1flag[2];   //  Arm#1  Event Flag [0]:GPI0[0] [1]:GPI1[0]
		unsigned int   a2flag[2];   //  Arm#1  Event Flag [0]:GPI0[0] [1]:GPI1[0]
		int            ifile;       //  File Identification Number
		int            tnumber;     //  Event Number in the file
		unsigned int   tag;         //  Tags for the event type  
		int            tmp;         //  Temporal Number, each user can use freely
		TObjArray      objarray;    //  Data Stock in the Event

	public:
		LHCfEvent(){Initialize();}
		LHCfEvent(const char* name, const char *title) : TNamed(name,title){Initialize();}
		~LHCfEvent(){Delete();}

		void           Initialize();
		void           Delete();

		int            GetRun(){return run;}
		int            GetGNumber(){return gnumber;}
		int            GetA1Number(){return a1number;}
		int            GetA2Number(){return a2number;}
		unsigned int*  GetA1Flag(){return a1flag;}
		unsigned int   GetA1Flag(int i){return a1flag[i];}
		unsigned int*  GetA2Flag(){return a2flag;}
		unsigned int   GetA2Flag(int i){return a2flag[i];}  
		int            GetIFile(){return ifile;}
		int            GetTNumber(){return tnumber;}
		unsigned int   GetTag(){return tag;}
		int            GetTmp(){return tmp;}
		TObjArray*     GetObjAarray(){return &objarray;}
		void           SetTmp(int  n){tmp=n;}

		void        Add(TObject* obj){objarray.Add(obj);}

		TObject*    FindObject(const char *name){return objarray.FindObject(name);}
		TObject*    GetObject(const char *name) {return FindObject(name);}
		TObject*    Get(const char *name)       {return FindObject(name);}
		int         Check(const char *name)     {return (FindObject(name)==0) ? 0 : 1;}
		A1Raw*      GetA1Raw(const char *name="a1raw")  {return (A1Raw*)FindObject(name);}
		A1Cal1*     GetA1Cal1(const char *name="a1cal1"){return (A1Cal1*)FindObject(name);}
		A1Cal2*     GetA1Cal2(const char *name="a1cal2"){return (A1Cal2*)FindObject(name);}
		A1Phys*     GetA1Phys(const char *name="a1phys"){return (A1Phys*)FindObject(name);}
		A1Info*     GetA1Info(const char *name="a1info"){return (A1Info*)FindObject(name);}
		A1Scl*      GetA1Scl(const char *name="a1scl")  {return (A1Scl*)FindObject(name);}
		A2Raw*      GetA2Raw(const char *name="a2raw")  {return (A2Raw*)FindObject(name);}
		A2Cal1*     GetA2Cal1(const char *name="a2cal1"){return (A2Cal1*)FindObject(name);}
		A2Cal2*     GetA2Cal2(const char *name="a2cal2"){return (A2Cal2*)FindObject(name);}
		A2Phys*     GetA2Phys(const char *name="a2phys"){return (A2Phys*)FindObject(name);}
		A2Info*     GetA2Info(const char *name="a2info"){return (A2Info*)FindObject(name);}
		A2Scl*      GetA2Scl(const char *name="a2scl")  {return (A2Scl*)FindObject(name);}
		//RHICfCollection* GetRHICfCollection(const char* name = "rhicfcol") {return (RHICfCollection*)FindObject(name);}
		//TLHCFSDATA* GetTLHCFSDATA(const char *name){return (TLHCFSDATA*)FindObject(name);}
		// For Operation 2015
		A1Raw_pp2015* GetA1Raw_pp2015(const char *name="a1raw"){return (A1Raw_pp2015*)FindObject(name);}
		A2Raw_pp2015* GetA2Raw_pp2015(const char *name="a2raw"){return (A2Raw_pp2015*)FindObject(name);}  
		A1Scl_pp2015* GetA1Scl_pp2015(const char *name="a1scl"){return (A1Scl_pp2015*)FindObject(name);}
		A2Scl_pp2015* GetA2Scl_pp2015(const char *name="a2scl"){return (A2Scl_pp2015*)FindObject(name);}

		void        Clear(){HeaderClear();ObjClear();}
		void        HeaderClear();
		void        ObjClear(){objarray.Clear();}   // Remove all objects from the objarray.  
		// Does not delete the objects
		void        ObjDelete(){objarray.Delete();} // ObjClear + Delete all objectes

		void        HeaderCopy(LHCfEvent* d);       // Copy header informations from d to this.
		int         CheckTag(unsigned int mask=0xFFFFFFFF){return (tag&mask) ? 1 : 0;}
		int         CheckA1Trg(){return CheckTag(0x000001);}
		int         CheckA1Scl(){return CheckTag(0x000010);}
		int         CheckA2Trg(){return CheckTag(0x000100);}
		int         CheckA2Scl(){return CheckTag(0x001000);}
		int         CheckSC()   {return CheckTag(0x010000);}
		int         CheckA1Sim(){return CheckTag(0x10000000);}
		int         CheckA2Sim(){return CheckTag(0x20000000);}

		int         CheckA1Flag(int i=0,unsigned int mask=0xFFFF){return (a1flag[i]&mask) ? 1 : 0;}
		int         CheckA2Flag(int i=0,unsigned int mask=0xFFFF){return (a2flag[i]&mask) ? 1 : 0;}
		int         IsA1BeamFlag()  {return CheckA1Flag(0,0x1000);}
		int         IsA1PedeFlag()  {return CheckA1Flag(0,0x2000);}
		int         IsA1LaserFlag() {return CheckA1Flag(0,0x4000);}
		int         IsA1EnableFlag(){return CheckA1Flag(0,0x8000);}
		int         IsA1BTPX1Flag() {return CheckA1Flag(0,0x0001);}
		int         IsA1BTPX2Flag() {return CheckA2Flag(0,0x0002);}
		int         IsA1L2TAFlag()  {return CheckA1Flag(0,0x0010);}
		int         IsA1L2TPFlag()  {return CheckA1Flag(0,0x0020);} 
		int         IsA1L2TEXTFlag(){return CheckA1Flag(0,0x0040);}
		int         IsA1STRGFlag()  {return CheckA1Flag(0,0x0400);}
		int         IsA1LTRGFlag()  {return CheckA1Flag(0,0x0800);}
		int         IsA1L2TASPFlag(){return CheckA1Flag(0,0x0080);}
		int         IsA1L2TAMBFlag(){return CheckA1Flag(0,0x0200);}
		int         IsA2BeamFlag()  {return CheckA2Flag(0,0x1000);}
		int         IsA2PedeFlag()  {return CheckA2Flag(0,0x2000);}
		int         IsA2LaserFlag() {return CheckA2Flag(0,0x4000);}
		int         IsA2EnableFlag(){return CheckA2Flag(0,0x8000);}
		int         IsA2BTPX1Flag() {return CheckA2Flag(0,0x0001);}
		int         IsA2BTPX2Flag() {return CheckA2Flag(0,0x0002);}
		int         IsA2L2TAFlag()  {return CheckA2Flag(0,0x0010);}
		int         IsA2L2TPFlag()  {return CheckA2Flag(0,0x0020);} 
		int         IsA2L2TEXTFlag(){return CheckA2Flag(0,0x0040);}
		int         IsA2STRGFlag()  {return CheckA2Flag(0,0x0400);}
		int         IsA2LTRGFlag()  {return CheckA2Flag(0,0x0800);} 
		int         IsA2L2TASPFlag(){return CheckA2Flag(0,0x0080);}
		int         IsA2L2TAMBFlag(){return CheckA2Flag(0,0x0200);}

		int         EventTime();

		void        Show();
		void        Print(){Show();}  // Alias of Show();

		ClassDef(LHCfEvent,1)    // Data store for LHCf one event
};

#endif
