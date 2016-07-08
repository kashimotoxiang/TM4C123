#include "myADC.h"
//*****************************************************************************
//
// ADC_Init
//
//*****************************************************************************
void ADC_Init(ADC_HandleTypeDef hadc) {

	// ʹ�� ADC0����
	SysCtlPeripheralEnable(hadc.ui32ADCPeripheral);

	// ʹ��Port B����˿�
	SysCtlPeripheralEnable(hadc.ui32GPIOPeripheral);

	// ѡ��PB4��Ϊģ��װ��ADC�Ĺܽ�
	GPIOPinTypeADC(hadc.ui32Port, hadc.ui8Pins);

	// ���ò������еĴ���Դ�����ȼ�
	ADCSequenceConfigure(hadc.ui32Base, hadc.ui32SequenceNum,
			ADC_TRIGGER_PROCESSOR, 0);

	// ���ò������з������Ĳ���
	ADCSequenceStepConfigure(hadc.ui32Base, hadc.ui32SequenceNum, 0,
			hadc.ui32Config | ADC_CTL_IE | ADC_CTL_END);

	// ʹ��һ����������
	ADCSequenceEnable(hadc.ui32Base, hadc.ui32SequenceNum);

	// ������������ж�Դ
	ADCIntClear(hadc.ui32Base, hadc.ui32SequenceNum);
}
//*****************************************************************************
//
// ADC_GET
//
//*****************************************************************************
double ADC_GET(ADC_HandleTypeDef hadc) {
	uint32_t ADCValue[1];			// ����ADC����ֵ
	ADCProcessorTrigger(hadc.ui32Base, hadc.ui32SequenceNum);
	while (!ADCIntStatus(hadc.ui32Base, hadc.ui32SequenceNum, false)) {
	}
	ADCIntClear(hadc.ui32Base, hadc.ui32SequenceNum);
	ADCSequenceDataGet(hadc.ui32Base, hadc.ui32SequenceNum,ADCValue);
	unsigned long sample = ADCValue[0];
	return (10100 * sample) / 4096;
}

