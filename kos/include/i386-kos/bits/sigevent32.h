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
#ifndef _I386_KOS_BIT_SIGEVENT32_H
#define _I386_KOS_BIT_SIGEVENT32_H 1

#include <__stdinc.h>
#include <__crt.h>            /* __CRT_CYG_PRIMARY */
#include <features.h>         /* __USE_KOS */
#include <hybrid/host.h>      /* __x86_64__ */
#include <hybrid/typecore.h>  /* __INT32_TYPE__ */
#include <hybrid/__pointer.h> /* __HYBRID_PTR32 */
#include <bits/sigval32.h>    /* union sigval32 */

#if !defined(__CRT_CYG_PRIMARY) && !defined(__x86_64__)
#define sigevent32                          sigevent
#define sigevent32_t                        sigevent_t
#define __SIGEV_MAX_SIZE                    __SIGEV32_MAX_SIZE
#define __OFFSET_SIGEVENT_VALUE             __OFFSET_SIGEVENT32_VALUE
#define __OFFSET_SIGEVENT_SIGNO             __OFFSET_SIGEVENT32_SIGNO
#define __OFFSET_SIGEVENT_NOTIFY            __OFFSET_SIGEVENT32_NOTIFY
#define __OFFSET_SIGEVENT_DATA              __OFFSET_SIGEVENT32_DATA
#define __OFFSET_SIGEVENT_TID               __OFFSET_SIGEVENT32_TID
#define __OFFSET_SIGEVENT_NOTIFY_FUNCTION   __OFFSET_SIGEVENT32_NOTIFY_FUNCTION
#define __OFFSET_SIGEVENT_NOTIFY_ATTRIBUTES __OFFSET_SIGEVENT32_NOTIFY_ATTRIBUTES
#define __SIZEOF_SIGEVENT                   __SIZEOF_SIGEVENT32
#endif /* !__CRT_CYG_PRIMARY && !__x86_64__ */


__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __pthread_attr_t_defined
#define __pthread_attr_t_defined 1
typedef union pthread_attr_t pthread_attr_t;
#endif /* !__pthread_attr_t_defined */
#endif /* __CC__ */

#ifdef __KERNEL__
#define __SIGEV32_MAX_SIZE    20
#else /* __KERNEL__ */
#define __SIGEV32_MAX_SIZE    64
#endif /* !__KERNEL__ */
#define __OFFSET_SIGEVENT32_VALUE             0
#define __OFFSET_SIGEVENT32_SIGNO             4
#define __OFFSET_SIGEVENT32_NOTIFY            8
#define __OFFSET_SIGEVENT32_DATA              12 /* [FIELD(_sigev_data, _sigev_un._data)] */
#define __OFFSET_SIGEVENT32_TID               12 /* [FIELD(_sigev_tid, _sigev_un._tid)] */
#define __OFFSET_SIGEVENT32_NOTIFY_FUNCTION   12 /* [FIELD(sigev_notify_function, _sigev_un._sigev_thread._function)] */
#define __OFFSET_SIGEVENT32_NOTIFY_ATTRIBUTES 16 /* [FIELD(sigev_notify_attributes, _sigev_un._sigev_thread._attribute)] */
#define __SIZEOF_SIGEVENT32   __SIGEV32_MAX_SIZE

#ifdef __CC__
typedef struct sigevent32 /*[PREFIX(sigev_)]*/ {
	union sigval32 sigev_value;
	__INT32_TYPE__ sigev_signo;
	__INT32_TYPE__ sigev_notify;
#if defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
    defined(__COMPILER_HAVE_TRANSPARENT_UNION)
#if !defined(__USE_KOS) || defined(GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C)
	union {
#endif /* !__USE_KOS || GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C */
	union {
		__UINT32_TYPE__ _sigev_data[(__SIGEV32_MAX_SIZE / 4) - 3];
		__INT32_TYPE__  _sigev_tid; /* When SIGEV_SIGNAL and SIGEV_THREAD_ID set, LWP
		                             * TID (pid_t) of the thread to receive the signal. */
		struct {
			__HYBRID_FUNCPTR32(void, __LIBCCALL, sigev_notify_function,(union sigval32 __val)); /* Function to start. */
			__HYBRID_PTR32(pthread_attr_t)       sigev_notify_attributes;                       /* Thread attributes. */
		};
	};
#if !defined(__USE_KOS) || defined(GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C)
	union {
		__UINT32_TYPE__ _data[(__SIGEV32_MAX_SIZE / 4) - 3];
		__INT32_TYPE__  _tid; /* When SIGEV_SIGNAL and SIGEV_THREAD_ID set, LWP
		                       * TID (pid_t) of the thread to receive the signal. */
		struct {
			__HYBRID_FUNCPTR32(void, __LIBCCALL, _function,(union sigval32 __val)); /* Function to start. */
			__HYBRID_PTR32(pthread_attr_t)       _attribute;                        /* Thread attributes. */
		} _sigev_thread;
	} _sigev_un;
	};
#endif /* !__USE_KOS || GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C */
#else
	union {
		__UINT32_TYPE__ _data[(__SIGEV32_MAX_SIZE / 4) - 3];
		__INT32_TYPE__  _tid; /* When SIGEV_SIGNAL and SIGEV_THREAD_ID set, LWP
		                       * TID (pid_t) of the thread to receive the signal. */
		struct {
			__HYBRID_FUNCPTR32(void, __LIBCCALL, _function,(union sigval32 __val)); /* Function to start. */
			__HYBRID_PTR32(pthread_attr_t)       _attribute;                        /* Thread attributes. */
		} _sigev_thread;
	} _sigev_un;
#define _sigev_data             _sigev_un._data
#define _sigev_tid              _sigev_un._tid
#define sigev_notify_function   _sigev_un._sigev_thread._function
#define sigev_notify_attributes _sigev_un._sigev_thread._attribute
#endif
} sigevent32_t;
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BIT_SIGEVENT32_H */
