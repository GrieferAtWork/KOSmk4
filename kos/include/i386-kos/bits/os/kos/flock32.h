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
#ifndef _I386_KOS_BITS_OS_KOS_FLOCK32_H
#define _I386_KOS_BITS_OS_KOS_FLOCK32_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef flockx32
#pragma push_macro("flockx32")
#define __PRIVATE_DID_PUSH_FLOCKX32
#endif /* flockx32 */
#ifdef flockx32_64
#pragma push_macro("flockx32_64")
#define __PRIVATE_DID_PUSH_FLOCKX32_64
#endif /* flockx32_64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


/*[[[autogen:wrap3264_x32_and_x32_64(
	linkIf:    "defined(__i386__) && !defined(__x86_64__)",
	name:      "flock",
	name32:    "flockx32",
	name64:    "flockx32_64",
	altname64: "__flockx32_64_alt",
	name32If:  "defined(__USE_KOS)",
	name64If:  "defined(__USE_LARGEFILE64)",
	link64If:  "defined(__USE_FILE_OFFSET64)",
	macro64If: "defined(__USE_STRUCT64_MACRO)",
)]]]*/
#undef flockx32
#undef flockx32_64
#if !defined(__i386__) || defined(__x86_64__)
#define flockx32    __flockx32
#define flockx32_64 __flockx32_64
#else /* !__i386__ || __x86_64__ */
#include <features.h>
#ifdef __USE_FILE_OFFSET64
/* Configure:
 *   - `flockx32_64' as `flock'
 *   - `flockx32' as `__flock32' */
#define flockx32      __flock32
#define flockx32_64   flock
#define __flockx32    __flock32
#define __flockx32_64 flock
#define __flock32     __flock32
#define __flock_alt   __flock32
#ifdef __USE_KOS
#define flock32 __flock32
#endif /* !__USE_KOS */
#ifdef __USE_LARGEFILE64
#ifdef __USE_STRUCT64_MACRO
#define flock64   flock
#define __flock64 flock
#else /* __USE_STRUCT64_MACRO */
#define __flockx32_64_alt flock64
#define __flock64         flock64
#endif /* !__USE_STRUCT64_MACRO */
#else /* __USE_LARGEFILE64 */
#define __flock64 flock
#endif /* !__USE_LARGEFILE64 */

#define __OFFSET_FLOCK_TYPE   __OFFSET_FLOCKX32_64_TYPE
#define __OFFSET_FLOCK_WHENCE __OFFSET_FLOCKX32_64_WHENCE
#define __OFFSET_FLOCK_START  __OFFSET_FLOCKX32_64_START
#define __OFFSET_FLOCK_LEN    __OFFSET_FLOCKX32_64_LEN
#define __OFFSET_FLOCK_PID    __OFFSET_FLOCKX32_64_PID
#define __SIZEOF_FLOCK        __SIZEOF_FLOCKX32_64

#else /* __USE_FILE_OFFSET64 */
/* Configure:
 *   - `flockx32_64' as `flock64' or `__flock64'
 *   - `flockx32' as `flock' */
#define flockx32   flock
#define __flock32  flock
#define __flockx32 flock
#ifdef __USE_KOS
#define flock32 flock
#endif /* __USE_KOS */
#ifdef __USE_LARGEFILE64
#define __flockx32_64 flock64
#define flockx32_64   flock64
#define __flock64     flock64
#define __flock_alt   flock64
#else /* __USE_LARGEFILE64 */
#define __flockx32_64 __flock64
#define flockx32_64   __flock64
#define __flock64     __flock64
#define __flock_alt   __flock64
#endif /* !__USE_LARGEFILE64 */

#define __OFFSET_FLOCK_TYPE   __OFFSET_FLOCKX32_TYPE
#define __OFFSET_FLOCK_WHENCE __OFFSET_FLOCKX32_WHENCE
#define __OFFSET_FLOCK_START  __OFFSET_FLOCKX32_START
#define __OFFSET_FLOCK_LEN    __OFFSET_FLOCKX32_LEN
#define __OFFSET_FLOCK_PID    __OFFSET_FLOCKX32_PID
#define __SIZEOF_FLOCK        __SIZEOF_FLOCKX32

#endif /* !__USE_FILE_OFFSET64 */

#define __OFFSET_FLOCK32_TYPE   __OFFSET_FLOCKX32_TYPE
#define __OFFSET_FLOCK32_WHENCE __OFFSET_FLOCKX32_WHENCE
#define __OFFSET_FLOCK32_START  __OFFSET_FLOCKX32_START
#define __OFFSET_FLOCK32_LEN    __OFFSET_FLOCKX32_LEN
#define __OFFSET_FLOCK32_PID    __OFFSET_FLOCKX32_PID
#define __SIZEOF_FLOCK32        __SIZEOF_FLOCKX32
#define __OFFSET_FLOCK64_TYPE   __OFFSET_FLOCKX32_64_TYPE
#define __OFFSET_FLOCK64_WHENCE __OFFSET_FLOCKX32_64_WHENCE
#define __OFFSET_FLOCK64_START  __OFFSET_FLOCKX32_64_START
#define __OFFSET_FLOCK64_LEN    __OFFSET_FLOCKX32_64_LEN
#define __OFFSET_FLOCK64_PID    __OFFSET_FLOCKX32_64_PID
#define __SIZEOF_FLOCK64        __SIZEOF_FLOCKX32_64

