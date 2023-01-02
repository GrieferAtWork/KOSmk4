/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_OS_GENERIC_SIGSET_WITH_SIZE64_H
#define _I386_KOS_BITS_OS_GENERIC_SIGSET_WITH_SIZE64_H 1

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

#ifdef __x86_64__
#define __sigset_with_sizex64            sigset_with_size
#define __OFFSET_SIGSET_WITH_SIZE_SIGSET __OFFSET_SIGSET_WITH_SIZEX64_SIGSET
#define __OFFSET_SIGSET_WITH_SIZE_SIGSIZ __OFFSET_SIGSET_WITH_SIZEX64_SIGSIZ
#define __SIZEOF_SIGSET_WITH_SIZE        __SIZEOF_SIGSET_WITH_SIZEX64
#define __ALIGNOF_SIGSET_WITH_SIZE       __ALIGNOF_SIGSET_WITH_SIZEX64
#endif /* __x86_64__ */

#define __OFFSET_SIGSET_WITH_SIZEX64_SIGSET  0
#define __OFFSET_SIGSET_WITH_SIZEX64_SIGSIZ  8
#define __SIZEOF_SIGSET_WITH_SIZEX64         16
#define __ALIGNOF_SIGSET_WITH_SIZEX64        __ALIGNOF_INT64__

#ifdef __CC__
__DECL_BEGIN

struct __sigset_with_sizex64 /*[NAME(sigset_with_sizex64)][PREFIX(sws_)]*/ {
	__HYBRID_PTR64(struct __sigset_struct) sws_sigset; /* [0..sws_sigsiz] Signal set. */
	__UINT64_TYPE__                        sws_sigsiz; /* Signal set size. */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_GENERIC_SIGSET_WITH_SIZE64_H */
