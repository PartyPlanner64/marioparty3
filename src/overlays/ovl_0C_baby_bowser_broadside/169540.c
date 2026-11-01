#include "common.h"
#include "mallocblock.h"
#include "gcc/memory.h"

#include "overlays/baby_bowser_broadside.h"

typedef struct BabyBowserBroadsideColor {
    u8 rgba[4];
} BabyBowserBroadsideColor;

extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;

extern Gfx D_8010FE80_baby_bowser_broadside[];

extern BabyBowserBroadsideColor D_8010FFE0_baby_bowser_broadside;
extern const f64 D_8010FFE8_baby_bowser_broadside;
extern const f64 D_8010FFF0_baby_bowser_broadside;

f32 atan2df(f32 y, f32 x);

s16 func_8010B54C_baby_bowser_broadside(HuSprite_Unk84_Struct *sprite, f32 scale);
s16 func_8010C8D4_baby_bowser_broadside(HuSprite_Unk84_Struct *sprite, u8 *color);

void func_8010F878_baby_bowser_broadside(f32 *matrix);
void func_80017D24_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_8010D590_baby_bowser_broadside(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color);

s16 func_8010D6C4_baby_bowser_broadside(HuSprite_Unk84_Struct *sprite, HmfData *data, f32 scale, s16 arg3, s16 arg4);

void func_8010A3C8_baby_bowser_broadside(BabyBowserBroadsideGroup *group);

void func_8010A7CC_baby_bowser_broadside(s16 arg0);

f32 func_8010F004_baby_bowser_broadside(BabyBowserBroadsideShip *ship, Vec *first, Vec *second);
void func_8010DE70_baby_bowser_broadside(void);
s32 func_8010E348_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, BabyBowserBroadsideShip *ship);
s32 func_8010E538_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, BabyBowserBroadsideShip *ship);
s32 func_8010E710_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, BabyBowserBroadsideShip *ship);
s32 func_8010EDC0_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, BabyBowserBroadsideShip *ship);
f32 func_8010ED1C_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, Vec *point);
s16 func_8010E9FC_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, Vec *point);
void func_8010F3C4_baby_bowser_broadside(Vec *vertices, BabyBowserBroadsidePlane *plane);
void func_8010FB74_baby_bowser_broadside(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 *matrix);
void func_8010FC2C_baby_bowser_broadside(Vec *vertices, s16 count, f32 *matrix, Vec *output);

void func_80109ED0_baby_bowser_broadside(void) {
    D_80110018_baby_bowser_broadside = HuMemAllocTag(14 * sizeof(BabyBowserBroadsideSprite), TAG_OVERLAY);
    memset(D_80110018_baby_bowser_broadside, 0, 14 * sizeof(BabyBowserBroadsideSprite));
    D_8011001C_baby_bowser_broadside = HuMemAllocTag(16 * sizeof(BabyBowserBroadsideModel), TAG_OVERLAY);
    memset(D_8011001C_baby_bowser_broadside, 0, 16 * sizeof(BabyBowserBroadsideModel));
    D_80110010_baby_bowser_broadside = HuMemAllocTag(8 * sizeof(BabyBowserBroadsideWork), TAG_OVERLAY);
    memset(D_80110010_baby_bowser_broadside, 0, 8 * sizeof(BabyBowserBroadsideWork));
    D_80110014_baby_bowser_broadside = HuMemAllocTag(7 * sizeof(BabyBowserBroadsideGroup), TAG_OVERLAY);
}

BabyBowserBroadsideGroup *func_80109F64_baby_bowser_broadside(omObjData *object, s8 index, s16 count, s16 handlers) {
    BabyBowserBroadsideGroup *group;
    if (index >= 7) {
        return NULL;
    }
    group = &D_80110014_baby_bowser_broadside[index];
    if (handlers != 0) {
        group->unk_04 = HuMemAllocTag(handlers * sizeof(BabyBowserBroadsideHandler), TAG_OVERLAY);
        memset(group->unk_04, 0, handlers * sizeof(BabyBowserBroadsideHandler));
        group->unk_0C = HuMemAllocTag((handlers + 1) * sizeof(BabyBowserBroadsideOrder), TAG_OVERLAY);
    }
    group->unk_08 = handlers;
    group->unk_00 = HuMemAllocTag(sizeof(BabyBowserBroadsideSlot), TAG_OVERLAY);
    if (count != 0) {
        group->unk_00->unk_04 = HuMemAllocTag(count * sizeof(u16), TAG_OVERLAY);
        memset(group->unk_00->unk_04, 0, count * sizeof(u16));
    }
    group->unk_00->unk_08 = count;
    group->unk_10 = 1;
    group->unk_00->unk_00 = object;
    return group;
}

s16 func_8010A0B4_baby_bowser_broadside(s8 index, s32 flags, s32 arg2, void (*callback)(), u8 arg4) {
    BabyBowserBroadsideGroup *group = &D_80110014_baby_bowser_broadside[index];
    BabyBowserBroadsideHandler *handler = group->unk_04;
    s16 i;
    s16 count = group->unk_08;

    for (i = 0; i < count; i++, handler++) {
        if (handler->unk_00 == 0) {
            handler->unk_00 = 1;
            handler->unk_08 = flags;
            handler->unk_02 = i;
            handler->unk_05 = arg4;
            handler->unk_04 = 0;
            handler->unk_3C = arg2;
            handler->unk_40 = callback;
            break;
        }
    }
    group->unk_10 = 1;
    return i;
}

void func_8010A158_baby_bowser_broadside(s8 arg0, BabyBowserBroadsideHandler *arg1) {
    memset(arg1, 0, sizeof(BabyBowserBroadsideHandler));
    D_80110014_baby_bowser_broadside[arg0].unk_10 = 1;
}

void func_8010A1B0_baby_bowser_broadside(s8 index, s8 tag) {
    BabyBowserBroadsideGroup *group = &D_80110014_baby_bowser_broadside[index];
    BabyBowserBroadsideHandler *handler = group->unk_04;
    s16 i;

    for (i = 0; i < group->unk_08; i++, handler++) {
        if ((s8)handler->unk_05 == tag) {
            func_8010A158_baby_bowser_broadside(index, handler);
        }
    }
}

void func_8010A264_baby_bowser_broadside(s8 arg0) {
    BabyBowserBroadsideGroup *group = &D_80110014_baby_bowser_broadside[arg0];

    memset(group->unk_04, 0, group->unk_08 * sizeof(BabyBowserBroadsideHandler));
    group->unk_10 = 1;
}

void func_8010A2C4_baby_bowser_broadside(s8 index) {
    BabyBowserBroadsideGroup *group = &D_80110014_baby_bowser_broadside[index];
    BabyBowserBroadsideOrder *order;
    BabyBowserBroadsideHandler *handler;
    s8 i;

    if (group->unk_10 != 0) {
        func_8010A3C8_baby_bowser_broadside(group);
    }
    for (i = 0; group->unk_0C[i].next.index != -1;) {
        order = group->unk_0C;
        i = order[i].next.bytes[1];
        handler = &group->unk_04[order[i].handler];
        if (handler->unk_00 != 0) {
            handler->unk_40(group->unk_00, handler);
        }
    }
}

