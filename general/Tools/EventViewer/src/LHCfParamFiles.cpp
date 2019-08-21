#ifndef __LHCFPARAMFILES_CPP__
#define __LHCFPARAMFILES_CPP__

#include "LHCfParamFiles.h"

LHCfParamFiles *gLHCfParamFiles = new LHCfParamFiles();

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
using namespace std;

LHCfParamFiles::LHCfParamFiles(){
  Initialize();
}

LHCfParamFiles::LHCfParamFiles(char *filename){
  Read(filename);
}

void LHCfParamFiles::Initialize(){
  
  strcpy(file_a1scifipostable,      "tables/scifi_pos_table_080408.dat");
  strcpy(file_a1adcrange,           "tables/adcrange_001_080307.dat");
  strcpy(file_a1particledefine,     "tables/pdef_sps07_arm1_080828.out");
  strcpy(file_a1scifiparticledefine,"tables/pardef_scifi_102_071019.txt");
  strcpy(file_a1fcparticledefine,   "tables/pdef_sps07_arm1_080828.out");
  strcpy(file_a1pmtgaintable,       "tables/GainsheetforCERN060812_1609.txt");
  strcpy(file_a1scifigaintable,     "tables/scifigaintable_081103.out");
  strcpy(file_a1fcgaintable,        "tables/fcgaintable_dummy.txt");
  strcpy(file_a1hvtable,            "config/hvtable_arm1_ALL600_SHV600.txt");
  //  strcpy(file_a1scificrosstalkx,    "tables/CROSSTALK_X_offset.dat");
  //  strcpy(file_a1scificrosstalky,    "tables/CROSSTALK_Y_offset.dat");
  strcpy(file_a1scificrosstalkx,    "tables/20141215_XtalkMatrixTemplate.root");
  strcpy(file_a1scificrosstalky,    "tables/20141215_XtalkMatrixTemplate.root");
  strcpy(file_a2adcrange,           "tables/adcrange_001_080307.dat");
  strcpy(file_a2particledefine,     "tables/pdef_sps07_arm2_081003.out");
  strcpy(file_a2siparticledefine,   "-"); 
  strcpy(file_a2fcparticledefine,   "tables/pdef_sps07_arm2_081003.out");
  strcpy(file_a2pmtgaintable,       "tables/GainsheetforCERN060812_1609.txt");
  strcpy(file_a2sigaintable,        "-");
  strcpy(file_a2fcgaintable,        "tables/fcgaintable_dummy.txt"); 
  strcpy(file_a2hvtable,            "config/hvtable_arm2_ALL600.txt");

#ifdef EVENTVIEWDIR
  // For Event Viewer ---------------------------------------
  char filename[256];
  sprintf(filename,"%s/.eventview/paramfiles.dat",EVENTVIEWDIR);
  strcpy(paramfile,filename);
  if(Read(filename,0)!=0){
    // Default Files 
    SetToDefault_Op2015();
  } 
#endif
  
  return ;
}

