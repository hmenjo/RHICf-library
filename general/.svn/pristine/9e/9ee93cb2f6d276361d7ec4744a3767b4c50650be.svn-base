#ifndef __RHICFRUNINFOTABLE_CPP__
#define __RHICFRUNINFOTABLE_CPP__

#include "RHICfRunInfoTable.h"

//----------------------------------------------------------------------
// Not completed the implementation yet.
// +++ Logs ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  12 Jan. 10: First edited by H.MENJO
//  31 Jan. 10: Added  ClassDef and ClassImp to make a manual automanitically by H.MENJO. 
//
//----------------------------------------------------------------------


#if !defined(__CINT__)
ClassImp(RHICfRunInfo);
ClassImp(RHICfRunInfoTable);
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
using namespace std;

// --------------------------------------------------------------------
// -------                   RHICfRunInfo                         ------
// --------------------------------------------------------------------

const Int_t RHICfRunInfo::NBUNCHES;
const Int_t RHICfRunInfo::STRING_LENGTH;
Int_t    RHICfRunInfo::buf_run = -1;
Int_t    RHICfRunInfo::buf_beam1_nbunches = 0;
Int_t    RHICfRunInfo::buf_beam2_nbunches = 0;
Int_t    RHICfRunInfo::buf_beam1_bunches[RHICfRunInfo::NBUNCHES]={0};
Int_t    RHICfRunInfo::buf_beam2_bunches[RHICfRunInfo::NBUNCHES]={0};
Int_t    RHICfRunInfo::buf_beam1_bunches_index[3565]={0};
Int_t    RHICfRunInfo::buf_beam2_bunches_index[3565]={0};
const Int_t RHICfRunInfo::DEFAULT_DAQ_BEAM1_SCL_NBUNCH_OFFSET;
const Int_t RHICfRunInfo::DEFAULT_DAQ_BEAM2_SCL_NBUNCH_OFFSET;


RHICfRunInfo::RHICfRunInfo(){
  clear();
}

RHICfRunInfo::~RHICfRunInfo(){;}

void RHICfRunInfo::clear(){
  // Clear all data 
  ioformat = -1;
  clear_general();
  clear_daq();
  clear_nevents();
  clear_beam();
  clear_analysis();
}

void RHICfRunInfo::clear_general(char op[]){
  // Clear General Information 
  run = -1;
  start_time = 0;
  end_time   = 0;
  if(!strstr(op,"exc_comments")) strcpy(general_comments,""); 
}

void RHICfRunInfo::clear_daq(char op[]){
  // Clear DAQ Information.
  
  a1_runmode = -1;
  strcpy(a1_LogicMode,"-");
  strcpy(a1_GPIOLoad,"-");
  strcpy(a1_GPIOLoadFiles[0],"-");
  strcpy(a1_GPIOLoadFiles[1],"-");
  strcpy(a1_GPIOSetup,"-");
  strcpy(a1_Discriminator,"-");
  a1_scifidaq   = -1;
  common_operation = -1;
  strcpy(a1_PMTgain,"-");
  strcpy(a1_scifigain,"-");
  strcpy(a1_position,"-");
  daq_beam1_scl_nbunch_offset = DEFAULT_DAQ_BEAM1_SCL_NBUNCH_OFFSET; 
  daq_beam2_scl_nbunch_offset = DEFAULT_DAQ_BEAM2_SCL_NBUNCH_OFFSET; 
  
  if(!strstr(op,"exc_comments")) strcpy(daq_comments,"");
}

void RHICfRunInfo::clear_nevents(char op[]){
  // Clear Number of Events
  
  nevent = 0;
  a1_nevent = 0;
  a1scl_nevent = 0;
  sc_nevent = 0;
  a1_nevent_presetMB = 0;
  a1_nevent_presetSP = 0;
  // For Operation 2017
  a1_nevent_L3T_Shower = 0;
  a1_nevent_L3T_Special1 = 0;
  a1_nevent_L3T_Special2 = 0;
  a1_nevent_L3T_Pedestal = 0;
  a1_nevent_L3T_L1T = 0;
  a1_nevent_L3T_Shower_TS = 0;
  a1_nevent_L3T_Shower_TL = 0;
  a1_nevent_L3T_STAR = 0;
  a1_nevent_STAR_Only = 0;
  
  a1_nevent_l1t = 0;
  a1_nevent_l1t_enable = 0; 
}



