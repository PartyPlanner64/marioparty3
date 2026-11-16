#include "common.h"
#include "msetup_internal.h"
#include "game/mallocblock.h"

extern MsetupPlayerConfig msetup_playerConfig;
extern s16 msetup_shadowMdl;
extern s32 msetup_chrMdlFileTbl[];
extern u8 msetup_chrAnimAltTbl[];
extern s32 msetup_chrMotEnterTbl[];
extern s32 msetup_chrMotEnterAltTbl[];
extern s32 msetup_chrMotStartTbl[];
extern s32 msetup_comLevelIconTbl[];
extern s32 msetup_handicapIconTbl[];
extern s32 msetup_duelHandicapIconTbl[];
extern u8 msetup_playerIconTPLvlTbl[];
extern u16 msetup_chrMotEnterAltMask;
extern MsetupModelEntry msetup_tumbleMdlEntryTbl[];
extern Vec msetup_playerPosTbl[];
extern Vec msetup_duelPlayerPosTbl[];
extern f32 msetup_playerRotTbl[];
extern f32 msetup_duelPlayerRotTbl[];
extern s16 msetup_playerAppearDelayTbl[];
extern Process *msetup_playerProcTbl[];
extern MsetupEntryAnim msetup_playerWorkTbl[];
extern omObjData *msetup_effObj;
extern s16 msetup_setupMode;
extern s16 msetup_padNo;
extern s16 msetup_winId;
extern s16 msetup_winIdTbl[2];
extern s16 msetup_winMode;

s16 msetup_SpiralEffCreate(s32, s32);
s32 msetup_SpiralEffAdd(s16, f32, f32, f32);
void msetup_PlayerProc(void);
void msetup_TumbleJumpMove(s16, s16);
void msetup_HmfAnimSet(s16, s16 *, s16);
void msetup_ModelEntryReadAll(MsetupModelEntry *, MsetupModelHandle *, s32);
void msetup_WinProc(void);
s16 msetup_HmfAnimCreate(s16, s16 *, s32, char *);

void msetup_TumbleJumpMove(s16 model, s16 linkedModel) {
    f32 angle = 330.0f;
    f32 angleStep = -4.0f;
    f32 phase = 0.0f;
    f32 phaseStep = 90.0f / 16.0f;
    f32 y = 260.0f;
    f32 yStep = -260.0f / 14.0f;
    f32 x = -86.0f;
    f32 z = 617.0f;
    f32 temp;
    s32 i;

    for (i = 0; i < 15; i++) {
        Hu3DModelPosSet(model, x, y, z);
        Hu3DModelPosSet(linkedModel, x, 0.0f, z);
        temp = y + 100.0f;
        msetup_EffEmitPosSet(msetup_effObj, 0, 100, x, temp, z);
        msetup_EffEmitPosSet(msetup_effObj, 1, 100, x, temp, z);
        temp = (1.0 - y * 0.009) * 0.6;
        if (temp < 0.0f) {
            temp = 0.0f;
        }
        Hu3DModelScaleSet(linkedModel, temp, 1.0f, temp);
        angle += angleStep;
        y += yStep;
        phase += phaseStep;
        temp = 500.0f - sindf(phase) * 500.0f;
        x = temp * sindf(angle) + 194.0f;
        z = temp * cosdf(angle) + 197.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, 194.0f, 0.0f, 197.0f);
    Hu3DModelPosSet(linkedModel, 194.0f, 0.0f, 197.0f);
}

