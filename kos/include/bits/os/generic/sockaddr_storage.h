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
#ifndef _BITS_OS_GENERIC_SOCKADDR_STORAGE_H
#define _BITS_OS_GENERIC_SOCKADDR_STORAGE_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/os/sockaddr-common.h>

#ifndef __SIZEOF_SOCKADDR_STORAGE
#define __SIZEOF_SOCKADDR_STORAGE 128
#endif /* !__SIZEOF_SOCKADDR_STORAGE */

#ifndef __ALIGNOF_SOCKADDR_STORAGE
#define __ALIGNOF_SOCKADDR_STORAGE __SIZEOF_POINTER__
#endif /* !__ALIGNOF_SOCKADDR_STORAGE */

#undef __ss_aligntype
#if __ALIGNOF_SOCKADDR_STORAGE == 1 && __ALIGNOF_INT8__ == 1
#define __ss_aligntype __UINT8_TYPE__
#elif __ALIGNOF_SOCKADDR_STORAGE == 2 && __ALIGNOF_INT16__ == 2
#define __ss_aligntype __UINT16_TYPE__
#elif __ALIGNOF_SOCKADDR_STORAGE == 4 && __ALIGNOF_INT32__ == 4
#define __ss_aligntype __UINT32_TYPE__
#elif __ALIGNOF_SOCKADDR_STORAGE == 8 && __ALIGNOF_INT64__ == 8
#define __ss_aligntype __UINT64_TYPE__
#endif /* ... */

#undef _SS_SIZE
#undef _SS_PADSIZE
#define _SS_SIZE    __SIZEOF_SOCKADDR_STORAGE
#ifdef __ss_aligntype
#define _SS_PADSIZE (__SIZEOF_SOCKADDR_STORAGE - __SOCKADDR_COMMON_SIZE - __ALIGNOF_SOCKADDR_STORAGE)
#else /* __ss_aligntype */
#define _SS_PADSIZE (__SIZEOF_SOCKADDR_STORAGE - __SOCKADDR_COMMON_SIZE)
#endif /* !__ss_aligntype */

/* Structure large enough to hold any socket address (with the historical exception of AF_UNIX). */
#ifdef __CC__
__DECL_BEGIN

struct __ATTR_ALIGNED(__ALIGNOF_SOCKADDR_STORAGE) sockaddr_storage /*[PREFIX(ss_)]*/ {
	__SOCKADDR_COMMON(ss_);    /* Address family, etc. */
	__BYTE_TYPE__  __ss_padding[_SS_PADSIZE];
#ifdef __ss_aligntype
	__ss_aligntype __ss_align; /* Force desired alignment. */
#endif /* __ss_aligntype */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_GENERIC_SOCKADDR_STORAGE_H */
