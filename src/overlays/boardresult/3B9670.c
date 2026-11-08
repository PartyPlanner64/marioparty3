#include "common.h"
#include "../ovl_81_name/ovl_81.h"

typedef struct BoardResultWork BoardResultWork;

void func_80105BD8_boardresult(void);
void func_80109754_boardresult(void);
void func_8010BA98_boardresult(void);
void func_8010BAD8_boardresult(omObjData *);
void func_8010BBF0_boardresult(omObjData *);
void func_8010BC3C_boardresult(void);
void func_8010BC70_boardresult(void);
void func_8010BCA4_boardresult(void);
void func_8010BD04_boardresult(void);
void func_8010BDC4_boardresult(BoardResultWork *, f32, f32, f32);
void func_8010BDD4_boardresult(BoardResultWork *, f32, f32, f32);
void func_8010BDE4_boardresult(BoardResultWork *, s16);
extern s32 D_8010E3E0_boardresult;
extern s32 D_8010E72C_boardresult[];
extern u32 D_8010E738_boardresult[];
extern s32 D_8010E73C_boardresult[];
extern s32 *D_8010E88C_boardresult[];
extern s32 *D_8010E8AC_boardresult[];
extern omObjData *D_8010E8EC_boardresult[4];
extern s32 D_8010E910_boardresult[6];
extern u8 D_8010EAF0_boardresult;
extern Object *D_8010EAF4_boardresult;
extern Object *D_8010EB48_boardresult;
extern Object *D_8010EB4C_boardresult;
extern Object *D_8010EB50_boardresult;
extern Object *D_8010EB60_boardresult[4];
extern Object *D_8010EB70_boardresult;
extern s16 D_8010EB74_boardresult;
extern s16 D_8010EB76_boardresult;
extern s32 D_8010EB88_boardresult[4];
extern s32 D_8010EB98_boardresult;
extern s16 kakusiMasuItemHis[10];

void func_801059A0_boardresult(void) {
    s32 i;
    u32 j;

    D_8010EAF0_boardresult = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    func_8010BCA4_boardresult();
    func_8010BC3C_boardresult();
    func_800D87DC_name_81(700.0f);
    func_800D85A8_name_81(1.6f);
    HuWinInit();
    omAddPrcObj(func_8010BA98_boardresult, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_8010BBF0_boardresult);

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010E72C_boardresult[0]; j++) {
            D_8010E88C_boardresult[i][j + 1] = func_80017BB8_main(i, D_8010E72C_boardresult[j + 1]);
        }
    }

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_8010E738_boardresult[0]; j++) {
            D_8010E8AC_boardresult[i][j + 1] = func_80017BB8_main(i, D_8010E738_boardresult[j + 1]);
        }
    }

    func_800EF3EC_name_81(4);
}

void func_80105B68_boardresult(omObjData *obj) {
    D_8010EAF4_boardresult->velocity.x = sindf(obj->rot.x) * obj->rot.z;
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80105BD8_boardresult);