int LHCfParamFiles::Read(char *filename,int op){
  ifstream fin(filename);
  if(!fin){
    if(op!=0){
      cerr << "[LHCfParamFiles::Read] "
	   << "Cannot open " << filename << endl;
    }
    return -1;
  }
  
  string ss;
  istringstream sin;
  char tmp[256];
  while(getline(fin,ss)){
    // Skip to read comment lines
    if(ss[0]=='#'){continue;}
    sin.clear();
    sin.str(ss);
    sin >> tmp;
    if(ss.find("ARM1_SCIFIPOSTABLE")!=string::npos)      {sin >> file_a1scifipostable;}
    if(ss.find("ARM1_ADCRANGE")!=string::npos)           {sin >> file_a1adcrange;}
    if(ss.find("ARM1_PARTICLEDEFINE")!=string::npos)     {sin >> file_a1particledefine;}
    if(ss.find("ARM1_SCIFIPARTICLEDEFINE")!=string::npos){sin >> file_a1scifiparticledefine;}
    if(ss.find("ARM1_FCPARTICLEDEFINE")!=string::npos)   {sin >> file_a1fcparticledefine;}
    if(ss.find("ARM1_PMTGAINTABLE")!=string::npos)       {sin >> file_a1pmtgaintable;}
    if(ss.find("ARM1_SCIFIGAINTABLE")!=string::npos)     {sin >> file_a1scifigaintable;}
    if(ss.find("ARM1_FCGAINTABLE")!=string::npos)        {sin >> file_a1fcgaintable;}
    if(ss.find("ARM1_HVTABL")!=string::npos)             {sin >> file_a1hvtable;}
    if(ss.find("ARM1_SCIFICROSSTALKX")!=string::npos)    {sin >> file_a1scificrosstalkx;}
    if(ss.find("ARM1_SCIFICROSSTALKY")!=string::npos)    {sin >> file_a1scificrosstalky;}
    if(ss.find("ARM2_ADCRANG")!=string::npos)            {sin >> file_a2adcrange;}
    if(ss.find("ARM2_PARTICLEDEFIN")!=string::npos)      {sin >> file_a2particledefine;}
    if(ss.find("ARM2_SIPARTICLEDEFIN")!=string::npos)    {sin >> file_a2siparticledefine;}
    if(ss.find("ARM2_FCPARTICLEDEFIN")!=string::npos)    {sin >> file_a2fcparticledefine;}
    if(ss.find("ARM2_PMTGAINTABLE")!=string::npos)       {sin >> file_a2pmtgaintable;}
    if(ss.find("ARM2_SIGAINTABL")!=string::npos)         {sin >> file_a2sigaintable;}
    if(ss.find("ARM2_FCGAINTABLE")!=string::npos)        {sin >> file_a2fcgaintable;}
    if(ss.find("ARM2_HVTABLE")!=string::npos)            {sin >> file_a2hvtable;}
  }
  
  return 0;
}

int LHCfParamFiles::Write(char *file){
  if(strcmp(file,"")==0){file = paramfile;}

  ofstream fout(file);
  if(!fout){return -1;}
  
  fout << "LHCFPARAMFILES" << endl << endl; 
  fout << " ARM1_SCIFIPOSTABLE        " << file_a1scifipostable << endl
       << " ARM1_ADCRANGE             " << file_a1adcrange << endl
       << " ARM1_PARTICLEDEFINE       " << file_a1particledefine << endl
       << " ARM1_SCIFIPARTICLEDEFINE  " << file_a1scifiparticledefine << endl
       << " ARM1_FCPARTICLEDEFINE     " << file_a1fcparticledefine << endl
       << " ARM1_PMTGAINTABLE         " << file_a1pmtgaintable << endl
       << " ARM1_SCIFIGAINTABLE       " << file_a1scifigaintable << endl
       << " ARM1_FCGAINTABLE          " << file_a1fcgaintable << endl
       << " ARM1_HVTABLE              " << file_a1hvtable << endl
       << " ARM1_SCIFICROSSTALKX      " << file_a1scificrosstalkx << endl
       << " ARM1_SCIFICROSSTALKY      " << file_a1scificrosstalky << endl
       << endl;
  fout << " ARM2_ADCRANGE             " << file_a2adcrange << endl
       << " ARM2_PARTICLEDEFINE       " << file_a2particledefine << endl
       << " ARM2_SIPARTICLEDEFINE     " << file_a2siparticledefine << endl
       << " ARM2_FCPARTICLEDEFINE     " << file_a2fcparticledefine << endl
       << " ARM2_PMTGAINTABLE         " << file_a2pmtgaintable << endl
       << " ARM2_SIGAINTABLE          " << file_a2sigaintable << endl
       << " ARM2_FCGAINTABLE          " << file_a2fcgaintable << endl
       << " ARM2_HVTABLE              " << file_a2hvtable << endl
       << endl;
  fout << endl << "END" << endl;

  fout.close();
  return 0;
}

