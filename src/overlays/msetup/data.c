#include "common.h"
#include "overlays/msetup_internal.h"

extern const char D_8011A6E4_msetup[];
extern const char D_8011A6F0_msetup[];
extern const char D_8011A6FC_msetup[];
extern const char D_8011A708_msetup[];
extern const char D_8011A714_msetup[];
extern const char D_8011A720_msetup[];
extern const char D_8011A72C_msetup[];
extern const char D_8011A738_msetup[];
extern const char D_8011A744_msetup[];
extern const char D_8011A74C_msetup[];
extern const char D_8011A754_msetup[];
extern const char D_8011A75C_msetup[];
extern const char D_8011A764_msetup[];
extern const char D_8011A76C_msetup[];
extern const char D_8011A774_msetup[];
extern const char D_8011A77C_msetup[];
extern const char D_8011A784_msetup[];
extern const char D_8011A78C_msetup[];
extern const char D_8011A794_msetup[];
extern const char D_8011A79C_msetup[];
extern const char D_8011A7A4_msetup[];
extern const char D_8011A7AC_msetup[];

u16 D_80119410_msetup = 0;

s16 D_80119412_msetup = 0;

f32 D_80119414_msetup = 58.0f;

s8 D_80119418_msetup = 0;

u8 D_80119419_msetup = 10;

u32 D_8011941C_msetup = 0;

Process *D_80119420_msetup = NULL;

s32 D_80119424_msetup[] = {0x140001, 0x14000C, 0x14000D};

omObjData *D_80119430_msetup = NULL;

s16 (*D_80119434_msetup[])(s16) = {
    func_801077E0_msetup,
    func_80107840_msetup,
    func_80107964_msetup,
    func_80107A58_msetup,
    func_80107B8C_msetup,
    func_80107CF4_msetup,
    func_80107D84_msetup,
    func_80107E48_msetup,
    func_80107ECC_msetup,
};

s16 (*D_80119458_msetup[])(s16) = {func_80108464_msetup, func_801084C4_msetup, func_801085D4_msetup, func_801086C8_msetup, func_801087F4_msetup, func_801088A8_msetup, func_80108938_msetup, func_801089FC_msetup};

u8 D_80119478_msetup[] = {
    0, 0, 1, 1, 2, 2, 3, 3,
    4, 4, 5, 5, 5, 5, 0, 0,
};

u8 D_80119488_msetup[] = {
    0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 1, 0, 2, 2, 0, 0,
};

u8 D_80119498_msetup[] = {
    4, 4, 3, 3, 5, 5, 2, 2,
    0, 0, 7, 6, 6, 0, 0, 0,
};

s32 D_801194A8_msetup[] = {0x1A01, 0x1A02, 0x1A03, 0x1A04, 0x1A05, 0x1A06};

s32 D_801194C0_msetup[] = {0x2901, 0x2902, 0x2903, 0x2904, 0x2905, 0x2906};

s32 D_801194D8_msetup[] = {0x290D, 0x290F, 0x290C, 0x290A, 0x2909, 0x290B, 0x290E, 0x290E};

s32 D_801194F8_msetup[] = {0x290F, 0x2910, 0x2911, 0x2912, 0x2913, 0x2913};

s16 (*D_80119510_msetup[])(s16) = {func_80109EA0_msetup, func_801077E0_msetup, func_80107840_msetup, func_80107964_msetup, func_8010A204_msetup};

s16 (*D_80119524_msetup[])(s16) = {func_80109F04_msetup, func_80109F7C_msetup, func_8010A10C_msetup, func_8010A2B0_msetup};

s32 D_80119534_msetup[] = {0x1701, 0x1702, 0x1703, 0x1704, 0x1705};

s32 D_80119548_msetup[] = {0x2601, 0x2602, 0x2603, 0x2604, 0x2605};

void (*D_8011955C_msetup[])(void) = {
    func_80107FB4_msetup,
    func_80108AB8_msetup,
    func_80109218_msetup,
    func_80109868_msetup,
    func_80118D48_msetup,
    func_8010A780_msetup,
    func_8010A7A0_msetup,
    func_8010AC78_msetup,
    func_8010AC94_msetup,
};

MsetupCameraPreset D_80119580_msetup = {{270.0f, 0.0f, 0.0f}, {0.0f, 200.0f, 0.0f}, 130.0f, 50.0f};

