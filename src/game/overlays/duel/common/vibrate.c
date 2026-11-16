#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkE78B0 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    Process *proc;
} UnkE78B0; // sizeof 0xC


void MBDPlayerVibrate(s16 playerNo, s16 arg1) {
    if (playerNo == CUR_PLAYER) {
        playerNo = MBDGetCurrentPlayerIndex();
    }

    //??
    if (playerNo != 4) {
        switch (arg1) {
            case 0:
                omVibrate(playerNo, 5, 0, 5);
                break;
            case 1:
                omVibrate(playerNo, 2, 3, 10);
                break;
            case 2:
                omVibrate(playerNo, 10, 0, 10);
                break;
            case 3:
                omVibrate(playerNo, 2, 2, 20);
                break;
            case 4:
                omVibrate(playerNo, 20, 0, 20);
                break;
            case 5:
                omVibrate(playerNo, 30, 0, 30);
                break;
        }
    }
}

void MBDPlayerVibrateProc(void) {
    UnkE78B0 *temp_s0 = (UnkE78B0 *)HuPrcCurrentGet()->user_data;

    while (1) {
        MBDPlayerVibrate(temp_s0->unk_00, temp_s0->unk_02);
        HuPrcSleep(temp_s0->unk_04);
    }
}

void *MBDPlayerVibrateObjCreate(s16 arg0, s16 arg1, s32 arg2) {
    Process *process;
    s16 temp_s1;
    UnkE78B0 *unk;
    static s8 mbdVibrateWaitTbl[] = { 5, 10, 10, 20, 20, 30 };

    temp_s1 = mbdVibrateWaitTbl[arg1] + arg2;
    unk = HuMemMemoryAllocTemp(sizeof(UnkE78B0));

    if (unk != NULL) {
        unk->unk_00 = arg0;
        unk->unk_02 = arg1;
        unk->unk_04 = temp_s1 - 1;
        process = omAddPrcObj(MBDPlayerVibrateProc, 0x1005, 0, 0);
        unk->proc = process;
        process->user_data = unk;
    }

    return unk;
}

void MBDPlayerVibrateObjKill(UnkE78B0 *arg0) {
    if (arg0 != NULL) {
        omDelPrcObj(arg0->proc);
        HuMemMemoryFreeTemp(arg0);
    }
}
