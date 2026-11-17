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
    char *unk_0C;
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
extern char selmenu2_optionTitleStr[];
extern char selmenu2_mapFmtStr[];
extern char selmenu2_pageFmtStr[];
extern s16 selMenuMgModeF;
extern char selmenu2_mgNameBlankStr[];
extern char selmenu2_mgNameMessStr[];
extern char selmenu2_mgName272Str[];
extern char selmenu2_mgName271Str[];
extern char selmenu2_mgName270Str[];
extern char selmenu2_mgName269Str[];
extern char selmenu2_mgName268Str[];
extern char selmenu2_mgName267Str[];
extern char selmenu2_mgName266Str[];
extern char selmenu2_mgName264Str[];
extern char selmenu2_mgName263Str[];
extern char selmenu2_mgName262Str[];
extern char selmenu2_mgName261Str[];
extern char selmenu2_mgName260Str[];
extern char selmenu2_mgName259Str[];
extern char selmenu2_mgName258Str[];
extern char selmenu2_mgName257Str[];
extern char selmenu2_mgName256Str[];
extern char selmenu2_mgName255Str[];
extern char selmenu2_mgName254Str[];
extern char selmenu2_mgName253Str[];
extern char selmenu2_mgName252Str[];
extern char selmenu2_mgName251Str[];
extern char selmenu2_mgName250Str[];
extern char selmenu2_mgName249Str[];
extern char selmenu2_mgName248Str[];
extern char selmenu2_mgName247Str[];
extern char selmenu2_mgName246Str[];
extern char selmenu2_mgName245Str[];
extern char selmenu2_mgName244Str[];
extern char selmenu2_mgName243Str[];
extern char selmenu2_mgName242Str[];
extern char selmenu2_mgName241Str[];
extern char selmenu2_mgName240Str[];
extern char selmenu2_mgName239Str[];
extern char selmenu2_mgName238Str[];
extern char selmenu2_mgName237Str[];
extern char selmenu2_mgName236Str[];
extern char selmenu2_mgName235Str[];
extern char selmenu2_mgName234Str[];
extern char selmenu2_mgName233Str[];
extern char selmenu2_mgName232Str[];
extern char selmenu2_mgName231Str[];
extern char selmenu2_mgName230Str[];
extern char selmenu2_mgName229Str[];
extern char selmenu2_mgName228Str[];
extern char selmenu2_mgName227Str[];
extern char selmenu2_mgName226Str[];
extern char selmenu2_mgName225Str[];
extern char selmenu2_mgName224Str[];
extern char selmenu2_mgName223Str[];
extern char selmenu2_mgName222Str[];
extern char selmenu2_mgName221Str[];
extern char selmenu2_mgName220Str[];
extern char selmenu2_mgName219Str[];
extern char selmenu2_mgName218Str[];
extern char selmenu2_mgName217Str[];
extern char selmenu2_mgName216Str[];
extern char selmenu2_mgName215Str[];
extern char selmenu2_mgName214Str[];
extern char selmenu2_mgName213Str[];
extern char selmenu2_mgName212Str[];
extern char selmenu2_mgName211Str[];
extern char selmenu2_mgName210Str[];
extern char selmenu2_mgName209Str[];
extern char selmenu2_mgName208Str[];
extern char selmenu2_mgName207Str[];
extern char selmenu2_mgName206Str[];
extern char selmenu2_mgName205Str[];
extern char selmenu2_mgName204Str[];
extern char selmenu2_mgName203Str[];
extern char selmenu2_mgName202Str[];
extern char selmenu2_mgName201Str[];
extern char selmenu2_padNoFmtStr[];
extern char selmenu2_coinFmtStr[];
extern char selmenu2_comLevelFmtStr[];
extern char selmenu2_groupFmtStr[];
extern char selmenu2_padFmtStr[];
extern char selmenu2_playerFmtStr[];
extern char selmenu2_comStr[];
extern char selmenu2_humanStr[];
extern char selmenu2_veryHardStr[];
extern char selmenu2_hardStr[];
extern char selmenu2_normalStr[];
extern char selmenu2_easyStr[];
extern char selmenu2_daisyStr[];
extern char selmenu2_waluigiStr[];
extern char selmenu2_donkeyStr[];
extern char selmenu2_warioStr[];
extern char selmenu2_yoshiStr[];
extern char selmenu2_peachStr[];
extern char selmenu2_luigiStr[];
extern char selmenu2_marioStr[];
extern char selmenu2_duelStr[];
extern char selmenu2_boardStr[];
extern char selmenu2_gameStr[];

