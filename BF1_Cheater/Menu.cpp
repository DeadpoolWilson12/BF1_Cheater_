/****************************************************************************************************
	�汾:1.0

	����:�ȷ��೤1997
	
	�ر�����:�ô������ѧϰ����ʹ��,����������ҵ��;�ͷǷ���;,������������ɵ�һ�к���ͷ�������һ���뱾���޹�

����ʱ��:2023-01-03 14:59

*****************************************************************************************************/
#include "Menu.h"


void Menu::switchState()
{
	// ���ƴ�����ʾ/����
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		Config_.showMenu = !Config_.showMenu;
	}

	if (GetAsyncKeyState(VK_F1) & 1)
	{
		Config_.boxEsp = !Config_.boxEsp;
	}

	if (GetAsyncKeyState(VK_F2) & 1)
	{
		Config_.snapEsp = !Config_.snapEsp;
	}

	if (GetAsyncKeyState(VK_F3) & 1)
	{
		Config_.boneEsp = !Config_.boneEsp;
	}

	if (GetAsyncKeyState(VK_F4) & 1)
	{
		Config_.bloodEsp = !Config_.bloodEsp;
	}

	if (GetAsyncKeyState(VK_F5) & 1)
	{
		Config_.distanceEsp = !Config_.distanceEsp;
	}

	if (GetAsyncKeyState(VK_F6) & 1)
	{
		Config_.aimbot = !Config_.aimbot;
	}
}


void Menu::RenderMenu()
{
	switchState();

	// �˵����أ������Ʋ˵�
	if (!Config_.showMenu)
	{
		return;
	}
	{
		ImGui::Begin(u8"By:�ȷ��೤1997");
		ImGui::TextColored(ImColor(220, 20, 60, 255), u8"��Ins������/��ʾ�˵�");
		ImGui::Text(u8"���ڱ������");
		ImGui::SameLine();
		ImGui::ShowStyleSelector("##Selector");
		ImGui::Checkbox(u8"��͸���ܿ��ء�", &Config_.openEsp);
		ImGui::SliderInt(u8"͸�ӷ�Χ", &Config_.espDistance, 0, 800);
		ImGui::TextColored(ImColor(0, 191, 255, 255), u8"͸��ѡ��");
		if (ImGui::BeginTable("split", 2))
		{
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"����͸��  ��F1��", &Config_.boxEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"����͸��  ��F2��", &Config_.snapEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"��ͷ͸��  ��F3��", &Config_.boneEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"Ѫ��͸��  ��F4��", &Config_.bloodEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"����͸��  ��F5��", &Config_.distanceEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"��ʾ����  ��00��", &Config_.nameEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"���緶Χ  ��00��", &Config_.aimRangeEsp);
			ImGui::EndTable();
		}

		ImGui::TextColored(ImColor(0, 191, 255, 255), u8"͸����ɫ");
		static int espColorIndex = 3;
		ImGui::RadioButton(u8"��", &espColorIndex, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"��", &espColorIndex, 1); ImGui::SameLine();
		ImGui::RadioButton(u8"��", &espColorIndex, 2); ImGui::SameLine();
		ImGui::RadioButton(u8"��", &espColorIndex, 3);
		ImGui::RadioButton(u8"�Զ�����ɫ", &espColorIndex, 4); ImGui::SameLine();
		ImGui::ColorEdit3(" ", (float*)&Customize_color);

		switch (espColorIndex)
		{
		case 0:
			Config_.espColor = ImColor(255, 0, 0);
			break;
		case 1:
			Config_.espColor = ImColor(255, 255, 0);
			break;
		case 2:
			Config_.espColor = ImColor(0, 0, 255);
			break;
		case 3:
			Config_.espColor = ImColor(0, 255, 0);
			break;
		case 4:
			Config_.espColor = ImColor(Customize_color.x, Customize_color.y, Customize_color.z, Customize_color.w);
			break;
		default:
			break;
		}

		ImGui::TextColored(ImColor(0, 191, 255, 255), u8"���˿ɼ���ɫ");
		static int espColorIndex2 = 0;
		ImGui::RadioButton(u8"�� ", &espColorIndex2, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"�� ", &espColorIndex2, 1); ImGui::SameLine();
		ImGui::RadioButton(u8"�� ", &espColorIndex2, 2); ImGui::SameLine();
		ImGui::RadioButton(u8"�� ", &espColorIndex2, 3);
		ImGui::RadioButton(u8"�Զ�����ɫ ", &espColorIndex2, 4); ImGui::SameLine();
		ImGui::ColorEdit3("", (float*)&Customize_color2);

		switch (espColorIndex2)
		{
		case 0:
			Config_.espColor2 = ImColor(255, 0, 0);;
			break;
		case 1:
			Config_.espColor2 = ImColor(255, 255, 0);
			break;
		case 2:
			Config_.espColor2 = ImColor(0, 0, 255);
			break;
		case 3:
			Config_.espColor2 = ImColor(0, 255, 0);
			break;
		case 4:
			Config_.espColor2 = ImColor(Customize_color2.x, Customize_color2.y, Customize_color2.z, Customize_color2.w);
			break;
		default:
			break;
		}

		ImGui::TextColored(ImColor(0, 191, 255, 255), u8"���ѡ��");
		ImGui::Checkbox(u8"ƽ������  ��F6��", &Config_.aimbot);
		ImGui::SameLine();
		ImGui::RadioButton(u8"ͷ��", &Config_.aimbotType, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"�ز�", &Config_.aimbotType, 1);
		ImGui::SliderInt(u8"���緶Χ", &Config_.aimbotRange, 0, 500);

		ImGui::Checkbox(u8"�޺�����", &Config_.noRecoil); ImGui::SameLine();
		ImGui::Checkbox(u8"���������ȷ��", &Config_.accuracyRaise);
		ImGui::Checkbox(u8"ǹе������", &Config_.noOverheat); ImGui::SameLine();
		ImGui::Checkbox(u8"�ӵ��˺����౶", &Config_.MultipleDamage);

		ImGui::TextColored(ImColor(0, 191, 255, 255), u8"��������");
		ImGui::Checkbox(u8"ħ���ӵ�(�ӵ�׷��)", &Config_.magicBullet);

		ImGui::TextColored(ImColor(220, 20, 60, 255), u8"�����ز˵��ٽ�����Ϸ������");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}

