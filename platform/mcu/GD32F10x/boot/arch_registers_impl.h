/*
 * SPDX-FileCopyrightText: Copyright 2020-2026 OpenRTX Contributors
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#ifndef ARCH_REGISTERS_IMPL_H
#define	ARCH_REGISTERS_IMPL_H

//Always include gd32f10x.h before core_cm3.h, there's some nasty dependency
#include "gd32f10x.h"
#include "core_cm3.h"
#include "system_gd32f10x.h"

#define RCC_SYNC() __DSB()

#endif	//ARCH_REGISTERS_IMPL_H
