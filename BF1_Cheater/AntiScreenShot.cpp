/****************************************************************************************************
	�汾:1.0

	����:�ȷ��೤1997
	
	�ر�����:�ô������ѧϰ����ʹ��,����������ҵ��;�ͷǷ���;,������������ɵ�һ�к���ͷ�������һ���뱾���޹�

����ʱ��:2023-01-03 14:59

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
			printf("��ͼ���,��������\n");
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
				printf("���յ���ͼ��Ϣ:%s, ��ֹͣ����\n", pType->m_InfoData->m_Name);

				IsScreenShotBeingTaken = true;
				fb::DXRenderer* pDX = *(fb::DXRenderer**)OFFSET_DXRENDERER;
				count_before = pDX->m_frameCounter;
				// while (pDX->m_frameCounter < count_before + 2) Sleep(0);
				Sleep(100);
				printf("�ȴ���ͼ���\n");
			}
		}
	}
	return oDispatchMessage(pMessageManagerImpl, pMessage);
}