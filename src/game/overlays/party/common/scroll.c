#include "common_board.h"
#include "back.h"
#include "status.h"
#include "helpwin.h"
#include "main.h"
#include "sprgrp.h"
#include "player.h"
#include "model.h"
#include "sai.h"

extern omObjData* mbMapScrollArrowObj;
extern UnkBoard8* mbMapScrollArrow;
extern Object* mbMapScrollMdlTbl[];
extern f32 mbMapScrollZoom;

// start of scroll.c .data section
f32 mbMapScrollShadowSizeTbl[] = {
    0.9f, 0.9f, 1.2f, 1.1f, 1.1f, 1.5f, 0.9f, 1.2f,
};

s16 mbMapScrollArrowPosTbl[MB_MAX_PLAYERS][2] = {
    { 34, 128 },
    { 286, 128 },
    { 160, 24 },
    { 160, 216 }
};

s16 mbMapScrollArrowStartTbl[MB_MAX_PLAYERS][2] = {
    {0x0092, 0x0080},
    {0x00AE, 0x0080},
    {0x00A0, 0x006C},
    {0x00A0, 0x0084}
};

s16 mbMapScrollArrowVelTbl[MB_MAX_PLAYERS][2] = {
    { -16, 0 },
    { 16, 0 },
    { 0, -12 },
    { 0, 12 }
};

f32 mbMapScrollArrowRotTbl[MB_MAX_PLAYERS] = {
    90.0f, -90.0f, 0.0f, 180.0f
};

s32 mbMapScrollIconMdlTbl[] = {
    0x001300B3,
    0x001300B4,
    0x001300B5,
    0x001300B6,
    0x001300B7,
    0x001300B8,
    0x001300B9,
    0x001300BA
};

s32 mbMapScrollKSuitIconMdlTbl[] = {
    0x001300C7,
    0x001300C8,
    0x001300C9,
    0x001300CA,
    0x001300CB,
    0x001300CC,
    0x001300CD,
    0x001300CE
};

extern UnkBoard8* mbMapScrollArrow;
extern s16 mbMapScrollArrowPos[][2];
extern Vec2f mbMapScrollPos;

static void MBMapScrollArrowObjMain(omObjData* arg0) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mbMapScrollArrowPos[i][0] += mbMapScrollArrowVelTbl[i][0];
        mbMapScrollArrowPos[i][1] += mbMapScrollArrowVelTbl[i][1];

        if (mbMapScrollArrowVelTbl[i][0] < 0) {
            if (mbMapScrollArrowPos[i][0] < mbMapScrollArrowPosTbl[i][0]) {
                mbMapScrollArrowPos[i][0] = mbMapScrollArrowPosTbl[i][0];
            }
        }

        if (mbMapScrollArrowVelTbl[i][0] > 0) {
            if (mbMapScrollArrowPos[i][0] > mbMapScrollArrowPosTbl[i][0]) {
                mbMapScrollArrowPos[i][0] = mbMapScrollArrowPosTbl[i][0];
            }
        }

        if (mbMapScrollArrowVelTbl[i][1] < 0) {
            if (mbMapScrollArrowPos[i][1] < mbMapScrollArrowPosTbl[i][1]) {
                mbMapScrollArrowPos[i][1] = mbMapScrollArrowPosTbl[i][1];
            }
        }

        if (mbMapScrollArrowVelTbl[i][1] > 0) {
            if (mbMapScrollArrowPos[i][1] > mbMapScrollArrowPosTbl[i][1]) {
                mbMapScrollArrowPos[i][1] = mbMapScrollArrowPosTbl[i][1];
            }
        }
        HuSprPosSet(mbMapScrollArrow->spriteGroup, i, mbMapScrollArrowPos[i][0], mbMapScrollArrowPos[i][1]);
    }
}

static UnkBoard8* MBMapScrollArrowCreate(void) {
    UnkBoard8* temp_v0;
    s32 i;
    void* temp_s4;

    temp_v0 = MBSprGrpCreate(5, 0);
    mbMapScrollArrow = temp_v0;
    temp_s4 = DataRead(0x1301D4);

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        temp_v0->model[i] = HuSprAnimRead(temp_s4);
        HuSprGrpMemberSet(temp_v0->spriteGroup, i, temp_v0->model[i], 0);
        HuSprPriSet(temp_v0->spriteGroup, i, 0U);
        HuSprDispOff(temp_v0->spriteGroup, i);
        HuSprPosSet(temp_v0->spriteGroup, i, mbMapScrollArrowStartTbl[i][0], mbMapScrollArrowStartTbl[i][1]);
        mbMapScrollArrowPos[i][0] = mbMapScrollArrowStartTbl[i][0];
        mbMapScrollArrowPos[i][1] = mbMapScrollArrowStartTbl[i][1];
        HuSprZRotSet(temp_v0->spriteGroup, i, mbMapScrollArrowRotTbl[i]);
    }

    DataClose(temp_s4);
    mbMapScrollArrowObj = omAddObj(0x1000, 0U, 0U, -1, MBMapScrollArrowObjMain);
    omSetStatBit(mbMapScrollArrowObj, OM_STAT_NOPAUSE);
    return temp_v0;
}

