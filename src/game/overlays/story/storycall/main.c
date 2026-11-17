#include "common.h"

extern u8 storySceneNo;

void storycall_ObjectSetup(void) {
    s32 scene = storySceneNo;

    omInitObjMan(10, 10);
    switch (scene) {
        case 1:
            omOvlGotoEx(opening, 1, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
            break;
        case 3:
            GwPlayer[0].coin = 0;
            omOvlGotoEx(mstory1, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 5:
            GwPlayer[0].coin = 1;
            omOvlGotoEx(mstory1, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 7:
            GwPlayer[0].coin = 2;
            omOvlGotoEx(mstory1, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 15:
            GwPlayer[0].coin = 0;
            omOvlGotoEx(mstory2, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 2:
            GwPlayer[0].coin = 1;
            omOvlGotoEx(mstory2, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 4:
            GwPlayer[0].coin = 2;
            omOvlGotoEx(mstory2, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 6:
            GwPlayer[0].coin = 3;
            omOvlGotoEx(mstory2, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 8:
            GwPlayer[0].coin = 4;
            omOvlGotoEx(mstory2, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 12:
            GwPlayer[0].coin = 0;
            omOvlGotoEx(mstory3, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 10:
            GwPlayer[0].coin = 1;
            omOvlGotoEx(mstory3, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 13:
            GwPlayer[0].coin = 0;
            omOvlGotoEx(mstory4, 0, OM_OVL_STAT_DUEL | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
            break;
        case 14:
            GwPlayer[0].coin = 1;
            omOvlGotoEx(mstory4, 0, OM_OVL_STAT_DUEL | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
            break;
        case 9:
            GwPlayer[0].coin = 0;
            omOvlGotoEx(mstory5, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        case 11:
            GwPlayer[0].coin = 1;
            omOvlGotoEx(mstory5, 0, OM_OVL_STAT_MG | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            break;
        default:
            omOvlReturnEx(1);
            break;
    }
}
