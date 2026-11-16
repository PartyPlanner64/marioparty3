#include "common_board.h"
#include "game/board.h"
#include "mapfull.h"
#include "vec.h"
#include "back.h"
#include "status.h"
#include "sprgrp.h"
#include "player.h"
#include "sai.h"
#include "helpwin.h"

typedef struct StarGlowData {
    s16 x;
    s16 y;
} StarGlowData; //sizeof 0x4

s32 mbMapFullIconSprTbl[] = {
    0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F,
    0x1301CF, 0x1301D0, 0x1301D1, 0x1301D2, 0x1301DD
};
s16 mbMapFullCursorMoveTbl[][4] = {
    { 0, 2, 0, 1 },
    { 0, 2, -1, 0 },
    { -2, 0, 0, 1 },
    { -2, 0, -1, 0 }
};
s16 mbMapFullPlayerXTbl[] = { 66, 252, 66, 252 };
s16 mbMapFullPlayerYTbl[] = { 30, 30, 210, 210 };
s32 mbMapFullCharSprTbl[] = { 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F };
s32 mbMapFullCharNameSprTbl[] = { 0x1301D5, 0x1301D6, 0x1301D7, 0x1301D8, 0x1301D9, 0x1301DA, 0x1301DB, 0x1301DC };

extern s32 mbMapFullBackNo;
extern s16 mbMapFullIconNum;
extern UnkBoard6 mbMapFullIconTbl[32];
extern s16 mbMapFullPlayerScrXTbl[];
extern s16 mbMapFullPlayerScrYTbl[];
extern UnkBoard8* mbMapFullLineTbl[];
extern s16 mbMapFullSel;
extern s32 mbBackNo;

void MBMapFullInit(s32 arg0) {
    s32 i;

    mbMapFullBackNo = arg0;
    for (i = 0; i < ARRAY_COUNT(mbMapFullIconTbl); i++) {
        mbMapFullIconTbl[i].unk_00 = -1;
    }

    mbMapFullIconNum = 0;
}

void MBMapFullClose(void) {
}

s32 MBMapFullIconMdlAdd(s8 arg0, Object* arg1, s16 arg2, s16 arg3) {
    UnkBoard6* temp_v0;

    temp_v0 = &mbMapFullIconTbl[mbMapFullIconNum++];
    temp_v0->unk_00 = arg0;
    temp_v0->unk4 = arg1;
    temp_v0->unkC = arg2;
    temp_v0->unkE = arg3;
    return mbMapFullIconNum - 1;
}

void MBMapFullIconRemove(s32 arg0) {
    mbMapFullIconTbl[arg0].unk_00 = -1;
}

void MBMapFullIconPosAdd(s8 arg0, Vec* arg1, s16 arg2, s16 arg3) {
    UnkBoard6* temp_v1;

    temp_v1 = &mbMapFullIconTbl[mbMapFullIconNum++];
    temp_v1->unk_00 = arg0;
    temp_v1->unk4 = 0;
    temp_v1->unkC = arg2;
    temp_v1->unkE = arg3;
    HuVecCopy3F(&temp_v1->unk10, arg1);
}

static void MBMapFullStarGlowKill(void) {
    UnkBoard6 *entry;
    s32 i;
    
    for (i = 0; i < ARRAY_COUNT(mbMapFullIconTbl); i++) {
        entry = &mbMapFullIconTbl[i];
        if (entry->unk_00 >= 0) {
            if (entry->process != NULL) {
                omDelPrcObj(entry->process);
            }
            entry->process = NULL;
        }
    }
}

static void MBMapFullStarGrow(void) {
    f32 temp_f0;
    f32 var_f20;
    f32 var_f22;
    StarGlowData* temp_s0;
    s32 temp;

    temp_s0 = HuPrcCurrentGet()->user_data;
    var_f20 = 0.0f;
    var_f22 = 0.0f;
    while (1) {
        temp_f0 = sindf(var_f22);
        temp_f0 = ((temp_f0 < 0.0f)) ? -temp_f0 : temp_f0;

        temp = (s32) (temp_f0 * 255.0f);
        var_f22 += 6.0f;
        
        if (var_f22 > 360.0f) {
            var_f22 -= 360.0f;
        }
        
        HuSprColorTPLvlSet(temp_s0->x, temp_s0->y, 0xFF, temp, 0, 0xC0);

        temp_f0 = sindf(var_f20);
        temp_f0 = (temp_f0 < 0.0f) ? 0.0f : 0.2f;
        
        var_f20 += 15.0f;
        if (var_f20 > 360.0f) {
            var_f20 -= 360.0f;
        }

        HuSprScaleSet(temp_s0->x, temp_s0->y, temp_f0 + 1.0f, temp_f0 + 1.0f);
        HuPrcVSleep();        
    }
}

