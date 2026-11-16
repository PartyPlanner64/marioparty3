#include "common_duel.h"
#include "ovl_81.h"

s16 MBDPadStkCheck(s16, f32);
f32 MBDVecBetweenAngleGet(Vec*, Vec*);

static void MBDBranchSelProc(void) {
    s32 mesg;
    s32 ret;
    UnkEA790Struct *work;
    Vec *scale;
    f32 scaleX;
    f32 scaleZ;
    f32 speed;
    f32 angle;
    s16 timer;
    s16 sel;
    s16 delay;
    s32 i;

    timer = -1;
    work = HuPrcCurrentGet()->user_data;
    sel = work->unk_0C;
    angle = 0.0f;
    delay = 0;

    while (timer != 0) {
        HuPrcVSleep();

        if (timer < 0) {
            if (delay == 0) {
                ret = osRecvMesg(&work->unk10, (OSMesg *)&mesg, 0);
                if (ret == -1) {
                    mesg = ret;
                }
                if (work->unk_00 & 1) {
                    delay = 8;
                }
            } else {
                mesg = -1;
                delay--;
            }

            switch (mesg) {
            case -1:
                break;
            case -2:
                work->unk_0C++;
                if (work->unk_0C >= work->unk_02) {
                    work->unk_0C = 0;
                }
                break;
            case -3:
                work->unk_0C--;
                if (work->unk_0C < 0) {
                    work->unk_0C = work->unk_02 - 1;
                }
                break;
            case -4:
                if (work->unk_0C >= 0) {
                    HuAudFXPlay(3);
                    mbCameraBtnF = 0;
                    duelCancelEnableF = 0;
                    timer = 30;
                }
                break;
            case -5:
                HuAudFXPlay(4);
                work->unk_0C = -1;
                timer = 0;
                break;
            case -6:
                work->unk_0C = -1;
                break;
            default:
                if (mesg < work->unk_02) {
                    work->unk_0C = mesg;
                }
                break;
            }

            if (sel != work->unk_0C) {
                HuAudFXPlay(1);
                if (sel >= 0) {
                    HuVecCopyXYZ(&MBDBranchArrowGrpArrowGet(work, sel)->obj->scale, 1.0f, 1.0f, 1.0f);
                    angle = 0.0f;
                }
                sel = work->unk_0C;
            }
        }

        if (sel >= 0) {
            f32 temp;
            if (timer >= 0) {
                speed = 50.0f;
            } else {
                speed = 25.0f;
            }
            angle += speed;
            temp = 360.0f;
            if (angle > temp) {
                angle -= temp;
            }
            scaleZ = (cosdf(angle) * 0.3f) + 1.2f;
            scaleX = (cosdf(angle) * 0.2f) + 1.2f;
            HuVecCopyXYZ(&MBDBranchArrowGrpArrowGet(work, sel)->obj->scale, scaleX, 1.0f, scaleZ);
        }

        if (timer > 0) {
            timer--;
            scaleZ = timer * (1.0f / 30.0f);
            for (i = 0; i < work->unk_02; i++) {
                if (i != sel) {
                    scale = &MBDBranchArrowGrpArrowGet(work, i)->obj->scale;
                    HuVecMulScalar(scale, scaleZ, scale);
                }
            }
        }
    }
    omDelPrcObj(NULL);
}

s32 MBDBranchSelMesSend(UnkEA790Struct* arg0, s32 arg1) {
    if (arg0->proc != NULL) {
        return osSendMesg(&arg0->unk10, (void* ) arg1, 0);
    }
    return - 1;
}

static void MBDBranchSelPadProc(void) {
    Vec stick;
    Vec diff;
    UnkEA790Struct *work;
    GW_PLAYER *player;
    s32 sel;
    s32 i;
    s16 run;

    run = 1;
    work = HuPrcCurrentGet()->user_data;
    player = work->player;
    sel = work->unk_0C;

    while (run) {
        HuPrcVSleep();

        stick.x = HuPadStkX[work->unkE];
        stick.z = HuPadStkY[work->unkE];
        stick.z = -stick.z;
        stick.y = 0.0f;

        if (MBDPadStkCheck(work->unkE, 40.0f) != 0) {
            for (i = 0; i < work->unk_02; i++) {
                HuVecSubtract(&diff,
                              &MBDBranchArrowGrpArrowGet(work, i)->obj->coords,
                              &player->player_obj->coords);
                diff.y = 0.0f;
                if (MBDVecBetweenAngleGet(&stick, &diff) <= 38.0f) {
                    if (sel != i) {
                        sel = i;
                        MBDBranchSelMesSend(work, sel);
                    }
                    break;
                }
            }
        }

        if ((ContBtnDown[work->unkE] & A_BUTTON) && (sel >= 0)) {
            sel = -4;
            MBDBranchSelMesSend(work, sel);
            run = 0;
        }
    }
    omDelPrcObj(NULL);
}


s32 MBDBranchSelStart(UnkEA790Struct* arg0, s16 playerNo, s32 arg2) {
    GW_PLAYER* player;
    Process* proc;

    if (arg0->proc == NULL) {
        proc = omAddPrcObj(MBDBranchSelProc, 0xEFFF, 0x1000, 0);
        arg0->proc = proc;
        proc->user_data = arg0;
        osCreateMesgQueue(&arg0->unk10, &arg0->unk28, 0x10);
        arg0->unk_00 = arg2 | arg0->unk_00;
        player = MBDGetPlayerStruct(playerNo);
        if (player->stat & 1) {
            arg0->unk_00 |= 1;
            MBDBranchSelMesSend(arg0, -1);
        } else {
            arg0->unkE = player->pad;
            omAddPrcObj(MBDBranchSelPadProc, 0xEFFF, 0x1000, 0)->user_data = arg0;
        }
        return player->stat & 1;
    }
    return -1;
}

s32 MBDBranchSelWait(UnkEA790Struct* arg0) {
    if (arg0->proc != NULL) {
        HuPrcChildLink(HuPrcCurrentGet(), arg0->proc);
        HuPrcChildWatch();
        arg0->proc = NULL;
    }
    return arg0->unk_0C;
}

void MBDBranchArrowPosSet(UnkBoard2* arg0, Vec* arg1, Vec* arg2, f32 arg3) {
    Vec sp10;

    MBDVecDirGet(arg1, arg2, &sp10);
    HuVecCopy3F(&arg0->obj->rot, &sp10);
    HuVecMulScalar(&sp10, arg3, &sp10);
    HuVecAdd(&arg0->obj->coords, &sp10, arg1);
}

static UnkEA790Struct* MBDBranchArrowGrpCreateEx(s16 arg0, s16* arg1, s32 arg2) {
    GW_PLAYER* player;
    UnkBoard2* temp_s0;
    UnkEA790Struct* temp_v0;

    player = MBDGetPlayerStruct(arg0);
    temp_v0 = MBDBranchArrowGrpCreate();
    temp_v0->player = player;
    for (; *arg1 >= 0; arg1++) {
        temp_s0 = MBDBranchArrowCreate(arg2);
        MBDBranchArrowPosSet(temp_s0, &player->player_obj->coords, &MBDMasuGet(*arg1)->coords, 12.0f);
        MBDBranchArrowGrpAdd(temp_v0, temp_s0, 0);
    }
    
    return temp_v0;
}

UnkEA790Struct* MBDBranchArrowLinkCreate(s16 arg0, s16* arg1) {
    return MBDBranchArrowGrpCreateEx(arg0, arg1, 0);
}
