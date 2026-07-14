/*
 * SPDX-FileCopyrightText: Copyright 2020-2026 OpenRTX Contributors
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include <stdint.h>
#include "peripherals/gpio.h"
#include "interfaces/delays.h"
#include "interfaces/keyboard.h"
#include "interfaces/platform.h"
#include "hwconfig.h"

void kbd_init()
{
    gpio_setMode(KB_ROW1, OUTPUT);
    gpio_setMode(KB_ROW2, OUTPUT);
    gpio_setMode(KB_ROW3, OUTPUT);
    gpio_setMode(KB_ROW4, OUTPUT);
    gpio_clearPin(KB_ROW1);
    gpio_clearPin(KB_ROW2);
    gpio_clearPin(KB_ROW3);
    gpio_clearPin(KB_ROW4);
    gpio_setMode(KB_CLM1, INPUT);
    gpio_setMode(KB_CLM2, INPUT);
    gpio_setMode(KB_CLM3, INPUT);
    gpio_setMode(KB_CLMP, INPUT);
}

void kbd_terminate()
{
    gpio_clearPin(KB_ROW1);
    gpio_clearPin(KB_ROW2);
    gpio_clearPin(KB_ROW3);
    gpio_clearPin(KB_ROW4);
    gpio_setMode(KB_ROW1, INPUT);
    gpio_setMode(KB_ROW2, INPUT);
    gpio_setMode(KB_ROW3, INPUT);
    gpio_setMode(KB_ROW4, INPUT);
}

keyboard_t kbd_getKeys()
{
    // active low keyboard
    keyboard_t keys = 0;

    if (!gpio_readPin(MONI_SW)) keys |= KEY_MONI;
    if (!gpio_readPin(FUNC_SW)) keys |= KEY_F1;
    if (!gpio_readPin(KB_CLMP)) keys |= KEY_UP;
    if (!gpio_readPin(KB_CLM3)) keys |= KEY_DOWN;

    gpio_clearPin(KB_ROW1);

    delayUs(10);
    if (!gpio_readPin(KB_CLM1)) keys |= KEY_1;
    if (!gpio_readPin(KB_CLM2)) keys |= KEY_2;
    if (!gpio_readPin(KB_CLM3)) keys |= KEY_3;
    if (!gpio_readPin(KB_CLMP)) keys |= KEY_F2; // P1

    gpio_setPin(KB_ROW1);
    gpio_clearPin(KB_ROW2);

    delayUs(10);
    if (!gpio_readPin(KB_CLM1)) keys |= KEY_4;
    if (!gpio_readPin(KB_CLM2)) keys |= KEY_5;
    if (!gpio_readPin(KB_CLM3)) keys |= KEY_6;
    if (!gpio_readPin(KB_CLMP)) keys |= KEY_F3; // P2

    gpio_setPin(KB_ROW2);
    gpio_clearPin(KB_ROW3);

    delayUs(10);
    if (!gpio_readPin(KB_CLM1)) keys |= KEY_7;
    if (!gpio_readPin(KB_CLM2)) keys |= KEY_8;
    if (!gpio_readPin(KB_CLM3)) keys |= KEY_9;
    if (!gpio_readPin(KB_CLMP)) keys |= KEY_F4; // P3

    gpio_setPin(KB_ROW3);
    gpio_clearPin(KB_ROW4);

    delayUs(10);
    if (!gpio_readPin(KB_CLM1)) keys |= KEY_STAR;
    if (!gpio_readPin(KB_CLM2)) keys |= KEY_0;
    if (!gpio_readPin(KB_CLM3)) keys |= KEY_HASH;
    if (!gpio_readPin(KB_CLMP)) keys |= KEY_F5; // P4

    gpio_setPin(KB_ROW4);
    return keys;
}