static Process* MBMapFullStarGlowCreate(s16 xPos, s16 yPos) {
    StarGlowData* starGlowData;
    Process* starGlowProc;

    starGlowProc = omAddPrcObj(MBMapFullStarGrow, 0x1005, 0, 0x40);
    starGlowData = HuMemMemoryAlloc(starGlowProc->heap, sizeof(StarGlowData));
    starGlowProc->user_data = starGlowData;
    starGlowData->x = xPos;
    starGlowData->y = yPos;
    return starGlowProc;
}

static void MBMapFullLinePosFix(UnkBoard8* arg0, s16 arg1) {
    Vec sp10;
    f32 vecAngle;

    HuSprPosSet(arg0->spriteGroup, 0, mbMapFullPlayerXTbl[arg1], mbMapFullPlayerYTbl[arg1]);
    HuSprPosSet(arg0->spriteGroup, 1, mbMapFullPlayerXTbl[arg1], mbMapFullPlayerYTbl[arg1]);
    sp10.x = mbMapFullPlayerScrXTbl[arg1] - mbMapFullPlayerXTbl[arg1];
    sp10.y = 0;
    sp10.z = mbMapFullPlayerScrYTbl[arg1] - mbMapFullPlayerYTbl[arg1];
    vecAngle = MBVecAngleGet(&sp10);
    HuSprScaleSet(arg0->spriteGroup, 0, 0.25f, HuSqrtf((sp10.x * sp10.x) + (sp10.z * sp10.z)) / 32.0f);
    HuSprZRotSet(arg0->spriteGroup, 0, vecAngle);
}

void MBMapFullLineCreate(void) {
    UnkBoard8* temp_s0;
    s32 i;
    void* temp_v0;
    void* temp_v0_2;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        temp_s0 = MBSprGrpCreate(2, 0);
        temp_v0 = DataRead(0x1301CE);
        temp_s0->model[0] = HuSprAnimRead(temp_v0);
        HuSprGrpMemberSet(temp_s0->spriteGroup, 0, temp_s0->model[0], 0);
        HuSprAttrSet(temp_s0->spriteGroup, 0, 0x01001808);
        HuSprPriSet(temp_s0->spriteGroup, 0, 2);
        HuSprColorTPLvlSet(temp_s0->spriteGroup, 0, 0, 0, 0xFF, 0x80);
        DataClose(temp_v0);
        temp_v0_2 = DataRead(0x1301CD);
        temp_s0->model[1] = HuSprAnimRead(temp_v0_2);
        HuSprGrpMemberSet(temp_s0->spriteGroup, 1, temp_s0->model[1], 0);
        HuSprAttrSet(temp_s0->spriteGroup, 1, 0x01001808);
        HuSprPriSet(temp_s0->spriteGroup, 1, 2);
        HuSprColorTPLvlSet(temp_s0->spriteGroup, 1, 0, 0, 0xFF, 0x80);
        DataClose(temp_v0_2);
        MBMapFullLinePosFix(temp_s0, i);
        mbMapFullLineTbl[i] = temp_s0;
    }
}

void MBMapFullLineKill(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        MBSprGrpKill(mbMapFullLineTbl[i]);
    }
}

