#include "game/audio.h"
#include "game/msm.h"
#include "game/vibrator.h"
#include "game/pad.h"
#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "variables.h"
#include "game/gamework_data.h"
#include "ld_addrs.h"

static s16 HuAudCharVoiceGrp[6];
extern s8 omPadStkX[4];
extern s8 omPadStkY[4];
extern s16 omPadBtn[4];
extern u16 omPadBtnDown[4];
extern s16 omPadBtnRep[4];
extern s16 HuAudSeVol[];
extern s16 HuAudSubMusNo;
extern u8 saveCommonBuf;
extern str800D5298 HuAudSysConfig;
extern s32 D_800D52C0_main;
extern omObjData *HuAudFadeObj;

u16 HuAudMusEnableF = 1;
u16 HuAudSeEnableF = 1;
s16 HuAudMusId = -1; // active musId
u16 HuAudStat = 1;  // stat/attr
s16 HuAudFxTypeNext = 0;
s16 HuAudFxType = 0;
s16 HuAudFxParamNext = 1;
s16 HuAudFxParam = 1;
s16 HuAudSeChMax = 0x40;


s16 HuAudSeqPlay(s16 musId) {
    if (HuAudMusEnableF == 0) {
        return 0;
    }
    if (HuAudMusId == musId) {
        return 0;
    }
    if (musId == 0) {
        return -1;
    }
    msmMusStop(HuAudMusNo);
    HuAudMusId = musId;
    HuAudStat |= 2;
    HuAudStat &= ~(1 | 8);
    HuAudMusNo = msmMusPlayDefault(musId);
    return HuAudMusNo;
}

s16 HuAudSubSeqPlay(s16 musId) {
    if (musId == 0) {
        return -1;
    }
    if (HuAudMusEnableF == 0) {
        return 0;
    }
    HuAudStat |= 0x20;
    HuAudStat &= ~(0x10 | 0x80);
    HuAudSubMusNo = msmMusPlayDefault(musId);
    if (HuAudFadeObj != NULL) {
        OM_GET_DATA_PTR(HuAudFadeObj, UnkAudioObjData)->unk34 = -1;
    }
    return HuAudSubMusNo;
}

void HuAudSubSeqParamSet(s32 arg0) {
    if (HuAudFadeObj != NULL) {
        OM_GET_DATA_PTR(HuAudFadeObj, UnkAudioObjData)->unk34 = arg0;
    }
}

void HuAudSeqVolFadeOut(s16 duration) {
    UnkAudioObjData *data;
    s16 frames = duration;
    f32 volume;

    if (HuAudFadeObj != NULL) {
        data = OM_GET_DATA_PTR(HuAudFadeObj, UnkAudioObjData);
        volume = msmMusGetVolume(HuAudMusNo);
        data->unk24 = data->unk2C = volume;
        data->unk18 = frames;
        if (duration == 0) {
            data->unk1C = -volume;
            data->unk2C = 0;
            msmMusSetVolume(HuAudMusNo, 0);
        } else {
            data->unk1C = -volume / frames;
            data->unk14 = 1;
        }
    }
}

void HuAudSeqVolFadeIn(s16 duration) {
    UnkAudioObjData *data;
    s16 frames = duration;

    if (HuAudFadeObj != NULL) {
        data = OM_GET_DATA_PTR(HuAudFadeObj, UnkAudioObjData);
        if (duration == 0) {
            data->unk2C = data->unk24;
            msmMusSetVolume(HuAudMusNo, data->unk24);
        } else {
            if (frames < 0) {
                data->unk1C = -data->unk1C;
            } else {
                data->unk1C = data->unk24 / frames;
            }
            data->unk14 = 1;
        }
    }
}

void HuAudSubSeqVolFadeOut(s16 duration) {
    UnkAudioObjData *data;
    s16 frames = duration;
    f32 volume;

    if (HuAudFadeObj != NULL) {
        data = OM_GET_DATA_PTR(HuAudFadeObj, UnkAudioObjData);
        volume = msmMusGetVolume(HuAudSubMusNo);
        data->unk28 = data->unk30 = volume;
        data->unk1A = frames;
        if (duration == 0) {
            data->unk20 = -volume;
            data->unk30 = 0;
            msmMusSetVolume(HuAudSubMusNo, 0);
        } else {
            data->unk20 = -volume / frames;
            data->unk16 = 1;
        }
    }
}

