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
#ifndef _I386_KOS_BITS_OS_KOS_SIGSTACK64_H
#define _I386_KOS_BITS_OS_KOS_SIGSTACK64_H 1

/* File:
 *    <i386-kos/bits/os/kos/sigstack64.h>
 *
 * Definitions:
 *    - struct __sigstackx64 { ... };
 *    - struct __sigaltstackx64 { ... };
 * #ifdef __x86_64__
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

#ifdef __x86_64__

#define __OFFSET_SIGSTACK_SP       __OFFSET_SIGSTACKX64_SP
#define __OFFSET_SIGSTACK_ONSTACK  __OFFSET_SIGSTACKX64_ONSTACK
#define __SIZEOF_SIGSTACK          __SIZEOF_SIGSTACKX64
#define __sigstackx64              sigstack

#define __OFFSET_SIGALTSTACK_SP    __OFFSET_SIGALTSTACKX64_SP
#define __OFFSET_SIGALTSTACK_FLAGS __OFFSET_SIGALTSTACKX64_FLAGS
#define __OFFSET_SIGALTSTACK_SIZE  __OFFSET_SIGALTSTACKX64_SIZE
#define __SIZEOF_SIGALTSTACK       __SIZEOF_SIGALTSTACKX64
#define __sigaltstackx64           sigaltstack

#endif /* __x86_64__ */

#define __OFFSET_SIGSTACKX64_SP      0
#define __OFFSET_SIGSTACKX64_ONSTACK 8
#define __SIZEOF_SIGSTACKX64         16

#ifdef __CC__
/* Structure describing a signal stack (obsolete). */
struct __sigstackx64 /*[NAME(sigstackx64)][PREFIX(ss_)]*/ {
	__HYBRID_PTR64(void) ss_sp;      /* Signal stack pointer. */
	__INT32_TYPE__       ss_onstack; /* Nonzero if executing on this stack. */
	__BYTE_TYPE__      __ss_pad[4];  /* ... */
};
#endif /* __CC__ */


#define __OFFSET_SIGALTSTACKX64_SP    0
#define __OFFSET_SIGALTSTACKX64_FLAGS 8
#define __OFFSET_SIGALTSTACKX64_SIZE  16
#define __SIZEOF_SIGALTSTACKX64       24

#ifdef __CC__
/* Alternate, preferred interface. */
struct __sigaltstackx64 /*[NAME(sigaltstackx64)][PREFIX(ss_)]*/ {
	__HYBRID_PTR64(void) ss_sp;     /* Signal stack pointer. */
	__INT32_TYPE__       ss_flags;  /* Set of `SS_*' from `<asm/os/sigstack.h>' */
	__BYTE_TYPE__      __ss_pad[4]; /* ... */
	__ULONG64_TYPE__     ss_size;   /* Signal stack size (in bytes) */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BITS_OS_KOS_SIGSTACK64_H */
