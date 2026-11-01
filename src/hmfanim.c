#include "common.h"
#include "gcc/string.h"
#include "mallocblock.h"

extern HmfPaletteData *D_800CD2F8_main;
extern HmfData_Unk84_Entry2 *D_800D1FCC_main;
extern u8 D_800CCF85_main;
extern HmfData_Unk84_Entry2 D_800A1190_main;
extern Gfx *gMainGfxPos;

s16 func_80011334_main(HmfData *, void *, s16);
s16 func_80011460_main(u8 *);
HmfData_Unk84_Entry2 *func_80031A60_main(HmfData *hmf, char *name);
void func_80032194_main(HmfPaletteData *pal);
void func_8003235C_main(void);
void func_80031B30_main(u8 *chunk, HmfData *hmf, HmfData_Unk84_Entry2 *tex);
void func_80031DF4_main(HmfData *hmf);
HmfPaletteData *func_80032038_main(HmfData *hmf, s16 index);
void func_800321B8_main(u8 *data, HmfData *hmf, HmfPaletteData *pal);
u8 *func_80010A38_main(s32 tag, void *start, void *end);
void *func_80010AC8_main(void *chunk);
void func_800333B0_main(s16 animIdx);
s16 func_800329B4_main(u8 *data);
s16 func_80033F8C_main(void);
s16 func_80033FEC_main(void);
s16 func_80033D0C_main(HmfData *hmf, u8 *data);
void func_80032950_main(void);

void func_80031560_main(void) {
    s16 i;

    D_800D1FCC_main = HuMemAlloc(0x1A00);
    D_800CD2F8_main = HuMemAlloc(0x1600);
    for (i = 0; i < 0x80; i++) {
        D_800D1FCC_main[i].nameHash = 0;
    }
    for (i = 0; i < 0x80; i++) {
        D_800CD2F8_main[i].nameHash = 0;
    }
    D_800CCF85_main = 0;
    func_8003235C_main();
}

void func_80031630_main(HmfData *hmf) {
    char name[0x20];
    HmfData_Unk84_Entry2 *tex;
    u8 *chunk;
    s16 hash;
    s16 i;

    func_80031DF4_main(hmf);
    for (chunk = hmf->unk34; chunk < hmf->unk30; chunk = func_80010AC8_main(chunk + 4)) {
        chunk = func_80010A38_main(0x424D5031, chunk, hmf->unk30); // "BMP1"
        if (chunk == NULL) {
            return;
        }
        hash = func_80011334_main(hmf, name, (chunk[8] << 8) + chunk[9]);
        for (i = 0; i < 0x80; i++) {
            if (D_800D1FCC_main[i].nameHash == hash && strcmp(D_800D1FCC_main[i].name, name) == 0) {
                break;
            }
        }
        if (i == 0x80) {
            for (i = 0; i < 0x80; i++) {
                if (D_800D1FCC_main[i].nameHash == 0) {
                    break;
                }
            }
            if (i == 0x80) {
                osSyncPrintf("TEXTURE OVER!\n");
                return;
            }
            tex = &D_800D1FCC_main[i];
            tex->nameHash = hash;
            strcpy(tex->name, name);
            tex->owner = hmf;
            func_80031B30_main(chunk, hmf, tex);
        } else {
            tex = &D_800D1FCC_main[i];
            if (D_800CCF85_main & 2) {
                func_80019C00_main(tex->unk28);
                tex->owner = hmf;
                func_80031B30_main(chunk, hmf, tex);
            }
        }
    }
}

void func_8003186C_main(HmfData *hmf) {
    HmfData_Unk84_Entry2 *tex;
    HmfData *other;
    s16 i;
    s16 j;
    s16 k;

    if (hmf->unk84 == NULL) {
        return;
    }
    for (i = 0; i < hmf->unk12; i++) {
        tex = hmf->unk84[i].unkC;
        if (tex->nameHash == 0) {
            continue;
        }
        for (j = 0; j < 0x80; j++) {
            other = HmfModelData[j].hmf;
            if (other == NULL || HmfModelData[j].unk00 != 0 || hmf == other || other->unk84 == NULL) {
                continue;
            }
            for (k = 0; k < other->unk12; k++) {
                if (other->unk84[k].unkC == tex) {
                    break;
                }
            }
            if (k != other->unk12) {
                break;
            }
        }
        if (j == 0x80) {
            tex->nameHash = 0;
            tex->owner = NULL;
            if (tex->unk1C == 2) {
                func_80032194_main(tex->unk_30);
            }
            func_80019C00_main(tex->unk28);
        }
    }
}