static void MBMapFullLineFlash(void) {
    UnkBoard8 *entry;
    s16 sel;
    s32 i;
    s16 alpha;
    f32 angle;

    sel = -1;
    angle = 90.0f;

    while (1) {
        //TODO: matching hack
        if (entry->spriteGroup) {
            HuPrcVSleep();
        } else {
            HuPrcVSleep();
        }
        
        if (sel != mbMapFullSel) {
            sel = mbMapFullSel;
            for (i = 0; i < 4; i++) {
                entry = mbMapFullLineTbl[i];
                if (i == sel) {
                    HuSprPriSet(entry->spriteGroup, 0, 2);
                    HuSprPriSet(entry->spriteGroup, 1, 2);
                } else {
                    HuSprColorTPLvlSet(entry->spriteGroup, 0, 0, 0, 0xFF, 0xA0);
                    HuSprColorTPLvlSet(entry->spriteGroup, 1, 0, 0, 0xFF, 0xFF);
                    HuSprPriSet(entry->spriteGroup, 0, 3);
                    HuSprPriSet(entry->spriteGroup, 1, 3);
                }
                
                HuSprDispOn(entry->spriteGroup, 0);
                HuSprDispOn(entry->spriteGroup, 1);
            }
        }

        entry = mbMapFullLineTbl[sel];
        alpha = (sindf(angle) * 255.0f);
        alpha = (alpha < 0) ? -alpha : alpha;
        
        angle += 6.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
 
        HuSprColorTPLvlSet(entry->spriteGroup, 0, 0xFF, alpha, 0, 0xA0);
        HuSprColorTPLvlSet(entry->spriteGroup, 1, 0xFF, alpha, 0, 0xFF);
    }
}

