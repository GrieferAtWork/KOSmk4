/* HASH CRC-32:0x9e547515 */
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
#ifndef __local_pow10_defined
#define __local_pow10_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pow_defined
#define __local___localdep_pow_defined
#if __has_builtin(__builtin_pow) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__localdep_pow,(double __x, double __y),pow,{ return __builtin_pow(__x, __y); })
#elif defined(__CRT_HAVE_pow)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__localdep_pow,(double __x, double __y),pow,(__x,__y))
#elif defined(__CRT_HAVE___pow)
__NAMESPACE_LOCAL_END
#include <bits/crt/math-vector.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__localdep_pow,(double __x, double __y),__pow,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/pow.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pow __LIBC_LOCAL_NAME(pow)
#else /* ... */
#undef __local___localdep_pow_defined
#endif /* !... */
#endif /* !__local___localdep_pow_defined */
__LOCAL_LIBC(pow10) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(pow10))(double __x) {
	return (__NAMESPACE_LOCAL_SYM __localdep_pow)(10.0, __x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pow10_defined
#define __local___localdep_pow10_defined
#define __localdep_pow10 __LIBC_LOCAL_NAME(pow10)
#endif /* !__local___localdep_pow10_defined */
#else /* __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_pow10_defined
#endif /* !__CRT_HAVE_pow && !__CRT_HAVE___pow && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_pow10_defined */
