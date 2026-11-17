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

extern s32 omCharModelNoTbl[][6];
extern s32 omCharMotTbl[][6];
extern s16 selMenuMgModeF;
extern char selmenu_mgName300Str[];
extern char selmenu_mgName299Str[];
extern char selmenu_mgName298Str[];
extern char selmenu_mgName297Str[];
extern char selmenu_mgName296Str[];
extern char selmenu_mgName295Str[];
extern char selmenu_mgName294Str[];
extern char selmenu_mgName293Str[];
extern char selmenu_mgName292Str[];
extern char selmenu_mgName291Str[];
extern char selmenu_mgName290Str[];
extern char selmenu_mgName289Str[];
extern char selmenu_mgName288Str[];
extern char selmenu_mgName287Str[];
extern char selmenu_mgName286Str[];
extern char selmenu_mgName285Str[];
extern char selmenu_mgName284Str[];
extern char selmenu_mgName283Str[];
extern char selmenu_mgName282Str[];
extern char selmenu_mgName281Str[];
extern char selmenu_mgName280Str[];
extern char selmenu_mgName279Str[];
extern char selmenu_mgName278Str[];
extern char selmenu_mgName277Str[];
extern char selmenu_mgName276Str[];
extern char selmenu_mgName275Str[];
extern char selmenu_mgName274Str[];
extern char selmenu_mgName273Str[];
extern char selmenu_mgName272Str[];
extern char selmenu_mgName271Str[];
extern char selmenu_mgName270Str[];
extern char selmenu_mgName269Str[];
extern char selmenu_mgName268Str[];
extern char selmenu_mgName267Str[];
extern char selmenu_mgName266Str[];
extern char selmenu_mgName265Str[];
extern char selmenu_mgName264Str[];
extern char selmenu_mgName263Str[];
extern char selmenu_mgName262Str[];
extern char selmenu_mgName261Str[];
extern char selmenu_mgName260Str[];
extern char selmenu_mgName259Str[];
extern char selmenu_mgName258Str[];
extern char selmenu_mgName257Str[];
extern char selmenu_mgName256Str[];
extern char selmenu_mgName255Str[];
extern char selmenu_mgName254Str[];
extern char selmenu_mgName253Str[];
extern char selmenu_mgName252Str[];
extern char selmenu_mgName251Str[];
extern char selmenu_mgName250Str[];
extern char selmenu_mgName249Str[];
extern char selmenu_mgName248Str[];
extern char selmenu_mgName247Str[];
extern char selmenu_mgName246Str[];
extern char selmenu_mgName245Str[];
extern char selmenu_mgName244Str[];
extern char selmenu_mgName243Str[];
extern char selmenu_mgName242Str[];
extern char selmenu_mgName241Str[];
extern char selmenu_mgName240Str[];
extern char selmenu_mgName239Str[];
extern char selmenu_mgName238Str[];
extern char selmenu_mgName237Str[];
extern char selmenu_mgName236Str[];
extern char selmenu_mgName235Str[];
extern char selmenu_mgName234Str[];
extern char selmenu_mgName233Str[];
extern char selmenu_mgName232Str[];
extern char selmenu_mgName231Str[];
extern char selmenu_mgName230Str[];
extern char selmenu_mgName229Str[];
extern char selmenu_mgName228Str[];
extern char selmenu_mgName227Str[];
extern char selmenu_mgName226Str[];
extern char selmenu_mgName225Str[];
extern char selmenu_mgName224Str[];
extern char selmenu_mgName223Str[];
extern char selmenu_mgName222Str[];
extern char selmenu_mgName221Str[];
extern char selmenu_mgName220Str[];
extern char selmenu_mgName219Str[];
extern char selmenu_mgName218Str[];
extern char selmenu_mgName217Str[];
extern char selmenu_mgName216Str[];
extern char selmenu_mgName215Str[];
extern char selmenu_mgName214Str[];
extern char selmenu_mgName213Str[];
extern char selmenu_mgName212Str[];
extern char selmenu_mgName211Str[];
extern char selmenu_mgName210Str[];
extern char selmenu_mgName209Str[];
extern char selmenu_mgName208Str[];
extern char selmenu_mgName207Str[];
extern char selmenu_mgName206Str[];
extern char selmenu_mgName205Str[];
extern char selmenu_mgName204Str[];
extern char selmenu_mgName203Str[];
extern char selmenu_mgName202Str[];
extern char selmenu_mgName201Str[];
extern char selmenu_padNoFmtStr[];
extern char selmenu_coinFmtStr[];
extern char selmenu_comLevelFmtStr[];
extern char selmenu_groupFmtStr[];
extern char selmenu_padFmtStr[];
extern char selmenu_playerFmtStr[];
extern char selmenu_comStr[];
extern char selmenu_humanStr[];
extern char selmenu_veryHardStr[];
extern char selmenu_hardStr[];
extern char selmenu_normalStr[];
extern char selmenu_easyStr[];
extern char selmenu_daisyStr[];
extern char selmenu_waluigiStr[];
extern char selmenu_donkeyStr[];
extern char selmenu_warioStr[];
extern char selmenu_yoshiStr[];
extern char selmenu_peachStr[];
extern char selmenu_luigiStr[];
extern char selmenu_marioStr[];
extern char selmenu_duelStr[];
extern char selmenu_boardStr[];
extern char selmenu_gameStr[];
extern char selmenu_pageFmtStr[];
extern char selmenu_modeFmtStr[];

