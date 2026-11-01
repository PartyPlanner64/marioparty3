#ifndef _GAME_WINDOW_H
#define _GAME_WINDOW_H

#include "ultra64.h"

#define WINDOWS_MAX 16
#define TEXT_WINDOW_SPRITES_MAX 0x18
#define WINDOW_INPUT_RECORDS_MAX 32
#define WINDOW_INPUT_RECORD_FRAMES MAXCONTROLLERS

#define MAKE_MESSID(bank, mess) (((bank) << 16) + (mess))
#define MAKE_MESSID_PTR(ptr) ((u32)(ptr))

// Pass as the x/y message position to center the message in the window.
#define HUWIN_POS_CENTER -2

#define HUWIN_PLAYER_NONE 0
#define HUWIN_PLAYER_1 (1 << 0)
#define HUWIN_PLAYER_2 (1 << 1)
#define HUWIN_PLAYER_3 (1 << 2)
#define HUWIN_PLAYER_4 (1 << 3)
#define HUWIN_PLAYER_ALL 0xF

#define HUWIN_ATTR_NONE 0
#define HUWIN_ATTR_NOCANCEL (1 << 0) // B does not cancel a choice
#define HUWIN_ATTR_COMKEY (1 << 1) // input comes from the COM key queue
#define HUWIN_ATTR_SHOWSPACE (1 << 2) // spaces drawn as glyphs, page breaks clear without waiting
#define HUWIN_ATTR_DISPOFF (1 << 3)
#define HUWIN_ATTR_KEYLOCK (1 << 4) // ignore input at the final key wait
#define HUWIN_ATTR_MUTE (1 << 5) // window sound effects are silenced
#define HUWIN_ATTR_PAUSE (1 << 6) // window pauses along with the game
#define HUWIN_ATTR_BOLD (1 << 7)
#define HUWIN_ATTR_BUFDIRTY (1 << 8) // text buffer was written this frame
#define HUWIN_ATTR_INPUT (1 << 9) // input was accepted this frame
#define HUWIN_ATTR_PROCOFF (1 << 10) // window is not processed
#define HUWIN_ATTR_ALIGN_CENTER (1 << 11)
#define HUWIN_ATTR_VALIGN_CENTER (1 << 12)
#define HUWIN_ATTR_EX (1 << 13) // window created by HuWinExCreate
#define HUWIN_ATTR_OPEN (1 << 14)
#define HUWIN_ATTR_NOCURSORANIM (1 << 15)
#define HUWIN_ATTR_ALTDIGITS (1 << 16)
#define HUWIN_ATTR_OUTLINE (1 << 17)
#define HUWIN_ATTR_NOCR (1 << 18)
#define HUWIN_ATTR_MONOSPACE (1 << 19)

#define HUWIN_STAT_NONE 0
#define HUWIN_STAT_DRAWMES 1
#define HUWIN_STAT_KEYWAIT 2
#define HUWIN_STAT_CHOICE 5
#define HUWIN_STAT_KEYWAIT_CLEAR 6 // key wait, then clear the window

#define HUWIN_CHOICE_STAT_MES 0
#define HUWIN_CHOICE_STAT_SPR 1
#define HUWIN_CHOICE_STAT_DISABLED 2

typedef struct TextWindowSprite {
    /* 0x00 */ u8 stat; /* HUWIN_CHOICE_STAT_* */
    /* 0x01 */ char pad1[1];
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char padA[6];
} TextWindowSprite; /* size = 0x10 */

/* One input per controller, followed by the number of frames to repeat them. */
typedef s16 WindowInputRecord[MAXCONTROLLERS + 1];

