#ifndef INSTRUCTIONS_PAGE_H
#define INSTRUCTIONS_PAGE_H

#include "common.h"
#include "page.h"

class InstructionsPage : public Page
{
public:
	char *GetName();
	void Print();
	void KeyEvent(char key);

	void PrintMessage();
};

#endif