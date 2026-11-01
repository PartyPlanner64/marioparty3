#include "game/esprite.h"
#include "game/data.h"
#include "game/sprite.h"
#include "mallocblock.h"
#include "include_asm.h"

// malloc
void HuMemMemoryFreePerm(void *ptr);

extern u16 D_800C951C_main;
extern u16 D_800CB8BC_main;
extern s16 D_800D5438_main;
extern HuSprite_Unk84_Struct *D_800C9530_main[];

void espInit(void) {
    u16 var_a0;

    HuSprInit();
    D_800CD1DC_main = HuMemAlloc(0x100 * sizeof(ESPRITE));
    D_800C951C_main = 0x100;
    D_800CB8BC_main = 0;
    for (var_a0 = 0; var_a0 < 0x100; var_a0++) {
        ESPRITE *temp_v0 = &D_800CD1DC_main[var_a0];

        temp_v0->unk00 = 0;
        temp_v0->unk02 = var_a0 + 1;
        temp_v0->unk1C = 0xFF;
        temp_v0->unk1E = 0xFF;
        temp_v0->unk20 = 0;
    }
    D_800D5438_main = 0;
}

s16 func_8000B838_main(s32 arg0) {
    void *temp_v0;
    s16 temp_s0;

    temp_v0 = DataRead(arg0);
    temp_s0 = HuSprAnimRead(temp_v0);
    HuMemMemoryFreePerm(temp_v0);
    return temp_s0;
}

void func_8000B880_main(s16 arg0, f32 r, f32 g, f32 b) {
    HuSprite_Unk84_Struct *tex = D_800C9530_main[arg0];
    u16 *pal = tex->unk0C;
    s32 i;
    u16 red, green, blue, alpha;

    for (i = 0; i < tex->unk1A; i++, pal++) {
        red = *pal >> 11;
        green = (*pal >> 6) & 0x1F;
        blue = (*pal >> 1) & 0x1F;
        alpha = *pal & 1;
        red = red * r;
        green = green * g;
        blue = blue * b;
        alpha |= (red << 11) | (green << 6) | (blue << 1);
        *pal = alpha;
    }
}

void func_8000BA00_main(void) {
    HuSprClose();
    HuMemFree(D_800CD1DC_main);
    D_800CD1DC_main = NULL;
}

void espMain(void) {
    ESPRITE *sprite;
    s16 gid;
    s32 i;

    if (D_800CD1DC_main != NULL) {
        for (i = 0; i < D_800C951C_main; i++) {
            if (D_800CD1DC_main[i].unk00 & 1) {
                sprite = &D_800CD1DC_main[i];
                gid = sprite->unk04;
                HuSprPosSet(gid, 0, sprite->unkA, sprite->unkC);
                if (sprite->unk00 & 2) {
                    HuSprTPLvlSet(gid, 0, sprite->unk1E);
                    sprite->unk1E += sprite->unk20;
                    if (sprite->unk20 > 0) {
                        if (sprite->unk1E > sprite->unk1C) {
                            sprite->unk1E = sprite->unk1C;
                        }
                    } else if (sprite->unk1E < sprite->unk1C) {
                        sprite->unk1E = sprite->unk1C;
                    }
                    if (sprite->unk1E == sprite->unk1C) {
                        sprite->unk00 &= ~2;
                    }
                }
            }
        }
    }
}

void espDispOn(u16 arg0) {
    HuSprDispOn(D_800CD1DC_main[arg0].unk04, 0);
}

void espDispOff(u16 arg0) {
    HuSprDispOff(D_800CD1DC_main[arg0].unk04, 0);
}

void espPosSet(u16 spriteId, s16 x, s16 y) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    sprite->unkA = x;
    sprite->unkC = y;
}

void espTPLvlSet(u16 spriteId, s16 arg1) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    sprite->unk1E = arg1;
    sprite->unk1C = arg1;
    HuSprTPLvlSet(sprite->unk04, 0, arg1);
}

void espAttrSet(u16 arg0, u16 arg1) {
    ESPRITE *temp = &D_800CD1DC_main[arg0];

    HuSprAttrSet(temp->unk04, 0, arg1);
}

