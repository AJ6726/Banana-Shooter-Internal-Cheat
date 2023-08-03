#include <Windows.h>
#include "CAimbot.h"
#include "Globals.h"
#include "Configs.h"

void CAimbot::RunAimbot()
{
	Multiplayer_Client_ClientPlayer_o* enemy = reinterpret_cast<Multiplayer_Client_ClientPlayer_o*>(GetClosestEntity());

	if (enemy)
	{
		Transform* enemyHead = reinterpret_cast<Transform*>(enemy->fields.head);

		Vector3 wEnemyHead = enemyHead->GetPosition(Module::gameAssembly);

		if (!wEnemyHead.IsZero())
		{
			Vector2 sEntityHead = Game::localCam->WorldToScreen(wEnemyHead, Module::gameAssembly);

			if (!sEntityHead.IsZero())
			{
				INPUT Mouse = { };
				Mouse.type = INPUT_MOUSE;
				Mouse.mi.dx = sEntityHead.x - 960.f;
				Mouse.mi.dy = sEntityHead.y - 540.f;
				Mouse.mi.dwFlags = MOUSEEVENTF_MOVE;
				Mouse.mi.time = 1;

				if (GetAsyncKeyState(Config::aimbotKeybind))
					SendInput(1, &Mouse, sizeof(Mouse));
			}
		}
	}
}


void* CAimbot::GetClosestEntity()
{
	float closestDistance = 10000.f;
	Multiplayer_Client_ClientPlayer_o* closestEntity = nullptr;

	for (auto entity : Game::entityList)
	{
		if (!entity || entity->fields._Dead_k__BackingField)
			continue;

		Transform* entityHead = reinterpret_cast<Transform*>(entity->fields.head);
		Vector3 wEntityHead = entityHead->GetPosition(Module::gameAssembly);

		if (!wEntityHead.IsZero())
		{
			Transform* localHead = reinterpret_cast<Transform*>(Game::localPlayer->fields.head);
			Vector3 wLocalHead = localHead->GetPosition(Module::gameAssembly);

			Vector3 DeltaPosition = wEntityHead - wLocalHead;

			float currentDistance = sqrtf(powf(DeltaPosition.x, 2) + powf(DeltaPosition.y, 2));

			if (closestDistance > currentDistance)
			{
				closestDistance = currentDistance;
				closestEntity = entity;
			}
		}
	}
	return closestEntity;
}