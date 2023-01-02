/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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

#ifdef __CC__
DECL_BEGIN

#ifdef __port_t
#ifndef __port_t_defined
#define __port_t_defined
__HYBRID_ALTINT_TYPEDEF(__port_t, port_t, false);
#endif /* !__port_t_defined */
#undef __port_t
#define __port_t port_t
#ifndef __IOPORT
#define __IOPORT(x) ((__port_t)x)
#endif /* !__IOPORT */
#endif /* __port_t */

/* Time (in Nano seconds == 1/1000000000 (1/1_000_000_000) seconds)
 * since the system was booted (s.a. `boottime')
 * NOTE: 64 bits is enough to keep this counter from overflowing for
 *       almost 600 years (so don't worry too much about  overflows) */
typedef u64 ktime_t;

/* Special values accepted by all interfaces that expose
 * a   `ktime_t abs_timeout'   or  `ktime_t rel_timeout' */
#define KTIME_NONBLOCK ((ktime_t)0)  /* Don't block (but possibly yield) */
#define KTIME_INFINITE ((ktime_t)-1) /* Wait indefinitely (never time out) */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_TYPES_H */
