#include "main.h"
#include "localization/zh_CN.h"
#include "localization/zh_HK.h"
#include "localization/ja_JP.h"
#include "localization/ko_KR.h"
#include "localization/en_US.h"
#include "localization/ru_RU.h"


const u32 backColors[16] = {
    0x00000000, 0x11111111, 0x22222222, 0x33333333,
    0x44444444, 0x55555555, 0x66666666, 0x77777777,
    0x88888888, 0x99999999, 0xAAAAAAAA, 0xBBBBBBBB,
    0xCCCCCCCC, 0xDDDDDDDD, 0xEEEEEEEE, 0xFFFFFFFF};

const u32 maskColors[16][8] ={{0X0000000f, 0X000000f0, 0X00000f00, 0X0000f000, 0X000f0000, 0X00f00000, 0X0f000000, 0Xf0000000},
                            {0X0000000e, 0X000000e0, 0X00000e00, 0X0000e000, 0X000e0000, 0X00e00000, 0X0e000000, 0Xe0000000},
                            {0X0000000d, 0X000000d0, 0X00000d00, 0X0000d000, 0X000d0000, 0X00d00000, 0X0d000000, 0Xd0000000},
                            {0X0000000c, 0X000000c0, 0X00000c00, 0X0000c000, 0X000c0000, 0X00c00000, 0X0c000000, 0Xc0000000},
                            {0X0000000b, 0X000000b0, 0X00000b00, 0X0000b000, 0X000b0000, 0X00b00000, 0X0b000000, 0Xb0000000},
                            {0X0000000a, 0X000000a0, 0X00000a00, 0X0000a000, 0X000a0000, 0X00a00000, 0X0a000000, 0Xa0000000},
                            {0X00000009, 0X00000090, 0X00000900, 0X00009000, 0X00090000, 0X00900000, 0X09000000, 0X90000000},
                            {0X00000008, 0X00000080, 0X00000800, 0X00008000, 0X00080000, 0X00800000, 0X08000000, 0X80000000},
                            {0X00000007, 0X00000070, 0X00000700, 0X00007000, 0X00070000, 0X00700000, 0X07000000, 0X70000000},
                            {0X00000006, 0X00000060, 0X00000600, 0X00006000, 0X00060000, 0X00600000, 0X06000000, 0X60000000},
                            {0X00000005, 0X00000050, 0X00000500, 0X00005000, 0X00050000, 0X00500000, 0X05000000, 0X50000000},
                            {0X00000004, 0X00000040, 0X00000400, 0X00004000, 0X00040000, 0X00400000, 0X04000000, 0X40000000},
                            {0X00000003, 0X00000030, 0X00000300, 0X00003000, 0X00030000, 0X00300000, 0X03000000, 0X30000000},
                            {0X00000002, 0X00000020, 0X00000200, 0X00002000, 0X00020000, 0X00200000, 0X02000000, 0X20000000},
                            {0X00000001, 0X00000010, 0X00000100, 0X00001000, 0X00010000, 0X00100000, 0X01000000, 0X10000000},
                            {0X00000000, 0X00000000, 0X00000000, 0X00000000, 0X00000000, 0X00000000, 0X00000000, 0X00000000}};

const u8 *BIN_FONT_CJK[5] = {&BIN_FONT_UTF8, &BIN_FONT_JIS, &BIN_FONT_GBK, &BIN_FONT_KSC, &BIN_FONT_BIG5};


char *getStringEx(u8 lang, u8 index)
{
    switch (lang)
    {
        case zh_CN:
        {
            return string_zh_CH[index];
            break;
        }
        case zh_HK:
        {
            return string_zh_HK[index];
            break;
        }
        case ja_JP:
        {
            return string_ja_JP[index];
            break;
        }
        case ko_KR:
        {
            return string_ko_KR[index];
            break;
        }
        case ru_RU:
        {
            return string_ru_RU[index];
            break;
        }
        default:
        {
            return string_en_US[index];
            break;
        }
    }
}

