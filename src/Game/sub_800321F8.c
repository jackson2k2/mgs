#include "Game/camera.h"

extern SVECTOR          svector_800ABA10;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

int sub_800321F8(SVECTOR *pos, int param_2, DVECTOR *out)
{
    int     vecdir;
    int     diffvec;
    int     vy;
    SVECTOR vec;

    diffvec = GV_DiffVec3_80016E84(&svector_800ABA10, pos) - param_2;
    if (diffvec < 0)
    {
        diffvec = 0;
        vy = 63;
    }
    else
    {
        vy = 63;
    }

    if (diffvec >= 1000)
    {
        if (diffvec < 7300)
        {
            vy = 63 - (diffvec - 1000) / 100;
        }
        else
        {
            diffvec = 7300;
            vy = 0;
        }
    }

    GV_SubVec3_80016D40(pos, &svector_800ABA10, &vec);
    vecdir = GV_VecDir2_80016EF8(&vec) + 1024;

    out->vx = sub_800321AC(vecdir - gUnkCameraStruct2_800B7868.field_10.vy, diffvec * 31 / 7300);
    out->vy = vy;

    if (vy <= 0)
    {
        return -1;
    }
    return 0;
}
