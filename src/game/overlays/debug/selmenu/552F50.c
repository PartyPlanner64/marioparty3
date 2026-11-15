#include "common.h"
#include "gcc/string.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

typedef struct SelMenuConfig {
    u8 available;
    u8 player_groups;
    u8 unk_02;
    u8 unk_03;
    u32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    char *name;
} SelMenuConfig; // sizeof 0x10

typedef struct SelMenuPlayerGroups {
    u8 group[4];
    u8 unk_04[4];
    s16 unk_08[4];
} SelMenuPlayerGroups; // sizeof 0x10

typedef struct SelMenuSound {
    s16 fx;
    u8 unk_02;
    s8 vol;
} SelMenuSound; // sizeof 0x4

extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern s16 D_800D1F28_main;
extern char D_80109820_selmenu[];
extern char D_8010982C_selmenu[];
extern char D_80109838_selmenu[];
extern char D_80109844_selmenu[];
extern char D_80109850_selmenu[];
extern char D_8010985C_selmenu[];
extern char D_80109868_selmenu[];
extern char D_80109874_selmenu[];
extern char D_8010987C_selmenu[];
extern char D_80109884_selmenu[];
extern char D_8010988C_selmenu[];
extern char D_80109894_selmenu[];
extern char D_8010989C_selmenu[];
extern char D_801098A4_selmenu[];
extern char D_801098AC_selmenu[];
extern char D_801098B4_selmenu[];
extern char D_801098BC_selmenu[];
extern char D_801098C8_selmenu[];
extern char D_801098D4_selmenu[];
extern char D_801098E0_selmenu[];
extern char D_801098EC_selmenu[];
extern char D_801098F4_selmenu[];
extern char D_801098FC_selmenu[];
extern char D_80109904_selmenu[];
extern char D_8010990C_selmenu[];
extern char D_80109914_selmenu[];
extern char D_8010991C_selmenu[];
extern char D_80109924_selmenu[];
extern char D_8010992C_selmenu[];
extern char D_80109934_selmenu[];
extern char D_80109948_selmenu[];
extern char D_8010995C_selmenu[];
extern char D_80109970_selmenu[];
extern char D_80109984_selmenu[];
extern char D_80109998_selmenu[];
extern char D_801099AC_selmenu[];
extern char D_801099B4_selmenu[];
extern char D_801099C8_selmenu[];
extern char D_801099E0_selmenu[];
extern char D_801099F8_selmenu[];
extern char D_80109A0C_selmenu[];
extern char D_80109A1C_selmenu[];
extern char D_80109A30_selmenu[];
extern char D_80109A44_selmenu[];
extern char D_80109A58_selmenu[];
extern char D_80109A70_selmenu[];
extern char D_80109A80_selmenu[];
extern char D_80109A94_selmenu[];
extern char D_80109AAC_selmenu[];
extern char D_80109AC8_selmenu[];
extern char D_80109AE0_selmenu[];
extern char D_80109AFC_selmenu[];
extern char D_80109B0C_selmenu[];
extern char D_80109B20_selmenu[];
extern char D_80109B34_selmenu[];
extern char D_80109B4C_selmenu[];
extern char D_80109B64_selmenu[];
extern char D_80109B74_selmenu[];
extern char D_80109B88_selmenu[];
extern char D_80109BA0_selmenu[];
extern char D_80109BB8_selmenu[];
extern char D_80109BD0_selmenu[];
extern char D_80109BE8_selmenu[];
extern char D_80109BFC_selmenu[];
extern char D_80109C14_selmenu[];
extern char D_80109C2C_selmenu[];
extern char D_80109C40_selmenu[];
extern char D_80109C58_selmenu[];
extern char D_80109C68_selmenu[];
extern char D_80109C7C_selmenu[];
extern char D_80109C90_selmenu[];
extern char D_80109CA4_selmenu[];
extern char D_80109CBC_selmenu[];
extern char D_80109CD0_selmenu[];
extern char D_80109CE4_selmenu[];
extern char D_80109CFC_selmenu[];
extern char D_80109D10_selmenu[];
extern char D_80109D28_selmenu[];
extern char D_80109D40_selmenu[];
extern char D_80109D58_selmenu[];
extern char D_80109D70_selmenu[];
extern char D_80109D88_selmenu[];
extern char D_80109D98_selmenu[];
extern char D_80109DAC_selmenu[];
extern char D_80109DBC_selmenu[];
extern char D_80109DD4_selmenu[];
extern char D_80109DEC_selmenu[];
extern char D_80109E04_selmenu[];
extern char D_80109E18_selmenu[];
extern char D_80109E30_selmenu[];
extern char D_80109E4C_selmenu[];
extern char D_80109E5C_selmenu[];
extern char D_80109E6C_selmenu[];
extern char D_80109E80_selmenu[];
extern char D_80109E94_selmenu[];
extern char D_80109EB0_selmenu[];
extern char D_80109EC4_selmenu[];
extern char D_80109EE0_selmenu[];
extern char D_80109EFC_selmenu[];
extern char D_80109F14_selmenu[];
extern char D_80109F2C_selmenu[];
extern char D_80109F34_selmenu[];
extern char D_80109F3C_selmenu[];
extern char D_80109F44_selmenu[];
extern char D_80109F4C_selmenu[];
extern char D_80109F58_selmenu[];
extern char D_80109F64_selmenu[];
extern char D_80109F68_selmenu[];
extern char D_80109F70_selmenu[];
extern char D_80109F7C_selmenu[];
extern char D_80109F84_selmenu[];
extern char D_80109F8C_selmenu[];
extern char D_80109F94_selmenu[];
extern char D_80109F9C_selmenu[];
extern char D_80109FA4_selmenu[];
extern char D_80109FAC_selmenu[];
extern char D_80109FB4_selmenu[];
extern char D_80109FBC_selmenu[];
extern char D_80109FC4_selmenu[];
extern char D_80109FCC_selmenu[];
extern char D_80109FD4_selmenu[];
extern char D_80109FDC_selmenu[];
extern char D_80109FE4_selmenu[];
extern char D_80109FEC_selmenu[];
extern char D_80109FF8_selmenu[];

