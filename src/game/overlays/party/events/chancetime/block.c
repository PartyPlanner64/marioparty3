#include "common.h"
#include "chancetime.h"
#include "game/window.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/status.h"

typedef struct ChanceTimeAmount {
    /* 0x00 */ s16 coins;
    /* 0x02 */ s16 stars;
} ChanceTimeAmount; // size = 0x4

typedef struct ChanceTimeReelSpeed {
    /* 0x00 */ f32 accel;
    /* 0x04 */ f32 max;
} ChanceTimeReelSpeed; // size = 0x8

extern char *chancetime_reelAnimNameTbl[3];
extern s32 chancetime_reelStartCnt;
extern s32 chancetime_reelSeOnTbl[3];
extern s32 chancetime_panelHopF;
extern s32 chancetime_introMesDoneF;
extern s32 chancetime_blockSpinDoneF;
extern s32 chancetime_transferDoneF;
extern s32 chancetime_blockSpinTimer;
extern const u8 chancetime_actionReelTierTbl[3][13];
extern const ChanceTimeReelSpeed chancetime_reelSpeedTbl[3];
extern const Vec chancetime_reelPosTbl[3];
extern const u32 chancetime_blockMesTbl[3];
extern const ChanceTimeAmount chancetime_actionAmountTbl[9];
extern const u32 chancetime_actionMesTbl[9];
extern const u32 chancetime_actionShortMesTbl[9];
extern const u32 chancetime_actionNoneMesTbl[9];
extern const u32 chancetime_actionAmountMesTbl[9];
extern const u32 chancetime_chrNameMesTbl[8];
extern const ChanceTimeAmount chancetime_actionMesAmountTbl[9];
extern s16 chancetime_blockHatenaSprTbl[3];
extern u16 chancetime_panelFrameSpr;
extern s32 chancetime_unusedCnt;
extern ChanceTimeTransfer chancetime_transferTbl[20];
extern ChanceTimeReel chancetime_reelTbl[3];
extern s16 chancetime_reelAnimTbl[3][3];
extern s8 chancetime_actionReelItemNum;
extern u8 chancetime_actionReelItemTbl[];
extern s32 chancetime_reelSeTbl[3];
extern s8 chancetime_unusedOnF;
extern s8 chancetime_unusedOffF;
extern s8 chancetime_reelStartNo;
extern s32 chancetime_eventWin;
extern s16 chancetime_starEffTbl[10];
extern s16 chancetime_coinSprTbl[20];
extern omObjData *chancetime_eventObj;
extern s32 chancetime_blockSpinNo;
extern void (*chancetime_eventFunc)();
extern omObjData *chancetime_blockObj;
extern s8 chancetime_blockResultTbl[3];
extern s8 chancetime_actionNo;
extern void (*chancetime_blockFunc)(omObjData *);
extern s16 chancetime_panelHookMdl;
extern s16 chancetime_panelSprAnim;
extern HuSprite *chancetime_panelSpr;
extern void *chancetime_panelTex;
extern void *chancetime_panelPal;
extern s16 chancetime_panelSize[2];

s32 chancetime_HostHopCheck(void);
void chancetime_PanelLand(omObjData *object);
void chancetime_BlockReelMain(omObjData *object);
void chancetime_BlockDestroy(void);
void chancetime_PanelDraw(Gfx **gfxPos, s32 arg1, s32 arg2);
void chancetime_ReelInit(s8 arg0);
void chancetime_ReelDispOffAll(void);
void chancetime_PanelDrop(omObjData *object);
void chancetime_ResultMesExec(s32 arg0, s32 arg1, s32 arg2);
void chancetime_ReelUpdate(omObjData *object);
void chancetime_ReelDispOn(s8 arg0);
void chancetime_EventDestroy(void);
void chancetime_EventIdle(void);
void chancetime_ReelStart(s8 arg0);
void chancetime_BlockSpinMesExec(void);
void chancetime_BlockSpinReelStart(void);
void chancetime_BlockSpinWait(void);
void chancetime_TransferExec(omObjData *object);
void chancetime_TransferAnimExec(omObjData *object);
void chancetime_TransferMesExec(omObjData *object);
void chancetime_IntroMesExec(void);
void chancetime_IntroMesEnd(void);

s8 chancetime_panelDropF = 0;
s8 chancetime_panelLandF = 0;
s16 chancetime_panelPos[2] = { 0, -240 };
f32 chancetime_panelDropY = 600.0f;
f32 chancetime_panelDropSpeed = 0.0f;
Vec chancetime_panelItemPosTbl[6] = {
    { -138.0f, 406.0f, -216.0f },
    { 152.0f, 406.0f, -216.0f },
    { 7.0f, 146.0f, -216.0f },
    { -150.0f, -30.0f, -216.0f },
    { 0.0f, -30.0f, -216.0f },
    { 150.0f, -30.0f, -216.0f },
};