s16 func_8010685C_boardresult(s16 model, s32 dataNum, char *name) {
    void *data = DataRead(dataNum);
    s32 anim;
    s16 animIdx;

    anim = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_8010EB74_boardresult = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    animIdx = D_800D1714_main[(s16)anim].animIdx;
    D_8010EB76_boardresult = HmfAnimLink(HmfModelData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void func_80106968_boardresult(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (D_8010EB76_boardresult != 0xFF) {
        if (animIdx == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            anim = &D_800D1714_main[D_8010EB76_boardresult];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 func_80106A38_boardresult(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = func_800329B4_main(data);

    DataClose(data);
    return anim;
}

void func_80106A80_boardresult(omObjData *obj) {
    func_8001E888_main(D_8010EB48_boardresult->omObj1->model[0], obj->trans.x, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    func_8001E888_main(D_8010EB4C_boardresult->omObj1->model[0], obj->trans.y, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    func_8001E888_main(D_8010EB50_boardresult->omObj1->model[0], obj->trans.z, 0, 0x40, 0x2B, "kumo-endkumo", 0);

    obj->trans.x -= 4.0f;
    obj->trans.y -= 2.0f;
    obj->trans.z -= 1.0f;

    if (obj->trans.x >= 64.0f) {
        obj->trans.x -= 64.0f;
    }
    if (obj->trans.y >= 64.0f) {
        obj->trans.y -= 64.0f;
    }
    if (obj->trans.z >= 64.0f) {
        obj->trans.z -= 64.0f;
    }
    if (obj->trans.x <= -64.0f) {
        obj->trans.x += 64.0f;
    }
    if (obj->trans.y <= -64.0f) {
        obj->trans.y += 64.0f;
    }
    if (obj->trans.z <= -64.0f) {
        obj->trans.z += 64.0f;
    }
}

void func_80106CA8_boardresult(omObjData *obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8010EB60_boardresult[i]->rot.x = sindf(obj->rot.x);
        D_8010EB60_boardresult[i]->rot.z = cosdf(obj->rot.x);
    }

    if (obj->work[0] == 0) {
        obj->rot.x += 20.0f;
        if (obj->rot.x >= 360.0f) {
            obj->rot.x -= 360.0f;
        }
    } else if (obj->rot.x < 360.0f) {
        obj->rot.x += 20.0f;
    } else {
        obj->rot.x = 360.0f;
    }
}

void func_80106DA4_boardresult(omObjData *obj) {
    Object *target = D_8010EB60_boardresult[obj->work[1]];

    obj->work[0]++;
    target->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * -700.0f;
    target->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    target->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void func_80106F54_boardresult(omObjData *obj) {
    Object *target = D_8010EB70_boardresult;

    obj->work[0]++;
    target->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * 700.0f;
    target->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    target->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_801070F8_boardresult);

void func_80107598_boardresult(omObjData *obj) {
    f32 scale;
    u32 i;

    scale = sinf(obj->rot.x * (M_PI / 180.0)) * 0.3f + 1.0;
    for (i = 0; i < obj->work[1]; i++) {
        HuSprScaleSet(D_8010EB88_boardresult[obj->work[0]], i, scale, scale);
    }

    obj->rot.x += 30.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_801076A0_boardresult);

void func_80107AB4_boardresult(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8010E8EC_boardresult[i] != NULL) {
            omDelObj(D_8010E8EC_boardresult[i]);
            D_8010E8EC_boardresult[i] = NULL;
        }
        HuSprGrpKill(D_8010EB88_boardresult[i]);
    }
    HuSprAnimKill(D_8010EB98_boardresult);
    HuPrcVSleep();
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80107B50_boardresult);

void func_80107EE8_boardresult(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8010E8EC_boardresult[i] != NULL) {
            omDelObj(D_8010E8EC_boardresult[i]);
            D_8010E8EC_boardresult[i] = NULL;
        }
        HuSprGrpKill(D_8010EB88_boardresult[i]);
    }
    HuSprAnimKill(D_8010EB98_boardresult);
    HuPrcVSleep();
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80107F84_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80108378_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80109128_boardresult);

s32 func_80109320_boardresult(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_8010E910_boardresult[i] == 0) {
            break;
        }
    }
    return i == 6;
}

void func_8010935C_boardresult(BoardResultWork *work, s32 index) {
    s32 x, y, z;

    x = func_800EFE20_name_81(256.0f) - 128;
    y = -func_800EFE20_name_81(256.0f) - 500;
    func_8010BDD4_boardresult(work, x, y, 0.0f);
    x = func_800EFE20_name_81(100.0f) + index * 500 - 550;
    y = func_800EFE20_name_81(64.0f) + 218;
    z = func_800EFE20_name_81(500.0f) - 500;
    func_8010BDC4_boardresult(work, x, y, z);
    func_8010BDE4_boardresult(work, func_800EFE20_name_81(60.0f) + 30);
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_801094A8_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA60_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA70_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA80_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA90_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EAB0_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80109754_boardresult);

void func_8010BA98_boardresult(void) {
    func_80105BD8_boardresult();
    func_80109754_boardresult();
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_8010BAD8_boardresult(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_8010BD04_boardresult();
        func_8010BC70_boardresult();
        if (D_8010E3E0_boardresult == 0) {
            HuWinAllKill();
        }
        if (!(GwSystem.playMode & 4)) {
            GWPlayNumInc(-1);
            GWCharPlayNumInc(-1, GwPlayer[kakusiMasuItemHis[0]].chr);
        }
        if (GwSystem.playMode & 4) {
            if (_CheckFlag(0)) {
                _ClearFlag(0);
                _ClearFlag(0x28);
            }
        } else if (_CheckFlag(0)) {
            _ClearFlag(0);
            _ClearFlag(0x16);
            SLSaveBoard(1);
        } else {
            SLCommonSet(1);
        }
        omOvlGotoEx(0x55, 0, 0x4190);
    }
}

void func_8010BBF0_boardresult(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 20);
        func_80007EC0_main(40);
        obj->func = func_8010BAD8_boardresult;
    }
}

void func_8010BC3C_boardresult(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800EF840_name_81();
    func_800F4300_name_81();
}

void func_8010BC70_boardresult(void) {
    func_800F4314_name_81();
    func_800EF880_name_81();
    func_800F4030_name_81();
    func_800D7F0C_name_81();
}

void func_8010BCA4_boardresult(void) {
    Hu3DCamInit(1);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0);
    func_800E8180_name_81(1000.0f, 10000.0f);
}

void func_8010BD04_boardresult(void) {
    MBDBackKill();
    MBDBackClose();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EADC_boardresult);
