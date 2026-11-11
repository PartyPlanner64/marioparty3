#include "common_duel.h"
#include "game/mallocblock.h"

// Rodrigues rotation matrix elements for a rotation of angle degrees about the unit axis (x, y, z).
#define ROT_XX(x, y, z, angle) ((x) * (x) + (1.0f - (x) * (x)) * cosdf(angle))
#define ROT_XY(x, y, z, angle) ((x) * (y) * (1.0f - cosdf(angle)) - (z) * sindf(angle))
#define ROT_XZ(x, y, z, angle) ((x) * (z) * (1.0f - cosdf(angle)) + (y) * sindf(angle))
#define ROT_YX(x, y, z, angle) ((x) * (y) * (1.0f - cosdf(angle)) + (z) * sindf(angle))
#define ROT_YY(x, y, z, angle) ((y) * (y) + (1.0f - (y) * (y)) * cosdf(angle))
#define ROT_YZ(x, y, z, angle) ((y) * (z) * (1.0f - cosdf(angle)) - (x) * sindf(angle))
#define ROT_ZX(x, y, z, angle) ((x) * (z) * (1.0f - cosdf(angle)) - (y) * sindf(angle))
#define ROT_ZY(x, y, z, angle) ((y) * (z) * (1.0f - cosdf(angle)) + (x) * sindf(angle))
#define ROT_ZZ(x, y, z, angle) ((z) * (z) + (1.0f - (z) * (z)) * cosdf(angle))

// Work area allocated by func_8010BD30 (HuMemAllocTag 0x4C bytes) and stored at
// the process object's user_data (offset 0x8C). Total size is 0x4C; fields are
// added as functions are decompiled.
typedef struct BoardResultWork {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec pos;
    /* 0x24 */ Vec unk_24;
    /* 0x30 */ Vec center;
    /* 0x3C */ Vec unk_3C;
    /* 0x48 */ f32 unk_48;
} BoardResultWork; // sizeof 0x4C

extern u8 D_8010E950_boardresult[][4];

void func_8010BE14_boardresult(void); /* extern */
void func_8010CEF4_boardresult(s16 model, s32 dataNum);
HmfModelData_UnkBC_Unk58_Struct *func_8010D28C_boardresult(s16 model, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, u8 r, u8 g, u8 b);
void func_8010D36C_boardresult(s16 model);
void func_8010D87C_boardresult(s16 model);
void func_8010DA30_boardresult(void); /* extern */

BoardResultWork *func_8010BD30_boardresult(s32 arg0) {
    Process *proc = omAddPrcObj(func_8010BE14_boardresult, 0x3F00, 0x2000, 0);
    BoardResultWork *work = proc->user_data = HuMemAllocTag(sizeof(BoardResultWork), TAG_OVERLAY);

    work->unk_06 = 60;
    work->unk_0A = 60;
    work->unk_0C.x = 0.0f;
    work->unk_0C.y = 500.0f;
    work->unk_0C.z = 0.0f;
    work->pos.x = 0.0f;
    work->pos.y = 0.0f;
    work->pos.z = 0.0f;
    work->unk_00 = arg0;
    work->unk_04 = 0;
    return work;
}

void func_8010BDBC_boardresult(BoardResultWork *arg0, s32 arg1) {
    arg0->unk_00 = arg1;
}

void func_8010BDC4_boardresult(BoardResultWork *arg0, f32 x, f32 y, f32 z) {
    arg0->unk_0C.x = x;
    arg0->unk_0C.y = y;
    arg0->unk_0C.z = z;
}

void func_8010BDD4_boardresult(BoardResultWork *arg0, f32 x, f32 y, f32 z) {
    arg0->pos.x = x;
    arg0->pos.y = y;
    arg0->pos.z = z;
}

