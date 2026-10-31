#include "common.h"
#include "overlays/minigame.h"
#include "mallocblock.h"
#include "game/pause.h"

typedef struct UnkCrazyCogsCog { // 0x84 bytes, one entry per cog slot
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ u16 timer;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ s16 unk_42;
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ Vec unk_78;
} UnkCrazyCogsCog;

typedef struct {
    /* 0x00 */ u8 unk_00[3];
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05[0xAF];
} CrazyCogsSetupWork;

typedef struct {
    u8 xTimer;
    s8 xDuration;
    s8 xSpeed;
    s8 xDirection;
    u8 zTimer;
    s8 zDuration;
    s8 zSpeed;
    s8 zDirection;
} CrazyCogsMovement;

typedef struct {
    u8 xTimer;
    s8 xDuration;
    s8 xStick;
    u8 zTimer;
    s8 zDuration;
    s8 zStick;
} CrazyCogsCpuMovement;

typedef struct {
    f32 scissorX;
    f32 scissorY;
    f32 scissorWidth;
    f32 scissorHeight;
    Vec viewportScale;
    Vec viewportTranslate;
    f32 fov;
} CrazyCogsCamera;

extern CrazyCogsMovement D_8010DE28_crazy_cogs[7];
extern CrazyCogsCpuMovement D_8010DE70_crazy_cogs[3];
extern CrazyCogsCamera D_8010B898_crazy_cogs[2];

extern s16 D_8010B858_crazy_cogs[4];
extern u16 D_8010B860_crazy_cogs[5];
extern s16 D_8010BA30_crazy_cogs;
extern u16 D_8010BA32_crazy_cogs;
extern f32 D_8010BA34_crazy_cogs;
extern f32 D_8010BA38_crazy_cogs;

extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern s32 D_800EBE24_minigame;
extern s16 D_8010B86E_crazy_cogs[8][2];
extern f32 D_8010B88C_crazy_cogs[3];
extern s8 D_8010B9A1_crazy_cogs;
extern s32 D_8010B810_crazy_cogs[8];
extern s8 D_8010B99C_crazy_cogs;
extern s8 D_8010B9A0_crazy_cogs;
extern s8 D_8010B9A2_crazy_cogs;
extern s8 D_8010B9A6_crazy_cogs;
extern s16 D_8010DE08_crazy_cogs[3];
extern s16 D_8010DE0E_crazy_cogs;
extern u8 D_8010DE64_crazy_cogs;
extern u8 D_8010DE69_crazy_cogs;
extern s8 D_8010DE68_crazy_cogs;
extern s8 D_8010DEB4_crazy_cogs;
extern s8 D_8010B996_crazy_cogs;
extern D_80111B50_vine_with_me_Struct D_8010B830_crazy_cogs;
extern const s16 D_8010B97C_crazy_cogs[];
extern s8 D_8010B997_crazy_cogs;
extern s16 D_8010DE62_crazy_cogs;
extern s16 D_8010DE66_crazy_cogs;
extern UnkCrazyCogsCog *D_8010DEB0_crazy_cogs;
extern f32 D_8010DE88_crazy_cogs[10];
extern f32 D_8010B998_crazy_cogs;
extern u16 D_8010B9A4_crazy_cogs;
extern s8 D_8010B990_crazy_cogs;
extern s16 D_8010B994_crazy_cogs;
extern s16 D_8010B99E_crazy_cogs;
extern f32 D_8010B9A8_crazy_cogs;
extern s8 D_8010B9B0_crazy_cogs[50];
extern s8 D_8010B9E2_crazy_cogs;
extern s8 D_8010B9E3_crazy_cogs[13];
extern UnkCrazyCogsCog D_8010B9F0_crazy_cogs[70];
extern omObjData *D_8010BA74_crazy_cogs;
extern omObjData *D_8010BAF8_crazy_cogs;
extern omObjData *D_8010BB7C_crazy_cogs;
extern UnkCrazyCogsCog D_8010C8E4_crazy_cogs[];
extern omObjData *D_8010C5CC_crazy_cogs;
extern omObjData *D_8010C650_crazy_cogs;
extern f32 D_8010DE14_crazy_cogs;
extern s32 D_8010DE18_crazy_cogs[2];
extern s16 D_8010DE22_crazy_cogs;
extern s16 D_8010DE20_crazy_cogs;
extern s8 D_8010B991_crazy_cogs[3];
extern s8 D_8010DE10_crazy_cogs[3];
extern s8 D_8010DE60_crazy_cogs;
extern s8 D_8010DE6A_crazy_cogs[4];

void func_800E6F0C_minigame(s32);
void func_80107778_crazy_cogs(void);
void func_80107AB8_crazy_cogs(void);
void func_80108EE8_crazy_cogs(void);
void func_8010A4A4_crazy_cogs(void);
void func_8010B0F4_crazy_cogs(omObjData *);
void func_8000B710_main(s32);
f32 atan2df(f32, f32);
void func_80088800_main(HuMtx4F, f32, f32, f32);
void func_8004AD8C_main(s16);
void espAttrSet(u16, u16);
void func_800E1304_minigame(omObjData *, f32);
void func_800E1310_minigame(omObjData *, f32);
void func_800E131C_minigame(omObjData *, f32);
void func_800E1404_minigame(omObjData *, f32, f32);
void func_8010908C_crazy_cogs(omObjData *);
void func_8010ABE0_crazy_cogs(omObjData *);
void func_80109388_crazy_cogs(omObjData *);
void func_80109F64_crazy_cogs(omObjData *);
void func_8010B6E0_crazy_cogs(void);
void func_80106270_crazy_cogs(omObjData *);
void func_80106688_crazy_cogs(omObjData *);
void func_8010683C_crazy_cogs(omObjData *);
void func_801069DC_crazy_cogs(omObjData *);
void func_8010A67C_crazy_cogs(omObjData *);
void func_8010AA10_crazy_cogs(omObjData *);
void func_8010AE08_crazy_cogs(omObjData *);
void func_80108B0C_crazy_cogs(omObjData *);
void func_800DDD94_minigame(omObjData *);

void func_801059A0_crazy_cogs(void) {
    func_8010B6E0_crazy_cogs();
}