SelMenuConfig D_80108C90_selmenu[100] = {
    { 0, 1, 11, 0, 1, 100, 0, D_80109F14_selmenu },     /* "201:PUKUPUKU FISHING" */
    { 0, 2, 11, 0, 2, 100, 0, D_80109EFC_selmenu },     /* "202:HIYAHIYA YASHINOMI" */
    { 0, 3, 11, 0, 3, 100, 0, D_80109EE0_selmenu },     /* "203:TERASHITE SEARCH LIGHT" */
    { 0, 4, 11, 0, 4, 100, 0, D_80109EC4_selmenu },     /* "204:GOROGORO IWAKOROGASHI" */
    { 0, 5, 11, 0, 5, 100, 0, D_80109EB0_selmenu },     /* "205:BOMHEI KOUKATAI" */
    { 0, 6, 11, 0, 6, 100, 0, D_80109E94_selmenu },     /* "206:DOKO?DOKO? KAKURENBO" */
    { 0, 7, 11, 0, 7, 100, 0, D_80109E80_selmenu },     /* "207:DOTABATA RELAY" */
    { 0, 8, 11, 0, 8, 100, 0, D_80109E6C_selmenu },     /* "208:ISOGE WANWAN" */
    { 0, 9, 11, 0, 9, 100, 0, D_80109E5C_selmenu },     /* "209:SUIJYOU SKI" */
    { 0, 10, 11, 0, 10, 100, 0, D_80109E4C_selmenu },   /* "210:WAVE*WAVE" */
    { 0, 11, 11, 0, 11, 100, 0, D_80109E30_selmenu },   /* "211:MOGOMOGU PIZZA HOUSE" */
    { 0, 12, 11, 0, 12, 100, 0, D_80109E18_selmenu },   /* "212:ATECHAE! MINI KOOPA" */
    { 0, 13, 11, 0, 13, 100, 0, D_80109E04_selmenu },   /* "213:GO!GO! ROCKET" */
    { 0, 14, 11, 0, 14, 100, 0, D_80109DEC_selmenu },   /* "214:BOBBLE HINO YOUJIN!" */
    { 0, 15, 11, 0, 15, 100, 0, D_80109DD4_selmenu },   /* "215:BURABURA BURANKO" */
    { 0, 16, 11, 0, 16, 100, 0, D_80109DBC_selmenu },   /* "216:TRUCK KIKI IPPATSU" */
    { 0, 17, 11, 0, 17, 100, 0, D_80109DAC_selmenu },   /* "217:PIT RACE" */
    { 0, 18, 11, 0, 18, 100, 0, D_80109D98_selmenu },   /* "218:KAKONDE KUREYON" */
    { 0, 19, 11, 0, 19, 100, 0, D_80109D88_selmenu },   /* "219:MAKIWARI" */
    { 0, 20, 11, 0, 20, 100, 0, D_80109D70_selmenu },   /* "220:NUIGURUMI FACTORY" */
    { 0, 21, 11, 0, 21, 100, 0, D_80109D58_selmenu },   /* "221:BELCON DANGEROUS" */
    { 0, 22, 11, 0, 22, 100, 0, D_80109D40_selmenu },   /* "222:POWER KINOKO GO!GO!" */
    { 0, 23, 11, 0, 23, 100, 0, D_80109D28_selmenu },   /* "223:TIKITIKI AIR FIGHT!" */
    { 0, 24, 11, 0, 24, 100, 0, D_80109D10_selmenu },   /* "224:PYONPYON BATTLE!" */
    { 0, 25, 11, 0, 25, 100, 0, D_80109CFC_selmenu },   /* "225:NOKONOKO ISLAND" */
    { 0, 26, 11, 0, 26, 100, 0, D_80109CE4_selmenu },   /* "226:NIGEKOME SHELTER" */
    { 0, 27, 11, 0, 27, 100, 0, D_80109CD0_selmenu },   /* "227:PITTARI! PATTER" */
    { 0, 28, 11, 0, 28, 100, 0, D_80109CBC_selmenu },   /* "228:OKKOTI PARASOL" */
    { 0, 29, 11, 0, 29, 100, 0, D_80109CA4_selmenu },   /* "229:MATIGAI WO SAGSE!" */
    { 0, 30, 11, 0, 30, 100, 0, D_80109C90_selmenu },   /* "230:OWASETE MONTAGE" */
    { 0, 31, 11, 0, 31, 100, 0, D_80109C7C_selmenu },   /* "231:DOSSUN PUZZLE" */
    { 0, 32, 11, 0, 32, 100, 0, D_80109C68_selmenu },   /* "232:TATAITE DRUM" */
    { 0, 33, 11, 0, 33, 100, 0, D_80109C58_selmenu },   /* "233:QUIZ PARTY" */
    { 0, 34, 11, 0, 34, 100, 0, D_80109C40_selmenu },   /* "234:ATEKKO CHARACTER" */
    { 0, 35, 11, 0, 35, 100, 0, D_80109C2C_selmenu },   /* "235:MOTORBOAT RACE" */
    { 0, 36, 11, 0, 36, 100, 0, D_80109C14_selmenu },   /* "236:KUNEKUNE ROAD RACE" */
    { 0, 37, 11, 0, 37, 100, 0, D_80109BFC_selmenu },   /* "237:AOZORA BLOCK RACE" */
    { 0, 38, 11, 0, 38, 100, 0, D_80109BE8_selmenu },   /* "238:BATAASHI RACE" */
    { 0, 39, 11, 0, 39, 100, 0, D_80109BD0_selmenu },   /* "239:TATAKE! MINI KOOPA" */
    { 0, 40, 11, 0, 40, 100, 0, D_80109BB8_selmenu },   /* "240:YUKIDAMA GOROGORO!" */
    { 0, 41, 11, 0, 41, 100, 0, D_80109BA0_selmenu },   /* "241:KAWASHITE BOBBLE" */
    { 0, 42, 11, 0, 42, 100, 0, D_80109B88_selmenu },   /* "242:CAPSULE MINI KOOPA" */
    { 0, 43, 11, 0, 43, 100, 0, D_80109B74_selmenu },   /* "243:HAYAOSHI HOUSE" */
    { 0, 44, 11, 0, 44, 100, 0, D_80109B64_selmenu },   /* "244:MOKUBA RACE" */
    { 0, 45, 11, 0, 45, 100, 0, D_80109B4C_selmenu },   /* "245:DANGEROUS ROULETTE" */
    { 0, 46, 11, 0, 46, 100, 0, D_80109B34_selmenu },   /* "246:MEKUTTE HAYAOSHI!" */
    { 0, 47, 11, 0, 47, 100, 0, D_80109B20_selmenu },   /* "247:AMEHURI FLOWER" */
    { 0, 48, 11, 0, 48, 100, 0, D_80109B0C_selmenu },   /* "248:AIKUN MAWASHI" */
    { 0, 49, 11, 0, 49, 100, 0, D_80109AFC_selmenu },   /* "249:TARZAN RACE" */
    { 0, 50, 11, 0, 50, 100, 0, D_80109AE0_selmenu },   /* "250:HIRAITA GATE NI PON!" */
    { 0, 51, 11, 0, 51, 100, 0, D_80109AC8_selmenu },   /* "251:BOUSOU!? SHUPPO-" */
    { 0, 52, 11, 0, 52, 100, 0, D_80109AAC_selmenu },   /* "252:TONDEKE KOOPA HAMMER" */
    { 0, 53, 11, 0, 53, 100, 0, D_80109A94_selmenu },   /* "253:ITAZURA MINI KOOPA" */
    { 0, 54, 11, 0, 54, 100, 0, D_80109A80_selmenu },   /* "254:TUBE COASTER" */
    { 0, 55, 11, 0, 55, 100, 0, D_80109A70_selmenu },   /* "255:BOLT DASH" */
    { 0, 56, 11, 0, 56, 100, 0, D_80109A58_selmenu },   /* "256:KONO E HA NAANI?" */
    { 0, 57, 11, 0, 57, 100, 0, D_80109A44_selmenu },   /* "257:JUMP DE CLOCK" */
    { 0, 58, 11, 0, 58, 100, 0, D_80109A30_selmenu },   /* "258:KIGURUMI KOOPA" */
    { 0, 59, 11, 0, 59, 100, 0, D_80109A1C_selmenu },   /* "259:NERAE! ITEM!!" */
    { 0, 60, 11, 0, 60, 100, 0, D_80109A0C_selmenu },   /* "260:ITEM HITTER" */
    { 0, 61, 11, 0, 61, 100, 0, D_801099F8_selmenu },   /* "261:NERATTE BALOON" */
    { 0, 62, 11, 0, 62, 100, 0, D_801099E0_selmenu },   /* "262:DOSSHI DE CATCH!" */
    { 0, 63, 11, 0, 63, 100, 0, D_801099C8_selmenu },   /* "263:BURABURA BURANKO" */
    { 0, 64, 11, 0, 64, 100, 0, D_801099B4_selmenu },   /* "264:ITEM THROWIN" */
    { 1, 65, 11, 0, 1000, 100, 0, D_801099AC_selmenu }, /* "265:" */
    { 0, 66, 11, 0, 65, 100, 0, D_80109998_selmenu },   /* "266:STARDUST BATTLE" */
    { 0, 67, 11, 0, 66, 100, 0, D_80109984_selmenu },   /* "267:HEIHO ROULETTE" */
    { 0, 68, 11, 0, 67, 100, 0, D_80109970_selmenu },   /* "268:OTITARA DAMEYO" */
    { 0, 69, 11, 0, 68, 100, 0, D_8010995C_selmenu },   /* "269:KINOPIO?KOOPA?" */
    { 0, 70, 11, 0, 69, 100, 0, D_80109948_selmenu },   /* "270:WANWAN BATTLE" */
    { 0, 71, 11, 0, 70, 100, 0, D_80109934_selmenu },   /* "271:MOTORBOAT TRIAL" */
    { 1, 1, 11, 0, 1000, 100, 0, D_8010992C_selmenu },  /* "272:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_80109924_selmenu },  /* "273:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_8010991C_selmenu },  /* "274:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_80109914_selmenu },  /* "275:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_8010990C_selmenu },  /* "276:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_80109904_selmenu },  /* "277:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_801098FC_selmenu },  /* "278:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_801098F4_selmenu },  /* "279:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_801098EC_selmenu },  /* "280:" */
    { 0, 1, 11, 0, 91, 100, 0, D_801098E0_selmenu },    /* "281:DUEL01" */
    { 0, 1, 11, 0, 92, 100, 0, D_801098D4_selmenu },    /* "282:DULE02" */
    { 0, 1, 11, 0, 93, 100, 0, D_801098C8_selmenu },    /* "283:DUEL03" */
    { 0, 1, 11, 0, 94, 100, 0, D_801098BC_selmenu },    /* "284:DUEL04" */
    { 1, 1, 11, 0, 1000, 100, 0, D_801098B4_selmenu },  /* "285:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_801098AC_selmenu },  /* "286:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_801098A4_selmenu },  /* "287:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_8010989C_selmenu },  /* "288:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_80109894_selmenu },  /* "289:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_8010988C_selmenu },  /* "290:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_80109884_selmenu },  /* "291:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_8010987C_selmenu },  /* "292:" */
    { 1, 1, 11, 0, 1000, 100, 0, D_80109874_selmenu },  /* "293:" */
    { 0, 1, 11, 0, 115, 100, 0, D_80109868_selmenu },   /* "294:RESULT3" */
    { 0, 1, 11, 0, 106, 100, 0, D_8010985C_selmenu },   /* "295:CHANCE" */
    { 0, 1, 11, 0, 114, 100, 0, D_80109850_selmenu },   /* "296:RESULT2" */
    { 0, 1, 11, 0, 112, 100, 0, D_80109844_selmenu },   /* "297:INST" */
    { 0, 1, 11, 0, 113, 100, 0, D_80109838_selmenu },   /* "298:RESULT" */
    { 0, 1, 11, 0, 126, 100, 0, D_8010982C_selmenu },   /* "299:SAMPLE" */
    { 0, 1, 11, 0, 86, 100, 0, D_80109820_selmenu },    /* "300*MCHAR" */
};

