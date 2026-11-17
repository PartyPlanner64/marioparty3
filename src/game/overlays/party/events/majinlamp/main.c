#include "common_board.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/vec.h"
#include "game/overlays/party/common/move.h"
#include "game/overlays/party/common/player.h"

void MBDlgResultWinExec(s32);
void MBDlgWinExecY(s16, s32, s32);
void *memcpy(void *, const void *, unsigned int);
void majinlamp_LampBoardExec(void);
void majinlamp_TunnelFlyExec(void);
void majinlamp_ExitObjMain(omObjData *arg0);
void majinlamp_MainProc(void);
void majinlamp_ExitCheckObjMain(omObjData *arg0);
void majinlamp_SysInit(void);
void majinlamp_SysClose(void);
void majinlamp_CameraInit(void);
void majinlamp_CameraClose(void);
void majinlamp_PosMoveObjMain(omObjData *arg0);
void majinlamp_ArcMoveObjMain(omObjData *arg0);
void majinlamp_RotMoveObjMain(omObjData *arg0);

f32 majinlamp_cam0Fov = 20.0f;
f32 majinlamp_cam0Near = 200.0f;
f32 majinlamp_cam0Far = 10000.0f;
f32 majinlamp_cam1Fov = 20.0f;
f32 majinlamp_cam1Near = 200.0f;
f32 majinlamp_cam1Far = 10000.0f;
s16 majinlamp_playerRideF = 0;
s16 majinlamp_playerTiltF = 0;
s16 majinlamp_lampBobF = 1;
f32 majinlamp_rideOfsY = 0.0f;

Vec majinlamp_flyPosTbl[] = {
    { 0.0f, 0.0f, -2000.0f },
    { -100.0f, -100.0f, 2000.0f },
    { 0.0f, -50.0f, 4500.0f },
};

Vec majinlamp_flyExitPos = { -500.0f, 500.0f, 5500.0f };
s32 majinlamp_bgOutScrollF = 1;

Process *majinlamp_cameraProc BSS;
Vec majinlamp_cam0Pos BSS;
Vec majinlamp_cam0Target BSS;
Vec majinlamp_cam0Up BSS;
Vec majinlamp_cam1Pos BSS;
Vec majinlamp_cam1Target BSS;
Vec majinlamp_cam1Up BSS;
Object *majinlamp_lampMdl BSS;
Object *majinlamp_tunnelMdl BSS;
GW_PLAYER *majinlamp_gwPlayer BSS;
s16 majinlamp_screenSprGrp BSS;
s16 majinlamp_screenSpr BSS;
s32 majinlamp_playerNo BSS;
s16 majinlamp_playerAnimTbl[2] BSS;
u8 majinlamp_playerAnimPad[0xC] BSS; /* Unreferenced. */
omObjData *majinlamp_moveObjTbl[32] BSS;

extern const char majinlamp_bgInStr[];
extern const char majinlamp_bgOutStr[];
extern const s32 majinlamp_playerRideAnimTbl[];
extern const s32 majinlamp_playerCheerAnimTbl[];
extern const Vec majinlamp_jumpPos;
extern const Vec majinlamp_lookPos;
extern const Vec majinlamp_flyAwayPos;
extern const Vec majinlamp_flyAwayArc;

void majinlamp_ObjectSetup(void) {
    majinlamp_playerNo = GwSystem.current_player_index;
    omInitObjMan(0x50, 0x50);
    majinlamp_CameraInit();
    majinlamp_SysInit();
    HuWinInit();
    omAddPrcObj(majinlamp_MainProc, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, majinlamp_ExitCheckObjMain);
}

void majinlamp_MoveObjInit(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        majinlamp_moveObjTbl[i] = NULL;
    }
}

void majinlamp_MoveObjKillAll(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (majinlamp_moveObjTbl[i] != NULL) {
            if (majinlamp_moveObjTbl[i]->func == majinlamp_PosMoveObjMain ||
                majinlamp_moveObjTbl[i]->func == majinlamp_ArcMoveObjMain ||
                majinlamp_moveObjTbl[i]->func == majinlamp_RotMoveObjMain) {
                if (majinlamp_moveObjTbl[i]->stat & 4) {
                    majinlamp_moveObjTbl[i]->data = NULL;
                    omDelObj(majinlamp_moveObjTbl[i]);
                }
            }
        }
    }
}

