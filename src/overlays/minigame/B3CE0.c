#include "overlays/minigame.h"
#include "types.h"
#include "gcc/memory.h"
#include "game/gamework_data.h"
#include "game/util.h"
#include "game/hu3d.h"
#include "game/hmfcoll.h"
#include "game/hmfdraw.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"
#include "game/hmfanim.h"
#include "game/audio.h"
#include "game/mallocblock.h"
#include "include_asm.h"
#include "game/pad.h"
#include "math.h"

extern s32 D_800EB730_minigame;
extern u8 D_800EB734_minigame;
extern u8 D_800EB739_minigame;
extern u8 D_800EB73A_minigame;
extern f32 D_800EB740_minigame;
extern f32 D_800EB74C_minigame;
extern f32 D_800EB750_minigame;
extern f32 D_800EB75C_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EB770_minigame;
extern f32 D_800EB778_minigame;
extern s16 D_800EB784_minigame[][14];
extern s16 D_800EBE10_minigame[];
extern s32 D_800EB820_minigame[][7];
extern s32 D_800A178C_main[][6];
extern u8 D_800D2008_main;
extern s32 D_800EB800_minigame[];
extern s16 D_800EBE18_minigame[];
extern u8 D_800EBE20_minigame[];
extern s8 D_800EC1BA_minigame[];
extern s8 D_800EC282_minigame[];
extern s16 D_800EC28A_minigame[];
extern u8 D_800EC5DC_minigame[];

void func_800E1160_minigame(omObjData *arg0, u16 arg1, u16 player, s32 arg3, s32 arg4, f32 arg5) {
    s32 dataNum = D_800EB800_minigame[GwPlayer[player].chr];
    s16 anim;

    arg0->model[arg1] = func_8000B108_main(arg3, arg4 & ~0x11);
    anim = func_80017790_main(arg0->model[arg1], 0, GwPlayer[player].chr, dataNum);
    func_80017954_main(arg0->model[arg1], 0, GwPlayer[player].chr, anim);
}

void func_800E123C_minigame(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, f32 arg4) {
    s16 model = func_8000B108_main(arg2, arg3);

    arg0->model[arg1] = model;
    func_8001F450_main(arg0->model[0], model, arg4);
}

void func_800E12B0_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk3C = func_800202A8_main(arg1);
}

void func_800E12E0_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk40 = arg1;
}

void func_800E12EC_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk38 = arg1;
}

void func_800E12F8_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk44 = arg1;
}

void func_800E1304_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk08 = arg1;
}

void func_800E1310_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk0C = arg1;
}

void func_800E131C_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk10 = arg1;
}

void func_800E1328_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk48 = arg1;
}

void func_800E1334_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk34 = arg1;
}

void func_800E1340_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk64 = arg1;
}

void func_800E134C_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk68 = arg1;
}

void func_800E1358_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk6C = arg1;
}

void func_800E1364_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk70 = arg1;
}

void func_800E1370_minigame(omObjData *arg0, s32 arg1, f32 arg2) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unk06 = (arg1 & 0xFF) | temp_data->unk06;
    if (arg1 & 2) {
        temp_data->unk14 = arg2;
    }
}

void func_800E139C_minigame(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x8;
    temp_v0->unk14 = arg1;
    temp_v0->unkA0 = arg2;
    temp_v0->unkA4 = arg3;
    temp_v0->unkA8.f = arg4;
    temp_v0->unkAC = arg5;
}

void func_800E13CC_minigame(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x10;
    temp_v0->unk14 = arg1;
    temp_v0->unk98 = arg2;
    temp_v0->unkA0 = arg3;
    temp_v0->unkA4 = arg4;
    temp_v0->unkA8.f = arg5;
    temp_v0->unkAC = arg6;
}

void func_800E1404_minigame(omObjData *arg0, f32 arg1, f32 arg2) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x20;
    temp_v0->unk14 = arg1;
    temp_v0->unk9C = arg2;
}

