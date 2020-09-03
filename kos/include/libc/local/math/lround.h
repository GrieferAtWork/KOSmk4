/* HASH CRC-32:0xd202a357 */
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
#ifndef __local_lround_defined
#define __local_lround_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: round from math */
#ifndef __local___localdep_round_defined
#define __local___localdep_round_defined 1
#if __has_builtin(__builtin_round) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_round,(double __x),round,{ return __builtin_round(__x); })
#elif defined(__CRT_HAVE_round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_round,(double __x),round,(__x))
#elif defined(__CRT_HAVE___round)
/* Round X to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__localdep_round,(double __x),__round,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/round.h>
__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
#define __localdep_round __LIBC_LOCAL_NAME(round)
#endif /* !... */
#endif /* !__local___localdep_round_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libm/lround.h>
__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__LOCAL_LIBC(lround) __ATTR_CONST __ATTR_WUNUSED long int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lround))(double __x) {
#ifdef __LIBM_MATHFUNI
	return __LIBM_MATHFUNI(lround, __x);
#else /* __LIBM_MATHFUNI */
	return (long int)__localdep_round(__x);
#endif /* !__LIBM_MATHFUNI */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lround_defined
#define __local___localdep_lround_defined 1
#define __localdep_lround __LIBC_LOCAL_NAME(lround)
#endif /* !__local___localdep_lround_defined */
#endif /* !__local_lround_defined */
