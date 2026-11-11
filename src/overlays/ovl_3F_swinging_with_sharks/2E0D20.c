#include "common.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfdraw.h"
#include "game/pause.h"
#include "game/wipe.h"

typedef struct {
    /* 0x00 */ s16 modelId;
    /* 0x02 */ s16 animId;
    /* 0x04 */ s32 flags;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
} SharkEntry; // Size 0x24

typedef struct {
    /* 0x00 */ s16 model;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[0xE];
    /* 0x14 */ Vec pos;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[0xA];
} SharkState; // Size 0x30

extern u16 D_800A11D0_main[];

extern u8 D_8010ACE1_swinging_with_sharks;
extern f32 D_8010ACE4_swinging_with_sharks;
extern f32 D_8010ACE8_swinging_with_sharks;
extern SharkEntry D_8010ACEC_swinging_with_sharks[];
extern u16 D_8010B418_swinging_with_sharks[];
extern u8 D_8010B420_swinging_with_sharks[];
extern s16 D_8010B428_swinging_with_sharks;
extern s16 D_8010B42A_swinging_with_sharks;
extern s16 D_8010B42C_swinging_with_sharks;
extern const char D_8010B7C0_swinging_with_sharks[]; // "rope"
extern const char D_8010B7C8_swinging_with_sharks[]; // "step"
extern HuMtx4F D_8010B860_swinging_with_sharks;
extern HuMtx4F D_8010B8A0_swinging_with_sharks;
extern s16 D_8010B8E0_swinging_with_sharks[50]; // model ids, indexed like D_8010ACEC
extern s16 D_8010B948_swinging_with_sharks[50]; // motion ids, indexed like D_8010ACEC
extern Vec D_8010B9AC_swinging_with_sharks;
extern Vec D_8010B9B8_swinging_with_sharks;
extern Vec D_8010B9C4_swinging_with_sharks;
extern f32 D_8010B9D0_swinging_with_sharks;
extern f32 D_8010B9D4_swinging_with_sharks;
extern s16 D_8010B9D8_swinging_with_sharks;
extern s16 D_8010B9DA_swinging_with_sharks;
extern s16 D_8010B9DC_swinging_with_sharks;
extern s16 D_8010B9DE_swinging_with_sharks;
extern s16 D_8010B9E0_swinging_with_sharks;
extern s16 D_8010B9E2_swinging_with_sharks;
extern s16 D_8010B9E4_swinging_with_sharks;
extern s16 D_8010B9E6_swinging_with_sharks;
extern s16 D_8010B9E8_swinging_with_sharks;
extern s16 D_8010B9EA_swinging_with_sharks;
extern s16 D_8010B9EC_swinging_with_sharks;
extern s16 D_8010B9EE_swinging_with_sharks;
extern SharkState D_8010B9F0_swinging_with_sharks[5];
extern s16 D_8010BAE0_swinging_with_sharks;
extern s16 D_8010BAE2_swinging_with_sharks;
extern s16 D_8010BAE6_swinging_with_sharks;
extern s16 D_8010BB48_swinging_with_sharks;
extern Vec D_8010BB78_swinging_with_sharks;
extern Vec D_8010BB90_swinging_with_sharks;
extern f32 D_8010BB9C_swinging_with_sharks;
extern Vec D_8010BBA8_swinging_with_sharks;
extern f32 D_8010BBB4_swinging_with_sharks;

const s16 D_8010B770_swinging_with_sharks[] = {
    0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000
};

void func_80105FE4_swinging_with_sharks(omObjData *object);
void func_80106334_swinging_with_sharks(void);
void func_80106398_swinging_with_sharks(omObjData *object);
void func_80106870_swinging_with_sharks(omObjData *object);
void func_80106D44_swinging_with_sharks(omObjData *object);
void func_80107044_swinging_with_sharks(omObjData *object);
void func_801071A8_swinging_with_sharks(omObjData *object);
void func_801073F0_swinging_with_sharks(omObjData *object);
void func_80107384_swinging_with_sharks(void);
void func_80107628_swinging_with_sharks(omObjData *object);
void func_801076DC_swinging_with_sharks(omObjData *object);
void func_801077C4_swinging_with_sharks(void);
void func_80107954_swinging_with_sharks(omObjData *object);
void func_801089A4_swinging_with_sharks(omObjData *object);
void func_80108B24_swinging_with_sharks(void);
void func_801088F0_swinging_with_sharks(f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ, f32 zoom,
                                        s16 time);
