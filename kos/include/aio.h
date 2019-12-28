/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _AIO_H
#define _AIO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/sigevent.h>
#include <bits/timespec.h>
#include <bits/types.h>

#include <librt/_api.h>
#include <librt/asm/aio.h>
#include <librt/bits/aiocb.h>
#ifdef __USE_GNU
#include <librt/bits/aioinit.h>
#endif /* __USE_GNU */
#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */


/* Documentation taken from Glibc /usr/include/aio.h */
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
   <http://www.gnu.org/licenses/>. */

__SYSDECL_BEGIN


#ifdef __CC__

#ifdef __USE_GNU
/* Allow user to specify optimization */
#ifndef __aio_init_defined
#define __aio_init_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBRT_CC aio_init)(struct aioinit const *__init);
#endif /* !__aio_init_defined */
#endif /* __USE_GNU */

#ifdef __USE_FILE_OFFSET64
#define __AIO_REDIRECT(attr, Treturn, nothrow, name, param, args) \
	__REDIRECT(__LIBRT_DECL, attr, Treturn, nothrow, __LIBRT_CC, name, param, name##64, args)
#else /* __USE_FILE_OFFSET64 */
#define __AIO_REDIRECT(attr, Treturn, nothrow, name, param, args) \
	__LIBRT_DECL attr Treturn nothrow(__LIBRT_CC name) param;
#endif /* !__USE_FILE_OFFSET64 */

/* Enqueue read request for given number of bytes and the given priority */
#ifndef __aio_read_defined
#define __aio_read_defined 1
__AIO_REDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_read,(struct aiocb *__aiocbp),(__aiocbp))
#endif /* !__aio_read_defined */

/* Enqueue write request for given number of bytes and the given priority */
#ifndef __aio_write_defined
#define __aio_write_defined 1
__AIO_REDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_write,(struct aiocb *__aiocbp),(__aiocbp))
#endif /* !__aio_write_defined */

/* Initiate list of I/O requests */
#ifndef __lio_listio_defined
#define __lio_listio_defined 1
__AIO_REDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,lio_listio,
               (int __mode, struct aiocb *const __list[__restrict_arr],
                __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sig),
               (__mode, __list, __nent, __sig))
#endif /* !__lio_listio_defined */

/* Retrieve error status associated with AIOCBP */
#ifndef __aio_error_defined
#define __aio_error_defined 1
__AIO_REDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,
               aio_error,(struct aiocb const *__aiocbp),(__aiocbp))
#endif /* !__aio_error_defined */

/* Return status associated with AIOCBP */
#ifndef __aio_return_defined
#define __aio_return_defined 1
__AIO_REDIRECT(__ATTR_NONNULL((1)),__ssize_t,__NOTHROW_NCX,
               aio_return,(struct aiocb *__aiocbp),(__aiocbp))
#endif /* !__aio_return_defined */

/* Try to cancel asynchronous I/O requests outstanding against file descriptor FILDES */
#ifndef __aio_cancel_defined
#define __aio_cancel_defined 1
__AIO_REDIRECT(,int,__NOTHROW_NCX,aio_cancel,(__fd_t __fildes, struct aiocb *__aiocbp),(__fildes,__aiocbp))
#endif /* !__aio_cancel_defined */

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
#ifndef __aio_suspend_defined
#define __aio_suspend_defined 1
#ifdef __USE_TIME_BITS64
#ifdef __USE_FILE_OFFSET64
__REDIRECT(__LIBRT_DECL,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBRT_CC,aio_suspend,
           (struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent,
            struct timespec const *__restrict __timeout),aio_suspend64t64,
           (__list, __nent, __timeout))
#else /* __USE_FILE_OFFSET64 */
__REDIRECT(__LIBRT_DECL,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBRT_CC,aio_suspend,
           (struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent,
            struct timespec const *__restrict __timeout),aio_suspendt64,
           (__list, __nent, __timeout))
#endif /* !__USE_FILE_OFFSET64 */
#else /* __USE_TIME_BITS64 */
__AIO_REDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,aio_suspend,
               (struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                struct timespec const *__restrict __timeout),
               (__list,__nent,__timeout))