#define __flock_defined
#endif /* __i386__ && !__x86_64__*/
/*[[[end]]]*/

#define __OFFSET_FLOCKX32_TYPE   0
#define __OFFSET_FLOCKX32_WHENCE 2
#define __OFFSET_FLOCKX32_START  4
#define __OFFSET_FLOCKX32_LEN    8
#define __OFFSET_FLOCKX32_PID    12
#define __SIZEOF_FLOCKX32        16

#define __OFFSET_FLOCKX32_64_TYPE   0
#define __OFFSET_FLOCKX32_64_WHENCE 2
#define __OFFSET_FLOCKX32_64_START  4
#define __OFFSET_FLOCKX32_64_LEN    12
#define __OFFSET_FLOCKX32_64_PID    20
#define __SIZEOF_FLOCKX32_64        24

#ifdef __CC__
__DECL_BEGIN

/* 32-bit flock for i386 */
struct flockx32 /*[PREFIX(l_)]*/ {
	__INT16_TYPE__   l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK. */
	__INT16_TYPE__   l_whence; /* Where `l_start' is relative to (like `lseek'). */
#ifdef __USE_KOS_ALTERATIONS
	__ULONG32_TYPE__ l_start;  /* Offset where the lock begins. */
	__ULONG32_TYPE__ l_len;    /* Size of the locked area; zero means until EOF. */
#else /* __USE_KOS_ALTERATIONS */
	__LONG32_TYPE__  l_start;  /* Offset where the lock begins. */
	__LONG32_TYPE__  l_len;    /* Size of the locked area; zero means until EOF. */
#endif /* !__USE_KOS_ALTERATIONS */
	__INT32_TYPE__   l_pid;    /* Process holding the lock. */
};

/* 64-bit flock for i386 */
struct __ATTR_PACKED __ATTR_ALIGNED(4) flockx32_64 /*[PREFIX(l_)]*/ {
	__INT16_TYPE__   l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK. */
	__INT16_TYPE__   l_whence; /* Where `l_start' is relative to (like `lseek'). */
#ifdef __USE_KOS_ALTERATIONS
	__ULONG64_TYPE__ l_start;  /* Offset where the lock begins. */
	__ULONG64_TYPE__ l_len;    /* Size of the locked area; zero means until EOF. */
#else /* __USE_KOS_ALTERATIONS */
	__LONG64_TYPE__  l_start;  /* Offset where the lock begins. */
	__LONG64_TYPE__  l_len;    /* Size of the locked area; zero means until EOF. */
#endif /* !__USE_KOS_ALTERATIONS */
	__INT32_TYPE__   l_pid;    /* Process holding the lock. */
};

#ifdef __flockx32_64_alt
struct __ATTR_PACKED __ATTR_ALIGNED(4) __flockx32_64_alt {
	__INT16_TYPE__   l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK. */
	__INT16_TYPE__   l_whence; /* Where `l_start' is relative to (like `lseek'). */
#ifdef __USE_KOS_ALTERATIONS
	__ULONG64_TYPE__ l_start;  /* Offset where the lock begins. */
	__ULONG64_TYPE__ l_len;    /* Size of the locked area; zero means until EOF. */
#else /* __USE_KOS_ALTERATIONS */
	__LONG64_TYPE__  l_start;  /* Offset where the lock begins. */
	__LONG64_TYPE__  l_len;    /* Size of the locked area; zero means until EOF. */
#endif /* !__USE_KOS_ALTERATIONS */
	__INT32_TYPE__   l_pid;    /* Process holding the lock. */
};
#undef __flockx32_64_alt
#endif /* __flockx32_64_alt */

__DECL_END
#endif /* __CC__ */

#ifndef __USE_KOS_KERNEL
#undef flockx32
#undef flockx32_64
#endif /* !__USE_KOS_KERNEL */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#ifdef __PRIVATE_DID_PUSH_FLOCKX32_64
#undef __PRIVATE_DID_PUSH_FLOCKX32_64
#pragma pop_macro("flockx32_64")
#endif /* __PRIVATE_DID_PUSH_FLOCKX32_64 */
#ifdef __PRIVATE_DID_PUSH_FLOCKX32
#undef __PRIVATE_DID_PUSH_FLOCKX32
#pragma pop_macro("flockx32")
#endif /* __PRIVATE_DID_PUSH_FLOCKX32 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


#endif /* !_I386_KOS_BITS_OS_KOS_FLOCK32_H */
