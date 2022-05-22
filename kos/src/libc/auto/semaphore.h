/* HASH CRC-32:0xf8251f09 */
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
#ifndef GUARD_LIBC_AUTO_SEMAPHORE_H
#define GUARD_LIBC_AUTO_SEMAPHORE_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <semaphore.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sem_init(3)
 * Initialize the given semaphore `self' to start out with `value' tickets
 * @param: self:     The semaphore to initialize
 * @param: pshared: When non-zero, `self'  may point to  a memory region  shared
 *                  with another process, such that both caller, and any process
 *                  the pointed-to memory is shared  with can safely operate  on
 *                  the same semaphore.
 * @param: value:   The initial # of tickets available.
 * @return: 0:      Success
 * @return: -1:     [errno=EINVAL] `value > SEM_VALUE_MAX'
 *                  HINT: Never returned `#if SEM_VALUE_MAX >= UINT_MAX'
 * @return: -1:     [errno=ENOSYS] `pshared != 0', but inter-process semaphores aren't supported
 *                  HINT: Never returned `#ifdef __ARCH_HAVE_INTERPROCESS_SEMAPHORES' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_sem_init)(sem_t *self, int pshared, unsigned int value);
/* >> sem_destroy(3)
 * Destroy a semaphore previously initialized by `sem_init(3)'
 * @return: 0: Success */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_sem_destroy)(sem_t *self);
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
INTDEF ATTR_IN(1) sem_t *NOTHROW_RPC_KOS(VLIBDCALL libd_sem_open)(char const *name, oflag_t oflags, ...);
/* >> sem_close(3)
 * Close a semaphore previously returned by `sem_open(3)'. But note the case
 * of opening the same semaphore more than once within the same process,  as
 * described by in `sem_open(3)' and by `__ARCH_HAVE_NON_UNIQUE_SEM_OPEN'->
 * @return: 0: Success */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_sem_close)(sem_t *self);
/* >> sem_unlink(3)
 * Unlink (delete) a named semaphore `name' that was
 * previously  created  by `sem_open(name, O_CREAT)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `name' contains no characters after the initial `/'
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(1) int NOTHROW_RPC_KOS(LIBDCALL libd_sem_unlink)(const char *name);
/* >> sem_wait(3)
 * Wait for a ticket to become  available to the given semaphore  `self'
 * Once a ticket has become available, consume it and return. Until that
 * point in time, keep on blocking.
 * @return: 0:  Success
 * @return: -1: [errno=EINTR] Interrupted. */
INTDEF ATTR_INOUT(1) int NOTHROW_RPC(LIBDCALL libd_sem_wait)(sem_t *self);
/* >> sem_timedwait(3), sem_timedwait64(3)
 * Wait  for a  ticket to become  available to the  given semaphore `self'
 * Once a ticket has become available, consume it and return. If no ticket
 * becomes  available until `abstime' has passed, return `errno=ETIMEDOUT'
 * @return: 0:  Success
 * @return: -1: [errno=EINTR]     Interrupted.
 * @return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available. */
INTDEF ATTR_IN(2) ATTR_INOUT(1) int NOTHROW_RPC(LIBDCALL libd_sem_timedwait)(sem_t *__restrict self, struct timespec const *__restrict abstime);
/* >> sem_timedwait(3), sem_timedwait64(3)
 * Wait  for a  ticket to become  available to the  given semaphore `self'
 * Once a ticket has become available, consume it and return. If no ticket
 * becomes  available until `abstime' has passed, return `errno=ETIMEDOUT'
 * @return: 0:  Success
 * @return: -1: [errno=EINTR]     Interrupted.
 * @return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available. */
INTDEF ATTR_IN(2) ATTR_INOUT(1) int NOTHROW_RPC(LIBDCALL libd_sem_timedwait64)(sem_t *__restrict self, struct timespec64 const *__restrict abstime);
/* >> sem_trywait(3)
 * Atomically check if at least 1 ticket is available for `self', and consume
 * one  if this is the case, or return with `errno=EAGAIN' if no tickets were
 * available at the time of the call.
 * @return: 0:  Success
 * @return: -1: [errno=EAGAIN] A ticket could not be acquired without blocking. */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_sem_trywait)(sem_t *self);
/* >> sem_post(3)
 * Post a ticket to the given semaphore `self', waking up to 1 other thread
 * that  may be waiting  for tickets to  become available before returning.
 * @return: 0:  Success
 * @return: -1: [errno=EOVERFLOW] The maximum number of tickets have already been posted. */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_sem_post)(sem_t *self);
/* >> sem_getvalue(3)
 * Capture a snapshot of how may tickets are available storing that number in `*sval'
 * @return: 0: Success */
INTDEF ATTR_INOUT(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_sem_getvalue)(sem_t *__restrict self, __STDC_INT_AS_UINT_T *__restrict sval);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SEMAPHORE_H */