void majinlamp_PosMoveObjMain(omObjData *arg0) {
    Object *temp_v1;

    temp_v1 = arg0->data;
    arg0->work[1]--;
    if (temp_v1 == NULL) {
        if (arg0->work[1] == 0) {
            GwPlayer[arg0->work[0]].player_obj->coords.x = arg0->trans.x;
            GwPlayer[arg0->work[0]].player_obj->coords.y = arg0->trans.y;
            GwPlayer[arg0->work[0]].player_obj->coords.z = arg0->trans.z;
            omDelObj(arg0);
        } else {
            GwPlayer[arg0->work[0]].player_obj->coords.x += arg0->scale.x;
            GwPlayer[arg0->work[0]].player_obj->coords.y += arg0->scale.y;
            GwPlayer[arg0->work[0]].player_obj->coords.z += arg0->scale.z;
        }
    } else if (arg0->work[1] == 0) {
        temp_v1->coords.x = arg0->trans.x;
        temp_v1->coords.y = arg0->trans.y;
        temp_v1->coords.z = arg0->trans.z;
        arg0->data = NULL;
        omDelObj(arg0);
    } else {
        temp_v1->coords.x += arg0->scale.x;
        temp_v1->coords.y += arg0->scale.y;
        temp_v1->coords.z += arg0->scale.z;
    }
}

omObjData *majinlamp_PosMoveCreate(s32 arg0, Vec *arg1, s32 arg2, Object *arg3) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x1000, 0, 0, -1, majinlamp_PosMoveObjMain);
    obj->work[0] = arg0;
    obj->work[1] = arg2;
    obj->trans.x = arg1->x;
    obj->trans.y = arg1->y;
    obj->trans.z = arg1->z;

    if (arg3 == NULL) {
        obj->scale.x = (arg1->x - GwPlayer[arg0].player_obj->coords.x) / arg2;
        obj->scale.y = (arg1->y - GwPlayer[arg0].player_obj->coords.y) / arg2;
        obj->scale.z = (arg1->z - GwPlayer[arg0].player_obj->coords.z) / arg2;
    } else {
        obj->scale.x = (arg1->x - arg3->coords.x) / arg2;
        obj->scale.y = (arg1->y - arg3->coords.y) / arg2;
        obj->scale.z = (arg1->z - arg3->coords.z) / arg2;
    }

    obj->data = arg3;
    for (i = 0; i < 32; i++) {
        if (majinlamp_moveObjTbl[i] == NULL) {
            majinlamp_moveObjTbl[i] = obj;
            break;
        }
    }
    return obj;
}

void majinlamp_ArcMoveObjMain(omObjData *arg0) {
    Object *temp_v1;
    Object *temp_v0;
    f32 temp_f20;

    temp_v1 = arg0->data;
    arg0->work[1]--;
    if (temp_v1 == NULL) {
        if (arg0->work[1] == 0) {
            GwPlayer[arg0->work[0]].player_obj->coords.x = arg0->trans.x;
            GwPlayer[arg0->work[0]].player_obj->coords.y = arg0->trans.y;
            GwPlayer[arg0->work[0]].player_obj->coords.z = arg0->trans.z;
            omDelObj(arg0);
            return;
        } else {
            GwPlayer[arg0->work[0]].player_obj->coords.x += arg0->scale.x;
            GwPlayer[arg0->work[0]].player_obj->coords.y += arg0->scale.y;
            GwPlayer[arg0->work[0]].player_obj->coords.z += arg0->scale.z;
            temp_v1 = GwPlayer[arg0->work[0]].player_obj;
            temp_v0 = temp_v1;
            temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.x;
            temp_v1->coords.x = temp_v0->coords.x + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.x));
            temp_v1 = GwPlayer[arg0->work[0]].player_obj;
            temp_v0 = temp_v1;
            temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.y;
            temp_v1->coords.y = temp_v0->coords.y + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.y));
            temp_v1 = GwPlayer[arg0->work[0]].player_obj;
            temp_v0 = temp_v1;
            temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.z;
            temp_v1->coords.z = temp_v0->coords.z + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.z));
        }
    } else if (arg0->work[1] == 0) {
        temp_v1->coords.x = arg0->trans.x;
        temp_v1->coords.y = arg0->trans.y;
        temp_v1->coords.z = arg0->trans.z;
        arg0->data = NULL;
        omDelObj(arg0);
        return;
    } else {
        temp_v1->coords.x += arg0->scale.x;
        temp_v1->coords.y += arg0->scale.y;
        temp_v1->coords.z += arg0->scale.z;
        temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.x;
        temp_v1->coords.x = temp_v1->coords.x + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.x));
        temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.y;
        temp_v1->coords.y = temp_v1->coords.y + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.y));
        temp_f20 = sinf((f32)(f64)arg0->work[1] * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.z;
        temp_v1->coords.z = temp_v1->coords.z + (temp_f20 - (sinf((f32)(f64)(arg0->work[1] + 1) * 180.0f / (f32)(f64)arg0->work[2] * (M_PI / 180.0)) * arg0->rot.z));
    }
}