f32 func_801059BC_crazy_cogs(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void func_80105A3C_crazy_cogs(void) {
    u32 i = 0;
    UnkCrazyCogsCog *cog = D_8010B9F0_crazy_cogs;

    for (; i < 70; i++, cog++) {
        cog->obj = NULL;
        cog->timer = 0;
        cog->unk_06 = 0;
        cog->unk_08 = 0;
        cog->unk_0A = 0;
        cog->unk_0C = 0;
        cog->unk_0E = 0;
        cog->unk_10 = 0;
        cog->unk_12 = 0;
        cog->unk_14 = 0;
        cog->unk_16 = 0;
        cog->unk_18 = 0;
        cog->unk_1C = 0;
        cog->unk_20 = 0;
        cog->unk_24 = 0;
        cog->unk_28 = 0;
        cog->unk_2C = 0;
        cog->unk_30 = 0;
        cog->unk_34 = 0;
        cog->unk_38 = 0;
        cog->unk_3C = 0;
        cog->unk_40 = -1;
        cog->unk_42 = -1;
        cog->unk_44.x = cog->unk_44.y = cog->unk_44.z = 0.0f;
        cog->unk_50.x = cog->unk_50.y = cog->unk_50.z = 0.0f;
        cog->unk_5C.x = cog->unk_5C.y = cog->unk_5C.z = 0.0f;
        cog->unk_68 = 0.0f;
        cog->unk_6C = 0.0f;
        cog->unk_70 = 0.0f;
        cog->unk_74 = 0.0f;
        cog->unk_78.x = cog->unk_78.y = cog->unk_78.z = 0.0f;
    }
}

void func_80105B04_crazy_cogs(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

s32 func_80105B7C_crazy_cogs(s32 arg0) {
    return rand8() % arg0;
}

f32 func_80105BD0_crazy_cogs(omObjData *arg0) {
    f32 x;
    f32 z;
    f32 distance;
    f32 height;

    x = (s32)((arg0->trans.x < 0.0f) ? -arg0->trans.x : arg0->trans.x);
    z = (s32)((arg0->trans.z < 0.0f) ? -arg0->trans.z : arg0->trans.z);
    distance = sqrtf(x * x + z * z);
    if (distance > 480.0f) {
        height = 1.0f;
        x = (s32)(((arg0->trans.x - 580.0f) < 0.0f) ? -(arg0->trans.x - 580.0f) : (arg0->trans.x - 580.0f));
        z = (s32)(((arg0->trans.z + 450.0f) < 0.0f) ? -(arg0->trans.z + 450.0f) : (arg0->trans.z + 450.0f));
        distance = sqrtf(x * x + z * z);
        if (distance <= 380.0f) {
            height = 55.0f;
        }
    } else {
        if ((distance <= 480.0f) & (distance > 350.0f)) {
            height = 55.0f;
        } else {
            height = 28.0f;
        }
    }
    return height;
}

f32 func_80105E4C_crazy_cogs(f32 x, f32 z) {
    f32 angle = 0.0f;
    s32 quadrant = 0;
    f32 absX;
    f32 absZ;

    if (x >= 0.0f) {
        quadrant |= 1;
    } else {
        quadrant |= 2;
    }
    if (z < 0.0f) {
        quadrant |= 4;
    } else {
        quadrant |= 8;
    }
    absX = x;
    if (absX < 0.0f) {
        absX = -absX;
    }
    absZ = z;
    if (absZ < 0.0f) {
        absZ = -absZ;
    }
    switch (quadrant) {
        case 5:
            if (x == 0.0f) {
                return 0.0f;
            }
            angle = 90.0f / (absX + absZ);
            angle *= absX;
            break;
        case 9:
            if (x == 0.0f) {
                return 180.0f;
            }
            if (z == 0.0f) {
                return 90.0f;
            }
            angle = 90.0f / (absX + absZ);
            angle *= absZ;
            angle += 90.0f;
            break;
        case 10:
            if (x == 0.0f) {
                return 270.0f;
            }
            angle = 90.0f / (absX + absZ);
            angle *= absX;
            angle += 180.0f;
            break;
        case 6:
            angle = 90.0f / (absX + absZ);
            angle *= absZ;
            angle += 270.0f;
            break;
    }
    return angle;
}

void func_80106034_crazy_cogs(omObjData *arg0, u16 arg1, s16 arg2) {
    if (arg1 < 0xA) {
        func_8001C5B4_main(arg0->model[0], arg0->motion[arg1]);
        func_8001C814_main(arg0->model[0], arg2, arg2);
    }
}

void func_801060A0_crazy_cogs(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if (arg1 < 0xA) {
        Hu3DMotionShiftSet(arg0->model[0], HmfModelData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
    }
}

f32 func_8010611C_crazy_cogs(f32 angle) {
    if ((angle > 5.0f) & (angle < 355.0f)) {
        if (angle < 180.0f) {
            angle = func_801059BC_crazy_cogs(angle, -6.0f);
        } else {
            angle = func_801059BC_crazy_cogs(angle, 6.0f);
        }
    } else {
        angle = 0.0f;
    }
    return angle;
}

void func_801061CC_crazy_cogs(s16 channel, s16 state) {
    switch (state) {
        case 0:
            osSyncPrintf("\x8E\x95\x8E\xD4\t"); // Cog (Shift-JIS)
            break;
        case 1:
            osSyncPrintf("\x83\x58\x83\x43\x83\x62\x83\x60\t"); // Switch (Shift-JIS)
            break;
        case 2:
            osSyncPrintf("\x91\xAB\x89\xB9\t"); // Footsteps (Shift-JIS)
            break;
        case 3:
            osSyncPrintf("\x83\x4C\x83\x89\x81\x5B\x97\x8E\x89\xBA\t"); // Bullet Bill falling (Shift-JIS)
            break;
        case 4:
            osSyncPrintf("\x94\x9A\x94\xAD\t"); // Explosion (Shift-JIS)
            break;
    }
    osSyncPrintf("ch=%d\n", channel);
}

void func_80106268_crazy_cogs(omObjData *arg0) {
}

void func_80106270_crazy_cogs(omObjData *arg0) {
    CrazyCogsSetupWork *work;

    D_8010BA34_crazy_cogs = 160.0f;
    D_8010BA38_crazy_cogs = 120.0f;
    D_8010BA30_crazy_cogs = func_8000B838_main(0x260000);
    D_8010BA32_crazy_cogs = espEntry(D_8010BA30_crazy_cogs, 0, 0);
    espAttrSet(D_8010BA32_crazy_cogs, 0x5000);
    espPosSet(D_8010BA32_crazy_cogs, D_8010BA34_crazy_cogs, D_8010BA38_crazy_cogs);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = arg0;
    work = HuMemAllocTag(sizeof(CrazyCogsSetupWork), TAG_OVERLAY);
    arg0->data = work;
    memset(work, 0, sizeof(CrazyCogsSetupWork));
    work->unk_03 = 1;
    work->unk_04 = 0;
    func_800E131C_minigame(arg0, 20.0f);
    func_800E1304_minigame(arg0, 0.5f);
    func_800E1310_minigame(arg0, 10.0f);
    func_800E1404_minigame(D_800EC1C0_minigame[0], 0.0f, 360.0f);
    arg0->model[0] = -1;
    arg0->func = func_80106268_crazy_cogs;
}

void func_801063DC_crazy_cogs(void) {
    D_8010B9F0_crazy_cogs[0].obj = omAddObj(0x1F4, 1, 0, -1, func_80106270_crazy_cogs);
}

void func_80106418_crazy_cogs(omObjData *arg0) {
    s8 cogIdx = ((s8 *)arg0->work)[3];
    UnkCrazyCogsCog *cog = &D_8010C8E4_crazy_cogs[cogIdx];

    if (D_8010DE6A_crazy_cogs[cogIdx] != 0) {
        if (cog->timer & 1) {
            arg0->trans.y = 10.0f;
        } else {
            arg0->trans.y = 0.0f;
        }

        cog->timer++;

        if ((s16)cog->timer >= 0x14) {
            cog->timer = 0;
            D_8010DE6A_crazy_cogs[cogIdx] = 0;
        }
    }
}

void func_801064AC_crazy_cogs(omObjData *arg0) {
    s8 cogIdx = ((s8 *)arg0->work)[3];

    arg0->model[0] = func_8000B108_main(0x260000 | D_8010B858_crazy_cogs[cogIdx], 0xB9);
    arg0->trans.x = 0.0f;
    arg0->trans.y = 0.0f;
    arg0->trans.z = 0.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    D_8010DE6A_crazy_cogs[cogIdx] = 0;
    arg0->func = func_80106418_crazy_cogs;
}

void func_8010654C_crazy_cogs(void) {
    s8 i;
    UnkCrazyCogsCog *cog;

    for (i = 0; i < 4; i++) {
        cog = &D_8010C8E4_crazy_cogs[i];
        cog->obj = omAddObj(0x6A4, 1, 0, -1, func_801064AC_crazy_cogs);
        cog->obj->work[0] = i;
    }
}

void func_801065F0_crazy_cogs(omObjData *arg0) {
    switch (D_8010DE60_crazy_cogs) {
        case 0:
            break;
        case 1:
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, -3.3f);
            break;
        case 2:
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, 3.3f);
            break;
    }
    Hu3DModelRotSet(arg0->model[1], arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

void func_80106688_crazy_cogs(omObjData *arg0) {
    arg0->model[0] = func_8000B108_main(0x260002, 0xB9);
    arg0->model[1] = func_8000B108_main(0x260005, 0xB9);
    arg0->trans.x = arg0->trans.y = arg0->trans.z = 0.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    arg0->func = func_801065F0_crazy_cogs;
    D_8010B9A8_crazy_cogs = 4.4f;
    D_8010DE14_crazy_cogs = 6.6000004f;
}

void func_80106770_crazy_cogs(void) {
    D_8010BA74_crazy_cogs = omAddObj(0x3E8, 2, 0, -1, func_80106688_crazy_cogs);
}

void func_801067AC_crazy_cogs(omObjData *arg0) {
    switch (D_8010DE60_crazy_cogs) {
        case 0:
            break;
        case 1:
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, D_8010B9A8_crazy_cogs);
            break;
        case 2:
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, -D_8010B9A8_crazy_cogs);
            break;
    }

    Hu3DModelRotSet(arg0->model[1], arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

void func_8010683C_crazy_cogs(omObjData *arg0) {
    arg0->model[0] = func_8000B108_main(0x260003, 0xB9);
    arg0->model[1] = func_8000B108_main(0x260006, 0xB9);
    arg0->trans.x = 580.0f;
    arg0->trans.y = 0.0f;
    arg0->trans.z = -450.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    arg0->func = func_801067AC_crazy_cogs;
}

void func_80106910_crazy_cogs(void) {
    D_8010BAF8_crazy_cogs = omAddObj(0x44C, 2, 0, -1, func_8010683C_crazy_cogs);
}

void func_8010694C_crazy_cogs(omObjData *arg0) {
    switch (D_8010DE60_crazy_cogs) {
        case 0:
            break;
        case 1:
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, -D_8010DE14_crazy_cogs);
            break;
        case 2:
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, D_8010DE14_crazy_cogs);
            break;
    }

    Hu3DModelRotSet(arg0->model[1], arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

void func_801069DC_crazy_cogs(omObjData *arg0) {
    arg0->model[0] = func_8000B108_main(0x260004, 0xB9);
    arg0->model[1] = func_8000B108_main(0x260007, 0xB9);
    arg0->trans.x = 185.0f;
    arg0->trans.y = 0.0f;
    arg0->trans.z = -800.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    arg0->func = func_8010694C_crazy_cogs;
}

void func_80106AB0_crazy_cogs(void) {
    D_8010BB7C_crazy_cogs = omAddObj(0x4B0, 2, 0, -1, func_801069DC_crazy_cogs);
}

void func_80106AEC_crazy_cogs(s8 direction) {
    D_8010DE60_crazy_cogs = direction;
    D_8010B9A6_crazy_cogs = 0;
    D_8010DEB4_crazy_cogs = func_80105B7C_crazy_cogs(5) + 10;
}

void func_80106B24_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *target;
    UnkCrazyCogsCog *player;
    f32 targetAngle;
    f32 playerAngle;
    f32 difference;
    u16 distance;

    target = &(&D_8010B9F0_crazy_cogs[8])[D_8010B9B0_crazy_cogs[D_8010B990_crazy_cogs]];
    if ((s16)target->timer == 0) {
        D_8010B9F0_crazy_cogs[4].unk_06 = 0;
        D_8010B9F0_crazy_cogs[4].unk_08 = 0;
        D_8010B9F0_crazy_cogs[4].unk_0A = 0;
        D_8010B9F0_crazy_cogs[4].unk_0C = 0;
        D_8010DE68_crazy_cogs = 0;
        D_8010B990_crazy_cogs++;
        return;
    }
    player = &D_8010B9F0_crazy_cogs[D_8010B9A2_crazy_cogs];
    if (player->unk_0E != 0) {
        D_8010DE68_crazy_cogs = 1;
        return;
    }
    targetAngle = func_80105E4C_crazy_cogs(target->obj->trans.x, target->obj->trans.z);
    playerAngle = func_80105E4C_crazy_cogs(player->obj->trans.x, player->obj->trans.z);
    distance = (s32)((targetAngle - playerAngle < 0.0f) ? -(targetAngle - playerAngle) : targetAngle - playerAngle);
    if ((distance < 5) || (distance >= 356)) {
        D_8010DE60_crazy_cogs = 0;
        return;
    }
    if (D_8010B9A6_crazy_cogs > D_8010DEB4_crazy_cogs) {
        difference = targetAngle - playerAngle;
        if (difference >= 0.0f) {
            if (((difference < 0.0f) ? -difference : difference) >= 180.0f) {
                func_80106AEC_crazy_cogs(2);
            } else {
                func_80106AEC_crazy_cogs(1);
            }
        } else {
            if (((difference < 0.0f) ? -difference : targetAngle - playerAngle) >= 180.0f) {
                func_80106AEC_crazy_cogs(1);
            } else {
                func_80106AEC_crazy_cogs(2);
            }
        }
    } else {
        D_8010B9A6_crazy_cogs++;
    }
}

void func_80106D54_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *target;
    UnkCrazyCogsCog *controller;
    UnkCrazyCogsCog *player;
    s16 i;
    f32 targetAngle;
    f32 difference;
    u16 distance;

    target = &(&D_8010B9F0_crazy_cogs[8])[D_8010B9B0_crazy_cogs[D_8010B990_crazy_cogs]];
    controller = &D_8010B9F0_crazy_cogs[4];
    if ((s16)target->timer == 0) {
        controller->unk_06 = 0;
        controller->unk_08 = 0;
        controller->unk_0A = 0;
        controller->unk_0C = 0;
        D_8010DE68_crazy_cogs = 0;
        D_8010B990_crazy_cogs++;
        return;
    }
    targetAngle = func_80105E4C_crazy_cogs(target->obj->trans.x, target->obj->trans.z);
    for (i = 0; i < 3; i++) {
        player = &(&D_8010B9F0_crazy_cogs[5])[i];
        if (player->unk_0E == 0) {
            difference = func_80105E4C_crazy_cogs(player->obj->trans.x, player->obj->trans.z);
            distance = (s32)((targetAngle - difference < 0.0f) ? -(targetAngle - difference) : targetAngle - difference);
            if (distance < 20 || distance >= 341) {
                controller->unk_0C = 0;
                D_8010B9A2_crazy_cogs = i + 5;
                D_8010DE68_crazy_cogs = 2;
                return;
            }
        }
    }
    if (D_8010B9A6_crazy_cogs > D_8010DEB4_crazy_cogs) {
        switch (controller->unk_0C) {
            case 0:
                controller->unk_0C = func_80105B7C_crazy_cogs(2);
                break;
            case 1:
                func_80106AEC_crazy_cogs(1);
                break;
            case 2:
                func_80106AEC_crazy_cogs(2);
                break;
        }
    } else {
        D_8010B9A6_crazy_cogs++;
    }
}

void func_80106F54_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *controller = &D_8010B9F0_crazy_cogs[4];

    switch (D_8010B9B0_crazy_cogs[D_8010B990_crazy_cogs]) {
        case -1:
            break;
        case 4:
        case 5:
        case 6:
            D_8010DE68_crazy_cogs = 1;
            return;
    }
    controller->unk_06++;
    if ((s16)controller->unk_06 >= controller->unk_08) {
        controller->unk_06 = 0;
        controller->unk_08 = D_8010B860_crazy_cogs[func_80105B7C_crazy_cogs(5)];
        controller->unk_0A = func_80105B7C_crazy_cogs(2);
    }
    if (D_8010B9A6_crazy_cogs > D_8010DEB4_crazy_cogs) {
        switch (controller->unk_0A) {
            case 0:
                func_80106AEC_crazy_cogs(1);
                break;
            case 1:
                func_80106AEC_crazy_cogs(2);
                break;
        }
    } else {
        D_8010B9A6_crazy_cogs++;
    }
}

