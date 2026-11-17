#include "game/overlays/minigame.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hu3d.h"
#include "game/hmfspr.h"
#include "variables.h"
#include "include_asm.h"
#include "game/util.h"

extern s32 omCharModelNoTbl[][6];
extern s32 mgCharAnimTbl[][7];
extern u16 mgHitSkipCnt;

s32 MgPlayerMotNoGet(omObjData *arg0) {
    MgPlayerWork *data = arg0->data;

    return data->unkD8.unk02 & 0x3FFF;
}

u32 MgPlayerMotStatGet(omObjData *arg0) {
    MgPlayerWork *data = arg0->data;
    u16 anim;
    s32 flag;

    if (data->unkD0 == 0xFFFF) {
        return MGPLAYER_MOTSTAT_DONE;
    }
    anim = MgPlayerMotNoGet(arg0);
    switch (anim) {
        case 0:
        case 11:
        case 24:
            flag = MGPLAYER_MOTSTAT_IDLE;
            break;
        case 16:
            flag = 0x20000;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            flag = MGPLAYER_MOTSTAT_WALK;
            break;
        case 25:
        case 27:
            flag = 8;
            break;
        case 26:
            flag = 0x10;
            break;
        case 6:
            flag = MGPLAYER_MOTSTAT_JUMP;
            break;
        case 20:
            flag = MGPLAYER_MOTSTAT_THROW;
            break;
        case 5:
            flag = MGPLAYER_MOTSTAT_PUNCH;
            break;
        case 7:
            flag = MGPLAYER_MOTSTAT_KICK;
            break;
        case 8:
            flag = MGPLAYER_MOTSTAT_HIPDROP;
            break;
        case 21:
            flag = 0x10000;
            break;
        case 18:
        case 19:
        case 28:
        case 30:
        case 31:
        case 33:
        case 34:
            flag = 0x8000;
            break;
        case 9:
        case 12:
        case 29:
            flag = MGPLAYER_MOTSTAT_KNOCKBACK_BACK;
            break;
        case 10:
        case 23:
            flag = MGPLAYER_MOTSTAT_KNOCKBACK_FRONT;
            break;
        case 13:
        case 14:
        case 15:
            flag = 0x1000;
            break;
        case 17:
            flag = 0x2000;
            break;
        case 32:
            flag = 0x4000;
            break;
        case 35:
            flag = 0x40000;
            break;
        case 36:
            flag = 0x80000;
            break;
        case 37:
            flag = 0x100000;
            break;
        default:
            if (anim >= 0x26) {
                flag = 0x200000;
            } else {
                flag = 0;
            }
            break;
    }
    data->unk5C = flag;
    return flag;
}