void HuAudSubSeqVolFadeIn(s16 duration) {
    UnkAudioObjData *data;
    s16 frames = duration;

    if (HuAudFadeObj != NULL) {
        data = OM_GET_DATA_PTR(HuAudFadeObj, UnkAudioObjData);
        if (duration == 0) {
            data->unk30 = data->unk28;
            msmMusSetVolume(HuAudSubMusNo, data->unk28);
        } else {
            if (frames < 0) {
                data->unk20 = -data->unk20;
            } else {
                data->unk20 = data->unk28 / frames;
            }
            data->unk16 = 1;
        }
    }
}

void HuAudSubSeqPlayMute(s16 musId) {
    HuAudSubSeqPlay(musId);
    msmMusSetVolume(HuAudSubMusNo, 127);
    HuAudSubSeqVolFadeOut(0);
}

void HuAudSeqStop(void) {
    HuAudMusId = -1;
    msmMusStop(HuAudMusNo);
    HuAudStat &= ~(2 | 8);
    HuAudStat |= 1;
}

void HuAudSeqFadeOut(s16 speed) {
    HuAudMusId = -1;
    msmMusFadeOut(HuAudMusNo, speed);
    HuAudStat |= 8;
}

void HuAudSeqVolSet(s8 volume) {
    msmMusSetVolume(HuAudMusNo, volume);
}

void HuAudSeqMasterVolSet(s8 volume) {
    msmMusSetMasterVolume(volume);
    HuAudStat &= ~8;
}

void HuAudSeqTempoSet(s16 arg0) {
    msmMusSetTempo(HuAudMusNo, arg0);
}

s16 HuAudSeqTempoGet(void) {
    return msmMusGetTempo(HuAudMusNo);
}