SelMenuPlayerGroups D_801092D0_selmenu[] = {
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 2, 3 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
};

SelMenuSound D_80109740_selmenu[] = {
    { 1, 0, 0x78 },
    { 9, 0, 0x6A },
    { 2, 0, 0x6E },
    { 4, 0, 0x72 },
    { 76, 0, 0x7B },
};

u16 D_80109754_selmenu[2][2] = { { 5, 13 }, { 4, 12 } }; // text colors

SelMenuConfig D_8010975C_selmenu[] = {
    { 1, 3, 11, 0, 1000, 0, 0, D_80109F58_selmenu }, /* ">PLAYER%d" */
    { 0, 4, 12, 0, 1000, 0, 0, D_80109F4C_selmenu }, /* "PAD%d:%s" */
    { 0, 4, 12, 0, 1000, 0, 0, D_80109F44_selmenu }, /* "GRP :%d" */
    { 0, 4, 12, 0, 1000, 0, 0, D_80109F3C_selmenu }, /* "DIF :%s" */
    { 0, 4, 12, 0, 1000, 0, 0, D_80109F34_selmenu }, /* "COIN:%d" */
    { 0, 4, 12, 0, 1000, 0, 0, D_80109F2C_selmenu }, /* "PADN:%d" */
};

char *D_801097BC_selmenu[] = { D_80109F68_selmenu, D_80109F64_selmenu };

char *D_801097C4_selmenu[] = { D_80109F8C_selmenu, D_80109F84_selmenu, D_80109F7C_selmenu, D_80109F70_selmenu };

char *D_801097D4_selmenu[] = { D_80109FCC_selmenu, D_80109FC4_selmenu, D_80109FBC_selmenu, D_80109FB4_selmenu, D_80109FAC_selmenu, D_80109FA4_selmenu, D_80109F9C_selmenu, D_80109F94_selmenu };

char *D_801097F4_selmenu[] = { D_80109FE4_selmenu, D_80109FDC_selmenu, D_80109FD4_selmenu };

u8 D_80109800_selmenu = 0;
char *D_80109804_selmenu[] = { D_80109F8C_selmenu, D_80109F84_selmenu, D_80109F7C_selmenu }; /* Unreferenced. */
s32 D_80109810_selmenu = 0;
s32 D_80109814_selmenu = 0;
s32 D_80109818_selmenu = 1;

s16 D_8010A070_selmenu BSS;
s16 D_8010A072_selmenu BSS;
u8 D_8010A074_selmenu[4] BSS; /* Unreferenced. */
s16 D_8010A078_selmenu[10] BSS;
s16 D_8010A08C_selmenu BSS;
s16 D_8010A08E_selmenu BSS;
s16 D_8010A090_selmenu BSS;
u8 D_8010A094_selmenu[4] BSS; /* Unreferenced. */
GW_PLAYER D_8010A098_selmenu[4] BSS;
u8 D_8010A178_selmenu[0x38] BSS; /* Unreferenced. */
u8 D_8010A1B0_selmenu[4] BSS;
u8 D_8010A1B4_selmenu[8] BSS;
u8 D_8010A1BC_selmenu[4] BSS; /* Unreferenced. */
s16 D_8010A1C0_selmenu[8] BSS;
s16 D_8010A1D0_selmenu[8] BSS;
s16 D_8010A1E0_selmenu[8] BSS;
s16 D_8010A1F0_selmenu[4] BSS;
s8 D_8010A1F8_selmenu[4] BSS;
s8 D_8010A1FC_selmenu[4] BSS;
u8 D_8010A200_selmenu BSS;
s16 D_8010A202_selmenu BSS;
s16 D_8010A204_selmenu BSS;
u16 D_8010A206_selmenu BSS;
s16 D_8010A208_selmenu BSS;
u8 D_8010A20C_selmenu[4] BSS; /* Unreferenced. */
s16 D_8010A210_selmenu[40] BSS;
f32 D_8010A260_selmenu[4] BSS;
u8 D_8010A270_selmenu[4] BSS;
u16 D_8010A274_selmenu[4] BSS;
u16 D_8010A27C_selmenu[4] BSS;
u16 D_8010A284_selmenu[4] BSS;