void func_80108B4C_swinging_with_sharks(omObjData *object);
void func_80108C08_swinging_with_sharks(f32 arg0);
void func_80108DB0_swinging_with_sharks(Vec *pos);
void func_8010979C_swinging_with_sharks(SharkEntry *entries);
void func_801098C0_swinging_with_sharks(omObjData *object);
void func_80109950_swinging_with_sharks(void);
void func_8010A0C0_swinging_with_sharks(void);
void func_8010A260_swinging_with_sharks(void);
void func_8010A41C_swinging_with_sharks(void);
void func_8010A4DC_swinging_with_sharks(void);
void func_8010AA68_swinging_with_sharks(void);
void func_8010AAA0_swinging_with_sharks(void);

void func_801059A0_swinging_with_sharks(void) {
    s32 index;
    s32 i;

    omInitObjMan(20, 10);
    func_8004A208_main();
    func_800142A0_main(20);
    Hu3DBGColorSet(0, 0xFF, 0);
    D_800CD280_main = 1;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CRot.x = 334.0f;
    CRot.y = D_8010BBA8_swinging_with_sharks.z = 0.0f;
    CZoom = 2750.0f;
    Center.x = -698.0f;
    Center.y = 363.0f;
    Center.z = -112.9f;
    D_8010BBB4_swinging_with_sharks = 20.0f;
    D_8010BBA8_swinging_with_sharks = CRot;
    D_8010BB90_swinging_with_sharks = D_8010BBA8_swinging_with_sharks;
    D_8010BB9C_swinging_with_sharks = CZoom;
    D_8010BB78_swinging_with_sharks = Center;
    Hu3DCameraPerspectiveSet(0, D_8010BBB4_swinging_with_sharks, 500.0f, 8000.0f);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(0, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(0, 92.0f, 79.0f, 22.0f);
    Hu3DGLightStatSet(0, 1, 1);
    Hu3DGLightColorSet(2, 100, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(10000, 0, 0, -1, func_801098C0_swinging_with_sharks);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8010B9E0_swinging_with_sharks = 0;
    D_8010B9E2_swinging_with_sharks = 0;
    omAddObj(1000, 0, 0, -1, func_80105FE4_swinging_with_sharks);
    omAddObj(1000, 0, 0, -1, func_80106398_swinging_with_sharks);
    omAddObj(900, 0, 0, -1, func_801073F0_swinging_with_sharks);
    omAddObj(900, 0, 0, -1, func_80107954_swinging_with_sharks);
    omSetStatBit(omAddObj(900, 0, 0, -1, func_80108B4C_swinging_with_sharks), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omAddObj(900, 0, 0, -1, func_801089A4_swinging_with_sharks);
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    D_8010B9D8_swinging_with_sharks = i;
    D_8010B9E8_swinging_with_sharks = GwPlayer[D_8010B9D8_swinging_with_sharks].stat & 1;
    GwPlayer[D_8010B9D8_swinging_with_sharks].bonusCoin = -1;
    D_8010B9DC_swinging_with_sharks = GwPlayer[i].chr;
    D_8010B9DA_swinging_with_sharks = GwPlayer[i].pad;
    func_8010979C_swinging_with_sharks(D_8010ACEC_swinging_with_sharks);
    if (D_8010B9E8_swinging_with_sharks != 0) {
        D_8010B9E8_swinging_with_sharks = GwPlayer[D_8010B9D8_swinging_with_sharks].cpu_difficulty + 1;
        D_8010B9EA_swinging_with_sharks =
            rand8() > D_8010B418_swinging_with_sharks[GwPlayer[D_8010B9D8_swinging_with_sharks].cpu_difficulty];
        D_8010B9EC_swinging_with_sharks = (u8)(rand8() & 0x1F) + 15;
        if (D_8010B9EA_swinging_with_sharks != 0) {
            index = (rand8() * 5) >> 8;
            D_8010B9EE_swinging_with_sharks =
                (Hu3DData[D_8010B8E0_swinging_with_sharks[index + 3]].pos.x + 70.0f) / 1000.0f * 70.0f + 10.0f;
        }
    }
    func_80107384_swinging_with_sharks();
    func_801077C4_swinging_with_sharks();
    func_80108B24_swinging_with_sharks();
    func_8010AA68_swinging_with_sharks();
    func_80106334_swinging_with_sharks();
    D_8010ACE4_swinging_with_sharks = 0;
    D_8010B9D0_swinging_with_sharks = 80.0f;
    D_8010B9DE_swinging_with_sharks = -1;
    func_80108C08_swinging_with_sharks(0.0f);
    func_80108DB0_swinging_with_sharks(&D_8010B9B8_swinging_with_sharks);
    D_8010B9E4_swinging_with_sharks = 0;
    func_8001FA68_main(D_8010B8E0_swinging_with_sharks[31]);
    func_8001C514_main(D_8010B8E0_swinging_with_sharks[31]);
    func_80045010_main(D_8010B770_swinging_with_sharks, 1);
    func_8010A41C_swinging_with_sharks();
    omAddPrcObj(func_80109950_swinging_with_sharks, 0x3F00, 0x2000, 0);
    omAddPrcObj(func_80109950_swinging_with_sharks, 0x3F00, 0x2000, 0);
    HuAudSeqPlay(0x44);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105FE4_swinging_with_sharks(omObjData *object) {
    switch (D_8010B9E0_swinging_with_sharks) {
        case 0:
            if (WipeStatGet() != 0) {
                break;
            }
            if (D_8010B9E4_swinging_with_sharks == 0) {
                D_8010B9E6_swinging_with_sharks = HuAudFXPlay(0x4ED);
            }
            if (++D_8010B9E4_swinging_with_sharks == 120) {
                D_8010BAE0_swinging_with_sharks = GMesCreate(8);
                func_801088F0_swinging_with_sharks(334.0f, 0.0f, 0.0f, 54.0f, 435.0f, -148.0f, 4340.0f, 30);
            }
            if (D_8010B9E4_swinging_with_sharks > 120 && GMesStatGet() == 0) {
                GMesCreate(0x1A, 10, 160, 120);
                D_8010B9E2_swinging_with_sharks = 329;
                D_8010B9E4_swinging_with_sharks = 0;
                D_8010B9E0_swinging_with_sharks = 1;
            }
            break;
        case 1:
            if (D_8010B9E2_swinging_with_sharks > 0) {
                D_8010B9E2_swinging_with_sharks--;
                func_8003F578_main(D_8010B9E2_swinging_with_sharks / 30);
                if (D_8010B9E2_swinging_with_sharks == 0) {
                    func_8003F5C0_main();
                    D_8010B9E4_swinging_with_sharks = 0;
                }
            }
            break;
        case 3:
            if (D_8010B9E4_swinging_with_sharks == 0) {
                GMesCreate(0x13);
                HuAudSeqFadeOut(120);
                D_8010B9E4_swinging_with_sharks++;
                D_8010BAE2_swinging_with_sharks = 0;
            }
            if (++D_8010BAE2_swinging_with_sharks == 30) {
                func_8004AEF0_main(D_8010B9E6_swinging_with_sharks, 30);
            }
            if (GMesStatGet() == 0) {
                D_8010B9E4_swinging_with_sharks++;
                if (D_8010B9DE_swinging_with_sharks == -1) {
                    if (D_8010B9E4_swinging_with_sharks >= 16) {
                        GMesCreate(0x1D);
                        D_8010B9E4_swinging_with_sharks = 0;
                        D_8010B9E0_swinging_with_sharks = 4;
                        HuAudSeqPlay(0x6B);
                    }
                } else if (D_8010B9E4_swinging_with_sharks >= 16) {
                    GMesCreate(0x24);
                    D_8010B9E4_swinging_with_sharks = 0;
                    D_8010B9E0_swinging_with_sharks = 4;
                    HuAudSeqPlay(0x68);
                }
            }
            break;
        case 4:
            if (++D_8010B9E4_swinging_with_sharks >= 136) {
                D_8010B9E4_swinging_with_sharks = 0;
                D_8010ACE1_swinging_with_sharks = 1;
                D_8010B9E0_swinging_with_sharks = 5;
            }
            break;
        case 5:
            break;
    }
    func_8010A0C0_swinging_with_sharks();
    func_8010A260_swinging_with_sharks();
    func_8010A4DC_swinging_with_sharks();
    func_8010AAA0_swinging_with_sharks();
}

void func_80106334_swinging_with_sharks(void) {
    Hu3DMotionSet(D_8010B8E0_swinging_with_sharks[32], D_8010B948_swinging_with_sharks[41]);
    func_8001C814_main(D_8010B8E0_swinging_with_sharks[32], 1, 1);
    Hu3DMotionTimeSet(D_8010B8E0_swinging_with_sharks[32], 0.0f);
    func_8001FA68_main(D_8010B8E0_swinging_with_sharks[33]);
    func_8001C514_main(D_8010B8E0_swinging_with_sharks[33]);
}

void func_80106398_swinging_with_sharks(omObjData *object) {
    Vec pos;
    s32 jump = FALSE;
    f32 y;
    f32 velY;
    s16 frames;

    func_80108DB0_swinging_with_sharks(&pos);
    Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[32], pos.x, pos.y, pos.z);
    Hu3DModelRotSet(D_8010B8E0_swinging_with_sharks[32], 0.0f, 90.0f, D_8010ACE4_swinging_with_sharks);
    if (D_8010ACE8_swinging_with_sharks < 180.0f) {
        Hu3DMotionTimeSet(D_8010B8E0_swinging_with_sharks[32], D_8010ACE8_swinging_with_sharks / 12.0f);
    } else {
        Hu3DMotionTimeSet(D_8010B8E0_swinging_with_sharks[32], (360.0f - D_8010ACE8_swinging_with_sharks) / 12.0f);
    }
    if (D_8010B9E0_swinging_with_sharks > 0) {
        if (D_8010B9E8_swinging_with_sharks != 0) {
            if (D_8010B9EC_swinging_with_sharks <= 0) {
                if (D_8010B9EA_swinging_with_sharks != 0) {
                    if (D_8010B9EE_swinging_with_sharks <= D_8010ACE4_swinging_with_sharks &&
                        D_8010ACE8_swinging_with_sharks < 90.0f) {
                        jump = TRUE;
                    }
                } else if ((150.0f < D_8010ACE8_swinging_with_sharks && D_8010ACE8_swinging_with_sharks < 180.0f) ||
                           345.0f < D_8010ACE8_swinging_with_sharks) {
                    jump = TRUE;
                }
            } else {
                D_8010B9EC_swinging_with_sharks--;
            }
        } else {
            jump = D_800D5558_main[D_8010B9DA_swinging_with_sharks] & 0x8000;
        }
        if ((D_8010B9E2_swinging_with_sharks != 0 && jump) ||
            (D_8010B9E2_swinging_with_sharks == 0 &&
             ((150.0f < D_8010ACE8_swinging_with_sharks && D_8010ACE8_swinging_with_sharks < 180.0f) ||
              345.0f < D_8010ACE8_swinging_with_sharks))) {
            HuAudFXPlay(0x4E9);
            if (D_8010B9E2_swinging_with_sharks != 0) {
                func_8003F5C0_main();
            }
            velY = pos.y - D_8010B9B8_swinging_with_sharks.y + 10.0f;
            y = pos.y;
            for (frames = 0;; frames++) {
                y += velY;
                velY -= 4.0f;
                if (y <= 0.0f) {
                    break;
                }
            }
            D_8010B9E0_swinging_with_sharks = 2;
            D_8010B9C4_swinging_with_sharks = pos;
            if (10.0f < D_8010ACE4_swinging_with_sharks && D_8010ACE4_swinging_with_sharks <= 80.0f &&
                D_8010ACE8_swinging_with_sharks <= 90.0f) {
                D_8010B9AC_swinging_with_sharks.x =
                    ((D_8010ACE4_swinging_with_sharks - 10.0f) * 14.285714f - 170.0f - pos.x) / frames;
            } else {
                D_8010B9AC_swinging_with_sharks.x = pos.x - D_8010B9B8_swinging_with_sharks.x;
            }
            D_8010B9AC_swinging_with_sharks.y = pos.y - D_8010B9B8_swinging_with_sharks.y;
            D_8010B9AC_swinging_with_sharks.z = 0.0f;
            D_8010B9AC_swinging_with_sharks.y += 10.0f;
            D_8010B9D0_swinging_with_sharks *= 1.1f;
            D_8010B9D4_swinging_with_sharks = D_8010ACE4_swinging_with_sharks;
            object->work[0] = 0;
            Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[32], D_8010B948_swinging_with_sharks[34], 0, 4, 0);
            object->func = func_80106870_swinging_with_sharks;
        }
    }
    D_8010B9B8_swinging_with_sharks = pos;
}

void func_80106870_swinging_with_sharks(omObjData *object) {
    f32 x;
    s16 i;

    D_8010B9C4_swinging_with_sharks.x += D_8010B9AC_swinging_with_sharks.x;
    D_8010B9C4_swinging_with_sharks.y += D_8010B9AC_swinging_with_sharks.y;
    D_8010B9C4_swinging_with_sharks.z += D_8010B9AC_swinging_with_sharks.z;
    D_8010B9AC_swinging_with_sharks.y -= 4.0f;
    if (object->work[0] < 6) {
        Hu3DModelRotSet(D_8010B8E0_swinging_with_sharks[32], 0.0f, 90.0f,
                        cosdf(object->work[0] * 18.0f) * D_8010B9D4_swinging_with_sharks);
        object->work[0]++;
    }
    if (D_8010B9C4_swinging_with_sharks.y <= 0.0f) {
        CharFXPlay(0x70, D_8010B9DC_swinging_with_sharks);
        omVibrate(D_8010B9D8_swinging_with_sharks, 10, 0, 10);
        D_8010B9E0_swinging_with_sharks = 3;
        D_8010B9D4_swinging_with_sharks = 0.0f;
        Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[32], D_8010B948_swinging_with_sharks[35], 0, 8, 2);
        Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[47], D_8010B948_swinging_with_sharks[48], 0, 4, 2);
        Hu3DModelRotSet(D_8010B8E0_swinging_with_sharks[32], 0.0f, 90.0f, 0.0f);
        object->work[0] = 0;
        func_8001C258_main(D_8010B8E0_swinging_with_sharks[29], 4, 0);
        Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[29], D_8010B9C4_swinging_with_sharks.x, 0.0f,
                        D_8010B9C4_swinging_with_sharks.z);
        Hu3DMotionSpeedSet(D_8010B8E0_swinging_with_sharks[29], 0.5f);
        Hu3DModelScaleSet(D_8010B8E0_swinging_with_sharks[29], 3.0f, 3.0f, 3.0f);
        func_8001C258_main(D_8010B8E0_swinging_with_sharks[30], 4, 0);
        Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[30], D_8010B9C4_swinging_with_sharks.x, -30.0f,
                        D_8010B9C4_swinging_with_sharks.z + 50.0f);
        Hu3DModelScaleSet(D_8010B8E0_swinging_with_sharks[30], 2.0f, 2.0f, 2.0f);
        HuAudFXPlay(0x4EF);
        object->func = func_80106D44_swinging_with_sharks;
    } else if (D_8010B9C4_swinging_with_sharks.y < 90.0f) {
        for (i = 0; i < 5; i++) {
            x = Hu3DData[D_8010B8E0_swinging_with_sharks[i + 3]].pos.x;
            if (x - 80.0f < D_8010B9C4_swinging_with_sharks.x && D_8010B9C4_swinging_with_sharks.x < x + 80.0f) {
                HuAudFXPlay(0x4EC);
                omVibrate(D_8010B9D8_swinging_with_sharks, 10, 0, 10);
                D_8010B9E0_swinging_with_sharks = 3;
                D_8010B9D4_swinging_with_sharks = 0.0f;
                if (D_8010B9C4_swinging_with_sharks.x < x - 40.0f) {
                    Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[32], D_8010B948_swinging_with_sharks[36], 0, 8, 0);
                } else if (x + 40.0f < D_8010B9C4_swinging_with_sharks.x || 35.0f < D_8010B9AC_swinging_with_sharks.x) {
                    Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[32], D_8010B948_swinging_with_sharks[37], 0, 4, 0);
                } else {
                    func_8001C814_main(D_8010B8E0_swinging_with_sharks[32], 4, 4);
                }
                Hu3DModelRotSet(D_8010B8E0_swinging_with_sharks[32], 0.0f, 100.0f, 0.0f);
                Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[32], D_8010B9C4_swinging_with_sharks.x, 50.0f,
                                D_8010B9C4_swinging_with_sharks.z);
                D_8010B9DE_swinging_with_sharks = i;
                func_8001C258_main(D_8010B8E0_swinging_with_sharks[42], 4, 0);
                Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[42], D_8010B9C4_swinging_with_sharks.x, 50.0f,
                                D_8010B9C4_swinging_with_sharks.z + 30.0f);
                HuAudFXPlay(0x4EF);
                object->func = func_80107044_swinging_with_sharks;
                break;
            }
        }
    }
    Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[32], D_8010B9C4_swinging_with_sharks.x,
                    D_8010B9C4_swinging_with_sharks.y, D_8010B9C4_swinging_with_sharks.z);
}

