/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](arg1) -> arg1.startswith("-O")))
	gcc_opt.append("-Os"); // Optimize for size, rather than speed
]]]*/
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_MATHERR_C
#define GUARD_LIBC_LIBC_MATHERR_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#ifndef __NO_FPU
#include <hybrid/atomic.h>

#include <bits/math-constants.h>
#include <kos/types.h>

#include <dlfcn.h>
#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <libm/matherr.h>

#include "dl.h"
#include "globals.h"

DECL_BEGIN

#ifdef __cplusplus
struct __exception;
#define STRUCT_EXCEPTION struct __exception
#else /* __cplusplus */
struct exception;
#define STRUCT_EXCEPTION struct exception
#endif /* !__cplusplus */

/* Public API:
 *
 * >> int matherr(struct exception *exc);
 * >> extern _LIB_VERSION_TYPE _LIB_VERSION;
 */
#undef _LIB_VERSION
INTERN ATTR_SECTION(".data.crt.math.math")
_LIB_VERSION_TYPE libc__LIB_VERSION = _POSIX_; /* Default to _POSIX_ mode. */
/* IMPORTANT: WEAK, so the main program's override has higher priority! */
DEFINE_PUBLIC_WEAK_ALIAS(_LIB_VERSION, libc__LIB_VERSION);
DECLARE_NOREL_GLOBAL_META(_LIB_VERSION_TYPE, _LIB_VERSION);
DEFINE_NOREL_GLOBAL_META(_LIB_VERSION_TYPE, _LIB_VERSION, ".math.math");
#define _LIB_VERSION GET_NOREL_GLOBAL(_LIB_VERSION)

INTERN ATTR_CONST WUNUSED ATTR_SECTION(".text.crt.math.math") __LIBM_LIB_VERSION_TYPE
NOTHROW(LIBCCALL libc___LIBM_GET_LIB_VERSION)(void) {
	return (__LIBM_LIB_VERSION_TYPE)_LIB_VERSION;
}

#undef _LIB_VERSION
#define _LIB_VERSION ((_LIB_VERSION_TYPE)libc___LIBM_GET_LIB_VERSION())

/* Default (no-op) matherr fallback. -- Only used when the  main
 * program doesn't export an override function by the same name. */
/* IMPORTANT: WEAK, so the main program's override has higher priority! */
DEFINE_PUBLIC_WEAK_ALIAS(matherr, libc_matherr);
INTERN ATTR_SECTION(".text.crt.math.math")
int LIBKCALL libc_matherr(STRUCT_EXCEPTION *exc) {
	COMPILER_IMPURE();
	(void)exc;
	return 0;
}


/* If non-NULL, the  currently used `matherr(3)'  handler in  "libc/matherr.c"
 * When `NULL', lazily load the matherr handler via `dlsym(3D)', and fall back
 * to a no-op handler when no override was defined. */
typedef int (LIBKCALL *LPMATHERR)(STRUCT_EXCEPTION *exc);
INTERN ATTR_SECTION(".bss.crt.math.math") LPMATHERR libc_pdyn_matherr = NULL;

/* Retrieve the global override function pointer for `matherr(3)'
 *
 * This function is special in that we _need_ to allow the  main
 * program  (or some other library) to override it. As such, the
 * libc fallback is declared WEAK, and when we first want to use
 * it, we do a dlsym(3) for the symbol.
 *
 * Using standard ELF conventions, we could also just reference
 * a __attribute__((visibility("default"))) symbol by the  name
 * "matherr", but  doing that  would result  in an  unnecessary
 * runtime relocation (and KOS's  libc is designed to  minimize
 * all such relocations to their bare minima) */