HmfData_Unk84_Entry2 *func_80031A08_main(HmfData *hmf, s16 index) {
    char name[0x20];

    func_80011334_main(hmf, name, index);
    return func_80031A60_main(hmf, name);
}

HmfData_Unk84_Entry2 *func_80031A44_main(HmfData *hmf, char *name) {
    return func_80031A60_main(hmf, name);
}

HmfData_Unk84_Entry2 *func_80031A60_main(HmfData *hmf, char *name) {
    u16 hash = func_80011460_main((u8 *)name);
    u16 i;

    for (i = 0; i < 0x80; i++) {
        if (D_800D1FCC_main[i].nameHash != 0 && D_800D1FCC_main[i].nameHash == hash &&
            strcmp(D_800D1FCC_main[i].name, name) == 0) {
            break;
        }
    }
    if (i == 0x80) {
        return NULL;
    }
    return &D_800D1FCC_main[i];
}

void func_80031B30_main(u8 *data, HmfData *hmf, HmfData_Unk84_Entry2 *tex) {
    u16 bpp;
    s32 size;
    u8 *dst;
    u16 i;
    u16 pixel;

    data += 0xB;
    tex->unk24 = (data[2] << 8) + data[3];
    tex->unk26 = (data[4] << 8) + data[5];
    if (data[0] == 0x28) {
        tex->unk1C = 2;
        tex->unk_30 = func_80032038_main(hmf, (data[6] << 8) + data[7]);
        tex->unk20 = (data[8] << 8) + data[9];
        tex->unk1D = 1;
        if (tex->unk_30->colorCount <= 16) {
            bpp = 1;
        } else {
            bpp = 2;
        }
        data += 4;
    } else {
        switch (data[1]) {
            case 8:
                tex->unk1D = 1;
                bpp = 2;
                break;
            case 16:
                tex->unk1D = 2;
                bpp = 4;
                break;
            case 4:
                tex->unk1D = 0;
                bpp = 1;
                break;
            case 32:
                tex->unk1D = 3;
                bpp = 8;
                break;
            default:
                tex->unk1D = 2;
                bpp = 6;
                break;
        }
        switch (data[0]) {
            case 0x26:
                tex->unk1C = 0;
                break;
            case 0x27:
                tex->unk1C = 0;
                break;
            case 0x25:
                tex->unk1C = 3;
                break;
            default:
                tex->unk1C = 4;
                break;
        }
    }
    size = tex->unk24 * tex->unk26 * bpp / 2;
    tex->unk1F = 0;
    if (bpp != 6) {
        if ((tex->unk1C == 2 && size > 0x800) || size > 0x1000) {
            tex->unk1F |= 1;
        }
        tex->unk28 = HuMemAllocTag(size, TAG_TEXTURE);
        bcopy(data + 0xA, tex->unk28, size);
    } else {
        size = size / 3 * 2;
        if (size > 0x1000) {
            tex->unk1F |= 1;
        }
        tex->unk28 = HuMemAllocTag(size, TAG_TEXTURE);
        dst = tex->unk28;
        data += 0xA;
        for (i = 0; i < size; i += 2) {
            /* Only the first byte of each RGB triple contributes to the pixel. */
            pixel = ((data[0] & 0xF8) << 8) + ((data[0] & 0xF8) << 3) + ((data[0] & 0xF8) >> 2) + 1;
            data++;
            data++;
            data++;
            *dst++ = pixel >> 8;
            *dst++ = pixel;
        }
    }
}