void func_8010A3C8_baby_bowser_broadside(BabyBowserBroadsideGroup *group) {
    BabyBowserBroadsideOrder *order = group->unk_0C;
    BabyBowserBroadsideHandler *handler = group->unk_04;
    s16 entry;
    s16 tail;
    s16 i;
    s16 insert;
    s16 current;
    s16 found;

    order[0].next.index = -1;
    entry = 1;
    tail = 0;
    for (i = 0; i < group->unk_08; i++, handler++) {
        if (handler->unk_00 != 0) {
            insert = tail;
            found = 0;
            current = 0;
            while (order[current].next.index != -1) {
                current = order[current].next.index;
                if ((u32)handler->unk_08 < order[current].priority) {
                    insert = current;
                    found = 1;
                    break;
                }
            }
            order[entry].handler = i;
            order[entry].priority = handler->unk_08;
            if (found != 0) {
                order[entry].next.index = order[order[insert].previous].next.index;
                order[entry].previous = order[insert].previous;
                order[order[insert].previous].next.index = entry;
                order[order[entry].next.index].previous = entry;
            } else {
                order[entry].next.index = order[insert].next.index;
                order[entry].previous = insert;
                order[insert].next.index = entry;
                tail = entry;
            }
            entry++;
        }
    }
    group->unk_10 = 0;
}

s16 func_8010A598_baby_bowser_broadside(s16 priority, s32 directory, s32 file, s32 bank, s32 attr) {
    BabyBowserBroadsideSprite *sprite = D_80110018_baby_bowser_broadside;
    HuSprite *data;
    s16 i;
    u16 animation = bank;

    for (i = 0; i < 14; i++, sprite++) {
        if (sprite->unk_00 == 0) {
            sprite->unk_02 = func_8000B838_main((directory << 16) | file);
            sprite->unk_01 = HuSprGrpCreate(1, 0);
            sprite->unk_06 = 255;
            HuSprAttrReset(sprite->unk_01, 0, -1);
            HuSprGrpMemberSet(sprite->unk_01, 0, sprite->unk_02, 0);
            HuSprAttrSet(sprite->unk_01, 0, attr);
            func_800550F4_main(sprite->unk_01, 0, animation);
            HuSprPriSet(sprite->unk_01, 0, (u16)priority);
            func_80054FF8_main(sprite->unk_01, 0, 0);
            HuSprSpeedSet(sprite->unk_01, 0, 1.0f);
            HuSprScaleSet(sprite->unk_01, 0, 1.0f, 1.0f);
            HuSprPosSet(sprite->unk_01, 0, 100, 100);
            data = HuSprGet(sprite->unk_01, 0);
            if (animation == 0) {
                sprite->unk_04 = 99;
            } else {
                sprite->unk_04 = data->unk_84->unk10;
            }
            sprite->unk_00 = 2;
            func_8010A7CC_baby_bowser_broadside(i);
            break;
        }
    }
    return i;
}

void func_8010A738_baby_bowser_broadside(s16 index, s16 x, s16 y) {
    BabyBowserBroadsideSprite *sprite = &D_80110018_baby_bowser_broadside[index];

    if (sprite->unk_00 != 0) {
        func_80054FF8_main(sprite->unk_01, 0, 0);
        HuSprDispOn(sprite->unk_01, 0);
        HuSprPosSet(sprite->unk_01, 0, x, y);
        sprite->unk_00 = 2;
    }
}

void func_8010A7CC_baby_bowser_broadside(s16 arg0) {
    BabyBowserBroadsideSprite *sprite = &D_80110018_baby_bowser_broadside[arg0];

    if (sprite->unk_00 != 0) {
        HuSprDispOff(sprite->unk_01, 0);
        sprite->unk_00 = 1;
    }
}

void func_8010A81C_baby_bowser_broadside(void) {
    BabyBowserBroadsideSprite *sprite = D_80110018_baby_bowser_broadside;
    s16 i;

    for (i = 0; i < 14; i++, sprite++) {
        if (sprite->unk_00 == 2) {
            if (HuSprGet(sprite->unk_01, 0)->unk_90 + 1 >= (u16)sprite->unk_04) {
                HuSprDispOff(sprite->unk_01, 0);
                func_80054FF8_main(sprite->unk_01, 0, 0);
            }
        }
    }
}

s16 func_8010A8C4_baby_bowser_broadside(s32 directory, s32 file, f32 scale, s16 type, s32 arg4, s32 flags) {
    BabyBowserBroadsideModel *work = D_8011001C_baby_bowser_broadside;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 == 0) {
            work->unk_0C = func_8000B108_main((directory << 16) | file, flags);
            func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            model = &HmfModelData[work->unk_0C];
            model->motTime = 0;
            model->motSpeed = 0;
            if (model->hmf->unk98 != NULL) {
                model->hmf->unk98->unk08 = 0;
            }
            work->unk_0A = type;
            work->unk_04 = arg4;
            work->unk_10 = scale;
            work->unk_08 = -1;
            work->unk_00 = 1;
            break;
        }
    }
    return i;
}

s16 func_8010A9D4_baby_bowser_broadside(s16 source, f32 scale, s16 type, s32 arg4) {
    BabyBowserBroadsideModel *work = D_8011001C_baby_bowser_broadside;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 == 0) {
            work->unk_0C = Hu3DModelLink(source);
            func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            model = &HmfModelData[work->unk_0C];
            model->motTime = 0;
            model->motSpeed = 0;
            if (model->hmf->unk98 != NULL) {
                model->hmf->unk98->unk08 = 0;
            }
            work->unk_0A = type;
            work->unk_04 = arg4;
            work->unk_10 = scale;
            work->unk_08 = -1;
            work->unk_00 = 1;
            break;
        }
    }
    return i;
}

s16 func_8010AADC_baby_bowser_broadside(s16 type) {
    BabyBowserBroadsideModel *work = D_8011001C_baby_bowser_broadside;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 != 0 && work->unk_0A == type) {
            model = &HmfModelData[work->unk_0C];
            if ((model->attr & HU3D_ATTR_DISPOFF) != 0 && work->unk_08 == -1) {
                break;
            }
        }
    }
    if (i == 16) {
        return -1;
    }
    return i;
}

s32 func_8010AB80_baby_bowser_broadside(s16 index, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale, f32 delay) {
    BabyBowserBroadsideModel *work;
    HmfModel *model;

    if (index >= 16) {
        return 0;
    }
    if (D_8011001C_baby_bowser_broadside[index].unk_00 == 0) {
        return 0;
    }
    {
        work = &D_8011001C_baby_bowser_broadside[index];
        model = &HmfModelData[work->unk_0C];
        if ((model->attr & HU3D_ATTR_DISPOFF) != 0 && work->unk_08 == -1) {
            Hu3DModelPosSet(work->unk_0C, x, y, z);
            Hu3DModelRotSet(work->unk_0C, rx, ry, rz);
            Hu3DModelScaleSet(work->unk_0C, scale, scale, scale);
            if (delay == 0.0f) {
                func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                work->unk_08 = 1;
                work->unk_18 = 0.0f;
                work->unk_14 = 0.0f;
                model->motSpeed = work->unk_10;
            } else {
                work->unk_08 = 0;
                work->unk_18 = delay;
                work->unk_14 = 0;
            }
            return 1;
        }
    }
    return 0;
}

