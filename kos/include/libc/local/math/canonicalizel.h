/* HASH CRC-32:0xfcb489c5 */
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
#ifndef __local_canonicalizel_defined
#define __local_canonicalizel_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___iscanonicall_defined
#define __local___localdep___iscanonicall_defined
#ifdef __CRT_HAVE___iscanonicall
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___iscanonicall,(__LONGDOUBLE __x),__iscanonicall,(__x))
#else /* __CRT_HAVE___iscanonicall */
__NAMESPACE_LOCAL_END
#include <libc/local/math/__iscanonicall.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___iscanonicall __LIBC_LOCAL_NAME(__iscanonicall)
#endif /* !__CRT_HAVE___iscanonicall */
#endif /* !__local___localdep___iscanonicall_defined */
#ifndef __local___localdep___issignalingl_defined
#define __local___localdep___issignalingl_defined
#ifdef __CRT_HAVE_issignalingl
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___issignalingl,(__LONGDOUBLE __x),issignalingl,(__x))
#elif defined(__CRT_HAVE___issignalingl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___issignalingl,(__LONGDOUBLE __x),__issignalingl,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE___issignaling) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___issignalingl,(__LONGDOUBLE __x),__issignaling,(__x))
#elif defined(__CRT_HAVE_issignaling) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___issignalingl,(__LONGDOUBLE __x),issignaling,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <ieee754.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_issignaling) || defined(__CRT_HAVE___issignaling) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/__issignalingl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep___issignalingl __LIBC_LOCAL_NAME(__issignalingl)
#else /* __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_issignaling || __CRT_HAVE___issignaling || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local___localdep___issignalingl_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ && !__CRT_HAVE_issignaling && !__CRT_HAVE___issignaling && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep___issignalingl_defined */
__LOCAL_LIBC(canonicalizel) __ATTR_IN(2) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(canonicalizel))(__LONGDOUBLE *__cx, __LONGDOUBLE const *__x) {
	__LONGDOUBLE ___value = *__x;

	if (!(__NAMESPACE_LOCAL_SYM __localdep___iscanonicall)(___value))
		return 1;

	if ((__NAMESPACE_LOCAL_SYM __localdep___issignalingl)(___value)) {
		*__cx = ___value + ___value;
	} else {
		*__cx = ___value;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_canonicalizel_defined
#define __local___localdep_canonicalizel_defined
#define __localdep_canonicalizel __LIBC_LOCAL_NAME(canonicalizel)
#endif /* !__local___localdep_canonicalizel_defined */
#endif /* !__local_canonicalizel_defined */
