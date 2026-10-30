#include "common.h"
#include "PR/n_libaudio.h"

typedef struct {
    /* 0x00 */ s8 cmdType;   // cmdType
    /* 0x01 */ s8 voiceSlot; // voiceSlot
    /* 0x04 */ s32 cmdArg;   // cmdArg
} AudioCmd;                  // size: 0x8

/* One entry of the active sound table the audio manager keeps. Only the
 * fields the manager's own functions touch are named so far. */
typedef struct GameSound_s {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s16 sndId; // ALSndId, -1 when unallocated
    /* 0x0E */ char unk_0E[0xEE];
} GameSound; // size: 0xFC

typedef struct {
    /* 0x00 */ char unk_00[0x8];
    /* 0x08 */ GameSound *sounds;
    /* 0x0C */ char unk_0C[0x8];
    /* 0x14 */ s32 soundCount;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ char unk_1C[0x1C];
    /* 0x38 */ s32 unk38;           // write index (wraps at 0x80)
    /* 0x3C */ AudioCmd cmds[0x80]; // ring buffer of commands
} UnkAudio;

typedef struct {
    /* 0x00 */ N_ALCSPlayer *seqp;
    /* 0x04 */ u8 *seqData; // raw sequence data, DMA'd in per track
    /* 0x08 */ ALBank **bankTable;
    /* 0x0C */ ALCSeq *seq;
    /* 0x10 */ s32 seqDataSize;
    /* 0x14 */ s32 flags;    // 0x1 stopped, 0x2/0x8 queued, 0x4/0x20 no fade, 0x10 play, 0x40 fading
    /* 0x18 */ s16 curTrack; // track whose data is loaded
    /* 0x1A */ s16 newTrack; // track requested by the latest event
    /* 0x1C */ s32 cspState;
    /* 0x20 */ s32 state;
    /* 0x24 */ s32 fadeStep; // 0x7F000000 / fadeTime
    /* 0x28 */ s32 fadeTime; // frames left, negative while fading in
    /* 0x2C */ s8 fadeVol;   // current fade level, 0 to 0x7F
    /* 0x2D */ s8 unk_2D;
    /* 0x2E */ s8 trackVol; // volume of the current track
    /* 0x2F */ s8 evtVol;   // volume of the latest event
    /* 0x30 */ s8 unk_30;   // index of a linked player
    /* 0x31 */ s8 unk_31;   // fade time of the current track, in frames
    /* 0x32 */ s8 unk_32;
    /* 0x33 */ s8 unk_33;
} SeqPlayer; // size: 0x34

typedef struct {
    /* 0x00 */ SeqPlayer *players;
    /* 0x04 */ char unk_04[0x10]; // 0x10-byte track descriptor table
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s8 playerCount;
    /* 0x19 */ s8 playingCount;
    /* 0x1A */ s8 masterVol; // overall volume, set by volume events
    /* 0x1B */ s8 configVol; // overall volume, taken from the audio config
    /* 0x1C */ s16 trackCount;
    /* 0x1E */ s16 eventCount;
} AudioManager; // size: 0x220

/* Header at the start of an MBF0/SBF0 sound bank in ROM. */
typedef struct {
    /* 0x00 */ s32 magic; // 'MBF0' or 'SBF0'
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk_08[8];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s32 unk_1C; // offset of the effect table, relative to the bank
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s8 unk_24;
    /* 0x25 */ s8 unk_25;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s8 unk_28;
    /* 0x29 */ char unk_29[0x17];
} SndBankHeader; // size: 0x40

/* Header of an effect table. The count is stored in the low byte of the first
 * word, and is widened in place after loading. */
typedef union {
    s32 count;
    s16 id;
    u8 bytes[4];
} SndFxHeader;

/* Sound system state: the active configuration plus a few loader fields. */
typedef struct {
    /* 0x00 */ str800D5298 cfg;
    /* 0x6C */ u8 *buf;     // 0x40-byte scratch buffer for ROM headers
    /* 0x70 */ s16 fxCount; // number of effect tables in the FXD0 file
    /* 0x72 */ s16 unk_72;
    /* 0x74 */ s16 fxId; // id of the loaded effect table
} SndSys;