SelMenuConfig selmenu2_menuTbl[80] = {
    { 0, 1, 1, 0, 1, 100, 0, selmenu2_mgName201Str }, /* "201:PUKUPUKU FISHING" */
    { 0, 2, 2, 0, 2, 100, 0, selmenu2_mgName202Str }, /* "202:HIYA2 YASHINOMI" */
    { 0, 3, 3, 0, 3, 100, 0, selmenu2_mgName203Str }, /* "203:TERASHITE SEARCH LIGHT" */
    { 0, 4, 4, 0, 4, 100, 0, selmenu2_mgName204Str }, /* "204:GOROGORO IWAKOROGASHI" */
    { 0, 4, 5, 0, 5, 100, 0, selmenu2_mgName205Str }, /* "205:GURU2 KILLER ATTACK" */
    { 0, 4, 6, 0, 6, 100, 0, selmenu2_mgName206Str }, /* "206:DOKO?2 KAKURENBO" */
    { 0, 5, 7, 0, 7, 100, 0, selmenu2_mgName207Str }, /* "207:DOTABATA RELAY" */
    { 0, 5, 8, 0, 8, 100, 0, selmenu2_mgName208Str }, /* "208:DOSSUN DOSSUN!" */
    { 0, 5, 9, 0, 9, 100, 0, selmenu2_mgName209Str }, /* "209:SUIJYOU SKI" */
    { 0, 5, 10, 0, 10, 100, 0, selmenu2_mgName210Str }, /* "210:WAVE*WAVE" */
    { 0, 6, 11, 0, 11, 100, 0, selmenu2_mgName211Str }, /* "211:MOGO2 PIZZA HOUSE" */
    { 0, 6, 12, 0, 12, 100, 0, selmenu2_mgName212Str }, /* "212:ATECHAE! MINI KOOPA" */
    { 0, 6, 13, 0, 13, 100, 0, selmenu2_mgName213Str }, /* "213:GO!GO! ROCKET" */
    { 0, 6, 14, 0, 14, 100, 0, selmenu2_mgName214Str }, /* "214:BOBBLE HINO YOUJIN!" */
    { 0, 7, 15, 0, 15, 100, 0, selmenu2_mgName215Str }, /* "215:FRUITS BASCKET" */
    { 0, 8, 16, 0, 16, 100, 0, selmenu2_mgName216Str }, /* "216:OJAMA COSTER" */
    { 0, 8, 17, 0, 17, 100, 0, selmenu2_mgName217Str }, /* "217:COIN LAKE" */
    { 0, 8, 18, 0, 18, 100, 0, selmenu2_mgName218Str }, /* "218:KAKONDE KUREYON" */
    { 0, 9, 19, 0, 19, 100, 0, selmenu2_mgName219Str }, /* "219:NAKAYOSHI MAKIWARI" */
    { 0, 9, 20, 0, 20, 100, 0, selmenu2_mgName220Str }, /* "220:NUIGURUMI FACTORY" */
    { 0, 11, 21, 0, 21, 100, 0, selmenu2_mgName221Str }, /* "221:BELCON DANGEROUS" */
    { 0, 11, 22, 0, 22, 100, 0, selmenu2_mgName222Str }, /* "222:POWER KINOKO GO!GO!" */
    { 0, 11, 23, 0, 23, 100, 0, selmenu2_mgName223Str }, /* "223:TIKITIKI AIR FIGHT!" */
    { 0, 11, 24, 0, 24, 100, 0, selmenu2_mgName224Str }, /* "224:PYONPYON BATTLE!" */
    { 0, 11, 25, 0, 25, 100, 0, selmenu2_mgName225Str }, /* "225:TOGEZOH CRASH" */
    { 0, 11, 26, 0, 26, 100, 0, selmenu2_mgName226Str }, /* "226:NIGEKOME SHELTER" */
    { 0, 12, 27, 0, 27, 100, 0, selmenu2_mgName227Str }, /* "227:PITTARI! SHOT" */
    { 0, 12, 28, 0, 28, 100, 0, selmenu2_mgName228Str }, /* "228:OKKOTI PARASOL" */
    { 0, 12, 29, 0, 29, 100, 0, selmenu2_mgName229Str }, /* "229:MATIGAI WO SAGSE!" */
    { 0, 12, 30, 0, 30, 100, 0, selmenu2_mgName230Str }, /* "230:OWASETE MONTAGE" */
    { 0, 14, 31, 0, 31, 100, 0, selmenu2_mgName231Str }, /* "231:DOSSUN PUZZLE" */
    { 0, 14, 32, 0, 32, 100, 0, selmenu2_mgName232Str }, /* "232:TATAITE DRUM" */
    { 0, 14, 33, 0, 33, 100, 0, selmenu2_mgName233Str }, /* "233:QUIZ PARTY" */
    { 0, 16, 34, 0, 34, 100, 0, selmenu2_mgName234Str }, /* "234:DAREKA WAKARUKANA" */
    { 0, 17, 35, 0, 35, 100, 0, selmenu2_mgName235Str }, /* "235:MOTORBOAT RACE" */
    { 0, 17, 36, 0, 36, 100, 0, selmenu2_mgName236Str }, /* "236:KUNEKUNE ROAD RACE" */
    { 0, 17, 37, 0, 37, 100, 0, selmenu2_mgName237Str }, /* "237:AOZORA BLOCK RACE" */
    { 0, 20, 38, 0, 38, 100, 0, selmenu2_mgName238Str }, /* "238:HARAPEKO PUKU2" */
    { 0, 20, 39, 0, 39, 100, 0, selmenu2_mgName239Str }, /* "239:TATAKE! MINI KOOPA" */
    { 0, 20, 40, 0, 40, 100, 0, selmenu2_mgName240Str }, /* "240:YUKIDAMA GOROGORO!" */
    { 0, 22, 41, 0, 41, 100, 0, selmenu2_mgName241Str }, /* "241:KAWASHITE BOBBLE" */
    { 0, 22, 42, 0, 42, 100, 0, selmenu2_mgName242Str }, /* "242:DOKI2 CARD DROP" */
    { 0, 22, 43, 0, 43, 100, 0, selmenu2_mgName243Str }, /* "243:HAYAOSHI HOUSE" */
    { 0, 23, 44, 0, 44, 100, 0, selmenu2_mgName244Str }, /* "244:GO!GO! MOKUBA" */
    { 0, 23, 45, 0, 45, 100, 0, selmenu2_mgName245Str }, /* "245:DANGEROUS ROULETTE" */
    { 0, 23, 46, 0, 46, 100, 0, selmenu2_mgName246Str }, /* "246:MEKUTTE HAYAOSHI!" */
    { 0, 23, 47, 0, 47, 100, 0, selmenu2_mgName247Str }, /* "247:AMEFURI FLOWER" */
    { 0, 23, 48, 0, 48, 100, 0, selmenu2_mgName248Str }, /* "248:EYEKUN MAWASHI" */
    { 0, 24, 49, 0, 49, 100, 0, selmenu2_mgName249Str }, /* "249:TARZAN RACE" */
    { 0, 25, 50, 0, 50, 100, 0, selmenu2_mgName250Str }, /* "250:HAYAUCHI MINIKOOPA" */
    { 0, 25, 51, 0, 51, 100, 0, selmenu2_mgName251Str }, /* "251:BOUSOU SYUPPOH" */
    { 0, 26, 52, 0, 52, 100, 0, selmenu2_mgName252Str }, /* "252:TONDEKE KOOPA HAMMER" */
    { 0, 27, 53, 0, 53, 100, 0, selmenu2_mgName253Str }, /* "253:ITAZURA MINI KOOPA" */
    { 0, 28, 54, 0, 54, 100, 0, selmenu2_mgName254Str }, /* "254:BIRIKYUU COASTER" */
    { 0, 28, 55, 0, 55, 100, 0, selmenu2_mgName255Str }, /* "255:BOLT DASH" */
    { 0, 28, 56, 0, 56, 100, 0, selmenu2_mgName256Str }, /* "256:KONO E HA NAANI?" */
    { 0, 30, 57, 0, 57, 100, 0, selmenu2_mgName257Str }, /* "257:GURU2 JUMP!" */
    { 0, 30, 58, 0, 58, 100, 0, selmenu2_mgName258Str }, /* "258:NIWATORI CATCH" */
    { 0, 30, 59, 0, 59, 100, 0, selmenu2_mgName259Str }, /* "259:NERAE! ITEM!!" */
    { 0, 30, 60, 0, 60, 100, 0, selmenu2_mgName260Str }, /* "260:ITEM HOMERUN" */
    { 0, 30, 61, 0, 61, 100, 0, selmenu2_mgName261Str }, /* "261:NERATTE BALOON" */
    { 0, 30, 62, 0, 62, 100, 0, selmenu2_mgName262Str }, /* "262:DOSSHI DE CATCH" */
    { 0, 30, 63, 0, 63, 100, 0, selmenu2_mgName263Str }, /* "263:FLYING.BURANKO" */
    { 0, 30, 64, 0, 64, 100, 0, selmenu2_mgName264Str }, /* "264:HAMMER ITEM" */
    { 0, 30, 66, 0, 65, 100, 0, selmenu2_mgName266Str }, /* "266:STARDUST BATTLE" */
    { 0, 32, 67, 0, 66, 100, 0, selmenu2_mgName267Str }, /* "267:HEIHO ROULETTE" */
    { 0, 32, 68, 0, 67, 100, 0, selmenu2_mgName268Str }, /* "268:NERATTE 7" */
    { 0, 33, 69, 0, 68, 100, 0, selmenu2_mgName269Str }, /* "269:KINOPIO?KOOPA?" */
    { 0, 33, 70, 0, 69, 100, 0, selmenu2_mgName270Str }, /* "270:CAKE DE BATTLE!" */
    { 0, 33, 71, 0, 104, 100, 0, selmenu2_mgName271Str }, /* "271:MOTERBOAT TRIAL" */
    { 0, 33, 72, 0, 31, 100, 0, selmenu2_mgName272Str }, /* "272:3PUNN DOSSUN" */
    { 0, 1, 11, 0, 118, 100, 0, selmenu2_mgNameMessStr }, /* "***:MESS" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu2_mgNameBlankStr }, /* "***:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu2_mgNameBlankStr }, /* "***:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu2_mgNameBlankStr }, /* "***:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu2_mgNameBlankStr }, /* "***:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu2_mgNameBlankStr }, /* "***:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu2_mgNameBlankStr }, /* "***:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu2_mgNameBlankStr }, /* "***:" */
    { 1, 1, 11, 0, 1000, 100, 0, selmenu2_mgNameBlankStr }, /* "***:" */
};

