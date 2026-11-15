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
u16 espMax BSS; // esprite.c
u16 ContBtnDown[4] BSS; // input.c, pause.c, window.c
u16 Hu3DMtxMax BSS; // hmfdraw.c
u32 texSizLineBytes BSS; // hmfdraw.c
HuSprAnimData *HuSprAnimTbl[256] BSS; // esprite.c, sprman.c
s16 mbSubMusNo BSS; // overlays only
s16 Hu3DCameraNum BSS; // camera.c, hmfdraw.c, hmfman.c
HuSprGrp *HuSprGrpLast BSS; // sprman.c
f32 mbCameraZoom BSS; // overlays only
s16 HuMemDelayFreeCnt BSS; // mallocblock.c
s32 Hu3DCurAttr BSS; // hmfcoll.c, hmfdraw.c, hmfman.c
u16 saveStorySystemSize BSS; // saveEncode.c, saveload.c
void *__osRdb_DbgRead_Buf BSS; // 2.0L/rmon/rmonsio.c
void *HuMemDebugBlk[2000] ALIGNED(8) BSS; // mallocblock.c
f32 CFanOfs BSS; // objmain.c, objsysobj.c
s16 mgModeCoinRate BSS; // overlays only
u32 __osBaseCounter ALIGNED(8) BSS; // 2.0L/io/vimgr.c, 2.0L/os/gettime.c, 2.0L/os/timerintr.c
void *currFrameBuffer BSS; // graphics.c, wipe.c
u16 HuSprOrderNum BSS; // sprman.c
s32 fontcolor BSS; // lightdebug.c, objmain.c, printfunc.c
Light *Hu3DLightP BSS; // hmfdraw.c, hmflight.c
u8 msmMonoF BSS; // msm.c, n_synsetpan.c, n_synstartvoiceparam.c
s16 ringBufferIndex BSS; // graphics.c
u8 Hu3DObjExtF[8] BSS; // hmfdraw.c, hmfload.c; contains mgPlayerTeam
u64 *gThreadOutStackSize BSS; // graphics.c, profiler.c
u16 espNum BSS; // esprite.c
HmfData Hu3DMotionHmf BSS; // hmfman.c
u8 winPauseF BSS; // pause.c, window.c
u32 __kmc_pt_mode BSS; // 2.0L/os/initialize_kmc.c, 2.0L/os/initialize_msp.c
s16 omPadBtnRep[4] BSS; // audio.c
u8 D_800CB9B0_main[0x1B0] ALIGNED(8) BSS; // unreferenced
HmfModelEntry *Hu3DSprModelData BSS; // hmfspr.c
u16 saveBoardSystemSize[14] BSS; // pad.c, audio.c, hmfman.c, ...; contains HuPadBtnOld, HuPadStkX, Hu3DDLModelNum
graphicsMessage gMesgRingBuffer[0x40] BSS; // graphics.c
Vtx *Hu3DSprVtxBuf[8] BSS; // hmfspr.c
HuSprGrp *HuSprGrpFirst BSS; // sprman.c
s32 HuGfxFrameCnt BSS; // graphics.c
u8 Hu3DClipRatio BSS; // hmfdraw.c, hmfman.c
HmfData_Unk84_Entry *texAnimGfxBak BSS; // hmfdraw.c
u32 __osProfileOverflowBin BSS; // 2.0L/os/timerintr.c
s16 Hu3DHiliteLightNo BSS; // hmfdraw.c, hmflight.c
s16 Hu3DFogEnd BSS; // hmfdraw.c, hmfman.c
s16 mbUnkParam BSS; // overlays only
u8 wipeMode BSS; // wipe.c
HmfDrawObject *DrawObjData BSS; // hmfdraw.c, hmfman.c
u8 mbDiceUnkF BSS; // overlays only
GW_COMMON GwCommon ALIGNED(8) BSS; // gamework.c, saveload.c, window.c
u8 D_800CC16C_main[0x204] BSS; // unreferenced
s32 omObjExecCnt BSS; // objmain.c
s16 kakusiMasuItemHis[10] ALIGNED(8) BSS; // overlays only
Gfx gTaskDataPointers[2] BSS; // graphics.c
OSMesgQueue scAudioTaskQueue BSS; // audiomgr.c, nnsched.c
void (*omCurObjFunc)(omObjData *) BSS; // objmain.c
s16 gSwapChainMesgTotal BSS; // graphics.c
OSMesgQueue scGraphicsTaskQueue BSS; // graphics.c, nnsched.c, profiler.c
void (*Hu3DLayerHook[1])(Gfx **, HuCamMtxs *, s16) BSS; // hmfman.c
u8 D_800CC3DC_main[0x4] BSS; // overlays only
u8 mbMgHisIdx[4] BSS; // overlays only
s16 D_800CC3E4_main BSS; // unreferenced
u16 HuSprAnimNum BSS; // sprman.c
u8 D_800CC3E8_main[0x8] BSS; // unreferenced
OSPifRam __osContPifRam BSS; // 2.0L/io/contreaddata.c, 2.0L/io/controller.c
s16 omobjlast BSS; // objmain.c
s16 D_800CC432_main BSS; // unreferenced
u8 D_800CC434_main[0x4] BSS; // unreferenced
s16 mgModeSelNo BSS; // overlays only
s16 D_800CC43A_main BSS; // unreferenced
u32 __osRdb_IP6_CurWrite BSS; // 2.0L/os/initrdb.c, 2.0L/os/rdbsend.c
Unk_D_800CC440 printWinData[4] BSS; // lightdebug.c, printfunc.c
UnkData_CD0A0 mbMgHis BSS; // overlays only
s16 kakusiMasuItem BSS; // overlays only
OSThread swapChainThread BSS; // graphics.c
u16 mgBattleCoinPot BSS; // overlays only
TextWindow *winData BSS; // window.c, pause.c
u16 strlinecnt BSS; // printfunc.c
s16 D_800CC6A2_main BSS; // unreferenced
u8 D_800CC6A4_main[0x80C] BSS; // unreferenced
OSPiHandle __Dom2SpeedParam BSS; // 2.0L/io/pimgr.c, 2.0L/os/initialize.c
OSProf *__osProfileList BSS; // 2.0L/os/timerintr.c
s16 MTXBufNum BSS; // hmfcoll.c, hmfdraw.c
s32 scPreNMIF BSS; // nnsched.c
Gfx *HuSprTileBuf BSS; // sprman.c, sprput.c
void *mainIntrQueue ALIGNED(8) BSS; // gameman.c, main.c
u8 D_800CCF3C_main[0x14] BSS; // unreferenced
s16 ommaxobjs BSS; // objmain.c
u8 HuGfxBufNum BSS; // main.c, objmain.c
u16 savePlayerSize BSS; // saveEncode.c, saveload.c
HmfModelData_Unk64_Unk8C_Struct *Hu3DMotion BSS; // hmfdraw.c, hmfman.c, hmfspr.c
OSMesgQueue mainOtherQueue ALIGNED(8) BSS; // main.c
u8 GameManPadNoneF[4] BSS; // gameman.c
u16 omPadBtn[4] BSS; // audio.c, objmain.c
u8 wipeStat BSS; // wipe.c
u8 Hu3DLoadFlags BSS; // hmfanim.c, hmfload.c
u32 texLoadSiz BSS; // hmfdraw.c
s16 omnumobjs BSS; // objmain.c
ISVDbg *gISVDbgPrnAdrs BSS; // 2.0L/os/initialize_isv.c
f32 CFanLenM[4] ALIGNED(8) BSS; // objmain.c, objsysobj.c
void *piMesgBuf BSS; // rom.c
u8 D_800CCFAC_main[0xA4] BSS; // unreferenced
u16 omMusFadeTime BSS; // objmain.c
GW_SYSTEM GwSystem ALIGNED(8) BSS; // gamemes.c, gamework.c, objmain.c, ...
u8 gEncodedSaveBuffer[224] BSS; // saveEncode.c, saveload.c
__osExceptionVector __isExpJPSave BSS; // 2.0L/os/initialize_isv.c
s16 motionBakeMtxCnt BSS; // hmfspr.c
Mtx *Hu3DMtxBuf[8] ALIGNED(8) BSS; // hmfdraw.c
u32 __osViIntrCount BSS; // 2.0L/io/vimgr.c, 2.0L/os/timerintr.c
ESPRITE *esprite BSS; // esprite.c
omObjGroup omgroup[10] BSS; // objmain.c
u8 Hu3DScreenClearF BSS; // hmfman.c, objmain.c
f32 CZoomM[6] ALIGNED(8) BSS; // gameman.c, objsysobj.c
Unk800CD2A0 ditherBak BSS; // hmfdraw.c
u8 cancelCRF BSS; // window.c
Vec CUpM[4] BSS; // objsysobj.c
u8 D_800CD2D8_main[0x18] BSS; // unreferenced
u32 __osThprofCount BSS; // 2.0L/debug/threadprofile.c
u16 omHu3DGfxNum BSS; // gameman.c, objmain.c
u16 Hu3DDLModelId BSS; // hmfman.c
HmfPaletteData *Hu3DPalData BSS; // hmfanim.c
u32 texSizIncr BSS; // hmfdraw.c
GAMEMES gMesData[GMES_MAX] BSS; // gamemes.c; contains D_800CD360_main, D_800CD364_main
u8 D_800CD6A0_main[0x4] BSS; // unreferenced
u16 saveStorySize BSS; // saveEncode.c, saveload.c
u8 Hu3DCameraNo BSS; // hmfdraw.c, hmfman.c, hmfparticle.c
u8 D_800CD6A7_main BSS; // unreferenced
u8 D_800CD6A8_main[0x8] BSS; // unreferenced
HmfDrawFace faceBuf[48] BSS; // hmfdraw.c
u8 D_800CDA70_main[0x4] BSS; // unreferenced
u8 wipeColorR BSS; // wipe.c
s16 lightColBakB BSS; // hmfdraw.c
u32 __osRdb_Read_Data_Ct BSS; // 2.0L/debug/readhost.c
s16 HuPadBtn[4] BSS; // audio.c, input.c, pad.c
u8 Hu3DFogColB BSS; // hmfdraw.c, hmfman.c
s16 ambColBakB BSS; // hmfdraw.c
WindowInputRecord winComKeyBuf[WINDOW_INPUT_RECORDS_MAX] BSS; // window.c
s16 HuAudMusNo BSS; // audio.c, objmain.c, objsysobj.c
UnkDiceRelated mbDiceData[5] ALIGNED(8) BSS; // overlays only
u16 saftyFrameF BSS; // printfunc.c
u16 Hu3DSprModelMax BSS; // hmfspr.c
OSPiHandle *cartRomHandle BSS; // gameman.c, rom.c
Vtx *Hu3DSprVtxPos BSS; // hmfspr.c
s16 mbCameraBtnF BSS; // overlays only
s16 ambColBakR BSS; // hmfdraw.c
u16 omPadBtnDown[4] BSS; // audio.c, objmain.c
s16 mbDiceBtnF BSS; // overlays only
s16 vtxCntBak BSS; // hmfdraw.c
s16 kakusiMasuItemCnt BSS; // unreferenced
s16 Hu3DModelTag BSS; // hmfdraw.c, hmfload.c, hmfman.c, ...
HuSprGrp *HuSprGrpData[HUSPR_GRP_MAX] ALIGNED(8) BSS; // sprman.c
s16 ambColBakG BSS; // hmfdraw.c
u32 __osRdb_IP6_Size BSS; // 2.0L/os/initrdb.c, 2.0L/os/rdbsend.c
s32 CFan BSS; // camsetup.c, objsysobj.c
f32 D_800CE17C_main[5] BSS; // objsysobj.c
s16 omExecStep BSS; // objmain.c
omObjData *omSysTimerObj BSS; // objsysobj.c
s16 mbBoardMusId BSS; // overlays only
u8 Hu3DLayerNo BSS; // hmfdraw.c, hmfman.c
OSMesgQueue siMesgQueue ALIGNED(8) BSS; // eeprom.c, pad.c, siman.c, ...
void *HuSprGfxBuf[3] BSS; // sprman.c
s16 kakusiMasuCoin BSS; // overlays only
u8 Hu3DFogF BSS; // hmfdraw.c, hmfman.c
f32 CZoom BSS; // gameman.c, objsysobj.c
s16 D_800CE1CC_main BSS; // unreferenced
s16 vtxCnt BSS; // hmfdraw.c
s16 duelUnkF0 BSS; // overlays only
UnkLightData *Hu3DLightData BSS; // hmfdraw.c, hmflight.c, lightdebug.c
u8 D_800CE1D8_main[0x4] BSS; // unreferenced
Unk_D_800CE1DC saftyFrameData BSS; // objmain.c, printfunc.c
s16 kakusiMasuCoinHis[10] BSS; // overlays only
u64 *gThreadYieldStack BSS; // graphics.c, profiler.c
s32 omovl BSS; // objmain.c, gamemes.c; contains D_800CE202_main
u8 __osMaxControllers BSS; // 2.0L/io/contreaddata.c, 2.0L/io/controller.c, 2.0L/io/contsetch.c, ...
s16 mbSeqPlayF BSS; // overlays only
u16 kakusiMasuStarCnt BSS; // overlays only
HmfLookAtData *Hu3DLookAtP BSS; // hmfdraw.c
u32 scPreNMICnt BSS; // nnsched.c
u16 omPauseWinInitF BSS; // objmain.c, pause.c
s16 HuAudSeVol[64] BSS; // audio.c
Process *pauseProc BSS; // pause.c
s16 mgModeMgNo BSS; // overlays only
s16 D_800CE29E_main BSS; // unreferenced
u8 mgModeRecordBak[0x14] BSS; // unreferenced
s16 Hu3DMotionTag BSS; // hmfdraw.c
OSTime __osCurrentTime BSS; // 2.0L/io/vimgr.c, 2.0L/os/gettime.c, 2.0L/os/timerintr.c
u16 saveChecksumOfs BSS; // saveEncode.c, saveload.c
void *winCursorData BSS; // window.c
u32 scRetraceRate BSS; // nnsched.c
s8 HuPadStkXHis[4][8] ALIGNED(8) BSS; // pad.c
u32 renderModeBak BSS; // hmfdraw.c; declared u64 in hmfdraw.c
s32 D_800CE2F4_main BSS; // hmfdraw.c
u8 D_800CE2F8_main[0x2008] BSS; // unreferenced
u64 *gThread3Stack BSS; // boot.c, graphics.c, profiler.c
GW_STORY GwStory ALIGNED(8) BSS; // gamework.c, saveload.c
s16 mbItemBtnF BSS; // overlays only
s16 HuAudSubMusNo BSS; // audio.c, objsysobj.c
OSPiHandle __CartRomHandle BSS; // 2.0L/io/cartrominit.c
HuMallocHeader *gLastMallocBlock BSS; // mallocblock.c
HmfModel *Hu3DData BSS; // aura.c, camera.c, effect.c, ...
u16 kakusiMasuCoinCnt BSS; // overlays only
s16 mgModeStar BSS; // overlays only; accessed as s16[4] in mgmode
u8 D_800D0400_main[0x8] BSS; // unreferenced
u8 D_800D0408_main[0x4] BSS; // unreferenced
Process *winProc BSS; // window.c
u16 empstrline BSS; // printfunc.c
s16 D_800D0412_main BSS; // unreferenced
u8 D_800D0414_main[0x4] BSS; // unreferenced
s16 mgModeMgList[8] BSS; // overlays only
u8 D_800D0428_main[0x18] BSS; // unreferenced
HmfData_Unk84_Entry *texAnimEntryBak BSS; // hmfdraw.c
HuCamMtxs *Hu3DCurCamMtx BSS; // camera.c, hmflight.c, hmfman.c
Process *GameManDrawPrc BSS; // gameman.c
u8 eepCommonBuf[24] ALIGNED(8) BSS; // eeprom.c, saveload.c
s16 HuSprLayerHookMdl BSS; // sprman.c
OSPifRam __osEepPifRam ALIGNED(8) BSS; // 2.0L/io/conteepread.c, 2.0L/io/conteepwrite.c
u16 saveCommonSize BSS; // saveEncode.c, saveload.c
s16 *motionBakeNodeMap BSS; // hmfspr.c
f32 CFanM[6][6] BSS; // camsetup.c, objsysobj.c
u64 *gThreadOutStack BSS; // graphics.c, profiler.c
omObjData *omCurObj BSS; // objmain.c
OSMesgQueue __osPiAccessQueue BSS; // 2.0L/io/piacs.c, 2.0L/io/pimgr.c
s16 D_800D0568_main[20] BSS; // pad.c; contains HuPadStkXSum
s16 ContBtnRep[4] BSS; // input.c, lightdebug.c, window.c
u8 wipeColorG BSS; // wipe.c
u8 Hu3DFogColR BSS; // hmfdraw.c, hmfman.c
u16 Hu3DDLModelList[4][128] ALIGNED(8) BSS; // hmfman.c
u8 D_800D09A0_main[0x8] BSS; // unreferenced
SaveCommonBuf saveCommonBuf BSS; // audio.c, gameman.c, saveload.c; contains D_800D09A9_main
OSPiHandle __Dom1SpeedParam BSS; // 2.0L/io/pimgr.c, 2.0L/os/initialize.c
s32 *gUCodeAddresses BSS; // graphics.c, profiler.c
s16 pauseSprAnim BSS; // pause.c
u16 omHu3DReinitWait BSS; // objmain.c
f32 wipeDuration BSS; // wipe.c
u8 D_800D0A40_main[0x4] BSS; // unreferenced
s16 faceCnt BSS; // hmfdraw.c
s16 D_800D0A46_main BSS; // unreferenced
u8 D_800D0A48_main[0x8] BSS; // unreferenced
HuSprAnmDesc *HuSprPalAnimData[0x100] BSS; // sprman.c
u8 eepBoxBuf[672] BSS; // eeprom.c, saveload.c
u8 D_800D10F0_main BSS; // hmfdraw.c
s16 HuSprBGHookMdl BSS; // sprman.c
HuCamera *Hu3DCurCamera BSS; // camera.c, hmfcoll.c, hmfdraw.c, ...
s16 ContRepCnt[4] BSS; // input.c
u16 omMgActiveF BSS; // gamemes.c, objmain.c
CollisionGrid *MapCollData BSS; // hmfcoll.c
GW_PLAYER GwPlayer[5] BSS; // audio.c, gameman.c, objmain.c, ...
OSMesgQueue siReqQueue BSS; // siman.c
HuMallocHeader *gLastFreedBlock BSS; // mallocblock.c
s8 omPadStkY[4] BSS; // audio.c
s32 mbGameMode BSS; // overlays only
u16 HuPadBtnRep[4] BSS; // audio.c, lightdebug.c, pad.c
s16 duelUnkF1 BSS; // overlays only
s16 kakusiMasuStar BSS; // overlays only
u8 __rmonUtilityBuffer[256] BSS; // 2.0L/rmon/rmonmem.c, 2.0L/rmon/rmontask.c
u16 ContBtnOld[4] BSS; // input.c
HuMtx4F *motionBakeMtx BSS; // hmfspr.c
HuFreeFunc gFreeFunc BSS; // hmfman.c, mallocblock.c
Gfx *Hu3DSprGfxBuf[8] BSS; // hmfspr.c
s16 mbWipeType[5] BSS; // pad.c; contains HuPadStkYSum
s16 Hu3DObjMtxStackIdx BSS; // hmfdraw.c, hmfspr.c
Vec CRot BSS; // gameman.c, objsysobj.c
str800D5298 HuAudFadeSysConfig BSS; // objsysobj.c; contains D_800D13EE_main
HmfLookAtData Hu3DLookAtBuf[8] BSS; // hmfdraw.c
s16 kakusiMasuItemForceF BSS; // overlays only
Process *GameManExecPrc BSS; // gameman.c
s8 omHu3DBufNum BSS; // gameman.c, objmain.c
HmfAnim *Hu3DAnimData BSS; // hmfanim.c, hmfspr.c
u8 D_800D1718_main[0x8] BSS; // unreferenced
u8 rmonRdbReadBuf[2048] BSS; // 2.0L/rmon/rmonsio.c
u8 mgModeGroupBak[4] BSS; // overlays only
u32 __osThprofLastTimer BSS; // 2.0L/debug/threadprofile.c
s16 selMenuMgModeF BSS; // unreferenced
u8 texFilterBak BSS; // hmfdraw.c
s16 mgModeMgListIdx BSS; // overlays only
Gfx *Hu3DSprGfxPos ALIGNED(8) BSS; // hmfspr.c
u8 comKeyIdx BSS; // window.c
Gfx *Hu3DGfxBuf[8] BSS; // hmfdraw.c
u8 __osContLastCmd BSS; // 2.0L/io/conteepread.c, 2.0L/io/conteepwrite.c, 2.0L/io/contramread.c, ...
WipeTexture wipeTex BSS; // wipe.c; contains D_800D1F60_main
u32 leoComuBuffAdd BSS; // 2.0L/os/initialize_isv.c
Mtx *MTXBuf BSS; // hmfcoll.c, hmfdraw.c
OSMesg __osEepromTimerMsg BSS; // 2.0L/io/conteeplongwrite.c, 2.0L/io/controller.c
s32 Hu3DDrawDoneCnt BSS; // hmfman.c, main.c
s32 geomFlagsBak BSS; // hmfdraw.c
s16 lightColBakR BSS; // hmfdraw.c
s16 kakusiMasuItemHisIdx BSS; // overlays only
u8 *wipeMallocBuf[8] ALIGNED(8) BSS; // wipe.c
u8 omHu3DReinitSkipF BSS; // objmain.c
s16 gNumOfControllers BSS; // pad.c, util.c
OSTimer __osBaseTimer BSS; // 2.0L/os/timerintr.c
s32 __osRdb_IP6_CurSend BSS; // 2.0L/os/initrdb.c
HmfData_Unk84_Entry2 *Hu3DTexData BSS; // hmfanim.c, hmfman.c
u32 combineModeBak BSS; // hmfdraw.c; declared u64 in hmfdraw.c
s32 D_800D1FD4_main BSS; // hmfdraw.c
s16 D_800D1FD8_main BSS; // hmfdraw.c
s32 HuSprGfxBufSize BSS; // sprman.c
s16 mgModeCoinBase BSS; // unreferenced
s16 lightColBakG BSS; // hmfdraw.c
WindowFont *winFontData BSS; // window.c
s32 Hu3DModelNum BSS; // hmfman.c
s16 kakusiMasuCoinHisIdx BSS; // overlays only
u16 Hu3DVtxMax BSS; // hmfdraw.c
u8 Hu3DBufNum BSS; // camera.c, hmfdraw.c, hmfman.c, ...
Gfx *gMainGfxPos BSS; // gamemes.c, hmfanim.c, hmfdraw.c, ...
Gfx *Hu3DGfxStart BSS; // hmfdraw.c, hmfman.c
u32 texSizShift BSS; // hmfdraw.c
u32 __osTimerCounter BSS; // 2.0L/os/settimer.c, 2.0L/os/timerintr.c
s32 __osEepromRead16K BSS; // 2.0L/io/conteepprobe.c, 2.0L/io/conteepread.c, 2.0L/io/conteepwrite.c
u8 Hu3DBufNo BSS; // aura.c, camera.c, hmfdraw.c, ...
omOvlHisData omovlhis[12] ALIGNED(8) BSS; // objmain.c
HmfDrawEntry *Hu3DDrawList[8] BSS; // hmfdraw.c, hmfman.c
void *nextFrameBuffer BSS; // graphics.c
u32 scRetraceCnt BSS; // graphics.c, main.c, nnsched.c
u8 D_800D2098_main[0x4] BSS; // unreferenced
s32 winLastAdvance BSS; // window.c
u8 Hu3DFlatShadeF[8] BSS; // audio.c, hmfdraw.c, input.c, ...; contains HuPadStkY
u32 sPrcSleepLoc BSS; // process.c
s32 Hu3DFrameCnt BSS; // hmfdraw.c, hmfman.c, mallocblock.c
u8 mgModeMenuNo BSS; // mgmode
s8 Hu3DPauseF BSS; // gamemes.c, hmfman.c, hmfspr.c, ...
u8 CharAnimId[16][3] ALIGNED(8) BSS; // hmfspr.c
u8 D_800D20E8_main[0x4] BSS; // unreferenced
u8 SLFormatFlags BSS; // saveload.c
u16 Hu3DDrawEnableF BSS; // hmfdraw.c, hmfman.c
omOvlHisData mbovlhis[5] BSS; // overlays only
omObjData *omDBGSysKeyObj BSS; // objmain.c
u8 shadingBak BSS; // hmfdraw.c
f32 Hu3DMotionGlobalSpeed BSS; // hmfdraw.c
u8 mgModeCursor[0xA] BSS; // unreferenced
u8 wipeColorB BSS; // wipe.c
u8 D_800D212F_main BSS; // unreferenced
s16 kakusiMasuCoinForceF BSS; // unreferenced
u8 omSysPauseReadyF BSS; // objmain.c, pause.c
u8 D_800D2133_main BSS; // unreferenced
u8 D_800D2134_main[0xC] BSS; // unreferenced
void *HuMemDebugBlkOld[2000] BSS; // mallocblock.c
s16 kakusiMasuStarForceF BSS; // overlays only
u16 omHu3DVtxNum BSS; // gameman.c, objmain.c
void *winFrameData BSS; // window.c
u8 D_800D4088_main[0x4] BSS; // unreferenced
HmfAnimSet *Hu3DAnimSetData BSS; // hmfanim.c, hmfspr.c
s16 CharAnimWork[6][3][7] BSS; // hmfspr.c
s16 D_800D418C_main BSS; // unreferenced
s16 Hu3DCamMtxNo BSS; // camera.c, hmfcoll.c, hmfman.c, ...
OSProf *__osProfileListEnd BSS; // 2.0L/os/timerintr.c
s16 mgModeType BSS; // overlays only
s16 mbOvlCallF BSS; // overlays only
f32 CFanOfsM[4] BSS; // objmain.c, objsysobj.c
OSMesgQueue __osProfTimerQ BSS; // 2.0L/os/timerintr.c; contains D_800D41B0_main
s32 mbWalkNum BSS; // overlays only
u8 Hu3DFogColG BSS; // hmfdraw.c, hmfman.c
OSTimer __osEepromTimer BSS; // 2.0L/io/conteeplongwrite.c
u8 D_800D41E8_main[0x8] BSS; // unreferenced
HuMtx4F Hu3DSubMtxStack[64] BSS; // hmfdraw.c
u8 D_800D51F0_main[0x4] BSS; // unreferenced
f32 wipeTime BSS; // wipe.c
s16 duelCancelEnableF BSS; // overlays only
f32 Hu3DMatAmbScale BSS; // hmfdraw.c, objmain.c
void *__osRdb_Read_Data_Buf BSS; // 2.0L/debug/readhost.c
u16 Hu3DModelDataTag[4] BSS; // hmfdraw.c, hmfload.c, hmfman.c, ...; contains mesWInsert
u16 HuSprGrpNum BSS; // sprman.c
f32 CFanLen BSS; // objmain.c, objsysobj.c
s16 Hu3DSubMtxStackIdx BSS; // hmfdraw.c
char omDBGStrBuf[128] BSS; // lightdebug.c, objmain.c
str800D5298 HuAudSysConfig BSS; // audio.c, gameman.c; contains D_800D52C0_main
u8 wipeScreenStillF BSS; // wipe.c
u16 Hu3DGfxMax BSS; // hmfdraw.c
Vtx *Hu3DVtxPos BSS; // hmfdraw.c
u16 omSysExitReq BSS; // gamemes.c, objmain.c, objsysobj.c
__OSInode __osPfsInodeCache BSS; // 2.0L/io/contpfs.c
f32 Hu3DMatColScale BSS; // hmfdraw.c, objmain.c
s8 HuPadStkYHis[4][8] ALIGNED(8) BSS; // pad.c
s16 espFreeIdx BSS; // esprite.c
__OSEventState __osEventStateTab[OS_NUM_EVENTS] ALIGNED(8) BSS; // 2.0L/os/seteventmesg.c
Vec CenterM[6] BSS; // gameman.c, objsysobj.c; contains D_800D54FC_main, D_800D5500_main
s8 winTabSize BSS; // window.c
s16 HuPadReadNum BSS; // pad.c
u16 matGfxSplitF[5] BSS; // hmfdraw.c, input.c; contains ContBtn
u16 HuSprPalAnimNum BSS; // sprman.c
u16 *wipeScreenBufP BSS; // wipe.c
rdbPacket *__osRdb_IP6_Data BSS; // 2.0L/os/initrdb.c, 2.0L/os/rdbsend.c
u16 HuPadBtnDown[4] BSS; // audio.c, lightdebug.c, objmain.c, ...
s16 omobjfirst BSS; // objmain.c
s16 faceNormCnt BSS; // hmfdraw.c
s16 DrawObjIdx BSS; // hmfdraw.c
u32 gISVFlag BSS; // 2.0L/os/initialize_isv.c
HuAllocFunc gMallocFunc BSS; // mallocblock.c
u8 CharAnimSrc[16][3] BSS; // hmfspr.c
OSPifRam __osPfsPifRam BSS; // 2.0L/io/contramread.c, 2.0L/io/contramwrite.c, 2.0L/io/pfsgetstatus.c, ...
__OSThreadprofile_s thprof[62] BSS; // 2.0L/debug/threadprofile.c, 2.0L/os/createthread.c
u8 D_800D59C0_main[0x10] BSS; // hmfdraw.c
u8 D_800D59D0_main[0x10] BSS; // unreferenced
s16 kakusiMasuStarHis[10] BSS; // overlays only
Vtx *HuSprVtxPos BSS; // sprman.c, sprput.c
HmfVertexAnim *Hu3DShapeData BSS; // hmfshape.c
HuMtx4F Hu3DObjMtxStack[64] ALIGNED(8) BSS; // hmfdraw.c, hmfspr.c; contains D_800D5A40_main
EffectGroup *EffectGroupData[EFFECT_GROUP_MAX] BSS; // effect.c
u32 texSizBytes BSS; // hmfdraw.c
u16 gISVChk BSS; // 2.0L/os/initialize_isv.c
s8 comKeyIdxNow BSS; // window.c
OSMesgQueue __osEepromTimerQ BSS; // 2.0L/io/conteeplongwrite.c, 2.0L/io/controller.c
omObjData *HuAudFadeObj BSS; // audio.c, objmain.c, objsysobj.c
s16 kakusiMasuStarHisIdx BSS; // overlays only
u16 printWinNum BSS; // printfunc.c
s16 mbEndingF BSS; // overlays only
s8 omPadStkX[4] BSS; // audio.c
u8 CharAnimWorkNum[6] BSS; // hmfspr.c
u16 omHu3DMtxNum BSS; // gameman.c, objmain.c
u8 omSysPauseDisableF BSS; // gamemes.c, objmain.c
u8 D_800D6A59_main BSS; // unreferenced
s16 D_800D6A5A_main BSS; // unreferenced
u8 __rmonRcpAtBreak BSS; // 2.0L/rmon/rmonbrk.c, 2.0L/rmon/rmontask.c
OSMesgQueue __rmonMQ BSS; // 2.0L/rmon/rmonmain.c, 2.0L/rmon/rmonmisc.c
Vec CUp BSS; // objsysobj.c
Gfx *extraGfxPos ALIGNED(8) BSS; // hmfdraw.c
u32 __osRdb_IP6_Ct BSS; // 2.0L/os/initrdb.c, 2.0L/os/rdbsend.c
u8 omAllPauseF BSS; // objmain.c, window.c
s16 D_800D6A92_main BSS; // hmfdraw.c
Vtx *Hu3DVtxBuf[8] ALIGNED(8) BSS; // hmfdraw.c
s32 omSysTimerMax BSS; // objsysobj.c
Vec Center BSS; // gameman.c, objsysobj.c
s16 Hu3DDrawListNum[8] BSS; // hmfdraw.c
s16 D_800D6AD8_main BSS; // unreferenced
s16 pauseSprGrp BSS; // pause.c
Vec CRotM[6] ALIGNED(8) BSS; // gameman.c, objsysobj.c; contains D_800D6AE4_main
OSMesgQueue piMesgQueue BSS; // rom.c
s16 omnextidx BSS; // objmain.c
OSMesgQueue __osSiAccessQueue ALIGNED(8) BSS; // 2.0L/io/siacs.c
s16 mbovlhisidx BSS; // overlays only
s16 winPrio BSS; // window.c
s16 Hu3DFogStart BSS; // hmfdraw.c, hmfman.c
HuMallocHeader *gFirstMallocBlock BSS; // mallocblock.c
u8 D_800D6B6C_main[0x4] BSS; // unreferenced
