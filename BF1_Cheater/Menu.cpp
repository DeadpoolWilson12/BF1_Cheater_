/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#include "Menu.h"


void Menu::switchState()
{
	// 控制窗口显示/隐藏
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

	// 菜单隐藏，不绘制菜单
	if (!Config_.showMenu)
	{
		return;
	}
	{
		ImGui::Begin(u8"By:热饭班长1997");
		ImGui::TextColored(ImColor(220, 20, 60, 255), u8"【Ins】隐藏/显示菜单");
		ImGui::Text(u8"窗口背景风格");
		ImGui::SameLine();
		ImGui::ShowStyleSelector("##Selector");
		ImGui::Checkbox(u8"【透视总开关】", &Config_.openEsp);
		ImGui::SliderInt(u8"透视范围", &Config_.espDistance, 0, 800);
		ImGui::TextColored(ImColor(0, 191, 255, 255), u8"透视选项");
		if (ImGui::BeginTable("split", 2))
		{
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"方框透视  【F1】", &Config_.boxEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"连线透视  【F2】", &Config_.snapEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"骨头透视  【F3】", &Config_.boneEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"血条透视  【F4】", &Config_.bloodEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"距离透视  【F5】", &Config_.distanceEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"显示名字  【00】", &Config_.nameEsp);
			ImGui::TableNextColumn(); ImGui::Checkbox(u8"自苗范围  【00】", &Config_.aimRangeEsp);
			ImGui::EndTable();
		}

		ImGui::TextColored(ImColor(0, 191, 255, 255), u8"透视颜色");
		static int espColorIndex = 3;
		ImGui::RadioButton(u8"红", &espColorIndex, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"黄", &espColorIndex, 1); ImGui::SameLine();
		ImGui::RadioButton(u8"蓝", &espColorIndex, 2); ImGui::SameLine();
		ImGui::RadioButton(u8"绿", &espColorIndex, 3);
		ImGui::RadioButton(u8"自定义颜色", &espColorIndex, 4); ImGui::SameLine();
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

		ImGui::TextColored(ImColor(0, 191, 255, 255), u8"敌人可见颜色");
		static int espColorIndex2 = 0;
		ImGui::RadioButton(u8"红 ", &espColorIndex2, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"黄 ", &espColorIndex2, 1); ImGui::SameLine();
		ImGui::RadioButton(u8"蓝 ", &espColorIndex2, 2); ImGui::SameLine();
		ImGui::RadioButton(u8"绿 ", &espColorIndex2, 3);
		ImGui::RadioButton(u8"自定义颜色 ", &espColorIndex2, 4); ImGui::SameLine();
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

		ImGui::TextColored(ImColor(0, 191, 255, 255), u8"射击选项");
		ImGui::Checkbox(u8"平滑自苗  【F6】", &Config_.aimbot);
		ImGui::SameLine();
		ImGui::RadioButton(u8"头部", &Config_.aimbotType, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"胸部", &Config_.aimbotType, 1);
		ImGui::SliderInt(u8"自苗范围", &Config_.aimbotRange, 0, 500);

		ImGui::Checkbox(u8"无后坐力", &Config_.noRecoil); ImGui::SameLine();
		ImGui::Checkbox(u8"修正射击精确度", &Config_.accuracyRaise);
		ImGui::Checkbox(u8"枪械不过热", &Config_.noOverheat); ImGui::SameLine();
		ImGui::Checkbox(u8"子弹伤害翻多倍", &Config_.MultipleDamage);

		ImGui::TextColored(ImColor(0, 191, 255, 255), u8"其他功能");
		ImGui::Checkbox(u8"魔术子弹(子弹追踪)", &Config_.magicBullet);

		ImGui::TextColored(ImColor(220, 20, 60, 255), u8"请隐藏菜单再进行游戏！！！");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}

