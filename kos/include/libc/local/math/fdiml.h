/* HASH CRC-32:0x1c6b4032 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fdiml_defined
#define __local_fdiml_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fabsl from math */
#ifndef __local___localdep_fabsl_defined
#define __local___localdep_fabsl_defined 1
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
/* Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fabsl,(__LONGDOUBLE __x),fabsl,{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fabsl,(__LONGDOUBLE __x),fabsl,(__x))
#elif defined(__CRT_HAVE___fabsl)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__localdep_fabsl,(__LONGDOUBLE __x),__fabsl,(__x))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/math/fabsl.h>
__NAMESPACE_LOCAL_BEGIN
/* Absolute value of `x' */
#define __localdep_fabsl __LIBC_LOCAL_NAME(fabsl)
#endif /* !... */
#endif /* !__local___localdep_fabsl_defined */
/* Return positive difference between `x' and `y' */
__LOCAL_LIBC(fdiml) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fdiml))(__LONGDOUBLE __x, __LONGDOUBLE __y) {
	/* TODO: ieee754-specific function */
	return __localdep_fabsl(__y - __x);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fdiml_defined
#define __local___localdep_fdiml_defined 1
#define __localdep_fdiml __LIBC_LOCAL_NAME(fdiml)
#endif /* !__local___localdep_fdiml_defined */
#endif /* !__local_fdiml_defined */
