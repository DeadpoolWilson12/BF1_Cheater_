/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#ifndef HELP_H
#define HELP_H

#include "Base.h"

struct ModuleInfo
{
	HANDLE ModuleHandle;
	char ModuleName[1024];
	char* ModuleData;
	DWORD64 ModuleAddr;
	DWORD ModuleSize;
	void Alloc(int size)
	{
		ModuleSize = size;
		ModuleData = (char*)VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (ModuleData == NULL) return;
	}
	void Release()
	{
		if (ModuleData) VirtualFree(ModuleData, 0, MEM_RELEASE);
		ModuleData = NULL;
	}
};

bool WriteBuffer(uintptr_t addr, PVOID Writebuff);

bool InitCurrentModuleInfo();

bool ReleaseModuleInfo();

uintptr_t GetAddrBypattern(const char* pattern, DWORD64 length, DWORD index = 0);

uintptr_t* GetModuleBase();

#endif // !HELP_H

