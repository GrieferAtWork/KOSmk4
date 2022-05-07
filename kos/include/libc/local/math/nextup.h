/* HASH CRC-32:0xa0de4d5d */
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
#ifndef __local_nextup_defined
#define __local_nextup_defined
#include <__crt.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libm/nextup.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(nextup) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(nextup))(double __x) {
#ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__
	return (double)__ieee754_nextup((__IEEE754_DOUBLE_TYPE__)__x);
#elif defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
	return (double)__ieee754_nextupf((__IEEE754_FLOAT_TYPE__)__x);
#else /* ... */
	return (double)__ieee854_nextupl((__IEEE854_LONG_DOUBLE_TYPE__)__x);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_nextup_defined
#define __local___localdep_nextup_defined
#define __localdep_nextup __LIBC_LOCAL_NAME(nextup)
#endif /* !__local___localdep_nextup_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_nextup_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_nextup_defined */
