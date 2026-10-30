#include "common.h"
#include "PR/n_libaudio.h"
#include "math.h"

/* Oscillator types, as in the N64 SDK sequence player demos. */
#define TREMELO_SIN 1
#define TREMELO_SQR 2
#define TREMELO_DSC_SAW 3
#define TREMELO_ASC_SAW 4
#define VIBRATO_SIN 0x80
#define VIBRATO_SQR 0x81
#define VIBRATO_DSC_SAW 0x82
#define VIBRATO_ASC_SAW 0x83

#define OSC_HIGH 0
#define OSC_LOW 1

#define PI 3.1415927f
#define TWO_PI 6.2831855f

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

/* One entry of the music track table, read from the MBF0 bank. */
typedef struct {
    /* 0x00 */ u8 player; // low nibble: player index, high nibble: crossfade flag
    /* 0x01 */ u8 vol;
    /* 0x02 */ u8 bank;     // index of the bank inside the bank file
    /* 0x03 */ s8 bankFile; // index into the bank file table
    /* 0x04 */ u8 fadeTime; // crossfade time, in units of 10 frames
    /* 0x08 */ u8 *romAddr; // relative to the MBF0 bank until loaded
    /* 0x0C */ s32 size;
} MusTrack; // size: 0x10

/* One entry of the music bank file table, read from the MBF0 bank. */
typedef struct {
    /* 0x00 */ u8 *ctlAddr; // relative to the MBF0 bank until loaded
    /* 0x04 */ s32 ctlSize;
    /* 0x08 */ u8 *tblAddr; // relative to the MBF0 bank until loaded
    /* 0x0C */ s32 unk_0C;
} MusBankFile; // size: 0x10

/* Oscillator state handed out to the sequence players, as in the oscData of
 * the N64 SDK sequence player demos. */
typedef struct MusOsc_s {
    /* 0x00 */ struct MusOsc_s *next;
    /* 0x04 */ u8 type;
    /* 0x05 */ u8 stateFlags;
    /* 0x06 */ u16 maxCount;
    /* 0x08 */ u16 curCount;
    /* 0x0C */ union {
        struct {
            u8 halfdepth;
            u8 baseVol;
        } tsin;
        struct {
            u8 curVal;
            u8 hiVal;
            u8 loVal;
        } tsqr;
        struct {
            u8 baseVol;
            u8 depth;
        } tsaw;
        struct {
            f32 depthcents;
        } vsin;
        struct {
            f32 loRatio;
            f32 hiRatio;
        } vsqr;
        struct {
            s32 hicents;
            s32 centsrange;
        } vdsaw;
        struct {
            s32 locents;
            s32 centsrange;
        } vasaw;
    } data;
} MusOsc; // size: 0x14

typedef struct {
    /* 0x00 */ N_ALCSPlayer *seqp;
    /* 0x04 */ u8 *seqData; // raw sequence data, DMA'd in per track
    /* 0x08 */ ALBankFile *bankFile;
    /* 0x0C */ ALCSeq *seq;
    /* 0x10 */ s32 seqDataSize;
    /* 0x14 */ s32 flags;    // 0x1 stopped, 0x2/0x8 queued, 0x4/0x20 no fade, 0x10 play, 0x40 fading
    /* 0x18 */ s16 curTrack; // track whose data is loaded
    /* 0x1A */ s16 newTrack; // track requested by the latest event
    /* 0x1C */ s32 cspState;
    /* 0x20 */ s32 state;
    /* 0x24 */ s32 fadeStep;   // 0x7F000000 / fadeTime
    /* 0x28 */ s32 fadeTime;   // frames left, negative while fading in
    /* 0x2C */ s8 fadeVol;     // current fade level, 0 to 0x7F
    /* 0x2D */ s8 bankFileIdx; // bank file loaded into bankFile, -1 for none
    /* 0x2E */ s8 trackVol;    // volume of the current track
    /* 0x2F */ s8 evtVol;      // volume of the latest event
    /* 0x30 */ s8 waitPlayer;  // player that must stop before this one resumes
    /* 0x31 */ u8 resumeFade;  // fade-in time used when resuming, in units of 10 frames
    /* 0x32 */ s8 crossfade;   // set when the current track was started with a crossfade
    /* 0x33 */ s8 unk_33;
} SeqPlayer; // size: 0x34

typedef struct {
    /* 0x00 */ SeqPlayer *players;
    /* 0x04 */ MusTrack *tracks;
    /* 0x08 */ MusBankFile *bankFiles;
    /* 0x0C */ MusOsc *oscs;
    /* 0x10 */ MusOsc *freeOscs;
    /* 0x14 */ union {
        s32 all;
        s16 flag[2]; // [0] set by the API functions, [1] by the periodic proc
    } busy;
    /* 0x18 */ s8 playerCount;
    /* 0x19 */ s8 playingCount;
    /* 0x1A */ s8 masterVol; // overall volume, set by volume events
    /* 0x1B */ s8 configVol; // overall volume, taken from the audio config
    /* 0x1C */ s16 trackCount;
    /* 0x1E */ s16 eventCount;
    /* 0x20 */ AudioCmd events[0x40];
} AudioManager; // size: 0x220

/* Optional parameters for starting a music track. */
typedef struct {
    /* 0x00 */ s32 flags; // which of the fields below are valid
    /* 0x04 */ s32 player;
    /* 0x08 */ s32 crossfade;
    /* 0x0C */ s32 vol;
    /* 0x10 */ s32 fadeIn;
} MusPlayParam;

