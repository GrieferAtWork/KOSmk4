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
#ifndef _I386_KOS_BITS_IOVEC_STRUCT64_H
#define _I386_KOS_BITS_IOVEC_STRUCT64_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#ifdef __x86_64__
#ifndef __iovec_defined
#define __iovec_defined 1
#define iovec64  iovec
#define __OFFSET_IOVEC_BASE __OFFSET_IOVEC64_BASE
#define __OFFSET_IOVEC_LEN  __OFFSET_IOVEC64_LEN
#define __SIZEOF_IOVEC      __SIZEOF_IOVEC64
#endif /* !__iovec_defined */
#endif /* __x86_64__ */

#define __OFFSET_IOVEC64_BASE 0
#define __OFFSET_IOVEC64_LEN  8
#define __SIZEOF_IOVEC64      16
#define __ALIGNOF_IOVEC64     __ALIGNOF_INT64__

#ifdef __CC__
#include <hybrid/__pointer.h>

__SYSDECL_BEGIN
struct iovec64 /*[prefix(iov_)]*/ {
	__HYBRID_PTR64(void) iov_base; /* Pointer to data. */
	__UINT64_TYPE__      iov_len;  /* Length of data. */
};
__SYSDECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_IOVEC_STRUCT64_H */
