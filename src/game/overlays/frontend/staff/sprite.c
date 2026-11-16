#include "staff.h"

u32 staff_backStarPad[3] = { 0xFFFFFFC8, 0xFFFFFFFF, 0xC8F07109 }; /* Unreferenced. */
s32 staff_backStarSprTbl[4] = { 0x16001E, 0x16001F, 0x160020, 0x160021 };
u8 staff_backStarNumTbl[4] = { 6, 8, 16, 32 };
u16 staff_backStarPriTbl[4] = { 0xF000, 0xF001, 0xF002, 0xF003 };
f32 staff_backStarSpeedTbl[4] = { 6.0f, 4.0f, 2.0f, 1.0f };
s16 staff_backSprSpeedTbl[4] = { 2, 6, 6, 0 };
u16 staff_backSprPriTbl[4] = { 402, 400, 400, 0 };
StaffPos2s staff_backSprPosTbl[3] = { { 160, 175 }, { 38, 185 }, { 286, 194 } };
s32 staff_backSprTbl[3] = { 0x16001B, 0x16001C, 0x16001D };
s32 staff_shootStarSprTbl[2] = { 0x160022, 0x160023 };

UnkStaff_7 *staff_BackStarCreate(void) {
    UnkStaff_7 *work;
    UnkStaff_7 *ptr;
    Vec2f *pos;
    f32 *vel;
    f32 *speed;
    f32 baseSpeed;
    f32 spread;
    u32 random;
    s32 x;
    s32 y;
    s16 i;
    s16 j;
    s16 grpId;
    s16 animId;
    u16 pri;
    s16 count;
    u8 red;
    u8 green;
    u8 blue;

    work = HuMemAllocTag(sizeof(UnkStaff_7) * 4, TAG_OVERLAY);
    memset(work, 0, sizeof(UnkStaff_7) * 4);
    for (i = 0, ptr = work; i < 4; i++, ptr++) {
        count = staff_backStarNumTbl[i];
        pos = HuMemAllocTag(count * sizeof(Vec2f), TAG_OVERLAY);
        vel = HuMemAllocTag(count * sizeof(f32), TAG_OVERLAY);
        speed = HuMemAllocTag(count * sizeof(f32), TAG_OVERLAY);
        grpId = HuSprGrpCreate(count, 0);
        animId = HuSprAnimDataRead(staff_backStarSprTbl[i]);
        pri = staff_backStarPriTbl[i];
        ptr->unk_00 = pos;
        ptr->unk_0C = grpId;
        ptr->unk_0E = animId;
        ptr->unk_04 = vel;
        ptr->unk_08 = speed;
        ptr->count = count;
        baseSpeed = staff_backStarSpeedTbl[i];
        for (j = 0; j < count; j++, pos++, vel++, speed++) {
            HuSprTPLvlSet(grpId, j, 0x100);
            HuSprAttrReset(grpId, j, 0xFFFF);
            HuSprAttrSet(grpId, j, 0x5000);
            HuSprScaleSet(grpId, j, 1.0f, 1.0f);
            HuSprAnimModeSet(grpId, j, HUSPR_ANIM_MODE_STOP);
            HuSprGrpMemberSet(grpId, j, animId, 0);
            HuSprPriSet(grpId, j, pri);
            random = staff_Rand();
            red = random | 0xC0;
            random >>= 7;
            green = random | 0xC0;
            random >>= 7;
            blue = random | 0xC0;
            HuSprColorSet(grpId, j, red, green, blue);
            random = staff_Rand() & 0x7FFFFFFF;
            x = random % 320;
            random >>= 6;
            y = random % 304 - 64;
            pos->x = x;
            pos->y = y;
            HuSprPosSet(grpId, j, x, y);
            *vel = 0;
            spread = baseSpeed / 16.0f;
            random >>= 6;
            x = (random & 3) - 1;
            *speed = baseSpeed + spread * x;
        }
    }
    return work;
}

void staff_BackStarKill(UnkStaff_7 *arg0) {
    s32 i;
    UnkStaff_7 *ptr;

    for (i = 0, ptr = arg0; i < 4; i++, ptr++) {
        HuSprGrpKill(ptr->unk_0C);
        HuSprAnimKill(ptr->unk_0E);
        HuMemFree(ptr->unk_00);
        HuMemFree(ptr->unk_04);
        HuMemFree(ptr->unk_08);
    }
    HuMemFree(arg0);
}

