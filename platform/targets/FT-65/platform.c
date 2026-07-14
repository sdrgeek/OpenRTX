/*
 * SPDX-FileCopyrightText: Copyright 2020-2026 OpenRTX Contributors
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "hwconfig.h"
#include "interfaces/platform.h"
#include "interfaces/delays.h"
#include "interfaces/audio.h"
#include "interfaces/nvmem.h"
#include "peripherals/gpio.h"
#include "peripherals/rtc.h"

static hwInfo_t hwInfo;

void platform_init()
{
    gpio_setMode(RED_LED, OUTPUT);
    gpio_setMode(GREEN_LED, OUTPUT);
    gpio_setMode(BLUE_LED, OUTPUT);

    gpio_setMode(PTT_SW, INPUT);
    gpio_setMode(PTT_DET, INPUT);
}

void platform_terminate()
{
    gpio_clearPin(RED_LED);
    gpio_clearPin(GREEN_LED);
    gpio_clearPin(BLUE_LED);
}

uint16_t platform_getVbat()
{
    return 1;   // TODO
}

uint8_t platform_getMicLevel()
{
    return 1;   // TODO
}

uint8_t platform_getVolumeLevel()
{
    return 1;   // I don't think there's a path from the potentiometer to 
}

bool platform_getPttStatus()
{
    uint8_t intPttStatus = gpio_readPin(PTT_SW);    // Active low
    uint8_t extPttStatus = gpio_readPin(PTT_DET);   // Active high
    return ((intPttStatus == 0) || (extPttStatus == 1)) ? true : false;
}

bool platform_pwrButtonStatus()
{
    return true;
}

void platform_ledOn(led_t led)
{
    switch (led)
        {
        case RED:
            gpio_setPin(RED_LED);
            break;

        case GREEN:
            gpio_setPin(GREEN_LED);
            break;

        case YELLOW:    // there is no blue lol
            gpio_setPin(BLUE_LED);
            break;

        default:
            break;
        }
}

void platform_ledOff(led_t led)
{
    switch (led)
        {
        case RED:
            gpio_clearPin(RED_LED);
            break;

        case GREEN:
            gpio_clearPin(GREEN_LED);
            break;

        case YELLOW:    // there is no blue lol
            gpio_clearPin(BLUE_LED);
            break;

        default:
            break;
        }
}

void platform_beepStart(uint16_t freq)
{
    // TODO
}

void platform_beepStop()
{
    // TODO
}

datetime_t platform_getCurrentTime()
{
    return rtc_getTime();
}

void platform_setTime(datetime_t t)
{
    rtc_setTime(t);
}

const hwInfo_t *platform_getHwInfo()
{
    return &hwInfo;
}