void func_80107078_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *controller = &D_8010B9F0_crazy_cogs[4];
    s16 frame;

    switch (D_8010DE60_crazy_cogs) {
        case 0:
            if (D_8010DE0E_crazy_cogs < 0) {
                D_8010DE0E_crazy_cogs += 5;
            }
            if (D_8010DE0E_crazy_cogs > 0) {
                D_8010DE0E_crazy_cogs -= 5;
            }
            if (controller->unk_0E != 0 || controller->unk_10 != 0) {
                func_8004AD8C_main(0x323);
                controller->unk_10 = 0;
                controller->unk_0E = 0;
            }
            break;
        case 1:
            if (D_8010DE0E_crazy_cogs < 30) {
                D_8010DE0E_crazy_cogs += 5;
            }
            if (controller->unk_0E == 0) {
                HuAudFXPlay(0x322);
                func_8004AC98_main(0x323, ((s16 *)arg0->work)[1]);
                controller->unk_0E = 1;
                controller->unk_10 = 0;
            }
            break;
        case 2:
            if (D_8010DE0E_crazy_cogs > -30) {
                D_8010DE0E_crazy_cogs -= 5;
            }
            if (controller->unk_10 == 0) {
                HuAudFXPlay(0x322);
                func_8004AC98_main(0x323, ((s16 *)arg0->work)[1]);
                controller->unk_0E = 0;
                controller->unk_10 = 1;
            }
            break;
    }
    frame = D_8010DE0E_crazy_cogs + 30;
    func_801060A0_crazy_cogs(arg0, 0, frame, 1, 1);
    Hu3DMotionTimeSet(arg0->model[1], frame);
    Hu3DModelPosSet(arg0->model[2], D_8010DE0E_crazy_cogs * 2.5f + arg0->trans.x, arg0->trans.y, arg0->trans.z + 40.0f);
}

void func_8010728C_crazy_cogs(omObjData *arg0) {
    s8 character = GwPlayer[arg0->work[0]].chr;

    if (D_8010B99C_crazy_cogs != 2) {
        if (D_8010B99C_crazy_cogs == 6) {
            Hu3DModelPosSet(arg0->model[2], arg0->trans.x, arg0->trans.y, arg0->trans.z);
            if (D_8010B9A0_crazy_cogs < 0) {
                func_80106034_crazy_cogs(arg0, 3, 0);
                func_80045ED0_main((D_8010B810_crazy_cogs[character] << 16) | 0x30);
            }
            if (D_8010B9A0_crazy_cogs > 0) {
                func_80106034_crazy_cogs(arg0, 4, 0);
            }
        } else {
            func_80107078_crazy_cogs(arg0);
        }
    } else {
        func_80107078_crazy_cogs(arg0);
        if (GwPlayer[arg0->work[0]].stat & 1) {
            switch (D_8010DE68_crazy_cogs) {
                case 0:
                    func_80106F54_crazy_cogs(arg0);
                    break;
                case 1:
                    func_80106D54_crazy_cogs(arg0);
                    break;
                case 2:
                    func_80106B24_crazy_cogs(arg0);
                    break;
            }
        } else {
            if (((D_800CBB6E_main[arg0->work[3]] < 0) ? -D_800CBB6E_main[arg0->work[3]] : D_800CBB6E_main[arg0->work[3]]) < 15) {
                D_8010DE60_crazy_cogs = 0;
            } else if (D_800CBB6E_main[arg0->work[3]] > 30) {
                D_8010DE60_crazy_cogs = 1;
            } else if (D_800CBB6E_main[arg0->work[3]] < -30) {
                D_8010DE60_crazy_cogs = 2;
            }
        }
    }
}

void func_801074A0_crazy_cogs(omObjData *arg0) {
    u16 character = GwPlayer[arg0->work[0]].chr;

    arg0->model[0] = func_8000B108_main(D_800A178C_main[character][0] | D_800A1790_main[character][0], 0x2B9);
    func_8000B460_main(arg0, 0, func_80017BB8_main(character, 0x3F));
    func_8000B460_main(arg0, 3, func_80017BB8_main(character, 0x30));
    func_8000B460_main(arg0, 4, func_80017BB8_main(character, D_8010B86E_crazy_cogs[character][0]));
    func_80106034_crazy_cogs(arg0, 0, 1);
    Hu3DMotionTimeSet(arg0->model[0], 30.0f);
    Hu3DMotionSpeedSet(arg0->model[0], 1.0f);
    Hu3DMotionTimeSet(arg0->model[1], 30.0f);
    Hu3DMotionSpeedSet(arg0->model[1], 1.0f);
    arg0->model[1] = func_8000B108_main(0x260001, 0xD9);
    arg0->model[2] = func_8000B0A0_main(0, 0x14C9);
    func_8001C2FC_main(arg0->model[2], 0x80000000, 0);
    func_8001C448_main(arg0->model[2]);
    func_8001C514_main(arg0->model[2]);
    func_80088800_main(HmfModelData[arg0->model[2]].mtx, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[2], HU3D_CAM0);
    arg0->trans.x = -600.0f;
    arg0->trans.y = 50.0f;
    arg0->trans.z = -600.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[2], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    D_8010B9A6_crazy_cogs = 20;
    D_8010DEB4_crazy_cogs = 0;
    D_8010B9A1_crazy_cogs = GwPlayer[arg0->work[0]].cpu_difficulty;
    D_8010B9F0_crazy_cogs[4].unk_0A = func_80105B7C_crazy_cogs(2);
    arg0->work[3] = GwPlayer[arg0->work[0]].pad;
    arg0->func = func_8010728C_crazy_cogs;
}

void func_80107778_crazy_cogs(void) {
    omObjData *obj;
    UnkCrazyCogsCog *cog = &D_8010B9F0_crazy_cogs[4];
    s16 i;
    u16 playerIndex;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    switch (i) {
        case 0:
            playerIndex = 0;
            break;
        case 1:
            playerIndex = 1;
            break;
        case 2:
            playerIndex = 2;
            break;
        case 3:
            playerIndex = 3;
            break;
        default:
            playerIndex = 0;
            break;
    }
    obj = omAddObj(0x2BC, 3, 4, -1, func_801074A0_crazy_cogs);
    obj->work[0] = playerIndex;
    cog->obj = obj;
    D_8010DE64_crazy_cogs = obj->work[0];
    D_8010DE69_crazy_cogs = GwPlayer[obj->work[0]].chr;
}

void func_8010787C_crazy_cogs(omObjData *arg0) {
}