void func_8010ACF8_baby_bowser_broadside(void) {
    BabyBowserBroadsideModel *work = D_8011001C_baby_bowser_broadside;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 16; i++, work++) {
        if (work->unk_00 != 0 && work->unk_08 != -1) {
            model = &HmfModelData[work->unk_0C];
            if (work->unk_08 != 0) {
                if (model->motTime >= D_800CCF58_main[model->motId].unk02) {
                    model->motTime = 0;
                    if (model->hmf->unk98 != NULL) {
                        model->hmf->unk98->unk08 = 0;
                    }
                    if (!(work->unk_04 & 1)) {
                        func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        work->unk_08 = -1;
                        model->motSpeed = 0;
                    }
                }
            } else {
                if (work->unk_14++ >= work->unk_18) {
                    func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    work->unk_08 = 1;
                    model->motSpeed = work->unk_10;
                }
            }
        }
    }
}

s16 func_8010AE60_baby_bowser_broadside(s32 directory, s32 file, s16 type, s32 flags) {
    BabyBowserBroadsideWork *work = D_80110010_baby_bowser_broadside;
    BabyBowserBroadsideColor color = D_8010FFE0_baby_bowser_broadside;
    s16 frame;
    s16 i;

    for (i = 0; i < 8; i++, work++) {
        if (work->unk_00 == 0) {
            frame = func_8000B838_main((directory << 16) | file);
            work->unk_0A = frame;
            if (flags & 1) {
                work->unk_0C = func_8010C8D4_baby_bowser_broadside(func_80055194_main(frame), color.rgba);
            } else {
                work->unk_0C = func_8010B54C_baby_bowser_broadside(func_80055194_main(frame), 1.0f);
            }
            if (flags & 8) {
                func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            work->unk_14 = &HmfModelData[work->unk_0C].pos.x;
            work->unk_18 = &HmfModelData[work->unk_0C].pos.y;
            work->unk_1C = &HmfModelData[work->unk_0C].pos.z;
            work->unk_08 = type;
            work->unk_04 = flags;
            work->unk_0E = func_80055194_main(frame)->unk10;
            work->unk_10 = 0;
            work->unk_00 = 1;
            break;
        }
    }
    return i;
}

s16 func_8010AFF4_baby_bowser_broadside(s16 type) {
    BabyBowserBroadsideWork *work = D_80110010_baby_bowser_broadside;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 8; i++, work++) {
        if (work->unk_00 != 0 && work->unk_08 == type) {
            model = &HmfModelData[work->unk_0C];
            if ((model->attr & HU3D_ATTR_DISPOFF) != 0 && (work->unk_04 & 8) != 0) {
                break;
            }
        }
    }
    if (i == 8) {
        return -1;
    }
    return i;
}

void func_8010B098_baby_bowser_broadside(s16 arg0, f32 arg1, f32 arg2, f32 arg3, u8 *arg4) {
    HmfModel *model;

    if (arg0 >= 8) {
        return;
    }
    model = &HmfModelData[D_80110010_baby_bowser_broadside[arg0].unk_0C];
    model->pos.x = arg1;
    model->pos.y = arg2;
    model->pos.z = arg3;
    func_8001C258_main(D_80110010_baby_bowser_broadside[arg0].unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    D_80110010_baby_bowser_broadside[arg0].unk_20[0] = arg4[0];
    D_80110010_baby_bowser_broadside[arg0].unk_20[1] = arg4[1];
    D_80110010_baby_bowser_broadside[arg0].unk_20[2] = arg4[2];
    D_80110010_baby_bowser_broadside[arg0].unk_20[3] = arg4[3];
    D_80110010_baby_bowser_broadside[arg0].unk_04 &= ~0x18;
}

void func_8010B198_baby_bowser_broadside(s16 index, f32 *x, f32 *y, f32 *z) {
    HmfModel *model;

    if (index >= 8) {
        return;
    }
    model = &HmfModelData[D_80110010_baby_bowser_broadside[index].unk_0C];
    if (x != NULL) {
        D_80110010_baby_bowser_broadside[index].unk_14 = x;
    } else {
        D_80110010_baby_bowser_broadside[index].unk_14 = &model->pos.x;
    }
    if (y != NULL) {
        D_80110010_baby_bowser_broadside[index].unk_18 = y;
    } else {
        D_80110010_baby_bowser_broadside[index].unk_18 = &model->pos.y;
    }
    if (z != NULL) {
        D_80110010_baby_bowser_broadside[index].unk_1C = z;
    } else {
        D_80110010_baby_bowser_broadside[index].unk_1C = &model->pos.z;
    }
    func_8001C258_main(D_80110010_baby_bowser_broadside[index].unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    D_80110010_baby_bowser_broadside[index].unk_04 = (D_80110010_baby_bowser_broadside[index].unk_04 & ~0x18) | 0x10;
}

BabyBowserBroadsideWork *func_8010B328_baby_bowser_broadside(s16 arg0) {
    if (arg0 >= 8) {
        return NULL;
    }
    return &D_80110010_baby_bowser_broadside[arg0];
}

HmfModel *func_8010B360_baby_bowser_broadside(s16 arg0) {
    HmfModel *model;

    if (arg0 < 8) {
        model = &HmfModelData[D_80110010_baby_bowser_broadside[arg0].unk_0C];
    } else {
        model = NULL;
    }
    return model;
}

void func_8010B3B4_baby_bowser_broadside(void) {
    BabyBowserBroadsideWork *work = D_80110010_baby_bowser_broadside;
    HmfModel *model;
    s16 i;

    for (i = 0; i < 8; i++, work++) {
        if (work->unk_00 != 0 && !(work->unk_04 & 8)) {
            model = &HmfModelData[work->unk_0C];
            if (work->unk_04 & 0x10) {
                model->pos.x = *work->unk_14;
                model->pos.y = *work->unk_18;
                model->pos.z = *work->unk_1C;
            }
            model->rot.x = CRot.x;
            model->rot.y = CRot.y;
            func_8010F878_baby_bowser_broadside(model->mtx[0]);
            func_80017D24_main(model->mtx, 0.0f, 0.0f, CRot.z);
            if (work->unk_04 & 1) {
                if (work->unk_04 & 2) {
                    func_8010D590_baby_bowser_broadside((u16)work->unk_0C, func_80055194_main(work->unk_0A), (u16)work->unk_10, work->unk_20);
                    work->unk_10++;
                    if (work->unk_10 >= work->unk_0E) {
                        if (work->unk_04 & 4) {
                            work->unk_10 = 0;
                        } else {
                            work->unk_10 = 0;
                            work->unk_04 |= 8;
                            func_8001C258_main(work->unk_0C, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        }
                    }
                }
            }
        }
    }
}

s16 func_8010B54C_baby_bowser_broadside(HuSprite_Unk84_Struct *sprite, f32 alpha) {
    Gfx *buffer;
    Gfx *gfx;
    HmfData *data;
    u32 count;
    s16 i;
    s16 model;
    s32 stride;
    s32 size;

    buffer = HuMemAlloc(0x10000);
    model = func_8001A894_main(0x4C1, buffer, 4);
    data = HmfModelData[model].hmf;
    data->unk60->unk50 |= 0x1010000;
    count = func_8010D6C4_baby_bowser_broadside(sprite, data, 1.0f, 0, 100);
    gfx = buffer;
    gSPDisplayList(gfx++, osVirtualToPhysical(D_8010FE80_baby_bowser_broadside));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_FRONT | G_SHADING_SMOOTH | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 1, 1, 1, 1);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, (u32)(alpha * 255.0f));
    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->unk1A >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        stride = 0x800;
        if (sprite->unk18 == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->unk0C);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->unk0C);
        }
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        stride = 0x1000;
    }
    gDPPipeSync(gfx++);
    for (i = 0; i < count; i++) {
        gSPSegment(gfx++, 2, osVirtualToPhysical((u8 *)sprite->unk08 + stride * i));
        gDPLoadTextureBlock(gfx++, 0x02000000, G_IM_FMT_CI, G_IM_SIZ_8b, sprite->unk00->unk04, sprite->unk00->unk06 / count, 0,
                            G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 1, osVirtualToPhysical(&data->unk44[0][i * 4]));
        gSPVertex(gfx++, 0x01000000, 4, 0);
        gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    }
    gSPClearGeometryMode(gfx++, -1);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - (u8 *)buffer;
    data->unk3C->unk00[0] = HuMemAllocTag(size, data->unk0E);
    bcopy(buffer, data->unk3C->unk00[0], size);
    HuMemFree(buffer);
    return model;
}