void func_80031DF4_main(HmfData *hmf) {
    char name[0x20];
    HmfPaletteData *pal;
    u8 *chunk;
    s16 hash;
    s16 i;

    for (chunk = hmf->unk34; chunk < hmf->unk30; chunk = func_80010AC8_main(chunk + 4)) {
        chunk = func_80010A38_main(0x50414C31, chunk, hmf->unk30); // "PAL1"
        if (chunk == NULL) {
            return;
        }
        hash = func_80011334_main(hmf, name, (chunk[8] << 8) + chunk[9]);
        for (i = 0; i < 0x80; i++) {
            if (D_800CD2F8_main[i].nameHash == hash && strcmp(D_800CD2F8_main[i].name, name) == 0) {
                break;
            }
        }
        if (i == 0x80) {
            for (i = 0; i < 0x80; i++) {
                if (D_800CD2F8_main[i].nameHash == 0) {
                    break;
                }
            }
            if (i == 0x80) {
                return;
            }
            pal = &D_800CD2F8_main[i];
            pal->nameHash = hash;
            strcpy(pal->name, name);
            pal->owner = hmf;
            pal->refCount = 1;
            func_800321B8_main(chunk, hmf, pal);
        } else {
            pal = &D_800CD2F8_main[i];
            if (D_800CCF85_main & 2) {
                func_80019C00_main(pal->data);
                pal->owner = hmf;
                func_800321B8_main(chunk, hmf, pal);
            }
            pal->refCount++;
        }
    }
}

HmfPaletteData *func_80032038_main(HmfData *hmf, s16 index) {
    char name[0x20];
    u16 hash = func_80011334_main(hmf, name, index);
    u16 i;

    for (i = 0; i < 0x80; i++) {
        if ((u16)D_800CD2F8_main[i].nameHash != 0 && (u16)D_800CD2F8_main[i].nameHash == hash &&
            strcmp(D_800CD2F8_main[i].name, name) == 0) {
            break;
        }
    }
    if (i == 0x80) {
        return NULL;
    }
    return &D_800CD2F8_main[i];
}

void func_80032104_main(void *unk) {
    s16 i;

    for (i = 0; i < 0x80; i++) {
        if (D_800CD2F8_main[i].nameHash != 0 && D_800CD2F8_main[i].owner == unk) {
            func_80032194_main(&D_800CD2F8_main[i]);
        }
    }
}

void func_80032194_main(HmfPaletteData *pal) {
    pal->nameHash = 0;
    pal->owner = NULL;
    func_80019C00_main(pal->data);
}

void func_800321B8_main(u8 *data, HmfData *hmf, HmfPaletteData *pal) {
    s16 count;
    u16 *dst;
    s16 i;

    data += 0xA;
    count = (data[0] << 8) + data[1];
    pal->data = HuMemAllocTag(count * 2, TAG_TEXTURE);
    pal->colorCount = count;
    data += 2;
    dst = (u16 *)pal->data;
    for (i = 0; i < count; i++) {
        dst[i] = ((data[i * 4 + 0] & 0xF8) << 8) + ((data[i * 4 + 1] & 0xF8) << 3) + ((data[i * 4 + 2] & 0xF8) >> 2) +
                 (data[i * 4 + 3] >= 0x80 ? 1 : 0);
    }
}

void func_800322AC_main(HmfData_Unk84_Entry2 *tex) {
    HmfData *hmf;
    s16 i;
    s16 j;

    for (i = 0; i < 0x80; i++) {
        if (HmfModelData[i].hmf != NULL) {
            hmf = HmfModelData[i].hmf;
            for (j = 0; j < hmf->unk12; j++) {
                if (hmf->unk84[j].unkC == tex) {
                    hmf->unk84[j].unkC = &D_800A1190_main;
                }
            }
        }
    }
}

void func_8003235C_main(void) {
    s16 i;

    D_800D1714_main = HuMemAlloc(0x600);
    for (i = 0; i < 0x80; i++) {
        D_800D1714_main[i].animIdx = -1;
    }
    func_80032950_main();
}

