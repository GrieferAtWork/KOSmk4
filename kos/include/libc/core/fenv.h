/* HASH CRC-32:0xcd20e112 */
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
#ifndef _LIBC_CORE_FENV_H
#define _LIBC_CORE_FENV_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifndef ____libc_core_feraiseexcept_defined
#define ____libc_core_feraiseexcept_defined
#include <bits/crt/fenv-impl.h>
#if defined(__CRT_HAVE_feraiseexcept) && defined(__arch_feraiseexcept)
#include <kos/anno.h>
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were railed
 * @return: != 0 : At least one exception of `excepts' could not be raised */
__CEIREDIRECT(,int,__THROWING(...),__libc_core_feraiseexcept,(int __excepts),feraiseexcept,{ return __arch_feraiseexcept(__excepts); })
#elif defined(__CRT_HAVE_feraiseexcept)
#include <kos/anno.h>
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were railed
 * @return: != 0 : At least one exception of `excepts' could not be raised */
__CREDIRECT(,int,__THROWING(...),__libc_core_feraiseexcept,(int __excepts),feraiseexcept,(__excepts))
#elif defined(__arch_feraiseexcept)
#include <kos/anno.h>
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were railed
 * @return: != 0 : At least one exception of `excepts' could not be raised */
__LOCAL int (__LIBCCALL __libc_core_feraiseexcept)(int __excepts) __THROWS(...) { return __arch_feraiseexcept(__excepts); }
#else /* ... */
#undef ____libc_core_feraiseexcept_defined
#endif /* !... */
#endif /* !____libc_core_feraiseexcept_defined */
#ifndef ____libc_core_fegetround_defined
#define ____libc_core_fegetround_defined
#include <bits/crt/fenv-impl.h>
#if defined(__CRT_HAVE_fegetround) && defined(__arch_fegetround)
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,__libc_core_fegetround,(void),fegetround,{ __COMPILER_IMPURE(); return __arch_fegetround(); })
#elif defined(__CRT_HAVE_fegetround)
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,__libc_core_fegetround,(void),fegetround,())
#elif defined(__arch_fegetround)
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __libc_core_fegetround)(void) { __COMPILER_IMPURE(); return __arch_fegetround(); }
#else /* ... */
#undef ____libc_core_fegetround_defined
#endif /* !... */
#endif /* !____libc_core_fegetround_defined */
#ifndef ____libc_core_fesetround_defined
#define ____libc_core_fesetround_defined
#include <bits/crt/fenv-impl.h>
#if defined(__CRT_HAVE_fesetround) && defined(__arch_fesetround)
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CEIREDIRECT(,int,__NOTHROW,__libc_core_fesetround,(int __rounding_direction),fesetround,{ return __arch_fesetround(__rounding_direction); })
#elif defined(__CRT_HAVE_fesetround)
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__CREDIRECT(,int,__NOTHROW,__libc_core_fesetround,(int __rounding_direction),fesetround,(__rounding_direction))
#elif defined(__arch_fesetround)
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__LOCAL int __NOTHROW(__LIBCCALL __libc_core_fesetround)(int __rounding_direction) { return __arch_fesetround(__rounding_direction); }
#else /* ... */
#undef ____libc_core_fesetround_defined
#endif /* !... */
#endif /* !____libc_core_fesetround_defined */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_FENV_H */