SelMenuPlayerGroups selmenu2_playerGroupTbl[] = {
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
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
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
    { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 5, 5, 5, 5 } },
};

SelMenuSound selmenu2_seTbl[] = {
    { 0, 0, 0x78 },
    { 0, 0, 0x6A },
    { 0, 0, 0x6E },
    { 0, 0, 0x72 },
    { 0, 0, 0x7B },
};

u16 selmenu2_textColorTbl[2][2] = { { 5, 13 }, { 4, 12 } }; // text colors

SelMenuConfig selmenu2_playerCfgMenuTbl[] = {
    { 1, 3, 11, 0, 1000, 0, 0, selmenu2_playerFmtStr }, /* ">PLAYER%d" */
    { 0, 4, 12, 0, 1000, 0, 0, selmenu2_padFmtStr }, /* "PAD%d:%s" */
    { 0, 4, 12, 0, 1000, 0, 0, selmenu2_groupFmtStr }, /* "GRP :%d" */
    { 0, 4, 12, 0, 1000, 0, 0, selmenu2_comLevelFmtStr }, /* "DIF :%s" */
    { 0, 4, 12, 0, 1000, 0, 0, selmenu2_coinFmtStr }, /* "COIN:%d" */
    { 0, 4, 12, 0, 1000, 0, 0, selmenu2_padNoFmtStr }, /* "PADN:%d" */
};

char *selmenu2_padCfgStrTbl[] = { selmenu2_humanStr, selmenu2_comStr };

char *selmenu2_comLevelStrTbl[] = { selmenu2_easyStr, selmenu2_normalStr, selmenu2_hardStr, selmenu2_veryHardStr };

char *selmenu2_chrNameTbl[] = {
    selmenu2_marioStr, selmenu2_luigiStr, selmenu2_peachStr, selmenu2_yoshiStr,
    selmenu2_warioStr, selmenu2_donkeyStr, selmenu2_waluigiStr, selmenu2_daisyStr,
    selmenu2_gameStr, selmenu2_boardStr, selmenu2_duelStr,
};

u8 selmenu2_decideF = 0;
char *selmenu2_comLevelUnusedStrTbl[] = { selmenu2_easyStr, selmenu2_normalStr, selmenu2_hardStr }; /* Unreferenced. */
s32 selmenu2_mgNameRiseOfs = 0;
s32 selmenu2_sparkNum = 0;
s32 selmenu2_sparkTimer = 1;

s16 selmenu2_page BSS;
s16 selmenu2_selectPos BSS;
u8 selmenu2_pagePad[4] BSS; /* Unreferenced. */
s16 selmenu2_selectPosBackupTbl[8] BSS;
s16 selmenu2_playerCfgOptionPos BSS;
s16 selmenu2_playerCfgPlayerPos BSS;
s16 selmenu2_playerCfgSelF BSS;
GW_PLAYER selmenu2_playerCfg[4] BSS;
u8 selmenu2_playerCfgTailPad[0x38] BSS; /* Unreferenced. */
u8 selmenu2_playerDoneF[4] BSS;
u8 selmenu2_chrUsedF[8] BSS;
u8 selmenu2_chrPad[4] BSS; /* Unreferenced. */
s16 selmenu2_chrMdlTbl[8] BSS;
s16 selmenu2_chrIdleMotTbl[8] BSS;
s16 selmenu2_chrDecideMotTbl[8] BSS;
s16 selmenu2_playerChrTbl[4] BSS;
s8 selmenu2_stickXPrev[4] BSS;
s8 selmenu2_stickYPrev[4] BSS;
u8 selmenu2_exitF BSS;
s16 selmenu2_bgAnim BSS;
s16 selmenu2_cursorAnim BSS;
u16 selmenu2_cursorSpr BSS;
s16 selmenu2_sparkAnim BSS;
u8 selmenu2_sparkPad[4] BSS; /* Unreferenced. */
s16 selmenu2_sparkSprTbl[40] BSS;
f32 selmenu2_chrRotYTbl[4] BSS;
u8 selmenu2_btnDownTbl[4] BSS;
u16 selmenu2_btnHoldDirTbl[4] BSS;
u16 selmenu2_btnHoldCntTbl[4] BSS;
u16 selmenu2_btnRepeatTimerTbl[4] BSS;
u8 selmenu2_btnPad[0xC] BSS; /* Unreferenced. */

void selmenu2_CameraSet(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);
void selmenu2_BtnCalcObjMain(omObjData *obj);
void selmenu2_MenuObjInit(omObjData *obj);
void selmenu2_MenuObjMain(omObjData *obj);
void selmenu2_PlayerCfgObjMain(omObjData *obj);
void selmenu2_MgNameRiseObjMain(omObjData *obj);
void selmenu2_ChrSelObjInit(omObjData *obj);
void selmenu2_ChrSelObjMain(omObjData *obj);
void selmenu2_SePlay(u16 index);
void selmenu2_CursorMove(s16 dir);
void selmenu2_ShadowTextPrint(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4);
void selmenu2_PageMove(s16 dir);
void selmenu2_PlayerGroupSet(void);
void selmenu2_PlayerCfgCopy(void);
void selmenu2_GroupShuffle(void);
void selmenu2_PadShuffle(void);

