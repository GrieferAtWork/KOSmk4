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
#ifndef _I386_KOS_BITS_OS_GENERIC_TIMESPEC64_H
#define _I386_KOS_BITS_OS_GENERIC_TIMESPEC64_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <parts/timespec-cxx-support.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef timespecx64
#pragma push_macro("timespecx64")
#define __PRIVATE_DID_PUSH_TIMESPECX64
#endif /* timespecx64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x64(
	linkIf:    "defined(__x86_64__)",
	name:      "timespec",
	name64:    "timespecx64",
	altname64: "__timespecx64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef timespecx64
#ifndef __x86_64__
#define timespecx64 __timespecx64
#else /* !__x86_64__ */
#include <features.h>
#define __OFFSET_TIMESPEC_SEC    __OFFSET_TIMESPECX64_SEC
#define __OFFSET_TIMESPEC_NSEC   __OFFSET_TIMESPECX64_NSEC
#define __SIZEOF_TIMESPEC        __SIZEOF_TIMESPECX64
#define __ALIGNOF_TIMESPEC       __ALIGNOF_TIMESPECX64
#define __OFFSET_TIMESPEC32_SEC  __OFFSET_TIMESPECX64_SEC
#define __OFFSET_TIMESPEC32_NSEC __OFFSET_TIMESPECX64_NSEC
#define __SIZEOF_TIMESPEC32      __SIZEOF_TIMESPECX64
#define __ALIGNOF_TIMESPEC32     __ALIGNOF_TIMESPECX64
#define __OFFSET_TIMESPEC64_SEC  __OFFSET_TIMESPECX64_SEC
#define __OFFSET_TIMESPEC64_NSEC __OFFSET_TIMESPECX64_NSEC
#define __SIZEOF_TIMESPEC64      __SIZEOF_TIMESPECX64
#define __ALIGNOF_TIMESPEC64     __ALIGNOF_TIMESPECX64
#define timespecx64              timespec
#define __timespecx64            timespec
#define __timespec32             timespec
#define __timespec_alt           timespec
#define _TIMESPEC_MATCHES_TIMESPEC64 1
#ifdef __USE_KOS
#define timespec32 timespec
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define timespec64   timespec
#define __timespec64 timespec
#else /* __USE_STRUCT64_MACRO */
#define __timespecx64_alt timespec64
#define __timespec64      timespec64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __timespec64 timespec
#endif /* !__USE_TIME64 */
#define __timespec_defined
#endif /* __x86_64__ */
/*[[[end]]]*/

#define __OFFSET_TIMESPECX64_SEC  0
#define __OFFSET_TIMESPECX64_NSEC 8
#define __SIZEOF_TIMESPECX64      16
#define __ALIGNOF_TIMESPECX64     __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN
__TIMESPEC_CXX_DECL_BEGIN

/* timespec for x86_64 */
struct timespecx64 /*[PREFIX(tv_)]*/ {
	__INT64_TYPE__  tv_sec;   /* Seconds */
#ifdef __USE_KOS_ALTERATIONS
	__UINT64_TYPE__ tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#else /* __USE_KOS_ALTERATIONS */
	__INT64_TYPE__  tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#endif /* !__USE_KOS_ALTERATIONS */
	__TIMESPEC_CXX_SUPPORT(8, struct timespecx64, __INT64_TYPE__, __UINT64_TYPE__)
};
__TIMESPEC_CXX_SUPPORT2(8, struct timespecx64, __INT64_TYPE__, __UINT64_TYPE__)

#ifdef __timespecx64_alt
struct __timespecx64_alt {
	__INT64_TYPE__  tv_sec;   /* Seconds */
#ifdef __USE_KOS_ALTERATIONS
	__UINT64_TYPE__ tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#else /* __USE_KOS_ALTERATIONS */
	__INT64_TYPE__  tv_nsec;  /* Nano seconds (< 1000000000 == 1_000_000_000) */
#endif /* !__USE_KOS_ALTERATIONS */
	__TIMESPEC_CXX_SUPPORT(8, struct __timespecx64_alt, __INT64_TYPE__, __UINT64_TYPE__)
};
__TIMESPEC_CXX_SUPPORT2(8, struct __timespecx64_alt, __INT64_TYPE__, __UINT64_TYPE__)
#undef __timespecx64_alt
#endif /* __timespecx64_alt */

__TIMESPEC_CXX_DECL_END
__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef timespecx64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_TIMESPECX64
#undef __PRIVATE_DID_PUSH_TIMESPECX64
#pragma pop_macro("timespecx64")
#endif /* __PRIVATE_DID_PUSH_TIMESPECX64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_GENERIC_TIMESPEC64_H */
