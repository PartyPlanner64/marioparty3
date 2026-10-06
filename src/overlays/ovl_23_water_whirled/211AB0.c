#include "common.h"

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801059A0_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80105D64_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80105EA0_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_8010616C_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801061E4_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80106308_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80106680_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_8010698C_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80106A58_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80106DB8_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801071BC_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_8010750C_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80107880_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_8010789C_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801078B8_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801078D4_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801078F0_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80107D18_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80107DD4_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80107F08_water_whirled);

void func_8010860C_water_whirled(Vec *origin, Vec *p, Vec *q, Vec *out) {
    f32 ax = p->x - origin->x;
    f32 ay = p->y - origin->y;
    f32 az = p->z - origin->z;
    f32 bx = q->x - origin->x;
    f32 by = q->y - origin->y;
    f32 bz = q->z - origin->z;

    out->x = ay * bz - az * by;
    out->y = az * bx - ax * bz;
    out->z = ax * by - ay * bx;
    func_800202FC_main(out);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801086A0_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80108898_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801089C0_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80108B98_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80108DF8_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80109340_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80109458_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_8010956C_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_8010960C_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801096BC_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801098AC_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80109E2C_water_whirled);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", D_8010A520_water_whirled);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", D_8010A540_water_whirled);
