/****************************************************************************************************
	�汾:1.0

	����:�ȷ��೤1997
	
	�ر�����:�ô������ѧϰ����ʹ��,����������ҵ��;�ͷǷ���;,������������ɵ�һ�к���ͷ�������һ���뱾���޹�

����ʱ��:2023-01-03 14:59

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