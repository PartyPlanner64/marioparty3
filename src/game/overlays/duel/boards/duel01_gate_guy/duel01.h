#include "common_duel.h"
#include "game/process.h"
#include "common_structs.h"
#include "game/malloc.h"
#include "game/board.h"
#include "game/overlays/duel/common/ovl_81.h"

typedef struct unkStruct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
} unkStruct;

typedef struct Duel01SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel01SpriteWork; // sizeof 0x10

typedef struct Duel01CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel01CamShakeWork; // sizeof 0x10

typedef struct Duel01WinColorWork {
    /* 0x00 */ s32 window;
    /* 0x04 */ char unk_04[0xC];
} Duel01WinColorWork; // sizeof 0x10

typedef struct Duel01PartnerAttackWork {
    /* 0x00 */ GW_PLAYER *player;
    /* 0x04 */ Object *obj;
    /* 0x08 */ s32 delay;
    /* 0x0C */ s32 waitTime;
} Duel01PartnerAttackWork; // sizeof 0x10

typedef struct Duel01PartnerRouletteWork {
    /* 0x00 */ s32 player;
    /* 0x04 */ char unk_04[0xC];
} Duel01PartnerRouletteWork; // sizeof 0x10

// Board space indices used when a player picks up a partner.
typedef struct Duel01PartnerSpaces {
    /* 0x00 */ s32 returnSpace;
    /* 0x04 */ s32 startSpace;
    /* 0x08 */ s32 partnerSpace;
} Duel01PartnerSpaces; // sizeof 0xC

typedef struct Duel01SwayWork {
    /* 0x00 */ s32 angle;
    /* 0x04 */ char unk_04[0xC];
} Duel01SwayWork; // sizeof 0x10

extern s16 omovlevtno;
f32 MBDVecAngleGet(Vec *);
s32 MBDCameraStopCheck(void);
// Defined in ovl_81_name with a u8 return, but callers here use the full register without masking.
s32 MBDTurnCoinGet(void);
void MBDVecDirGet(Vec *, Vec *, Vec *);
void MBD1_MissMarkProc(void); // probably takes object as arg
Process *MBDPlayerPosMoveCreate(Vec *, Vec *, Vec *, s32);
void MBD1_CameraShakeProc(void);
void MBDPlayerPartyMotionSet(s32, s32, s32);
void MBD1_ObjectSetup(void);
void MBD1_GateGuyCreate(void);
void MBD1_PartnerBox1Create(void);
void MBD1_PartnerBox2Create(void);
void MBD1_GateCreate(s16);
void MBD1_GateCreateAll(void);
void MBDStart(s32);
void MBD1_KoopaFireObjMain(omObjData *);
void MBD1Ev_PartnerBox1SquashProc(void);
void MBD1Ev_PartnerBox2SquashProc(void);
void MBD1_GateOpen(s32);
void MBD1Ev_PartnerGetExec(s32);
void MBD1Ev_StartWarpLinkGet(s8 *, s8 *);
void MBD1_DodgeProc(void);
void MBD1_NokonokoAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_KuriboAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_KinopioAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_BomheiAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_WhompAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_DossunAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_TeresaAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_BlizzardAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_KoopaJrAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_WanwanAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_SnifitAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1_PakkunAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD1Ev_PartnerBox1SwayProc(void);
void MBD1Ev_PartnerBox2SwayProc(void);
void MBD1Ev_Hatena(void);
s32 MBD1_WalkAttackHook(void);
void MBD1Ev_GateGuyWarpExec(void);
void MBDPartnerAttackFuncSet(PartnerFunc *, PartnerFunc *);
void MBDMasuEventTblAdd(event_table_entry *);
void MBDHatenaFuncSet(process_func);
void MBDWalkAttackHookSet(s32 (*)(void));
void MBDItemWarpBlockSwapInit(void);
void MBDItemWarpBlockSwapPlayerSet(void);
void MBDItemWarpBlockSwapCreate(void);
void MBDCoinChangeCreate(s32, s32);
void MBDCoinTakeCreate(s32, s32);
void MBDPartnerAttackMotSet(Object *, s32, s32);
void MBDPartnerAttackMotKill(void);
Object *MBDAuraCreate(Vec *);
void MBDAuraLandNoSe(s32);
void MBDAuraHoverStart(void);
void *MBDPlayerVibrateObjCreate(s16, s16, s32);
void MBDAuraSpinExec(s32);
void MBDPlayerVibrateObjKill(void *);
void MBDAuraHoverStop(void);
void MBDAuraRiseExec(s32);
void MBDAuraKill(void);
void MBDPlayerMotionSet(s32, s32, s32);
extern s32 mbKSuitObj[];
Process *MBDMgCallListProcCreate(void);
Process *MBDEffMdlCreate(s32, Vec *, Vec *, f32);
s32 MBD1_ComPartnerRefuseRateGet(void);
Process *MBDCoinScatterCreate(Object *, s32, s32, s32, s32);
void MBD1Ev_PartnerRouletteProc(void);
void MBD1Ev_PartnerRouletteWinColorProc(void);
void MBDCameraFocusObjSet(Object *);
void MBDVecForwardSet(Vec *);
Process *MBDVecRotLerpCreate(Vec *, Vec *, Vec *, s32);
void MBDBranchArrowGrpKill(UnkEA790Struct *win);