SelMenuConfig selmenu_menuTbl[100] = {
    { 0, 1, 11, 0, 1, 100, 0, selmenu_mgName201Str },     /* "201:PUKUPUKU FISHING" */
    { 0, 2, 11, 0, 2, 100, 0, selmenu_mgName202Str },     /* "202:HIYAHIYA YASHINOMI" */
    { 0, 3, 11, 0, 3, 100, 0, selmenu_mgName203Str },     /* "203:TERASHITE SEARCH LIGHT" */
    { 0, 4, 11, 0, 4, 100, 0, selmenu_mgName204Str },     /* "204:GOROGORO IWAKOROGASHI" */
    { 0, 5, 11, 0, 5, 100, 0, selmenu_mgName205Str },     /* "205:BOMHEI KOUKATAI" */
    { 0, 6, 11, 0, 6, 100, 0, selmenu_mgName206Str },     /* "206:DOKO?DOKO? KAKURENBO" */
    { 0, 7, 11, 0, 7, 100, 0, selmenu_mgName207Str },     /* "207:DOTABATA RELAY" */
    { 0, 8, 11, 0, 8, 100, 0, selmenu_mgName208Str },     /* "208:ISOGE WANWAN" */
    { 0, 9, 11, 0, 9, 100, 0, selmenu_mgName209Str },     /* "209:SUIJYOU SKI" */
    { 0, 10, 11, 0, 10, 100, 0, selmenu_mgName210Str },   /* "210:WAVE*WAVE" */
    { 0, 11, 11, 0, 11, 100, 0, selmenu_mgName211Str },   /* "211:MOGOMOGU PIZZA HOUSE" */
    { 0, 12, 11, 0, 12, 100, 0, selmenu_mgName212Str },   /* "212:ATECHAE! MINI KOOPA" */
    { 0, 13, 11, 0, 13, 100, 0, selmenu_mgName213Str },   /* "213:GO!GO! ROCKET" */
    { 0, 14, 11, 0, 14, 100, 0, selmenu_mgName214Str },   /* "214:BOBBLE HINO YOUJIN!" */
    { 0, 15, 11, 0, 15, 100, 0, selmenu_mgName215Str },   /* "215:BURABURA BURANKO" */
    { 0, 16, 11, 0, 16, 100, 0, selmenu_mgName216Str },   /* "216:TRUCK KIKI IPPATSU" */
    { 0, 17, 11, 0, 17, 100, 0, selmenu_mgName217Str },   /* "217:PIT RACE" */
    { 0, 18, 11, 0, 18, 100, 0, selmenu_mgName218Str },   /* "218:KAKONDE KUREYON" */
    { 0, 19, 11, 0, 19, 100, 0, selmenu_mgName219Str },   /* "219:MAKIWARI" */
    { 0, 20, 11, 0, 20, 100, 0, selmenu_mgName220Str },   /* "220:NUIGURUMI FACTORY" */
    { 0, 21, 11, 0, 21, 100, 0, selmenu_mgName221Str },   /* "221:BELCON DANGEROUS" */
    { 0, 22, 11, 0, 22, 100, 0, selmenu_mgName222Str },   /* "222:POWER KINOKO GO!GO!" */
    { 0, 23, 11, 0, 23, 100, 0, selmenu_mgName223Str },   /* "223:TIKITIKI AIR FIGHT!" */
    { 0, 24, 11, 0, 24, 100, 0, selmenu_mgName224Str },   /* "224:PYONPYON BATTLE!" */
    { 0, 25, 11, 0, 25, 100, 0, selmenu_mgName225Str },   /* "225:NOKONOKO ISLAND" */
    { 0, 26, 11, 0, 26, 100, 0, selmenu_mgName226Str },   /* "226:NIGEKOME SHELTER" */
    { 0, 27, 11, 0, 27, 100, 0, selmenu_mgName227Str },   /* "227:PITTARI! PATTER" */
    { 0, 28, 11, 0, 28, 100, 0, selmenu_mgName228Str },   /* "228:OKKOTI PARASOL" */
    { 0, 29, 11, 0, 29, 100, 0, selmenu_mgName229Str },   /* "229:MATIGAI WO SAGSE!" */
    { 0, 30, 11, 0, 30, 100, 0, selmenu_mgName230Str },   /* "230:OWASETE MONTAGE" */
    { 0, 31, 11, 0, 31, 100, 0, selmenu_mgName231Str },   /* "231:DOSSUN PUZZLE" */
    { 0, 32, 11, 0, 32, 100, 0, selmenu_mgName232Str },   /* "232:TATAITE DRUM" */
    { 0, 33, 11, 0, 33, 100, 0, selmenu_mgName233Str },   /* "233:QUIZ PARTY" */
    { 0, 34, 11, 0, 34, 100, 0, selmenu_mgName234Str },   /* "234:ATEKKO CHARACTER" */
    { 0, 35, 11, 0, 35, 100, 0, selmenu_mgName235Str },   /* "235:MOTORBOAT RACE" */
    { 0, 36, 11, 0, 36, 100, 0, selmenu_mgName236Str },   /* "236:KUNEKUNE ROAD RACE" */
    { 0, 37, 11, 0, 37, 100, 0, selmenu_mgName237Str },   /* "237:AOZORA BLOCK RACE" */
    { 0, 38, 11, 0, 38, 100, 0, selmenu_mgName238Str },   /* "238:BATAASHI RACE" */
    { 0, 39, 11, 0, 39, 100, 0, selmenu_mgName239Str },   /* "239:TATAKE! MINI KOOPA" */
    { 0, 40, 11, 0, 40, 100, 0, selmenu_mgName240Str },   /* "240:YUKIDAMA GOROGORO!" */
    { 0, 41, 11, 0, 41, 100, 0, selmenu_mgName241Str },   /* "241:KAWASHITE BOBBLE" */
    { 0, 42, 11, 0, 42, 100, 0, selmenu_mgName242Str },   /* "242:CAPSULE MINI KOOPA" */
    { 0, 43, 11, 0, 43, 100, 0, selmenu_mgName243Str },   /* "243:HAYAOSHI HOUSE" */
    { 0, 44, 11, 0, 44, 100, 0, selmenu_mgName244Str },   /* "244:MOKUBA RACE" */
    { 0, 45, 11, 0, 45, 100, 0, selmenu_mgName245Str },   /* "245:DANGEROUS ROULETTE" */
    { 0, 46, 11, 0, 46, 100, 0, selmenu_mgName246Str },   /* "246:MEKUTTE HAYAOSHI!" */
    { 0, 47, 11, 0, 47, 100, 0, selmenu_mgName247Str },   /* "247:AMEHURI FLOWER" */
    { 0, 48, 11, 0, 48, 100, 0, selmenu_mgName248Str },   /* "248:AIKUN MAWASHI" */
    { 0, 49, 11, 0, 49, 100, 0, selmenu_mgName249Str },   /* "249:TARZAN RACE" */
    { 0, 50, 11, 0, 50, 100, 0, selmenu_mgName250Str },   /* "250:HIRAITA GATE NI PON!" */
    { 0, 51, 11, 0, 51, 100, 0, selmenu_mgName251Str },   /* "251:BOUSOU!? SHUPPO-" */
    { 0, 52, 11, 0, 52, 100, 0, selmenu_mgName252Str },   /* "252:TONDEKE KOOPA HAMMER" */
    { 0, 53, 11, 0, 53, 100, 0, selmenu_mgName253Str },   /* "253:ITAZURA MINI KOOPA" */
    { 0, 54, 11, 0, 54, 100, 0, selmenu_mgName254Str },   /* "254:TUBE COASTER" */
    { 0, 55, 11, 0, 55, 100, 0, selmenu_mgName255Str },   /* "255:BOLT DASH" */
    { 0, 56, 11, 0, 56, 100, 0, selmenu_mgName256Str },   /* "256:KONO E HA NAANI?" */
    { 0, 57, 11, 0, 57, 100, 0, selmenu_mgName257Str },   /* "257:JUMP DE CLOCK" */
    { 0, 58, 11, 0, 58, 100, 0, selmenu_mgName258Str },   /* "258:KIGURUMI KOOPA" */
    { 0, 59, 11, 0, 59, 100, 0, selmenu_mgName259Str },   /* "259:NERAE! ITEM!!" */
    { 0, 60, 11, 0, 60, 100, 0, selmenu_mgName260Str },   /* "260:ITEM HITTER" */
    { 0, 61, 11, 0, 61, 100, 0, selmenu_mgName261Str },   /* "261:NERATTE BALOON" */
    { 0, 62, 11, 0, 62, 100, 0, selmenu_mgName262Str },   /* "262:DOSSHI DE CATCH!" */
    { 0, 63, 11, 0, 63, 100, 0, selmenu_mgName263Str },   /* "263:BURABURA BURANKO" */
    { 0, 64, 11, 0, 64, 100, 0, selmenu_mgName264Str },   /* "264:ITEM THROWIN" */
    { 1, 65, 11, 0, 1000, 100, 0, selmenu_mgName265Str }, /* "265:" */
    { 0, 66, 11, 0, 65, 100, 0, selmenu_mgName266Str },   /* "266:STARDUST BATTLE" */
    { 0, 67, 11, 0, 66, 100, 0, selmenu_mgName267Str },   /* "267:HEIHO ROULETTE" */
    { 0, 68, 11, 0, 67, 100, 0, selmenu_mgName268Str },   /* "268:OTITARA DAMEYO" */
    { 0, 69, 11, 0, 68, 100, 0, selmenu_mgName269Str },   /* "269:KINOPIO?KOOPA?" */
    { 0, 70, 11, 0, 69, 100, 0, selmenu_mgName270Str },   /* "270:WANWAN BATTLE" */
    { 0, 71, 11, 0, 70, 100, 0, selmenu_mgName271Str },   /* "271:MOTORBOAT TRIAL" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName272Str },  /* "272:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName273Str },  /* "273:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName274Str },  /* "274:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName275Str },  /* "275:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName276Str },  /* "276:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName277Str },  /* "277:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName278Str },  /* "278:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName279Str },  /* "279:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName280Str },  /* "280:" */
    { 0, 1, 11, 0, 91, 100, 0, selmenu_mgName281Str },    /* "281:DUEL01" */
    { 0, 1, 11, 0, 92, 100, 0, selmenu_mgName282Str },    /* "282:DULE02" */
    { 0, 1, 11, 0, 93, 100, 0, selmenu_mgName283Str },    /* "283:DUEL03" */
    { 0, 1, 11, 0, 94, 100, 0, selmenu_mgName284Str },    /* "284:DUEL04" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName285Str },  /* "285:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName286Str },  /* "286:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName287Str },  /* "287:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName288Str },  /* "288:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName289Str },  /* "289:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName290Str },  /* "290:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName291Str },  /* "291:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName292Str },  /* "292:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu_mgName293Str },  /* "293:" */
    { 0, 1, 11, 0, 115, 100, 0, selmenu_mgName294Str },   /* "294:RESULT3" */
    { 0, 1, 11, 0, 106, 100, 0, selmenu_mgName295Str },   /* "295:CHANCE" */
    { 0, 1, 11, 0, 114, 100, 0, selmenu_mgName296Str },   /* "296:RESULT2" */
    { 0, 1, 11, 0, 112, 100, 0, selmenu_mgName297Str },   /* "297:INST" */
    { 0, 1, 11, 0, 113, 100, 0, selmenu_mgName298Str },   /* "298:RESULT" */
    { 0, 1, 11, 0, 126, 100, 0, selmenu_mgName299Str },   /* "299:SAMPLE" */
    { 0, 1, 11, 0, 86, 100, 0, selmenu_mgName300Str },    /* "300*MCHAR" */
};

