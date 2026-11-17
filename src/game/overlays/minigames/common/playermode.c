#include "common.h"
#include "game/overlays/minigame.h"
#include "game/hmfcoll.h"
#include "game/hu3d.h"
#include "math.h"

extern u8 mgShadowAltF;
extern f32 mgPlayerSpeedMax;
extern f32 mgPlayerSpeedRun;
extern f32 mgPlayerSpeedWalk;
extern f32 mgPlayerSpeedMin;
extern f32 mgPlayerSpeedZero;

void MgPlayerJumpStart(omObjData *arg0, MgPlayerWork *arg1) {
    if (arg1->unk50 & 0x40) {
        if (arg1->unk38 == 1000.0f) {
            if (arg1->unk104[10] == NULL || arg1->unk104[10](arg0) != 1) {
                MgPlayerMotSet(arg0, 0x23);
            }
        }
    } else {
        MgPlayerJump(arg0, arg1);
    }
}

void MgPlayerActStart(omObjData *arg0, MgPlayerWork *arg1) {
    if (arg1->unk50 & 0x40) {
        if (arg1->unk38 == 1000.0f) {
            if (arg1->unk104[11] == NULL || arg1->unk104[11](arg0) != 1) {
                MgPlayerMotSet(arg0, 0x24);
            }
        }
    } else {
        MgPlayerAttack(arg0, arg1);
    }
}

void MgPlayerJump(omObjData *arg0, MgPlayerWork *arg1) {
    if (arg1->unk104[2] != NULL && arg1->unk104[2](arg0) == 1) {
        return;
    }
    if (arg1->unkB0 == 1.0f) {
        if (MgPlayerMotSet(arg0, 6) == 1) {
            arg1->unk38 = -mgPlayerJumpPower;
            arg1->unk50 &= ~0x80;
            MgPlayerSePlay(arg1, 3);
        }
    }
}

void MgPlayerLand(omObjData *arg0, MgPlayerWork *arg1, MgMapWork *arg2,
                            s16 arg3, s16 arg4) {
    if (arg1->unk104[3] != NULL && arg1->unk104[3](arg0, arg2) == 1) {
        return;
    }
    if (abs(arg3) < 8 && abs(arg4) < 8) {
        arg1->unk40 = mgPlayerSpeedZero;
        MgPlayerMotSet(arg0, 0x15);
        MgPlayerSePlay(arg1, 4);
        MgPlayerStickReset(arg0);
    } else {
        MgPlayerMotSet(arg0, 1);
        arg1->unk40 = mgPlayerSpeedRun;
        MgPlayerSePlay(arg1, 1);
    }
}

void MgPlayerHipDrop(omObjData *arg0, MgPlayerWork *arg1) {
    if (MgPlayerMotSet(arg0, 8) != 1) {
        return;
    }
    if (arg1->unk104[5] != NULL && arg1->unk104[5](arg0) == 1) {
        return;
    }
    arg1->unk40 = mgPlayerSpeedZero;
    arg1->unk38 = -mgPlayerJumpPower * 0.1f;
    if (arg1->unk50 & 0x10) {
        MgPlayerItemThrow(arg0, mgPlayerSpeedMin * 0.6f);
    }
    MgPlayerSePlay(arg1, 0xA);
}

void MgPlayerHipDropLand(omObjData *arg0, MgPlayerWork *arg1, MgMapWork *arg2,
                            f32 arg3, f32 arg4, f32 arg5) {
    if (arg1->unk104[6] != NULL && arg1->unk104[6](arg0, arg2) == 1) {
        return;
    }
    arg1->unk38 = -mgPlayerJumpPower * 0.6f;
    MgPlayerEffSet(arg0, 7, arg3, arg4, arg5, 0.0f, 0.0f);
    MgPlayerEffSet(arg0, 8, arg3, arg4, arg5, 0.0f, 0.0f);
    arg1->unk50 |= 0x80;
    MgPlayerSePlay(arg1, 0xB);
    omVibrate(arg1->unk59, 10, 0, 10);
}

void MgPlayerHipDropEnd(omObjData *arg0, MgPlayerWork *arg1, MgMapWork *arg2,
                            f32 arg3, f32 arg4, f32 arg5) {
    if (arg1->unk104[7] != NULL && arg1->unk104[7](arg0, arg2) == 1) {
        return;
    }
    MgPlayerMotSet(arg0, 0x12);
    MgPlayerEffSet(arg0, 8, arg3, arg4, arg5, 0.0f, 0.0f);
    arg1->unk50 &= ~0x80;
}

