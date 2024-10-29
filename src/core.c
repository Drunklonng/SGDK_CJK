#include "main.h"

void basicInit()
{
    VDP_setScreenWidth320();
    JOY_init();
    SPR_init();
    PAL_fadeOutAll(8, FALSE);
    setLanguage(zh_CN);
    currentState = STATE_OP;
}

void clearScreen()
{
    PAL_fadeOutAll(8, FALSE);
    JOY_init();
    SPR_init();
    VDP_clearPlane(BG_A, TRUE);
    VDP_clearPlane(BG_B, TRUE);
    SYS_doVBlankProcess();
}
