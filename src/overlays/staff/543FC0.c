#include "staff.h"

u32 D_80110580_staff[3] = { 0xFFFFFFC8, 0xFFFFFFFF, 0xC8F07109 }; /* Unreferenced. */
s32 D_8011058C_staff[4] = { 0x16001E, 0x16001F, 0x160020, 0x160021 };
u8 D_8011059C_staff[4] = { 6, 8, 16, 32 };
u16 D_801105A0_staff[4] = { 0xF000, 0xF001, 0xF002, 0xF003 };
f32 D_801105A8_staff[4] = { 6.0f, 4.0f, 2.0f, 1.0f };
s16 D_801105B8_staff[4] = { 2, 6, 6, 0 };
u16 D_801105C0_staff[4] = { 402, 400, 400, 0 };
StaffPos2s D_801105C8_staff[3] = { { 160, 175 }, { 38, 185 }, { 286, 194 } };
s32 D_801105D4_staff[3] = { 0x16001B, 0x16001C, 0x16001D };
s32 D_801105E0_staff[2] = { 0x160022, 0x160023 };

UnkStaff_7 *func_80107740_staff(void) {
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
        count = D_8011059C_staff[i];
        pos = HuMemAllocTag(count * sizeof(Vec2f), TAG_OVERLAY);
        vel = HuMemAllocTag(count * sizeof(f32), TAG_OVERLAY);
        speed = HuMemAllocTag(count * sizeof(f32), TAG_OVERLAY);
        grpId = HuSprGrpCreate(count, 0);
        animId = func_8000B838_main(D_8011058C_staff[i]);
        pri = D_801105A0_staff[i];
        ptr->unk_00 = pos;
        ptr->unk_0C = grpId;
        ptr->unk_0E = animId;
        ptr->unk_04 = vel;
        ptr->unk_08 = speed;
        ptr->count = count;
        baseSpeed = D_801105A8_staff[i];
        for (j = 0; j < count; j++, pos++, vel++, speed++) {
            HuSprTPLvlSet(grpId, j, 0x100);
            HuSprAttrReset(grpId, j, 0xFFFF);
            HuSprAttrSet(grpId, j, 0x5000);
            HuSprScaleSet(grpId, j, 1.0f, 1.0f);
            func_800550F4_main(grpId, j, 0);
            HuSprGrpMemberSet(grpId, j, animId, 0);
            HuSprPriSet(grpId, j, pri);
            random = func_8010601C_staff();
            red = random | 0xC0;
            random >>= 7;
            green = random | 0xC0;
            random >>= 7;
            blue = random | 0xC0;
            HuSprColorSet(grpId, j, red, green, blue);
            random = func_8010601C_staff() & 0x7FFFFFFF;
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

void func_80107A9C_staff(UnkStaff_7 *arg0) {
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

void func_80107B1C_staff(UnkStaff_7 *arg0, f32 arg1) {
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

void func_80107BA0_staff(UnkStaff_7 *arg0) {
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
                random = func_8010601C_staff() & 0x7FFFFFFF;
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

const char D_80111228_staff[] = "";

void func_80107DBC_staff(UnkStaff_7 *arg0) {
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
                random = func_8010601C_staff();
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

void func_80107EB8_staff(void) {
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

    snow = func_80107740_staff();
    for (i = 0; i < 2; i++) {
        starAnimIds[i] = func_8000B838_main(D_801105E0_staff[i]);
        starSprIds[i] = espEntry(starAnimIds[i], 0, 0);
        espColorSet(starSprIds[i], 255, 255, 255);
        espAttrSet(starSprIds[i], 0x4000);
        espDispOff(starSprIds[i]);
        starTimers[i] = (rand8() & 0x7F) + 120;
    }
    espColorSet(starSprIds[1], 255, 200, 200);
    titleAnim = func_8000B838_main(0x16001A);
    titleSpr = espEntry(titleAnim, 0, 0);
    espAttrSet(titleSpr, 0x4000);
    espPosSet(titleSpr, 160, 120);
    espPriSet(titleSpr, 0xFFF0);
    titleActive = TRUE;
    for (i = 0; i < 3; i++) {
        animIds[i] = func_8000B838_main(D_801105D4_staff[i]);
        sprIds[i] = temp = espEntry(animIds[i], 0, 0);
        espPriSet(temp, D_801105C0_staff[i]);
        xs[i] = D_801105C8_staff[i].x;
        ys[i] = D_801105C8_staff[i].y;
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
            func_80107B1C_staff(snow, snowSpeed);
        }
        if (snowActive) {
            func_80107BA0_staff(snow);
            for (i = 0; i < 2; i++) {
                if (--starTimers[i] == 0) {
                    espDispOn(starSprIds[i]);
                    x = func_80106044_staff(160);
                    x += func_80106044_staff(160);
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
        func_80107DBC_staff(snow);
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
                        ys[i] += moveRate * D_801105B8_staff[i];
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
    func_80107A9C_staff(snow);
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
