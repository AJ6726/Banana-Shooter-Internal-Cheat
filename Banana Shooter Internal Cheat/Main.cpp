#include "CConsole.h"
#include "CMenu.h"
#include "CHooks.h"
#include "CAimbot.h"
#include "CEsp.h"
#include "Configs.h"

extern bool g_bGuiOpen;

DWORD WINAPI Main(HMODULE hModule)
{
	Module::gameAssembly = reinterpret_cast<uintptr_t>(GetModuleHandle(L"GameAssembly.dll"));

	CConsole Console;
	Console.CreateConsole();

	CMenu Menu;
	Menu.CreateGui();

	CHooks Hooks;
	Hooks.CreateHooks();

	CAimbot Aimbot;
	CEsp Esp;

	while (true)
	{
		MSG Message;
		if (PeekMessage(&Message, Menu.m_hWindow, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessageA(&Message);
		}

		if (GetAsyncKeyState(VK_END) & 1)
			break;

		if (GetAsyncKeyState(VK_INSERT) & 1)
			g_bGuiOpen = !g_bGuiOpen;

		if (Game::networkManager)
		{
			if (Game::networkManager->fields.connecting) //Reset all global variables for a new game instance
			{
				Game::localPlayer = nullptr; 
				Game::localCam = nullptr; 
				Game::entityList.clear(); 
			}
		}

		Menu.BeginRender();

		if (Game::localPlayer && Game::localCam) 
		{
			if (Config::aimbot)
				Aimbot.RunAimbot(); 

			if (Config::esp)
				Esp.RenderEsp();
		}

		if (g_bGuiOpen)
		{
			SetWindowLong(Menu.m_hWindow, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST);
			Menu.RenderMenu();
		}
		else
			SetWindowLong(Menu.m_hWindow, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT);

		Menu.EndRender();
	}

	Hooks.DestroyHooks();
	Menu.DestroyGui();
	Console.DestroyConsole();
	FreeLibraryAndExitThread(hModule, 0);
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	HANDLE hMain = nullptr;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		hMain = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main), hModule, 0, 0);
		if (hMain)
			CloseHandle(hMain);

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

