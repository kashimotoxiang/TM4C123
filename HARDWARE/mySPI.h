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
#define g_pui8RxBuf g_ADConvBuf
#define g_pui8TxBuf g_SPITxBuf
//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void SPI0Init(void);
void SPI0uDMAIntHandler(void);
void SPI0_uDMAInit(void);
void uDMAIntHandler(void);