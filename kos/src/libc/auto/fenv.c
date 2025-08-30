/* HASH CRC-32:0xbeb9c870 */
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
#ifndef GUARD_LIBC_AUTO_FENV_C
#define GUARD_LIBC_AUTO_FENV_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "fenv.h"

DECL_BEGIN

#ifndef __arch_feraiseexcept
#define __arch_feraiseexcept(excepts) \
	(CRT_UNIMPLEMENTEDF("feraiseexcept(excepts: %#x)", excepts), -1)
#endif /* !__arch_feraiseexcept */
#ifndef __arch_feclearexcept
#define __arch_feclearexcept(excepts) \
	(CRT_UNIMPLEMENTEDF("feclearexcept(excepts: %#x)", excepts), -1)
#endif /* !__arch_feclearexcept */
#ifndef __arch_fesetexcept
#define __arch_fesetexcept(excepts) \
	(CRT_UNIMPLEMENTEDF("fesetexcept(excepts: %#x)", excepts), -1)
#endif /* !__arch_fesetexcept */
#ifndef __arch_fegetexcept
#define __arch_fegetexcept() \
	(CRT_UNIMPLEMENTED("fegetexcept"), 0)
#endif /* !__arch_fegetexcept */
#ifndef __arch_fetestexcept
#define __arch_fetestexcept(excepts) \
	(CRT_UNIMPLEMENTEDF("fetestexcept(excepts: %#x)", excepts), 0)
#endif /* !__arch_fetestexcept */
#ifndef __arch_feenableexcept
#define __arch_feenableexcept(excepts) \
	(CRT_UNIMPLEMENTEDF("feenableexcept(excepts: %#x)", excepts), -1)
#endif /* !__arch_feenableexcept */
#ifndef __arch_fedisableexcept
#define __arch_fedisableexcept(excepts) \
	(CRT_UNIMPLEMENTEDF("fedisableexcept(excepts: %#x)", excepts), -1)
#endif /* !__arch_fedisableexcept */
#ifndef __arch_fegetround
#define __arch_fegetround() \
	(CRT_UNIMPLEMENTED("fegetround"), )
#endif /* !__arch_fegetround */
#ifndef __arch_fesetround
#define __arch_fesetround(rounding_direction) \
	(CRT_UNIMPLEMENTEDF("fesetround(rounding_direction: %#x)", rounding_direction), -1)
#endif /* !__arch_fesetround */
#ifndef __arch_fegetenv
#define __arch_fegetenv(envp) \
	(CRT_UNIMPLEMENTEDF("fegetenv(envp: %p)", envp), -1)
#endif /* !__arch_fegetenv */
#ifndef __arch_feholdexcept
#define __arch_feholdexcept(envp) \
	(CRT_UNIMPLEMENTEDF("feholdexcept(envp: %p)", envp), -1)
#endif /* !__arch_feholdexcept */
#ifndef __arch_fesetenv
#define __arch_fesetenv(envp) \
	(CRT_UNIMPLEMENTEDF("fesetenv(envp: %p)", envp), -1)
#endif /* !__arch_fesetenv */
#ifndef __arch_feupdateenv
#define __arch_feupdateenv(envp) \
	(CRT_UNIMPLEMENTEDF("feupdateenv(envp: %p)", envp), -1)
#endif /* !__arch_feupdateenv */
#ifndef __arch_fegetmode
#define __arch_fegetmode(modep) \
	(CRT_UNIMPLEMENTEDF("fegetmode(modep: %p)", modep), -1)
#endif /* !__arch_fegetmode */
#ifndef __arch_fesetmode
#define __arch_fesetmode(modep) \
	(CRT_UNIMPLEMENTEDF("fesetmode(modep: %p)", modep), -1)
#endif /* !__arch_fesetmode */
#ifndef __arch_fegetexceptflag
#define __arch_fegetexceptflag(flagp, excepts) \
	(CRT_UNIMPLEMENTEDF("fegetexceptflag(flagp: %p, excepts: %#x)", flagp, excepts), -1)