static void MBMapScrollArrowKill(UnkBoard8* arg0) {
    omDelObj(mbMapScrollArrowObj);
    MBSprGrpKill(arg0);
}

static void MBMapScrollArrowDispSet(UnkBoard8* arg0, u16 arg1) {
    s32 i;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((arg1 >> i) & 1) {
            HuSprDispOff(arg0->spriteGroup, i);
        } else {
            HuSprDispOn(arg0->spriteGroup, i);
        }
    }
}

void MBPlayerIconMdlSet(void) {
    GW_PLAYER* temp_a1;
    s32 i;
    Object* temp_a0_2;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        temp_a1 = MBPlayerGet(i);
        if (GwPlayer[i].itemTurn != 0) {
            mbMapScrollMdlTbl[i] = MBModelFileCreate(mbMapScrollKSuitIconMdlTbl[temp_a1->chr], 9, 1.0f, mbMapScrollShadowSizeTbl[temp_a1->chr], NULL);
        } else {
            mbMapScrollMdlTbl[i] = MBModelFileCreate(mbMapScrollIconMdlTbl[temp_a1->chr], 9, 1.0f, mbMapScrollShadowSizeTbl[temp_a1->chr], NULL);
        }

        Hu3DModelScaleSet(mbMapScrollMdlTbl[i]->omObj1->model[0], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(mbMapScrollMdlTbl[i]->omObj2->model[0], 0.0f, 0.0f, 0.0f);
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        temp_a1 = MBPlayerGet(i);
        temp_a0_2 = temp_a1->player_obj;
        temp_a1->player_obj = mbMapScrollMdlTbl[i];
        mbMapScrollMdlTbl[i] = temp_a0_2;
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBPlayerPosFixSet(i, 1);
    }

    
    HuPrcVSleep();

    if (mbKSuitMdl != NULL) {
        MBModelDispOff(mbKSuitMdl);
    }
    
    for (i = 0; i < MB_MAX_PLAYERS; i++){
        MBModelDispOff(mbMapScrollMdlTbl[i]);
    }
}

void MBPlayerIconMdlReset(void) {
    GW_PLAYER* player;
    Object* temp_a0;
    s32 i;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        player = MBPlayerGet(i);
        temp_a0 = player->player_obj;
        player->player_obj = mbMapScrollMdlTbl[i];
        mbMapScrollMdlTbl[i] = temp_a0;
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        player = MBPlayerGet(i);
        if (GwPlayer[i].itemTurn == 0) {
            MBModelDispOn(player->player_obj);
        }
        MBModelKill(mbMapScrollMdlTbl[i]);
    }
    
    if (mbKSuitMdl != NULL) {
        MBModelDispOn(mbKSuitMdl);
    }
}

static void MBMapScrollIconSet(void) {
    MBPlayerIconMdlSet();
}

static void MBMapScrollIconReset(void) {
    MBPlayerIconMdlReset();
    MBStatusShowAll();
}

