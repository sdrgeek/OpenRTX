/*
 * SPDX-FileCopyrightText: Copyright 2020-2026 OpenRTX Contributors
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

/*
 * startup.cpp
 * STM32 C++ startup.
 * NOTE: for stm32f303xC devices ONLY.
 * Supports interrupt handlers in C++ without extern "C"
 * Developed by Terraneo Federico, based on ST startup code.
 * Additionally modified to boot Miosix.
 */

#include "interfaces/arch_registers.h"
#include "kernel/stage_2_boot.h"
#include "core/interrupts.h" //For the unexpected interrupt call
#include <string.h>

/**
 * Called by Reset_Handler, performs initialization and calls main.
 * Never returns.
 */
void program_startup() __attribute__((noreturn));
void program_startup()
{
    //Cortex M3 core appears to get out of reset with interrupts already enabled
    __disable_irq();

    //SystemInit() is called *before* initializing .data and zeroing .bss
    //Despite all startup files provided by ST do the opposite, there are three
    //good reasons to do so:
    //First, the CMSIS specifications say that SystemInit() must not access
    //global variables, so it is actually possible to call it before
    //Second, when running Miosix with the xram linker scripts .data and .bss
    //are placed in the external RAM, so we *must* call SystemInit(), which
    //enables xram, before touching .data and .bss
    //Third, this is a performance improvement since the loops that initialize
    //.data and zeros .bss now run with the CPU at full speed instead of 8MHz
    SystemInit();

    //These are defined in the linker script
    extern unsigned char _etext asm("_etext");
    extern unsigned char _data asm("_data");
    extern unsigned char _edata asm("_edata");
    extern unsigned char _bss_start asm("_bss_start");
    extern unsigned char _bss_end asm("_bss_end");

    //Initialize .data section, clear .bss section
    unsigned char *etext=&_etext;
    unsigned char *data=&_data;
    unsigned char *edata=&_edata;
    unsigned char *bss_start=&_bss_start;
    unsigned char *bss_end=&_bss_end;
    memcpy(data, etext, edata-data);
    memset(bss_start, 0, bss_end-bss_start);

    //Move on to stage 2
    _init();

    //If main returns, reboot
    NVIC_SystemReset();
    for(;;) ;
}

/**
 * Reset handler, called by hardware immediately after reset
 */
void Reset_Handler() __attribute__((__interrupt__, noreturn));
void Reset_Handler()
{
    /*
     * Initialize process stack and switch to it.
     * This is required for booting Miosix, a small portion of the top of the
     * heap area will be used as stack until the first thread starts. After,
     * this stack will be abandoned and the process stack will point to the
     * current thread's stack.
     */
    asm volatile("ldr r0,  =_heap_end          \n\t"
                 "msr psp, r0                  \n\t"
                 "movw r0, #2                  \n\n" //Privileged, process stack
                 "msr control, r0              \n\t"
                 "isb                          \n\t":::"r0");

    program_startup();
}

/**
 * All unused interrupts call this function.
 */
extern "C" void Default_Handler()
{
    unexpectedInterrupt();
}

//System handlers
void /*__attribute__((weak))*/ Reset_Handler();     //These interrupts are not
void /*__attribute__((weak))*/ NMI_Handler();       //weak because they are
void /*__attribute__((weak))*/ HardFault_Handler(); //surely defined by Miosix
void /*__attribute__((weak))*/ MemManage_Handler();
void /*__attribute__((weak))*/ BusFault_Handler();
void /*__attribute__((weak))*/ UsageFault_Handler();
void /*__attribute__((weak))*/ SVC_Handler();
void /*__attribute__((weak))*/ DebugMon_Handler();
void /*__attribute__((weak))*/ PendSV_Handler();
void /*__attribute__((weak))*/ SysTick_Handler();

