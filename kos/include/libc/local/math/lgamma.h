/* HASH CRC-32:0xe4b4ada9 */
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
#ifndef __local_lgamma_defined
#define __local_lgamma_defined
#include <__crt.h>
#include <libc/template/signgam.h>
#include <ieee754.h>
#if defined(__LOCAL_signgam) && (defined(__CRT_HAVE_lgamma_r) || defined(__CRT_HAVE___lgamma_r) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_lgamma_r_defined
#define __local___localdep_lgamma_r_defined
#if __has_builtin(__builtin_lgamma_r) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma_r)
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_OUT(2),double,__NOTHROW_NCX,__localdep_lgamma_r,(double __x, int *__signgamp),lgamma_r,{ return __builtin_lgamma_r(__x, __signgamp); })
#elif defined(__CRT_HAVE_lgamma_r)
__CREDIRECT(__ATTR_WUNUSED __ATTR_OUT(2),double,__NOTHROW_NCX,__localdep_lgamma_r,(double __x, int *__signgamp),lgamma_r,(__x,__signgamp))
#elif defined(__CRT_HAVE___lgamma_r)
__CREDIRECT(__ATTR_WUNUSED __ATTR_OUT(2),double,__NOTHROW_NCX,__localdep_lgamma_r,(double __x, int *__signgamp),__lgamma_r,(__x,__signgamp))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/lgamma_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lgamma_r __LIBC_LOCAL_NAME(lgamma_r)
#else /* ... */
#undef __local___localdep_lgamma_r_defined
#endif /* !... */
#endif /* !__local___localdep_lgamma_r_defined */
__LOCAL_LIBC(lgamma) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(lgamma))(double __x) {
	return (__NAMESPACE_LOCAL_SYM __localdep_lgamma_r)(__x, &__LOCAL_signgam);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lgamma_defined
#define __local___localdep_lgamma_defined
#define __localdep_lgamma __LIBC_LOCAL_NAME(lgamma)
#endif /* !__local___localdep_lgamma_defined */
#else /* __LOCAL_signgam && (__CRT_HAVE_lgamma_r || __CRT_HAVE___lgamma_r || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
#undef __local_lgamma_defined
#endif /* !__LOCAL_signgam || (!__CRT_HAVE_lgamma_r && !__CRT_HAVE___lgamma_r && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) */
#endif /* !__local_lgamma_defined */
