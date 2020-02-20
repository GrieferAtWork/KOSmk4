/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_SOCKADDR_STORAGE_STRUCT_H
#define _BITS_SOCKADDR_STORAGE_STRUCT_H 1

#include <__stdinc.h>

/* Structure large enough to hold any socket address (with the historical exception of AF_UNIX). */
#ifdef __CC__
#ifndef __sockaddr_storage_defined
#define __sockaddr_storage_defined 1
#include <hybrid/typecore.h>
#include <bits/sockaddr.h>
#ifndef __ss_aligntype
#define __ss_aligntype __ULONGPTR_TYPE__
#endif /* !__ss_aligntype */
#ifndef _SS_PADSIZE
#define _SS_PADSIZE (_SS_SIZE - __SOCKADDR_COMMON_SIZE - sizeof(__ss_aligntype))
#endif /* !_SS_PADSIZE */
__DECL_BEGIN
struct sockaddr_storage {
	__SOCKADDR_COMMON(ss_);    /* Address family, etc. */
	__BYTE_TYPE__  __ss_padding[_SS_PADSIZE];
	__ss_aligntype __ss_align; /* Force desired alignment. */
};
__DECL_END
#endif /* !__sockaddr_storage_defined */
#endif /* __CC__ */

#endif /* !_BITS_SOCKADDR_STORAGE_STRUCT_H */
