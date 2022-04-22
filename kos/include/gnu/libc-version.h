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
/* (#) Portability: GNU C Library (/include/gnu/libc-version.h) */
#ifndef _GNU_LIBC_VERSION_H
#define _GNU_LIBC_VERSION_H 1

#include <__crt.h>
#include <features.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* Return libc version information. (gLibc-specific, but emulated on KOS for ABI compat) */
__CDECLARE_OPT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW,gnu_get_libc_release,(void),())
__CDECLARE_OPT(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char const *,__NOTHROW,gnu_get_libc_version,(void),())

__SYSDECL_END
#endif /* __CC__ */

#endif /* gnu/libc-version.h */
