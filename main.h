#pragma once

//*****************************************************************************
//
// include
//
//*****************************************************************************

/*System-------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "inc/hw_ssi.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"
#include "driverlib/udma.h"
#include "driverlib/ssi.h"
/*Hardware-------------------------------------------------------*/
#include "mySPI.h"
#include "myADC.h"
//#include "myUART.h"
#include "System.h"
#include "pinout.h"
/*Software-------------------------------------------------------*/
#include "KeyBroad.h"
#include "KeyInt.h"

//*****************************************************************************
//
// define
//
//*****************************************************************************
#define SPI_TXBUF_SIZE         256
#define SPI_RXBUF_SIZE         256

//*****************************************************************************
//
// enum
//
//*****************************************************************************
/*ͨʶ״̬-------------------------------------------------------*/
#define e_SUCCESS 1
#define e_FLASE   0
#define e_ERROR  -1

//*****************************************************************************
//
// Type
//
//*****************************************************************************
typedef uint8_t ADConvType;

//*****************************************************************************
//
//extern
//
//*****************************************************************************
extern uint8_t g_SPITxBuf[SPI_TXBUF_SIZE];
extern ADConvType g_ADConvBuf[SPI_RXBUF_SIZE];
extern uint8_t ucControlTable[1024];