#endif /* !__USE_TIME_BITS64 */
#endif /* !__aio_suspend_defined */

/* Force all operations associated with file descriptor described by `aio_fildes' member of AIOCBP. */
#ifndef __aio_fsync_defined
#define __aio_fsync_defined 1
__AIO_REDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_fsync,
               (int __operation, struct aiocb *__aiocbp),(__operation,__aiocbp))
#endif /* !__aio_fsync_defined */

#undef __AIO_REDIRECT

#ifdef __USE_LARGEFILE64
/* Enqueue read request for given number of bytes and the given priority */
#ifndef __aio_read64_defined
#define __aio_read64_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBRT_CC aio_read64)(struct aiocb64 *__aiocbp);
#endif /* !__aio_read64_defined */

/* Enqueue write request for given number of bytes and the given priority */
#ifndef __aio_write64_defined
#define __aio_write64_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBRT_CC aio_write64)(struct aiocb64 *__aiocbp);
#endif /* !__aio_write64_defined */

/* Initiate list of I/O requests */
#ifndef __lio_listio64_defined
#define __lio_listio64_defined 1
__LIBRT_DECL __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBRT_CC lio_listio64)(int __mode, struct aiocb64 *const __list[__restrict_arr],
                                       __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sig);
#endif /* !__lio_listio64_defined */

/* Retrieve error status associated with AIOCBP */
#ifndef __aio_error64_defined
#define __aio_error64_defined 1
__LIBRT_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBRT_CC aio_error64)(struct aiocb64 const *__aiocbp);
#endif /* !__aio_error64_defined */

/* Return status associated with AIOCBP */
#ifndef __aio_return64_defined
#define __aio_return64_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) __ssize_t
__NOTHROW_NCX(__LIBRT_CC aio_return64)(struct aiocb64 *__aiocbp);
#endif /* !__aio_return64_defined */

/* Try to cancel asynchronous I/O requests outstanding against file descriptor FILDES */
#ifndef __aio_cancel64_defined
#define __aio_cancel64_defined 1
__LIBRT_DECL int
__NOTHROW_NCX(__LIBRT_CC aio_cancel64)(__fd_t __fildes, struct aiocb64 *__aiocbp);
#endif /* !__aio_cancel64_defined */

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
#ifndef __aio_suspend64_defined
#define __aio_suspend64_defined 1
#ifdef __USE_TIME_BITS64
__REDIRECT(__LIBRT_DECL,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBRT_CC,aio_suspend64,
           (struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout),
           aio_suspend64t64,(__list, __nent, __timeout))
#else /* __USE_TIME_BITS64 */
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBRT_CC aio_suspend64)(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                        struct timespec const *__restrict __timeout);
#endif /* !__USE_TIME_BITS64 */
#endif /* !__aio_suspend64_defined */

/* Force all operations associated with file descriptor described by `aio_fildes' member of AIOCBP. */
#ifndef __aio_fsync64_defined
#define __aio_fsync64_defined 1
__LIBRT_DECL __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBRT_CC aio_fsync64)(int __operation, struct aiocb64 *__aiocbp);
#endif /* !__aio_fsync64_defined */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_TIME64
/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
#ifndef __aio_suspendt64_defined
#define __aio_suspendt64_defined 1
#ifdef __USE_FILE_OFFSET64
__REDIRECT(__LIBRT_DECL,__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__LIBRT_CC,aio_suspendt64,
           (struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __timeout),
           aio_suspend64t64,(__list, __nent, __timeout))
#else /* __USE_FILE_OFFSET64 */
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBRT_CC aio_suspendt64)(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                         struct timespec64 const *__restrict __timeout);
#endif /* !__USE_FILE_OFFSET64 */
#endif /* !__aio_suspendt64_defined */

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
#ifdef __USE_LARGEFILE64
#ifndef __aio_suspend64t64_defined
#define __aio_suspend64t64_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBRT_CC aio_suspend64t64)(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                           struct timespec64 const *__restrict __timeout);
#endif /* !__aio_suspend64t64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_TIME64 */


#endif /* __CC__ */

__SYSDECL_END

#endif /* !_AIO_H */
