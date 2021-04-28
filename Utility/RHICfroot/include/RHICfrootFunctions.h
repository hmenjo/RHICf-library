#ifndef __RHICFROOTFUNCTIONS_H__
#define __RHICFROOTFUNCTIONS_H__

#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include "RHICfRaw_Op2017.h"
#include "A1Cal1.h"
#include "A1Cal2M.h"
#include "RHICfPhys.h"
#include "RHICfRec0.h"
#include "RHICfRec1.h"
#include "RHICfSimIncidents.h"

#include "RHICfScl_Op2017.h"
#include "A1CalEventHist.h"

int RHICfEvents_Show(TTree *tree, int iev);  // Show the content list in EventID:iev of tree.
int RHICfEvents_Show(TFile *file, int iev);  // Show the content list in EventID:iev of file.
int RHICfEvents_Show(int iev);               // Show the contents list in EventID::iev of the opened tree.
TObject*           RHICfEvents_Get(TTree *tree, const int iev, const TString objname); // Get the object named as objname from EventID::iev of the LHCfEvents Tree:: tree.
TObject*           RHICfEvents_Get(const int iev, const TString dataname); // Get the object named as objname from EventID::iev of the opened tree.
RHICfRaw_Op2017*   RHICfEvents_GetRaw(const int iev);
A1Cal1*            RHICfEvents_GetCal1(const int iev);
A1Cal2M*           RHICfEvents_GetCal2(const int iev);
RHICfPhys*         RHICfEvents_GetPhys(const int iev);
RHICfRec0*         RHICfEvents_GetRec(const int iev);
RHICfSimIncidents* RHICfEvents_GetSimin(const int iev);

void               RHICfEvents_GetRec_Show(const int iev);

// Added on 27 Aug 2020
A1CalEventHist*    RHICfEventView(A1Cal2 *cal, TString op=""); // op: "Wait"=> c1->WaitePrimitive()
A1CalEventHist*    RHICfEventView_Cal2(int iev, TString op=""); // op: "Wait"=> c1->WaitePrimitive()

#endif