s16 func_8010BCBC_baby_bowser_broadside(HuSprite_Unk84_Struct *sprite, f32 alpha) {
    u8 *buffer;
    Gfx *gfx;
    Gfx *header;
    HmfData *data;
    u16 format;
    s16 i;
    s16 model;
    s32 size;

    gfx = HuMemAlloc(0x10000);
    header = gfx;
    buffer = (u8 *)gfx;
    model = func_8001A894_main(0x4C1, gfx, 4);
    data = HmfModelData[model].hmf;
    data->unk60->unk50 |= 0x1010000;
    gfx++;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(0x14, D_800CDD6A_main);
    func_8010D6C4_baby_bowser_broadside(sprite, data, 1.0f, 0, 30);
    gSPDisplayList(header, osVirtualToPhysical(D_8010FE80_baby_bowser_broadside));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 1, 1, 1, 1);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (sprite->unk1A >= 2) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, (u32)(alpha * 255.0f));
    } else {
        if (sprite->unk18 & 0x8000) {
            gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
        } else {
            gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        }
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, (u32)(alpha * 255.0f));
    }
    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->unk1A >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->unk18 == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->unk0C);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->unk0C);
        }
        gDPPipeSync(gfx++);
        format = G_IM_FMT_CI;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = ((u32)sprite->unk18 >> 15) * 4;
    }
    switch (sprite->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                   G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 1, osVirtualToPhysical(data->unk44[0]));
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, -1);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    data->unk3C->unk00[0] = data->unk3C->unk10 = HuMemAllocTag(size, data->unk0E);
    bcopy(buffer, data->unk3C->unk00[0], size);
    HuMemFree(buffer);
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[D_800D2008_main + 1];
    return model;
}

s16 func_8010C8D4_baby_bowser_broadside(HuSprite_Unk84_Struct *sprite, u8 *color) {
    u8 *buffer;
    Gfx *gfx;
    Gfx *header;
    HmfData *data;
    u16 format;
    s32 i;
    s32 model;
    s32 size;

    gfx = HuMemAlloc(0x10000);
    header = gfx;
    buffer = (u8 *)gfx;
    model = func_8001A894_main(0x8C1, gfx, 4);
    data = HmfModelData[model].hmf;
    data->unk60->unk50 |= 0x1010000;
    gfx++;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    func_8010D6C4_baby_bowser_broadside(sprite, data, 1.0f, 0, 0);
    gSPDisplayList(header, osVirtualToPhysical(D_8010FE80_baby_bowser_broadside));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 1, 1, 1, 1);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (sprite->unk18 & 0x8000) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    data->unk3C->unk10 = HuMemAllocTag(size, data->unk0E);
    bcopy(buffer, data->unk3C->unk10, size);
    HuMemFree(buffer);
    gfx = HuMemAlloc(0x10000);
    {
        Gfx *textureHeader = gfx;
        buffer = (u8 *)gfx;
        gfx++;
        gSPTexture(textureHeader, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->unk1A >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->unk18 == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->unk0C);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->unk0C);
        }
        gDPPipeSync(gfx++);
        format = G_IM_FMT_CI;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = sprite->unk18;
        format = ((u32)format / 0x8000) * 4;
    }
    switch (sprite->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                   G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 1, osVirtualToPhysical(data->unk44[0]));
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, -1);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    data->unk3C->unk14 = HuMemAllocTag(size, data->unk0E);
    bcopy(buffer, data->unk3C->unk14, size);
    HuMemFree(buffer);
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], color[3]);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[D_800D2008_main + 1];
    return model;
}

void func_8010D4C0_baby_bowser_broadside(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame) {
    HmfModel *modelData = HmfModelData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[D_800D2008_main + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->unk00[frame].unk00));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPPipeSync(gfx + 3);
    gSPEndDisplayList(gfx + 4);
}

void func_8010D590_baby_bowser_broadside(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color) {
    HmfModel *modelData = HmfModelData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[D_800D2008_main + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->unk00[frame].unk00));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPSetPrimColor(gfx + 3, 0, 0, color[0], color[1], color[2], color[3]);
    gDPPipeSync(gfx + 4);
    gSPDisplayList(gfx + 5, osVirtualToPhysical(data->unk3C->unk14));
    gDPPipeSync(gfx + 6);
    gSPEndDisplayList(gfx + 7);
}

