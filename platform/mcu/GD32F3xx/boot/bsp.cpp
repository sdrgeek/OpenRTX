/*
 * SPDX-FileCopyrightText: Copyright 2020-2026 OpenRTX Contributors
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

/***********************************************************************
* bsp.cpp Part of the Miosix Embedded OS.
* Board support package, this file initializes hardware.
************************************************************************/

#include "interfaces/bsp.h"
#include <kernel/kernel.h>
#include <kernel/sync.h>
#include "hwconfig.h"


namespace miosix
{

void IRQbspInit()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN
                 |  RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIODEN
                 |  RCC_AHBENR_GPIOEEN;
    RCC_SYNC();

    GPIOA->OSPEEDR=0xaaaaaaaa; //Default to 50MHz speed for all GPIOS
    GPIOB->OSPEEDR=0xaaaaaaaa;
    GPIOC->OSPEEDR=0xaaaaaaaa;
    GPIOD->OSPEEDR=0xaaaaaaaa;
    GPIOE->OSPEEDR=0xaaaaaaaa;

    /*
     * Enable SWD interface on PA13 and PA14 (Yaesu's bootloader disables this
     * functionality).
     * NOTE: PA13/14 are used also for other functions (green LED, VOX det),
     * thus they cannot be always used for debugging!
     */
    #ifdef FT65_ENABLE_SWD
    GPIOA->MODER  &= ~0x3C000000;   // Clear current setting
    GPIOA->MODER  |= 0x28000000;    // Put back to alternate function
    GPIOA->AFR[1] &= ~0x0FF00000;   // SWD is AF0
    #endif

    // Configure SysTick
    SysTick->LOAD = SystemCoreClock / miosix::TICK_FREQ;
}

void bspInit2()
{

}

//
// Shutdown and reboot
//

void shutdown()
{
    reboot();
}

void reboot()
{
    disableInterrupts();
    miosix_private::IRQsystemReboot();
}

} //namespace miosix
