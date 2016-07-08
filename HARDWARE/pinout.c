//*****************************************************************************
//
// Configure the device pins for different signals
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

// This file was automatically generated on 2016/7/8 at ÏÂÎç9:46:40
// by TI PinMux version 
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "pinout.h"

//*****************************************************************************
//
//! \addtogroup pinout_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! Configures the device pins for the customer specific usage.
//!
//! \return None.
//
//*****************************************************************************
void
PinoutSet(void)
{
    //
    // Enable Peripheral Clocks 
    //
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Configure the GPIO Pin Mux for PB6
	// for GPIO_PB6
    //
	MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_6);

    //
    // Configure the GPIO Pin Mux for PB7
	// for GPIO_PB7
    //
	MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_7);

    //
    // Configure the GPIO Pin Mux for PB0
	// for GPIO_PB0
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0);

    //
    // Configure the GPIO Pin Mux for PB1
	// for GPIO_PB1
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_1);

    //
    // Configure the GPIO Pin Mux for PB2
	// for GPIO_PB2
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2);

    //
    // Configure the GPIO Pin Mux for PB3
	// for GPIO_PB3
    //
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3);

    //
    // Configure the GPIO Pin Mux for PB4
	// for GPIO_PB4
    //
	MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_4);

    //
    // Configure the GPIO Pin Mux for PB5
	// for GPIO_PB5
    //
	MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_5);

    //
    // Configure the GPIO Pin Mux for PF4
	// for GPIO_PF4
    //
	MAP_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);

	//
	// Unlock the Port Pin and Set the Commit Bit
	//
	HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE+GPIO_O_CR)   |= GPIO_PIN_0;
	HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = 0x0;

    //
    // Configure the GPIO Pin Mux for PF0
	// for GPIO_PF0
    //
	MAP_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);

    //
    // Configure the GPIO Pin Mux for PD2
	// for SSI3RX
    //
	MAP_GPIOPinConfigure(GPIO_PD2_SSI3RX);
	MAP_GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_2);

    //
    // Configure the GPIO Pin Mux for PD1
	// for SSI3FSS
    //
	MAP_GPIOPinConfigure(GPIO_PD1_SSI3FSS);
	MAP_GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_1);

    //
    // Configure the GPIO Pin Mux for PD3
	// for SSI3TX
    //
	MAP_GPIOPinConfigure(GPIO_PD3_SSI3TX);
	MAP_GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_3);

    //
    // Configure the GPIO Pin Mux for PD0
	// for SSI3CLK
    //
	MAP_GPIOPinConfigure(GPIO_PD0_SSI3CLK);
	MAP_GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0);

    //
    // Configure the GPIO Pin Mux for PA4
	// for SSI0RX
    //
	MAP_GPIOPinConfigure(GPIO_PA4_SSI0RX);
	MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_4);

    //
    // Configure the GPIO Pin Mux for PA3
	// for SSI0FSS
    //
	MAP_GPIOPinConfigure(GPIO_PA3_SSI0FSS);
	MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_3);

    //
    // Configure the GPIO Pin Mux for PA5
	// for SSI0TX
    //
	MAP_GPIOPinConfigure(GPIO_PA5_SSI0TX);
	MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5);

    //
    // Configure the GPIO Pin Mux for PA2
	// for SSI0CLK
    //
	MAP_GPIOPinConfigure(GPIO_PA2_SSI0CLK);
	MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2);

}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

