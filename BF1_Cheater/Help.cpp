/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#include "Help.h"
#include <stdarg.h>
#include <TlHelp32.h>

ModuleInfo g_ModuleInfo { 0 };


bool WriteBuffer(uintptr_t addr, PVOID Writebuff)
{
	bool bRet = WriteProcessMemory((HANDLE)-1, (LPVOID)addr, Writebuff, sizeof(Writebuff), NULL);
	return bRet;
}


bool InitCurrentModuleInfo()
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetCurrentProcessId());
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 me;
		me.dwSize = sizeof(me);
		if (Module32First(hSnap, &me))
		{
			g_ModuleInfo.ModuleAddr = (DWORD64)me.modBaseAddr;
			g_ModuleInfo.ModuleHandle = me.hModule;
			g_ModuleInfo.Alloc(me.modBaseSize);
			ZeroMemory(g_ModuleInfo.ModuleName, sizeof(g_ModuleInfo.ModuleName));
			strncpy(g_ModuleInfo.ModuleName, me.szModule, strlen(me.szModule));
			SIZE_T ReadSize = 0;
			ReadProcessMemory((HANDLE)-1, (LPCVOID)g_ModuleInfo.ModuleAddr, g_ModuleInfo.ModuleData, g_ModuleInfo.ModuleSize, &ReadSize);

			if (ReadSize != g_ModuleInfo.ModuleSize) return false;
		}
		else return false;
	}
	else return false;
	CloseHandle(hSnap);

	return true;
}


bool ReleaseModuleInfo()
{
	if (g_ModuleInfo.ModuleSize == 0) return false;
	g_ModuleInfo.Release();
	return true;
}


uintptr_t GetAddrBypattern(const char* pattern, DWORD64 length, DWORD index)
{
	const char* start = g_ModuleInfo.ModuleData;

	DWORD count = 0;
	for (DWORD i = 0; i < g_ModuleInfo.ModuleSize; i++)
	{
		if (start[i] == pattern[0] || pattern[0] == '?')
		{
			DWORD j = 1;
			for (; j < length; j++) if (start[i + j] != pattern[j] && pattern[j] != '?') break;
			if (j == length && count++ == index) return g_ModuleInfo.ModuleAddr + i;//count++
		}
	}

	printf("特征码匹配失败\n");
	return 0;
}


uintptr_t* GetModuleBase()
{
	return (uintptr_t*)GetModuleHandle(NULL);
}