void func_80105F30_selmenu(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);
void func_80105FC8_selmenu(omObjData *obj);
void func_80106770_selmenu(omObjData *obj);
void func_80106A10_selmenu(omObjData *obj);
void func_80106DEC_selmenu(omObjData *obj);
void func_80107924_selmenu(omObjData *obj);
void func_80107DEC_selmenu(omObjData *obj);
void func_80107DFC_selmenu(omObjData *obj);
void func_801087C8_selmenu(u16 index);
void func_80108814_selmenu(s16 dir);
void func_801089C0_selmenu(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4);
void func_80108890_selmenu(s16 dir);
void func_80108A40_selmenu(void);
void func_80108AB4_selmenu(void);
void func_80108B1C_selmenu(void);
void func_80108BE8_selmenu(void);

void func_801059A0_selmenu(void) {
    omObjData *obj;
    u16 sprite;
    s32 i;

    D_8010A200_selmenu = 0;
    _SetFlag(0x12);
    GwSystem.show_minigame_explanations = 0;
    if (omprevovl >= 0 && omprevovl < 71) {
        for (i = 0; i < 4; i++) {
            GwPlayer[i].coin += GwPlayer[i].gameCoin;
            GwPlayer[i].coin += GwPlayer[i].bonusCoin;
            if (GwPlayer[i].coin >= 1000) {
                GwPlayer[i].coin = 999;
            }
            if (GwPlayer[i].coin < 0) {
                GwPlayer[i].coin = 0;
            }
            GwPlayer[i].gameCoin = 0;
            GwPlayer[i].bonusCoin = 0;
        }
    }
    omInitObjMan(50, 0);
    func_80105F30_selmenu(2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightMaxSet(1);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightColorSet(1, 0x60, 0x60, 0x10);
    Hu3DGLightDirSet(1, 100.0f, -100.0f, 100.0f);
    omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omAddObj(0, 0, 0, -1, func_80105FC8_selmenu);
    omAddObj(1, 0, 0, -1, func_80106770_selmenu);
    omMakeGroup(0, 32);
    obj = omAddObj(10, 1, 80, -1, NULL);
    for (i = 0; i < 8; i++) {
        D_8010A1C0_selmenu[i] = Hu3DModelRead(D_800A178C_main[i][0] | D_800A1790_main[i][0], 0x69D);
        Hu3DData[D_8010A1C0_selmenu[i]].motAttr |= 2;
        omObjMotionRead(obj, 0, CharMotionDataNumGet(i, 0));
        D_8010A1D0_selmenu[i] = obj->motion[0];
        omObjMotionRead(obj, 1, CharMotionDataNumGet(i, 0x2F));
        D_8010A1E0_selmenu[i] = obj->motion[1];
    }
    omDelObj(obj);
    for (i = 0; i < 4; i++) {
        D_8010A1FC_selmenu[i] = 0;
        D_8010A1F8_selmenu[i] = 0;
    }
    D_8010A202_selmenu = HuSprAnimDataRead(0x10020);
    espPalColorSet(D_8010A202_selmenu, 0.3f, 0.3f, 0.3f);
    for (i = 0; i < 35; i++) {
        sprite = espEntry(D_8010A202_selmenu, i % 6, 1);
        espDispOn(sprite);
        espPriSet(sprite, 0xFFFF);
        espAttrSet(sprite, 0x4000);
        espTPLvlSet(sprite, 0xFF);
        espPosSet(sprite, (i % 7) * 48, (i / 7) * 48);
    }
    D_8010A204_selmenu = HuSprAnimDataRead(10);
    D_8010A206_selmenu = espEntry(D_8010A204_selmenu, 0, 1);
    espDispOn(D_8010A206_selmenu);
    espPosSet(D_8010A206_selmenu, 0x80, 0x80);
    espScaleSet(D_8010A206_selmenu, 0.25f, 0.25f);
    for (i = 0; i < 40; i++) {
        D_8010A210_selmenu[i] = -1;
    }
    D_8010A208_selmenu = HuSprAnimDataRead(12);
    for (i = 0; i < 4; i++) {
        D_8010A27C_selmenu[i] = 0;
        D_8010A284_selmenu[i] = 0;
        D_8010A274_selmenu[i] = 0;
    }
    WipeCreateIn(0xFF, 16);
    HuAudSeqPlay(rand8() % 9);
}

void func_80105F30_selmenu(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    CamSetupInit(1);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
}

void func_80105FC8_selmenu(omObjData *obj) {
    s8 stickX;
    s8 stickY;
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8010A270_selmenu[i] = 0;
        if (!CheckControllerRead(i)) {
            continue;
        }
        if (WipeStatGet() == 1) {
            continue;
        }
        stickX = D_800CBB6E_main[i];
        stickY = D_800D20A1_main[i];
        if (D_800D5558_main[i] & (U_JPAD | U_CBUTTONS)) {
            D_8010A270_selmenu[i] |= 1;
        }
        if (D_800D5558_main[i] & (D_JPAD | D_CBUTTONS)) {
            D_8010A270_selmenu[i] |= 2;
        }
        if (D_800D5558_main[i] & (L_JPAD | L_CBUTTONS)) {
            D_8010A270_selmenu[i] |= 4;
        }
        if (D_800D5558_main[i] & (R_JPAD | R_CBUTTONS)) {
            D_8010A270_selmenu[i] |= 8;
        }
        if (stickY < -10 && ABS(D_8010A1FC_selmenu[i]) < 10) {
            D_8010A270_selmenu[i] |= 2;
        }
        if (stickY > 10 && ABS(D_8010A1FC_selmenu[i]) < 10) {
            D_8010A270_selmenu[i] |= 1;
        }
        if (stickX < -10 && ABS(D_8010A1F8_selmenu[i]) < 10) {
            D_8010A270_selmenu[i] |= 4;
        }
        if (stickX > 10 && ABS(D_8010A1F8_selmenu[i]) < 10) {
            D_8010A270_selmenu[i] |= 8;
        }
        D_8010A1F8_selmenu[i] = stickX;
        D_8010A1FC_selmenu[i] = stickY;
        if (D_800D5558_main[i] & Z_TRIG) {
            D_8010A270_selmenu[i] |= 0x40;
        }
        if ((D_800CDA7C_main[i] & (U_JPAD | U_CBUTTONS)) || stickY > 10) {
            if (D_8010A274_selmenu[i] & 1) {
                D_8010A27C_selmenu[i]++;
                if (D_8010A27C_selmenu[i] >= 16) {
                    D_8010A27C_selmenu[i] = 15;
                }
            } else {
                D_8010A27C_selmenu[i] = 0;
            }
            if (D_8010A274_selmenu[i] != 1) {
                D_8010A284_selmenu[i] = 0;
                D_8010A27C_selmenu[i] = 0;
            }
            D_8010A274_selmenu[i] = 1;
            if (D_8010A27C_selmenu[i] == 15) {
                if (D_8010A284_selmenu[i] == 0) {
                    D_8010A270_selmenu[i] |= 1;
                    D_8010A284_selmenu[i] = 2;
                } else {
                    D_8010A284_selmenu[i]--;
                }
            }
        } else if ((D_800CDA7C_main[i] & (D_JPAD | D_CBUTTONS)) || stickY < -10) {
            if (D_8010A274_selmenu[i] & 2) {
                D_8010A27C_selmenu[i]++;
                if (D_8010A27C_selmenu[i] >= 16) {
                    D_8010A27C_selmenu[i] = 15;
                }
            } else {
                D_8010A27C_selmenu[i] = 0;
            }
            if (D_8010A274_selmenu[i] != 2) {
                D_8010A284_selmenu[i] = 0;
                D_8010A27C_selmenu[i] = 0;
            }
            D_8010A274_selmenu[i] = 2;
            if (D_8010A27C_selmenu[i] == 15) {
                if (D_8010A284_selmenu[i] == 0) {
                    D_8010A270_selmenu[i] |= 2;
                    D_8010A284_selmenu[i] = 2;
                } else {
                    D_8010A284_selmenu[i]--;
                }
            }
        } else if ((D_800CDA7C_main[i] & (L_JPAD | L_CBUTTONS)) || stickX < -10) {
            if (D_8010A274_selmenu[i] & 4) {
                D_8010A27C_selmenu[i]++;
                if (D_8010A27C_selmenu[i] >= 16) {
                    D_8010A27C_selmenu[i] = 15;
                }
            } else {
                D_8010A27C_selmenu[i] = 0;
            }
            if (D_8010A274_selmenu[i] != 4) {
                D_8010A284_selmenu[i] = 0;
                D_8010A27C_selmenu[i] = 0;
            }
            D_8010A274_selmenu[i] = 4;
            if (D_8010A27C_selmenu[i] == 15) {
                if (D_8010A284_selmenu[i] == 0) {
                    D_8010A270_selmenu[i] |= 4;
                    D_8010A284_selmenu[i] = 2;
                } else {
                    D_8010A284_selmenu[i]--;
                }
            }
        } else if ((D_800CDA7C_main[i] & (R_JPAD | R_CBUTTONS)) || stickX > 10) {
            if (D_8010A274_selmenu[i] & 8) {
                D_8010A27C_selmenu[i]++;
                if (D_8010A27C_selmenu[i] >= 16) {
                    D_8010A27C_selmenu[i] = 15;
                }
            } else {
                D_8010A27C_selmenu[i] = 0;
            }
            if (D_8010A274_selmenu[i] != 8) {
                D_8010A284_selmenu[i] = 0;
                D_8010A27C_selmenu[i] = 0;
            }
            D_8010A274_selmenu[i] = 8;
            if (D_8010A27C_selmenu[i] == 15) {
                if (D_8010A284_selmenu[i] == 0) {
                    D_8010A270_selmenu[i] |= 8;
                    D_8010A284_selmenu[i] = 2;
                } else {
                    D_8010A284_selmenu[i]--;
                }
            }
        } else {
            D_8010A27C_selmenu[i] = 0;
        }
        if (D_800D5558_main[i] & A_BUTTON) {
            D_8010A270_selmenu[i] |= 0x10;
        }
        if (D_800D5558_main[i] & B_BUTTON) {
            D_8010A270_selmenu[i] |= 0x20;
        }
        if (D_800D5558_main[i] & START_BUTTON) {
            D_8010A270_selmenu[i] |= 0x80;
        }
        if ((D_800CDA7C_main[i] & (L_TRIG | R_TRIG)) == (L_TRIG | R_TRIG)) {
            omOvlReturnEx(0);
            return;
        }
    }
}

