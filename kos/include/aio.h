/* HASH CRC-32:0xbb5ec56f */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/aio.h) */
/* (#) Portability: GNU C Library (/rt/aio.h) */
/* (#) Portability: NetBSD        (/include/aio.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/aio.h) */
/* (#) Portability: libc6         (/include/aio.h) */
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

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

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
#define LIO_READ  __LIO_READ  /* Perform an async `read(2)' or `pread(2)' */
#endif /* !LIO_READ && __LIO_READ */
#if !defined(LIO_WRITE) && defined(__LIO_WRITE)
#define LIO_WRITE __LIO_WRITE /* Perform an async `write(2)' or `pwrite(2)' */
#endif /* !LIO_WRITE && __LIO_WRITE */
#if !defined(LIO_NOP) && defined(__LIO_NOP)
#define LIO_NOP   __LIO_NOP   /* No-op */
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
#define __sigevent_t_defined
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */

/*
 * The implementation of NOTIFY_COMPLETION behaves identical to:
 *
 * >> struct thread_cookie {
 * >>     void (LIBKCALL *tc_func)(sigval_t value);
 * >>     sigval_t        tc_value;
 * >> };
 * >> static void *LIBCCALL thread_wrapper(void *arg) {
 * >>     struct thread_cookie cookie;
 * >>     cookie = *(struct thread_cookie *)arg;
 * >>     free(arg);
 * >>     (*cookie.tc_func)(cookie.tc_value);
 * >>     return NULL;
 * >> }
 * >>
 * >> errno_t NOTIFY_COMPLETION(struct sigevent *ev) {
 * >>     errno_t result = EOK;
 * >>     if (ev->sigev_notify == SIGEV_THREAD) {
 * >>         pthread_attr_t _attr;
 * >>         pthread_attr_t *attr = ev->sigev_notify_attributes;
 * >>         struct thread_cookie *cookie;
 * >>         if (!attr) {
 * >>             result = pthread_attr_init(&_attr);
 * >>             if (result != EOK)
 * >>                 goto done;
 * >>             result = pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_DETACHED);
 * >>             if (result != EOK) {
 * >>                 pthread_attr_destroy(&_attr);
 * >>                 goto done;
 * >>             }
 * >>             attr = &_attr;
 * >>         }
 * >>         cookie = (struct thread_cookie *)malloc(sizeof(struct thread_cookie));
 * >>         if (!cookie)
 * >>             result = errno; // Likely: ENOMEM
 * >>         else {
 * >>             pthread_t p;
 * >>             cookie->tc_func  = ev->sigev_notify_function;
 * >>             cookie->tc_value = ev->sigev_value;
 * >>             result = pthread_create(&p, attr, &thread_wrapper, cookie);
 * >>             if (result != EOK)
 * >>                 free(cookie);
 * >>         }
 * >>         if (!ev->sigev_notify_attributes)
 * >>             pthread_attr_destroy(&_attr);
 * >>     } else if ((ev->sigev_notify == SIGEV_SIGNAL ||
 * >>                 ev->sigev_notify == SIGEV_THREAD_ID) &&
 * >>                (ev->sigev_signo != 0)) {
 * >>         // When `sigev_signo == 0', the below syscalls would become no-ops
 * >>         // Or   rather,   would  "test if we're allowed to send a signal".
 * >>         siginfo_t info;
 * >>         bzero(&info, sizeof(siginfo_t));
 * >>         info.si_signo = ev->sigev_signo;
 * >>         info.si_code  = SI_ASYNCIO;
 * >>         info.si_pid   = getpid();
 * >>         info.si_uid   = getuid();
 * >>         info.si_value = ev->sigev_value;
 * >>         if (ev->sigev_notify == SIGEV_SIGNAL) {
 * >>             result = -sys_rt_sigqueueinfo(info.si_pid, info.si_signo, &info);
 * >>         } else {
 * >>             // PORTABILITY WARNING: Support for this case isn't implemented by
 * >>             //                      gLibc, which only supports `SIGEV_SIGNAL'!
 * >>             result = -sys_rt_tgsigqueueinfo(info.si_pid, ev->_sigev_tid,
 * >>                                             info.si_signo, &info);
 * >>         }
 * >>     }
 * >> done:
 * >>     return result;
 * >> }
 *
 * WARNING: Errors returned by `NOTIFY_COMPLETION()' are silently discarded!
 */


