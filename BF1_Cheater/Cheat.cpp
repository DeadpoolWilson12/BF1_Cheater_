/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#include "Cheat.h"
#include "Frosbite.h"
#include "Obfuscationmgr.h"
#include "Render.h"
#include "AimBot.h"
#include "OtherFunc.h"
#include "Help.h"


Cheater::Cheater(Menu* g_pMenu)
{
	g_pMenuRef = g_pMenu;

	if (InitCurrentModuleInfo())
	{
		accuracyAddr = (DWORD64)GetAddrBypattern(ACCURACY_PATTERN, sizeof(ACCURACY_PATTERN) - 1);
		recoilAddr = (DWORD64)GetAddrBypattern(RECOIL_PATTERN, sizeof(RECOIL_PATTERN) - 1);
		overheatAddr = (DWORD64)GetAddrBypattern(OVERHEAT_PATTERN, sizeof(OVERHEAT_PATTERN) - 1);
		multipleDamage = (DWORD64)GetAddrBypattern(BULLETDAMAGE_PATTERN, sizeof(BULLETDAMAGE_PATTERN) - 1);
		ReleaseModuleInfo();
	}
	// else printf("InitCurrentModuleInfo()失败\n");
	printf("accuracyAddr:%p, recoilAddr:%p, overheatAddr:%p, multipleDamage:%p\n",
		accuracyAddr, recoilAddr, overheatAddr, multipleDamage);

	this->HookInit();
}


void Cheater::HookInit()
{
	/*try
	{
		hook1.install(accuracyAddr, accuracyCallback);
		hook2.install(recoilAddr, noRecoilCallback);
		hook3.install(overheatAddr, overHeatCallback);
	}
	catch (int exception)
	{
		printf("hook异常,Code:(%d)\n", exception);
	}*/
	memcpy(InjectShell1, "\x0F\x57\xC0\x0F\x28\xD0\xC7\x44\x24\x4C\x00\x00\x00\x00", sizeof("\x0F\x57\xC0\x0F\x28\xD0\xC7\x44\x24\x4C\x00\x00\x00\x00"));
	memcpy(InjectShell2, "\xC7\x46\x6C\x00\x00\x00\x00\xC7\x46\x68\x00\x00\x00\x00", sizeof("\xC7\x46\x6C\x00\x00\x00\x00\xC7\x46\x68\x00\x00\x00\x00"));
	memcpy(InjectShell3, "\x0F\x57\xC0", sizeof("\x0F\x57\xC0"));
	memcpy(InjectShell4, "\xB8\x80\x00\x00\x00", sizeof("\xB8\x40\x00\x00\x00"));

	// 0x18CC00000
	bool bRet1 = hook1.Install((HANDLE)-1, accuracyAddr, InjectShell1, 14, 6, 0x14CD76603);
	bool bRet2 = hook2.Install((HANDLE)-1, recoilAddr, InjectShell2, 14, 5, 0x14CD76703);
	bool bRet3 = hook3.Install((HANDLE)-1, overheatAddr, InjectShell3, 3, 8, 0x14CD76803);
	bool bRet4 = hook4.Install((HANDLE)-1, multipleDamage, InjectShell4, 5, 6, 0x14CD76903);
	printf("hook1_bRet1:%d, hook2_bRet2:%d, hook3_bRet3:%d, hook4_bRet4:%d\n"
		, bRet1, bRet2, bRet3, bRet4);
}


