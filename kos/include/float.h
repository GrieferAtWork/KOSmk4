/* HASH CRC-32:0xf9c59383 */
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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: DJGPP         (/include/float.h) */
/* (#) Portability: FreeBSD       (/sys/[...]/include/float.h) */
/* (#) Portability: GNU C Library (/include/float.h) */
/* (#) Portability: MSVC          (/include/float.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/float.h) */
/* (#) Portability: NetBSD        (/sys/arch/[...]/include/float.h) */
/* (#) Portability: OpenBSD       (/include/float.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/float.h) */
/* (#) Portability: Windows Kits  (/ucrt/float.h) */
/* (#) Portability: diet libc     (/include/float.h) */
/* (#) Portability: musl libc     (/include/float.h) */
#ifndef _FLOAT_H
#define _FLOAT_H 1

#ifdef _CXX_STDONLY_CFLOAT
#ifdef __CXX_SYSTEM_HEADER
#undef _FLOAT_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "float.h" after "cfloat" */
#ifndef __NO_FPU
#endif /* !__NO_FPU */
#undef _CXX_STDONLY_CFLOAT
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CFLOAT */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#ifndef __NO_FPU
#include <features.h>

#include <hybrid/floatcore.h>
#include <hybrid/host.h> /* TODO: Get rid of this #include! */
#include <hybrid/typecore.h>

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
#ifdef __CRT_HAVE___fpe_flt_rounds
#define FLT_ROUNDS __fpe_flt_rounds()
#ifdef __CC__
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpe_flt_rounds,(void),())
#endif /* !__CC__ */
#else /* __CRT_HAVE___fpe_flt_rounds */
#define FLT_ROUNDS 1
#endif /* !__CRT_HAVE___fpe_flt_rounds */
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


#ifdef __USE_DOS
#ifdef __CC__
__CDECLARE_OPT(,__UINT32_TYPE__,__NOTHROW_NCX,_clearfp,(void),())
#ifdef __CRT_HAVE__controlfp
__CDECLARE(,__UINT32_TYPE__,__NOTHROW_NCX,_controlfp,(__UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask),(__newval,__mask))
#else /* __CRT_HAVE__controlfp */
#include <fpu_control.h>
#if defined(_FPU_GETCW) && defined(_FPU_SETCW)
#include <libc/local/float/_controlfp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_controlfp, __FORCELOCAL __ATTR_ARTIFICIAL __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL _controlfp)(__UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_controlfp))(__newval, __mask); })
#endif /* _FPU_GETCW && _FPU_SETCW */
#endif /* !__CRT_HAVE__controlfp */
#ifdef __CRT_HAVE__set_controlfp
__CDECLARE_VOID(,__NOTHROW_NCX,_set_controlfp,(__UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask),(__newval,__mask))
#else /* __CRT_HAVE__set_controlfp */
#include <fpu_control.h>
#if defined(__CRT_HAVE__controlfp) || (defined(_FPU_GETCW) && defined(_FPU_SETCW))
#include <libc/local/float/_set_controlfp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_set_controlfp, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL _set_controlfp)(__UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_set_controlfp))(__newval, __mask); })
#endif /* __CRT_HAVE__controlfp || (_FPU_GETCW && _FPU_SETCW) */
#endif /* !__CRT_HAVE__set_controlfp */
#ifdef __CRT_HAVE__controlfp_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_controlfp_s,(__UINT32_TYPE__ *__pcurrent, __UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask),(__pcurrent,__newval,__mask))
#else /* __CRT_HAVE__controlfp_s */
#include <fpu_control.h>
#if defined(__CRT_HAVE__controlfp) || (defined(_FPU_GETCW) && defined(_FPU_SETCW))
#include <libc/local/float/_controlfp_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_controlfp_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _controlfp_s)(__UINT32_TYPE__ *__pcurrent, __UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_controlfp_s))(__pcurrent, __newval, __mask); })
#endif /* __CRT_HAVE__controlfp || (_FPU_GETCW && _FPU_SETCW) */
#endif /* !__CRT_HAVE__controlfp_s */
__CDECLARE_OPT(,__UINT32_TYPE__,__NOTHROW_NCX,_statusfp,(void),())
#ifdef __CRT_HAVE_fpreset
__CREDIRECT_VOID(,__NOTHROW_NCX,_fpreset,(void),fpreset,())
#elif defined(__CRT_HAVE__fpreset)
__CDECLARE_VOID(,__NOTHROW_NCX,_fpreset,(void),())
#endif /* ... */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,_statusfp2,(__UINT32_TYPE__ *__x86_stat, __UINT32_TYPE__ *__sse2_stat),(__x86_stat,__sse2_stat))
#endif /* __CC__ */

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
#ifdef __CRT_HAVE__control87
__CDECLARE(,__UINT32_TYPE__,__NOTHROW_NCX,_control87,(__UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask),(__newval,__mask))
#else /* __CRT_HAVE__control87 */
#include <libc/local/float/_control87.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_control87, __FORCELOCAL __ATTR_ARTIFICIAL __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL _control87)(__UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_control87))(__newval, __mask); })
#endif /* !__CRT_HAVE__control87 */
/* TODO: This function is most definitely x86-specific! */
#if defined(__x86_64__) || defined(__i386__)
__CDECLARE_OPT(,int,__NOTHROW_NCX,__control87_2,(__UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask, __UINT32_TYPE__ *__x86_control_word, __UINT32_TYPE__ *__sse2_control_word),(__newval,__mask,__x86_control_word,__sse2_control_word))
#endif /* X64... */
/* TODO: This function is most definitely x86-specific! */
#if !defined(____fpecode_defined) && defined(__CRT_HAVE___fpecode)
#define ____fpecode_defined
__CDECLARE(,int *,__NOTHROW_NCX,__fpecode,(void),())
#endif /* !____fpecode_defined && __CRT_HAVE___fpecode */
#ifdef ____fpecode_defined
#define _fpecode (*__fpecode())
#endif /* ____fpecode_defined */
#if __has_builtin(__builtin_copysign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysign)
/* >> copysignf(3), copysign(3), copysignl(3)
 * Return `x' with its signed changed to `y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_copysign,(double __num, double __sign),copysign,{ return __builtin_copysign(__num, __sign); })
#elif defined(__CRT_HAVE_copysign)
/* >> copysignf(3), copysign(3), copysignl(3)
 * Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_copysign,(double __num, double __sign),copysign,(__num,__sign))
#elif defined(__CRT_HAVE___copysign)
/* >> copysignf(3), copysign(3), copysignl(3)
 * Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_copysign,(double __num, double __sign),__copysign,(__num,__sign))
#elif defined(__CRT_HAVE__copysign)
/* >> copysignf(3), copysign(3), copysignl(3)
 * Return `x' with its signed changed to `y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_copysign,(double __num, double __sign),(__num,__sign))
#else /* ... */
#include <libc/local/math/copysign.h>
/* >> copysignf(3), copysign(3), copysignl(3)
 * Return `x' with its signed changed to `y's */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL _copysign)(double __num, double __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysign))(__num, __sign); }
