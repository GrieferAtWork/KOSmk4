/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_FENV_INLINE_H
#define _BITS_CRT_FENV_INLINE_H 1

#include <__stdinc.h>

#include <bits/crt/fenv.h>
#include <hybrid/__assert.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

/* @param: EXCEPTS: Set of `FE_*' */
__LOCAL void (__inline_feraiseexcept)(int __excepts) {
	(void)__excepts;
	__hybrid_assertion_failed("Not implemented: feraiseexcept()");
}

/* @param: EXCEPTS: Set of `FE_*' */
__LOCAL void __NOTHROW(__inline_feclearexcept)(int __excepts) {
	(void)__excepts;
	__hybrid_assertion_failed("Not implemented: feclearexcept()");
}

__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__inline_fegetenv)(struct __fenv_struct *__restrict __envp) {
	(void)__envp;
	__hybrid_assertion_failed("Not implemented: fegetenv()");
}

__LOCAL __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__inline_fegetexcept)(void) {
	__hybrid_assertion_failed("Not implemented: fegetexcept()");
	return 0;
}

/* @return: * : The old set of enabled exceptions. */
__LOCAL int
__NOTHROW(__inline_feenableexcept)(int __excepts) {
	__hybrid_assertion_failed("Not implemented: feenableexcept()");
	return 0;
}

/* @return: * : The old set of enabled exceptions. */
__LOCAL int
__NOTHROW(__inline_fedisableexcept)(int __excepts) {
	__hybrid_assertion_failed("Not implemented: fedisableexcept()");
	return 0;
}

/* @return: * : One of `FE_TONEAREST', `FE_DOWNWARD', `FE_UPWARD', `FE_TOWARDZERO'. */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__inline_fegetround)(void) {
	__hybrid_assertion_failed("Not implemented: fegetround()");
	return 0;
}

/* @param: ROUNDING_DIRECTION: One of `FE_TONEAREST', `FE_DOWNWARD', `FE_UPWARD', `FE_TOWARDZERO'.
 * @return: 0 : Success
 * @return: 1 : `ROUNDING_DIRECTION' was invalid. */
__LOCAL int
__NOTHROW(__inline_fesetround)(int __rounding_direction) {
	(void)__rounding_direction;
	__hybrid_assertion_failed("Not implemented: fesetround()");
	return 0;
}

/* @param: EXCEPTS: Set of `FE_*'
 * @return: * : Set of `FE_*' */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__inline_fetestexcept)(int __excepts) {
	(void)__excepts;
	__hybrid_assertion_failed("Not implemented: fetestexcept()");
	return 0;
}

__LOCAL void
__NOTHROW(__inline_feholdexcept)(struct __fenv_struct *__restrict __envp) {
	(void)__envp;
	__hybrid_assertion_failed("Not implemented: feholdexcept()");
}

__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(__inline_fesetenv)(struct __fenv_struct const *__restrict __envp) {
	(void)__envp;
	__hybrid_assertion_failed("Not implemented: fesetenv()");
}

__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(__inline_feupdateenv)(struct __fenv_struct const *__restrict __envp) {
	(void)__envp;
	__hybrid_assertion_failed("Not implemented: feupdateenv()");
}


#if 0
#define __inline_fegetexceptflag __inline_fegetexceptflag
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(__inline_fegetexceptflag)(__fexcept_t *__flagp, int __excepts) {
	(void)__flagp;
	(void)__excepts;
	__hybrid_assertion_failed("Not implemented: fegetexceptflag()");
}
#endif


#if 0
#define __inline_fesetexceptflag __inline_fesetexceptflag
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(__inline_fesetexceptflag)(__fexcept_t const *__flagp, int __excepts) {
	(void)__flagp;
	(void)__excepts;
	__hybrid_assertion_failed("Not implemented: fesetexceptflag()");
}
#endif

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_CRT_FENV_INLINE_H */