void func_800E1420_minigame(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x40;
    temp_v0->unk14 = arg1;
    temp_v0->unk98 = arg2;
    temp_v0->unk9C = arg3;
}

void func_800E1440_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x80;
}

void func_800E1454_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x100;
}

void func_800E1468_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x200;
}

void func_800E147C_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x400;
}

void func_800E1490_minigame(s32 arg0) {
    D_800EB734_minigame = arg0;
}

void func_800E149C_minigame(omObjData *arg0, u8 arg1, s8 arg2) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    temp_v0->unk00[arg1] = arg2;
}

void func_800E14B0_minigame(omObjData *arg0, s32 arg1, s32 arg2) {
    if (!(arg2 & 0xFF)) {
        func_8001C258_main(arg0->model[arg1 & 0xFF], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        func_8001C258_main(arg0->model[arg1 & 0xFF], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

s32 func_800E1510_minigame(s8 arg0) {
    D_800EC1C0_minigame_ObjData *data;
    s32 i;

    if (arg0 < 0) {
        return 0;
    }
    for (i = 0; i < D_800EBE28_minigame; i++) {
        data = D_800EC1C0_minigame[i]->data;
        if (data->unk04 == arg0) {
            if (data->unk06 & 0x200) {
                return 0;
            }
            break;
        }
    }
    return 1;
}

void func_800E1594_minigame(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    temp_v0->unk53[2] = SprModelRead(arg1, arg2, arg3);
    arg0->model[0] = D_800CBB60_main[(u8)temp_v0->unk53[2]].modelId;
    func_8001C2FC_main(arg0->model[0], 0x70000000, 0x70000000);
}

void func_800E1610_minigame(omObjData *arg0, u8 arg1, s32 arg2, s32 arg3, char *arg4, s32 arg5) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    u8 anim;
    HmfModel *model;

    arg0->model[arg1] = func_8000B0D4_main(arg2, arg5);
    model = &HmfModelData[arg0->model[arg1]];
    anim = HmfAnimRead(model->hmf, arg3, arg4);
    data->unk21[arg1] = anim;
    Hu3DModelRemakeStatic(arg0->model[arg1]);
    func_80032FC0_main(anim, 1, 1);
    func_80032FC0_main(anim, 2, 2);
    Hu3DModelScaleSet(arg0->model[arg1], 2.0f, 2.0f, 2.0f);
}

void func_800E1718_minigame(omObjData *arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    u16 sprite = SprModelRead(arg2, arg3, arg4);

    arg0->model[arg1] = D_800CBB60_main[(u8)sprite].modelId;
    data->unk21[arg1] = sprite;
    func_8001C2FC_main(D_800CBB60_main[(u8)sprite].modelId, 0x70000000, 0x70000000);
    func_800146DC_main((u8)sprite, 4, 4);
}

void func_800E17D4_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    arg0->trans.x = x;
    arg0->trans.y = y;
    arg0->trans.z = z;
}

void func_800E17E4_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    arg0->rot.x = x;
    arg0->rot.y = y;
    arg0->rot.z = z;
}

void func_800E17F4_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    arg0->scale.x = x;
    arg0->scale.y = y;
    arg0->scale.z = z;
}

void func_800E1804_minigame(void) {
    D_800EB730_minigame = 0;
}

void func_800E1810_minigame(void) {
    D_800EB730_minigame = 2;
}

void func_800E1820_minigame(void) {
    D_800EB730_minigame = 3;
}

void func_800E1830_minigame(void) {
    D_800EB730_minigame = 1;
}

void func_800E1840_minigame(void) {
    D_800EBE24_minigame = D_800EB730_minigame;
}

s32 func_800E1854_minigame(s32 arg0) {
    s32 i;

    for (i = 0; i < D_800EBE28_minigame; i++) {
        /* Raw byte at 0x5F, inside omObjData's trailing data pointer field. */
        if (((u8 *)D_800EC1C0_minigame[i])[0x5F] == arg0) {
            return i;
        }
    }
    return D_800EB734_minigame;
}

