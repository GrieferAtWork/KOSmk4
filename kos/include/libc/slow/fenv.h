/* HASH CRC-32:0x21931fcc */
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
#ifndef _LIBC_SLOW_FENV_H
#define _LIBC_SLOW_FENV_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>
#include <kos/anno.h>

__SYSDECL_BEGIN

#ifdef __CRT_HAVE_feraiseexcept
/* Raise the supported exceptions represented by EXCEPTS */
__CREDIRECT(,int,,__libc_slow_feraiseexcept,(int __excepts),feraiseexcept,(__excepts)) __THROWS(...)
#else /* LIBC: feraiseexcept */
#include <local/fenv/feraiseexcept.h>
/* Raise the supported exceptions represented by EXCEPTS */
#define __libc_slow_feraiseexcept (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feraiseexcept))
#endif /* feraiseexcept... */
#ifdef __CRT_HAVE_fegetround
/* Get current rounding direction */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,__libc_slow_fegetround,(void),fegetround,())
#else /* LIBC: fegetround */
#include <local/fenv/fegetround.h>
/* Get current rounding direction */
#define __libc_slow_fegetround (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fegetround))
#endif /* fegetround... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LIBC_SLOW_FENV_H */
