/* HASH CRC-32:0x9ede7a70 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local___signbitl_defined
#if defined(__CRT_HAVE___signbit) || defined(__CRT_HAVE__dsign)
#define __local___signbitl_defined 1
/* Dependency: "__signbit" */
#ifndef ____localdep___signbit_defined
#define ____localdep___signbit_defined 1
#ifdef __CRT_HAVE___signbit
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbit,(double __val),__signbit,(__val))
#elif defined(__CRT_HAVE__dsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___signbit,(double __val),_dsign,(__val))
#else /* LIBC: __signbit */
#undef ____localdep___signbit_defined
#endif /* __signbit... */
#endif /* !____localdep___signbit_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__signbitl) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(__signbitl))(long double __val) {
#line 1313 "kos/src/libc/magic/math.c"
	return (int)__localdep___signbit((double)__val);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE___signbit) || defined(__CRT_HAVE__dsign) */
#endif /* !__local___signbitl_defined */
