/* HASH CRC-32:0x8086990f */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/semaphore.h) */
/* (#) Portability: FreeBSD       (/include/semaphore.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/semaphore.h) */
/* (#) Portability: MinGW         (/mingw-w64-libraries/winpthreads/include/semaphore.h) */
/* (#) Portability: NetBSD        (/include/semaphore.h) */
/* (#) Portability: OpenBSD       (/include/semaphore.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/semaphore.h) */
/* (#) Portability: diet libc     (/include/semaphore.h) */
/* (#) Portability: musl libc     (/include/semaphore.h) */
/* (#) Portability: uClibc        (/libpthread/nptl/semaphore.h) */
#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/crt/semaphore.h>  /* __ARCH_HAVE_INTERPROCESS_SEMAPHORES, __ARCH_HAVE_NON_UNIQUE_SEM_OPEN */
#include <bits/crt/semaphore.h> /* __sem_t */
#include <bits/types.h>
#ifdef __USE_XOPEN2K
#include <bits/os/timespec.h>
#endif /* __USE_XOPEN2K */

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

#if !defined(SEM_FAILED) && defined(__SEM_FAILED)
#define SEM_FAILED (__CCAST(sem_t *)__SEM_FAILED) /* Returned by `sem_open(3)' upon failure. */
#endif /* !SEM_FAILED && __SEM_FAILED */

#ifdef __CC__
__SYSDECL_BEGIN

typedef __sem_t sem_t;

/* >> sem_init(3)
 * Initialize the given semaphore `sem' to start out with `value' tickets
 * @param: sem:     The semaphore to initialize
 * @param: pshared: When  non-zero, `sem'  may point  to a  memory region shared
 *                  with another process, such that both caller, and any process
 *                  the pointed-to memory is shared  with can safely operate  on
 *                  the same semaphore.
 * @param: value:   The initial # of tickets available.
 * @return: 0:      Success
 * @return: -1:     [errno=EINVAL] `value > SEM_VALUE_MAX'
 *                  HINT: Never returned `#if SEM_VALUE_MAX >= UINT_MAX'
 * @return: -1:     [errno=ENOSYS] `pshared != 0', but inter-process semaphores aren't supported
 *                  HINT: Never returned `#ifdef __ARCH_HAVE_INTERPROCESS_SEMAPHORES' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sem_init,(sem_t *__sem, int __pshared, unsigned int __value),(__sem,__pshared,__value))
/* >> sem_destroy(3)
 * Destroy a semaphore previously initialized by `sem_init(3)'
 * @return: 0: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sem_destroy,(sem_t *__sem),(__sem))
#ifdef __CRT_HAVE_sem_open
/* >> sem_open(3)
 * Open a named semaphore `name', which must be string that starts with `/'
 * NOTE: When called multiple times with identical strings for  `name',
 *       the behavior of this function differs between implementations:
 *       #ifdef __ARCH_HAVE_NON_UNIQUE_SEM_OPEN
 *          The  returned pointer is  allowed to be  unique and different from
 *          any previously returned semaphore, but the backing physical memory
 *          will be shared with other semaphores with the same name.
 *       #else // __ARCH_HAVE_NON_UNIQUE_SEM_OPEN
 *          The returned pointer  may be identical  to a pointer  previously
 *          returned for the same semaphore. In this case, `sem_close()' may
 *          only have to be  called once to close  all open handles for  the
 *          semaphore
 *       #endif // !__ARCH_HAVE_NON_UNIQUE_SEM_OPEN
 * @param: oflags:      Set of `0 | O_CREAT | O_EXCL' (When `O_CREAT' is given, this functions
 *                      takes 2  additional arguments  `..., mode_t mode, unsigned int value')
 * @return: * :         A pointer to the opened semaphore, which must be closed by `sem_close(3)'
 * @return: SEM_FAILED: [errno=EINVAL] The given `name' contains no characters after the initial `/'
 * @return: SEM_FAILED: Error (s.a. `errno') */
__LIBC __ATTR_NONNULL((1)) sem_t *__NOTHROW_RPC_KOS(__VLIBCCALL sem_open)(char const *__name, __oflag_t __oflags, ...) __CASMNAME_SAME("sem_open");
#endif /* __CRT_HAVE_sem_open */
/* >> sem_close(3)
 * Close a semaphore previously returned by `sem_open(3)'. But note the case
 * of opening the same semaphore more than once within the same process,  as
 * described by in `sem_open(3)' and by `__ARCH_HAVE_NON_UNIQUE_SEM_OPEN'->
 * @return: 0: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sem_close,(sem_t *__sem),(__sem))
/* >> sem_unlink(3)
 * Unlink (delete) a named semaphore `name' that was
 * previously  created  by `sem_open(name, O_CREAT)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `name' contains no characters after the initial `/'
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_KOS,sem_unlink,(const char *__name),(__name))
/* >> sem_wait(3)
 * Wait  for a ticket  to become available to  the given semaphore `sem'
 * Once a ticket has become available, consume it and return. Until that
 * point in time, keep on blocking.
 * @return: 0:  Success
 * @return: -1: [errno=EINTR] Interrupted. */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sem_wait,(sem_t *__sem),(__sem))

