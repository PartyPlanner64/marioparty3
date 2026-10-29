#include "common.h"
#include "game/hmfman.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/util.h"
#include "mallocblock.h"
#include "overlays/minigame.h"
#include "hand_line_sinker.h"

typedef struct HandLineSinkerObjWork {
    /* 0x000 */ f32 unk0;
    /* 0x004 */ f32 unk4;
    /* 0x008 */ f32 unk8;
    /* 0x00C */ Vec pos;
    /* 0x018 */ Vec unk18;
    /* 0x024 */ s16 unk24;
    /* 0x026 */ char unk26[0x28 - 0x26];
    /* 0x028 */ FishingLine *line;
    /* 0x02C */ s16 numPoints;
    /* 0x030 */ Vec points[32];
    /* 0x1B0 */ f32 unk1B0;
    /* 0x1B4 */ f32 unk1B4;
    /* 0x1B8 */ omObjData *unk1B8;
    /* 0x1BC */ f32 unk1BC;
    /* 0x1C0 */ u16 unk1C0;
    /* 0x1C4 */ f32 unk1C4;
    /* 0x1C8 */ s16 unk1C8;
    /* 0x1CA */ s16 unk1CA;
    /* 0x1CC */ s16 seNo;
    /* 0x1CE */ s16 unk1CE;
    /* 0x1D0 */ u16 unk1D0;
} HandLineSinkerObjWork; // sizeof 0x1D4

typedef struct HandLineSinkerPlayerWork {
    /* 0x00 */ s8 playerNo;
    /* 0x01 */ char unk1[0x4 - 0x1];
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u16 aiWait;
    /* 0x0E */ char unkE[0x10 - 0xE];
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 pressTimer;
    /* 0x14 */ omObjData *lineObj;
    /* 0x18 */ char unk18[0x1C - 0x18];
    /* 0x1C */ FishingLine *line;
    /* 0x20 */ f32 flyRot;
    /* 0x24 */ f32 flyVelY;
    /* 0x28 */ f32 velY;
    /* 0x2C */ u16 splashed;
    /* 0x2E */ u16 aiState;
    /* 0x30 */ f32 aiTargetRot;
    /* 0x34 */ f32 aiPrevRot;
    /* 0x38 */ u16 aiTimer;
    /* 0x3A */ u16 aiBtn;
    /* 0x3C */ u16 aiCastTimer;
    /* 0x40 */ omObjData *aiTarget;
    /* 0x44 */ f32 aiAimOffset;
} HandLineSinkerPlayerWork; // sizeof 0x48

typedef struct HandLineSinkerFollowWork {
    /* 0x00 */ omObjData *parent;
    /* 0x04 */ Vec offset;
    /* 0x10 */ Vec unk10;
} HandLineSinkerFollowWork; // sizeof 0x1C

extern s16 D_8010C0EC_hand_line_sinker;
extern s16 D_8010C0F0_hand_line_sinker;
extern omObjData *D_8010C0F4_hand_line_sinker;
extern omObjData *D_8010C0F8_hand_line_sinker;
extern u16 D_8010C10C_hand_line_sinker;
extern u16 D_8010C0E8_hand_line_sinker;
extern u16 D_8010BF60_hand_line_sinker;
extern omObjData **D_8010C100_hand_line_sinker;
extern s32 D_8010BFA0_hand_line_sinker[];
extern s16 D_8010C148_hand_line_sinker[2][6];
extern omObjData *D_8010C160_hand_line_sinker[];
extern omObjFunc D_8010BFA8_hand_line_sinker[];
extern u16 D_8010C104_hand_line_sinker[2];
extern f32 D_8010C108_hand_line_sinker;
extern u8 D_800D6A90_main;
extern f32 D_8010C130_hand_line_sinker;
extern f32 D_8010C134_hand_line_sinker;
extern f32 D_8010C138_hand_line_sinker;
extern f32 D_8010C13C_hand_line_sinker;
extern f32 D_8010C140_hand_line_sinker;
extern omObjData *D_8010C0E0_hand_line_sinker;
extern u16 D_8010C0EE_hand_line_sinker;
extern omObjData *D_8010C0FC_hand_line_sinker;
extern CameraPreset D_8010C110_hand_line_sinker;
extern omObjData *D_8010C190_hand_line_sinker;
extern CameraPreset D_8010BF28_hand_line_sinker;
extern s16 D_8010C12C_hand_line_sinker;
extern u16 D_8010C0EA_hand_line_sinker;
extern D_80111B50_vine_with_me_Struct D_8010BF00_hand_line_sinker;
extern const s16 D_8010BFB0_hand_line_sinker[];
extern s16 D_800EB930_minigame;
extern f32 D_8010C0E4_hand_line_sinker;
extern CameraPreset D_8010BF44_hand_line_sinker;
extern u8 D_8010BF18_hand_line_sinker;
extern s32 D_800A178C_main[][6];
extern s32 D_8010BF64_hand_line_sinker[];
extern char *D_8010BF88_hand_line_sinker;
extern u16 D_8010BF9C_hand_line_sinker;

void func_80105D28_hand_line_sinker(omObjData *);
void func_80105CF0_hand_line_sinker(omObjData *arg0);
void func_80105EE8_hand_line_sinker(omObjData *obj);
void func_80106040_hand_line_sinker(omObjData *obj);
void func_80106070_hand_line_sinker(omObjData *obj);
void func_801060A0_hand_line_sinker(omObjData *obj);
void func_801060D0_hand_line_sinker(omObjData *obj);
void func_8010B5B0_hand_line_sinker(void);
void func_8010A5F0_hand_line_sinker(void);
s32 func_800329B4_main(void *data);
void func_80045C2C_main(void);
void func_80047C0C_main(u16 group, u16 max_objs);
void omAddMember(u16 group, omObjData *obj);
omObjData **func_80047DBC_main(s16 arg0);
void func_8001766C_main(void);
void func_80105FA4_hand_line_sinker(omObjData *obj);
void func_8001E888_main(s16 model, f32 x, f32 y, u16 arg3, u16 arg4, char *name, s32 arg6);
void func_800335BC_main(char *name, u16 *result);
void func_80106100_hand_line_sinker(omObjData *obj, u16 playerNo);
f32 func_8010ABD4_hand_line_sinker(f32 a);
void func_801081D0_hand_line_sinker(omObjData *obj);
void func_8010A6D0_hand_line_sinker(omObjData *parent, u16 type, Vec *offset, Vec *rot);
omObjData *func_8010A554_hand_line_sinker(void);
void func_800E6F0C_minigame(s32);
void func_80109584_hand_line_sinker(omObjData *obj);
void func_80109B9C_hand_line_sinker(omObjData *obj);
void func_8010689C_hand_line_sinker(omObjData *obj);
void func_80107B24_hand_line_sinker(omObjData *obj);
void func_80107420_hand_line_sinker(omObjData *obj, s8 *stickX, s8 *stickY, u16 *btn);
void func_80108880_hand_line_sinker(omObjData *obj, s8 *stickX, s8 *stickY, u16 *btn);
f32 func_801092B8_hand_line_sinker(s8 stickX, s8 stickY);
void func_801093A4_hand_line_sinker(omObjData *obj);
void func_8010BA64_hand_line_sinker(void);
omObjData *func_80107A3C_hand_line_sinker(void);
omObjData *func_801080F0_hand_line_sinker(omObjData *arg0);
void func_80047E90_main(omObjData *obj, s32 arg1);
void func_8010AD7C_hand_line_sinker(omObjData *obj, f32 length, f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1);
void func_8010B0FC_hand_line_sinker(omObjData *arg0, f32 arg1);
void func_8000CFD8_main(s16 arg0, s32 arg1);
void func_8010BB58_hand_line_sinker(FishingLine *line, Vec *points, u16 count);
void func_8010B1E4_hand_line_sinker(omObjData *obj);
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
s32 func_80017B6C_main(s16 chr, s16 arg1, s16 arg2);
void func_8001EF6C_main(s16, s16, char *);

void func_801059A0_hand_line_sinker(void) {
    omObjData *players[4];
    void *data;
    s32 i;

    omInitObjMan(26, 0);
    func_8004A208_main();
    data = DataRead(0x220015);
    D_8010C12C_hand_line_sinker = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_800142A0_main(9);
    Hu3DBGColorSet(0, 40, 120);
    D_800CD280_main = 1;
    func_8010B5B0_hand_line_sinker();
    func_8010A5F0_hand_line_sinker();
    func_80045C2C_main();
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x40, 0x40, 0x60);
    HmfLightDirSet(0, 92.0f, 79.0f, 22.0f);
    HmfLightStatSet(0, 1, 1);
    HmfLightColorSet(2, 0x64, 0xFF, 0xFF);
    HmfLightDirSet(2, -115.0f, 6.0f, -33.0f);
    HmfLightStatSet(2, 1, 1);
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            D_8010C0EA_hand_line_sinker = i;
            break;
        }
    }
    omAddObj(0, 0, 0, -1, func_80105CF0_hand_line_sinker);
    omAddObj(6, 6, 0, -1, func_80105EE8_hand_line_sinker);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    players[0] = omAddObj(20, 6, 18, -1, func_80106040_hand_line_sinker);
    players[1] = omAddObj(20, 6, 18, -1, func_80106070_hand_line_sinker);
    players[2] = omAddObj(20, 6, 18, -1, func_801060A0_hand_line_sinker);
    players[3] = omAddObj(20, 6, 18, -1, func_801060D0_hand_line_sinker);
    func_80047C0C_main(0, 4);
    for (i = 0; i < 4; i++) {
        if (i == D_8010C0EA_hand_line_sinker) {
            D_8010C0FC_hand_line_sinker = players[i];
        } else {
            omAddMember(0, players[i]);
        }
    }
    D_8010C100_hand_line_sinker = func_80047DBC_main(0);
    func_80045010_main(D_8010BFB0_hand_line_sinker, 1);
    func_800E5EA0_minigame(&D_8010BF00_hand_line_sinker);
    D_800EB930_minigame = 45;
    func_8001766C_main();
}

