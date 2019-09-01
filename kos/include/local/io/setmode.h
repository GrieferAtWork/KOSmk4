/* HASH 0x91ad9dfb */
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
#ifndef __local_setmode_defined
#if defined(__CRT_HAVE_fcntl) && (defined(__KOS__) || defined(__linux__))
#define __local_setmode_defined 1
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "fcntl" */
#ifndef ____localdep_fcntl_defined
#define ____localdep_fcntl_defined 1
#if defined(__CRT_HAVE_fcntl)
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, int __cmd),fcntl,(__fd,__cmd),__cmd,1,(void *))
#else /* LIBC: fcntl */
#undef ____localdep_fcntl_defined
#endif /* fcntl... */
#endif /* !____localdep_fcntl_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(setmode) __oflag_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setmode))(__fd_t __fd,
                                                     __oflag_t __mode) {
#line 292 "kos/src/libc/magic/io.c"
#ifdef __KOS__
	return __localdep_fcntl(__fd, 5163, __mode); /* F_SETFL_XCH */
#else
	__oflag_t __result;
	__result = __localdep_fcntl(__fd, 3); /* F_GETFL */
	if __unlikely(__result < 0)
		return -1;
	return __localdep_fcntl(__fd, 4, __mode); /* F_SETFL */
#endif
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_fcntl) && (defined(__KOS__) || defined(__linux__)) */
#endif /* !__local_setmode_defined */
