#include "common_duel.h"
#include "game/object.h"
#include "game/board.h"
#include "game/window.h"
#include "game/malloc.h"

typedef void (*PartnerFunc)(s32, s32, Object*, Object*, s32, s32);

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
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Object* unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} UnkBoard5; //sizeof 0x20

typedef struct UnkOvl81_2 {
    /* 0x00 */ Object* obj;
    /* 0x04 */ Process* process;
    /* 0x08 */ s16 win_id;
    /* 0x0A */ s16 unk_0A;
} UnkOvl81_2; //sizeof 0xC

// Duel help window, counterpart of the board overlay's Unk3.
typedef struct DuelHelpWin {
    /* 0x00 */ u8 unk_00; // message index
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02; // x position, or -1 to center
    /* 0x04 */ s16 unk_04; // y position
    /* 0x08 */ omObjData* unk_08;
    /* 0x0C */ s16 winID;
    /* 0x10 */ char* unk_10;
} DuelHelpWin; //sizeof 0x14

typedef struct UnkC5770B70 {
    /* 0x00 */ s16 windowId;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 w;
    /* 0x08 */ s16 h;
} UnkC5770B70; // sizeof 0xA

// Space form image: a CI texture with a header, palette and texels.
typedef struct MasuBmp {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u32 palCount;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u16 data[1];
} MasuBmp;

typedef struct UnkD6B00 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Object *unk_04;
    /* 0x08 */ omObjData *unk_08;
} UnkD6B00; // sizeof 0xC

typedef struct NameSpriteIds {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02[2];
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} NameSpriteIds; // sizeof 0xC

typedef struct NamePlayerData {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 spriteGroup;
    /* 0x06 */ char unk_06[0x2];
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char unk_0A[0x2];
    /* 0x0C */ f32 xPos;
    /* 0x10 */ f32 yPos;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ omObjData *unk_2C;
    /* 0x30 */ char unk_30[0x4];
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ char unk_36[0x4];
    /* 0x3A */ s16 unk_3A[11];
    /* 0x50 */ s16 unk_50[11];
    /* 0x66 */ char unk_66[0x4];
    /* 0x6A */ s8 unk_6A;
    /* 0x6B */ s8 unk_6B;
} NamePlayerData; // sizeof 0x6C

typedef struct UnkE3CD0 {
    char unk_00[0xC];
    Vec unk_0C;
    char unk_18[0x18];
    f32 unk_30;
} UnkE3CD0;

#ifndef NO_EXTERN_VARIABLES
extern UnkBoard4* D_80105400_name_81;
extern u16 D_80105404_name_81;
extern PartnerBaseAttributes PartnersBaseStats[];
extern Object* mbdPartnerObj[][PARTNEROBJINDEX_MAX];
extern process_func D_80101A90_name_81;
extern s32 (*D_80101A94_name_81)(void);
extern void (*D_80101A98_name_81)(void);
extern s16 D_80105494_name_81;
extern s16 D_80105496_name_81;
extern s32 D_80101980_name_81;
extern s32 D_80101984_name_81;
extern Object* D_80101988_name_81;
extern void (*D_8010198C_name_81)(void);
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
extern Object* D_801029C0_name_81;
extern s16 D_801029C8_name_81[];
extern s16 D_80102BF0_name_81;
extern s16 D_80102BF2_name_81;
extern s16 D_80102BF4_name_81;
extern s16 D_80102BF6_name_81;
extern s16 D_80102BF8_name_81;
extern s16 D_80102BFA_name_81;
extern Vec D_80102C00_name_81;
extern Vec D_80102C0C_name_81;
extern Vec D_80102C18_name_81;
extern s16 duelUnkF0;
#endif