void func_80105CF0_hand_line_sinker(omObjData *arg0) {
    D_8010C0EC_hand_line_sinker = 0;
    D_8010C0F8_hand_line_sinker = 0;
    D_8010C0F4_hand_line_sinker = 0;
    D_8010C0F0_hand_line_sinker = 0;
    D_8010C10C_hand_line_sinker = 0;
    arg0->func = func_80105D28_hand_line_sinker;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", D_8010BFB0_hand_line_sinker);

void func_80105D28_hand_line_sinker(omObjData *obj) {
    HandLineSinkerPlayerWork *work;

    if (D_8010BF60_hand_line_sinker == 0) {
        switch (func_800E6F40_minigame()) {
            case 0:
                if (D_8010C0F4_hand_line_sinker == NULL) {
                    D_8010C0EE_hand_line_sinker = 0;
                    D_8010C0F4_hand_line_sinker = omAddObj(4, 0, 0, -1, func_801093A4_hand_line_sinker);
                    HuAudSeqPlay(0);
                }
                break;
            case 1:
                break;
            case 2:
                if (D_8010C10C_hand_line_sinker == 3) {
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                if (D_8010C0F8_hand_line_sinker == NULL) {
                    if (D_8010C10C_hand_line_sinker == 3) {
                        D_8010C0F8_hand_line_sinker = omAddObj(4, 0, 0, -1, func_80109584_hand_line_sinker);
                        D_8010C0F8_hand_line_sinker->work[1] = 0;
                    } else {
                        D_8010C0F8_hand_line_sinker = omAddObj(4, 0, 0, -1, func_80109B9C_hand_line_sinker);
                        D_8010C0F8_hand_line_sinker->work[1] = 0;
                    }
                    D_8010C0F8_hand_line_sinker->work[0] = 0;
                } else if (D_8010C0F8_hand_line_sinker->work[0] == 1) {
                    omDelObj(D_8010C0F8_hand_line_sinker);
                    func_800E6F0C_minigame(4);
                }
                break;
            case 4:
                break;
            case 5:
                WipeCreateOut(0, 20);
                D_8010BF60_hand_line_sinker = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        work = D_8010C0FC_hand_line_sinker->data;
        func_8010BE6C_hand_line_sinker(work->line);
        work->line = NULL;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
        func_8010BA64_hand_line_sinker();
    }
}

void func_80105EE8_hand_line_sinker(omObjData *obj) {
    obj->data = HuMemAllocTag(0x24, 0x7918);
    obj->model[0] = func_8000B108_main(0x220000, 0x699);
    obj->model[1] = func_8000B108_main(0x220001, 0x1A99);
    obj->model[2] = func_8000B108_main(0x220003, 0x699);
    func_8001C814_main(obj->model[2], 2, 2);
    func_800335BC_main("m201_3mizu_DEF", D_8010C104_hand_line_sinker);
    func_8001C954_main(obj->model[1]);
    D_8010C108_hand_line_sinker = 0.0f;
    obj->func = func_80105FA4_hand_line_sinker;
}

void func_80105FA4_hand_line_sinker(omObjData *obj) {
    if (func_80049F98_main() + D_800D6A90_main == 0) {
        D_8010C108_hand_line_sinker += 0.1f;
    }
    func_8001E888_main(obj->model[1], D_8010C108_hand_line_sinker, 0.0f, D_8010C104_hand_line_sinker[0],
                       D_8010C104_hand_line_sinker[1], "m201_00-grid6", 0);
}

void func_80106040_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 0);
}

void func_80106070_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 1);
}

void func_801060A0_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 2);
}

void func_801060D0_hand_line_sinker(omObjData *obj) {
    obj->trans.z = 5000.0f;
    func_80106100_hand_line_sinker(obj, 3);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", D_8010BFF0_hand_line_sinker);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", D_8010C008_hand_line_sinker);

void func_80106100_hand_line_sinker(omObjData *obj, u16 playerNo) {
    HandLineSinkerPlayerWork *work;
    s8 chr;
    f32 x;
    f32 z;
    f32 rot;
    f32 dist;
    u32 i;
    s32 model;
    s32 motion;

    chr = GwPlayer[playerNo].chr;
    model = D_800A178C_main[chr][0];
    motion = D_800A178C_main[chr][2];
    obj->data = HuMemAllocTag(sizeof(HandLineSinkerPlayerWork), 0x7918);
    work = obj->data;
    work->playerNo = playerNo;
    work->aiWait = 0;
    work->aiState = 0;
    work->unk10 = 0;
    work->pressTimer = 0;
    work->speed = 0.0f;
    if (playerNo == D_8010C0EA_hand_line_sinker) {
        obj->model[0] = func_8000B108_main(model | motion, 0x20689);
        func_80017790_main(obj->model[0], 2, chr, func_80017B6C_main(chr, 2, 0));
        func_8001C514_main(obj->model[0]);
        obj->model[5] = func_80017AD8_main(func_80017B6C_main(chr, 2, 1));
        obj->work[0] = 0;
        work->unk8 = 0.0f;
        work->line = func_8010BA80_hand_line_sinker(0xFF, 0xFF, 0xFF);
        work->lineObj = NULL;
        work->aiTarget = NULL;
        obj->model[1] = func_8000B108_main(0x220006, 0x20499);
        obj->model[2] = func_8000B108_main(0x220007, 0x20499);
        obj->model[3] = func_8000B108_main(0x22000B, 0x21899);
        obj->model[4] = func_8000B0D4_main(9, 0x689);
        func_8001EF6C_main(obj->model[1], obj->model[0], "item_hook");
        func_8000B460_main(obj, 17, 0x220007);
        func_8000B460_main(obj, 14, 0x220008);
        func_8000B460_main(obj, 15, 0x220009);
        func_8000B460_main(obj, 16, 0x22000A);
        func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x16));
        func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x17));
        func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x40));
        func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x26));
        func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x2A));
        func_8000B460_main(obj, 10, func_80017BB8_main(chr, 1));
        func_8000B460_main(obj, 11, func_80017BB8_main(chr, 0));
        func_8000B460_main(obj, 12, func_80017BB8_main(chr, 0x2F));
        func_8000B460_main(obj, 13, func_80017BB8_main(chr, 0x36));
        func_8001C5B4_main(obj->model[0], obj->motion[4]);
        func_8001C814_main(obj->model[0], 2, 2);
        func_8001C258_main(obj->model[2], 4, 4);
        func_8001EF6C_main(obj->model[3], obj->model[1], D_8010BF88_hand_line_sinker);
        func_8001C258_main(obj->model[3], 0x4000, 0x4000);
        func_8001C258_main(obj->model[1], 0x4000, 0x4000);
        omSetTra(obj, 0.0f, 100.0f, 900.0f);
        omSetRot(obj, 0.0f, 180.0f, 0.0f);
        Hu3DModelPosSet(obj->model[4], 0.0f, 100.0f, 900.0f);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
        Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[2], obj->rot.x, obj->rot.y, obj->rot.z);
        obj->func = func_8010689C_hand_line_sinker;
    } else {
        obj->model[0] = func_8000B108_main(D_8010BF64_hand_line_sinker[chr] | 0x220000, 0x1A99);
        func_8000B460_main(obj, 0, D_8010BF64_hand_line_sinker[chr] | 0x220000);
        func_8000B460_main(obj, 1, 0x220014);
        func_8001C5B4_main(obj->model[0], obj->motion[0]);
        func_8001C814_main(obj->model[0], 2, 2);
        omSetSca(obj, 1.0f, 1.0f, 1.0f);
        omSetSca(obj, 1.5f, 1.5f, 1.5f);
        do {
            rot = (rand8() * rand8()) % 360;
            dist = (rand8() * rand8()) % 595;
            x = sindf(rot) * dist;
            z = cosdf(rot) * dist;
            for (i = 0; i < D_8010BF9C_hand_line_sinker; i++) {
                dist = HuSqrtf((D_8010C100_hand_line_sinker[i]->trans.x - x) *
                                   (D_8010C100_hand_line_sinker[i]->trans.x - x) +
                               (D_8010C100_hand_line_sinker[i]->trans.z - z) *
                                   (D_8010C100_hand_line_sinker[i]->trans.z - z));
                if (dist < 405.0f) {
                    break;
                }
            }
        } while (i != D_8010BF9C_hand_line_sinker);
        omSetTra(obj, x, -240.0f, z);
        D_8010BF9C_hand_line_sinker++;
        obj->rot.y = (rand8() * rand8()) % 360;
        work->aiPrevRot = work->aiTargetRot = (rand8() * rand8()) % 360;
        work->aiTimer = 0;
        obj->work[0] = 0;
        obj->func = func_801081D0_hand_line_sinker;
    }
}

