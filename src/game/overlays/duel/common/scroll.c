#include "common_duel.h"
#include "ovl_81.h"

#define UNK_ARR_SIZE 4

extern s32 Hu3DSubMtxStackPrev[];

extern omObjData *mbdMapScrollArrowObj;
extern UnkBoard4 *mbdMapScrollArrow;
extern s16 mbdMapScrollArrowPos[UNK_ARR_SIZE][2];
extern UnkBoard4 *mbdMapScrollMiniMap;
extern Process *mbdMapScrollMiniMapProc;
extern Object *mbdMapScrollMdlTbl[MBD_MAX_PLAYERS];
extern f32 mbdMapScrollZoom;
extern Vec2f mbdMapScrollPos;

f32 mbdMapScrollShadowSizeTbl[] = {
    0.8999999762f, 0.8999999762f, 1.200000048f,
    1.100000024f, 1.100000024f,
    1.5f, 0.8999999762f, 1.200000048f
};

s16 mbdMapScrollArrowPosTbl[UNK_ARR_SIZE][2] = {
    { 0x22, 0x80 }, { 0x11E, 0x80 }, { 0xA0, 0x18 }, { 0xA0, 0xD8 }
};

s16 mbdMapScrollArrowStartTbl[UNK_ARR_SIZE][2] = {
    { 0x0092, 0x0080 }, { 0x00AE, 0x0080 }, { 0x00A0, 0x006C }, { 0x00A0, 0x0084 }
};

s16 mbdMapScrollArrowVelTbl[UNK_ARR_SIZE][2] = {
    { 0xFFF0, 0x0000 }, { 0x0010, 0x0000 }, { 0x0000, 0xFFF4 }, { 0x0000, 0x000C }
};

f32 mbdMapScrollArrowRotTbl[UNK_ARR_SIZE] = {
    90.0f, -90.0f, 0.0f, 180.0f
};

s16 mbdMapScrollMiniMapPosTbl[][2] = {
    { 0x00F0, 0x0034 }, { 0x00F0, 0x0034 }, { 0x00F0, 0x0034 }, { 0x00F0, 0x0034 }, { 0x00F0, 0x0034 }
};

s32 mbdMapScrollMiniMapSprTbl[] = {
    0x00130117, 0x00130118, 0x00130119, 0x0013011A, 0x0013011B
};

s32 mbdMapScrollMiniMapBoardSprTbl[] = {
    0x00130117, 0x00130136, 0x00130138, 0x0013013B, 0x0013013D, 0x0013013F
};

s32 mbdMapScrollMiniMapBoardAltSprTbl[] = {
    0x00130118, 0x00130137, 0x00130139, 0x0013013C, 0x0013013E, 0x00130140
};

s32 mbdMapScrollIconMdlTbl[] = {
    0x001300B3, 0x001300B4, 0x001300B5, 0x001300B6, 0x001300B7, 0x001300B8, 0x001300B9, 0x001300BA
};

f32 mbdMapScrollIconScaleTbl[] = {
    0.6499999762f,
    0.6499999762f,
    0.6499999762f,
    0.6499999762f,
    0.6499999762f,
    0.5849999785f,
    0.6499999762f,
    0.6499999762f,
};

void MBDMapScrollArrowObjMain(omObjData *obj) {
    s32 i;

    for (i = 0; i < UNK_ARR_SIZE; i++) {
        mbdMapScrollArrowPos[i][0] += mbdMapScrollArrowVelTbl[i][0];
        mbdMapScrollArrowPos[i][1] += mbdMapScrollArrowVelTbl[i][1];
        if (mbdMapScrollArrowVelTbl[i][0] < 0) {
            if (mbdMapScrollArrowPos[i][0] < mbdMapScrollArrowPosTbl[i][0]) {
                mbdMapScrollArrowPos[i][0] = mbdMapScrollArrowPosTbl[i][0];
            }
        }

        if (mbdMapScrollArrowVelTbl[i][0] > 0) {
            if (mbdMapScrollArrowPos[i][0] > mbdMapScrollArrowPosTbl[i][0]) {
                mbdMapScrollArrowPos[i][0] = mbdMapScrollArrowPosTbl[i][0];
            }
        }

        if (mbdMapScrollArrowVelTbl[i][1] < 0) {
            if (mbdMapScrollArrowPos[i][1] < mbdMapScrollArrowPosTbl[i][1]) {
                mbdMapScrollArrowPos[i][1] = mbdMapScrollArrowPosTbl[i][1];
            }
        }

        if (mbdMapScrollArrowVelTbl[i][1] > 0) {
            if (mbdMapScrollArrowPos[i][1] > mbdMapScrollArrowPosTbl[i][1]) {
                mbdMapScrollArrowPos[i][1] = mbdMapScrollArrowPosTbl[i][1];
            }
        }
        HuSprPosSet(mbdMapScrollArrow->unk_0A, i, mbdMapScrollArrowPos[i][0], mbdMapScrollArrowPos[i][1]);
    }
}

