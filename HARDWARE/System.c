#include "System.h"
//*****************************************************************************
//
//  Static Varible
//
//*****************************************************************************
// Error counter
static uint32_t g_ui32DMAErrCount = 0;
//*****************************************************************************
//
// System Varible
//
//*****************************************************************************
uint8_t pui8ControlTable[1024];
//*****************************************************************************
//
//系统初始化
//
//*****************************************************************************
void SystemInit(void) {
	ROM_FPULazyStackingEnable();

	ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
	SYSCTL_XTAL_16MHZ);

	ROM_SysCtlPeripheralClockGating(true);

	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	ROM_SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_UDMA);

	ROM_IntEnable(INT_UDMAERR);
	ROM_uDMAEnable();

	ROM_uDMAControlBaseSet(pui8ControlTable);
	//
	// PinoutSet
	//
	PinoutSet();
}

//*****************************************************************************
//
// uDMA error handler
//
//*****************************************************************************
void uDMAErrorHandler(void) {
	uint32_t ui32Status;

	ui32Status = ROM_uDMAErrorStatusGet();

	if (ui32Status) {
		ROM_uDMAErrorStatusClear();
		g_ui32DMAErrCount++;
	}
}
//*****************************************************************************
//
// delay_ms
//
//*****************************************************************************
void delay_ms(int num) {
	unsigned long clk = (SysCtlClockGet() / 1000) / 6;
	clk *= num;
	SysCtlDelay(clk);
}
//*****************************************************************************
//
// delay_us
//
//*****************************************************************************
void delay_us(int num) {
	unsigned long clk = (SysCtlClockGet() / 1000000) / 6;
	clk *= num;
	SysCtlDelay(clk);
}
//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif
