/*
 * SPDX-FileCopyrightText: Copyright 2020-2026 OpenRTX Contributors
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#ifndef ARCH_REGISTERS_IMPL_H
#define	ARCH_REGISTERS_IMPL_H

//Always include gd32f30x.h before core_cm4.h, there's some nasty dependency
#include "gd32f30x.h"
#include "core_cm4.h"
#include "system_gd32f30x.h"

#define RCC_SYNC() __DSB()

#endif	//ARCH_REGISTERS_IMPL_H