/*
 * WARNING: ONCE STARTED, YOU MUST NOT FREE THE BACKING STRUCTURE
 *          OF `struct aiocb' UNTIL `aio_error() != EINPROGRESS'!
 *
 * Until that point, the address of the structure itself may be
 * used internally as  part of linked  lists which will  become
 * corrupted if one  of their elements  isn't properly  removed
 * prior to being free'd.
 */


#if defined(__CRT_HAVE_aio_read) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_read(3), aio_read64(3)
 * Begin an async `pread(2)' operation:
 * >> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `read(2)' is called instead (in which case `self->aio_offset' is ignored) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_read,(struct aiocb *__self),(__self))
#elif defined(__CRT_HAVE_aio_read64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_read(3), aio_read64(3)
 * Begin an async `pread(2)' operation:
 * >> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `read(2)' is called instead (in which case `self->aio_offset' is ignored) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_read,(struct aiocb *__self),aio_read64,(__self))
#endif /* ... */
#if defined(__CRT_HAVE_aio_write) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_write(3), aio_write64(3)
 * Begin an async `pwrite(2)' operation:
 * >> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `write(2)' is called instead (in which case `self->aio_offset' is ignored) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_write,(struct aiocb *__self),(__self))
#elif defined(__CRT_HAVE_aio_write64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_write(3), aio_write64(3)
 * Begin an async `pwrite(2)' operation:
 * >> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `write(2)' is called instead (in which case `self->aio_offset' is ignored) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_write,(struct aiocb *__self),aio_write64,(__self))
