/* HASH CRC-32:0x3edccf7a */
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
#ifndef __local_remquof_defined
#define __local_remquof_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_remquo_defined
#define __local___localdep_remquo_defined
#if __has_builtin(__builtin_remquo) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquo)
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,__localdep_remquo,(double __x, double __p, int *__pquo),remquo,{ return __builtin_remquo(__x, __p, __pquo); })
#elif defined(__CRT_HAVE_remquo)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,__localdep_remquo,(double __x, double __p, int *__pquo),remquo,(__x,__p,__pquo))
#elif defined(__CRT_HAVE___remquo)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,__localdep_remquo,(double __x, double __p, int *__pquo),__remquo,(__x,__p,__pquo))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/remquo.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_remquo __LIBC_LOCAL_NAME(remquo)
#else /* ... */
#undef __local___localdep_remquo_defined
#endif /* !... */
#endif /* !__local___localdep_remquo_defined */
__NAMESPACE_LOCAL_END
#include <libm/remquo.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(remquof) __ATTR_WUNUSED __ATTR_NONNULL((3)) float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(remquof))(float __x, float __p, int *__pquo) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


	return __LIBM_MATHFUN3IF(remquo, __x, __p, __pquo);
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_remquo)((double)__x, (double)__p, __pquo);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_remquof_defined
#define __local___localdep_remquof_defined
#define __localdep_remquof __LIBC_LOCAL_NAME(remquof)
#endif /* !__local___localdep_remquof_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_remquo || __CRT_HAVE___remquo || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_remquof_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_remquo && !__CRT_HAVE___remquo && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_remquof_defined */
