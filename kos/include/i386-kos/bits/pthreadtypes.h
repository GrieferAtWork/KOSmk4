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
#ifndef _I386_KOS_BITS_PTHREADTYPES_H
#define _I386_KOS_BITS_PTHREADTYPES_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

/* Copyright (C) 2002-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef __x86_64__
#if __SIZEOF_POINTER__ == 8
#   define __SIZEOF_PTHREAD_ATTR_T        56
#   define __SIZEOF_PTHREAD_MUTEX_T       40
#   define __SIZEOF_PTHREAD_MUTEXATTR_T   4
#   define __SIZEOF_PTHREAD_COND_T        48
#   define __SIZEOF_PTHREAD_CONDATTR_T    4
#   define __SIZEOF_PTHREAD_RWLOCK_T      56
#   define __SIZEOF_PTHREAD_RWLOCKATTR_T  8
#   define __SIZEOF_PTHREAD_BARRIER_T     32
#   define __SIZEOF_PTHREAD_BARRIERATTR_T 4
#else
#   define __SIZEOF_PTHREAD_ATTR_T        32
#   define __SIZEOF_PTHREAD_MUTEX_T       32
#   define __SIZEOF_PTHREAD_MUTEXATTR_T   4
#   define __SIZEOF_PTHREAD_COND_T        48
#   define __SIZEOF_PTHREAD_CONDATTR_T    4
#   define __SIZEOF_PTHREAD_RWLOCK_T      44
#   define __SIZEOF_PTHREAD_RWLOCKATTR_T  8
#   define __SIZEOF_PTHREAD_BARRIER_T     20
#   define __SIZEOF_PTHREAD_BARRIERATTR_T 4
#endif
#else
#   define __SIZEOF_PTHREAD_ATTR_T        36
#   define __SIZEOF_PTHREAD_MUTEX_T       24
#   define __SIZEOF_PTHREAD_MUTEXATTR_T   4
#   define __SIZEOF_PTHREAD_COND_T        48
#   define __SIZEOF_PTHREAD_CONDATTR_T    4
#   define __SIZEOF_PTHREAD_RWLOCK_T      32
#   define __SIZEOF_PTHREAD_RWLOCKATTR_T  8
#   define __SIZEOF_PTHREAD_BARRIER_T     20
#   define __SIZEOF_PTHREAD_BARRIERATTR_T 4
#endif


#define __SIZEOF_PTHREAD_T  __SIZEOF_POINTER__
#ifdef __CC__
typedef __UINTPTR_TYPE__ pthread_t;

union pthread_attr_t {
	char __size[__SIZEOF_PTHREAD_ATTR_T];
	__INTPTR_TYPE__ __align;
};
#ifndef __pthread_attr_t_defined
#define __pthread_attr_t_defined 1
typedef union pthread_attr_t pthread_attr_t;
#endif

#ifdef __x86_64__
typedef struct __pthread_internal_list {
	struct __pthread_internal_list *__prev;
	struct __pthread_internal_list *__next;
} __pthread_list_t;
#else
typedef struct __pthread_internal_slist {
	struct __pthread_internal_slist *__next;
} __pthread_slist_t;
#endif


typedef union {
	struct __pthread_mutex_s {
		int __lock;
		unsigned int __count;
		int __owner;
#ifdef __x86_64__
		unsigned int __nusers;
#endif
		/* KIND must stay at this position in the structure to maintain binary compatibility.  */
		int __kind;
#ifdef __x86_64__
		short __spins;
		short __elision;
		__pthread_list_t __list;
#define __PTHREAD_MUTEX_HAVE_PREV  1
#define __PTHREAD_SPINS            0, 0
#else
		unsigned int __nusers;
		union {
			struct {
				short __espins;
				short __elision;
#define __spins   __elision_data.__espins
#define __elision __elision_data.__elision
#define __PTHREAD_SPINS         {0,0}
			} __elision_data;
			__pthread_slist_t __list;
		};
#endif
	} __data;
	char __size[__SIZEOF_PTHREAD_MUTEX_T];
	__INTPTR_TYPE__ __align;
} pthread_mutex_t;

typedef union {
	char __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
	int  __align;
} pthread_mutexattr_t;


typedef union {
	struct {
		int          __lock;
		unsigned int __futex;
		__ULONGLONG  __total_seq;
		__ULONGLONG  __wakeup_seq;
		__ULONGLONG  __woken_seq;
		void        *__mutex;
		unsigned int __nwaiters;
		unsigned int __broadcast_seq;
	} __data;
	char __size[__SIZEOF_PTHREAD_COND_T];
	__LONGLONG __align;
} pthread_cond_t;

typedef union {
	char __size[__SIZEOF_PTHREAD_CONDATTR_T];
	int  __align;
} pthread_condattr_t;

typedef unsigned int pthread_key_t;
typedef int pthread_once_t;

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
typedef union {
#ifdef __x86_64__
	struct {
		int __lock;
		unsigned int __nr_readers;
		unsigned int __readers_wakeup;
		unsigned int __writer_wakeup;
		unsigned int __nr_readers_queued;
		unsigned int __nr_writers_queued;
		int __writer;
		int __shared;
		signed char __rwelision;
#ifdef  __ILP32__
		unsigned char __pad1[3];
#define __PTHREAD_RWLOCK_ELISION_EXTRA 0,{0,0,0}
#else /* __ILP32__ */
		unsigned char __pad1[7];
#define __PTHREAD_RWLOCK_ELISION_EXTRA 0,{0,0,0,0,0,0,0}
#endif /* !__ILP32__ */
		__UINTPTR_TYPE__ __pad2;
		unsigned int __flags;
#define __PTHREAD_RWLOCK_INT_FLAGS_SHARED    1
	} __data;
#else /* __x86_64__ */
	struct {
		int           __lock;
		unsigned int  __nr_readers;
		unsigned int  __readers_wakeup;
		unsigned int  __writer_wakeup;
		unsigned int  __nr_readers_queued;
		unsigned int  __nr_writers_queued;
		unsigned char __flags;
		unsigned char __shared;
		signed char   __rwelision;
#define __PTHREAD_RWLOCK_ELISION_EXTRA 0
		unsigned char __pad2;
		int           __writer;
	} __data;
#endif /* !__x86_64__ */
	char __size[__SIZEOF_PTHREAD_RWLOCK_T];
	__INTPTR_TYPE__ __align;
} pthread_rwlock_t;

typedef union {
	char __size[__SIZEOF_PTHREAD_RWLOCKATTR_T];
	__INTPTR_TYPE__ __align;
} pthread_rwlockattr_t;
#endif

#ifdef __USE_XOPEN2K
typedef volatile int pthread_spinlock_t;
typedef union {
	char __size[__SIZEOF_PTHREAD_BARRIER_T];
	__INTPTR_TYPE__ __align;
} pthread_barrier_t;
typedef union {
	char __size[__SIZEOF_PTHREAD_BARRIERATTR_T];
	int  __align;
} pthread_barrierattr_t;
#endif /* __USE_XOPEN2K */

#ifndef __x86_64__
#define __cleanup_fct_attribute   __attribute__((__regparm__(1)))
#endif
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BITS_PTHREADTYPES_H */
