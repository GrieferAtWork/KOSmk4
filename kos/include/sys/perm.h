/* HASH CRC-32:0xf4cdeda1 */
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
#ifndef _SYS_PERM_H
#define _SYS_PERM_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/[...]/sys/perm.h) */
#include <features.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __CC__
/* Change I/O port permissions for a specific I/O port range */
__CDECLARE_OPT(,int,__NOTHROW_NCX,ioperm,(__ULONGPTR_TYPE__ __from, __ULONGPTR_TYPE__ __num, __STDC_INT_AS_UINT_T __turn_on),(__from,__num,__turn_on))
/* Change I/O port permissions for all I/O ports */
__CDECLARE_OPT(,int,__NOTHROW_NCX,iopl,(__STDC_INT_AS_UINT_T __level),(__level))
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_PERM_H */