void func_80106770_selmenu(omObjData *obj) {
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        D_8010A1B4_selmenu[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].chr = i;
        D_8010A1F0_selmenu[i] = i;
        D_8010A1B0_selmenu[i] = 0;
        D_8010A260_selmenu[i] = 0.0f;
    }
    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            D_8010A1B4_selmenu[i] = 1;
        }
    }
    D_8010A070_selmenu = -1;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (D_80108C90_selmenu[i * 10 + j].available != 1) {
                break;
            }
        }
        if (j == 10) {
            D_8010A078_selmenu[i] = -1;
        } else {
            D_8010A078_selmenu[i] = j;
        }
    }
    func_80108890_selmenu(1);
    if (omprevovl != 999) {
        for (i = 0; i < 100; i++) {
            if (D_80108C90_selmenu[i].unk_04 == omprevovl) {
                D_8010A070_selmenu = i / 10;
                D_8010A072_selmenu = i % 10;
                D_8010A078_selmenu[D_8010A070_selmenu] = D_8010A072_selmenu;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        D_8010A098_selmenu[i] = GwPlayer[i];
    }
    func_80108A40_selmenu();
    obj->func = func_80106A10_selmenu;
}

void func_80106A10_selmenu(omObjData *obj) {
    SelMenuConfig *config;
    u16 *color;
    s32 x;
    s32 i;

    rand8();
    config = &D_80108C90_selmenu[D_8010A070_selmenu * 10];
    for (i = 0; i < 10; i++, config++) {
        sprintf(D_800D5218_main, config->name);
        // The strlen result is discarded; x is overwritten with a fixed position.
        x = strlen(D_800D5218_main);
        x = 0x40;
        if (D_80108C90_selmenu[D_8010A070_selmenu * 10 + i].available == 0) {
            color = D_80109754_selmenu[0];
        } else {
            color = D_80109754_selmenu[1];
        }
        if (D_8010A072_selmenu == i) {
            func_801089C0_selmenu(x, (i + 10) * 9, D_800D5218_main, color[1], color[0]);
        } else {
            func_801089C0_selmenu(x, (i + 10) * 9, D_800D5218_main, color[0], 0);
        }
    }
    sprintf(D_800D5218_main, D_80109FEC_selmenu, D_8010A070_selmenu + 1, 10);
    func_801089C0_selmenu(0x80, 0x40, D_800D5218_main, 15, 7);
    sprintf(D_800D5218_main, D_80109FF8_selmenu, D_801097F4_selmenu[D_800A175E_main]);
    func_801089C0_selmenu(0x80, 0x48, D_800D5218_main, 14, 6);
    espPosSet(D_8010A206_selmenu, 0x3C, (D_8010A072_selmenu + 11) * 9 - 1);
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        if ((D_8010A270_selmenu[i] & 0x90) && D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].available == 0) {
            if (D_80109800_selmenu == 0) {
                omAddObj(2, 0, 0, -1, func_80107DEC_selmenu);
                D_80109800_selmenu = 1;
                espDispOff(D_8010A206_selmenu);
                obj->func = func_80107924_selmenu;
                func_801087C8_selmenu(1);
            }
        } else if (D_8010A270_selmenu[i] & 1) {
            func_80108814_selmenu(-1);
            func_80108A40_selmenu();
            func_801087C8_selmenu(0);
        } else if (D_8010A270_selmenu[i] & 2) {
            func_80108814_selmenu(1);
            func_80108A40_selmenu();
            func_801087C8_selmenu(0);
        } else if (D_8010A270_selmenu[i] & 4) {
            func_80108890_selmenu(-1);
            func_80108A40_selmenu();
            func_801087C8_selmenu(4);
        } else if (D_8010A270_selmenu[i] & 8) {
            func_80108890_selmenu(1);
            func_80108A40_selmenu();
            func_801087C8_selmenu(4);
        } else if (D_8010A270_selmenu[i] & 0x40) {
            D_8010A08C_selmenu = 0;
            D_8010A08E_selmenu = 0;
            D_8010A090_selmenu = 0;
            obj->func = func_80106DEC_selmenu;
        } else if (D_800D5558_main[i] & 0x10) {
            if (++D_800A175E_main >= 3) {
                D_800A175E_main = 0;
            }
        }
    }
}