void func_800E18B4_minigame(void) {
    s8 temp_s8;

    memset(&temp_s8, 0, sizeof(temp_s8));
}

void func_800E18D8_minigame(void) {
    D_800EB73C_minigame = 15.0f;
    D_800EB740_minigame = 0.5f;
    D_800EB744_minigame = 1.45f;
    D_800EB748_minigame = 0.15f;
    D_800EB74C_minigame = 7.0f;
    D_800EB750_minigame = 30.0f;
    D_800EB778_minigame = 0.5f;
    D_800EB75C_minigame = 3.3333333f;
    D_800EB760_minigame = 18.0f;
    D_800EB764_minigame = 13.5f;
    D_800EB768_minigame = 9.0f;
    D_800EB76C_minigame = 4.5f;
    D_800EB770_minigame = 0.0f;
    D_800EB774_minigame = 1.6f;
    D_800EB77C_minigame = 0.14500001f;
    D_800EB735_minigame = 1;
    D_800EB73A_minigame = 0;
}

void func_800E19E4_minigame(s32 arg0) {
    D_800EB73A_minigame = arg0;
}

void func_800E19F0_minigame(s8 arg0) {
    D_800EB739_minigame = arg0;
}

void func_800E19FC_minigame(func_800E1BA8_minigame_ObjData *arg0, s32 arg1) {
    s16 sound = D_800EB784_minigame[arg0->unk59][arg1];

    if (sound >= 0) {
        if (arg0->unkC4 != arg1) {
            arg0->unkC5 = func_8004AC98_main(sound, arg0->unk59);
            arg0->unkC4 = arg1;
            D_800EBE10_minigame[arg0->unk59] = sound;
        }
    } else {
        arg0->unkC4 = -1;
    }
}

void func_800E1A9C_minigame(func_800E1BA8_minigame_ObjData *arg0, s32 arg1) {
    s16 sound = D_800EB784_minigame[arg0->unk59][arg1];

    if (sound >= 0) {
        if (arg0->unkC4 != arg1) {
            arg0->unkC5 = func_8004AC98_main(sound, arg0->unk59);
            arg0->unkC4 = arg1;
            D_800EBE10_minigame[arg0->unk59] = sound;
        }
    } else {
        arg0->unkC4 = -1;
    }
}

void func_800E1B3C_minigame(void) {
    s32 i;

    for (i = 0; i < D_800EC280_minigame; i++) {
        HuAudFXStop(OM_GET_DATA_PTR(D_800EC598_minigame[i], func_800E1BA8_minigame_ObjData)->unkC5);
    }
}

