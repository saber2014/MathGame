#include "keyboard.h"

Keyboard::Keyboard()
{
	this->m_hStdIn = GetStdHandle(STD_INPUT_HANDLE);
}

Keyboard::~Keyboard()
{
	if (this->m_hStdIn)
		CloseHandle(this->m_hStdIn);
}

void Keyboard::Flush()
{
	int nNumberOfEvents = 0;
	GetNumberOfConsoleInputEvents(this->m_hStdIn, (LPDWORD)&nNumberOfEvents);

	for (int i = 0; i < nNumberOfEvents; i++)
	{
		INPUT_RECORD buffer = {};
		DWORD nNumberOfEventsRead = 0;

		ReadConsoleInput(this->m_hStdIn, &buffer, 1, &nNumberOfEventsRead);
	}
}

list<char> Keyboard::GetInput()
{
	bool keys[ASCII_COUNT] = { false };

	int nNumberOfEvents = 0;
	GetNumberOfConsoleInputEvents(this->m_hStdIn, (LPDWORD)&nNumberOfEvents);

	for (int i = 0; i < nNumberOfEvents; i++)
	{
		INPUT_RECORD buffer = {};
		DWORD nNumberOfEventsRead = 0;

		ReadConsoleInput(this->m_hStdIn, &buffer, 1, &nNumberOfEventsRead);

		if (buffer.EventType == KEY_EVENT && buffer.Event.KeyEvent.bKeyDown == TRUE)
		{
			if (37 <= buffer.Event.KeyEvent.wVirtualKeyCode && buffer.Event.KeyEvent.wVirtualKeyCode <= 40)
			{
				if (0 <= buffer.Event.KeyEvent.wVirtualKeyCode && buffer.Event.KeyEvent.wVirtualKeyCode < ASCII_COUNT)
					keys[buffer.Event.KeyEvent.wVirtualKeyCode] = true;
			}
			else
			{
				if (0 <= buffer.Event.KeyEvent.uChar.AsciiChar && buffer.Event.KeyEvent.uChar.AsciiChar < ASCII_COUNT)
					keys[buffer.Event.KeyEvent.uChar.AsciiChar] = true;
			}
		}
	}

	list<char> list;

	for (int i = 0; i < ASCII_COUNT; i++)
	{
		if (keys[i])
			list.push_back(i);
	}

	return list;
}