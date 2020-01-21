/* HASH CRC-32:0x8cea1b11 */
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
#ifndef __local_ilogbl_defined
#if defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb)
#define __local_ilogbl_defined 1
/* Dependency: "ilogb" */
#ifndef ____localdep_ilogb_defined
#define ____localdep_ilogb_defined 1
#if __has_builtin(__builtin_ilogb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of X, which must be nonzero */
__EXTERNINLINE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_ilogb)(double __x) { return __builtin_ilogb(__x); }
#elif defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),ilogb,(__x))
#elif defined(__CRT_HAVE___ilogb)
/* Return the binary exponent of X, which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__localdep_ilogb,(double __x),__ilogb,(__x))
#else /* LIBC: ilogb */
#undef ____localdep_ilogb_defined
#endif /* ilogb... */
#endif /* !____localdep_ilogb_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the binary exponent of X, which must be nonzero */
__LOCAL_LIBC(ilogbl) __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ilogbl))(__LONGDOUBLE __x) {
#line 856 "kos/src/libc/magic/math.c"
	return (int)__localdep_ilogb((double)__x);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_ilogb || __CRT_HAVE___ilogb */
#endif /* !__local_ilogbl_defined */
