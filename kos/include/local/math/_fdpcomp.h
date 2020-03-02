/* HASH CRC-32:0x268936fa */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__fdpcomp_defined
#ifdef __CRT_HAVE__dpcomp
#define __local__fdpcomp_defined 1
/* Dependency: "_dpcomp" from "math" */
#ifndef ____localdep__dpcomp_defined
#define ____localdep__dpcomp_defined 1
#ifdef __CRT_HAVE__dpcomp
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__dpcomp,(double __x, double __y),_dpcomp,(__x,__y))
#else /* LIBC: _dpcomp */
#undef ____localdep__dpcomp_defined
#endif /* _dpcomp... */
#endif /* !____localdep__dpcomp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_fdpcomp) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_fdpcomp))(float __x,
                                                      float __y) {
#line 3027 "kos/src/libc/magic/math.c"
	return (int)__localdep__dpcomp((double)__x, (double)__y);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE__dpcomp */
#endif /* !__local__fdpcomp_defined */
