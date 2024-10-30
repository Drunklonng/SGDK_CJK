#include "main.h"

int main(bool hardReset)
{
    basicInit();
    while (TRUE)
    {
        switch (currentState)
        {
            case STATE_OP:
            {
                processStateOP();
                break;
            }
            case STATE_TITLE:
            {
                processStateTitle();
                break;
            }
            case STATE_ED:
            {
                processStateED();
                break;
            }
            default:
            {
                break;
            }
        } 
    }
    return 0;
}

void processStateOP()
{
    currentState = STATE_TITLE;
    void myJoyHandler(u16 joy, u16 changed, u16 state)
    {
        if (joy == JOY_1 && state & BUTTON_BTN)
        {
            currentState = STATE_TITLE;
        }
    }
    JOY_setEventHandler(&myJoyHandler);
    PAL_fadeIn(0, 63, palette_all.data, 8, TRUE);
    while (currentState == STATE_OP)
    {
        SYS_doVBlankProcess();
    } 
    clearScreen();
}

void Test_drawTextCJK()
{
    VDP_clearPlane(BG_A, TRUE);
    VDP_drawTextCJK(BG_A, PAL2, 4, "SGDK", 64, 12, 8, 20);
    VDP_drawTextCJK(BG_A, PAL1, 4, getString(0), 128, 12, 10, 20);
    VDP_drawTextCJK(BG_A, PAL0, 4, getString(1), 192, 12, 12, 20);
    VDP_drawTextCJK(BG_A, PAL3, 0, "\e\x01\e\x02\e\x03\e\x04\n\a\x01\a\x02\a\x03\a\x04\a\x05\a\x06\n\r9\b\a\x07\a\x08\a\x09\a\x0a\a\x0b\a\x0c", 256, 12, 14, 20);
    VDP_drawTextCJK(BG_A, PAL0, 0, "\f1\rd\b\x83\x81\rb\x83\x4B\r9\b\x83\x68\r7\x83\x89\r5\b\x83\x43\r3\x83\x75", 384, 12, 20, 20);
}

void switchLanguage()
{
    u8 lang = language + 1;
    if (lang > 5)
    {
        lang = 0;
    }
    setLanguage(lang);
}

void processStateTitle()
{
    Test_drawTextCJK();
    void myJoyHandler(u16 joy, u16 changed, u16 state)
    {
        if (state & BUTTON_ALL)
        {
            switchLanguage();
            Test_drawTextCJK();
        }
    }
    JOY_setEventHandler(&myJoyHandler);
    PAL_fadeIn(0, 63, palette_all.data, 8, TRUE);
    while (currentState == STATE_TITLE)
    {
        SYS_doVBlankProcess();
    }
    clearScreen();
}

void processStateED()
{
    PAL_fadeIn(0, 63, palette_all.data, 8, TRUE);
    while (currentState == STATE_ED)
    {
        SYS_doVBlankProcess();
    }
    clearScreen();
}
