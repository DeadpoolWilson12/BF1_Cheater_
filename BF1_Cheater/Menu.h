/****************************************************************************************************
	�汾:1.0

	����:�ȷ��೤1997
	
	�ر�����:�ô������ѧϰ����ʹ��,����������ҵ��;�ͷǷ���;,������������ɵ�һ�к���ͷ�������һ���뱾���޹�

����ʱ��:2023-01-03 14:59

*****************************************************************************************************/
#ifndef MENU_H
#define MENU_H

#include "ImGui/imgui.h"
#include "Base.h"

class Menu
{
	~Menu() {};

public:
	ImVec4 Customize_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImVec4 Customize_color2 = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	struct Config
	{
		ImFont* pMenuFont = NULL; //�˵�����
		ImFont* pEspFont = NULL; //Esp����

		bool showMenu = true; //��ʾ�˵�
		int aimbotRange = 251; // ���鷶Χ
		int espDistance = 251; // ͸�ӷ�Χ
		ImColor espColor = { 255, 255, 0 }; // ͸����ɫ
		ImColor espColor2 = { 255, 0, 0 }; // ���˿ɼ���ɫ

		bool openEsp = false; // ͸�ӿ���
		bool boxEsp = false; // ����͸��
		bool nameEsp = false; // ��ʾ����
		bool aimRangeEsp = false; // ���鷶Χ
		bool snapEsp = false; // ����
		bool bloodEsp = false; // Ѫ��͸��
		bool distanceEsp = false; // ��ʾ����
		bool boneEsp = false; // ����͸��

		bool aimbot = false; // ����
		int aimbotType = 0; // 0��ͷ�� 1���ز�
		bool noRecoil = false; // �޺�����
		bool accuracyRaise = false; // ������ȷ��
		bool noOverheat = false; // ������
		bool MultipleDamage = false; // �ӵ��˺�����
		bool magicBullet = false; // ħ���ӵ�
	}Config_;

	void switchState();
	void RenderMenu();
};


#endif // !MENU_H

