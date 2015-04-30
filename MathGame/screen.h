#ifndef SCREEN_H
#define SCREEN_H

#include "common.h"
#include "console.h"

enum SCREEN_ALIGN
{
	SCREEN_ALIGN_DEFAULT = 0,
	SCREEN_ALIGN_LEFT = 1,
	SCREEN_ALIGN_HCENTER = 2,
	SCREEN_ALIGN_RIGHT = 4,
	SCREEN_ALIGN_TOP = 8,
	SCREEN_ALIGN_VCENTER = 16,
	SCREEN_ALIGN_BOTTOM = 32
};

enum SCREEN_MESSAGE_STYLE
{
	SCREEN_MESSAGE_STYLE_DEFAULT = -1,
	SCREEN_MESSAGE_STYLE_BLUE = 0,
	SCREEN_MESSAGE_STYLE_GREEN,
	SCREEN_MESSAGE_STYLE_AQUA,
	SCREEN_MESSAGE_STYLE_RED,
	SCREEN_MESSAGE_STYLE_PURPLE,
	SCREEN_MESSAGE_STYLE_YELLOW,
};

enum OBJECT_TYPE
{
	OBJECT_TYPE_NONE = 0,
	OBJECT_TYPE_PLAYER1,
	OBJECT_TYPE_PLAYER2,
	OBJECT_TYPE_NUMBER,
	OBJECT_TYPE_SHOT
};

class Screen
{
private:
	char m_ppScreen[HEIGHT][WIDTH];

public:
	Screen();
	~Screen();

	int NormalizeX(int nX);
	int NormalizeGameX(int nX);
	int NormalizeY(int nY);
	int NormalizeGameY(int nY);
	void Print(char *pszText, int nX, int nY, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor);
	void PrintAligned(char *pszText, int align, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor);
	void SetAt(char ch, int nX, int nY);
	char GetAt(int nX, int nY);
	void PrintMessage(char *pszMessage, SCREEN_MESSAGE_STYLE style);
	void PrintBottomMessage(char *pszMessage, SCREEN_MESSAGE_STYLE style);
	OBJECT_TYPE GetObjectAt(int x, int y);
};

#endif