//Interrupt handlers
void __attribute__((weak)) WWDGT_IRQHandler();
void __attribute__((weak)) LVD_IRQHandler();
void __attribute__((weak)) TAMPER_IRQHandler();
void __attribute__((weak)) RTC_IRQHandler();
void __attribute__((weak)) FMC_IRQHandler();
void __attribute__((weak)) RCU_CTC_IRQHandler();
void __attribute__((weak)) EXTI0_IRQHandler();
void __attribute__((weak)) EXTI1_IRQHandler();
void __attribute__((weak)) EXTI2_IRQHandler();
void __attribute__((weak)) EXTI3_IRQHandler();
void __attribute__((weak)) EXTI4_IRQHandler();
void __attribute__((weak)) DMA0_Channel0_IRQHandler();
void __attribute__((weak)) DMA0_Channel1_IRQHandler();
void __attribute__((weak)) DMA0_Channel2_IRQHandler();
void __attribute__((weak)) DMA0_Channel3_IRQHandler();
void __attribute__((weak)) DMA0_Channel4_IRQHandler();
void __attribute__((weak)) DMA0_Channel5_IRQHandler();
void __attribute__((weak)) DMA0_Channel6_IRQHandler();
void __attribute__((weak)) ADC0_1_IRQHandler();
void __attribute__((weak)) CAN0_TX_IRQHandler();
void __attribute__((weak)) CAN0_RX0_IRQHandler();
void __attribute__((weak)) CAN0_RX1_IRQHandler();
void __attribute__((weak)) CAN0_EWMC_IRQHandler();
void __attribute__((weak)) EXTI5_9_IRQHandler();
void __attribute__((weak)) TIMER0_BRK_TIMER8_IRQHandler();
void __attribute__((weak)) TIMER0_UP_TIMER9_IRQHandler();
void __attribute__((weak)) TIMER0_TRG_CMT_TIMER10_IRQHandler();
void __attribute__((weak)) TIMER0_Channel_IRQHandler();
void __attribute__((weak)) TIMER1_IRQHandler();
void __attribute__((weak)) TIMER2_IRQHandler();
void __attribute__((weak)) TIMER3_IRQHandler();
void __attribute__((weak)) I2C0_EV_IRQHandler();
void __attribute__((weak)) I2C0_ER_IRQHandler();
void __attribute__((weak)) I2C1_EV_IRQHandler();
void __attribute__((weak)) I2C1_ER_IRQHandler();
void __attribute__((weak)) SPI0_IRQHandler();
void __attribute__((weak)) SPI1_IRQHandler();
void __attribute__((weak)) USART0_IRQHandler();
void __attribute__((weak)) USART1_IRQHandler();
void __attribute__((weak)) USART2_IRQHandler();
void __attribute__((weak)) EXTI10_15_IRQHandler();
void __attribute__((weak)) RTC_Alarm_IRQHandler();
void __attribute__((weak)) USBFS_WKUP_IRQHandler();
void __attribute__((weak)) TIMER7_BRK_TIMER11_IRQHandler();
void __attribute__((weak)) TIMER7_UP_TIMER12_IRQHandler();
void __attribute__((weak)) TIMER7_TRG_CMT_TIMER13_IRQHandler();
void __attribute__((weak)) TIMER7_Channel_IRQHandler();
void __attribute__((weak)) EXMC_IRQHandler();
void __attribute__((weak)) TIMER4_IRQHandler();
void __attribute__((weak)) SPI2_IRQHandler();
void __attribute__((weak)) UART3_IRQHandler();
void __attribute__((weak)) UART4_IRQHandler();
void __attribute__((weak)) TIMER5_IRQHandler();
void __attribute__((weak)) TIMER6_IRQHandler();
void __attribute__((weak)) DMA1_Channel0_IRQHandler();
void __attribute__((weak)) DMA1_Channel1_IRQHandler();
void __attribute__((weak)) DMA1_Channel2_IRQHandler();
void __attribute__((weak)) DMA1_Channel3_IRQHandler();
void __attribute__((weak)) DMA1_Channel4_IRQHandler();
void __attribute__((weak)) ENET_IRQHandler();
void __attribute__((weak)) ENET_WKUP_IRQHandler();
void __attribute__((weak)) CAN1_TX_IRQHandler();
void __attribute__((weak)) CAN1_RX0_IRQHandler();
void __attribute__((weak)) CAN1_RX1_IRQHandler();
void __attribute__((weak)) CAN1_EWMC_IRQHandler();
void __attribute__((weak)) USBFS_IRQHandler();

