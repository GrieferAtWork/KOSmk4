/* HASH CRC-32:0x2ac0e390 */
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
#ifndef __local_roundf_defined
#define __local_roundf_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>

#include <libm/round.h>
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

__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__LOCAL_LIBC(roundf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(roundf))(float __x) {
#line 1137 "kos/src/libc/magic/math.c"
#ifdef __LIBM_MATHFUNF
	#ifdef __LIBM_MATHFUNF
	return (float)__LIBM_MATHFUNF(round, __x);
#else /* __LIBM_MATHFUN */
	float __result;
	__result = (float)(__INTMAX_TYPE__)__x;
	if (__x < 0.0f) {
		/* result >= x */
		if ((__result - __x) >= 0.5f)
			__result -= 1.0f;
	} else {
		/* result <= x */
		if ((__x - __result) >= 0.5f)
			__result += 1.0f;
	}
	return __result;
#endif /* !__LIBM_MATHFUN */
#else /* __LIBM_MATHFUNF */
	return (float)__localdep_round((double)__x);
#endif /* !__LIBM_MATHFUNF */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_roundf_defined */
