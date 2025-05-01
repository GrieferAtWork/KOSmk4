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
/*!replace_with_include <fenv.h>*/
#ifndef _BITS_CRT_FENV_IMPL_H
#define _BITS_CRT_FENV_IMPL_H 1

#include <__stdinc.h>
#include <bits/crt/fenv.h>

#ifdef __CC__
__DECL_BEGIN

#if 0
__LOCAL int (__arch_feraiseexcept)(int __excepts);
__LOCAL int __NOTHROW(__arch_feclearexcept)(int __excepts);
__LOCAL int __NOTHROW(__arch_fesetexcept)(int __excepts);
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__arch_fegetexcept)(void);
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__arch_fetestexcept)(int __excepts);

__LOCAL int __NOTHROW(__arch_feenableexcept)(int __excepts);
__LOCAL int __NOTHROW(__arch_fedisableexcept)(int __excepts);

__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__arch_fegetround)(void);
__LOCAL int __NOTHROW(__arch_fesetround)(int __rounding_direction);

__LOCAL __ATTR_OUT(1) int __NOTHROW_NCX(__arch_fegetenv)(struct __fenv_struct *__restrict __envp);
__LOCAL __ATTR_OUT(1) int __NOTHROW(__arch_feholdexcept)(struct __fenv_struct *__restrict __envp);
__LOCAL __ATTR_IN(1) int __NOTHROW(__arch_fesetenv)(struct __fenv_struct const *__restrict __envp);
__LOCAL __ATTR_IN(1) int __NOTHROW(__arch_feupdateenv)(struct __fenv_struct const *__restrict __envp);

__LOCAL __ATTR_OUT(1) int __NOTHROW_NCX(__arch_fegetmode)(__femode_t *__restrict __modep);
__LOCAL __ATTR_IN(1) int __NOTHROW_NCX(__arch_fesetmode)(__femode_t const *__restrict __modep);
#endif

#if !defined(__arch_fegetexceptflag) && defined(__arch_fetestexcept)
#define __arch_fegetexceptflag __arch_fegetexceptflag
__LOCAL __ATTR_OUT(1) int
__NOTHROW(__arch_fegetexceptflag)(__fexcept_t *__flagp, int __excepts) {
	*__flagp = __arch_fetestexcept(__excepts);
	return 0;
}
#endif /* !__arch_fegetexceptflag && __arch_fetestexcept */

#if !defined(__arch_fesetexceptflag) && defined(__arch_feclearexcept) && defined(__arch_fesetexcept)
#define __arch_fesetexceptflag __arch_fesetexceptflag
__LOCAL __ATTR_IN(1) int
__NOTHROW(__arch_fesetexceptflag)(__fexcept_t const *__flagp, int __excepts) {
	int __result = __arch_feclearexcept(~*__flagp & __excepts);
	if __likely(__result == 0)
		__result = __arch_fesetexcept(*__flagp & __excepts);
	return __result;
}
#endif /* !__arch_fesetexceptflag && __arch_feclearexcept && __arch_fesetexcept */

#ifndef __arch_fetestexceptflag
#define __arch_fetestexceptflag __arch_fetestexceptflag
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int
__NOTHROW(__arch_fetestexceptflag)(__fexcept_t const *__flagp, int __excepts) {
	return *__flagp & __excepts & __FE_ALL_EXCEPT;
}
#endif /* !__arch_fetestexceptflag */


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_FENV_IMPL_H */
