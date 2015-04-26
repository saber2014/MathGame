#ifndef START_GAME_LEVEL_PAGE_H
#define START_GAME_LEVEL_PAGE_H

#include "common.h"
#include "page.h"

class StartGameLevelPage : public Page
{
private:
	string m_levelNumber;

public:
	StartGameLevelPage();
	~StartGameLevelPage();

	char *GetName();
	void Print();
	void KeyEvent(char key);

	void PrintLevel();
	void PrintMessage();
	int GetLevelNumber();
};

#endif