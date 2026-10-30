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

/* Added to each pitch modulation term, so any active modulation registers as a
 * change even when it is zero. */
#define SE_CENTS_EPSILON 1e-5f

/* Big-endian reads from sound effect scripts. */
#define SE_READ16(p) (((p)[0] << 8) | (p)[1])
#define SE_READ32(p) (((p)[0] << 24) | ((p)[1] << 16) | ((p)[2] << 8) | (p)[3])

#define MAGIC_FXD0 0x46584430 // 'FXD0'
#define MAGIC_MBF0 0x4D424630 // 'MBF0'
#define MAGIC_SBF0 0x53424630 // 'SBF0'

typedef struct {
    /* 0x00 */ s8 cmdType;   // cmdType
    /* 0x01 */ s8 voiceSlot; // voiceSlot
    /* 0x04 */ s32 cmdArg;   // cmdArg
} AudioCmd;                  // size: 0x8

/* One playing sound effect voice. A sound effect made of several layers uses
 * one voice per layer; the first voice links to the others. */
typedef struct {
    /* 0x00 */ s32 slot;  // index of the linked voice
    /* 0x04 */ u32 order; // play order of the linked voice, to detect reuse
} SeLink;

/* Random variation of a voice's volume or pan. */
typedef struct {
    /* 0x00 */ s8 max;
    /* 0x01 */ s8 min;
    /* 0x02 */ u8 interval; // frames between new random values
    /* 0x03 */ u8 timer;
} SeRandom; // size: 0x4

/* An external modulation source applied to a voice. */
typedef struct {
    /* 0x00 */ s16 value;
    /* 0x02 */ s16 target; // 1 volume, 2 pan, 3 pitch
} SeMod; // size: 0x4

typedef struct GameSound_s {
    /* 0x00 */ s32 flags; // 0x4000 vol, 0x8000 pan, 0x10000 fx mix, 0x20000 pitch changed
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 sndState; // latest n_alSndpGetState()
    /* 0x0C */ s16 sndId;    // ALSndId, -1 when unallocated
    /* 0x0E */ s16 seId;
    /* 0x10 */ u32 order;      // play order, used to steal the oldest voice
    /* 0x14 */ f32 pitchRatio; // sample rate / output rate
    /* 0x18 */ s16 pitch;
    /* 0x1A */ s8 vol;
    /* 0x1B */ s8 pan;
    /* 0x1C */ s8 fxMix;
    /* 0x1D */ u8 priority;
    /* 0x1E */ s8 layer;
    /* 0x1F */ s8 linkCount;
    /* 0x20 */ SeLink links[4]; // first layer: the other layers, others: the first layer
    /* 0x40 */ u8 *script;
    /* 0x44 */ char unk_44[4];
    /* 0x48 */ s16 soundIdx; // index into alSounds, 0x8000 when not yet set up
    /* 0x4A */ s16 wait;     // frames until the next script command
    /* 0x4C */ s16 key;      // in cents
    /* 0x4E */ s16 detune;   // pitch modulation, in cents
    /* 0x50 */ s8 scriptVol;
    /* 0x51 */ s8 volMod;
    /* 0x52 */ s8 scriptPan;
    /* 0x53 */ s8 panMod;
    /* 0x54 */ s8 scriptFxMix;
    /* 0x55 */ char unk_55[3];
    /* 0x58 */ u16 loopAddr[3];
    /* 0x5E */ u8 loopCount[3];
    /* 0x61 */ s8 loopDepth;
    /* 0x62 */ char unk_62[2];
    /* 0x64 */ u8 *callStack[2];
    /* 0x6C */ s8 callDepth;
    /* 0x6D */ char unk_6D[3];
    /* 0x70 */ f32 lfoRand;
    /* 0x74 */ s8 lfoPhase;
    /* 0x75 */ u8 lfoType;
    /* 0x76 */ u8 lfoRate;
    /* 0x77 */ s8 unk_77;
    /* 0x78 */ s16 lfoDepth;
    /* 0x7A */ s16 lfoCounter;
    /* 0x7C */ s16 lfoPeriod;
    /* 0x7E */ s16 lfoDelay;     // frames left before the LFO starts
    /* 0x80 */ s16 lfoDelaySave;
    /* 0x82 */ s8 lfoActive;
    /* 0x83 */ char unk_83[1];
    /* 0x84 */ s8 sweepFlags;
    /* 0x85 */ s8 sweepActive;
    /* 0x86 */ s16 sweepAmount;
    /* 0x88 */ s16 sweepCounter;
    /* 0x8A */ s16 sweepTime;
    /* 0x8C */ u8 *envScript; // pitch envelope
    /* 0x90 */ u8 *envPtr;
    /* 0x94 */ f32 envScale;
    /* 0x98 */ s16 envDelayInit;
    /* 0x9A */ s16 envDelay;
    /* 0x9C */ s16 envStep;
    /* 0x9E */ s16 envAccum;
    /* 0xA0 */ s8 envCount;
    /* 0xA1 */ char unk_A1[3];
    /* 0xA4 */ f32 unk_A4;
    /* 0xA8 */ f32 unk_A8;
    /* 0xAC */ f32 unk_AC;
    /* 0xB0 */ char unk_B0[2];
    /* 0xB2 */ s8 unk_B2;
    /* 0xB3 */ s8 unk_B3;
    /* 0xB4 */ f32 unk_B4;
    /* 0xB8 */ s32 randFlags; // 1 volume, 2 pan, 4 pitch
    /* 0xBC */ SeRandom randVol;
    /* 0xC0 */ SeRandom randPan;
    /* 0xC4 */ s16 randPitchMax;
    /* 0xC6 */ s16 randPitchMin;
    /* 0xC8 */ u8 randPitchInterval;
    /* 0xC9 */ u8 randPitchTimer;
    /* 0xCA */ s16 randPitch;
    /* 0xCC */ s32 modMask;
    /* 0xD0 */ SeMod mods[3];
    /* 0xDC */ ALSound sound; // keyMap holds the sample rate
    /* 0xEC */ ALEnvelope env;
} GameSound; // size: 0xFC

/* One layer of a sound effect. */
typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 voiceShift; // low nibble: shift of the voice mask per variant
    /* 0x02 */ u16 voiceMask; // voices this layer may play on
    /* 0x04 */ u8 *script;
} SeLayer; // size: 0x8

/* One sound effect, as read from the SBF0 bank. */
typedef struct {
    /* 0x00 */ s8 layerCount;
    /* 0x01 */ u8 priority;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ char unk_04[4];
    /* 0x08 */ SeLayer layers[1];
} SeEntry;

/* Table of contents of an SBF0 bank, following its header. */
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 soundCount;
    /* 0x08 */ u8 *ctlAddr; // relative to the bank until loaded
    /* 0x0C */ s32 ctlSize;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 *tblAddr; // relative to the bank until loaded
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 seCount;
    /* 0x20 */ s32 seOffset;
    /* 0x24 */ s32 seSize;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
} SeBankInfo; // size: 0x34

typedef struct {
    /* 0x00 */ s8 cmdType;
    /* 0x01 */ s8 voiceSlot;
    /* 0x04 */ union {
        s32 i;
        f32 f;
    } arg;
} SeCmd; // size: 0x8

typedef struct {
    /* 0x000 */ N_ALSndPlayer *sndp;
    /* 0x004 */ ALSound *alSounds;
    /* 0x008 */ GameSound *sounds;
    /* 0x00C */ SeEntry **entries;
    /* 0x010 */ u8 **envScripts; // pitch envelope scripts
    /* 0x014 */ s32 soundCount;
    /* 0x018 */ s32 unk_18; // number of voices in use
    /* 0x01C */ u32 order;  // play order counter
    /* 0x020 */ s32 fadeStep;
    /* 0x024 */ s32 fadeTime; // frames left, negative while fading in
    /* 0x028 */ s16 seCount;
    /* 0x02A */ s16 unk_2A;
    /* 0x02C */ s8 masterVol;
    /* 0x02D */ s8 pan;
    /* 0x02E */ s8 unk_2E;
    /* 0x02F */ s8 vol;
    /* 0x030 */ s8 configVol;
    /* 0x031 */ s8 fadeVol;
    /* 0x032 */ s8 pauseState;
    /* 0x034 */ union {
        s32 all;
        s16 flag[2]; // [0] set by the API functions, [1] by the periodic proc
    } busy;
    /* 0x038 */ s32 cmdCount;
    /* 0x03C */ SeCmd cmds[0x80];
    /* 0x43C */ f32 minDist;
    /* 0x440 */ f32 maxDist;
    /* 0x444 */ f32 unk_444;
    /* 0x448 */ f32 unk_448;
    /* 0x44C */ s16 angle;
    /* 0x44E */ s16 unk_44E;
    /* 0x450 */ f32 unk_450;
    /* 0x454 */ f32 unk_454;
} SeManager; // size: 0x458

/* Voices considered by func_800072A4_main when picking a voice to play on. */
#define SE_VOICES_FREE 0  // not playing
#define SE_VOICES_SAME 1  // playing the same sound effect
#define SE_VOICES_OTHER 2 // playing another sound effect

typedef struct {
    /* 0x00 */ s32 count;
    /* 0x04 */ s8 slots[20];
} SeVoiceList; // size: 0x18

