#ifndef __LHCFRUNINFOTABLE_CPP__
#define __LHCFRUNINFOTABLE_CPP__

#include "LHCfRunInfoTable.h"

//----------------------------------------------------------------------
// Not completed the implementation yet.
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  12 Jan. 10: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------


#if !defined(__CINT__)
ClassImp(LHCfRunInfo);
ClassImp(LHCfRunInfoTable);
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
using namespace std;

// --------------------------------------------------------------------
// -------                   LHCfRunInfo                         ------
// --------------------------------------------------------------------

const int LHCfRunInfo::NBUNCHES;
const int LHCfRunInfo::STRING_LENGTH;
int    LHCfRunInfo::buf_run = -1;
int    LHCfRunInfo::buf_beam1_nbunches = 0;
int    LHCfRunInfo::buf_beam2_nbunches = 0;
int    LHCfRunInfo::buf_beam1_bunches[LHCfRunInfo::NBUNCHES]={0};
int    LHCfRunInfo::buf_beam2_bunches[LHCfRunInfo::NBUNCHES]={0};
int    LHCfRunInfo::buf_beam1_bunches_index[3565]={0};
int    LHCfRunInfo::buf_beam2_bunches_index[3565]={0};
const int LHCfRunInfo::DEFAULT_DAQ_BEAM1_SCL_NBUNCH_OFFSET;
const int LHCfRunInfo::DEFAULT_DAQ_BEAM2_SCL_NBUNCH_OFFSET;


LHCfRunInfo::LHCfRunInfo(){
  clear();
}

LHCfRunInfo::~LHCfRunInfo(){;}

void LHCfRunInfo::clear(){
  // Clear all data 
  ioformat = -1;
  clear_general();
  clear_daq();
  clear_nevents();
  clear_beam();
  clear_analysis();
}

void LHCfRunInfo::clear_general(char op[]){
  // Clear General Information 
  run = -1;
  start_time = 0;
  end_time   = 0;
  if(!strstr(op,"exc_comments")) strcpy(general_comments,""); 
}

void LHCfRunInfo::clear_daq(char op[]){
  // Clear DAQ Information.
  
  a1_runmode = -1;
  a2_runmode = -1;
  strcpy(LTPmode,"-");
  strcpy(a1_LogicMode,"-");
  strcpy(a2_LogicMode,"-");
  strcpy(a1_V1495Load,"-");
  strcpy(a2_V1495Load,"-");
  strcpy(a1_V1495Setup,"-");
  strcpy(a2_V1495Setup,"-");
  strcpy(a1_GPIOLoad,"-");
  strcpy(a2_GPIOLoad,"-");
  strcpy(a1_GPIOSetup,"-");
  strcpy(a2_GPIOSetup,"-");
  strcpy(a1_Discriminator,"-");
  strcpy(a2_Discriminator,"-");  
  a1_scifidaq   = -1;
  a2_silicondaq = -1;
  strcpy(a1_PMTgain,"-");
  strcpy(a2_PMTgain,"-");  
  strcpy(a1_scifigain,"-");
  strcpy(a2_silicongain,"-");   
  strcpy(a1_position,"-");
  strcpy(a2_position,"-");  
  daq_beam1_scl_nbunch_offset = DEFAULT_DAQ_BEAM1_SCL_NBUNCH_OFFSET; 
  daq_beam2_scl_nbunch_offset = DEFAULT_DAQ_BEAM2_SCL_NBUNCH_OFFSET; 
  
  if(!strstr(op,"exc_comments")) strcpy(daq_comments,"");
}

void LHCfRunInfo::clear_nevents(char op[]){
  // Clear Number of Events
  
  nevent = 0;
  a1_nevent = 0;
  a1_nevent_L2TA = 0;
  a1_nevent_L2TA_MB = 0;
  a1_nevent_L2TA_SP = 0;
  a1_nevent_L2TP = 0;
  a1_nevent_laser = 0;
  a2_nevent = 0;
  a2_nevent_L2TA = 0;
  a2_nevent_L2TA_MB = 0;
  a2_nevent_L2TA_SP = 0;
  a2_nevent_L2TP = 0;
  a2_nevent_laser = 0;
  a1scl_nevent = 0;
  a2scl_nevent = 0;
  sc_nevent = 0;
  dipl_nevent = 0;
  diph_nevent = 0;
  dipvh_nevent = 0;
  a1_nevent_l1t = 0;
  a1_nevent_l1t_enable = 0;
  a2_nevent_l1t = 0;
  a2_nevent_l1t_enable = 0;  
  a1_nevent_presetMB = 0;
  a1_nevent_presetSP = 0;
  a2_nevent_presetMB = 0;
  a2_nevent_presetSP = 0;
  // For Operation 2015
  a1_nevent_L2T_Shower = 0;
  a1_nevent_L2T_Special = 0;
  a1_nevent_L2T_Pedestal = 0;
  a1_nevent_L2T_L1T = 0;
  a1_nevent_L2T_FC = 0;
  a2_nevent_L2T_Shower = 0;
  a2_nevent_L2T_Special = 0;
  a2_nevent_L2T_Pedestal = 0;
  a2_nevent_L2T_L1T = 0;
  a2_nevent_L2T_FC = 0;
  a2_ncrcerror = 0;

}