void msetup_TumbleEnterExec(MsetupModelHandle *models, s16 *animSlot, s16 *anim) {
    s16 model;
    s16 linkedModel;

    model = models[0].model;
    linkedModel = models[3].model;
    msetup_effObj->work[0] = 1;
    msetup_effObj->work[1] = 1;
    msetup_EffEmitNumSet(msetup_effObj, 2);
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(linkedModel, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    msetup_TumbleJumpMove(model, linkedModel);
    msetup_effObj->work[0] = 0;
    HuAudFXPlay(0x135);
    Hu3DMotionAttrSet(model, 2, 0);
    while (Hu3DData[model].motTime < 40.0) {
        HuPrcVSleep();
    }
    Hu3DMotionModelSet(model, models[2].model);
    while (Hu3DData[model].motTime < 45.0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2A8);
    msetup_HmfAnimSet(model, animSlot, *anim);
    while (Hu3DData[model].motTime < 80.0) {
        HuPrcVSleep();
    }
    Hu3DMotionSet(model, models[0].motion);
    Hu3DMotionAttrSet(model, 2, 2);
}

void msetup_TumbleProc(void) {
    MsetupModelHandle models[4];
    s16 animSlot[3];
    s16 anim;
    s16 model;
    s16 linkedModel;
    s16 state;
    s16 *requestedState;

    requestedState = HuPrcCurrentGet()->user_data;
    omAddPrcObj(msetup_WinProc, 0x3F00, 0x800, 0);
    msetup_ModelEntryReadAll(msetup_tumbleMdlEntryTbl, models, 4);
    model = models[0].model;
    linkedModel = models[3].model;
    Hu3DModelScaleSet(linkedModel, 0.6f, 1.0f, 0.6f);
    Hu3DMotionSet(model, models[1].motion);
    Hu3DMotionAttrSet(model, 2, 2);
    animSlot[0] = -1;
    anim = msetup_HmfAnimCreate(model, animSlot, 0xA007E, "c204n_0_DEF");
    msetup_HmfAnimSet(model, animSlot, -1);
    state = 0;
    while (1) {
        if (state != *requestedState) {
            state = *requestedState;
        }
        switch (state) {
            case 0:
                break;
            case 1:
                msetup_TumbleEnterExec(models, animSlot, &anim);
                *requestedState = 0;
                break;
            case 2:
                Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(linkedModel, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                *requestedState = 0;
                break;
        }
        HuPrcVSleep();
    }
}

s16 msetup_HmfAnimCreate(s16 model, s16 *animSlot, s32 dataId, char *name) {
    void *data;
    s32 anim;
    s16 length;

    if (animSlot[0] >= 0) {
        Hu3DAnimKill(animSlot[0]);
        Hu3DAnimKill(animSlot[1]);
    }
    data = DataRead(dataId);
    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    animSlot[1] = anim;
    Hu3DAnimAttrSet(anim, 1, 1);
    DataClose(data);
    length = Hu3DAnimData[(s16)anim].animIdx;
    animSlot[2] = length;
    animSlot[0] = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return length;
}

void msetup_HmfAnimSet(s16 model, s16 *animSlot, s16 anim) {
    HmfAnim *entry;

    if (*animSlot >= 0) {
        if (anim == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            entry = &Hu3DAnimData[*animSlot];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

s16 msetup_AnimDataRead(s32 dataId) {
    void *data;
    s32 anim;

    data = DataRead(dataId);
    anim = Hu3DAnimDataCreate(data);
    DataClose(data);
    return anim;
}

void msetup_WinProc(void) {
    s16 window;
    s16 state;

    window = HuWinExCreateStyled(250, 204, 8);
    HuWinActivePlayerSet(window, 1 << msetup_padNo);
    HuWinExTPLvlSet(window, 224);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    msetup_winId = msetup_winIdTbl[0] = window;
    window = HuWinExCreateStyled(250, 204, 18);
    HuWinActivePlayerSet(window, 1 << msetup_padNo);
    HuWinExTPLvlSet(window, 224);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    msetup_winIdTbl[1] = window;
    msetup_winMode = 0;
    state = 0;
    while (1) {
        if (state != msetup_winMode) {
            switch (msetup_winMode) {
                case 0:
                    HuWinExClose(msetup_winId, 1);
                    break;
                case 1:
                    window = msetup_winId;
                    msetup_winId = msetup_winIdTbl[0];
                    if (state != 0) {
                        HuWinExClose(window, 1);
                    }
                    HuWinHomeClear(msetup_winId);
                    HuWinExOpen(msetup_winId, 1);
                    break;
                case 2:
                    window = msetup_winId;
                    msetup_winId = msetup_winIdTbl[1];
                    if (state != 0) {
                        HuWinExClose(window, 1);
                    }
                    HuWinHomeClear(msetup_winId);
                    HuWinExOpen(msetup_winId, 1);
                    break;
            }
            state = msetup_winMode;
        }
        HuPrcVSleep();
    }
}

void msetup_WinMesSet(s32 message) {
    HuWinMesSet(msetup_winId, message, -1, -1);
}

s32 msetup_WinMesWait(void) {
    while (HuWinStatGet(msetup_winId) != 0) {
        HuPrcVSleep();
    }
    return winData[msetup_winId].num_choices == 0 ? 0 : HuWinChoiceGet(msetup_winId, 0, 0);
}

s32 msetup_WinMesWaitEx(void) {
    while (HuWinStatGet(msetup_winId) != 0) {
        HuPrcVSleep();
    }
    return winData[msetup_winId].num_choices == 0 ? 0 : HuWinChoiceGet(msetup_winId, 1, 0);
}

void msetup_WinInsertMesSet(u32 arg0, s8 arg1) {
    HuWinInsertMesSet(msetup_winId, arg0, arg1);
}

void msetup_WinHomeClear(void) {
    HuWinHomeClear(msetup_winId);
}

void msetup_WinAttrWait(s32 arg0, s32 arg1) {
    // wait for the given status bits of the menu window to be set
    while ((~HuWinAttrGet(msetup_winId) & arg0) == arg1) {
        HuPrcVSleep();
    }
}

void msetup_WinAttrSet(s32 arg0, s32 arg1) {
    HuWinAttrSet(msetup_winId, arg0, arg1);
}

s16 msetup_WinInputGet(void) {
    return (s16)winData[msetup_winId].input;
}

void msetup_PlayerProcCreateEx(s16 start, s16 end) {
    Vec *positions;
    f32 *values;
    s16 delay;
    s32 i;
    MsetupEntryAnim *entry;

    if (end != 2) {
        positions = msetup_playerPosTbl;
        values = msetup_playerRotTbl;
    } else {
        positions = msetup_duelPlayerPosTbl;
        values = msetup_duelPlayerRotTbl;
    }
    delay = msetup_playerAppearDelayTbl[msetup_setupMode];
    for (i = start; i < end; i++) {
        msetup_playerWorkTbl[i].state = 0;
        msetup_playerWorkTbl[i].index = i;
        msetup_playerWorkTbl[i].pos = positions[i];
        entry = &msetup_playerWorkTbl[i];
        msetup_playerWorkTbl[i].value = values[i];
        msetup_playerProcTbl[i] = omAddPrcObj(msetup_PlayerProc, 0x4000, 0xC00, 0);
        msetup_playerProcTbl[i]->user_data = entry;
        if (delay != 0) {
            HuPrcSleep(delay);
        }
    }
}

void msetup_PlayerProcCreate(s16 end) {
    msetup_PlayerProcCreateEx(0, end);
}

void msetup_PlayerProcKillEx(s16 start, s16 end) {
    s32 i;
    s32 last = end - 1;

    for (i = start; i < end; i++) {
        msetup_playerWorkTbl[i].state = 12;
    }
    while (msetup_playerWorkTbl[last].state != 0) {
        HuPrcVSleep();
    }
    for (i = start; i < end; i++) {
        msetup_playerWorkTbl[i].state = 2;
    }
    while (msetup_playerWorkTbl[last].state != 0) {
        HuPrcVSleep();
    }
    for (i = 30; i != 0; i--) {
        HuPrcVSleep();
    }
    for (i = start; i < end; i++) {
        msetup_playerWorkTbl[i].state = 18;
    }
    HuPrcVSleep();
    while (msetup_playerWorkTbl[last].state != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    for (i = start; i < end; i++) {
        omDelPrcObj(msetup_playerProcTbl[i]);
        msetup_playerProcTbl[i] = NULL;
    }
    HuPrcVSleep();
    HuPrcVSleep();
}

void msetup_PlayerProcKill(s16 end) {
    msetup_PlayerProcKillEx(0, end);
}

s16 msetup_PlayerStateSet(s16 arg0, s16 arg1) {
    s16 prevValue = msetup_playerWorkTbl[arg0].state;

    if (arg1 >= 0) {
        msetup_playerWorkTbl[arg0].state = arg1;
    }
    return prevValue;
}

void msetup_PlayerProc(void) {
    s16 offset[2];
    Vec2f projected;
    s16 sprites[4];
    s16 slots[4];
    s16 alpha[4];
    s16 alphaStep[4];
    s16 alphaTarget[4];
    s16 kill[4];
    s16 motions[4];
    s16 model;
    s16 shadow;
    s16 effect;
    s16 character;
    s16 specialMotion;
    s16 playing;
    s32 i;
    s32 dataId;
    MsetupEntryAnim *entry;
    Vec *pos;
    s16 state;
    s16 setupCharacter;
    s16 index;
    f32 scale;
    f32 scaleStep;

    i = 0;
    entry = HuPrcCurrentGet()->user_data;
    for (; i < 4; i++) {
        slots[i] = -1;
        sprites[i] = -1;
        alphaStep[i] = 0;
        alphaTarget[i] = 0;
        alpha[i] = 0;
        kill[i] = 0;
    }
    motions[0] = -1;
    motions[1] = -1;
    character = msetup_playerConfig.characters[entry->index];
    setupCharacter = character;
    model = Hu3DModelRead(msetup_chrMdlFileTbl[setupCharacter], 0x2A9);
    index = model;
    Hu3DMotionAttrSet(index, 2, 2);
    Hu3DModelAttrSet(index, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    pos = &entry->pos;
    Hu3DModelPosSet(index, entry->pos.x, entry->pos.y, entry->pos.z);
    Hu3DModelRotSet(index, 0.0f, entry->value, 0.0f);
    motions[3] = Hu3DData[index].motId;
    HuPrcVSleep();
    if (msetup_chrAnimAltTbl[setupCharacter] != 0) {
        CharAnimCreate(index, 1, setupCharacter, CharMotionDataNumGet(setupCharacter, 0xA4));
    } else {
        CharAnimCreate(index, 0, character, CharMotionDataNumGet(character, 0xA3));
    }
    Hu3DModelDynamicFree(index);
    HuPrcVSleep();
    if (msetup_shadowMdl < 0) {
        index = msetup_shadowMdl = Hu3DModelRead(9, 0x299);
    } else {
        index = Hu3DModelLink(msetup_shadowMdl);
    }
    shadow = index;
    Hu3DModelAttrSet(shadow, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(shadow, pos->x, 0.0f, pos->z);
    HuPrcVSleep();
    specialMotion = 0;
    if ((msetup_chrMotEnterAltMask >> msetup_setupMode) & 1) {
        specialMotion = 1;
        motions[0] = Hu3DMotionModelRead(msetup_chrMotEnterAltTbl[character]);
    } else {
        motions[0] = Hu3DMotionModelRead(msetup_chrMotEnterTbl[character]);
    }
    state = 0;
    HuPrcVSleep();
    motions[1] = Hu3DMotionModelRead(msetup_chrMotStartTbl[character]);
    HuPrcVSleep();
    effect = msetup_SpiralEffCreate(0x110012, 0x289);
    scale = 0.0f;
    scaleStep = 0.0f;
    playing = 0;
    do {
        HuPrcVSleep();
        if (state != entry->state) {
            state = entry->state;
        }
        switch (state) {
            case 0:
                break;
            case 1:
                for (i = 15; i != 0; i--) {
                    msetup_SpiralEffAdd(effect, pos->x, pos->y + 50.0f, pos->z);
                    HuPrcVSleep();
                }
                entry->state = 3;
                break;
            case 3:
                Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(shadow, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                if (motions[0] >= 0 && (!specialMotion || entry->index != 0)) {
                    Hu3DMotionModelSet(model, motions[0]);
                    playing = 1;
                }
                scale = 0.0f;
                scaleStep = 1.0f / 15.0f;
                for (i = 15; i != 0; i--) {
                    scale += scaleStep;
                    Hu3DModelScaleSet(model, scale, 1.0f, scale);
                    Hu3DModelScaleSet(shadow, scale, 1.0f, scale);
                    HuPrcVSleep();
                }
                entry->state = 0;
                break;
            case 2:
                scale = 1.0f;
                scaleStep = 1.0f / 7.0f;
                entry->state = 4;
                break;
            case 4:
                scale -= scaleStep;
                if (scale <= 0.0f) {
                    scale = 0.0f;
                    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(shadow, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    entry->state = 0;
                }
                Hu3DModelScaleSet(model, scale, 1.0f, scale);
                Hu3DModelScaleSet(shadow, scale, 1.0f, scale);
                msetup_SpiralEffAdd(effect, pos->x, pos->y + 50.0f, pos->z);
                break;
            case 11:
                for (i = 0; i < 4; i++) {
                    if (slots[i] >= 0) {
                        espDispOn(slots[i]);
                        alphaTarget[i] = msetup_playerIconTPLvlTbl[i];
                        alphaStep[i] = (u8)(msetup_playerIconTPLvlTbl[i] / 5U);
                    }
                }
                entry->state = 0;
                break;
            case 12:
                for (i = 0; i < 4; i++) {
                    alphaTarget[i] = 0;
                    alphaStep[i] = -alpha[i] / 5;
                }
                entry->state = 0;
                break;
            case 13:
                index = msetup_playerConfig.stars[entry->index];
                index--;
                if (index < 0) {
                    break;
                }
                dataId = msetup_duelHandicapIconTbl[index];
                i = 2;
                offset[0] = 28;
                offset[1] = -48;
                goto createSprite;
            case 15:
                kill[2] = 1;
            case 14:
                i = 2;
                goto hideSprite;
            case 5:
                dataId = msetup_comLevelIconTbl[msetup_playerConfig.cpuDifficulty[entry->index]];
                i = 0;
                offset[0] = 8;
                offset[1] = -6;
                goto createSprite;
            case 7:
                kill[0] = 1;
            case 6:
                i = 0;
                goto hideSprite;
            case 8:
                dataId = msetup_handicapIconTbl[msetup_playerConfig.stars[entry->index]];
                i = 1;
                offset[0] = 16;
                offset[1] = -30;
            createSprite:
                if (slots[(s16)i] >= 0) {
                    espKill(slots[(s16)i]);
                }
                if (sprites[(s16)i] >= 0) {
                    HuSprAnimKill(sprites[(s16)i]);
                }
                index = i;
                kill[index] = 0;
                sprites[index] = HuSprAnimDataRead(dataId);
                slots[index] = espEntry(sprites[index], 0, 1);
                espPriSet(slots[index], 1);
                Hu3DCam3Dto2D(0, pos, &projected);
                espPosSet(slots[index], (s16)(offset[0] + projected.x), (s16)(offset[1] + projected.y));
                espTPLvlSet(slots[index], 0);
                espDispOn(slots[index]);
                alphaTarget[index] = msetup_playerIconTPLvlTbl[index];
                alphaStep[index] = (u8)(msetup_playerIconTPLvlTbl[index] / 7U);
                entry->state = 0;
                break;
            case 10:
                kill[1] = 1;
            case 9:
                i = 1;
            hideSprite:
                alphaTarget[(s16)i] = 0;
                alphaStep[(s16)i] = -alpha[(s16)i] / 7;
                entry->state = 0;
                if (alpha[(s16)i] == 0 && kill[(s16)i] != 0) {
                    kill[(s16)i] = 0;
                    if (slots[(s16)i] >= 0) {
                        espKill(slots[(s16)i]);
                        slots[(s16)i] = -1;
                    }
                    if (sprites[(s16)i] >= 0) {
                        HuSprAnimKill(sprites[(s16)i]);
                        sprites[(s16)i] = -1;
                    }
                }
                break;
            case 16:
                if (motions[1] >= 0) {
                    Hu3DMotionModelSet(model, motions[1]);
                }
                entry->state = 0;
                break;
            case 17:
                if (motions[0] >= 0) {
                    Hu3DMotionShiftSet(model, Hu3DData[motions[0]].motId, 0, 6, 0);
                }
                entry->state = 0;
                playing = 1;
                break;
            case 18:
                state = -1;
                break;
        }
        if (playing && Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
            Hu3DMotionShiftSet(model, motions[3], 0, 30, 2);
            playing = 0;
        }
        for (i = 0; i < 4; i++) {
            if (slots[i] >= 0) {
                if (alphaStep[i] != 0) {
                    alpha[i] += alphaStep[i];
                    if (alphaStep[i] < 0) {
                        if (alpha[i] <= alphaTarget[i]) {
                            alpha[i] = alphaTarget[i];
                            alphaStep[i] = 0;
                        }
                    } else {
                        if (alpha[i] >= alphaTarget[i]) {
                            alpha[i] = alphaTarget[i];
                            alphaStep[i] = 0;
                        }
                    }
                    espTPLvlSet(slots[i], alpha[i]);
                    if (alpha[i] == 0) {
                        espDispOff(slots[i]);
                        if (kill[i] != 0) {
                            kill[i] = 0;
                            if (slots[i] >= 0) {
                                espKill(slots[i]);
                                slots[i] = -1;
                            }
                            if (sprites[i] >= 0) {
                                HuSprAnimKill(sprites[i]);
                                sprites[i] = -1;
                            }
                        }
                    }
                }
            }
        }
    } while (state >= 0);
    for (i = 0; i < 4; i++) {
        if (slots[i] >= 0) {
            espKill(slots[i]);
        }
        if (sprites[i] >= 0) {
            HuSprAnimKill(sprites[i]);
        }
    }
    if (CharAnimId[character][1] != 0xFF) {
        Hu3DAnimKill(CharAnimId[character][1]);
        Hu3DAnimKill(CharAnimSrc[character][1]);
        CharAnimId[character][1] = 0xFF;
    }
    Hu3DModelKill(model);
    Hu3DModelKill(shadow);
    if (msetup_shadowMdl == shadow) {
        msetup_shadowMdl = -1;
    }
    for (i = 0; i < 2; i++) {
        if (motions[i] >= 0) {
            Hu3DModelKill(motions[i]);
        }
    }
    Hu3DModelKill(effect);
    entry->state = 0;
    while (1) {
        HuPrcVSleep();
    }
}
