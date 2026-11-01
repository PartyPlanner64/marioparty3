#include "overlays/minigame.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "variables.h"
#include "include_asm.h"
#include "game/util.h"

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E4A80_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E4A90_minigame);

void func_800E4BA4_minigame(s32 arg0) {
    f32 unk40;

    if (arg0 & 0xFF) {
        unk40 = HmfModelData[arg0 & 0xFF].motTime;
        if (D_800CCF58_main[HmfModelData[arg0 & 0xFF].motId].unk02 <= unk40) {
            func_8001C258_main((u8)arg0, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E4C2C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E4C88_minigame);

void func_800E4D9C_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    s16 *motion = arg0->motion;
    s16 flag = (data->unkD8.unk00 & 1) ? 2 : 0;

    if (data->unkE8[22].unk00 & 4) {
        s16 anim = motion[22] & 0x3FFF;
        Hu3DMotionShapeSet(arg0->model[0], anim, flag);
    } else {
        s16 anim = HmfModelData[arg0->motion[22] & 0x3FFF].motId;
        Hu3DMotionShapeSet(arg0->model[0], anim, flag);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E4E30_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E5138_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E561C_minigame);

void func_800E5638_minigame(func_800E5638_minigame_UnkD8_ObjData *arg0, u16 arg1, u16 arg2, u16 arg3,
                            s16 arg4) {
    arg0->unk00 = arg1;
    arg0->unk02 = arg2;
    arg0->unk08 = 0;
    arg0->unk0C = arg3;
    arg0->unk06 = arg4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E5664_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E567C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E5690_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E5798_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E5848_minigame);

void func_800E58B4_minigame(omObjData *arg0, s32 arg1, s32 arg2) {
    arg0->motion[arg2] = arg0->motion[arg1];
}

void func_800E58D4_minigame(omObjData *arg0, s32 arg1, s16 arg2, s16 arg3) {
    func_800E1BA8_minigame_ObjData *temp_a1;
    func_800E1BA8_minigame_UnkE8_ObjData *temp_v0_2;

    temp_a1 = (func_800E1BA8_minigame_ObjData *)arg0->data;
    temp_v0_2 = &temp_a1->unkE8[arg1];
    temp_v0_2->unk00 = arg2;
    temp_v0_2->unk02 = arg3;
}

void func_800E58F8_minigame(omObjData *arg0, s32 arg1, s32 arg2) {
    func_800E1BA8_minigame_ObjData *temp_t2;
    func_800E1BA8_minigame_UnkE8_ObjData *temp_a3;
    func_800E1BA8_minigame_UnkE8_ObjData *temp_v1;
    s32 temp_t1;
    u16 temp_a0;
    u16 temp_a1;
    u16 temp_a2;

    temp_t2 = (func_800E1BA8_minigame_ObjData *)arg0->data;
    temp_t1 = arg0->motion[arg1];
    arg0->motion[arg1] = arg0->motion[arg2];
    arg0->motion[arg2] = temp_t1;
    temp_a3 = &temp_t2->unkE8[arg1];
    temp_v1 = &temp_t2->unkE8[arg2];
    temp_a0 = temp_a3->unk02;
    temp_a1 = temp_a3->unk00;
    temp_a2 = temp_a3->unk04;
    temp_a3->unk02 = temp_v1->unk02;
    temp_a3->unk00 = temp_v1->unk00;
    temp_a3->unk04 = temp_v1->unk04;
    temp_v1->unk02 = temp_a0;
    temp_v1->unk00 = temp_a1;
    temp_v1->unk04 = temp_a2;
}

void func_800E5978_minigame(omObjData *arg0, u16 arg1, s32 arg2, u16 arg3, u16 arg4) {
    func_800E1BA8_minigame_ObjData *data;
    func_800E1BA8_minigame_UnkE8_ObjData *entry;
    s16 modelId;

    modelId = func_8000B13C_main(arg2);
    if (modelId < 0) {
        return;
    }
    data = arg0->data;
    arg0->motion[arg1] = modelId;
    entry = &data->unkE8[arg1];
    entry->unk00 = arg3;
    entry->unk02 = arg4;
}

void func_800E5A00_minigame(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, u16 arg4) {
    func_800E1BA8_minigame_ObjData *temp_a1;
    func_800E1BA8_minigame_UnkE8_ObjData *temp_v0_2;
    s16 temp_v0;

    temp_v0 = func_8001F1FC_main(DataRead(arg2), 0x18);
    if (temp_v0 < 0) {
        return;
    }
    temp_a1 = (func_800E1BA8_minigame_ObjData *)arg0->data;
    arg0->motion[arg1] = temp_v0;
    temp_v0_2 = &temp_a1->unkE8[arg1];
    temp_v0_2->unk00 = arg3 | 4;
    temp_v0_2->unk02 = arg4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E5A98_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E5B08_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B7600", func_800E5C18_minigame);