void LHCfRunInfo::clear_beam(char op[]){
  // Clear Beam Configuration. 

  stable_beam = -1;
  crossingangle = -1;
  beam1_nbunches = 0;
  beam2_nbunches = 0;
  beam1_avintensity = 0.;
  beam2_avintensity = 0.;  
  for(int i=0;i<NBUNCHES;i++){
    beam1_bunches[i] = -1;
    beam2_bunches[i] = -1;
    beam1_tag[i] = 0;
    beam2_tag[i] = 0; 
    beam1_avintensitypb[i] = 0.;
    beam2_avintensitypb[i] = 0.; 
    beam_avluminositypb[i] = 0.;
  }
  done_lumiscan = -1;
  if(!strstr(op,"exc_comments")) strcpy(beam_comments,"");
}

void LHCfRunInfo::clear_analysis(char op[]){
  // Clear Analysis Information

  analysis_quality = 0;
  analysis_cut_stime = 0;
  analysis_cut_etime = 0;
  analysis_a1_nevent = 0;
  analysis_a1_nevent_L2TA = 0; 
  analysis_a2_nevent = 0;
  analysis_a2_nevent_L2TA = 0;
  if(!strstr(op,"exc_comments")) strcpy(analysis_comments,"");
}

int LHCfRunInfo::Print(std::ostream &out,int format){
  // Print the all information.  Default: standard output. 
  
  if(format<0){
    if(ioformat>=0){format = ioformat;}
    else           {format = 0;}
  }
  char tmp[256];
  if(format==0){
    PrintGeneral(out,format);
    PrintDAQ(out,format);
    PrintNEvents(out,format);
    PrintBeam(out,format);
    PrintAnalysis(out,format);
    return OK;
  }
  else if(format==1){
    sprintf(tmp,"RUN%05d",run);
    out << "# ---------------------------------------------------------- \n"
	<< "START_RUNINFO   " << tmp << endl;
    out << " FORMAT    "  << format << endl;
    PrintGeneral(out,format);
    PrintDAQ(out,format);
    PrintNEvents(out,format);
    PrintBeam(out,format);
    PrintAnalysis(out,format);
    out << "END_RUNINFO     " << tmp << endl;
    out << endl;    
    return OK;
  }
  else{
    cout << "[LHCfRunInfo::Print] "
	 << "Error: Unknown format " << format << endl;
    return ERROR;
  }
}

int LHCfRunInfo::WriteFile(char *filename,int format){
  // Write the all information in the file.
  // Format number must be 1.(default)
  ofstream fout(filename);
  return Print(fout,format);
}

void LHCfRunInfo::PrintGeneral(std::ostream& out,int format){  
  time_t st,et;
  st = start_time;
  et = end_time;
  if(format==0 || format==1){
    out << " -GENERAL" << endl;
    out << "   RUN         " << run << endl;
    out << "   START_TIME  " << start_time << "    "
	<< asctime(localtime(&st)) << flush;
    out << "   END_TIME    " << end_time   << "    " 
	<< asctime(localtime(&et)) << flush;
    out << "   GENRAL_COMMENTS  " <<  general_comments << endl;
    out << endl;
  }
}

void LHCfRunInfo::PrintDAQ(std::ostream& out,int format){
  if(format==0 || format==1){
    out << right ;
    out << " -DAQ" << endl;
    out << "   A1_RUNMODE   " << a1_runmode << endl
	<< "   A2_RUNMODE   " << a2_runmode << endl
	<< "   LTP_MODE     " << LTPmode << endl
	<< "   A1_LOGICMODE " << a1_LogicMode << endl
      	<< "   A2_LOGICMODE " << a2_LogicMode << endl
	<< "   A1_V1495LOAD " << a1_V1495Load << endl
     	<< "   A2_V1495LOAD " << a2_V1495Load << endl
      	<< "   A1_V1495SETUP " << a1_V1495Setup << endl
      	<< "   A2_V1495SETUP " << a2_V1495Setup << endl
	<< "   A1_GPIOLOAD  " << a1_GPIOLoad << endl
      	<< "   A2_GPIOLOAD  " << a2_GPIOLoad << endl
      	<< "   A1_GPIOSETUP " << a1_GPIOSetup << endl
	<< "   A2_GPIOSETUP " << a2_GPIOSetup << endl
      	<< "   A1_DISCRI    " << a1_Discriminator << endl
       	<< "   A2_DISCRI    " << a2_Discriminator << endl   
	<< "   A1_SCIFIDAQ  " << a1_scifidaq << endl
      	<< "   A2_SIDAQ     " << a2_silicondaq << endl
	<< "   A1_PMTGAIN   " << a1_PMTgain << endl
	<< "   A2_PMTGAIN   " << a2_PMTgain << endl
      	<< "   A1_SCIFIGAIN " << a1_scifigain << endl
      	<< "   A2_SIGAIN    " << a2_silicongain << endl
	<< "   A1_POSITION  " << a1_position << endl
   	<< "   A2_POSITION  " << a2_position << endl 
	<< "   DAQ_BEAM1_OFFSET " << daq_beam1_scl_nbunch_offset << endl
      	<< "   DAQ_BEAM2_OFFSET " << daq_beam2_scl_nbunch_offset << endl
       	<< "   DAQ_COMMENTS " << daq_comments << endl;
    out << endl;
  }
}

