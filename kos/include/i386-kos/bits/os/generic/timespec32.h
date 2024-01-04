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
#ifndef _I386_KOS_BITS_OS_GENERIC_TIMESPEC32_H
#define _I386_KOS_BITS_OS_GENERIC_TIMESPEC32_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <parts/timespec-cxx-support.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef timespecx32
#pragma push_macro("timespecx32")
#define __PRIVATE_DID_PUSH_TIMESPECX32
#endif /* timespecx32 */
#ifdef timespecx32_64
#pragma push_macro("timespecx32_64")
#define __PRIVATE_DID_PUSH_TIMESPECX32_64
#endif /* timespecx32_64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x32_and_x32_64(
	linkIf:    "defined(__i386__) && !defined(__x86_64__)",
	name:      "timespec",
	name32:    "timespecx32",
	name64:    "timespecx32_64",
	altname64: "__timespecx32_64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	link64If:  "defined(__USE_TIME_BITS64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef timespecx32
#undef timespecx32_64
#if !defined(__i386__) || defined(__x86_64__)
#define timespecx32    __timespecx32
#define timespecx32_64 __timespecx32_64
#else /* !__i386__ || __x86_64__ */
#include <features.h>
#ifdef __USE_TIME_BITS64
/* Configure:
 *   - `timespecx32_64' as `timespec'
 *   - `timespecx32' as `__timespec32' */
#define timespecx32      __timespec32
#define timespecx32_64   timespec
#define __timespecx32    __timespec32
#define __timespecx32_64 timespec
#define __timespec32     __timespec32
#define __timespec_alt   __timespec32
#ifdef __USE_KOS
#define timespec32 __timespec32
#endif /* !__USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define timespec64   timespec
#define __timespec64 timespec
#else /* __USE_STRUCT64_MACRO */
#define __timespecx32_64_alt timespec64
#define __timespec64         timespec64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __timespec64 timespec
#endif /* !__USE_TIME64 */

#define __OFFSET_TIMESPEC_SEC  __OFFSET_TIMESPECX32_64_SEC
#define __OFFSET_TIMESPEC_NSEC __OFFSET_TIMESPECX32_64_NSEC
#define __SIZEOF_TIMESPEC      __SIZEOF_TIMESPECX32_64
#define __ALIGNOF_TIMESPEC     __ALIGNOF_TIMESPECX32_64

#else /* __USE_TIME_BITS64 */
/* Configure:
 *   - `timespecx32_64' as `timespec64' or `__timespec64'
 *   - `timespecx32' as `timespec' */
#define timespecx32   timespec
#define __timespec32  timespec
#define __timespecx32 timespec
#ifdef __USE_KOS
#define timespec32 timespec
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#define __timespecx32_64 timespec64
#define timespecx32_64   timespec64
#define __timespec64     timespec64
#define __timespec_alt   timespec64
#else /* __USE_TIME64 */
#define __timespecx32_64 __timespec64
#define timespecx32_64   __timespec64
#define __timespec64     __timespec64
#define __timespec_alt   __timespec64
#endif /* !__USE_TIME64 */

#define __OFFSET_TIMESPEC_SEC  __OFFSET_TIMESPECX32_SEC
#define __OFFSET_TIMESPEC_NSEC __OFFSET_TIMESPECX32_NSEC
#define __SIZEOF_TIMESPEC      __SIZEOF_TIMESPECX32
#define __ALIGNOF_TIMESPEC     __ALIGNOF_TIMESPECX32

#endif /* !__USE_TIME_BITS64 */

#define __OFFSET_TIMESPEC32_SEC  __OFFSET_TIMESPECX32_SEC
#define __OFFSET_TIMESPEC32_NSEC __OFFSET_TIMESPECX32_NSEC
#define __SIZEOF_TIMESPEC32      __SIZEOF_TIMESPECX32
#define __ALIGNOF_TIMESPEC32     __ALIGNOF_TIMESPECX32
#define __OFFSET_TIMESPEC64_SEC  __OFFSET_TIMESPECX32_64_SEC
#define __OFFSET_TIMESPEC64_NSEC __OFFSET_TIMESPECX32_64_NSEC
#define __SIZEOF_TIMESPEC64      __SIZEOF_TIMESPECX32_64
#define __ALIGNOF_TIMESPEC64     __ALIGNOF_TIMESPECX32_64

#define __timespec_defined
#endif /* __i386__ && !__x86_64__*/
/*[[[end]]]*/


#if defined(__i386__) && !defined(__x86_64__)
#ifdef __USE_TIME_BITS64
#define __TIMESPEC_HAVE_TV_PAD
#endif /* __USE_TIME_BITS64 */
#define __TIMESPEC64_HAVE_TV_PAD
#endif /* __i386__ && !__x86_64__ */
#define __TIMESPECX32_64_HAVE_TV_PAD


#define __OFFSET_TIMESPECX32_SEC     0
#define __OFFSET_TIMESPECX32_NSEC    4
#define __SIZEOF_TIMESPECX32         8
#define __ALIGNOF_TIMESPECX32        __ALIGNOF_INT32__
#define __OFFSET_TIMESPECX32_64_SEC  0
#define __OFFSET_TIMESPECX32_64_NSEC 8
#define __SIZEOF_TIMESPECX32_64      16
#define __ALIGNOF_TIMESPECX32_64     __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN
__TIMESPEC_CXX_DECL_BEGIN

/* 32-bit timespec for i386 */
struct timespecx32 /*[PREFIX(tv_)]*/ {
	__INT32_TYPE__  tv_sec;   /* Seconds */
#ifdef __USE_KOS_ALTERATIONS
	__UINT32_TYPE__ tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#else /* __USE_KOS_ALTERATIONS */
	__INT32_TYPE__  tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#endif /* !__USE_KOS_ALTERATIONS */
	__TIMESPEC_CXX_SUPPORT(4, struct timespecx32, __INT32_TYPE__, __UINT32_TYPE__)
};
__TIMESPEC_CXX_SUPPORT2(4, struct timespecx32, __INT32_TYPE__, __UINT32_TYPE__)

/* 64-bit timespec for i386 */
struct timespecx32_64 /*[PREFIX(tv_)]*/ {
	__INT64_TYPE__    tv_sec;   /* Seconds */
#ifdef __USE_KOS_ALTERATIONS
	__UINT32_TYPE__   tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#else /* __USE_KOS_ALTERATIONS */
	__INT32_TYPE__    tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#endif /* !__USE_KOS_ALTERATIONS */
	__UINT32_TYPE__ __tv_pad;   /* ... */
	__TIMESPEC_CXX_SUPPORT(8, struct timespecx32_64, __INT64_TYPE__, __UINT32_TYPE__)
};
__TIMESPEC_CXX_SUPPORT2(8, struct timespecx32_64, __INT64_TYPE__, __UINT32_TYPE__)

#ifdef __timespecx32_64_alt
struct __timespecx32_64_alt {
	__INT64_TYPE__    tv_sec;   /* Seconds */
#ifdef __USE_KOS_ALTERATIONS
	__UINT32_TYPE__   tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#else /* __USE_KOS_ALTERATIONS */
	__INT32_TYPE__    tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#endif /* !__USE_KOS_ALTERATIONS */
	__UINT32_TYPE__ __tv_pad;   /* ... */
	__TIMESPEC_CXX_SUPPORT(8, struct __timespecx32_64_alt, __INT64_TYPE__, __UINT32_TYPE__)
};
__TIMESPEC_CXX_SUPPORT2(8, struct __timespecx32_64_alt, __INT64_TYPE__, __UINT32_TYPE__)
#undef __timespecx32_64_alt
#endif /* __timespecx32_64_alt */

__TIMESPEC_CXX_DECL_END
__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef timespecx32
#undef timespecx32_64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_TIMESPECX32_64
#undef __PRIVATE_DID_PUSH_TIMESPECX32_64
#pragma pop_macro("timespecx32_64")
#endif /* __PRIVATE_DID_PUSH_TIMESPECX32_64 */
#ifdef __PRIVATE_DID_PUSH_TIMESPECX32
#undef __PRIVATE_DID_PUSH_TIMESPECX32
#pragma pop_macro("timespecx32")
#endif /* __PRIVATE_DID_PUSH_TIMESPECX32 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_GENERIC_TIMESPEC32_H */
