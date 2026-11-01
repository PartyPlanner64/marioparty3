#include "common.h"
#include "game/printfunc.h"

u16 D_80106DB0_mchar2 = 0;
u8 D_80106DB2_mchar2 = 1;
s16 D_80106DB4_mchar2[] = { 2, 3, 7, 4, 5, 6, 8, 9 };
u16 D_80106DC4_mchar2[] = { 0, 1, 2, 3, 0x802F, 0x8036, 0xFFFF };
char *D_80106DD4_mchar2[] = {
    "C000_000", "C000_001", "C000_003", "C000_004", "C000_400", "C000_407"
};
s16 D_80106DEC_mchar2 = 0;
s16 D_80106DEE_mchar2 = 0;
s16 D_80106DF0_mchar2 = 1;
s16 D_80106DF2_mchar2 = 0;
u8 D_80106DF4_mchar2 = 0;
u8 D_80106DF5_mchar2 = 0;
s32 D_80106DF8_mchar2[] = { 0x800A2, 0x800A0, 0x90003, 0x90000 };

static u8 D_80106EC0_mchar2;
static s32 D_80106EC8_mchar2[8][2];
static s32 D_80106F08_mchar2[8][2];
static char D_80106F48_mchar2[0x100];
static Vec D_80107048_mchar2;

extern s32 fontcolor;
extern u16 omdispinfo;
extern s16 D_800A1786_main;

void func_80106630_mchar2(s32 arg0);
void func_80105B7C_mchar2(omObjData *arg0);
void func_80105C90_mchar2(omObjData *arg0);
void func_80106428_mchar2(s32 arg0);
void func_801067C4_mchar2(omObjData *arg0);
void func_80106CA8_mchar2(void);
void func_80106D24_mchar2(omObjData *arg0);

void func_80106D80_mchar2(omObjData *arg0);

void func_801059A0_mchar2(void) {
    s16 i;

    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 0);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    if (omdispinfo != 0) {
        omdispinfo = 0;
        func_8004DEC8_main(D_800A1786_main);
        D_800A1786_main = -1;
    }
    omAddObj(0x2710, 0, 0, -1, func_80106D24_mchar2);
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, -100.0f, 100.0f, 100.0f);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    func_80106CA8_mchar2();
    omAddObj(0x7D0, 10, 10, -1, func_80105B7C_mchar2);
    omAddObj(0x7D0, 0, 0, -1, func_801067C4_mchar2);
    WipeCreateIn(WIPE_TYPE_NORMAL, 16);
    D_800CD280_main = 1;
    Hu3DBGColorSet(0xC0, 0xE0, 0xFF);
    for (i = 0; D_80106DC4_mchar2[i] != 0xFFFF; i++) {}
    D_80106EC0_mchar2 = i;
    func_80045C2C_main();
}

