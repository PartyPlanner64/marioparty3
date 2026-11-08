#include "common.h"
#include "../ovl_81_name/ovl_81.h"

void func_8010BA98_boardresult(void);
void func_8010BAD8_boardresult(omObjData *);
void func_8010BBF0_boardresult(omObjData *);
void func_8010BC3C_boardresult(void);
void func_8010BCA4_boardresult(void);
extern s32 D_8010E72C_boardresult[];
extern u32 D_8010E738_boardresult[];
extern s32 D_8010E73C_boardresult[];
extern s32 *D_8010E88C_boardresult[];
extern s32 *D_8010E8AC_boardresult[];
extern omObjData *D_8010E8EC_boardresult[4];
extern s32 D_8010E910_boardresult[6];
extern u8 D_8010EAF0_boardresult;
extern Object *D_8010EAF4_boardresult;
extern s32 D_8010EB88_boardresult[4];
extern s32 D_8010EB98_boardresult;

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

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010685C_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106968_boardresult);

s16 func_80106A38_boardresult(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = func_800329B4_main(data);

    DataClose(data);
    return anim;
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106A80_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106CA8_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106DA4_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80106F54_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_801070F8_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80107598_boardresult);

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

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80107EE8_boardresult);

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

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010935C_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_801094A8_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA60_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA70_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA80_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EA90_boardresult);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult/3B9670", D_8010EAB0_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_80109754_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010BA98_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010BAD8_boardresult);

void func_8010BBF0_boardresult(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(2, 20);
        func_80007EC0_main(40);
        obj->func = func_8010BAD8_boardresult;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010BC3C_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3B9670", func_8010BC70_boardresult);

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
