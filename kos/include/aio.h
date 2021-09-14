/* HASH CRC-32:0xe92ba7c3 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/aio.h) */
/* (#) Portability: GNU C Library (/rt/aio.h) */
/* (#) Portability: NetBSD        (/include/aio.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/aio.h) */
/* (#) Portability: musl libc     (/include/aio.h) */
#ifndef _AIO_H
#define _AIO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/crt/aio.h>
#include <bits/os/sigevent.h> /* struct sigevent */
#include <bits/os/timespec.h>
#include <bits/types.h>
#include <bits/crt/aiocb.h>

#ifdef __USE_GNU
#include <bits/crt/aioinit.h>
#endif /* __USE_GNU */

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

/* Return values of cancellation function. */
#if !defined(AIO_CANCELED) && defined(__AIO_CANCELED)
#define AIO_CANCELED    __AIO_CANCELED    /* ??? */
#endif /* !AIO_CANCELED && __AIO_CANCELED */
#if !defined(AIO_NOTCANCELED) && defined(__AIO_NOTCANCELED)
#define AIO_NOTCANCELED __AIO_NOTCANCELED /* ??? */
#endif /* !AIO_NOTCANCELED && __AIO_NOTCANCELED */
#if !defined(AIO_ALLDONE) && defined(__AIO_ALLDONE)
#define AIO_ALLDONE     __AIO_ALLDONE     /* ??? */
#endif /* !AIO_ALLDONE && __AIO_ALLDONE */

/* Operation codes for `aio_lio_opcode'. */
#if !defined(LIO_READ) && defined(__LIO_READ)
#define LIO_READ  __LIO_READ  /* ??? */
#endif /* !LIO_READ && __LIO_READ */
#if !defined(LIO_WRITE) && defined(__LIO_WRITE)
#define LIO_WRITE __LIO_WRITE /* ??? */
#endif /* !LIO_WRITE && __LIO_WRITE */
#if !defined(LIO_NOP) && defined(__LIO_NOP)
#define LIO_NOP   __LIO_NOP   /* ??? */
#endif /* !LIO_NOP && __LIO_NOP */

/* Synchronization options for `lio_listio' function. */
#if !defined(LIO_WAIT) && defined(__LIO_WAIT)
#define LIO_WAIT   __LIO_WAIT   /* ??? */
#endif /* !LIO_WAIT && __LIO_WAIT */
#if !defined(LIO_NOWAIT) && defined(__LIO_NOWAIT)
#define LIO_NOWAIT __LIO_NOWAIT /* ??? */
#endif /* !LIO_NOWAIT && __LIO_NOWAIT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sigevent_t_defined
#define __sigevent_t_defined 1
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */

#if defined(__CRT_HAVE_aio_read64) && defined(__USE_FILE_OFFSET64)
/* >> aio_read(3)
 * Begin an async `read(2)' operation (TODO: Document fields used) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_read,(struct aiocb *__aiocbp),aio_read64,(__aiocbp))
#elif defined(__CRT_HAVE_aio_read) && !defined(__USE_FILE_OFFSET64)
/* >> aio_read(3)
 * Begin an async `read(2)' operation (TODO: Document fields used) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_read,(struct aiocb *__aiocbp),(__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_write64) && defined(__USE_FILE_OFFSET64)
/* >> aio_write(3)
 * Begin an async `write(2)' operation (TODO: Document fields used) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_write,(struct aiocb *__aiocbp),aio_write64,(__aiocbp))
#elif defined(__CRT_HAVE_aio_write) && !defined(__USE_FILE_OFFSET64)
/* >> aio_write(3)
 * Begin an async `write(2)' operation (TODO: Document fields used) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_write,(struct aiocb *__aiocbp),(__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_fsync64) && defined(__USE_FILE_OFFSET64)
/* >> aio_fsync(3)
 * Begin an async `fsync(2)' operation (TODO: Document fields used) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_fsync,(int __operation, struct aiocb *__aiocbp),aio_fsync64,(__operation,__aiocbp))
#elif defined(__CRT_HAVE_aio_fsync) && !defined(__USE_FILE_OFFSET64)
/* >> aio_fsync(3)
 * Begin an async `fsync(2)' operation (TODO: Document fields used) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_fsync,(int __operation, struct aiocb *__aiocbp),(__operation,__aiocbp))
#endif /* ... */
/* >> lio_listio(3)
 * Execute/perform a `list' of AIO operations
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT' */
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,lio_listio,(int __mode, struct aiocb *const __list[__restrict_arr], __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sig),(__mode,__list,__nent,__sig))
#if defined(__CRT_HAVE_aio_error64) && defined(__USE_FILE_OFFSET64)
/* >> aio_error(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress
 * @return: ECANCELED:   Operation was cancelled
 * @return: * :          The  `errno'  with  which  the  async  operation  failed.
 *                       s.a. `read(2)', `write(2)', `fsync(2)' and `fdatasync(2)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,aio_error,(struct aiocb const *__aiocbp),aio_error64,(__aiocbp))
#elif defined(__CRT_HAVE_aio_error) && !defined(__USE_FILE_OFFSET64)
/* >> aio_error(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress
 * @return: ECANCELED:   Operation was cancelled
 * @return: * :          The  `errno'  with  which  the  async  operation  failed.
 *                       s.a. `read(2)', `write(2)', `fsync(2)' and `fdatasync(2)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,aio_error,(struct aiocb const *__aiocbp),(__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_return64) && defined(__USE_FILE_OFFSET64)
/* >> aio_return(3)
 * @return: * : Return value of async `read(2)', `write(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,aio_return,(struct aiocb *__aiocbp),aio_return64,(__aiocbp))
#elif defined(__CRT_HAVE_aio_return) && !defined(__USE_FILE_OFFSET64)
/* >> aio_return(3)
 * @return: * : Return value of async `read(2)', `write(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,aio_return,(struct aiocb *__aiocbp),(__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_cancel64) && defined(__USE_FILE_OFFSET64)
/* >> aio_cancel(3)
 * @return: AIO_CANCELED:    Operations cancelled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 * @return: AIO_ALLDONE:     Operations were already completed before the call was made
 * @return: -1:              Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_cancel,(__fd_t __fildes, struct aiocb *__aiocbp),aio_cancel64,(__fildes,__aiocbp))
#elif defined(__CRT_HAVE_aio_cancel) && !defined(__USE_FILE_OFFSET64)
/* >> aio_cancel(3)
 * @return: AIO_CANCELED:    Operations cancelled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 * @return: AIO_ALLDONE:     Operations were already completed before the call was made
 * @return: -1:              Error (s.a. `errno') */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_cancel,(__fd_t __fildes, struct aiocb *__aiocbp),(__fildes,__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_suspend64t64) && defined(__USE_FILE_OFFSET64) && defined(__USE_TIME_BITS64)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,aio_suspend,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout),aio_suspend64t64,(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspendt64) && !defined(__USE_FILE_OFFSET64) && defined(__USE_TIME_BITS64)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,aio_suspend,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout),aio_suspendt64,(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspend64) && defined(__USE_FILE_OFFSET64) && !defined(__USE_TIME_BITS64)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,aio_suspend,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout),aio_suspend64,(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspend) && !defined(__USE_FILE_OFFSET64) && !defined(__USE_TIME_BITS64)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,aio_suspend,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout),(__list,__nent,__timeout))
#elif (defined(__CRT_HAVE_aio_suspend64t64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_aio_suspendt64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_aio_suspend) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || (defined(__CRT_HAVE_aio_suspend64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_aio_suspend) && !defined(__USE_FILE_OFFSET64))
#include <libc/local/aio/aio_suspend.h>
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(aio_suspend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL aio_suspend)(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(aio_suspend))(__list, __nent, __timeout); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_aio_read) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_read(3)
 * Begin an async `read(2)' operation (TODO: Document fields used) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_read64,(struct aiocb64 *__aiocbp),aio_read,(__aiocbp))
#elif defined(__CRT_HAVE_aio_read64)
/* >> aio_read(3)
 * Begin an async `read(2)' operation (TODO: Document fields used) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_read64,(struct aiocb64 *__aiocbp),(__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_write) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_write(3)
 * Begin an async `write(2)' operation (TODO: Document fields used) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_write64,(struct aiocb64 *__aiocbp),aio_write,(__aiocbp))
#elif defined(__CRT_HAVE_aio_write64)
/* >> aio_write(3)
 * Begin an async `write(2)' operation (TODO: Document fields used) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_write64,(struct aiocb64 *__aiocbp),(__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_fsync) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_fsync(3)
 * Begin an async `fsync(2)' operation (TODO: Document fields used) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_fsync64,(int __operation, struct aiocb64 *__aiocbp),aio_fsync,(__operation,__aiocbp))
#elif defined(__CRT_HAVE_aio_fsync64)
/* >> aio_fsync(3)
 * Begin an async `fsync(2)' operation (TODO: Document fields used) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_fsync64,(int __operation, struct aiocb64 *__aiocbp),(__operation,__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_write) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_write(3)
 * Begin an async `write(2)' operation (TODO: Document fields used) */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,lio_listio64,(int __mode, struct aiocb64 *const __list[__restrict_arr], __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sig),aio_write,(__mode,__list,__nent,__sig))
#elif defined(__CRT_HAVE_lio_listio64)
/* >> aio_write(3)
 * Begin an async `write(2)' operation (TODO: Document fields used) */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,lio_listio64,(int __mode, struct aiocb64 *const __list[__restrict_arr], __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sig),(__mode,__list,__nent,__sig))
