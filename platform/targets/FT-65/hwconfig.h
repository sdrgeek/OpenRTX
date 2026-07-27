/*
 * SPDX-FileCopyrightText: Copyright 2020-2026 OpenRTX Contributors
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef HWCONFIG_H
#define HWCONFIG_H

#include "gd32f30x.h"
#include "pinmap.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Device has a working real time clock */
#define CONFIG_RTC

/* Screen dimensions */
#define CONFIG_SCREEN_WIDTH 160     // dummy value to make compiler happy
#define CONFIG_SCREEN_HEIGHT 128    // dummy value to make compiler happy

/* Screen pixel format */
#define CONFIG_PIX_FMT_BW

/* Battery type */
#define CONFIG_BAT_LIION
#define CONFIG_BAT_NCELLS 2

#ifdef __cplusplus
}
#endif

#endif 