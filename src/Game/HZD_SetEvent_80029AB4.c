#include "GM_Control.h"

void HZD_SetEvent_80029AB4(Res_Control_unknown *param_1, int param_2)
{
    int    iVar1;
    short *psVar2;

    param_1->field_0_scriptData_orHashedName = (short)param_2;
    param_1->field_6_count = 0;
    param_1->field_4_trigger_Hash_Name_or_camera_w = 0;
    param_1->field_2_name_hash = 0;

    // TODO: simplify loop
    psVar2 = &param_1->field_8;
    iVar1 = 6;
    do
    {
        *psVar2 = 0;
        iVar1--;
        psVar2++;
    } while (iVar1 > 0);

    param_1->field_14_vec.vz = 0;
    param_1->field_14_vec.vy = 0;
    param_1->field_14_vec.vx = 0;
}