void func_800E1BA8_minigame(omObjData *arg0, u32 arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5) {
    func_800E1BA8_minigame_ObjData *temp_s0;
    s32 var_a0;

    for (var_a0 = 0; var_a0 < arg0->mdlcnt; var_a0++) {
        arg0->model[var_a0] = 0;
    }
    arg0->data = HuMemAllocTag(sizeof(func_800E1BA8_minigame_ObjData), TAG_OVERLAY);
    memset(arg0->data, 0, sizeof(func_800E1BA8_minigame_ObjData));
    temp_s0 = arg0->data;
    temp_s0->unkE8 = HuMemAllocTag(arg0->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), TAG_OVERLAY);
    if (D_800EB73A_minigame == 1) {
        func_800E1160_minigame(arg0, 0, arg3, arg1 | arg2, arg4, 750.0f);
    } else {
        arg0->model[0] = func_8000B108_main(arg1 | arg2, arg4);
    }
    arg0->model[1] = func_8000B0D4_main((D_800EB739_minigame != 0) ? 9 : 0, arg5);
    func_800E3584_minigame(arg0->model[1]);
    for (var_a0 = 0; var_a0 < arg0->mtncnt; var_a0++) {
        arg0->motion[var_a0] = -1;
    }
    for (var_a0 = 0; var_a0 < 21; var_a0++) {
        temp_s0->unk104[var_a0] = 0;
    }
    for (var_a0 = 0; var_a0 < arg0->mtncnt; var_a0++) {
        temp_s0->unkE8[var_a0].unk00 = 0;
        temp_s0->unkE8[var_a0].unk02 = 0;
        temp_s0->unkE8[var_a0].unk04 = -1;
        temp_s0->unkE8[var_a0].unk08 = -1;
    }
    temp_s0->unk57 = GwPlayer[arg3].pad;
    arg0->func = func_800DDD94_minigame;
    temp_s0->unk52 = 0;
    temp_s0->unkB4 = 1.0f;
    temp_s0->unk8C = 65536.0f;
    temp_s0->unkD0 = 0xFFFF;
    temp_s0->unk4C = 0.5f;
    temp_s0->unkCC = 1.0f;
    temp_s0->unk60 = 0.0f;
    func_800E1328_minigame(arg0, 60.0f);
    func_800E1334_minigame(arg0, 150.0f);
    func_800E1340_minigame(arg0, 20.0f);
    func_800E134C_minigame(arg0, 30.0f);
    func_800E1358_minigame(arg0, 50.0f);
    func_800E1364_minigame(arg0, 40.0f);
    func_800E12EC_minigame(arg0, 1000.0f);
    temp_s0->unk9C = temp_s0->unkA0 = temp_s0->unkA4 = 0.0f;
    temp_s0->unk59 = (s8)arg3;
    temp_s0->unkC3 = -1;
    temp_s0->unkC4 = -1;
    temp_s0->unkB0 = 1.0f;
    switch (arg1 >> 16) {
        case 6:
            temp_s0->unkAC = 0.7f;
            break;
        case 4:
            temp_s0->unkAC = 0.9f;
            break;
        case 5:
            temp_s0->unkAC = 0.8f;
            break;
        default:
            temp_s0->unkAC = 1.0f;
            break;
    }
    var_a0 = GwPlayer[arg3].chr + 1;
    D_800EB784_minigame[temp_s0->unk59][0] = var_a0 + 0x1F;
    D_800EB784_minigame[temp_s0->unk59][1] = var_a0 + 0x28;
    D_800EB784_minigame[temp_s0->unk59][2] = var_a0 + 0x43;
    D_800EB784_minigame[temp_s0->unk59][3] = var_a0 + 0x3A;
    D_800EB784_minigame[temp_s0->unk59][4] = var_a0 + 0x31;
    D_800EB784_minigame[temp_s0->unk59][5] = var_a0 + 0x4C;
    D_800EB784_minigame[temp_s0->unk59][6] = var_a0 + 0x55;
    D_800EB784_minigame[temp_s0->unk59][7] = var_a0 + 0x9D;
    D_800EB784_minigame[temp_s0->unk59][8] = var_a0 + 0x94;
    D_800EB784_minigame[temp_s0->unk59][9] = var_a0 + 0xA6;
    D_800EB784_minigame[temp_s0->unk59][10] = var_a0 + 0x5E;
    D_800EB784_minigame[temp_s0->unk59][11] = var_a0 + 0x67;
    D_800EB784_minigame[temp_s0->unk59][12] = var_a0 + 0xAF;
    D_800EB784_minigame[temp_s0->unk59][13] = var_a0 + 0xB8;
}

void func_800E210C_minigame(omObjData *arg0, s16 arg1, s16 arg2) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;
    s32 chr;
    s32 model;

    temp_data->unk5A = arg1;
    temp_data->unk5B = arg2;
    chr = GwPlayer[temp_data->unk59].chr;
    model = D_800A178C_main[chr][0];
    func_80017790_main(arg1, arg2, chr, model | func_80017B6C_main(chr, arg2, 0));
}

void func_800E21B8_minigame(omObjData *arg0, s32 arg1, s32 arg2) {
    func_800E1BA8_minigame_ObjData *temp_data = arg0->data;

    temp_data->unkF2[arg2] =
        func_80017AD8_main(D_800EB820_minigame[GwPlayer[arg1].chr][arg2] | D_800A178C_main[GwPlayer[0].chr][0]);
}