void selmenu2_ObjectSetup(void) {
    omObjData *obj;
    GW_PLAYER *player;
    u16 sprite;
    s32 i;

    selmenu2_exitF = 0;
    _SetFlag(0x12);
    _ClearFlag(0xD);
    GwSystem.show_minigame_explanations = 0;
    if (selMenuLastOvl < 71) {
        for (i = 0; i < 4; i++) {
            GwPlayer[i].coin += GwPlayer[i].gameCoin;
            if (GwPlayer[i].coin >= 1000) {
                GwPlayer[i].coin = 999;
            }
            if (GwPlayer[i].coin < 0) {
                GwPlayer[i].coin = 0;
            }
            GwPlayer[i].gameCoin = 0;
        }
    }
    omInitObjMan(50, 0);
    selmenu2_CameraSet(2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightMaxSet(1);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightColorSet(1, 0x60, 0x60, 0x10);
    Hu3DGLightDirSet(1, 100.0f, -100.0f, 100.0f);
    omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omAddObj(0, 0, 0, -1, selmenu2_BtnCalcObjMain);
    omAddObj(1, 0, 0, -1, selmenu2_MenuObjInit);
    omMakeGroup(0, 32);
    obj = omAddObj(10, 1, 80, -1, NULL);
    for (i = 0; i < 8; i++) {
        selmenu2_chrMdlTbl[i] = Hu3DModelRead(omCharModelNoTbl[i][0] | omCharMotTbl[i][0], 0x69D);
        Hu3DData[selmenu2_chrMdlTbl[i]].motAttr |= 2;
        omObjMotionRead(obj, 0, CharMotionDataNumGet(i, 0));
        selmenu2_chrIdleMotTbl[i] = obj->motion[0];
        omObjMotionRead(obj, 1, CharMotionDataNumGet(i, 0x2F));
        selmenu2_chrDecideMotTbl[i] = obj->motion[1];
    }
    omDelObj(obj);
    for (i = 0; i < 4; i++) {
        selmenu2_stickYPrev[i] = 0;
        selmenu2_stickXPrev[i] = 0;
    }
    selmenu2_bgAnim = HuSprAnimDataRead(0x10020);
    espPalColorSet(selmenu2_bgAnim, 0.3f, 0.3f, 0.3f);
    for (i = 0; i < 35; i++) {
        sprite = espEntry(selmenu2_bgAnim, i % 6, 1);
        espDispOn(sprite);
        espPriSet(sprite, 0xFFFF);
        espAttrSet(sprite, HUSPR_ATTR_BG);
        espTPLvlSet(sprite, 0xFF);
        espPosSet(sprite, (i % 7) * 48, (i / 7) * 48);
    }
    selmenu2_cursorAnim = HuSprAnimDataRead(10);
    selmenu2_cursorSpr = espEntry(selmenu2_cursorAnim, 0, 1);
    espDispOn(selmenu2_cursorSpr);
    espPosSet(selmenu2_cursorSpr, 0x80, 0x80);
    espScaleSet(selmenu2_cursorSpr, 0.25f, 0.25f);
    for (i = 0; i < 40; i++) {
        selmenu2_sparkSprTbl[i] = -1;
    }
    selmenu2_sparkAnim = HuSprAnimDataRead(12);
    for (i = 0; i < 4; i++) {
        selmenu2_btnHoldCntTbl[i] = 0;
        selmenu2_btnRepeatTimerTbl[i] = 0;
        selmenu2_btnHoldDirTbl[i] = 0;
    }
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    HuAudSeqPlay(rand8() % 9);
    for (i = 0; i < 4; i++) {
        player = &GwPlayer[i];
        player->gamePrize = -1;
        player->coinPrize = -1;
        player->stats.prize.hatenaPrize = 0;
        player->stats.prize.redPrize = 0;
        player->stats.prize.bluePrize = 0;
        player->stats.prize.eventPrize = 0;
        player->stats.prize.kupaPrize = 0;
        player->stats.prize.battlePrize = 0;
        player->stats.prize.itemPrize = 0;
        player->stats.prize.bankPrize = 0;
        player->star = 5;
    }
    GwSystem.bank_coins = 0;
}

void selmenu2_CameraSet(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    CamSetupInit(1);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
}

void selmenu2_BtnCalcObjMain(omObjData *obj) {
    s8 stickX;
    s8 stickY;
    s32 i;

    for (i = 0; i < 4; i++) {
        selmenu2_btnDownTbl[i] = 0;
        if (!CheckControllerRead(i)) {
            continue;
        }
        if (WipeStatGet() == 1) {
            continue;
        }
        stickX = HuPadStkX[i];
        stickY = HuPadStkY[i];
        if (HuPadBtnDown[i] & (U_JPAD | U_CBUTTONS)) {
            selmenu2_btnDownTbl[i] |= 1;
        }
        if (HuPadBtnDown[i] & (D_JPAD | D_CBUTTONS)) {
            selmenu2_btnDownTbl[i] |= 2;
        }
        if (HuPadBtnDown[i] & (L_JPAD | L_CBUTTONS)) {
            selmenu2_btnDownTbl[i] |= 4;
        }
        if (HuPadBtnDown[i] & (R_JPAD | R_CBUTTONS)) {
            selmenu2_btnDownTbl[i] |= 8;
        }
        if (stickY < -10 && ABS(selmenu2_stickYPrev[i]) < 10) {
            selmenu2_btnDownTbl[i] |= 2;
        }
        if (stickY > 10 && ABS(selmenu2_stickYPrev[i]) < 10) {
            selmenu2_btnDownTbl[i] |= 1;
        }
        if (stickX < -10 && ABS(selmenu2_stickXPrev[i]) < 10) {
            selmenu2_btnDownTbl[i] |= 4;
        }
        if (stickX > 10 && ABS(selmenu2_stickXPrev[i]) < 10) {
            selmenu2_btnDownTbl[i] |= 8;
        }
        selmenu2_stickXPrev[i] = stickX;
        selmenu2_stickYPrev[i] = stickY;
        if (HuPadBtnDown[i] & Z_TRIG) {
            selmenu2_btnDownTbl[i] |= 0x40;
        }
        if ((HuPadBtn[i] & (U_JPAD | U_CBUTTONS)) || stickY > 10) {
            if (selmenu2_btnHoldDirTbl[i] & 1) {
                selmenu2_btnHoldCntTbl[i]++;
                if (selmenu2_btnHoldCntTbl[i] >= 16) {
                    selmenu2_btnHoldCntTbl[i] = 15;
                }
            } else {
                selmenu2_btnHoldCntTbl[i] = 0;
            }
            if (selmenu2_btnHoldDirTbl[i] != 1) {
                selmenu2_btnRepeatTimerTbl[i] = 0;
                selmenu2_btnHoldCntTbl[i] = 0;
            }
            selmenu2_btnHoldDirTbl[i] = 1;
            if (selmenu2_btnHoldCntTbl[i] == 15) {
                if (selmenu2_btnRepeatTimerTbl[i] == 0) {
                    selmenu2_btnDownTbl[i] |= 1;
                    selmenu2_btnRepeatTimerTbl[i] = 2;
                } else {
                    selmenu2_btnRepeatTimerTbl[i]--;
                }
            }
        } else if ((HuPadBtn[i] & (D_JPAD | D_CBUTTONS)) || stickY < -10) {
            if (selmenu2_btnHoldDirTbl[i] & 2) {
                selmenu2_btnHoldCntTbl[i]++;
                if (selmenu2_btnHoldCntTbl[i] >= 16) {
                    selmenu2_btnHoldCntTbl[i] = 15;
                }
            } else {
                selmenu2_btnHoldCntTbl[i] = 0;
            }
            if (selmenu2_btnHoldDirTbl[i] != 2) {
                selmenu2_btnRepeatTimerTbl[i] = 0;
                selmenu2_btnHoldCntTbl[i] = 0;
            }
            selmenu2_btnHoldDirTbl[i] = 2;
            if (selmenu2_btnHoldCntTbl[i] == 15) {
                if (selmenu2_btnRepeatTimerTbl[i] == 0) {
                    selmenu2_btnDownTbl[i] |= 2;
                    selmenu2_btnRepeatTimerTbl[i] = 2;
                } else {
                    selmenu2_btnRepeatTimerTbl[i]--;
                }
            }
        } else if ((HuPadBtn[i] & (L_JPAD | L_CBUTTONS)) || stickX < -10) {
            if (selmenu2_btnHoldDirTbl[i] & 4) {
                selmenu2_btnHoldCntTbl[i]++;
                if (selmenu2_btnHoldCntTbl[i] >= 16) {
                    selmenu2_btnHoldCntTbl[i] = 15;
                }
            } else {
                selmenu2_btnHoldCntTbl[i] = 0;
            }
            if (selmenu2_btnHoldDirTbl[i] != 4) {
                selmenu2_btnRepeatTimerTbl[i] = 0;
                selmenu2_btnHoldCntTbl[i] = 0;
            }
            selmenu2_btnHoldDirTbl[i] = 4;
            if (selmenu2_btnHoldCntTbl[i] == 15) {
                if (selmenu2_btnRepeatTimerTbl[i] == 0) {
                    selmenu2_btnDownTbl[i] |= 4;
                    selmenu2_btnRepeatTimerTbl[i] = 2;
                } else {
                    selmenu2_btnRepeatTimerTbl[i]--;
                }
            }
        } else if ((HuPadBtn[i] & (R_JPAD | R_CBUTTONS)) || stickX > 10) {
            if (selmenu2_btnHoldDirTbl[i] & 8) {
                selmenu2_btnHoldCntTbl[i]++;
                if (selmenu2_btnHoldCntTbl[i] >= 16) {
                    selmenu2_btnHoldCntTbl[i] = 15;
                }
            } else {
                selmenu2_btnHoldCntTbl[i] = 0;
            }
            if (selmenu2_btnHoldDirTbl[i] != 8) {
                selmenu2_btnRepeatTimerTbl[i] = 0;
                selmenu2_btnHoldCntTbl[i] = 0;
            }
            selmenu2_btnHoldDirTbl[i] = 8;
            if (selmenu2_btnHoldCntTbl[i] == 15) {
                if (selmenu2_btnRepeatTimerTbl[i] == 0) {
                    selmenu2_btnDownTbl[i] |= 8;
                    selmenu2_btnRepeatTimerTbl[i] = 2;
                } else {
                    selmenu2_btnRepeatTimerTbl[i]--;
                }
            }
        } else {
            selmenu2_btnHoldCntTbl[i] = 0;
        }
        if (HuPadBtnDown[i] & A_BUTTON) {
            selmenu2_btnDownTbl[i] |= 0x10;
        }
        if (HuPadBtnDown[i] & B_BUTTON) {
            selmenu2_btnDownTbl[i] |= 0x20;
        }
        if (HuPadBtnDown[i] & START_BUTTON) {
            selmenu2_btnDownTbl[i] |= 0x80;
        }
        if ((HuPadBtn[i] & (L_TRIG | R_TRIG)) == (L_TRIG | R_TRIG)) {
            omOvlReturnEx(0);
            return;
        }
    }
}

void selmenu2_MenuObjInit(omObjData *obj) {
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        selmenu2_chrUsedF[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].chr = i;
        selmenu2_playerChrTbl[i] = i;
        selmenu2_playerDoneF[i] = 0;
        selmenu2_chrRotYTbl[i] = 0.0f;
    }
    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            selmenu2_chrUsedF[i] = 1;
        }
    }
    selmenu2_page = -1;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 10; j++) {
            if (selmenu2_menuTbl[i * 10 + j].available != 1) {
                break;
            }
        }
        if (j == 10) {
            selmenu2_selectPosBackupTbl[i] = -1;
        } else {
            selmenu2_selectPosBackupTbl[i] = j;
        }
    }
    selmenu2_PageMove(1);
    if (selMenuLastOvl != 999) {
        for (i = 0; i < 80; i++) {
            if (selmenu2_menuTbl[i].unk_04 == selMenuLastOvl) {
                selmenu2_page = i / 10;
                selmenu2_selectPos = i % 10;
                selmenu2_selectPosBackupTbl[selmenu2_page] = selmenu2_selectPos;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        selmenu2_playerCfg[i] = GwPlayer[i];
    }
    selmenu2_PlayerGroupSet();
    obj->func = selmenu2_MenuObjMain;
}

void selmenu2_MenuObjMain(omObjData *obj) {
    SelMenuConfig *space;
    u16 *color;
    s32 x;
    s32 i;

    rand8();
    space = &selmenu2_menuTbl[selmenu2_page * 10];
    for (i = 0; i < 10; i++, space++) {
        sprintf(omDBGStrBuf, space->unk_0C);
        x = strlen(omDBGStrBuf);
        x = 0x40;
        if (selmenu2_menuTbl[selmenu2_page * 10 + i].available == 0) {
            color = selmenu2_textColorTbl[0];
        } else {
            color = selmenu2_textColorTbl[1];
        }
        if (selmenu2_selectPos == i) {
            selmenu2_ShadowTextPrint(x, (i + 10) * 9, omDBGStrBuf, color[1], color[0]);
        } else {
            selmenu2_ShadowTextPrint(x, (i + 10) * 9, omDBGStrBuf, color[0], 0);
        }
    }
    sprintf(omDBGStrBuf, selmenu2_pageFmtStr, selmenu2_page + 1, 8);
    selmenu2_ShadowTextPrint(0x80, 0x40, omDBGStrBuf, 15, 7);
    espPosSet(selmenu2_cursorSpr, 0x3C, (selmenu2_selectPos + 11) * 9 - 1);
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        if ((selmenu2_btnDownTbl[i] & 0x90) && selmenu2_menuTbl[selmenu2_page * 10 + selmenu2_selectPos].available == 0) {
            if (selmenu2_decideF == 0) {
                omAddObj(2, 0, 0, -1, selmenu2_ChrSelObjInit);
                selmenu2_decideF = 1;
                espDispOff(selmenu2_cursorSpr);
                obj->func = selmenu2_MgNameRiseObjMain;
                selmenu2_SePlay(1);
            }
        } else if (selmenu2_btnDownTbl[i] & 1) {
            selmenu2_CursorMove(-1);
            selmenu2_PlayerGroupSet();
            selmenu2_SePlay(0);
        } else if (selmenu2_btnDownTbl[i] & 2) {
            selmenu2_CursorMove(1);
            selmenu2_PlayerGroupSet();
            selmenu2_SePlay(0);
        } else if (selmenu2_btnDownTbl[i] & 4) {
            selmenu2_PageMove(-1);
            selmenu2_PlayerGroupSet();
            selmenu2_SePlay(4);
        } else if (selmenu2_btnDownTbl[i] & 8) {
            selmenu2_PageMove(1);
            selmenu2_PlayerGroupSet();
            selmenu2_SePlay(4);
        } else if (selmenu2_btnDownTbl[i] & 0x40) {
            selmenu2_playerCfgOptionPos = 0;
            selmenu2_playerCfgPlayerPos = 0;
            selmenu2_playerCfgSelF = 0;
            obj->func = selmenu2_PlayerCfgObjMain;
        }
    }
}

