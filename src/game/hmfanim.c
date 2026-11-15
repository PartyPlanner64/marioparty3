#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/hmfanim.h"
#include "include_asm.h"
#include "game/hmfload.h"
#include "gcc/string.h"
#include "game/mallocblock.h"

extern HmfPaletteData *Hu3DPalData;
extern HmfData_Unk84_Entry2 *Hu3DTexData;
extern u8 Hu3DLoadFlags;
extern Gfx *gMainGfxPos;

u16 Hu3DTexDummyImg[] = {
    0x03C1, 0x03C1, 0x03C1, 0x03C1, 0x03C1, 0x03C1, 0x03C1, 0x03C1,
    0x03C1, 0x03C1, 0x03C1, 0x03C1, 0x03C1, 0x03C1, 0x03C1, 0x03C1,
};

HmfData_Unk84_Entry2 Hu3DTexDummy = {
    "0123456789ABCDE", 0, 2, 4, 4, 0xFF, 0, 0, 0, (u8 *)Hu3DTexDummyImg, (struct HmfData *)-1, NULL,
};

void Hu3DTexInit(void) {
    s16 i;

    Hu3DTexData = HuMemAlloc(0x1A00);
    Hu3DPalData = HuMemAlloc(0x1600);
    for (i = 0; i < 0x80; i++) {
        Hu3DTexData[i].nameHash = 0;
    }
    for (i = 0; i < 0x80; i++) {
        Hu3DPalData[i].nameHash = 0;
    }
    Hu3DLoadFlags = 0;
    Hu3DAnimWorkInit();
}

void Hu3DTexLoad(HmfData *hmf) {
    char name[0x20];
    HmfData_Unk84_Entry2 *tex;
    u8 *chunk;
    s16 hash;
    s16 i;

    Hu3DPalLoad(hmf);
    for (chunk = hmf->unk34; chunk < hmf->unk30; chunk = HmfChunkNext(chunk + 4)) {
        chunk = HmfChunkSearch(0x424D5031, chunk, hmf->unk30); // "BMP1"
        if (chunk == NULL) {
            return;
        }
        hash = GetString(hmf, name, (chunk[8] << 8) + chunk[9]);
        for (i = 0; i < 0x80; i++) {
            if (Hu3DTexData[i].nameHash == hash && strcmp(Hu3DTexData[i].name, name) == 0) {
                break;
            }
        }
        if (i == 0x80) {
            for (i = 0; i < 0x80; i++) {
                if (Hu3DTexData[i].nameHash == 0) {
                    break;
                }
            }
            if (i == 0x80) {
                osSyncPrintf("TEXTURE OVER!\n");
                return;
            }
            tex = &Hu3DTexData[i];
            tex->nameHash = hash;
            strcpy(tex->name, name);
            tex->owner = hmf;
            Hu3DTexDataSet(chunk, hmf, tex);
        } else {
            tex = &Hu3DTexData[i];
            if (Hu3DLoadFlags & 2) {
                HuMemDelayFree(tex->unk28);
                tex->owner = hmf;
                Hu3DTexDataSet(chunk, hmf, tex);
            }
        }
    }
}

void Hu3DTexRelease(HmfData *hmf) {
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
            other = Hu3DData[j].hmf;
            if (other == NULL || Hu3DData[j].unk00 != 0 || hmf == other || other->unk84 == NULL) {
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
                Hu3DPalKill(tex->unk_30);
            }
            HuMemDelayFree(tex->unk28);
        }
    }
}

HmfData_Unk84_Entry2 *Hu3DTexSearchIdx(HmfData *hmf, s16 index) {
    char name[0x20];

    GetString(hmf, name, index);
    return Hu3DTexSearch(hmf, name);
}

HmfData_Unk84_Entry2 *Hu3DTexSearchName(HmfData *hmf, char *name) {
    return Hu3DTexSearch(hmf, name);
}

