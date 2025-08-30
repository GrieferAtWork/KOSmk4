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
#include <asm/crt/fenv.h>
)]%[insert:prefix(
#include <bits/crt/fenv.h>
)]
%[insert:prefix(
#include <bits/crt/fenv-impl.h>
)]
%[insert:prefix(
#include <kos/anno.h>
)]


%[define_replacement(FE_ALL_EXCEPT = __FE_ALL_EXCEPT)]
%[define_replacement(FE_INVALID    = __FE_INVALID)]
%[define_replacement(FE_DIVBYZERO  = __FE_DIVBYZERO)]
%[define_replacement(FE_OVERFLOW   = __FE_OVERFLOW)]
%[define_replacement(FE_UNDERFLOW  = __FE_UNDERFLOW)]
%[define_replacement(FE_INEXACT    = __FE_INEXACT)]
%[define_replacement(FE_TONEAREST  = __FE_TONEAREST)]
%[define_replacement(FE_DOWNWARD   = __FE_DOWNWARD)]
%[define_replacement(FE_UPWARD     = __FE_UPWARD)]
%[define_replacement(FE_TOWARDZERO = __FE_TOWARDZERO)]

%{


/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __FE_INVALID
	FE_INVALID   = __FE_INVALID,
#endif /* __FE_INVALID */
#ifdef __FE_DIVBYZERO
	FE_DIVBYZERO = __FE_DIVBYZERO,
#endif /* __FE_DIVBYZERO */
#ifdef __FE_OVERFLOW
	FE_OVERFLOW  = __FE_OVERFLOW,
#endif /* __FE_OVERFLOW */
#ifdef __FE_UNDERFLOW
	FE_UNDERFLOW = __FE_UNDERFLOW,
#endif /* __FE_UNDERFLOW */
#ifdef __FE_INEXACT
	FE_INEXACT   = __FE_INEXACT
#endif /* __FE_INEXACT */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __FE_INVALID
#define FE_INVALID   FE_INVALID
#endif /* __FE_INVALID */
#ifdef __FE_DIVBYZERO
#define FE_DIVBYZERO FE_DIVBYZERO
#endif /* __FE_DIVBYZERO */
#ifdef __FE_OVERFLOW
#define FE_OVERFLOW  FE_OVERFLOW
#endif /* __FE_OVERFLOW */
#ifdef __FE_UNDERFLOW
#define FE_UNDERFLOW FE_UNDERFLOW
#endif /* __FE_UNDERFLOW */
#ifdef __FE_INEXACT
#define FE_INEXACT   FE_INEXACT
#endif /* __FE_INEXACT */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __FE_INVALID
#define FE_INVALID   __FE_INVALID
#endif /* __FE_INVALID */
#ifdef __FE_DIVBYZERO
#define FE_DIVBYZERO __FE_DIVBYZERO
#endif /* __FE_DIVBYZERO */
#ifdef __FE_OVERFLOW
#define FE_OVERFLOW  __FE_OVERFLOW
#endif /* __FE_OVERFLOW */
#ifdef __FE_UNDERFLOW
#define FE_UNDERFLOW __FE_UNDERFLOW
#endif /* __FE_UNDERFLOW */
#ifdef __FE_INEXACT
#define FE_INEXACT   __FE_INEXACT
#endif /* __FE_INEXACT */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

#ifndef FE_ALL_EXCEPT
#define FE_ALL_EXCEPT __FE_ALL_EXCEPT
#endif /* !FE_ALL_EXCEPT */

/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __FE_TONEAREST
	FE_TONEAREST  = __FE_TONEAREST, /* round() */
#endif /* __FE_TONEAREST */
#ifdef __FE_DOWNWARD
	FE_DOWNWARD   = __FE_DOWNWARD,  /* floor() */
#endif /* __FE_DOWNWARD */
#ifdef __FE_UPWARD
	FE_UPWARD     = __FE_UPWARD,    /* ceil() */
#endif /* __FE_UPWARD */
#ifdef __FE_TOWARDZERO
	FE_TOWARDZERO = __FE_TOWARDZERO /* trunc() */
#endif /* __FE_TOWARDZERO */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __FE_TONEAREST
#define FE_TONEAREST  FE_TONEAREST  /* round() */
#endif /* __FE_TONEAREST */
#ifdef __FE_DOWNWARD
#define FE_DOWNWARD   FE_DOWNWARD   /* floor() */
#endif /* __FE_DOWNWARD */
#ifdef __FE_UPWARD
#define FE_UPWARD     FE_UPWARD     /* ceil() */
#endif /* __FE_UPWARD */
#ifdef __FE_TOWARDZERO
#define FE_TOWARDZERO FE_TOWARDZERO /* trunc() */
#endif /* __FE_TOWARDZERO */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __FE_TONEAREST
#define FE_TONEAREST  __FE_TONEAREST  /* round() */
#endif /* __FE_TONEAREST */
#ifdef __FE_DOWNWARD
#define FE_DOWNWARD   __FE_DOWNWARD   /* floor() */
#endif /* __FE_DOWNWARD */
#ifdef __FE_UPWARD
#define FE_UPWARD     __FE_UPWARD     /* ceil() */
#endif /* __FE_UPWARD */
#ifdef __FE_TOWARDZERO
#define FE_TOWARDZERO __FE_TOWARDZERO /* trunc() */
#endif /* __FE_TOWARDZERO */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


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

/* If the default argument is used we use this value. */
#if !defined(FE_DFL_ENV) && defined(__FE_DFL_ENV)
#define FE_DFL_ENV __FE_DFL_ENV
#endif /* !FE_DFL_ENV && __FE_DFL_ENV */

#ifdef __USE_GNU
/* Floating-point environment where none of the exception is masked. */
#if !defined(FE_NOMASK_ENV) && defined(__FE_NOMASK_ENV)
#define FE_NOMASK_ENV __FE_NOMASK_ENV
#endif /* !FE_NOMASK_ENV && __FE_NOMASK_ENV */
#endif /* __USE_GNU */

}

