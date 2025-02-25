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
#ifndef _LIBM_MATHERR_H
#define _LIBM_MATHERR_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <asm/crt/math-libc_version.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

/* Taken from fdlimb (include/k_stand.h)
 * The header didn't contain a copyright notice, however the following notice
 * was taken from `k_standard.c': */
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


enum __libm_matherr {
	__LIBM_KMATHERR_ACOS = 1,         /* acos(|x|>1) */
	__LIBM_KMATHERR_ASIN,             /* asin(|x|>1) */
	__LIBM_KMATHERR_ATAN2,            /* atan2(+-0,+-0) */
	__LIBM_KMATHERR_HYPOT,            /* hypot overflow */
	__LIBM_KMATHERR_COSH,             /* cosh overflow */
	__LIBM_KMATHERR_EXP_OVERFLOW,     /* exp overflow */
	__LIBM_KMATHERR_EXP_UNDERFLOW,    /* exp underflow */
	__LIBM_KMATHERR_Y0_ZERO,          /* y0(0) */
	__LIBM_KMATHERR_Y0_MINUS,         /* y0(x<0) */
	__LIBM_KMATHERR_Y1_ZERO,          /* y1(0) */
	__LIBM_KMATHERR_Y1_MINUS,         /* y1(x<0) */
	__LIBM_KMATHERR_YN_ZERO,          /* yn(0) */
	__LIBM_KMATHERR_YN_MINUS,         /* yn(x<0) */
	__LIBM_KMATHERR_LGAMMA_OVERFLOW,  /* lgamma(finite) overflow */
	__LIBM_KMATHERR_LGAMMA_MINUS,     /* lgamma(-integer) */
	__LIBM_KMATHERR_LOG_ZERO,         /* log(0) */
	__LIBM_KMATHERR_LOG_MINUS,        /* log(x<0) */
	__LIBM_KMATHERR_LOG10_ZERO,       /* log10(0) */
	__LIBM_KMATHERR_LOG10_MINUS,      /* log10(x<0) */
	__LIBM_KMATHERR_POW_ZERO,         /* pow(0.0,0.0) */
	__LIBM_KMATHERR_POW_OVERFLOW,     /* pow(x,y) overflow */
	__LIBM_KMATHERR_POW_UNDERFLOW,    /* pow(x,y) underflow */
	__LIBM_KMATHERR_POW_MINUS,        /* pow(0,negative) */
	__LIBM_KMATHERR_POW_NONINT,       /* pow(neg,non-integral) */
	__LIBM_KMATHERR_SINH,             /* sinh(finite) overflow */
	__LIBM_KMATHERR_SQRT,             /* sqrt(negative) */
	__LIBM_KMATHERR_FMOD,             /* fmod(x,0) */
	__LIBM_KMATHERR_REMAINDER,        /* remainder(x,0) */
	__LIBM_KMATHERR_ACOSH,            /* acosh(x<1) */
	__LIBM_KMATHERR_ATANH_PLUSONE,    /* atanh(|x|>1) */
	__LIBM_KMATHERR_ATANH_ONE,        /* atanh(|x|=1) */
	__LIBM_KMATHERR_SCALB_OVERFLOW,   /* scalb overflow */
	__LIBM_KMATHERR_SCALB_UNDERFLOW,  /* scalb underflow */
	__LIBM_KMATHERR_J0_TLOSS,         /* j0(|x|>X_TLOSS) */
	__LIBM_KMATHERR_Y0_TLOSS,         /* y0(x>X_TLOSS) */
	__LIBM_KMATHERR_J1_TLOSS,         /* j1(|x|>X_TLOSS) */
	__LIBM_KMATHERR_Y1_TLOSS,         /* y1(x>X_TLOSS) */
	__LIBM_KMATHERR_JN_TLOSS,         /* jn(|x|>X_TLOSS) */
	__LIBM_KMATHERR_YN_TLOSS,         /* yn(x>X_TLOSS) */
	__LIBM_KMATHERR_TGAMMA_OVERFLOW,  /* tgamma(finite) overflow */
	__LIBM_KMATHERR_TGAMMA_MINUS,     /* tgamma(-integer) */
	__LIBM_KMATHERR_POW_NAN,          /* pow(NaN,0.0) */
	__LIBM_KMATHERR_POW_ZEROMINUS,    /* +0**neg */
	__LIBM_KMATHERR_EXP2_OVERFLOW,    /* exp2 overflow */
	__LIBM_KMATHERR_EXP2_UNDERFLOW,   /* exp2 underflow */
	__LIBM_KMATHERR_EXP10_OVERFLOW,   /* exp10 overflow */
	__LIBM_KMATHERR_EXP10_UNDERFLOW,  /* exp10 underflow */
	__LIBM_KMATHERR_LOG2_ZERO,        /* log2(0) */
	__LIBM_KMATHERR_LOG2_MINUS,       /* log2(x<0) */
	__LIBM_KMATHERR_TGAMMA_ZERO,      /* tgamma(+-0) */
	__LIBM_KMATHERR_COS_INF,          /* cos(inf) */
	__LIBM_KMATHERR_SIN_INF,          /* sin(inf) */
	__LIBM_KMATHERR_TAN_INF,          /* tan(inf) */
	__LIBM_KMATHERR_SCALB_INVALID,    /* scalb invalid */
	__LIBM_KMATHERR_TGAMMA_UNDERFLOW, /* tgamma(finite) underflow */
	__LIBM_KMATHERR_ILOGB,            /* ilogb(0 or NaN) */
	__LIBM_KMATHERR_EXPM1_OVERFLOW,   /* expm1 overflow */
	__LIBM_KMATHERR_EXPM1_UNDERFLOW,  /* expm1 underflow */

