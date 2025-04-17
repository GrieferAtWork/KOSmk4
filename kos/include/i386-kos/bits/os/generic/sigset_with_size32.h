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
/*!replace_with_include <bits/os/sigset_with_size.h>*/
#ifndef _I386_KOS_BITS_OS_GENERIC_SIGSET_WITH_SIZE32_H
#define _I386_KOS_BITS_OS_GENERIC_SIGSET_WITH_SIZE32_H 1

/* File:
 *    <i386-kos/bits/os/generic/sigset_with_size.h>
 *
 * Definitions:
 *    - struct sigset_with_size { ... };
 */

#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>

#include <bits/os/sigset.h>
#include <bits/types.h>

#if defined(__i386__) && !defined(__x86_64__)
#define __sigset_with_sizex32            sigset_with_size
#define __OFFSET_SIGSET_WITH_SIZE_SIGSET __OFFSET_SIGSET_WITH_SIZEX32_SIGSET
#define __OFFSET_SIGSET_WITH_SIZE_SIGSIZ __OFFSET_SIGSET_WITH_SIZEX32_SIGSIZ
#define __SIZEOF_SIGSET_WITH_SIZE        __SIZEOF_SIGSET_WITH_SIZEX32
#define __ALIGNOF_SIGSET_WITH_SIZE       __ALIGNOF_SIGSET_WITH_SIZEX32
#endif /* __i386__ && !__x86_64__ */

#define __OFFSET_SIGSET_WITH_SIZEX32_SIGSET 0
#define __OFFSET_SIGSET_WITH_SIZEX32_SIGSIZ 4
#define __SIZEOF_SIGSET_WITH_SIZEX32        8
#define __ALIGNOF_SIGSET_WITH_SIZEX32       4

#ifdef __CC__
__DECL_BEGIN

#ifndef ____sigsetx32_t_defined
#define ____sigsetx32_t_defined
#if __SIZEOF_POINTER__ == 4
#define __sigset_structx32 __sigset_struct
#else /* __SIZEOF_POINTER__ == 4 */
struct __sigset_structx32 {
	__UINT32_TYPE__ __val[__SIZEOF_SIGSET_T__ / 4];
};
#endif /* !__SIZEOF_POINTER__ != 4 */
#endif /* !____sigsetx32_t_defined */

struct __sigset_with_sizex32 /*[NAME(sigset_with_sizex32)][PREFIX(sws_)]*/ {
	__HYBRID_PTR32(struct __sigset_structx32) sws_sigset; /* [0..sws_sigsiz] Signal set. */
	__UINT32_TYPE__                           sws_sigsiz; /* Signal set size. */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_GENERIC_SIGSET_WITH_SIZE32_H */
