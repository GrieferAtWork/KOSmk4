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
#ifndef _I386_KOS_BITS_OS_GENERIC_IOVEC64_H
#define _I386_KOS_BITS_OS_GENERIC_IOVEC64_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __x86_64__
#define __iovecx64          iovec
#define __OFFSET_IOVEC_BASE __OFFSET_IOVECX64_BASE
#define __OFFSET_IOVEC_LEN  __OFFSET_IOVECX64_LEN
#define __SIZEOF_IOVEC      __SIZEOF_IOVECX64
#define __ALIGNOF_IOVEC     __ALIGNOF_IOVECX64
#endif /* __x86_64__ */

#define __OFFSET_IOVECX64_BASE 0
#define __OFFSET_IOVECX64_LEN  8
#define __SIZEOF_IOVECX64      16
#define __ALIGNOF_IOVECX64     __ALIGNOF_INT64__

#ifdef __CC__
#include <features.h>
#include <hybrid/__pointer.h>

#ifdef __USE_KOS_KERNEL
#define iovecx64 __iovecx64
#endif /* __USE_KOS_KERNEL */

__DECL_BEGIN

struct __iovecx64 /*[name(iovecx64)][prefix(iov_)]*/ {
	__HYBRID_PTR64(void) iov_base; /* Pointer to data. */
	__UINT64_TYPE__      iov_len;  /* Length of data. */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_GENERIC_IOVEC64_H */