	__LIBM_KMATHERRF_FIRST            = 100,
	__LIBM_KMATHERRF_ACOS             = __LIBM_KMATHERR_ACOS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_ASIN             = __LIBM_KMATHERR_ASIN + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_ATAN2            = __LIBM_KMATHERR_ATAN2 + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_HYPOT            = __LIBM_KMATHERR_HYPOT + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_COSH             = __LIBM_KMATHERR_COSH + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_EXP_OVERFLOW     = __LIBM_KMATHERR_EXP_OVERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_EXP_UNDERFLOW    = __LIBM_KMATHERR_EXP_UNDERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_Y0_ZERO          = __LIBM_KMATHERR_Y0_ZERO + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_Y0_MINUS         = __LIBM_KMATHERR_Y0_MINUS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_Y1_ZERO          = __LIBM_KMATHERR_Y1_ZERO + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_Y1_MINUS         = __LIBM_KMATHERR_Y1_MINUS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_YN_ZERO          = __LIBM_KMATHERR_YN_ZERO + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_YN_MINUS         = __LIBM_KMATHERR_YN_MINUS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_LGAMMA_OVERFLOW  = __LIBM_KMATHERR_LGAMMA_OVERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_LGAMMA_MINUS     = __LIBM_KMATHERR_LGAMMA_MINUS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_LOG_ZERO         = __LIBM_KMATHERR_LOG_ZERO + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_LOG_MINUS        = __LIBM_KMATHERR_LOG_MINUS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_LOG10_ZERO       = __LIBM_KMATHERR_LOG10_ZERO + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_LOG10_MINUS      = __LIBM_KMATHERR_LOG10_MINUS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_POW_ZERO         = __LIBM_KMATHERR_POW_ZERO + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_POW_OVERFLOW     = __LIBM_KMATHERR_POW_OVERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_POW_UNDERFLOW    = __LIBM_KMATHERR_POW_UNDERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_POW_MINUS        = __LIBM_KMATHERR_POW_MINUS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_POW_NONINT       = __LIBM_KMATHERR_POW_NONINT + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_SINH             = __LIBM_KMATHERR_SINH + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_SQRT             = __LIBM_KMATHERR_SQRT + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_FMOD             = __LIBM_KMATHERR_FMOD + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_REMAINDER        = __LIBM_KMATHERR_REMAINDER + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_ACOSH            = __LIBM_KMATHERR_ACOSH + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_ATANH_PLUSONE    = __LIBM_KMATHERR_ATANH_PLUSONE + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_ATANH_ONE        = __LIBM_KMATHERR_ATANH_ONE + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_SCALB_OVERFLOW   = __LIBM_KMATHERR_SCALB_OVERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_SCALB_UNDERFLOW  = __LIBM_KMATHERR_SCALB_UNDERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_J0_TLOSS         = __LIBM_KMATHERR_J0_TLOSS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_Y0_TLOSS         = __LIBM_KMATHERR_Y0_TLOSS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_J1_TLOSS         = __LIBM_KMATHERR_J1_TLOSS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_Y1_TLOSS         = __LIBM_KMATHERR_Y1_TLOSS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_JN_TLOSS         = __LIBM_KMATHERR_JN_TLOSS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_YN_TLOSS         = __LIBM_KMATHERR_YN_TLOSS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_TGAMMA_OVERFLOW  = __LIBM_KMATHERR_TGAMMA_OVERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_TGAMMA_MINUS     = __LIBM_KMATHERR_TGAMMA_MINUS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_POW_NAN          = __LIBM_KMATHERR_POW_NAN + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_POW_ZEROMINUS    = __LIBM_KMATHERR_POW_ZEROMINUS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_EXP2_OVERFLOW    = __LIBM_KMATHERR_EXP2_OVERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_EXP2_UNDERFLOW   = __LIBM_KMATHERR_EXP2_UNDERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_EXP10_OVERFLOW   = __LIBM_KMATHERR_EXP10_OVERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_EXP10_UNDERFLOW  = __LIBM_KMATHERR_EXP10_UNDERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_LOG2_ZERO        = __LIBM_KMATHERR_LOG2_ZERO + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_LOG2_MINUS       = __LIBM_KMATHERR_LOG2_MINUS + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_TGAMMA_ZERO      = __LIBM_KMATHERR_TGAMMA_ZERO + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_COS_INF          = __LIBM_KMATHERR_COS_INF + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_SIN_INF          = __LIBM_KMATHERR_SIN_INF + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_TAN_INF          = __LIBM_KMATHERR_TAN_INF + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_SCALB_INVALID    = __LIBM_KMATHERR_SCALB_INVALID + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_TGAMMA_UNDERFLOW = __LIBM_KMATHERR_TGAMMA_UNDERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_ILOGB            = __LIBM_KMATHERR_ILOGB + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_EXPM1_OVERFLOW   = __LIBM_KMATHERR_EXPM1_OVERFLOW + __LIBM_KMATHERRF_FIRST,
	__LIBM_KMATHERRF_EXPM1_UNDERFLOW  = __LIBM_KMATHERR_EXPM1_UNDERFLOW + __LIBM_KMATHERRF_FIRST,

