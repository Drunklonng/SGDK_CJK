
#define SET_4BIT_MASK(x, mask) (x |= mask)

#define GET_BIT(x, bit) ((x & (1 << bit)) >> bit)
#define CLEAR_BIT(x, bit) (x &= ~(1 << bit))
#define SET_BIT(x, bit) (x |= (1 << bit))

#define TYPE_ASCII 0
#define TYPE_ANSI 1
#define TYPE_UTF8 2
#define TYPE_EXTRA 3
#define TYPE_EMOJI 4

#define ASCII_NUL 0
#define ASCII_EX 7
#define ASCII_BS 8
#define ASCII_HT 9
#define ASCII_LF 10
#define ASCII_VT 11
#define ASCII_FF 12
#define ASCII_COLOR 13
#define ASCII_EMOJI 27
#define ASCII_SP 32
#define ASCII_DEL 127
#define CHARACTER 255

enum CODE_PAGE
{
    CP65001,
    CP932,
    CP936,
    CP949,
    CP950,
};
enum CODE_PAGE codePage;
enum LANGUAGE
{
    zh_CN,
    zh_HK,
    ja_JP,
    ko_KR,
    en_US,
    ru_RU,
    /*
    fr_FR,
    de_DE,
    it_IT,
    es_ES,
    pt_PT,
    el_GR,
    */
};
enum LANGUAGE language;