void LHCfRunInfo::PrintNEvents(std::ostream& out,int format){
  int size=10; 
  if(format==0 || format==1){
    out << right ;
    out << " -NEVENTS" << endl;
    out << "   TOTAL       " << setw(size) << nevent << endl
	<< "   ARM1        " << setw(size) << a1_nevent  << endl
	<< "   ARM1_L2TA   " << setw(size) << a1_nevent_L2TA << endl
      	<< "   ARM1_L2TA_MB " << setw(size)<< a1_nevent_L2TA_MB << endl
      	<< "   ARM1_L2TA_SP " << setw(size)<< a1_nevent_L2TA_SP << endl
	<< "   ARM1_L2TP   " << setw(size) << a1_nevent_L2TP << endl
	<< "   ARM1_LASER  " << setw(size) << a1_nevent_laser << endl 
     	<< "   ARM1_PRESET_MB " << setw(size) << a1_nevent_presetMB << endl
	<< "   ARM1_PRESET_SP " << setw(size) << a1_nevent_presetSP << endl
	<< "   ARM1_L1T    " << setw(size) << a1_nevent_l1t << endl
      	<< "   ARM1_L1T_EN " << setw(size) << a1_nevent_l1t_enable << endl
	<< "   ARM2        " << setw(size) << a2_nevent  << endl
	<< "   ARM2_L2TA   " << setw(size) << a2_nevent_L2TA << endl 
     	<< "   ARM2_L2TA_MB " << setw(size)<< a2_nevent_L2TA_MB << endl
      	<< "   ARM2_L2TA_SP " << setw(size)<< a2_nevent_L2TA_SP << endl
	<< "   ARM2_L2TP   " << setw(size) << a2_nevent_L2TP << endl
	<< "   ARM2_LASER  " << setw(size) << a2_nevent_laser << endl 
      	<< "   ARM2_PRESET_MB " << setw(size) << a2_nevent_presetMB << endl
	<< "   ARM2_PRESET_SP " << setw(size) << a2_nevent_presetSP << endl
	<< "   ARM2_L1T    " << setw(size) << a2_nevent_l1t << endl
      	<< "   ARM2_L1T_EN " << setw(size) << a2_nevent_l1t_enable << endl
      // For Opration 2015
	<< "   ARM1_L2T_SHOWER   " << setw(size) << a1_nevent_L2T_Shower << endl
	<< "   ARM1_L2T_SPECIAL  " << setw(size) << a1_nevent_L2T_Special << endl
	<< "   ARM1_L2T_PEDESTAL " << setw(size) << a1_nevent_L2T_Pedestal<< endl
	<< "   ARM1_L2T_L1T      " << setw(size) << a1_nevent_L2T_L1T << endl
      	<< "   ARM1_L2T_FC       " << setw(size) << a1_nevent_L2T_FC  << endl
  	<< "   ARM2_L2T_SHOWER   " << setw(size) << a2_nevent_L2T_Shower << endl
	<< "   ARM2_L2T_SPECIAL  " << setw(size) << a2_nevent_L2T_Special << endl
	<< "   ARM2_L2T_PEDESTAL " << setw(size) << a2_nevent_L2T_Pedestal<< endl
	<< "   ARM2_L2T_L1T      " << setw(size) << a2_nevent_L2T_L1T << endl
      	<< "   ARM2_L2T_FC       " << setw(size) << a2_nevent_L2T_FC  << endl
	<< "   ARM1_SCL    " << setw(size) << a1scl_nevent  << endl
	<< "   ARM2_SCL    " << setw(size) << a2scl_nevent  << endl
	<< "   SLOWCONTROL " << setw(size) << sc_nevent << endl
	<< "   DIPL        " << setw(size) << dipl_nevent << endl
	<< "   DIPH        " << setw(size) << diph_nevent << endl 
	<< "   DIPVH       " << setw(size) << dipvh_nevent << endl    
	<< "   ARM2_CRCERROR     " << setw(size) << a2_ncrcerror << endl   
	<< endl; 
    out << endl;
  }
}