s16 func_8010D6C4_baby_bowser_broadside(HuSprite_Unk84_Struct *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset) {
    s32 capacity = 0x1000;
    s32 width, height, scaledWidth, scaledHeight;
    s32 size, slices, textureHeight, sliceHeight, vertexCount;
    s32 i, j;
    Vtx_t *vertices, *start;

    if (sprite->unk1A >= 2) {
        capacity = 0x800;
    }
    width = sprite->unk00->unk04;
    height = sprite->unk00->unk06;
    scaledWidth = width * 100 * (f64)scale / D_8010FFE8_baby_bowser_broadside;
    scaledHeight = height * 100 * (f64)scale / D_8010FFE8_baby_bowser_broadside;
    if ((sprite->unk18 & 0xFFF) == 4) {
        size = ((width + 1) & 0xFFFE) * height * 4;
    } else {
        size = width * height * sprite->unk18;
    }
    size /= 8;
    slices = size / capacity;
    if (slices <= 0) {
        slices = 1;
    }
    textureHeight = height / slices;
    sliceHeight = scaledHeight / slices;
    vertexCount = slices * 4;
    size = slices * 4 * sizeof(Vtx_t);
    start = vertices = HuMemAllocTag(size, data->unk0E);
    memset(start, 0, size);
    for (i = 0; i < slices; i++, vertices += 4) {
        vertices[0].ob[0] = scaledWidth * D_8010FFF0_baby_bowser_broadside;
        vertices[0].ob[1] = scaledHeight * D_8010FFF0_baby_bowser_broadside - sliceHeight * i;
        vertices[0].tc[0] = (width - 1) << 6;
        vertices[0].tc[1] = 0;
        vertices[1].ob[0] = scaledWidth * D_8010FFF0_baby_bowser_broadside;
        vertices[1].ob[1] = scaledHeight * D_8010FFF0_baby_bowser_broadside - sliceHeight * (i + 1);
        vertices[1].tc[0] = (width - 1) << 6;
        vertices[1].tc[1] = (textureHeight - 1) << 6;
        vertices[2].ob[0] = -(scaledWidth * D_8010FFF0_baby_bowser_broadside);
        vertices[2].ob[1] = scaledHeight * D_8010FFF0_baby_bowser_broadside - sliceHeight * i;
        vertices[2].tc[0] = 0;
        vertices[2].tc[1] = 0;
        vertices[3].ob[0] = -(scaledWidth * D_8010FFF0_baby_bowser_broadside);
        vertices[3].ob[1] = scaledHeight * D_8010FFF0_baby_bowser_broadside - sliceHeight * (i + 1);
        vertices[3].tc[0] = 0;
        vertices[3].tc[1] = (textureHeight - 1) << 6;
        for (j = 0; j < 4; j++) {
            vertices[j].ob[0] += xOffset;
            vertices[j].ob[1] += yOffset;
            vertices[j].ob[2] = 0;
            vertices[j].flag = 0;
            vertices[j].cn[3] = 255;
            vertices[j].cn[0] = vertices[j].cn[1] = vertices[j].cn[2] = 0;
        }
    }
    vertices = start;
    for (i = 0; i < D_800D1FF0_main; i++) {
        Vtx_t *destination;
        Vtx_t *source;
        data->unk44[i] = HuMemAllocTag(vertexCount * sizeof(Vtx_t), data->unk0E);
        destination = (Vtx_t *)data->unk44[i];
        source = vertices;
        for (j = 0; j < vertexCount; j++) {
            *destination++ = *source++;
        }
    }
    HuMemFree(start);
    return slices;
}

void func_8010DAE8_baby_bowser_broadside(s32 arg0, BabyBowserBroadsideHandler *arg1) {
    D_80110020_baby_bowser_broadside = HuMemAllocTag(0xAB0, TAG_OVERLAY);
    memset(D_80110020_baby_bowser_broadside, 0, 0xAB0);
    arg1->unk_40 = func_8010DE70_baby_bowser_broadside;
}

s16 func_8010DB38_baby_bowser_broadside(s16 model, Vec *vertices, s16 count, f32 arg3, f32 arg4, s32 flags) {
    BabyBowserBroadsideBoat *boat = D_80110020_baby_bowser_broadside;
    s16 i;
    for (i = 0; i < 12; i++, boat++) {
        if (boat->unk_04 == 0) {
            if (model != -1) {
                boat->x = &HmfModelData[model].pos.x;
                boat->y = &HmfModelData[model].pos.y;
                boat->z = &HmfModelData[model].pos.z;
                boat->rx = &HmfModelData[model].rot.x;
                boat->ry = &HmfModelData[model].rot.y;
                boat->rz = &HmfModelData[model].rot.z;
            }
            memcpy(boat->vertices, vertices, count * sizeof(Vec));
            boat->unk_DC = arg3;
            boat->unk_C4 = arg4;
            boat->vertexCount = count;
            if ((u32)(flags & 0x700) <= 0x100) {
                func_8010F3C4_baby_bowser_broadside(boat->vertices, &boat->plane);
                boat->unk_00 = flags;
            } else {
                flags &= ~4;
                boat->unk_00 = flags;
            }
            boat->unk_04 = 1;
            break;
        }
    }
    return i;
}

s16 func_8010DC88_baby_bowser_broadside(s16 index, s32 flags) {
    BabyBowserBroadsideBoat *boat = D_80110020_baby_bowser_broadside;
    BabyBowserBroadsideBoat *source = &D_80110020_baby_bowser_broadside[index];
    s16 i;
    for (i = 0; i < 12; i++, boat++) {
        if (boat->unk_04 == 0) {
            boat->source = index;
            boat->x = source->x;
            boat->y = source->y;
            boat->z = source->z;
            boat->rx = source->rx;
            boat->ry = source->ry;
            boat->rz = source->rz;
            memcpy(boat->vertices, source->vertices, source->vertexCount * sizeof(Vec));
            boat->unk_DC = source->unk_DC;
            boat->unk_C4 = source->unk_C4;
            boat->vertexCount = source->vertexCount;
            if ((u32)(flags & 0x700) <= 0x100) {
                boat->plane.normal = source->plane.normal;
            } else {
                flags &= ~4;
            }
            boat->unk_00 = flags | 0x40;
            boat->unk_04 = 1;
            break;
        }
    }
    return i;
}

void func_8010DDDC_baby_bowser_broadside(s16 index, Vec *vertices, f32 arg2) {
    BabyBowserBroadsideBoat *boat;
    Vec *destination;

    if (index >= 12) {
        return;
    }
    if (D_80110020_baby_bowser_broadside[index].unk_04 == 0) {
        return;
    }
    boat = &D_80110020_baby_bowser_broadside[index];
    destination = boat->vertices;
    memcpy(destination, vertices, boat->vertexCount * sizeof(Vec));
    boat->unk_C4 = arg2;
    func_8010F3C4_baby_bowser_broadside(destination, &boat->plane);
}

void func_8010DE70_baby_bowser_broadside(void) {
    BabyBowserBroadsideBoat *boat = D_80110020_baby_bowser_broadside;
    s16 i;

    if (boat != NULL) {
        for (i = 0; i < 12; i++, boat++) {
            if (boat->unk_04 != 0 && !(boat->unk_00 & 1)) {
                if (!(boat->unk_00 & 0x40)) {
                    if (boat->unk_00 & 8) {
                        func_8010FB74_baby_bowser_broadside(*boat->x, *boat->y, *boat->z,
                                                            *boat->rx, *boat->ry, *boat->rz, boat->matrix[0]);
                        func_8010FC2C_baby_bowser_broadside(boat->vertices, boat->vertexCount, boat->matrix[0], boat->transformed);
                    } else {
                        func_8010F878_baby_bowser_broadside(boat->matrix[0]);
                        func_8010FC2C_baby_bowser_broadside(boat->vertices, boat->vertexCount, boat->matrix[0], boat->transformed);
                    }
                    if (boat->unk_00 & 4) {
                        func_8010F3C4_baby_bowser_broadside(boat->transformed, &boat->plane);
                    }
                } else {
                    memcpy(&boat->transformed[0], D_80110020_baby_bowser_broadside[boat->source].transformed,
                           boat->vertexCount * sizeof(Vec));
                    if (boat->unk_00 & 4) {
                        boat->plane = D_80110020_baby_bowser_broadside[boat->source].plane;
                    }
                }
            }
        }
    }
}