SelMenuPlayerGroups selmenu_playerGroupTbl[] = {
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

SelMenuSound selmenu_seTbl[] = {
    { 1, 0, 0x78 },
    { 9, 0, 0x6A },
    { 2, 0, 0x6E },
    { 4, 0, 0x72 },
    { 76, 0, 0x7B },
};

u16 selmenu_textColorTbl[2][2] = { { 5, 13 }, { 4, 12 } }; // text colors

SelMenuConfig selmenu_playerCfgMenuTbl[] = {
    { 1, 3, 11, 0, 1000, 0, 0, selmenu_playerFmtStr }, /* ">PLAYER%d" */
    { 0, 4, 12, 0, 1000, 0, 0, selmenu_padFmtStr }, /* "PAD%d:%s" */
    { 0, 4, 12, 0, 1000, 0, 0, selmenu_groupFmtStr }, /* "GRP :%d" */
    { 0, 4, 12, 0, 1000, 0, 0, selmenu_comLevelFmtStr }, /* "DIF :%s" */
    { 0, 4, 12, 0, 1000, 0, 0, selmenu_coinFmtStr }, /* "COIN:%d" */
    { 0, 4, 12, 0, 1000, 0, 0, selmenu_padNoFmtStr }, /* "PADN:%d" */
};

char *selmenu_padCfgStrTbl[] = { selmenu_humanStr, selmenu_comStr };

char *selmenu_comLevelStrTbl[] = { selmenu_easyStr, selmenu_normalStr, selmenu_hardStr, selmenu_veryHardStr };

char *selmenu_chrNameTbl[] = { selmenu_marioStr, selmenu_luigiStr, selmenu_peachStr, selmenu_yoshiStr, selmenu_warioStr, selmenu_donkeyStr, selmenu_waluigiStr, selmenu_daisyStr };

char *selmenu_playModeStrTbl[] = { selmenu_gameStr, selmenu_boardStr, selmenu_duelStr };

u8 selmenu_decideF = 0;
char *selmenu_comLevelUnusedStrTbl[] = { selmenu_easyStr, selmenu_normalStr, selmenu_hardStr }; /* Unreferenced. */
s32 selmenu_mgNameRiseOfs = 0;
s32 selmenu_sparkNum = 0;
s32 selmenu_sparkTimer = 1;

s16 selmenu_page BSS;
s16 selmenu_selectPos BSS;
u8 selmenu_pagePad[4] BSS; /* Unreferenced. */
s16 selmenu_selectPosBackupTbl[10] BSS;
s16 selmenu_playerCfgOptionPos BSS;
s16 selmenu_playerCfgPlayerPos BSS;
s16 selmenu_playerCfgSelF BSS;
u8 selmenu_playerCfgPad[4] BSS; /* Unreferenced. */
GW_PLAYER selmenu_playerCfg[4] BSS;
u8 selmenu_playerCfgTailPad[0x38] BSS; /* Unreferenced. */
u8 selmenu_playerDoneF[4] BSS;
u8 selmenu_chrUsedF[8] BSS;
u8 selmenu_chrPad[4] BSS; /* Unreferenced. */
s16 selmenu_chrMdlTbl[8] BSS;
s16 selmenu_chrIdleMotTbl[8] BSS;
s16 selmenu_chrDecideMotTbl[8] BSS;
s16 selmenu_playerChrTbl[4] BSS;
s8 selmenu_stickXPrev[4] BSS;
s8 selmenu_stickYPrev[4] BSS;
u8 selmenu_exitF BSS;
s16 selmenu_bgAnim BSS;
s16 selmenu_cursorAnim BSS;
u16 selmenu_cursorSpr BSS;
s16 selmenu_sparkAnim BSS;
u8 selmenu_sparkPad[4] BSS; /* Unreferenced. */
s16 selmenu_sparkSprTbl[40] BSS;
f32 selmenu_chrRotYTbl[4] BSS;
u8 selmenu_btnDownTbl[4] BSS;
u16 selmenu_btnHoldDirTbl[4] BSS;
u16 selmenu_btnHoldCntTbl[4] BSS;
u16 selmenu_btnRepeatTimerTbl[4] BSS;

void selmenu_CameraSet(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);
void selmenu_BtnCalcObjMain(omObjData *obj);
void selmenu_MenuObjInit(omObjData *obj);
void selmenu_MenuObjMain(omObjData *obj);
void selmenu_PlayerCfgObjMain(omObjData *obj);
void selmenu_MgNameRiseObjMain(omObjData *obj);
void selmenu_ChrSelObjInit(omObjData *obj);
void selmenu_ChrSelObjMain(omObjData *obj);
void selmenu_SePlay(u16 index);
void selmenu_CursorMove(s16 dir);
void selmenu_ShadowTextPrint(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4);
void selmenu_PageMove(s16 dir);
void selmenu_PlayerGroupSet(void);
void selmenu_PlayerCfgCopy(void);
void selmenu_GroupShuffle(void);
void selmenu_PadShuffle(void);

void selmenu_ObjectSetup(void) {
    omObjData *obj;
    u16 sprite;
    s32 i;

    selmenu_exitF = 0;
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
    selmenu_CameraSet(2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightMaxSet(1);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightColorSet(1, 0x60, 0x60, 0x10);
    Hu3DGLightDirSet(1, 100.0f, -100.0f, 100.0f);
    omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omAddObj(0, 0, 0, -1, selmenu_BtnCalcObjMain);
    omAddObj(1, 0, 0, -1, selmenu_MenuObjInit);
    omMakeGroup(0, 32);
    obj = omAddObj(10, 1, 80, -1, NULL);
    for (i = 0; i < 8; i++) {
        selmenu_chrMdlTbl[i] = Hu3DModelRead(omCharModelNoTbl[i][0] | omCharMotTbl[i][0], 0x69D);
        Hu3DData[selmenu_chrMdlTbl[i]].motAttr |= 2;
        omObjMotionRead(obj, 0, CharMotionDataNumGet(i, 0));
        selmenu_chrIdleMotTbl[i] = obj->motion[0];
        omObjMotionRead(obj, 1, CharMotionDataNumGet(i, 0x2F));
        selmenu_chrDecideMotTbl[i] = obj->motion[1];
    }
    omDelObj(obj);
    for (i = 0; i < 4; i++) {
        selmenu_stickYPrev[i] = 0;
        selmenu_stickXPrev[i] = 0;
    }
    selmenu_bgAnim = HuSprAnimDataRead(0x10020);
    espPalColorSet(selmenu_bgAnim, 0.3f, 0.3f, 0.3f);
    for (i = 0; i < 35; i++) {
        sprite = espEntry(selmenu_bgAnim, i % 6, 1);
        espDispOn(sprite);
        espPriSet(sprite, 0xFFFF);
        espAttrSet(sprite, HUSPR_ATTR_BG);
        espTPLvlSet(sprite, 0xFF);
        espPosSet(sprite, (i % 7) * 48, (i / 7) * 48);
    }
    selmenu_cursorAnim = HuSprAnimDataRead(10);
    selmenu_cursorSpr = espEntry(selmenu_cursorAnim, 0, 1);
    espDispOn(selmenu_cursorSpr);
    espPosSet(selmenu_cursorSpr, 0x80, 0x80);
    espScaleSet(selmenu_cursorSpr, 0.25f, 0.25f);
    for (i = 0; i < 40; i++) {
        selmenu_sparkSprTbl[i] = -1;
    }
    selmenu_sparkAnim = HuSprAnimDataRead(12);
    for (i = 0; i < 4; i++) {
        selmenu_btnHoldCntTbl[i] = 0;
        selmenu_btnRepeatTimerTbl[i] = 0;
        selmenu_btnHoldDirTbl[i] = 0;
    }
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    HuAudSeqPlay(rand8() % 9);
}

void selmenu_CameraSet(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    CamSetupInit(1);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
}

void selmenu_BtnCalcObjMain(omObjData *obj) {
    s8 stickX;
    s8 stickY;
    s32 i;

    for (i = 0; i < 4; i++) {
        selmenu_btnDownTbl[i] = 0;
        if (!CheckControllerRead(i)) {
            continue;
        }
        if (WipeStatGet() == 1) {
            continue;
        }
        stickX = HuPadStkX[i];
        stickY = HuPadStkY[i];
        if (HuPadBtnDown[i] & (U_JPAD | U_CBUTTONS)) {
            selmenu_btnDownTbl[i] |= 1;
        }
        if (HuPadBtnDown[i] & (D_JPAD | D_CBUTTONS)) {
            selmenu_btnDownTbl[i] |= 2;
        }
        if (HuPadBtnDown[i] & (L_JPAD | L_CBUTTONS)) {
            selmenu_btnDownTbl[i] |= 4;
        }
        if (HuPadBtnDown[i] & (R_JPAD | R_CBUTTONS)) {
            selmenu_btnDownTbl[i] |= 8;
        }
        if (stickY < -10 && ABS(selmenu_stickYPrev[i]) < 10) {
            selmenu_btnDownTbl[i] |= 2;
        }
        if (stickY > 10 && ABS(selmenu_stickYPrev[i]) < 10) {
            selmenu_btnDownTbl[i] |= 1;
        }
        if (stickX < -10 && ABS(selmenu_stickXPrev[i]) < 10) {
            selmenu_btnDownTbl[i] |= 4;
        }
        if (stickX > 10 && ABS(selmenu_stickXPrev[i]) < 10) {
            selmenu_btnDownTbl[i] |= 8;
        }
        selmenu_stickXPrev[i] = stickX;
        selmenu_stickYPrev[i] = stickY;
        if (HuPadBtnDown[i] & Z_TRIG) {
            selmenu_btnDownTbl[i] |= 0x40;
        }
        if ((HuPadBtn[i] & (U_JPAD | U_CBUTTONS)) || stickY > 10) {
            if (selmenu_btnHoldDirTbl[i] & 1) {
                selmenu_btnHoldCntTbl[i]++;
                if (selmenu_btnHoldCntTbl[i] >= 16) {
                    selmenu_btnHoldCntTbl[i] = 15;
                }
            } else {
                selmenu_btnHoldCntTbl[i] = 0;
            }
            if (selmenu_btnHoldDirTbl[i] != 1) {
                selmenu_btnRepeatTimerTbl[i] = 0;
                selmenu_btnHoldCntTbl[i] = 0;
            }
            selmenu_btnHoldDirTbl[i] = 1;
            if (selmenu_btnHoldCntTbl[i] == 15) {
                if (selmenu_btnRepeatTimerTbl[i] == 0) {
                    selmenu_btnDownTbl[i] |= 1;
                    selmenu_btnRepeatTimerTbl[i] = 2;
                } else {
                    selmenu_btnRepeatTimerTbl[i]--;
                }
            }
        } else if ((HuPadBtn[i] & (D_JPAD | D_CBUTTONS)) || stickY < -10) {
            if (selmenu_btnHoldDirTbl[i] & 2) {
                selmenu_btnHoldCntTbl[i]++;
                if (selmenu_btnHoldCntTbl[i] >= 16) {
                    selmenu_btnHoldCntTbl[i] = 15;
                }
            } else {
                selmenu_btnHoldCntTbl[i] = 0;
            }
            if (selmenu_btnHoldDirTbl[i] != 2) {
                selmenu_btnRepeatTimerTbl[i] = 0;
                selmenu_btnHoldCntTbl[i] = 0;
            }
            selmenu_btnHoldDirTbl[i] = 2;
            if (selmenu_btnHoldCntTbl[i] == 15) {
                if (selmenu_btnRepeatTimerTbl[i] == 0) {
                    selmenu_btnDownTbl[i] |= 2;
                    selmenu_btnRepeatTimerTbl[i] = 2;
                } else {
                    selmenu_btnRepeatTimerTbl[i]--;
                }
            }
        } else if ((HuPadBtn[i] & (L_JPAD | L_CBUTTONS)) || stickX < -10) {
            if (selmenu_btnHoldDirTbl[i] & 4) {
                selmenu_btnHoldCntTbl[i]++;
                if (selmenu_btnHoldCntTbl[i] >= 16) {
                    selmenu_btnHoldCntTbl[i] = 15;
                }
            } else {
                selmenu_btnHoldCntTbl[i] = 0;
            }
            if (selmenu_btnHoldDirTbl[i] != 4) {
                selmenu_btnRepeatTimerTbl[i] = 0;
                selmenu_btnHoldCntTbl[i] = 0;
            }
            selmenu_btnHoldDirTbl[i] = 4;
            if (selmenu_btnHoldCntTbl[i] == 15) {
                if (selmenu_btnRepeatTimerTbl[i] == 0) {
                    selmenu_btnDownTbl[i] |= 4;
                    selmenu_btnRepeatTimerTbl[i] = 2;
                } else {
                    selmenu_btnRepeatTimerTbl[i]--;
                }
            }
        } else if ((HuPadBtn[i] & (R_JPAD | R_CBUTTONS)) || stickX > 10) {
            if (selmenu_btnHoldDirTbl[i] & 8) {
                selmenu_btnHoldCntTbl[i]++;
                if (selmenu_btnHoldCntTbl[i] >= 16) {
                    selmenu_btnHoldCntTbl[i] = 15;
                }
            } else {
                selmenu_btnHoldCntTbl[i] = 0;
            }
            if (selmenu_btnHoldDirTbl[i] != 8) {
                selmenu_btnRepeatTimerTbl[i] = 0;
                selmenu_btnHoldCntTbl[i] = 0;
            }
            selmenu_btnHoldDirTbl[i] = 8;
            if (selmenu_btnHoldCntTbl[i] == 15) {
                if (selmenu_btnRepeatTimerTbl[i] == 0) {
                    selmenu_btnDownTbl[i] |= 8;
                    selmenu_btnRepeatTimerTbl[i] = 2;
                } else {
                    selmenu_btnRepeatTimerTbl[i]--;
                }
            }
        } else {
            selmenu_btnHoldCntTbl[i] = 0;
        }
        if (HuPadBtnDown[i] & A_BUTTON) {
            selmenu_btnDownTbl[i] |= 0x10;
        }
        if (HuPadBtnDown[i] & B_BUTTON) {
            selmenu_btnDownTbl[i] |= 0x20;
        }
        if (HuPadBtnDown[i] & START_BUTTON) {
            selmenu_btnDownTbl[i] |= 0x80;
        }
        if ((HuPadBtn[i] & (L_TRIG | R_TRIG)) == (L_TRIG | R_TRIG)) {
            omOvlReturnEx(0);
            return;
        }
    }
}

void selmenu_MenuObjInit(omObjData *obj) {
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        selmenu_chrUsedF[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].chr = i;
        selmenu_playerChrTbl[i] = i;
        selmenu_playerDoneF[i] = 0;
        selmenu_chrRotYTbl[i] = 0.0f;
    }
    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            selmenu_chrUsedF[i] = 1;
        }
    }
    selmenu_page = -1;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (selmenu_menuTbl[i * 10 + j].available != 1) {
                break;
            }
        }
        if (j == 10) {
            selmenu_selectPosBackupTbl[i] = -1;
        } else {
            selmenu_selectPosBackupTbl[i] = j;
        }
    }
    selmenu_PageMove(1);
    if (omprevovl != 999) {
        for (i = 0; i < 100; i++) {
            if (selmenu_menuTbl[i].unk_04 == omprevovl) {
                selmenu_page = i / 10;
                selmenu_selectPos = i % 10;
                selmenu_selectPosBackupTbl[selmenu_page] = selmenu_selectPos;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        selmenu_playerCfg[i] = GwPlayer[i];
    }
    selmenu_PlayerGroupSet();
    obj->func = selmenu_MenuObjMain;
}

void selmenu_MenuObjMain(omObjData *obj) {
    SelMenuConfig *config;
    u16 *color;
    s32 x;
    s32 i;

    rand8();
    config = &selmenu_menuTbl[selmenu_page * 10];
    for (i = 0; i < 10; i++, config++) {
        sprintf(omDBGStrBuf, config->name);
        // The strlen result is discarded; x is overwritten with a fixed position.
        x = strlen(omDBGStrBuf);
        x = 0x40;
        if (selmenu_menuTbl[selmenu_page * 10 + i].available == 0) {
            color = selmenu_textColorTbl[0];
        } else {
            color = selmenu_textColorTbl[1];
        }
        if (selmenu_selectPos == i) {
            selmenu_ShadowTextPrint(x, (i + 10) * 9, omDBGStrBuf, color[1], color[0]);
        } else {
            selmenu_ShadowTextPrint(x, (i + 10) * 9, omDBGStrBuf, color[0], 0);
        }
    }
    sprintf(omDBGStrBuf, selmenu_pageFmtStr, selmenu_page + 1, 10);
    selmenu_ShadowTextPrint(0x80, 0x40, omDBGStrBuf, 15, 7);
    sprintf(omDBGStrBuf, selmenu_modeFmtStr, selmenu_playModeStrTbl[omDBGPlayMode]);
    selmenu_ShadowTextPrint(0x80, 0x48, omDBGStrBuf, 14, 6);
    espPosSet(selmenu_cursorSpr, 0x3C, (selmenu_selectPos + 11) * 9 - 1);
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        if ((selmenu_btnDownTbl[i] & 0x90) && selmenu_menuTbl[selmenu_page * 10 + selmenu_selectPos].available == 0) {
            if (selmenu_decideF == 0) {
                omAddObj(2, 0, 0, -1, selmenu_ChrSelObjInit);
                selmenu_decideF = 1;
                espDispOff(selmenu_cursorSpr);
                obj->func = selmenu_MgNameRiseObjMain;
                selmenu_SePlay(1);
            }
        } else if (selmenu_btnDownTbl[i] & 1) {
            selmenu_CursorMove(-1);
            selmenu_PlayerGroupSet();
            selmenu_SePlay(0);
        } else if (selmenu_btnDownTbl[i] & 2) {
            selmenu_CursorMove(1);
            selmenu_PlayerGroupSet();
            selmenu_SePlay(0);
        } else if (selmenu_btnDownTbl[i] & 4) {
            selmenu_PageMove(-1);
            selmenu_PlayerGroupSet();
            selmenu_SePlay(4);
        } else if (selmenu_btnDownTbl[i] & 8) {
            selmenu_PageMove(1);
            selmenu_PlayerGroupSet();
            selmenu_SePlay(4);
        } else if (selmenu_btnDownTbl[i] & 0x40) {
            selmenu_playerCfgOptionPos = 0;
            selmenu_playerCfgPlayerPos = 0;
            selmenu_playerCfgSelF = 0;
            obj->func = selmenu_PlayerCfgObjMain;
        } else if (HuPadBtnDown[i] & R_TRIG) {
            if (++omDBGPlayMode >= 3) {
                omDBGPlayMode = 0;
            }
        }
    }
}