#endif /* ... */
#if defined(__CRT_HAVE_aio_fsync) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_fsync(3), aio_fsync64(3)
 * Begin an async `fsync(2)' or `fdatasync(2)' operation:
 * >> if (operation == O_SYNC) {
 * >>     fsync(self->aio_fildes);
 * >> } else if (operation == O_DSYNC) {
 * >>     fdatasync(self->aio_fildes);
 * >> }
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * @param: operation: One of `O_SYNC' or `O_DSYNC'
 * @return: 0 : Operation was started successfully
 * @return: -1: [errno=EAGAIN] Insufficient resources  (read:  `ENOMEM',  but  posix
 *                             didn't want to use that errno for whatever reason...)
 * @return: -1: [errno=EINVAL] `operation' was invalid */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_fsync,(__oflag_t __operation, struct aiocb *__self),(__operation,__self))
#elif defined(__CRT_HAVE_aio_fsync64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_fsync(3), aio_fsync64(3)
 * Begin an async `fsync(2)' or `fdatasync(2)' operation:
 * >> if (operation == O_SYNC) {
 * >>     fsync(self->aio_fildes);
 * >> } else if (operation == O_DSYNC) {
 * >>     fdatasync(self->aio_fildes);
 * >> }
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * @param: operation: One of `O_SYNC' or `O_DSYNC'
 * @return: 0 : Operation was started successfully
 * @return: -1: [errno=EAGAIN] Insufficient resources  (read:  `ENOMEM',  but  posix
 *                             didn't want to use that errno for whatever reason...)
 * @return: -1: [errno=EINVAL] `operation' was invalid */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_fsync,(__oflag_t __operation, struct aiocb *__self),aio_fsync64,(__operation,__self))
#endif /* ... */
#if defined(__CRT_HAVE_lio_listio) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lio_listio(3), lio_listio64(3)
 * Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively,  when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediately once all operations have been started.
 * If  this was successful, return `0', or  `-1' if doing so failed (`errno').
 * Note that upon error here, no AIO operations will have been started, yet.
 *
 * Additionally, the given `sigev' (if non-NULL) will be assigned as a master
 * completion event that is only triggered  once _all_ of the AIO  operations
 * have completed. Note that in this case, `sigev' will/has always be invoked
 * if this function returns  `0', even if  any of the  AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM')
 * @return: -1: [errno=EINVAL] Invalid `mode'
 * @return: -1: [errno=EINTR]  When `mode == LIO_WAIT': Calling thread was interrupted.
 *                             Note that in  this case incomplete  AIO operations  will
 *                             continue to run and that  the caller should handle  this
 *                             case by looping over  all and using `aio_suspend(3)'  to
 *                             wait for each until doing so has succeeded at least once
 *                             for every entry.
 * @return: -1: [errno=EIO]    When `mode == LIO_WAIT': At least one of the operations
 *                             failed (s.a. `aio_error(3)') */
__CDECLARE(__ATTR_INS(2, 3),int,__NOTHROW_NCX,lio_listio,(int __mode, struct aiocb *const __list[__restrict_arr], __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sigev),(__mode,__list,__nent,__sigev))
#elif defined(__CRT_HAVE_lio_listio64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lio_listio(3), lio_listio64(3)
 * Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively,  when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediately once all operations have been started.
 * If  this was successful, return `0', or  `-1' if doing so failed (`errno').
 * Note that upon error here, no AIO operations will have been started, yet.
 *
 * Additionally, the given `sigev' (if non-NULL) will be assigned as a master
 * completion event that is only triggered  once _all_ of the AIO  operations
 * have completed. Note that in this case, `sigev' will/has always be invoked
 * if this function returns  `0', even if  any of the  AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM')
 * @return: -1: [errno=EINVAL] Invalid `mode'
 * @return: -1: [errno=EINTR]  When `mode == LIO_WAIT': Calling thread was interrupted.
 *                             Note that in  this case incomplete  AIO operations  will
 *                             continue to run and that  the caller should handle  this
 *                             case by looping over  all and using `aio_suspend(3)'  to
 *                             wait for each until doing so has succeeded at least once
 *                             for every entry.
 * @return: -1: [errno=EIO]    When `mode == LIO_WAIT': At least one of the operations
 *                             failed (s.a. `aio_error(3)') */
__CREDIRECT(__ATTR_INS(2, 3),int,__NOTHROW_NCX,lio_listio,(int __mode, struct aiocb *const __list[__restrict_arr], __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sigev),lio_listio64,(__mode,__list,__nent,__sigev))
#endif /* ... */
#if defined(__CRT_HAVE_aio_error) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_error(3), aio_error64(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress (or pending)
 * @return: ECANCELED:   Operation was canceled (s.a. `aio_cancel(3)')
 * @return: EINVAL:      `self' is invalid, or its return value has already been read.
 * @return: * :          The   `errno'  with  which   the  async  operation  failed.
 *                       s.a. `pread(2)', `pwrite(2)', `fsync(2)' and `fdatasync(2)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),__errno_t,__NOTHROW_NCX,aio_error,(struct aiocb const *__self),(__self))
#elif defined(__CRT_HAVE_aio_error64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_error(3), aio_error64(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress (or pending)
 * @return: ECANCELED:   Operation was canceled (s.a. `aio_cancel(3)')
 * @return: EINVAL:      `self' is invalid, or its return value has already been read.
 * @return: * :          The   `errno'  with  which   the  async  operation  failed.
 *                       s.a. `pread(2)', `pwrite(2)', `fsync(2)' and `fdatasync(2)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__errno_t,__NOTHROW_NCX,aio_error,(struct aiocb const *__self),aio_error64,(__self))
