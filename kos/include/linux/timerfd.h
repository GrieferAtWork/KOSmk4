/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux (/usr/include/linux/timerfd.h) */
#ifndef _LINUX_TIMERFD_H
#define _LINUX_TIMERFD_H 1

#include <__stdinc.h>

#include <asm/os/timerfd.h>
#include <linux/fcntl.h>
#include <linux/ioctl.h>
#include <linux/types.h>

#if !defined(TFD_TIMER_ABSTIME) && defined(__TFD_TIMER_ABSTIME)
#define TFD_TIMER_ABSTIME __TFD_TIMER_ABSTIME /* The given timestamp is absolute. */
#endif /* !TFD_TIMER_ABSTIME && __TFD_TIMER_ABSTIME */
#if !defined(TFD_TIMER_CANCEL_ON_SET) && defined(__TFD_TIMER_CANCEL_ON_SET)
#define TFD_TIMER_CANCEL_ON_SET __TFD_TIMER_CANCEL_ON_SET /* ??? */
#endif /* !TFD_TIMER_CANCEL_ON_SET && __TFD_TIMER_CANCEL_ON_SET */
#if !defined(TFD_NONBLOCK) && defined(__TFD_NONBLOCK)
#define TFD_NONBLOCK __TFD_NONBLOCK /* Set the `IO_NONBLOCK' flag for the returned */
#endif /* !TFD_NONBLOCK && __TFD_NONBLOCK */
#if !defined(TFD_CLOEXEC) && defined(__TFD_CLOEXEC)
#define TFD_CLOEXEC __TFD_CLOEXEC /* Set the `IO_CLOEXEC' flag for the returned */
#endif /* !TFD_CLOEXEC && __TFD_CLOEXEC */

#define TFD_IOC_SET_TICKS _IOW('T', 0, __u64) /* Explicitly set the # of extra overrun ticks. */

#endif /* !_LINUX_TIMERFD_H */