void func_8010BDE4_boardresult(BoardResultWork *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

void func_8010BDEC_boardresult(BoardResultWork *arg0, s32 mask, s32 flags) {
    arg0->unk_04 = flags | (arg0->unk_04 & ~mask);
}

s16 func_8010BE04_boardresult(BoardResultWork *arg0) {
    return arg0->unk_04;
}

void func_8010BE0C_boardresult(BoardResultWork *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

void func_8010BE14_boardresult(void) {
    s16 model2;
    s16 i;
    s16 angle;
    HmfModelData_UnkBC_Struct *effect;
    s16 model;
    BoardResultWork *work;
    f32 rot;
    HmfData *hmf;
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    Vec cur;
    Vec prev;
    s16 count;
    s16 j;
    s16 k;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 s;
    f32 s2;
    f32 scale;
    f32 vx;
    f32 vy;
    f32 vz;
    s32 range;

    rot = 0.0f;
    work = HuPrcCurrentGet()->user_data;
    angle = 0;
    model = func_8000B108_main(0xB0034, 0x2A8);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    hmf = Hu3DData[model].hmf;
    for (k = 0; k < hmf->unk10; k++) {
        count = hmf->unk60[k].unk22;
        face = hmf->unk60[k].unk54;
        for (j = 0; j < count; j++, face++) {
            face->unk00 |= 0x80;
        }
    }
    Hu3DModelRemakeStatic(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_8010D36C_boardresult);
    func_800138EC_main(model, 8, 8);
    effect = Hu3DData[model].unkBC;
    func_8001C258_main(model, 4, 4);
    model2 = func_8000B108_main(0xB0035, 0x2B9);
    func_8001C258_main(model2, 4, 4);
    Hu3DModelScaleSet(model2, 2.0f, 2.0f, 2.0f);
    Hu3DMotionSpeedSet(model2, 2.0f);

    while (TRUE) {
        work->unk_04 &= ~1;
        work->center = work->pos;
        work->unk_24 = work->unk_0C;
        work->unk_08 = work->unk_0A;
        range = rand8() * 2 + 400;
        work->unk_3C.x = range - range / 2.0f;
        range = rand8() * 2 + 200;
        work->unk_3C.y = range - range / 2.0f;
        range = rand8() * 2 + 200;
        work->unk_3C.z = range - range / 2.0f;
        work->unk_48 = (rand8() & 1) ? 180.0f : 0.0f;
        effect->unk08.f = work->unk_06;
        cur = work->center;
        prev = cur;
        HuAudFXPlay(0x16F);
        func_8001C258_main(model, 4, 0);
        func_80013954_main(model, 0);
        effect->unk18 = func_8010D87C_boardresult;
        func_800138EC_main(model, 2, 0);

        for (i = 0; i <= work->unk_08; i++) {
            HuPrcVSleep();
            prev = cur;
            dx = work->unk_24.x - work->center.x;
            dy = work->unk_24.y - work->center.y;
            dz = work->unk_24.z - work->center.z;
            s = sindf(90.0f / work->unk_08 * i);
            s2 = sindf(180.0f / work->unk_08 * i + work->unk_48);
            cur.x = s * dx + work->center.x + s2 * work->unk_3C.x;
            cur.y = s * dy + work->center.y + s2 * work->unk_3C.y;
            cur.z = s * dz + work->center.z + s2 * work->unk_3C.z;
            angle += 5;
            if (angle > 360) {
                angle -= 360;
            }
            rot += 20.0f;
            if (rot > 360.0f) {
                rot -= 360.0f;
            }

            dx = prev.x - cur.x;
            dy = prev.y - cur.y;
            dz = prev.z - cur.z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (dist == 0.0f) {
                continue;
            }
            dx /= dist;
            dy /= dist;
            dz /= dist;

            for (j = 0; j < 2; j++) {
                vx = dx * ((rand8() * 15 >> 7) * 0.01f + 1.0f);
                vy = dy * ((rand8() * 15 >> 7) * 0.01f + 1.0f);
                vz = dz * ((rand8() * 15 >> 7) * 0.01f + 1.0f);
                scale = dist * ((s32)(rand8() * 25U >> 7) * 0.01f);
                vx *= scale;
                vy *= scale;
                vz *= scale;
                func_8010D28C_boardresult(model, vx + cur.x, vy + cur.y, vz + cur.z, vx, vy, vz, 0xFF, 0xFF, 0xC0);
            }

            vx = ROT_XX(dx, dy, dz, rot) * 0.0f + ROT_XY(dx, dy, dz, rot) + ROT_XZ(dx, dy, dz, rot) * 0.0f;
            vy = ROT_YX(dx, dy, dz, rot) * 0.0f + ROT_YY(dx, dy, dz, rot) + ROT_YZ(dx, dy, dz, rot) * 0.0f;
            vz = ROT_ZX(dx, dy, dz, rot) * 0.0f + ROT_ZY(dx, dy, dz, rot) + ROT_ZZ(dx, dy, dz, rot) * 0.0f;
            vx = (dx * 0.5f + vx * 0.5f) * dist / 2.0f;
            vy = (dy * 0.5f + vy * 0.5f) * dist / 2.0f;
            vz = (dz * 0.5f + vz * 0.5f) * dist / 2.0f;
            func_8010D28C_boardresult(model, cur.x, cur.y, cur.z, vx, vy, vz, 0xFF, 0x20, 0x20);

            vx = ROT_XX(dx, dy, dz, rot) * 0.0f + ROT_XY(dx, dy, dz, rot) * -1.0f + ROT_XZ(dx, dy, dz, rot) * 0.0f;
            vy = ROT_YX(dx, dy, dz, rot) * 0.0f + ROT_YY(dx, dy, dz, rot) * -1.0f + ROT_YZ(dx, dy, dz, rot) * 0.0f;
            vz = ROT_ZX(dx, dy, dz, rot) * 0.0f + ROT_ZY(dx, dy, dz, rot) * -1.0f + ROT_ZZ(dx, dy, dz, rot) * 0.0f;
            vx = (dx * 0.5f + vx * 0.5f) * dist / 2.0f;
            vy = (dy * 0.5f + vy * 0.5f) * dist / 2.0f;
            vz = (dz * 0.5f + vz * 0.5f) * dist / 2.0f;
            func_8010D28C_boardresult(model, cur.x, cur.y, cur.z, vx, vy, vz, 0xFF, 0x40, 0x00);
        }

        HuPrcSleep(15);
        func_8001C258_main(model, 4, 4);
        Hu3DMotionTimeSet(model2, 0.0f);
        func_8001C258_main(model2, 4, 0);
        Hu3DModelPosSet(model2, cur.x, cur.y, cur.z);
        HuPrcVSleep();
        HuAudFXPlay(0x170);
        func_8010CEF4_boardresult(model, work->unk_00);
        effect->unk18 = func_8010D36C_boardresult;
        func_80013954_main(model, 0);
        func_8001C258_main(model, 4, 0);
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        func_800138EC_main(model, 2, 0);
        while (!(func_80013928_main(model) & 2)) {
            HuPrcVSleep();
        }
        func_8001C258_main(model2, 4, 4);
        func_8001C258_main(model, 4, 4);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        work->unk_04 |= 1;
        if (!(work->unk_04 & 2)) {
            while (work->unk_04 & 1) {
                HuPrcVSleep();
            }
        } else {
            HuPrcVSleep();
        }
    }
}

void func_8010CEF4_boardresult(s16 model, s32 dataNum) {
    s16 anim = func_8000B838_main(dataNum);
    s16 group = HuSprGrpCreate(1, 0);
    HuSprite *sprite;
    u16 *pixels;
    s16 width;
    s16 height;
    s16 count;
    HmfModelData_UnkBC_Struct *effect;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 used;
    s16 x;
    s16 y;
    s16 i;
    s16 white;

    HuSprGrpMemberSet(group, 0, anim, 0);
    sprite = HuSprGet(group, 0);
    pixels = sprite->unk_84->unk00->unk00;
    width = sprite->unk_84->unk00->unk04;
    height = sprite->unk_84->unk00->unk06;
    // Counts the white pixels, but the result goes unused.
    white = 0;
    for (i = 0; i < width * height; i++) {
        if (*pixels++ == 0xFFFF) {
            white++;
        }
    }
    (void)white;

    pixels = sprite->unk_84->unk00->unk00;
    effect = Hu3DData[model].unkBC;
    count = Hu3DData[model].hmf->unk1A;
    particle = effect->unk58;
    for (y = 0, used = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            if (*pixels++ == 0xFFFF && used < count) {
                particle = &effect->unk58[used];
                particle->unk18 = rand8() & 0xF;
                particle->unk24 = (x - width / 2) * 12;
                particle->unk28 = (height / 2 - y) * 12;
                particle->unk2C = 1.0f;
                particle->unk08 = 3.0f;
                particle->unk04 = (s32)((s16)rand8() * 5U / 128) * 0.1f + 3.0f;
                used++;
                particle++;
            }
        }
    }

    for (i = 0; i < count - used; i++, particle++) {
        particle->unk08 = particle->unk2C = particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
    }

    HuSprGrpKill(group);
    HuSprAnimKill(anim);
}

HmfModelData_UnkBC_Unk58_Struct *func_8010D28C_boardresult(s16 model, f32 x, f32 y, f32 z, f32 arg4, f32 arg5,
                                                           f32 arg6, u8 r, u8 g, u8 b) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Unk58_Struct *particle = Hu3DData[model].unkBC->unk58;
    s16 i;
    s16 count = hmf->unk1A;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            particle->unk24 = arg4;
            particle->unk28 = arg5;
            particle->unk2C = arg6;
            particle->unk00[0] = r;
            particle->unk00[1] = g;
            particle->unk00[2] = b;
            particle->unk08 = 2.0f;
            break;
        }
    }
    return particle;
}

