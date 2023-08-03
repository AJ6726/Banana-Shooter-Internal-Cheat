#include <dwmapi.h>
#include "CGui.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h" 

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool g_bGuiOpen = false;

LRESULT CALLBACK WindowProcedure(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	if (g_bGuiOpen)
		ImGui_ImplWin32_WndProcHandler(hWindow, uMessage, wParam, lParam);
		
	return DefWindowProc(hWindow, uMessage, wParam, lParam); 
}


void CGui::SetupWindow()
{
	m_WindowClass.cbSize = sizeof(WNDCLASSEX);
	m_WindowClass.hInstance = GetModuleHandle(0);
	m_WindowClass.lpfnWndProc = reinterpret_cast<WNDPROC>(WindowProcedure);
	m_WindowClass.style = CS_VREDRAW | CS_HREDRAW; 
	m_WindowClass.lpszClassName = L"Zestware";
	
	RegisterClassEx(&m_WindowClass); 

	m_hWindow = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, m_WindowClass.lpszClassName, L"Zestware", WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080, 0, 0, m_WindowClass.hInstance, 0);
	SetLayeredWindowAttributes(m_hWindow, RGB(0, 0, 0), (BYTE)255, LWA_ALPHA); 


	RECT ClientArea{};
	GetClientRect(m_hWindow, &ClientArea);

	RECT WindowArea{};
	GetWindowRect(m_hWindow, &WindowArea);

	POINT diff{};
	ClientToScreen(m_hWindow, &diff);

	const MARGINS Margins{
		WindowArea.left + (diff.x - WindowArea.left),
		WindowArea.top + (diff.y - WindowArea.top),
		ClientArea.right,
		ClientArea.bottom
	};

	DwmExtendFrameIntoClientArea(m_hWindow, &Margins);

	ShowWindow(m_hWindow, SW_SHOW); 
	UpdateWindow(m_hWindow);
}

void CGui::SetupDirect3D11()
{
	DXGI_MODE_DESC Buffer = { 0 }; 
	Buffer.Width = 0; 
	Buffer.Height = 0; 
	Buffer.RefreshRate = { .Numerator = 165, .Denominator = 1 };
	Buffer.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	Buffer.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; 
	Buffer.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	DXGI_SAMPLE_DESC Sample = { 0 }; 
	Sample.Count = 1; 
	Sample.Quality = 0; 

	DXGI_SWAP_CHAIN_DESC SwapChain = { 0 }; 
	SwapChain.BufferDesc = Buffer; 
	SwapChain.SampleDesc = Sample; 
	SwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChain.BufferCount = 2; 
	SwapChain.OutputWindow = m_hWindow; 
	SwapChain.Windowed = true; 
	SwapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; 
	SwapChain.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; 
	D3D_FEATURE_LEVEL FeatureLevel[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 }; 

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, FeatureLevel, 2, D3D11_SDK_VERSION, &SwapChain, &m_pSwapChain, &m_pDevice, &m_FeatureLevel, &m_pDeviceContext);  

	m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&m_pBackBuffer)); 
	m_pDevice->CreateRenderTargetView(m_pBackBuffer, nullptr, &m_pRenderTargetView); 
	m_pBackBuffer->Release(); 
}
void CGui::SetupImGui()
{
	ImGui::CreateContext(); 
	ImGui_ImplWin32_Init(m_hWindow); 
	ImGui_ImplDX11_Init(m_pDevice, m_pDeviceContext);
}

void CGui::DestroyImGui()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown(); 
	ImGui::DestroyContext(); 
}
void CGui::DestroyDirect3D11()
{
	m_pDevice->Release();
	m_pSwapChain->Release(); 
	m_pDeviceContext->Release(); 
	m_pRenderTargetView->Release(); 
	
}
void CGui::DestroyWindow()
{
	::DestroyWindow(m_hWindow);
	UnregisterClass(m_WindowClass.lpszClassName, m_WindowClass.hInstance);
}