void MgEffMdlUpdate(s32 arg0) {
    f32 unk40;

    if (arg0 & 0xFF) {
        unk40 = Hu3DData[arg0 & 0xFF].motTime;
        if (Hu3DMotion[Hu3DData[arg0 & 0xFF].motId].unk02 <= unk40) {
            Hu3DModelAttrSet((u8)arg0, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}

void MgPlayerEffUpdate(omObjData *arg0) {
    s32 i;

    for (i = 3; i < 9 && i < arg0->mdlcnt; i++) {
        MgEffMdlUpdate((u8)arg0->model[i]);
    }
}

void MgPlayerEffSet(omObjData *arg0, u8 arg1, f32 x, f32 y, f32 z, f32 rotX, f32 rotY) {
    u8 model = arg0->model[arg1];
    f32 motTime;

    if (arg0->mdlcnt > arg1) {
        if (model != 0) {
            motTime = Hu3DData[model].motTime;
            if (Hu3DMotion[Hu3DData[model].motId].unk02 <= motTime) {
                if (Hu3DData[model].hmf->unk98 != NULL) {
                    Hu3DData[model].hmf->unk98->unk08 = 0;
                }
                Hu3DMotionTimeSet(model, 0.0f);
            }
            Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelPosSet(model, x, y, z);
            Hu3DModelRotSet(model, rotX, rotY, 0.0f);
        }
    }
}

void MgPlayerShapeApply(omObjData *arg0) {
    MgPlayerWork *data = arg0->data;
    s16 *motion = arg0->motion;
    s16 flag = (data->unkD8.unk00 & 1) ? 2 : 0;

    if (data->unkE8[22].unk00 & 4) {
        s16 anim = motion[22] & 0x3FFF;
        Hu3DMotionShapeSet(arg0->model[0], anim, flag);
    } else {
        s16 anim = Hu3DData[arg0->motion[22] & 0x3FFF].motId;
        Hu3DMotionShapeSet(arg0->model[0], anim, flag);
    }
}

void MgPlayerMotUpdate(omObjData *arg0) {
    s16 model = arg0->model[0];
    MgPlayerWork *data = arg0->data;
    MgMotReq *anim;
    MgMotAttr *entry;
    s32 chr;
    s16 shape;
    s16 motion;
    u16 shiftTime;
    f32 time;

    if (data->unkD6 != 0) {
        chr = GwPlayer[data->unk59].chr;
        shape = 0;
        if (data->unkD2 != 0) {
            anim = &data->unkD8;
            if (anim->unk00 & 4) {
                motion = arg0->motion[anim->unk02] & 0x3FFF;
                data->unkB8 = Hu3DMotionMotionMaxTimeGet(motion);
                shiftTime = data->unkB8 / 5.0f;
            } else {
                motion = Hu3DData[arg0->motion[anim->unk02] & 0x3FFF].motId;
                data->unkB8 = Hu3DMotion[Hu3DData[arg0->motion[anim->unk02] & 0x3FFF].motId].unk02;
                shiftTime = data->unkB8 / 5.0f;
            }
            if (anim->unk00 & 1) {
                shape = 2;
            }
            if (anim->unk06 >= 0) {
                CharAnimSet(data->unk5A, data->unk5B, chr, anim->unk06);
            }
            Hu3DMotionShiftSet(model, motion, 0, shiftTime, shape);
            Hu3DData[(u16)model].unk54 = anim->unk0C;
            if (data->unk50 & 0x100) {
                MgPlayerShapeApply(arg0);
            }
        }
        data->unkD6 = 0;
    } else {
        entry = &data->unkE8[(u16)MgPlayerMotNoGet(arg0)];
        if (entry->unk00 & 1) {
            return;
        }
        time = Hu3DMotionShiftTimeGet(model);
        if (time == -1.0f) {
            time = Hu3DData[(u16)model].motTime;
        }
        if (data->unkB8 <= time) {
            data->unkD0++;
            if (data->unkD2 <= data->unkD0) {
                data->unkD2 = 0;
                data->unkD0 = 0xFFFF;
            }
        }
    }
}

void MgPlayerScaleUpdate(omObjData *arg0) {
    MgPlayerWork *data = arg0->data;
    u16 start;
    u16 end;
    f32 scaleXZ;
    f32 scaleY;
    f32 t;
    s16 attr;
    u16 prevBE;

    if (data->unk50 & 7) {
        data->unkA8.u16 += 2;
        if (data->unk50 & 2) {
            start = 60;
            end = 106;
            scaleY = 0.6f;
            scaleXZ = data->unkAC * 1.4f;
        } else {
            start = 120;
            end = 166;
            scaleY = 0.1f;
            scaleXZ = data->unkAC * 1.6f;
            if (data->unkA8.u16 >= 120 && (data->unk50 & 1)) {
                data->unk50 = (data->unk50 & ~1) | 4;
            }
        }
        if (data->unkA8.u16 < end) {
            if (data->unkA8.u16 <= start) {
                arg0->scale.x = arg0->scale.z = scaleXZ;
                arg0->scale.y = scaleY;
            } else if (data->unkA8.u16 <= start + 10) {
                t = data->unkA8.u16 - start;
                arg0->scale.y = t * 0.05f + 0.2;
                arg0->scale.z = arg0->scale.x = 1.8 - t * 0.08f;
            } else if (data->unkA8.u16 <= start + 20) {
                t = data->unkA8.u16 - (start + 10);
                arg0->scale.y = 0.9 - t * 0.05f;
                arg0->scale.z = arg0->scale.x = t * 0.05f + 1.0;
            } else if (data->unkA8.u16 <= start + 30) {
                t = data->unkA8.u16 - (start + 20);
                arg0->scale.y = t * 0.05f + 0.7;
                arg0->scale.z = arg0->scale.x = 1.4 - t * 0.04f;
            } else if (data->unkA8.u16 <= start + 38) {
                t = data->unkA8.u16 - (start + 30);
                arg0->scale.y = 1.3 - t * 0.1f;
                arg0->scale.z = arg0->scale.x = t * 0.02f + 1.0;
            } else {
                t = data->unkA8.u16 - (start + 38);
                arg0->scale.y = t * 0.1f + 0.3;
                arg0->scale.z = arg0->scale.x = 1.1 - t * 0.01f;
            }
        } else {
            arg0->scale.x = arg0->scale.y = arg0->scale.z = 1.0f;
            data->unk50 &= ~7;
            data->unkA8.u16 = 0;
        }
    } else if (data->unk8C != 65536.0f) {
        if (data->unk38 == 1000.0f) {
            if (arg0->scale.y <= 0.5f) {
                MgPlayerSquashSet(arg0, 1);
            } else {
                arg0->scale.y = data->unkB0;
                arg0->scale.x = arg0->scale.z = (1.0f - data->unkB0) * 2 + 1.0f;
            }
        }
    } else {
        data->unkB0 = arg0->scale.x = arg0->scale.y = arg0->scale.z = 1.0f;
    }
    if (data->unkBE != 0) {
        prevBE = data->unkBE;
        data->unkBE = prevBE - 1;
        if (data->unkBE == 0) {
            if (mgHitSkipCnt != 0) {
                data->unkBE = prevBE;
            } else {
                data->unkC2 = 1;
            }
        }
        attr = (data->unkC2 & 1) ? 0 : HU3D_ATTR_DISPOFF;
        Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, attr);
        if (attr) {
            Hu3DMotionNext(&Hu3DData[arg0->model[0]], 2);
        }
        data->unkC2 = (data->unkC2 + 1) & 3;
    }
    MgPlayerEffUpdate(arg0);
}

void MgPlayerSquashSet(omObjData *arg0, u8 arg1) {
    MgPlayerWork *data = arg0->data;

    data->unk50 |= arg1;
    data->unkA8.u16 = 0;
}

void MgMotReqSet(MgMotReq *arg0, u16 arg1, u16 arg2, u16 arg3,
                            s16 arg4) {
    arg0->unk00 = arg1;
    arg0->unk02 = arg2;
    arg0->unk08 = 0;
    arg0->unk0C = arg3;
    arg0->unk06 = arg4;
}

s32 MgPlayerMotCheck(omObjData *arg0, u16 arg1) {
    MgPlayerWork *data = arg0->data;

    return data->unkD8.unk02 == arg1;
}

s32 MgPlayerWorkMotCheck(MgPlayerWork *arg0, u16 arg1) {
    return arg0->unkD8.unk02 == arg1;
}

s32 MgPlayerMotSet(omObjData *arg0, u16 arg1) {
    MgPlayerWork *data = arg0->data;
    MgMotAttr *entry;
    u16 unk00;
    u16 unk02;
    s16 unk04;

    if (data->unk52 != 0) {
        return 0;
    }
    entry = &data->unkE8[(u16)MgPlayerMotNoGet(arg0)];
    if (data->unkD0 != 0xFFFF) {
        if (entry->unk00 & 2) {
            return 0;
        }
        if (MgPlayerWorkMotCheck(data, arg1)) {
            return 0;
        }
    }
    entry = &data->unkE8[arg1];
    if ((u16)arg0->motion[arg1] == 0xFFFF) {
        return 0;
    }
    unk00 = entry->unk00;
    unk02 = entry->unk02;
    unk04 = entry->unk04;
    data->unkD0 = 0;
    data->unkD2 = 1;
    MgMotReqSet(&data->unkD8, unk00, arg1, unk02, unk04);
    data->unkD6 = 1;
    return 1;
}

s32 MgPlayerMotForceSet(omObjData *arg0, s32 arg1) {
    MgPlayerWork *data = arg0->data;
    MgMotAttr *entry;
    u16 unk00;
    u16 unk02;
    s16 unk04;

    if (data->unk52 != 0) {
        return 0;
    }
    entry = &data->unkE8[arg1 & 0xFFFF];
    if ((u16)arg0->motion[arg1 & 0xFFFF] != 0xFFFF) {
        unk00 = entry->unk00;
        unk02 = entry->unk02;
        unk04 = entry->unk04;
        data->unkD0 = 0;
        data->unkD2 = 1;
        MgMotReqSet(&data->unkD8, unk00, arg1, unk02, unk04);
        data->unkD6 = 1;
        return 1;
    }
    return 0;
}

s32 MgPlayerMotShapeStart(omObjData *arg0, u16 arg1, u16 arg2) {
    MgPlayerWork *data = arg0->data;

    if (MgPlayerMotForceSet(arg0, arg1) == 1) {
        MgPlayerMotSwap(arg0, 0x16, arg2);
        data->unk50 |= 0x100;
        return 1;
    }
    return 0;
}

void MgPlayerMotCopy(omObjData *arg0, s32 arg1, s32 arg2) {
    arg0->motion[arg2] = arg0->motion[arg1];
}

void MgPlayerMotAttrSet(omObjData *arg0, s32 arg1, s16 arg2, s16 arg3) {
    MgPlayerWork *temp_a1;
    MgMotAttr *temp_v0_2;

    temp_a1 = (MgPlayerWork *)arg0->data;
    temp_v0_2 = &temp_a1->unkE8[arg1];
    temp_v0_2->unk00 = arg2;
    temp_v0_2->unk02 = arg3;
}

void MgPlayerMotSwap(omObjData *arg0, s32 arg1, s32 arg2) {
    MgPlayerWork *temp_t2;
    MgMotAttr *temp_a3;
    MgMotAttr *temp_v1;
    s32 temp_t1;
    u16 temp_a0;
    u16 temp_a1;
    u16 temp_a2;

    temp_t2 = (MgPlayerWork *)arg0->data;
    temp_t1 = arg0->motion[arg1];
    arg0->motion[arg1] = arg0->motion[arg2];
    arg0->motion[arg2] = temp_t1;
    temp_a3 = &temp_t2->unkE8[arg1];
    temp_v1 = &temp_t2->unkE8[arg2];
    temp_a0 = temp_a3->unk02;
    temp_a1 = temp_a3->unk00;
    temp_a2 = temp_a3->unk04;
    temp_a3->unk02 = temp_v1->unk02;
    temp_a3->unk00 = temp_v1->unk00;
    temp_a3->unk04 = temp_v1->unk04;
    temp_v1->unk02 = temp_a0;
    temp_v1->unk00 = temp_a1;
    temp_v1->unk04 = temp_a2;
}

void MgPlayerMotRead(omObjData *arg0, u16 arg1, s32 arg2, u16 arg3, u16 arg4) {
    MgPlayerWork *data;
    MgMotAttr *entry;
    s16 modelId;

    modelId = Hu3DMotionModelRead(arg2);
    if (modelId < 0) {
        return;
    }
    data = arg0->data;
    arg0->motion[arg1] = modelId;
    entry = &data->unkE8[arg1];
    entry->unk00 = arg3;
    entry->unk02 = arg4;
}

void MgPlayerMotLoad(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, u16 arg4) {
    MgPlayerWork *temp_a1;
    MgMotAttr *temp_v0_2;
    s16 temp_v0;

    temp_v0 = Hu3DMotionCreate(DataRead(arg2), 0x18);
    if (temp_v0 < 0) {
        return;
    }
    temp_a1 = (MgPlayerWork *)arg0->data;
    arg0->motion[arg1] = temp_v0;
    temp_v0_2 = &temp_a1->unkE8[arg1];
    temp_v0_2->unk00 = arg3 | 4;
    temp_v0_2->unk02 = arg4;
}

s16 MgPlayerAnimGet(omObjData *arg0, s32 arg1) {
    MgPlayerWork *data = arg0->data;
    s32 i;

    for (i = 0; i < arg0->mtncnt; i++) {
        if (data->unkE8[i].unk08 == arg1) {
            return data->unkE8[i].unk04;
        }
    }
    return Hu3DAnimDataRead(arg1);
}

void MgPlayerMotReadEx(omObjData *arg0, u16 arg1, s32 arg2, u16 arg3, u16 arg4, s16 arg5) {
    MgPlayerWork *data;
    MgMotAttr *entry;
    s16 modelId;
    s32 chr;
    s32 unk08;

    modelId = Hu3DMotionModelRead(arg2);
    if (modelId < 0) {
        return;
    }
    data = arg0->data;
    arg0->motion[arg1] = modelId;
    entry = &data->unkE8[arg1];
    entry->unk00 = arg3;
    entry->unk02 = arg4;
    chr = GwPlayer[data->unk59].chr;
    unk08 = mgCharAnimTbl[chr][arg5] | omCharModelNoTbl[chr][0];
    entry->unk04 = MgPlayerAnimGet(arg0, unk08);
    entry->unk08 = unk08;
}

void MgPlayerMotLoadEx(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, u16 arg4, s16 arg5) {
    MgPlayerWork *data;
    MgMotAttr *entry;
    s16 modelId;
    s32 chr;
    s32 unk08;

    modelId = Hu3DMotionCreate(DataRead(arg2), 0x18);
    if (modelId < 0) {
        return;
    }
    data = arg0->data;
    arg0->motion[arg1] = modelId;
    entry = &data->unkE8[arg1];
    entry->unk00 = arg3 | 4;
    entry->unk02 = arg4;
    chr = GwPlayer[data->unk59].chr;
    unk08 = mgCharAnimTbl[chr][arg5] | omCharModelNoTbl[chr][0];
    entry->unk04 = MgPlayerAnimGet(arg0, unk08);
    entry->unk08 = unk08;
}
