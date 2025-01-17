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
#ifndef _ASM_OS_KOS_SIGEVENT_H
#define _ASM_OS_KOS_SIGEVENT_H 1

#include <__crt.h> /* __CRT_KOS */
#include <__stdinc.h>

/* `sigev_notify' values. */
#define __SIGEV_SIGNAL    0 /* Notify via signal. */
#define __SIGEV_NONE      1 /* Other notification: meaningless. */
#define __SIGEV_THREAD    2 /* Deliver via thread creation. */
#define __SIGEV_THREAD_ID 4 /* Send signal to specific thread. */
#ifdef __CRT_KOS
#define __SIGEV_INLINE_THREAD 16 /* KOS-only: Same as `SIGEV_THREAD', but try not to actually spawn a thread, though
                                  * this event kind  is allowed to  be implemented as  an alias for  `SIGEV_THREAD'.
                                  * Semantically, the following rules have to be followed by  `SIGEV_INLINE_THREAD':
                                  *   - You mustn't call `pthread_exit(3)'
                                  * In the context of AIO completion events (s.a. <aio.h>), the following applies:
                                  *   - If triggered as a result of `aio_cancel(3)', the call to `aio_cancel()' may
                                  *     not return until your callback has also returned (because your callback may
                                  *     have hi-jacked that thread)
                                  * NOTE: You are allowed to make modifications to `errno', so don't worry about it.
                                  * NOTE: Depending on context, this may be identical to `SIGEV_THREAD'!
                                  *
                                  * Generally speaking,  you should  act like  your callback  is invoked  as though  it
                                  * were a signal handler (note that it may actually be invoked from a signal handler),
                                  * meaning that you should only call NOBLOCK and re-entrance-safe functions. */
#endif /* __CRT_KOS */

#endif /* !_ASM_OS_KOS_SIGEVENT_H */
