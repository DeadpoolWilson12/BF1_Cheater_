/****************************************************************************************************
	�汾:1.0

	����:�ȷ��೤1997
	
	�ر�����:�ô������ѧϰ����ʹ��,����������ҵ��;�ͷǷ���;,������������ɵ�һ�к���ͷ�������һ���뱾���޹�

����ʱ��:2023-01-03 14:59

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