extern AudioManager *D_800A97B8_main;
extern UnkAudio *D_800A97BC_main;
extern ALHeap D_800A9730_main;
extern OSMesg D_800A9650_main[50];
extern OSMesgQueue D_800A9718_main;
extern SndSys D_800A9740_main;
extern u8 D_800CB8AC_main;

s32 func_80007080_main(s32, s32);
s32 func_80001134_main(s32 arg0, s32 arg1);
s32 func_80000650_main(void);
s32 func_8000086C_main(str800D5298 *cfg);
SndSys *func_80000E9C_main(void);
void func_80000FE4_main(void *dst, void *romAddr, s32 size, s32 chunkSize);
void *func_800010B8_main(s32 size);
s32 func_80001E10_main(SndSys *sys, ALHeap *heap, s32 arg2, s32 arg3);
void func_80002528_main(void);
AudioManager *func_800025B4_main(void);
void func_800025C0_main(void);
s32 func_80006A8C_main(SndSys *sys, ALHeap *heap, s32 arg2, s32 arg3);
void func_80006FC4_main(void);
UnkAudio *func_8000704C_main(void);
void func_80007058_main(void);
s32 amCreateAudioMgr(str800D5298 *cfg, ALHeap *heap);
void func_80008678_main(str800D5298 *cfg);
void func_8000870C_main(str800D5298 *cfg);

/* Takes the default settings from a bank header for any setting not given by
 * the caller's configuration. */
void func_80000540_main(SndBankHeader *hdr, void *romAddr) {
    SndSys *sys = &D_800A9740_main;

    if (!(sys->cfg.unk0 & 0x10)) {
        sys->cfg.unk1C = hdr->unk_14;
    }
    if (!(sys->cfg.unk0 & 0x20)) {
        sys->cfg.unk20 = hdr->unk_16;
    }
    if (!(sys->cfg.unk0 & 0x40)) {
        sys->cfg.unk24 = hdr->unk_18;
    }
    if (!(sys->cfg.unk0 & 0x80)) {
        sys->cfg.unk28 = hdr->unk_1A;
    }
    if (!(sys->cfg.unk0 & 0x200)) {
        sys->cfg.unk30 = hdr->unk_20;
    }
    if (!(sys->cfg.unk0 & 0x400)) {
        sys->cfg.unk34 = hdr->unk_24;
    }
    if (!(sys->cfg.unk0 & 0x800)) {
        sys->cfg.unk38 = hdr->unk_22;
    }
    if (!(sys->cfg.unk0 & 0x1000)) {
        sys->cfg.unk3C = hdr->unk_25;
    }
    if (!(sys->cfg.unk0 & 0x8000)) {
        sys->cfg.unk48 = hdr->unk_26;
    }
    if (!(sys->cfg.unk0 & 0x100)) {
        sys->cfg.unk2C = NULL;
        if (hdr->unk_1C != 0) {
            sys->cfg.unk2C = (u8 *)romAddr + hdr->unk_1C;
        }
    }
}

/* Loads the effect table, either the one given by the configuration or the
 * selected entry of the FXD0 file. */
#ifdef NON_MATCHING
/* sys and buf get swapped callee-saved registers, and some field accesses use
 * the base register where the target addresses the global directly. */