static void MBMapFullMain(void) {
    Vec2f sp10;
    f32 sp18[2];            /* MBCamera3Dto2D target (sp18/sp1C) */
    s32 userData;        /* sp24 */
    s32 savedBack;       /* sp2C */
    s16 sel;             /* sp36 */
    Process *lineFlash;  /* sp3C */
    GW_PLAYER *player;
    UnkBoard6 *entry;
    UnkBoard8 *iconGrp;  /* temp_fp */
    UnkBoard8 *charGrp;  /* temp_s6 */
    Unk3 *help0, *help1;
    Vec *pos;
    f32 savedZoom;
    s16 mid, y;
    s16 dir;
    s32 i, j, k;
    void *data;

    userData = (s32)HuPrcCurrentGet()->user_data; //this is correct, usage is strange here
    savedBack = mbBackNo;
    sel = 0;

    for (i = 0; i < 4; i++) {
        if (MBPlayerComCheck(i) != 0) {
            continue;
        }
        if (GwPlayer[i].pad == userData) {
            sel = i;
            break;
        }
    }

    mbMapFullSel = sel;
    savedZoom = MBCameraZoomGet();
    MBCameraPos2DGet(&sp10);
    WipeCreateOut(WIPE_TYPE_NORMAL, 8);
    HuPrcSleep(8);
    MBBackSprDispOff();
    MBStatusHideAll();
    MBSaiMdlDispOff(userData);
    HuPrcVSleep();
    Hu3DPauseF = 1;
    mbModelDispFlag &= ~1;
    MBSaiNumKill(GwSystem.current_player_index);
    MBSaiMdlDispOff(GwSystem.current_player_index);
    MBMasuBmpModeSet(1);
    MBBackKill();
    MBBackLoad(mbMapFullBackNo);
    iconGrp = MBSprGrpCreate(0x20, 0);

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        player = MBPlayerGet(i);
        MBCamera3Dto2D(&MBMasuGet(MBMasuLinkMasuIdGet(player->clink, player->cidx))->coords, sp18);
        mbMapFullPlayerScrXTbl[i] = sp18[0];
        mbMapFullPlayerScrYTbl[i] = sp18[1];
    }

    
    for (i = 0, j = 0; j < ARRAY_COUNT(mbMapFullIconTbl); i++, j++) {
        entry = &mbMapFullIconTbl[j];
        if (entry->unk_00 >= 0) {
            data = DataRead(mbMapFullIconSprTbl[entry->unk_00]);
            iconGrp->model[i] = HuSprAnimRead(data);
            HuSprGrpMemberSet(iconGrp->spriteGroup, i, iconGrp->model[i], 0);
            HuSprAttrSet(iconGrp->spriteGroup, i, 0x01001000);
            if (entry->unk4 != NULL) {
                MBCamera3Dto2D(&entry->unk4->coords, sp18);
            } else {
                MBCamera3Dto2D(&entry->unk10, sp18);
            }
            
            mid = (s32)sp18[0] + entry->unkC;
            y   = (s32)sp18[1] + entry->unkE;
            HuSprPosSet(iconGrp->spriteGroup, i, mid, y);
            HuSprPriSet(iconGrp->spriteGroup, i, ~y);
            DataClose(data);
            if (entry->unk_00 == 0xB) {
                i++;
                data = DataRead(0x1301D3);
                iconGrp->model[i] = HuSprAnimRead(data);
                HuSprGrpMemberSet(iconGrp->spriteGroup, i, iconGrp->model[i], 0);
                HuSprAttrSet(iconGrp->spriteGroup, i, 0x01001808);
                HuSprPosSet(iconGrp->spriteGroup, i, mid, y - 1);
                HuSprPriSet(iconGrp->spriteGroup, i, 0xFFFF);
                DataClose(data);
                entry->process = MBMapFullStarGlowCreate(iconGrp->spriteGroup, i);
            }
        }
    }

    MBMapFullLineCreate();
    lineFlash = omAddPrcObj(MBMapFullLineFlash, 0x1005, 0, 0);
    charGrp = MBSprGrpCreate(8, 0);

    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        data = DataRead(mbMapFullCharSprTbl[player->chr]);
        charGrp->model[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(charGrp->spriteGroup, i, charGrp->model[i], 0);
        HuSprPriSet(charGrp->spriteGroup, i, 1);
        HuSprAttrSet(charGrp->spriteGroup, i, 0x01001000);
        HuSprPosSet(charGrp->spriteGroup, i,
                            mbMapFullPlayerXTbl[i] - 0x1E,
                            mbMapFullPlayerYTbl[i]);
        DataClose(data);

        data = DataRead(mbMapFullCharNameSprTbl[player->chr]);
        charGrp->model[i+4] = HuSprAnimRead(data);
        HuSprGrpMemberSet(charGrp->spriteGroup, i + 4, charGrp->model[i + 4], 0);
        HuSprPriSet(charGrp->spriteGroup, i + 4, 1);
        HuSprAttrSet(charGrp->spriteGroup, i + 4, 0x01001000);
        HuSprPosSet(charGrp->spriteGroup, i + 4,
                            mbMapFullPlayerXTbl[i] + 8,
                            mbMapFullPlayerYTbl[i]);
        DataClose(data);
    }

    HuAudSeqVolSet(0x60);
    WipeCreateIn(WIPE_TYPE_NORMAL, 8);
    HuPrcSleep(7);
    help0 = MBHelpWinCreate(0, 0xC0, 0);
    help1 = MBHelpWinCreate(4, 0xCE, 0);

    do {
        u16 pad;
        HuPrcVSleep();
        pad = ContBtnDown[userData];
        dir = -((pad & 0x800) == 0);
        if (pad & 0x400) {
            dir = 1;
        }
        if (ContBtnDown[userData] & L_JPAD) {
            dir = 2;
        }
        if (ContBtnDown[userData] & R_JPAD) {
            dir = 3;
        }
        if (dir != -1) {
            sel += mbMapFullCursorMoveTbl[sel][dir];
        }
        mbMapFullSel = sel;
    } while (!(HuPadBtnDown[userData] & (A_BUTTON | B_BUTTON | Z_TRIG | R_TRIG)));

    WipeCreateOut(WIPE_TYPE_NORMAL, 8);
    HuPrcSleep(8);
    Hu3DPauseF = 0;
    MBBackKill();
    MBBackLoad(savedBack);
    MBCameraZoomSet(savedZoom);
    MBCameraPos2DSet(&sp10);
    HuPrcVSleep();
    mbModelDispFlag |= 1;
    MBSaiNumShow(GwSystem.current_player_index);
    MBSaiMdlDispOn(GwSystem.current_player_index);
    MBHelpWinKill(help0);
    MBHelpWinKill(help1);
    omDelPrcObj(lineFlash);
    MBSprGrpKill(charGrp);
    MBSprGrpKill(iconGrp);
    MBMapFullLineKill();
    MBMapFullStarGlowKill();
    MBBackSprDispOn();
    MBSaiMdlDispOn(userData);
    MBStatusShowAll();
    MBMasuBmpModeSet(0);
    HuAudSeqVolSet(0x7F);
    WipeCreateIn(WIPE_TYPE_NORMAL, 8);
    HuPrcSleep(8);
    omDelPrcObj(NULL);
}

void MBMapFullExec(s32 playerPadNo) {
    Process* temp_s1;
    Process* temp_v0;

    winPauseF = 1;
    omAllPause();
    temp_s1 = HuPrcCurrentGet();
    temp_v0 = omAddPrcObj(MBMapFullMain, 0x1005, 0, 0);
    temp_v0->user_data = (void*)playerPadNo;
    omPrcSetStatBit(temp_v0, OM_STAT_NOALLPAUSE);
    HuPrcChildLink(temp_s1, temp_v0);
    HuPrcChildWatch();
    omAllUPause();
    winPauseF = 0;
}
