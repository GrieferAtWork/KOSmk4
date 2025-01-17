/* HASH CRC-32:0x9f4b90d2 */
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
#ifndef __local_log2_defined
#define __local_log2_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_feraiseexcept_defined
#define __local___localdep_feraiseexcept_defined
#ifdef __CRT_HAVE_feraiseexcept
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__THROWING(...),__localdep_feraiseexcept,(int __excepts),feraiseexcept,(__excepts))
#else /* __CRT_HAVE_feraiseexcept */
__NAMESPACE_LOCAL_END
#include <libc/local/fenv/feraiseexcept.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_feraiseexcept __LIBC_LOCAL_NAME(feraiseexcept)
#endif /* !__CRT_HAVE_feraiseexcept */
#endif /* !__local___localdep_feraiseexcept_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/fenv.h>
#include <bits/math-constants.h>
#include <libm/nan.h>
#include <libm/log2.h>
#include <libm/fcomp.h>
#include <libm/matherr.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(log2) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(log2))(double __x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(islessequal, __x, 0.0)) {
		if (__x == 0.0) {
			(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(FE_DIVBYZERO);
			return __kernel_standard(__x, __x, -__HUGE_VAL,
			                         __LIBM_KMATHERR_LOG2_ZERO); /* log2(0) */
		} else {
			(__NAMESPACE_LOCAL_SYM __localdep_feraiseexcept)(FE_INVALID);
			return __kernel_standard(__x, __x, __LIBM_MATHFUN1I(nan, ""),
			                         __LIBM_KMATHERR_LOG2_MINUS); /* log2(x<0) */
		}
	}
	return __LIBM_MATHFUN(log2, __x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_log2_defined
#define __local___localdep_log2_defined
#define __localdep_log2 __LIBC_LOCAL_NAME(log2)
#endif /* !__local___localdep_log2_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_log2_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_log2_defined */