s32 HmfAnimCreate(HmfData *hmf, void *data, s16 bank, char *name) {
    HmfData_Unk84_Entry2 *tex;
    s16 hash = func_80011460_main((u8 *)name);
    s16 slot;
    s16 i;
    s16 j;

    for (i = 0; i < 0x80; i++) {
        if (D_800D1FCC_main[i].nameHash == hash && strcmp(D_800D1FCC_main[i].name, name) == 0) {
            break;
        }
    }
    if (i == 0x80) {
        osSyncPrintf("Can't Find TextureName! EntryAnimMAn\n");
        return -1;
    }
    for (slot = 0; slot < 0x80; slot++) {
        if (D_800D1714_main[slot].animIdx == -1) {
            break;
        }
    }
    if (slot == 0x80) {
        return -1;
    }
    D_800D1714_main[slot].animIdx = func_800329B4_main(data);
    D_800D1714_main[slot].rot = bank;
    D_800D1714_main[slot].frame = 0;
    D_800D1714_main[slot].interp = 0;
    D_800D1714_main[slot].speed = 0x10;
    D_800D1714_main[slot].flags = 0;
    tex = &D_800D1FCC_main[i];
    if (hmf != (HmfData *)-1) {
        for (i = 0; i < hmf->unk12; i++) {
            if (hmf->unk84[i].unkC == tex) {
                hmf->unk84[i].unk9 = slot;
            }
        }
    } else {
        for (j = 0; j < 0x80; j++) {
            if (HmfModelData[j].hmf != NULL && HmfModelData[j].unk00 == 0) {
                hmf = HmfModelData[j].hmf;
                for (i = 0; i < hmf->unk12; i++) {
                    if (hmf->unk84[i].unkC == tex) {
                        hmf->unk84[i].unk9 = slot;
                    }
                }
            }
        }
    }
    return slot;
}

s16 HmfAnimLink(HmfData *hmf, u16 linkIdx, s16 bank, char *name) {
    HmfData_Unk84_Entry2 *tex;
    HmfAnim *anim;
    s16 hash = func_80011460_main((u8 *)name);
    s16 slot;
    s16 i;
    s16 j;

    for (i = 0; i < 0x80; i++) {
        if (D_800D1FCC_main[i].nameHash == hash && strcmp(D_800D1FCC_main[i].name, name) == 0) {
            break;
        }
    }
    if (i == 0x80) {
        osSyncPrintf("Can't Find TextureName! LinkAnimMAn\n");
        return -1;
    }
    if ((slot = func_80033F8C_main()) == -1) {
        return -1;
    }
    anim = &D_800D1714_main[slot];
    anim->animIdx = D_800D1714_main[linkIdx].animIdx;
    anim->rot = bank;
    anim->flags = 0;
    anim->interp = 0;
    anim->frame = 0;
    anim->speed = 0x10;
    D_800D408C_main[anim->animIdx].refCount++;
    tex = &D_800D1FCC_main[i];
    if (hmf != (HmfData *)-1) {
        for (i = 0; i < hmf->unk12; i++) {
            if (hmf->unk84[i].unkC == tex) {
                hmf->unk84[i].unk9 = slot;
            }
        }
    } else {
        for (j = 0; j < 0x80; j++) {
            if (HmfModelData[j].hmf != NULL && HmfModelData[j].unk00 == 0) {
                hmf = HmfModelData[j].hmf;
                for (i = 0; i < hmf->unk12; i++) {
                    if (hmf->unk84[i].unkC == tex) {
                        hmf->unk84[i].unk9 = slot;
                    }
                }
            }
        }
    }
    return slot;
}

void func_80032950_main(void) {
    s16 i;

    D_800D408C_main = HuMemAlloc(0x300);
    for (i = 0; i < 0x20; i++) {
        D_800D408C_main[i].unk0C = NULL;
    }
}