#endif /* ... */
#if defined(__CRT_HAVE_aio_return) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_return(3), aio_return64(3)
 * @return: * : Return value of async `pread(2)', `pwrite(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: [errno=<unchanged>] AIO operation failed (s.a. `aio_error(3)')
 * @return: -1: [errno=EINVAL]      `self' is invalid (including the case where `self' is still
 *                                  in progress), or  its return value  has already been  read. */
__CDECLARE(__ATTR_INOUT(1),__SSIZE_TYPE__,__NOTHROW_NCX,aio_return,(struct aiocb *__self),(__self))
#elif defined(__CRT_HAVE_aio_return64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_return(3), aio_return64(3)
 * @return: * : Return value of async `pread(2)', `pwrite(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: [errno=<unchanged>] AIO operation failed (s.a. `aio_error(3)')
 * @return: -1: [errno=EINVAL]      `self' is invalid (including the case where `self' is still
 *                                  in progress), or  its return value  has already been  read. */
__CREDIRECT(__ATTR_INOUT(1),__SSIZE_TYPE__,__NOTHROW_NCX,aio_return,(struct aiocb *__self),aio_return64,(__self))
#endif /* ... */
#if defined(__CRT_HAVE_aio_cancel) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_cancel(3), aio_cancel64(3)
 * Cancel  a specific AIO  operation (self != NULL),  or all operations currently
 * operating on a given `fd' (self !=  NULL && fd == self->aio_fildes). For  this
 * purpose,  it is undefined if the numerical value of `fd' is used for searching
 * active operations, or the pointed-to kernel object. As such, it is recommended
 * that you always aio_cancel the same fd as was also used when the AIO operation
 * was initiated.
 * NOTE: When `AIO_CANCELED' is returned, the completion event of `self',
 *       as  specified in `self->aio_sigevent'  will have been triggered,
 *       as completion events are triggered even for canceled operations.
 * @return: AIO_CANCELED:    At least one operation was canceled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 *                           This KOS implementation never returns  this value, as it  includes
 *                           facilities to force-abort any async operation (in the same vain as
 *                           sending SIGKILL can also force-aborts a process)
 *                           NOTE: In other implementations, this return value outweighs
 *                                 `AIO_CANCELED'  and `AIO_ALLDONE' in face of multiple
 *                                 AIO operations.
 * @return: AIO_ALLDONE:     Operations had  already been  completed
 *                           (or canceled) before the call was made.
 * @return: -1: [errno=EBADF]  `fd' is not a valid file descriptor
 * @return: -1: [errno=EINVAL] `self != NULL' and the given `fd' differs from `self->aio_fildes' */
__CDECLARE(,int,__NOTHROW_NCX,aio_cancel,(__fd_t __fd, struct aiocb *__self),(__fd,__self))
#elif defined(__CRT_HAVE_aio_cancel64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_cancel(3), aio_cancel64(3)
 * Cancel  a specific AIO  operation (self != NULL),  or all operations currently
 * operating on a given `fd' (self !=  NULL && fd == self->aio_fildes). For  this
 * purpose,  it is undefined if the numerical value of `fd' is used for searching
 * active operations, or the pointed-to kernel object. As such, it is recommended
 * that you always aio_cancel the same fd as was also used when the AIO operation
 * was initiated.
 * NOTE: When `AIO_CANCELED' is returned, the completion event of `self',
 *       as  specified in `self->aio_sigevent'  will have been triggered,
 *       as completion events are triggered even for canceled operations.
 * @return: AIO_CANCELED:    At least one operation was canceled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 *                           This KOS implementation never returns  this value, as it  includes
 *                           facilities to force-abort any async operation (in the same vain as
 *                           sending SIGKILL can also force-aborts a process)
 *                           NOTE: In other implementations, this return value outweighs
 *                                 `AIO_CANCELED'  and `AIO_ALLDONE' in face of multiple
 *                                 AIO operations.
 * @return: AIO_ALLDONE:     Operations had  already been  completed
 *                           (or canceled) before the call was made.
 * @return: -1: [errno=EBADF]  `fd' is not a valid file descriptor
 * @return: -1: [errno=EINVAL] `self != NULL' and the given `fd' differs from `self->aio_fildes' */
__CREDIRECT(,int,__NOTHROW_NCX,aio_cancel,(__fd_t __fd, struct aiocb *__self),aio_cancel64,(__fd,__self))
#endif /* ... */
#if defined(__CRT_HAVE_aio_suspend) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CDECLARE(__ATTR_INS(1, 2),int,__NOTHROW_RPC,aio_suspend,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout),(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspend64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_RPC,aio_suspend,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout),aio_suspend64,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspendt64) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_RPC,aio_suspend,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout),aio_suspendt64,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspend64t64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_RPC,aio_suspend,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout),aio_suspend64t64,(__list,__nent,__rel_timeout))
#elif (defined(__CRT_HAVE_aio_suspend) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspend64) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspendt64) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspend64t64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspend) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspend64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
#include <libc/local/aio/aio_suspend.h>
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__NAMESPACE_LOCAL_USING_OR_IMPL(aio_suspend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 2) int __NOTHROW_RPC(__LIBCCALL aio_suspend)(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(aio_suspend))(__list, __nent, __rel_timeout); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_aio_read) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_read(3), aio_read64(3)
 * Begin an async `pread(2)' operation:
 * >> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `read(2)' is called instead (in which case `self->aio_offset' is ignored) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_read64,(struct aiocb64 *__self),aio_read,(__self))
#elif defined(__CRT_HAVE_aio_read64)
/* >> aio_read(3), aio_read64(3)
 * Begin an async `pread(2)' operation:
 * >> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `read(2)' is called instead (in which case `self->aio_offset' is ignored) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_read64,(struct aiocb64 *__self),(__self))
#endif /* ... */
#if defined(__CRT_HAVE_aio_write) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_write(3), aio_write64(3)
 * Begin an async `pwrite(2)' operation:
 * >> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `write(2)' is called instead (in which case `self->aio_offset' is ignored) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_write64,(struct aiocb64 *__self),aio_write,(__self))