void staff_BackStarSpeedSet(UnkStaff_7 *arg0, f32 arg1) {
    s16 i;
    s16 j;
    s16 count;
    f32 *dest;
    f32 *src;
    UnkStaff_7 *ptr;

    for (i = 0, ptr = arg0; i < 4; i++, ptr++) {
        dest = ptr->unk_04;
        src = ptr->unk_08;
        count = ptr->count;
        for (j = 0; j < count; j++, dest++, src++) {
            *dest = arg1 * *src;
        }
    }
}

void staff_BackStarMove(UnkStaff_7 *arg0) {
    UnkStaff_7 *ptr;
    Vec2f *pos;
    f32 *vel;
    u32 random;
    s16 x;
    s16 i;
    s16 j;
    s16 grpId;
    s16 count;

    for (i = 0, ptr = arg0; i < 4; i++, ptr++) {
        vel = ptr->unk_04;
        grpId = ptr->unk_0C;
        pos = ptr->unk_00;
        count = ptr->count;
        for (j = 0; j < count; j++, pos++, vel++) {
            pos->y += *vel;
            if (pos->y >= 240.0f) {
                random = staff_Rand() & 0x7FFFFFFF;
                if (i == 0) {
                    x = random % 160;
                    random >>= 5;
                    x += random % 160;
                    pos->x = x;
                } else {
                    pos->x = random % 320;
                }
                random >>= 6;
                pos->y = -(s32)(random & 0x1F);
            }
            HuSprPosSet(grpId, j, pos->x, pos->y);
        }
    }
}

const char staff_emptyStr[] = "";

void staff_BackStarTwinkle(UnkStaff_7 *arg0) {
    UnkStaff_7 *ptr;
    u32 random;
    s16 counter;
    s16 i;
    s16 j;
    s16 grpId;
    s16 count;
    s32 tpLvl;
    u32 bits;

    random = 0;
    counter = 0;
    for (i = 0, ptr = arg0; i < 4; i++, ptr++) {
        grpId = ptr->unk_0C;
        count = ptr->count;
        for (j = 0; j < count; j++) {
            counter -= 4;
            if (counter < 0) {
                counter = 31;
                random = staff_Rand();
            }
            bits = random & 0xF;
            random >>= 4;
            tpLvl = 0x100;
            if (bits == 0) {
                tpLvl = 0xB4;
            }
            HuSprTPLvlSet(grpId, j, tpLvl);
        }
    }
}