void func_80106D44_swinging_with_sharks(omObjData *object) {
    f32 scale;
    s16 model;

    if (object->work[0] == 8) {
        HuAudFXPlay(D_8010B9DC_swinging_with_sharks + 0x287);
    }
    if (object->work[0] >= 9) {
        model = D_8010B8E0_swinging_with_sharks[31];
        func_8001C258_main(model, 4, 0);
        Hu3DModelPosSet(model, D_8010B9C4_swinging_with_sharks.x, 0.0f, D_8010B9C4_swinging_with_sharks.z);
        if (D_8010B428_swinging_with_sharks > 90) {
            if (Hu3DData[D_8010B8E0_swinging_with_sharks[32]].motTime != 0.0f) {
                return;
            }
            D_8010B428_swinging_with_sharks = 0;
        }
        scale = sindf((s16)(D_8010B428_swinging_with_sharks % 90)) + 0.5f;
        Hu3DModelScaleSet(model, scale, scale, scale);
        func_8001F9E4_main(model, 255.0f - D_8010B428_swinging_with_sharks * 2.8333333f);
        D_8010B428_swinging_with_sharks += 3;
    } else {
        D_8010B9C4_swinging_with_sharks.y = sindf(object->work[0] * 18.0f) * D_8010B9AC_swinging_with_sharks.y;
        object->work[0]++;
        Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[32], D_8010B9C4_swinging_with_sharks.x,
                        D_8010B9C4_swinging_with_sharks.y, D_8010B9C4_swinging_with_sharks.z);
        Hu3DData[D_8010B8E0_swinging_with_sharks[32]].rot.y = 90.0f - object->work[0] * 11.25f;
    }
}

