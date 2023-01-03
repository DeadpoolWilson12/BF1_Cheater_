/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#ifndef MEMORYHOOK_H
#define MEMORYHOOK_H

#include <Windows.h>
#include <stdio.h>

class Hook
{
public:
	bool Install(HANDLE handle, DWORD64 hookAddr_, PVOID FuncCallBack, int byteOfNum_, DWORD64 JmpAddr_ = 0);
	bool Install(HANDLE handle, DWORD64 hookAddr, char *ShellCode, int ShellCodeNum, int byteOfNum, DWORD64 JmpAddr_ = 0);

	bool StartHook();
	bool EndHook();

	bool Uninstall();

private:

	HANDLE processHandle = NULL;
	DWORD64 hookAddr = 0;
	int byteOfNum = 0;

	LPVOID JmpBuffer = NULL;
	char InjectCode[512];
	char OriginalCode[64];
	char NewCode[64];
};


#endif // !MEMORYHOOK_H