void func_80106DEC_selmenu(omObjData *obj) {
    SelMenuConfig *space;
    u16 *color;
    s32 x;
    s32 y;
    s32 row;
    s32 line;
    s16 sel;
    s16 cursorCol;
    s16 cursorRow;
    s32 i;
    s32 j;

    rand8();
    sprintf(D_800D5218_main, "* OPTION *");
    func_801089C0_selmenu(0x70, 0x40, D_800D5218_main, 15, 7);
    for (i = 0; i < 5; i++) {
        space = D_8010975C_selmenu;
        if (i == 4) {
            sprintf(D_800D5218_main, "MAP:%d", GwSystem.current_board_index);
            color = D_80109754_selmenu[0];
            if (D_8010A08E_selmenu == i) {
                func_801089C0_selmenu(0x80, 0x50, D_800D5218_main, color[1], color[0]);
            } else {
                func_801089C0_selmenu(0x80, 0x50, D_800D5218_main, color[0], 0);
            }
            continue;
        }
        for (j = 0; j < 6; j++, space++) {
            x = (i % 2) * 144 + 40;
            row = (i / 2) * 7;
            line = j + 12;
            y = (row + line) * 8;
            switch (j) {
                case 0:
                    sprintf(D_800D5218_main, space->name, i);
                    break;
                case 1:
                    sprintf(D_800D5218_main, space->name, D_8010A098_selmenu[i].pad,
                            D_801097BC_selmenu[D_8010A098_selmenu[i].stat & 1]);
                    break;
                case 2:
                    sprintf(D_800D5218_main, space->name, D_8010A098_selmenu[i].group);
                    break;
                case 3:
                    sprintf(D_800D5218_main, space->name, D_801097C4_selmenu[D_8010A098_selmenu[i].cpu_difficulty]);
                    break;
                case 4:
                    sprintf(D_800D5218_main, space->name, D_8010A098_selmenu[i].coin);
                    break;
                case 5:
                    sprintf(D_800D5218_main, space->name, D_8010A098_selmenu[i].pad);
                    break;
            }
            switch (D_8010A090_selmenu) {
                case 0:
                    if (j == 0) {
                        color = D_80109754_selmenu[0];
                        if (i == D_8010A08E_selmenu) {
                            func_801089C0_selmenu(x, y, D_800D5218_main, color[1], color[0]);
                        } else {
                            func_801089C0_selmenu(x, y, D_800D5218_main, color[0], 0);
                        }
                    } else {
                        func_801089C0_selmenu(x, y, D_800D5218_main, D_80109754_selmenu[1][0], 0);
                    }
                    break;
                case 1:
                    if (i == D_8010A08E_selmenu) {
                        color = D_80109754_selmenu[0];
                        if (j == D_8010A08C_selmenu) {
                            func_801089C0_selmenu(x, y, D_800D5218_main, color[1], color[0]);
                        } else {
                            func_801089C0_selmenu(x, y, D_800D5218_main, color[0], 0);
                        }
                    } else {
                        func_801089C0_selmenu(x, y, D_800D5218_main, D_80109754_selmenu[1][0], 0);
                    }
                    break;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        if (D_8010A270_selmenu[i] & 0x40) {
            obj->func = func_80106A10_selmenu;
            return;
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        switch (D_8010A090_selmenu) {
            case 0:
                if (D_8010A08E_selmenu < 2 && (D_8010A270_selmenu[i] & 1)) {
                    D_8010A08E_selmenu = 4;
                } else if (D_8010A08E_selmenu == 4 && (D_8010A270_selmenu[i] & 2)) {
                    D_8010A08E_selmenu = 0;
                } else if (D_8010A08E_selmenu == 4 && (D_8010A270_selmenu[i] & 4)) {
                    if (--GwSystem.current_board_index < 0) {
                        GwSystem.current_board_index = 0;
                    }
                } else if (D_8010A08E_selmenu == 4 && (D_8010A270_selmenu[i] & 8)) {
                    if (++GwSystem.current_board_index > 0) {
                        GwSystem.current_board_index = 0;
                    }
                } else if (D_8010A08E_selmenu != 4) {
                    if (D_8010A270_selmenu[i] & 0xC) {
                        D_8010A08E_selmenu ^= 1;
                    } else if (D_8010A270_selmenu[i] & 3) {
                        D_8010A08E_selmenu ^= 2;
                    }
                    if (D_8010A270_selmenu[i] & 0x20) {
                        obj->func = func_80106A10_selmenu;
                        return;
                    }
                    if (D_8010A270_selmenu[i] & 0x10) {
                        D_8010A090_selmenu = 1;
                        return;
                    }
                    if (D_8010A270_selmenu[i] & 0x80) {
                        func_80108B1C_selmenu();
                        func_80108BE8_selmenu();
                    }
                }
                break;
            case 1:
                if (D_8010A270_selmenu[i] & 1) {
                    if (--D_8010A08C_selmenu < 0) {
                        D_8010A08C_selmenu = 5;
                    }
                } else if (D_8010A270_selmenu[i] & 2) {
                    if (++D_8010A08C_selmenu >= 6) {
                        D_8010A08C_selmenu = 0;
                    }
                }
                if (D_8010A270_selmenu[i] & 8) {
                    switch (D_8010A08C_selmenu) {
                        case 0:
                            break;
                        case 1:
                            D_8010A098_selmenu[D_8010A08E_selmenu].stat ^= 1;
                            break;
                        case 2:
                            if (++D_8010A098_selmenu[D_8010A08E_selmenu].group >= 4) {
                                D_8010A098_selmenu[D_8010A08E_selmenu].group = 0;
                            }
                            break;
                        case 3:
                            if (++D_8010A098_selmenu[D_8010A08E_selmenu].cpu_difficulty >= 4) {
                                D_8010A098_selmenu[D_8010A08E_selmenu].cpu_difficulty = 0;
                            }
                            break;
                        case 4:
                            if (++D_8010A098_selmenu[D_8010A08E_selmenu].coin >= 1000) {
                                D_8010A098_selmenu[D_8010A08E_selmenu].coin = 0;
                            }
                            break;
                        case 5:
                            if (++D_8010A098_selmenu[D_8010A08E_selmenu].pad == 4) {
                                D_8010A098_selmenu[D_8010A08E_selmenu].pad = 0;
                            }
                            break;
                    }
                } else if (D_8010A270_selmenu[i] & 4) {
                    switch (D_8010A08C_selmenu) {
                        case 0:
                            break;
                        case 1:
                            D_8010A098_selmenu[D_8010A08E_selmenu].stat ^= 1;
                            break;
                        case 2:
                            if (D_8010A098_selmenu[D_8010A08E_selmenu].group == 0) {
                                D_8010A098_selmenu[D_8010A08E_selmenu].group = 3;
                            } else {
                                D_8010A098_selmenu[D_8010A08E_selmenu].group--;
                            }
                            break;
                        case 3:
                            if (D_8010A098_selmenu[D_8010A08E_selmenu].cpu_difficulty == 0) {
                                D_8010A098_selmenu[D_8010A08E_selmenu].cpu_difficulty = 3;
                            } else {
                                D_8010A098_selmenu[D_8010A08E_selmenu].cpu_difficulty--;
                            }
                            break;
                        case 4:
                            if (--D_8010A098_selmenu[D_8010A08E_selmenu].coin < 0) {
                                D_8010A098_selmenu[D_8010A08E_selmenu].coin = 999;
                            }
                            break;
                        case 5:
                            if (--D_8010A098_selmenu[D_8010A08E_selmenu].pad == 0xFF) {
                                D_8010A098_selmenu[D_8010A08E_selmenu].pad = 3;
                            }
                            break;
                    }
                } else if (D_8010A270_selmenu[i] & 0x30) {
                    D_8010A090_selmenu = 0;
                    D_8010A08C_selmenu = 0;
                    return;
                } else if (D_8010A270_selmenu[i] & 0x80) {
                    switch (D_8010A08C_selmenu) {
                        case 2:
                            func_80108B1C_selmenu();
                            break;
                        case 5:
                            func_80108BE8_selmenu();
                            break;
                    }
                }
                break;
        }
    }
    sel = D_8010A08E_selmenu;
    if (sel != 4) {
        cursorCol = sel % 2;
        cursorRow = sel / 2;
        x = cursorCol * 144;
        x += 40;
        y = cursorRow * 7;
        line = D_8010A08C_selmenu + 12;
        y += line;
        y++;
        y *= 8;
    } else {
        x = 0x80;
        y = 0x58;
    }
    espPosSet(D_8010A206_selmenu, x - 4, y);
}

void func_80107924_selmenu(omObjData *obj) {
    u32 x;
    s32 y;
    s32 shadowOfs = 12;
    s32 textOfs = 6;
    s32 i;

    rand8();
    sprintf(D_800D5218_main, D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].name);
    x = (320 - strlen(D_800D5218_main) * 8) / 2;
    y = (D_8010A072_selmenu + 10) * 9;
    // The do-while(0) ends a CSE block, keeping GCC from folding textOfs into the sprite positions.
    do {
    } while (0);
    if (y - D_80109810_selmenu > 48) {
        if (--D_80109818_selmenu == 0) {
            D_8010A210_selmenu[D_80109814_selmenu] = espEntry(D_8010A208_selmenu, 0, 1);
            espAttrSet(D_8010A210_selmenu[D_80109814_selmenu], 0x4000);
            espPriSet(D_8010A210_selmenu[D_80109814_selmenu], 0x8000);
            espScaleSet(D_8010A210_selmenu[D_80109814_selmenu], 0.75f, 0.75f);
            espSpeedSet(D_8010A210_selmenu[D_80109814_selmenu], 8.0f);
            espPosSet(D_8010A210_selmenu[D_80109814_selmenu], x, y - (u16)D_80109810_selmenu + textOfs + 8);
            espColorSet(D_8010A210_selmenu[D_80109814_selmenu], 0xFF, 0xFF, 0xBE);
            D_80109814_selmenu++;
            D_8010A210_selmenu[D_80109814_selmenu] = espEntry(D_8010A208_selmenu, 0, 1);
            espAttrSet(D_8010A210_selmenu[D_80109814_selmenu], 0x4000);
            espPriSet(D_8010A210_selmenu[D_80109814_selmenu], 0x8000);
            espScaleSet(D_8010A210_selmenu[D_80109814_selmenu], 0.75f, 0.75f);
            espSpeedSet(D_8010A210_selmenu[D_80109814_selmenu], 8.0f);
            espPosSet(D_8010A210_selmenu[D_80109814_selmenu],
                      x + strlen(D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].name) * 8,
                      y - (u16)D_80109810_selmenu + textOfs + 8);
            espColorSet(D_8010A210_selmenu[D_80109814_selmenu], 0xFF, 0xFF, 0xBE);
            D_80109814_selmenu++;
            D_80109818_selmenu = 4;
        }
        D_80109810_selmenu += 4;
        if (y < y - D_80109810_selmenu + shadowOfs) {
            shadowOfs = (y - D_80109810_selmenu + shadowOfs) - y;
        }
        if (y < y - D_80109810_selmenu + textOfs) {
            textOfs = (y - D_80109810_selmenu + textOfs) - y;
        }
        fontcolor = 9;
        print8(x, y - (u16)D_80109810_selmenu + shadowOfs, D_800D5218_main);
        fontcolor = 13;
        print8(x, y - (u16)D_80109810_selmenu + textOfs, D_800D5218_main);
    }
    for (i = 0; i < D_80109814_selmenu; i++) {
        if (D_8010A210_selmenu[i] != -1 && (espAnimStatGet(D_8010A210_selmenu[i]) & 6)) {
            espKill(D_8010A210_selmenu[i]);
            D_8010A210_selmenu[i] = -1;
        }
    }
    x = (320 - strlen(D_800D5218_main) * 8) / 2;
    fontcolor = 7;
    print8(x + 1, y + 1 - (u16)D_80109810_selmenu, D_800D5218_main);
    fontcolor = 15;
    print8(x, y - (u16)D_80109810_selmenu, D_800D5218_main);
}

void func_80107DEC_selmenu(omObjData *obj) {
    obj->func = func_80107DFC_selmenu;
}

void func_80107DFC_selmenu(omObjData *obj) {
    u8 freeChars[8];
    u16 pads[4];
    s32 ready = 0;
    s32 chr;
    u16 color;
    u16 textColor;
    u8 pick;
    s32 i;
    s32 j;
    u8 missing;
    u8 count;
    u8 index;

    if (D_8010A200_selmenu == 1) {
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            func_80108AB4_selmenu();
            GwSystem.minigame_index = D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].player_groups;
            GwSystem.current_player_index = 0;
            if (D_800A175E_main == 0) {
                if (D_800D1F28_main == 0) {
                    omOvlCallEx(D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].unk_04, 0, 0x94);
                } else {
                    omOvlCallEx(MgDataMaxGet(GwSystem.minigame_index), 0, 0x82);
                }
            } else if (D_800A175E_main == 1) {
                GwSystem.playMode = 1;
                omOvlCallEx(D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].unk_04, 0, 0x92);
            } else {
                GwSystem.playMode = 2;
                omOvlCallEx(D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].unk_04, 0, 0x4090);
            }
        }
        return;
    }
    for (i = 0; i < 4; i++) {
        if (D_8010A1B0_selmenu[i] == 1) {
            ready++;
        }
    }
    missing = 0;
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            pads[missing++] = i;
        }
    }
    if (ready == gNumOfControllers) {
        if (ready < 4) {
            for (index = 0; index < missing; index++) {
                count = 0;
                for (i = 0; i < 8; i++) {
                    freeChars[i] = 0;
                }
                for (i = 0; i < 8; i++) {
                    if (D_8010A1B4_selmenu[i] == 0) {
                        freeChars[count++] = i;
                    }
                }
                if (count == 1) {
                    GwPlayer[pads[index]].chr = freeChars[0];
                    D_8010A1B4_selmenu[freeChars[0]] = 1;
                } else {
                    pick = rand8() % count;
                    GwPlayer[pads[index]].chr = freeChars[pick];
                    D_8010A1B4_selmenu[freeChars[pick]] = 1;
                }
            }
        }
        WipeColorSet(0, 0, 0);
        WipeCreateOut(0, 20);
        D_8010A200_selmenu = 1;
        D_800D1F28_main = 0;
        for (i = 0; i < 4; i++) {
            if (CheckControllerRead(i) && (D_800CDA7C_main[i] & L_TRIG)) {
                D_800D1F28_main = 1;
                break;
            }
        }
        return;
    }
    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i) && (D_800D5558_main[i] & START_BUTTON)) {
            for (j = 0; j < 4; j++) {
                if (CheckControllerRead(j)) {
                    D_8010A270_selmenu[j] |= 0x10;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            sprintf(D_800D5218_main, "------");
            func_801089C0_selmenu(i * 56 + 56, 144, D_800D5218_main, 15, 7);
            continue;
        }
        Hu3DModelAttrSet(D_8010A1C0_selmenu[GwPlayer[i].chr], 4, 0);
        Hu3DModelPosSet(D_8010A1C0_selmenu[GwPlayer[i].chr], i * 420 - 650.0f - 60.0f + i * 40, -120.0f, 0.0f);
        Hu3DModelScaleSet(D_8010A1C0_selmenu[GwPlayer[i].chr], 2.0f, 2.0f, 2.0f);
        if (D_8010A1B0_selmenu[i] == 1) {
            D_8010A260_selmenu[i] = 0.0f;
        }
        Hu3DModelRotSet(D_8010A1C0_selmenu[GwPlayer[i].chr], 0.0f, D_8010A260_selmenu[i], 0.0f);
        D_8010A260_selmenu[i] += 1.0f;
        if (D_8010A260_selmenu[i] >= 360.0f) {
            D_8010A260_selmenu[i] -= 360.0f;
        }
        color = (D_8010A1B0_selmenu[i] != 0) ? 15 : 12;
        textColor = color;
        sprintf(D_800D5218_main, D_801097D4_selmenu[GwPlayer[i].chr]);
        func_801089C0_selmenu(i * 56 + 50 + i * 4, 144, D_800D5218_main, textColor, color - 8);
        if ((D_8010A270_selmenu[i] & 0x10) && D_8010A1B0_selmenu[i] == 0) {
            D_8010A1B0_selmenu[i] = 1;
            Hu3DMotionModelSet(D_8010A1C0_selmenu[GwPlayer[i].chr], D_8010A1E0_selmenu[GwPlayer[i].chr]);
            Hu3DMotionAttrSet(D_8010A1C0_selmenu[GwPlayer[i].chr], 1, 0);
            Hu3DMotionAttrSet(D_8010A1C0_selmenu[GwPlayer[i].chr], 2, 2);
            func_801087C8_selmenu(2);
        } else if ((D_8010A270_selmenu[i] & 0x20) && D_8010A1B0_selmenu[i] == 1) {
            D_8010A1B0_selmenu[i] = 0;
            Hu3DMotionModelSet(D_8010A1C0_selmenu[GwPlayer[i].chr], D_8010A1D0_selmenu[GwPlayer[i].chr]);
            Hu3DMotionAttrSet(D_8010A1C0_selmenu[GwPlayer[i].chr], 1, 0);
            Hu3DMotionAttrSet(D_8010A1C0_selmenu[GwPlayer[i].chr], 2, 2);
            func_801087C8_selmenu(3);
        }
        if (D_8010A1B0_selmenu[i] == 0) {
            if (D_8010A270_selmenu[i] & 4) {
                chr = GwPlayer[i].chr - 1;
                func_801087C8_selmenu(0);
                while (TRUE) {
                    if (chr < 0) {
                        chr = 7;
                    }
                    if (D_8010A1B4_selmenu[chr] == 0) {
                        break;
                    }
                    chr--;
                }
                D_8010A1B4_selmenu[GwPlayer[i].chr] = 0;
                Hu3DModelAttrSet(D_8010A1C0_selmenu[GwPlayer[i].chr], 4, 4);
                GwPlayer[i].chr = chr;
                D_8010A1B4_selmenu[GwPlayer[i].chr] = 1;
                D_8010A260_selmenu[i] = 0.0f;
            } else if (D_8010A270_selmenu[i] & 8) {
                chr = GwPlayer[i].chr + 1;
                func_801087C8_selmenu(0);
                while (TRUE) {
                    if (chr >= 8) {
                        chr = 0;
                    }
                    if (D_8010A1B4_selmenu[chr] == 0) {
                        break;
                    }
                    chr++;
                }
                D_8010A1B4_selmenu[GwPlayer[i].chr] = 0;
                Hu3DModelAttrSet(D_8010A1C0_selmenu[GwPlayer[i].chr], 4, 4);
                GwPlayer[i].chr = chr;
                D_8010A1B4_selmenu[GwPlayer[i].chr] = 1;
                D_8010A260_selmenu[i] = 0.0f;
            }
        }
    }
}

