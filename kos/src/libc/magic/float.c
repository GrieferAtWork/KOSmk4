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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: DJGPP         (/include/float.h) */
/* (#) Portability: DragonFly BSD (/include/float.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/float.h) */
/* (#) Portability: FreeBSD       (/sys/[...]/include/float.h) */
/* (#) Portability: GNU C Library (/include/float.h) */
/* (#) Portability: MSVC          (/include/float.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/float.h) */
/* (#) Portability: NetBSD        (/sys/arch/[...]/include/float.h) */
/* (#) Portability: OpenBSD       (/include/float.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/float.h) */
/* (#) Portability: PDCLib        (/include/float.h) */
/* (#) Portability: Windows Kits  (/ucrt/float.h) */
/* (#) Portability: diet libc     (/include/float.h) */
/* (#) Portability: musl libc     (/include/float.h) */
}

%[define_ccompat_header("cfloat")]
%[define_replacement(errno_t = __errno_t)]
%[default:section(".text.crt{|.dos}.math.float")]

%(c, ccompat)#ifndef __NO_FPU
%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/floatcore.h>
)]%[insert:prefix(
#include <hybrid/host.h> /* TODO: Get rid of this #include! */
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#ifdef __USE_DOS
#include <asm/crt/float.h>
#include <bits/types.h>
#endif /* __USE_DOS */

__SYSDECL_BEGIN

#ifdef __FLT_RADIX__
#define FLT_RADIX        __FLT_RADIX__
#endif /* __FLT_RADIX__ */
#ifdef __FLT_MANT_DIG__
#define FLT_MANT_DIG     __FLT_MANT_DIG__
#endif /* __FLT_MANT_DIG__ */
#ifdef __DBL_MANT_DIG__
#define DBL_MANT_DIG     __DBL_MANT_DIG__
#endif /* __DBL_MANT_DIG__ */
#ifdef __LDBL_MANT_DIG__
#define LDBL_MANT_DIG    __LDBL_MANT_DIG__
#endif /* __LDBL_MANT_DIG__ */
#ifdef __FLT_DIG__
#define FLT_DIG          __FLT_DIG__
#endif /* __FLT_DIG__ */
#ifdef __DBL_DIG__
#define DBL_DIG          __DBL_DIG__
#endif /* __DBL_DIG__ */
#ifdef __LDBL_DIG__
#define LDBL_DIG         __LDBL_DIG__
#endif /* __LDBL_DIG__ */
#ifdef __FLT_MIN_EXP__
#define FLT_MIN_EXP      __FLT_MIN_EXP__
#endif /* __FLT_MIN_EXP__ */
#ifdef __DBL_MIN_EXP__
#define DBL_MIN_EXP      __DBL_MIN_EXP__
#endif /* __DBL_MIN_EXP__ */
#ifdef __LDBL_MIN_EXP__
#define LDBL_MIN_EXP     __LDBL_MIN_EXP__
#endif /* __LDBL_MIN_EXP__ */
#ifdef __FLT_MIN_10_EXP__
#define FLT_MIN_10_EXP   __FLT_MIN_10_EXP__
#endif /* __FLT_MIN_10_EXP__ */
#ifdef __DBL_MIN_10_EXP__
#define DBL_MIN_10_EXP   __DBL_MIN_10_EXP__
#endif /* __DBL_MIN_10_EXP__ */
#ifdef __LDBL_MIN_10_EXP__
#define LDBL_MIN_10_EXP  __LDBL_MIN_10_EXP__
#endif /* __LDBL_MIN_10_EXP__ */
#ifdef __FLT_MAX_EXP__
#define FLT_MAX_EXP      __FLT_MAX_EXP__
#endif /* __FLT_MAX_EXP__ */
#ifdef __DBL_MAX_EXP__
#define DBL_MAX_EXP      __DBL_MAX_EXP__
#endif /* __DBL_MAX_EXP__ */
#ifdef __LDBL_MAX_EXP__
#define LDBL_MAX_EXP     __LDBL_MAX_EXP__
#endif /* __LDBL_MAX_EXP__ */
#ifdef __FLT_MAX_10_EXP__
#define FLT_MAX_10_EXP   __FLT_MAX_10_EXP__
#endif /* __FLT_MAX_10_EXP__ */
#ifdef __DBL_MAX_10_EXP__
#define DBL_MAX_10_EXP   __DBL_MAX_10_EXP__
#endif /* __DBL_MAX_10_EXP__ */
#ifdef __LDBL_MAX_10_EXP__
#define LDBL_MAX_10_EXP  __LDBL_MAX_10_EXP__
#endif /* __LDBL_MAX_10_EXP__ */
#ifdef __FLT_MAX__
#define FLT_MAX          __FLT_MAX__
#endif /* __FLT_MAX__ */
#ifdef __DBL_MAX__
#define DBL_MAX          __DBL_MAX__
#endif /* __DBL_MAX__ */
#ifdef __LDBL_MAX__
#define LDBL_MAX         __LDBL_MAX__
#endif /* __LDBL_MAX__ */
#ifdef __FLT_EPSILON__
#define FLT_EPSILON      __FLT_EPSILON__
#endif /* __FLT_EPSILON__ */
#ifdef __DBL_EPSILON__
#define DBL_EPSILON      __DBL_EPSILON__
#endif /* __DBL_EPSILON__ */
#ifdef __LDBL_EPSILON__
#define LDBL_EPSILON     __LDBL_EPSILON__
#endif /* __LDBL_EPSILON__ */
#ifdef __FLT_MIN__
#define FLT_MIN          __FLT_MIN__
#endif /* __FLT_MIN__ */
#ifdef __DBL_MIN__
#define DBL_MIN          __DBL_MIN__
#endif /* __DBL_MIN__ */
#ifdef __LDBL_MIN__
#define LDBL_MIN         __LDBL_MIN__
#endif /* __LDBL_MIN__ */

#ifndef FLT_ROUNDS
}
%[insert:pp_if($crt_has_function(__fpe_flt_rounds))]
%#define FLT_ROUNDS __fpe_flt_rounds()
%#ifdef __CC__
[[const, wunused, nothrow, inline, no_extern_inline]]
int __fpe_flt_rounds(void) {
	return 1;
}
%#endif /* !__CC__ */
%[insert:pp_else]
%#define FLT_ROUNDS 1
%[insert:pp_endif]
%{
#endif /* !FLT_ROUNDS */

#if defined(__USE_ISOC99) || defined(__USE_ISOCXX11)
#ifdef __FLT_EVAL_METHOD__
#define FLT_EVAL_METHOD  __FLT_EVAL_METHOD__
#endif /* __FLT_EVAL_METHOD__ */
#ifdef __DECIMAL_DIG__
#define DECIMAL_DIG      __DECIMAL_DIG__
#endif /* __DECIMAL_DIG__ */
#endif /* __USE_ISOC99 || __USE_ISOCXX11 */

#ifdef __USE_ISOC11
#ifdef __FLT_DECIMAL_DIG__
#define FLT_DECIMAL_DIG  __FLT_DECIMAL_DIG__
#endif /* __FLT_DECIMAL_DIG__ */
#ifdef __DBL_DECIMAL_DIG__
#define DBL_DECIMAL_DIG  __DBL_DECIMAL_DIG__
#endif /* __DBL_DECIMAL_DIG__ */
#ifdef __DECIMAL_DIG__
#define LDBL_DECIMAL_DIG __DECIMAL_DIG__
#endif /* __DECIMAL_DIG__ */
#ifdef __FLT_HAS_DENORM__
#define FLT_HAS_SUBNORM  __FLT_HAS_DENORM__
#endif /* __FLT_HAS_DENORM__ */
#ifdef __DBL_HAS_DENORM__
#define DBL_HAS_SUBNORM  __DBL_HAS_DENORM__
#endif /* __DBL_HAS_DENORM__ */
#ifdef __LDBL_HAS_DENORM__
#define LDBL_HAS_SUBNORM __LDBL_HAS_DENORM__
#endif /* __LDBL_HAS_DENORM__ */
#ifdef __FLT_DENORM_MIN__
#define FLT_TRUE_MIN     __FLT_DENORM_MIN__
#endif /* __FLT_DENORM_MIN__ */
#ifdef __DBL_DENORM_MIN__
#define DBL_TRUE_MIN     __DBL_DENORM_MIN__
#endif /* __DBL_DENORM_MIN__ */
#ifdef __LDBL_DENORM_MIN__
#define LDBL_TRUE_MIN    __LDBL_DENORM_MIN__
#endif /* __LDBL_DENORM_MIN__ */
#endif /* __USE_ISOC11 */

#ifdef __STDC_WANT_DEC_FP__
#ifdef __DEC32_EPSILON__
#define DEC32_EPSILON        __DEC32_EPSILON__
#endif /* __DEC32_EPSILON__ */
#ifdef __DEC32_MANT_DIG__
#define DEC32_MANT_DIG       __DEC32_MANT_DIG__
#endif /* __DEC32_MANT_DIG__ */
#ifdef __DEC32_MAX__
#define DEC32_MAX            __DEC32_MAX__
#endif /* __DEC32_MAX__ */
#ifdef __DEC32_MAX_EXP__
#define DEC32_MAX_EXP        __DEC32_MAX_EXP__
#endif /* __DEC32_MAX_EXP__ */
#ifdef __DEC32_MIN__
#define DEC32_MIN            __DEC32_MIN__
#endif /* __DEC32_MIN__ */
#ifdef __DEC32_MIN_EXP__
#define DEC32_MIN_EXP        __DEC32_MIN_EXP__
#endif /* __DEC32_MIN_EXP__ */
#ifdef __DEC32_SUBNORMAL_MIN__
#define DEC32_SUBNORMAL_MIN  __DEC32_SUBNORMAL_MIN__
#endif /* __DEC32_SUBNORMAL_MIN__ */
#ifdef __DEC64_EPSILON__
#define DEC64_EPSILON        __DEC64_EPSILON__
#endif /* __DEC64_EPSILON__ */
#ifdef __DEC64_MANT_DIG__
#define DEC64_MANT_DIG       __DEC64_MANT_DIG__
#endif /* __DEC64_MANT_DIG__ */
#ifdef __DEC64_MAX__
#define DEC64_MAX            __DEC64_MAX__
#endif /* __DEC64_MAX__ */
#ifdef __DEC64_MAX_EXP__
#define DEC64_MAX_EXP        __DEC64_MAX_EXP__
#endif /* __DEC64_MAX_EXP__ */
#ifdef __DEC64_MIN__
#define DEC64_MIN            __DEC64_MIN__
#endif /* __DEC64_MIN__ */
#ifdef __DEC64_MIN_EXP__
#define DEC64_MIN_EXP        __DEC64_MIN_EXP__
#endif /* __DEC64_MIN_EXP__ */
#ifdef __DEC64_SUBNORMAL_MIN__
#define DEC64_SUBNORMAL_MIN  __DEC64_SUBNORMAL_MIN__
#endif /* __DEC64_SUBNORMAL_MIN__ */
#ifdef __DEC128_EPSILON__
#define DEC128_EPSILON       __DEC128_EPSILON__
#endif /* __DEC128_EPSILON__ */
#ifdef __DEC128_MANT_DIG__
#define DEC128_MANT_DIG      __DEC128_MANT_DIG__
#endif /* __DEC128_MANT_DIG__ */
#ifdef __DEC128_MAX__
#define DEC128_MAX           __DEC128_MAX__
#endif /* __DEC128_MAX__ */
#ifdef __DEC128_MAX_EXP__
#define DEC128_MAX_EXP       __DEC128_MAX_EXP__
#endif /* __DEC128_MAX_EXP__ */
#ifdef __DEC128_MIN__
#define DEC128_MIN           __DEC128_MIN__
#endif /* __DEC128_MIN__ */
#ifdef __DEC128_MIN_EXP__
#define DEC128_MIN_EXP       __DEC128_MIN_EXP__
#endif /* __DEC128_MIN_EXP__ */
#ifdef __DEC128_SUBNORMAL_MIN__
#define DEC128_SUBNORMAL_MIN __DEC128_SUBNORMAL_MIN__
#endif /* __DEC128_SUBNORMAL_MIN__ */
#ifdef __DEC_EVAL_METHOD__
#define DEC_EVAL_METHOD      __DEC_EVAL_METHOD__
#endif /* __DEC_EVAL_METHOD__ */
#endif /* __STDC_WANT_DEC_FP__ */


}

%#ifdef __USE_DOS
%#ifdef __CC__

[[decl_include("<hybrid/typecore.h>")]]
$uint32_t _clearfp();

[[decl_include("<hybrid/typecore.h>")]]
[[requires_include("<fpu_control.h>")]]
[[requires(defined(_FPU_GETCW) && defined(_FPU_SETCW))]]
[[impl_include("<fpu_control.h>")]]
$uint32_t _controlfp($uint32_t newval, $uint32_t mask) {
	@fpu_control_t@ result;
	@_FPU_GETCW@(result);
@@pp_if defined(_FPU_RESERVED) && _FPU_RESERVED != 0@@
	mask &= ~_FPU_RESERVED; /* Don't allow modification of reserved words. */
@@pp_endif@@
	if (mask) {
		@fpu_control_t@ newword;
		newword = result;
		newword &= ~mask;
		newword = newval & mask;
		_FPU_SETCW(newword);
	}
	return result;
}

[[decl_include("<hybrid/typecore.h>"), requires_function(_controlfp)]]
void _set_controlfp($uint32_t newval, $uint32_t mask) {
	_controlfp(newval, mask);
}

[[decl_include("<bits/types.h>"), requires_function(_controlfp)]]
$errno_t _controlfp_s($uint32_t *pcurrent, $uint32_t newval, $uint32_t mask) {
	uint32_t st = _controlfp(newval, mask);
	if (pcurrent)
		*pcurrent = st;
	return 0;
}

[[decl_include("<hybrid/typecore.h>")]]
$uint32_t _statusfp();

%[insert:function(_fpreset = fpreset)]

[[decl_include("<hybrid/typecore.h>")]]
void _statusfp2($uint32_t *x86_stat, $uint32_t *sse2_stat);

%#endif /* __CC__ */
%{

/* TODO: This stuff is most definitely x86-specific! */
#define _SW_INEXACT     0x00000001 /* Inexact precision. */
#define _SW_UNDERFLOW   0x00000002 /* Underflow. */
#define _SW_OVERFLOW    0x00000004 /* Overflow. */
#define _SW_ZERODIVIDE  0x00000008 /* Zero divide. */
#define _SW_INVALID     0x00000010 /* Invalid. */
#define _SW_DENORMAL    0x00080000 /* Denormal bit. */
#define _EM_AMBIGUIOUS  0x80000000
#define _EM_AMBIGUOUS   0x80000000

/* TODO: This stuff is most definitely x86-specific! */
#define _MCW_EM         0x0008001f     /* Interrupt exception masks. */
#define _EM_INEXACT     _SW_INEXACT    /* Inexact precision. */
#define _EM_UNDERFLOW   _SW_UNDERFLOW  /* Underflow. */
#define _EM_OVERFLOW    _SW_OVERFLOW   /* Overflow. */
#define _EM_ZERODIVIDE  _SW_ZERODIVIDE /* Zero division. */
#define _EM_INVALID     _SW_INVALID    /* Invalid. */
#define _EM_DENORMAL    _SW_DENORMAL   /* Denormal exception bit.) */

/* TODO: This stuff is most definitely x86-specific! */
#define _MCW_RC         0x00000300 /* Rounding mode mask. */
#define _RC_NEAR        0x00000000 /* Round to nearest. */
#define _RC_DOWN        0x00000100 /* Round down. */
#define _RC_UP          0x00000200 /* Round up. */
#define _RC_CHOP        0x00000300 /* Truncate result. */

/* TODO: This stuff is most definitely x86-specific! */
#define _MCW_PC         0x00030000 /* Precision width mask. */
#define _PC_64          0x00000000 /* 64-bit precision. */
#define _PC_53          0x00010000 /* 53-bit precision. */
#define _PC_24          0x00020000 /* 24-bit precision. */

/* TODO: This stuff is most definitely x86-specific! */
#define _MCW_IC         0x00040000 /* Infinity mode mask. */
#define _IC_AFFINE      0x00040000 /* Affine mode. */
#define _IC_PROJECTIVE  0x00000000 /* Projective mode. */

/* TODO: This stuff is most definitely x86-specific! */
#define _MCW_DN         0x03000000 /* Denormal control mask. */
#define _DN_SAVE        0x00000000 /* Save. */
#define _DN_FLUSH       0x01000000 /* Flush to zero. */
#define _DN_FLUSH_OPERANDS_SAVE_RESULTS 0x02000000  /* Flush operands to + save result. */
#define _DN_SAVE_OPERANDS_FLUSH_RESULTS 0x03000000  /* Save + flush results to zero. */

#if defined(__x86_64__) || defined(__i386__)
#define _CW_DEFAULT (_RC_NEAR | _PC_53 | _EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW | _EM_UNDERFLOW | _EM_INEXACT | _EM_DENORMAL)
#else
#define _CW_DEFAULT (_RC_NEAR | _EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW | _EM_UNDERFLOW | _EM_INEXACT | _EM_DENORMAL)
#endif


/* TODO: This stuff is most definitely x86-specific! */
#define _SW_UNEMULATED          0x0040
#define _SW_SQRTNEG             0x0080
#define _SW_STACKOVERFLOW       0x0200
#define _SW_STACKUNDERFLOW      0x0400
#define _FPE_INVALID            0x81
#define _FPE_DENORMAL           0x82
#define _FPE_ZERODIVIDE         0x83
#define _FPE_OVERFLOW           0x84
#define _FPE_UNDERFLOW          0x85
#define _FPE_INEXACT            0x86
#define _FPE_UNEMULATED         0x87
#define _FPE_SQRTNEG            0x88
#define _FPE_STACKOVERFLOW      0x8a
#define _FPE_STACKUNDERFLOW     0x8b
#define _FPE_EXPLICITGEN        0x8c
#define _FPE_MULTIPLE_TRAPS     0x8d
#define _FPE_MULTIPLE_FAULTS    0x8e

#define DBL_RADIX          FLT_RADIX
#define DBL_ROUNDS         FLT_ROUNDS
#define LDBL_RADIX         FLT_RADIX
#define LDBL_ROUNDS        FLT_ROUNDS
#define EM_AMBIGUIOUS      _EM_AMBIGUOUS
#define EM_AMBIGUOUS       _EM_AMBIGUOUS
#define MCW_EM             _MCW_EM
#define EM_INVALID         _EM_INVALID
#define EM_DENORMAL        _EM_DENORMAL
#define EM_ZERODIVIDE      _EM_ZERODIVIDE
#define EM_OVERFLOW        _EM_OVERFLOW
#define EM_UNDERFLOW       _EM_UNDERFLOW
#define EM_INEXACT         _EM_INEXACT
#define MCW_IC             _MCW_IC
#define IC_AFFINE          _IC_AFFINE
#define IC_PROJECTIVE      _IC_PROJECTIVE
#define MCW_RC             _MCW_RC
#define RC_CHOP            _RC_CHOP
#define RC_UP              _RC_UP
#define RC_DOWN            _RC_DOWN
#define RC_NEAR            _RC_NEAR
#define MCW_PC             _MCW_PC
#define PC_24              _PC_24
#define PC_53              _PC_53
#define PC_64              _PC_64
#define CW_DEFAULT         _CW_DEFAULT
#define SW_INVALID         _SW_INVALID
#define SW_DENORMAL        _SW_DENORMAL
#define SW_ZERODIVIDE      _SW_ZERODIVIDE
#define SW_OVERFLOW        _SW_OVERFLOW
#define SW_UNDERFLOW       _SW_UNDERFLOW
#define SW_INEXACT         _SW_INEXACT
#define SW_UNEMULATED      _SW_UNEMULATED
#define SW_SQRTNEG         _SW_SQRTNEG
#define SW_STACKOVERFLOW   _SW_STACKOVERFLOW
#define SW_STACKUNDERFLOW  _SW_STACKUNDERFLOW
#define FPE_INVALID        _FPE_INVALID
#define FPE_DENORMAL       _FPE_DENORMAL
#define FPE_ZERODIVIDE     _FPE_ZERODIVIDE
#define FPE_OVERFLOW       _FPE_OVERFLOW
#define FPE_UNDERFLOW      _FPE_UNDERFLOW
#define FPE_INEXACT        _FPE_INEXACT
#define FPE_UNEMULATED     _FPE_UNEMULATED
#define FPE_SQRTNEG        _FPE_SQRTNEG
#define FPE_STACKOVERFLOW  _FPE_STACKOVERFLOW
#define FPE_STACKUNDERFLOW _FPE_STACKUNDERFLOW
#define FPE_EXPLICITGEN    _FPE_EXPLICITGEN

/* Bits for return value of `_fpclass(3)' */
#if !defined(_FPCLASS_SNAN) && defined(__FPCLASS_SNAN)
#define _FPCLASS_SNAN __FPCLASS_SNAN /* signaling NaN. */
#endif /* !_FPCLASS_SNAN && __FPCLASS_SNAN */
#if !defined(_FPCLASS_QNAN) && defined(__FPCLASS_QNAN)
#define _FPCLASS_QNAN __FPCLASS_QNAN /* quiet NaN. */
#endif /* !_FPCLASS_QNAN && __FPCLASS_QNAN */
#if !defined(_FPCLASS_NINF) && defined(__FPCLASS_NINF)
#define _FPCLASS_NINF __FPCLASS_NINF /* negative infinity. */
#endif /* !_FPCLASS_NINF && __FPCLASS_NINF */
#if !defined(_FPCLASS_NN) && defined(__FPCLASS_NN)
#define _FPCLASS_NN   __FPCLASS_NN   /* negative normal. */
#endif /* !_FPCLASS_NN && __FPCLASS_NN */
#if !defined(_FPCLASS_ND) && defined(__FPCLASS_ND)
#define _FPCLASS_ND   __FPCLASS_ND   /* negative denormal. */
#endif /* !_FPCLASS_ND && __FPCLASS_ND */
#if !defined(_FPCLASS_NZ) && defined(__FPCLASS_NZ)
#define _FPCLASS_NZ   __FPCLASS_NZ   /* -0 */
#endif /* !_FPCLASS_NZ && __FPCLASS_NZ */
#if !defined(_FPCLASS_PZ) && defined(__FPCLASS_PZ)
#define _FPCLASS_PZ   __FPCLASS_PZ   /* +0 */
#endif /* !_FPCLASS_PZ && __FPCLASS_PZ */
#if !defined(_FPCLASS_PD) && defined(__FPCLASS_PD)
#define _FPCLASS_PD   __FPCLASS_PD   /* positive denormal. */
#endif /* !_FPCLASS_PD && __FPCLASS_PD */
#if !defined(_FPCLASS_PN) && defined(__FPCLASS_PN)
#define _FPCLASS_PN   __FPCLASS_PN   /* positive normal. */
#endif /* !_FPCLASS_PN && __FPCLASS_PN */
#if !defined(_FPCLASS_PINF) && defined(__FPCLASS_PINF)
#define _FPCLASS_PINF __FPCLASS_PINF /* positive infinity. */
#endif /* !_FPCLASS_PINF && __FPCLASS_PINF */

#ifdef __CC__
}

[[decl_include("<hybrid/typecore.h>")]]
$uint32_t _control87($uint32_t newval, $uint32_t mask) {
	return _controlfp(newval, mask);
}

%/* TODO: This function is most definitely x86-specific! */
%#if defined(__x86_64__) || defined(__i386__)
[[decl_include("<hybrid/typecore.h>")]]
int __control87_2($uint32_t newval, $uint32_t mask,
                  $uint32_t *x86_control_word,
                  $uint32_t *sse2_control_word);
%#endif /* X64... */

%/* TODO: This function is most definitely x86-specific! */
[[guard]] int *__fpecode();
%{
#ifdef ____fpecode_defined
#define _fpecode (*__fpecode())
#endif /* ____fpecode_defined */
}

%[insert:function(_copysign = copysign)]

%[insert:extern(_chgsign)]
%[insert:function(_scalb = scalb)]
%[insert:function(_logb = logb)]
%[insert:function(_nextafter = nextafter)]
%[insert:function(_finite = finite)]
%[insert:function(_isnan = isnan)]

@@>> _fpclass(3)
@@@return: * : Set of `_FPCLASS_*'
[[const, wunused, nothrow]]
int _fpclass(double x);

[[hidden, const, wunused, nothrow]]
int _fpclassf(float x);





%#if defined(__x86_64__) || defined(__i386__)
%[insert:function(_scalbf = scalbf)]
%#endif /* __x86_64__ || __i386__ */

[[dos_only_export_alias("_fpreset")]]
void fpreset();

%{

#define _clear87  _clearfp
#define _status87 _statusfp
#define clear87   _clear87
#define status87  _status87
#define control87 _control87
#endif /* __CC__ */

}
%#endif /* __USE_DOS */

%{

__SYSDECL_END

}
%(c, ccompat)#endif /* !__NO_FPU */
