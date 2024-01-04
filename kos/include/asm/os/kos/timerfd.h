/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_KOS_TIMERFD_H
#define _ASM_OS_KOS_TIMERFD_H 1

#include <__stdinc.h>

/* Values for the `flags' argument of `timerfd_create(2)'. */
#define __TFD_NONBLOCK 0x000800 /* Set the `IO_NONBLOCK' flag for the returned */
#define __TFD_CLOEXEC  0x080000 /* Set the `IO_CLOEXEC' flag for the returned */
#ifdef __KOS__
#define __TFD_CLOFORK  0x100000 /* Set the `IO_CLOFORK' flag for the returned */
#endif /* __KOS__ */

/* Values for the `flags' argument of `timerfd_settime(2)'. */
#define __TFD_TIMER_ABSTIME       0x000001 /* The given timestamp is absolute. */
#define __TFD_TIMER_CANCEL_ON_SET 0x000002 /* ??? */

#endif /* !_ASM_OS_KOS_TIMERFD_H */
