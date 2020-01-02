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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_PTHREADTYPES_H
#define _BITS_PTHREADTYPES_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <bits/pthreadtypesizes.h>

__SYSDECL_BEGIN

#ifdef __CC__
typedef __TYPEFOR_UINTIB(__SIZEOF_PTHREAD_T) __pthread_t;
typedef __TYPEFOR_UINTIB(__SIZEOF_PTHREAD_KEY_T) __pthread_key_t;
typedef __TYPEFOR_INTIB(__SIZEOF_PTHREAD_ONCE_T) __pthread_once_t;

typedef union __pthread_attr {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_ATTR_T];
	__INTPTR_TYPE__ __align;
} __pthread_attr_t;

typedef union __pthread_mutex {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_MUTEX_T];
	__INTPTR_TYPE__ __align;
} __pthread_mutex_t;

typedef union __pthread_mutexattr {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
	__INT32_TYPE__ __align;
} __pthread_mutexattr_t;

typedef union __pthread_cond {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_COND_T];
	__INT64_TYPE__ __align;
} __pthread_cond_t;

typedef union __pthread_condattr {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_CONDATTR_T];
	__INT32_TYPE__ __align;
} __pthread_condattr_t;

typedef union __pthread_rwlock {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_RWLOCK_T];
	__INTPTR_TYPE__ __align;
} __pthread_rwlock_t;

typedef union __pthread_rwlockattr {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_RWLOCKATTR_T];
	__INTPTR_TYPE__ __align;
} __pthread_rwlockattr_t;

typedef int volatile __pthread_spinlock_t;

typedef union __pthread_barrier {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_BARRIER_T];
	__INTPTR_TYPE__ __align;
} __pthread_barrier_t;

typedef union __pthread_barrierattr {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_BARRIERATTR_T];
	__INT32_TYPE__ __align;
} __pthread_barrierattr_t;
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_PTHREADTYPES_H */
