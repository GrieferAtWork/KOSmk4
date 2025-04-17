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
/*!replace_with_include <bits/os/flock.h>*/
#ifndef _I386_KOS_BITS_OS_KOS_FLOCK64_H
#define _I386_KOS_BITS_OS_KOS_FLOCK64_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef flockx64
#pragma push_macro("flockx64")
#define __PRIVATE_DID_PUSH_FLOCKX64
#endif /* flockx64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/*[[[autogen:wrap3264_x64(
	linkIf:    "defined(__x86_64__)",
	name:      "flock",
	name64:    "flockx64",
	altname64: "__flockx64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_LARGEFILE64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef flockx64
#ifndef __x86_64__
#define flockx64 __flockx64
#else /* !__x86_64__ */
#include <features.h>
#define __OFFSET_FLOCK_TYPE     __OFFSET_FLOCKX64_TYPE
#define __OFFSET_FLOCK_WHENCE   __OFFSET_FLOCKX64_WHENCE
#define __OFFSET_FLOCK_START    __OFFSET_FLOCKX64_START
#define __OFFSET_FLOCK_LEN      __OFFSET_FLOCKX64_LEN
#define __OFFSET_FLOCK_PID      __OFFSET_FLOCKX64_PID
#define __SIZEOF_FLOCK          __SIZEOF_FLOCKX64
#define __OFFSET_FLOCK32_TYPE   __OFFSET_FLOCKX64_TYPE
#define __OFFSET_FLOCK32_WHENCE __OFFSET_FLOCKX64_WHENCE
#define __OFFSET_FLOCK32_START  __OFFSET_FLOCKX64_START
#define __OFFSET_FLOCK32_LEN    __OFFSET_FLOCKX64_LEN
#define __OFFSET_FLOCK32_PID    __OFFSET_FLOCKX64_PID
#define __SIZEOF_FLOCK32        __SIZEOF_FLOCKX64
#define __OFFSET_FLOCK64_TYPE   __OFFSET_FLOCKX64_TYPE
#define __OFFSET_FLOCK64_WHENCE __OFFSET_FLOCKX64_WHENCE
#define __OFFSET_FLOCK64_START  __OFFSET_FLOCKX64_START
#define __OFFSET_FLOCK64_LEN    __OFFSET_FLOCKX64_LEN
#define __OFFSET_FLOCK64_PID    __OFFSET_FLOCKX64_PID
#define __SIZEOF_FLOCK64        __SIZEOF_FLOCKX64
#define flockx64                flock
#define __flockx64              flock
#define __flock32               flock
#define __flock_alt             flock
#define _FLOCK_MATCHES_FLOCK64 1
#ifdef __USE_KOS
#define flock32 flock
#endif /* __USE_KOS */
#ifdef __USE_LARGEFILE64
#ifdef __USE_STRUCT64_MACRO
#define flock64   flock
#define __flock64 flock
#else /* __USE_STRUCT64_MACRO */
#define __flockx64_alt flock64
#define __flock64      flock64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_LARGEFILE64 */
#define __flock64 flock
#endif /* !__USE_LARGEFILE64 */
#define __flock_defined
#endif /* __x86_64__ */
/*[[[end]]]*/

#define __OFFSET_FLOCKX64_TYPE   0
#define __OFFSET_FLOCKX64_WHENCE 2
#define __OFFSET_FLOCKX64_START  8
#define __OFFSET_FLOCKX64_LEN    16
#define __OFFSET_FLOCKX64_PID    24
#define __SIZEOF_FLOCKX64        32

#ifdef __CC__
__DECL_BEGIN

/* flock for x86_64 */
struct flockx64 /*[PREFIX(l_)]*/ {
	__INT16_TYPE__   l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK. */
	__INT16_TYPE__   l_whence; /* Where `l_start' is relative to (like `lseek'). */
	__UINT32_TYPE__ __l_pad;   /* ... */
#ifdef __USE_KOS_ALTERATIONS
	__ULONG64_TYPE__ l_start;  /* Offset where the lock begins. */
	__ULONG64_TYPE__ l_len;    /* Size of the locked area; zero means until EOF. */
#else /* __USE_KOS_ALTERATIONS */
	__LONG64_TYPE__  l_start;  /* Offset where the lock begins. */
	__LONG64_TYPE__  l_len;    /* Size of the locked area; zero means until EOF. */
#endif /* !__USE_KOS_ALTERATIONS */
	__INT32_TYPE__   l_pid;    /* Process holding the lock. */
	__UINT32_TYPE__ __l_pad2;  /* ... */
};

#ifdef __flockx64_alt
struct __flockx64_alt {
	__INT16_TYPE__   l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK. */
	__INT16_TYPE__   l_whence; /* Where `l_start' is relative to (like `lseek'). */
	__UINT32_TYPE__ __l_pad;   /* ... */
#ifdef __USE_KOS_ALTERATIONS
	__ULONG64_TYPE__ l_start;  /* Offset where the lock begins. */
	__ULONG64_TYPE__ l_len;    /* Size of the locked area; zero means until EOF. */
#else /* __USE_KOS_ALTERATIONS */
	__LONG64_TYPE__  l_start;  /* Offset where the lock begins. */
	__LONG64_TYPE__  l_len;    /* Size of the locked area; zero means until EOF. */
#endif /* !__USE_KOS_ALTERATIONS */
	__INT32_TYPE__   l_pid;    /* Process holding the lock. */
	__UINT32_TYPE__ __l_pad2;  /* ... */
};
#undef __flockx64_alt
#endif /* __flockx64_alt */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef flockx64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_FLOCKX64
#undef __PRIVATE_DID_PUSH_FLOCKX64
#pragma pop_macro("flockx64")
#endif /* __PRIVATE_DID_PUSH_FLOCKX64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#endif /* !_I386_KOS_BITS_OS_KOS_FLOCK64_H */
