#include "common.h"
#include "game/audio.h"
#include "game/camsetup.h"
#include "game/esprite.h"
#include "game/gamework.h"
#include "game/hmfcoll.h"
#include "game/hmfspr.h"
#include "game/input.h"
#include "game/mallocblock.h"
#include "game/sprite.h"
#include "game/util.h"
#include "game/window.h"
#include "game/wipe.h"
#include "overlays/minigame.h"

// 0x14 byte entry for one space of a Mario's Puzzle Party board path
typedef struct MarioPuzzlePartyPathSpace {
    /* 0x00 */ s32 sprite;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ s32 ownerId;
    /* 0x10 */ s32 type;
} MarioPuzzlePartyPathSpace;

// one board path of 40 spaces
typedef struct MarioPuzzlePartyPath {
    /* 0x00 */ MarioPuzzlePartyPathSpace spaces[40];
} MarioPuzzlePartyPath;

// a sparkle effect drifting around the background
typedef struct MarioPuzzlePartySparkle {
    /* 0x00 */ s32 sprGroup;
    /* 0x04 */ s32 spawnMode;
    /* 0x08 */ s32 moveMode;
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ f32 vx;
    /* 0x1C */ f32 vy;
    /* 0x20 */ f32 scale;
} MarioPuzzlePartySparkle; // sizeof 0x24

// initial values for MarioPuzzlePartySparkle
typedef struct MarioPuzzlePartySparkleInit {
    /* 0x00 */ s32 spawnMode;
    /* 0x04 */ s32 moveMode;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 vx;
    /* 0x14 */ f32 vy;
} MarioPuzzlePartySparkleInit; // sizeof 0x18

// per-player cursor state
typedef struct MarioPuzzlePartyCursor {
    /* 0x00 */ s32 sprite;
    /* 0x04 */ s32 board;
    /* 0x08 */ s32 blockSprites[2];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 pathIdx;
    /* 0x18 */ s32 spaceIdx;
    /* 0x1C */ s32 blockOwners[2];
    /* 0x24 */ s32 moveDir;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ f32 x;
    /* 0x30 */ f32 y;
} MarioPuzzlePartyCursor; // sizeof 0x34

// a block falling after the spaces beneath it were cleared
typedef struct MarioPuzzlePartyFallingBlock {
    /* 0x00 */ s32 board;
    /* 0x04 */ s32 sprite;
    /* 0x08 */ s32 x;
    /* 0x0C */ s32 y;
    /* 0x10 */ s32 ownerId;
    /* 0x14 */ s32 type;
    /* 0x18 */ s32 unk_18;
} MarioPuzzlePartyFallingBlock; // sizeof 0x1C

// state for a block being squashed by a garbage block landing on it
typedef struct MarioPuzzlePartySquash {
    /* 0x00 */ s32 board;
    /* 0x04 */ s32 pathIdx;
    /* 0x08 */ s32 sprGroup;
    /* 0x0C */ s32 x;
    /* 0x10 */ MarioPuzzlePartyCursor *cursor;
    /* 0x14 */ char unk_14[8];
} MarioPuzzlePartySquash; // sizeof 0x1C

// a piece of debris thrown off a cleared block
typedef struct MarioPuzzlePartyDebris {
    /* 0x00 */ s32 sprite;
    /* 0x04 */ s32 active;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 vx;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 vy;
} MarioPuzzlePartyDebris; // sizeof 0x1C

// user data for the score display process
typedef struct MarioPuzzlePartyScoreDisplay {
    /* 0x00 */ s32 board;
    /* 0x04 */ s32 sprGroup;
} MarioPuzzlePartyScoreDisplay;

// a board space queued for removal
typedef struct MarioPuzzlePartyMatch {
    /* 0x00 */ s32 pathIdx;
    /* 0x04 */ s32 spaceIdx;
    /* 0x08 */ s32 type;
} MarioPuzzlePartyMatch; // sizeof 0xC

// screen origin of each player's board
extern s32 D_80110080_marios_puzzle_party[4][2];
extern D_80111B50_vine_with_me_Struct D_80110140_marios_puzzle_party;
extern MarioPuzzlePartySparkleInit D_80110168_marios_puzzle_party[8];

extern MarioPuzzlePartyPath D_801102E0_marios_puzzle_party[4][6];

// per-player input state; CPU players read their input from here rather than a controller
typedef struct MarioPuzzlePartyPlayerInput {
    /* 0x00 */ s32 unk_00[16];
    /* 0x40 */ u16 direction;
    /* 0x42 */ u16 buttons;
} MarioPuzzlePartyPlayerInput; // sizeof 0x44

extern MarioPuzzlePartyPlayerInput D_80114DE0_marios_puzzle_party[4];

extern MarioPuzzlePartyDebris D_80114EF0_marios_puzzle_party[160];

extern s32 D_801160E4_marios_puzzle_party;

extern u8 D_800D6A90_main;

extern s16 D_8011608E_marios_puzzle_party;
extern s16 D_80116096_marios_puzzle_party;
extern s16 D_801160A2_marios_puzzle_party;
extern s16 D_801160A6_marios_puzzle_party;
extern s16 D_801160AA_marios_puzzle_party;
extern s16 D_801160AE_marios_puzzle_party;
extern s16 D_801160B2_marios_puzzle_party;
extern s16 D_801160D2_marios_puzzle_party;
extern s16 D_801160D6_marios_puzzle_party;

// set once the minigame is ending
extern s32 D_801160E8_marios_puzzle_party;

// number of players that took part in the game
extern s32 D_80116100_marios_puzzle_party;

extern s32 D_80116158_marios_puzzle_party;
extern s32 D_80116160_marios_puzzle_party;

// per-player "still waiting for its turn to finish" flag
extern s32 D_80116168_marios_puzzle_party[4];

extern s32 D_80116108_marios_puzzle_party[4];
extern s32 D_80116128_marios_puzzle_party[4];
extern s32 D_80116138_marios_puzzle_party[4];
extern s32 D_80116148_marios_puzzle_party[4];
extern s32 D_80116178_marios_puzzle_party[4];
extern s32 D_80116188_marios_puzzle_party[4];
extern s32 D_801161A8_marios_puzzle_party[4];
extern s32 D_801161B8_marios_puzzle_party[4];
extern s32 D_801161C8_marios_puzzle_party[4];
extern s32 D_801161D8_marios_puzzle_party[4];
extern s32 D_801161E8_marios_puzzle_party[4];
extern s32 D_801161F8_marios_puzzle_party[4];
extern s32 D_80116208_marios_puzzle_party[4];
extern s32 D_80116218_marios_puzzle_party[4];
extern s32 D_80116228_marios_puzzle_party[4];
extern MarioPuzzlePartyCursor D_80116238_marios_puzzle_party[4];
extern MarioPuzzlePartyCursor D_80116308_marios_puzzle_party[4];

// per-player process spawned by the minigame setup
extern Process *D_801163D8_marios_puzzle_party[4];

// spaces queued for removal
extern s32 D_801163E8_marios_puzzle_party;
extern MarioPuzzlePartyMatch D_801163F0_marios_puzzle_party[80];

// sequence of block owner pairs dealt to every player
extern s32 D_801167B0_marios_puzzle_party[30][2];
// per-player position in D_801167B0_marios_puzzle_party
extern s32 D_801168A0_marios_puzzle_party[4];

void func_80105C98_marios_puzzle_party(void);
void func_8010604C_marios_puzzle_party(void);
s32 func_80106A44_marios_puzzle_party(s32 board, s32 ownerId, s32 type, s32 x, s32 y);
void func_80107400_marios_puzzle_party(s32 board, s32 pathIdx, s32 spaceIdx, s32 ownerId, s32 type);
void func_80107880_marios_puzzle_party(s32 board, s32 pathIdx, s32 spaceIdx, s32 ownerId, s32 type);
void func_80107BB0_marios_puzzle_party(s32 board);
void func_80107CBC_marios_puzzle_party(void);
void func_80108568_marios_puzzle_party(s32 board, s32 arg1);
void func_80108C80_marios_puzzle_party(void);
void func_80105D50_marios_puzzle_party(s32 board, s32 ownerId, s32 type, s32 pathIdx, s32 spaceIdx);
s32 func_80107000_marios_puzzle_party(s32 board, s32 pathIdx);
s32 func_80107070_marios_puzzle_party(s32 board, s32 pathIdx);
s32 func_80107108_marios_puzzle_party(s32 board, s32 pathIdx);
void func_8010913C_marios_puzzle_party(void);
void func_80109160_marios_puzzle_party(void);
void func_8010A588_marios_puzzle_party(void);
void func_8010AD20_marios_puzzle_party(void);
void func_8010D8E8_marios_puzzle_party(void);
void func_8010CF4C_marios_puzzle_party(void);
void func_8010CFF8_marios_puzzle_party(omObjData *obj);
void func_8010D290_marios_puzzle_party(s32 board, s32 pathIdx, s32 spaceIdx);
void func_8010D46C_marios_puzzle_party(void);
void func_8010D490_marios_puzzle_party(void);
void func_8010D9AC_marios_puzzle_party(void);
void func_8010DB98_marios_puzzle_party(void);
void func_8010E868_marios_puzzle_party(s16 group, s32 time);
void func_8010EF30_marios_puzzle_party(void);
s16 func_8010FEDC_marios_puzzle_party(s16 group, f32 x, f32 y);
void func_8010FF78_marios_puzzle_party(s16 index, f32 x, f32 y);
void func_8010FFBC_marios_puzzle_party(s16 index, f32 width, f32 height);
void func_80110000_marios_puzzle_party(s16 index);
void func_8011006C_marios_puzzle_party(s32 board, s32 offset);

