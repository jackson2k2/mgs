#include "gcl.h"
#include "kernel.h"

extern void DG_DequeuePrim_800182E0(int param_1);
extern void DG_FreePrim_8001BC04(int param_1);
extern void GM_Control_RemoveIfScriptData_800260CC(int param_1);
extern void sub_80034BF8(unsigned int *param_1);

void item_kill_80033F88(int param_1)
{
    char *pScript;
    int iVar2;

    GM_Control_RemoveIfScriptData_800260CC(param_1 + 0x20);
    sub_80034BF8((unsigned int *)(param_1 + 0x9c));
    iVar2 = *(int *)(param_1 + 0x15c);
    if (iVar2 != 0)
    {
        DG_DequeuePrim_800182E0(iVar2);
        DG_FreePrim_8001BC04(iVar2);
    }
    if ((*(char *)(param_1 + 0x112) == '\x02') &&
        (pScript = *(char **)(param_1 + 0x120),  pScript != NULL))
    {
        if ((int)pScript < 0)
        {
            GCL_ExecBlock_80020118(pScript, NULL);
        }
        else 
        {
            GCL_ExecProc_8001FF2C((unsigned int)pScript, NULL);
        }
    }
    return;
}
