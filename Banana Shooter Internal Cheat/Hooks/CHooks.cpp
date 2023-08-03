#include "CHooks.h"
#include "MinHook.h"
#include "Globals.h"
#include "Offsets.h"

using pFnClientPlayerUpdate = void(__thiscall*)(void*);
pFnClientPlayerUpdate ogClientPlayerUpdate = nullptr;
void __stdcall hkClientPlayerUpdate(Multiplayer_Client_ClientPlayer_o* player);

using pFnFirearmsUpdate = void(__thiscall*)(void*, float, int);
pFnFirearmsUpdate ogFirearmsReload = nullptr;
void __stdcall hkFirearmsReload(Firearms_o* firearm, float time, int spinAmount);

using pFnNetworkManagerInit = void(__thiscall*)(void*);
pFnNetworkManagerInit ogNetworkManagerInit = nullptr;
void __stdcall hkNetworkManagerInit(Multiplayer_NetworkManager_o* networkManager);

using pFnLobbyManagerSetLobbyGameMode = void(__thiscall*)(void*);
pFnLobbyManagerSetLobbyGameMode ogLobbyManagerSetLobbyGameMode = nullptr;
void __stdcall hkLobbyManagerSetLobbyGameMode(Multiplayer_LobbyManager_o* lobbyManager);

void CHooks::CreateHooks()
{
	MH_Initialize();
	MH_CreateHook(reinterpret_cast<LPVOID>(Module::gameAssembly + Offsets::ClientPlayer::fnUpdate), hkClientPlayerUpdate, reinterpret_cast<LPVOID*>(&ogClientPlayerUpdate));
	MH_CreateHook(reinterpret_cast<LPVOID>(Module::gameAssembly + Offsets::Firearms::fnReload), hkFirearmsReload, reinterpret_cast<LPVOID*>(&ogFirearmsReload));
	MH_CreateHook(reinterpret_cast<LPVOID>(Module::gameAssembly + Offsets::NetworkManager::fnInit), hkNetworkManagerInit, reinterpret_cast<LPVOID*>(&ogNetworkManagerInit));
	MH_CreateHook(reinterpret_cast<LPVOID>(Module::gameAssembly + Offsets::LobbyManager::fnSetLobbyGameMode), hkLobbyManagerSetLobbyGameMode, reinterpret_cast<LPVOID*>(&ogLobbyManagerSetLobbyGameMode));
	MH_EnableHook(MH_ALL_HOOKS);
}

void CHooks::DestroyHooks()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

void __stdcall hkClientPlayerUpdate(Multiplayer_Client_ClientPlayer_o* player)
{

	if (!player || !player->fields.m_CachedPtr)
		return ogClientPlayerUpdate(player);

	if (player->fields._IsLocal_k__BackingField && !player->fields._Dead_k__BackingField)
		Game::localPlayer = player;

	if (!player->fields._IsLocal_k__BackingField && !player->fields._Dead_k__BackingField)
	{
		bool inList = false;

		for (auto& entity : Game::entityList)
		{
			if (player == entity)
				inList = true;
		}

		if (!inList)
			Game::entityList.push_back(player);
	}

	return ogClientPlayerUpdate(player);
}


void __stdcall hkFirearmsReload(Firearms_o* firearm, float time, int spinAmount)
{
	Game::localCam = reinterpret_cast<Camera*>(firearm->fields.PlayerCam);
	return ogFirearmsReload(firearm, time, spinAmount);
}

void __stdcall hkNetworkManagerInit(Multiplayer_NetworkManager_o* networkManager)
{
	Game::networkManager = networkManager;
	return ogNetworkManagerInit(networkManager);
}

void __stdcall hkLobbyManagerSetLobbyGameMode(Multiplayer_LobbyManager_o* lobbyManager)
{
	return ogLobbyManagerSetLobbyGameMode(lobbyManager);
}
