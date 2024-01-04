/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_OS_KOS_TMS64_H
#define _I386_KOS_BITS_OS_KOS_TMS64_H 1

/* File:
 *    <i386-kos/bits/os/kos/tms64.h>
 *
 * Definitions:
 *    - struct __tmsx64 { ... };
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __x86_64__
#define __tmsx64            tms
#define __OFFSET_TMS_UTIME  __OFFSET_TMSX64_UTIME
#define __OFFSET_TMS_STIME  __OFFSET_TMSX64_STIME
#define __OFFSET_TMS_CUTIME __OFFSET_TMSX64_CUTIME
#define __OFFSET_TMS_CSTIME __OFFSET_TMSX64_CSTIME
#define __SIZEOF_TMS        __SIZEOF_TMSX64
#define __ALIGNOF_TMS       __ALIGNOF_TMSX64
#endif /* __x86_64__ */

#define __OFFSET_TMSX64_UTIME  0
#define __OFFSET_TMSX64_STIME  8
#define __OFFSET_TMSX64_CUTIME 16
#define __OFFSET_TMSX64_CSTIME 24
#define __SIZEOF_TMSX64        32
#define __ALIGNOF_TMSX64       __ALIGNOF_INT64__

#ifdef __USE_KOS_KERNEL
#define tmsx64 __tmsx64
#endif /* __USE_KOS_KERNEL */

#ifdef __CC__
__DECL_BEGIN

struct __tmsx64 /*[NAME(tmsx64)][PREFIX(tms_)]*/ {
	__LONG64_TYPE__ tms_utime;  /* Userspace CPU time. */
	__LONG64_TYPE__ tms_stime;  /* Kernelspace CPU time. */
	__LONG64_TYPE__ tms_cutime; /* Userspace CPU time of dead children. */
	__LONG64_TYPE__ tms_cstime; /* Kernelspace CPU time of dead children. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_OS_KOS_TMS64_H */