#ifdef NON_MATCHING
s32 func_800E2250_minigame(omObjData *arg0, s16 arg1, s16 arg2) {
    func_800E1BA8_minigame_ObjData *temp_a3 = arg0->data;
    s32 value = (arg1 << 16) | (arg2 & 0xFFFF);
    s16 sumHi;
    s16 sumLo;
    u8 i;

    temp_a3->unk74[temp_a3->unk58++] = value;
    if (temp_a3->unk58 >= 6) {
        temp_a3->unk58 = 0;
    }
    sumLo = 0;
    sumHi = 0;
    for (i = 0; i < 6; i++) {
        sumHi += temp_a3->unk74[i] >> 16;
        sumLo += temp_a3->unk74[i] & 0xFFFF;
    }
    sumHi /= 6;
    sumLo /= 6;
    return (sumHi << 16) | (sumLo & 0xFFFF);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B3CE0", func_800E2250_minigame);
#endif

void func_800E2308_minigame(s16 *arg0, s16 *arg1) {
    Vec vec;
    f32 x = *arg0;
    f32 z = *arg1;

    if (HuSqrtf(x * x + z * z) > 60.0f) {
        vec.x = x;
        vec.y = 0.0f;
        vec.z = z;
        func_800202FC_main(&vec);
        *arg0 = vec.x * 60.0f;
        *arg1 = vec.z * 60.0f;
    }
}

void func_800E23E0_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;
    s32 var_a0;

    for (var_a0 = 0; var_a0 < 6; var_a0++) {
        temp_v0->unk74[var_a0] = 0;
    }
}

s16 func_800E240C_minigame(s16 idx, s16 arg1, s8 x, s8 y) {
    s16 mult = 1;
    s16 angle;
    s16 diff;
    s16 dir;

    if (x == 0 && y == 0) {
        return 0;
    }
    angle = atan2df(y, x);
    if (angle < 0) {
        angle += 360;
    }
    angle /= 90;
    if (angle == D_800EBE20_minigame[idx]) {
        if (++D_800EC282_minigame[idx] > arg1) {
            D_800EC282_minigame[idx] = arg1;
            D_800EC1BA_minigame[idx] = 0;
            D_800EC5DC_minigame[idx] = angle;
            D_800EBE18_minigame[idx] = 0;
            return 0;
        }
        D_800EBE18_minigame[idx]++;
        return D_800EC1BA_minigame[idx];
    }
    D_800EBE18_minigame[idx]++;
    D_800EC282_minigame[idx] = 0;
    if (D_800EC5DC_minigame[idx] == angle) {
        mult = 2;
        D_800EC28A_minigame[idx] = D_800EBE18_minigame[idx];
        D_800EBE18_minigame[idx] = 0;
    }
    diff = angle - D_800EBE20_minigame[idx];
    if (diff >= 0 ? diff == 3 : -diff == 3) {
        diff = -diff;
    }
    dir = (diff < 0) ? -1 : 1;
    if (dir != 0 && dir != D_800EC1BA_minigame[idx]) {
        D_800EC1BA_minigame[idx] = dir;
        D_800EBE20_minigame[idx] = angle;
        D_800EC282_minigame[idx] = 0;
        D_800EC5DC_minigame[idx] = angle;
        D_800EBE18_minigame[idx] = 0;
        return 0;
    }
    D_800EBE18_minigame[idx]++;
    if (((D_800EBE20_minigame[idx] + D_800EC1BA_minigame[idx]) & 3) == angle) {
        D_800EBE20_minigame[idx] = angle;
        return D_800EC1BA_minigame[idx] * mult;
    }
    D_800EC1BA_minigame[idx] = dir;
    D_800EBE20_minigame[idx] = angle;
    D_800EC282_minigame[idx] = 0;
    D_800EBE18_minigame[idx] = 0;
    return 0;
}

