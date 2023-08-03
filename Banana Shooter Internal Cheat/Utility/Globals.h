#include <cstdint>
#include <vector>
#include "il2cpp.h"
#include "Classes.h"

namespace Module
{
	inline uintptr_t gameAssembly = 0;
}

namespace Game
{
	inline Multiplayer_Client_ClientPlayer_o* localPlayer = nullptr; 
	inline Camera* localCam = nullptr; 

	inline std::vector<Multiplayer_Client_ClientPlayer_o*> entityList = { }; 

	inline Multiplayer_NetworkManager_o* networkManager = nullptr; 
	inline Multiplayer_LobbyManager_o* lobbyManager = nullptr; 
}