#endif /* !... */
#ifdef __CRT_HAVE__chgsign
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_chgsign,(double __x),(__x))
#else /* __CRT_HAVE__chgsign */
#include <libc/local/float/_chgsign.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_chgsign, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL _chgsign)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_chgsign))(__x); })
#endif /* !__CRT_HAVE__chgsign */
#if __has_builtin(__builtin_scalb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalb)
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,_scalb,(double __x, double __fn),scalb,{ return __builtin_scalb(__x, __fn); })
#elif defined(__CRT_HAVE_scalb)
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,_scalb,(double __x, double __fn),scalb,(__x,__fn))
#elif defined(__CRT_HAVE__scalb)
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,_scalb,(double __x, double __fn),(__x,__fn))
#elif defined(__CRT_HAVE___scalb)
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,_scalb,(double __x, double __fn),__scalb,(__x,__fn))
#else /* ... */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalb.h>
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL _scalb)(double __x, double __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalb))(__x, __fn); }
#endif /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
#if __has_builtin(__builtin_logb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logb)
/* >> logbf(3), logb(3), logbl(3)
 * Return the base 2 signed integral exponent of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_logb,(double __x),logb,{ return __builtin_logb(__x); })
#elif defined(__CRT_HAVE_logb)
/* >> logbf(3), logb(3), logbl(3)
 * Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_logb,(double __x),logb,(__x))
#elif defined(__CRT_HAVE___logb)
/* >> logbf(3), logb(3), logbl(3)
 * Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_logb,(double __x),__logb,(__x))
#elif defined(__CRT_HAVE__logb)
/* >> logbf(3), logb(3), logbl(3)
 * Return the base 2 signed integral exponent of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_logb,(double __x),(__x))
#else /* ... */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/logb.h>
/* >> logbf(3), logb(3), logbl(3)
 * Return the base 2 signed integral exponent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL _logb)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logb))(__x); }
#endif /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
#if __has_builtin(__builtin_nextafter) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafter)
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_nextafter,(double __x, double __y),nextafter,{ return __builtin_nextafter(__x, __y); })
#elif __has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttoward)
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_nextafter,(double __x, double __y),nexttoward,{ return __builtin_nexttoward(__x); })
#elif defined(__CRT_HAVE_nextafter)
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_nextafter,(double __x, double __y),nextafter,(__x,__y))
#elif defined(__CRT_HAVE_nexttoward)
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_nextafter,(double __x, double __y),nexttoward,(__x,__y))
#elif defined(__CRT_HAVE___nextafter)
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_nextafter,(double __x, double __y),__nextafter,(__x,__y))
#elif defined(__CRT_HAVE__nextafter)
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_nextafter,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___nexttoward)
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,_nextafter,(double __x, double __y),__nexttoward,(__x,__y))
#else /* ... */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/nextafter.h>
/* >> nextafterf(3), nextafter(3), nextafterl(3)
 * Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL _nextafter)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafter))(__x, __y); }
#endif /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
#if __has_builtin(__builtin_finite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finite)
/* >> finitef(3), finite(3), finitel(3)
 * Return nonzero if `value' is finite and not NaN */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_finite,(double __x),finite,{ return __builtin_finite(__x); })
