/* HASH CRC-32:0x79284ef4 */
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
#ifndef __local__access_s_defined
#define __local__access_s_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_access) || defined(__CRT_HAVE__access) || defined(__CRT_HAVE___access) || defined(__CRT_HAVE___libc_access) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat))
#include <bits/types.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_access_defined
#define __local___localdep_access_defined
#ifdef __CRT_HAVE_access
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_access,(char const *__file, __STDC_INT_AS_UINT_T __type),access,(__file,__type))
#elif defined(__CRT_HAVE__access)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_access,(char const *__file, __STDC_INT_AS_UINT_T __type),_access,(__file,__type))
#elif defined(__CRT_HAVE___access)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_access,(char const *__file, __STDC_INT_AS_UINT_T __type),__access,(__file,__type))
#elif defined(__CRT_HAVE___libc_access)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_access,(char const *__file, __STDC_INT_AS_UINT_T __type),__libc_access,(__file,__type))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/access.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_access __LIBC_LOCAL_NAME(access)
#else /* ... */
#undef __local___localdep_access_defined
#endif /* !... */
#endif /* !__local___localdep_access_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_access_s) __ATTR_ACCESS_RO(1) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_access_s))(char const *__filename, __STDC_INT_AS_UINT_T __type) {
	if ((__NAMESPACE_LOCAL_SYM __localdep_access)(__filename, __type) == 0)
		return __EOK;
	return __libc_geterrno_or(1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__access_s_defined
#define __local___localdep__access_s_defined
#define __localdep__access_s __LIBC_LOCAL_NAME(_access_s)
#endif /* !__local___localdep__access_s_defined */
#else /* __CRT_HAVE_access || __CRT_HAVE__access || __CRT_HAVE___access || __CRT_HAVE___libc_access || (__AT_FDCWD && __CRT_HAVE_faccessat) */
#undef __local__access_s_defined
#endif /* !__CRT_HAVE_access && !__CRT_HAVE__access && !__CRT_HAVE___access && !__CRT_HAVE___libc_access && (!__AT_FDCWD || !__CRT_HAVE_faccessat) */
#endif /* !__local__access_s_defined */
