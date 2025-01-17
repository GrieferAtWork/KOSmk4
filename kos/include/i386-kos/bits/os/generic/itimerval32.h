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
#ifndef _I386_KOS_BITS_OS_GENERIC_ITIMERVAL32_H
#define _I386_KOS_BITS_OS_GENERIC_ITIMERVAL32_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include "timeval32.h"

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef itimervalx32
#pragma push_macro("itimervalx32")
#define __PRIVATE_DID_PUSH_ITIMERVALX32
#endif /* itimervalx32 */
#ifdef itimervalx32_64
#pragma push_macro("itimervalx32_64")
#define __PRIVATE_DID_PUSH_ITIMERVALX32_64
#endif /* itimervalx32_64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x32_and_x32_64(
	linkIf:    "defined(__i386__) && !defined(__x86_64__)",
	name:      "itimerval",
	name32:    "itimervalx32",
	name64:    "itimervalx32_64",
	altname64: "__itimervalx32_64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	link64If:  "defined(__USE_TIME_BITS64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef itimervalx32
#undef itimervalx32_64
#if !defined(__i386__) || defined(__x86_64__)
#define itimervalx32    __itimervalx32
#define itimervalx32_64 __itimervalx32_64
#else /* !__i386__ || __x86_64__ */
#include <features.h>
#ifdef __USE_TIME_BITS64
/* Configure:
 *   - `itimervalx32_64' as `itimerval'
 *   - `itimervalx32' as `__itimerval32' */
#define itimervalx32      __itimerval32
#define itimervalx32_64   itimerval
#define __itimervalx32    __itimerval32
#define __itimervalx32_64 itimerval
#define __itimerval32     __itimerval32
#define __itimerval_alt   __itimerval32
#ifdef __USE_KOS
#define itimerval32 __itimerval32
#endif /* !__USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define itimerval64   itimerval
#define __itimerval64 itimerval
#else /* __USE_STRUCT64_MACRO */
#define __itimervalx32_64_alt itimerval64
#define __itimerval64         itimerval64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __itimerval64 itimerval
#endif /* !__USE_TIME64 */

#define __OFFSET_ITIMERVAL_INTERVAL __OFFSET_ITIMERVALX32_64_INTERVAL
#define __OFFSET_ITIMERVAL_VALUE    __OFFSET_ITIMERVALX32_64_VALUE
#define __SIZEOF_ITIMERVAL          __SIZEOF_ITIMERVALX32_64
#define __ALIGNOF_ITIMERVAL         __ALIGNOF_ITIMERVALX32_64

#else /* __USE_TIME_BITS64 */
/* Configure:
 *   - `itimervalx32_64' as `itimerval64' or `__itimerval64'
 *   - `itimervalx32' as `itimerval' */
#define itimervalx32   itimerval
#define __itimerval32  itimerval
#define __itimervalx32 itimerval
#ifdef __USE_KOS
#define itimerval32 itimerval
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#define __itimervalx32_64 itimerval64
#define itimervalx32_64   itimerval64
#define __itimerval64     itimerval64
#define __itimerval_alt   itimerval64
#else /* __USE_TIME64 */
#define __itimervalx32_64 __itimerval64
#define itimervalx32_64   __itimerval64
#define __itimerval64     __itimerval64
#define __itimerval_alt   __itimerval64
#endif /* !__USE_TIME64 */

#define __OFFSET_ITIMERVAL_INTERVAL __OFFSET_ITIMERVALX32_INTERVAL
#define __OFFSET_ITIMERVAL_VALUE    __OFFSET_ITIMERVALX32_VALUE
#define __SIZEOF_ITIMERVAL          __SIZEOF_ITIMERVALX32
#define __ALIGNOF_ITIMERVAL         __ALIGNOF_ITIMERVALX32

#endif /* !__USE_TIME_BITS64 */

#define __OFFSET_ITIMERVAL32_INTERVAL __OFFSET_ITIMERVALX32_INTERVAL
#define __OFFSET_ITIMERVAL32_VALUE    __OFFSET_ITIMERVALX32_VALUE
#define __SIZEOF_ITIMERVAL32          __SIZEOF_ITIMERVALX32
#define __ALIGNOF_ITIMERVAL32         __ALIGNOF_ITIMERVALX32
#define __OFFSET_ITIMERVAL64_INTERVAL __OFFSET_ITIMERVALX32_64_INTERVAL
#define __OFFSET_ITIMERVAL64_VALUE    __OFFSET_ITIMERVALX32_64_VALUE
#define __SIZEOF_ITIMERVAL64          __SIZEOF_ITIMERVALX32_64
#define __ALIGNOF_ITIMERVAL64         __ALIGNOF_ITIMERVALX32_64

#define __itimerval_defined
#endif /* __i386__ && !__x86_64__*/
/*[[[end]]]*/

#define __OFFSET_ITIMERVALX32_INTERVAL    0
#define __OFFSET_ITIMERVALX32_VALUE       8
#define __SIZEOF_ITIMERVALX32             16
#define __ALIGNOF_ITIMERVALX32            __ALIGNOF_INT32__
#define __OFFSET_ITIMERVALX32_64_INTERVAL 0
#define __OFFSET_ITIMERVALX32_64_VALUE    16
#define __SIZEOF_ITIMERVALX32_64          32
#define __ALIGNOF_ITIMERVALX32_64         __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("it_interval")
#pragma push_macro("it_value")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef it_interval
#undef it_value

/* 32-bit itimerval for i386 */
struct itimervalx32 /*[PREFIX(it_)]*/ {
	struct __timevalx32 it_interval;
	struct __timevalx32 it_value;
};

/* 64-bit itimerval for i386 */
struct itimervalx32_64 /*[PREFIX(it_)]*/ {
	struct __timevalx32_64 it_interval;
	struct __timevalx32_64 it_value;
};

#ifdef __itimervalx32_64_alt
struct __itimervalx32_64_alt {
	struct __timevalx32_64 it_interval;
	struct __timevalx32_64 it_value;
};
#undef __itimervalx32_64_alt
#endif /* __itimervalx32_64_alt */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("it_value")
#pragma pop_macro("it_interval")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef itimervalx32
#undef itimervalx32_64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_ITIMERVALX32_64
#undef __PRIVATE_DID_PUSH_ITIMERVALX32_64
#pragma pop_macro("itimervalx32_64")
#endif /* __PRIVATE_DID_PUSH_ITIMERVALX32_64 */
#ifdef __PRIVATE_DID_PUSH_ITIMERVALX32
#undef __PRIVATE_DID_PUSH_ITIMERVALX32
#pragma pop_macro("itimervalx32")
#endif /* __PRIVATE_DID_PUSH_ITIMERVALX32 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_GENERIC_ITIMERVAL32_H */
