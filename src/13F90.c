/* This file does not include common.h: the original source appears to have called rand8() without a
 * prototype in scope (implicit int return, no 0xFF mask at the call site in func_80013390_main). */
#include "ultra64.h"
#include "types.h"
#include "game/camera.h"
#include "game/hmfman.h"
#include "include_asm.h"
#include "mallocblock.h"

extern u8 D_800CD6A6_main;
extern u8 D_800D2008_main;

void func_80018F18_main(HuMtx4F in, HuMtx4F out);
s16 func_8002C834_main(HmfData *hmf, char *name);
void func_80013D44_main(s16 model);
void func_80013D4C_main(s16 model);
void func_80013FB4_main(s16 model);

#ifdef NON_MATCHING
/* rand8() mask now matches via implicit declaration; remaining diff is a2/a3 swaps (swap tmp, group/j loop) */
void func_80013390_main(s16 model, s16 type, char *name, void (*func)(s16)) {
    HmfModel *modelP = &HmfModelData[model];
    HmfData *hmf = modelP->hmf;
    HmfModelData_UnkBC_Struct *bc;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    HmfVertexGroup *group;
    s16 *order;
    s32 first;
    s32 count;
    s16 i;
    s16 j;
    Vtx *vert;
    s16 a;
    s16 b;
    s16 tmp;
    s16 side;
    s16 index;
    f32 angle1;
    f32 angle2;
    f32 sinAngle1;

    func_8001C258_main(model, 0x1000000, 0x1000000);
    bc = HuMemAllocTag(sizeof(HmfModelData_UnkBC_Struct), hmf->unk0E + 1);
    modelP->unkBC = bc;
    particle = HuMemAllocTag(hmf->unk1A * sizeof(HmfModelData_UnkBC_Unk58_Struct), hmf->unk0E + 1);
    bc->unk58 = particle;
    if (type == -1) {
        bc->unk18 = func;
    }
    bc->unk02 = 0;
    bc->unk04 = 0;
    bc->unk08.f = bc->unk0C.f = 0.0f;
    if (name != NULL) {
        bc->unk00 = func_8002C834_main(HmfModelData[model].hmf, name);
        first = hmf->unk60[bc->unk00].unk2C;
        count = hmf->unk60[bc->unk00].unk2E;
    } else {
        bc->unk00 = -1;
        first = 0;
        count = hmf->unk1A;
    }
    order = HuMemAlloc(hmf->unk1A * sizeof(s16));
    for (i = 0; i < count; i++) {
        order[i] = i;
    }
    for (i = 0; i < 200; i++) {
        a = (rand8() * hmf->unk1A) >> 8;
        b = (rand8() * hmf->unk1A) >> 8;
        tmp = order[a];
        order[a] = order[b];
        order[b] = tmp;
    }
    group = &hmf->unkB0[first];
    for (j = 0; j < group->count; j++) {
        vert = &hmf->unk40[group->indices[j]];
        bc->unk28[j].x = vert->v.ob[0] - group->center.x;
        bc->unk28[j].y = vert->v.ob[1] - group->center.y;
        bc->unk28[j].z = vert->v.ob[2] - group->center.z;
    }
    if (type != -1) {
        switch (type) {
            case 0:
                bc->unk18 = func_80013D44_main;
                break;
            case 1:
                bc->unk18 = func_80013D4C_main;
                break;
            case 2:
                bc->unk18 = func_80013FB4_main;
                break;
        }
        side = HuSqrtf(count);
        for (i = 0; i < count; i++, particle++) {
            particle->unk04 = 1.0f;
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            index = order[i];
            angle1 = 360.0f / side * (index % side);
            sinAngle1 = sindf(angle1);
            angle2 = 180.0f / side * (index / side);
            particle->unk18 = particle->unk24 = sinAngle1 * sindf(angle2);
            particle->unk1C = particle->unk28 = cosdf(angle2);
            particle->unk20 = particle->unk2C = cosdf(angle1) * sindf(angle2);
            particle->unk08 = 1.0f;
        }
    } else {
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = particle->unk08 = particle->unk18 = particle->unk1C =
                particle->unk20 = 0.0f;
        }
    }
    HuMemFree(hmf->unk40);
    HuMemFree(order);
}
#else
INCLUDE_ASM("asm/nonmatchings/13F90", func_80013390_main);
#endif

void func_800138EC_main(s16 arg0, s32 arg1, s32 arg2) {
    HmfModelData_UnkBC_Struct *lightFlags = HmfModelData[arg0].unkBC;

    lightFlags->unk04 = arg2 | (lightFlags->unk04 & ~arg1);
}

s16 func_80013928_main(s16 arg0) {
    return HmfModelData[arg0].unkBC->unk04;
}

void func_80013954_main(s16 arg0, s16 arg1) {
    HmfModelData[arg0].unkBC->unk02 = arg1;
}

s16 func_80013980_main(s16 arg0) {
    return HmfModelData[arg0].unkBC->unk02;
}

