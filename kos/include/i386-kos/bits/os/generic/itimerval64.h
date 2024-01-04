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
#ifndef _I386_KOS_BITS_OS_GENERIC_ITIMERVAL64_H
#define _I386_KOS_BITS_OS_GENERIC_ITIMERVAL64_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include "timeval64.h"

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef itimervalx64
#pragma push_macro("itimervalx64")
#define __PRIVATE_DID_PUSH_ITIMERVALX64
#endif /* itimervalx64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x64(
	linkIf:    "defined(__x86_64__)",
	name:      "itimerval",
	name64:    "itimervalx64",
	altname64: "__itimervalx64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_TIME64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef itimervalx64
#ifndef __x86_64__
#define itimervalx64 __itimervalx64
#else /* !__x86_64__ */
#include <features.h>
#define __OFFSET_ITIMERVAL_INTERVAL   __OFFSET_ITIMERVALX64_INTERVAL
#define __OFFSET_ITIMERVAL_VALUE      __OFFSET_ITIMERVALX64_VALUE
#define __SIZEOF_ITIMERVAL            __SIZEOF_ITIMERVALX64
#define __ALIGNOF_ITIMERVAL           __ALIGNOF_ITIMERVALX64
#define __OFFSET_ITIMERVAL32_INTERVAL __OFFSET_ITIMERVALX64_INTERVAL
#define __OFFSET_ITIMERVAL32_VALUE    __OFFSET_ITIMERVALX64_VALUE
#define __SIZEOF_ITIMERVAL32          __SIZEOF_ITIMERVALX64
#define __ALIGNOF_ITIMERVAL32         __ALIGNOF_ITIMERVALX64
#define __OFFSET_ITIMERVAL64_INTERVAL __OFFSET_ITIMERVALX64_INTERVAL
#define __OFFSET_ITIMERVAL64_VALUE    __OFFSET_ITIMERVALX64_VALUE
#define __SIZEOF_ITIMERVAL64          __SIZEOF_ITIMERVALX64
#define __ALIGNOF_ITIMERVAL64         __ALIGNOF_ITIMERVALX64
#define itimervalx64                  itimerval
#define __itimervalx64                itimerval
#define __itimerval32                 itimerval
#define __itimerval_alt               itimerval
#define _ITIMERVAL_MATCHES_ITIMERVAL64 1
#ifdef __USE_KOS
#define itimerval32 itimerval
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_STRUCT64_MACRO
#define itimerval64   itimerval
#define __itimerval64 itimerval
#else /* __USE_STRUCT64_MACRO */
#define __itimervalx64_alt itimerval64
#define __itimerval64      itimerval64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_TIME64 */
#define __itimerval64 itimerval
#endif /* !__USE_TIME64 */
#define __itimerval_defined
#endif /* __x86_64__ */
/*[[[end]]]*/

#define __OFFSET_ITIMERVALX64_INTERVAL 0
#define __OFFSET_ITIMERVALX64_VALUE    16
#define __SIZEOF_ITIMERVALX64          32
#define __ALIGNOF_ITIMERVALX64         __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("it_interval")
#pragma push_macro("it_value")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef it_interval
#undef it_value

/* itimerval for x86_64 */
struct itimervalx64 /*[PREFIX(it_)]*/ {
	struct __timevalx64 it_interval;
	struct __timevalx64 it_value;
};

#ifdef __itimervalx64_alt
struct __itimervalx64_alt {
	struct __timevalx64 it_interval;
	struct __timevalx64 it_value;
};
#undef __itimervalx64_alt
#endif /* __itimervalx64_alt */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("it_value")
#pragma pop_macro("it_interval")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef itimervalx64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_ITIMERVALX64
#undef __PRIVATE_DID_PUSH_ITIMERVALX64
#pragma pop_macro("itimervalx64")
#endif /* __PRIVATE_DID_PUSH_ITIMERVALX64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_GENERIC_ITIMERVAL64_H */
