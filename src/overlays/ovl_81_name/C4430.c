#include "common_duel.h"
#include "ovl_81.h"

void func_800DC660_name_81(void);
void func_800DC700_name_81(void);

void func_800DC660_name_81(void) {
    f32 var_f20 = 96.0f;

    func_8004A9DC_main(0x60);

    while (var_f20 < 127.0f) {
        HuPrcVSleep();
        var_f20 += 1.9375f;
        if (var_f20 >= 127.0f) {
            var_f20 = 127.0f;
        }
        func_8004A9DC_main(var_f20);
    }
    omDelPrcObj(NULL);
}

void func_800DC700_name_81(void) {
    f32 var_f20 = 127.0f;

    func_8004A9DC_main(0x7F);

    while (var_f20 > 96.0f) {
        HuPrcVSleep();
        var_f20 -= 1.9375f;
        if (var_f20 <= 96.0f) {
            var_f20 = 96.0f;
        }
        func_8004A9DC_main(var_f20);
    }
    omDelPrcObj(NULL);
}

void func_800DC7A0_name_81(void) {
    omAddPrcObj(func_800DC700_name_81, 0xEFFF, 0, 0);
}

void func_800DC7CC_name_81(void) {
    omAddPrcObj(func_800DC660_name_81, 0xEFFF, 0, 0);
}