void MgPlayerAirAttack(omObjData *arg0, MgPlayerWork *arg1) {
    if (arg1->unk104[14] != NULL && arg1->unk104[14](arg0) == 1) {
        return;
    }
    if (arg1->unk50 & 0x10) {
        if (MgPlayerMotSet(arg0, 0x14) == 1) {
            arg1->unk38 = -mgPlayerJumpPower * 0.4f;
            MgPlayerItemShapeReset(arg0);
            MgPlayerSePlay(arg1, 0xC);
        }
    } else if (MgPlayerMotSet(arg0, 7) == 1) {
        arg1->unk38 = -mgPlayerJumpPower * 0.4f;
        MgPlayerSePlay(arg1, 6);
    }
}

void MgPlayerAirAttackUpdate(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3) {
    MgPlayerWork *data = arg0->data;

    if (data->unk104[15] != NULL && data->unk104[15](arg0) == 1) {
        return;
    }
    MgPlayerPunchHit(arg0, arg1, arg2, arg3);
}

void MgPlayerAttack(omObjData *arg0, MgPlayerWork *arg1) {
    if (arg1->unk104[8] != NULL && arg1->unk104[8](arg0) == 1) {
        return;
    }
    if (arg1->unk50 & 0x10) {
        if (MgPlayerMotSet(arg0, 0x14) == 1) {
            MgPlayerItemShapeReset(arg0);
            MgPlayerSePlay(arg1, 0xC);
        }
    } else if (MgPlayerMotSet(arg0, 5) == 1) {
        MgPlayerSePlay(arg1, 5);
    }
}

void MgPlayerAttackUpdate(omObjData *arg0, s32 motStat, f32 arg2, f32 arg3, f32 arg4) {
    MgPlayerWork *data = arg0->data;

    if (data->unk104[9] != NULL && data->unk104[9](arg0) == 1) {
        return;
    }
    if (motStat & MGPLAYER_MOTSTAT_THROW) {
        MgPlayerThrowRelease(arg0);
    } else {
        MgPlayerPunchHit(arg0, arg2, arg3, arg4);
    }
}

void MgPlayerPoundHit(omObjData *arg0, f32 x, f32 y, f32 z) {
    MgPlayerWork *data = arg0->data;
    MgPlayerWork *otherData;
    omObjData *other;
    f32 time;
    f32 dx, dy, dz;
    s32 i;

    if (data->unk104[12] != NULL && data->unk104[12](arg0, &x, &y, &z) == 1) {
        return;
    }
    Hu3DData[arg0->model[0]].motIdShape = 0xFF;
    time = Hu3DMotionShiftTimeGet(arg0->model[0]);
    if (time == -1.0f) {
        time = Hu3DData[arg0->model[0]].motTime;
    }
    if (time >= 30.0f && time <= 50.0f) {
        x += sindf(data->unk3C) * (data->unk6C + data->unk48);
        z += cosdf(data->unk3C) * (data->unk6C + data->unk48);
        for (i = 0; i < mgPlayerObjNum; i++) {
            other = mgPlayerObjTbl[i];
            otherData = other->data;
            if (data == otherData) {
                continue;
            }
            dx = other->trans.x - x;
            dy = other->trans.y - y;
            dz = other->trans.z - z;
            if (HuSqrtf(dx * dx + dy * dy + dz * dz) < otherData->unk48 + data->unk70) {
                MgPlayerSquashSet(other, 1);
                MgPlayerMotSet(other, 0);
                MgPlayerEffSet(arg0, 7, x, y, z, 0.0f, 0.0f);
            }
        }
    }
}

void MgPlayerSwingHit(omObjData *arg0, f32 x, f32 y, f32 z) {
    MgPlayerWork *data = arg0->data;
    MgPlayerWork *otherData;
    omObjData *other;
    f32 time;
    f32 angle;
    f32 dx, dy, dz;
    s32 i;

    if (data->unk104[13] != NULL && data->unk104[13](arg0, &x, &y, &z) == 1) {
        return;
    }
    Hu3DData[arg0->model[0]].motIdShape = 0xFF;
    time = Hu3DMotionShiftTimeGet(arg0->model[0]);
    if (time == -1.0f) {
        time = Hu3DData[arg0->model[0]].motTime;
    }
    if (time >= 10.0f && time <= 25.0f) {
        angle = data->unk3C - 90.0f + (time - 10.0f) * 12.0f;
        x += sindf(angle) * (data->unk6C + data->unk48);
        z += cosdf(angle) * (data->unk6C + data->unk48);
        for (i = 0; i < mgPlayerObjNum; i++) {
            other = mgPlayerObjTbl[i];
            otherData = other->data;
            if (data == otherData) {
                continue;
            }
            dx = other->trans.x - x;
            dy = other->trans.y - y;
            dz = other->trans.z - z;
            if (HuSqrtf(dx * dx + dy * dy + dz * dz) < otherData->unk48 + data->unk70) {
                MgPlayerMotSet(other, 0x25);
                otherData->unk40 = mgPlayerSpeedMax + mgPlayerSpeedMax;
                otherData->unk3C = HuAngleWrap(atan2df(dx, dz) + 90.0f);
                otherData->unkC0 = 90;
            }
        }
    }
}