omObjData *majinlamp_ArcMoveCreate(s32 arg0, Vec *arg1, s32 arg2, Vec *arg3) {
    omObjData *obj;
    s32 player = -1;
    s32 i;

    obj = omAddObj(0x1000, 0, 0, -1, majinlamp_ArcMoveObjMain);
    if (arg0 >= 0) {
        player = arg0;
        arg0 = 0;
        obj->work[0] = player;
    }
    obj->work[1] = arg2;
    obj->work[2] = arg2;
    obj->trans.x = arg1->x;
    obj->trans.y = arg1->y;
    obj->trans.z = arg1->z;

    if (arg0 == 0) {
        obj->scale.x = (arg1->x - GwPlayer[player].player_obj->coords.x) / arg2;
        obj->scale.y = (arg1->y - GwPlayer[player].player_obj->coords.y) / arg2;
        obj->scale.z = (arg1->z - GwPlayer[player].player_obj->coords.z) / arg2;
    } else {
        obj->scale.x = (arg1->x - ((Object *)arg0)->coords.x) / arg2;
        obj->scale.y = (arg1->y - ((Object *)arg0)->coords.y) / arg2;
        obj->scale.z = (arg1->z - ((Object *)arg0)->coords.z) / arg2;
    }

    obj->rot.x = arg3->x;
    obj->rot.y = arg3->y;
    obj->rot.z = arg3->z;
    obj->data = (void *)arg0;

    for (i = 0; i < 32; i++) {
        if (majinlamp_moveObjTbl[i] == NULL) {
            majinlamp_moveObjTbl[i] = obj;
            break;
        }
    }
    return obj;
}

void majinlamp_RotMoveObjMain(omObjData *arg0) {
    Object *temp_v1;

    temp_v1 = arg0->data;
    arg0->work[1]--;
    if (temp_v1 == NULL) {
        if (arg0->work[1] == 0) {
            GwPlayer[arg0->work[0]].player_obj->rot.x = arg0->rot.x;
            GwPlayer[arg0->work[0]].player_obj->rot.y = arg0->rot.y;
            GwPlayer[arg0->work[0]].player_obj->rot.z = arg0->rot.z;
            omDelObj(arg0);
        } else {
            arg0->scale.y += arg0->scale.x;
            GwPlayer[arg0->work[0]].player_obj->rot.x =
                sinf((f32)(f64)arg0->scale.y * (M_PI / 180.0));
            GwPlayer[arg0->work[0]].player_obj->rot.y = 0;
            GwPlayer[arg0->work[0]].player_obj->rot.z =
                cosf((f32)(f64)arg0->scale.y * (M_PI / 180.0));
        }
    } else if (arg0->work[1] == 0) {
        temp_v1->rot.x = arg0->rot.x;
        temp_v1->rot.y = arg0->rot.y;
        temp_v1->rot.z = arg0->rot.z;
        arg0->data = NULL;
        omDelObj(arg0);
    } else {
        arg0->scale.y += arg0->scale.x;
        temp_v1->rot.x = sinf((f32)(f64)arg0->scale.y * (M_PI / 180.0));
        temp_v1->rot.y = 0;
        temp_v1->rot.z = cosf((f32)(f64)arg0->scale.y * (M_PI / 180.0));
    }
}

