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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_STRING64_S
#define GUARD_LIBC_HYBRID_ARCH_I386_STRING64_S 1
#define __ASSEMBLER__ 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#ifndef __INTELLISENSE__
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
#endif /* !__INTELLISENSE__ */

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__bzero, libc_bzero)
DEFINE_PUBLIC_ALIAS(__gcc_bcmp, libc_memcmp)
DEFINE_PUBLIC_ALIAS(explicit_bzero, libc_bzero)
DEFINE_PUBLIC_ALIAS(explicit_memset, libc_memset)

/* Implement a couple of wchar functions */
DEFINE_PUBLIC_ALIAS(wmemcmp, libc_memcmpl)
DEFINE_PUBLIC_ALIAS(wmemmove, libc_memmovel)
DEFINE_PUBLIC_ALIAS(wmempmove, libc_mempmovel)
DEFINE_PUBLIC_ALIAS(wmemcpy, libc_memcpyl)
DEFINE_PUBLIC_ALIAS(wmemset, libc_memsetl)
DEFINE_PUBLIC_ALIAS(wmempcpy, libc_mempcpyl)
DEFINE_PUBLIC_ALIAS(wmempset, libc_mempsetl)
DEFINE_INTERN_ALIAS(libc_wmemcmp, libc_memcmpl)
DEFINE_INTERN_ALIAS(libc_wmemmove, libc_memmovel)
DEFINE_INTERN_ALIAS(libc_wmempmove, libc_mempmovel)
DEFINE_INTERN_ALIAS(libc_wmemcpy, libc_memcpyl)
DEFINE_INTERN_ALIAS(libc_wmemset, libc_memsetl)
DEFINE_INTERN_ALIAS(libc_wmempcpy, libc_mempcpyl)
DEFINE_INTERN_ALIAS(libc_wmempset, libc_mempsetl)
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_STRING64_S */
