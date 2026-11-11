#include "common.h"
#include "game/object.h"
#include "game/board.h"
#include "game/window.h"
#include "game/malloc.h"

// Duel mode's copy of the board model object (Object). The duel overlay has its
// own model functions (MBD*), which add a motion count at 0x44 and shift
// Object's unk44/unk46 to 0x46/0x48.
typedef struct ObjectDuel {
    /* 0x00 */ struct ObjectDuel *prev;
    /* 0x04 */ struct ObjectDuel *next;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ s8 unk9;
    /* 0x0A */ u16 flags;
    /* 0x0C */ Vec coords;
    /* 0x18 */ Vec rot;
    /* 0x24 */ Vec scale;
    /* 0x30 */ Vec velocity;
    /* 0x3C */ omObjData* omObj1;
    /* 0x40 */ omObjData* omObj2;
    /* 0x44 */ s16 mtncnt; // -1 when the model has no motion table
    /* 0x46 */ s16 unk46; // Object::unk44
    /* 0x48 */ s16 unk48; // Object::unk46
} ObjectDuel; // sizeof 0x4C

typedef void (*PartnerFunc)(s32, s32, ObjectDuel*, ObjectDuel*, s32, s32);

typedef enum PartnerObjIndex {
    /* 0 */ PARTNEROBJINDEX_FRONT,
    /* 1 */ PARTNEROBJINDEX_BACK,
    /* 2 */ PARTNEROBJINDEX_MAX = MBD_MAX_PLAYERS,
} PartnerObjIndex;

#define POWERUP_NONE 1
#define POWERUP_ACTIVE 2

#define PARTNER_FRONT 0
#define PARTNER_BACK 1

typedef struct PartnerBaseAttributes {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 hp;
    /* 0x02 */ s8 power;
    /* 0x03 */ s8 cost;
    /* 0x04 */ PartnerFunc func1;
    /* 0x08 */ PartnerFunc func2;
    /* 0x0C */ void (*func3)(void);
    /* 0x10 */ void (*func4)(void);
} PartnerBaseAttributes; //sizeof 0x14

typedef struct UnkBoard4 {
    /* 0x00 */ struct UnkBoard4* unk_00; //TODO: is this correct?
    /* 0x04 */ struct UnkBoard4* unk_04; //TODO: is this correct?
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16* unk_0C;
    /* 0x10 */ f32* unk_10;
    /* 0x14 */ f32* unk_14;
    /* 0x18 */ s16* unk_18;
    /* 0x1C */ s16* unk_1C;
} UnkBoard4; //sizeof 0x20

typedef struct UnkBoard5 {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s16* unk_0C;
    /* 0x10 */ f32* unk_10;
    /* 0x14 */ f32* unk_14;
    /* 0x18 */ s16* unk_18;
    /* 0x1C */ s16* unk_1C;
} UnkBoard5; //sizeof 0x20

typedef struct UnkOvl81_2 {
    /* 0x00 */ ObjectDuel* obj;
    /* 0x04 */ Process* process;
    /* 0x08 */ s16 win_id;
} UnkOvl81_2; //sizeof 0xC

extern UnkBoard4* D_80105400_name_81;
extern u16 D_80105404_name_81;
extern PartnerBaseAttributes PartnersBaseStats[];
extern ObjectDuel* Duel_PartnerObjects[][PARTNEROBJINDEX_MAX];
extern process_func D_80101A90_name_81;
extern s32 D_80101A94_name_81;
extern s32 D_80101A98_name_81;
extern s16 D_80105494_name_81;
extern s16 D_80105496_name_81;
extern u8* D_80101980_name_81;
extern s32 D_80101984_name_81;
extern ObjectDuel* D_80101988_name_81;
extern s32* D_801017DC_name_81[];
extern Process* D_8010195C_name_81;
extern s32* D_8010180C_name_81[];
extern s16 D_80101990_name_81;
extern s16 D_80105470_name_81[];
extern s32* D_8010183C_name_81[];
extern s16 D_80105480_name_81[];
extern s16 D_80101992_name_81;
extern s32 D_80101998_name_81[];
extern s16 D_801019C8_name_81[];
extern s16 D_8010555C_name_81;
extern s16 D_801011D0_name_81;
extern s16 D_801011D2_name_81;
extern Process* D_801011F4_name_81;
extern u8 D_80101370_name_81[];
extern ObjectDuel* D_801029C0_name_81;
extern s16 D_801029C8_name_81[];
extern s16 D_80102BF0_name_81;
extern s16 D_80102BF2_name_81;

