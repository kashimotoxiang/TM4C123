#include "myADC.h"
//*****************************************************************************
//
// ADC_Init
//
//*****************************************************************************
void ADC_Init(ADC_HandleTypeDef hadc) {

	// 使能 ADC0外设
	SysCtlPeripheralEnable(hadc.ui32ADCPeripheral);

	// 使能Port B外设端口
	SysCtlPeripheralEnable(hadc.ui32GPIOPeripheral);

	// 选择PB4作为模数装换ADC的管脚
	GPIOPinTypeADC(hadc.ui32Port, hadc.ui8Pins);

	// 配置采样序列的触发源和优先级
	ADCSequenceConfigure(hadc.ui32Base, hadc.ui32SequenceNum,
			ADC_TRIGGER_PROCESSOR, 0);

	// 配置采样序列发生器的步进
	ADCSequenceStepConfigure(hadc.ui32Base, hadc.ui32SequenceNum, 0,
			hadc.ui32Config | ADC_CTL_IE | ADC_CTL_END);

	// 使能一个采样序列
	ADCSequenceEnable(hadc.ui32Base, hadc.ui32SequenceNum);

	// 清除采样序列中断源
	ADCIntClear(hadc.ui32Base, hadc.ui32SequenceNum);
}
//*****************************************************************************
//
// ADC_GET
//
//*****************************************************************************
double ADC_GET(ADC_HandleTypeDef hadc) {
	uint32_t ADCValue[1];			// 保存ADC采样值
	ADCProcessorTrigger(hadc.ui32Base, hadc.ui32SequenceNum);
	while (!ADCIntStatus(hadc.ui32Base, hadc.ui32SequenceNum, false)) {
	}
	ADCIntClear(hadc.ui32Base, hadc.ui32SequenceNum);
	ADCSequenceDataGet(hadc.ui32Base, hadc.ui32SequenceNum,ADCValue);
	unsigned long sample = ADCValue[0];
	return (10100 * sample) / 4096;
}