void func_80105B7C_mchar2(omObjData *arg0) {
    s16 i;

    arg0->model[0] = -1;
    for (i = 0; i < 8; i++) {
        D_80106EC8_mchar2[i][0] = D_80106EC8_mchar2[i][1] =
            D_80106F08_mchar2[i][0] = D_80106F08_mchar2[i][1] = -1;
    }
    D_80106DF2_mchar2 = 0;
    func_80106428_mchar2(0);
    func_8001C258_main((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C814_main((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 2, 2);
    arg0->func = func_80105C90_mchar2;
}

void func_80105C90_mchar2(omObjData *arg0) {
    HmfModel *model;

    if (D_80106DF5_mchar2 != 0) {
        D_80106DF5_mchar2--;
        if (D_80106DF5_mchar2 == 0) {
            func_80106428_mchar2(D_80106DF2_mchar2);
            func_8001C258_main((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            func_8001C814_main((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 2, 2);
        }
    }
    if ((u16)D_800D0590_main[0] & A_BUTTON) {
        D_80106DEE_mchar2++;
        if (D_80106DC4_mchar2[D_80106DEE_mchar2] == 0xFFFF) {
            D_80106DEE_mchar2 = 0;
        }
        func_80106630_mchar2((s16)D_80106DC4_mchar2[D_80106DEE_mchar2]);
    }
    if (D_800D0590_main[0] & B_BUTTON) {
        D_80106DEE_mchar2--;
        if (D_80106DEE_mchar2 < 0) {
            D_80106DEE_mchar2 = D_80106EC0_mchar2 - 1;
        }
        func_80106630_mchar2((s16)D_80106DC4_mchar2[D_80106DEE_mchar2]);
    }
    if (D_800D5558_main[0] & START_BUTTON) {
        D_80106DF4_mchar2++;
    }
    if (D_800D5558_main[0] & L_CBUTTONS) {
        func_8001C258_main((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        D_80106DEC_mchar2++;
        if (D_80106DEC_mchar2 >= 2) {
            D_80106DEC_mchar2 = 0;
        }
        func_8001C258_main((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionSet((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], (s16)D_80106F08_mchar2[D_80106DEC_mchar2][0]);
        func_8001C814_main((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 2, 2);
        func_80045ED0_main((D_80106DB4_mchar2[D_80106DEC_mchar2] << 16) | D_80106DEE_mchar2);
    }
    if (D_800D5558_main[0] & R_CBUTTONS) {
        func_8001C258_main((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        D_80106DEC_mchar2--;
        if (D_80106DEC_mchar2 < 0) {
            D_80106DEC_mchar2 = 1;
        }
        func_8001C258_main((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionSet((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], (s16)D_80106F08_mchar2[D_80106DEC_mchar2][0]);
        func_8001C814_main((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2], 2, 2);
        func_80045ED0_main((D_80106DB4_mchar2[D_80106DEC_mchar2] << 16) | D_80106DEE_mchar2);
    }
    if ((u16)D_800D0590_main[1] & (A_BUTTON | B_BUTTON)) {
        model = &HmfModelData[D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2]];
        if ((u16)D_800D0590_main[1] & B_BUTTON) {
            model->motAttr |= 4;
        }
        model->motAttr &= 0xFE;
        model->motTime = func_8002FC7C_main(&D_800CCF58_main[model->motId], model->motAttr, model->motTime, model->unk48, model->motSpeed + model->motSpeed);
        if (model->motIdShift != 0xFF) {
            model->motShiftTime = func_8002FC7C_main(&D_800CCF58_main[model->motIdShift], model->motShiftAttr, model->motShiftTime, model->unk54, model->motShiftSpeed + model->motShiftSpeed);
        }
        model->motAttr = (model->motAttr & 0xFB) | 1;
    }
    if ((D_800CDA7C_main[0] & (L_TRIG | R_TRIG)) == 0x30) {
        D_80106DB0_mchar2 = 1;
    }
    if (D_800D5558_main[1] & START_BUTTON) {
        D_80106DB2_mchar2 = !D_80106DB2_mchar2;
    }
    if (D_80106DB2_mchar2 != 0) {
        model = &HmfModelData[D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2]];
        fontcolor = FONT_COLOR_BLUE;
        sprintf(D_80106F48_mchar2, "MOTIONNO.%3d <%s>", D_80106DEE_mchar2, D_80106DD4_mchar2[D_80106DEE_mchar2]);
        print8(24, 182, D_80106F48_mchar2);
        sprintf(D_80106F48_mchar2, "CENTER:%3.3f,%3.3f,%3.3f", Center.x, Center.y, Center.z);
        print8(24, 190, D_80106F48_mchar2);
        sprintf(D_80106F48_mchar2, "ROTATE:%3.3f,%3.3f,%3.3f", CRot.x, CRot.y, CRot.z);
        print8(24, 198, D_80106F48_mchar2);
        sprintf(D_80106F48_mchar2, "ZOOM:  %3.3f", CZoom);
        print8(24, 206, D_80106F48_mchar2);
        sprintf(D_80106F48_mchar2, "M_TIME:%d", (u16)model->motTime);
        print8(24, 214, D_80106F48_mchar2);
    }
}

void func_80106428_mchar2(s32 arg0) {
    s16 i;
    void *data;
    s16 flags;
    s32 *files0;
    s32 *files1;

    i = 0;
    files0 = D_80106DF8_mchar2;
    flags = 0x2AC;
    for (; i < 2; i++) {
        D_80106EC8_mchar2[i][0] = func_8000B108_main(files0[i * 2], flags);
        files1 = &D_80106DF8_mchar2[1];
        func_80017790_main((s16)D_80106EC8_mchar2[i][0], 0, i + 6, func_80017BB8_main(i + 6, 0xA3));
        func_8001C514_main((s16)D_80106EC8_mchar2[i][0]);
        D_80106EC8_mchar2[i][1] = func_8000B108_main(files1[i * 2], flags);
        func_80017790_main((s16)D_80106EC8_mchar2[i][1], 1, i + 6, func_80017BB8_main(i + 6, 0xA4));
        func_8001C514_main((s16)D_80106EC8_mchar2[i][1]);
        if (D_80106F08_mchar2[i][0] != -1) {
            func_8002D4B8_main((s16)D_80106F08_mchar2[i][0]);
        }
        if (D_80106F08_mchar2[i][1] != -1) {
            func_8002D4B8_main((s16)D_80106F08_mchar2[i][1]);
        }
        data = DataReadTemp(func_80017BB8_main(i + 6, 0));
        D_80106F08_mchar2[i][0] = func_8001F1FC_main(data, 0);
        DataCloseTemp(data);
        D_80106F08_mchar2[i][1] = -1;
        Hu3DMotionSet((s16)D_80106EC8_mchar2[i][0], (s16)D_80106F08_mchar2[i][0]);
    }
}

void func_80106630_mchar2(s32 arg0) {
    s16 i;
    void *data;

    for (i = 0; i < 2; i++) {
        if (D_80106F08_mchar2[i][1] != -1) {
            func_8002D4B8_main((s16)D_80106F08_mchar2[i][1]);
        }
        D_80106F08_mchar2[i][1] = D_80106F08_mchar2[i][0];
        data = DataReadTemp(func_80017BB8_main(i + 6, arg0 & 0x7FFF));
        D_80106F08_mchar2[i][0] = func_8001F1FC_main(data, 0);
        DataCloseTemp(data);
    }
    if (arg0 & 0x8000) {
        Hu3DMotionShiftSet((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2],
                           (s16)D_80106F08_mchar2[D_80106DEC_mchar2][0], 0, 10, 0);
    } else {
        Hu3DMotionShiftSet((s16)D_80106EC8_mchar2[D_80106DEC_mchar2][D_80106DF0_mchar2],
                           (s16)D_80106F08_mchar2[D_80106DEC_mchar2][0], 0, 10, 2);
    }
}

void func_801067C4_mchar2(omObjData *arg0) {
    f32 dz;
    f32 zoom;
    f32 speed;

    f32 x, y;
    f32 length;
    s8 stick;

    if (D_800CDA7C_main[0] & START_BUTTON) {
        func_80106CA8_mchar2();
    }
    if (D_800CDA7C_main[0] & L_TRIG) {
        if (D_800CDA7C_main[0] & Z_TRIG) {
            zoom = CZoom;
            zoom += 30.0f;
            CZoom = zoom;
        } else {
            zoom = CZoom;
            zoom += 10.0f;
            CZoom = zoom;
        }
    }
    if ((D_800CDA7C_main[0] & R_TRIG) && (CZoom - 10.0f != 0.0f)) {
        if (D_800CDA7C_main[0] & Z_TRIG) {
            CZoom -= 30.0f;
        } else {
            zoom = CZoom;
            CZoom = zoom - 10.0f;
        }
    }
    x = D_80107048_mchar2.x;
    y = D_80107048_mchar2.y;
    if (D_800CDA7C_main[0] & Z_TRIG) {
        speed = 5.0f;
    } else {
        speed = 2.0f;
    }
    y += (-D_800CBB6E_main[0] / 30) * speed;
    if (y >= 360.0f) {
        y -= 360.0f;
    } else if (y < 0.0f) {
        y += 360.0f;
    }
    D_80107048_mchar2.y = y;
    stick = D_800D20A1_main[0];
    stick /= 30;
    x += stick * speed;
    if (x >= 360.0f) {
        x -= 360.0f;
    } else if (x < 0.0f) {
        x += 360.0f;
    }
    D_80107048_mchar2.x = x;
    CRot.x = (s16)x;
    CRot.y = (s16)D_80107048_mchar2.y;
    if (D_800CDA7C_main[0] & Z_TRIG) {
        speed = 10.0f;
    } else {
        speed = 2.0f;
    }
    if (D_800CDA7C_main[0] & U_JPAD) {
        Center.x += sindf(y) * sindf(x) * -speed;
        Center.y += cosdf(x) * -speed;
        Center.z += cosdf(y) * sindf(x) * -speed;
    } else if (D_800CDA7C_main[0] & D_JPAD) {
        Center.x += sindf(y) * sindf(x) * speed;
        Center.y += cosdf(x) * speed;
        Center.z += cosdf(y) * sindf(x) * speed;
    } else if (D_800CDA7C_main[0] & L_JPAD) {
        x = gCameraList->pos.z - Center.z;
        dz = -(gCameraList->pos.x - Center.x);
        length = 1.0f / HuSqrtf(x * x + dz * dz);
        Center.x += x * length * speed;
        Center.y += 0.0f;
        Center.z += dz * length * speed;
    } else if (D_800CDA7C_main[0] & R_JPAD) {
        x = -(gCameraList->pos.z - Center.z);
        dz = gCameraList->pos.x - Center.x;
        length = 1.0f / HuSqrtf(x * x + dz * dz);
        Center.x += x * length * speed;
        Center.y += 0.0f;
        Center.z += dz * length * speed;
    }
}

void func_80106CA8_mchar2(void) {
    D_80107048_mchar2.x = D_80107048_mchar2.y = D_80107048_mchar2.z = 0.0f;
    CRot.x = CRot.y = CRot.z = 0.0f;
    CZoom = 400.0f;
    Center.x = Center.z = 0.0f;
    Center.y = 64.0f;
    gCameraList->fov = 45.0f;
}

void func_80106D24_mchar2(omObjData *arg0) {
    if ((D_80106DB0_mchar2 != 0) || (D_800D530C_main != 0)) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 8);
        arg0->func = func_80106D80_mchar2;
        HuAudSeqFadeOut(0x3C);
    }
}

void func_80106D80_mchar2(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}