s16 HuAudFXPlay(s16 seId) {
    if (HuAudSeEnableF == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return msmSePlayDefault(seId);
}

void HuAudFXVolSet(s16 seNo, s8 volume) {
    HuAudSeVol[seNo] = volume;
    msmSeSetVolume(seNo, volume);
}

void HuAudFXAllFadeOut(s32 arg0) {
    s32 i;

    if (HuAudFadeObj != NULL) {
        for (i = 0; i < HuAudSeChMax; i++) {
            HuAudFXFadeOut(i, (s16)arg0);
        }
    }
}

void HuAudFXMasterVolSet(s8 volume) {
    s32 i;

    for (i = 0; i < HuAudSeChMax; i++) {
        HuAudSeVol[i] = volume;
    }
    msmSeSetMasterVolume(volume);
}

void HuAudFXPitchSet(s32 seNo, s32 pitch) {
    msmSeSetPitch((s16)seNo, (s16)pitch);
}

s16 CharFXPlay(s16 seId, u8 charNo) {
    if (HuAudSeEnableF == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return msmSePlayDefault(seId + charNo + 1);
}

s32 _HuAudPlayerFXPlay(s16 arg0, s16 arg1) {
    SePlayParam sp10;

    sp10.flags = 0x200;
    sp10.variant = arg1 + 1;
    return msmSePlay(arg0, &sp10);
}

s16 HuAudPlayerFXPlay(s16 arg0, s16 arg1) {
    if (HuAudSeEnableF == 0) {
        return 0;
    }
    if (arg0 == 0) {
        return 0;
    }
    return _HuAudPlayerFXPlay(arg0, arg1);
}

s16 PlayerFXPlay(s16 seId, s16 playerIdx) {
    if (HuAudSeEnableF == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return _HuAudPlayerFXPlay(seId + GwPlayer[playerIdx].chr + 1, playerIdx);
}

void HuAudFXStop(s32 seNo) {
    msmSeStop((s16)seNo);
}

void HuAudFXAllStop(void) {
    msmSeStop(-1);
}

s16 HuAudFXIdStop(s16 seId) {
    s16 seNo;

    seNo = msmSeSearchEntry(seId);
    if (seNo != -1) {
        msmSeStop(seNo);
    }
    return seNo;
}

void HuAudFXAllPanning(s16 arg0) {
    msmSeSetPan(-1, arg0);
}

void HuAudFXPanning(s16 arg0, s16 arg1) {
    msmSeSetPan(arg0, arg1);
}

void HuAudStatUpdate(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        HuAudCharVoiceGrp[i] = -1;
    }
    switch (msmMusGetStatus(HuAudMusNo)) {
        case 0:
            HuAudStat |= 1;
            HuAudStat &= ~2;
            break;
        case 1:
            break;
        case 2:
            break;
    }
    switch (msmMusGetStatus(HuAudSubMusNo)) {
        case 0:
            HuAudStat |= 0x10;
            HuAudStat &= ~(0x20 | 0x80);
            break;
        case 1:
            break;
        case 2:
            break;
    }
}

void HuAudFXFadeOut(s16 seNo, s32 duration) {
    UnkAudioObjData *data;

    if (HuAudFadeObj != NULL && msmSeGetStatus(seNo) != 0) {
        data = OM_GET_DATA_PTR(HuAudFadeObj, UnkAudioObjData);
        data->unk10[seNo] |= 1;
        data->unk00[seNo] = HuAudSeVol[seNo];
        data->unk04[seNo] = (f32)HuAudSeVol[seNo] / (s16)duration;
    }
}

void HuAudFXAllVolFadeDown(s16 duration) {
    UnkAudioObjData *data;
    s32 i;

    if (HuAudFadeObj != NULL) {
        data = OM_GET_DATA_PTR(HuAudFadeObj, UnkAudioObjData);
        for (i = 0; i < HuAudSeChMax; i++) {
            data->unk10[i] |= 6;
            if (data->unk10[i] & 1) {
                data->unk08[i] = data->unk00[i];
                data->unk0C[i] = data->unk00[i] / duration;
            } else {
                data->unk08[i] = HuAudSeVol[i];
                data->unk0C[i] = (f32)HuAudSeVol[i] / duration;
            }
        }
    }
}

void HuAudFXAllVolRestore(void) {
    UnkAudioObjData *data;
    s32 i;
    s16 volume;

    if (HuAudFadeObj != NULL) {
        data = OM_GET_DATA_PTR(HuAudFadeObj, UnkAudioObjData);
        for (i = 0; i < HuAudSeChMax; i++) {
            data->unk10[i] &= ~6;
            if (data->unk10[i] & 1) {
                volume = (s32)data->unk00[i];
            } else {
                volume = HuAudSeVol[i];
            }
            msmSeSetVolume(i, volume);
        }
    }
}

void HuAudPlayerParamCopy(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omPadStkX[i] = HuPadStkX[i];
        omPadStkY[i] = HuPadStkY[i];
        omPadBtn[i] = HuPadBtn[i];
        omPadBtnDown[i] = HuPadBtnDown[i];
        omPadBtnRep[i] = HuPadBtnRep[i];
    }
}

// Doesn't seem to be audio related? Maybe part of the next file.
void omVibrate(s16 player, s16 duration, s16 off, s16 on) {
    if (!(GwPlayer[player].stat & PLAYER_IS_CPU)) {
        RepeatVibrator(GwPlayer[player].pad, duration, off, on);
    }
}

u16 HuAudDummy(void) {
    return 0;
}

void HuAudInit(void) {
    str800D5298 *temp;

    msmSysGetConfig(&HuAudSysConfig);
    temp = &HuAudSysConfig;
    temp->unk28 = 1; //?
    HuAudSysConfig.unk8 = audio_mbf0_ROM_START;
    HuAudSysConfig.unkC = audio_sbf0_ROM_START;
    msmSysInit(&HuAudSysConfig);
    if (!(saveCommonBuf & 1)) {
        msmSysSetOutputMode(0);
    } else {
        msmSysSetOutputMode(1);
    }
}