void chancetime_BlockProc(void) {
    omObjData *obj;
    void *data;
    s8 i;
    s32 spriteId;
    s16 grp;
    HuSprite *spr;

    obj = omAddObj(20, 16, 0, -1, NULL);
    chancetime_blockObj = obj;

    obj->model[1] = Hu3DModelRead(0x1C0009, 0x229);
    data = DataRead(0x1C0002);
    chancetime_reelAnimTbl[0][0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, chancetime_reelAnimNameTbl[0]);
    Hu3DAnimAttrSet(chancetime_reelAnimTbl[0][0], 1, 1);
    Hu3DAnimBankSet(chancetime_reelAnimTbl[0][0], 0);
    HuMemMemoryFreePerm(data);
    for (i = 1; i < 3; i++) {
        chancetime_reelAnimTbl[0][i] =
            Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, chancetime_reelAnimTbl[0][0], 0, chancetime_reelAnimNameTbl[i]);
        Hu3DAnimAttrSet(chancetime_reelAnimTbl[0][i], 1, 1);
        Hu3DAnimBankSet(chancetime_reelAnimTbl[0][i], 0);
    }
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 0);
    Hu3DModelCameraSet(obj->model[1], 1);

    obj->model[2] = Hu3DModelRead(0x1C0009, 0x229);
    for (i = 0; i < 3; i++) {
        chancetime_reelAnimTbl[1][i] =
            Hu3DAnimLink(Hu3DData[obj->model[2]].hmf, chancetime_reelAnimTbl[0][0], 0, chancetime_reelAnimNameTbl[i]);
        Hu3DAnimAttrSet(chancetime_reelAnimTbl[1][i], 1, 1);
        Hu3DAnimBankSet(chancetime_reelAnimTbl[1][i], 0);
    }
    Hu3DModelRemakeStatic(obj->model[2]);
    Hu3DModelDynamicFree(obj->model[2]);
    Hu3DMotionAttrSet(obj->model[2], 2, 0);
    Hu3DModelCameraSet(obj->model[2], 1);

    obj->model[3] = Hu3DModelRead(0x1C0009, 0x229);
    data = DataRead(0x1C0003);
    chancetime_reelAnimTbl[2][0] = Hu3DAnimCreate(Hu3DData[obj->model[3]].hmf, data, 0, chancetime_reelAnimNameTbl[0]);
    Hu3DAnimAttrSet(chancetime_reelAnimTbl[2][0], 1, 1);
    Hu3DAnimBankSet(chancetime_reelAnimTbl[2][0], 0);
    HuMemMemoryFreePerm(data);
    for (i = 1; i < 3; i++) {
        chancetime_reelAnimTbl[2][i] =
            Hu3DAnimLink(Hu3DData[obj->model[3]].hmf, chancetime_reelAnimTbl[2][0], 0, chancetime_reelAnimNameTbl[i]);
        Hu3DAnimAttrSet(chancetime_reelAnimTbl[2][i], 1, 1);
        Hu3DAnimBankSet(chancetime_reelAnimTbl[2][i], 0);
    }
    Hu3DModelRemakeStatic(obj->model[3]);
    Hu3DModelDynamicFree(obj->model[3]);
    Hu3DMotionAttrSet(obj->model[3], 2, 0);
    Hu3DModelCameraSet(obj->model[3], 1);

    spriteId = HuSprAnimDataRead(0x1C0000);
    chancetime_panelSprAnim = spriteId;
    grp = HuSprGrpCreate(1, 0);
    HuSprAttrSet(grp, 0, HUSPR_ATTR_DISPOFF);
    HuSprGrpMemberSet(grp, 0, spriteId, 0);
    chancetime_panelSpr = spr = HuSprGet(grp, 0);
    chancetime_panelTex = spr->data->data;
    chancetime_panelPal = spr->data->pal;
    chancetime_panelSize[0] = spr->data->sizeX;
    chancetime_panelSize[1] = spr->data->sizeY;
    chancetime_panelHookMdl = Hu3DHookFuncCreate(0, chancetime_PanelDraw, 2);
    Hu3DModelCameraSet(chancetime_panelHookMdl, 1);

    data = DataRead(0x1C0007);
    for (i = 0; i < 3; i++) {
        chancetime_blockHatenaSprTbl[i] = espEntry(HuSprAnimRead(data), 0, 0);
        espDispOff(chancetime_blockHatenaSprTbl[i]);
    }
    HuMemMemoryFreePerm(data);
    spriteId = HuSprAnimDataRead(0x1C0004);
    chancetime_panelFrameSpr = espEntry(spriteId, 0, 0);
    espDispOff(chancetime_panelFrameSpr);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[1], -111.0f, 486.0f, -541.0f);
    Hu3DModelPosSet(obj->model[2], 119.0f, 486.0f, -541.0f);
    Hu3DModelPosSet(obj->model[3], 3.0f, 265.0f, -541.0f);
    chancetime_ReelInit(chancetime_turnTier);
    chancetime_ReelDispOffAll();
    omPrcSetDestructor(0, chancetime_BlockDestroy);
    chancetime_blockFunc = chancetime_BlockReelMain;
    while (TRUE) {
        chancetime_blockFunc(obj);
        HuPrcVSleep();
    }
}

void chancetime_BlockReelMain(omObjData *object) {
    chancetime_ReelUpdate(object);
}

void chancetime_PanelDrop(omObjData *object) {
    Vec pos;
    Vec2f screen;

    chancetime_panelDropSpeed += 1.2f;
    chancetime_panelDropSpeed = (chancetime_panelDropSpeed > 30.0f) ? 30.0f : chancetime_panelDropSpeed;
    chancetime_panelDropY -= chancetime_panelDropSpeed;
    if (chancetime_panelDropY < 0.0f) {
        chancetime_panelDropSpeed = chancetime_panelDropSpeed * -0.1f;
        chancetime_panelDropY = 0.0f;
        if (chancetime_panelHopF == 0) {
            chancetime_HostHopStart();
            chancetime_panelHopF = 1;
        }
        if (chancetime_panelDropSpeed >= -0.24000001f) {
            chancetime_panelHopF = 0;
            chancetime_blockFunc = chancetime_PanelLand;
            chancetime_panelDropY = 0.0f;
            return;
        }
    }
    pos.x = 0.0f;
    pos.y = chancetime_panelItemPosTbl[0].y + chancetime_panelDropY - 168.0f;
    pos.z = chancetime_panelItemPosTbl[0].z;
    Hu3D3Dto2D(0, &pos, &screen);
    chancetime_panelPos[0] = 74;
    chancetime_panelPos[1] = screen.y - 120.0f + 25.0f;
    espPosSet(chancetime_panelFrameSpr, 161, chancetime_panelPos[1] + 46);
    espPosSet(chancetime_blockHatenaSprTbl[0], chancetime_panelPos[0] + 51, chancetime_panelPos[1] + 46);
    espPosSet(chancetime_blockHatenaSprTbl[1], chancetime_panelPos[0] + 124, chancetime_panelPos[1] + 46);
    espPosSet(chancetime_blockHatenaSprTbl[2], chancetime_panelPos[0] + 87, chancetime_panelPos[1] + 116);
}

