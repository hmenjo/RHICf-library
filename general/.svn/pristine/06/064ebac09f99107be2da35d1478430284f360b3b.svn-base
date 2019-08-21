#ifndef __LHCFROOTFUNCTIONS_H__
#define __LHCFROOTFUNCTIONS_H__

#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include "A1Raw.h"
#include "A1Raw_pp2015.h"
#include "RHICfRaw_Op2017.h"
#include "A1Cal1.h"
#include "A1Cal2M.h"
#include "A1Phys.h"
#include "A2Raw.h"
#include "A2Raw_pPb2013.h"
#include "A2Raw_pp2015.h"
#include "A2Raw_pPb2016.h"
#include "A2Cal1.h"
#include "A2Cal2M.h"
#include "A2Phys.h"
#include "Rec0.h"
#include "SPSAdamo.h"
#include "SimIncidents.h"
#include "RHICfRaw_Op2017.h"
#include "RHICfScl_Op2017.h"

int LHCfEvents_Show(TTree *tree, int iev);  // Show the content list in EventID:iev of tree.
int LHCfEvents_Show(TFile *file, int iev);  // Show the content list in EventID:iev of file.
int LHCfEvents_Show(int iev);               // Show the contents list in EventID::iev of the opened tree.
TObject*         LHCfEvents_Get(TTree *tree, const int iev, const TString objname); // Get the object named as objname from EventID::iev of the LHCfEvents Tree:: tree.
TObject*         LHCfEvents_Get(const int iev, const TString dataname); // Get the object named as objname from EventID::iev of the opened tree.
A1Raw*           LHCfEvents_GetA1Raw(const int iev);
A1Raw_pp2015*    LHCfEvents_GetA1Raw_pp2015(const int iev);
RHICfRaw_Op2017* LHCfEvents_GetRHICfRaw_Op2017(const int iev);
A1Cal1*          LHCfEvents_GetA1Cal1(const int iev);
A1Cal2M*         LHCfEvents_GetA1Cal2(const int iev);
A1Phys*          LHCfEvents_GetA1Phys(const int iev);
Rec0*            LHCfEvents_GetA1Rec(const int iev);
SimIncidents*    LHCfEvents_GetA1Simin(const int iev);
A2Raw*           LHCfEvents_GetA2Raw(const int iev);
A2Raw_pPb2013*   LHCfEvents_GetA2Raw_pPb2013(const int iev);
A2Raw_pp2015*    LHCfEvents_GetA2Raw_pp2015(const int iev);
A2Raw_pPb2016*   LHCfEvents_GetA2Raw_pPb2016(const int iev);
A2Cal1*          LHCfEvents_GetA2Cal1(const int iev);
A2Cal2M*         LHCfEvents_GetA2Cal2(const int iev);
A2Phys*          LHCfEvents_GetA2Phys(const int iev);
Rec0*            LHCfEvents_GetA2Rec(const int iev);
SimIncidents*    LHCfEvents_GetA2Simin(const int iev);
SPSAdamo*        LHCfEvents_GetAdamo(const int iev);

void             LHCfEvents_GetA1Rec_Show(const int iev);
void             LHCfEvents_GetA2Rec_Show(const int iev);

// For RHICf
RHICfRaw_Op2017* LHCfEvents_GetRHICfRaw_Op2017(const int iev);
RHICfScl_Op2017* LHCfEvents_GetRHICfScl_Op2017(const int iev);

#endif