PRIVATE ATTR_SECTION(".rodata.crt.math.math") char const name_matherr[] = "matherr";
PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.math.math")
LPMATHERR NOTHROW(LIBCCALL libc_get_matherr)(void) {
	LPMATHERR result;
	while ((result = ATOMIC_READ(libc_pdyn_matherr)) == NULL) {
		/* Lazily load on first access. */
		*(void **)&result = dlsym(RTLD_DEFAULT, name_matherr);
		if unlikely(!result)
			result = &libc_matherr; /* Really shouldn't happen. -- libdl should have found our version... */
		ATOMIC_CMPXCH(libc_pdyn_matherr, NULL, result);
	}
	return result;
}
PRIVATE WUNUSED NONNULL((1)) ATTR_SECTION(".text.crt.math.math") int
NOTHROW(LIBCCALL libc_call_matherr)(STRUCT_EXCEPTION *__restrict exc) {
	/* NOTE: If  there ever is a need to  support different ABIs on how `matherr(3)'
	 *       should be called (regarding the `struct exception' it expects to take),
	 *       then support for them may be added in here (via `libc_compat()' checks) */
	LPMATHERR func = libc_get_matherr();
	return (*func)(exc);
}
#undef matherr
#define matherr(exc) libc_call_matherr(exc)


/* Return the (public) name of a math function, given a pointer into its body. */
PRIVATE ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.math.math") char *LIBCCALL
libc_math_funcname_from_pc(void const *return_pc_in_math_function) {
	char *result;
	Dl_info info;
	if (dladdr((byte_t const *)return_pc_in_math_function - 1, &info) != 0) {
		/* Shouldn't get here (XXX:  what if GCC places  __kernel_standard
		 * calls in one of those "*.cold" functions? -- Is there some  way
		 * for us to prevent it from doing so? Or more general: is there a
		 * commandline option for  "dont-move-function-body-pc-outside-of-
		 * elf-.size-directive-ranges"?) */
		return (char *)"?";
	}
	result = (char *)info.dli_sname;
	if unlikely(!result)
		return (char *)"?"; /* Really shouldn't happen */
	/* Check for case where libdl gave us the "__*" alias for the function.
	 * Note that we don't have to worry about the "libc_*" alias, since the
	 * `dladdr()' function we're using  only search .dymsym, which  doesn't
	 * contain INTERN symbols, but only PUBLIC ones. */
	if (result[0] == '_' && result[1] == '_')
		result += 2;
	return result;
}



/* NOTE: The actual selection of how  math errors should be  handled
 *       is derived from what is done by "fdlibm". See the following
 *       copyright  notice taken from its file "k_standard.c", which
 *       does all of the error handling stuff. */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#if 0
PRIVATE ATTR_SECTION(".rodata.crt.math.math")
double const zero = 0.0; /* used as const */
#else
/* Work-around for a GCC bug that doesn't delay "0.0/0.0" division until runtime. */
INTERN_CONST ATTR_SECTION(".rodata.crt.math.math")
double const __libc_matherr_zero = 0.0; /* used as const */
INTDEF double zero ASMNAME("__libc_matherr_zero");
#endif

#define nan(tag) __NAN

PRIVATE NONNULL((1)) ATTR_SECTION(".text.crt.math.math") void LIBCCALL
libc_matherr_writerr(char const *__restrict message) {
	/* Flush all streams, so our message appears at the very end. */
	(void)fflush(NULL);

	/* Directly write the message to the system `stderr' file. */
	(void)write(STDERR_FILENO, message, strlen(message) * sizeof(char));
}

