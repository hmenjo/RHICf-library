#ifndef RHICfFlag_H
#define RHICfFlag_H

#include "/ccj/u/satoken/RHICf/convertor/lhcflib/include/A1Cal2.h"

//class A1cal2;
class TF1;
class RHICfFlag
{
    private:
        TF1 *f[2][16];
    
        //TRandom3 *rand;
        //srand((unsigned int)time(NULL));

    public:
        RHICfFlag();
        ~RHICfFlag();
        void Init();
        void SetFlag(A1Cal2 *a1cal2);
};

#endif
