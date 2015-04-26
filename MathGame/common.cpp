#include "common.h"
#include "screen.h"

class Console *g_pConsole = NULL;
class Screen *g_pScreen = NULL;
class Keyboard *g_pKeyboard = NULL;

CONSOLE_COLOR GetStylizedForeground(SCREEN_MESSAGE_STYLE style)
{
	CONSOLE_COLOR foregroundColor = CONSOLE_COLOR_DEFAULT;

	switch (style)
	{
	case SCREEN_MESSAGE_STYLE_BLUE:
		foregroundColor = CONSOLE_COLOR_LIGHT_BLUE;
		break;

	case SCREEN_MESSAGE_STYLE_GREEN:
		foregroundColor = CONSOLE_COLOR_LIGHT_GREEN;
		break;

	case SCREEN_MESSAGE_STYLE_AQUA:
		foregroundColor = CONSOLE_COLOR_LIGHT_AQUA;
		break;

	case SCREEN_MESSAGE_STYLE_RED:
		foregroundColor = CONSOLE_COLOR_LIGHT_RED;
		break;

	case SCREEN_MESSAGE_STYLE_PURPLE:
		foregroundColor = CONSOLE_COLOR_LIGHT_PURPLE;
		break;

	case SCREEN_MESSAGE_STYLE_YELLOW:
		foregroundColor = CONSOLE_COLOR_LIGHT_YELLOW;
		break;

	case SCREEN_MESSAGE_STYLE_DEFAULT:
	default:
		foregroundColor = CONSOLE_COLOR_DEFAULT;
	}

	return foregroundColor;
}

CONSOLE_COLOR GetStylizedBackground(SCREEN_MESSAGE_STYLE style)
{
	CONSOLE_COLOR backgroundColor = CONSOLE_COLOR_DEFAULT;

	switch (style)
	{
	case SCREEN_MESSAGE_STYLE_BLUE:
		backgroundColor = CONSOLE_COLOR_BLUE;
		break;

	case SCREEN_MESSAGE_STYLE_GREEN:
		backgroundColor = CONSOLE_COLOR_GREEN;
		break;

	case SCREEN_MESSAGE_STYLE_AQUA:
		backgroundColor = CONSOLE_COLOR_AQUA;
		break;

	case SCREEN_MESSAGE_STYLE_RED:
		backgroundColor = CONSOLE_COLOR_RED;
		break;

	case SCREEN_MESSAGE_STYLE_PURPLE:
		backgroundColor = CONSOLE_COLOR_PURPLE;
		break;

	case SCREEN_MESSAGE_STYLE_YELLOW:
		backgroundColor = CONSOLE_COLOR_YELLOW;
		break;

	case SCREEN_MESSAGE_STYLE_DEFAULT:
	default:
		backgroundColor = CONSOLE_COLOR_DEFAULT;
	}

	return backgroundColor;
}