/* Optional parameters for starting a sound effect. */
typedef struct {
    /* 0x00 */ s32 flags; // which of the fields below are valid
    /* 0x04 */ s32 slot;
    /* 0x08 */ s32 variant;
    /* 0x0C */ s32 vol;
    /* 0x10 */ s32 pitch;
    /* 0x14 */ s32 pan;
    /* 0x18 */ s32 fxMix;
    /* 0x1C */ s32 angle;
    /* 0x20 */ f32 dist;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
} SePlayParam; // size: 0x2C

/* Positional parameters of a sound effect voice. */
typedef struct {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 angle;
    /* 0x08 */ f32 dist;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
} SePosParam;

/* Settings of the sound effect player, see func_80007A10_main. */
typedef struct {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 masterVol;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 pan;
    /* 0x10 */ s32 unk_10;
} SeParam;

/* Positional settings of the sound effect player, see func_8000801C_main. */
typedef struct {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 angle;
    /* 0x08 */ f32 minDist;
    /* 0x0C */ f32 maxDist;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s32 unk_20;
} SePosConfig;

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
    /* 0x00 */ s32 magic; // MAGIC_MBF0 or MAGIC_SBF0
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

/* Header of an effect table. The id is stored in the high halfword of the first
 * word and the count in its low byte; the count is widened in place after
 * loading. */
