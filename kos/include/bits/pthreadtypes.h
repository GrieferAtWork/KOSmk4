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
/* (#) Portability: GNU C Library (/bits/pthreadtypes.h) */
#ifndef _BITS_PTHREADTYPES_H
#define _BITS_PTHREADTYPES_H 1

/* NOTE: This file must _always_ be kept for Glibc compatibility! */

#include <__stdinc.h>
#include <features.h>

#include <bits/crt/pthreadtypes.h>
#include <bits/crt/pthreadtypesizes.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __pthread_t_defined
#define __pthread_t_defined
typedef __pthread_t pthread_t;
#endif /* !__pthread_t_defined */

#ifndef __pthread_attr_t_defined
#define __pthread_attr_t_defined
typedef __pthread_attr_t pthread_attr_t;
#endif /* !__pthread_attr_t_defined */

#ifndef __pthread_mutex_t_defined
#define __pthread_mutex_t_defined
typedef __pthread_mutex_t pthread_mutex_t;
#endif /* !__pthread_mutex_t_defined */

#ifndef __pthread_mutexattr_t_defined
#define __pthread_mutexattr_t_defined
typedef __pthread_mutexattr_t pthread_mutexattr_t;
#endif /* !__pthread_mutexattr_t_defined */

#ifndef __pthread_cond_t_defined
#define __pthread_cond_t_defined
typedef __pthread_cond_t pthread_cond_t;
#endif /* !__pthread_cond_t_defined */

#ifndef __pthread_condattr_t_defined
#define __pthread_condattr_t_defined
typedef __pthread_condattr_t pthread_condattr_t;
#endif /* !__pthread_condattr_t_defined */

#ifndef __pthread_key_t_defined
#define __pthread_key_t_defined
typedef __pthread_key_t pthread_key_t;
#endif /* !__pthread_key_t_defined */

#ifndef __pthread_once_t_defined
#define __pthread_once_t_defined
typedef __pthread_once_t pthread_once_t;
#endif /* !__pthread_once_t_defined */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#ifndef __pthread_rwlock_t_defined
#define __pthread_rwlock_t_defined
typedef __pthread_rwlock_t pthread_rwlock_t;
#endif /* !__pthread_rwlock_t_defined */
#ifndef __pthread_rwlockattr_t_defined
#define __pthread_rwlockattr_t_defined
typedef __pthread_rwlockattr_t pthread_rwlockattr_t;
#endif /* !__pthread_rwlockattr_t_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */


#ifdef __USE_XOPEN2K
#ifndef __pthread_spinlock_t_defined
#define __pthread_spinlock_t_defined
typedef __pthread_spinlock_t pthread_spinlock_t;
#endif /* !__pthread_spinlock_t_defined */
#ifndef __pthread_barrier_t_defined
#define __pthread_barrier_t_defined
typedef __pthread_barrier_t pthread_barrier_t;
#endif /* !__pthread_barrier_t_defined */
#ifndef __pthread_barrierattr_t_defined
#define __pthread_barrierattr_t_defined
typedef __pthread_barrierattr_t pthread_barrierattr_t;
#endif /* !__pthread_barrierattr_t_defined */
#endif /* __USE_XOPEN2K */

#ifndef __cleanup_fct_attribute
#define __cleanup_fct_attribute /* nothing */
#endif /* !__cleanup_fct_attribute */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_PTHREADTYPES_H */