void staff_BackProc(void) {
    s16 *stat = HuPrcCurrentGet()->user_data;
    UnkStaff_7 *snow;
    s16 sprIds[3];
    s16 animIds[3];
    s16 unused[3];
    s16 xs[3];
    f32 ys[3];
    s16 starSprIds[2];
    s16 starAnimIds[2];
    s16 starTimers[2];
    StaffPos2s starPos[2];
    f32 snowSpeed;
    f32 snowSpeedVel;
    f32 titleAlpha;
    f32 titleAlphaVel;
    f32 moveVel;
    f32 moveRate;
    s16 snowActive;
    s16 titleAnim;
    s16 titleSpr;
    s16 titleActive;
    s16 moveActive;
    s16 prevStat;
    s16 temp;
    s16 x;
    s32 i;

    snow = staff_BackStarCreate();
    for (i = 0; i < 2; i++) {
        starAnimIds[i] = HuSprAnimDataRead(staff_shootStarSprTbl[i]);
        starSprIds[i] = espEntry(starAnimIds[i], 0, 0);
        espColorSet(starSprIds[i], 255, 255, 255);
        espAttrSet(starSprIds[i], 0x4000);
        espDispOff(starSprIds[i]);
        starTimers[i] = (rand8() & 0x7F) + 120;
    }
    espColorSet(starSprIds[1], 255, 200, 200);
    titleAnim = HuSprAnimDataRead(0x16001A);
    titleSpr = espEntry(titleAnim, 0, 0);
    espAttrSet(titleSpr, 0x4000);
    espPosSet(titleSpr, 160, 120);
    espPriSet(titleSpr, 0xFFF0);
    titleActive = TRUE;
    for (i = 0; i < 3; i++) {
        animIds[i] = HuSprAnimDataRead(staff_backSprTbl[i]);
        sprIds[i] = temp = espEntry(animIds[i], 0, 0);
        espPriSet(temp, staff_backSprPriTbl[i]);
        xs[i] = staff_backSprPosTbl[i].x;
        ys[i] = staff_backSprPosTbl[i].y;
        espPosSet(temp, xs[i], ys[i]);
    }
    moveActive = TRUE;
    moveVel = 0.0f;
    titleAlphaVel = 0.0f;
    snowSpeedVel = 0.0f;
    snowActive = FALSE;
    prevStat = *stat;
    while (prevStat >= 0) {
        if (prevStat != *stat) {
            switch (*stat) {
                case -1:
                    prevStat = -1;
                    continue;
                case 0:
                    break;
                case 1:
                    snowActive = TRUE;
                    snowSpeedVel = 1.0f / 120.0f;
                    snowSpeed = 0.0f;
                    *stat = 0;
                    if (titleActive) {
                        titleAlpha = 256.0f;
                        titleAlphaVel = -64.0f / 120.0f;
                    }
                    if (moveActive) {
                        moveVel = 1.0f / 120.0f;
                        moveRate = 0.0f;
                    }
                    break;
                case 2:
                    for (i = 0; i < 3; i++) {
                        espAttrSet(sprIds[i], 0x4000);
                    }
                    break;
            }
            prevStat = *stat;
        }
        if (snowSpeedVel != 0.0f) {
            snowSpeed += snowSpeedVel;
            if (snowSpeed >= 1.0f) {
                snowSpeed = 1.0f;
                snowSpeedVel = 0.0f;
            } else if (snowSpeed <= 0.0f) {
                snowSpeed = 0.0f;
                snowSpeedVel = 0.0f;
                snowActive = FALSE;
            }
            staff_BackStarSpeedSet(snow, snowSpeed);
        }
        if (snowActive) {
            staff_BackStarMove(snow);
            for (i = 0; i < 2; i++) {
                if (--starTimers[i] == 0) {
                    espDispOn(starSprIds[i]);
                    x = staff_RandMod(160);
                    x += staff_RandMod(160);
                    starPos[i].x = x;
                    starPos[i].y = -128;
                    espPosSet(starSprIds[i], starPos[i].x, -128);
                } else if (starTimers[i] < 0) {
                    starPos[i].y += 8;
                    espPosSet(starSprIds[i], starPos[i].x, starPos[i].y);
                    if (starPos[i].y > 240) {
                        espDispOff(starSprIds[i]);
                        starTimers[i] = (rand8() & 0x7F) + 1;
                    }
                }
            }
        }
        staff_BackStarTwinkle(snow);
        if (titleActive) {
            if (titleAlphaVel != 0.0f) {
                titleAlpha += titleAlphaVel;
                if (titleAlpha <= 0.0f) {
                    titleAlpha = 0.0f;
                    titleAlphaVel = 0.0f;
                }
                espTPLvlSet(titleSpr, titleAlpha);
                if (titleAlpha == 0.0f) {
                    espKill(titleSpr);
                    HuSprAnimKill(titleAnim);
                    titleSpr = -1;
                    titleAnim = -1;
                    titleActive = FALSE;
                }
            }
        }
        if (moveActive) {
            if (moveVel != 0.0f) {
                moveRate += moveVel;
                if (moveRate >= 1.0f) {
                    moveRate = 1.0f;
                }
                temp = 3;
                for (i = 0; i < 3; i++) {
                    if (ys[i] < 304.0f) {
                        ys[i] += moveRate * staff_backSprSpeedTbl[i];
                        espPosSet(sprIds[i], xs[i], ys[i]);
                    } else {
                        temp--;
                        if (sprIds[i] >= 0) {
                            espKill(sprIds[i]);
                            HuSprAnimKill(animIds[i]);
                            animIds[i] = -1;
                            sprIds[i] = -1;
                        }
                    }
                }
                if (temp == 0) {
                    moveActive = FALSE;
                }
            }
        }
        HuPrcVSleep();
    }
    staff_BackStarKill(snow);
    for (i = 0; i < 2; i++) {
        espKill(starSprIds[i]);
        HuSprAnimKill(starAnimIds[i]);
    }
    *stat = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