MsetupCameraKeyframe D_801195A0_msetup[] = {
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 130.0f, 50.0f}}, 1.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 130.0f, 50.0f}}, 0.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 450.0f, 50.0f}}, 0.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 1000.0f, 50.0f}}, 0.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 166.5f, 70.0f}, 700.0f, 50.0f}}, 0.0f},
    {{{{352.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{352.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}}, 0.0f},
};

MsetupCameraKeyframe D_801196C0_msetup[] = {
    {{{{-8.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{-8.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{68.0f, 0.0f, 0.0f}, {0.0f, 166.5f, 70.0f}, 560.0f, 50.0f}}, 1.0f},
    {{{{90.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 810.0f, 50.0f}}, 0.0f},
    {{{{90.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 1960.0f, 150.0f}}, 0.0f},
    {{{{90.0f, 0.0f, 0.0f}, {0.0f, 164.5f, 70.0f}, 1960.0f, 150.0f}}, 0.0f},
    {{{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}}, 0.0f},
};

MsetupCameraKeyframe D_801197BC_msetup[] = {
    {{{{352.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{352.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 70.0f}, 560.0f, 50.0f}}, 0.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 50.0f}, 560.0f, 50.0f}}, 1.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 50.0f}, 560.0f, 50.0f}}, 1.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 50.0f}, 1800.0f, 156.0f}}, 1.0f},
    {{{{270.0f, 0.0f, 0.0f}, {0.0f, 169.5f, 50.0f}, 1800.0f, 156.0f}}, 1.0f},
    {{{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f, 0.0f}}, 0.0f},
};

/* Padding between the camera paths and the model data. */
s32 D_801198B8_msetup[2] = {0, 0};

s16 D_801198C0_msetup = -1;