typedef union {
    s32 count;
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
extern SeManager *D_800A97BC_main;
extern ALHeap D_800A9730_main;
extern OSMesg D_800A9650_main[50];
extern OSMesgQueue D_800A9718_main;
extern SndSys D_800A9740_main;
extern u8 D_800CB8AC_main;

s32 func_80007080_main(s32 seId, SePlayParam *param);
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
SeManager *func_8000704C_main(void);
void func_80007058_main(void);
s32 amCreateAudioMgr(str800D5298 *cfg, ALHeap *heap);
void func_80003FB4_main(void);
void func_800048D0_main(GameSound *sound);
void func_80004928_main(GameSound *sound);
void func_8000499C_main(GameSound *sound);
void func_800049E8_main(GameSound *sound);
void func_80004D4C_main(GameSound *sound);
s32 func_80005804_main(u8 **cursor);
f32 func_80005850_main(GameSound *sound);
void func_80005BAC_main(GameSound *sound, f32 arg1);
void func_80005FE4_main(GameSound *sound);
void func_80006148_main(GameSound *sound);
void func_800062A8_main(GameSound *sound);
void func_8000658C_main(GameSound *sound, s32 arg1);
void func_80006830_main(void);
void func_800068B8_main(void);
void func_80006CD4_main(s32 voiceSlot, s32 cmdType, s32 cmdArg);
void func_80006D80_main(s32 voiceSlot, s32 cmdType, f32 cmdArg);
s32 func_800072A4_main(s32 seId, s32 layer, s32 slot, s32 variant);
void func_800076B8_main(s32 seId, s32 slot, u8 priority, SePlayParam *param);
void func_8000810C_main(s32 slot, SePosParam *param);
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
        if (buf->count == MAGIC_FXD0) {
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
    D_800A9740_main.fxId = buf->count >> 16;
    buf->count = buf->bytes[3];
    size = (buf->count * 32) | 8;
    if ((sys->cfg.unk2C = func_800010B8_main(size)) == NULL) {
        return 2;
    }
    func_80000FE4_main(sys->cfg.unk2C, romAddr, size, 0);
    fx = sys->cfg.unk2C;
    fx->count = fx->bytes[3];
    return 0;
}

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
        if (buf->magic == MAGIC_SBF0) {
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
        if (buf->magic == MAGIC_MBF0) {
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
    SeManager *se;

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
    SeManager *se;
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
void func_80000FE4_main(void *dst, void *romAddr, s32 size, s32 chunkSize) {
    OSIoMesg mesg;
    s32 len;
    s32 chunk = chunkSize;
    u32 rom = (u32)romAddr;
    u8 *ram = dst;
    s32 remaining = size;

    if (chunk == 0) {
        chunk = remaining;
    }
    chunk += chunk & 1;
    while (remaining != 0) {
        len = remaining;
        if (len > chunk) {
            len = chunk;
        }
        mesg.hdr.pri = OS_MESG_PRI_NORMAL;
        mesg.hdr.retQueue = &D_800A9718_main;
        mesg.dramAddr = ram;
        mesg.devAddr = rom;
        mesg.size = len;
        osInvalDCache(ram, len);
        osEPiStartDma(D_800A9740_main.cfg.unk68, &mesg, OS_READ);
        osRecvMesg(&D_800A9718_main, NULL, OS_MESG_BLOCK);
        rom += len;
        remaining -= len;
        ram += len;
    }
}

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
/* Loads the sound effect bank file and resolves the offsets inside it. */
s32 func_80003CB8_main(u8 *bankAddr, SeBankInfo *info) {
    ALSound *sound;
    ALWaveTable *wave;
    s32 i;

    if ((D_800A97BC_main->alSounds = func_800010B8_main(info->ctlSize)) == NULL) {
        return 1;
    }
    info->ctlAddr = bankAddr + (u32)info->ctlAddr;
    func_80000FE4_main(D_800A97BC_main->alSounds, info->ctlAddr, info->ctlSize, 0);
    info->tblAddr = bankAddr + (u32)info->tblAddr;
    for (i = 0; i < info->soundCount; i++) {
        sound = &D_800A97BC_main->alSounds[i];
        if (sound->flags == 0) {
            sound->flags = 1;
            sound->envelope = (ALEnvelope *)((u8 *)sound->envelope + (u32)D_800A97BC_main->alSounds);
            sound->wavetable = wave = (ALWaveTable *)((u8 *)sound->wavetable + (u32)D_800A97BC_main->alSounds);
            if (wave->flags == 0) {
                wave->flags = 1;
                wave->base += (u32)info->tblAddr;
                wave->waveInfo.adpcmWave.book =
                    (ALADPCMBook *)((u8 *)wave->waveInfo.adpcmWave.book + (u32)D_800A97BC_main->alSounds);
                if (wave->waveInfo.adpcmWave.loop != NULL) {
                    wave->waveInfo.adpcmWave.loop =
                        (ALADPCMloop *)((u8 *)wave->waveInfo.adpcmWave.loop + (u32)D_800A97BC_main->alSounds);
                }
            }
        }
    }
    return 0;
}

/* Loads the sound effect table and resolves the offsets inside it. */
s32 func_80003DF4_main(u8 *bankAddr, SeBankInfo *info) {
    u8 *romAddr;
    SeEntry *entry;
    s32 i;
    s32 j;

    if ((D_800A97BC_main->entries = func_800010B8_main(info->seSize)) == NULL) {
        return 1;
    }
    romAddr = bankAddr + info->seOffset;
    func_80000FE4_main(D_800A97BC_main->entries, romAddr, info->seSize, 0);
    for (i = 0; i < info->seCount; i++) {
        if (D_800A97BC_main->entries[i] != NULL) {
            entry = D_800A97BC_main->entries[i] = (SeEntry *)((u8 *)D_800A97BC_main->entries[i] + (u32)D_800A97BC_main->entries);
            for (j = 0; j < entry->layerCount; j++) {
                entry->layers[j].script += (u32)D_800A97BC_main->entries;
            }
        }
    }
    return 0;
}

s32 func_80003EE4_main(u8 *bankAddr, SeBankInfo *info) {
    u8 *romAddr;
    s32 i;

    if (info->unk_28 == 0) {
        D_800A97BC_main->envScripts = NULL;
        return 0;
    }
    if ((D_800A97BC_main->envScripts = func_800010B8_main(info->unk_30)) == NULL) {
        return 1;
    }
    romAddr = bankAddr + info->unk_2C;
    func_80000FE4_main(D_800A97BC_main->envScripts, romAddr, info->unk_30, 0);
    for (i = 0; i < info->unk_28; i++) {
        if (D_800A97BC_main->envScripts[i] != NULL) {
            D_800A97BC_main->envScripts[i] += (u32)D_800A97BC_main->envScripts;
        }
    }
    return 0;
}

/* Processes the commands queued by the API functions. Changes to a voice that
 * has not started yet are flagged so they are not overwritten when it starts;
 * changes to a playing voice also apply to the voices of its other layers. */
void func_80003FB4_main(void) {
    SeCmd *cmd;
    GameSound *sound;
    GameSound *link;
    s32 i;
    s32 j;

    for (i = 0; i < D_800A97BC_main->cmdCount; i++) {
        cmd = &D_800A97BC_main->cmds[i];
        sound = &D_800A97BC_main->sounds[cmd->voiceSlot];
        switch (cmd->cmdType) {
            case 0:
                sound->flags = (sound->flags & ~1) | 2;
                sound->state = 3;
                break;
            case 1:
                sound->flags |= 1;
                sound->layer = cmd->arg.i & 0xF;
                sound->linkCount = cmd->arg.i >> 4;
                break;
            case 2:
                sound->vol = cmd->arg.i;
                if (sound->flags & 3) {
                    sound->flags |= 0x10;
                } else {
                    sound->flags |= 0x4000;
                    if (sound->linkCount != 0) {
                        for (j = 0; j < sound->linkCount; j++) {
                            link = &D_800A97BC_main->sounds[sound->links[j].slot];
                            if (link->order == sound->links[j].order) {
                                link->vol = cmd->arg.i;
                                link->flags |= 0x4000;
                            }
                        }
                    }
                }
                break;
            case 4:
                for (j = 0; j < D_800A97BC_main->soundCount; j++) {
                    link = &D_800A97BC_main->sounds[j];
                    link->vol = cmd->arg.i;
                    if (link->flags & 3) {
                        link->flags |= 0x10;
                    } else {
                        link->flags |= 0x4000;
                    }
                }
                break;
            case 3:
                for (j = 0; j < D_800A97BC_main->soundCount; j++) {
                    link = &D_800A97BC_main->sounds[j];
                    if (link->state == 4) {
                        link->flags |= 0x4000;
                    }
                }
                D_800A97BC_main->vol = cmd->arg.i;
                D_800A97BC_main->fadeVol = 0x7F;
                D_800A97BC_main->fadeTime = 0;
                break;
            case 5:
                sound->pitch = cmd->arg.i;
                if (sound->flags & 3) {
                    sound->flags |= 0x40;
                } else {
                    sound->flags |= 0x20000;
                    if (sound->linkCount != 0) {
                        for (j = 0; j < sound->linkCount; j++) {
                            link = &D_800A97BC_main->sounds[sound->links[j].slot];
                            if (link->order == sound->links[j].order) {
                                link->pitch = cmd->arg.i;
                                link->flags |= 0x20000;
                            }
                        }
                    }
                }
                break;
            case 6:
                for (j = 0; j < D_800A97BC_main->soundCount; j++) {
                    link = &D_800A97BC_main->sounds[j];
                    link->pitch = cmd->arg.i;
                    if (link->flags & 3) {
                        link->flags |= 0x40;
                    } else {
                        link->flags |= 0x20000;
                    }
                }
                break;
            case 7:
                sound->pan = cmd->arg.i;
                if (sound->flags & 3) {
                    sound->flags |= 0x20;
                } else {
                    sound->flags |= 0x8000;
                    if (sound->linkCount != 0) {
                        for (j = 0; j < sound->linkCount; j++) {
                            link = &D_800A97BC_main->sounds[sound->links[j].slot];
                            if (link->order == sound->links[j].order) {
                                link->pan = cmd->arg.i;
                                link->flags |= 0x8000;
                            }
                        }
                    }
                }
                break;
            case 8:
                for (j = 0; j < D_800A97BC_main->soundCount; j++) {
                    link = &D_800A97BC_main->sounds[j];
                    link->pan = cmd->arg.i;
                    if (link->flags & 3) {
                        link->flags |= 0x20;
                    } else {
                        link->flags |= 0x8000;
                    }
                }
                break;
            case 9:
                sound->fxMix = cmd->arg.i;
                if (sound->flags & 3) {
                    sound->flags |= 0x80;
                } else {
                    sound->flags |= 0x10000;
                    if (sound->linkCount != 0) {
                        for (j = 0; j < sound->linkCount; j++) {
                            link = &D_800A97BC_main->sounds[sound->links[j].slot];
                            if (link->order == sound->links[j].order) {
                                link->fxMix = cmd->arg.i;
                                link->flags |= 0x10000;
                            }
                        }
                    }
                }
                break;
            case 10:
                for (j = 0; j < D_800A97BC_main->soundCount; j++) {
                    link = &D_800A97BC_main->sounds[j];
                    link->fxMix = cmd->arg.i;
                    if (link->flags & 3) {
                        link->flags |= 0x80;
                    } else {
                        link->flags |= 0x10000;
                    }
                }
                break;
            case 11:
                func_800048D0_main(sound);
                if (sound->linkCount != 0) {
                    for (j = 0; j < sound->linkCount; j++) {
                        link = &D_800A97BC_main->sounds[sound->links[j].slot];
                        if (link->order == sound->links[j].order) {
                            func_800048D0_main(link);
                        }
                    }
                }
                break;
            case 12:
                for (j = 0; j < D_800A97BC_main->soundCount; j++) {
                    func_800048D0_main(&D_800A97BC_main->sounds[j]);
                }
                break;
            case 13:
                D_800A97BC_main->fadeTime = cmd->arg.i > 0 ? cmd->arg.i : 1;
                D_800A97BC_main->fadeStep = 0x7F000000 / D_800A97BC_main->fadeTime;
                D_800A97BC_main->fadeVol = 0x7F;
                break;
            case 14:
                for (j = 0; j < D_800A97BC_main->soundCount; j++) {
                    link = &D_800A97BC_main->sounds[j];
                    if (link->state >= 2) {
                        link->state = 2;
                    }
                    if (link->flags & 8) {
                        func_800048D0_main(link);
                    }
                }
                D_800A97BC_main->pauseState = 0x7E;
                break;
            case 15:
                D_800A97BC_main->pauseState = 0x7F;
                for (j = 0; j < D_800A97BC_main->soundCount; j++) {
                    link = &D_800A97BC_main->sounds[j];
                    if (link->state == 2) {
                        link->state = 4;
                        link->flags |= 0x4000;
                    }
                }
                if (cmd->arg.i != 0 && D_800A97BC_main->fadeTime <= 0) {
                    D_800A97BC_main->fadeTime = -cmd->arg.i;
                    D_800A97BC_main->fadeStep = 0x7F000000 / cmd->arg.i;
                    D_800A97BC_main->fadeVol = 0;
                }
                break;
            case 16:
                if (sound->flags & 3) {
                    sound->flags |= 0x100;
                } else {
                    sound->flags |= 0x4000;
                }
                sound->unk_B2 = cmd->arg.i;
                break;
            case 17:
                if (sound->flags & 3) {
                    sound->flags |= 0x200;
                } else {
                    sound->flags |= 0x8000;
                }
                sound->unk_B3 = cmd->arg.i;
                break;
            case 18:
                if (sound->flags & 3) {
                    sound->flags |= 0x400;
                } else {
                    sound->flags |= 0x20000;
                }
                sound->unk_B4 = cmd->arg.f;
                break;
        }
    }
    D_800A97BC_main->cmdCount = 0;
}

void func_800048D0_main(GameSound *sound) {
    sound->flags = 0;
    sound->state = 0;
    if (sound->sndId >= 0) {
        n_alSndpSetSound(sound->sndId);
        n_alSndpStop();
        sound->state = 1;
        sound->flags |= 0x800;
    }
}

void func_80004928_main(GameSound *sound) {
    if (sound->sndId >= 0) {
        n_alSndpSetSound(sound->sndId);
        if ((sound->sndState = n_alSndpGetState()) == AL_STOPPED && (sound->flags & 0x800)) {
            n_alSndpDeallocate(sound->sndId);
            sound->sndId = -1;
            sound->flags &= ~0x800;
        }
    }
}

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

/* Starts the scripts of a sound effect once its previous sound has stopped.
 * The first layer's voice starts the voices of the other layers too. */
void func_800049E8_main(GameSound *sound) {
    SeEntry *entry;
    SeLink *links;
    GameSound *link;
    s32 linkCount;
    s32 flags;
    s32 i;

    if (!(sound->flags & 1)) {
        return;
    }
    entry = D_800A97BC_main->entries[sound->seId];
    if (D_800A97BC_main->pauseState < 0x7F && !(entry->unk_02 & 1)) {
        return;
    }
    sound->state = 3;
    if (sound->sndState == AL_PLAYING) {
        sound->env.releaseTime = 184000000 / func_80000E9C_main()->cfg.unk1C;
        n_alSndpStop();
        sound->flags |= 0x800;
        return;
    }
    if (sound->sndState == AL_STOPPING) {
        return;
    }
    if (sound->sndId >= 0) {
        n_alSndpDeallocate(sound->sndId);
        sound->sndId = -1;
    }
    if (sound->layer > 0) {
        if (D_800A97BC_main->sounds[sound->links[0].slot].order != sound->links[0].order) {
            sound->state = 0;
            sound->flags = 0;
        }
        return;
    }
    linkCount = sound->linkCount;
    links = sound->links;
    if (linkCount != 0) {
        for (i = 0; i < linkCount; i++) {
            link = &D_800A97BC_main->sounds[links[i].slot];
            if (link->order == links[i].order && link->sndId >= 0) {
                return;
            }
        }
    }
    i = 0;
    flags = 0;
    if (entry->unk_02 & 1) {
        flags |= 4;
    }
    if (entry->unk_02 & 2) {
        flags |= 8;
    }
    do {
        sound->script = entry->layers[sound->layer].script;
        sound->wait = 0;
        sound->scriptVol = 0x7F;
        sound->scriptPan = 0x40;
        sound->scriptFxMix = 0;
        sound->lfoType = 0;
        sound->lfoDepth = 0;
        sound->envScript = NULL;
        sound->envScale = 1.0f;
        sound->sweepFlags = 0;
        sound->sweepActive = 0;
        sound->loopDepth = 0;
        sound->loopCount[0] = 0;
        sound->callDepth = 0;
        sound->randFlags = 0;
        sound->modMask = 0;
        if (!(sound->flags & 0x10)) {
            sound->vol = D_800A97BC_main->masterVol;
        }
        if (!(sound->flags & 0x20)) {
            sound->pan = D_800A97BC_main->pan;
        }
        if (!(sound->flags & 0x40)) {
            sound->pitch = D_800A97BC_main->unk_2A;
        }
        if (!(sound->flags & 0x80)) {
            sound->fxMix = D_800A97BC_main->unk_2E;
        }
        if (!(sound->flags & 0x100)) {
            sound->unk_B2 = 0x7F;
        }
        if (!(sound->flags & 0x200)) {
            sound->unk_B3 = 0x40;
        }
        if (!(sound->flags & 0x400)) {
            sound->unk_B4 = 1.0f;
        }
        sound->unk_AC = -1.0f;
        sound->flags = flags;
        sound->state = 4;
        for (; i < linkCount; i++) {
            sound = &D_800A97BC_main->sounds[links[i].slot];
            if (sound->order == links[i].order) {
                break;
            }
        }
        i++;
    } while (i <= linkCount);
}

#ifdef NON_MATCHING
/* Register allocation differs: the mod loop index and its sign-extended copy
 * are swapped, and the volume/pan delta lands in v1 instead of a0. Reusing the
 * loop index for the delta puts both in the same register, as in the target,
 * but the index/copy swap remains. */
/* Runs the script of a voice until it has to wait. Each command byte is
 * followed by a variable length wait time unless bit 7 is set. */
void func_80004D4C_main(GameSound *sound) {
    u8 *cursor;
    u8 *op;
    u8 *count;
    s8 delta;
    s8 idx;
    u16 bit;
    s8 i;

    if (sound->flags & 0x1000) {
        return;
    }
    if (sound->wait != 0) {
        sound->wait--;
        return;
    }
    if ((cursor = sound->script) == NULL) {
        sound->flags |= 0x40000;
        return;
    }
    while (sound->wait == 0) {
        op = cursor++;
        if (!(*op & 0x80)) {
            sound->wait = func_80005804_main(&cursor);
        }
        switch (*op & 0x7F) {
            case 2:
                count = &sound->loopCount[sound->loopDepth];
                if (*count != 0) {
                    if (((u32)cursor & 0xFFFF) != sound->loopAddr[sound->loopDepth]) {
                        if (sound->loopDepth == 2) {
                            cursor += 3;
                            break;
                        }
                        sound->loopDepth++;
                        count = &sound->loopCount[sound->loopDepth];
                        *count = 0;
                    } else if (*count == 1) {
                        (*count)--;
                        if (sound->loopDepth != 0) {
                            sound->loopDepth--;
                        }
                        cursor += 3;
                        break;
                    } else {
                        (*count)--;
                    }
                }
                if (*count == 0) {
                    if (*cursor == 0) {
                        cursor += 3;
                        break;
                    }
                    *count = *cursor;
                    sound->loopAddr[sound->loopDepth] = (u16)(u32)cursor;
                }
                cursor++;
                cursor = op + (s16)SE_READ16(cursor);
                break;
            case 3:
                cursor = op + SE_READ32(cursor);
                break;
            case 4:
                {
                    s32 offset = SE_READ32(cursor);

                    cursor += 4;
                    if (sound->callDepth < ARRAY_COUNT(sound->callStack)) {
                        sound->callStack[sound->callDepth++] = cursor;
                        cursor = op + offset;
                    }
                }
                break;
            case 16:
                if (sound->soundIdx < 0 && ((sound->flags & 0x1000) || sound->sndState != AL_STOPPED)) {
                    cursor = op;
                    sound->wait = 1;
                    break;
                }
                sound->key = SE_READ16(cursor);
                cursor += 2;
                sound->flags |= 0x1000;
                if (sound->sweepFlags & 8) {
                    sound->sweepFlags &= ~8;
                } else {
                    sound->sweepActive = 0;
                }
                if (sound->modMask != 0) {
                    for (i = 0; i < ARRAY_COUNT(sound->mods); i++) {
                        bit = 1 << i;
                        if (bit & sound->modMask) {
                            if (sound->mods[i].target & 8) {
                                sound->mods[i].target &= ~8;
                            } else {
                                sound->modMask &= ~bit;
                            }
                        }
                    }
                }
                break;
            case 17:
                sound->flags |= 0x2000;
                break;
            case 18:
                sound->soundIdx = SE_READ16(cursor);
                cursor += 2;
                sound->flags = (sound->flags & ~0x5F00000) | 0x2000000;
                break;
            case 19:
                sound->soundIdx = SE_READ16(cursor) | 0x8000;
                cursor += 2;
                sound->flags = (sound->flags & ~0x5F00000) | 0x2000000;
                break;
            case 20:
                sound->scriptVol = *cursor++ & 0x7F;
                sound->flags |= 0x4000;
                break;
            case 21:
                delta = *cursor++;
                sound->scriptVol += delta;
                if (sound->scriptVol < 0) {
                    if (delta < 0) {
                        sound->scriptVol = 0;
                    } else {
                        sound->scriptVol = 0x7F;
                    }
                }
                sound->flags |= 0x4000;
                break;
            case 22:
                sound->scriptPan = *cursor++ & 0x7F;
                sound->flags |= 0x8000;
                break;
            case 23:
                delta = *cursor++;
                sound->scriptPan += delta;
                if (sound->scriptPan < 0) {
                    if (delta < 0) {
                        sound->scriptPan = 0;
                    } else {
                        sound->scriptPan = 0x7F;
                    }
                }
                sound->flags |= 0x8000;
                break;
            case 25:
                sound->key = SE_READ16(cursor);
                cursor += 2;
                sound->flags |= 0x20000;
                break;
            case 26:
                sound->key += SE_READ16(cursor);
                cursor += 2;
                sound->flags |= 0x20000;
                break;
            case 27:
                sound->scriptFxMix = *cursor++ & 0x7F;
                sound->flags |= 0x10000;
                break;
            case 32:
                sound->lfoType = cursor[0];
                sound->lfoRate = cursor[1];
                sound->lfoDelay = SE_READ16(cursor + 2);
                sound->lfoDepth = 0;
                sound->unk_77 = 0;
                sound->lfoActive = 0;
                cursor += 4;
                break;
            case 33:
                sound->lfoDepth = SE_READ16(cursor);
                cursor += 2;
                break;
            case 34:
                sound->sweepActive = cursor[0];
                sound->sweepAmount = SE_READ16(cursor + 1);
                sound->sweepTime = SE_READ16(cursor + 3);
                sound->sweepCounter = 0;
                sound->sweepFlags |= 8;
                cursor += 5;
                break;
            case 35:
                if (D_800A97BC_main->envScripts != NULL) {
                    sound->envScript = D_800A97BC_main->envScripts[cursor[0]];
                    sound->envDelayInit = SE_READ16(cursor + 1);
                    sound->envDelay = -1;
                }
                cursor += 3;
                break;
            case 36:
                sound->envScale = SE_READ16(cursor) / 100.0f;
                cursor += 2;
                break;
            case 37:
                sound->envScript = NULL;
                break;
            case 48:
                sound->env.attackVolume = *cursor++ & 0x7F;
                if (sound->flags & 0x2000000) {
                    sound->flags |= 0x100000;
                }
                break;
            case 49:
                sound->env.decayVolume = *cursor++ & 0x7F;
                if (sound->flags & 0x2000000) {
                    sound->flags |= 0x200000;
                }
                break;
            case 50:
                sound->env.attackTime = SE_READ32(cursor);
                cursor += 4;
                if (sound->flags & 0x2000000) {
                    sound->flags |= 0x400000;
                }
                break;
            case 51:
                sound->env.decayTime = SE_READ32(cursor);
                cursor += 4;
                if (sound->flags & 0x2000000) {
                    sound->flags |= 0x800000;
                }
                break;
            case 52:
                if (sound->soundIdx < 0) {
                    sound->env.releaseTime = SE_READ32(cursor);
                    if (sound->flags & 0x2000000) {
                        sound->flags |= 0x1000000;
                    }
                }
                cursor += 4;
                break;
            case 53:
                bit = SE_READ16(cursor);
                cursor += 2;
                sound->pitchRatio = (f32)bit / func_80000E9C_main()->cfg.unk1C;
                if (sound->flags & 0x2000000) {
                    sound->flags |= 0x4000000;
                }
                break;
            case 64:
                sound->randVol.min = cursor[0];
                sound->randVol.max = cursor[1];
                sound->randVol.interval = cursor[2];
                sound->randFlags |= 1;
                cursor += 3;
                break;
            case 65:
                sound->randFlags &= ~1;
                break;
            case 66:
                sound->randPan.min = cursor[0];
                sound->randPan.max = cursor[1];
                sound->randPan.interval = cursor[2];
                sound->randFlags |= 2;
                cursor += 3;
                break;
            case 67:
                sound->randFlags &= ~2;
                break;
            case 68:
                sound->randPitchMin = SE_READ16(cursor);
                sound->randPitchMax = SE_READ16(cursor + 2);
                sound->randPitchInterval = cursor[4];
                sound->randFlags |= 4;
                cursor += 5;
                break;
            case 69:
                sound->randFlags &= ~4;
                break;
            case 80:
                sound->mods[(s8)*cursor++].value = 0;
                break;
            case 81:
                sound->mods[(s8)cursor[0]].value = SE_READ16(cursor + 1);
                cursor += 3;
                break;
            case 82:
                sound->mods[(s8)cursor[0]].value += SE_READ16(cursor + 1);
                cursor += 3;
                break;
            case 88:
                idx = *cursor++;
                sound->mods[idx].target = 9;
                sound->modMask |= 1 << idx;
                break;
            case 89:
                idx = *cursor++;
                sound->mods[idx].target = 10;
                sound->modMask |= 1 << idx;
                break;
            case 90:
                idx = *cursor++;
                sound->mods[idx].target = 11;
                sound->modMask |= 1 << idx;
                break;
            case 1:
                break;
            case 0:
                if (sound->callDepth != 0) {
                    cursor = sound->callStack[--sound->callDepth];
                    sound->wait = 0;
                    break;
                }
                if (sound->soundIdx < 0 && ((sound->flags & 0x1000) || sound->sndState != AL_STOPPED)) {
                    cursor = op;
                    sound->wait = 1;
                    break;
                }
                sound->flags |= 0x40000;
                sound->wait = 1;
                break;
            default:
                sound->flags |= 0x40000;
                sound->wait = 1;
                break;
        }
    }
    sound->script = cursor;
    sound->wait--;
}
#else
INCLUDE_ASM("asm/nonmatchings/1140", func_80004D4C_main);
#endif

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

/* Steps the pitch LFO of a voice, returning its current value. */
f32 func_80005850_main(GameSound *sound) {
    f32 val;
    f32 half;

    if (sound->lfoType == 0) {
        return 0.0f;
    }
    if (sound->flags & 0x1000) {
        switch (sound->lfoType) {
            case 4:
                sound->lfoPhase = 1;
                sound->lfoPeriod = 0x105 - sound->lfoRate;
                break;
            case 2:
                sound->lfoPhase = 0;
            case 1:
            case 3:
                sound->lfoPeriod = 0x105 - sound->lfoRate;
                break;
            case 5:
                sound->lfoPeriod = (0x105 - sound->lfoRate) / 2;
                sound->lfoRand = 0.0f;
                break;
        }
        sound->lfoCounter = 0;
        sound->lfoDelaySave = sound->lfoDelay;
        sound->lfoActive = 1;
    }
    if (sound->lfoActive == 0) {
        return 0.0f;
    }
    if (sound->lfoDelay != 0) {
        sound->lfoDelay--;
        return 0.0f;
    }
    switch (sound->lfoType) {
        case 1:
            if (sound->lfoCounter >= sound->lfoPeriod) {
                sound->lfoCounter = 0;
            }
            val = (f32)sound->lfoCounter / sound->lfoPeriod;
            val = sinf(val * TWO_PI);
            break;
        case 2:
            if (sound->lfoCounter >= sound->lfoPeriod / 4) {
                if (++sound->lfoPhase >= 4) {
                    sound->lfoPhase = 0;
                }
                sound->lfoCounter = 0;
            }
            val = (f32)sound->lfoCounter / (sound->lfoPeriod / 4);
            switch (sound->lfoPhase) {
                case 1:
                    val = 1.0f - val;
                    break;
                case 2:
                    val = -val;
                    break;
                case 3:
                    val = -(1.0f - val);
                    break;
            }
            break;
        case 3:
            if (sound->lfoCounter > sound->lfoPeriod) {
                sound->lfoCounter = 0;
            }
            half = sound->lfoPeriod / 2.0f;
            val = (sound->lfoCounter - half) / half;
            break;
        case 4:
            if (sound->lfoCounter >= sound->lfoPeriod) {
                sound->lfoCounter = 0;
                sound->lfoPhase *= -1;
            }
            val = sound->lfoPhase;
            break;
        case 5:
            if (sound->lfoCounter >= sound->lfoPeriod) {
                sound->lfoCounter = 0;
                sound->lfoRand = (100 - (s32)guRandom() % 201) / 100.0f;
            }
            val = sound->lfoRand;
            break;
    }
    sound->lfoCounter += 2;
    return val;
}

/* Updates the pitch modulation of a voice: LFO, sweep, pitch envelope, random
 * pitch and external modulation. */
void func_80005BAC_main(GameSound *sound, f32 lfo) {
    f32 detune = 0.0f;
    s32 i;
    s32 n;

    if (sound->flags & 0x1000) {
        sound->detune = 0;
    }
    if (sound->lfoDepth != 0) {
        detune = sound->lfoDepth * lfo + SE_CENTS_EPSILON;
    }
    if (sound->sweepActive == 1) {
        if (sound->sweepCounter >= sound->sweepTime) {
            sound->sweepActive = 0;
            sound->key += sound->sweepAmount;
            detune += SE_CENTS_EPSILON;
        } else {
            detune += (f32)sound->sweepCounter / sound->sweepTime * sound->sweepAmount;
        }
        sound->sweepCounter++;
    }
    if (sound->envScript != NULL) {
        if (sound->flags & 0x1000) {
            sound->envDelay = sound->envDelayInit;
            sound->envPtr = sound->envScript;
            sound->envCount = 0;
            sound->envAccum = 0;
            sound->envStep = 0;
        }
        if (sound->envDelay >= 0) {
            if (sound->envDelay != 0) {
                sound->envDelay--;
            } else {
                if (sound->envCount == 0) {
                    if ((sound->envCount = *sound->envPtr++) == 0) {
                        sound->envPtr = sound->envScript;
                        sound->envCount = *sound->envPtr++;
                        sound->envAccum = 0;
                    }
                    if (sound->envCount == -0x80) {
                        if (sound->envStep == sound->envAccum) {
                            sound->key += sound->envStep;
                        } else {
                            sound->key += sound->envAccum;
                        }
                        sound->envDelay = -1;
                        sound->envCount = 0;
                    } else {
                        sound->envStep = ((sound->envPtr[0] << 8) | sound->envPtr[1]) * sound->envScale;
                        sound->envPtr += 2;
                        if (sound->envCount < 0) {
                            sound->envAccum += sound->envStep;
                        }
                        if (sound->envCount > 0) {
                            sound->envAccum = sound->envStep;
                        }
                        if (sound->envCount == 0) {
                            sound->envScript = NULL;
                        }
                    }
                }
                if (sound->envCount > 0) {
                    sound->envCount--;
                    detune += sound->envStep;
                }
                if (sound->envCount < 0) {
                    sound->envCount++;
                    detune += sound->envAccum;
                }
                detune += SE_CENTS_EPSILON;
            }
        }
    }
    if (sound->randFlags & 4) {
        sound->randPitchTimer--;
        if ((sound->flags & 0x1000) || (sound->randPitchTimer == 0 && sound->randPitchInterval != 0)) {
            sound->randPitchTimer = sound->randPitchInterval;
            n = sound->randPitchMax - sound->randPitchMin + 1;
            sound->randPitch = (s32)guRandom() % n + sound->randPitchMin;
        }
        detune += sound->randPitch + SE_CENTS_EPSILON;
    }
    if (sound->modMask != 0) {
        for (i = 0; i < ARRAY_COUNT(sound->mods); i++) {
            n = 1 << i;
            if ((n & sound->modMask) && sound->mods[i].target == 3) {
                detune += sound->mods[i].value + SE_CENTS_EPSILON;
            }
        }
    }
    if (detune != 0.0f) {
        sound->detune = detune;
        sound->flags |= 0x20000;
    }
}

/* Updates the random and modulated pan of a voice. */
void func_80005FE4_main(GameSound *sound) {
    s32 mod = 0;
    s32 modded = FALSE;
    s32 i;
    s32 n;

    if (sound->flags & 0x1000) {
        sound->panMod = 0;
    }
    if (sound->randFlags & 2) {
        sound->randPan.timer--;
        if ((sound->flags & 0x1000) || (sound->randPan.timer == 0 && sound->randPan.interval != 0)) {
            sound->randPan.timer = sound->randPan.interval;
            n = sound->randPan.max - sound->randPan.min + 1;
            sound->scriptPan = sound->randPan.min + (s32)guRandom() % n;
            sound->flags |= 0x8000;
        }
    }
    if (sound->modMask != 0) {
        for (i = 0; i < ARRAY_COUNT(sound->mods); i++) {
            n = 1 << i;
            if ((n & sound->modMask) && sound->mods[i].target == 2) {
                mod += sound->mods[i].value;
                modded = TRUE;
            }
        }
    }
    if (modded) {
        sound->panMod = mod;
        sound->flags |= 0x8000;
    }
}

/* Updates the random and modulated volume of a voice. */
void func_80006148_main(GameSound *sound) {
    s32 mod = 0;
    s32 modded = FALSE;
    s32 i;
    s32 n;

    if (sound->flags & 0x1000) {
        sound->volMod = 0;
    }
    if (sound->randFlags & 1) {
        sound->randVol.timer--;
        if ((sound->flags & 0x1000) || (sound->randVol.timer == 0 && sound->randVol.interval != 0)) {
            sound->randVol.timer = sound->randVol.interval;
            n = sound->randVol.max - sound->randVol.min + 1;
            sound->scriptVol = sound->randVol.min + (s32)guRandom() % n;
            sound->flags |= 0x4000;
        }
    }
    if (sound->modMask != 0) {
        for (i = 0; i < ARRAY_COUNT(sound->mods); i++) {
            n = 1 << i;
            if ((n & sound->modMask) && sound->mods[i].target == 1) {
                mod += sound->mods[i].value;
                modded = TRUE;
            }
        }
    }
    if (modded) {
        sound->volMod = mod;
        sound->flags |= 0x4000;
    }
}

/* Starts, stops and releases the voice's sound as requested by its script. */
void func_800062A8_main(GameSound *sound) {
    s32 start;
    s32 val;

    if (sound->flags & 0x40000) {
        switch (sound->sndState) {
            case AL_PLAYING:
                sound->env.releaseTime = 184000000 / func_80000E9C_main()->cfg.unk1C;
                n_alSndpStop();
            case AL_STOPPING:
                sound->state = 1;
                break;
            default:
                sound->state = 0;
                break;
        }
        sound->flags = 0x800;
        return;
    }
    start = FALSE;
    if (sound->flags & 0x1000) {
        if (sound->sndState == AL_STOPPED) {
            start = TRUE;
            sound->flags &= ~0x1000;
        } else if (sound->soundIdx >= 0) {
            n_alSndpStop();
            sound->flags |= 0x800;
        }
    }
    if (start) {
        if (sound->flags & 0x2000000) {
            val = sound->soundIdx & 0x7FFF;
            bcopy(&D_800A97BC_main->alSounds[val], &sound->sound, sizeof(ALSound));
            if (sound->flags & 0x1F00000) {
                if (!(sound->flags & 0x100000)) {
                    sound->env.attackVolume = sound->sound.envelope->attackVolume;
                }
                if (!(sound->flags & 0x200000)) {
                    sound->env.decayVolume = sound->sound.envelope->decayVolume;
                }
                if (!(sound->flags & 0x400000)) {
                    sound->env.attackTime = sound->sound.envelope->attackTime;
                }
                if (!(sound->flags & 0x800000)) {
                    sound->env.decayTime = sound->sound.envelope->decayTime;
                }
                if (!(sound->flags & 0x1000000)) {
                    sound->env.releaseTime = sound->sound.envelope->releaseTime;
                }
            } else {
                bcopy(sound->sound.envelope, &sound->env, sizeof(ALEnvelope));
            }
            sound->sound.envelope = &sound->env;
            if (sound->soundIdx >= 0) {
                sound->env.releaseTime = 184000000 / func_80000E9C_main()->cfg.unk1C;
            }
            if (!(sound->flags & 0x4000000)) {
                val = (s32)sound->sound.keyMap;
                sound->pitchRatio = (f32)val / func_80000E9C_main()->cfg.unk1C;
            }
            sound->sound.keyMap = NULL;
            sound->flags &= ~0x7F00000;
        }
        sound->sndId = n_alSndpAllocate(&sound->sound);
        if (sound->sndId >= 0) {
            n_alSndpSetPriority(sound->sndId, 20);
        }
    }
    func_8000658C_main(sound, start);
}

/* Applies the changed parameters of a voice to its sound. */
void func_8000658C_main(GameSound *sound, s32 force) {
    s32 val;

    if (sound->sndId < 0) {
        return;
    }
    n_alSndpSetSound(sound->sndId);
    if ((sound->flags & 0x4000) || force) {
        val = sound->volMod + sound->scriptVol;
        if (val >= 0x80) {
            val = 0x7F;
        }
        if (val < 0) {
            val = 0;
        }
        val = val * D_800A97BC_main->fadeVol * sound->vol * sound->sound.sampleVolume / (127 * 127 * 127);
        val = val * D_800A97BC_main->vol * D_800A97BC_main->configVol * sound->unk_B2 / (127 * 127 * 127);
        if (!(sound->flags & 4)) {
            val = val * D_800A97BC_main->pauseState / 127;
        }
        n_alSndpSetVol(func_8000113C_main(val));
    }
    if ((sound->flags & 0x8000) || force) {
        val = 0x40;
        if (!(D_800CB8AC_main & 1)) {
            val = sound->panMod + sound->scriptPan;
            val = sound->unk_B3 - 0x40 + sound->pan - 0x40 + val;
            if (val < 0) {
                val = 0;
            }
            if (val >= 0x80) {
                val = 0x7F;
            }
        }
        n_alSndpSetPan(val);
    }
    if ((sound->flags & 0x20000) || force) {
        val = sound->pitch + sound->detune;
        n_alSndpSetPitch(alCents2Ratio(val + sound->key) * sound->pitchRatio * sound->unk_B4);
    }
    if ((sound->flags & 0x10000) || force) {
        if (sound->scriptFxMix != 0) {
            val = sound->scriptFxMix;
        } else {
            val = sound->fxMix;
        }
        n_alSndpSetFXMix(val);
    }
    if (force && sound->sndState == AL_STOPPED) {
        n_alSndpPlay();
    }
    if (sound->flags & 0x2000) {
        n_alSndpStop();
        sound->flags |= 0x800;
    }
    sound->flags &= ~0x3E000;
}

void func_80006830_main(void) {
    switch (D_800A97BC_main->pauseState) {
        case 0x7E:
            D_800A97BC_main->pauseState = 0x40;
            break;
        case 0x40:
            D_800A97BC_main->pauseState = 10;
            break;
        case 10:
            D_800A97BC_main->pauseState = 0;
            break;
        case 0:
            D_800A97BC_main->pauseState = -1;
            break;
    }
}

/* Steps the fade of all sound effects. The loop counter doubles as the new
 * fade volume. */
void func_800068B8_main(void) {
    GameSound *sound;
    s32 i;

    if (D_800A97BC_main->fadeTime > 0) {
        if (--D_800A97BC_main->fadeTime != 0) {
            i = (D_800A97BC_main->fadeStep * D_800A97BC_main->fadeTime) >> 24;
            if (i != D_800A97BC_main->fadeVol) {
                D_800A97BC_main->fadeVol = i;
                for (i = 0; i < D_800A97BC_main->soundCount; i++) {
                    sound = &D_800A97BC_main->sounds[i];
                    if (sound->state == 4) {
                        sound->flags |= 0x4000;
                    }
                }
            }
        } else {
            for (i = 0; i < D_800A97BC_main->soundCount; i++) {
                func_800048D0_main(&D_800A97BC_main->sounds[i]);
            }
            D_800A97BC_main->fadeVol = 0x7F;
        }
    }
    if (D_800A97BC_main->fadeTime < 0) {
        if (++D_800A97BC_main->fadeTime != 0) {
            i = 0x7F - ((-D_800A97BC_main->fadeTime * D_800A97BC_main->fadeStep) >> 24);
        } else {
            i = 0x7F;
        }
        if (i != D_800A97BC_main->fadeVol) {
            D_800A97BC_main->fadeVol = i;
            for (i = 0; i < D_800A97BC_main->soundCount; i++) {
                sound = &D_800A97BC_main->sounds[i];
                if (sound->state == 4) {
                    sound->flags |= 0x4000;
                }
            }
        }
    }
}

/* Sets up the sound effect manager. The loop counter doubles as the size of
 * the voice array. */
s32 func_80006A8C_main(SndSys *sys, ALHeap *heap, s32 seCount, s32 vol) {
    str800D5298 *cfg = &sys->cfg;
    SeBankInfo *info = (SeBankInfo *)sys->buf;
    ALSndpConfig config;
    s32 i;

    if (seCount == 0) {
        D_800A97BC_main = NULL;
        return 0;
    }
    if ((D_800A97BC_main = func_800010B8_main(sizeof(SeManager))) == NULL) {
        return 1;
    }
    bzero(D_800A97BC_main, sizeof(SeManager));
    func_80000FE4_main(info, (u8 *)cfg->unkC + sizeof(SndBankHeader), sizeof(SeBankInfo), 0);
    if (func_80003CB8_main(cfg->unkC, info) != 0) {
        return 2;
    }
    if (func_80003DF4_main(cfg->unkC, info) != 0) {
        return 3;
    }
    if (func_80003EE4_main(cfg->unkC, info) != 0) {
        return 4;
    }
    i = cfg->unk54 * sizeof(GameSound);
    if ((D_800A97BC_main->sounds = func_800010B8_main(i)) == NULL) {
        return 5;
    }
    bzero(D_800A97BC_main->sounds, i);
    config.maxSounds = cfg->unk54;
    config.maxEvents = cfg->unk58;
    config.heap = heap;
    if ((D_800A97BC_main->sndp = func_800010B8_main(sizeof(N_ALSndPlayer))) == NULL) {
        return 6;
    }
    n_alSndpNew(D_800A97BC_main->sndp, &config);
    D_800A97BC_main->soundCount = cfg->unk54;
    D_800A97BC_main->seCount = seCount;
    D_800A97BC_main->configVol = vol;
    D_800A97BC_main->pan = 0x40;
    D_800A97BC_main->vol = D_800A97BC_main->fadeVol = D_800A97BC_main->pauseState = D_800A97BC_main->masterVol = 0x7F;
    D_800A97BC_main->minDist = 50.0f;
    D_800A97BC_main->maxDist = 500.0f;
    D_800A97BC_main->unk_44E = 10;
    D_800A97BC_main->unk_450 = 1224.0f;
    D_800A97BC_main->unk_454 = 1.0f;
    for (i = 0; i < D_800A97BC_main->soundCount; i++) {
        D_800A97BC_main->sounds[i].sndId = -1;
    }
    return 0;
}

/* Queues a command for the periodic proc to process. */
void func_80006CD4_main(s32 voiceSlot, s32 cmdType, s32 cmdArg) {
    u32 mask = osSetIntMask(1);
    SeCmd *cmd = &D_800A97BC_main->cmds[D_800A97BC_main->cmdCount];

    cmd->cmdType = cmdType;
    cmd->voiceSlot = voiceSlot;
    cmd->arg.i = cmdArg;
    if (++D_800A97BC_main->cmdCount >= ARRAY_COUNT(D_800A97BC_main->cmds)) {
        func_80001134_main(0, 0x200);
        D_800A97BC_main->cmdCount = 0;
    }
    osSetIntMask(mask);
}

/* Queues a command with a float argument for the periodic proc to process. */
void func_80006D80_main(s32 voiceSlot, s32 cmdType, f32 cmdArg) {
    u32 mask = osSetIntMask(1);
    SeCmd *cmd = &D_800A97BC_main->cmds[D_800A97BC_main->cmdCount];

    cmd->cmdType = cmdType;
    cmd->voiceSlot = voiceSlot;
    cmd->arg.f = cmdArg;
    if (++D_800A97BC_main->cmdCount >= ARRAY_COUNT(D_800A97BC_main->cmds)) {
        func_80001134_main(0, 0x200);
        D_800A97BC_main->cmdCount = 0;
    }
    osSetIntMask(mask);
}

void func_80006E30_main(void) {
    GameSound *sound;
    s32 i;

    if (D_800A97BC_main != NULL && D_800A97BC_main->busy.all == 0) {
        D_800A97BC_main->busy.flag[1] = 1;
        D_800A97BC_main->unk_18 = 0;
        func_80003FB4_main();
        func_80006830_main();
        for (i = 0; i < D_800A97BC_main->soundCount; i++) {
            sound = &D_800A97BC_main->sounds[i];
            func_80004928_main(sound);
            func_800049E8_main(sound);
            func_8000499C_main(sound);
            if (sound->state != 4) {
                if (sound->state == 2 && D_800A97BC_main->pauseState >= 0) {
                    sound->flags |= 0x4000;
                    func_8000658C_main(sound, 0);
                }
            } else {
                func_80004D4C_main(sound);
                func_80005BAC_main(sound, func_80005850_main(sound));
                func_80005FE4_main(sound);
                func_80006148_main(sound);
                func_800062A8_main(sound);
                if (sound->state < 2) {
                    D_800A97BC_main->unk_18--;
                }
            }
        }
        if (D_800A97BC_main->pauseState == 0x7F) {
            func_800068B8_main();
        }
        D_800A97BC_main->busy.flag[1] = 0;
    }
}

void func_80006FC4_main(void) {
    GameSound *sound;
    s32 i;

    if (D_800A97BC_main != NULL) {
        for (i = 0; i < D_800A97BC_main->soundCount; i++) {
            sound = &D_800A97BC_main->sounds[i];
            if (sound->sndId >= 0) {
                n_alSndpSetSound(sound->sndId);
                n_alSndpStop();
            }
        }
        n_alSndpDelete();
    }
}

SeManager *func_8000704C_main(void) {
    return D_800A97BC_main;
}

void func_80007058_main(void) {
    D_800A97BC_main = NULL;
}

s32 func_80007064_main(s32 seId) {
    return func_80007080_main(seId, NULL);
}

/* Starts a sound effect, allocating one voice per layer. Returns the slot of
 * the first layer's voice, or -1 if it could not be played. */
s32 func_80007080_main(s32 seId, SePlayParam *param) {
    SeManager *se = func_8000704C_main();
    s32 slots[4];
    SeEntry *entry;
    GameSound *sound;
    s32 slot;
    s32 variant;
    s32 linkCount;
    s32 i;

    if (se == NULL) {
        return 0;
    }
    if (seId >= se->seCount) {
        return -1;
    }
    if ((entry = se->entries[seId]) == NULL) {
        return -1;
    }
    slot = -1;
    if (param != NULL && (param->flags & 0x100)) {
        slot = param->slot;
    }
    variant = 0;
    if (param != NULL && (param->flags & 0x200)) {
        variant = param->variant;
    }
    if ((slots[0] = func_800072A4_main(seId, 0, slot, variant)) < 0) {
        return -1;
    }
    func_800076B8_main(seId, slots[0], 0xFF, param);
    sound = &se->sounds[slots[0]];
    linkCount = 0;
    for (i = entry->layerCount - 1; i > 0; i--) {
        slot = slots[i] = func_800072A4_main(seId, i, -1, variant);
        if (slot >= 0) {
            func_800076B8_main(seId, slot, entry->priority, param);
            se->sounds[slot].links[0].slot = (s8)slots[0];
            se->sounds[slot].links[0].order = sound->order;
            sound->links[linkCount].slot = slot;
            sound->links[linkCount].order = se->sounds[slot].order;
            linkCount++;
        }
    }
    sound->priority = entry->priority;
    for (i = entry->layerCount - 1; i > 0; i--) {
        if (slots[i] >= 0) {
            func_80006CD4_main(slots[i], 1, i);
        }
    }
    func_80006CD4_main(slots[0], 1, linkCount << 4);
    return slots[0];
}

#ifdef NON_MATCHING
/* The temporaries holding se, entry and mask get different registers (the
 * target gives them lower allocation priority), and the target frame is 8 bytes
 * larger, as if there were an extra unused 8-byte local. */
/* Picks the voice to play the given layer of a sound effect on: the requested
 * slot, a free voice, or the oldest voice of lower priority. Returns -1 if
 * there is none. */
s32 func_800072A4_main(s32 seId, s32 layer, s32 slot, s32 variant) {
    SeManager *se = func_8000704C_main();
    SeEntry *entry = se->entries[seId];
    u32 mask = entry->layers[layer].voiceMask;
    SeVoiceList lists[3];
    GameSound *sound;
    u32 order;
    u32 bit;
    s32 count;
    s32 tmp;
    s32 idx;
    s32 i;
    s32 j;

    if (slot >= 0) {
        if (slot >= se->soundCount) {
            return -1;
        }
        sound = &se->sounds[slot];
        if (sound->state >= 2 && entry->priority < sound->priority) {
            return -1;
        }
        return slot;
    }
    if (variant != 0) {
        mask <<= (variant - 1) * (entry->layers[layer].voiceShift & 0xF);
    }
    lists[SE_VOICES_OTHER].count = 0;
    lists[SE_VOICES_SAME].count = 0;
    lists[SE_VOICES_FREE].count = 0;
    count = 0;
    for (i = (mask & 0x1F) ? 0 : 5; i < se->soundCount && mask != 0; i++) {
        bit = 1 << i;
        if (mask & bit) {
            sound = &se->sounds[i];
            if (sound->state >= 2) {
                if (sound->seId == seId) {
                    lists[SE_VOICES_SAME].slots[lists[SE_VOICES_SAME].count++] = i;
                } else {
                    lists[SE_VOICES_OTHER].slots[lists[SE_VOICES_OTHER].count++] = i;
                }
            } else {
                lists[SE_VOICES_FREE].slots[lists[SE_VOICES_FREE].count++] = i;
            }
            count++;
            mask &= ~bit;
        }
    }
    if (count >= 2) {
        for (j = 0; j < lists[SE_VOICES_SAME].count; j++) {
            sound = &se->sounds[lists[SE_VOICES_SAME].slots[j]];
            if (sound->state == 3 && sound->seId == seId) {
                return -1;
            }
        }
    }
    if (lists[SE_VOICES_FREE].count != 0) {
        return lists[SE_VOICES_FREE].slots[0];
    }
    if (lists[SE_VOICES_OTHER].count != 0) {
        if (lists[SE_VOICES_OTHER].count == 1) {
            idx = lists[SE_VOICES_OTHER].slots[0];
            if (!(entry->priority < se->sounds[idx].priority)) {
                return idx;
            }
        } else {
            for (i = 0; i < lists[SE_VOICES_OTHER].count - 1; i++) {
                order = se->sounds[lists[SE_VOICES_OTHER].slots[i]].order;
                for (j = i + 1; j < lists[SE_VOICES_OTHER].count; j++) {
                    idx = lists[SE_VOICES_OTHER].slots[j];
                    if (se->sounds[idx].order < order) {
                        order = se->sounds[idx].order;
                        tmp = lists[SE_VOICES_OTHER].slots[i];
                        lists[SE_VOICES_OTHER].slots[i] = idx;
                        lists[SE_VOICES_OTHER].slots[j] = tmp;
                    }
                }
            }
            for (j = 0; j < lists[SE_VOICES_OTHER].count; j++) {
                idx = lists[SE_VOICES_OTHER].slots[j];
                if (!(entry->priority < se->sounds[idx].priority)) {
                    return idx;
                }
            }
        }
    }
    if (lists[SE_VOICES_SAME].count != 0) {
        order = se->sounds[lists[SE_VOICES_SAME].slots[0]].order;
        i = 0;
        for (j = 1; j < lists[SE_VOICES_SAME].count; j++) {
            sound = &se->sounds[lists[SE_VOICES_SAME].slots[j]];
            if (sound->order < order) {
                order = sound->order;
                i = j;
            }
        }
        return lists[SE_VOICES_SAME].slots[i];
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/1140", func_800072A4_main);
#endif

/* Sets up a voice for a newly started sound effect layer. */
void func_800076B8_main(s32 seId, s32 slot, u8 priority, SePlayParam *param) {
    SeManager *se = func_8000704C_main();
    GameSound *sound;
    SePosParam pos;

    func_80006CD4_main(slot, 0, 0);
    sound = &se->sounds[slot];
    sound->state = 3;
    sound->order = se->order++;
    sound->priority = priority;
    sound->linkCount = 0;
    sound->unk_A4 = sound->unk_A8 = 0.0f;
    sound->seId = seId;
    if (param != NULL) {
        if (param->flags & 1) {
            sound->vol = param->vol;
            func_80006CD4_main(slot, 2, param->vol);
        }
        if (param->flags & 2) {
            sound->pan = param->pan;
            func_80006CD4_main(slot, 7, param->pan);
        }
        if (param->flags & 4) {
            sound->pitch = param->pitch;
            func_80006CD4_main(slot, 5, param->pitch);
        }
        if (param->flags & 8) {
            sound->fxMix = param->fxMix;
            func_80006CD4_main(slot, 9, param->fxMix);
        }
        pos.flags = 0;
        if (param->flags & 0x20) {
            pos.flags = 2;
            pos.dist = param->dist;
        }
        if (param->flags & 0x10) {
            pos.flags |= 1;
            pos.angle = param->angle;
        }
        if (param->flags & 0x40) {
            pos.flags |= 0x10;
            pos.unk_0C = param->unk_24;
        }
        if (param->flags & 0x80) {
            pos.flags |= 0x20;
            pos.unk_10 = param->unk_28;
        }
        if (pos.flags & 0x33) {
            func_8000810C_main(slot, &pos);
        }
    }
}

s32 func_800078A4_main(void) {
    SeManager *se = func_8000704C_main();

    if (se == NULL) {
        return 0;
    }
    return se->seCount;
}

s32 func_800078CC_main(void) {
    SeManager *se = func_8000704C_main();

    if (se == NULL) {
        return 0;
    }
    return se->unk_18;
}

s32 func_800078F8_main(s32 slot) {
    SeManager *se = func_8000704C_main();

    if (se == NULL) {
        return 0;
    }
    return se->sounds[slot].state;
}

/* Returns the slot of the first layer of a playing sound effect. */
s32 func_8000793C_main(s32 seId) {
    SeManager *se = func_8000704C_main();
    GameSound *sound;
    s32 i;

    if (se == NULL) {
        return 0;
    }
    for (i = 0; i < se->soundCount; i++) {
        sound = &se->sounds[i];
        if (sound->state >= 2 && sound->seId == seId && sound->layer == 0) {
            return i;
        }
    }
    return -1;
}

s32 func_800079CC_main(s32 seId) {
    SeManager *se = func_8000704C_main();

    if (se == NULL) {
        return 0;
    }
    return se->entries[seId]->unk_03;
}

void func_80007A10_main(SeParam *param) {
    SeManager *se = func_8000704C_main();

    if (se != NULL) {
        param->masterVol = se->masterVol;
        param->unk_08 = se->unk_2A;
        param->pan = se->pan;
        param->unk_10 = se->unk_2E;
    }
}

void func_80007A60_main(SeParam *param) {
    SeManager *se = func_8000704C_main();

    if (se != NULL) {
        if (param->flags & 1) {
            se->masterVol = param->masterVol;
        }
        if (param->flags & 4) {
            se->unk_2A = param->unk_08;
        }
        if (param->flags & 2) {
            se->pan = param->pan;
        }
        if (param->flags & 8) {
            se->unk_2E = param->unk_10;
        }
    }
}

void func_80007AF0_main(s32 vol) {
    if (func_8000704C_main() != NULL) {
        func_80006CD4_main(0, 3, vol);
    }
}

/* Sets the volume of the given voice, or of every voice when negative. */
void func_80007B28_main(s32 slot, s32 vol) {
    SeManager *se = func_8000704C_main();

    if (se != NULL) {
        if (slot < 0) {
            for (slot = 0; slot < se->soundCount; slot++) {
                se->sounds[slot].vol = vol;
            }
            func_80006CD4_main(0, 4, vol);
        } else {
            se->sounds[slot].vol = vol;
            func_80006CD4_main(slot, 2, vol);
        }
    }
}

/* Sets the pitch of the given voice, or of every voice when negative. */
void func_80007BD4_main(s32 slot, s32 pitch) {
    SeManager *se = func_8000704C_main();

    if (se != NULL) {
        if (slot < 0) {
            for (slot = 0; slot < se->soundCount; slot++) {
                se->sounds[slot].pitch = pitch;
            }
            func_80006CD4_main(0, 6, pitch);
        } else {
            se->sounds[slot].pitch = pitch;
            func_80006CD4_main(slot, 5, pitch);
        }
    }
}

/* Sets the pan of the given voice, or of every voice when negative. */
void func_80007C80_main(s32 slot, s32 pan) {
    SeManager *se = func_8000704C_main();

    if (se != NULL) {
        if (slot < 0) {
            for (slot = 0; slot < se->soundCount; slot++) {
                se->sounds[slot].pan = pan;
            }
            func_80006CD4_main(0, 8, pan);
        } else {
            se->sounds[slot].pan = pan;
            func_80006CD4_main(slot, 7, pan);
        }
    }
}

/* Sets the effect mix of the given voice, or of every voice when negative. */
void func_80007D2C_main(s32 slot, s32 fxMix) {
    SeManager *se = func_8000704C_main();

    if (se != NULL) {
        if (slot < 0) {
            for (slot = 0; slot < se->soundCount; slot++) {
                se->sounds[slot].fxMix = fxMix;
            }
            func_80006CD4_main(0, 10, fxMix);
        } else {
            se->sounds[slot].fxMix = fxMix;
            func_80006CD4_main(slot, 9, fxMix);
        }
    }
}

/* Stops the given voice, or every voice when negative. */
void func_80007DD8_main(s32 slot) {
    SeManager *se = func_8000704C_main();
    GameSound *sound;
    s32 i;

    if (se == NULL) {
        return;
    }
    se->busy.flag[0] = 1;
    if (slot < 0) {
        func_80006CD4_main(0, 12, 0);
        for (i = 0; i < se->soundCount; i++) {
            sound = &se->sounds[i];
            if (sound->state >= 2) {
                sound->state = 1;
            }
        }
    } else {
        sound = &se->sounds[slot];
        if (sound->state >= 2) {
            func_80006CD4_main(slot, 11, 0);
            sound->state = 1;
        }
    }
    se->busy.flag[0] = 0;
}

void func_80007EC0_main(s32 time) {
    if (func_8000704C_main() != NULL) {
        func_80006CD4_main(0, 13, time);
    }
}

s32 func_80007EF8_main(void) {
    SeManager *se = func_8000704C_main();

    if (se == NULL) {
        return 0;
    }
    return se->fadeTime;
}

/* Pauses every playing voice. */
void func_80007F24_main(void) {
    SeManager *se = func_8000704C_main();
    GameSound *sound;
    s32 i;

    if (se != NULL && se->pauseState >= 0x7F) {
        func_80006CD4_main(0, 14, 0);
        se->busy.flag[0] = 1;
        for (i = 0; i < D_800A97BC_main->soundCount; i++) {
            sound = &D_800A97BC_main->sounds[i];
            if (sound->state >= 2) {
                sound->state = 2;
            }
        }
        se->busy.flag[0] = 0;
    }
}

/* Resumes the paused voices. */
void func_80007FD4_main(s32 time) {
    SeManager *se = func_8000704C_main();

    if (se != NULL && se->pauseState != 0x7F) {
        func_80006CD4_main(0, 15, time);
    }
}

void func_8000801C_main(SePosConfig *cfg) {
    SeManager *se = func_8000704C_main();

    if (se != NULL) {
        if (cfg->flags & 1) {
            se->angle = cfg->angle;
        }
        if (cfg->flags & 2) {
            se->minDist = cfg->minDist;
        }
        if (cfg->flags & 4) {
            se->maxDist = cfg->maxDist;
        }
        if (cfg->flags & 8) {
            se->unk_444 = cfg->unk_10;
        }
        if (cfg->flags & 0x10) {
            se->unk_448 = cfg->unk_14;
        }
        if (cfg->flags & 0x20) {
            se->unk_450 = cfg->unk_18;
        }
        if (cfg->flags & 0x40) {
            se->unk_454 = cfg->unk_1C;
        }
        if (cfg->flags & 0x80) {
            se->unk_44E = cfg->unk_20;
        }
    }
}

/* Sets the volume and pan of a voice from its distance and angle to the
 * listener. */
void func_8000810C_main(s32 slot, SePosParam *param) {
    SeManager *se = func_8000704C_main();
    f32 dist;
    f32 range;
    s32 val;

    if (se == NULL) {
        return;
    }
    if (param->flags & 2) {
        dist = param->dist;
        if (dist < 0.0f) {
            dist = -dist;
        }
        dist -= se->minDist;
        if (dist < 0.0f) {
            dist = 0.0f;
        }
        range = se->maxDist - se->minDist;
        val = 0;
        if (dist <= range) {
            val = (range - dist) * 128.0f / range;
            if (val >= 0x80) {
                val = 0x7F;
            }
        }
        func_80006CD4_main(slot, 16, val);
    }
    if (param->flags & 1) {
        val = se->angle + param->angle;
        if (val >= 360) {
            val -= 360;
        }
        if (val > 180) {
            val = 360 - val;
        }
        val = val * 128 / 180;
        if (val >= 0x80) {
            val = 0x7F;
        }
        range = se->unk_448;
        if (range != 0.0f) {
            dist = param->dist;
            if (dist < 0.0f) {
                dist = -dist;
            }
            dist -= se->unk_444;
            if (dist < 0.0f) {
                dist = 0.0f;
            }
            if (dist < range) {
                val = 64.0f - (64 - val) * (dist / range);
            }
        }
        func_80006CD4_main(slot, 17, val);
    }
}
