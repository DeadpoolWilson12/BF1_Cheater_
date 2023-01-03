/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#ifndef ANTISCREENSHOT_H
#define ANTISCREENSHOT_H

#include "Base.h"
#include "Frosbite.h"

// 反截图
extern bool IsScreenShotBeingTaken;
typedef void(__thiscall* tDispatchMessage)(void* pMessageManagerImpl, fb::Message* pMessage);

DWORD WINAPI MonitorTread(LPVOID lpParam);
void __fastcall hkDispatchMessage(void* pMessageManagerImpl, fb::Message* pMessage);
bool StartAntiScreenShot();

#endif // !ANTISCREENSHOT_H