UnkBoard4 *MBDMapScrollArrowCreate(void) {
    UnkBoard4 *temp_v0;
    omObjData *temp_v0_2;
    void *temp_s4;
    s32 i;

    temp_v0 = MBDSprGrpCreate(4, 0);
    mbdMapScrollArrow = temp_v0;
    temp_s4 = DataRead(0x001301D4);

    for (i = 0; i < UNK_ARR_SIZE; i++) {
        temp_v0->unk_0C[i] = HuSprAnimRead(temp_s4);
        HuSprGrpMemberSet(temp_v0->unk_0A, i, temp_v0->unk_0C[i], 0);
        HuSprPriSet(temp_v0->unk_0A, i, 0);
        HuSprDispOff(temp_v0->unk_0A, i);
        HuSprPosSet(temp_v0->unk_0A, i, mbdMapScrollArrowStartTbl[i][0], mbdMapScrollArrowStartTbl[i][1]);
        mbdMapScrollArrowPos[i][0] = mbdMapScrollArrowStartTbl[i][0];
        mbdMapScrollArrowPos[i][1] = mbdMapScrollArrowStartTbl[i][1];
        HuSprZRotSet(temp_v0->unk_0A, i, mbdMapScrollArrowRotTbl[i]);
    }

    DataClose(temp_s4);
    temp_v0_2 = omAddObj(0x1000, 0, 0, -1, MBDMapScrollArrowObjMain);
    mbdMapScrollArrowObj = temp_v0_2;
    omSetStatBit(temp_v0_2, OM_STAT_NOPAUSE);
    return temp_v0;
}

void MBDMapScrollArrowKill(UnkBoard4 *arg0) {
    omDelObj(mbdMapScrollArrowObj);
    MBDSprGrpKill(arg0);
}

void MBDMapScrollArrowDispSet(UnkBoard4 *arg0, u16 arg1) {
    s32 var_v0;
    s32 i;

    for (i = 0; i < 4; i++) {
        var_v0 = arg1 >> i;
        if (var_v0 & 1) {
            HuSprDispOff(arg0->unk_0A, i);
        } else {
            HuSprDispOn(arg0->unk_0A, i);
        }
    }
}

void MBDMapScrollMiniMapUpdate(UnkBoard4 *arg0, s32 arg1) {
    Vec2f sp10;
    Vec2f sp18;

    MBDCameraPos2DGet(&sp10);
    HuSprPosSet(arg0->unk_0A, 2, (mbdMapScrollMiniMapPosTbl[2][0] + (sp10.x / 9.0f)), (mbdMapScrollMiniMapPosTbl[2][1] + (sp10.y / 9.0f)));
    MBDCamera3Dto2D(&GwPlayer[0].player_obj->coords, &sp18);
    HuSprPosSet(arg0->unk_0A, 3, (mbdMapScrollMiniMapPosTbl[3][0] + (sp10.x / 9.0f) + ((sp18.x - 160.0f) / 9.0f)), ((mbdMapScrollMiniMapPosTbl[3][1] + (sp10.y / 9.0f) + ((sp18.y - 120.0f) / 9.0f)) - 4.0f));
    MBDCamera3Dto2D(&GwPlayer[1].player_obj->coords, &sp18);
    HuSprPosSet(arg0->unk_0A, 4, (mbdMapScrollMiniMapPosTbl[4][0] + (sp10.x / 9.0f) + ((sp18.x - 160.0f) / 9.0f)), ((mbdMapScrollMiniMapPosTbl[4][1] + (sp10.y / 9.0f) + ((sp18.y - 120.0f) / 9.0f)) - 4.0f));

    if (arg1 == 0) {
        HuSprDispOff(arg0->unk_0A, 3);
        HuSprDispOn(arg0->unk_0A, 4);
        return;
    }

    HuSprDispOn(arg0->unk_0A, 3);
    HuSprDispOff(arg0->unk_0A, 4);
}

// TODO: what is this?
void MBDMapScrollMiniMapProc(void) {
    s32 counter = 32;

    while (1) {
        UnkBoard4 *data = mbdMapScrollMiniMap;
        s32 adjusted = (counter < 0) ? (counter + 0x1F) : counter;
        MBDMapScrollMiniMapUpdate(data, adjusted >> 5);

        counter++;
        if (counter >= 64) {
            counter = 0;
        }

        HuPrcVSleep();
    }
}

