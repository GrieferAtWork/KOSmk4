/* HASH CRC-32:0x85d3c3cb */
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
#ifndef __local_scandir64_defined
#define __local_scandir64_defined 1
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_scandirat64) || (defined(__CRT_HAVE_scandirat) && defined(_DIRENT_MATCHES_DIRENT64)))
#include <features.h>
#include <bits/os/dirent.h>
#ifndef ____scandir64_selector_t_defined
#define ____scandir64_selector_t_defined 1
typedef int (*__scandir64_selector_t)(struct dirent64 const *);
typedef int (*__scandir64_cmp_t)(struct dirent64 const **, struct dirent64 const **);
#endif /* !____scandir64_selector_t_defined */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_scandirat64_defined
#define __local___localdep_scandirat64_defined 1
#ifdef __CRT_HAVE_scandirat64
__CREDIRECT(__ATTR_NONNULL((2, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct dirent64 ***__restrict __namelist, __scandir64_selector_t __selector, __scandir64_cmp_t __cmp),scandirat64,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat) && defined(_DIRENT_MATCHES_DIRENT64)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct dirent64 ***__restrict __namelist, __scandir64_selector_t __selector, __scandir64_cmp_t __cmp),scandirat,(__dirfd,__dir,__namelist,__selector,__cmp))
#else /* ... */
#undef __local___localdep_scandirat64_defined
#endif /* !... */
#endif /* !__local___localdep_scandirat64_defined */
__LOCAL_LIBC(scandir64) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(scandir64))(char const *__restrict __dir, struct dirent64 ***__restrict __namelist, __scandir64_selector_t __selector, __scandir64_cmp_t __cmp) {
	return __NAMESPACE_LOCAL_SYM __localdep_scandirat64(__AT_FDCWD, __dir, __namelist, __selector, __cmp);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_scandir64_defined
#define __local___localdep_scandir64_defined 1
#define __localdep_scandir64 __LIBC_LOCAL_NAME(scandir64)
#endif /* !__local___localdep_scandir64_defined */
#else /* __AT_FDCWD && (__CRT_HAVE_scandirat64 || (__CRT_HAVE_scandirat && _DIRENT_MATCHES_DIRENT64)) */
#undef __local_scandir64_defined
#endif /* !__AT_FDCWD || (!__CRT_HAVE_scandirat64 && (!__CRT_HAVE_scandirat || !_DIRENT_MATCHES_DIRENT64)) */
#endif /* !__local_scandir64_defined */