void func_800E2780_minigame(omObjData *obj) {
    s32 model = obj->model[0];
    D_800EC1C0_minigame_ObjData *data = obj->data;

    if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f) {
        func_80088800_main(data->unk18, obj->trans.x, obj->trans.y, obj->trans.z);
    } else {
        func_8008A070_main(data->unk18);
    }
    if (obj->rot.x != 0.0f || obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
        mtxRotCat(data->unk18, obj->rot.x, obj->rot.y, obj->rot.z);
    }
    if (data->unk06 & 0x100) {
        guMtxCatF(HmfModelData[model].mtx, data->unk18, data->unk18);
    }
    func_80018F18_main(data->unk18, data->unk58);
}

void func_800E28BC_minigame(HuMtx4F mtx, HuMtx4F result, Vec *pos, omObjData *obj) {
    D_800EC1C0_minigame_ObjData *data = obj->data;
    s32 model = obj->model[0];
    f32 rotX = obj->rot.x;
    f32 rotY = obj->rot.y;
    f32 rotZ = obj->rot.z;
    f32 transX = obj->trans.x;
    f32 transY = obj->trans.y;
    f32 transZ = obj->trans.z;
    f32 x = pos->x;
    f32 y = pos->y;
    f32 z = pos->z;

    if (data->unk06 & 0x80) {
        func_8002367C_main(mtx, data->unk18);
        func_8002367C_main(result, data->unk58);
    } else {
        if (transX != 0.0f || transY != 0.0f || transZ != 0.0f) {
            func_80088800_main(mtx, transX, transY, transZ);
        } else {
            func_8008A070_main(mtx);
        }
        if (rotX != 0.0f || rotY != 0.0f || rotZ != 0.0f) {
            mtxRotCat(mtx, rotX, rotY, rotZ);
        }
        if (data->unk06 & 0x100) {
            guMtxCatF(HmfModelData[model].mtx, mtx, mtx);
        }
        func_80018F18_main(mtx, result);
    }
    pos->x = x * result[0][0] + y * result[1][0] + z * result[2][0] + result[3][0];
    pos->y = x * result[0][1] + y * result[1][1] + z * result[2][1] + result[3][1];
    pos->z = x * result[0][2] + y * result[1][2] + z * result[2][2] + result[3][2];
}

void func_800E2B58_minigame(HuMtx4F mtx, Vec *arg1) {
    f32 x = arg1->x;
    f32 y = arg1->y;
    f32 z = arg1->z;

    arg1->x = x * mtx[0][0] + y * mtx[1][0] + z * mtx[2][0];
    arg1->y = x * mtx[0][1] + y * mtx[1][1] + z * mtx[2][1];
    arg1->z = x * mtx[0][2] + y * mtx[1][2] + z * mtx[2][2];
}

void func_800E2BD4_minigame(HuMtx4F mtx, Vec *arg1) {
    f32 x = arg1->x;
    f32 y = arg1->y;
    f32 z = arg1->z;

    arg1->x = x * mtx[0][0] + y * mtx[1][0] + z * mtx[2][0] + mtx[3][0];
    arg1->y = x * mtx[0][1] + y * mtx[1][1] + z * mtx[2][1] + mtx[3][1];
    arg1->z = x * mtx[0][2] + y * mtx[1][2] + z * mtx[2][2] + mtx[3][2];
}

void func_800E2C68_minigame(HuMtx4F mtx, Vec *arg1) {
    f32 x = arg1->x;
    f32 y = arg1->y;
    f32 z = arg1->z;

    arg1->y = x * mtx[0][1] + y * mtx[1][1] + z * mtx[2][1] + mtx[3][1];
}

