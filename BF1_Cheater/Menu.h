/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

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
		ImFont* pMenuFont = NULL; //菜单字体
		ImFont* pEspFont = NULL; //Esp字体

		bool showMenu = true; //显示菜单
		int aimbotRange = 251; // 自瞄范围
		int espDistance = 251; // 透视范围
		ImColor espColor = { 255, 255, 0 }; // 透视颜色
		ImColor espColor2 = { 255, 0, 0 }; // 敌人可见颜色

		bool openEsp = false; // 透视开关
		bool boxEsp = false; // 方框透视
		bool nameEsp = false; // 显示名字
		bool aimRangeEsp = false; // 自瞄范围
		bool snapEsp = false; // 连线
		bool bloodEsp = false; // 血量透视
		bool distanceEsp = false; // 显示距离
		bool boneEsp = false; // 骨骼透视

		bool aimbot = false; // 自瞄
		int aimbotType = 0; // 0：头部 1：胸部
		bool noRecoil = false; // 无后座力
		bool accuracyRaise = false; // 提升精确度
		bool noOverheat = false; // 不过热
		bool MultipleDamage = false; // 子弹伤害翻倍
		bool magicBullet = false; // 魔术子弹
	}Config_;

	void switchState();
	void RenderMenu();
};


#endif // !MENU_H