void func_80107884_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&D_8010B9F0_crazy_cogs[25])[arg0->work[1]];
    u16 character = GwPlayer[arg0->work[0]].chr;
    f32 angle;

    arg0->model[0] = func_8000B108_main(D_800A178C_main[character][0] | D_800A1790_main[character][0], 0x2B9);
    func_8000B460_main(arg0, 1, func_80017BB8_main(character, 0));
    func_8000B460_main(arg0, 2, func_80017BB8_main(character, 2));
    func_80106034_crazy_cogs(arg0, 1, 2);
    arg0->model[1] = func_8000B0A0_main(0, 0x14C9);
    func_8001C2FC_main(arg0->model[1], 0x80000000, 0);
    func_8001C448_main(arg0->model[1]);
    func_8001C514_main(arg0->model[1]);
    func_80088800_main(HmfModelData[arg0->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    angle = func_801059BC_crazy_cogs(0.0f, (s16)cog->timer * 120);
    arg0->trans.x = sindf(angle) * 90.0f;
    arg0->trans.y = 28.0f;
    arg0->trans.z = cosdf(angle) * 90.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    arg0->func = func_8010787C_crazy_cogs;
}

void func_80107AB8_crazy_cogs(void) {
    omObjData *obj;
    s8 positions[3];
    s8 available[3];
    s8 i;
    s8 j;
    s8 count;
    s8 position;
    s32 cogIndex;
    u16 playerIndex;
    UnkCrazyCogsCog *cog;

    for (i = 0; i < 3; i++) {
        positions[i] = i;
        available[i] = 1;
    }
    playerIndex = 0;
    cogIndex = 0;
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            switch (i) {
                case 0:
                    playerIndex = 0;
                    break;
                case 1:
                    playerIndex = 1;
                    break;
                case 2:
                    playerIndex = 2;
                    break;
                case 3:
                    playerIndex = 3;
                    break;
            }
            cog = &(&D_8010B9F0_crazy_cogs[25])[cogIndex];
            obj = omAddObj(0x320, 3, 3, -1, func_80107884_crazy_cogs);
            obj->work[0] = playerIndex;
            cog->obj = obj;
            obj->work[1] = cogIndex;
            position = func_80105B7C_crazy_cogs(3 - cogIndex);
            cog->timer = positions[position];
            available[positions[position]] = 0;
            j = 0;
            count = 0;
            for (; j < 3; j++) {
                if (available[j] != 0) {
                    positions[count] = j;
                    count++;
                }
            }
            cogIndex++;
        }
    }
}

void func_80107CA8_crazy_cogs(f32 *x, f32 *z, f32 angle) {
    f32 radius = sqrtf(*x * *x + *z * *z);
    f32 direction = func_801059BC_crazy_cogs(atan2df(*x, *z), angle);

    *x = radius * sindf(direction);
    *z = radius * cosdf(direction);
}

void func_80107D58_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&D_8010B9F0_crazy_cogs[25])[arg0->work[1]];

    if (arg0->work[2] == 0) {
        if (cog->unk_16 != 0) {
            HuAudFXStop(cog->unk_16);
        }
        cog->unk_16 = PlayerFXPlay(0x28, ((s16 *)arg0->work)[1]);
    }
    arg0->work[2] = (arg0->work[2] + 1) % 11;
}

void func_80107E00_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&D_8010B9F0_crazy_cogs[5])[arg0->work[1]];
    UnkCrazyCogsCog *introCog = &(&D_8010B9F0_crazy_cogs[25])[arg0->work[1]];

    switch (cog->unk_12) {
        case 0:
            cog->unk_16++;
            if (cog->unk_16 == 20) {
                cog->unk_12 = 1;
                cog->unk_16 = 0;
                D_8010DE60_crazy_cogs = 1;
                func_80106034_crazy_cogs(introCog->obj, 2, 2);
            }
            break;
        case 1:
            introCog->obj->rot.y = D_8010B88C_crazy_cogs[(s16)introCog->timer];
            func_80107D58_crazy_cogs(arg0);
            cog->unk_16++;
            if (cog->unk_16 == 40) {
                cog->unk_12 = 4;
                cog->unk_16 = 0;
                D_8010DE60_crazy_cogs = 2;
            }
            break;
        case 2:
            introCog->obj->rot.y = func_801059BC_crazy_cogs(D_8010B88C_crazy_cogs[(s16)introCog->timer], -180.0f);
            func_80107D58_crazy_cogs(arg0);
            cog->unk_16++;
            if (cog->unk_16 == 40) {
                cog->unk_12++;
                cog->unk_16 = 0;
                D_8010DE60_crazy_cogs = 1;
            }
            break;
        case 3:
            introCog->obj->rot.y = D_8010B88C_crazy_cogs[(s16)introCog->timer];
            func_80107D58_crazy_cogs(arg0);
            cog->unk_16++;
            if (cog->unk_16 == 30) {
                cog->unk_12++;
                cog->unk_16 = 0;
                D_8010DE60_crazy_cogs = 2;
            }
            break;
        case 4:
            introCog->obj->rot.y = func_801059BC_crazy_cogs(D_8010B88C_crazy_cogs[(s16)introCog->timer], -180.0f);
            func_80107D58_crazy_cogs(arg0);
            cog->unk_16++;
            if (cog->unk_16 == 30) {
                cog->unk_12++;
                cog->unk_16 = 0;
                D_8010DE60_crazy_cogs = 0;
                arg0->trans.x = introCog->obj->trans.x;
                arg0->trans.y = introCog->obj->trans.y;
                arg0->trans.z = introCog->obj->trans.z;
                func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                func_8001C258_main(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                func_8001C258_main(introCog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                func_8001C258_main(introCog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            break;
        case 5:
            switch ((s16)introCog->timer) {
                case 0:
                    D_800D20A1_main[arg0->work[3]] = -67;
                    break;
                case 1:
                    D_800CBB6E_main[arg0->work[3]] = 60;
                    D_800D20A1_main[arg0->work[3]] = 30;
                    break;
                case 2:
                    D_800CBB6E_main[arg0->work[3]] = -60;
                    D_800D20A1_main[arg0->work[3]] = 30;
                    break;
            }
            cog->unk_16++;
            if (cog->unk_16 == 18) {
                cog->unk_12 = 0;
                D_8010DE62_crazy_cogs = 1;
            }
            break;
        case 6:
            cog->unk_16++;
            if (cog->unk_16 == 30) {
                cog->unk_12 = 0;
                D_8010DE62_crazy_cogs = 1;
            }
            break;
    }
}

void func_80108190_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&D_8010B9F0_crazy_cogs[5])[arg0->work[1]];

    switch (cog->unk_12) {
        case 0:
            if (cog->unk_10 != 0) {
                cog->unk_44.x = arg0->trans.x + 650.0f;
                cog->unk_1C = -5.0f;
                cog->unk_20 = 180.0f;
            } else {
                cog->unk_44.x = arg0->trans.x - 650.0f;
                cog->unk_1C = 5.0f;
                cog->unk_20 = 0;
            }
            cog->unk_44.y = arg0->trans.y;
            cog->unk_12++;
            func_800E5690_minigame(arg0, 0x12);
            HmfModelData[arg0->model[0]].motTime = 0;
            HmfModelData[arg0->model[0]].motSpeed = 0;
            func_80105B04_crazy_cogs(arg0->work[1]);
            func_800DDD94_minigame(arg0);
            HuAudFXStop((s16)(arg0->work[3] * 2 + 2));
            func_8004AC98_main(0x325, ((s16 *)arg0->work)[1]);
            PlayerFXPlay(0x286, ((s16 *)arg0->work)[1]);
            D_8010DE08_crazy_cogs[arg0->work[1]] = 0;
        case 1:
            cog->unk_20 = func_801059BC_crazy_cogs(cog->unk_20, cog->unk_1C);
            arg0->trans.x = cosdf(cog->unk_20) * 650.0f + cog->unk_44.x;
            arg0->trans.y = sindf(cog->unk_20) * 590.0f + cog->unk_44.y;
            arg0->rot.y = func_801059BC_crazy_cogs(arg0->rot.y, 33.0f);
            arg0->rot.x = func_801059BC_crazy_cogs(arg0->rot.x, 33.0f);
            D_8010DE08_crazy_cogs[arg0->work[1]]++;
            if (arg0->trans.y < 0.0f) {
                cog->unk_12++;
            }
            break;
        case 2:
            return;
    }
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelRotSet(arg0->model[0], arg0->rot.x, arg0->rot.y, arg0->rot.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, func_80105BD0_crazy_cogs(arg0), arg0->trans.z);
}

void func_80108464_crazy_cogs(omObjData *arg0) {
    CrazyCogsCpuMovement *movement = &D_8010DE70_crazy_cogs[arg0->work[1]];
    UnkCrazyCogsCog *cog = &(&D_8010B9F0_crazy_cogs[5])[arg0->work[1]];
    UnkCrazyCogsCog *obstacle;
    omObjData *obj;
    s16 i;

    movement->xTimer++;
    if ((s8)movement->xTimer >= movement->xDuration) {
        movement->xTimer = 0;
        movement->xDuration = func_80105B7C_crazy_cogs(30) + 10;
        movement->xStick = func_80105B7C_crazy_cogs(20) + 30;
        movement->xStick = func_80105B7C_crazy_cogs(2) == 1 ? movement->xStick : -movement->xStick;
        cog->unk_0C = 0;
    }
    movement->zTimer++;
    if ((s8)movement->zTimer >= movement->zDuration) {
        movement->zTimer = 0;
        movement->zDuration = func_80105B7C_crazy_cogs(30) + 10;
        movement->zStick = func_80105B7C_crazy_cogs(20) + 30;
        movement->zStick = func_80105B7C_crazy_cogs(2) == 1 ? movement->zStick : -movement->zStick;
        cog->unk_0C = 0;
    }
    if (cog->unk_0C == 0 && cog->unk_14 != 0) {
        for (i = 0; i < 7; i++) {
            obstacle = &(&D_8010B9F0_crazy_cogs[8])[i];
            if ((s16)obstacle->timer != 0) {
                obj = obstacle->obj;
                if (arg0->trans.x < cog->unk_14 + obj->trans.x &&
                    arg0->trans.x > obj->trans.x - cog->unk_14 &&
                    arg0->trans.z < cog->unk_14 + obj->trans.z &&
                    arg0->trans.z > obj->trans.z - cog->unk_14) {
                    if (arg0->trans.x >= 0.0f && arg0->trans.z < 0.0f) {
                        movement->xStick = -40;
                        movement->zStick = -40;
                    } else if (arg0->trans.x >= 0.0f && arg0->trans.z >= 0.0f) {
                        movement->xStick = -40;
                        movement->zStick = 40;
                    } else if (arg0->trans.x < 0.0f && arg0->trans.z >= 0.0f) {
                        movement->xStick = 40;
                        movement->zStick = 40;
                    } else if (arg0->trans.x < 0.0f && arg0->trans.z < 0.0f) {
                        movement->xStick = 40;
                        movement->zStick = -40;
                    }
                    movement->zTimer = 0;
                    movement->xTimer = 0;
                    movement->zDuration = 17;
                    movement->xDuration = 17;
                    cog->unk_0C = 1;
                }
            }
        }
    }
    D_800CBB6E_main[arg0->work[3]] = movement->xStick;
    D_800D20A1_main[arg0->work[3]] = movement->zStick;
}

void func_801087B8_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&D_8010B9F0_crazy_cogs[5])[arg0->work[1]];
    func_800E1BA8_minigame_ObjData *work = arg0->data;

    if (cog->unk_0E != 0) {
        func_80108190_crazy_cogs(arg0);
        return;
    }
    if (D_8010B9E3_crazy_cogs[arg0->work[0]] != 0) {
        if (!(GwPlayer[arg0->work[0]].stat & 1)) {
            omVibrate(((s16 *)arg0->work)[1], 10, 0, 10);
        }
        D_8010B9E3_crazy_cogs[arg0->work[0]] = 0;
    }
    if (D_8010B99C_crazy_cogs != 2) {
        func_80105B04_crazy_cogs(arg0->work[0]);
        if (D_8010B99C_crazy_cogs == 0) {
            func_80107E00_crazy_cogs(arg0);
        }
        if (D_8010B99C_crazy_cogs == 3) {
            work->unk3C = 0;
            work->unk40 = 0;
        }
        if (D_8010B9A0_crazy_cogs > 0) {
            func_800E5690_minigame(arg0, 0xD);
            func_80045ED0_main((D_8010B810_crazy_cogs[GwPlayer[arg0->work[0]].chr] << 16) | 0x30);
        }
    } else {
        if (GwPlayer[arg0->work[0]].stat & 1) {
            func_80108464_crazy_cogs(arg0);
        }
        switch (D_8010DE60_crazy_cogs) {
            case 0:
                break;
            case 1:
                func_80107CA8_crazy_cogs(&arg0->trans.x, &arg0->trans.z, -3.3f);
                if (((D_800CBB6E_main[arg0->work[3]] < 0) ? -D_800CBB6E_main[arg0->work[3]] : D_800CBB6E_main[arg0->work[3]]) < 20 &&
                    ((D_800D20A1_main[arg0->work[3]] < 0) ? -D_800D20A1_main[arg0->work[3]] : D_800D20A1_main[arg0->work[3]]) < 20) {
                    work->unk3C = func_801059BC_crazy_cogs(work->unk3C, -3.3f);
                }
                break;
            case 2:
                func_80107CA8_crazy_cogs(&arg0->trans.x, &arg0->trans.z, 3.3f);
                if (((D_800CBB6E_main[arg0->work[3]] < 0) ? -D_800CBB6E_main[arg0->work[3]] : D_800CBB6E_main[arg0->work[3]]) < 20 &&
                    ((D_800D20A1_main[arg0->work[3]] < 0) ? -D_800D20A1_main[arg0->work[3]] : D_800D20A1_main[arg0->work[3]]) < 20) {
                    work->unk3C = func_801059BC_crazy_cogs(work->unk3C, 3.3f);
                }
                break;
        }
    }
    func_800DDD94_minigame(arg0);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
}