void func_801087C8_selmenu(u16 index) {
    HuAudFXVolSet(HuAudFXPlay(D_80109740_selmenu[index].fx), D_80109740_selmenu[index].vol);
}

void func_80108814_selmenu(s16 dir) {
    s16 index = D_8010A072_selmenu;

    do {
        index += dir;
        if (index >= 10) {
            index = 0;
        } else if (index < 0) {
            index = 9;
        }
    } while (D_80108C90_selmenu[D_8010A070_selmenu * 10 + index].available == 1);
    D_8010A072_selmenu = index;
}

void func_80108890_selmenu(s16 dir) {
    u16 found = FALSE;
    s16 prevPage;
    s16 page;
    s32 i;

    prevPage = page = D_8010A070_selmenu;
    do {
        page += dir;
        if (page >= 10) {
            page = 0;
        } else if (page < 0) {
            page = 9;
        }
        for (i = 0; i < 10; i++) {
            if (D_80108C90_selmenu[page * 10 + i].available == 0) {
                found = TRUE;
                break;
            }
        }
    } while (!found);
    D_8010A070_selmenu = page;
    if (prevPage == -1) {
        D_8010A072_selmenu = -1;
        func_80108814_selmenu(1);
        D_8010A078_selmenu[D_8010A070_selmenu] = D_8010A072_selmenu;
    } else {
        D_8010A078_selmenu[prevPage] = D_8010A072_selmenu;
        D_8010A072_selmenu = D_8010A078_selmenu[D_8010A070_selmenu];
    }
}

