#ifndef _GAME_WINDOW_H
#define _GAME_WINDOW_H

#include "ultra64.h"

#define WINDOWS_MAX 16
#define TEXT_WINDOW_SPRITES_MAX 0x18

#define MAKE_MESSID(bank, mess) (((bank) << 16)+(mess))
#define MAKE_MESSID_PTR(ptr) ((u32)(ptr))

typedef struct TextWindowSprite {
    /* 0x00 */ u8 unk_00;                           /* 0 = free, 1 = active, 2 = disabled */
    /* 0x01 */ char pad1[1];
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char padA[6];
} TextWindowSprite;                                 /* size = 0x10 */

typedef struct TextWindow {
    /* 0x000 */ u8 unk_00;
    /* 0x001 */ char pad1[3];                       /* maybe part of unk_00[4]? */
    /* 0x004 */ s8 unk_04;
    /* 0x005 */ u8 unk_05;
    /* 0x006 */ char pad6[0xA];                     /* maybe part of unk_05[0xB]? */
    /* 0x010 */ u8 unk_10;
    /* 0x011 */ char pad11[7];                      /* maybe part of unk_10[8]? */
    /* 0x018 */ s16 unk_18;
    /* 0x01A */ s16 unk_1A;
    /* 0x01C */ char pad1C[4];                      /* maybe part of unk_1A[3]? */
    /* 0x020 */ s8 unk20;                           /* inferred */
    /* 0x021 */ u8 unk21;                           /* low nibble: enabled inputs */
    /* 0x022 */ s8 unk_22;
    /* 0x023 */ s8 unk_23;
    /* 0x024 */ char pad24[1];                      /* maybe part of unk20[9]? */
    /* 0x025 */ s8 unk_25;
    /* 0x026 */ s8 unk_26;
    /* 0x027 */ char pad27[1];                      /* maybe part of unk20[9]? */
    /* 0x028 */ u8 unk_28;                          /* maybe part of unk20[9]? */
    /* 0x029 */ s8 unk_29;
    /* 0x02A */ u8 unk_2A;
    /* 0x02B */ char pad2B[1];
    /* 0x02C */ s16 unk_2C;
    /* 0x02E */ s16 unk_2E;
    /* 0x030 */ s8 unk_30;                      /* maybe part of unk_2E[3]? */
    /* 0x031 */ s8 unk_31;
    /* 0x032 */ s16 unk_32;
    /* 0x034 */ u8 unk_34;
    /* 0x035 */ u8 unk_35;
    /* 0x036 */ char pad36[2];                      /* maybe part of unk_35[3]? */
    /* 0x038 */ u32 unk_38;
    /* 0x03C */ u16 unk3C;
    /* 0x03E */ u16 unk3E;
    /* 0x040 */ char pad40[8];                      /* maybe part of unk3E[5]? */
    /* 0x048 */ u16 unk48;
    /* 0x04A */ u16 unk4A;
    /* 0x04C */ u16 unk4C;
    /* 0x04E */ s16 unk4E;
    /* 0x050 */ s16 unk50;
    /* 0x052 */ s16 unk52;
    /* 0x054 */ u16 unk54;
    /* 0x056 */ u16 unk56;
    /* 0x058 */ char pad58[6];                      /* maybe part of unk56[5]? */
    /* 0x05E */ s16 unk5E;
    /* 0x060 */ char pad60[2];
    /* 0x062 */ s16 unk62;
    /* 0x064 */ s16 unk64;
    /* 0x066 */ char pad66[6];                      /* maybe part of unk64[4]? */
    /* 0x06C */ s16 unk_6C;
    /* 0x06E */ s16 unk_6E[0xC];
    /* 0x086 */ char pad86[0x20];                   /* maybe part of unk_6E[2]? */
    /* 0x0A6 */ s16 unk_A6;
    /* 0x0A8 */ char padA8[2];
    /* 0x0AA */ s16 unk_AA;
    /* 0x0AC */ char padAC[1];
    /* 0x0AD */ s8 usingStringIDBool[5];
    /* 0x0B2 */ s8 unk_B2[6];
    /* 0x0B8 */ void *unk_B8[4];
    /* 0x0C8 */ char padC8[0x2C];
    /* 0x0F4 */ TextWindowSprite unk_F4[TEXT_WINDOW_SPRITES_MAX];
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ char pad278[4];                     /* maybe part of unk276[3]? */
} TextWindow;                                       /* size = 0x27C */

void func_8005A6B0_main(void);
s16 func_8005A968_main(s16, s16, s16, s16, s32, s16);
void func_8005B43C_main(s16, s32, s32, s32);
void func_8005B6BC_main(s16 win_id, u32 arg1, s8 arg2);
void func_8005BDFC_main(s16, s32);
void func_8005BE30_main(s16, s32);
void func_8005BEE0_main(s16, s16);
void func_8005C02C_main(s16, s32);
void func_8005C060_main(s16, s32, s32, s32, s32);
s32 func_8005CCF0_main(TextWindow *window);
s32 func_8005CD38_main(TextWindow *window);
void func_8005D294_main(s16);
void func_8005E1A8_main(s16, s16);
void func_8005F364_main(s16);
void func_8005F524_main(void);
void func_8005FBF8_main(s16, s32, s32, s32);
void func_8005FE90_main(s16);
void func_8005FFA8_main(s16);
void func_8006022C_main(u32 mesg, s16);
void func_80060394_main(s32, s16*, s32);
void func_80061388_main(s16);
void func_80060144_main(s16 obj);
void *func_800364DC_main(void *arg0);
void func_800365E8_main(void *ptr);
s16 func_8005B7B8_main(s16 win_id, u32 spriteMainFsPair, s16 arg2, s16 arg3, u16 arg4);
TextWindow* func_8005BA28_main(s16 win_id);
void func_8005BA90_main(s16, s16, s16);
void func_8005BCA4_main(s16, s16, s16);
void func_8005DDDC_main(void);
void func_8005F904_main(void);
void func_800605A4_main(u32);

extern TextWindow* D_800CC69C_main;

#endif
