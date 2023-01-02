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
#ifndef _I386_KOS_BITS_OS_KOS_SIGVAL64_H
#define _I386_KOS_BITS_OS_KOS_SIGVAL64_H 1

/* File:
 *    <i386-kos/bits/os/kos/sigval64.h>
 *
 * Definitions:
 *    - union __sigvalx64 { ... };
 * #ifdef __x86_64__
 *    - union sigval { ... };
 * #endif
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __x86_64__
#define __sigvalx64      sigval
#define __SIZEOF_SIGVAL  __SIZEOF_SIGVALX64
#define __ALIGNOF_SIGVAL __ALIGNOF_SIGVALX64
#endif /* __x86_64__ */

#define __SIZEOF_SIGVALX64  8
#define __ALIGNOF_SIGVALX64 __ALIGNOF_INT64__
#ifdef __CC__
__DECL_BEGIN

/* Type for data associated with a signal. */
union __sigvalx64 /*[NAME(sigvalx64)][PREFIX(sival_)]*/ {
	__INT64_TYPE__       sival_int;
	__HYBRID_PTR64(void) sival_ptr;
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_KOS_SIGVAL64_H */
