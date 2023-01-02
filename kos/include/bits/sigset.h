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
/* (#) Portability: mintlib (/include/bits/sigset.h) */
#ifndef _BITS_SIGSET_H
#define _BITS_SIGSET_H 1

/* NOTE: This file must _always_ be kept for Glibc compatibility! */

#include <__stdinc.h>

#ifndef _SIGSET_H_types
#define _SIGSET_H_types 1
#ifdef __CC__
#include <hybrid/typecore.h>

#include <bits/os/sigset.h>

__DECL_BEGIN

typedef __SIG_ATOMIC_TYPE__ __sig_atomic_t;

#ifndef __SIGSET_NWORDS
#define __SIGSET_NWORDS (__SIZEOF_SIGSET_T__ / __SIZEOF_POINTER__)
#endif /* !__SIGSET_NWORDS */
#define _SIGSET_NWORDS __SIGSET_NWORDS
typedef struct __sigset_struct __sigset_t;

__DECL_END
#endif /* __CC__ */
#endif /* !_SIGSET_H_types */

/* NOTE: The Glibc counterpart of this file also declares some function,
 *       but only does so when <signal.h> was already included.  However
 *       the function that it declares already get defined by <signal.h>
 *       on KOS, so no need to define anything else here :) */

#endif /* !_BITS_SIGSET_H */
