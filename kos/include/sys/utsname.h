/* HASH CRC-32:0x2fffd7b5 */
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
#ifndef _SYS_UTSNAME_H
#define _SYS_UTSNAME_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/os/kos/utsname.h>

__SYSDECL_BEGIN

/* Note that SVID assumes all members have the same size. */
#ifdef __USE_MISC
#define SYS_NMLN _UTSNAME_LENGTH
#endif /* __USE_MISC */

#ifdef __CC__

/* Put information about the system in NAME */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,uname,(struct utsname *__name),(__name))

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_UTSNAME_H */