void func_8010E018_baby_bowser_broadside(BabyBowserBroadsideShip *ship, s16 count, f32 speed, s16 model) {
    if (ship != NULL) {
        ship->unk_08 = count + 1;
        ship->unk_04 = HuMemAllocTag(ship->unk_08 * sizeof(s16), TAG_OVERLAY);
        memset(ship->unk_04, -1, ship->unk_08 * sizeof(s16));
        ship->pos.x = ship->pos.y = ship->pos.z = 0.0f;
        ship->facing.x = ship->facing.y = ship->facing.z = 0.0f;
        ship->unk_24 = speed;
        ship->unk_28 = model;
    }
}

void func_8010E0B0_baby_bowser_broadside(BabyBowserBroadsideShip *ship) {
    BabyBowserBroadsideBoat *boat;
    s16 i;

    if (D_80110020_baby_bowser_broadside == NULL) {
        return;
    }
    ship->unk_30 = 0;
    ship->unk_2A = 0;
    ship->unk_2C = 0;
    ship->unk_2E = 0;
    ship->unk_00 &= ~1;
    if (ship->unk_28 != -1) {
        ship->pos.x = HmfModelData[ship->unk_28].pos.x;
        ship->pos.y = HmfModelData[ship->unk_28].pos.y;
        ship->pos.z = HmfModelData[ship->unk_28].pos.z;
    }
    for (i = 1; i < ship->unk_08; i++) {
        if (ship->unk_04[i] != -1) {
            boat = &D_80110020_baby_bowser_broadside[ship->unk_04[i]];
            if (!(boat->unk_00 & 1)) {
                if (boat->unk_00 & 0x400) {
                    if ((s16)func_8010E348_baby_bowser_broadside(boat, ship) != 0) {
                        if (boat->unk_00 & 0x80) {
                            ship->unk_00 |= 1;
                        } else {
                            ship->unk_30 = i;
                        }
                    }
                } else if (boat->unk_00 & 0x200) {
                    if ((s16)func_8010E538_baby_bowser_broadside(boat, ship) != 0) {
                        if (boat->unk_00 & 0x80) {
                            ship->unk_00 |= 1;
                        } else {
                            ship->unk_2E = i;
                        }
                    }
                } else if (boat->unk_00 & 0x100) {
                    if ((s16)func_8010E710_baby_bowser_broadside(boat, ship) != 0) {
                        ship->unk_2A = i;
                    }
                } else {
                    if ((s16)func_8010EDC0_baby_bowser_broadside(boat, ship) != 0) {
                        if (boat->unk_00 & 0x80) {
                            ship->unk_00 |= 1;
                        } else {
                            ship->unk_2C = i;
                        }
                    }
                }
            }
        }
    }
    ship->pos.x += ship->facing.x;
    ship->pos.y += ship->facing.y;
    ship->pos.z += ship->facing.z;
    if (ship->unk_28 != -1) {
        HmfModelData[ship->unk_28].pos.x = ship->pos.x;
        HmfModelData[ship->unk_28].pos.y = ship->pos.y;
        HmfModelData[ship->unk_28].pos.z = ship->pos.z;
    }
}

s32 func_8010E348_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, BabyBowserBroadsideShip *ship) {
    f32 bounds[2];
    Vec position;
    Vec movement;
    Vec next;
    Vec difference;
    f32 distance;
    f32 radius;

    position.x = ship->pos.x;
    position.y = ship->pos.y;
    position.z = ship->pos.z;
    movement.x = ship->facing.x;
    movement.y = ship->facing.y;
    movement.z = ship->facing.z;
    next.x = position.x + movement.x;
    next.y = position.y + movement.y;
    next.z = position.z + movement.z;
    radius = ship->unk_24;
    bounds[0] = boat->transformed[0].y - radius * 0.5f;
    bounds[1] = boat->transformed[0].y + boat->unk_C4 + radius * 0.5f;
    if (next.y < bounds[0] || next.y > bounds[1]) {
        return 0;
    } else {
        difference.x = boat->transformed[0].x - next.x;
        difference.z = boat->transformed[0].z - next.z;
        distance = HuSqrtf(difference.x * difference.x + difference.z * difference.z);
        if (distance <= ship->unk_24 + boat->unk_DC) {
            if (boat->unk_00 & 0x10) {
                return 1;
            }
            if (distance != 0.0f) {
                difference.x /= distance;
                difference.x = (ship->unk_24 + boat->unk_DC) * difference.x;
                difference.z /= distance;
                difference.z = (ship->unk_24 + boat->unk_DC) * difference.z;
            }
            next.x = boat->transformed[0].x - difference.x;
            next.z = boat->transformed[0].z - difference.z;
        } else {
            return 0;
        }
    }
    movement.x = next.x - position.x;
    movement.z = next.z - position.z;
    ship->facing.x = movement.x;
    ship->facing.y = movement.y;
    ship->facing.z = movement.z;
    return 1;
}

s32 func_8010E538_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, BabyBowserBroadsideShip *ship) {
    Vec position;
    Vec movement;
    Vec next;
    Vec difference;
    f32 distance;

    position.x = ship->pos.x;
    position.y = ship->pos.y;
    position.z = ship->pos.z;
    movement.x = ship->facing.x;
    movement.y = ship->facing.y;
    movement.z = ship->facing.z;
    next.x = position.x + movement.x;
    next.y = position.y + movement.y;
    next.z = position.z + movement.z;
    difference.x = boat->transformed[0].x - next.x;
    difference.y = boat->transformed[0].y - next.y;
    difference.z = boat->transformed[0].z - next.z;
    distance = HuSqrtf(difference.x * difference.x + difference.y * difference.y + difference.z * difference.z);
    if (distance <= ship->unk_24 + boat->unk_DC) {
        if (boat->unk_00 & 0x10) {
            return 1;
        }
        if (distance != 0.0f) {
            difference.x /= distance;
            difference.x *= ship->unk_24 + boat->unk_DC;
            difference.y /= distance;
            difference.y *= ship->unk_24 + boat->unk_DC;
            difference.z /= distance;
            difference.z *= ship->unk_24 + boat->unk_DC;
        }
        next.x = boat->transformed[0].x - difference.x;
        next.y = boat->transformed[0].y - difference.y;
        next.z = boat->transformed[0].z - difference.z;
    } else {
        return 0;
    }
    movement.x = next.x - position.x;
    movement.y = next.y - position.y;
    movement.z = next.z - position.z;
    ship->facing.x = movement.x;
    ship->facing.y = movement.y;
    ship->facing.z = movement.z;
    return 1;
}