static void MBMapScrollProc(void) {
    Vec2f sp10;
    Unk3* temp_s6;
    Unk3* var_s4;
    UnkBoard8* temp_s3;
    f32 temp_f20;
    f32 temp_f22;
    s32 temp_s2;
    s16 var_s1;
    s32 var_s7;
    u16* temp_s0;
    s32 temp;

    var_s4 = NULL;
    temp_s2 = (s32)HuPrcCurrentGet()->user_data;
    var_s7 = 0;
    var_s1 = 0;
    
    temp_f22 = MBCameraSpeedGet();
    
    if (MBOvlCallCheck() == 0) {
        var_s7 = MBSaiNumKill(GwSystem.current_player_index);
        MBSaiMdlDispOff(GwSystem.current_player_index);
        if (mbSubMusNo != -1) {
            msmMusSetVolume(mbSubMusNo, 0x60);
        } else {
            HuAudSeqVolSet(0x60);
        }
    }
    
    MBMapScrollIconSet();
    temp_s3 = MBMapScrollArrowCreate();
    temp_s6 = MBHelpWinCreate(4, 0xA0, 0);
    
    if (mbWalkNum != 0) {
        var_s4 = MBHelpWinCreate(6, 0x3C, 0);
    }
    MBCameraSpeedSet(4.0f);
    while (1) {
        s16 temp2 = 16;
        HuPrcVSleep();
        MBCameraPos2DGet(&sp10);
        temp = MBCameraPos2DSet(&sp10);
        MBMapScrollArrowDispSet(temp_s3, temp);
        if (ContBtn[temp_s2] & 0x200) {
            sp10.x -= 16.0f;
            var_s1 = 0xF;
        }
        if (ContBtn[temp_s2] & 0x100) {
            sp10.x += temp2;
            var_s1 = 0xF;
        }
        if (ContBtn[temp_s2] & 0x800) {
            sp10.y -= temp2;
            var_s1 = 0xF;
        }
        if (ContBtn[temp_s2] & 0x400) {
            sp10.y += temp2;
            var_s1 = 0xF;
        }
        MBCameraPos2DSet(&sp10);
        if (var_s1 != 0) {
            var_s1 -= 1;
            MBStatusHideAll();
        } else {
            MBStatusShowAll();
        }

        if (GwPlayer[GwSystem.current_player_index].stat & 1) {
            HuWinComKeyReset();
            break;
        }
        if (mbCameraBtnF == 0) {
            break;
        }
        if (ContBtnDown[temp_s2] & (A_BUTTON | B_BUTTON | Z_TRIG | R_TRIG)) {
            break;
        }
    }       
    
    MBHelpWinKill(temp_s6);
    if (var_s4 != NULL) {
        MBHelpWinKill(var_s4);
    }
    MBMapScrollArrowKill(temp_s3);
    WipeCreateOut(WIPE_TYPE_NORMAL, 4);
    HuPrcSleep(4);
    if ((MBOvlCallCheck()) == 0) {
        MBBackStreamStop();
        MBBackStreamStart();
        MBCameraSpeedSet(-1.0f);
        temp_f20 = MBCameraSpeedDivGet();
        MBCameraSpeedDivSet(1.0f);
        MBBackThreadPriHighSet();
        MBCameraZoomSet(mbMapScrollZoom);
        MBCameraPos2DSet(&mbMapScrollPos);
        HuPrcVSleep();
        MBCameraSpeedDivSet(temp_f20);
        
        if (var_s7 != 0) {
            MBSaiNumShow(GwSystem.current_player_index);
        }
        
        MBSaiMdlDispOn(GwSystem.current_player_index);
        MBMapScrollIconReset();
        
        if (mbSubMusNo != -1) {
            msmMusSetVolume(mbSubMusNo, 0x7F);
        } else {
            HuAudSeqVolSet(0x7F);
        }
        
        WipeCreateIn(WIPE_TYPE_NORMAL, 4);
        HuPrcSleep(4);
    } else {
        MBMapScrollIconReset();
    }
    MBCameraSpeedSet(temp_f22);
    omDelPrcObj(NULL);
}


static void MBMapScrollFocusProc(void) {
    while (1) {
        MBCameraPos3DSet(&GwPlayer[GwSystem.current_player_index].player_obj->coords);
        HuPrcVSleep();        
    }
}

void MBMapScrollExec(s32 arg0) {
    Process* temp_s0;
    Process* temp_v0;

    mbMapScrollZoom = MBCameraZoomGet();
    MBCameraPos2DGet(&mbMapScrollPos);
    winPauseF = 1;
    omAllPause();
    MBBackThreadPriLowSet();
    temp_v0 = omAddPrcObj(MBMapScrollFocusProc, 0x1005, 0, 0);
    omPrcSetStatBit(temp_v0, OM_STAT_NOPAUSE);
    HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.0f));
    HuPrcChildWatch();
    omDelPrcObj(temp_v0);
    temp_s0 = HuPrcCurrentGet();
    temp_v0 = omAddPrcObj(MBMapScrollProc, 0x1005, 0, 0);
    temp_v0->user_data = (void*)arg0;
    omPrcSetStatBit(temp_v0, OM_STAT_NOALLPAUSE);
    HuPrcChildLink(temp_s0, temp_v0);
    HuPrcChildWatch();
    omAllUPause();
    winPauseF = 0;
    MBBackThreadPriHighSet();
}