void func_80107044_swinging_with_sharks(omObjData *object) {
    HmfModel *shark;
    s16 model = D_8010B8E0_swinging_with_sharks[32];

    if (Hu3DData[model].motId == D_8010B948_swinging_with_sharks[37] &&
        Hu3DData[model].motTime >= D_800CCF58_main[Hu3DData[model].motId].unk02) {
        Hu3DMotionShiftSet(model, D_8010B948_swinging_with_sharks[32], 0, 16, 2);
    }
    shark = &Hu3DData[D_8010B8E0_swinging_with_sharks[D_8010B9DE_swinging_with_sharks + 3]];
    Hu3DModelPosSet(model, D_8010B9C4_swinging_with_sharks.x, shark->pos.y + 80.0f, D_8010B9C4_swinging_with_sharks.z);
    if (++object->work[0] > 20) {
        object->work[0] = 0;
        Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[47], D_8010B948_swinging_with_sharks[49], 0, 4, 0);
        object->func = func_801071A8_swinging_with_sharks;
    }
}

void func_801071A8_swinging_with_sharks(omObjData *object) {
    HmfModel *shark;
    s16 model = D_8010B8E0_swinging_with_sharks[32];

    shark = &Hu3DData[D_8010B8E0_swinging_with_sharks[D_8010B9DE_swinging_with_sharks + 3]];
    D_8010B9C4_swinging_with_sharks.x += (shark->pos.x - D_8010B9C4_swinging_with_sharks.x) / 2.0f;
    Hu3DModelPosSet(model, D_8010B9C4_swinging_with_sharks.x, shark->pos.y + 80.0f, D_8010B9C4_swinging_with_sharks.z);
    if (object->work[0] == 0) {
        Hu3DMotionShiftSet(model, D_8010B948_swinging_with_sharks[38], 0, 4, 2);
    }
    if (++object->work[0] == 75) {
        Hu3DMotionShiftSet(model, D_8010B948_swinging_with_sharks[39], 0, 4, 0);
        func_80045ED0_main((D_8010B420_swinging_with_sharks[D_8010B9DC_swinging_with_sharks] << 16) | 0x35);
    }
    if (object->work[0] < 9) {
        Hu3DData[model].rot.y = 90.0f - object->work[0] * 11.25f;
        if (object->work[0] == 8) {
            Hu3DMotionShiftSet(model, D_8010B948_swinging_with_sharks[32], 0, 8, 2);
        }
    }
}

