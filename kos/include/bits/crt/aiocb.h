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
#ifndef _BITS_CRT_AIOCB_H
#define _BITS_CRT_AIOCB_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/sigevent.h>
#include <bits/types.h>

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

struct aiocb /*[PREFIX(aio_)]*/ {
	__INT32_TYPE__      aio_fildes;     /* [TYPE(fd_t)] File descriptor to operate upon */
	__INT32_TYPE__      aio_lio_opcode; /* Opcode (s.a. `lio_listio(3)') */
	__INT32_TYPE__      aio_reqprio;    /* ... */
#if __SIZEOF_POINTER__ > 4
	__INT32_TYPE__    __aio_pad0;       /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
	void volatile      *aio_buf;        /* Input/output buffer for `aio_write(3)' and `aio_read(3)' */
	__size_t            aio_nbytes;     /* Number of bytes to transfer `aio_write(3)' and `aio_read(3)' */
	struct sigevent     aio_sigevent;   /* Signal event triggered once AIO operation has completed. */
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
	__pos_t             aio_offset;     /* File offset for `aio_write(3)' and `aio_read(3)' */
#else /* __USE_KOS_ALTERATIONS */
	__off_t             aio_offset;     /* File offset for `aio_write(3)' and `aio_read(3)' */
#endif /* !__USE_KOS_ALTERATIONS */
	char              __glibc_reserved[32];
};


#ifdef __USE_LARGEFILE64
#if (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && defined(__USE_STRUCT64_MACRO)
#define aiocb64 aiocb
#else /* (__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && __USE_STRUCT64_MACRO */
#define __aiocb64 aiocb64
#endif /* (!__USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) || !__USE_STRUCT64_MACRO */
#endif /* __USE_LARGEFILE64 */

#if (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && defined(__USE_STRUCT64_MACRO)
#define __aiocb64 aiocb
#else /* (__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && __USE_STRUCT64_MACRO */
struct __aiocb64 /*[NAME(aiocb64)][PREFIX(tv_)]*/ {
	__INT32_TYPE__      aio_fildes;     /* [TYPE(fd_t)] File descriptor to operate upon */
	__INT32_TYPE__      aio_lio_opcode; /* Opcode (s.a. `lio_listio(3)') */
	__INT32_TYPE__      aio_reqprio;    /* ... */
#if __SIZEOF_POINTER__ > 4
	__INT32_TYPE__    __aio_pad0;       /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
	void volatile      *aio_buf;        /* Input/output buffer for `aio_write(3)' and `aio_read(3)' */
	__size_t            aio_nbytes;     /* Number of bytes to transfer `aio_write(3)' and `aio_read(3)' */
	struct sigevent     aio_sigevent;   /* Signal event triggered once AIO operation has completed. */
	/* Internal members. */
	struct __aiocb64 *__next_prio;
	__INT32_TYPE__    __abs_prio;
	__INT32_TYPE__    __policy;
	__INT32_TYPE__    __error_code;
#if __SIZEOF_SIZE_T__ > 4
	__INT32_TYPE__    __aio_pad1;       /* ... */
#endif /* __SIZEOF_SIZE_T__ > 4 */
	__ssize_t         __return_value;
#ifdef __USE_KOS_ALTERATIONS
	__pos64_t           aio_offset;     /* File offset for `aio_write(3)' and `aio_read(3)' */
#else /* __USE_KOS_ALTERATIONS */
	__off64_t           aio_offset;     /* File offset for `aio_write(3)' and `aio_read(3)' */
#endif /* !__USE_KOS_ALTERATIONS */
	char              __glibc_reserved[32];
};
#endif /* (!__USE_FILE_OFFSET64 && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) || !__USE_STRUCT64_MACRO */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("tv_nsec")
#pragma pop_macro("tv_sec")
#pragma pop_macro("aiocb")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_BITS_CRT_AIOCB_H */