void func_801059A0_marios_puzzle_party(void) {
    Process *process;
    MarioPuzzlePartySparkle *sparkle;
    s32 camIndex;
    s32 i;

    func_8001FE20_main(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 64);
    func_800142A0_main(32);
    omInitObjMan(170, 200);
    func_8004A208_main();
    func_800E1804_minigame();
    HuWinInit();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main() & 0xFF;
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 16.0f, 500.0f, 5000.0f);
    CZoom = 800.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    omAddPrcObj(func_8010EF30_marios_puzzle_party, 0x4001, 0x800, 0);
    for (i = 0; i < 4; i++) {
        D_801163D8_marios_puzzle_party[i] = process = omAddPrcObj(func_8010AD20_marios_puzzle_party, 0x4001, 0x3000, 0);
        process->user_data = (void *)i;
    }
    D_80116100_marios_puzzle_party = i;
    omAddPrcObj(func_8010DB98_marios_puzzle_party, 0x4001, 0x800, 0);
    for (i = 0; i < 8; i++) {
        process = omAddPrcObj(func_8010D490_marios_puzzle_party, 0x4001, 0x800, 0);
        sparkle = process->user_data = HuMemAlloc(sizeof(MarioPuzzlePartySparkle));
        sparkle->x = D_80110168_marios_puzzle_party[i].x;
        sparkle->y = D_80110168_marios_puzzle_party[i].y;
        sparkle->vx = D_80110168_marios_puzzle_party[i].vx;
        sparkle->vy = D_80110168_marios_puzzle_party[i].vy;
        sparkle->spawnMode = D_80110168_marios_puzzle_party[i].spawnMode;
        sparkle->moveMode = D_80110168_marios_puzzle_party[i].moveMode;
    }
    func_8010604C_marios_puzzle_party();
    omAddPrcObj(func_80105C98_marios_puzzle_party, 0x4001, 0x800, 0);
    omPrcSetStatBit(omAddPrcObj(func_8010D9AC_marios_puzzle_party, 0x4001, 0x800, 0), 0xA0);
    func_800E5EA0_minigame(&D_80110140_marios_puzzle_party);
    D_800EB930_minigame = 56;
    WipeCreateIn(0xFF, 16);
}

void func_80105C98_marios_puzzle_party(void) {
    s32 done = FALSE;

    while (TRUE) {
        if (D_800D530C_main == 1) {
            done = TRUE;
        }
        if (done) {
            D_801160E8_marios_puzzle_party = 1;
            WipeCreateOut(0, 20);
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            while (WipeStatGet()) {
                HuPrcVSleep();
            }
            Hu3DBGColorSet(0, 0, 0);
            HuWinAllKill();
            omOvlKill();
            omOvlReturnEx(1);
        }
        HuPrcVSleep();
    }
}

void func_80105D50_marios_puzzle_party(s32 board, s32 ownerId, s32 type, s32 pathIdx, s32 spaceIdx) {
    MarioPuzzlePartyPathSpace *space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];
    MarioPuzzlePartyPathSpace *next;

    space->ownerId = ownerId;
    space->x = D_80110080_marios_puzzle_party[board][0] + pathIdx * 14;
    space->y = D_80110080_marios_puzzle_party[board][1] - spaceIdx * 7;
    space->type = type;
    space->sprite = func_80106A44_marios_puzzle_party(board, space->ownerId, space->type, space->x, space->y);
    if (type == 1) {
        next = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx + 1];
        next->ownerId = ownerId;
        next->x = space->x;
        next->y = space->y - 7;
        next->type = 2;
        next->sprite = space->sprite;
    }
}

u16 func_80105E88_marios_puzzle_party(s32 playerIndex) {
    u16 buttons;

    if (!(GwPlayer[playerIndex].stat & PLAYER_IS_CPU)) {
        buttons = D_800CDA7C_main[GwPlayer[playerIndex].pad];
        buttons &= 0xF0FF;
        if (D_800CBB6E_main[GwPlayer[playerIndex].pad] > 30.0f) {
            buttons |= 0x100;
        }
        if (D_800CBB6E_main[GwPlayer[playerIndex].pad] < -30.0f) {
            buttons |= 0x200;
        }
        if (D_800D20A1_main[GwPlayer[playerIndex].pad] < -30.0f) {
            buttons |= 0x400;
        }
    } else {
        buttons = D_80114DE0_marios_puzzle_party[playerIndex].direction;
    }
    return buttons;
}

u16 func_80105FCC_marios_puzzle_party(s32 playerIndex, s16 bits) {
    u16 result;

    if (!(GwPlayer[playerIndex].stat & PLAYER_IS_CPU)) {
        result = D_800D5558_main[GwPlayer[playerIndex].pad];
        result &= bits;
    } else {
        MarioPuzzlePartyPlayerInput *input = &D_80114DE0_marios_puzzle_party[playerIndex];
        result = input->buttons;
        result &= bits;
        input->buttons &= ~bits;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010604C_marios_puzzle_party);

s32 func_80106A44_marios_puzzle_party(s32 board, s32 ownerId, s32 type, s32 x, s32 y) {
    s32 sprite = func_8010FEDC_marios_puzzle_party(board * 7 + ownerId, x, y);

    if (type != 1) {
        func_8010FFBC_marios_puzzle_party(sprite, 1.0f, 0.5f);
    }
    return sprite;
}

s32 func_80106ACC_marios_puzzle_party(s32 board, MarioPuzzlePartyCursor *cursor, s32 dir) {
    s32 result = TRUE;
    MarioPuzzlePartyPath *path;
    s32 offset;
    s32 pathIdx;
    s32 spaceIdx;

    if (dir > 0) {
        offset = 14;
    } else {
        offset = -14;
    }
    pathIdx = (offset + cursor->x - D_80110080_marios_puzzle_party[board][0]) / 14.0f;
    spaceIdx = (D_80110080_marios_puzzle_party[board][1] - cursor->y) / 7.0f;

    path = &D_801102E0_marios_puzzle_party[board][pathIdx];
    if (path->spaces[spaceIdx].type == 0) {
        result = FALSE;
    }
    return result;
}

s32 func_80106BB0_marios_puzzle_party(s32 board, MarioPuzzlePartyCursor *cursor, s32 dir) {
    s32 result = TRUE;
    MarioPuzzlePartyPath *path;
    s32 offset;
    s32 pathIdx;
    s32 spaceIdx;

    if (dir > 0) {
        offset = 14;
    } else {
        offset = -28;
    }
    pathIdx = (offset + cursor->x - D_80110080_marios_puzzle_party[board][0]) / 14.0f;
    spaceIdx = (D_80110080_marios_puzzle_party[board][1] - (cursor->y + 14.0f)) / 7.0f;

    path = &D_801102E0_marios_puzzle_party[board][pathIdx];
    if (path->spaces[spaceIdx].type == 0) {
        result = FALSE;
    }
    return result;
}

s32 func_80106C98_marios_puzzle_party(s32 board, MarioPuzzlePartyCursor *cursor, s32 dy) {
    s32 result = TRUE;
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyPathSpace *other;
    s32 pathIdx;
    s32 spaceIdx;
    s32 otherIdx;

    cursor->y += dy;
    pathIdx = (cursor->x - D_80110080_marios_puzzle_party[board][0]) / 14.0f;
    spaceIdx = (D_80110080_marios_puzzle_party[board][1] - cursor->y) / 7.0f;
    space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];
    if (cursor->moveDir != 0) {
        if (pathIdx * 14 - cursor->x > 0.0f) {
            otherIdx = pathIdx - 1;
        } else {
            otherIdx = pathIdx + 1;
        }
        other = &D_801102E0_marios_puzzle_party[board][otherIdx].spaces[spaceIdx];
        if (space->type == 0 && other->type == 0) {
            cursor->pathIdx = pathIdx;
            cursor->spaceIdx = spaceIdx;
            result = FALSE;
        }
    } else if (space->type == 0) {
        cursor->pathIdx = pathIdx;
        cursor->spaceIdx = spaceIdx;
        result = FALSE;
    }
    if (result) {
        cursor->y -= dy;
    }
    return result;
}

s32 func_80106E40_marios_puzzle_party(s32 board, MarioPuzzlePartyCursor *cursor, s32 dy) {
    s32 result = TRUE;
    MarioPuzzlePartyPathSpace *left;
    MarioPuzzlePartyPathSpace *right;
    MarioPuzzlePartyPathSpace *other;
    s32 pathIdx;
    s32 spaceIdx;
    s32 otherIdx;

    cursor->y += dy;
    spaceIdx = (D_80110080_marios_puzzle_party[board][1] - cursor->y - 14.0f) / 7.0f;
    pathIdx = (cursor->x - (D_80110080_marios_puzzle_party[board][0] + 22)) / 14.0f + 1.0f;
    left = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];
    right = &D_801102E0_marios_puzzle_party[board][pathIdx + 1].spaces[spaceIdx];
    if (cursor->moveDir != 0) {
        if (cursor->moveDir < 0) {
            otherIdx = pathIdx - 1;
        } else {
            otherIdx = pathIdx + 2;
        }
        other = &D_801102E0_marios_puzzle_party[board][otherIdx].spaces[spaceIdx];
        if (left->type == 0 && right->type == 0 && other->type == 0) {
            result = FALSE;
        }
    } else if (left->type == 0 && right->type == 0) {
        result = FALSE;
    }
    if (result) {
        cursor->y -= dy;
    }
    return result;
}

