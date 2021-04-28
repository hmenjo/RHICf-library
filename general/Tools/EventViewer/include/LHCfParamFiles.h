#ifndef __LHCFPARAMFILES_H__
#define __LHCFPARAMFILES_H__

class LHCfParamFiles {
 public:
  
  char file_a1scifipostable[256];
  char file_a1adcrange[256];
  char file_a1particledefine[256];
  char file_a1scifiparticledefine[256];
  char file_a1fcparticledefine[256];
  char file_a1pmtgaintable[256];
  char file_a1scifigaintable[256];
  char file_a1fcgaintable[256];
  char file_a1hvtable[256];
  char file_a1scificrosstalkx[256];
  char file_a1scificrosstalky[256];
  
  char file_a2adcrange[256];
  char file_a2particledefine[256];
  char file_a2siparticledefine[256]; 
  char file_a2fcparticledefine[256]; 
  char file_a2pmtgaintable[256];
  char file_a2sigaintable[256];
  char file_a2fcgaintable[256];
  char file_a2hvtable[256];
  
  
  char paramfile[256];
  
 public:
  LHCfParamFiles();
  LHCfParamFiles(char *filename); 
  ~LHCfParamFiles(); 

  void Initialize();
  int  Read(char *filename,int op=1);
  int  Write(char *filename="");

  void SetToDefault_Op2010();
  void SetToDefault_Op2013();
  void SetToDefault_Op2015();
  void SetToDefault_RHICf2017();
  
};

extern LHCfParamFiles *gLHCfParamFiles;

#endif
