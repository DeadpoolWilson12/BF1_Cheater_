/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#ifndef BASE_H
#define BASE_H

#include <Windows.h>
#include <stdio.h>

struct DrawRect
{
	int x;
	int y;
	int width;
	int height;
	int centerX;
	int centerY;
};

extern DrawRect g_drawRect;
extern HWND g_hwnd;

#endif
