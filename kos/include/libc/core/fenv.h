/* HASH CRC-32:0xb871856b */
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
#ifndef _LIBC_CORE_FENV_H
#define _LIBC_CORE_FENV_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __CRT_HAVE_feraiseexcept
#include <kos/anno.h>
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*' */
__CREDIRECT(,int,__THROWING(...),__libc_core_feraiseexcept,(int __excepts),feraiseexcept,(__excepts))
#else /* __CRT_HAVE_feraiseexcept */
#include <libc/local/fenv/feraiseexcept.h>
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*' */
#define __libc_core_feraiseexcept __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(feraiseexcept)
#endif /* !__CRT_HAVE_feraiseexcept */
#ifdef __CRT_HAVE_fegetround
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,__libc_core_fegetround,(void),fegetround,())
#else /* __CRT_HAVE_fegetround */
#include <libc/local/fenv/fegetround.h>
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
#define __libc_core_fegetround __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fegetround)
#endif /* !__CRT_HAVE_fegetround */
#ifdef __CRT_HAVE_fesetround
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CREDIRECT(,int,__NOTHROW,__libc_core_fesetround,(int __rounding_direction),fesetround,(__rounding_direction))
#else /* __CRT_HAVE_fesetround */
#include <libc/local/fenv/fesetround.h>
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
#define __libc_core_fesetround __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fesetround)
#endif /* !__CRT_HAVE_fesetround */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_FENV_H */
