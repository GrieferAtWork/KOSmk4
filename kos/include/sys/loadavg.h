/* HASH CRC-32:0xb9698be8 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/loadavg.h) */
#ifndef _SYS_LOADAVG_H
#define _SYS_LOADAVG_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __NO_FPU
#if !defined(__getloadavg_defined) && defined(__CRT_HAVE_getloadavg)
#define __getloadavg_defined
__CDECLARE(,int,__NOTHROW_RPC,getloadavg,(double __loadavg[], __STDC_INT_AS_SIZE_T __nelem),(__loadavg,__nelem))
#endif /* !__getloadavg_defined && __CRT_HAVE_getloadavg */
#endif /* !__NO_FPU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_LOADAVG_H */
