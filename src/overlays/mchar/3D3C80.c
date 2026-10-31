#include "common.h"
#include "game/printfunc.h"
#include "game/pause.h"

u16 D_80106E80_mchar = 0;
u8 D_80106E82_mchar = 1;
s16 D_80106E84_mchar[] = { 2, 3, 7, 4, 5, 6, 8, 9 };
char *D_80106E94_mchar[] = {
    "C000_000",
    "C000_001",
    "C000_003",
    "C000_004",
    "C000_005",
    "C000_006",
    "C000_009",
    "C000_010",
    "C000_011",
    "C000_012",
    "C000_013",
    "C000_020",
    "C000_022",
    "C000_023",
    "C000_024",
    "C000_028",
    "C000_029",
    "C000_030",
    "C000_036",
    "C000_039",
    "C000_047",
    "C000_048",
    "C000_049",
    "C000_050",
    "C000_068",
    "C000_072",
    "C000_078",
    "C000_101",
    "C000_113",
    "C000_114",
    "C000_115",
    "C000_116",
    "C000_117",
    "C000_118",
    "C000_121",
    "C000_122",
    "C000_123",
    "C000_172",
    "C000_178",
    "C000_227",
    "C000_228",
    "C000_243",
    "C000_277",
    "C000_288",
    "C000_308",
    "C000_322",
    "C000_323",
    "C000_400",
    "C000_401",
    "C000_402",
    "C000_403",
    "C000_404",
    "C000_405",
    "C000_406",
    "C000_407",
    "C000_408",
    "C000_409",
    "C000_410",
    "C000_411",
    "C000_413",
    "C000_414",
    "C000_415",
    "C000_416",
    "C000_417",
    "C000_418",
    "C000_419",
    "C000_420",
    "C000_421",
    "C000_422",
    "C000_423",
    "C000_424",
    "C000_426",
    "C000_427",
    "C000_428",
    "C000_429",
    "C000_430",
    "C000_431",
    "C000_432",
    "C000_437",
    "C000_438",
    "C000_439",
    "C000_440",
    "C000_441",
    "C000_442",
    "C000_445",
    "C000_446",
    "C000_447",
    "C000_448",
    "C000_449",
    "C000_450",
    "C000_451",
    "C000_453",
    "C000_455",
    "C000_456",
    "C000_458",
    "C000_459",
    "C000_460",
    "C000_461",
    "C000_462",
    "C000_463",
    "C000_464",
    "C000_465",
    "C000_466",
    "C000_467",
    "C000_468",
    "C000_469",
    "C000_470",
    "C000_471",
    "C000_472",
    "C000_473",
    "C000_474",
    "C000_476",
    "C000_477",
    "C000_478",
    "C000_479",
    "C000_480",
    "C000_481",
    "C000_482",
    "C000_483",
    "C000_484",
    "C000_485",
    "C000_486",
    "C000_487",
    "C000_488",
    "C000_489",
    "C000_490",
    "C000_491",
    "C000_492",
    "C000_493",
    "C000_494",
    "C000_495",
    "C000_496",
    "C000_497",
    "C000_498",
    "C000_499",
    "C000_500",
    "C000_501",
    "C000_502",
    "C000_504",
    "C000_505",
    "C000_506",
    "C000_507",
    "C000_508",
    "C000_509",
    "C000_510",
    "C000_511",
    "C000_512",
    "C000_513",
    "C000_514",
    "C000_515",
    "C000_516",
    "C000_517",
    "C000_518",
    "C000_519",
    "C000_520",
    "C000_521",
    "C000_522",
    "C000_523",
    "C000_524",
    "C000_100",
};
s16 D_80107114_mchar = 0;
s16 D_80107116_mchar = 0;
s16 D_80107118_mchar = 0;
s16 D_8010711A_mchar = 0;
u8 D_8010711C_mchar = 0;
u8 D_8010711D_mchar = 0;
s32 D_80107120_mchar[] = {
    0x200A2, 0x200A1, 0x300A2, 0x300A1, 0x700A2, 0x700A1, 0x400A2, 0x400A1,
    0x500A2, 0x500A1, 0x600A2, 0x600A1, 0x800A2, 0x800A1, 0x90003, 0x90001
};

static char D_80107950_mchar[0x100];
static Vec D_80107A50_mchar;
static s32 D_80107A60_mchar[8][2];
static s32 D_80107AA0_mchar[8][2];

extern s32 fontcolor;
extern u16 omdispinfo;
extern s16 D_800A1786_main;

f32 func_8002FC7C_main(D_800CCF58_main_Struct *, u16, f32, f32, f32);
void func_8004DEC8_main(s16);
void func_80045C2C_main(void);
void func_80106DF8_mchar(omObjData *arg0);
void func_80106D7C_mchar(void);
void func_80105B38_mchar(omObjData *arg0);
void func_80106898_mchar(omObjData *arg0);
void func_80106764_mchar(s16 arg0);
void func_80106E54_mchar(omObjData *arg0);
void func_8010654C_mchar(s16 arg0);
void func_80105C4C_mchar(omObjData *arg0);