void LHCfRunInfo::PrintBeam(ostream& out,int format){ 
  if(format==0 || format==1){
    out << " -BEAM_INFORMATION" << endl;
    out << "   STABLE_BEAM        " <<  stable_beam << endl;
    out << "   CROSSINGANGLE      " <<  crossingangle << endl;
    out.setf(ios::scientific);  
    out << "   BEAM1_AVINTENSITY  " << setprecision(4) << beam1_avintensity << endl;
    out << "   BEAM2_AVINTENSITY  " << setprecision(4) << beam2_avintensity << endl;  
    out.unsetf(ios::scientific);
    out << "   BEAM1_NBUNCHES     " <<  beam1_nbunches << endl;
    out << "   BRAM1_BUNCHES" << endl;
    out << right ;
    out << "    ";
    out.setf(ios::scientific);
    for(int i=0;i<beam1_nbunches;i++){
      out << setw(4) << beam1_bunches[i] << "  " 
	  << setw(2) << beam1_tag[i] << "  " 
	  << setw(8) << setprecision(4) << beam1_avintensitypb[i] << " " 
	  << "    ";
      if((i+1)%3==0 && (i+1)!=beam1_nbunches){
	out << endl << "    " ;
      }
    }
    out << endl; 
    out << "   BEAM2_NBUNCHES  " <<  beam2_nbunches << endl;
    out << "   BRAM2_BUNCHES" << endl;  
    out << "    ";
    for(int i=0;i<beam2_nbunches;i++){
      out << setw(4) << beam2_bunches[i] << "  " 
	  << setw(2) << beam2_tag[i] << "  " 
	  << setw(8) << setprecision(4) << beam2_avintensitypb[i] << " " 
	  << "    ";
      if((i+1)%3==0 && (i+1)!=beam2_nbunches){
	out << endl << "    " ;
      }
    } 
    out << endl; 
    out << "   BEAM_AVERAGELUMINOSITYPERBUNCH" << endl; 
    out << "    ";
    for(int i=0;i<beam1_nbunches;i++){
      out << setw(10) << setprecision(5) << beam_avluminositypb[i] << "    " ;
      if((i+1)%3==0 && (i+1)!=beam1_nbunches){
	out << endl << "    " ;
      }
    }
    out << endl;;
    out.unsetf(ios::scientific);
    out << "   DONE_LUMISCAN   " <<  done_lumiscan << endl;
    out << "   BEAM_COMMENTS   " <<  beam_comments << endl;
    out << endl;
  } 
}

void LHCfRunInfo::PrintAnalysis(ostream& out,int format){ 
  int size=10;
  time_t st,et;
  st = analysis_cut_stime;
  et = analysis_cut_etime; 
  if(format==0 || format==1){
    out << " -ANALYSIS_INFOMATION " << endl
	<< "   ANA_QUALITY     " << analysis_quality << endl ;
    out << "   ANA_CUT_STIME   " << analysis_cut_stime << "    " 
	<< asctime(localtime(&st)) << flush; 
    out << "   ANA_CUT_ETIME   " << analysis_cut_etime << "    "
	<< asctime(localtime(&et)) << flush;
    out << "   ANA_ARM1_NEVENT      " << setw(size) << analysis_a1_nevent << endl
	<< "   ANA_ARM1_NEVENT_L1TA " << setw(size) << analysis_a1_nevent_L2TA << endl
	<< "   ANA_ARM2_NEVENT      " << setw(size) << analysis_a2_nevent << endl
	<< "   ANA_ARM2_NEVENT_L1TA " << setw(size) << analysis_a2_nevent_L2TA << endl
	<< "   ANA_COMMENTS    " << analysis_comments << endl;
    out << endl;
  }
  return ;
}