void func_8010D36C_boardresult(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    HmfModelData_UnkBC_Unk58_Struct *src;
    HmfModelData_UnkBC_Unk58_Struct *dst;
    s16 count = hmf->unk1A;
    s16 i;
    s16 j;
    s16 done;
    u8 r;
    u8 g;
    u8 b;
    f32 angle;

    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        particle = effect->unk58;
        for (i = 0; i < count; i++, particle++) {
            if (particle->unk2C > 0.0f) {
                particle->unk08 = 1.0f;
            }
        }
    }
    particle = effect->unk58;

    r = rand8() | 0x80;
    g = rand8() | 0x80;
    b = rand8() | 0x80;

    if (effect->unk02 <= effect->unk08.f) {
        if (effect->unk02 > 20) {
            for (j = 0; j < 2; j++) {
                src = &effect->unk58[(rand8() * count) >> 8];
                if (src->unk2C > 0.0f) {
                    dst = &effect->unk58[(rand8() * count) >> 8];
                    if (dst->unk2C <= 0.0f) {
                        dst->unk0C = src->unk0C;
                        dst->unk10 = src->unk10;
                        dst->unk14 = src->unk14;
                        dst->unk08 = 1.0f;
                    }
                }
            }
        }
        for (i = 0; i < count; i++, particle++) {
            if (particle->unk08 > 0.0f) {
                particle->unk00[0] = r;
                particle->unk00[1] = g;
                particle->unk00[2] = b;
                if (particle->unk2C > 0.0f) {
                    angle = effect->unk02 * particle->unk04;
                    if (angle > 90.0f) {
                        angle = 90.0f;
                    }
                    particle->unk0C = sindf(angle) * particle->unk24;
                    particle->unk10 = sindf(angle) * particle->unk28;
                    particle->unk14 = 0.0f;
                    particle->unk08 = ((effect->unk02 + i) & 1) * 0.5f + 1.0f;
                } else {
                    particle->unk10 -= 10.0f;
                    particle->unk08 -= 0.04f;
                }
            } else {
                particle->unk08 = 0.0f;
            }
        }
    } else {
        for (i = 0, done = 0; i < count; i++, particle++) {
            if (particle->unk08 > 0.0f) {
                particle->unk00[0] = r;
                particle->unk00[1] = g;
                particle->unk00[2] = b;
                if (particle->unk2C > 0.0f) {
                    if (particle->unk18 <= 0.0f) {
                        particle->unk10 -= particle->unk04 * 5.0f;
                        particle->unk08 -= 0.02f;
                        if (particle->unk08 < 0.0f) {
                            particle->unk08 = 0.0f;
                        }
                    } else {
                        particle->unk18 -= 1.0f;
                        particle->unk08 = ((effect->unk02 + i) & 1) * 0.5f + 1.0f;
                    }
                } else {
                    particle->unk10 -= 10.0f;
                    particle->unk08 -= 0.04f;
                }
            } else {
                particle->unk08 = 0.0f;
                done++;
            }
        }
        if (done >= i) {
            effect->unk04 |= 2;
            return;
        }
    }
    effect->unk02++;
}

