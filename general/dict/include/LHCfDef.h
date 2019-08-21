#ifndef __LHCFDEF_H__

namespace LHCfDef {
  //  
  //  Definitions of General Numbers 
  // 
  
  enum Def_TOWER{
    SMALL_TOWER  = 0,
    LARGE_TOWER  = 1,
    N_TOWER      = 2
  };
  
  static const int N_SCIN_LAYER  = 16;
  static const int N_SI_LAYER    = 4;
  static const int N_SI_VIEW     = 2;
  static const int N_SI_SAMPLE   = 3;

} 

#endif /* __LHCFDEF_H__ */