int LHCfRunInfo::Read(istream& in){
  // Read the information from the streamer.
  
  string ss,stmp;
  istringstream sin;
  bool check_start=false;
  bool check_end=false;
  int  itmp;
  
  // -----  Check Format  ------
  int format = -1;
  while(getline(in,ss)){
    if(ss[0]=='#') continue;
    if(ss.find("START_RUNINFO")!=string::npos){check_start=true;continue;}
    if(check_start==false){continue;}
    sin.clear();
    sin.str(ss);
    sin >> stmp;
    if(stmp=="FORMAT"){ sin >> format; break;}
  }
  
  // -- CHECK OF EOF 
  if(!check_start){return ERROR;}
  
  if(format==-1){
    cerr << "[LHCfRunInfo::Read] " 
	 << "ERROR: Cannot find format paramters (\"FORMAT\") " << endl;
    return ERROR;
  }
  else if(format==1){
    ioformat = format;
    while(getline(in,ss)){

      if(ss[0]=='#') continue;
      if(ss.find("START_RUNINFO")!=string::npos){check_start=true;continue;}
      if(ss.find("END_RUNINFO")!=string::npos){check_end=true;break;}
      if(check_start==false){continue;}
      
      sin.clear();
      sin.str(ss);
      sin >> stmp;

      // general 
      if(stmp=="RUN"){sin >> run;}
      else if(stmp=="START_TIME"){sin >> start_time;}
      else if(stmp=="END_TIME"){sin >> end_time;}
      else if(stmp=="GENERAL_COMMENTS"){
	getline(sin,stmp);
	removespace(stmp);
	strncpy(general_comments,stmp.c_str(),256);
      }
      // DAQ
      else if(stmp=="A1_RUNMODE"){sin >> a1_runmode;}
      else if(stmp=="A2_RUNMODE"){sin >> a2_runmode;}
      else if(stmp=="LTP_MODE") {sin >> LTPmode;}
      else if(stmp=="A1_LOGICMODE") {sin >> a1_LogicMode;} 
      else if(stmp=="A2_LOGICMODE") {sin >> a2_LogicMode;} 
      else if(stmp=="A1_V1495LOAD") {sin >> a1_V1495Load;}
      else if(stmp=="A2_V1495LOAD") {sin >> a2_V1495Load;}
      else if(stmp=="A1_V1495SETUP") {sin >> a1_V1495Setup;} 
      else if(stmp=="A2_V1495SETUP") {sin >> a2_V1495Setup;} 
      else if(stmp=="A1_GPIOLOAD"){ sin >> a1_GPIOLoad;}
      else if(stmp=="A2_GPIOLOAD"){ sin >> a2_GPIOLoad;}
      else if(stmp=="A1_GPIOSETUP"){ sin >> a1_GPIOSetup;}
      else if(stmp=="A2_GPIOSETUP"){ sin >> a2_GPIOSetup;}
      else if(stmp=="A1_DISCRI"){ sin >> a1_Discriminator;}
      else if(stmp=="A2_DISCRI"){ sin >> a2_Discriminator;}
      else if(stmp=="A1_SCIFIDAQ"){ sin >> a1_scifidaq;}
      else if(stmp=="A2_SIDAQ"){ sin >> a2_silicondaq;}  
      else if(stmp=="A1_PMTGAIN"){ sin >> a1_PMTgain;}
      else if(stmp=="A2_PMTGAIN"){ sin >> a2_PMTgain;}
      else if(stmp=="A1_SCIFIGAIN"){sin >> a1_scifigain;}
      else if(stmp=="A2_SIGAIN")   {sin >> a2_silicongain;}
      else if(stmp=="A1_POSITION"){sin >> a1_position;}
      else if(stmp=="A2_POSITION"){sin >> a2_position;}
      else if(stmp=="DAQ_BEAM1_OFFSE"){ sin >> daq_beam1_scl_nbunch_offset;}
      else if(stmp=="DAQ_BEAM2_OFFSE"){ sin >> daq_beam2_scl_nbunch_offset;}  
      else if(stmp=="DAQ_COMMENTS"){
	getline(sin,stmp);
	removespace(stmp);
	strncpy(daq_comments,stmp.c_str(),256);	
      }
      // NEvents
      else if(stmp=="TOTAL"){sin >> nevent;}
      else if(stmp=="ARM1"){sin >>  a1_nevent;}
      else if(stmp=="ARM1_L2TA"){sin >> a1_nevent_L2TA;} 
      else if(stmp=="ARM1_L2TA_MB"){sin >> a1_nevent_L2TA_MB;} 
      else if(stmp=="ARM1_L2TA_SP"){sin >> a1_nevent_L2TA_SP;}
      else if(stmp=="ARM1_L2TP"){sin >> a1_nevent_L2TP;}
      else if(stmp=="ARM1_LASER"){sin >> a1_nevent_laser;}  
      else if(stmp=="ARM1_PRESET_MB"){sin >> a1_nevent_presetMB;}
      else if(stmp=="ARM1_PRESET_SP"){sin >> a1_nevent_presetSP;} 
      else if(stmp=="ARM1_L1T") {sin >> a1_nevent_l1t;}
      else if(stmp=="ARM1_L1T_EN") {sin >> a1_nevent_l1t_enable;}
      else if(stmp=="ARM2"){sin >> a2_nevent;}
      else if(stmp=="ARM2_L2TA"){sin >> a2_nevent_L2TA;} 
      else if(stmp=="ARM2_L2TA_MB"){sin >> a2_nevent_L2TA_MB;} 
      else if(stmp=="ARM2_L2TA_SP"){sin >> a2_nevent_L2TA_SP;} 
      else if(stmp=="ARM2_L2TP"){sin >> a2_nevent_L2TP;}
      else if(stmp=="ARM2_LASER"){sin >> a2_nevent_laser;}
      else if(stmp=="ARM2_PRESET_MB"){sin >> a2_nevent_presetMB;}
      else if(stmp=="ARM2_PRESET_SP"){sin >> a2_nevent_presetSP;}
      else if(stmp=="ARM2_L1T") {sin >> a2_nevent_l1t;}
      else if(stmp=="ARM2_L1T_EN") {sin >> a2_nevent_l1t_enable;}
      // For Operation 2015
      else if(stmp=="ARM1_L2T_SHOWER") {sin >> a1_nevent_L2T_Shower;}
      else if(stmp=="ARM1_L2T_SPECIAL") {sin >> a1_nevent_L2T_Special;}
      else if(stmp=="ARM1_L2T_PEDESTAL") {sin >> a1_nevent_L2T_Pedestal;}
      else if(stmp=="ARM1_L2T_L1T") {sin >> a1_nevent_L2T_L1T;} 
      else if(stmp=="ARM1_L2T_FC") {sin >> a1_nevent_L2T_FC;}
      else if(stmp=="ARM2_L2T_SHOWER") {sin >> a2_nevent_L2T_Shower;}
      else if(stmp=="ARM2_L2T_SPECIAL") {sin >> a2_nevent_L2T_Special;}
      else if(stmp=="ARM2_L2T_PEDESTAL") {sin >> a2_nevent_L2T_Pedestal;}
      else if(stmp=="ARM2_L2T_L1T") {sin >> a2_nevent_L2T_L1T;} 
      else if(stmp=="ARM2_L2T_FC") {sin >> a2_nevent_L2T_FC;}
      else if(stmp=="ARM1_SCL"){sin >> a1scl_nevent;}
      else if(stmp=="ARM2_SCL"){sin >> a2scl_nevent;}  
      else if(stmp=="SLOWCONTROL"){sin >> sc_nevent;}
      else if(stmp=="DIPL"){sin >> dipl_nevent;}   
      else if(stmp=="DIPH"){sin >> diph_nevent;}
      else if(stmp=="DIPVH"){sin >> diph_nevent;}  
      else if(stmp=="ARM2_CRCERROR") {sin >> a2_ncrcerror;}
      // BEAN CONFIGURATION
      else if(stmp=="STABLE_BEAM"){sin >>  stable_beam;}
      else if(stmp=="CROSSINGANGLE") {sin >> crossingangle;}
      else if(stmp=="BEAM1_AVINTENSITY"){ sin >>  beam1_avintensity;}
      else if(stmp=="BEAM2_AVINTENSITY"){ sin >>  beam2_avintensity;}   
      else if(stmp=="BEAM1_NBUNCHES"){
	sin >> beam1_nbunches; 
	if(beam1_nbunches>NBUNCHES) { beam1_nbunches = NBUNCHES;}
      }
      else if(stmp=="BRAM1_BUNCHES"){
	itmp=0;
	for(int il=0;il<beam1_nbunches/3+1;il++){
	  getline(in,ss);
	  sin.clear();
	  sin.str(ss);
	  for(int is=0;is<3;is++){
	    sin >> beam1_bunches[itmp];
	    sin >> beam1_tag[itmp];
	    sin >> beam1_avintensitypb[itmp];
	    itmp++;
	    if(itmp>=beam1_nbunches){break;}
	  }
	  if(itmp>=beam1_nbunches){break;}
	}
      }
      else if(stmp=="BEAM2_NBUNCHES"){
	sin >> beam2_nbunches;
	if(beam2_nbunches>NBUNCHES) { beam2_nbunches = NBUNCHES;}	
      }
      else if(stmp=="BRAM2_BUNCHES"){
	itmp=0;
	for(int il=0;il<beam2_nbunches/3+1;il++){
	  getline(in,ss);
	  sin.clear();
	  sin.str(ss);
	  for(int is=0;is<3;is++){
	    sin >> beam2_bunches[itmp];
	    sin >> beam2_tag[itmp];
	    sin >> beam2_avintensitypb[itmp];
	    itmp++;
	    if(itmp>=beam2_nbunches){break;}
	  }
	  if(itmp>=beam2_nbunches){break;}
	}
      }  
      else if(stmp=="BEAM_AVERAGELUMINOSITYPERBUNCH"){
	itmp=0;
	for(int il=0;il<beam1_nbunches/3+1;il++){
	  getline(in,ss);
	  sin.clear();
	  sin.str(ss);
	  for(int is=0;is<3;is++){
	    sin >> beam_avluminositypb[itmp];
	    itmp++;
	    if(itmp>=beam1_nbunches){break;}
	  }
	  if(itmp>=beam1_nbunches){break;}
	}
      }
      else if(stmp=="DONE_LUMISCAN"){sin >> done_lumiscan;}
      else if(stmp=="BEAM_COMMENTS"){
	getline(sin,stmp);
	removespace(stmp);
	strncpy(beam_comments,stmp.c_str(),256);
      }
      // ANALYSIS
      else if(stmp=="ANA_QUALITY"){sin >> analysis_quality;}    
      else if(stmp=="ANA_CUT_STIME"){sin >> analysis_cut_stime;}   
      else if(stmp=="ANA_CUT_ETIME"){sin >> analysis_cut_etime;}
      else if(stmp=="ANA_ARM1_NEVENT"){sin >> analysis_a1_nevent;}
      else if(stmp=="ANA_ARM1_NEVENT_L1TA"){sin >> analysis_a1_nevent_L2TA;}
      else if(stmp=="ANA_ARM2_NEVENT"){sin >> analysis_a2_nevent;}
      else if(stmp=="ANA_ARM2_NEVENT_L1TA"){sin >> analysis_a2_nevent_L2TA;}
      else if(stmp=="ANA_COMMENTS"){
	getline(sin,stmp);
	removespace(stmp);
	strncpy(analysis_comments,stmp.c_str(),256);
      } 
    }

    if(check_start && check_end){return OK;}
    else{return ERROR;}
  }
  else{
    cerr << "[LHCfRunInfo::Read] "
	 << "ERROR: Unknown format " << format
	 << endl;
    return ERROR;
  }  
}