void MBDBackKill(void);
void MBDBackClose(void);
void func_800EBAD4_name_81(s16);
void func_800E9F4C_name_81(s16 spaceIdx, s8 *chainOut, s8 *linkOut);
void func_800E890C_name_81(Vec *, s32);
void func_800E24AC_name_81(s32, s32, s32, s32);
void func_800E18C0_name_81(void);
void func_800EB8B0_name_81(s16 playerNoOne, s16 playerNoTwo);
void func_800EB7BC_name_81(Vec *);
void func_800F3B54_name_81(s32 playerIndex, u8 cpuDifficulty);
void func_800F3B94_name_81(s32, Vec *);
Object *func_800EDD50_name_81(Vec *);
void func_800EE0F4_name_81(s32);
void func_800EDF48_name_81(void);
void func_800EDF78_name_81(void);
void func_800EDDBC_name_81(void);
void func_800EE74C_name_81(s32);
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
void func_800E9180_name_81(void);
void func_800E9190_name_81(void);
s32 func_800F37B8_name_81(s16 playerIndex);
void func_800F37E0_name_81(s32 playerIndex, s32 amount);
DuelHelpWin* func_800E1824_name_81(s16, s16, u16);
DuelHelpWin* func_800E172C_name_81(s16, s16, s16, u16);
void func_800E1854_name_81(DuelHelpWin*);
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
void MBDCameraPos3DGet(Vec2f*);
f32 MBDCameraSpeedGet(void);
void func_80100124_name_81(UnkBoard4*, s32);
Object* MBDModelFileCreate(s32, s32, f32, f32, u32*);
void func_800FCF50_name_81(s32, s32);
Process *func_800EBF2C_name_81(Vec *, Vec *, Vec *, s32);
void func_800EB680_name_81(s16 playerIdx, s16 spaceIdx, Vec *outCoords);
void func_800DC3AC_name_81(s32 playerIndex);
void func_800DC410_name_81(s32 playerIndex);
void func_800F3500_name_81(s32 playerIndex);
void func_800EB6C4_name_81(s16 playerIdx, s16 spaceIdx);
void func_800F40E4_name_81(void);
void func_800DC7CC_name_81(void);
void MBDModelAttrSetDispOn(Object*);
void MBDModelAttrSetDispOff(Object*);
f32 MBDBackMdlScaleGet(void);
void MBDModelDispOn(Object*);
void MBDModelKill(Object*);
Process *func_800DCC8C_name_81(s32 modelId, Vec *pos, Vec *vel, f32 scale, s32 delay, f32 speed);
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
s32 func_800F89D0_name_81(s32 playerIndex, s32 frontOrBackIndex, s16 arg2, u16 arg3);
void func_801007C4_name_81(void);
void func_800E5954_name_81(void);
void func_800E5964_name_81(void);
void func_801008E8_name_81(void);
void func_80100CA0_name_81(void);
void func_800DADA0_name_81(s32);
s32 func_800DB3E0_name_81(s32);
void func_800DB544_name_81(s32);
void func_800DB5AC_name_81(s32);
void func_800E5954_name_81(void);
void func_800E5BE8_name_81(void);
void func_800E5C20_name_81(void);
void func_800E856C_name_81(f32);
f32 func_800E8578_name_81(void);
s32 func_800F73AC_name_81(void);
void func_800F73C0_name_81(void);
void func_800F740C_name_81(void);
s16 func_800FC114_name_81(void);
void func_80100864_name_81(void);
void func_80100890_name_81(void);
UnkBoard4* func_800FFEEC_name_81(void);
void func_801000A4_name_81(UnkBoard4* arg0, u16 arg1);
void MBDCameraSpeedSet(f32);
s16 func_800EABBC_name_81(s16, s16*, s16);
UnkBoard4* func_800F4528_name_81(s16 arg0, s16 arg1);
void func_800F4584_name_81(UnkBoard4*);
void func_800E0310_name_81(u8 *, s32);
void func_800E4E64_name_81(UnkOvl81_2*);
UnkOvl81_2* func_800E4B64_name_81(s32, s32);
void func_800E4EAC_name_81(UnkOvl81_2*, s16, s16);
void func_800FAD04_name_81(s32 arg0);
void MBDModelDispOff(Object*);
Object* func_800D8B18_name_81(Object*);
void func_800D96F4_name_81(void);
void func_800D974C_name_81(Object*);
Object* MBDGetPlayerPartnerRef(s32 playerIndex, s32 frontOrBackIndex);
void func_800ECF1C_name_81(s32, Vec*, Vec*);
f32 func_800D7CEC_name_81(Vec *vec_1, Vec *vec_2);
f32 MBDVecAngleGet(Vec*);
void MBDVecNormalize(Vec*);
void MBDVecRotateY(Vec*, f32);
void MBDModelInit(void);
void MBDModelTempAllocFree(Object*);
void func_800DAB1C_name_81(void);
void func_800DF1B0_name_81(void);
void func_800E0CEC_name_81(void);
void func_800E2870_name_81(void);
void func_800E4F50_name_81(Addr arg0);
void MBDBackLoad(s32);
void func_800E8D10_name_81(void);
void func_800E94D0_name_81(void);
s32 func_800E9B10_name_81(s32, s16);
void func_800EA760_name_81(void);
void func_800ECD0C_name_81(s16 playerIdx, s16 nlink, s16 nidx);
void func_800ECD88_name_81(s16 playerIdx, s16 nlink, s16 nidx);
Process *func_800EBDDC_name_81(s16 playerIndex, s32 time, s16 spaceIndex);
void func_800ED788_name_81(s32 playerIndex);
void func_800ECDE8_name_81(void);
void func_800ECE10_name_81(void);
Process *func_800ED70C_name_81(s32 playerIdx, s32 arg);
Process *func_800EDC6C_name_81(s32 playerIdx, s32 arg);
UnkBoard2 *func_800D6B70_name_81(s32 arg0);
UnkEA790Struct *func_800D6C6C_name_81(void);
void func_800D6D2C_name_81(UnkEA790Struct *arg0, UnkBoard2 *arg1, u16 arg2);
UnkBoard2 *func_800D6EC8_name_81(UnkEA790Struct *arg0, s16 arg1);
UnkEA790Struct *func_800D76A0_name_81(s16 playerNo, s16 *choices);
s32 func_800D742C_name_81(UnkEA790Struct *win, s16 playerNo, s32 arg2);
s32 func_800D7250_name_81(UnkEA790Struct *win, s32 input);
s32 func_800D7518_name_81(UnkEA790Struct *win);
s16 func_800D97B0_name_81(DecisionTreeNonLeafNode *tree);
s16 func_800EB9D4_name_81(s8 percent);
s16 func_800EBA1C_name_81(void);
s32 func_800EFB3C_name_81(s32 playerIndex);
s32 func_800F3850_name_81(s32 playerIndex, s32 requiredCoins);
void func_800EB664_name_81(void);
void func_800EF840_name_81(void);
void func_800EF880_name_81(void);
void func_800F3DFC_name_81(s16 playerIndex);
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
void MBDPartnerObjClear(void);
void func_800F7FDC_name_81(void);
void func_800D898C_name_81(Object *arg0, u8 arg1);
s32 func_800F8AEC_name_81(s32 playerIndex, s32 arg1, s16 arg2, s16 arg3, s16 arg4, u16 flags);
Object* func_800D8010_name_81(u8, s32*);
Object* func_800F8034_name_81(s32);
Object* func_800F8050_name_81(s32);
void func_800F8108_name_81(s32 playerIndex);
void func_800F85A4_name_81(s32 playerIndex, s32 frontOrBackIndex);
void MBDMotionSet(Object*, s16, u16);
s16 MBDGetCurrentPlayerIndex(void);
void MBDMotionShiftSet(Object*, s16, s16, s16, u16);
s32 func_800EFE20_name_81(f32);
void func_800FB160_name_81(void);
void func_800FAEFC_name_81(s32);
void func_800FB038_name_81(Object*, s16, u16);
void func_800EB278_name_81(void);
void func_800EB29C_name_81(void);
void func_800EB58C_name_81(void);
void func_800FA120_name_81(void);
Process *func_800DCE40_name_81(s32, Vec *, Vec *, f32);
void func_800FC8C4_name_81(Vec *arg0);
void func_800EAB6C_name_81(s16, s32);

