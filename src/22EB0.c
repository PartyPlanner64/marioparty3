#include "common.h"
#include "mallocblock.h"
#include "gcc/string.h"

typedef struct {
    u8 next;
    u8 unk01;
    s16 unk02;
    f32 depth;
} HmfDrawEntry;

extern HmfDrawEntry *D_800D2070_main[8];
extern s16 D_800D6AC8_main[8];
extern s16 D_800D5564_main;

extern s16 D_800A0A78_main;
extern s16 D_800A1160_main;
extern s16 D_800CDD6A_main;
extern f32 D_800D2120_main;
extern u16 D_800D5204_main;

s16 func_80011460_main(u8 *);
void func_80018544_main(s32, s32);
void func_80019C00_main(void *data);
void func_80022660_main(HmfData *);
void func_80030030_main(f32);
void func_8002FE08_main(s16, s16, char *, s16, s16, s16);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_800222B0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_800224BC_main);

void func_800225D4_main(void) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(D_800D2070_main); i++) {
        D_800D6AC8_main[i] = 2;
        D_800D2070_main[i][0].next = 1;
        D_800D2070_main[i][1].unk01 = 0;
        D_800D2070_main[i][1].next = 0;
        D_800D2070_main[i][1].depth = 200000.0f;
    }
    D_800D5564_main = 0;
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80022660_main);

void func_80022F08_main(HmfData *arg0) {
    s16 needed;
    s16 i;
    u16 count;

    needed = 0;
    for (i = 0, count = 0; i < arg0->unk10; i++) {
        if (arg0->unk60[i].unk50 & 0x20000) {
            needed = 1;
        }
        count += (u16)arg0->unk60[i].unk22;
    }
    if (needed && arg0->unkB0 == NULL) {
        arg0->unkB0 = HuMemAllocTag(count * sizeof(*arg0->unkB0), D_800CDD6A_main);
    }
}

void func_80022FF4_main(HmfData *arg0) {
    HmfVertexGroup *group;
    s16 *indices;
    s16 i, j;
    u16 count;
    f32 x, y, z;

    if (arg0->unkB0 == NULL) {
        return;
    }
    group = arg0->unkB0;
    for (i = 0; i < arg0->unk1A; i++, group++) {
        indices = group->indices;
        count = group->count;
        x = y = z = 0.0f;
        for (j = 0; j < count; j++, indices++) {
            x += arg0->unk40[*indices].v.ob[0];
            y += arg0->unk40[*indices].v.ob[1];
            z += arg0->unk40[*indices].v.ob[2];
        }
        group->center.x = x / count;
        group->center.y = y / count;
        group->center.z = z / count;
    }
}

void func_800230F8_main(HmfData *arg0) {
    s16 textureIndex;
    s16 i, j;

    textureIndex = 4; // TODO: why does this start at 4?

    for (i = 0; i < arg0->unk12; i++) {
        /* Skip entries marked as 0xFF */
        if (arg0->unk84[i].unk9 == 0xFF) {
            continue;
        }

        /* Find first entry with different unkC value */
        for (j = 0; j < i; j++) {
            if (arg0->unk84[i].unkC == arg0->unk84[j].unkC) {
                break;
            }
        }

        /* Copy or assign texture indices */
        if (j != i) {
            arg0->unk84[i].unk3 = arg0->unk84[j].unk3;
            arg0->unk84[i].unk4 = arg0->unk84[j].unk4;
        } else {
            arg0->unk84[i].unk3 = textureIndex++;
            if (arg0->unk84[i].unkC->unk_30 != NULL) {
                arg0->unk84[i].unk4 = textureIndex++;
            }

            if (textureIndex > 16) {
                osSyncPrintf("Texture Anime Over\n");
                return;
            }
        }
    }
}

s32 func_80023264_main(HmfData *arg0) {
    s32 var_s2;
    s16 i;

    var_s2 = 0;
    if (arg0->unk40 != NULL) {
        for (i = 0; i < ARRAY_COUNT(arg0->unk44); i++) {
            if (arg0->unk40 != arg0->unk44[i]) {
                if (arg0->unk0A != 0) {
                    func_80019C00_main(arg0->unk44[i]);
                } else {
                    HuMemFree(arg0->unk44[i]);
                }
                arg0->unk44[i] = arg0->unk40;
                var_s2 = 1;
            }
        }

        if (arg0->unk0A != 0) {
            func_80019C00_main(arg0->unk40);
        } else {
            HuMemFree(arg0->unk40);
        }
    }
    if (arg0->unk3C != NULL) {
        for (i = 0; i < arg0->unk10; i++) {
            if (arg0->unk0A != 0) {
                func_80019C00_main(arg0->unk3C->unk00[i]);
            } else {
                HuMemFree(arg0->unk3C->unk00[i]);
            }
        }

        if (arg0->unk0A != 0) {
            func_80019C00_main(arg0->unk3C);
        } else {
            HuMemFree(arg0->unk3C);
        }
    }
    D_800D5204_main = arg0->unk0E;
    D_800CDD6A_main = arg0->unk0E + 1;
    func_80022660_main(arg0);
    return var_s2;
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80023404_main);