HmfData_Unk84_Entry2 *Hu3DTexSearch(HmfData *hmf, char *name) {
    u16 hash = HmfNameHash((u8 *)name);
    u16 i;

    for (i = 0; i < 0x80; i++) {
        if (Hu3DTexData[i].nameHash != 0 && Hu3DTexData[i].nameHash == hash &&
            strcmp(Hu3DTexData[i].name, name) == 0) {
            break;
        }
    }
    if (i == 0x80) {
        return NULL;
    }
    return &Hu3DTexData[i];
}

void Hu3DTexDataSet(u8 *data, HmfData *hmf, HmfData_Unk84_Entry2 *tex) {
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
        tex->unk_30 = Hu3DPalSearch(hmf, (data[6] << 8) + data[7]);
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

void Hu3DPalLoad(HmfData *hmf) {
    char name[0x20];
    HmfPaletteData *pal;
    u8 *chunk;
    s16 hash;
    s16 i;

    for (chunk = hmf->unk34; chunk < hmf->unk30; chunk = HmfChunkNext(chunk + 4)) {
        chunk = HmfChunkSearch(0x50414C31, chunk, hmf->unk30); // "PAL1"
        if (chunk == NULL) {
            return;
        }
        hash = GetString(hmf, name, (chunk[8] << 8) + chunk[9]);
        for (i = 0; i < 0x80; i++) {
            if (Hu3DPalData[i].nameHash == hash && strcmp(Hu3DPalData[i].name, name) == 0) {
                break;
            }
        }
        if (i == 0x80) {
            for (i = 0; i < 0x80; i++) {
                if (Hu3DPalData[i].nameHash == 0) {
                    break;
                }
            }
            if (i == 0x80) {
                return;
            }
            pal = &Hu3DPalData[i];
            pal->nameHash = hash;
            strcpy(pal->name, name);
            pal->owner = hmf;
            pal->refCount = 1;
            Hu3DPalDataSet(chunk, hmf, pal);
        } else {
            pal = &Hu3DPalData[i];
            if (Hu3DLoadFlags & 2) {
                HuMemDelayFree(pal->data);
                pal->owner = hmf;
                Hu3DPalDataSet(chunk, hmf, pal);
            }
            pal->refCount++;
        }
    }
}

HmfPaletteData *Hu3DPalSearch(HmfData *hmf, s16 index) {
    char name[0x20];
    u16 hash = GetString(hmf, name, index);
    u16 i;

    for (i = 0; i < 0x80; i++) {
        if ((u16)Hu3DPalData[i].nameHash != 0 && (u16)Hu3DPalData[i].nameHash == hash &&
            strcmp(Hu3DPalData[i].name, name) == 0) {
            break;
        }
    }
    if (i == 0x80) {
        return NULL;
    }
    return &Hu3DPalData[i];
}

void Hu3DPalOwnerKill(void *unk) {
    s16 i;

    for (i = 0; i < 0x80; i++) {
        if (Hu3DPalData[i].nameHash != 0 && Hu3DPalData[i].owner == unk) {
            Hu3DPalKill(&Hu3DPalData[i]);
        }
    }
}

void Hu3DPalKill(HmfPaletteData *pal) {
    pal->nameHash = 0;
    pal->owner = NULL;
    HuMemDelayFree(pal->data);
}

void Hu3DPalDataSet(u8 *data, HmfData *hmf, HmfPaletteData *pal) {
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

void Hu3DTexRefClear(HmfData_Unk84_Entry2 *tex) {
    HmfData *hmf;
    s16 i;
    s16 j;

    for (i = 0; i < 0x80; i++) {
        if (Hu3DData[i].hmf != NULL) {
            hmf = Hu3DData[i].hmf;
            for (j = 0; j < hmf->unk12; j++) {
                if (hmf->unk84[j].unkC == tex) {
                    hmf->unk84[j].unkC = &Hu3DTexDummy;
                }
            }
        }
    }
}

void Hu3DAnimWorkInit(void) {
    s16 i;

    Hu3DAnimData = HuMemAlloc(0x600);
    for (i = 0; i < 0x80; i++) {
        Hu3DAnimData[i].animIdx = -1;
    }
    Hu3DAnimInit();
}

s32 Hu3DAnimCreate(HmfData *hmf, void *data, s16 bank, const char *name) {
    HmfData_Unk84_Entry2 *tex;
    s16 hash = HmfNameHash((u8 *)name);
    s16 slot;
    s16 i;
    s16 j;

    for (i = 0; i < 0x80; i++) {
        if (Hu3DTexData[i].nameHash == hash && strcmp(Hu3DTexData[i].name, name) == 0) {
            break;
        }
    }
    if (i == 0x80) {
        osSyncPrintf("Can't Find TextureName! EntryAnimMAn\n");
        return -1;
    }
    for (slot = 0; slot < 0x80; slot++) {
        if (Hu3DAnimData[slot].animIdx == -1) {
            break;
        }
    }
    if (slot == 0x80) {
        return -1;
    }
    Hu3DAnimData[slot].animIdx = Hu3DAnimDataCreate(data);
    Hu3DAnimData[slot].rot = bank;
    Hu3DAnimData[slot].frame = 0;
    Hu3DAnimData[slot].interp = 0;
    Hu3DAnimData[slot].speed = 0x10;
    Hu3DAnimData[slot].flags = 0;
    tex = &Hu3DTexData[i];
    if (hmf != (HmfData *)-1) {
        for (i = 0; i < hmf->unk12; i++) {
            if (hmf->unk84[i].unkC == tex) {
                hmf->unk84[i].unk9 = slot;
            }
        }
    } else {
        for (j = 0; j < 0x80; j++) {
            if (Hu3DData[j].hmf != NULL && Hu3DData[j].unk00 == 0) {
                hmf = Hu3DData[j].hmf;
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

s16 Hu3DAnimLink(HmfData *hmf, u16 linkIdx, s16 bank, const char *name) {
    HmfData_Unk84_Entry2 *tex;
    HmfAnim *anim;
    s16 hash = HmfNameHash((u8 *)name);
    s16 slot;
    s16 i;
    s16 j;

    for (i = 0; i < 0x80; i++) {
        if (Hu3DTexData[i].nameHash == hash && strcmp(Hu3DTexData[i].name, name) == 0) {
            break;
        }
    }
    if (i == 0x80) {
        osSyncPrintf("Can't Find TextureName! LinkAnimMAn\n");
        return -1;
    }
    if ((slot = Hu3DAnimSlotGet()) == -1) {
        return -1;
    }
    anim = &Hu3DAnimData[slot];
    anim->animIdx = Hu3DAnimData[linkIdx].animIdx;
    anim->rot = bank;
    anim->flags = 0;
    anim->interp = 0;
    anim->frame = 0;
    anim->speed = 0x10;
    Hu3DAnimSetData[anim->animIdx].refCount++;
    tex = &Hu3DTexData[i];
    if (hmf != (HmfData *)-1) {
        for (i = 0; i < hmf->unk12; i++) {
            if (hmf->unk84[i].unkC == tex) {
                hmf->unk84[i].unk9 = slot;
            }
        }
    } else {
        for (j = 0; j < 0x80; j++) {
            if (Hu3DData[j].hmf != NULL && Hu3DData[j].unk00 == 0) {
                hmf = Hu3DData[j].hmf;
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

void Hu3DAnimInit(void) {
    s16 i;

    Hu3DAnimSetData = HuMemAlloc(0x300);
    for (i = 0; i < 0x20; i++) {
        Hu3DAnimSetData[i].unk0C = NULL;
    }
}

s32 Hu3DAnimDataCreate(u8 *data) {
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
        if (Hu3DAnimSetData[slot].unk0C == NULL) {
            break;
        }
    }
    if (slot == 0x20) {
        return -1;
    }
    set = &Hu3DAnimSetData[slot];
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
    Hu3DAnimSetData[slot].refCount = 1;
    return slot;
}

void Hu3DAnimAttrSet(s16 animIdx, u8 bitmask, u8 flags) {
    HmfAnim *anim = &Hu3DAnimData[animIdx];

    anim->flags = (anim->flags & ~bitmask) | flags;
}

void Hu3DAnimBankSet(s16 animIdx, u8 rot) {
    HmfAnim *anim = &Hu3DAnimData[animIdx];

    anim->rot = rot;
    anim->frame = 0;
    anim->interp = 0;
}

void Hu3DAnmNoSet(s16 animIdx, u8 frame) {
    HmfAnim *anim = &Hu3DAnimData[animIdx];

    HmfAnimRot *rot;

    anim->frame = frame;
    rot = &Hu3DAnimSetData[anim->animIdx].rot[anim->rot];
    if (rot->frameCount <= frame) {
        anim->frame = frame % rot->frameCount;
    }
    anim->interp = 0;
    anim->speed = 0x10;
}

u8 Hu3DAnimFrameGet(s16 animIdx) {
    HmfAnim *anim = &Hu3DAnimData[animIdx];
    u8 *rotFrames = (u8 *)&Hu3DAnimSetData[anim->animIdx].rot[anim->rot];

    return rotFrames[1];
}

void Hu3DAnimExec(u16 vcount) {
    HmfAnim *anim;
    HmfAnimRot *bank;
    s16 i;
    s16 j;

    for (i = 0; i < 0x80; i++) {
        if (Hu3DAnimData[i].animIdx != -1 && !(Hu3DAnimData[i].flags & 4)) {
            anim = &Hu3DAnimData[i];
            if (!(anim->flags & 1)) {
                bank = &Hu3DAnimSetData[anim->animIdx].rot[anim->rot];
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

void Hu3DAnimSpeedSet(s16 animIdx, f32 speed) {
    Hu3DAnimData[animIdx].speed = speed * 16.0f;
}

void Hu3DAnimKill(s16 animIdx) {
    HmfAnim *anim = &Hu3DAnimData[animIdx];

    if (anim->animIdx != -1) {
        Hu3DAnimDataKill(anim->animIdx);
        anim->animIdx = -1;
    }
}

void Hu3DAnimDataKill(s16 animIdx) {
    if (Hu3DAnimSetData[animIdx].unk0C != NULL) {
        Hu3DAnimSetData[animIdx].refCount--;
        if (Hu3DAnimSetData[animIdx].refCount == 0) {
            HuMemDelayFreeAllWithTag(animIdx + TAG_TEXANIM);
            Hu3DAnimSetData[animIdx].unk0C = NULL;
        }
    }
}

void Hu3DAnimModelKill(s16 animIdx) {
    Hu3DAnimKill(animIdx);
}

void Hu3DAnimAllKill(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        if (Hu3DAnimSetData[i].unk0C != NULL) {
            Hu3DAnimSetData[i].unk0C = NULL;
            HuMemDelayFreeAllWithTag(i + TAG_TEXANIM);
        }
    }
    for (i = 0; i < 0x80; i++) {
        Hu3DAnimData[i].animIdx = -1;
    }
}

void Hu3DTexAllKill(void) {
    s16 i;

    for (i = 0; i < 0x80; i++) {
        Hu3DTexData[i].nameHash = 0;
    }
    for (i = 0; i < 0x80; i++) {
        Hu3DPalData[i].nameHash = 0;
    }
    HuMemDelayFreeAllWithTag(TAG_TEXTURE);
}

void Hu3DTexSizeGet(char *name, u16 *out) {
    HmfData_Unk84_Entry2 *entry;
    u16 hash = HmfNameHash((u8 *)name);
    u16 i;

    for (i = 0; i < 0x80; i++) {
        if (Hu3DTexData[i].nameHash == hash && strcmp(Hu3DTexData[i].name, name) == 0) {
            break;
        }
    }
    if (i != 0x80) {
        entry = Hu3DTexData;
        out[0] = entry[i].unk24;
        out[1] = entry[i].unk26;
    }
}

void Hu3DAnimSegmentSet(HmfData *hmf) {
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
        if (!(slot & 0x80) && Hu3DAnimData[slot].animIdx != -1) {
            anim = &Hu3DAnimData[slot];
            rot = &Hu3DAnimSetData[anim->animIdx].rot[anim->rot];
            img = rot->frames[anim->frame].unk00;
            if (img != -1) {
                set = &Hu3DAnimSetData[anim->animIdx];
                gSPSegment(gMainGfxPos++, hmf->unk84[i].unk3, osVirtualToPhysical(set->unk0C[img].data));
                if (Hu3DAnimSetData[anim->animIdx].unk14 != NULL) {
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

void Hu3DModelAnimStop(HmfData *arg0) {
    s16 i;

    for (i = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unk3 != -1) {
            arg0->unk84[i].unk9 |= 0x80;
        }
    }
}

void Hu3DModelAnimStart(HmfData *arg0) {
    s16 i;

    for (i = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unk3 != -1) {
            arg0->unk84[i].unk9 &= 0x7F;
        }
    }
}

s32 Hu3DModelAnimLoad(HmfData *hmf) {
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
        chunk = HmfChunkSearch(0x4D544E31, chunk, hmf->unk30); // "MTN1"
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
                slot = Hu3DAnimSlotGet();
                if (slot == -1) {
                    break;
                }
                slots[count] = slot;
                Hu3DAnimData[slot].animIdx = Hu3DAnimSetCreate(hmf, rec);
                Hu3DAnimData[slot].rot = 0;
                Hu3DAnimData[slot].frame = 0;
                Hu3DAnimData[slot].interp = 0;
                Hu3DAnimData[slot].speed = 0x10;
                Hu3DAnimData[slot].flags = 4;
                Hu3DAnimSetData[Hu3DAnimData[slot].animIdx].refCount = 1;
                entry = &hmf->unk84[(rec[2] << 8) + rec[3]];
                hash = entry->unkC->nameHash;
                for (i = 0; i < 0x80; i++) {
                    if (Hu3DTexData[i].nameHash == hash && strcmp(Hu3DTexData[i].name, entry->unkC->name) == 0) {
                        break;
                    }
                }
                tex = &Hu3DTexData[i];
                for (i = 0; i < hmf->unk12; i++) {
                    if (hmf->unk84[i].unkC == tex) {
                        hmf->unk84[i].unk9 = slot;
                    }
                }
                count++;
            }
        }
        chunk = HmfChunkNext(chunk + 4);
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

s16 Hu3DAnimSetCreate(HmfData *hmf, u8 *data) {
    HmfData_Unk84_Entry2 *tex;
    HmfAnimSet *set;
    HmfAnimImage *img;
    HmfAnimFrame *frame = NULL;
    u8 *entry;
    s16 slot;
    s16 count;
    s16 totalTime;
    s16 i;

    slot = Hu3DAnimDataSlotGet();
    if (slot == -1) {
        return -1;
    }
    set = &Hu3DAnimSetData[slot];
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
        tex = Hu3DTexSearchIdx(hmf, (entry[0] << 8) + entry[1]);
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

s16 Hu3DAnimSlotGet(void) {
    s16 i;

    for (i = 0; i < 0x80; i++) {
        if (Hu3DAnimData[i].animIdx == -1) {
            return i;
        }
    }
    return -1;
}

s16 Hu3DAnimDataSlotGet(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        if (Hu3DAnimSetData[i].unk0C == NULL) {
            return i;
        }
    }
    return -1;
}

void Hu3DAnimTimeSet(s16 animIdx, s16 count) {
    HmfAnim *anim;
    HmfAnimRot *bank;
    s16 j;

    if (Hu3DAnimData[animIdx].animIdx != -1) {
        anim = &Hu3DAnimData[animIdx];
        bank = &Hu3DAnimSetData[anim->animIdx].rot[anim->rot];
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
