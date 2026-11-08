#define NO_EXTERN_VARIABLES
#include "ultra64.h"
#include "macros.h"
#include "game/board.h"
#include "game/camera.h"
#include "game/effect.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/graphics.h"
#include "game/hmfcoll.h"
#include "game/hmfdraw.h"
#include "game/hmflight.h"
#include "game/hmfshape.h"
#include "game/printfunc.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "PR/osint.h"
#include "2.0L/io/controller.h"
#include "2.0L/os/initialize.h"
#include "PR/rdb.h"

// Main segment COMMON symbols, in their original allocation order.
//
// GCC emits globals in the order they are first declared, so the headers hide
// their extern variable declarations when NO_EXTERN_VARIABLES is defined. Do not
// include headers here that declare these variables without that guard.
//
// The comment on each variable lists the files that reference it, i.e. the
// likely original definer. Labels inside a variable are aliased in
// undefined_syms.txt. "unreferenced" storage has no known symbol.

u8 D_800C9510_main[0xC] BSS; // unreferenced
u16 D_800C951C_main BSS; // esprite.c
u16 D_800C9520_main[4] BSS; // input.c, pause.c, window.c
u16 D_800C9528_main BSS; // hmfdraw.c
u32 D_800C952C_main BSS; // hmfdraw.c
HuSprite_Unk84_Struct *D_800C9530_main[256] BSS; // esprite.c, sprman.c
s16 D_800C9930_main BSS; // overlays only
s16 D_800C9932_main BSS; // camera.c, hmfdraw.c, hmfman.c
HuSprGrp *HuSprGrpLast BSS; // sprman.c
f32 D_800C9938_main BSS; // overlays only
s16 D_800C993C_main BSS; // mallocblock.c
s32 D_800C9940_main BSS; // hmfcoll.c, hmfdraw.c, hmfman.c
u16 D_800C9944_main BSS; // saveEncode.c, saveload.c
void *__osRdb_DbgRead_Buf BSS; // 2.0L/rmon/rmonsio.c
void *D_800C9950_main[2000] ALIGNED(8) BSS; // mallocblock.c
f32 D_800CB890_main BSS; // objmain.c, objsysobj.c
s16 D_800CB894_main BSS; // overlays only
u32 __osBaseCounter ALIGNED(8) BSS; // 2.0L/io/vimgr.c, 2.0L/os/gettime.c, 2.0L/os/timerintr.c
void *currFrameBuffer BSS; // graphics.c, wipe.c
u16 D_800CB8A0_main BSS; // sprman.c
s32 fontcolor BSS; // lightdebug.c, objmain.c, printfunc.c
Light *D_800CB8A8_main BSS; // hmfdraw.c, hmflight.c
u8 D_800CB8AC_main BSS; // msm.c, n_synsetpan.c, n_synstartvoiceparam.c
s16 ringBufferIndex BSS; // graphics.c
u8 D_800CB8B0_main[8] BSS; // hmfdraw.c, hmfload.c; contains D_800CB8B1_main
u64 *gThreadOutStackSize BSS; // graphics.c, profiler.c
u16 D_800CB8BC_main BSS; // esprite.c
HmfData D_800CB8C0_main BSS; // hmfman.c
u8 D_800CB99C_main BSS; // pause.c, window.c
u32 __kmc_pt_mode BSS; // 2.0L/os/initialize_kmc.c, 2.0L/os/initialize_msp.c
s16 D_800CB9A4_main[4] BSS; // audio.c
u8 D_800CB9B0_main[0x1B0] ALIGNED(8) BSS; // unreferenced
HmfModelEntry *D_800CBB60_main BSS; // hmfspr.c
u16 D_800CBB64_main[14] BSS; // pad.c, audio.c, hmfman.c, ...; contains D_800CBB66_main, D_800CBB6E_main, D_800CBB72_main
graphicsMessage gMesgRingBuffer[0x40] BSS; // graphics.c
Vtx *D_800CC080_main[8] BSS; // hmfspr.c
HuSprGrp *HuSprGrpFirst BSS; // sprman.c
s32 D_800CC0A4_main BSS; // graphics.c
u8 D_800CC0A8_main BSS; // hmfdraw.c, hmfman.c
HmfData_Unk84_Entry *D_800CC0AC_main BSS; // hmfdraw.c
u32 __osProfileOverflowBin BSS; // 2.0L/os/timerintr.c
s16 D_800CC0B4_main BSS; // hmfdraw.c, hmflight.c
s16 D_800CC0B6_main BSS; // hmfdraw.c, hmfman.c
s16 D_800CC0B8_main BSS; // overlays only
u8 wipeMode BSS; // wipe.c
HmfDrawObject *D_800CC0BC_main BSS; // hmfdraw.c, hmfman.c
u8 D_800CC0C0_main BSS; // overlays only
GW_COMMON GwCommon ALIGNED(8) BSS; // gamework.c, saveload.c, window.c
u8 D_800CC16C_main[0x204] BSS; // unreferenced
s32 D_800CC370_main BSS; // objmain.c
s16 kakusiMasuItemHis[10] ALIGNED(8) BSS; // overlays only
Gfx gTaskDataPointers[2] BSS; // graphics.c
OSMesgQueue D_800CC3A0_main BSS; // audiomgr.c, nnsched.c
void (*D_800CC3B8_main)(omObjData *) BSS; // objmain.c
s16 gSwapChainMesgTotal BSS; // graphics.c
OSMesgQueue D_800CC3C0_main BSS; // graphics.c, nnsched.c, profiler.c
void (*D_800CC3D8_main[1])(Gfx **, HuCamMtxs *, s16) BSS; // hmfman.c
u8 D_800CC3DC_main[0x4] BSS; // overlays only
u8 D_800CC3E0_main[4] BSS; // overlays only
s16 D_800CC3E4_main BSS; // unreferenced
u16 D_800CC3E6_main BSS; // sprman.c
u8 D_800CC3E8_main[0x8] BSS; // unreferenced
OSPifRam __osContPifRam BSS; // 2.0L/io/contreaddata.c, 2.0L/io/controller.c
s16 omobjlast BSS; // objmain.c
s16 D_800CC432_main BSS; // unreferenced
u8 D_800CC434_main[0x4] BSS; // unreferenced
s16 D_800CC438_main BSS; // overlays only
s16 D_800CC43A_main BSS; // unreferenced
u32 D_800CC43C_main BSS; // 2.0L/os/initrdb.c, 2.0L/os/rdbsend.c
Unk_D_800CC440 D_800CC440_main[4] BSS; // lightdebug.c, printfunc.c
UnkData_CD0A0 D_800CC4A0_main BSS; // overlays only
s16 kakusiMasuItem BSS; // overlays only
OSThread swapChainThread BSS; // graphics.c
u16 D_800CC698_main BSS; // overlays only
TextWindow *winData BSS; // window.c, pause.c
u16 strlinecnt BSS; // printfunc.c
s16 D_800CC6A2_main BSS; // unreferenced
u8 D_800CC6A4_main[0x80C] BSS; // unreferenced
OSPiHandle __Dom2SpeedParam BSS; // 2.0L/io/pimgr.c, 2.0L/os/initialize.c
OSProf *__osProfileList BSS; // 2.0L/os/timerintr.c
s16 MTXBufNum BSS; // hmfcoll.c, hmfdraw.c
s32 D_800CCF2C_main BSS; // nnsched.c
Gfx *D_800CCF30_main BSS; // sprman.c, sprput.c
void *D_800CCF38_main ALIGNED(8) BSS; // gameman.c, main.c
u8 D_800CCF3C_main[0x14] BSS; // unreferenced
s16 ommaxobjs BSS; // objmain.c
u8 D_800CCF52_main BSS; // main.c, objmain.c
u16 D_800CCF54_main BSS; // saveEncode.c, saveload.c
HmfModelData_Unk64_Unk8C_Struct *D_800CCF58_main BSS; // hmfdraw.c, hmfman.c, hmfspr.c
OSMesgQueue D_800CCF60_main ALIGNED(8) BSS; // main.c
u8 D_800CCF78_main[4] BSS; // gameman.c
u16 D_800CCF7C_main[4] BSS; // audio.c, objmain.c
u8 wipeStat BSS; // wipe.c
u8 D_800CCF85_main BSS; // hmfanim.c, hmfload.c
u32 D_800CCF88_main BSS; // hmfdraw.c
s16 omnumobjs BSS; // objmain.c
ISVDbg *gISVDbgPrnAdrs BSS; // 2.0L/os/initialize_isv.c
f32 D_800CCF98_main[4] ALIGNED(8) BSS; // objmain.c, objsysobj.c
void *D_800CCFA8_main BSS; // rom.c
u8 D_800CCFAC_main[0xA4] BSS; // unreferenced
u16 D_800CD050_main BSS; // objmain.c
GW_SYSTEM GwSystem ALIGNED(8) BSS; // gamemes.c, gamework.c, objmain.c, ...
u8 gEncodedSaveBuffer[224] BSS; // saveEncode.c, saveload.c
__osExceptionVector D_800CD1A0_main BSS; // 2.0L/os/initialize_isv.c
s16 D_800CD1B0_main BSS; // hmfspr.c
Mtx *D_800CD1B8_main[8] ALIGNED(8) BSS; // hmfdraw.c
u32 __osViIntrCount BSS; // 2.0L/io/vimgr.c, 2.0L/os/timerintr.c
ESPRITE *D_800CD1DC_main BSS; // esprite.c
omObjGroup omgroup[10] BSS; // objmain.c
u8 D_800CD280_main BSS; // hmfman.c, objmain.c
f32 CZoomM[6] ALIGNED(8) BSS; // gameman.c, objsysobj.c
Unk800CD2A0 D_800CD2A0_main BSS; // hmfdraw.c
u8 cancelCRF BSS; // window.c
Vec D_800CD2A8_main[4] BSS; // objsysobj.c
u8 D_800CD2D8_main[0x18] BSS; // unreferenced
u32 __osThprofCount BSS; // 2.0L/debug/threadprofile.c
u16 D_800CD2F4_main BSS; // gameman.c, objmain.c
u16 D_800CD2F6_main BSS; // hmfman.c
HmfPaletteData *D_800CD2F8_main BSS; // hmfanim.c
u32 D_800CD2FC_main BSS; // hmfdraw.c
GAMEMES gMesData[GMES_MAX] BSS; // gamemes.c; contains D_800CD360_main, D_800CD364_main
u8 D_800CD6A0_main[0x4] BSS; // unreferenced
u16 D_800CD6A4_main BSS; // saveEncode.c, saveload.c
u8 D_800CD6A6_main BSS; // hmfdraw.c, hmfman.c, hmfparticle.c
u8 D_800CD6A7_main BSS; // unreferenced
u8 D_800CD6A8_main[0x8] BSS; // unreferenced
HmfDrawFace D_800CD6B0_main[48] BSS; // hmfdraw.c
u8 D_800CDA70_main[0x4] BSS; // unreferenced
u8 D_800CDA74_main BSS; // wipe.c
s16 D_800CDA76_main BSS; // hmfdraw.c
u32 __osRdb_Read_Data_Ct BSS; // 2.0L/debug/readhost.c
s16 D_800CDA7C_main[4] BSS; // audio.c, input.c, pad.c
u8 D_800CDA84_main BSS; // hmfdraw.c, hmfman.c
s16 D_800CDA86_main BSS; // hmfdraw.c
WindowInputRecord winComKeyBuf[WINDOW_INPUT_RECORDS_MAX] BSS; // window.c
s16 D_800CDBC8_main BSS; // audio.c, objmain.c, objsysobj.c
UnkDiceRelated D_800CDBD0_main[5] ALIGNED(8) BSS; // overlays only
u16 saftyFrameF BSS; // printfunc.c
u16 D_800CDD4E_main BSS; // hmfspr.c
OSPiHandle *D_800CDD50_main BSS; // gameman.c, rom.c
Vtx *D_800CDD54_main BSS; // hmfspr.c
s16 mbCameraBtnF BSS; // overlays only
s16 D_800CDD5A_main BSS; // hmfdraw.c
u16 D_800CDD5C_main[4] BSS; // audio.c, objmain.c
s16 D_800CDD64_main BSS; // overlays only
s16 D_800CDD66_main BSS; // hmfdraw.c
s16 D_800CDD68_main BSS; // unreferenced
s16 D_800CDD6A_main BSS; // hmfdraw.c, hmfload.c, hmfman.c, ...
HuSprGrp *HuSprGrpData[HUSPR_GRP_MAX] ALIGNED(8) BSS; // sprman.c
s16 D_800CE170_main BSS; // hmfdraw.c
u32 D_800CE174_main BSS; // 2.0L/os/initrdb.c, 2.0L/os/rdbsend.c
s32 D_800CE178_main BSS; // camsetup.c, objsysobj.c
f32 D_800CE17C_main[5] BSS; // objsysobj.c
s16 D_800CE190_main BSS; // objmain.c
omObjData *D_800CE194_main BSS; // objsysobj.c
s16 D_800CE198_main BSS; // overlays only
u8 D_800CE19A_main BSS; // hmfdraw.c, hmfman.c
OSMesgQueue D_800CE1A0_main ALIGNED(8) BSS; // eeprom.c, pad.c, siman.c, ...
void *D_800CE1B8_main[3] BSS; // sprman.c
s16 kakusiMasuCoin BSS; // overlays only
u8 D_800CE1C6_main BSS; // hmfdraw.c, hmfman.c
f32 CZoom BSS; // gameman.c, objsysobj.c
s16 D_800CE1CC_main BSS; // unreferenced
s16 D_800CE1CE_main BSS; // hmfdraw.c
s16 D_800CE1D0_main BSS; // overlays only
UnkLightData *D_800CE1D4_main BSS; // hmfdraw.c, hmflight.c, lightdebug.c
u8 D_800CE1D8_main[0x4] BSS; // unreferenced
Unk_D_800CE1DC D_800CE1DC_main BSS; // objmain.c, printfunc.c
s16 kakusiMasuCoinHis[10] BSS; // overlays only
u64 *gThreadYieldStack BSS; // graphics.c, profiler.c
s32 omovl BSS; // objmain.c, gamemes.c; contains D_800CE202_main
u8 __osMaxControllers BSS; // 2.0L/io/contreaddata.c, 2.0L/io/controller.c, 2.0L/io/contsetch.c, ...
s16 D_800CE206 BSS; // overlays only
u16 D_800CE208 BSS; // overlays only
HmfLookAtData *D_800CE20C_main BSS; // hmfdraw.c
u32 D_800CE210_main BSS; // nnsched.c
u16 D_800CE214_main BSS; // objmain.c, pause.c
s16 D_800CE218_main[64] BSS; // audio.c
Process *pauseProc BSS; // pause.c
s16 D_800CE29C_main BSS; // overlays only
s16 D_800CE29E_main BSS; // unreferenced
u8 D_800CE2A0_main[0x14] BSS; // unreferenced
s16 D_800CE2B4_main BSS; // hmfdraw.c
OSTime __osCurrentTime BSS; // 2.0L/io/vimgr.c, 2.0L/os/gettime.c, 2.0L/os/timerintr.c
u16 D_800CE2C0_main BSS; // saveEncode.c, saveload.c
void *D_800CE2C4_main BSS; // window.c
u32 D_800CE2C8_main BSS; // nnsched.c
s8 D_800CE2D0_main[4][8] ALIGNED(8) BSS; // pad.c
u32 D_800CE2F0_main BSS; // hmfdraw.c; declared u64 in hmfdraw.c
s32 D_800CE2F4_main BSS; // hmfdraw.c
u8 D_800CE2F8_main[0x2008] BSS; // unreferenced
u64 *gThread3Stack BSS; // boot.c, graphics.c, profiler.c
GW_STORY GwStory ALIGNED(8) BSS; // gamework.c, saveload.c
s16 mbItemBtnF BSS; // overlays only
s16 D_800D037E_main BSS; // audio.c, objsysobj.c
OSPiHandle __CartRomHandle BSS; // 2.0L/io/cartrominit.c
HuMallocHeader *gLastMallocBlock BSS; // mallocblock.c
HmfModel *HmfModelData BSS; // aura.c, camera.c, effect.c, ...
u16 D_800D03FC BSS; // overlays only
s16 D_800D03FE_main BSS; // overlays only; accessed as s16[4] in mgmode
u8 D_800D0400_main[0x8] BSS; // unreferenced
u8 D_800D0408_main[0x4] BSS; // unreferenced
Process *winProc BSS; // window.c
u16 empstrline BSS; // printfunc.c
s16 D_800D0412_main BSS; // unreferenced
u8 D_800D0414_main[0x4] BSS; // unreferenced
s16 D_800D0418_main[8] BSS; // overlays only
u8 D_800D0428_main[0x18] BSS; // unreferenced
HmfData_Unk84_Entry *D_800D0440_main BSS; // hmfdraw.c
HuCamMtxs *D_800D0444_main BSS; // camera.c, hmflight.c, hmfman.c
Process *D_800D0448_main BSS; // gameman.c
u8 D_800D0450_main[24] ALIGNED(8) BSS; // eeprom.c, saveload.c
s16 D_800D0468_main BSS; // sprman.c
OSPifRam __osEepPifRam ALIGNED(8) BSS; // 2.0L/io/conteepread.c, 2.0L/io/conteepwrite.c
u16 D_800D04B0_main BSS; // saveEncode.c, saveload.c
s16 *D_800D04B4_main BSS; // hmfspr.c
f32 D_800D04B8_main[6][6] BSS; // camsetup.c, objsysobj.c
u64 *gThreadOutStack BSS; // graphics.c, profiler.c
omObjData *D_800D054C_main BSS; // objmain.c
OSMesgQueue __osPiAccessQueue BSS; // 2.0L/io/piacs.c, 2.0L/io/pimgr.c
s16 D_800D0568_main[20] BSS; // pad.c; contains D_800D056A_main
s16 D_800D0590_main[4] BSS; // input.c, lightdebug.c, window.c
u8 D_800D0598_main BSS; // wipe.c
u8 D_800D0599_main BSS; // hmfdraw.c, hmfman.c
u16 D_800D05A0_main[4][128] ALIGNED(8) BSS; // hmfman.c
u8 D_800D09A0_main[0x8] BSS; // unreferenced
SaveCommonBuf D_800D09A8_main BSS; // audio.c, gameman.c, saveload.c; contains D_800D09A9_main
OSPiHandle __Dom1SpeedParam BSS; // 2.0L/io/pimgr.c, 2.0L/os/initialize.c
s32 *gUCodeAddresses BSS; // graphics.c, profiler.c
s16 D_800D0A38_main BSS; // pause.c
u16 D_800D0A3A_main BSS; // objmain.c
f32 wipeDuration BSS; // wipe.c
u8 D_800D0A40_main[0x4] BSS; // unreferenced
s16 D_800D0A44_main BSS; // hmfdraw.c
s16 D_800D0A46_main BSS; // unreferenced
u8 D_800D0A48_main[0x8] BSS; // unreferenced
HuSprAnmDesc *D_800D0A50_main[0x100] BSS; // sprman.c
u8 D_800D0E50_main[672] BSS; // eeprom.c, saveload.c
u8 D_800D10F0_main BSS; // hmfdraw.c
s16 D_800D10F2_main BSS; // sprman.c
HuCamera *D_800D10F4_main BSS; // camera.c, hmfcoll.c, hmfdraw.c, ...
s16 D_800D10F8_main[4] BSS; // input.c
u16 D_800D1100_main BSS; // gamemes.c, objmain.c
CollisionGrid *D_800D1104_main BSS; // hmfcoll.c
GW_PLAYER GwPlayer[5] BSS; // audio.c, gameman.c, objmain.c, ...
OSMesgQueue D_800D1220_main BSS; // siman.c
HuMallocHeader *gLastFreedBlock BSS; // mallocblock.c
s8 D_800D123C_main[4] BSS; // audio.c
s32 mbGameMode BSS; // overlays only
u16 D_800D1244_main[4] BSS; // audio.c, lightdebug.c, pad.c
s16 D_800D124C_main BSS; // overlays only
s16 kakusiMasuStar BSS; // overlays only
u8 __rmonUtilityBuffer[256] BSS; // 2.0L/rmon/rmonmem.c, 2.0L/rmon/rmontask.c
u16 D_800D1350_main[4] BSS; // input.c
HuMtx4F *D_800D1358_main BSS; // hmfspr.c
HuFreeFunc gFreeFunc BSS; // hmfman.c, mallocblock.c
Gfx *D_800D1360[8] BSS; // hmfspr.c
s16 D_800D1380_main[5] BSS; // pad.c; contains D_800D1382_main
s16 D_800D138A_main BSS; // hmfdraw.c, hmfspr.c
Vec CRot BSS; // gameman.c, objsysobj.c
str800D5298 D_800D1398_main BSS; // objsysobj.c; contains D_800D13EE_main
HmfLookAtData D_800D1408_main[8] BSS; // hmfdraw.c
s16 D_800D1708_main BSS; // overlays only
Process *D_800D170C_main BSS; // gameman.c
s8 D_800D1710_main BSS; // gameman.c, objmain.c
HmfAnim *D_800D1714_main BSS; // hmfanim.c, hmfspr.c
u8 D_800D1718_main[0x8] BSS; // unreferenced
u8 rmonRdbReadBuf[2048] BSS; // 2.0L/rmon/rmonsio.c
u8 D_800D1F20_main[4] BSS; // overlays only
u32 __osThprofLastTimer BSS; // 2.0L/debug/threadprofile.c
s16 D_800D1F28_main BSS; // unreferenced
u8 D_800D1F2A_main BSS; // hmfdraw.c
Gfx *D_800D1F30_main ALIGNED(8) BSS; // hmfspr.c
u8 comKeyIdx BSS; // window.c
Gfx *D_800D1F38_main[8] BSS; // hmfdraw.c
u8 __osContLastCmd BSS; // 2.0L/io/conteepread.c, 2.0L/io/conteepwrite.c, 2.0L/io/contramread.c, ...
WipeTexture D_800D1F5C_main BSS; // wipe.c; contains D_800D1F60_main
u32 leoComuBuffAdd BSS; // 2.0L/os/initialize_isv.c
Mtx *MTXBuf BSS; // hmfcoll.c, hmfdraw.c
OSMesg __osEepromTimerMsg BSS; // 2.0L/io/conteeplongwrite.c, 2.0L/io/controller.c
s32 D_800D1F70_main BSS; // hmfman.c, main.c
s32 D_800D1F74_main BSS; // hmfdraw.c
s16 D_800D1F78_main BSS; // hmfdraw.c
s16 kakusiMasuItemHisIdx BSS; // overlays only
u8 *D_800D1F80_main[8] ALIGNED(8) BSS; // wipe.c
u8 D_800D1FA0_main BSS; // objmain.c
s16 gNumOfControllers BSS; // pad.c, util.c
OSTimer __osBaseTimer BSS; // 2.0L/os/timerintr.c
s32 D_800D1FC8_main BSS; // 2.0L/os/initrdb.c
HmfData_Unk84_Entry2 *D_800D1FCC_main BSS; // hmfanim.c, hmfman.c
u32 D_800D1FD0_main BSS; // hmfdraw.c; declared u64 in hmfdraw.c
s32 D_800D1FD4_main BSS; // hmfdraw.c
s16 D_800D1FD8_main BSS; // hmfdraw.c
s32 D_800D1FDC_main BSS; // sprman.c
s16 D_800D1FE0_main BSS; // unreferenced
s16 D_800D1FE2_main BSS; // hmfdraw.c
WindowFont *D_800D1FE4_main BSS; // window.c
s32 D_800D1FE8_main BSS; // hmfman.c
s16 kakusiMasuCoinHisIdx BSS; // overlays only
u16 D_800D1FEE_main BSS; // hmfdraw.c
u8 D_800D1FF0_main BSS; // camera.c, hmfdraw.c, hmfman.c, ...
Gfx *gMainGfxPos BSS; // gamemes.c, hmfanim.c, hmfdraw.c, ...
Gfx *D_800D1FF8_main BSS; // hmfdraw.c, hmfman.c
u32 D_800D1FFC_main BSS; // hmfdraw.c
u32 __osTimerCounter BSS; // 2.0L/os/settimer.c, 2.0L/os/timerintr.c
s32 __osEepromRead16K BSS; // 2.0L/io/conteepprobe.c, 2.0L/io/conteepread.c, 2.0L/io/conteepwrite.c
u8 D_800D2008_main BSS; // aura.c, camera.c, hmfdraw.c, ...
omOvlHisData omovlhis[12] ALIGNED(8) BSS; // objmain.c
HmfDrawEntry *D_800D2070_main[8] BSS; // hmfdraw.c, hmfman.c
void *nextFrameBuffer BSS; // graphics.c
u32 D_800D2094_main BSS; // graphics.c, main.c, nnsched.c
u8 D_800D2098_main[0x4] BSS; // unreferenced
s32 D_800D209C_main BSS; // window.c
u8 D_800D20A0_main[8] BSS; // audio.c, hmfdraw.c, input.c, ...; contains D_800D20A1_main
u32 sPrcSleepLoc BSS; // process.c
s32 D_800D20AC_main BSS; // hmfdraw.c, hmfman.c, mallocblock.c
u8 D_800D20B0_main BSS; // mgmode
s8 HmfPauseF BSS; // gamemes.c, hmfman.c, hmfspr.c, ...
u8 D_800D20B8_main[16][3] ALIGNED(8) BSS; // hmfspr.c
u8 D_800D20E8_main[0x4] BSS; // unreferenced
u8 D_800D20EC_main BSS; // saveload.c
u16 D_800D20EE_main BSS; // hmfdraw.c, hmfman.c
omOvlHisData mbovlhis[5] BSS; // overlays only
omObjData *omDBGSysKeyObj BSS; // objmain.c
u8 D_800D211C_main BSS; // hmfdraw.c
f32 D_800D2120_main BSS; // hmfdraw.c
u8 D_800D2124_main[0xA] BSS; // unreferenced
u8 D_800D212E_main BSS; // wipe.c
u8 D_800D212F_main BSS; // unreferenced
s16 D_800D2130_main BSS; // unreferenced
u8 D_800D2132_main BSS; // objmain.c, pause.c
u8 D_800D2133_main BSS; // unreferenced
u8 D_800D2134_main[0xC] BSS; // unreferenced
void *D_800D2140_main[2000] BSS; // mallocblock.c
s16 D_800D4080_main BSS; // overlays only
u16 D_800D4082_main BSS; // gameman.c, objmain.c
void *D_800D4084_main BSS; // window.c
u8 D_800D4088_main[0x4] BSS; // unreferenced
HmfAnimSet *D_800D408C_main BSS; // hmfanim.c, hmfspr.c
s16 D_800D4090_main[6][3][7] BSS; // hmfspr.c
s16 D_800D418C_main BSS; // unreferenced
s16 D_800D418E_main BSS; // camera.c, hmfcoll.c, hmfman.c, ...
OSProf *__osProfileListEnd BSS; // 2.0L/os/timerintr.c
s16 D_800D4194_main BSS; // overlays only
s16 D_800D4196_main BSS; // overlays only
f32 D_800D4198_main[4] BSS; // objmain.c, objsysobj.c
OSMesgQueue __osProfTimerQ BSS; // 2.0L/os/timerintr.c; contains D_800D41B0_main
s32 mbWalkNum BSS; // overlays only
u8 D_800D41C4_main BSS; // hmfdraw.c, hmfman.c
OSTimer __osEepromTimer BSS; // 2.0L/io/conteeplongwrite.c
u8 D_800D41E8_main[0x8] BSS; // unreferenced
HuMtx4F D_800D41F0_main[64] BSS; // hmfdraw.c
u8 D_800D51F0_main[0x4] BSS; // unreferenced
f32 wipeTime BSS; // wipe.c
s16 D_800D51F8_main BSS; // overlays only
f32 D_800D51FC_main BSS; // hmfdraw.c, objmain.c
void *__osRdb_Read_Data_Buf BSS; // 2.0L/debug/readhost.c
u16 D_800D5204_main[4] BSS; // hmfdraw.c, hmfload.c, hmfman.c, ...; contains mesWInsert
u16 HuSprGrpNum BSS; // sprman.c
f32 D_800D5210_main BSS; // objmain.c, objsysobj.c
s16 D_800D5214_main BSS; // hmfdraw.c
char D_800D5218_main[128] BSS; // lightdebug.c, objmain.c
str800D5298 D_800D5298_main BSS; // audio.c, gameman.c; contains D_800D52C0_main
u8 D_800D5304_main BSS; // wipe.c
u16 D_800D5306_main BSS; // hmfdraw.c
Vtx *D_800D5308_main BSS; // hmfdraw.c
u16 D_800D530C_main BSS; // gamemes.c, objmain.c, objsysobj.c
__OSInode __osPfsInodeCache BSS; // 2.0L/io/contpfs.c
f32 D_800D5410_main BSS; // hmfdraw.c, objmain.c
s8 D_800D5418_main[4][8] ALIGNED(8) BSS; // pad.c
s16 D_800D5438_main BSS; // esprite.c
__OSEventState __osEventStateTab[OS_NUM_EVENTS] ALIGNED(8) BSS; // 2.0L/os/seteventmesg.c
Vec CenterM[6] BSS; // gameman.c, objsysobj.c; contains D_800D54FC_main, D_800D5500_main
s8 winTabSize BSS; // window.c
s16 D_800D5542_main BSS; // pad.c
u16 D_800D5544_main[5] BSS; // hmfdraw.c, input.c; contains D_800D5546_main
u16 D_800D554E_main BSS; // sprman.c
u16 *D_800D5550_main BSS; // wipe.c
rdbPacket *D_800D5554_main BSS; // 2.0L/os/initrdb.c, 2.0L/os/rdbsend.c
u16 D_800D5558_main[4] BSS; // audio.c, lightdebug.c, objmain.c, ...
s16 omobjfirst BSS; // objmain.c
s16 D_800D5562_main BSS; // hmfdraw.c
s16 D_800D5564_main BSS; // hmfdraw.c
u32 gISVFlag BSS; // 2.0L/os/initialize_isv.c
HuAllocFunc gMallocFunc BSS; // mallocblock.c
u8 D_800D5570_main[16][3] BSS; // hmfspr.c
OSPifRam __osPfsPifRam BSS; // 2.0L/io/contramread.c, 2.0L/io/contramwrite.c, 2.0L/io/pfsgetstatus.c, ...
__OSThreadprofile_s thprof[62] BSS; // 2.0L/debug/threadprofile.c, 2.0L/os/createthread.c
u8 D_800D59C0_main[0x10] BSS; // hmfdraw.c
u8 D_800D59D0_main[0x10] BSS; // unreferenced
s16 kakusiMasuStarHis[10] BSS; // overlays only
Vtx *D_800D59F4_main BSS; // sprman.c, sprput.c
HmfVertexAnim *D_800D59F8_main BSS; // hmfshape.c
HuMtx4F D_800D5A00_main[64] ALIGNED(8) BSS; // hmfdraw.c, hmfspr.c; contains D_800D5A40_main
EffectGroup *D_800D6A00_main[EFFECT_GROUP_MAX] BSS; // effect.c
u32 D_800D6A20_main BSS; // hmfdraw.c
u16 gISVChk BSS; // 2.0L/os/initialize_isv.c
s8 comKeyIdxNow BSS; // window.c
OSMesgQueue __osEepromTimerQ BSS; // 2.0L/io/conteeplongwrite.c, 2.0L/io/controller.c
omObjData *D_800D6A40_main BSS; // audio.c, objmain.c, objsysobj.c
s16 kakusiMasuStarHisIdx BSS; // overlays only
u16 D_800D6A46_main BSS; // printfunc.c
s16 D_800D6A48_main BSS; // overlays only
s8 D_800D6A4C_main[4] BSS; // audio.c
u8 D_800D6A50_main[6] BSS; // hmfspr.c
u16 D_800D6A56_main BSS; // gameman.c, objmain.c
u8 D_800D6A58_main BSS; // gamemes.c, objmain.c
u8 D_800D6A59_main BSS; // unreferenced
s16 D_800D6A5A_main BSS; // unreferenced
u8 __rmonRcpAtBreak BSS; // 2.0L/rmon/rmonbrk.c, 2.0L/rmon/rmontask.c
OSMesgQueue __rmonMQ BSS; // 2.0L/rmon/rmonmain.c, 2.0L/rmon/rmonmisc.c
Vec D_800D6A78_main BSS; // objsysobj.c
Gfx *D_800D6A88_main ALIGNED(8) BSS; // hmfdraw.c
u32 D_800D6A8C_main BSS; // 2.0L/os/initrdb.c, 2.0L/os/rdbsend.c
u8 D_800D6A90_main BSS; // objmain.c, window.c
s16 D_800D6A92_main BSS; // hmfdraw.c
Vtx *D_800D6A98_main[8] ALIGNED(8) BSS; // hmfdraw.c
s32 D_800D6AB8_main BSS; // objsysobj.c
Vec Center BSS; // gameman.c, objsysobj.c
s16 D_800D6AC8_main[8] BSS; // hmfdraw.c
s16 D_800D6AD8_main BSS; // unreferenced
s16 D_800D6ADA_main BSS; // pause.c
Vec CRotM[6] ALIGNED(8) BSS; // gameman.c, objsysobj.c; contains D_800D6AE4_main
OSMesgQueue D_800D6B28_main BSS; // rom.c
s16 omnextidx BSS; // objmain.c
OSMesgQueue __osSiAccessQueue ALIGNED(8) BSS; // 2.0L/io/siacs.c
s16 mbovlhisidx BSS; // overlays only
s16 winPrio BSS; // window.c
s16 D_800D6B64_main BSS; // hmfdraw.c, hmfman.c
HuMallocHeader *gFirstMallocBlock BSS; // mallocblock.c
u8 D_800D6B6C_main[0x4] BSS; // unreferenced