void func_800E2CA4_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    omObjData *item;
    A96F0_ObjData *itemData;

    if (data->unk50 & 0x10) {
        item = data->unkC8;
        itemData = item->data;
        if (data->unk104[19] != NULL && data->unk104[19](arg0, item) == 1) {
            return;
        }
        data->unk50 &= ~0x150;
        itemData->unk50 &= ~0x10;
        func_8001C258_main(item->model[0], 0x4000, HU3D_ATTR_NONE);
        HmfModelData[arg0->model[0]].motIdShape = 0xFF;
        if (item->model[1] != 0) {
            func_8001C258_main(item->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        func_800D853C_minigame(arg0, item);
        data->unkC8 = NULL;
        data->unkB4 = 1.0f;
    }
}

s32 func_800E2DA4_minigame(omObjData *arg0, omObjData *item) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    A96F0_ObjData *itemData = item->data;

    if (!(itemData->unk50 & 0x20)) {
        return 0;
    }
    if (itemData->unk50 & 0x10) {
        return 0;
    }
    if (data->unk50 & 0x10) {
        return 0;
    }
    data->unk50 |= 0x110;
    itemData->unk50 |= 0x10;
    if (itemData->unk50 & 0x40) {
        data->unk50 |= 0x40;
    }
    data->unkC8 = item;
    itemData->unk80 = arg0;
    Hu3DModelHookSet(item->model[0], arg0->model[0], "item_hook");
    func_8001C258_main(item->model[0], 0x4000, 0x4000);
    data->unkB4 = itemData->unk74;
    if (item->model[1] != 0) {
        func_8001C258_main(item->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    return 1;
}

void func_800E2E98_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    HmfModelData[arg0->model[0]].motIdShape = 0xFF;
    temp_v0->unk50 &= 0xFEFF;
}

f32 func_800E2ED4_minigame(f32 x1, f32 z1, f32 x2, f32 z2) {
    Vec a;
    Vec b;

    a.x = x1;
    a.y = 0.0f;
    a.z = z1;
    func_800202FC_main(&a);
    b.x = x2;
    b.y = 0.0f;
    b.z = z2;
    func_800202FC_main(&b);
    return HuVecDot3F(&b, &a);
}

s32 func_800E2F40_minigame(HmfModelData_Unk64_Unk60_Struct *obj, Vec *pos) {
    f32 minX = obj->boundsMin[0];
    f32 minZ = obj->boundsMin[2];
    f32 maxX = obj->boundsMax[0];
    f32 maxZ = obj->boundsMax[2];

    return minX <= pos->x && minZ <= pos->z && pos->x <= maxX && pos->z <= maxZ;
}

s32 func_800E2FD8_minigame(HmfModelData_Unk64_Unk60_Struct *obj, Vec *pos, f32 margin) {
    f32 x;
    f32 z;
    f32 minX;
    f32 maxX;
    f32 maxZ;
    f32 minZ;

    x = pos->x;
    z = pos->z;
    minX = obj->boundsMin[0] - margin;
    minZ = obj->boundsMin[2] - margin;
    maxX = obj->boundsMax[0] + margin;
    maxZ = obj->boundsMax[2] + margin;
    if (minX <= x && minZ <= z && x <= maxX && z <= maxZ) {
        return 1;
    }
    return 0;
}

s32 func_800E30B8_minigame(Vec *pos, D_800EC1C0_minigame_ObjData *data) {
    f32 x;
    f32 z;

    if (!(data->unk06 & 0x50)) {
        return 1;
    }
    x = pos->x;
    z = pos->z;
    if (data->unk06 & 0x10) {
        if (data->unkA0 <= x && x <= data->unkA8 && data->unkA4 <= z && z <= data->unkAC) {
            return 1;
        }
    } else if (HuSqrtf(x * x + z * z) <= data->unk9C) {
        return 1;
    }
    return 0;
}

void func_800E317C_minigame(omObjData *arg0, f32 x, f32 z) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    s16 stickX;
    s16 stickY;
    s32 avg;

    if (data->unk5C & 0x200) {
        data->unk4C = 0.7f;
    } else {
        data->unk4C = 0.6f;
    }
    func_800E5690_minigame(arg0, 6);
    if (abs(D_800CBB6E_main[data->unk57]) >= 9 || abs(D_800D20A1_main[data->unk57]) >= 9) {
        stickX = D_800CBB6E_main[data->unk57];
        stickY = D_800D20A1_main[data->unk57];
        if (stickX > 60) {
            stickX = 60;
        }
        if (stickY > 60) {
            stickY = 60;
        }
        if (stickX < -60) {
            stickX = -60;
        }
        if (stickY < -60) {
            stickY = -60;
        }
        func_800E2308_minigame(&stickX, &stickY);
        func_800E2250_minigame(arg0, stickX, stickY);
        func_800E2250_minigame(arg0, stickX, stickY);
        func_800E2250_minigame(arg0, stickX, stickY);
        func_800E2250_minigame(arg0, stickX, stickY);
        func_800E2250_minigame(arg0, stickX, stickY);
        avg = func_800E2250_minigame(arg0, stickX, stickY);
        stickX = avg >> 16;
        stickY = avg;
        data->unk3C = atan2df(stickX, -stickY) + data->unk60;
        data->unk40 = D_800EB760_minigame;
    } else if (func_800E2ED4_minigame(sindf(data->unk3C), cosdf(data->unk3C), x, z) < 0.0f) {
        data->unk40 = D_800EB760_minigame;
    } else {
        data->unk40 = -D_800EB760_minigame;
    }
    data->unk38 = -D_800EB744_minigame * 0.9f;
    data->unk50 |= 8;
}

