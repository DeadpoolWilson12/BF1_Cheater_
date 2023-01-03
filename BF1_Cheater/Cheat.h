/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#ifndef CHEAT_H
#define CHEAT_H

#include "Base.h"
#include "DX11.h"
#include "InlineHook/MemoryHook.h"

#define ACCURACY_PATTERN "\xF3\x0F\x10\x4C\x24\x4C\x0F\x2F"
#define RECOIL_PATTERN   "\xF3\x0F\x58\x56\x6C\xF3"
#define OVERHEAT_PATTERN "\xF3\x0F\x10\x81\x30\x02\x00\x00\xC3"
#define BULLETDAMAGE_PATTERN "\x89\x85\xE8\x00\x00\x00\x80"


class Cheater
{
public:
	Cheater(Menu* g_pMenu);

	void DoCheat();

	void HookInit();

	void HookFunc();

	Menu* g_pMenuRef;

	/*YPageHook hook1;
	YPageHook hook2;
	YPageHook hook3;*/
	Hook hook1;
	Hook hook2;
	Hook hook3;
	Hook hook4;
	
	char InjectShell1[128] = { 0 };
	char InjectShell2[128] = { 0 };
	char InjectShell3[128] = { 0 };
	char InjectShell4[128] = { 0 };

	bool IS_hooked1 = false;
	bool IS_hooked2 = false;
	bool IS_hooked3 = false;
	bool IS_hooked4 = false;

	DWORD64 accuracyAddr = NULL;
	DWORD64 recoilAddr = NULL;
	DWORD64 overheatAddr = NULL;
	DWORD64 multipleDamage = NULL;
};

#endif // !CHEAT_H