void func_80108B0C_crazy_cogs(omObjData *arg0) {
    CrazyCogsCpuMovement *movement = &D_8010DE70_crazy_cogs[arg0->work[1]];
    UnkCrazyCogsCog *cog = &(&D_8010B9F0_crazy_cogs[5])[arg0->work[1]];
    u16 character = GwPlayer[arg0->work[0]].chr;
    s32 modelFile = D_800A178C_main[character][0];
    s32 motionFile = D_800A1790_main[character][0];
    func_800E1BA8_minigame_ObjData *work;

    func_800E18D8_minigame();
    func_800E1BA8_minigame(arg0, modelFile, motionFile, ((u16 *)arg0->work)[1], 0x299, 0x289);
    work = arg0->data;
    work->unkEC = 0;
    func_8001C2FC_main(arg0->model[1], 0x80000000, 0);
    func_8001C258_main(arg0->model[1], 0x60, 0x20);
    func_8001C448_main(arg0->model[1]);
    func_8001C514_main(arg0->model[1]);
    arg0->model[3] = func_8000B108_main(3, 0x2BD);
    arg0->model[4] = func_8000B108_main(4, 0x2BD);
    func_800E5A00_minigame(arg0, 0, func_80017BB8_main(character, 0), 1, 0);
    func_800E5A00_minigame(arg0, 1, func_80017BB8_main(character, 1), 1, 0);
    func_800E5A00_minigame(arg0, 2, func_80017BB8_main(character, 2), 1, 0);
    func_800E5A00_minigame(arg0, 0x12, func_80017BB8_main(character, 0xF), 2, 0);
    func_800E5978_minigame(arg0, 3, func_80017BB8_main(character, 0x1D), 1, 0);
    func_800E5978_minigame(arg0, 4, func_80017BB8_main(character, 0x1E), 1, 0);
    func_800E5A00_minigame(arg0, 0xD, func_80017BB8_main(character, 0x30), 1, 120);
    func_800E5690_minigame(arg0, 0);
    D_800EBE24_minigame = 1;
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[3], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[4], HU3D_CAM0);
    func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    arg0->trans.x = 700.0f;
    arg0->trans.y = 28.0f;
    arg0->trans.z = 700.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    movement->xTimer = movement->xDuration = movement->xStick = 0;
    movement->zTimer = movement->zDuration = movement->zStick = 0;
    switch (GwPlayer[arg0->work[0]].cpu_difficulty) {
        case 0:
            cog->unk_14 = 0;
            break;
        case 1:
            cog->unk_14 = 33;
            break;
        case 2:
            cog->unk_14 = 66;
            break;
        case 3:
            cog->unk_14 = 100;
            break;
    }
    arg0->work[3] = GwPlayer[arg0->work[0]].pad;
    arg0->work[2] = 0;
    arg0->func = func_801087B8_crazy_cogs;
}

void func_80108EE8_crazy_cogs(void) {
    omObjData *obj;
    s16 count;
    u16 playerIndex;
    s32 cogIndex;
    s16 i;
    UnkCrazyCogsCog *cog;

    count = 0;
    playerIndex = 0;
    cogIndex = 0;
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            switch (i) {
                case 0:
                    playerIndex = 0;
                    break;
                case 1:
                    playerIndex = 1;
                    break;
                case 2:
                    playerIndex = 2;
                    break;
                case 3:
                    playerIndex = 3;
                    break;
            }
            cog = &(&D_8010B9F0_crazy_cogs[5])[cogIndex];
            obj = omAddObj(0x384, 9, 60, -1, func_80108B0C_crazy_cogs);
            obj->work[0] = playerIndex;
            cog->obj = obj;
            obj->work[1] = cogIndex;
            cogIndex++;
            D_800EC598_minigame[D_800EC280_minigame] = obj;
            D_800EC280_minigame++;
            D_8010B991_crazy_cogs[count] = GwPlayer[obj->work[0]].chr;
            D_8010DE10_crazy_cogs[count] = obj->work[0];
            count++;
        }
    }
}

void func_80109084_crazy_cogs(omObjData *arg0) {
}

void func_8010908C_crazy_cogs(omObjData *arg0) {
    arg0->model[0] = func_8000B0A0_main(0x260008, 0x89);
    func_8001C2FC_main(arg0->model[0], 0x80000000, 0);
    func_8001C448_main(arg0->model[0]);
    func_8001C514_main(arg0->model[0]);
    func_80088800_main(HmfModelData[arg0->model[0]].mtx, 0.0f, 0.0f, 0.0f);
    arg0->trans.x = arg0->trans.z = arg0->trans.y = 1000.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    arg0->scale.x = arg0->scale.y = arg0->scale.z = 2.0f;
    Hu3DModelScaleSet(arg0->model[0], arg0->scale.x, arg0->scale.y, arg0->scale.z);
    arg0->rot.x = 290.0f;
    arg0->rot.y = arg0->rot.z = 0.0f;
    Hu3DModelRotSet(arg0->model[0], arg0->rot.x, arg0->rot.y, arg0->rot.z);
    Hu3DMotionSpeedSet(arg0->model[0], 2.0f);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    arg0->func = func_80109084_crazy_cogs;
}

void func_801091F4_crazy_cogs(void) {
    s8 i;
    UnkCrazyCogsCog *cog;

    for (i = 0; i < 5; i++) {
        cog = &(&D_8010B9F0_crazy_cogs[18])[i];
        cog->obj = omAddObj(0x5DC, 1, 1, -1, func_8010908C_crazy_cogs);
        cog->obj->work[0] = i;
    }
}

void func_80109298_crazy_cogs(omObjData *arg0) {
    omObjData *obj = (&D_8010B9F0_crazy_cogs[18])[D_8010B996_crazy_cogs].obj;

    HuAudFXPlay(0x321);
    obj->trans.x = arg0->trans.x;
    obj->trans.y = func_80105BD0_crazy_cogs(arg0) + arg0->trans.y + 70.0f;
    obj->trans.z = arg0->trans.z + 70.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    D_8010B996_crazy_cogs = (D_8010B996_crazy_cogs + 1) % 5;
}

