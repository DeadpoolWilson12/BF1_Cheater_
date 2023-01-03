/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#ifndef RENDER_H
#define RENDER_H

#include "Base.h"
#include "DX11.h"
#include "Frosbite.h"


class Render
{
public:

	Render(fb::ClientPlayer* LocalPlayer_, fb::ClientPlayer* Player_);
	
	void BoxEsp();
	
	void BoneEsp();

	void NameEsp();

	void DistanceEsp();
	
	void BloodEsp();
	
	void SnapEsp();

	void AimRangeEsp();
private:

	void InitPlayerInfo();

	void DrawPartBone(int32_t start, int32_t end, ImColor Color);
	
	int FindLeftPoint();
	
	int FindRightPoint();
	
	int FindHighestPoint();
	
	int FindLowestPoint();

	void DrawLine(D3DXVECTOR2 PointStart, D3DXVECTOR2 PointEnd, ImColor Color);
	void DrawCricle(D3DXVECTOR2 Center, float Redius, ImColor Color);
	void DrawRect(D3DXVECTOR2 PointStart, D3DXVECTOR2 PointEnd, ImColor Color);
	void DrawText_(D3DXVECTOR2 CenterPoint, const char* Text, float FrontSize, ImColor Color);
	void DrawFullRect(D3DXVECTOR2 PointStart, D3DXVECTOR2 PointEnd, ImColor Color);
	void DrawFullCricle(D3DXVECTOR2 Center, float Redius, ImColor Color);

	fb::ClientPlayer* LocalPlayer = NULL;
	fb::ClientPlayer* Player = NULL;
	D3DXVECTOR3 BonePosArray[17];
	D3DXVECTOR2 BonePointArray[17];
	bool        BoneIsValid[17];
	D3DXVECTOR3 EnemyPos;

	bool IsVisible = false;
};


#endif // !RENDER_H

