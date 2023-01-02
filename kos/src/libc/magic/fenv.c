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
%(c_prefix){
/* (>) Standard: ISO C99 (ISO/IEC 9899:1999) */
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/newlib/libc/include/fenv.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/fenv.h) */
/* (#) Portability: GNU C Library (/math/fenv.h) */
/* (#) Portability: GNU Hurd      (/usr/include/fenv.h) */
/* (#) Portability: MSVC          (/include/fenv.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/fenv.h) */
/* (#) Portability: NetBSD        (/include/fenv.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/fenv.h) */
/* (#) Portability: OpenBSD       (/include/fenv.h) */
/* (#) Portability: Windows Kits  (/ucrt/fenv.h) */
/* (#) Portability: diet libc     (/include/fenv.h) */
/* (#) Portability: libc6         (/include/fenv.h) */
/* (#) Portability: musl libc     (/include/fenv.h) */
/* (#) Portability: uClibc        (/include/fenv.h) */
}

%[define_ccompat_header("cfenv")]
%[define_replacement(errno_t = __errno_t)]
%[define_replacement(fexcept_t = __fexcept_t)]
%[define_replacement(fenv_t = "struct __fenv_struct")]
%[define_partial_replacement(envp = ___envp)]
%[default:section(".text.crt{|.dos}.math.fenv")]

%(c, ccompat)#ifndef __NO_FPU
%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/crt/fenv.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%[insert:prefix(
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/fenv.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

__NAMESPACE_STD_BEGIN
#ifndef __std_fenv_t_defined
#define __std_fenv_t_defined
typedef struct __fenv_struct fenv_t;
#endif /* !__std_fenv_t_defined */
#ifndef __std_fexcept_t_defined
#define __std_fexcept_t_defined
typedef __fexcept_t fexcept_t;
#endif /* !__std_fexcept_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef ___fenv_t_defined
#define ___fenv_t_defined
__NAMESPACE_STD_USING(fenv_t)
#endif /* !___fenv_t_defined */
#ifndef __fexcept_t_defined
#define __fexcept_t_defined
__NAMESPACE_STD_USING(fexcept_t)
#endif /* !__fexcept_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

}

%[insert:std]
%


@@>> feclearexcept(3)
@@@param: excepts: Set of `FE_*'
[[std, nothrow, preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int feclearexcept(int excepts) {
	@__inline_feclearexcept@(excepts);
	return 0;
}

@@>> feraiseexcept(3)
@@@param: excepts: Set of `FE_*'
[[std, throws, preferred_fastbind, libc, impl_include("<bits/crt/fenv-inline.h>")]]
int feraiseexcept(int excepts) {
	@__inline_feraiseexcept@(excepts);
	return 0;
}

@@>> fegetexceptflag(3)
[[std, preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int fegetexceptflag([[out]] fexcept_t *flagp, int excepts) {
@@pp_ifdef __inline_fegetexceptflag@@
	__inline_fegetexceptflag(flagp, excepts);
@@pp_else@@
	*flagp = 0;
	(void)excepts;
@@pp_endif@@
	return 0;
}

@@>> fesetexceptflag(3)
[[std, preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int fesetexceptflag([[in]] fexcept_t const *flagp, int excepts) {
@@pp_ifdef __inline_fesetexceptflag@@
	__inline_fesetexceptflag(flagp, excepts);
@@pp_else@@
	(void)flagp;
	(void)excepts;
	COMPILER_IMPURE();
@@pp_endif@@
	return 0;
}

@@>> fetestexcept(3)
[[std, nothrow, pure, wunused]]
[[preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int fetestexcept(int excepts) {
	/* Do `COMPILER_IMPURE()' to supress a false warning:
	 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=105682 */
	COMPILER_IMPURE();
	return __inline_fetestexcept(excepts);
}

@@>> fegetround(3)
@@Get the current rounding direction
@@@return: One of...
@@            ... `FE_TONEAREST':  round()
@@            ... `FE_DOWNWARD':   floor()
@@            ... `FE_UPWARD':     ceil()
@@            ... `FE_TOWARDZERO': trunc()
[[std, nothrow, pure, wunused, libc]]
[[preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int fegetround() {
	return __inline_fegetround();
}

@@>> fesetround(3)
@@Set the current rounding direction
@@@param: rounding_direction: One of...
@@            ... `FE_TONEAREST':  round()
@@            ... `FE_DOWNWARD':   floor()
@@            ... `FE_UPWARD':     ceil()
@@            ... `FE_TOWARDZERO': trunc()
[[std, nothrow, libc]]
[[preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int fesetround(int rounding_direction) {
	return __inline_fesetround(rounding_direction);
}

@@>> fegetenv(3)
[[std, preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int fegetenv([[out]] fenv_t *envp) {
	__inline_fegetenv(envp);
	return 0;
}

@@>> feholdexcept(3)
[[std, preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int feholdexcept([[out]] fenv_t *envp) {
	__inline_feholdexcept(envp);
	return 0;
}

@@>> fesetenv(3)
[[std, preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int fesetenv([[in]] fenv_t const *envp) {
	__inline_fesetenv(envp);
	return 0;
}

@@>> feupdateenv(3)
[[std, preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int feupdateenv([[in]] fenv_t const *envp) {
	__inline_feupdateenv(envp);
	return 0;
}


%#ifdef __USE_GNU
@@>> feenableexcept(3)
[[nothrow, preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int feenableexcept(int excepts) {
	return __inline_feenableexcept(excepts);
}

@@>> fedisableexcept(3)
[[nothrow, preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int fedisableexcept(int excepts) {
	return __inline_fedisableexcept(excepts);
}

@@>> fegetexcept(3)
[[wunused, nothrow, pure]]
[[preferred_fastbind, impl_include("<bits/crt/fenv-inline.h>")]]
int fegetexcept() {
	return __inline_fegetexcept();
}

%#endif /* __USE_GNU */

%
%#if defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__)
/* TODO: These 2 need to got into <bits/crt/fenv.h> */
%{
typedef unsigned int femode_t;
#define FE_DFL_MODE ((femode_t const *)-1)
}
%[define_replacement(femode_t = "unsigned int")]

int fesetexcept(int excepts);
int fetestexceptflag($fexcept_t const *flagp, int excepts);
int fegetmode(femode_t *modep);
int fesetmode(femode_t const *modep);

%{
#if defined(FE_INVALID) && defined(__SUPPORT_SNAN__)
#define FE_SNANS_ALWAYS_SIGNAL 1
#endif /* FE_INVALID && __SUPPORT_SNAN__ */
}
%#endif /* __USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__ */

%{

__SYSDECL_END
#endif /* __CC__ */

}
%(c, ccompat)#endif /* !__NO_FPU */
