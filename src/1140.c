#include "common.h"

typedef struct {
    /* 0x00 */ s8 cmdType;   // cmdType
    /* 0x01 */ s8 voiceSlot; // voiceSlot
    /* 0x04 */ s32 cmdArg;   // cmdArg
} AudioCmd;                  // size: 0x8

typedef struct {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ char unk_1C[0x1C];
    /* 0x38 */ s32 unk38;           // write index (wraps at 0x80)
    /* 0x3C */ AudioCmd cmds[0x80]; // ring buffer of commands
} UnkAudio;

/* One entry of the active sound table the audio manager keeps. Only the
 * fields the manager's own functions touch are named so far. */
typedef struct GameSound_s {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s16 sndId; // ALSndId, -1 when unallocated
} GameSound;

typedef struct {
    /* 0x00 */ ALSeqPlayer *seqp;
    /* 0x04 */ u8 *seqData; // raw sequence data, DMA'd in per track
    /* 0x08 */ ALBank **bankTable;
    /* 0x0C */ ALSeq *seq;
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

extern AudioManager *D_800A97B8_main;
extern UnkAudio *D_800A97BC_main;
extern ALHeap D_800A9730_main;

s32 func_80007080_main(s32, s32);
s32 func_80001134_main(s32 arg0, s32 arg1);
void *func_80077290_main(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size);

INCLUDE_ASM("asm/nonmatchings/1140", func_80000540_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80000650_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_800007FC_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_8000086C_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80000DF0_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80000E9C_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80000EA8_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80000EDC_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80000EFC_main);

s32 func_80000F08_main(s32 arg0) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/1140", func_80000F10_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80000F30_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80000FC4_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80000FE4_main);

/* Allocates a single element of the given size from the audio heap, reporting a
 * fatal error if the allocation fails. This is the non-debug alHeapAlloc(). */
void *func_800010B8_main(s32 size) {
    void *ptr = func_80077290_main(NULL, 0, &D_800A9730_main, 1, size);

    if (ptr == NULL) {
        func_80001134_main(0, 1);
    }
    return ptr;
}

INCLUDE_ASM("asm/nonmatchings/1140", func_8000110C_main);

s32 func_80001134_main(s32 arg0, s32 arg1) {
    return 0;
}

s16 func_8000113C_main(s32 arg0) {
    if (arg0 <= 0) {
        return 0;
    }
    return (arg0 << 8) | 0xFF;
}

INCLUDE_ASM("asm/nonmatchings/1140", func_80001160_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_8000124C_main);

s32 func_800012C4_main(SeqPlayer *seqPlayer) {
    return D_800A97B8_main->configVol * seqPlayer->evtVol * seqPlayer->trackVol * seqPlayer->fadeVol / 127 / 127 / 127 * D_800A97B8_main->masterVol / 127;
}

INCLUDE_ASM("asm/nonmatchings/1140", func_80001348_main);

INCLUDE_ASM("asm/nonmatchings/1140", func_80001408_main);

void func_80001ADC_main(SeqPlayer *seqPlayer) {
    s32 state = alCSPGetState((ALCSPlayer *)seqPlayer->seqp);

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