void chancetime_PanelLand(omObjData *object) {
    chancetime_panelPos[0] = 74;
    chancetime_panelPos[1] = 25;
    espPosSet(chancetime_panelFrameSpr, 161, 71);
    espPosSet(chancetime_blockHatenaSprTbl[0], chancetime_panelPos[0] + 51, chancetime_panelPos[1] + 46);
    espPosSet(chancetime_blockHatenaSprTbl[1], chancetime_panelPos[0] + 124, chancetime_panelPos[1] + 46);
    espPosSet(chancetime_blockHatenaSprTbl[2], chancetime_panelPos[0] + 87, chancetime_panelPos[1] + 116);
    if (chancetime_HostHopCheck() == 1) {
        chancetime_panelDropY = 600.0f;
        chancetime_panelDropSpeed = 0.0f;
        chancetime_panelDropF = 0;
        chancetime_panelLandF = 1;
        chancetime_blockFunc = chancetime_BlockReelMain;
    }
}

void chancetime_BlockDestroy(void) {
}

void chancetime_PanelDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
    Gfx *gfx;
    s16 texX[2];
    s16 texY[2];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 screenX;
    s16 screenY;
    s16 texWidth;
    s16 row;
    s16 rows;
    s16 offset;

    width = chancetime_panelSize[0];
    height = chancetime_panelSize[1];
    x = chancetime_panelPos[0];
    y = chancetime_panelPos[1];
    if ((x + width < 0) | (x >= 320)) {
        return;
    }
    if ((y + height < 0) | (y >= 240)) {
        return;
    }

    texX[0] = (x < 0) ? -x : 0;
    texX[1] = (x + width > 320) ? 320 - x : width;
    if (x < 0) {
        screenX = 0;
    } else if (x >= 319) {
        screenX = 319;
    } else {
        screenX = x;
    }
    texWidth = texX[1] - texX[0];
    texY[0] = (y < 0) ? -y : 0;
    texY[1] = (y + height > 240) ? 240 - y : height;
    if (y < 0) {
        screenY = 0;
    } else if (y >= 319) {
        screenY = 319;
    } else {
        screenY = y;
    }

    gfx = *gfxPos;
    gDPPipeSync(gfx++);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetRenderMode(gfx++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, chancetime_panelPal);

    rows = 4;
    offset = 0;
    for (row = texY[0]; row < texY[1]; row += rows) {
        if (row + rows > texY[1]) {
            rows = texY[1] - row;
        }
        gDPLoadTextureTile(gfx++, chancetime_panelTex, G_IM_FMT_CI, G_IM_SIZ_8b, width, rows, texX[0], row, texX[1] - 1, row + rows - 1, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, texWidth << 2, rows << 2);
        gSPTextureRectangle(gfx++, screenX << 2, (offset + screenY) << 2, (texWidth + screenX) << 2, (offset + rows + screenY) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        offset += rows;
    }
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 104, 52, 215, 163);
    *gfxPos = gfx;
}

void chancetime_ReelInit(s8 arg0) {
    s8 i;
    s8 j;
    s8 k;

    chancetime_reelStartCnt = 0;
    for (i = 0; i < 3; i++) {
        chancetime_reelSeOnTbl[i] = 0;
        chancetime_blockResultTbl[i] = -1;
        chancetime_reelTbl[i].unk00 = 0;
        chancetime_reelTbl[i].unk10 = 2;
        chancetime_reelTbl[i].unk12 = 4;
        chancetime_reelTbl[i].unk04 = 0;
        chancetime_reelTbl[i].unk0C = -1.0f;
    }
    for (i = 0; i < 2; i++) {
        k = rand8() & 3;
        for (j = 0; j < 4; j++) {
            chancetime_reelTbl[i].unk1B[k] = GwPlayer[chancetime_playerOrderTbl[j]].chr;
            if (++k >= 4) {
                k = 0;
            }
        }
        chancetime_reelTbl[i].unk1A = 4;
    }
    k = rand8() % 13;
    for (j = 0; j < 13; j++) {
        chancetime_actionReelItemTbl[k] = chancetime_actionReelTierTbl[arg0][j];
        if (++k >= 13) {
            k = 0;
        }
    }
    chancetime_actionReelItemNum = 13;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            chancetime_reelTbl[i].unk14[j] = chancetime_reelAnimTbl[i][j];
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DAnmNoSet(chancetime_reelTbl[i].unk14[j], chancetime_reelTbl[i].unk1B[2 - j]);
        }
    }
}

const u8 chancetime_actionReelTierTbl[3][13] = {
    { 4, 2, 8, 3, 7, 4, 8, 2, 3, 0, 3, 5, 8 },
    { 0, 3, 6, 1, 8, 7, 2, 8, 4, 5, 0, 7, 2 },
    { 1, 7, 5, 4, 7, 1, 0, 6, 2, 0, 7, 8, 6 },
};