int  LHCfRunInfo::ReadFile(char* filename){
  // Read Information from the file.
  ifstream fin(filename);
  if(!fin){
    cerr << "[LHCfRunInfo::ReadFile] "
	 << "Cannot open " << filename << endl;
    return ERROR;
  } 
  return Read(fin);
}

void LHCfRunInfo::removespace(string& s){
  // Internal function 
  for(int i=0;i<100;i++){
    if(s[0]==' '){s = s.substr(1);}
    else{break;}
  }
}

int  LHCfRunInfo::IndexToBunch(int beam,int index){
  // Return Bunch Position by Bunch Index 
  // beam:   1 or 2
  // index:  0-nbunches
  
  if(beam==1) {return beam1_bunches[index];}
  if(beam==2) {return beam2_bunches[index];}
  return 0;
}

int  LHCfRunInfo::BunchToIndex(int beam,int bunch){
  // Return Bunch Index by Bunch Position
  // beam:    1 or 2 
  // bunch:   1-3565
  
  if(buf_run!=run){
    // clear buffer
    for(int i=0;i<buf_beam1_nbunches;i++){
      buf_beam1_bunches_index[buf_beam1_bunches[i]] = 0;
    }
    for(int i=0;i<buf_beam2_nbunches;i++){
      buf_beam2_bunches_index[buf_beam2_bunches[i]] = 0;
    }
    // set buffer
    for(int i=0;i<beam1_nbunches;i++){
      buf_beam1_bunches_index[beam1_bunches[i]] = i;
      buf_beam1_bunches[i] = beam1_bunches[i];
    }
    buf_beam1_nbunches = beam1_nbunches;
    for(int i=0;i<beam2_nbunches;i++){
      buf_beam2_bunches_index[beam2_bunches[i]] = i;
      buf_beam2_bunches[i] = beam2_bunches[i];
    }      
    buf_beam2_nbunches = beam2_nbunches;
    buf_run = run;
  }
  if(beam==1){
    return buf_beam1_bunches_index[bunch];
  }
  if(beam==2){
    return buf_beam2_bunches_index[bunch];
  }
  return 0;
}

