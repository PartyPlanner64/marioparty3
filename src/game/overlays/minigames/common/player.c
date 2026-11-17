#include "game/overlays/minigame.h"
#include "types.h"
#include "gcc/memory.h"
#include "game/gamework_data.h"
#include "game/util.h"
#include "game/hu3d.h"
#include "game/hmfcoll.h"
#include "game/hmfdraw.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"
#include "game/hmfanim.h"
#include "game/audio.h"
#include "game/mallocblock.h"
#include "include_asm.h"
#include "game/pad.h"
#include "math.h"

s32 mgCharMdlTbl[] = {
    0x000200A3, 0x000300A3, 0x000700A3, 0x000400A3, 0x000500A3, 0x000600A3, 0x000800A3, 0x0009001A,
};

s32 mgCharAnimTbl[][7] = {
    { 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA },
    { 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA },
    { 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA },
    { 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA },
    { 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA },
    { 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA },
    { 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA },
    { 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA },
};

extern s32 mgFieldStatReq;
extern u8 mgMapBaseNo;
extern u8 mgShadowAltF;
extern u8 mgCharMdlF;
extern f32 mgPlayerAirStickDiv;
extern f32 mgPlayerTurnDiv;
extern f32 mgPlayerStickDiv;
extern f32 mgPlayerSpeedMax;
extern f32 mgPlayerSpeedRun;
extern f32 mgPlayerSpeedWalk;
extern f32 mgPlayerSpeedMin;
extern f32 mgPlayerSpeedZero;
extern f32 mgPlayerAirSpeedScale;
extern s16 mgPlayerSeNoTbl[];
extern s32 omCharModelNoTbl[][6];
extern u8 Hu3DBufNo;
extern s16 mgStickRotTimeTbl[];
extern u8 mgStickRotQuadTbl[];
extern s8 mgStickRotDirTbl[];
extern s8 mgStickRotWaitTbl[];
extern s16 mgStickRotLapTbl[];
extern u8 mgStickRotStartTbl[];

void MgCharMdlCreate(omObjData *arg0, u16 arg1, u16 player, s32 arg3, s32 arg4, f32 arg5) {
    s32 dataNum = mgCharMdlTbl[GwPlayer[player].chr];
    s16 anim;

    arg0->model[arg1] = Hu3DModelRead(arg3, arg4 & ~0x11);
    anim = CharAnimCreate(arg0->model[arg1], 0, GwPlayer[player].chr, dataNum);
    CharAnimSet(arg0->model[arg1], 0, GwPlayer[player].chr, anim);
}

void MgObjLODMdlCreate(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, f32 arg4) {
    s16 model = Hu3DModelRead(arg2, arg3);

    arg0->model[arg1] = model;
    Hu3DModelLODSet(arg0->model[0], model, arg4);
}

void MgPlayerDirSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk3C = HuAngleWrap(arg1);
}

void MgPlayerSpeedSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk40 = arg1;
}

void MgPlayerVelYSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk38 = arg1;
}

void MgPlayerResvSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk44 = arg1;
}

void MgMapFrictionSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk08 = arg1;
}

void MgMapAccelSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk0C = arg1;
}

void MgMapSlideSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk10 = arg1;
}

void MgPlayerRadiusSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk48 = arg1;
}

void MgPlayerHeightSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk34 = arg1;
}

void MgPlayerPunchRadiusSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk64 = arg1;
}

void MgPlayerAttackParamSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk68 = arg1;
}

void MgPlayerReachSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk6C = arg1;
}

void MgPlayerHitRadiusSet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk70 = arg1;
}

void MgMapAttrSet(omObjData *arg0, s32 arg1, f32 arg2) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unk06 = (arg1 & 0xFF) | temp_data->unk06;
    if (arg1 & 2) {
        temp_data->unk14 = arg2;
    }
}

void MgMapBoxSet(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    MgPlayerWork *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x8;
    temp_v0->unk14 = arg1;
    temp_v0->unkA0 = arg2;
    temp_v0->unkA4 = arg3;
    temp_v0->unkA8.f = arg4;
    temp_v0->unkAC = arg5;
}

