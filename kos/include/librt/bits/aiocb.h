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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBRT_BITS_AIOCB_H
#define _LIBRT_BITS_AIOCB_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/sigevent.h>
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



#ifdef __CC__
__SYSDECL_BEGIN
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("aiocb")
#pragma push_macro("tv_sec")
#pragma push_macro("tv_nsec")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef aiocb
#undef tv_sec
#undef tv_nsec

#ifndef __aiocb_defined
#define __aiocb_defined 1
struct aiocb /*[PREFIX(aio_)]*/ {
	__INT32_TYPE__      aio_fildes;     /* File descriptor. */
	__INT32_TYPE__      aio_lio_opcode; /* Operation to be performed. */
	__INT32_TYPE__      aio_reqprio;    /* Request priority offset. */
#if __SIZEOF_POINTER__ > 4
	__INT32_TYPE__    __aio_pad0;       /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
	void volatile      *aio_buf;        /* Location of buffer. */
	__size_t            aio_nbytes;     /* Length of transfer. */
	struct sigevent     aio_sigevent;   /* Signal number and value. */
	/* Internal members. */
	struct aiocb     *__next_prio;
	__INT32_TYPE__    __abs_prio;
	__INT32_TYPE__    __policy;
	__INT32_TYPE__    __error_code;
#if __SIZEOF_SIZE_T__ > 4
	__INT32_TYPE__    __aio_pad1;       /* ... */
#endif /* __SIZEOF_SIZE_T__ > 4 */
	__ssize_t         __return_value;
#ifdef __USE_KOS_ALTERATIONS
	__FS_TYPE(pos)      aio_offset;     /* File offset. */
#else /* __USE_KOS_ALTERATIONS */
	__FS_TYPE(off)      aio_offset;     /* File offset. */
#endif /* !__USE_KOS_ALTERATIONS */
	char              __glibc_reserved[32];
};
#endif /* !__aiocb_defined */

#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
#define _AIOCB_MATCHES_AIOCB64 1
#endif /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */

#ifdef __USE_LARGEFILE64
#ifndef __aiocb64_defined
#define __aiocb64_defined 1
#if (defined(__USE_FILE_OFFSET64) || defined(_AIOCB_MATCHES_AIOCB64)) && defined(__USE_STRUCT64_MACRO)
#define aiocb64 aiocb
#else /* (__USE_FILE_OFFSET64 || _AIOCB_MATCHES_AIOCB64) && __USE_STRUCT64_MACRO */
#define __aiocb64 aiocb64
#endif /* (!__USE_FILE_OFFSET64 && !_AIOCB_MATCHES_AIOCB64) || !__USE_STRUCT64_MACRO */
#endif /* !__aiocb64_defined */
#endif /* __USE_LARGEFILE64 */

#if (defined(__USE_FILE_OFFSET64) || defined(_AIOCB_MATCHES_AIOCB64)) && defined(__USE_STRUCT64_MACRO)
#define __aiocb64 aiocb
#else /* (__USE_FILE_OFFSET64 || _AIOCB_MATCHES_AIOCB64) && __USE_STRUCT64_MACRO */
struct __aiocb64 /*[NAME(aiocb64)][PREFIX(tv_)]*/ {
	__INT32_TYPE__      aio_fildes;     /* File descriptor. */
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
#ifdef __USE_KOS_ALTERATIONS
	__pos64_t           aio_offset;     /* File offset. */
#else /* __USE_KOS_ALTERATIONS */
	__off64_t           aio_offset;     /* File offset. */
#endif /* !__USE_KOS_ALTERATIONS */
	char              __glibc_reserved[32];
};
#endif /* (!__USE_FILE_OFFSET64 && !_AIOCB_MATCHES_AIOCB64) || !__USE_STRUCT64_MACRO */

#ifdef __USE_KOS
#ifndef __aiocb32_defined
#define __aiocb32_defined 1
#if !defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
#define aiocb32 aiocb
#else /* !__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
#define __aiocb32 aiocb32
#endif /* __USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
#endif /* !__aiocb32_defined */
#endif /* __USE_KOS */

#if !defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
#define __aiocb32 aiocb
#else /* !__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
struct __aiocb32 /*[NAME(aiocb32)][PREFIX(tv_)]*/ {
	__INT32_TYPE__      aio_fildes;     /* File descriptor. */
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
#ifdef __USE_KOS_ALTERATIONS
	__pos32_t           aio_offset;     /* File offset. */
#else /* __USE_KOS_ALTERATIONS */
	__off32_t           aio_offset;     /* File offset. */
#endif /* !__USE_KOS_ALTERATIONS */
	char              __glibc_reserved[32];
};
#endif /* __USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("tv_nsec")
#pragma pop_macro("tv_sec")
#pragma pop_macro("aiocb")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_LIBRT_BITS_AIOCB_H */
