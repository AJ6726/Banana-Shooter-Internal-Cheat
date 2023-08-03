#pragma once
#include <d3d11.h>

struct CGui
{
	void CreateGui()
	{
		SetupWindow(); 
		SetupDirect3D11();
		SetupImGui(); 
	}

	void DestroyGui()
	{
		DestroyImGui();
		DestroyDirect3D11(); 
		DestroyWindow(); 
	}

	void SetupWindow(); 
	void SetupDirect3D11(); 
	void SetupImGui(); 

	void DestroyImGui(); 
	void DestroyDirect3D11(); 
	void DestroyWindow(); 


	WNDCLASSEX m_WindowClass = { 0 };
	HWND m_hWindow = nullptr; 

	ID3D11Device* m_pDevice = nullptr; 
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;
	ID3D11Texture2D* m_pBackBuffer = nullptr; 
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr; 
	D3D_FEATURE_LEVEL m_FeatureLevel; 

};