/* MIDI channel settings of a playing music track. */
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 program;
    /* 0x08 */ s32 vol;
    /* 0x0C */ s32 pan;
    /* 0x10 */ s32 fxMix;
} MusChlInfo;

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
void func_80001348_main(SeqPlayer *player, s32 fadeTime);
void func_80001408_main(void);
void func_80002300_main(s32 player, s32 type, s32 arg);
ALMicroTime func_800025CC_main(void **oscState, f32 *initVal, u8 oscType, u8 oscRate, u8 oscDepth, u8 oscDelay);
ALMicroTime func_80002A28_main(void *oscState, f32 *updateVal);
void func_800032B4_main(void *oscState);
s32 func_8000332C_main(s32 trackId, MusPlayParam *param);
f32 func_800032CC_main(s32 arg0);
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
/* Loads a bank file for the player, copying it from another player that
 * already has it loaded when possible. */
void func_80001160_main(SeqPlayer *player, s8 bankFileIdx, s32 chunkSize) {
    MusBankFile *bankFile;
    SeqPlayer *other;
    s32 i;

    if (player->bankFileIdx != bankFileIdx) {
        bankFile = &D_800A97B8_main->bankFiles[bankFileIdx];
        for (i = 0; i < D_800A97B8_main->playerCount; i++) {
            other = &D_800A97B8_main->players[i];
            if (other->bankFileIdx == bankFileIdx) {
                bcopy(other->bankFile, player->bankFile, bankFile->ctlSize);
                player->bankFileIdx = bankFileIdx;
                return;
            }
        }
        func_80000FE4_main(player->bankFile, bankFile->ctlAddr, bankFile->ctlSize, chunkSize);
        alBnkfNew(player->bankFile, bankFile->tblAddr);
        player->bankFileIdx = bankFileIdx;
    }
}

/* Loads the sequence data of the requested track, then hands it to the player. */
void func_8000124C_main(SeqPlayer *player) {
    MusTrack *track;

    if (player->curTrack != player->newTrack) {
        player->curTrack = player->newTrack;
        track = &D_800A97B8_main->tracks[player->newTrack];
        func_80000FE4_main(player->seqData, track->romAddr, track->size, 0x4000);
    }
    n_alCSeqNew(player->seq, player->seqData);
    n_alCSPSetSeq(player->seqp, player->seq);
}

s32 func_800012C4_main(SeqPlayer *seqPlayer) {
    return D_800A97B8_main->configVol * seqPlayer->evtVol * seqPlayer->trackVol * seqPlayer->fadeVol / 127 / 127 / 127 * D_800A97B8_main->masterVol / 127;
}

/* Queues the player to start, fading in over the given number of frames. */
void func_80001348_main(SeqPlayer *player, s32 fadeTime) {
    if (!(player->flags & 0x40)) {
        player->flags &= ~8;
        if (!(player->flags & 1)) {
            if (fadeTime != 0 && player->fadeTime <= 0) {
                player->fadeTime = (fadeTime > 0) ? -fadeTime : -1;
                player->fadeStep = 0x7F000000 / -player->fadeTime;
                player->fadeVol = 0;
                n_alCSPSetVol(player->seqp, 0);
            }
            player->flags |= 0x10;
        }
    }
}

/* Processes the events queued by the API functions. */
void func_80001408_main(void) {
    AudioCmd *event;
    SeqPlayer *player;
    s32 time;
    s32 fadeTime;
    s32 i;
    s32 j;

    for (i = 0; i < D_800A97B8_main->eventCount; i++) {
        event = &D_800A97B8_main->events[i];
        player = &D_800A97B8_main->players[event->voiceSlot];
        switch (event->cmdType) {
            case 0:
                player->flags |= 2;
                break;
            case 1:
                player->flags = (player->flags & ~0x18) | 1;
                player->newTrack = (s16)event->cmdArg;
                player->crossfade = 0;
                break;
            case 2:
                player->evtVol = (u8)event->cmdArg;
                if (player->flags & 3) {
                    player->flags |= 4;
                } else {
                    n_alCSPSetVol(player->seqp, func_8000113C_main(func_800012C4_main(player)));
                }
                break;
            case 3:
                for (j = 0; j < D_800A97B8_main->playerCount; j++) {
                    player = &D_800A97B8_main->players[j];
                    player->evtVol = (u8)event->cmdArg;
                    if (player->flags & 3) {
                        player->flags |= 4;
                    } else {
                        n_alCSPSetVol(player->seqp, func_8000113C_main(func_800012C4_main(player)));
                    }
                }
                break;
            case 4:
                D_800A97B8_main->masterVol = (u8)event->cmdArg;
                for (j = 0; j < D_800A97B8_main->playerCount; j++) {
                    player = &D_800A97B8_main->players[j];
                    player->fadeTime = 0;
                    player->fadeVol = 0x7F;
                    n_alCSPSetVol(player->seqp, func_8000113C_main(func_800012C4_main(player)));
                }
                break;
            case 6:
                if (!(player->flags & 1)) {
                    n_alCSPStop(player->seqp);
                    player->state = 1;
                }
                player->flags = 0;
                break;
            case 7:
                for (j = 0; j < D_800A97B8_main->playerCount; j++) {
                    player = &D_800A97B8_main->players[j];
                    if (!(player->flags & 1)) {
                        n_alCSPStop(player->seqp);
                        player->state = 1;
                    }
                    player->flags = 0;
                }
                break;
            case 8:
                time = event->cmdArg;
                if (time <= 0) {
                    time = 1;
                }
                player->fadeTime = time;
                player->fadeStep = 0x7F000000 / time;
                player->fadeVol = 0x7F;
                break;
            case 9:
                for (j = 0; j < D_800A97B8_main->playerCount; j++) {
                    player = &D_800A97B8_main->players[j];
                    if (player->state >= 3) {
                        time = event->cmdArg;
                        if (time <= 0) {
                            time = 1;
                        }
                        player->fadeTime = time;
                        player->fadeStep = 0x7F000000 / time;
                        player->fadeVol = 0x7F;
                    }
                }
                break;
            case 10:
                if (!(player->flags & 1)) {
                    n_alCSPStop(player->seqp);
                }
                player->flags = (player->flags | 8) & ~0x10;
                break;
            case 11:
                for (j = 0; j < D_800A97B8_main->playerCount; j++) {
                    player = &D_800A97B8_main->players[j];
                    if (!(player->flags & 1)) {
                        n_alCSPStop(player->seqp);
                    }
                    player->flags = (player->flags | 8) & ~0x10;
                }
                break;
            case 12:
                func_80001348_main(player, event->cmdArg);
                break;
            case 13:
                for (j = 0; j < D_800A97B8_main->playerCount; j++) {
                    player = &D_800A97B8_main->players[j];
                    if (player->flags & 8) {
                        func_80001348_main(player, event->cmdArg);
                    }
                }
                break;
            case 14:
                time = event->cmdArg;
                if (time != 0) {
                    fadeTime = (time > 0) ? -time : -1;
                    player->fadeTime = fadeTime;
                    player->fadeStep = 0x7F000000 / -fadeTime;
                    player->fadeVol = 0;
                    if (player->flags & 3) {
                        player->flags |= 0x20;
                    } else {
                        n_alCSPSetVol(player->seqp, 0);
                    }
                }
                break;
            case 15:
                player->flags = (player->flags & ~0x18) | 1;
                player->newTrack = (s16)event->cmdArg;
                player->crossfade = 1;
                for (j = 0; j < D_800A97B8_main->playerCount; j++) {
                    if (j != event->voiceSlot) {
                        player = &D_800A97B8_main->players[j];
                        if (player->state >= 2) {
                            if (player->state == 4) {
                                n_alCSPStop(player->seqp);
                            }
                            player->flags = (player->flags | 8) & ~0x10;
                            player->fadeTime = 0;
                            player->waitPlayer = event->voiceSlot;
                            player->resumeFade = D_800A97B8_main->tracks[player->newTrack].fadeTime;
                            player->flags |= 0x40;
                        }
                    }
                }
                break;
        }
    }
    D_800A97B8_main->eventCount = 0;
}

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