void func_80109388_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&D_8010B9F0_crazy_cogs[8])[arg0->work[0]];
    s32 offset;

    if (arg0->work[0] < 7) {
        if (arg0->trans.x > 0.0f) {
            if (arg0->trans.z > -50.0f) {
                D_8010DE6A_crazy_cogs[3] = 1;
            } else {
                D_8010DE6A_crazy_cogs[1] = 1;
            }
        } else {
            if (arg0->trans.z > -50.0f) {
                D_8010DE6A_crazy_cogs[2] = 1;
            } else {
                D_8010DE6A_crazy_cogs[0] = 1;
            }
        }
    }
    arg0->trans.x = cog->unk_44.x;
    arg0->trans.y = cog->unk_44.y;
    if (arg0->work[0] == 9) {
        cog->unk_18 = func_80105B7C_crazy_cogs(5);
        if (func_80105B7C_crazy_cogs(2) != 0) {
            cog->unk_18 = 0.0f - cog->unk_18;
        }
        arg0->trans.z = -1300.0f;
    } else {
        arg0->trans.x = cog->unk_44.x;
        arg0->trans.z = 0;
    }
    D_8010DE88_crazy_cogs[arg0->work[0]] = 0.1f;
    cog->timer = 0;
    func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (arg0->work[0] < 4) {
        offset = func_80105B7C_crazy_cogs(54);
        offset = offset * 10 + func_80105B7C_crazy_cogs(100);
        if (func_80105B7C_crazy_cogs(2) != 0) {
            arg0->trans.x = offset + arg0->trans.x;
        } else {
            arg0->trans.x -= offset;
        }
    } else if ((arg0->work[0] < 3) & (arg0->work[0] < 7)) {
        offset = func_80105B7C_crazy_cogs(20);
        offset = offset * 10 + func_80105B7C_crazy_cogs(100);
        if (func_80105B7C_crazy_cogs(2) != 0) {
            arg0->trans.x = offset + arg0->trans.x;
        } else {
            arg0->trans.x -= offset;
        }
        offset = func_80105B7C_crazy_cogs(20);
        offset = offset * 10 + func_80105B7C_crazy_cogs(100);
        if (func_80105B7C_crazy_cogs(2) != 0) {
            arg0->trans.z = offset + arg0->trans.z;
        } else {
            arg0->trans.z -= offset;
        }
    } else if ((arg0->work[0] == 7) & (arg0->work[0] == 8)) {
        offset = func_80105B7C_crazy_cogs(20);
        offset = offset * 10 + func_80105B7C_crazy_cogs(100);
        if (arg0->work[0] == 7) {
            arg0->trans.x -= offset;
        } else {
            arg0->trans.x = offset + arg0->trans.x;
        }
        offset = func_80105B7C_crazy_cogs(30) * 10;
        if (func_80105B7C_crazy_cogs(3) != 0) {
            arg0->trans.z = offset + (f32)func_80105B7C_crazy_cogs(200) + arg0->trans.z;
        } else {
            arg0->trans.z -= offset;
        }
    } else if (arg0->work[0] == 9) {
        offset = func_80105B7C_crazy_cogs(150);
        if (func_80105B7C_crazy_cogs(2) != 0) {
            arg0->trans.x -= offset;
        } else {
            arg0->trans.x = offset + arg0->trans.x;
        }
        offset = func_80105B7C_crazy_cogs(150);
        if (func_80105B7C_crazy_cogs(2) != 0) {
            arg0->trans.z = offset + arg0->trans.z;
        } else {
            arg0->trans.z -= offset;
        }
    }
}

void func_801097EC_crazy_cogs(omObjData *arg0) {
    s16 candidates[3];
    UnkCrazyCogsCog *cog;
    func_800E1BA8_minigame_ObjData *work;
    s16 count;
    s16 i;
    f32 x;
    f32 z;
    f32 distance;
    u32 obstacleIndex;

    if (D_8010B99C_crazy_cogs != 2) {
        return;
    }
    count = 0;
    for (i = 0; i < 3; i++) {
        cog = &(&D_8010B9F0_crazy_cogs[5])[i];
        work = cog->obj->data;
        if (cog->unk_0E == 0 && arg0->trans.y <= work->unk34) {
            x = arg0->trans.x - cog->obj->trans.x;
            z = arg0->trans.z - cog->obj->trans.z;
            distance = sqrtf(x * x + z * z);
            if (distance < work->unk48 + 40.0f) {
                candidates[count] = ((s16 *)cog->obj->work)[3];
                count++;
            }
        }
    }
    if (count != 0) {
        cog = &(&D_8010B9F0_crazy_cogs[5])[candidates[(s16)func_80105B7C_crazy_cogs(count)]];
        func_80109298_crazy_cogs(arg0);
        if (!(GwPlayer[cog->obj->work[0]].stat & 1)) {
            omVibrate(((s16 *)cog->obj->work)[1], 20, 0, 20);
        }
        func_80109388_crazy_cogs(arg0);
        cog->unk_0E = 1;
        D_8010B997_crazy_cogs++;
        obstacleIndex = arg0->work[0];
        if (obstacleIndex < 2) {
            cog->unk_10 = 1;
        } else if (obstacleIndex < 4) {
            cog->unk_10 = 0;
        } else {
            if (arg0->trans.x > cog->obj->trans.x) {
                cog->unk_10 = 0;
            } else {
                cog->unk_10 = 1;
            }
        }
    }
}

s8 func_80109A44_crazy_cogs(omObjData *arg0) {
    s8 result;

    switch (arg0->work[0]) {
        case 4:
        case 5:
        case 6:
            if (arg0->trans.x > -600.0f && arg0->trans.x < 600.0f && arg0->trans.z > -350.0f && arg0->trans.z < 600.0f) {
                result = 0;
            } else {
                result = 1;
                if (arg0->trans.x > -350.0f && arg0->trans.x < 600.0f && arg0->trans.z > -600.0f && arg0->trans.z < -350.0f) {
                    result = 0;
                }
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
            result = 1;
            if (arg0->trans.z > -350.0f) {
                if (arg0->trans.z < 500.0f) {
                    result = 0;
                }
            }
            break;
        default:
            result = 1;
            break;
    }
    return result;
}

void func_80109B88_crazy_cogs(omObjData *arg0, s32 arg1) {
    CrazyCogsMovement *movement;

    if (arg0->work[0] < 7) {
        movement = &D_8010DE28_crazy_cogs[arg0->work[0]];
        if (func_80109A44_crazy_cogs(arg0) != 0) {
            movement->xTimer = 0;
            movement->xDirection *= -1;
            movement->zTimer = 0;
            movement->zDirection *= -1;
        } else {
            movement->xTimer++;
            if ((s8)movement->xTimer >= movement->xDuration) {
                movement->xTimer = 0;
                movement->xDuration = func_80105B7C_crazy_cogs(20) + 5;
                movement->xSpeed = func_80105B7C_crazy_cogs(8);
                movement->xDirection = func_80105B7C_crazy_cogs(2) == 1 ? 1 : -1;
            }
            movement->zTimer++;
            if ((s8)movement->zTimer >= movement->zDuration) {
                movement->zTimer = 0;
                movement->zDuration = func_80105B7C_crazy_cogs(20) + 5;
                movement->zSpeed = func_80105B7C_crazy_cogs(8);
                movement->zDirection = func_80105B7C_crazy_cogs(2) == 1 ? 1 : -1;
            }
        }
        switch (arg0->work[0]) {
            case 4:
            case 5:
            case 6:
                arg0->trans.x = movement->xSpeed * movement->xDirection + arg0->trans.x;
            case 0:
            case 1:
            case 2:
            case 3:
                arg0->trans.z = movement->zSpeed * movement->zDirection + arg0->trans.z;
                break;
        }
    }
}

void func_80109D24_crazy_cogs(void) {
    D_8010B9E3_crazy_cogs[0] = 1;
    D_8010B9E3_crazy_cogs[1] = 1;
    D_8010B9E3_crazy_cogs[2] = 1;
    D_8010B9E3_crazy_cogs[3] = 1;
}

void func_80109D44_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&D_8010B9F0_crazy_cogs[8])[arg0->work[0]];

    func_801097EC_crazy_cogs(arg0);
    if ((s16)cog->timer == 0) {
        return;
    }
    switch (D_8010B99C_crazy_cogs) {
        case 0:
        case 1:
            break;
        case 2:
            if (arg0->trans.y > 25.0f) {
                arg0->trans.x -= cog->unk_18;
                arg0->trans.y -= cog->unk_1C;
                D_8010DE88_crazy_cogs[arg0->work[0]] += cog->unk_20;
            } else {
                func_80109298_crazy_cogs(arg0);
                func_80109388_crazy_cogs(arg0);
                func_80109D24_crazy_cogs();
            }
            if (arg0->work[0] == 9) {
                if (arg0->trans.z < 600.0f) {
                    arg0->trans.z += 35.0f;
                } else {
                    func_80109388_crazy_cogs(arg0);
                    func_80109D24_crazy_cogs();
                }
            }
            func_80109B88_crazy_cogs(arg0, 0);
            break;
        default:
            if ((s16)cog->timer != 0) {
                func_80109298_crazy_cogs(arg0);
                func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                func_8001C258_main(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                cog->timer = 0;
            }
            break;
    }
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, func_80105BD0_crazy_cogs(arg0), arg0->trans.z);
    if (D_8010DE88_crazy_cogs[arg0->work[0]] > 1.0f) {
        D_8010DE88_crazy_cogs[arg0->work[0]] = 1.0f;
    }
    Hu3DModelScaleSet(arg0->model[1], D_8010DE88_crazy_cogs[arg0->work[0]], 1.0f,
                      D_8010DE88_crazy_cogs[arg0->work[0]]);
}