	__LIBM_KMATHERRL_FIRST            = 200,
	__LIBM_KMATHERRL_ACOS             = __LIBM_KMATHERR_ACOS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_ASIN             = __LIBM_KMATHERR_ASIN + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_ATAN2            = __LIBM_KMATHERR_ATAN2 + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_HYPOT            = __LIBM_KMATHERR_HYPOT + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_COSH             = __LIBM_KMATHERR_COSH + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_EXP_OVERFLOW     = __LIBM_KMATHERR_EXP_OVERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_EXP_UNDERFLOW    = __LIBM_KMATHERR_EXP_UNDERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_Y0_ZERO          = __LIBM_KMATHERR_Y0_ZERO + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_Y0_MINUS         = __LIBM_KMATHERR_Y0_MINUS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_Y1_ZERO          = __LIBM_KMATHERR_Y1_ZERO + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_Y1_MINUS         = __LIBM_KMATHERR_Y1_MINUS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_YN_ZERO          = __LIBM_KMATHERR_YN_ZERO + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_YN_MINUS         = __LIBM_KMATHERR_YN_MINUS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_LGAMMA_OVERFLOW  = __LIBM_KMATHERR_LGAMMA_OVERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_LGAMMA_MINUS     = __LIBM_KMATHERR_LGAMMA_MINUS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_LOG_ZERO         = __LIBM_KMATHERR_LOG_ZERO + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_LOG_MINUS        = __LIBM_KMATHERR_LOG_MINUS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_LOG10_ZERO       = __LIBM_KMATHERR_LOG10_ZERO + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_LOG10_MINUS      = __LIBM_KMATHERR_LOG10_MINUS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_POW_ZERO         = __LIBM_KMATHERR_POW_ZERO + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_POW_OVERFLOW     = __LIBM_KMATHERR_POW_OVERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_POW_UNDERFLOW    = __LIBM_KMATHERR_POW_UNDERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_POW_MINUS        = __LIBM_KMATHERR_POW_MINUS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_POW_NONINT       = __LIBM_KMATHERR_POW_NONINT + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_SINH             = __LIBM_KMATHERR_SINH + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_SQRT             = __LIBM_KMATHERR_SQRT + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_FMOD             = __LIBM_KMATHERR_FMOD + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_REMAINDER        = __LIBM_KMATHERR_REMAINDER + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_ACOSH            = __LIBM_KMATHERR_ACOSH + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_ATANH_PLUSONE    = __LIBM_KMATHERR_ATANH_PLUSONE + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_ATANH_ONE        = __LIBM_KMATHERR_ATANH_ONE + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_SCALB_OVERFLOW   = __LIBM_KMATHERR_SCALB_OVERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_SCALB_UNDERFLOW  = __LIBM_KMATHERR_SCALB_UNDERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_J0_TLOSS         = __LIBM_KMATHERR_J0_TLOSS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_Y0_TLOSS         = __LIBM_KMATHERR_Y0_TLOSS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_J1_TLOSS         = __LIBM_KMATHERR_J1_TLOSS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_Y1_TLOSS         = __LIBM_KMATHERR_Y1_TLOSS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_JN_TLOSS         = __LIBM_KMATHERR_JN_TLOSS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_YN_TLOSS         = __LIBM_KMATHERR_YN_TLOSS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_TGAMMA_OVERFLOW  = __LIBM_KMATHERR_TGAMMA_OVERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_TGAMMA_MINUS     = __LIBM_KMATHERR_TGAMMA_MINUS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_POW_NAN          = __LIBM_KMATHERR_POW_NAN + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_POW_ZEROMINUS    = __LIBM_KMATHERR_POW_ZEROMINUS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_EXP2_OVERFLOW    = __LIBM_KMATHERR_EXP2_OVERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_EXP2_UNDERFLOW   = __LIBM_KMATHERR_EXP2_UNDERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_EXP10_OVERFLOW   = __LIBM_KMATHERR_EXP10_OVERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_EXP10_UNDERFLOW  = __LIBM_KMATHERR_EXP10_UNDERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_LOG2_ZERO        = __LIBM_KMATHERR_LOG2_ZERO + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_LOG2_MINUS       = __LIBM_KMATHERR_LOG2_MINUS + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_TGAMMA_ZERO      = __LIBM_KMATHERR_TGAMMA_ZERO + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_COS_INF          = __LIBM_KMATHERR_COS_INF + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_SIN_INF          = __LIBM_KMATHERR_SIN_INF + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_TAN_INF          = __LIBM_KMATHERR_TAN_INF + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_SCALB_INVALID    = __LIBM_KMATHERR_SCALB_INVALID + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_TGAMMA_UNDERFLOW = __LIBM_KMATHERR_TGAMMA_UNDERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_ILOGB            = __LIBM_KMATHERR_ILOGB + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_EXPM1_OVERFLOW   = __LIBM_KMATHERR_EXPM1_OVERFLOW + __LIBM_KMATHERRL_FIRST,
	__LIBM_KMATHERRL_EXPM1_UNDERFLOW  = __LIBM_KMATHERR_EXPM1_UNDERFLOW + __LIBM_KMATHERRL_FIRST
};

