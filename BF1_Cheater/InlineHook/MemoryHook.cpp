/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#include "MemoryHook.h"



bool Hook::Install(HANDLE handle, DWORD64 hookAddr_, PVOID FuncCallBack, int byteOfNum_, DWORD64 JmpAddr_)
{
	processHandle = handle;
	hookAddr = hookAddr_;
	byteOfNum = byteOfNum_;

	memset(this->OriginalCode, 0, 64);
	bool bRet = ReadProcessMemory(this->processHandle, (LPVOID)this->hookAddr, this->OriginalCode, byteOfNum, NULL);
	if (!bRet) return false;
	
	memset(this->NewCode, 0, 64);
	this->NewCode[0] = '\xE9';
	JmpBuffer = VirtualAllocEx(processHandle,(LPVOID)JmpAddr_, 1024, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (JmpBuffer == NULL) return false;
	// printf("JmpBuffer:%p\n", JmpBuffer);
	
	DWORD64 X = (DWORD64)JmpBuffer - (hookAddr + 5);
	// printf("X:%p\n", X);
	*(DWORD*)(this->NewCode + 1) = (DWORD)X;

	int Numnop = byteOfNum - 5;
	for (int i = 0; i < Numnop; i++)
	{
		this->NewCode[5 + i] = '\x90';
	}
	bRet = WriteProcessMemory(this->processHandle, (LPVOID)this->hookAddr, this->NewCode, byteOfNum, NULL);
	if (!bRet) return false;

	memset(this->InjectCode, 0, 512);
	memcpy(this->InjectCode, "\xFF\x15\x02\x00\x00\x00\xEB\x08", 8);
	*(DWORD64*)(this->InjectCode + 8) = (DWORD64)FuncCallBack;

	// printf("FuncCallBack:%p\n", FuncCallBack);
	memcpy(this->InjectCode + 16, this->OriginalCode, byteOfNum);

	this->InjectCode[16 + byteOfNum] = '\xE9';
	X = this->hookAddr + byteOfNum - ((DWORD64)JmpBuffer + 16 + byteOfNum + 5);
	*(DWORD*)(this->InjectCode + 16 + byteOfNum + 1) = (DWORD)X;

	bRet = WriteProcessMemory(this->processHandle, JmpBuffer, this->InjectCode, 16 + byteOfNum + 5, NULL);
	if (!bRet) return false;

	return true;
}


bool Hook::Install(HANDLE handle, DWORD64 hookAddr_, char* ShellCode, int ShellCodeNum, int byteOfNum_, DWORD64 JmpAddr_)
{
	processHandle = handle;
	hookAddr = hookAddr_;
	byteOfNum = byteOfNum_;

	char TempShellCode[128] = { 0 };
	memcpy(TempShellCode, ShellCode, ShellCodeNum);

	memset(this->OriginalCode, 0, 64);
	bool bRet = ReadProcessMemory(this->processHandle, (LPVOID)this->hookAddr, this->OriginalCode, byteOfNum, NULL);
	if (!bRet) return false;

	memset(this->NewCode, 0, 64);
	this->NewCode[0] = '\xE9';
	// JmpBuffer = VirtualAllocEx(processHandle, (LPVOID)JmpAddr_, 256, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	JmpBuffer = (LPVOID)JmpAddr_;
	if (JmpBuffer == NULL) return false;
	printf("JmpBuffer:%p\n", JmpBuffer);

	DWORD64 X = (DWORD64)JmpBuffer - (hookAddr + 5);
	// printf("X:%p\n", X);
	*(DWORD*)(this->NewCode + 1) = (DWORD)X;

	int Numnop = byteOfNum - 5;
	for (int i = 0; i < Numnop; i++)
	{
		this->NewCode[5 + i] = '\x90';
	}
	/*bRet = WriteProcessMemory(this->processHandle, (LPVOID)this->hookAddr, this->NewCode, byteOfNum, NULL);
	if (!bRet) return false;*/

	memset(this->InjectCode, 0, 512);
	memcpy(this->InjectCode, TempShellCode, ShellCodeNum);
	memcpy(this->InjectCode + ShellCodeNum, this->OriginalCode, byteOfNum);

	this->InjectCode[ShellCodeNum + byteOfNum] = '\xE9';
	X = this->hookAddr + byteOfNum - ((DWORD64)JmpBuffer + ShellCodeNum + byteOfNum + 5);
	*(DWORD*)(this->InjectCode + ShellCodeNum + byteOfNum + 1) = (DWORD)X;

	bRet = WriteProcessMemory(this->processHandle, JmpBuffer, this->InjectCode, ShellCodeNum + byteOfNum + 5, NULL);
	if (!bRet) return false;

	return true;
}


bool Hook::StartHook()
{
	if (JmpBuffer == NULL)
	{
		printf("Hook未安装\n");
		return false;
	}

	bool bRet = WriteProcessMemory(this->processHandle, (LPVOID)this->hookAddr, this->NewCode, this->byteOfNum, NULL);
	if (!bRet) return false;

	return true;
}


bool Hook::EndHook()
{
	if (JmpBuffer == NULL)
	{
		printf("Hook未安装\n");
		return false;
	}

	bool bRet = WriteProcessMemory(this->processHandle, (LPVOID)this->hookAddr, this->OriginalCode, this->byteOfNum, NULL);
	if (!bRet) return false;

	return true;
}


bool Hook::Uninstall()
{
	if (this->JmpBuffer == NULL) return false;

	bool bRet = WriteProcessMemory(this->processHandle, (LPVOID)this->hookAddr, this->OriginalCode, this->byteOfNum, NULL);
	if (!bRet) return false;

	bRet = VirtualFreeEx(this->processHandle, (LPVOID)JmpBuffer, 1024, MEM_RELEASE);

	this->processHandle = NULL;
	this->hookAddr = 0;
	this->byteOfNum = 0;
	this->JmpBuffer = NULL;

	memset(InjectCode, 0, 512);
	memset(OriginalCode, 0, 64);
	memset(NewCode, 0, 64);

	return true;
}

