#include "CMenu.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "Configs.h"

void CMenu::BeginRender()
{
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();
}

void CMenu::RenderMenu()
{
	ImGui::SetNextWindowSize(ImVec2{ 500, 400 }); 

	ImGui::Begin("Hello World");
	{
		ImGui::Checkbox("Aimbot", &Config::aimbot);
		static char buffer[2];
		ImGui::InputText("Aimbot Keybind", buffer, sizeof(buffer));
		Config::aimbotKeybind = toupper(buffer[0]); 

		ImGui::Checkbox("Esp", &Config::esp);
		ImGui::Checkbox("Boxes", &Config::box);
		ImGui::Checkbox("Traceline", &Config::traceline);
		ImGui::Checkbox("Healthbar", &Config::healthbar);
	}
	ImGui::End();
}

void CMenu::EndRender()
{
	ImGui::Render();
	static const float color[4] = { 0.f, 0.f, 0.f, 0.f };
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	m_pSwapChain->Present(1, 0);
}
