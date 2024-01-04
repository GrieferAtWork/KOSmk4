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
#ifndef _I386_KOS_BITS_OS_KOS_SIGEVENT32_H
#define _I386_KOS_BITS_OS_KOS_SIGEVENT32_H 1

/* File:
 *    <i386-kos/bits/os/kos/sigevent32.h>
 *
 * Definitions:
 *    - struct __sigeventx32 { ... };
 * #if !defined(__x86_64__) && defined(__i386__)
 *    - struct sigevent { ... };
 * #endif
 */

#include <__stdinc.h>
#include <features.h> /* __USE_KOS */

#include <hybrid/__pointer.h> /* __HYBRID_PTR32 */
#include <hybrid/host.h>      /* __x86_64__ */
#include <hybrid/typecore.h>  /* __INT32_TYPE__ */

#include <bits/os/kos/sigval32.h> /* union __sigvalx32 */

#if !defined(__x86_64__) && defined(__i386__)
#define __sigeventx32                       sigevent
#define __SIGEV_MAX_SIZE                    __SIGEVX32_MAX_SIZE
#define __OFFSET_SIGEVENT_VALUE             __OFFSET_SIGEVENTX32_VALUE
#define __OFFSET_SIGEVENT_SIGNO             __OFFSET_SIGEVENTX32_SIGNO
#define __OFFSET_SIGEVENT_NOTIFY            __OFFSET_SIGEVENTX32_NOTIFY
#define __OFFSET_SIGEVENT_DATA              __OFFSET_SIGEVENTX32_DATA
#define __OFFSET_SIGEVENT_TID               __OFFSET_SIGEVENTX32_TID
#define __OFFSET_SIGEVENT_NOTIFY_FUNCTION   __OFFSET_SIGEVENTX32_NOTIFY_FUNCTION
#define __OFFSET_SIGEVENT_NOTIFY_ATTRIBUTES __OFFSET_SIGEVENTX32_NOTIFY_ATTRIBUTES
#define __SIZEOF_SIGEVENT                   __SIZEOF_SIGEVENTX32
#endif /* !__x86_64__ && __i386__ */



#ifdef __KERNEL__
#define __SIGEVX32_MAX_SIZE 20
#else /* __KERNEL__ */
#define __SIGEVX32_MAX_SIZE 64
#endif /* !__KERNEL__ */
#define __OFFSET_SIGEVENTX32_VALUE             0
#define __OFFSET_SIGEVENTX32_SIGNO             4
#define __OFFSET_SIGEVENTX32_NOTIFY            8
#define __OFFSET_SIGEVENTX32_DATA              12 /* [FIELD(_sigev_data, _sigev_un._data)] */
#define __OFFSET_SIGEVENTX32_TID               12 /* [FIELD(_sigev_tid, _sigev_un._tid)] */
#define __OFFSET_SIGEVENTX32_NOTIFY_FUNCTION   12 /* [FIELD(sigev_notify_function, _sigev_un._sigev_thread._function)] */
#define __OFFSET_SIGEVENTX32_NOTIFY_ATTRIBUTES 16 /* [FIELD(sigev_notify_attributes, _sigev_un._sigev_thread._attribute)] */
#define __SIZEOF_SIGEVENTX32                   __SIGEVX32_MAX_SIZE

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
struct __sigeventx32 /*[NAME(sigeventx32)][PREFIX(sigev_)]*/ {
	union __sigvalx32 sigev_value;
	__INT32_TYPE__    sigev_signo;
	__INT32_TYPE__    sigev_notify; /* One of `SIGEV_*' */
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION) &&  \
     defined(__HYBRID_PTR32_IN_TRANSPARENT_STRUCT))
	union {
		union {
			__UINT32_TYPE__ _sigev_data[(__SIGEVX32_MAX_SIZE - 12) / 4];
			__INT32_TYPE__  _sigev_tid; /* When SIGEV_SIGNAL and  SIGEV_THREAD_ID set,  LWP
			                             * TID (pid_t) of the thread to receive the signal. */
			struct {
				__HYBRID_FUNCPTR32(void, __ATTR_CDECL, sigev_notify_function,(union __sigvalx32 __val)); /* Function to start. */
				__HYBRID_PTR32(union __pthread_attr)   sigev_notify_attributes;                          /* Thread attributes. */
			};
		};
#endif /* Transparent struct/union */
		union {
			__UINT32_TYPE__ _data[(__SIGEVX32_MAX_SIZE - 12) / 4];
			__INT32_TYPE__  _tid; /* When SIGEV_SIGNAL and  SIGEV_THREAD_ID set,  LWP
			                       * TID (pid_t) of the thread to receive the signal. */
			struct {
				__HYBRID_FUNCPTR32(void, __ATTR_CDECL, _function,(union __sigvalx32 __val)); /* Function to start. */
				__HYBRID_PTR32(union __pthread_attr)   _attribute;                           /* Thread attributes. */
			} _sigev_thread;
		} _sigev_un;
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION) &&  \
     defined(__HYBRID_PTR32_IN_TRANSPARENT_STRUCT))
	};
#endif /* ... */
#if (defined(__PRIVATE_WAS_DEFINED__sigev_data) ||   \
     !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) || \
     !defined(__COMPILER_HAVE_TRANSPARENT_UNION) ||  \
     !defined(__HYBRID_PTR32_IN_TRANSPARENT_STRUCT))
#undef __PRIVATE_WAS_DEFINED__sigev_data
#define _sigev_data             _sigev_un._data
#define _sigev_tid              _sigev_un._tid
#define sigev_notify_function   _sigev_un._sigev_thread._function
#define sigev_notify_attributes _sigev_un._sigev_thread._attribute
#endif /* ... */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_KOS_SIGEVENT32_H */