void func_80001B44_main(SeqPlayer *player) {
    if (player->cspState < 3) {
        if (player->cspState > 0) {
            if (player->flags & 0x10) {
                player->state = 4;
            }
            if (player->flags & 8) {
                player->state = 2;
            }
            return;
        }
    }
    if (player->flags & 8) {
        player->state = 2;
    }
    if (player->flags & 0x10) {
        n_alCSPPlay(player->seqp);
        player->flags &= ~0x10;
        player->state = 4;
    }
}

/* Starts the requested track once the sequence player has stopped. */
void func_80001BEC_main(SeqPlayer *player) {
    MusTrack *track;
    s32 vol;

    if (player->flags & 1) {
        player->state = 3;
        if (player->cspState == 1) {
            n_alCSPStop(player->seqp);
        } else if (player->cspState != 2) {
            track = &D_800A97B8_main->tracks[player->newTrack];
            func_80001160_main(player, track->bankFile, 0x4000);
            n_alCSPSetBank(player->seqp, player->bankFile->bankArray[track->bank]);
            func_8000124C_main(player);
            player->trackVol = track->vol;
            if (!(player->flags & 4)) {
                player->evtVol = 0x7F;
            }
            if (!(player->flags & 0x20)) {
                player->fadeVol = 0x7F;
                player->fadeTime = 0;
                vol = func_800012C4_main(player);
            } else {
                vol = 0;
            }
            n_alCSPSetVol(player->seqp, func_8000113C_main(vol));
            player->flags &= ~0x67;
            if (!(player->flags & 8)) {
                n_alCSPPlay(player->seqp);
                player->state = 4;
            }
        }
    }
}

/* Steps the player's fade out or fade in by one frame. */
void func_80001D20_main(SeqPlayer *player) {
    s32 vol;

    if (player->fadeTime > 0) {
        if (--player->fadeTime != 0) {
            vol = (player->fadeStep * player->fadeTime) >> 24;
            if (vol != player->fadeVol) {
                player->fadeVol = vol;
                n_alCSPSetVol(player->seqp, func_8000113C_main(func_800012C4_main(player)));
            }
        } else {
            n_alCSPStop(player->seqp);
            player->state = 1;
        }
    }
    if (player->fadeTime < 0) {
        if (++player->fadeTime != 0) {
            vol = 0x7F - ((-player->fadeTime * player->fadeStep) >> 24);
        } else {
            vol = 0x7F;
        }
        if (vol != player->fadeVol) {
            player->fadeVol = vol;
            n_alCSPSetVol(player->seqp, func_8000113C_main(func_800012C4_main(player)));
        }
    }
}

/* Creates the music players from the track and bank file tables of the MBF0
 * bank. */
