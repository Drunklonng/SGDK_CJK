#include <genesis.h>
#include <sram.h>

#include "gfx.h"
#include "sprite.h"
#include "sound.h"
#include "font.h"
#include "language.h"

#define TEST_TEST1 0

enum GAME_STATE {
	STATE_OP,
	STATE_TITLE,
	STATE_ED,
};
enum GAME_STATE currentState;

enum DEBUG_MODE
{
	DEBUG_DISABLED,
	DEBUG_ENABLED,
};
enum DEBUG_MODE debugMode;

typedef struct
{
	int x;
	int y;
} Test;
