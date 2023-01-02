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
#ifndef _I386_KOS_BITS_OS_GENERIC_ITIMERSPEC32_H
#define _I386_KOS_BITS_OS_GENERIC_ITIMERSPEC32_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include "timespec32.h"

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef itimerspecx32
#pragma push_macro("itimerspecx32")
#define __PRIVATE_DID_PUSH_ITIMERSPECX32
#endif /* itimerspecx32 */
#ifdef itimerspecx32_64
#pragma push_macro("itimerspecx32_64")
#define __PRIVATE_DID_PUSH_ITIMERSPECX32_64
#endif /* itimerspecx32_64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x32_and_x32_64(
	linkIf:    "defined(__i386__) && !defined(__x86_64__)",
	name:      "itimerspec",
	name32:    "itimerspecx32",
	name64:    "itimerspecx32_64",
	altname64: "__itimerspecx32_64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	link64If:  "defined(__USE_TIME_BITS64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef itimerspecx32
#undef itimerspecx32_64
#if !defined(__i386__) || defined(__x86_64__)
#define itimerspecx32    __itimerspecx32
#define itimerspecx32_64 __itimerspecx32_64
#else /* !__i386__ || __x86_64__ */
#include <features.h>
#ifdef __USE_TIME_BITS64
/* Configure:
 *   - `itimerspecx32_64' as `itimerspec'
 *   - `itimerspecx32' as `__itimerspec32' */
#define itimerspecx32      __itimerspec32
#define itimerspecx32_64   itimerspec
#define __itimerspecx32    __itimerspec32
#define __itimerspecx32_64 itimerspec
#define __itimerspec32     __itimerspec32
#define __itimerspec_alt   __itimerspec32
#ifdef __USE_KOS
#define itimerspec32 __itimerspec32
#endif /* !__USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define itimerspec64   itimerspec
#define __itimerspec64 itimerspec
#else /* __USE_STRUCT64_MACRO */
#define __itimerspecx32_64_alt itimerspec64
#define __itimerspec64         itimerspec64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __itimerspec64 itimerspec
#endif /* !__USE_TIME64 */

#define __OFFSET_ITIMERSPEC_INTERVAL __OFFSET_ITIMERSPECX32_64_INTERVAL
#define __OFFSET_ITIMERSPEC_VALUE    __OFFSET_ITIMERSPECX32_64_VALUE
#define __SIZEOF_ITIMERSPEC          __SIZEOF_ITIMERSPECX32_64
#define __ALIGNOF_ITIMERSPEC         __ALIGNOF_ITIMERSPECX32_64

#else /* __USE_TIME_BITS64 */
/* Configure:
 *   - `itimerspecx32_64' as `itimerspec64' or `__itimerspec64'
 *   - `itimerspecx32' as `itimerspec' */
#define itimerspecx32   itimerspec
#define __itimerspec32  itimerspec
#define __itimerspecx32 itimerspec
#ifdef __USE_KOS
#define itimerspec32 itimerspec
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#define __itimerspecx32_64 itimerspec64
#define itimerspecx32_64   itimerspec64
#define __itimerspec64     itimerspec64
#define __itimerspec_alt   itimerspec64
#else /* __USE_TIME64 */
#define __itimerspecx32_64 __itimerspec64
#define itimerspecx32_64   __itimerspec64
#define __itimerspec64     __itimerspec64
#define __itimerspec_alt   __itimerspec64
#endif /* !__USE_TIME64 */

#define __OFFSET_ITIMERSPEC_INTERVAL __OFFSET_ITIMERSPECX32_INTERVAL
#define __OFFSET_ITIMERSPEC_VALUE    __OFFSET_ITIMERSPECX32_VALUE
#define __SIZEOF_ITIMERSPEC          __SIZEOF_ITIMERSPECX32
#define __ALIGNOF_ITIMERSPEC         __ALIGNOF_ITIMERSPECX32

#endif /* !__USE_TIME_BITS64 */

#define __OFFSET_ITIMERSPEC32_INTERVAL __OFFSET_ITIMERSPECX32_INTERVAL
#define __OFFSET_ITIMERSPEC32_VALUE    __OFFSET_ITIMERSPECX32_VALUE
#define __SIZEOF_ITIMERSPEC32          __SIZEOF_ITIMERSPECX32
#define __ALIGNOF_ITIMERSPEC32         __ALIGNOF_ITIMERSPECX32
#define __OFFSET_ITIMERSPEC64_INTERVAL __OFFSET_ITIMERSPECX32_64_INTERVAL
#define __OFFSET_ITIMERSPEC64_VALUE    __OFFSET_ITIMERSPECX32_64_VALUE
#define __SIZEOF_ITIMERSPEC64          __SIZEOF_ITIMERSPECX32_64
#define __ALIGNOF_ITIMERSPEC64         __ALIGNOF_ITIMERSPECX32_64

#define __itimerspec_defined
#endif /* __i386__ && !__x86_64__*/
/*[[[end]]]*/

#define __OFFSET_ITIMERSPECX32_INTERVAL    0
#define __OFFSET_ITIMERSPECX32_VALUE       8
#define __SIZEOF_ITIMERSPECX32             16
#define __ALIGNOF_ITIMERSPECX32            __ALIGNOF_INT32__
#define __OFFSET_ITIMERSPECX32_64_INTERVAL 0
#define __OFFSET_ITIMERSPECX32_64_VALUE    16
#define __SIZEOF_ITIMERSPECX32_64          32
#define __ALIGNOF_ITIMERSPECX32_64         __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("it_interval")
#pragma push_macro("it_value")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef it_interval
#undef it_value

/* 32-bit itimerspec for i386 */
struct itimerspecx32 /*[PREFIX(it_)]*/ {
	struct __timespecx32 it_interval;
	struct __timespecx32 it_value;
};

/* 64-bit itimerspec for i386 */
struct itimerspecx32_64 /*[PREFIX(it_)]*/ {
	struct __timespecx32_64 it_interval;
	struct __timespecx32_64 it_value;
};

#ifdef __itimerspecx32_64_alt
struct __itimerspecx32_64_alt {
	struct __timespecx32_64 it_interval;
	struct __timespecx32_64 it_value;
};
#undef __itimerspecx32_64_alt
#endif /* __itimerspecx32_64_alt */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("it_value")
#pragma pop_macro("it_interval")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef itimerspecx32
#undef itimerspecx32_64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_ITIMERSPECX32_64
#undef __PRIVATE_DID_PUSH_ITIMERSPECX32_64
#pragma pop_macro("itimerspecx32_64")
#endif /* __PRIVATE_DID_PUSH_ITIMERSPECX32_64 */
#ifdef __PRIVATE_DID_PUSH_ITIMERSPECX32
#undef __PRIVATE_DID_PUSH_ITIMERSPECX32
#pragma pop_macro("itimerspecx32")
#endif /* __PRIVATE_DID_PUSH_ITIMERSPECX32 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_GENERIC_ITIMERSPEC32_H */