#ifndef NO_EXTERN_VARIABLES
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
#endif

Process *func_800D9668_name_81(Object *, f32, f32, s32);
void func_800E3C6C_name_81(void);
Process* func_800E415C_name_81(void);
Process* func_800E47B8_name_81(s32, s32, Vec*, Vec*, s32);
void func_800E5954_name_81(void);
void func_800E5964_name_81(void);
void MBDBackTPLvlSet(u8);
void func_800EAFC4_name_81(s32);
Process* func_800EC1E4_name_81(Vec*, Vec*, Vec*, f32);
Process* func_800EC36C_name_81(Vec*, Vec*, Vec*, f32);
void func_800EF7C8_name_81(Object *, f32, f32);
void func_800EF800_name_81(Object *);
void func_800FAE98_name_81(Object *, s16, s16, s16, s16);
void func_800EFA8C_name_81(Object*, s16, s32);
void func_800EFABC_name_81(Object*);
void func_800EFB00_name_81(Object*);
void func_800F0378_name_81(Object *obj, char *hookName, s16 model);
void MBDVecDirGet(Vec *, Vec *, Vec *);
void func_800EB804_name_81(Object *obj);
s32 func_800DD1E0_name_81(s32 dataNum, char *objName);
void func_800DD2BC_name_81(s32 model);
void func_800DD2DC_name_81(s32 model, Vec *pos);
s32 func_800DD3B4_name_81(s32 model);
Process *func_800DCB04_name_81(s32, s32, Vec *, f32, s32);
Process *func_800DCE10_name_81(s32, Vec *, Vec *, f32, s32);
void func_800FB0B8_name_81(Object*, s32, s32);
void func_800F57B0_name_81(s32);
void func_800F5E2C_name_81(s32);
s16 func_800EA6A4_name_81(void);
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
s32 func_800EF7D4_name_81(Object*);
SpaceData* MBDMasuGet(s16 spaceIdx);
void func_800F64FC_name_81(void);
Process *func_800E4A74_name_81(s32 arg0);
Process *func_800EE40C_name_81(s32 arg0);
void MBDPartnerPowerUp(s32 playerIndex);
void MBDPartnerPowerDown(s32 playerIndex);
void MBDPartnerPosSwap(s32 playerIndex);
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
u16 MBDMotionCheck(Object *);
u16 func_800D92A8_name_81(Object *);
Object *func_800EEC40_name_81(Vec *);
void func_800FC5B4_name_81(void (*)(void));
void func_800FD620_name_81(void);
Process *func_800DC324_name_81(s32 playerIndex);
Process *func_800E39AC_name_81(s32 playerIndex);
Process *func_800EBC60_name_81(Vec *from, Vec *to, Vec *out, s32 time);
void func_800EB7D8_name_81(s16 playerIdx);
void func_800ECC34_name_81(s16 playerIndex, f32 speed);
Process *func_800EDEC4_name_81(Object *obj, f32 arg1, f32 arg2);
void func_800F3AF4_name_81(s32 playerIndex, f32 arg1);
Process *func_800F41DC_name_81(void);
Process *func_800F429C_name_81(void);
s32 func_800F42C8_name_81(void);
void func_800D9F90_name_81(s32 playerIndex);
void func_800DB4DC_name_81(s32 arg0);
void func_800DB624_name_81(s32 arg0, s8 arg1);
s32 func_800DC0B4_name_81(s32 arg0);
void func_800E14B0_name_81(s32 arg0, s32 arg1);
void func_800E14D8_name_81(s32 arg0, s32 arg1);
void func_800EA388_name_81(s16 spaceIdx);
s32 func_800EA4D4_name_81(s16 spaceIdx, s16 activationType);
void func_800EA698_name_81(s16 spaceIdx);
void func_800EA788_name_81(s16 unk_17_value, s8 unk_2A_value);
s32 func_800EA848_name_81(s16 unk_17_value);
s32 func_800EA940_name_81(s32 playerIndex);
void func_800EAD08_name_81(s32 arg0);
void func_800ECE38_name_81(s32 playerIndex);
void func_800EE468_name_81(s32 arg0);
void func_800F397C_name_81(s32 playerIndex, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
void func_800F3A04_name_81(s32 playerIndex, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
void func_800F7378_name_81(s32 playerIndex, s32 coins);
void func_800F924C_name_81(s32 attackType);
void func_800FADB4_name_81(void);

#ifndef NO_EXTERN_VARIABLES
extern Object *D_80100F44_name_81;
#endif
