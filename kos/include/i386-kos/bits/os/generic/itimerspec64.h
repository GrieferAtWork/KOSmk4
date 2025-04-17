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
/*!replace_with_include <bits/os/itimerspec.h>*/
#ifndef _I386_KOS_BITS_OS_GENERIC_ITIMERSPEC64_H
#define _I386_KOS_BITS_OS_GENERIC_ITIMERSPEC64_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include "timespec64.h"

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef itimerspecx64
#pragma push_macro("itimerspecx64")
#define __PRIVATE_DID_PUSH_ITIMERSPECX64
#endif /* itimerspecx64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x64(
	linkIf:    "defined(__x86_64__)",
	name:      "itimerspec",
	name64:    "itimerspecx64",
	altname64: "__itimerspecx64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef itimerspecx64
#ifndef __x86_64__
#define itimerspecx64 __itimerspecx64
#else /* !__x86_64__ */
#include <features.h>
#define __OFFSET_ITIMERSPEC_INTERVAL   __OFFSET_ITIMERSPECX64_INTERVAL
#define __OFFSET_ITIMERSPEC_VALUE      __OFFSET_ITIMERSPECX64_VALUE
#define __SIZEOF_ITIMERSPEC            __SIZEOF_ITIMERSPECX64
#define __ALIGNOF_ITIMERSPEC           __ALIGNOF_ITIMERSPECX64
#define __OFFSET_ITIMERSPEC32_INTERVAL __OFFSET_ITIMERSPECX64_INTERVAL
#define __OFFSET_ITIMERSPEC32_VALUE    __OFFSET_ITIMERSPECX64_VALUE
#define __SIZEOF_ITIMERSPEC32          __SIZEOF_ITIMERSPECX64
#define __ALIGNOF_ITIMERSPEC32         __ALIGNOF_ITIMERSPECX64
#define __OFFSET_ITIMERSPEC64_INTERVAL __OFFSET_ITIMERSPECX64_INTERVAL
#define __OFFSET_ITIMERSPEC64_VALUE    __OFFSET_ITIMERSPECX64_VALUE
#define __SIZEOF_ITIMERSPEC64          __SIZEOF_ITIMERSPECX64
#define __ALIGNOF_ITIMERSPEC64         __ALIGNOF_ITIMERSPECX64
#define itimerspecx64                  itimerspec
#define __itimerspecx64                itimerspec
#define __itimerspec32                 itimerspec
#define __itimerspec_alt               itimerspec
#define _ITIMERSPEC_MATCHES_ITIMERSPEC64 1
#ifdef __USE_KOS
#define itimerspec32 itimerspec
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define itimerspec64   itimerspec
#define __itimerspec64 itimerspec
#else /* __USE_STRUCT64_MACRO */
#define __itimerspecx64_alt itimerspec64
#define __itimerspec64      itimerspec64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __itimerspec64 itimerspec
#endif /* !__USE_TIME64 */
#define __itimerspec_defined
#endif /* __x86_64__ */
/*[[[end]]]*/

#define __OFFSET_ITIMERSPECX64_INTERVAL 0
#define __OFFSET_ITIMERSPECX64_VALUE    16
#define __SIZEOF_ITIMERSPECX64          32
#define __ALIGNOF_ITIMERSPECX64         __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("it_interval")
#pragma push_macro("it_value")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef it_interval
#undef it_value

/* itimerspec for x86_64 */
struct itimerspecx64 /*[PREFIX(it_)]*/ {
	struct __timespecx64 it_interval;
	struct __timespecx64 it_value;
};

#ifdef __itimerspecx64_alt
struct __itimerspecx64_alt {
	struct __timespecx64 it_interval;
	struct __timespecx64 it_value;
};
#undef __itimerspecx64_alt
#endif /* __itimerspecx64_alt */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("it_value")
#pragma pop_macro("it_interval")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef itimerspecx64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_ITIMERSPECX64
#undef __PRIVATE_DID_PUSH_ITIMERSPECX64
#pragma pop_macro("itimerspecx64")
#endif /* __PRIVATE_DID_PUSH_ITIMERSPECX64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_GENERIC_ITIMERSPEC64_H */
