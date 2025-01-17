/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_TMS_H
#define _BITS_OS_KOS_TMS_H 1

#include <__stdinc.h>

#include <bits/types.h>

#define __OFFSET_TMS_UTIME  0
#define __OFFSET_TMS_STIME  __SIZEOF_CLOCK_T__
#define __OFFSET_TMS_CUTIME (__SIZEOF_CLOCK_T__ * 2)
#define __OFFSET_TMS_CSTIME (__SIZEOF_CLOCK_T__ * 3)
#define __SIZEOF_TMS        (__SIZEOF_CLOCK_T__ * 4)
#define __ALIGNOF_TMS       __ALIGNOF_CLOCK_T__

#ifdef __CC__
__DECL_BEGIN

struct tms /*[PREFIX(tms_)]*/ {
	__clock_t tms_utime;  /* Userspace CPU time. */
	__clock_t tms_stime;  /* Kernelspace CPU time. */
	__clock_t tms_cutime; /* Userspace CPU time of dead children. */
	__clock_t tms_cstime; /* Kernelspace CPU time of dead children. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_TMS_H */