void selmenu2_PlayerCfgObjMain(omObjData *obj) {
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
    sprintf(omDBGStrBuf, selmenu2_optionTitleStr);
    selmenu2_ShadowTextPrint(0x70, 0x40, omDBGStrBuf, 15, 7);
    for (i = 0; i < 5; i++) {
        space = selmenu2_playerCfgMenuTbl;
        if (i == 4) {
            sprintf(omDBGStrBuf, selmenu2_mapFmtStr, GwSystem.current_board_index);
            color = selmenu2_textColorTbl[0];
            if (selmenu2_playerCfgPlayerPos == i) {
                selmenu2_ShadowTextPrint(0x80, 0x50, omDBGStrBuf, color[1], color[0]);
            } else {
                selmenu2_ShadowTextPrint(0x80, 0x50, omDBGStrBuf, color[0], 0);
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
                    sprintf(omDBGStrBuf, space->unk_0C, i);
                    break;
                case 1:
                    sprintf(omDBGStrBuf, space->unk_0C, selmenu2_playerCfg[i].pad,
                            selmenu2_padCfgStrTbl[selmenu2_playerCfg[i].stat & 1]);
                    break;
                case 2:
                    sprintf(omDBGStrBuf, space->unk_0C, selmenu2_playerCfg[i].group);
                    break;
                case 3:
                    sprintf(omDBGStrBuf, space->unk_0C, selmenu2_comLevelStrTbl[selmenu2_playerCfg[i].cpu_difficulty]);
                    break;
                case 4:
                    sprintf(omDBGStrBuf, space->unk_0C, selmenu2_playerCfg[i].coin);
                    break;
                case 5:
                    sprintf(omDBGStrBuf, space->unk_0C, selmenu2_playerCfg[i].pad);
                    break;
            }
            switch (selmenu2_playerCfgSelF) {
                case 0:
                    if (j == 0) {
                        color = selmenu2_textColorTbl[0];
                        if (i == selmenu2_playerCfgPlayerPos) {
                            selmenu2_ShadowTextPrint(x, y, omDBGStrBuf, color[1], color[0]);
                        } else {
                            selmenu2_ShadowTextPrint(x, y, omDBGStrBuf, color[0], 0);
                        }
                    } else {
                        selmenu2_ShadowTextPrint(x, y, omDBGStrBuf, selmenu2_textColorTbl[1][0], 0);
                    }
                    break;
                case 1:
                    if (i == selmenu2_playerCfgPlayerPos) {
                        color = selmenu2_textColorTbl[0];
                        if (j == selmenu2_playerCfgOptionPos) {
                            selmenu2_ShadowTextPrint(x, y, omDBGStrBuf, color[1], color[0]);
                        } else {
                            selmenu2_ShadowTextPrint(x, y, omDBGStrBuf, color[0], 0);
                        }
                    } else {
                        selmenu2_ShadowTextPrint(x, y, omDBGStrBuf, selmenu2_textColorTbl[1][0], 0);
                    }
                    break;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        if (selmenu2_btnDownTbl[i] & 0x40) {
            obj->func = selmenu2_MenuObjMain;
            return;
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        switch (selmenu2_playerCfgSelF) {
            case 0:
                if (selmenu2_playerCfgPlayerPos < 2 && (selmenu2_btnDownTbl[i] & 1)) {
                    selmenu2_playerCfgPlayerPos = 4;
                } else if (selmenu2_playerCfgPlayerPos == 4 && (selmenu2_btnDownTbl[i] & 2)) {
                    selmenu2_playerCfgPlayerPos = 0;
                } else if (selmenu2_playerCfgPlayerPos == 4 && (selmenu2_btnDownTbl[i] & 4)) {
                    if (--GwSystem.current_board_index < 0) {
                        GwSystem.current_board_index = 0;
                    }
                } else if (selmenu2_playerCfgPlayerPos == 4 && (selmenu2_btnDownTbl[i] & 8)) {
                    if (++GwSystem.current_board_index > 0) {
                        GwSystem.current_board_index = 0;
                    }
                } else if (selmenu2_playerCfgPlayerPos != 4) {
                    if (selmenu2_btnDownTbl[i] & 0xC) {
                        selmenu2_playerCfgPlayerPos ^= 1;
                    } else if (selmenu2_btnDownTbl[i] & 3) {
                        selmenu2_playerCfgPlayerPos ^= 2;
                    }
                    if (selmenu2_btnDownTbl[i] & 0x20) {
                        obj->func = selmenu2_MenuObjMain;
                        return;
                    }
                    if (selmenu2_btnDownTbl[i] & 0x10) {
                        selmenu2_playerCfgSelF = 1;
                        return;
                    }
                    if (selmenu2_btnDownTbl[i] & 0x80) {
                        selmenu2_GroupShuffle();
                        selmenu2_PadShuffle();
                    }
                }
                break;
            case 1:
                if (selmenu2_btnDownTbl[i] & 1) {
                    if (--selmenu2_playerCfgOptionPos < 0) {
                        selmenu2_playerCfgOptionPos = 5;
                    }
                } else if (selmenu2_btnDownTbl[i] & 2) {
                    if (++selmenu2_playerCfgOptionPos >= 6) {
                        selmenu2_playerCfgOptionPos = 0;
                    }
                }
                if (selmenu2_btnDownTbl[i] & 8) {
                    switch (selmenu2_playerCfgOptionPos) {
                        case 0:
                            break;
                        case 1:
                            selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].stat ^= 1;
                            break;
                        case 2:
                            if (++selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].group >= 4) {
                                selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].group = 0;
                            }
                            break;
                        case 3:
                            if (++selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].cpu_difficulty >= 4) {
                                selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].cpu_difficulty = 0;
                            }
                            break;
                        case 4:
                            if (++selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].coin >= 1000) {
                                selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].coin = 0;
                            }
                            break;
                        case 5:
                            if (++selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].pad == 4) {
                                selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].pad = 0;
                            }
                            break;
                    }
                } else if (selmenu2_btnDownTbl[i] & 4) {
                    switch (selmenu2_playerCfgOptionPos) {
                        case 0:
                            break;
                        case 1:
                            selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].stat ^= 1;
                            break;
                        case 2:
                            if (selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].group == 0) {
                                selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].group = 3;
                            } else {
                                selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].group--;
                            }
                            break;
                        case 3:
                            if (selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].cpu_difficulty == 0) {
                                selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].cpu_difficulty = 3;
                            } else {
                                selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].cpu_difficulty--;
                            }
                            break;
                        case 4:
                            if (--selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].coin < 0) {
                                selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].coin = 999;
                            }
                            break;
                        case 5:
                            if (--selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].pad == 0xFF) {
                                selmenu2_playerCfg[selmenu2_playerCfgPlayerPos].pad = 3;
                            }
                            break;
                    }
                } else if (selmenu2_btnDownTbl[i] & 0x30) {
                    selmenu2_playerCfgSelF = 0;
                    selmenu2_playerCfgOptionPos = 0;
                    return;
                } else if (selmenu2_btnDownTbl[i] & 0x80) {
                    switch (selmenu2_playerCfgOptionPos) {
                        case 2:
                            selmenu2_GroupShuffle();
                            break;
                        case 5:
                            selmenu2_PadShuffle();
                            break;
                    }
                }
                break;
        }
    }
    sel = selmenu2_playerCfgPlayerPos;
    if (sel != 4) {
        cursorCol = sel % 2;
        cursorRow = sel / 2;
        x = cursorCol * 144;
        x += 40;
        y = cursorRow * 7;
        line = selmenu2_playerCfgOptionPos + 12;
        y += line;
        y++;
        y *= 8;
    } else {
        x = 0x80;
        y = 0x58;
    }
    espPosSet(selmenu2_cursorSpr, x - 4, y);
}

