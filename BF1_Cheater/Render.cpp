/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#include "Render.h"


// 0-4, 5-11, 12-16
enum BoneIndex
{
	BONE_Head = 0,
	BONE_Neck = 1,
	BONE_SPINE2 = 2,
	BONE_SPINE1 = 3,
	BONE_LeftHand = 4,
	BONE_LeftElbowRoll = 5,
	BONE_LeftShoulder = 6,
	BONE_SPINE2_ = 7,
	BONE_RightShoulder = 8,
	BONE_RightElbowRoll = 9,
	BONE_RightHand = 10,
	BONE_LeftFoot = 11,
	BONE_LeftKneeRoll = 12,
	BONE_Spine = 13,
	BONE_RightKneeRoll = 14,
	BONE_RightFoot = 15
};

DWORD BoneIndexArray[17] =
{
	0x35,
	0x33,
	0x7,
	0x6,
	0x5,
	0x10,
	0xE,
	0x8,
	0x7,
	0xA3,
	0xA9,
	0xAB,
	0x115,
	0x11F,
	0x5,
	0x12D,
	0x123
};


Render::Render(fb::ClientPlayer* LocalPlayer_, fb::ClientPlayer* Player_)
{
	this->LocalPlayer = LocalPlayer_;
	this->Player = Player_;

	InitPlayerInfo();
}


void Render::InitPlayerInfo()
{
	for (int i = 0; i < 17; i++)
	{
		D3DXVECTOR3 TemPos = { 0, 0, 0 };
		fb::ClientSoldierEntity* pSoldierEntity = Player->clientSoldierEntity;
		if (!ValidPointer(pSoldierEntity)) continue;
		pSoldierEntity->GetBonePos(BoneIndexArray[i], &TemPos);

		this->BonePosArray[i] = TemPos;

		D3DXVECTOR2 TemPoint = { 0, 0 };
		BoneIsValid[i] = WorldToScreen(TemPos, TemPoint);
		this->BonePointArray[i] = TemPoint;
	}

	EnemyPos = Player->clientSoldierEntity->location;
	IsVisible = !(bool)Player->clientSoldierEntity->occluded;
}


void Render::DrawPartBone(int32_t start, int32_t end, ImColor Color)
{
	D3DXVECTOR2 Point, oPoint;

	for (int i = start; i <= end; i++)
	{
		Point = BonePointArray[i];

		if (i != start)
		{
			DrawLine({ oPoint.x,oPoint.y }, { Point.x,Point.y }, Color);
		}

		oPoint = Point;
	}
}


void Render::BoxEsp()
{
	int LeftIndex = FindLeftPoint();
	int RightIndex = FindRightPoint();
	int LowestIndex = FindLowestPoint();
	int HighesIndex = FindHighestPoint();

	ImColor Color = IsVisible ? g_pMenu->Config_.espColor2 : g_pMenu->Config_.espColor;
	if (BoneIsValid[LeftIndex] && BoneIsValid[RightIndex] &&
		BoneIsValid[LowestIndex] && BoneIsValid[HighesIndex])
	{
		DrawRect({ BonePointArray[LeftIndex].x, BonePointArray[HighesIndex].y }, { BonePointArray[RightIndex].x, BonePointArray[LowestIndex].y }, Color);
	}
}


// 0-4, 5-11, 12-16
void Render::BoneEsp()
{
	ImColor Color = IsVisible ? g_pMenu->Config_.espColor2 : g_pMenu->Config_.espColor;

	DrawPartBone(0, 4, Color);
	DrawPartBone(5, 11, Color);
	DrawPartBone(12, 16, Color);
}


void Render::NameEsp()
{
	D3DXVECTOR2 EnemyPoint{ 0, 0 };
	char* NameText = Player->szName;

	if (WorldToScreen(EnemyPos, EnemyPoint, -2.0f))
	{
		DrawText_(EnemyPoint, NameText, 16.f, ImColor(255, 255, 255));
	}
}


void Render::DistanceEsp()
{
	D3DXVECTOR3 MyPos = LocalPlayer->clientSoldierEntity->location;
	D3DXVECTOR2 EnemyPoint{ 0, 0 };

	char DistanceText[56] = { 0 };

	float Distance = sqrtf(powf(MyPos.x - EnemyPos.x, 2) + powf(MyPos.y - EnemyPos.y, 2) + powf(MyPos.z - EnemyPos.z, 2));
	wsprintf(DistanceText, "%dm", (DWORD)Distance);

	if (WorldToScreen(EnemyPos, EnemyPoint))
	{
		DrawText_(EnemyPoint, DistanceText, 16.f, ImColor(255, 255, 255));
	}
}


