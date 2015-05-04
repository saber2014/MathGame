#include "screen.h"

Screen::Screen()
{
	memset(this->m_ppScreen, ' ', sizeof(this->m_ppScreen));
}

Screen::~Screen()
{
}

int Screen::NormalizeX(int nX)
{
	return nX % WIDTH;
}

int Screen::NormalizeGameX(int nX)
{
	if (nX < 0) return WIDTH - 1;
	else if (nX > WIDTH - 1) return 0;
	else return nX;
}

int Screen::NormalizeY(int nY)
{
	return nY % HEIGHT;
}

int Screen::NormalizeGameY(int nY)
{
	if (nY < 3) return HEIGHT - 1;
	else if (nY > HEIGHT - 1) return 3;
	else return nY;
}

void Screen::Print(char *pszText, int nX, int nY, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor)
{
	if (this->NormalizeX(nX) + strlen(pszText) >= WIDTH)
		g_pConsole->EnableWrap(false);

	g_pConsole->SetPosition(this->NormalizeX(nX), this->NormalizeY(nY));
	g_pConsole->SetColor(foregroundColor, backgroundColor);

	cout << pszText;
}

void Screen::PrintAligned(char *pszText, int align, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor)
{
	g_pConsole->SetColor(foregroundColor, backgroundColor);

	int i = 0;
	int startY = 0, lines = 0;

	while (true)
	{
		if (pszText[i] == '\n' || !pszText[i])
		{
			lines++;

			if (!pszText[i])
				break;
		}

		i++;
	}

	if ((align & SCREEN_ALIGN_TOP) != 0)
		startY = 0;
	else if ((align & SCREEN_ALIGN_VCENTER) != 0)
		startY = HEIGHT / 2 - lines / 2;
	else if ((align & SCREEN_ALIGN_BOTTOM) != 0)
		startY = HEIGHT - lines;
	else
		startY = g_pConsole->GetYPosition();

	i = 0;
	int start = 0, end = 0;

	while (true)
	{
		if (pszText[i] == '\n' || !pszText[i])
		{
			end = i;
			
			int length = end - start;
			
			char *temp = new char[length + 1];
			memset(temp, 0, sizeof(char) * (length + 1));
			strncpy(temp, pszText + start, length);

			int startX = 0;

			if ((align & SCREEN_ALIGN_LEFT) != 0)
				startX = 0;
			else if ((align & SCREEN_ALIGN_HCENTER) != 0)
				startX = WIDTH / 2 - length / 2;
			else if ((align & SCREEN_ALIGN_RIGHT) != 0)
				startX = WIDTH - length;
			else
				startX = g_pConsole->GetXPosition();

			if (this->NormalizeX(startX) + length >= WIDTH)
				g_pConsole->EnableWrap(false);

			g_pConsole->SetPosition(this->NormalizeX(startX), this->NormalizeY(startY++));
			cout << temp;

			delete[] temp;

			start = end + 1;

			if (!pszText[i])
				break;
		}

		i++;
	}
}

void Screen::SetAt(char ch, int nX, int nY)
{
	this->m_ppScreen[this->NormalizeY(nY)][this->NormalizeX(nX)] = ch;
}

char Screen::GetAt(int nX, int nY)
{
	return this->m_ppScreen[this->NormalizeY(nY)][this->NormalizeX(nX)];
}

void Screen::PrintMessage(char *pszMessage, SCREEN_MESSAGE_STYLE style)
{
	g_pConsole->SetColor(GetStylizedForeground(style), GetStylizedBackground(style));

	int max = 0;
	int start = 0, end = 0;
	int lines = 0;

	int i = 0;
	
	while (true)
	{
		if (pszMessage[i] == '\n' || !pszMessage[i])
		{
			end = i;

			if (end - start > max)
				max = end - start;

			start = end + 1;

			lines++;

			if (!pszMessage[i])
				break;
		}
		
		i++;
	}

	int startX = WIDTH / 2 - (max + 6) / 2;
	int startY = HEIGHT / 2 - (lines + 4) / 2;

	for (int i = 0; i < lines + 4; i++)
	{
		g_pConsole->SetPosition(startX, startY++);

		if (i == 0 || i + 1 == lines + 4)
		{
			for (int j = 0; j < max + 6; j++)
				cout << "*";
		}
		else
		{
			for (int j = 0; j < max + 6; j++)
			{
				if (j == 0 || j + 1 == max + 6)
					cout << "*";
				else
					cout << " ";
			}
		}
	}

	this->PrintAligned(pszMessage, SCREEN_ALIGN_VCENTER | SCREEN_ALIGN_HCENTER, GetStylizedForeground(style), GetStylizedBackground(style));
}

void Screen::PrintBottomMessage(char *pszMessage, SCREEN_MESSAGE_STYLE style)
{
	g_pConsole->SetColor(GetStylizedForeground(style), GetStylizedBackground(style));

	g_pConsole->SetPosition(0, HEIGHT - 1);

	for (int i = 0; i < WIDTH; i++)
		cout << " ";

	this->PrintAligned(pszMessage, SCREEN_ALIGN_HCENTER | SCREEN_ALIGN_BOTTOM, GetStylizedForeground(style), GetStylizedBackground(style));
}

OBJECT_TYPE Screen::GetObjectAt(int x, int y)
{
	char ch = this->GetAt(this->NormalizeGameX(x), this->NormalizeGameY(y));

	if (ch == '#')
		return OBJECT_TYPE_PLAYER1;
	else if (ch == '@')
		return OBJECT_TYPE_PLAYER2;
	else if ('0' <= ch && ch <= '9')
		return OBJECT_TYPE_NUMBER;
	else if (ch == '*')
		return OBJECT_TYPE_SHOT;
	else if (ch == '%')
		return OBJECT_TYPE_NUMBERS_EATER;

	return OBJECT_TYPE_NONE;
}

void Screen::Clear()
{
	memset(this->m_ppScreen, ' ', sizeof(this->m_ppScreen));
}

void Screen::PrintScreenWithNumbers()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if ('0' <= this->m_ppScreen[y][x] && this->m_ppScreen[y][x] <= '9')
			{
				g_pConsole->SetPosition(x, y);
				g_pConsole->SetColor(CONSOLE_COLOR_LIGHT_GREEN, CONSOLE_COLOR_GREEN);

				cout << this->m_ppScreen[y][x];
			}
		}
	}
}