void *MBDMapScrollMiniMapCreate(void) {
    UnkBoard4 *temp_s2;
    void *temp_v0;
    s32 i;

    temp_s2 = MBDSprGrpCreate(5, 0);
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            temp_v0 = DataRead(mbdMapScrollMiniMapBoardSprTbl[GwSystem.current_board_index]);
        } else if (i == 1) {
            temp_v0 = DataRead(mbdMapScrollMiniMapBoardAltSprTbl[GwSystem.current_board_index]);
        } else {
            temp_v0 = DataRead(mbdMapScrollMiniMapSprTbl[i]);
        }

        temp_s2->unk_0C[i] = HuSprAnimRead(temp_v0);
        HuSprGrpMemberSet(temp_s2->unk_0A, i, temp_s2->unk_0C[i], 0);
        HuSprPriSet(temp_s2->unk_0A, i, 0);
        if (i == 0) {
            HuSprAttrSet(temp_s2->unk_0A, 0, 0x1000);
            HuSprTPLvlSet(temp_s2->unk_0A, 0, 0x80U);
        } else {
            HuSprAttrSet(temp_s2->unk_0A, i, 0);
        }
        HuSprPosSet(temp_s2->unk_0A, i, mbdMapScrollMiniMapPosTbl[i][0], mbdMapScrollMiniMapPosTbl[i][1]);
        DataClose(temp_v0);
    }
    mbdMapScrollMiniMapProc = omAddPrcObj(MBDMapScrollMiniMapProc, 0x1005, 0, 0);
    MBDMapScrollMiniMapUpdate(temp_s2, 1);
    return temp_s2;
}

void MBDMapScrollMiniMapKill(UnkBoard4 *arg0) {
    MBDSprGrpKill(arg0);
    omDelPrcObj(mbdMapScrollMiniMapProc);
}

void MBDPlayerIconMdlSet(void) {
    GW_PLAYER *temp_v0;
    s32 i;
    Object **obj;
    Object *temp_a0;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        temp_v0 = MBDPlayerGet(i);
        mbdMapScrollMdlTbl[i] = MBDModelFileCreate(mbdMapScrollIconMdlTbl[temp_v0->chr], 9, 1.0f, mbdMapScrollShadowSizeTbl[temp_v0->chr], 0);
        obj = &mbdMapScrollMdlTbl[i]; // TODO: this is odd
        Hu3DModelScaleSet(mbdMapScrollMdlTbl[i]->omObj1->model[0], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet((*obj)->omObj2->model[0], 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&(*obj)->scale, mbdMapScrollIconScaleTbl[temp_v0->chr], mbdMapScrollIconScaleTbl[temp_v0->chr], mbdMapScrollIconScaleTbl[temp_v0->chr]);
    }

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        temp_v0 = MBDPlayerGet(i);
        temp_a0 = temp_v0->player_obj;
        temp_v0->player_obj = mbdMapScrollMdlTbl[i];
        mbdMapScrollMdlTbl[i] = temp_a0;
    }

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        MBDPlayerPosFixSet(i, 1);
    }

    HuPrcVSleep();

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        MBDModelDispOff(mbdMapScrollMdlTbl[i]);
    }
}

void MBDPlayerIconMdlReset(void) {
    GW_PLAYER *temp_v0;
    Object *temp_a0;
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        temp_v0 = MBDPlayerGet(i);
        temp_a0 = temp_v0->player_obj;
        temp_v0->player_obj = mbdMapScrollMdlTbl[i];
        mbdMapScrollMdlTbl[i] = temp_a0;
    }

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        temp_v0 = MBDPlayerGet(i);
        MBDModelDispOn(temp_v0->player_obj);
        MBDModelKill(mbdMapScrollMdlTbl[i]);
    }
}

void MBDMapScrollIconSet(void) {
    MBDPlayerIconMdlSet();
    MBDPartnerMotionReset(0);
    MBDPartnerMotionReset(1);
}

void MBDMapScrollIconReset(void) {
    MBDPlayerIconMdlReset();
    MBDStatusShowAll();
    MBDPartnerMotionSet(GwSystem.current_player_index, 0, -1, 2);
    MBDPartnerMotionSet(GwSystem.current_player_index, 1, -1, 2);
}

