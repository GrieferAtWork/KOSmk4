/* HASH CRC-32:0xd277e405 */
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
#ifndef _BITS_STD_ABS_H
#define _BITS_STD_ABS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <stdlib.h>
#include <math.h>

/* NOTE: This file is needed for libstdc++ compatibility.
 *
 * It needs to define any possibly missing variant of `std::abs',
 * working  together with system headers <stdlib.h> and <math.h>.
 */

#ifdef __CC__
__SYSDECL_BEGIN

__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
#ifndef __CORRECT_ISO_CPP_STDLIB_H_PROTO
extern "C++" {
#if __has_builtin(__builtin_labs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_labs)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),labs,{ return __builtin_labs(__x); })
#elif defined(__CRT_HAVE_labs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),labs,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <hybrid/typecore.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
#if defined(__CRT_HAVE_abs) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),abs,(__x))
#elif defined(__CRT_HAVE_llabs) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),llabs,(__x))
#elif defined(__CRT_HAVE_qabs) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),qabs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long,__NOTHROW,abs,(long __x),_abs64,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/stdlib/labs.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long __NOTHROW(__LIBCCALL abs)(long __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(labs))(__x); }
#endif /* !... */
#endif /* !... */
#ifdef __CRT_HAVE_ldiv
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),ldiv,(__numer,__denom))
#else /* __CRT_HAVE_ldiv */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <hybrid/typecore.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
#if defined(__CRT_HAVE_div) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_lldiv) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_qdiv) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),qdiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __ldiv_struct,__NOTHROW_NCX,div,(long __numer, long __denom),imaxdiv,(__numer,__denom))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/stdlib/ldiv.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED struct __ldiv_struct __NOTHROW_NCX(__LIBCCALL div)(long __numer, long __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldiv))(__numer, __denom); }
#endif /* !... */
#endif /* !__CRT_HAVE_ldiv */
} /* extern "C++" */
#endif /* !__CORRECT_ISO_CPP_STDLIB_H_PROTO */
#if (!defined(__CORRECT_ISO_CPP_STDLIB_H_PROTO) || !defined(__USE_ISOC99)) && defined(__COMPILER_HAVE_LONGLONG)
extern "C++" {
#if __has_builtin(__builtin_llabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llabs)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),llabs,{ return __builtin_llabs(__x); })
#elif defined(__CRT_HAVE_llabs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),llabs,(__x))
#elif defined(__CRT_HAVE_qabs)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),qabs,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <hybrid/typecore.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
#if defined(__CRT_HAVE_abs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),abs,(__x))
#elif defined(__CRT_HAVE_labs) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),labs,(__x))
#elif defined(__CRT_HAVE_imaxabs) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),imaxabs,(__x))
#elif defined(__CRT_HAVE__abs64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,abs,(__LONGLONG __x),_abs64,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/stdlib/llabs.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL abs)(__LONGLONG __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llabs))(__x); }
#endif /* !... */
#endif /* !... */
#ifdef __CRT_HAVE_lldiv
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),lldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_qdiv)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),qdiv,(__numer,__denom))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <hybrid/typecore.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
#if defined(__CRT_HAVE_div) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),div,(__numer,__denom))
#elif defined(__CRT_HAVE_ldiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),ldiv,(__numer,__denom))
#elif defined(__CRT_HAVE_imaxdiv) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,struct __lldiv_struct,__NOTHROW_NCX,div,(__LONGLONG __numer, __LONGLONG __denom),imaxdiv,(__numer,__denom))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/stdlib/lldiv.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED struct __lldiv_struct __NOTHROW_NCX(__LIBCCALL div)(__LONGLONG __numer, __LONGLONG __denom) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lldiv))(__numer, __denom); }
#endif /* !... */
#endif /* !... */
} /* extern "C++" */
#endif /* (!__CORRECT_ISO_CPP_STDLIB_H_PROTO || !__USE_ISOC99) && __COMPILER_HAVE_LONGLONG */
#if !defined(__CORRECT_ISO_CPP_MATH_H_PROTO) && !defined(__NO_FPU)
extern "C++" {
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,abs,(float __x),fabsf,{ return __builtin_fabsf(__x); })
#elif defined(__CRT_HAVE_fabsf)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,abs,(float __x),fabsf,(__x))
#elif defined(__CRT_HAVE___fabsf)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,abs,(float __x),__fabsf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fabsf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL abs)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,abs,(double __x),fabs,{ return __builtin_fabs(__x); })
#elif defined(__CRT_HAVE_fabs)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,abs,(double __x),fabs,(__x))
#elif defined(__CRT_HAVE___fabs)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,abs,(double __x),__fabs,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fabs.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL abs)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabs))(__x); }
#endif /* !... */
} /* extern "C++" */
#ifdef __COMPILER_HAVE_LONGDOUBLE
extern "C++" {
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,abs,(__LONGDOUBLE __x),fabsl,{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,abs,(__LONGDOUBLE __x),fabsl,(__x))
#elif defined(__CRT_HAVE___fabsl)
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,abs,(__LONGDOUBLE __x),__fabsl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fabsl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* >> fabsf(3), fabs(3), fabsl(3)
 * Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL abs)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsl))(__x); }
#endif /* !... */
} /* extern "C++" */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__CORRECT_ISO_CPP_MATH_H_PROTO && !__NO_FPU */
#endif /* __cplusplus */
__NAMESPACE_STD_END

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_STD_ABS_H */
