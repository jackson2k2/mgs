#include "linker.h"
#include "mts/mts_new.h"
#include "unknown.h"
#include "psyq.h"
#include "libfs.h"

void FS_StartDaemon_80014A7C(void)
{
    // CPU exception if >= 2MB ram range is used since retail consoles have 2 MB and dev have 8 MB.
    SetMem_8009944C(2);
    CDFS_Init_80021EC4();       // init cd and the likes
    sio_output_stop_8008C5B0(); // empty func
}

void FS_CdStageProgBinFix_80014AAC()
{
}

int CdReadCallback_80014AB4()
{
    return 0;
}

void CdReadMode_80014ABC()
{
}

void DsReadyCallback_80014AC4(int a1)
{
    mts_printf_8008BBA0("DsReadyCallback %x\n", a1);
}

void DsDataCallback_80014AEC(int a1)
{
    mts_printf_8008BBA0("DsDataCallback %x\n", a1);
}

int PCinit_80014B14(void)
{
    return -1;
}

int PCopen_80014B1C(char *name, int flags, int perms)
{
    return 0;
}

int PCread_80014B24(int fd, char *buff, int len)
{
    return 0;
}

int PCclose_80014B2C(int fd)
{
    return 0;
}