void func_801089C0_selmenu(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4) {
    fontcolor = arg4;
    print8((arg0 + 1), (arg1 + 1), arg2);
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

void func_80108A40_selmenu(void) {
    SelMenuPlayerGroups *groups = &D_801092D0_selmenu[D_80108C90_selmenu[D_8010A070_selmenu * 10 + D_8010A072_selmenu].player_groups - 1];
    GW_PLAYER *player = D_8010A098_selmenu;

    player->group = groups->group[0];
    player++;
    player->group = groups->group[1];
    player++;
    player->group = groups->group[2];
    player++;
    player->group = groups->group[3];
}

void func_80108AB4_selmenu(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        GW_PLAYER *src = &D_8010A098_selmenu[i];
        GW_PLAYER *dst = &GwPlayer[i];

        dst->stat = src->stat;
        dst->group = src->group;
        dst->pad = src->pad;
        dst->cpu_difficulty = src->cpu_difficulty;
        dst->coin = src->coin;
    }
}

void func_80108B1C_selmenu(void) {
    u8 groups[4];
    u8 used[4];
    s32 i;
    s32 r;

    for (i = 0; i < 4; i++) {
        groups[i] = D_8010A098_selmenu[i].group;
        used[i] = FALSE;
    }
    for (i = 0; i < 4; i++) {
        do {
            r = rand8() & 3;
        } while (used[r] == TRUE);
        used[r] = TRUE;
        D_8010A098_selmenu[i].group = groups[r];
    }
}

void func_80108BE8_selmenu(void) {
    u8 used[4];
    s32 i;
    s32 r;

    for (i = 0; i < 4; i++) {
        used[i] = FALSE;
    }
    for (i = 0; i < 4; i++) {
        do {
            r = rand8() & 3;
        } while (used[r] == TRUE);
        used[r] = TRUE;
        D_8010A098_selmenu[i].pad = r;
    }
}