s32 func_80000650_main(void) {
    SndSys *sys;
    SndFxHeader *buf;
    u8 *romAddr;
    s32 size;
    s32 flags;
    SndFxHeader *fx;

    sys = &D_800A9740_main;
    buf = (SndFxHeader *)D_800A9740_main.buf;
    D_800A9740_main.fxId = 0;
    D_800A9740_main.fxCount = 0;
    sys->cfg.unk4 &= ~3;
    if (sys->cfg.unk10 != NULL) {
        func_80000FE4_main(buf, sys->cfg.unk10, 0x10, 0);
        if (buf->count == 'FXD0') {
            sys->fxCount = ((u16 *)buf)[3];
        }
    }
    if (sys->cfg.unk0 & 0x100) {
        if (sys->cfg.unk2C != NULL) {
            sys->cfg.unk4 |= 3;
            return 0;
        }
    } else if (sys->cfg.unk2C != NULL) {
        romAddr = sys->cfg.unk2C;
        flags = sys->cfg.unk4 | 1;
        goto load;
    }
    if (D_800A9740_main.fxCount == 0 || sys->cfg.unk28 == 0) {
        return 0;
    }
    if (D_800A9740_main.fxCount < sys->cfg.unk28) {
        func_80001134_main(0, 0x20);
        return 1;
    }
    romAddr = (u8 *)sys->cfg.unk10 + ((sys->cfg.unk28 - 1) * 0x208 + 0x10);
    flags = sys->cfg.unk4 | 2;
load:
    sys->cfg.unk4 = flags;
    func_80000FE4_main(buf, romAddr, 4, 0);
    D_800A9740_main.fxId = buf->id;
    buf->count = buf->bytes[3];
    size = (buf->count << 5) | 8;
    if ((sys->cfg.unk2C = func_800010B8_main(size)) == NULL) {
        return 2;
    }
    func_80000FE4_main(sys->cfg.unk2C, romAddr, size, 0);
    fx = sys->cfg.unk2C;
    fx->count = fx->bytes[3];
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/1140", func_80000650_main);
#endif

void func_800007FC_main(str800D5298 *cfg) {
    osCreateMesgQueue(&D_800A9718_main, D_800A9650_main, ARRAY_COUNT(D_800A9650_main));
    bzero(&D_800A9740_main, sizeof(str800D5298));
    D_800A9740_main.cfg.unk40 = 1;
    D_800A9740_main.cfg.unk44 = 0x3C;
    D_800CB8AC_main = 0;
    func_8000086C_main(cfg);
}

/* Initializes the sound system from the given configuration: sets up the audio
 * heap, reads the bank headers, then creates the audio manager, music player
 * and sound effect player. */
s32 func_8000086C_main(str800D5298 *cfg) {
    SndSys *sys;
    SndBankHeader *buf;
    s32 ret;
    s32 mbfArg2 = 0;
    s32 sbfArg2 = 0;
    s32 mbfArg3;
    s32 sbfArg3;

    sys = &D_800A9740_main;
    if (cfg->unk0 < 0) {
        sys->cfg.unk0 = 0;
        cfg->unk0 &= 0x7FFFFFFF;
    }
    if (cfg->unk0 & 0x40000000) {
        sys->cfg.unk0 &= ~0x184;
        cfg->unk0 &= ~0x40000000;
    }
    if (cfg->unk0 & 8) {
        sys->cfg.unk14 = cfg->unk14;
        sys->cfg.unk18 = cfg->unk18;
    }
    if (sys->cfg.unk14 == NULL || sys->cfg.unk18 == 0) {
        return 1;
    }
    alHeapInit(&D_800A9730_main, sys->cfg.unk14, sys->cfg.unk18);
    if (cfg->unk0 & 0x800000) {
        sys->cfg.unk68 = cfg->unk68;
    } else if (!(sys->cfg.unk0 & 0x800000)) {
        sys->cfg.unk68 = osCartRomInit();
    }
    buf = func_800010B8_main(sizeof(SndBankHeader));
    D_800A9740_main.buf = (u8 *)buf;
    if (buf == NULL) {
        return 2;
    }
    if (cfg->unk0 & 1) {
        sys->cfg.unk8 = cfg->unk8;
        if (sys->cfg.unk8 != NULL) {
            sys->cfg.unk0 = 0;
        }
    }
    if (cfg->unk0 & 2) {
        sys->cfg.unkC = cfg->unkC;
        if (!(cfg->unk0 & 1) && sys->cfg.unkC != NULL) {
            sys->cfg.unk0 = 0;
        }
    }
    if (sys->cfg.unk8 == NULL && sys->cfg.unkC == NULL) {
        return 3;
    }
    if (sys->cfg.unkC != NULL) {
        func_80000FE4_main(buf, sys->cfg.unkC, sizeof(SndBankHeader), 0);
        if (buf->magic == 'SBF0') {
            if (sys->cfg.unk8 == NULL) {
                func_80000540_main(buf, sys->cfg.unkC);
            }
            if (!(sys->cfg.unk0 & 0x40000)) {
                sys->cfg.unk54 = buf->unk_10;
            }
            if (!(sys->cfg.unk0 & 0x80000)) {
                sys->cfg.unk58 = buf->unk_12;
            }
            sbfArg3 = buf->unk_28;
            sbfArg2 = buf->unk_04;
        }
    }
    if (sys->cfg.unk8 != NULL) {
        func_80000FE4_main(buf, sys->cfg.unk8, sizeof(SndBankHeader), 0);
        if (buf->magic == 'MBF0') {
            func_80000540_main(buf, sys->cfg.unk8);
            if (!(sys->cfg.unk0 & 0x10000)) {
                sys->cfg.unk4C = buf->unk_10;
            }
            if (!(sys->cfg.unk0 & 0x20000)) {
                sys->cfg.unk50 = buf->unk_12;
            }
            mbfArg3 = buf->unk_28;
            mbfArg2 = buf->unk_04;
        }
    }
    if (cfg->unk0 & 4) {
        sys->cfg.unk10 = cfg->unk10;
    }
    if (cfg->unk0 & 0x10) {
        sys->cfg.unk1C = cfg->unk1C;
    }
    if (cfg->unk0 & 0x20) {
        sys->cfg.unk20 = cfg->unk20;
    }
    if (cfg->unk0 & 0x40) {
        sys->cfg.unk24 = cfg->unk24;
    }
    if (cfg->unk0 & 0x80) {
        sys->cfg.unk28 = cfg->unk28;
    }
    if (cfg->unk0 & 0x100) {
        sys->cfg.unk2C = cfg->unk2C;
    }
    if (cfg->unk0 & 0x200) {
        sys->cfg.unk30 = cfg->unk30;
    }
    if (cfg->unk0 & 0x400) {
        sys->cfg.unk34 = cfg->unk34;
    }
    if (cfg->unk0 & 0x800) {
        sys->cfg.unk38 = cfg->unk38;
    }
    if (cfg->unk0 & 0x1000) {
        sys->cfg.unk3C = cfg->unk3C;
    }
    if (cfg->unk0 & 0x2000) {
        sys->cfg.unk40 = cfg->unk40;
    }
    if (cfg->unk0 & 0x4000) {
        sys->cfg.unk44 = cfg->unk44;
    }
    if (cfg->unk0 & 0x8000) {
        sys->cfg.unk48 = cfg->unk48;
    }
    if (cfg->unk0 & 0x10000) {
        sys->cfg.unk4C = cfg->unk4C;
    }
    if (cfg->unk0 & 0x20000) {
        sys->cfg.unk50 = cfg->unk50;
    }
    if (cfg->unk0 & 0x40000) {
        sys->cfg.unk54 = cfg->unk54;
    }
    if (cfg->unk0 & 0x80000) {
        sys->cfg.unk58 = cfg->unk58;
    }
    if (cfg->unk0 & 0x100000) {
        sys->cfg.unk5C = cfg->unk5C;
    }
    if (cfg->unk0 & 0x200000) {
        sys->cfg.unk60 = cfg->unk60;
    }
    if (cfg->unk0 & 0x400000) {
        sys->cfg.unk64 = cfg->unk64;
    }
    sys->cfg.unk0 |= cfg->unk0;
    if ((cfg->unk0 & 0x100) && cfg->unk2C == NULL) {
        sys->cfg.unk0 &= ~0x100;
    }
    if ((ret = func_80000650_main()) != 0) {
        return ret + 100;
    }
    if ((ret = amCreateAudioMgr(&sys->cfg, &D_800A9730_main)) != 0) {
        return ret + 200;
    }
    if ((ret = func_80001E10_main(&D_800A9740_main, &D_800A9730_main, mbfArg2, mbfArg3)) != 0) {
        return ret + 300;
    }
    if ((ret = func_80006A8C_main(&D_800A9740_main, &D_800A9730_main, sbfArg2, sbfArg3)) != 0) {
        return ret + 400;
    }
    func_80001134_main(100, 0);
    func_80008678_main(&sys->cfg);
    return 0;
}

s32 func_80000DF0_main(void) {
    AudioManager *mus = func_800025B4_main();
    UnkAudio *se;

    if (mus != NULL && mus->playingCount != 0) {
        return 1;
    }
    se = func_8000704C_main();
    if (se != NULL) {
        if (se->unk_18 != 0) {
            return 1;
        }
        func_80006FC4_main();
    }
    if (mus != NULL) {
        func_80002528_main();
    }
    func_8000870C_main(&func_80000E9C_main()->cfg);
    if (mus != NULL) {
        func_800025C0_main();
    }
    if (se != NULL) {
        func_80007058_main();
    }
    return 0;
}

SndSys *func_80000E9C_main(void) {
    return &D_800A9740_main;
}

void func_80000EA8_main(str800D5298 *cfg) {
    bcopy(func_80000E9C_main(), cfg, sizeof(str800D5298));
}

s32 func_80000EDC_main(void) {
    return func_80000E9C_main()->fxCount;
}

s32 func_80000EFC_main(void) {
    return 0x660104;
}

s32 func_80000F08_main(s32 arg0) {
    return 0;
}

s32 func_80000F10_main(void) {
    return func_80000E9C_main()->unk_72;
}

void func_80000F30_main(u32 mono) {
    UnkAudio *se;
    s32 i;

    D_800CB8AC_main = mono & 1;
    se = func_8000704C_main();
    if (se != NULL) {
        for (i = 0; i < se->soundCount; i++) {
            if (se->sounds[i].flags & 3) {
                se->sounds[i].flags |= 0x20;
            } else {
                se->sounds[i].flags |= 0x8000;
            }
        }
    }
}

s32 func_80000FC4_main(void) {
    return func_80000E9C_main()->fxId;
}

/* Reads from ROM using PI DMA, in chunks of at most chunkSize bytes. */
#ifdef NON_MATCHING
/* Two of the argument register copies in the prologue are scheduled in a different order. */
void func_80000FE4_main(void *dst, void *romAddr, s32 size, s32 chunkSize) {
    OSIoMesg mesg;
    s32 len;

    if (chunkSize == 0) {
        chunkSize = size;
    }
    chunkSize += chunkSize & 1;
    while (size != 0) {
        len = size;
        if (chunkSize < size) {
            len = chunkSize;
        }
        mesg.hdr.pri = OS_MESG_PRI_NORMAL;
        mesg.hdr.retQueue = &D_800A9718_main;
        mesg.dramAddr = dst;
        mesg.devAddr = (u32)romAddr;
        mesg.size = len;
        osInvalDCache(dst, len);
        osEPiStartDma(D_800A9740_main.cfg.unk68, &mesg, OS_READ);
        osRecvMesg(&D_800A9718_main, NULL, OS_MESG_BLOCK);
        romAddr = (u8 *)romAddr + len;
        size -= len;
        dst = (u8 *)dst + len;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1140", func_80000FE4_main);
#endif

/* Allocates a single element of the given size from the audio heap, reporting a
 * fatal error if the allocation fails. This is the non-debug alHeapAlloc(). */
void *func_800010B8_main(s32 size) {
    void *ptr = alHeapDBAlloc(NULL, 0, &D_800A9730_main, 1, size);

    if (ptr == NULL) {
        func_80001134_main(0, 1);
    }
    return ptr;
}

void func_8000110C_main(s16 arg0) {
    func_80000E9C_main()->unk_72 = arg0;
}

s32 func_80001134_main(s32 arg0, s32 arg1) {
    return 0;
}

s16 func_8000113C_main(s32 arg0) {
    if (arg0 <= 0) {
        return 0;
    }
    return (arg0 << 8) | 0xFF;
}

// Possible file boundary: ROM 0x1D60 (msm "mus" code starts here). The text
// address is 16-aligned and the sys code above uses no data or rodata, but the
// function before it ends exactly here (no nop padding), and the sys bss ends at
// 0x800A97B8, which is not 16-aligned. So the mus/se player pointers
// (D_800A97B8/D_800A97BC) may be defined with the sys code, or this is not a
// real split.
INCLUDE_ASM("asm/nonmatchings/1140", func_80001160_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_8000124C_main);

s32 func_800012C4_main(SeqPlayer *seqPlayer) {
    return D_800A97B8_main->configVol * seqPlayer->evtVol * seqPlayer->trackVol * seqPlayer->fadeVol / 127 / 127 / 127 * D_800A97B8_main->masterVol / 127;
}

INCLUDE_ASM("asm/nonmatchings/1140", func_80001348_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80001408_main);

void func_80001ADC_main(SeqPlayer *seqPlayer) {
    s32 state = n_alCSPGetState(seqPlayer->seqp);

    seqPlayer->cspState = state;
    switch (state) {
        case 1:
            if (seqPlayer->state != 1) {
                seqPlayer->state = 4;
            }
            break;
        case 2:
            seqPlayer->state = 1;
            break;
        default:
            seqPlayer->state = 0;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/1140", func_80001B44_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80001BEC_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80001D20_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80001E10_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80002300_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800023B4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80002528_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800025B4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800025C0_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800025CC_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80002A28_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800032B4_main);

f32 func_800032CC_main(s32 arg0) {
    f32 base = 1.03099298f;
    f32 result = 1.0f;

    if (arg0 & 0xFF) {
        do {
            if (arg0 & 1) {
                result = result * base;
            }
            arg0 = (u8)arg0 >> 1;
            base = base * base;
        } while (arg0);
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/1140", func_80003310_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_8000332C_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800034D8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003524_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_8000354C_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003598_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800035C0_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800035E8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800036E8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800037C4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003810_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003848_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800038EC_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800039A4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003A24_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003A70_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003B70_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003BF4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003CB8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003DF4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003EE4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80003FB4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800048D0_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80004928_main);

void func_8000499C_main(GameSound *sound) {
    if (sound->state != 1) {
        if (sound->state > 0) {
            if (sound->state < 5) {
                D_800A97BC_main->unk_18++;
            }
        }
    } else if (sound->sndId < 0) {
        // The store lands in the delay slot of a branch-likely, so the state is only
        // cleared while the id is still valid. Keep the comparison as written.
        sound->state = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/1140", func_800049E8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80004D4C_main);

/**
 * Reads a big-endian style variable length quantity: each byte contributes its
 * low 7 bits, with bit 7 signalling that another byte follows. Only the final
 * byte is added unshifted, which is why it is kept out of the loop accumulator.
 */
s32 func_80005804_main(u8 **cursor) {
    s32 value = 0;
    s32 byte = *(*cursor)++;

    if (byte & 0x80) {
        do {
            value = ((byte & 0x7F) | value) << 7;
            byte = *(*cursor)++;
        } while (byte & 0x80);
    }
    return value + byte;
}

INCLUDE_ASM("asm/nonmatchings/1140", func_80005850_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80005BAC_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80005FE4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80006148_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800062A8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_8000658C_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80006830_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800068B8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80006A8C_main);

void func_80006CD4_main(s32 voiceSlot, s32 cmdType, s32 cmdArg) {
    u32 temp_s3;
    AudioCmd *cmd;
    s32 temp_v0_2;

    temp_s3 = osSetIntMask(1);
    cmd = &D_800A97BC_main->cmds[D_800A97BC_main->unk38];
    cmd->cmdType = cmdType;
    cmd->voiceSlot = voiceSlot;
    cmd->cmdArg = cmdArg;
    if (++D_800A97BC_main->unk38 >= 128) {
        func_80001134_main(0, 0x200);
        D_800A97BC_main->unk38 = 0;
    }
    osSetIntMask(temp_s3);
}

INCLUDE_ASM("asm/nonmatchings/1140", func_80006D80_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80006E30_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80006FC4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_8000704C_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007058_main);

s32 func_80007064_main(s32 arg0) {
    return func_80007080_main(arg0, 0);
}

INCLUDE_ASM("asm/nonmatchings/1140", func_80007080_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800072A4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800076B8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800078A4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800078CC_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800078F8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_8000793C_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800079CC_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007A10_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007A60_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007AF0_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007B28_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007BD4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007C80_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007D2C_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007DD8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007EC0_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007EF8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007F24_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80007FD4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_8000801C_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_8000810C_main);