void func_8010689C_hand_line_sinker(omObjData *obj) {
    HandLineSinkerPlayerWork *work;
    HandLineSinkerObjWork *lineWork;
    Vec pos;
    s8 stickX;
    s8 stickY;
    s8 x;
    s8 y;
    u16 btn;
    u16 pad;
    u32 stat;
    f32 angle;
    f32 rot;
    f32 dist;

    stat = obj->unk10;
    work = obj->data;
    pad = GwPlayer[work->playerNo].pad;
    if (GwPlayer[work->playerNo].stat & 1) {
        func_80107420_hand_line_sinker(obj, &stickX, &stickY, &btn);
    } else {
        stickX = D_800CBB6E_main[pad];
        stickY = D_800D20A1_main[pad];
        btn = D_800D5558_main[pad];
    }
    if (func_800E6E8C_minigame() != 2) {
        stickX = stickY = 0;
        btn = 0;
    }
    y = stickY;
    x = stickX;
    angle = atan2df(y, x);
    switch (obj->work[0]) {
        case 0:
            if ((x != 0) | (y != 0)) {
                obj->rot.y = angle + 270.0f;
                if (obj->rot.y >= 360.0f) {
                    obj->rot.y -= 360.0f;
                }
                if (obj->rot.y < 135.0f) {
                    obj->rot.y = 135.0f;
                }
                if (obj->rot.y > 225.0f) {
                    obj->rot.y = 225.0f;
                }
                Hu3DModelRotSet(obj->model[2], 0.0f, obj->rot.y, 0.0f);
                Hu3DModelRotSet(obj->model[3], 0.0f, obj->rot.y, 0.0f);
                work->unk8 = func_801092B8_hand_line_sinker(x, y);
                if (func_800E6E8C_minigame() != 2) {
                    obj->work[0] = 0;
                } else {
                    obj->work[0] = 1;
                }
            }
            break;
        case 1:
            if ((x != 0) | (y != 0)) {
                obj->rot.y = angle + 270.0f;
                if (obj->rot.y >= 360.0f) {
                    obj->rot.y -= 360.0f;
                }
                if (obj->rot.y < 135.0f) {
                    obj->rot.y = 135.0f;
                }
                if (obj->rot.y > 225.0f) {
                    obj->rot.y = 225.0f;
                }
                Hu3DModelRotSet(obj->model[2], 0.0f, obj->rot.y, 0.0f);
                Hu3DModelRotSet(obj->model[3], 0.0f, obj->rot.y, 0.0f);
                work->unk8 = func_801092B8_hand_line_sinker(x, y);
            }
            if (func_800E6E8C_minigame() != 2) {
                obj->work[0] = 0;
                break;
            }
            if (btn & 0x8000) {
                if (func_800E6E8C_minigame() != 2) {
                    obj->work[0] = 0;
                    break;
                }
                obj->work[0] = 2;
                func_8001C258_main(obj->model[1], 0x4000, 0);
                func_8001C258_main(obj->model[1], 4, 4);
                func_8001C258_main(obj->model[2], 4, 0);
                func_8001C5B4_main(obj->model[0], obj->motion[3]);
                func_8001C5B4_main(obj->model[2], obj->motion[14]);
                work->aiWait = 5;
            }
            break;
        case 2:
            if (--work->aiWait != 0) {
                break;
            }
            if (func_800E6E8C_minigame() != 2) {
                obj->work[0] = 0;
                func_8001C258_main(obj->model[1], 0x4000, 0x4000);
                func_8001C258_main(obj->model[1], 4, 0);
                func_8001C258_main(obj->model[2], 4, 4);
                func_8001C5B4_main(obj->model[0], obj->motion[8]);
                func_8001C814_main(obj->model[0], 3, 3);
                break;
            }
            obj->work[0] = 4;
            func_8001C5B4_main(obj->model[0], obj->motion[8]);
            func_8001C814_main(obj->model[0], 3, 3);
            func_8001C92C_main(obj->model[0], 1.0f);
            func_8001C92C_main(obj->model[2], 1.0f);
            func_8001C258_main(obj->model[3], 0x4000, 0);
            if (work->lineObj != NULL) {
                omDelObj(work->lineObj);
            }
            work->lineObj = omAddObj(20, 1, 0, -1, func_80107B24_hand_line_sinker);
            work->lineObj->model[0] = obj->model[3];
            work->lineObj->data = HuMemAllocTag(sizeof(HandLineSinkerObjWork), 0x7918);
            lineWork = work->lineObj->data;
            work->lineObj->work[0] = 0;
            work->lineObj->work[1] = 0;
            lineWork->unk1CE = 0;
            lineWork->unk1B8 = NULL;
            lineWork->unk1BC = 0.0f;
            lineWork->unk1C0 = 0;
            lineWork->unk1C8 = work->playerNo;
            lineWork->unk0 = -(work->unk8 / 70.0f * 85.0f) - 15.0f;
            angle = obj->rot.y;
            if (angle > 180.0f) {
                angle = fabsf(angle - 360.0f);
            } else {
                angle = fabsf(angle);
            }
            lineWork->unk0 *= fabs(sindf(angle - 90.0f));
            lineWork->unk4 = 45.0f;
            lineWork->unk8 = 0.0f;
            lineWork->pos.y = 240.0f;
            lineWork->pos.x = sindf(obj->rot.y - 6.0f) * 140.0f + obj->trans.x;
            lineWork->pos.z = cosdf(obj->rot.y - 6.0f) * 140.0f + obj->trans.z;
            lineWork->unk18.x = 75.0f;
            lineWork->unk18.y = obj->rot.y;
            lineWork->unk18.z = 0.0f;
            lineWork->unk24 = 0;
            lineWork->numPoints = 0;
            lineWork->line = work->line;
            lineWork->unk1CA = HuAudFXPlay(0x302);
            lineWork->seNo = -1;
            omSetTra(work->lineObj, lineWork->pos.x, lineWork->pos.y, lineWork->pos.z);
            omSetRot(work->lineObj, lineWork->unk18.x, lineWork->unk18.y, lineWork->unk18.z);
            Hu3DModelPosSet(work->lineObj->model[0], lineWork->pos.x, lineWork->pos.y, lineWork->pos.z);
            Hu3DModelRotSet(work->lineObj->model[0], lineWork->unk18.x, lineWork->unk18.y, lineWork->unk18.z);
            break;
        case 4:
            if (stat & 1) {
                obj->unk10 &= ~1;
                func_8001C624_main(D_8010C0FC_hand_line_sinker->model[0],
                                   HmfModelData[D_8010C0FC_hand_line_sinker->motion[5]].unk02, 0, 6, 2);
                obj->work[0] = 3;
            }
            break;
        case 3:
            lineWork = work->lineObj->data;
            if (stat & 2) {
                obj->unk10 &= ~2;
                if (work->lineObj->work[1] == 1) {
                    func_80047E90_main(lineWork->unk1B8, 2);
                    obj->work[0] = 5;
                    func_8001C258_main(obj->model[1], 0x4000, 0);
                    func_8001C258_main(obj->model[1], 4, 4);
                    func_8001C258_main(obj->model[2], 4, 0);
                    func_8001C5B4_main(obj->model[0], obj->motion[2]);
                    func_8001C5B4_main(obj->model[2], obj->motion[17]);
                    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
                } else {
                    obj->work[0] = 0;
                    func_8001C258_main(obj->model[1], 0x4000, 0x4000);
                    func_8001C258_main(obj->model[1], 4, 0);
                    func_8001C258_main(obj->model[2], 4, 4);
                    func_8001C5B4_main(obj->model[0], obj->motion[8]);
                    func_8001C814_main(obj->model[0], 3, 3);
                    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
                    work->aiTarget = NULL;
                }
                omDelObj(work->lineObj);
                work->lineObj = NULL;
                break;
            }
            if (lineWork->unk1D0 == 0 && ((x != 0) | (y != 0))) {
                rot = angle + 270.0f;
                if (rot >= 360.0f) {
                    rot -= 360.0f;
                }
                if (rot < 135.0f) {
                    rot = 135.0f;
                }
                if (rot > 225.0f) {
                    rot = 225.0f;
                }
                if (rot != obj->rot.y) {
                    obj->rot.y = rot;
                    pos.y = 240.0f;
                    pos.x = sindf(obj->rot.y - 6.0f) * 140.0f + obj->trans.x;
                    pos.z = cosdf(obj->rot.y - 6.0f) * 140.0f + obj->trans.z;
                    dist = HuSqrtf((pos.x - work->lineObj->trans.x) * (pos.x - work->lineObj->trans.x) +
                                   (pos.y - work->lineObj->trans.y) * (pos.y - work->lineObj->trans.y) +
                                   (pos.z - work->lineObj->trans.z) * (pos.z - work->lineObj->trans.z));
                    lineWork->pos = pos;
                    Hu3DModelRotSet(obj->model[2], 0.0f, obj->rot.y, 0.0f);
                    if (dist < lineWork->unk1B0) {
                        lineWork->unk1B4 += lineWork->unk1B0 - dist;
                    }
                    lineWork->unk1B0 = dist;
                }
            }
            break;
        case 5:
            if (HmfModelData[obj->model[0]].unk40 >= D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02) {
                obj->work[0] = 0;
                func_8001C258_main(obj->model[1], 0x4000, 0x4000);
                func_8001C258_main(obj->model[1], 4, 0);
                func_8001C258_main(obj->model[2], 4, 4);
                func_8001C5B4_main(obj->model[0], obj->motion[8]);
                func_8001C814_main(obj->model[0], 3, 3);
                work->aiTarget = NULL;
            }
            break;
    }
}