void MBDMapScrollProc(void) {
    Vec2f sp10;
    f32 temp_f20;
    f32 temp_f22;
    s16 *temp_s0;
    s32 temp_s2;
    UnkBoard4 *temp_s3;
    DuelHelpWin *temp_s6;
    s16 var_s1;
    DuelHelpWin *var_s4;
    s32 var_s7;
    s16 sixteen;
    f32 sixteenFloat;

    var_s4 = NULL;

    // TODO: do-while(0) required for matching
    do {
        temp_s2 = (s32)HuPrcCurrentGet()->user_data;
        var_s7 = 0;
        var_s1 = 0;
        temp_f22 = MBDCameraSpeedGet();
        if ((MBDOvlCallCheck()) == 0) {
            var_s7 = MBDSaiNumKill(GwSystem.current_player_index);
            MBDSaiMdlDispOff(GwSystem.current_player_index);
            HuAudSeqVolSet(0x60);
        }
        MBDMapScrollIconSet();
        temp_s3 = MBDMapScrollArrowCreate();
        temp_s6 = MBDHelpWinCreate(4, 0xA0, 0);
        if (Hu3DSubMtxStackPrev[4] != 0) {
            var_s4 = MBDHelpWinCreate(6, 0x3C, 0);
        }
        mbdMapScrollMiniMap = MBDMapScrollMiniMapCreate();
        MBDCameraSpeedSet(3.5f);

        do {
            sixteen = 16;
            HuPrcVSleep();
            MBDCameraPos2DGet(&sp10);
            MBDMapScrollArrowDispSet(temp_s3, MBDCameraPos2DSet(&sp10));

            if (ContBtn[temp_s2] & 0x200) {
                sp10.x -= sixteen;
                var_s1 = 0xF;
            }
            if (ContBtn[temp_s2] & 0x100) {
                sp10.x += sixteen;
                var_s1 = 0xF;
            }
            if (ContBtn[temp_s2] & 0x800) {
                sp10.y -= sixteen;
                var_s1 = 0xF;
            }
            if (ContBtn[temp_s2] & 0x400) {
                sp10.y += sixteen;
                var_s1 = 0xF;
            }

            MBDCameraPos2DSet(&sp10);

            if (var_s1 != 0) {
                var_s1 -= 1;
                MBDStatusHideAll();
            } else {
                MBDStatusShowAll();
            }

            if (GwPlayer[GwSystem.current_player_index].stat & 1) {
                HuWinComKeyReset();
                goto label; // break doesn't work here for some reason
            }
        } while (mbCameraBtnF != 0 && !(ContBtnDown[temp_s2] & (A_BUTTON | B_BUTTON | Z_TRIG | R_TRIG)));

        while (1) {
        label:
            MBDHelpWinKill(temp_s6);
            if (var_s4 != NULL) {
                MBDHelpWinKill(var_s4);
            }
            MBDMapScrollArrowKill(temp_s3);
            MBDMapScrollMiniMapKill(mbdMapScrollMiniMap);
            WipeCreateOut(WIPE_TYPE_NORMAL, 4);
            HuPrcSleep(4);
            if ((MBDOvlCallCheck()) == 0) {
                MBDBackStreamStop();
                MBDBackStreamStart();
                MBDCameraSpeedSet(-1.0f);
                temp_f20 = MBDCameraSpeedDivGet();
                MBDCameraSpeedDivSet(1.0f);
                MBDBackThreadPriHighSet();
                MBDCameraZoomSet(mbdMapScrollZoom);
                MBDCameraPos2DSet(&mbdMapScrollPos);
                HuPrcVSleep();
                MBDCameraSpeedDivSet(temp_f20);
                if (var_s7 != 0) {
                    MBDSaiNumShow(GwSystem.current_player_index);
                }
                MBDSaiMdlDispOn(GwSystem.current_player_index);
                MBDMapScrollIconReset();
                HuAudSeqVolSet(0x7F);
                WipeCreateIn(WIPE_TYPE_NORMAL, 4);
                HuPrcSleep(4);
                MBDCameraSpeedSet(temp_f22);
                omDelPrcObj(0);
                return;
            } else {
                break;
            }
            HuWinComKeyReset();
        }
        MBDMapScrollIconReset();
        MBDCameraSpeedSet(temp_f22);
        omDelPrcObj(0);
    } while (0);
}

void MBDMapScrollFocusProc(void) {
    while (1) {
        MBDCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
        HuPrcVSleep();
    }
}

void MBDMapScrollExec(s32 padIdx) {
    Process *proc;
    Process *proc2;
    Process *procObj;

    mbdMapScrollZoom = MBDCameraZoomGet();
    MBDCameraPos2DGet(&mbdMapScrollPos);
    winPauseF = 1;
    omAllPause();
    MBDBackThreadPriLowSet();
    procObj = omAddPrcObj(MBDMapScrollFocusProc, 0x1005, 0, 0);
    omPrcSetStatBit(procObj, OM_STAT_NOPAUSE);
    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, MBDCameraZoomMotStart(1.0f));
    HuPrcChildWatch();
    omDelPrcObj(procObj);
    proc2 = HuPrcCurrentGet();
    procObj = omAddPrcObj(MBDMapScrollProc, 0x1005, 0, 0);
    procObj->user_data = (void *)padIdx;
    omPrcSetStatBit(procObj, OM_STAT_NOALLPAUSE);
    HuPrcChildLink(proc2, procObj);
    HuPrcChildWatch();
    omAllUPause();
    winPauseF = 0;
    MBDBackThreadPriHighSet();
}