%[insert:std]
%

%(auto_source){
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
}



@@>> feraiseexcept(3)
@@@param: excepts: Set of `FE_*'
@@@return: == 0 : All exceptions indicated by `excepts' were railed
@@@return: != 0 : At least one exception of `excepts' could not be raised
[[std, throws, extern_inline, libc, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_feraiseexcept))]]
int feraiseexcept(int excepts) {
	return __arch_feraiseexcept(excepts);
}

@@>> feclearexcept(3)
@@@param: excepts: Set of `FE_*'
@@@return: == 0 : All exceptions indicated by `excepts' were cleared
@@@return: != 0 : At least one exception of `excepts' could not be cleared
[[std, nothrow, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_feclearexcept))]]
int feclearexcept(int excepts) {
	return __arch_feclearexcept(excepts);
}

@@>> fegetexceptflag(3)
@@@return: == 0 : Success
@@@return: != 0 : Unspecified error
[[std, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fegetexceptflag))]]
int fegetexceptflag([[out]] fexcept_t *flagp, int excepts) {
	return __arch_fegetexceptflag(flagp, excepts);
}

@@>> fesetexceptflag(3)
@@@return: == 0 : Success
@@@return: != 0 : Unspecified error
[[std, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fesetexceptflag))]]
int fesetexceptflag([[in]] fexcept_t const *flagp, int excepts) {
	return __arch_fesetexceptflag(flagp, excepts);
}

@@>> fetestexcept(3)
[[std, nothrow, pure, wunused]]
[[extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fetestexcept))]]
int fetestexcept(int excepts) {
	/* Do `COMPILER_IMPURE()' to supress a false warning:
	 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=105682 */
	COMPILER_IMPURE();
	return __arch_fetestexcept(excepts);
}

@@>> fegetround(3)
@@Get the current rounding direction
@@@return: One of...
@@            ... `FE_TONEAREST':  round()
@@            ... `FE_DOWNWARD':   floor()
@@            ... `FE_UPWARD':     ceil()
@@            ... `FE_TOWARDZERO': trunc()
[[std, nothrow, pure, wunused, libc]]
[[extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fegetround))]]
int fegetround() {
	COMPILER_IMPURE();
	return __arch_fegetround();
}

@@>> fesetround(3)
@@Set the current rounding direction
@@@param: rounding_direction: One of...
@@            ... `FE_TONEAREST':  round()
@@            ... `FE_DOWNWARD':   floor()
@@            ... `FE_UPWARD':     ceil()
@@            ... `FE_TOWARDZERO': trunc()
[[std, nothrow, libc]]
[[extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fesetround))]]
int fesetround(int rounding_direction) {
	return __arch_fesetround(rounding_direction);
}