s32 func_80001E10_main(SndSys *sys, ALHeap *heap, s32 trackCount, s32 vol) {
    str800D5298 *cfg = &sys->cfg;
    s32 seqSize[5];
    ALSeqpConfig config;
    u8 *romAddr;
    MusTrack *track;
    MusBankFile *bankFile;
    ALBankFile *sharedBankFile;
    SeqPlayer *player;
    MusOsc *osc;
    s32 playerCount;
    s32 bankFileCount;
    s32 maxCtlSize;
    s32 oscCount;
    s32 size;
    s32 i;

    if (trackCount == 0) {
        D_800A97B8_main = NULL;
        return 0;
    }
    if ((D_800A97B8_main = func_800010B8_main(sizeof(AudioManager))) == NULL) {
        return 1;
    }
    bzero(seqSize, sizeof(seqSize));
    size = trackCount * sizeof(MusTrack);
    if ((D_800A97B8_main->tracks = func_800010B8_main(size)) == NULL) {
        return 2;
    }
    romAddr = (u8 *)cfg->unk8 + sizeof(SndBankHeader);
    func_80000FE4_main(D_800A97B8_main->tracks, romAddr, size, 0);
    bankFileCount = 0;
    playerCount = 0;
    for (i = 0; i < trackCount; i++) {
        track = &D_800A97B8_main->tracks[i];
        if (track->romAddr != NULL && track->size != 0) {
            track->romAddr += (u32)cfg->unk8;
            size = track->player & 0xF;
            if (playerCount < size) {
                playerCount = size;
            }
            if (seqSize[size] < track->size) {
                seqSize[size] = track->size;
            }
            if (bankFileCount < track->bankFile) {
                bankFileCount = track->bankFile;
            }
        }
    }
    bankFileCount++;
    playerCount++;
    size = bankFileCount * sizeof(MusBankFile);
    if ((D_800A97B8_main->bankFiles = func_800010B8_main(size)) == NULL) {
        return 3;
    }
    romAddr = (u8 *)cfg->unk8 + (trackCount * sizeof(MusTrack) + sizeof(SndBankHeader));
    func_80000FE4_main(D_800A97B8_main->bankFiles, romAddr, size, 0);
    maxCtlSize = 0;
    for (i = 0; i < bankFileCount; i++) {
        bankFile = &D_800A97B8_main->bankFiles[i];
        bankFile->ctlAddr += (u32)cfg->unk8;
        bankFile->tblAddr += (u32)cfg->unk8;
        if (maxCtlSize < bankFile->ctlSize) {
            maxCtlSize = bankFile->ctlSize;
        }
    }
    if (bankFileCount == 1) {
        if ((sharedBankFile = func_800010B8_main(maxCtlSize)) == NULL) {
            return 4;
        }
        func_80000FE4_main(sharedBankFile, bankFile->ctlAddr, bankFile->ctlSize, 0);
        alBnkfNew(sharedBankFile, bankFile->tblAddr);
    } else {
        sharedBankFile = NULL;
    }
    config.maxVoices = cfg->unk4C;
    config.maxEvents = cfg->unk50;
    config.maxChannels = 16;
    config.debugFlags = 0;
    config.heap = heap;
    config.initOsc = func_800025CC_main;
    config.updateOsc = func_80002A28_main;
    config.stopOsc = func_800032B4_main;
    if ((D_800A97B8_main->players = func_800010B8_main(playerCount * sizeof(SeqPlayer))) == NULL) {
        return 5;
    }
    for (i = 0; i < playerCount; i++) {
        player = &D_800A97B8_main->players[i];
        player->flags = 0;
        player->state = 0;
        player->fadeTime = 0;
        player->curTrack = -1;
        if ((player->seqp = func_800010B8_main(sizeof(N_ALCSPlayer))) == NULL) {
            return 6;
        }
        n_alCSPNew(player->seqp, &config);
        if ((player->seq = func_800010B8_main(sizeof(ALCSeq))) == NULL) {
            return 7;
        }
        if (seqSize[i] & 1) {
            seqSize[i]++;
        }
        if ((player->seqData = func_800010B8_main(seqSize[i])) == NULL) {
            return 8;
        }
        player->seqDataSize = seqSize[i];
        if (sharedBankFile != NULL) {
            player->bankFile = sharedBankFile;
            player->bankFileIdx = 0;
        } else {
            if ((player->bankFile = func_800010B8_main(maxCtlSize)) == NULL) {
                return 9;
            }
            player->bankFileIdx = -1;
            D_800A97B8_main->playerCount = i;
            func_80001160_main(player, 0, 0);
        }
    }
    oscCount = playerCount * cfg->unk4C;
    if ((D_800A97B8_main->oscs = func_800010B8_main(oscCount * sizeof(MusOsc))) == NULL) {
        return 10;
    }
    osc = D_800A97B8_main->freeOscs = D_800A97B8_main->oscs;
    oscCount--;
    for (i = 0; i < oscCount; i++) {
        osc->next = &D_800A97B8_main->oscs[i + 1];
        osc = osc->next;
    }
    osc->next = NULL;
    D_800A97B8_main->playerCount = playerCount;
    D_800A97B8_main->trackCount = trackCount;
    D_800A97B8_main->configVol = vol;
    D_800A97B8_main->masterVol = 0x7F;
    D_800A97B8_main->eventCount = 0;
    D_800A97B8_main->busy.flag[0] = 0;
    D_800A97B8_main->busy.flag[1] = 0;
    return 0;
}

/* Queues an event for the periodic proc to process. */
void func_80002300_main(s32 player, s32 type, s32 arg) {
    u32 mask = osSetIntMask(1);
    AudioCmd *event = &D_800A97B8_main->events[D_800A97B8_main->eventCount];

    event->cmdType = type;
    event->voiceSlot = player;
    event->cmdArg = arg;
    if (++D_800A97B8_main->eventCount >= ARRAY_COUNT(D_800A97B8_main->events)) {
        func_80001134_main(0, 0x100);
        D_800A97B8_main->eventCount = 0;
    }
    osSetIntMask(mask);
}

void func_800023B4_main(void) {
    SeqPlayer *player;
    s32 i;

    if (D_800A97B8_main != NULL && D_800A97B8_main->busy.all == 0) {
        D_800A97B8_main->busy.flag[1] = 1;
        func_80001408_main();
        D_800A97B8_main->playingCount = 0;
        for (i = 0; i < D_800A97B8_main->playerCount; i++) {
            player = &D_800A97B8_main->players[i];
            func_80001ADC_main(player);
            func_80001BEC_main(player);
            func_80001B44_main(player);
            if ((player->flags & 0x40) && D_800A97B8_main->players[player->waitPlayer].state < 2) {
                player->flags &= ~0x40;
                func_80001348_main(player, player->resumeFade * 10);
            }
            if (player->state >= 2) {
                D_800A97B8_main->playingCount++;
            }
            if (player->state >= 3) {
                func_80001D20_main(player);
            }
        }
        D_800A97B8_main->busy.flag[1] = 0;
    }
}

