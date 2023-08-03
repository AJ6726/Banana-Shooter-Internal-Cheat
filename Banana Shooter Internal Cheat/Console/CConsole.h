#pragma once
#include <iostream>
struct CConsole
{
	void CreateConsole(); 
	void DestroyConsole(); 
	FILE* ConsoleFile = nullptr;
};
