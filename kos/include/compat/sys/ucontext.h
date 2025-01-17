/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _COMPAT_SYS_UCONTEXT_H
#define _COMPAT_SYS_UCONTEXT_H 1

#include <__stdinc.h>
#include <features.h>

#include <compat/config.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/mcontext.h> /* struct compat_mcontext */
#include <compat/bits/os/ucontext.h> /* struct compat_ucontext */
#include <compat/bits/types.h>

#ifdef __COMPAT_MCONTEXT_NGREG
#define COMPAT_NGREG __COMPAT_MCONTEXT_NGREG
#endif /* __COMPAT_MCONTEXT_NGREG */

#define __SIZEOF_COMPAT_GREG_T__ __ARCH_COMPAT_SIZEOF_REGISTER

#ifdef __CC__
__DECL_BEGIN

#ifndef __compat_greg_t_defined
#define __compat_greg_t_defined
typedef __ARCH_COMPAT_REGISTER_T compat_greg_t;
#endif /* !__compat_greg_t_defined */

#ifndef __compat_ucontext_t_defined
#define __compat_ucontext_t_defined
typedef struct compat_ucontext compat_ucontext_t;
#endif /* !__compat_ucontext_t_defined */

#ifndef __compat_mcontext_t_defined
#define __compat_mcontext_t_defined
typedef struct compat_mcontext compat_mcontext_t;
#endif /* !__compat_mcontext_t_defined */

__DECL_END
#endif /* __CC__ */
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_SYS_UCONTEXT_H */