void func_800E341C_minigame(func_800E1BA8_minigame_ObjData *arg0, f32 x, f32 z) {
    if (0.0f <= func_800E2ED4_minigame(sindf(arg0->unk3C), cosdf(arg0->unk3C), x, z)) {
        arg0->unk40 = D_800EB764_minigame;
    } else {
        arg0->unk40 = -D_800EB764_minigame;
    }
    arg0->unk50 |= 8;
    func_800E19FC_minigame(arg0, 7);
}

void func_800E34D8_minigame(omObjData *arg0, omObjData *arg1) {
    func_800E1BA8_minigame_ObjData *data1 = arg1->data;

    func_800E341C_minigame(arg0->data, arg0->trans.x - arg1->trans.x, arg0->trans.z - arg1->trans.z);
    func_800E341C_minigame(data1, arg1->trans.x - arg0->trans.x, arg1->trans.z - arg0->trans.z);
}

void func_800E3568_minigame(func_800E1BA8_minigame_ObjData *arg0, s32 index, s32 (*func)()) {
    if (index < 21) {
        arg0->unk104[index] = func;
    }
}

void func_800E3584_minigame(s16 model) {
    HmfData *hmf;
    s16 i;

    func_8001C954_main(model);
    hmf = HmfModelData[model].hmf;
    for (i = 0; i < D_800D1FF0_main; i++) {
        bcopy(hmf->unk40, hmf->unk44[i], hmf->unk18 * sizeof(Vtx));
    }
}

void func_800E3628_minigame(s16 model, Vec *normal) {
    HmfModel *hmfModel = &HmfModelData[model];
    HmfData *hmf = hmfModel->hmf;
    Vtx *vtx = hmf->unk44[D_800D2008_main];
    Vtx *src = hmf->unk40;
    f32 dist;
    f32 x;
    f32 y;
    f32 z;
    f32 scale;
    Vec unused;
    s16 i;

    dist = normal->x * hmfModel->pos.x + normal->y * hmfModel->pos.y + normal->z * hmfModel->pos.z;
    for (i = 0; i < hmfModel->hmf->unk18; vtx++, i++, src++) {
        x = vtx->v.ob[0] + hmfModel->pos.x;
        z = vtx->v.ob[2] + hmfModel->pos.z;
        y = dist - x * normal->x - z * normal->z;
        y /= normal->y;
        vtx->v.ob[1] = y - hmfModel->pos.y + 0.5f;
        x = src->v.ob[0];
        y = vtx->v.ob[1];
        z = src->v.ob[2];
        scale = (f32)(src->v.ob[0] * src->v.ob[0] + vtx->v.ob[2] * vtx->v.ob[2]) / (x * x + y * y + z * z);
        vtx->v.ob[0] = x * scale;
        vtx->v.ob[1] = vtx->v.ob[1] * scale;
        vtx->v.ob[2] = src->v.ob[2] * scale;
    }
}
