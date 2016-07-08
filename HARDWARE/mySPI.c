#include "mySPI.h"
//*****************************************************************************
//
//note:
//SSIDataPut(SSI0_BASE, ui32Data);//发送一次数据
//SSIDataGet(SSI0_BASE, &ui32Data);//接受一次数据
//uDMAChannelRequest(UDMA_CHANNEL_SSI0RX);//启动DMA接受
//uDMAChannelRequest(UDMA_CHANNEL_SSI0TX);//启动DMA发送
//*****************************************************************************

//*****************************************************************************
//
// Static Varible
//
//*****************************************************************************

// Transfer counters
static uint32_t g_ui32BadISR = 0;
/*Normal-------------------------------------------------------*/
//*****************************************************************************
//
// SSI初始化
//
//*****************************************************************************
void SPI0Init(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_1,
	SSI_MODE_MASTER, 2000000, 8);
	SSIEnable(SSI0_BASE);
}

/*uDMA-------------------------------------------------------*/
//*****************************************************************************
//
// Initialize SSI uDMA transfer
//
//*****************************************************************************
void SPI0_uDMAInit(void) {
	// Enable SSI0 and make sure it can run while the CPU sleeps
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	ROM_SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_SSI0);

	// Configure and enable the SSI with DMA
	ROM_SSIConfigSetExpClk(SSI0_BASE, ROM_SysCtlClockGet(), SSI_FRF_MOTO_MODE_1,
	SSI_MODE_MASTER, 2000000, 8);

	ROM_SSIEnable(SSI0_BASE);
	ROM_SSIDMAEnable(SSI0_BASE, SSI_DMA_RX | SSI_DMA_TX);

	/*-------------------------------------------------------*/
	/*uDMA配置*/
	/*-------------------------------------------------------*/
	// Enable interrupts from the uDMA software channel.
	ROM_IntEnable(INT_UDMA);
	// Receive channel setup for a basic recieve
	ROM_uDMAChannelAttributeDisable(UDMA_CHANNEL_SSI0RX,
			UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT
					| (UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK));

	ROM_uDMAChannelControlSet(UDMA_CHANNEL_SSI0RX | UDMA_PRI_SELECT,
	UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 | UDMA_ARB_64);

	ROM_uDMAChannelTransferSet(UDMA_CHANNEL_SSI0RX | UDMA_PRI_SELECT,
	UDMA_MODE_BASIC, (void *) (SSI0_BASE + SSI_O_DR), g_pui8RxBuf,
			sizeof(g_pui8RxBuf));

	// Transmit channel setup for a basic transfer
	ROM_uDMAChannelAttributeDisable(UDMA_CHANNEL_SSI0TX,
			UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT
					| (UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK));

	ROM_uDMAChannelAttributeEnable(UDMA_CHANNEL_SSI0TX, UDMA_ATTR_USEBURST);

	ROM_uDMAChannelControlSet(UDMA_CHANNEL_SSI0TX | UDMA_PRI_SELECT,
	UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_NONE | UDMA_ARB_64);

	ROM_uDMAChannelTransferSet(UDMA_CHANNEL_SSI0TX | UDMA_PRI_SELECT,
	UDMA_MODE_BASIC, g_pui8TxBuf, (void *) (SSI0_BASE + SSI_O_DR),
			sizeof(g_pui8TxBuf));

	// Enable both channels
	//ROM_uDMAChannelEnable(UDMA_CHANNEL_SSI0RX);
	ROM_uDMAChannelEnable(UDMA_CHANNEL_SSI0TX);

	uDMAChannelRequest(UDMA_CHANNEL_SSI0TX);	//启动DMA发送
}

/*uDMA_Handle-------------------------------------------------------*/
//*****************************************************************************
//
// SSI interrupt handler. Called on completion of uDMA transfer
//
//*****************************************************************************
void SPI0uDMAIntHandler(void) {
	uint32_t ui32Mode;

	delay_ms(100);
	// Check for the primary control structure to indicate complete.
	/*-------------------------------------------------------*/
	ui32Mode = ROM_uDMAChannelModeGet(UDMA_CHANNEL_SSI0RX);
	if (ui32Mode == UDMA_MODE_STOP) {
		ROM_uDMAChannelControlSet(UDMA_CHANNEL_SSI0RX | UDMA_PRI_SELECT,
		UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 | UDMA_ARB_64);

		ROM_uDMAChannelTransferSet(UDMA_CHANNEL_SSI0RX | UDMA_PRI_SELECT,
		UDMA_MODE_BASIC, (void *) (SSI0_BASE + SSI_O_DR), g_pui8RxBuf,
				sizeof(g_pui8RxBuf));
		ROM_uDMAChannelEnable(UDMA_CHANNEL_SSI0RX);
		uDMAChannelRequest(UDMA_CHANNEL_SSI0RX); //启动DMA发送
	}
	/*-------------------------------------------------------*/
	ui32Mode = ROM_uDMAChannelModeGet(UDMA_CHANNEL_SSI0TX);
	if (ui32Mode == UDMA_MODE_STOP) {
		ROM_uDMAChannelControlSet(UDMA_CHANNEL_SSI0TX | UDMA_PRI_SELECT,
		UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_NONE | UDMA_ARB_64);

		ROM_uDMAChannelTransferSet(UDMA_CHANNEL_SSI0TX | UDMA_PRI_SELECT,
		UDMA_MODE_BASIC, g_pui8TxBuf, (void *) (SSI0_BASE + SSI_O_DR),
				sizeof(g_pui8TxBuf));

		ROM_uDMAChannelEnable(UDMA_CHANNEL_SSI0TX);
		uDMAChannelRequest(UDMA_CHANNEL_SSI0TX); //启动DMA发送
	}

	// If the channel is not stopped, then something is wrong.
	else {
		g_ui32BadISR++;
	}
}
