/****************************************************************************************************
	�汾:1.0

	����:�ȷ��೤1997
	
	�ر�����:�ô������ѧϰ����ʹ��,����������ҵ��;�ͷǷ���;,������������ɵ�һ�к���ͷ�������һ���뱾���޹�

����ʱ��:2023-01-03 14:59

*****************************************************************************************************/
#ifndef ANTISCREENSHOT_H
#define ANTISCREENSHOT_H

#include "Base.h"
#include "Frosbite.h"

// ����ͼ
extern bool IsScreenShotBeingTaken;
typedef void(__thiscall* tDispatchMessage)(void* pMessageManagerImpl, fb::Message* pMessage);

DWORD WINAPI MonitorTread(LPVOID lpParam);
void __fastcall hkDispatchMessage(void* pMessageManagerImpl, fb::Message* pMessage);
bool StartAntiScreenShot();

#endif // !ANTISCREENSHOT_H

