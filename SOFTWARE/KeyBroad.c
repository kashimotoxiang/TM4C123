#include "Keybroad.h"

//*****************************************************************************
//
//��������
//
//*****************************************************************************
uint8_t KeyBroad_Array[4][4]=
{
	1				       ,2			,3					,0,
	4				       ,5			,6					,0,
	7				       ,8			,9					,0,
	0    ,0		,0		,0
};
static inline int Row_KeyBroadScan(uint8_t row);
//*****************************************************************************
//
// ����ɨ�����
//
//*****************************************************************************
uint32_t KeyBroadScan(void) {
	/*��������-------------------------------------------------------*/
	int result = e_ERROR;
	/*��һ��-------------------------------------------------------*/
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN4 | OUTPIN1 | OUTPIN2, e_KeyTrue);
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN3, e_KeyFalse);
	result = Row_KeyBroadScan(0);
	if (result != e_ERROR)
		return result;
	//�ڶ���----------------------------------------------------------------------------//
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN4 | OUTPIN1 | OUTPIN3, e_KeyTrue);
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN2, e_KeyFalse);
	result = Row_KeyBroadScan(1);
	if (result != e_ERROR)
		return result;
	//������----------------------------------------------------------------------------//
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN4 | OUTPIN2 | OUTPIN3, e_KeyTrue);
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN1, e_KeyFalse);
	result = Row_KeyBroadScan(2);
	if (result != e_ERROR)
		return result;
	//������----------------------------------------------------------------------------//
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN1 | OUTPIN2 | OUTPIN3, e_KeyTrue);
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN4, e_KeyFalse);
	result = Row_KeyBroadScan(3);
	return result; //��ôҲ�÷�����
}
//*****************************************************************************
//
// ������ɨ�����
//
//*****************************************************************************
static inline int Row_KeyBroadScan(uint8_t row) {
	if (ROW0 != e_KeyTrue) {
		while (ROW0 != e_KeyTrue)
			;
		return KeyBroad_Array[row][0];
	}
	if (ROW1 != e_KeyTrue) {
		while (ROW1 != e_KeyTrue)
			;
		return KeyBroad_Array[row][1];
	}
	if (ROW2 != e_KeyTrue) {
		while (ROW2 != e_KeyTrue)
			;
		return KeyBroad_Array[row][2];
	}
	if (ROW3 != e_KeyTrue) {
		while (ROW3 != e_KeyTrue)
			;
		return KeyBroad_Array[row][3];
	}
	return e_ERROR;
}
