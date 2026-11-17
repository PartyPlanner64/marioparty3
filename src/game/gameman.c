#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/saveEncode.h"
#include "game/wipe.h"
#include "game/camera.h"
#include "game/printfunc.h"
#include "game/messdata.h"
#include "ld_addrs.h"
#include "game/saveload.h"
#include "game/gamework.h"
#include "game/msm.h"
#include "game/hmfdraw.h"
#include "game/hmfspr.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "common_structs.h"
#include "game/gameman.h"
#include "game/malloc.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/object.h"
#include "game/util.h"
#include "gcc/memory.h"

extern str800D5298 HuAudSysConfig;
extern void *mainIntrQueue;
extern u8 GameManPadNoneF[];
extern u16 omHu3DGfxNum;
extern OSPiHandle *cartRomHandle;
extern Process *GameManDrawPrc;
extern u8 saveCommonBuf;
extern Process *GameManExecPrc;
extern u8 omHu3DBufNum;
extern s16 GameManFirstPad;
extern u16 omHu3DVtxNum;
extern u16 omHu3DMtxNum;
extern u16 HuAudFxParamNext;
extern u16 HuAudFxParam;

void GameManInitProc(void) {
    s32 i;

    HuPrcVSleep();
    SaveSchemeInit();

    CRot.x = 325.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;

    CZoom = 2250.0f;

    Center.x =
        Center.y =
            Center.z = CRot.y;

    for (i = 0; i < 4; i++) {
        CRotM[i].x = 325.0f;
        CRotM[i].y =
            CRotM[i].z = 0.0f;

        CZoomM[i] = 2250.0f;

        CenterM[i].x =
            CenterM[i].y =
                CenterM[i].z = 0.0f;
    }

    omHu3DBufNum = 3;
    omHu3DVtxNum = 0x1000;
    omHu3DGfxNum = 0x2004;
    omHu3DMtxNum = 0x180;
    WipeInit();
    Hu3DInit(&HuMemMemoryAllocPerm, &HuMemMemoryFreePerm, omHu3DVtxNum, omHu3DGfxNum, omHu3DMtxNum, omHu3DBufNum);
    Hu3DCamInit(1);
    pfInit();
    MessDataInit((u32)strings_japanese_ROM_START);
    GameManFirstPad = 0;

    do {
        if (CheckControllerRead(GameManFirstPad) != 0) {
            break;
        }
    } while (++GameManFirstPad < 4);

    if (GameManFirstPad == 4) {
        GameManFirstPad = -1;
    }

    HuMemHeapAllocPermSizeGet();
    GameManDrawPrc = HuPrcCreate(&GameManDrawProc, 0xF000, 0x3000, 0);
    HuPrcCreate(&GameManObjProc, 0x4000, 0x3000, 0);
    GameManExecPrc = HuPrcCreate(&GameManExecProc, 0x1000, 0x3000, 0);

    {
        s32 temp_s0 = SLInit();
        GWInit();
        GWGameStatReset();
        msmSysGetConfig(&HuAudSysConfig);
        SLCurBoxNoSet(0);
        SLLoadGameStat();
        if (temp_s0 != 0) {
            omOvlCallEx(slerror, 0, OM_OVL_STAT_BOARD | OM_OVL_STAT_GFXBUF3);
        } else {
            omOvlCallEx(ovl_boot, 0, OM_OVL_STAT_MG | OM_OVL_STAT_GFXBUF3);
        }
    }

    HuAudSysConfig.unk8 = audio_mbf0_ROM_START;
    HuAudSysConfig.unkC = audio_sbf0_ROM_START;
    HuAudFxParam = 0;
    HuAudFxParamNext = 0;
    HuAudSysConfig.unk0 = 0x70418F;
    HuAudSysConfig.unk10 = audio_fxd0_ROM_START;
    HuAudSysConfig.unk28 = 1;
    HuAudSysConfig.unk2C = 0;
    HuAudSysConfig.unk14 = (void *)0x802E0000;
    HuAudSysConfig.unk18 = 0x80000;
    HuAudSysConfig.unk5C = 0x6E;
    HuAudSysConfig.unk60 = 0;
    HuAudSysConfig.unk64 = 0;
    HuAudSysConfig.unk68 = cartRomHandle;
    HuAudSysConfig.unk44 = 0x3C;
    msmInit(&HuAudSysConfig);

    if ((saveCommonBuf & 1) != 0) {
        msmSysSetOutputMode(1);
    } else {
        msmSysSetOutputMode(0);
    }

    HuPrcKill(HuPrcCurrentGet());

    while (TRUE) {
        HuPrcVSleep();
    }
}

void GameManDrawProc(void) {
    while (TRUE) {
        HuPrcVSleep();
        Hu3DPreProc();
        Hu3DSprModelBufSwap();
        Hu3DScreenClear(0x2000000, 0x3D0800);
        pfClsScr();
    }
}

void GameManObjProc(void) {
    while (TRUE) {
        HuPrcVSleep();
        omMain();
    }
}

void GameManExecProc(void) {
    while (TRUE) {
        HuPrcVSleep();
        rand8();
        espMain(); // esprite
        Hu3DSprModelExec(2);
        Hu3DExec(&mainIntrQueue, 2); // hmfman
    }
}

/* Initialize Players */
void GameManPlayerInit(void) {
    s32 i;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        memset(&GwPlayer[i], 0, sizeof(GW_PLAYER));
        if (CheckControllerRead(i) != PAD_NOT_INSERTED) {
            GameManPadNoneF[i] = 0;
            GwPlayer[i].stat &= ~PLAYER_IS_CPU;
        } else {
            GameManPadNoneF[i] = 1;
            GwPlayer[i].stat |= PLAYER_IS_CPU;
        }

        GwPlayer[i].pad = i;
        GwPlayer[i].coin = 10;
        GwPlayer[i].gameCoin = 0;
        GwPlayer[i].group = i;
        GwPlayer[i].cpu_difficulty = 0;
        GwPlayer[i].star = 0;
        GwPlayer[i].gamePrize = 0;
        GwPlayer[i].stats.prize.bluePrize = 0;
        GwPlayer[i].stats.prize.redPrize = 0;
        GwPlayer[i].stats.prize.hatenaPrize = 0;
    }
}

/* Initialize Game Save Data */
void GWGameStatReset(void) {
    GameManPlayerInit();
    GWMgRecordSet(0, 0x64);
    GWMgRecordSet(1, 0xE10);
    GWMgRecordSet(2, 0xE10);
    GWMgRecordSet(3, 0x708);
    GWMgRecordSet(4, 0x3E8);
    GWMgRecordSet(5, 0xE10);
    GWMgRecordSet(6, 0xE10);
    GWMgRecordSet(7, 0xE10);
    GWMgRecordSet(8, 0);
    GWMgRecordSet(9, 0x1518);
}
