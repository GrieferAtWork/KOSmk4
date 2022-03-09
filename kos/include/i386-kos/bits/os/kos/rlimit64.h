/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_OS_KOS_RLIMIT64_H
#define _I386_KOS_BITS_OS_KOS_RLIMIT64_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef rlimitx64
#pragma push_macro("rlimitx64")
#define __PRIVATE_DID_PUSH_RLIMITX64
#endif /* rlimitx64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x64(
	linkIf:    "defined(__x86_64__)",
	name:      "rlimit",
	name64:    "rlimitx64",
	altname64: "__rlimitx64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_LARGEFILE64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef rlimitx64
#ifndef __x86_64__
#define rlimitx64 __rlimitx64
#else /* !__x86_64__ */
#include <features.h>
#define __OFFSET_RLIMIT_CUR      __OFFSET_RLIMITX64_CUR
#define __OFFSET_RLIMIT_MAX      __OFFSET_RLIMITX64_MAX
#define __SIZEOF_RLIMIT          __SIZEOF_RLIMITX64
#define __ALIGNOF_RLIMIT         __ALIGNOF_RLIMITX64
#define __OFFSET_RLIMIT32_CUR    __OFFSET_RLIMITX64_CUR
#define __OFFSET_RLIMIT32_MAX    __OFFSET_RLIMITX64_MAX
#define __SIZEOF_RLIMIT32        __SIZEOF_RLIMITX64
#define __ALIGNOF_RLIMIT32       __ALIGNOF_RLIMITX64
#define __OFFSET_RLIMIT64_CUR    __OFFSET_RLIMITX64_CUR
#define __OFFSET_RLIMIT64_MAX    __OFFSET_RLIMITX64_MAX
#define __SIZEOF_RLIMIT64        __SIZEOF_RLIMITX64
#define __ALIGNOF_RLIMIT64       __ALIGNOF_RLIMITX64
#define rlimitx64                rlimit
#define __rlimitx64              rlimit
#define __rlimit32               rlimit
#define __rlimit_alt             rlimit
#define _RLIMIT_MATCHES_RLIMIT64 1
#ifdef __USE_KOS
#define rlimit32 rlimit
#endif /* __USE_KOS */
#ifdef __USE_LARGEFILE64
#ifdef __USE_STRUCT64_MACRO
#define rlimit64   rlimit
#define __rlimit64 rlimit
#else /* __USE_STRUCT64_MACRO */
#define __rlimitx64_alt rlimit64
#define __rlimit64      rlimit64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_LARGEFILE64 */
#define __rlimit64 rlimit
#endif /* !__USE_LARGEFILE64 */
#define __rlimit_defined
#endif /* __x86_64__ */
/*[[[end]]]*/


#define __OFFSET_RLIMITX64_CUR 0
#define __OFFSET_RLIMITX64_MAX 8
#define __SIZEOF_RLIMITX64     16
#define __ALIGNOF_RLIMITX64    __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

/* rlimit for x86_64 */
struct rlimitx64 /*[PREFIX(ru_)]*/ {
	__ULONG64_TYPE__ rlim_cur; /* The current (soft) limit. */
	__ULONG64_TYPE__ rlim_max; /* The hard limit. */
};

#ifdef __rlimitx64_alt
struct __rlimitx64_alt {
	__ULONG64_TYPE__ rlim_cur; /* The current (soft) limit. */
	__ULONG64_TYPE__ rlim_max; /* The hard limit. */
};
#undef __rlimitx64_alt
#endif /* __rlimitx64_alt */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef rlimitx64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_RLIMITX64
#undef __PRIVATE_DID_PUSH_RLIMITX64
#pragma pop_macro("rlimitx64")
#endif /* __PRIVATE_DID_PUSH_RLIMITX64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_KOS_RLIMIT64_H */
