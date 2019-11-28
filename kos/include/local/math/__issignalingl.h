/* HASH CRC-32:0xfb60b42f */
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
#ifndef __local___issignalingl_defined
#ifdef __CRT_HAVE___issignaling
#define __local___issignalingl_defined 1
/* Dependency: "__issignaling" */
#ifndef ____localdep___issignaling_defined
#define ____localdep___issignaling_defined 1
#ifdef __CRT_HAVE___issignaling
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep___issignaling,(double __val),__issignaling,(__val))
#else /* LIBC: __issignaling */
#undef ____localdep___issignaling_defined
#endif /* __issignaling... */
#endif /* !____localdep___issignaling_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__issignalingl) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(__issignalingl))(long double __val) {
#line 1322 "kos/src/libc/magic/math.c"
	return (int)__localdep___issignaling((double)__val);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE___issignaling */
#endif /* !__local___issignalingl_defined */