s16 func_800329B4_main(u8 *data) {
    HmfAnimSet *set;
    HmfAnimImage *img;
    HmfAnimFrame *frame;
    u8 *table;
    u8 *src;
    u8 *pixels;
    s16 bpp;
    s32 palCount;
    s16 imgCount;
    s16 bankCount;
    s16 frameCount;
    s16 width;
    s16 height;
    s16 time;
    s16 total;
    s16 slot;
    s16 i;
    s16 j;

    for (slot = 0; slot < 0x20; slot++) {
        if (D_800D408C_main[slot].unk0C == NULL) {
            break;
        }
    }
    if (slot == 0x20) {
        return -1;
    }
    set = &D_800D408C_main[slot];
    set->interp = (data[0x18] << 8) + data[0x19];
    bpp = set->interp & 0xFF;
    palCount = data[0x1A];
    set->rotCount = palCount;
    table = data + (data[0xD] << 16) + (data[0xE] << 8) + data[0xF];
    if (bpp <= 8) {
        if (palCount >= 2 && !(set->interp & 0x8000)) {
            set->unk14 = HuMemAllocTag(palCount * 2, slot + TAG_TEXANIM);
            bcopy(table, set->unk14, palCount * 2);
        } else {
            set->rotCount = 0;
            set->unk14 = NULL;
        }
    } else {
        set->rotCount = 0;
        set->unk14 = NULL;
    }

    imgCount = (data[0x10] << 8) + data[0x11];
    set->unk00 = imgCount;
    set->unk0C = HuMemAllocTag(imgCount * sizeof(HmfAnimImage), slot + TAG_TEXANIM);
    table = data + (data[1] << 16) + (data[2] << 8) + data[3];
    for (i = 0; i < imgCount; i++) {
        img = &set->unk0C[i];
        pixels = data + (table[1] << 16) + (table[2] << 8) + table[3];
        width = img->width = (table[4] << 8) + table[5];
        height = img->height = (table[6] << 8) + table[7];
        img->unk04 = (table[8] << 8) + table[9];
        img->unk06 = (table[10] << 8) + table[11];
        img->data = HuMemAllocTag(width * height * bpp / 8, slot + TAG_TEXANIM);
        bcopy(pixels, img->data, width * height * bpp / 8);
        img->palette = set->unk14;
        img->colorCount = set->rotCount;
        table += 12;
    }

    bankCount = (data[0x12] << 8) + data[0x13];
    set->unk02 = bankCount;
    if (bankCount != 0) {
        set->rot = HuMemAllocTag(bankCount * sizeof(HmfAnimRot), slot + TAG_TEXANIM);
        table = data + (data[5] << 16) + (data[6] << 8) + data[7];
        for (i = 0; i < bankCount; i++) {
            src = data + (table[i * 4 + 1] << 16) + (table[i * 4 + 2] << 8) + table[i * 4 + 3];
            set->rot[i].frameCount = frameCount = (src[0] << 8) + src[1];
            set->rot[i].frames = HuMemAllocTag(frameCount * sizeof(HmfAnimFrame), slot + TAG_TEXANIM);
            src += 2;
            total = 0;
            for (j = 0; j < frameCount; j++) {
                frame = &set->rot[i].frames[j];
                frame->unk00 = (src[0] << 8) + src[1];
                frame->time = time = (src[2] << 8) + src[3];
                if (time > 0) {
                    total += time;
                }
                frame->unk04 = src[4];
                frame->unk05 = src[5];
                frame->unk06 = src[6];
                src += 7;
            }
            set->rot[i].totalFrames = total;
        }
    } else {
        set->unk02 = 1;
        set->rot = HuMemAllocTag(sizeof(HmfAnimRot), slot + TAG_TEXANIM);
        set->rot->frameCount = frameCount = imgCount;
        set->rot->frames = HuMemAllocTag(frameCount * sizeof(HmfAnimFrame), slot + TAG_TEXANIM);
        for (j = 0; j < frameCount; j++) {
            frame = &set->rot->frames[j];
            frame->unk00 = j;
            frame->time = 1;
            frame->unk06 = frame->unk04 = frame->unk05 = 0;
        }
        set->rot->totalFrames = frameCount;
    }
    D_800D408C_main[slot].refCount = 1;
    return slot;
}

void func_80032FC0_main(s16 animIdx, u8 bitmask, u8 flags) {
    HmfAnim *anim = &D_800D1714_main[animIdx];

    anim->flags = (anim->flags & ~bitmask) | flags;
}

void func_80032FF8_main(s16 animIdx, u8 rot) {
    HmfAnim *anim = &D_800D1714_main[animIdx];

    anim->rot = rot;
    anim->frame = 0;
    anim->interp = 0;
}