#endif /* !__arch_fegetexceptflag */
#ifndef __arch_fesetexceptflag
#define __arch_fesetexceptflag(flagp, excepts) \
	(CRT_UNIMPLEMENTEDF("fesetexceptflag(flagp: %p, excepts: %#x)", flagp, excepts), -1)
#endif /* !__arch_fesetexceptflag */
#ifndef __KERNEL__
#include <bits/crt/fenv-impl.h>
/* >> feraiseexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were railed
 * @return: != 0 : At least one exception of `excepts' could not be raised */
INTERN ATTR_SECTION(".text.crt.math.fenv") int
(LIBCCALL libc_feraiseexcept)(int excepts) THROWS(...) {
	return __arch_feraiseexcept(excepts);
}
#include <bits/crt/fenv-impl.h>
/* >> feclearexcept(3)
 * @param: excepts: Set of `FE_*'
 * @return: == 0 : All exceptions indicated by `excepts' were cleared
 * @return: != 0 : At least one exception of `excepts' could not be cleared */
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW(LIBCCALL libc_feclearexcept)(int excepts) {
	return __arch_feclearexcept(excepts);
}
#include <bits/crt/fenv-impl.h>
/* >> fegetexceptflag(3)
 * @return: == 0 : Success
 * @return: != 0 : Unspecified error */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_fegetexceptflag)(fexcept_t *flagp,
                                           int excepts) {
	return __arch_fegetexceptflag(flagp, excepts);
}
#include <bits/crt/fenv-impl.h>
/* >> fesetexceptflag(3)
 * @return: == 0 : Success
 * @return: != 0 : Unspecified error */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_fesetexceptflag)(fexcept_t const *flagp,
                                           int excepts) {
	return __arch_fesetexceptflag(flagp, excepts);
}
#include <bits/crt/fenv-impl.h>
/* >> fetestexcept(3) */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_PURE WUNUSED int
NOTHROW(LIBCCALL libc_fetestexcept)(int excepts) {
	/* Do `COMPILER_IMPURE()' to supress a false warning:
	 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=105682 */
	COMPILER_IMPURE();
	return __arch_fetestexcept(excepts);
}
#include <bits/crt/fenv-impl.h>
/* >> fegetround(3)
 * Get the current rounding direction
 * @return: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_PURE WUNUSED int
NOTHROW(LIBCCALL libc_fegetround)(void) {
	COMPILER_IMPURE();
	return __arch_fegetround();
}
#include <bits/crt/fenv-impl.h>
/* >> fesetround(3)
 * Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW(LIBCCALL libc_fesetround)(int rounding_direction) {
	return __arch_fesetround(rounding_direction);
}
#include <bits/crt/fenv-impl.h>
/* >> fegetenv(3) */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_fegetenv)(fenv_t *envp) {
	return __arch_fegetenv(envp);
}
#include <bits/crt/fenv-impl.h>
/* >> feholdexcept(3) */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_feholdexcept)(fenv_t *envp) {
	return __arch_feholdexcept(envp);
}
#include <bits/crt/fenv-impl.h>
/* >> fesetenv(3) */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_fesetenv)(fenv_t const *envp) {
	return __arch_fesetenv(envp);
}
#include <bits/crt/fenv-impl.h>
/* >> feupdateenv(3) */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_feupdateenv)(fenv_t const *envp) {
	return __arch_feupdateenv(envp);
}
#include <bits/crt/fenv-impl.h>
/* >> feenableexcept(3)
 * @return: * : The old set of enabled exceptions */
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW(LIBCCALL libc_feenableexcept)(int excepts) {
	return __arch_feenableexcept(excepts);
}
#include <bits/crt/fenv-impl.h>
/* >> fedisableexcept(3)
 * @return: * : The old set of enabled exceptions */
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW(LIBCCALL libc_fedisableexcept)(int excepts) {
	return __arch_fedisableexcept(excepts);
}
#include <bits/crt/fenv-impl.h>
/* >> fegetexcept(3) */
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_PURE WUNUSED int
NOTHROW(LIBCCALL libc_fegetexcept)(void) {
	COMPILER_IMPURE();
	return __arch_fegetexcept();
}
#include <bits/crt/fenv-impl.h>
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW(LIBCCALL libc_fesetexcept)(int excepts) {
	return __arch_fesetexcept(excepts);
}
#include <bits/crt/fenv-impl.h>
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_fetestexceptflag)(fexcept_t const *flagp,
                                            int excepts) {
	return __arch_fetestexceptflag(flagp, excepts);
}
#include <bits/crt/fenv-impl.h>
INTERN ATTR_SECTION(".text.crt.math.fenv") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_fegetmode)(femode_t *modep) {
	return __arch_fegetmode(modep);
}
#include <bits/crt/fenv-impl.h>
INTERN ATTR_SECTION(".text.crt.math.fenv") int
NOTHROW_NCX(LIBCCALL libc_fesetmode)(femode_t const *modep) {
	return __arch_fesetmode(modep);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(feraiseexcept,libc_feraiseexcept,,int,THROWING(...),LIBCCALL,(int excepts),(excepts));
DEFINE_PUBLIC_ALIAS_P(feclearexcept,libc_feclearexcept,,int,NOTHROW,LIBCCALL,(int excepts),(excepts));
DEFINE_PUBLIC_ALIAS_P(fegetexceptflag,libc_fegetexceptflag,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(fexcept_t *flagp, int excepts),(flagp,excepts));
DEFINE_PUBLIC_ALIAS_P(fesetexceptflag,libc_fesetexceptflag,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(fexcept_t const *flagp, int excepts),(flagp,excepts));
DEFINE_PUBLIC_ALIAS_P(fetestexcept,libc_fetestexcept,ATTR_PURE WUNUSED,int,NOTHROW,LIBCCALL,(int excepts),(excepts));
DEFINE_PUBLIC_ALIAS_P(fegetround,libc_fegetround,ATTR_PURE WUNUSED,int,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(fesetround,libc_fesetround,,int,NOTHROW,LIBCCALL,(int rounding_direction),(rounding_direction));
DEFINE_PUBLIC_ALIAS_P(fegetenv,libc_fegetenv,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(fenv_t *envp),(envp));
DEFINE_PUBLIC_ALIAS_P(feholdexcept,libc_feholdexcept,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(fenv_t *envp),(envp));
DEFINE_PUBLIC_ALIAS_P(fesetenv,libc_fesetenv,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(fenv_t const *envp),(envp));
DEFINE_PUBLIC_ALIAS_P(feupdateenv,libc_feupdateenv,ATTR_IN(1),int,NOTHROW_NCX,LIBCCALL,(fenv_t const *envp),(envp));
DEFINE_PUBLIC_ALIAS_P(feenableexcept,libc_feenableexcept,,int,NOTHROW,LIBCCALL,(int excepts),(excepts));
DEFINE_PUBLIC_ALIAS_P(fedisableexcept,libc_fedisableexcept,,int,NOTHROW,LIBCCALL,(int excepts),(excepts));
DEFINE_PUBLIC_ALIAS_P(fegetexcept,libc_fegetexcept,ATTR_PURE WUNUSED,int,NOTHROW,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(fesetexcept,libc_fesetexcept,,int,NOTHROW,LIBCCALL,(int excepts),(excepts));
DEFINE_PUBLIC_ALIAS_P(fetestexceptflag,libc_fetestexceptflag,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(fexcept_t const *flagp, int excepts),(flagp,excepts));
DEFINE_PUBLIC_ALIAS_P(fegetmode,libc_fegetmode,ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(femode_t *modep),(modep));
DEFINE_PUBLIC_ALIAS_P(fesetmode,libc_fesetmode,,int,NOTHROW_NCX,LIBCCALL,(femode_t const *modep),(modep));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_FENV_C */
