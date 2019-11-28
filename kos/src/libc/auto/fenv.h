/* HASH CRC-32:0xa5fe92c1 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_FENV_H
#define GUARD_LIBC_AUTO_FENV_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <fenv.h>
#include <kos/anno.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Clear the supported exceptions represented by EXCEPTS */
INTDEF int NOTHROW(LIBCCALL libc_feclearexcept)(int excepts);
/* Raise the supported exceptions represented by EXCEPTS */
INTDEF int (LIBCCALL libc_feraiseexcept)(int excepts) __THROWS(...);
/* Store implementation-defined representation of the exception
 * flags indicated by EXCEPTS in the object pointed to by FLAGP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fegetexceptflag)(fexcept_t *flagp, int excepts);
/* Set complete status for exceptions indicated by EXCEPTS according
 * to the representation in the object pointed to by FLAGP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fesetexceptflag)(fexcept_t const *flagp, int excepts);
/* Determine which of subset of the exceptions
 * specified by EXCEPTS are currently set */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBCCALL libc_fetestexcept)(int excepts);
/* Get current rounding direction */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBCCALL libc_fegetround)(void);
/* Establish the rounding direction represented by ROUND */
INTDEF int NOTHROW(LIBCCALL libc_fesetround)(int rounding_direction);
/* Store the current floating-point environment in the object pointed to by ENVP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fegetenv)(fenv_t *envp);
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_feholdexcept)(fenv_t *envp);
/* Establish the floating-point environment represented by the object pointed to by ENVP */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_fesetenv)(fenv_t const *envp);
/* Save current exceptions in temporary storage, install environment
 * represented by object pointed to by ENVP and raise exceptions
 * according to saved exceptions */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_feupdateenv)(fenv_t const *envp);
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
INTDEF int NOTHROW(LIBCCALL libc_feenableexcept)(int excepts);
/* Disable individual exceptions.  Will not disable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully disabled, otherwise returns -1 */
INTDEF int NOTHROW(LIBCCALL libc_fedisableexcept)(int excepts);
/* Return enabled exceptions */
INTDEF ATTR_PURE WUNUSED int NOTHROW(LIBCCALL libc_fegetexcept)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_FENV_H */
