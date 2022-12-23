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
/* (#) Portability: GNU C Library (/bits/sockaddr.h) */
/* (#) Portability: mintlib       (/include/bits/sockaddr.h) */
#ifndef _BITS_SOCKADDR_H
#define _BITS_SOCKADDR_H 1

/* NOTE: This file must _always_ be kept for Glibc compatibility! */

#include <__stdinc.h>

/* for: `__SOCKADDR_COMMON', `__SOCKADDR_COMMON_SIZE', `__SIZEOF_SOCKADDR_STORAGE' */
#include <bits/os/sockaddr-common.h>

#undef _SS_SIZE
#define _SS_SIZE __SIZEOF_SOCKADDR_STORAGE

#ifndef __sa_family_t_defined
#define __sa_family_t_defined
#include <bits/types.h>
#ifdef __CC__
__DECL_BEGIN
typedef __sa_family_t sa_family_t; /* One of `AF_*' */
__DECL_END
#endif /* __CC__ */
#endif /* !__sa_family_t_defined */

#endif /* !_BITS_SOCKADDR_H */