s32 func_8010E710_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, BabyBowserBroadsideShip *ship) {
    Vec normal;
    Vec position;
    Vec movement;
    Vec next;
    Vec contact;
    f32 constant;
    f32 side;
    f32 distance;
    f32 radius;
    s16 result;

    normal.x = boat->plane.normal.x;
    normal.y = boat->plane.normal.y;
    normal.z = boat->plane.normal.z;
    constant = -boat->plane.constant;
    position.x = ship->pos.x;
    position.y = ship->pos.y;
    position.z = ship->pos.z;
    movement.x = ship->facing.x;
    movement.y = ship->facing.y;
    movement.z = ship->facing.z;
    if (!(boat->unk_00 & 0x20)) {
        side = normal.x * position.x + normal.y * position.y + normal.z * position.z + constant;
        if (side < 0.0f) {
            return 0;
        }
    }
    next.x = position.x + movement.x;
    next.y = position.y + movement.y;
    next.z = position.z + movement.z;
    if (!(boat->unk_00 & 0x20)) {
        side = normal.x * next.x + normal.y * next.y + normal.z * next.z + constant;
        distance = func_8010ED1C_baby_bowser_broadside(boat, &next);
        if (side > 0.0f) {
            radius = ship->unk_24;
            if (distance > 0.0f ? radius <= distance : radius <= -distance) {
                return 0;
            }
        }
    } else {
        distance = func_8010ED1C_baby_bowser_broadside(boat, &next);
        radius = ship->unk_24;
        if (distance > 0.0f ? radius <= distance : radius <= -distance) {
            return 0;
        }
    }
    contact.x = -normal.x * distance + next.x;
    contact.y = -normal.y * distance + next.y;
    contact.z = -normal.z * distance + next.z;
    result = func_8010E9FC_baby_bowser_broadside(boat, &contact);
    if (result != 0) {
        if (boat->unk_00 & 0x10) {
            return 1;
        }
        next.x = normal.x * ship->unk_24 * 1.01f + contact.x;
        next.y = normal.y * ship->unk_24 * 1.01f + contact.y;
        next.z = normal.z * ship->unk_24 * 1.01f + contact.z;
        movement.x = next.x - position.x;
        movement.y = next.y - position.y;
        movement.z = next.z - position.z;
        ship->facing.x = movement.x;
        ship->facing.y = movement.y;
        ship->facing.z = movement.z;
    }
    return result;
}

s16 func_8010E9FC_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, Vec *point) {
    Vec edge;
    Vec offset;
    f32 cross;
    s16 i;
    s16 next;

    switch (boat->plane.axis) {
        case 0:
            for (i = 0; i < boat->vertexCount; i++) {
                next = i + 1;
                next = next != boat->vertexCount ? next : 0;
                edge.y = boat->transformed[next].y - boat->transformed[i].y;
                edge.z = boat->transformed[next].z - boat->transformed[i].z;
                offset.y = point->y - boat->transformed[i].y;
                offset.z = point->z - boat->transformed[i].z;
                cross = edge.y * offset.z - edge.z * offset.y;
                if (cross * boat->plane.normal.x < 0.0f) {
                    return 0;
                }
            }
            break;
        case 1:
            for (i = 0; i < boat->vertexCount; i++) {
                next = i + 1;
                next = next != boat->vertexCount ? next : 0;
                edge.x = boat->transformed[next].x - boat->transformed[i].x;
                edge.z = boat->transformed[next].z - boat->transformed[i].z;
                offset.x = point->x - boat->transformed[i].x;
                offset.z = point->z - boat->transformed[i].z;
                cross = edge.z * offset.x - edge.x * offset.z;
                if (cross * boat->plane.normal.y < 0.0f) {
                    return 0;
                }
            }
            // The Y-axis case also checks the polygon's XY projection.
            // Fall through.
        case 2:
            for (i = 0; i < boat->vertexCount; i++) {
                next = i + 1;
                next = next != boat->vertexCount ? next : 0;
                edge.x = boat->transformed[next].x - boat->transformed[i].x;
                edge.y = boat->transformed[next].y - boat->transformed[i].y;
                offset.x = point->x - boat->transformed[i].x;
                offset.y = point->y - boat->transformed[i].y;
                cross = edge.x * offset.y - edge.y * offset.x;
                if (cross * boat->plane.normal.z < 0.0f) {
                    return 0;
                }
            }
            break;
    }
    return 1;
}

f32 func_8010ED1C_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, Vec *point) {
    f32 x = point->x;
    f32 y = point->y;
    f32 z = point->z;
    Vec normal;
    f32 length;

    normal.x = boat->plane.normal.x;
    normal.y = boat->plane.normal.y;
    normal.z = boat->plane.normal.z;
    length = HuSqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    return (x * normal.x + y * normal.y + z * normal.z - boat->plane.constant) / length;
}

s32 func_8010EDC0_baby_bowser_broadside(BabyBowserBroadsideBoat *boat, BabyBowserBroadsideShip *ship) {
    f32 side;
    f32 edge;
    s16 i;
    s16 next;

    if (!(boat->unk_00 & 2) && ship->pos.y > boat->unk_C4) {
        return 0;
    }
    side = func_8010F004_baby_bowser_broadside(ship, &boat->transformed[0], &boat->transformed[1]);
    if (side == 0.0f) {
        return 0;
    }
    if (side > 0.0f) {
        for (i = 1; i < boat->vertexCount; i++) {
            next = i + 1;
            next = next != boat->vertexCount ? next : 0;
            edge = func_8010F004_baby_bowser_broadside(ship, &boat->transformed[i], &boat->transformed[next]);
            if (edge == 0.0f) {
                return 1;
            }
            if (edge < 0.0f) {
                return 0;
            }
        }
    } else {
        for (i = 1; i < boat->vertexCount; i++) {
            next = i + 1;
            next = next != boat->vertexCount ? next : 0;
            edge = func_8010F004_baby_bowser_broadside(ship, &boat->transformed[i], &boat->transformed[next]);
            if (edge == 0.0f) {
                return 1;
            }
            if (edge > 0.0f) {
                return 0;
            }
        }
    }
    return 1;
}

f32 func_8010F004_baby_bowser_broadside(BabyBowserBroadsideShip *arg0, Vec *arg1, Vec *arg2) {
    Vec shipPos;
    Vec ma;
    Vec mb;

    shipPos.x = arg0->pos.x;
    shipPos.z = arg0->pos.z;
    ma.x = arg1->x - shipPos.x;
    ma.z = arg1->z - shipPos.z;
    mb.x = arg2->x - shipPos.x;
    mb.z = arg2->z - shipPos.z;
    return ma.z * mb.x - ma.x * mb.z;
}

s32 func_8010F060_baby_bowser_broadside(f32 *arg0, u8 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 t = *arg1 / arg4;
    u8 step;

    *arg0 = arg2 + (arg3 - arg2) * t;
    step = *arg1 + 1;
    *arg1 = step;
    if (arg4 < (f32)step) {
        *arg1 = 0;
        *arg0 = arg3;
        return 1;
    }
    return 0;
}

f32 func_8010F0D8_baby_bowser_broadside(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 d;

    if (1.0f < arg0) {
        arg0 = 1.0f;
    }
    d = 1.0f - arg0;
    return d * d * arg1 + (d + d) * arg0 * arg2 + arg0 * arg0 * arg3;
}

void func_8010F144_baby_bowser_broadside(u16 *order, s16 count) {
    s16 i;
    s16 index;
    s32 random;
    u16 temp;

    for (i = 0; i < count; i++) {
        order[i] = i;
    }
    for (i = count - 1; i >= 0; i--) {
        random = rand16();
        index = random % (i + 1);
        temp = order[i];
        order[i] = order[index];
        order[index] = temp;
    }
}

