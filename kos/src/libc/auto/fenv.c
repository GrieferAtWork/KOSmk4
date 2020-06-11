/* HASH CRC-32:0x5bfed87c */
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
#ifndef GUARD_LIBC_AUTO_FENV_C
#define GUARD_LIBC_AUTO_FENV_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "fenv.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/fenv-inline.h>
/* Clear the supported exceptions represented by EXCEPTS */
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW(LIBCCALL libc_feclearexcept)(int excepts) {
	__inline_feclearexcept(excepts);
	return 0;
}
#include <bits/fenv-inline.h>
/* Raise the supported exceptions represented by EXCEPTS */
INTERN ATTR_SECTION(".text.crt.math.fenv") int
(LIBCCALL libc_feraiseexcept)(int excepts) THROWS(...) {
	__inline_feraiseexcept(excepts);
	return 0;
}
#include <bits/fenv-inline.h>
/* Store implementation-defined representation of the exception
 * flags indicated by EXCEPTS in the object pointed to by FLAGP */
INTERN ATTR_SECTION(".text.crt.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_fegetexceptflag)(fexcept_t *flagp, int excepts) {
#ifdef __inline_fegetexceptflag
	__inline_fegetexceptflag(flagp, excepts);
#else /* __inline_fegetexceptflag */
	*flagp = 0;
	(void)excepts;
#endif /* !__inline_fegetexceptflag */
	return 0;
}
#include <bits/fenv-inline.h>
/* Set complete status for exceptions indicated by EXCEPTS according
 * to the representation in the object pointed to by FLAGP */
INTERN ATTR_SECTION(".text.crt.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_fesetexceptflag)(fexcept_t const *flagp, int excepts) {
#ifdef __inline_fesetexceptflag
	__inline_fesetexceptflag(flagp, excepts);
#else /* __inline_fesetexceptflag */
	(void)flagp;
	(void)excepts;
	COMPILER_IMPURE();
#endif /* !__inline_fesetexceptflag */
	return 0;
}
#include <bits/fenv-inline.h>
/* Determine which of subset of the exceptions
 * specified by EXCEPTS are currently set */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_PURE WUNUSED int
NOTHROW(LIBCCALL libc_fetestexcept)(int excepts) {
	return __inline_fetestexcept(excepts);
}
#include <bits/fenv-inline.h>
/* Get current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_PURE WUNUSED int
NOTHROW(LIBCCALL libc_fegetround)(void) {
	return __inline_fegetround();
}
#include <bits/fenv-inline.h>
/* Establish the rounding direction represented by `rounding_direction'
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW(LIBCCALL libc_fesetround)(int rounding_direction) {
	return __inline_fesetround(rounding_direction);
}
#include <bits/fenv-inline.h>
/* Store the current floating-point environment in the object pointed to by ENVP */
INTERN ATTR_SECTION(".text.crt.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_fegetenv)(fenv_t *envp) {
	__inline_fegetenv(envp);
	return 0;
}
#include <bits/fenv-inline.h>
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
INTERN ATTR_SECTION(".text.crt.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_feholdexcept)(fenv_t *envp) {
	__inline_feholdexcept(envp);
	return 0;
}
#include <bits/fenv-inline.h>
/* Establish the floating-point environment represented by the object pointed to by ENVP */
INTERN ATTR_SECTION(".text.crt.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_fesetenv)(fenv_t const *envp) {
	__inline_fesetenv(envp);
	return 0;
}
#include <bits/fenv-inline.h>
/* Save current exceptions in temporary storage, install environment
 * represented by object pointed to by ENVP and raise exceptions
 * according to saved exceptions */
INTERN ATTR_SECTION(".text.crt.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_feupdateenv)(fenv_t const *envp) {
	__inline_feupdateenv(envp);
	return 0;
}
#include <bits/fenv-inline.h>
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW(LIBCCALL libc_feenableexcept)(int excepts) {
	return __inline_feenableexcept(excepts);
}
#include <bits/fenv-inline.h>
/* Disable individual exceptions.  Will not disable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully disabled, otherwise returns -1 */
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW(LIBCCALL libc_fedisableexcept)(int excepts) {
	return __inline_fedisableexcept(excepts);
}
#include <bits/fenv-inline.h>
/* Return enabled exceptions */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_PURE WUNUSED int
NOTHROW(LIBCCALL libc_fegetexcept)(void) {
	return __inline_fegetexcept();
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(feclearexcept, libc_feclearexcept);
DEFINE_PUBLIC_WEAK_ALIAS(feraiseexcept, libc_feraiseexcept);
DEFINE_PUBLIC_WEAK_ALIAS(fegetexceptflag, libc_fegetexceptflag);
DEFINE_PUBLIC_WEAK_ALIAS(fesetexceptflag, libc_fesetexceptflag);
DEFINE_PUBLIC_WEAK_ALIAS(fetestexcept, libc_fetestexcept);
DEFINE_PUBLIC_WEAK_ALIAS(fegetround, libc_fegetround);
DEFINE_PUBLIC_WEAK_ALIAS(fesetround, libc_fesetround);
DEFINE_PUBLIC_WEAK_ALIAS(fegetenv, libc_fegetenv);
DEFINE_PUBLIC_WEAK_ALIAS(feholdexcept, libc_feholdexcept);
DEFINE_PUBLIC_WEAK_ALIAS(fesetenv, libc_fesetenv);
DEFINE_PUBLIC_WEAK_ALIAS(feupdateenv, libc_feupdateenv);
DEFINE_PUBLIC_WEAK_ALIAS(feenableexcept, libc_feenableexcept);
DEFINE_PUBLIC_WEAK_ALIAS(fedisableexcept, libc_fedisableexcept);
DEFINE_PUBLIC_WEAK_ALIAS(fegetexcept, libc_fegetexcept);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_FENV_C */
