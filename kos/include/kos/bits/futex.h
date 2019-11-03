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
#ifndef _KOS_BITS_FUTEX_H
#define _KOS_BITS_FUTEX_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

/* KOS futex operations (for use with the lfutex() system
 * call, though can't be used with the futex() system call!). */
#define LFUTEX_WAKE               0x00000000 /* >> result = 0; while (val && sig_send(uaddr)) ++result; return result; */
#define LFUTEX_NOP                0x00000001 /* >> return 0; */
#define LFUTEX_GETFUTEX           0x00000002 /* [struct hop_openfd *val]
                                              * Return a handle for the underlying kernel futex object that
                                              * is automatically created for some given address, as doing so
                                              * becomes necessary by other LFUTEX_* operations.
                                              * The return value in this case is the `fd_t' of the newly allocated
                                              * handle, which may be influenced by `val' (s.a. the documentation of
                                              * `struct hop_openfd'). When `val' is `NULL', the behavior is the same
                                              * as though `val->of_mode' was set to `HOP_OPENFD_MODE_AUTO', meaning
                                              * that a file descriptor will be assigned automatically. */
#define LFUTEX_GETFUTEX_EXISTING  0x00000003 /* [struct hop_openfd *val]
                                              * Same as `LFUTEX_GETFUTEX', but don't create a futex where there is none already.
                                              * If no futex already exists, simply return `-ENOENT', and don't throw an error */
#define LFUTEX_WAIT               0x00000010 /* >> return waitfor(uaddr); // 0, E_INTERRUPT or -ETIMEDOUT */
#define LFUTEX_WAIT_LOCK          0x00000011 /* >> if ((*uaddr & LFUTEX_WAIT_LOCK_TIDMASK) == 0) {
                                              * >>     *uaddr = (*uaddr & ~LFUTEX_WAIT_LOCK_TIDMASK) | (val ? val : gettid());
                                              * >>     return 1;
                                              * >> } else {
                                              * >>     *uaddr |= LFUTEX_WAIT_LOCK_WAITERS;
                                              * >>     return waitfor(uaddr); // 0, E_INTERRUPT or -ETIMEDOUT
                                              * >> }
                                              */
#define LFUTEX_WAIT_WHILE         0x00000012 /* >> if (*uaddr == val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_UNTIL         0x00000013 /* >> if (*uaddr != val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_ABOVE   0x00000014 /* >> if ((unsigned)*uaddr > val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_BELOW   0x00000015 /* >> if ((unsigned)*uaddr < val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_BITMASK 0x00000016 /* >> if ((*uaddr & val) == val2) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_UNTIL_BITMASK 0x00000017 /* >> if ((*uaddr & val) != val2) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_CMPXCH  0x00000018 /* >> if (*uaddr == val) {
                                              * >>     *uaddr = val2;
                                              * >>     return waitfor(uaddr); // 0, E_INTERRUPT or -ETIMEDOUT
                                              * >> }
                                              * >> return 1; */
#define LFUTEX_WAIT_UNTIL_CMPXCH  0x00000019 /* >> if (*uaddr != val) {
                                              * >>     return waitfor(uaddr); // 0, E_INTERRUPT or -ETIMEDOUT
                                              * >> } else {
                                              * >>     *uaddr = val2;
                                              * >> }
                                              * >> return 1; */


/* Bit indicating a futexfd operation.
 * When or'd with one of the `LFUTEX_WAIT*' operations, the `lfutex()'
 * system call will then return a file descriptor that can be used
 * with `poll()' or `select()' in order to perform the same operation
 * that would have been done by `lfutex()', had this bit not been set.
 * For more information on this, see the section `lfutex() and select()'
 * that can be found in <kos/futex.h>
 * Note that when a futexfd object is shared between different processes,
 * the underlying futex that the associated thread will be waiting on will
 * remain the same, even when used within the same process after memory at
 * the location where the FD originally existed at has been unmapped.
 * However, futex wait operation that will read (and possibly write) memory
 * in order to determine if a wait really has to be performed will always do
 * so using the same virtual memory address with which the descriptor was
 * originally created, however will always do so using the currently set VM,
 * meaning that user-space application must either ensure that memory is
 * properly shared between applications, or simply only use this functionality
 * for futex objects within the same process.
 * If the user of this functionality requires that futex FD objects still
 * function properly, even in other processes where memory may potentially
 * be mapped differently that it is within the process that originally
 * created the FD object, then you may instead make use of `LFUTEX_MPFDBIT'
 * NOTE: The file descriptor used cannot be influenced directly, meaning that
 *       wishing make use of some particular descriptor will require the use
 *       of an additional call to some kernel function that can be used for
 *       duplicating file descriptors (e.g. `dup2()' or `HOP_HANDLE_REOPEN'). */
