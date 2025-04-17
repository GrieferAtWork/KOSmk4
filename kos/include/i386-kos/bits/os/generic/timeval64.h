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
/*!replace_with_include <bits/os/timeval.h>*/
#ifndef _I386_KOS_BITS_OS_GENERIC_TIMEVAL64_H
#define _I386_KOS_BITS_OS_GENERIC_TIMEVAL64_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <parts/timeval-cxx-support.h>


#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef timevalx64
#pragma push_macro("timevalx64")
#define __PRIVATE_DID_PUSH_TIMEVALX64
#endif /* timevalx64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x64(
	linkIf:    "defined(__x86_64__)",
	name:      "timeval",
	name64:    "timevalx64",
	altname64: "__timevalx64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef timevalx64
#ifndef __x86_64__
#define timevalx64 __timevalx64
#else /* !__x86_64__ */
#include <features.h>
#define __OFFSET_TIMEVAL_SEC    __OFFSET_TIMEVALX64_SEC
#define __OFFSET_TIMEVAL_USEC   __OFFSET_TIMEVALX64_USEC
#define __SIZEOF_TIMEVAL        __SIZEOF_TIMEVALX64
#define __ALIGNOF_TIMEVAL       __ALIGNOF_TIMEVALX64
#define __OFFSET_TIMEVAL32_SEC  __OFFSET_TIMEVALX64_SEC
#define __OFFSET_TIMEVAL32_USEC __OFFSET_TIMEVALX64_USEC
#define __SIZEOF_TIMEVAL32      __SIZEOF_TIMEVALX64
#define __ALIGNOF_TIMEVAL32     __ALIGNOF_TIMEVALX64
#define __OFFSET_TIMEVAL64_SEC  __OFFSET_TIMEVALX64_SEC
#define __OFFSET_TIMEVAL64_USEC __OFFSET_TIMEVALX64_USEC
#define __SIZEOF_TIMEVAL64      __SIZEOF_TIMEVALX64
#define __ALIGNOF_TIMEVAL64     __ALIGNOF_TIMEVALX64
#define timevalx64              timeval
#define __timevalx64            timeval
#define __timeval32             timeval
#define __timeval_alt           timeval
#define _TIMEVAL_MATCHES_TIMEVAL64 1
#ifdef __USE_KOS
#define timeval32 timeval
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define timeval64   timeval
#define __timeval64 timeval
#else /* __USE_STRUCT64_MACRO */
#define __timevalx64_alt timeval64
#define __timeval64      timeval64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __timeval64 timeval
#endif /* !__USE_TIME64 */
#define __timeval_defined
#endif /* __x86_64__ */
/*[[[end]]]*/

#define __OFFSET_TIMEVALX64_SEC   0
#define __OFFSET_TIMEVALX64_USEC  8
#define __SIZEOF_TIMEVALX64       16
#define __ALIGNOF_TIMEVALX64      __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN
__TIMEVAL_CXX_DECL_BEGIN

/* timeval for x86_64 */
struct timevalx64 /*[PREFIX(tv_)]*/ {
	__INT64_TYPE__   tv_sec;   /* Seconds */
#ifdef __USE_KOS_ALTERATIONS
	__ULONG64_TYPE__ tv_usec;  /* Micro seconds (< 1000000 == 1_000_000) */
#else /* __USE_KOS_ALTERATIONS */
	__LONG64_TYPE__  tv_usec;  /* Micro seconds (< 1000000 == 1_000_000) */
#endif /* !__USE_KOS_ALTERATIONS */
	__TIMEVAL_CXX_SUPPORT(8, struct timevalx64, __INT64_TYPE__, __UINT64_TYPE__)
};
__TIMEVAL_CXX_SUPPORT2(8, struct timevalx64, __INT64_TYPE__, __UINT64_TYPE__)

#ifdef __timevalx64_alt
struct __timevalx64_alt {
	__INT64_TYPE__   tv_sec;   /* Seconds */
#ifdef __USE_KOS_ALTERATIONS
	__ULONG64_TYPE__ tv_usec;  /* Micro seconds (< 1000000 == 1_000_000) */
#else /* __USE_KOS_ALTERATIONS */
	__LONG64_TYPE__  tv_usec;  /* Micro seconds (< 1000000 == 1_000_000) */
#endif /* !__USE_KOS_ALTERATIONS */
	__TIMEVAL_CXX_SUPPORT(8, struct __timevalx64_alt, __INT64_TYPE__, __UINT64_TYPE__)
};
__TIMEVAL_CXX_SUPPORT2(8, struct __timevalx64_alt, __INT64_TYPE__, __UINT64_TYPE__)
#undef __timevalx64_alt
#endif /* __timevalx64_alt */

__TIMEVAL_CXX_DECL_END
__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef timevalx64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_TIMEVALX64
#undef __PRIVATE_DID_PUSH_TIMEVALX64
#pragma pop_macro("timevalx64")
#endif /* __PRIVATE_DID_PUSH_TIMEVALX64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_GENERIC_TIMEVAL64_H */