void LHCfParamFiles::SetToDefault_Op2010(){
#ifdef EVENTVIEWDIR
  sprintf(file_a1scifipostable,      "%s/config/scifi_pos_table_080408.dat",EVENTVIEWDIR);
  sprintf(file_a1adcrange,           "%s/config/adcrange_001_080307.dat",EVENTVIEWDIR);
  sprintf(file_a1particledefine,     "%s/config/pdef_sps07_arm1_080828.out",EVENTVIEWDIR);
  sprintf(file_a1scifiparticledefine,"%s/config/pardef_scifi_102_071019.txt",EVENTVIEWDIR); 
  sprintf(file_a1fcparticledefine,   "%s/config/pdef_sps07_arm1_080828.out",EVENTVIEWDIR);
  sprintf(file_a1pmtgaintable,       "%s/config/GainsheetforCERN060812_1609.txt",EVENTVIEWDIR);
  sprintf(file_a1scifigaintable,     "%s/config/scifigaintable_081103.out",EVENTVIEWDIR);
  sprintf(file_a1fcgaintable,        "%s/config/fcgaintable_dummy.txt",EVENTVIEWDIR);
  sprintf(file_a1hvtable,            "%s/config/hvtable_arm1_3.5TeVnormal.txt",EVENTVIEWDIR);
  sprintf(file_a1scificrosstalkx,    "%s/config/CROSSTALK_X_offset.dat",EVENTVIEWDIR);
  sprintf(file_a1scificrosstalky,    "%s/config/CROSSTALK_Y_offset.dat",EVENTVIEWDIR);
  sprintf(file_a2adcrange,           "%s/config/adcrange_001_080307.dat",EVENTVIEWDIR);
  sprintf(file_a2particledefine,     "%s/config/pdef_sps07_arm2_081003.out",EVENTVIEWDIR);
  sprintf(file_a2siparticledefine,   "-");
  sprintf(file_a2fcparticledefine,   "%s/config/pdef_sps07_arm2_081003.out",EVENTVIEWDIR);
  sprintf(file_a2pmtgaintable,       "%s/config/GainsheetforCERN060812_1609.txt",EVENTVIEWDIR);
  sprintf(file_a2sigaintable,        "-");
  sprintf(file_a2fcgaintable,        "%s/config/fcgaintable_dummy.txt",EVENTVIEWDIR); 
  sprintf(file_a2hvtable,            "%s/config/hvtable_arm2_3.5TeVnormal.txt",EVENTVIEWDIR);
#endif
}

void LHCfParamFiles::SetToDefault_Op2013(){
#ifdef EVENTVIEWDIR
#endif
}

