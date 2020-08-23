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
#ifndef _I386_KOS_BITS_CRT_PTHREADTYPES_H
#define _I386_KOS_BITS_CRT_PTHREADTYPES_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/crt/pthreadtypesizes.h>

__SYSDECL_BEGIN

#ifdef __CC__
typedef __TYPEFOR_UINTIB(__SIZEOF_PTHREAD_T) __pthread_t;
typedef __TYPEFOR_UINTIB(__SIZEOF_PTHREAD_KEY_T) __pthread_key_t;
typedef __TYPEFOR_INTIB(__SIZEOF_PTHREAD_ONCE_T) __pthread_once_t;

typedef union __pthread_attr {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_ATTR_T];
	__INTPTR_TYPE__ __align;
} __pthread_attr_t;

#ifdef __x86_64__
typedef struct __pthread_internal_list {
	struct __pthread_internal_list *__prev;
	struct __pthread_internal_list *__next;
} __pthread_list_t;
#else /* __x86_64__ */
typedef struct __pthread_internal_slist {
	struct __pthread_internal_slist *__next;
} __pthread_slist_t;
#endif /* !__x86_64__ */


typedef union __pthread_mutex {
#undef __spins
#undef __elision
	struct __pthread_mutex_s {
		__INT32_TYPE__ __lock;
		__UINT32_TYPE__ __count;
		__INT32_TYPE__ __owner;
#ifdef __x86_64__
		__UINT32_TYPE__ __nusers;
#endif /* __x86_64__ */
		/* KIND must stay at this position in the structure to maintain binary compatibility.  */
		__INT32_TYPE__ __kind;
#ifdef __x86_64__
		__INT16_TYPE__ __spins;
		__INT16_TYPE__ __elision;
		__pthread_list_t __list;
#define __PTHREAD_MUTEX_HAVE_PREV  1
#define __PTHREAD_SPINS            0, 0
#else /* __x86_64__ */
		__UINT32_TYPE__ __nusers;
		union {
			struct {
				__INT16_TYPE__ __espins;
				__INT16_TYPE__ __elision;
#define __PTHREAD_SPINS { 0, 0 }
			}
#ifdef __COMPILER_HAVE_TRANSPARENT_STRUCT
			;
#else /* __COMPILER_HAVE_TRANSPARENT_STRUCT */
#define __spins   __elision_data.__espins
#define __elision __elision_data.__elision
			__elision_data;
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
			__pthread_slist_t __list;
		};
#endif /* !__x86_64__ */
	} __data;
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_MUTEX_T];
	__INTPTR_TYPE__ __align;
} __pthread_mutex_t;

typedef union __pthread_mutexattr {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
	__INT32_TYPE__ __align;
} __pthread_mutexattr_t;


typedef union __pthread_cond {
	struct {
		__INT32_TYPE__  __lock;
		__UINT32_TYPE__ __futex;
		__UINT64_TYPE__ __total_seq;
		__UINT64_TYPE__ __wakeup_seq;
		__UINT64_TYPE__ __woken_seq;
		void           *__mutex;
		__UINT32_TYPE__ __nwaiters;
		__UINT32_TYPE__ __broadcast_seq;
	} __data;
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_COND_T];
	__INT64_TYPE__ __align;
} __pthread_cond_t;

typedef union __pthread_condattr {
	__BYTE_TYPE__ __size[__SIZEOF_PTHREAD_CONDATTR_T];
	__INT32_TYPE__ __align;
} __pthread_condattr_t;

typedef union __pthread_rwlock {
#ifdef __x86_64__
	struct {
		__INT32_TYPE__ __lock;
		__UINT32_TYPE__ __nr_readers;
		__UINT32_TYPE__ __readers_wakeup;
		__UINT32_TYPE__ __writer_wakeup;
		__UINT32_TYPE__ __nr_readers_queued;
		__UINT32_TYPE__ __nr_writers_queued;
		__INT32_TYPE__ __writer;
		__INT32_TYPE__ __shared;
		__INT8_TYPE__ __rwelision;
#ifdef  __ILP32__
		__UINT8_TYPE__ __pad1[3];
#define __PTHREAD_RWLOCK_ELISION_EXTRA 0,{0,0,0}
#else /* __ILP32__ */
		__UINT8_TYPE__ __pad1[7];
#define __PTHREAD_RWLOCK_ELISION_EXTRA 0,{0,0,0,0,0,0,0}
#endif /* !__ILP32__ */
		__UINTPTR_TYPE__ __pad2;
		__UINT32_TYPE__ __flags;
#define __PTHREAD_RWLOCK_INT_FLAGS_SHARED    1
	} __data;
#else /* __x86_64__ */
	struct {
		__INT32_TYPE__  __lock;
		__UINT32_TYPE__ __nr_readers;
		__UINT32_TYPE__ __readers_wakeup;
		__UINT32_TYPE__ __writer_wakeup;
		__UINT32_TYPE__ __nr_readers_queued;
		__UINT32_TYPE__ __nr_writers_queued;
		__UINT8_TYPE__  __flags;
		__UINT8_TYPE__  __shared;
		__INT8_TYPE__   __rwelision;
#define __PTHREAD_RWLOCK_ELISION_EXTRA 0
		__UINT8_TYPE__  __pad2;
		__INT32_TYPE__  __writer;
	} __data;
#endif /* !__x86_64__ */
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

#ifndef __x86_64__
#define __cleanup_fct_attribute __attribute__((__regparm__(1)))
#endif /* !__x86_64__ */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BITS_CRT_PTHREADTYPES_H */