MsetupModelEntry D_801198C4_msetup[] = {
    {0xA0075, 0x2AD, 0, 2, 1, {184.0f, 0.0f, 77.0f}, {0.0f, -30.0f, 0.0f}},
    {0xA0077, 8, 0, 0, 0, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
    {0xA0078, 8, 0, 0, 0, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
    {9, 0x29D, 0, 0, 1, {184.0f, 0.0f, 77.0f}, {0.0f, 0.0f, 0.0f}},
};

s32 D_80119964_msetup[] = {0x200A1, 0x300A2, 0x700A2, 0x400A2, 0x500A1, 0x600A1, 0x800A1, 0x90003};

u8 D_80119984_msetup[] = {1, 0, 0, 0, 1, 1, 1, 0};

s32 D_8011998C_msetup[] = {0x20025, 0x30025, 0x70025, 0x40025, 0x50025, 0x60025, 0x80025, 0x70025};

s32 D_801199AC_msetup[] = {
    0x20033, 0x30033, 0x70033, 0x40033, 0x50033, 0x60033, 0x80033, 0x9000B,
    0x20072, 0x30072, 0x70072, 0x40072, 0x50072, 0x60072, 0x80072, 0x70072,
};

s32 D_801199EC_msetup[] = {0x2004E, 0x3004E, 0x7004E, 0x4004E, 0x5004E, 0x6004E, 0x8004E, 0x90013};

Vec D_80119A0C_msetup[] = {
    {-272.0f, 0.0f, -16.0f},
    {-136.0f, 0.0f, -16.0f},
    {0.0f, 0.0f, -16.0f},
    {136.0f, 0.0f, -16.0f},
};

Vec D_80119A3C_msetup[] = {
    {-184.0f, 0.0f, -16.0f},
    {88.0f, 0.0f, -16.0f},
};

f32 D_80119A54_msetup[] = {22.0f, 12.0f, 0.0f, -12.0f};

f32 D_80119A64_msetup[] = {16.0f, -5.0f};

s16 D_80119A6C_msetup[] = {5, 5, 0, 0, 0, 5, 5, 5};

s32 D_80119A7C_msetup[] = {0x14001D, 0x14001E, 0x14001F, 0x140020};

s32 D_80119A8C_msetup[] = {
    0x140025, 0x140026, 0x140027, 0x140028, 0x140029, 0x14002A, 0x14002B, 0x14002C,
    0x14002D, 0x14002E,
};

s32 D_80119AB4_msetup[] = {0x14002F, 0x140030, 0x140031, 0x140032, 0x140033};

u8 D_80119AC8_msetup[] = {255, 255, 255, 0};

u16 D_80119ACC_msetup = 76;

s32 D_80119AD0_msetup[] = {0x140043, 0x140044, 0x140045, 0x140046, 0x140047, 0, 0, 0};

omObjData *D_80119AF0_msetup = NULL;

f32 D_80119AF4_msetup = 5.0f;

f32 D_80119AF8_msetup = 20.0f;

f32 D_80119AFC_msetup = 10.0f;

f32 D_80119B00_msetup[] = {8.0f, 40.0f, 20.0f};

f32 D_80119B0C_msetup[] = {1.0f, 1.0f, 1.0f, 0.0f, 0.0f};

Vec D_80119B20_msetup = {0.0f, -265.0f, -467.0f};

s32 D_80119B2C_msetup[] = {0x11000E, 0x30};

s32 D_80119B34_msetup[] = {0x1504, 0x1505, 0x1506, 0x1507};

s32 D_80119B44_msetup[] = {0x140035, 0x1300D3, 0x1300D2, 0x1300D4, 0x1300CF, 0x1300CF, 0x1300CF};

s16 D_80119B60_msetup[][2] = {
    {136, 144},
    {81, 136},
    {81, 149},
    {81, 162},
    {91, 136},
    {91, 149},
    {91, 162},
    {53, 148},
    {136, 144},
    {136, 144},
    {136, 144},
    {136, 144},
};

s16 D_80119B90_msetup[][4] = {
    {94, 119, 152, 62},
    {108, 104, 120, 31},
};

s32 D_80119BA0_msetup[] = {
    0x140036, 0x140037, 0x140038, 0x14003C, 0x14003A, 0x140039, 0x14003B, 0x14003D,
    0x14003E, 0x14003F, 0x140040, 0x140041,
};

s32 D_80119BD0_msetup[] = {0x241E, 0x241F, 0x2420, 0x2424, 0x2422, 0x2421, 0x2423, 0x2425};

s32 D_80119BF0_msetup[] = {0x2426, 0x2427, 0x2428, 0x242C, 0x242A, 0x2429, 0x242B, 0x242D};

u8 D_80119C10_msetup[][3] = {
    {1, 2, 1},
    {2, 1, 2},
    {1, 1, 1},
    {2, 2, 5},
    {2, 1, 3},
    {1, 1, 3},
    {0, 4, 3},
    {3, 1, 5},
};

MsetupModelTarget D_80119C28_msetup[] = {
    {{350.0f, 300.0f, -467.0f}, 0.0f},
    {{-350.0f, 300.0f, -467.0f}, 0.0f},
};

MsetupModelTarget D_80119C48_msetup[] = {
    {{0.0f, 300.0f, -467.0f}, 90.0f},
    {{0.0f, 300.0f, -467.0f}, 270.0f},
};

u8 D_80119C68_msetup[] = {0, 1, 2, 7, 3, 4, 5, 6};

s32 D_80119C70_msetup[] = {
    0x140014, 0x140015, 0x140016, 0x14001B, 0x140017, 0x140018, 0x140019, 0x14001A,
    -0x7FEE58C8, -0x7FEE58D4, -0x7FEE58E0, -0x7FEE58EC, -0x7FEE58F8, -0x7FEE5904, -0x7FEE5910, -0x7FEE591C,
};

s16 D_80119CB0_msetup[] = {693, 694, 695, 700, 696, 697, 698, 699};

s32 D_80119CC0_msetup[] = {0x150C, 0x150D, 0x150E, 0x1512, 0x150F, 0x1510, 0x1511, 0x1513};

s32 D_80119CE0_msetup[] = {0x2407, 0x2408, 0x2409, 0x240D, 0x240A, 0x240B, 0x240C, 0x240E};

s32 D_80119D00_msetup[] = {0x490C, 0x490D, 0x490E, 0x4912, 0x490F, 0x4910, 0x4911, 0x4913};

s32 D_80119D20_msetup[] = {
    0x4A06, 0x4A07, 0x4A08, 0x4A0C, 0x4A09, 0x4A0A, 0x4A0B, 0x4A0D,
    0x700035, 0x910035, 0xB20035, 0xD30035, 0x700055, 0x910055, 0xB20055, 0xD30055,
    0x140006, 0x14000B,
};

const char *D_80119D68_msetup[] = {D_8011A77C_msetup, D_8011A774_msetup, D_8011A76C_msetup, D_8011A764_msetup, D_8011A75C_msetup, D_8011A754_msetup, D_8011A74C_msetup, D_8011A744_msetup};

s32 D_80119D88_msetup[] = {0x130036, 0x130037, 0x130038, 0x13003D, 0x130039, 0x13003A, 0x13003B, 0x13003C};

s32 D_80119DA8_msetup[] = {0x1508, 0x150B, 0x150A, 0x1509};

s32 D_80119DB8_msetup[] = {0x1508, 0x2406, 0x2406, 0x2406};

MsetupModelTarget D_80119DC8_msetup[] = {
    {{350.0f, 300.0f, -467.0f}, 0.0f},
    {{-350.0f, 300.0f, -467.0f}, 0.0f},
};

s16 D_80119DE8_msetup[][2] = {
    {98, 50},
    {98, 84},
};

s16 D_80119DF0_msetup[][2] = {
    {108, 64},
    {165, 64},
    {222, 64},
};

s16 D_80119DFC_msetup[][2] = {
    {98, 64},
    {143, 64},
    {188, 64},
    {233, 64},
};

s16 (*D_80119E0C_msetup[])[2] = {D_80119DE8_msetup, D_80119DF0_msetup, D_80119DFC_msetup};

s32 D_80119E18_msetup[] = {0x1515, 0x1516};

const char *D_80119E20_msetup[] = {D_8011A7AC_msetup, D_8011A7A4_msetup, D_8011A79C_msetup, D_8011A794_msetup, D_8011A78C_msetup, D_8011A784_msetup};

s32 D_80119E38_msetup[] = {0x140059, 0x14005A, 0x14005B, 0x14005C, 0x140057, 0x140058};

s16 D_80119E50_msetup[] = {4, 0};

s16 D_80119E54_msetup[] = {5, 3};

s32 D_80119E58_msetup[] = {0x1519, 0x151A, 0x151B};

s32 D_80119E64_msetup[] = {0x152A, 0x152B, 0x152C};

s32 D_80119E70_msetup[] = {0x2410, 0x2411, 0x2412};

s32 D_80119E7C_msetup[] = {0x2431, 0x2432, 0x2433};

s32 D_80119E88_msetup[] = {0x1530, 0x1531, 0x1532};

s32 D_80119E94_msetup[] = {0x140048, 0x140049, 0x14004A, 0x14004B, 0x14004C, 0x14004D};

s32 D_80119EAC_msetup[] = {0x140051, 0x140052, 0x140053, 0x140054, 0x140055, 0x140056};

s32 D_80119EC4_msetup[] = {0x151E, 0x151F, 0x1520, 0x1521, 0x1522, 0x1523, 0x151D};

s32 D_80119EE0_msetup[] = {0x2415, 0x2416, 0x2417, 0x2418, 0x2419, 0x241A, 0x2414};

s32 D_80119EFC_msetup[] = {0x1A11, 0x1A12, 0x1A13, 0x1A14, 0x1A15, 0x1A16};

s32 D_80119F14_msetup[] = {
    0x291B, 0x291C, 0x291D, 0x291E, 0x291F, 0x2920, -0xFEFC01, 0x20102FF,
    0x3FF, -1,
};

s32 D_80119F3C_msetup[] = {0x1525, 0x1526, 0x1527, 0x1528};

f32 D_80119F4C_msetup[] = {288.0f, 216.0f, 144.0f, 72.0f, 0.0f};

f32 D_80119F60_msetup[] = {288.0f, 72.0f, 0.0f};

s16 D_80119F6C_msetup[] = {20, 35, 50, -1, -1, 0};

s16 D_80119F78_msetup[] = {
    10, 15, 20, 25, 30, 35, 40, 45,
    50, 0,
};

s32 D_80119F8C_msetup[] = {0x242F, 0x2430};

MsetupModelTarget D_80119F94_msetup[] = {
    {{-144.0f, 300.0f, -467.0f}, 180.0f},
    {{144.0f, 300.0f, -467.0f}, 180.0f},
};

MsetupModelTarget D_80119FB4_msetup[] = {
    {{0.0f, 300.0f, -467.0f}, 270.0f},
    {{0.0f, 300.0f, -467.0f}, 90.0f},
};

s32 D_80119FD4_msetup[] = {0x2404, 0x2405};

s32 D_80119FDC_msetup[] = {0x14004E, 0x14004F};

s16 D_80119FE4_msetup[] = {1, 2, 3, 4, 5, 0};

s16 (*D_80119FF0_msetup[])(MsetupMenuState *) = {
    func_80117818_msetup,
    func_8010F87C_msetup,
    func_80111650_msetup,
    func_801132C4_msetup,
    func_80114AA0_msetup,
    func_80115EE0_msetup,
    func_80113DEC_msetup,
    func_80113E20_msetup,
    func_80113ED4_msetup,
    func_801167B8_msetup,
    func_80116FE0_msetup,
    func_80113E54_msetup,
    func_801145D0_msetup,
    func_80113E88_msetup,
};

Vec D_8011A028_msetup[] = {
    {0.0f, 270.0f, -377.0f},
    {190.0f, 300.0f, -467.0f},
    {0.0f, 330.0f, -557.0f},
    {-190.0f, 300.0f, -467.0f},
};

s16 D_8011A058_msetup[4][4] = {
    {0, 1, 2, 3},
    {3, 0, 1, 2},
    {2, 3, 0, 1},
    {1, 2, 3, 0},
};

s16 D_8011A078_msetup[4][4] = {
    {0, 1, 3, 2},
    {3, 0, 1, 2},
    {1, 3, 0, 2},
    {3, 0, 1, 2},
};

s32 D_8011A098_msetup[] = {0x14000E, 0x14000F, 0x140010, 0x140011};

f32 D_8011A0A8_msetup[] = {180.0f, 0.0f, 0.0f, 0.0f};

f32 D_8011A0B8_msetup[] = {1.0f, 2.0f, 3.0f, 4.0f, 0.0f, 0.0f};

s16 D_8011A0D0_msetup[] = {693, 694, 695, 696, 697, 698};

Vec D_8011A0DC_msetup[] = {
    {-1000.0f, 700.0f, -700.0f},
    {-85.0f, -8.0f, 2.0f},
    {-341.0f, 133.0f, -534.0f},
    {-410.0f, -50.0f, -534.0f},
};

Vec D_8011A10C_msetup[] = {
    {1100.0f, 510.0f, -745.0f},
    {82.0f, 13.0f, 6.0f},
    {357.0f, -31.0f, -366.0f},
    {370.0f, -65.0f, -366.0f},
};

Vec D_8011A13C_msetup[] = {
    {0.0f, 700.0f, 2.0f},
    {0.0f, -8.0f, 2.0f},
    {0.0f, 700.0f, 2.0f},
    {0.0f, 205.0f, -534.0f},
};

Vec *D_8011A16C_msetup[] = {D_8011A0DC_msetup, D_8011A10C_msetup, D_8011A13C_msetup};

MsetupStorySprite D_8011A178_msetup[] = {
    {0x140065, {129.0f, -84.0f, 0.0f}},
    {0x140065, {126.0f, 85.0f, 0.0f}},
    {0x140065, {-127.0f, 93.0f, 0.0f}},
    {0x140065, {-139.0f, -73.0f, 0.0f}},
    {0x140066, {142.0f, 0.0f, 0.0f}},
    {0x140066, {46.0f, 106.0f, 0.0f}},
    {0x140066, {-39.0f, 111.0f, 0.0f}},
    {0x140066, {-143.0f, 4.0f, 0.0f}},
    {0x140066, {-62.0f, -92.0f, 0.0f}},
    {0x140066, {27.0f, -95.0f, 0.0f}},
};

MsetupStorySprite D_8011A218_msetup[] = {
    {0x140065, {81.0f, -99.0f, 0.0f}},
    {0x140065, {79.0f, 104.0f, 0.0f}},
    {0x140065, {-88.0f, 106.0f, 0.0f}},
    {0x140065, {-84.0f, -108.0f, 0.0f}},
    {0x140066, {94.0f, -36.0f, 0.0f}},
    {0x140066, {114.0f, 41.0f, 0.0f}},
    {0x140066, {0.0f, 111.0f, 0.0f}},
    {0x140066, {-92.0f, 16.0f, 0.0f}},
    {0x140066, {-115.0f, -42.0f, 0.0f}},
    {0x140066, {6.0f, -122.0f, 0.0f}},
};

MsetupStorySprite D_8011A2B8_msetup[] = {
    {0x140064, {0.0f, 0.0f, 0.0f}},
    {0x140065, {129.0f, -84.0f, 0.0f}},
    {0x140065, {126.0f, 85.0f, 0.0f}},
    {0x140065, {-127.0f, 93.0f, 0.0f}},
    {0x140065, {-139.0f, -73.0f, 0.0f}},
    {0x140066, {142.0f, 0.0f, 0.0f}},
    {0x140066, {46.0f, 106.0f, 0.0f}},
    {0x140066, {-39.0f, 111.0f, 0.0f}},
    {0x140066, {-143.0f, 4.0f, 0.0f}},
    {0x140066, {-62.0f, -92.0f, 0.0f}},
    {0x140066, {27.0f, -95.0f, 0.0f}},
};

Vec D_8011A368_msetup[] = {
    {-30.0f, 190.0f, 0.0f},
    {30.0f, 170.0f, 0.0f},
    {-30.0f, 190.0f, 0.0f},
};

Vec D_8011A38C_msetup[] = {
    {20.0f, 25.0f, 0.0f},
    {20.0f, 335.0f, 0.0f},
    {20.0f, 25.0f, 0.0f},
};

u8 D_8011A3B0_msetup[] = {0, 1, 2, 3, 4, 5, 0, 0};

MsetupStorySprite D_8011A3B8_msetup[] = {
    {0x14005D, {0.0f, 0.0f, 0.0f}},
    {0x140014, {-102.0f, 50.0f, 0.0f}},
    {0x140015, {0.0f, 50.0f, 0.0f}},
    {0x140016, {105.0f, 50.0f, 0.0f}},
    {0x140017, {-102.0f, -55.0f, 0.0f}},
    {0x140018, {0.0f, -55.0f, 0.0f}},
    {0x140019, {105.0f, -55.0f, 0.0f}},
};

MsetupStorySprite D_8011A428_msetup[] = {
    {0x14005E, {0.0f, 0.0f, 0.0f}},
    {0x14005F, {0.0f, 95.0f, 0.0f}},
    {0x140060, {0.0f, 33.0f, 0.0f}},
    {0x140061, {0.0f, -30.0f, 0.0f}},
    {0x140062, {0.0f, -93.0f, 0.0f}},
};

MsetupStorySprite D_8011A478_msetup[] = {
    {0x14005E, {0.0f, 0.0f, 0.0f}},
    {0x14005F, {0.0f, 95.0f, 0.0f}},
    {0x140060, {0.0f, 33.0f, 0.0f}},
    {0x140061, {0.0f, -30.0f, 0.0f}},
    {0x140063, {0.0f, -93.0f, 0.0f}},
};

MsetupStorySprite D_8011A4C8_msetup[] = {
    {0x14006A, {-90.0f, 0.0f, 0.0f}},
    {0x14006B, {90.0f, 0.0f, 0.0f}},
    {0x140069, {-90.0f, 0.0f, 0.0f}},
    {0x140069, {90.0f, 0.0f, 0.0f}},
};

s32 D_8011A508_msetup[] = {0x11000E, 0x30, 0x11000E};

s16 D_8011A514_msetup[][2] = {
    {90, 95},
    {130, 95},
    {170, 95},
    {90, 135},
    {130, 135},
    {170, 135},
};

s16 D_8011A52C_msetup[][2] = {
    {146, 77},
    {146, 102},
    {146, 127},
    {146, 152},
};

s16 D_8011A53C_msetup[][2] = {
    {124, 100},
    {194, 100},
};

s16 (*D_8011A544_msetup[])[2] = {D_8011A514_msetup, D_8011A52C_msetup, D_8011A53C_msetup};

u8 D_8011A550_msetup[] = {0, 1, 0, 0};

MsetupCameraPreset D_8011A554_msetup = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 650.0f, 50.0f};

/* Align the following rodata to 16 bytes. */
s32 D_8011A574_msetup[] = {0, 0, 0};
