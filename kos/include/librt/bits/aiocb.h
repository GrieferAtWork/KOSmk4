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
#ifndef _LIBRT_BITS_AIOCB_H
#define _LIBRT_BITS_AIOCB_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/sigevent.h>
#include <bits/types.h>

/* Documentation derived from Glibc /usr/include/aio.h */
/* Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


#ifdef __USE_LARGEFILE64
#define __aiocb64 aiocb
#ifdef __USE_LARGEFILE64
#define aiocb64   aiocb
#endif /* __USE_LARGEFILE64 */
#ifdef __USE_KOS
#define __aiocb32 aiocb32
#else /* __USE_KOS */
#define __aiocb32 __aiocb32
#endif /* !__USE_KOS */
#else /* __USE_LARGEFILE64 */
#define __aiocb32 aiocb
#define __aiocb64 __aiocb64
#ifdef __USE_LARGEFILE64
#define __aiocb64 aiocb64
#endif /* __USE_LARGEFILE64 */
#ifdef __USE_KOS
#define aiocb32   aiocb
#endif /* __USE_KOS */
#endif /* !__USE_LARGEFILE64 */


__SYSDECL_BEGIN

/* Asynchronous I/O control block. */
/*[[[struct]]]*/
#ifdef __CC__
struct __aiocb32 /*[PREFIX(aio_)]*/ {
	__INT32_TYPE__      aio_fildes;     /* File desriptor. */
	__INT32_TYPE__      aio_lio_opcode; /* Operation to be performed. */
	__INT32_TYPE__      aio_reqprio;    /* Request priority offset. */
#if __SIZEOF_POINTER__ > 4
	__INT32_TYPE__    __aio_pad0;       /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
	void volatile      *aio_buf;        /* Location of buffer. */
	__size_t            aio_nbytes;     /* Length of transfer. */
	struct sigevent     aio_sigevent;   /* Signal number and value. */
	/* Internal members. */
	struct __aiocb32 *__next_prio;
	__INT32_TYPE__    __abs_prio;
	__INT32_TYPE__    __policy;
	__INT32_TYPE__    __error_code;
#if __SIZEOF_SIZE_T__ > 4
	__INT32_TYPE__    __aio_pad1;       /* ... */
#endif /* __SIZEOF_SIZE_T__ > 4 */
	__ssize_t         __return_value;
#ifdef __USE_KOS
	__pos32_t           aio_offset;     /* File offset. */
#else /* __USE_KOS */
	__off32_t           aio_offset;     /* File offset. */
#endif /* !__USE_KOS */
	char              __glibc_reserved[32];
};
#endif /* __CC__ */
/*[[[end]]]*/

/*[[[struct]]]*/
#ifdef __CC__
struct __aiocb64 /*[PREFIX(aio_)]*/ {
	__INT32_TYPE__      aio_fildes;     /* File desriptor. */
	__INT32_TYPE__      aio_lio_opcode; /* Operation to be performed. */
	__INT32_TYPE__      aio_reqprio;    /* Request priority offset. */
#if __SIZEOF_POINTER__ > 4
	__INT32_TYPE__    __aio_pad0;       /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
	void volatile      *aio_buf;        /* Location of buffer. */
	__size_t            aio_nbytes;     /* Length of transfer. */
	struct sigevent     aio_sigevent;   /* Signal number and value. */
	/* Internal members. */
	struct __aiocb32 *__next_prio;
	__INT32_TYPE__    __abs_prio;
	__INT32_TYPE__    __policy;
	__INT32_TYPE__    __error_code;
#if __SIZEOF_SIZE_T__ > 4
	__INT32_TYPE__    __aio_pad1;       /* ... */
#endif /* __SIZEOF_SIZE_T__ > 4 */
	__ssize_t         __return_value;
#ifdef __USE_KOS
	__pos64_t           aio_offset;     /* File offset. */
#else /* __USE_KOS */
	__off64_t           aio_offset;     /* File offset. */
#endif /* !__USE_KOS */
	char              __glibc_reserved[32];
};
#endif /* __CC__ */
/*[[[end]]]*/

__SYSDECL_END

#endif /* !_LIBRT_BITS_AIOCB_H */
