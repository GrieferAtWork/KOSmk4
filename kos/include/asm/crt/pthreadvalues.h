/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_CRT_PTHREADVALUES_H
#define _ASM_CRT_PTHREADVALUES_H 1

#include <__stdinc.h>

/* PThread constants */
#define __PTHREAD_CREATE_JOINABLE 0
#define __PTHREAD_CREATE_DETACHED 1

#define __PTHREAD_MUTEX_TIMED      0
#define __PTHREAD_MUTEX_RECURSIVE  1
#define __PTHREAD_MUTEX_ERRORCHECK 2
#define __PTHREAD_MUTEX_ADAPTIVE   3

#define __PTHREAD_MUTEX_STALLED 0
#define __PTHREAD_MUTEX_ROBUST  1

#define __PTHREAD_PRIO_NONE    0
#define __PTHREAD_PRIO_INHERIT 1
#define __PTHREAD_PRIO_PROTECT 2

#define __PTHREAD_RWLOCK_PREFER_READER              0
#define __PTHREAD_RWLOCK_PREFER_WRITER              1
#define __PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE 2

#define __PTHREAD_INHERIT_SCHED  0
#define __PTHREAD_EXPLICIT_SCHED 1

#define __PTHREAD_SCOPE_SYSTEM  0
#define __PTHREAD_SCOPE_PROCESS 1

#define __PTHREAD_PROCESS_PRIVATE 0
#define __PTHREAD_PROCESS_SHARED  1

#define __PTHREAD_CANCEL_ENABLE  0
#define __PTHREAD_CANCEL_DISABLE 1

#define __PTHREAD_CANCEL_DEFERRED     0
#define __PTHREAD_CANCEL_ASYNCHRONOUS 1

#define __PTHREAD_CANCELED (__CCAST(void *)-1)

#define __PTHREAD_ONCE_INIT 0

#define __PTHREAD_BARRIER_SERIAL_THREAD (-1)

#endif /* !_ASM_CRT_PTHREADVALUES_H */