void espAttrReset(u16 arg0, u16 arg1) {
    ESPRITE *temp = &D_800CD1DC_main[arg0];

    HuSprAttrReset(temp->unk04, 0, arg1);
}

void espPriSet(u16 spriteId, s32 arg1) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    HuSprPriSet(sprite->unk04, 0, arg1);
}

void espSpeedSet(u16 spriteId, f32 arg1) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    HuSprSpeedSet(sprite->unk04, 0, arg1);
}

void func_8000BD50_main(u16 spriteId, s16 arg1) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    func_80054FF8_main(sprite->unk04, 0, arg1);
}

void espBankSet(u16 spriteId, s32 arg1, s32 arg2) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    HuSprBankSet(sprite->unk04, 0, arg1, (u16)arg2);
}

void func_8000BDDC_main(u16 spriteId, s32 arg1) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    func_800550F4_main(sprite->unk04, 0, (u16)arg1);
}

u8 func_8000BE1C_main(u16 spriteId) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    return func_800551AC_main(sprite->unk04, 0);
}

void espScaleSet(u16 spriteId, f32 x, f32 y) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    HuSprScaleSet(sprite->unk04, 0, x, y);
}

void espColorSet(u16 spriteId, s32 arg1, s32 arg2, s32 arg3) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    HuSprColorSet(sprite->unk04, 0, arg1, arg2, arg3);
}

void espZRotSet(u16 spriteId, f32 arg1) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    HuSprZRotSet(sprite->unk04, 0, arg1);
}

void func_8000BF48_main(u16 spriteId, s16 arg1, s16 arg2, s16 arg3) {
    u16 temp_v0;
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + spriteId;
    sprite->unk00 |= 2;
    sprite->unk1C = arg1;
    if (arg2 > 0) {
        sprite->unk1E = arg2;
    }
    sprite->unk20 = arg3;
}

void func_8000BF8C_main(u16 spriteId, s16 arg1) {
    u16 temp_v0;
    ESPRITE *sprite;
    u16 phi_return;

    sprite = D_800CD1DC_main + spriteId;
    sprite->unk00 &= 0xFFFD;
    if (arg1 > 0) {
        sprite->unk1E = arg1;
        sprite->unk1C = arg1;
        HuSprTPLvlSet(sprite->unk04, 0, arg1 & 0xFFFF);
    }
}

s16 espEntry(s16 arg0, s16 arg1, u16 arg2) {
    ESPRITE *temp_s0;
    s16 temp_s3;
    s16 temp_v0;

    if (D_800CB8BC_main == D_800C951C_main) {
        return -1;
    }
    D_800CB8BC_main++;
    temp_s3 = D_800D5438_main;
    temp_s0 = &D_800CD1DC_main[temp_s3];
    D_800D5438_main = temp_s0->unk02;
    temp_s0->unk04 = temp_v0 = HuSprGrpCreate(1, 0);
    temp_s0->unk00 |= 1;
    temp_s0->unk06 = arg0;
    temp_s0->unk10 = temp_s0->unk14 = 1.0f;
    HuSprTPLvlSet(temp_v0, 0, 0x100);
    HuSprAttrReset(temp_v0, 0, 0xFFFF);
    HuSprAttrSet(temp_v0, 0, 0x1000);
    HuSprScaleSet(temp_v0, 0, 1.0f, 1.0f);
    func_800550F4_main(temp_v0, 0, arg2);
    HuSprGrpMemberSet(temp_v0, 0, arg0, arg1);
    HuSprPriSet(temp_v0, 0, 10);
    if (arg2 == 0) {
        func_80054FF8_main(temp_v0, 0, 0);
    }
    return temp_s3;
}

void espKill(u16 arg0) {
    ESPRITE *sprite;

    sprite = D_800CD1DC_main + arg0;
    if ((sprite->unk00 & 1) != 0) {
        HuSprGrpKill(sprite->unk04);
        sprite->unk00 = 0;
        sprite->unk02 = D_800D5438_main;
        D_800D5438_main = arg0;
        D_800CB8BC_main--;
    }
}