omObjData *majinlamp_RotMoveCreate(s32 arg0, Vec *arg1, s32 arg2, Object *arg3) {
    Vec sp18;
    omObjData *obj;
    f32 var_f20;
    f32 var_f4;
    s32 i;

    if (arg3 == NULL) {
        MBVecDirGet(&GwPlayer[arg0].player_obj->coords, arg1, &sp18);
    } else {
        MBVecDirGet(&arg3->coords, arg1, &sp18);
    }

    obj = omAddObj(0x1000, 0, 0, -1, majinlamp_RotMoveObjMain);
    obj->work[0] = arg0;
    obj->work[1] = arg2;
    obj->rot.x = sp18.x;
    obj->rot.y = sp18.y;
    obj->rot.z = sp18.z;

    if (arg3 == NULL) {
        var_f20 = MBVecAngleGet(&GwPlayer[arg0].player_obj->rot);
        var_f4 = MBVecAngleGet(&sp18);
        if (var_f4 < var_f20) {
            if ((var_f20 - var_f4) >= 180.0f) {
                var_f4 += 360.0f;
            }
        } else if ((var_f4 - var_f20) >= 180.0f) {
            var_f20 += 360.0f;
        }
    } else {
        var_f20 = MBVecAngleGet(&arg3->rot);
        var_f4 = MBVecAngleGet(&sp18);
        if (var_f4 < var_f20) {
            if ((var_f20 - var_f4) >= 180.0f) {
                var_f4 += 360.0f;
            }
        } else if ((var_f4 - var_f20) >= 180.0f) {
            var_f20 += 360.0f;
        }
    }

    obj->scale.y = var_f20;
    obj->scale.x = (var_f4 - var_f20) / (f32)arg2;
    obj->data = arg3;

    for (i = 0; i < 32; i++) {
        if (majinlamp_moveObjTbl[i] == NULL) {
            majinlamp_moveObjTbl[i] = obj;
            break;
        }
    }
    return obj;
}

void majinlamp_TunnelScrollObjMain(omObjData *arg0) {
    Hu3DModelObjTexScroll(majinlamp_tunnelMdl->omObj1->model[0], 0, arg0->trans.x, 0x40, 0x40, majinlamp_bgInStr, 0);
    arg0->trans.x += 1.0f;

    if (majinlamp_bgOutScrollF != 0) {
        Hu3DModelObjTexScroll(majinlamp_tunnelMdl->omObj1->model[0], 0, arg0->trans.y, 0x40, 0x40, majinlamp_bgOutStr, 0);
        arg0->trans.y += 1.0f;
    }

    if (arg0->trans.x >= 64.0f) {
        arg0->trans.x -= 64.0f;
    }
    if (arg0->trans.y >= 64.0f) {
        arg0->trans.y -= 64.0f;
    }
    if (arg0->trans.x <= -64.0f) {
        arg0->trans.x += 64.0f;
    }
    if (arg0->trans.y <= -64.0f) {
        arg0->trans.y += 64.0f;
    }
}

void majinlamp_LampObjMain(omObjData *arg0) {
    if (majinlamp_lampBobF != 0) {
        majinlamp_lampMdl->velocity.x = sindf(arg0->rot.y) * 30.0f;
        arg0->rot.y += 2.0f;
        if (arg0->rot.y >= 360.0f) {
            arg0->rot.y -= 360.0f;
        }
    }

    if (majinlamp_playerRideF != 0) {
        majinlamp_gwPlayer->player_obj->velocity.x =
            majinlamp_rideOfsY * majinlamp_lampMdl->scale.x + majinlamp_lampMdl->velocity.x;
        HuVecCopy3F(&majinlamp_gwPlayer->player_obj->coords, &majinlamp_lampMdl->coords);
        HuVecCopy3F(&majinlamp_gwPlayer->player_obj->scale, &majinlamp_lampMdl->scale);
    }

    if (majinlamp_playerTiltF != 0) {
        majinlamp_gwPlayer->player_obj->rot.x = majinlamp_lampMdl->rot.x;
        majinlamp_gwPlayer->player_obj->rot.z = majinlamp_lampMdl->rot.z;
    }
}