#elif defined(__CRT_HAVE_finite)
/* >> finitef(3), finite(3), finitel(3)
 * Return nonzero if `value' is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_finite,(double __x),finite,(__x))
#elif defined(__CRT_HAVE___finite)
/* >> finitef(3), finite(3), finitel(3)
 * Return nonzero if `value' is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_finite,(double __x),__finite,(__x))
#elif defined(__CRT_HAVE__finite)
/* >> finitef(3), finite(3), finitel(3)
 * Return nonzero if `value' is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_finite,(double __x),(__x))
#else /* ... */
#include <ieee754.h>
#include <bits/math-constants.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
#include <libc/local/math/finite.h>
/* >> finitef(3), finite(3), finitel(3)
 * Return nonzero if `value' is finite and not NaN */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL _finite)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finite))(__x); }
#endif /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || ((__CRT_HAVE_isinf || __CRT_HAVE___isinf || __INFINITY || __HUGE_VAL) && (__CRT_HAVE_isnan || __CRT_HAVE__isnan || __CRT_HAVE___isnan)) */
#endif /* !... */
#if __has_builtin(__builtin_isnan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnan)
/* >> isnanf(3), isnan(3), isnanl(3)
 * Return nonzero if `value' is not a number */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_isnan,(double __x),isnan,{ return __builtin_isnan(__x); })
#elif defined(__CRT_HAVE_isnan)
/* >> isnanf(3), isnan(3), isnanl(3)
 * Return nonzero if `value' is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_isnan,(double __x),isnan,(__x))
#elif defined(__CRT_HAVE__isnan)
/* >> isnanf(3), isnan(3), isnanl(3)
 * Return nonzero if `value' is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_isnan,(double __x),(__x))
#elif defined(__CRT_HAVE___isnan)
/* >> isnanf(3), isnan(3), isnanl(3)
 * Return nonzero if `value' is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_isnan,(double __x),__isnan,(__x))
#else /* ... */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/isnan.h>
/* >> isnanf(3), isnan(3), isnanl(3)
 * Return nonzero if `value' is not a number */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL _isnan)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnan))(__x); }
#endif /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
/* >> _fpclass(3)
 * @return: * : Set of `_FPCLASS_*' */
__CDECLARE_OPT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_fpclass,(double __x),(__x))
#if defined(__x86_64__) || defined(__i386__)
#if __has_builtin(__builtin_scalbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbf)
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,_scalbf,(float __x, float __fn),scalbf,{ return __builtin_scalbf(__x, __fn); })
#elif defined(__CRT_HAVE_scalbf)
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,_scalbf,(float __x, float __fn),scalbf,(__x,__fn))
#elif defined(__CRT_HAVE__scalbf)
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,_scalbf,(float __x, float __fn),(__x,__fn))
#elif defined(__CRT_HAVE___scalbf)
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,_scalbf,(float __x, float __fn),__scalbf,(__x,__fn))
#else /* ... */
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalb) || defined(__CRT_HAVE__scalb) || defined(__CRT_HAVE___scalb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalbf.h>
/* >> scalbf(3), scalb(3), scalbl(3)
 * Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL _scalbf)(float __x, float __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbf))(__x, __fn); }
#endif /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_scalb || __CRT_HAVE__scalb || __CRT_HAVE___scalb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
#endif /* __x86_64__ || __i386__ */
#ifdef __CRT_HAVE_fpreset
__CDECLARE_VOID(,__NOTHROW_NCX,fpreset,(void),())
#elif defined(__CRT_HAVE__fpreset)
__CREDIRECT_VOID(,__NOTHROW_NCX,fpreset,(void),_fpreset,())
#endif /* ... */

#define _clear87  _clearfp
#define _status87 _statusfp
#define clear87   _clear87
#define status87  _status87
#define control87 _control87
#endif /* __CC__ */

#endif /* __USE_DOS */

__SYSDECL_END

#endif /* !__NO_FPU */
#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CFLOAT
#undef _FLOAT_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CFLOAT */
#endif /* !_FLOAT_H */