@@>> fegetenv(3)
[[std, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fegetenv))]]
int fegetenv([[out]] fenv_t *envp) {
	return __arch_fegetenv(envp);
}

@@>> feholdexcept(3)
[[std, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_feholdexcept))]]
int feholdexcept([[out]] fenv_t *envp) {
	return __arch_feholdexcept(envp);
}

@@>> fesetenv(3)
[[std, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fesetenv))]]
int fesetenv([[in]] fenv_t const *envp) {
	return __arch_fesetenv(envp);
}

@@>> feupdateenv(3)
[[std, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_feupdateenv))]]
int feupdateenv([[in]] fenv_t const *envp) {
	return __arch_feupdateenv(envp);
}


%#ifdef __USE_GNU
@@>> feenableexcept(3)
@@@return: * : The old set of enabled exceptions
[[nothrow, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_feenableexcept))]]
int feenableexcept(int excepts) {
	return __arch_feenableexcept(excepts);
}

@@>> fedisableexcept(3)
@@@return: * : The old set of enabled exceptions
[[nothrow, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fedisableexcept))]]
int fedisableexcept(int excepts) {
	return __arch_fedisableexcept(excepts);
}

@@>> fegetexcept(3)
[[wunused, nothrow, pure, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fegetexcept))]]
int fegetexcept() {
	COMPILER_IMPURE();
	return __arch_fegetexcept();
}

%#endif /* __USE_GNU */

%
%#if defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__)
%{
typedef __femode_t femode_t;
#if !defined(FE_DFL_MODE) && defined(__FE_DFL_MODE)
#define FE_DFL_MODE __FE_DFL_MODE
#endif /* !FE_DFL_MODE && __FE_DFL_MODE */
}
%[define_replacement(femode_t = "__femode_t")]

[[nothrow, extern_inline, impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fesetexcept))]]
int fesetexcept(int excepts) {
	return __arch_fesetexcept(excepts);
}

[[pure, wunused, extern_inline]]
[[decl_include("<bits/crt/fenv.h>")]]
[[impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fetestexceptflag))]]
int fetestexceptflag($fexcept_t const *flagp, int excepts) {
	return __arch_fetestexceptflag(flagp, excepts);
}

[[extern_inline]]
[[decl_include("<bits/crt/fenv.h>")]]
[[impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fegetmode))]]
int fegetmode([[out]] femode_t *modep) {
	return __arch_fegetmode(modep);
}

[[extern_inline]]
[[decl_include("<bits/crt/fenv.h>")]]
[[impl_include("<bits/crt/fenv-impl.h>")]]
[[requires($extended_include_prefix("<bits/crt/fenv-impl.h>")defined(__arch_fesetmode))]]
int fesetmode(femode_t const *modep) {
	return __arch_fesetmode(modep);
}

%{

#if defined(FE_INVALID) && defined(__SUPPORT_SNAN__)
#define FE_SNANS_ALWAYS_SIGNAL 1
#endif /* FE_INVALID && __SUPPORT_SNAN__ */
}
%#endif /* __USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__ */

