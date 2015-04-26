#ifndef CONSOLE_H
#define CONSOLE_H

#include "common.h"

enum CONSOLE_COLOR
{
	CONSOLE_COLOR_DEFAULT = -1,
	CONSOLE_COLOR_BLACK = 0,
	CONSOLE_COLOR_BLUE,
	CONSOLE_COLOR_GREEN,
	CONSOLE_COLOR_AQUA,
	CONSOLE_COLOR_RED,
	CONSOLE_COLOR_PURPLE,
	CONSOLE_COLOR_YELLOW,
	CONSOLE_COLOR_WHITE,
	CONSOLE_COLOR_GRAY,
	CONSOLE_COLOR_LIGHT_BLUE,
	CONSOLE_COLOR_LIGHT_GREEN,
	CONSOLE_COLOR_LIGHT_AQUA,
	CONSOLE_COLOR_LIGHT_RED,
	CONSOLE_COLOR_LIGHT_PURPLE,
	CONSOLE_COLOR_LIGHT_YELLOW,
	CONSOLE_COLOR_BRIGHT_WHITE
};

class Console
{
private:
	HANDLE m_hStdOut;
	CONSOLE_COLOR m_foregroundColorDefault;
	CONSOLE_COLOR m_backgroundColorDefault;

public:
	Console();
	~Console();

	void Clear();
	void SetTitle(char *pszTitle);
	void ShowCursor(bool bShow);
	void SetColor(CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor);
	CONSOLE_COLOR GetForegroundColor();
	CONSOLE_COLOR GetBackgroundColor();
	void SetPosition(int nX, int nY);
	int GetXPosition();
	int GetYPosition();
	void SetBufferSize(int nWidth, int nHeight);
	void EnableWrap(bool bWrap);
	void Wait(int nMilliseconds);
};

#endif