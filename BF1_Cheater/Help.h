/****************************************************************************************************
	�汾:1.0

	����:�ȷ��೤1997
	
	�ر�����:�ô������ѧϰ����ʹ��,����������ҵ��;�ͷǷ���;,������������ɵ�һ�к���ͷ�������һ���뱾���޹�

����ʱ��:2023-01-03 14:59

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

