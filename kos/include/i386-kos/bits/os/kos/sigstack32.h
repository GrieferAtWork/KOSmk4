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
#ifndef _I386_KOS_BITS_OS_KOS_SIGSTACK32_H
#define _I386_KOS_BITS_OS_KOS_SIGSTACK32_H 1

/* File:
 *    <i386-kos/bits/os/kos/sigstack32.h>
 *
 * Definitions:
 *    - struct __sigstackx32 { ... };
 *    - struct __sigaltstackx32 { ... };
 * #if !defined(__x86_64__) && defined(__i386__)
 *    - struct sigstack { ... };
 *    - struct sigaltstack { ... };
 * #endif
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#if !defined(__x86_64__) && defined(__i386__)

#define __OFFSET_SIGSTACK_SP       __OFFSET_SIGSTACKX32_SP
#define __OFFSET_SIGSTACK_ONSTACK  __OFFSET_SIGSTACKX32_ONSTACK
#define __SIZEOF_SIGSTACK          __SIZEOF_SIGSTACKX32
#define __sigstackx32              sigstack

#define __OFFSET_SIGALTSTACK_SP    __OFFSET_SIGALTSTACKX32_SP
#define __OFFSET_SIGALTSTACK_FLAGS __OFFSET_SIGALTSTACKX32_FLAGS
#define __OFFSET_SIGALTSTACK_SIZE  __OFFSET_SIGALTSTACKX32_SIZE
#define __SIZEOF_SIGALTSTACK       __SIZEOF_SIGALTSTACKX32
#define __sigaltstackx32           sigaltstack

#endif /* !__x86_64__ && __i386__ */

#define __OFFSET_SIGSTACKX32_SP      0
#define __OFFSET_SIGSTACKX32_ONSTACK 4
#define __SIZEOF_SIGSTACKX32         8

#ifdef __CC__
/* Structure describing a signal stack (obsolete). */
struct __sigstackx32 /*[NAME(sigstackx32)][PREFIX(ss_)]*/ {
	__HYBRID_PTR32(void) ss_sp;      /* Signal stack pointer. */
	int                  ss_onstack; /* Nonzero if executing on this stack. */
#if __SIZEOF_INT__ < 4
	__BYTE_TYPE__ __ss_pad[4 - __SIZEOF_INT__];
#endif /* 4 > __SIZEOF_INT__ */
};
#endif /* __CC__ */


#define __OFFSET_SIGALTSTACKX32_SP    0
#define __OFFSET_SIGALTSTACKX32_FLAGS 4
#define __OFFSET_SIGALTSTACKX32_SIZE  8
#define __SIZEOF_SIGALTSTACKX32       12

#ifdef __CC__
/* Alternate, preferred interface. */
struct __sigaltstackx32 /*[NAME(sigaltstackx32)][PREFIX(ss_)]*/ {
	__HYBRID_PTR32(void) ss_sp;    /* Signal stack pointer. */
	__INT32_TYPE__       ss_flags; /* Set of `SS_*' from `<asm/os/sigstack.h>' */
	__ULONG32_TYPE__     ss_size;  /* Signal stack size (in bytes) */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BITS_OS_KOS_SIGSTACK32_H */
