#ifndef MANAGER_H
#define MANAGER_H

#include "common.h"

enum MANAGER_CALLBACK
{
	MANAGER_CALLBACK_DEFAULT = 0,
	MANAGER_CALLBACK_GAME_OVER
};

class Page;
class GamePage;

class Manager
{
private:
	Page *m_pCurrentPage;
	bool m_gameOver;

	GamePage *m_savedGamePage;

public:
	Manager();
	~Manager();

	void SwitchPage(Page *pNewPage);
	void Run();
	void Callback(MANAGER_CALLBACK value);
};

#endif