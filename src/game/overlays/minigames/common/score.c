#include "common.h"
#include "game/overlays/minigame.h"

extern s16 mgGaugeNum;
extern MgGauge *mgGaugeTbl;
extern s16 mgGaugeFrameAnim;
extern s16 mgGaugeBarAnim;
extern u16 mgGaugeLen;

void MgGaugeInit(s16 count, u16 length) {
    s32 i;
    s32 j;

    mgGaugeNum = count;
    mgGaugeLen = length;
    mgGaugeTbl = HuMemAllocTag(count * sizeof(MgGauge), 0x7918);
    mgGaugeFrameAnim = HuSprAnimDataRead(0x210018);
    mgGaugeBarAnim = HuSprAnimDataRead(0x210019);
    for (i = 0; i < count; i++) {
        mgGaugeTbl[i].unk_00 = HuMemAllocTag(length * sizeof(s16), 0x7918);
        mgGaugeTbl[i].unk_04 = HuMemAllocTag(length * sizeof(s16), 0x7918);
        mgGaugeTbl[i].unk_16 = 0;
        mgGaugeTbl[i].unk_14 = 0;
        for (j = 0; j < length; j++) {
            mgGaugeTbl[i].unk_00[j] = espEntry(mgGaugeFrameAnim, 0, 0);
            mgGaugeTbl[i].unk_04[j] = espEntry(mgGaugeBarAnim, 0, 0);
        }
        MgGaugePosSet(i, 24, 16, 0);
        MgGaugeRangeSet(i, 0.0f, 100.0f);
        MgGaugeValueSet(i, 0.0f);
        MgGaugePriSet(i, 0x8000);
        MgGaugeDispOff(i);
    }
}

void MgGaugeClose(void) {
    s32 i;
    s32 j;

    for (i = 0; i < mgGaugeNum; i++) {
        for (j = 0; j < mgGaugeLen; j++) {
            espKill(mgGaugeTbl[i].unk_00[j]);
            espKill(mgGaugeTbl[i].unk_04[j]);
        }
        HuMemFree(mgGaugeTbl[i].unk_00);
        HuMemFree(mgGaugeTbl[i].unk_04);
    }
    HuSprAnimKill(mgGaugeFrameAnim);
    HuSprAnimKill(mgGaugeBarAnim);
}

void MgGaugePosSet(s16 arg0, s16 x, s16 y, s16 arg3) {
    MgGauge *entry = &mgGaugeTbl[arg0];
    s32 i;

    switch (arg3) {
        case 0:
            for (i = 0; i < mgGaugeLen; i++) {
                espPosSet(entry->unk_00[i], x + 5 + i * 10, y + 5);
                espPosSet(entry->unk_04[i], x + 5 + i * 10, y + 5);
            }
            break;
        case 1:
            for (i = mgGaugeLen - 1; i >= 0; i--) {
                espPosSet(entry->unk_00[i], x + 5 + (mgGaugeLen - 1 - i) * 10, y + 5);
                espPosSet(entry->unk_04[i], x + 5 + (mgGaugeLen - 1 - i) * 10, y + 5);
            }
            break;
    }
}

void MgGaugeRangeSet(s16 arg0, f32 arg1, f32 arg2) {
    mgGaugeTbl[arg0].unk_08 = arg1;
    mgGaugeTbl[arg0].unk_0C = arg2;
}

void MgGaugeRateSet(s16 arg0, f32 arg1) {
    mgGaugeTbl[arg0].unk_10 = arg1;
    if (!(mgGaugeTbl[arg0].unk_14 & 1)) {
        MgGaugeDispOn(arg0);
    }
}

void MgGaugeValueSet(s16 arg0, f32 arg1) {
    f32 range = mgGaugeTbl[arg0].unk_0C - mgGaugeTbl[arg0].unk_08;

    mgGaugeTbl[arg0].unk_10 = (arg1 - mgGaugeTbl[arg0].unk_08) / range;
    if (!(mgGaugeTbl[arg0].unk_14 & 1)) {
        MgGaugeDispOn(arg0);
    }
}

void MgGaugePriSet(s16 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < mgGaugeLen; i++) {
        espPriSet(mgGaugeTbl[arg0].unk_00[i], (u16)(arg1 + 1));
        espPriSet(mgGaugeTbl[arg0].unk_04[i], (u16)arg1);
    }
}

void MgGaugeDispOn(s16 arg0) {
    MgGauge *entry = &mgGaugeTbl[arg0];
    f32 count;
    f32 step;
    f32 frac;
    s32 filled;
    s32 i;

    entry->unk_14 &= ~1;
    if (entry->unk_14 & 2) {
        return;
    }
    count = mgGaugeLen;
    filled = count * entry->unk_10;
    step = 1.0f / count;
    frac = (entry->unk_10 - step * filled) / step;
    for (i = 0; i < mgGaugeLen; i++) {
        espDispOn(entry->unk_00[i]);
        if (i < filled) {
            espDispOn(entry->unk_04[i]);
            espTPLvlSet(entry->unk_04[i], 256);
        } else if (i == filled) {
            espDispOn(entry->unk_04[i]);
            espTPLvlSet(entry->unk_04[i], frac * 256.0f);
        } else {
            espDispOff(entry->unk_04[i]);
        }
    }
}

void MgGaugeDispOff(s16 arg0) {
    s32 i;

    mgGaugeTbl[arg0].unk_14 |= 1;
    for (i = 0; i < mgGaugeLen; i++) {
        espDispOff(mgGaugeTbl[arg0].unk_00[i]);
        espDispOff(mgGaugeTbl[arg0].unk_04[i]);
    }
}

void MgGaugeUpdate(void) {
    MgGauge *entry;
    s32 i;
    s32 j;

    for (i = 0; i < mgGaugeNum; i++) {
        entry = &mgGaugeTbl[i];
        if (entry->unk_14 & 1) {
            continue;
        }
        if (entry->unk_10 >= 1.0f) {
            if (!(entry->unk_14 & 2)) {
                entry->unk_14 |= 2;
                entry->unk_16 = 0;
            }
            if (entry->unk_16 < 2) {
                for (j = 0; j < mgGaugeLen; j++) {
                    espDispOff(entry->unk_04[j]);
                }
            } else {
                for (j = 0; j < mgGaugeLen; j++) {
                    espDispOn(entry->unk_04[j]);
                }
            }
            entry->unk_16 = (entry->unk_16 + 1) & 3;
        } else if (entry->unk_14 & 2) {
            entry->unk_14 &= ~2;
            MgGaugeDispOn(i);
        }
    }
}
