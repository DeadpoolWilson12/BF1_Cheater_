/****************************************************************************************************
	�汾:1.0

	����:�ȷ��೤1997
	
	�ر�����:�ô������ѧϰ����ʹ��,����������ҵ��;�ͷǷ���;,������������ɵ�һ�к���ͷ�������һ���뱾���޹�

����ʱ��:2023-01-03 14:59

*****************************************************************************************************/
#ifndef AIMBOT_H
#define	AIMBOT_H

#include "Base.h"
#include "DX11.h"
#include "Frosbite.h"

class Aimbot
{
public:
	
	static Aimbot& GetInstance()
	{
		static Aimbot Instance;
		return Instance;
	}

	void Push(fb::ClientPlayer* LocalPlayer_, fb::ClientPlayer* Player_);

	void LockPlayer();

	bool CanAim();

	bool IsVisible();

	void SmoothAimbot();

private:
	// ��������׼�������Ŀ��
	fb::ClientPlayer* TempEnemy = NULL;
	fb::ClientPlayer* TempLocalPlayer = NULL;
	float TempPreviousDistance = 100000.f;

	fb::ClientPlayer* Enemy = NULL;
	fb::ClientPlayer* LocalPlayer = NULL;
	float PreviousDistance = 100000.f;

	DWORD AimPartIndex = 0;
	int32_t AimCount = 0;
};

#endif // !AIMBOT_H