void selmenu_PlayerCfgObjMain(omObjData *obj) {
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
    sprintf(omDBGStrBuf, "* OPTION *");
    selmenu_ShadowTextPrint(0x70, 0x40, omDBGStrBuf, 15, 7);
    for (i = 0; i < 5; i++) {
        space = selmenu_playerCfgMenuTbl;
        if (i == 4) {
            sprintf(omDBGStrBuf, "MAP:%d", GwSystem.current_board_index);
            color = selmenu_textColorTbl[0];
            if (selmenu_playerCfgPlayerPos == i) {
                selmenu_ShadowTextPrint(0x80, 0x50, omDBGStrBuf, color[1], color[0]);
            } else {
                selmenu_ShadowTextPrint(0x80, 0x50, omDBGStrBuf, color[0], 0);
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
                    sprintf(omDBGStrBuf, space->name, i);
                    break;
                case 1:
                    sprintf(omDBGStrBuf, space->name, selmenu_playerCfg[i].pad,
                            selmenu_padCfgStrTbl[selmenu_playerCfg[i].stat & 1]);
                    break;
                case 2:
                    sprintf(omDBGStrBuf, space->name, selmenu_playerCfg[i].group);
                    break;
                case 3:
                    sprintf(omDBGStrBuf, space->name, selmenu_comLevelStrTbl[selmenu_playerCfg[i].cpu_difficulty]);
                    break;
                case 4:
                    sprintf(omDBGStrBuf, space->name, selmenu_playerCfg[i].coin);
                    break;
                case 5:
                    sprintf(omDBGStrBuf, space->name, selmenu_playerCfg[i].pad);
                    break;
            }
            switch (selmenu_playerCfgSelF) {
                case 0:
                    if (j == 0) {
                        color = selmenu_textColorTbl[0];
                        if (i == selmenu_playerCfgPlayerPos) {
                            selmenu_ShadowTextPrint(x, y, omDBGStrBuf, color[1], color[0]);
                        } else {
                            selmenu_ShadowTextPrint(x, y, omDBGStrBuf, color[0], 0);
                        }
                    } else {
                        selmenu_ShadowTextPrint(x, y, omDBGStrBuf, selmenu_textColorTbl[1][0], 0);
                    }
                    break;
                case 1:
                    if (i == selmenu_playerCfgPlayerPos) {
                        color = selmenu_textColorTbl[0];
                        if (j == selmenu_playerCfgOptionPos) {
                            selmenu_ShadowTextPrint(x, y, omDBGStrBuf, color[1], color[0]);
                        } else {
                            selmenu_ShadowTextPrint(x, y, omDBGStrBuf, color[0], 0);
                        }
                    } else {
                        selmenu_ShadowTextPrint(x, y, omDBGStrBuf, selmenu_textColorTbl[1][0], 0);
                    }
                    break;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        if (selmenu_btnDownTbl[i] & 0x40) {
            obj->func = selmenu_MenuObjMain;
            return;
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        switch (selmenu_playerCfgSelF) {
            case 0:
                if (selmenu_playerCfgPlayerPos < 2 && (selmenu_btnDownTbl[i] & 1)) {
                    selmenu_playerCfgPlayerPos = 4;
                } else if (selmenu_playerCfgPlayerPos == 4 && (selmenu_btnDownTbl[i] & 2)) {
                    selmenu_playerCfgPlayerPos = 0;
                } else if (selmenu_playerCfgPlayerPos == 4 && (selmenu_btnDownTbl[i] & 4)) {
                    if (--GwSystem.current_board_index < 0) {
                        GwSystem.current_board_index = 0;
                    }
                } else if (selmenu_playerCfgPlayerPos == 4 && (selmenu_btnDownTbl[i] & 8)) {
                    if (++GwSystem.current_board_index > 0) {
                        GwSystem.current_board_index = 0;
                    }
                } else if (selmenu_playerCfgPlayerPos != 4) {
                    if (selmenu_btnDownTbl[i] & 0xC) {
                        selmenu_playerCfgPlayerPos ^= 1;
                    } else if (selmenu_btnDownTbl[i] & 3) {
                        selmenu_playerCfgPlayerPos ^= 2;
                    }
                    if (selmenu_btnDownTbl[i] & 0x20) {
                        obj->func = selmenu_MenuObjMain;
                        return;
                    }
                    if (selmenu_btnDownTbl[i] & 0x10) {
                        selmenu_playerCfgSelF = 1;
                        return;
                    }
                    if (selmenu_btnDownTbl[i] & 0x80) {
                        selmenu_GroupShuffle();
                        selmenu_PadShuffle();
                    }
                }
                break;
            case 1:
                if (selmenu_btnDownTbl[i] & 1) {
                    if (--selmenu_playerCfgOptionPos < 0) {
                        selmenu_playerCfgOptionPos = 5;
                    }
                } else if (selmenu_btnDownTbl[i] & 2) {
                    if (++selmenu_playerCfgOptionPos >= 6) {
                        selmenu_playerCfgOptionPos = 0;
                    }
                }
                if (selmenu_btnDownTbl[i] & 8) {
                    switch (selmenu_playerCfgOptionPos) {
                        case 0:
                            break;
                        case 1:
                            selmenu_playerCfg[selmenu_playerCfgPlayerPos].stat ^= 1;
                            break;
                        case 2:
                            if (++selmenu_playerCfg[selmenu_playerCfgPlayerPos].group >= 4) {
                                selmenu_playerCfg[selmenu_playerCfgPlayerPos].group = 0;
                            }
                            break;
                        case 3:
                            if (++selmenu_playerCfg[selmenu_playerCfgPlayerPos].cpu_difficulty >= 4) {
                                selmenu_playerCfg[selmenu_playerCfgPlayerPos].cpu_difficulty = 0;
                            }
                            break;
                        case 4:
                            if (++selmenu_playerCfg[selmenu_playerCfgPlayerPos].coin >= 1000) {
                                selmenu_playerCfg[selmenu_playerCfgPlayerPos].coin = 0;
                            }
                            break;
                        case 5:
                            if (++selmenu_playerCfg[selmenu_playerCfgPlayerPos].pad == 4) {
                                selmenu_playerCfg[selmenu_playerCfgPlayerPos].pad = 0;
                            }
                            break;
                    }
                } else if (selmenu_btnDownTbl[i] & 4) {
                    switch (selmenu_playerCfgOptionPos) {
                        case 0:
                            break;
                        case 1:
                            selmenu_playerCfg[selmenu_playerCfgPlayerPos].stat ^= 1;
                            break;
                        case 2:
                            if (selmenu_playerCfg[selmenu_playerCfgPlayerPos].group == 0) {
                                selmenu_playerCfg[selmenu_playerCfgPlayerPos].group = 3;
                            } else {
                                selmenu_playerCfg[selmenu_playerCfgPlayerPos].group--;
                            }
                            break;
                        case 3:
                            if (selmenu_playerCfg[selmenu_playerCfgPlayerPos].cpu_difficulty == 0) {
                                selmenu_playerCfg[selmenu_playerCfgPlayerPos].cpu_difficulty = 3;
                            } else {
                                selmenu_playerCfg[selmenu_playerCfgPlayerPos].cpu_difficulty--;
                            }
                            break;
                        case 4:
                            if (--selmenu_playerCfg[selmenu_playerCfgPlayerPos].coin < 0) {
                                selmenu_playerCfg[selmenu_playerCfgPlayerPos].coin = 999;
                            }
                            break;
                        case 5:
                            if (--selmenu_playerCfg[selmenu_playerCfgPlayerPos].pad == 0xFF) {
                                selmenu_playerCfg[selmenu_playerCfgPlayerPos].pad = 3;
                            }
                            break;
                    }
                } else if (selmenu_btnDownTbl[i] & 0x30) {
                    selmenu_playerCfgSelF = 0;
                    selmenu_playerCfgOptionPos = 0;
                    return;
                } else if (selmenu_btnDownTbl[i] & 0x80) {
                    switch (selmenu_playerCfgOptionPos) {
                        case 2:
                            selmenu_GroupShuffle();
                            break;
                        case 5:
                            selmenu_PadShuffle();
                            break;
                    }
                }
                break;
        }
    }
    sel = selmenu_playerCfgPlayerPos;
    if (sel != 4) {
        cursorCol = sel % 2;
        cursorRow = sel / 2;
        x = cursorCol * 144;
        x += 40;
        y = cursorRow * 7;
        line = selmenu_playerCfgOptionPos + 12;
        y += line;
        y++;
        y *= 8;
    } else {
        x = 0x80;
        y = 0x58;
    }
    espPosSet(selmenu_cursorSpr, x - 4, y);
}

void selmenu_MgNameRiseObjMain(omObjData *obj) {
    u32 x;
    s32 y;
    s32 shadowOfs = 12;
    s32 textOfs = 6;
    s32 i;

    rand8();
    sprintf(omDBGStrBuf, selmenu_menuTbl[selmenu_page * 10 + selmenu_selectPos].name);
    x = (320 - strlen(omDBGStrBuf) * 8) / 2;
    y = (selmenu_selectPos + 10) * 9;
    // The do-while(0) ends a CSE block, keeping GCC from folding textOfs into the sprite positions.
    do {
    } while (0);
    if (y - selmenu_mgNameRiseOfs > 48) {
        if (--selmenu_sparkTimer == 0) {
            selmenu_sparkSprTbl[selmenu_sparkNum] = espEntry(selmenu_sparkAnim, 0, 1);
            espAttrSet(selmenu_sparkSprTbl[selmenu_sparkNum], HUSPR_ATTR_BG);
            espPriSet(selmenu_sparkSprTbl[selmenu_sparkNum], 0x8000);
            espScaleSet(selmenu_sparkSprTbl[selmenu_sparkNum], 0.75f, 0.75f);
            espSpeedSet(selmenu_sparkSprTbl[selmenu_sparkNum], 8.0f);
            espPosSet(selmenu_sparkSprTbl[selmenu_sparkNum], x, y - (u16)selmenu_mgNameRiseOfs + textOfs + 8);
            espColorSet(selmenu_sparkSprTbl[selmenu_sparkNum], 0xFF, 0xFF, 0xBE);
            selmenu_sparkNum++;
            selmenu_sparkSprTbl[selmenu_sparkNum] = espEntry(selmenu_sparkAnim, 0, 1);
            espAttrSet(selmenu_sparkSprTbl[selmenu_sparkNum], HUSPR_ATTR_BG);
            espPriSet(selmenu_sparkSprTbl[selmenu_sparkNum], 0x8000);
            espScaleSet(selmenu_sparkSprTbl[selmenu_sparkNum], 0.75f, 0.75f);
            espSpeedSet(selmenu_sparkSprTbl[selmenu_sparkNum], 8.0f);
            espPosSet(selmenu_sparkSprTbl[selmenu_sparkNum],
                      x + strlen(selmenu_menuTbl[selmenu_page * 10 + selmenu_selectPos].name) * 8,
                      y - (u16)selmenu_mgNameRiseOfs + textOfs + 8);
            espColorSet(selmenu_sparkSprTbl[selmenu_sparkNum], 0xFF, 0xFF, 0xBE);
            selmenu_sparkNum++;
            selmenu_sparkTimer = 4;
        }
        selmenu_mgNameRiseOfs += 4;
        if (y < y - selmenu_mgNameRiseOfs + shadowOfs) {
            shadowOfs = (y - selmenu_mgNameRiseOfs + shadowOfs) - y;
        }
        if (y < y - selmenu_mgNameRiseOfs + textOfs) {
            textOfs = (y - selmenu_mgNameRiseOfs + textOfs) - y;
        }
        fontcolor = 9;
        print8(x, y - (u16)selmenu_mgNameRiseOfs + shadowOfs, omDBGStrBuf);
        fontcolor = 13;
        print8(x, y - (u16)selmenu_mgNameRiseOfs + textOfs, omDBGStrBuf);
    }
    for (i = 0; i < selmenu_sparkNum; i++) {
        if (selmenu_sparkSprTbl[i] != -1 && (espAnimStatGet(selmenu_sparkSprTbl[i]) & 6)) {
            espKill(selmenu_sparkSprTbl[i]);
            selmenu_sparkSprTbl[i] = -1;
        }
    }
    x = (320 - strlen(omDBGStrBuf) * 8) / 2;
    fontcolor = 7;
    print8(x + 1, y + 1 - (u16)selmenu_mgNameRiseOfs, omDBGStrBuf);
    fontcolor = 15;
    print8(x, y - (u16)selmenu_mgNameRiseOfs, omDBGStrBuf);
}

void selmenu_ChrSelObjInit(omObjData *obj) {
    obj->func = selmenu_ChrSelObjMain;
}

void selmenu_ChrSelObjMain(omObjData *obj) {
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

    if (selmenu_exitF == 1) {
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            selmenu_PlayerCfgCopy();
            GwSystem.minigame_index = selmenu_menuTbl[selmenu_page * 10 + selmenu_selectPos].player_groups;
            GwSystem.current_player_index = 0;
            if (omDBGPlayMode == 0) {
                if (selMenuMgModeF == 0) {
                    omOvlCallEx(selmenu_menuTbl[selmenu_page * 10 + selmenu_selectPos].unk_04, 0, 0x94);
                } else {
                    omOvlCallEx(MgDataMaxGet(GwSystem.minigame_index), 0, 0x82);
                }
            } else if (omDBGPlayMode == 1) {
                GwSystem.playMode = 1;
                omOvlCallEx(selmenu_menuTbl[selmenu_page * 10 + selmenu_selectPos].unk_04, 0, 0x92);
            } else {
                GwSystem.playMode = 2;
                omOvlCallEx(selmenu_menuTbl[selmenu_page * 10 + selmenu_selectPos].unk_04, 0, 0x4090);
            }
        }
        return;
    }
    for (i = 0; i < 4; i++) {
        if (selmenu_playerDoneF[i] == 1) {
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
                    if (selmenu_chrUsedF[i] == 0) {
                        freeChars[count++] = i;
                    }
                }
                if (count == 1) {
                    GwPlayer[pads[index]].chr = freeChars[0];
                    selmenu_chrUsedF[freeChars[0]] = 1;
                } else {
                    pick = rand8() % count;
                    GwPlayer[pads[index]].chr = freeChars[pick];
                    selmenu_chrUsedF[freeChars[pick]] = 1;
                }
            }
        }
        WipeColorSet(0, 0, 0);
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        selmenu_exitF = 1;
        selMenuMgModeF = 0;
        for (i = 0; i < 4; i++) {
            if (CheckControllerRead(i) && (HuPadBtn[i] & L_TRIG)) {
                selMenuMgModeF = 1;
                break;
            }
        }
        return;
    }
    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i) && (HuPadBtnDown[i] & START_BUTTON)) {
            for (j = 0; j < 4; j++) {
                if (CheckControllerRead(j)) {
                    selmenu_btnDownTbl[j] |= 0x10;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            sprintf(omDBGStrBuf, "------");
            selmenu_ShadowTextPrint(i * 56 + 56, 144, omDBGStrBuf, 15, 7);
            continue;
        }
        Hu3DModelAttrSet(selmenu_chrMdlTbl[GwPlayer[i].chr], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(selmenu_chrMdlTbl[GwPlayer[i].chr], i * 420 - 650.0f - 60.0f + i * 40, -120.0f, 0.0f);
        Hu3DModelScaleSet(selmenu_chrMdlTbl[GwPlayer[i].chr], 2.0f, 2.0f, 2.0f);
        if (selmenu_playerDoneF[i] == 1) {
            selmenu_chrRotYTbl[i] = 0.0f;
        }
        Hu3DModelRotSet(selmenu_chrMdlTbl[GwPlayer[i].chr], 0.0f, selmenu_chrRotYTbl[i], 0.0f);
        selmenu_chrRotYTbl[i] += 1.0f;
        if (selmenu_chrRotYTbl[i] >= 360.0f) {
            selmenu_chrRotYTbl[i] -= 360.0f;
        }
        color = (selmenu_playerDoneF[i] != 0) ? 15 : 12;
        textColor = color;
        sprintf(omDBGStrBuf, selmenu_chrNameTbl[GwPlayer[i].chr]);
        selmenu_ShadowTextPrint(i * 56 + 50 + i * 4, 144, omDBGStrBuf, textColor, color - 8);
        if ((selmenu_btnDownTbl[i] & 0x10) && selmenu_playerDoneF[i] == 0) {
            selmenu_playerDoneF[i] = 1;
            Hu3DMotionModelSet(selmenu_chrMdlTbl[GwPlayer[i].chr], selmenu_chrDecideMotTbl[GwPlayer[i].chr]);
            Hu3DMotionAttrSet(selmenu_chrMdlTbl[GwPlayer[i].chr], 1, 0);
            Hu3DMotionAttrSet(selmenu_chrMdlTbl[GwPlayer[i].chr], 2, 2);
            selmenu_SePlay(2);
        } else if ((selmenu_btnDownTbl[i] & 0x20) && selmenu_playerDoneF[i] == 1) {
            selmenu_playerDoneF[i] = 0;
            Hu3DMotionModelSet(selmenu_chrMdlTbl[GwPlayer[i].chr], selmenu_chrIdleMotTbl[GwPlayer[i].chr]);
            Hu3DMotionAttrSet(selmenu_chrMdlTbl[GwPlayer[i].chr], 1, 0);
            Hu3DMotionAttrSet(selmenu_chrMdlTbl[GwPlayer[i].chr], 2, 2);
            selmenu_SePlay(3);
        }
        if (selmenu_playerDoneF[i] == 0) {
            if (selmenu_btnDownTbl[i] & 4) {
                chr = GwPlayer[i].chr - 1;
                selmenu_SePlay(0);
                while (TRUE) {
                    if (chr < 0) {
                        chr = 7;
                    }
                    if (selmenu_chrUsedF[chr] == 0) {
                        break;
                    }
                    chr--;
                }
                selmenu_chrUsedF[GwPlayer[i].chr] = 0;
                Hu3DModelAttrSet(selmenu_chrMdlTbl[GwPlayer[i].chr], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                GwPlayer[i].chr = chr;
                selmenu_chrUsedF[GwPlayer[i].chr] = 1;
                selmenu_chrRotYTbl[i] = 0.0f;
            } else if (selmenu_btnDownTbl[i] & 8) {
                chr = GwPlayer[i].chr + 1;
                selmenu_SePlay(0);
                while (TRUE) {
                    if (chr >= 8) {
                        chr = 0;
                    }
                    if (selmenu_chrUsedF[chr] == 0) {
                        break;
                    }
                    chr++;
                }
                selmenu_chrUsedF[GwPlayer[i].chr] = 0;
                Hu3DModelAttrSet(selmenu_chrMdlTbl[GwPlayer[i].chr], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                GwPlayer[i].chr = chr;
                selmenu_chrUsedF[GwPlayer[i].chr] = 1;
                selmenu_chrRotYTbl[i] = 0.0f;
            }
        }
    }
}

void selmenu_SePlay(u16 index) {
    HuAudFXVolSet(HuAudFXPlay(selmenu_seTbl[index].fx), selmenu_seTbl[index].vol);
}

void selmenu_CursorMove(s16 dir) {
    s16 index = selmenu_selectPos;

    do {
        index += dir;
        if (index >= 10) {
            index = 0;
        } else if (index < 0) {
            index = 9;
        }
    } while (selmenu_menuTbl[selmenu_page * 10 + index].available == 1);
    selmenu_selectPos = index;
}

void selmenu_PageMove(s16 dir) {
    u16 found = FALSE;
    s16 prevPage;
    s16 page;
    s32 i;

    prevPage = page = selmenu_page;
    do {
        page += dir;
        if (page >= 10) {
            page = 0;
        } else if (page < 0) {
            page = 9;
        }
        for (i = 0; i < 10; i++) {
            if (selmenu_menuTbl[page * 10 + i].available == 0) {
                found = TRUE;
                break;
            }
        }
    } while (!found);
    selmenu_page = page;
    if (prevPage == -1) {
        selmenu_selectPos = -1;
        selmenu_CursorMove(1);
        selmenu_selectPosBackupTbl[selmenu_page] = selmenu_selectPos;
    } else {
        selmenu_selectPosBackupTbl[prevPage] = selmenu_selectPos;
        selmenu_selectPos = selmenu_selectPosBackupTbl[selmenu_page];
    }
}

void selmenu_ShadowTextPrint(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4) {
    fontcolor = arg4;
    print8((arg0 + 1), (arg1 + 1), arg2);
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

void selmenu_PlayerGroupSet(void) {
    SelMenuPlayerGroups *groups = &selmenu_playerGroupTbl[selmenu_menuTbl[selmenu_page * 10 + selmenu_selectPos].player_groups - 1];
    GW_PLAYER *player = selmenu_playerCfg;

    player->group = groups->group[0];
    player++;
    player->group = groups->group[1];
    player++;
    player->group = groups->group[2];
    player++;
    player->group = groups->group[3];
}

void selmenu_PlayerCfgCopy(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        GW_PLAYER *src = &selmenu_playerCfg[i];
        GW_PLAYER *dst = &GwPlayer[i];

        dst->stat = src->stat;
        dst->group = src->group;
        dst->pad = src->pad;
        dst->cpu_difficulty = src->cpu_difficulty;
        dst->coin = src->coin;
    }
}

void selmenu_GroupShuffle(void) {
    u8 groups[4];
    u8 used[4];
    s32 i;
    s32 r;

    for (i = 0; i < 4; i++) {
        groups[i] = selmenu_playerCfg[i].group;
        used[i] = FALSE;
    }
    for (i = 0; i < 4; i++) {
        do {
            r = rand8() & 3;
        } while (used[r] == TRUE);
        used[r] = TRUE;
        selmenu_playerCfg[i].group = groups[r];
    }
}

void selmenu_PadShuffle(void) {
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
        selmenu_playerCfg[i].pad = r;
    }
}