void selmenu2_MgNameRiseObjMain(omObjData *obj) {
    u32 x;
    s32 y;
    s32 shadowOfs = 12;
    // The comparison is folded away, but the join it leaves behind keeps textOfs in a register below.
    s32 textOfs = MIN(6, shadowOfs);
    s32 i;

    rand8();
    sprintf(omDBGStrBuf, selmenu2_menuTbl[selmenu2_page * 10 + selmenu2_selectPos].unk_0C);
    x = (320 - strlen(omDBGStrBuf) * 8) / 2;
    y = (selmenu2_selectPos + 10) * 9;
    if (y - selmenu2_mgNameRiseOfs > 48) {
        if (--selmenu2_sparkTimer == 0) {
            selmenu2_sparkSprTbl[selmenu2_sparkNum] = espEntry(selmenu2_sparkAnim, 0, 1);
            espAttrSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], HUSPR_ATTR_BG);
            espPriSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], 0x8000);
            espScaleSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], 0.75f, 0.75f);
            espSpeedSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], 8.0f);
            espPosSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], x, y - (u16)selmenu2_mgNameRiseOfs + textOfs + 8);
            espColorSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], 0xFF, 0xFF, 0xBE);
            selmenu2_sparkNum++;
            selmenu2_sparkSprTbl[selmenu2_sparkNum] = espEntry(selmenu2_sparkAnim, 0, 1);
            espAttrSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], HUSPR_ATTR_BG);
            espPriSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], 0x8000);
            espScaleSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], 0.75f, 0.75f);
            espSpeedSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], 8.0f);
            espPosSet(selmenu2_sparkSprTbl[selmenu2_sparkNum],
                      x + strlen(selmenu2_menuTbl[selmenu2_page * 10 + selmenu2_selectPos].unk_0C) * 8,
                      y - (u16)selmenu2_mgNameRiseOfs + textOfs + 8);
            espColorSet(selmenu2_sparkSprTbl[selmenu2_sparkNum], 0xFF, 0xFF, 0xBE);
            selmenu2_sparkNum++;
            selmenu2_sparkTimer = 4;
        }
        selmenu2_mgNameRiseOfs += 4;
        if (y < y - selmenu2_mgNameRiseOfs + shadowOfs) {
            shadowOfs = (y - selmenu2_mgNameRiseOfs + shadowOfs) - y;
        }
        if (y < y - selmenu2_mgNameRiseOfs + textOfs) {
            textOfs = (y - selmenu2_mgNameRiseOfs + textOfs) - y;
        }
        fontcolor = 9;
        print8(x, y - (u16)selmenu2_mgNameRiseOfs + shadowOfs, omDBGStrBuf);
        fontcolor = 13;
        print8(x, y - (u16)selmenu2_mgNameRiseOfs + textOfs, omDBGStrBuf);
    }
    for (i = 0; i < selmenu2_sparkNum; i++) {
        if (selmenu2_sparkSprTbl[i] != -1 && (espAnimStatGet(selmenu2_sparkSprTbl[i]) & 6)) {
            espKill(selmenu2_sparkSprTbl[i]);
            selmenu2_sparkSprTbl[i] = -1;
        }
    }
    x = (320 - strlen(omDBGStrBuf) * 8) / 2;
    fontcolor = 7;
    print8(x + 1, y + 1 - (u16)selmenu2_mgNameRiseOfs, omDBGStrBuf);
    fontcolor = 15;
    print8(x, y - (u16)selmenu2_mgNameRiseOfs, omDBGStrBuf);
}