//Stack top, defined in the linker script
extern char _main_stack_top asm("_main_stack_top");

//Interrupt vectors, must be placed @ address 0x00000000
//The extern declaration is required otherwise g++ optimizes it out
extern void (* const __Vectors[])();
void (* const __Vectors[])() __attribute__ ((section(".isr_vector"))) =
{
    reinterpret_cast<void (*)()>(&_main_stack_top),/* Stack pointer*/
    Reset_Handler,              /* Reset Handler */
    NMI_Handler,                /* NMI Handler */
    HardFault_Handler,          /* Hard Fault Handler */
    MemManage_Handler,          /* MPU Fault Handler */
    BusFault_Handler,           /* Bus Fault Handler */
    UsageFault_Handler,         /* Usage Fault Handler */
    0,                          /* Reserved */
    0,                          /* Reserved */
    0,                          /* Reserved */
    0,                          /* Reserved */
    SVC_Handler,                /* SVCall Handler */
    DebugMon_Handler,           /* Debug Monitor Handler */
    0,                          /* Reserved */
    PendSV_Handler,             /* PendSV Handler */
    SysTick_Handler,            /* SysTick Handler */

    /* External Interrupts */
    WWDGT_IRQHandler,
    LVD_IRQHandler,
    TAMPER_IRQHandler,
    RTC_IRQHandler,
    FMC_IRQHandler,
    RCU_CTC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA0_Channel0_IRQHandler,
    DMA0_Channel1_IRQHandler,
    DMA0_Channel2_IRQHandler,
    DMA0_Channel3_IRQHandler,
    DMA0_Channel4_IRQHandler,
    DMA0_Channel5_IRQHandler,
    DMA0_Channel6_IRQHandler,
    ADC0_1_IRQHandler,
    CAN0_TX_IRQHandler,
    CAN0_RX0_IRQHandler,
    CAN0_RX1_IRQHandler,
    CAN0_EWMC_IRQHandler,
    EXTI5_9_IRQHandler,
    TIMER0_BRK_TIMER8_IRQHandler,
    TIMER0_UP_TIMER9_IRQHandler,
    TIMER0_TRG_CMT_TIMER10_IRQHandler,
    TIMER0_Channel_IRQHandler,
    TIMER1_IRQHandler,
    TIMER2_IRQHandler,
    TIMER3_IRQHandler,
    I2C0_EV_IRQHandler,
    I2C0_ER_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    SPI0_IRQHandler,
    SPI1_IRQHandler,
    USART0_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    EXTI10_15_IRQHandler,
    RTC_Alarm_IRQHandler,
    USBFS_WKUP_IRQHandler,
    TIMER7_BRK_TIMER11_IRQHandler,
    TIMER7_UP_TIMER12_IRQHandler,
    TIMER7_TRG_CMT_TIMER13_IRQHandler,
    TIMER7_Channel_IRQHandler,
    0,
    EXMC_IRQHandler,
    0,
    TIMER4_IRQHandler,
    SPI2_IRQHandler,
    UART3_IRQHandler,
    UART4_IRQHandler,
    TIMER5_IRQHandler,
    TIMER6_IRQHandler,
    DMA1_Channel0_IRQHandler,
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_IRQHandler,
    DMA1_Channel3_IRQHandler,
    DMA1_Channel4_IRQHandler,
    ENET_IRQHandler,
    ENET_WKUP_IRQHandler,
    CAN1_TX_IRQHandler,
    CAN1_RX0_IRQHandler,
    CAN1_RX1_IRQHandler,
    CAN1_EWMC_IRQHandler,
    USBFS_IRQHandler
};