typedef struct TextWindow {
    /* 0x000 */ u16 palette[16];
    /* 0x020 */ s8 stat; /* inferred */
    /* 0x021 */ u8 active_pad; /* low nibble: enabled inputs */
    /* 0x022 */ s8 mess_color;
    /* 0x023 */ s8 unk_23;
    /* 0x024 */ u8 unk_24; /* maybe part of unk20[9]? */
    /* 0x025 */ s8 speed;
    /* 0x026 */ s8 unk_26;
    /* 0x027 */ u8 unk_27;
    /* 0x028 */ u8 unk_28; /* maybe part of unk20[9]? */
    /* 0x029 */ s8 spacing_x;
    /* 0x02A */ u8 spacing_y;
    /* 0x02B */ char pad2B[1];
    /* 0x02C */ u8 unk_2C;
    /* 0x02D */ u8 backgroundRed;
    /* 0x02E */ u8 backgroundGreen;
    /* 0x02F */ u8 backgroundBlue;
    /* 0x030 */ s8 num_choices;
    /* 0x031 */ s8 choice;
    /* 0x032 */ u8 unk_32;
    /* 0x033 */ u8 mess_shadow_color;
    /* 0x034 */ u8 unk_34;
    /* 0x035 */ u8 tab_w;
    /* 0x036 */ char pad36[2]; /* maybe part of unk_35[3]? */
    /* 0x038 */ u32 attr;
    /* 0x03C */ u16 pos_x;
    /* 0x03E */ u16 pos_y;
    /* 0x040 */ s16 w;
    /* 0x042 */ s16 h;
    /* 0x044 */ s16 unk44;
    /* 0x046 */ s16 unk46;
    /* 0x048 */ u16 unk48;
    /* 0x04A */ u16 unk4A;
    /* 0x04C */ u16 mess_rect_x;
    /* 0x04E */ s16 mess_rect_y;
    /* 0x050 */ s16 mess_rect_w;
    /* 0x052 */ s16 mess_rect_h;
    /* 0x054 */ u16 mess_x;
    /* 0x056 */ u16 mess_y;
    /* 0x058 */ u16 unk58;
    /* 0x05A */ u16 unk5A;
    /* 0x05C */ s16 mess_time;
    /* 0x05E */ s16 unk5E;
    /* 0x060 */ s16 prio;
    /* 0x062 */ s16 unk62;
    /* 0x064 */ s16 unk64;
    /* 0x066 */ s16 unk66;
    /* 0x068 */ s16 unk68;
    /* 0x06A */ s16 cursor_sprite;
    /* 0x06C */ s16 group;
    /* 0x06E */ s16 sprite_id[22];
    /* 0x09A */ s16 unk_9A;
    /* 0x09C */ s16 cursorStartX;
    /* 0x09E */ s16 cursorStartY;
    /* 0x0A0 */ s16 cursorTargetX;
    /* 0x0A2 */ s16 cursorTargetY;
    /* 0x0A4 */ s16 unk_A4;
    /* 0x0A6 */ s16 push_key;
    /* 0x0A8 */ u16 input;
    /* 0x0AA */ s16 unk_AA;
    /* 0x0AC */ s8 insertionIndex;
    /* 0x0AD */ s8 usingStringIDBool[5];
    /* 0x0B2 */ s8 unk_B2[6];
    /* 0x0B8 */ void *insert_mess[5];
    /* 0x0CC */ u8 *mess;
    /* 0x0D0 */ void *unk_D0;
    /* 0x0D4 */ u8 unk_D4;
    /* 0x0D5 */ char padD5[3];
    /* 0x0D8 */ u8 *unk_D8;
    /* 0x0DC */ u8 *pixels;
    /* 0x0E0 */ void *unk_E0[3];
    /* 0x0EC */ f32 scaleX;
    /* 0x0F0 */ f32 scaleY;
    /* 0x0F4 */ TextWindowSprite choice_data[TEXT_WINDOW_SPRITES_MAX];
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ char pad278[4]; /* maybe part of unk276[3]? */
} TextWindow;                   /* size = 0x27C */

void HuWinInit(void);
s16 HuWinCreate(s16, s16, s16, s16, s32, s16);
void HuWinMesSet(s16, u32, s16, s16);
void HuWinInsertMesSet(s16 win_id, u32 arg1, s8 arg2);
void HuWinMesSpeedSet(s16, s32);
void HuWinPriSet(s16, s32);
void HuWinBGTPLvlSet(s16, s16);
void HuWinMesColSet(s16, s32);
void HuWinMesPalSet(s16, u8, u8, u8, u8);
s32 HuWinCR(TextWindow *window);
s32 func_8005CD38_main(TextWindow *window);
void HuWinHomeClear(s16);
void func_8005DD54_main(TextWindow *window);
void func_8005E1A8_main(s16, s16);
void HuWinKill(s16);
void HuWinAllKill(void);
void _HuWinComKeySet(s16, s16, s16, s16, s16);
void HuWinBGColSet(s16, s32, s32, s32);
void HuWinDispOff(s16);
void HuWinDispOn(s16);
void HuWinInsertMesSizeGet(u32 mesg, s16);
void HuWinMesMaxSizeGet(s16 count, s16 *size, ...);
void HuWinExAnimIn(s16);
void func_80060144_main(s16 obj);
void func_800601BC_main(s16, u32, s8);
s16 HuWinAnimSet(s16 win_id, u32 spriteMainFsPair, s16 arg2, s16 arg3, s16 arg4);
TextWindow *HuWinGet(s16 win_id);
void HuWinPosSet(s16, s16, s16);
void HuWinCenterPosSet(s16, s16, s16);
void HuWinProc(void);
void HuWinComKeyReset(void);
void GetMesMaxSizeSub(u32);

