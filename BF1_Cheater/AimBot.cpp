/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#include "AimBot.h"


void Aimbot::Push(fb::ClientPlayer* LocalPlayer_, fb::ClientPlayer* Player_)
{
	D3DXVECTOR2 Screen{ 0, 0 };
	D3DXVECTOR3 PlayerPos{ 0, 0, 0 };
	AimPartIndex = g_pMenu->Config_.aimbotType ? fb::BoneIds::BONE_SPINE2 : fb::BoneIds::BONE_Head;
	
	fb::ClientSoldierEntity* pSoldierEntity = Player_->clientSoldierEntity;
	if (!ValidPointer(pSoldierEntity)) return;
	pSoldierEntity->GetBonePos(AimPartIndex, &PlayerPos);
	WorldToScreen(PlayerPos, Screen);

	float Distance = sqrtf(powf(Screen.x - (float)g_drawRect.centerX, 2) + powf(Screen.y - (float)g_drawRect.centerY, 2));

	if (Distance < TempPreviousDistance && Distance < (float)g_pMenu->Config_.aimbotRange)
	{
		TempEnemy = Player_;
		TempLocalPlayer = LocalPlayer_;
		TempPreviousDistance = Distance;
	}
	return;
}


void Aimbot::LockPlayer()
{
	Enemy = TempEnemy;
	LocalPlayer = TempLocalPlayer;
	PreviousDistance = TempPreviousDistance;

	TempEnemy = NULL;
	TempLocalPlayer = NULL;
	TempPreviousDistance = 100000.f;
}


bool Aimbot::CanAim()
{
	if (!Enemy || !LocalPlayer)
		return false;

	return true;
}


bool Aimbot::IsVisible()
{
	return Enemy->clientSoldierEntity->IsVisible();
}


void Aimbot::SmoothAimbot()
{
	if (CanAim() && GetAsyncKeyState(VK_RBUTTON))
	{
		AimCount++;
		if (AimCount > 15)
		{
			// 重读一遍数据，更准确
			D3DXVECTOR3 AimPos{ 0, 0, 0 };
			D3DXVECTOR2 AimPoint{ 0, 0 };
			Enemy->clientSoldierEntity->GetBonePos(AimPartIndex, &AimPos);

			if (WorldToScreen(AimPos, AimPoint))
			{
				AimPoint.x -= g_drawRect.centerX;
				AimPoint.y -= g_drawRect.centerY;
				mouse_event(MOUSEEVENTF_MOVE, (DWORD)AimPoint.x, (DWORD)AimPoint.y, 0, 0);
			}
		}
	}
	else
	{
		AimCount = 0;
	}
}