void func_80002528_main(void) {
    SeqPlayer *player;
    s32 i;

    if (D_800A97B8_main != NULL) {
        for (i = 0; i < D_800A97B8_main->playerCount; i++) {
            player = &D_800A97B8_main->players[i];
            n_alCSPStop(player->seqp);
            n_alCSPDelete(player->seqp);
        }
    }
}

AudioManager *func_800025B4_main(void) {
    return D_800A97B8_main;
}

void func_800025C0_main(void) {
    D_800A97B8_main = NULL;
}

/* Oscillator init callback for the sequence players, based on the initOsc()
 * of the N64 SDK sequence player demos. */
ALMicroTime func_800025CC_main(void **oscState, f32 *initVal, u8 oscType, u8 oscRate, u8 oscDepth, u8 oscDelay) {
    MusOsc *osc;
    ALMicroTime deltaTime = 0;
    s32 cents;

    if (D_800A97B8_main->freeOscs != NULL) {
        osc = D_800A97B8_main->freeOscs;
        D_800A97B8_main->freeOscs = osc->next;
        osc->type = oscType;
        *oscState = osc;
        deltaTime = oscDelay << 14;
        switch (oscType) {
            case TREMELO_SIN:
                osc->curCount = 0;
                osc->maxCount = 259 - oscRate;
                osc->data.tsin.halfdepth = oscDepth >> 1;
                osc->data.tsin.baseVol = AL_VOL_FULL - osc->data.tsin.halfdepth;
                *initVal = (f32)osc->data.tsin.baseVol;
                break;
            case TREMELO_SQR:
                osc->maxCount = 256 - oscRate;
                osc->curCount = osc->maxCount;
                osc->stateFlags = OSC_HIGH;
                osc->data.tsqr.loVal = AL_VOL_FULL - oscDepth;
                osc->data.tsqr.hiVal = AL_VOL_FULL;
                osc->data.tsqr.curVal = AL_VOL_FULL;
                *initVal = (f32)AL_VOL_FULL;
                break;
            case TREMELO_DSC_SAW:
                osc->maxCount = 256 - oscRate;
                osc->curCount = 0;
                osc->data.tsaw.depth = oscDepth;
                osc->data.tsaw.baseVol = AL_VOL_FULL;
                *initVal = (f32)osc->data.tsaw.baseVol;
                break;
            case TREMELO_ASC_SAW:
                osc->maxCount = 256 - oscRate;
                osc->curCount = 0;
                osc->data.tsaw.depth = oscDepth;
                osc->data.tsaw.baseVol = AL_VOL_FULL - oscDepth;
                *initVal = (f32)osc->data.tsaw.baseVol;
                break;
            case 5:
                osc->curCount = 0;
                osc->maxCount = (259 - oscRate) / 4;
                osc->data.tsin.halfdepth = oscDepth >> 1;
                osc->data.tsin.baseVol = AL_VOL_FULL - osc->data.tsin.halfdepth;
                osc->stateFlags = 0;
                *initVal = (f32)osc->data.tsin.baseVol;
                break;
            case 6:
            case 7:
                osc->curCount = 0;
                osc->maxCount = 259 - oscRate;
                osc->data.tsin.halfdepth = oscDepth >> 1;
                osc->data.tsin.baseVol = AL_VOL_FULL;
                *initVal = (f32)osc->data.tsin.baseVol;
                break;
            case 8:
            case 9:
                osc->curCount = 0;
                osc->maxCount = (259 - oscRate) / 4;
                osc->data.tsin.halfdepth = oscDepth >> 1;
                osc->data.tsin.baseVol = AL_VOL_FULL;
                osc->stateFlags = 0;
                *initVal = (f32)osc->data.tsin.baseVol;
                break;
            case VIBRATO_SIN:
            case 0x8A:
                osc->data.vsin.depthcents = func_800032CC_main(oscDepth);
                osc->curCount = 0;
                osc->maxCount = 259 - oscRate;
                *initVal = 1.0f;
                break;
            case VIBRATO_SQR:
                osc->maxCount = 256 - oscRate;
                osc->curCount = osc->maxCount;
                osc->stateFlags = OSC_HIGH;
                cents = func_800032CC_main(oscDepth);
                osc->data.vsqr.loRatio = alCents2Ratio(-cents);
                osc->data.vsqr.hiRatio = alCents2Ratio(cents);
                *initVal = osc->data.vsqr.hiRatio;
                break;
            case VIBRATO_DSC_SAW:
                osc->maxCount = 256 - oscRate;
                osc->curCount = osc->maxCount;
                cents = func_800032CC_main(oscDepth);
                osc->data.vdsaw.hicents = cents;
                osc->data.vdsaw.centsrange = 2 * cents;
                *initVal = alCents2Ratio(osc->data.vdsaw.hicents);
                break;
            case VIBRATO_ASC_SAW:
                osc->maxCount = 256 - oscRate;
                osc->curCount = osc->maxCount;
                cents = func_800032CC_main(oscDepth);
                osc->data.vasaw.locents = -cents;
                osc->data.vasaw.centsrange = 2 * cents;
                *initVal = alCents2Ratio(osc->data.vasaw.locents);
                break;
            case 0x84:
                osc->data.vsin.depthcents = func_800032CC_main(oscDepth);
                osc->stateFlags = 0;
                osc->curCount = 0;
                osc->maxCount = (259 - oscRate) / 4;
                *initVal = 1.0f;
                break;
            case 0x85:
                osc->maxCount = 256 - oscRate;
                osc->curCount = osc->maxCount;
                osc->stateFlags = 0;
                cents = func_800032CC_main(oscDepth);
                osc->data.vsqr.loRatio = alCents2Ratio(-cents);
                osc->data.vsqr.hiRatio = alCents2Ratio(cents);
                *initVal = 1.0f;
                break;
            case 0x86:
                osc->maxCount = 256 - oscRate;
                osc->curCount = osc->maxCount;
                osc->stateFlags = 1;
                cents = func_800032CC_main(oscDepth);
                osc->data.vsqr.loRatio = alCents2Ratio(-cents);
                osc->data.vsqr.hiRatio = alCents2Ratio(cents);
                *initVal = 1.0f;
                break;
            case 0x87:
                osc->maxCount = 256 - oscRate;
                osc->curCount = 0;
                cents = func_800032CC_main(oscDepth);
                osc->data.vdsaw.hicents = cents;
                osc->data.vdsaw.centsrange = 2 * cents;
                *initVal = 1.0f;
                break;
            case 0x88:
                osc->maxCount = 256 - oscRate;
                osc->curCount = 0;
                cents = func_800032CC_main(oscDepth);
                osc->data.vasaw.locents = -cents;
                osc->data.vasaw.centsrange = 2 * cents;
                *initVal = 1.0f;
                break;
            case 0x89:
                osc->data.vsin.depthcents = func_800032CC_main(oscDepth);
                osc->stateFlags = 2;
                osc->curCount = 0;
                osc->maxCount = (259 - oscRate) / 4;
                *initVal = 1.0f;
                break;
            default:
                deltaTime = 0xFF << 14;
                break;
        }
    }
    return deltaTime;
}