void MgMapBlockSet(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    MgPlayerWork *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x10;
    temp_v0->unk14 = arg1;
    temp_v0->unk98 = arg2;
    temp_v0->unkA0 = arg3;
    temp_v0->unkA4 = arg4;
    temp_v0->unkA8.f = arg5;
    temp_v0->unkAC = arg6;
}

void MgMapCircleSet(omObjData *arg0, f32 arg1, f32 arg2) {
    MgPlayerWork *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x20;
    temp_v0->unk14 = arg1;
    temp_v0->unk9C = arg2;
}

void MgMapCylinderSet(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3) {
    MgPlayerWork *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x40;
    temp_v0->unk14 = arg1;
    temp_v0->unk98 = arg2;
    temp_v0->unk9C = arg3;
}

void MgMapMtxStaticOn(omObjData *arg0) {
    MgPlayerWork *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x80;
}

void MgMapMdlMtxOn(omObjData *arg0) {
    MgPlayerWork *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x100;
}

void MgMapNoBumpOn(omObjData *arg0) {
    MgPlayerWork *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x200;
}

void MgMapTiltOn(omObjData *arg0) {
    MgPlayerWork *temp_v0 = arg0->data;

    temp_v0->unk06 |= 0x400;
}

void MgMapBaseSet(s32 arg0) {
    mgMapBaseNo = arg0;
}

void MgPlayerMapAttrSet(omObjData *arg0, u8 arg1, s8 arg2) {
    MgPlayerWork *temp_v0 = arg0->data;

    temp_v0->unk00[arg1] = arg2;
}