void selmenu2_ChrSelObjInit(omObjData *obj) {
    obj->func = selmenu2_ChrSelObjMain;
}

void selmenu2_ChrSelObjMain(omObjData *obj) {
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

    if (selmenu2_exitF == 1) {
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            selmenu2_PlayerCfgCopy();
            GwSystem.minigame_index = selmenu2_menuTbl[selmenu2_page * 10 + selmenu2_selectPos].unk_02;
            GwSystem.current_player_index = 0;
            selMenuLastOvl = selmenu2_menuTbl[selmenu2_page * 10 + selmenu2_selectPos].unk_04;
            if (selMenuLastOvl >= 71) {
                omOvlCallEx(selMenuLastOvl, 0, OM_OVL_STAT_MG | OM_OVL_STAT_GFXBUF3);
            } else if (mgDataTbl[GwSystem.minigame_index - 1].minigameType != 6) {
                omOvlCallEx(inst, 0, OM_OVL_STAT_BOARD | OM_OVL_STAT_GFXBUF3);
            } else {
                omOvlCallEx(mgDataTbl[GwSystem.minigame_index - 1].overlay, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            }
        }
        return;
    }
    for (i = 0; i < 4; i++) {
        if (selmenu2_playerDoneF[i] == 1) {
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
                    if (selmenu2_chrUsedF[i] == 0) {
                        freeChars[count++] = i;
                    }
                }
                if (count == 1) {
                    GwPlayer[pads[index]].chr = freeChars[0];
                    selmenu2_chrUsedF[freeChars[0]] = 1;
                } else {
                    pick = rand8() % count;
                    GwPlayer[pads[index]].chr = freeChars[pick];
                    selmenu2_chrUsedF[freeChars[pick]] = 1;
                }
            }
        }
        WipeColorSet(0, 0, 0);
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        selmenu2_exitF = 1;
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
                    selmenu2_btnDownTbl[j] |= 0x10;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            sprintf(omDBGStrBuf, "------");
            selmenu2_ShadowTextPrint(i * 56 + 56, 144, omDBGStrBuf, 15, 7);
            continue;
        }
        Hu3DModelAttrSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], i * 420 - 650.0f - 60.0f + i * 40, -120.0f, 0.0f);
        Hu3DModelScaleSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], 2.0f, 2.0f, 2.0f);
        if (selmenu2_playerDoneF[i] == 1) {
            selmenu2_chrRotYTbl[i] = 0.0f;
        }
        Hu3DModelRotSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], 0.0f, selmenu2_chrRotYTbl[i], 0.0f);
        selmenu2_chrRotYTbl[i] += 1.0f;
        if (selmenu2_chrRotYTbl[i] >= 360.0f) {
            selmenu2_chrRotYTbl[i] -= 360.0f;
        }
        color = (selmenu2_playerDoneF[i] != 0) ? 15 : 12;
        textColor = color;
        sprintf(omDBGStrBuf, selmenu2_chrNameTbl[GwPlayer[i].chr]);
        selmenu2_ShadowTextPrint(i * 56 + 50 + i * 4, 144, omDBGStrBuf, textColor, color - 8);
        if ((selmenu2_btnDownTbl[i] & 0x10) && selmenu2_playerDoneF[i] == 0) {
            selmenu2_playerDoneF[i] = 1;
            Hu3DMotionModelSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], selmenu2_chrDecideMotTbl[GwPlayer[i].chr]);
            Hu3DMotionAttrSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], 1, 0);
            Hu3DMotionAttrSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], 2, 2);
            selmenu2_SePlay(2);
        } else if ((selmenu2_btnDownTbl[i] & 0x20) && selmenu2_playerDoneF[i] == 1) {
            selmenu2_playerDoneF[i] = 0;
            Hu3DMotionModelSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], selmenu2_chrIdleMotTbl[GwPlayer[i].chr]);
            Hu3DMotionAttrSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], 1, 0);
            Hu3DMotionAttrSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], 2, 2);
            selmenu2_SePlay(3);
        }
        if (selmenu2_playerDoneF[i] == 0) {
            if (selmenu2_btnDownTbl[i] & 4) {
                chr = GwPlayer[i].chr - 1;
                selmenu2_SePlay(0);
                while (TRUE) {
                    if (chr < 0) {
                        chr = 7;
                    }
                    if (selmenu2_chrUsedF[chr] == 0) {
                        break;
                    }
                    chr--;
                }
                selmenu2_chrUsedF[GwPlayer[i].chr] = 0;
                Hu3DModelAttrSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                GwPlayer[i].chr = chr;
                selmenu2_chrUsedF[GwPlayer[i].chr] = 1;
                selmenu2_chrRotYTbl[i] = 0.0f;
            } else if (selmenu2_btnDownTbl[i] & 8) {
                chr = GwPlayer[i].chr + 1;
                selmenu2_SePlay(0);
                while (TRUE) {
                    if (chr >= 8) {
                        chr = 0;
                    }
                    if (selmenu2_chrUsedF[chr] == 0) {
                        break;
                    }
                    chr++;
                }
                selmenu2_chrUsedF[GwPlayer[i].chr] = 0;
                Hu3DModelAttrSet(selmenu2_chrMdlTbl[GwPlayer[i].chr], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                GwPlayer[i].chr = chr;
                selmenu2_chrUsedF[GwPlayer[i].chr] = 1;
                selmenu2_chrRotYTbl[i] = 0.0f;
            }
        }
    }
}