void func_8003302C_main(s16 animIdx, u8 frame) {
    HmfAnim *anim = &D_800D1714_main[animIdx];

    HmfAnimRot *rot;

    anim->frame = frame;
    rot = &D_800D408C_main[anim->animIdx].rot[anim->rot];
    if (rot->frameCount <= frame) {
        anim->frame = frame % rot->frameCount;
    }
    anim->interp = 0;
    anim->speed = 0x10;
}

u8 func_800330D4_main(s16 animIdx) {
    HmfAnim *anim = &D_800D1714_main[animIdx];
    u8 *rotFrames = (u8 *)&D_800D408C_main[anim->animIdx].rot[anim->rot];

    return rotFrames[1];
}

void HmfAnimExec(u16 vcount) {
    HmfAnim *anim;
    HmfAnimRot *bank;
    s16 i;
    s16 j;

    for (i = 0; i < 0x80; i++) {
        if (D_800D1714_main[i].animIdx != -1 && !(D_800D1714_main[i].flags & 4)) {
            anim = &D_800D1714_main[i];
            if (!(anim->flags & 1)) {
                bank = &D_800D408C_main[anim->animIdx].rot[anim->rot];
                for (j = 0; j < vcount; j++) {
                    anim->interp += anim->speed;
                    while (anim->interp >= bank->frames[anim->frame].time * 16) {
                        anim->interp -= bank->frames[anim->frame].time * 16;
                        anim->frame++;
                        if (bank->frameCount <= anim->frame) {
                            if ((anim->flags & 2) || bank->frames[anim->frame - 1].time != -1) {
                                anim->frame--;
                            } else {
                                anim->frame = 0;
                                anim->interp = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

void func_800332D4_main(s16 animIdx, f32 speed) {
    D_800D1714_main[animIdx].speed = speed * 16.0f;
}

void func_80033354_main(s16 animIdx) {
    HmfAnim *anim = &D_800D1714_main[animIdx];

    if (anim->animIdx != -1) {
        func_800333B0_main(anim->animIdx);
        anim->animIdx = -1;
    }
}

void func_800333B0_main(s16 animIdx) {
    if (D_800D408C_main[animIdx].unk0C != NULL) {
        D_800D408C_main[animIdx].refCount--;
        if (D_800D408C_main[animIdx].refCount == 0) {
            func_80019C68_main(animIdx + TAG_TEXANIM);
            D_800D408C_main[animIdx].unk0C = NULL;
        }
    }
}

void func_80033430_main(s16 animIdx) {
    func_80033354_main(animIdx);
}

void func_80033450_main(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        if (D_800D408C_main[i].unk0C != NULL) {
            D_800D408C_main[i].unk0C = NULL;
            func_80019C68_main(i + TAG_TEXANIM);
        }
    }
    for (i = 0; i < 0x80; i++) {
        D_800D1714_main[i].animIdx = -1;
    }
}

void func_80033510_main(void) {
    s16 i;

    for (i = 0; i < 0x80; i++) {
        D_800D1FCC_main[i].nameHash = 0;
    }
    for (i = 0; i < 0x80; i++) {
        D_800CD2F8_main[i].nameHash = 0;
    }
    func_80019C68_main(TAG_TEXTURE);
}

void func_800335BC_main(char *name, u16 *out) {
    HmfData_Unk84_Entry2 *entry;
    u16 hash = func_80011460_main((u8 *)name);
    u16 i;

    for (i = 0; i < 0x80; i++) {
        if (D_800D1FCC_main[i].nameHash == hash && strcmp(D_800D1FCC_main[i].name, name) == 0) {
            break;
        }
    }
    if (i != 0x80) {
        entry = D_800D1FCC_main;
        out[0] = entry[i].unk24;
        out[1] = entry[i].unk26;
    }
}

void func_80033694_main(HmfData *hmf) {
    HmfData_Unk84_Entry2 *tex;
    HmfAnimSet *set;
    HmfAnim *anim;
    HmfAnimRot *rot;
    s16 img;
    s16 slot;
    s16 i;

    for (i = 0; i < hmf->unk12; i++) {
        if (hmf->unk84[i].unk3 == -1) {
            continue;
        }
        slot = hmf->unk84[i].unk9;
        if (!(slot & 0x80) && D_800D1714_main[slot].animIdx != -1) {
            anim = &D_800D1714_main[slot];
            rot = &D_800D408C_main[anim->animIdx].rot[anim->rot];
            img = rot->frames[anim->frame].unk00;
            if (img != -1) {
                set = &D_800D408C_main[anim->animIdx];
                gSPSegment(gMainGfxPos++, hmf->unk84[i].unk3, osVirtualToPhysical(set->unk0C[img].data));
                if (D_800D408C_main[anim->animIdx].unk14 != NULL) {
                    gSPSegment(gMainGfxPos++, (s8)hmf->unk84[i].unk4, osVirtualToPhysical(set->unk0C[img].palette));
                }
            } else {
                tex = hmf->unk84[i].unkC;
                gSPSegment(gMainGfxPos++, hmf->unk84[i].unk3, osVirtualToPhysical(tex->unk28));
                if (tex->unk_30 != NULL) {
                    gSPSegment(gMainGfxPos++, (s8)hmf->unk84[i].unk4, osVirtualToPhysical(tex->unk_30->data));
                }
            }
        } else {
            tex = hmf->unk84[i].unkC;
            gSPSegment(gMainGfxPos++, hmf->unk84[i].unk3, osVirtualToPhysical(tex->unk28));
            if (tex->unk_30 != NULL) {
                gSPSegment(gMainGfxPos++, (s8)hmf->unk84[i].unk4, osVirtualToPhysical(tex->unk_30->data));
            }
        }
    }
}

void func_80033910_main(HmfData *arg0) {
    s16 i;

    for (i = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unk3 != -1) {
            arg0->unk84[i].unk9 |= 0x80;
        }
    }
}

void func_80033970_main(HmfData *arg0) {
    s16 i;

    for (i = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unk3 != -1) {
            arg0->unk84[i].unk9 &= 0x7F;
        }
    }
}

s32 func_800339D0_main(HmfData *hmf) {
    u8 slots[0x20];
    HmfData_Unk84_Entry2 *tex;
    HmfData_Unk84_Entry *entry;
    u8 *chunk;
    u8 *next;
    u8 *rec;
    s16 recCount;
    s16 hash;
    s16 slot;
    s16 count;
    s16 j;
    s16 i;

    count = 0;
    chunk = hmf->unk34;
    while (TRUE) {
        chunk = func_80010A38_main(0x4D544E31, chunk, hmf->unk30); // "MTN1"
        if (chunk == NULL) {
            break;
        }
        next = chunk + 0xD;
        recCount = chunk[0xA];
        for (j = 0; j < recCount; j++) {
            rec = next;
            next += ((next[0] << 8) + next[1]) + 2;
            if (rec[2] == 'V' && rec[3] == 'X') {
                rec += 4;
                slot = func_80033F8C_main();
                if (slot == -1) {
                    break;
                }
                slots[count] = slot;
                D_800D1714_main[slot].animIdx = func_80033D0C_main(hmf, rec);
                D_800D1714_main[slot].rot = 0;
                D_800D1714_main[slot].frame = 0;
                D_800D1714_main[slot].interp = 0;
                D_800D1714_main[slot].speed = 0x10;
                D_800D1714_main[slot].flags = 4;
                D_800D408C_main[D_800D1714_main[slot].animIdx].refCount = 1;
                entry = &hmf->unk84[(rec[2] << 8) + rec[3]];
                hash = entry->unkC->nameHash;
                for (i = 0; i < 0x80; i++) {
                    if (D_800D1FCC_main[i].nameHash == hash && strcmp(D_800D1FCC_main[i].name, entry->unkC->name) == 0) {
                        break;
                    }
                }
                tex = &D_800D1FCC_main[i];
                for (i = 0; i < hmf->unk12; i++) {
                    if (hmf->unk84[i].unkC == tex) {
                        hmf->unk84[i].unk9 = slot;
                    }
                }
                count++;
            }
        }
        chunk = func_80010AC8_main(chunk + 4);
    }
    if (count == 0) {
        hmf->unkC8 = NULL;
        return 0;
    }
    hmf->unkC8 = HuMemAllocTag(count, hmf->unk0E + 1);
    for (i = 0; i < count; i++) {
        hmf->unkC8[i] = slots[i];
    }
    hmf->unk2A = count;
    return 1;
}

s16 func_80033D0C_main(HmfData *hmf, u8 *data) {
    HmfData_Unk84_Entry2 *tex;
    HmfAnimSet *set;
    HmfAnimImage *img;
    HmfAnimFrame *frame = NULL;
    u8 *entry;
    s16 slot;
    s16 count;
    s16 totalTime;
    s16 i;

    slot = func_80033FEC_main();
    if (slot == -1) {
        return -1;
    }
    set = &D_800D408C_main[slot];
    count = (data[4] << 8) + data[5];
    set->unk00 = count;
    set->unk0C = HuMemAllocTag(count * sizeof(HmfAnimImage), slot + TAG_TEXANIM);
    entry = data + 6;
    set->interp = (data[0x18] << 8) + data[0x19];
    set->unk02 = 1;
    set->rot = HuMemAllocTag(sizeof(HmfAnimRot), slot + TAG_TEXANIM);
    set->rot->frameCount = count + 1;
    set->rot->frames = HuMemAllocTag((count + 1) * sizeof(HmfAnimFrame), slot + TAG_TEXANIM);
    totalTime = 0;
    for (i = 0; i < count; i++) {
        img = &set->unk0C[i];
        frame = &set->rot->frames[i];
        tex = func_80031A08_main(hmf, (entry[0] << 8) + entry[1]);
        img->width = tex->unk24;
        img->height = tex->unk26;
        img->unk06 = 0;
        img->unk04 = 0;
        img->data = tex->unk28;
        frame->unk00 = i;
        frame->time = (entry[2] << 8) + entry[3];
        if (frame->time == 0) {
            frame->time = 1;
        }
        if (frame->time > 0) {
            totalTime += frame->time;
        }
        frame->unk04 = frame->unk05 = frame->unk06 = 0;
        if (tex->unk1C == 2) {
            img->colorCount = tex->unk_30->colorCount;
            img->palette = tex->unk_30->data;
        }
        entry += 4;
    }
    frame++;
    frame->unk00 = 0;
    frame->time = -1;
    set->rot->totalFrames = totalTime;
    set->rotCount = set->unk0C[0].colorCount;
    set->unk14 = set->unk0C[0].palette;
    return slot;
}

s16 func_80033F8C_main(void) {
    s16 i;

    for (i = 0; i < 0x80; i++) {
        if (D_800D1714_main[i].animIdx == -1) {
            return i;
        }
    }
    return -1;
}

s16 func_80033FEC_main(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        if (D_800D408C_main[i].unk0C == NULL) {
            return i;
        }
    }
    return -1;
}

void func_80034048_main(s16 animIdx, s16 count) {
    HmfAnim *anim;
    HmfAnimRot *bank;
    s16 j;

    if (D_800D1714_main[animIdx].animIdx != -1) {
        anim = &D_800D1714_main[animIdx];
        bank = &D_800D408C_main[anim->animIdx].rot[anim->rot];
        anim->frame = 0;
        anim->interp = 0;
        for (j = 0; j < count; j++) {
            anim->interp++;
            while (anim->interp >= bank->frames[anim->frame].time) {
                anim->interp -= bank->frames[anim->frame].time;
                anim->frame++;
                if (bank->frameCount <= anim->frame) {
                    if ((anim->flags & 2) || bank->frames[anim->frame - 1].time != -1) {
                        anim->frame--;
                    } else {
                        anim->frame = 0;
                        anim->interp = 0;
                    }
                }
            }
        }
    }
}

// Possible file boundary: rodata 0x800A6D40 (start of the minigame table, likely belongs with mgdata.c).
const s32 D_800A6D40_main = 1;

INCLUDE_RODATA("asm/nonmatchings/hmfanim", D_800A6D44_main);

INCLUDE_RODATA("asm/nonmatchings/hmfanim", D_800A6D4C_main);

INCLUDE_RODATA("asm/nonmatchings/hmfanim", D_800A6D50_main);
