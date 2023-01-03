/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

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
	// 用来求离准心最近的目标
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

