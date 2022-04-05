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
#ifndef _KOS_ASM_FUTEX_H
#define _KOS_ASM_FUTEX_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

/* KOS futex operations (for use with the `lfutex(2)' system
 * call, iow: can't be used with the futex(2) system call!). */
#define LFUTEX_WAKE                __UINT32_C(0x00000000) /* >> result = 0; while (val && sig_send(uaddr)) ++result; return result; */
#define LFUTEX_EXPREND             __UINT32_C(0x00000000) /* Expression list terminator for `lfutexexpr(2)' */
#define LFUTEX_NOP                 __UINT32_C(0x00000001) /* >> return 0; // Only valid in `lfutexexpr(2)' */
#define LFUTEX_WAKEMASK            __UINT32_C(0x00000001) /* Same as `LFUTEX_WAKE', but clear/set  certain bits once there are  no
                                                           * more threads to wake up, before broadcasting all remaining threads to
                                                           * ensure that futex bits are in a consistent state.
                                                           * Mainly intended to be used like this (allowing something like `sem_post()'
                                                           * to be implemented without the need of a system call whenever there  aren't
                                                           * any waiting threads):
                                                           * >> if (BIT_SET(0x80000000))
                                                           * >>     wakemask(timeout: ~0x80000000, val2: 0);
                                                           * Behavior:
                                                           * >> result = 0;
                                                           * >> while (val && sig_send(uaddr))
                                                           * >>     ++result, --val;
                                                           * >> if (result < val && val != 0) {
                                                           * >>     *uaddr = (*uaddr & (lfutex_t)timeout) | val2;
                                                           * >>     result += sig_broadcast(uaddr);
                                                           * >>     if (result > val)
                                                           * >>         result = val;
                                                           * >> }
                                                           * >> return result; */
#define LFUTEX_WAIT_WHILE          __UINT32_C(0x00000010) /* >> if (*uaddr == val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_UNTIL          __UINT32_C(0x00000011) /* >> if (*uaddr != val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_ABOVE    __UINT32_C(0x00000012) /* >> if ((unsigned)*uaddr > val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_BELOW    __UINT32_C(0x00000013) /* >> if ((unsigned)*uaddr < val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_BITMASK  __UINT32_C(0x00000014) /* >> if ((*uaddr & val) == val2) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_UNTIL_BITMASK  __UINT32_C(0x00000015) /* >> if ((*uaddr & val) != val2) return waitfor(uaddr); return 1; */

/* Wait for a variable-length buffer to change value.
 * NOTE: In  the case of lfutexexpr(), `val' is interpreted
 *       as an offset to the object base, rather than as an
 *       absolute address! */
#define LFUTEX_WAIT_WHILE_EX       __UINT32_C(0x00000018) /* >> if (memcmp(uaddr, val, val2) == 0) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_UNTIL_EX       __UINT32_C(0x00000019) /* >> if (memcmp(uaddr, val, val2) != 0) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_ABOVE_EX __UINT32_C(0x0000001a) /* >> if (memcmp(uaddr, val, val2) >  0) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_BELOW_EX __UINT32_C(0x0000001b) /* >> if (memcmp(uaddr, val, val2) <  0) return waitfor(uaddr); return 1; */



/* Bit indicating a futexfd operation.
 * These functions cannot be used when the memory pointed to by the  futex
 * is backed by VIO, as the act of polling of a condition to be applicable
 * in the context of memory pointed-to by a futex must be non-blocking  as
 * far as that is possible.
 *
 * - The returned handle is of type `HANDLE_TYPE_FUTEXFD'
 * - This flag may also appear in `lfutexexpr(2)::flags', in which case that
 *   system call returns a futexfd object that  can be used to poll for  the
 *   specified expression(s).
 * - When used with `lfutex(2)', only a singular expression can be specified.
 * - A futexfd object remembers:
 *   - `WEAK REF struct mman *': A weak reference to the creating thread's mman
 *   - `REF struct mfutex *':    Then futex object on which to wait
 *   - `exprv':                  Everything relating to the expression being checked.
 *                               Note that a full copy of the caller-given `exprv' is
 *                               taken, meaning that  you can immediately  deallocate
 *                               the storage for the exprv of the initial system call
 *                               after it returns!
 *                               s.a. `LFUTEXFD_DEFAULT_MAXEXPR'
 * - Whenever the fd is polled, the mnode->mpart mapped at that address is tested.
 * - Poll will indicate:
 *   - POLLRDHUP | POLLHUP | POLLPRI:
 *     - The mman has been destroyed
 *     - No mnode or mpart exist at the specified address
 *     - The mpart is backed by VIO
 *   - POLLPRI:
 *     - The specified expression is true
 *   - 0:
 *     - The specified expression is false
 */
#define LFUTEX_FDBIT 0x00000100


/* Default value for the max # of expressions in `lfutexexpr()' when using `LFUTEX_FDBIT'
 * - The limit can be overwritten system-wide by use of "/proc/kos/futexfd-maxexpr"
 * - A thread with `CAP_SYS_RESOURCE' is always allowed to exceed this limit. */
#define LFUTEXFD_DEFAULT_MAXEXPR 32


/* Check if the given futex command `x' uses the timeout argument. */
#define LFUTEX_USES_TIMEOUT(x) ((x) & 0x10)
#define LFUTEX_CMDMASK         __UINT32_C(0x00ffffff) /* Mask for lfutex(2) command code */
#define LFUTEX_FLAGMASK        __UINT32_C(0xff000000) /* Mask for lfutex(2) command flags */

/* Flags for waiter futex functions. */
#define LFUTEX_WAIT_FLAG_TIMEOUT_ABSOLUTE __UINT32_C(0x00000000) /* Default: Timeouts are given as absolute positions of CPU quantum time (`CLOCK_PROCESS_CPUTIME_ID') */
#define LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE __UINT32_C(0x40000000) /* The given timeout argument describes a timeout relative to the point when waiting starts */
#define LFUTEX_WAIT_FLAG_TIMEOUT_REALTIME __UINT32_C(0x80000000) /* The given timeout argument is in absolute realtime (`CLOCK_REALTIME') */
#define LFUTEX_WAIT_FLAG_TIMEOUT_FORPOLL  __UINT32_C(0x20000000) /* Connect to signals for polling. (s.a. `task_connect_for_poll()') */

#endif /* !_KOS_ASM_FUTEX_H */