#ifndef ___IEEE_
#define ___IEEE_  (-1) /* According to IEEE 754/IEEE 854. */
#define ___SVID_  0    /* According to System V, release 4. */
#define ___XOPEN_ 1    /* Nowadays also Unix98. */
#define ___POSIX_ 2    /* ... */
#define ___ISOC_  3    /* Actually this is ISO C99. */
#endif /* !___IEEE_ */
typedef enum {
	__LIBM_IEEE  = ___IEEE_,  /* According to IEEE 754/IEEE 854. */
	__LIBM_SVID  = ___SVID_,  /* According to System V, release 4. */
	__LIBM_XOPEN = ___XOPEN_, /* Nowadays also Unix98. */
	__LIBM_POSIX = ___POSIX_,
	__LIBM_ISOC  = ___ISOC_, /* Actually this is ISO C99. */
} __LIBM_LIB_VERSION_TYPE;



#if defined(__CRT_KOS) && defined(__BUILDING_LIBC)
#define __kernel_standard   libc___kernel_standard
#define __kernel_standard_f libc___kernel_standard_f
__INTDEF double __LIBCCALL libc___kernel_standard(double __arg1, double __arg2, double __retval, enum __libm_matherr __type);
__INTDEF float __LIBCCALL libc___kernel_standard_f(float __arg1, float __arg2, float __retval, enum __libm_matherr __type);
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __kernel_standard_l libc___kernel_standard_l
__INTDEF __LONGDOUBLE __LIBCCALL libc___kernel_standard_l(__LONGDOUBLE __arg1, __LONGDOUBLE __arg2, __LONGDOUBLE __retval, enum __libm_matherr __type);
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#define __LIBM_LIB_VERSION libc___LIBM_GET_LIB_VERSION()
__INTDEF __ATTR_CONST __ATTR_WUNUSED __LIBM_LIB_VERSION_TYPE
__NOTHROW(__LIBCCALL libc___LIBM_GET_LIB_VERSION)(void);
#else /* __CRT_KOS && __BUILDING_LIBC */
__LIBM_LOCAL_FUNC(kernel_standard) double
(__LIBCCALL __kernel_standard)(double __arg1, double __arg2,
                               double __retval, enum __libm_matherr __type) {
	__COMPILER_IMPURE();
	/* Sorry, but the `matherr(3)' handling implementation only exists in libc. */
	(void)__arg1;
	(void)__arg2;
	(void)__retval;
	(void)__type;
	return __retval;
}

