#include "Keybroad.h"

//*****************************************************************************
//
//键盘数组
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
// 键盘扫描程序
//
//*****************************************************************************
uint32_t KeyBroadScan(void) {
	/*变量定义-------------------------------------------------------*/
	int result = e_ERROR;
	/*第一行-------------------------------------------------------*/
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN4 | OUTPIN1 | OUTPIN2, e_KeyTrue);
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN3, e_KeyFalse);
	result = Row_KeyBroadScan(0);
	if (result != e_ERROR)
		return result;
	//第二行----------------------------------------------------------------------------//
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN4 | OUTPIN1 | OUTPIN3, e_KeyTrue);
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN2, e_KeyFalse);
	result = Row_KeyBroadScan(1);
	if (result != e_ERROR)
		return result;
	//第三行----------------------------------------------------------------------------//
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN4 | OUTPIN2 | OUTPIN3, e_KeyTrue);
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN1, e_KeyFalse);
	result = Row_KeyBroadScan(2);
	if (result != e_ERROR)
		return result;
	//第四行----------------------------------------------------------------------------//
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN1 | OUTPIN2 | OUTPIN3, e_KeyTrue);
	GPIOPinWrite(Keybroad_Control_Port, OUTPIN4, e_KeyFalse);
	result = Row_KeyBroadScan(3);
	return result; //怎么也得返回了
}
//*****************************************************************************
//
// 键盘行扫描程序
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
