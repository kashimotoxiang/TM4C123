#include "myUART.h"

//*****************************************************************************
//
// define
//
//*****************************************************************************
#define SPI_TXBUF_SIZE         256
#define SPI_RXBUF_SIZE         256
//*****************************************************************************
//
// Static Varible
//
//*****************************************************************************
// Buffer definitions
static uint8_t g_pui8TxBuf[SPI_TXBUF_SIZE];
static uint8_t g_pui8RxPing[SPI_RXBUF_SIZE];
static uint8_t g_pui8RxPong[SPI_RXBUF_SIZE];

// Transfer counters
static uint32_t g_ui32RxPingCount = 0;
static uint32_t g_ui32RxPongCount = 0;

/*Normal-------------------------------------------------------*/
//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count) {
	//
	// Loop while there are more characters to send.
	//
	while (ui32Count--) {
		//
		// Write the next character to the UART.
		//
		ROM_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
	}
}

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void UARTIntHandler(void) {
	uint32_t ui32Status;

	//
	// Get the interrrupt status.
	//
	ui32Status = ROM_UARTIntStatus(UART0_BASE, true);

	//
	// Clear the asserted interrupts.
	//
	ROM_UARTIntClear(UART0_BASE, ui32Status);

	//
	// Loop while there are characters in the receive FIFO.
	//
	while (ROM_UARTCharsAvail(UART0_BASE)) {
		//
		// Read the next character from the UART and write it back to the UART.
		//
		ROM_UARTCharPutNonBlocking(UART0_BASE,
		ROM_UARTCharGetNonBlocking(UART0_BASE));

		//
		// Blink the LED to show a character transfer is occuring.
		//
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

		//
		// Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
		//
		SysCtlDelay(SysCtlClockGet() / (1000 * 3));

		//
		// Turn off the LED
		//
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);

	}
}

//*****************************************************************************
//
// UART≥ı ºªØ
//
//*****************************************************************************
void UARTInit(void) {
	//
	// Enable the GPIO port that is used for the on-board LED.
	//
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	//
	// Enable the GPIO pins for the LED (PF2).
	//
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

	//
	// Enable the peripherals used by this example.
	//
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	//
	// Enable processor interrupts.
	//
	ROM_IntMasterEnable();

	//
	// Set GPIO A0 and A1 as UART pins.
	//
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	//
	// Configure the UART for 115,200, 8-N-1 operation.
	//
	ROM_UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), 115200,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	//
	// Enable the UART interrupt.
	//
	ROM_IntEnable(INT_UART0);
	ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
}

/*uDMA-------------------------------------------------------*/

//*****************************************************************************
//
// UART interrupt handler. Called on completion of uDMA transfer
//
//*****************************************************************************
void UART1IntHandler(void) {
	uint32_t ui32Status;
	uint32_t ui32Mode;

	ui32Status = ROM_UARTIntStatus(UART1_BASE, 1);

	ROM_UARTIntClear(UART1_BASE, ui32Status);

	ui32Mode = ROM_uDMAChannelModeGet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT);

	if (ui32Mode == UDMA_MODE_STOP) {
		g_ui32RxPingCount++;

		ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
		UDMA_MODE_PINGPONG, (void *) (UART1_BASE + UART_O_DR), g_pui8RxPing,
				sizeof(g_pui8RxPing));
	}

	ui32Mode = ROM_uDMAChannelModeGet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT);

	if (ui32Mode == UDMA_MODE_STOP) {
		g_ui32RxPongCount++;

		ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
		UDMA_MODE_PINGPONG, (void *) (UART1_BASE + UART_O_DR), g_pui8RxPong,
				sizeof(g_pui8RxPong));
	}

	if (!ROM_uDMAChannelIsEnabled(UDMA_CHANNEL_UART1TX)) {

		ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1TX | UDMA_PRI_SELECT,
		UDMA_MODE_BASIC, g_pui8TxBuf, (void *) (UART1_BASE + UART_O_DR),
				sizeof(g_pui8TxBuf));

		ROM_uDMAChannelEnable(UDMA_CHANNEL_UART1TX);
	}
}

//*****************************************************************************
//
// Initialize UART uDMA transfer
//
//*****************************************************************************
void InitUART1Transfer(void) {
	uint32_t ui32Idx;

	// Initialize transmit buffer with some data
	for (ui32Idx = 0; ui32Idx < SPI_TXBUF_SIZE; ui32Idx++) {
		g_pui8TxBuf[ui32Idx] = ui32Idx;
	}

	// Enable UART1 and make sure it can run while the CPU sleeps
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	ROM_SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_UART1);

	// Configure and enable the UART with DMA
	ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), 115200,
	UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

	ROM_UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX4_8, UART_FIFO_RX4_8);

	ROM_UARTEnable(UART1_BASE);
	ROM_UARTDMAEnable(UART1_BASE, UART_DMA_RX | UART_DMA_TX);

	// Loopback mode
	HWREG(UART1_BASE + UART_O_CTL) |= UART_CTL_LBE;

	ROM_IntEnable(INT_UART1);

	// Receive channel setup for ping and pong
	ROM_uDMAChannelAttributeDisable(UDMA_CHANNEL_UART1RX,
			UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST | UDMA_ATTR_HIGH_PRIORITY
					| UDMA_ATTR_REQMASK);

	ROM_uDMAChannelControlSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
	UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 | UDMA_ARB_4);

	ROM_uDMAChannelControlSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
	UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 | UDMA_ARB_4);

	ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
	UDMA_MODE_PINGPONG, (void *) (UART1_BASE + UART_O_DR), g_pui8RxPing,
			sizeof(g_pui8RxPing));

	ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
	UDMA_MODE_PINGPONG, (void *) (UART1_BASE + UART_O_DR), g_pui8RxPong,
			sizeof(g_pui8RxPong));

	// Transmit channel setup for a basic transfer
	ROM_uDMAChannelAttributeDisable(UDMA_CHANNEL_UART1TX,
	UDMA_ATTR_ALTSELECT | UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK);

	ROM_uDMAChannelAttributeEnable(UDMA_CHANNEL_UART1TX, UDMA_ATTR_USEBURST);

	ROM_uDMAChannelControlSet(UDMA_CHANNEL_UART1TX | UDMA_PRI_SELECT,
	UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_NONE | UDMA_ARB_4);

	ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1TX | UDMA_PRI_SELECT,
	UDMA_MODE_BASIC, g_pui8TxBuf, (void *) (UART1_BASE + UART_O_DR),
			sizeof(g_pui8TxBuf));

	// Enable both channels
	ROM_uDMAChannelEnable(UDMA_CHANNEL_UART1RX);
	ROM_uDMAChannelEnable(UDMA_CHANNEL_UART1TX);
}
