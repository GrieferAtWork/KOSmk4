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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_STRING64_S
#define GUARD_LIBC_HYBRID_ARCH_I386_STRING64_S 1

#if 1
#define N 1
#define RETURN_PCPY 1
#include "string64-template.S"
#define N 2
#define RETURN_PCPY 1
#include "string64-template.S"
#define N 4
#define RETURN_PCPY 1
#include "string64-template.S"
#define N 8
#define RETURN_PCPY 1
#include "string64-template.S"

#define N 1
#define RETURN_PCPY 0
#include "string64-template.S"
#define N 2
#define RETURN_PCPY 0
#include "string64-template.S"
#define N 4
#define RETURN_PCPY 0
#include "string64-template.S"
#define N 8
#define RETURN_PCPY 0
#include "string64-template.S"

#ifndef __KERNEL__
/* Implement a couple of wchar functions */
//TODO:DEFINE_PUBLIC_ALIAS(DOS$wmemcmp, libc_memcmpw)
//TODO:DEFINE_PUBLIC_ALIAS(wmemcmp, libc_memcmpl)

DEFINE_PUBLIC_ALIAS(DOS$wmemcpy, libc_memcpyw)
DEFINE_PUBLIC_ALIAS(wmemcpy, libc_memcpyl)

//TODO:DEFINE_PUBLIC_ALIAS(DOS$wmemmove, libc_memmovew)
//TODO:DEFINE_PUBLIC_ALIAS(wmemmove, libc_memmovel)

DEFINE_PUBLIC_ALIAS(DOS$wmemset, libc_memsetw)
DEFINE_PUBLIC_ALIAS(wmemset, libc_memsetl)

DEFINE_PUBLIC_ALIAS(DOS$wmempcpy, libc_mempcpyw)
DEFINE_PUBLIC_ALIAS(wmempcpy, libc_mempcpyl)

//TODO:DEFINE_PUBLIC_ALIAS(DOS$wmempmove, libc_mempmovew)
//TODO:DEFINE_PUBLIC_ALIAS(wmempmove, libc_mempmovel)

DEFINE_PUBLIC_ALIAS(DOS$wmempset, libc_mempsetw)
DEFINE_PUBLIC_ALIAS(wmempset, libc_mempsetl)
#endif /* !__KERNEL__ */

#endif

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_STRING64_S */
