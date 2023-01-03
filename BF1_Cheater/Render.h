/****************************************************************************************************
	�汾:1.0

	����:�ȷ��೤1997
	
	�ر�����:�ô������ѧϰ����ʹ��,����������ҵ��;�ͷǷ���;,������������ɵ�һ�к���ͷ�������һ���뱾���޹�

����ʱ��:2023-01-03 14:59

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

