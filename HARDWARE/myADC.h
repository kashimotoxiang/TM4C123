#pragma once

//*****************************************************************************
//
// include
//
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//
// struct
//
//*****************************************************************************
typedef struct ADC_HandleTypeDef {
	uint32_t ui32ADCPeripheral;
	uint32_t ui32Base;
	uint32_t ui32GPIOPeripheral;
	uint32_t ui32Port;
	uint8_t ui8Pins;
	uint32_t ui32SequenceNum;
	uint32_t ui32Config;
} ADC_HandleTypeDef;

//*****************************************************************************
//
// declartion
//
//*****************************************************************************
void ADC_Init(ADC_HandleTypeDef hadc);
double ADC_GET(ADC_HandleTypeDef hadc);