void func_8002367C_main(HuMtx4F dst, HuMtx4F src) {
    dst[0][0] = src[0][0];
    dst[0][1] = src[0][1];
    dst[0][2] = src[0][2];
    dst[0][3] = src[0][3];
    dst[1][0] = src[1][0];
    dst[1][1] = src[1][1];
    dst[1][2] = src[1][2];
    dst[1][3] = src[1][3];
    dst[2][0] = src[2][0];
    dst[2][1] = src[2][1];
    dst[2][2] = src[2][2];
    dst[2][3] = src[2][3];
    dst[3][0] = src[3][0];
    dst[3][1] = src[3][1];
    dst[3][2] = src[3][2];
    dst[3][3] = src[3][3];
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80023700_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80023AF8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002404C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80024354_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80024814_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80024D94_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80024DF0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_800250D4_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_800257BC_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_800260F0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_80029FB4_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002A358_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002AC5C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002AF40_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002AFEC_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002B104_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002B2AC_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C0EC_main);

s32 func_8002C4C0_main(HmfData *arg0, s16 arg1, s32 arg2, s32 arg3) {
    if (!(arg0->unk60[arg1].unk50 & 0x70000000)) {
        return 0;
    }
    func_80018544_main(arg2, arg3);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C520_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C5B8_main);

s32 func_8002C834_main(HmfData *arg0, char *name) {
    s16 hash;
    s16 i;

    hash = func_80011460_main((u8 *)name);
    for (i = 0; i < arg0->unk10; i++) {
        if (arg0->unk60[i].unk26 == hash && strcmp(arg0->unk60[i].unk00, name) == 0) {
            break;
        }
    }
    if (i == arg0->unk10) {
        osSyncPrintf("Can't find ObjName %s\n", name);
        return -1;
    }
    return i;
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C914_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002C960_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002CAE4_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002CB6C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002CDF4_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D094_main);

void func_8002D260_main(void) {
    s16 i;

    func_80030030_main(1.0f);
    D_800CCF58_main = HuMemAlloc(HU3D_MODEL_MAX * sizeof(*D_800CCF58_main));
    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        D_800CCF58_main[i].unk02 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D2D8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D3AC_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D3D0_main);

void func_8002D4B8_main(s32 arg0) {
    s16 modelIndex = arg0;

    if (modelIndex != 0xFF) {
        HuMemFreeAllWithTag(modelIndex + 0x2874);
        D_800CCF58_main[modelIndex].unk02 = -1;
    }
}

void func_8002D514_main(void) {
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        if (D_800CCF58_main[i].unk02 != -1) {
            HuMemFreeAllWithTag(i + 0x2874);
            D_800CCF58_main[i].unk02 = -1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002D5B0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DA98_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DD4C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DF2C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002DFF8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002E78C_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002E8E8_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002EAC0_main);

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002F60C_main);

void func_8002FB08_main(HmfData *arg0, f32 arg1) {
    if (arg0->unk98->unk02 & 1) {
        return;
    }

    arg0->unk98->unk08 = arg1 * D_800D2120_main + arg0->unk98->unk08;

    if (!(arg0->unk98->unk08 >= arg0->unk98->unk04)) {
        return;
    }

    if (arg0->unk98->unk02 & 2) {
        arg0->unk98->unk08 = 0;
    } else {
        arg0->unk98->unk08 = arg0->unk98->unk04;
    }
}

void func_8002FB98_main(HmfData *arg0, f32 arg1) {
    arg0->unkA0 = arg1 * D_800D2120_main + arg0->unkA0;

    if (arg0->unkA0 >= arg0->unk8C->unk02) {
        if (D_800A1160_main != 0) {
            arg0->unkA0 = 0;
        } else {
            arg0->unkA0 = arg0->unk8C->unk02;
        }
    }
}

void func_8002FC14_main(HmfData *arg0, f32 arg1) {
    arg0->unkA0 = arg0->unkA0 - arg1 * D_800D2120_main;

    if (arg0->unkA0 < 0) {
        if (D_800A1160_main != 0) {
            arg0->unkA0 = arg0->unk8C->unk02;
        } else {
            arg0->unkA0 = 0;
        }
    }
}

f32 func_8002FC7C_main(HmfModelData_Unk64_Unk8C_Struct *arg0, u16 flags, f32 frame, f32 start, f32 speed) {
    speed *= D_800A0A78_main * D_800D2120_main;
    if (!(flags & 9)) {
        if (!(flags & 4)) {
            frame += speed;
            if (frame >= arg0->unk02) {
                if (flags & 2) {
                    return start;
                } else {
                    return arg0->unk02;
                }
            }
        } else {
            frame -= speed;
            if (frame < start) {
                if (flags & 2) {
                    return arg0->unk02 - speed;
                } else {
                    return start;
                }
            }
        }
    }
    return frame;
}

void func_8002FD48_main(HmfData *arg0) {
    arg0->unkA0 = 0;
}

void func_8002FD50_main(HmfData *arg0) {
    arg0->unkA0 = arg0->unk8C->unk02 - 1;
}

s16 func_8002FD70_main(HmfData *arg0) {
    return arg0->unkA0;
}

void func_8002FD8C_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4) {
    func_8002FE08_main(arg0, arg1, arg2, arg3, arg4, 0x8000);
}

void func_8002FDCC_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4) {
    func_8002FE08_main(arg0, arg1, arg2, arg3, arg4, 0);
}

INCLUDE_ASM("asm/nonmatchings/22EB0", func_8002FE08_main);

void func_80030030_main(f32 arg0) {
    D_800D2120_main = arg0;
}
