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
#ifndef _I386_KOS_BITS_OS_KOS_SIGEVENT64_H
#define _I386_KOS_BITS_OS_KOS_SIGEVENT64_H 1

/* File:
 *    <i386-kos/bits/sigevent64.h>
 *
 * Definitions:
 *    - struct __sigeventx64 { ... };
 * #if defined(__x86_64__)
 *    - struct sigevent { ... };
 * #endif
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__pointer.h> /* __HYBRID_PTR64 */
#include <hybrid/host.h>      /* __x86_64__ */
#include <hybrid/typecore.h>  /* __INT32_TYPE__ */

#include <bits/os/kos/sigval64.h> /* union __sigvalx64 */

#ifdef __x86_64__
#define __sigeventx64                       sigevent
#define __SIGEV_MAX_SIZE                    __SIGEVX64_MAX_SIZE
#define __OFFSET_SIGEVENT_VALUE             __OFFSET_SIGEVENTX64_VALUE
#define __OFFSET_SIGEVENT_SIGNO             __OFFSET_SIGEVENTX64_SIGNO
#define __OFFSET_SIGEVENT_NOTIFY            __OFFSET_SIGEVENTX64_NOTIFY
#define __OFFSET_SIGEVENT_DATA              __OFFSET_SIGEVENTX64_DATA
#define __OFFSET_SIGEVENT_TID               __OFFSET_SIGEVENTX64_TID
#define __OFFSET_SIGEVENT_NOTIFY_FUNCTION   __OFFSET_SIGEVENTX64_NOTIFY_FUNCTION
#define __OFFSET_SIGEVENT_NOTIFY_ATTRIBUTES __OFFSET_SIGEVENTX64_NOTIFY_ATTRIBUTES
#define __SIZEOF_SIGEVENT                   __SIZEOF_SIGEVENTX64
#endif /* __x86_64__ */



#ifdef __KERNEL__
#define __SIGEVX64_MAX_SIZE 32
#else /* __KERNEL__ */
#define __SIGEVX64_MAX_SIZE 64
#endif /* !__KERNEL__ */
#define __OFFSET_SIGEVENTX64_VALUE             0
#define __OFFSET_SIGEVENTX64_SIGNO             8
#define __OFFSET_SIGEVENTX64_NOTIFY            12
#define __OFFSET_SIGEVENTX64_DATA              16 /* [FIELD(_sigev_data, _sigev_un._data)] */
#define __OFFSET_SIGEVENTX64_TID               16 /* [FIELD(_sigev_tid, _sigev_un._tid)] */
#define __OFFSET_SIGEVENTX64_NOTIFY_FUNCTION   16 /* [FIELD(sigev_notify_function, _sigev_un._sigev_thread._function)] */
#define __OFFSET_SIGEVENTX64_NOTIFY_ATTRIBUTES 24 /* [FIELD(sigev_notify_attributes, _sigev_un._sigev_thread._attribute)] */
#define __SIZEOF_SIGEVENTX64 __SIGEVX64_MAX_SIZE

#ifdef __CC__
__DECL_BEGIN

#ifdef _sigev_data
#define __PRIVATE_WAS_DEFINED__sigev_data
#endif /* _sigev_data */
#undef _sigev_data
#undef _sigev_tid
#undef sigev_notify_function
#undef sigev_notify_attributes
union __pthread_attr;
struct __sigeventx64 /*[NAME(sigeventx64)][PREFIX(sigev_)]*/ {
	union __sigvalx64 sigev_value;  /* ... */
	__INT32_TYPE__    sigev_signo;  /* ... */
	__INT32_TYPE__    sigev_notify; /* One of `SIGEV_*' */
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION) &&  \
     defined(__HYBRID_PTR64_IN_TRANSPARENT_STRUCT))
	union {
		union {
			__UINT64_TYPE__ _sigev_data[(__SIGEVX64_MAX_SIZE / 8) - 2];
			__INT32_TYPE__  _sigev_tid; /* When SIGEV_SIGNAL and  SIGEV_THREAD_ID set,  LWP
			                             * TID (pid_t) of the thread to receive the signal. */
			struct {
				__HYBRID_FUNCPTR64(void, __ATTR_SYSVABI, sigev_notify_function,(union __sigvalx64 __val)); /* Function to start. */
				__HYBRID_PTR64(union __pthread_attr)     sigev_notify_attributes;                          /* Thread attributes. */
			};
		};
#endif /* Transparent struct/union */
		union {
			__UINT64_TYPE__ _data[(__SIGEVX64_MAX_SIZE / 8) - 2];
			__INT32_TYPE__  _tid; /* When SIGEV_SIGNAL and  SIGEV_THREAD_ID set,  LWP
			                       * TID (pid_t) of the thread to receive the signal. */
			struct {
				__HYBRID_FUNCPTR64(void, __ATTR_SYSVABI, _function,(union __sigvalx64 __val)); /* Function to start. */
				__HYBRID_PTR64(union __pthread_attr)     _attribute;                           /* Thread attributes. */
			} _sigev_thread;
		} _sigev_un;
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION) &&  \
     defined(__HYBRID_PTR64_IN_TRANSPARENT_STRUCT))
	};
#endif /* ... */
#if (defined(__PRIVATE_WAS_DEFINED__sigev_data) ||   \
     !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) || \
     !defined(__COMPILER_HAVE_TRANSPARENT_UNION) ||  \
     !defined(__HYBRID_PTR64_IN_TRANSPARENT_STRUCT))
#undef __PRIVATE_WAS_DEFINED__sigev_data
#define _sigev_data             _sigev_un._data
#define _sigev_tid              _sigev_un._tid
#define sigev_notify_function   _sigev_un._sigev_thread._function
#define sigev_notify_attributes _sigev_un._sigev_thread._attribute
#endif /* ... */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_KOS_SIGEVENT64_H */
