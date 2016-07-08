#include "KeyInt.h"
//*****************************************************************************
//
// ����
//
//*****************************************************************************

/*SW1-------------------------------------------------------*/
KeyInt_HandleTypeDef KeySW1 = {
SYSCTL_PERIPH_GPIOF,
GPIO_PORTF_BASE,
INT_GPIOF,
GPIO_PIN_4,
GPIO_INT_PIN_4,
GPIO_FALLING_EDGE, 0, //USED
		1, //Name
		};
/*SW2-------------------------------------------------------*/
KeyInt_HandleTypeDef KeySW2 = {
SYSCTL_PERIPH_GPIOF,
GPIO_PORTF_BASE,
INT_GPIOF,
GPIO_PIN_0,
GPIO_INT_PIN_0,
GPIO_FALLING_EDGE, 0, //USED
		2, //Name
		};
//*****************************************************************************
//
// �жϰ�����ʼ��
//
//*****************************************************************************
void KeyInt_Init(KeyInt_HandleTypeDef hkey) {
	SysCtlPeripheralEnable(hkey.SYSCTL_PERIPH_GPIOx); //ʹ��GPIO����
	GPIOPinTypeGPIOInput(hkey.GPIO_PORTx_BASE, hkey.GPIO_PIN_x);
	GPIOPadConfigSet(hkey.GPIO_PORTx_BASE, hkey.GPIO_PIN_x,
	GPIO_STRENGTH_2MA,
	GPIO_PIN_TYPE_STD_WPU);
	//��������Ϊ2mA����������
	IntEnable(hkey.INT_GPIOx);
	GPIOIntTypeSet(hkey.GPIO_PORTx_BASE, hkey.GPIO_PIN_x,
			hkey.GPIO_x_EDGE);
	GPIOIntEnable(hkey.GPIO_PORTx_BASE, hkey.GPIO_PIN_x);
	IntEnable(hkey.INT_GPIOx);
	IntMasterEnable();
	GPIOIntClear(hkey.GPIO_PORTx_BASE, hkey.GPIO_PIN_x);
	hkey.USED = 1;
}

//*****************************************************************************
//
// �жϺ���
//
//*****************************************************************************
void GPIOF_IntHandler(void) {
	/*��������-------------------------------------------------------*/
	unsigned int ulStatus;
	int i = 0;
	KeyInt_HandleTypeDef *p;
	/*�жϱ�־��ȡ-------------------------------------------------------*/
	ulStatus = GPIOIntStatus(GPIO_PORTF_BASE, true);
	GPIOIntClear(GPIO_PORTF_BASE, ulStatus);
	/*�����ж�-------------------------------------------------------*/
	for (i = 0; i < KeyNum; i++) {
		switch (i) {
		case 1:
			p = &KeySW1;
			break;
		case 2:
			p = &KeySW2;
			break;
		default:
			break;
		}
		if (ulStatus & (p->GPIO_INT_PIN_x && p->USED)) {
			// ��ʱԼ10ms��������������
			delay_ms(10);
			// �ȴ�KEY̧��
			if (GPIOPinRead(p->GPIO_PORTx_BASE, p->GPIO_PIN_x) != 0x00)
				return;
			while (GPIOPinRead(p->GPIO_PORTx_BASE, p->GPIO_PIN_x) == 0x00) {
			}
			//TODO �߼�����
			return;
		}
	}

}

//*****************************************************************************
//
// �жϴ�����
//
//*****************************************************************************
void Interrupt_Deal(void) {

}
