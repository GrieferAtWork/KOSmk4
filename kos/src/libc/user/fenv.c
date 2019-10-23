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
#ifndef GUARD_LIBC_USER_FENV_C
#define GUARD_LIBC_USER_FENV_C 1

#include "../api.h"
#include "fenv.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:feclearexcept,hash:CRC-32=0xf5fd540f]]]*/
/* Clear the supported exceptions represented by EXCEPTS */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.feclearexcept") int
NOTHROW(LIBCCALL libc_feclearexcept)(int excepts)
/*[[[body:feclearexcept]]]*/
{
	CRT_UNIMPLEMENTED("feclearexcept"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:feclearexcept]]]*/

/*[[[head:fegetexceptflag,hash:CRC-32=0x5e627861]]]*/
/* Store implementation-defined representation of the exception
 * flags indicated by EXCEPTS in the object pointed to by FLAGP */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.fegetexceptflag") int
NOTHROW_NCX(LIBCCALL libc_fegetexceptflag)(fexcept_t *flagp,
                                           int excepts)
/*[[[body:fegetexceptflag]]]*/
{
	CRT_UNIMPLEMENTED("fegetexceptflag"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fegetexceptflag]]]*/

/*[[[head:feraiseexcept,hash:CRC-32=0x915b14d2]]]*/
/* Raise the supported exceptions represented by EXCEPTS */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.feraiseexcept") int
NOTHROW(LIBCCALL libc_feraiseexcept)(int excepts)
/*[[[body:feraiseexcept]]]*/
{
	CRT_UNIMPLEMENTED("feraiseexcept"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:feraiseexcept]]]*/

/*[[[head:fesetexceptflag,hash:CRC-32=0x3daa6641]]]*/
/* Set complete status for exceptions indicated by EXCEPTS according
 * to the representation in the object pointed to by FLAGP */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.fesetexceptflag") int
NOTHROW_NCX(LIBCCALL libc_fesetexceptflag)(fexcept_t const *flagp,
                                           int excepts)
/*[[[body:fesetexceptflag]]]*/
{
	CRT_UNIMPLEMENTED("fesetexceptflag"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fesetexceptflag]]]*/

/*[[[head:fetestexcept,hash:CRC-32=0xce7f108b]]]*/
/* Determine which of subset of the exceptions
 * specified by EXCEPTS are currently set */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.fetestexcept") int
NOTHROW(LIBCCALL libc_fetestexcept)(int excepts)
/*[[[body:fetestexcept]]]*/
{
	CRT_UNIMPLEMENTED("fetestexcept"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fetestexcept]]]*/

/*[[[head:fegetround,hash:CRC-32=0x21d3accc]]]*/
/* Get current rounding direction */
INTERN ATTR_PURE
ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.fegetround") int
NOTHROW(LIBCCALL libc_fegetround)(void)
/*[[[body:fegetround]]]*/
{
	CRT_UNIMPLEMENTED("fegetround"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fegetround]]]*/

/*[[[head:fesetround,hash:CRC-32=0x63ff237d]]]*/
/* Establish the rounding direction represented by ROUND */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.fesetround") int
NOTHROW(LIBCCALL libc_fesetround)(int rounding_direction)
/*[[[body:fesetround]]]*/
{
	CRT_UNIMPLEMENTED("fesetround"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fesetround]]]*/

/*[[[head:fegetenv,hash:CRC-32=0xf87fb68a]]]*/
/* Store the current floating-point environment in the object pointed to by ENVP */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.fegetenv") int
NOTHROW_NCX(LIBCCALL libc_fegetenv)(fenv_t *envp)
/*[[[body:fegetenv]]]*/
{
	CRT_UNIMPLEMENTED("fegetenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fegetenv]]]*/

/*[[[head:feholdexcept,hash:CRC-32=0xf17410d0]]]*/
/* Save the current environment in the object pointed to by ENVP, clear
 * exception flags and install a non-stop mode (if available) for all exceptions */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.feholdexcept") int
NOTHROW_NCX(LIBCCALL libc_feholdexcept)(fenv_t *envp)
/*[[[body:feholdexcept]]]*/
{
	CRT_UNIMPLEMENTED("feholdexcept"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:feholdexcept]]]*/

/*[[[head:fesetenv,hash:CRC-32=0xdd4ba9c5]]]*/
/* Establish the floating-point environment represented by the object pointed to by ENVP */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.fesetenv") int
NOTHROW_NCX(LIBCCALL libc_fesetenv)(fenv_t const *envp)
/*[[[body:fesetenv]]]*/
{
	CRT_UNIMPLEMENTED("fesetenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fesetenv]]]*/

/*[[[head:feupdateenv,hash:CRC-32=0xee809ec7]]]*/
/* Save current exceptions in temporary storage, install environment
 * represented by object pointed to by ENVP and raise exceptions
 * according to saved exceptions */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.feupdateenv") int
NOTHROW_NCX(LIBCCALL libc_feupdateenv)(fenv_t const *envp)
/*[[[body:feupdateenv]]]*/
{
	CRT_UNIMPLEMENTED("feupdateenv"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:feupdateenv]]]*/

/*[[[head:feenableexcept,hash:CRC-32=0xdb6ea890]]]*/
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.feenableexcept") int
NOTHROW(LIBCCALL libc_feenableexcept)(int excepts)
/*[[[body:feenableexcept]]]*/
{
	CRT_UNIMPLEMENTED("feenableexcept"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:feenableexcept]]]*/

/*[[[head:fedisableexcept,hash:CRC-32=0xb9b3df6e]]]*/
/* Disable individual exceptions.  Will not disable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully disabled, otherwise returns -1 */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.fedisableexcept") int
NOTHROW(LIBCCALL libc_fedisableexcept)(int excepts)
/*[[[body:fedisableexcept]]]*/
{
	CRT_UNIMPLEMENTED("fedisableexcept"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fedisableexcept]]]*/

/*[[[head:fegetexcept,hash:CRC-32=0xc8f3633d]]]*/
/* Return enabled exceptions */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.math.fenv.fegetexcept") int
NOTHROW(LIBCCALL libc_fegetexcept)(void)
/*[[[body:fegetexcept]]]*/
{
	CRT_UNIMPLEMENTED("fegetexcept"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:fegetexcept]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xf5ba3c19]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(feclearexcept, libc_feclearexcept);
DEFINE_PUBLIC_WEAK_ALIAS(fegetexceptflag, libc_fegetexceptflag);
DEFINE_PUBLIC_WEAK_ALIAS(feraiseexcept, libc_feraiseexcept);
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
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FENV_C */