void Cheater::DoCheat()
{
	//----其它功能
	HookFunc();

	fb::ClientPlayer* pLocalPlayer = GetLocalPlayer();
	if (!ValidPointer(pLocalPlayer) || pLocalPlayer->szName == NULL) return;

	fb::ClientSoldierEntity* pMySoldierEntity = pLocalPlayer->clientSoldierEntity;
	if (!ValidPointer(pMySoldierEntity)) return;

	// printf("pLocalPlayer->teamId:%d\n", pLocalPlayer->teamId);

	if (pMySoldierEntity->IsDead()) return;

	if (pMySoldierEntity->IsValid() == false) return;

	for (int i = 0; i < 64; i++)
	{
		fb::ClientPlayer* pPlayer = GetPlayerById(i);
		if (!ValidPointer(pPlayer)) continue;

		fb::ClientSoldierEntity* pSoldierEntity = pPlayer->clientSoldierEntity;
		if (!ValidPointer(pSoldierEntity)) continue;

		// printf("pPlayer->teamId:%d\n", pPlayer->teamId);
		if (pPlayer->teamId == pLocalPlayer->teamId) continue;

		if (pSoldierEntity->IsDead()) continue;

		if (pSoldierEntity->IsValid() == false) continue;

		D3DXVECTOR3 MyPos = pLocalPlayer->clientSoldierEntity->location;
		D3DXVECTOR3 EnemyPos = pPlayer->clientSoldierEntity->location;
		float Distance = sqrtf(powf(MyPos.x - EnemyPos.x, 2) + powf(MyPos.y - EnemyPos.y, 2) + powf(MyPos.z - EnemyPos.z, 2));
		if (Distance <= 0 || (int)Distance > g_pMenuRef->Config_.espDistance) continue;

		Render RenderIns(pLocalPlayer, pPlayer);
		
		if (g_pMenuRef->Config_.aimbot && pSoldierEntity->IsVisible()) 
			Aimbot::GetInstance().Push(pLocalPlayer, pPlayer);

		if (g_pMenuRef->Config_.openEsp && g_pMenuRef->Config_.boxEsp)
			RenderIns.BoxEsp();
		
		if (g_pMenuRef->Config_.openEsp && g_pMenuRef->Config_.nameEsp)
			RenderIns.NameEsp();
		
		if (g_pMenuRef->Config_.openEsp && g_pMenuRef->Config_.boneEsp)
			RenderIns.BoneEsp();

		if (g_pMenuRef->Config_.openEsp && g_pMenuRef->Config_.bloodEsp)
			RenderIns.BloodEsp();

		if (g_pMenuRef->Config_.openEsp && g_pMenuRef->Config_.distanceEsp)
			RenderIns.DistanceEsp();

		if (g_pMenuRef->Config_.openEsp && g_pMenuRef->Config_.aimRangeEsp)
			RenderIns.AimRangeEsp();

		if (g_pMenuRef->Config_.openEsp && g_pMenuRef->Config_.snapEsp)
			RenderIns.SnapEsp();

	}
	if (g_pMenuRef->Config_.aimbot)
	{
		Aimbot::GetInstance().LockPlayer();
		Aimbot::GetInstance().SmoothAimbot();
	}
}


void Cheater::HookFunc()
{
	// 提高射击精确
	if (g_pMenuRef->Config_.accuracyRaise && IS_hooked1 == false)
	{
		bool bRet = hook1.StartHook();
		IS_hooked1 = true;
	}
	else if (!g_pMenuRef->Config_.accuracyRaise && IS_hooked1 == true)
	{
		hook1.EndHook();
		IS_hooked1 = false;
	}

	// 无后座
	if (g_pMenuRef->Config_.noRecoil && IS_hooked2 == false)
	{
		hook2.StartHook();
		IS_hooked2 = true;
	}
	else if (!g_pMenuRef->Config_.noRecoil && IS_hooked2 == true)
	{
		hook2.EndHook();
		IS_hooked2 = false;
	}

	// 武器不过热
	if (g_pMenuRef->Config_.noOverheat && IS_hooked3 == false)
	{
		hook3.StartHook();
		IS_hooked3 = true;
	}
	else if (!g_pMenuRef->Config_.noOverheat && IS_hooked3 == true)
	{
		hook3.EndHook();
		IS_hooked3 = false;
	}

	// 子弹伤害加倍
	if (g_pMenuRef->Config_.MultipleDamage && IS_hooked4 == false)
	{
		hook4.StartHook();
		IS_hooked4 = true;
	}
	else if (!g_pMenuRef->Config_.MultipleDamage && IS_hooked4 == true)
	{
		hook4.EndHook();
		IS_hooked4 = false;
	}
}