#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_sem_timedwait) && !defined(__USE_TIME_BITS64)
/* >> sem_timedwait(3)
 * Wait for a  ticket to  become available  to the  given semaphore  `sem'
 * Once a ticket has become available, consume it and return. If no ticket
 * becomes  available until `abstime' has passed, return `errno=ETIMEDOUT'
 * @return: 0:  Success
 * @return: -1: [errno=EINTR]     Interrupted.
 * @return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available. */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sem_timedwait,(sem_t *__restrict __sem, struct timespec const *__restrict __abstime),(__sem,__abstime))
#elif defined(__CRT_HAVE_sem_timedwait64) && defined(__USE_TIME_BITS64)
/* >> sem_timedwait(3)
 * Wait for a  ticket to  become available  to the  given semaphore  `sem'
 * Once a ticket has become available, consume it and return. If no ticket
 * becomes  available until `abstime' has passed, return `errno=ETIMEDOUT'
 * @return: 0:  Success
 * @return: -1: [errno=EINTR]     Interrupted.
 * @return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available. */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sem_timedwait,(sem_t *__restrict __sem, struct timespec const *__restrict __abstime),sem_timedwait64,(__sem,__abstime))
#elif defined(__CRT_HAVE_sem_timedwait64) || defined(__CRT_HAVE_sem_timedwait)
#include <libc/local/semaphore/sem_timedwait.h>
/* >> sem_timedwait(3)
 * Wait for a  ticket to  become available  to the  given semaphore  `sem'
 * Once a ticket has become available, consume it and return. If no ticket
 * becomes  available until `abstime' has passed, return `errno=ETIMEDOUT'
 * @return: 0:  Success
 * @return: -1: [errno=EINTR]     Interrupted.
 * @return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sem_timedwait, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL sem_timedwait)(sem_t *__restrict __sem, struct timespec const *__restrict __abstime) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sem_timedwait)(__sem, __abstime); })
#endif /* ... */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_sem_timedwait64
/* >> sem_timedwait(3)
 * Wait for a  ticket to  become available  to the  given semaphore  `sem'
 * Once a ticket has become available, consume it and return. If no ticket
 * becomes  available until `abstime' has passed, return `errno=ETIMEDOUT'
 * @return: 0:  Success
 * @return: -1: [errno=EINTR]     Interrupted.
 * @return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available. */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sem_timedwait64,(sem_t *__restrict __sem, struct timespec64 const *__restrict __abstime),(__sem,__abstime))
#elif defined(__CRT_HAVE_sem_timedwait) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> sem_timedwait(3)
 * Wait for a  ticket to  become available  to the  given semaphore  `sem'
 * Once a ticket has become available, consume it and return. If no ticket
 * becomes  available until `abstime' has passed, return `errno=ETIMEDOUT'
 * @return: 0:  Success
 * @return: -1: [errno=EINTR]     Interrupted.
 * @return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available. */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sem_timedwait64,(sem_t *__restrict __sem, struct timespec64 const *__restrict __abstime),sem_timedwait,(__sem,__abstime))
#elif defined(__CRT_HAVE_sem_timedwait)
#include <libc/local/semaphore/sem_timedwait64.h>
/* >> sem_timedwait(3)
 * Wait for a  ticket to  become available  to the  given semaphore  `sem'
 * Once a ticket has become available, consume it and return. If no ticket
 * becomes  available until `abstime' has passed, return `errno=ETIMEDOUT'
 * @return: 0:  Success
 * @return: -1: [errno=EINTR]     Interrupted.
 * @return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available. */
__NAMESPACE_LOCAL_USING_OR_IMPL(sem_timedwait64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL sem_timedwait64)(sem_t *__restrict __sem, struct timespec64 const *__restrict __abstime) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sem_timedwait64)(__sem, __abstime); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */
/* >> sem_trywait(3)
 * Atomically check if at least 1 ticket is available for `sem', and consume
 * one if this is the case, or return with `errno=EAGAIN' if no tickets were
 * available at the time of the call.
 * @return: 0:  Success
 * @return: -1: [errno=EAGAIN] A ticket could not be acquired without blocking. */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sem_trywait,(sem_t *__sem),(__sem))
/* >> sem_post(3)
 * Post a ticket to the given semaphore `sem', waking up to 1 other thread
 * that may be waiting for  tickets to become available before  returning.
 * @return: 0:  Success
 * @return: -1: [errno=EOVERFLOW] The maximum number of tickets have already been posted. */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sem_post,(sem_t *__sem),(__sem))
/* >> sem_getvalue(3)
 * Capture a snapshot of how may tickets are available storing that number in `*sval'
 * @return: 0: Success */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,sem_getvalue,(sem_t *__restrict __sem, __STDC_INT_AS_UINT_T *__restrict __sval),(__sem,__sval))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SEMAPHORE_H */