void func_800139AC_main(s16 model, s16 group) {
    HuMtx4F lookAt;
    HuMtx4F rotMtx;
    Vec rotated[4];
    HmfModel *modelP = &HmfModelData[model];
    HmfData *hmf = modelP->hmf;
    HmfModelData_UnkBC_Struct *bc = modelP->unkBC;
    HuCamera *camera = &gCameraList[D_800CD6A6_main];
    HmfModelData_UnkBC_Unk58_Struct *particle;
    HmfVertexGroup *vtxGroup;
    Vtx *vtx;
    Vtx *v;
    Vtx *color;
    s16 *index;
    s32 first;
    s32 count;
    s32 numVerts;
    s32 i;
    s32 j;
    f32 scale;
    f32 x;
    f32 y;
    f32 z;
    Vec *out;

    HuLookAtF(lookAt, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z,
              camera->up.x, camera->up.y, camera->up.z);
    func_80018F18_main(lookAt, rotMtx);
    if (group != -1) {
        first = hmf->unk60[group].unk2C;
        count = hmf->unk60[group].unk2E;
    } else {
        first = 0;
        count = hmf->unk1A;
    }
    vtxGroup = &hmf->unkB0[first];
    out = rotated;
    for (j = 0; j < vtxGroup->count; j++, out++) {
        x = bc->unk28[j].x;
        y = bc->unk28[j].y;
        z = bc->unk28[j].z;
        out->x = x * rotMtx[0][0] + y * rotMtx[1][0] + z * rotMtx[2][0];
        out->y = x * rotMtx[0][1] + y * rotMtx[1][1] + z * rotMtx[2][1];
        out->z = x * rotMtx[0][2] + y * rotMtx[1][2] + z * rotMtx[2][2];
    }
    particle = bc->unk58;
    vtx = hmf->unk44[D_800D2008_main];
    if (bc->unk04 & 8) {
        for (i = 0; i < count; i++) {
            numVerts = vtxGroup->count & 0x7F;
            index = vtxGroup->indices;
            out = rotated;
            scale = particle->unk08;
            for (j = 0; j < numVerts; j++, out++) {
                v = &vtx[*index];
                v->v.ob[0] = scale * out->x + particle->unk0C;
                v->v.ob[1] = scale * out->y + particle->unk10;
                v->v.ob[2] = scale * out->z + particle->unk14;
                color = &vtx[*index++];
                color->v.cn[0] = particle->unk00[0];
                color->v.cn[1] = particle->unk00[1];
                color->v.cn[2] = particle->unk00[2];
            }
            vtxGroup++;
            particle++;
        }
    } else {
        for (i = 0; i < count; i++) {
            numVerts = vtxGroup->count & 0x7F;
            index = vtxGroup->indices;
            out = rotated;
            scale = particle->unk08;
            for (j = 0; j < numVerts; j++, out++) {
                v = &vtx[*index++];
                v->v.ob[0] = scale * out->x + particle->unk0C;
                v->v.ob[1] = scale * out->y + particle->unk10;
                v->v.ob[2] = scale * out->z + particle->unk14;
            }
            vtxGroup++;
            particle++;
        }
    }
}

void func_80013D44_main(s16 model) {
}

void func_80013D4C_main(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count;
    s16 i;
    f32 scale;
    f32 speed;
    f32 weight;

    if (bc->unk00 == -1) {
        count = hmf->unk1A;
    } else {
        count = hmf->unk60[bc->unk00].unk2E;
    }
    particle = bc->unk58;
    if (bc->unk02 >= 50) {
        if (!(bc->unk04 & 1)) {
            return;
        }
        bc->unk02 = 0;
    }
    scale = cosdf(bc->unk02 * 1.8f) * 2;
    if (bc->unk02 <= 0) {
        bc->unk04 &= ~4;
        bc->unk08.f = 0.0f;
        bc->unk0C.f = 10.0f;
        for (i = 0; i < count; i++) {
            particle[i].unk04 = (rand8() & 0xF) * 0.1f;
        }
        scale = 0.0f;
    }
    speed = bc->unk08.f;
    for (i = 0; i < count; i++, particle++) {
        weight = particle->unk04;
        particle->unk0C = speed * particle->unk18 * weight;
        particle->unk10 = speed * particle->unk1C * weight;
        particle->unk14 = speed * particle->unk20 * weight;
        particle->unk08 = scale;
    }
    bc->unk08.f += bc->unk0C.f;
    bc->unk0C.f *= 0.98;
    if (++bc->unk02 >= 50) {
        bc->unk04 |= 4;
    }
}

void func_80013FB4_main(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count;
    s16 i;
    f32 scale;
    f32 baseY;

    if (bc->unk00 == -1) {
        count = hmf->unk1A;
    } else {
        count = hmf->unk60[bc->unk00].unk2E;
    }
    if (bc->unk02 >= 100) {
        if (!(bc->unk04 & 1)) {
            return;
        }
        bc->unk02 = 0;
    }
    scale = cosdf(bc->unk02 * 0.9f) * 2;
    if (bc->unk02 <= 0) {
        bc->unk04 &= ~4;
        scale = 0.0f;
        particle = bc->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk18 * 10.0f;
            particle->unk28 = particle->unk1C * 10.0f;
            particle->unk2C = particle->unk20 * 10.0f;
        }
    }
    particle = bc->unk58;
    baseY = HmfModelData[model].pos.y;
    for (i = 0; i < count; i++, particle++) {
        particle->unk0C = particle->unk24 * particle->unk04 + particle->unk0C;
        particle->unk10 = particle->unk28 * particle->unk04 + particle->unk10;
        particle->unk14 = particle->unk2C * particle->unk04 + particle->unk14;
        particle->unk28 -= 0.1f;
        if (baseY + particle->unk10 < 0.0f) {
            particle->unk10 = -baseY;
            particle->unk24 *= 0.9f;
            particle->unk28 = -(particle->unk28 * 0.3f);
            particle->unk2C *= 0.9f;
        }
        particle->unk24 *= 0.999f;
        particle->unk28 *= 0.999f;
        particle->unk2C *= 0.999f;
        particle->unk08 = scale;
    }
    if (++bc->unk02 >= 100) {
        bc->unk04 |= 4;
    }
}