void MBDBackKill(void);
void MBDBackClose(void);
void func_800EBAD4_name_81(s32);
void func_800E9F4C_name_81(s32, s8 *, s8 *);
void func_800E890C_name_81(Vec *, s32);
void func_800E24AC_name_81(s32, s32, s32, s32);
void func_800FC5D8_name_81(void);
void func_800FC4E4_name_81(void);
void func_800FC108_name_81(void);
void MBDModelClose(void);
void func_800DBEB0_name_81(void);
void func_800DF210_name_81(void);
void func_800E0E38_name_81(void);
void func_800E28B0_name_81(void);
void func_800E4FF4_name_81(void);
void func_800E90B4_name_81(void);
void func_800E9564_name_81(void);
void func_800E9D9C_name_81(void);
void func_800F4030_name_81(void);
void func_800F4314_name_81(void);
void func_800FD55C_name_81(void);
void func_800DAAB0_name_81(void);
void func_800DF154_name_81(void);
s32 func_800F37B8_name_81(s16 playerIndex);
s32 func_800E1824_name_81(s32, s32, s32);
s32 func_800E172C_name_81(s32, s32, s32, s32);
void func_800E1854_name_81(s32);
Process* func_800E0888_name_81(void);
void func_800EDE1C_name_81(void);
void func_800EE114_name_81(void);
void func_80100CEC_name_81(s32 padIdx);
void func_800E5954_name_81(void);
void func_800E5BE8_name_81(void);
void func_800E5C20_name_81(void);
void func_800E856C_name_81(f32);
void MBDCameraSpeedSet(f32);
f32 MBDCameraSpeedGet(void);
void MBDCameraZoomSet(f32);
void MBDCamera3Dto2D(Vec*, Vec2f*);
f32 MBDCameraZoomGet(void);
Process* MBDCameraZoomMotStart(f32);
u16 MBDCameraPos3DSet(Vec*);
u16 MBDCameraPos2DSet(Vec2f*);
void MBDCameraPos2DGet(Vec2f*);
f32 MBDCameraSpeedGet(void);
void func_80100124_name_81(UnkBoard4*, s32);
ObjectDuel* MBDModelFileCreate(s32, s32, f32, f32, u32*);
void func_800FCF50_name_81(s32, s32);
void MBDModelAttrSetDispOn(ObjectDuel*);
void MBDModelDispOn(ObjectDuel*);
void MBDModelKill(ObjectDuel*);
void func_800DCC8C_name_81(s32, Vec *, Vec *, f32, s32, f32);
void func_800EA8DC_name_81(void);
void func_800EA97C_name_81(void);
void func_800FC260_name_81(s32 arg0, s16 arg1, s32 arg2);
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
void func_800E27D4_name_81(s32 playerIndex, Vec *pos, Vec *pos1, Vec *pos2);
void func_800EA7D4_name_81(void);
void func_800EA898_name_81(s32 playerIndex, s32 newPlayerIndex);
void func_800FAC1C_name_81(Vec *);
void func_800EB140_name_81(s16, s32);
void func_800F8C68_name_81(s32);
void func_800F8CD8_name_81(s32 playerIndex, f32 arg1);
void func_80100604_name_81(void);
s32 func_800F89D0_name_81(s32 playerIndex, s32 frontOrBackIndex, s16 arg2, s16 arg3);
void func_801007C4_name_81(void);
void func_800E5954_name_81(void);
void func_800E5964_name_81(void);
void func_801008E8_name_81(void);
void func_80100CA0_name_81(void);
void func_800DADA0_name_81(s32);
s32 func_800DB3E0_name_81(s32);
void func_800DB544_name_81(s32);
void func_800DB5AC_name_81(s32);
s32 func_800E1824_name_81(s32, s32, s32);
void func_800E1854_name_81(s32);
void func_800E5954_name_81(void);
void func_800E5BE8_name_81(void);
void func_800E5C20_name_81(void);
void func_800E856C_name_81(f32);
f32 func_800E8578_name_81(void);
void func_800F73C0_name_81(void);
void func_800F740C_name_81(void);
s16 func_800FC114_name_81(void);
void func_80100864_name_81(void);
void func_80100890_name_81(void);
UnkBoard4* func_800FFEEC_name_81(void);
void func_801000A4_name_81(UnkBoard4* arg0, u16 arg1);
void MBDCameraSpeedSet(f32);
s16 func_800EABBC_name_81(s16, s16*, s16);
void func_800EED68_name_81(s16, s32);
void func_800EF3B4_name_81(s16);
UnkBoard4* func_800F4528_name_81(s16 arg0, s16 arg1);
s32 func_800E1824_name_81(s32, s32, s32);
void func_800E1854_name_81(s32);
void func_800F4584_name_81(UnkBoard4*);
void func_800E0310_name_81(u8 *, s32);
void func_800E4E64_name_81(UnkOvl81_2*);
UnkOvl81_2* func_800E4B64_name_81(s32, s32);
void func_800E4EAC_name_81(UnkOvl81_2*, s32, s32);
void func_800FAD04_name_81(s32 arg0);
void MBDModelDispOff(ObjectDuel*);
ObjectDuel* func_800D8B18_name_81(ObjectDuel*);
void func_800D96F4_name_81(void);
void func_800D974C_name_81(ObjectDuel*);
ObjectDuel* MBDGetPlayerPartnerRef(s32 playerIndex, s32 frontOrBackIndex);
void func_800ECF1C_name_81(s32, Vec*, Vec*);
f32 MBDVecAngleGet(Vec*);
void MBDVecNormalize(Vec*);
void MBDVecRotateY(Vec*, f32);
void MBDModelInit(void);
void MBDModelTempAllocFree(ObjectDuel*);
void func_800DAB1C_name_81(void);
void func_800DF1B0_name_81(void);
void func_800E0CEC_name_81(void);
void func_800E2870_name_81(void);
void func_800E4F50_name_81(Addr arg0);
void MBDBackLoad(s32);
void func_800E8D10_name_81(void);
void func_800E94D0_name_81(void);
void func_800E9B10_name_81(s32, s16);
void func_800EA760_name_81(void);
void func_800ECD0C_name_81(s16 playerIdx, s16 nlink, s16 nidx);
void func_800ECD88_name_81(s16 playerIdx, s16 nlink, s16 nidx);
Process *func_800EBDDC_name_81(s16 playerIndex, s32 time, s16 spaceIndex);
void func_800ED788_name_81(s32 playerIndex);
void func_800ECDE8_name_81(void);
void func_800ECE10_name_81(void);
Process *func_800ED70C_name_81(s32 playerIdx, s32 arg);
Process *func_800EDC6C_name_81(s32 playerIdx, s32 arg);
void *func_800D6B70_name_81(s32 arg0);
UnkEA790Struct *func_800D6C6C_name_81(void);
void func_800D6D2C_name_81(UnkEA790Struct *arg0, UnkBoard2 *arg1, u16 arg2);
UnkBoard2 *func_800D6EC8_name_81(UnkEA790Struct *arg0, s16 arg1);
UnkEA790Struct *func_800D76A0_name_81(s16 playerNo, s16 *choices);
s32 func_800D742C_name_81(UnkEA790Struct *win, s16 playerNo, s32 arg2);
s32 func_800D7250_name_81(UnkEA790Struct *win, s32 input);
s32 func_800D7518_name_81(UnkEA790Struct *win);
s16 func_800D97B0_name_81(DecisionTreeNonLeafNode *tree);
void func_800EB664_name_81(void);
void func_800EF840_name_81(void);
void func_800EF880_name_81(void);
void func_800F3DFC_name_81(s32);
void func_800F3F4C_name_81(void);
void func_800F4080_name_81(void);
void func_800F4300_name_81(void);
void func_800F5BB4_name_81(s32 playerIndex);
void func_800F5EB0_name_81(s32);
void func_800F6390_name_81(void);
void func_800FC198_name_81(omObjData*);
void func_800E8180_name_81(f32, f32);
void func_800E4F50_name_81(Addr arg0);
void func_800E8110_name_81(void);
void func_800E8180_name_81(f32, f32);
void func_800EC6F4_name_81(void);
void func_800EC99C_name_81(void);
void func_800ED214_name_81(s32 playerIndex);
void func_800ED31C_name_81(void);
void func_800ED520_name_81(void);
void func_800ED7EC_name_81(void);
void func_800EDA38_name_81(void);
void func_800F0FE8_name_81(void);
void func_800F82EC_name_81(s32);
ObjectDuel* func_800D8010_name_81(u8, s32*);
ObjectDuel* func_800F8034_name_81(s32);
ObjectDuel* func_800F8050_name_81(s32);
void func_800F8108_name_81(s32 playerIndex);
void func_800F85A4_name_81(s32 playerIndex, s32 frontOrBackIndex);
void MBDMotionSet(ObjectDuel*, s16, u16);
s16 MBDGetCurrentPlayerIndex(void);
void MBDMotionShiftSet(ObjectDuel*, s16, s16, s16, u16);
s32 func_800EFE20_name_81(f32);
void func_800FB160_name_81(void);
void func_800FAEFC_name_81(s32);
void func_800FB038_name_81(ObjectDuel*, s16, u16);
void func_800EB278_name_81(void);
void func_800EB29C_name_81(void);
void func_800EB58C_name_81(void);
void func_800FA120_name_81(void);
void func_800FC8C4_name_81(Vec *arg0);
void func_800EAB6C_name_81(s32, s32);