void majinlamp_LampBoardExec(void) {
    Vec sp18;
    Vec sp28;
    Vec sp38;
    Vec sp48;
    f32 var_f20;
    f32 var_f22;
    f32 var_f24;
    f32 var_f26;
    f32 temp_f28;
    Object *temp_obj;
    s32 i;
    void *temp_v0;
    omObjData *temp_v1;

    majinlamp_screenSprGrp = HuSprGrpCreate(1, 5);
    temp_v0 = DataRead(0x1301BF);
    majinlamp_screenSpr = HuSprAnimRead(temp_v0);
    DataClose(temp_v0);
    HuSprGrpMemberSet(majinlamp_screenSprGrp, 0, majinlamp_screenSpr, 0);
    HuSprPriSet(majinlamp_screenSprGrp, 0, 0xA);
    HuSprAnimModeSet(majinlamp_screenSprGrp, 0, HUSPR_ANIM_MODE_BANK);
    HuSprAttrSet(majinlamp_screenSprGrp, 0, 0x5000);
    HuSprPosSet(majinlamp_screenSprGrp, 0, 0xA0, 0x78);
    HuSprScaleSet(majinlamp_screenSprGrp, 0, 50.0f, 50.0f);
    majinlamp_gwPlayer = MBPlayerGet(majinlamp_playerNo);
    MBPlayerModelCreate(majinlamp_playerNo, mbPlayerMotTbl[GwPlayer[majinlamp_playerNo].chr], 2);
    memcpy(&sp18, majinlamp_playerRideAnimTbl, 0x20);
    memcpy(&sp38, majinlamp_playerCheerAnimTbl, 0x20);
    majinlamp_playerAnimTbl[0] = CharAnimCreate(
        majinlamp_gwPlayer->player_obj->omObj1->model[0], 2,
        GwPlayer[majinlamp_playerNo].chr,
        ((s32 *)&sp18)[GwPlayer[majinlamp_playerNo].chr]);
    majinlamp_playerAnimTbl[1] = Hu3DAnimDataRead(
        ((s32 *)&sp38)[GwPlayer[majinlamp_playerNo].chr]);
    CharAnimSet(majinlamp_gwPlayer->player_obj->omObj1->model[0], 2,
                       GwPlayer[majinlamp_playerNo].chr, majinlamp_playerAnimTbl[0]);
    MBPlayerMotionSet(majinlamp_playerNo, 4, 2);
    HuVecCopyXYZ(&majinlamp_gwPlayer->player_obj->coords, 150.0f, -100.0f, 3000.0f);
    temp_v1 = (omObjData *)majinlamp_gwPlayer->player_obj;
    temp_v1->next_idx |= 1;
    majinlamp_lampMdl = MBModelCreate(0x25, 0);
    HuVecCopyXYZ(&majinlamp_lampMdl->coords, -150.0f, -50.0f, 3000.0f);
    {
        omObjData *obj = omAddObj(0x1000, 0, 0, -1, majinlamp_LampObjMain);
        obj->rot.y = 0.0f;
        obj->scale.x = 0.0f;
    }
    mbSubMusNo = HuAudSubSeqPlay(0x3C);
    HuAudFXPlay(0x129);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(WIPE_FADE, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x1E);
    MBPlayerMotionShiftSet(majinlamp_playerNo, -1, 0, 0xA, 2);
    HuPrcSleep(0xF);
    MBDlgResultWinExec(0x3A17);
    majinlamp_lampBobF = 0;
    var_f20 = 20.0f;
    while (majinlamp_lampMdl->velocity.x < 1000.0f) {
        majinlamp_lampMdl->velocity.x += var_f20;
        var_f20 += 5.0f;
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&majinlamp_lampMdl->coords, -1600.0f, -100.0f, 1600.0f);
    majinlamp_lampBobF = 1;
    HuMtxRotXF(Hu3DData[majinlamp_lampMdl->omObj1->model[0]].mtx, 60.0f);
    majinlamp_lampMdl->rot.x = sindf(45.0f);
    majinlamp_lampMdl->rot.z = cosdf(45.0f);
    var_f20 = 50.0f;
    while (majinlamp_lampMdl->coords.x < 0.0f) {
        majinlamp_lampMdl->coords.x += var_f20 * 2.0f;
        majinlamp_lampMdl->coords.z += var_f20 * 2.0f;
        var_f20 -= 1.6f;
        if (var_f20 <= 5.0f) {
            var_f20 = 5.0f;
        }
        HuPrcVSleep();
    }
    MBPlayerMotionSet(majinlamp_playerNo, 2, 0);
    memcpy(&sp18, &majinlamp_jumpPos, 0xC);
    MBPlayerPosMoveCreate(&majinlamp_gwPlayer->player_obj->coords, &sp18,
                          &majinlamp_gwPlayer->player_obj->coords, 0x14);
    majinlamp_gwPlayer->player_obj->velocity.y = 30.0f;
    majinlamp_gwPlayer->player_obj->velocity.z = -2.5f;
    HuPrcSleep(0x14);
    temp_obj = majinlamp_gwPlayer->player_obj;
    temp_obj->velocity.z = (temp_f28 = 0.0f);
    temp_obj->velocity.y = temp_f28;
    majinlamp_rideOfsY = majinlamp_gwPlayer->player_obj->coords.y -
                           majinlamp_lampMdl->coords.y - 15.0f;
    majinlamp_playerRideF = 1;
    majinlamp_playerTiltF = 1;
    MBPlayerMotionSet(majinlamp_playerNo, -1, 2);
    memcpy(&sp28, &majinlamp_lookPos, 0xC);
    majinlamp_RotMoveCreate(majinlamp_playerNo, &sp28, 5, NULL);
    HuPrcSleep(5);
    MBDlgWinExecY(-1, 0x3A18, 0x28);
    HuAudFXPlay(0x12B);
    memcpy(&sp38, &majinlamp_flyAwayPos, 0xC);
    memcpy(&sp48, &majinlamp_flyAwayArc, 0xC);
    majinlamp_RotMoveCreate(0, &sp38, 0x1E, majinlamp_lampMdl);
    majinlamp_ArcMoveCreate((s32)majinlamp_lampMdl, &sp38, 0x1E, &sp48);
    var_f20 = 60.0f;
    for (i = 0; i < 0x1E; i++) {
        HuMtxRotXF(Hu3DData[majinlamp_lampMdl->omObj1->model[0]].mtx, var_f20);
        HuMtxRotXF(Hu3DData[majinlamp_gwPlayer->player_obj->omObj1->model[0]].mtx,
                           var_f20 - 60.0f);
        var_f20 -= 2.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateOut(WIPE_FADE, 2);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(majinlamp_gwPlayer->player_obj);
    MBModelDispOff(majinlamp_lampMdl);
    HuSprTPLvlSet(majinlamp_screenSprGrp, 0, 0);
}

void majinlamp_TunnelFlyExec(void) {
    Vec sp[4];
    Vec *direction;
    Vec *offset;
    s16 sound;
    s32 i;

    majinlamp_tunnelMdl = MBModelFileCreate(0x1301F6, -1, 1.0f, 0.0f, NULL);
    HuVecCopyXYZ(&majinlamp_tunnelMdl->scale, 2.0f, 2.0f, 2.0f);
    Hu3DModelVtxBufMake(majinlamp_tunnelMdl->omObj1->model[0]);
    Hu3DMotionSpeedSet(majinlamp_tunnelMdl->omObj1->model[0], 0.25f);
    HuVecCopyXYZ(&majinlamp_tunnelMdl->scale, 4.0f, 4.0f, 4.0f);
    Hu3DModelCameraSet(majinlamp_tunnelMdl->omObj1->model[0], HU3D_CAM1);
    omAddObj(0x1000, 0, 0, -1, majinlamp_TunnelScrollObjMain);
    majinlamp_cam0Fov = 45.0f;
    majinlamp_cam1Fov = 100.0f;
    majinlamp_cam1Near = 10.0f;
    majinlamp_cam1Far = 20000.0f;
    HuMtxRotXF(Hu3DData[majinlamp_lampMdl->omObj1->model[0]].mtx, 60.0f);
    HuMtxRotXF(Hu3DData[majinlamp_gwPlayer->player_obj->omObj1->model[0]].mtx, 0.0f);
    HuVecCopy3F(&majinlamp_gwPlayer->player_obj->coords, &majinlamp_flyPosTbl[0]);
    HuVecCopy3F(&majinlamp_lampMdl->coords, &majinlamp_flyPosTbl[0]);
    MBMotionSet(majinlamp_gwPlayer->player_obj, -1, 2);
    MBVecForwardSet(&majinlamp_gwPlayer->player_obj->rot);
    MBVecForwardSet(&majinlamp_lampMdl->rot);
    majinlamp_rideOfsY = 0.0f;
    majinlamp_playerRideF = 1;
    majinlamp_playerTiltF = 1;
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(WIPE_FADE, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    sound = HuAudFXPlay(0x12A);
    MBModelDispOn(majinlamp_gwPlayer->player_obj);
    MBModelDispOn(majinlamp_lampMdl);
    for (i = 0; i < 0xB5; i += 2) {
        HuVecCopy3F(&sp[0], &majinlamp_gwPlayer->player_obj->coords);
        HuVecCopy3F(&majinlamp_gwPlayer->player_obj->coords, &majinlamp_flyPosTbl[0]);
        HuVecSubtract(&sp[2], &majinlamp_flyPosTbl[2], &majinlamp_flyPosTbl[0]);
        HuVecMulScalar(&sp[2], sindf(i / 2), &sp[2]);
        HuVecAdd(&majinlamp_gwPlayer->player_obj->coords, &sp[2],
                 &majinlamp_gwPlayer->player_obj->coords);
        sp[3].x = -sindf(i * 2) * (0x1F4 - i);
        sp[3].y = -sindf(i * 2) * (0x12C - i);
        sp[3].z = 0.0f;
        HuVecAdd(&majinlamp_gwPlayer->player_obj->coords, &sp[3],
                 &majinlamp_gwPlayer->player_obj->coords);
        MBVecDirGet(&sp[0], &majinlamp_gwPlayer->player_obj->coords,
                    &majinlamp_gwPlayer->player_obj->rot);
        HuVecCopy3F(&majinlamp_lampMdl->coords,
                    &majinlamp_gwPlayer->player_obj->coords);
        HuVecCopy3F(&majinlamp_lampMdl->rot, &majinlamp_gwPlayer->player_obj->rot);
        HuPrcVSleep();
    }
    majinlamp_bgOutScrollF = 1;
    majinlamp_playerTiltF = 0;
    direction = &sp[2];
    offset = &sp[3];
    MBVecForwardSet(offset);
    HuVecCopy3F(direction, &majinlamp_gwPlayer->player_obj->rot);
    HuPrcChildLink(HuPrcCurrentGet(), MBVecRotLerpCreate(&majinlamp_gwPlayer->player_obj->rot, offset,
                                                                 &majinlamp_gwPlayer->player_obj->rot, 0xA));
    HuPrcChildWatch();
    msmSeStop(sound);
    PlayerFXPlay(0x2BD, majinlamp_playerNo);
    CharAnimSet(majinlamp_gwPlayer->player_obj->omObj1->model[0], 2,
                       GwPlayer[majinlamp_playerNo].chr, majinlamp_playerAnimTbl[1]);
    MBPlayerMotionSet(majinlamp_playerNo, 5, 2);
    HuPrcSleep(0x32);
    MBVecDirGet(&majinlamp_gwPlayer->player_obj->coords, &majinlamp_flyExitPos, direction);
    HuPrcChildLink(HuPrcCurrentGet(), MBVecRotLerpCreate(&majinlamp_gwPlayer->player_obj->rot, direction,
                                                                 &majinlamp_gwPlayer->player_obj->rot, 0xA));
    HuPrcChildLink(HuPrcCurrentGet(), MBVecRotLerpCreate(&majinlamp_lampMdl->rot, direction,
                                                                 &majinlamp_lampMdl->rot, 0xA));
    HuPrcChildWatch();
    majinlamp_playerTiltF = 1;
    HuPrcSleep(0xA);
    HuAudFXPlay(0x12B);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&majinlamp_gwPlayer->player_obj->coords,
                                                            &majinlamp_flyExitPos,
                                                            &majinlamp_gwPlayer->player_obj->coords, 0x14));
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&majinlamp_lampMdl->coords, &majinlamp_flyExitPos,
                                                            &majinlamp_lampMdl->coords, 0x14));
    HuPrcSleep(0xA);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateOut(WIPE_FADE, 0x14);
    HuPrcChildWatch();
}