%(libc_fast){
/*[[[deemon
import * from deemon;
function printWrappersWithOptions(__libc_foo: string, OPTIONS: {{string...}...}) {
	print("#ifdef ", __libc_foo);
	for (local options: OPTIONS) {
		if (#options == 1) {
			print("#ifdef __", options.first);
		} else {
			print("#if ", " && ".join(for (local o: options) f"defined(__{o})"));
		}
		print("#define ", __libc_foo, "_", "_".join(options),
			  "() (void)", __libc_foo, "(",
			  " | ".join(for (local o: options) f"__{o}"),
			  ")");
		if (#options == 1) {
			print("#endif /" "* __", options.first, " *" "/");
		} else {
			print("#endif /" "*", " && ".join(for (local o: options) f"__{o}"), " *" "/");
		}
	}
	print("#endif /" "* ", __libc_foo, " *" "/");
	for (local options: OPTIONS) {
		local name = f"{__libc_foo}_{"_".join(options)}";
		print("#ifndef ", name);
		print("#define ", name, "() (void)0");
		print("#endif /" "* !", name, " *" "/");
	}
}

printWrappersWithOptions("__libc_feraiseexcept", {
	{ "FE_UNDERFLOW" },
	{ "FE_OVERFLOW" },
	{ "FE_INEXACT" },
	{ "FE_INVALID", "FE_INEXACT" },
	{ "FE_INVALID" },
});
]]]*/
#ifdef __libc_feraiseexcept
#ifdef __FE_UNDERFLOW
#define __libc_feraiseexcept_FE_UNDERFLOW() (void)__libc_feraiseexcept(__FE_UNDERFLOW)
#endif /* __FE_UNDERFLOW */
#ifdef __FE_OVERFLOW
#define __libc_feraiseexcept_FE_OVERFLOW() (void)__libc_feraiseexcept(__FE_OVERFLOW)
#endif /* __FE_OVERFLOW */
#ifdef __FE_INEXACT
#define __libc_feraiseexcept_FE_INEXACT() (void)__libc_feraiseexcept(__FE_INEXACT)
#endif /* __FE_INEXACT */
#if defined(__FE_INVALID) && defined(__FE_INEXACT)
#define __libc_feraiseexcept_FE_INVALID_FE_INEXACT() (void)__libc_feraiseexcept(__FE_INVALID | __FE_INEXACT)
#endif /*__FE_INVALID && __FE_INEXACT */
#ifdef __FE_INVALID
#define __libc_feraiseexcept_FE_INVALID() (void)__libc_feraiseexcept(__FE_INVALID)
#endif /* __FE_INVALID */
#endif /* __libc_feraiseexcept */
#ifndef __libc_feraiseexcept_FE_UNDERFLOW
#define __libc_feraiseexcept_FE_UNDERFLOW() (void)0
#endif /* !__libc_feraiseexcept_FE_UNDERFLOW */
#ifndef __libc_feraiseexcept_FE_OVERFLOW
#define __libc_feraiseexcept_FE_OVERFLOW() (void)0
#endif /* !__libc_feraiseexcept_FE_OVERFLOW */
#ifndef __libc_feraiseexcept_FE_INEXACT
#define __libc_feraiseexcept_FE_INEXACT() (void)0
#endif /* !__libc_feraiseexcept_FE_INEXACT */
#ifndef __libc_feraiseexcept_FE_INVALID_FE_INEXACT
#define __libc_feraiseexcept_FE_INVALID_FE_INEXACT() (void)0
#endif /* !__libc_feraiseexcept_FE_INVALID_FE_INEXACT */
#ifndef __libc_feraiseexcept_FE_INVALID
#define __libc_feraiseexcept_FE_INVALID() (void)0
#endif /* !__libc_feraiseexcept_FE_INVALID */
/*[[[end]]]*/
#if defined(__libc_fegetround) && defined(__libc_fesetround)
#ifdef __OPTIMIZE_SIZE__
#define __libc_fepushround(rounding_direction)       \
	do {                                             \
		int __lfpr_old_round = __libc_fegetround();  \
		(void)__libc_fesetround(rounding_direction); \
		(void)0
#define __libc_fepopround(rounding_direction) \
		__libc_fesetround(__lfpr_old_round);  \
	}	__WHILE0
#else /* __OPTIMIZE_SIZE__ */
#define __libc_fepushround(rounding_direction)           \
	do {                                                 \
		int __lfpr_old_round = __libc_fegetround();      \
		if (__lfpr_old_round != (rounding_direction))    \
			(void)__libc_fesetround(rounding_direction); \
		(void)0
#define __libc_fepopround(rounding_direction)         \
		if (__lfpr_old_round != (rounding_direction)) \
			__libc_fesetround(__lfpr_old_round);      \
	}	__WHILE0
#endif /* !__OPTIMIZE_SIZE__ */
#else /* __libc_fegetround && __libc_fesetround */
#define __libc_fepushround(rounding_direction) do {
#define __libc_fepopround(rounding_direction)  } __WHILE0
#endif /* !__libc_fegetround || !__libc_fesetround */
#ifdef __FE_TONEAREST
#define __libc_fepushround_FE_TONEAREST() __libc_fepushround(__FE_TONEAREST)
#define __libc_fepopround_FE_TONEAREST()  __libc_fepopround(__FE_TONEAREST)
#else /* __FE_TONEAREST */
#define __libc_fepushround_FE_TONEAREST() do {
#define __libc_fepopround_FE_TONEAREST()  } __WHILE0
#endif /* !__FE_TONEAREST */
}

%{

__SYSDECL_END
#endif /* __CC__ */

}
%(c, ccompat)#endif /* !__NO_FPU */
