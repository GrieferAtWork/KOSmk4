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
#ifndef _OPTIMIZED_FENV_H
#define _OPTIMIZED_FENV_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <bits/crt/fenv-inline.h>

#ifndef __WANT_FENV_INLINE
#if 0
#define __WANT_FENV_INLINE 1
#endif
#endif /* !__WANT_FENV_INLINE */

__SYSDECL_BEGIN
__NAMESPACE_FAST_BEGIN


#ifndef __fast_feclearexcept_defined
#if !defined(__CRT_HAVE_feclearexcept) || defined(__WANT_FENV_INLINE)
#define __fast_feclearexcept_defined
__FORCELOCAL __ATTR_ARTIFICIAL int
__NOTHROW(__LIBC_FAST_NAME(feclearexcept))(int __excepts) {
	__inline_feclearexcept(__excepts);
	return 0;
}
#endif /* !__CRT_HAVE_feclearexcept || __WANT_FENV_INLINE */
#endif /* !__fast_feclearexcept_defined */

#ifndef __fast_feraiseexcept_defined
#if !defined(__CRT_HAVE_feraiseexcept) || defined(__WANT_FENV_INLINE)
#define __fast_feraiseexcept_defined
__FORCELOCAL __ATTR_ARTIFICIAL int
(__LIBC_FAST_NAME(feraiseexcept))(int __excepts) {
	__inline_feraiseexcept(__excepts);
	return 0;
}
#endif /* !__CRT_HAVE_feraiseexcept || __WANT_FENV_INLINE */
#endif /* !__fast_feraiseexcept_defined */

#ifndef __fast_fegetexceptflag_defined
#if !defined(__CRT_HAVE_fegetexceptflag) || !defined(__inline_fegetexceptflag) || defined(__WANT_FENV_INLINE)
#define __fast_fegetexceptflag_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBC_FAST_NAME(fegetexceptflag))(__fexcept_t *__flagp, int __excepts) {
#ifdef __inline_fegetexceptflag
	__inline_fegetexceptflag(__flagp, __excepts);
#else /* __inline_fegetexceptflag */
	*__flagp = 0;
	(void)__excepts;
#endif /* !__inline_fegetexceptflag */
	return 0;
}
#endif /* !__CRT_HAVE_fegetexceptflag || !__inline_fegetexceptflag || __WANT_FENV_INLINE */
#endif /* !__fast_fegetexceptflag_defined */

#ifndef __fast_fesetexceptflag_defined
#if !defined(__CRT_HAVE_fesetexceptflag) || !defined(__inline_fesetexceptflag) || defined(__WANT_FENV_INLINE)
#define __fast_fesetexceptflag_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBC_FAST_NAME(fesetexceptflag))(__fexcept_t const *__flagp, int __excepts) {
#ifdef __inline_fesetexceptflag
	__inline_fesetexceptflag(__flagp, __excepts);
#else /* __inline_fesetexceptflag */
	(void)__flagp;
	(void)__excepts;
	__COMPILER_IMPURE();
#endif /* !__inline_fesetexceptflag */
	return 0;
}
#endif /* !__CRT_HAVE_fesetexceptflag || !__inline_fesetexceptflag || __WANT_FENV_INLINE */
#endif /* !__fast_fesetexceptflag_defined */

#ifndef __fast_fetestexcept_defined
#if !defined(__CRT_HAVE_fetestexcept) || defined(__WANT_FENV_INLINE)
#define __fast_fetestexcept_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__LIBC_FAST_NAME(fetestexcept))(int __excepts) {
	return __inline_fetestexcept(__excepts);
}
#endif /* !__CRT_HAVE_fetestexcept || __WANT_FENV_INLINE */
#endif /* !__fast_fetestexcept_defined */

#ifndef __fast_fegetround_defined
#if !defined(__CRT_HAVE_fegetround) || defined(__WANT_FENV_INLINE)
#define __fast_fegetround_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__LIBC_FAST_NAME(fegetround))(void) {
	return __inline_fegetround();
}
#endif /* !__CRT_HAVE_fegetround || __WANT_FENV_INLINE */
#endif /* !__fast_fegetround_defined */