/* Oscillator update callback for the sequence players, based on the
 * updateOsc() of the N64 SDK sequence player demos. */
ALMicroTime func_80002A28_main(void *oscState, f32 *updateVal) {
    MusOsc *osc = oscState;
    ALMicroTime deltaTime = AL_USEC_PER_FRAME;
    f32 tmpflt;

    switch (osc->type) {
        case TREMELO_SIN:
            osc->curCount++;
            if (osc->curCount >= osc->maxCount) {
                osc->curCount = 0;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            tmpflt = sinf(tmpflt * TWO_PI);
            tmpflt = tmpflt * (f32)osc->data.tsin.halfdepth;
            *updateVal = (f32)osc->data.tsin.baseVol + tmpflt;
            break;
        case TREMELO_SQR:
            if (osc->stateFlags == OSC_HIGH) {
                *updateVal = (f32)osc->data.tsqr.loVal;
                osc->stateFlags = OSC_LOW;
            } else {
                *updateVal = (f32)osc->data.tsqr.hiVal;
                osc->stateFlags = OSC_HIGH;
            }
            deltaTime *= osc->maxCount;
            break;
        case TREMELO_DSC_SAW:
            osc->curCount++;
            if (osc->curCount > osc->maxCount) {
                osc->curCount = 0;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            tmpflt *= (f32)osc->data.tsaw.depth;
            *updateVal = (f32)osc->data.tsaw.baseVol - tmpflt;
            break;
        case TREMELO_ASC_SAW:
            osc->curCount++;
            if (osc->curCount > osc->maxCount) {
                osc->curCount = 0;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            tmpflt *= (f32)osc->data.tsaw.depth;
            *updateVal = (f32)osc->data.tsaw.baseVol + tmpflt;
            break;
        case 5:
            osc->curCount++;
            if (osc->curCount >= osc->maxCount) {
                osc->curCount = 0;
                osc->stateFlags = (osc->stateFlags + 1) & 3;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            switch (osc->stateFlags) {
                case 0:
                    tmpflt *= (f32)osc->data.tsin.halfdepth;
                    break;
                case 1:
                    tmpflt = (1.0f - tmpflt) * (f32)osc->data.tsin.halfdepth;
                    break;
                case 2:
                    tmpflt = -tmpflt * (f32)osc->data.tsin.halfdepth;
                    break;
                case 3:
                    tmpflt = (tmpflt - 1.0f) * (f32)osc->data.tsin.halfdepth;
                    break;
            }
            *updateVal = (f32)osc->data.tsin.baseVol + tmpflt;
            break;
        case 6:
            osc->curCount++;
            if (osc->curCount >= osc->maxCount) {
                osc->curCount = 0;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            tmpflt = sinf(tmpflt * PI);
            tmpflt = tmpflt * (f32)osc->data.tsin.halfdepth;
            if (tmpflt < 0.0f) {
                *updateVal = (f32)osc->data.tsin.baseVol + tmpflt;
            } else {
                *updateVal = (f32)osc->data.tsin.baseVol - tmpflt;
            }
            break;
        case 7:
            osc->curCount++;
            if (osc->curCount >= osc->maxCount) {
                osc->curCount = 0;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            tmpflt = sinf(tmpflt * PI);
            tmpflt = tmpflt * (f32)osc->data.tsin.halfdepth;
            if (tmpflt < 0.0f) {
                *updateVal = (f32)osc->data.tsin.baseVol - tmpflt;
            } else {
                *updateVal = (f32)osc->data.tsin.baseVol + tmpflt;
            }
            break;
        case 8:
            osc->curCount++;
            if (osc->curCount >= osc->maxCount) {
                osc->curCount = 0;
                osc->stateFlags = (osc->stateFlags + 1) & 1;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            switch (osc->stateFlags) {
                case 0:
                    tmpflt = -tmpflt * (f32)osc->data.tsin.halfdepth;
                    break;
                case 1:
                    tmpflt = (tmpflt - 1.0f) * (f32)osc->data.tsin.halfdepth;
                    break;
            }
            *updateVal = (f32)osc->data.tsin.baseVol + tmpflt;
            break;
        case 9:
            osc->curCount++;
            if (osc->curCount >= osc->maxCount) {
                osc->curCount = 0;
                osc->stateFlags = (osc->stateFlags + 1) & 1;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            switch (osc->stateFlags) {
                case 0:
                    tmpflt *= (f32)osc->data.tsin.halfdepth;
                    break;
                case 1:
                    tmpflt = (1.0f - tmpflt) * (f32)osc->data.tsin.halfdepth;
                    break;
            }
            *updateVal = (f32)osc->data.tsin.baseVol + tmpflt;
            break;
        case VIBRATO_SIN:
            osc->curCount++;
            if (osc->curCount >= osc->maxCount) {
                osc->curCount = 0;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            tmpflt = sinf(tmpflt * TWO_PI) * osc->data.vsin.depthcents;
            *updateVal = alCents2Ratio(tmpflt);
            break;
        case VIBRATO_SQR:
        case 0x85:
        case 0x86:
            if (osc->stateFlags == OSC_HIGH) {
                osc->stateFlags = OSC_LOW;
                *updateVal = osc->data.vsqr.loRatio;
            } else {
                osc->stateFlags = OSC_HIGH;
                *updateVal = osc->data.vsqr.hiRatio;
            }
            deltaTime *= osc->maxCount;
            break;
        case VIBRATO_DSC_SAW:
        case 0x87:
            osc->curCount++;
            if (osc->curCount > osc->maxCount) {
                osc->curCount = 0;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            tmpflt *= (f32)osc->data.vdsaw.centsrange;
            tmpflt = (f32)osc->data.vdsaw.hicents - tmpflt;
            *updateVal = alCents2Ratio(tmpflt);
            break;
        case VIBRATO_ASC_SAW:
        case 0x88:
            osc->curCount++;
            if (osc->curCount > osc->maxCount) {
                osc->curCount = 0;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            tmpflt *= (f32)osc->data.vasaw.centsrange;
            tmpflt = tmpflt + (f32)osc->data.vasaw.locents;
            *updateVal = alCents2Ratio(tmpflt);
            break;
        case 0x84:
        case 0x89:
            osc->curCount++;
            if (osc->curCount >= osc->maxCount) {
                osc->curCount = 0;
                osc->stateFlags = (osc->stateFlags + 1) & 3;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            switch (osc->stateFlags) {
                case 0:
                    tmpflt *= osc->data.vsin.depthcents;
                    break;
                case 1:
                    tmpflt = (1.0f - tmpflt) * osc->data.vsin.depthcents;
                    break;
                case 2:
                    tmpflt = -tmpflt * osc->data.vsin.depthcents;
                    break;
                case 3:
                    tmpflt = (tmpflt - 1.0f) * osc->data.vsin.depthcents;
                    break;
            }
            *updateVal = alCents2Ratio(tmpflt);
            break;
        case 0x8A:
            osc->curCount++;
            if (osc->curCount >= osc->maxCount) {
                osc->curCount = 0;
            }
            tmpflt = (f32)osc->curCount / (f32)osc->maxCount;
            tmpflt = sinf(tmpflt * TWO_PI) * -osc->data.vsin.depthcents;
            *updateVal = alCents2Ratio(tmpflt);
            break;
    }
    return deltaTime;
}

void func_800032B4_main(void *oscState) {
    MusOsc *osc = oscState;

    osc->next = D_800A97B8_main->freeOscs;
    D_800A97B8_main->freeOscs = osc;
}

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

s32 func_80003310_main(s32 trackId) {
    return func_8000332C_main(trackId, NULL);
}

/* Starts a music track, returning the index of the player it plays on. */
s32 func_8000332C_main(s32 trackId, MusPlayParam *param) {
    AudioManager *mus = func_800025B4_main();
    SeqPlayer *player;
    s32 playerIdx;
    s32 type;

    if (mus == NULL) {
        return 0;
    }
    if (trackId >= mus->trackCount) {
        return -1;
    }
    playerIdx = mus->tracks[trackId].player & 0xF;
    type = (mus->tracks[trackId].player & 0xF0) ? 15 : 1;
    player = &mus->players[playerIdx];
    if (param != NULL) {
        if (param->flags & 1) {
            playerIdx = param->player;
            if (playerIdx >= mus->playerCount) {
                return -1;
            }
            player = &mus->players[playerIdx];
        }
        if (param->flags & 2) {
            type = param->crossfade ? 15 : 1;
        }
        func_80002300_main(playerIdx, 0, 0);
        if (param->flags & 4) {
            player->evtVol = param->vol;
            func_80002300_main(playerIdx, 2, param->vol);
        }
        if (param->flags & 8) {
            func_80002300_main(playerIdx, 14, param->fadeIn);
        }
    }
    if (mus->tracks[trackId].size > player->seqDataSize) {
        return -1;
    }
    mus->busy.flag[0] = 1;
    func_80002300_main(playerIdx, type, trackId);
    player->state = 3;
    mus->busy.flag[0] = 0;
    return playerIdx;
}

s32 func_800034D8_main(s32 playerIdx) {
    AudioManager *mus = func_800025B4_main();

    if (mus == NULL) {
        return 0;
    }
    return mus->players[playerIdx].state;
}

s32 func_80003524_main(void) {
    AudioManager *mus = func_800025B4_main();

    if (mus == NULL) {
        return 0;
    }
    return mus->trackCount;
}

s32 func_8000354C_main(s32 playerIdx) {
    AudioManager *mus = func_800025B4_main();

    if (mus == NULL) {
        return 0;
    }
    return mus->players[playerIdx].curTrack;
}

s32 func_80003598_main(void) {
    AudioManager *mus = func_800025B4_main();

    if (mus == NULL) {
        return 0;
    }
    return mus->playerCount;
}

s32 func_800035C0_main(void) {
    AudioManager *mus = func_800025B4_main();

    if (mus == NULL) {
        return 0;
    }
    return mus->playingCount;
}

/* Stops the given player, or every player when the index is negative. */
void func_800035E8_main(s32 playerIdx) {
    AudioManager *mus = func_800025B4_main();
    SeqPlayer *player;
    s32 i;

    if (mus == NULL) {
        return;
    }
    if (playerIdx < 0) {
        func_80002300_main(0, 7, 0);
        mus->busy.flag[0] = 1;
        for (i = 0; i < mus->playerCount; i++) {
            player = &mus->players[i];
            if (player->state >= 2) {
                player->state = 1;
            }
        }
    } else {
        player = &mus->players[playerIdx];
        if (player->state < 2) {
            return;
        }
        mus->busy.flag[0] = 1;
        func_80002300_main(playerIdx, 6, 0);
        player->state = 1;
    }
    mus->busy.flag[0] = 0;
}

/* Sets the volume of the given player, or every player when the index is negative. */
void func_800036E8_main(s32 playerIdx, s32 vol) {
    AudioManager *mus = func_800025B4_main();
    SeqPlayer *player;
    s32 i;

    if (mus != NULL) {
        if (playerIdx < 0) {
            func_80002300_main(0, 3, vol);
            for (i = 0; i < mus->playerCount; i++) {
                player = &mus->players[i];
                if (player->state >= 2) {
                    player->evtVol = vol;
                }
            }
        } else {
            mus->players[playerIdx].evtVol = vol;
            func_80002300_main(playerIdx, 2, vol);
        }
    }
}

s32 func_800037C4_main(s32 playerIdx) {
    AudioManager *mus = func_800025B4_main();

    if (mus == NULL) {
        return 0;
    }
    return mus->players[playerIdx].evtVol;
}

void func_80003810_main(s32 vol) {
    if (func_800025B4_main() != NULL) {
        func_80002300_main(0, 4, vol);
    }
}

/* Sets the tempo of the given player, in beats per minute. */
void func_80003848_main(s32 playerIdx, s32 bpm) {
    AudioManager *mus = func_800025B4_main();
    f32 tempo;

    if (mus != NULL) {
        if (bpm <= 0) {
            bpm = 1;
        }
        tempo = 60.0f / bpm * 1000.0f * 1000.0f;
        n_alCSPSetTempo(mus->players[playerIdx].seqp, tempo);
    }
}

/* Returns the tempo of the given player, in beats per minute. */
s32 func_800038EC_main(s32 playerIdx) {
    AudioManager *mus = func_800025B4_main();
    SeqPlayer *player;
    s32 tempo;

    if (mus == NULL || (player = &mus->players[playerIdx])->state != 4) {
        return 0;
    }
    tempo = n_alCSPGetTempo(player->seqp);
    if (tempo != 0) {
        tempo = 60.0f / (tempo / 1000000.0f);
    }
    return tempo;
}

/* Fades out the given player, or every player when the index is negative. */
void func_800039A4_main(s32 playerIdx, s32 time) {
    AudioManager *mus = func_800025B4_main();

    if (mus != NULL) {
        if (playerIdx < 0) {
            func_80002300_main(0, 9, time);
        } else if (mus->players[playerIdx].state >= 3) {
            func_80002300_main(playerIdx, 8, time);
        }
    }
}

s32 func_80003A24_main(s32 playerIdx) {
    AudioManager *mus = func_800025B4_main();

    if (mus == NULL) {
        return 0;
    }
    return mus->players[playerIdx].fadeTime;
}

/* Pauses the given player, or every player when the index is negative. */
void func_80003A70_main(s32 playerIdx) {
    AudioManager *mus = func_800025B4_main();
    SeqPlayer *player;
    s32 i;

    if (mus == NULL) {
        return;
    }
    if (playerIdx < 0) {
        func_80002300_main(0, 11, 0);
        mus->busy.flag[0] = 1;
        for (i = 0; i < mus->playerCount; i++) {
            player = &mus->players[i];
            if (player->state >= 3) {
                player->state = 2;
            }
        }
    } else {
        player = &mus->players[playerIdx];
        if (player->state < 3) {
            return;
        }
        mus->busy.flag[0] = 1;
        func_80002300_main(playerIdx, 10, 0);
        player->state = 2;
    }
    mus->busy.flag[0] = 0;
}

/* Resumes the given player, or every player when the index is negative. */
void func_80003B70_main(s32 playerIdx, s32 fadeTime) {
    AudioManager *mus = func_800025B4_main();
    SeqPlayer *player;

    if (mus != NULL) {
        if (playerIdx < 0) {
            func_80002300_main(0, 13, fadeTime);
        } else {
            player = &mus->players[playerIdx];
            if (player->state == 2) {
                func_80002300_main(playerIdx, 12, fadeTime);
            }
        }
    }
}

/* Reads the settings of one MIDI channel of the given player. */
void func_80003BF4_main(s32 playerIdx, s32 chan, MusChlInfo *info) {
    AudioManager *mus = func_800025B4_main();
    SeqPlayer *player;

    if (mus != NULL && (player = &mus->players[playerIdx])->state == 4) {
        info->program = n_alCSPGetChlProgram(player->seqp, chan);
        info->vol = n_alCSPGetChlVol(player->seqp, chan);
        info->pan = n_alCSPGetChlPan(player->seqp, chan);
        info->fxMix = n_alCSPGetChlFXMix(player->seqp, chan);
    }
}

// Suspected mus/se boundary: ROM 0x48B8 (msm "se" code starts here). This is
// not a real file split: the mus text ends here at a non-16-aligned address with
// no nop padding, and func_80003CB8_main is clearly se code (D_800A97BC), so the
// mus and se code were most likely built as one file. The mus rodata (jump
// tables 0x800A6300-0x800A6790) does end 16-aligned, but that looks incidental.
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