int  LHCfRunInfo::CountBCtoBunch(int beam, int count){
  // Return Bunch Position by BC Count in GPIO_LHCFCOUNTER.
  // Just count - daq_beam1_scl_nbunch_offset.
  // beam:    1 or 2
  // count:   Beam1: A*Cal1::connter[23]
  //          Beam2: A*Cal1::counter[23]

  if(beam==1){return count - daq_beam1_scl_nbunch_offset;}
  if(beam==2){return count - daq_beam2_scl_nbunch_offset;}
  return 0;
}

int  LHCfRunInfo::CountBCtoIndex(int beam, int count){
  // Return Bunch Index by BC Count in GPIO_LHCFCOUNTER.
  // beam:    1 or 2
  // count:   Beam1: A*Cal1::connter[23]
  //          Beam2: A*Cal1::counter[23]

  return BunchToIndex(beam, CountBCtoBunch(beam,count));
}

int  LHCfRunInfo::GetBunchTagByIndex(int beam, int index){
  // Return Bunch Tag by Bunch Index
  // beam:    1 or 2
  // index:   0-nbunches
  
  if(beam==1 && index < NBUNCHES) return beam1_tag[index];
  if(beam==2 && index < NBUNCHES) return beam2_tag[index];
  return 0;
}

int  LHCfRunInfo::GetBunchTag(int beam,int bunch){
  // Return Bunch Tag by Bunch Position.
  // beam:    1 or 2 
  // bunch:   1-3565

  return GetBunchTagByIndex(beam, BunchToIndex(beam,bunch));
}

