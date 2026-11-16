#include "common_duel.h"
#include "ovl_81.h"

void MBDSeqVolUpProc(void);
void MBDSeqVolDownProc(void);

void MBDSeqVolUpProc(void) {
    f32 var_f20 = 96.0f;

    HuAudSeqVolSet(0x60);

    while (var_f20 < 127.0f) {
        HuPrcVSleep();
        var_f20 += 1.9375f;
        if (var_f20 >= 127.0f) {
            var_f20 = 127.0f;
        }
        HuAudSeqVolSet(var_f20);
    }
    omDelPrcObj(NULL);
}

void MBDSeqVolDownProc(void) {
    f32 var_f20 = 127.0f;

    HuAudSeqVolSet(0x7F);

    while (var_f20 > 96.0f) {
        HuPrcVSleep();
        var_f20 -= 1.9375f;
        if (var_f20 <= 96.0f) {
            var_f20 = 96.0f;
        }
        HuAudSeqVolSet(var_f20);
    }
    omDelPrcObj(NULL);
}

void MBDSeqVolDownStart(void) {
    omAddPrcObj(MBDSeqVolDownProc, 0xEFFF, 0, 0);
}

void MBDSeqVolUpStart(void) {
    omAddPrcObj(MBDSeqVolUpProc, 0xEFFF, 0, 0);
}