void func_801059A0_mchar(void) {
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
    omAddObj(0x2710, 0, 0, -1, func_80106DF8_mchar);
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, -100.0f, 100.0f, 100.0f);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    func_80106D7C_mchar();
    omAddObj(0x7D0, 10, 10, -1, func_80105B38_mchar);
    omAddObj(0x7D0, 0, 0, -1, func_80106898_mchar);
    WipeCreateIn(WIPE_TYPE_NORMAL, 16);
    D_800CD280_main = 1;
    Hu3DBGColorSet(0xC0, 0xE0, 0xFF);
    func_80045C2C_main();
}

void func_80105B38_mchar(omObjData *arg0) {
    s16 i;

    arg0->model[0] = -1;
    for (i = 0; i < 8; i++) {
        D_80107A60_mchar[i][0] = D_80107A60_mchar[i][1] =
            D_80107AA0_mchar[i][0] = D_80107AA0_mchar[i][1] = -1;
    }
    D_8010711A_mchar = 0;
    func_8010654C_mchar(0);
    func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C814_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
    arg0->func = func_80105C4C_mchar;
}

void func_80105C4C_mchar(omObjData *arg0) {
    HmfModel *model;
    HmfModel *newModel;

    if (D_8010711D_mchar != 0) {
        D_8010711D_mchar--;
        if (D_8010711D_mchar == 0) {
            func_8010654C_mchar(D_8010711A_mchar);
            func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            func_8001C814_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
        }
    }
    if ((u16)D_800D0590_main[0] & A_BUTTON) {
        D_80107116_mchar++;
        if (D_80107116_mchar >= 160) {
            D_80107116_mchar = 0;
        }
        func_80106764_mchar(D_80107116_mchar);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if (D_800D0590_main[0] & B_BUTTON) {
        D_80107116_mchar--;
        if (D_80107116_mchar < 0) {
            D_80107116_mchar = 159;
        }
        func_80106764_mchar(D_80107116_mchar);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if (D_800D5558_main[0] & START_BUTTON) {
        D_8010711C_mchar++;
    }
    if (D_800D5558_main[0] & D_CBUTTONS) {
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        model = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        D_80107118_mchar++;
        if (D_80107118_mchar >= 2) {
            D_80107118_mchar = 0;
        }
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        newModel = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        newModel->motId = model->motId;
        newModel->motTime = model->motTime;
        newModel->motAttr = model->motAttr;
        newModel->motShiftTime = model->motShiftTime;
        newModel->motShiftAttr = model->motShiftAttr;
        newModel->motIdShift = model->motIdShift;
    }
    if (D_800D5558_main[0] & L_CBUTTONS) {
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        D_80107114_mchar++;
        if (D_80107114_mchar >= 8) {
            D_80107114_mchar = 0;
        }
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionSet((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], (s16)D_80107AA0_mchar[D_80107114_mchar][0]);
        func_8001C814_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if (D_800D5558_main[0] & R_CBUTTONS) {
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        D_80107114_mchar--;
        if (D_80107114_mchar < 0) {
            D_80107114_mchar = 7;
        }
        func_8001C258_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionSet((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], (s16)D_80107AA0_mchar[D_80107114_mchar][0]);
        func_8001C814_main((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar], 2, 2);
        func_80045ED0_main((D_80106E84_mchar[D_80107114_mchar] << 16) | D_80107116_mchar);
    }
    if ((u16)D_800D0590_main[1] & (A_BUTTON | B_BUTTON)) {
        model = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        if ((u16)D_800D0590_main[1] & B_BUTTON) {
            model->motAttr |= 4;
        }
        model->motAttr &= 0xFE;
        model->motTime = func_8002FC7C_main(&D_800CCF58_main[model->motId], model->motAttr, model->motTime, model->unk48, model->motSpeed + model->motSpeed);
        model->motShiftTime = func_8002FC7C_main(&D_800CCF58_main[model->motIdShift], model->motShiftAttr, model->motShiftTime, model->unk54, model->motShiftSpeed + model->motShiftSpeed);
        model->motAttr = (model->motAttr & 0xFB) | 1;
    }
    if ((D_800CDA7C_main[0] & (L_TRIG | R_TRIG)) == 0x30) {
        D_80106E80_mchar = 1;
    }
    if (D_800D5558_main[1] & START_BUTTON) {
        D_80106E82_mchar = !D_80106E82_mchar;
    }
    if (D_80106E82_mchar != 0) {
        model = &HmfModelData[D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar]];
        fontcolor = FONT_COLOR_BLUE;
        sprintf(D_80107950_mchar, "MOTIONNO.%3d <%s>", D_80107116_mchar, D_80106E94_mchar[D_80107116_mchar]);
        print8(24, 182, D_80107950_mchar);
        sprintf(D_80107950_mchar, "CENTER:%3.3f,%3.3f,%3.3f", Center.x, Center.y, Center.z);
        print8(24, 190, D_80107950_mchar);
        sprintf(D_80107950_mchar, "ROTATE:%3.3f,%3.3f,%3.3f", CRot.x, CRot.y, CRot.z);
        print8(24, 198, D_80107950_mchar);
        sprintf(D_80107950_mchar, "ZOOM:  %3.3f", CZoom);
        print8(24, 206, D_80107950_mchar);
        sprintf(D_80107950_mchar, "M_TIME:%d", (u16)model->motTime);
        print8(24, 214, D_80107950_mchar);
    }
}

void func_8010654C_mchar(s16 arg0) {
    s16 i;
    void *data;
    s16 flags;
    s32 *files0;
    s32 *files1;
    s32 offset;

    i = 0;
    offset = arg0;
    files0 = D_80107120_mchar;
    flags = 0x2AC;
    for (; i < 8; i++) {
        D_80107A60_mchar[i][0] = func_8000B108_main(files0[(i + offset) * 2], flags);
        files1 = &D_80107120_mchar[1];
        func_80017790_main((s16)D_80107A60_mchar[i][0], 0, i, func_80017BB8_main(i, 0xA3));
        func_8001C514_main((s16)D_80107A60_mchar[i][0]);
        D_80107A60_mchar[i][1] = func_8000B108_main(files1[(i + offset) * 2], flags);
        func_80017790_main((s16)D_80107A60_mchar[i][1], 1, i, func_80017BB8_main(i, 0xA4));
        func_8001C514_main((s16)D_80107A60_mchar[i][1]);
        if (D_80107AA0_mchar[i][0] != -1) {
            func_8002D4B8_main((s16)D_80107AA0_mchar[i][0]);
        }
        if (D_80107AA0_mchar[i][1] != -1) {
            func_8002D4B8_main((s16)D_80107AA0_mchar[i][1]);
        }
        data = DataReadTemp(func_80017BB8_main(i, 0));
        D_80107AA0_mchar[i][0] = func_8001F1FC_main(data, 0);
        DataCloseTemp(data);
        D_80107AA0_mchar[i][1] = -1;
        Hu3DMotionSet((s16)D_80107A60_mchar[i][0], (s16)D_80107AA0_mchar[i][0]);
    }
}

void func_80106764_mchar(s16 arg0) {
    s16 i;
    void *data;

    for (i = 0; i < 8; i++) {
        if (D_80107AA0_mchar[i][1] != -1) {
            func_8002D4B8_main((s16)D_80107AA0_mchar[i][1]);
        }
        D_80107AA0_mchar[i][1] = D_80107AA0_mchar[i][0];
        data = DataReadTemp(func_80017BB8_main(i, arg0));
        D_80107AA0_mchar[i][0] = func_8001F1FC_main(data, 0);
        DataCloseTemp(data);
    }
    Hu3DMotionShiftSet((s16)D_80107A60_mchar[D_80107114_mchar][D_80107118_mchar],
                       (s16)D_80107AA0_mchar[D_80107114_mchar][0], 0, 10, 2);
}

void func_80106898_mchar(omObjData *arg0) {
    f32 dz;
    f32 zoom;
    f32 speed;

    f32 x, y;
    f32 length;
    s8 stick;

    if (D_800CDA7C_main[0] & START_BUTTON) {
        func_80106D7C_mchar();
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
    x = D_80107A50_mchar.x;
    y = D_80107A50_mchar.y;
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
    D_80107A50_mchar.y = y;
    stick = D_800D20A1_main[0];
    stick /= 30;
    x += stick * speed;
    if (x >= 360.0f) {
        x -= 360.0f;
    } else if (x < 0.0f) {
        x += 360.0f;
    }
    D_80107A50_mchar.x = x;
    CRot.x = (s16)x;
    CRot.y = (s16)D_80107A50_mchar.y;
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

void func_80106D7C_mchar(void) {
    D_80107A50_mchar.x = D_80107A50_mchar.y = D_80107A50_mchar.z = 0.0f;
    CRot.x = CRot.y = CRot.z = 0.0f;
    CZoom = 400.0f;
    Center.x = Center.z = 0.0f;
    Center.y = 64.0f;
    gCameraList->fov = 45.0f;
}

void func_80106DF8_mchar(omObjData *arg0) {
    if ((D_80106E80_mchar != 0) || (D_800D530C_main != 0)) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 8);
        arg0->func = func_80106E54_mchar;
        HuAudSeqFadeOut(0x3C);
    }
}

void func_80106E54_mchar(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}