char *chancetime_reelAnimNameTbl[3] = { "mar_DEF", "rui_DEF", "pie_DEF" };
char *chancetime_actionAnimNameTbl[3] = { "coin_all_DEF", "coin_x30_DEF", "coin_x20_DEF" }; /* Unreferenced. */
s32 chancetime_reelStartCnt = 0;
s32 chancetime_reelSeOnTbl[3] = { 0 };
s32 chancetime_panelHopF = 0;
s32 chancetime_unusedTbl[3] = { 0 }; /* Unreferenced. */
s32 chancetime_introMesDoneF = 0;
s32 chancetime_blockSpinDoneF = 0;
s32 chancetime_transferDoneF = 0;
s32 chancetime_blockSpinTimer = 0;

void chancetime_ReelUpdate(omObjData *object) {
    ChanceTimeReel *reel;
    s16 idx;
    s16 tmp;
    s8 i;
    s8 j;

    for (i = 0; i < 3; i++) {
        reel = &chancetime_reelTbl[i];
        if (reel->unk00 == 4) {
            reel->unk04 += chancetime_reelSpeedTbl[chancetime_reelStartCnt - 1].accel;
            reel->unk04 = (reel->unk04 > chancetime_reelSpeedTbl[chancetime_reelStartCnt - 1].max)
                              ? chancetime_reelSpeedTbl[chancetime_reelStartCnt - 1].max
                              : reel->unk04;
        }
        if (reel->unk00 == 1) {
            reel->unk0C = ((s32)(reel->unk08 / 100.0f) + 1) * 100.0f;
            reel->unk00 = 2;
        }
        reel->unk08 += reel->unk04;
        reel->unk04 *= 0.98f;
        if (reel->unk00 == 2 && reel->unk08 >= reel->unk0C) {
            reel->unk08 = reel->unk0C;
            reel->unk04 = 0.0f;
            reel->unk00 = 3;
        }
        if (reel->unk08 >= 200.0f) {
            reel->unk08 -= 200.0f;
            reel->unk12 = (reel->unk12 < reel->unk1A) ? reel->unk12 : reel->unk12 - reel->unk1A;
            idx = reel->unk12;
            reel->unk10 = idx;
            for (j = 0; j < 3; j++) {
                Hu3DAnmNoSet(reel->unk14[j], reel->unk1B[idx]);
                tmp = idx - 1;
                tmp = (tmp < 0) ? reel->unk1A + tmp : tmp;
                idx = tmp;
            }
            reel->unk12 += 2;
            reel->unk12 = (reel->unk12 < reel->unk1A) ? reel->unk12 : reel->unk12 - reel->unk1A;
        }
        if (reel->unk00 == 3) {
            tmp = reel->unk10 + (s32)(reel->unk08 / 100.0f) - 2;
            tmp = (tmp < 0) ? reel->unk1A + tmp : tmp;
            tmp = (tmp < reel->unk1A) ? tmp : tmp - reel->unk1A;
            chancetime_blockResultTbl[i] = reel->unk1B[tmp];
            reel->unk00 = 0;
        }
        Hu3DModelPosSet(object->model[i + 1], chancetime_reelPosTbl[i].x,
                        chancetime_reelPosTbl[i].y - reel->unk08, chancetime_reelPosTbl[i].z);
    }
}

void chancetime_ReelStart(s8 arg0) {
    s8 i;
    s8 j;

    chancetime_reelStartCnt++;
    switch (chancetime_reelStartCnt) {
        case 1:
            chancetime_reelSeTbl[0] = HuAudFXPlay(0x4F9);
            chancetime_reelSeOnTbl[0] = 1;
            break;
        case 2:
            chancetime_reelSeTbl[1] = HuAudFXPlay(0x4FA);
            chancetime_reelSeOnTbl[1] = 1;
            break;
        case 3:
            chancetime_reelSeTbl[2] = HuAudFXPlay(0x4FB);
            chancetime_reelSeOnTbl[2] = 1;
            break;
    }
    chancetime_reelTbl[arg0].unk00 = 4;
    if (arg0 < 2 && chancetime_blockResultTbl[1 - arg0] != -1) {
        j = 0;
        for (i = 0; i < 4; i++) {
            if (chancetime_blockResultTbl[1 - arg0] != GwPlayer[chancetime_playerOrderTbl[i]].chr) {
                chancetime_reelTbl[arg0].unk1B[j] = GwPlayer[chancetime_playerOrderTbl[i]].chr;
                j++;
            }
        }
        chancetime_reelTbl[arg0].unk1A = 3;
        for (i = 0; i < 3; i++) {
            Hu3DAnmNoSet(chancetime_reelTbl[arg0].unk14[i], chancetime_reelTbl[arg0].unk1B[2 - i]);
        }
    }
    chancetime_ReelDispOn(arg0);
}

void chancetime_ReelStop(s8 arg0) {
    switch (chancetime_reelStartCnt) {
        case 1:
            if (chancetime_reelSeOnTbl[0] == 1) {
                HuAudFXStop((s16)chancetime_reelSeTbl[0]);
            }
            HuAudFXPlay(0x4FC);
            break;
        case 2:
            if (chancetime_reelSeOnTbl[1] == 1) {
                HuAudFXStop((s16)chancetime_reelSeTbl[1]);
            }
            HuAudFXPlay(0x4FD);
            break;
        case 3:
            if (chancetime_reelSeOnTbl[2] == 1) {
                HuAudFXStop((s16)chancetime_reelSeTbl[2]);
            }
            HuAudFXPlay(0x4FE);
            break;
    }
    chancetime_reelTbl[arg0].unk00 = 1;
}