void func_80107420_hand_line_sinker(omObjData *obj, s8 *stickX, s8 *stickY, u16 *btn) {
    HandLineSinkerPlayerWork *work;
    omObjData *target;
    f32 offset;
    f32 angle;
    f32 dist;
    f32 x;
    f32 y;
    u16 castTimer;

    *stickY = 0;
    *stickX = 0;
    *btn = 0;
    work = obj->data;
    offset = 0.0f;
    switch (GwPlayer[work->playerNo].cpu_difficulty) {
        case 0:
            if (rand8() % 10 < 8) {
                offset = rand8() % 31 - 15;
            }
            castTimer = rand8() % 45 + 20;
            break;
        case 1:
            if (rand8() % 10 < 5) {
                offset = rand8() % 21 - 10;
            }
            castTimer = rand8() % 30 + 15;
            break;
        case 2:
            if (rand8() % 10 < 3) {
                offset = rand8() % 11 - 5;
            }
            castTimer = rand8() % 15 + 10;
            break;
        case 3:
            if (rand8() % 10 == 0) {
                offset = rand8() % 11 - 5;
            }
            castTimer = rand8() % 10 + 10;
            break;
    }
    switch (obj->work[0]) {
        case 0:
            target = work->aiTarget;
            if (target == NULL) {
                work->aiTarget = func_80107A3C_hand_line_sinker();
                work->aiAimOffset = offset;
                break;
            }
            angle = atan2df(target->trans.x - obj->trans.x, target->trans.z - obj->trans.z) + work->aiAimOffset;
            dist = HuSqrtf((target->trans.x - obj->trans.x) * (target->trans.x - obj->trans.x) +
                           (target->trans.z - obj->trans.z) * (target->trans.z - obj->trans.z)) /
                   15.0f;
            x = -sindf(angle) * dist;
            y = cosdf(angle) * dist;
            *stickX = x;
            *stickY = y;
            work->aiCastTimer = castTimer;
            break;
        case 1:
            target = work->aiTarget;
            if (target == NULL) {
                work->aiTarget = func_80107A3C_hand_line_sinker();
                work->aiAimOffset = offset;
                break;
            }
            angle = atan2df(target->trans.x - obj->trans.x, target->trans.z - obj->trans.z) + work->aiAimOffset;
            dist = HuSqrtf((target->trans.x - obj->trans.x) * (target->trans.x - obj->trans.x) +
                           (target->trans.z - obj->trans.z) * (target->trans.z - obj->trans.z)) /
                   15.0f;
            x = -sindf(angle) * dist;
            y = cosdf(angle) * dist;
            if (--work->aiCastTimer == 0) {
                *btn |= 0x8000;
                break;
            }
            *stickX = x;
            *stickY = y;
            break;
        case 2:
            break;
        case 3:
            target = work->aiTarget;
            angle = atan2df(target->trans.x - obj->trans.x, target->trans.z - obj->trans.z);
            dist = HuSqrtf((target->trans.x - obj->trans.x) * (target->trans.x - obj->trans.x) +
                           (target->trans.z - obj->trans.z) * (target->trans.z - obj->trans.z)) /
                   15.0f;
            x = -sindf(angle) * dist;
            y = cosdf(angle) * dist;
            *stickX = x;
            *stickY = y;
            break;
        case 4:
            break;
        case 5:
            break;
    }
}

omObjData *func_80107A3C_hand_line_sinker(void) {
    omObjData *candidates[3];
    omObjData *obj;
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < 3; i++) {
        obj = D_8010C100_hand_line_sinker[i];
        if (obj->work[0] == 2 || obj->work[0] == 4) {
            continue;
        }
        if (obj->work[0] != 3) {
            candidates[count++] = obj;
        }
    }
    if (count == 0) {
        return NULL;
    }
    if (count == 1) {
        return candidates[0];
    }
    return candidates[rand8() % count];
}

void func_80107B24_hand_line_sinker(omObjData *obj) {
    HandLineSinkerObjWork *work;
    HandLineSinkerPlayerWork *targetWork;
    omObjData *target;
    Vec offset;
    Vec rot;
    f32 velXZ;
    f32 x;
    f32 y;
    f32 z;
    f32 dist;
    f32 angle;
    f32 dy;

    work = obj->data;
    switch (obj->work[0]) {
        case 0:
            y = sindf(work->unk4) * work->unk0;
            velXZ = -work->unk0 * cosdf(work->unk4);
            x = sindf(obj->rot.y) * velXZ;
            z = cosdf(obj->rot.y) * velXZ;
            y = y * work->unk8 + work->unk8 * work->unk8 * 4.9f;
            y = work->pos.y - y;
            work->unk8 += 1.0f;
            if (obj->trans.y <= -50.0f && work->unk1C0 == 0) {
                work->unk1C0 = 1;
                offset.x = obj->trans.x;
                offset.y = -50.0f;
                offset.z = obj->trans.z;
                rot.x = rot.y = rot.z = 0.0f;
                func_8010A6D0_hand_line_sinker(NULL, 0, &offset, &rot);
                work->seNo = func_8004AC98_main(0x300, work->unk1C8);
                HuAudFXStop(work->unk1CA);
                omVibrate(work->unk1C8, 2, 3, 10);
            }
            if (y <= -210.0f) {
                y = -210.0f;
                work->unk1D0 = 0;
                obj->work[0] = 1;
                func_80047E90_main(D_8010C0FC_hand_line_sinker, 1);
                work->unk1C4 = 0.0f;
                work->unk1CA = HuAudFXPlay(0x303);
            }
            omSetTra(obj, x + obj->trans.x, y, z + obj->trans.z);
            work->unk1B0 = HuSqrtf((work->pos.x - obj->trans.x) * (work->pos.x - obj->trans.x) +
                                   (work->pos.y - obj->trans.y) * (work->pos.y - obj->trans.y) +
                                   (work->pos.z - obj->trans.z) * (work->pos.z - obj->trans.z));
            if (y <= -240.0f) {
                work->unk1B4 = 5.0f + work->unk1B0;
            } else {
                work->unk1B4 = work->unk1B0 + 3.0f;
            }
            func_8010AD7C_hand_line_sinker(obj, work->unk1B0, work->pos.x, work->pos.y, work->pos.z, obj->trans.x,
                                           obj->trans.y, obj->trans.z);
            func_8010B0FC_hand_line_sinker(obj, 111.0f);
            break;
        case 1:
            work->unk1B4 -= 21.0f - work->unk1BC * 21.0f;
            if (work->unk1D0 == 0 && (target = func_801080F0_hand_line_sinker(obj)) != NULL && obj->work[1] == 0) {
                obj->work[1] = 1;
                func_80047E90_main(target, 1);
                work->unk1B8 = target;
                obj->trans.y = -140.0f;
                targetWork = target->data;
                work->seNo = func_8004AC98_main(0x301, work->unk1C8);
                omVibrate(targetWork->playerNo, 2, 2, 20);
                omVibrate(work->unk1C8, 2, 2, 20);
            }
            if (work->unk1B4 < work->unk1B0) {
                work->unk1B0 -= work->unk1B0 - work->unk1B4;
                if (work->unk1B0 > fabs(240.0f - obj->trans.y)) {
                    dy = fabsf(work->pos.y - obj->trans.y);
                    dist = HuSqrtf(fabsf(work->unk1B0 * work->unk1B0 - dy * dy));
                    angle = atan2df(obj->trans.x - work->pos.x, -(obj->trans.z - work->pos.z));
                    omSetTra(obj, sindf(angle) * dist + work->pos.x, obj->trans.y,
                             work->pos.z - cosdf(angle) * dist);
                    obj->rot.y = 180.0f - angle;
                    work->unk1B4 = work->unk1B0;
                    if (work->unk1C4 < 5.0f) {
                        work->unk1C4 += 0.5f;
                    }
                } else {
                    work->unk1D0 = 1;
                    if (work->unk1CE == 0 && work->unk1B8 != NULL) {
                        work->unk1CE = 1;
                        func_8004AC98_main(0x304, work->unk1C8);
                    }
                    work->unk1C4 = 0.0f;
                    obj->rot.y = D_8010C0FC_hand_line_sinker->rot.y;
                    if (work->unk1B0 < 0.0f) {
                        func_80047E90_main(D_8010C0FC_hand_line_sinker, 2);
                        omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
                        HuAudFXStop(work->unk1CA);
                    } else {
                        omSetTra(obj, work->pos.x, 240.0f - work->unk1B0, work->pos.z);
                        omSetRot(obj, 160.0f, obj->rot.y, 0.0f);
                    }
                }
            }
            func_8010AD7C_hand_line_sinker(obj, work->unk1B4 + work->unk1C4, work->pos.x, work->pos.y, work->pos.z,
                                           obj->trans.x, obj->trans.y, obj->trans.z);
            func_8010B0FC_hand_line_sinker(obj, 104.0f);
            break;
    }
    func_8010BB58_hand_line_sinker(work->line, work->points, work->numPoints);
}

omObjData *func_801080F0_hand_line_sinker(omObjData *arg0) {
    omObjData *obj;
    s32 i;

    if (func_800E6E8C_minigame() != 2) {
        return NULL;
    }
    for (i = 0; i < 3; i++) {
        obj = D_8010C100_hand_line_sinker[i];
        if (obj->work[0] < 2) {
            if (HuSqrtf((arg0->trans.x - obj->trans.x) * (arg0->trans.x - obj->trans.x) +
                        (arg0->trans.z - obj->trans.z) * (arg0->trans.z - obj->trans.z)) < HuSqrtf(8725.0f)) {
                return obj;
            }
        }
    }
    return NULL;
}