void func_8010D87C_boardresult(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count = hmf->unk1A;
    s16 i;

    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        particle = effect->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk08 = particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        }
        effect->unk02++;
    }

    particle = effect->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            particle->unk0C += particle->unk24;
            particle->unk10 += particle->unk28;
            particle->unk14 += particle->unk2C;
            particle->unk10 -= 5.0f;
            particle->unk08 -= 0.05f;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void func_8010D9D0_boardresult(void) {
    Process *proc = omAddPrcObj(func_8010DA30_boardresult, 0x3F00, 0x2000, 0);
    BoardResultWork *work = proc->user_data = HuMemAllocTag(sizeof(BoardResultWork), TAG_OVERLAY);

    work->pos.x = 0.0f;
    work->pos.y = 100.0f;
    work->pos.z = 0.0f;
}

void func_8010DA30_boardresult(void) {
    BoardResultWork *work = HuPrcCurrentGet()->user_data;
    s16 model = func_8000B108_main(0xB0034, 0x6A8);
    HmfData *hmf;
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    HmfModelData_UnkBC_Struct *effect;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 angles[2];
    Vec pos[2];
    Vec prev[2];
    f32 rotAngles[2];
    f32 tiltAngles[2];
    s16 count;
    s16 i;
    s16 j;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 angle;
    f32 vx;
    f32 vy;
    f32 vz;
    s16 color;

    func_8001C2FC_main(model, 0x20000, 0x20000);
    hmf = Hu3DData[model].hmf;
    for (j = 0; j < hmf->unk10; j++) {
        count = hmf->unk60[j].unk22;
        face = hmf->unk60[j].unk54;
        for (i = 0; i < count; i++, face++) {
            face->unk00 |= 0x80;
        }
    }
    Hu3DModelRemakeStatic(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_8010D36C_boardresult);
    func_800138EC_main(model, 8, 8);
    effect = Hu3DData[model].unkBC;
    func_8001C258_main(model, 4, 4);
    func_8001C258_main(model, 4, 0);
    func_80013954_main(model, 0);
    effect->unk18 = func_8010D87C_boardresult;
    func_800138EC_main(model, 2, 0);

    work->center = work->pos;
    pos[0].x = sindf(0.0f) * 150.0f + work->center.x;
    pos[0].y = work->center.y;
    pos[0].z = cosdf(0.0f) * 150.0f + work->center.z;
    prev[0] = pos[0];
    tiltAngles[0] = rotAngles[0] = 0.0f;
    angles[0] = 0;
    pos[1].x = sindf(180.0f) * 150.0f + work->center.x;
    pos[1].y = work->center.y;
    pos[1].z = cosdf(180.0f) * 150.0f + work->center.z;
    prev[1] = pos[1];
    tiltAngles[1] = rotAngles[1] = 180.0f;
    angles[1] = 180;

    while (TRUE) {
        HuPrcVSleep();
        for (i = 0; i < 2; i++) {
            prev[i] = pos[i];
            dx = sindf(angles[i]) * 150.0f;
            dz = cosdf(angles[i]) * 150.0f;
            angle = sindf(tiltAngles[i]) * 10.0f;
            pos[i].x = dx * cosdf(angle) + work->center.x;
            pos[i].y = dx * -sindf(angle) + work->center.y;
            pos[i].z = dz + work->center.z;
            angles[i] += 5;
            if (angles[i] > 360) {
                angles[i] -= 360;
            }
            rotAngles[i] += 20.0f;
            if (rotAngles[i] > 360.0f) {
                rotAngles[i] -= 360.0f;
            }
            tiltAngles[i] += 1.0f;
            if (tiltAngles[i] > 360.0f) {
                tiltAngles[i] -= 360.0f;
            }

            dx = prev[i].x - pos[i].x;
            dy = prev[i].y - pos[i].y;
            dz = prev[i].z - pos[i].z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (dist == 0.0f) {
                continue;
            }
            dx /= dist;
            dy /= dist;
            dz /= dist;
            angle = rotAngles[i];

            vx = dx * dy * (1.0f - cosdf(angle)) - dz * sindf(angle);
            vy = dy * dy + (1.0f - dy * dy) * cosdf(angle);
            vz = dy * dz * (1.0f - cosdf(angle)) + dx * sindf(angle);
            vx = (dx * 0.7f + vx * 0.3f) * dist * 0.7f;
            vy = (dy * 0.7f + vy * 0.3f) * dist * 0.7f;
            vz = (dz * 0.7f + vz * 0.3f) * dist * 0.7f;
            color = rand8() & 3;
            particle = func_8010D28C_boardresult(model, pos[i].x, pos[i].y, pos[i].z, vx, vy, vz,
                                                 D_8010E950_boardresult[color][0], D_8010E950_boardresult[color][1],
                                                 D_8010E950_boardresult[color][2]);
            particle->unk08 = 1.0f;

            vx = -(dx * dy * (1.0f - cosdf(angle)) - dz * sindf(angle));
            vy = -(dy * dy + (1.0f - dy * dy) * cosdf(angle));
            vz = -(dy * dz * (1.0f - cosdf(angle)) + dx * sindf(angle));
            vx = (dx * 0.7f + vx * 0.3f) * dist * 0.7f;
            vy = (dy * 0.7f + vy * 0.3f) * dist * 0.7f;
            vz = (dz * 0.7f + vz * 0.3f) * dist * 0.7f;
            color = rand8() & 3;
            particle = func_8010D28C_boardresult(model, pos[i].x, pos[i].y, pos[i].z, vx, vy, vz,
                                                 D_8010E950_boardresult[color][0], D_8010E950_boardresult[color][1],
                                                 D_8010E950_boardresult[color][2]);
            particle->unk08 = 1.0f;
        }
    }
}
