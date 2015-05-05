/*
 * MathGame - a competitive math game
 * Copyright (C) 2015  saber2014
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

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

void OutputDebugMessage(char *message)
{
#if defined(_MSC_VER)
	OutputDebugStringA(message);
#endif
}