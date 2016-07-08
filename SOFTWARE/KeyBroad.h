#pragma once

//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//
// define
//
//*****************************************************************************
/*控制组-------------------------------------------------------*/
#define Keybroad_Control_Port             GPIO_PORTB_BASE
#define Keybroad_PortSYSCTL_PERIPH        SYSCTL_PERIPH_GPIOB
/*引脚-------------------------------------------------------*/
#define OUTPIN1 GPIO_PIN_0
#define OUTPIN2 GPIO_PIN_1
#define OUTPIN3 GPIO_PIN_2
#define OUTPIN4 GPIO_PIN_3
#define INPIN1  GPIO_PIN_4
#define INPIN2  GPIO_PIN_5
#define INPIN3  GPIO_PIN_6
#define INPIN4  GPIO_PIN_7
/*输入组-------------------------------------------------------*/
#define ROW0 GPIOPinRead(Keybroad_Control_Port,INPIN1)
#define ROW1 GPIOPinRead(Keybroad_Control_Port,INPIN2)
#define ROW2 GPIOPinRead(Keybroad_Control_Port,INPIN3)
#define ROW3 GPIOPinRead(Keybroad_Control_Port,INPIN4)
//*****************************************************************************
//
//enum
//
//*****************************************************************************
/*按键状态-------------------------------------------------------*/
#define e_KeyTrue 		0
#define e_KeyFalse 		!e_KeyTrue
//*****************************************************************************
//
// declartion
//
//*****************************************************************************
uint32_t KeyBroadScan(void);
