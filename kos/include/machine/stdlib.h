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
/* (#) Portability: Cygwin (/newlib/libc/include/machine/stdlib.h) */
/* (#) Portability: Newlib (/newlib/libc/include/machine/stdlib.h) */
#ifndef _MACHINE_STDLIB_H
#define _MACHINE_STDLIB_H 1

#include <__crt.h>
#include <__stdinc.h>

__DECL_BEGIN

#ifdef __CC__

#ifndef __mkdtemp_defined
#define __mkdtemp_defined
#if defined(__CRT_HAVE_mkdtemp)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mkdtemp,(char *__template_),(__template_))
#elif defined(__CRT_HAVE__mktemp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,mkdtemp,(char *__template_),_mktemp,(__template_))
#else /* LIBC: mkdtemp */
#undef __mkdtemp_defined
#endif /* mkdtemp... */
#endif /* !__mkdtemp_defined */

#endif /* __CC__ */

__DECL_END

#endif /* !_MACHINE_STDLIB_H */
