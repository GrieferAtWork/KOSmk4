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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_ccompat_header(cfenv)]
%[define_replacement(errno_t = __errno_t)]
%[default_impl_section(.text.crt.math.fenv)]

%(c, ccompat)#ifndef __NO_FPU
%{
#include <features.h>

#include <bits/fenv.h>

/* Documentation comments are taken from glibc /usr/include/fenv.h */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __CC__

__NAMESPACE_STD_BEGIN
#ifndef __std_fenv_t_defined
#define __std_fenv_t_defined 1
typedef struct __fenv_struct fenv_t;
#endif /* !__std_fenv_t_defined */
#ifndef __std_fexcept_t_defined
#define __std_fexcept_t_defined 1
typedef __fexcept_t fexcept_t;
#endif /* !__std_fexcept_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef ___fenv_t_defined
#define ___fenv_t_defined 1
__NAMESPACE_STD_USING(fenv_t)
#endif /* !___fenv_t_defined */
#ifndef __fexcept_t_defined
#define __fexcept_t_defined 1
__NAMESPACE_STD_USING(fexcept_t)
#endif /* !__fexcept_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

}

%[insert:std]
%


@@Clear the supported exceptions represented by EXCEPTS
[std][nothrow][fast][dependency_include(<bits/fenv-inline.h>)]
feclearexcept:(int excepts) -> int {
	@__inline_feclearexcept@(excepts);
	return 0;
}

@@Raise the supported exceptions represented by EXCEPTS
[std][throws][fast][dependency_include(<bits/fenv-inline.h>)]
feraiseexcept:(int excepts) -> int {
	@__inline_feraiseexcept@(excepts);
	return 0;
}

@@Store implementation-defined representation of the exception
@@flags indicated by EXCEPTS in the object pointed to by FLAGP
[std][fast][dependency_include(<bits/fenv-inline.h>)]
fegetexceptflag:([nonnull] fexcept_t *flagp, int excepts) -> int {
#ifdef @__inline_fegetexceptflag@
	@__inline_fegetexceptflag@(flagp, excepts);
#else /* __inline_fegetexceptflag */
	*flagp = 0;
	(void)excepts;
#endif /* !__inline_fegetexceptflag */
	return 0;
}

@@Set complete status for exceptions indicated by EXCEPTS according
@@to the representation in the object pointed to by FLAGP
[std][fast][dependency_include(<bits/fenv-inline.h>)]
fesetexceptflag:([nonnull] fexcept_t const *flagp, int excepts) -> int {
#ifdef @__inline_fesetexceptflag@
	@__inline_fesetexceptflag@(flagp, excepts);
#else /* __inline_fesetexceptflag */
	(void)flagp;
	(void)excepts;
	COMPILER_IMPURE();
#endif /* !__inline_fesetexceptflag */
	return 0;
}

@@Determine which of subset of the exceptions
@@specified by EXCEPTS are currently set
[std][nothrow][ATTR_PURE][ATTR_WUNUSED]
[fast][dependency_include(<bits/fenv-inline.h>)]
fetestexcept:(int excepts) -> int {
	return @__inline_fetestexcept@(excepts);
}

@@Get current rounding direction
[std][nothrow][ATTR_PURE][ATTR_WUNUSED]
[fast][dependency_include(<bits/fenv-inline.h>)]
fegetround:() -> int {
	return @__inline_fegetround@();
}

@@Establish the rounding direction represented by ROUND
[std][nothrow]
[fast][dependency_include(<bits/fenv-inline.h>)]
fesetround:(int rounding_direction) -> int {
	return @__inline_fesetround@(rounding_direction);
}

@@Store the current floating-point environment in the object pointed to by ENVP
[std][fast][dependency_include(<bits/fenv-inline.h>)]
fegetenv:([nonnull] fenv_t *envp) -> int {
	@__inline_fegetenv@(envp);
	return 0;
}

@@Save the current environment in the object pointed to by ENVP, clear
@@exception flags and install a non-stop mode (if available) for all exceptions
[std][fast][dependency_include(<bits/fenv-inline.h>)]
feholdexcept:([nonnull] fenv_t *envp) -> int {
	@__inline_feholdexcept@(envp);
	return 0;
}

@@Establish the floating-point environment represented by the object pointed to by ENVP
[std][fast][dependency_include(<bits/fenv-inline.h>)]
fesetenv:([nonnull] fenv_t const *envp) -> int {
	@__inline_fesetenv@(envp);
	return 0;
}

@@Save current exceptions in temporary storage, install environment
@@represented by object pointed to by ENVP and raise exceptions
@@according to saved exceptions
[std][fast][dependency_include(<bits/fenv-inline.h>)]
feupdateenv:([nonnull] fenv_t const *envp) -> int {
	@__inline_feupdateenv@(envp);
	return 0;
}


%#ifdef __USE_GNU

@@Enable individual exceptions.  Will not enable more exceptions than
@@EXCEPTS specifies.  Returns the previous enabled exceptions if all
@@exceptions are successfully set, otherwise returns -1
[nothrow][fast][dependency_include(<bits/fenv-inline.h>)]
feenableexcept:(int excepts) -> int {
	return @__inline_feenableexcept@(excepts);
}

@@Disable individual exceptions.  Will not disable more exceptions than
@@EXCEPTS specifies.  Returns the previous enabled exceptions if all
@@exceptions are successfully disabled, otherwise returns -1
[nothrow][fast][dependency_include(<bits/fenv-inline.h>)]
fedisableexcept:(int excepts) -> int {
	return @__inline_fedisableexcept@(excepts);
}

@@Return enabled exceptions
[nothrow][ATTR_WUNUSED][ATTR_PURE]
[fast][dependency_include(<bits/fenv-inline.h>)]
fegetexcept:() -> int {
	return @__inline_fegetexcept@();
}

%#endif /* __USE_GNU */

%{

#endif /* __CC__ */

__SYSDECL_END

}
%(c, ccompat)#endif /* !__NO_FPU */