s32 func_80107000_marios_puzzle_party(s32 board, s32 pathIdx) {
    s32 i = 1;
    MarioPuzzlePartyPath *path = &D_801102E0_marios_puzzle_party[board][pathIdx];

    for (; i < 40; i++) {
        if (path->spaces[i].type == 0) {
            break;
        }
    }
    return i;
}

s32 func_80107070_marios_puzzle_party(s32 board, s32 pathIdx) {
    s32 i = 1;
    s32 count = 0;
    MarioPuzzlePartyPath *path = &D_801102E0_marios_puzzle_party[board][pathIdx];
    MarioPuzzlePartyPathSpace *space;

    for (; i < 40; i++) {
        space = &path->spaces[i];
        if (space->type == 0) {
            break;
        }
        if (space->type == 1) {
            i++;
            count++;
        }
        if (space->type == 3) {
            count++;
        }
    }
    return count;
}

s32 func_80107108_marios_puzzle_party(s32 board, s32 pathIdx) {
    s32 i = 1;
    s32 count = 0;
    MarioPuzzlePartyPath *path = &D_801102E0_marios_puzzle_party[board][pathIdx];

    for (; i < 40; i++) {
        if (path->spaces[i].type == 0) {
            break;
        }
        if (path->spaces[i].type == 1) {
            count++;
            i++;
        }
    }
    return count;
}

s32 func_8010718C_marios_puzzle_party(s32 pathIdx, s32 spaceIdx) {
    s32 i;

    for (i = 0; i < D_801163E8_marios_puzzle_party; i++) {
        MarioPuzzlePartyMatch *match = &D_801163F0_marios_puzzle_party[i];

        if (pathIdx == match->pathIdx && spaceIdx == match->spaceIdx) {
            return TRUE;
        }
        if (match->type == 1 && pathIdx == match->pathIdx && spaceIdx == match->spaceIdx + 1) {
            return TRUE;
        }
    }
    return FALSE;
}

void func_80107224_marios_puzzle_party(s32 board, s32 pathIdx, s32 spaceIdx) {
    MarioPuzzlePartyPathSpace *space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];

    if (space->ownerId != 6) {
        D_80116188_marios_puzzle_party[board]++;
    }
    func_8010D290_marios_puzzle_party(board, pathIdx, spaceIdx);
    if (space->type == 2) {
        spaceIdx--;
        space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];
    }
    func_80110000_marios_puzzle_party(space->sprite);
    space->sprite = -1;
    if (space->type == 1) {
        space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx + 1];
        space->ownerId = -1;
        space->type = 0;
    }
    space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];
    space->ownerId = -1;
    space->type = 0;
}

void func_80107400_marios_puzzle_party(s32 board, s32 pathIdx, s32 spaceIdx, s32 ownerId, s32 type) {
    MarioPuzzlePartyPathSpace *space;

    if (type == 2) {
        spaceIdx--;
        type = 1;
    }
    D_801163F0_marios_puzzle_party[D_801163E8_marios_puzzle_party].pathIdx = pathIdx;
    D_801163F0_marios_puzzle_party[D_801163E8_marios_puzzle_party].spaceIdx = spaceIdx;
    D_801163F0_marios_puzzle_party[D_801163E8_marios_puzzle_party].type = type;
    D_801163E8_marios_puzzle_party++;
    if (D_801163E8_marios_puzzle_party >= 80) {
        osSyncPrintf("BlockDelete Over\n");
        while (TRUE) {
            HuPrcVSleep();
        }
    }
    if (ownerId == 6) {
        return;
    }
    if (!func_8010718C_marios_puzzle_party(pathIdx - 1, spaceIdx)) {
        space = &D_801102E0_marios_puzzle_party[board][pathIdx - 1].spaces[spaceIdx];
        if (space->ownerId == ownerId) {
            func_80107400_marios_puzzle_party(board, pathIdx - 1, spaceIdx, ownerId, space->type);
        }
    }
    if (!func_8010718C_marios_puzzle_party(pathIdx + 1, spaceIdx)) {
        space = &D_801102E0_marios_puzzle_party[board][pathIdx + 1].spaces[spaceIdx];
        if (space->ownerId == ownerId) {
            func_80107400_marios_puzzle_party(board, pathIdx + 1, spaceIdx, ownerId, space->type);
        }
    }
    if (!func_8010718C_marios_puzzle_party(pathIdx, spaceIdx - 1)) {
        space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx - 1];
        if (space->ownerId == ownerId) {
            func_80107400_marios_puzzle_party(board, pathIdx, spaceIdx - 1, ownerId, space->type);
        }
    }
    if (type == 1) {
        if (!func_8010718C_marios_puzzle_party(pathIdx - 1, spaceIdx + 1)) {
            space = &D_801102E0_marios_puzzle_party[board][pathIdx - 1].spaces[spaceIdx + 1];
            if (space->ownerId == ownerId) {
                func_80107400_marios_puzzle_party(board, pathIdx - 1, spaceIdx + 1, ownerId, space->type);
            }
        }
        if (!func_8010718C_marios_puzzle_party(pathIdx + 1, spaceIdx + 1)) {
            space = &D_801102E0_marios_puzzle_party[board][pathIdx + 1].spaces[spaceIdx + 1];
            if (space->ownerId == ownerId) {
                func_80107400_marios_puzzle_party(board, pathIdx + 1, spaceIdx + 1, ownerId, space->type);
            }
        }
        if (!func_8010718C_marios_puzzle_party(pathIdx, spaceIdx + 2)) {
            space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx + 2];
            if (space->ownerId == ownerId) {
                func_80107400_marios_puzzle_party(board, pathIdx, spaceIdx + 2, ownerId, space->type);
            }
        }
    } else {
        if (!func_8010718C_marios_puzzle_party(pathIdx, spaceIdx + 1)) {
            space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx + 1];
            if (space->ownerId == ownerId) {
                func_80107400_marios_puzzle_party(board, pathIdx, spaceIdx + 1, ownerId, space->type);
            }
        }
    }
}

void func_80107880_marios_puzzle_party(s32 board, s32 pathIdx, s32 spaceIdx, s32 ownerId, s32 type) {
    MarioPuzzlePartyPathSpace *space;

    if (type == 2) {
        spaceIdx--;
        type = 1;
    }
    space = &D_801102E0_marios_puzzle_party[board][pathIdx - 1].spaces[spaceIdx];
    if (space->ownerId == ownerId) {
        func_80107224_marios_puzzle_party(board, pathIdx - 1, spaceIdx);
    }
    space = &D_801102E0_marios_puzzle_party[board][pathIdx + 1].spaces[spaceIdx];
    if (space->ownerId == ownerId) {
        func_80107224_marios_puzzle_party(board, pathIdx + 1, spaceIdx);
    }
    space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx - 1];
    if (space->ownerId == ownerId) {
        func_80107224_marios_puzzle_party(board, pathIdx, spaceIdx - 1);
    }
    if (type == 1) {
        space = &D_801102E0_marios_puzzle_party[board][pathIdx - 1].spaces[spaceIdx + 1];
        if (space->ownerId == ownerId) {
            func_80107224_marios_puzzle_party(board, pathIdx - 1, spaceIdx + 1);
        }
        space = &D_801102E0_marios_puzzle_party[board][pathIdx + 1].spaces[spaceIdx + 1];
        if (space->ownerId == ownerId) {
            func_80107224_marios_puzzle_party(board, pathIdx + 1, spaceIdx + 1);
        }
        space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx + 2];
        if (space->ownerId == ownerId) {
            func_80107224_marios_puzzle_party(board, pathIdx, spaceIdx + 2);
        }
    } else {
        space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx + 1];
        if (space->ownerId == ownerId) {
            func_80107224_marios_puzzle_party(board, pathIdx, spaceIdx + 1);
        }
    }
}

void func_80107BB0_marios_puzzle_party(s32 board) {
    s32 i;

    for (i = 0; i < D_801163E8_marios_puzzle_party; i++) {
        MarioPuzzlePartyMatch *match = &D_801163F0_marios_puzzle_party[i];

        func_80107224_marios_puzzle_party(board, match->pathIdx, match->spaceIdx);
        D_80116148_marios_puzzle_party[board] += D_80116108_marios_puzzle_party[board] + 1;
        D_80116138_marios_puzzle_party[board] += D_80116108_marios_puzzle_party[board] + 1;
        func_80107880_marios_puzzle_party(board, match->pathIdx, match->spaceIdx, 6, match->type);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_80107CBC_marios_puzzle_party);

void func_80108568_marios_puzzle_party(s32 board, s32 arg1) {
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyFallingBlock *block;
    Process *process;
    s32 first = TRUE;
    s32 found;
    s32 saved;
    s32 pathIdx;
    s32 spaceIdx;
    s32 chain;

    while (TRUE) {
        saved = D_80116148_marios_puzzle_party[board];
        D_80116148_marios_puzzle_party[board] = 0;
        for (pathIdx = 1, found = FALSE; pathIdx < 5; pathIdx++) {
            for (spaceIdx = 1; spaceIdx < 40; spaceIdx++) {
                space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];
                if (space->type == 1 || space->type == 3) {
                    D_801163E8_marios_puzzle_party = 0;
                    func_80107400_marios_puzzle_party(board, pathIdx, spaceIdx, space->ownerId, space->type);
                    if (D_801163E8_marios_puzzle_party >= 2) {
                        func_80107BB0_marios_puzzle_party(board);
                        found = TRUE;
                        if (first && arg1) {
                            first = FALSE;
                            omAddPrcObj(func_80107CBC_marios_puzzle_party, 0x4001, 0x800, 0)->user_data = (void *)board;
                        }
                    }
                }
            }
        }
        if (found) {
            D_80116108_marios_puzzle_party[board]++;
            func_8004AC98_main(0x3F8, board);
            chain = D_80116108_marios_puzzle_party[board] - 1;
            if (chain < 0 || chain > 4) {
                chain = 4;
            }
            func_8004AC98_main(chain + 0x400, board);
            omVibrate(board, 2, 3, 10);
            for (pathIdx = 1; pathIdx < 5; pathIdx++) {
                for (spaceIdx = 1; spaceIdx < 40; spaceIdx++) {
                    space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];
                    if (space->type == 0) {
                        break;
                    }
                }
                for (; spaceIdx < 40; spaceIdx++) {
                    space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];
                    if (space->type == 1 || space->type == 3) {
                        process = omAddPrcObj(func_80108C80_marios_puzzle_party, 0x4001, 0x800, 0);
                        HuPrcChildLink(HuPrcCurrentGet(), process);
                        block = process->user_data = HuMemAlloc(sizeof(MarioPuzzlePartyFallingBlock));
                        block->board = board;
                        block->sprite = space->sprite;
                        block->x = D_80110080_marios_puzzle_party[board][0] + pathIdx * 14;
                        block->y = D_80110080_marios_puzzle_party[board][1] - spaceIdx * 7;
                        block->ownerId = space->ownerId;
                        block->type = space->type;
                        block->unk_18 = 0;
                    }
                }
            }
            HuPrcChildWatch();
        } else {
            D_80116148_marios_puzzle_party[board] = saved;
            break;
        }
    }
}

