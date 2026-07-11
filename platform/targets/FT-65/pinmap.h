/*
 * SPDX-FileCopyrightText: Copyright 2020-2026 OpenRTX Contributors
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef PINMAP_H
#define PINMAP_H

#include "gd32f10x.h"

/* Display */
#define LCD_CS  GPIOB,3
#define LCD_RST GPIOB,4
#define LCD_A0  GPIOB,5
#define LCD_SCL GPIOB,6
#define LCD_SI  GPIOB,7
#define LCD_BKLIGHT GPIOD,2

/* Signalling LEDs */
#define RED_LED     GPIOA,8
#define GREEN_LED   GPIOA,13
#define BLUE_LED    GPIOC,13

/* Analog inputs */
#define AIN_VBAT    GPIOA,5

/* Buttons */
#define PTT_SW  GPIOB,13
#define MONI_SW GPIOC,14
#define FUNC_SW GPIOA,12
#define SOS_SW  GPIOA,11

/* Keyboard */
#define KB_CLM1 GPIOC,3
#define KB_CLM2 GPIOC,2
#define KB_CLM3 GPIOC,1     /* includes DOWN */
#define KB_CLMP GPIOC,0     /* P-keys & UP */
#define KB_ROW1 GPIOA,0
#define KB_ROW2 GPIOA,1
#define KB_ROW3 GPIOA,2
#define KB_ROW4 GPIOA,3
#define KB_BKLIGHT  GPIOB,12

/* UART */
#define UART_RX GPIOA,10
#define UART_TX GPIOA,9

/* I2C for AT24C128RM */
#define I2C_SCL GPIOB,8
#define I2C_SDA GPIOB,9

#endif/* PINMAP_H */