void func_801081D0_hand_line_sinker(omObjData *obj) {
    HandLineSinkerPlayerWork *work = obj->data;
    HandLineSinkerObjWork *lineWork;
    omObjData *lineObj;
    Vec offset;
    Vec rot;
    s8 stickX;
    s8 stickY;
    u16 btn;
    u16 pad;
    u32 stat;
    f32 angle;
    f32 diff;

    pad = GwPlayer[work->playerNo].pad;
    if (GwPlayer[work->playerNo].stat & 1) {
        func_80108880_hand_line_sinker(obj, &stickX, &stickY, &btn);
    } else {
        stickX = D_800CBB6E_main[pad];
        stickY = D_800D20A1_main[pad];
        btn = D_800D5558_main[pad];
    }
    if (func_800E6E8C_minigame() != 2) {
        stickX = stickY = 0;
        btn = 0;
    }
    stat = obj->unk10;
    if (stat & 1) {
        obj->unk10 = stat & ~1;
        obj->work[0] = 3;
        work->aiTimer = 0;
        work->aiBtn = 0;
        func_8001C5B4_main(obj->model[0], obj->motion[1]);
        func_8001C814_main(obj->model[0], 2, 2);
    }
    switch (obj->work[0]) {
        case 0:
            if ((stickX != 0) | (stickY != 0)) {
                angle = atan2df(stickX, -stickY);
                if (angle < 0.0f) {
                    angle += 360.0f;
                }
                if (obj->rot.y != angle) {
                    diff = angle - obj->rot.y;
                    if (diff < 0.0f) {
                        diff += 360.0f;
                    }
                    if (diff < 180.0f) {
                        if (diff > 4.0f) {
                            obj->rot.y += 4.0f;
                        } else {
                            obj->rot.y += diff;
                        }
                    } else {
                        if (360.0f - diff > 4.0f) {
                            obj->rot.y -= 4.0f;
                        } else {
                            obj->rot.y -= 360.0f - diff;
                        }
                    }
                    if (obj->rot.y < 0.0f) {
                        obj->rot.y += 360.0f;
                    }
                    if (obj->rot.y >= 360.0f) {
                        obj->rot.y -= 360.0f;
                    }
                }
            }
            func_8010B1E4_hand_line_sinker(obj);
            if (btn & 0x8000) {
                obj->work[0] = 1;
                work->speed = 20.0f;
                angle = obj->rot.y + 180.0f;
                offset.x = sindf(angle) * 80.0f;
                offset.y = 0.0f;
                offset.z = cosdf(angle) * 80.0f;
                rot.x = rot.z = 0.0f;
                rot.y = obj->rot.y + 180.0f;
                func_8010A6D0_hand_line_sinker(obj, 1, &offset, &rot);
                func_8004ACE0_main(0x306, work->playerNo);
            }
            work->pressTimer = 1000;
            break;
        case 1:
            func_8010B1E4_hand_line_sinker(obj);
            work->speed *= 0.85f;
            if (work->speed < 2.0f) {
                obj->work[0] = 0;
                work->speed = 0.0f;
            }
            break;
        case 2:
            break;
        case 3:
            if (stat & 2) {
                obj->unk10 &= ~2;
                obj->work[0] = 4;
                D_8010C10C_hand_line_sinker++;
                work->flyRot = atan2df(obj->trans.x - D_8010C0FC_hand_line_sinker->trans.x,
                                       obj->trans.z - D_8010C0FC_hand_line_sinker->trans.z) +
                               180.0f;
                work->flyVelY = 50.0f;
                HuAudFXPlay(GwPlayer[work->playerNo].chr + 0x287);
                omVibrate(work->playerNo, 10, 0, 10);
                break;
            }
            lineObj = ((HandLineSinkerPlayerWork *)D_8010C0FC_hand_line_sinker->data)->lineObj;
            lineWork = lineObj->data;
            if (lineWork != NULL) {
                if (btn & 0x8000) {
                    if (work->pressTimer < 2) {
                        lineWork->unk1BC = 0.5f;
                    } else if (work->pressTimer < 3) {
                        lineWork->unk1BC = 0.3f;
                    } else if (work->pressTimer < 4) {
                        lineWork->unk1BC = 0.1f;
                    }
                    work->pressTimer = 0;
                } else {
                    work->pressTimer++;
                }
            }
            if (lineObj != NULL) {
                if (lineWork->unk1D0 == 0) {
                    omSetTra(obj, sindf(lineObj->rot.y) * 40.0f + lineObj->trans.x, lineObj->trans.y - 60.0f,
                             cosdf(lineObj->rot.y) * 40.0f + lineObj->trans.z);
                } else {
                    omSetTra(obj, sindf(lineObj->rot.y) * 40.0f + lineObj->trans.x, lineObj->trans.y - 100.0f,
                             cosdf(lineObj->rot.y) * 40.0f + lineObj->trans.z);
                }
            }
            break;
        case 4:
            obj->trans.x += sindf(work->flyRot) * 35.0f;
            obj->trans.z += cosdf(work->flyRot) * 35.0f;
            obj->trans.y += work->flyVelY;
            work->flyVelY -= 5.0f;
            if (work->flyVelY < -600.0f) {
                obj->work[0] = 2;
            }
            break;
    }
}

void func_80108880_hand_line_sinker(omObjData *obj, s8 *stickX, s8 *stickY, u16 *btn) {
    HandLineSinkerPlayerWork *work;
    u8 difficulty;

    *stickX = 0;
    *stickY = 0;
    *btn = 0;
    if (obj->work[0] == 1) {
        return;
    }
    work = obj->data;
    if (obj->work[0] != 3) {
        switch (work->aiState) {
            case 0:
                if (rand8() < 4) {
                    work->aiState = 1;
                    work->aiWait = rand8() % 25 + 5;
                } else {
                    work->aiState = 2;
                    if (rand8() % 10 < 7) {
                        work->aiPrevRot = work->aiTargetRot = rand8() * rand8() % 360;
                    }
                }
                break;
            case 1:
                if (work->aiWait == 0) {
                    work->aiState = 0;
                } else {
                    work->aiWait--;
                }
                break;
            case 2:
                if (obj->rot.y == work->aiTargetRot || obj->rot.y == work->aiPrevRot) {
                    *btn |= 0x8000;
                    work->aiState = 0;
                } else {
                    *stickX = sindf(work->aiTargetRot) * 60.0f;
                    *stickY = -cosdf(work->aiTargetRot) * 60.0f;
                    work->aiPrevRot = obj->rot.y;
                }
                break;
        }
    } else if (work->aiTimer == 0) {
        *btn |= work->aiBtn;
        difficulty = GwPlayer[work->playerNo].cpu_difficulty;
        work->aiBtn = 0;
        switch (difficulty) {
            case 0:
                work->aiTimer = 3;
                if (rand8() % 10 < 4) {
                    work->aiBtn = 0x8000;
                }
                break;
            case 1:
                work->aiTimer = (rand8() & 1) + 2;
                if (rand8() % 10 < 8) {
                    work->aiBtn = 0x8000;
                }
                break;
            case 2:
                work->aiTimer = (u8)(rand8() & 3);
                if (rand8() % 10 < 5) {
                    work->aiBtn = 0x8000;
                }
                break;
            case 3:
                work->aiTimer = rand8() & 1;
                if (rand8() % 10 < 8) {
                    work->aiBtn = 0x8000;
                }
                break;
        }
    }
}

void func_80108C5C_hand_line_sinker(omObjData *obj) {
    HandLineSinkerPlayerWork *work = obj->data;
    Vec pos;
    Vec rot;

    switch (obj->work[0]) {
        case 5:
            obj->rot.x -= 15.0f;
            if (obj->rot.x == -90.0f) {
                obj->work[0] = 6;
            }
            break;
        case 6:
            obj->trans.y += work->velY;
            work->velY -= 4.2f;
            if (obj->trans.y >= -50.0f && work->splashed == 0) {
                pos.x = obj->trans.x;
                pos.y = -50.0f;
                pos.z = obj->trans.z;
                rot.x = rot.y = rot.z = 0.0f;
                func_8010A6D0_hand_line_sinker(NULL, 0, &pos, &rot);
                HuAudFXPlay(0x30F);
                work->splashed = 1;
            }
            if (work->velY < 0.0f) {
                obj->work[0] = 7;
            }
            break;
        case 7:
            obj->trans.y += work->velY;
            work->velY -= 4.2f;
            obj->rot.x += 30.0f;
            if (obj->rot.x > 90.0f) {
                obj->rot.x = 90.0f;
            }
            if (obj->trans.y <= -50.0f) {
                obj->work[0] = 8;
                pos.x = obj->trans.x;
                pos.y = -50.0f;
                pos.z = obj->trans.z;
                rot.x = rot.y = rot.z = 0.0f;
                func_8010A6D0_hand_line_sinker(NULL, 0, &pos, &rot);
                HuAudFXPlay(0x30F);
            }
            break;
        case 8:
            obj->trans.y += work->velY;
            work->velY -= 4.2f;
            obj->rot.x -= 20.0f;
            if (obj->rot.x < 0.0f) {
                obj->rot.x = 0.0f;
            }
            if (obj->trans.y <= -240.0f) {
                obj->trans.y = -240.0f;
                obj->work[0] = 0;
                obj->rot.x = 0.0f;
                obj->func = func_801081D0_hand_line_sinker;
            }
            break;
    }
}

