#include "instructions_page.h"
#include "screen.h"

char *InstructionsPage::GetName()
{
	return "Instructions";
}

void InstructionsPage::Print()
{
	g_pConsole->SetPosition(0, 2);
	g_pScreen->PrintAligned("INSTRUCTIONS", SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_LIGHT_RED, CONSOLE_COLOR_RED);

	g_pConsole->SetPosition(2, 5);
	g_pScreen->PrintAligned("There are two players in the game.", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);

	g_pConsole->SetPosition(2, 6);
	g_pScreen->PrintAligned("The first player indicated as @, while the other indicated as #.", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);

	g_pConsole->SetPosition(2, 9);
	g_pScreen->PrintAligned("To move the first player up, right, bottom and left use the w d x a keys, ", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);

	g_pConsole->SetPosition(2, 10);
	g_pScreen->PrintAligned("respectively.", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);

	g_pConsole->SetPosition(2, 12);
	g_pScreen->PrintAligned("To move the second player up, right, bottom and left use the i l m j keys, ", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);

	g_pConsole->SetPosition(2, 13);
	g_pScreen->PrintAligned("respectively.", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);

	g_pConsole->SetPosition(2, 16);
	g_pScreen->PrintAligned("The purpose of the game is to solve the given exercise for each player.", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);

	g_pConsole->SetPosition(2, 17);
	g_pScreen->PrintAligned("The first player who solve the exercise, gets one point.", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);

	g_pConsole->SetPosition(2, 18);
	g_pScreen->PrintAligned("Once someone solved the given exercise, the game moves to the next level.", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);

	this->PrintMessage();
}

void InstructionsPage::KeyEvent(char key)
{
}

void InstructionsPage::PrintMessage()
{
	g_pConsole->SetPosition(0, 21);
	g_pScreen->PrintAligned("PRESS ESC TO GO BACK TO THE MAIN MENU", SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_LIGHT_AQUA, CONSOLE_COLOR_AQUA);
}