void RHICfRunInfo::clear_beam(char op[]){
  // Clear Beam Configuration. 

  stable_beam = -1;
  crossingangle = -1;
  beam1_nbunches = 0;
  beam2_nbunches = 0;
  beam1_avintensity = 0.;
  beam2_avintensity = 0.;  
  for(Int_t i=0;i<NBUNCHES;i++){
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

void RHICfRunInfo::clear_analysis(char op[]){
  // Clear Analysis Information

  analysis_quality = 0;
  analysis_cut_stime = 0;
  analysis_cut_etime = 0;
  analysis_a1_nevent = 0;
  //analysis_a1_nevent_L2TA = 0; 
  if(!strstr(op,"exc_comments")) strcpy(analysis_comments,"");
}

Int_t RHICfRunInfo::Print(std::ostream &out,Int_t format){
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
    cout << "[RHICfRunInfo::Print] "
	 << "Error: Unknown format " << format << endl;
    return ERROR;
  }
}

Int_t RHICfRunInfo::WriteFile(char *filename,Int_t format){
  // Write the all information in the file.
  // Format number must be 1.(default)
  ofstream fout(filename);
  return Print(fout,format);
}

void RHICfRunInfo::PrintGeneral(std::ostream& out,Int_t format){  
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

void RHICfRunInfo::PrintDAQ(std::ostream& out,Int_t format){
  if(format==0 || format==1){
    out << right ;
    out << " -DAQ" << endl;
    out << "   A1_RUNMODE   " << a1_runmode << endl
		  << "   A1_LOGICMODE " << a1_LogicMode << endl
		  << "   A1_GPIOLOAD  " << a1_GPIOLoad << endl
		  << "   A1_GPIOLOADFILES " << a1_GPIOLoadFiles[0] << " " << a1_GPIOLoadFiles[1] << endl
		  << "   A1_GPIOSETUP " << a1_GPIOSetup << endl
		  << "   A1_DISCRI    " << a1_Discriminator << endl
		  << "   A1_SCIFIDAQ  " << a1_scifidaq << endl
		  << "   COMMON_OPERATION " << common_operation << endl 
		  << "   A1_PMTGAIN   " << a1_PMTgain << endl
		  << "   A1_SCIFIGAIN " << a1_scifigain << endl
		  << "   A1_POSITION  " << a1_position << endl
		  << "   DAQ_BEAM1_OFFSET " << daq_beam1_scl_nbunch_offset << endl
		  << "   DAQ_BEAM2_OFFSET " << daq_beam2_scl_nbunch_offset << endl
		  << "   DAQ_COMMENTS " << daq_comments << endl;
    out << endl;
  }
}

void RHICfRunInfo::PrintNEvents(std::ostream& out,Int_t format){
  Int_t size=15; 
  if(format==0 || format==1){
    out << right ;
    out << " -NEVENTS" << endl;
    out << "   TOTAL       " << setw(size) << nevent << endl
		  << "   ARM1        " << setw(size) << a1_nevent  << endl
		  << "   ARM1_L1T           " << setw(size) << a1_nevent_l1t << endl
		  << "   ARM1_L1T_EN        " << setw(size) << a1_nevent_l1t_enable << endl
		  << "   ARM1_PRESET_MB     " << setw(size) << a1_nevent_presetMB << endl
		  << "   ARM1_PRESET_SP     " << setw(size) << a1_nevent_presetSP << endl
		  << "   ARM1_L3T_SHOWER    " << setw(size) << a1_nevent_L3T_Shower << endl
		  << "   ARM1_L3T_SPECIAL1  " << setw(size) << a1_nevent_L3T_Special1 << endl
		  << "   ARM1_L3T_SPECIAL2  " << setw(size) << a1_nevent_L3T_Special2 << endl
		  << "   ARM1_L3T_PEDESTAL  " << setw(size) << a1_nevent_L3T_Pedestal<< endl
		  << "   ARM1_L3T_L1T       " << setw(size) << a1_nevent_L3T_L1T << endl
		  << "   ARM1_L3T_SHOWER_TS " << setw(size)<< a1_nevent_L3T_Shower_TS << endl
		  << "   ARM1_L3T_SHOWER_TL " << setw(size)<< a1_nevent_L3T_Shower_TL << endl
		  << "   ARM1_L3T_STAR      " << setw(size)<< a1_nevent_L3T_STAR << endl
		  << "   ARM1_STAR_ONLY     " << setw(size)<< a1_nevent_STAR_Only << endl
		  << "   ARM1_SCL    " << setw(size) << a1scl_nevent  << endl
		  << "   SLOWCONTROL " << setw(size) << sc_nevent << endl
		  << endl; 
    out << endl;
  }
}

void RHICfRunInfo::PrintBeam(ostream& out,Int_t format){ 
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
    for(Int_t i=0;i<beam1_nbunches;i++){
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
    for(Int_t i=0;i<beam2_nbunches;i++){
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
    for(Int_t i=0;i<beam1_nbunches;i++){
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

void RHICfRunInfo::PrintAnalysis(ostream& out,Int_t format){ 
  Int_t size=10;
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
      //<< "   ANA_ARM1_NEVENT_L1TA " << setw(size) << analysis_a1_nevent_L2TA << endl
	<< "   ANA_COMMENTS    " << analysis_comments << endl;
    out << endl;
  }
  return ;
}

Int_t RHICfRunInfo::Read(istream& in){
  // Read the information from the streamer.
  
  string ss,stmp;
  istringstream sin;
  bool check_start=false;
  bool check_end=false;
  Int_t  itmp;
  
  // -----  Check Format  ------
  Int_t format = -1;
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
    cerr << "[RHICfRunInfo::Read] " 
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
      else if(stmp=="A1_LOGICMODE") {sin >> a1_LogicMode;} 
      else if(stmp=="A1_GPIOLOAD"){ sin >> a1_GPIOLoad;}
		else if(stmp=="A1_GPIOLOADFILES"){ sin >> a1_GPIOLoadFiles[0] >>a1_GPIOLoadFiles[1];} 
      else if(stmp=="A1_GPIOSETUP"){ sin >> a1_GPIOSetup;}
      else if(stmp=="A1_DISCRI"){ sin >> a1_Discriminator;}
      else if(stmp=="A1_SCIFIDAQ"){ sin >> a1_scifidaq;}
      else if(stmp=="A1_PMTGAIN"){ sin >> a1_PMTgain;}
      else if(stmp=="A1_SCIFIGAIN"){sin >> a1_scifigain;}
		else if(stmp=="COMMON_OPERATION"){sin >> common_operation;}
      else if(stmp=="A1_POSITION"){sin >> a1_position;}
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
      else if(stmp=="ARM1_L1T") {sin >> a1_nevent_l1t;}
      else if(stmp=="ARM1_L1T_EN") {sin >> a1_nevent_l1t_enable;}
      else if(stmp=="ARM1_L3T_SHOWER") {sin >> a1_nevent_L3T_Shower;}
      else if(stmp=="ARM1_L3T_SPECIAL1") {sin >> a1_nevent_L3T_Special1;}
      else if(stmp=="ARM1_L3T_SPECIAL2") {sin >> a1_nevent_L3T_Special2;}
      else if(stmp=="ARM1_L3T_PEDESTAL") {sin >> a1_nevent_L3T_Pedestal;}
      else if(stmp=="ARM1_L3T_L1T") {sin >> a1_nevent_L3T_L1T;} 
		else if(stmp=="ARM1_L3T_SHOWER_TS") {sin >> a1_nevent_L3T_Shower_TS;}
 		else if(stmp=="ARM1_L3T_SHOWER_TL") {sin >> a1_nevent_L3T_Shower_TL;}
		else if(stmp=="ARM1_L3T_STAR") {sin >> a1_nevent_L3T_STAR;}
		else if(stmp=="ARM1_STAR_ONLY") {sin >> a1_nevent_STAR_Only;}
      else if(stmp=="ARM1_SCL"){sin >> a1scl_nevent;}
      else if(stmp=="SLOWCONTROL"){sin >> sc_nevent;}
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
		  for(Int_t il=0;il<beam1_nbunches/3+1;il++){
			 getline(in,ss);
			 sin.clear();
			 sin.str(ss);
			 for(Int_t is=0;is<3;is++){
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
		  for(Int_t il=0;il<beam2_nbunches/3+1;il++){
			 getline(in,ss);
			 sin.clear();
			 sin.str(ss);
			 for(Int_t is=0;is<3;is++){
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
		  for(Int_t il=0;il<beam1_nbunches/3+1;il++){
			 getline(in,ss);
			 sin.clear();
			 sin.str(ss);
			 for(Int_t is=0;is<3;is++){
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
      //else if(stmp=="ANA_ARM1_NEVENT"){sin >> analysis_a1_nevent;}
      //else if(stmp=="ANA_ARM1_NEVENT_L1TA"){sin >> analysis_a1_nevent_L2TA;}
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
    cerr << "[RHICfRunInfo::Read] "
			<< "ERROR: Unknown format " << format
			<< endl;
    return ERROR;
  }  
}

Int_t  RHICfRunInfo::ReadFile(char* filename){
  // Read Information from the file.
  ifstream fin(filename);
  if(!fin){
    cerr << "[RHICfRunInfo::ReadFile] "
	 << "Cannot open " << filename << endl;
    return ERROR;
  } 
  return Read(fin);
}

void RHICfRunInfo::removespace(string& s){
  // Internal function 
  for(Int_t i=0;i<100;i++){
    if(s[0]==' '){s = s.substr(1);}
    else{break;}
  }
}

Int_t  RHICfRunInfo::IndexToBunch(Int_t beam,Int_t index){
  // Return Bunch Position by Bunch Index 
  // beam:   1 or 2
  // index:  0-nbunches
  
  if(beam==1) {return beam1_bunches[index];}
  if(beam==2) {return beam2_bunches[index];}
  return 0;
}

Int_t  RHICfRunInfo::BunchToIndex(Int_t beam,Int_t bunch){
  // Return Bunch Index by Bunch Position
  // beam:    1 or 2 
  // bunch:   1-3565
  
  if(buf_run!=run){
    // clear buffer
    for(Int_t i=0;i<buf_beam1_nbunches;i++){
      buf_beam1_bunches_index[buf_beam1_bunches[i]] = 0;
    }
    for(Int_t i=0;i<buf_beam2_nbunches;i++){
      buf_beam2_bunches_index[buf_beam2_bunches[i]] = 0;
    }
    // set buffer
    for(Int_t i=0;i<beam1_nbunches;i++){
      buf_beam1_bunches_index[beam1_bunches[i]] = i;
      buf_beam1_bunches[i] = beam1_bunches[i];
    }
    buf_beam1_nbunches = beam1_nbunches;
    for(Int_t i=0;i<beam2_nbunches;i++){
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

Int_t  RHICfRunInfo::CountBCtoBunch(Int_t beam, Int_t count){
  // Return Bunch Position by BC Count in GPIO_LHCFCOUNTER.
  // Just count - daq_beam1_scl_nbunch_offset.
  // beam:    1 or 2
  // count:   Beam1: A*Cal1::connter[23]
  //          Beam2: A*Cal1::counter[23]

  if(beam==1){return count - daq_beam1_scl_nbunch_offset;}
  if(beam==2){return count - daq_beam2_scl_nbunch_offset;}
  return 0;
}

Int_t  RHICfRunInfo::CountBCtoIndex(Int_t beam, Int_t count){
  // Return Bunch Index by BC Count in GPIO_LHCFCOUNTER.
  // beam:    1 or 2
  // count:   Beam1: A*Cal1::connter[23]
  //          Beam2: A*Cal1::counter[23]

  return BunchToIndex(beam, CountBCtoBunch(beam,count));
}

Int_t  RHICfRunInfo::GetBunchTagByIndex(Int_t beam, Int_t index){
  // Return Bunch Tag by Bunch Index
  // beam:    1 or 2
  // index:   0-nbunches
  
  if(beam==1 && index < NBUNCHES) return beam1_tag[index];
  if(beam==2 && index < NBUNCHES) return beam2_tag[index];
  return 0;
}

Int_t  RHICfRunInfo::GetBunchTag(Int_t beam,Int_t bunch){
  // Return Bunch Tag by Bunch Position.
  // beam:    1 or 2 
  // bunch:   1-3565

  return GetBunchTagByIndex(beam, BunchToIndex(beam,bunch));
}

Int_t  RHICfRunInfo::GetBunchTagByCountBC(Int_t beam, Int_t bunch){
  // Return Bunch Tag by BC Count in GPIO_LHCFCOUNTER.
  // beam:    1 or 2
  // count:   Beam1: A*Cal1::connter[23]
  //          Beam2: A*Cal1::counter[23]
  
  return GetBunchTagByIndex(beam, CountBCtoIndex(beam,bunch));
}

Int_t  RHICfRunInfo::CheckTime(Int_t t){
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

Int_t  RHICfRunInfo::CheckBunchQuality(A1Cal1* cal){
  // if bunch quality is good, return 1. if not, return 0.
  
  Int_t tag = GetBunchTag(cal);
  if(tag>0){
    return 1;
  }
  else{
    return 0;
  }
}

string RHICfRunInfo::CutdownGPIOSetup(char csetup[]){
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
// -------                 RHICfRunInfoTable                      ------
// --------------------------------------------------------------------


RHICfRunInfoTable::RHICfRunInfoTable(){
  Clear();
}

RHICfRunInfoTable::RHICfRunInfoTable(char* filename,Int_t format){
  Clear();
  ReadTable(filename);
}

RHICfRunInfoTable::~RHICfRunInfoTable(){;}

void RHICfRunInfoTable::Clear(){
  ioformat = -1;
  ninfo = 0;
  iinfo = 0;
  irun  = 0;
  for(Int_t i=0;i<(int)runinfo.size();i++){
    if(runinfo[i]) delete runinfo[i];
  }
  runinfo.clear();
}

RHICfRunInfo*  RHICfRunInfoTable::SetRun(Int_t run){
  // to save the search time.
  if(run==irun){
    return runinfo[iinfo];
  }
  
  // search in the table.
  for(Int_t i=0;i<ninfo;i++){
    if(runinfo[i]->run == run){
      iinfo = i;
      irun  = run;
      return runinfo[i]; 
    }
  }
  
  return NULL;
}

RHICfRunInfo*  RHICfRunInfoTable::GetIinfo(Int_t i){
  if(i<0 || i>=ninfo){ return NULL;}
  iinfo  = i;
  irun   = runinfo[i]->run;
  return runinfo[i];
}

RHICfRunInfo*  RHICfRunInfoTable::CreateInfo(){
  iinfo = ninfo;
  irun  = -1;
  runinfo.push_back(new RHICfRunInfo());
  ninfo++;
  return runinfo[iinfo];
}

Int_t RHICfRunInfoTable::ReadTable(char filename[256]){
  ifstream fin(filename);
  if(!fin){
    cerr << "[RHICfRunInfoTable::ReadTable] "
	 << "Cannot open " << filename << endl;
    return ERROR;
  }
  
  RHICfRunInfo* infodata = new RHICfRunInfo();
  for(Int_t i=0;i<5000;i++){ // for safty, the loop limit is 5000
    if(fin.eof()) break;
    if(infodata->Read(fin)==OK){
      runinfo.push_back(infodata);
      ninfo++;
      infodata =  new RHICfRunInfo();
    }
    else{
      break;
    }
  }
  fin.close();
  if(infodata->run < 0 ){ delete infodata;}

  return OK;
}

Int_t RHICfRunInfoTable::WriteTable(char* filename,Int_t format){
  ofstream fout(filename); 
  
  for(Int_t i=0;i<ninfo;i++){
    runinfo[i]->Print(fout,format);
    fout << endl;
  }
  fout.close();
  return OK;
}









#endif
