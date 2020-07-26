/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_SIGEVENT_H
#define _ASM_SIGEVENT_H 1

#include <__crt.h>
#include <__stdinc.h>

/* `sigev_notify' values. */
#if defined(__linux__) || defined(__KOS__)

#define __SIGEV_SIGNAL    0 /* Notify via signal. */
#define __SIGEV_NONE      1 /* Other notification: meaningless. */
#define __SIGEV_THREAD    2 /* Deliver via thread creation. */
#define __SIGEV_THREAD_ID 4 /* Send signal to specific thread. */

#elif defined(__CRT_CYG)

#define __SIGEV_SIGNAL 0 /* Notify via signal. */
#define __SIGEV_NONE   1 /* Other notification: meaningless. */
#define __SIGEV_THREAD 2 /* Deliver via thread creation. */

#endif /* ... */



#endif /* !_ASM_SIGEVENT_H */
