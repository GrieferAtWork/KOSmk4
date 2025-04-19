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
/*!replace_with_include <sys/resource.h>*/
#ifndef _I386_KOS_BITS_OS_KOS_RLIMIT32_H
#define _I386_KOS_BITS_OS_KOS_RLIMIT32_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef rlimitx32
#pragma push_macro("rlimitx32")
#define __PRIVATE_DID_PUSH_RLIMITX32
#endif /* rlimitx32 */
#ifdef rlimitx32_64
#pragma push_macro("rlimitx32_64")
#define __PRIVATE_DID_PUSH_RLIMITX32_64
#endif /* rlimitx32_64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


/*[[[autogen:wrap3264_x32_and_x32_64(
	linkIf:    "defined(__i386__) && !defined(__x86_64__)",
	name:      "rlimit",
	name32:    "rlimitx32",
	name64:    "rlimitx32_64",
	altname64: "__rlimitx32_64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_LARGEFILE64)",
	link64If:  "defined(__USE_FILE_OFFSET64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef rlimitx32
#undef rlimitx32_64
#if !defined(__i386__) || defined(__x86_64__)
#define rlimitx32    __rlimitx32
#define rlimitx32_64 __rlimitx32_64
#else /* !__i386__ || __x86_64__ */
#include <features.h>
#ifdef __USE_FILE_OFFSET64
/* Configure:
 *   - `rlimitx32_64' as `rlimit'
 *   - `rlimitx32' as `__rlimit32' */
#define rlimitx32      __rlimit32
#define rlimitx32_64   rlimit
#define __rlimitx32    __rlimit32
#define __rlimitx32_64 rlimit
#define __rlimit32     __rlimit32
#define __rlimit_alt   __rlimit32
#ifdef __USE_KOS
#define rlimit32 __rlimit32
#endif /* !__USE_KOS */
#ifdef __USE_LARGEFILE64
#ifdef __USE_STRUCT64_MACRO
#define rlimit64   rlimit
#define __rlimit64 rlimit
#else /* __USE_STRUCT64_MACRO */
#define __rlimitx32_64_alt rlimit64
#define __rlimit64         rlimit64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_LARGEFILE64 */
#define __rlimit64 rlimit
#endif /* !__USE_LARGEFILE64 */

#define __OFFSET_RLIMIT_CUR __OFFSET_RLIMITX32_64_CUR
#define __OFFSET_RLIMIT_MAX __OFFSET_RLIMITX32_64_MAX
#define __SIZEOF_RLIMIT     __SIZEOF_RLIMITX32_64
#define __ALIGNOF_RLIMIT    __ALIGNOF_RLIMITX32_64

#else /* __USE_FILE_OFFSET64 */
/* Configure:
 *   - `rlimitx32_64' as `rlimit64' or `__rlimit64'
 *   - `rlimitx32' as `rlimit' */
#define rlimitx32   rlimit
#define __rlimit32  rlimit
#define __rlimitx32 rlimit
#ifdef __USE_KOS
#define rlimit32 rlimit
#endif /* __USE_KOS */
#ifdef __USE_LARGEFILE64
#define __rlimitx32_64 rlimit64
#define rlimitx32_64   rlimit64
#define __rlimit64     rlimit64
#define __rlimit_alt   rlimit64
#else /* __USE_LARGEFILE64 */
#define __rlimitx32_64 __rlimit64
#define rlimitx32_64   __rlimit64
#define __rlimit64     __rlimit64
#define __rlimit_alt   __rlimit64
#endif /* !__USE_LARGEFILE64 */

#define __OFFSET_RLIMIT_CUR __OFFSET_RLIMITX32_CUR
#define __OFFSET_RLIMIT_MAX __OFFSET_RLIMITX32_MAX
#define __SIZEOF_RLIMIT     __SIZEOF_RLIMITX32
#define __ALIGNOF_RLIMIT    __ALIGNOF_RLIMITX32

#endif /* !__USE_FILE_OFFSET64 */

#define __OFFSET_RLIMIT32_CUR __OFFSET_RLIMITX32_CUR
#define __OFFSET_RLIMIT32_MAX __OFFSET_RLIMITX32_MAX
#define __SIZEOF_RLIMIT32     __SIZEOF_RLIMITX32
#define __ALIGNOF_RLIMIT32    __ALIGNOF_RLIMITX32
#define __OFFSET_RLIMIT64_CUR __OFFSET_RLIMITX32_64_CUR
#define __OFFSET_RLIMIT64_MAX __OFFSET_RLIMITX32_64_MAX
#define __SIZEOF_RLIMIT64     __SIZEOF_RLIMITX32_64
#define __ALIGNOF_RLIMIT64    __ALIGNOF_RLIMITX32_64

#define __rlimit_defined
#endif /* __i386__ && !__x86_64__*/
/*[[[end]]]*/

#define __OFFSET_RLIMITX32_CUR 0
#define __OFFSET_RLIMITX32_MAX 4
#define __SIZEOF_RLIMITX32     8
#define __ALIGNOF_RLIMITX32    __ALIGNOF_INT32__

#define __OFFSET_RLIMITX32_64_CUR 0
#define __OFFSET_RLIMITX32_64_MAX 8
#define __SIZEOF_RLIMITX32_64     16
#define __ALIGNOF_RLIMITX32_64    __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

/* 32-bit rlimit for i386 */
struct rlimitx32 /*[PREFIX(ru_)]*/ {
	__ULONG32_TYPE__ rlim_cur; /* The current (soft) limit. */
	__ULONG32_TYPE__ rlim_max; /* The hard limit. */
};

/* 64-bit rlimit for i386 */
struct rlimitx32_64 /*[PREFIX(ru_)]*/ {
	__ULONG64_TYPE__ rlim_cur; /* The current (soft) limit. */
	__ULONG64_TYPE__ rlim_max; /* The hard limit. */
};

#ifdef __rlimitx32_64_alt
struct __rlimitx32_64_alt {
	__ULONG64_TYPE__ rlim_cur; /* The current (soft) limit. */
	__ULONG64_TYPE__ rlim_max; /* The hard limit. */
};
#undef __rlimitx32_64_alt
#endif /* __rlimitx32_64_alt */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef rlimitx32
#undef rlimitx32_64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_RLIMITX32_64
#undef __PRIVATE_DID_PUSH_RLIMITX32_64
#pragma pop_macro("rlimitx32_64")
#endif /* __PRIVATE_DID_PUSH_RLIMITX32_64 */
#ifdef __PRIVATE_DID_PUSH_RLIMITX32
#undef __PRIVATE_DID_PUSH_RLIMITX32
#pragma pop_macro("rlimitx32")
#endif /* __PRIVATE_DID_PUSH_RLIMITX32 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_KOS_RLIMIT32_H */
