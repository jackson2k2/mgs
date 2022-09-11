#ifndef _RMISSILE_H_
#define _RMISSILE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>

#include "Game/camera.h"
#include "Game/game.h"
#include "libdg/libdg.h"
#include "libgcl/gcl.h"
#include "libgv/libgv.h"

// nikita missile

typedef struct Actor_rmissile
{
    Actor           field_0_actor;
    GM_Control      field_20_ctrl;
    OBJECT          field_9C_kmd;
    MATRIX          field_C0_matrix;
    char            field_E0[32];
    SVECTOR         field_100_svector;
    SVECTOR         field_108_svector;
    char            field_110;
    char            field_111;
    char            field_112;
    char            field_113;
    char            field_114;
    char            field_115;
    char            field_116;
    char            field_117;
    short           field_118;
    short           field_11A;
    int             field_11C;
    char            field_120[72];
    short           field_168;
    char            field_16A[10];
    void           *field_174;
    char            field_178[4];
    GM_Camera       field_17C_camera;
    UnkCameraStruct field_1F8;
    CAMERA          field_228_camera[8];
    int             field_2C8;
    SVECTOR         field_2CC_svector;
    int             field_2D4;
    DG_OBJS        *field_2D8_objs;
    char            field_2DC[70];
    int             field_324;
} Actor_rmissile;

STATIC_ASSERT_SIZE(Actor_rmissile, 0x328);

void rmissile_8006B924(Actor_rmissile *pActor);
void rmissile_act_8006C5C4(Actor_rmissile *pActor);
void rmissile_kill_8006CB40(Actor_rmissile *pActor);

int  rmissile_loader_helper2_8006CC50(Actor_rmissile *pActor);
int  rmissile_loader_helper3_8006CBD8(Actor_rmissile *pActor, int whichSide);
void rmissile_loader_helper4_8006B800(Actor_rmissile *pActor);
void rmissile_loader_helper_8006CE54(Actor_rmissile *pActor);
int  rmissile_loader_8006CF44(Actor_rmissile *pActor, MATRIX *pMtx, int whichSide);

Actor_rmissile *NewRMissile_8006D124(MATRIX *pMtx, int whichSide);

#endif // _RMISSILE_H_
