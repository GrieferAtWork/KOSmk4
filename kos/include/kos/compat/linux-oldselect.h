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
#ifndef _KOS_COMPAT_LINUX_OLDSELECT_H
#define _KOS_COMPAT_LINUX_OLDSELECT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <kos/anno.h>
#include <bits/timeval.h> /* struct __timeval32 */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("n")
#pragma push_macro("inp")
#pragma push_macro("outp")
#pragma push_macro("exp")
#pragma push_macro("tvp")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef n
#undef inp
#undef outp
#undef exp
#undef tvp

struct __fd_set_struct;
struct sel_arg_struct {
	__ULONGPTR_TYPE__              n;    /* nfds argument */
	__USER struct __fd_set_struct *inp;  /* Read fd-set */
	__USER struct __fd_set_struct *outp; /* Write fd-set */
	__USER struct __fd_set_struct *exp;  /* Except fd-set */
	__USER struct __timeval32     *tvp;  /* Timeout argument */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("tvp")
#pragma pop_macro("exp")
#pragma pop_macro("outp")
#pragma pop_macro("inp")
#pragma pop_macro("n")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_COMPAT_LINUX_OLDSELECT_H */