extern Vec D_80105460_name_81;
extern s32 D_801019E0_name_81[][2];
extern s32 D_80101A08_name_81[];
extern s32 D_80101A1C_name_81[];
extern s16 D_80101992_name_81;
extern s16 D_80101994_name_81;
extern s8* D_80101968_name_81;
extern s8* D_8010196C_name_81;
extern s8* D_80101970_name_81;
extern s8* D_80101974_name_81;
extern s8* D_80101978_name_81;
extern s8* D_8010197C_name_81;
extern Vec D_80105540_name_81;
extern s32 D_8010554C_name_81;
extern s32 D_80105550_name_81;
extern s32 D_80105558_name_81;
extern s32 D_80105620_name_81;
extern s32 D_8010570C_name_81;
extern s32 D_80105718_name_81;
extern s32 D_8010571C_name_81;

Process *func_800D9668_name_81(ObjectDuel *, f32, f32, s32);
void func_800E3C6C_name_81(void);
Process* func_800E415C_name_81(void);
Process* func_800E47B8_name_81(s16, s8, Vec*, Vec*, s32);
void func_800E5954_name_81(void);
void func_800E5964_name_81(void);
void MBDBackTPLvlSet(u8);
void func_800EAFC4_name_81(s32);
Process* func_800EC1E4_name_81(Vec*, Vec*, Vec*, f32);
Process* func_800EC36C_name_81(Vec*, Vec*, Vec*, f32);
void func_800EF7C8_name_81(ObjectDuel *, f32, f32);
void func_800EF800_name_81(ObjectDuel *);
void func_800FAE98_name_81(ObjectDuel *, s16, s16, s16, s16);
u32 func_800EFA8C_name_81(ObjectDuel*, s16, s16);
void func_800EFABC_name_81(void*);
void func_800EFB00_name_81(ObjectDuel*);
void func_800F0378_name_81(ObjectDuel *obj, char *hookName, s16 model);
void MBDVecDirGet(Vec *, Vec *, Vec *);
void func_800EB804_name_81(ObjectDuel *obj);
s32 func_800DD1E0_name_81(s32 dataNum, char *objName);
void func_800DD2BC_name_81(s32 model);
void func_800DD2DC_name_81(s32 model, Vec *pos);
s32 func_800DD3B4_name_81(s32 model);
Process *func_800DCB04_name_81(s32, s32, Vec *, f32, s32);
Process *func_800DCE10_name_81(s32, Vec *, Vec *, f32, s32);
void func_800FB0B8_name_81(ObjectDuel*, s32, s32);
void func_800F57B0_name_81(s32);
void func_800F5E2C_name_81(s32);
s32 func_800EA6A4_name_81(void);
void func_800F74E4_name_81(s32);
void func_800F75EC_name_81(s32);
void func_800F8358_name_81(s32);
void func_800F8D9C_name_81(s32, s32*, s32*);
void func_800F8EB8_name_81(u32 partnerID, s32 arg1, s32* damageAmount, s32* arg3, s32 arg4);
void func_800FAB1C_name_81(void);
void func_800FAC4C_name_81(void);
void func_800FAEE8_name_81(void);
void func_800FAFAC_name_81(void);
void func_800FC888_name_81(s32);
void func_800FC8C4_name_81(Vec *arg0);
Vec* func_800FC8D0_name_81(void);
void func_800FFAE0_name_81(s16, s16);
void func_800EB49C_name_81(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_800EB4DC_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_800D85A8_name_81(f32);
void func_800D87DC_name_81(f32);
void func_800EF3EC_name_81(s32);
s32 func_800EF7D4_name_81(ObjectDuel*);
SpaceData* MBDMasuGet(s16 spaceIdx);
void func_800F64FC_name_81(void);
Process *func_800E4A74_name_81(s32 arg0);
Process *func_800EE40C_name_81(s32 arg0);
void Duel_PowerUpPartners(s32 playerIndex);
void Duel_PowerDownPartners(s32 playerIndex);
void Duel_SwapPartnerPositions(s32 playerIndex);
void func_800DD41C_name_81(Vec *);
void func_800DD554_name_81(void);
void func_800DD564_name_81(void);
void func_800DD570_name_81(void);
void func_800EE0D0_name_81(s32);
void func_800EB1D8_name_81(s16, s32);
s32 func_800EED50_name_81(void);
void func_800FB524_name_81(s32 playerIndex);
void func_800ED118_name_81(s32, Vec *, Vec *);
void func_800F8418_name_81(s32, s32, s32);
void func_800F821C_name_81(s32, s32);
void func_800F7BB4_name_81(s32, s32);
void func_800F7D94_name_81(s32, s32);
void func_800FBDD4_name_81(void);
void func_800EADBC_name_81(s32, char *, s32, s32, s32, s32);
void func_800EAF70_name_81(s32);
void func_800EAF94_name_81(void);
s32 func_800F8980_name_81(s32 playerIndex);
u16 MBDMotionCheck(ObjectDuel *);
void func_800EEC40_name_81(Vec *);
void func_800FC5B4_name_81(void (*)(void));
void func_800FD620_name_81(void);

extern ObjectDuel *D_80100F44_name_81;