void func_80109F64_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&D_8010B9F0_crazy_cogs[8])[arg0->work[0]];
    f32 xSpeed;
    f32 angle;
    u32 cogIndex;

    if (arg0->work[0] == 0) {
        arg0->model[0] = func_8000B0A0_main(0xA0062, 0x89);
        func_8001C448_main(arg0->model[0]);
        func_8001C514_main(arg0->model[0]);
        arg0->model[1] = func_8000B0A0_main(0, 0x14C9);
        func_8001C2FC_main(arg0->model[1], 0x80000000, 0);
        func_8001C448_main(arg0->model[1]);
        func_8001C514_main(arg0->model[1]);
        func_80088800_main(HmfModelData[arg0->model[1]].mtx, 0.0f, 0.0f, 0.0f);
        D_8010DE18_crazy_cogs[0] = arg0->model[0];
        D_8010DE18_crazy_cogs[1] = arg0->model[1];
    } else {
        arg0->model[0] = Hu3DModelLink((s16)D_8010DE18_crazy_cogs[0]);
        arg0->model[1] = Hu3DModelLink((s16)D_8010DE18_crazy_cogs[1]);
    }
    if (arg0->work[0] < 4) {
        angle = 60.0f;
        xSpeed = cosdf(0.0f) * cosdf(angle) * 36.0f;
        cog->unk_1C = sindf(angle) * 36.0f;
        cogIndex = arg0->work[0];
        if (cogIndex < 2) {
            cog->unk_18 = 0.0f - xSpeed;
            cog->unk_44.x = 0.0f - cosdf(0.0f) * cosdf(angle) * 2900.0f;
            cog->unk_50.y = 90.0f;
            cog->unk_50.z = 300.0f;
        } else if (cogIndex < 4) {
            cog->unk_18 = xSpeed;
            cog->unk_44.x = cosdf(0.0f) * cosdf(angle) * 2900.0f;
            cog->unk_50.y = 270.0f;
            cog->unk_50.z = angle;
        }
        cog->unk_44.y = sindf(angle) * 2900.0f;
    } else if (arg0->work[0] < 7) {
        cog->unk_18 = 0;
        cog->unk_1C = 36.0f;
        cog->unk_44.x = 0;
        cog->unk_44.y = 2900.0f;
        cog->unk_50.x = 90.0f;
    }
    if (arg0->work[0] == 7) {
        cog->unk_18 = 45.0f;
        cog->unk_1C = 45.0f;
        cog->unk_44.x = 1400.0f;
        cog->unk_44.y = 2000.0f;
        cog->unk_44.z = 0;
        cog->unk_50.y = 270.0f;
        cog->unk_50.z = 45.0f;
    }
    if (arg0->work[0] == 8) {
        cog->unk_18 = -45.0f;
        cog->unk_1C = 45.0f;
        cog->unk_44.x = -1400.0f;
        cog->unk_44.y = 2000.0f;
        cog->unk_44.z = 0;
        cog->unk_50.y = 90.0f;
        cog->unk_50.z = 315.0f;
    }
    if (arg0->work[0] == 9) {
        cog->unk_18 = 5.0f;
        cog->unk_1C = 30.0f;
        cog->unk_44.x = 0;
        cog->unk_44.y = 1800.0f;
        cog->unk_44.z = 0;
        cog->unk_50.y = 0;
        cog->unk_50.x = 30.0f;
    }
    arg0->trans.x = cog->unk_44.x;
    arg0->trans.y = cog->unk_44.y;
    arg0->trans.z = cog->unk_44.z;
    arg0->rot.x = cog->unk_50.x;
    arg0->rot.y = cog->unk_50.y;
    arg0->rot.z = cog->unk_50.z;
    arg0->scale.x = arg0->scale.y = arg0->scale.z = 1.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelRotSet(arg0->model[0], arg0->rot.x, arg0->rot.y, arg0->rot.z);
    Hu3DModelScaleSet(arg0->model[0], arg0->scale.x, arg0->scale.y, arg0->scale.z);
    cog->unk_20 = 0.9f / 80.0f;
    Hu3DModelScaleSet(arg0->model[1], 0.1f, 1.0f, 0.1f);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    func_80109388_crazy_cogs(arg0);
    arg0->func = func_80109D44_crazy_cogs;
}

void func_8010A4A4_crazy_cogs(void) {
    s16 i;
    UnkCrazyCogsCog *cog;
    omObjData *obj;

    for (i = 0; i < 10; i++) {
        cog = &(&D_8010B9F0_crazy_cogs[8])[i];
        obj = omAddObj(0x578, 20, 0, -1, func_80109F64_crazy_cogs);
        obj->work[0] = i;
        cog->obj = obj;
    }
}

void func_8010A548_crazy_cogs(UnkCrazyCogsCog *cog) {
    if (cog->obj->work[0] < 4) {
        return;
    }
    D_8010DE22_crazy_cogs++;
    switch (D_8010B9A1_crazy_cogs) {
        case 0:
            return;
        case 1:
            if ((s16)(D_8010DE22_crazy_cogs % 3) != 1) {
                return;
            }
            break;
        case 2:
            if ((s16)(D_8010DE22_crazy_cogs % 3) == 1) {
                return;
            }
            break;
    }
    D_8010B9B0_crazy_cogs[D_8010B9E2_crazy_cogs] = ((s8 *)cog->obj->work)[3];
    D_8010B9E2_crazy_cogs++;
}

