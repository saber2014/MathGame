#include "console.h"

Console::Console()
{
	this->m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	this->m_foregroundColorDefault = this->GetForegroundColor();
	this->m_backgroundColorDefault = this->GetBackgroundColor();
}

Console::~Console()
{
	if (this->m_hStdOut)
		CloseHandle(this->m_hStdOut);
}

void Console::Clear()
{
	this->SetColor(CONSOLE_COLOR_DEFAULT, CONSOLE_COLOR_DEFAULT);
	system("cls");
}

void Console::SetTitle(char *pszTitle)
{
	SetConsoleTitleA(pszTitle);
}

void Console::ShowCursor(bool bShow)
{
	CONSOLE_CURSOR_INFO cci = {};
	GetConsoleCursorInfo(this->m_hStdOut, &cci);

	cci.bVisible = bShow;

	SetConsoleCursorInfo(this->m_hStdOut, &cci);
}

void Console::SetColor(CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor)
{
	if (foregroundColor == CONSOLE_COLOR_DEFAULT) foregroundColor = this->m_foregroundColorDefault;
	if (backgroundColor == CONSOLE_COLOR_DEFAULT) backgroundColor = this->m_backgroundColorDefault;

	SetConsoleTextAttribute(this->m_hStdOut, (backgroundColor << 4) | foregroundColor);
}

CONSOLE_COLOR Console::GetForegroundColor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(this->m_hStdOut, &csbi);

	return (CONSOLE_COLOR)(csbi.wAttributes & 0x0f);
}

CONSOLE_COLOR Console::GetBackgroundColor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(this->m_hStdOut, &csbi);

	return (CONSOLE_COLOR)((csbi.wAttributes & 0xf0) >> 4);
}

void Console::SetPosition(int nX, int nY)
{
	COORD coord = { nX, nY };
	SetConsoleCursorPosition(this->m_hStdOut, coord);
}

int Console::GetXPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(this->m_hStdOut, &csbi);

	return csbi.dwCursorPosition.X;
}

int Console::GetYPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(this->m_hStdOut, &csbi);
	
	return csbi.dwCursorPosition.Y;
}

void Console::SetBufferSize(int nWidth, int nHeight)
{
	COORD coord = { nWidth, nHeight };
	SetConsoleScreenBufferSize(this->m_hStdOut, coord);
}

void Console::EnableWrap(bool bWrap)
{
	DWORD dwOldMode = 0;
	GetConsoleMode(this->m_hStdOut, &dwOldMode);

	if (bWrap) dwOldMode |= ENABLE_WRAP_AT_EOL_OUTPUT;
	else dwOldMode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;

	SetConsoleMode(this->m_hStdOut, dwOldMode);
}

void Console::Wait(int nMilliseconds)
{
	Sleep(nMilliseconds);
}