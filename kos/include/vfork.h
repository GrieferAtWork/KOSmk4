/* HASH CRC-32:0x344edf0d */
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
#ifndef _VFORK_H
#define _VFORK_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __vfork_defined
#define __vfork_defined 1
#ifdef __CRT_HAVE_vfork
/* >> vfork(2)
 * Same as `fork(2)', but possibly suspend the calling process until the
 * child process either calls `exit(2)' or one of the many `exec(2)' functions */
__CDECLARE(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,vfork,(void),())
#elif defined(__CRT_HAVE___vfork)
/* >> vfork(2)
 * Same as `fork(2)', but possibly suspend the calling process until the
 * child process either calls `exit(2)' or one of the many `exec(2)' functions */
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,vfork,(void),__vfork,())
#else /* LIBC: vfork */
#undef __vfork_defined
#endif /* vfork... */
#endif /* !__vfork_defined */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_VFORK_H */