void Render::BloodEsp()
{
	int LeftIndex = FindLeftPoint();
	int LowestIndex = FindLowestPoint();
	int HighestIndex = FindHighestPoint();
	ImColor Color = (0, 255, 0);

	if (Player->clientSoldierEntity->healthcomponent->m_Health < 50)
		 Color = ImColor(255, 0, 0);

	float FilledW = (float)(Player->clientSoldierEntity->healthcomponent->m_Health) / 100.f * (BonePointArray[HighestIndex].y - BonePointArray[LowestIndex].y);
	
	if (BoneIsValid[LeftIndex] && BoneIsValid[LowestIndex] && BoneIsValid[HighestIndex])
	{
		DrawRect({ BonePointArray[LeftIndex].x - 5,BonePointArray[LowestIndex].y }, { BonePointArray[LeftIndex].x - 2,BonePointArray[HighestIndex].y }, ImColor(0, 0, 0));
		DrawFullRect({ BonePointArray[LeftIndex].x - 4,BonePointArray[LowestIndex].y }, { BonePointArray[LeftIndex].x - 3,BonePointArray[LowestIndex].y + FilledW }, Color);
	}
}


void Render::SnapEsp()
{
	D3DXVECTOR2 EnemyPoint{ 0, 0 };
	ImColor Color = IsVisible ? g_pMenu->Config_.espColor2 : g_pMenu->Config_.espColor;
	if (WorldToScreen(EnemyPos, EnemyPoint, 3.0f))
	{
		DrawLine({ (float)g_drawRect.centerX, 0 }, EnemyPoint, Color);
	}
}


void Render::AimRangeEsp()
{
	DrawCricle({ (float)g_drawRect.centerX, (float)g_drawRect.centerY }, g_pMenu->Config_.aimbotRange, ImColor(255, 255, 255));
}


int Render::FindLeftPoint()
{
	int ret = 0;

	for (int i = 0; i < 16; i++)
	{
		if (BonePointArray[i].x < BonePointArray[ret].x)
			ret = i;
	}

	return ret;
}


int Render::FindRightPoint()
{
	int ret = 0;

	for (int i = 0; i < 16; i++)
	{
		if (BonePointArray[i].x > BonePointArray[ret].x)
			ret = i;
	}

	return ret;
}


int Render::FindHighestPoint()
{
	int ret = 0;

	for (int i = 0; i < 16; i++)
	{
		if (BonePointArray[i].y < BonePointArray[ret].y)
			ret = i;
	}

	return ret;
}


int Render::FindLowestPoint()
{
	int ret = 0;

	for (int i = 0; i < 16; i++)
	{
		if (BonePointArray[i].y > BonePointArray[ret].y)
			ret = i;
	}

	return ret;
}


void Render::DrawLine(D3DXVECTOR2 PointStart, D3DXVECTOR2 PointEnd, ImColor Color)
{
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(PointStart.x, PointStart.y), ImVec2(PointEnd.x, PointEnd.y), Color);
}


void Render::DrawCricle(D3DXVECTOR2 Center, float Redius, ImColor Color)
{
	ImGui::GetForegroundDrawList()->AddCircle(ImVec2(Center.x, Center.y), Redius, Color, 0);
}


void Render::DrawFullCricle(D3DXVECTOR2 Center, float Redius, ImColor Color)
{
	ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(Center.x, Center.y), Redius, Color, 0);
}


void Render::DrawRect(D3DXVECTOR2 PointStart, D3DXVECTOR2 PointEnd, ImColor Color)
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(PointStart.x, PointStart.y), ImVec2(PointEnd.x, PointEnd.y), Color, 0, 0);
}


void Render::DrawFullRect(D3DXVECTOR2 PointStart, D3DXVECTOR2 PointEnd, ImColor Color)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(PointStart.x, PointStart.y), ImVec2(PointEnd.x, PointEnd.y), Color, 0, 0);
}


void Render::DrawText_(D3DXVECTOR2 CenterPoint, const char* Text, float FrontSize, ImColor Color)
{
	ImGui::GetForegroundDrawList()->AddText(g_pMenu->Config_.pEspFont, FrontSize, ImVec2(CenterPoint.x, CenterPoint.y), Color, Text);
}