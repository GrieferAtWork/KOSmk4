/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_TYPES_H
#define GUARD_KERNEL_INCLUDE_KERNEL_TYPES_H 1

#include <kernel/compiler.h>

#include <hybrid/__altint.h>
#include <hybrid/typecore.h>

#include <bits/os/timespec.h>
#include <kos/kernel/types.h>

#define __SIZEOF_PORT_T__ 2

#ifdef __CC__
DECL_BEGIN

#ifndef __port_t_defined
#define __port_t_defined 1
__HYBRID_ALTINT_TYPEDEF(u16, port_t, false);
#endif /* !__port_t_defined */

#ifndef __IOPORT_T
#define __IOPORT_T     port_t
#endif /* !__IOPORT_T */

#ifndef __IOPORT
#define __IOPORT(x)  ((__IOPORT_T)x)
#endif /* !__IOPORT */

#ifndef __intptr_half_t_defined
#define __intptr_half_t_defined 1
#if __SIZEOF_POINTER__ == 4
typedef s16 intptr_half_t;
typedef u16 uintptr_half_t;
#elif __SIZEOF_POINTER__ == 8
typedef s32 intptr_half_t;
typedef u32 uintptr_half_t;
#elif __SIZEOF_POINTER__ == 2
typedef s8 intptr_half_t;
typedef u8 uintptr_half_t;
#elif __SIZEOF_POINTER__ == 16
typedef s64 intptr_half_t;
typedef u64 uintptr_half_t;
#else
#undef __intptr_half_t_defined
#endif
#endif /* !__intptr_half_t_defined */

#ifndef __intptr_quarter_t_defined
#define __intptr_quarter_t_defined 1
#if __SIZEOF_POINTER__ == 4
typedef s8 intptr_quarter_t;
typedef u8 uintptr_quarter_t;
#elif __SIZEOF_POINTER__ == 8
typedef s16 intptr_quarter_t;
typedef u16 uintptr_quarter_t;
#elif __SIZEOF_POINTER__ == 16
typedef s32 intptr_quarter_t;
typedef u32 uintptr_quarter_t;
#elif __SIZEOF_POINTER__ == 32
typedef s64 intptr_quarter_t;
typedef u64 uintptr_quarter_t;
#else
#undef __intptr_quarter_t_defined
#endif
#endif /* !__intptr_quarter_t_defined */

/* Time (in Nano seconds == 1/1000000000 (1/1_000_000_000) seconds)
 * since the system was booted (s.a. `boottime')
 * NOTE: 64 bits is enough to keep this counter from overflowing for
 *       almost 600 years (so don't worry too much about overflows) */
typedef u64 ktime_t;

/* Special values accepted by all interfaces that expose
 * a `ktime_t abs_timeout' or `ktime_t rel_timeout' */
#define KTIME_NONBLOCK ((ktime_t)0)  /* Don't block (but possibly yield) */
#define KTIME_INFINITE ((ktime_t)-1) /* Wait indefinitely (never time out) */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_TYPES_H */
