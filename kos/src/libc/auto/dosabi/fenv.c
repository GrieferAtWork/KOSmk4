/* HASH CRC-32:0xe1cc3d97 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_FENV_C
#define GUARD_LIBC_AUTO_DOSABI_FENV_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../fenv.h"

DECL_BEGIN

/* Clear the supported exceptions represented by EXCEPTS */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") int
NOTHROW(LIBDCALL libd_feclearexcept)(int excepts) {
	return libc_feclearexcept(excepts);
}
/* Raise the supported exceptions represented by EXCEPTS */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") int
(LIBDCALL libd_feraiseexcept)(int excepts) THROWS(...) {
	return libc_feraiseexcept(excepts);
}
/* Store implementation-defined representation of the exception
 * flags indicated by EXCEPTS in the object pointed to by FLAGP */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_fegetexceptflag)(fexcept_t *flagp,
                                           int excepts) {
	return libc_fegetexceptflag(flagp, excepts);
}
/* Set complete status for exceptions indicated by EXCEPTS according
 * to the representation in the object pointed to by FLAGP */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_fesetexceptflag)(fexcept_t const *flagp,
                                           int excepts) {
	return libc_fesetexceptflag(flagp, excepts);
}
/* Determine which of subset of the exceptions
 * specified by EXCEPTS are currently set */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") ATTR_PURE WUNUSED int
NOTHROW(LIBDCALL libd_fetestexcept)(int excepts) {
	return libc_fetestexcept(excepts);
}
/* Establish the rounding direction represented by `rounding_direction'
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") int
NOTHROW(LIBDCALL libd_fesetround)(int rounding_direction) {
	return libc_fesetround(rounding_direction);
}
/* Store the current floating-point environment in the object pointed to by ENVP */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_fegetenv)(fenv_t *envp) {
	return libc_fegetenv(envp);
}
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_feholdexcept)(fenv_t *envp) {
	return libc_feholdexcept(envp);
}
/* Establish the floating-point environment represented by the object pointed to by ENVP */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_fesetenv)(fenv_t const *envp) {
	return libc_fesetenv(envp);
}
/* Save current exceptions in temporary storage, install environment
 * represented by object pointed to by ENVP and raise exceptions
 * according to saved exceptions */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_feupdateenv)(fenv_t const *envp) {
	return libc_feupdateenv(envp);
}
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") int
NOTHROW(LIBDCALL libd_feenableexcept)(int excepts) {
	return libc_feenableexcept(excepts);
}
/* Disable individual exceptions.  Will not disable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully disabled, otherwise returns -1 */
INTERN ATTR_SECTION(".text.crt.dos.math.fenv") int
NOTHROW(LIBDCALL libd_fedisableexcept)(int excepts) {
	return libc_fedisableexcept(excepts);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$feclearexcept, libd_feclearexcept);
DEFINE_PUBLIC_ALIAS(DOS$feraiseexcept, libd_feraiseexcept);
DEFINE_PUBLIC_ALIAS(DOS$fegetexceptflag, libd_fegetexceptflag);
DEFINE_PUBLIC_ALIAS(DOS$fesetexceptflag, libd_fesetexceptflag);
DEFINE_PUBLIC_ALIAS(DOS$fetestexcept, libd_fetestexcept);
DEFINE_PUBLIC_ALIAS(DOS$fesetround, libd_fesetround);
DEFINE_PUBLIC_ALIAS(DOS$fegetenv, libd_fegetenv);
DEFINE_PUBLIC_ALIAS(DOS$feholdexcept, libd_feholdexcept);
DEFINE_PUBLIC_ALIAS(DOS$fesetenv, libd_fesetenv);
DEFINE_PUBLIC_ALIAS(DOS$feupdateenv, libd_feupdateenv);
DEFINE_PUBLIC_ALIAS(DOS$feenableexcept, libd_feenableexcept);
DEFINE_PUBLIC_ALIAS(DOS$fedisableexcept, libd_fedisableexcept);

#endif /* !GUARD_LIBC_AUTO_DOSABI_FENV_C */