void func_8010A67C_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *cog;
    s16 cogIndex;
    s16 i;

    if (D_8010B99C_crazy_cogs != 2) {
        return;
    }
    if (D_8010B99E_crazy_cogs >= D_8010B994_crazy_cogs) {
        D_8010B99E_crazy_cogs = 0;
        D_8010B994_crazy_cogs = func_80105B7C_crazy_cogs(2) == 0 ? 30 : func_80105B7C_crazy_cogs(10) + 30;
        cogIndex = func_80105B7C_crazy_cogs(7);
        cog = &(&D_8010B9F0_crazy_cogs[8])[cogIndex];
        if ((s16)cog->timer == 0) {
            cog->timer = 1;
            func_8010A548_crazy_cogs(cog);
            func_8001C258_main(cog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            func_8001C258_main(cog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        } else {
            cogIndex++;
            for (i = 0; i < 6; cogIndex = (cogIndex + 1) % 7, i++) {
                if (cogIndex == 7) {
                    cogIndex--;
                    i--;
                } else {
                    cog = &(&D_8010B9F0_crazy_cogs[8])[cogIndex];
                    if ((s16)cog->timer == 0) {
                        cog->timer = 1;
                        func_8010A548_crazy_cogs(cog);
                        func_8001C258_main(cog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        func_8001C258_main(cog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        break;
                    }
                }
            }
        }
    }
    if ((s16)(D_8010B99E_crazy_cogs % 27) == 0 && func_80105B7C_crazy_cogs(5) == 0) {
        cog = &D_8010B9F0_crazy_cogs[15];
        if ((s16)cog->timer == 0) {
            cog->timer = 1;
            func_8001C258_main(cog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            func_8001C258_main(cog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
    }
    if ((D_8010B99E_crazy_cogs + 15) % 27 == 0 && func_80105B7C_crazy_cogs(5) == 0) {
        cog = &D_8010B9F0_crazy_cogs[16];
        if ((s16)cog->timer == 0) {
            cog->timer = 1;
            func_8001C258_main(cog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            func_8001C258_main(cog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
    }
    if ((s16)(D_8010B99E_crazy_cogs % 15) == 0 && func_80105B7C_crazy_cogs(5) == 0) {
        cog = &D_8010B9F0_crazy_cogs[17];
        if ((s16)cog->timer == 0) {
            cog->timer = 1;
            func_8001C258_main(cog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            func_8001C258_main(cog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
    }
    D_8010B99E_crazy_cogs++;
}

void func_8010AA10_crazy_cogs(omObjData *arg0) {
    s16 i;

    D_8010B99E_crazy_cogs = 0;
    D_8010B994_crazy_cogs = 5;

    for (i = 0; i < 0x32; i++) {
        D_8010B9B0_crazy_cogs[i] = -1;
    }

    D_8010B9B0_crazy_cogs[i] = -1;
    D_8010B9E2_crazy_cogs = 0;
    D_8010B990_crazy_cogs = 0;
    D_8010DE22_crazy_cogs = 0;

    arg0->model[0] = -1;
    arg0->func = func_8010A67C_crazy_cogs;
}

void func_8010AAA4_crazy_cogs(void) {
    D_8010C5CC_crazy_cogs = omAddObj(0x514, 1, 1, -1, func_8010AA10_crazy_cogs);
}

void func_8010AAE0_crazy_cogs(omObjData *arg0) {
}

void func_8010AAE8_crazy_cogs(omObjData *arg0) {
}

void func_8010AAF0_crazy_cogs(omObjData *arg0) {
    if (D_8010DEB0_crazy_cogs->obj->trans.y >= 1500.0f) {
        D_8010DEB0_crazy_cogs->obj->trans.x = 0.0f;
        D_8010DEB0_crazy_cogs->obj->trans.y = 2400.0f;
        D_8010DEB0_crazy_cogs->obj->trans.z = 560.0f;
        D_8010DEB0_crazy_cogs->obj->rot.x = D_8010DEB0_crazy_cogs->unk_50.x;
        D_8010DEB0_crazy_cogs->obj->rot.y = D_8010DEB0_crazy_cogs->unk_50.y;
        D_8010DEB0_crazy_cogs->obj->rot.z = D_8010DEB0_crazy_cogs->unk_50.z;
        D_8010DE88_crazy_cogs[D_8010DEB0_crazy_cogs->obj->work[0]] = 0.2f;
        arg0->func = func_8010AAE8_crazy_cogs;
    } else {
        D_8010DEB0_crazy_cogs->obj->trans.y += 42.0f;
        D_8010DEB0_crazy_cogs->obj->trans.z += 14.0f;
    }
}

void func_8010ABE0_crazy_cogs(omObjData *arg0) {
    omObjData *obj = D_8010DEB0_crazy_cogs->obj;

    D_8010B9A4_crazy_cogs++;
    if ((s16)D_8010B9A4_crazy_cogs == 15) {
        HuAudFXPlay(0x326);
    }
    if (D_8010B9A4_crazy_cogs >= 25 && D_8010B9A4_crazy_cogs < 100) {
        obj->trans.x -= 30.0f;
        obj->trans.y -= 8.0f;
        obj->trans.z += 30.0f;
        if (obj->trans.z >= 900.0f) {
            obj->trans.x = 0.0f;
            obj->trans.y = D_8010DEB0_crazy_cogs->unk_44.y;
            obj->trans.z = 0.0f;
            obj->rot.x = 90.0f;
            obj->rot.y = 0.0f;
            obj->rot.z = 0.0f;
            D_8010B9A4_crazy_cogs = 100;
        }
    }
    if ((s16)D_8010B9A4_crazy_cogs >= 100) {
        if (obj->trans.y > 25.0f) {
            obj->trans.x -= D_8010DEB0_crazy_cogs->unk_18;
            obj->trans.y -= D_8010DEB0_crazy_cogs->unk_1C + 10.0f;
            D_8010DE88_crazy_cogs[obj->work[0]] += D_8010DEB0_crazy_cogs->unk_20;
        } else {
            func_80109298_crazy_cogs(obj);
            func_80109388_crazy_cogs(obj);
            func_80109D24_crazy_cogs();
            D_8010DE6A_crazy_cogs[0] = D_8010DE6A_crazy_cogs[1] = D_8010DE6A_crazy_cogs[2] = D_8010DE6A_crazy_cogs[3] = 1;
            arg0->func = func_8010AAE0_crazy_cogs;
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, func_80105BD0_crazy_cogs(obj), obj->trans.z);
        Hu3DModelScaleSet(obj->model[1], D_8010DE88_crazy_cogs[obj->work[0]], 1.0f, D_8010DE88_crazy_cogs[obj->work[0]]);
    }
}

void func_8010AE08_crazy_cogs(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &D_8010B9F0_crazy_cogs[12];

    D_8010DEB0_crazy_cogs = cog;
    D_8010B9A4_crazy_cogs = 0;
    D_8010B998_crazy_cogs = 820.0f;
    cog->obj->trans.x = 400.0f;
    cog->obj->trans.y = 900.0f;
    cog->obj->trans.z = 300.0f;
    cog->obj->rot.x = 15.0f;
    cog->obj->rot.y = 315.0f;
    cog->obj->rot.z = 0.0f;
    Hu3DModelPosSet(cog->obj->model[0], cog->obj->trans.x,
                    cog->obj->trans.y, cog->obj->trans.z);
    Hu3DModelRotSet(D_8010DEB0_crazy_cogs->obj->model[0], D_8010DEB0_crazy_cogs->obj->rot.x,
                    D_8010DEB0_crazy_cogs->obj->rot.y, D_8010DEB0_crazy_cogs->obj->rot.z);
    func_8001C258_main(D_8010DEB0_crazy_cogs->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(D_8010DEB0_crazy_cogs->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    arg0->model[0] = -1;
    arg0->func = func_8010ABE0_crazy_cogs;
}

void func_8010AF58_crazy_cogs(void) {
    D_8010C650_crazy_cogs = omAddObj(0x640, 1, 1, -1, func_8010AE08_crazy_cogs);
}

void func_8010AF94_crazy_cogs(void) {
    u32 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 1648.63f;
        CRotM[i].x = 314.034f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = -20.0f;
        CenterM[i].z = -50.0f;
    }
}

void func_8010B040_crazy_cogs(omObjData *arg0) {
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void func_8010B064_crazy_cogs(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        arg0->func = func_8010B040_crazy_cogs;
    }
}

void func_8010B09C_crazy_cogs(omObjData *arg0) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        arg0->func = func_8010B064_crazy_cogs;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_8010B0F4_crazy_cogs(omObjData *arg0) {
    switch (D_8010B99C_crazy_cogs) {
        case 0:
            if (D_8010DE62_crazy_cogs == 1) {
                GMesCreate(4);
                D_8010B99C_crazy_cogs = 1;
                D_8010DE20_crazy_cogs = 0;
            }
            break;
        case 1:
            if (GMesStatGet() == 0) {
                D_8010B99C_crazy_cogs = 2;
                GMesCreate(0x1A, 30, 160, 28);
                D_8010DE66_crazy_cogs = 901;
            }
            D_8010DE20_crazy_cogs++;
            if (D_8010DE20_crazy_cogs == 57) {
                HuAudSeqPlay(0x2F);
            }
            break;
        case 2:
            if (D_8010DE66_crazy_cogs <= 0) {
                D_8010B99C_crazy_cogs = 3;
                func_8003F5C0_main();
                D_8010DE66_crazy_cogs = 0;
            } else {
                D_8010DE66_crazy_cogs--;
                func_8003F578_main((D_8010DE66_crazy_cogs + 29) / 30);
                if (D_8010B997_crazy_cogs == 3) {
                    func_8003F5C0_main();
                    D_8010B99C_crazy_cogs = 3;
                } else {
                    break;
                }
            }
            D_8010DE60_crazy_cogs = 0;
            GMesCreate(0xF);
            HuAudSeqFadeOut(120);
            break;
        case 3:
            if (GMesStatGet() == 0) {
                D_8010DE66_crazy_cogs = 0;
                if (D_8010B997_crazy_cogs == 3) {
                    D_8010B99C_crazy_cogs = 4;
                } else {
                    D_8010B99C_crazy_cogs = 5;
                }
            }
            break;
        case 4:
            D_8010DE66_crazy_cogs++;
            if (D_8010DE66_crazy_cogs >= 15) {
                D_8010B9A0_crazy_cogs = -1;
                HuAudSeqPlay(0x65);
                GMesCreate(0x16, (s8)D_8010DE69_crazy_cogs);
                GwPlayer[(s8)D_8010DE64_crazy_cogs].bonusCoin = 10;
                D_8010DE66_crazy_cogs = 15;
                D_8010B99C_crazy_cogs = 6;
            }
            break;
        case 5:
            D_8010DE66_crazy_cogs++;
            if (D_8010DE66_crazy_cogs >= 15) {
                D_8010B9A0_crazy_cogs = 1;
                HuAudSeqPlay(0x66);
                GMesCreate(0x22, D_8010B991_crazy_cogs[0], D_8010B991_crazy_cogs[1], D_8010B991_crazy_cogs[2]);
                GwPlayer[D_8010DE10_crazy_cogs[0]].bonusCoin = 10;
                GwPlayer[D_8010DE10_crazy_cogs[1]].bonusCoin = 10;
                GwPlayer[D_8010DE10_crazy_cogs[2]].bonusCoin = 10;
                D_8010DE66_crazy_cogs = 15;
                D_8010B99C_crazy_cogs = 6;
            }
            break;
        case 6:
            D_8010B9A0_crazy_cogs = 0;
            if (GMesStatGet() == 0) {
                D_8010DE66_crazy_cogs--;
                if (D_8010DE66_crazy_cogs <= 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                    arg0->func = func_8010B064_crazy_cogs;
                }
            }
            break;
    }
}

void func_8010B46C_crazy_cogs(omObjData *arg0) {
    func_800E6F0C_minigame(2);
    D_8010B99C_crazy_cogs = 0;
    D_8010B997_crazy_cogs = 0;
    D_8010DE66_crazy_cogs = 0;
    D_8010DE62_crazy_cogs = 0;
    D_8010DE0E_crazy_cogs = 0;
    D_8010B9A0_crazy_cogs = 0;
    D_8010DE60_crazy_cogs = 0;
    D_8010B9E3_crazy_cogs[0] = D_8010B9E3_crazy_cogs[1] = D_8010B9E3_crazy_cogs[2] = D_8010B9E3_crazy_cogs[3] = 0;
    D_8010B996_crazy_cogs = 0;
    func_8010AF94_crazy_cogs();
    func_801063DC_crazy_cogs();
    func_80106770_crazy_cogs();
    func_80106910_crazy_cogs();
    func_80106AB0_crazy_cogs();
    func_80107778_crazy_cogs();
    func_80107AB8_crazy_cogs();
    func_80108EE8_crazy_cogs();
    func_8010AAA4_crazy_cogs();
    func_8010A4A4_crazy_cogs();
    func_801091F4_crazy_cogs();
    func_8010AF58_crazy_cogs();
    func_8010654C_crazy_cogs();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    arg0->func = func_8010B0F4_crazy_cogs;
}

void func_8010B568_crazy_cogs(void) {
}

void func_8010B570_crazy_cogs(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8010B898_crazy_cogs[i].scissorX, D_8010B898_crazy_cogs[i].scissorY,
                   D_8010B898_crazy_cogs[i].scissorWidth, D_8010B898_crazy_cogs[i].scissorHeight);
        ViewportSet(i, D_8010B898_crazy_cogs[i].viewportScale.x, D_8010B898_crazy_cogs[i].viewportScale.y,
                    D_8010B898_crazy_cogs[i].viewportScale.z, D_8010B898_crazy_cogs[i].viewportTranslate.x,
                    D_8010B898_crazy_cogs[i].viewportTranslate.y, D_8010B898_crazy_cogs[i].viewportTranslate.z);
        Hu3DCamSetPerspective(i, D_8010B898_crazy_cogs[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010B6E0_crazy_cogs(void) {
    Hu3DAnimInit(50);
    func_800142A0_main(32);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_8010B570_crazy_cogs();
    HmfLightMaxSet(1);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(0, 0.0f, 90.0f, 560.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010B97C_crazy_cogs, 0);
    func_80045010_main(D_8010B97C_crazy_cogs, 1);
    omAddObj(0x7D0, 0, 0, -1, func_8010B46C_crazy_cogs);
    omAddObj(0x7D0, 0, 0, -1, func_8010B09C_crazy_cogs);
    func_80105A3C_crazy_cogs();
    func_800E5EA0_minigame(&D_8010B830_crazy_cogs);
}

// Keep this table after the functions to preserve the original rodata order.
const s16 D_8010B97C_crazy_cogs[] = { 0x8260, 0x8261, 0x8262, 0 };