void func_80107384_swinging_with_sharks(void) {
    HmfSkeletonNode *node;

    node = func_8001D33C_main(D_8010B8E0_swinging_with_sharks[2], D_8010B7C0_swinging_with_sharks);
    func_8002367C_main(D_8010B860_swinging_with_sharks, node->unk4C);
    node = func_8001D33C_main(D_8010B8E0_swinging_with_sharks[2], D_8010B7C8_swinging_with_sharks);
    func_8002367C_main(D_8010B8A0_swinging_with_sharks, node->unk4C);
    D_8010ACE8_swinging_with_sharks = 0.0f;
}

void func_801073F0_swinging_with_sharks(omObjData *object) {
    switch (D_8010B42A_swinging_with_sharks) {
        case 0:
            if (D_8010ACE8_swinging_with_sharks == 0.0f) {
                D_8010B42C_swinging_with_sharks = HuAudFXPlay(0x4EA);
            }
            D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
            D_8010ACE8_swinging_with_sharks += 5.0f;
            if (D_8010ACE8_swinging_with_sharks > 360.0f) {
                D_8010ACE8_swinging_with_sharks -= 360.0f;
                D_8010B42A_swinging_with_sharks++;
            }
            break;
        case 1:
            D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * 180.0f;
            D_8010ACE8_swinging_with_sharks += 5.0f;
            if (D_8010ACE8_swinging_with_sharks > 90.0f) {
                D_8010B42A_swinging_with_sharks++;
                D_8010B9D0_swinging_with_sharks = 180.0f;
            }
            break;
        case 2:
            D_8010ACE4_swinging_with_sharks = -sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
            D_8010ACE8_swinging_with_sharks += 5.0f;
            D_8010B9D0_swinging_with_sharks -= 6.0f;
            if (D_8010ACE8_swinging_with_sharks > 180.0f) {
                D_8010B9D0_swinging_with_sharks = 80.0f;
                D_8010ACE8_swinging_with_sharks += 180.0f;
                object->func = func_80107628_swinging_with_sharks;
            }
            break;
    }
    func_80108C08_swinging_with_sharks(D_8010ACE4_swinging_with_sharks);
}

