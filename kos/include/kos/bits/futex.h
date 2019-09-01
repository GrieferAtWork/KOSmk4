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

/* KOS futex operations (for use with the lfutex() system
 * call, though can't be used with the futex() system call!). */
#define LFUTEX_WAKE               0x00000000 /* >> result = 0; while (val && sig_send(uaddr)) ++result; return result; */
#define LFUTEX_NOP                0x00000001 /* >> return 0; */
#define LFUTEX_WAIT               0x00000010 /* >> return waitfor(uaddr); */
#define LFUTEX_WAIT_LOCK          0x00000011 /* >> if ((*uaddr & LFUTEX_WAIT_LOCK_TIDMASK) == 0) {
                                              * >>     *uaddr = (*uaddr & ~LFUTEX_WAIT_LOCK_TIDMASK) | (val ? val : gettid());
                                              * >>     return 1;
                                              * >> } else {
                                              * >>     *uaddr |= LFUTEX_WAIT_LOCK_WAITERS;
                                              * >>     return waitfor(uaddr); // 0, -EINTR or -ETIMEDOUT
                                              * >> }
                                              */
#define LFUTEX_WAIT_WHILE         0x00000012 /* >> if (*uaddr == val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_UNTIL         0x00000013 /* >> if (*uaddr != val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_ABOVE   0x00000014 /* >> if ((unsigned)*uaddr < val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_BELOW   0x00000015 /* >> if ((unsigned)*uaddr > val) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_BITMASK 0x00000016 /* >> if ((*uaddr & val) == val2) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_UNTIL_BITMASK 0x00000017 /* >> if ((*uaddr & val) != val2) return waitfor(uaddr); return 1; */
#define LFUTEX_WAIT_WHILE_CMPXCH  0x00000018 /* >> if (*uaddr == val) {
                                              * >>     *uaddr = val2;
                                              * >>     return waitfor(uaddr); // 0, -EINTR or -ETIMEDOUT
                                              * >> }
                                              * >> return 1; */
#define LFUTEX_WAIT_UNTIL_CMPXCH  0x00000019 /* >> if (*uaddr != val) {
                                              * >>     return waitfor(uaddr); // 0, -EINTR or -ETIMEDOUT
                                              * >> } else {
                                              * >>     *uaddr = val2;
                                              * >> }
                                              * >> return 1; */
#define LFUTEX_WAIT_LOCK_TIDMASK  0x3fffffff /* Mask for the TID. */
#define LFUTEX_WAIT_LOCK_WAITERS  0x40000000 /* Flag: Set by the kernel before waiting for the futex. */
#define LFUTEX_WAIT_LOCK_OWNDIED  0x80000000 /* Flag: Set by the kernel if a robust futex died. */

/* Check if the given futex command `x' uses the timeout argument. */
#define LFUTEX_USES_TIMEOUT(x) ((x) & 0x10)

/* Flags for waiter futex functions. */
#define LFUTEX_WAIT_FLAG_TIMEOUT_SYSQTIME 0x00000000 /* Default: Timeouts are given as absolute positions of CPU quantum time (`CLOCK_PROCESS_CPUTIME_ID') */
#define LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE 0x40000000 /* The given timeout argument describes a timeout relative to the point when waiting starts  */
#define LFUTEX_WAIT_FLAG_TIMEOUT_REALTIME 0x80000000 /* The given timeout argument is in absolute realtime (`CLOCK_REALTIME') */

#endif /* !_KOS_BITS_FUTEX_H */