#define LFUTEX_FDBIT                0x00000100
#define LFUTEX_FDWAIT               (LFUTEX_FDBIT | LFUTEX_WAIT)
#define LFUTEX_FDWAIT_LOCK          (LFUTEX_FDBIT | LFUTEX_WAIT_LOCK)
#define LFUTEX_FDWAIT_WHILE         (LFUTEX_FDBIT | LFUTEX_WAIT_WHILE)
#define LFUTEX_FDWAIT_UNTIL         (LFUTEX_FDBIT | LFUTEX_WAIT_UNTIL)
#define LFUTEX_FDWAIT_WHILE_ABOVE   (LFUTEX_FDBIT | LFUTEX_WAIT_WHILE_ABOVE)
#define LFUTEX_FDWAIT_WHILE_BELOW   (LFUTEX_FDBIT | LFUTEX_WAIT_WHILE_BELOW)
#define LFUTEX_FDWAIT_WHILE_BITMASK (LFUTEX_FDBIT | LFUTEX_WAIT_WHILE_BITMASK)
#define LFUTEX_FDWAIT_UNTIL_BITMASK (LFUTEX_FDBIT | LFUTEX_WAIT_UNTIL_BITMASK)
#define LFUTEX_FDWAIT_WHILE_CMPXCH  (LFUTEX_FDBIT | LFUTEX_WAIT_WHILE_CMPXCH)
#define LFUTEX_FDWAIT_UNTIL_CMPXCH  (LFUTEX_FDBIT | LFUTEX_WAIT_UNTIL_CMPXCH)

/* This bit function very similar to `LFUTEX_FDBIT', however enables the use
 * of futex FD objects across multiple processes with different, and possibly
 * incompatible VMs, such that whatever operation is meant to be performed
 * when polling from the associated FD will still be able to happen.
 * This is essentially done by storing a reference to the `vm_datapart' that
 * contains the backing memory descriptor for the indicated address, and using
 * reads/writes to/from this `vm_datapart' to implement the checks associated
 * with the used wait operation.
 * WARNING: Any memory writes that are performed as part of one of the futex
 *          operations that can write to memory (LFUTEX_WAIT_(WHILE|UNTIL)_CMPXCH,
 *          and `LFUTEX_WAIT_LOCK'), will be made as through they where done by
 *          writing to a memory-mapped file, meaning that any such changes will
 *          not appear in memory images that aren't mapped with the `MAP_SHARED'
 *          flag set.
 *          As such, this flag should only ever be used to create futex FDs for
 *          futex objects in memory mappings that are mapped as `MAP_SHARED', since
 *          changes may otherwise not become visible to either the process that
 *          originally created the memory mapping, or the process that is using
 *          the FD to actually wait for something to happen. Note that access to
 *          the data part used by a MPFUTEXFD object can be gained through use
 *          of the `HOP_MPFUTEXFD_OPEN_DATAPART' hop() function.
 */
#define LFUTEX_MPFDBIT            0x00000200


#if __SIZEOF_POINTER__ >= 8
#define LFUTEX_WAIT_LOCK_TIDMASK  __UINT64_C(0x3fffffffffffffff) /* Mask for the TID. */
#define LFUTEX_WAIT_LOCK_WAITERS  __UINT64_C(0x4000000000000000) /* Flag: Set by the kernel before waiting for the futex. */
#define LFUTEX_WAIT_LOCK_OWNDIED  __UINT64_C(0x8000000000000000) /* Flag: Set by the kernel if a robust futex died. */
#else /* __SIZEOF_POINTER__ >= 8 */
#define LFUTEX_WAIT_LOCK_TIDMASK  __UINT32_C(0x3fffffff) /* Mask for the TID. */
#define LFUTEX_WAIT_LOCK_WAITERS  __UINT32_C(0x40000000) /* Flag: Set by the kernel before waiting for the futex. */
#define LFUTEX_WAIT_LOCK_OWNDIED  __UINT32_C(0x80000000) /* Flag: Set by the kernel if a robust futex died. */
#endif /* __SIZEOF_POINTER__ < 8 */

/* Check if the given futex command `x' uses the timeout argument. */
#define LFUTEX_USES_TIMEOUT(x) ((x) & 0x10)
#define LFUTEX_CMDMASK  0x00ffffff
#define LFUTEX_FLAGMASK 0xff000000

/* Flags for waiter futex functions. */
#define LFUTEX_WAIT_FLAG_TIMEOUT_SYSQTIME 0x00000000 /* Default: Timeouts are given as absolute positions of CPU quantum time (`CLOCK_PROCESS_CPUTIME_ID') */
#define LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE 0x40000000 /* The given timeout argument describes a timeout relative to the point when waiting starts */
#define LFUTEX_WAIT_FLAG_TIMEOUT_REALTIME 0x80000000 /* The given timeout argument is in absolute realtime (`CLOCK_REALTIME') */

#endif /* !_KOS_BITS_FUTEX_H */