void func_80107628_swinging_with_sharks(omObjData *object) {
    D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
    D_8010ACE8_swinging_with_sharks += 5.0f;
    if (D_8010ACE8_swinging_with_sharks > 360.0f) {
        D_8010ACE8_swinging_with_sharks -= 360.0f;
    }
    func_80108C08_swinging_with_sharks(D_8010ACE4_swinging_with_sharks);
    if (D_8010B9E0_swinging_with_sharks == 2) {
        object->func = func_801076DC_swinging_with_sharks;
    }
}

void func_801076DC_swinging_with_sharks(omObjData *object) {
    if (D_8010B9D0_swinging_with_sharks > 0.0f) {
        D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
        D_8010ACE8_swinging_with_sharks += 5.0f;
        if (D_8010ACE8_swinging_with_sharks > 360.0f) {
            D_8010ACE8_swinging_with_sharks -= 360.0f;
        }
        D_8010B9D0_swinging_with_sharks -= 0.5f;
        if (D_8010B9D0_swinging_with_sharks <= 0.0f) {
            D_8010B9D0_swinging_with_sharks = 0.0f;
        }
        func_80108C08_swinging_with_sharks(D_8010ACE4_swinging_with_sharks);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", D_8010B7C0_swinging_with_sharks);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", D_8010B7C8_swinging_with_sharks);

void func_801077C4_swinging_with_sharks(void) {
    SharkState *shark;
    s16 i;

    for (i = 0; i < 5; i++) {
        shark = &D_8010B9F0_swinging_with_sharks[i];
        shark->model = D_8010B8E0_swinging_with_sharks[i + 3];
        Hu3DModelPosGet(shark->model, &shark->pos);
        shark->unk20 = rand8() & 0xF8;
        shark->unk02 = 0;
        shark->unk04 = 30;
        Hu3DAnimBankSet(Hu3DAnimRead(Hu3DData[D_8010B8E0_swinging_with_sharks[i + 8]].hmf, 0x21002C, "m259_30_000_DEF"),
                        D_800A11D0_main[i]);
        Hu3DModelRemakeStatic(D_8010B8E0_swinging_with_sharks[i + 8]);
        func_8001C514_main(D_8010B8E0_swinging_with_sharks[i + 8]);
        shark->unk24 = rand8() & 0x3F;
        func_8001FA68_main(D_8010B8E0_swinging_with_sharks[i + 18]);
        func_8001C514_main(D_8010B8E0_swinging_with_sharks[i + 18]);
    }
    D_8010BAE6_swinging_with_sharks = func_8000CED8_main(0xB0004, 0x2A9);
    func_800138EC_main(D_8010BAE6_swinging_with_sharks, 1, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80107954_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108474_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801085F4_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801088F0_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801089A4_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108B24_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108B4C_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108C08_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108DB0_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108E00_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108E50_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80108F20_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109020_swinging_with_sharks);

void func_801096AC_swinging_with_sharks(void) {
    CRot = D_8010BBA8_swinging_with_sharks;
    D_8010BB90_swinging_with_sharks = CRot;
    CZoom = D_8010BB9C_swinging_with_sharks;
    Center = D_8010BB78_swinging_with_sharks;
}

void func_80109730_swinging_with_sharks(SharkEntry *arg0, s16 arg1, s16 modelId) {
    SharkEntry *entry = &arg0[arg1];
    Hu3DModelPosSet(modelId, entry->pos.x, entry->pos.y, entry->pos.z);
    Hu3DModelRotSet(modelId, entry->rot.x, entry->rot.y, entry->rot.z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010979C_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_801098C0_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109924_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109950_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109B04_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_80109C90_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010A0C0_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010A260_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010A41C_swinging_with_sharks);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010A4DC_swinging_with_sharks);

void func_8010AA68_swinging_with_sharks(void) {
    D_8010BB48_swinging_with_sharks = Hu3DData[D_8010B8E0_swinging_with_sharks[44]].rot.y;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3F_swinging_with_sharks/2E0D20", func_8010AAA0_swinging_with_sharks);