void func_8010F250_baby_bowser_broadside(omObjData *object) {
    HmfModel *model = &HmfModelData[object->model[0]];

    object->scale.x = model->scale.x;
    object->scale.y = model->scale.y;
    object->scale.z = model->scale.z;
    object->trans.x = model->pos.x;
    object->trans.y = model->pos.y;
    object->trans.z = model->pos.z;
    if (model->rot.x >= 360.0f) {
        model->rot.x -= 360.0f;
    }
    if (model->rot.x < 0.0f) {
        model->rot.x += 360.0f;
    }
    if (model->rot.y >= 360.0f) {
        model->rot.y -= 360.0f;
    }
    if (model->rot.y < 0.0f) {
        model->rot.y += 360.0f;
    }
    if (model->rot.z >= 360.0f) {
        model->rot.z -= 360.0f;
    }
    if (model->rot.z < 0.0f) {
        model->rot.z += 360.0f;
    }
    object->rot.x = model->rot.x;
    object->rot.y = model->rot.y;
    object->rot.z = model->rot.z;
}

void func_8010F3C4_baby_bowser_broadside(Vec *vertices, BabyBowserBroadsidePlane *plane) {
    f32 firstX, firstY, firstZ, secondX, secondY, secondZ;
    f32 normal[3];
    f32 length;
    f32 magnitude;
    s16 axis, i;

    firstX = vertices[1].x - vertices[0].x;
    firstY = vertices[1].y - vertices[0].y;
    firstZ = vertices[1].z - vertices[0].z;
    secondX = vertices[2].x - vertices[0].x;
    secondY = vertices[2].y - vertices[0].y;
    secondZ = vertices[2].z - vertices[0].z;
    normal[0] = firstY * secondZ - firstZ * secondY;
    normal[1] = firstZ * secondX - firstX * secondZ;
    normal[2] = firstX * secondY - firstY * secondX;
    length = HuSqrtf(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    if (length != 0.0f) {
        normal[0] /= length;
        normal[1] /= length;
        normal[2] /= length;
    }
    plane->constant = normal[0] * vertices[0].x + normal[1] * vertices[0].y + normal[2] * vertices[0].z;
    axis = 0;
    for (i = 1; i < 3; i++) {
        magnitude = normal[axis] > 0.0f ? normal[axis] : -normal[axis];
        if (normal[i] > 0.0f ? magnitude < normal[i] : magnitude < -normal[i]) {
            axis = i;
        }
    }
    plane->normal.x = normal[0];
    plane->normal.y = normal[1];
    plane->normal.z = normal[2];
    plane->axis = axis;
}

void func_8010F5C8_baby_bowser_broadside(Vec from, Vec to, f32 *angles) {
    Vec difference;
    f32 angle;
    f32 fullRotation = 360.0f;

    difference.x = to.x - from.x;
    difference.y = to.y - from.y;
    difference.z = to.z - from.z;
    angle = atan2df(difference.y, sqrtf(difference.x * difference.x + difference.z * difference.z));
    if (angle < 0.0f) {
        angle += fullRotation;
    } else if (angle >= fullRotation) {
        angle -= fullRotation;
    }
    *angles++ = angle;
    angle = atan2df(difference.x, difference.z);
    if (angle < 0.0f) {
        angle += fullRotation;
    } else if (angle >= fullRotation) {
        angle -= fullRotation;
    }
    *angles = angle;
}

void func_8010F6F8_baby_bowser_broadside(f32 *angle, f32 *target) {
    f32 difference;

    while (*target < 0.0f) {
        *target += 360.0f;
    }
    while (*target >= 360.0f) {
        *target -= 360.0f;
    }
    while (*angle < 0.0f) {
        *angle += 360.0f;
    }
    while (*angle >= 360.0f) {
        *angle -= 360.0f;
    }
    difference = *target - *angle;
    if (!(difference > 0.0f)) {
        difference = -difference;
    }
    if (difference > 180.0f) {
        if (*angle < *target) {
            *target -= 360.0f;
        } else {
            *angle -= 360.0f;
        }
    }
}

void func_8010F878_baby_bowser_broadside(f32 *arg0) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            arg0[i * 4 + j] = 0.0f;
        }
        arg0[i * 4 + i] = 1.0f;
    }
}

void func_8010F900_baby_bowser_broadside(f32 *matrix, f32 x, f32 y, f32 z) {
    func_8010F878_baby_bowser_broadside(matrix);
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void func_8010F958_baby_bowser_broadside(f32 *matrix, f32 angle) {
    func_8010F878_baby_bowser_broadside(matrix);
    matrix[5] = cosdf(angle);
    matrix[6] = sindf(angle);
    matrix[9] = -sindf(angle);
    matrix[10] = cosdf(angle);
}

void func_8010F9C0_baby_bowser_broadside(f32 *matrix, f32 angle) {
    func_8010F878_baby_bowser_broadside(matrix);
    matrix[0] = cosdf(angle);
    matrix[2] = -sindf(angle);
    matrix[8] = sindf(angle);
    matrix[10] = cosdf(angle);
}

void func_8010FA28_baby_bowser_broadside(f32 *left, f32 *right, f32 *output) {
    s16 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            output[i * 4 + j] = left[i * 4] * right[j] + left[i * 4 + 1] * right[4 + j] +
                                left[i * 4 + 2] * right[8 + j] + left[i * 4 + 3] * right[12 + j];
        }
    }
}

void func_8010FADC_baby_bowser_broadside(f32 *matrix, f32 *output) {
    *output++ = matrix[12] * matrix[0] + matrix[13] * matrix[4] + matrix[14] * matrix[8];
    *output++ = matrix[12] * matrix[1] + matrix[13] * matrix[5] + matrix[14] * matrix[9];
    *output = matrix[12] * matrix[2] + matrix[13] * matrix[6] + matrix[14] * matrix[10];
}

void func_8010FB74_baby_bowser_broadside(f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 *matrix) {
    f32 translation[16];
    f32 rotationX[16];
    f32 rotationY[16];
    f32 rotation[16];

    func_8010F900_baby_bowser_broadside(translation, x, y, z);
    func_8010F958_baby_bowser_broadside(rotationX, rx);
    func_8010F9C0_baby_bowser_broadside(rotationY, ry);
    func_8010FA28_baby_bowser_broadside(rotationX, rotationY, rotation);
    func_8010FA28_baby_bowser_broadside(rotation, translation, matrix);
}

void func_8010FC2C_baby_bowser_broadside(Vec *vertices, s16 count, f32 *matrix, Vec *output) {
    s16 i;

    for (i = 0; i < count; i++) {
        output[i].x = (matrix[12] + vertices[i].x) * matrix[0] +
                      (matrix[13] + vertices[i].y) * matrix[4] +
                      (matrix[14] + vertices[i].z) * matrix[8];
        output[i].y = (matrix[12] + vertices[i].x) * matrix[1] +
                      (matrix[13] + vertices[i].y) * matrix[5] +
                      (matrix[14] + vertices[i].z) * matrix[9];
        output[i].z = (matrix[12] + vertices[i].x) * matrix[2] +
                      (matrix[13] + vertices[i].y) * matrix[6] +
                      (matrix[14] + vertices[i].z) * matrix[10];
    }
}