void func_801088F4_marios_puzzle_party(s32 board, MarioPuzzlePartyCursor *cursor) {
    MarioPuzzlePartyPathSpace *space;
    s32 i;

    for (i = 0; i < 2; i++) {
        space = &D_801102E0_marios_puzzle_party[board][cursor->pathIdx].spaces[i + cursor->spaceIdx];
        space->sprite = cursor->blockSprites[0];
        space->x = cursor->x;
        space->y = cursor->y;
        space->ownerId = cursor->blockOwners[0];
        space->type = i + 1;
    }
    for (i = 0; i < 2; i++) {
        space = &D_801102E0_marios_puzzle_party[board][cursor->pathIdx].spaces[cursor->spaceIdx + 2 + i];
        space->sprite = cursor->blockSprites[1];
        space->x = cursor->x;
        space->y = cursor->y - 14.0f;
        space->ownerId = cursor->blockOwners[1];
        space->type = i + 1;
    }
    func_80108568_marios_puzzle_party(board, 1);
}

s32 func_80108A50_marios_puzzle_party(s32 board, s32 type, s32 ownerId, s32 pathIdx, s32 spaceIdx) {
    MarioPuzzlePartyPathSpace *space;
    s32 count = 0;

    if (ownerId != 6) {
        space = &D_801102E0_marios_puzzle_party[board][pathIdx - 1].spaces[spaceIdx];
        count = space->ownerId == ownerId;
        space = &D_801102E0_marios_puzzle_party[board][pathIdx + 1].spaces[spaceIdx];
        count += space->ownerId == ownerId;
        space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx - 1];
        count += space->ownerId == ownerId;
        if (type == 1) {
            space = &D_801102E0_marios_puzzle_party[board][pathIdx - 1].spaces[spaceIdx + 1];
            count += space->ownerId == ownerId;
            space = &D_801102E0_marios_puzzle_party[board][pathIdx + 1].spaces[spaceIdx + 1];
            count += space->ownerId == ownerId;
            space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx + 2];
            count += space->ownerId == ownerId;
        } else {
            space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx + 1];
            count += space->ownerId == ownerId;
        }
    }
    return count;
}

void func_80108BB0_marios_puzzle_party(void) {
    MarioPuzzlePartyFallingBlock *block = HuPrcCurrentGet()->user_data;

    if (D_801160E4_marios_puzzle_party == block->board && D_80116178_marios_puzzle_party[D_801160E4_marios_puzzle_party] != 0) {
        func_8010D290_marios_puzzle_party(D_801160E4_marios_puzzle_party,
                                          (block->x - D_80110080_marios_puzzle_party[D_801160E4_marios_puzzle_party][0]) / 14,
                                          (D_80110080_marios_puzzle_party[D_801160E4_marios_puzzle_party][1] - block->y) / 7);
        func_80110000_marios_puzzle_party(block->sprite);
    }
    func_80019C00_main(HuPrcCurrentGet()->user_data);
}