#endif /* ... */
#if defined(__CRT_HAVE_aio_error) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_error(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress
 * @return: ECANCELED:   Operation was cancelled
 * @return: * :          The  `errno'  with  which  the  async  operation  failed.
 *                       s.a. `read(2)', `write(2)', `fsync(2)' and `fdatasync(2)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_error64,(struct aiocb64 const *__aiocbp),aio_error,(__aiocbp))
#elif defined(__CRT_HAVE_aio_error64)
/* >> aio_error(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress
 * @return: ECANCELED:   Operation was cancelled
 * @return: * :          The  `errno'  with  which  the  async  operation  failed.
 *                       s.a. `read(2)', `write(2)', `fsync(2)' and `fdatasync(2)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_error64,(struct aiocb64 const *__aiocbp),(__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_return) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_return(3)
 * @return: * : Return value of async `read(2)', `write(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,aio_return64,(struct aiocb64 *__aiocbp),aio_return,(__aiocbp))
#elif defined(__CRT_HAVE_aio_return64)
/* >> aio_return(3)
 * @return: * : Return value of async `read(2)', `write(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,aio_return64,(struct aiocb64 *__aiocbp),(__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_cancel) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_cancel(3)
 * @return: AIO_CANCELED:    Operations cancelled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 * @return: AIO_ALLDONE:     Operations were already completed before the call was made
 * @return: -1:              Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_cancel64,(__fd_t __fildes, struct aiocb64 *__aiocbp),aio_cancel,(__fildes,__aiocbp))
#elif defined(__CRT_HAVE_aio_cancel64)
/* >> aio_cancel(3)
 * @return: AIO_CANCELED:    Operations cancelled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 * @return: AIO_ALLDONE:     Operations were already completed before the call was made
 * @return: -1:              Error (s.a. `errno') */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_cancel64,(__fd_t __fildes, struct aiocb64 *__aiocbp),(__fildes,__aiocbp))
#endif /* ... */
#if defined(__CRT_HAVE_aio_suspend) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_suspend64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout),aio_suspend,(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspendt64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_suspend64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout),aio_suspendt64,(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspend64) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_suspend64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout),(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspend64t64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_suspend64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout),aio_suspend64t64,(__list,__nent,__timeout))
#elif (defined(__CRT_HAVE_aio_suspend) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || (defined(__CRT_HAVE_aio_suspendt64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE_aio_suspend) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_aio_suspend64)
#include <libc/local/aio/aio_suspend64.h>
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(aio_suspend64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL aio_suspend64)(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(aio_suspend64))(__list, __nent, __timeout); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_aio_suspend64t64) && defined(__USE_FILE_OFFSET64)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __timeout),aio_suspend64t64,(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspendt64) && !defined(__USE_FILE_OFFSET64)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __timeout),(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspend) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __timeout),aio_suspend,(__list,__nent,__timeout))
#elif (defined(__CRT_HAVE_aio_suspend64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_aio_suspend) && !defined(__USE_FILE_OFFSET64))
#include <libc/local/aio/aio_suspendt64.h>
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(aio_suspendt64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL aio_suspendt64)(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(aio_suspendt64))(__list, __nent, __timeout); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_aio_suspend) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_suspend64t64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __timeout),aio_suspend,(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspendt64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_suspend64t64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __timeout),aio_suspendt64,(__list,__nent,__timeout))
#elif defined(__CRT_HAVE_aio_suspend64) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_suspend64t64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __timeout),aio_suspend64,(__list,__nent,__timeout))
#elif (defined(__CRT_HAVE_aio_suspend) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_aio_suspend64)
#include <libc/local/aio/aio_suspend64t64.h>
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(aio_suspend64t64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL aio_suspend64t64)(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(aio_suspend64t64))(__list, __nent, __timeout); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_TIME64 */

#ifdef __USE_GNU
/* >> aio_init(3) */
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1)),__NOTHROW_NCX,aio_init,(struct aioinit const *__init),(__init))
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_AIO_H */
