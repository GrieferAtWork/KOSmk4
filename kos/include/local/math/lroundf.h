/* HASH CRC-32:0xbba6db67 */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_lroundf_defined
#define __local_lroundf_defined 1
#include <hybrid/typecore.h>

#include <libm/lround.h>
/* Dependency: "round" from "math" */
#ifndef ____localdep_round_defined
#define ____localdep_round_defined 1
#if __has_builtin(__builtin_round) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_round,(double __x),round,{ return __builtin_round(__x); })
#elif defined(__CRT_HAVE_round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_round,(double __x),round,(__x))
#elif defined(__CRT_HAVE___round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_round,(double __x),__round,(__x))
#else /* LIBC: round */
#include <local/math/round.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define __localdep_round (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(round))
#endif /* round... */
#endif /* !____localdep_round_defined */

/* Dependency: "lround" from "math" */
#ifndef ____localdep_lround_defined
#define ____localdep_lround_defined 1
#if __has_builtin(__builtin_lround) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__localdep_lround,(double __x),lround,{ return __builtin_lround(__x); })
#elif defined(__CRT_HAVE_lround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__localdep_lround,(double __x),lround,(__x))
#elif defined(__CRT_HAVE___lround)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__localdep_lround,(double __x),__lround,(__x))
#elif defined(__CRT_HAVE_llround) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__localdep_lround,(double __x),llround,(__x))
#else /* LIBC: lround */
#include <local/math/lround.h>
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define __localdep_lround (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lround))
#endif /* lround... */
#endif /* !____localdep_lround_defined */

__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__LOCAL_LIBC(lroundf) __ATTR_CONST __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lroundf))(float __x) {
#line 1120 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(lround, __x);
#else /* __LIBM_MATHFUNI */
	return (long int)__localdep_round(__x);
#endif /* !__LIBM_MATHFUNI */
#else /* __LIBM_MATHFUNF */
	return __localdep_lround((double)__x);
#endif /* !__LIBM_MATHFUNF */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_lroundf_defined */