#ifndef __fast_fesetround_defined
#if !defined(__CRT_HAVE_fesetround) || defined(__WANT_FENV_INLINE)
#define __fast_fesetround_defined
__FORCELOCAL __ATTR_ARTIFICIAL int
__NOTHROW(__LIBC_FAST_NAME(fesetround))(int __rounding_direction) {
	return __inline_fesetround(__rounding_direction);
}
#endif /* !__CRT_HAVE_fesetround || __WANT_FENV_INLINE */
#endif /* !__fast_fesetround_defined */

#ifndef __fast_fegetenv_defined
#if !defined(__CRT_HAVE_fegetenv) || defined(__WANT_FENV_INLINE)
#define __fast_fegetenv_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBC_FAST_NAME(fegetenv))(struct __fenv_struct *envp) {
	__inline_fegetenv(envp);
	return 0;
}
#endif /* !__CRT_HAVE_fegetenv || __WANT_FENV_INLINE */
#endif /* !__fast_fegetenv_defined */

#ifndef __fast_feholdexcept_defined
#if !defined(__CRT_HAVE_feholdexcept) || defined(__WANT_FENV_INLINE)
#define __fast_feholdexcept_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBC_FAST_NAME(feholdexcept))(struct __fenv_struct *envp) {
	__inline_feholdexcept(envp);
	return 0;
}
#endif /* !__CRT_HAVE_feholdexcept || __WANT_FENV_INLINE */
#endif /* !__fast_feholdexcept_defined */

#ifndef __fast_fesetenv_defined
#if !defined(__CRT_HAVE_fesetenv) || defined(__WANT_FENV_INLINE)
#define __fast_fesetenv_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBC_FAST_NAME(fesetenv))(struct __fenv_struct const *envp) {
	__inline_fesetenv(envp);
	return 0;
}
#endif /* !__CRT_HAVE_fesetenv || __WANT_FENV_INLINE */
#endif /* !__fast_fesetenv_defined */

#ifndef __fast_feupdateenv_defined
#if !defined(__CRT_HAVE_feupdateenv) || defined(__WANT_FENV_INLINE)
#define __fast_feupdateenv_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBC_FAST_NAME(feupdateenv))(struct __fenv_struct const *envp) {
	__inline_feupdateenv(envp);
	return 0;
}
#endif /* !__CRT_HAVE_feupdateenv || __WANT_FENV_INLINE */
#endif /* !__fast_feupdateenv_defined */

#ifndef __fast_feenableexcept_defined
#if !defined(__CRT_HAVE_feenableexcept) || defined(__WANT_FENV_INLINE)
#define __fast_feenableexcept_defined
__FORCELOCAL __ATTR_ARTIFICIAL int
__NOTHROW(__LIBC_FAST_NAME(feenableexcept))(int __excepts) {
	return __inline_feenableexcept(__excepts);
}
#endif /* !__CRT_HAVE_feenableexcept || __WANT_FENV_INLINE */
#endif /* !__fast_feenableexcept_defined */

#ifndef __fast_fedisableexcept_defined
#if !defined(__CRT_HAVE_fedisableexcept) || defined(__WANT_FENV_INLINE)
#define __fast_fedisableexcept_defined
__FORCELOCAL __ATTR_ARTIFICIAL int
__NOTHROW(__LIBC_FAST_NAME(fedisableexcept))(int __excepts) {
	return __inline_fedisableexcept(__excepts);
}
#endif /* !__CRT_HAVE_fedisableexcept || __WANT_FENV_INLINE */
#endif /* !__fast_fedisableexcept_defined */

#ifndef __fast_fegetexcept_defined
#if !defined(__CRT_HAVE_fegetexcept) || defined(__WANT_FENV_INLINE)
#define __fast_fegetexcept_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__LIBC_FAST_NAME(fegetexcept))(void) {
	return __inline_fegetexcept();
}
#endif /* !__CRT_HAVE_fegetexcept || __WANT_FENV_INLINE */
#endif /* !__fast_fegetexcept_defined */

__NAMESPACE_FAST_END
__SYSDECL_END

#endif /* __CC__ */

#endif /* !_OPTIMIZED_FENV_H */
