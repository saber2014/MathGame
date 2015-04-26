#ifndef PAGE_H
#define PAGE_H

#include "common.h"

class Page
{
public:
	Page();

	virtual char *GetName() = 0;
	virtual void Print() = 0;
	virtual void KeyEvent(char key) = 0;
};

#endif