void func_80108C80_marios_puzzle_party(void) {
    MarioPuzzlePartyFallingBlock *block = HuPrcCurrentGet()->user_data;
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyPathSpace *below;
    s32 landed;
    s32 row;
    s32 pathIdx;
    s32 spaceIdx;
    s32 type;
    s32 ownerId;
    f32 speed;

    omPrcSetDestructor(HuPrcCurrentGet(), func_80108BB0_marios_puzzle_party);
    pathIdx = (block->x - D_80110080_marios_puzzle_party[block->board][0]) / 14;
    spaceIdx = (D_80110080_marios_puzzle_party[block->board][1] - block->y) / 7;
    space = &D_801102E0_marios_puzzle_party[block->board][pathIdx].spaces[spaceIdx];
    type = space->type;
    ownerId = space->ownerId;
    space->ownerId = -1;
    space->type = 0;
    if (type == 1) {
        below = &D_801102E0_marios_puzzle_party[block->board][pathIdx].spaces[spaceIdx + 1];
        below->ownerId = -1;
        below->type = 0;
    }
    landed = FALSE;
    while (TRUE) {
        pathIdx = (block->x - D_80110080_marios_puzzle_party[block->board][0]) / 14;
        spaceIdx = (D_80110080_marios_puzzle_party[block->board][1] - block->y) / 7;
        below = &D_801102E0_marios_puzzle_party[block->board][pathIdx].spaces[spaceIdx - 1];
        if (below->type == 0) {
            speed = 1.0f;
            while (TRUE) {
                block->y = block->y + speed;
                speed += 0.5f;
                if (speed > 6.0f) {
                    speed = 6.0f;
                }
                row = (D_80110080_marios_puzzle_party[block->board][1] - block->y) / 7;
                below = &D_801102E0_marios_puzzle_party[block->board][pathIdx].spaces[row];
                if (below->type != 0) {
                    space = &D_801102E0_marios_puzzle_party[block->board][pathIdx].spaces[row + 1];
                    block->y = D_80110080_marios_puzzle_party[block->board][1] - (row + 1) * 7;
                    space->y = block->y;
                    func_8010FF78_marios_puzzle_party(block->sprite, block->x, block->y);
                    space->sprite = block->sprite;
                    space->ownerId = ownerId;
                    space->type = type;
                    if (type == 1) {
                        space = &D_801102E0_marios_puzzle_party[block->board][pathIdx].spaces[row + 2];
                        space->sprite = block->sprite;
                        space->ownerId = ownerId;
                        space->type = 2;
                    }
                    break;
                } else {
                    func_8010FF78_marios_puzzle_party(block->sprite, block->x, block->y);
                    HuPrcVSleep();
                }
            }
        } else {
            landed = TRUE;
        }
        HuPrcVSleep();
        if (landed) {
            break;
        }
    }
    pathIdx = (block->x - D_80110080_marios_puzzle_party[block->board][0]) / 14;
    spaceIdx = (D_80110080_marios_puzzle_party[block->board][1] - block->y) / 7;
    if ((spaceIdx >= 20 && type == 1) || (spaceIdx >= 21 && type == 3)) {
        func_80107224_marios_puzzle_party(block->board, pathIdx, spaceIdx);
    } else if (block->unk_18 != 0) {
        func_8004AC98_main(0x3F9, block->board);
    }
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010913C_marios_puzzle_party(void) {
    func_80019C00_main(HuPrcCurrentGet()->user_data);
}

void func_80109160_marios_puzzle_party(void) {
    MarioPuzzlePartySquash *squash = HuPrcCurrentGet()->user_data;
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyPathSpace *other;
    s32 i = 1;
    s32 j;
    s32 squashing;
    s32 more;
    f32 scale;

    omPrcSetDestructor(HuPrcCurrentGet(), func_8010913C_marios_puzzle_party);
    while (TRUE) {
        space = &D_801102E0_marios_puzzle_party[squash->board][squash->pathIdx].spaces[i];
        if (space->type == 0 || space->type == 1) {
            break;
        }
        i++;
    }
    if (space->type != 0) {
        squashing = TRUE;
        scale = 1.0f;
        do {
            scale -= 0.2f;
            if (scale <= 0.5f) {
                scale = 0.5f;
                squashing = FALSE;
            }
            func_8010FFBC_marios_puzzle_party(space->sprite, 1.0f, scale);
            j = i + 2;
            more = TRUE;
            do {
                other = &D_801102E0_marios_puzzle_party[squash->board][squash->pathIdx].spaces[j];
                switch (other->type) {
                    case 1:
                        other->y = space->y - scale * 7.0f * 2.0f - (j - (i + 2)) * 7;
                        j++;
                        func_8010FF78_marios_puzzle_party(
                            other->sprite, D_80110080_marios_puzzle_party[squash->board][0] + squash->pathIdx * 14,
                            other->y);
                        j++;
                        break;
                    case 3:
                        other->y = space->y - scale * 7.0f * 2.0f - (j - (i + 2)) * 7;
                        j++;
                        func_8010FF78_marios_puzzle_party(
                            other->sprite, D_80110080_marios_puzzle_party[squash->board][0] + squash->pathIdx * 14,
                            other->y);
                        break;
                    case 0:
                        more = FALSE;
                        j++;
                        break;
                    default:
                        j++;
                        break;
                }
            } while (more);
            squash->cursor->y = space->y - scale * 7.0f * 2.0f - (j - (i + 2)) * 7 - 7.0f;
            HuSprPosSet(squash->sprGroup, 0, squash->x,
                        squash->cursor->y + D_801161A8_marios_puzzle_party[squash->board]);
            HuPrcVSleep();
        } while (squashing);
        space = &D_801102E0_marios_puzzle_party[squash->board][squash->pathIdx].spaces[i];
        i++;
        space->type = 3;
        j = i + 1;
        while (TRUE) {
            space = &D_801102E0_marios_puzzle_party[squash->board][squash->pathIdx].spaces[i];
            other = &D_801102E0_marios_puzzle_party[squash->board][squash->pathIdx].spaces[j];
            space->sprite = other->sprite;
            space->x = other->x;
            space->y = other->y;
            space->ownerId = other->ownerId;
            space->type = other->type;
            i++;
            if (other->type == 0) {
                break;
            }
            j++;
        }
    }
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_8010961C_marios_puzzle_party(s32 board, s32 x, s32 sprGroup, MarioPuzzlePartyCursor *cursor, s32 arg4) {
    MarioPuzzlePartySquash *squash;
    Process *process;
    s32 count[2];
    s32 height[2];
    s32 pathIdx;
    s32 side;
    s32 prevScore;

    pathIdx = x - 22;
    pathIdx = (pathIdx - D_80110080_marios_puzzle_party[board][0]) / 14 + 1;
    omAddPrcObj(func_8010D8E8_marios_puzzle_party, 0x4001, 0x800, 0)->user_data = (void *)board;
    func_8004AC98_main(0x3FA, board);
    omVibrate(board, 20, 0, 20);
    while (TRUE) {
        count[0] = func_80107070_marios_puzzle_party(board, pathIdx);
        count[1] = func_80107070_marios_puzzle_party(board, pathIdx + 1);
        side = !(count[1] < count[0]);
        if (func_80107108_marios_puzzle_party(board, pathIdx + side) == 0) {
            count[0] = func_80107000_marios_puzzle_party(board, pathIdx);
            count[1] = func_80107000_marios_puzzle_party(board, pathIdx + 1);
            if (side == 0 ? count[1] <= count[0] : count[0] <= count[1]) {
                break;
            }
        }
        height[0] = func_80107000_marios_puzzle_party(board, pathIdx) - 1;
        height[1] = func_80107000_marios_puzzle_party(board, pathIdx + 1) - 1;
        if (height[1] <= height[0]) {
            process = omAddPrcObj(func_80109160_marios_puzzle_party, 0x4001, 0x800, 0);
            HuPrcChildLink(HuPrcCurrentGet(), process);
            squash = process->user_data = HuMemAlloc(sizeof(MarioPuzzlePartySquash));
            squash->board = board;
            squash->sprGroup = sprGroup;
            squash->pathIdx = pathIdx;
            squash->x = x;
            squash->cursor = cursor;
        }
        if (height[0] <= height[1]) {
            func_8004AC98_main(0x3FB, board);
            process = omAddPrcObj(func_80109160_marios_puzzle_party, 0x4001, 0x800, 0);
            HuPrcChildLink(HuPrcCurrentGet(), process);
            squash = process->user_data = HuMemAlloc(sizeof(MarioPuzzlePartySquash));
            squash->board = board;
            squash->sprGroup = sprGroup;
            squash->pathIdx = pathIdx + 1;
            squash->x = x;
            squash->cursor = cursor;
        }
        HuPrcChildWatch();
    }
    prevScore = D_80116138_marios_puzzle_party[board];
    func_80108568_marios_puzzle_party(board, arg4);
    return prevScore < D_80116138_marios_puzzle_party[board];
}

void func_801098A0_marios_puzzle_party(void) {
    MarioPuzzlePartyScoreDisplay *display = HuPrcCurrentGet()->user_data;
    s32 board = display->board;
    s32 group = display->sprGroup;
    s32 started;
    s32 divisor;
    s32 digit;
    s32 i;

    D_80116128_marios_puzzle_party[board] = 0;
    for (i = 1; i < 6; i++) {
        HuSprGrpMemberSet(group, i, D_801160D2_marios_puzzle_party, 0);
        if (D_80116158_marios_puzzle_party == 0) {
            HuSprPosSet(group, i, -(i * 8) + 16, 12);
        } else {
            HuSprPosSet(group, i, -(i * 8) + 24, 12);
        }
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, 0x4000);
        HuSprPriSet(group, i, 0x1FE);
        func_800554C4_main(group, i, 0);
    }
    HuSprGrpMemberSet(group, 8, D_801160D6_marios_puzzle_party, 0);
    HuSprPosSet(group, 8, 0, 12);
    HuSprAttrReset(group, 8, 0xFFFF);
    HuSprAttrSet(group, 8, 0x4000);
    HuSprPriSet(group, 8, 0x1FF);
    func_800554C4_main(group, 8, 0);
    while (TRUE) {
        if (D_80116128_marios_puzzle_party[board] < 0) {
            D_80116128_marios_puzzle_party[board] = 0;
        }
        if (D_80116128_marios_puzzle_party[board] > 99999) {
            D_80116128_marios_puzzle_party[board] = 99999;
        }
        HuSprGrpMemberSet(group, 1, D_801160D2_marios_puzzle_party, D_80116128_marios_puzzle_party[board] % 10);
        for (i = 5; i >= 2; i--) {
            HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
        }
        for (i = 5, divisor = 10000, started = FALSE; i >= 2; i--, divisor /= 10) {
            digit = (D_80116128_marios_puzzle_party[board] / divisor) % 10;
            if (digit > 0 || divisor == 1 || started) {
                started = TRUE;
                HuSprAttrReset(group, i, HUSPR_ATTR_DISPOFF);
                HuSprGrpMemberSet(group, i, D_801160D2_marios_puzzle_party, digit);
            }
        }
        HuPrcVSleep();
    }
}

void func_80109C04_marios_puzzle_party(s32 board, s32 ownerId, s32 type, s32 pathIdx, s32 spaceIdx, s32 arg5) {
    MarioPuzzlePartyPathSpace *space;
    MarioPuzzlePartyFallingBlock *block;
    Process *process;

    func_80105D50_marios_puzzle_party(board, ownerId, type, pathIdx, spaceIdx);
    space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];
    if (space->type == 1 || space->type == 3) {
        process = omAddPrcObj(func_80108C80_marios_puzzle_party, 0x4001, 0x800, 0);
        HuPrcChildLink(HuPrcCurrentGet(), process);
        block = process->user_data = HuMemAlloc(sizeof(MarioPuzzlePartyFallingBlock));
        block->board = board;
        block->sprite = space->sprite;
        block->x = space->x;
        block->y = space->y;
        block->ownerId = space->ownerId;
        block->type = space->type;
        block->unk_18 = arg5;
    }
}

