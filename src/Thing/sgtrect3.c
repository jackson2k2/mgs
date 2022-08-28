#include "sgtrect3.h"
#include "libdg/dgd.h"
#include <LIBGTE.H>
#include "psyq.h"
#include "Game/target.h"

// stinger missile first person HUD + stinger HUD?

extern DG_CHNL          DG_Chanls_800B1800[3];
extern char             byte_8009F5F8[];
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

void sgtrect3_act_helper_helper_80070040(void *ot, void *prim)
{
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000))
    {
        addPrim(ot, prim);
    }
}

void sgtrect3_act_helper_8007009C()
{
    DG_CHNL *chnl = &DG_Chanls_800B1800[1];
    DG_Clip_80017594(&chnl->field_5C_clip_rect, chnl->field_4C_clip_distance);
    SetRotMatrix_80093218(&chnl->field_10_transformation_matrix);
    SetTransMatrix_80093248(&chnl->field_10_transformation_matrix);
}

unsigned int sgtrect3_act_helper_helper_800700E0(GM_Target *target, DVECTOR *vector)
{
    int     vyAddend;
    int     vyDiff;
    DVECTOR screenCoordinates;
    SVECTOR vertexCoordinateVector;
    long    interpolatedValue;
    long    flag;

    vyAddend = (target->field_10_size.vy * 3) / 5;
    if (vyAddend < 500)
    {
        vyAddend = 500;
    }
    vertexCoordinateVector = target->field_8_vec;
    vertexCoordinateVector.vy += vyAddend;
    RotTransPers_80093478(&vertexCoordinateVector, (long *)&screenCoordinates, &interpolatedValue, &flag);
    vyDiff = vector->vy - screenCoordinates.vy;
    if (vyDiff < 0)
    {
        vyDiff = 0;
    }
    if (vyDiff >= 0xe1)
    {
        vyDiff = 0;
    }
    return vyDiff & 0xffff;
}

extern int dword_800ABA0C;

int sgtrect3_act_helper_800701A8(GM_Target *target)
{
    if (!((((target->field_0_flags & 0xfffe) != 0 && (target->field_4_map & dword_800ABA0C) != 0) &&
           target->field_2_side == 2) &&
          target->field_6_flags == 0 && ((target->field_0_flags & 0x220) == 0)))
    {
        return 0;
    }

    return 1;
}

extern int     dword_8009F46C;
extern int     dword_8009F490;
extern SVECTOR stru_800ABA10;
extern SVECTOR svector_8009F478;

void sgtrect3_act_helper_8007020C(Actor_sgtrect3 *sgtrect3, DVECTOR *outScreenCoordsArray, GM_Target **outTargetsArray,
                                  ushort *outResultsArray)
{
    int         downCount;
    GM_Target  *targets, *currentTarget;
    SVECTOR     vector, vector2;
    int         targetCount;
    DVECTOR     screenCoordinates;
    long        interpolatedValue;
    long        flag;
    int         result;
    int         shortestVecLen;
    int         vecLen;
    int         vx, vy;
    DVECTOR    *outScreenCoordsIter;
    GM_Target **outTargetsIter;
    ushort     *outResultsIter;

    targets = NULL;
    GM_Target_8002E374(&downCount, &targets);
    if (downCount != 1)
    {
        GM_Target *lastTarget;

        vector = (dword_8009F46C != 0) ? svector_8009F478 : stru_800ABA10;

        targetCount = 0;
        shortestVecLen = -1;
        lastTarget = NULL;
        outScreenCoordsIter = outScreenCoordsArray;
        outTargetsIter = outTargetsArray;
        outResultsIter = outResultsArray;

        while (--downCount >= 0)
        {
            currentTarget = targets;
            targets++;
            if (sgtrect3_act_helper_800701A8(currentTarget))
            {
                if (RotTransPers_80093478(&currentTarget->field_8_vec, (long *)&screenCoordinates, &interpolatedValue,
                                          &flag) > 0)
                {
                    vx = screenCoordinates.vx;
                    vy = screenCoordinates.vy;
                    result = sgtrect3_act_helper_helper_800700E0(currentTarget, &screenCoordinates) & 0xffff;
                    if (result != 0 && vx + result >= -160 && vx - result < 161 && vy + result >= -112 &&
                        vy - result < 113)
                    {
                        if (vx < result && -result < vx && vy < result && -result < vy)
                        {
                            vector2.vx = vx;
                            vector2.vy = vy;
                            vector2.vz = 0;

                            if (shortestVecLen < 0)
                            {
                                shortestVecLen = 60000;
                            }

                            GV_SubVec3_80016D40(&currentTarget->field_8_vec, &vector, &vector2);
                            vecLen = GV_VecLen3_80016D80(&vector2);
                            if (vecLen < shortestVecLen && vecLen >= 2401)
                            {
                                shortestVecLen = vecLen;
                                lastTarget = currentTarget;
                            }
                        }

                        targetCount++;
                        *outScreenCoordsIter++ = screenCoordinates;
                        *outResultsIter++ = result;
                        *outTargetsIter++ = currentTarget;
                        if (targetCount == 0x1f)
                        {
                            break;
                        }
                    }
                }
            }
        }

        if (dword_8009F490 == 0)
        {
            if (!lastTarget)
            {
                if (sgtrect3->field_30_target)
                {
                    sgtrect3->field_34_count++;
                    sgtrect3->field_38++;
                    if (sgtrect3->field_38 >= 24)
                    {
                        sgtrect3->field_34_count = 0;
                        sgtrect3->field_38 = 0;
                        sgtrect3->field_30_target = NULL;
                    }
                }
            }
            else
            {
                sgtrect3->field_38 = 0;
                if (sgtrect3->field_30_target == lastTarget)
                {
                    sgtrect3->field_34_count++;
                }
                else
                {
                    sgtrect3->field_34_count = 0;
                }
                sgtrect3->field_30_target = lastTarget;
            }
        }
        else if (sgtrect3->field_30_target)
        {
            if (!sgtrect3_act_helper_800701A8(sgtrect3->field_30_target))
            {
                sgtrect3->field_34_count = 0;
                sgtrect3->field_38 = 0;
                sgtrect3->field_30_target = NULL;
            }
            else
            {
                sgtrect3->field_34_count++;
                sgtrect3->field_38 = 24;
            }
        }

        sgtrect3->field_21AC_target_count = targetCount;
    }
}