s32 MgPlayerAttackCheck(omObjData *arg0, omObjData *arg1) {
    MgPlayerWork *temp_v0 = arg0->data;

    if (temp_v0->unk104[16] != NULL) {
        if (temp_v0->unk104[16](arg0, arg1) == 1) {
            return 0;
        }
    }
    return 1;
}

void MgPlayerHit(omObjData *arg0, omObjData *arg1, f32 x, f32 z, u16 arg4) {
    MgPlayerWork *data = arg0->data;
    MgPlayerWork *otherData = arg1->data;
    f32 dot;

    if (data->unk104[17] != NULL && data->unk104[17](arg0, arg1) == 1) {
        return;
    }
    if (!(otherData->unk50 & 0x200)) {
        dot = MgDirDot(sindf(otherData->unk3C), cosdf(otherData->unk3C), x, z);
        if (otherData->unk50 & 0x10) {
            MgPlayerItemThrow(arg1, mgPlayerSpeedWalk);
        }
        if (dot < 0.0f) {
            MgPlayerMotSet(arg1, 0x1E);
            if (otherData->unk38 == 1000.0f) {
                otherData->unk40 = -mgPlayerSpeedMax;
            } else {
                otherData->unk40 = -mgPlayerSpeedMax;
                otherData->unk38 = -mgPlayerJumpPower * 0.6f;
            }
            otherData->unk3C = HuAngleWrap(data->unk3C + 180.0f);
        } else {
            MgPlayerMotSet(arg1, 0x1F);
            if (otherData->unk38 == 1000.0f) {
                otherData->unk40 = mgPlayerSpeedMax;
            } else {
                otherData->unk40 = mgPlayerSpeedMax;
                otherData->unk38 = -mgPlayerJumpPower * 0.6f;
            }
            otherData->unk3C = data->unk3C;
        }
        MgPlayerEffSet(arg0, 6, arg1->trans.x, arg1->trans.y, arg1->trans.z, 0.0f, atan2df(x, z) + 180.0f);
        MgPlayerSePlay(data, 8);
        omVibrate(data->unk59, 2, 3, 10);
        omVibrate(otherData->unk59, 20, 0, 20);
    }
    data->unk53[1] = arg4;
    otherData->unkC3 = data->unk59;
}

void MgPlayerCeilHit(omObjData *arg0, f32 arg1) {
    MgPlayerWork *data = arg0->data;

    if (data->unk104[4] != NULL && data->unk104[4](arg0, &arg1) == 1) {
        return;
    }
    if (data->unk38 == 1000.0f) {
        data->unkB0 = (data->unk8C - arg1) / data->unk34;
    } else if (data->unk38 < 0.0f) {
        data->unk38 = mgPlayerJumpPower * 0.1f;
    }
}

void MgPlayerShadowSet(omObjData *arg0, f32 x, f32 y, f32 z, f32 groundY, Vec *normal) {
    MgPlayerWork *data = arg0->data;
    f32 scale;

    if (data->unk104[18] != NULL && data->unk104[18](arg0, &x, &y, &z, &groundY, normal) == 1) {
        return;
    }
    if (groundY != -65536.0f) {
        if (y != groundY) {
            if (mgShadowAltF == 1) {
                groundY += 2.0f;
            }
            Hu3DModelPosSet(arg0->model[1], x, groundY, z);
            groundY = y - groundY;
            if (groundY > 200.0f) {
                scale = 0.6f;
            } else {
                scale = 1.0 - fabs(groundY) / 500.0;
            }
            Hu3DModelScaleSet(arg0->model[1], scale, scale, scale);
        } else {
            if (mgShadowAltF == 1) {
                groundY += 2.0f;
            }
            Hu3DModelPosSet(arg0->model[1], x, groundY, z);
        }
        MgShadowSlopeSet(arg0->model[1], normal);
        Hu3DModelAttrSet(arg0->model[1], 4, 0);
    } else {
        Hu3DModelAttrSet(arg0->model[1], 4, 4);
    }
}
