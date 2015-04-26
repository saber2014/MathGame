#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "common.h"

#define ASCII_COUNT 128

#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_LEFT 37
#define KEY_UP 38
#define KEY_RIGHT 39
#define KEY_DOWN 40

class Keyboard
{
private:
	HANDLE m_hStdIn;

public:
	Keyboard();
	~Keyboard();

	void Flush();
	list<char> GetInput();
};

#endif