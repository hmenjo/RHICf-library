{

  #include <string>
  string libbasedir;
  if(getenv("LHCF_LIBDIR")!=NULL){
    libbasedir = getenv("LHCF_LIBDIR");
  }
  else{
    libbasedir = "~/LHCf/Analysis/LHC/general";
  }

  gInterpreter->AddIncludePath((libbasedir+"/dict/include").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/dict/src").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/dict/lib").c_str());
  gInterpreter->AddIncludePath((libbasedir+"sc/include").c_str());
  gInterpreter->AddIncludePath((libbasedir+"sc/src").c_str());
  gInterpreter->AddIncludePath((libbasedir+"sc/lib").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/func/include").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/func/src").c_str());
  gInterpreter->AddIncludePath((libbasedir+"/func/lib").c_str());
 
}