INTERN ATTR_SECTION(".text.crt.math.math") double LIBCCALL
libc_handle_matherr(void const *return_pc_in_math_function,
                    double arg1, double arg2, double retval,
                    enum __libm_matherr type) {
#define WRITE_ERROR(message) libc_matherr_writerr(message)
	STRUCT_EXCEPTION exc;
	_LIB_VERSION_TYPE version = _LIB_VERSION;

	/* To cut down on  memory bloat as the  result of hundreds of  strings
	 * containing the names of math functions being duplicated, when  they
	 * already appear in .dynstr, we ask `libdl' to give use those .dynstr
	 * strings for function names, just so  we don't have to repeat  them! */
	exc.name   = libc_math_funcname_from_pc(return_pc_in_math_function);
	exc.arg1   = arg1;
	exc.arg2   = arg2;
	exc.retval = retval;
	exc.err    = 0;

	/* BEGIN: TAKEN FROM fdlibm (with various modifications) */
	switch (type) {

	case __LIBM_KMATHERR_ACOS:
	case __LIBM_KMATHERRF_ACOS:
	case __LIBM_KMATHERRL_ACOS:
		/* acos(|arg1|>1) */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = HUGE;
		} else {
			exc.retval = nan("");
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("acos: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_ASIN:
	case __LIBM_KMATHERRF_ASIN:
	case __LIBM_KMATHERRL_ASIN:
		/* asin(|arg1|>1) */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = HUGE;
		} else {
			exc.retval = nan("");
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("asin: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_ATAN2:
	case __LIBM_KMATHERRF_ATAN2:
	case __LIBM_KMATHERRL_ATAN2:
		/* atan2(+-0,+-0) */
		exc.arg1   = arg2;
		exc.arg2   = arg1;
		exc.type   = DOMAIN;
		exc.retval = HUGE;
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("atan2: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_HYPOT:
	case __LIBM_KMATHERRF_HYPOT:
	case __LIBM_KMATHERRL_HYPOT:
		/* hypot(finite,finite) overflow */
	case __LIBM_KMATHERR_COSH:
	case __LIBM_KMATHERRF_COSH:
	case __LIBM_KMATHERRL_COSH:
		/* cosh(finite) overflow */
	case __LIBM_KMATHERR_EXP_OVERFLOW:
	case __LIBM_KMATHERRF_EXP_OVERFLOW:
	case __LIBM_KMATHERRL_EXP_OVERFLOW:
		/* exp(finite) overflow */
		exc.type = OVERFLOW;
		if (version == _SVID_) {
			exc.retval = HUGE;
		} else {
			exc.retval = HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_EXP_UNDERFLOW:
	case __LIBM_KMATHERRF_EXP_UNDERFLOW:
	case __LIBM_KMATHERRL_EXP_UNDERFLOW:
		/* exp(finite) underflow */
		exc.type = UNDERFLOW;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_EXPM1_OVERFLOW:
	case __LIBM_KMATHERRF_EXPM1_OVERFLOW:
	case __LIBM_KMATHERRL_EXPM1_OVERFLOW:
		/* exp(finite) overflow */
		exc.type = OVERFLOW;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_EXPM1_UNDERFLOW:
	case __LIBM_KMATHERRF_EXPM1_UNDERFLOW:
	case __LIBM_KMATHERRL_EXPM1_UNDERFLOW:
		/* exp(finite) underflow */
		exc.type = UNDERFLOW;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_Y0_ZERO:
	case __LIBM_KMATHERRF_Y0_ZERO:
	case __LIBM_KMATHERRL_Y0_ZERO:
		/* y0(0) = -inf */
		/*exc.type = DOMAIN;*/ /* should be SING for IEEE */
	case __LIBM_KMATHERR_Y0_MINUS:
	case __LIBM_KMATHERRF_Y0_MINUS:
	case __LIBM_KMATHERRL_Y0_MINUS:
		/* y0(arg1<0) = NaN */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = -HUGE;
		} else {
			exc.retval = -HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("y0: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_Y1_ZERO:
	case __LIBM_KMATHERRF_Y1_ZERO:
	case __LIBM_KMATHERRL_Y1_ZERO:
		/* y1(0) = -inf */
		/*exc.type = DOMAIN;*/ /* should be SING for IEEE */
	case __LIBM_KMATHERR_Y1_MINUS:
	case __LIBM_KMATHERRF_Y1_MINUS:
	case __LIBM_KMATHERRL_Y1_MINUS:
		/* y1(arg1<0) = NaN */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = -HUGE;
		} else {
			exc.retval = -HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("y1: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_YN_ZERO:
	case __LIBM_KMATHERRF_YN_ZERO:
	case __LIBM_KMATHERRL_YN_ZERO:
		/* yn(n,0) = -inf */
		/*exc.type = DOMAIN;*/ /* should be SING for IEEE */
	case __LIBM_KMATHERR_YN_MINUS:
	case __LIBM_KMATHERRF_YN_MINUS:
	case __LIBM_KMATHERRL_YN_MINUS:
		/* yn(arg1<0) = NaN */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = -HUGE;
		} else {
			exc.retval = -HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("yn: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_LGAMMA_OVERFLOW:
	case __LIBM_KMATHERRF_LGAMMA_OVERFLOW:
	case __LIBM_KMATHERRL_LGAMMA_OVERFLOW:
		/* lgamma(finite) overflow */
		exc.type = OVERFLOW;
		if (version == _SVID_) {
			exc.retval = HUGE;
		} else {
			exc.retval = HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_LGAMMA_MINUS:
	case __LIBM_KMATHERRF_LGAMMA_MINUS:
	case __LIBM_KMATHERRL_LGAMMA_MINUS:
		/* lgamma(-integer) or lgamma(0) */
		exc.type = SING;
		if (version == _SVID_) {
			exc.retval = HUGE;
		} else {
			exc.retval = HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("lgamma: SING error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_LOG_ZERO:
	case __LIBM_KMATHERRF_LOG_ZERO:
	case __LIBM_KMATHERRL_LOG_ZERO:
		/* log(0) */
		exc.type = SING;
		if (version == _SVID_) {
			exc.retval = -HUGE;
		} else {
			exc.retval = -HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("log: SING error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_LOG_MINUS:
	case __LIBM_KMATHERRF_LOG_MINUS:
	case __LIBM_KMATHERRL_LOG_MINUS:
		/* log(arg1<0) */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = -HUGE;
		} else {
			exc.retval = nan("");
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("log: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_LOG10_ZERO:
	case __LIBM_KMATHERRF_LOG10_ZERO:
	case __LIBM_KMATHERRL_LOG10_ZERO:
		/* log10(0) */
		exc.type = SING;
		if (version == _SVID_) {
			exc.retval = -HUGE;
		} else {
			exc.retval = -HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("log10: SING error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_LOG10_MINUS:
	case __LIBM_KMATHERRF_LOG10_MINUS:
	case __LIBM_KMATHERRL_LOG10_MINUS:
		/* log10(arg1<0) */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = -HUGE;
		} else {
			exc.retval = nan("");
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("log10: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_POW_ZERO:
	case __LIBM_KMATHERRF_POW_ZERO:
	case __LIBM_KMATHERRL_POW_ZERO:
		/* pow(0.0,0.0) */
		/* error only if version == _SVID_ */
		exc.type   = DOMAIN;
		exc.retval = zero;
		if (version != _SVID_) {
			exc.retval = 1.0;
		} else if (matherr(&exc) == 0) {
			WRITE_ERROR("pow(0,0): DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_POW_OVERFLOW:
	case __LIBM_KMATHERRF_POW_OVERFLOW:
	case __LIBM_KMATHERRL_POW_OVERFLOW:
		/* pow(arg1,arg2) overflow */
		exc.type = OVERFLOW;
		if (version == _SVID_) {
			exc.retval = HUGE;
			arg2 *= 0.5;
			/* rint() doesn't call __kernel_standard(), so cannot recurse */
			if (arg1 < zero && rint(arg2) != arg2)
				exc.retval = -HUGE;
		} else {
			exc.retval = HUGE_VAL;
			arg2 *= 0.5;
			/* rint() doesn't call __kernel_standard(), so cannot recurse */
			if (arg1 < zero && rint(arg2) != arg2)
				exc.retval = -HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_POW_UNDERFLOW:
	case __LIBM_KMATHERRF_POW_UNDERFLOW:
	case __LIBM_KMATHERRL_POW_UNDERFLOW:
		/* pow(arg1,arg2) underflow */
		exc.type   = UNDERFLOW;
		exc.retval = zero;
		arg2 *= 0.5;
		/* rint() doesn't call __kernel_standard(), so cannot recurse */
		if (arg1 < zero && rint(arg2) != arg2)
			exc.retval = -zero;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_POW_MINUS:
	case __LIBM_KMATHERRF_POW_MINUS:
	case __LIBM_KMATHERRL_POW_MINUS:
		/* -0**neg */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = zero;
		} else {
			exc.retval = -HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("pow(0,neg): DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_POW_NONINT:
	case __LIBM_KMATHERRF_POW_NONINT:
	case __LIBM_KMATHERRL_POW_NONINT:
		/* neg**non-integral */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = zero;
		} else {
			exc.retval = zero / zero; /* X/Open allow NaN */
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("neg**non-integral: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_SINH:
	case __LIBM_KMATHERRF_SINH:
	case __LIBM_KMATHERRL_SINH:
		/* sinh(finite) overflow */
		exc.type = OVERFLOW;
		if (version == _SVID_) {
			exc.retval = ((arg1 > zero) ? HUGE : -HUGE);
		} else {
			exc.retval = ((arg1 > zero) ? HUGE_VAL : -HUGE_VAL);
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_SQRT:
	case __LIBM_KMATHERRF_SQRT:
	case __LIBM_KMATHERRL_SQRT:
		/* sqrt(arg1<0) */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = zero;
		} else {
			exc.retval = zero / zero;
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("sqrt: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_FMOD:
	case __LIBM_KMATHERRF_FMOD:
	case __LIBM_KMATHERRL_FMOD:
		/* fmod(arg1,0) */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = arg1;
		} else {
			exc.retval = zero / zero;
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("fmod:  DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_REMAINDER:
	case __LIBM_KMATHERRF_REMAINDER:
	case __LIBM_KMATHERRL_REMAINDER:
		/* remainder(arg1,0) */
		exc.type   = DOMAIN;
		exc.retval = zero / zero;
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("remainder: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_ACOSH:
	case __LIBM_KMATHERRF_ACOSH:
	case __LIBM_KMATHERRL_ACOSH:
		/* acosh(arg1<1) */
		exc.type   = DOMAIN;
		exc.retval = zero / zero;
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("acosh: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_ATANH_PLUSONE:
	case __LIBM_KMATHERRF_ATANH_PLUSONE:
	case __LIBM_KMATHERRL_ATANH_PLUSONE:
		/* atanh(|arg1|>1) */
		exc.type   = DOMAIN;
		exc.retval = zero / zero;
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("atanh: DOMAIN error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_ATANH_ONE:
	case __LIBM_KMATHERRF_ATANH_ONE:
	case __LIBM_KMATHERRL_ATANH_ONE:
		/* atanh(|arg1|=1) */
		exc.type   = SING;
		exc.retval = arg1 / zero; /* sign(arg1)*inf */
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("atanh: SING error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_SCALB_OVERFLOW:
	case __LIBM_KMATHERRF_SCALB_OVERFLOW:
	case __LIBM_KMATHERRL_SCALB_OVERFLOW:
		/* scalb overflow; SVID also returns +-HUGE_VAL */
		exc.type   = OVERFLOW;
		exc.retval = arg1 > zero ? HUGE_VAL : -HUGE_VAL;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_SCALB_UNDERFLOW:
	case __LIBM_KMATHERRF_SCALB_UNDERFLOW:
	case __LIBM_KMATHERRL_SCALB_UNDERFLOW:
		/* scalb underflow */
		exc.type   = UNDERFLOW;
		exc.retval = copysign(zero, arg1);
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_J0_TLOSS:
	case __LIBM_KMATHERRF_J0_TLOSS:
	case __LIBM_KMATHERRL_J0_TLOSS:
		/* j0(|arg1|>X_TLOSS) */
		exc.type   = TLOSS;
		exc.retval = zero;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("j0: TLOSS error\n");
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_Y0_TLOSS:
	case __LIBM_KMATHERRF_Y0_TLOSS:
	case __LIBM_KMATHERRL_Y0_TLOSS:
		/* y0(arg1>X_TLOSS) */
		exc.type   = TLOSS;
		exc.retval = zero;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("y0: TLOSS error\n");
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_J1_TLOSS:
	case __LIBM_KMATHERRF_J1_TLOSS:
	case __LIBM_KMATHERRL_J1_TLOSS:
		/* j1(|arg1|>X_TLOSS) */
		exc.type   = TLOSS;
		exc.retval = zero;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("j1: TLOSS error\n");
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_Y1_TLOSS:
	case __LIBM_KMATHERRF_Y1_TLOSS:
	case __LIBM_KMATHERRL_Y1_TLOSS:
		/* y1(arg1>X_TLOSS) */
		exc.type   = TLOSS;
		exc.retval = zero;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("y1: TLOSS error\n");
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_JN_TLOSS:
	case __LIBM_KMATHERRF_JN_TLOSS:
	case __LIBM_KMATHERRL_JN_TLOSS:
		/* jn(|arg1|>X_TLOSS) */
		exc.type   = TLOSS;
		exc.retval = zero;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("jn: TLOSS error\n");
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_YN_TLOSS:
	case __LIBM_KMATHERRF_YN_TLOSS:
	case __LIBM_KMATHERRL_YN_TLOSS:
		/* yn(arg1>X_TLOSS) */
		exc.type   = TLOSS;
		exc.retval = zero;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("yn: TLOSS error\n");
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_TGAMMA_OVERFLOW:
	case __LIBM_KMATHERRF_TGAMMA_OVERFLOW:
	case __LIBM_KMATHERRL_TGAMMA_OVERFLOW:
		/* tgamma(finite) overflow */
		exc.type   = OVERFLOW;
		exc.retval = copysign(HUGE_VAL, arg1);
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_TGAMMA_MINUS:
	case __LIBM_KMATHERRF_TGAMMA_MINUS:
	case __LIBM_KMATHERRL_TGAMMA_MINUS:
		/* tgamma(-integer) */
		exc.type = SING;
		if (version == _SVID_) {
			exc.retval = HUGE_VAL;
		} else {
			exc.retval = nan("");
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			if (version == _SVID_)
				WRITE_ERROR("gamma: SING error\n");
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_TGAMMA_UNDERFLOW:
	case __LIBM_KMATHERRF_TGAMMA_UNDERFLOW:
	case __LIBM_KMATHERRL_TGAMMA_UNDERFLOW:
		/* tgamma(finite) underflow */
		exc.type   = UNDERFLOW;
		exc.retval = 0;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_POW_NAN:
	case __LIBM_KMATHERRF_POW_NAN:
	case __LIBM_KMATHERRL_POW_NAN:
		/* pow(NaN,0.0) */
		/* error only if version == _SVID_ & _XOPEN_ */
		exc.type   = DOMAIN;
		exc.retval = arg1;
		if (version != _SVID_ && version != _XOPEN_) {
			exc.retval = 1.0;
		} else if (matherr(&exc) == 0) {
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_POW_ZEROMINUS:
	case __LIBM_KMATHERRF_POW_ZEROMINUS:
	case __LIBM_KMATHERRL_POW_ZEROMINUS:
		/* +0**neg */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = zero;
		} else {
			exc.retval = HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_EXP2_OVERFLOW:
	case __LIBM_KMATHERRF_EXP2_OVERFLOW:
	case __LIBM_KMATHERRL_EXP2_OVERFLOW:
		/* exp(finite) overflow */
		exc.type = OVERFLOW;
		if (version == _SVID_) {
			exc.retval = HUGE;
		} else {
			exc.retval = HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_EXP2_UNDERFLOW:
	case __LIBM_KMATHERRF_EXP2_UNDERFLOW:
	case __LIBM_KMATHERRL_EXP2_UNDERFLOW:
		/* exp(finite) underflow */
		exc.type   = UNDERFLOW;
		exc.retval = zero;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_EXP10_OVERFLOW:
	case __LIBM_KMATHERRF_EXP10_OVERFLOW:
	case __LIBM_KMATHERRL_EXP10_OVERFLOW:
		/* exp(finite) overflow */
		exc.type = OVERFLOW;
		if (version == _SVID_) {
			exc.retval = HUGE;
		} else {
			exc.retval = HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_EXP10_UNDERFLOW:
	case __LIBM_KMATHERRF_EXP10_UNDERFLOW:
	case __LIBM_KMATHERRL_EXP10_UNDERFLOW:
		/* exp(finite) underflow */
		exc.type   = UNDERFLOW;
		exc.retval = zero;
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = ERANGE;
		}
		break;

	case __LIBM_KMATHERR_LOG2_ZERO:
	case __LIBM_KMATHERRF_LOG2_ZERO:
	case __LIBM_KMATHERRL_LOG2_ZERO:
		/* log2(0) */
		exc.type = SING;
		if (version == _SVID_) {
			exc.retval = -HUGE;
		} else {
			exc.retval = -HUGE_VAL;
		}
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_LOG2_MINUS:
	case __LIBM_KMATHERRF_LOG2_MINUS:
	case __LIBM_KMATHERRL_LOG2_MINUS:
		/* log2(arg1<0) */
		exc.type = DOMAIN;
		if (version == _SVID_) {
			exc.retval = -HUGE;
		} else {
			exc.retval = nan("");
		}
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_TGAMMA_ZERO:
	case __LIBM_KMATHERRF_TGAMMA_ZERO:
	case __LIBM_KMATHERRL_TGAMMA_ZERO:
		/* tgamma(+-0) */
		exc.type   = SING;
		exc.retval = copysign(HUGE_VAL, arg1);
		if (version == _POSIX_) {
			exc.err = ERANGE;
		} else if (matherr(&exc) == 0) {
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_COS_INF:
	case __LIBM_KMATHERRF_COS_INF:
	case __LIBM_KMATHERRL_COS_INF:
		/* cos(inf) */
	case __LIBM_KMATHERR_SIN_INF:
	case __LIBM_KMATHERRF_SIN_INF:
	case __LIBM_KMATHERRL_SIN_INF:
		/* sin(inf) */
	case __LIBM_KMATHERR_TAN_INF:
	case __LIBM_KMATHERRF_TAN_INF:
	case __LIBM_KMATHERRL_TAN_INF:
		/* tan(inf) */
	case __LIBM_KMATHERR_SCALB_INVALID:
	case __LIBM_KMATHERRF_SCALB_INVALID:
	case __LIBM_KMATHERRL_SCALB_INVALID:
		/* scalb(arg1, non-integer) */
		exc.type   = DOMAIN;
		exc.retval = nan("");
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			exc.err = EDOM;
		}
		break;

	case __LIBM_KMATHERR_ILOGB:
	case __LIBM_KMATHERRF_ILOGB:
	case __LIBM_KMATHERRL_ILOGB:
		/* ilogb(0 or NaN) */
		exc.type   = DOMAIN;
		exc.retval = arg1 == 0 ? FP_ILOGB0 : FP_ILOGBNAN;
		feraiseexcept(FE_INVALID);
		if (version == _POSIX_) {
			exc.err = EDOM;
		} else if (matherr(&exc) == 0) {
			exc.err = EDOM;
		}
		break;

	default:
		break;
	}
	/* END: TAKEN FROM fdlibm (with various modifications) */

	if (exc.err != 0)
		libc_seterrno(exc.err);
	return exc.retval;
}




INTERN ATTR_SECTION(".text.crt.math.math") double LIBCCALL
libc___kernel_standard(double arg1, double arg2,
                       double retval, enum __libm_matherr type) {
	return libc_handle_matherr(__builtin_return_address(0),
	                           arg1, arg2, retval, type);
}

INTERN ATTR_SECTION(".text.crt.math.math") float LIBCCALL
libc___kernel_standard_f(float arg1, float arg2,
                         float retval, enum __libm_matherr type) {
	return (float)libc_handle_matherr(__builtin_return_address(0),
	                                  arg1, arg2, retval, type);
}

#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
DEFINE_INTERN_ALIAS(libc___kernel_standard_l, libc___kernel_standard);
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
PRIVATE ATTR_CONST ATTR_SECTION(".text.crt.math.math") double
NOTHROW(LIBCCALL safe_ldouble_to_double)(__LONGDOUBLE arg1) {
	double result;
	if (isfinite(arg1)) {
		__LONGDOUBLE ax = fabsl(arg1);
		if (ax > DBL_MAX) {
			result = (double)copysignl(DBL_MAX, arg1);
		} else if (ax > 0 && ax < DBL_MIN) {
			result = (double)copysignl(DBL_MIN, arg1);
		} else {
			result = (double)arg1;
		}
	} else {
		result = (double)arg1;
	}
	return result;
}

INTERN ATTR_SECTION(".text.crt.math.math") __LONGDOUBLE LIBCCALL
libc___kernel_standard_l(__LONGDOUBLE arg1, __LONGDOUBLE arg2,
                         __LONGDOUBLE retval, enum __libm_matherr type) {
	double dx, dy, dretval;
	void const *pc;
	pc      = __builtin_return_address(0);
	dx      = safe_ldouble_to_double(arg1);
	dy      = safe_ldouble_to_double(arg2);
	dretval = safe_ldouble_to_double(retval);

	/* BEGIN: TAKEN FROM fdlibm (with various modifications) */
	switch (type) {

	case __LIBM_KMATHERRL_POW_OVERFLOW:
		/* powl (arg1, arg2) overflow.  */
		if (_LIB_VERSION == _SVID_)
			dretval = signbit(retval) ? -HUGE : HUGE;
		if (_LIB_VERSION == _POSIX_) {
			libc_seterrno(ERANGE);
		} else {
			STRUCT_EXCEPTION exc;
			exc.arg1   = dx;
			exc.arg2   = dy;
			exc.type   = OVERFLOW;
			exc.name   = "powl"; /* libc_math_funcname_from_pc(pc) */
			exc.retval = dretval;
			exc.err    = 0;
			if (matherr(&exc) == 0)
				exc.err = ERANGE;
			if (exc.err != 0)
				libc_seterrno(exc.err);
			dretval = exc.retval;
		}
		return dretval;

	case __LIBM_KMATHERRL_POW_UNDERFLOW:
		/* powl (arg1, arg2) underflow.  */
		if (_LIB_VERSION == _POSIX_) {
			libc_seterrno(ERANGE);
		} else {
			STRUCT_EXCEPTION exc;
			exc.arg1   = dx;
			exc.arg2   = dy;
			exc.type   = UNDERFLOW;
			exc.name   = "powl"; /* libc_math_funcname_from_pc(pc) */
			exc.retval = dretval;
			exc.err    = 0;
			if (matherr(&exc) == 0)
				libc_seterrno(ERANGE);
			if (exc.err != 0)
				libc_seterrno(exc.err);
			dretval = exc.retval;
		}
		return dretval;

	default:
		break;
	}
	/* END: TAKEN FROM fdlibm (with various modifications) */

	return libc_handle_matherr(pc, dx, dy, dretval, type);
}
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

DECL_END
#endif /* !__NO_FPU */

#endif /* !GUARD_LIBC_LIBC_MATHERR_C */
