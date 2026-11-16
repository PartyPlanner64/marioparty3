#include "common_board.h"
#include "ovl_80.h"


typedef struct UnkData {
    Process *unk_00;
    u16 *unk_04;
    s16 unk_08;
} UnkData;

static void MBDebugPrintShadow(u16 arg0, u16 arg1, char *arg2, u8 arg3, u8 arg4) {
    fontcolor = arg4;
    print8((arg0 + 1), (arg1 + 1), arg2);
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

static void MBDebugCheatProc(void) {
    s16 temp_v0;
    s16 temp_v0_2;
    UnkData *temp_s0;

    temp_s0 = HuPrcCurrentGet()->user_data;

    for (;; HuPrcVSleep()) {
        if (*HuPadBtnDown == 0) {
            continue;
        } else if (*HuPadBtnDown != temp_s0->unk_04[temp_s0->unk_08]) {
            temp_s0->unk_08 = 0;
            continue;
        } else if (temp_s0->unk_04[++temp_s0->unk_08] == 0) {
            temp_s0->unk_08 = -1;
            break;
        }
    }

    while (1) {
        HuPrcVSleep();
    }
}

void MBDebugCheatCreate(u16 *arg0) {
    Process *process;
    UnkData *temp_v0_2;

    process = omAddPrcObj(MBDebugCheatProc, 0xEFFF, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(process->heap, sizeof(UnkData));
    process->user_data = temp_v0_2;
    temp_v0_2->unk_04 = arg0;
    temp_v0_2->unk_08 = 0;
    temp_v0_2->unk_00 = process;
}

void MBDebugCheatKill(Process* arg0) {
    omDelPrcObj(arg0->next);
}

s32 MBDebugCheatCheck(UnkData* arg0) {
    if (~arg0->unk_08) {
        return 0;
    } else {
        return 1;
    }
}

void MBDebugStub1(void) {
}

// this needs a \0 due to rodata splitting problems
void MBDebugKakusiMasuPrint(s32 arg0, s16 arg1) {

    sprintf(omDBGStrBuf, "KMS: %d", kakusiMasuStar);
    arg0 = (arg0 * 8) & 0xFFF8;
    MBDebugPrintShadow(arg0, (arg1 * 8), omDBGStrBuf, 0xF, 9);
    sprintf(omDBGStrBuf, "KMC: %d\0", kakusiMasuCoin);
    MBDebugPrintShadow(arg0, ((arg1 + 1) * 8), omDBGStrBuf, 0xF, 9);
}

void MBDebugStub2(void) {
}

void MBDebugStub3(void) {
}

void MBDebugStub4(void) {
}

void MBDebugStub5(void) {
}

void MBDebugStub6(void) {
}
