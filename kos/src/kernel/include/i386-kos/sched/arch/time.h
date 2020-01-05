/* Copyright (c) 2019-2020 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TIME_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TIME_H 1

#include <kernel/compiler.h>

#ifdef __CC__
DECL_BEGIN

struct realtime_clock_struct;
DATDEF struct realtime_clock_struct x86_cmos_realtime_clock;
#define ARCH_DEFAULT_REALTIME_CLOCK (&x86_cmos_realtime_clock)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TIME_H */