extern TextWindow *winData;
extern WindowInputRecord winComKeyBuf[WINDOW_INPUT_RECORDS_MAX];

void func_8005B040_main(u8 *pixels, s16 width, s16 height);
void func_8005B238_main(u8 *pixels, s16 width, s16 height);
s16 func_8005B5EC_main(u8 *str);
s16 func_8005B614_main(s32 arg0);
void func_8005B63C_main(s16 winId, s32 arg1, s32 arg2);
s32 func_8005B68C_main(s16 win_id);
void HuWinSprKill(s16 arg0, s16 arg1);
s16 func_8005B974_main(s16 winId, u32 spriteMainFsPair, s16 x, s16 y, s16 arg4);
s16 HuWinSprIDGet(s16 arg0, s16 arg1);
void HuWinScaleSet(s16 winId, f32 scaleX, f32 scaleY);
void func_8005BBC0_main(s16 winId, f32 scaleX, f32 scaleY);
void HuWinZRotSet(s16 winId, f32 arg1);
void func_8005BF70_main(s16 winId, s32 arg1);
void func_8005C154_main(s16 winId, s32 red, s32 green, s32 blue);
s32 HuWinDrawMes(s16 winId);
s32 func_8005CC18_main(TextWindow *window);
s32 func_8005CC3C_main(TextWindow *window, s16 advance);
void func_8005CD84_main(TextWindow *window);
void _HuWinHomeClear(TextWindow *window);
void HuWinKeyWaitEntry(s16 winId);
void HuWinKeyWaitIconOff(s16 winId);
s32 HuWinSpcFontEntry(s16 winId, s16 icon);
void func_8005D2D4_main(s16 win_id);
void HuWinCancelCRSet(void);
void charEntry(s16, u8, u8, s16, s16);
void func_8005D83C_main(s16 winId, s16 x, s16 y, s16 width, s16 height);
void *func_8005DAA4_main(s16 winId);
void func_8005DC94_main(s16 winId);
void func_8005DD14_main(s16 winId);
s16 HuWinStatGet(s16 winId);
s32 HuWinChoiceGet(s16 winId, s16 arg1, s32 arg2);
s32 HuWinChoice(s16);
void func_8005EEE4_main(TextWindow *window, TextWindowSprite *sprite);
void HuWinComKeyWait(s16 up, s16 down, s16 left, s16 right, u8 frames);
void HuWinComKeySet(s16 up, s16 down, s16 left, s16 right);
void HuWinComKeyGet(s16 *inputs);
s32 HuWinActivePadGet(TextWindow *window);
u8 func_8005FA90_main(u8 *arg0);
void func_8005FBA4_main(u8 *buffer, s32 message);
void HuWinActivePlayerSet(s16 winId, s16 arg1);
void func_800600C0_main(s16 winId, s32 arg1);
void HuWinChoiceDisable(s32 winId, s16 spriteIndex);
s16 HuWinChoiceNowGet(s32 winId);
void func_80060174_main(u8 *str, u8 *buffer);
void func_80060290_main(u32 str, s16 index);
void func_8006034C_main(s16 winId, s16 arg1, u8 arg2);
void func_80060388_main(s8 arg0);
void HuWinMesMaxSizeBetGet(s16 *arg0, s16 arg1, s16 arg2);
void HuWinMesSizeCancelCRSet(void);
void HuWinPushKeySet(s32 winId, s16 arg1);
s32 func_80060880_main(s32 x, s32 y, s32 frameIndex);
void func_80060C14_main(s32 winId, s32 playSound);
void func_80060DEC_main(s32 win_id);
void func_80060EA8_main(s32 winId, s32 playSound);
void func_8006105C_main(s32 winId, s32 alpha);
void HuWinExCleanup(s16 win_id);
void func_80061100_main(s16 win_id, s32 priority);
s32 HuWinExCreate(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5);
void func_800615B8_main(s16 winId, s32 opening);
void HuWinExAnimPopIn(s16 winId, s16 arg1);
void HuWinExAnimOut(s16 arg0, s16 arg1);

#endif
