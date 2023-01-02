/* HASH CRC-32:0x575cb37c */
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
#ifndef __local_llrintf_defined
#define __local_llrintf_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_rintf_defined
#define __local___localdep_rintf_defined
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_rintf,(float __x),rintf,{ return __builtin_rintf(__x); })
#elif __has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_rintf,(float __x),nearbyintf,{ return __builtin_nearbyintf(__x); })
#elif defined(__CRT_HAVE_rintf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_rintf,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE_nearbyintf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_rintf,(float __x),nearbyintf,(__x))
#elif defined(__CRT_HAVE___rintf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_rintf,(float __x),__rintf,(__x))
#elif defined(__CRT_HAVE___nearbyintf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__localdep_rintf,(float __x),__nearbyintf,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <ieee754.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/rintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rintf __LIBC_LOCAL_NAME(rintf)
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_rint || __CRT_HAVE_nearbyint || __CRT_HAVE___rint || __CRT_HAVE___nearbyint || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local___localdep_rintf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_rint && !__CRT_HAVE_nearbyint && !__CRT_HAVE___rint && !__CRT_HAVE___nearbyint && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !... */
#endif /* !__local___localdep_rintf_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libm/lrint.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(llrintf) __ATTR_CONST __ATTR_WUNUSED __LONGLONG
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(llrintf))(float __x) {
#ifdef __LIBM_MATHFUNIF
	return __LIBM_MATHFUNIF(llrint, __x);
#else /* __LIBM_MATHFUNIF */
	return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __localdep_rintf)(__x);
#endif /* !__LIBM_MATHFUNIF */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_llrintf_defined
#define __local___localdep_llrintf_defined
#define __localdep_llrintf __LIBC_LOCAL_NAME(llrintf)
#endif /* !__local___localdep_llrintf_defined */
#endif /* !__local_llrintf_defined */