void func_80108F44_hand_line_sinker(omObjData *obj) {
    omObjData *other;
    f32 angle;
    f32 diff;
    f32 x;
    f32 z;
    f32 dist;
    f32 dx;
    f32 dz;
    s32 hit;
    s32 inRange;
    s32 i;

    angle = atan2df(-obj->trans.x, -obj->trans.z);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    if (angle != obj->rot.y) {
        if (obj->rot.y != angle) {
            diff = angle - obj->rot.y;
            if (diff < 0.0f) {
                diff += 360.0f;
            }
            if (diff < 180.0f) {
                if (diff > 4.0f) {
                    obj->rot.y = obj->rot.y + 4.0f;
                } else {
                    obj->rot.y = diff + obj->rot.y;
                }
            } else {
                if (360.0f - diff > 4.0f) {
                    obj->rot.y -= 4.0f;
                } else {
                    obj->rot.y -= 360.0f - diff;
                }
            }
            if (obj->rot.y < 0.0f) {
                obj->rot.y += 360.0f;
            }
            if (obj->rot.y >= 360.0f) {
                obj->rot.y -= 360.0f;
            }
        }
        return;
    }

    dx = sindf(angle) * 20.0f;
    dz = cosdf(angle) * 20.0f;
    x = dx + obj->trans.x;
    z = dz + obj->trans.z;
    hit = 0;
    for (i = 0; i < 3; i++) {
        other = D_8010C100_hand_line_sinker[i];
        if (obj == other || obj->work[0] == 2) {
            continue;
        }
        dist = HuSqrtf((other->trans.x - x) * (other->trans.x - x) + (other->trans.z - z) * (other->trans.z - z));
        if (dist < 270.0f) {
            x -= sindf(obj->rot.y) * (270.0f - dist);
            z -= cosdf(obj->rot.y) * (270.0f - dist);
            if (D_8010C100_hand_line_sinker[i]->work[3] == 1) {
                hit = 1;
            }
            break;
        }
    }
    omSetTra(obj, x, obj->trans.y, z);
    inRange = HuSqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z) < 300.0f;
    if (inRange | hit) {
        obj->func = NULL;
        obj->work[3] = 1;
    }
}

f32 func_801092B8_hand_line_sinker(s8 stickX, s8 stickY) {
    f32 angle;
    f32 mag;

    if (stickX == 0 && stickY == 0) {
        return 0.0f;
    }
    angle = atan2df(stickY, stickX);
    mag = fabs(stickX * cosdf(angle)) + fabs(stickY * sindf(angle));
    if (mag > 70.0f) {
        mag = 70.0f;
    }
    return mag;
}

void func_801093A4_hand_line_sinker(omObjData *obj) {
    HandLineSinkerPlayerWork *work;

    switch (D_8010C0EE_hand_line_sinker) {
        case 0:
            WipeCreateIn(0xFF, 0x10);
            D_8010C0E0_hand_line_sinker = func_8010A554_hand_line_sinker();
            D_8010C110_hand_line_sinker.center.x = D_8010C0E0_hand_line_sinker->trans.x;
            D_8010C110_hand_line_sinker.center.y = D_8010C0E0_hand_line_sinker->trans.y;
            D_8010C110_hand_line_sinker.center.z = D_8010C0E0_hand_line_sinker->trans.z;
            D_8010C110_hand_line_sinker.rot = D_8010BF28_hand_line_sinker.rot;
            D_8010C110_hand_line_sinker.rot.x = 328.0f;
            D_8010C110_hand_line_sinker.zoom = 1250.0f;
            func_8010B5EC_hand_line_sinker(&D_8010C110_hand_line_sinker, &D_8010BF28_hand_line_sinker, 37);
            D_8010C0EE_hand_line_sinker = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                work = D_8010C0E0_hand_line_sinker->data;
                work->velY = 60.0f;
                work->splashed = 0;
                D_8010C0EE_hand_line_sinker = 3;
                HuAudFXPlay(0x305);
            }
            break;
        case 2:
            if (D_8010C0E0_hand_line_sinker->work[0] == 0) {
                D_8010C0EE_hand_line_sinker = 3;
            }
            break;
        case 3:
            D_8010C190_hand_line_sinker->work[1] = 1;
            if (D_8010C190_hand_line_sinker->work[0] == 0) {
                func_8001C624_main(D_8010C0FC_hand_line_sinker->model[0],
                                   HmfModelData[D_8010C0FC_hand_line_sinker->motion[8]].unk02, 0, 30, 3);
                omDelObj(D_8010C190_hand_line_sinker);
                D_8010C190_hand_line_sinker = NULL;
                omDelObj(D_8010C0F4_hand_line_sinker);
                func_800E6F0C_minigame(1);
            }
            break;
    }
}

void func_80109584_hand_line_sinker(omObjData *obj) {
    HandLineSinkerPlayerWork *work;
    Vec pos;
    f32 dist;
    s16 effect;
    s32 i;

    switch (obj->work[1]) {
        case 0:
            if (D_8010C0FC_hand_line_sinker->work[0] == 0) {
                obj->work[1] = 1;
            }
            break;
        case 1:
            func_8001C258_main(D_8010C0FC_hand_line_sinker->model[1], 0x4000, 0);
            func_8001C258_main(D_8010C0FC_hand_line_sinker->model[3], 0x4000, 0);
            func_8001C258_main(D_8010C0FC_hand_line_sinker->model[2], 0x4000, 0);
            func_8001C258_main(D_8010C0FC_hand_line_sinker->model[1], 4, 4);
            func_8001C258_main(D_8010C0FC_hand_line_sinker->model[3], 4, 4);
            for (i = 0; i < 6; i++) {
                dist = i * 17.0f;
                pos.y = 240.0f - dist;
                pos.x = sindf(D_8010C0FC_hand_line_sinker->rot.y - 6.0f + rand8() % 13 - 6.0f) * (140.0f - dist) +
                        D_8010C0FC_hand_line_sinker->trans.x;
                pos.z = cosdf(D_8010C0FC_hand_line_sinker->rot.y - 6.0f + rand8() % 13 - 6.0f) * (140.0f - dist) +
                        D_8010C0FC_hand_line_sinker->trans.z;
                effect = func_8000CED8_main(0x85, 0x2A9);
                func_8000CFA4_main(effect, pos.x, pos.y, pos.z);
                func_8000CFD8_main(effect, 16);
            }
            obj->work[1] = 2;
            func_8001C624_main(D_8010C0FC_hand_line_sinker->model[0],
                               HmfModelData[D_8010C0FC_hand_line_sinker->motion[10]].unk02, 0, 6, 2);
            break;
        case 2:
            D_8010C0E4_hand_line_sinker = -D_8010C0FC_hand_line_sinker->rot.y;
            if (D_8010C0E4_hand_line_sinker < 0.0f) {
                D_8010C0E4_hand_line_sinker += 360.0f;
            }
            if (D_8010C0E4_hand_line_sinker < 180.0f) {
                if (D_8010C0E4_hand_line_sinker > 5.0f) {
                    D_8010C0FC_hand_line_sinker->rot.y += 5.0f;
                } else {
                    D_8010C0FC_hand_line_sinker->rot.y += D_8010C0E4_hand_line_sinker;
                }
            } else {
                if (360.0f - D_8010C0E4_hand_line_sinker > 5.0f) {
                    D_8010C0FC_hand_line_sinker->rot.y -= 5.0f;
                } else {
                    D_8010C0FC_hand_line_sinker->rot.y -= 360.0f - D_8010C0E4_hand_line_sinker;
                }
            }
            if (D_8010C0FC_hand_line_sinker->rot.y >= 360.0f) {
                D_8010C0FC_hand_line_sinker->rot.y -= 360.0f;
            }
            if (D_8010C0FC_hand_line_sinker->rot.y < 0.0f) {
                D_8010C0FC_hand_line_sinker->rot.y += 360.0f;
            }
            if (fabs(D_8010C0FC_hand_line_sinker->rot.y) < 0.0001f) {
                D_8010C0FC_hand_line_sinker->rot.y = 0.0f;
                func_8001C624_main(D_8010C0FC_hand_line_sinker->model[0],
                                   HmfModelData[D_8010C0FC_hand_line_sinker->motion[11]].unk02, 0, 6, 2);
                obj->work[1] = 3;
            }
            break;
        case 3:
            func_8010B5EC_hand_line_sinker(&D_8010BF28_hand_line_sinker, &D_8010BF44_hand_line_sinker, 16);
            D_8010C190_hand_line_sinker->work[1] = 1;
            D_8010C190_hand_line_sinker->work[2] = 0;
            obj->work[1] = 4;
            break;
        case 4:
            if (D_8010C190_hand_line_sinker->work[0] == 0) {
                work = D_8010C0FC_hand_line_sinker->data;
                func_80017954_main(D_8010C0FC_hand_line_sinker->model[0], 2, GwPlayer[work->playerNo].chr,
                                   D_8010C0FC_hand_line_sinker->model[5]);
                func_8001C624_main(D_8010C0FC_hand_line_sinker->model[0],
                                   HmfModelData[D_8010C0FC_hand_line_sinker->motion[12]].unk02, 0, 8, 0);
                func_80045ED0_main(D_800A178C_main[GwPlayer[work->playerNo].chr][0] | 0x2F);
                omDelObj(D_8010C190_hand_line_sinker);
                D_8010BF18_hand_line_sinker = work->playerNo;
                obj->work[0] = 1;
                GwPlayer[work->playerNo].bonusCoin = 10;
            }
            break;
    }
}