void MgObjMdlDispSet(omObjData *arg0, s32 arg1, s32 arg2) {
    if (!(arg2 & 0xFF)) {
        Hu3DModelAttrSet(arg0->model[arg1 & 0xFF], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelAttrSet(arg0->model[arg1 & 0xFF], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

s32 MgMapBumpCheck(s8 arg0) {
    MgMapWork *data;
    s32 i;

    if (arg0 < 0) {
        return 0;
    }
    for (i = 0; i < mgMapObjNum; i++) {
        data = mgMapObjTbl[i]->data;
        if (data->unk04 == arg0) {
            if (data->unk06 & 0x200) {
                return 0;
            }
            break;
        }
    }
    return 1;
}

void MgObjSprMdlCreate(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3) {
    MgPlayerWork *temp_v0 = arg0->data;

    temp_v0->unk53[2] = SprModelRead(arg1, arg2, arg3);
    arg0->model[0] = Hu3DSprModelData[(u8)temp_v0->unk53[2]].modelId;
    Hu3DModelObjAttrSet(arg0->model[0], 0x70000000, 0x70000000);
}

void MgObjAnimMdlCreate(omObjData *arg0, u8 arg1, s32 arg2, s32 arg3, char *arg4, s32 arg5) {
    MgPlayerWork *data = arg0->data;
    u8 anim;
    HmfModel *model;

    arg0->model[arg1] = Hu3DModelRead3(arg2, arg5);
    model = &Hu3DData[arg0->model[arg1]];
    anim = Hu3DAnimRead(model->hmf, arg3, arg4);
    data->unk21[arg1] = anim;
    Hu3DModelRemakeStatic(arg0->model[arg1]);
    Hu3DAnimAttrSet(anim, 1, 1);
    Hu3DAnimAttrSet(anim, 2, 2);
    Hu3DModelScaleSet(arg0->model[arg1], 2.0f, 2.0f, 2.0f);
}

void MgObjSprCreate(omObjData *arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4) {
    MgPlayerWork *data = arg0->data;
    u16 sprite = SprModelRead(arg2, arg3, arg4);

    arg0->model[arg1] = Hu3DSprModelData[(u8)sprite].modelId;
    data->unk21[arg1] = sprite;
    Hu3DModelObjAttrSet(Hu3DSprModelData[(u8)sprite].modelId, 0x70000000, 0x70000000);
    Hu3DSprModelAttrSet((u8)sprite, 4, 4);
}

void MgObjPosSet(omObjData *arg0, f32 x, f32 y, f32 z) {
    arg0->trans.x = x;
    arg0->trans.y = y;
    arg0->trans.z = z;
}

void MgObjRotSet(omObjData *arg0, f32 x, f32 y, f32 z) {
    arg0->rot.x = x;
    arg0->rot.y = y;
    arg0->rot.z = z;
}

void MgObjScaleSet(omObjData *arg0, f32 x, f32 y, f32 z) {
    arg0->scale.x = x;
    arg0->scale.y = y;
    arg0->scale.z = z;
}

void MgFieldStatClear(void) {
    mgFieldStatReq = 0;
}

void MgFieldStatLand(void) {
    mgFieldStatReq = 2;
}

void MgFieldStatEnd(void) {
    mgFieldStatReq = 3;
}

void MgFieldStatStart(void) {
    mgFieldStatReq = 1;
}

void MgFieldStatUpdate(void) {
    mgFieldStat = mgFieldStatReq;
}

s32 MgMapObjNoGet(s32 arg0) {
    s32 i;

    for (i = 0; i < mgMapObjNum; i++) {
        /* Raw byte at 0x5F, inside omObjData's trailing data pointer field. */
        if (((u8 *)mgMapObjTbl[i])[0x5F] == arg0) {
            return i;
        }
    }
    return mgMapBaseNo;
}

void MgDummy(void) {
    s8 temp_s8;

    memset(&temp_s8, 0, sizeof(temp_s8));
}

void MgPlayerParamReset(void) {
    mgPlayerAccel = 15.0f;
    mgPlayerFriction = 0.5f;
    mgPlayerJumpPower = 1.45f;
    mgPlayerGravity = 0.15f;
    mgPlayerAirStickDiv = 7.0f;
    mgPlayerTurnDiv = 30.0f;
    mgPlayerAirSpeedScale = 0.5f;
    mgPlayerStickDiv = 3.3333333f;
    mgPlayerSpeedMax = 18.0f;
    mgPlayerSpeedRun = 13.5f;
    mgPlayerSpeedWalk = 9.0f;
    mgPlayerSpeedMin = 4.5f;
    mgPlayerSpeedZero = 0.0f;
    mgPlayerFallMax = 1.6f;
    mgPlayerFallInit = 0.14500001f;
    mgPlayerBounceF = 1;
    mgCharMdlF = 0;
}

void MgCharMdlSet(s32 arg0) {
    mgCharMdlF = arg0;
}

void MgShadowAltSet(s8 arg0) {
    mgShadowAltF = arg0;
}

void MgPlayerSePlay(MgPlayerWork *arg0, s32 arg1) {
    s16 sound = mgPlayerSeTbl[arg0->unk59][arg1];

    if (sound >= 0) {
        if (arg0->unkC4 != arg1) {
            arg0->unkC5 = HuAudPlayerFXPlay(sound, arg0->unk59);
            arg0->unkC4 = arg1;
            mgPlayerSeNoTbl[arg0->unk59] = sound;
        }
    } else {
        arg0->unkC4 = -1;
    }
}

void MgPlayerSeReq(MgPlayerWork *arg0, s32 arg1) {
    s16 sound = mgPlayerSeTbl[arg0->unk59][arg1];

    if (sound >= 0) {
        if (arg0->unkC4 != arg1) {
            arg0->unkC5 = HuAudPlayerFXPlay(sound, arg0->unk59);
            arg0->unkC4 = arg1;
            mgPlayerSeNoTbl[arg0->unk59] = sound;
        }
    } else {
        arg0->unkC4 = -1;
    }
}

void MgPlayerSeStopAll(void) {
    s32 i;

    for (i = 0; i < mgPlayerObjNum; i++) {
        HuAudFXStop(OM_GET_DATA_PTR(mgPlayerObjTbl[i], MgPlayerWork)->unkC5);
    }
}

void MgPlayerCreate(omObjData *arg0, u32 arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5) {
    MgPlayerWork *temp_s0;
    s32 var_a0;

    for (var_a0 = 0; var_a0 < arg0->mdlcnt; var_a0++) {
        arg0->model[var_a0] = 0;
    }
    arg0->data = HuMemAllocTag(sizeof(MgPlayerWork), TAG_OVERLAY);
    memset(arg0->data, 0, sizeof(MgPlayerWork));
    temp_s0 = arg0->data;
    temp_s0->unkE8 = HuMemAllocTag(arg0->mtncnt * sizeof(MgMotAttr), TAG_OVERLAY);
    if (mgCharMdlF == 1) {
        MgCharMdlCreate(arg0, 0, arg3, arg1 | arg2, arg4, 750.0f);
    } else {
        arg0->model[0] = Hu3DModelRead(arg1 | arg2, arg4);
    }
    arg0->model[1] = Hu3DModelRead3((mgShadowAltF != 0) ? 9 : 0, arg5);
    MgShadowMdlInit(arg0->model[1]);
    for (var_a0 = 0; var_a0 < arg0->mtncnt; var_a0++) {
        arg0->motion[var_a0] = -1;
    }
    for (var_a0 = 0; var_a0 < 21; var_a0++) {
        temp_s0->unk104[var_a0] = 0;
    }
    for (var_a0 = 0; var_a0 < arg0->mtncnt; var_a0++) {
        temp_s0->unkE8[var_a0].unk00 = 0;
        temp_s0->unkE8[var_a0].unk02 = 0;
        temp_s0->unkE8[var_a0].unk04 = -1;
        temp_s0->unkE8[var_a0].unk08 = -1;
    }
    temp_s0->unk57 = GwPlayer[arg3].pad;
    arg0->func = MgPlayerObjMain;
    temp_s0->unk52 = 0;
    temp_s0->unkB4 = 1.0f;
    temp_s0->unk8C = 65536.0f;
    temp_s0->unkD0 = 0xFFFF;
    temp_s0->unk4C = 0.5f;
    temp_s0->unkCC = 1.0f;
    temp_s0->unk60 = 0.0f;
    MgPlayerRadiusSet(arg0, 60.0f);
    MgPlayerHeightSet(arg0, 150.0f);
    MgPlayerPunchRadiusSet(arg0, 20.0f);
    MgPlayerAttackParamSet(arg0, 30.0f);
    MgPlayerReachSet(arg0, 50.0f);
    MgPlayerHitRadiusSet(arg0, 40.0f);
    MgPlayerVelYSet(arg0, 1000.0f);
    temp_s0->unk9C = temp_s0->unkA0 = temp_s0->unkA4 = 0.0f;
    temp_s0->unk59 = (s8)arg3;
    temp_s0->unkC3 = -1;
    temp_s0->unkC4 = -1;
    temp_s0->unkB0 = 1.0f;
    switch (arg1 >> 16) {
        case 6:
            temp_s0->unkAC = 0.7f;
            break;
        case 4:
            temp_s0->unkAC = 0.9f;
            break;
        case 5:
            temp_s0->unkAC = 0.8f;
            break;
        default:
            temp_s0->unkAC = 1.0f;
            break;
    }
    var_a0 = GwPlayer[arg3].chr + 1;
    mgPlayerSeTbl[temp_s0->unk59][0] = var_a0 + 0x1F;
    mgPlayerSeTbl[temp_s0->unk59][1] = var_a0 + 0x28;
    mgPlayerSeTbl[temp_s0->unk59][2] = var_a0 + 0x43;
    mgPlayerSeTbl[temp_s0->unk59][3] = var_a0 + 0x3A;
    mgPlayerSeTbl[temp_s0->unk59][4] = var_a0 + 0x31;
    mgPlayerSeTbl[temp_s0->unk59][5] = var_a0 + 0x4C;
    mgPlayerSeTbl[temp_s0->unk59][6] = var_a0 + 0x55;
    mgPlayerSeTbl[temp_s0->unk59][7] = var_a0 + 0x9D;
    mgPlayerSeTbl[temp_s0->unk59][8] = var_a0 + 0x94;
    mgPlayerSeTbl[temp_s0->unk59][9] = var_a0 + 0xA6;
    mgPlayerSeTbl[temp_s0->unk59][10] = var_a0 + 0x5E;
    mgPlayerSeTbl[temp_s0->unk59][11] = var_a0 + 0x67;
    mgPlayerSeTbl[temp_s0->unk59][12] = var_a0 + 0xAF;
    mgPlayerSeTbl[temp_s0->unk59][13] = var_a0 + 0xB8;
}

void MgPlayerCharAnimCreate(omObjData *arg0, s16 arg1, s16 arg2) {
    MgPlayerWork *temp_data = arg0->data;
    s32 chr;
    s32 model;

    temp_data->unk5A = arg1;
    temp_data->unk5B = arg2;
    chr = GwPlayer[temp_data->unk59].chr;
    model = omCharModelNoTbl[chr][0];
    CharAnimCreate(arg1, arg2, chr, model | CharMotionDataNumGetTbl(chr, arg2, 0));
}

void MgPlayerAnimRead(omObjData *arg0, s32 arg1, s32 arg2) {
    MgPlayerWork *temp_data = arg0->data;

    temp_data->unkF2[arg2] =
        Hu3DAnimDataRead(mgCharAnimTbl[GwPlayer[arg1].chr][arg2] | omCharModelNoTbl[GwPlayer[0].chr][0]);
}

s32 MgPlayerStickAvgGet(omObjData *arg0, s16 arg1, s16 arg2) {
    MgPlayerWork *temp_a3 = arg0->data;
    s32 value = (arg1 << 16) | (arg2 & 0xFFFF);
    s16 sumHi;
    s16 sumLo;
    u8 i;

    temp_a3->unk74[temp_a3->unk58++] = value;
    if (temp_a3->unk58 >= 6) {
        temp_a3->unk58 = 0;
    }
    sumLo = 0;
    sumHi = 0;
    for (i = 0; i < 6; i++) {
        sumHi += temp_a3->unk74[i] >> 16;
        sumLo += temp_a3->unk74[i] & 0xFFFF;
    }
    sumHi /= 6;
    sumLo /= 6;
    value = (sumHi << 16) | (sumLo & 0xFFFF);
    return value;
}

void MgStickClamp(s16 *arg0, s16 *arg1) {
    Vec vec;
    f32 x = *arg0;
    f32 z = *arg1;

    if (HuSqrtf(x * x + z * z) > 60.0f) {
        vec.x = x;
        vec.y = 0.0f;
        vec.z = z;
        MapVecNormalize(&vec);
        *arg0 = vec.x * 60.0f;
        *arg1 = vec.z * 60.0f;
    }
}

void MgPlayerStickReset(omObjData *arg0) {
    MgPlayerWork *temp_v0 = arg0->data;
    s32 var_a0;

    for (var_a0 = 0; var_a0 < 6; var_a0++) {
        temp_v0->unk74[var_a0] = 0;
    }
}

s16 MgStickRotGet(s16 idx, s16 arg1, s8 x, s8 y) {
    s16 mult = 1;
    s16 angle;
    s16 diff;
    s16 dir;

    if (x == 0 && y == 0) {
        return 0;
    }
    angle = atan2df(y, x);
    if (angle < 0) {
        angle += 360;
    }
    angle /= 90;
    if (angle == mgStickRotQuadTbl[idx]) {
        if (++mgStickRotWaitTbl[idx] > arg1) {
            mgStickRotWaitTbl[idx] = arg1;
            mgStickRotDirTbl[idx] = 0;
            mgStickRotStartTbl[idx] = angle;
            mgStickRotTimeTbl[idx] = 0;
            return 0;
        }
        mgStickRotTimeTbl[idx]++;
        return mgStickRotDirTbl[idx];
    }
    mgStickRotTimeTbl[idx]++;
    mgStickRotWaitTbl[idx] = 0;
    if (mgStickRotStartTbl[idx] == angle) {
        mult = 2;
        mgStickRotLapTbl[idx] = mgStickRotTimeTbl[idx];
        mgStickRotTimeTbl[idx] = 0;
    }
    diff = angle - mgStickRotQuadTbl[idx];
    if (diff >= 0 ? diff == 3 : -diff == 3) {
        diff = -diff;
    }
    dir = (diff < 0) ? -1 : 1;
    if (dir != 0 && dir != mgStickRotDirTbl[idx]) {
        mgStickRotDirTbl[idx] = dir;
        mgStickRotQuadTbl[idx] = angle;
        mgStickRotWaitTbl[idx] = 0;
        mgStickRotStartTbl[idx] = angle;
        mgStickRotTimeTbl[idx] = 0;
        return 0;
    }
    mgStickRotTimeTbl[idx]++;
    if (((mgStickRotQuadTbl[idx] + mgStickRotDirTbl[idx]) & 3) == angle) {
        mgStickRotQuadTbl[idx] = angle;
        return mgStickRotDirTbl[idx] * mult;
    }
    mgStickRotDirTbl[idx] = dir;
    mgStickRotQuadTbl[idx] = angle;
    mgStickRotWaitTbl[idx] = 0;
    mgStickRotTimeTbl[idx] = 0;
    return 0;
}

void MgMapMtxUpdate(omObjData *obj) {
    s32 model = obj->model[0];
    MgMapWork *data = obj->data;

    if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f) {
        HuTranslateF(data->unk18, obj->trans.x, obj->trans.y, obj->trans.z);
    } else {
        HuMtxIdentF(data->unk18);
    }
    if (obj->rot.x != 0.0f || obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
        mtxRotCat(data->unk18, obj->rot.x, obj->rot.y, obj->rot.z);
    }
    if (data->unk06 & 0x100) {
        guMtxCatF(Hu3DData[model].mtx, data->unk18, data->unk18);
    }
    mtxInverse(data->unk18, data->unk58);
}

void MgMapPosLocalGet(HuMtx4F mtx, HuMtx4F result, Vec *pos, omObjData *obj) {
    MgMapWork *data = obj->data;
    s32 model = obj->model[0];
    f32 rotX = obj->rot.x;
    f32 rotY = obj->rot.y;
    f32 rotZ = obj->rot.z;
    f32 transX = obj->trans.x;
    f32 transY = obj->trans.y;
    f32 transZ = obj->trans.z;
    f32 x = pos->x;
    f32 y = pos->y;
    f32 z = pos->z;

    if (data->unk06 & 0x80) {
        mtxCopy(mtx, data->unk18);
        mtxCopy(result, data->unk58);
    } else {
        if (transX != 0.0f || transY != 0.0f || transZ != 0.0f) {
            HuTranslateF(mtx, transX, transY, transZ);
        } else {
            HuMtxIdentF(mtx);
        }
        if (rotX != 0.0f || rotY != 0.0f || rotZ != 0.0f) {
            mtxRotCat(mtx, rotX, rotY, rotZ);
        }
        if (data->unk06 & 0x100) {
            guMtxCatF(Hu3DData[model].mtx, mtx, mtx);
        }
        mtxInverse(mtx, result);
    }
    pos->x = x * result[0][0] + y * result[1][0] + z * result[2][0] + result[3][0];
    pos->y = x * result[0][1] + y * result[1][1] + z * result[2][1] + result[3][1];
    pos->z = x * result[0][2] + y * result[1][2] + z * result[2][2] + result[3][2];
}

void MgMtxDirMult(HuMtx4F mtx, Vec *arg1) {
    f32 x = arg1->x;
    f32 y = arg1->y;
    f32 z = arg1->z;

    arg1->x = x * mtx[0][0] + y * mtx[1][0] + z * mtx[2][0];
    arg1->y = x * mtx[0][1] + y * mtx[1][1] + z * mtx[2][1];
    arg1->z = x * mtx[0][2] + y * mtx[1][2] + z * mtx[2][2];
}

void MgMtxPosMult(HuMtx4F mtx, Vec *arg1) {
    f32 x = arg1->x;
    f32 y = arg1->y;
    f32 z = arg1->z;

    arg1->x = x * mtx[0][0] + y * mtx[1][0] + z * mtx[2][0] + mtx[3][0];
    arg1->y = x * mtx[0][1] + y * mtx[1][1] + z * mtx[2][1] + mtx[3][1];
    arg1->z = x * mtx[0][2] + y * mtx[1][2] + z * mtx[2][2] + mtx[3][2];
}

void MgMtxPosYMult(HuMtx4F mtx, Vec *arg1) {
    f32 x = arg1->x;
    f32 y = arg1->y;
    f32 z = arg1->z;

    arg1->y = x * mtx[0][1] + y * mtx[1][1] + z * mtx[2][1] + mtx[3][1];
}

void MgPlayerItemThrow(omObjData *arg0, f32 arg1) {
    MgPlayerWork *data = arg0->data;
    omObjData *item;
    MgItemWork *itemData;

    if (data->unk50 & 0x10) {
        item = data->unkC8;
        itemData = item->data;
        if (data->unk104[19] != NULL && data->unk104[19](arg0, item) == 1) {
            return;
        }
        data->unk50 &= ~0x150;
        itemData->unk50 &= ~0x10;
        Hu3DModelAttrSet(item->model[0], HU3D_ATTR_HOOK, HU3D_ATTR_NONE);
        Hu3DData[arg0->model[0]].motIdShape = 0xFF;
        if (item->model[1] != 0) {
            Hu3DModelAttrSet(item->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        MgItemRelease(arg0, item);
        data->unkC8 = NULL;
        data->unkB4 = 1.0f;
    }
}

s32 MgPlayerItemHold(omObjData *arg0, omObjData *item) {
    MgPlayerWork *data = arg0->data;
    MgItemWork *itemData = item->data;

    if (!(itemData->unk50 & 0x20)) {
        return 0;
    }
    if (itemData->unk50 & 0x10) {
        return 0;
    }
    if (data->unk50 & 0x10) {
        return 0;
    }
    data->unk50 |= 0x110;
    itemData->unk50 |= 0x10;
    if (itemData->unk50 & 0x40) {
        data->unk50 |= 0x40;
    }
    data->unkC8 = item;
    itemData->unk80 = arg0;
    Hu3DModelHookSet(item->model[0], arg0->model[0], "item_hook");
    Hu3DModelAttrSet(item->model[0], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
    data->unkB4 = itemData->unk74;
    if (item->model[1] != 0) {
        Hu3DModelAttrSet(item->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    return 1;
}

void MgPlayerItemShapeReset(omObjData *arg0) {
    MgPlayerWork *temp_v0 = arg0->data;

    Hu3DData[arg0->model[0]].motIdShape = 0xFF;
    temp_v0->unk50 &= 0xFEFF;
}

f32 MgDirDot(f32 x1, f32 z1, f32 x2, f32 z2) {
    Vec a;
    Vec b;

    a.x = x1;
    a.y = 0.0f;
    a.z = z1;
    MapVecNormalize(&a);
    b.x = x2;
    b.y = 0.0f;
    b.z = z2;
    MapVecNormalize(&b);
    return HuVecDot3F(&b, &a);
}

s32 MgBoundsCheck(HmfModelData_Unk64_Unk60_Struct *obj, Vec *pos) {
    f32 minX = obj->boundsMin[0];
    f32 minZ = obj->boundsMin[2];
    f32 maxX = obj->boundsMax[0];
    f32 maxZ = obj->boundsMax[2];

    return minX <= pos->x && minZ <= pos->z && pos->x <= maxX && pos->z <= maxZ;
}

s32 MgBoundsMarginCheck(HmfModelData_Unk64_Unk60_Struct *obj, Vec *pos, f32 margin) {
    f32 x;
    f32 z;
    f32 minX;
    f32 maxX;
    f32 maxZ;
    f32 minZ;

    x = pos->x;
    z = pos->z;
    minX = obj->boundsMin[0] - margin;
    minZ = obj->boundsMin[2] - margin;
    maxX = obj->boundsMax[0] + margin;
    maxZ = obj->boundsMax[2] + margin;
    if (minX <= x && minZ <= z && x <= maxX && z <= maxZ) {
        return 1;
    }
    return 0;
}

s32 MgMapAreaCheck(Vec *pos, MgMapWork *data) {
    f32 x;
    f32 z;

    if (!(data->unk06 & 0x50)) {
        return 1;
    }
    x = pos->x;
    z = pos->z;
    if (data->unk06 & 0x10) {
        if (data->unkA0 <= x && x <= data->unkA8 && data->unkA4 <= z && z <= data->unkAC) {
            return 1;
        }
    } else if (HuSqrtf(x * x + z * z) <= data->unk9C) {
        return 1;
    }
    return 0;
}

void MgPlayerBounce(omObjData *arg0, f32 x, f32 z) {
    MgPlayerWork *data = arg0->data;
    s16 stickX;
    s16 stickY;
    s32 avg;

    if (data->unk5C & 0x200) {
        data->unk4C = 0.7f;
    } else {
        data->unk4C = 0.6f;
    }
    MgPlayerMotSet(arg0, 6);
    if (abs(HuPadStkX[data->unk57]) >= 9 || abs(HuPadStkY[data->unk57]) >= 9) {
        stickX = HuPadStkX[data->unk57];
        stickY = HuPadStkY[data->unk57];
        if (stickX > 60) {
            stickX = 60;
        }
        if (stickY > 60) {
            stickY = 60;
        }
        if (stickX < -60) {
            stickX = -60;
        }
        if (stickY < -60) {
            stickY = -60;
        }
        MgStickClamp(&stickX, &stickY);
        MgPlayerStickAvgGet(arg0, stickX, stickY);
        MgPlayerStickAvgGet(arg0, stickX, stickY);
        MgPlayerStickAvgGet(arg0, stickX, stickY);
        MgPlayerStickAvgGet(arg0, stickX, stickY);
        MgPlayerStickAvgGet(arg0, stickX, stickY);
        avg = MgPlayerStickAvgGet(arg0, stickX, stickY);
        stickX = avg >> 16;
        stickY = avg;
        data->unk3C = atan2df(stickX, -stickY) + data->unk60;
        data->unk40 = mgPlayerSpeedMax;
    } else if (MgDirDot(sindf(data->unk3C), cosdf(data->unk3C), x, z) < 0.0f) {
        data->unk40 = mgPlayerSpeedMax;
    } else {
        data->unk40 = -mgPlayerSpeedMax;
    }
    data->unk38 = -mgPlayerJumpPower * 0.9f;
    data->unk50 |= 8;
}

void MgPlayerRepel(MgPlayerWork *arg0, f32 x, f32 z) {
    if (0.0f <= MgDirDot(sindf(arg0->unk3C), cosdf(arg0->unk3C), x, z)) {
        arg0->unk40 = mgPlayerSpeedRun;
    } else {
        arg0->unk40 = -mgPlayerSpeedRun;
    }
    arg0->unk50 |= 8;
    MgPlayerSePlay(arg0, 7);
}

void MgPlayerRepelPair(omObjData *arg0, omObjData *arg1) {
    MgPlayerWork *data1 = arg1->data;

    MgPlayerRepel(arg0->data, arg0->trans.x - arg1->trans.x, arg0->trans.z - arg1->trans.z);
    MgPlayerRepel(data1, arg1->trans.x - arg0->trans.x, arg1->trans.z - arg0->trans.z);
}

void MgPlayerHookSet(MgPlayerWork *arg0, s32 index, s32 (*func)()) {
    if (index < 21) {
        arg0->unk104[index] = func;
    }
}

void MgShadowMdlInit(s16 model) {
    HmfData *hmf;
    s16 i;

    Hu3DModelVtxBufMake(model);
    hmf = Hu3DData[model].hmf;
    for (i = 0; i < Hu3DBufNum; i++) {
        bcopy(hmf->unk40, hmf->unk44[i], hmf->unk18 * sizeof(Vtx));
    }
}

void MgShadowSlopeSet(s16 model, Vec *normal) {
    HmfModel *hmfModel = &Hu3DData[model];
    HmfData *hmf = hmfModel->hmf;
    Vtx *vtx = hmf->unk44[Hu3DBufNo];
    Vtx *src = hmf->unk40;
    f32 dist;
    f32 x;
    f32 y;
    f32 z;
    f32 scale;
    Vec unused;
    s16 i;

    dist = normal->x * hmfModel->pos.x + normal->y * hmfModel->pos.y + normal->z * hmfModel->pos.z;
    for (i = 0; i < hmfModel->hmf->unk18; vtx++, i++, src++) {
        x = vtx->v.ob[0] + hmfModel->pos.x;
        z = vtx->v.ob[2] + hmfModel->pos.z;
        y = dist - x * normal->x - z * normal->z;
        y /= normal->y;
        vtx->v.ob[1] = y - hmfModel->pos.y + 0.5f;
        x = src->v.ob[0];
        y = vtx->v.ob[1];
        z = src->v.ob[2];
        scale = (f32)(src->v.ob[0] * src->v.ob[0] + vtx->v.ob[2] * vtx->v.ob[2]) / (x * x + y * y + z * z);
        vtx->v.ob[0] = x * scale;
        vtx->v.ob[1] = vtx->v.ob[1] * scale;
        vtx->v.ob[2] = src->v.ob[2] * scale;
    }
}
