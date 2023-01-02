/* HASH CRC-32:0x545f891a */
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
#ifndef __local__setmode_defined
#define __local__setmode_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && (defined(__F_SETFL_XCH) || (defined(__F_GETFL) && defined(__F_SETFL)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fcntl_defined
#define __local___localdep_fcntl_defined
#ifdef __CRT_HAVE_fcntl
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __fcntl_t __cmd),fcntl,(__fd,__cmd),__cmd,1,(void *))
#elif defined(__CRT_HAVE___fcntl)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __fcntl_t __cmd),__fcntl,(__fd,__cmd),__cmd,1,(void *))
#elif defined(__CRT_HAVE___libc_fcntl)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __fcntl_t __cmd),__libc_fcntl,(__fd,__cmd),__cmd,1,(void *))
#else /* ... */
#undef __local___localdep_fcntl_defined
#endif /* !... */
#endif /* !__local___localdep_fcntl_defined */
__LOCAL_LIBC(_setmode) __oflag_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_setmode))(__fd_t __fd, __oflag_t __mode) {
#ifdef __F_SETFL_XCH
	return (__NAMESPACE_LOCAL_SYM __localdep_fcntl)(__fd, __F_SETFL_XCH, __mode);
#else /* __F_SETFL_XCH */
	__oflag_t __result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_fcntl)(__fd, __F_GETFL);
	if __unlikely(__result < 0)
		return -1;
	return (__NAMESPACE_LOCAL_SYM __localdep_fcntl)(__fd, __F_SETFL, __mode);
#endif /* !__F_SETFL_XCH */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__setmode_defined
#define __local___localdep__setmode_defined
#define __localdep__setmode __LIBC_LOCAL_NAME(_setmode)
#endif /* !__local___localdep__setmode_defined */
#else /* (__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && (__F_SETFL_XCH || (__F_GETFL && __F_SETFL)) */
#undef __local__setmode_defined
#endif /* (!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || (!__F_SETFL_XCH && (!__F_GETFL || !__F_SETFL)) */
#endif /* !__local__setmode_defined */