extern int GV_Clock_800AB920;

void sgtrect3_act_helper_80070568(Actor_sgtrect3 *sgtrect3, void *ot, LINE_F3 *lineF3Arr)
{
    int count;
    int index;

    LINE_F4 *firstLineF4;
    LINE_F4 *secondLineF4;

    int   firstLineX_0_3;
    int   firstLineX_1_2;
    int   secondLineX_0_3;
    int   secondLineX_1_2;
    int   xOffset;
    short yCoord_0_1;
    short yCoord_2_3;

    int multiplicand;

    count = sgtrect3->field_34_count;
    if (0xc < count)
    {
        count = 0xc;
    }

    firstLineF4 = sgtrect3->field_1C3C_lines[GV_Clock_800AB920].field_0;
    secondLineF4 = firstLineF4 + 1;
    for (index = 0; index < count; index++)
    {
        firstLineX_1_2 = (lineF3Arr->x0 * index) / 12;
        secondLineX_1_2 = ((lineF3Arr->x1 - 319) * index) / 12 + 319;
        yCoord_0_1 = (((lineF3Arr->y0 - 29) * index) / 12) + 29;
        yCoord_2_3 = (((lineF3Arr->y2 - 210) * index) / 12) + 210;

        xOffset = ((secondLineX_1_2 - firstLineX_1_2) / 6);
        firstLineX_0_3 = firstLineX_1_2 + xOffset;
        secondLineX_0_3 = secondLineX_1_2 - xOffset;

        firstLineF4->x0 = firstLineF4->x3 = firstLineX_0_3;
        secondLineF4->x0 = secondLineF4->x3 = secondLineX_0_3;
        firstLineF4->x1 = firstLineF4->x2 = firstLineX_1_2;
        secondLineF4->x1 = secondLineF4->x2 = secondLineX_1_2;
        firstLineF4->y0 = firstLineF4->y1 = secondLineF4->y0 = secondLineF4->y1 = yCoord_0_1;
        firstLineF4->y2 = firstLineF4->y3 = secondLineF4->y2 = secondLineF4->y3 = yCoord_2_3;

        if (index != 11)
        {
            multiplicand = 16 - (sgtrect3->field_34_count - index);

            if (multiplicand < 0)
            {
                multiplicand = 0;
            }

            firstLineF4->r0 = (unsigned int)(sgtrect3->field_2C_r * multiplicand) >> 4;
            firstLineF4->g0 = (unsigned int)(sgtrect3->field_2D_g * multiplicand) >> 4;
            firstLineF4->b0 = (unsigned int)(sgtrect3->field_2E_b * multiplicand) >> 4;
            secondLineF4->r0 = firstLineF4->r0;
            secondLineF4->g0 = firstLineF4->g0;
            secondLineF4->b0 = firstLineF4->b0;
        }

        sgtrect3_act_helper_helper_80070040(ot, firstLineF4);
        sgtrect3_act_helper_helper_80070040(ot, secondLineF4);
        firstLineF4 += 2;
        secondLineF4 += 2;
    }

    sgtrect3_act_helper_helper_80070040(ot, &sgtrect3->field_23B8_prim[GV_Clock_800AB920]);
}

#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070820.s") // 656 bytes