void LHCfParamFiles::SetToDefault_Op2015(){
#ifdef EVENTVIEWDIR
  // Default Files 
  sprintf(file_a1scifipostable,      "%s/config/GSObar_map9.tab",EVENTVIEWDIR); 
  sprintf(file_a1adcrange,           "%s/config/adcrange_001_080307.dat",EVENTVIEWDIR); 
  sprintf(file_a1particledefine,     "%s/config/160208_conversion_factors.tab",EVENTVIEWDIR);
  sprintf(file_a1scifiparticledefine,"%s/config/160208_conversion_factors.tab",EVENTVIEWDIR); 
  sprintf(file_a1fcparticledefine,   "%s/config/160208_conversion_factors.tab",EVENTVIEWDIR);
  sprintf(file_a1pmtgaintable,       "%s/config/GainsheetforCERN060812_1609.txt",EVENTVIEWDIR); 
  sprintf(file_a1scifigaintable,     "%s/config/scifigaintable_160727.out",EVENTVIEWDIR); 
  sprintf(file_a1fcgaintable,        "%s/config/fcgaintable_dummy.txt",EVENTVIEWDIR);
  sprintf(file_a1hvtable,            "%s/config/hvtable_arm1_6.5TeVnormal.txt",EVENTVIEWDIR);
  sprintf(file_a1scificrosstalkx,    "%s/config/20141215_XtalkMatrixTemplate.root",EVENTVIEWDIR); 
  sprintf(file_a1scificrosstalky,    "",EVENTVIEWDIR);
  sprintf(file_a2adcrange,           "%s/config/adcrange_001_080307.dat",EVENTVIEWDIR);
  sprintf(file_a2particledefine,     "%s/config/pdef_sps07_arm2_081003.out",EVENTVIEWDIR);
  sprintf(file_a2siparticledefine,   "-");
  sprintf(file_a2fcparticledefine,   "%s/config/pdef_sps07_arm2_081003.out",EVENTVIEWDIR);
  sprintf(file_a2pmtgaintable,       "%s/config/GainsheetforCERN060812_1609.txt",EVENTVIEWDIR);
  sprintf(file_a2sigaintable,        "-");
  sprintf(file_a2fcgaintable,        "%s/config/fcgaintable_dummy.txt",EVENTVIEWDIR); 
  sprintf(file_a2hvtable,            "%s/config/hvtable_arm2_ALL600.txt",EVENTVIEWDIR);
#endif
}

void LHCfParamFiles::SetToDefault_RHICf2017(){
#ifdef EVENTVIEWDIR
  // Default Files 
  sprintf(file_a1scifipostable,      "%s/config/GSObar_map9.tab",EVENTVIEWDIR); 
  sprintf(file_a1adcrange,           "%s/config/adcrange_001_080307.dat",EVENTVIEWDIR); 
  sprintf(file_a1particledefine,     "%s/config/170617_conversion_factors_rhicf.tab",EVENTVIEWDIR);
  sprintf(file_a1scifiparticledefine,"%s/config/170617_conversion_factors_rhicf.tab",EVENTVIEWDIR); 
  sprintf(file_a1fcparticledefine,   "%s/config/170617_conversion_factors_rhicf.tab",EVENTVIEWDIR);
  sprintf(file_a1pmtgaintable,       "%s/config/GainTable_Fit_20170427.txt",EVENTVIEWDIR); 
  sprintf(file_a1scifigaintable,     "%s/config/MAPMTgaintable_20170501.txt",EVENTVIEWDIR); 
  sprintf(file_a1fcgaintable,        "%s/config/fcgaintable_dummy.txt",EVENTVIEWDIR);
  sprintf(file_a1hvtable,            "%s/config/hvtable_rhicf2017_normal.txt",EVENTVIEWDIR);
  sprintf(file_a1scificrosstalkx,    "%s/config/20141215_XtalkMatrixTemplate.root",EVENTVIEWDIR); 
  sprintf(file_a1scificrosstalky,    "",EVENTVIEWDIR);
  sprintf(file_a2adcrange,           "%s/config/adcrange_001_080307.dat",EVENTVIEWDIR);
  sprintf(file_a2particledefine,     "%s/config/pdef_sps07_arm2_081003.out",EVENTVIEWDIR);
  sprintf(file_a2siparticledefine,   "-");
  sprintf(file_a2fcparticledefine,   "%s/config/pdef_sps07_arm2_081003.out",EVENTVIEWDIR);
  sprintf(file_a2pmtgaintable,       "%s/config/GainsheetforCERN060812_1609.txt",EVENTVIEWDIR);
  sprintf(file_a2sigaintable,        "-");
  sprintf(file_a2fcgaintable,        "%s/config/fcgaintable_dummy.txt",EVENTVIEWDIR); 
  sprintf(file_a2hvtable,            "%s/config/hvtable_arm2_ALL600.txt",EVENTVIEWDIR);
#endif
}



#endif