#elif defined(__CRT_HAVE_aio_write64)
/* >> aio_write(3), aio_write64(3)
 * Begin an async `pwrite(2)' operation:
 * >> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `write(2)' is called instead (in which case `self->aio_offset' is ignored) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,aio_write64,(struct aiocb64 *__self),(__self))
#endif /* ... */
#if defined(__CRT_HAVE_aio_fsync) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_fsync(3), aio_fsync64(3)
 * Begin an async `fsync(2)' or `fdatasync(2)' operation:
 * >> if (operation == O_SYNC) {
 * >>     fsync(self->aio_fildes);
 * >> } else if (operation == O_DSYNC) {
 * >>     fdatasync(self->aio_fildes);
 * >> }
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * @param: operation: One of `O_SYNC' or `O_DSYNC'
 * @return: 0 : Operation was started successfully
 * @return: -1: [errno=EAGAIN] Insufficient resources  (read:  `ENOMEM',  but  posix
 *                             didn't want to use that errno for whatever reason...)
 * @return: -1: [errno=EINVAL] `operation' was invalid */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_fsync64,(int __operation, struct aiocb64 *__self),aio_fsync,(__operation,__self))
#elif defined(__CRT_HAVE_aio_fsync64)
/* >> aio_fsync(3), aio_fsync64(3)
 * Begin an async `fsync(2)' or `fdatasync(2)' operation:
 * >> if (operation == O_SYNC) {
 * >>     fsync(self->aio_fildes);
 * >> } else if (operation == O_DSYNC) {
 * >>     fdatasync(self->aio_fildes);
 * >> }
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * @param: operation: One of `O_SYNC' or `O_DSYNC'
 * @return: 0 : Operation was started successfully
 * @return: -1: [errno=EAGAIN] Insufficient resources  (read:  `ENOMEM',  but  posix
 *                             didn't want to use that errno for whatever reason...)
 * @return: -1: [errno=EINVAL] `operation' was invalid */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,aio_fsync64,(int __operation, struct aiocb64 *__self),(__operation,__self))