__LIBM_LOCAL_FUNC(kernel_standard_f) float
(__LIBCCALL __kernel_standard_f)(float __arg1, float __arg2,
                                 float __retval, enum __libm_matherr __type) {
	__COMPILER_IMPURE();
	/* Sorry, but the `matherr(3)' handling implementation only exists in libc. */
	(void)__arg1;
	(void)__arg2;
	(void)__retval;
	(void)__type;
	return __retval;
}

#ifdef __COMPILER_HAVE_LONGDOUBLE
__LIBM_LOCAL_FUNC(kernel_standard_l) __LONGDOUBLE
(__LIBCCALL __kernel_standard_l)(__LONGDOUBLE __arg1, __LONGDOUBLE __arg2,
                                 __LONGDOUBLE __retval, enum __libm_matherr __type) {
	__COMPILER_IMPURE();
	/* Sorry, but the `matherr(3)' handling implementation only exists in libc. */
	(void)__arg1;
	(void)__arg2;
	(void)__retval;
	(void)__type;
	return __retval;
}
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#ifdef _LIB_VERSION
/* User-provided override */
#define __LIBM_LIB_VERSION _LIB_VERSION
#elif defined(__CRT_HAVE__LIB_VERSION)
/* Use libc configuration */
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,__LIBM_LIB_VERSION_TYPE,_LIB_VERSION)
#define _LIB_VERSION       _LIB_VERSION
#define __LIBM_LIB_VERSION _LIB_VERSION
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,__LIBM_LIB_VERSION_TYPE,__LIBM_LIB_VERSION,_LIB_VERSION)
#define __LIBM_LIB_VERSION __LIBM_LIB_VERSION
#endif /* !__NO_COMPILER_SREDIRECT */
#else /* __CRT_HAVE__LIB_VERSION */
/* Fallback: select most appropriate for caller's system. */
#if defined(__unix__)
#define __LIBM_LIB_VERSION __LIBM_POSIX
#else /* ... */
#define __LIBM_LIB_VERSION __LIBM_ISOC
#endif /* !... */
#endif /* __CRT_HAVE__LIB_VERSION */

#endif /* !__CRT_KOS || !__BUILDING_LIBC */


__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_MATHERR_H */