void func_80109B9C_hand_line_sinker(omObjData *obj) {
    HandLineSinkerPlayerWork *work;
    HandLineSinkerObjWork *lineWork;
    omObjData *lineObj;
    omObjData *player;
    Vec pos;
    f32 min[2];
    f32 max[2];
    f32 dist;
    f32 rot;
    s16 effect;
    s32 count;
    s32 i;

    work = D_8010C0FC_hand_line_sinker->data;
    lineObj = work->lineObj;
    lineWork = NULL;
    if (lineObj != NULL) {
        lineWork = lineObj->data;
    }
    switch (obj->work[1]) {
        case 0:
            if (lineObj != NULL) {
                if (lineWork != NULL) {
                    lineWork->unk1BC = -0.5f;
                }
                obj->work[1] = 1;
            } else {
                obj->work[1] = 2;
            }
            break;
        case 1:
            if (D_8010C0FC_hand_line_sinker->work[0] == 0) {
                count = 0;
                for (i = 0; i < 3; i++) {
                    player = D_8010C100_hand_line_sinker[i];
                    if (player->work[0] == 0 || player->work[0] == 4 || player->work[0] == 2) {
                        count++;
                    }
                }
                if (count == 3) {
                    if (D_8010C10C_hand_line_sinker == 3) {
                        omDelObj(obj);
                        D_8010C0F8_hand_line_sinker = omAddObj(4, 0, 0, -1, func_80109584_hand_line_sinker);
                        D_8010C0F8_hand_line_sinker->work[1] = 0;
                    } else {
                        obj->work[1] = 2;
                    }
                }
            }
            break;
        case 2:
            D_8010C0E8_hand_line_sinker = 3;
            for (i = 0; i < 3; i++) {
                player = D_8010C100_hand_line_sinker[i];
                player->work[3] = 1;
                if (player->work[0] == 2 || player->work[0] == 4) {
                    continue;
                }
                if (HuSqrtf(player->trans.x * player->trans.x + player->trans.z * player->trans.z) < 300.0f) {
                    continue;
                }
                player->work[3] = 0;
                D_8010C0E8_hand_line_sinker--;
            }
            if (D_8010C0E8_hand_line_sinker < 3) {
                obj->work[1] = 3;
                for (i = 0; i < 3; i++) {
                    player = D_8010C100_hand_line_sinker[i];
                    if ((player->work[0] == 2 || player->work[0] == 4) == FALSE) {
                        player->func = func_80108F44_hand_line_sinker;
                    }
                }
            } else {
                obj->work[1] = 4;
            }
            break;
        case 3:
            count = 3;
            for (i = 0; i < 3; i++) {
                player = D_8010C100_hand_line_sinker[i];
                player->work[3] = 1;
            }
            if (count == 3) {
                obj->work[1] = 4;
            }
            break;
        case 4:
            func_8001C258_main(D_8010C0FC_hand_line_sinker->model[1], 0x4000, 0);
            func_8001C258_main(D_8010C0FC_hand_line_sinker->model[3], 0x4000, 0);
            func_8001C258_main(D_8010C0FC_hand_line_sinker->model[2], 0x4000, 0);
            func_8001C258_main(D_8010C0FC_hand_line_sinker->model[1], 4, 4);
            func_8001C258_main(D_8010C0FC_hand_line_sinker->model[3], 4, 4);
            for (i = 0; i < 6; i++) {
                dist = i * 17.0f;
                pos.y = 240.0f - dist;
                pos.x = sindf(D_8010C0FC_hand_line_sinker->rot.y - 6.0f + rand8() % 13 - 6.0f) * (140.0f - dist) +
                        D_8010C0FC_hand_line_sinker->trans.x;
                pos.z = cosdf(D_8010C0FC_hand_line_sinker->rot.y - 6.0f + rand8() % 13 - 6.0f) * (140.0f - dist) +
                        D_8010C0FC_hand_line_sinker->trans.z;
                effect = func_8000CED8_main(0x85, 0x2A9);
                func_8000CFA4_main(effect, pos.x, pos.y, pos.z);
                func_8000CFD8_main(effect, 16);
            }
            obj->work[1] = 5;
            func_8001C624_main(D_8010C0FC_hand_line_sinker->model[0],
                               HmfModelData[D_8010C0FC_hand_line_sinker->motion[10]].unk02, 0, 6, 2);
            break;
        case 5:
            rot = -D_8010C0FC_hand_line_sinker->rot.y;
            if (rot < 0.0f) {
                rot += 360.0f;
            }
            if (rot < 180.0f) {
                if (rot > 5.0f) {
                    D_8010C0FC_hand_line_sinker->rot.y += 5.0f;
                } else {
                    D_8010C0FC_hand_line_sinker->rot.y += rot;
                }
            } else {
                if (360.0f - rot > 5.0f) {
                    D_8010C0FC_hand_line_sinker->rot.y -= 5.0f;
                } else {
                    D_8010C0FC_hand_line_sinker->rot.y -= 360.0f - rot;
                }
            }
            if (D_8010C0FC_hand_line_sinker->rot.y >= 360.0f) {
                D_8010C0FC_hand_line_sinker->rot.y -= 360.0f;
            }
            if (D_8010C0FC_hand_line_sinker->rot.y < 0.0f) {
                D_8010C0FC_hand_line_sinker->rot.y += 360.0f;
            }
            if (fabs(D_8010C0FC_hand_line_sinker->rot.y) < 0.0001f) {
                HuAudFXPlay(GwPlayer[work->playerNo].chr + 0x287);
                func_8001C624_main(D_8010C0FC_hand_line_sinker->model[0],
                                   HmfModelData[D_8010C0FC_hand_line_sinker->motion[13]].unk02, 0, 6, 0);
                obj->work[1] = 6;
            }
            break;
        case 6:
            if (HmfModelData[D_8010C0FC_hand_line_sinker->model[0]].unk40 >=
                D_800CCF58_main[HmfModelData[D_8010C0FC_hand_line_sinker->model[0]].unk02].unk02) {
                min[1] = min[0] = 10000.0f;
                max[1] = max[0] = -10000.0f;
                for (i = 0; i < 3; i++) {
                    player = D_8010C100_hand_line_sinker[i];
                    work = player->data;
                    D_8010BF00_hand_line_sinker.unk18[i] = work->playerNo;
                    GwPlayer[work->playerNo].bonusCoin = 10;
                    if (player->work[0] == 2 || player->work[0] == 4) {
                        continue;
                    }
                    work->velY = 60.0f;
                    work->splashed = 0;
                    func_8004ACE0_main(0x28F, work->playerNo);
                    player->func = func_80108C5C_hand_line_sinker;
                    player->work[0] = 5;
                    if (player->trans.x < min[0]) {
                        min[0] = player->trans.x;
                    }
                    if (player->trans.z < min[1]) {
                        min[1] = player->trans.z;
                    }
                    if (player->trans.x > max[0]) {
                        max[0] = player->trans.x;
                    }
                    if (player->trans.z > max[1]) {
                        max[1] = player->trans.z;
                    }
                }
                D_8010C110_hand_line_sinker.center.x = (min[0] + max[0]) / 2.0f;
                D_8010C110_hand_line_sinker.center.z = (min[1] + max[1]) / 2.0f;
                D_8010C110_hand_line_sinker.rot.x = 318.0f;
                if (D_8010C110_hand_line_sinker.center.z > 0.0f) {
                    D_8010C110_hand_line_sinker.rot.x = 318.0f - D_8010C110_hand_line_sinker.center.z / 730.0f * 20.0f;
                }
                D_8010C110_hand_line_sinker.zoom = 1700.0f;
                func_8010B5EC_hand_line_sinker(&D_8010BF28_hand_line_sinker, &D_8010C110_hand_line_sinker, 16);
                D_8010C190_hand_line_sinker->work[1] = 1;
                D_8010C190_hand_line_sinker->work[2] = 1;
                D_8010BF00_hand_line_sinker.unk06 = 2;
                obj->work[0] = 1;
            }
            break;
    }
}

omObjData *func_8010A554_hand_line_sinker(void) {
    omObjData *closest;
    omObjData *obj;
    f32 minDist;
    f32 dist;
    s32 i;

    minDist = 100000.0f;
    closest = NULL;
    for (i = 0; i < 3; i++) {
        obj = D_8010C100_hand_line_sinker[i];
        dist = HuSqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
        if (dist < minDist) {
            minDist = dist;
            closest = obj;
        }
    }
    return closest;
}

void func_8010A5F0_hand_line_sinker(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 6; j++) {
            D_8010C148_hand_line_sinker[i][j] = func_8000B108_main(D_8010BFA0_hand_line_sinker[i], 0x1A9D);
            if (i == 0) {
                func_8001C2FC_main(D_8010C148_hand_line_sinker[0][j], 0x20000000, 0x20000000);
            }
            D_8010C160_hand_line_sinker[j] = 0;
        }
    }
}

void func_8010A6D0_hand_line_sinker(omObjData *parent, u16 type, Vec *offset, Vec *rot) {
    HandLineSinkerFollowWork *work;
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_8010C160_hand_line_sinker[i] == NULL) {
            break;
        }
    }
    if (i == 6) {
        return;
    }
    D_8010C160_hand_line_sinker[i] = omAddObj(0x28, 1, 0, -1, D_8010BFA8_hand_line_sinker[type]);
    D_8010C160_hand_line_sinker[i]->data = HuMemAllocTag(sizeof(HandLineSinkerFollowWork), 0x7918);
    work = D_8010C160_hand_line_sinker[i]->data;
    D_8010C160_hand_line_sinker[i]->work[0] = i;
    func_8001C258_main(D_8010C148_hand_line_sinker[type][i], 4, 0);
    D_8010C160_hand_line_sinker[i]->model[0] = D_8010C148_hand_line_sinker[type][i];
    func_8001C6A8_main(D_8010C160_hand_line_sinker[i]->model[0], 0);
    work->parent = parent;
    work->offset = *offset;
    work->unk10 = *rot;
    if (parent == NULL) {
        omSetTra(D_8010C160_hand_line_sinker[i], offset->x, offset->y, offset->z);
    } else {
        omSetTra(D_8010C160_hand_line_sinker[i], parent->trans.x + offset->x, parent->trans.y + offset->y,
                 parent->trans.z + offset->z);
    }
    omSetRot(D_8010C160_hand_line_sinker[i], rot->x, rot->y, rot->z);
    Hu3DModelPosSet(D_8010C160_hand_line_sinker[i]->model[0], D_8010C160_hand_line_sinker[i]->trans.x,
                    D_8010C160_hand_line_sinker[i]->trans.y, D_8010C160_hand_line_sinker[i]->trans.z);
    Hu3DModelRotSet(D_8010C160_hand_line_sinker[i]->model[0], D_8010C160_hand_line_sinker[i]->rot.x,
                    D_8010C160_hand_line_sinker[i]->rot.y, D_8010C160_hand_line_sinker[i]->rot.z);
}

