/* HASH CRC-32:0xc976d2f */
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
#ifndef _LIBC_FENV_H
#define _LIBC_FENV_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include "core/fenv.h"

#if !defined(____libc_feraiseexcept_defined) && defined(____libc_core_feraiseexcept_defined)
#define ____libc_feraiseexcept_defined
#define __libc_feraiseexcept __libc_core_feraiseexcept
#endif /* !____libc_feraiseexcept_defined && ____libc_core_feraiseexcept_defined */
#if !defined(____libc_fegetround_defined) && defined(____libc_core_fegetround_defined)
#define ____libc_fegetround_defined
#define __libc_fegetround __libc_core_fegetround
#endif /* !____libc_fegetround_defined && ____libc_core_fegetround_defined */
#if !defined(____libc_fesetround_defined) && defined(____libc_core_fesetround_defined)
#define ____libc_fesetround_defined
#define __libc_fesetround __libc_core_fesetround
#endif /* !____libc_fesetround_defined && ____libc_core_fesetround_defined */
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

#endif /* __CC__ */

#endif /* !_LIBC_FENV_H */