#pragma weak WWDGT_IRQHandler = Default_Handler
#pragma weak LVD_IRQHandler = Default_Handler
#pragma weak TAMPER_IRQHandler = Default_Handler
#pragma weak RTC_IRQHandler = Default_Handler
#pragma weak FMC_IRQHandler = Default_Handler
#pragma weak RCU_CTC_IRQHandler = Default_Handler
#pragma weak EXTI0_IRQHandler = Default_Handler
#pragma weak EXTI1_IRQHandler = Default_Handler
#pragma weak EXTI2_IRQHandler = Default_Handler
#pragma weak EXTI3_IRQHandler = Default_Handler
#pragma weak EXTI4_IRQHandler = Default_Handler
#pragma weak DMA0_Channel0_IRQHandler = Default_Handler
#pragma weak DMA0_Channel1_IRQHandler = Default_Handler
#pragma weak DMA0_Channel2_IRQHandler = Default_Handler
#pragma weak DMA0_Channel3_IRQHandler = Default_Handler
#pragma weak DMA0_Channel4_IRQHandler = Default_Handler
#pragma weak DMA0_Channel5_IRQHandler = Default_Handler
#pragma weak DMA0_Channel6_IRQHandler = Default_Handler
#pragma weak ADC0_1_IRQHandler = Default_Handler
#pragma weak CAN0_TX_IRQHandler = Default_Handler
#pragma weak CAN0_RX0_IRQHandler = Default_Handler
#pragma weak CAN0_RX1_IRQHandler = Default_Handler
#pragma weak CAN0_EWMC_IRQHandler = Default_Handler
#pragma weak EXTI5_9_IRQHandler = Default_Handler
#pragma weak TIMER0_BRK_TIMER8_IRQHandler = Default_Handler
#pragma weak TIMER0_UP_TIMER9_IRQHandler = Default_Handler
#pragma weak TIMER0_TRG_CMT_TIMER10_IRQHandler = Default_Handler
#pragma weak TIMER0_Channel_IRQHandler = Default_Handler
#pragma weak TIMER1_IRQHandler = Default_Handler
#pragma weak TIMER2_IRQHandler = Default_Handler
#pragma weak TIMER3_IRQHandler = Default_Handler
#pragma weak I2C0_EV_IRQHandler = Default_Handler
#pragma weak I2C0_ER_IRQHandler = Default_Handler
#pragma weak I2C1_EV_IRQHandler = Default_Handler
#pragma weak I2C1_ER_IRQHandler = Default_Handler
#pragma weak SPI0_IRQHandler = Default_Handler
#pragma weak SPI1_IRQHandler = Default_Handler
#pragma weak USART0_IRQHandler = Default_Handler
#pragma weak USART1_IRQHandler = Default_Handler
#pragma weak USART2_IRQHandler = Default_Handler
#pragma weak EXTI10_15_IRQHandler = Default_Handler
#pragma weak RTC_Alarm_IRQHandler = Default_Handler
#pragma weak USBFS_WKUP_IRQHandler = Default_Handler
#pragma weak TIMER7_BRK_TIMER11_IRQHandler = Default_Handler
#pragma weak TIMER7_UP_TIMER12_IRQHandler = Default_Handler
#pragma weak TIMER7_TRG_CMT_TIMER13_IRQHandler = Default_Handler
#pragma weak TIMER7_Channel_IRQHandler = Default_Handler
#pragma weak EXMC_IRQHandler = Default_Handler
#pragma weak TIMER4_IRQHandler = Default_Handler
#pragma weak SPI2_IRQHandler = Default_Handler
#pragma weak UART3_IRQHandler = Default_Handler
#pragma weak UART4_IRQHandler = Default_Handler
#pragma weak TIMER5_IRQHandler = Default_Handler
#pragma weak TIMER6_IRQHandler = Default_Handler
#pragma weak DMA1_Channel0_IRQHandler = Default_Handler
#pragma weak DMA1_Channel1_IRQHandler = Default_Handler
#pragma weak DMA1_Channel2_IRQHandler = Default_Handler
#pragma weak DMA1_Channel3_IRQHandler = Default_Handler
#pragma weak DMA1_Channel4_IRQHandler = Default_Handler
#pragma weak ENET_IRQHandler = Default_Handler
#pragma weak ENET_WKUP_IRQHandler = Default_Handler
#pragma weak CAN1_TX_IRQHandler = Default_Handler
#pragma weak CAN1_RX0_IRQHandler = Default_Handler
#pragma weak CAN1_RX1_IRQHandler = Default_Handler
#pragma weak CAN1_EWMC_IRQHandler = Default_Handler
#pragma weak USBFS_IRQHandler = Default_Handler