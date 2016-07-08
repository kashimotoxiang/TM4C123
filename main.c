//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "main.h"
//*****************************************************************************
//
//Varible
//
//*****************************************************************************
ADC_HandleTypeDef hadc1={
		SYSCTL_PERIPH_ADC0,
		ADC0_BASE,
		SYSCTL_PERIPH_GPIOE,
		GPIO_PORTE_BASE,
        GPIO_PIN_0,
		3,
		ADC_CTL_CH3,
};
//SPI Buffer
uint8_t g_SPITxBuf[SPI_TXBUF_SIZE];
ADConvType g_ADConvBuf[SPI_RXBUF_SIZE];
//*****************************************************************************
//
// declartion
//
//*****************************************************************************
int main(void) {
	int i = 0;
	SystemInit();
	for (i = 0; i < SPI_TXBUF_SIZE; i++)
		g_SPITxBuf[i] = 'C';
	SPI0_uDMAInit();


	//
	// Loop forever echoing data through the UART.

	while (1) {

		//SSIDataPut(SSI0_BASE, 0XAA);//发送一次数据
		//
	}
}