char *getString(u8 index)
{
    return getStringEx(language, index);
}

void setLanguage(u8 lang)
{
    switch (lang)
    {
        case zh_CN:
        {
            codePage = CP936;
            break;
        }
        case zh_HK:
        {
            codePage = CP950;
            break;
        }
        case ja_JP:
        {
            codePage = CP932;
            break;
        }
        case ko_KR:
        {
            codePage = CP949;
            break;
        }
        default:
        {
            codePage = CP65001;
            break;
        }
    }
    language = lang;
}

u32 set4Bit(u32 x, u8 bit, u8 color)
{
    return SET_4BIT_MASK(x,maskColors[color][bit]);
}

int getFontIndexUTF8(u8 big, u8 little)
{
    int index = (big - 194) * 64 + little - 128;
    return BIN_DEFAULT_UTF8[index * 2 + 1] * 256 + BIN_DEFAULT_UTF8[index * 2];
}

int getFontIndexUTF8Multi(u8 first, u8 second, u8 third)
{
    int index = (first - 224) * 64 * 64 + (second - 128) * 64 + third - 128;
    if (index > 40767)
    {
        index -= 29056;
    }
    return BIN_DEFAULT_UTF8[index * 2 + 1] * 256 + BIN_DEFAULT_UTF8[index * 2];
}

int getFontIndexGBK(u8 big, u8 little)
{
    if (little > 127)
    {
        little--;
    }
    int index = (big - 129) * 190 + little - 64;
    return BIN_DEFAULT_GBK[index * 2 + 1] * 256 + BIN_DEFAULT_GBK[index * 2];
}

int getFontIndexBIG5(u8 big, u8 little)
{
    if (little > 127)
    {
        little -= 34;
    }
    int index = (big - 161) * 157 + little - 64;
    return BIN_DEFAULT_BIG5[index * 2 + 1] * 256 + BIN_DEFAULT_BIG5[index * 2];
}

int getFontIndexJIS(u8 big, u8 little)
{
    if (little > 127)
    {
        little--;
    }
    int index = (big - 129) * 188 + little - 64;
    return BIN_DEFAULT_JIS[index * 2 + 1] * 256 + BIN_DEFAULT_JIS[index * 2];
}

int getFontIndexKSC(u8 big, u8 little)
{
    if (little > 127)
    {
        little-=12;
    }
    int index = (big - 129) * 180 + little - 65;
    return BIN_DEFAULT_KSC[index * 2 + 1] * 256 + BIN_DEFAULT_KSC[index * 2];
}

int getFontIndexCJK(u8 cp, u8 big, u8 little)
{
    switch (cp)
    {
        case CP932:
        {
            return getFontIndexJIS(big, little);
        }
        case CP936:
        {
            return getFontIndexGBK(big, little);
        }
        case CP949:
        {
            return getFontIndexKSC(big, little);
        }
        case CP950:
        {
            return getFontIndexBIG5(big, little);
        }
        return 0;
    }
}

