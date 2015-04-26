#ifndef MANAGER_H
#define MANAGER_H

#include "common.h"

class Page;

class Manager
{
private:
	Page *m_pCurrentPage;

public:
	Manager();
	~Manager();

	void SwitchPage(Page *pNewPage);
	void Run();
};

#endif