#ifndef __TRANSITIONFIT_H__
#define __TRANSITIONFIT_H__

//-----------------------------------------------------------------
//                          TransitionFit 
//-----------------------------------------------------------------

#include <TObject.h>
#include <TDirectory.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include "globaldef.h"
#include "A1Cal2.h"
#include "A2Cal2.h"

class TransitionFit{
 protected:
  static int    ncall;
  char          name[256];     
  char          title[256];
  TDirectory*   dir;          // directory
  TGraphErrors* g[2];         // [tower]
  TF1*          f[2];         // [tower]
  double        depth[16];    // for the conversion from #layer to pos[r.l.]
  double        pede[2];
  
 public:
  TransitionFit();
  TransitionFit(char tname[],char ttitle[]="");
  virtual ~TransitionFit(){;}
  
  void          Initialize();
  void          FillToGraph(int tower,A1Cal2* cal); 
  void          FillToGraph(int tower,A2Cal2* cal);    //  
  void          FillToGraphMod(int tower,A2Cal2* cal); // except layer 5
  int           Fit(int tower);
  int           Fit(int tower,A1Cal2 *cal);
  int           Fit(int tower,A2Cal2 *cal); 
  TGraphErrors* GetGraph(int tower){return g[tower];}
  TF1*          GetFunction(int tower){return f[tower];}
  double        GetParameter(int tower,int iparam);               // iparam<4
  int           SetParameter(int tower,int iparam,double value);  // iparam<4
  int           GetParameters(int tower, double *val);            // Get all(4) parameters and fill to the array
  int           SetParameters(int tower, double *val);            // Set all(4) parameters from the array.
  double        GetParError(int tower,int iparam);                // iparam<4
  double        GetChisquare(int tower){return f[tower]->GetChisquare();}
  double        GetShowerMax(int tower)
                    {return (GetParameter(tower,1)-1.)/GetParameter(tower,2);}
  void          GetFitRange(int tower,double &min,double &max);
  double        GetFitRangeMax(int tower);
  double        GetFitRangeMin(int tower);
  int           SetFitRange(int tower,double min=0,double max=45); // [r.l.]
  int           SetFitRangeLayer(int tower,int min=0,int max=15);
  double        GetBaseFluctuation(int tower){return pede[tower];}
  void          SetBaseFluctuation(int tower,double value){pede[tower]=value;} 
  
  double        Eval(int tower,double x){return f[tower]->Eval(x);}
  double        EvalAtLayer(int tower,int layer){return Eval(tower,depth[layer]);}
  int           Subtract(int tower, A1Cal2* cal);
  int           Subtract(int tower, A2Cal2* cal); 

  // public:
  double        FittingFunction(double* , double* );

  ClassDef(TransitionFit,1);   // Fit transition curves of the calorimeters. 
};

#endif