void VDP_drawTextCJK(VDPPlane plane, u8 palette, u8 backColor, unsigned char *text, int tileIndex, u8 x, u8 y, u8 w)
{
    u32 backTile[8];
    u32 tile[2][3][8];
    int tileNum = 1;
    int index = 0;
    int fontIndex;
    u8 textColor = 0;
    u8 line = 0;
    u8 pos = 0;
    u8 num = 0;
    u8 byte = 0;
    u8 type = TYPE_ASCII;
    u8 functionCode = CHARACTER;
    int cp = codePage;
    w = w - w % 3;
    for (u8 n = 0; n < 8; n++)
    {
        backTile[n] = backColors[backColor];
    }
    VDP_loadTileData(backTile, tileIndex, 1, DMA);
    while (text[index] != 0)
    {
        if (byte == 0)
        {
            if (text[index] >= 128)
            {
                if (cp == CP65001)
                {
                    if (text[index + 1] > 223)
                    {
                        fontIndex = getFontIndexUTF8Multi(text[index], text[index + 1], text[index + 2]);
                        index++;
                    }
                    else
                    {
                        fontIndex = getFontIndexUTF8(text[index], text[index + 1]);
                    }
                    byte = 1;
                    type = TYPE_UTF8;
                    index++;
                }
                else
                {
                    if (pos + 1 < w / 3 * 4)
                    {
                        fontIndex = getFontIndexCJK(cp, text[index], text[index + 1]);
                        byte = 2;
                        type = TYPE_ANSI;
                    }
                    else
                    {
                        functionCode = ASCII_NUL;
                        fontIndex = 0;
                        byte = 1;
                        type = TYPE_ASCII;
                        index--;
                    }
                }
            }
            else
            {
                if (text[index] > 32 && text[index] < 127)
                {
                    fontIndex = text[index] - 32;
                    byte = 1;
                    type = TYPE_ASCII;
                }
                else if (text[index] == ASCII_EX)
                {
                    fontIndex = text[index + 1];
                    byte = 2;
                    type = TYPE_EXTRA;
                }
                else if (text[index] == ASCII_EMOJI)
                {
                    fontIndex = text[index + 1];
                    byte = 2;
                    type = TYPE_EMOJI;
                }
                else 
                {
                    functionCode = text[index];
                    fontIndex = 0;
                    byte = 1;
                    type = TYPE_ASCII;
                }
            }
        }
        if (pos % 4 == 0 && functionCode != ASCII_BS)
        {
            for (u8 n1 = 0; n1 < 2; n1++)
            {
                for (u8 n2 = 0; n2 < 3; n2++)
                {
                    for (u8 n3 = 0; n3 < 8; n3++)
                    {
                        tile[n1][n2][n3] = backTile[n3];
                    }
                }
            }
        }
        if (fontIndex > 0)
        {
            u8 groupBitX = pos % 4 * 6;
            u8 byteBitX = groupBitX % 8;
            u8 xi = (groupBitX - byteBitX) / 8;
            if (type == TYPE_ANSI)
            {
                for (u8 fy = 0; fy < 12; fy++)
                {
                    u8 yi = fy < 6 ? 0 : 1;
                    u8 bitY = fy < 6 ? fy + 2 : fy - 6;
                    if (byte == 2)
                    {
                        for (u8 fx = 0; fx < 6; fx++)
                        {
                            u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                            if (GET_BIT(BIN_FONT_CJK[cp][fontIndex * 24 + fy * 2 + 1], 5 - fx) > 0)
                            {
                                tile[yi][xi + group][bitY] = set4Bit(tile[yi][xi + group][bitY], 7 - (byteBitX + fx - group * 8), textColor);
                            }
                        }
                    }
                    else
                    {
                        for (u8 fx = 0; fx < 6; fx++)
                        {
                            u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                            if (GET_BIT(BIN_FONT_CJK[cp][fontIndex * 24 + fy * 2], 7 - fx) > 0)
                            {
                                tile[yi][xi + group][bitY] = set4Bit(tile[yi][xi + group][bitY], 7 - (byteBitX + fx - group * 8), textColor);
                            }
                        }
                    }
                }
                if (functionCode == ASCII_DEL)
                {
                    for (u8 fx = 0; fx < 6; fx++)
                    {
                        u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                        tile[1][xi + group][0] = set4Bit(tile[1][xi + group][0], 7 - (byteBitX + fx - group * 8), textColor);
                    }
                    if (byte == 1)
                    {
                        functionCode = CHARACTER;
                    }
                }
            }
            else if (type == TYPE_EXTRA)
            {
                for (u8 fy = 0; fy < 12; fy++)
                {
                    u8 yi = fy < 6 ? 0 : 1;
                    u8 bitY = fy < 6 ? fy + 2 : fy - 6;
                    if (byte == 2)
                    {
                        for (u8 fx = 0; fx < 6; fx++)
                        {
                            u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                            if (GET_BIT(BIN_FONT_EXTRA[fontIndex * 24 + fy * 2 + 1], 5 - fx) > 0)
                            {
                                tile[yi][xi + group][bitY] = set4Bit(tile[yi][xi + group][bitY], 7 - (byteBitX + fx - group * 8), textColor);
                            }
                        }
                    }
                    else
                    {
                        for (u8 fx = 0; fx < 6; fx++)
                        {
                            u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                            if (GET_BIT(BIN_FONT_EXTRA[fontIndex * 24 + fy * 2], 7 - fx) > 0)
                            {
                                tile[yi][xi + group][bitY] = set4Bit(tile[yi][xi + group][bitY], 7 - (byteBitX + fx - group * 8), textColor);
                            }
                        }
                    }
                }
                if (functionCode == ASCII_DEL)
                {
                    for (u8 fx = 0; fx < 6; fx++)
                    {
                        u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                        tile[1][xi + group][0] = set4Bit(tile[1][xi + group][0], 7 - (byteBitX + fx - group * 8), textColor);
                    }
                    if (byte == 1)
                    {
                        functionCode = CHARACTER;
                    }
                }
            }
            else if (type == TYPE_EMOJI)
            {
                for (u8 fy = 0; fy < 12; fy++)
                {
                    u8 yi = fy < 6 ? 0 : 1;
                    u8 bitY = fy < 6 ? fy + 2 : fy - 6;
                    if (byte == 2)
                    {
                        for (u8 fx = 0; fx < 6; fx++)
                        {
                            u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                            u8 emojiColor = BIN_FONT_EMOJI[fontIndex * 72 + fy * 6 + (fx - fx % 2) / 2];
                            if (fx % 2 > 0)
                            {
                                emojiColor = emojiColor << 4;
                            }
                            emojiColor = emojiColor >> 4;
                            if (emojiColor > 0)
                            {
                                tile[yi][xi + group][bitY] = set4Bit(tile[yi][xi + group][bitY], 7 - (byteBitX + fx - group * 8), 15 - emojiColor);
                            }
                        }
                    }
                    else
                    {
                        for (u8 fx = 0; fx < 6; fx++)
                        {
                            u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                            u8 emojiColor = BIN_FONT_EMOJI[fontIndex * 72 + fy * 6 + (fx - fx % 2) / 2 + 3];
                            if (fx % 2 > 0)
                            {
                                emojiColor = emojiColor << 4;
                            }
                            emojiColor = emojiColor >> 4;
                            if (emojiColor > 0)
                            {
                                tile[yi][xi + group][bitY] = set4Bit(tile[yi][xi + group][bitY], 7 - (byteBitX + fx - group * 8), 15 - emojiColor);
                            }
                        }
                    }
                }
            }
            else
            {
                if (type == TYPE_UTF8)
                {
                    for (u8 fy = 0; fy < 12; fy++)
                    {
                        u8 yi = fy < 4 ? 0 : 1;
                        u8 bitY = fy < 4 ? fy + 4 : fy - 4;
                        for (u8 fx = 0; fx < 6; fx++)
                        {
                            u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                            if (GET_BIT(BIN_FONT_UTF8[fontIndex * 12 + fy], 5 - fx) > 0)
                            {
                                tile[yi][xi + group][bitY] = set4Bit(tile[yi][xi + group][bitY], 7 - (byteBitX + fx - group * 8), textColor);
                            }
                        }
                    }
                }
                else
                {
                    for (u8 fy = 0; fy < 12; fy++)
                    {
                        u8 yi = fy < 4 ? 0 : 1;
                        u8 bitY = fy < 4 ? fy + 4 : fy - 4;
                        for (u8 fx = 0; fx < 6; fx++)
                        {
                            u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                            if (GET_BIT(BIN_FONT_ASCII[fontIndex * 12 + fy], 5 - fx) > 0)
                            {
                                tile[yi][xi + group][bitY] = set4Bit(tile[yi][xi + group][bitY], 7 - (byteBitX + fx - group * 8), textColor);
                            }
                        }
                    }
                }
                if (functionCode == ASCII_DEL)
                {
                    for (u8 fx = 0; fx < 6; fx++)
                    {
                        u8 group = (byteBitX + fx) >= 8 ? 1 : 0;
                        tile[1][xi + group][2] = set4Bit(tile[1][xi + group][2], 7 - (byteBitX + fx - group * 8), textColor);
                    }
                    functionCode = CHARACTER;
                }
            }
            if (functionCode == ASCII_BS || functionCode == ASCII_FF)
            {
                functionCode = CHARACTER;
            }
            pos++;
        }
        else
        {
            switch (functionCode)
            {
            case ASCII_EX:
            {
                break;
            }
            case ASCII_BS:
            {
                if (pos % 4 == 0)
                {
                    tileNum -= 6;
                    num -= 3;
                }
                pos -= pos % 4;
                break;
            }
            case ASCII_HT:
            {
                pos += 8 - pos % 8;
                break;
            }
            case ASCII_VT:
            {
                if (pos % 8 > 0)
                {
                    pos -= pos % 8;
                }
                else
                {
                    pos -= 8;
                }
                break;
            }
            case ASCII_LF:
            {
                pos = w / 3 * 4;
                break;
            }
            case ASCII_FF:
            {
                u8 temp = text[index + 1];
                if (temp >= 48 && temp <= 52)
                {
                    cp = temp - 48;
                    index++;
                }
                else
                {
                    cp = codePage;
                }
                break;
            }
            case ASCII_COLOR:
            {
                u8 temp = text[index + 1];
                if (temp >= 48 && temp <= 57)
                {
                    textColor = temp - 48;
                    index++;
                }
                else if (temp >= 97 && temp <= 102)
                {
                    textColor = temp - 97 + 10;
                    index++;
                }
                else
                {
                    textColor = 0;
                }
                break;
            }
            case ASCII_NUL:
            case ASCII_SP:
            {
                pos++;
                break;
            }
            default:
            {
                break;
            }
            }
        }
        index++;
        byte--;
        if ((pos % 4 == 0 && functionCode != ASCII_BS && functionCode != ASCII_DEL && functionCode != ASCII_FF) || text[index] == 0 || functionCode == ASCII_VT)
        {
            u8 tempNum = num;
            for (u8 n1 = 0; n1 < 2; n1++)
            {
                VDP_loadTileData(tile[n1], tileIndex + tileNum + n1 * 3, 3, DMA);
            }
            VDP_fillTileMapRectInc(plane, TILE_ATTR_FULL(palette, FALSE, FALSE, FALSE, tileIndex + tileNum), x + num, y + line * 2, 3, 2);
            tileNum += 6;
            num += 3;
            if (functionCode == ASCII_HT && num % 6 > 0)
            {
                VDP_fillTileMapRect(plane, TILE_ATTR_FULL(palette, FALSE, FALSE, FALSE, tileIndex), x + num, y + line * 2, 3, 2);
                num += 3;
                functionCode = CHARACTER;
            }
            else if (functionCode == ASCII_VT)
            {
                num = tempNum - tempNum % 6;
                line++;
                VDP_fillTileMapRect(plane, TILE_ATTR_FULL(palette, FALSE, FALSE, FALSE, tileIndex), x, y + line * 2, num, 2);
                functionCode = CHARACTER;
            }
        }
        if (pos >= w / 3 * 4 || text[index] == 0)
        {
            line++;
            pos = 0;
            num = 0;
        }
    }
    return tileNum;
}



