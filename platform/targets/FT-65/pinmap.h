/*
 * SPDX-FileCopyrightText: Copyright 2020-2026 OpenRTX Contributors
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef PINMAP_H
#define PINMAP_H

#include "gd32f30x.h"

/* Display */
#define LCD_CS  GPIOB,3
#define LCD_RST GPIOB,4
#define LCD_A0  GPIOB,5
#define LCD_SCL GPIOB,6
#define LCD_SI  GPIOB,7
#define LCD_BKLIGHT GPIOD,2

/* Signaling LEDs */
#define RED_LED     GPIOA,8
#define GREEN_LED   GPIOA,13
#define BLUE_LED    GPIOC,13
#define POWER_LED   GPIOC,6

/* Charging logic */
#define AIN_VBAT    GPIOA,5

/* Buttons */
#define PTT_SW  GPIOB,13
#define MONI_SW GPIOC,14
#define FUNC_SW GPIOA,12
#define SOS_SW  GPIOA,11

/* Audio logic */
#define PTT_DET     GPIOC,4   // external PTT detection, but more like a VOX than a real PTT, since PTT in these radios is a series switch
#define VOX_SEL     GPIOB,14  // demultiplexes mic_in between audio_proc and VOX (high: audio_proc, low: vox)
#define AIN_TONE    GPIOA,4   // driven by AFOUT (RDA), connected via analogue amps/filters (HPF). Labeled as 2T/5T/DTMF DET in schema
#define TONE_GEN    GPIOA,7   // driven by CPU, connected to RDA MIC_IN (via HPF). Alternative unpopulated connection to audio processor. Labeled as 2T/5T/DTMF. Also connected to audio output, which confirms it as DTMF
#define AUDIO_PWR   GPIOB,15  // connects to PA shutdown, so more of a MUTE than a POWER
#define AF_MUTE     GPIOB,11  // unpopulated DEMUX in receiver path

/* RF logic */
#define VCTCXO_CAL  GPIOA,6   // labeled as freq cont, connected via LPF to X200 which looks like a VCTCXO
#define V_U_SEL     GPIOC,8   // demultiplexes the 5TU/5TV supply voltages (low: UHF, high: VHF)
#define PA_ENA      GPIOC,7   // enables the 5T transmitter supply
#define V_RX_SEL    GPIOC,5   // enables the 5RV receiver supply
#define U_RX_SEL    GPIOC,15  // enables the 5RU receiver supply
#define TX_PWR      GPIOC,9   // connected to PABIAS of the RDA via LPF

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

/* SPI and stuff for CMX138AE1 audio processor */
#define AUDIO_IRQ   GPIOB,0
#define AUDIO_RDATA GPIOB,1
#define AUDIO_SCLK  GPIOB,2
#define AUDIO_CDATA GPIOB,10
#define AUDIO_CSN   GPIOB,11

/* RDA1846 */
#define RDA_SQ    GPIOA,15
#define RDA_VOX   GPIOA,14
#define RDA_SCLK  GPIOC,11
#define RDA_SDIO  GPIOC,10
#define RDA_SENB  GPIOC,12

/* I2C for AT24C128RM and RDA5802N */
#define I2C_SCL GPIOB,8
#define I2C_SDA GPIOB,9

#endif/* PINMAP_H */