void func_80109D24_marios_puzzle_party(void) {
    MarioPuzzlePartyCursor *cursor = HuPrcCurrentGet()->user_data;
    s32 board = cursor->board;
    s32 falling;

    if (D_80116188_marios_puzzle_party[board] < 10) {
        cursor->blockOwners[0] = D_801167B0_marios_puzzle_party[D_801168A0_marios_puzzle_party[board]][0];
        cursor->blockOwners[1] = D_801167B0_marios_puzzle_party[D_801168A0_marios_puzzle_party[board]][1];
        D_801168A0_marios_puzzle_party[board]++;
        if (D_801168A0_marios_puzzle_party[board] >= 30) {
            D_801168A0_marios_puzzle_party[board] = 0;
        }
        cursor->x = D_80110080_marios_puzzle_party[board][0] + 35;
        cursor->y = D_80110080_marios_puzzle_party[board][1] - 231;
        cursor->blockSprites[0] =
            func_80106A44_marios_puzzle_party(board, cursor->blockOwners[0], 1, cursor->x, cursor->y);
        cursor->blockSprites[1] =
            func_80106A44_marios_puzzle_party(board, cursor->blockOwners[1], 1, cursor->x, cursor->y - 14.0f);
    } else {
        cursor->x = D_80110080_marios_puzzle_party[board][0] + 42;
        cursor->y = D_80110080_marios_puzzle_party[board][1] - 231;
        cursor->blockOwners[0] = 7;
        cursor->blockSprites[0] = HuSprGrpCreate(1, 5);
        HuSprGrpMemberSet(cursor->blockSprites[0], 0, D_801160AE_marios_puzzle_party, 0);
        HuSprPosSet(cursor->blockSprites[0], 0, cursor->x, D_801161A8_marios_puzzle_party[board] + cursor->y);
        HuSprAttrReset(cursor->blockSprites[0], 0, 0xFFFF);
        HuSprAttrSet(cursor->blockSprites[0], 0, 8);
    }
    falling = TRUE;
    do {
        cursor->y += 5.0f;
        if (cursor->blockOwners[0] != 7) {
            if (cursor->y > D_80110080_marios_puzzle_party[board][1] - 182) {
                cursor->y = D_80110080_marios_puzzle_party[board][1] - 182;
                falling = FALSE;
            }
            func_8010FF78_marios_puzzle_party(cursor->blockSprites[0], cursor->x, cursor->y);
            func_8010FF78_marios_puzzle_party(cursor->blockSprites[1], cursor->x, cursor->y - 14.0f);
        } else {
            if (cursor->y > D_80110080_marios_puzzle_party[board][1] - 196) {
                cursor->y = D_80110080_marios_puzzle_party[board][1] - 196;
                falling = FALSE;
            }
            HuSprPosSet(cursor->blockSprites[0], 0, cursor->x, D_801161A8_marios_puzzle_party[board] + cursor->y);
        }
        HuPrcVSleep();
    } while (falling);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010A0D8_marios_puzzle_party(void) {
    f32 xOffsets[5] = { -95.0f, -30.0f, 30.0f, 95.0f, 0.0f };
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    s32 i;
    s32 group0;
    s32 group1;
    s32 group2;
    f32 angle;
    f32 y;
    f32 z;

    if (board == 4) {
        func_8004AC98_main(0x3FE, 0);
    } else {
        func_8004AC98_main(0x3FE, board);
    }
    group0 = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(group0, 0, D_801160B2_marios_puzzle_party, 0);
    HuSprAttrReset(group0, 0, 0xFFFF);
    HuSprPriSet(group0, 0, 0x200);
    HuSprAttrSet(group0, 0, 0x4000);
    group1 = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(group1, 0, D_801160D2_marios_puzzle_party, 0);
    HuSprAttrReset(group1, 0, 0xFFFF);
    HuSprPriSet(group1, 0, 0x1FE);
    HuSprAttrSet(group1, 0, 0x4000);
    group2 = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(group2, 0, D_801160D6_marios_puzzle_party, 0);
    HuSprAttrReset(group2, 0, 0xFFFF);
    HuSprPriSet(group2, 0, 0x1FF);
    HuSprAttrSet(group2, 0, 0x4000);
    z = -5000.0f;
    angle = 0.0f;
    for (i = 0; i < 45; i++) {
        y = sindf(angle) * 150.0f;
        angle += 6.0f;
        z += 111.111115f;
        func_80054B1C_main(group0, 0, 0, xOffsets[board], y, z);
        func_80054EE0_main(group0, 0, 0, xOffsets[board], y, z);
        if (D_80116158_marios_puzzle_party == 0) {
            func_80054B1C_main(group1, 0, 0, xOffsets[board] + 8.0f, y - 12.0f, z);
            func_80054EE0_main(group1, 0, 0, xOffsets[board] + 8.0f, y - 12.0f, z);
        } else {
            func_80054B1C_main(group1, 0, 0, xOffsets[board] + 16.0f, y - 12.0f, z);
            func_80054EE0_main(group1, 0, 0, xOffsets[board] + 16.0f, y - 12.0f, z);
        }
        func_80054B1C_main(group2, 0, 0, xOffsets[board], y - 12.0f, z);
        func_80054EE0_main(group2, 0, 0, xOffsets[board], y - 12.0f, z);
        HuPrcVSleep();
    }
    HuSprGrpKill(group0);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_8010A4B4_marios_puzzle_party(s32 board, s32 x, s32 y) {
    s32 pathIdx = (x - D_80110080_marios_puzzle_party[board][0]) / 14;
    s32 spaceIdx = (D_80110080_marios_puzzle_party[board][1] - y) / 7;
    MarioPuzzlePartyPathSpace *space;
    s32 i;

    for (i = 0; i < 4; i++) {
        space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx + i];
        if (space->type != 0) {
            break;
        }
    }
    return !(i < 4);
}

#ifdef NON_MATCHING
void func_8010A588_marios_puzzle_party(void) {
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    MarioPuzzlePartyCursor *next = &D_80116308_marios_puzzle_party[board];
    s32 group;
    s32 x;
    s32 y;
    f32 angle;

    if (next->blockOwners[0] != 7) {
        func_8010D290_marios_puzzle_party(board, (next->x - D_80110080_marios_puzzle_party[board][0]) / 14.0f,
                                          (D_80110080_marios_puzzle_party[board][1] - next->y) / 7.0f);
        func_80110000_marios_puzzle_party(next->blockSprites[0]);
        func_80110000_marios_puzzle_party(next->blockSprites[1]);
    } else {
        HuSprAttrSet(next->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
    }
    angle = 0.0f;
    while (TRUE) {
        angle += 10.0f;
        if (angle > 360.0f) {
            angle = 360.0f;
        }
        HuSprZRotSet(D_801161D8_marios_puzzle_party[board], 0, sindf(angle) * 45.0f);
        HuPrcVSleep();
        if (angle == 360.0f) {
            break;
        }
    }
    HuSprGrpKill(D_801161E8_marios_puzzle_party[board]);
    group = D_801161E8_marios_puzzle_party[board] = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(group, 0, D_80116096_marios_puzzle_party, 0);
    HuSprPosSet(group, 0, D_80110080_marios_puzzle_party[board][0] + 42,
                D_801161A8_marios_puzzle_party[board] - 161 + D_80110080_marios_puzzle_party[board][1]);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x4008);
    HuSprPriSet(group, 0, 0x300);
    omAddPrcObj(func_8010CF4C_marios_puzzle_party, 0x4001, 0x800, 0)->user_data = (void *)board;
    HuPrcSleep(10);
    x = D_80110080_marios_puzzle_party[board][0] + 42;
    y = D_80110080_marios_puzzle_party[board][1] - 181;
    while (y < 130) {
        y += 3;
        HuSprPosSet(D_801161D8_marios_puzzle_party[board], 0, x, y);
        HuPrcVSleep();
    }
    y = 130;
    HuSprPosSet(D_801161D8_marios_puzzle_party[board], 0, x, 130);
    angle = 0.0f;
    while (TRUE) {
        angle += 8.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        HuSprPosSet(D_801161D8_marios_puzzle_party[board], 0, x, y + sindf(angle) * 3.0f);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010A588_marios_puzzle_party);
#endif

void func_8010A958_marios_puzzle_party(void) {
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    MarioPuzzlePartyCursor *cursor = &D_80116238_marios_puzzle_party[board];
    MarioPuzzlePartyCursor *next = &D_80116308_marios_puzzle_party[board];
    MarioPuzzlePartyPathSpace *space;
    s32 pathIdx;
    s32 spaceIdx;

    if (D_801160E4_marios_puzzle_party != board) {
        if (D_801160E8_marios_puzzle_party == 0) {
            if (D_80116158_marios_puzzle_party != 2) {
                omVibrate(board, 10, 0, 10);
            } else if (board == 0) {
                omVibrate(0, 10, 0, 10);
            }
            D_80116168_marios_puzzle_party[board] = 1;
            omAddPrcObj(func_8010A588_marios_puzzle_party, 0x4001, 0x1000, 0)->user_data =
                HuPrcCurrentGet()->user_data;
        }
    }
    if (D_801160E8_marios_puzzle_party == 0) {
        HuSprBankSet(D_801161D8_marios_puzzle_party[board], 0, 0, 2);
        func_800550F4_main(D_801161D8_marios_puzzle_party[board], 0, 1);
        HuSprAttrReset(D_801161D8_marios_puzzle_party[board], 0, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(D_801161D8_marios_puzzle_party[board], 9, HUSPR_ATTR_DISPOFF);
        if (D_801160E8_marios_puzzle_party == 0) {
            if (next->blockOwners[0] != 7) {
                func_8010D290_marios_puzzle_party(board,
                                                  (next->x - D_80110080_marios_puzzle_party[board][0]) / 14.0f,
                                                  (D_80110080_marios_puzzle_party[board][1] - next->y) / 7.0f);
                func_80110000_marios_puzzle_party(next->blockSprites[0]);
                func_80110000_marios_puzzle_party(next->blockSprites[1]);
            } else {
                HuSprAttrSet(next->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
            }
        }
    }
    D_80116178_marios_puzzle_party[board] = 1;
    if (D_801160E4_marios_puzzle_party == board) {
        HuAudFXPlay(0x3FF);
        for (spaceIdx = 1; spaceIdx < 40; spaceIdx++) {
            for (pathIdx = 1; pathIdx < 5; pathIdx++) {
                space = &D_801102E0_marios_puzzle_party[board][pathIdx].spaces[spaceIdx];
                if (space->type == 3 || space->type == 1) {
                    func_80107224_marios_puzzle_party(board, pathIdx, spaceIdx);
                }
            }
        }
        if (D_801160E8_marios_puzzle_party == 0) {
            if (cursor->blockOwners[0] != 7) {
                func_8010D290_marios_puzzle_party(board,
                                                  (cursor->x - D_80110080_marios_puzzle_party[board][0]) / 14.0f,
                                                  (D_80110080_marios_puzzle_party[board][1] - cursor->y) / 7.0f);
                func_80110000_marios_puzzle_party(cursor->blockSprites[0]);
                func_80110000_marios_puzzle_party(cursor->blockSprites[1]);
            } else if (D_80116228_marios_puzzle_party[board] != -1) {
                HuSprAttrSet(D_80116228_marios_puzzle_party[board], 0, HUSPR_ATTR_DISPOFF);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010AD20_marios_puzzle_party);

void func_8010CF4C_marios_puzzle_party(void) {
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    f32 speed = 0.0f;

    D_801161C8_marios_puzzle_party[board] = 0;
    while (D_801161C8_marios_puzzle_party[board] < 300) {
        speed += 0.5f;
        D_801161C8_marios_puzzle_party[board] = D_801161C8_marios_puzzle_party[board] + speed;
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010CFF8_marios_puzzle_party(omObjData *obj) {
    MarioPuzzlePartyDebris *debris = &D_80114EF0_marios_puzzle_party[obj->work[0]];

    switch (obj->work[1]) {
        case 0:
            switch (obj->work[2]) {
                case 0:
                    debris->vy = -3.0f;
                    debris->vx = -1.0f - (rand8() % 10) * 0.1f;
                    break;
                case 1:
                    debris->vy = -5.0f;
                    debris->vx = -1.0f - (rand8() % 10) * 0.1f;
                    break;
                case 2:
                    debris->vy = -3.0f;
                    debris->vx = (rand8() % 10) * 0.1f + 1.0f;
                    break;
                default:
                    debris->vy = -5.0f;
                    debris->vx = (rand8() % 10) * 0.1f + 1.0f;
                    break;
            }
            obj->work[1] = 1;
        case 1:
            debris->vy += 1.0f;
            debris->y += debris->vy;
            debris->x += debris->vx;
            func_8010FF78_marios_puzzle_party(debris->sprite, debris->x, debris->y);
            if (debris->y > 250.0f) {
                obj->work[1] = 2;
            }
            break;
        case 2:
            func_80110000_marios_puzzle_party(debris->sprite);
            debris->active = FALSE;
            obj->work[1] = 100;
            omDelObj(obj);
            break;
    }
}

void func_8010D290_marios_puzzle_party(s32 board, s32 pathIdx, s32 spaceIdx) {
    MarioPuzzlePartyDebris *debris;
    omObjData *obj;
    s32 slots[4];
    s32 count;
    s32 i;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;

    debris = D_80114EF0_marios_puzzle_party;
    count = 0;
    for (i = 0; i < 160; i++, debris++) {
        if (debris->active == FALSE) {
            slots[count] = i;
            count++;
            if (count >= 4) {
                break;
            }
        }
    }
    if (i < 160) {
        x = D_80110080_marios_puzzle_party[board][0] + pathIdx * 14;
        y = D_80110080_marios_puzzle_party[board][1] - spaceIdx * 7;
        i = 0;
        for (dx = 0; dx < 8; dx += 7) {
            for (dy = 0; dy >= -7; dy -= 7) {
                debris = &D_80114EF0_marios_puzzle_party[slots[i]];
                debris->active = TRUE;
                debris->x = x + dx;
                debris->y = y + dy;
                debris->unk_14 = 1.0f;
                debris->sprite = func_8010FEDC_marios_puzzle_party(28, debris->x, debris->y);
                obj = omAddObj(100, 0, 0, -1, func_8010CFF8_marios_puzzle_party);
                obj->work[0] = slots[i];
                obj->work[1] = 0;
                obj->work[2] = i;
                i++;
            }
        }
    }
}

void func_8010D46C_marios_puzzle_party(void) {
    func_80019C00_main(HuPrcCurrentGet()->user_data);
}

void func_8010D490_marios_puzzle_party(void) {
    MarioPuzzlePartySparkle *sparkle = HuPrcCurrentGet()->user_data;
    f32 baseX;
    f32 baseY;
    f32 vx;
    f32 vy;
    f32 scale;

    omPrcSetDestructor(HuPrcCurrentGet(), func_8010D46C_marios_puzzle_party);
    sparkle->sprGroup = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(sparkle->sprGroup, 0, D_8011608E_marios_puzzle_party, 0);
    HuSprAttrReset(sparkle->sprGroup, 0, 0xFFFF);
    HuSprAttrSet(sparkle->sprGroup, 0, 0xC008);
    HuSprPriSet(sparkle->sprGroup, 0, 0x1000);
    baseX = sparkle->x;
    baseY = sparkle->y;
    while (TRUE) {
        HuPrcSleep(rand8() % 90);
        HuSprAttrReset(sparkle->sprGroup, 0, HUSPR_ATTR_DISPOFF);
        sparkle->x = baseX;
        sparkle->y = baseY;
        vx = sparkle->vx;
        vy = sparkle->vy;
        switch (sparkle->spawnMode) {
            case 0:
                sparkle->x = baseX + rand8() % 40 - 20.0f;
                break;
            case 1:
                sparkle->y = baseY + rand8() % 40 - 20.0f;
                break;
            default:
                sparkle->x = baseX + rand8() % 20 - 10.0f;
                sparkle->y = baseY + rand8() % 20 - 10.0f;
                break;
        }
        switch (rand8() & 1) {
            case 0:
            default:
                scale = 1.2f;
                break;
            case 1:
                scale = 2.0f;
                if (vx != 0.0f) {
                    if (vx > 0.0f) {
                        vx -= 1.0f;
                    } else {
                        vx += 1.0f;
                    }
                }
                if (vy != 0.0f) {
                    if (vy > 0.0f) {
                        vy -= 1.0f;
                    } else {
                        vy += 1.0f;
                    }
                }
                break;
        }
        sparkle->scale = scale;
        while (sparkle->scale > 0.0f) {
            switch (sparkle->moveMode) {
                case 0:
                    sparkle->y = vy + sparkle->y;
                    break;
                case 1:
                    sparkle->x = vx + sparkle->x;
                    break;
                default:
                    sparkle->x = vx + sparkle->x;
                    sparkle->y = vy + sparkle->y;
                    break;
            }
            HuSprPosSet(sparkle->sprGroup, 0, sparkle->x, sparkle->y);
            HuSprScaleSet(sparkle->sprGroup, 0, sparkle->scale, sparkle->scale);
            HuPrcVSleep();
            sparkle->scale -= 0.03f;
        }
        HuSprAttrSet(sparkle->sprGroup, 0, HUSPR_ATTR_DISPOFF);
    }
}

void func_8010D8E8_marios_puzzle_party(void) {
    s32 board = (s32)HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;

    while (TRUE) {
        angle += 90.0f;
        if (angle > 1080.0f) {
            break;
        }
        D_801161B8_marios_puzzle_party[board] = sindf(angle) * 2.0f;
        HuPrcVSleep();
    }
    D_801161B8_marios_puzzle_party[board] = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010D9AC_marios_puzzle_party(void) {
    MarioPuzzlePartyCursor *cursor;
    MarioPuzzlePartyCursor *next;
    s32 i;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            cursor = &D_80116238_marios_puzzle_party[i];
            if (cursor->blockOwners[0] == 7 && D_80116228_marios_puzzle_party[i] != -1) {
                if (omPauseChk() + D_800D6A90_main != 0 || D_80116178_marios_puzzle_party[i] != 0) {
                    HuSprAttrSet(D_80116228_marios_puzzle_party[i], 0, HUSPR_ATTR_DISPOFF);
                } else {
                    HuSprAttrReset(D_80116228_marios_puzzle_party[i], 0, HUSPR_ATTR_DISPOFF);
                }
            }
            next = &D_80116308_marios_puzzle_party[i];
            if (next->blockOwners[0] == 7) {
                if (omPauseChk() + D_800D6A90_main != 0 || D_80116178_marios_puzzle_party[i] != 0) {
                    HuSprAttrSet(next->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                } else {
                    HuSprAttrReset(next->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                }
            }
            if (omPauseChk() + D_800D6A90_main != 0 || D_80116178_marios_puzzle_party[i] != 0) {
                espDispOff(cursor->sprite);
            } else {
                espDispOn(cursor->sprite);
            }
        }
        HuPrcVSleep();
    }
}

void func_8010DB98_marios_puzzle_party(void) {
    s32 stopped[4];
    f32 angle[4];
    f32 offset[4];
    MarioPuzzlePartyCursor *cursor;
    s32 i;

    for (i = 0; i < 4; i++) {
        offset[i] = 0.0f;
        angle[i] = 0.0f;
        stopped[i] = FALSE;
    }
    while (TRUE) {
        for (i = 0; i < 4; i++) {
            if (stopped[i] == FALSE && func_800E6E8C_minigame() != 0) {
                angle[i] += 8.0f;
                offset[i] = sindf(i * 45.0f + angle[i]) * 3.0f;
                if (angle[i] > 360.0f) {
                    angle[i] -= 360.0f;
                }
                if ((angle[i] > 360.0f || angle[i] > 180.0f) && D_80116168_marios_puzzle_party[i] != 0) {
                    stopped[i] = TRUE;
                    offset[i] = 0.0f;
                }
            }
            D_801161A8_marios_puzzle_party[i] =
                (s32)offset[i] + D_801161B8_marios_puzzle_party[i] + D_801161C8_marios_puzzle_party[i];
            func_8011006C_marios_puzzle_party(i, D_801161A8_marios_puzzle_party[i]);
            if (stopped[i] == FALSE) {
                HuSprPosSet(D_801161D8_marios_puzzle_party[i], 0, D_80110080_marios_puzzle_party[i][0] + 42,
                            D_801161A8_marios_puzzle_party[i] + D_80110080_marios_puzzle_party[i][1] - 181);
            }
            HuSprPosSet(D_801161E8_marios_puzzle_party[i], 0, D_80110080_marios_puzzle_party[i][0] + 42,
                        D_801161A8_marios_puzzle_party[i] + D_80110080_marios_puzzle_party[i][1] - 160);
            HuSprPosSet(D_801161F8_marios_puzzle_party[i], 0, D_80110080_marios_puzzle_party[i][0] + 42,
                        D_801161A8_marios_puzzle_party[i] + D_80110080_marios_puzzle_party[i][1] - 76);
            HuSprPosSet(D_80116208_marios_puzzle_party[i], 0, D_80110080_marios_puzzle_party[i][0] + 42,
                        D_801161A8_marios_puzzle_party[i] + D_80110080_marios_puzzle_party[i][1] - 76);
            HuSprPosSet(D_80116218_marios_puzzle_party[i], 0, D_80110080_marios_puzzle_party[i][0] + 42,
                        D_801161A8_marios_puzzle_party[i] + D_80110080_marios_puzzle_party[i][1] - 104);
            cursor = &D_80116238_marios_puzzle_party[i];
            if (cursor->blockOwners[0] != 7) {
                espPosSet(cursor->sprite, cursor->x + 7.0f, D_801161A8_marios_puzzle_party[i] + cursor->y);
            } else {
                if (D_80116228_marios_puzzle_party[i] != -1) {
                    HuSprPosSet(cursor->blockSprites[0], 0, cursor->x, D_801161A8_marios_puzzle_party[i] + cursor->y);
                    if (omPauseChk() + D_800D6A90_main != 0) {
                        HuSprAttrSet(cursor->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                    } else {
                        HuSprAttrReset(cursor->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                    }
                }
                espPosSet(cursor->sprite, cursor->x + 7.0f, cursor->y + 7.0f + D_801161A8_marios_puzzle_party[i]);
            }
            cursor = &D_80116308_marios_puzzle_party[i];
            if (cursor->blockOwners[0] == 7) {
                HuSprPosSet(cursor->blockSprites[0], 0, cursor->x, D_801161A8_marios_puzzle_party[i] + cursor->y);
                if (omPauseChk() + D_800D6A90_main != 0) {
                    HuSprAttrSet(cursor->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                } else {
                    HuSprAttrReset(cursor->blockSprites[0], 0, HUSPR_ATTR_DISPOFF);
                }
            }
        }
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
void func_8010E12C_marios_puzzle_party(void) {
    s32 group = HuSprGrpCreate(6, 5);
    s32 record;
    s32 started;
    s32 divisor;
    s32 digit;
    s32 xOffset;
    s32 width;
    s32 i;
    f32 angle;

    HuSprGrpMemberSet(group, 0, D_801160A2_marios_puzzle_party, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
    func_800554C4_main(group, 0, -1);
    HuSprPriSet(group, 0, 0x100);
    record = GWMgRecordGet(8);
    for (i = 1, divisor = 1000, started = FALSE; i < 5; i++, divisor /= 10) {
        digit = (record / divisor) % 10;
        HuSprGrpMemberSet(group, i, D_801160A2_marios_puzzle_party, digit);
        func_800550F4_main(group, i, 1);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, 8);
        if (!started) {
            if (digit == 0 && i != 4) {
                HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
            } else {
                started = TRUE;
            }
        }
        HuSprPriSet(group, i, 0x100);
        func_800554C4_main(group, i, 0);
    }
    for (i = 4, divisor = 1000; i >= 2; i--, divisor /= 10) {
        if (record / divisor != 0) {
            break;
        }
    }
    xOffset = 58;
    width = i * 12 + 10;
    for (i = 1; i < 5; i++) {
        HuSprPosSet(group, i, i * 12 - xOffset + (width >> 1), 0);
    }
    HuSprPosSet(group, 5, (width >> 1) + 65 - xOffset, 0);
    HuSprPosSet(group, 0, 90 - (width >> 1), 30);
    HuSprGrpMemberSet(group, 5, D_801160A6_marios_puzzle_party, 0);
    func_800550F4_main(group, 5, 0);
    HuSprAttrReset(group, 5, 0xFFFF);
    HuSprAttrSet(group, 5, 8);
    HuSprPriSet(group, 5, 0x100);
    func_800554C4_main(group, 5, 0);
    while (D_80110140_marios_puzzle_party.unk00 != 4) {
        HuPrcVSleep();
    }
    if (D_801160E4_marios_puzzle_party != -1 && record < D_80116128_marios_puzzle_party[0]) {
        record = D_80116128_marios_puzzle_party[0];
        for (i = 1, divisor = 1000, started = FALSE; i < 5; i++, divisor /= 10) {
            digit = (record / divisor) % 10;
            HuSprGrpMemberSet(group, i, D_801160A2_marios_puzzle_party, digit);
            func_800550F4_main(group, i, 1);
            HuSprAttrReset(group, i, 0xFFFF);
            HuSprAttrSet(group, i, 8);
            if (!started) {
                if (digit == 0 && i != 4) {
                    HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
                } else {
                    started = TRUE;
                }
            }
            HuSprPriSet(group, i, 0x100);
            func_800554C4_main(group, i, 0);
        }
        for (i = 4, divisor = 1000; i >= 2; i--, divisor /= 10) {
            if (record / divisor != 0) {
                break;
            }
        }
        xOffset = 58;
        width = i * 12 + 10;
        for (i = 1; i < 5; i++) {
            HuSprPosSet(group, i, i * 12 - xOffset + (width >> 1), 0);
        }
        HuSprPosSet(group, 5, (width >> 1) + 65 - xOffset, 0);
        HuSprPosSet(group, 0, 90 - (width >> 1), 30);
        for (angle = 0.0f; angle < 180.0f; angle += 9.0f) {
            for (i = 0; i < 6; i++) {
                HuSprScaleSet(group, i, sindf(angle) + 1.0f, sindf(angle) + 1.0f);
            }
            HuPrcVSleep();
        }
        for (i = 0; i < 6; i++) {
            HuSprScaleSet(group, i, 1.0f, 1.0f);
        }
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010E12C_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
void func_8010E868_marios_puzzle_party(s16 group, s32 time) {
    s32 minutes;
    s32 tens;
    s32 seconds;
    s32 tenths;

    minutes = time / 3600;
    HuSprBankSet(group, 1, minutes, 0);
    func_800550F4_main(group, 1, 1);
    time -= minutes * 3600;
    HuSprBankSet(group, 2, 10, 0);
    func_800550F4_main(group, 2, 1);
    tens = time / 600;
    HuSprBankSet(group, 3, tens, 0);
    func_800550F4_main(group, 3, 1);
    time -= tens * 600;
    seconds = time / 60;
    HuSprBankSet(group, 4, seconds, 0);
    func_800550F4_main(group, 4, 1);
    time = time * 100 / 60 - seconds * 100;
    HuSprBankSet(group, 5, 11, 0);
    func_800550F4_main(group, 5, 1);
    tenths = time / 10;
    HuSprBankSet(group, 6, tenths, 0);
    func_800550F4_main(group, 6, 1);
    HuSprBankSet(group, 7, time - tenths * 10, 0);
    func_800550F4_main(group, 7, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010E868_marios_puzzle_party);
#endif

#ifdef NON_MATCHING
void func_8010EAA0_marios_puzzle_party(void) {
    s32 group = HuSprGrpCreate(8, 5);
    s32 i;
    s32 x;

    HuSprGrpMemberSet(group, 0, D_801160AA_marios_puzzle_party, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
    func_800554C4_main(group, 0, -1);
    HuSprPriSet(group, 0, 0x100);
    HuSprPosSet(group, 0, 215, 30);
    D_80116160_marios_puzzle_party = 5400;
    for (i = 1, x = 0; i < 8; i++) {
        func_800550F4_main(group, i, 1);
        HuSprGrpMemberSet(group, i, D_801160AA_marios_puzzle_party, 0);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, 8);
        HuSprPriSet(group, i, 0x100);
        func_800554C4_main(group, i, 0);
        HuSprPosSet(group, i, x, 0);
        switch (i) {
            case 1:
                x += 4;
                break;
            case 4:
                x += 8;
                break;
            default:
                x += 12;
                break;
        }
    }
    func_8010E868_marios_puzzle_party(group, D_80116160_marios_puzzle_party * 2);
    while (func_800E6E8C_minigame() != 2) {
        HuPrcVSleep();
    }
    while (D_80116160_marios_puzzle_party != 0) {
        if (D_80116168_marios_puzzle_party[0] != 0) {
            break;
        }
        func_8010E868_marios_puzzle_party(group, D_80116160_marios_puzzle_party * 2);
        HuPrcVSleep();
        D_80116160_marios_puzzle_party--;
    }
    func_8010E868_marios_puzzle_party(group, D_80116160_marios_puzzle_party * 2);
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010EAA0_marios_puzzle_party);
#endif

void func_8010ECD8_marios_puzzle_party(void) {
    s32 startX = (s32)HuPrcCurrentGet()->user_data;
    s32 group = HuSprGrpCreate(1, 5);
    f32 x;
    f32 y;
    f32 speed;

    HuSprGrpMemberSet(group, 0, D_801160AE_marios_puzzle_party, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 8);
    HuSprScaleSet(group, 0, 0.8f, 0.8f);
    x = startX;
    while (TRUE) {
        HuPrcSleep(rand8() % 30 + 300);
        if (D_80116160_marios_puzzle_party < 300 || D_80116168_marios_puzzle_party[0] != 0) {
            break;
        }
        y = -30.0f;
        speed = 0.0f;
        do {
            speed += 0.3f;
            if (speed > 7.0f) {
                speed = 7.0f;
            }
            y += speed;
            HuSprPosSet(group, 0, x, y);
            HuPrcVSleep();
        } while (y < 270.0f);
    }
    omDelPrcObj(NULL);
}

void func_8010EEB0_marios_puzzle_party(void) {
    s32 i;

    for (i = 0; i < D_80116100_marios_puzzle_party; i++) {
        if (D_80116168_marios_puzzle_party[i] == 0) {
            omDelPrcObj(D_801163D8_marios_puzzle_party[i]);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1F_marios_puzzle_party/1F3B90", func_8010EF30_marios_puzzle_party);
