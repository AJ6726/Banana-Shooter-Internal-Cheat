#include <Windows.h>
#include "CConsole.h"
void CConsole::CreateConsole()
{
	AllocConsole(); 
	freopen_s(&(this->ConsoleFile), "CONOUT$", "w", stdout);
}
void CConsole::DestroyConsole()
{
	fclose(this->ConsoleFile); 
	FreeConsole(); 
}