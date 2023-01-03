/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#include "DX11.h"
#include "AntiScreenShot.h"

Present			oPresent;
ResizeBuffers	oResizeBuffers;
WNDPROC			oWndProc;

ID3D11Device*				g_pDevice = NULL;
ID3D11DeviceContext*		g_pContext = NULL;
ID3D11RenderTargetView*		g_mainRenderTargetView = NULL;

DrawRect g_drawRect = { 0 };
HWND	 g_hwnd = NULL;
bool	 bInit = false;
bool	 bResize = false;

Menu*	 g_pMenu = NULL;
Cheater* g_pCheat = NULL;

DWORD WINAPI MainThreadFunc(LPVOID lpThreadParameter)
{
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "wt", stdout);
	printf("创建AllocConsole完毕\n");

	g_pMenu = new Menu();
	g_pCheat = new Cheater(g_pMenu);
	printf("完成创建g_pMenu和g_pCheat\n");

	bool bRet = StartAntiScreenShot();
	printf("StartAntiScreenShot()--bRet:%d\n", bRet);

	g_hwnd = FindWindowW(GAME_WIN_CLASS, GAME_WIN_NAME);
	GetESPWindowInfo();

	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			kiero::bind(13, (void**)&oResizeBuffers, hkResizeBuffers);
			init_hook = true;
		}
	} while (!init_hook);
	return 0;
}


void GetESPWindowInfo()
{
	RECT marginRect;
	RECT overlayRect;
	GetWindowRect(g_hwnd, &marginRect);
	GetClientRect(g_hwnd, &overlayRect);

	// 窗口模式，窗口左边的边框尺寸
	int winBorderLeft = ((marginRect.right - marginRect.left) - (overlayRect.right - overlayRect.left)) * 0.5;
	// 窗口模式，窗口顶部的边框尺寸，也就是窗口标题栏高度
	int winBorderTop = (marginRect.bottom - marginRect.top) - (overlayRect.bottom - overlayRect.top) - winBorderLeft;

	int clientCenterX = (overlayRect.right - overlayRect.left) * 0.5f;
	int clientCenterY = (overlayRect.bottom - overlayRect.top) * 0.5f;


	// 计算绘制窗口区域
	g_drawRect = {
		marginRect.left + winBorderLeft,
		marginRect.top + winBorderTop,
		overlayRect.right - overlayRect.left,
		overlayRect.bottom - overlayRect.top,
		clientCenterX,
		clientCenterY
	};
}


void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	ImFontConfig f_cfg1;
	f_cfg1.FontDataOwnedByAtlas = false;
	// 好像是最先加载的字体作为菜单窗口的字体
	g_pMenu->Config_.pMenuFont =  io.Fonts->AddFontFromMemoryTTF((void*)baidu_font_data, baidu_font_size, 15.0f, &f_cfg1, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());


	ImFontConfig f_cfg2;
	f_cfg2.FontDataOwnedByAtlas = false;
	g_pMenu->Config_.pEspFont = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\STKAITI.TTF", 17.0f, &f_cfg2, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(g_hwnd);
	ImGui_ImplDX11_Init(g_pDevice, g_pContext);
}


void GetDx11Ptr(IDXGISwapChain* This)
{
	This->GetDevice(__uuidof(g_pDevice), (void**)&g_pDevice);
	g_pDevice->GetImmediateContext(&g_pContext);
	DXGI_SWAP_CHAIN_DESC sd;
	This->GetDesc(&sd);
	g_hwnd = sd.OutputWindow;
	ID3D11Texture2D* pBackBuffer;
	This->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
}


LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (bResize)
	{
		printf("重新初始化\n");
		// 重新初始化
		GetDx11Ptr(pSwapChain);
		ImGui_ImplDX11_Init(g_pDevice, g_pContext);
		bResize = false;
		GetESPWindowInfo();
		return oPresent(pSwapChain, SyncInterval, Flags);
	}

	if (!bInit)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pDevice)))
		{
			GetDx11Ptr(pSwapChain);
			oWndProc = (WNDPROC)SetWindowLongPtr(g_hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			bInit = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	if (IsScreenShotBeingTaken == false)
	{
		g_pMenu->RenderMenu();
	}
	ImGui::EndFrame();

	if (IsScreenShotBeingTaken == false)
	{
		g_pCheat->DoCheat();
	}
	ImGui::Render();

	g_pContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}


HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (g_pDevice)
	{
		printf("进入hkResizeBuffers\n");
		g_pDevice->Release();
		g_pDevice = NULL;
		g_mainRenderTargetView->Release();

		ImGui_ImplDX11_Shutdown();

		bResize = true;
	}

	return oResizeBuffers(This, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}