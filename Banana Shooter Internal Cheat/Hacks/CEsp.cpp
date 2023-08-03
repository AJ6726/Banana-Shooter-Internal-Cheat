#include "CEsp.h"
#include "imgui.h"
#include "Configs.h"

void CEsp::RenderEsp()
{
	for (auto& entity : Game::entityList)
	{
		if (!entity || entity->fields._Dead_k__BackingField)
			continue;

		Transform* entityHead = reinterpret_cast<Transform*>(entity->fields.head);
		wEntityHead = entityHead->GetPosition(Module::gameAssembly);

		if (!wEntityHead.IsZero())
		{
			wEntityHead = { wEntityHead.x, wEntityHead.y + 0.5f, wEntityHead.z };
			wEntityFeet = { wEntityHead.x, wEntityHead.y - 3.3f, wEntityHead.z };

			sEntityHead = Game::localCam->WorldToScreen(wEntityHead, Module::gameAssembly);
			sEntityFeet = Game::localCam->WorldToScreen(wEntityFeet, Module::gameAssembly);

			if (!sEntityHead.IsZero() && !sEntityHead.IsZero())
			{
				if(Config::box)
					DrawBox();

				if(Config::traceline)
					DrawTraceline(); 

				if(Config::healthbar)
					DrawHealthbar(entity->fields.health); 
			}
		}

	}

}

void CEsp::DrawBox()
{
	float height = sEntityFeet.y - sEntityHead.y;
	float width = height * 0.35f;

	Vector2 TopLeft = { sEntityHead.x - width, sEntityHead.y };
	Vector2 BottomRight = { sEntityFeet.x + width, sEntityFeet.y };

	ImGui::GetBackgroundDrawList()->AddRect(ImVec2{ TopLeft.x, TopLeft.y }, ImVec2{ BottomRight.x, BottomRight.y }, IM_COL32_WHITE);
}

void CEsp::DrawTraceline()
{
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2{ 960.f , 1080.f }, ImVec2{ sEntityFeet.x, sEntityFeet.y }, IM_COL32_WHITE); 
}

void CEsp::DrawHealthbar(int health)
{
	float height = sEntityFeet.y - sEntityHead.y; 
	float width = height * 0.35f; 

	Vector2 HealthBarTop = { sEntityHead.x - width, sEntityFeet.y - ((health * height) / 100.f) };
	Vector2 HealthBarBottom = { sEntityHead.x - width, sEntityFeet.y }; 

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2{ HealthBarBottom.x - 2.f, HealthBarBottom.y }, { HealthBarTop.x - 2.f, HealthBarTop.y }, ImColor{ 0.f, 255.f, 0.f }, 2.f); 
}