#endif /* ... */
#if defined(__CRT_HAVE_lio_listio) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lio_listio(3), lio_listio64(3)
 * Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively,  when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediately once all operations have been started.
 * If  this was successful, return `0', or  `-1' if doing so failed (`errno').
 * Note that upon error here, no AIO operations will have been started, yet.
 *
 * Additionally, the given `sigev' (if non-NULL) will be assigned as a master
 * completion event that is only triggered  once _all_ of the AIO  operations
 * have completed. Note that in this case, `sigev' will/has always be invoked
 * if this function returns  `0', even if  any of the  AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM')
 * @return: -1: [errno=EINVAL] Invalid `mode'
 * @return: -1: [errno=EINTR]  When `mode == LIO_WAIT': Calling thread was interrupted.
 *                             Note that in  this case incomplete  AIO operations  will
 *                             continue to run and that  the caller should handle  this
 *                             case by looping over  all and using `aio_suspend(3)'  to
 *                             wait for each until doing so has succeeded at least once
 *                             for every entry.
 * @return: -1: [errno=EIO]    When `mode == LIO_WAIT': At least one of the operations
 *                             failed (s.a. `aio_error(3)') */
__CREDIRECT(__ATTR_INS(2, 3),int,__NOTHROW_NCX,lio_listio64,(int __mode, struct aiocb64 *const __list[__restrict_arr], __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sigev),lio_listio,(__mode,__list,__nent,__sigev))
#elif defined(__CRT_HAVE_lio_listio64)
/* >> lio_listio(3), lio_listio64(3)
 * Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively,  when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediately once all operations have been started.
 * If  this was successful, return `0', or  `-1' if doing so failed (`errno').
 * Note that upon error here, no AIO operations will have been started, yet.
 *
 * Additionally, the given `sigev' (if non-NULL) will be assigned as a master
 * completion event that is only triggered  once _all_ of the AIO  operations
 * have completed. Note that in this case, `sigev' will/has always be invoked
 * if this function returns  `0', even if  any of the  AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM')
 * @return: -1: [errno=EINVAL] Invalid `mode'
 * @return: -1: [errno=EINTR]  When `mode == LIO_WAIT': Calling thread was interrupted.
 *                             Note that in  this case incomplete  AIO operations  will
 *                             continue to run and that  the caller should handle  this
 *                             case by looping over  all and using `aio_suspend(3)'  to
 *                             wait for each until doing so has succeeded at least once
 *                             for every entry.
 * @return: -1: [errno=EIO]    When `mode == LIO_WAIT': At least one of the operations
 *                             failed (s.a. `aio_error(3)') */
__CDECLARE(__ATTR_INS(2, 3),int,__NOTHROW_NCX,lio_listio64,(int __mode, struct aiocb64 *const __list[__restrict_arr], __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sigev),(__mode,__list,__nent,__sigev))
#endif /* ... */
#if defined(__CRT_HAVE_aio_error) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_error(3), aio_error64(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress (or pending)
 * @return: ECANCELED:   Operation was canceled (s.a. `aio_cancel(3)')
 * @return: EINVAL:      `self' is invalid, or its return value has already been read.
 * @return: * :          The   `errno'  with  which   the  async  operation  failed.
 *                       s.a. `pread(2)', `pwrite(2)', `fsync(2)' and `fdatasync(2)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,aio_error64,(struct aiocb64 const *__self),aio_error,(__self))