void selmenu2_SePlay(u16 index) {
    HuAudFXVolSet(HuAudFXPlay(selmenu2_seTbl[index].fx), selmenu2_seTbl[index].vol);
}

void selmenu2_CursorMove(s16 dir) {
    s16 index = selmenu2_selectPos;

    do {
        index += dir;
        if (index >= 10) {
            index = 0;
        } else if (index < 0) {
            index = 9;
        }
    } while (selmenu2_menuTbl[selmenu2_page * 10 + index].available == 1);
    selmenu2_selectPos = index;
}

void selmenu2_PageMove(s16 dir) {
    u16 found = FALSE;
    s16 prevPage;
    s16 page;
    s32 i;

    prevPage = page = selmenu2_page;
    do {
        page += dir;
        if (page >= 8) {
            page = 0;
        } else if (page < 0) {
            page = 7;
        }
        for (i = 0; i < 10; i++) {
            if (selmenu2_menuTbl[page * 10 + i].available == 0) {
                found = TRUE;
                break;
            }
        }
    } while (!found);
    selmenu2_page = page;
    if (prevPage == -1) {
        selmenu2_selectPos = -1;
        selmenu2_CursorMove(1);
        selmenu2_selectPosBackupTbl[selmenu2_page] = selmenu2_selectPos;
    } else {
        selmenu2_selectPosBackupTbl[prevPage] = selmenu2_selectPos;
        selmenu2_selectPos = selmenu2_selectPosBackupTbl[selmenu2_page];
    }
}

void selmenu2_ShadowTextPrint(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4) {
    fontcolor = arg4;
    print8((arg0 + 1), (arg1 + 1), arg2);
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

void selmenu2_PlayerGroupSet(void) {
    s16 x = selmenu2_page;
    s16 y = selmenu2_selectPos;
    SelMenuPlayerGroups *groups = &selmenu2_playerGroupTbl[selmenu2_menuTbl[x * 10 + y].player_groups - 1];
    GW_PLAYER *player = selmenu2_playerCfg;

    player->group = groups->group[0];
    player++;
    player->group = groups->group[1];
    player++;
    player->group = groups->group[2];
    player++;
    player->group = groups->group[3];
}

void selmenu2_PlayerCfgCopy(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        GW_PLAYER *src = &selmenu2_playerCfg[i];
        GW_PLAYER *dst = &GwPlayer[i];

        dst->stat = src->stat;
        dst->group = src->group;
        dst->pad = src->pad;
        dst->cpu_difficulty = src->cpu_difficulty;
        dst->coin = src->coin;
    }
}

void selmenu2_GroupShuffle(void) {
    u8 groups[4];
    u8 used[4];
    s32 i;
    s32 r;

    for (i = 0; i < 4; i++) {
        groups[i] = selmenu2_playerCfg[i].group;
        used[i] = FALSE;
    }
    for (i = 0; i < 4; i++) {
        do {
            r = rand8() & 3;
        } while (used[r] == TRUE);
        used[r] = TRUE;
        selmenu2_playerCfg[i].group = groups[r];
    }
}

void selmenu2_PadShuffle(void) {
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
        selmenu2_playerCfg[i].pad = r;
    }
}