int  LHCfRunInfo::GetBunchTagByCountBC(int beam, int bunch){
  // Return Bunch Tag by BC Count in GPIO_LHCFCOUNTER.
  // beam:    1 or 2
  // count:   Beam1: A*Cal1::connter[23]
  //          Beam2: A*Cal1::counter[23]
  
  return GetBunchTagByIndex(beam, CountBCtoIndex(beam,bunch));
}

int  LHCfRunInfo::CheckTime(int t){
  // if t is in time window of physics analysis, return 1. if not, return 0. 

  if(analysis_quality == 1 &&
     t >= analysis_cut_stime && 
     t <= analysis_cut_etime ){
    return 1;
  }
  else{
    return 0;
  }
}

int  LHCfRunInfo::CheckBunchQuality(A1Cal1* cal){
  // if bunch quality is good, return 1. if not, return 0.
  
  int tag = GetBunchTag(cal);
  if(tag>0){
    return 1;
  }
  else{
    return 0;
  }
}

int  LHCfRunInfo::CheckBunchQuality(A2Cal1* cal){
  // if bunch quality is good, return 1. if not, return 0.
  
  int tag = GetBunchTag(cal);
  if(tag>0){
    return 1;
  }
  else{
    return 0;
  }
}


string LHCfRunInfo::CutdownGPIOSetup(char csetup[]){
  string ss = csetup;
  string cword;
  
  // For setup_a1_****.sh 
  cword = "setup_a1_";
  if(ss.find(cword)!=string::npos){ 
    ss = ss.substr(ss.find(cword)+cword.size(),
		   ss.size()-(ss.find(cword)+cword.size()));

  }
  // For setup_a1_****.sh   
  cword = "setup_a2_";
  if(ss.find(cword)!=string::npos){
    ss = ss.substr(ss.find(cword)+cword.size(),
		   ss.size()-(ss.find(cword)+cword.size()));
  }
  
  cword = ".sh";
  if(ss.find(cword)!=string::npos){
    ss = ss.substr(0,
		   ss.size()-(cword.size()));
  }
  return ss;
}

// --------------------------------------------------------------------
// -------                 LHCfRunInfoTable                      ------
// --------------------------------------------------------------------


LHCfRunInfoTable::LHCfRunInfoTable(){
  Clear();
}

LHCfRunInfoTable::LHCfRunInfoTable(char* filename,int format){
  Clear();
  ReadTable(filename);
}

LHCfRunInfoTable::~LHCfRunInfoTable(){;}

void LHCfRunInfoTable::Clear(){
  ioformat = -1;
  ninfo = 0;
  iinfo = 0;
  irun  = 0;
  for(int i=0;i<(int)runinfo.size();i++){
    if(runinfo[i]) delete runinfo[i];
  }
  runinfo.clear();
}

LHCfRunInfo*  LHCfRunInfoTable::SetRun(int run){
  // to save the search time.
  if(run==irun){
    return runinfo[iinfo];
  }
  
  // search in the table.
  for(int i=0;i<ninfo;i++){
    if(runinfo[i]->run == run){
      iinfo = i;
      irun  = run;
      return runinfo[i]; 
    }
  }
  
  return NULL;
}

LHCfRunInfo*  LHCfRunInfoTable::GetIinfo(int i){
  if(i<0 || i>=ninfo){ return NULL;}
  iinfo  = i;
  irun   = runinfo[i]->run;
  return runinfo[i];
}

LHCfRunInfo*  LHCfRunInfoTable::CreateInfo(){
  iinfo = ninfo;
  irun  = -1;
  runinfo.push_back(new LHCfRunInfo());
  ninfo++;
  return runinfo[iinfo];
}

int LHCfRunInfoTable::ReadTable(char filename[256]){
  ifstream fin(filename);
  if(!fin){
    cerr << "[LHCfRunInfoTable::ReadTable] "
	 << "Cannot open " << filename << endl;
    return ERROR;
  }
  
  LHCfRunInfo* infodata = new LHCfRunInfo();
  for(int i=0;i<5000;i++){ // for safty, the loop limit is 5000
    if(fin.eof()) break;
    if(infodata->Read(fin)==OK){
      runinfo.push_back(infodata);
      ninfo++;
      infodata =  new LHCfRunInfo();
    }
    else{
      break;
    }
  }
  fin.close();
  if(infodata->run < 0 ){ delete infodata;}

  return OK;
}

int LHCfRunInfoTable::WriteTable(char* filename,int format){
  ofstream fout(filename); 
  
  for(int i=0;i<ninfo;i++){
    runinfo[i]->Print(fout,format);
    fout << endl;
  }
  fout.close();
  return OK;
}









#endif