#elif defined(__CRT_HAVE_aio_error64)
/* >> aio_error(3), aio_error64(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress (or pending)
 * @return: ECANCELED:   Operation was canceled (s.a. `aio_cancel(3)')
 * @return: EINVAL:      `self' is invalid, or its return value has already been read.
 * @return: * :          The   `errno'  with  which   the  async  operation  failed.
 *                       s.a. `pread(2)', `pwrite(2)', `fsync(2)' and `fdatasync(2)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,aio_error64,(struct aiocb64 const *__self),(__self))
#endif /* ... */
#if defined(__CRT_HAVE_aio_return) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_return(3), aio_return64(3)
 * @return: * : Return value of async `pread(2)', `pwrite(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: [errno=<unchanged>] AIO operation failed (s.a. `aio_error(3)')
 * @return: -1: [errno=EINVAL]      `self' is invalid (including the case where `self' is still
 *                                  in progress), or  its return value  has already been  read. */
__CREDIRECT(__ATTR_INOUT(1),__SSIZE_TYPE__,__NOTHROW_NCX,aio_return64,(struct aiocb64 *__self),aio_return,(__self))
#elif defined(__CRT_HAVE_aio_return64)
/* >> aio_return(3), aio_return64(3)
 * @return: * : Return value of async `pread(2)', `pwrite(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: [errno=<unchanged>] AIO operation failed (s.a. `aio_error(3)')
 * @return: -1: [errno=EINVAL]      `self' is invalid (including the case where `self' is still
 *                                  in progress), or  its return value  has already been  read. */
__CDECLARE(__ATTR_INOUT(1),__SSIZE_TYPE__,__NOTHROW_NCX,aio_return64,(struct aiocb64 *__self),(__self))
#endif /* ... */
#if defined(__CRT_HAVE_aio_cancel) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_cancel(3), aio_cancel64(3)
 * Cancel  a specific AIO  operation (self != NULL),  or all operations currently
 * operating on a given `fd' (self !=  NULL && fd == self->aio_fildes). For  this
 * purpose,  it is undefined if the numerical value of `fd' is used for searching
 * active operations, or the pointed-to kernel object. As such, it is recommended
 * that you always aio_cancel the same fd as was also used when the AIO operation
 * was initiated.
 * NOTE: When `AIO_CANCELED' is returned, the completion event of `self',
 *       as  specified in `self->aio_sigevent'  will have been triggered,
 *       as completion events are triggered even for canceled operations.
 * @return: AIO_CANCELED:    At least one operation was canceled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 *                           This KOS implementation never returns  this value, as it  includes
 *                           facilities to force-abort any async operation (in the same vain as
 *                           sending SIGKILL can also force-aborts a process)
 *                           NOTE: In other implementations, this return value outweighs
 *                                 `AIO_CANCELED'  and `AIO_ALLDONE' in face of multiple
 *                                 AIO operations.
 * @return: AIO_ALLDONE:     Operations had  already been  completed
 *                           (or canceled) before the call was made.
 * @return: -1: [errno=EBADF]  `fd' is not a valid file descriptor
 * @return: -1: [errno=EINVAL] `self != NULL' and the given `fd' differs from `self->aio_fildes' */
__CREDIRECT(,int,__NOTHROW_NCX,aio_cancel64,(__fd_t __fildes, struct aiocb64 *__self),aio_cancel,(__fildes,__self))
#elif defined(__CRT_HAVE_aio_cancel64)
/* >> aio_cancel(3), aio_cancel64(3)
 * Cancel  a specific AIO  operation (self != NULL),  or all operations currently
 * operating on a given `fd' (self !=  NULL && fd == self->aio_fildes). For  this
 * purpose,  it is undefined if the numerical value of `fd' is used for searching
 * active operations, or the pointed-to kernel object. As such, it is recommended
 * that you always aio_cancel the same fd as was also used when the AIO operation
 * was initiated.
 * NOTE: When `AIO_CANCELED' is returned, the completion event of `self',
 *       as  specified in `self->aio_sigevent'  will have been triggered,
 *       as completion events are triggered even for canceled operations.
 * @return: AIO_CANCELED:    At least one operation was canceled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 *                           This KOS implementation never returns  this value, as it  includes
 *                           facilities to force-abort any async operation (in the same vain as
 *                           sending SIGKILL can also force-aborts a process)
 *                           NOTE: In other implementations, this return value outweighs
 *                                 `AIO_CANCELED'  and `AIO_ALLDONE' in face of multiple
 *                                 AIO operations.
 * @return: AIO_ALLDONE:     Operations had  already been  completed
 *                           (or canceled) before the call was made.
 * @return: -1: [errno=EBADF]  `fd' is not a valid file descriptor
 * @return: -1: [errno=EINVAL] `self != NULL' and the given `fd' differs from `self->aio_fildes' */
__CDECLARE(,int,__NOTHROW_NCX,aio_cancel64,(__fd_t __fildes, struct aiocb64 *__self),(__fildes,__self))
#endif /* ... */
#if defined(__CRT_HAVE_aio_suspend) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspend64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout),aio_suspend,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspend64) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CDECLARE(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspend64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout),(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspendt64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspend64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout),aio_suspendt64,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspend64t64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspend64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout),aio_suspend64t64,(__list,__nent,__rel_timeout))
#elif (defined(__CRT_HAVE_aio_suspend) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) || (defined(__CRT_HAVE_aio_suspendt64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_aio_suspend64t64) || (defined(__CRT_HAVE_aio_suspend) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_aio_suspend64)
#include <libc/local/aio/aio_suspend64.h>
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__NAMESPACE_LOCAL_USING_OR_IMPL(aio_suspend64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 2) int __NOTHROW_NCX(__LIBCCALL aio_suspend64)(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec const *__restrict __rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(aio_suspend64))(__list, __nent, __rel_timeout); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_aio_suspend) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __rel_timeout),aio_suspend,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspend64) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __rel_timeout),aio_suspend64,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspendt64) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CDECLARE(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __rel_timeout),(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspend64t64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspendt64,(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __rel_timeout),aio_suspend64t64,(__list,__nent,__rel_timeout))
#elif (defined(__CRT_HAVE_aio_suspend) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_aio_suspend64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
#include <libc/local/aio/aio_suspendt64.h>
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__NAMESPACE_LOCAL_USING_OR_IMPL(aio_suspendt64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 2) int __NOTHROW_NCX(__LIBCCALL aio_suspendt64)(struct aiocb const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(aio_suspendt64))(__list, __nent, __rel_timeout); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_aio_suspend) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspend64t64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __rel_timeout),aio_suspend,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspend64) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspend64t64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __rel_timeout),aio_suspend64,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspendt64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspend64t64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __rel_timeout),aio_suspendt64,(__list,__nent,__rel_timeout))
#elif defined(__CRT_HAVE_aio_suspend64t64)
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__CDECLARE(__ATTR_INS(1, 2),int,__NOTHROW_NCX,aio_suspend64t64,(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __rel_timeout),(__list,__nent,__rel_timeout))
#elif (defined(__CRT_HAVE_aio_suspend) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_aio_suspend64)
#include <libc/local/aio/aio_suspend64t64.h>
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
__NAMESPACE_LOCAL_USING_OR_IMPL(aio_suspend64t64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 2) int __NOTHROW_NCX(__LIBCCALL aio_suspend64t64)(struct aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent, struct timespec64 const *__restrict __rel_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(aio_suspend64t64))(__list, __nent, __rel_timeout); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_TIME64 */

#ifdef __USE_GNU
/* >> aio_init(3) */
__CDECLARE_VOID_OPT(__ATTR_IN(1),__NOTHROW_NCX,aio_init,(struct aioinit const *__init),(__init))
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_AIO_H */