void sgtrect3_act_helper_80070AB0(Actor_sgtrect3 *sgtrect3, DVECTOR *screenCoordsArray, GM_Target **inTargets,
                                  unsigned short *offsets)
{
    unsigned int  rgb;
    unsigned int *rgbFields;

    int            field_21B4;
    DVECTOR        screenCoords;
    int            targetCount;
    GM_Target     *field_30_target;
    GM_Target     *currentTarget;
    unsigned short currentOffset;

    DG_CHNL  *chnl;
    void     *ot;
    LINE_F3  *lineF3Arr;
    LINE_F2  *lineF2Arr;
    DR_TPAGE *tPageArr;

    rgbFields = (unsigned int *)&sgtrect3->field_28_r;
    targetCount = sgtrect3->field_21AC_target_count;
    field_21B4 = sgtrect3->field_21B4;
    lineF3Arr = sgtrect3->field_3C[GV_Clock_800AB920].field_0;
    lineF2Arr = sgtrect3->field_C3C[GV_Clock_800AB920].field_0;
    tPageArr = sgtrect3->field_21B8[GV_Clock_800AB920].field_0;
    chnl = &DG_Chanls_800B1800[1];
    ot = chnl[1].mOrderingTables[GV_Clock_800AB920]; // todo: fix when static inline DG_Chanl getter works.
    field_30_target = sgtrect3->field_30_target;

    for (targetCount--; targetCount >= 0; screenCoordsArray++, inTargets++, offsets++, targetCount--)
    {
        currentOffset = *offsets;
        currentTarget = *inTargets;

        if ((currentTarget != field_30_target) || (field_21B4 == 0))
        {
            rgb = rgbFields[0];
        }
        else if ((((unsigned short)(screenCoordsArray->vx + 160) < 321) && (-113 < screenCoordsArray->vy)) &&
                 (screenCoordsArray->vy < 113))
        {
            rgb = rgbFields[1];
        }
        else
        {
            continue;
        }

        screenCoords = *screenCoordsArray;
        screenCoords.vx += 160;
        screenCoords.vy += 112;
        sgtrect3_act_helper_80070820(ot, lineF3Arr, lineF2Arr, &screenCoords, currentOffset, rgb);
        sgtrect3_act_helper_helper_80070040(ot, tPageArr);

        if ((currentTarget == field_30_target) && (field_21B4 != 0))
        {
            sgtrect3_act_helper_80070568(sgtrect3, ot, lineF3Arr);
        }

        lineF3Arr += 2;
        lineF2Arr += 4;
        tPageArr++;
    }
}

extern int GV_PauseLevel_800AB928;

void sgtrect3_act_helper_80070CAC(Actor_sgtrect3 *sgtrect3)
{
    int     vecLen;
    SVECTOR vector2;
    SVECTOR vector;

    if (GV_PauseLevel_800AB928 != 0)
    {
        return;
    }
    if (sgtrect3->field_21B4 == 0)
    {
        sgtrect3->field_21B0++;
        if (!sgtrect3->field_30_target)
        {
            return;
        }

        vector = (dword_8009F46C != 0) ? svector_8009F478 : stru_800ABA10;

        GV_SubVec3_80016D40(&sgtrect3->field_30_target->field_8_vec, &vector, &vector2);
        vecLen = GV_VecLen3_80016D80(&vector2);
        vecLen = (vecLen * 3) / 2000;
        if (vecLen == 0)
        {
            vecLen = 1;
        }
        if (sgtrect3->field_21B0 % vecLen != 0)
        {
            return;
        }
    }
    else if (!sgtrect3->field_30_target)
    {
        return;
    }
    GM_Sound_80032968(0, 0x3f, 0x4f);
}

extern GM_Target *target_800BDF00;

void sgtrect3_act_80070E14(Actor_sgtrect3 *sgtrect3)
{
    DVECTOR    screenCoords[32];
    GM_Target *targets[32];
    ushort     offsets[32];

    if (sgtrect3->field_24 != *(short *)sgtrect3->field_20)
    {
        GV_DestroyActor_800151C8((Actor *)sgtrect3);
        return;
    }

    target_800BDF00 = NULL;
    sgtrect3_act_helper_8007009C();
    sgtrect3_act_helper_8007020C(sgtrect3, screenCoords, targets, offsets);
    sgtrect3_act_helper_80070AB0(sgtrect3, screenCoords, targets, offsets);
    sgtrect3_act_helper_80070CAC(sgtrect3);
    target_800BDF00 = sgtrect3->field_30_target;
}

void sgtrect3_kill_80070EC0(Actor_sgtrect3 *actor_sgtrect3)
{
    byte_8009F5F8[0] = 0;
}

#pragma INCLUDE_ASM("asm/Thing/sgtrect3_loader_helper_80070ECC.s") // 128 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_loader_80070F4C.s")        // 196 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_init_80071010.s")          // 268 bytes
