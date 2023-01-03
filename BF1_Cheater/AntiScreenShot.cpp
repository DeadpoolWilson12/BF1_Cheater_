/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#include "AntiScreenShot.h"
#include "kiero/minhook/include/MinHook.h"


int count_before = 0;
bool IsScreenShotBeingTaken = false;
tDispatchMessage oDispatchMessage;

char monitors[][128] =
{
	"XiteNetworkGet1Message",
	"XiteNetworkGet2Message",
	"XiteNetworkGoMessage",
	"XiteNetworkInfo1Message",
	"XiteNetworkInfo2Message",
	"XiteNetworkInfo3Message",
	"XiteNetworkInfo4Message",
	"XiteNetworkPush1",
	"ScreenshotNetworkRequestScreenshotMessage"
};


bool StartAntiScreenShot()
{
	oDispatchMessage = (tDispatchMessage)OFFSET_DISPATCHMESSAGE;
	if (MH_Initialize() != MH_OK)  return false;
	if (MH_CreateHook((LPVOID)OFFSET_DISPATCHMESSAGE, &hkDispatchMessage, (LPVOID*)&oDispatchMessage) != MH_OK) return false;
	if (MH_EnableHook((LPVOID)OFFSET_DISPATCHMESSAGE) != MH_OK) return false;

	CreateThread(NULL, 0, MonitorTread, NULL, 0, NULL);

	return true;
}


DWORD WINAPI MonitorTread(LPVOID lpParam)
{
	while (true)
	{
		Sleep(10);
		if (IsScreenShotBeingTaken)
		{
			fb::DXRenderer* pDX = *(fb::DXRenderer**)OFFSET_DXRENDERER;
			Sleep(1000);
			printf("截图完成,开启作弊\n");
			IsScreenShotBeingTaken = false;
		}
	}
}


void __fastcall hkDispatchMessage(void* pMessageManagerImpl, fb::Message* pMessage)
{
	fb::TypeInfo* pType = pMessage->GetType();
	if ((pType->m_InfoData) != nullptr)
	{
		for (int i = 0; i < 9; i++) {
			if (strcmp(pType->m_InfoData->m_Name, monitors[i]) == 0)
			{
				printf("接收到截图消息:%s, 已停止作弊\n", pType->m_InfoData->m_Name);

				IsScreenShotBeingTaken = true;
				fb::DXRenderer* pDX = *(fb::DXRenderer**)OFFSET_DXRENDERER;
				count_before = pDX->m_frameCounter;
				// while (pDX->m_frameCounter < count_before + 2) Sleep(0);
				Sleep(100);
				printf("等待截图完毕\n");
			}
		}
	}
	return oDispatchMessage(pMessageManagerImpl, pMessage);
}