/* HASH CRC-32:0xf41f1298 */
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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/klog.h) */
/* (#) Portability: diet libc     (/include/sys/klog.h) */
/* (#) Portability: musl libc     (/include/sys/klog.h) */
/* (#) Portability: uClibc        (/include/sys/klog.h) */
#ifndef _SYS_KLOG_H
#define _SYS_KLOG_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>


#ifdef __CC__
__SYSDECL_BEGIN

__CDECLARE_OPT(,int,__NOTHROW_NCX,klogctl,(__STDC_INT_AS_UINT_T __type, char *__bufp, __STDC_INT_AS_SIZE_T __len),(__type,__bufp,__len))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_KLOG_H */