void majinlamp_MainProc(void) {
    majinlamp_LampBoardExec();
    majinlamp_TunnelFlyExec();
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void majinlamp_ExitObjMain(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        majinlamp_CameraClose();
        majinlamp_SysClose();
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void majinlamp_ExitCheckObjMain(omObjData *arg0) {
    if (omSysExitReq != 0) {
        arg0->func = majinlamp_ExitObjMain;
    }
}

void majinlamp_SysInit(void) {
    MBModelInit();
    MBPlayerMotInit();
}

void majinlamp_SysClose(void) {
    HuSprAnimKill(majinlamp_screenSpr);
    HuSprGrpKill(majinlamp_screenSprGrp);
    MBPlayerClose();
    MBModelClose();
}

void majinlamp_CameraProc(void) {
    for (;;) {
        Hu3DCameraPerspectiveSet(0, majinlamp_cam0Fov, majinlamp_cam0Near, majinlamp_cam0Far);
        Hu3DCameraPosSetV(0, &majinlamp_cam0Pos, &majinlamp_cam0Target, &majinlamp_cam0Up);
        Hu3DCamUpdateMtx(0);
        Hu3DCameraPerspectiveSet(1, majinlamp_cam1Fov, majinlamp_cam1Near, majinlamp_cam1Far);
        Hu3DCameraPosSetV(1, &majinlamp_cam1Pos, &majinlamp_cam1Target, &majinlamp_cam1Up);
        Hu3DCamUpdateMtx(1);
        HuPrcVSleep();
    }
}

void majinlamp_CameraInit(void) {
    Hu3DCamInit(2);
    majinlamp_cameraProc = omAddPrcObj(majinlamp_CameraProc, 0x1001, 0, 0);
    omPrcSetStatBit(majinlamp_cameraProc, OM_STAT_NOALLPAUSE);

    HuVecCopyXYZ(&majinlamp_cam0Pos, 0.0f, 0.0f, 5000.0f);
    HuVecCopyXYZ(&majinlamp_cam0Target, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&majinlamp_cam0Up, 0.0f, 1.0f, 0.0f);
    Hu3DCameraPerspectiveSet(0, majinlamp_cam0Fov, majinlamp_cam0Near, majinlamp_cam0Far);
    Hu3DCameraPosSetV(0, &majinlamp_cam0Pos, &majinlamp_cam0Target, &majinlamp_cam0Up);
    Hu3DCamUpdateMtx(0);

    HuVecCopyXYZ(&majinlamp_cam1Pos, 0.0f, 0.0f, 5000.0f);
    HuVecCopyXYZ(&majinlamp_cam1Target, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&majinlamp_cam1Up, 0.0f, 1.0f, 0.0f);
    Hu3DCameraPerspectiveSet(1, majinlamp_cam1Fov, majinlamp_cam1Near, majinlamp_cam1Far);
    Hu3DCameraPosSetV(1, &majinlamp_cam1Pos, &majinlamp_cam1Target, &majinlamp_cam1Up);
    Hu3DCamUpdateMtx(1);
}

void majinlamp_CameraClose(void) {
}

const char majinlamp_bgInStr[8] = "bg_in";
const char majinlamp_bgOutStr[8] = "bg_out";

const s32 majinlamp_playerRideAnimTbl[] = {
    0x000200A4,
    0x000300A4,
    0x000700A4,
    0x000400A4,
    0x000500A4,
    0x000600A4,
    0x000800A4,
    0x0009001B,
};

const s32 majinlamp_playerCheerAnimTbl[] = {
    0x000200AB,
    0x000300AB,
    0x000700AB,
    0x000400AB,
    0x000500AB,
    0x000600AB,
    0x000800AB,
    0x00090027,
};

const Vec majinlamp_jumpPos = { 0.0f, -90.0f, 3200.0f };
const Vec majinlamp_lookPos = { 500.0f, 0.0f, 4000.0f };
const Vec majinlamp_flyAwayPos = { 200.0f, 200.0f, 5000.0f };
const Vec majinlamp_flyAwayArc = { 0.0f, 0.0f, -200.0f };
