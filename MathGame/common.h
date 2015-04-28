#ifndef COMMON_H
#define COMMON_H

#define _CRT_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
#include <list>
#include <string>
using namespace std;

#define	WIDTH 80
#define	HEIGHT 25

#define WAIT_TIME 100
#define GAME_WAIT_TIME 200

extern class Console *g_pConsole;
extern class Screen *g_pScreen;
extern class Keyboard *g_pKeyboard;

extern enum CONSOLE_COLOR;
extern enum SCREEN_MESSAGE_STYLE;

CONSOLE_COLOR GetStylizedForeground(SCREEN_MESSAGE_STYLE style);
CONSOLE_COLOR GetStylizedBackground(SCREEN_MESSAGE_STYLE style);

#endif