void chancetime_PanelDropStart(void) {
    s32 i;

    chancetime_panelDropF = 1;
    chancetime_panelLandF = 0;
    for (i = 0; i < 3; i++) {
        espDispOn(chancetime_blockHatenaSprTbl[i]);
    }
    espDispOn(chancetime_panelFrameSpr);
    chancetime_blockFunc = chancetime_PanelDrop;
}

s32 chancetime_PanelLandCheck(void) {
    return chancetime_panelLandF;
}

void chancetime_ReelDispOffAll(void) {
    omObjData *obj = chancetime_blockObj;
    s8 i;

    for (i = 0; i < 3; i++) {
        Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void chancetime_ReelDispOn(s8 arg0) {
    omObjData *obj = chancetime_blockObj;

    espDispOff(chancetime_blockHatenaSprTbl[arg0]);
    Hu3DModelAttrSet(obj->model[arg0 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void chancetime_UnusedFlagOn(void) {
    chancetime_unusedCnt = 0;
    chancetime_unusedOnF = 1;
    chancetime_unusedOffF = 0;
}

void chancetime_UnusedFlagOff(void) {
    chancetime_unusedOnF = 0;
    chancetime_unusedOffF = 1;
}

void chancetime_EventProc(void) {
    omObjData *obj;
    HmfModel *model;
    s16 sprId;
    s8 i;

    obj = omAddObj(0x14, 0x15, 0, -1, NULL);
    chancetime_eventObj = obj;
    model = &Hu3DData[HuSprBGHookMdl];
    model->unk00 = (model->unk00 & 0xF9) | 3;
    Hu3DModelCameraSet(HuSprBGHookMdl, 2);
    sprId = HuSprAnimDataRead(0x210026);
    for (i = 0; i < 20; i++) {
        chancetime_coinSprTbl[i] = espEntry(sprId, 0, 1);
        espPriSet(chancetime_coinSprTbl[i], 0);
        espDispOff(chancetime_coinSprTbl[i]);
        espBankSet(chancetime_coinSprTbl[i], 0, 0);
        espAnimModeSet(chancetime_coinSprTbl[i], 1);
        espScaleSet(chancetime_coinSprTbl[i], 0.5f, 0.5f);
    }
    obj->model[1] = Hu3DModelRead3(0x1301CC, 0x2B9);
    Hu3DModelScaleSet(obj->model[1], 0.5f, 0.5f, 0.5f);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelCameraSet(obj->model[1], 4);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    for (i = 1; i < 10; i++) {
        obj->model[i + 1] = Hu3DModelLink(obj->model[1]);
        Hu3DModelScaleSet(obj->model[i + 1], 0.5f, 0.5f, 0.5f);
        Hu3DModelCameraSet(obj->model[i + 1], 4);
        Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DMotionAttrSet(obj->model[i + 1], 2, 2);
    }
    for (i = 0; i < 10; i++) {
        chancetime_starEffTbl[i] = EffectCreate(0xB0004, 0x6A9);
        EffectParamSet(chancetime_starEffTbl[i], 4.0f, 20.0f, 4.0f);
        EffectRangeSet(chancetime_starEffTbl[i], 60.0f);
        Hu3DModelCameraSet(chancetime_starEffTbl[i], 4);
        Hu3DParticleAttrSet(chancetime_starEffTbl[i], 1, 0);
        Hu3DModelAttrSet(chancetime_starEffTbl[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    chancetime_eventWin = HuWinExCreateStyled(100, 160, 14);
    HuWinExPriSet((s16)chancetime_eventWin, 5);
    if (!(GwPlayer[chancetime_playerOrderTbl[0]].stat & 1)) {
        HuWinActivePlayerSet((s16)chancetime_eventWin, 1 << GwPlayer[chancetime_playerOrderTbl[0]].pad);
    }
    omPrcSetDestructor(0, chancetime_EventDestroy);
    chancetime_eventFunc = chancetime_EventIdle;
    while (TRUE) {
        chancetime_eventFunc(obj);
        HuPrcVSleep();
    }
}

void chancetime_EventDestroy(void) {
}

void chancetime_EventIdle(void) {
}

void chancetime_BlockSpinStart(s32 arg0) {
    chancetime_blockSpinDoneF = 0;
    chancetime_blockSpinNo = (s8)arg0;
    chancetime_eventFunc = chancetime_BlockSpinMesExec;
}

void chancetime_BlockSpinMesExec(void) {
    s32 index = chancetime_blockSpinNo;

    HuWinHomeClear(chancetime_eventWin);
    if (GwPlayer[chancetime_playerOrderTbl[0]].stat & 1) {
        HuWinAttrSet(chancetime_eventWin, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
    }
    chancetime_HostTalkStart();
    HuWinMesSet(chancetime_eventWin, chancetime_blockMesTbl[index], -1, -1);
    HuWinExOpen(chancetime_eventWin, 1);
    while (HuWinStatGet(chancetime_eventWin)) {
        HuPrcVSleep();
    }
    HuWinExClose(chancetime_eventWin, 1);
    chancetime_HostTalkEnd();
    if (GwPlayer[chancetime_playerOrderTbl[0]].stat & 1) {
        HuWinComKeyReset();
    }
    chancetime_reelStartNo = index;
    chancetime_eventFunc = chancetime_BlockSpinReelStart;
}

void chancetime_BlockSpinReelStart(void) {
    chancetime_ReelStart(chancetime_reelStartNo);
    chancetime_eventFunc = chancetime_BlockSpinWait;
}

void chancetime_BlockSpinWait(void) {
    chancetime_blockSpinTimer++;
    if (chancetime_blockSpinTimer < 10) {
        return;
    }
    chancetime_blockSpinDoneF = 1;
    chancetime_blockSpinTimer = 0;
    chancetime_eventFunc = chancetime_EventIdle;
}

s32 chancetime_BlockSpinCheck(void) {
    return chancetime_blockSpinDoneF;
}

void chancetime_TransferStart(void) {
    chancetime_transferDoneF = 0;
    chancetime_eventFunc = chancetime_TransferExec;
}

void chancetime_TransferExec(omObjData *object) {
    s32 players[2];
    s32 i;
    s32 j;
    s32 coins = GwPlayer[chancetime_playerOrderTbl[0]].coin;
    s32 stars = GwPlayer[chancetime_playerOrderTbl[0]].star;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (chancetime_blockResultTbl[i] == GwPlayer[j].chr) {
                players[i] = j;
                break;
            }
        }
    }

    chancetime_TransferMesExec(object);
    HuPrcSleep(10);
    chancetime_statusVsF = 1;
    MBStatusCreateHidden(players[0], players[1]);
    MBStatusItemDispOff();
    MBStatusVsPlayerSet(players[0], players[1]);
    MBStatusVsAMove();
    MBStatusVsBMove();
    HuPrcSleep(40);
    chancetime_TransferAnimExec(object);
    if (coins + 1 == GwPlayer[chancetime_playerOrderTbl[0]].coin) {
        chancetime_PlayerNeutralExec();
    } else if (coins < GwPlayer[chancetime_playerOrderTbl[0]].coin) {
        chancetime_PlayerJoyExec();
    } else if (stars < GwPlayer[chancetime_playerOrderTbl[0]].star) {
        chancetime_PlayerJoyExec();
    } else if (GwPlayer[chancetime_playerOrderTbl[0]].coin < coins) {
        chancetime_PlayerSadExec();
    } else if (GwPlayer[chancetime_playerOrderTbl[0]].star < stars) {
        chancetime_PlayerSadExec();
    } else {
        chancetime_PlayerNeutralExec();
    }
    HuPrcSleep(30);
    chancetime_transferDoneF = 1;
    chancetime_eventFunc = chancetime_EventIdle;
}

s32 chancetime_TransferCheck(void) {
    return chancetime_transferDoneF;
}

void chancetime_TransferAnimExec(omObjData *object) {
    f32 coinsF[2];
    f32 starsF[2];
    s32 players[2];
    s32 i;
    s32 j;
    f32 offsetY;
    u16 isStars;
    s32 launched;
    s32 finished;
    s32 delay;
    s16 coins;
    s16 stars;
    s32 coinAmount;
    s32 count;
    f32 step;
    f32 lost;
    f32 gained;
    s32 frame;
    s32 timer;
    f32 value;
    f32 s;
    f32 x;
    f32 y;
    f32 t;
    f32 scale;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (chancetime_blockResultTbl[i] == GwPlayer[chancetime_playerOrderTbl[j]].chr) {
                players[i] = chancetime_playerOrderTbl[j];
                break;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        coinsF[i] = GwPlayer[players[i]].coin;
        starsF[i] = GwPlayer[players[i]].star;
    }

    coins = chancetime_actionAmountTbl[chancetime_actionNo].coins;
    // Set but unused; its pseudo orders the coins/stars loads and adds the spill slot at 0x70.
    coinAmount = coins;
    (void)coinAmount;
    stars = chancetime_actionAmountTbl[chancetime_actionNo].stars;
    if (coins > 0) {
        if (GwPlayer[players[0]].coin < coins) {
            coins = GwPlayer[players[0]].coin;
        }
        isStars = FALSE;
    } else {
        if (stars > GwPlayer[players[0]].star) {
            stars = GwPlayer[players[0]].star;
        }
        isStars = TRUE;
    }

    if ((!isStars ? coins : stars) <= 0) {
        return;
    }

    if (!isStars) {
        offsetY = 0.0f;
        count = coins;
        if (count > 20) {
            count = 20;
        }
        step = (f32)coins / count;
    } else {
        offsetY = 16.0f;
        count = stars;
        if (count > 10) {
            count = 10;
        }
        step = (f32)stars / count;
    }
    gained = 0.0f;
    lost = 0.0f;
    delay = 20 / count;
    delay = (delay < 5) ? 5 : delay;

    for (i = 0; i < 20; i++) {
        chancetime_transferTbl[i].state = 0;
        chancetime_transferTbl[i].timer = 0;
    }

    frame = 0;
    launched = 0;
    finished = 0;
    while (finished < count) {
        for (i = 0; i < 20; i++) {
            switch (chancetime_transferTbl[i].state) {
                case 0:
                    if (delay < frame) {
                        if (launched < count) {
                            chancetime_transferTbl[i].state = 1;
                            frame = 0;
                            launched++;
                            if (!isStars) {
                                lost += step;
                                value = coinsF[0] - lost;
                                if (value >= 0.0f) {
                                    GwPlayer[players[0]].coin = (u32)value;
                                } else {
                                    GwPlayer[players[0]].coin = 0;
                                }
                                HuAudFXPlay(0x109);
                            } else {
                                lost += step;
                                value = starsF[0] - lost;
                                if (value >= 0.0f) {
                                    GwPlayer[players[0]].star = (u32)value;
                                } else {
                                    GwPlayer[players[0]].star = 0;
                                }
                            }
                        }
                    }
                    break;
                case 1:
                    if (!isStars) {
                        espDispOn(chancetime_coinSprTbl[i]);
                        espAnimModeSet(chancetime_coinSprTbl[i], 1);
                        espBankSet(chancetime_coinSprTbl[i], 0, 0);
                        espPosSet(chancetime_coinSprTbl[i], 80, 74.0f - offsetY);
                    } else {
                        Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelAttrSet(chancetime_starEffTbl[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DParticleAttrSet(chancetime_starEffTbl[i], 1, 1);
                        Hu3DModelPosSet(object->model[i + 1], -170.0f, 375.0f, 0.0f);
                        EffectPosSet(chancetime_starEffTbl[i], -170.0f, 375.0f, 0.0f);
                    }
                    chancetime_transferTbl[i].timer = 0;
                    chancetime_transferTbl[i].state = 3;
                    break;
                case 2:
                    chancetime_transferTbl[i].state = 0;
                    if (!isStars) {
                        espDispOff(chancetime_coinSprTbl[i]);
                        gained += step;
                        value = gained + coinsF[1];
                        if (value <= 999.0f) {
                            GwPlayer[players[1]].coin = value;
                        } else {
                            GwPlayer[players[1]].coin = 999;
                        }
                        HuAudFXPlay(0x106);
                    } else {
                        Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DParticleAttrSet(chancetime_starEffTbl[i], 1, 0);
                        gained += step;
                        value = gained + starsF[1];
                        if (value <= 99.0f) {
                            GwPlayer[players[1]].star = value;
                        } else {
                            GwPlayer[players[1]].star = 99;
                        }
                        HuAudFXPlay(0x11B);
                    }
                    finished++;
                    break;
                case 3:
                    timer = chancetime_transferTbl[i].timer;
                    if (!isStars) {
                        x = timer * 8.5f;
                        s = sindf(timer * 9.0f);
                        y = s * 32.0f;
                        espPosSet(chancetime_coinSprTbl[i], x + 80.0f, 74.0f - y - offsetY);
                        espScaleSet(chancetime_coinSprTbl[i], s * 0.5f + 0.5f, s * 0.5f + 0.5f);
                        chancetime_transferTbl[i].timer++;
                        if (timer >= 20) {
                            chancetime_transferTbl[i].state = 2;
                        }
                    } else {
                        x = timer * 9.25f;
                        t = timer;
                        s = sindf(t * 4.5f);
                        y = s * 88.0f;
                        Hu3DModelPosSet(object->model[i + 1], x + -170.0f, y + 375.0f, 0.0f);
                        EffectPosSet(chancetime_starEffTbl[i], x + -170.0f, y + 375.0f, 0.0f);
                        scale = s * 0.5f + 0.5f;
                        Hu3DModelScaleSet(object->model[i + 1], scale, scale, scale);
                        Hu3DModelRotSet(object->model[i + 1], 0.0f, t * 15.0f, 0.0f);
                        EffectParamSet(chancetime_starEffTbl[i], s + s + 4.0f, 20.0f, s + s + 4.0f);
                        chancetime_transferTbl[i].timer++;
                        if (timer >= 40) {
                            chancetime_transferTbl[i].state = 2;
                        }
                    }
                    break;
            }
        }
        HuPrcVSleep();
        frame++;
    }

    if (!isStars) {
        value = coinsF[0] - coins;
        if (value >= 0.0f) {
            GwPlayer[players[0]].coin = value;
        } else {
            GwPlayer[players[0]].coin = 0;
        }
        value = coins + coinsF[1];
        if (value <= 999.0f) {
            GwPlayer[players[1]].coin = value;
        } else {
            GwPlayer[players[1]].coin = 999;
        }
    } else {
        value = starsF[0] - stars;
        if (value >= 0.0f) {
            GwPlayer[players[0]].star = value;
        } else {
            GwPlayer[players[0]].star = 0;
        }
        value = stars + starsF[1];
        if (value <= 99.0f) {
            GwPlayer[players[1]].star = value;
        } else {
            GwPlayer[players[1]].star = 99;
        }
    }
    MBPlayerCoinAdd(players[1], 0);
    HuPrcSleep(30);
}

void chancetime_IntroMesStart(void) {
    chancetime_introMesDoneF = 0;
    chancetime_eventFunc = chancetime_IntroMesExec;
}

void chancetime_IntroMesExec(void) {
    HuWinHomeClear(chancetime_eventWin);
    if (GwPlayer[chancetime_playerOrderTbl[0]].stat & 1) {
        HuWinAttrSet(chancetime_eventWin, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
    }
    chancetime_HostTalkStart();
    chancetime_HostTurn();
    HuAudFXPlay(0x298);
    HuWinMesSet(chancetime_eventWin, 0x1B00, -1, -1);
    HuWinExOpen(chancetime_eventWin, 1);
    while (HuWinStatGet(chancetime_eventWin)) {
        HuPrcVSleep();
    }
    HuWinExClose(chancetime_eventWin, 1);
    chancetime_HostTalkEnd();
    if (GwPlayer[chancetime_playerOrderTbl[0]].stat & 1) {
        HuWinComKeyReset();
    }
    chancetime_eventFunc = chancetime_IntroMesEnd;
}

s32 chancetime_IntroMesCheck(void) {
    return chancetime_introMesDoneF;
}

void chancetime_IntroMesEnd(void) {
    chancetime_introMesDoneF = 1;
    chancetime_eventFunc = chancetime_EventIdle;
}

void chancetime_ResultMesExec(s32 arg0, s32 arg1, s32 arg2) {
    u32 mes;
    s32 i;

    for (i = 0; i < 2; i++) {
        HuWinInsertMesSet(chancetime_eventWin, chancetime_chrNameMesTbl[chancetime_blockResultTbl[i]], i);
    }
    if (chancetime_actionNo < 5) {
        if (chancetime_actionAmountMesTbl[chancetime_actionNo] != 0) {
            HuWinInsertMesSet(chancetime_eventWin, chancetime_actionAmountMesTbl[chancetime_actionNo], 2);
        }
    } else {
        if (chancetime_actionAmountMesTbl[chancetime_actionNo] != 0) {
            HuWinInsertMesSet(chancetime_eventWin, chancetime_actionAmountMesTbl[chancetime_actionNo], 3);
        }
    }
    HuWinHomeClear(chancetime_eventWin);
    if (GwPlayer[chancetime_playerOrderTbl[0]].stat & 1) {
        HuWinAttrSet(chancetime_eventWin, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
    }
    chancetime_HostTalkStart();
    HuWinMesSet(chancetime_eventWin, chancetime_actionMesTbl[arg0], -1, -1);
    HuWinExOpen(chancetime_eventWin, 1);
    while (HuWinStatGet(chancetime_eventWin)) {
        HuPrcVSleep();
    }
    if (GwPlayer[chancetime_playerOrderTbl[0]].stat & 1) {
        HuWinAttrSet(chancetime_eventWin, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
        HuWinComKeyWait(-0x8000, -0x8000, -0x8000, -0x8000, MBMesWaitGet());
    }
    if (arg2 < arg1) {
        if (arg2 > 0) {
            mes = chancetime_actionShortMesTbl[arg0];
            if (mes != 0) {
                HuWinExClose(chancetime_eventWin, 1);
                HuWinMesSet(chancetime_eventWin, mes, -1, -1);
                HuAudFXPlay(0x29A);
                HuWinExOpen(chancetime_eventWin, 1);
                while (HuWinStatGet(chancetime_eventWin)) {
                    HuPrcVSleep();
                }
            }
        } else {
            HuWinExClose(chancetime_eventWin, 1);
            HuWinMesSet(chancetime_eventWin, chancetime_actionNoneMesTbl[arg0], -1, -1);
            HuAudFXPlay(0x29A);
            HuWinExOpen(chancetime_eventWin, 1);
            while (HuWinStatGet(chancetime_eventWin)) {
                HuPrcVSleep();
            }
        }
    }
    HuWinExClose(chancetime_eventWin, 1);
    chancetime_HostTalkEnd();
    if (GwPlayer[chancetime_playerOrderTbl[0]].stat & 1) {
        HuWinComKeyReset();
    }
    chancetime_eventFunc = chancetime_BlockSpinReelStart;
}

void chancetime_TransferMesExec(omObjData *object) {
    s32 players[4];
    s32 i;
    s32 j;
    s32 coinAmount;
    s32 starAmount;
    s16 coins;
    s16 stars;
    u16 isStars;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (chancetime_blockResultTbl[i] == GwPlayer[chancetime_playerOrderTbl[j]].chr) {
                players[i] = chancetime_playerOrderTbl[j];
                break;
            }
        }
    }

    coins = chancetime_actionMesAmountTbl[chancetime_actionNo].coins;
    coinAmount = chancetime_actionMesAmountTbl[chancetime_actionNo].coins;
    starAmount = chancetime_actionMesAmountTbl[chancetime_actionNo].stars;
    stars = starAmount;
    if (coinAmount > 0) {
        if (GwPlayer[players[0]].coin < coinAmount) {
            coins = GwPlayer[players[0]].coin;
        }
        isStars = FALSE;
    } else {
        if (stars > GwPlayer[players[0]].star) {
            stars = GwPlayer[players[0]].star;
        }
        isStars = TRUE;
    }

    if (!isStars) {
        chancetime_ResultMesExec(chancetime_actionNo, coinAmount, coins);
    } else {
        chancetime_ResultMesExec(chancetime_actionNo, starAmount, stars);
    }
}

const ChanceTimeReelSpeed chancetime_reelSpeedTbl[3] = { { 10.0f, 10.0f }, { 20.0f, 20.0f }, { 40.0f, 40.0f } };

const s32 chancetime_unusedSprPosTbl[6] = { 125, 71, 198, 71, 161, 141 }; /* Unreferenced. */

const Vec chancetime_reelPosTbl[3] = {
    { -111.0f, 486.0f, -541.0f },
    { 119.0f, 486.0f, -541.0f },
    { 3.0f, 265.0f, -541.0f },
};

const u32 chancetime_blockMesTbl[3] = { 0x1B01, 0x1B02, 0x1B03 };

const ChanceTimeAmount chancetime_actionAmountTbl[9] = {
    { 1000, 0 },
    { 30, 0 },
    { 20, 0 },
    { 10, 0 },
    { 1, 0 },
    { 0, 1000 },
    { 0, 3 },
    { 0, 2 },
    { 0, 1 },
};

const u32 chancetime_actionMesTbl[9] = { 0x1B0C, 0x1B06, 0x1B06, 0x1B06, 0x1B04, 0x1B0E, 0x1B09, 0x1B09, 0x1B09 };

const u32 chancetime_actionShortMesTbl[9] = { 0, 0x1B07, 0x1B07, 0x1B07, 0, 0, 0x1B0A, 0x1B0A, 0x1B0A };

const u32 chancetime_actionNoneMesTbl[9] = { 0x1B0D, 0x1B08, 0x1B08, 0x1B08, 0x1B05, 0x1B0F, 0x1B0B, 0x1B0B, 0x1B0B };

const u32 chancetime_actionAmountMesTbl[9] = { 0, 0x1B1A, 0x1B19, 0x1B18, 0, 0, 0x1B1D, 0x1B1C, 0x1B1B };

const u32 chancetime_chrNameMesTbl[8] = { 0x1B10, 0x1B11, 0x1B12, 0x1B13, 0x1B14, 0x1B15, 0x1B16, 0x1B17 };

const ChanceTimeAmount chancetime_actionMesAmountTbl[9] = {
    { 1000, 0 },
    { 30, 0 },
    { 20, 0 },
    { 10, 0 },
    { 1, 0 },
    { 0, 1000 },
    { 0, 3 },
    { 0, 2 },
    { 0, 1 },
};
