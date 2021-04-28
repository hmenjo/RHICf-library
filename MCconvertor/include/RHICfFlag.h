#ifndef RHICfFlag_H
#define RHICfFlag_H

#include <TF1.h>
#include <A1Cal2.h>

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
