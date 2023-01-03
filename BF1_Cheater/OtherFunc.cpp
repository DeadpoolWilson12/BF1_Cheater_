/****************************************************************************************************
	版本:1.0

	作者:热饭班长1997
	
	特别声明:该代码仅供学习交流使用,请勿用于商业用途和非法用途,如作他用所造成的一切后果和法律责任一概与本人无关

创建时间:2023-01-03 14:59

*****************************************************************************************************/
#include "OtherFunc.h"
#include "DX11.h"
#include "Help.h"


void WINAPI accuracyCallback()
{
	printf("accuracyCallback\n");
	if (false && g_pMenu->Config_.noRecoil)
	{

		/*context->Xmm0.High = 0;
		context->Xmm0.Low = 0;

		context->Xmm2.Low = 0;
		context->Xmm2.High = 0;

		uintptr_t ModifyAddr = (uintptr_t)(context->Rsp + 0x4C);
		uintptr_t value = 0;
		bool bRet = WriteBuffer(ModifyAddr, &value);
		
		printf("bRet:%d\n", bRet);*/
	}
}


void WINAPI noRecoilCallback()
{
	printf("noRecoilCallback\n");
	if (g_pMenu->Config_.noRecoil)
	{

		/*uintptr_t ModifyAddr1 = (uintptr_t)(context->Rsi + 0x6C);
		uintptr_t ModifyAddr2 = (uintptr_t)(context->Rsi + 0x68);

		uintptr_t value = 0;
		bool bRet = WriteBuffer(ModifyAddr1, &value);
		bRet = WriteBuffer(ModifyAddr2, &value);
		
		printf("bRet:%d\n", bRet);*/
	}
}


void WINAPI overHeatCallback()
{
	printf("overHeatCallback\n");
	if (g_pMenu->Config_.noOverheat)
	{

		//context->Xmm0.High = 0;
		//context->Xmm0.Low = 0;
	}
}