void func_8010A904_hand_line_sinker(omObjData *obj) {
    HandLineSinkerFollowWork *work = obj->data;

    if (work->parent != NULL) {
        omSetTra(obj, work->parent->trans.x + work->offset.x, work->parent->trans.y + work->offset.y,
                 work->parent->trans.z + work->offset.z);
    }
    if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
        func_8001C258_main(obj->model[0], 4, 4);
        D_8010C160_hand_line_sinker[obj->work[0]] = 0;
        omDelObj(obj);
    }
}

void func_8010A9F8_hand_line_sinker(omObjData *obj) {
    HandLineSinkerFollowWork *work = obj->data;

    if (work->parent != NULL) {
        omSetTra(obj, work->parent->trans.x + work->offset.x, work->parent->trans.y + work->offset.y,
                 work->parent->trans.z + work->offset.z);
    }
    if (D_800CCF58_main[HmfModelData[obj->model[0]].unk02].unk02 <= HmfModelData[obj->model[0]].unk40) {
        func_8001C258_main(obj->model[0], 4, 4);
        D_8010C160_hand_line_sinker[obj->work[0]] = 0;
        omDelObj(obj);
    }
}

f32 func_8010AAEC_hand_line_sinker(f32 x) {
    f32 fx;
    f32 slope;
    f32 prev;
    s32 i;

    for (i = 0; i < 64; i++) {
        fx = func_8010ABD4_hand_line_sinker(x);
        if (fx == 0.0f) {
            break;
        }
        slope = (func_8010ABD4_hand_line_sinker(x + fx) - fx) / fx;
        if (slope < 1e-10f) {
            break;
        }
        prev = x;
        x -= fx / slope;
        if (fabs((x - prev) / x) < 1e-6f) {
            break;
        }
    }
    return x;
}

#ifdef NON_MATCHING
/* Only difference: the target has an extra nop between the second logf call's delay slot and the
 * following mul.s (assembler vr4300 mul fix, likely triggered by a label at that point in the original). */
f32 func_8010ABD4_hand_line_sinker(f32 a) {
    f32 b;
    f32 t;
    f32 s;
    f32 start;
    f32 end;

    b = (D_8010C140_hand_line_sinker - D_8010C138_hand_line_sinker) /
            (D_8010C13C_hand_line_sinker - D_8010C134_hand_line_sinker) -
        a * (D_8010C134_hand_line_sinker + D_8010C13C_hand_line_sinker);

    t = 2.0f * a * D_8010C134_hand_line_sinker + b;
    s = HuSqrtf(t * t + 1.0f);
    if (t + s > 0.0f) {
        start = t * s + logf(t + s);
    } else {
        start = t * s - 1.0f;
    }

    t = 2.0f * a * D_8010C13C_hand_line_sinker + b;
    s = HuSqrtf(t * t + 1.0f);
    if (t + s > 0.0f) {
        end = t * s + logf(t + s);
    } else {
        end = t * s - 1.0f;
    }

    if (a != 0.0f) {
        end = (end - start) / (a * 4.0f) - D_8010C130_hand_line_sinker;
    } else {
        end = -D_8010C130_hand_line_sinker;
    }
    return end;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/11A480", func_8010ABD4_hand_line_sinker);
#endif

void func_8010AD7C_hand_line_sinker(omObjData *obj, f32 length, f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1) {
    HandLineSinkerObjWork *work;
    f32 temp;
    f32 dx;
    f32 dz;
    f32 angle;
    f32 sin;
    f32 cos;
    f32 end;
    f32 slope;
    f32 intercept;
    f32 a;
    f32 t;
    s32 i;

    work = obj->data;
    if (length < HuSqrtf((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) + (z1 - z0) * (z1 - z0)) * 1.0001f) {
        work->points[0].x = x0;
        work->points[0].y = y0;
        work->points[0].z = z0;
        work->points[1].x = x1;
        work->points[1].y = y1;
        work->points[1].z = z1;
        work->numPoints = 2;
        return;
    }
    if (z1 < z0) {
        temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
        temp = z0;
        z0 = z1;
        z1 = temp;
    }
    dx = x1 - x0;
    dz = z1 - z0;
    angle = atan2df(dx, dz);
    sin = sindf(angle);
    cos = cosdf(angle);
    end = dx * sin + dz * cos + z0;
    slope = (y0 - y1) / (z0 - end);
    intercept = (z0 * y1 - end * y0) / (z0 - end);
    D_8010C130_hand_line_sinker = length * 0.00041666668f;
    D_8010C138_hand_line_sinker = y0 * 0.00041666668f;
    D_8010C140_hand_line_sinker = y1 * 0.00041666668f;
    D_8010C134_hand_line_sinker = z0 * 0.00041666668f;
    D_8010C13C_hand_line_sinker = end * 0.00041666668f;
    a = func_8010AAEC_hand_line_sinker(20000.0f);
    if (a < 0.0f) {
        a = -a;
    }
    a *= 0.00041666668f;
    work->points[0].x = x0;
    work->points[0].y = y0;
    work->points[0].z = z0;
    for (i = 1; i < 23; i++) {
        work->points[i].x = (x1 - x0) / 24.0f + work->points[i - 1].x;
        work->points[i].z = (z1 - z0) / 24.0f + work->points[i - 1].z;
        t = (work->points[i].x - x0) * sin + (work->points[i].z - z0) * cos + z0;
        work->points[i].y = a * (t - z0) * (t - end) + slope * t + intercept;
    }
    work->points[i].x = x1;
    work->points[i].y = y1;
    work->points[i].z = z1;
    work->numPoints = 24;
}

void func_8010B0FC_hand_line_sinker(omObjData *arg0, f32 arg1) {
    HandLineSinkerObjWork *work;
    f32 ratio;
    f32 volume;

    work = arg0->data;
    ratio = 1.0f - (HuSqrtf((arg0->trans.x - work->pos.x) * (arg0->trans.x - work->pos.x) +
                            (arg0->trans.z - work->pos.z) * (arg0->trans.z - work->pos.z)) /
                    730.0f) *
                       2;
    if (ratio < 0.0f) {
        ratio = 0.0f;
    }
    volume = arg1 + (127.0f - arg1) * ratio;
    if (volume > 127.0f) {
        volume = 127.0f;
    }
    if (work->seNo >= 0) {
        func_8004AAD0_main(work->seNo, volume);
    }
}

void func_8010B1E4_hand_line_sinker(omObjData *obj) {
    HandLineSinkerObjWork *work;
    f32 px;
    f32 pz;
    f32 x;
    f32 z;
    f32 ox;
    f32 oz;
    f32 dist;
    s32 i;
    s32 j;
    s32 k;

    work = obj->data;
    x = obj->trans.x + sindf(obj->rot.y) * work->unk4;
    z = obj->trans.z + cosdf(obj->rot.y) * work->unk4;
    for (i = 0; i < 2; i++) {
        px = x + sindf(i * 180.0f + obj->rot.y) * 67.5f;
        pz = z + cosdf(i * 180.0f + obj->rot.y) * 67.5f;
        for (j = 0; j < 3; j++) {
            if (obj == D_8010C100_hand_line_sinker[j]) {
                continue;
            }
            if (D_8010C100_hand_line_sinker[j]->work[0] == 2 || D_8010C100_hand_line_sinker[j]->work[0] == 3 ||
                D_8010C100_hand_line_sinker[j]->work[0] == 4) {
                continue;
            }
            for (k = 0; k < 2; k++) {
                ox = D_8010C100_hand_line_sinker[j]->trans.x +
                     sindf(D_8010C100_hand_line_sinker[j]->rot.y + k * 180.0f) * 67.5f;
                oz = D_8010C100_hand_line_sinker[j]->trans.z +
                     cosdf(D_8010C100_hand_line_sinker[j]->rot.y + k * 180.0f) * 67.5f;
                dist = HuSqrtf((ox - px) * (ox - px) + (oz - pz) * (oz - pz));
                if (dist < 135.0f) {
                    x -= sindf(i * 180.0f + obj->rot.y) * (135.0f - dist);
                    z -= cosdf(i * 180.0f + obj->rot.y) * (135.0f - dist);
                    px = x + sindf(i * 180.0f + obj->rot.y) * 67.5f;
                    pz = z + cosdf(i * 180.0f + obj->rot.y) * 67.5f;
                    work->unk4 = 0.0f;
                    break;
                }
            }
        }
        dist = HuSqrtf(px * px + pz * pz);
        if (dist > 662.5f) {
            x -= sindf(i * 180.0f + obj->rot.y) * (dist - 662.5f);
            z -= cosdf(i * 180.0f + obj->rot.y) * (dist - 662.5f);
            work->unk4 = 0.0f;
            break;
        }
    }
    omSetTra(obj, x, obj->trans.y, z);
}
