#include "unknown.h"

extern int HZD_sub_80029384( HZD_FLR* );

void sub_80029604(HZD_FLR *pHzdFlr)
{
    int  y, h;
    int *scratch;

    h = pHzdFlr->b1.h; // TODO: What's "h"?
    if ((h & 1) || HZD_sub_80029384(pHzdFlr))
    {
        if (h & 2)
        {
            y = pHzdFlr->b1.y;
        }
        else
        {
            y = HZD_sub_80029514(pHzdFlr);
        }
        scratch = (int *)0x1F800000;
        if (*(short *)0x1F800010 >= y)
        {
            if (scratch[17] < y)
            {
                scratch[17] = y;
                scratch[15] = (int)pHzdFlr;
            }
        }
        else if (y < scratch[18])
        {
            scratch[18] = y;
            scratch[16] = (int)pHzdFlr;
        }
    }
}
